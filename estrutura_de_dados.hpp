
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <chrono>
#include <map>
#include <cmath>

using namespace std;

using TimeT = std::chrono::milliseconds;


/* ------------------------------- Utilitárias ------------------------------ */

void print_arr(vector<int>& data);

auto gen_rand_data(int n, int low = 0, int max=10'000) -> vector<int>;

auto test(vector<int>& data, string algoritm_name= "") -> void;

void are_smaller_than(vector<int>& data, int value);

void are_greater_than(vector<int>& data, int value);

// Desloca os valores no array que iniciam em "begin" até "end" para a
// direita (1 posição). O valor na posição end é perdido
void rshift(vector<int>& data, int begin, int end);

int find_greater_than(vector<int>& data, int value, int start);

void trivial_sort(vector<int>& data);

int find_smaller(const vector<int>& data, int begin, int end);

/* ------------------------------- Algoritmos ------------------------------- */

// Na teoria, este algorimo possui ordem O(N^2), porém esta implementação deve
// ser ainda pior pelo fato de ter de deslocar o array (a função shift)
void insertion_sort(vector<int>& data);

void selection_sort(vector<int>& data);

void bubble_sort(vector<int>& data);

void heap_sort(vector<int>& data);

void quick_sort(vector<int>& data, int from=0, int to=-1);

void merge_sort(vector<int>& data);

void counting_sort(vector<int>& data);

void bucket_sort(vector<int>& data);