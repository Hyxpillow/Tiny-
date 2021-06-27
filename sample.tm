* TINY Compilation to TM Code
* File: sample.tm
* Standard prelude:
  0:     LD  6,0(0) 	load maxaddress from location 0
  1:     ST  0,0(0) 	clear location 0
* End of standard prelude.
* -> assign
* -> Const
  2:    LDC  0,4(0) 	load const
* <- Const
  3:     ST  0,0(5) 	assign: store value
* <- assign
* -> assign
* -> Const
  4:    LDC  0,5(0) 	load const
* <- Const
  5:     ST  0,1(5) 	assign: store value
* <- assign
* -> assign
* -> Const
  6:    LDC  0,6(0) 	load const
* <- Const
  7:     ST  0,2(5) 	assign: store value
* <- assign
* -> if
* -> Op
* -> Const
  8:    LDC  0,0(0) 	load const
* <- Const
  9:     ST  0,0(6) 	op: push left
* -> Const
 10:    LDC  0,0(0) 	load const
* <- Const
 11:     LD  1,0(6) 	op: load left
 12:    JNE  0,3(7) 	left  false
 13:    JNE  1,2(7) 	right false
 14:    LDC  0,0(0) 	false case
 15:    LDA  7,1(7) 	unconditional jmp
 16:    LDC  0,1(0) 	true case
* <- Op
* if: jump to else belongs here
* -> Id
 18:     LD  0,2(5) 	load id value
* <- Id
 19:    OUT  0,0,0 	write ac
* if: jump to end belongs here
 17:    JEQ  0,3(7) 	if: jmp to else
 20:    LDA  7,0(7) 	jmp to end
* <- if
* End of execution.
 21:   HALT  0,0,0 	
