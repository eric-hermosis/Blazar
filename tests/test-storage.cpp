#include <gtest/gtest.h>
#include <blazar/memory.hpp>
#include <blazar/storage.hpp>

using namespace blazar; 

TEST(TestStorage, TestRefCount) {
    Storage storage_1(10, Host()); 
    EXPECT_EQ(storage_1.get()->references(), 1); 
  
    Storage storage_2 = storage_1;
    EXPECT_EQ(storage_1.get()->references(), 2);
    EXPECT_EQ(storage_2.get()->references(), 2);

    Storage storage_3 = storage_2;
    EXPECT_EQ(storage_1.get()->references(), 3);

    {
        Storage storage_4 = storage_1;
        EXPECT_EQ(storage_3.get()->references(), 4); 
    }
    Storage storage_5 = std::move(storage_2);
    EXPECT_EQ(storage_5.get()->references(), 3);  
    EXPECT_EQ(storage_2.get(), nullptr);
}