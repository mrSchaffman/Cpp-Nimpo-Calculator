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
#include "Command.h"
#include"Stack.h"
#include"Exception.h"

using namespace model;
namespace control
{
	void Command::execute()
	{
		// like the Template Methode Pattern
		checkPreConditionImpl();
		executeImpl();
		checkPostConditionImpl();
	}
	void Command::undo()
	{
		undoImpl();
	}
	Command * Command::clone() const
	{
		return cloneImpl();
	}
	const char * Command::getHelpMessage() const
	{
		return getHelpMessageImpl();
	}
	void Command::dealocate()
	{
		delete this;
	}
	void Command::checkPostConditionImpl() const
	{
		// to be overrided by the Children;
	}
	void Command::checkPreConditionImpl() const
	{
		// to be overrided by the Children;
	}

	// UnaryCommand Implementation
	void UnaryCommand::executeImpl()
	{
		m_stackTop = Stack::getInstance().pop(true);
		Stack::getInstance().push(unaryOperation(m_stackTop));
	}
	void UnaryCommand::undoImpl()
	{
		Stack::getInstance().pop(true);
		Stack::getInstance().push(m_stackTop);

	}
	void UnaryCommand::checkPostConditionImpl()const
	{
		// To Do
	}
	void UnaryCommand::checkPreConditionImpl()const
	{
		if (model::Stack::getInstance().size() < 1)
			throw utility::Exception("Stack must have at least one Element!");

	}
	UnaryCommand::UnaryCommand(const UnaryCommand & rhs):Command(rhs),m_stackTop(rhs.m_stackTop)
	{
	}
	void BinaryCommand::executeImpl()
	{
		m_stackTop = model::Stack::getInstance().pop();
		m_stackNext = model::Stack::getInstance().pop();
		model::Stack::getInstance().push(binaryOperation(m_stackNext, m_stackTop));

	}
	void BinaryCommand::undoImpl()
	{
		model::Stack::getInstance().pop();
		model::Stack::getInstance().push(m_stackNext);
		model::Stack::getInstance().push(m_stackTop);
	}
	void BinaryCommand::checkPostConditionImpl() const
	{
		// To do
	}
	void BinaryCommand::checkPreConditionImpl() const
	{
		if (model::Stack::getInstance().size() < 2)
			throw utility::Exception{ "Stack must have 2 elements" };

	}
	BinaryCommand::BinaryCommand(const BinaryCommand &rhs):Command(rhs),m_stackTop{rhs.m_stackTop},m_stackNext{rhs.m_stackNext}
	{
	}
}