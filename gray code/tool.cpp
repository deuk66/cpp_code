// b.cpp (原始碼檔：Source File - 定義/實作)

#include "tool.h"      // 包含自己的標頭檔以獲取宣告和模板結構
#include <iostream> 
#include <string>   // 由於你需要 cout 告知訊息，我們需要 string 函式庫

// 函數定義 (Function Definition)：
// 這裡實作了模板函數的具體邏輯。
template <typename T, size_t N>
size_t size(T (&arr)[N]) {
    // 告知使用者正在進入 b.cpp 函數
    std::cout << "--- 進入 b.cpp 函數：get_array_size ---" << std::endl;
    std::cout << "陣列包含的元素型別大小是: " << sizeof(T) << " bytes" << std::endl;
    
    // 實際計算並回傳陣列的大小 N
    size_t calculated_size = N;
    
    std::cout << "計算出的陣列元素數量是: " << calculated_size << std::endl;
    // 告知使用者正在離開 b.cpp 函數
    std::cout << "--- 離開 b.cpp 函數 ---" << std::endl;

    // 將計算結果回傳
    return calculated_size; 
}

// !!! 重要提醒 !!!
// 在 C++ 標準中，模板定義應該放在 .h 檔中。
// 這裡將其放在 .cpp 只是為了示範「定義」和「宣告」的分離，
// 實際專案中，你可能需要在 a.cpp 中包含 b.cpp 才能連結，
// 或是將定義移到 b.h 中。