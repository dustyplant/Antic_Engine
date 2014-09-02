#ifndef EMGRID_H
#define EMGRID_H

#include <Antic/Entity.h>
#include <Antic/EntityManager.h>
#include <vector>

namespace antic
{
	class EMGrid;
	struct GridLocData
	{
		int x = 0;
		int y = 0;
		int layer = 0;
	};

	class GridEntity: public Entity
	{
	public:
		GridLocData gld;
		virtual void setEntityManager( EntityManager * );
		virtual void move( int x, int y, bool overwrite = false, bool clearPrevious = true );
		virtual void setGLD( int x, int y, int layer = -1 );
		virtual void setGLD( GridLocData &newGLD );

	protected:
		EMGrid *emg = nullptr;
	};

	class Layer
	{
	public:
		virtual bool init( int width, int height );
		virtual bool update( unsigned int entityID, int toX, int toY, int fromX, int fromY, bool overwrite = false );
		virtual bool update( unsigned int entityID, int toX, int toY, bool overwrite = false );
		virtual bool isOccupied( int x, int y );
		virtual unsigned int getFromLayer( int x, int y );

		bool inBounds( int x, int y );
		int getWidth();
		int getHeight();
	protected:
		std::vector< std::vector<unsigned int> > entities;
		int width;
		int height;
	};

	class EMGrid: public EntityManager
	{
	public:
		virtual ~EMGrid();
		virtual bool init( int width, int height, int layers = 1 );
		virtual void update( float dt );


		// Use these functions rather than the base EntityManager functions.
		virtual void addEntity( Entity* entity );
		virtual void removeEntity( unsigned int entityID );

		virtual Entity* getFromGrid( int x, int y, int layer = 0 );
		virtual Layer* getLayer( int layer = 0 );

		int getWidth();
		int getHeight();
		int getLayers();
		void printGrid();

	protected:
		std::vector<Layer> layers;

	};
}

#endif