/* 
 * File:   FileConfig.cpp
 * Author: walle
 * 
 * Created on August 31, 2009, 6:47 PM
 */

#include <iostream>

#include "FileConfig.h"

namespace libConf
{
    FileConfig::FileConfig(std::string filename) : Config()
    {
        this->filename = filename;
    }

    FileConfig::FileConfig(std::string filename, std::string separator) : Config(separator)
    {
        this->filename = filename;
    }

    FileConfig::~FileConfig()
    {
        if (this->isChanged && this->isLoaded)
        {
            this->save();
        }
    }

    void FileConfig::load()
    {
        std::string line;
        std::ifstream file;

        file.open(this->filename.c_str());

        if (file.is_open())
        {
            while(!file.eof())
            {
                std::getline(file, line);
                int pos = line.find_first_of(this->separator);
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos+1, line.size());

                this->values.insert(this->values.end(), std::pair<std::string,std::string>(key, value));
            }
        }

        file.close();

        this->isLoaded = true;

        // TODO: Implement file loading
        /*
        this->values.insert(this->values.end(), std::pair<std::string,std::string>("width", "10"));
        this->values.insert(this->values.end(), std::pair<std::string,std::string>("height", "10"));
        this->values.insert(this->values.end(), std::pair<std::string,std::string>("mines", "10"));
        this->values.insert(this->values.end(), std::pair<std::string,std::string>("cellwidth", "24"));
        this->values.insert(this->values.end(), std::pair<std::string,std::string>("seed", "32532"));
       */
    }

    void FileConfig::save()
    {
        std::ofstream file;

        file.open(this->filename.c_str());

        for(std::map<std::string, std::string>::iterator i = this->values.begin(); i != this->values.end(); i++)
        {
            file << i->first << this->separator << i->second << std::endl;
        }

        file.close();
    }
}