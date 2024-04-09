#include<iostream>
#include<format>

#include "route/router.h"

namespace piwcs::prw::router{

#ifndef NDEBUG
static std::unique_ptr<AlgWorkspace> AlgWorkspace::d_makeDebugWorkspace(){
	return std::make_unique<AlgWorkspace>(std::vector<RouteNode>());
}

Index AlgWorkspace::d_addNode(const Identifier &id, Index table_capacity, bool requiresrouting, bool isdestination){
	RouteNode node = RouteNode(id, table_capacity, requiresrouting, isdestination);
	m_nodes.push_back(node);

	return m_nodes.size() - 1;
}

void AlgWorkspace::d_addSection(Index from, Index to, Length distance){
	m_nodes[from].addNeighbor(to, distance);

}

#endif // NDEBUG

static RouteTables AlgWorkspace::makeRouteTables(const Model &InModel){
	auto workspaceptr = m_makeWorkspace(InModel);
	workspaceptr->m_run();
	return workspaceptr->m_getTables();
}

AlgWorkspace::AlgWorkspace(const std::vector<RouteNode> &nodes):
	m_nodes(std::move(nodes)),
	m_nodeCount(m_nodes.size()),
	m_nodeinheap(std::vector<bool>(m_nodeCount, false)),
	m_nodevisited(std::vector<NodeStatus>(m_nodeCount, NodeStatus::NOT_VISITED)),
	m_heap(DistHeap(m_nodeCount)){
	this->m_reset();
}

/*
 * TODO Stub WIP
 */
void AlgWorkspace::m_run(){
	for (Index origin_i = 0; origin_i<m_nodes.size(); origin_i++){
		if (!m_nodes[origin_i].requiresRouting()){
			continue;
		}
		RouteNode& origin = m_nodes[origin_i];
		/*
		 *  Reset workspace variables
		 */
		m_reset();

		/*
		 * Initiate Dijkstra's algorithm by adding origin with
		 * zero distance to itself
		 *
		 * We also assume that previous node of route from origin to itself
		 * is origin. Therefore additional check is needed to determine if
		 * we search for this route to add it to routing table as 'SELF'
		 */
		m_heap.add(HeapItem(0, origin_i, origin_i));

		for(; !m_heap.empty();){
			Index current_i = m_heap.top().current_i;
			Index previous_i = m_heap.top().previous_i;

			RouteNode& current = m_nodes[current_i];

			/************************************************/
			/* Iterate over current's neighbors             */
			/************************************************/
			for(Index exit=0; exit<current.neighbourCount(); ++exit){
				// Skip neighbor if visited
				if(NodeStatus::VISITED==
						m_nodevisited[current.getNeighbor(exit).node_i]){
					continue;
				}

				RouteNeighbor& neighbor_p = current.getNeighbor(exit);
				Index neighbor_i = neighbor_p.node_i;
				RouteNode& neighbor = m_nodes[neighbor_i];
				Length dist_curr = m_heap.dist(current_i)+neighbor_p.distance;

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
			if(current_i==origin_i){
				exit = RouteTableItem::NOT_COMPUTED;
				distance = consts::SELF;
			}
			else{

				if(previous_i==origin_i){
					// Current is neighbor of origin
					exit = origin.findNeighbor(current_i);
					if(RouteNode::NOT_FOUND==exit){
						throw std::format(
								"Neighbor with index '{}' not found at node with index '{}'",
								current_i, origin_i);
					}
					distance = origin.getNeighbor(exit).distance;
				}
				else{
					/*
					 *  Current is not neighbor of origin
					 *  and previous has record in table
					 *
					 *  Optimal route to current lies through previous
					 */
					RouteTableItem& previous_rec = origin.getTableItem(previous_i);
					exit = previous_rec.exitIdx;
					distance = m_heap.dist(current_i);
				}
			}
			origin.insertTableRecord(current_i, exit, distance);

			/************************************************/
			/* Mark current visited                         */
			/************************************************/
			m_nodevisited[current_i] = NodeStatus::VISITED;

		}

	}
}

/*
 * TODO Stub WIP
 */
RouteTables AlgWorkspace::m_getTables(){
	return RouteTables();
}

void AlgWorkspace::m_reset(){
	m_heap.makeEmpty();
	for(Index i=0; i<m_nodeCount;){
		m_nodeinheap[i]=false;
		m_nodevisited[i]=NodeStatus::NOT_VISITED;
	}
}

}

