/* 
 * File:   FileConfig.h
 * Author: walle
 *
 * Created on August 31, 2009, 6:47 PM
 */

#ifndef _FILECONFIG_H
#define	_FILECONFIG_H

#include <fstream>

#include "Config.h"

namespace libConf
{
    class FileConfig : public Config
    {
    public:
        FileConfig(std::string filename);
        FileConfig(std::string filename, std::string separator);
        virtual ~FileConfig();

        /**
         * Returns the filename
         */
        std::string getFilename() { return filename; }

        /**
         * FileConfig implementation of load
         */
        void load();

        /**
         * FileConfig implementation of save
         */
        void save();

    private:
        std::string filename;
    };
}

#endif	/* _FILECONFIG_H */

