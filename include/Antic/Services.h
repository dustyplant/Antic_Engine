#ifndef SERVICES_H
#define SERVICES_H

#include <Antic/EngineVars.h>

namespace antic
{
	class Services
	{
	public:
		virtual ~Services();

		virtual bool init();
		void close();

		EngineVars *getEngineVars();

	private:
		antic::EngineVars* engineVars = nullptr;
	};
}

#endif