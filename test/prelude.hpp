//
// Created by Ignacio Rossi on 4/7/18.
//

#ifndef CLIONTEST_MY_CATCH_H
#define CLIONTEST_MY_CATCH_H

#include <catch2/catch.hpp>
#include "gmock/gmock.h"

#ifdef CATCH_CONFIG_PREFIX_ALL

#undef SCENARIO
#define SCENARIO CATCH_SCENARIO
#undef GIVEN
#define GIVEN(x) CATCH_GIVEN(x)
#undef WHEN
#define WHEN(x) CATCH_WHEN(x)
#undef THEN
#define THEN(x) CATCH_THEN(x)
#undef AND_THEN
#define AND_THEN(x) CATCH_AND_THEN(x)

#define REQUIRE CATCH_REQUIRE
#define CHECK_THROWS CATCH_CHECK_THROWS
#define REQUIRE_FALSE CATCH_REQUIRE_FALSE
#endif

namespace testing {
template<typename T>
void assertEquals(T one, T two) {
    REQUIRE(one == two);
    REQUIRE_FALSE(one != two);
}

template<typename T>
void assertDifferent(T one, T two) {
    REQUIRE(one != two);
    REQUIRE_FALSE(one == two);
}  // namespace testing
}

#endif // CLIONTEST_MY_CATCH_H
