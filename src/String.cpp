#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <axl.util/lib.hpp>
#include <axl.util/String.hpp>

namespace axl {
namespace util {

const String::char_t*const String::NullCStr = (const String::char_t*)0;
String::char_t*const String::NullStr = (String::char_t*)0;
const String::char_t String::NullChar = (String::char_t)'\0';

String::String(size_t length) :
	m_length(0U),
	m_size(0U)
{
	const size_t size = length + 1U;
	if(size == 0)
		m_array = NullStr;
	else if(size > 0)
	{
		m_array = (char_t*) malloc(size*sizeof(char_t));
		if(m_array)
		{
			m_size = size;
			m_array[0] = NullChar;
		}
	}
}
String::String(const String::char_t* cstring) :
	m_length(0U),
	m_size(0U)
{
	const size_t size = scLength(cstring) + 1U;
	if(size == 0)
		m_array = NullStr;
	else if(size > 0)
	{
		m_array = (char_t*) malloc(size*sizeof(char_t));
		if(m_array)
		{
			m_size = size;
			m_length = size - 1;
			scCopy(cstring, m_array, m_length);
			m_array[m_length] = NullChar;
		}
	}
}
String::String(const String::char_t* cstring, size_t length, size_t offset) :
	m_length(0U),
	m_size(0U)
{
	const size_t size = length + 1U;
	if(size == 0)
		m_array = NullStr;
	else if(size > 0)
	{
		m_array = (char_t*) malloc(size*sizeof(char_t));
		if(m_array)
		{
			m_size = size;
			m_length = size - 1;
			scCopy(cstring, m_array, m_length, offset);
			m_array[m_length] = NullChar;
		}
	}
}
String::String(const String& tocopy) :
	m_length(0U),
	m_size(0U)
{
	const size_t size = tocopy.m_length + 1U;
	if(size == 0)
		m_array = NullStr;
	else if(size > 0)
	{
		m_array = (char_t*) malloc(size*sizeof(char_t));
		if(m_array)
		{
			m_size = size;
			m_length = size - 1;
			scCopy(tocopy.m_array, m_array, m_length);
			m_array[m_length] = NullChar;
		}
	}
}
String::String(const String& tocopy, size_t length, size_t offset) :
	m_length(0U),
	m_size(0U)
{
	const size_t tocopy_len = (offset <= tocopy.m_length ? (tocopy.m_length - offset) : 0U);
	const size_t size = (offset <= tocopy.m_length ? ((length > tocopy_len ? tocopy_len : length) + 1U) : 1U);
	if(size == 0)
		m_array = NullStr;
	else if(size > 0)
	{
		m_array = (char_t*) malloc(size*sizeof(char_t));
		if(m_array)
		{
			m_size = size;
			m_length = size - 1;
			scCopy(tocopy.m_array, m_array, m_length, offset);
			m_array[m_length] = NullChar;
		}
	}
}
#if (__cplusplus >= 201103)
String::String(String&& tomove) :
	m_array(tomove.m_array),
	m_length(tomove.m_length),
	m_size(tomove.m_size)
{
	tomove.m_array = NullStr;
}
#endif
String::~String()
{
	this->destroy();
}

#if (__cplusplus >= 201103)
String& String::operator=(String&& tomove) 
{
	this->destroy();
	this->m_length = tomove.m_length;
	this->m_size = tomove.m_size;
	this->m_array = tomove.m_array;
	tomove.m_array = NullStr;
	return *this;
}
#endif
String& String::operator=(const String& tocopy)
{
	const size_t size = tocopy.m_length + 1U;
	this->destroy();
	if(size == 0)
		m_array = NullStr;
	else if(size > 0)
	{
		m_array = (char_t*) malloc(size*sizeof(char_t));
		if(m_array)
		{
			m_size = size;
			m_length = size - 1;
			scCopy(tocopy.m_array, m_array, m_length);
			m_array[m_length] = NullChar;
		}
	}
	return *this;
}
String& String::operator=(const String::char_t* cstring)
{
	const size_t size = scLength(cstring) + 1U;
	if(size == 0)
	{
		this->destroy();
	}
	else if(size > 0)
	{
		if(this->resize(size - 1) && m_array && m_size >= size)
		{
			m_length = size - 1;
			scCopy(cstring, m_array, m_length);
			m_array[m_length] = NullChar;
		}
	}
	return *this;
}

const String::char_t& String::operator[](size_t index) const 
{
	return m_array[index];
}
String::char_t& String::operator[](size_t index) 
{
	return m_array[index];
}
String String::operator+(const String& rhs) const
{
	const size_t total_length = (m_length + rhs.m_length);
	String appended_str(total_length);
	if(appended_str.m_size == total_length + 1)
	{
		scCopy(m_array, appended_str.m_array, m_length);
		scCopy(rhs.m_array, appended_str.m_array, rhs.m_length, 0, m_length);
		appended_str.m_array[total_length] = NullChar;
		appended_str.m_length = total_length;
	}
	return appended_str;
}
String String::operator+(const String::char_t* rhs) const
{
	const size_t rhs_length = scLength(rhs);
	const size_t total_length = (m_length + rhs_length);
	String appended_str(total_length);
	if(appended_str.m_size == total_length + 1)
	{
		scCopy(m_array, appended_str.m_array, m_length);
		scCopy(rhs, appended_str.m_array, rhs_length, 0, m_length);
		appended_str.m_array[total_length] = NullChar;
		appended_str.m_length = total_length;
	}
	return appended_str;
}
String& String::operator+=(const String& rhs)
{
	return this->append(rhs);
}
String& String::operator+=(const String::char_t* rhs)
{
	return this->append(rhs);
}

bool String::operator==(const String& rhs) const
{
	if(m_length != rhs.m_length)
		return false;
	for(size_t i = 0U; i < m_length; ++i)
		if(m_array[i] != rhs.m_array[i])
			return false;;
	return true;
}
bool String::operator!=(const String& rhs) const
{
	if(m_length != rhs.m_length)
		return true;
	for(size_t i = 0U; i < m_length; ++i)
		if(m_array[i] != rhs.m_array[i])
			return true;;
	return false;
}
bool String::operator>=(const String& rhs) const
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
bool String::operator<=(const String& rhs) const
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
bool String::operator>(const String& rhs) const
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
bool String::operator<(const String& rhs) const
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

size_t String::length() const
{
	return m_length;
}
size_t String::length(bool check)
{
	if(check)
		m_length = (m_array ? scLength(m_array, m_size) : 0U);
	return m_length;
}
size_t String::size() const
{
	return m_size;
}
bool String::isNull() const
{
	return !m_array || m_array[0] == NullChar;
}
const String::char_t* String::cstr() const
{
	return m_array;
}
String::char_t* String::str()
{
	return m_array;
}
String::char_t** String::pstr()
{
	return &m_array;
}

void String::destroy()
{
	if(m_array)
	{
		free(m_array);
		m_array = NullStr;
		m_size = 0U;
		m_length = 0U;
	}
}
bool String::resize(size_t new_length)
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
			m_array[m_length] = NullChar;
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
			m_array[m_length] = NullChar;
			return true;
		}
	}
	return false;
}
String& String::append(const String& toappend)
{
	const size_t new_length = (m_length + toappend.m_length);
	const size_t new_size = new_length + 1U;
	if(this->resize(new_length) && m_size == new_size)
	{
		scCopy(toappend.cstr(), m_array, toappend.m_length, 0, m_length);
		m_length = new_length;
		m_array[m_length] = NullChar;
	}
	return *this;
}
String& String::append(const String& toappend, size_t length, size_t offset)
{
	const size_t max_append_len = (offset <= toappend.m_length ? (toappend.m_length - offset) : 0U);
	const size_t toappend_len = (length == 0U || length > max_append_len ? max_append_len : length);
	if(toappend_len == 0)
		return *this;
	const size_t new_length = (m_length + toappend_len);
	const size_t new_size = new_length + 1U;
	if(this->resize(new_length) && m_size == new_size)
	{
		scCopy(toappend.cstr(), m_array, toappend_len, offset, m_length);
		m_length = new_length;
		m_array[m_length] = NullChar;
	}
	return *this;
}
String& String::append(const String::char_t* cstring)
{
	const size_t cstr_length = scLength(cstring);
	const size_t new_length = (m_length + cstr_length);
	const size_t new_size = new_length + 1U;
	if(this->resize(new_length) && m_size == new_size)
	{
		scCopy(cstring, m_array, cstr_length, 0, m_length);
		m_length = new_length;
		m_array[m_length] = NullChar;
	}
	return *this;
}
String& String::append(const String::char_t* cstring, size_t length, size_t offset)
{
	if(length == 0U)
		length = scLength(cstring);
	if(length == 0U) return *this;
	const size_t new_length = (m_length + length);
	const size_t new_size = new_length + 1U;
	if(this->resize(new_length) && m_size == new_size)
	{
		scCopy(cstring, m_array, length, offset, m_length);
		m_length = new_length;
		m_array[m_length] = NullChar;
	}
	return *this;
}
String String::substring(size_t length, size_t offset) const
{
	return String(*this, length, offset);
}
String String::reverse() const
{
	const size_t last_index = m_length - 1U;
	String rev_str(m_length);
	if(rev_str.m_size >= m_length + 1U)
	{
		for(size_t i = 0U; i < m_length; ++i)
		{
			rev_str.m_array[i] = m_array[last_index - i];
		}
		rev_str.m_length = m_length;
		rev_str.m_array[m_length] = NullChar;
	}
	return rev_str;
}
String String::toUpper() const
{
	const static char_t diff = (char_t)'A' - (char_t)'a';
	String upper_str(m_length);
	if(upper_str.m_size >= m_length + 1U)
	{
		char_t m_char;
		for(size_t i = 0U; i < m_length; ++i)
		{
			m_char = m_array[i];
			upper_str.m_array[i] = ((m_char >= (char_t)'a' && m_char <= (char_t)'z') ? (m_char + diff) : m_char);
		}
		upper_str.m_length = m_length;
		upper_str.m_array[m_length] = NullChar;
	}
	return upper_str;
}
String String::toLower() const
{
	const static char_t diff = (char_t)'A' - (char_t)'a';
	String lower_str(m_length);
	if(lower_str.m_size >= m_length + 1U)
	{
		char_t m_char;
		for(size_t i = 0U; i < m_length; ++i)
		{
			m_char = m_array[i];
			lower_str.m_array[i] = ((m_char >= (char_t)'A' && m_char <= (char_t)'Z') ? (m_char - diff) : m_char);
		}
		lower_str.m_length = m_length;
		lower_str.m_array[m_length] = NullChar;
	}
	return lower_str;
}
String& String::format(const char_t* format, ...)
{
	if (!m_array || m_size == 0) return *this;
	va_list args;
	va_start(args, format);
#ifdef _MSC_VER
	m_length = vsprintf_s(m_array, (m_size-1), format, args);
#else
#	if __cplusplus >= 201103
	m_length = vsnprintf(m_array, (m_size-1), format, args);
#	else
	m_length = vsprintf(m_array, format, args);
#	endif
#endif
	va_end(args);
	this->length(true);
	return *this;
}
String String::Format(size_t length, const char_t* format, ...)
{
	String str(length);
	va_list args;
	va_start(args, format);
#ifdef _MSC_VER
	vsprintf_s(str.m_array, (str.m_size-1), format, args);
#else
#	if __cplusplus >= 201103
	m_length = vsnprintf(str.m_array, (str.m_size-1), format, args);
#	else
	m_length = vsprintf(str.m_array, format, args);
#	endif
#endif
	va_end(args);
	str.length(true);
	return str;
}

size_t String::scLength(const String::char_t* cstr, size_t max)
{
	if(!cstr) return 0U;
	size_t c_len = 0U;
	for(size_t i = 0U; i < max; ++i)
	{
		switch(cstr[i])
		{
			case (char_t)'\0': return c_len;
			default: ++c_len; continue;
		}
	}
	return c_len;
}
String::char_t* String::scCopy(const String::char_t* src, String::char_t* dest, size_t length, size_t src_offset, size_t dest_offset)
{
	if(!src || !dest) return dest;
	const char_t *ac_src = &src[src_offset];
	char_t *ac_dest = &dest[dest_offset];
	for(size_t i = 0U; i < length; ++i)
		ac_dest[i] = ac_src[i];
	return dest;
}
bool String::scEquals(const String::char_t* cstr1, const String::char_t* cstr2)
{
	if(!cstr1 || !cstr2) return false;
	for(size_t i = 0; i < (size_t)-1; ++i)
	{
		if((cstr1[i] == '\0') && (cstr2[i] == '\0'))
			return true;
		else if((cstr1[i] == '\0') ^ (cstr2[i] == '\0'))
			return false;
		else if(cstr1[i] != cstr2[i])
			return false;
	}
	return false;
}

} // namespace axl.util
} // namespace axl