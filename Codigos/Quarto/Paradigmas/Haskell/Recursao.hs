module Recursao where

-- Função recursiva de fibonacci, retorna o n-esimo elemento da sequencia
fibonacci :: Int -> Int
fibonacci n 
    | n == 0 = 0
    | n == 1 = 1
    | otherwise = fibonacci (n - 1) + fibonacci (n - 2)

-- Função que conta o numero de digitos de um inteiro
digitos :: Int -> Int
digitos n 
    | div n 10 == 0 = 1 
    | otherwise = 1 + digitos (div n 10) 

-- Função que soma os digitos de um inteiro
somaDigitos :: Int -> Int 
somaDigitos n 
    | n == 0 = 0
    | otherwise = mod n 10 + somaDigitos (div n 10)