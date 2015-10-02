#include <iostream>
#include <sstream>
#include <assert.h>
#include <memory>
#include "const_expr_string.hpp"

struct test_ctors
{
    static constexpr const_expr_string::const_expr_string<char> ctor1 = "asdfasdfasdf";
    static constexpr const_expr_string::const_expr_string<char> ctor2 = ctor1;
    constexpr bool operator()() const
    {
        return true;
    }
};

struct test_char_conversion
{
    static constexpr const char* root = "asdfqefaxdvaqwerasdf";
    static constexpr const_expr_string::const_expr_string<char> ctor1 = root;
    static constexpr const_expr_string::const_expr_string<char> ctor2 = ctor1;

    static constexpr const char* temp1 = ctor1;
    static constexpr const char* temp2 = ctor2;

    constexpr bool operator()() const
    {
        static_assert(&temp1[0] == &root[0], "test_output failed");
        static_assert(&temp2[0] == &root[0], "test_output failed");

        return true;
    }
};

struct test_sizes
{
    static constexpr const char* root = "asdfqefaxdvaqwerasdf";
    static constexpr const_expr_string::const_expr_string<char> ctor1 = root;

    constexpr bool operator()() const
    {
        static_assert(ctor1.size() == sizeof("asdfqefaxdvaqwerasdf") - 1, "test_sizes failed");
        static_assert(ctor1.length() == sizeof("asdfqefaxdvaqwerasdf") - 1, "test_sizes failed");

        return true;
    }
};

struct test_iterators
{
    static constexpr const char* root = "asdfqefaxdvaqwerasdf";
    static constexpr const_expr_string::const_expr_string<char> ctor1 = root;
    using It = typename const_expr_string::const_expr_string<char>::iterator;

    constexpr bool helper(size_t i, It iterator) const
    {
        return iterator < ctor1.end() ?
            (
                *iterator != root[i] ? false : helper(i + 1, iterator + 1)
            )
            : true;
    }
    constexpr bool operator()() const
    {
        static_assert(*(ctor1.begin()) == root[0], "Iterator Begin Failed");
        return ctor1.begin() != ctor1.end() && helper(0, ctor1.begin());
    }
};

struct test_const_iterators
{
    static constexpr const char* root = "asdfqefaxdvaqwerasdf";
    static constexpr const_expr_string::const_expr_string<char> ctor1 = root;
    using It = typename const_expr_string::const_expr_string<char>::const_iterator;

    constexpr bool helper(size_t i, It iterator) const
    {
        return iterator < ctor1.cend() ?
            (
                *iterator != root[i] ? false : helper(i + 1, iterator + 1)
            )
            : true;
    }
    constexpr bool operator()() const
    {
        static_assert(*(ctor1.cbegin()) == root[0], "Iterator Begin Failed");
        return ctor1.cbegin() != ctor1.cend() && helper(0, ctor1.cbegin());
    }
};

struct test_index_op
{
    static constexpr const char* root = "asdfqefaxdvaqwerasdf";
    static constexpr const_expr_string::const_expr_string<char> ctor1 = root;

    constexpr bool helper(const_expr_string::const_expr_string<char>::size_type i) const
    {
        return i < ctor1.size() ?
            (
                ctor1[i] != root[i] ? false : helper(i+1)
            )
            :true;
    }
    constexpr bool operator()() const
    {
        return helper(0);
    }
};

struct test_at
{
    static constexpr const char* root = "asdfqefaxdvaqwerasdf";
    static constexpr const_expr_string::const_expr_string<char> ctor1 = root;

    constexpr bool helper(const_expr_string::const_expr_string<char>::size_type i) const
    {
        return i < ctor1.size() ?
            (
                ctor1.at(i) != root[i] ? false : helper(i+1)
                )
            : true;
    }

    constexpr bool operator()() const
    {
        return helper(0);
    }
};

struct test_data
{
    static constexpr const char* root = "asdfqefaxdvaqwerasdf";
    static constexpr const_expr_string::const_expr_string<char> ctor1 = root;

    constexpr bool operator()() const
    {
        static_assert(ctor1.data() == root, "test_data");
        return true;
    }
};

struct test_base_compare
{
    static constexpr const char* root = "asdfqefaxdvaqwerasdf";
    static constexpr const_expr_string::const_expr_string<char> ctor1 = root;
    static constexpr const char* root2 = "asdfqefaxdvaqwerasdf";
    static constexpr const_expr_string::const_expr_string<char> ctor2 = root2;
    static constexpr const char* root3 = "asdfqefaxdvaqwerasds";
    static constexpr const_expr_string::const_expr_string<char> ctor3 = root3;
    static constexpr const char* root4 = "asdfqefaxdvaqwerasdc";
    static constexpr const_expr_string::const_expr_string<char> ctor4 = root4;
    static constexpr const char* root5 = "qefax";
    static constexpr const_expr_string::const_expr_string<char> ctor5 = root5;

    constexpr bool operator()() const
    {
        // Compare-all
        static_assert(ctor1.compare(ctor2) == 0, " failed equal");
        static_assert(ctor1.compare(ctor3) != 0, " failed not equal");
        static_assert(ctor1.compare(ctor3) < 0, " failed lt");
        static_assert(ctor1.compare(ctor3) <= 0, " failed lte");
        static_assert(ctor1.compare(ctor2) <= 0, " failed lte");
        static_assert(ctor1.compare(ctor4) > 0, " failed gt");
        static_assert(ctor1.compare(ctor4) >= 0, " failed gte");
        static_assert(ctor1.compare(ctor2) >= 0, " failed gte");

        // compare first-range-only
        static_assert(ctor1.compare(4, 5, ctor5) == 0, "failed equal");
        static_assert(ctor1.compare(10, 5, ctor5) != 0, "failed not equal");
        static_assert(ctor1.compare(10, 4, ctor5) < 0, "failed lt");
        static_assert(ctor1.compare(10, 4, ctor5) <= 0, "failed lte");
        static_assert(ctor1.compare(10, 7, ctor5) > 0, "failed gt");
        static_assert(ctor1.compare(10, 7, ctor5) >= 0, "failed gte");
        static_assert(ctor1.compare(5, 5, ctor5) < 0, "failed lt");
        static_assert(ctor1.compare(8, 5, ctor5) > 0, "failed gt");

        // compare full ranges
        static_assert(ctor1.compare(4, 5, ctor5, 0, 5) == 0, "failed equal");
        static_assert(ctor1.compare(4, 5, ctor5, 0, 4) > 0, "failed gt");
        static_assert(ctor1.compare(4, 4, ctor5, 0, 5) < 0, "failed lt");
        static_assert(ctor1.compare(6, 3, ctor5, 2, 3) == 0, "failed equal");
        static_assert(ctor1.compare(10, 3, ctor5, 2, 3) != 0, "failed not equal");

        // Compare-all with char ptrs
        static_assert(ctor1.compare("asdfqefaxdvaqwerasdf") == 0, " failed equal");
        static_assert(ctor1.compare("asdfqdfaxdvaqwerasdf") != 0, " failed not equal");
        static_assert(ctor1.compare("asdfqffaxdvaqwerasdf") < 0, " failed lt");
        static_assert(ctor1.compare("asdfqdfaxdvaqwerasdf") > 0, " failed gt");

        // compare first-range-only with char ptrs
        static_assert(ctor1.compare(4, 5, "qefax") == 0, "failed equal");
        static_assert(ctor1.compare(10, 5, "qefax") != 0, "failed not equal");
        static_assert(ctor1.compare(10, 4, "qefax") < 0, "failed lt");
        static_assert(ctor1.compare(10, 4, "qefax") <= 0, "failed lte");
        static_assert(ctor1.compare(10, 7, "qefax") > 0, "failed gt");
        static_assert(ctor1.compare(10, 7, "qefax") >= 0, "failed gte");
        static_assert(ctor1.compare(5, 5, "qefax") < 0, "failed lt");
        static_assert(ctor1.compare(8, 5, "qefax") > 0, "failed gt");

        // compare full ranges with char ptrs
        static_assert(ctor1.compare(4, 5, "qefax", 5) == 0, "failed equal");
        static_assert(ctor1.compare(4, 5, "qefax", 4) > 0, "failed gt");
        static_assert(ctor1.compare(4, 4, "qefax", 5) < 0, "failed lt");
        static_assert(ctor1.compare(6, 3, "fax", 3) == 0, "failed equal");
        static_assert(ctor1.compare(10, 3, "fax", 3) != 0, "failed not equal");
        return true;
    }

};

struct test_compare_operators
{
    static constexpr const char* root = "asdfqefaxdvaqwerasdf";
    static constexpr const_expr_string::const_expr_string<char> ctor1 = root;
    static constexpr const char* root2 = "asdfqefaxdvaqwerasdf";
    static constexpr const_expr_string::const_expr_string<char> ctor2 = root2;
    static constexpr const char* root3 = "asdfqefaxdvaqwerasds";
    static constexpr const_expr_string::const_expr_string<char> ctor3 = root3;
    static constexpr const char* root4 = "asdfqefaxdvaqwerasdc";
    static constexpr const_expr_string::const_expr_string<char> ctor4 = root4;

    constexpr bool operator()() const
    {
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
};

struct test_front_back
{
    static constexpr const char* root = "asdfqefaxdvaqwerasdf";
    static constexpr const_expr_string::const_expr_string<char> ctor1 = root;

    constexpr bool operator()() const
    {
        static_assert(ctor1.front() == root[0], "front");
        static_assert(ctor1.back() == root[ctor1.size() - 1], "back");
        static_assert(&ctor1.front() == &root[0], "front addr");
        static_assert(&ctor1.back() == &root[ctor1.size() - 1], "back addr");

        return true;
    }
};

struct test_max_size
{
    static constexpr const char* root = "asdfqefaxdvaqwerasdf";
    static constexpr const_expr_string::const_expr_string<char> ctor1 = root;

    constexpr bool operator()() const
    {
        static_assert(ctor1.max_size() == size_t(-1) - 1, "Failed max size");

        return true;
    }
};

struct test_empty
{
    static constexpr const char* root = "asdfqefaxdvaqwerasdf";
    static constexpr const_expr_string::const_expr_string<char> ctor1 = root;
    static constexpr const_expr_string::const_expr_string<char> ctor2 = "";

    constexpr bool operator()() const
    {
        static_assert(!ctor1.empty(), "failed empty");
        static_assert(ctor2.empty(), "failed empty");

        return true;
    }
};

bool test_ostream()
{
    static constexpr const char* root = "asdfqefaxdvaqwerasdf";
    static constexpr const_expr_string::const_expr_string<char> ctor1 = root;

    std::stringstream ss;
    assert(ss == ss << ctor1);

    assert(ss.str() == root);
    return true;
}

struct test_find
{
    static constexpr const char* root = "asdfqefaxdvaqwerasdf";
    static constexpr const_expr_string::const_expr_string<char> ctor1 = root;
    static constexpr const char* root2 = "axd";
    static constexpr const_expr_string::const_expr_string<char> ctor2 = root2;
    static constexpr const char* root3 = "df";
    static constexpr const_expr_string::const_expr_string<char> ctor3 = root3;

    constexpr bool operator()() const
    {
        static_assert(ctor1.find(ctor2, 2) == 7, "find");
        static_assert(ctor1.find('q', 1) == 4, "find");
        static_assert(ctor1.find("axd", 3) == 7, "find");
        static_assert(ctor1.find("axd", 3, 3) == 7, "find");

        static_assert(ctor1.rfind(ctor3) == 18, "rfind");
        static_assert(ctor1.rfind('d') == 18, "rfind");
        static_assert(ctor1.rfind("df") == 18, "rfind");
        static_assert(ctor1.rfind("dfe", ctor1.size(), 2) == 18, "rfind");

        static_assert(ctor1.find_first_of(ctor2) == 0, "find_first_of");
        static_assert(ctor1.find_first_of(ctor2, 1) == 2, "find_first_of");
        static_assert(ctor1.find_first_of('f') == 3, "find_first_of");
        static_assert(ctor1.find_first_of("efa", 1) == 3, "find_first_of");
        static_assert(ctor1.find_first_of("efa", 1, 2) == 3, "find_first_of");

        static_assert(ctor1.find_last_of(ctor2) == 18, "find_last_of");
        static_assert(ctor1.find_last_of(ctor2, 17) == 16, "find_last_of");
        static_assert(ctor1.find_last_of('f') == 19, "find_last_of");
        static_assert(ctor1.find_last_of("efa", 17) == 16, "find_last_of");
        static_assert(ctor1.find_last_of("efa", 4, 2) == 3, "find_last_of");

        static_assert(ctor1.find_first_not_of(ctor2) == 1, "find_first_not_of");
        static_assert(ctor1.find_first_not_of(ctor2, 2) == 3, "find_first_not_of");
        static_assert(ctor1.find_first_not_of('a') == 1, "find_first_not_of");
        static_assert(ctor1.find_first_not_of("efa", 2) == 2, "find_first_not_of");
        static_assert(ctor1.find_first_not_of("efa", 2, 2) == 2, "find_first_not_of");

        static_assert(ctor1.find_last_not_of(ctor2) == 19, "find_last_not_of");
        static_assert(ctor1.find_last_not_of(ctor2, 16) == 15, "find_last_not_of");
        static_assert(ctor1.find_last_not_of('f') == 18, "find_last_not_of");
        static_assert(ctor1.find_last_not_of("efa", 16) == 15, "find_last_not_of");
        static_assert(ctor1.find_last_not_of("efa", 3, 2) == 2, "find_last_not_of");
        return true;
    }
};

int main()
{
    static_assert(test_ctors{}(), "failed");
    static_assert(test_char_conversion{}(), "failed");
    static_assert(test_sizes{}(), "failed");
    static_assert(test_iterators{}(), "failed");
    static_assert(test_const_iterators{}(), "failed");
    static_assert(test_index_op{}(), "failed");
    static_assert(test_at{}(), "failed");
    static_assert(test_data{}(), "failed");
    static_assert(test_base_compare{}(), "failed");
    static_assert(test_empty{}(), "failed");
    static_assert(test_front_back{}(), "failed");
    static_assert(test_max_size{}(), "failed");
    static_assert(test_compare_operators{}(), "failed");
    assert(test_ostream());
    static_assert(test_find{}(), "failed");
}
