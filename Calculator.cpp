#include "Calculator.h"
#include <cmath>
int32_t Calculator::calculateProduct(const std::vector<int32_t>& numbers) {
    int32_t product = 1;
    int sign = 1;

    for (const auto& number : numbers) {
        if (number == 0) {
            return 0;
        } else if (number < 0) {
            sign *= -1;
        }

        int32_t absNumber = std::abs(number);
        if (sign > 0 && product > std::numeric_limits<int32_t>::max() / absNumber) {
            return std::numeric_limits<int32_t>::max();
        } else if (sign < 0 && product > (std::numeric_limits<int32_t>::max() - 1) / absNumber) {
            return std::numeric_limits<int32_t>::min();
        }
        product *= absNumber;
    }

    product *= sign;
    return product;
}


