#include "route/node.h"

namespace piwcs::prw::router {

	RouteNode::RouteNode(const Identifier &id,
			bool requiresrouting = true,
			bool isdestination = false,
			Index table_capacity = 0,
			std::vector<RouteNeighbor> &neighbors
			):
		m_id(id),
		m_isdestination(isdestination),
		m_requiresrouting(requiresrouting),
		m_neighbors(neighbors)
	{
		this->ensureTableCapacity(table_capacity);
	}

	RouteNode::RouteNode(const Identifier &id,
			bool requiresrouting = true,
			bool isdestination = false,
			Index table_capacity = 0,
			Index neighbor_capacity = 0):
		RouteNode(id, requiresrouting, isdestination, table_capacity, std::vector<RouteNeighbor>())
	{
		this->ensureNeighborCapacity(neighbor_capacity);
	}

	void RouteNode::ensureTableCapacity(Index N){
		m_table.resize(N);
	}

	void RouteNode::ensureNeighborCapacity(Index N){
		m_neighbors.reserve(N);
	}

	bool RouteNode::insertTableRecord(Index destination, Index exit, Length distance){
		if (m_table[destination].isComputed()){
			return false;
		}
		else{
			m_table[destination].exitIdx = exit;
			m_table[destination].routeLength = distance;
			return true;
		}
	}

	void RouteNode::addNeighbor(Index index, Length distance){
		m_neighbors.push_back(RouteNeighbor{index, distance});
	}

	Index RouteNode::findNeighbor(Index index) const{
		for(Index i=0; i<m_neighbors.size(); ++i){
			if(index==m_neighbors[i].node_i){
				return i;
			}
		}

		return NOT_FOUND;
	}

	const RouteNeighbor& RouteNode::getNeighbor(Index exit) const{
		return m_neighbors[exit];
	}

	const RouteTableItem& RouteNode::getTableItem(Index destination) const{
		return m_table[destination];
	}

}
