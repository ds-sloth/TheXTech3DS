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

#ifndef FMT_FORMAT_NE_H
#define FMT_FORMAT_NE_H

#include <fmt/fmt_format.h>
#include <fmt/fmt_printf.h>
#include "Logger/logger.h"

namespace fmt
{
/*
    Exception-less fmt::format version. Instead of exception, the error message will be logged into file
*/
template <typename... Args>
std::string format_ne(CStringRef format_str, const Args & ... args)
{
    return format(format_str, std::forward<const Args&>(args)...);
}

template <typename... Args>
std::string sprintf_ne(CStringRef format_str, const Args & ... args)
{
    return sprintf(format_str, std::forward<const Args&>(args)...);
}

}//namespace fmt

#endif // FMT_FORMAT_NE_H
