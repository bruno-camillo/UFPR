program vetores002;

const max = 100;

type vetor = array [1..max] of longint;

var v : vetor;
    tam, i, x : longint;

//procedimento que le vetor e da o tamanho

procedure ler_vetor (var v : vetor; var tam : longint);
var x, i : longint;

begin
    i := 1;
    read (x);
    while x <> 0 do
    begin
        v[i] := x;
        i := i + 1;
        tam := tam + 1;
        read (x);
    end;
end;

//funcao que busca no vetor

function busca_no_vetor (var v : vetor; x, tam : longint): longint;
var i : longint;

begin  
    busca_no_vetor := 0;
    for i := 1 to tam do
        if v[i] = x then
            busca_no_vetor := i;
end;
//programa principal

begin
    tam := 0;
    ler_vetor (v, tam); 
    read (x);
    while x <> 0 do
        begin
            i := busca_no_vetor (v, x, tam);
            if i = 0 then
                writeln ('0')
            else
                writeln (i);
            read (x);
        end;
end.
