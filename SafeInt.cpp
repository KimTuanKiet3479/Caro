#include "SafeInt.h"

SafeInt ::operator int() const 
{ 
	return value; 
}

istream&  operator>>(istream& is, SafeInt& obj)
{
    while (true) {
        if (is >> obj.value)
        { // Nếu nhập thành công
            break;
        }
        else {
            cout << "Invalid input! Please enter a valid integer: ";
            is.clear(); // Xóa trạng thái lỗi
            is.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm
        }
    }
    return is;
}


SafeInt& SafeInt :: operator=(int val)
{
    value = val;
    return *this;
}