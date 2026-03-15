#include <vector>

std::vector<int> Range(int from, int to, int step = 1) {
    std::vector<int> res;

    if((from > to && step > 0) || (from < to && step < 0) || (step == 0)) {
        return res;
    }

    size_t size = std::abs(to - from) % std::abs(step) == 0 ? 
                  std::abs(to - from) / std::abs(step) : 
                  std::abs(to - from) / std::abs(step) + 1;
    res.reserve(size);

    for(int i = from; from < to ? i < to : i > to; i += step){
        res.push_back(i);
    }
    
    return res;
}
