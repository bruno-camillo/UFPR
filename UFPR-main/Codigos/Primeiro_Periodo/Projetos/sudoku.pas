program sudoku;

type matriz = array [1..9,1..9] of longint;
     vetor = array [1..9] of longint;

var m : matriz;
    n, lin, col, terminou : longint;

procedure inicializa_matriz (var m : matriz);
var i, j : longint;

begin
        for i := 1 to 9 do 
            for j := 1 to 9 do 
                m[i,j] := 0;
end;

procedure imprime_matriz (var m :  matriz);
var i, j : longint;

begin
        for i := 1 to 9 do 
        begin
            for j := 1 to 9 do 
                    write (m[i,j], ' ');
            writeln;
        end;        
end;

procedure introduz_a_matriz (var m : matriz; n, lin, col : longint);
begin
    m[lin,col] := n;
end;

procedure inicializa_vetor (var v : vetor);
var i : longint;

begin
    for i := 1 to 9 do
        v[i] := i;
end;

procedure insere_vetor (var v : vetor; n : longint);

begin
        v[n] := n; 
end;

procedure zera_vetor (var v : vetor);
var i : longint;

begin   
        for i := 1 to 9 do  
            v[i] := 0;
end;

function vetor_nao_completo (var resposta, v : vetor): boolean;
var i : longint;

begin
        vetor_nao_completo := false;
        i := 1;
        while (i <= 9) and not vetor_nao_completo do
            begin
                    if resposta[i] <> v[i] then 
                        vetor_nao_completo := true;
                    i := i + 1;
            end;
end;

procedure verifica_linhas (var m : matriz; var k : boolean);
var i, j : longint;
    v, resposta : vetor;

begin
    inicializa_vetor (v);
    k := true;
    i := 1;
    while (i <= 9) and k do
        begin
            j := 1; 
            zera_vetor (resposta);
            while (j <= 9) and k do    
                begin
                    insere_vetor (resposta, m[i,j]);
                    j := j + 1;
                end;
            if vetor_nao_completo (resposta, v) then
                k := false;
            i := i + 1;
        end;
end;

procedure verifica_colunas (var m : matriz; var k : boolean);
var i, j : longint;
    v, resposta : vetor;

begin
    inicializa_vetor (v);
    k := true;
    j := 1;
    while (j <= 9) and k do
        begin
            i := 1; 
            zera_vetor (resposta);
            while (i <= 9) and k do    
                begin
                    insere_vetor (resposta, m[i,j]);
                    i := i + 1;
                end;
            if vetor_nao_completo (resposta, v) then
                k := false;
            j := j + 1;
        end;
end;

procedure verifica_sub (var m : matriz; var k : boolean);
var lin, col, i, j : longint;
    v, resposta : vetor;

begin
        k := true;
        lin := 1;
        inicializa_vetor (v);
        while (lin <= 7) and k do
            begin
                col := 1;
                while (col <= 7) and k do
                    begin
                        zera_vetor (resposta);
                        for i := lin to lin + 2 do
                            for j := col to col + 2 do
                                resposta[m[i,j]] := m[i,j];
                        if vetor_nao_completo (resposta, v) then
                            k := false
                        else
                            col := col + 3;
                    end;
                lin := lin + 3;
            end;
end;

function ganhou_jogo (var m : matriz): boolean;
var verificaC, verificaL, verificaS : boolean;

begin
        verifica_linhas (m, verificaL);
        verifica_colunas (m, verificaC);
        verifica_sub (m, verificaS);
        if verificaC and verificaL and verificaS then   
            ganhou_jogo := true
        else
            ganhou_jogo := false;
end;

(*PROGRAMA PRINCIPAL*)
begin
        writeln ('Bem vindo (a) ao Sudoku no Terminal!');
        writeln;
        inicializa_matriz (m);
        imprime_matriz (m);
        terminou := 0;
        writeln ('Para ganhar, preencha essa tabela seguindo as regras do Sudoku tradicional!');
        writeln;
        while terminou <> 1 do 
            begin
                writeln ('Defina o número a ser introduzido ao jogo: ');
                read (n);
                writeln;
                writeln ('Defina as coordenadas (x,y) que o número será introduzido: ');
                read (lin, col);
                introduz_a_matriz (m, n, lin, col);
                writeln ('O jogo foi atualizado:');
                imprime_matriz (m);
                writeln;
                writeln ('Se você acha que finalizou o jogo, digite 1, caso queira continuar, digite 0:');
                read (terminou);
                writeln;
            end;
        if ganhou_jogo (m) then
            writeln ('Parabéns você concluiu o jogo corretamente!!!')
        else
        begin
            writeln ('Droga, você se enganou...Comece o jogo novamente!!!');
        end;
end.
