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
public:

	static const Index NOT_FOUND = ~0;

INSPECTABLE:
	Identifier m_id;
	std::vector<RouteNeighbor> m_neighbors;
	std::vector<RouteTableItem> m_table;
	bool m_isdestination;
	bool m_requiresrouting;

public:
	RouteNode(const Identifier &id,
			bool requiresrouting = true,
			bool isdestination = false,
			Index table_capacity = 0,
			std::vector<RouteNeighbor> &neighbors
			);

	RouteNode(const Identifier &id,
			bool requiresrouting = true,
			bool isdestination = false,
			Index table_capacity = 0,
			Index neighbor_capacity = 0);

	const Identifier &id() const { return m_id; }

	/**
	 * Reserve memory for node's routing table to hold
	 * all possible destinations (all other nodes in graph)
	 */
	void ensureTableCapacity(Index N);

	/**
	 * Create new record in node's routing table. If record for this
	 * node already exists do nothing and return false
	 *
	 * @param destination index of node for which table record will be created
	 * @param exit index of this node's exit from which optimal route to `destination` node starts
	 * @param distance length of optimal route to `destination` node
	 *
	 * @return whether new record was created
	 */
	bool insertTableRecord(Index destination, Index exit, Length distance);

	/**
	 * Reserve memory for node's neighbor list to hold
	 * all its neighbors
	 */
	void ensureNeighborCapacity(Index N);

	/**
	 * Create new record in node's neighbor list.
	 *
	 * @param index index of neighbor to add
	 * @param distance length of connection to neighbor
	 */
	void addNeighbor(Index index, Length distance);

	/**
	 * Checks if node requires routing
	 *
	 * @return whether this node requires routing
	 */
	bool requiresRouting() const { return m_requiresrouting; }

	/**
	 * Checks if node is marked as destination
	 *
	 * @return whether this node is marked as destination
	 */
	bool isDestination() const { return m_isdestination; }

	/**
	 * Find exit index of neighbor with index `index`
	 *
	 * @param index index of neighbor to find
	 *
	 * @return index of exit leading to specified neighbor or RouteNode::NOT_FOUND if specified node is not on neighbor list
	 */
	Index findNeighbor(Index index) const;


};

}

#endif /* INCLUDE_ROUTE_NODE_H_ */
