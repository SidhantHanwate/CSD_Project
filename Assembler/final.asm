.section
.data
.section
.text
jal $30,main
main:
addi $9,$0,8224
addi $10,$0,8196
add $10,$8,$10
sw $9,0($10)
addi $9,$0,8736
addi $10,$0,8200
add $10,$8,$10
sw $9,0($10)
addi $9,$0,8768
addi $10,$0,8204
add $10,$8,$10
sw $9,0($10)
addi $9,$0,9280
addi $10,$0,8192
add $10,$8,$10
sw $9,0($10)
addi $2,$0,9280
add $2,$2,$8
addi $9,$0,8
sw $9,0($2)
addi $2,$2,4
addi $2,$2,-4
lw $9,0($2)
addi $10,$0,8204
add $10,$10,$8
lw $10,0($10)
addi $10,$10,4
sw $9,0($10)
addi $9,$0,8204
add $9,$9,$8
lw $9,0($9)
addi $9,$9,4
lw $9,0($9)
sw $9,0($2)
addi $2,$2,4
addi $2,$2,-4
lw $9,0($2)
addi $10,$0,8196
add $10,$10,$8
lw $10,0($10)
addi $10,$10,4
sw $9,0($10)
addi $9,$0,2
sw $9,0($2)
addi $2,$2,4
addi $2,$2,-4
lw $9,0($2)
addi $10,$0,8204
add $10,$10,$8
lw $10,0($10)
addi $10,$10,8
sw $9,0($10)
addi $9,$0,8204
add $9,$9,$8
lw $9,0($9)
addi $9,$9,8
lw $9,0($9)
sw $9,0($2)
addi $2,$2,4
addi $2,$2,-4
lw $9,0($2)
addi $10,$0,8196
add $10,$10,$8
lw $10,0($10)
addi $10,$10,8
sw $9,0($10)
addi $9,$0,8196
add $9,$9,$8
lw $9,0($9)
addi $9,$9,4
lw $9,0($9)
sw $9,0($2)
addi $2,$2,4
addi $9,$0,8196
add $9,$9,$8
lw $9,0($9)
addi $9,$9,8
lw $9,0($9)
sw $9,0($2)
addi $2,$2,4
addi $2,$2,-4
lw $9,0($2)
addi $2,$2,-4
lw $10,0($2)
add $9,$10,$9
sw $9,0($2)
addi $2,$2,4
addi $2,$2,-4
lw $9,0($2)
addi $10,$0,8204
add $10,$10,$8
lw $10,0($10)
addi $10,$10,12
sw $9,0($10)
addi $9,$0,8204
add $9,$9,$8
lw $9,0($9)
addi $9,$9,12
lw $9,0($9)
sw $9,0($2)
addi $2,$2,4
addi $2,$2,-4
lw $9,0($2)
addi $10,$0,8196
add $10,$10,$8
lw $10,0($10)
addi $10,$10,12
sw $9,0($10)
addi $9,$0,8196
add $9,$9,$8
lw $9,0($9)
addi $9,$9,12
lw $9,0($9)
sw $9,0($2)
addi $2,$2,4
addi $2,$2,-4
lw $9,0($2)
add $3,$9,$0
addi $2,$2,4
addi $5,$0,4
__END:
nop