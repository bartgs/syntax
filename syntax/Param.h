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
#include "IValue.h"

namespace syntax
{
    class Param final : public IValue
    {
        public:
            Param() : IValue{}, _required{ false }, _value{} {}
            Param( const std::string& name, const std::string& syntax, const std::string& help, const bool required, const std::string& value ) : IValue{ name, syntax, help }, _required{ required }, _value{ value } {}

            bool required() const noexcept { return _required; }
            const std::string& value() const noexcept{ return _value; }

        private:
            bool _required;
            std::string _value;

            friend class Syntax;
    };
}
