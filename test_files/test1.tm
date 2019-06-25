# C- Compilation to SPIM Code
# Source File: test_files/test1.tm
.align 2
.globl main

f:
# set frame pointer
move  $fp,$sp
# push the return address
addiu $sp,$sp,-4
sw    $ra,0($sp)

addiu $sp,$sp,0 # allocate locals

addiu $sp,$sp,0 # free locals


# restore return address
lw    $ra,-4($fp)
# copy the fp to the sp
move  $sp,$fp
# load the control link into the fp
lw    $fp,0($fp)
# jump to the return address
j     $ra

func:
# set frame pointer
move  $fp,$sp
# push the return address
addiu $sp,$sp,-4
sw    $ra,0($sp)

addiu $sp,$sp,-44 # allocate locals


#     i = 0;
addiu $t0, $fp, -48
li    $t1, 0
sw    $t1, 0($t0)
$_L0: # loop
# evaluate the loop condition

#     while (parB == 0) {
move  $t0, $a1
li    $t1, 0
xor   $t0, $t0, $t1
sltu  $t0, $t0, 1
andi  $t0, $t0, 0x00ff
# exit if the condition is false
beq   $t0,$0,$_L1

# loop body
addiu $sp,$sp,-4 # allocate locals


#         parA[i] = parB * func(parA, i) * (parA[i] + parA[i+1]/parB);

#         parA[i] = parB * func(parA, i) * (parA[i] + parA[i+1]/parB);
lw    $t1, -48($fp)
sll   $t1,$t1,2
addu  $t0, $a0, $t1

#         parA[i] = parB * func(parA, i) * (parA[i] + parA[i+1]/parB);

#         parA[i] = parB * func(parA, i) * (parA[i] + parA[i+1]/parB);
move  $t1, $a1

#         parA[i] = parB * func(parA, i) * (parA[i] + parA[i+1]/parB);
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
move  $t6, $a0
move  $t2, $t6
lw    $t6, -48($fp)
move  $t3, $t6
move  $a0, $t2
move  $a1, $t3
addiu $sp,$sp,-4
sw    $fp,0($sp) # push control link
jal   func
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
addiu $sp,$sp,40
move  $t2,$v0
mult  $t1, $t2
mflo  $t1

#         parA[i] = parB * func(parA, i) * (parA[i] + parA[i+1]/parB);

#         parA[i] = parB * func(parA, i) * (parA[i] + parA[i+1]/parB);
lw    $t3, -48($fp)
sll   $t3,$t3,2
addu  $t2, $a0, $t3
lw    $t2, 0($t2)

#         parA[i] = parB * func(parA, i) * (parA[i] + parA[i+1]/parB);

#         parA[i] = parB * func(parA, i) * (parA[i] + parA[i+1]/parB);

#         parA[i] = parB * func(parA, i) * (parA[i] + parA[i+1]/parB);
lw    $t4, -48($fp)
li    $t5, 1
addu   $t4, $t4, $t5
sll   $t4,$t4,2
addu  $t3, $a0, $t4
lw    $t3, 0($t3)
move  $t4, $a1
div   $0,$t3,$t4
mfhi  $t3
mflo  $t3
addu   $t2, $t2, $t3
mult  $t1, $t2
mflo  $t1
sw    $t1, 0($t0)

#         parB = parB - 1;

#         parB = parB - 1;
move  $t1, $a1
li    $t2, 1
subu   $t1, $t1, $t2
move $a1, $t1

#         i = i + 1;
addiu $t0, $fp, -48

#         i = i + 1;
lw    $t1, -48($fp)
li    $t2, 1
addu   $t1, $t1, $t2
sw    $t1, 0($t0)
# evaluate the condition

#         if(parB = parA[12])

#         if(parB = parA[12])
li    $t2, 12
sll   $t2,$t2,2
addu  $t1, $a0, $t2
lw    $t1, 0($t1)
move $a1, $t1
# branch to else if the condition is false
beq   $t0,$0,$_L2

# if block
# evaluate the condition

#             if (wvar == 1)
lw    $t0, -52($fp)
li    $t1, 1
xor   $t0, $t0, $t1
sltu  $t0, $t0, 1
andi  $t0, $t0, 0x00ff
# branch to else if the condition is false
beq   $t0,$0,$_L4

# if block

#                 i = 0;
addiu $t0, $fp, -48
li    $t1, 0
sw    $t1, 0($t0)
# jump to end
j     $_L5

# else
$_L4:

#         else i = 1;
addiu $t0, $fp, -48
li    $t1, 1
sw    $t1, 0($t0)
# end of if statement
$_L5:

# jump to end
j     $_L3

# else
$_L2:
# end of if statement
$_L3:

addiu $sp,$sp,4 # free locals

j     $_L0 # loop
$_L1: # loop exit

#     return parA[2];
li    $t1, 2
sll   $t1,$t1,2
addu  $t0, $a0, $t1
lw    $t0, 0($t0)
move  $v0, $t0 # set return value
# restore return address
lw    $ra,-4($fp)
# copy the fp to the sp
move  $sp,$fp
# load the control link into the fp
lw    $fp,0($fp)
# jump to the return address
j     $ra

addiu $sp,$sp,44 # free locals


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

$_L6: # loop
# evaluate the loop condition

#     while (tmp = 1) {
addiu $t0, $fp, -8
li    $t1, 1
sw    $t1, 0($t0)
# exit if the condition is false
beq   $t0,$0,$_L7

# loop body
addiu $sp,$sp,-4 # allocate locals


#         one = arr[1];
addiu $t0, $fp, -12

#         one = arr[1];
li    $t2, 1
sll   $t2,$t2,2
la    $t1, arr
addu  $t1, $t1, $t2
lw    $t1, 0($t1)
sw    $t1, 0($t0)
# evaluate the condition

#         if (one == brr[2])
lw    $t0, -12($fp)

#         if (one == brr[2])
li    $t2, 2
sll   $t2,$t2,2
la    $t1, brr
addu  $t1, $t1, $t2
lw    $t1, 0($t1)
xor   $t0, $t0, $t1
sltu  $t0, $t0, 1
andi  $t0, $t0, 0x00ff
# branch to else if the condition is false
beq   $t0,$0,$_L8

# if block

#             tmp = one == brr[3];
addiu $t0, $fp, -8

#             tmp = one == brr[3];
lw    $t1, -12($fp)

#             tmp = one == brr[3];
li    $t3, 3
sll   $t3,$t3,2
la    $t2, brr
addu  $t2, $t2, $t3
lw    $t2, 0($t2)
xor   $t1, $t1, $t2
sltu  $t1, $t1, 1
andi  $t1, $t1, 0x00ff
sw    $t1, 0($t0)
# jump to end
j     $_L9

# else
$_L8:
addiu $sp,$sp,-8 # allocate locals


#             two = arr[2];
addiu $t0, $fp, -16

#             two = arr[2];
li    $t2, 2
sll   $t2,$t2,2
la    $t1, arr
addu  $t1, $t1, $t2
lw    $t1, 0($t1)
sw    $t1, 0($t0)
$_L10: # loop
# evaluate the loop condition

#             while(arr[one] == brr[tmp]) {

#             while(arr[one] == brr[tmp]) {
lw    $t1, -12($fp)
sll   $t1,$t1,2
la    $t0, arr
addu  $t0, $t0, $t1
lw    $t0, 0($t0)

#             while(arr[one] == brr[tmp]) {
lw    $t2, -20($fp)
sll   $t2,$t2,2
la    $t1, brr
addu  $t1, $t1, $t2
lw    $t1, 0($t1)
xor   $t0, $t0, $t1
sltu  $t0, $t0, 1
andi  $t0, $t0, 0x00ff
# exit if the condition is false
beq   $t0,$0,$_L11

# loop body
addiu $sp,$sp,-4 # allocate locals

# evaluate the condition
li    $t0, 1
# branch to else if the condition is false
beq   $t0,$0,$_L12

# if block
addiu $sp,$sp,-4 # allocate locals


#                     tmp = one;
addiu $t0, $fp, -28
lw    $t1, -12($fp)
sw    $t1, 0($t0)
addiu $sp,$sp,4 # free locals

# jump to end
j     $_L13

# else
$_L12:
# end of if statement
$_L13:

addiu $sp,$sp,4 # free locals

j     $_L10 # loop
$_L11: # loop exit

#             tmp = two;
addiu $t0, $fp, -20
lw    $t1, -16($fp)
sw    $t1, 0($t0)
addiu $sp,$sp,8 # free locals

# end of if statement
$_L9:

addiu $sp,$sp,4 # free locals

j     $_L6 # loop
$_L7: # loop exit

#     tmp = func(arr, 45);
addiu $t0, $fp, -8

#     tmp = func(arr, 45);
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
la    $t5, arr
move  $t1, $t5
li    $t5, 45
move  $t2, $t5
move  $a0, $t1
move  $a1, $t2
addiu $sp,$sp,-4
sw    $fp,0($sp) # push control link
jal   func
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
addiu $sp,$sp,40
move  $t1,$v0
sw    $t1, 0($t0)
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
arr: .word 10
brr: .word 20
crr: .word 30
# End of code.
