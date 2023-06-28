#include <gtest/gtest.h>
#include <vector.hpp>

class Vector2Test : public ::testing::Test
{
protected:
    ///< Define some vectors to use in the tests
    Fzolv::Vector2f v1{1.0f, 2.0f};
    Fzolv::Vector2f v2{3.0f, 4.0f};
    Fzolv::Vector2f v3{5.0f, 6.0f};
    Fzolv::Vector2i v4{7, 8};
    Fzolv::Vector2i v5{9, 10};
    Fzolv::Vector2i v6{11, 12};
};

class Vector2ClampTest : public ::testing::Test {
protected:
    // Define some Vector2 objects for testing
    Fzolv::Vector2f v1{3.5, 4.2};
    Fzolv::Vector2f v2{1.0, 2.0};
    Fzolv::Vector2f v3{5.0, 6.0};
    Fzolv::Vector2f v4{3.5, 4.2}; // Expected result of clamping v1 between v2 and v3
};

TEST_F(Vector2Test, DefaultConstructor)
{
    Fzolv::Vector2f v;

    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
}

TEST_F(Vector2Test, CopyConstructor)
{
    Fzolv::Vector2f v{v1};

    EXPECT_FLOAT_EQ(v.x, v1.x);
    EXPECT_FLOAT_EQ(v.y, v1.y);
}

TEST_F(Vector2Test, MoveConstructor)
{
    Fzolv::Vector2f temp{1.0f, 2.0f};
    Fzolv::Vector2f v{std::move(temp)};

    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);

    EXPECT_FLOAT_EQ(temp.x, 0.0f);
    EXPECT_FLOAT_EQ(temp.y, 0.0f);
}

TEST_F(Vector2Test, CopyAssignmentOperator)
{
    v2 = v1;

    EXPECT_FLOAT_EQ(v2.x, v1.x);
    EXPECT_FLOAT_EQ(v2.y, v1.y);
}

TEST_F(Vector2Test, MoveAssignmentOperator)
{
    Fzolv::Vector2f temp{1.0f, 2.0f};
    v3 = std::move(temp);

    EXPECT_FLOAT_EQ(v3.x, 1.0f);
    EXPECT_FLOAT_EQ(v3.y, 2.0f);

    EXPECT_FLOAT_EQ(temp.x, 0.0f);
    EXPECT_FLOAT_EQ(temp.y, 0.0f);
}

TEST_F(Vector2Test, ConstructorFromXY)
{
    Fzolv::Vector2f v{1.0f, 2.0f};

    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
}

TEST_F(Vector2Test, StaticFactoryMethods)
{
    auto v1 = Fzolv::Vector2f::Zero();

    EXPECT_FLOAT_EQ(v1.x, 0.0f);
    EXPECT_FLOAT_EQ(v1.y, 0.0f);

    auto v2 = Fzolv::Vector2f::One();

    EXPECT_FLOAT_EQ(v2.x, 1.0f);
    EXPECT_FLOAT_EQ(v2.y, 1.0f);

    auto v3 = Fzolv::Vector2f::UnitX();

    EXPECT_FLOAT_EQ(v3.x, 1.0f);
    EXPECT_FLOAT_EQ(v3.y, 0.0f);

    auto v4 = Fzolv::Vector2f::UnitY();

    EXPECT_FLOAT_EQ(v4.x, 0.0f);
    EXPECT_FLOAT_EQ(v4.y, 1.0f);
}

TEST_F(Vector2Test, SetMethod)
{
    v1.set(3.0f, 4.0f);

    EXPECT_FLOAT_EQ(v1.x, 3.0f);
    EXPECT_FLOAT_EQ(v1.y, 4.0f);
}

TEST_F(Vector2Test, LengthSquaredMethod)
{
    float lenSq = v1.lengthSquared();
    EXPECT_FLOAT_EQ(lenSq, v1.x * v1.x + v1.y * v1.y);
}

TEST_F(Vector2Test, LengthMethod)
{
    float len = v1.length();
    EXPECT_FLOAT_EQ(len, std::sqrt(v1.x * v1.x + v1.y * v1.y));
}

TEST_F(Vector2Test, NormalizeMethod)
{
    Fzolv::Vector2f &ref = v1.normalize();

    EXPECT_EQ(&ref, &v1);
    EXPECT_FLOAT_EQ(v1.length(), 1.0f);
    EXPECT_FLOAT_EQ(v1.x / v1.y, 0.5f);
}

TEST_F(Vector2Test, DotMethod)
{
    float dot = v1.dot(v2);
    EXPECT_FLOAT_EQ(dot, v1.x * v2.x + v1.y * v2.y);
}

TEST_F(Vector2Test, CrossMethod)
{
    float cross = v1.cross(v2);
    EXPECT_FLOAT_EQ(cross, v1.x * v2.y - v1.y * v2.x);
}

TEST_F(Vector2Test, DistanceToSquaredMethod)
{
    float distSq = v1.distanceToSquared(v2);
    EXPECT_FLOAT_EQ(distSq, (v1 - v2).lengthSquared());
}

TEST_F(Vector2Test, DistanceToMethod)
{
    float dist = v1.distanceTo(v2);
    EXPECT_FLOAT_EQ(dist, (v1 - v2).length());
}

TEST_F(Vector2Test, FloorMethod)
{
    auto &ref = v1.floor();

    EXPECT_EQ(&ref, &v1);
    EXPECT_FLOAT_EQ(v1.x, std::floor(1.0f));
    EXPECT_FLOAT_EQ(v1.y, std::floor(2.0f));
}

TEST_F(Vector2Test, CeilMethod)
{
    auto &ref = v1.ceil();

    EXPECT_EQ(&ref, &v1);
    EXPECT_FLOAT_EQ(v1.x, std::ceil(1.0f));
    EXPECT_FLOAT_EQ(v1.y, std::ceil(2.0f));
}

TEST_F(Vector2Test, RoundMethod)
{
    auto &ref = v1.round();

    EXPECT_EQ(&ref, &v1);
    EXPECT_FLOAT_EQ(v1.x, std::round(1.0f));
    EXPECT_FLOAT_EQ(v1.y, std::round(2.0f));
}

TEST_F(Vector2Test, LerpMethod)
{
    auto v = Fzolv::Vector2f::Lerp(v1, v2, 0.5);

    EXPECT_FLOAT_EQ(v.x, (v1.x + v2.x) / 2.0f);
    EXPECT_FLOAT_EQ(v.y, (v1.y + v2.y) / 2.0f);
}

TEST_F(Vector2Test, ArithmeticOperators)
{
    Fzolv::Vector2f v1plusv2 = v1 + v2;

    EXPECT_FLOAT_EQ(v1plusv2.x, v1.x + v2.x);
    EXPECT_FLOAT_EQ(v1plusv2.y, v1.y + v2.y);

    Fzolv::Vector2f v1minusv2 = v1 - v2;

    EXPECT_FLOAT_EQ(v1minusv2.x, v1.x - v2.x);
    EXPECT_FLOAT_EQ(v1minusv2.y, v1.y - v2.y);

    Fzolv::Vector2f v1times3 = v1 * 3.0f;

    EXPECT_FLOAT_EQ(v1times3.x, v1.x * 3.0f);
    EXPECT_FLOAT_EQ(v1times3.y, v1.y * 3.0f);

    Fzolv::Vector2f v1div2 = v1 / 2.0f;

    EXPECT_FLOAT_EQ(v1div2.x, v1.x / 2.0f);
    EXPECT_FLOAT_EQ(v1div2.y, v1.y / 2.0f);
}

TEST_F(Vector2Test, CompoundAssignmentOperators)
{
    v1 += v2;

    EXPECT_FLOAT_EQ(v1.x, 4.0f);
    EXPECT_FLOAT_EQ(v1.y, 6.0f);

    v1 -= v2;

    EXPECT_FLOAT_EQ(v1.x, 1.0f);
    EXPECT_FLOAT_EQ(v1.y, 2.0f);

    v1 *= 3.0f;

    EXPECT_FLOAT_EQ(v1.x, 3.0f);
    EXPECT_FLOAT_EQ(v1.y, 6.0f);

    v1 /= 3.0f;

    EXPECT_FLOAT_EQ(v1.x, 1.0f);
    EXPECT_FLOAT_EQ(v1.y, 2.0f);
}

TEST_F(Vector2Test, ComparisonOperators)
{
    bool v1eqv2 = (v1 == v2);
    EXPECT_FALSE(v1eqv2);

    bool v1nev2 = (v1 != v2);
    EXPECT_TRUE(v1nev2);

    bool v4eqv5 = (v4 == v5);
    EXPECT_FALSE(v4eqv5);

    bool v4nev5 = (v4 != v5);
    EXPECT_TRUE(v4nev5);
}

TEST_F(Vector2Test, PrivateMembers)
{
    class Accessor
    {
    public:
        static int getX(const Fzolv::Vector2i &v)
        {
            return v.x;
        }

        static int getY(const Fzolv::Vector2i &v)
        {
            return v.y;
        }
    };

    EXPECT_EQ(Accessor::getX(v6), v6.x);
    EXPECT_EQ(Accessor::getY(v6), v6.y);
}

TEST_F(Vector2ClampTest, Clamp) {
    Fzolv::Vector2f result = Fzolv::Vector2f::clamp(v1, v2, v3);
    EXPECT_EQ(result.x, v4.x);
    EXPECT_EQ(result.y, v4.y);
}
