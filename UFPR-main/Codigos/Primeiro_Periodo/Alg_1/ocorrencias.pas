program ocorrencia;

const max = 100;

type vetor = array [1..max] of longint;

var m, n : longint;
    vm, vn : vetor;
    
//procedimento que le m e n, limitando aos naturais e seguindo a condicao de m > n

procedure ler (var n, m : longint);
begin
	while ((n <= 0) or (m <= 0)) or (n < m) do
		read (n, m);
end;    
    
//procedimento que le os vetores    

procedure ler_vetor (var v : vetor; n : longint);
var i : longint;

begin
	for i := 1 to n do
		read ( v[i] );
end;

//funcao que conta quantas vezes o vetor m esta no vetor n

function qnt_repeticoes (var v, w : vetor; n, m : longint): longint;
var i, j, cont, temp : longint;
	eh_igual : boolean; 

begin
	i := 1; cont := 0;
	while i <= (n - m + 1) do
		begin
			if v[i] <> w[1] then
				i := i + 1
			else
				begin
					j := 1; temp := i; eh_igual := true;
					while j <= m do
						begin
							if v[i] <> w[j] then
								eh_igual := false;
							j := j + 1;
							i := i + 1;
						end;
					i := temp;
					if eh_igual then
						cont := cont + 1;
					i := i + 1;	
				end;
		end;
	qnt_repeticoes := cont;
end;		
    
//programa principal

begin
	ler (n, m);
	ler_vetor (vn, n);
	ler_vetor (vm, m);
	writeln ( qnt_repeticoes(vn, vm, n, m) );
end.	
