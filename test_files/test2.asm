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

addiu $sp,$sp,0 # allocate locals

li $t0, 1
li $t1, 2
slt $t0, $t0, $t1
andi $t0, $t0, 0x00ff
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 1
slt $t0, $t0, $t1
andi $t0, $t0, 0x00ff
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 0
slt $t0, $t0, $t1
andi $t0, $t0, 0x00ff
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 2
slt $t0, $t1, $t0
xori $t0, $t0, 0x1
andi $t0, $t0, 0x00ff
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 1
slt $t0, $t1, $t0
xori $t0, $t0, 0x1
andi $t0, $t0, 0x00ff
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 0
slt $t0, $t1, $t0
xori $t0, $t0, 0x1
andi $t0, $t0, 0x00ff
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 2
slt $t0, $t1, $t0
andi $t0, $t0, 0x00ff
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 1
slt $t0, $t1, $t0
andi $t0, $t0, 0x00ff
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 0
slt $t0, $t1, $t0
andi $t0, $t0, 0x00ff
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 2
slt $t0, $t0, $t1
xori $t0, $t0, 0x1
andi $t0, $t0, 0x00ff
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 1
slt $t0, $t0, $t1
xori $t0, $t0, 0x1
andi $t0, $t0, 0x00ff
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 0
slt $t0, $t0, $t1
xori $t0, $t0, 0x1
andi $t0, $t0, 0x00ff
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 2
xor $t0, $t0, $t1
sltu $t0, $t0, 1
andi $t0, $t0, 0x00ff
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 1
xor $t0, $t0, $t1
sltu $t0, $t0, 1
andi $t0, $t0, 0x00ff
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 0
xor $t0, $t0, $t1
sltu $t0, $t0, 1
andi $t0, $t0, 0x00ff
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 2
xor $t0, $t0, $t1
sltu $t0, $0, $t0
andi $t0, $t0, 0x00ff
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 1
xor $t0, $t0, $t1
sltu $t0, $0, $t0
andi $t0, $t0, 0x00ff
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 0
xor $t0, $t0, $t1
sltu $t0, $0, $t0
andi $t0, $t0, 0x00ff
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 2
addu $t0, $t0, $t1
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 1
addu $t0, $t0, $t1
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 0
addu $t0, $t0, $t1
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 2
subu $t0, $t0, $t1
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 1
subu $t0, $t0, $t1
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 0
subu $t0, $t0, $t1
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 2
mult $t0, $t1
mflo $t0
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 1
mult $t0, $t1
mflo $t0
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 0
mult $t0, $t1
mflo $t0
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 2
div $0,$t0,$t1
mfhi $t0
mflo $t0
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 1
div $0,$t0,$t1
mfhi $t0
mflo $t0
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

li $t0, 1
li $t1, 0
div $0,$t0,$t1
mfhi $t0
mflo $t0
addiu $sp,$sp,-4
sw $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw $fp,0($sp) # push control link
jal output
addiu $sp,$sp,8

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
j $ra

.data
glo: .word 1
# End of code.
