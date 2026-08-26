module Lista2 where

-- Verifica se a idade da pessoa eh maior ou igual a 18
permiteId :: Int -> String
permiteId idade = 
    if idade >= 18
        then "Permitido"
        else "Negado"

gPermite :: Int -> String
gPermite idade 
    | idade >= 18 = "Permitido"
    | idade < 18 = "Negado"

-- Verifica o sinal do numero
sinal :: Float -> String
sinal num =
    if num > 0 
        then "Positivo"
        else if num < 0
            then "Negativo"
            else "Zero"

gSinal :: Float -> String
gSinal num 
    | num > 0 = "Positivo"
    | num < 0 = "Negativo"
    | num == 0 = "Zero"

-- Verifica se um ano eh bissexto
bissexto :: Int -> String
bissexto ano = 
    if mod ano 400 == 0 || (mod ano 4 == 0 && mod ano 100 /= 0) 
        then "Eh bissexto"
        else "Nao eh Bissexto"

bi :: Int -> String
bi ano = 
    if div400 || (div4 && not div100)
        then "Eh bissexto"
        else "Nao eh Bissexto"
    where
        div100 = mod ano 100 == 0
        div4 = mod ano 4 == 0
        div400 = mod ano 400 == 0