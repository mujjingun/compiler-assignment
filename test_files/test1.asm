# C- Compilation to SPIM Code
# File: test_files/test1.asm
.align 2
.globl main

f:
# set frame pointer
move $fp,$sp
# push the return address
addiu $sp,$sp,-4
sw $ra,0($sp)


# restore return address
lw $ra,4($fp)
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


# restore return address
lw $ra,4($fp)
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
lw $ra,4($fp)
# copy the fp to the sp
move $sp,$fp
# load the control link into the fp
lw $fp,0($fp)
# jump to the return address
j $ra

# End of code.
