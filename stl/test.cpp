#include <gtest/gtest.h>
#include "MyVector.h"  // �������д��������ͷ�ļ�



// ����MyVector�Ĺ��캯��
TEST(MyVectorTest, Constructor) {
    MyVector<int> vec;
    EXPECT_EQ(vec.getSize(), 0);
}

// ����MyVector��push_back����
TEST(MyVectorTest, PushBack) {
    MyVector<int> vec;
    vec.push_back(1);
    EXPECT_EQ(vec.getSize(), 1);
    EXPECT_EQ(vec[0], 1);
}

// ����MyVector��pop_back����
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