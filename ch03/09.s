  .globl dw_short1
  .type dw_short1, @function
dw_short1:
  .cfi_startproc
  movw %di, %ax
  leaq (,%rdi,2), %rsi
  andq $0xFFFF, %rsi
  movw $9, %cx
  idivq %rcx
  movw %ax, %dx
  movw %di, %ax
.dw_short1.loop.1:
  leaq 5(%rax, %rdx), %rax
  andq $0xFFFF, %rax
  decw %si
  jg .dw_short1.loop.1
  ret
  .cfi_endproc

  .globl lname
  .type lname, @function
lname: # <letter> for word using switch: jump table
  .cfi_startproc
  movl $26, %esi
  subl $65, %edi # uppercase
  cmpl %esi, %edi
  jb .lname.ret.name
  subq $32, %rdi # lowercase
  cmpl %esi, %edi
  cmova %esi, %edi
.lname.ret.name:
  # movq .lname.map.name(%rip,%rdi,8), %rdi # For whatever reasons, this is not working
  # movq (%rax), %rdi
  leaq (,%rdi,8), %rdi
  leaq .lname.map.name(%rip), %rax
  movq (%rax,%rdi), %rax
  ret
  .cfi_endproc
  
  .data
  .align 8
  .size .lname.map.name, 8*27
.lname.map.name:
  .quad .L.letter.A # A
  .quad .L.letter.B # B
  .quad .L.letter.C # C
  .quad .L.letter.D # D
  .quad .L.letter.E # E
  .quad .L.letter.F # F
  .quad .L.letter.G # G
  .quad .L.letter.H # H
  .quad .L.letter.I # I
  .quad .L.letter.J # J
  .quad .L.letter.K # K
  .quad .L.letter.L # L
  .quad .L.letter.M # M
  .quad .L.letter.N # N
  .quad .L.letter.O # O
  .quad .L.letter.P # P
  .quad .L.letter.Q # Q
  .quad .L.letter.R # R
  .quad .L.letter.S # S
  .quad .L.letter.T # T
  .quad .L.letter.U # U
  .quad .L.letter.V # V
  .quad .L.letter.W # W
  .quad .L.letter.X # X
  .quad .L.letter.Y # Y
  .quad .L.letter.Z # Z
  .quad .L.letter._ # NaL  Not A Letter

  .globl author
  .type author, @object
author:
  .quad .author_name
  .long 23
  .size author, 12

  .section .rodata.str1.1, "aMS", @progbits, 1
  .type .author_name, @object
.author_name:
  .asciz "Simon Nganga"
  .size .author_name, 13

  .type .L.letter.A, @object
.L.letter.A:
  .asciz "apple"
  .size .L.letter.A, 6

  .type .L.letter.B, @object
.L.letter.B:
  .asciz "ball"
  .size .L.letter.B, 5

  .type .L.letter.C, @object
.L.letter.C:
  .asciz "cat"
  .size .L.letter.C, 4

  .type .L.letter.D, @object
.L.letter.D:
  .asciz "dog"
  .size .L.letter.D, 4

  .type .L.letter.E, @object
.L.letter.E:
  .asciz "elephant"
  .size .L.letter.E, 9

  .type .L.letter.F, @object
.L.letter.F:
  .asciz "fish"
  .size .L.letter.F, 5

  .type .L.letter.G, @object
.L.letter.G:
  .asciz "glue"
  .size .L.letter.G, 5

  .type .L.letter.H, @object
.L.letter.H:
  .asciz "house"
  .size .L.letter.H, 6

  .type .L.letter.I, @object
.L.letter.I:
  .asciz "ink"
  .size .L.letter.I, 4

  .type .L.letter.J, @object
.L.letter.J:
  .asciz "jet"
  .size .L.letter.J, 4

  .type .L.letter.K, @object
.L.letter.K:
  .asciz "kettle"
  .size .L.letter.K, 7

  .type .L.letter.L, @object
.L.letter.L:
  .asciz "lumberjack"
  .size .L.letter.L, 11

  .type .L.letter.M, @object
.L.letter.M:
  .asciz "milk"
  .size .L.letter.M, 5

  .type .L.letter.N, @object
.L.letter.N:
  .asciz "nose"
  .size .L.letter.N, 5

  .type .L.letter.O, @object
.L.letter.O:
  .asciz "oil"
  .size .L.letter.O, 4

  .type .L.letter.P, @object
.L.letter.P:
  .asciz "pet"
  .size .L.letter.P, 4

  .type .L.letter.Q, @object
.L.letter.Q:
  .asciz "quil"
  .size .L.letter.Q, 5

  .type .L.letter.R, @object
.L.letter.R:
  .asciz "rust"
  .size .L.letter.R, 5

  .type .L.letter.S, @object
.L.letter.S:
  .asciz "swim"
  .size .L.letter.S, 5

  .type .L.letter.T, @object
.L.letter.T:
  .asciz "tent"
  .size .L.letter.T, 5

  .type .L.letter.U, @object
.L.letter.U:
  .asciz "uncle"
  .size .L.letter.U, 6

  .type .L.letter.V, @object
.L.letter.V:
  .asciz "vehicle"
  .size .L.letter.V, 8

  .type .L.letter.W, @object
.L.letter.W:
  .asciz "well"
  .size .L.letter.W, 5

  .type .L.letter.X, @object
.L.letter.X:
  .asciz "xerophone"
  .size .L.letter.X, 10

  .type .L.letter.Y, @object
.L.letter.Y:
  .asciz "yawn"
  .size .L.letter.Y, 5

  .type .L.letter.Z, @object
.L.letter.Z:
  .asciz "zebra"
  .size .L.letter.Z, 6

  .type .L.letter._, @object
.L.letter._:
  .asciz "-"
  .size .L.letter._, 2

