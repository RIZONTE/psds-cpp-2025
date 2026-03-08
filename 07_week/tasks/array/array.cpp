#include <initializer_list>
#include <algorithm>
#include <utility>
#include <iterator>
#include <type_traits>

template <typename Ptr> class Array_iterator;

template <typename T, size_t N = 0>
class Array {
public:
    using iterator = Array_iterator<T*>;
    using const_iterator = Array_iterator<const T*>;

    Array() = default;
    Array(const Array<T, N>& other) = default;
    Array(Array<T, N>&& other) noexcept = default;
    Array<T, N>& operator=(const Array<T, N>& other) = default;
    Array<T, N>& operator=(Array<T, N>&& other) noexcept = default;
    ~Array() = default;
    Array(std::initializer_list<T> list);
    size_t Size() const noexcept;
    bool Empty() const noexcept;
    const T& operator[](size_t index) const;
    T& operator[](size_t index);
    const T& Front() const;
    T& Front();
    const T& Back() const;
    T& Back();
    const T* Data() const;
    T* Data();
    void Fill(T&& value);
    void Swap(Array<T, N>& other);
    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
    auto operator<=>(const Array<T, N>&) const = default;

private:
    T data_[N];
};

template <typename Ptr>
class Array_iterator {
template <typename T, size_t N>
friend class Array;
public:
    using iterator_category [[maybe_unused]] = std::random_access_iterator_tag;
    using value_type = typename std::remove_pointer<Ptr>::type;
    using difference_type = std::ptrdiff_t;
    using pointer = Ptr;
    using reference = std::add_lvalue_reference_t<std::remove_pointer_t<Ptr>>;
    Array_iterator() = default;
    Array_iterator(pointer ptr);
    Array_iterator(const Array_iterator<Ptr>& other);
    Array_iterator<Ptr>& operator=(const Array_iterator<Ptr>& other);
    auto operator<=>(const Array_iterator<Ptr>&) const = default;
    Array_iterator<Ptr>& operator++();
    Array_iterator<Ptr> operator++(int);
    Array_iterator<Ptr>& operator--();
    Array_iterator<Ptr> operator--(int);
    reference operator*() const;
    pointer operator->() const;
    Array_iterator<Ptr> operator+(difference_type n) const;
    Array_iterator<Ptr> operator-(difference_type n) const;
    Array_iterator<Ptr>& operator+=(difference_type n);
    Array_iterator<Ptr>& operator-=(difference_type n);
    difference_type operator-(const Array_iterator<Ptr>& rhs) const;
    reference operator[](difference_type n) const;

    friend Array_iterator<Ptr> operator+(Array_iterator<Ptr>::difference_type lhs, const Array_iterator<Ptr>& rhs) {
        return Array_iterator(lhs + rhs.ptr_);
    }

private:
    pointer ptr_ = nullptr;
};

template <typename T, size_t N>
Array<T, N>::Array(std::initializer_list<T> list) {
    size_t i = 0;
    for (auto& item : list) {
        data_[i++] = item;
    }

    for (; i < N; ++i) {
        data_[i] = T{};
    }
}

template <typename T, size_t N>
size_t Array<T, N>::Size() const noexcept {
    return N;
}

template <typename T, size_t N>
bool Array<T, N>::Empty() const noexcept {
    return N == 0;
}

template <typename T, size_t N>
const T& Array<T, N>::operator[](size_t index) const {
    return data_[index];
}

template <typename T, size_t N>
T& Array<T, N>::operator[](size_t index) {
    return data_[index];
}

template <typename T, size_t N>
const T& Array<T, N>::Front() const {
    return data_[0];
}

template <typename T, size_t N>
T& Array<T, N>::Front() {
    return data_[0];
}

template <typename T, size_t N>
const T& Array<T, N>::Back() const {
    return data_[N-1];
}

template <typename T, size_t N>
T& Array<T, N>::Back() {
    return data_[N-1];
}

template <typename T, size_t N>
const T* Array<T, N>::Data() const {
    return data_;
}

template <typename T, size_t N>
T* Array<T, N>::Data() {
    return data_;
}

template <typename T, size_t N>
void Array<T, N>::Fill(T&& value) {
    if(N == 0) return;
    for(T& el : data_) {
        el = value;
    }
}

template <typename T, size_t N>
void Array<T, N>::Swap(Array<T, N>& other) {
    std::swap(data_, other.data_);
}

template <typename T, size_t N>
void swap(Array<T, N>& a, Array<T, N>& b) {
    a.Swap(b);
}

template <size_t I, typename T, size_t N>
constexpr const T& get(const Array<T, N>& arr) noexcept {
    return arr[I];
}

template <size_t I, typename T, size_t N>
constexpr const T&& get(const Array<T, N>&& arr) noexcept {
    return std::move(arr[I]);
}

template <size_t I, typename T, size_t N>
constexpr T& get(Array<T, N>& arr) noexcept {
    return arr[I];
}

template <size_t I, typename T, size_t N>
constexpr T&& get(Array<T, N>&& arr) noexcept {
    return std::move(arr[I]);
}

template <typename T, size_t N>
Array<T, N>::iterator Array<T, N>::begin() {
    return Array<T, N>::iterator(data_);
}

template <typename T, size_t N>
Array<T, N>::iterator Array<T, N>::end() {
    return Array<T, N>::iterator(data_ + N);
}

template <typename T, size_t N>
Array<T, N>::const_iterator Array<T, N>::cbegin() const {
    return Array<T, N>::const_iterator(data_);
}

template <typename T, size_t N>
Array<T, N>::const_iterator Array<T, N>::cend() const {
    return Array<T, N>::const_iterator(data_ + N);
}

template <typename Ptr>
Array_iterator<Ptr>::Array_iterator(pointer ptr) : ptr_(ptr) {};


template <typename Ptr>
Array_iterator<Ptr>::Array_iterator(const Array_iterator<Ptr>& other) : ptr_(other.ptr_) {};

template <typename Ptr>
Array_iterator<Ptr>& Array_iterator<Ptr>::operator=(const Array_iterator<Ptr>& other) {
    if(this != &other) {
        ptr_ = other.ptr_;
    }
    return *this;
}

template <typename Ptr>
Array_iterator<Ptr>& Array_iterator<Ptr>::operator++() {
    ++ptr_;
    return *this;
}

template <typename Ptr>
Array_iterator<Ptr> Array_iterator<Ptr>::operator++(int) {
    ++ptr_;
    return *this;
}

template <typename Ptr>
Array_iterator<Ptr>& Array_iterator<Ptr>::operator--() {
    --ptr_;
    return *this;
}

template <typename Ptr>
Array_iterator<Ptr> Array_iterator<Ptr>::operator--(int) {
    --ptr_;
    return *this;
}

template <typename Ptr>
Array_iterator<Ptr>::reference Array_iterator<Ptr>::operator*() const {
    return *ptr_;
}

template <typename Ptr>
Array_iterator<Ptr>::pointer Array_iterator<Ptr>::operator->() const {
    return ptr_;
}

template <typename Ptr>
Array_iterator<Ptr> Array_iterator<Ptr>::operator+(Array_iterator<Ptr>::difference_type n) const { 
    return Array_iterator<Ptr>(ptr_ + n);
}

template <typename Ptr>
Array_iterator<Ptr> Array_iterator<Ptr>::operator-(Array_iterator<Ptr>::difference_type n) const {
    return Array_iterator<Ptr>(ptr_ - n);
}

template <typename Ptr>
Array_iterator<Ptr>& Array_iterator<Ptr>::operator+=(Array_iterator<Ptr>::difference_type n) {
    ptr_ += n;
    return *this;
}

template <typename Ptr>
Array_iterator<Ptr>& Array_iterator<Ptr>::operator-=(Array_iterator<Ptr>::difference_type n) {
    ptr_ -= n;
    return *this;
}

template <typename Ptr>
Array_iterator<Ptr>::difference_type Array_iterator<Ptr>::operator-(const Array_iterator<Ptr>& rhs) const {
    return ptr_ - rhs.ptr_;
}

template <typename Ptr>
Array_iterator<Ptr>::reference Array_iterator<Ptr>::operator[](Array_iterator<Ptr>::difference_type n) const {
    return (*ptr_)[n];
}