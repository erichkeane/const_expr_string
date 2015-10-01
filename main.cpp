#include <iostream>
#include <sstream>
#include <assert.h>
#include "const_expr_string.hpp"

constexpr bool test_ctors()
{
    constexpr const_expr_string::const_expr_string<char> ctor1 = "asdfasdfasdf";
    constexpr const_expr_string::const_expr_string<char> ctor2 = ctor1;

    return true;
}

constexpr bool test_char_conversion()
{
    constexpr const char* root = "asdfqefaxdvaqwerasdf";
    constexpr const_expr_string::const_expr_string<char> ctor1 = root;
    constexpr const_expr_string::const_expr_string<char> ctor2 = ctor1;

    constexpr const char* temp1 = ctor1;
    constexpr const char* temp2 = ctor2;

    static_assert(&temp1[0] == &root[0], "test_output failed");
    static_assert(&temp2[0] == &root[0], "test_output failed");

    return true;
}

constexpr bool test_sizes()
{
    constexpr const char* root = "asdfqefaxdvaqwerasdf";
    constexpr const_expr_string::const_expr_string<char> ctor1 = root;

    static_assert(ctor1.size() == sizeof("asdfqefaxdvaqwerasdf") - 1, "test_sizes failed");
    static_assert(ctor1.length() == sizeof("asdfqefaxdvaqwerasdf") - 1, "test_sizes failed");

    return true;
}

constexpr bool test_iterators()
{
    constexpr const char* root = "asdfqefaxdvaqwerasdf";
    constexpr const_expr_string::const_expr_string<char> ctor1 = root;

    using It = typename const_expr_string::const_expr_string<char>::iterator;

    size_t i = 0;
    constexpr It itr1 = ctor1.begin();
    static_assert(*itr1 == root[0], "itr fail");

    for(It itr = ctor1.begin(); itr < ctor1.end(); ++itr, ++i)
    {
        if (*itr != root[i])
        {
            return false;
        }
    }

    return true;
}

constexpr bool test_const_iterators()
{
    constexpr const char* root = "asdfqefaxdvaqwerasdf";
    constexpr const_expr_string::const_expr_string<char> ctor1 = root;

    using It = const_expr_string::const_expr_string<char>::const_iterator;

    size_t i = 0;
    constexpr It itr1 = ctor1.cbegin();
    static_assert(*itr1 == root[0], "itr fail");

    for(It itr = ctor1.cbegin(); itr < ctor1.cend(); ++itr, ++i)
    {
        if (*itr != root[i])
        {
            return false;
        }
    }

    return true;
}

//Reenable when we get const-expr reverse-iterator
//constexpr bool test_reverse_iterators()
//{
//    constexpr const char* root = "asdfqefaxdvaqwerasdf";
//    constexpr const_expr_string::const_expr_string<char> ctor1 = root;
//
//    using It = const_expr_string::const_expr_string<char>::reverse_iterator;
//
//    size_t i = 0;
//    constexpr It itr1 = ctor1.rbegin();
//    static_assert(*itr1 == root[0], "itr fail");
//
//    for(It itr = ctor1.rbegin(); itr < ctor1.rend(); ++itr, ++i)
//    {
//        if (*itr != root[i])
//        {
//            return false;
//        }
//    }
//
//    return true;
//}
//
//constexpr bool test_const_reverse_iterators()
//{
//    constexpr const char* root = "asdfqefaxdvaqwerasdf";
//    constexpr const_expr_string::const_expr_string<char> ctor1 = root;
//
//    size_t i = 0;
//    constexpr It itr1 = ctor1.crbegin();
//    static_assert(*itr1 == root[0], "itr fail");
//
//    using It = const_expr_string::const_expr_string<char>::const_reverse_iterator;
//    for(It itr = ctor1.crbegin(); itr < ctor1.crend(); ++itr, ++i)
//    {
//        if (*itr != root[i])
//        {
//            return false;
//        }
//    }
//
//    return true;
//}

constexpr bool test_index_op()
{
    constexpr const char* root = "asdfqefaxdvaqwerasdf";
    constexpr const_expr_string::const_expr_string<char> ctor1 = root;

    for (const_expr_string::const_expr_string<char>::size_type i = 0;
            i < ctor1.size(); ++i)
    {
        if (ctor1[i] != root[i])
            return false;
    }
    return true;
}

constexpr bool test_at()
{
    constexpr const char* root = "asdfqefaxdvaqwerasdf";
    constexpr const_expr_string::const_expr_string<char> ctor1 = root;

    for (const_expr_string::const_expr_string<char>::size_type i = 0;
            i < ctor1.size(); ++i)
    {
        if (ctor1.at(i) != root[i])
            return false;
    }
    return true;
}

constexpr bool test_data()
{
    constexpr const char* root = "asdfqefaxdvaqwerasdf";
    constexpr const_expr_string::const_expr_string<char> ctor1 = root;

    static_assert(ctor1.data() == root, "test_data");
    return true;
}

constexpr bool test_base_compare()
{
    constexpr const char* root = "asdfqefaxdvaqwerasdf";
    constexpr const_expr_string::const_expr_string<char> ctor1 = root;
    constexpr const char* root2 = "asdfqefaxdvaqwerasdf";
    constexpr const_expr_string::const_expr_string<char> ctor2 = root2;
    constexpr const char* root3 = "asdfqefaxdvaqwerasds";
    constexpr const_expr_string::const_expr_string<char> ctor3 = root3;
    constexpr const char* root4 = "asdfqefaxdvaqwerasdc";
    constexpr const_expr_string::const_expr_string<char> ctor4 = root4;

    static_assert(ctor1.compare(ctor2) == 0, " failed equal");
    static_assert(ctor1.compare(ctor3) != 0, " failed not equal");
    static_assert(ctor1.compare(ctor3) < 0, " failed lt");
    static_assert(ctor1.compare(ctor3) <= 0, " failed lte");
    static_assert(ctor1.compare(ctor2) <= 0, " failed lte");
    static_assert(ctor1.compare(ctor4) > 0, " failed gt");
    static_assert(ctor1.compare(ctor4) >= 0, " failed gte");
    static_assert(ctor1.compare(ctor2) >= 0, " failed gte");
    return true;

}

constexpr bool test_compare_operators()
{
    constexpr const char* root = "asdfqefaxdvaqwerasdf";
    constexpr const_expr_string::const_expr_string<char> ctor1 = root;
    constexpr const char* root2 = "asdfqefaxdvaqwerasdf";
    constexpr const_expr_string::const_expr_string<char> ctor2 = root2;
    constexpr const char* root3 = "asdfqefaxdvaqwerasds";
    constexpr const_expr_string::const_expr_string<char> ctor3 = root3;
    constexpr const char* root4 = "asdfqefaxdvaqwerasdc";
    constexpr const_expr_string::const_expr_string<char> ctor4 = root4;

    static_assert(ctor1 == ctor2, " failed equal");
    static_assert(ctor1 != ctor3, " failed not equal");
    static_assert(ctor1 < ctor3, " failed lt");
    static_assert(ctor1 <= ctor3, " failed lte");
    static_assert(ctor1 <= ctor2, " failed lte");
    static_assert(ctor1 > ctor4, " failed gt");
    static_assert(ctor1 >= ctor4, " failed gte");
    static_assert(ctor1 >= ctor2, " failed gte");
    return true;
}

constexpr bool test_front_back()
{
    constexpr const char* root = "asdfqefaxdvaqwerasdf";
    constexpr const_expr_string::const_expr_string<char> ctor1 = root;

    static_assert(ctor1.front() == root[0], "front");
    static_assert(ctor1.back() == root[ctor1.size() - 1], "back");
    static_assert(&ctor1.front() == &root[0], "front addr");
    static_assert(&ctor1.back() == &root[ctor1.size() - 1], "back addr");

    return true;
}

constexpr bool test_max_size()
{
    constexpr const char* root = "asdfqefaxdvaqwerasdf";
    constexpr const_expr_string::const_expr_string<char> ctor1 = root;
    static_assert(ctor1.max_size() == size_t(-1) - 1, "Failed max size");

    return true;
}

constexpr bool test_empty()
{
    constexpr const char* root = "asdfqefaxdvaqwerasdf";
    constexpr const_expr_string::const_expr_string<char> ctor1 = root;
    constexpr const_expr_string::const_expr_string<char> ctor2 = "";

    static_assert(!ctor1.empty(), "failed empty");
    static_assert(ctor2.empty(), "failed empty");

    return true;
}

bool test_ostream()
{
    // TODO validate!!
    return false;
}

int main()
{
    static_assert(test_ctors(), "failed");
    static_assert(test_char_conversion(), "failed");
    static_assert(test_sizes(), "failed");
    static_assert(test_iterators(), "failed");
    static_assert(test_const_iterators(), "failed");
    //static_assert(test_reverse_iterators(), "failed");
    //static_assert(test_const_reverse_iterators(), "failed");
    static_assert(test_index_op(), "failed");
    static_assert(test_at(), "failed");
    static_assert(test_data(), "failed");
    static_assert(test_base_compare(), "failed");



    static_assert(test_empty(), "failed");
    static_assert(test_front_back(), "failed");
    static_assert(test_max_size(), "failed");
    static_assert(test_compare_operators(), "failed");
    assert(test_ostream());
}
