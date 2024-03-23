#ifndef INCLUDE_ROUTE_ROUTER_H_
#define INCLUDE_ROUTE_ROUTER_H_

#include <vector>
#include <memory>

#include<piwcsprwmodel.h> //#TODO Unnecessary?

#include "common.h"
#include "util.h"
#include "routetables.h"
#include "route/distheap.h"
#include "route/node.h"


namespace piwcs::prw::router{

/**
 * Class containing properties of nodes in exploded graph
 */
class AlgWorkspace{
  public:

	/*
	 * TODO add comment
	 */
	static RouteTables makeRouteTables(const Model &InModel);

#ifndef NDEBUG

	/**
	 * Functions to populate workspace manually.
	 * For debug and tests only
	 */

	/**
	 * Create empty workspace
	 */
	static std::unique_ptr<AlgWorkspace> d_makeDebugWorkspace();

	/*
	 * Adds a new RouteNode to workspace
	 *
	 * @return index of newly inserted node
	 */
	Index d_addNode(const Identifier &id, bool isdestination, bool requiresrouting);

	/*
	 * Adds new unidirectional section to workspace
	 */
	void d_addSection(Index from, Index to, Length distance);
#endif // NDEBUG
public:
	enum class NodeStatus {
			NOT_VISITED,
			VISITED,
		};

INSPECTABLE:
	std::vector<RouteNode> m_nodes;
	std::vector<bool> m_nodeinheap;
	std::vector<NodeStatus> m_nodevisited;
	DistHeap m_heap;

	//bool m_routed;

	AlgWorkspace(const std::vector<RouteNode> &nodes);
	
	/*
	 * Process information from Model and generate AlgWorkspace containing
	 * information on graph in adjacency list form
	 */
	static std::unique_ptr<AlgWorkspace> m_makeWorkspace(const Model &InModel);

	/*
	 * For each node in workspace Run Dijekstra algorithm
	 * and generate routing table
	 */
	void m_run();

	/*
	 * Collect routing tables from nodes where it is necessary and
	 * generate RouteTables object
	 */
	RouteTables m_getTables();

};

}
#endif /* INCLUDE_ROUTE_ROUTER_H_ */
