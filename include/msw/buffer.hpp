#ifndef MSW_BUFFER_HPP
#define MSW_BUFFER_HPP

#include "config.hpp"

namespace msw
{

template<typename T>
void memcpy(const T *src, T *dst, unsigned long amount)
{
	while (amount-- > 0)
	{
		dst[amount] = src[amount];
	}
}

template<typename T>
T min(const T a, const T b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

template<typename T>
class basic_buffer
{
public:
	using size_type = unsigned long;
	using value_type = T;
	using pointer = T *;
	using const_pointer = const T *;
	using reference = T &;
	using const_reference = const T &;

public:
	/**
	 * @brief Construct a empty buffer
	 * @param size The size of the buffer
	 */
	explicit basic_buffer(const size_type size)
		: m_data{ new value_type[size] }
		, m_size{ size }
	{
	}

	/**
	 * @brief Construct a buffer by copying the data
	 * @param data The data (will be copied!)
	 * @param size The size of the data in bytes
	 */
	basic_buffer(const_pointer data, const size_type size)
	{
		m_data = new value_type[size];
		m_size = size;
		memcpy(data, m_data, m_size);
	}

	/**
	 * @brief Construct a buffer by copying the data
	 * @param begin const_pointer to the beginning of the data
	 * @param end const_pointer to the end of the data
	 */
	basic_buffer(const_pointer begin, const_pointer end)
	{
		m_size = (size_type)(end - begin);
		m_data = new value_type[m_size];
		memcpy(begin, m_data, m_size);
	}

	~basic_buffer()
	{
		clear();
	}

	/**
	 * @brief Sorry! We don't copy buffers, we hate it ;)
	 */
	basic_buffer(const basic_buffer &buffer) = delete;

	/**
	 * @brief Move the buffer
	 */
	basic_buffer(basic_buffer &&buffer) noexcept
	{
		this->operator=((basic_buffer &&) buffer);
	}

public:
	/**
	 * @brief pointer to the beginning of the buffer
	 */
	MSW_NODISCARD pointer begin()
	{
		return m_data;
	}

	/**
	 * @brief const_pointer to the beginning of the buffer
	 */
	MSW_NODISCARD const_pointer begin() const
	{
		return cbegin();
	}

	/**
	 * @brief pointer to the end of the buffer
	 */
	MSW_NODISCARD pointer end()
	{
		return m_data + m_size;
	}

	/**
	  * @brief const_pointer to the end of the buffer
	  */
	MSW_NODISCARD const_pointer end() const
	{
		return cend();
	}

	/**
	 * @brief const_pointer to the beginning of the buffer
	 */
	MSW_NODISCARD const_pointer cbegin() const
	{
		return m_data;
	}

	/**
	 * @brief const_pointer to the end of the buffer
	 */
	MSW_NODISCARD const_pointer cend() const
	{
		return m_data + m_size;
	}

	/**
	 * @brief Resize the buffer
	 * @param new_size The new size of the buffer
	 */
	void resize(const size_type new_size)
	{
		auto new_data = new value_type[new_size];
		memcpy(m_data, new_data, min(m_size, new_size));
		delete[] m_data;

		m_data = new_data;
		m_size = new_size;
	}

	/**
	 * @brief Clear the buffer
	 */
	void clear()
	{
		delete[] m_data;
		m_data = nullptr;
		m_size = 0;
	}

	/**
	 * @return pointer to the data
	 */
	MSW_NODISCARD pointer data()
	{
		return m_data;
	}

	/**
	 * @return const_pointer to the data
	 */
	MSW_NODISCARD const_pointer data() const
	{
		return m_data;
	}

	/**
	 * @return The size of the data
	 */
	MSW_NODISCARD size_type size() const
	{
		return m_size;
	}

	/**
	 * @return True if the buffer is empty, false otherwise
	 */
	MSW_NODISCARD bool empty() const
	{
		return m_size == 0;
	}

	/**
	 * @param index The index of the element in the buffer
	 * @return Reference to the element at index
	 */
	MSW_NODISCARD reference operator[](const size_type index)
	{
		return m_data[index];
	}

	/**
	 * @param index The index of the element in the buffer
	 * @return The element at index
	 */
	MSW_NODISCARD const_reference operator[](const size_type index) const
	{
		return m_data[index];
	}

	/**
	 * @brief Move the buffer
	 */
	basic_buffer &operator=(basic_buffer &&buffer) noexcept
	{
		m_data = buffer.m_data;
		m_size = buffer.m_size;

		buffer.m_data = nullptr;
		buffer.m_size = 0;

		return *this;
	}

private:
	pointer m_data{};
	size_t m_size{};
};

/**
 * @brief Create a buffer with std iterators.
 * Custom iterators work too, but they need a `const T *base()` method
 * 
 * @tparam T value_type for the buffer
 * @tparam Iter The iterator type
 * @param begin The beginning of the range
 * @param end The end of the range
 * @return basic_buffer<T> 
 */
template<typename T, typename Iter>
basic_buffer<T> make_buffer(Iter begin, Iter end)
{
	return basic_buffer<T>{ begin.base(), end.base() };
}

using buffer = basic_buffer<char>;

}

#endif
