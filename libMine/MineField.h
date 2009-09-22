/* 
 * File:   MineField.h
 * Author: walle
 *
 * Created on August 19, 2009, 7:19 AM
 */

#ifndef _MINEFIELD_H
#define	_MINEFIELD_H

#include "Cell.h"

namespace libMine
{
    class MineField
    {
    public:
        MineField(int width, int height, int numMines, int seed);
        virtual ~MineField();

        /**
         * The rendering is implemented by subclass
         */
        virtual void render() = 0;

        /**
         * Test a cell for mine
         */
        CellState examine(int x, int y);

        /**
         * Toggle a flag a cell at a specific point
         */
        bool flag(int x, int y);

        /**
         * Get the state in a given point
         */
        CellState getState(int x, int y);

        /**
         * Get the number of cells
         */
        int getNumCells() { return this->numCells; }

        /**
         * Get the width
         */
        int getWidth() { return this->width; }

        /**
         * Get the height
         */
        int getHeight() { return this->height; }

        /**
         * Returns the number of mines not yet discovered
         */
        //int numRemainingMines() { return this->numMinesLeft; /* TODO: Add functionality to calculate the flas etc. */ }
        //TODO: Remove?

        /**
         * Checks if the board is in winning location
         */
        bool win() { return (this->numClosedCells == this->numMines); }

        /**
         * Opens all cells, usually used for when the player steps on a mine
         */
        void openAll();

        /**
         * Flags all mines, usually used when the player wins
         */
        void flagAllMines();

    protected:
        void init();
        
        std::vector<Cell*> field;
        int numMines;
        int numFlags;
        int numCells;
        int numClosedCells;
        int width; // In cells
        int height; // In cells
        int seed; // Used to generate the same field
    };
} // libMine

#endif	/* _MINEFIELD_H */

