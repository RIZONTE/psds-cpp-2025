#include <vector>

std::vector<size_t> FindAll(const std::vector<int>& data, bool(*predicat)(int)){
    std::vector<size_t> res;
    if(predicat != nullptr){
        res.reserve(data.size() / 2);
        for(size_t i = 0; i < data.size(); ++i){
            if(predicat(data[i])) res.push_back(i);
        }
    }
    return res;
}