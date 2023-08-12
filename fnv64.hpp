/* -------------------------------------------------------------------------------------------------
*
* FNV HASH 64
* ===========
*
* This file:
*    fnv64 C++ header-only
*
* Authors:
*    Fabio Galuppo
*
* Releases: August 12 2023 - v0.1
*    v0.1 - August 2023 - initial release
*
* The MIT License (MIT)
* Copyright © 2023 Fabio Galuppo
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the “Software”), to deal in the Software without
* restriction, including without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
------------------------------------------------------------------------------------------------- */

#ifndef FNV64_HPP
#define FNV64_HPP

#include <cstddef>
#include <cstdint>
#include <string>

namespace fnv64
{
	namespace internal
	{
		static constexpr std::uint64_t shift_sum(std::uint64_t hashval)
		{
			return (hashval << 1) + (hashval << 4) + (hashval << 5) +
				(hashval << 7) + (hashval << 8) + (hashval << 40);
		}
	}

	static const std::uint64_t FNV1_64_INIT = 0xcbf29ce484222325ULL;
	static const std::uint64_t FNV1A_64_INIT = FNV1_64_INIT;

	//FNV-1 hash
	static std::uint64_t fnv1_hash(void* buf, std::size_t size, std::uint64_t hashval = FNV1_64_INIT)
	{
		unsigned char* first = reinterpret_cast<unsigned char*>(buf);
		unsigned char* last = first + size;
		while (first < last)
		{
			hashval += internal::shift_sum(hashval);
			hashval ^= static_cast<std::uint64_t>(*first++);
		}
		return hashval;
	}

	//FNV-1 hash
	static inline std::uint64_t fnv1_hash(std::size_t n, void* buf, std::size_t size, std::uint64_t hashval = FNV1_64_INIT)
	{
		for (std::size_t i = 0; i < n; ++i) hashval = fnv1_hash(buf, size, hashval);
		return hashval;
	}

	//FNV-1 hash
	static inline std::uint64_t fnv1_hash(const char* buf, std::size_t size, std::uint64_t hashval = FNV1_64_INIT)
	{
		return fnv1_hash(reinterpret_cast<void*>(const_cast<char*>(buf)), size, hashval);
	}

	//FNV-1 hash
	static inline std::uint64_t fnv1_hash(std::size_t n, const char* buf, std::size_t size, std::uint64_t hashval = FNV1_64_INIT)
	{
		for (std::size_t i = 0; i < n; ++i) hashval = fnv1_hash(reinterpret_cast<void*>(const_cast<char*>(buf)), size, hashval);
		return hashval;
	}

	//FNV-1 hash
	static inline std::uint64_t fnv1_hash(const std::string& s, std::uint64_t hashval = FNV1_64_INIT)
	{
		return fnv1_hash(s.c_str(), s.size(), hashval);
	}

	//FNV-1 hash
	static inline std::uint64_t fnv1_hash(std::size_t n, const std::string& s, std::uint64_t hashval = FNV1_64_INIT)
	{
		for (std::size_t i = 0; i < n; ++i) hashval = fnv1_hash(s.c_str(), s.size(), hashval);
		return hashval;
	}

	//FNV-1a hash
	static std::uint64_t fnv1a_hash(void* buf, std::size_t size, std::uint64_t hashval = FNV1A_64_INIT)
	{
		unsigned char* first = reinterpret_cast<unsigned char*>(buf);
		unsigned char* last = first + size;
		while (first < last)
		{
			hashval ^= static_cast<std::uint64_t>(*first++);
			hashval += internal::shift_sum(hashval);
		}
		return hashval;
	}

	//FNV-1a hash
	static inline std::uint64_t fnv1a_hash(std::size_t n, void* buf, std::size_t size, std::uint64_t hashval = FNV1_64_INIT)
	{
		for (std::size_t i = 0; i < n; ++i) hashval = fnv1a_hash(buf, size, hashval);
		return hashval;
	}

	//FNV-1a hash
	static inline std::uint64_t fnv1a_hash(const char* buf, std::size_t size, std::uint64_t hashval = FNV1A_64_INIT)
	{
		return fnv1a_hash(reinterpret_cast<void*>(const_cast<char*>(buf)), size, hashval);
	}

	//FNV-1a hash
	static inline std::uint64_t fnv1a_hash(std::size_t n, const char* buf, std::size_t size, std::uint64_t hashval = FNV1A_64_INIT)
	{
		for (std::size_t i = 0; i < n; ++i) hashval = fnv1a_hash(buf, size, hashval);
		return hashval;
	}

	//FNV-1a hash
	static inline std::uint64_t fnv1a_hash(const std::string& s, std::uint64_t hashval = FNV1_64_INIT)
	{
		return fnv1a_hash(s.c_str(), s.size(), hashval);
	}

	//FNV-1a hash
	static inline std::uint64_t fnv1a_hash(std::size_t n, const std::string& s, std::uint64_t hashval = FNV1_64_INIT)
	{
		for (std::size_t i = 0; i < n; ++i) hashval = fnv1a_hash(s, hashval);
		return hashval;
	}
}

#endif /* FNV64_HPP */