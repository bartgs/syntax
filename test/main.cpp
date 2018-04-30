//
//  Copyright 2017-2018
//  Author(s): Bart Gysens <gysens.bart@gmx.com>
//
//  This file is part of 'syntax'.
//
//  'syntax' is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  'syntax' is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with 'syntax'. If not, see <http://www.gnu.org/licenses/>.
//

#include <iostream>
#include <Syntax.h>

using namespace syntax;

int main(int argc, char *argv[])
{
    Syntax syntax;
    syntax.setProgram( "gpio", "gpio is a tool to operate on gpio pin(s)", "0 on success, else failure" );

    Command& read{ syntax.addCommand( "read", "read {debounce <time>} <p0> {<p1> .. p<30>}", "read value of given gpio pin(s)" ) };
    read.addOption( "debounce", "debounce <time>", "debounce time, in ms", true );
    read.addParam( "p0", "<p0> {<p2> .. <p30>}", "gpio pin(s)", true );
    for ( int i = 1; i < 31; ++i )
        read.addParam( "p" + std::to_string( i ) );

    Command& wait{ syntax.addCommand( "wait", "wait set|clear|mask <value> {debounce <time>} <p0> {<p1> .. <p30>}", "wait until gpio pin(s) are set, cleared or have given mask value" ) };
    wait.addOption( "set", "set", "wait until gpio pin(s) are set", false, 1 );
    wait.addOption( "clear", "clear", "wait until gpio pin(s) are cleared", false, 1 );
    wait.addOption( "mask", "mask <value>", "wait until gpio pin(s) have given mask value", true, 1 );
    wait.addOption( "debounce", "debounce <time>", "debounce time, in ms" );
    wait.addParam( "p0", "<p0> {<p1> .. <p30>}", "gpio pin(s)", true );
    for ( int i = 1; i < 31; ++i )
        wait.addParam( "p" + std::to_string( i ) );

    Command& write{ syntax.addCommand( "write", "write <value> <p0> {<p1> .. <p30>}", "write value to given gpio pin(s)" ) };
    write.addParam( "value", "<value>", "write value to gpio pin(s) (p0=bit0, p1=bit1, etc)", true );
    write.addParam( "p0", "<p0> {<p1> .. <p30>}", "gpio pin(s)", true );
    for ( int i = 1; i < 31; ++i )
        write.addParam( "p" + std::to_string( i ) );

    std::cout << std::endl << syntax.toString() << std::endl;

    Command command;
    int result = syntax.parse( argc, argv, command );

    if ( !result )
    {
        std::cout << "  command:" << std::endl
                  << "    " << syntax.program() << " " << command.name();

        for ( auto&& option : command.options() )
        {
            auto& o{ command.option( option ) };
            std::cout << " " << o.name();

            if ( o.hasValue() )
                std::cout << " " << o.value();
        }

        for ( auto&& param : command.params() )
        {
            auto& p{ command.param( param ) };
            std::cout << " " << p.value();
        }

        std::cout << std::endl;
    }
    else
    {
        std::cout << "  error:" << std::endl << "    " << syntax.error() << std::endl;
    }

    return result;
}
