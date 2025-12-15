#include <stdexcept>
#include <vector>
#include <utility>


struct Coord2D {
    int x;
    int y;
};

struct Circle {
    Coord2D coord;
    unsigned radius;
};

using CircleRegion = std::pair<Circle, bool>;
using CircleRegionList = std::vector<CircleRegion>;

/* return_type */ operator<<(/* args */) {
    throw std::runtime_error{"Not implemented"};
}
