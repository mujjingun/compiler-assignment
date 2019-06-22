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
lw $t1, 4($fp)
li $t2, 1
subu $t1, $t1, $t2
addiu $sp,$sp,-4
sw $t1,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal fact
addiu $sp,$sp,8

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

li $t0, 5
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal fact
addiu $sp,$sp,8

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
