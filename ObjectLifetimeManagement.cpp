/**
 * @file ObjectLifetimeManagement.cpp
 * @author Mjiso
 * @brief 这个代码文件是一个关于C++对象生命周期管理和资源管理的实用指南，适合初学者学习和参考。
 *        通过这个例子，开发者可以更好地理解C++中的构造函数、析构函数、拷贝控制和类型转换等概念。
 * @version 0.1
 * @date 2024-03-29
 * @copyright Copyright (c) 2024
 */
#include <iostream>
#include <cstring>

class A {
   private:
    int* data = nullptr;
    int size = 0;

   public:
    A();                           // 1. 无参构造函数
    A(int size);                   // 2. 有参构造函数
    ~A();                          // 3. 析构函数

    explicit A(double d);          // 4. 显示转换构造函数（其他类型 转 类的对象）
    // A(double d);                //    隐式转换构造函数（其他类型 转 类的对象）
    operator int() const;          // 5. 类型转换运算符（类的对象 转 其他类型）

    A(const A& other);             // 6. 拷贝构造函数（已存在对象 构造 新对象，深拷贝）
    A(A&& other);                  // 7. 移动构造函数（已存在的对象 转移资源构造 新对象）（可以说是 "剪切构造函数"）

    A& operator=(const A& other);  // 8. 拷贝赋值运算符（对象 <= 对象）
    A& operator=(A&& other);       // 9. 移动拷贝赋值运算符（对象1 <= 对象2，对象1直接把对象2的资源 "剪切" 了过来。）
};
/**
  * @brief   无参构造函数。
  * @note    None
  * @param   None
  * @return  None
  */
A::A() : data(nullptr), size(0) {
    std::cout << "Default constructor" << std::endl;
}
/**
  * @brief   有参构造函数
  * @note    None
  * @param   size：构造对象的参数。
  * @return  None
  */
A::A(int size) : size(size) {
    std::cout << "Parameterized constructor" << std::endl;
    if (size > 0) {
        data = new int[size];
        for (int i = 0; i < size; ++i) {
            data[i] = 0;
        }  // 初始化数组为零
    } else {
        data = nullptr;
    }
}
/**
  * @brief   析构函数
  *          因为类的成员有指针类型，即动态分配的内存，所以这里要手动释放。
  * @note    None
  * @param   None
  * @return  None
  */
A::~A() {
    std::cout << "Destructor" << std::endl;
    delete[] data;
}


/**
  * @brief   转换构造函数（将普通数据类型作为构造参数，构造类的对象）
  *         （注意，关键字explicit只需要在类内部声明时有，外部定义时不需要写出来！）
  *
  *          这里因为声明时用了 explicit 关键字修饰，所以禁止隐式类型转换。
  *          如：A a = 1.2 就是隐式转换；A a = A(1.2)则是显式转换。
  * @note    None
  * @param   d：double类型的构造参数，用来构造A类的对象。
  * @return  None
  */
A::A(double d) : size(static_cast<int>(d)) {
    std::cout << "conversion constructor (double to A)" << std::endl;
    if (size > 0) {
        data = new int[size];
        for (int i = 0; i < size; ++i) {  // 初始化数组为零
            data[i] = 0;
        }
    } else {
        data = nullptr;
    }
}
/**
  * @brief   转换构造函数（将普通数据类型作为构造参数，构造类的对象）
  *          这里因为没有用 explicit 关键字修饰，所以可以隐式转换。
  *          如：A a = 1.2 就是隐式转换；A a = A(1.2)则是显式转换。
  *
  *          需要注意的是：若显式转换构造函数，隐式转换构造函数，这二者同时存在。
  *          由于显式转换构造函数的存在，编译器将会报错，指示该调用是模糊的。（所以，需要支持隐式转换构造，就不能有显式的！）
  * @note    None
  * @param   d：double类型的构造参数，用来构造A类的对象。
  * @return  None
  */
// A::A(double d) : size(static_cast<int>(d)) {
//     std::cout << "Conversion constructor" << std::endl;
//     if (size > 0) {
//         data = new int[size];
//         for (int i = 0; i < size; ++i) {
//             data[i] = 0;
//         }
//     } else {
//         data = nullptr;
//     }
// }
/**
  * @brief   类型转换运算符函数（将类的对象转换为其他类型的数据）（这里是：将 A 类型转换为 int 类型）
  * @note    None
  * @param   None
  * @return  None
  */
A::operator int() const {
    std::cout << "Conversion operator (A to int)" << std::endl;
    return size;
}


/**
  * @brief   拷贝构造函数（将另一个同类型的对象的值复制给当前对象）
  *          拷贝构造函数一般用于实现 "深拷贝"！
  * @note    None
  * @param   other：一个类的对象，用这个对象的数据构造一个新的对象。
  * @return  None
  */
A::A(const A& other) : size(other.size) {
    std::cout << "Copy constructor" << std::endl;
    if (size > 0) {
        data = new int[size];
        std::memcpy(data, other.data, size * sizeof(int));  // 拷贝数组内容
    } else {
        data = nullptr;
    }
}
/**
  * @brief   移动构造函数（将另一个同类型的对象，用 "剪切" 的方式构造当前对象，即：转移了旧对象的所有资源给新对象）
  *          移动构造函数一般用于实现 "浅拷贝"！
  * @note    None
  * @param   other：一个类的对象，将这个对象的资源数据 "剪切" 给一个新的对象。
  * @return  None
  */
A::A(A&& other) {
    std::cout << "Move constructor" << std::endl;
    // 先保存自己的资源
    int tmp_size = this->size;
    int *tmp_data = this->data;

    // 将other的资源剪切到自己
    this->size = other.size;
    this->data = other.data;
    
    // 将自己保存的资源赋值给other。
    other.size = tmp_size;
    other.data = tmp_data;

    // 这里其实为了实现 "剪切" 的操作，应该是将other的资源拿过来后，直接置空！
    // 即如下操作，那么上面也就可以直接拿other的资源，不用保存自己的资源了！
    // other.size = 0;
    // other.data = nullptr;
}


/**
  * @brief   拷贝赋值运算符（用于将一个对象的值赋给另一个对象）
  *          拷贝赋值运算符可以用于实现深拷贝或浅拷贝，具体取决于实现方式。（这里实现的是深拷贝！）
  *
  *          注意：copy assignment 用于将一个已经存在的对象的值赋给另一个已经存在的对象。
  *          而对象构造函数则是：用一个已经存在的对象，作为构造参数，创建一个新的对象。
  * @note    None
  * @param   other：同类型的拷贝对象。拷贝的数据来源。
  * @return  None
  */
A& A::operator=(const A& other) {
    std::cout << "Copy assignment operator" << std::endl;
    if (this != &other) {
        delete[] data;      // 释放自身原有的资源
        size = other.size;
        if (size > 0) {     // 分配新的内存并拷贝数据
            data = new int[size];
            std::memcpy(data, other.data, size * sizeof(int));
        } else {
            data = nullptr;
        }
    }
    return *this;
}
/**
  * @brief   移动拷贝赋值运算符（用于将一个对象的所有资源 "剪切" 给另一个对象）
  *          移动拷贝赋值运算符一般用于浅拷贝！
  *
  * @note    None
  * @param   other：同类型的右值对象。"剪切" 的数据来源。
  * @return  None
  */
A& A::operator=(A&& other) {
    std::cout << "Move copy assignment operator" << std::endl;
    if (this == &other) {   // 自我赋值检查
        return *this;
    }
    // 先保存自己的资源
    int tmp_size = this->size;
    int *tmp_data = this->data;

    // 将other的资源剪切到自己
    this->size = other.size;
    this->data = other.data;

    // 将自己保存的资源赋值给other。
    other.size = tmp_size;
    other.data = tmp_data;

    return *this;
}


int main() {
    // TEST 1：无参构造函数 + 有参构造函数 + 转换构造函数
    std::cout << "TEST 1 START" << std::endl;
    A a;                    // Default constructor
    A a1(123);              // Parameterized constructor
    A a2(1.23);             // conversion constructor (double to A)
    std::cout << "TEST 1 END" << std::endl << std::endl;

    // TSET 2：转换构造函数 + 类型转换运算符
    std::cout << "TEST 2 START" << std::endl;

    A a3(1.23);             // conversion constructor (double to A)
    int tmp = a3;           // Conversion operator (A to int)
    std::cout << "TEST 2 END" << std::endl << std::endl;

    // TEST 3：对象构造函数 + 移动构造函数
    std::cout << "TEST 3 START" << std::endl;

    A a4(123);
    A a5(a4);               // Copy constructor（显式）
    A a6 = a4;              // Copy constructor（隐式）

    A a7(std::move(a5));    // Move constructo（显式）
    A a8 = std::move(a6);   // Move constructo（隐式）
    std::cout << "TEST 3 END" << std::endl << std::endl;

    // TSET 4：拷贝赋值运算符 + 移动拷贝赋值运算符
    std::cout << "TEST 4 START" << std::endl;
    A a9(123);
    A a10;
    a10 = a9;               // Copy assignment operator

    A a11;
    a11 = std::move(a9);    // Move copy assignment operator
    std::cout << "TEST 4 END" << std::endl << std::endl;

    return 0;
}