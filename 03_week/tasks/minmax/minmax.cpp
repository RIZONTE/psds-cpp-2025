#include <vector>
#include <utility>
#include <limits>

namespace {
    using v_int_cit = std::vector<int>::const_iterator;
}


std::pair<v_int_cit, v_int_cit> MinMax(const std::vector<int>& data){
    auto res = std::make_pair(data.end(), data.end());
    int Min{std::numeric_limits<int>::max()};
    int Max{std::numeric_limits<int>::min()};
    for(auto it = data.begin(); it != data.end(); ++it){
        if(*it < Min){
            Min = *it;
            res.first = it;
        }
        if(*it >= Max){
            Max = *it;
            res.second = it;
        }
    }
    return res;
}
