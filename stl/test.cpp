#include <gtest/gtest.h>
#include "MyVector.h"  // 包含你仿写的容器库头文件



// 测试MyVector的构造函数
TEST(MyVectorTest, Constructor) {
    MyVector<int> vec;
    EXPECT_EQ(vec.getSize(), 0);
}

// 测试MyVector的push_back方法
TEST(MyVectorTest, PushBack) {
    MyVector<int> vec;
    vec.push_back(1);
    EXPECT_EQ(vec.getSize(), 1);
    EXPECT_EQ(vec[0], 1);
}

// 测试MyVector的pop_back方法
TEST(MyVectorTest, PopBack) {
    MyVector<int> vec;
    vec.push_back(1);
    vec.pop_back();
    EXPECT_EQ(vec.getSize(), 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}