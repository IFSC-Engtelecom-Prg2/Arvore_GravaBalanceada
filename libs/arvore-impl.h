/* 
 * File:   arvore-impl.h
 * Author: sobral
 *
 * Created on 8 de Outubro de 2016, 19:37
 */

#ifndef ARVORE_IMPL_H
#define	ARVORE_IMPL_H

#include "arvore.h"
#include <sstream>
#include <ostream>

using std::ostream;
using std::ostringstream;
using std::endl;

namespace prglib {

template <typename T> arvore<T>::~arvore() {    
}
    
template <typename T> arvore<T>::arvore() : BasicTree() {    
}

template <typename T> arvore<T>::arvore(const T & dado) : data(dado),BasicTree((void*)&data) {    
}

template <typename T> arvore<T>::arvore(list<T> &dados): BasicTree((void*)&data) {
    if (dados.empty()) throw -1;
    auto it = dados.begin();
    data = *it;
    for (;it != dados.end(); it++) {
        adiciona(*it);
    }
}

template <typename T> arvore<T>::arvore(istream &inp): BasicTree((void*)&data) {
    inp >> data;
    if (inp.fail()) throw -1;

    T algo;
    while (inp >> algo) adiciona(algo);
}
//template <typename T> arvore<T>::arvore(const arvore<T> & outra) : BasicTree(outra) {}

template <typename T> BasicTree * arvore<T>::create(void * p_dado) {
    T * o = (T*)p_dado;
    arvore<T> * ptr = new arvore<T>(*o);
    return (BasicTree*) ptr;
}

template <typename T> void arvore<T>::adiciona(const T & algo) {
    BasicTree::adiciona((void*)&algo);
}

template <typename T> const T& arvore<T>::obtem(const T & algo) const {
    T * o = (T*)BasicTree::obtem((void*)&algo);
    return *o;
}

template <typename T> const T& arvore<T>::obtem() const {
    return this->data;
}

template <typename T> arvore<T> * arvore<T>::esquerda() {
    return static_cast<arvore<T>*>(this->esq);
}

template <typename T> arvore<T> * arvore<T>::direita() {
    return static_cast<arvore<T>*>(this->dir);
}

template <typename T> void arvore<T>::listeEmLargura(list<T> & result) {
    list<void*> l;
    
    BasicTree::listeEmLargura(l);
    copia_lista(l , result);
}

template <typename T> void arvore<T>::listeInOrder(list<T> & result) {
    list<void*> l;
    
    BasicTree::listeInOrder(l);
    copia_lista(l , result);
}

template <typename T> void arvore<T>::copia_lista(list<void*> l, list<T> & res) {
    for (auto & x: l) {
        res.push_back(*(T*)x);
    }
}

template <typename T> void arvore<T>::listePreOrder(list<T> & result) {
    list<void*> l;
    
    BasicTree::listePreOrder(l);
    copia_lista(l , result);
}

template <typename T> void arvore<T>::listePostOrder(list<T> & result) {
    list<void*> l;
    
    BasicTree::listePostOrder(l);
    copia_lista(l , result);
}

template <typename T> unsigned int arvore<T>::tamanho() const {
    return BasicTree::tamanho();
}

template <typename T> int arvore<T>::fatorB()  {
    return BasicTree::fatorB();
}

template <typename T> unsigned int arvore<T>::altura()  {
    return BasicTree::altura();
}

template <typename T> arvore<T>* arvore<T>::balanceia() {
    arvore<T> * ptr = (arvore<T>*)BasicTree::balanceia();
    return ptr;
}

template <typename T> arvore<T>* arvore<T>::balanceia(bool otimo) {
    arvore<T> * ptr = (arvore<T>*)BasicTree::balanceia(otimo);
    return ptr;
}

//template <typename T> void arvore<T>::inicia() {
//    BasicTree::inicia();
//}
//
//template <typename T> T& arvore<T>::proximo() {
//    T * ptr = (T*)BasicTree::proximo();
//    return *ptr;
//}
//
//template <typename T> bool arvore<T>::fim() {
//    return BasicTree::fim();
//}

//template <typename T> void arvore<T>::iniciaPeloFim() {
//    BasicTree::rinicia();
//}
//
//template <typename T> T& arvore<T>::anterior() {
//    T * ptr = (T*)BasicTree::rproximo();
//    return *ptr;
//}
//
//template <typename T> bool arvore<T>::inicio() {
//    return BasicTree::rfim();
//}

template <typename T> T& arvore<T>::obtemMenor() const{
    T * ptr = (T*)BasicTree::obtemMenor();
    return *ptr;    
}

template <typename T> T arvore<T>::remove(const T & algo) {
    if (not (esq or dir)) throw -1; // tem apenas raiz
    
    T coisa;
    BasicTree::remove((void*)&algo, (void*)&coisa);
    return coisa;    
}

template <typename T> T& arvore<T>::obtemMaior() const{
    T * ptr = (T*)BasicTree::obtemMaior();
    return *ptr;    
}

template <typename T> void arvore<T>::obtemMenoresQue(list<T> & result, const T & algo) {
    list<void*> l;
    BasicTree::obtemMenoresQue(l, (void*)&algo);
    copia_lista(l , result);
}

template <typename T> void arvore<T>::obtemMaioresQue(list<T> & result, const T & algo) {
    list<void*> l;
    BasicTree::obtemMaioresQue(l, (void*)&algo);
    copia_lista(l , result);
}

template <typename T> void arvore<T>::obtemIntervalo(list<T>& result, const T& start, const T& end) {
    list<void*> l;
    BasicTree::obtemIntervalo(l, (void*)&start, (void*)&end);
    copia_lista(l , result);
}

template <typename T> arvore<T> * arvore<T>::rotacionaL() {
    arvore<T> * ptr = (arvore<T>*)BasicTree::rotacionaL();
    return ptr;
}

template <typename T> arvore<T> * arvore<T>::rotacionaR() {
    arvore<T> * ptr = (arvore<T>*)BasicTree::rotacionaR();
    return ptr;
}

template <typename T> void arvore<T>::atribui(void * p1, void * p2) {
    T * o1 = (T*)p1;
    T * o2 = (T*)p2;
    *o1 = *o2;
}
    // compararação de igualdade
template <typename T> bool arvore<T>::ehIgual(void * p1, void * p2) {
    T * o1 = (T*)p1;
    T * o2 = (T*)p2;
    return *o1 == *o2;
}
    
    // comparação de precedência: *p1 < *p2
template <typename T> bool arvore<T>::ehMenor(void * p1, void * p2) {
    T * o1 = (T*)p1;
    T * o2 = (T*)p2;
    return *o1 < *o2;
}
    // destroi dado
template <typename T> void arvore<T>::destroi(void * p1) {
    T * o1 = (T*)p1;
    delete o1;
}

    template <typename T> void desenha_nodos(arvore<T> * arv, ostream & out) {
        auto raiz = arv->obtem();
        auto esq = arv->esquerda();
        auto dir = arv->direita();

        if (! esq and ! dir) out << raiz << endl;
        else {
            if (esq) {
                out << raiz << " -- " << esq->obtem() << endl;
                if (esq->altura()) desenha_nodos(esq, out);
            }
            if (dir) {
                out << raiz << " -- " << dir->obtem() << endl;
                if (dir->altura()) desenha_nodos(dir, out);
            }
        }

    }

    template <typename T> string desenha_arvore(arvore<T> * arv) {
        ostringstream out;

        out << "strict graph {" << endl;
        desenha_nodos(arv, out);
        out << "}" << endl;

        return out.str();
    }

    template<typename T> typename arvore<T>::preorder_iterator arvore<T>::preorder_begin() {
        return preorder_iterator(this);
    }

    template<typename T> typename arvore<T>::preorder_iterator arvore<T>::preorder_end() const {
        return preorder_iterator();
    }

    template<typename T> typename arvore<T>::inorder_iterator arvore<T>::inorder_begin() {
        return inorder_iterator(this);
    }

    template<typename T> typename arvore<T>::inorder_iterator arvore<T>::inorder_end() const {
        return inorder_iterator();
    }

    template<typename T> typename arvore<T>::preorder_riterator arvore<T>::preorder_rbegin() {
        return preorder_riterator(this);
    }

    template<typename T> typename arvore<T>::preorder_riterator arvore<T>::preorder_rend() const {
        return preorder_riterator();
    }

    template<typename T> typename arvore<T>::inorder_riterator arvore<T>::inorder_rbegin() {
        return inorder_riterator(this);
    }

    template<typename T> typename arvore<T>::inorder_riterator arvore<T>::inorder_rend() const {
        return inorder_riterator();
    }

    template<typename T>
    arvore<T>::preorder_iterator::preorder_iterator() {

    }

    template<typename T>
    arvore<T>::preorder_iterator::preorder_iterator(const arvore::preorder_iterator &it) {
        p = it.p;
    }

    template<typename T>
    arvore<T>::preorder_iterator::preorder_iterator(arvore<T> *raiz) {
        p.push(raiz);
    }

    template<typename T>
    bool arvore<T>::preorder_iterator::operator==(const arvore::preorder_iterator &it) const {
        return p == it.p;
    }

    template<typename T>
    bool arvore<T>::preorder_iterator::operator!=(const arvore::preorder_iterator &it) const {
        return p != it.p;
    }

    template<typename T>
    const T &arvore<T>::preorder_iterator::operator*() const {
        if (p.empty()) throw -1; // a meu critério ???
        auto ptr = p.top();
        return ptr->obtem();
    }

    template<typename T>
    typename arvore<T>::preorder_iterator &arvore<T>::preorder_iterator::operator++() {
        if (! p.empty()) {
            auto ptr = p.top();
            p.pop();
            if (ptr->direita() != nullptr) p.push(ptr->direita());
            if (ptr->esquerda() != nullptr) p.push(ptr->esquerda());
        }
        return *this;
    }

    template<typename T>
    typename arvore<T>::preorder_iterator &arvore<T>::preorder_iterator::operator++(int) {
        return ++(*this);
    }

    template<typename T>
    arvore<T>::preorder_riterator::preorder_riterator() {

    }

    template<typename T>
    arvore<T>::preorder_riterator::preorder_riterator(const arvore::preorder_riterator &it):preorder_iterator(it) {
    }

    template<typename T>
    arvore<T>::preorder_riterator::preorder_riterator(arvore<T> *raiz): preorder_iterator(raiz) {
    }

    template<typename T>
    typename arvore<T>::preorder_riterator &arvore<T>::preorder_riterator::operator++() {
        auto & p = this->p;

        if (! p.empty()) {
            auto ptr = p.top();
            p.pop();
            if (ptr->esquerda() != nullptr) p.push(ptr->esquerda());
            if (ptr->direita() != nullptr) p.push(ptr->direita());
        }
        return *this;
    }

    template<typename T>
    typename arvore<T>::preorder_riterator &arvore<T>::preorder_riterator::operator++(int) {
        return ++(*this);
    }

    template<typename T>
    arvore<T>::inorder_iterator::inorder_iterator(): arvore<T>::preorder_iterator() {

    }

    template<typename T>
    arvore<T>::inorder_iterator::inorder_iterator(const arvore::inorder_iterator &it): arvore<T>::preorder_iterator(it) {
    }

    template<typename T>
    arvore<T>::inorder_iterator::inorder_iterator(arvore<T> *raiz) {
        for (auto ptr = raiz; ptr != nullptr; ptr=ptr->esquerda()) {
            this->p.push(ptr);
        }
    }

    template<typename T>
    typename arvore<T>::inorder_iterator &arvore<T>::inorder_iterator::operator++() {
        if (! this->p.empty()) {
            auto ptr = this->p.top();
            this->p.pop();
            for (ptr = ptr->direita(); ptr != nullptr; ptr=ptr->esquerda()) {
                this->p.push(ptr);
            }
        }
        return *this;
    }

    template<typename T>
    typename arvore<T>::inorder_iterator &arvore<T>::inorder_iterator::operator++(int) {
        return ++(*this);
    }

    template<typename T>
    arvore<T>::inorder_riterator::inorder_riterator(): arvore<T>::preorder_iterator() {

    }

    template<typename T>
    arvore<T>::inorder_riterator::inorder_riterator(const arvore::inorder_riterator &it): arvore<T>::preorder_iterator(it) {
    }

    template<typename T>
    arvore<T>::inorder_riterator::inorder_riterator(arvore<T> *raiz) {
        for (auto ptr = raiz; ptr != nullptr; ptr=ptr->direita()) {
            this->p.push(ptr);
        }
    }

    template<typename T>
    typename arvore<T>::inorder_riterator &arvore<T>::inorder_riterator::operator++() {
        if (! this->p.empty()) {
            auto ptr = this->p.top();
            this->p.pop();
            for (ptr = ptr->esquerda(); ptr != nullptr; ptr=ptr->direita()) {
                this->p.push(ptr);
            }
        }
        return *this;
    }

    template<typename T>
    typename arvore<T>::inorder_riterator &arvore<T>::inorder_riterator::operator++(int) {
        return ++(*this);
    }

};

#endif	/* ARVORE_IMPL_H */

