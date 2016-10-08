#include "TestScreen.h"
#include <FlipdotConfig.h>

TestScreen::TestScreen(IFlipdotGfx& gfx)
  : _gfx(gfx)
{
}

TestScreen::~TestScreen()
{
}

void TestScreen::init(unsigned ticks)
{
	_tNextStep = ticks + 1000;
}

void TestScreen::update(unsigned ticks)
{
	if (ticks < _tNextStep)
	{
		return;
	}
	_tNextStep = ticks + STEP_INTERVAL;

	if (++_pointX >= SCREEN_WIDTH)
	{
		_pointX = 0;
	}

	if (++_pointY >= SCREEN_HEIGHT)
	{
		_pointY = 0;
	}

	_gfx.clear();
	_gfx.setPixel(_pointX, _pointY, true);


}

