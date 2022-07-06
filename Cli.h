#pragma once
/*
	Copyright (C) 2022  Barth.Feudong
	Author can be contacted here: <https://github.com/mrSchaffman/Cpp-Nimpo-Calculator>

	This file is part of the Nimpo Command Line Calculator project.

	Nimpo is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Nimpo is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/
#ifndef CLI_H
#define CLI_H
#include"UserInterface.h"
#include<istream>
#include<ostream>
namespace view
{
	class Cli : public UserInterface
	{
	public:
		Cli(std::istream&is,std::ostream&os);
		~Cli();
		void run();
	private:
		void stackChanged()override;
		void displayMessage(const std::string& msg)override;

		Cli(const Cli&) = delete;
		Cli(Cli&&) = delete;
		Cli& operator=(const Cli&) = delete;
		Cli& operator=(Cli&&) = delete;

		class CliImpl;
		std::unique_ptr<CliImpl> impl;
	};
}
#endif // !CLI_H

