#include "catch.hpp"

#include "component.hpp"
#include "tyra.hpp"

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

    void entityRemoved(tyra::EntityId id) override {
        removed += 1;
        last_eid = id;
        test_removed(id);
    }
};

struct S1 : public TestSystem {
    S1() { requireAll<C1>(); }
    void test_process(const Container& ids) override {
        for (auto id : ids) {
            if (!world().component().valid<C2>(id)) {
                world().component().add<C2>(id);
            }
        }
    }
};

struct S2 : public TestSystem {
    S2() {
        requireAll<C2>();
    }

    void test_added(tyra::EntityId id) override {
        world().component().remove<C2>(id);
    }
};

static int test_number = 0;
inline void verify(TestSystem* sys, std::vector<int> values, bool reset = false) {
    ++test_number;
    INFO("test number " << test_number);
    INFO("added " << sys->added);
    INFO("removed " << sys->removed);
    INFO("processed " << sys->num_processed);
    REQUIRE(sys->added == values[0]);
    REQUIRE(sys->removed == values[2]);
    REQUIRE(sys->num_processed == values[3]);
    if (reset) {
        sys->added = 0;
        sys->removed = 0;
        sys->num_processed = 0;
    }

}


TEST_CASE("Callbacks when adding and removing components within systems", "[systemtest]") {
    tyra::World world;
    world.system().add<S1>();
    world.system().add<S2>();
    auto s1 = &world.system().get<S1>();
    auto s2 = &world.system().get<S2>();
    auto id = world.entity().create();
    world.start();
    SECTION("One change per update") {
        world.component().add<C1>(id);
        world.update();
        verify(s1, {1,0,0,1}, true); // C1 added above
        verify(s2, {1,0,0,1}, true); // C1 added C2
        world.update();
        verify(s1, {0,0,0,1}, true);
        verify(s2, {0,0,0,1}, true);
        world.update();
        verify(s1, {0,0,0,1}, true);
        verify(s2, {0,0,0,1}, true);
    }
}


