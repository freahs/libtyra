#include "catch.hpp"

#include "componentset.hpp"
#include "componentmanager.hpp"

TEST_CASE( "Building", "[componentset]" ) {
    struct C1 : public tyra::Component {};
    struct C2 : public tyra::Component {};
    struct C3 : public tyra::Component {};
    struct C4 : public tyra::Component {};
    struct C5 : public tyra::Component {};
    struct C6 : public tyra::Component {};

    tyra::ComponentSet s1 = tyra::ComponentSet::build<C1, C2, C3, C4>();
    tyra::ComponentSet s2 = tyra::ComponentSet::build<C2, C3, C4>();
    tyra::ComponentSet s3 = tyra::ComponentSet::build<C4, C5>();
    tyra::ComponentSet s4 = tyra::ComponentSet::build<C6>();

    SECTION( "contains_all" ) {
        REQUIRE(s1.contains_all(s2) == true);
        REQUIRE(s2.contains_all(s1) == false);
        REQUIRE(s1.contains_all(s3) == false);
    }

    SECTION( "contains_any" ) {
        REQUIRE(s1.contains_any(s2) == true);
        REQUIRE(s1.contains_any(s3) == true);
        REQUIRE(s1.contains_any(s4) == false);
        REQUIRE(s2.contains_any(s3) == true);
    }

    SECTION("contains_none") {
        REQUIRE(s1.contains_none(s2) == false);
        REQUIRE(s1.contains_none(s3) == false);
        REQUIRE(s1.contains_none(s4) == true);
        REQUIRE(s2.contains_none(s1) == false);
    }
}
