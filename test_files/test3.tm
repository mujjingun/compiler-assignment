# C- Compilation to SPIM Code
# Source File: test_files/test3.tm
.align 2
.globl main

exp:
# set frame pointer
move  $fp,$sp
# push the return address
addiu $sp,$sp,-4
sw    $ra,0($sp)

addiu $sp,$sp,-4 # allocate locals


#     r = 1;
addiu $t0, $fp, -8
li    $t1, 1
sw    $t1, 0($t0)
$_L0: # loop
# evaluate the loop condition

#     while (b > 0) {
move  $t0, $a1
li    $t1, 0
slt   $t0, $t1, $t0
andi  $t0, $t0, 0x00ff
# exit if the condition is false
beq   $t0,$0,$_L1

# loop body
addiu $sp,$sp,0 # allocate locals


#         r = r * a;
addiu $t0, $fp, -8

#         r = r * a;
lw    $t1, -8($fp)
move  $t2, $a0
mult  $t1, $t2
mflo  $t1
sw    $t1, 0($t0)

#         b = b - 1;

#         b = b - 1;
move  $t1, $a1
li    $t2, 1
subu   $t1, $t1, $t2
move $a1, $t1
addiu $sp,$sp,0 # free locals

j     $_L0 # loop
$_L1: # loop exit
lw    $t0, -8($fp)
move  $v0, $t0 # set return value
# restore return address
lw    $ra,-4($fp)
# copy the fp to the sp
move  $sp,$fp
# load the control link into the fp
lw    $fp,0($fp)
# jump to the return address
j     $ra

addiu $sp,$sp,4 # free locals


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

addiu $sp,$sp,0 # allocate locals


#     output(exp(0-2, 10)); /* 1024  */
addiu $sp, $sp,-56
sw    $t0, 0($sp)
sw    $t1, 4($sp)
sw    $t2, 8($sp)
sw    $t3, 12($sp)
sw    $t4, 16($sp)
sw    $t5, 20($sp)
sw    $t6, 24($sp)
sw    $t7, 28($sp)
sw    $t8, 32($sp)
sw    $t9, 36($sp)
sw    $a0, 40($sp)
sw    $a1, 44($sp)
sw    $a2, 48($sp)
sw    $a3, 52($sp)

#     output(exp(0-2, 10)); /* 1024  */
addiu $sp, $sp,-56
sw    $t0, 0($sp)
sw    $t1, 4($sp)
sw    $t2, 8($sp)
sw    $t3, 12($sp)
sw    $t4, 16($sp)
sw    $t5, 20($sp)
sw    $t6, 24($sp)
sw    $t7, 28($sp)
sw    $t8, 32($sp)
sw    $t9, 36($sp)
sw    $a0, 40($sp)
sw    $a1, 44($sp)
sw    $a2, 48($sp)
sw    $a3, 52($sp)

#     output(exp(0-2, 10)); /* 1024  */
li    $t0, 0
li    $t1, 2
subu   $t0, $t0, $t1
li    $t1, 10
move  $a0, $t0
move  $a1, $t1
addiu $sp,$sp,-4
sw    $fp,0($sp) # push control link
jal   exp
sw    $fp,0($sp) # pop control link
addiu $sp,$sp,4
lw    $t0, 0($sp)
lw    $t1, 4($sp)
lw    $t2, 8($sp)
lw    $t3, 12($sp)
lw    $t4, 16($sp)
lw    $t5, 20($sp)
lw    $t6, 24($sp)
lw    $t7, 28($sp)
lw    $t8, 32($sp)
lw    $t9, 36($sp)
lw    $a0, 40($sp)
lw    $a1, 44($sp)
lw    $a2, 48($sp)
lw    $a3, 52($sp)
addiu $sp,$sp,56
move  $t0,$v0
move  $a0, $t0
addiu $sp,$sp,-4
sw    $fp,0($sp) # push control link
jal   output
sw    $fp,0($sp) # pop control link
addiu $sp,$sp,4
lw    $t0, 0($sp)
lw    $t1, 4($sp)
lw    $t2, 8($sp)
lw    $t3, 12($sp)
lw    $t4, 16($sp)
lw    $t5, 20($sp)
lw    $t6, 24($sp)
lw    $t7, 28($sp)
lw    $t8, 32($sp)
lw    $t9, 36($sp)
lw    $a0, 40($sp)
lw    $a1, 44($sp)
lw    $a2, 48($sp)
lw    $a3, 52($sp)
addiu $sp,$sp,56
move  $t0,$v0

#     output(exp(0-2, 11)); /* -2048 */
addiu $sp, $sp,-56
sw    $t0, 0($sp)
sw    $t1, 4($sp)
sw    $t2, 8($sp)
sw    $t3, 12($sp)
sw    $t4, 16($sp)
sw    $t5, 20($sp)
sw    $t6, 24($sp)
sw    $t7, 28($sp)
sw    $t8, 32($sp)
sw    $t9, 36($sp)
sw    $a0, 40($sp)
sw    $a1, 44($sp)
sw    $a2, 48($sp)
sw    $a3, 52($sp)

#     output(exp(0-2, 11)); /* -2048 */
addiu $sp, $sp,-56
sw    $t0, 0($sp)
sw    $t1, 4($sp)
sw    $t2, 8($sp)
sw    $t3, 12($sp)
sw    $t4, 16($sp)
sw    $t5, 20($sp)
sw    $t6, 24($sp)
sw    $t7, 28($sp)
sw    $t8, 32($sp)
sw    $t9, 36($sp)
sw    $a0, 40($sp)
sw    $a1, 44($sp)
sw    $a2, 48($sp)
sw    $a3, 52($sp)

#     output(exp(0-2, 11)); /* -2048 */
li    $t0, 0
li    $t1, 2
subu   $t0, $t0, $t1
li    $t1, 11
move  $a0, $t0
move  $a1, $t1
addiu $sp,$sp,-4
sw    $fp,0($sp) # push control link
jal   exp
sw    $fp,0($sp) # pop control link
addiu $sp,$sp,4
lw    $t0, 0($sp)
lw    $t1, 4($sp)
lw    $t2, 8($sp)
lw    $t3, 12($sp)
lw    $t4, 16($sp)
lw    $t5, 20($sp)
lw    $t6, 24($sp)
lw    $t7, 28($sp)
lw    $t8, 32($sp)
lw    $t9, 36($sp)
lw    $a0, 40($sp)
lw    $a1, 44($sp)
lw    $a2, 48($sp)
lw    $a3, 52($sp)
addiu $sp,$sp,56
move  $t0,$v0
move  $a0, $t0
addiu $sp,$sp,-4
sw    $fp,0($sp) # push control link
jal   output
sw    $fp,0($sp) # pop control link
addiu $sp,$sp,4
lw    $t0, 0($sp)
lw    $t1, 4($sp)
lw    $t2, 8($sp)
lw    $t3, 12($sp)
lw    $t4, 16($sp)
lw    $t5, 20($sp)
lw    $t6, 24($sp)
lw    $t7, 28($sp)
lw    $t8, 32($sp)
lw    $t9, 36($sp)
lw    $a0, 40($sp)
lw    $a1, 44($sp)
lw    $a2, 48($sp)
lw    $a3, 52($sp)
addiu $sp,$sp,56
move  $t0,$v0

#     output(exp(0-2, 12)); /* 4096 */
addiu $sp, $sp,-56
sw    $t0, 0($sp)
sw    $t1, 4($sp)
sw    $t2, 8($sp)
sw    $t3, 12($sp)
sw    $t4, 16($sp)
sw    $t5, 20($sp)
sw    $t6, 24($sp)
sw    $t7, 28($sp)
sw    $t8, 32($sp)
sw    $t9, 36($sp)
sw    $a0, 40($sp)
sw    $a1, 44($sp)
sw    $a2, 48($sp)
sw    $a3, 52($sp)

#     output(exp(0-2, 12)); /* 4096 */
addiu $sp, $sp,-56
sw    $t0, 0($sp)
sw    $t1, 4($sp)
sw    $t2, 8($sp)
sw    $t3, 12($sp)
sw    $t4, 16($sp)
sw    $t5, 20($sp)
sw    $t6, 24($sp)
sw    $t7, 28($sp)
sw    $t8, 32($sp)
sw    $t9, 36($sp)
sw    $a0, 40($sp)
sw    $a1, 44($sp)
sw    $a2, 48($sp)
sw    $a3, 52($sp)

#     output(exp(0-2, 12)); /* 4096 */
li    $t0, 0
li    $t1, 2
subu   $t0, $t0, $t1
li    $t1, 12
move  $a0, $t0
move  $a1, $t1
addiu $sp,$sp,-4
sw    $fp,0($sp) # push control link
jal   exp
sw    $fp,0($sp) # pop control link
addiu $sp,$sp,4
lw    $t0, 0($sp)
lw    $t1, 4($sp)
lw    $t2, 8($sp)
lw    $t3, 12($sp)
lw    $t4, 16($sp)
lw    $t5, 20($sp)
lw    $t6, 24($sp)
lw    $t7, 28($sp)
lw    $t8, 32($sp)
lw    $t9, 36($sp)
lw    $a0, 40($sp)
lw    $a1, 44($sp)
lw    $a2, 48($sp)
lw    $a3, 52($sp)
addiu $sp,$sp,56
move  $t0,$v0
move  $a0, $t0
addiu $sp,$sp,-4
sw    $fp,0($sp) # push control link
jal   output
sw    $fp,0($sp) # pop control link
addiu $sp,$sp,4
lw    $t0, 0($sp)
lw    $t1, 4($sp)
lw    $t2, 8($sp)
lw    $t3, 12($sp)
lw    $t4, 16($sp)
lw    $t5, 20($sp)
lw    $t6, 24($sp)
lw    $t7, 28($sp)
lw    $t8, 32($sp)
lw    $t9, 36($sp)
lw    $a0, 40($sp)
lw    $a1, 44($sp)
lw    $a2, 48($sp)
lw    $a3, 52($sp)
addiu $sp,$sp,56
move  $t0,$v0
addiu $sp,$sp,0 # free locals


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
# End of code.
