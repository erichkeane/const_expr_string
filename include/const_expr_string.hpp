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
            constexpr int compare (size_type pos1, size_type count1, const_expr_string v) const;
            constexpr int compare (size_type pos1, size_type count1, const_expr_string v,
                    size_type pos2, size_type count2) const;
            constexpr int compare (const_pointer s) const;
            constexpr int compare (size_type pos1, size_type count1, const_pointer s) const;
            constexpr int compare (size_type pos1, size_type count1, const_pointer s, size_type count2) const;

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
            static constexpr size_type str_len(const char* str)
            {
                size_type i = 0;
                while (str[i] != '\0') ++i;
                return i;
            }
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

    template <typename CharT>
    constexpr size_t const_expr_string<CharT>::length() const noexcept
    {
        return const_expr_string<CharT>::str_len(_data);
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

    // Compare functions
    template<typename CharT>
    constexpr int const_expr_string<CharT>::compare (const_expr_string<CharT> v) const
    {
        return compare(0, size(), v, 0, size());
    }

    template<typename CharT>
    constexpr int const_expr_string<CharT>::compare (typename const_expr_string<CharT>::size_type pos1,
            typename const_expr_string<CharT>::size_type count1,
            typename const_expr_string<CharT>::const_expr_string v) const
    {
        return compare (pos1, count1, v, 0, v.size());
    }

    template<typename CharT>
    constexpr int const_expr_string<CharT>::compare (typename const_expr_string<CharT>::size_type pos1,
            typename const_expr_string<CharT>::size_type count1,
            typename const_expr_string<CharT>::const_expr_string v,
            const_expr_string<CharT>::size_type pos2,
            const_expr_string<CharT>::size_type count2) const
    {
        typename const_expr_string<CharT>::size_type lhsSize = count1;
        typename const_expr_string<CharT>::size_type rhsSize = count2;

        if (lhsSize < rhsSize) return -1;
        if (lhsSize > rhsSize) return 1;

        for (const_expr_string<CharT>::size_type i = 0; i < lhsSize; ++i)
        {
            if (_data[i + pos1] < v._data[i + pos2]) return -1;
            if (_data[i + pos1] > v._data[i + pos2]) return 1;
        }

        return 0;
    }


    template<typename CharT>
    constexpr int const_expr_string<CharT>::compare (
            typename const_expr_string<CharT>::const_pointer s) const
    {
        return compare(0, size(), s, str_len(s));
    }

    template<typename CharT>
    constexpr int const_expr_string<CharT>::compare (
            typename const_expr_string<CharT>::size_type pos1,
            typename const_expr_string<CharT>::size_type count1,
            typename const_expr_string<CharT>::const_pointer s) const
    {
        return compare(pos1, count1, s, str_len(s));
    }

    template<typename CharT>
    constexpr int const_expr_string<CharT>::compare (
            typename const_expr_string<CharT>::size_type pos1,
            typename const_expr_string<CharT>::size_type count1,
            typename const_expr_string<CharT>::const_pointer s,
            typename const_expr_string<CharT>::size_type count2) const
    {
        return compare(pos1, count1, const_expr_string<CharT>(s), 0, count2);
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

    // OStream conversion
    template <typename CharT, typename Traits>
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
        const_expr_string<CharT> v)
    {
        return os << v.data();
    }
} // namespace const_expr_string
