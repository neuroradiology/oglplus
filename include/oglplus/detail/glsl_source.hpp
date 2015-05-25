/**
 *  .file oglplus/detail/glsl_source.hpp
 *  .brief Helper classes storing source code in GLSL
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_AUX_GLSL_SOURCE_1207111232_HPP
#define OGLPLUS_AUX_GLSL_SOURCE_1207111232_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/string/def.hpp>
#include <oglplus/string/ref.hpp>

#include <oglplus/detail/any_iter.hpp>

#include <vector>
#include <cassert>
#include <fstream>

namespace oglplus {
namespace aux {

struct GLSLSourceWrapper
{
	virtual
	~GLSLSourceWrapper(void)
	noexcept
	{ }

	virtual
	GLsizei Count(void) const = 0;

	virtual
	const GLchar* const* Parts(void) const = 0;

	virtual
	const GLint* Lengths(void) const = 0;
};

class GLCStrRefGLSLSrcWrap
 : public GLSLSourceWrapper
{
private:
	const GLchar* _ptr;
	const GLint _size;
public:
	GLCStrRefGLSLSrcWrap(const GLCStrRef& source)
	 : _ptr(source.begin())
	 , _size(GLint(source.size()))
	{
		assert(_ptr != nullptr);
	}

	GLsizei Count(void) const
	override
	{
		return GLsizei(1);
	}

	const GLchar* const* Parts(void) const
	override
	{
		return &_ptr;
	}

	const GLint* Lengths(void) const
	override
	{
		return &_size;
	}
};

class GLCStrRefsGLSLSrcWrap
 : public GLSLSourceWrapper
{
private:
	std::vector<const GLchar*> _ptrs;
	std::vector<GLint> _sizes;
public:
	GLCStrRefsGLSLSrcWrap(
		AnyInputIter<GLCStrRef>&& i,
		AnyInputIter<GLCStrRef>&& e
	);

	GLsizei Count(void) const
	override
	{
		return GLsizei(_ptrs.size());
	}

	const GLchar* const* Parts(void) const
	override
	{
		return _ptrs.data();
	}

	const GLint* Lengths(void) const
	override
	{
		return _sizes.data();
	}
};

class StrGLSLSrcWrap
 : public GLSLSourceWrapper
{
private:
	const GLString _storage;
	const GLchar* _ptr;
	const GLint _size;
public:
	StrGLSLSrcWrap(const GLString& source)
	 : _storage(source)
	 , _ptr(_storage.c_str())
	 , _size(GLint(_storage.size()))
	{
		assert(_ptr != nullptr);
	}

	StrGLSLSrcWrap(GLString&& source)
	 : _storage(std::move(source))
	 , _ptr(_storage.c_str())
	 , _size(GLint(_storage.size()))
	{
		assert(_ptr != nullptr);
	}

	GLsizei Count(void) const
	override
	{
		return GLsizei(1);
	}

	const GLchar* const* Parts(void) const
	override
	{
		return &_ptr;
	}

	const GLint* Lengths(void) const
	override
	{
		return &_size;
	}
};

class StrsGLSLSrcWrap
 : public GLSLSourceWrapper
{
private:
	std::vector<GLString> _storage;
	std::vector<const GLchar*> _ptrs;
	std::vector<GLint> _sizes;

	void _init(void);
public:
	StrsGLSLSrcWrap(
		AnyInputIter<GLString>&& i,
		AnyInputIter<GLString>&& e
	);

	StrsGLSLSrcWrap(std::vector<GLString>&& storage);

	GLsizei Count(void) const
	override
	{
		return GLsizei(_storage.size());
	}

	const GLchar* const* Parts(void) const
	override
	{
		return _ptrs.data();
	}

	const GLint* Lengths(void) const
	override
	{
		return _sizes.data();
	}
};

class InputStreamGLSLSrcWrap
 : public GLSLSourceWrapper
{
private:
	std::vector<GLchar> _storage;
	GLchar* _pdata;
	GLint _size;

	static std::size_t _check_and_get_size(std::istream& in);
	static std::vector<GLchar> _read_data(std::istream&, std::size_t);
public:
	InputStreamGLSLSrcWrap(std::istream& input);

	GLsizei Count(void) const
	override
	{
		return GLsizei(1);
	}

	const GLchar* const* Parts(void) const
	override
	{
		return const_cast<const GLchar**>(&_pdata);
	}

	const GLint* Lengths(void) const
	override
	{
		return &_size;
	}
};

class FileGLSLSrcWrapOpener
{
protected:
	std::ifstream _file;

	FileGLSLSrcWrapOpener(const eagine::base::cstrref& path);
};

class FileGLSLSrcWrap
 : public FileGLSLSrcWrapOpener
 , public InputStreamGLSLSrcWrap
{
public:
	FileGLSLSrcWrap(const eagine::base::cstrref& path);
};

} // namespace aux
} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/detail/glsl_source.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
