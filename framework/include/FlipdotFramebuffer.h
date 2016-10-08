#pragma once

#include <stdint.h>

#include <FlipdotConfig.h>
#include "IFlipdotDriver.h"
#include "FlipdotPanel.h"

class FlipdotFramebuffer
{
	public:
		FlipdotFramebuffer(IFlipdotDriver &driver);

		void configurePanel(unsigned panelNumber, unsigned x, unsigned y, FlipdotPanel::Orientation orientation);
		void init();
		void update(unsigned ticks);

		void flush();

		void clear();
		void setPixel(unsigned x, unsigned y, bool value);
		bool getPixel(unsigned x, unsigned y);


	private:
		static const unsigned DOT_FLIP_TIME_MS = 15;

		enum class Color {
			WHITE,
			BLACK
		};

		IFlipdotDriver &_driver;
		FlipdotPanel _panels[NUM_PANELS];
		ScreenBuffer _offScreenBuffer;
		ScreenBuffer _onScreenBuffer;

		uint32_t _currentColumn = 0;
		uint32_t _tWaitDotsFlip = 0;

		void selectColumn(unsigned column);
		void updateColumn(Color color, unsigned column);
		void flushColor(Color color);

};

