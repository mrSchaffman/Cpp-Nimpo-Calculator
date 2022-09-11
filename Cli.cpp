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

#include "Cli.h"
#include"Tokenizer.h"
#include<iterator>
#include<sstream>
#include<vector>
#include<algorithm>
#include"Stack.h"
#include"ConsoleLogger.h"

namespace view
{
	class Cli::CliImpl
	{
	public:
		CliImpl(Cli& cli, std::istream& is, std::ostream& os) :m_parent{ cli }, m_is{ is }, m_os{ os }{}
		~CliImpl() = default;

		void stackChanged();
		void displayMessage(const std::string& msg);

		void run();

	private:
		void startupMessage();

		std::istream& m_is;
		std::ostream& m_os;
		Cli& m_parent;
	};

	Cli::Cli(std::istream& is, std::ostream& os)
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Cli::Cli() ", sizeof(this), " bytes");
#endif // DEBUG_MODE

		impl = std::make_unique<CliImpl>(*this, is, os);
	}

	Cli::~Cli()
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Cli::~Cli()");
#endif // DEBUG_MODE

	}

	void Cli::run()
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Cli::run()");
#endif // DEBUG_MODE

		impl->run();
	}

	void Cli::stackChanged()
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Cli::stackChanged()");
#endif // DEBUG_MODE

		impl->stackChanged();
	}

	void Cli::displayMessage(const std::string& msg)
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Cli::displayMessage()");
#endif // DEBUG_MODE

		impl->displayMessage(msg);
	}

	void Cli::CliImpl::stackChanged()
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Cli::CliImpl::stackChanged()");
#endif // DEBUG_MODE

		unsigned int nElements{ 4 };
		auto v = model::Stack::getInstance().getElements(nElements);
		std::ostringstream oss;
		oss.precision(12);
		size_t size = model::Stack::getInstance().size();
		oss << "\n";

		if (size == 0)
			oss << "Stack currently empty.\n";
		else if (size == 1)
			oss << "Top element of stack (size = " << size << "):\n";
		else if (size > 1 && size <= nElements)
			oss << "Top " << size << " elements of stack (size = " << size << "):\n";
		else
			oss << "Top " << nElements << " elements of stack (size = " << size << "):\n";

		size_t j{ v.size() };
		for (auto i = v.rbegin(); i != v.rend(); ++i)
		{
			oss << j << ":\t" << *i << "\n";
			--j;
		}

		displayMessage(oss.str());
	}

	void Cli::CliImpl::displayMessage(const std::string& msg)
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Cli::CliImpl::displayMessage(s)",msg);
#endif // DEBUG_MODE

		// print to the Consol
		m_os << msg << std::endl;
	}

	void Cli::CliImpl::run()
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Cli::CliImpl::run()");
#endif // DEBUG_MODE

		startupMessage();

		for (string line; std::getline(m_is, line, '\n'); )
		{
			utility::Tokenizer tokenizer{ line };
			for (const auto& i : tokenizer)
			{
				if (i == "exit" || i == "quit")
				{
					return;
				}
				else
				{
					m_parent.notify(UserInterface::UICommandName, std::make_shared<UIEventData>(i));
				}
			}
		}
	}

	void Cli::CliImpl::startupMessage()
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Cli::CliImpl::startupMessage()");
#endif // DEBUG_MODE

		m_os << "#############################################################\n\n"
			 << "      Nimpo v. " << 1 << ", an RPN calculator by Barth. Feudong\n\n"
			 << "#############################################################\n\n" 
			 << "type:\n'help' for a list of commnads\n"
			 << "'exit' to end program\n" << std::endl;

		return;
	}

}