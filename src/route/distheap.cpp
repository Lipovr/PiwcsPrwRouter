#include<stdexcept>
#include<format>

#include "route/distheap.h"

namespace piwcs::prw::router{

	DistHeap::DistHeap(Index _capacity){
		m_distances.resize(_capacity);
		this->m_markAllInf();

	}

	void DistHeap::m_markAllInf(){
		for(auto it=m_distances.begin(); it<m_distances.end(); ++it){
			*it = consts::INF;
		}
	}

	void DistHeap::add(const HeapItem &_x){
		if(_x.current_i>=m_distances.size()){
			throw std::out_of_range(std::format(
					"Value of current_i: {} is out of range for heap of size {}",
					_x.current_i, m_distances.size()
					));
		}
		if(_x.previous_i>=m_distances.size()){
			throw std::out_of_range(std::format(
					"Value of previous_i: {} is out of range for heap of size {}",
					_x.previous_i, m_distances.size()
					));
		}
		m_heap.emplace(_x.routeLength, _x.current_i, _x.previous_i);
		m_distances[_x.current_i] = _x.routeLength;
	}

	const HeapItem& DistHeap::top() const{
		return m_heap.top();
	}

	void DistHeap::pop(){
		m_heap.pop();
	}

	Length DistHeap::dist(Index _idx) const{
		return m_distances[_idx];
	}

	bool DistHeap::empty() const{
		return m_heap.empty();
	}

	void DistHeap::makeEmpty(){
		for(;!this->empty();){
			m_heap.pop();
		}
		this->m_markAllInf();

	}




}
