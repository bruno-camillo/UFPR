module Primo where

cont :: [a] -> Int
cont [] = 0
cont (h:t) = 1 + cont t 


ehPrimo :: Int -> Bool
ehPrimo n =
    if numDivisores == 2 
        then True
        else False
    where   
        numDivisores = cont [x | x <- [1..n], mod n x == 0]

-- contar a quantidade de pares e impares
contar :: [Int] -> (Int, Int)
contar [] = (0, 0)
contar (h:t)
    | mod h 2 == 0 = (pares + 1, impares)
    | otherwise = (pares, impares + 1)
    where
        (pares, impares) = contar t

notaAluno :: (String, Float) -> Bool
notaAluno (nome, nota) 
    | nota > 7 = True
    | otherwise = False

tamSalario :: (String, Float) -> Bool
tamSalario (nome, sal) 
    | sal < 10000 = True
    | otherwise = False

filtra :: ((String, Float) -> Bool) -> [(String, Float)] -> [(String, Float)] 
filtra _ [] = []
filtra func (h:t)
    | func h = h : filtra func t
    | otherwise = filtra func t