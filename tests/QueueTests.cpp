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

TEST_F(QueueTest, ClearManyElements)
{
  void *some_data= NULL;

  int firstElem = 10;
  int secondElem = 100;
  int thirdElem = 101;
  int forthElem = 102;

  enqueue(q, &firstElem);
  enqueue(q, &secondElem);
  enqueue(q, &thirdElem);
  enqueue(q, &forthElem);

  EXPECT_EQ(getSize(q), 4);

  clearQueue(q);
  EXPECT_TRUE(getSize(q) == 0);

  EXPECT_TRUE(front(q, some_data) == NULL);
}

TEST_F(QueueTest, FindMemElementExists)
{
  int first = 10;
  int second = 20;
  int third = 30;

  enqueue(q, &first);
  enqueue(q, &second);
  enqueue(q, &third);

  int searchFor = 20;
  int* found = (int*)findMem(q, &searchFor);

  ASSERT_NE(found, nullptr);
  EXPECT_EQ(*found, 20);
}

TEST_F(QueueTest, FindMemElementNotExists)
{
  int first = 10;
  int second = 20;

  enqueue(q, &first);
  enqueue(q, &second);

  int searchFor = 999;
  int* found = (int*)findMem(q, &searchFor);

  EXPECT_EQ(found, nullptr);
}

TEST_F(QueueTest, FindMemLastElement)
{
  int first = 10;
  int second = 20;
  int third = 30;

  enqueue(q, &first);
  enqueue(q, &second);
  enqueue(q, &third);

  int searchFor = 30;
  int* found = (int*)findMem(q, &searchFor);

  ASSERT_NE(found, nullptr);
  EXPECT_EQ(*found, 30);
}

TEST_F(QueueTest, FindMemWithStruct)
{
  queue* structQueue = createQueue(sizeof(foo));

  foo first = {1, 2, 3, 4};
  foo second = {5, 6, 7, 8};
  foo third = {9, 10, 11, 12};

  enqueue(structQueue, &first);
  enqueue(structQueue, &second);
  enqueue(structQueue, &third);

  foo searchFor = {5, 6, 7, 8};
  foo* found = (foo*)findMem(structQueue, &searchFor);

  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found->a, 5);
  EXPECT_EQ(found->b, 6);
  EXPECT_EQ(found->c, 7);
  EXPECT_EQ(found->d, 8);

  destroyQueue(&structQueue);
}

// Predicate function for testing find
static bool isGreaterThan15(void *data)
{
  int value = *(int*)data;
  return value > 15;
}

TEST_F(QueueTest, FindWithPredicate)
{
  int first = 10;
  int second = 20;
  int third = 30;

  enqueue(q, &first);
  enqueue(q, &second);
  enqueue(q, &third);

  int* found = (int*)find(q, isGreaterThan15);

  ASSERT_NE(found, nullptr);
  EXPECT_EQ(*found, 20);  // Should find 20, which is the first value > 15
}
