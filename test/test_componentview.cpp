#include "catch.hpp"

#include "componentmanager.hpp"
#include "componentview.hpp"
#include "componentset.hpp"

TEST_CASE( "Building", "[componentview]" ) {
    struct C1 : public tyra::Component {};
    struct C2 : public tyra::Component {};
    struct C3 : public tyra::Component {};
    struct C4 : public tyra::Component {};
    struct C5 : public tyra::Component {};
    struct C6 : public tyra::Component {};

    auto c1 = tyra::ComponentView().requireAll<C1,C2,C3>().requireOne<C4,C5>().exclude<C6>();

    SECTION ("compare") {
        auto c2 = tyra::ComponentView().requireAll<C1,C2,C3>().requireOne<C4,C5>().exclude<C6>();
        auto c3 = tyra::ComponentView().requireAll<C1>();
        auto c4 = tyra::ComponentView().requireOne<C1>();
        auto c5 = tyra::ComponentView().exclude<C1>();
        REQUIRE(c1 == c2);
        REQUIRE(c1 != c3);
        REQUIRE(c1 != c4);
        REQUIRE(c1 != c5);
    }

    SECTION ("interested") {
        auto s1 = tyra::ComponentSet()
            .add(tyra::Type<tyra::Component>::id<C1>())
            .add(tyra::Type<tyra::Component>::id<C2>());
        auto s2 = tyra::ComponentSet()
            .add(tyra::Type<tyra::Component>::id<C1>())
            .add(tyra::Type<tyra::Component>::id<C2>())
            .add(tyra::Type<tyra::Component>::id<C3>());
        auto s3 = tyra::ComponentSet()
            .add(tyra::Type<tyra::Component>::id<C1>())
            .add(tyra::Type<tyra::Component>::id<C2>())
            .add(tyra::Type<tyra::Component>::id<C3>())
            .add(tyra::Type<tyra::Component>::id<C4>());
        auto s4 = tyra::ComponentSet()
            .add(tyra::Type<tyra::Component>::id<C1>())
            .add(tyra::Type<tyra::Component>::id<C2>())
            .add(tyra::Type<tyra::Component>::id<C3>())
            .add(tyra::Type<tyra::Component>::id<C4>())
            .add(tyra::Type<tyra::Component>::id<C6>());
        auto s5 = tyra::ComponentSet()
            .add(tyra::Type<tyra::Component>::id<C4>())
            .add(tyra::Type<tyra::Component>::id<C5>());
        tyra::ComponentSet s6;

        auto c2 = tyra::ComponentView().requireAll<C1,C2,C3>();
        auto c3 = tyra::ComponentView().requireOne<C1,C2,C3>();
        auto c4 = tyra::ComponentView().exclude<C1,C2,C3>();
        tyra::ComponentView c5;
        auto c6 = tyra::ComponentView().requireAll<C1>();

        REQUIRE(c1.interested(s1) == false);
        REQUIRE(c1.interested(s2) == false);
        REQUIRE(c1.interested(s3) == true);
        REQUIRE(c1.interested(s4) == false);

        REQUIRE(c2.interested(s1) == false);
        REQUIRE(c2.interested(s2) == true);
        REQUIRE(c2.interested(s5) == false);

        REQUIRE(c3.interested(s1) == true);
        REQUIRE(c3.interested(s2) == true);
        REQUIRE(c3.interested(s5) == false);

        REQUIRE(c4.interested(s1) == false);
        REQUIRE(c4.interested(s2) == false);
        REQUIRE(c4.interested(s5) == true);

        REQUIRE(c5.interested(s1) == false);
        REQUIRE(c5.interested(s6) == false);

        REQUIRE(c6.interested(s6) == false);

    }

}
