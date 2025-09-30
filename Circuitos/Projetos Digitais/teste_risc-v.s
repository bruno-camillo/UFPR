# comentario 
.section .text
.globl _start
_start:
    li a0, 5          # carrega o valor 5 em a0
    li a1, 10         # carrega o valor 10 em a1
    add a2, a0, a1    # soma a0 e a1, resultado em a2
    sub a3, a1, a0    # subtrai a0 de a1, resultado em a3
    mul a4, a0, a1    # multiplica a0 por a1, resultado em a4
    div a5, a1, a0    # divide a1 por a0, resultado em a5