(*Faça um programa em Free Pascal que leia um número natural 0 < n ≤ 100 e em seguida leia uma sequência de n números inteiros. Seu programa deve determinar o valor do subsequência que maximize a soma dos seus elementos.

Exemplo de entrada:
12
5 2 -2 -7 3 14 10 -3 9 -6 4 1

Saı́da esperada para a entrada acima:
33

Observação 1: O valor 33 da saı́da esperada acima, foi obtido pela soma dos valores dos ı́ndices de 5 a 9, isto é, v[5] = 3 até v[9] = 9.

Observação 2: Idealmente, seu programa deve fazer o menor número possı́vel de somas dos elementos dos vetores, embora o FARMA-ALG apenas checa se sua resposta está correta. Você consegue fazer um programa que nunca some duas vezes uma sequência que já foi somada antes? Teste isso fora do FARMA-ALG.*)

program maximizadorlista8;

const max = 100;
      max_da_soma = 10000;

type vetor = array [1..max] of longint;
     vetor_soma = array [1..max_da_soma] of longint;

var v : vetor;	tam, tam_das_somas : longint; somas_possiveis : vetor_soma;
	
//procedimento que le um vetor	
	
procedure le_vetor (var v : vetor; tam : longint);	
var i : longint;

begin
	for i := 1 to tam do
		read ( v[i] );
end;

//funcao que faz a soma dos conteudos do vetor

function soma_dos_conteudos (var v : vetor; x, y : longint): longint;

begin;
	soma_dos_conteudos := x + y;
end;

//procedimento que insere num vetor

procedure insere_no_vetor (var w : vetor_soma; x : longint; var tam_das_somas: longint);

begin
	tam_das_somas := tam_das_somas + 1;
	w[tam_das_somas] := x;
end;

//funcao que escreve o maior conteudo

function maior_soma (var v : vetor_soma; tam_das_somas : longint): longint;
var i, maior : longint;

begin
	maior := v[1];
	for i := 2 to tam_das_somas do
		if v[i] > maior then
			maior := v[i];
	maior_soma := maior;
end;
//procedimento que soma e insere num vetor

procedure soma_e_insere_um_a_um (var v : vetor; var w : vetor_soma; tam : longint);
var i, j, soma : longint;

begin
	for i := 1 to tam do
	begin
		soma := 0; 	
		for j := i + 1 to tam do
		begin	
			soma := soma_dos_conteudos(v, v[i], v[j]);
			insere_no_vetor (w, soma, tam_das_somas);
		end;
	end;
end;
	
procedure soma_e_insere_todas_as_opcoes (var v : vetor; var w : vetor_soma; tam : longint);
var i, j, soma : longint;

begin
	for i := 1 to tam do
	begin
		soma := 0;	
		for j:= i + 1 to tam do
		begin	
			soma := soma_dos_conteudos(v, soma, v[j]);
			insere_no_vetor (w, soma, tam_das_somas);
		end;
	end;
end;
	
//programa principal

begin
	read (tam);
	tam_das_somas := 0;
	le_vetor (v, tam);
	soma_e_insere_um_a_um (v, somas_possiveis, tam);
	soma_e_insere_todas_as_opcoes (v, somas_possiveis, tam);
	writeln ( maior_soma(somas_possiveis, tam_das_somas) );
end.
