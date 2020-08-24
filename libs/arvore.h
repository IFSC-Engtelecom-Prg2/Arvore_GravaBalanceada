/* 
 * File:   arvore.h
 * Author: msobral
 *
 * Created on 12 de Agosto de 2016, 13:12
 */

#ifndef ARVORE_H
#define	ARVORE_H

#include <libs/BasicTree.h>
#include <list>
#include <istream>
#include <string>
#include <iterator>
#include <stack>
#include <queue>

using std::string;
using std::istream;
using std::list;
using std::forward_iterator_tag;
using std::stack;
using std::queue;

namespace prglib {
    
template <typename T> class arvore : private BasicTree{
 public:
  arvore();
  //arvore(const arvore<T> & outra);
  arvore(const T & dado);
  arvore(list<T> & dados);
  arvore(istream & inp);

  virtual ~arvore();

  // adiciona um dado à árvore
  void adiciona(const T& algo);

  // obtém um dado da árvore
  const T& obtem(const T & algo) const;

  // obtém o valor da raiz da árvore
  const T& obtem() const ;

    // iteradores PRE-ORDER e IN-ORDER
    class preorder_iterator;
    class inorder_iterator;
    class preorder_riterator;
    class inorder_riterator;

    // iteradores default: inorder
    inorder_iterator begin() { return inorder_begin(); }
    inorder_iterator end() const { return inorder_end(); }

    // iteradores diretos ...
    preorder_iterator preorder_begin();
    preorder_iterator preorder_end() const;
    inorder_iterator inorder_begin();
    inorder_iterator inorder_end() const;
    // iteradores reversos ...
    preorder_riterator preorder_rbegin();
    preorder_riterator preorder_rend() const;
    inorder_riterator inorder_rbegin();
    inorder_riterator inorder_rend() const;


  // Versão alternativa: enumera os dados in-order, pre-order, post-order e breadth-first
  // copiando-os para uma lista
  void listeInOrder(list<T> & result);
  void listePreOrder(list<T> & result);
  void listePostOrder(list<T> & result);
  void listeEmLargura(list<T> & result);

  // retorna a quantidade de dados na árvore
  unsigned int tamanho() const;

  // retorna a subárvore esquerda
  arvore<T> * esquerda();

  // retorna a subárvore direita
  arvore<T> * direita();

  // itera a árvore de forma reversa
//  void iniciaPeloFim();
//  bool inicio();
//  T& anterior();

  // remove um dado
  T remove(const T & algo);

  // retorna o menor dado
  T & obtemMenor() const;

  // retorna o maior dado
  T & obtemMaior() const;

  // copia na lista "result" os dados menores que "algo"
  void obtemMenoresQue(list<T> & result, const T & algo);

  // copia na lista "result" os dados maiores que "algo"
  void obtemMaioresQue(list<T> & result, const T & algo);
  
  // obtém todos valores entre "start" e "end" (inclusive)
  void obtemIntervalo(list<T> & result, const T & start, const T & end);

    // retorna a altura da folha mais distante da raiz
    unsigned int altura() ;

    // retorna o fator de balanceamento
    int fatorB() ;

    // balanceia a árvore
    arvore<T> * balanceia();

    // balanceia a árvore repetidamente, até que a altura não mais se reduza
    arvore<T> * balanceia(bool otimo);

 protected:
     T data;
     
    // atribuição: *p1 <- *p2
    virtual void atribui(void * p1, void * p2);
    // compararação de igualdade
    virtual bool ehIgual(void * p1, void * p2);
    // comparação de precedência: *p1 < *p2
    virtual bool ehMenor(void * p1, void * p2);
    // destroi dado
    virtual void destroi(void * p1);
    
    virtual BasicTree * create(void * p_dado);

    void copia_lista(list<void*> l, list<T> & res);
    
  arvore<T> * rotacionaL();
  arvore<T> * rotacionaR();

public:
    class preorder_iterator: public forward_iterator_tag {
    public:
        preorder_iterator();
        preorder_iterator(const preorder_iterator & it);
        preorder_iterator(arvore<T> * raiz);
        ~preorder_iterator() {}

        bool operator==(const preorder_iterator & it) const;
        bool operator!=(const preorder_iterator & it) const;
        const T& operator*() const;
        virtual preorder_iterator& operator++();
        virtual preorder_iterator& operator++(int);
    protected:
        stack<arvore<T>*> p;
    };

    class inorder_iterator: public preorder_iterator {
    public:
        inorder_iterator();
        inorder_iterator(const inorder_iterator & it);
        inorder_iterator(arvore<T> * raiz);
        ~inorder_iterator() {}

        virtual inorder_iterator& operator++();
        inorder_iterator& operator++(int);
    };

    class preorder_riterator: public preorder_iterator {
    public:
        preorder_riterator();
        preorder_riterator(const preorder_riterator & it);
        preorder_riterator(arvore<T> * raiz);
        ~preorder_riterator() {}

        virtual preorder_riterator& operator++();
        preorder_riterator& operator++(int);
    };

    class inorder_riterator: public preorder_iterator {
    public:
        inorder_riterator();
        inorder_riterator(const inorder_riterator & it);
        inorder_riterator(arvore<T> * raiz);
        ~inorder_riterator() {}

        virtual inorder_riterator& operator++();
        inorder_riterator& operator++(int);
    };


};



// gera uma descrição de um diagrama DOT para a árvore
// O resultado deve ser gravado em arquivo para se gerar o diagrama
// com o programa "dot" ou "dotty"
template <typename T> string desenha_arvore(arvore<T> * arv);

} // fim do namespace

#include <libs/arvore-impl.h>

#endif	/* ARVORE_H */

