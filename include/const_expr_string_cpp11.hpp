#pragma once
namespace const_expr_string
{
    template <typename CharT>
    constexpr typename const_expr_string<CharT>::size_type
    const_expr_string<CharT>::str_len(const_expr_string<CharT>::const_pointer str)
    {
        return str[0] =='\0' ? 0 : 1 + str_len(str+1);
    }

    template<typename CharT> template <typename TermCmp, typename Mut, typename SucCmp>
    constexpr typename const_expr_string<CharT>::size_type
    const_expr_string<CharT>::find_base(
            const_expr_string<CharT>::size_type initPos,
            const_expr_string<CharT>::size_type termVal, TermCmp termcmp,
            Mut mut, SucCmp cmp) const
    {
        return termcmp(initPos, termVal) ?
            (
                cmp(_data + initPos) ? initPos :
                find_base(mut(initPos,1), termVal, termcmp, mut, cmp)
             )
            : npos;// termcmp
    }

    template<typename CharT>
    constexpr bool is_one_of_helper(
            const const_expr_string<CharT>& chars,
            const CharT* lhs,
            typename const_expr_string<CharT>::size_type index,
            typename const_expr_string<CharT>::size_type count)
    {
        return index == count ? false :
            (
                chars[index] == *lhs ? true : is_one_of_helper(chars, lhs, index +1, count)
            );
    }

    template<typename CharT>
    constexpr bool is_one_of<CharT>::operator()(const CharT* lhs) const
    {
        return is_one_of_helper(_c, lhs, 0, _c.size());
    }

    template<typename CharT>
    constexpr bool is_one_of_partial<CharT>::operator()(const CharT* lhs) const
    {
        return is_one_of_helper(_c, lhs, 0, _count);
    }

    template<typename CharT>
    constexpr bool is_not_one_of_helper(
            const const_expr_string<CharT>& chars,
            const CharT* lhs,
            typename const_expr_string<CharT>::size_type index,
            typename const_expr_string<CharT>::size_type count)
    {
        return index == count ? true :
            (
                chars[index] == *lhs ? false : is_not_one_of_helper(chars, lhs, index +1, count)
            );
    }

    template<typename CharT>
    constexpr bool is_not_one_of<CharT>::operator()(const CharT* lhs) const
    {
        return is_not_one_of_helper(_c, lhs, 0, _c.size());
    }

    template<typename CharT>
    constexpr bool is_not_one_of_partial<CharT>::operator()(const CharT* lhs) const
    {
        return is_not_one_of_helper(_c, lhs, 0, _count);
    }

    template<typename CharT>
    constexpr int compare_helper(
            const const_expr_string<CharT>& lhs,
            typename const_expr_string<CharT>::size_type pos1,
            typename const_expr_string<CharT>::size_type count1,
            const const_expr_string<CharT>& rhs,
            typename const_expr_string<CharT>::size_type pos2,
            typename const_expr_string<CharT>::size_type index
            )
    {
        return count1 == index ? 0 :
            (
                lhs.data()[index + pos1] == rhs.data()[index + pos2] ?
                compare_helper(lhs, pos1, count1, rhs, pos2, index + 1) :
                (
                    lhs.data()[index + pos1] < rhs.data()[index + pos2] ? -1 : 1
                )
            );
    }
    template<typename CharT>
    constexpr int const_expr_string<CharT>::compare(typename const_expr_string<CharT>::size_type pos1,
            typename const_expr_string<CharT>::size_type count1,
            typename const_expr_string<CharT>::const_expr_string v,
            const_expr_string<CharT>::size_type pos2,
            const_expr_string<CharT>::size_type count2) const
    {
        return count1 < count2 ? -1 :
            (
                count1 > count2 ?  1 :
                compare_helper<CharT>(*this, pos1, count1, v, pos2, 0)
            );
    }
}
