.MODEL SMALL

.STACK

.DATA
STRING DB  'hello world!$'

.CODE
.STARTUP
 
 MOV DX,OFFSET STRING
 MOV AH,9
 INT 21H
	
.EXIT

END