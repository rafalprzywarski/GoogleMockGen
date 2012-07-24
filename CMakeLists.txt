project(googlemockgen)
cmake_minimum_required(VERSION 2.8)

include_directories("gmock-1.6.0/fused-src")

add_custom_target(GoogleMockGen ALL make -C llvm/tools/clang/plugins/GoogleMockGen WORKING_DIRECTORY "../../../../../..")

add_custom_target(Mocks ALL ./makeMocks.sh WORKING_DIRECTORY "../test/acceptance")
add_dependencies(Mocks GoogleMockGen)

add_library(gmock gmock-1.6.0/fused-src/gmock-gtest-all.cc gmock-1.6.0/fused-src/gmock_main.cc)

add_executable(
    GoogleMockGen_AT
    test/acceptance/Interface1Test.cpp
    test/acceptance/Interface2Test.cpp
    test/acceptance/InterfaceWithArgsTest.cpp
    test/acceptance/HeaderGuardsTest.cpp)

add_dependencies(GoogleMockGen_AT Mocks)

target_link_libraries(GoogleMockGen_AT gmock pthread)

