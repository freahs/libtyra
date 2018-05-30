#include "catch.hpp"

#include "component.hpp"
#include "typeset.hpp"
#include "typeid.hpp"

TEST_CASE( "API", "[TypeSet]" ) {
    struct C1 : public tyra::Component {};
    struct C2 : public tyra::Component {};
    struct C3 : public tyra::Component {};
    struct C4 : public tyra::Component {};
    struct C5 : public tyra::Component {};
    struct C6 : public tyra::Component {};

    tyra::TypeSet s1 = tyra::TypeSet()
        .add(tyra::type_id<tyra::Component, C1>::value)
        .add(tyra::type_id<tyra::Component, C2>::value)
        .add(tyra::type_id<tyra::Component, C3>::value)
        .add(tyra::type_id<tyra::Component, C4>::value);
    tyra::TypeSet s2 = tyra::TypeSet()
        .add(tyra::type_id<tyra::Component, C2>::value)
        .add(tyra::type_id<tyra::Component, C3>::value)
        .add(tyra::type_id<tyra::Component, C4>::value);
    tyra::TypeSet s3 = tyra::TypeSet()
        .add(tyra::type_id<tyra::Component, C4>::value)
        .add(tyra::type_id<tyra::Component, C5>::value);
    tyra::TypeSet s4 = tyra::TypeSet()
        .add(tyra::type_id<tyra::Component, C6>::value);
    tyra::TypeSet s5;

    SECTION ("compare") {
        tyra::TypeSet s6 = tyra::TypeSet()
            .add(tyra::type_id<tyra::Component, C2>::value)
            .add(tyra::type_id<tyra::Component, C3>::value)
            .add(tyra::type_id<tyra::Component, C4>::value);
        tyra::TypeSet s7;
        REQUIRE(s1 != s2);
        REQUIRE(s2 == s6);
        REQUIRE(s2 != s5);
        REQUIRE(s5 == s7);
    }

    SECTION("size()") {
        REQUIRE(s1.size() == 4);
        REQUIRE(s2.size() == 3);
        REQUIRE(s3.size() == 2);
        REQUIRE(s4.size() == 1);
        REQUIRE(s5.size() == 0);
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
