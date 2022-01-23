#include "queue.h"

#include <gtest/gtest.h>

class QueueTest : public ::testing::Test {
protected:
    void SetUp() override {
        q = createQueue(sizeof(int));
    }

    void TearDown() override {
        destroyQueue(q);
    }

    queue* q;
};

TEST_F(QueueTest, Creation) { ASSERT_TRUE(q != NULL); }

TEST_F(QueueTest, Enqueue) {
    int prevSize = getSize(q);
    int a = 10;
    EXPECT_TRUE(enqueue(q, &a) != NULL);
    EXPECT_EQ(prevSize + 1, getSize(q));
}

TEST_F(QueueTest, Clear) {
    clearQueue(q);
    EXPECT_TRUE(getSize(q) == 0);
}
