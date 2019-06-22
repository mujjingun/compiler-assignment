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

addiu $sp,$sp,-8 # allocate locals

addiu $t0, $fp, -28
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal input
addiu $sp,$sp,4

move $t1,$v0
sw $t1, 0($t0)
li $t1, 2
sll $t1,$t1,2
addu $t0, $fp, $t1
addiu $t0, $fp, -24
lw $t1, -28($fp)
sw $t1, 0($t0)
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

move $t0,$v0
addiu $sp,$sp,8 # free locals


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
