program vetores004;

const max = 100;

type vetor = array [1..max] of longint;

var n, qnt: longint;
    v, d: vetor;
    
function eh_distinto (var w : vetor; x, y : longint): boolean;

begin
	eh_distinto := false;
	
	if x <> y then
		eh_distinto := true;
end;


//funcao que conta os valores distintos

function qnt_distintos (var v : vetor; n : longint) : longint;
var i, j, cont : longint;
	eh_dif : boolean;

begin   
    cont := 0; i := 1; j := i + 1 ;
    while i <= n do
    begin    
    	eh_dif := true;
        while j <= n do
        begin	
        	if v[i] = v[j] then
                	eh_dif := false;
                j := j + 1;
        end;
        if eh_dif then
        	cont := cont + 1;
        i:= i + 1;
        j := i + 1;
    end;    	
    qnt_distintos := cont;
end;

//procedimento que imprime os distintos

procedure imprime_vetor (var d : vetor; qnt : longint);
var i : longint;

begin
	for i := 1 to qnt do
		write (d[i], ' ');
	writeln
end; 

//procedimento que le vetor

procedure le_vetor (var v : vetor; n : longint);
var i : longint;

begin
    for i := 1 to n do
        read ( v[i] );
end;

//procedimento que verifica a ocorrencia

procedure ocorrencia (var v : vetor; n : longint);
var i, cont, k : longint;

begin 
	for k := 1 to n do
	begin 
	if v[k] <> v[k + 1] then
		begin
		cont := 0;
		for i := 1 to n do 
			if v[k] = v[i] then
				cont := cont + 1;
		if cont > 1 then
			writeln (v[k], ' ocorre ', cont, ' vezes' )
		else
			writeln (v[k], ' ocorre ', cont, ' vez' )
		end;
	end;
end;

//procedimento que cria um novo vetor

procedure le_vetor_dos_distintos (v : vetor; var d : vetor; n : longint);
var
  iv, id, maxd: longint;
  achou: boolean;
begin
  maxd := 0;  // contador de elementos distintos já armazenados em d

  for iv := 1 to n do
  begin
    achou := false;
    for id := 1 to maxd do
    begin
      if v[iv] = d[id] then
      begin
        achou := true;
        break;
      end;
    end;

    if not achou then
    begin
      maxd := maxd + 1;
      d[maxd] := v[iv];
    end;
  end;
end;
//ocorrencia com um novo vetor

procedure ocorrencia_novo_vetor (var v, d : vetor; n : longint);
var iv, id, cont : longint;

begin 
	for id := 1 to qnt do
	begin 
		cont := 0;
		for iv := 1 to n do
			if d[id] = v[iv] then
				cont := cont + 1;
		if cont > 1 then
			writeln (d[id], ' ocorre ', cont, ' vezes')
		else	
			writeln (d[id], ' ocorre ', cont, ' vez')
	end;
end;

//programa principal

begin
    read (n);
    le_vetor (v, n);
    qnt := qnt_distintos(v,n);
    if qnt > 1 then
    	write ( 'a sequencia tem ', qnt, ' numeros distintos: ')
    else
    	write ( 'a sequencia tem ', qnt, ' numero distinto: ');
    le_vetor_dos_distintos (v, d, n);
    imprime_vetor (d, qnt);
    ocorrencia_novo_vetor (v, d, n);
end.
