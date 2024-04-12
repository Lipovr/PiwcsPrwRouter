#include<iostream>
/* TODO Implement exceptions?
#include<format>*/

#include "route/router.h"

namespace piwcs::prw::router{

Router::Router(const Graph &nodes):
	m_nodes(std::move(nodes)),
	m_nodeCount(nodes.size()),
	m_nodevisited(std::vector<NodeStatus>(nodes.size(), NodeStatus::NOT_VISITED)),
	m_heap(DistHeap(nodes.size())){
	this->m_reset();
}


/*
 * TODO Stub WIP
 */
NodeTable Router::run(Index origin_i){

	/*
	 * Initialize vector representing routing table with default RouteTableItem
	 * for each node.
	 *
	 * This sets every node's optimal path length to consts::INF, and it will stay so
	 * in resulting routing table for nodes that are unreachable from origin
	 */
	auto result = NodeTable(m_nodeCount, RouteTableItem{});

	/*
	 * Bind reference to 'origin' node for convenience
	 */
	const RouteNode& origin = m_nodes[origin_i];

	/*
	 * Initiate Dijkstra's algorithm by adding origin with
	 * zero distance to itself
	 *
	 * We also assume that previous node of route from origin to itself
	 * is origin. Therefore additional check is needed to determine if
	 * we search for route 'origin->origin' and add it to routing table as 'SELF'
	 */
	m_heap.add(HeapItem(0, origin_i, origin_i));

	for(; !m_heap.empty();){
		Index current_i = m_heap.top().current_i;
		Index previous_i = m_heap.top().previous_i;

		m_heap.pop();

		const RouteNode& current = m_nodes[current_i];

		/************************************************/
		/* Iterate over current's neighbors             */
		/************************************************/
		for(Index exit=0; exit<current.neighbourCount(); ++exit){
			const RouteNeighbor& neighbor_info = current.getNeighbor(exit);
			Index neighbor_i = neighbor_info.node_i;

			// Skip neighbor if visited
			if(NodeStatus::VISITED==
					m_nodevisited[neighbor_i]){
				continue;
			}

			Length dist_curr = m_heap.dist(current_i)+neighbor_info.distance;

			/*
			 * No need to check if neighbor is in heap
			 * because in this case its route length will be INF
			 */
			if(dist_curr<m_heap.dist(neighbor_i)){
					m_heap.add(HeapItem(dist_curr, neighbor_i, current_i));
			}
		}

		/************************************************/
		/* Modify origin's routing table                */
		/************************************************/
		Length distance = consts::INF;
		Index exit = RouteTableItem::NOT_COMPUTED;
		/*
		 * Current is origin and this path is marked as path to 'self'
		 */
		if(current_i==origin_i){
			exit = RouteTableItem::NOT_COMPUTED;
			distance = consts::SELF;
		}
		else{
			/*
			 * If we got current node from top of the heap
			 * we can guarantee that its shortest path distance is not consts::INF
			 * and stored in DistHeap
			 */
			distance = m_heap.dist(current_i);

			if(previous_i==origin_i){
				/*
				 * Current is neighbor of origin and we need index of origin's exit
				 * leading to this neighbor
				 */
				exit = origin.findNeighbor(current_i);
				/* TODO Implement exceptions?
				if(RouteNode::NOT_FOUND==exit){
					throw std::format(
							"Neighbor with index '{}' not found at node with index '{}'",
							current_i, origin_i);
				}*/
			}
			else{
				/*
				 *  Current is not neighbor of origin
				 *  and previous has record in table
				 *
				 *  Optimal route to current lies through previous
				 */
				const RouteTableItem& previous_rec = result[previous_i];
				exit = previous_rec.exitIdx;
			}
		} // not self
		result[current_i] = RouteTableItem{exit, distance};

		/************************************************/
		/* Mark current visited                         */
		/************************************************/
		m_nodevisited[current_i] = NodeStatus::VISITED;


	} // heap loop

	/************************************************/
	/* Reset workspace variables                    */
	/************************************************/
	m_reset();

	return result;
} //Router::run

std::vector<NodeTable> Router::runAll(){

	/*
	 * Preallocate resulting vector
	 */
	auto result = std::vector<NodeTable>(m_nodeCount, NodeTable(m_nodeCount));

	/*
	 * Run algorithm for each node
	 */
	for (Index i=0; i<m_nodeCount; ++i){
		result[i] = run(i);
	}
	return result;
}

void Router::m_reset(){
	m_heap.makeEmpty();
	for(Index i=0; i<m_nodeCount; ++i){
		m_nodevisited[i]=NodeStatus::NOT_VISITED;
	}
}

} //namespace piwcs::prw::router

