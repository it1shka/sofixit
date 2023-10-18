## Submission for competition "Code Wars" by Sofixit company
Written in C++23 (C++17 also should work fine)

In *__solution/function.h__* you will find definition of my <br>
best function so far:
```cpp
template<size_t ArraySize>
auto materialFast(const std::array<int, ArraySize>& spaceship) -> int;
```

as well as some other attemps which are not that good

In *__tests/function_tests.cpp__* you will find a file <br>
that provides test cases for my solution

The way you can launch tests is <br>
__building the *sofixit_tests* target with CMake__