section .data
four:   dq 4.0

section .text
global mandelbrot
    ; registers to preserve (if used) - RBP, RBX, and R12–R15
    ; rdi - pPixelBuffer
    ; rsi - width
    ; rdx - height
    ; xmm0 - x
    ; xmm1 - y
    ; xmm2 - step
mandelbrot:
    push rbp
    mov rbp, rsp
    mov rax, rsi
    movsd xmm9, [four]
    movsd xmm8, xmm0
preCalculate:
    mov r9, 0x000000
    xorps xmm3, xmm3
    xorps xmm4, xmm4
calculate:
    movsd xmm5, xmm3
    mulsd xmm5, xmm5
    movsd xmm6, xmm4
    mulsd xmm6, xmm6
    movsd xmm7, xmm5
    addsd xmm7, xmm6
    ucomisd xmm7, xmm9
    jnb nextPixel
nextN:
    mulsd xmm4, xmm3
    addsd xmm4, xmm4
    addsd xmm4, xmm1
    movsd xmm3, xmm5
    subsd xmm3, xmm6
    addsd xmm3, xmm0
    add r9, 0x010101
    cmp r9, 0xffffff
    jne calculate
nextPixel:
    mov [rdi], r9
    add rdi, 4
    addsd xmm0, xmm2
    dec rax
    jnz preCalculate
nextLine:
    mov rax, rsi
    movsd xmm0, xmm8
    addsd xmm1, xmm2
    dec rdx
    jnz preCalculate
end:
    mov rsp, rbp
    pop rbp
    ret