# C- Compilation to SPIM Code
# Source File: test_files/test4.asm
.align 2
.globl main

fact:
# set frame pointer
move $fp,$sp
# push the return address
addiu $sp,$sp,-4
sw $ra,0($sp)

addiu $sp,$sp,0 # allocate locals

# evaluate the condition
lw $t0, 4($fp)
li $t1, 1
xor $t0, $t0, $t1
sltu $t0, $t0, 1
andi $t0, $t0, 0x00ff
# branch to else if the condition is false
beq $t0,$0,$_L0

# if block
li $t0, 1
move $v0, $t0 # set return value
# jump to end
j $_L1

# else
$_L0:
lw $t0, 4($fp)
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
lw $t1, 4($fp)
li $t2, 1
subu $t1, $t1, $t2
addiu $sp,$sp,-4
sw $t1,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal fact
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
move $t1,$v0
mult $t0, $t1
mflo $t0
move $v0, $t0 # set return value
# end of if statement
$_L1:

addiu $sp,$sp,0 # free locals


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
li $t0, 5
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal fact
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

input:
li $v0,5
syscall
j $ra

.data
_Newline: .asciiz "\n"
# End of code.
