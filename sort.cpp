
/* -------------------------------------------------------------------------- */
/*               Implementação de alguns Algoritmos de Ordenação              */
/*                                                                            */
/*  Autor: Matheus Cândido Teixeira                                           */
/*                                                                            */
/* -------------------------------------------------------------------------- */


#include "estrutura_de_dados.hpp"

int main() {
    const int DATA_LEN = 4000;

    cout << "🚀 Starting Test :" << endl;

/* ----------------------------- Insertion Sort ----------------------------- */

    auto data = gen_rand_data(DATA_LEN);

    insertion_sort(data);

    test(data, "insertion sort");

/* ----------------------------- Selection Sort ----------------------------- */

    data = gen_rand_data(DATA_LEN);

    selection_sort(data);

    test(data, "selection");

/* ------------------------------- Bubble Sort ------------------------------ */

    data = gen_rand_data(DATA_LEN);

    bubble_sort(data);

    test(data, "bubble sort");


/* ------------------------------ Counting Sort ----------------------------- */

    data = gen_rand_data(DATA_LEN);

    counting_sort(data);

    test(data, "counting_sort");

/* ------------------------------- Bucket Sort ------------------------------ */

    data = gen_rand_data(DATA_LEN);

    bucket_sort(data);

    test(data, "bucket sort");

/* ------------------------------- Quick Sort ------------------------------- */

    data = gen_rand_data(DATA_LEN * 40);

    quick_sort(data);

    test(data, "quick sort");

/* ------------------------------- Merge Sort ------------------------------- */

    data = gen_rand_data(DATA_LEN * 400);

    merge_sort(data);

    test(data, "merge sort");

/* -------------------------------- Heap Sort ------------------------------- */

    data = gen_rand_data(DATA_LEN  * 4000);

    heap_sort(data);

    test(data, "heap sort");

/* -------------------------------------------------------------------------- */

    return 0;
}