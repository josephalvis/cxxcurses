#ifndef CXXCURSES_PRINT_PRINT_HPP
#define CXXCURSES_PRINT_PRINT_HPP

#include "utils.hpp"

namespace cxxcurses
{

//TODO: WINDOW* versions
void print( const int y, const int x, const std::string& format ) noexcept
{
    mvwprintw( stdscr, y, x, format.c_str() );
}

void print( const int y, const int x, const glyph_string& format ) noexcept
{
    format.print( y, x );
}

void print( const int y, const std::string& format ) noexcept
{
    const auto x_centered{ ( getmaxx( stdscr ) - format.size() ) / 2 };
    mvwprintw( stdscr, y, x_centered, format.c_str() );
}

void print( const int y, const glyph_string& format ) noexcept
{
    const auto x_centered{ ( getmaxx( stdscr ) - format.size() ) / 2 };
    format.print( y, x_centered );
}

void print( const std::string& format ) noexcept
{
    const auto[y, x] = get_current_yx();
    mvwprintw( stdscr, y, x, format.c_str() );
}

void print( const glyph_string& format ) noexcept
{
    const auto[y, x] = get_current_yx();
    format.print( y, x );
}

//move and print versions
template <typename T, typename... Args>
constexpr void print( const int y, const int x, const glyph_string& format_str, const T& arg, Args&& ... args ) noexcept
{
    print( y, x, parse( format_str, arg ), ( std::forward<Args>( args ) )... );
}

template <typename T, typename... Args>
constexpr void print( const int y, const int x, const std::string& format_str, const T& arg, Args&& ... args ) noexcept
{
    print( y, x, parse( glyph_string{ format_str }, arg ), ( std::forward<Args>( args ) )... );
}

//print at curent cursor position versions
template <typename T, typename... Args>
constexpr void print( const glyph_string& format_str, const T& arg, Args&& ... args ) noexcept
{
    print( parse( format_str, arg ), ( std::forward<Args>( args ) )... );
}

template <typename T, typename... Args>
constexpr void print( const std::string& format_str, const T& arg, Args&& ... args ) noexcept
{
    print( parse( format_str, arg ), ( std::forward<Args>( args ) )... );
}

//TODO: centered version
//centered versions

template <typename T, typename... Args>
constexpr void print( const int y, const glyph_string& format_str, const T& arg, Args&& ... args ) noexcept
{
    print( y, parse( format_str, arg ), ( std::forward<Args>( args ) )... );
}

template <typename... Args>
constexpr void print( const int y, const std::string& format_str, Args&& ... args ) noexcept
{
    print( y, glyph_string{ format_str }, ( std::forward<Args>( args ) )... );
}

template <typename... Args>
[[deprecated]] void center_mvmwprintw( WINDOW* window, int y, const std::string& string, Args... args )
{
    mvwprintw( window, y,
               ( static_cast<unsigned int>(getmaxx( window )) - string.length() ) / 2,
               string.c_str(), args... );
    wrefresh( window );
}

}
#endif //CXXCURSES_PRINT_PRINT_HPP