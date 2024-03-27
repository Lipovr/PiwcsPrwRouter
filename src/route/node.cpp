#include "route/node.h"

namespace piwcs::prw::router {

	RouteNode::RouteNode(Index idx,
			const Identifier &id,
			std::vector<RouteNeighbor> neighbors,
			Index table_capacity,
			bool requiresrouting,
			bool isdestination
			):
		m_index(idx),
		m_id(id),
		m_neighbors(std::move(neighbors)),
		m_requiresrouting(requiresrouting),
		m_isdestination(isdestination)
	{
		this->ensureTableCapacity(table_capacity);
	}

	RouteNode::RouteNode(Index idx,
			const Identifier &id,
			Index table_capacity,
			bool requiresrouting,
			bool isdestination,
			Index neighbor_capacity
			):
		RouteNode(idx, id, std::vector<RouteNeighbor>(), table_capacity, requiresrouting, isdestination)
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
		m_neighbors.emplace_back(index, distance);
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

	Index RouteNode::neighbourCount() const{
		return m_neighbors.size();
	}

}
