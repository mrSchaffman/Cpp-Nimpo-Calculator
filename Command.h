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
#include<memory>
#include<stack>

namespace control
{
	// The Command Hierarchy
	class Command
	{
	public:
		virtual~Command() = default;
		virtual void deallocate();

		void execute();
		void undo();

		// The Prototyp pattern
		Command* clone()const;
		const char* getHelpMessage()const;

	protected:
		// only the children of this class are allowed to call this Command Class.
		Command() = default;
		Command(const Command&) = default;

	private:
		// check some precondition before execute this Command
		virtual void checkPostConditionImpl()const;
		virtual void checkPreConditionImpl()const;

	private:
		// NVI Pattern, This are the methode to be overriden by the children
		virtual void executeImpl()noexcept = 0;			// atomic function (commit-or roll back)
		virtual void undoImpl()noexcept = 0;			// atomic function (commit-or roll back)
		virtual Command* cloneImpl()const = 0;
		virtual const char* getHelpMessageImpl()const noexcept = 0; // atomic function (commit-or roll back)

	private:
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
		virtual void executeImpl()noexcept override;
		virtual void undoImpl()noexcept override;

		// needed for the children of this class
		virtual double unaryOperation(double)const noexcept = 0;

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

	protected:
		BinaryCommand() :m_stackNext{}, m_stackTop{}{};
		BinaryCommand(const BinaryCommand&);

		virtual void checkPostConditionImpl()const override;
		virtual void checkPreConditionImpl()const override;

	private:
		virtual void executeImpl()noexcept override;
		virtual void undoImpl()noexcept override;

		// needed for the children of this class
		virtual double binaryOperation(double d, double b)const noexcept = 0;

		// not needed in this hierarchy
		// virtual Command* cloneImpl()const override; 
		// virtual const char* getHelpMessageImpl()const override;
	private:
		double m_stackTop;
		double m_stackNext;

	private:
		BinaryCommand(BinaryCommand&&) = delete;
		BinaryCommand& operator=(const BinaryCommand&) = delete;
		BinaryCommand& operator=(BinaryCommand&&) = delete;
	};

	// Concrete unary Command
	class CosineCommand : public UnaryCommand
	{
	public:
		double unaryOperation(double)const noexcept override;
		CosineCommand() = default;

		// needed for the Clone operation
		explicit CosineCommand(const CosineCommand& s);
		~CosineCommand();


	private:
		// from the base Class
		CosineCommand* cloneImpl()const override;
		const char* getHelpMessageImpl()const noexcept override;

		CosineCommand(CosineCommand&&) = delete;
		CosineCommand& operator=(const CosineCommand&) = delete;
		CosineCommand& operator=(CosineCommand&&) = delete;

	};
	
	class ACosineCommand : public UnaryCommand
	{
	public:
		double unaryOperation(double)const noexcept override;
		ACosineCommand() = default;

		// needed for the Clone operation
		explicit ACosineCommand(const ACosineCommand& s);
		~ACosineCommand();


	private:
		// from the base Class
		ACosineCommand* cloneImpl()const override;
		const char* getHelpMessageImpl()const noexcept override;

		ACosineCommand(ACosineCommand&&) = delete;
		ACosineCommand& operator=(const ACosineCommand&) = delete;
		ACosineCommand& operator=(ACosineCommand&&) = delete;

	};
	
	class SineCommand : public UnaryCommand
	{
	public:
		double unaryOperation(double)const noexcept override;
		SineCommand() = default;

		// needed for the Clone operation
		explicit SineCommand(const SineCommand& s);
		~SineCommand();


	private:
		// from the base Class
		SineCommand* cloneImpl()const override;
		const char* getHelpMessageImpl()const noexcept override;

		SineCommand(SineCommand&&) = delete;
		SineCommand& operator=(const SineCommand&) = delete;
		SineCommand& operator=(SineCommand&&) = delete;

	};
	
	class ASineCommand : public UnaryCommand
	{
	public:
		double unaryOperation(double)const noexcept override;
		ASineCommand() = default;
		explicit ASineCommand(const ASineCommand& s);
		~ASineCommand();

	private:
		// from the base Class
		ASineCommand* cloneImpl()const override;
		const char* getHelpMessageImpl()const noexcept override;
	
	private:
		ASineCommand(ASineCommand&&) = delete;
		ASineCommand& operator=(const ASineCommand&) = delete;
		ASineCommand& operator=(ASineCommand&&) = delete;

	};
	
	class TangentCommand : public UnaryCommand
	{
	public:
		double unaryOperation(double)const noexcept override;
		TangentCommand() = default;
		explicit TangentCommand(const TangentCommand& s);
		~TangentCommand();


	private:
		// from the base Class
		TangentCommand* cloneImpl()const override;
		const char* getHelpMessageImpl()const noexcept override;
		void checkPreConditionImpl()const override;
	
	private:
		TangentCommand(TangentCommand&&) = delete;
		TangentCommand& operator=(const TangentCommand&) = delete;
		TangentCommand& operator=(TangentCommand&&) = delete;

	};

	class ATangentCommand : public UnaryCommand
	{
	public:
		double unaryOperation(double)const noexcept override;
		ATangentCommand() = default;
		explicit ATangentCommand(const ATangentCommand& s);
		~ATangentCommand();

	private:
		// from the base Class
		ATangentCommand* cloneImpl()const override;
		const char* getHelpMessageImpl()const noexcept override;
	
	private:
		ATangentCommand(ATangentCommand&&) = delete;
		ATangentCommand& operator=(const ATangentCommand&) = delete;
		ATangentCommand& operator=(ATangentCommand&&) = delete;

	};

	// Concrete Binary Commands

	// adds two elements on the stack
	class AddCommand : public BinaryCommand
	{
	public:
		AddCommand() { }

		// needed for the Clone operation
		explicit AddCommand(const AddCommand&);
		~AddCommand();

	private:
		AddCommand(AddCommand&&) = delete;
		AddCommand& operator=(const AddCommand&) = delete;
		AddCommand& operator=(AddCommand&&) = delete;

		double binaryOperation(double next, double top) const noexcept override;

		AddCommand* cloneImpl() const override;

		const char* getHelpMessageImpl() const noexcept override;
	};

	// subtract two elements on the stack
	class SubstractCommand : public BinaryCommand
	{
	public:
		SubstractCommand() { }
		explicit SubstractCommand(const SubstractCommand&);
		~SubstractCommand();

	private:
		SubstractCommand(AddCommand&&) = delete;
		SubstractCommand& operator=(const SubstractCommand&) = delete;
		SubstractCommand& operator=(SubstractCommand&&) = delete;

		double binaryOperation(double next, double top) const noexcept override;

		SubstractCommand* cloneImpl() const override;

		const char* getHelpMessageImpl() const noexcept override;
	};

	// multiply two elements on the stack
	class MultiplyCommand : public BinaryCommand
	{
	public:
		MultiplyCommand() { }
		explicit MultiplyCommand(const MultiplyCommand&);
		~MultiplyCommand();

	private:
		MultiplyCommand(AddCommand&&) = delete;
		MultiplyCommand& operator=(const MultiplyCommand&) = delete;
		MultiplyCommand& operator=(MultiplyCommand&&) = delete;

		double binaryOperation(double next, double top) const noexcept override;

		MultiplyCommand* cloneImpl() const override;

		const char* getHelpMessageImpl() const noexcept override;
	};

	// divide two elements on the stack
	class DivideCommand : public BinaryCommand
	{
	public:
		DivideCommand() { }
		explicit DivideCommand(const DivideCommand&);
		~DivideCommand();

	private:
		double binaryOperation(double next, double top) const noexcept override;
		DivideCommand* cloneImpl() const override;
		void checkPreConditionImpl()const override;
		const char* getHelpMessageImpl() const noexcept override;

	private:
		DivideCommand(DivideCommand&&) = delete;
		DivideCommand& operator=(const DivideCommand&) = delete;
		DivideCommand& operator=(DivideCommand&&) = delete;
	};

	class SwapCommand : public Command
	{
	public:
		SwapCommand() { }
		explicit SwapCommand(const SwapCommand&);
		~SwapCommand();

	private:
		SwapCommand* cloneImpl() const override;
		void checkPreConditionImpl()const override;
		const char* getHelpMessageImpl() const noexcept override;
		void executeImpl()noexcept override;
		void undoImpl()noexcept override;
		
	private:
		SwapCommand(SwapCommand&&) = delete;
		SwapCommand& operator=(const SwapCommand&) = delete;
		SwapCommand& operator=(SwapCommand&&) = delete;
	};

	class ClearCommand : public Command
	{
	public:
		ClearCommand() :m_stack_{} { }
		explicit ClearCommand(const ClearCommand&);
		~ClearCommand();

	private:
		ClearCommand* cloneImpl() const override;
		const char* getHelpMessageImpl() const noexcept override;
		void executeImpl()noexcept override;
		void undoImpl()noexcept override;

	private:
		std::stack<double> m_stack_;

	private:
		ClearCommand(ClearCommand&&) = delete;
		ClearCommand& operator=(const ClearCommand&) = delete;
		ClearCommand& operator=(ClearCommand&&) = delete;
	};

	class DropCommand : public Command
	{
	public:
		DropCommand() :m_droppedNumber_{} { }
		explicit DropCommand(const DropCommand&);
		~DropCommand();

	private:
		DropCommand* cloneImpl() const override;
		const char* getHelpMessageImpl() const noexcept override;
		void executeImpl()noexcept override;
		void undoImpl()noexcept override;

	private:
		double m_droppedNumber_;
	private:
		DropCommand(DropCommand&&) = delete;
		DropCommand& operator=(const DropCommand&) = delete;
		DropCommand& operator=(DropCommand&&) = delete;
	};

	// Other Concrete Command
	// accepts a number from input and adds it to the stack
	// no preconditions are necessary for this command
	class EnterNumber : public Command
	{
	public:
		explicit EnterNumber(double d);
		explicit EnterNumber(const EnterNumber&);
		~EnterNumber();

	private:
		// adds the number to the stack
		void executeImpl() noexcept override;

		// removes the number from the stack
		void undoImpl() noexcept override;
		EnterNumber* cloneImpl() const override;
		const char* getHelpMessageImpl() const noexcept override;

	private:
		double m_number;

	private:
		EnterNumber(EnterNumber&&) = delete;
		EnterNumber& operator=(const EnterNumber&) = delete;
		EnterNumber& operator=(EnterNumber&&) = delete;
	};

	// helper
	inline void CommandDeleter(Command* p)
	{
		p->deallocate();
		return;
	}

	using CommandPtr = std::unique_ptr<Command, decltype(&CommandDeleter)>;

	template<typename T, typename... Args>
	auto MakeCommandPtr(Args&&... args)
	{
		return CommandPtr{ new T{std::forward<Args>(args)...}, &CommandDeleter };
	}

	inline auto MakeCommandPtr(Command* p)
	{
		return CommandPtr{ p, &CommandDeleter };
	}
}
#endif // !COMMAND_H

