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

#include <algorithm>
#include "Syntax.h"

namespace syntax
{
    Syntax::Syntax()
        : _program{}
        , _help{}
        , _exit{}
        , _order{}
        , _commands{}
        , _err{}
    {
    }


    void Syntax::setProgram( const std::string& program, const std::string& help, const std::string& exit ) noexcept
    {
        _program = program;
        _help = help;
        _exit = exit;
    }


    const std::string& Syntax::program() const noexcept
    {
        return _program;
    }


    Command& Syntax::addCommand( const std::string& name, const std::string& syntax, const std::string& help ) noexcept
    {
        _order.push_back( name );
        _commands[name] = Command{ name, syntax, help };
        return _commands.at( name );
    }


    void Syntax::delCommand( const std::string& name ) noexcept
    {
        _order.remove( name );
        _commands.erase( name );
    }


    bool Syntax::hasCommand( const std::string& name ) const noexcept
    {
        return _commands.find( name ) != _commands.end();
    }


    const Command& Syntax::command( const std::string& name ) const
    {
        auto pos{ _commands.find( name ) };
        if ( pos == _commands.end() )
            throw std::out_of_range( "there is no Command with name \'" + name + "\' available" );
        return pos->second;
    }


    std::string Syntax::toString() const noexcept
    {
        std::string newline{ "\n" };
        std::string indent{ "  " };
        std::string head{ "+ " };
        std::string result;

        result += indent + _help + newline
                + newline;

        if ( _commands.size() )
        {
            result += indent + "syntax:";

            unsigned long align{ 0 };

            for ( auto&& name : _order )
            {
                auto& command{ _commands.at( name ) };
                for ( auto&& option : command._options )
                    align = std::max( align, option.second._syntax.size() );

                for ( auto&& param : command._params )
                    align = std::max( align, param.second._syntax.size() );
            }

            align += 4 * indent.size();
            align = ( ( align / indent.size() ) * indent.size() ) + ( align % indent.size() ? indent.size() : 0 ) + 2 * indent.size();

            for ( auto&& name : _order )
            {
                auto& command{ _commands.at( name ) };
                result += newline
                        + indent + indent + _program + " " + command._syntax + newline
                        + indent + indent + indent + command.help() + newline;

                for ( auto&& name : command._orderOptions )
                {
                    auto& option{ command._options.at( name ) };
                    if ( option._help.size() )
                        result += indent + indent + indent + option._syntax
                                + std::string( align - ( 4 * indent.size() ) - option._syntax.size(), ' ' )
                                + option._help + ( option._requiredId ? "" : " [optional]" ) + newline;
                }

                for( auto&& name : command._orderParams )
                {
                    auto& param{ command._params.at( name ) };
                    if ( param._help.size() )
                        result += indent + indent + indent + param._syntax
                                + std::string( align - ( 4 * indent.size() ) - param._syntax.size(), ' ' )
                                + param._help + ( param._required ? "" : " [optional]" ) + newline;
                }
            }

            result += newline;
        }

        if ( _exit.size() )
        {
            result += indent + "return:" + newline
                    + indent + indent + _exit + newline;
        }

        return result;
    }


    int Syntax::parse( int argc, char* argv[], Command& command )
    {
        enum class State{ Command, OptionOrParam, OptionValue };
        State state{ State::Command };
        std::map<std::string, Command>::const_iterator itCommand;
        std::map<std::string,Option>::const_iterator itOption;
        std::list<std::string>::const_iterator itParam;
        std::string program{ argv[0] };

        if (   _program.size() > program.size()
            || !std::equal( _program.rbegin(), _program.rend(), program.rbegin() ) )
            return _error( -1, "invalid program name (expecting: " + _program + ")" );

        if ( argc < 2 )
            return _error( -2, "insufficient arguments" );

        for ( int i{ 1 }; i < argc; ++i )
        {
            switch ( state )
            {
                case State::Command:
                {
                    itCommand = _commands.find( argv[i] );

                    if ( itCommand != _commands.end() )
                    {
                        itParam = itCommand->second._orderParams.begin();

                        command = Command{ itCommand->second.name(), itCommand->second.syntax(), itCommand->second.help() };
                        state = State::OptionOrParam;
                        continue;
                    }

                    return _error( -3, std::string( "unknown command: " ) + argv[i] );
                }

                case State::OptionOrParam:
                {
                    itOption = itCommand->second._options.find( argv[i] );

                    if ( itOption != itCommand->second._options.end() )
                    {
                        command.addOption( argv[i], itOption->second.syntax(), itOption->second.help(), itOption->second.hasValue(), itOption->second.requiredId() );

                        if ( itOption->second.hasValue() )
                            state = State::OptionValue;
                        continue;
                    }
                    else if( itParam != itCommand->second._orderParams.end() )
                    {
                        auto& param = itCommand->second._params.at( *itParam++ );
                        command.addParam( param.name(), param.syntax(), param.help(), param.required(), argv[i] );
                        continue;
                    }

                    return _error( -4, std::string( "unknown option or param: " ) + argv[i] );
                }

                case State::OptionValue:
                {
                    command._options.at( itOption->first )._value = std::string( argv[i] );
                    state = State::OptionOrParam;
                    break;
                }

                default:
                {
                    return _error( -5, std::string( "unknown how to handle:" ) + argv[i] );
                }
            }
        }

        return 0;
    }


    const std::string& Syntax::error() const noexcept
    {
        return _err;
    }


    int Syntax::_error( const int error, const std::string& message )
    {
        _err = "error [" + std::to_string( error ) + "]: " + message;
        return error;
    }
}
