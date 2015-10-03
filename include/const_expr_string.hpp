#pragma once

#include <cstdlib>
#include <string>

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
            using const_pointer = const CharT*;
            using pointer = const_pointer;
            using const_reference = const CharT&;
            using reference = const_reference;
            using const_iterator = const CharT*;
            using iterator = const_iterator;
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
            constexpr size_type find(const_expr_string v, size_type pos = 0) const;
            constexpr size_type find(value_type c, size_type pos = 0) const;
            constexpr size_type find(const_pointer, size_type pos = 0) const;
            constexpr size_type find(const_pointer, size_type pos, size_type count) const;

            constexpr size_type rfind(const_expr_string v, size_type pos = npos) const;
            constexpr size_type rfind(value_type c, size_type pos = npos) const;
            constexpr size_type rfind(const_pointer, size_type pos = npos) const;
            constexpr size_type rfind(const_pointer, size_type pos, size_type count) const;

            constexpr size_type find_first_of(const_expr_string v, size_type pos = 0) const;
            constexpr size_type find_first_of(value_type c, size_type pos = 0) const;
            constexpr size_type find_first_of(const_pointer, size_type pos = 0) const;
            constexpr size_type find_first_of(const_pointer, size_type pos, size_type count) const;

            constexpr size_type find_last_of(const_expr_string v, size_type pos = npos) const;
            constexpr size_type find_last_of(value_type c, size_type pos = npos) const;
            constexpr size_type find_last_of(const_pointer, size_type pos = npos) const;
            constexpr size_type find_last_of(const_pointer, size_type pos, size_type count) const;

            constexpr size_type find_first_not_of(const_expr_string v, size_type pos = 0) const;
            constexpr size_type find_first_not_of(value_type c, size_type pos = 0) const;
            constexpr size_type find_first_not_of(const_pointer, size_type pos = 0) const;
            constexpr size_type find_first_not_of(const_pointer, size_type pos, size_type count) const;

            constexpr size_type find_last_not_of(const_expr_string v, size_type pos = npos) const;
            constexpr size_type find_last_not_of(value_type c, size_type pos = npos) const;
            constexpr size_type find_last_not_of(const_pointer, size_type pos = npos) const;
            constexpr size_type find_last_not_of(const_pointer, size_type pos, size_type count) const;
        private:
            const_pointer _data;
            static constexpr size_type str_len(const_pointer str);

            template <typename TermCmp, typename Mut, typename SucCmp>
            constexpr size_type find_base(size_type initPos,
                    size_type termVal, TermCmp termcmp,
                    Mut mut, SucCmp cmp) const;
    };
}

#include "const_expr_string_helper_defs.hpp"
#include "const_expr_string_universal.hpp"
#if __cpp_constexpr >=201304
    #include "const_expr_string_cpp14.hpp"
#else
    #include "const_expr_string_cpp11.hpp"
#endif
