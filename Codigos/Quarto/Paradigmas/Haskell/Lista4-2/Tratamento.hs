module Tratamento where

type Nome = String

-- Funções que adicionam o termo de tratamento no inicio -- 

senhor :: Nome -> Nome 
senhor n = "Sr." ++ n 

senhora :: Nome -> Nome 
senhora n = "Sra." ++ n 

senhorita :: Nome -> Nome 
senhorita n = "Srta." ++ n 

-----------------------------------------------------------

-- Função recursiva que aplica o pronome de tratamento a todos os nomes da lista, ambos definidos pelo usuario
mapNomes :: (Nome -> Nome) -> [Nome] ->  [Nome]
mapNomes _ [] = []
mapNomes f (h:t) = (f h) : (mapNomes f t) 

