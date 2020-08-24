Escreva uma função que leia um arquivo que contém palavras, as quais podem estar em uma ordem qualquer. Sua função deve então reescrever esse arquivo, gravando de volta as palavras numa ordem tal que uma árvore de pesquisa binária criada a partir de seu conteúdo já estará balanceada de forma ótima. Essa função está declarada assim em questao4.h:

```c++
void reordena(const string & nome_arquivo);
```

Caso o arquivo seja inválido, sua função deve gerar uma exceção.