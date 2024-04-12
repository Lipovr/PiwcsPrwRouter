#include "route/node.h"

namespace piwcs::prw::router {

	RouteNode::RouteNode(std::vector<RouteNeighbor> neighbors)
		: m_neighbors(std::move(neighbors))
	{
	}

	RouteNode::RouteNode(Index neighbor_capacity)
	: RouteNode(std::vector<RouteNeighbor>())
	{
		this->ensureNeighborCapacity(neighbor_capacity);
	}

	RouteNode::RouteNode()
	: RouteNode(0)
	{}

	void RouteNode::ensureNeighborCapacity(Index N){
		m_neighbors.reserve(N);
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

	Index RouteNode::neighbourCount() const{
		return m_neighbors.size();
	}

}
