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
        else "nao"
            --if num < 0 
           -- then "Numero eh negativo!" 
           -- else "Numero eh zero!"
               
            
        