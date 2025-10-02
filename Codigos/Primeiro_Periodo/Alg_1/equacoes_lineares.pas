program equacao_linear;

const MAX = 50;

type matriz = array [1..MAX,1..MAX] of real;
	vetor = array [1..MAX] of real;

var mat : matriz;
	v_resultado, v_igualdade : vetor;
	m, n : longint;

(*PROCEDIMENTO LEITOR DE VETOR*)
procedure le_vetor (var v : vetor; tam : longint);
var i : longint;

begin
	for i:= 1 to tam do
		read ( v[i] );
end;

(*PROCEDIMENTO LEITOR DE MATRIZ*)
procedure le_matriz (var m : matriz; lin, col : longint);
var i, j : longint;

begin
	for i := 1 to lin do
		for j := 1 to col do
			read ( m[i,j] );
end;

(*PROCEDIMENTO QUE INSERE NO VETOR*)
procedure insere_vetor (var v : vetor; x : real; i : longint);

begin
	v[i] := x;
end;

(*FUNCAO QUE COMPARA DOIS VETORES*)
function vetores_iguais (var v, w : vetor; tam : longint): boolean;
var i : longint;

begin
	vetores_iguais := true;
	i := 1;
	while vetores_iguais and (i <= tam) do
		begin
			if v[i] <> w[i] then
				vetores_iguais := false;
			i := i + 1;
		end;
end;

(*FUNCAO QUE VERIFICA O RESULTADO*)
function eh_resultado (var mat : matriz; var res, igd : vetor; lin, col : longint): boolean;
var v : vetor;
	i, j : longint;
	soma : real;

begin
	eh_resultado := false;
	soma := 0;
(*LACO REALIZA A TROCA AS VARIAVEIS DA EQUACAO PELO RESULTADO INFORMADO, INFORMANDO A SOMA OBTIDA APOS A TROCA*)
	for i := 1 to lin do
		begin
			soma := 0;
			for j := 1 to col do
				soma := soma + mat[i,j] * res[j];
(*INSERE O RESULTADO DA EQUACAO APOS TROCA DAS VARIAVEIS DENTRO DE UM VETOR*)
			insere_vetor (v, soma, i);          
		end;
(*COMPARA O VETOR DAS SOMAS APOS TROCA DE VARIAVEL, COM A IGUALDADE DAS EQUACOES ORIGINAIS*)
	if vetores_iguais (igd, v, col) then
		eh_resultado := true;
end;
(*PROGRAMA PRINCIPAL*)
begin
	(*INICIO, ENTRADA DE VALORES*)
	read (m, n);             (*M = numero de linhas, N = numero de colunas*)
	le_vetor (v_resultado, n); // le os valores do possivel resultado
	le_matriz (mat, m, n);
	le_vetor (v_igualdade, m); // le os valores das igualdades do sistema
	
	(*VERIFICACAO DE RESULTADO*)
	if eh_resultado (mat, v_resultado, v_igualdade, m, n) then
		writeln ('sim')
	else
		writeln ('nao');
end.
