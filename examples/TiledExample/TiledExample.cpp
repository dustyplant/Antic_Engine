#include <Antic/Antic.h>
#include <Antic/TiledLevel.h>
#include <Antic/Sprite.h>

enum AnimStates { IDLE, RUNNING };
struct AnimState
{
	int start;
	int stop;
};

class Elisa: public antic::PEntity, public antic::Observer
{
public:
	Elisa()
	{
		if( states.find( IDLE ) == states.end() )
		{
			AnimState newState { 0, 2 };
			states[ IDLE ] = newState;
		}

		if( states.find( RUNNING ) == states.end() )
		{
			AnimState newState { 5, 12 };
			states[ RUNNING ] = newState;
		}
	}

	virtual bool init()
	{
		currState = RUNNING;
		currIndex = states[ currState ].start;
		ss = agraph::SpriteSheetFactory::loadSS("elisa.json");
		if( ss == nullptr )
		{
			printf("Elisa SpriteSheet NULL\n");
			return false;
		}

		if( ss->getTexture() == nullptr )
		{
			printf("Elisa Texture NULL\n");
			return false;
		}

		setBody( antic::createBodyDynamic( 600, 100, 56, 56, 1.f, 0.3f ) );
		
		if( body == nullptr )
		{
			printf("Elisa body NULL\n");
			return false;
		}

		return true;
	}

	virtual void update( float dt )
	{
		
		while( antic::Observer::getNumEvents() > 0 )
		{
			antic::Event *currEvent = antic::Observer::pop_event();
			if( antic::SystemEvent *tempEvent = dynamic_cast<antic::SystemEvent*>( currEvent ) )
			{
				if( tempEvent->event.type == SDL_KEYDOWN )
				{
					b2Vec2 newForce( vel, vel );
					switch( tempEvent->event.key.keysym.sym )
					{
						case SDLK_w:
						case SDLK_UP:
							newForce = b2Vec2(0, -vel);
							this->body->SetLinearVelocity( newForce );
							break;
						case SDLK_s:
						case SDLK_DOWN:
							newForce = b2Vec2(0,  vel);
							this->body->SetLinearVelocity( newForce );
							break;
						case SDLK_d:
						case SDLK_RIGHT:
							newForce = b2Vec2( vel, 0);
							this->body->SetLinearVelocity( newForce );
							break;
						case SDLK_a:
						case SDLK_LEFT:
							newForce = b2Vec2(-vel, 0);
							this->body->SetLinearVelocity( newForce );
							break;
						default:
							newForce = b2Vec2(0, 0);
							this->body->SetLinearVelocity( newForce );
							break;
					}
				}
			}
		}

		currIndex += 1;
		if( currIndex > states[ currState ].stop )
			currIndex = states[ currState ].start;

	}

	virtual void render()
	{
		b2Fixture* fixture = this->body->GetFixtureList();
		if( fixture != nullptr )
		{
			b2Vec2 center = fixture->GetAABB( 0 ).GetCenter();
			b2Vec2 extents = fixture->GetAABB( 0 ).GetExtents();
			
			agraph::pushMatrix();
				agraph::translate( center.x, center.y );
				agraph::rotate2D(  this->body->GetAngle() );
				ss->render( currIndex );
			agraph::popMatrix();
		}
	}

protected:
	agraph::SpriteSheet* ss;
	std::map< AnimStates, AnimState > states;
	int currIndex = 0;
	AnimStates currState = IDLE;
	int vel = 1000000;
};


int main( int argc, char* argv[] )
{
	antic::Engine engine;
	if( engine.init("TiledExample", 1024, 768, 60, b2Vec2( 0, 16 * 20 ) ) == false )
		exit( EXIT_FAILURE );

	antic::TiledLevel level;
	if( level.init("res/Test1.tmx") == false )
		exit( EXIT_FAILURE );

	antic::DEntity* entity = new antic::DEntity;
	entity->setTexture( agraph::TextureFactory::loadTexture("res/exterior-parallaxBG1.png") );
	if( entity->getTexture() == nullptr )
	{
		printf("Error initializing entity\n");
		exit( EXIT_FAILURE );
	}

	entity->setBody( antic::createBodyDynamic( 200, 20, entity->getTexture()->getWidth(), entity->getTexture()->getHeight(), 10.0f, 0.3f ) );

	Elisa* elisa = new Elisa;
	if( elisa->init() == false ){
		printf("Failed to initialize Elisa\n");
		exit( EXIT_FAILURE );
	}

	antic::GameState* gs = new antic::GameState;
	gs->entityManager->addEntity( entity );
	gs->entityManager->addEntity( elisa );


	antic::StateManager* sm = new antic::StateManager;
	gs->addToLog<antic::SystemEvent>( sm );
	elisa->addToLog<antic::SystemEvent>( gs );
	sm->addToLog( &engine );

	sm->pushState( gs );

	engine.setStateManager( sm );

	bool quit = false;
	while( quit == false )
	{
		while( SDL_PollEvent( &engine.event ) )
		{
			if( engine.event.type == SDL_QUIT )
				quit = true;

			antic::SystemEvent *sysEvent = new antic::SystemEvent;
			sysEvent->event = engine.event;
			engine.push_event( sysEvent );
		}

		engine.update();
		
		level.render();
		engine.render();
	}

	engine.close();
}