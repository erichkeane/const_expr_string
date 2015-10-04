#pragma once
namespace erichkeane
{
    template <typename CharT>
    constexpr typename const_expr_string<CharT>::size_type
    const_expr_string<CharT>::str_len(const_expr_string<CharT>::const_pointer str)
    {
        size_type i = 0;
        while (str[i] != '\0') ++i;
        return i;
    }

    template<typename CharT> template <typename TermCmp, typename Mut, typename SucCmp>
    constexpr typename const_expr_string<CharT>::size_type
    const_expr_string<CharT>::find_base(
            const_expr_string<CharT>::size_type initPos,
            const_expr_string<CharT>::size_type termVal, TermCmp termcmp,
            Mut mut, SucCmp cmp) const
    {
        for (;termcmp(initPos, termVal); initPos = mut(initPos, 1))
        {
            if(cmp(_data + initPos))
            {
                return initPos;
            }
        }

        return npos;
    }

    template<typename CharT>
    constexpr bool is_one_of<CharT>::operator()(const CharT* lhs) const
    {
        for (auto&& itr : _c)
        {
            if (itr == *lhs)
                return true;
        }
        return false;
    }

    template<typename CharT>
    constexpr bool is_one_of_partial<CharT>::operator()(const CharT* lhs) const
    {
        for (typename const_expr_string<CharT>::size_type i = 0;
                i < _count; ++i)
        {
            if (*lhs == _c[i])
                return true;
        }
        return false;
    }

    template<typename CharT>
    constexpr bool is_not_one_of<CharT>::operator()(const CharT* lhs) const
    {
        for (auto&& itr : _c)
        {
            if (itr == *lhs)
                return false;
        }
        return true;
    }

    template<typename CharT>
    constexpr bool is_not_one_of_partial<CharT>::operator()(const CharT* lhs) const
    {
        for (typename const_expr_string<CharT>::size_type i = 0;
                i < _count; ++i)
        {
            if (*lhs == _c[i])
                return false;
        }
        return true;
    }

    template<typename CharT>
    constexpr int const_expr_string<CharT>::compare(typename const_expr_string<CharT>::size_type pos1,
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
}
