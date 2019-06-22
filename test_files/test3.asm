# C- Compilation to SPIM Code
# Source File: test_files/test3.asm
.align 2
.globl main

exp:
# set frame pointer
move $fp,$sp
# push the return address
addiu $sp,$sp,-4
sw $ra,0($sp)

addiu $sp,$sp,-4 # allocate locals

addiu $t0, $fp, -8
li $t1, 1
sw $t1, 0($t0)
$_L0: # loop
# evaluate the loop condition
lw $t0, 4($fp)
li $t1, 0
slt $t0, $t1, $t0
andi $t0, $t0, 0x00ff
# exit if the condition is false
beq $t0,$0,$_L1

# loop body
addiu $sp,$sp,0 # allocate locals

addiu $t0, $fp, -8
lw $t1, -8($fp)
lw $t2, 8($fp)
mult $t1, $t2
mflo $t1
sw $t1, 0($t0)
addiu $t0, $fp, 4
lw $t1, 4($fp)
li $t2, 1
subu $t1, $t1, $t2
sw $t1, 0($t0)
addiu $sp,$sp,0 # free locals

j $_L0 # loop
$_L1: # loop exit
lw $t0, -8($fp)
move $v0, $t0 # set return value
addiu $sp,$sp,4 # free locals


# restore return address
lw $ra,-4($fp)
# copy the fp to the sp
move $sp,$fp
# load the control link into the fp
lw $fp,0($fp)
# jump to the return address
j $ra

main:
# set frame pointer
move $fp,$sp
# push the return address
addiu $sp,$sp,-4
sw $ra,0($sp)

addiu $sp,$sp,0 # allocate locals

li $t0, 0
li $t1, 2
subu $t0, $t0, $t1
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
li $t0, 10
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 1
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal exp
addiu $sp,$sp,12

move $t0,$v0
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

move $t0,$v0
li $t0, 0
li $t1, 2
subu $t0, $t0, $t1
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
li $t0, 11
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 1
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal exp
addiu $sp,$sp,12

move $t0,$v0
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

move $t0,$v0
li $t0, 0
li $t1, 2
subu $t0, $t0, $t1
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
li $t0, 12
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 1
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal exp
addiu $sp,$sp,12

move $t0,$v0
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

move $t0,$v0
addiu $sp,$sp,0 # free locals


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

.data
_Newline: .asciiz "\n"
# End of code.
