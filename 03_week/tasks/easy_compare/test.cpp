#include <gtest/gtest.h>

#include <vector>
#include <algorithm>

#include "easy_compare.cpp"


TEST(DateTest, DefaultCtor) {
    Date date;
    EXPECT_EQ(date.year, 0u);
    EXPECT_EQ(date.month, 0u);
    EXPECT_EQ(date.day, 0u);
}

TEST(DateTest, ParameterizedCtor) {
    Date date{2025, 12, 31};
    EXPECT_EQ(date.year, 2025u);
    EXPECT_EQ(date.month, 12u);
    EXPECT_EQ(date.day, 31u);
}

TEST(DateTest, EqualityOperator) {
    EXPECT_TRUE(Date({2007, 1, 1}) == Date({2007, 1, 1}));
    EXPECT_FALSE(Date({2007, 1, 1}) == Date({2007, 1, 2}));
    EXPECT_FALSE(Date({2007, 1, 1}) == Date({2007, 2, 1}));
    EXPECT_FALSE(Date({2007, 1, 1}) == Date({2006, 1, 1}));
}

TEST(DateTest, LessThanOperator) {
    Date d1(2007, 1, 1);
    Date d2(2007, 1, 2);
    Date d3(2007, 2, 1);
    Date d4(2008, 1, 1);

    EXPECT_TRUE(d1 < d2);
    EXPECT_TRUE(d1 < d3);
    EXPECT_TRUE(d1 < d4);
    EXPECT_TRUE(d2 < d3);
    EXPECT_TRUE(d2 < d4);
    EXPECT_TRUE(d3 < d4);

    EXPECT_FALSE(d1 < d1);
    EXPECT_FALSE(d2 < d1);
    EXPECT_FALSE(d3 < d1);
    EXPECT_FALSE(d4 < d1);
    EXPECT_FALSE(d3 < d2);
    EXPECT_FALSE(d4 < d3);
}

TEST(DateTest, FullComparisonOperators) {
    Date d1(2000, 1, 1);
    Date d2(2000, 1, 2);

    EXPECT_TRUE(d1 != d2);
    EXPECT_FALSE(d1 != d1);

    EXPECT_FALSE(d2 <= d1);
    EXPECT_TRUE(d1 <= d2);
    EXPECT_FALSE(d1 >= d2);
    EXPECT_TRUE(d2 >= d1);
    EXPECT_FALSE(d1 > d2);
    EXPECT_TRUE(d2 > d1);

    EXPECT_TRUE(d1 >= d1);
    EXPECT_TRUE(d1 <= d1);
}

TEST(StudentInfoTest, EqualityOperator) {
    StudentInfo s1{1, 'A', 100, 1, Date{2000, 1, 1}};
    StudentInfo s2{2, 'A', 100, 2, Date{1999, 12, 31}};
    StudentInfo s3{3, 'B', 100, 1, Date{2000, 1, 1}};
    StudentInfo s4{4, 'A', 90,  1, Date{2000, 1, 1}};

    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 == s3);
    EXPECT_FALSE(s1 == s4);
}

TEST(StudentInfoTest, NotEqualOperator) {
    StudentInfo s1{1, 'A', 100, 1, Date{2000, 1, 1}};
    StudentInfo s2{4, 'B', 100, 1, Date{2000, 1, 1}};
    StudentInfo s4{2, 'A', 90,  1, Date{2000, 1, 1}};

    EXPECT_TRUE(s1 != s2);
    EXPECT_FALSE(s1 != s1);
    EXPECT_TRUE(s1 != s4);
}

TEST(StudentInfoTest, CompareByMark) {
    StudentInfo z_student{1, 'Z', 10, 1, Date{2000, 1, 1}};
    StudentInfo d_student{2, 'D', 20, 2, Date{2001, 1, 1}};
    StudentInfo c_student{3, 'C', 30, 3, Date{2002, 1, 1}};
    StudentInfo b_student{2, 'B', 40, 4, Date{2003, 1, 1}};
    StudentInfo a_student{5, 'A', 50, 5, Date{2004, 1, 1}};

    EXPECT_TRUE(z_student < d_student);
    EXPECT_TRUE(z_student < c_student);
    EXPECT_TRUE(z_student < b_student);
    EXPECT_TRUE(z_student < a_student);

    EXPECT_TRUE(d_student < c_student);
    EXPECT_TRUE(d_student < b_student);
    EXPECT_TRUE(d_student < a_student);

    EXPECT_TRUE(c_student < b_student);
    EXPECT_TRUE(c_student < a_student);

    EXPECT_TRUE(b_student < a_student);

    EXPECT_FALSE(a_student < z_student);
    EXPECT_FALSE(a_student < d_student);
    EXPECT_FALSE(a_student < c_student);
    EXPECT_FALSE(a_student < b_student);
}

TEST(StudentInfoTest, CompareByScore) {
    StudentInfo high_score{3, 'A', 100, 1, Date{2000, 1, 1}};
    StudentInfo medium_score{2, 'A', 80, 2, Date{2001, 1, 1}};
    StudentInfo low_score{7, 'A', 60, 3, Date{2002, 1, 1}};

    EXPECT_TRUE(low_score < medium_score);
    EXPECT_TRUE(medium_score < high_score);
    EXPECT_TRUE(low_score < high_score);

    EXPECT_FALSE(high_score < medium_score);
    EXPECT_FALSE(high_score < low_score);
    EXPECT_FALSE(medium_score < low_score);
}

TEST(StudentInfoTest, CompareByCourse) {
    StudentInfo first_year{1, 'A', 100, 1, Date{2000, 1, 1}};
    StudentInfo second_year{3, 'A', 100, 2, Date{2000, 1, 1}};
    StudentInfo third_year{2, 'A', 100, 3, Date{2000, 1, 1}};
    StudentInfo fourth_year{4, 'A', 100, 4, Date{2000, 1, 1}};

    EXPECT_TRUE(fourth_year < third_year);
    EXPECT_TRUE(fourth_year < second_year);
    EXPECT_TRUE(fourth_year < first_year);

    EXPECT_TRUE(third_year < second_year);
    EXPECT_TRUE(third_year < first_year);

    EXPECT_TRUE(second_year < first_year);

    EXPECT_FALSE(first_year < second_year);
    EXPECT_FALSE(first_year < third_year);
    EXPECT_FALSE(first_year < fourth_year);
    EXPECT_FALSE(third_year < fourth_year);
}

TEST(StudentInfoTest, CompareByBirthDate) {
    StudentInfo young{1, 'A', 100, 1, Date{2001, 1, 1}};
    StudentInfo middle{2, 'A', 100, 1, Date{2000, 6, 15}};
    StudentInfo old{3, 'A', 100, 1, Date{1999, 12, 31}};

    EXPECT_TRUE(old < middle);
    EXPECT_TRUE(middle < young);
    EXPECT_TRUE(old < young);

    EXPECT_FALSE(young < middle);
    EXPECT_FALSE(young < old);
    EXPECT_FALSE(middle < old);
}

TEST(StudentInfoTest, CompareByDateComponents) {
    StudentInfo year1{1, 'A', 100, 1, Date{2000, 1, 1}};
    StudentInfo year2{2, 'A', 100, 1, Date{2001, 1, 1}};

    StudentInfo month1{4, 'A', 100, 1, Date{2000, 1, 1}};
    StudentInfo month2{3, 'A', 100, 1, Date{2000, 2, 1}};

    StudentInfo day1{5, 'A', 100, 1, Date{2000, 1, 1}};
    StudentInfo day2{6, 'A', 100, 1, Date{2000, 1, 2}};

    EXPECT_TRUE(year1 < year2);
    EXPECT_FALSE(year2 < year1);

    EXPECT_TRUE(month1 < month2);
    EXPECT_FALSE(month2 < month1);

    EXPECT_TRUE(day1 < day2);
    EXPECT_FALSE(day2 < day1);
}

TEST(StudentInfoTest, ComplexComparisons) {
    StudentInfo a_student{1, 'A', 50, 4, Date{1990, 1, 1}};
    StudentInfo b_student{2, 'B', 100, 1, Date{2005, 1, 1}};

    EXPECT_TRUE(b_student < a_student);
    EXPECT_FALSE(a_student < b_student);

    StudentInfo high_score{4, 'B', 100, 4, Date{1990, 1, 1}};
    StudentInfo low_score{3, 'B', 50, 1, Date{2005, 1, 1}};

    EXPECT_TRUE(low_score < high_score);
    EXPECT_FALSE(high_score < low_score);

    StudentInfo first_year{5, 'C', 80, 1, Date{1995, 1, 1}};
    StudentInfo fourth_year{6, 'C', 80, 4, Date{2005, 1, 1}};

    EXPECT_TRUE(fourth_year < first_year);
    EXPECT_FALSE(first_year < fourth_year);

    StudentInfo older{8, 'D', 70, 2, Date{1998, 1, 1}};
    StudentInfo younger{7, 'D', 70, 2, Date{2000, 1, 1}};

    EXPECT_TRUE(older < younger);
    EXPECT_FALSE(younger < older);

    StudentInfo older_month{8, 'D', 70, 2, Date{2007, 1, 31}};
    StudentInfo younger_month{7, 'D', 70, 2, Date{2007, 2, 1}};

    EXPECT_TRUE(older_month < younger_month);
    EXPECT_FALSE(younger_month < older_month);

    StudentInfo older_day{8, 'D', 70, 2, Date{2007, 1, 1}};
    StudentInfo younger_day{7, 'D', 70, 2, Date{2007, 1, 2}};

    EXPECT_TRUE(older_day < younger_day);
    EXPECT_FALSE(younger_day < older_day);
}

class StudentSortTest : public ::testing::Test {
protected:
    void SetUp() override {
        students_expected = {
            {7, 'Z', 100, 1, Date{2018, 1, 1}},
            {6, 'D', 120, 2, Date{2017, 1, 1}},
            {5, 'C', 140, 3, Date{2016, 1, 1}},
            {4, 'B', 150, 5, Date{2017, 1, 1}},
            {8, 'A', 1999, 2, Date{2003, 1, 1}},
            {9, 'A', 1999, 1, Date{2003, 1, 1}},
            {3, 'A', 1999, 1, Date{2003, 2, 1}},
            {2, 'A', 1999, 1, Date{2004, 2, 1}},
            {1, 'A', 2000, 5, Date{2000, 1, 1}},
            {10, 'A', 2000, 4, Date{2000, 1, 1}},
            {11, 'A', 2000, 4, Date{2000, 1, 2}}
        };
    }

    std::vector<StudentInfo> students_expected;
};

TEST_F(StudentSortTest, SortStudents) {
    std::vector<StudentInfo> students = {
        {1, 'A', 2000, 5, Date{2000, 1, 1}},
        {2, 'A', 1999, 1, Date{2004, 2, 1}},
        {3, 'A', 1999, 1, Date{2003, 2, 1}},
        {4, 'B', 150, 5, Date{2017, 1, 1}},
        {5, 'C', 140, 3, Date{2016, 1, 1}},
        {6, 'D', 120, 2, Date{2017, 1, 1}},
        {7, 'Z', 100, 1, Date{2018, 1, 1}},
        {8, 'A', 1999, 2, Date{2003, 1, 1}},
        {9, 'A', 1999, 1, Date{2003, 1, 1}},
        {10, 'A', 2000, 4, Date{2000, 1, 1}},
        {11, 'A', 2000, 4, Date{2000, 1, 2}}
    };

    std::sort(students.begin(), students.end());

    for (size_t i = 0; i < students.size(); ++i) {
        EXPECT_EQ(students[i].id, students_expected[i].id);
        EXPECT_EQ(students[i].mark, students_expected[i].mark);
        EXPECT_EQ(students[i].score, students_expected[i].score);
        EXPECT_EQ(students[i].course, students_expected[i].course);
        EXPECT_EQ(students[i].birth_date, students_expected[i].birth_date);
    }
}