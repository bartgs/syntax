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

#include "Command.h"

namespace syntax
{
    Command::Command()
        : IValue{}
        , _orderOptions{}
        , _options{}
        , _orderParams{}
        , _params{}
    {
    }


    Command::Command( const std::string& name, const std::string& syntax, const std::string& help )
        : IValue{ name, syntax, help }
        , _orderOptions{}
        , _options{}
        , _orderParams{}
        , _params{}
    {
    }


    void Command::addOption( const std::string& name, const std::string& syntax, const std::string& help, const bool value, const unsigned int requiredId ) noexcept
    {
        _orderOptions.push_back( name );
        _options[name] = Option{ name, syntax, help, value, requiredId };
    }


    void Command::delOption( const std::string& name ) noexcept
    {
        _orderOptions.remove( name );
        _options.erase( name );
    }


    bool Command::hasOption( const std::string& name ) const noexcept
    {
        return _options.find( name ) != _options.end();
    }


    const Option& Command::option( const std::string& name ) const
    {
        auto pos{ _options.find( name ) };
        if ( pos == _options.end() )
            throw std::out_of_range{ "there is no Option with name \'" + name + "\' available" };
        return pos->second;
    }


    const std::list<std::string>& Command::options() const noexcept
    {
        return _orderOptions;
    }


    void Command::addParam( const std::string& name, const std::string& syntax, const std::string& help, const bool required, const std::string& value ) noexcept
    {
        _orderParams.push_back( name );
        _params[name] = Param{ name, syntax, help, required, value };
    }


    void Command::delParam( const std::string& name ) noexcept
    {
        _orderParams.remove( name );
        _params.erase( name );
    }


    bool Command::hasParam( const std::string& name ) const noexcept
    {
        return _params.find( name ) != _params.end();
    }


    const Param& Command::param( const std::string& name ) const
    {
        auto pos{ _params.find( name ) };
        if ( pos == _params.end() )
            throw std::out_of_range{ "there is no Param with name \'" + name + "\' available" };
        return pos->second;
    }


    const std::list<std::string>& Command::params() const noexcept
    {
        return _orderParams;
    }
}
