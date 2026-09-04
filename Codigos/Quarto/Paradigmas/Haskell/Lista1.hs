module Lista1 where 

--Calcula o reajuste de um salario 
reajuste :: Float -> Float
reajuste salario = salario * 1.5
    
-- Calcula a media ponderada de 3 notas e seus respectivos pesos
mediapond :: Float -> Float -> Float -> Float -> Float -> Float -> Float
mediapond n1 n2 n3 p1 p2 p3 = (n1 * p1 + n2 * p2 + n3 * p3) / (p1 + p2 + p3) 

-- Converte a temperatura de Celsius para Fahrenheit
convTemp :: Float -> Float 
convTemp temp = temp * (9/5) + 32

-- Calcula a idade de uma pessoa em 2032
calId :: Int -> Int
calId ano = 2032 - ano 

-- Calcula os minutos de um horario formado por hora e minutos
calMin :: Float -> Float
calMin hora = hora * 60

-- Retorna a soma dos quadrados de tres valores
calQuad :: Float -> Float -> Float -> Float
calQuad n1 n2 n3 = n1 **2 + n2 **2 + n3 **2

-- Verifica se um numero eh impar
ehImpar :: Int -> Bool
ehImpar num =
    if mod num 2 /= 0
        then True
        else False

-- Verifica se um numero eh par
ehPar :: Int -> Bool
ehPar num =
    if even num 
        then True
        else False

-- Verifica se um numero eh divisivel pelo outro
ehDiv :: Int -> Int -> Bool
ehDiv n1 n2 =
    if mod n1 n2 == 0 
        then True
        else False

-- Calcula o salario que um funcionario vai receber com 7% de imposto e 5% de gratificaçao
salario :: Float -> Float
salario sal = sal - sal * 0.02