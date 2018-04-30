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

#include <list>
#include <map>
#include <string>
#include "IValue.h"
#include "Option.h"
#include "Param.h"

namespace syntax
{
    class Command final : public IValue
    {
        public:
            Command();
            Command( const std::string& name, const std::string& syntax, const std::string& help );

            void addOption( const std::string& name, const std::string& syntax, const std::string& help, const bool value = false, const unsigned int requiredId = 0 ) noexcept;
            void delOption( const std::string& name ) noexcept;
            bool hasOption( const std::string& name ) const noexcept;
            const Option& option( const std::string& name ) const;  // throws std::out_of_range when name is not found
            const std::list<std::string>& options() const noexcept;

            void addParam( const std::string& name, const std::string& syntax = std::string{}, const std::string& help = std::string{}, const bool required = false, const std::string& value = std::string{} ) noexcept;
            void delParam( const std::string& name ) noexcept;
            bool hasParam( const std::string& name ) const noexcept;
            const Param& param( const std::string& name ) const;    // throws std::out_of_range when name is not found
            const std::list<std::string>& params() const noexcept;

        private:
            std::list<std::string> _orderOptions;
            std::map<std::string, Option> _options;
            std::list<std::string> _orderParams;
            std::map<std::string, Param> _params;

            friend class Syntax;
    };
}
