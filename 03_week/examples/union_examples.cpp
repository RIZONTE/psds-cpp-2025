#include <cstdint>
#include <iostream>
#include <string>

union ID {
    int i;
    double d;
};

union IBC {
    int i;
    bool b;
    char c;
};

union IDBC {
    int i;
    double d;
    bool b;
    char c;
};

void union_sizeof() {
    std::cout << __func__ << ':' << std::endl;
    std::cout << "sizeof(ID): " << sizeof(ID) << std::endl;       // 8
    std::cout << "sizeof(IBC): " << sizeof(IBC) << std::endl;     // 4
    std::cout << "sizeof(IDBC): " << sizeof(IDBC) << std::endl;   // 8
    std::cout << std::endl;
}

void union_alignof() {
    std::cout << __func__ << ':' << std::endl;
    std::cout << "alignof(ID): " << alignof(ID) << std::endl;      // 8
    std::cout << "alignof(IBC): " << alignof(IBC) << std::endl;    // 4
    std::cout << "alignof(IDBC): " << alignof(IDBC) << std::endl;  // 8
    std::cout << std::endl;
}

void union_address() {
    std::cout << __func__ << ':' << std::endl;
    {
        ID obj;
        obj.i = 42;
        std::cout << "union ID: " << std::endl;
        std::cout << "&obj: " << &obj << std::endl;
        std::cout << "&obj.i: " << &(obj.i) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.i) << std::endl;
        obj.d = 3.14;
        std::cout << "&obj.d: " << &(obj.d) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.d) << std::endl;
    }
    {
        IBC obj;
        obj.i = 42;
        std::cout << "union IBC: " << std::endl;
        std::cout << "&obj: " << &obj << std::endl;
        std::cout << "&obj.i: " << &(obj.i) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.i) << std::endl;
        obj.b = true;
        std::cout << "&obj.b: " << &(obj.b) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&(obj.b)) << std::endl;
        obj.c = 'c';
        std::cout << "&obj.c: " << static_cast<void*>(&(obj.c)) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&(obj.c)) << std::endl;
    }
    {
        IDBC obj;
        obj.i = 42;
        std::cout << "union IDBC: " << std::endl;
        std::cout << "&obj: " << &obj << std::endl;
        std::cout << "&obj.i: " << &(obj.i) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.i) << std::endl;
        obj.d = 3.14;
        std::cout << "&obj.d: " << &(obj.d) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.d) << std::endl;
        obj.b = true;
        std::cout << "&obj.b: " << &(obj.b) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.b) << std::endl;
        obj.c = 'c';
        std::cout << "&obj.c: " << reinterpret_cast<void*>(std::addressof(obj.c)) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.c) << std::endl;
    }
    std::cout << std::endl;
}

union Color {
    uint32_t value;
    struct {
        uint8_t a;
        uint8_t b;
        uint8_t g;
        uint8_t r;
    } components;
};

void union_read_inactive() {
    std::cout << __func__ << ':' << std::endl;
    Color c;
    c.value = 0x00FF9955;

    std::cout << "Red: " << +c.components.r << std::endl;     // 0
    std::cout << "Green: " << +c.components.g << std::endl;   // 255
    std::cout << "Blue: " << +c.components.b << std::endl;    // 153
    std::cout << "Alpha: " << +c.components.a << std::endl;   // 85
    std::cout << std::endl;
}



int main() {
    union_sizeof();
    union_alignof();
    union_address();
    union_read_inactive();
}


