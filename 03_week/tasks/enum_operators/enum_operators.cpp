#include <stdexcept>
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

/* return_type */ operator|(/* args */) {
    throw std::runtime_error{"Not implemented"};
}

/* return_type */ operator&(/* args */) {
    throw std::runtime_error{"Not implemented"};
}

/* return_type */ operator^(/* args */) {
    throw std::runtime_error{"Not implemented"};
}

/* return_type */ operator~(/* args */) {
    throw std::runtime_error{"Not implemented"};
}

/* return_type */ operator<<(/* args */) {
    throw std::runtime_error{"Not implemented"};
}
