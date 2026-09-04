module PraticaCuringas where 

func :: (Int, (Int,Int)) -> Int
func z = 
    if fst z == 1
    then fst (snd z) + snd (snd z)
    else if fst z == 2
        then fst (snd z) - snd (snd z)
        else 0

func2 :: (Int, (Int,Int)) -> Int
func2 (1, (f,s)) = f + s
func2 (2, (f,s)) = f - s
func2 (_, (_,_)) = 0

temElem :: [a] -> Bool
temElem [] = False
temElem (_:t) = True