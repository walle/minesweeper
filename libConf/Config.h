/* 
 * File:   Config.h
 * Author: walle
 *
 * Created on August 31, 2009, 6:26 PM
 */

#ifndef _CONFIG_H
#define	_CONFIG_H

#include <string>
#include <sstream>
#include <map>
#include <algorithm>

namespace libConf
{
    class Config
    {
    public:
        Config();
        Config(std::string separator);
        virtual ~Config();
        
        /**
         * Returns the separator
         */
        std::string getSeparator() { return separator; }    
        
        /**
         * Load the values
         */
        virtual void load() = 0;
        
        /**
         * Save the values back to the file
         */
        virtual void save() = 0;
        
        /**
         * Read the value
         */
        std::string read(std::string key) { return this->values.at(key); }

        /**
         * Return a in from the key
         * TODO: This is completely wrong, fix nice string to int function
         */
        int readInt(std::string key) { return std::atoi(this->values.at(key).c_str()); }
        
        /**
         * Bind the value to key, overwrites the existing value if any
         */
        void set(std::string key, std::string value) { this->isChanged = true; this->values.at(key) = value; }
        
        /**
         * Checks if a key exists
         */
        bool exists(std::string key) { if(this->values.at(key) != "") { return true; } else { return false; } }

    protected:
        std::map<std::string, std::string> values;
        std::string separator;
        bool isLoaded;
        bool isChanged;
    };
}

#endif	/* _CONFIG_H */

