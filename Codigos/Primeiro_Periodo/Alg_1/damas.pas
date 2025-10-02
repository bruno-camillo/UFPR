program damas;

type matriz = array [1..8,0..9] of longint;

var tabuleiro, auxiliar : matriz;

(*PROCEDIMENTO QUE LE A MATRIZ DO TABULEIRO*)
procedure le_matriz (var m : matriz);
var i, j : longint;

begin
	for i := 1 to 8 do
		for j := 1 to 8 do
			read ( m[i,j] );
	for i := 1 to 8 do
	begin
		m[i,0] := -2;
		m[i,9] := -2;
	end;
	
end;

(*PROCEDIMENTO QUE ZERA A MATRIZ*)
procedure zera_matriz (var m : matriz);
var i, j : longint;

begin
	for i := 1 to 8 do
		for j := 1 to 8 do
			m[i,j] := 0;
end;

(*FUNCAO QUE VERIFICA SE UMA PECA DE DAMAS PODE TOMAR UMA OUTRA*)
function pode_tomar (var m : matriz; i, j : longint): boolean;

begin
	pode_tomar := false;
	if ((m[i+1, j+1] = 1) and (m[i+2, j+2] = 0)) or ((m[i+1, j-1] = 1) and (m[i+2, j-2] = 0))  then
		pode_tomar := true;
end;

(*FUNCAO QUE VERIFICA SE UMA PECA DE DAMAS PODE SE MOVIMENTAR*)
function tem_casa_livre (var m : matriz; i, j : longint): boolean;

begin
	tem_casa_livre := false;
	if (m[i+1, j-1] = 0) or (m[i+1, j+1] = 0) then
		tem_casa_livre := true;
end;

(*FUNCAO QUE VERIFICA SE UMA PECA DE DAMAS ESTA IMPOSSIBILITADA DE SE MOVIMENTAR*)
function tem_casa_ocupada (var m: matriz; i, j : longint): boolean;

begin
	tem_casa_ocupada := false;
	if (m[i+1, j-1] = -1) or (m[i+1, j+1] = -1) then
		tem_casa_ocupada := true;
end;

(*PROCEDIMENTO QUE VERIFICA TODAS AS POSSIBILIDADES DE JOGADA PARA AS PECAS PRETAS NUM TABULEIRO DE DAMAS, MONTANDO UMA MATRIZ AUXILIAR*)
procedure verifica_movimento (var m, aux : matriz);
var i, j : longint;

begin
	for i:= 1 to 7 do       //percorre todas as casas do tabuleiro, com excecao da ultima linha, que nao deve ser contada para o exercicio
		for j := 1 to 8 do
			begin
				if m[i,j] = -1 then
					begin
(*condicionais verificam a situcao da peca de coordenada (i, j), podendo se mover, caso a proxima casa estiver livre, ficar, se as proximas casas estiverem 
ocupadas, ou tomar uma peca adversaria se as condicoes forem atendidas*)
						if tem_casa_ocupada (m, i, j) then
							aux[i,j] := 3;
						if tem_casa_livre (m, i, j) then
								aux[i,j] := 2;
						if pode_tomar (m, i, j)  then
							aux[i,j] := 1;
					end;
			end;
end;

function busca_na_matriz (var m : matriz; x : longint): boolean;
var i, j : longint;

begin
	busca_na_matriz := false;
	i := 1;
	while not busca_na_matriz and (i <= 8) do
		begin
			j := 1;
			while not busca_na_matriz and (j <= 8) do
				begin
					if m[i,j] = x then
						busca_na_matriz := true;
					j := j + 1;
				end;
			i := i + 1;
		end;
end;

(*PROCEDIMENTO QUE VERIFICA E IMPRIME AS COORDENADAS DE PECAS QUE PODEM SER TOMADAS*)
procedure imprime_tomaveis (var m : matriz);
var i, j, x : longint;

begin
	write ('tomar: ');
	x := 1;
	if busca_na_matriz (m, x) then
		for i := 1 to 7 do
			for j := 1 to 8 do
				if m[i,j] = 1 then
					write (i, '-', j, ' ');
	if not busca_na_matriz (m, x) then 
		write ('0');
	writeln;
end;
(*PROCEDIMENTO QUE VERIFICA E IMPRIME AS PECAS QUE PODEM SE MOVER*)
procedure imprime_moveis (var m: matriz);
var i, j, x : longint;

begin
	write ('mover: ');
	x := 2;
	if busca_na_matriz (m, x) then
		for i := 1 to 7 do
			for j := 1 to 8 do
				if m[i,j] = 2 then
					write (i, '-', j, ' ');
	if not busca_na_matriz (m, x) then
		write ('0');
	writeln;
end;

(*PROCEDIMENTO QUE VERIFICA AS PECAS QUE DEVEM FICAS EM SUAS POSICOES*)
procedure imprime_imoveis (var m : matriz);
var i, j, x : longint;

begin
	write ('ficar: ');
	x := 3;
	if busca_na_matriz (m, x) then
		for i := 1 to 7 do
			for j := 1 to 8 do
				if m[i,j] = 3 then
					write (i, '-', j, ' ');
	if not busca_na_matriz (m, x) then
		write ('0');
	writeln;
end;

(*PROGRAMA PRINCIPAL*)
begin
	le_matriz (tabuleiro);
	zera_matriz (auxiliar);
	verifica_movimento (tabuleiro, auxiliar); (*matriz auxiliar funcionando perfeitamente*)
	imprime_tomaveis (auxiliar);
	imprime_moveis (auxiliar);
	imprime_imoveis (auxiliar);
end.
