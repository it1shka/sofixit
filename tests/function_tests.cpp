#include "function.h"
#include <chrono>
#include <iostream>
#include <random>

template<size_t ArraySize>
using MaterialFunction = std::function<int(const std::array<int, ArraySize>&)>;

template<size_t Measurements, size_t ArraySize>
auto test (
    const std::array<int, ArraySize>& source,
    const MaterialFunction<ArraySize>& func,
    int expectedResult
) -> void {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration;

    // measuring performance (runtime)
    duration<double, std::nano> averageRuntime(0);
    for (size_t i = 0; i < Measurements; i++) {
        const auto start = high_resolution_clock::now();
        func(source);
        const auto end = high_resolution_clock::now();
        duration<double, std::nano> durationDouble = end - start;
        averageRuntime += durationDouble;
    }
    averageRuntime /= Measurements;
    std::cout
        << ArraySize << " elements: "
        << averageRuntime.count() << " ns. ";

    // measuring correctness
    const auto result = func(source);
    const auto correct = result == expectedResult;
    if (correct) {
        std::cout << "OK";
    } else {
        std::cout << "FAIL: expected " << expectedResult << ", got " << result;
    }
    std::cout << std::endl;
}

template<size_t ArraySize>
std::array<int, ArraySize> randomArray() {
    std::uniform_int_distribution<int> distribution(0, 100);
    std::random_device device;
    std::mt19937 generator(device());

    std::array<int, ArraySize> output{};
    for (size_t i = 0; i < ArraySize; i++) {
        output[i] = distribution(generator);
    }
    return output;
}

#define TEST(MEASUREMENTS,FUNC,RESULT,SIZE,ARRAY)                   \
    {                                                               \
            const auto array = ARRAY;                               \
            test<MEASUREMENTS,SIZE>(array, &FUNC<SIZE>, RESULT);    \
    }

auto main() -> int {
    // TESTING CORRECTNESS AND PERFORMANCE
    constexpr size_t INTENSIVE_MEASUREMENT = 1e6;
    TEST(INTENSIVE_MEASUREMENT, materialFast, 83, 26, (std::array { 6, 4, 2, 0, 3, 2, 0, 3, 1, 4, 5, 3, 2, 7, 5, 3, 0, 1, 2, 1, 3, 4, 6, 8, 1, 3 }))
    TEST(INTENSIVE_MEASUREMENT, materialFast, 50, 18, (std::array {6, 2, 1, 1, 8, 0, 5, 5, 0, 1, 8, 9, 6, 9, 4, 8, 0, 0}))

    TEST(INTENSIVE_MEASUREMENT, materialFast, 0, 15, (std::array { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150 }))
    TEST(INTENSIVE_MEASUREMENT, materialFast, 45, 12, (std::array { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 10, 11 }))
    TEST(INTENSIVE_MEASUREMENT, materialFast, 2, 10, (std::array { 6, 7, 8, 9, 4, 5, 2, 3, 1, 0 }))
    TEST(INTENSIVE_MEASUREMENT, materialFast, 45, 14, (std::array { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 10, 11, 12, 13 }))
    TEST(INTENSIVE_MEASUREMENT, materialFast, 36, 13, (std::array { 8, 7, 6, 5, 4, 3, 2, 1, 0, 9, 10, 11, 12 }))
    TEST(INTENSIVE_MEASUREMENT, materialFast, 0, 18, (std::array { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36 }))

    TEST(INTENSIVE_MEASUREMENT, materialFast, 476, 26, (std::array { 135, 130, 145, 150, 115, 110, 115, 110, 95, 106, 105, 5, 103, 110, 65, 66, 70, 50, 45, 40, 35, 100, 25, 20, 15, 16 }))
    TEST(INTENSIVE_MEASUREMENT, materialFast, 112, 18, (std::array { 7, 5, 19, 10, 11, 13, 20, 55, 55, 50, 50, 100, 50, 85, 91, 97, 103, 109 }))
    TEST(INTENSIVE_MEASUREMENT, materialFast, 276, 25, (std::array { 12, 7, 32, 18, 5, 9, 25, 14, 8, 21, 11, 28, 17, 6, 23, 15, 10, 30, 19, 4, 13, 22, 16, 27, 20 }))

    TEST(INTENSIVE_MEASUREMENT, materialFast, 4130, 100, (std::array { 8, 43, 12, 67, 31, 15, 72, 25, 4, 38, 19, 91, 10, 53, 29, 64, 7, 48, 21, 81, 35, 16, 61, 9, 46, 23, 78, 40, 13, 57, 32, 89, 6, 49, 27, 73, 37, 18, 63, 20, 75, 42, 11, 68, 30, 86, 5, 50, 26, 69, 34, 14, 62, 24, 79, 45, 17, 80, 39, 87, 2, 55, 33, 74, 36, 3, 60, 22, 76, 41, 1, 58, 28, 82, 47, 92, 51, 96, 7, 90, 44, 77, 52, 28, 83, 54, 99, 56, 23, 70, 19, 84, 59, 8, 65, 14, 71, 4, 66, 25 }))
    TEST(INTENSIVE_MEASUREMENT, materialFast, 4147, 100, (std::array { 39, 12, 78, 21, 56, 8, 43, 67, 29, 64, 15, 91, 7, 32, 54, 9, 28, 81, 35, 10, 47, 61, 26, 49, 17, 83, 40, 13, 72, 36, 89, 5, 60, 23, 68, 31, 84, 19, 74, 45, 16, 53, 37, 18, 76, 2, 58, 22, 66, 30, 79, 51, 25, 80, 42, 14, 67, 34, 99, 57, 3, 46, 11, 86, 41, 1, 55, 27, 71, 4, 62, 20, 75, 44, 88, 6, 63, 24, 70, 50, 65, 38, 82, 52, 96, 69, 33, 77, 93, 59, 90, 95, 98, 73, 85, 94, 97, 92, 87, 100 }))

    // TESTING ONLY PERFORMANCE
    std::cerr << "WITHOUT CHECK FOR CORRECTNESS: " << std::endl;
    const size_t MEDIUM_MEASUREMENT = 1e3;
    constexpr size_t MEDIUM_MEASUREMENTS_AMOUNT = 10;
    constexpr size_t MEDIUM_MEASUREMENT_ARRAY_SIZE = 1e3;
    for (size_t i = 0; i < MEDIUM_MEASUREMENTS_AMOUNT; i++) {
        TEST(MEDIUM_MEASUREMENT, materialFast, -1, MEDIUM_MEASUREMENT_ARRAY_SIZE, randomArray<MEDIUM_MEASUREMENT_ARRAY_SIZE>())
    }

    const size_t SOFT_MEASUREMENT = 1e2;
    constexpr size_t SOFT_MEASUREMENTS_AMOUNT = 10;
    constexpr size_t SOFT_MEASUREMENT_ARRAY_SIZE = 1e6;
    for (size_t i = 0; i < SOFT_MEASUREMENTS_AMOUNT; i++) {
        TEST(SOFT_MEASUREMENT, materialFast, -1, SOFT_MEASUREMENT_ARRAY_SIZE, randomArray<SOFT_MEASUREMENT_ARRAY_SIZE>())
    }
}