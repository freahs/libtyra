
#include "catch.hpp"

#include "system.hpp"
#include "world.hpp"
#include "entitymanager.hpp"
#include "systemmanager.hpp"

#include <memory>

struct C1 : public tyra::Component { int v = 0; };
struct C2 : public tyra::Component { int v = 0; };
struct C3 : public tyra::Component { int v = 0; };
struct C4 : public tyra::Component { int v = 0; };
struct C5 : public tyra::Component { int v = 0; };
struct C6 : public tyra::Component { int v = 0; };

struct TestSystem : public tyra::System {
    int added = 0;
    int updated = 0;
    int removed = 0;
    size_t num_processed = 0;
    tyra::EntityId last_eid = 0;

    virtual void test_process(const Container&) { }
    virtual void test_added(tyra::EntityId) { }
    //virtual void test_updated(tyra::EntityId) { }
    virtual void test_removed(tyra::EntityId) { }

    void process(const Container& ids) override {
        num_processed = ids.size();
        test_process(ids);

    }

    void entityAdded(tyra::EntityId id) override {
        added += 1;
        last_eid = id;
        test_added(id);
    }

    /*
    void entityUpdated(tyra::EntityId id) override {
        updated += 1;
        last_eid = id;
        test_updated(id);
    }
    */

    void entityRemoved(tyra::EntityId id) override {
        removed += 1;
        last_eid = id;
        test_removed(id);
    }
};

struct S : public TestSystem { S() {
    requireAll<C1, C2>();
    requireOne<C3, C4>();
    exclude<C5, C6>();
}};

static int test_number = 0;
inline void verify(TestSystem* sys, std::vector<int> values, bool reset = false) {
    ++test_number;
    INFO("test number " << test_number);
    REQUIRE(sys->added == values[0]);
    //REQUIRE(sys->updated == values[1]);
    REQUIRE(sys->removed == values[2]);
    REQUIRE(sys->num_processed == values[3]);
    if (reset) {
        sys->added = 0;
        sys->updated = 0;
        sys->removed = 0;
        sys->num_processed = 0;
    }

}


TEST_CASE("Callbacks when adding and removing components", "[systemtest]") {
    tyra::World world;
    world.system().add<S>();
    auto sys = &world.system().get<S>();
    auto id = world.entity().create();
    world.start();
    SECTION("One change per update") {
        world.component().add<C1>(id);
        world.update();
        verify(sys, {0,0,0,0}, true);

        world.component().add<C2>(id);
        world.update();
        verify(sys, {0,0,0,0}, true);

        world.component().add<C3>(id);
        world.update();
        verify(sys, {1,0,0,1}, true);

        world.component().add<C4>(id);
        world.update();
        verify(sys, {0,1,0,1}, true);

        world.component().add<C5>(id);
        world.update();
        verify(sys, {0,0,1,0}, true);

        world.component().add<C6>(id);
        world.update();
        verify(sys, {0,0,0,0}, true);

        world.component().remove<C4>(id);
        world.update();
        verify(sys, {0,0,0,0}, true);

        world.component().remove<C5>(id);
        world.update();
        verify(sys, {0,0,0,0}, true);

        world.component().remove<C6>(id);
        world.update();
        verify(sys, {1,0,0,1}, true);

        world.component().remove<C3>(id);
        world.update();
        verify(sys, {0,0,1,0}, true);
    }

    SECTION("Multiple changes per update") {
        world.component().add<C1>(id);
        world.component().add<C2>(id);
        world.component().add<C3>(id);
        world.component().add<C4>(id);
        world.component().add<C5>(id);
        world.component().add<C6>(id);
        world.update();
        verify(sys, {0,0,0,0}, true);

        world.component().remove<C5>(id);
        world.component().remove<C6>(id);
        world.update();
        verify(sys, {1,0,0,1}, true);

        world.component().remove<C4>(id);
        world.update();
        verify(sys, {0,1,0,1}, true);
    }

    SECTION("Multiple entities") {
        auto n = 10;
        for(auto i = 0; i < n; ++i) {
            auto e = world.entity().create();
            world.component().add<C1>(e);
            world.component().add<C2>(e);
            world.component().add<C3>(e);
        }
        world.update();
        verify(sys, {n,0,0,n}, true);
    }
}


