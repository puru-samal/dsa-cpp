#include <vector>

/*
 * Debug macros, which can be enabled by adding -DDEBUG in the Makefile
 */
#ifdef DEBUG
#define dbg_assert(...) assert(__VA_ARGS__)
#define dbg_printf(...) fprintf(stderr, __VA_ARGS__)
#else
#define dbg_assert(...)
#define dbg_printf(...)
#endif

/**
 * @brief A helper functuion to see if a vector is sorted based on predicate function.
 *
 * @tparam T
 * @param V  vector containing objects of type T
 * @param lo start index. lo >= 0 && lo < hi
 * @param hi end index. hi > lo && hi <= V.size()
 * @param cmp_fn generic predicate function. compares two objects of type T and returns an int.
 * @return true indicates vector is sorted based on predicate.
 * @return false indicates vector is not sorted based on predicate.
 */
template <typename T>
bool is_sorted(const std::vector<T> &V, size_t lo, size_t hi, std::function<int(const T &, const T &)> cmp_fn)
{
    dbg_assert(lo >= 0 && lo < hi && hi <= V.size());

    if (lo + 1 >= hi)
        return true;

    if (cmp_fn(V[lo], V[lo + 1]) > 0)
        return false;

    return is_sorted(V, lo + 1, hi, cmp_fn);
}

/**
 * @brief Impmementation of the insertion sort algorithm. Requires 0 <= lo && lo <= hi && hi <= V.size();
 *
 * @tparam T
 * @param V  vector containing objects of type T
 * @param lo start index. lo >= 0 && lo <= hi
 * @param hi end index. hi > lo && hi <= V.size()
 * @param cmp_fn  generic predicate function. compares two objects of type T and returns an int.
 */
template <typename T>
void insertion_sort(std::vector<T> &V, size_t lo, size_t hi, std::function<int(const T &, const T &)> cmp_fn)
{
    dbg_assert(lo >= 0 && lo <= hi && hi <= V.size());

    if (lo + 1 >= hi)
        return;

    for (size_t i = lo + 1; i < hi; i++)
    {
        // Loop invariant
        dbg_assert(is_sorted(V, lo, i, cmp_fn));

        T key = V[i];
        size_t j = i;

        while (j-- > 0 && cmp_fn(V[j], key) > 0)
        {
            V[j + 1] = V[j];
        }

        V[j + 1] = key;
    }
}

/**
 * @brief Helper function to merge two sorted sub-arrays. Requires 0 <= lo && lo <= mid && mid <= hi && hi <= V.size()
 *
 * @tparam T
 * @param V   vector containing objects of type T
 * @param lo  start index.
 * @param mid mid index. mid >= 0 && lo <= mid  && mid < hi
 * @param hi  end index. hi > lo && hi > mid && hi <= V.size()
 * @param cmp_fn  generic predicate function. compares two objects of type T and returns an int.
 */
template <typename T>
void merge(std::vector<T> &V, size_t lo, size_t mid, size_t hi, std::function<int(const T &, const T &)> cmp_fn)
{
    dbg_assert(0 <= lo && lo <= mid && mid <= hi && hi <= V.size());

    // Tmp vector to store sorted array
    std::vector<T> tmp(hi - lo);

    // i : idx into smallest element in left subarray
    // j : idx into smallest element in right subarray
    // k : idx into location in tmp
    size_t i = lo, j = mid, k = 0;

    while (i < mid && j < hi)
    {
        if (cmp_fn(V[i], V[j]) < 0)
        {
            tmp[k] = V[i];
            i++;
        }
        else
        {
            tmp[k] = V[j];
            j++;
        }
        k++;
    }

    // Copy remaining
    while (i < mid)
    {
        tmp[k] = V[i];
        i++;
        k++;
    }
    while (j < hi)
    {
        tmp[k] = V[j];
        j++;
        k++;
    }

    // Copy back into original array
    for (k = 0; k < hi - lo; k++)
    {
        V[lo + k] = tmp[k];
    }
}

/**
 * @brief Implementation of the merge sort algorithm.
 *
 * @tparam T
 * @param V  vector containing objects of type T
 * @param lo start index. lo >= 0 && lo < hi
 * @param hi end index. hi > lo && hi <= V.size()
 * @param cmp_fn  generic predicate function. compares two objects of type T and returns an int.
 */
template <typename T>
void merge_sort(std::vector<T> &V, size_t lo, size_t hi, std::function<int(const T &, const T &)> cmp_fn)
{
    dbg_assert(lo >= 0 && lo <= hi && hi <= V.size());
    if (hi - lo <= 1)
        return;
    size_t mid = lo + (hi - lo) / 2;
    merge_sort(V, lo, mid, cmp_fn);
    merge_sort(V, mid, hi, cmp_fn);
    merge(V, lo, mid, hi, cmp_fn);
}