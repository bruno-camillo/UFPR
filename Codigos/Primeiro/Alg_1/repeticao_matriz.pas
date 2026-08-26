program repeticao_matriz;

type matriz = array [1..100,1..100] of longint;

var m, n : longint;
	mat : matriz;

(*procedimento que le os elementos da matriz*)
procedure le_matriz (var mat : matriz; m, n : longint);
var i, j : longint;

begin
	for i := 1 to m do
		for j := 1 to n do
			read ( mat[i,j] ); (*le o elemento da linha i e coluna j*)
end;

(*funcao que busca um elemento numa matriz*)
function busca_na_matriz (var mat : matriz; elemento, m, n : longint): boolean;
var i, j, k : longint;

begin
	busca_na_matriz := false;
	k := 0; (*variavel que conta quantas vezes um elemento aparece na matriz*)
	(*laco que percorre todas as linhas e colunas da matriz, procurando o elemento desejado, e para caso encontrar*)
	i := 1;
	while (k <= 1) and (i <= m) do  
		begin
			j := 1;
			while (k <= 1) and (j <= n) do
				begin
					if mat [i,j] = elemento then  
						k := k + 1;
					j := j + 1;
				end;
			i := i + 1;
		end;
	if k > 1 then
		busca_na_matriz := true;
end;

(*funcao que verifica se existem elementos repetidos na matriz*)
function ha_elementos_repetidos (var mat : matriz; m, n : longint): boolean;
var elemento, lin, col : longint;

begin
	ha_elementos_repetidos := false;
	lin := 1; (*linha do elemento a ser encontrado*)
	col := 1; (*coluna do elemento a ser encontrado*)
	elemento := mat[lin,col]; 
	while (not ha_elementos_repetidos) and ( (lin <= m) and (col <= n) ) do 
		begin
			if busca_na_matriz (mat, elemento, m, n)then
				ha_elementos_repetidos := true
			else
				begin
					if col = n then (*se a coluna do elemento for a ultima, entao o proximo elemento sera o primeiro da proxima linha*)
						begin
							col := 1;
							lin := lin + 1;
						end
					else
						col := col + 1; (*se o elemento nao estiver na ultima coluna, mantem-se a linha e avanca uma coluna*)
					elemento := mat[lin,col];
				end;
		end;
			
end;

(*Programa principal*)
begin
	read (m, n);
	le_matriz (mat, m, n);
	if ha_elementos_repetidos (mat, m, n) then
		writeln ('sim')
	else
		writeln ('nao');
end.
