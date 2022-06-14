#ifndef MSW_BUFFER_VIEW_HPP
#define MSW_BUFFER_VIEW_HPP

#include "buffer.hpp"
#include "config.hpp"

namespace msw
{

template<typename T>
class basic_buffer_view
{
public:
	using value_type = T;
	using size_type = unsigned long;
	using const_pointer = const T *;
	using const_reference = const T &;

public:
	/**
	 * @brief Construct a buffer view using a Buffer object
	 * @param buffer The buffer object
	 */
	explicit basic_buffer_view(const basic_buffer<T> &buffer)
		: m_data{ buffer.data() }
		, m_size{ buffer.size() }
	{
	}

	/**
	 * @brief Construct a buffer view. The data the view points to has to be alive
	 * as long as the buffer view is alive
	 * @param data Pointer to the data (will NOT be copied!)
	 * @param size The size of the data in bytes
	 */
	basic_buffer_view(const_pointer data, const size_type size)
		: m_data{ data }
		, m_size{ size }
	{
	}

	/**
	 * @brief Construct a buffer view. The data the view points to has to be alive
	 * as long as the buffer view is alive
	 * @param begin const_pointer to the first element of the buffer
	 * @param end const_pointer to the last element of the buffer
	 */
	basic_buffer_view(const_pointer begin, const_pointer end)
		: m_data{ begin }
		, m_size{ (size_type)(end - begin) }
	{
	}

public:
	/**
	 * @brief const_pointer to the beginning of the buffer
	 */
	MSW_NODISCARD const_pointer begin() const
	{
		return m_data;
	}

	/**
	  * @brief const_pointer to the end of the buffer
	  */
	MSW_NODISCARD const_pointer end() const
	{
		return m_data + m_size;
	}

	/**
	 * @brief Get the data the view points to
	 * @return const_pointer to the data
	 */
	MSW_NODISCARD const_pointer data() const
	{
		return m_data;
	}

	/**
	 * @return The size of the buffer the data points to
	 */
	MSW_NODISCARD size_type size() const
	{
		return m_size;
	}

	/**
	 * @param index The index of the element in the buffer
	 * @return The element at index
	 */
	MSW_NODISCARD const_reference operator[](const size_type index) const
	{
		return m_data[index];
	}

private:
	const const_pointer m_data;	   ///< Pointer to the data
	const size_type m_size;		   ///< Size of the data
};

/**
 * @brief Create a buffer_view with std iterators.
 * Custom iterators work too, but they need a `const T *base()` method
 * 
 * @tparam T value_type for the buffer
 * @tparam Iter The iterator type
 * @param begin The beginning of the range
 * @param end The end of the range
 * @return basic_buffer_view<T> 
 */
template<typename T, typename Iter>
basic_buffer_view<T> make_buffer_view(Iter begin, Iter end)
{
	return basic_buffer_view<T>{ begin.base(), end.base() };
}

using buffer_view = basic_buffer_view<char>;

}

#endif
