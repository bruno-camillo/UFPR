program series10;

var n, sinal, den, i : longint;
	x, num, soma : real;

procedure calcula_num (var num : real; x : real);
var i : longint;

begin	
	for i := 1 to 4 do
		num := num * x;
end;

procedure calcula_den (var den: longint);

begin
	if den = 6 then
		den := 1
	else
		den := den * (den + 1);
end;

procedure calcula_sinal (var sinal : longint; i : longint);

begin
	sinal := 1;
	if i mod 3 = 0 then
		sinal := -1;
end;

(*PROGRAMA PRINCIPAL*)
begin
	read (n, x);
	soma := 1;
	num := 1;
	den := 1;
	for i := 2 to n do
		begin
			calcula_num (num, x);
			calcula_den (den);
			calcula_sinal (sinal, i);
			soma:= soma + sinal * (num/den);
		end;
	writeln (soma:0:2);
end.
