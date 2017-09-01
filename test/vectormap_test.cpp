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
    }

}
