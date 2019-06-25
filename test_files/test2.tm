# C- Compilation to SPIM Code
# Source File: test_files/test2.tm
.align 2
.globl main

main:
# set frame pointer
move  $fp,$sp
# push the return address
addiu $sp,$sp,-4
sw    $ra,0($sp)

addiu $sp,$sp,0 # allocate locals


#     output(1 < 2); /* 1 */
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

#     output(1 < 2); /* 1 */
li    $t0, 1
li    $t1, 2
slt   $t0, $t0, $t1
andi  $t0, $t0, 0x00ff
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

#     output(1 < 1); /* 0 */
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

#     output(1 < 1); /* 0 */
li    $t0, 1
li    $t1, 1
slt   $t0, $t0, $t1
andi  $t0, $t0, 0x00ff
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

#     output(1 < 0); /* 0 */
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

#     output(1 < 0); /* 0 */
li    $t0, 1
li    $t1, 0
slt   $t0, $t0, $t1
andi  $t0, $t0, 0x00ff
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

#     output(1 <= 2); /* 1 */
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

#     output(1 <= 2); /* 1 */
li    $t0, 1
li    $t1, 2
slt   $t0, $t1, $t0
xori  $t0, $t0, 0x1
andi  $t0, $t0, 0x00ff
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

#     output(1 <= 1); /* 1 */
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

#     output(1 <= 1); /* 1 */
li    $t0, 1
li    $t1, 1
slt   $t0, $t1, $t0
xori  $t0, $t0, 0x1
andi  $t0, $t0, 0x00ff
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

#     output(1 <= 0); /* 0 */
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

#     output(1 <= 0); /* 0 */
li    $t0, 1
li    $t1, 0
slt   $t0, $t1, $t0
xori  $t0, $t0, 0x1
andi  $t0, $t0, 0x00ff
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

#     output(1 > 2); /* 0 */
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

#     output(1 > 2); /* 0 */
li    $t0, 1
li    $t1, 2
slt   $t0, $t1, $t0
andi  $t0, $t0, 0x00ff
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

#     output(1 > 1); /* 0 */
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

#     output(1 > 1); /* 0 */
li    $t0, 1
li    $t1, 1
slt   $t0, $t1, $t0
andi  $t0, $t0, 0x00ff
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

#     output(1 > 0); /* 1 */
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

#     output(1 > 0); /* 1 */
li    $t0, 1
li    $t1, 0
slt   $t0, $t1, $t0
andi  $t0, $t0, 0x00ff
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

#     output(1 >= 2); /* 0 */
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

#     output(1 >= 2); /* 0 */
li    $t0, 1
li    $t1, 2
slt   $t0, $t0, $t1
xori  $t0, $t0, 0x1
andi  $t0, $t0, 0x00ff
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

#     output(1 >= 1); /* 1 */
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

#     output(1 >= 1); /* 1 */
li    $t0, 1
li    $t1, 1
slt   $t0, $t0, $t1
xori  $t0, $t0, 0x1
andi  $t0, $t0, 0x00ff
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

#     output(1 >= 0); /* 1 */
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

#     output(1 >= 0); /* 1 */
li    $t0, 1
li    $t1, 0
slt   $t0, $t0, $t1
xori  $t0, $t0, 0x1
andi  $t0, $t0, 0x00ff
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

#     output(1 == 2); /* 0 */
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

#     output(1 == 2); /* 0 */
li    $t0, 1
li    $t1, 2
xor   $t0, $t0, $t1
sltu  $t0, $t0, 1
andi  $t0, $t0, 0x00ff
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

#     output(1 == 1); /* 1 */
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

#     output(1 == 1); /* 1 */
li    $t0, 1
li    $t1, 1
xor   $t0, $t0, $t1
sltu  $t0, $t0, 1
andi  $t0, $t0, 0x00ff
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

#     output(1 == 0); /* 0 */
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

#     output(1 == 0); /* 0 */
li    $t0, 1
li    $t1, 0
xor   $t0, $t0, $t1
sltu  $t0, $t0, 1
andi  $t0, $t0, 0x00ff
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

#     output(1 != 2); /* 1 */
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

#     output(1 != 2); /* 1 */
li    $t0, 1
li    $t1, 2
xor   $t0, $t0, $t1
sltu  $t0, $0, $t0
andi  $t0, $t0, 0x00ff
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

#     output(1 != 1); /* 0 */
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

#     output(1 != 1); /* 0 */
li    $t0, 1
li    $t1, 1
xor   $t0, $t0, $t1
sltu  $t0, $0, $t0
andi  $t0, $t0, 0x00ff
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

#     output(1 != 0); /* 1 */
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

#     output(1 != 0); /* 1 */
li    $t0, 1
li    $t1, 0
xor   $t0, $t0, $t1
sltu  $t0, $0, $t0
andi  $t0, $t0, 0x00ff
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

#     output(1 + 2); /* 3 */
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

#     output(1 + 2); /* 3 */
li    $t0, 1
li    $t1, 2
addu   $t0, $t0, $t1
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

#     output(1 + 1); /* 2 */
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

#     output(1 + 1); /* 2 */
li    $t0, 1
li    $t1, 1
addu   $t0, $t0, $t1
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

#     output(1 + 0); /* 1 */
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

#     output(1 + 0); /* 1 */
li    $t0, 1
li    $t1, 0
addu   $t0, $t0, $t1
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

#     output(1 - 2); /* -1 */
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

#     output(1 - 2); /* -1 */
li    $t0, 1
li    $t1, 2
subu   $t0, $t0, $t1
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

#     output(1 - 1); /* 0  */
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

#     output(1 - 1); /* 0  */
li    $t0, 1
li    $t1, 1
subu   $t0, $t0, $t1
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

#     output(1 - 0); /* 1  */
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

#     output(1 - 0); /* 1  */
li    $t0, 1
li    $t1, 0
subu   $t0, $t0, $t1
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

#     output(1 * 2); /* 2 */
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

#     output(1 * 2); /* 2 */
li    $t0, 1
li    $t1, 2
mult  $t0, $t1
mflo  $t0
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

#     output(1 * 1); /* 1 */
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

#     output(1 * 1); /* 1 */
li    $t0, 1
li    $t1, 1
mult  $t0, $t1
mflo  $t0
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

#     output(1 * 0); /* 0 */
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

#     output(1 * 0); /* 0 */
li    $t0, 1
li    $t1, 0
mult  $t0, $t1
mflo  $t0
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

#     output(1 / 2); /* 0     */
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

#     output(1 / 2); /* 0     */
li    $t0, 1
li    $t1, 2
div   $0,$t0,$t1
mfhi  $t0
mflo  $t0
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

#     output(1 / 1); /* 1     */
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

#     output(1 / 1); /* 1     */
li    $t0, 1
li    $t1, 1
div   $0,$t0,$t1
mfhi  $t0
mflo  $t0
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

#     output(1 / 0); /* error */
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

#     output(1 / 0); /* error */
li    $t0, 1
li    $t1, 0
div   $0,$t0,$t1
mfhi  $t0
mflo  $t0
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
