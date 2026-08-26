module Condicionais where 

--Função que verifica a idade e retorna Permitido ou Negado
aprovaIdadeGuard :: Int -> String

aprovaIdadeGuard idade 
    | idade >= 18 = "Permitido"
    | otherwise = "Negado"
    
aprovaIdadeIf :: Int -> String

aprovaIdadeIf idade =
    if idade >= 18
        then "Permitido"
        else "Negado"

--Função que verifica o sinal 
verificaSinalGuard :: Int -> String

verificaSinalGuard num
    | num > 0 = "Numero eh positivo!"
    | num < 0 = "Numero eh negativo!"
    | num == 0 = "Numero eh zero!"

verificaSinalIf :: Int -> String

verificaSinalIf num = 
    if num > 0 
        then "Numero eh positivo!"
        else if num < 0 
            then "Numero eh negativo!"
            else "Numero eh zero!"

--Função que verifica se um ano eh bissexto

verificaBissextoGuard :: Int -> Bool

verificaBissextoGuard ano
    | eh_div400 || eh_div4 && nao_div100 = True
    | otherwise = False
    where   
        eh_div4 = (ano `mod` 4) == 0
        eh_div400 = (ano `mod` 400) == 0
        nao_div100 = (ano `mod` 100) /= 0
