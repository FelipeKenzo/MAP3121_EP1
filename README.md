# MAP3121_EP1

Exercício-programa da disciplina MAP3121 - Métodos numéricos e aplicações.

O enunciado pode ser obtido [neste link](https://www.ime.usp.br/~map3121/2019/map3121/programas/EP1-MachineLearning_v2.pdf).

## Compilação

O programa foi compilado com o gcc 7.4.0, em um ambiente Linux (Ubuntu 18.04). Basta utilizar o arquivo `Makefile`, por meio do comando `make`, ou então rodar o comando dentro da pasta raiz do projeto:
```
g++ -Wall -Wextra -O4 -std=c++11 -Iinclude -Llib src/MatrixOp.cpp src/Classificator.cpp src/Matrix.cpp src/Tester.cpp src/main.cpp -o bin/map3121_ep1  -lpthread
```


## Rodando o EP

Para rodar o EP, basta abrir o executável (`bin/./map3121_ep1`). Por *default*, o programa roda as três atividades e, na atividade principal, solicita que o usuário digite os parâmetros `n_digTreino`, `n_digTeste` e `p`, que correspondem a , respectivamente, o número de dígitos a serem utilizados para a fase de treinamento dos classificadores, a serem classificados e a dimensão interna da fatoração por matrizes não-negativas (ou o número de colunas das matrizes Wd).

Algumas *flags* foram implementadas por motivo de conveniência. São elas: 
```
  -nt                     - Recebe como parâmetro o n_digTreino.
  -nc                     - Recebe como parâmetro o n_digTeste.
  -p                      - Recebe como parâmetro o p.
                            Cada flag de parâmetro utilizada pula a entrada de dados correspondente em runtime.
                          
  -a                      - Recebe como parâmetro o número da atividade (1, 2 ou 3)
                            Utilizar para rodar apenas *uma* atividade!
                            
  -mt, -multithreading    - Ativa computação paralela na fase de treinamento.
```
### Exemplo de uso:

 - `bin/./map3121_ep1 -nt 1000 -nc 10000 -p 15 -mt` -> Irá executar as três atividades, utilizando 1000 dígitos na fase de treino, 10000 dígitos na fase de classificação, dimensão p igual a 15, e utilizará computação em paralelo.

 - `bin/./map3121_ep1 -a 3` -> Irá executar apenas a tarefa principal, porém solicitará que o usuário digite os parâmetros em tempo de execução.
 
## Notas sobre a eficiência

Muito provavelmente pela má decisão de projeto de tentar abstrair o EP em classes alocada dinamicamente, a atividade principal demora mais do que o esperado para rodar por completo. A opção de *multi-threading* foi adicionada para mitigar essa ineficiência (e ~~tentar~~ evitar que o monitor que rodar morra de tédio enquanto espera o treinamento). Assim, para:

```
---Hardware:
Processador: i5-6200U(quad-core) @ 2.30GHz
Hd: 5400RPM
Memória: 8Gb DDR3 1333MHz

---Parâmetros:
n_digTreino: 1000
n_digTeste:  10000
p: 15
```

Foram obtidos os seguintes resultados:

| Multi-Threading | Tempo de Execução | Memória consumida |
|:---------------:|:-----------------:|:-----------------:|
|     Ativado     |      160.899s     |       ~500mb      |
|    Desativado   |      340.591s     |       ~50mb       |

