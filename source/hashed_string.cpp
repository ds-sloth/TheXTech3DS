#include <string>
#include <iostream>
#include <algorithm>

#include "hashed_string.h"

std::hash<std::string> strHash = std::hash<std::string>();
size_t empty_hash = strHash("");

HashedString::HashedString(void)
{
}
HashedString::HashedString(const std::string& o)
{
    std::string uppercase_string;
    uppercase_string.resize(o.length());
    std::transform(o.begin(), o.end(), uppercase_string.begin(), [](unsigned char c){ return std::toupper(c); });

    // base_str = o;
    is_empty = (o.empty());
    hash = strHash(o);
    upper_hash = strHash(uppercase_string);
}

void HashedString::clear()
{
    // base_str.clear();
    is_empty = true;
    hash = empty_hash;
    upper_hash = empty_hash;
}

const HashedString HS_LevelStart = (HashedString)"Level - Start";
const HashedString HS_SpawnedNPCs = (HashedString)"Spawned NPCs";
const HashedString HS_DestroyedBlocks = (HashedString)"Destroyed Blocks";
const HashedString HS_Default = (HashedString)"Default";
const HashedString HS_PSwitchStart = (HashedString)"P Switch - Start";
const HashedString HS_UsedPSwitch = (HashedString)"Used P Switch";
const HashedString HS_PSwitchEnd = (HashedString)"P Switch - End";
