#pragma once

#include "const_expr_string_helper_defs.hpp"
// File exists for definitions that are both C++11 and C++14
namespace const_expr_string
{
    // Helper implementations
    template<typename CharT>
    constexpr bool char_equal<CharT>::operator()(const CharT* lhs) const
    {
        return *lhs == _c;
    }

    template<typename CharT>
    constexpr bool char_not_equal<CharT>::operator()(const CharT* lhs) const
    {
        return *lhs != _c;
    }

    template <typename CharT>
    constexpr bool ces_equal<CharT>::operator()(const CharT* lhs) const
    {
        return 0 == const_expr_string<CharT>(lhs).compare(0, _count, _c, 0, _count);
    }

    template <typename T>
    constexpr typename less<T>::result_type less<T>::operator() (
            const first_argument_type& lhs,
            const second_argument_type& rhs) const
    {
        return lhs < rhs;
    }

    template <typename T>
    constexpr typename greater_equal<T>::result_type greater_equal<T>::operator() (
            const first_argument_type& lhs,
            const second_argument_type& rhs) const
    {
        return lhs >= rhs;
    }

    template <typename T>
    constexpr typename plus<T>::result_type plus<T>::operator() (
            const first_argument_type& lhs,
            const second_argument_type& rhs) const
    {
        return lhs + rhs;
    }

    template <typename T>
    constexpr typename minus<T>::result_type minus<T>::operator() (
            const first_argument_type& lhs,
            const second_argument_type& rhs) const
    {
        return lhs - rhs;
    }
    // Member Implementations
    template <typename CharT>
    constexpr const_expr_string<CharT>::const_expr_string(
            const_expr_string<CharT>::const_pointer data) noexcept
    : _data(data){}

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

    template<typename CharT>
    constexpr typename const_expr_string<CharT>::const_reference const_expr_string<CharT>::operator[](const_expr_string<CharT>::size_type pos) const
    {
        return _data[pos];
    }

    template<typename CharT>
    constexpr typename const_expr_string<CharT>::const_reference const_expr_string<CharT>::at(const_expr_string<CharT>::size_type pos) const
    {
        return pos >= size() ?
            // GCC complains that this throw returns a temporary,
            // so the comma and operator[](0) is to silence that
            throw std::out_of_range("call to at with too large index"), operator[](0) :
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

    // Find methods
    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find(
            const_expr_string<CharT> v,
            typename const_expr_string<CharT>::size_type pos) const
    {
        return find_base(
                pos,
                size(), less<const_expr_string<CharT>::size_type>(),
                plus<const_expr_string<CharT>::size_type>(), ces_equal<CharT>(v));
    }

    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::rfind(
           const_expr_string<CharT> v,
            typename const_expr_string<CharT>::size_type pos) const
    {
        return find_base(
                pos == npos ? size() - 1 : pos,
                0, greater_equal<const_expr_string<CharT>::size_type>(),
                minus<const_expr_string<CharT>::size_type>(), ces_equal<CharT>(v));
    }

    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find(
            const_expr_string<CharT>::value_type c,
            typename const_expr_string<CharT>::size_type pos) const
    {
        return find_base(pos,
                size(), less<const_expr_string<CharT>::size_type>(),
                plus<const_expr_string<CharT>::size_type>(), char_equal<CharT>(c)
                );
    }

    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::rfind(
            typename const_expr_string<CharT>::value_type c,
            typename const_expr_string<CharT>::size_type pos) const
    {
        return find_base(
                pos == npos ? size() - 1 : pos,
                0, greater_equal<const_expr_string<CharT>::size_type>(),
                minus<const_expr_string<CharT>::size_type>(), char_equal<CharT>(c)
                );
    }


    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find(
            typename const_expr_string<CharT>::const_pointer v,
            typename const_expr_string<CharT>::size_type pos) const
    {
        return find(const_expr_string<CharT>(v), pos);
    }
    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::rfind(
            typename const_expr_string<CharT>::const_pointer v,
            typename const_expr_string<CharT>::size_type pos) const
    {
        return rfind(const_expr_string<CharT>(v), pos);
    }

    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find(
            typename const_expr_string<CharT>::const_pointer v,
            typename const_expr_string<CharT>::size_type pos,
            typename const_expr_string<CharT>::size_type count) const
    {
        return find_base(
                pos,
                size(), less<const_expr_string<CharT>::size_type>(),
                plus<const_expr_string<CharT>::size_type>(),
                ces_equal<CharT>(const_expr_string<CharT>{v}, count));
    }
    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::rfind(
            typename const_expr_string<CharT>::const_pointer v,
            typename const_expr_string<CharT>::size_type pos,
            typename const_expr_string<CharT>::size_type count) const
    {
        return find_base(
                pos == npos ? size() - 1 : pos,
                0, greater_equal<const_expr_string<CharT>::size_type>(),
                minus<const_expr_string<CharT>::size_type>(),
                ces_equal<CharT>(const_expr_string<CharT>{v}, count));
    }
    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find_first_of(
            const_expr_string<CharT> v,
            typename const_expr_string<CharT>::size_type pos) const
    {
        return find_base(
                pos,
                size(),
                less<const_expr_string<CharT>::size_type>(),
                plus<const_expr_string<CharT>::size_type>(),
                is_one_of<CharT>(v));
    }

    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find_first_of(
            typename const_expr_string<CharT>::value_type c,
            typename const_expr_string<CharT>::size_type pos) const
    {
        return find_base(
                pos,
                size(),
                less<const_expr_string<CharT>::size_type>(),
                plus<const_expr_string<CharT>::size_type>(),
                char_equal<CharT>(c));
    }
    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find_first_of(
            typename const_expr_string<CharT>::const_pointer v,
            typename const_expr_string<CharT>::size_type pos) const
    {
        return find_first_of(const_expr_string<CharT>(v),pos);
    }
    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find_first_of(
            typename const_expr_string<CharT>::const_pointer v,
            typename const_expr_string<CharT>::size_type pos,
            typename const_expr_string<CharT>::size_type count) const
    {
        return find_base(
                pos,
                size(),
                less<const_expr_string<CharT>::size_type>(),
                plus<const_expr_string<CharT>::size_type>(),
                is_one_of_partial<CharT>(const_expr_string<CharT>(v),count));
    }
    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find_last_of(
            const_expr_string<CharT> v,
            typename const_expr_string<CharT>::size_type pos) const
    {
        return find_base(
                pos == npos ? size() - 1 : pos,
                0,
                greater_equal<const_expr_string<CharT>::size_type>(),
                minus<const_expr_string<CharT>::size_type>(),
                is_one_of<CharT>(v));
    }
    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find_last_of(
            typename const_expr_string<CharT>::value_type c,
            typename const_expr_string<CharT>::size_type pos) const
    {
        return find_base(
                pos == npos ? size() - 1 : pos,
                0,
                greater_equal<const_expr_string<CharT>::size_type>(),
                minus<const_expr_string<CharT>::size_type>(),
                char_equal<CharT>(c));
    }
    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find_last_of(
            typename const_expr_string<CharT>::const_pointer v,
            typename const_expr_string<CharT>::size_type pos) const
    {
        return find_last_of(const_expr_string<CharT>(v), pos);
    }

    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find_last_of(
            typename const_expr_string<CharT>::const_pointer v,
            typename const_expr_string<CharT>::size_type pos,
            typename const_expr_string<CharT>::size_type count) const
    {
        return find_base(
                pos == npos ? size() - 1 : pos,
                0,
                greater_equal<const_expr_string<CharT>::size_type>(),
                minus<const_expr_string<CharT>::size_type>(),
                is_one_of_partial<CharT>(const_expr_string<CharT>(v), count));
    }
    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find_first_not_of(
            const_expr_string<CharT> v,
            typename const_expr_string<CharT>::size_type pos) const
    {
        return find_base(
                pos,
                size(),
                less<const_expr_string<CharT>::size_type>(),
                plus<const_expr_string<CharT>::size_type>(),
                is_not_one_of<CharT>(v));
    }
    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find_first_not_of(
            typename const_expr_string<CharT>::value_type c,
            typename const_expr_string<CharT>::size_type pos) const
    {
        return find_base(
                pos,
                size(),
                less<const_expr_string<CharT>::size_type>(),
                plus<const_expr_string<CharT>::size_type>(),
                char_not_equal<CharT>(c));
    }
    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find_first_not_of(
            typename const_expr_string<CharT>::const_pointer v,
            typename const_expr_string<CharT>::size_type pos) const
    {
        return find_first_not_of(const_expr_string<CharT>(v),pos);
    }

    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find_first_not_of(
            typename const_expr_string<CharT>::const_pointer v,
            typename const_expr_string<CharT>::size_type pos,
            typename const_expr_string<CharT>::size_type count) const
    {
        return find_base(
                pos,
                size(),
                less<const_expr_string<CharT>::size_type>(),
                plus<const_expr_string<CharT>::size_type>(),
                is_not_one_of_partial<CharT>(const_expr_string<CharT>(v), count));
    }
    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find_last_not_of(
            const_expr_string<CharT> v,
            typename const_expr_string<CharT>::size_type pos) const
    {
        return find_base(
                pos == npos ? size() - 1 : pos,
                0,
                greater_equal<const_expr_string<CharT>::size_type>(),
                minus<const_expr_string<CharT>::size_type>(),
                is_not_one_of<CharT>(v));
    }
    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find_last_not_of(
            typename const_expr_string<CharT>::value_type c,
            typename const_expr_string<CharT>::size_type pos) const
    {
        return find_base(
                pos == npos ? size() - 1 : pos,
                0,
                greater_equal<const_expr_string<CharT>::size_type>(),
                minus<const_expr_string<CharT>::size_type>(),
                char_not_equal<CharT>(c));
    }
    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find_last_not_of(
            typename const_expr_string<CharT>::const_pointer v,
            typename const_expr_string<CharT>::size_type pos) const
    {
        return find_last_not_of(const_expr_string<CharT>(v), pos);
    }

    template<typename CharT>
    constexpr typename const_expr_string<CharT>::size_type const_expr_string<CharT>::find_last_not_of(
            typename const_expr_string<CharT>::const_pointer v,
            typename const_expr_string<CharT>::size_type pos,
            typename const_expr_string<CharT>::size_type count) const
    {
        return find_base(
                pos == npos ? size() - 1 : pos,
                0,
                greater_equal<const_expr_string<CharT>::size_type>(),
                minus<const_expr_string<CharT>::size_type>(),
                is_not_one_of_partial<CharT>(const_expr_string<CharT>(v), count));
    }

}
