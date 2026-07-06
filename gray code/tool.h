// b.h (標頭檔：Header File - 宣告)
#ifndef B_H
#define B_H

#include <iostream> 
#include <stddef.h> // 引入 size_t 的定義

// 函數宣告 (Function Declaration)：
// 這是 C++ 模板函數的宣告。
// 類型 T 代表陣列中的元素類型 (如 int, double, char)。
// 類型 N 代表陣列的元素數量 (它是一個常數)。
template <typename T, size_t N>
size_t size(T (&arr)[N]); // 接受一個對 N 個 T 型別元素的陣列的參考

#endif // B_H