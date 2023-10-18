## Submission for competition "Code Wars" by Sofixit company

## Performance
**10** elements -- **15 ns** <br>
**100** elements -- **50 ns** <br>
**1000** elements -- **460 ns** <br>
**1000000** elements -- **0.46 ms** <br>

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

Please, make sure that you have installed CMake 3.23

Tests can be compiled and run in the following manner:

```shell
# cloning my repo from github
git clone https://github.com/it1shka/sofixit
cd sofixit
# initializing CMake
cmake .
# building and running tests
cmake --build tests
cd tests
./sofixit_tests
```
