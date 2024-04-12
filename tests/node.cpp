#include <gtest/gtest.h>

#include "route/node.h"

using namespace piwcs::prw::router;

Identifier id_0 = "this_is_id_0";
Identifier id_1 = "this_is_id_1";


TEST(RouteNode, DefaultConstruct){
	RouteNode node = RouteNode();
	ASSERT_GE(node.m_neighbors.capacity(), 0);
	ASSERT_EQ(node.m_neighbors.size(), 0);
}

TEST(RouteNode, NeighborsDefaultConstruct){
	std::vector<RouteNeighbor> neighbors;
	neighbors.emplace_back(0, 10);
	neighbors.emplace_back(7, 8);
	neighbors.emplace_back(5, 80);

	RouteNode node = RouteNode(neighbors);

	ASSERT_EQ(node.m_neighbors, neighbors);
}

TEST(RouteNode, AllocConstruct){
	RouteNode node = RouteNode(20);
	EXPECT_GE(node.m_neighbors.capacity(), 20);
	EXPECT_EQ(node.m_neighbors.size(), 0);
}

TEST(RouteNode, AddNeighbor){
	RouteNode node = RouteNode(10);
	node.addNeighbor(4,23);
	std::vector<RouteNeighbor> neighbors;
	neighbors.emplace_back(4,23);
	ASSERT_EQ(node.m_neighbors, neighbors);
}


class RouteNodeNeighborTests: public testing::Test{
public:
	RouteNode node = RouteNode(10);
	std::vector<RouteNeighbor> neighbors;
	void SetUp() override{
		neighbors.emplace_back(3, 12);
		neighbors.emplace_back(6, 5);
		neighbors.emplace_back(1, 53);
		std::for_each(neighbors.begin(),neighbors.end(), [&](RouteNeighbor &n){
		node.addNeighbor(n.node_i,n.distance);
		});
	}
};

TEST_F(RouteNodeNeighborTests, AddNeighbors){
	std::vector<RouteNeighbor> test_neighbors;
	for(Index i=0; i<neighbors.size(); ++i){
		test_neighbors.emplace_back(node.getNeighbor(i));
	}
	ASSERT_EQ(test_neighbors, neighbors);
}

TEST_F(RouteNodeNeighborTests, FindNeighborSucceed){
	ASSERT_EQ(node.findNeighbor(6), 1);
}

TEST_F(RouteNodeNeighborTests, FindNeighborFail){
	ASSERT_EQ(node.findNeighbor(8), RouteNode::NOT_FOUND);
}

TEST_F(RouteNodeNeighborTests, NeighborCount){
	ASSERT_EQ(node.neighbourCount(), neighbors.size());
}
