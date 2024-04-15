#ifndef INCLUDE_ROUTE_GRAPHMETADATA_H_
#define INCLUDE_ROUTE_GRAPHMETADATA_H_

#include<vector>

#include "util.h"

namespace piwcs::prw::router{

struct GraphMetaItem{
	Identifier idmap;
	bool routeable;
	bool destination;

	GraphMetaItem(
			  const Identifier& _idmap
			, bool _routeable
			, bool _destination
			);

}; // struct GraphMetaItem

using GraphMetadata = std::vector<GraphMetaItem>;

} // namespace piwcs::prw::router

#endif /* INCLUDE_ROUTE_GRAPHMETADATA_H_ */
