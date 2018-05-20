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
    S1() {
        requireAll<C1>();
    }
    void test_process(const Container& ids) override {
        for (auto id : ids) {
            auto c = &world().component().get<C1>(id);
            c->v -= 1;
            if (c->v <= 0) {
                world().component().remove<C1>(id);
            }
        }
    }
};

struct S2 : public TestSystem { S2() {
    requireAll<C1>();
}};

TEST_CASE("Multiple systems", "[systemtest]") {
    tyra::World world;
    world.system().add<S1>();
    world.system().add<S2>();
    auto s1 = &world.system().get<S1>();
    auto s2 = &world.system().get<S2>();
    world.start();

    SECTION("TEST") {
        auto id = world.entity().create();
        world.component().add<C1>(id);
        world.component().get<C1>(id).v = 3;
        for (auto i = 0; i < 10; ++i) {
            world.update();
            std::cout << "--------" << std::endl;
            std::cout << "   s1 added=" << s1->added << " removed=" << s1->removed << " processed=" << s1->num_processed << std::endl;
            std::cout << "   s2 added=" << s2->added << " removed=" << s2->removed << " processed=" << s2->num_processed << std::endl;
        }
    }
}
