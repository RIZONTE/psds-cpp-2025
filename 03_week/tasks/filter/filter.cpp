#include <vector>

void Filter(std::vector<int>& data, bool (*predicate)(int)) {
    size_t i{0};
    size_t j{0};
    size_t size{data.size()};
    if(predicate == nullptr) return;
    while(j < size){
        if(predicate(data[j])){
            data[i++] = data[j];
        }
        ++j;
    }
    data.resize(i);
}