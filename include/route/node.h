#ifndef INCLUDE_ROUTE_NODE_H_
#define INCLUDE_ROUTE_NODE_H_
#include <vector>

#include "common.h"
#include "fwd.h"
#include "util.h"

namespace piwcs::prw::router{

/**
 * Structure with information on neighboring node
 * in adjacency list representation.
 *
 * @note A node 'B' is considered a neighbor to another node 'A' if they are
 * connected with a section and 'B' can be reached from 'A'.
 * Thus if 'A' is connected to 'B' with unidirectional
 * section 'A'->'B' 'B' is a neighbor of 'A', but 'A' is not a neighbor of 'B'
 * since it can't be reached.
 */
struct RouteNeighbor{
	Index node_i;
	Length distance;

	bool operator==(const RouteNeighbor& rhs) const = default;
};

/*
 * Class for node of regular graph in adjacency list representation
 *
 * Holds information on neighbors of this node,
 * see @ref RouteNeighbor for details
 */
class RouteNode{
public:

	static constexpr Index NOT_FOUND = ~0;


INSPECTABLE:
	std::vector<RouteNeighbor> m_neighbors;
public:
	RouteNode(std::vector<RouteNeighbor> neighbors);

	RouteNode(Index neighbor_capacity);

	RouteNode();

	bool operator==(const RouteNode &rhs) const = default;

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
	 * Find exit index of neighbor with index `index`
	 *
	 * @param index index of neighbor to find
	 *
	 * @return index of exit leading to specified neighbor or RouteNode::NOT_FOUND if specified node is not on neighbor list
	 */
	Index findNeighbor(Index index) const;

	/**
	 * Get neighbor list entry by exit index
	 *
	 * @param exit index of exit for which to get neighbor
	 *
	 * @return constant reference to requested neighbor list entry
	 */
	const RouteNeighbor& getNeighbor(Index exit) const;

	/**
	 * Get count of this node's neighbors
	 *
	 * @return size of neighbor list
	 */
	Index neighbourCount() const;

};

}

#endif /* INCLUDE_ROUTE_NODE_H_ */
