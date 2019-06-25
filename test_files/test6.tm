# C- Compilation to SPIM Code
# Source File: test_files/test6.tm
.align 2
.globl main

print:
# set frame pointer
move  $fp,$sp
# push the return address
addiu $sp,$sp,-4
sw    $ra,0($sp)

addiu $sp,$sp,-4 # allocate locals


#     i = 0;
addiu $t0, $fp, -8
li    $t1, 0
sw    $t1, 0($t0)
$_L0: # loop
# evaluate the loop condition

#     while (i < 10) {
lw    $t0, -8($fp)
li    $t1, 10
slt   $t0, $t0, $t1
andi  $t0, $t0, 0x00ff
# exit if the condition is false
beq   $t0,$0,$_L1

# loop body
addiu $sp,$sp,0 # allocate locals


#         output(x[i]);
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

#         output(x[i]);
lw    $t1, -8($fp)
sll   $t1,$t1,2
addu  $t0, $a0, $t1
lw    $t0, 0($t0)
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

#         i = i + 1;
addiu $t0, $fp, -8

#         i = i + 1;
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


#     k = low;
addiu $t0, $fp, -16
move  $t1, $a1
sw    $t1, 0($t0)

#     x = a[low];
addiu $t0, $fp, -12

#     x = a[low];
move  $t2, $a1
sll   $t2,$t2,2
addu  $t1, $a0, $t2
lw    $t1, 0($t1)
sw    $t1, 0($t0)

#     i = low + 1;
addiu $t0, $fp, -8

#     i = low + 1;
move  $t1, $a1
li    $t2, 1
addu   $t1, $t1, $t2
sw    $t1, 0($t0)
$_L2: # loop
# evaluate the loop condition

#     while (i < high)
lw    $t0, -8($fp)
move  $t1, $a2
slt   $t0, $t0, $t1
andi  $t0, $t0, 0x00ff
# exit if the condition is false
beq   $t0,$0,$_L3

# loop body
addiu $sp,$sp,0 # allocate locals

# evaluate the condition

#         if (a[i] < x)

#         if (a[i] < x)
lw    $t1, -8($fp)
sll   $t1,$t1,2
addu  $t0, $a0, $t1
lw    $t0, 0($t0)
lw    $t1, -12($fp)
slt   $t0, $t0, $t1
andi  $t0, $t0, 0x00ff
# branch to else if the condition is false
beq   $t0,$0,$_L4

# if block
addiu $sp,$sp,0 # allocate locals


#             x = a[i];
addiu $t0, $fp, -12

#             x = a[i];
lw    $t2, -8($fp)
sll   $t2,$t2,2
addu  $t1, $a0, $t2
lw    $t1, 0($t1)
sw    $t1, 0($t0)

#             k = i;
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


#         i = i + 1;
addiu $t0, $fp, -8

#         i = i + 1;
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


#     i = low;
addiu $t0, $fp, -8
move  $t1, $a1
sw    $t1, 0($t0)
$_L6: # loop
# evaluate the loop condition

#     while (i < high - 1) {
lw    $t0, -8($fp)

#     while (i < high - 1) {
move  $t1, $a2
li    $t2, 1
subu   $t1, $t1, $t2
slt   $t0, $t0, $t1
andi  $t0, $t0, 0x00ff
# exit if the condition is false
beq   $t0,$0,$_L7

# loop body
addiu $sp,$sp,-4 # allocate locals


#         k = minloc(a,i,high);
addiu $t0, $fp, -12

#         k = minloc(a,i,high);
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
move  $t1, $a0
lw    $t2, -8($fp)
move  $t3, $a2
move  $a0, $t1
move  $a1, $t2
move  $a2, $t3
addiu $sp,$sp,-4
sw    $fp,0($sp) # push control link
jal   minloc
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
move  $t1,$v0
sw    $t1, 0($t0)

#         t=a[k];
addiu $t0, $fp, -16

#         t=a[k];
lw    $t2, -12($fp)
sll   $t2,$t2,2
addu  $t1, $a0, $t2
lw    $t1, 0($t1)
sw    $t1, 0($t0)

#         a[k]=a[i];

#         a[k]=a[i];
lw    $t1, -12($fp)
sll   $t1,$t1,2
addu  $t0, $a0, $t1

#         a[k]=a[i];
lw    $t2, -8($fp)
sll   $t2,$t2,2
addu  $t1, $a0, $t2
lw    $t1, 0($t1)
sw    $t1, 0($t0)

#         a[i] = t;

#         a[i] = t;
lw    $t1, -8($fp)
sll   $t1,$t1,2
addu  $t0, $a0, $t1
lw    $t1, -16($fp)
sw    $t1, 0($t0)

#         i = i + 1;
addiu $t0, $fp, -8

#         i = i + 1;
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


#     i = 0;
addiu $t0, $fp, -8
li    $t1, 0
sw    $t1, 0($t0)
$_L8: # loop
# evaluate the loop condition

#     while (i < 10) {
lw    $t0, -8($fp)
li    $t1, 10
slt   $t0, $t0, $t1
andi  $t0, $t0, 0x00ff
# exit if the condition is false
beq   $t0,$0,$_L9

# loop body
addiu $sp,$sp,0 # allocate locals


#         x[i] = input();

#         x[i] = input();
lw    $t1, -8($fp)
sll   $t1,$t1,2
la    $t0, x
addu  $t0, $t0, $t1

#         x[i] = input();
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
addiu $sp,$sp,-4
sw    $fp,0($sp) # push control link
jal   input
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
move  $t1,$v0
sw    $t1, 0($t0)

#         i = i + 1;
addiu $t0, $fp, -8

#         i = i + 1;
lw    $t1, -8($fp)
li    $t2, 1
addu   $t1, $t1, $t2
sw    $t1, 0($t0)
addiu $sp,$sp,0 # free locals

j     $_L8 # loop
$_L9: # loop exit

#     sort(x,0,10);
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
la    $t0, x
li    $t1, 0
li    $t2, 10
move  $a0, $t0
move  $a1, $t1
move  $a2, $t2
addiu $sp,$sp,-4
sw    $fp,0($sp) # push control link
jal   sort
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

#     print(x);
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
la    $t0, x
move  $a0, $t0
addiu $sp,$sp,-4
sw    $fp,0($sp) # push control link
jal   print
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
