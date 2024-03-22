#ifndef INCLUDE_ROUTETABLES_H_
#define INCLUDE_ROUTETABLES_H_

#include<unordered_map>
#include<iostream>

#include "util.h"

namespace piwcs::prw::router{

enum class TableNodeType{
	DESTINATION,
	MOTORIZED,
	OTHER,
};

struct TableNode{
	/**
	 * <Origin Id, {exit, distance}>
	 */
	std::unordered_map<Identifier, RouteTableItem> origins;
	TableNodeType type;
	Identifier dadress{};
	Identifier dname{};

};

class RouteTables{
public:
	/*
	 * <Destination Id, TableNode>
	 */
	std::unordered_map<Identifier, TableNode> destinations;

	/*
	 * Output routing data to std::ostream in .csv format
	 */

	friend std::ostream& operator<<(std::ostream &os, const RouteTables& tables);

	friend std::istream& operator>>(std::istream &is, RouteTables& tables);


};

}
#endif /* INCLUDE_ROUTETABLES_H_ */
