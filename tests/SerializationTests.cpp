#include "queue.h"

#include <gtest/gtest.h>

class SerializationTest : public ::testing::Test
{
protected:
  queue *q;

  void SetUp() override
  {
    q = createQueue(sizeof(int));
  }

  void TearDown() override
  {
    destroyQueue(&q);
  }
};

TEST_F(SerializationTest, SerializeEmptyQueue)
{
  void *buffer;
  size_t bufferSize;

  SerializeResult result = serializeQueueToNewBuffer(q, &buffer, &bufferSize);
  EXPECT_EQ(result, SERIALIZE_ERROR_EMPTY_QUEUE);
}

TEST_F(SerializationTest, SerializeSingleElement)
{
  int initialValue = 42;
  ASSERT_TRUE(enqueue(q, &initialValue) != NULL);

  void *buffer = NULL;
  size_t bufferSize = 0;

  SerializeResult result = serializeQueueToNewBuffer(q, &buffer, &bufferSize);
  EXPECT_EQ(result, SERIALIZE_SUCCESS);
  EXPECT_TRUE(buffer != NULL);
  EXPECT_GT(bufferSize, 0);

  // Deserialize
  queue *restored = NULL;
  result = deserializeQueueFromBuffer(buffer, bufferSize, &restored);
  EXPECT_EQ(result, SERIALIZE_SUCCESS);
  EXPECT_TRUE(restored != NULL);
  EXPECT_EQ(getSize(restored), 1);

  int restoredValue;
  dequeue(restored, &restoredValue);
  EXPECT_EQ(initialValue, restoredValue);

  free(buffer);
  destroyQueue(&restored);
}

TEST_F(SerializationTest, SerializeMultipleElements)
{
  int values[] = {10, 20, 30, 40, 50};
  for(int i = 0; i < 5; i++)
  {
    ASSERT_TRUE(enqueue(q, &values[i]) != NULL);
  }

  void *buffer = NULL;
  size_t bufferSize = 0;

  SerializeResult result = serializeQueueToNewBuffer(q, &buffer, &bufferSize);
  EXPECT_EQ(result, SERIALIZE_SUCCESS);
  EXPECT_TRUE(buffer != NULL);
  EXPECT_GT(bufferSize, 0);

  // Deserialize
  queue *restored = NULL;
  result = deserializeQueueFromBuffer(buffer, bufferSize, &restored);
  EXPECT_EQ(result, SERIALIZE_SUCCESS);
  EXPECT_TRUE(restored != NULL);
  EXPECT_EQ(getSize(restored), 5);

  // Check values
  for(int i = 0; i < 5; i++)
  {
    int restoredValue;
    dequeue(restored, &restoredValue);
    EXPECT_EQ(values[i], restoredValue);
  }

  free(buffer);
  destroyQueue(&restored);
}

TEST_F(SerializationTest, SerializeWithStruct)
{
  // Recreate the queue since it was created to hold ints
  destroyQueue(&q);
  typedef struct
  {
    int id;
    double value;
    char name[10];
  } TestStruct;

  q = createQueue(sizeof(TestStruct));
  ASSERT_TRUE(NULL != q);

  TestStruct data[] = {{1, 1.5, "first"}, {2, 2.5, "second"}, {3, 3.5, "third"}};

  for(int i = 0; i < 3; i++)
  {
    ASSERT_TRUE(enqueue(q, &data[i]) != NULL);
  }

  void *buffer = NULL;
  size_t bufferSize = 0;

  SerializeResult result = serializeQueueToNewBuffer(q, &buffer, &bufferSize);
  EXPECT_EQ(result, SERIALIZE_SUCCESS);
  EXPECT_TRUE(buffer != NULL);
  EXPECT_GT(bufferSize, 0);

  // Deserialize
  queue *restored = NULL;
  result = deserializeQueueFromBuffer(buffer, bufferSize, &restored);
  EXPECT_EQ(result, SERIALIZE_SUCCESS);
  EXPECT_TRUE(restored != NULL);
  EXPECT_EQ(getSize(restored), 3);

  // Check values
  for(int i = 0; i < 3; i++)
  {
    TestStruct restoredData;
    dequeue(restored, &restoredData);
    EXPECT_EQ(data[i].id, restoredData.id);
    EXPECT_DOUBLE_EQ(data[i].value, restoredData.value);
    EXPECT_STREQ(data[i].name, restoredData.name);
  }

  free(buffer);
  destroyQueue(&restored);
}

TEST_F(SerializationTest, NullPointerHandling)
{
  void *buffer = NULL;
  size_t bufferSize = 0;

  // Test null queue
  SerializeResult result = serializeQueueToNewBuffer(NULL, &buffer, &bufferSize);
  EXPECT_EQ(result, SERIALIZE_ERROR_NULL_POINTER);

  // Test null buffer pointer
  result = serializeQueueToNewBuffer(q, NULL, &bufferSize);
  EXPECT_EQ(result, SERIALIZE_ERROR_NULL_POINTER);

  // Test null buffer size pointer
  result = serializeQueueToNewBuffer(q, &buffer, NULL);
  EXPECT_EQ(result, SERIALIZE_ERROR_NULL_POINTER);
}