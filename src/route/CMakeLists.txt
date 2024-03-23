if(TARGET router_tests)
	target_sources(router_tests PRIVATE 
	distheap.cpp 
	node.cpp
	)
endif()