.386
.model flat,stdcall

.data
szMsg  byte "hello world !",0ah,0

.code
start:
	mov eax,1
	mov ebx,2
	add eax,ebx
	ret

end start