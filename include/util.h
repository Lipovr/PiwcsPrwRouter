#ifndef INCLUDE_UTIL_H_
#define INCLUDE_UTIL_H_

#include<piwcsprwmodel.h>
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
}

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
