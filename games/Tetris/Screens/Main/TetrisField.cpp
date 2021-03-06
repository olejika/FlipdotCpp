#include <Framebuffer.h>

#include "TetrisField.h"
#include "TetrisBlock.h"

void TetrisField::clear()
{
	for (int i=0; i<ROWS; i++)
	{
		_data[i] = 0;
	}
}

void TetrisField::setPoint(int fieldX, int fieldY, bool value)
{
	if ((fieldX<0) || (fieldX>=COLUMNS)) { return; }
	if ((fieldY<0) || (fieldY>=ROWS)) { return; }
	uint16_t bitmask = (1<<fieldX);
	if (value) {
		_data[fieldY] |= bitmask;
	} else {
		_data[fieldY] &= ~bitmask;
	}
}

bool TetrisField::isPointSet(int fieldX, int fieldY) const
{
	if (fieldY<0) { return false; }
	if (fieldY>=ROWS) { return true; }
	if ( (fieldX<0) || (fieldX >= COLUMNS) ) { return true; }
	return (_data[fieldY] & (1<<fieldX)) != 0;
}

bool TetrisField::hasFullRows() const
{
	for (int i=0; i<ROWS; i++)
	{
		if (isRowFull(i))
		{
			return true;
		}
	}
	return false;
}

bool TetrisField::isRowFull(int row) const
{
	if ( (row<0) || (row >= ROWS) ) {
		return false;
	} else {
		return (_data[row] & FULL_ROW_MASK) == FULL_ROW_MASK;
	}
}

int TetrisField::deleteFullRows()
{
	int deletedRows = 0;

	int i = ROWS-1;
	while (i>=0)
	{
		if (isRowFull(i)) {
			deleteRow(i);
			deletedRows++;
		} else {
			i--;
		}
	};

	return deletedRows;
}

void TetrisField::deleteRow(int row)
{
	for (int y=row; y>0; y--)
	{
		_data[y] = _data[y-1];
	}
	_data[0] = 0;
}

void TetrisField::draw(Framebuffer& fb, int x, int y, bool doInvert) const
{
	Rect r(0, 0, POINT_WIDTH, POINT_HEIGHT);
	for (int fieldY=0; fieldY<ROWS; fieldY++)
	{
		r.x = 0;
		r.y = fieldY*POINT_HEIGHT;
		bool invertThisRow = doInvert ^ (_invertFullRows && isRowFull(fieldY));
		for (int fieldX=0; fieldX<COLUMNS; fieldX++)
		{
			bool value = isPointSet(fieldX, fieldY) ^ invertThisRow;
			fb.draw(x, y, r, value);
			r.x += POINT_WIDTH;
		}
	}
}

void TetrisField::setDrawFullRowsInverted(bool doInvert)
{
	_invertFullRows = doInvert;
}
