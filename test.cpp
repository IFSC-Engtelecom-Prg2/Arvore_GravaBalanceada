//
// Created by sobral on 27/07/19.
//
#include <limits.h>
#include <time.h>
#include <string>
#include <algorithm>
#include <vector>
#include <ostream>
#include <sstream>
#include <fstream>
#include <list>
#include <libs/arvore.h>
#include <chrono>
#include <random>
#include "questao.h"
#include "gtest/gtest.h"

using namespace std;
using prglib::arvore;

class TesteQuestao: public ::testing::Test {
protected:
    virtual void SetUp() {
        srand(clock());
    }
    const string Palavras = "../palavras.txt";
    const string Dados = "dados.txt";

    template <class T> void embaralha(list<T> & l) {
        if (l.size() < 2) return;
        static bool _started = false;
        static std::default_random_engine generator;

        if (not _started) {
            auto t = std::chrono::high_resolution_clock::now();
            _started = true;
            generator.seed(std::chrono::high_resolution_clock::to_time_t(t));
        }
        vector<T> v(l.begin(), l.end());
        shuffle(v.begin(), v.end(), generator);
        l.clear();
        l.insert(l.begin(),v.begin(), v.end());
    }

    void gera_arq(long size, bool sorted) {
        ifstream inp(Palavras);
        if (! inp.is_open()) throw -1;
        ofstream out(Dados);
        list<string> l;
        string w;

        while (getline(inp, w) and size--) l.push_back(w);
        if (sorted) l.sort();
        else embaralha(l);
        for (auto & x: l) out << x << endl;
        inp.close();
        out.close();
    }

    shared_ptr<arvore<string>> gera_arvore(const string & nome) {
        ifstream arq(nome);
        string w;


        getline(arq, w);
        auto a = new arvore<string>(w);
        while (getline(arq, w)) a->adiciona(w);
        arq.close();

        return shared_ptr<arvore<string>>(a);
    }

    bool compara(arvore<string> * a1, arvore<string> * a2) {
        // implemente aqui sua função ...
        list<string> l1, l2;

        if (a1) a1->listePreOrder(l1);
        if (a2) a2->listePreOrder(l2);

        return l1 == l2;
    }
};

TEST_F(TesteQuestao, Invalido)
{
    try {
        reordena("words.txt");
        FAIL() <<"em caso de arquivo inválido, deve-se gerar uma exceção";
    } catch (...) {
    }
}

TEST_F(TesteQuestao, Normal)
{
    for (int n=5; n > 0; n--) {
        try {
            gera_arq(500 + (rand() % 1000), false);
            auto a0 = gera_arvore(Dados);
            reordena(Dados);
            auto a1 = gera_arvore(Dados);
            auto a2 = a0->balanceia(true);
            //FAIL() <<"a2: "+to_string(a2->altura())+", a1: "+to_string(a1->altura()));
            //FAIL() <<compara(a2, a1.get()));
            if (not compara(a2, a1.get())) {
                ostringstream os;

                os << "palavras não foram gravadas de forma a se poder gerar uma árvore balanceada otimamente:\n ";
                int l1 = a1->tamanho();
                int l0 = a0->tamanho();
                if (l1 != l0) os << " novo arquivo tem "+to_string(l1) +" palavras, mas original tem "+to_string(l0)+" palavras\n";
                int h1 = a1->altura();
                int h2 = a2->altura();
                if (h1 != h2) os << " árvore gerada do novo arquivo tem altura "+to_string(h1) +", mas deveria ter "+to_string(h2);
                FAIL() <<os.str();
                return;
            }
        } catch (...) {
            FAIL() <<"exceção inesperada";
        }
    }

}

TEST_F(TesteQuestao, Ordenado)
{
    for (int n=5; n > 0; n--) {
        try {
            gera_arq(500 + (rand() % 1000), true);
            auto a0 = gera_arvore(Dados);
            reordena(Dados);
            auto a1 = gera_arvore(Dados);
            auto a2 = a0->balanceia(true);
            if (not compara(a2, a1.get())) {
                FAIL() <<"palavras não foram gravadas de forma a se poder gerar uma árvore balanceada otimamente";
                return;
            }
        } catch (...) {
            FAIL() <<"exceção inesperada";
        }
    }
}