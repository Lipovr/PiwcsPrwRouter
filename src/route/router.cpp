#include <iostream>

#include "route/router.h"

namespace piwcs::prw::router{

#ifndef NDEBUG
static std::unique_ptr<AlgWorkspace> AlgWorkspace::d_makeDebugWorkspace(){
	return std::make_unique<AlgWorkspace>(std::vector<RouteNode>());
}

Index AlgWorkspace::d_addNode(const Identifier &id, bool isdestination, bool requiresrouting){
	RouteNode node = RouteNode(id, isdestination, requiresrouting, std::vector<RouteNeighbor>());
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

/*
 * TODO Stub WIP
 */
void AlgWorkspace::m_run(){
	for (Index origin_i = 0; origin_i<m_nodes.size(); origin_i++){
		if (!m_nodes[origin_i].requiresRouting()){
			continue;
		}

		/*
		 *  Reset workspace variables
		 */
		for (auto it = m_nodeinheap.begin(); it != m_nodeinheap.end(); it++){
			*it = false;
		}


		if (!m_heap.empty()){
			// "It will never happen"
			#ifdef NDEBUG
			std::cout << "Heap is not empty, emptying" << "/n";
			#endif /* NDEBUG */
			// Empty the heap
			for (; !m_heap.empty(); m_heap.pop()){}
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

