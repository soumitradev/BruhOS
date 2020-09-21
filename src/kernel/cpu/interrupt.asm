section .text
[extern isr_handler]

; Common handler for the isrs
isr_common_format:
    pushall
    mov ax, ds
    push rax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop rax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popall
    add esp, 8
    sti
    iretq

; Define isrs
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

; Handle each isr
isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_common_format


isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_format


isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common_format


isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_common_format


isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_common_format


isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_common_format


isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_common_format


isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_common_format


isr8:
    cli
    push byte 8
    jmp isr_common_format


isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_common_format


isr10:
    cli
    push byte 10
    jmp isr_common_format


isr11:
    cli
    push byte 11
    jmp isr_common_format


isr12:
    cli
    push byte 12
    jmp isr_common_format


isr13:
    cli
    push byte 13
    jmp isr_common_format


isr14:
    cli
    push byte 14
    jmp isr_common_format


isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_common_format


isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_common_format


isr17:
    cli
    push byte 0
    push byte 17
    jmp isr_common_format


isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_common_format


isr19:
    cli
    push byte 0
    push byte 19
    jmp isr_common_format


isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_common_format


isr21:
    cli
    push byte 0
    push byte 21
    jmp isr_common_format


isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_common_format


isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_common_format


isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_common_format


isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_common_format


isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_common_format


isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_common_format


isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_common_format


isr29:
    cli
    push byte 0
    push byte 29
    jmp isr_common_format


isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_common_format


isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_common_format
