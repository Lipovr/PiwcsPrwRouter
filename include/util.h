#ifndef INCLUDE_UTIL_H_
#define INCLUDE_UTIL_H_

#ifdef NDEBUG
#define INSPECTABLE private
#else
#define INSPECTABLE public
#endif

#include<vector>

#include<piwcsprwmodel.h>

#include "fwd.h"

namespace piwcs::prw::router{

/**
 * Type alias for route distance and section lengths.
 *
 */
using Length = uint32_t;

/**
 * Type alias for identifiers. Effectively a string.
 * Inherited from piwcsprwmodel
 */
using Identifier = piwcs::prw::Identifier;

/**
 * Type alias for indexes.
 */
using Index = size_t;

/*
 * A regular graph in adjacency list representation
 * Basically vector of nodes each containing list
 * of reachable neighbors, see @ref RouteNode
 */
using Graph = std::vector<RouteNode>;

/*
 * A routing table for a node in @ref Graph
 * Basically vector of route table entries for every other node in graph.
 * See @ref RouteTableItem
 */
using NodeTable = std::vector<RouteTableItem>;

} // namespace piwcs::prw::router

namespace piwcs::prw::router::consts{
	/**
	 * Constant for infinite length of a route (e.g. destination unreachable)
	 */
	constexpr Length INF = ~0;
	/**
	 * Constant for length of route from a node to itself
	 */
	constexpr Length SELF = 0;
}

namespace piwcs::prw::router{

/*
 * Structure for routing table entry for a node where
 * 'exitIdx' is index of exit leading to next hop in shortest path to this node
 * 'routeLength' length of shortest path to this node
 */
struct RouteTableItem{
	static constexpr Index NOT_COMPUTED = ~0;

	Index exitIdx = NOT_COMPUTED;
	Length routeLength = consts::INF;

	bool isComputed() const {return exitIdx != NOT_COMPUTED;}

	bool operator==(const RouteTableItem& rhs) const = default;

	friend std::ostream& operator<<(std::ostream& os, const RouteTableItem& item);

};

std::ostream& operator<<(std::ostream& os, const RouteTableItem& item);


}
#endif /* INCLUDE_UTIL_H_ */
