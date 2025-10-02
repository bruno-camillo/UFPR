program matriz_triangular;

type matriz = array [1..100,1..100] of longint;

var m : longint;
	mat : matriz;

//procedimento que le matriz
procedure le_matriz (var mat : matriz; m : longint);
var i, j : longint;

begin		
	for i := 1 to m do
		for j := 1 to m do
			read (mat[i,j]);
end;

//funcao que verifica se a matriz eh triangular superior
function eh_inferior (var mat : matriz; m : longint): boolean;
var i, j, i_ini, j_ini : longint;

begin
	eh_inferior := true;
	i_ini := 1; j_ini := 2;
	while (eh_inferior) and (i_ini < m) and (j_ini < m) do
		begin
			i := i_ini; j := j_ini;
			while (j < m) do
				begin
					if mat[i,j] <> 0 then
						eh_inferior := false;
					j := j + 1;
				end;
			i_ini := i_ini + 1; j_ini := j_ini + 1;
		end;
end;

//funcao que verifica se a matriz eh triangular superior
function eh_superior (var mat : matriz; m : longint): boolean;
var i, j, i_ini, j_ini : longint;

begin
	eh_superior := true;
	i_ini := 2; j_ini := 1;
	while (eh_superior) and (i_ini < m) and (j_ini < m) do
		begin
			i := i_ini; j := j_ini;
			while (i < m) do
				begin
					if mat[i,j] <> 0 then
						eh_superior := false;
					i:= i + 1;
				end;
			i_ini := i_ini + 1; j_ini := j_ini + 1;
		end;
end;

//funcao que verifica se a matriz eh triangular
function eh_matriz_tring (var mat : matriz; m : longint): boolean;

begin	
	eh_matriz_tring := false;
	if eh_superior (mat, m) then
		eh_matriz_tring := true;
	if eh_inferior (mat, m) then
		eh_matriz_tring := true;
end;

//programa principal
begin	
	read (m);
	le_matriz (mat, m);
	//verifica se a matiz eh triangular
	if eh_matriz_tring (mat, m) then 
		writeln ('sim')
	else
		writeln ('nao');
end.
