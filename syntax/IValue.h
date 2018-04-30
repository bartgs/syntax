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

#include <string>

namespace syntax
{
    class IValue
    {
        public:
            IValue() noexcept : _name{}, _syntax{}, _help{} {}
            IValue( const std::string& name, const std::string& syntax, const std::string& help ) : _name{ name }, _syntax{ syntax }, _help{ help } {}
            virtual ~IValue() = default;

            virtual const std::string& name() const noexcept { return _name; }
            virtual const std::string& syntax() const noexcept { return _syntax; }
            virtual const std::string& help() const noexcept { return _help; }

        protected:
            std::string _name;
            std::string _syntax;
            std::string _help;

            friend class Syntax;
    };
}
