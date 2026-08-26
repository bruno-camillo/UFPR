xor r1, r1 ; r1 (i) = 0
xor r2, r2 ; r2 (k) = 0
xor r3, r3 ; inicio do loop 1
xor r0, r0 
addi 5     ; r0 = 5
add r0, r0 ; r0 = 5 + 5 = 10
sub r0, r1 ; r0 = 10 - i
add r3, r0 ; r3 = 10 - i
xor r0, r0 ; r0 = 0
addi 5
mul r0, r0
addi 4 ; r0 = Endereço fim loop 1
brzr r3, r0
xor r0, r0
addi 5
addi 3
mul r0, r0
addi -1 ; r0 = 63
add r0, r1 ; r0 = 63 + i = &A[i]
st r2, r0 ; A[i] = k
inc r2 ; k++
addi 5
addi 5 ; &A[i] + 10 = &B[i]
st r2, r0 ; B[i] = k
inc r2 ; k++
inc r1 ; i++
xor r0, r0
addi 2 ; r0 = 2
jr r0 ; volta pro inicio do loop
xor r1, r1
xor r3, r3 ; inicio do loop 2
xor r0, r0
addi 5
add r0, r0
sub r0, r1
add r3, r0 ; r3 = 10 - i
xor r0, r0
addi 5
addi 3
mul r0, r0
addi -2 ; r0 = Endereço fim loop 2 = 62
brzr r3, r0
xor r0, r0
addi 5
addi 3
mul r0, r0
addi -1 ; r0 = 63
add r0, r1 ; r0 = 60 + i = &A[i]
ld r2, r0 ; r2 = M[&A[i]]
addi 5
addi 5 ; r0 = &B[i]
ld r3, r0 ; r3 = M[&B[i]]
addi 5
addi 5 ; r0 = &R[i]
add r2, r3 ; r2 = A[i] + B[i]
st r2, r0 ; M[&R[i]] = A[i] + B[i]
inc r1 ; i++
xor r0, r0
addi 5
mul r0, r0
addi 5 ; r0 = 30
jr r0 ; volta para o inicio do loop 2
ji 0 ; equivalente ao ebreak
