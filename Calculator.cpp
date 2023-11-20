#include "Calculator.h"

int32_t Calculator::calculateProduct(const std::vector<int32_t>& numbers) {
    int32_t product = 1;

    for (const auto& number : numbers) {
        if (number == 0) {
            return 0;
        } else if (product > (std::numeric_limits<int32_t>::max() / number)) {
            return std::numeric_limits<int32_t>::max();
        } else if (product < (std::numeric_limits<int32_t>::min() / number)) {
            return std::numeric_limits<int32_t>::min();
        }
        product *= number;
        if (product < 0) {
            return std::numeric_limits<int32_t>::max();
        }
    }

    return static_cast<int32_t>(product);
}

