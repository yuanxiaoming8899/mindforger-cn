/*
 installer.h     MindForger thinking notebook

 Copyright (C) 2016-2018 Martin Dvorak <martin.dvorak@mindforger.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef M8R_INSTALLER_H
#define M8R_INSTALLER_H

#include <dirent.h>

#include <string>
#include <iostream>

#include "../config/configuration.h"
#include "../gear/file_utils.h"
#include "../exceptions.h"

namespace m8r {

class Installer
{
public:
    explicit Installer();
    Installer(const Installer&) = delete;
    Installer(const Installer&&) = delete;
    Installer &operator=(const Installer&) = delete;
    Installer &operator=(const Installer&&) = delete;
    ~Installer();

    /**
     * @brief Create empty MindForger repository.
     *
     * Creates the directory and the skeleton of empty repository in it.
     */
    void createEmptyMindForgerRepository(const std::string& directory);

    /**
     * @brief Check whether directory contains a MindForger repository.
     */
    bool isMindForgerRepository(const std::string& directory);

private:
    void createDirectory(const std::string& path);
};

}
#endif // M8R_INSTALLER_H