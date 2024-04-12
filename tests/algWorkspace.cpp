#include <new>

#include <gtest/gtest.h>

#include "route/router.h"

using namespace piwcs::prw::router;
TEST(AlgWorkspaceBasicTests, DebugMakeWorkspace){
	std::unique_ptr<AlgWorkspace> workspaceptr = std::move(AlgWorkspace::d_makeDebugWorkspace());
	ASSERT_EQ(workspaceptr->m_nodes.size(), 0);
	ASSERT_EQ(workspaceptr->m_nodeCount, 0);
}
auto nodes_t = std::vector<RouteNode>();
class AlgWorkspaceDebugTests : public testing::Test{
public:
	std::unique_ptr<AlgWorkspace> workspaceptr = AlgWorkspace::d_makeDebugWorkspace();
	Identifier id_0 = "this_is_id_0";
	Identifier id_1 = "this_is_id_0";
	Index N = 10; // node count
};

TEST_F(AlgWorkspaceDebugTests, DebugAddNode){
	workspaceptr->d_addNode(id_0, N, true, false);
	ASSERT_EQ(workspaceptr->m_nodes[0].id(), id_0);
	ASSERT_EQ(workspaceptr->m_nodes[0].neighbourCount(), 0);
	ASSERT_TRUE(workspaceptr->m_nodes[0].requiresRouting());
	ASSERT_FALSE(workspaceptr->m_nodes[0].isDestination());
}

TEST_F(AlgWorkspaceDebugTests, DebugAddSection){
	workspaceptr->d_addNode(id_0, N, true, false);
	workspaceptr->d_addNode(id_1, N, true, false);
	workspaceptr->d_addSection(0, 1, 10);
	Index ne_idx = workspaceptr->m_nodes[0].findNeighbor(1);
	ASSERT_EQ(workspaceptr->m_nodes[0].getNeighbor(ne_idx), RouteNeighbor(1, 10));
}

