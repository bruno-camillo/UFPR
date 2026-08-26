xor r1, r1 ; r1 (i) = 0
xor r2, r2 ; r2 (k) = 0
xor r3, r3
xor r0, r0 ; inicio do loop 1
addi 5     ; r0 = 5
add r0, r0 ; r0 = 5 + 5 = 10
sub r0, r1 ; r0 = 10 - i
add r3, r0 ; r3 = 10 - i
xor r0, r0 ; r0 = 0
addi 5
add r0, r0 
add r0, r0 ; r0 = 20
add r0, r0 ; r0 = 40
addi 4     ; r0 = 44
brzr r3, r0
xor r0, r0
addi 5
add r0, r0 ; r0 = 10
add r0, r0 ; r0 = 20
add r0, r0 ; r0 = 40
add r0, r0 ; r0 = 80
addi 6 ; r0 = 86 = &A[0]
add r0, r1 ; r0 = 86 + i = &A[i]
st r2, r0 ; A[i] = k
xor r0, r0
addi 1
add r2, r0 ; k++
addi 4
add r0, r0 ; r0 = 10
add r0, r0 ; r0 = 20
add r0, r0 ; r0 = 40
add r0, r0 ; r0 = 80
addi 6 ; r0 = 86
addi 5
addi 5 ; r0 = &B[0]
add r0, r1 ; r0 = 96 + i = &B[i]
st r2, r0 ; B[i] = k
xor r0, r0
addi 1
add r2, r0 ; k++
add r1, r0 ; i++
addi 2 ; r0 = 3
xor r3, r3
brzr r3, r0 ; volta pro inicio do loop
xor r1, r1
xor r3, r3 ; inicio do loop 2
xor r0, r0
addi 5
add r0, r0
sub r0, r1
add r3, r0 ; r3 = 10 - i
xor r0, r0
addi 5
add r0, r0 ; r0 = 10
add r0, r0 ; . = 20
add r0, r0 ; . = 40
add r0, r0 ; . = 80
addi 5 ; . = 85 (Endereço do ebreak)
brzr r3, r0
xor r0, r0
addi 5
add r0, r0 ; r0 = 10
add r0, r0 ; r0 = 20
add r0, r0 ; r0 = 40
add r0, r0 ; r0 = 80
addi 6 ; r0 = 86 = &A[0]
add r0, r1 ; r0 = 86 + i = &A[i]
ld r2, r0 ; r2 = M[&A[i]]
addi 5
addi 5
ld r3, r0 ; r3 = M[&A[i]]
addi 5
addi 5
add r2, r3 ; r2 = A[i] + B[i]
st r2, r0 
xor r0, r0
addi 1
add r1, r0 ; i++
addi 4
add r0, r0 ; r0 = 10
add r0, r0 
add r0, r0
addi 5 ; r0 = 45
xor r3, r3
brzr r3, r0 ; volta para o inicio do loop 2
ji 0 ; equivalente ao ebreak
