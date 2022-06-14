#include <limits>

#include <msw/buffer.hpp>

#include "common.hpp"
#include "utest.h"

UTEST(buffer, construct_size)
{
	const size_t size = 4096;

	msw::buffer buf{ size };
	ASSERT_EQ(size, buf.size());
	ASSERT_TRUE(buf.data());
}

UTEST(buffer, construct_data_size)
{
	using byte = msw::buffer::value_type;
	const size_t size = std::numeric_limits<byte>::max();

	auto raw_buf = new byte[size];
	for (size_t i = 0; i < size; ++i)
	{
		raw_buf[i] = (byte)(i % std::numeric_limits<byte>::max());
	}

	msw::buffer buf{ raw_buf, size };
	ASSERT_NE(raw_buf, buf.data());
	ASSERT_EQ(size, buf.size());

	delete[] raw_buf;

	for (size_t i = 0; i < buf.size(); ++i)
	{
		ASSERT_EQ((byte)i, buf[i]);
	}
}

UTEST(buffer, begin_end)
{
	const size_t size = 4096;

	msw::buffer buf{ size };
	ASSERT_EQ(buf.data(), buf.begin());
	ASSERT_EQ((buf.data() + buf.size()), buf.end());
	ASSERT_LT(buf.begin(), buf.end());
	ASSERT_EQ(size, (size_t)(buf.end() - buf.begin()));
}

UTEST(buffer, cbegin_cend)
{
	const size_t size = 4096;

	msw::buffer buf{ size };
	const msw::buffer &const_buf = buf;

	ASSERT_EQ(const_buf.begin(), buf.cbegin());
	ASSERT_EQ(buf.end(), buf.cend());

	ASSERT_EQ(buf.begin(), const_buf.begin());
	ASSERT_EQ(buf.end(), const_buf.end());

	ASSERT_EQ(const_buf.begin(), const_buf.cbegin());
	ASSERT_EQ(const_buf.end(), const_buf.cend());
}

UTEST(buffer, resize)
{
	size_t size = 1;

	msw::buffer buf{ size };

	for (size_t i = 0; i < 8; ++i)
	{
		ASSERT_EQ(size, buf.size());
		ASSERT_TRUE(buf.data());

		size *= 2;
		buf.resize(size);
	}
}

UTEST(buffer, clear)
{
	const size_t size = 4096;

	msw::buffer buf{ size };
	buf.clear();

	ASSERT_FALSE(buf.data());
	ASSERT_TRUE(buf.empty());
	ASSERT_EQ(buf.size(), 0ul);
}
