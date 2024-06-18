#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include "../sort.hpp"

int int_cmp(const int &a, const int &b)
{
    if (a ^ b)
    {
        return (a > b) ? 1 : -1;
    }

    return 0;
}

std::vector<int> generateRandomArray(int minLength, int maxLength, int minValue, int maxValue)
{
    // Initialize a random number generator with a seed based on the current time
    std::mt19937 rng(static_cast<unsigned int>(std::time(0)));

    // Define a distribution for the array length
    std::uniform_int_distribution<int> lengthDist(minLength, maxLength);

    // Generate a random length for the array
    size_t length = (size_t)lengthDist(rng);

    // Define a distribution for the array values
    std::uniform_int_distribution<int> valueDist(minValue, maxValue);

    // Create the array and fill it with random values
    std::vector<int> array((size_t)length);
    for (size_t i = 0; i < length; ++i)
    {
        array[i] = valueDist(rng);
    }

    return array;
}

int main()
{
    int minLength = 1;   // Minimum length of the array
    int maxLength = 300; // Maximum length of the array
    int minValue = 1;    // Minimum value of random numbers
    int maxValue = 100;  // Maximum value of random numbers
    int num_tests = 100; // Number of Tests

    // insertion_sort tests
    std::cout << "Testing: insertion_sort\n";
    for (int i = 0; i < num_tests; i++)
    {
        std::vector<int> randomArray = generateRandomArray(minLength, maxLength, minValue, maxValue);
        insertion_sort<int>(randomArray, 0, randomArray.size(), int_cmp);
        assert(is_sorted<int>(randomArray, 0, randomArray.size(), int_cmp));
    }
    std::cout << "SUCCESS: All tests passed!\n";

    std::cout << "Testing: merge_sort\n";
    for (int i = 0; i < num_tests; i++)
    {
        std::vector<int> randomArray = generateRandomArray(minLength, maxLength, minValue, maxValue);
        merge_sort<int>(randomArray, 0, randomArray.size(), int_cmp);
        assert(is_sorted<int>(randomArray, 0, randomArray.size(), int_cmp));
    }
    std::cout << "SUCCESS: All tests passed!\n";
    return 0;
}
