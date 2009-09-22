#include "cMineField.h"

#include <iostream>

namespace consoleMine
{
    MineField::MineField(int width, int height, int numMines, int seed) : libMine::MineField(width, height, numMines, seed)
    {

    }

    MineField::~MineField()
    {
        // Only run parent, by virtual
    }

    bool MineField::open(int x, int y)
    {
        libMine::CellState res = this->examine(x, y);

        switch (res)
        {
            case libMine::MINE:
                std::cout << "Boom!" << std::endl << "Game Over!" << std::endl;

                // Reveal all the mines
                this->openAll();

                // Draw the loosing minefield
                this->render();

                return true;
            break;
            case libMine::OPEN:
                std::cout << "The cell (" << x << ", " << y << ") is open" << std::endl;
            break;
            case libMine::ALREADYOPEN:
                std::cout << "The cell (" << x << ", " << y << ") is already opened" << std::endl;
            break;
            case libMine::FLAG:
                std::cout << "The cell (" << x << ", " << y << ") is flagged" << std::endl;
            break;
            // Closed meens error in this context, not allowed
            case libMine::CLOSED:
            case libMine::ERROR:
                std::cout << "Error!" << std::endl;
            break;
            default:
                /*
                 * ONE,
                 * TWO,
                 * THREE,
                 * FOUR,
                 * FIVE,
                 * SIX,
                 * SEVEN,
                 * EIGHT
                 */
                std::cout << "The cell (" << x << ", " << y << ") has " << res << " adjecent mines" << std::endl;
            break;
        }

        return false;
    }

    void MineField::render()
    {
        for (int y = -2; y < this->getHeight(); y++)
        {
           for (int x = -1; x < this->getWidth(); x++)
           {
               if (y == -2 && x == -1)
               {
                   std::cout << "   ";
                   continue;
               }
               else if (y == -2)
               {
                   std::cout << x << " ";
                   continue;
               }
               else if (y == -1)
               {
                   std::cout << "--";
                   continue;
               }
               else if(x == -1)
               {
                   std::cout << y << "| ";
                   continue;
               }
               libMine::CellState state = this->getState(x, y);
               switch (state)
               {
                   case libMine::OPEN:
                       std::cout << "0";
                   break;
                   case libMine::FLAG:
                       std::cout << "F";
                   break;
                   case libMine::MINE:
                       std::cout << "M";
                   break;
                   case libMine::CLOSED:
                       std::cout << "X";
                   break;
                   default:
                       std::cout << state;
                   break;
               }

               // Space out the field some in the x direction
               std::cout << " ";
           }

           std::cout << std::endl;
        }
    }
}
