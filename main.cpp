#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <inttypes.h>
#include <thread>
#include <unistd.h>

std::map<int, int> threadRecords = {};

struct ThreadCalcRange {
    uint64_t size = 10000000000;
    uint64_t min = 11;
    uint64_t max = min + size;
    int thread_index = 0;
};

void multiply_digits(uint64_t number, int *iteration_ptr) {

    if (number < 10) {
        return;
    } else {
        uint64_t multiply_product = 1;

        while (number > 0) {
            int digit = number % 10;
            multiply_product = multiply_product * digit;
            number /= 10;
        }

        (*iteration_ptr)++;
        multiply_digits(multiply_product, iteration_ptr);
    }
}

void find(ThreadCalcRange *range) {
    auto index = range->thread_index;

    if (range->min == 0) {
        range->min = 11;
    }

    for (uint64_t i = range->min; i < range->max; ++i) {
        int iterations = 0;
        multiply_digits(i, &iterations);

        if (iterations > threadRecords[index]) {
            printf(
                    "T=%d, Iterations=%d, New record=%" PRIu64 "\n",
                    range->thread_index,
                    iterations,
                    i
            );

            threadRecords[index] = iterations;
        }

        if (i % 100000000 == 0) {
            printf("T=%d, Current=%" PRIu64 "\n", range->thread_index, i);
        }
    }
}

int main() {
    ThreadCalcRange range;
    range.min = 11;
    range.max = 10000000000000000000;
    find(&range);


//    auto maxThreads = std::thread::hardware_concurrency();
//    uint64_t upper = 0;
//    std::vector<std::thread> threads = {};
//
//    printf("Will Start %d threads\n", maxThreads);
//
//    while (true) {
//        for (int i = 0; i < maxThreads; ++i) {
//            auto range = new ThreadCalcRange();
//
//            range->min = upper + (range->size * i);
//            range->max = range->min + range->size;
//            range->thread_index = i;
//
//            if (range->max >= upper) {
//                upper = range->max;
//            }
//
//            threadRecords[0] = 0;
//
//            std::thread thread([&range]() {
//                printf("T=%d, Min=%lld, Max=%lld\n", range->thread_index, range->min, range->max);
//
//                find(range);
//            });
//
//            threads.push_back(std::move(thread));
//        }

//        for (auto &thread:threads) {
//            thread.join();
//        }
//    }
}