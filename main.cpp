#include <iostream>
#include <iomanip>
#include <string>
#include <boost/coroutine2/coroutine.hpp>

using IntGenerator = boost::coroutines2::coroutine<int>;
using StringReceiver = boost::coroutines2::coroutine<std::string>;

import moduleTest;


struct FinalEOL {
    ~FinalEOL() {
        std::cout << std::endl;
    }
};

int main() {

    auto source{IntGenerator::pull_type(
            [](IntGenerator::push_type& sink){
                int first=1,second=1;
                sink(first);
                sink(second);
                for (int i = 0; i < 8; ++i) {
                    int third = first + second;
                    first = second;
                    second = third;
                    sink(third);
                }
            })};

    for (auto number: source) {
        std::cout << number << " ";
    }
    std::cout << "\n";

    auto writer{StringReceiver::push_type(
            [num = 5, width = 15](StringReceiver::pull_type &inputs) {
                // 何が起きたとしても、最終行を終了する
                FinalEOL eol;
                // 上流から値を引き出して、num個を一行に展開する
                for (;;) {
                    for (int i = 0; i < num; ++i) {
                        // 入力を使い果たしたらやめる
                        if (!inputs) return 1;
                        std::cout << std::setw(width) << inputs.get();
                        // この要素をハンドルし終わったので、次へ進む
                        inputs();
                    }
                    // num個の要素の後、改行する
                    std::cout << std::endl;
                }
            })};

    std::vector<std::string> words{
            "peas", "porridge", "hot", "peas",
            "porridge", "cold", "peas", "porridge",
            "in", "the", "pot", "nine",
            "days", "old" };

    std::copy(words.begin(),words.end(),begin(writer));

    return 0;
}
