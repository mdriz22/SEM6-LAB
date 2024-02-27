org 00h
mov r4 ,#05h
here: mov p1,#11111111b
acall delay
mov p1,#00000000b
acall delay
sjmp here
delay:mov r0,#100
back2:mov r1,#200
back1: mov r2,#200
again: djnz r2,again
djnz r1,back1
djnz r0, back2
ret
end