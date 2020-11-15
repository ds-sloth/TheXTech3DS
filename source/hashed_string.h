#ifndef HASHED_STRING_H
#define HASHED_STRING_H

#include <string>

class HashedString {
private:
    bool is_empty;
public:
    HashedString(void);
    explicit HashedString(const std::string& o);
    inline bool operator==(const HashedString& o) const;
    inline bool operator!=(const HashedString& o) const;
    inline bool empty();
    void clear();
    // std::string base_str;
    size_t hash;
    size_t upper_hash;
};

inline bool HashedString::operator==(const HashedString& o) const
{
    return (hash == o.hash);
}

inline bool HashedString::operator!=(const HashedString& o) const
{
    return (hash != o.hash);
}

inline bool HashedString::empty()
{
    return is_empty;
}

extern const HashedString HS_LevelStart;
extern const HashedString HS_SpawnedNPCs;
extern const HashedString HS_DestroyedBlocks;
extern const HashedString HS_Default;
extern const HashedString HS_PSwitchStart;
extern const HashedString HS_UsedPSwitch;
extern const HashedString HS_PSwitchEnd;

#endif
