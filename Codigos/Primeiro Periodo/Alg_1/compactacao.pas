program compactacao;

const max = 100;

type vetor = array [1..max] of longint;

var v, w, c: vetor;
    tam, iw, n, iv, cont, s, tamc : longint;

//procedimento que imprime um vetor

procedure imprime (var v : vetor; n : longint);
var i : longint;

begin
	for i := 1 to n do
		write ( v[i], ' ');	
end;

procedure insere (var v : vetor; var i : longint; n : longint);

begin
	i := i + 1;
	v[i] := n;
end;

//le um numero n 0 <= n <= 100

procedure ler (var n : longint);
begin
	read (n);
	while (n < 0) or (n > 100) do
		read (n);
end;
 
//procedimento que le vetor

procedure ler_vetor (var v : vetor; tam, n, j : longint);
var i : longint;

begin
	for i := j + 1 to tam do
		read ( v[i] );
end;

//procedimento que imprime a sequencia original

procedure sequencia_original (var v : vetor; c, i : longint);
var j : longint;

begin
	write ('Sequencia original: ');
	for j := i to c do 
		write ( v[j], ' ' );
	writeln;
end;

//funcao que compara um elemento com os demais de um vetor;

function eh_unico (var c : vetor; tamc, n : longint): boolean;
var j : longint;

begin	
	eh_unico := true;
	for j := 1 to tamc do
		if n = c[j] then
			eh_unico := false;
end;

//procedimento que imprime a sequencia original

procedure sequencia_compactada (var v, c : vetor; s, iv, tamc : longint);
var j : longint;

begin
	write ('Sequencia compactada: '); 
	for j := iv to s do
		if eh_unico (c, tamc, v[j]) then 
			insere (c, tamc, v[j]);

	imprime (c, tamc);	
	writeln;
end;

//procedimento que zera o vetor

procedure zera_vetor (var v : vetor ; var tam : longint);
var i : longint;

begin
	for i := 1 to tam do
		v[i] := 0;
	tam := 0;
end; 

//programa principal

begin
	writeln ('Digite um numero equivalente a quantidade da sequencia: ');
	ler (n); iw := 0; iv := 0; tam := 0; cont := 0;
	while n <> 0 do
	begin	
		cont := cont + 1;
		tam := tam + n;
		writeln ('Digite os numeros da sequencia: ');
		ler_vetor (v, tam, n, iv);
		iv := tam;
		writeln ('Digite um numero equivalente a quantidade da sequencia: ');
		insere (w, iw, n);
		
		ler (n);
	end;	
	// funcionando corretamente até aqui, vetor v mantem os conteudos, e o vetor w mantem os valor 'n' inseridos na ordem correta que foram lidos
	iv := 1; s := 0; tamc := 0;
	//reinicializamos iv para poder realizar a impressao do jeito correto!
	for iw := 1 to cont do
	begin
		s := s + w[iw];
		sequencia_original (v, s , iv);
		sequencia_compactada (v, c, s, iv, tamc);
		zera_vetor (c, tamc);
		iv := iv + w[iw];
	end;
end.
