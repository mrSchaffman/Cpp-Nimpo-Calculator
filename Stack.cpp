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
#include "Stack.h"
#include"Exception.h"
#include"ConsoleLogger.h"
#include<deque>

namespace model
{
	const std::string Stack::StackChanged = "stackChanged";
	const std::string Stack::StackError = "stackError";

	class Stack::StackImpl
	{
	public:
		explicit StackImpl(const Stack&);
		
		void push(double, bool notify = false);
		double pop(bool notify = false);
		double top()const;
		void swap();
		size_t size() const;
		void clear();
		std::vector<double> getElements(size_t n) const;
		void getElements(size_t n, std::vector<double>&) const;

	private:
		const Stack& parent;
		std::deque<double> m_model;
	};

	Stack::Stack()
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Stack::Stack()",sizeof(this)," bytes");
#endif // DEBUG_MODE

		impl = std::make_unique<StackImpl>(*this);

		// register the event populate by the stack model
		registerEvent(StackChanged);
		registerEvent(StackError);
	}
	Stack::~Stack()
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Stack::~Stack()");
#endif // DEBUG_MODE

	}

	Stack & Stack::getInstance()
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Stack::getInstance()");
#endif // DEBUG_MODE

		static Stack instance;
		return instance;
	}

	void Stack::push(double d, bool suppressChangeEvent)
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Stack::push()", d, suppressChangeEvent);
#endif // DEBUG_MODE


		impl->push(d, suppressChangeEvent);
	}

	double Stack::pop(bool suppressChangeEvent)
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Stack::pop()");
#endif // DEBUG_MODE

		return impl->pop(suppressChangeEvent);
	}

	double Stack::top() const
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Stack::top()");
#endif // DEBUG_MODE


		return impl->top();
	}

	void Stack::swap()
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Stack::swap()");
#endif // DEBUG_MODE


		impl->swap();
	}

	std::vector<double> Stack::getElements(size_t n) const
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Stack::getElements(n)","n = ", n);
#endif // DEBUG_MODE


		return impl->getElements(n);
	}

	void Stack::getElements(size_t n, std::vector<double>&v) const
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Stack::getElements(n,v)", "n = ", n, "vector size = ", v.size());// , std::to_string(d), v);
#endif // DEBUG_MODE


		impl->getElements(n, v);
	}

	size_t Stack::size() const
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Stack::size()");
#endif // DEBUG_MODE


		return impl->size();
	}

	void Stack::clear() const
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Stack::clear()");
#endif // DEBUG_MODE


		impl->clear();
	}

	Stack::StackImpl::StackImpl(const Stack & p): parent{p}
	{
#ifdef DEBUG_MODE
		utility::logToConsole("Stack::StackImpl::StackImpl()",sizeof(this)," bytes");
#endif // DEBUG_MODE

	}

	void Stack::StackImpl::push(double d, bool notify)
	{
		m_model.push_back(d);
		if (notify) parent.notify(Stack::StackChanged, nullptr);
	}

	double Stack::StackImpl::pop(bool notify)
	{
		if (m_model.empty())
		{
			parent.notify(Stack::StackError,
				std::make_shared<StackEventData>(ErrorType::EMPTY));

			throw utility::Exception{ StackEventData::getMessage(ErrorType::EMPTY) };

		}
		else
		{
			auto val = m_model.back();
			m_model.pop_back();
			if (notify) parent.notify(Stack::StackChanged, nullptr);
			return val;
		}
	}

	double Stack::StackImpl::top() const
	{
		return m_model.back();
	}

	void Stack::StackImpl::swap()
	{
		if (m_model.size() < 2)
		{
			parent.notify(Stack::StackError,
				std::make_shared<StackEventData>(ErrorType::TOO_FEW_ARGUMENT));

			throw utility::Exception{ StackEventData::getMessage(ErrorType::TOO_FEW_ARGUMENT) };
		}
		else
		{
			auto first = m_model.back();
			m_model.pop_back();
			auto second = m_model.back();
			m_model.pop_back();
			m_model.push_back(first);
			m_model.push_back(second);

			parent.notify(Stack::StackChanged, nullptr);
		}

	}

	size_t Stack::StackImpl::size() const
	{
		return m_model.size();
	}

	void Stack::StackImpl::clear()
	{
		m_model.clear();
		
		parent.notify(Stack::StackChanged, nullptr);

	}

	std::vector<double> Stack::StackImpl::getElements(size_t n) const
	{
		std::vector<double> v;
		getElements(n, v);
		return v;
	}

	void Stack::StackImpl::getElements(size_t n, std::vector<double>& v) const
	{
		if (n > m_model.size()) n = m_model.size();

		v.insert(v.end(), m_model.rbegin(), m_model.rbegin() + n);

	}

	const char * StackEventData::getMessage(ErrorType e)
	{
		switch (e)
		{
		case ErrorType::EMPTY: return "Attempting to pop empty stack";
		case ErrorType::TOO_FEW_ARGUMENT: return "Need at least two stack elements to swap top";
		default: return "Unknown error";
		};
	}

	const char * StackEventData::getMessage() const
	{
#ifdef DEBUG_MODE
		utility::logToConsole("StackEventData::getMessage() ","()");
#endif // DEBUG_MODE

		return getMessage(er);
	}

}