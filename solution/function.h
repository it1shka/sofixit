#pragma once
#include <array>
#include <thread>

// Fast solution with only one for loop
// Time O(n), Space O(1)
template<size_t ArraySize>
auto materialFast(const std::array<int, ArraySize>& spaceship) /* noexcept */ {
    if (ArraySize == 0) return 0;
    size_t leftPointer = 0;
    size_t rightPointer = ArraySize - 1;
    auto leftMax = spaceship[leftPointer];
    auto rightMax = spaceship[rightPointer];

    auto materialSize = 0;
    while (leftPointer < rightPointer) {
        if (leftMax < rightMax) {
            materialSize += leftMax - spaceship[leftPointer];
            leftPointer++;
            leftMax = std::max(leftMax, spaceship[leftPointer]);
        } else {
            materialSize += rightMax - spaceship[rightPointer];
            rightPointer--;
            rightMax = std::max(rightMax, spaceship[rightPointer]);
        }
    }
    return materialSize;
}

// Slow solution enabling multiple threads,
// Time O(n), Space O(n)
template<size_t ArraySize>
auto materialMultiThreadedSlow(const std::array<int, ArraySize>& spaceship) /* noexcept */ {
    std::array<int, ArraySize> left, right;
    std::thread leftInitThread([&left, &spaceship]() {
        left[0] = spaceship[0];
        for (size_t i = 1; i < ArraySize; i++) {
            left[i] = std::max(left[i - 1], spaceship[i]);
        }
    });
    std::thread rightInitThread([&right, &spaceship]() {
        right[ArraySize - 1] = spaceship[ArraySize - 1];
        for (size_t i = 1; i < ArraySize; i++) {
            const auto idx = ArraySize - i - 1;
            right[idx] = std::max(right[idx + 1], spaceship[idx]);
        }
    });
    leftInitThread.join();
    rightInitThread.join();
    auto materialSize = 0;
    for (size_t i = 1; i < ArraySize - 1; i++) {
        const auto limit = std::min(left[i - 1], right[i + 1]);
        if (spaceship[i] >= limit) continue;
        materialSize += limit - spaceship[i];
    }
    return materialSize;
}

// Slow solution using only one thread
// Time O(n), Space O(n)
template<size_t ArraySize>
auto materialSingleThreadedSlow(const std::array<int, ArraySize>& spaceship) /* noexcept */ {
    std::array<int, ArraySize> left, right;
    left[0] = spaceship[0];
    right[ArraySize - 1] = spaceship[ArraySize - 1];
    for (size_t i = 1; i < ArraySize; i++) {
        left[i] = std::max(left[i - 1], spaceship[i]);
        const auto idx = ArraySize - i - 1;
        right[idx] = std::max(right[idx + 1], spaceship[idx]);
    }
    auto materialSize = 0;
    for (size_t i = 1; i < ArraySize - 1; i++) {
        const auto limit = min(left[i - 1], right[i + 1]);
        if (spaceship[i] >= limit) continue;
        materialSize += limit - spaceship[i];
    }
    return materialSize;
}