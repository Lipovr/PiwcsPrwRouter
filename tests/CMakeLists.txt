find_package(GTest)

if(GTest_FOUND)
	enable_testing()
	
	add_executable(router_tests
		heap.cpp)
		
	target_link_libraries(router_tests piwcsprwmodel)
	
	target_link_libraries(
		router_tests
		GTest::gtest_main
		)
		
	target_compile_options(router_tests PUBLIC -g -O0)
	include(GoogleTest)
	gtest_discover_tests(router_tests)
	
else()
	message(STATUS "GTest not found, skipping tests")
endif()