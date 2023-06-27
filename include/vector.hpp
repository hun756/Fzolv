#ifndef FZOLV_VECTOR_hy78kj
#define FZOLV_VECTOR_hy78kj

#include <cmath>
#include <type_traits>

namespace Fzolv
{
    /**
     * @brief A template struct that checks if a type is numeric.
     * @tparam T The type to check.
     * @details This struct inherits from std::integral_constant and sets its value to true if T is either an integral
     * or a floating point type, and false otherwise. It uses std::is_integral and std::is_floating_point to perform the check.
     */
    template <typename T>
    struct is_numeric : std::integral_constant<bool, std::is_integral<T>::value || std::is_floating_point<T>::value>
    {
    };

    /**
     * @brief A generic class for 2D vectors with numeric types
     *
     * @tparam T The type of the vector components, must be arithmetic
     */
    template <typename T, typename = std::enable_if_t<is_numeric<T>::value>>
    class Vector2
    {
    public:
        /**
         * @brief Default constructor, initializes the vector to zero
         *
         */
        Vector2() : x(), y(){};

        /**
         * @brief Copy constructor, copies the components from another vector
         *
         * @param other The other vector to copy from
         */
        Vector2(const Vector2 &) = default;

        /**
         * @brief Move constructor, moves the components from another vector
         *
         * @param other The other vector to move from
         */
        Vector2(Vector2 &&other) noexcept
        {
            x = std::move(other.x);
            y = std::move(other.y);

            ///< Empty other
            other.x = 0;
            other.y = 0;
        }

        /**
         * @brief Copy assignment operator, copies the components from another vector
         *
         * @param other The other vector to copy from
         * @return Vector2& A reference to this vector
         */
        Vector2 &operator=(const Vector2 &) = default;

        /**
         * @brief Move assignment operator, moves the components from another vector
         *
         * @param other The other vector to move from
         * @return Vector2& A reference to this vector
         */
        Vector2 &operator=(Vector2 &&other) noexcept
        {
            if (this != &other)
            {
                x = std::move(other.x);
                y = std::move(other.y);

                ///< Empty other
                other.x = 0;
                other.y = 0;
            }

            return *this;
        }

        /**
         * @brief Constructor from x and y components
         *
         * @param x The x component of the vector
         * @param y The y component of the vector
         */
        constexpr Vector2(T x, T y) : x{x}, y{y} {}

        ///< Static factory methods for common vectors

        /**
         * @brief Static factory method for the zero vector
         *
         * @return constexpr Vector2 The zero vector
         */
        static constexpr Vector2 Zero() { return {.0F, .0F}; }

        /**
         * @brief Static factory method for the one vector
         *
         * @return constexpr Vector2 The one vector
         */
        static constexpr Vector2 One() { return {1.0F, 1.0F}; }

        /**
         * @brief Static factory method for the unit x vector
         *
         * @return constexpr Vector2 The unit x vector
         */
        static constexpr Vector2 UnitX() { return {1.0F, .0F}; }

        /**
         * @brief Static factory method for the unit y vector
         *
         * @return constexpr Vector2 The unit y vector
         */
        static constexpr Vector2 UnitY() { return {.0F, 1.0F}; }

        /**
         * @brief Set the x and y components of the vector
         *
         * @param x The new x component of the vector
         * @param y The new y component of the vector
         */
        constexpr void set(T x, T y)
        {
            this->x = x;
            this->y = y;
        }

        /**
         * @brief Get the squared length of the vector
         *
         * @return constexpr T The squared length of the vector
         */
        [[nodiscard]] constexpr T lengthSquared() const
        {
            return (x * x) + (y * y);
        }

        /**
         * @brief Get the length of the vector
         *
         * @return double The length of the vector
         */
        [[nodiscard]] double length() const
        {
            return std::sqrt(lengthSquared());
        }

        /**
         * @brief Normalize the vector in-place and return a reference to itself
         *
         * @return Vector2& A reference to this normalized vector
         */
        Vector2 &normalize()
        {
            auto len = length();
            if (len != 0)
            {
                x /= len;
                y /= len;
            }
            return *this;
        }

        /**
         * @brief Get the dot product of this vector and another vector
         *
         * Dot product is a scalar value that indicates how much two vectors are aligned. It is equal to
         * |a|*|b|*cos(theta), where theta is the angle between them. If they are perpendicular, it is zero.
         * If they are parallel, it is equal to their product of lengths.
         *
         * Dot product can also be used to project one vector onto another. If a and b are unit vectors,
         * then a.dot(b) is equal to the length of a projected onto b.
         *
         * Dot product can also be used to calculate the angle between two vectors. If a and b are non-zero vectors,
         * then theta = acos(a.dot(b) / (|a|*|b|)).
         *
         * Dot product is commutative, meaning that a.dot(b) = b.dot(a).
         *
         * @param other The other vector to dot with
         * @return constexpr T The dot product of the two vectors
         */
        [[nodiscard]] constexpr T dot(const Vector2 &other) const
        {
            return x * other.x + y * other.y;
        }

        /**
         * @brief Get the cross product of this vector and another vector
         *
         * Cross product is a vector value that indicates how much two vectors are perpendicular. It is equal to
         * |a|*|b|*sin(theta)*n, where theta is the angle between them and n is the unit vector perpendicular to
         * both of them. If they are parallel, it is zero. If they are perpendicular, it is equal to their product
         * of lengths.
         *
         * Cross product can also be used to calculate the area of a parallelogram formed by two vectors. If a and b
         * are the sides of the parallelogram, then |a.cross(b)| is equal to the area of the parallelogram.
         *
         * Cross product can also be used to calculate the normal vector of a plane defined by two vectors. If a and b
         * are two non-parallel vectors on the plane, then a.cross(b) is a vector perpendicular to the plane.
         *
         * Cross product is anti-commutative, meaning that a.cross(b) = -b.cross(a).
         *
         * @param other The other vector to cross with
         * @return constexpr T The cross product of the two vectors
         */
        [[nodiscard]] constexpr T cross(const Vector2 &other) const
        {
            return x * other.y - y * other.x;
        }

        /**
         * @brief Get the squared distance between this vector and another vector
         *
         * @param other The other vector to measure the distance to
         * @return constexpr T The squared distance between the two vectors
         */
        [[nodiscard]] constexpr T distanceToSquared(const Vector2 &other) const
        {
            auto dx = x - other.x;
            auto dy = y - other.y;
            return (dx * dx) + (dy * dy);
        }

        /**
         * @brief Get the distance between this vector and another vector
         *
         * @param other The other vector to measure the distance to
         * @return double The distance between the two vectors
         */
        [[nodiscard]] double distanceTo(const Vector2 &other) const
        {
            return std::sqrt(distanceToSquared(other));
        }

        /**
         * @brief Clamp this vector to the maximum components of another vector in-place and return a reference to itself
         *
         * Clamping a vector means limiting its components to a certain range. For example, clamping a vector (3, 5) to the maximum
         * components of (4, 4) results in (3, 4). Clamping can be useful for bounding a vector within a certain region or preventing
         * it from exceeding a certain limit.
         *
         * Clamping is not the same as normalizing. Normalizing a vector means scaling it to have a unit length, while preserving its
         * direction. Clamping a vector does not change its direction, but may change its length.
         *
         * Clamping is also not the same as projecting. Projecting a vector means finding the closest point on a line or a plane that
         * passes through another vector. Projecting a vector does not change its length, but may change its direction.
         *
         * @param other The other vector to clamp to its maximum components
         * @return Vector2& A reference to this clamped vector
         */
        Vector2 &clampToMax(const Vector2 &other)
        {
            if (x > other.x)
                x = other.x;
            if (y > other.y)
                y = other.y;
            return *this;
        }

        /**
         * @brief Clamp this vector to the minimum components of another vector in-place and return a reference to itself
         *
         * Clamping a vector means limiting its components to a certain range. For example, clamping a vector (3, 5) to the minimum
         * components of (4, 4) results in (4, 5). Clamping can be useful for bounding a vector within a certain region or preventing
         * it from exceeding a certain limit.
         *
         * Clamping is not the same as normalizing. Normalizing a vector means scaling it to have a unit length, while preserving its
         * direction. Clamping a vector does not change its direction, but may change its length.
         *
         * Clamping is also not the same as projecting. Projecting a vector means finding the closest point on a line or a plane that
         * passes through another vector. Projecting a vector does not change its length, but may change its direction.
         *
         * @param other The other vector to clamp to its minimum components
         * @return Vector2& A reference to this clamped vector
         */
        Vector2 &clampToMin(const Vector2 &other)
        {
            if (x < other.x)
                x = other.x;
            if (y < other.y)
                y = other.y;
            return *this;
        }

        /**
         * @brief Floor the components of this vector in-place and return a reference to itself
         *
         * Flooring a vector means rounding down its components to the nearest integer. For example, flooring a vector (3.7, 5.2) results
         * in (3, 5). Flooring can be useful for aligning a vector to a grid or snapping it to a lower bound.
         *
         * Flooring is not the same as truncating. Truncating a vector means discarding its fractional part. For example, truncating
         * a vector (3.7, 5.2) results in (3, 5), but truncating a vector (-3.7, -5.2) results in (-3, -5). Flooring always rounds down, while
         * truncating always rounds towards zero.
         *
         * Flooring is also not the same as rounding. Rounding a vector means rounding its components to the nearest integer, or to the nearest multiple
         * of some value. For example, rounding a vector (3.7, 5.2) results in (4, 5), but rounding a vector (-3.7, -5.2) results in (-4, -5). Rounding
         * can be useful for approximating a vector or reducing its precision.
         *
         * @return Vector2& A reference to this floored vector
         */
        Vector2 &floor()
        {
            x = std::floor(x);
            y = std::floor(y);
            return *this;
        }

        /**
         * @brief Ceil the components of this vector in-place and return a reference to itself
         *
         * Ceiling a vector means rounding up its components to the nearest integer. For example, ceiling a vector (3.7, 5.2) results
         * in (4, 6). Ceiling can be useful for aligning a vector to a grid or snapping it to an upper bound.
         *
         * Ceiling is not the same as truncating. Truncating a vector means discarding its fractional part. For example, truncating
         * a vector (3.7, 5.2) results in (3, 5), but truncating a vector (-3.7, -5.2) results in (-3, -5). Ceiling always rounds up, while
         * truncating always rounds towards zero.
         *
         * Ceiling is also not the same as rounding. Rounding a vector means rounding its components to the nearest integer, or to the nearest
         * multiple of some value. For example, rounding a vector (3.7, 5.2) results in (4, 5), but rounding a vector (-3.7, -5.2) results in (-4, -5).
         * Rounding can be useful for approximating a vector or reducing its precision.
         *
         * @return Vector2& A reference to this ceiled vector
         */
        Vector2 &ceil()
        {
            x = std::ceil(x);
            y = std::ceil(y);
            return *this;
        }

        /**
         * @brief Round the components of this vector in-place and return a reference to itself
         *
         * Rounding a vector means rounding its components to the nearest integer, or to the nearest multiple of some value.
         * For example, rounding a vector (3.7, 5.2) results in (4, 5), but rounding a vector (-3.7, -5.2) results in (-4, -5).
         * Rounding can be useful for approximating a vector or reducing its precision.
         *
         * Rounding is not the same as flooring or ceiling. Flooring and ceiling always round down or up respectively, while
         * rounding may round up or down depending on the fractional part. For example, flooring and ceiling a vector (3.5, 4.5)
         * both result in (3, 4), but rounding it results in (4, 5).
         *
         * Rounding is also not the same as truncating. Truncating a vector means discarding its fractional part. For example,
         * truncating a vector (3.7, 5.2) results in (3, 5), but truncating a vector (-3.7, -5.2) results in (-3, -5). Truncating
         * always rounds towards zero, while rounding may round away from zero depending on the fractional part.
         *
         * @return Vector2& A reference to this rounded vector
         */
        Vector2 &round()
        {
            x = std::round(x);
            y = std::round(y);
            return *this;
        }

        /**
         * @brief Overload arithmetic operators for vector addition, subtraction, scalar multiplication and division
         *
         * Arithmetic operators are symbols that perform mathematical operations on operands. For example, + is an arithmetic,
         * operator that performs addition on two operands. Arithmetic operators can be overloaded for user-defined types such
         * as vectors to define how they behave with these operators.
         *
         * Vector addition and subtraction are element-wise operations that result in a new vector with the same dimension as the
         * operands. For example, adding two 2D vectors (a1, b1) and (a2, b2) results in (a1 + a2, b1 + b2). Vector addition and
         * subtraction are commutative and associative, meaning that (a + b) = (b + a) and (a + (b + c)) = ((a + b) + c).
         *
         * Scalar multiplication and division are operations that scale a vector by a scalar value. For example, multiplying a 2D vector
         * (a, b) by a scalar s results in (sa, sb). Scalar multiplication and division are distributive over vector addition and subtraction,
         * meaning that s(a + b) = sa + sb and (a + b)/s = a/s + b/s.
         *
         * @param lhs The left-hand side operand of the operator
         * @param rhs The right-hand side operand of the operator
         * @return friend constexpr Vector2 The result of the operation
         */
        static constexpr Vector2 Lerp(const Vector2 &start, const Vector2 &end, float amount)
        {
            float x = start.x + ((end.x - start.x) * amount);
            float y = start.y + ((end.y - start.y) * amount);
            return {x, y};
        }

        friend constexpr Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs)
        {
            return {lhs.x + rhs.x, lhs.y + rhs.y};
        }

        friend constexpr Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs)
        {
            return {lhs.x - rhs.x, lhs.y - rhs.y};
        }

        friend constexpr Vector2 operator*(const Vector2 &lhs, T scalar)
        {
            return {lhs.x * scalar, lhs.y * scalar};
        }

        friend constexpr Vector2 operator/(const Vector2 &lhs, T scalar)
        {
            return {lhs.x / scalar, lhs.y / scalar};
        }

        /**
         * @brief Overload compound assignment operators for vector addition, subtraction, scalar multiplication and division
         *
         * Compound assignment operators are symbols that perform an arithmetic operation on the left-hand side operand and assign
         * the result to it. For example, += is a compound assignment operator that performs addition on the left-hand side operand
         * and the right-hand side operand and assigns the result to the left-hand side operand. Compound assignment operators can be
         * overloaded for user-defined types such as vectors to define how they behave with these operators.
         *
         * Vector addition and subtraction are element-wise operations that modify the components of the left-hand side vector by adding
         * subtracting the components of the right-hand side vector. For example, adding two 2D vectors (a1, b1) and (a2, b2) and assigning
         * the result to the first vector results in (a1 + a2, b1 + b2) stored in (a1, b1). Vector addition and subtraction are commutative
         * and associative, meaning that (a += b) = (b += a) and (a += (b += c)) = ((a += b) += c).
         */
        Vector2 &operator+=(const Vector2 &other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vector2 &operator-=(const Vector2 &other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Vector2 &operator*=(T scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        Vector2 &operator/=(T scalar)
        {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        /**
         * @brief Overload comparison operators for vector equality and inequality
         *
         * Comparison operators are symbols that compare two operands and return a boolean value. For example, == is a comparison operator
         *  that checks if two operands are equal and returns true or false. Comparison operators can be overloaded for user-defined types
         * such as vectors to define how they behave with these operators.
         *
         * Vector equality and inequality are element-wise operations that check if the components of two vectors are equal or not.
         * For example, checking if two 2D vectors (a1, b1) and (a2, b2) are equal results in true if a1 == a2 and b1 == b2, and false otherwise.
         * Vector equality is reflexive, symmetric and transitive, meaning that (a == a), (a == b) implies (b == a), and (a == b) and (b == c) imply (a == c).
         *
         * @param lhs The left-hand side operand of the operator
         * @param rhs The right-hand side operand of the operator
         * @return friend constexpr bool The result of the comparison
         */
        friend constexpr bool operator==(const Vector2 &lhs, const Vector2 &rhs)
        {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }

        friend constexpr bool operator!=(const Vector2 &lhs, const Vector2 &rhs)
        {
            return !(lhs == rhs);
        }

    public:
        /**
         * @brief The x component of the vector
         */
        T x;

        /**
         * @brief The y component of the vector
         */
        T y;
    };

    template <typename T, typename = std::enable_if_t<is_numeric<T>::value>>
    class Vector3
    {
    public:
        Vector3() = default;
        Vector3(const Vector3 &) = default;
        Vector3(const Vector3 &&) = default;
        Vector3 &operator=(const Vector3 &) = default;
        Vector3 &operator=(const Vector3 &&) = default;

    private:
        T x, y, z;
    };

    using Vector2f = Vector2<float>;
    using Vector2i = Vector2<int>;
    using Vector3f = Vector3<float>;
    using Vector3i = Vector3<int>;
}

#endif /* end of include guard: FZOLV_VECTOR_hy78kj */