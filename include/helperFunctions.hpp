#pragma once
#include <config.hpp>

int getVectorIndex(int row,int col)
{
	return row * COLS + col;
}