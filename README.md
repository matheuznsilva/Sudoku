# SUDOKU EM C

Este repositorio possui o trabalho prático da disciplina de Algoritmo e estrutura de dados no curso de Ciência da Computação na UFSJ de 2017.

## Requisitos

<div>
  <img src="https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&amp;logo=C&amp;logoColor=white" alt="C">
  <img src="https://img.shields.io/badge/Gcc-323330?style=for-the-badge&amp;logo=Gcc&amp;logoColor=white" alt="GCC">
</div>

## Instalação

Todas as instalações abaixo são referentes ao Ubuntu

### Install GCC

O GCC geralmente já está instalado no Ubuntu, mas você pode verificar a versão digitando:

     $ gcc --version

Se não estiver instalado, você pode instalar usando o apt:

     $ sudo apt update
     $ sudo apt install build-essential

## Uso

Entre no diretorio via terminal

    $ cd Sudoku/

E depois execute os seguintes comandos:

    $ make
    $ ./main

## Instruções

Para jogar é necessario escolher um modo de jogo: **Pre-definido ou Carregar jogo**

**pré-definido:** 
A aplicação sorteia um quebra-cabeças aleatorio.

**Carregar jogo**
O jogador deve inserir um quebra-cabeças (formato .txt) na pasta do jogo com o nome "meu_jogo.txt".

Apos escolher o modo de jogo será solicitado que o jogador escolha um nivel de dificuldade.

Para preencher cada célula do quebra-cabeças deve-se colocar as coordenadas da celula (de A a I), Linha e depois Coluna, 
logo após será solicitado que digite o valor para preenchimento da célula.

## Status do Projeto

**Status do Projeto: Concluído**

O projeto está concluido.

**Conquistas Atuais:**
- Funcionalidades básicas implementadas com sucesso.
- Interface do usuário (UI) está operacional.

**Próximos Passos:**
- Realizar correções de bugs.
- Implementar recursos adicionais.
- Refatorar código para aumentar a eficiência e manutenibilidade.