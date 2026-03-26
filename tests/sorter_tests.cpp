#include <iostream>
#include <cassert>
#include <random>
#include <chrono>
#include "../include/sequence_lib/ArraySequence.h"
#include "../include/sequence_lib/ListSequence.h"
#include "../include/sorter_lib/QuickSorter.h"
#include "../include/sorter_lib/CocktailSorter.h"

// Проверка отсортированности
template<typename T>
bool IsSorted(Sequence<T>* seq) {
    if (seq->GetLength() <= 1) return true;

    for (int i = 1; i < seq->GetLength(); i++) {
        if (seq->Get(i - 1) > seq->Get(i)) {
            return false;
        }
    }
    return true;
}

// Проверка наличия одинаковых элементов
template<typename T>
bool HasSameElements(Sequence<T>* original, Sequence<T>* sorted) {
    if (original->GetLength() != sorted->GetLength()) return false;

    ArraySequence<T> origCopy;
    ArraySequence<T> sortedCopy;

    for (int i = 0; i < original->GetLength(); i++) {
        origCopy.Append(original->Get(i));
        sortedCopy.Append(sorted->Get(i));
    }

    QuickSorter<T> sorter;
    sorter.Sort(&origCopy);
    sorter.Sort(&sortedCopy);

    for (int i = 0; i < origCopy.GetLength(); i++) {
        if (origCopy.Get(i) != sortedCopy.Get(i)) {
            return false;
        }
    }

    return true;
}

template<typename T>
void GenerateRandomSequence(Sequence<T>* seq, int size, T min = 0, T max = 10000) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dist(min, max);

    for (int i = 0; i < size; i++) {
        seq->Append(dist(gen));
    }
}

template<typename T>
void GenerateNearlySortedSequence(Sequence<T>* seq, int size, int swaps = 10) {
    for (int i = 0; i < size; i++) {
        seq->Append(i);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, size - 1);

    for (int i = 0; i < swaps; i++) {
        int pos1 = dist(gen);
        int pos2 = dist(gen);
        T temp = seq->Get(pos1);
        seq->Set(pos1, seq->Get(pos2));
        seq->Set(pos2, temp);
    }
}

void TestQuickSorterEmptySequence() {
    std::cout << "Testing QuickSorter with empty sequence... ";

    QuickSorter<int> sorter;
    ArraySequence<int> seq;

    Sequence<int>* result = sorter.Sort(&seq);

    assert(result->GetLength() == 0);
    assert(IsSorted(result));

    std::cout << "PASSED" << std::endl;
}

void TestQuickSorterSingleElement() {
    std::cout << "Testing QuickSorter with single element... ";

    QuickSorter<int> sorter;
    ArraySequence<int> seq;
    seq.Append(42);

    Sequence<int>* result = sorter.Sort(&seq);

    assert(result->GetLength() == 1);
    assert(result->Get(0) == 42);
    assert(IsSorted(result));

    std::cout << "PASSED" << std::endl;
}

void TestQuickSorterTwoElements() {
    std::cout << "Testing QuickSorter with two elements... ";

    QuickSorter<int> sorter;
    ArraySequence<int> seq;
    seq.Append(2);
    seq.Append(1);

    Sequence<int>* result = sorter.Sort(&seq);

    assert(result->GetLength() == 2);
    assert(result->Get(0) == 1);
    assert(result->Get(1) == 2);
    assert(IsSorted(result));

    std::cout << "PASSED" << std::endl;
}

void TestQuickSorterAlreadySorted() {
    std::cout << "Testing QuickSorter with already sorted sequence... ";

    QuickSorter<int> sorter;
    ArraySequence<int> seq;

    for (int i = 0; i < 100; i++) {
        seq.Append(i);
    }

    Sequence<int>* result = sorter.Sort(&seq);

    assert(result->GetLength() == 100);
    assert(IsSorted(result));
    assert(result->Get(0) == 0);
    assert(result->Get(99) == 99);

    std::cout << "PASSED" << std::endl;
}

void TestQuickSorterReverseSorted() {
    std::cout << "Testing QuickSorter with reverse sorted sequence... ";

    QuickSorter<int> sorter;
    ArraySequence<int> seq;

    for (int i = 99; i >= 0; i--) {
        seq.Append(i);
    }

    Sequence<int>* result = sorter.Sort(&seq);

    assert(result->GetLength() == 100);
    assert(IsSorted(result));

    for (int i = 0; i < 100; i++) {
        assert(result->Get(i) == i);
    }

    std::cout << "PASSED" << std::endl;
}

void TestQuickSorterAllEqual() {
    std::cout << "Testing QuickSorter with all equal elements... ";

    QuickSorter<int> sorter;
    ArraySequence<int> seq;

    for (int i = 0; i < 100; i++) {
        seq.Append(42);
    }

    Sequence<int>* result = sorter.Sort(&seq);

    assert(result->GetLength() == 100);
    assert(IsSorted(result));

    for (int i = 0; i < 100; i++) {
        assert(result->Get(i) == 42);
    }

    std::cout << "PASSED" << std::endl;
}

void TestQuickSorterRandomSequence() {
    std::cout << "Testing QuickSorter with random sequence... ";

    QuickSorter<int> sorter;
    ArraySequence<int> seq;
    GenerateRandomSequence(&seq, 1000, 0, 10000);

    Sequence<int>* result = sorter.Sort(&seq);

    assert(IsSorted(result));
    assert(HasSameElements(&seq, result));

    std::cout << "PASSED" << std::endl;
}

void TestQuickSorterNearlySorted() {
    std::cout << "Testing QuickSorter with nearly sorted sequence... ";

    QuickSorter<int> sorter;
    ArraySequence<int> seq;
    GenerateNearlySortedSequence(&seq, 1000, 10);

    Sequence<int>* result = sorter.Sort(&seq);

    assert(IsSorted(result));
    assert(HasSameElements(&seq, result));

    std::cout << "PASSED" << std::endl;
}

void TestQuickSorterNegativeNumbers() {
    std::cout << "Testing QuickSorter with negative numbers... ";

    QuickSorter<int> sorter;
    ArraySequence<int> seq;
    seq.Append(-5);
    seq.Append(3);
    seq.Append(-10);
    seq.Append(0);
    seq.Append(7);
    seq.Append(-2);

    Sequence<int>* result = sorter.Sort(&seq);

    assert(IsSorted(result));
    assert(result->Get(0) == -10);
    assert(result->Get(1) == -5);
    assert(result->Get(2) == -2);
    assert(result->Get(3) == 0);
    assert(result->Get(4) == 3);
    assert(result->Get(5) == 7);

    std::cout << "PASSED" << std::endl;
}

void TestQuickSorterDuplicates() {
    std::cout << "Testing QuickSorter with duplicates... ";

    QuickSorter<int> sorter;
    ArraySequence<int> seq;
    seq.Append(5);
    seq.Append(3);
    seq.Append(5);
    seq.Append(1);
    seq.Append(3);
    seq.Append(5);
    seq.Append(2);

    Sequence<int>* result = sorter.Sort(&seq);

    assert(IsSorted(result));
    assert(result->Get(0) == 1);
    assert(result->Get(1) == 2);
    assert(result->Get(2) == 3);
    assert(result->Get(3) == 3);
    assert(result->Get(4) == 5);
    assert(result->Get(5) == 5);
    assert(result->Get(6) == 5);

    std::cout << "PASSED" << std::endl;
}

void TestQuickSorterWithListSequence() {
    std::cout << "Testing QuickSorter with ListSequence... ";

    QuickSorter<int> sorter;
    ListSequence<int> seq;
    seq.Append(5);
    seq.Append(2);
    seq.Append(8);
    seq.Append(1);
    seq.Append(9);
    seq.Append(3);
    seq.Append(7);
    seq.Append(4);
    seq.Append(6);

    Sequence<int>* result = sorter.Sort(&seq);

    assert(IsSorted(result));
    assert(result->Get(0) == 1);
    assert(result->Get(4) == 5);
    assert(result->Get(8) == 9);

    std::cout << "PASSED" << std::endl;
}

void TestQuickSorterLargeSequence() {
    std::cout << "Testing QuickSorter with large sequence (10000 elements)... ";

    QuickSorter<int> sorter;
    ArraySequence<int> seq;
    GenerateRandomSequence(&seq, 10000, 0, 100000);

    auto start = std::chrono::high_resolution_clock::now();
    Sequence<int>* result = sorter.Sort(&seq);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "\n  Time: " << duration.count() << " ms";

    assert(IsSorted(result));
    assert(HasSameElements(&seq, result));

    std::cout << " PASSED" << std::endl;
}

// Тесты для CocktailSorter (Shaker Sort)
void TestCocktailSorterEmptySequence() {
    std::cout << "Testing CocktailSorter with empty sequence... ";

    CocktailSorter<int> sorter;
    ArraySequence<int> seq;

    Sequence<int>* result = sorter.Sort(&seq);

    assert(result->GetLength() == 0);
    assert(IsSorted(result));

    std::cout << "PASSED" << std::endl;
}

void TestCocktailSorterSingleElement() {
    std::cout << "Testing CocktailSorter with single element... ";

    CocktailSorter<int> sorter;
    ArraySequence<int> seq;
    seq.Append(42);

    Sequence<int>* result = sorter.Sort(&seq);

    assert(result->GetLength() == 1);
    assert(result->Get(0) == 42);
    assert(IsSorted(result));

    std::cout << "PASSED" << std::endl;
}

void TestCocktailSorterTwoElements() {
    std::cout << "Testing CocktailSorter with two elements... ";

    CocktailSorter<int> sorter;
    ArraySequence<int> seq;
    seq.Append(2);
    seq.Append(1);

    Sequence<int>* result = sorter.Sort(&seq);

    assert(result->GetLength() == 2);
    assert(result->Get(0) == 1);
    assert(result->Get(1) == 2);
    assert(IsSorted(result));

    std::cout << "PASSED" << std::endl;
}

void TestCocktailSorterAlreadySorted() {
    std::cout << "Testing CocktailSorter with already sorted sequence... ";

    CocktailSorter<int> sorter;
    ArraySequence<int> seq;

    for (int i = 0; i < 100; i++) {
        seq.Append(i);
    }

    Sequence<int>* result = sorter.Sort(&seq);

    assert(result->GetLength() == 100);
    assert(IsSorted(result));
    assert(result->Get(0) == 0);
    assert(result->Get(99) == 99);

    std::cout << "PASSED" << std::endl;
}

void TestCocktailSorterReverseSorted() {
    std::cout << "Testing CocktailSorter with reverse sorted sequence... ";

    CocktailSorter<int> sorter;
    ArraySequence<int> seq;

    for (int i = 99; i >= 0; i--) {
        seq.Append(i);
    }

    Sequence<int>* result = sorter.Sort(&seq);

    assert(result->GetLength() == 100);
    assert(IsSorted(result));

    for (int i = 0; i < 100; i++) {
        assert(result->Get(i) == i);
    }

    std::cout << "PASSED" << std::endl;
}

void TestCocktailSorterAllEqual() {
    std::cout << "Testing CocktailSorter with all equal elements... ";

    CocktailSorter<int> sorter;
    ArraySequence<int> seq;

    for (int i = 0; i < 100; i++) {
        seq.Append(42);
    }

    Sequence<int>* result = sorter.Sort(&seq);

    assert(result->GetLength() == 100);
    assert(IsSorted(result));

    for (int i = 0; i < 100; i++) {
        assert(result->Get(i) == 42);
    }

    std::cout << "PASSED" << std::endl;
}

void TestCocktailSorterRandomSequence() {
    std::cout << "Testing CocktailSorter with random sequence... ";

    CocktailSorter<int> sorter;
    ArraySequence<int> seq;
    GenerateRandomSequence(&seq, 500, 0, 1000);

    Sequence<int>* result = sorter.Sort(&seq);

    assert(IsSorted(result));
    assert(HasSameElements(&seq, result));

    std::cout << "PASSED" << std::endl;
}

void TestCocktailSorterNegativeNumbers() {
    std::cout << "Testing CocktailSorter with negative numbers... ";

    CocktailSorter<int> sorter;
    ArraySequence<int> seq;
    seq.Append(-5);
    seq.Append(3);
    seq.Append(-10);
    seq.Append(0);
    seq.Append(7);
    seq.Append(-2);

    Sequence<int>* result = sorter.Sort(&seq);

    assert(IsSorted(result));
    assert(result->Get(0) == -10);
    assert(result->Get(1) == -5);
    assert(result->Get(2) == -2);
    assert(result->Get(3) == 0);
    assert(result->Get(4) == 3);
    assert(result->Get(5) == 7);

    std::cout << "PASSED" << std::endl;
}

void TestCocktailSorterDuplicates() {
    std::cout << "Testing CocktailSorter with duplicates... ";

    CocktailSorter<int> sorter;
    ArraySequence<int> seq;
    seq.Append(5);
    seq.Append(3);
    seq.Append(5);
    seq.Append(1);
    seq.Append(3);
    seq.Append(5);
    seq.Append(2);

    Sequence<int>* result = sorter.Sort(&seq);

    assert(IsSorted(result));
    assert(result->Get(0) == 1);
    assert(result->Get(1) == 2);
    assert(result->Get(2) == 3);
    assert(result->Get(3) == 3);
    assert(result->Get(4) == 5);
    assert(result->Get(5) == 5);
    assert(result->Get(6) == 5);

    std::cout << "PASSED" << std::endl;
}

void TestCocktailSorterWithListSequence() {
    std::cout << "Testing CocktailSorter with ListSequence... ";

    CocktailSorter<int> sorter;
    ListSequence<int> seq;
    seq.Append(5);
    seq.Append(2);
    seq.Append(8);
    seq.Append(1);
    seq.Append(9);
    seq.Append(3);
    seq.Append(7);
    seq.Append(4);
    seq.Append(6);

    Sequence<int>* result = sorter.Sort(&seq);

    assert(IsSorted(result));
    assert(result->Get(0) == 1);
    assert(result->Get(4) == 5);
    assert(result->Get(8) == 9);

    std::cout << "PASSED" << std::endl;
}

void TestCocktailSorterLargeSequence() {
    std::cout << "Testing CocktailSorter with large sequence (5000 elements)... ";

    CocktailSorter<int> sorter;
    ArraySequence<int> seq;
    GenerateRandomSequence(&seq, 5000, 0, 10000);

    auto start = std::chrono::high_resolution_clock::now();
    Sequence<int>* result = sorter.Sort(&seq);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "\n  Time: " << duration.count() << " ms";

    assert(IsSorted(result));
    assert(HasSameElements(&seq, result));

    std::cout << " PASSED" << std::endl;
}

void ComparePerformance() {
    std::cout << "=== Performance Comparison ===" << std::endl;
    std::cout << "Size\tQuickSort (ms)\tCocktailSort (ms)" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    const int SIZES[] = {100, 500, 1000, 2000, 5000};

    QuickSorter<int> quickSorter;
    CocktailSorter<int> cocktailSorter;

    for (int size : SIZES) {
        ArraySequence<int> original;
        GenerateRandomSequence(&original, size, 0, size * 10);

        // Тестируем QuickSort
        ArraySequence<int> quickCopy;
        for (int i = 0; i < original.GetLength(); i++) {
            quickCopy.Append(original.Get(i));
        }

        auto start = std::chrono::high_resolution_clock::now();
        quickSorter.Sort(&quickCopy);
        auto end = std::chrono::high_resolution_clock::now();
        auto quickTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // Тестируем CocktailSort
        ArraySequence<int> cocktailCopy;
        for (int i = 0; i < original.GetLength(); i++) {
            cocktailCopy.Append(original.Get(i));
        }

        start = std::chrono::high_resolution_clock::now();
        cocktailSorter.Sort(&cocktailCopy);
        end = std::chrono::high_resolution_clock::now();
        auto cocktailTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << size << "\t" << quickTime << "\t\t" << cocktailTime << std::endl;

        // Проверяем корректность
        assert(IsSorted(&quickCopy));
        assert(IsSorted(&cocktailCopy));
    }
}

int main() {
    std::cout << "Testing QuickSorter: " << std::endl;
    TestQuickSorterEmptySequence();
    TestQuickSorterSingleElement();
    TestQuickSorterTwoElements();
    TestQuickSorterAlreadySorted();
    TestQuickSorterReverseSorted();
    TestQuickSorterAllEqual();
    TestQuickSorterRandomSequence();
    TestQuickSorterNearlySorted();
    TestQuickSorterNegativeNumbers();
    TestQuickSorterDuplicates();
    TestQuickSorterWithListSequence();
    TestQuickSorterLargeSequence();

    std::cout << "Testing CocktailSorter: " << std::endl;
    TestCocktailSorterEmptySequence();
    TestCocktailSorterSingleElement();
    TestCocktailSorterTwoElements();
    TestCocktailSorterAlreadySorted();
    TestCocktailSorterReverseSorted();
    TestCocktailSorterAllEqual();
    TestCocktailSorterRandomSequence();
    TestCocktailSorterNegativeNumbers();
    TestCocktailSorterDuplicates();
    TestCocktailSorterWithListSequence();
    TestCocktailSorterLargeSequence();

    std::cout << "Comparison: " << std::endl;
    ComparePerformance();

    std::cout << "All tests passed" << std::endl;

    return 0;
}