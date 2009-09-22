/* 
 * File:   main.cpp
 * Author: walle
 *
 * Created on August 19, 2009, 7:52 PM
 */

#include <iostream>
#include <string>
#include <stdlib.h>

#include "cMineField.h"

/*
 * 
 */
int main(int argc, char** argv)
{
    srand(time(0));
    bool done = false;
  
    consoleMine::MineField* field = new consoleMine::MineField(10, 10, 10, rand());

    std::string inp;

    std::cout << "Instructions" << std::endl;
    std::cout << "e)xamine, f)lag, q)uit" << std::endl;

    while (!done)
    {
        // Draw the current minefield
        field->render();

        std::cin >> inp;
        
        if (inp == "quit" || inp == "q")
        {
            done = true;
        }
        else if (inp == "examine" || inp == "e" || inp == "flag" || inp == "f")
        {
            int x= 0;

            std::cout << "X:";
            std::cin >> x;

            if(x < 0 || x >= field->getWidth())
            {
                std::cerr << "X value is out-of-bounds" << std::endl;
                continue;
            }

            int y = 0;
            std::cout << "Y:";
            std::cin >> y;

            if (y < 0 || y >= field->getHeight())
            {
                std::cerr << "Y value is out-of-bounds" << std::endl;
                continue;
            }

            if (inp == "examine" || inp == "e")
            {
                done = field->open(x, y);
            }
            else if(inp == "flag" || inp == "f")
            {
                field->flag(x, y);
            }

            if (field->win())
            {
                std::cout << "You win!" << std::endl;

                // Draw the winning minefield
                field->render();

                done = true;
            }
        }
    }

    delete field;

    return 0;
}

