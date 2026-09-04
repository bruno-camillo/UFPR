module Aula3 where

-- Gera uma lista dos pares de 0 a 20
numPares :: [Int]
numPares = [2*x | x <- [0..10]]

-- Gera uma lista de numeros pares a partir de uma lista qualquer
numPares2 :: [Int] -> [Int]
numPares2 lista = [2*x | x <- lista]

-- Gera uma lista de quadrados dos numeros impares de uma lista qualquer
numQuadImp :: [Int] -> [Int]
numQuadImp lista = [x^2 | x <- lista, mod x 2 /= 0]

-- "type" é um apelido para o tipo, e nao um tipo novo
type Nome = String
type Media = Int
type Aluno = (Nome, Media)
type Turma = [Aluno]

-- Gera uma lista de aprovados de uma lista Turma qualquer
-- Turma eh uma lista de alunos, que sao uma tupla de string e int
-- Os nomes das "Variaveis" nao pode ser igual a declaração do type
aprovados :: Turma -> Int -> [Nome]
aprovados tma nota = [ n | (n, m) <- tma, m >= nota]

-- Retorna um numero qualquer ao cubo
cubo :: Int -> Int
cubo x = x^3

-- Retorna uma lista dos cubos de uma lista qualquer 
-- Versao recursiva
aoCubo :: [Int] -> [Int]
aoCubo [] = []
aoCubo (h:t) = cubo h : aoCubo t

-- Função recursiva que soma os elementos de uma lista qualquer
somaLista :: [Int] -> Int
somaLista [] = 0
somaLista (h:t) = h + somaLista t

-- Função recursiva que remove os numeros pares de uma lista qualquer
rmPar :: [Int] -> [Int]
rmPar [] = []
rmPar (h:t) = 
    if mod h 2 == 0
        then rmPar t 
        else h : rmPar t

-- Função recursiva que inverte os elementos de uma lista qualquer de reais
invLista :: [Float] -> [Float]
invLista [] = []
invLista (h:t) = invLista t ++ [h]

-- Função recursiva que filtra os nomes que começam com a letra A de uma lista qualquer
filtraLista :: [String] -> [String]
filtraLista [] = []
filtraLista (h:t) = 
    if head h == 'A'
        then h : filtraLista t
        else filtraLista t

-- Gera uma lista dos primeiros seis multiplos de 3 
multTres :: [Int]
multTres = [ 3*x | x <- [0..5]]

-- Gera uma lista de listas 
listaLista :: [[Int]]
listaLista = [[x] | x <- [1..5]]

type Multiplos = (Int, Int, Int, Int)
-- Função que recebe um inteiro e retorna uma tupla contendo o dobro, triplo, quadruplo e quintuplo
multTupla :: Int -> Multiplos
multTupla x = (2*x, 3*x, 4*x, 5*x)

-- Função que recebe um inteiro e retorna uma tupla contendo o resultado da sua divisao inteira
-- E uma string que indica se eh par ou impar
divTupla :: Int -> (Int, String)
divTupla x = 
    if mod x 2 == 0
        then (div x 2,"Par")
        else (div x 2,"Impar")

type TipoLocal = String 
type Avaliacao = Int
type NomeLocal = String
type PontoTuristico = (NomeLocal, Avaliacao, TipoLocal)

-- Gera uma lista de pontos turisticos que possuem uma avaliação maior que uma nota qualquer de 0 a 10
-- a partir de uma lista de PontoTuristico
pontosTuristicos :: Int -> [PontoTuristico] -> [(NomeLocal, Avaliacao)]
pontosTuristicos valor lista = [(nome,nota) | (nome,nota, _) <- lista, nota > valor]