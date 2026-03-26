#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include "random"
#include "../include/sequence_lib/ArraySequence.h"
#include "../include/sequence_lib/ListSequence.h"
#include "../include/sorter_lib/ISorter.h"
#include "../include/sorter_lib/QuickSorter.h"
#include "../include/sorter_lib/CocktailSorter.h"

template<typename T>
T get_input(T default_value) {
    std::string input;
    T new_value;

    std::getline(std::cin, input);
    if (!input.empty()) {
        std::istringstream stream(input);
        stream >> new_value;

        return new_value;
    }
    return default_value;
}

Sequence<int>* generateSequence(Sequence<int>* seq, int length, int type) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,100);

    if (type == 1) {
        seq->Append(dist(rng));
        for (int i = 1; i < length; i++) {
            seq->Append(seq->Get(i-1) + dist(rng));
        }
    } else if (type == 2) {
        for (int i = 0; i < length; i++) {
            seq->Append(dist(rng));
        }
    } else if (type == 3) {
        seq->Append(dist(rng));
        for (int i = 1; i < length; i++) {
            seq->Append(seq->Get(i-1) - dist(rng));
        }
    }

    return seq;
}

ArraySequence<int> menu() {
    ArraySequence<int> menu_values;

    int creation_type = 1;
    int seq_len = 10;
    int seq_type = 2;
    int sort_meth = 5;

    while (true) {
        std::cout << "Choose how to create sequence. Default 1:" << std::endl;
        std::cout << "1. Automatic" << std::endl;
        std::cout << "2. Manually" << std::endl;

        creation_type = get_input(creation_type);

        if (creation_type >= 1 && creation_type <=2) {
            break;
        }
        std::cout << "Wrong value! Please write correct value." << std::endl << std::endl;
    }

    if (creation_type == 1) {
        while (true) {
            std::cout << "Set sequence length (write -1 for long sequence). Default 10:" << std::endl;

            seq_len = get_input(seq_len);

            if (seq_len >= -1) {
                break;
            }
            std::cout << "Wrong value! Please write correct value." << std::endl << std::endl;
        }

        while (true) {
            std::cout << "Set sequence type (you can write multiple numbers separated with space). Default 2:"
                      << std::endl;
            std::cout << "1. Sorted" << std::endl;
            std::cout << "2. Unsorted" << std::endl;
            std::cout << "3. Sorted backwards" << std::endl;

            seq_type = get_input(seq_type);

            if (seq_type >= 1 && seq_type <= 3) {
                break;
            }
            std::cout << "Wrong value! Please write correct value." << std::endl << std::endl;
        }
    }

    while (true) {
        std::cout << "Choose sort method and additional functionality. Default 5:" << std::endl;
        std::cout << "1. QuickSort" << std::endl;
        std::cout << "2. QuickSort with time-lapse" << std::endl;
        std::cout << "3. CocktailSort" << std::endl;
        std::cout << "4. CocktailSort with time-lapse" << std::endl;
        std::cout << "5. Compare execution time for both sort methods" << std::endl;

        sort_meth = get_input(sort_meth);

        if (sort_meth >= 1 && sort_meth <= 5) {
            break;
        }
        std::cout << "Wrong value! Please write correct value." << std::endl << std::endl;
    }

    menu_values.Append(creation_type);
    menu_values.Append(seq_len);
    menu_values.Append(seq_type);
    menu_values.Append(sort_meth);

    return menu_values;
}


void sort_analyzer(ISorter<int>* sorter, Sequence<int>* seq, bool need_time) {
    clock_t start = clock();

    sorter->Sort(seq);

    clock_t stop = clock();
    double elapsed = double(stop - start) / CLOCKS_PER_SEC;

    std::cout << "Sorted sequence: ";

    for (int i = 0; i < seq->GetLength(); i++) {
        std::cout << seq->Get(i) << " ";
    }
    if (need_time) {
        std::cout << std::endl << "Elapsed time: " << elapsed << std::endl;
    }
}


int main() {
    ListSequence<int> list;
    ArraySequence<int> array;
    ArraySequence<int> menu_values = menu();

    QuickSorter<int> qSort;
    CocktailSorter<int> cSort;

    if (menu_values.Get(0) == 1) {
        int test_leng = menu_values.Get(1);
        if (menu_values.Get(1) == -1) {
            test_leng = 10000;
        }

        generateSequence(&list, test_leng, menu_values.Get(2));
        generateSequence(&array, test_leng, menu_values.Get(2));

        std::cout << "The initial sequences: " << std::endl << "Array: ";
        for (int i = 0; i < array.GetLength(); i++) {
            std::cout << array.Get(i) << " ";
        }
        std::cout << std::endl << "List: ";
        for (int i = 0; i < list.GetLength(); i++) {
            std::cout << list.Get(i) << " ";
        }
        std::cout << std::endl;

    } else {
        std::cout << "Start writing sequence elements. Write ~ for end of sequence:" << std::endl;
        std::string input;

        while (true) {
            std::cout << "> ";
            std::cin >> input;

            if (input == "~") {
                break;
            }

            try {
                int element = std::stoi(input);
                array.Append(element);
                list.Append(element);
            } catch (const std::exception& e) {
                std::cout << "You can only write numbers or symbol ~ for stop end of sequence" << std::endl;
            }
        }

        std::cout << "The entered sequence: ";
        for (int i = 0; i < array.GetLength(); i++) {
            std::cout << array.Get(i) << " ";
        }
        std::cout << std::endl;
    }

    if (menu_values.Get(3) < 5) {
        ISorter<int>* sorter;
        if (menu_values.Get(3) < 3) {
            sorter = &qSort;
        } else {
            sorter = &cSort;
        }

        std::cout << "Results for " << sorter->GetName() << " Array: " << std::endl;
        sort_analyzer(sorter, &array, menu_values.Get(3) % 2 == 0);

        std::cout << "Results for " << sorter->GetName() << " List: " << std::endl;
        sort_analyzer(sorter, &list, menu_values.Get(3) % 2 == 0);
    } else {
        std::cout << "Results for Quick Sort: " << std::endl;
        sort_analyzer(&qSort, &array, true);
        sort_analyzer(&qSort, &list, true);
        std::cout << std::endl << "Results for Cocktail Sort: " << std::endl;
        sort_analyzer(&cSort, &array, true);
        sort_analyzer(&cSort, &list, true);
    }



    return 0;
}
