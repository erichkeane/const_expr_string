#pragma once

// contains a number of helper definitions.  most of these can be replaced once the standard library
// makes the standard version constexpr
namespace erichkeane
{
    template <typename CharT>
    struct char_equal
    {
        CharT _c;
        constexpr char_equal(CharT c): _c(c){}
        constexpr bool operator()(const CharT* lhs) const;
    };

    template <typename CharT>
    struct char_not_equal
    {
        CharT _c;
        constexpr char_not_equal(CharT c): _c(c){}
        constexpr bool operator()(const CharT* lhs) const;
    };

    template <typename CharT>
    struct ces_equal
    {
        const_expr_string<CharT> _c;
        typename const_expr_string<CharT>::size_type _count;

        constexpr ces_equal(const_expr_string<CharT> c): _c(c), _count(c.size()){}
        constexpr ces_equal(const_expr_string<CharT> c,
                typename const_expr_string<CharT>::size_type count): _c(c), _count(count){}

        constexpr bool operator()(const CharT* lhs) const;
    };

    template <typename CharT>
    struct is_one_of
    {
        const_expr_string<CharT> _c;

        constexpr is_one_of(const_expr_string<CharT> c): _c(c){}

        constexpr bool operator()(const CharT* lhs) const;
    };

    template <typename CharT>
    struct is_not_one_of
    {
        const_expr_string<CharT> _c;

        constexpr is_not_one_of(const_expr_string<CharT> c): _c(c){}

        constexpr bool operator()(const CharT* lhs) const;
    };

    template <typename CharT>
    struct is_one_of_partial
    {
        const_expr_string<CharT> _c;
        typename const_expr_string<CharT>::size_type _count;


        constexpr is_one_of_partial(const_expr_string<CharT> c,
                typename const_expr_string<CharT>::size_type count): _c(c), _count(count){}


        constexpr bool operator()(const CharT* lhs) const;
    };

    template <typename CharT>
    struct is_not_one_of_partial
    {
        const_expr_string<CharT> _c;
        typename const_expr_string<CharT>::size_type _count;


        constexpr is_not_one_of_partial(const_expr_string<CharT> c,
                typename const_expr_string<CharT>::size_type count): _c(c), _count(count){}

        constexpr bool operator()(const CharT* lhs) const;
    };

    template <typename T>
    struct less
    {
        using result_type = bool;
        using first_argument_type = T;
        using second_argument_type = T;

        constexpr result_type operator()(
                const first_argument_type& lhs,
                const second_argument_type& rhs) const;
    };
    template <typename T>
    struct greater_equal
    {
        using result_type = bool;
        using first_argument_type = T;
        using second_argument_type = T;

        constexpr result_type operator()(
                const first_argument_type& lhs,
                const second_argument_type& rhs) const;
    };
    template <typename T>
    struct plus
    {
        using first_argument_type = T;
        using second_argument_type = T;
        using result_type = decltype(first_argument_type(0) + second_argument_type(0));

        constexpr result_type operator()(
                const first_argument_type& lhs,
                const second_argument_type& rhs) const;
    };
    template <typename T>
    struct minus
    {
        using first_argument_type = T;
        using second_argument_type = T;
        using result_type = decltype(first_argument_type(0) - second_argument_type(0));

        constexpr result_type operator()(
                const first_argument_type& lhs,
                const second_argument_type& rhs) const;
    };
}
