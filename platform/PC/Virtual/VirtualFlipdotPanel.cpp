#include "VirtualFlipdotPanel.h"

VirtualFlipdotPanel::VirtualFlipdotPanel()
  : _offScreenBuffer { false },
	_onScreenBuffer { false },
	_columnShiftRegister {0},
	_selectedColumn(0)
{
}

VirtualFlipdotPanel::~VirtualFlipdotPanel()
{
}

void VirtualFlipdotPanel::selectColumn(uint8_t column)
{
	_selectedColumn = column;
}

void VirtualFlipdotPanel::shiftInputColumnByte(uint8_t data)
{
	for (unsigned i=sizeof(_columnShiftRegister)-1; i>0; i--)
	{
		_columnShiftRegister[i] = _columnShiftRegister[i-1];
	}
	_columnShiftRegister[0] = data;
}

uint8_t VirtualFlipdotPanel::getOutputColumnByte()
{
	return _columnShiftRegister[COLUMN_OUTPUT_BYTE];
}

void VirtualFlipdotPanel::strobe()
{
	static const uint8_t map[] = { 20,21,22,23, 8, 9,10,11,12,13, 14,15, 0, 1, 2, 3, 4, 5, 6, 7};

	for (unsigned row=0; row<ACTIVE_ROWS; row++)
	{
		unsigned mapped_row = map[row];
		unsigned byte_num = mapped_row / 8;
		uint8_t bit_mask = 1<<(mapped_row % 8);
		bool value = (_columnShiftRegister[byte_num] & bit_mask) != 0;

		setBufferBit(_offScreenBuffer, _selectedColumn, row, value);
	}
}

void VirtualFlipdotPanel::setOutputEnableBlack()
{
	for (unsigned row=0; row<ACTIVE_ROWS; row++)
	{
		if (getBufferBit(_offScreenBuffer, _selectedColumn, row))
		{
			setBufferBit(_onScreenBuffer, _selectedColumn, row, true);
		}
	}
}

void VirtualFlipdotPanel::setOutputEnableWhite()
{
	for (unsigned row=0; row<ACTIVE_ROWS; row++)
	{
		if (!getBufferBit(_offScreenBuffer, _selectedColumn, row))
		{
			setBufferBit(_onScreenBuffer, _selectedColumn, row, false);
		}
	}
}

bool VirtualFlipdotPanel::getDotColor(unsigned x, unsigned y)
{
	return getBufferBit(_onScreenBuffer, x, y);
}

void VirtualFlipdotPanel::setBufferBit(buffer_t& buffer, unsigned x, unsigned y, bool value)
{
	buffer[x*ACTIVE_ROWS + y] = value;
}

bool VirtualFlipdotPanel::getBufferBit(buffer_t& buffer, unsigned x, unsigned y)
{
	return buffer[x*ACTIVE_ROWS + y];
}
