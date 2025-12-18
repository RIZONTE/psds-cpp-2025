#include <vector>
#include <utility>


struct Coord2D {
    int x = 0;
    int y = 0;
};

struct Circle {
    Coord2D coord;
    unsigned radius = 1;
};

using CircleRegion = std::pair<Circle, bool>;
using CircleRegionList = std::vector<CircleRegion>;

std::ostream& operator<<(std::ostream& os, const Coord2D& coord) {
    return os << "(" << coord.x << ", " << coord.y << ")";
}

std::ostream& operator<<(std::ostream& os, const Circle& circle) {
    if(circle.radius == 0) return os << "circle[]";
    return os << "circle[" << circle.coord << ", r = " << circle.radius <<"]";
}

std::ostream& operator<<(std::ostream& os, const CircleRegion& circReg) {
    if(circReg.second) return os << "+" << circReg.first;
    return os << "-" << circReg.first;
}

std::ostream& operator<<(std::ostream& os, const CircleRegionList& regList) {
    if(regList.empty()) return os << "{}";
    os << "{\n\t" << regList[0];
    for(auto it = ++regList.begin(); it != regList.end(); ++it){
        os << ",\n\t" << *it;
    }
    return os << "\n}";
}
