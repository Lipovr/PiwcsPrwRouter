#include <gtest/gtest.h>

#include "route/router.h"


using namespace piwcs::prw::router;


namespace{
#define ROUTING_TEST(graph, node, expected)									\
	TEST(Router, graph ## _from_ ## node ){													\
		Router router(graph);												\
		NodeTable result = router.run(node);								\
		ASSERT_EQ(result, expected)	;										\
	}
} // namespace

Graph minimal_example={
		  RouteNode({{1, 10}})
		, RouteNode({{0, 5}})
};

TEST(Router, Constructor){
	Router router(minimal_example);
	ASSERT_EQ(router.nodes(), minimal_example);
}

NodeTable ex_minimal_example_0={
		  {RouteTableItem::NOT_COMPUTED, consts::SELF}
		, {0, 10}
};

ROUTING_TEST(minimal_example, 0, ex_minimal_example_0);

// This one is fully interconnected
Graph rather_complex={
		  RouteNode({{2, 16}})							// 0
		, RouteNode({{0, 2}, {2, 8}})					// 1
		, RouteNode({{3, 3}, {1, 8}})					// 2
		, RouteNode({{1, 10}, {4, 7}, {6, 5}, {5, 2}})	// 3
		, RouteNode({{3, 7}})							// 4
		, RouteNode({{6, 3}, {3, 2}})					// 5
		, RouteNode({{5, 10}})							// 6
};

NodeTable ex_rather_complex_3={
		  {0, 12}										// 0
		, {0, 10}										// 1
		, {0, 18}										// 2
		, {RouteTableItem::NOT_COMPUTED, consts::SELF}	// 3
		, {1, 7}										// 4
		, {3, 2}										// 5
		, {2, 5}										// 6
};

NodeTable ex_rather_complex_1={
		  {0, 2}										// 0
		, {RouteTableItem::NOT_COMPUTED, consts::SELF}	// 1
		, {1, 8}										// 2
		, {1, 11}										// 3
		, {1, 18}										// 4
		, {1, 13}										// 5
		, {1, 16}										// 6
};

ROUTING_TEST(rather_complex, 3, ex_rather_complex_3);

ROUTING_TEST(rather_complex, 1, ex_rather_complex_1);

// This is not interconnected
Graph rather_complex_not_interconnected={
		  RouteNode({{2, 16}})							// 0
		, RouteNode({{0, 2}, {2, 8}})					// 1
		, RouteNode({{3, 3}, {1, 8}})					// 2
		, RouteNode({{4, 7}, {6, 5}, {5, 2}})			// 3
		, RouteNode({{3, 7}})							// 4
		, RouteNode({{6, 3}, {3, 2}})					// 5
		, RouteNode({{5, 10}})							// 6
};

// Since removed link to "1" had exit index "0", new exit indices decreased by one
NodeTable ex_rather_complex_not_interconnected_3={
		  {RouteTableItem::NOT_COMPUTED, consts::INF}	// 0
		, {RouteTableItem::NOT_COMPUTED, consts::INF}	// 1
		, {RouteTableItem::NOT_COMPUTED, consts::INF}	// 2
		, {RouteTableItem::NOT_COMPUTED, consts::SELF}	// 3
		, {0, 7}										// 4
		, {2, 2}										// 5
		, {1, 5}										// 6
};

ROUTING_TEST(rather_complex_not_interconnected, 3, ex_rather_complex_not_interconnected_3)

// These are two graphs that are not connected to each other
Graph two_halves={
		  RouteNode({{2, 16}})							// 0
		, RouteNode({{0, 2}, {2, 8}})					// 1
		, RouteNode({{1, 8}})							// 2
		, RouteNode({{4, 7}, {6, 5}, {5, 2}})			// 3
		, RouteNode({{3, 7}})							// 4
		, RouteNode({{6, 3}, {3, 2}})					// 5
		, RouteNode({{5, 10}})							// 6
};

NodeTable ex_two_halves_3={
		  {RouteTableItem::NOT_COMPUTED, consts::INF}	// 0
		, {RouteTableItem::NOT_COMPUTED, consts::INF}	// 1
		, {RouteTableItem::NOT_COMPUTED, consts::INF}	// 2
		, {RouteTableItem::NOT_COMPUTED, consts::SELF}	// 3
		, {0, 7}										// 4
		, {2, 2}										// 5
		, {1, 5}										// 6
};

NodeTable ex_two_halves_1={
		  {0, 2}										// 0
		, {RouteTableItem::NOT_COMPUTED, consts::SELF}	// 1
		, {1, 8}										// 2
		, {RouteTableItem::NOT_COMPUTED, consts::INF}	// 3
		, {RouteTableItem::NOT_COMPUTED, consts::INF}	// 4
		, {RouteTableItem::NOT_COMPUTED, consts::INF}	// 5
		, {RouteTableItem::NOT_COMPUTED, consts::INF}	// 6
};

ROUTING_TEST(two_halves, 3, ex_two_halves_3)

ROUTING_TEST(two_halves, 1, ex_two_halves_1)

Graph which_one_v1={
		  RouteNode({{1, 1}, {3, 3}})					// 0
		, RouteNode({{2, 1}})							// 1
		, RouteNode({{4, 2}})							// 2
		, RouteNode({{4, 1}})							// 3
		, RouteNode({})									// 4
};

NodeTable ex_which_one_v1_0={
		  {RouteTableItem::NOT_COMPUTED, consts::SELF}	// 0
		, {0, 1}										// 1
		, {0, 2}										// 2
		, {1, 3}										// 3
		, {0, 4}										// 4
};

Graph which_one_v2={
		  RouteNode({{1, 1}, {3, 1}})					// 0
		, RouteNode({{2, 1}})							// 1
		, RouteNode({{4, 2}})							// 2
		, RouteNode({{4, 3}})							// 3
		, RouteNode({})									// 4
};

NodeTable ex_which_one_v2_0={
		  {RouteTableItem::NOT_COMPUTED, consts::SELF}	// 0
		, {0, 1}										// 1
		, {0, 2}										// 2
		, {1, 1}										// 3
		, {1, 4}										// 4
};

ROUTING_TEST(which_one_v1, 0, ex_which_one_v1_0)

ROUTING_TEST(which_one_v2, 0, ex_which_one_v2_0)

