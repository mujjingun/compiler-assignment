# C- Compilation to SPIM Code
# File: test_files/test2.asm
.align 2
.globl main

main:
# set frame pointer
move $fp,$sp
# push the return address
addiu $sp,$sp,-4
sw $ra,0($sp)

# allocate storage for 'locA'
addiu $sp,$sp,-4

# allocate storage for 'locB'
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
