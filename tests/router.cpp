#include <gtest/gtest.h>

#include "route/router.h"


using namespace piwcs::prw::router;


namespace{
#define ROUTING_TEST(graph, node, expected)									\
	TEST(Router, graph){													\
		Router router(graph);												\
		NodeTable result = router.run(node);								\
		ASSERT_EQ(result, expected)	;										\
	}
} // namespace

Graph minimal_example={
		  RouteNode({{1, 10}})
		, RouteNode({{0, 5}})
};

NodeTable ex_minimal_example_0={
		  {RouteTableItem::NOT_COMPUTED, consts::SELF}
		, {0, 10}
};


TEST(Router, Constructor){
	Router router(minimal_example);
	ASSERT_EQ(router.nodes(), minimal_example);
}

ROUTING_TEST(minimal_example, 0, ex_minimal_example_0);
