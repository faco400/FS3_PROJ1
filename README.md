# FS3_PROJ1

## OBJETIVO

Repositório dedicado ao desenvolvimento do [projeto 1 de FSE - UnB/2021.2](https://gitlab.com/fse_fga/trabalhos-2021_2/trabalho-1-2021-2)

## COMPILÇÃO
Para compilar o projeto basta executar o comando abaixo enquanto na raiz do projeto:

```terminal
make
```

## EXECUÇÃO
Para executar o projeto, após a compilação executar o comando abaixo na raiz do projeto:

```terminal
./bin/bin
```

## USO
O usuário poderá escolher entre 3 opções para controlar o programa. 
- Pelo terminal onde poderá definir uma temperatura de referência (TR). 

- Através do Potênciometro externo.

- Através da leitura do arquivo de curva-reflow.cvs que contém tempo(em segundos) e temperatura de referência a serem utiliadas.

## OBSERVAÇÕES
- Até o momento a opção de de controlar o programa através do arquivo curva_reflow.csv não foi implementado.

- Se está utilizando valores padrões para as constantes kp, ki e kd no cálculo do sinal de controle PID (kp = 20.0, ki = 0.1 e kd = 100)
