program permutacao_matriz;

type matriz = array [1..100,1..100] of longint;

var mat : matriz;
	n : longint;
	
(*Procedimento que le os valores dos elementos da matriz*)	
procedure le_matriz (var mat : matriz; n : longint);
var i, j : longint;

begin
	for i := 1 to n do
		for j := 1 to n do
			read ( mat[i,j] );
end;	

(*Funcao que verifica todas as linhas da matriz para a condicao de ser de permutacao ou nao*)
function eh_permutacao_linha (var mat: matriz; n : longint): boolean;
var i, j, nulos, um: longint;

begin
	i := 1;
	eh_permutacao_linha := true;
	(*Enquanto a funcao eh verdadeira, o laco continua verificando se a matriz eh de permutacao,
	  aumentando as linhas*)
	while eh_permutacao_linha and (i <= n) do
		begin
			j := 1;
			nulos := 0;
			um := 0;
			(*Laco que verifica as colunas de linha 'i'*)
			while eh_permutacao_linha and (j <= n) do
				begin
					(*Se o elemento for 0, entao eh adicionado ao contador 'nulo'*)
					if mat [i,j] = 0 then      
						nulos := nulos + 1 
					else
						(*Se o elemento for 1, entao eh adicionado ao contador 'um'*)
						if mat [i,j] = 1 then
							um := um + 1
					else
						(*Em qualquer outro caso, a funcao ja encerra, considerando a
						matriz como nao sendo permutada*)
						eh_permutacao_linha := false;
					(*Se uma linha for nula, a matriz nao eh permutada*)
					if nulos = n then
						eh_permutacao_linha := false;
					(*Se houver mais de um elemento 1, a matriz nao eh permutada*)
					if um > 1 then
						eh_permutacao_linha := false;
					j := j + 1;
				end;
			i := i + 1;
		end;
end;

(*Funcao que verifica todas as colunas da matriz para a condicao de ser de permutacao ou nao*)
function eh_permutacao_coluna (var mat: matriz; n : longint): boolean;
var i, j, nulos, um: longint;

begin
	j := 1;
	eh_permutacao_coluna := true;
	(*Enquanto a funcao eh verdadeira, o laco continua verificando se a matriz eh de permutacao,
	  aumentando as linhas*)
	while eh_permutacao_coluna and (j <= n) do
		begin
			i := 1;
			nulos := 0;
			um := 0;
			(*Laco que verifica as colunas de linha 'i'*)
			while eh_permutacao_coluna and (i <= n) do
				begin
					(*Se o elemento for 0, entao eh adicionado ao contador 'nulo'*)
					if mat [i,j] = 0 then      
						nulos := nulos + 1 
					else
						(*Se o elemento for 1, entao eh adicionado ao contador 'um'*)
						if mat [i,j] = 1 then
							um := um + 1
					else
						(*Em qualquer outro caso, a funcao ja encerra, considerando a
						matriz como nao sendo permutada*)
						eh_permutacao_coluna := false;
					(*Se uma linha for nula, a matriz nao eh permutada*)
					if nulos = n then
						eh_permutacao_coluna := false;
					(*Se houver mais de um elemento 1, a matriz nao eh permutada*)
					if um > 1 then
						eh_permutacao_coluna := false;
					i := i + 1;
				end;
			j := j + 1;
		end;
end;
	
(*Funcao que verifica se a matriz eh de permutacao ou nao*)
function eh_permutacao (var mat: matriz; n : longint): boolean;	

begin
	if (eh_permutacao_linha(mat, n)) and (eh_permutacao_coluna(mat, n)) then
		eh_permutacao := true
	else
		eh_permutacao := false;
end;	

(*Programa Principal*)
begin
	read (n);
	le_matriz (mat, n);
	(*verifica se a matriz eh de permutacao*)
	if eh_permutacao (mat, n) then
		writeln ('sim')
	else
		writeln ('nao');
end.
