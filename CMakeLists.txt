project(googlemockgen)
cmake_minimum_required(VERSION 2.8)

add_custom_target(GoogleMockGen ALL make -C llvm/tools/clang/plugins/GoogleMockGen WORKING_DIRECTORY "../../../../../..")
#add_custom_target(GoogleMockGen ALL pwd WORKING_DIRECTORY "../../../../../..")
