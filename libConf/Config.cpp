/* 
 * File:   Config.cpp
 * Author: walle
 * 
 * Created on August 31, 2009, 6:26 PM
 */

#include "Config.h"

namespace libConf
{
    Config::Config()
    {
        this->separator = "=";
        this->isLoaded = false;
        this->isChanged = false;
    }

    Config::Config(std::string separator)
    {
        this->separator = separator;
        this->isLoaded = false;
        this->isChanged = false;
    }

    Config::~Config()
    {
        this->values.clear();
    }
}

