#include <gtest/gtest.h>

#include "route/distheap.h"

using namespace piwcs::prw::router;
namespace{
#define ALLOCATION_TEST(N, testName)									\
	TEST(DistHeap, testName){											\
		DistHeap heap = DistHeap(N);									\
		ASSERT_EQ(heap.m_distances.size(), N) 							\
		<< "Queue allocation test failed with " << N << " elements"	;	\
	};
} // namespace


ALLOCATION_TEST(0, Preallocate0);
ALLOCATION_TEST(10, Preallocate10);
ALLOCATION_TEST(1000, Preallocate1000);

TEST(DistHeap, Add){
	DistHeap heap = DistHeap(1);
	HeapItem a(10,0,0);
	heap.add(a);
	EXPECT_EQ(heap.top(), a);
	EXPECT_EQ(heap.dist(0), a.routeLength);
};

TEST(DistHeap, AddCurrentOutOfBounds){
	DistHeap heap = DistHeap(10);
	HeapItem a(10,20,0);
	EXPECT_THROW({heap.add(a);},std::out_of_range);
};

TEST(DistHeap, AddPreviousOutOfBounds){
	DistHeap heap = DistHeap(10);
	HeapItem a(10,0,20);
	EXPECT_THROW({
			heap.add(a);
			},
			std::out_of_range);
};

TEST(DistHeap, IsEmpty){
	DistHeap heap = DistHeap(1);
	ASSERT_TRUE(heap.empty());
};

TEST(DistHeap, Pop){
	DistHeap heap = DistHeap(1);
	heap.add(HeapItem(10,0,0));
	ASSERT_TRUE(!heap.empty());
	HeapItem a(10,0,0);
	EXPECT_EQ(heap.top(), a);
	heap.pop();
	ASSERT_TRUE(heap.empty());
};

class DistHeapFilledTests : public testing::Test{
protected:
	DistHeap heap= DistHeap(4);

	void SetUp() override{
		// Populate with some initial values
		heap.add(HeapItem(15,0,3));
		heap.add(HeapItem(8,1,0));
		heap.add(HeapItem(10,2,1));
		heap.add(HeapItem(5,3,2));
	}
};

TEST_F(DistHeapFilledTests, CheckInitial){
	std::vector<Length> test_dist = {15,8,10,5};
	EXPECT_EQ(heap.m_distances, test_dist);
};

TEST_F(DistHeapFilledTests, Update){
	heap.add(HeapItem(1,0,2));
	std::vector<Length> test_dist = {1,8,10,5};
	EXPECT_EQ(heap.m_distances, test_dist);
};

TEST_F(DistHeapFilledTests, PopSorted){
	std::vector<Length> popped;
	std::vector<Length> test_popped = {5,8,10,15};
	for(; !heap.empty(); heap.pop()){
		popped.push_back(heap.top().routeLength);
	}

	EXPECT_EQ(popped, test_popped);
};

TEST_F(DistHeapFilledTests, NotEmptyMakeEmpty){
	heap.makeEmpty();
	EXPECT_TRUE(heap.empty());
}

TEST(DistHeap, EmptyMakeEmpty){
	DistHeap heap = DistHeap(10);
	EXPECT_TRUE(heap.empty());
	heap.makeEmpty();
	EXPECT_TRUE(heap.empty());
}
