#ifndef INCLUDE_ROUTE_DISTHEAP_H_
#define INCLUDE_ROUTE_DISTHEAP_H_

#include<queue>

#include "util.h"

namespace piwcs::prw::router{

	class HeapElement{
	public:
		const Length routeLength;
		const Index current_i;
		const Index previous_i;

		//Length operator<=>(const HeapElement &rhs) const {return this.routeLength - rhs.routelength};
		bool operator<(const HeapElement &rhs) const { return this->routeLength < rhs.routeLength; }
		bool operator<=(const HeapElement &rhs) const { return this->routeLength <= rhs.routeLength; }
		bool operator>(const HeapElement &rhs) const { return this->routeLength > rhs.routeLength; }
		bool operator>=(const HeapElement &rhs) const { return this->routeLength >= rhs.routeLength; }
		bool operator==(const HeapElement &rhs) const { return this->routeLength == rhs.routeLength; }
	};

	using DistHeap = std::priority_queue<HeapElement>;
}
#endif /* INCLUDE_ROUTE_DISTHEAP_H_ */
