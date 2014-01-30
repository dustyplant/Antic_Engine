#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H

#include <Antic/Drawable.h>
#include <vector>
#include <algorithm>

namespace antic
{
	class RenderQueue
	{
	public:
		virtual ~RenderQueue();
		virtual bool init( int numberOfLayers );
		virtual void render();
		virtual void insert( Drawable* );

		virtual int getLayersSize();
		virtual void clear();
	private:
		// The rendering layers.
		std::vector< std::vector<Drawable*> > layers;
	};
}

#endif