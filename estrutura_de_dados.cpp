#include "estrutura_de_dados.hpp"

// Utilizado para demonstrar vizualmente o resultado da ordenação.
// Não utilize está função para testes. Prefira uma asserção.
void print_arr(vector<int>& data) {
    for (auto v: data) {
        cout << v << " ";
    }
    cout << endl;
}

// Gera dados "aleatórios" para a ordenação.
auto gen_rand_data(int n, int low, int max) -> vector<int> {
    vector<int> out{};
    for (int i = 0; i < n; ++i) {
        out.push_back(low+random()%(max-low));
    }

    return std::move(out);
}

// Testa se o vetor está ordenado. É testado apenas se o vetor está na
// ordem crescente.
auto test(vector<int>& data, string algoritm_name) -> void {
    cout << ("🔥 testing " + algoritm_name + " ");
    cout << ("data size: " + to_string(data.size()) + "...");
    bool error = false;
    for (int i=0; (i < data.size() - 1) && !error; ++i) {
        if (data[i] > data[i+1]) error = true;
    }
    cout << (error ? "❌":"✓") << endl;
}

// Testa se os valores no vetor são menores do que o valor passado por
// parâmetro.
void are_smaller_than(vector<int>& data, int value) {
    for (auto v: data){
        assert(v < value);
    }
}

// Testa se os valores no vetor são maiores do que o valor passado por
// parâmetro.
void are_greater_than(vector<int>& data, int value) {
    for (auto v: data){
        assert(v >= value);
    }
}

// Desloca os valores no array que iniciam em "begin" até "end" para a
// direita (1 posição).
void rshift(vector<int>& data, int begin, int end) {
    if (end > data.size())
        throw out_of_range{
            "end > data.size() at estrutura_de_dados " + __LINE__
        };

    // Salva para reinseri-lo no começo
    int last = data[end];

    // Desloca os demais elementos
    for (int i=end; i >= begin; --i) {
        data[i+1] = data[i];
    }

    // Atribui o valor da última posição do vetor na primeira posição do vetor
    // deslocado.
    data[begin] = last;
}


void insertion_sort(vector<int>& data) {
    for (int i = 0; i < data.size(); ++i) {
        // Procura onde inserir
        int j  = 0;
        while (j < i && data[j] < data[i]) ++j;

        // Caso não haja encontrado.
        if (i == j) continue;

        // Salva o dado.
        int temp = data[i];

        // Desloca os valores maiores do que ele.
        rshift(data, j, i-1);

        // Insere o valor na posição.
        swap(data[j], temp);
    }
}

int find_smaller(const vector<int>& data, int begin, int end) {
    // Valor de referência.
    auto smaller = data[begin];

    // Procura no array por algum valor menor. Ordem da busca: O(N)
    for (int i = begin + 1; i < end; ++i) {
        // Testa se o valor é menor. Se for, atualize.
        if (data[i] < smaller)  {
            smaller = data[i];
        }
    }

    // Retorne o valor
    return smaller;
}

/* int find_greater_than(vector<int>& data, int start, int value) {
    for (int i = start; i < data.size(); ++i)
        if (data[i] > value) {
            return i;
        }
} */

void selection_sort(vector<int>& data) {
    const auto sz = data.size();
    // Itera pelo array
    for (int i = 0; i < sz; ++i) {
        // Substitui a posição avaliada pelo menor elemento da parte não
        // ordenado do vetor, ie, a parte à direita.
        int smaller = find_smaller(data, i, sz);

        // Embora seja possível remover a repetição pelo próprio valor, isso
        // não traria nenhuma vantagem. Pelo contrário, teria de executar uma
        // if-stmt O(N^2) vezes para um caso excepcional.
        swap(data[i], smaller);
    }
}


void bubble_sort(vector<int>& data) {
    const auto sz = data.size();

    // Em cada iteração o maior valor contido no array "borbulha" para o
    // final do array. Como último valor está ordendo, a cata iteração o
    // o tamanho do vetor desordenado decaí.
    for (int j = sz - 1; j >= 0; --j) {
        for (int i = 0; i < j; ++i) {
            if (data[i] > data[i+1])
                swap(data[i], data[i+1]);
        }
    }
}

void counting_sort(vector<int>& data) {
    using Pr = std::pair<int, int>;

    // "Keys are sorted by using the comparison function Compare."
    // Lêia: https://en.cppreference.com/w/cpp/container/map para enterder os
    // constraint de um map no C++.
    map<int, int> itens{};

    // Indentifica as ocorrências
    for (auto v: data) {
        if (itens.find(v) != itens.end())
            itens[v]++;
        else
            itens.insert(Pr{v, 1});
    }

    // Replica os dados baseado na recorrência dos valores.
    int last_postion = 0;
    for (auto v: itens) {
        const auto value = v.first;
        const auto times = v.second;

        for (int i = 0; i < times; ++i)
            data[last_postion++] = value;
    }
}


void bucket_sort(vector<int>& data) {
    // O número de buckets, o ideal é que ele seja proporcional ao tamanho do
    // dado para que haja uma melhora do desempenho do algoritmo independente-
    // mente da entrada.
    int n_buckets = 200;

    // Procura index que contém o valor máximo e mínimo do vetor.
    int ind_max = distance(data.begin(), max_element(data.begin(), data.end()));
    int ind_min = distance(data.begin(), min_element(data.begin(), data.end()));

    // O valor máximo e mínimo do vetor.
    int max =  data[ind_max];
    int min =  data[ind_min];

    // O número aproximado de elementos no vetor.
    int delta = ceil((double)(max - min)/n_buckets);

    // Cria os n_buckets buckets
    vector<vector<int>> buckets{
        (long unsigned int)n_buckets, vector<int>{}};

    // Insere os dados nos seus respectivos buckets.
    for (int i = 0; i < data.size(); ++i) {
        // "data[i] - min", desloca o valor mínimo para próximo do 0.
        int selected_bucket = static_cast<int>(ceil(data[i]-min)/delta);

        // Note que cada bucket possui valores dentro de uma faixa específica.
        buckets[selected_bucket].push_back(data[i]);
    }

    data.clear();

    // Ordena cada bucket e reinsere no vetor.
    for (auto& bucket: buckets) {
        counting_sort(bucket);
        data.insert(data.end(), bucket.begin(), bucket.end());
    }
}

void heap_sort(vector<int>& data) {
    vector<int> temp{};

    // Caso o vetor não seja um heap, transoforme-o em uma heap.
    if (!is_heap(data.begin(), data.end()))
        make_heap(data.begin(), data.end());

    while (data.size()) {
        // Baseado no conceito de heap (uma árvore completa), que possui como
        // raiz o maior valor no topo, retire do vetor a raiz da árvore
        // (o maior valor) e adicione-o em um vetor temporário.
        pop_heap(data.begin(), data.end());

        // Insira os dados no final do vetor para obter maior desempenho (supo-
        // sição minha) e depois inverta-o.
        temp.push_back(data.back());

        data.pop_back();
    }

    // Inverte o vetor.
    data.insert(data.begin(), temp.rbegin(), temp.rend());
}

void trivial_sort(vector<int>& data) {
    if (data.size() == 2)
        if (data[0] > data[1])
            swap(data[0], data[1]);
}


void merge_sort(vector<int>& data) {
    // Se o tamanho do vetor for suficientemente pequeno ordene-o.
    if (data.size() <= 2) {
        trivial_sort(data);
        return;
    }

    // Dois vetores temporátios para simplificar a divisão do vetor e a imple-
    // mentação. Um armazena os valores à direita do ponto médio e outro
    // os valores à esquerda do ponto médio.
    vector<int> _start{}, _end{};
    int ind_middle = ceil((double)data.size()/2);
    assert(ind_middle >= 0 && ind_middle < data.size());

    // Copia os dois vetores para os temporários.
    auto divisor = data.begin() + ind_middle;
    _start.insert(_start.begin(), data.begin(), divisor);
    _end.insert(_end.begin(), divisor, data.end());

    assert(_start.size() + _end.size() == data.size());

    assert(_start.size() > 0);
    assert(_end.size() > 0);

    int old_start_sz = _start.size(), old_end_sz = _end.size();

    // Aplica a recursividade.
    merge_sort(_start);
    merge_sort(_end);

    assert(old_start_sz == _start.size() && old_end_sz == _end.size());

    assert(_start.size() + _end.size() == data.size());

    // Esvazia o vetor original.
    data.clear();

    // Neste ponto as metades já estão ordenadas. Então aplique um "merge"
    // mantendo a ordenação.
    int current_start = 0, current_end = 0;
    while (current_start < _start.size() && current_end < _end.size()) {
        if (_start[current_start] < _end[current_end]) {
            data.push_back(_start[current_start]);
            ++current_start;
        } else {
            data.push_back(_end[current_end]);
            ++current_end;
        }
    }

    assert(_start.size() == current_start || _end.size() == current_end);

    // Insere o que restou no final do vetor.
    if (current_start < _start.size())
        data.insert(data.end(), _start.begin() + current_start, _start.end());

    if (current_end < _end.size());
        data.insert(data.end(), _end.begin() + current_end, _end.end());

    assert(_start.size() + _end.size() == data.size());
}

void quick_sort(vector<int>& data, int from, int to) {
    // Substitui pelo valor correto
    if (to == -1) to = data.size();

    // Se há apenas um valor, então ele já está ordenado.
    if (to - from < 2) return;

    // Calcula o divisor. Escolhendo o valor aleatóriamente eu evito o pior
    // caso.
    int ind_divisor = random()%(to - from) + from;
    assert(ind_divisor < data.size());
    int divisor = data[ind_divisor];


    // Divide os itens entre maiores e menores. O divisor não é inserido
    // neste momento.
    vector<int> greater{}, lower{};
    for (int i = from; i < to; ++i) {
        if (i==ind_divisor) continue;

        if (data[i] < divisor)
            lower.push_back(data[i]);
        else
            greater.push_back(data[i]);
    }

    assert(lower.size() + greater.size() + 1 == (to - from));

    // are_smaller_than(lower, divisor);
    // are_greater_than(greater, divisor);

    // Adiciona os valores menores, o divisor e os valores maiores na posição
    // que está sendo ordenada. A posição do divisor é atualizada e ele está
    // após o último elemento dos números menores do que ele, isto é,
    // Offset + tamanha(vetor_menor)
    ind_divisor = from + lower.size();
    lower.push_back(divisor);
    lower.insert(lower.end(), greater.begin(), greater.end());

    data.erase(data.begin() + from, data.begin() + to);
    data.insert(data.begin() + from, lower.begin(), lower.end());


    assert(data[ind_divisor] == divisor);

    assert(lower.size() == (to - from));

    // Ordena as metades do array separados pelo elemento divisor
    quick_sort(data, from, ind_divisor);
    quick_sort(data, ind_divisor + 1, to);
}

