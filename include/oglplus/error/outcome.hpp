/**
 *  @file oglplus/error/outcome.hpp
 *  @brief Class combining a return value and deferred error handler
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_ERROR_OUTCOME_1405082311_HPP
#define OGLPLUS_ERROR_OUTCOME_1405082311_HPP

#include <oglplus/error/deferred_handler.hpp>

namespace oglplus {

template <typename T>
class Outcome;

template <typename T>
class Outcome<T&>
{
private:
	DeferredHandler _error;
	T* _ptr;
public:
#if !OGLPLUS_NO_DEFAULTED_FUNCTIONS
	Outcome(Outcome&&) = default;
#else
	Outcome(Outcome&& temp)
	OGLPLUS_NOEXCEPT(true)
	 : _error(std::move(temp._error))
	 , _ptr(std::move(temp._ptr))
	{ }
#endif
	Outcome(T& ref)
	OGLPLUS_NOEXCEPT(true)
	 : _ptr(&ref)
	{ }

	template <typename Func>
	Outcome(Func handler)
	 : _error(handler)
	 , _ptr(nullptr)
	{ }
};

} // namespace oglplus

#endif // include guard