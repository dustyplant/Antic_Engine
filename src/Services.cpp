/*
#include <Antic/Services.h>

antic::Services::~Services()
{
	close();
}

bool antic::Services::init()
{
	close();

	engineVars = new EngineVars();
	if( engineVars == nullptr )
	{
		printf("Error: Services could not load EngineVars.\n");
		close();
		return false;
	}

	return true;
}

void antic::Services::close()
{
	if( engineVars != nullptr )
	{
		delete engineVars;
		engineVars = nullptr;
	}
}

antic::EngineVars * antic::Services::getEngineVars()
{
	return engineVars;
}
*/