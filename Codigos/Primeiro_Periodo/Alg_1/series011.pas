program series10;

var sinal, i : longint;
	x, soma, num, den : real;

procedure calcula_num (var num : real; x : real; i : longint);

begin	
	if i mod 2 = 0 then
		num := (num + 5) * x
	else
		num := (num + 1) * x;
end;

procedure calcula_den (var den: real; i : longint);
var j, fat : longint;
begin
	fat := 1;
	for j := 0 to i - 1 do
		fat := fat * (j + 1);
	den := sqrt(fat); 
end;

procedure calcula_sinal (var sinal : longint; i : longint);

begin
	sinal := 1;
	if (i = 2) or (i = 5) or (i = 8) or (i = 11) or (i = 14) then
		sinal := -1;
end;

function soma_ (i, sinal : longint; x, den, num : real): real;

begin
	if i = 1 then
		soma_ := 0;
	calcula_num (num, x, i);
	calcula_den (den, i);
	calcula_sinal (sinal, i);
	soma_:= soma_ + sinal * (num/den);
end;

(*PROGRAMA PRINCIPAL*)
begin
	read (x);
	i := 1;
	num := 0;
	den := 0;
	sinal := 1;
	while (i <= 15) and ((soma_ (i+1, sinal, x, den, num)) - (soma_(i, sinal, x, den, num)) < 0.1) do
	begin
	    soma := soma_(i, sinal, x, den, num);
		i := i + 1;
	end;
	if i = 15 then
		writeln('MAXIMO ATINGIDO')
	else
		writeln (soma:0:2);
end.
