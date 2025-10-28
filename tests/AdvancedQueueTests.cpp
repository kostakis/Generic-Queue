#include "queue.h"

#include <gtest/gtest.h>
#include <string.h>

class AdvancedQueueTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    q = createQueue(sizeof(int));
    ASSERT_TRUE(NULL != q);
  }

  void TearDown() override
  {
    if(q != NULL)
    {
      destroyQueue(&q);
      ASSERT_EQ(NULL, q);
    }
  }

  struct ComplexData
  {
    int id;
    char name[32];
    double value;
  };

  queue *q;
};

TEST_F(AdvancedQueueTest, IsEmptyOnNewQueue)
{
  EXPECT_TRUE(isEmpty(q));
  EXPECT_EQ(getSize(q), 0);
}

TEST_F(AdvancedQueueTest, IsEmptyAfterEnqueue)
{
  int val = 42;
  enqueue(q, &val);
  EXPECT_FALSE(isEmpty(q));
  EXPECT_EQ(getSize(q), 1);
}

TEST_F(AdvancedQueueTest, IsEmptyAfterDequeue)
{
  int val = 42;
  int result;
  enqueue(q, &val);
  dequeue(q, &result);
  EXPECT_TRUE(isEmpty(q));
  EXPECT_EQ(getSize(q), 0);
}

TEST_F(AdvancedQueueTest, GetAllocationSizeReturnsCorrectSize)
{
  EXPECT_EQ(getAllocationSize(q), sizeof(int));
}

TEST_F(AdvancedQueueTest, GetAllocationSizeWithDifferentTypes)
{
  queue *doubleQueue = createQueue(sizeof(double));
  EXPECT_EQ(getAllocationSize(doubleQueue), sizeof(double));
  destroyQueue(&doubleQueue);

  queue *structQueue = createQueue(sizeof(ComplexData));
  EXPECT_EQ(getAllocationSize(structQueue), sizeof(ComplexData));
  destroyQueue(&structQueue);
}

TEST_F(AdvancedQueueTest, GetAllocationSizeWithNullQueue)
{
  EXPECT_EQ(getAllocationSize(NULL), 0);
}

// Test copyQueue function
TEST_F(AdvancedQueueTest, CopyEmptyQueue)
{
  queue *copy = copyQueue(q);
  ASSERT_TRUE(copy != NULL);
  EXPECT_EQ(getSize(copy), 0);
  EXPECT_TRUE(isEmpty(copy));
  EXPECT_EQ(getAllocationSize(copy), getAllocationSize(q));
  destroyQueue(&copy);
}

TEST_F(AdvancedQueueTest, CopySingleElementQueue)
{
  int val = 100;
  enqueue(q, &val);

  queue *copy = copyQueue(q);
  ASSERT_TRUE(copy != NULL);
  EXPECT_EQ(getSize(copy), getSize(q));

  int originalFront, copyFront;
  front(q, &originalFront);
  front(copy, &copyFront);
  EXPECT_EQ(originalFront, copyFront);

  destroyQueue(&copy);
}

TEST_F(AdvancedQueueTest, CopyMultipleElementQueue)
{
  for(int i = 0; i < 10; i++)
  {
    enqueue(q, &i);
  }

  queue *copy = copyQueue(q);
  ASSERT_TRUE(copy != NULL);
  EXPECT_EQ(getSize(copy), 10);

  // Verify all elements match
  for(int i = 0; i < 10; i++)
  {
    int originalVal, copyVal;
    dequeue(q, &originalVal);
    dequeue(copy, &copyVal);
    EXPECT_EQ(originalVal, copyVal);
  }

  destroyQueue(&copy);
}

TEST_F(AdvancedQueueTest, CopyQueueIsIndependent)
{
  int val1 = 10, val2 = 20;
  enqueue(q, &val1);
  enqueue(q, &val2);

  queue *copy = copyQueue(q);

  // Modify original
  int val3 = 30;
  enqueue(q, &val3);

  // Copy should be unaffected
  EXPECT_EQ(getSize(q), 3);
  EXPECT_EQ(getSize(copy), 2);

  destroyQueue(&copy);
}

TEST_F(AdvancedQueueTest, CopyNullQueueReturnsNull)
{
  queue *copy = copyQueue(NULL);
  EXPECT_EQ(copy, (queue*)NULL);
}

TEST_F(AdvancedQueueTest, EnqueueWithNullQueue)
{
  int val = 42;
  EXPECT_EQ(enqueue(NULL, &val), (queue*)NULL);
}

TEST_F(AdvancedQueueTest, EnqueueWithNullData)
{
  EXPECT_EQ(enqueue(q, NULL), (queue*)NULL);
}

TEST_F(AdvancedQueueTest, DequeueWithNullQueue)
{
  int val;
  EXPECT_EQ(dequeue(NULL, &val), (queue*)NULL);
}

TEST_F(AdvancedQueueTest, DequeueEmptyQueue)
{
  int val;
  EXPECT_EQ(dequeue(q, &val), (queue*)NULL);
}

TEST_F(AdvancedQueueTest, FrontWithNullQueue)
{
  int val;
  EXPECT_EQ(front(NULL, &val), (queue*)NULL);
}

TEST_F(AdvancedQueueTest, FrontOnEmptyQueue)
{
  int val;
  EXPECT_EQ(front(q, &val), (queue*)NULL);
}

TEST_F(AdvancedQueueTest, ReverseNullQueue)
{
  EXPECT_EQ(reverse(NULL), (queue*)NULL);
}

TEST_F(AdvancedQueueTest, ReverseEmptyQueue)
{
  queue *result = reverse(q);
  EXPECT_TRUE(result != NULL);
  EXPECT_TRUE(isEmpty(q));
}

TEST_F(AdvancedQueueTest, ReverseSingleElementQueue)
{
  int val = 42;
  enqueue(q, &val);
  reverse(q);

  int result;
  front(q, &result);
  EXPECT_EQ(result, 42);
}

TEST_F(AdvancedQueueTest, ClearNullQueue)
{
  EXPECT_EQ(clearQueue(NULL), (queue*)NULL);
}

TEST_F(AdvancedQueueTest, GetSizeWithNullQueue)
{
  EXPECT_EQ(getSize(NULL), 0);
}

// Test complex data types
TEST_F(AdvancedQueueTest, QueueWithStrings)
{
  destroyQueue(&q);
  q = createQueue(32 * sizeof(char));

  char str1[] = "Hello";
  char str2[] = "World";
  char str3[] = "Queue";

  enqueue(q, str1);
  enqueue(q, str2);
  enqueue(q, str3);

  char result[32];
  dequeue(q, result);
  EXPECT_STREQ(result, "Hello");

  dequeue(q, result);
  EXPECT_STREQ(result, "World");

  dequeue(q, result);
  EXPECT_STREQ(result, "Queue");
}

TEST_F(AdvancedQueueTest, QueueWithComplexStructs)
{
  destroyQueue(&q);
  q = createQueue(sizeof(ComplexData));

  ComplexData data1 = {1, "Alice", 99.5};
  ComplexData data2 = {2, "Bob", 87.3};
  ComplexData data3 = {3, "Charlie", 92.1};

  enqueue(q, &data1);
  enqueue(q, &data2);
  enqueue(q, &data3);

  ComplexData result;
  dequeue(q, &result);
  EXPECT_EQ(result.id, 1);
  EXPECT_STREQ(result.name, "Alice");
  EXPECT_DOUBLE_EQ(result.value, 99.5);

  dequeue(q, &result);
  EXPECT_EQ(result.id, 2);
  EXPECT_STREQ(result.name, "Bob");
  EXPECT_DOUBLE_EQ(result.value, 87.3);
}

// Test mixed operations
TEST_F(AdvancedQueueTest, InterleavedEnqueueDequeue)
{
  for(int i = 0; i < 5; i++)
  {
    enqueue(q, &i);
  }

  int result;
  dequeue(q, &result);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(getSize(q), 4);

  int val = 100;
  enqueue(q, &val);
  EXPECT_EQ(getSize(q), 5);

  dequeue(q, &result);
  EXPECT_EQ(result, 1);
}

TEST_F(AdvancedQueueTest, MultipleReversesRestoresOrder)
{
  int values[] = {1, 2, 3, 4, 5};
  for(int i = 0; i < 5; i++)
  {
    enqueue(q, &values[i]);
  }

  // First reverse
  reverse(q);
  int result;
  front(q, &result);
  EXPECT_EQ(result, 5);

  // Second reverse (should restore original order)
  reverse(q);
  front(q, &result);
  EXPECT_EQ(result, 1);
}

TEST_F(AdvancedQueueTest, ClearAndReuse)
{
  for(int i = 0; i < 10; i++)
  {
    enqueue(q, &i);
  }
  EXPECT_EQ(getSize(q), 10);

  clearQueue(q);
  EXPECT_EQ(getSize(q), 0);
  EXPECT_TRUE(isEmpty(q));

  // Reuse after clear
  int val = 999;
  enqueue(q, &val);
  EXPECT_EQ(getSize(q), 1);

  int result;
  dequeue(q, &result);
  EXPECT_EQ(result, 999);
}

TEST_F(AdvancedQueueTest, ReverseAfterClearAndReuse)
{
  for(int i = 0; i < 3; i++)
  {
    enqueue(q, &i);
  }

  clearQueue(q);

  int values[] = {10, 20, 30};
  for(int i = 0; i < 3; i++)
  {
    enqueue(q, &values[i]);
  }

  reverse(q);

  int result;
  dequeue(q, &result);
  EXPECT_EQ(result, 30);
}

// Stress tests
TEST_F(AdvancedQueueTest, LargeQueueOperations)
{
  const int LARGE_SIZE = 10000;

  for(int i = 0; i < LARGE_SIZE; i++)
  {
    ASSERT_TRUE(enqueue(q, &i) != NULL);
  }

  EXPECT_EQ(getSize(q), LARGE_SIZE);

  int result;
  for(int i = 0; i < LARGE_SIZE; i++)
  {
    ASSERT_TRUE(dequeue(q, &result) != NULL);
    EXPECT_EQ(result, i);
  }

  EXPECT_TRUE(isEmpty(q));
}

TEST_F(AdvancedQueueTest, StressCopyLargeQueue)
{
  const int SIZE = 1000;

  for(int i = 0; i < SIZE; i++)
  {
    enqueue(q, &i);
  }

  queue *copy = copyQueue(q);
  ASSERT_TRUE(copy != NULL);
  EXPECT_EQ(getSize(copy), SIZE);

  // Verify independence by clearing original
  clearQueue(q);
  EXPECT_EQ(getSize(copy), SIZE);

  destroyQueue(&copy);
}

TEST_F(AdvancedQueueTest, FrontDoesNotModifyQueue)
{
  int val = 42;
  enqueue(q, &val);

  size_t sizeBefore = getSize(q);

  int result;
  front(q, &result);
  front(q, &result);
  front(q, &result);

  EXPECT_EQ(getSize(q), sizeBefore);
  EXPECT_EQ(result, 42);
}

TEST_F(AdvancedQueueTest, CopyThenModifyBoth)
{
  int values[] = {1, 2, 3};
  for(int i = 0; i < 3; i++)
  {
    enqueue(q, &values[i]);
  }

  queue *copy = copyQueue(q);

  // Modify original
  int result;
  dequeue(q, &result);
  EXPECT_EQ(result, 1);
  EXPECT_EQ(getSize(q), 2);

  // Modify copy
  int newVal = 100;
  enqueue(copy, &newVal);
  EXPECT_EQ(getSize(copy), 4);

  // Verify independence
  EXPECT_EQ(getSize(q), 2);

  destroyQueue(&copy);
}

TEST_F(AdvancedQueueTest, ReverseLargeQueue)
{
  const int SIZE = 100;

  for(int i = 0; i < SIZE; i++)
  {
    enqueue(q, &i);
  }

  reverse(q);

  int result;
  for(int i = SIZE - 1; i >= 0; i--)
  {
    dequeue(q, &result);
    EXPECT_EQ(result, i);
  }
}
