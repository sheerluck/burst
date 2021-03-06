#include <burst/container/make_forward_list.hpp>
#include <burst/container/make_vector.hpp>
#include <burst/range/adaptor/merged.hpp>
#include <burst/range/make_range_vector.hpp>

#include <boost/range/irange.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/test/unit_test.hpp>

#include <iterator>

BOOST_AUTO_TEST_SUITE(merged)
    BOOST_AUTO_TEST_CASE(accepts_a_range_by_rvalue)
    {
        const auto first = burst::make_vector({1, 2, 3});
        const auto second = burst::make_vector({3, 4, 5});
        auto ranges = burst::make_range_vector(first, second);

        const auto merged = boost::make_iterator_range(ranges) | burst::merged;

        const auto expected = {1, 2, 3, 3, 4, 5};
        BOOST_CHECK_EQUAL_COLLECTIONS
        (
            std::begin(merged), std::end(merged),
            std::begin(expected), std::end(expected)
        );
    }

    BOOST_AUTO_TEST_CASE(accepts_a_range_by_lvalue)
    {
        auto range_vector = burst::make_vector({boost::irange(1, 3), boost::irange(2, 4)});
        auto ranges = boost::make_iterator_range(range_vector);

        const auto merged = ranges | burst::merged;

        const auto expected = {1, 2, 2, 3};
        BOOST_CHECK_EQUAL_COLLECTIONS
        (
            std::begin(merged), std::end(merged),
            std::begin(expected), std::end(expected)
        );
    }

    BOOST_AUTO_TEST_CASE(accepts_custom_comparator)
    {
        const auto first = burst::make_forward_list({3, 2, 1});
        const auto second = burst::make_forward_list({5, 3, 1});
        auto ranges = burst::make_range_vector(first, second);

        const auto merged =
            boost::make_iterator_range(ranges)
                | burst::merged([] (const auto & left, const auto & right) { return left > right; });

        const auto expected = {5, 3, 3, 2, 1, 1};
        BOOST_CHECK_EQUAL_COLLECTIONS
        (
            std::begin(merged), std::end(merged),
            std::begin(expected), std::end(expected)
        );
    }
BOOST_AUTO_TEST_SUITE_END()
