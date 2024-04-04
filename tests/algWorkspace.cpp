#include <gtest/gtest.h>

#include "route/router.h"

using namespace piwcs::prw::router;

class AlgWorkspaceTests : public testing::Test{
public:
	auto workplaceptr = AlgWorkspace::d_makeDebugWorkspace();
	Identifier id_0 = "this_is_id_0";
};

TEST_F(AlgWorkspaceTests, DebugAdd){
	workplaceptr->d_addNode(id_0, false, true);
	ASSERT_EQ(workplaceptr->m_nodes[0], )

}

