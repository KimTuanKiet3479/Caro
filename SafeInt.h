#pragma once
#include <iostream>
#include <limits>
using namespace std;

// Lớp SafeInt để đóng gói int và nạp chồng toán tử >> để chỉ được nhập số nguyên
class SafeInt 
{
private:
    int value;

public:
    SafeInt() : value(0) {}  // Constructor mặc định
    SafeInt(int val) : value(val) {}  // Constructor nhận int
    // Hàm chuyển đổi ngầm định sang int
    operator int() const;

    // Nạp chồng toán tử >> để nhập dữ liệu an toàn
    friend  istream& operator>>(istream& is, SafeInt& obj);
    // Nạp chồng toán tử gán
    SafeInt& operator=(int val);
};

