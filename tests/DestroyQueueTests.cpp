#include "queue.h"

#include <gtest/gtest.h>

class DestroyQueueTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    q = createQueue(sizeof(Foo));
    ASSERT_TRUE(NULL != q);
  }

  void TearDown() override
  {
    ASSERT_EQ(NULL, q);
  }

  struct Foo
  {
    int a = 0;
    int b = 0;
  };

  queue *q;
};

TEST_F(DestroyQueueTest, DestroyTwoElementsInserted)
{
  Foo foo1;
  Foo foo2;

  EXPECT_TRUE(enqueue(q, &foo1) != NULL);
  EXPECT_TRUE(enqueue(q, &foo2) != NULL);

  destroyQueue(&q);
}

TEST_F(DestroyQueueTest, DestroyOneElementInserted)
{
  Foo foo1;

  EXPECT_TRUE(enqueue(q, &foo1) != NULL);

  destroyQueue(&q);
}

TEST_F(DestroyQueueTest, DestroyNullQueueWorks)
{
  destroyQueue(&q);
  ASSERT_TRUE(q == NULL);
  EXPECT_NO_THROW(destroyQueue(&q));
}
