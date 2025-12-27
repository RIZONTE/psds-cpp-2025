#include <vector>
#include <stack>
#include <initializer_list>


class Queue {
public:
    Queue(std::stack<int>& stack);
    Queue(const std::vector<int>& vec);
    Queue(const std::initializer_list<int> list);
    Queue(size_t size);
    Queue() = default;
    void Push(int value);
    bool Pop();
    int& Front();
    int& Back();
    const int& Front() const;
    const int& Back() const;
    bool Empty() const;
    size_t Size() const;
    void Clear();
    void Swap(Queue& other);
    bool operator==(const Queue& rhs) const;
    bool operator!=(const Queue& rhs) const;

private:
    std::vector<int> in_;
    std::vector<int> out_;
};


Queue::Queue(std::stack<int>& stack) {
    out_.reserve(stack.size() * 1.2);
    while(!(stack.empty())){
        out_.push_back(stack.top());
        stack.pop();
    }
}
Queue::Queue(const std::vector<int>& vec) {
    out_.reserve(vec.size() * 1.5);
    out_.insert(out_.end(), vec.rbegin(), vec.rend());
}
Queue::Queue(std::initializer_list<int> list) {
    out_.reserve(list.size() * 1.5);
    for(auto it = std::rbegin(list); it != std::rend(list); ++it){
        out_.push_back(*it);
    }
}
Queue::Queue(size_t size) {
    out_.reserve(size);
    in_.reserve(size);
}

void Queue::Push(int value){
    in_.push_back(value);
}
bool Queue::Pop(){
    if(in_.empty() && out_.empty()) return false;
    if(out_.empty() && !(in_.empty())){
        while(!(in_.empty())){
            out_.push_back(in_.back());
            in_.pop_back();
        }
    }
    out_.pop_back();
    return true;
}
int& Queue::Front() {
    if(out_.empty()) return in_.front();
    return out_.back();
}
int& Queue::Back() {
    if(in_.empty()) return out_.front();
    return in_.back();
}
const int& Queue::Front() const {
    if(out_.empty()) return in_.front();
    return out_.back();
}
const int& Queue::Back() const {
    if(in_.empty()) return out_.front();
    return in_.back();
}
bool Queue::Empty() const {
    if(in_.empty() && out_.empty()) return true;
    return false;
}
size_t Queue::Size() const {
    return in_.size() + out_.size();
}
void Queue::Clear() {
    in_.clear();
    out_.clear();
}
void Queue::Swap(Queue& other) {
    in_.swap(other.in_);
    out_.swap(other.out_);
}

bool Queue::operator==(const Queue& rhs) const {
    std::vector<int> tmp_lhs(this->in_.rbegin(), this->in_.rend());
    tmp_lhs.insert(tmp_lhs.end(), this->out_.begin(), this->out_.end());
    std::vector<int> tmp_rhs(rhs.in_.rbegin(), rhs.in_.rend());
    tmp_rhs.insert(tmp_rhs.end(), rhs.out_.begin(), rhs.out_.end());

    return tmp_lhs == tmp_rhs;
}
bool Queue::operator!=(const Queue& rhs) const {
    return !(*this == rhs);
}