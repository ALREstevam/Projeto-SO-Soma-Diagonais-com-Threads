#Projeto soma das diagonais principais de uma matriz - disciplina de Sistemas operacionais

Programa desenvolvido em **Linguagem C** utilizando da biblioteca **pthreads** para resolver o problema de soma das diagonais principais de uma matriz:

> Criação de um programa que utilize de múltiplas threads para calcular a soma dos elementos das diagonais principais de uma matriz M por N utilizando a biblioteca POSIX Threads.
> Cada diagonal deve ser calculada por apenas uma thread. Ao término da soma a thread deve armazenar o resultado num vetor e procurar outra diagonal para processar.
>Obs: todos os vetores e matrizes devem ser armazenados utilizando de alocação dinâmica.

## Observações
* Arquivo executável pode ser gerado pelo comando make e executado com o comando ./projso.o. 
* Os valores a inserir na matriz devem estar no arquivo: in.txt. 
* Os valores de saída serão escritos nos arquivos: out_sol_A.txt e out_sol_B.txt. 
* As dimensões M e N da matriz e a quantidade de threads T devem ser inseridos pelo usuário pelo terminal. 
* Para sair do programa insira 0 em todas as entradas do terminal.
