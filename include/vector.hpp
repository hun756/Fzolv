#ifndef FZOLV_VECTOR_hy78kj
#define FZOLV_VECTOR_hy78kj

#include <algorithm>
#include <cmath>
#include <util.hpp>

namespace Fzolv
{
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
        auto operator=(const Vector2 &) -> Vector2 & = default;

        /**
         * @brief Move assignment operator, moves the components from another vector
         *
         * @param other The other vector to move from
         * @return Vector2& A reference to this vector
         */
        auto operator=(Vector2 &&other) noexcept -> Vector2 &
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
        constexpr Vector2(T xVal, T yVal) : x{xVal}, y{yVal} {}

        ///< Static factory methods for common vectors

        /**
         * @brief Static factory method for the zero vector
         *
         * @return constexpr Vector2 The zero vector
         */
        static constexpr auto Zero() -> Vector2 { return {.0F, .0F}; }

        /**
         * @brief Static factory method for the one vector
         *
         * @return constexpr Vector2 The one vector
         */
        static constexpr auto One() -> Vector2 { return {1.0F, 1.0F}; }

        /**
         * @brief Static factory method for the unit x vector
         *
         * @return constexpr Vector2 The unit x vector
         */
        static constexpr auto UnitX() -> Vector2 { return {1.0F, .0F}; }

        /**
         * @brief Static factory method for the unit y vector
         *
         * @return constexpr Vector2 The unit y vector
         */
        static constexpr auto UnitY() -> Vector2 { return {.0F, 1.0F}; }

        /**
         * @brief Set the x and y components of the vector
         *
         * @param x The new x component of the vector
         * @param y The new y component of the vector
         */
        constexpr void set(T xVal, T yVal)
        {
            x = xVal;
            y = yVal;
        }

        /**
         * @brief Get the squared length of the vector
         *
         * @return constexpr T The squared length of the vector
         */
        [[nodiscard]] constexpr auto lengthSquared() const -> T
        {
            return (x * x) + (y * y);
        }

        /**
         * @brief Get the length of the vector
         *
         * @return double The length of the vector
         */
        [[nodiscard]] auto length() const -> double
        {
            return std::sqrt(lengthSquared());
        }

        /**
         * @brief Normalize the vector in-place and return a reference to itself
         *
         * @return Vector2& A reference to this normalized vector
         */
        auto normalize() -> Vector2 &
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
        [[nodiscard]] constexpr auto dot(const Vector2 &other) const -> T
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
        [[nodiscard]] constexpr auto cross(const Vector2 &other) const -> T
        {
            return x * other.y - y * other.x;
        }

        /**
         * @brief Get the squared distance between this vector and another vector
         *
         * @param other The other vector to measure the distance to
         * @return constexpr T The squared distance between the two vectors
         */
        [[nodiscard]] constexpr auto distanceToSquared(const Vector2 &other) const -> T
        {
            auto dxVal = x - other.x;
            auto dyVal = y - other.y;
            return (dxVal * dxVal) + (dyVal * dyVal);
        }

        /**
         * @brief Get the distance between this vector and another vector
         *
         * @param other The other vector to measure the distance to
         * @return double The distance between the two vectors
         */
        [[nodiscard]] auto distanceTo(const Vector2 &other) const -> double
        {
            return std::sqrt(distanceToSquared(other));
        }

        /**
         * @brief Clamps a vector to a given range.
         * 
         * This function template takes a vector of type U and two vectors of the same type representing the minimum and maximum values, 
         * and returns a new vector of type U that is clamped to the range [min, max]. The clamping is done component-wise, using a lambda 
         * expression that clamps a scalar value to a scalar range. The function template uses std::enable_if and std::is_convertible to enable 
         * the function only if U is convertible to Vector2<T>.
         * 
         * @tparam U The type of the vector to be clamped. Must be convertible to Vector2<T>.
         * @param value The vector to be clamped.
         * @param min The vector representing the minimum values.
         * @param max The vector representing the maximum values.
         * @return U A new vector of type U that is clamped to the range [min, max].
         */
        template <typename U> static constexpr auto clamp(const U &value, const U &min, const U &max) 
            -> typename std::enable_if<std::is_convertible<U, Vector2<T>>::value, U>::type
        {
            constexpr auto clamp = [](auto x, auto low, auto high)
            {
                return x > high ? high : (x < low ? low : x);
            };

            return U{clamp(value.x, min.x, max.x), clamp(value.y, min.y, max.y)};
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
        auto floor() -> Vector2 &
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
        auto ceil() -> Vector2 &
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
        auto round() -> Vector2 &
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
        static constexpr auto Lerp(const Vector2 &start, const Vector2 &end, float amount) -> Vector2
        {
            float x = start.x + ((end.x - start.x) * amount);
            float y = start.y + ((end.y - start.y) * amount);
            return {x, y};
        }

        friend constexpr auto operator+(const Vector2 &lhs, const Vector2 &rhs) -> Vector2
        {
            return {lhs.x + rhs.x, lhs.y + rhs.y};
        }

        friend constexpr auto operator-(const Vector2 &lhs, const Vector2 &rhs) -> Vector2
        {
            return {lhs.x - rhs.x, lhs.y - rhs.y};
        }

        friend constexpr auto operator*(const Vector2 &lhs, T scalar) -> Vector2
        {
            return {lhs.x * scalar, lhs.y * scalar};
        }

        friend constexpr auto operator/(const Vector2 &lhs, T scalar) -> Vector2
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
        auto operator+=(const Vector2 &other) -> Vector2 &
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        auto operator-=(const Vector2 &other) -> Vector2 &
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        auto operator*=(T scalar) -> Vector2 &
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        auto operator/=(T scalar) -> Vector2 &
        {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        /**
         * @brief Overload comparison operators for vector equality and inequality
         *
         * Comparison operators are symbols that compare two operands and return a boolean value. For example, == is a comparison operator
         * that checks if two operands are equal and returns true or false. Comparison operators can be overloaded for user-defined types
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
        friend constexpr auto operator==(const Vector2 &lhs, const Vector2 &rhs) -> bool
        {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }

        friend constexpr auto operator!=(const Vector2 &lhs, const Vector2 &rhs) -> bool
        {
            return !(lhs == rhs);
        }
    

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
        Vector3(const Vector3 &&)  noexcept = default;
        auto operator=(const Vector3 &) -> Vector3 & = default;
        auto operator=(Vector3 &&)  noexcept -> Vector3 & = default;

    private:
        T x, y, z;
    };

    using Vector2f = Vector2<float>;
    using Vector2i = Vector2<int>;
    using Vector3f = Vector3<float>;
    using Vector3i = Vector3<int>;
}

#endif /* end of include guard: FZOLV_VECTOR_hy78kj */