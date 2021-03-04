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
#include <3ds.h>
// #include "../version.h"

// #include <SDL2/SDL.h>

std::string  ApplicationPathSTD;

std::string AppPathManager::m_settingsPath;
std::string AppPathManager::m_userPath;
std::vector<std::string> AppPathManager::m_worldRootDirs;
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
        if(appDir.exists() || appDir.mkpath(""))
        {
            m_userPath = appDir.absolutePath();
            m_userPath.append("/");
            initSettingsPath();
            findUserWorlds(appDir);
            return;
        }
    }
    m_userPath = ApplicationPathSTD;
    initSettingsPath(); // can't write ANYTHING
    std::printf("== App Path is %s\n", ApplicationPathSTD.c_str());
    std::printf("== User Path is %s\n", m_userPath.c_str());
    fflush(stdout);
}

void AppPathManager::findUserWorlds(DirMan userDir)
{
    m_worldRootDirs.push_back(UserDirName "/worlds/");
    m_worldRootDirs.push_back(assetsRoot() + "worlds/");
    std::vector<std::string> romfsFiles;
    static const std::vector<std::string> romfsExt = {".romfs"};
    userDir.getListOfFiles(romfsFiles, romfsExt);
    // for some reason dirent returns a very strange format that appears to be
    // utf-8 expressed as utf-16 and then converted back to utf-8.
    uint16_t utf16_buf[4096+1];
    uint8_t utf8_buf[4096+1];
    std::string fullPath;
    char mount_label[9] = "romfsA:/";
    for (std::string& s : romfsFiles)
    {
        fullPath = userDir.absolutePath() + "/" + s;
        ssize_t units = utf8_to_utf16(utf16_buf, (const uint8_t*)fullPath.c_str(), 4096);
        if (units < 0 || units > 4096) continue;
        utf16_buf[units] = 0;
        for (int i = 0; i < units; i++)
        {
            utf8_buf[i] = (uint8_t) (0xff & utf16_buf[i]);
        }
        utf8_buf[units] = 0;

        Handle fd = 0;
        FS_Path archPath = { PATH_EMPTY, 1, "" };
        FS_Path filePath = { PATH_ASCII, units+1, utf8_buf };
        Result rc = FSUSER_OpenFileDirectly(&fd, ARCHIVE_SDMC, archPath, filePath, FS_OPEN_READ, 0);
        if (R_FAILED(rc))
            continue;
        mount_label[6] = '\0';
        rc = romfsMountFromFile(fd, 0, mount_label);
        if (R_FAILED(rc))
            continue;
        mount_label[6] = ':';
        m_worldRootDirs.push_back(std::string(mount_label));
        mount_label[5] ++;
        // from Z to a.
        if (mount_label[5] == 91)
            mount_label[5] = 97;
        // max of 52 mounts.
        if (mount_label[5] == 123)
            break;
    }
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

const std::vector<std::string>& AppPathManager::worldRootDirs()
{
    return m_worldRootDirs;
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
