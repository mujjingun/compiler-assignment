# C- Compilation to SPIM Code
# File: test_files/test.asm
.align 2
.globl main

f:
# set frame pointer
move $fp,$sp
# push the return address
addiu $sp,$sp,-4
sw $ra,0($sp)


# restore return address
lw $ra,-4($fp)
# copy the fp to the sp
move $sp,$fp
# load the control link into the fp
lw $fp,0($fp)
# jump to the return address
j $ra

func:
# set frame pointer
move $fp,$sp
# push the return address
addiu $sp,$sp,-4
sw $ra,0($sp)

# allocate storage for 'a'
addiu $sp,$sp,-4

# allocate storage for 'i'
addiu $sp,$sp,-4

# evaluate the condition to temp register 0
# branch to else if the condition is false
beq $t0,$0,$_L0

# if block
# allocate storage for 'second'
addiu $sp,$sp,-4

# allocate storage for 'third'
addiu $sp,$sp,-4

# jump to end
j $_L1

# else
$_L0:
# end of if statement
$_L1:

# evaluate the condition to temp register 0
# branch to else if the condition is false
beq $t0,$0,$_L2

# if block
# allocate storage for 'fourth'
addiu $sp,$sp,-4

# allocate storage for 'fifth'
addiu $sp,$sp,-4

# jump to end
j $_L3

# else
$_L2:
# end of if statement
$_L3:


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

# allocate storage for 'tmp'
addiu $sp,$sp,-4


# restore return address
lw $ra,-4($fp)
# copy the fp to the sp
move $sp,$fp
# load the control link into the fp
lw $fp,0($fp)
# jump to the return address
j $ra

# End of code.
