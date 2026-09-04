module Lista4-1 where

type Tupla = (String, String, Char)

-- Retorna o primeiro elemento da tupla
primEle :: Tupla -> String
primEle (x, _, _) = x

-- Retorna o segundo elemento da tupla
secEle :: Tupla -> String
secEle (_, x, _) = x

-- Retorna o terceiro elemento da tupla
tercEle :: Tupla -> Char
tercEle (_, _, x) = x

-- Base de dados para o exercicio
base :: Int -> (String, String, Char)
base x
    |x == 1 = ("joao", "mestre", 'm')
    |x == 2 = ("jonas", "doutor", 'm')
    |x == 3 = ("joice", "mestre", 'f')
    |x == 4 = ("janete", "doutor", 'f')
    |x == 5 = ("jocileide", "doutor", 'f')
    |otherwise = ("ninguem","", 'x')

-- Função recursiva que conta o numero de mestres da base
contMestre :: Int
contMestre = aux 1
    where aux x 
            | x > 5 = 0
            | secEle(base(x)) == "mestre" = 1 + aux(x + 1)
            | otherwise = aux(x + 1)

-- Função recursiva que conta o numero de doutores da base
contDoc :: Int
contDoc = aux 1
    where aux x
            | x > 5 = 0
            | secEle(base(x)) == "doutor" = 1 + aux(x + 1)
            | otherwise = aux(x + 1) 

-- Função retorna o numero de doutores ou mestres, definido pelo usuario
contMD :: String -> Int
contMD t 
    | t == "mestre" = contMestre
    | t == "doutor" = contDoc
    | otherwise = 0

-- Função que retorna o numero de pessoas determinado pelo titulo e genero definido pelo usuario
cont :: String -> Char -> Int
cont t g = aux 1 t g 
    where 
        aux x t g 
            | x > 5 = 0
            | titulo x && genero x = 1 + aux (x+1) t g
            | otherwise = aux (x+1) t g 
            
        titulo x = secEle(base(x)) == t
        genero x = tercEle(base(x)) == g

type Nome = String
type Titulo = String
type Genero = Char
type Pesquisador = (Nome, Titulo, Genero)
type Grupo = [Pesquisador]

-- Função recursiva que cria uma lista de pesquisadores da funçao base
pesquisadores :: Grupo
pesquisadores = aux 1
    where 
        aux x 
            | x > 5 = []
            | otherwise = base x : aux (x + 1)

-- Função que gera uma lista com os nomes dos doutores da função base
geraDoc :: Grupo -> [Nome]
geraDoc lista = [n | (n, t, g) <- lista, t == "doutor"]

