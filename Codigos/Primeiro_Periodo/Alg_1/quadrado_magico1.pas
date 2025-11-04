program quadrado_magico1;

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

(*Programa principal*)
begin
	read (n);
	le_matriz (mat, n);
	if eh_quadrado_magico(mat, n) then
		writeln ('sim')
	else
		writeln ('nao');
end.	
