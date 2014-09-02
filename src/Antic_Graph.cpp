#include <Antic/Antic_Graph.h>

bool AGraph::initAGraph( std::string title, int width, int height )
{
	AGraph::window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN );
	if( window == nullptr )
		return false;

	AGraph::renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC */);
	if( renderer == nullptr )
		return false;

	if( SDL_SetRenderDrawBlendMode( AGraph::renderer, SDL_BLENDMODE_BLEND ) < 0 )
		return false;

	SDL_RenderClear( AGraph::renderer );

	if( TTF_Init() == -1 )
		return false;

	return true;
}

void AGraph::cleanup()
{
	AGraph::clearTextureMap();
	AGraph::clearFontMap();
	AGraph::clearColorMap();

	SDL_DestroyRenderer( AGraph::renderer );
	SDL_DestroyWindow( AGraph::window );
	TTF_Quit();
	SDL_Quit();
}

void AGraph::clearTextureMap()
{
	for( std::map< std::string, SDL_Texture* >::iterator iter = AGraph::textureMap.begin(); iter != AGraph::textureMap.end(); iter++ )
	{
		SDL_DestroyTexture( iter->second );
	}
	AGraph::textureMap.clear();
}

void AGraph::clearFontMap()
{
	for( std::map< std::string, TTF_Font* >::iterator iter = AGraph::fontMap.begin(); iter != AGraph::fontMap.end(); iter++ )
	{
		TTF_CloseFont( iter->second );
	}
	AGraph::fontMap.clear();
}

void AGraph::clearColorMap()
{
	AGraph::colorMap.clear();
}

SDL_Texture *AGraph::loadImage( std::string path, Uint8 r, Uint8 g, Uint8 b )
{
	SDL_Surface *surface = IMG_Load( path.c_str() );
	if( surface == nullptr )
		return nullptr;

	Uint32 colorkey = SDL_MapRGB(surface->format, r, g, b );
	SDL_SetColorKey( surface, SDL_TRUE, colorkey );

	SDL_Texture *texture = nullptr;
	texture = SDL_CreateTextureFromSurface( AGraph::renderer, surface );
	SDL_FreeSurface( surface );

	return texture;
}

SDL_Texture *AGraph::loadImage( std::string path )
{
	return IMG_LoadTexture( AGraph::renderer, path.c_str() );
}

SDL_Texture *AGraph::loadImage( std::string path, SDL_Color &color )
{
	return loadImage( path, color.r, color.g, color.b );
}

bool AGraph::loadImage( std::string name, std::string path )
{
	bool loaded = true;
	if( AGraph::textureMap[ name ] == nullptr )
	{
		AGraph::textureMap[ name ] = AGraph::loadImage( path );
		if( AGraph::textureMap[ name ] == nullptr )
			loaded = false;
	}
	return loaded;
}

bool AGraph::loadImage( std::string name, std::string path, Uint8 r, Uint8 g, Uint8 b )
{
	bool loaded = true;
	if( AGraph::textureMap[ name ] == nullptr )
	{
		AGraph::textureMap[ name ] = AGraph::loadImage( path, r, g, b );
		if( AGraph::textureMap[ name ] == nullptr )
			loaded = false;
	}
	return loaded;
}

bool AGraph::loadImage( std::string name, std::string path, std::string color )
{
	SDL_Color tempColor = AGraph::getColor( color );
	return AGraph::loadImage( name, path, tempColor );
}

bool AGraph::loadImage( std::string name, std::string path, SDL_Color &color )
{
	return AGraph::loadImage( name, path, color.r, color.g, color.b );
}

void AGraph::render( SDL_Texture *texture, int x, int y, SDL_Rect *clip, const double angle, const SDL_Point *centerRotate )
{
	static SDL_Rect pos;
	pos.x = x;
	pos.y = y;

	if( clip != nullptr ){
		pos.w = clip->w;
		pos.h = clip->h;
	}
	else
		SDL_QueryTexture( texture, nullptr, nullptr, &pos.w, &pos.h );

	SDL_RenderCopyEx( AGraph::renderer, texture, clip, &pos, angle, centerRotate, SDL_FLIP_NONE );
}

void AGraph::renderDone()
{
	SDL_RenderPresent( AGraph::renderer );
	SDL_RenderClear( AGraph::renderer );
}

void AGraph::render( std::string words, int x, int y, SDL_Rect *clip, const double angle, const SDL_Point *centerRotate )
{
	AGraph::render( getTexture( words ), x, y, clip, angle, centerRotate );
}

SDL_Texture* AGraph::getTexture( std::string name )
{
	return AGraph::textureMap.at( name );
}

bool AGraph::loadFont( std::string name, std::string path, int fontSize )
{
	bool loaded = false;
	if( AGraph::fontMap[ name ] == nullptr )
	{		
		AGraph::fontMap[ name ] = AGraph::loadFont( path, fontSize );
		if( AGraph::fontMap[ name ] != nullptr )
			loaded = true;
	}
	return loaded;
}

TTF_Font *AGraph::loadFont( std::string path, int fontSize )
{
	return TTF_OpenFont( path.c_str(), fontSize );
}

TTF_Font *AGraph::getFont( std::string name )
{
	return fontMap.at( name );
}

bool AGraph::loadWords( std::string name, std::string words, std::string fontName, std::string colorName )
{
	return AGraph::loadWords( name, words, getFont( fontName ), getColor( colorName ) );
}

bool AGraph::loadWords( std::string name, std::string words, TTF_Font* font, std::string colorName )
{
	return AGraph::loadWords( name, words, font, getColor( colorName ) );
}


bool AGraph::loadWords( std::string name, std::string words, std::string fontName, SDL_Color color )
{
	return AGraph::loadWords( name, words, getFont( fontName ), color );
}

bool AGraph::loadWords( std::string name, std::string words, TTF_Font* font, SDL_Color color )
{
	bool loaded = false;
	if( AGraph::textureMap[ name ] == nullptr )
	{
		SDL_Surface *surface = TTF_RenderText_Blended( font, words.c_str(), color );
		AGraph::textureMap[ name ] = SDL_CreateTextureFromSurface( renderer, surface );
		if( AGraph::textureMap[ name ] != nullptr )
			loaded = true;
		SDL_FreeSurface( surface );
	}
	return loaded;
}

bool AGraph::loadColor( std::string name, Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
	SDL_Color newColor = { r, g, b, a };
	return loadColor( name, newColor );
}

bool AGraph::loadColor( std::string name, SDL_Color newColor )
{
	AGraph::colorMap[ name ] = newColor;
	return true;
}

SDL_Color AGraph::getColor( std::string name )
{
	return AGraph::colorMap.at( name );
}

void AGraph::getWindowSize( int &w, int &h )
{
	SDL_GetWindowSize( window, &w, &h );
}


void AGraph::drawRect( int x, int y, int w, int h )
{
	SDL_Rect tempRect = { x, y, w, h };
	AGraph::drawRect( &tempRect );
}
void AGraph::drawRect( int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
	SDL_SetRenderDrawColor( AGraph::renderer, r, g, b, a );
	AGraph::drawRect( x, y, w, h );
	SDL_SetRenderDrawColor( AGraph::renderer, 0, 0, 0, 255 );
}
void AGraph::drawRect( SDL_Rect *rect )
{
	SDL_RenderFillRect( AGraph::renderer, rect );
}
void AGraph::drawRect( SDL_Rect *rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
	SDL_SetRenderDrawColor( AGraph::renderer, r, g, b, a );
	AGraph::drawRect( rect );
	SDL_SetRenderDrawColor( AGraph::renderer, 0, 0, 0, 255 );
}

void AGraph::drawLine( int x1, int y1, int x2, int y2 )
{
	SDL_RenderDrawLine( AGraph::renderer, x1, y1, x2, y2 );
}
void AGraph::drawLine( int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
	SDL_SetRenderDrawColor( AGraph::renderer, r, g, b, a );
	AGraph::drawLine( x1, y1, x2, y2 );
	SDL_SetRenderDrawColor( AGraph::renderer, 0, 0, 0, 255 );
}