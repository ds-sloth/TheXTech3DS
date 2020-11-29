#include <cstdlib>
#include <cstdio>

// each of these parses a section and returns true if it successfully exits
bool read_header(char* buffer, int n_chars, int& current_char, int& curActive, int& maxActive)
{
    // printf("header\n");
    while (current_char + 3 < n_chars)
    {
        // TS:int
        if (buffer[current_char] == 'T' && buffer[current_char+1] == 'S')
        {
            current_char += 3;
            const char* temp_buffer = buffer+current_char;
            while (buffer[current_char] != ';')
            {
                current_char++;
                if (current_char == n_chars)
                {
                    return false;
                }
            }
            buffer[current_char] = '\0';
            // total stars
            maxActive += atoi(temp_buffer)*4;
        }
        // GC:bool (0/1)
        else if (buffer[current_char] == 'G' && buffer[current_char+1] == 'C')
        {
            current_char += 3;
            // game complete
            if (buffer[current_char] == '1')
                curActive ++;
        }
        // SAVE_HEADER_END
        else if (buffer[current_char] == 'D')
        {
            if (buffer[current_char+1] == '\r')
            {
                current_char += 3;
                return true;
            }
            else if (buffer[current_char+1] == '\n')
            {
                current_char += 2;
                return true;
            }
        }
        current_char ++;
    }
    return false;
}

bool read_levels_paths(const char* buffer, int n_chars, int& current_char, int& curActive, int& maxActive)
{
    // printf("levels paths\n");
    while (current_char + 2 < n_chars)
    {
        // visible level/path
        if (buffer[current_char] == 'V' && buffer[current_char+1] == ':'
            && buffer[current_char+2] == '1')
            curActive ++;
        // level/path (regardless of visibility)
        else if (buffer[current_char] == '\n')
            maxActive ++;
        // VIZ_LEVELS_END / VIZ_PATHS_END
        else if (buffer[current_char] == 'D')
        {
            if (buffer[current_char+1] == '\r')
            {
                current_char += 3;
                return true;
            }
            else if (buffer[current_char+1] == '\n')
            {
                current_char += 2;
                return true;
            }
        }
        current_char ++;
    }
    return false;
}

bool read_junk(const char* buffer, int n_chars, int& current_char)
{
    // printf("junk\n");
    while (current_char + 1 < n_chars)
    {
        // VIZ_SCENERY_END
        if (buffer[current_char] == 'D')
        {
            if (buffer[current_char+1] == '\r')
            {
                current_char += 3;
                return true;
            }
            else if (buffer[current_char+1] == '\n')
            {
                current_char += 2;
                return true;
            }
        }
        current_char ++;
    }
    return false;
}

bool read_stars(const char* buffer, int n_chars, int& current_char, int& curActive, int& stars)
{
    // printf("stars\n");
    while (current_char + 1 < n_chars)
    {
        // gotten star
        if (buffer[current_char] == '\n')
        {
            curActive += 4;
            stars ++;
        }
        // STARS_END
        else if (buffer[current_char] == 'D')
        {
            if (buffer[current_char+1] == '\r')
            {
                current_char += 3;
                return true;
            }
            else if (buffer[current_char+1] == '\n')
            {
                current_char += 2;
                return true;
            }
        }
        current_char ++;
    }
    return false;
}

// only read game completed, total stars
// n paths open, n levels open, and n stars collected
bool quick_read_save(const char* p, int& curActive, int& maxActive, int& stars)
{
    // printf("reading from %s\n", p);
    FILE* f = fopen(p, "r");
    if (!f) return false;

    static const int BUFFER_SIZE = 128*1024;
    char* buffer = (char*) malloc(BUFFER_SIZE);
    if (!buffer) return false;
    int n_chars = 0;

    {
        int just_read;
        while (true)
        {
            just_read = fread((void*)&buffer[n_chars], 1, BUFFER_SIZE - n_chars - 1, f);
            if (just_read <= 0) break;
            n_chars += just_read;
        }
    }
    fclose(f);
    buffer[n_chars] = '\0';
    // printf("Read %d chars\n", n_chars);

    int current_char = 0;
    bool success = true;

    curActive = 0;
    maxActive = 1; // game completion
    stars = 0;

    // look for sections and call appropriate functions
    while (current_char+11 < n_chars && success)
    {
        // SAVE_HEADER
        if (buffer[current_char] == 'S' && buffer[current_char+1] == 'A')
        {
            if (buffer[current_char+11] == '\r')
            {
                current_char += 13;
                success = read_header(buffer, n_chars, current_char, curActive, maxActive);
            }
            else if (buffer[current_char+11] == '\n')
            {
                current_char += 12;
                success = read_header(buffer, n_chars, current_char, curActive, maxActive);
            }
        }
        // VIZ_LEVELS
        else if (buffer[current_char] == 'V' && buffer[current_char+4] == 'L')
        {
            if (buffer[current_char+10] == '\r')
            {
                current_char += 12;
                success = read_levels_paths(buffer, n_chars, current_char, curActive, maxActive);
            }
            else if (buffer[current_char+10] == '\n')
            {
                current_char += 11;
                success = read_levels_paths(buffer, n_chars, current_char, curActive, maxActive);
            }
        }
        // VIZ_PATHS
        else if (buffer[current_char] == 'V' && buffer[current_char+4] == 'P')
        {
            if (buffer[current_char+9] == '\r')
            {
                current_char += 11;
                success = read_levels_paths(buffer, n_chars, current_char, curActive, maxActive);
            }
            else if (buffer[current_char+9] == '\n')
            {
                current_char += 10;
                success = read_levels_paths(buffer, n_chars, current_char, curActive, maxActive);
            }
        }
        // VIZ_SCENERYS
        else if (buffer[current_char] == 'V' && buffer[current_char+4] == 'S')
        {
            if (buffer[current_char+11] == '\r')
            {
                current_char += 13;
                success = read_junk(buffer, n_chars, current_char);
            }
            else if (buffer[current_char+11] == '\n')
            {
                current_char += 12;
                success = read_junk(buffer, n_chars, current_char);
            }
        }
        // CHARACTERS
        else if (buffer[current_char] == 'C')
        {
            if (buffer[current_char+10] == '\r')
            {
                current_char += 12;
                success = read_junk(buffer, n_chars, current_char);
            }
            else if (buffer[current_char+10] == '\n')
            {
                current_char += 11;
                success = read_junk(buffer, n_chars, current_char);
            }
        }
        // SAVES
        else if (buffer[current_char] == 'S')
        {
            if (buffer[current_char+5] == '\r')
            {
                current_char += 7;
                success = read_stars(buffer, n_chars, current_char, curActive, stars);
            }
            else if (buffer[current_char+5] == '\n')
            {
                current_char += 6;
                success = read_stars(buffer, n_chars, current_char, curActive, stars);
            }
        }
        else
            current_char ++;
    }
    if (success)
    {
        // printf("Success: max %d, active %d, stars %d!\n", maxActive, curActive, stars);
    }
    free(buffer);
    return success;
}
