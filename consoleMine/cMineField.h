/* 
 * File:   ConsoleMineField.h
 * Author: walle
 *
 * Created on August 25, 2009, 6:41 PM
 */

#ifndef _CONSOLEMINEFIELD_H
#define	_CONSOLEMINEFIELD_H

#include "MineField.h"

namespace consoleMine
{
    class MineField : public libMine::MineField
    {
    public:
        MineField(int width, int height, int numMines, int seed);
        virtual ~MineField();

        /**
         * Examine and handle the cell
         */
        bool open(int x, int y);

        /**
         * Render the field to the console
         */
        void render();
    };
}

#endif	/* _CONSOLEMINEFIELD_H */

