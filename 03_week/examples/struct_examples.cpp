#include <iostream>
#include <string>

struct BoolBool { bool x; bool y; };
struct Point { int x; int y; };
struct IID { int x; int y; double d; };
struct IDI { int x; double d; int y;};
struct IDIB { int x; double d; int y; bool b;};
struct IIDB { int x; int y; double d; bool b;};
struct IISDB { int x; int y; std::string s; double d; bool b;};


void struct_sizeof() {
    std::cout << __func__ << ':' << std::endl;
    std::cout << "sizeof(BoolBool): " << sizeof(BoolBool) << std::endl; // 2
    std::cout << "sizeof(Point): " << sizeof(Point) << std::endl;       // 8
    std::cout << "sizeof(IID): " << sizeof(IID) << std::endl;           // 16
    std::cout << "sizeof(IDI): " << sizeof(IDI) << std::endl;           // 24
    std::cout << "sizeof(IDIB): " << sizeof(IDIB) << std::endl;         // 24
    std::cout << "sizeof(IIDB): " << sizeof(IIDB) << std::endl;         // 24
    std::cout << "sizeof(IISDB): " << sizeof(IISDB) << std::endl;       // 56
    std::cout << std::endl;
}

void struct_alignof() {
    std::cout << __func__ << ':' << std::endl;
    std::cout << "alignof(BoolBool): " << alignof(BoolBool) << std::endl; // 1
    std::cout << "alignof(Point): " << alignof(Point) << std::endl;       // 4
    std::cout << "alignof(IID): " << alignof(IID) << std::endl;           // 8
    std::cout << "alignof(IDI): " << alignof(IDI) << std::endl;           // 8
    std::cout << "alignof(IDIB): " << alignof(IDIB) << std::endl;         // 8
    std::cout << "alignof(IIDB): " << alignof(IIDB) << std::endl;         // 8
    std::cout << "alignof(IISDB): " << alignof(IISDB) << std::endl;       // 8
    std::cout << std::endl;
}

void struct_address() {
    std::cout << __func__ << ':' << std::endl;
    {
        BoolBool obj;
        std::cout << "struct BoolBool: " << std::endl;
        std::cout << "&obj: " << &obj << std::endl;
        std::cout << "&obj.x: " << &(obj.x) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.x) << std::endl;
        std::cout << "&obj.y: " << &(obj.y) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.y) << std::endl;
    }
    {
        Point obj;
        std::cout << "struct Point: " << std::endl;
        std::cout << "&obj: " << &obj << std::endl;
        std::cout << "&obj.x: " << &(obj.x) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.x) << std::endl;
        std::cout << "&obj.y: " << &(obj.y) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.y) << std::endl;
    }
    {
        IID obj;
        std::cout << "struct IID: " << std::endl;
        std::cout << "&obj: " << &obj << std::endl;
        std::cout << "&obj.x: " << &(obj.x) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.x) << std::endl;
        std::cout << "&obj.y: " << &(obj.y) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.y) << std::endl;
        std::cout << "&obj.d: " << &(obj.d) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.d) << std::endl;

    }
    {
        IDI obj;
        std::cout << "struct IDI: " << std::endl;
        std::cout << "&obj: " << &obj << std::endl;
        std::cout << "&obj.x: " << &(obj.x) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.x) << std::endl;
        std::cout << "&obj.d: " << &(obj.d) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.d) << std::endl;
        std::cout << "&obj.y: " << &(obj.y) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.y) << std::endl;
    }
    {
        IDIB obj;
        std::cout << "struct IDIB: " << std::endl;
        std::cout << "&obj: " << &obj << std::endl;
        std::cout << "&obj.x: " << &(obj.x) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.x) << std::endl;
        std::cout << "&obj.d: " << &(obj.d) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.d) << std::endl;
        std::cout << "&obj.y: " << &(obj.y) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.y) << std::endl;
        std::cout << "&obj.b: " << &(obj.b) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.b) << std::endl;
    }
    {
        IIDB obj;
        std::cout << "struct IIDB: " << std::endl;
        std::cout << "&obj: " << &obj << std::endl;
        std::cout << "&obj.x: " << &(obj.x) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.x) << std::endl;
        std::cout << "&obj.y: " << &(obj.y) << " distance ="
           << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.y) << std::endl;
        std::cout << "&obj.d: " << &(obj.d) << " distance ="
           << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.d) << std::endl;
        std::cout << "&obj.b: " << &(obj.b) << " distance ="
           << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.b) << std::endl;
    }
    {
        IISDB obj;
        std::cout << "struct IISDB: " << std::endl;
        std::cout << "&obj: " << &obj << std::endl;
        std::cout << "&obj.x: " << &(obj.x) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.x) << std::endl;
        std::cout << "&obj.y: " << &(obj.y) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.y) << std::endl;
        std::cout << "&obj.s: " << &(obj.s) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.s) << std::endl;
        std::cout << "&obj.d: " << &(obj.d) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.d) << std::endl;
        std::cout << "&obj.b: " << &(obj.b) << " distance ="
            << reinterpret_cast<char*>(&obj) - reinterpret_cast<char*>(&obj.b) << std::endl;
    }
    std::cout << std::endl;
}

void struct_creation() {
    std::cout << __func__ << ':' << std::endl;
    {
        Point p;
        Point p2 = {1, 2};
        Point p3{2, 3};
        Point p4 = {};
        Point p5 = {1};
    }
    {
        std::string Point = "some_product_name";
        // Point p = {10, 300};     // compile error
        struct Point p = {10, 300}; // OK
    }
    std::cout << std::endl;
}

struct Inner {
    bool b = false;
};

struct A {
    int a = 0;
    Inner inner = {};
};

void struct_inner() {
    std::cout << __func__ << ':' << std::endl;
    std::cout << "sizeof(Inner): " << sizeof(Inner) << std::endl; // 1
    std::cout << "sizeof(A): " << sizeof(A) << std::endl;         // 8
    std::cout << "alignof(Inner): " << alignof(Inner) << std::endl; // 1
    std::cout << "alignof(A): " << alignof(A) << std::endl;         // 4
    A obj;
    std::cout << "obj.inner.b = " << obj.inner.b << std::endl;
    obj.inner.b = true;
    std::cout << "obj.inner.b = true" << std::endl;
    std::cout << "obj.inner.b = " << obj.inner.b << std::endl;
    std::cout << std::endl;
}

int main() {
    struct_sizeof();
    struct_alignof();
    struct_address();
    struct_creation();
    struct_inner();
}


