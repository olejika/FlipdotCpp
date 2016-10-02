#pragma once

#include "IFlipdotFramebuffer.h"

class IFlipdotGfx
{
	public:
		IFlipdotGfx() {}
		virtual ~IFlipdotGfx() {}

		virtual void clear() = 0;
		virtual void setPixel(unsigned x, unsigned y, bool value) = 0;
		virtual void drawRect(unsigned x, unsigned y, unsigned dx, unsigned dy, bool value) = 0;
		virtual void drawChar(unsigned x, unsigned y, char ch, bool value) = 0;

};
