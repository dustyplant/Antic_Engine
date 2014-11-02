#include <Antic/Component.h>
#include <Antic/ComponentPhysics.h>
#include <Antic/Entity.h>
#include <Antic/TiledLevel.h>


antic::ComponentPhysics::ComponentPhysics()
{
	id = 1;

	dx = 0;
	dy = 0;
	dg = 16;
	maxFallSpeed = 256;
	width = 16;
	height = 16;
	level = nullptr;
}

antic::ComponentPhysics::~ComponentPhysics()
{

}

bool antic::ComponentPhysics::init(antic::TiledLevel * level)
{
	this->level = level;
	return true;
}

void antic::ComponentPhysics::update(float dt, Entity *me)
{
	collision = false;
	onGround = false;
	collisionList.clear();

	dy += dg*dt;

	// if(dy > maxFallSpeed)
	// 	dy = maxFallSpeed;

	me->x += dx * dt;
	me->y += dy * dt;
	int layer = 1;
	tile t;

	//check for vertical collisions
	if(dy >0) {
		t.x = me->x/16;
		t.y = me->y/16+1;
		if(level->getTile(t.x, t.y, layer) > 0 &&
			level->getTile(t.x+1, t.y, layer) > 0) {
			me->y = t.y*16 - 16.1;
			dy = 0;
			collision = true;
			onGround = true;
		}
	} else if(dy < 0) {
		t.x = me->x/16;
		t.y = me->y/16;
		if(level->getTile(t.x, t.y, layer) > 0 &&
			level->getTile(t.x+1, t.y, layer) > 0) {
			me->y = t.y*16 + 16;
			dy = 0;
			collision = true;
		}
	}

	//check for horizontal collisions
	if(dx >0) {
		t.x = me->x/16+1;
		t.y = me->y/16;
		if(level->getTile(t.x, t.y, layer) > 0 &&
			level->getTile(t.x, t.y+1, layer) > 0) {
			me->x = t.x*16 - 16;
			dx = 0;
			collision = true;
		}
	} else if(dx < 0) {
		t.x = me->x/16;
		t.y = me->y/16;
		if(level->getTile(t.x, t.y, layer) > 0 &&
			level->getTile(t.x, t.y+1, layer) > 0) {
			me->x = t.x*16 + 16;
			dx = 0;
			collision = true;
		}
	}


	t.x = me->x/16;
	t.y = me->y/16;
	t.id = level->getTile(t.x, t.y, layer);
	if(t.id > 0) {
		collision = true;
		float cent_x = me->x + width/2;
		float cent_y = me->y + height/2;
		float cent_tile_x = t.x*16+8;
		float cent_tile_y = t.y*16+8;
		float dx_sq = ((cent_x-cent_tile_x)*(cent_x-cent_tile_x));
		float dy_sq = ((cent_y-cent_tile_y)*(cent_y-cent_tile_y));
		if(dx_sq > dy_sq) {
			//move on x to avoid collision
			if(dx > 0) {
				//me->x = t.x*16-16;
			} else {
				me->x = t.x*16+16;
				dx = 0;
			}
		} else {
			//move on y to avoid collision
			if(dy > 0) {
				//me->y = t.y*16-16;
			} else {
				me->y = t.y*16+16;
				onGround = true;
				dy = 0;
			}
		}
	}
	t.x = me->x/16+1;
	t.y = me->y/16;
	t.id = level->getTile(t.x, t.y, layer);
	if(t.id > 0) {
		collision = true;
		float cent_x = me->x + width/2;
		float cent_y = me->y + height/2;
		float cent_tile_x = t.x*16+8;
		float cent_tile_y = t.y*16+8;
		float dx_sq = ((cent_x-cent_tile_x)*(cent_x-cent_tile_x));
		float dy_sq = ((cent_y-cent_tile_y)*(cent_y-cent_tile_y));
		if(dx_sq > dy_sq) {
			//move on x to avoid collision
			if(dx > 0) {
				me->x = t.x*16-16;
				dx = 0;
			} else {
				//me->x = t.x*16+16;
			}
		} else {
			//move on y to avoid collision
			if(dy > 0) {
				//me->y = t.y*16-16;
			} else {
				me->y = t.y*16+16;
				dy = 0;
			}
		}
	}
	t.x = me->x/16;
	t.y = me->y/16+1;
	t.id = level->getTile(t.x, t.y, layer);
	if(t.id > 0) {
		collision = true;
		float cent_x = me->x + width/2;
		float cent_y = me->y + height/2;
		float cent_tile_x = t.x*16+8;
		float cent_tile_y = t.y*16+8;
		float dx_sq = ((cent_x-cent_tile_x)*(cent_x-cent_tile_x));
		float dy_sq = ((cent_y-cent_tile_y)*(cent_y-cent_tile_y));
		//std::cout << dx_sq  << ' ' << dy_sq << '\n';
		if(dx_sq > dy_sq) {
			//move on x to avoid collision
			if(dx > 0) {
				//me->x = t.x*16-16;
			} else {
				me->x = t.x*16+16;
				dx = 0;
			}
		} else {
			//move on y to avoid collision
			if(dy > 0) {
				me->y = t.y*16-16;
				dy = 0;
				collision = true;
				onGround = true;
			} else {
				//me->y = t.y*16+16;
			}
		}
	}
	t.x = me->x/16+1;
	t.y = me->y/16+1;
	t.id = level->getTile(t.x, t.y, layer);
	if(t.id > 0) {
		collision = true;
		float cent_x = me->x + width/2;
		float cent_y = me->y + height/2;
		float cent_tile_x = t.x*16+8;
		float cent_tile_y = t.y*16+8;
		float dx_sq = ((cent_x-cent_tile_x)*(cent_x-cent_tile_x));
		float dy_sq = ((cent_y-cent_tile_y)*(cent_y-cent_tile_y));
		if(dx_sq > dy_sq) {
			//move on x to avoid collision
			if(dx > 0) {
				me->x = t.x*16-16;
				dx = 0;
			} else {
				//me->x = t.x*16+16;
			}
		} else {
			//move on y to avoid collision
			if(dy > 0) {
				me->y = t.y*16-16;
				dy = 0;
				collision = true;
				onGround = true;
			} else {
				//me->y = t.y*16+16;
			}
		}
	}


	//move to avoid a collision
	// for(auto t : collisionList) {
	// 	float cent_x = me->x + width/2;
	// 	float cent_y = me->y + height/2;
	// 	float cent_tile_x = t.x*16+8;
	// 	float cent_tile_y = t.y*16+8;
	// 	float dx_sq = ((cent_x-cent_tile_x)*(cent_x-cent_tile_x));
	// 	float dy_sq = ((cent_y-cent_tile_y)*(cent_y-cent_tile_y));
	// 	if(dx_sq > dy_sq) {
	// 		//move on x to avoid collision
	// 		if(dx > 0) {
	// 			me->x = t.x*16-1;
	// 		} else {
	// 			me->x = t.x*16+1;
	// 		}
	// 	} else {
	// 		//move on y to avoid collision
	// 		if(dy > 0) {
	// 			me->y = t.y*16-1;
	// 		} else {
	// 			me->y = t.y*16+1;
	// 		}
	// 	}
	// }
}

void antic::ComponentPhysics::setVelocity( float dx, float dy)
{
	this->dx = dx;
	this->dy = dy;
}

void antic::ComponentPhysics::setSize(float width, float height)
{
	this->width = width;
	this->height = height;
}

void antic::ComponentPhysics::setGravity(float gravity)
{
	dg = gravity;
}