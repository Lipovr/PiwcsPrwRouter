#ifndef INCLUDE_UTIL_H_
#define INCLUDE_UTIL_H_

#include<piwcsprwmodel.h>


namespace piwcs::prw::router{

/**
 * Type alias for route distance and section lengths.
 * Inherited from prwmodel
 */
using Length = piwcs::prw::Section::Length;

/**
 * Type alias for identifiers. Effectively a string.
 * Inherited from prwmodel
 */
using Identifier = piwcs::prw::Identifier;

using Index = size_t;

struct RouteTableItem{
	static constexpr Index NOT_COMPUTED = ~0;
	static constexpr Length INF = ~0;

	Index exitIdx = NOT_COMPUTED;
	Length routeLength = INF;

	bool isComputed() const {return exitIdx != NOT_COMPUTED;}

};

}
#endif /* INCLUDE_UTIL_H_ */
