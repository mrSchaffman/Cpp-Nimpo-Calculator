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

#ifndef COMMAND_H
#define COMMAND_H
namespace control
{
	// The Command Hierarchy
	class Command
	{
	public:
		virtual~Command() = default;
		void execute();
		void undo();

		// The Prototyp pattern
		Command* clone()const;

		const char* getHelpMessage()const;
		virtual void dealocate();

	protected:
		// only the children of this class are allowed to call this Command Class.
		Command() = default;
		Command(const Command&) = default;

	private:
		// check some precondition before execute this Command
		virtual void checkPostConditionImpl()const;
		virtual void checkPreConditionImpl()const;

		// NVI Pattern, This are the methode to be overriden by the children
		virtual void executeImpl() = 0;
		virtual void undoImpl() = 0;
		virtual Command* cloneImpl()const = 0;
		virtual const char* getHelpMessageImpl()const = 0;

		// uneeded Capabiliies
		Command(Command&&) = delete;
		Command& operator=(const Command&) = delete;
		Command& operator=(Command&&) = delete;
	};

	// 1st hierarchy Base Classes Binary Command And Unary Commands

	class UnaryCommand : public Command
	{
	public:
		virtual~UnaryCommand() = default;

	private:
		virtual void executeImpl()override;
		virtual void undoImpl()override;

		// needed for the children of this class
		virtual double unaryOperation(double) = 0;


		// not needed in this hierarchy
		// virtual Command* cloneImpl()const override; 
		// virtual const char* getHelpMessageImpl()const override;

		double m_stackTop;


	protected:

		virtual void checkPostConditionImpl()const override;
		virtual void checkPreConditionImpl()const override;

		UnaryCommand() = default;
		UnaryCommand(const UnaryCommand&);


	private:
		UnaryCommand(UnaryCommand&&) = delete;
		UnaryCommand& operator=(const UnaryCommand&) = delete;
		UnaryCommand& operator=(UnaryCommand&&) = delete;
	};
	class BinaryCommand : public Command
	{
	public:
		virtual~BinaryCommand() = default;

	private:
		virtual void executeImpl()override;
		virtual void undoImpl()override;

		// needed for the children of this class
		virtual double binaryOperation(double d,double b) = 0;


		// not needed in this hierarchy
		// virtual Command* cloneImpl()const override; 
		// virtual const char* getHelpMessageImpl()const override;

		double m_stackTop;
		double m_stackNext;


	protected:

		virtual void checkPostConditionImpl()const override;
		virtual void checkPreConditionImpl()const override;

		BinaryCommand() = default;
		BinaryCommand(const BinaryCommand&);


	private:
		BinaryCommand(BinaryCommand&&) = delete;
		BinaryCommand& operator=(const BinaryCommand&) = delete;
		BinaryCommand& operator=(BinaryCommand&&) = delete;
	};


}
#endif // !COMMAND_H

