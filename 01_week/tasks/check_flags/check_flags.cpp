#include <cstdint>
#include <stdexcept>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

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

void PrintCheckFlags(CheckFlags flags) {
    std::unordered_map<uint8_t, std::string> flagStr = {
        {0b00000001,"TIME"},
        {0b00000010,"DATE"},
        {0b00000100,"USER"},
        {0b00001000,"CERT"},
        {0b00010000,"KEYS"},
        {0b00100000,"DEST"}
    };
    
    std::vector<std::string> result = {"["};
    result.reserve(16);

    if(flags == CheckFlags::NONE){
        std::cout << "[]";
        return;
    }
    else if(flags == CheckFlags::ALL)
    {
        std::cout << "[TIME,DATE,USER,CERT,KEYS,DEST]";
        return;
    }
    else if(static_cast<uint8_t>(flags) > static_cast<uint8_t>(CheckFlags::ALL))
    {
        std::cout << "";
        return;
    }
    else
    {
        for(uint8_t flag = 1; flag < static_cast<uint8_t>(CheckFlags::ALL); flag *= 2){
            if(static_cast<uint8_t>(flags) & flag){
                result.push_back(flagStr[flag]);
                result.push_back(",");
            }
        }
    }

    result.pop_back();
    result.push_back("]");


    for(auto& elem : result){
        std::cout << elem;
    }
}
