#ifndef INCLUDE_ROUTE_NODE_H_
#define INCLUDE_ROUTE_NODE_H_
#include <vector>

#
#include "util.h"

namespace piwcs::prw::router{

enum class NodeStatus {
		NOT_VISITED,
		VISITED,
	};

/**
 * Structure with information on neighboring node
 * in adjacency list representation.
 *
 * @note A node 'B' is considered a neighbor to another node 'A' if they are
 * connected with a section and 'B' be reached from 'A'.
 * Thus if 'A' is connected to 'B' with unidirectional
 * section 'A'->'B' 'B' is a neighbor of 'A', but 'A' is not a neighbor of 'B'
 * since it can't be reached.
 */
struct RouteNeighbor{
	Index node_i;
	Length distance;
};

class RouteNode{
  INSPECTABLE:
	Identifier m_id;
	std::vector<RouteNeighbor> m_neighbors;
	std::vector<RouteTableItem> m_table;
	NodeStatus m_visitstatus;
	bool m_isdestination;

  public:

	RouteNode(const Identifier &id);

	const Identifier &id() const { return m_id; }

	NodeStatus visitStatus() const { return m_visitstatus; }

	void markVisited() { m_visitstatus = NodeStatus::VISITED; }
	/*
	 * Reserve memory for node's routing table to hold
	 * all possible destinations (all other nodes in graph)
	 */
	void ensureTableCapacity(Index N);
	/*
	 * Create new record in node's routing table. If record for this
	 * node already exists*
	 */
	bool insertTableRecord(Index destination, Index exit, Length distance);

	void addNeighbor(Index index, Length distance);


};

}

#endif /* INCLUDE_ROUTE_NODE_H_ */
