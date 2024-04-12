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
 * Class containing adjacency list representation of regular graph
 * representation of Model and performing routing table generation
 * for its nodes
 */
class Router{

public:
	enum class NodeStatus {
			NOT_VISITED,
			VISITED,
		};

	Router(const std::vector<RouteNode> &nodes);
	/*
	 * For specified node in workspace generate routing table
	 *
	 * Utilizes Dijkstra algorithm to find index of exit leading to next hop in shortest path to every other node and shortest path length
	 *
	 * @param origin_i index of node to generate routing table for in regular graph node list
	 *
	 * @return vector representing routing table for specified node with RouteTableItem for every node in graph at corresponding index
	 */
	std::vector<RouteTableItem> run(Index origin_i);

	/*
	 * For every node in workspace generate routing table
	 *
	 * Utilizes Dijkstra algorithm to find index of exit leading to next hop in shortest path to every other node and shortest path length
	 *
	 * @return vector with vectors representing routing table for each node at corresponding index.
	 * This vector holds RouteTableItem for every node in graph at node's index
	 */
	std::vector<std::vector<RouteTableItem>> runAll();

INSPECTABLE:
	Index m_nodeCount;
	std::vector<RouteNode> m_nodes;
	std::vector<NodeStatus> m_nodevisited;
	DistHeap m_heap;

	/*
	 * Ready workspace for running routing algorithm on next origin node
	 *
	 * Reset m_nodeinheap
	 * Reset m_nodevisited
	 * Empty m_heap
	 */
	void m_reset();

};

}
#endif /* INCLUDE_ROUTE_ROUTER_H_ */
