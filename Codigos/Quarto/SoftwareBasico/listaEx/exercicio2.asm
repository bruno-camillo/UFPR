.section .data
    CLIENTES:
        .quad 5000, 0 
        .quad 1200, 2 
        .quad -300, 1 
        .quad 8000, 5 
        .quad 900, 0 
        .quad 0, 3 

    TAM_CLIENTE = 16
    NUM_CLIENTES = 6

    QTD_APTOS: .quad 0
    QTD_ANALISE: .quad 0
    QTD_NEGADOS: .quad 0

.section .text
.global _start
_start:
    movq $1, %r8

inicio:
    cmp %r8, $11
    jg fim

if_1:
    cmp $3, CLIENTES(, %r8, 8)
    jl elseIf_1
    addq $1, QTD_NEGADOS
    addq $2, %r8
    jmp inicio

elseIf_1:
    subq $1, %r8
    cmp %r8, $0
    jge elseIf_2
    addq $1, QTD_NEGADOS
    addq $3, %r8
    jmp inicio

elseIf_2: