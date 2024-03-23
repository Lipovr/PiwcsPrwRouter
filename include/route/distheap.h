#ifndef INCLUDE_ROUTE_DISTHEAP_H_
#define INCLUDE_ROUTE_DISTHEAP_H_

#include<queue>

#include "common.h"
#include "util.h"

namespace piwcs::prw::router{

	class HeapItem{
	INSPECTABLE:
		Length routeLength;
		Index current_i;
		Index previous_i;
	public:
		HeapItem(Length _routeLength, Index _current_i, Index _previous_i)
			: routeLength(_routeLength),
			  current_i(_current_i),
			  previous_i(_previous_i)
		{}
		HeapItem() = delete;

		bool operator<(const HeapItem &rhs) const { return this->routeLength < rhs.routeLength; }
		bool operator<=(const HeapItem &rhs) const { return this->routeLength <= rhs.routeLength; }
		bool operator>(const HeapItem &rhs) const { return this->routeLength > rhs.routeLength; }
		bool operator>=(const HeapItem &rhs) const { return this->routeLength >= rhs.routeLength; }
		bool operator==(const HeapItem &rhs) const { return this->routeLength == rhs.routeLength; }
	};

	/*
	 * Wrap around for stl's minimum priority queue and vector
	 * updates vector of route lengths when pushing new item to queue.
	 */
	class DistHeap{
	INSPECTABLE:
		std::priority_queue<
			HeapItem,
			std::vector<HeapItem>,
			std::greater<HeapItem>
			> m_heap;
		std::vector<Length> m_distances;

	public:
		/*
		 * Constructs new DistHeap with given size of underlying containers.
		 *
		 * @param _size capacity of queue to reserve and new size of lengths vector
		 */
		DistHeap(Index _size);

		/*
		 * Adds new item _x to the queue and updates length of route to node with index _x.current_i so that it equals _x.routeLength
		 *
		 * @param _x item to push to queue
		 *
		 * @throws out_of_range exception if `_x.current_i` or `_x.previous_i` is out of range for queue's underlying containers size
		 */
		void add(const HeapItem &_x);

		/*
		 * Removes top item from the queue, corresponding route length is not affected
		 */
		void pop();

		/*
		 * Accesses top (smallest) item of the queue
		 *
		 * @return reference to the top item
		 */
		const HeapItem& top() const;

		/*
		 * Accesses route length for node with given index
		 *
		 * @param index index of node to return
		 *
		 * @return route length for node with index `index`
		 */
		Length dist(Index index) const;

		/*
		 * Checks if underlying queue is empty
		 *
		 * @return whether underlying queue is empty
		 */
		bool empty() const;
	};
}
#endif /* INCLUDE_ROUTE_DISTHEAP_H_ */
