#ifndef FZOLV_UTIL_mzn8c4
#define FZOLV_UTIL_mzn8c4

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
}

#endif /* end of include guard : FZOLV_UTIL_mzn8c4 */