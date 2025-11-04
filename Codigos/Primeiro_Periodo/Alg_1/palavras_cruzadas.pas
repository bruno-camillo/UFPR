program palavras_cruzadas;

const max = 99;

type matriz = array [0..max,0..max] of longint;

var m : matriz;
	lin, col : longint;

procedure le_matriz (var m : matriz; lin, col : longint);
var i, j : longint;

begin
	for i := 1 to lin do
		for j := 1 to col do
			read (m[i,j]);
	(*dois lacos criam uma barreira em volta da matriz original, com o fito de auxiliar nos calculos*)
	for i := 0 to lin + 1 do
		begin
			m[i,0] := -1;
			m[i,col+1] := -1
		end;
	for j := 1 to col do
		begin
			m[0, j] := -1;
			m[lin+1, j] := -1;
		end;
	
end;

(*FUNCAO QUE VERIFICA SE O ELEMENTO TEM ESPACO PARA FORMAR UMA PALAVRA NA LINHA*)
function tem_espaco_lin (var m : matriz; lin, col : longint): boolean;

begin
	tem_espaco_lin := false;
	if (m[lin, col+1] = 0) then
		tem_espaco_lin := true;
end;

(*FUNCAO QUE VERIFICA SE O ELEMENTO DA MATRIZ NAO ESTA NO MEIO DE UMA PALAVRA*)
function pode_iniciar_lin (var m : matriz; lin, col : longint): boolean;

begin
	pode_iniciar_lin := false;
	if (m[lin, col-1] = -1) then	 
		pode_iniciar_lin := true;
end;

(*FUNCAO QUE VERIFICA SE O ELEMENTO TEM ESPACO PARA FORMAR UMA PALAVRA NA COLUNA*)
function tem_espaco_col (var m : matriz; lin, col : longint): boolean;

begin
	tem_espaco_col := false;
	if m[lin+1, col] = 0 then
		tem_espaco_col := true;
end;

(*FUNCAO QUE VERIFICA SE O ELEMENTO DA MATRIZ NAO ESTA NO MEIO DE UMA PALAVRA*)
function pode_iniciar_col (var m : matriz; lin, col : longint): boolean;

begin
	pode_iniciar_col := false;
	if m[lin-1, col] = -1 then	 
		pode_iniciar_col := true;
end;

(*FUNCAO QUE VERIFICA SE UMA PALAVRA PODE SER FORMADA NA LINHA DO ELEMENTO*)
function verifica_lin (var m : matriz; lin, col : longint): boolean;

begin
	verifica_lin := false;
	if tem_espaco_lin (m, lin, col) and pode_iniciar_lin (m, lin, col) then
		verifica_lin := true;
end;

(**FUNCAO QUE VERIFICA SE UMA PALAVRA PODE SER FORMADA NA COLUNA DO ELEMENTO*)
function verifica_col (var m : matriz; lin, col : longint): boolean;

begin
	verifica_col := false;
	if tem_espaco_col (m, lin, col) and pode_iniciar_col (m, lin, col) then
		verifica_col := true;
end;

(*procedimento que modifica a matriz para a nova com a contagem de palavras*)
procedure conta_palavras (var m : matriz; lin, col: longint);
var i, j, cont : longint;

begin
	cont := 1;
	for i := 1 to lin do
		for j := 1 to col do
			begin
				if m[i,j] <> -1 then
					if verifica_lin (m, i, j) or verifica_col (m, i, j) then
						begin	
							m[i,j] := cont;
							cont := cont + 1;
						end;
			end;
end;

(*PROCEDIMENTO QUE REALIZA A CONTAGEM DE PALAVRAS DO JOGO JA INSERINDO NA MATRIZ, E A IMPRIME*)
procedure imprime_jogo (var m : matriz; lin, col : longint);
var i, j : longint;

begin
	conta_palavras (m, lin, col);
	for i := 1 to lin do
		begin
			for j := 1 to col do
				write (m[i,j], ' ');
			writeln;
		end;
end;

(*PROGRAMA PRINCIPAL*)
begin
	read (lin, col);
	le_matriz (m, lin, col);
	imprime_jogo (m, lin, col);
end.
