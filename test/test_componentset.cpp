#include "catch.hpp"

#include "componentset.hpp"
#include "componentmanager.hpp"
#include "typeid.hpp"

TEST_CASE( "Building", "[componentset]" ) {
    struct C1 : public tyra::Component {};
    struct C2 : public tyra::Component {};
    struct C3 : public tyra::Component {};
    struct C4 : public tyra::Component {};
    struct C5 : public tyra::Component {};
    struct C6 : public tyra::Component {};

    tyra::ComponentSet s1 = tyra::ComponentSet()
        .add(tyra::Type<tyra::Component>::id<C1>())
        .add(tyra::Type<tyra::Component>::id<C2>())
        .add(tyra::Type<tyra::Component>::id<C3>())
        .add(tyra::Type<tyra::Component>::id<C4>());
    tyra::ComponentSet s2 = tyra::ComponentSet()
        .add(tyra::Type<tyra::Component>::id<C2>())
        .add(tyra::Type<tyra::Component>::id<C3>())
        .add(tyra::Type<tyra::Component>::id<C4>());
    tyra::ComponentSet s3 = tyra::ComponentSet()
        .add(tyra::Type<tyra::Component>::id<C4>())
        .add(tyra::Type<tyra::Component>::id<C5>());
    tyra::ComponentSet s4 = tyra::ComponentSet()
        .add(tyra::Type<tyra::Component>::id<C6>());
    tyra::ComponentSet s5;

    SECTION ("compare") {
        tyra::ComponentSet s6 = tyra::ComponentSet()
            .add(tyra::Type<tyra::Component>::id<C2>())
            .add(tyra::Type<tyra::Component>::id<C3>())
            .add(tyra::Type<tyra::Component>::id<C4>());
        tyra::ComponentSet s7;
        REQUIRE(s1 != s2);
        REQUIRE(s2 == s6);
        REQUIRE(s2 != s5);
        REQUIRE(s5 == s7);
    }

    SECTION ("empty()") {
        REQUIRE(s1.empty() == false);
        REQUIRE(s2.empty() == false);
        REQUIRE(s3.empty() == false);
        REQUIRE(s4.empty() == false);
        REQUIRE(s5.empty() == true);
    }

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