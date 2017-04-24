  # labwork.S
  # Written 2015 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1 2015-2016.
  # The macros PUSH and POP are in the public domain.

.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

	.data
	.align 2
mytime:	.word 0x5957
#timstr:	.ascii "text more text lots of text\0"
.global time2string
.global delay
.global hexasc
	.text



  # you can write your code for subroutine "hexasc" below this line
  #
  # Converts a number
hexasc:
	andi $t0,$a0,0x000f  # Removes everything but the 4 LSB
	addi $t0,$t0,0x0030  # Adds the ASCII - hex value for 0
	bgt $t0,0x0039,convHex  # Checks if the value is bigger than the ASCII hex value for 9, if so jumps to the subroutine "convHex"
	move $v0,$t0  # Sets the value of register $t0 to $v0
	jr $ra # Jumps back to the main method
	nop
	
	#Here the number will be converted to a hexadecimal number	
convHex:
	addi $t0,$t0,0x0007  # Adds the difference between 9 and A in ASCII hex to the number
	move $v0,$t0  # Sets the value of register $t0 to $v0
	jr $ra  # Jumps back to the main method
	nop
	
	#The while loop
delay:
	
	move $t0, $a0 # move milliseconds to $t0
	
	while:
		blez $t0, done # While loop ends if value in register t0 is equal or less than zero.
		addi $t0, $t0, -1 # Decrement the value in register t0 with 1.
		
		li $t1, 0 # Load the immidiate 0 to register t1.
		for:
			bgt $t1, 13500, exit # Exit the for loop if the value in register t1 is greater than a set immidiate value.
			addi $t1, $t1, 1 # Increments the value in $t1 by one.

			j for  # Jump back to the start of the for loop.
			nop
			
		exit:
			j while #Continue the while loop
			nop
			
	
	done: #while loop is done
		jr $ra #Jumps back to main
		nop

	#Converts the time to a string of characters
time2string:
	PUSH $ra #Pushes the main address to the stack. 

	PUSH $a0 #Pushes $a0 to the stack, because it's used as argument in hexasc
	andi $t2,$a1,0xf000 #Takes the 16 LSB and assigns it to $t2.
	srl $a0, $t2, 12 #Shifts the value 12 bits in order to get it as a 4 bit number.
	jal hexasc #Call hexasc in order to convert the value in $a0 to an ASCII-representation.
	nop
	
	POP $a0 #Pops $a0 from the stack, so we retain the address to the string
	sb $v0,0($a0) #Stores the the returned value from hexasc 
	
	PUSH $a0
	andi $t2,$a1,0x0f00
	srl $a0, $t2, 8 #Shifts the value 8 bits right in order to get it as a 4 bit number.
	jal hexasc
	nop
	
	POP $a0
	sb $v0,1($a0)
	li $t3,0x3A #ASCII char ':'
	sb $t3,2($a0)
	
	PUSH $a0
	andi $t2,$a1,0x00f0
	srl $a0, $t2, 4 #Shifts the value 4 bits right in order to get it as a 4 bit number.
	jal hexasc
	nop
	
	POP $a0
	sb $v0,3($a0)
	
	PUSH $a0
	andi $t2,$a1,0x000f
	move $a0, $t2 #No bits to shift here, just move $t2 to $a0
	jal hexasc
	nop
	

	POP $a0
	
	li $t4, 0x39
	beq $v0, $t4, nine
	
	sb $v0,4($a0)
	li $t3, 0x00
	sb $t3,5($a0) #Store a nullbyte to terminate the string
	
	j timend
	nop

	nine:
	
	li $t3, 0x4e
	sb $t3,4($a0) 
	
	li $t3, 0x49
	sb $t3,5($a0)
	
	li $t3, 0x4e
	sb $t3,6($a0) 
	
	li $t3, 0x45
	sb $t3,7($a0)
	
	li $t3, 0x00
	sb $t3,8($a0) #Store a nullbyte to terminate the string
	
	
	timend:

	POP $ra #Pop the main address from the stack, so you can return to main
	jr $ra #Returns to main
	nop
