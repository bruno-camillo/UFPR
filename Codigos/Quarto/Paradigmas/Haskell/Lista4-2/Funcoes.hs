module Funcoes where

-- Funçoes que verificam o sinal de um numero, ou se ele eh zero -- 

ehPositivo :: Float -> Bool
ehPositivo x 
    | x > 0 = True
    | otherwise = False

ehNegativo :: Float -> Bool
ehNegativo x 
    | x < 0 = True
    | otherwise = False 

ehZero :: Float -> Bool
ehZero x 
    | x == 0 = True
    | otherwise = False

-------------------------------------------------------------------

-- Função que filtra numa lista um tipo determinado de numero (positivo, negativo ou zero) --
filtraNum :: (Float -> Bool) -> [Float] -> [Float]
filtraNum _ [] = []
filtraNum func (h:t)
    | func h = h : filtraNum func t 
    | otherwise = filtraNum func t