#include <cstddef>
#include <vector>

enum class CheckFlags : uint8_t {
    NONE = 0,
    TIME = (1 << 0),
    DATE = (1 << 1),
    USER = (1 << 2),
    CERT = (1 << 3),
    KEYS = (1 << 4),
    DEST = (1 << 5),
    ALL = TIME | DATE | USER | CERT | KEYS | DEST
};

CheckFlags operator|(const CheckFlags& lhs, const CheckFlags& rhs) {
    uint8_t res = static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs);
    res = res & static_cast<uint8_t>(CheckFlags::ALL);
    return static_cast<CheckFlags>(res);
}

bool operator&(const CheckFlags& lhs, const CheckFlags& rhs) { 
    uint8_t all_uint8 = static_cast<uint8_t>(CheckFlags::ALL);
    uint8_t lhs_uint8 = static_cast<uint8_t>(lhs) & all_uint8;
    uint8_t rhs_uint8 = static_cast<uint8_t>(rhs) & all_uint8;
    if(lhs_uint8 == 0 || rhs_uint8 == 0) return false;
    if(((lhs_uint8 & rhs_uint8) == lhs_uint8) || ((lhs_uint8 & rhs_uint8) == rhs_uint8)) return true;
    return false;
}

CheckFlags operator^(const CheckFlags& lhs, const CheckFlags& rhs) {
    uint8_t all_uint8 = static_cast<uint8_t>(CheckFlags::ALL);
    uint8_t lhs_uint8 = static_cast<uint8_t>(lhs) & all_uint8;
    uint8_t rhs_uint8 = static_cast<uint8_t>(rhs) & all_uint8;
    return static_cast<CheckFlags>(lhs_uint8 ^ rhs_uint8);
}

CheckFlags operator~(const CheckFlags& flags) {
    return static_cast<CheckFlags>(~(static_cast<uint8_t>(flags)) & static_cast<uint8_t>(CheckFlags::ALL));
}

std::ostream& operator<<(std::ostream& os, const CheckFlags& flags) {
    //Хэш-таблица для быстрого преобразования uint8_t -> string
    std::unordered_map<uint8_t, std::string> flagStr = {
        {0b00000001,"TIME"},
        {0b00000010,"DATE"},
        {0b00000100,"USER"},
        {0b00001000,"CERT"},
        {0b00010000,"KEYS"},
        {0b00100000,"DEST"}
    };

    //Вектор с результатом работы функции
    std::vector<std::string> result;
    //Резервирование места под элементы, чтобы не было лишних реаллокаций
    result.reserve(16);

    for(uint8_t flag = 1; flag < static_cast<uint8_t>(CheckFlags::ALL); flag *= 2){
        if(static_cast<uint8_t>(flags) & flag){
            result.push_back( !result.empty() ? ", " : "");
            result.push_back(flagStr[flag]);
        }
    }

    for(auto& elem : result) os << elem;

    if(result.empty()) os << "NONE";

    return os;
}
