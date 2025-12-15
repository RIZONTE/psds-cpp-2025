#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <type_traits>

#include "enum_operators.cpp"


TEST(EnumOperatorsTest, UnderlyingType) {
    static_assert(std::is_same_v<std::underlying_type_t<CheckFlags>, uint8_t>,
                  "CheckFlags must use uint8_t as underlying type");
    EXPECT_EQ(sizeof(CheckFlags), sizeof(uint8_t));
    EXPECT_EQ(alignof(CheckFlags), alignof(uint8_t));
}

TEST(EnumOperatorsTest, BitwiseOr) {
    EXPECT_EQ(CheckFlags::TIME | CheckFlags::DATE, static_cast<CheckFlags>(
        static_cast<uint8_t>(CheckFlags::TIME) + static_cast<uint8_t>(CheckFlags::DATE)));
    EXPECT_EQ(CheckFlags::TIME | CheckFlags::DEST | CheckFlags::USER, static_cast<CheckFlags>(
        static_cast<uint8_t>(CheckFlags::TIME) + static_cast<uint8_t>(CheckFlags::DEST) +
        static_cast<uint8_t>(CheckFlags::USER)));
    EXPECT_EQ(CheckFlags::TIME | CheckFlags::TIME, CheckFlags::TIME);
    EXPECT_EQ(CheckFlags::NONE | CheckFlags::TIME, CheckFlags::TIME);
    EXPECT_EQ(CheckFlags::ALL | CheckFlags::TIME, CheckFlags::ALL);
}

TEST(EnumOperatorsTest, BitwiseOrOutside) {
    EXPECT_EQ(static_cast<CheckFlags>(0xFF) | CheckFlags::NONE, CheckFlags::ALL);
    uint8_t invalid = 0x40;
    invalid += static_cast<uint8_t>(CheckFlags::CERT);
    EXPECT_EQ(static_cast<CheckFlags>(invalid) | CheckFlags::KEYS,
        static_cast<CheckFlags>(static_cast<uint8_t>(CheckFlags::CERT) + static_cast<uint8_t>(CheckFlags::KEYS)));
}

TEST(EnumOperatorsTest, BitwiseAnd) {
    CheckFlags flags = CheckFlags::TIME | CheckFlags::DATE;

    EXPECT_TRUE(flags & CheckFlags::TIME);
    EXPECT_TRUE(flags & CheckFlags::DATE);
    EXPECT_FALSE(flags & CheckFlags::USER);

    EXPECT_TRUE(CheckFlags::ALL & CheckFlags::TIME);
    EXPECT_TRUE(CheckFlags::TIME & CheckFlags::ALL);
    EXPECT_TRUE(CheckFlags::DATE & CheckFlags::ALL);
    EXPECT_TRUE(CheckFlags::ALL & CheckFlags::ALL);

    EXPECT_FALSE(CheckFlags::DATE & CheckFlags::NONE);
    EXPECT_FALSE(CheckFlags::NONE & CheckFlags::DATE);
    EXPECT_FALSE(CheckFlags::NONE & CheckFlags::ALL);
    EXPECT_FALSE(CheckFlags::ALL & CheckFlags::NONE);
    EXPECT_FALSE(CheckFlags::NONE & CheckFlags::NONE);
}

TEST(EnumOperatorsTest, BitwiseAndComplex) {
    CheckFlags flags = CheckFlags::TIME | CheckFlags::DATE | CheckFlags::USER;

    EXPECT_TRUE(flags & (CheckFlags::TIME | CheckFlags::DATE));
    EXPECT_TRUE(flags & (CheckFlags::USER | CheckFlags::DATE));
    EXPECT_TRUE((CheckFlags::TIME | CheckFlags::DATE) & flags);
    EXPECT_TRUE((CheckFlags::USER | CheckFlags::DATE) & flags);

    EXPECT_FALSE(flags & CheckFlags::CERT);
    EXPECT_FALSE(flags & (CheckFlags::TIME | CheckFlags::CERT));
    EXPECT_FALSE(flags & (CheckFlags::DATE | CheckFlags::CERT));
    EXPECT_FALSE(flags & (CheckFlags::DATE | CheckFlags::TIME | CheckFlags::CERT));

    EXPECT_FALSE(flags & CheckFlags::NONE);
    EXPECT_FALSE(CheckFlags::NONE & flags);

    EXPECT_TRUE(flags & flags);
    EXPECT_TRUE(flags & (CheckFlags::TIME | CheckFlags::DATE | CheckFlags::USER | CheckFlags::CERT));
    EXPECT_TRUE((CheckFlags::TIME | CheckFlags::DATE | CheckFlags::USER | CheckFlags::CERT) & flags);
}

TEST(EnumOperatorsTest, BitwiseAndOutside) {
    EXPECT_FALSE(static_cast<CheckFlags>(0xC0) & static_cast<CheckFlags>(0xC0));
    EXPECT_FALSE(static_cast<CheckFlags>(0xC1) & static_cast<CheckFlags>(0xC2));
    EXPECT_FALSE(static_cast<CheckFlags>(0xC0) & CheckFlags::ALL);
    EXPECT_TRUE(static_cast<CheckFlags>(0xC1) & static_cast<CheckFlags>(0x03));
}

TEST(EnumOperatorsTest, BitwiseXor) {
    CheckFlags flags1 = CheckFlags::TIME | CheckFlags::DATE;
    CheckFlags flags2 = CheckFlags::TIME | CheckFlags::USER;

    EXPECT_EQ(flags1 ^ flags2, CheckFlags::DATE | CheckFlags::USER);
    EXPECT_EQ(flags2 ^ flags1, CheckFlags::DATE | CheckFlags::USER);
    EXPECT_EQ(flags1 ^ flags1, CheckFlags::NONE);
    EXPECT_EQ(flags1 ^ CheckFlags::NONE, flags1);
    EXPECT_EQ(CheckFlags::NONE ^ flags2, flags2);
    EXPECT_EQ(flags1 ^ CheckFlags::ALL, CheckFlags::USER | CheckFlags::CERT | CheckFlags::KEYS | CheckFlags::DEST);
    EXPECT_EQ(CheckFlags::ALL ^ flags2, CheckFlags::DATE | CheckFlags::CERT | CheckFlags::KEYS | CheckFlags::DEST);
}

TEST(EnumOperatorsTest, BitwiseXorOutside) {
    EXPECT_EQ(static_cast<CheckFlags>(0xC0) ^ static_cast<CheckFlags>(0x80), CheckFlags::NONE);
    EXPECT_EQ(static_cast<CheckFlags>(0xC1) ^ static_cast<CheckFlags>(0xC2), CheckFlags::TIME | CheckFlags::DATE);
    EXPECT_EQ(static_cast<CheckFlags>(0xC0) ^ CheckFlags::ALL,CheckFlags::ALL);
    EXPECT_EQ(static_cast<CheckFlags>(0xFF) ^ CheckFlags::ALL, CheckFlags::NONE);
}

TEST(EnumOperatorsTest, BitwiseNot) {
    EXPECT_EQ(~(CheckFlags::NONE), CheckFlags::ALL);
    EXPECT_EQ(~(CheckFlags::ALL), CheckFlags::NONE);

    CheckFlags not_time = ~CheckFlags::TIME;
    EXPECT_NE(not_time, CheckFlags::NONE);
    EXPECT_NE(not_time, CheckFlags::TIME);
    EXPECT_FALSE(not_time & CheckFlags::TIME);

    CheckFlags flags = CheckFlags::TIME | CheckFlags::DATE;
    EXPECT_EQ(~(~flags), flags);
}

TEST(EnumOperatorsTest, OutputOperator) {
    std::stringstream ss;

    ss << CheckFlags::NONE;
    EXPECT_EQ(ss.str(), "NONE");
    ss.str("");

    ss << CheckFlags::ALL;
    EXPECT_EQ(ss.str(), "TIME, DATE, USER, CERT, KEYS, DEST");
    ss.str("");

    ss << CheckFlags::DEST;
    EXPECT_EQ(ss.str(), "DEST");
    ss.str("");

    ss << (CheckFlags::TIME | CheckFlags::DATE | CheckFlags::USER);
    std::string result = ss.str();
    EXPECT_EQ(result, "TIME, DATE, USER");
}

TEST(EnumOperatorsTest, OutputOperatorOutside) {
    std::stringstream ss;

    ss << static_cast<CheckFlags>(0xC1);
    EXPECT_EQ(ss.str(), "TIME");
    ss.str("");

    ss << static_cast<CheckFlags>(0xFF);
    EXPECT_EQ(ss.str(), "TIME, DATE, USER, CERT, KEYS, DEST");
    ss.str("");

    ss << static_cast<CheckFlags>(0x80);
    EXPECT_EQ(ss.str(), "NONE");
    ss.str("");
}

TEST(EnumOperatorsTest, OutputOperatorChainUse) {
    std::stringstream ss;
    ss << CheckFlags::CERT << " " <<  CheckFlags::KEYS << " " <<  CheckFlags::DEST;
    std::string result = ss.str();
    EXPECT_EQ(result, "CERT KEYS DEST");
}


TEST(EnumOperatorsTest, Sanitization) {
    uint8_t raw_value = 0xFF;
    CheckFlags flags_with_invalid = static_cast<CheckFlags>(raw_value);

    CheckFlags or_result = flags_with_invalid | CheckFlags::NONE;
    EXPECT_EQ(or_result, CheckFlags::ALL);

    EXPECT_TRUE(flags_with_invalid & CheckFlags::ALL);

    CheckFlags xor_result = flags_with_invalid ^ CheckFlags::ALL;
    EXPECT_EQ(xor_result, CheckFlags::NONE);
    std::cerr << flags_with_invalid << std::endl;

    CheckFlags not_result = ~flags_with_invalid;
    std::cerr << not_result << std::endl;
    EXPECT_EQ(not_result, CheckFlags::NONE);
}

TEST(EnumOperatorsTest, CombinedOperations) {
    CheckFlags base = CheckFlags::TIME | CheckFlags::DATE | CheckFlags::USER;

    CheckFlags added = base | CheckFlags::CERT;
    EXPECT_TRUE(added & CheckFlags::CERT);

    CheckFlags removed = added ^ CheckFlags::DATE;
    EXPECT_FALSE(removed & CheckFlags::DATE);
    EXPECT_TRUE(removed & CheckFlags::TIME);
    EXPECT_TRUE(removed & CheckFlags::USER);
    EXPECT_TRUE(removed & CheckFlags::CERT);

    CheckFlags inverse = ~removed;
    EXPECT_FALSE(inverse & CheckFlags::TIME);
    EXPECT_FALSE(inverse & CheckFlags::USER);
    EXPECT_FALSE(inverse & CheckFlags::CERT);
    EXPECT_TRUE(inverse & CheckFlags::DATE);
    EXPECT_TRUE(inverse & CheckFlags::KEYS);
    EXPECT_TRUE(inverse & CheckFlags::DEST);
}

TEST(EnumOperatorsTest, OperationWithConst) {
    const CheckFlags base = CheckFlags::TIME | CheckFlags::DATE | CheckFlags::USER;

    const CheckFlags added_lhs = base | CheckFlags::CERT;
    const CheckFlags added_rhs = CheckFlags::CERT | base;
    EXPECT_TRUE(added_lhs & CheckFlags::CERT);
    EXPECT_TRUE(CheckFlags::CERT & added_rhs);

    const CheckFlags removed_lhs = added_lhs ^ CheckFlags::DATE;
    const CheckFlags removed_rhs = CheckFlags::DATE ^ added_lhs;
    EXPECT_FALSE(removed_lhs & CheckFlags::DATE);
    EXPECT_TRUE(removed_lhs & CheckFlags::TIME);
    EXPECT_TRUE(CheckFlags::USER & removed_lhs);
    EXPECT_TRUE(CheckFlags::CERT & removed_lhs);

    EXPECT_FALSE(removed_rhs & CheckFlags::DATE);
    EXPECT_TRUE(removed_rhs & CheckFlags::TIME);
    EXPECT_TRUE(CheckFlags::USER & removed_rhs);
    EXPECT_TRUE(CheckFlags::CERT & removed_rhs);

    const CheckFlags inverse = ~removed_lhs;
    EXPECT_FALSE(inverse & CheckFlags::TIME);
    EXPECT_FALSE(inverse & CheckFlags::USER);
    EXPECT_FALSE(inverse & CheckFlags::CERT);
    EXPECT_TRUE(inverse & CheckFlags::DATE);
    EXPECT_TRUE(inverse & CheckFlags::KEYS);
    EXPECT_TRUE(inverse & CheckFlags::DEST);
}