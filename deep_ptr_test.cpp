#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "deep_ptr.h"

using namespace jbcoe;

TEST_CASE("Ensure that deep_ptr default construction produces a default initialised deep_ptr", "[deep_ptr.constructor]")
{
    deep_ptr<int> instance;
    REQUIRE(instance.operator->() == nullptr);
}