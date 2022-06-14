#include <limits>

#include <msw/buffer_view.hpp>

#include "common.hpp"
#include "utest.h"

UTEST(buffer_view, construct_buffer)
{
	const size_t size = 4096;

	msw::buffer buf{ size };
	for (size_t i = 0; i < size; ++i)
	{
		buf[i] = (char)i;
	}

	msw::buffer_view buf_view{ buf };

	ASSERT_EQ(buf.size(), buf_view.size());
	ASSERT_EQ(buf.data(), buf_view.data());
	ASSERT_EQ(buf.begin(), buf_view.begin());
	ASSERT_EQ(buf.end(), buf_view.end());

	for (size_t i = 0; i < size; ++i)
	{
		ASSERT_EQ(buf[i], buf_view[i]);
	}
}

UTEST(buffer_view, construct_data_size)
{
	using Byte = msw::buffer_view::value_type;

	const size_t size = 4096;
	auto raw_buf = new Byte[size];
	for (size_t i = 0; i < size; ++i)
	{
		raw_buf[i] = (Byte)(i % std::numeric_limits<Byte>::max());
	}

	msw::buffer_view buf_view{ raw_buf, size };

	ASSERT_EQ(size, buf_view.size());
	ASSERT_EQ(raw_buf, buf_view.data());
	ASSERT_EQ(raw_buf, buf_view.begin());
	ASSERT_EQ(raw_buf + size, buf_view.end());

	for (size_t i = 0; i < size; ++i)
	{
		ASSERT_EQ(raw_buf[i], buf_view[i]);
	}

	delete[] raw_buf;
}

UTEST(buffer_view, make_buffer_view)
{
	std::string s{ "std::string" };
	auto sv = msw::make_buffer_view<char>(s.begin(), s.end());

	ASSERT_EQ(s.size(), sv.size());

	for (size_t i = 0; i < s.size(); ++i)
	{
		ASSERT_EQ(s[i], sv[i]);
	}
}

UTEST(buffer_view, string)
{
	using string_view = msw::basic_buffer_view<std::string::value_type>;

	std::string s{ "std::string" };
	string_view sv{ s.data(), s.size() };

	for (size_t i = 0; i < s.size(); ++i)
	{
		ASSERT_EQ(s[i], sv[i]);
	}
}

UTEST(buffer_view, string_view)
{
	std::string_view sv{ "std::string_view" };
	msw::buffer_view bv{ sv.begin(), sv.end() };

	for (size_t i = 0; i < sv.size(); ++i)
	{
		ASSERT_EQ(sv[i], bv[i]);
	}
}

UTEST(buffer_view, vector)
{
	using vector_view = msw::basic_buffer_view<std::vector<int>::value_type>;

	std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector_view vec_view{ v.data(), v.size() };

	for (size_t i = 0; i < v.size(); ++i)
	{
		ASSERT_EQ(v[i], vec_view[i]);
	}
}
