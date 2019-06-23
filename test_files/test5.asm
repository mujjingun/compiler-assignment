# C- Compilation to SPIM Code
# Source File: test_files/test5.asm
.align 2
.globl main

main:
# set frame pointer
move $fp,$sp
# push the return address
addiu $sp,$sp,-4
sw $ra,0($sp)

addiu $sp,$sp,-24 # allocate locals

addiu $t0, $fp, -28
addiu $sp,$sp,-40
sw $t0,0($sp)
sw $t1,4($sp)
sw $t2,8($sp)
sw $t3,12($sp)
sw $t4,16($sp)
sw $t5,20($sp)
sw $t6,24($sp)
sw $t7,28($sp)
sw $t8,32($sp)
sw $t9,36($sp)
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal input
addiu $sp,$sp,4

lw $t0,0($sp)
lw $t1,4($sp)
lw $t2,8($sp)
lw $t3,12($sp)
lw $t4,16($sp)
lw $t5,20($sp)
lw $t6,24($sp)
lw $t7,28($sp)
lw $t8,32($sp)
lw $t9,36($sp)
addiu $sp,$sp,40
move $t1,$v0
sw $t1, 0($t0)
li $t1, 2
sll $t1,$t1,2
addu $t0, $fp, $t1
addiu $t0, $fp, -24
lw $t1, -28($fp)
sw $t1, 0($t0)
addiu $sp,$sp,-40
sw $t0,0($sp)
sw $t1,4($sp)
sw $t2,8($sp)
sw $t3,12($sp)
sw $t4,16($sp)
sw $t5,20($sp)
sw $t6,24($sp)
sw $t7,28($sp)
sw $t8,32($sp)
sw $t9,36($sp)
li $t1, 2
sll $t1,$t1,2
addu $t0, $fp, $t1
lw $t0, -24($fp)
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

lw $t0,0($sp)
lw $t1,4($sp)
lw $t2,8($sp)
lw $t3,12($sp)
lw $t4,16($sp)
lw $t5,20($sp)
lw $t6,24($sp)
lw $t7,28($sp)
lw $t8,32($sp)
lw $t9,36($sp)
addiu $sp,$sp,40
move $t0,$v0
addiu $sp,$sp,24 # free locals


# restore return address
lw $ra,-4($fp)
# copy the fp to the sp
move $sp,$fp
# load the control link into the fp
lw $fp,0($fp)
# jump to the return address
j $ra

output:
li $v0,1
lw $a0,4($sp)
syscall
li $v0,4
la $a0,_Newline
syscall
j $ra

input:
li $v0,5
syscall
j $ra

.data
_Newline: .asciiz "\n"
# End of code.
