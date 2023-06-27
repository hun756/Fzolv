#include <gtest/gtest.h>
#include <vector.hpp>

TEST(SimpleFirstTest,FzlovVectorTest)
{
    auto point = Fzolv::Vector2<int>();
    point.x = 1;
    point.y = 2;
    
    ASSERT_EQ(point.x, 1);
    ASSERT_EQ(point.y, 2);
}