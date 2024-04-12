#include <ostream>

#include "util.h"
namespace piwcs::prw::router{

	std::ostream& operator<<(std::ostream& os, const RouteTableItem& item){
		os <<"{";
		if (item.exitIdx==RouteTableItem::NOT_COMPUTED){
			os << "NC";
		}
		else{
			os << item.exitIdx;
		}
		os << ", ";
		if (item.routeLength==consts::INF){
			os << "INF";
		}
		else{
			os << item.routeLength;
		}
		os << "}";

		return os;
	}


}


