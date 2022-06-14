#include <limits>

#include <msw/buffer_view.hpp>

#include "common.hpp"
#include "utest.h"

UTEST(buffer_view, construct_buffer)
{
	const size_t size = 4096;

	msw::buffer buf{ size };
	for (int i = 0; i < size; ++i)
	{
		buf[i] = (char)i;
	}

	msw::buffer_view buf_view{ buf };

	ASSERT_EQ(buf.size(), buf_view.size());
	ASSERT_EQ(buf.data(), buf_view.data());
	ASSERT_EQ(buf.begin(), buf_view.begin());
	ASSERT_EQ(buf.end(), buf_view.end());

	for (int i = 0; i < size; ++i)
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

	for (int i = 0; i < size; ++i)
	{
		ASSERT_EQ(raw_buf[i], buf_view[i]);
	}

	delete[] raw_buf;
}
