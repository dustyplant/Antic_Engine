#include <Antic/EMGrid.h>
#include <iostream>

bool antic::Layer::init( int width, int height )
{
	entities.resize(height);

	for( auto &i: entities )
		i.resize(width, 0);

	if( entities.size() != height || entities.at(0).size() != width )
		return false;

	this->width = width;
	this->height = height;
	return true;
}

bool antic::Layer::update( unsigned int entityID, int toX, int toY, int fromX, int fromY, bool overwrite )
{
	bool success = update( entityID, toX, toY, overwrite );
	if( success && getFromLayer( fromX, fromY ) == entityID )
		entities[fromY][fromX] = 0;
	return success;
}
bool antic::Layer::update( unsigned int entityID, int toX, int toY, bool overwrite )
{
	bool success = inBounds( toX, toY ) && ( overwrite || isOccupied( toX, toY ) == false );
	if( success )
		entities[toY][toX] = entityID;
	return success;
}

bool antic::Layer::isOccupied( int x, int y )
{
	return getFromLayer( x, y ) != 0 || inBounds( x, y ) == false;
}

bool antic::Layer::inBounds( int x, int y )
{
	return x >= 0 && x < getWidth() && y >= 0 && y < getHeight();
}

int antic::Layer::getWidth(){ return this->width; }
int antic::Layer::getHeight(){ return this->height; }

unsigned int antic::Layer::getFromLayer( int x, int y )
{
	return entities.at( y ).at( x );
}

antic::EMGrid::~EMGrid(){}

bool antic::EMGrid::init( int width, int height, int layers )
{
	bool success = antic::EntityManager::init();
	for( int i = 0; i < layers; ++i )
	{
		antic::Layer newLayer;
		if( newLayer.init( width, height ) == false )
			return false;
		this->layers.push_back( newLayer );
	}
	return success;
}

void antic::EMGrid::addEntity( antic::Entity *entity )
{
	antic::EntityManager::addEntity( entity );
	if( antic::GridEntity *ge = dynamic_cast<antic::GridEntity*>(entity) )
		layers.at( ge->gld.layer ).update( entity->getID(), ge->gld.x, ge->gld.y );
}

void antic::EMGrid::removeEntity( unsigned int entityID )
{
	antic::EntityManager::removeEntity( entityID );
	if( antic::GridEntity *ge = dynamic_cast<antic::GridEntity*>(getEntity(entityID)) )
		layers.at( ge->gld.layer ).update( 0, ge->gld.x, ge->gld.y );
}

antic::Entity* antic::EMGrid::getFromGrid( int x, int y, int layer )
{
	unsigned int found = layers.at(layer).isOccupied( x, y );
	return ( found ? getEntity(found) : nullptr );
}

antic::Layer* antic::EMGrid::getLayer( int layer )
{
	return &layers.at( layer );
}

void antic::EMGrid::update( float dt )
{
	antic::EntityManager::update( dt );
}

int antic::EMGrid::getLayers(){ return this->layers.size(); }

int antic::EMGrid::getWidth()
{
	if( this->layers.empty() )
		return 0;
	return this->layers.at(0).getWidth();
}

int antic::EMGrid::getHeight()
{
	if( this->layers.empty() )
		return 0;
	return this->layers.at(0).getWidth();
}

void antic::EMGrid::printGrid()
{
	for( auto i: layers )
	{
		for( int j = 0; j < 20; ++j )
		{
			for( int k = 0; k < 20; ++k ){
				unsigned int eid = i.getFromLayer( k, j );
				if( eid > 0 )
					printf("%4u", eid);
				else
					printf("    ");
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

void antic::GridEntity::setEntityManager( antic::EntityManager *newEM )
{
	if( this->em != nullptr ){
		delete this->em;
		this->em = nullptr;
	}

	if( this->emg != nullptr ){
		delete this->emg;
		this->emg = nullptr;
	}

	if( antic::EMGrid *emg = dynamic_cast<antic::EMGrid*>(newEM) ){
		antic::Entity::setEntityManager( newEM );
		this->emg = emg;
	}
}

void antic::GridEntity::move( int x, int y, bool overwrite, bool clearPrevious )
{
	antic::EMGrid *tempGrid = nullptr;
	if( this->emg != nullptr )
		tempGrid = this->emg;
	else
		tempGrid = dynamic_cast<antic::EMGrid*>( this->em );

	if( tempGrid != nullptr )
	{
		Layer *layer = tempGrid->getLayer( this->gld.layer );
		if( layer != nullptr )
		{
			bool success = false;
			if( clearPrevious )
				success = layer->update( this->getID(), x, y, this->gld.x, this->gld.y, overwrite );
			else
				success = layer->update( this->getID(), x, y, overwrite );

			if( success ){
				this->gld.x = x;
				this->gld.y = y;
			}
		}
	}
}

void antic::GridEntity::setGLD( int x, int y, int layer )
{
	if( layer >= 0 )
		this->gld.layer = layer;
	this->gld.x = x;
	this->gld.y = y;
}

void antic::GridEntity::setGLD( GridLocData &newGLD )
{
	antic::GridEntity::setGLD( newGLD.x, newGLD.y, newGLD.layer );
}