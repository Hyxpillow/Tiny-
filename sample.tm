  0:     LD  6,0(0) 
  1:     ST  0,0(0) 
  2:     IN  0,0,0 
  3:     ST  0,1(5) 
  4:     LD  0,1(5) 
  5:     ST  0,0(6) 
  6:    LDC  0,0(0) 
  7:     LD  1,0(6) 
  8:    SUB  0,1,0 
  9:    JGT  0,2(7) 
 10:    LDC  0,0(0) 
 11:    LDA  7,1(7) 
 12:    LDC  0,1(0) 
 14:    LDC  0,1(0) 
 15:     ST  0,0(5) 
 16:     LD  0,0(5) 
 17:     ST  0,0(6) 
 18:     LD  0,1(5) 
 19:     LD  1,0(6) 
 20:    MUL  0,1,0 
 21:     ST  0,0(5) 
 22:     LD  0,1(5) 
 23:     ST  0,0(6) 
 24:    LDC  0,1(0) 
 25:     LD  1,0(6) 
 26:    SUB  0,1,0 
 27:     ST  0,1(5) 
 28:     LD  0,1(5) 
 29:     ST  0,0(6) 
 30:    LDC  0,0(0) 
 31:     LD  1,0(6) 
 32:    SUB  0,1,0 
 33:    JEQ  0,2(7) 
 34:    LDC  0,0(0) 
 35:    LDA  7,1(7) 
 36:    LDC  0,1(0) 
 37:    JEQ  0,-22(7) 
 38:     LD  0,0(5) 
 39:    OUT  0,0,0 
 13:    JEQ  0,27(7) 
 40:    LDA  7,0(7) 
 41:   HALT  0,0,0 
