#include "Calculator.h"

int64_t Calculator::calculateProduct(const std::vector<int32_t>& numbers) {
    int64_t product = 1;
    bool overflowFlag = false;

    for(uint32_t i=0; i<numbers.size(); i++){
        if (product > (std::numeric_limits < int64_t > ::max() / numbers[i])) {
            product = std::numeric_limits < int64_t > ::max();
            overflowFlag = true;
            break;
        }
        product = product * numbers[i];
    }
    
    int64_t result;
    if( overflowFlag )
        result = product;
    else
        result = product;

    return result;
}
