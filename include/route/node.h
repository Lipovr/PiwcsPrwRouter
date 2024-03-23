#ifndef INCLUDE_ROUTE_NODE_H_
#define INCLUDE_ROUTE_NODE_H_
#include <vector>

#include "common.h"
#include "util.h"

namespace piwcs::prw::router{

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
	bool m_isdestination;
	bool m_requiresrouting;

  public:

	RouteNode(const Identifier &id, bool isdestination,
			bool requiresrouting, std::vector<RouteNeighbor> neighbors);

	const Identifier &id() const { return m_id; }

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

	bool requiresRouting() { return m_requiresrouting; }

	bool isDestination() { return m_isdestination; }


};

}

#endif /* INCLUDE_ROUTE_NODE_H_ */
