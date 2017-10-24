#include "catch.hpp"

#include "componentmanager.hpp"
#include "componentview.hpp"
#include "componentset.hpp"
#include "vectormap.hpp"

TEST_CASE( "Building", "[vectormap]" ) {


    SECTION ("default constructor") {
        auto vm = tyra::VectorMap<int>();
        REQUIRE(vm.size() == 0);
        REQUIRE(vm.begin() == vm.end());
        vm.insert(1);
        vm.insert(2);
        vm.insert(3);
        REQUIRE(vm.contains(1));
        REQUIRE(vm.contains(2));
        REQUIRE(vm.contains(3));
        REQUIRE(vm.size() == 3);
    }

    SECTION ("copy constructor") {
        auto vm1 = tyra::VectorMap<int>();
        vm1.insert(1);
        vm1.insert(2);
        vm1.insert(3);
        auto vm2 = vm1;
        REQUIRE(vm2.contains(1));
        REQUIRE(vm2.contains(2));
        REQUIRE(vm2.contains(3));
        REQUIRE(vm1.size() == vm2.size());
        REQUIRE(vm2.size() == 3);
        vm1.insert(42);
        REQUIRE(!vm2.contains(42));
        REQUIRE(vm1.size() != vm2.size());
        REQUIRE(vm2.size() == 3);
    }

    SECTION ("copy assignment") {
        auto vm1 = tyra::VectorMap<int>();
        vm1.insert(1);
        vm1.insert(2);
        vm1.insert(3);
        auto vm2 = tyra::VectorMap<int>();
        vm2.insert(4);
        vm1 = vm2;
        REQUIRE(vm1.size() == 1);
        REQUIRE(vm2.size() == vm1.size());
        REQUIRE(!vm1.contains(1));
        REQUIRE(!vm1.contains(2));
        REQUIRE(!vm1.contains(3));
        REQUIRE(vm1.contains(4));
    }

    SECTION ("insert & erase") {
        auto vm = tyra::VectorMap<int>();
        vm.insert(1);
        vm.insert(2);
        vm.insert(3);
        REQUIRE(vm.size() == 3);
        vm.insert(3);
        REQUIRE(vm.size() == 3);
        vm.erase(3);
        REQUIRE(vm.size() == 2);
    }

}
