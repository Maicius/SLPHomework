
data    segment para public 'data'    ;���ݶ�
msg     db 'hello world ! $',0ah,0dh ;db�����ֽڣ�ÿ��������ռ��һ���ֽ�
data    ends


ss_seg  segment stack para 'stack'  ;��ջ��
        db 256 dup(?)               ;�ظ������еĲ�����256�Ρ� 

ss_seg  ends

code    segment para public 'code'   ;�����

	assume cs:code,ds:data,ss:ss_seg ;��ȷ�κͶμĴ����Ĺ�ϵ

start:                               ;starting execution address
	mov ax,data                  ;data segment addr
	mov ds,ax                    ;into ds register

	mov dx,offset msg            ;ȡ�ַ���ʼ��ַ����BX��
        mov ah,09h                   ;��ʾ�ַ���	
	int 21h
       ;��ʾ�ַ���������21H�жϣ�Ҳ��DOS���ܵ��ã���9�Ź��ܣ��ù�����
       ;��ʾ�ַ���������DS��DXΪ�ַ�����ַ����$��Ϊ�ַ���������־��

	mov ah,4ch
	int 21h
        ;����21H�жϵ�4c���ܣ�����dos


code  	ends                          ;end of code segment

	end  start
