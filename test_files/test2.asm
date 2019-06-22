# C- Compilation to SPIM Code
# Source File: test_files/test2.asm
.align 2
.globl main

main:
# set frame pointer
move $fp,$sp
# push the return address
addiu $sp,$sp,-4
sw $ra,0($sp)

addiu $sp,$sp,-4 # allocate locals

addiu $sp,$sp,-4 # allocate locals

li $t0, 1
li $t1, 2
addu $t0, $t0, $t1
sw $t0, -8($fp)
lw $t0, -12($fp)
la $t1, glo
sw $t0, 0($t1)
addiu $sp,$sp,4 # free locals

addiu $sp,$sp,4 # free locals


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
lw $a0,0($sp)
syscall
lw $fp,0($fp)
j $ra

.data
glo: .word 1
# End of code.
