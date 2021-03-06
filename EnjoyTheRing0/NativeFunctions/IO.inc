proc StartBeeper
  ; ������� ������ ��� ����, ���������� �� ������������ ������� �� ����� 61h:
  in al, 61h
  or al, 00000011b
  out 61h, al
  ret
endp

;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

proc StopBeeper
  ; ���������� ������ ��� ���� � ����� 61h, ���������� �� ������������ �������:
  in al, 61h
  and al, 11111100b
  out 61h, al
  ret
endp

;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

proc SetBeeperRegime
  ; �������������� �������:
  mov al, 10110110b ; 0B6h = 10 11 011 0
     ;     10 = ����� ������, ������� �� ����� ��������� (10b = ������ �����)
     ;     11 = ��� �������� (11b = ������/������ ������� ��������, � ����� �������� �����)
     ;    011 = ����� ������ ������ (011b = ��������� ������������� ��������� (�������� �����))
     ;      0 = ������ �������� (0 = 16-��������� ����� �� 0 �� 0FFFFh)
  out 43h, al
  ret
endp

;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

proc SetBeeperOut
  ; ������� 1� ���, ���������� �� ��������� �������� �� ����� 61h - ����� ����������:
  in al, 61h
  or al, 00000010b
  out 61h, al
endp

;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

proc SetBeeperIn
  ; ���������� 1� ���, ���������� �� ��������� �������� �� ����� 61h - ������� ���������:
  in al, 61h
  and al, 11111101b
  out 61h, al
endp

;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

proc SetBeeperDivider ; Divider: Word
  mov ax, cx
  out 42h, al
  shr ax, 8
  out 42h, al
  ret
endp

;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

proc SetBeeperFrequency ; Frequency: Word
  ; Divider = Round(1193182 / Frequency):
  
  mov ax, 19
  cmp cx, ax
  cmovl cx, ax
  
  movzx ecx, cx
  xor edx, edx
  mov eax, 1193182
  div ecx
  
  out 42h, al
  shr ax, 8
  out 42h, al
  
  ret
endp


;HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH


proc WriteIoPortByte ; PortNumber: Word, InputData: Byte
  ; CX - ����� �����
  ; DL - ������
  mov al, dl
  mov dx, cx
  out dx, al
  ret
endp

;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

proc WriteIoPortWord ; PortNumber: Word, InputData: Word
  ; CX - ����� �����
  ; DX - ������
  mov ax, dx
  mov dx, cx
  out dx, ax
  ret
endp

;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

proc WriteIoPortDword ; PortNumber: Word, InputData: DWord
  ; CX - ����� �����
  ; EDX - ������
  mov eax, edx
  mov dx, cx
  out dx, eax
  ret
endp


;HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH


proc ReadIoPortByte ; PortNumber: Word 
  ; CX - ����� �����
  ; AL - ����������� ������
  mov dx, cx
  in al, dx
  ret
endp

;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

proc ReadIoPortWord ; PortNumber: Word
  ; CX - ����� �����
  ; AX - ����������� ������
  mov dx, cx
  in ax, dx
  ret
endp

;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

proc ReadIoPortDword ; PortNumber: Word
  ; CX - ����� �����
  ; EAX - ����������� ������
  mov dx, cx
  in eax, dx
  ret
endp