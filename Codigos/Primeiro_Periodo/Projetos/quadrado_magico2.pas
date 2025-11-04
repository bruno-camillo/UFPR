program quadrado_magico2;

const MAX = 100;

type matriz = array [1..MAX,1..MAX] of longint;
	vetor = array [1..MAX] of longint;

var mat : matriz;
	n : longint;

(*procedimento que le a matriz*)
procedure le_matriz (var mat : matriz; n : longint);
var i, j : longint;

begin
	for i := 1 to n do
		for j := 1 to n do
			read (mat[i,j]);
end;

(*procedimento que verifica a soma das linhas*)
procedure soma_linha (var mat : matriz; n : longint; var somaL, tam : longint; var vetor_somas : vetor);
var i, j : longint;

begin 
	for i := 1 to n do
		begin
			somaL := 0;
			for j := 1 to n do
		 		somaL := somaL + mat[i,j];
		 	tam := tam + 1;
		 	vetor_somas[tam] := somaL;
		 end;
end;

(*procedimento que verifica a soma das colunas*)
procedure soma_coluna (var mat : matriz; n : longint; var somaC, tam : longint; var vetor_somas : vetor);
var i, j : longint;

begin 
	for j := 1 to n do
		begin
			somaC := 0;
			for i := 1 to n do
		 		somaC := somaC + mat[i,j];
		 	tam := tam + 1;
		 	vetor_somas[tam] := somaC;
		 end;
end;

(*procedimento que verifica a soma das diagonais*)
procedure soma_diagonais (var mat : matriz; n : longint; var somaD, tam : longint; var vetor_somas : vetor);
var i, j : longint;

begin
	i := 1;
	somaD := 0;
	while i <= n do
		begin
			somaD := somaD + mat[i, i]; (*Calcula a soma da diagonal principal*)
			i := i + 1;
		end;
	tam := tam + 1;
	vetor_somas[tam] := somaD;
	somaD := 0;
	i := 1;
	j := n;
	while (i <= n) and (j >= 1) do
		begin
			somaD := somaD + mat[i,j]; (*calcula a soma da diagonal secundaria*)
			i := i + 1;
			j := j - 1;
		end;
	tam := tam + 1;
	vetor_somas[tam] := somaD;
end;

(*funcao que verifica se a matriz eh um quadrado magico*)
function eh_quadrado_magico (var mat : matriz; n : longint): boolean;
var i, somaL, somaC, somaD, tam : longint;
	vetor_somas : vetor;
	soma_eh_igual : boolean;

begin
	eh_quadrado_magico := false;
	tam := 0;
	soma_eh_igual := true;
	
	soma_linha (mat, n, somaL, tam, vetor_somas);       (*procedimentos calculam os resulados das somas de cada linha coluna e diagonal, e insere num vetor*)
	soma_coluna (mat, n, somaC, tam, vetor_somas);
	soma_diagonais (mat, n, somaD, tam, vetor_somas);
	
	i := 1;
	while soma_eh_igual and (i <= tam - 1 ) do
		begin
			if vetor_somas[i] <> vetor_somas[i + 1] then
				soma_eh_igual := false;
			i := i + 1;
		end;
	if soma_eh_igual then
		eh_quadrado_magico := true;	
end;

function calcula_tam (var m : matriz; n, lin, col: longint): longint;

begin
	calcula_tam := 0;
	while (lin <= n) and (col <= n) do
		begin
			calcula_tam := calcula_tam + 1;
			col := col + 1;
			lin := lin -1;
		end;
end;

procedure zera_matriz (var m : matriz; tam : longint);
var i, j : longint;

begin
	for i := 1 to tam do
		for j := 1 to tam do
			m[i,j] := 0;
end;

procedure insere_matriz (var m, aux : matriz; lin, col, tam : longint);
var i, j, inicio_col : longint;

begin
	inicio_col := col;
	i := 1;
	while i <= tam do
		begin
			col:= inicio_col;
			j := 1;
			while j <= tam do
				begin
					aux[i,j] := m[lin,col];
					j := j + 1;
					col := col + 1;		
				end;
			i := i + 1;
			lin := lin + 1;
		end;
end;

procedure imprime_matriz (var m : matriz; tam : longint);
var i, j : longint;

begin
	writeln;
	writeln ('a matriz quadrada eh:');
	for i := 1 to tam do
	begin
		for j := 1 to tam do
			write (m[i,j], ' ');
		writeln;
	end;
	writeln;
end;

(*FUNCAO QUE VERIFFICA A QUANTIDADE DE QUADRADOS MAGICOS, NUMA COORDENADA ESPECIFICA*)
function verifica_quadrados (var m : matriz; n, lin, col : longint): longint;
var tam : longint;
	aux : matriz;
	
begin
	verifica_quadrados := 0;
	for tam := calcula_tam (m, n, lin, col) downto 2 do
		begin
			zera_matriz (aux, tam);
			insere_matriz (m, aux, lin, col, tam);
			if eh_quadrado_magico (aux, tam) then
				begin
					verifica_quadrados := verifica_quadrados + 1;
					imprime_matriz (aux, tam);
				end;
		end;
end;

function total_de_quadrados (var m : matriz; n : longint): longint;
var i, j : longint;

begin
	total_de_quadrados := 0;
	for i := 1 to n - 1 do
		for j := 1 to n - 1 do
			total_de_quadrados := total_de_quadrados + verifica_quadrados (m, n, i, j);
end;

(*Programa principal*)
begin
	read (n);
	le_matriz (mat, n);
	writeln (total_de_quadrados (mat, n));
end.	
