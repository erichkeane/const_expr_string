#include <iostream>
#include <stdexcept>
#include <limits>
#include <type_traits>

namespace const_expr_string
{
    // Definition
    template<typename CharT>
    class const_expr_string
    {
        public:
            using value_type = CharT;
            using traits_type = std::char_traits<value_type>;
            using size_type = size_t;
            using difference_type = std::ptrdiff_t;
            using const_pointer = const CharT *;
            using pointer = const_pointer;
            using const_reference = const CharT&;
            using reference = const_reference;
            using const_iterator = const CharT*;
            using iterator = const_iterator;
            using const_reverse_iterator = std::reverse_iterator<const_iterator>;
            using reverse_iterator = const_reverse_iterator;
            static constexpr size_type npos = size_type(-1);

            // Constructors
            constexpr const_expr_string(const_pointer data) noexcept;
            constexpr const_expr_string(const const_expr_string<CharT>& other) = default;

            // Size based
            constexpr size_t length() const noexcept;
            constexpr size_t size() const noexcept;
            constexpr size_type max_size() const noexcept;
            constexpr bool empty() const noexcept;

            // Conversion operator
            constexpr operator const_pointer() const noexcept;

            // Iterators
            constexpr iterator begin() const noexcept;
            constexpr const_iterator cbegin() const noexcept;
            constexpr iterator end() const noexcept;
            constexpr const_iterator cend() const noexcept;

            // TODO: Fix reverse_iterator functions!
            //Can't be constexpr without a reverse_iterator type
            //constexpr const_reverse_iterator rbegin() const noexcept;
            //constexpr const_reverse_iterator crbegin() const noexcept;
            //constexpr const_reverse_iterator rend() const noexcept;
            //constexpr const_reverse_iterator crend() const noexcept;

            // Indexing
            constexpr const_reference operator[](size_type pos) const;
            constexpr const_reference at(size_type pos) const;

            // ref positions
            constexpr const_reference front() const;
            constexpr const_reference back() const;

            // Data member
            constexpr const_pointer data() const noexcept;

            // Compares
            constexpr int compare (const_expr_string v) const;
            constexpr int compare (size_type pos1, size_type count1, const_expr_string v) const; // TODO: not implemented
            constexpr int compare (size_type pos1, size_type count1, const_expr_string v, size_type pos2, size_type count2) const; // TODO: not implemented
            constexpr int compare (const_pointer s) const; // TODO: not implemented
            constexpr int compare (size_type pos1, size_type count1, const_pointer s) const; // TODO: not implemented
            constexpr int compare (size_type pos1, size_type count1, const_pointer s, size_type count2) const; // TODO: not implemented

            // Finds
            constexpr size_type find(const_expr_string v, size_type pos = 0) const;// TODO: not implemented
            constexpr size_type find(value_type c, size_type pos = 0) const;// TODO: not implemented
            constexpr size_type find(const_pointer, size_type pos = 0) const;// TODO: not implemented
            constexpr size_type find(const_pointer, size_type pos, size_type count) const;// TODO: not implemented
            constexpr size_type rfind(const_expr_string v, size_type pos = 0) const;// TODO: not implemented
            constexpr size_type rfind(value_type c, size_type pos = 0) const;// TODO: not implemented
            constexpr size_type rfind(const_pointer, size_type pos = 0) const;// TODO: not implemented
            constexpr size_type rfind(const_pointer, size_type pos, size_type count) const;// TODO: not implemented
            constexpr size_type find_first_of(const_expr_string v, size_type pos = 0) const;// TODO: not implemented
            constexpr size_type find_first_of(value_type c, size_type pos = 0) const;// TODO: not implemented
            constexpr size_type find_first_of(const_pointer, size_type pos = 0) const;// TODO: not implemented
            constexpr size_type find_first_of(const_pointer, size_type pos, size_type count) const;// TODO: not implemented
            constexpr size_type find_last_of(const_expr_string v, size_type pos = 0) const;// TODO: not implemented
            constexpr size_type find_last_of(value_type c, size_type pos = 0) const;// TODO: not implemented
            constexpr size_type find_last_of(const_pointer, size_type pos = 0) const;// TODO: not implemented
            constexpr size_type find_last_of(const_pointer, size_type pos, size_type count) const;// TODO: not implemented
            constexpr size_type find_first_not_of(const_expr_string v, size_type pos = 0) const;// TODO: not implemented
            constexpr size_type find_first_not_of(value_type c, size_type pos = 0) const;// TODO: not implemented
            constexpr size_type find_first_not_of(const_pointer, size_type pos = 0) const;// TODO: not implemented
            constexpr size_type find_first_not_of(const_pointer, size_type pos, size_type count) const;// TODO: not implemented
            constexpr size_type find_last_not_of(const_expr_string v, size_type pos = 0) const;// TODO: not implemented
            constexpr size_type find_last_not_of(value_type c, size_type pos = 0) const;// TODO: not implemented
            constexpr size_type find_last_not_of(const_pointer, size_type pos = 0) const;// TODO: not implemented
            constexpr size_type find_last_not_of(const_pointer, size_type pos, size_type count) const;// TODO: not implemented
        private:
            const_pointer _data;
    };

    // Implementation
    template <typename CharT>
    constexpr const_expr_string<CharT>::const_expr_string(
            const_expr_string<CharT>::const_pointer data) noexcept
    : _data(data)
    {
    }

    template <typename CharT>
    constexpr const_expr_string<CharT>::operator
            const_expr_string<CharT>::const_pointer() const noexcept
    {
        return _data;
    }

    // works with C++14, will likely need a helper recursive function
    // for C++11
    template <typename CharT>
    constexpr size_t const_expr_string<CharT>::length() const noexcept
    {
        size_type i = 0;
        while (_data[i] != '\0') ++i;
        return i;
    }

    template <typename CharT>
    constexpr size_t const_expr_string<CharT>::size() const noexcept
    {
        return length();
    }

    template <typename CharT>
    constexpr typename const_expr_string<CharT>::iterator const_expr_string<CharT>::begin() const noexcept
    {
        return &*_data;
    }

    template <typename CharT>
    constexpr typename const_expr_string<CharT>::const_iterator const_expr_string<CharT>::cbegin() const noexcept
    {
        return begin();
    }

    template <typename CharT>
    constexpr typename const_expr_string<CharT>::iterator const_expr_string<CharT>::end() const noexcept
    {
        return _data + size();
    }

    template <typename CharT>
    constexpr typename const_expr_string<CharT>::const_iterator const_expr_string<CharT>::cend() const noexcept
    {
        return end();
    }

    //Can't be constexpr without a reverse_iterator type
    //template <typename CharT>
    //constexpr typename const_expr_string<CharT>::reverse_iterator const_expr_string<CharT>::rbegin() const noexcept
    //{
    //    return const_reverse_iterator(end());
    //}

    //template <typename CharT>
    //constexpr typename const_expr_string<CharT>::const_reverse_iterator const_expr_string<CharT>::crbegin() const noexcept
    //{
    //    return rbegin();
    //}

    //template <typename CharT>
    //constexpr typename const_expr_string<CharT>::reverse_iterator const_expr_string<CharT>::rend() const noexcept
    //{
    //    return const_reverse_iterator(begin());
    //}

    //template <typename CharT>
    //constexpr typename const_expr_string<CharT>::const_reverse_iterator const_expr_string<CharT>::crend() const noexcept
    //{
    //    return rend();
    //}

    template<typename CharT>
    constexpr typename const_expr_string<CharT>::const_reference const_expr_string<CharT>::operator[](const_expr_string<CharT>::size_type pos) const
    {
        return _data[pos];
    }

    template<typename CharT>
    constexpr typename const_expr_string<CharT>::const_reference const_expr_string<CharT>::at(const_expr_string<CharT>::size_type pos) const
    {
        return pos >= size() ?
            throw std::out_of_range("call to at with too large index") :
            operator[](pos);
    }

    template<typename CharT>
    constexpr typename const_expr_string<CharT>::const_pointer const_expr_string<CharT>::data() const noexcept
    {
        return _data;
    }

    template<typename CharT>
    constexpr typename const_expr_string<CharT>::const_reference const_expr_string<CharT>::front() const
    {
        return operator[](0);
    }

    template<typename CharT>
    constexpr typename const_expr_string<CharT>::const_reference const_expr_string<CharT>::back() const
    {
        return operator[](size() - 1);
    }

    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::max_size() const noexcept
    {
        // reserves npos to be an illegal index
        return std::numeric_limits<size_type>::max() - 1;
    }

    template<typename CharT>
    constexpr bool const_expr_string<CharT>::empty() const noexcept
    {
        return _data[0] == '\0';
    }

    template<typename CharT>
    constexpr int const_expr_string<CharT>::compare (const_expr_string<CharT> v) const
    {
        if (size() < v.size()) return -1;
        if (size() > v.size()) return 1;

        for (const_expr_string<CharT>::size_type i = 0; i < size(); ++i)
        {
            if (_data[i] < v._data[i]) return -1;
            if (_data[i] > v._data[i]) return 1;
        }

        return 0;
    }

    // compare operators
    template<typename CharT>
    constexpr bool operator==(const_expr_string<CharT> lhs, const_expr_string<CharT> rhs)
    {
        return lhs.compare(rhs) == 0;
    }

    template<typename CharT>
    constexpr bool operator!=(const_expr_string<CharT> lhs, const_expr_string<CharT> rhs)
    {
        return !(lhs == rhs);
    }

    template<typename CharT>
    constexpr bool operator < (const_expr_string<CharT> lhs, const_expr_string<CharT> rhs)
    {
        return lhs.compare(rhs) < 0;
    }

    template<typename CharT>
    constexpr bool operator <= (const_expr_string<CharT> lhs, const_expr_string<CharT> rhs)
    {
        return lhs.compare(rhs) <= 0;
    }

    template<typename CharT>
    constexpr bool operator > (const_expr_string<CharT> lhs, const_expr_string<CharT> rhs)
    {
        return lhs.compare(rhs) > 0;
    }

    template<typename CharT>
    constexpr bool operator >= (const_expr_string<CharT> lhs, const_expr_string<CharT> rhs)
    {
        return lhs.compare(rhs) >= 0;
    }

    // TODO: Test!!, doesn't work?!
    // OStream conversion
    template <typename CharT, typename Traits>
    std::basic_ostream<CharT, Traits&> operator <<(std::basic_ostream<CharT, Traits>& os,
        const_expr_string<CharT> v)
    {
        return os << v;
    }
} // namespace const_expr_string
