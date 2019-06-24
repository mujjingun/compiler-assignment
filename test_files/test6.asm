# C- Compilation to SPIM Code
# Source File: test_files/test6.asm
.align 2
.globl main

print:
# set frame pointer
move  $fp,$sp
# push the return address
addiu $sp,$sp,-4
sw    $ra,0($sp)

addiu $sp,$sp,-4 # allocate locals

addiu $t0, $fp, -8
li    $t1, 0
sw    $t1, 0($t0)
$_L0: # loop
# evaluate the loop condition
lw    $t0, -8($fp)
li    $t1, 10
slt   $t0, $t0, $t1
andi  $t0, $t0, 0x00ff
# exit if the condition is false
beq   $t0,$0,$_L1

# loop body
addiu $sp,$sp,0 # allocate locals

addiu $sp,$sp,-40
sw    $t0,0($sp)
sw    $t1,4($sp)
sw    $t2,8($sp)
sw    $t3,12($sp)
sw    $t4,16($sp)
sw    $t5,20($sp)
sw    $t6,24($sp)
sw    $t7,28($sp)
sw    $t8,32($sp)
sw    $t9,36($sp)
lw    $t1, -8($fp)
sll   $t1,$t1,2
lw    $t0, 4($fp)
addu  $t0, $t0, $t1
lw    $t0, 0($t0)
addiu $sp,$sp,-4
sw    $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw    $fp,0($sp) # push control link
jal   output
addiu $sp,$sp,8
lw    $t0,0($sp)
lw    $t1,4($sp)
lw    $t2,8($sp)
lw    $t3,12($sp)
lw    $t4,16($sp)
lw    $t5,20($sp)
lw    $t6,24($sp)
lw    $t7,28($sp)
lw    $t8,32($sp)
lw    $t9,36($sp)
addiu $sp,$sp,40
move  $t0,$v0
addiu $t0, $fp, -8
lw    $t1, -8($fp)
li    $t2, 1
addu   $t1, $t1, $t2
sw    $t1, 0($t0)
addiu $sp,$sp,0 # free locals

j     $_L0 # loop
$_L1: # loop exit
addiu $sp,$sp,4 # free locals


# restore return address
lw    $ra,-4($fp)
# copy the fp to the sp
move  $sp,$fp
# load the control link into the fp
lw    $fp,0($fp)
# jump to the return address
j     $ra

minloc:
# set frame pointer
move  $fp,$sp
# push the return address
addiu $sp,$sp,-4
sw    $ra,0($sp)

addiu $sp,$sp,-12 # allocate locals

addiu $t0, $fp, -16
lw    $t1, 8($fp)
sw    $t1, 0($t0)
addiu $t0, $fp, -12
lw    $t2, 8($fp)
sll   $t2,$t2,2
lw    $t1, 12($fp)
addu  $t1, $t1, $t2
lw    $t1, 0($t1)
sw    $t1, 0($t0)
addiu $t0, $fp, -8
lw    $t1, 8($fp)
li    $t2, 1
addu   $t1, $t1, $t2
sw    $t1, 0($t0)
$_L2: # loop
# evaluate the loop condition
lw    $t0, -8($fp)
lw    $t1, 4($fp)
slt   $t0, $t0, $t1
andi  $t0, $t0, 0x00ff
# exit if the condition is false
beq   $t0,$0,$_L3

# loop body
addiu $sp,$sp,0 # allocate locals

# evaluate the condition
lw    $t1, -8($fp)
sll   $t1,$t1,2
lw    $t0, 12($fp)
addu  $t0, $t0, $t1
lw    $t0, 0($t0)
lw    $t1, -12($fp)
slt   $t0, $t0, $t1
andi  $t0, $t0, 0x00ff
# branch to else if the condition is false
beq   $t0,$0,$_L4

# if block
addiu $sp,$sp,0 # allocate locals

addiu $t0, $fp, -12
lw    $t2, -8($fp)
sll   $t2,$t2,2
lw    $t1, 12($fp)
addu  $t1, $t1, $t2
lw    $t1, 0($t1)
sw    $t1, 0($t0)
addiu $t0, $fp, -16
lw    $t1, -8($fp)
sw    $t1, 0($t0)
addiu $sp,$sp,0 # free locals

# jump to end
j     $_L5

# else
$_L4:
# end of if statement
$_L5:

addiu $t0, $fp, -8
lw    $t1, -8($fp)
li    $t2, 1
addu   $t1, $t1, $t2
sw    $t1, 0($t0)
addiu $sp,$sp,0 # free locals

j     $_L2 # loop
$_L3: # loop exit
lw    $t0, -16($fp)
move  $v0, $t0 # set return value
# restore return address
lw    $ra,-4($fp)
# copy the fp to the sp
move  $sp,$fp
# load the control link into the fp
lw    $fp,0($fp)
# jump to the return address
j     $ra

addiu $sp,$sp,12 # free locals


# restore return address
lw    $ra,-4($fp)
# copy the fp to the sp
move  $sp,$fp
# load the control link into the fp
lw    $fp,0($fp)
# jump to the return address
j     $ra

sort:
# set frame pointer
move  $fp,$sp
# push the return address
addiu $sp,$sp,-4
sw    $ra,0($sp)

addiu $sp,$sp,-8 # allocate locals

addiu $t0, $fp, -8
lw    $t1, 8($fp)
sw    $t1, 0($t0)
$_L6: # loop
# evaluate the loop condition
lw    $t0, -8($fp)
lw    $t1, 4($fp)
li    $t2, 1
subu   $t1, $t1, $t2
slt   $t0, $t0, $t1
andi  $t0, $t0, 0x00ff
# exit if the condition is false
beq   $t0,$0,$_L7

# loop body
addiu $sp,$sp,-4 # allocate locals

addiu $t0, $fp, -12
addiu $sp,$sp,-40
sw    $t0,0($sp)
sw    $t1,4($sp)
sw    $t2,8($sp)
sw    $t3,12($sp)
sw    $t4,16($sp)
sw    $t5,20($sp)
sw    $t6,24($sp)
sw    $t7,28($sp)
sw    $t8,32($sp)
sw    $t9,36($sp)
lw    $t1, 12($fp)
addiu $sp,$sp,-4
sw    $t1,0($sp) # push argument 0
lw    $t1, -8($fp)
addiu $sp,$sp,-4
sw    $t1,0($sp) # push argument 1
lw    $t1, 4($fp)
addiu $sp,$sp,-4
sw    $t1,0($sp) # push argument 2
addiu $sp,$sp,-4
sw    $fp,0($sp) # push control link
jal   minloc
addiu $sp,$sp,16
lw    $t0,0($sp)
lw    $t1,4($sp)
lw    $t2,8($sp)
lw    $t3,12($sp)
lw    $t4,16($sp)
lw    $t5,20($sp)
lw    $t6,24($sp)
lw    $t7,28($sp)
lw    $t8,32($sp)
lw    $t9,36($sp)
addiu $sp,$sp,40
move  $t1,$v0
sw    $t1, 0($t0)
addiu $t0, $fp, -16
lw    $t2, -12($fp)
sll   $t2,$t2,2
lw    $t1, 12($fp)
addu  $t1, $t1, $t2
lw    $t1, 0($t1)
sw    $t1, 0($t0)
lw    $t1, -12($fp)
sll   $t1,$t1,2
lw    $t0, 12($fp)
addu  $t0, $t0, $t1
lw    $t2, -8($fp)
sll   $t2,$t2,2
lw    $t1, 12($fp)
addu  $t1, $t1, $t2
lw    $t1, 0($t1)
sw    $t1, 0($t0)
lw    $t1, -8($fp)
sll   $t1,$t1,2
lw    $t0, 12($fp)
addu  $t0, $t0, $t1
lw    $t1, -16($fp)
sw    $t1, 0($t0)
addiu $t0, $fp, -8
lw    $t1, -8($fp)
li    $t2, 1
addu   $t1, $t1, $t2
sw    $t1, 0($t0)
addiu $sp,$sp,4 # free locals

j     $_L6 # loop
$_L7: # loop exit
addiu $sp,$sp,8 # free locals


# restore return address
lw    $ra,-4($fp)
# copy the fp to the sp
move  $sp,$fp
# load the control link into the fp
lw    $fp,0($fp)
# jump to the return address
j     $ra

main:
# set frame pointer
move  $fp,$sp
# push the return address
addiu $sp,$sp,-4
sw    $ra,0($sp)

addiu $sp,$sp,-4 # allocate locals

addiu $t0, $fp, -8
li    $t1, 0
sw    $t1, 0($t0)
$_L8: # loop
# evaluate the loop condition
lw    $t0, -8($fp)
li    $t1, 10
slt   $t0, $t0, $t1
andi  $t0, $t0, 0x00ff
# exit if the condition is false
beq   $t0,$0,$_L9

# loop body
addiu $sp,$sp,0 # allocate locals

lw    $t1, -8($fp)
sll   $t1,$t1,2
la    $t0, x
addu  $t0, $t0, $t1
addiu $sp,$sp,-40
sw    $t0,0($sp)
sw    $t1,4($sp)
sw    $t2,8($sp)
sw    $t3,12($sp)
sw    $t4,16($sp)
sw    $t5,20($sp)
sw    $t6,24($sp)
sw    $t7,28($sp)
sw    $t8,32($sp)
sw    $t9,36($sp)
addiu $sp,$sp,-4
sw    $fp,0($sp) # push control link
jal   input
addiu $sp,$sp,4
lw    $t0,0($sp)
lw    $t1,4($sp)
lw    $t2,8($sp)
lw    $t3,12($sp)
lw    $t4,16($sp)
lw    $t5,20($sp)
lw    $t6,24($sp)
lw    $t7,28($sp)
lw    $t8,32($sp)
lw    $t9,36($sp)
addiu $sp,$sp,40
move  $t1,$v0
sw    $t1, 0($t0)
addiu $t0, $fp, -8
lw    $t1, -8($fp)
li    $t2, 1
addu   $t1, $t1, $t2
sw    $t1, 0($t0)
addiu $sp,$sp,0 # free locals

j     $_L8 # loop
$_L9: # loop exit
addiu $sp,$sp,-40
sw    $t0,0($sp)
sw    $t1,4($sp)
sw    $t2,8($sp)
sw    $t3,12($sp)
sw    $t4,16($sp)
sw    $t5,20($sp)
sw    $t6,24($sp)
sw    $t7,28($sp)
sw    $t8,32($sp)
sw    $t9,36($sp)
la    $t0, x
addiu $sp,$sp,-4
sw    $t0,0($sp) # push argument 0
li    $t0, 0
addiu $sp,$sp,-4
sw    $t0,0($sp) # push argument 1
li    $t0, 10
addiu $sp,$sp,-4
sw    $t0,0($sp) # push argument 2
addiu $sp,$sp,-4
sw    $fp,0($sp) # push control link
jal   sort
addiu $sp,$sp,16
lw    $t0,0($sp)
lw    $t1,4($sp)
lw    $t2,8($sp)
lw    $t3,12($sp)
lw    $t4,16($sp)
lw    $t5,20($sp)
lw    $t6,24($sp)
lw    $t7,28($sp)
lw    $t8,32($sp)
lw    $t9,36($sp)
addiu $sp,$sp,40
move  $t0,$v0
addiu $sp,$sp,-40
sw    $t0,0($sp)
sw    $t1,4($sp)
sw    $t2,8($sp)
sw    $t3,12($sp)
sw    $t4,16($sp)
sw    $t5,20($sp)
sw    $t6,24($sp)
sw    $t7,28($sp)
sw    $t8,32($sp)
sw    $t9,36($sp)
la    $t0, x
addiu $sp,$sp,-4
sw    $t0,0($sp) # push argument 0
addiu $sp,$sp,-4
sw    $fp,0($sp) # push control link
jal   print
addiu $sp,$sp,8
lw    $t0,0($sp)
lw    $t1,4($sp)
lw    $t2,8($sp)
lw    $t3,12($sp)
lw    $t4,16($sp)
lw    $t5,20($sp)
lw    $t6,24($sp)
lw    $t7,28($sp)
lw    $t8,32($sp)
lw    $t9,36($sp)
addiu $sp,$sp,40
move  $t0,$v0
addiu $sp,$sp,4 # free locals


# restore return address
lw    $ra,-4($fp)
# copy the fp to the sp
move  $sp,$fp
# load the control link into the fp
lw    $fp,0($fp)
# jump to the return address
j     $ra

output:
li    $v0,1
lw    $a0,4($sp)
syscall
li    $v0,4
la    $a0,_Newline
syscall
j     $ra

input:
li    $v0,5
syscall
j     $ra

.data
_Newline: .asciiz "\n"
x: .word 10
# End of code.
