#include "queue.h"

#include <gtest/gtest.h>

class DestroyQueueTest : public ::testing::Test {
protected:
	void SetUp() override {
		q = createQueue(sizeof(Foo));
	}

	void TearDown() override {
		EXPECT_EQ(NULL, q);
	}

	struct Foo {
		int a = 0;
		int b = 0;
	};

	queue* q;
};

TEST_F(DestroyQueueTest, DestroyTwoElementsInserted) {
	Foo foo1;
	Foo foo2;

	EXPECT_TRUE(enqueue(q, &foo1) != NULL);
	EXPECT_TRUE(enqueue(q, &foo2) != NULL);

	destroyQueue(&q);
}

TEST_F(DestroyQueueTest, DestroyOneElementInserted) {
	Foo foo1;

	EXPECT_TRUE(enqueue(q, &foo1) != NULL);

	destroyQueue(&q);
}
