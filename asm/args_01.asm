;
; Подсчитываем количество аргументов командной строки. т.е фактически количество опций вводимой команды

format ELF executable 3
entry start
segment readable writeable

msg1 db 'Enter some text : '
msg1_size = $-msg1

msg2 rb 255
msg2_sz rb 1 ; резервируем 1 байт под значение длины

msg3 db 'your arguments number is     : '
msg3_sz = $ - msg3
max_len db '255'

msg4 db 'your string length is '
msg4_sz = $ - msg4

msg5 rb 5    ; 5 символов - строка, показывающая число
msg5_sz rb 1 ; 1 байт - хранит длину строки. 255 символов хватит


segment readable writeable executable
include 'int_2_str.inc'
start:


;	mov	eax,4
;	mov	ebx,1
;	mov	ecx,msg1
;	mov	edx,msg1_size
;	int	0x80

; now read input
;  mov eax, 3
;  mov ebx, 0
;  mov ecx, msg2
;  mov edx, max_len
;  int 0x80


;push ebp
;mov ebp, esp
;mov eax, [esp +4]
;mov ebx, [esp +8]

        push    ebp
        mov     ebp,esp
        mov     eax,[ebp+4]     ;argc
        dec eax                 ; (-1) as there is "path" argument in addition to user arguments
        ;sub     ebx,1
        ;jz      usage


  mov edi, msg5

; По завершении системного вызова Чтение имеем в регистре eax длину строки, 
; веденную пользователем.
; Поэтому сразу сохраняем эту длину здесь.
;mov [msg2_sz], byte al

call int_to_string
    mov [msg5_sz], dl ; сохраняем длину строки, показывающей число

 ;now reflect input 
   ;1st print comment message
	mov	eax,4
	mov	ebx,1
	mov	ecx,msg3
	mov	edx,msg3_sz
	int	0x80
	
   ;next print input string itself
	;mov	eax,4
	;mov	ebx,1
	;mov	ecx,msg2
	;mov	dl,  [msg2_sz]
	;int	0x80
   
   ;3rd print comment message for length
   ; mov eax,4
   ; mov ebx,1
   ; mov ecx,msg4
   ; mov edx,msg4_sz
   ; int 80h

   ;4th print length int value as string 
    mov eax,4
    mov ebx,1
    mov ecx,msg5
    mov dl, [msg5_sz]
    int 80h


exit:

	mov	eax,1           ; sys_exit
	xor	ebx,ebx         ; exit code == 0
	int	0x80            ; Вызов прерывания

