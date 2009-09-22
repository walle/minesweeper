/* 
 * File:   sCell.h
 * Author: walle
 *
 * Created on August 28, 2009, 7:46 AM
 */

#ifndef _SCELL_H
#define	_SCELL_H

#include "SDL/SDL.h"

#include "Cell.h"

namespace sdlMine
{
    class Cell : public libMine::Cell
    {
    public:
        Cell(int x, int y, bool mined, libMine::CellState state);
        virtual ~Cell();

        bool getBlink() { return this->blink; }
        void setBlink(bool value) { this->blink = value; }

    private:
        bool blink;
    };
}

#endif	/* _SCELL_H */

