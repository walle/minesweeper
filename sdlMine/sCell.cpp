#include "sCell.h"

namespace sdlMine
{
    Cell::Cell(int x, int y, bool mined, libMine::CellState state) : libMine::Cell(x, y, mined, state)
    {
        this->blink = false;
    }

    Cell::~Cell()
    {
        
    }
}
