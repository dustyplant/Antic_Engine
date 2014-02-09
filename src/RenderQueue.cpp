#include <Antic/RenderQueue.h>

antic::RenderQueue::~RenderQueue()
{
	clear();
}

bool antic::RenderQueue::init( int numberOfLayers )
{
	clear();	
	layers.resize( numberOfLayers );
	for( int i = 0; i < layers.size(); i++ )
	{
		std::make_heap( layers[i].begin(), layers[i].end() );
	}
}

void antic::RenderQueue::render()
{
	for( int i = layers.size() - 1; i >= 0; --i )
	{
		while( layers[i].empty() == false )
		{
			if( layers[i].front() != nullptr )
				layers[i].front()->render();
			std::pop_heap( layers[i].begin(), layers[i].end() );
			layers[i].pop_back();
		}
	}
}

void antic::RenderQueue::insert( Drawable* obj )
{
	if( obj != nullptr && obj->layer > 0 && obj->layer < layers.size() )
	{
		layers[ obj->layer ].push_back( obj );
		std::push_heap( layers[ obj->layer ].begin(), layers[ obj->layer ].end() );
	}
}

int antic::RenderQueue::getLayersSize()
{
	return layers.size();
}

void antic::RenderQueue::clear()
{
	layers.clear();
}