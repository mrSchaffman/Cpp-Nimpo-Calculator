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
#include <iostream>
#include"Cli.h"
#include"Stack.h"
#include"Command.h"
#include"Observers.h"
#include"CommandRepository.h"
#include"Exception.h"

using namespace view;
using namespace model;
using namespace control;
using namespace utility;

using namespace std;

void registerCommand(UserInterface& ui, const string& label, CommandPtr c)
{
	try
	{
		CommandRepository::getInstance().registerCommand(label, std::move(c));
	}
	catch (Exception& e)
	{
		ui.displayMessage(e.what());
	}

	return;
}

void RegisterCoreCommands(UserInterface& ui)
{
	registerCommand(ui, "+", MakeCommandPtr<AddCommand>());
	registerCommand(ui, "cos", MakeCommandPtr<CosineCommand>());
	registerCommand(ui, "arccos", MakeCommandPtr<ACosineCommand>());
	registerCommand(ui, "sin", MakeCommandPtr<SineCommand>());
	registerCommand(ui, "tan", MakeCommandPtr<TangentCommand>());
	registerCommand(ui, "-", MakeCommandPtr<SubstractCommand>());
	registerCommand(ui, "*", MakeCommandPtr<MultiplyCommand>());
	registerCommand(ui, "/", MakeCommandPtr<DivideCommand>());

	return;
}

int main()
{
	
	Cli cli{ cin,cout };
	RegisterCoreCommands(cli);

	CommandDispatcher ce{ cli };

	cli.subscribe(view::UserInterface::UICommandName, make_unique<CommandIssuedObserver>(ce));

	Stack::getInstance().subscribe(Stack::StackChanged, make_unique<StackUpdatedObserver>(cli));

	cli.run();
}

