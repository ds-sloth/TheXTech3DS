#ifndef FASTCALCS_H
#define FASTCALCS_H
#include <cmath>

/**
 * @brief Comparison of two floating point numbers
 * @param a First argument
 * @param b Second argument
 * @return true whe both arguments are equal (almost)
 */
inline bool fEqual(double a, double b)
{
    return (std::abs(a-b) < 1e-6);
}
/**
 * @brief Comparison of two floating point numbers
 * @param a First argument
 * @param b Second argument
 * @return true whe both arguments are equal (almost)
 */
inline bool fEqual(float a, float b)
{
    return (std::abs(a-b) < 1e-4f);
}

inline bool iEqual(double a, double b)
{
    return (std::abs(a-b) < .5);
}

inline bool iEqual(double a, float b)
{
    return (std::abs(a-b) < .5);
}

inline bool iEqual(double a, int b)
{
    return (std::abs(a-b) < .5);
}

inline bool iEqual(double a, long b)
{
    return (std::abs(a-b) < .5);
}

inline bool iEqual(float a, double b)
{
    return (std::abs(a-b) < .5);
}

inline bool iEqual(float a, float b)
{
    return (std::abs(a-b) < .5);
}

inline bool iEqual(float a, int b)
{
    return (std::abs(a-b) < .5);
}

inline bool iEqual(float a, long b)
{
    return (std::abs(a-b) < .5);
}

inline bool iEqual(int a, double b)
{
    return (std::abs(a-b) < .5);
}

inline bool iEqual(int a, float b)
{
    return (std::abs(a-b) < .5);
}

inline bool iEqual(long a, double b)
{
    return (std::abs(a-b) < .5);
}

inline bool iEqual(long a, float b)
{
    return (std::abs(a-b) < .5);
}

inline bool iEqual(int a, int b)
{
    return (a == b);
}

inline bool iEqual(long a, long b)
{
    return (a == b);
}
#endif
