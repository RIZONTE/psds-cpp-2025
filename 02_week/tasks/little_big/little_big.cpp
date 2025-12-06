#include <iostream>
#include <cstddef>
#include <iomanip>

void PrintMemory(int num, bool inverse = false) {
    const size_t size = sizeof(int);
    auto ptr = reinterpret_cast<const unsigned char*>(&num);
    
    std::cout << "0x";
    
    if (inverse) {
        // little-endian
        for (size_t i = size - 1; i < size; --i) {
            std::cout << std::uppercase <<  std::hex << std::setw(2) << std::setfill('0') 
                      << static_cast<unsigned int>(ptr[i]);
        }
    } else {
        // big-endian
        for (size_t i = 0; i < size; ++i) {
            std::cout << std::uppercase << std::hex << std::setw(2) << std::setfill('0') 
                      << static_cast<unsigned int>(ptr[i]);
        }
    }
    std::cout << std::endl;
}

void PrintMemory(double num, bool inverse = false) {
    const size_t size = sizeof(double);
    auto ptr = reinterpret_cast<const unsigned char*>(&num);
    
    std::cout << "0x";
    
    if (inverse) {
        //little-endian
        for (size_t i = size - 1; i < size; --i) {
            std::cout << std::uppercase << std::hex << std::setw(2) << std::setfill('0') 
                      << static_cast<unsigned int>(ptr[i]);
        }
    } else {
        // big-endian
        for (size_t i = 0; i < size; ++i) {
            std::cout << std::uppercase << std::hex << std::setw(2) << std::setfill('0') 
                      << static_cast<unsigned int>(ptr[i]);
        }
    }
    std::cout << std::endl;
}