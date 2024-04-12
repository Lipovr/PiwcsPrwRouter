add_subdirectory(route)

if(TARGET router_tests)
	target_sources(router_tests PRIVATE 
	util.cpp
	)
endif()