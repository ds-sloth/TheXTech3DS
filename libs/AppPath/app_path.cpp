/*
 * Moondust, a free game engine for platform game making
 * Copyright (c) 2014-2020 Vitaly Novichkov <admin@wohlnet.ru>
 *
 * This software is licensed under a dual license system (MIT or GPL version 3 or later).
 * This means you are free to choose with which of both licenses (MIT or GPL version 3 or later)
 * you want to use this software.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You can see text of MIT license in the LICENSE.mit file you can see in Engine folder,
 * or see https://mit-license.org/.
 *
 * You can see text of GPLv3 license in the LICENSE.gpl3 file you can see in Engine folder,
 * or see <http://www.gnu.org/licenses/>.
 */

#include <DirManager/dirman.h>
#include <Utils/files.h>
#include <IniProcessor/ini_processing.h>
#define FMT_NOEXCEPT
#include <fmt/fmt_format.h>

#ifdef __gnu_linux__
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

#include "app_path.h"
// #include "../version.h"

// #include <SDL2/SDL.h>

std::string  ApplicationPathSTD;

std::string AppPathManager::m_settingsPath;
std::string AppPathManager::m_userPath;
bool AppPathManager::m_isPortable = false;

#define UserDirName "/3ds/thextech"

/**
 * @brief Retreive User Home directory with appending of the PGE user data directory
 * @return Absolute directory path
 */
static std::string getPgeUserDirectory()
{
    return UserDirName;
    // std::string path = "";
    // return path.empty() ? std::string(".") : (path + UserDirName);
}


void AppPathManager::initAppPath()
{
    ApplicationPathSTD = "romfs:/";

    std::string userDirPath = getPgeUserDirectory();
    if(!userDirPath.empty())
    {
        DirMan appDir(userDirPath);
        if(appDir.exists() || appDir.mkpath(userDirPath))
        {
            m_userPath = appDir.absolutePath();
            m_userPath.append("/");
            initSettingsPath();
            return;
        }
    }
    m_userPath = ApplicationPathSTD;
    initSettingsPath(); // can't write ANYTHING
    std::printf("== App Path is %s\n", ApplicationPathSTD.c_str());
    std::printf("== User Path is %s\n", m_userPath.c_str());
    fflush(stdout);
}

std::string AppPathManager::settingsFileSTD()
{
    return m_settingsPath + "thextech.ini";
}

std::string AppPathManager::userAppDirSTD()
{
    return m_userPath;
}

std::string AppPathManager::assetsRoot()
{
    return ApplicationPathSTD;
}

std::string AppPathManager::languagesDir()
{
    return ApplicationPathSTD + "languages";
}

std::string AppPathManager::screenshotsDir()
{
    return "";
}

std::string AppPathManager::gifRecordsDir()
{
    return "";
}

std::string AppPathManager::gameSaveRootDir()
{
    return m_settingsPath + "gamesaves";
}

std::string AppPathManager::userWorldsRootDir()
{
    return m_userPath + "worlds";
}

std::string AppPathManager::userBattleRootDir()
{
    return m_userPath + "battle";
}

void AppPathManager::install()
{
    std::string path = getPgeUserDirectory();

    if(!path.empty())
    {
        DirMan appDir(path);
        if(!appDir.exists())
            appDir.mkpath(path);
    }
}

bool AppPathManager::isPortable()
{
    return m_isPortable;
}

bool AppPathManager::checkPortable()
{
    return false;
}

bool AppPathManager::userDirIsAvailable()
{
    return (m_userPath != ApplicationPathSTD);
}

void AppPathManager::initSettingsPath()
{
    m_settingsPath = m_userPath + "settings/";

    if(Files::fileExists(m_settingsPath))
        Files::deleteFile(m_settingsPath);//Just in case, avoid mad jokes with making same-named file as settings folder

    if(!DirMan::exists(m_settingsPath))
        DirMan::mkAbsPath(m_settingsPath);

    // Also make the gamesaves root folder to be exist
    if(!DirMan::exists(gameSaveRootDir()))
        DirMan::mkAbsPath(gameSaveRootDir());
}
