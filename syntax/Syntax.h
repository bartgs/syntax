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

#pragma once

#include <map>
#include <string>
#include "Command.h"

namespace syntax
{
    class Syntax final
    {
        public:
            Syntax();

            void setProgram( const std::string& program, const std::string& help, const std::string& exit ) noexcept;
            const std::string& program() const noexcept;

            Command& addCommand( const std::string& name, const std::string& syntax, const std::string& help ) noexcept;
            void delCommand( const std::string& name ) noexcept;
            bool hasCommand( const std::string& name ) const noexcept;
            const Command& command( const std::string& name ) const;    // throws std::out_of_range when name is not found

            std::string toString() const noexcept;
            int parse( int arg, char* argv[], Command& command );
            const std::string& error() const noexcept;

        private:
            int _error( const int error, const std::string& message );

        private:
            std::string _program;
            std::string _help;
            std::string _exit;
            std::list<std::string> _order;
            std::map<std::string, Command> _commands;
            std::string _err;
    };
}
