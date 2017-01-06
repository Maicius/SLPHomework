
data    segment para public 'data'    ;数据段
msg     db 'hello world ! $',0ah,0dh ;db定义字节，每个操作数占用一个字节
data    ends


ss_seg  segment stack para 'stack'  ;堆栈段
        db 256 dup(?)               ;重复括号中的操作数256次。 

ss_seg  ends

code    segment para public 'code'   ;代码段

	assume cs:code,ds:data,ss:ss_seg ;明确段和段寄存器的关系

start:                               ;starting execution address
	mov ax,data                  ;data segment addr
	mov ds,ax                    ;into ds register

	mov dx,offset msg            ;取字符串始地址送入BX中
        mov ah,09h                   ;显示字符串	
	int 21h
       ;显示字符串。调用21H中断（也是DOS功能调用）的9号功能，该功能是
       ;显示字符串，其中DS：DX为字符串地址，‘$’为字符串结束标志。

	mov ah,4ch
	int 21h
        ;调用21H中断的4c功能，返回dos


code  	ends                          ;end of code segment

	end  start
