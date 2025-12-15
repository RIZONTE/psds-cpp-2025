#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include "os_overload.cpp"

TEST(Coord2DTest, DefaultConstructor) {
    Coord2D coord;
    EXPECT_EQ(coord.x, 0);
    EXPECT_EQ(coord.y, 0);
}

TEST(Coord2DTest, Coord2DCreation) {
    Coord2D coord = {5, -3};
    EXPECT_EQ(coord.x, 5);
    EXPECT_EQ(coord.y, -3);
}

TEST(Coord2DTest, OutputOperator) {
    {
        Coord2D coord;
        std::ostringstream oss;
        oss << coord;
        EXPECT_EQ(oss.str(), "(0, 0)");
    }
    {
        Coord2D coord{42, -15};
        std::ostringstream oss;
        oss << coord;
        EXPECT_EQ(oss.str(), "(42, -15)");
    }
    {
        Coord2D coord{-1, 3};
        std::ostringstream oss;
        oss << coord;
        EXPECT_EQ(oss.str(), "(-1, 3)");
    }
}

TEST(CircleTest, DefaultConstructor) {
    Circle circle;
    EXPECT_EQ(circle.coord.x, 0);
    EXPECT_EQ(circle.coord.y, 0);
    EXPECT_EQ(circle.radius, 1u);
}

TEST(CircleTest, CircleCreation) {
    {
        Coord2D center{10, 20};
        Circle circle(center, 5);
        EXPECT_EQ(circle.coord.x, 10);
        EXPECT_EQ(circle.coord.y, 20);
        EXPECT_EQ(circle.radius, 5u);
    }
    {
        Circle circle({-5, 7});
        EXPECT_EQ(circle.coord.x, -5);
        EXPECT_EQ(circle.coord.y, 7);
        EXPECT_EQ(circle.radius, 1u);
    }
}

TEST(CircleTest, OutputOperator) {
    {
        Circle circle;
        std::ostringstream oss;
        oss << circle;
        EXPECT_EQ(oss.str(), "circle[(0, 0), r = 1]");
    }
    {
        Coord2D center(-1, 3);
        Circle circle(center, 5);
        std::ostringstream oss;
        oss << circle;
        EXPECT_EQ(oss.str(), "circle[(-1, 3), r = 5]");
    }
    {
        Coord2D center(0, 0);
        Circle circle(center, 17);
        std::ostringstream oss;
        oss << circle;
        EXPECT_EQ(oss.str(), "circle[(0, 0), r = 17]");
    }
    {
        Coord2D center(10, 10);
        Circle circle(center, 0);
        std::ostringstream oss;
        oss << circle;
        EXPECT_EQ(oss.str(), "circle[]");
    }
    {
        Coord2D center(100, -200);
        Circle circle(center, 1000);
        std::ostringstream oss;
        oss << circle;
        EXPECT_EQ(oss.str(), "circle[(100, -200), r = 1000]");
    }
}

TEST(CircleRegionTest, CreateAndOutput) {
    {
        Circle circle({3, 4});
        CircleRegion region(circle, true);
        std::ostringstream oss;
        oss << region;
        EXPECT_EQ(oss.str(), "+circle[(3, 4), r = 1]");
    }
    {
        Circle circle({-5, -6}, 7);
        CircleRegion region(circle, false);
        std::ostringstream oss;
        oss << region;
        EXPECT_EQ(oss.str(), "-circle[(-5, -6), r = 7]");
    }
    {
        Circle circle({1, 2}, 0);
        CircleRegion region(circle, true);
        std::ostringstream oss;
        oss << region;
        EXPECT_EQ(oss.str(), "+circle[]");
    }
    {
        Circle circle({1, 2}, 0);
        CircleRegion region(circle, false);
        std::ostringstream oss;
        oss << region;
        EXPECT_EQ(oss.str(), "-circle[]");
    }
}

TEST(CircleRegionListTest, EmptyList) {
    CircleRegionList empty_list;
    std::ostringstream oss;
    oss << empty_list;
    std::string expected = "{}";
    EXPECT_EQ(oss.str(), expected);
}

TEST(CircleRegionListTest, SingleElement) {
    CircleRegionList list;
    list.emplace_back(Circle(Coord2D{1, 2}, 3), true);
    std::ostringstream oss;
    oss << list;
    std::string expected = "{\n\t+circle[(1, 2), r = 3]\n}";
    EXPECT_EQ(oss.str(), expected);
}

TEST(CircleRegionListTest, MultipleElements) {
    CircleRegionList list;
    list.emplace_back(Circle(Coord2D(-1, 3), 5), true);
    list.emplace_back(Circle(Coord2D(0, 0), 17), false);
    list.emplace_back(Circle(Coord2D(10, 20), 0), true);
    list.emplace_back(Circle(Coord2D(-5, -5), 0), false);

    std::ostringstream oss;
    oss << list;

    std::string expected =
        "{\n"
        "\t+circle[(-1, 3), r = 5],\n"
        "\t-circle[(0, 0), r = 17],\n"
        "\t+circle[],\n"
        "\t-circle[]\n"
        "}";
    EXPECT_EQ(oss.str(), expected);
}

TEST(CircleRegionListTest, VariousCombinations) {
    CircleRegionList list;

    // Добавляем разные комбинации
    list.emplace_back(Circle({0, 0}), true);
    list.emplace_back(Circle(Coord2D(5, 5), 10), false);
    list.emplace_back(Circle(Coord2D(-10, -10), 0), true);
    list.emplace_back(Circle(Coord2D(100, 200), 50), true);
    list.emplace_back(Circle(Coord2D(-3, 7), 2), false);

    std::ostringstream oss;
    oss << list;

    std::string expected =
        "{\n"
        "\t+circle[(0, 0), r = 1],\n"
        "\t-circle[(5, 5), r = 10],\n"
        "\t+circle[],\n"
        "\t+circle[(100, 200), r = 50],\n"
        "\t-circle[(-3, 7), r = 2]\n"
        "}";
    EXPECT_EQ(oss.str(), expected);
}

TEST(FullTaskTest, ChainedOutput) {
    {
        Coord2D coord{42, -15};
        std::ostringstream oss;
        oss << coord << coord;
        EXPECT_EQ(oss.str(), "(42, -15)(42, -15)");
    }
    {
        Circle circle_one({0, 0}, 17);
        Circle circle_two({10, 10}, 0);
        std::ostringstream oss;
        oss << circle_one << circle_two;
        EXPECT_EQ(oss.str(), "circle[(0, 0), r = 17]circle[]");
    }
    {
        Circle circle({-5, -6}, 7);
        CircleRegion region(circle, false);
        std::ostringstream oss;
        oss << region << region;
        EXPECT_EQ(oss.str(), "-circle[(-5, -6), r = 7]-circle[(-5, -6), r = 7]");
    }
    {
        CircleRegionList list;
        list.emplace_back(Circle(Coord2D(1, 2), 3), true);

        std::ostringstream oss;
        oss << "List:\n" << list << '\n' << list << "\nEnd";

        std::string expected = "List:\n{\n\t+circle[(1, 2), r = 3]\n}\n{\n\t+circle[(1, 2), r = 3]\n}\nEnd";
        EXPECT_EQ(oss.str(), expected);
    }
}

TEST(FullTaskTest, ConstCorrectness) {
    {
        const Coord2D coord{42, -15};
        std::ostringstream oss;
        oss << coord << coord;
        EXPECT_EQ(oss.str(), "(42, -15)(42, -15)");
    }
    {
        const Circle circle_one({0, 0}, 17);
        const Circle circle_two({10, 10}, 0);
        std::ostringstream oss;
        oss << circle_one << circle_two;
        EXPECT_EQ(oss.str(), "circle[(0, 0), r = 17]circle[]");
    }
    {
        Circle circle({-5, -6}, 7);
        const CircleRegion region(circle, false);
        std::ostringstream oss;
        oss << region << region;
        EXPECT_EQ(oss.str(), "-circle[(-5, -6), r = 7]-circle[(-5, -6), r = 7]");
    }
    {
        const CircleRegionList list = { std::make_pair<Circle, bool>(Circle(Coord2D(1, 2), 3), true) };

        std::ostringstream oss;
        oss << "List:\n" << list << '\n' << list << "\nEnd";

        std::string expected = "List:\n{\n\t+circle[(1, 2), r = 3]\n}\n{\n\t+circle[(1, 2), r = 3]\n}\nEnd";
        EXPECT_EQ(oss.str(), expected);
    }
}

class StandardOutputCaptureTest : public ::testing::Test {
protected:
    void SetUp() override {
        origin_cout = std::cout.rdbuf(buffer.rdbuf());
    }

    void TearDown() override {
        std::cout.rdbuf(origin_cout);
    }

    std::string GetOutput() {
        return buffer.str();
    }

    void ClearOutput() {
        buffer.str("");
    }

    std::stringstream buffer;
    std::streambuf* origin_cout;
};

TEST_F(StandardOutputCaptureTest, WorkWithCout) {
    {
        Coord2D coord{42, -15};
        EXPECT_NO_THROW(std::cout << coord);
        EXPECT_EQ(GetOutput(), "(42, -15)");
    }
    ClearOutput();
    {
        Circle circle_one({0, 0}, 17);
        Circle circle_two({10, 10}, 0);
        EXPECT_NO_THROW(std::cout << circle_one << circle_two);
        EXPECT_EQ(GetOutput(), "circle[(0, 0), r = 17]circle[]");
    }
    ClearOutput();
    {
        Circle circle({-5, -6}, 7);
        CircleRegion region(circle, false);
        EXPECT_NO_THROW(std::cout << region);
        EXPECT_EQ(GetOutput(), "-circle[(-5, -6), r = 7]");
    }
    ClearOutput();
    {
        CircleRegionList list;
        list.emplace_back(Circle(Coord2D(1, 2), 3), true);
        EXPECT_NO_THROW(std::cout << "List:\n" << list << '\n' << list << "\nEnd");
        std::string expected = "List:\n{\n\t+circle[(1, 2), r = 3]\n}\n{\n\t+circle[(1, 2), r = 3]\n}\nEnd";
        EXPECT_EQ(GetOutput(), expected);
    }
}