#pragma once
#include <cstdint>
#include <limits>
#include <vector>

class Calculator {
public:
    std::vector<int32_t> calculateProducts(const std::vector<std::vector<int32_t>>& vectors);
    int32_t calculateProduct(const std::vector<int32_t>& numbers);
};
