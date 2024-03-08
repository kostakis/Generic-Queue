#include "queue.h"

#include <gtest/gtest.h>

class QueueTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    q = createQueue(sizeof(int));
    ASSERT_TRUE(NULL != q);
  }

  void TearDown() override
  {
    destroyQueue(&q);
    ASSERT_EQ(NULL, q);
  }

  typedef struct Foo
  {
    int a{0};
    int b{0};
    int c{0};
    int d{0};
  } foo;

  void checkSize(int expected)
  {
    ASSERT_EQ(getSize(q), expected);
  }

  queue *q;
};

TEST_F(QueueTest, Enqueue)
{
  int prevSize = getSize(q);
  int a = 10;
  EXPECT_TRUE(enqueue(q, &a) != NULL);
  checkSize(prevSize + 1);
}

TEST_F(QueueTest, Enqueue10)
{
  int prevSize = getSize(q);
  int insertedElements = 10;

  for(int i = 0; i < insertedElements; i++)
  {
    EXPECT_TRUE(enqueue(q, &i) != NULL);
  }

  checkSize(prevSize + insertedElements);
}

TEST_F(QueueTest, Enqueue100)
{
  int prevSize = getSize(q);
  int insertedElements = 100;

  for(int i = 0; i < insertedElements; i++)
  {
    EXPECT_TRUE(enqueue(q, &i) != NULL);
  }

  checkSize(prevSize + insertedElements);
}

TEST_F(QueueTest, Front)
{
  int expected = 10;
  enqueue(q, &expected);

  int returnValue;
  front(q, &returnValue);

  EXPECT_EQ(expected, returnValue);
}

TEST_F(QueueTest, Dequeue)
{
  int firstInsert = 10;
  int secondInsert = 20;
  enqueue(q, &firstInsert);
  enqueue(q, &secondInsert);

  int returned;
  dequeue(q, &returned);

  EXPECT_EQ(firstInsert, returned);
  checkSize(1);
}

TEST_F(QueueTest, Reverse)
{
  int firstElem = 10;
  int secondElem = 100;
  int thirdElem = 101;
  int forthElem = 102;

  enqueue(q, &firstElem);
  enqueue(q, &secondElem);
  enqueue(q, &thirdElem);
  enqueue(q, &forthElem);

  checkSize(4);

  reverse(q);

  int returnValue;
  dequeue(q, &returnValue);
  EXPECT_EQ(returnValue, forthElem);

  dequeue(q, &returnValue);
  EXPECT_EQ(returnValue, thirdElem);

  dequeue(q, &returnValue);
  EXPECT_EQ(returnValue, secondElem);

  dequeue(q, &returnValue);
  EXPECT_EQ(returnValue, firstElem);

  checkSize(0);
}

TEST_F(QueueTest, Clear)
{
  clearQueue(q);
  EXPECT_TRUE(getSize(q) == 0);
}
