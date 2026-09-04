module Main where 

import Tratamento
import Funcoes

main :: IO()
main = do 
    let numeros = [1, 2 , -3, -4, 0, 12, 0 ,-11]
    let nomes = ["Bruno", "Joao", "Marcelo"]

    print(filtraNum ehPositivo numeros)

    print(filtraNum ehNegativo numeros)

    print(filtraNum ehZero numeros)

    print(mapNomes senhor nomes)