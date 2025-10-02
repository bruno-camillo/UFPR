program subsequencias;

const MAX = 100;

type vetor = array [1..MAX] of longint;

var
    v, m : vetor;
    n, pos, tamanho_subsequencia: longint;

procedure ler_vetor (var v: vetor; n: longint);
var i : longint;

begin
	for i := 1 to n do
		read ( v[i] );
end;

procedure imprime (var v : vetor; n : longint);
var i : longint;

begin	
	for i := 1 to n do
		write ( v[i] );
	writeln;
end;

//procedimento que insere num vetor
procedure insere (var v : vetor; n, i : longint);
begin
	v[i] := n;
end;

//procedimento que zera o vetor
procedure zera_vetor (var v : vetor; var tam : longint);
var i : longint;

begin
	for i := 1 to tam do
		v[i] := 0;
	tam := 0;		
end;

function eh_igual (n, m : longint): boolean;
begin
	eh_igual := false;
	if n = m then
		eh_igual := true;
end;

//funcao que acha um vetor dentro de outro retornando true ou false

function acha_vetor(var v, w: vetor; tamv, tamw, inicio: longint): boolean;
var
    i, j: longint;
begin
    acha_vetor := false;
    for i := inicio to tamv - tamw + 1 do
    begin
        j := 1;
        while (j <= tamw) and (v[i + j - 1] = w[j]) do
            j := j + 1;
        if j > tamw then
        begin
            acha_vetor := true;
            exit;
        end;
    end;
end;

function tem_subsequencia_iguais(var v, m: vetor; n: longint; var tam: longint): longint;
var
    tam0, i, j: longint;
begin
    tem_subsequencia_iguais := 0;
    for tam0 := tam downto 2 do
    begin
        for i := 1 to n - tam0 do
        begin
            // Preenche m com a subsequência atual
            for j := 1 to tam0 do
                m[j] := v[i + j - 1];
            
            // Verifica se a subsequência se repete depois
            if acha_vetor(v, m, n, tam0, i + tam0) then
            begin
                tem_subsequencia_iguais := i;
                tam := tam0;
                exit;
            end;
        end;
    end;
end;

(*PRECISA FAZER ALTERACOES NOS PARAMETROS, VISTO QUE AS FUNCOES FORAM MODIFICADAS*)
// programa principal
begin
    read (n);
    // tamanho da subsequencia a ser lido
    ler_vetor (v,n); 
    pos:= 0;
    tamanho_subsequencia:= n div 2; // inicia com maior valor possivel
    while (pos = 0) and (tamanho_subsequencia >= 2) do
    begin     
    	pos:= tem_subsequencia_iguais (v, m, n,tamanho_subsequencia);
    	if pos = 0 then
        tamanho_subsequencia := tamanho_subsequencia - 1;
    end;
    if pos > 0 then
        writeln (pos, ' ', tamanho_subsequencia)
    else
        writeln ('nenhuma');
end.

