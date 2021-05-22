#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertion1) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
}

TEST(HelloTest, BasicAssertion2) {
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}