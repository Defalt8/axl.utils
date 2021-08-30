#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <wchar.h>
#include <axl.util/lib.hpp>
#include <axl.util/WString.hpp>
#include <axl.util/String.hpp>

namespace axl {
namespace util {

const WString::char_t*const WString::NullCWStr = (const WString::char_t*const)0;
WString::char_t*const WString::NullWStr = (WString::char_t*const)0;
const WString::char_t WString::NullWChar = (WString::char_t)L'\0';

WString::WString(size_t length) :
	m_length(0U),
	m_size(0U)
{
	const size_t size = length + 1U;
	if(size == 0)
		m_array = NullWStr;
	else if(size > 0)
	{
		m_array = (char_t*) malloc(size*sizeof(char_t));
		if(m_array)
		{
			m_size = size;
			m_array[0] = NullWChar;
		}
	}
}
WString::WString(const WString::char_t* cwstring) :
	m_length(0U),
	m_size(0U)
{
	const size_t size = scwLength(cwstring) + 1U;
	if(size == 0)
		m_array = NullWStr;
	else if(size > 0)
	{
		m_array = (char_t*) malloc(size*sizeof(char_t));
		if(m_array)
		{
			m_size = size;
			m_length = size - 1;
			scwCopy(cwstring, m_array, m_length);
			m_array[m_length] = NullWChar;
		}
	}
}
WString::WString(const WString::char_t* cstring, size_t length, size_t offset) :
	m_length(0U),
	m_size(0U)
{
	const size_t size = length + 1U;
	if(size == 0)
		m_array = NullWStr;
	else if(size > 0)
	{
		m_array = (char_t*) malloc(size*sizeof(char_t));
		if(m_array)
		{
			m_size = size;
			m_length = size - 1;
			scwCopy(cstring, m_array, m_length, offset);
			m_array[m_length] = NullWChar;
		}
	}
}
WString::WString(const WString& tocopy) :
	m_length(0U),
	m_size(0U)
{
	const size_t size = tocopy.m_length + 1U;
	if(size == 0)
		m_array = NullWStr;
	else if(size > 0)
	{
		m_array = (char_t*) malloc(size*sizeof(char_t));
		if(m_array)
		{
			m_size = size;
			m_length = size - 1;
			scwCopy(tocopy.m_array, m_array, m_length);
			m_array[m_length] = NullWChar;
		}
	}
}
WString::WString(const WString& tocopy, size_t length, size_t offset) :
	m_length(0U),
	m_size(0U)
{
	const size_t tocopy_len = (offset <= tocopy.m_length ? (tocopy.m_length - offset) : 0U);
	const size_t size = (offset <= tocopy.m_length ? ((length > tocopy_len ? tocopy_len : length) + 1U) : 1U);
	if(size == 0)
		m_array = NullWStr;
	else if(size > 0)
	{
		m_array = (char_t*) malloc(size*sizeof(char_t));
		if(m_array)
		{
			m_size = size;
			m_length = size - 1;
			scwCopy(tocopy.m_array, m_array, m_length, offset);
			m_array[m_length] = NullWChar;
		}
	}
}
WString::WString(const String& tocopy) :
	m_length(0U),
	m_size(0U)
{
	const size_t size = tocopy.length() + 1U;
	if(size == 0)
		m_array = NullWStr;
	else if(size > 0)
	{
		m_array = (char_t*) malloc(size*sizeof(char_t));
		if(m_array)
		{
			m_size = size;
			m_length = size - 1;
			scCopy(tocopy.cstr(), m_array, m_length);
			m_array[m_length] = NullWChar;
		}
	}
}
WString::WString(const String& tocopy, size_t length, size_t offset) :
	m_length(0U),
	m_size(0U)
{
	const size_t str_len = tocopy.length();
	const size_t tocopy_len = (offset <= str_len ? (str_len - offset) : 0U);
	const size_t size = (offset <= str_len ? ((length > tocopy_len ? tocopy_len : length) + 1U) : 1U);
	if(size == 0)
		m_array = NullWStr;
	else if(size > 0)
	{
		m_array = (char_t*) malloc(size*sizeof(char_t));
		if(m_array)
		{
			m_size = size;
			m_length = size - 1;
			scCopy(tocopy.cstr(), m_array, m_length, offset);
			m_array[m_length] = NullWChar;
		}
	}
}
#if (__cplusplus >= 201103)
WString::WString(WString&& tomove) :
	m_array(tomove.m_array),
	m_length(tomove.m_length),
	m_size(tomove.m_size)
{
	tomove.m_array = NullWStr;
}
#endif
WString::~WString()
{
	this->destroy();
}

#if (__cplusplus >= 201103)
WString& WString::operator=(WString&& tomove) 
{
	this->destroy();
	this->m_length = tomove.m_length;
	this->m_size = tomove.m_size;
	this->m_array = tomove.m_array;
	tomove.m_array = NullWStr;
	return *this;
}
#endif
WString& WString::operator=(const WString& tocopy)
{
	const size_t size = tocopy.m_length + 1U;
	this->destroy();
	if(size == 0)
		m_array = NullWStr;
	else if(size > 0)
	{
		m_array = (char_t*) malloc(size*sizeof(char_t));
		if(m_array)
		{
			m_size = size;
			m_length = size - 1;
			scwCopy(tocopy.m_array, m_array, m_length);
			m_array[m_length] = NullWChar;
		}
	}
	return *this;
}
WString& WString::operator=(const String& tocopy)
{
	const size_t size = tocopy.length() + 1U;
	this->destroy();
	if(size == 0)
		m_array = NullWStr;
	else if(size > 0)
	{
		m_array = (char_t*) malloc(size*sizeof(char_t));
		if(m_array)
		{
			m_size = size;
			m_length = size - 1;
			scCopy(tocopy.cstr(), m_array, m_length);
			m_array[m_length] = NullWChar;
		}
	}
	return *this;
}
WString& WString::operator=(const WString::char_t* cstring)
{
	const size_t size = scwLength(cstring) + 1U;
	if(size == 0)
	{
		this->destroy();
	}
	else if(size > 0)
	{
		if(this->resize(size - 1) && m_array && m_size >= size)
		{
			m_length = size - 1;
			scwCopy(cstring, m_array, m_length);
			m_array[m_length] = NullWChar;
		}
	}
	return *this;
}

const WString::char_t& WString::operator[](size_t index) const 
{
	return m_array[index];
}
WString::char_t& WString::operator[](size_t index) 
{
	return m_array[index];
}
WString WString::operator+(const WString& rhs) const
{
	const size_t total_length = (m_length + rhs.m_length);
	WString appended_str(total_length);
	if(appended_str.m_size == total_length + 1)
	{
		scwCopy(m_array, appended_str.m_array, m_length);
		scwCopy(rhs.m_array, appended_str.m_array, rhs.m_length, 0, m_length);
		appended_str.m_array[total_length] = NullWChar;
		appended_str.m_length = total_length;
	}
	return appended_str;
}
WString WString::operator+(const WString::char_t* rhs) const
{
	const size_t rhs_length = scwLength(rhs);
	const size_t total_length = (m_length + rhs_length);
	WString appended_str(total_length);
	if(appended_str.m_size == total_length + 1)
	{
		scwCopy(m_array, appended_str.m_array, m_length);
		scwCopy(rhs, appended_str.m_array, rhs_length, 0, m_length);
		appended_str.m_array[total_length] = NullWChar;
		appended_str.m_length = total_length;
	}
	return appended_str;
}
WString& WString::operator+=(const WString& rhs)
{
	return this->append(rhs);
}
WString& WString::operator+=(const WString::char_t* rhs)
{
	return this->append(rhs);
}

bool WString::operator==(const WString& rhs) const
{
	if(m_length != rhs.m_length)
		return false;
	for(size_t i = 0U; i < m_length; ++i)
		if(m_array[i] != rhs.m_array[i])
			return false;;
	return true;
}
bool WString::operator!=(const WString& rhs) const
{
	if(m_length != rhs.m_length)
		return true;
	for(size_t i = 0U; i < m_length; ++i)
		if(m_array[i] != rhs.m_array[i])
			return true;;
	return false;
}
bool WString::operator>=(const WString& rhs) const
{
	const size_t min_length = (m_length <= rhs.m_length ? m_length : rhs.m_length);
	for(size_t i = 0U; i < min_length; ++i)
	{
		if(m_array[i] == rhs.m_array[i])
			continue;
		else if(m_array[i] > rhs.m_array[i])
			return true;
		else 
			return false;
	}
	return true;
}
bool WString::operator<=(const WString& rhs) const
{
	const size_t min_length = (m_length <= rhs.m_length ? m_length : rhs.m_length);
	for(size_t i = 0U; i < min_length; ++i)
	{
		if(m_array[i] == rhs.m_array[i])
			continue;
		else if(m_array[i] < rhs.m_array[i])
			return true;
		else 
			return false;
	}
	return true;
}
bool WString::operator>(const WString& rhs) const
{
	const size_t min_length = (m_length <= rhs.m_length ? m_length : rhs.m_length);
	for(size_t i = 0U; i < min_length; ++i)
	{
		if(m_array[i] == rhs.m_array[i])
			continue;
		else if(m_array[i] > rhs.m_array[i])
			return true;
		else 
			return false;
	}
	return false;
}
bool WString::operator<(const WString& rhs) const
{
	const size_t min_length = (m_length <= rhs.m_length ? m_length : rhs.m_length);
	for(size_t i = 0U; i < min_length; ++i)
	{
		if(m_array[i] == rhs.m_array[i])
			continue;
		else if(m_array[i] < rhs.m_array[i])
			return true;
		else 
			return false;
	}
	return false;
}

size_t WString::length() const
{
	return m_length;
}
size_t WString::length(bool check)
{
	if(check)
		m_length = (m_array ? scwLength(m_array, m_size) : 0U);
	return m_length;
}
size_t WString::size() const
{
	return m_size;
}
bool WString::isNull() const
{
	return !m_array || m_array[0] == NullWChar;
}
const WString::char_t* WString::cwstr() const
{
	return m_array;
}
WString::char_t* WString::wstr()
{
	return m_array;
}
WString::char_t** WString::pwstr()
{
	return &m_array;
}

void WString::destroy()
{
	if(m_array)
	{
		free(m_array);
		m_array = NullWStr;
		m_size = 0U;
		m_length = 0U;
	}
}
bool WString::resize(size_t new_length)
{
	const size_t new_size = new_length + 1U;
	if(new_size == m_size) return true;
	if(m_array)
	{
		void* new_array = realloc(m_array, new_size * sizeof(char_t));
		if(!new_array)
			return false;
		else
		{
			m_array = (char_t*) new_array;
			m_size = new_size;
			m_length = (m_length <= new_length ? m_length : new_length);
			m_array[m_length] = NullWChar;
			return true;
		}
	}
	else
	{
		m_array = (char_t*) malloc(new_size * sizeof(char_t));
		if(!m_array)
			return false;
		else
		{
			m_size = new_size;
			m_length = 0U;
			m_array[m_length] = NullWChar;
			return true;
		}
	}
	return false;
}
WString& WString::append(const WString& toappend)
{
	const size_t new_length = (m_length + toappend.m_length);
	const size_t new_size = new_length + 1U;
	if(this->resize(new_length) && m_size == new_size)
	{
		scwCopy(toappend.cwstr(), m_array, toappend.m_length, 0, m_length);
		m_length = new_length;
		m_array[m_length] = NullWChar;
	}
	return *this;
}
WString& WString::append(const WString& toappend, size_t length, size_t offset)
{
	const size_t max_append_len = (offset <= toappend.m_length ? (toappend.m_length - offset) : 0U);
	const size_t toappend_len = (length == 0U || length > max_append_len ? max_append_len : length);
	if(toappend_len == 0)
		return *this;
	const size_t new_length = (m_length + toappend_len);
	const size_t new_size = new_length + 1U;
	if(this->resize(new_length) && m_size == new_size)
	{
		scwCopy(toappend.cwstr(), m_array, toappend_len, offset, m_length);
		m_length = new_length;
		m_array[m_length] = NullWChar;
	}
	return *this;
}
WString& WString::append(const WString::char_t* cstring)
{
	const size_t cstr_length = scwLength(cstring);
	const size_t new_length = (m_length + cstr_length);
	const size_t new_size = new_length + 1U;
	if(this->resize(new_length) && m_size == new_size)
	{
		scwCopy(cstring, m_array, cstr_length, 0, m_length);
		m_length = new_length;
		m_array[m_length] = NullWChar;
	}
	return *this;
}
WString& WString::append(const WString::char_t* cstring, size_t length, size_t offset)
{
	if(length == 0U)
		length = scwLength(cstring);
	if(length == 0U) return *this;
	const size_t new_length = (m_length + length);
	const size_t new_size = new_length + 1U;
	if(this->resize(new_length) && m_size == new_size)
	{
		scwCopy(cstring, m_array, length, offset, m_length);
		m_length = new_length;
		m_array[m_length] = NullWChar;
	}
	return *this;
}
WString WString::substring(size_t length, size_t offset) const
{
	return WString(*this, length, offset);
}
WString WString::reverse() const
{
	const size_t last_index = m_length - 1U;
	WString rev_str(m_length);
	if(rev_str.m_size >= m_length + 1U)
	{
		for(size_t i = 0U; i < m_length; ++i)
		{
			rev_str.m_array[i] = m_array[last_index - i];
		}
		rev_str.m_length = m_length;
		rev_str.m_array[m_length] = NullWChar;
	}
	return rev_str;
}
WString WString::toUpper() const
{
	const static char_t diff = (char_t)'A' - (char_t)'a';
	WString upper_str(m_length);
	if(upper_str.m_size >= m_length + 1U)
	{
		char_t m_char;
		for(size_t i = 0U; i < m_length; ++i)
		{
			m_char = m_array[i];
			upper_str.m_array[i] = ((m_char >= (char_t)'a' && m_char <= (char_t)'z') ? (m_char + diff) : m_char);
		}
		upper_str.m_length = m_length;
		upper_str.m_array[m_length] = NullWChar;
	}
	return upper_str;
}
WString WString::toLower() const
{
	const static char_t diff = (char_t)'A' - (char_t)'a';
	WString lower_str(m_length);
	if(lower_str.m_size >= m_length + 1U)
	{
		char_t m_char;
		for(size_t i = 0U; i < m_length; ++i)
		{
			m_char = m_array[i];
			lower_str.m_array[i] = ((m_char >= (char_t)'A' && m_char <= (char_t)'Z') ? (m_char - diff) : m_char);
		}
		lower_str.m_length = m_length;
		lower_str.m_array[m_length] = NullWChar;
	}
	return lower_str;
}
WString& WString::format(const char_t* format, ...)
{
	if (!m_array || m_size == 0) return *this;
	va_list args;
	va_start(args, format);
#ifdef _MSC_VER
	m_length = vswprintf_s(m_array, (m_size - 1), format, args);
#else
#	if ((defined(__MINGW32_VERSION) && __MINGW32_VERSION > 5000002L)) || (!defined(__MINGW32_VERSION) && __cplusplus >= 201103)
	m_length = vswprintf(m_array, (m_size - 1), format, args);
#	else
	m_length = vswprintf(m_array, format, args);
#	endif
#endif
	va_end(args);
	this->length(true);
	return *this;
}
String WString::toString() const
{
	String str(m_length);
#ifdef _MSC_VER
	if(m_array && str.size() == m_length + 1U)
		wcstombs_s(NULL, str.str(), m_length + 1U, m_array, m_length + 1U);
#else
	if(m_array && str.size() == m_length + 1U)
		std::wcstombs(str.str(), m_array, m_length + 1U);
#endif
	str.m_length = m_length;
	return str;
}

WString WString::Format(size_t length, const char_t* format, ...)
{
	WString str(length);
	va_list args;
	va_start(args, format);
#ifdef _MSC_VER
	vswprintf_s(str.m_array, (str.m_size - 1), format, args);
#else
#	if ((defined(__MINGW32_VERSION) && __MINGW32_VERSION > 5000002L)) || (!defined(__MINGW32_VERSION) && __cplusplus >= 201103)
	m_length = vswprintf(str.m_array, (str.m_size - 1), format, args);
#	else
	m_length = vswprintf(str.m_array, format, args);
#	endif
#endif
	va_end(args);
	str.length(true);
	return str;
}
size_t WString::scwLength(const WString::char_t* cwstr, size_t max)
{
	if(!cwstr) return 0U;
	size_t cw_len = 0U;
	for(size_t i = 0U; i < max; ++i)
	{
		switch(cwstr[i])
		{
			case (char_t)L'\0': return cw_len;
			default: ++cw_len; continue;
		}
	}
	return cw_len;
}
WString::char_t* WString::scwCopy(const WString::char_t* src, WString::char_t* dest, size_t length, size_t src_offset, size_t dest_offset)
{
	if(!src || !dest) return dest;
	const char_t *ac_src = &src[src_offset];
	char_t *ac_dest = &dest[dest_offset];
	for(size_t i = 0U; i < length; ++i)
		ac_dest[i] = ac_src[i];
	return dest;
}
WString::char_t* WString::scCopy(const String::char_t* src, WString::char_t* dest, size_t length, size_t src_offset, size_t dest_offset)
{
	if(!src || !dest) return dest;
	const String::char_t *ac_src = &src[src_offset];
	char_t *ac_dest = &dest[dest_offset];
	for(size_t i = 0U; i < length; ++i)
		ac_dest[i] = (char_t)ac_src[i];
	return dest;
}
bool WString::scwEquals(const WString::char_t* cwstr1, const WString::char_t* cwstr2)
{
	if(!cwstr1 || !cwstr2) return false;
	for(size_t i = 0; i < (size_t)-1; ++i)
	{
		if((cwstr1[i] == L'\0') && (cwstr2[i] == L'\0'))
			return true;
		else if((cwstr1[i] == L'\0') ^ (cwstr2[i] == L'\0'))
			return false;
		else if(cwstr1[i] != cwstr2[i])
			return false;
	}
	return false;
}

} // namespace axl.util
} // namespace axl