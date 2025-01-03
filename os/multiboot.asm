bits 32

section .text
  multiboot_header:    DD 0x1BADB002
  multiboot_flags:     DD 0x00000000
  multiboot_signature: DD -(0x1BADB002 + 0x00000000)
  multiboot_info_ptr:  DD 0x00000000

global start
extern k_entry

start:
  ; Turning off interrupts
  CLI

  ; Storing pointer
  mov eax, multiboot_info_ptr
  mov (eax), ebx

  ; Setting up stack
  mov esp, stack_space
  mov ebp, esp

  ; Jumping to kernel entry
  JMP k_entry

section .bss
RESB 8192
stack_space: