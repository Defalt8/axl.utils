#pragma once
#include "lib.hpp"
#include "types.hpp"
#include "String.hpp"

namespace axl {
namespace util {

class AXLUTILCXXAPI WString
{
	public:
		typedef wchar_t char_t;
	public:
		WString(size_t length = 0U);
		WString(const char_t* cwstring);
		WString(const char_t* cwstring, size_t length, size_t offset = 0U);
		WString(const WString& tocopy);
		WString(const WString& tocopy, size_t length, size_t offset = 0U);
		WString(const String& tocopy);
		WString(const String& tocopy, size_t length, size_t offset = 0U);
		#if (__cplusplus >= 201103)
		WString(WString&& tomove);
		#endif
		~WString();
	public:
		#if (__cplusplus >= 201103)
		WString& operator=(WString&& tomove);
		#endif
		WString& operator=(const WString& tocopy);
		WString& operator=(const String& tocopy);
		WString& operator=(const char_t* cwstring);
	public:
		const char_t& operator[](size_t index) const;
		char_t& operator[](size_t index);
		WString operator+(const WString& rhs) const;
		WString operator+(const char_t* rhs) const;
		WString& operator+=(const WString& rhs);
		WString& operator+=(const char_t* rhs);
	public:
		bool operator==(const WString& rhs) const;
		bool operator!=(const WString& rhs) const;
		bool operator>=(const WString& rhs) const;
		bool operator<=(const WString& rhs) const;
		bool operator>(const WString& rhs) const;
		bool operator<(const WString& rhs) const;
	public:
		size_t length() const;
		size_t length(bool check);
		size_t size() const;
		bool isNull() const;
		const char_t* cwstr() const;
		char_t* wstr();
		char_t** pwstr();
	public:
		void destroy();
		bool resize(size_t new_length);
		WString& append(const WString& toappend);
		WString& append(const WString& toappend, size_t length, size_t offset = 0U);
		WString& append(const char_t* cwstring);
		WString& append(const char_t* cwstring, size_t length, size_t offset = 0U);
		WString substring(size_t length, size_t offset = 0U) const;
		WString reverse() const;
		WString toUpper() const;
		WString toLower() const;
		WString& format(const char_t* format, ...);
		String toString() const;
	public:
		static WString Format(size_t length, const char_t* format, ...);
		static size_t scwLength(const WString::char_t* cwstr, size_t max=-1);
		static char_t* scwCopy(const WString::char_t* cwstrsrc, WString::char_t* cwstrdest, size_t length, size_t srcoffset = 0U, size_t destoffset = 0U);
		static char_t* scCopy(const String::char_t* cwstrsrc, WString::char_t* cwstrdest, size_t length, size_t srcoffset = 0U, size_t destoffset = 0U);
		static bool scwEquals(const WString::char_t* cwstr1, const WString::char_t* cwstr2);
	private:
		char_t* m_array;
		size_t m_length;
		size_t m_size;
	public:
		static const char_t*const NullCWStr;
		static char_t*const NullWStr;
		static const char_t NullWChar;
};

} // namespace axl.util
} // namespace axl