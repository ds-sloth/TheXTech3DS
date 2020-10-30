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

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <PGE_File_Formats/pge_file_lib_private.h>//It's only exception for macOS here to get URL-Decode. Never include this!
#include "app_path_macosx.h"
#endif

#ifdef __gnu_linux__
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

#ifdef _WIN32
#include <windows.h>
#include <winreg.h>
#include <algorithm> // std::replace from \\ into /
#endif

#ifdef __EMSCRIPTEN__
#include <emscripten.h>

static bool loadingLocked = false;

extern "C" void unlockLoadingCustomState()
{
    loadingLocked = false;
}

static void loadCustomState()
{
    loadingLocked = true;
    EM_ASM(
        FS.mkdir('/settings');
        FS.mount(IDBFS, {}, '/settings');

        // sync from persisted state into memory and then
        // run the 'test' function
        FS.syncfs(true, function (err) {
            assert(!err);
            ccall('unlockLoadingCustomState', 'v');
        });
    );

    while(loadingLocked)
        emscripten_sleep(10);
}

static void saveCustomState()
{
    loadingLocked = true;
    EM_ASM(
        FS.syncfs(function (err) {
            assert(!err);
            ccall('unlockLoadingCustomState', 'v');
        });
    );

    while(loadingLocked)
        emscripten_sleep(10);
}
#endif

#include "app_path.h"
// #include "../version.h"

// #include <SDL2/SDL.h>

std::string  ApplicationPathSTD;

std::string AppPathManager::m_settingsPath;
std::string AppPathManager::m_userPath;
#ifdef __APPLE__

#   ifndef USERDATA_ROOT_NAME
#       define USERDATA_ROOT_NAME "TheXTech Episodes"
#   endif

std::string AppPathManager::m_userDataRoot;
#endif
bool AppPathManager::m_isPortable = false;

#define UserDirName "/smbx-data"

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
    ApplicationPathSTD = "/smbx/";

    if(checkPortable())
        return;

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
    initSettingsPath();
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
    return m_userPath;
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
    if(m_settingsPath.empty())
        m_settingsPath = ApplicationPathSTD;

    if(m_userPath.empty())
        m_userPath = ApplicationPathSTD;

    if(!Files::fileExists(settingsFileSTD()))
        return false;

    m_isPortable = false;

    IniProcessing checkForPort(settingsFileSTD());
    checkForPort.beginGroup("Main");
    m_isPortable = checkForPort.value("force-portable", false).toBool();
    checkForPort.endGroup();

    if(m_isPortable)
        initSettingsPath();

    return m_isPortable;
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
