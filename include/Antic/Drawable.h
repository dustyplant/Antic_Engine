#ifndef DRAWABLE_H
#define DRAWABLE_H

namespace antic
{
	class Drawable
	{
	public:
		virtual void render() = 0;
		int layer = 0;
		int priority = 0;
	};
}

#endif