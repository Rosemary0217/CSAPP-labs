
bomb:     file format elf64-x86-64


Disassembly of section .init:

0000000000400a80 <_init>:
  400a80:	48 83 ec 08          	sub    $0x8,%rsp
  400a84:	48 8b 05 6d 25 20 00 	mov    0x20256d(%rip),%rax        # 602ff8 <__gmon_start__>
  400a8b:	48 85 c0             	test   %rax,%rax
  400a8e:	74 02                	je     400a92 <_init+0x12>
  400a90:	ff d0                	callq  *%rax
  400a92:	48 83 c4 08          	add    $0x8,%rsp
  400a96:	c3                   	retq   

Disassembly of section .plt:

0000000000400aa0 <.plt>:
  400aa0:	ff 35 62 25 20 00    	pushq  0x202562(%rip)        # 603008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400aa6:	ff 25 64 25 20 00    	jmpq   *0x202564(%rip)        # 603010 <_GLOBAL_OFFSET_TABLE_+0x10>
  400aac:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400ab0 <getenv@plt>:
  400ab0:	ff 25 62 25 20 00    	jmpq   *0x202562(%rip)        # 603018 <getenv@GLIBC_2.2.5>
  400ab6:	68 00 00 00 00       	pushq  $0x0
  400abb:	e9 e0 ff ff ff       	jmpq   400aa0 <.plt>

0000000000400ac0 <__errno_location@plt>:
  400ac0:	ff 25 5a 25 20 00    	jmpq   *0x20255a(%rip)        # 603020 <__errno_location@GLIBC_2.2.5>
  400ac6:	68 01 00 00 00       	pushq  $0x1
  400acb:	e9 d0 ff ff ff       	jmpq   400aa0 <.plt>

0000000000400ad0 <strcpy@plt>:
  400ad0:	ff 25 52 25 20 00    	jmpq   *0x202552(%rip)        # 603028 <strcpy@GLIBC_2.2.5>
  400ad6:	68 02 00 00 00       	pushq  $0x2
  400adb:	e9 c0 ff ff ff       	jmpq   400aa0 <.plt>

0000000000400ae0 <puts@plt>:
  400ae0:	ff 25 4a 25 20 00    	jmpq   *0x20254a(%rip)        # 603030 <puts@GLIBC_2.2.5>
  400ae6:	68 03 00 00 00       	pushq  $0x3
  400aeb:	e9 b0 ff ff ff       	jmpq   400aa0 <.plt>

0000000000400af0 <write@plt>:
  400af0:	ff 25 42 25 20 00    	jmpq   *0x202542(%rip)        # 603038 <write@GLIBC_2.2.5>
  400af6:	68 04 00 00 00       	pushq  $0x4
  400afb:	e9 a0 ff ff ff       	jmpq   400aa0 <.plt>

0000000000400b00 <__stack_chk_fail@plt>:
  400b00:	ff 25 3a 25 20 00    	jmpq   *0x20253a(%rip)        # 603040 <__stack_chk_fail@GLIBC_2.4>
  400b06:	68 05 00 00 00       	pushq  $0x5
  400b0b:	e9 90 ff ff ff       	jmpq   400aa0 <.plt>

0000000000400b10 <alarm@plt>:
  400b10:	ff 25 32 25 20 00    	jmpq   *0x202532(%rip)        # 603048 <alarm@GLIBC_2.2.5>
  400b16:	68 06 00 00 00       	pushq  $0x6
  400b1b:	e9 80 ff ff ff       	jmpq   400aa0 <.plt>

0000000000400b20 <close@plt>:
  400b20:	ff 25 2a 25 20 00    	jmpq   *0x20252a(%rip)        # 603050 <close@GLIBC_2.2.5>
  400b26:	68 07 00 00 00       	pushq  $0x7
  400b2b:	e9 70 ff ff ff       	jmpq   400aa0 <.plt>

0000000000400b30 <read@plt>:
  400b30:	ff 25 22 25 20 00    	jmpq   *0x202522(%rip)        # 603058 <read@GLIBC_2.2.5>
  400b36:	68 08 00 00 00       	pushq  $0x8
  400b3b:	e9 60 ff ff ff       	jmpq   400aa0 <.plt>

0000000000400b40 <fgets@plt>:
  400b40:	ff 25 1a 25 20 00    	jmpq   *0x20251a(%rip)        # 603060 <fgets@GLIBC_2.2.5>
  400b46:	68 09 00 00 00       	pushq  $0x9
  400b4b:	e9 50 ff ff ff       	jmpq   400aa0 <.plt>

0000000000400b50 <signal@plt>:
  400b50:	ff 25 12 25 20 00    	jmpq   *0x202512(%rip)        # 603068 <signal@GLIBC_2.2.5>
  400b56:	68 0a 00 00 00       	pushq  $0xa
  400b5b:	e9 40 ff ff ff       	jmpq   400aa0 <.plt>

0000000000400b60 <gethostbyname@plt>:
  400b60:	ff 25 0a 25 20 00    	jmpq   *0x20250a(%rip)        # 603070 <gethostbyname@GLIBC_2.2.5>
  400b66:	68 0b 00 00 00       	pushq  $0xb
  400b6b:	e9 30 ff ff ff       	jmpq   400aa0 <.plt>

0000000000400b70 <__memmove_chk@plt>:
  400b70:	ff 25 02 25 20 00    	jmpq   *0x202502(%rip)        # 603078 <__memmove_chk@GLIBC_2.3.4>
  400b76:	68 0c 00 00 00       	pushq  $0xc
  400b7b:	e9 20 ff ff ff       	jmpq   400aa0 <.plt>

0000000000400b80 <strtol@plt>:
  400b80:	ff 25 fa 24 20 00    	jmpq   *0x2024fa(%rip)        # 603080 <strtol@GLIBC_2.2.5>
  400b86:	68 0d 00 00 00       	pushq  $0xd
  400b8b:	e9 10 ff ff ff       	jmpq   400aa0 <.plt>

0000000000400b90 <fflush@plt>:
  400b90:	ff 25 f2 24 20 00    	jmpq   *0x2024f2(%rip)        # 603088 <fflush@GLIBC_2.2.5>
  400b96:	68 0e 00 00 00       	pushq  $0xe
  400b9b:	e9 00 ff ff ff       	jmpq   400aa0 <.plt>

0000000000400ba0 <__isoc99_sscanf@plt>:
  400ba0:	ff 25 ea 24 20 00    	jmpq   *0x2024ea(%rip)        # 603090 <__isoc99_sscanf@GLIBC_2.7>
  400ba6:	68 0f 00 00 00       	pushq  $0xf
  400bab:	e9 f0 fe ff ff       	jmpq   400aa0 <.plt>

0000000000400bb0 <__printf_chk@plt>:
  400bb0:	ff 25 e2 24 20 00    	jmpq   *0x2024e2(%rip)        # 603098 <__printf_chk@GLIBC_2.3.4>
  400bb6:	68 10 00 00 00       	pushq  $0x10
  400bbb:	e9 e0 fe ff ff       	jmpq   400aa0 <.plt>

0000000000400bc0 <fopen@plt>:
  400bc0:	ff 25 da 24 20 00    	jmpq   *0x2024da(%rip)        # 6030a0 <fopen@GLIBC_2.2.5>
  400bc6:	68 11 00 00 00       	pushq  $0x11
  400bcb:	e9 d0 fe ff ff       	jmpq   400aa0 <.plt>

0000000000400bd0 <exit@plt>:
  400bd0:	ff 25 d2 24 20 00    	jmpq   *0x2024d2(%rip)        # 6030a8 <exit@GLIBC_2.2.5>
  400bd6:	68 12 00 00 00       	pushq  $0x12
  400bdb:	e9 c0 fe ff ff       	jmpq   400aa0 <.plt>

0000000000400be0 <connect@plt>:
  400be0:	ff 25 ca 24 20 00    	jmpq   *0x2024ca(%rip)        # 6030b0 <connect@GLIBC_2.2.5>
  400be6:	68 13 00 00 00       	pushq  $0x13
  400beb:	e9 b0 fe ff ff       	jmpq   400aa0 <.plt>

0000000000400bf0 <__fprintf_chk@plt>:
  400bf0:	ff 25 c2 24 20 00    	jmpq   *0x2024c2(%rip)        # 6030b8 <__fprintf_chk@GLIBC_2.3.4>
  400bf6:	68 14 00 00 00       	pushq  $0x14
  400bfb:	e9 a0 fe ff ff       	jmpq   400aa0 <.plt>

0000000000400c00 <sleep@plt>:
  400c00:	ff 25 ba 24 20 00    	jmpq   *0x2024ba(%rip)        # 6030c0 <sleep@GLIBC_2.2.5>
  400c06:	68 15 00 00 00       	pushq  $0x15
  400c0b:	e9 90 fe ff ff       	jmpq   400aa0 <.plt>

0000000000400c10 <__ctype_b_loc@plt>:
  400c10:	ff 25 b2 24 20 00    	jmpq   *0x2024b2(%rip)        # 6030c8 <__ctype_b_loc@GLIBC_2.3>
  400c16:	68 16 00 00 00       	pushq  $0x16
  400c1b:	e9 80 fe ff ff       	jmpq   400aa0 <.plt>

0000000000400c20 <__sprintf_chk@plt>:
  400c20:	ff 25 aa 24 20 00    	jmpq   *0x2024aa(%rip)        # 6030d0 <__sprintf_chk@GLIBC_2.3.4>
  400c26:	68 17 00 00 00       	pushq  $0x17
  400c2b:	e9 70 fe ff ff       	jmpq   400aa0 <.plt>

0000000000400c30 <socket@plt>:
  400c30:	ff 25 a2 24 20 00    	jmpq   *0x2024a2(%rip)        # 6030d8 <socket@GLIBC_2.2.5>
  400c36:	68 18 00 00 00       	pushq  $0x18
  400c3b:	e9 60 fe ff ff       	jmpq   400aa0 <.plt>

Disassembly of section .text:

0000000000400c40 <_start>:
  400c40:	31 ed                	xor    %ebp,%ebp
  400c42:	49 89 d1             	mov    %rdx,%r9
  400c45:	5e                   	pop    %rsi
  400c46:	48 89 e2             	mov    %rsp,%rdx
  400c49:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  400c4d:	50                   	push   %rax
  400c4e:	54                   	push   %rsp
  400c4f:	49 c7 c0 70 22 40 00 	mov    $0x402270,%r8
  400c56:	48 c7 c1 00 22 40 00 	mov    $0x402200,%rcx
  400c5d:	48 c7 c7 27 0d 40 00 	mov    $0x400d27,%rdi
  400c64:	ff 15 86 23 20 00    	callq  *0x202386(%rip)        # 602ff0 <__libc_start_main@GLIBC_2.2.5>
  400c6a:	f4                   	hlt    
  400c6b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000400c70 <_dl_relocate_static_pie>:
  400c70:	f3 c3                	repz retq 
  400c72:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400c79:	00 00 00 
  400c7c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400c80 <deregister_tm_clones>:
  400c80:	55                   	push   %rbp
  400c81:	b8 40 37 60 00       	mov    $0x603740,%eax
  400c86:	48 3d 40 37 60 00    	cmp    $0x603740,%rax
  400c8c:	48 89 e5             	mov    %rsp,%rbp
  400c8f:	74 17                	je     400ca8 <deregister_tm_clones+0x28>
  400c91:	b8 00 00 00 00       	mov    $0x0,%eax
  400c96:	48 85 c0             	test   %rax,%rax
  400c99:	74 0d                	je     400ca8 <deregister_tm_clones+0x28>
  400c9b:	5d                   	pop    %rbp
  400c9c:	bf 40 37 60 00       	mov    $0x603740,%edi
  400ca1:	ff e0                	jmpq   *%rax
  400ca3:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400ca8:	5d                   	pop    %rbp
  400ca9:	c3                   	retq   
  400caa:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400cb0 <register_tm_clones>:
  400cb0:	be 40 37 60 00       	mov    $0x603740,%esi
  400cb5:	55                   	push   %rbp
  400cb6:	48 81 ee 40 37 60 00 	sub    $0x603740,%rsi
  400cbd:	48 89 e5             	mov    %rsp,%rbp
  400cc0:	48 c1 fe 03          	sar    $0x3,%rsi
  400cc4:	48 89 f0             	mov    %rsi,%rax
  400cc7:	48 c1 e8 3f          	shr    $0x3f,%rax
  400ccb:	48 01 c6             	add    %rax,%rsi
  400cce:	48 d1 fe             	sar    %rsi
  400cd1:	74 15                	je     400ce8 <register_tm_clones+0x38>
  400cd3:	b8 00 00 00 00       	mov    $0x0,%eax
  400cd8:	48 85 c0             	test   %rax,%rax
  400cdb:	74 0b                	je     400ce8 <register_tm_clones+0x38>
  400cdd:	5d                   	pop    %rbp
  400cde:	bf 40 37 60 00       	mov    $0x603740,%edi
  400ce3:	ff e0                	jmpq   *%rax
  400ce5:	0f 1f 00             	nopl   (%rax)
  400ce8:	5d                   	pop    %rbp
  400ce9:	c3                   	retq   
  400cea:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400cf0 <__do_global_dtors_aux>:
  400cf0:	80 3d 71 2a 20 00 00 	cmpb   $0x0,0x202a71(%rip)        # 603768 <completed.7698>
  400cf7:	75 17                	jne    400d10 <__do_global_dtors_aux+0x20>
  400cf9:	55                   	push   %rbp
  400cfa:	48 89 e5             	mov    %rsp,%rbp
  400cfd:	e8 7e ff ff ff       	callq  400c80 <deregister_tm_clones>
  400d02:	c6 05 5f 2a 20 00 01 	movb   $0x1,0x202a5f(%rip)        # 603768 <completed.7698>
  400d09:	5d                   	pop    %rbp
  400d0a:	c3                   	retq   
  400d0b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400d10:	f3 c3                	repz retq 
  400d12:	0f 1f 40 00          	nopl   0x0(%rax)
  400d16:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400d1d:	00 00 00 

0000000000400d20 <frame_dummy>:
  400d20:	55                   	push   %rbp
  400d21:	48 89 e5             	mov    %rsp,%rbp
  400d24:	5d                   	pop    %rbp
  400d25:	eb 89                	jmp    400cb0 <register_tm_clones>

0000000000400d27 <main>:
  400d27:	53                   	push   %rbx
  400d28:	83 ff 01             	cmp    $0x1,%edi
  400d2b:	0f 84 e8 00 00 00    	je     400e19 <main+0xf2>
  400d31:	48 89 f3             	mov    %rsi,%rbx
  400d34:	83 ff 02             	cmp    $0x2,%edi
  400d37:	0f 85 0f 01 00 00    	jne    400e4c <main+0x125>
  400d3d:	48 8b 7e 08          	mov    0x8(%rsi),%rdi
  400d41:	be 84 22 40 00       	mov    $0x402284,%esi
  400d46:	e8 75 fe ff ff       	callq  400bc0 <fopen@plt>
  400d4b:	48 89 05 1e 2a 20 00 	mov    %rax,0x202a1e(%rip)        # 603770 <infile>
  400d52:	48 85 c0             	test   %rax,%rax
  400d55:	0f 84 d1 00 00 00    	je     400e2c <main+0x105>
  400d5b:	e8 51 06 00 00       	callq  4013b1 <initialize_bomb>
  400d60:	bf 08 23 40 00       	mov    $0x402308,%edi
  400d65:	e8 76 fd ff ff       	callq  400ae0 <puts@plt>
  400d6a:	bf 48 23 40 00       	mov    $0x402348,%edi
  400d6f:	e8 6c fd ff ff       	callq  400ae0 <puts@plt>
  400d74:	e8 2f 07 00 00       	callq  4014a8 <read_line>
  400d79:	48 89 c7             	mov    %rax,%rdi
  400d7c:	e8 ec 00 00 00       	callq  400e6d <phase_1>
  400d81:	e8 50 08 00 00       	callq  4015d6 <phase_defused>
  400d86:	bf 78 23 40 00       	mov    $0x402378,%edi
  400d8b:	e8 50 fd ff ff       	callq  400ae0 <puts@plt>
  400d90:	e8 13 07 00 00       	callq  4014a8 <read_line>
  400d95:	48 89 c7             	mov    %rax,%rdi
  400d98:	e8 ee 00 00 00       	callq  400e8b <phase_2>
  400d9d:	e8 34 08 00 00       	callq  4015d6 <phase_defused>
  400da2:	bf bd 22 40 00       	mov    $0x4022bd,%edi
  400da7:	e8 34 fd ff ff       	callq  400ae0 <puts@plt>
  400dac:	e8 f7 06 00 00       	callq  4014a8 <read_line>
  400db1:	48 89 c7             	mov    %rax,%rdi
  400db4:	e8 3a 01 00 00       	callq  400ef3 <phase_3>
  400db9:	e8 18 08 00 00       	callq  4015d6 <phase_defused>
  400dbe:	bf db 22 40 00       	mov    $0x4022db,%edi
  400dc3:	e8 18 fd ff ff       	callq  400ae0 <puts@plt>
  400dc8:	e8 db 06 00 00       	callq  4014a8 <read_line>
  400dcd:	48 89 c7             	mov    %rax,%rdi
  400dd0:	e8 06 02 00 00       	callq  400fdb <phase_4>
  400dd5:	e8 fc 07 00 00       	callq  4015d6 <phase_defused>
  400dda:	bf a8 23 40 00       	mov    $0x4023a8,%edi
  400ddf:	e8 fc fc ff ff       	callq  400ae0 <puts@plt>
  400de4:	e8 bf 06 00 00       	callq  4014a8 <read_line>
  400de9:	48 89 c7             	mov    %rax,%rdi
  400dec:	e8 5d 02 00 00       	callq  40104e <phase_5>
  400df1:	e8 e0 07 00 00       	callq  4015d6 <phase_defused>
  400df6:	bf ea 22 40 00       	mov    $0x4022ea,%edi
  400dfb:	e8 e0 fc ff ff       	callq  400ae0 <puts@plt>
  400e00:	e8 a3 06 00 00       	callq  4014a8 <read_line>
  400e05:	48 89 c7             	mov    %rax,%rdi
  400e08:	e8 cf 02 00 00       	callq  4010dc <phase_6>
  400e0d:	e8 c4 07 00 00       	callq  4015d6 <phase_defused>
  400e12:	b8 00 00 00 00       	mov    $0x0,%eax
  400e17:	5b                   	pop    %rbx
  400e18:	c3                   	retq   
  400e19:	48 8b 05 30 29 20 00 	mov    0x202930(%rip),%rax        # 603750 <stdin@@GLIBC_2.2.5>
  400e20:	48 89 05 49 29 20 00 	mov    %rax,0x202949(%rip)        # 603770 <infile>
  400e27:	e9 2f ff ff ff       	jmpq   400d5b <main+0x34>
  400e2c:	48 8b 4b 08          	mov    0x8(%rbx),%rcx
  400e30:	48 8b 13             	mov    (%rbx),%rdx
  400e33:	be 86 22 40 00       	mov    $0x402286,%esi
  400e38:	bf 01 00 00 00       	mov    $0x1,%edi
  400e3d:	e8 6e fd ff ff       	callq  400bb0 <__printf_chk@plt>
  400e42:	bf 08 00 00 00       	mov    $0x8,%edi
  400e47:	e8 84 fd ff ff       	callq  400bd0 <exit@plt>
  400e4c:	48 8b 16             	mov    (%rsi),%rdx
  400e4f:	be a3 22 40 00       	mov    $0x4022a3,%esi
  400e54:	bf 01 00 00 00       	mov    $0x1,%edi
  400e59:	b8 00 00 00 00       	mov    $0x0,%eax
  400e5e:	e8 4d fd ff ff       	callq  400bb0 <__printf_chk@plt>
  400e63:	bf 08 00 00 00       	mov    $0x8,%edi
  400e68:	e8 63 fd ff ff       	callq  400bd0 <exit@plt>

0000000000400e6d <phase_1>:
  400e6d:	48 83 ec 08          	sub    $0x8,%rsp
  400e71:	be d0 23 40 00       	mov    $0x4023d0,%esi
  400e76:	e8 cf 04 00 00       	callq  40134a <strings_not_equal>
  400e7b:	85 c0                	test   %eax,%eax
  400e7d:	75 05                	jne    400e84 <phase_1+0x17>
  400e7f:	48 83 c4 08          	add    $0x8,%rsp
  400e83:	c3                   	retq   
  400e84:	e8 be 05 00 00       	callq  401447 <explode_bomb>
  400e89:	eb f4                	jmp    400e7f <phase_1+0x12>

0000000000400e8b <phase_2>:
  400e8b:	53                   	push   %rbx
  400e8c:	48 83 ec 20          	sub    $0x20,%rsp
  400e90:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  400e97:	00 00 
  400e99:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
  400e9e:	31 c0                	xor    %eax,%eax
  400ea0:	48 89 e6             	mov    %rsp,%rsi
  400ea3:	e8 c1 05 00 00       	callq  401469 <read_six_numbers>
  400ea8:	83 3c 24 00          	cmpl   $0x0,(%rsp)
  400eac:	78 07                	js     400eb5 <phase_2+0x2a>
  400eae:	bb 01 00 00 00       	mov    $0x1,%ebx
  400eb3:	eb 11                	jmp    400ec6 <phase_2+0x3b>
  400eb5:	e8 8d 05 00 00       	callq  401447 <explode_bomb>
  400eba:	eb f2                	jmp    400eae <phase_2+0x23>
  400ebc:	48 83 c3 01          	add    $0x1,%rbx
  400ec0:	48 83 fb 06          	cmp    $0x6,%rbx
  400ec4:	74 12                	je     400ed8 <phase_2+0x4d>
  400ec6:	89 d8                	mov    %ebx,%eax
  400ec8:	03 44 9c fc          	add    -0x4(%rsp,%rbx,4),%eax
  400ecc:	39 04 9c             	cmp    %eax,(%rsp,%rbx,4)
  400ecf:	74 eb                	je     400ebc <phase_2+0x31>
  400ed1:	e8 71 05 00 00       	callq  401447 <explode_bomb>
  400ed6:	eb e4                	jmp    400ebc <phase_2+0x31>
  400ed8:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  400edd:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  400ee4:	00 00 
  400ee6:	75 06                	jne    400eee <phase_2+0x63>
  400ee8:	48 83 c4 20          	add    $0x20,%rsp
  400eec:	5b                   	pop    %rbx
  400eed:	c3                   	retq   
  400eee:	e8 0d fc ff ff       	callq  400b00 <__stack_chk_fail@plt>

0000000000400ef3 <phase_3>:
  400ef3:	48 83 ec 18          	sub    $0x18,%rsp
  400ef7:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  400efe:	00 00 
  400f00:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  400f05:	31 c0                	xor    %eax,%eax
  400f07:	48 8d 4c 24 04       	lea    0x4(%rsp),%rcx
  400f0c:	48 89 e2             	mov    %rsp,%rdx
  400f0f:	be cf 25 40 00       	mov    $0x4025cf,%esi
  400f14:	e8 87 fc ff ff       	callq  400ba0 <__isoc99_sscanf@plt>
  400f19:	83 f8 01             	cmp    $0x1,%eax
  400f1c:	7e 10                	jle    400f2e <phase_3+0x3b>
  400f1e:	83 3c 24 07          	cmpl   $0x7,(%rsp)
  400f22:	77 42                	ja     400f66 <phase_3+0x73>
  400f24:	8b 04 24             	mov    (%rsp),%eax
  400f27:	ff 24 c5 40 24 40 00 	jmpq   *0x402440(,%rax,8)
  400f2e:	e8 14 05 00 00       	callq  401447 <explode_bomb>
  400f33:	eb e9                	jmp    400f1e <phase_3+0x2b>
  400f35:	b8 35 02 00 00       	mov    $0x235,%eax
  400f3a:	eb 3b                	jmp    400f77 <phase_3+0x84>
  400f3c:	b8 a7 01 00 00       	mov    $0x1a7,%eax
  400f41:	eb 34                	jmp    400f77 <phase_3+0x84>
  400f43:	b8 2b 02 00 00       	mov    $0x22b,%eax
  400f48:	eb 2d                	jmp    400f77 <phase_3+0x84>
  400f4a:	b8 6c 00 00 00       	mov    $0x6c,%eax
  400f4f:	eb 26                	jmp    400f77 <phase_3+0x84>
  400f51:	b8 f1 02 00 00       	mov    $0x2f1,%eax
  400f56:	eb 1f                	jmp    400f77 <phase_3+0x84>
  400f58:	b8 3e 00 00 00       	mov    $0x3e,%eax
  400f5d:	eb 18                	jmp    400f77 <phase_3+0x84>
  400f5f:	b8 48 02 00 00       	mov    $0x248,%eax
  400f64:	eb 11                	jmp    400f77 <phase_3+0x84>
  400f66:	e8 dc 04 00 00       	callq  401447 <explode_bomb>
  400f6b:	b8 00 00 00 00       	mov    $0x0,%eax
  400f70:	eb 05                	jmp    400f77 <phase_3+0x84>
  400f72:	b8 21 01 00 00       	mov    $0x121,%eax
  400f77:	39 44 24 04          	cmp    %eax,0x4(%rsp)
  400f7b:	74 05                	je     400f82 <phase_3+0x8f>
  400f7d:	e8 c5 04 00 00       	callq  401447 <explode_bomb>
  400f82:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  400f87:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  400f8e:	00 00 
  400f90:	75 05                	jne    400f97 <phase_3+0xa4>
  400f92:	48 83 c4 18          	add    $0x18,%rsp
  400f96:	c3                   	retq   
  400f97:	e8 64 fb ff ff       	callq  400b00 <__stack_chk_fail@plt>

0000000000400f9c <func4>:
  400f9c:	48 83 ec 08          	sub    $0x8,%rsp
  400fa0:	89 d0                	mov    %edx,%eax
  400fa2:	29 f0                	sub    %esi,%eax
  400fa4:	89 c1                	mov    %eax,%ecx
  400fa6:	c1 e9 1f             	shr    $0x1f,%ecx
  400fa9:	01 c1                	add    %eax,%ecx
  400fab:	d1 f9                	sar    %ecx
  400fad:	01 f1                	add    %esi,%ecx
  400faf:	39 f9                	cmp    %edi,%ecx
  400fb1:	7f 0e                	jg     400fc1 <func4+0x25>
  400fb3:	b8 00 00 00 00       	mov    $0x0,%eax
  400fb8:	39 f9                	cmp    %edi,%ecx
  400fba:	7c 11                	jl     400fcd <func4+0x31>
  400fbc:	48 83 c4 08          	add    $0x8,%rsp
  400fc0:	c3                   	retq   
  400fc1:	8d 51 ff             	lea    -0x1(%rcx),%edx
  400fc4:	e8 d3 ff ff ff       	callq  400f9c <func4>
  400fc9:	01 c0                	add    %eax,%eax
  400fcb:	eb ef                	jmp    400fbc <func4+0x20>
  400fcd:	8d 71 01             	lea    0x1(%rcx),%esi
  400fd0:	e8 c7 ff ff ff       	callq  400f9c <func4>
  400fd5:	8d 44 00 01          	lea    0x1(%rax,%rax,1),%eax
  400fd9:	eb e1                	jmp    400fbc <func4+0x20>

0000000000400fdb <phase_4>:
  400fdb:	48 83 ec 18          	sub    $0x18,%rsp
  400fdf:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  400fe6:	00 00 
  400fe8:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  400fed:	31 c0                	xor    %eax,%eax
  400fef:	48 8d 4c 24 04       	lea    0x4(%rsp),%rcx
  400ff4:	48 89 e2             	mov    %rsp,%rdx
  400ff7:	be cf 25 40 00       	mov    $0x4025cf,%esi
  400ffc:	e8 9f fb ff ff       	callq  400ba0 <__isoc99_sscanf@plt>
  401001:	83 f8 02             	cmp    $0x2,%eax
  401004:	75 06                	jne    40100c <phase_4+0x31>
  401006:	83 3c 24 0e          	cmpl   $0xe,(%rsp)
  40100a:	76 05                	jbe    401011 <phase_4+0x36>
  40100c:	e8 36 04 00 00       	callq  401447 <explode_bomb>
  401011:	ba 0e 00 00 00       	mov    $0xe,%edx
  401016:	be 00 00 00 00       	mov    $0x0,%esi
  40101b:	8b 3c 24             	mov    (%rsp),%edi
  40101e:	e8 79 ff ff ff       	callq  400f9c <func4>
  401023:	83 f8 03             	cmp    $0x3,%eax
  401026:	75 07                	jne    40102f <phase_4+0x54>
  401028:	83 7c 24 04 03       	cmpl   $0x3,0x4(%rsp)
  40102d:	74 05                	je     401034 <phase_4+0x59>
  40102f:	e8 13 04 00 00       	callq  401447 <explode_bomb>
  401034:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  401039:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  401040:	00 00 
  401042:	75 05                	jne    401049 <phase_4+0x6e>
  401044:	48 83 c4 18          	add    $0x18,%rsp
  401048:	c3                   	retq   
  401049:	e8 b2 fa ff ff       	callq  400b00 <__stack_chk_fail@plt>

000000000040104e <phase_5>:
  40104e:	48 83 ec 18          	sub    $0x18,%rsp
  401052:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401059:	00 00 
  40105b:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  401060:	31 c0                	xor    %eax,%eax
  401062:	48 8d 4c 24 04       	lea    0x4(%rsp),%rcx
  401067:	48 89 e2             	mov    %rsp,%rdx
  40106a:	be cf 25 40 00       	mov    $0x4025cf,%esi
  40106f:	e8 2c fb ff ff       	callq  400ba0 <__isoc99_sscanf@plt>
  401074:	83 f8 01             	cmp    $0x1,%eax
  401077:	7e 57                	jle    4010d0 <phase_5+0x82>
  401079:	8b 04 24             	mov    (%rsp),%eax
  40107c:	83 e0 0f             	and    $0xf,%eax
  40107f:	89 04 24             	mov    %eax,(%rsp)
  401082:	83 f8 0f             	cmp    $0xf,%eax
  401085:	74 2f                	je     4010b6 <phase_5+0x68>
  401087:	b9 00 00 00 00       	mov    $0x0,%ecx
  40108c:	ba 00 00 00 00       	mov    $0x0,%edx
  401091:	83 c2 01             	add    $0x1,%edx
  401094:	48 98                	cltq   
  401096:	8b 04 85 80 24 40 00 	mov    0x402480(,%rax,4),%eax
  40109d:	01 c1                	add    %eax,%ecx
  40109f:	83 f8 0f             	cmp    $0xf,%eax
  4010a2:	75 ed                	jne    401091 <phase_5+0x43>
  4010a4:	c7 04 24 0f 00 00 00 	movl   $0xf,(%rsp)
  4010ab:	83 fa 03             	cmp    $0x3,%edx
  4010ae:	75 06                	jne    4010b6 <phase_5+0x68>
  4010b0:	39 4c 24 04          	cmp    %ecx,0x4(%rsp)
  4010b4:	74 05                	je     4010bb <phase_5+0x6d>
  4010b6:	e8 8c 03 00 00       	callq  401447 <explode_bomb>
  4010bb:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  4010c0:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  4010c7:	00 00 
  4010c9:	75 0c                	jne    4010d7 <phase_5+0x89>
  4010cb:	48 83 c4 18          	add    $0x18,%rsp
  4010cf:	c3                   	retq   
  4010d0:	e8 72 03 00 00       	callq  401447 <explode_bomb>
  4010d5:	eb a2                	jmp    401079 <phase_5+0x2b>
  4010d7:	e8 24 fa ff ff       	callq  400b00 <__stack_chk_fail@plt>

00000000004010dc <phase_6>:
  4010dc:	41 56                	push   %r14
  4010de:	41 55                	push   %r13
  4010e0:	41 54                	push   %r12
  4010e2:	55                   	push   %rbp
  4010e3:	53                   	push   %rbx
  4010e4:	48 83 ec 60          	sub    $0x60,%rsp
  4010e8:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  4010ef:	00 00 
  4010f1:	48 89 44 24 58       	mov    %rax,0x58(%rsp)
  4010f6:	31 c0                	xor    %eax,%eax
  4010f8:	48 89 e6             	mov    %rsp,%rsi
  4010fb:	e8 69 03 00 00       	callq  401469 <read_six_numbers>
  401100:	49 89 e4             	mov    %rsp,%r12
  401103:	49 89 e5             	mov    %rsp,%r13
  401106:	41 be 00 00 00 00    	mov    $0x0,%r14d
  40110c:	eb 25                	jmp    401133 <phase_6+0x57>
  40110e:	e8 34 03 00 00       	callq  401447 <explode_bomb>
  401113:	eb 2d                	jmp    401142 <phase_6+0x66>
  401115:	83 c3 01             	add    $0x1,%ebx
  401118:	83 fb 05             	cmp    $0x5,%ebx
  40111b:	7f 12                	jg     40112f <phase_6+0x53>
  40111d:	48 63 c3             	movslq %ebx,%rax
  401120:	8b 04 84             	mov    (%rsp,%rax,4),%eax
  401123:	39 45 00             	cmp    %eax,0x0(%rbp)
  401126:	75 ed                	jne    401115 <phase_6+0x39>
  401128:	e8 1a 03 00 00       	callq  401447 <explode_bomb>
  40112d:	eb e6                	jmp    401115 <phase_6+0x39>
  40112f:	49 83 c5 04          	add    $0x4,%r13
  401133:	4c 89 ed             	mov    %r13,%rbp
  401136:	41 8b 45 00          	mov    0x0(%r13),%eax
  40113a:	83 e8 01             	sub    $0x1,%eax
  40113d:	83 f8 05             	cmp    $0x5,%eax
  401140:	77 cc                	ja     40110e <phase_6+0x32>
  401142:	41 83 c6 01          	add    $0x1,%r14d
  401146:	41 83 fe 06          	cmp    $0x6,%r14d
  40114a:	74 05                	je     401151 <phase_6+0x75>
  40114c:	44 89 f3             	mov    %r14d,%ebx
  40114f:	eb cc                	jmp    40111d <phase_6+0x41>
  401151:	49 8d 4c 24 18       	lea    0x18(%r12),%rcx
  401156:	ba 07 00 00 00       	mov    $0x7,%edx
  40115b:	89 d0                	mov    %edx,%eax
  40115d:	41 2b 04 24          	sub    (%r12),%eax
  401161:	41 89 04 24          	mov    %eax,(%r12)
  401165:	49 83 c4 04          	add    $0x4,%r12
  401169:	4c 39 e1             	cmp    %r12,%rcx
  40116c:	75 ed                	jne    40115b <phase_6+0x7f>
  40116e:	be 00 00 00 00       	mov    $0x0,%esi
  401173:	eb 1a                	jmp    40118f <phase_6+0xb3>
  401175:	48 8b 52 08          	mov    0x8(%rdx),%rdx
  401179:	83 c0 01             	add    $0x1,%eax
  40117c:	39 c8                	cmp    %ecx,%eax
  40117e:	75 f5                	jne    401175 <phase_6+0x99>
  401180:	48 89 54 f4 20       	mov    %rdx,0x20(%rsp,%rsi,8)
  401185:	48 83 c6 01          	add    $0x1,%rsi
  401189:	48 83 fe 06          	cmp    $0x6,%rsi
  40118d:	74 14                	je     4011a3 <phase_6+0xc7>
  40118f:	8b 0c b4             	mov    (%rsp,%rsi,4),%ecx
  401192:	b8 01 00 00 00       	mov    $0x1,%eax
  401197:	ba d0 32 60 00       	mov    $0x6032d0,%edx
  40119c:	83 f9 01             	cmp    $0x1,%ecx
  40119f:	7f d4                	jg     401175 <phase_6+0x99>
  4011a1:	eb dd                	jmp    401180 <phase_6+0xa4>
  4011a3:	48 8b 5c 24 20       	mov    0x20(%rsp),%rbx
  4011a8:	48 8b 44 24 28       	mov    0x28(%rsp),%rax
  4011ad:	48 89 43 08          	mov    %rax,0x8(%rbx)
  4011b1:	48 8b 54 24 30       	mov    0x30(%rsp),%rdx
  4011b6:	48 89 50 08          	mov    %rdx,0x8(%rax)
  4011ba:	48 8b 44 24 38       	mov    0x38(%rsp),%rax
  4011bf:	48 89 42 08          	mov    %rax,0x8(%rdx)
  4011c3:	48 8b 54 24 40       	mov    0x40(%rsp),%rdx
  4011c8:	48 89 50 08          	mov    %rdx,0x8(%rax)
  4011cc:	48 8b 44 24 48       	mov    0x48(%rsp),%rax
  4011d1:	48 89 42 08          	mov    %rax,0x8(%rdx)
  4011d5:	48 c7 40 08 00 00 00 	movq   $0x0,0x8(%rax)
  4011dc:	00 
  4011dd:	bd 05 00 00 00       	mov    $0x5,%ebp
  4011e2:	eb 09                	jmp    4011ed <phase_6+0x111>
  4011e4:	48 8b 5b 08          	mov    0x8(%rbx),%rbx
  4011e8:	83 ed 01             	sub    $0x1,%ebp
  4011eb:	74 11                	je     4011fe <phase_6+0x122>
  4011ed:	48 8b 43 08          	mov    0x8(%rbx),%rax
  4011f1:	8b 00                	mov    (%rax),%eax
  4011f3:	39 03                	cmp    %eax,(%rbx)
  4011f5:	7d ed                	jge    4011e4 <phase_6+0x108>
  4011f7:	e8 4b 02 00 00       	callq  401447 <explode_bomb>
  4011fc:	eb e6                	jmp    4011e4 <phase_6+0x108>
  4011fe:	48 8b 44 24 58       	mov    0x58(%rsp),%rax
  401203:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  40120a:	00 00 
  40120c:	75 0d                	jne    40121b <phase_6+0x13f>
  40120e:	48 83 c4 60          	add    $0x60,%rsp
  401212:	5b                   	pop    %rbx
  401213:	5d                   	pop    %rbp
  401214:	41 5c                	pop    %r12
  401216:	41 5d                	pop    %r13
  401218:	41 5e                	pop    %r14
  40121a:	c3                   	retq   
  40121b:	e8 e0 f8 ff ff       	callq  400b00 <__stack_chk_fail@plt>

0000000000401220 <fun7>:
  401220:	48 85 ff             	test   %rdi,%rdi
  401223:	74 34                	je     401259 <fun7+0x39>
  401225:	48 83 ec 08          	sub    $0x8,%rsp
  401229:	8b 17                	mov    (%rdi),%edx
  40122b:	39 f2                	cmp    %esi,%edx
  40122d:	7f 0e                	jg     40123d <fun7+0x1d>
  40122f:	b8 00 00 00 00       	mov    $0x0,%eax
  401234:	39 f2                	cmp    %esi,%edx
  401236:	75 12                	jne    40124a <fun7+0x2a>
  401238:	48 83 c4 08          	add    $0x8,%rsp
  40123c:	c3                   	retq   
  40123d:	48 8b 7f 08          	mov    0x8(%rdi),%rdi
  401241:	e8 da ff ff ff       	callq  401220 <fun7>
  401246:	01 c0                	add    %eax,%eax
  401248:	eb ee                	jmp    401238 <fun7+0x18>
  40124a:	48 8b 7f 10          	mov    0x10(%rdi),%rdi
  40124e:	e8 cd ff ff ff       	callq  401220 <fun7>
  401253:	8d 44 00 01          	lea    0x1(%rax,%rax,1),%eax
  401257:	eb df                	jmp    401238 <fun7+0x18>
  401259:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  40125e:	c3                   	retq   

000000000040125f <secret_phase>:
  40125f:	53                   	push   %rbx
  401260:	e8 43 02 00 00       	callq  4014a8 <read_line>
  401265:	ba 0a 00 00 00       	mov    $0xa,%edx
  40126a:	be 00 00 00 00       	mov    $0x0,%esi
  40126f:	48 89 c7             	mov    %rax,%rdi
  401272:	e8 09 f9 ff ff       	callq  400b80 <strtol@plt>
  401277:	48 89 c3             	mov    %rax,%rbx
  40127a:	8d 40 ff             	lea    -0x1(%rax),%eax
  40127d:	3d e8 03 00 00       	cmp    $0x3e8,%eax
  401282:	77 27                	ja     4012ab <secret_phase+0x4c>
  401284:	89 de                	mov    %ebx,%esi
  401286:	bf f0 30 60 00       	mov    $0x6030f0,%edi
  40128b:	e8 90 ff ff ff       	callq  401220 <fun7>
  401290:	83 f8 04             	cmp    $0x4,%eax
  401293:	74 05                	je     40129a <secret_phase+0x3b>
  401295:	e8 ad 01 00 00       	callq  401447 <explode_bomb>
  40129a:	bf 08 24 40 00       	mov    $0x402408,%edi
  40129f:	e8 3c f8 ff ff       	callq  400ae0 <puts@plt>
  4012a4:	e8 2d 03 00 00       	callq  4015d6 <phase_defused>
  4012a9:	5b                   	pop    %rbx
  4012aa:	c3                   	retq   
  4012ab:	e8 97 01 00 00       	callq  401447 <explode_bomb>
  4012b0:	eb d2                	jmp    401284 <secret_phase+0x25>

00000000004012b2 <sig_handler>:
  4012b2:	48 83 ec 08          	sub    $0x8,%rsp
  4012b6:	bf c0 24 40 00       	mov    $0x4024c0,%edi
  4012bb:	e8 20 f8 ff ff       	callq  400ae0 <puts@plt>
  4012c0:	bf 03 00 00 00       	mov    $0x3,%edi
  4012c5:	e8 36 f9 ff ff       	callq  400c00 <sleep@plt>
  4012ca:	be 82 25 40 00       	mov    $0x402582,%esi
  4012cf:	bf 01 00 00 00       	mov    $0x1,%edi
  4012d4:	b8 00 00 00 00       	mov    $0x0,%eax
  4012d9:	e8 d2 f8 ff ff       	callq  400bb0 <__printf_chk@plt>
  4012de:	48 8b 3d 5b 24 20 00 	mov    0x20245b(%rip),%rdi        # 603740 <stdout@@GLIBC_2.2.5>
  4012e5:	e8 a6 f8 ff ff       	callq  400b90 <fflush@plt>
  4012ea:	bf 01 00 00 00       	mov    $0x1,%edi
  4012ef:	e8 0c f9 ff ff       	callq  400c00 <sleep@plt>
  4012f4:	bf 8a 25 40 00       	mov    $0x40258a,%edi
  4012f9:	e8 e2 f7 ff ff       	callq  400ae0 <puts@plt>
  4012fe:	bf 10 00 00 00       	mov    $0x10,%edi
  401303:	e8 c8 f8 ff ff       	callq  400bd0 <exit@plt>

0000000000401308 <invalid_phase>:
  401308:	48 83 ec 08          	sub    $0x8,%rsp
  40130c:	48 89 fa             	mov    %rdi,%rdx
  40130f:	be 92 25 40 00       	mov    $0x402592,%esi
  401314:	bf 01 00 00 00       	mov    $0x1,%edi
  401319:	b8 00 00 00 00       	mov    $0x0,%eax
  40131e:	e8 8d f8 ff ff       	callq  400bb0 <__printf_chk@plt>
  401323:	bf 08 00 00 00       	mov    $0x8,%edi
  401328:	e8 a3 f8 ff ff       	callq  400bd0 <exit@plt>

000000000040132d <string_length>:
  40132d:	80 3f 00             	cmpb   $0x0,(%rdi)
  401330:	74 12                	je     401344 <string_length+0x17>
  401332:	48 89 fa             	mov    %rdi,%rdx
  401335:	48 83 c2 01          	add    $0x1,%rdx
  401339:	89 d0                	mov    %edx,%eax
  40133b:	29 f8                	sub    %edi,%eax
  40133d:	80 3a 00             	cmpb   $0x0,(%rdx)
  401340:	75 f3                	jne    401335 <string_length+0x8>
  401342:	f3 c3                	repz retq 
  401344:	b8 00 00 00 00       	mov    $0x0,%eax
  401349:	c3                   	retq   

000000000040134a <strings_not_equal>:
  40134a:	41 54                	push   %r12
  40134c:	55                   	push   %rbp
  40134d:	53                   	push   %rbx
  40134e:	48 89 fb             	mov    %rdi,%rbx
  401351:	48 89 f5             	mov    %rsi,%rbp
  401354:	e8 d4 ff ff ff       	callq  40132d <string_length>
  401359:	41 89 c4             	mov    %eax,%r12d
  40135c:	48 89 ef             	mov    %rbp,%rdi
  40135f:	e8 c9 ff ff ff       	callq  40132d <string_length>
  401364:	ba 01 00 00 00       	mov    $0x1,%edx
  401369:	41 39 c4             	cmp    %eax,%r12d
  40136c:	74 07                	je     401375 <strings_not_equal+0x2b>
  40136e:	89 d0                	mov    %edx,%eax
  401370:	5b                   	pop    %rbx
  401371:	5d                   	pop    %rbp
  401372:	41 5c                	pop    %r12
  401374:	c3                   	retq   
  401375:	0f b6 03             	movzbl (%rbx),%eax
  401378:	84 c0                	test   %al,%al
  40137a:	74 27                	je     4013a3 <strings_not_equal+0x59>
  40137c:	3a 45 00             	cmp    0x0(%rbp),%al
  40137f:	75 29                	jne    4013aa <strings_not_equal+0x60>
  401381:	48 83 c3 01          	add    $0x1,%rbx
  401385:	48 83 c5 01          	add    $0x1,%rbp
  401389:	0f b6 03             	movzbl (%rbx),%eax
  40138c:	84 c0                	test   %al,%al
  40138e:	74 0c                	je     40139c <strings_not_equal+0x52>
  401390:	38 45 00             	cmp    %al,0x0(%rbp)
  401393:	74 ec                	je     401381 <strings_not_equal+0x37>
  401395:	ba 01 00 00 00       	mov    $0x1,%edx
  40139a:	eb d2                	jmp    40136e <strings_not_equal+0x24>
  40139c:	ba 00 00 00 00       	mov    $0x0,%edx
  4013a1:	eb cb                	jmp    40136e <strings_not_equal+0x24>
  4013a3:	ba 00 00 00 00       	mov    $0x0,%edx
  4013a8:	eb c4                	jmp    40136e <strings_not_equal+0x24>
  4013aa:	ba 01 00 00 00       	mov    $0x1,%edx
  4013af:	eb bd                	jmp    40136e <strings_not_equal+0x24>

00000000004013b1 <initialize_bomb>:
  4013b1:	48 83 ec 08          	sub    $0x8,%rsp
  4013b5:	be b2 12 40 00       	mov    $0x4012b2,%esi
  4013ba:	bf 02 00 00 00       	mov    $0x2,%edi
  4013bf:	e8 8c f7 ff ff       	callq  400b50 <signal@plt>
  4013c4:	48 83 c4 08          	add    $0x8,%rsp
  4013c8:	c3                   	retq   

00000000004013c9 <initialize_bomb_solve>:
  4013c9:	f3 c3                	repz retq 

00000000004013cb <blank_line>:
  4013cb:	55                   	push   %rbp
  4013cc:	53                   	push   %rbx
  4013cd:	48 83 ec 08          	sub    $0x8,%rsp
  4013d1:	48 89 fd             	mov    %rdi,%rbp
  4013d4:	0f b6 5d 00          	movzbl 0x0(%rbp),%ebx
  4013d8:	84 db                	test   %bl,%bl
  4013da:	74 1e                	je     4013fa <blank_line+0x2f>
  4013dc:	e8 2f f8 ff ff       	callq  400c10 <__ctype_b_loc@plt>
  4013e1:	48 83 c5 01          	add    $0x1,%rbp
  4013e5:	48 0f be db          	movsbq %bl,%rbx
  4013e9:	48 8b 00             	mov    (%rax),%rax
  4013ec:	f6 44 58 01 20       	testb  $0x20,0x1(%rax,%rbx,2)
  4013f1:	75 e1                	jne    4013d4 <blank_line+0x9>
  4013f3:	b8 00 00 00 00       	mov    $0x0,%eax
  4013f8:	eb 05                	jmp    4013ff <blank_line+0x34>
  4013fa:	b8 01 00 00 00       	mov    $0x1,%eax
  4013ff:	48 83 c4 08          	add    $0x8,%rsp
  401403:	5b                   	pop    %rbx
  401404:	5d                   	pop    %rbp
  401405:	c3                   	retq   

0000000000401406 <skip>:
  401406:	53                   	push   %rbx
  401407:	48 63 05 5e 23 20 00 	movslq 0x20235e(%rip),%rax        # 60376c <num_input_strings>
  40140e:	48 8d 3c 80          	lea    (%rax,%rax,4),%rdi
  401412:	48 c1 e7 04          	shl    $0x4,%rdi
  401416:	48 81 c7 80 37 60 00 	add    $0x603780,%rdi
  40141d:	48 8b 15 4c 23 20 00 	mov    0x20234c(%rip),%rdx        # 603770 <infile>
  401424:	be 50 00 00 00       	mov    $0x50,%esi
  401429:	e8 12 f7 ff ff       	callq  400b40 <fgets@plt>
  40142e:	48 89 c3             	mov    %rax,%rbx
  401431:	48 85 c0             	test   %rax,%rax
  401434:	74 0c                	je     401442 <skip+0x3c>
  401436:	48 89 c7             	mov    %rax,%rdi
  401439:	e8 8d ff ff ff       	callq  4013cb <blank_line>
  40143e:	85 c0                	test   %eax,%eax
  401440:	75 c5                	jne    401407 <skip+0x1>
  401442:	48 89 d8             	mov    %rbx,%rax
  401445:	5b                   	pop    %rbx
  401446:	c3                   	retq   

0000000000401447 <explode_bomb>:
  401447:	48 83 ec 08          	sub    $0x8,%rsp
  40144b:	bf a3 25 40 00       	mov    $0x4025a3,%edi
  401450:	e8 8b f6 ff ff       	callq  400ae0 <puts@plt>
  401455:	bf ac 25 40 00       	mov    $0x4025ac,%edi
  40145a:	e8 81 f6 ff ff       	callq  400ae0 <puts@plt>
  40145f:	bf 08 00 00 00       	mov    $0x8,%edi
  401464:	e8 67 f7 ff ff       	callq  400bd0 <exit@plt>

0000000000401469 <read_six_numbers>:
  401469:	48 83 ec 08          	sub    $0x8,%rsp
  40146d:	48 89 f2             	mov    %rsi,%rdx
  401470:	48 8d 4e 04          	lea    0x4(%rsi),%rcx
  401474:	48 8d 46 14          	lea    0x14(%rsi),%rax
  401478:	50                   	push   %rax
  401479:	48 8d 46 10          	lea    0x10(%rsi),%rax
  40147d:	50                   	push   %rax
  40147e:	4c 8d 4e 0c          	lea    0xc(%rsi),%r9
  401482:	4c 8d 46 08          	lea    0x8(%rsi),%r8
  401486:	be c3 25 40 00       	mov    $0x4025c3,%esi
  40148b:	b8 00 00 00 00       	mov    $0x0,%eax
  401490:	e8 0b f7 ff ff       	callq  400ba0 <__isoc99_sscanf@plt>
  401495:	48 83 c4 10          	add    $0x10,%rsp
  401499:	83 f8 05             	cmp    $0x5,%eax
  40149c:	7e 05                	jle    4014a3 <read_six_numbers+0x3a>
  40149e:	48 83 c4 08          	add    $0x8,%rsp
  4014a2:	c3                   	retq   
  4014a3:	e8 9f ff ff ff       	callq  401447 <explode_bomb>

00000000004014a8 <read_line>:
  4014a8:	48 83 ec 08          	sub    $0x8,%rsp
  4014ac:	b8 00 00 00 00       	mov    $0x0,%eax
  4014b1:	e8 50 ff ff ff       	callq  401406 <skip>
  4014b6:	48 85 c0             	test   %rax,%rax
  4014b9:	74 63                	je     40151e <read_line+0x76>
  4014bb:	8b 35 ab 22 20 00    	mov    0x2022ab(%rip),%esi        # 60376c <num_input_strings>
  4014c1:	48 63 c6             	movslq %esi,%rax
  4014c4:	48 8d 14 80          	lea    (%rax,%rax,4),%rdx
  4014c8:	48 c1 e2 04          	shl    $0x4,%rdx
  4014cc:	48 81 c2 80 37 60 00 	add    $0x603780,%rdx
  4014d3:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  4014da:	b8 00 00 00 00       	mov    $0x0,%eax
  4014df:	48 89 d7             	mov    %rdx,%rdi
  4014e2:	f2 ae                	repnz scas %es:(%rdi),%al
  4014e4:	48 f7 d1             	not    %rcx
  4014e7:	48 83 e9 01          	sub    $0x1,%rcx
  4014eb:	83 f9 4e             	cmp    $0x4e,%ecx
  4014ee:	0f 8f 9c 00 00 00    	jg     401590 <read_line+0xe8>
  4014f4:	83 e9 01             	sub    $0x1,%ecx
  4014f7:	48 63 c9             	movslq %ecx,%rcx
  4014fa:	48 63 c6             	movslq %esi,%rax
  4014fd:	48 8d 04 80          	lea    (%rax,%rax,4),%rax
  401501:	48 c1 e0 04          	shl    $0x4,%rax
  401505:	c6 84 01 80 37 60 00 	movb   $0x0,0x603780(%rcx,%rax,1)
  40150c:	00 
  40150d:	8d 46 01             	lea    0x1(%rsi),%eax
  401510:	89 05 56 22 20 00    	mov    %eax,0x202256(%rip)        # 60376c <num_input_strings>
  401516:	48 89 d0             	mov    %rdx,%rax
  401519:	48 83 c4 08          	add    $0x8,%rsp
  40151d:	c3                   	retq   
  40151e:	48 8b 05 2b 22 20 00 	mov    0x20222b(%rip),%rax        # 603750 <stdin@@GLIBC_2.2.5>
  401525:	48 39 05 44 22 20 00 	cmp    %rax,0x202244(%rip)        # 603770 <infile>
  40152c:	74 19                	je     401547 <read_line+0x9f>
  40152e:	bf f3 25 40 00       	mov    $0x4025f3,%edi
  401533:	e8 78 f5 ff ff       	callq  400ab0 <getenv@plt>
  401538:	48 85 c0             	test   %rax,%rax
  40153b:	74 1e                	je     40155b <read_line+0xb3>
  40153d:	bf 00 00 00 00       	mov    $0x0,%edi
  401542:	e8 89 f6 ff ff       	callq  400bd0 <exit@plt>
  401547:	bf d5 25 40 00       	mov    $0x4025d5,%edi
  40154c:	e8 8f f5 ff ff       	callq  400ae0 <puts@plt>
  401551:	bf 08 00 00 00       	mov    $0x8,%edi
  401556:	e8 75 f6 ff ff       	callq  400bd0 <exit@plt>
  40155b:	48 8b 05 ee 21 20 00 	mov    0x2021ee(%rip),%rax        # 603750 <stdin@@GLIBC_2.2.5>
  401562:	48 89 05 07 22 20 00 	mov    %rax,0x202207(%rip)        # 603770 <infile>
  401569:	b8 00 00 00 00       	mov    $0x0,%eax
  40156e:	e8 93 fe ff ff       	callq  401406 <skip>
  401573:	48 85 c0             	test   %rax,%rax
  401576:	0f 85 3f ff ff ff    	jne    4014bb <read_line+0x13>
  40157c:	bf d5 25 40 00       	mov    $0x4025d5,%edi
  401581:	e8 5a f5 ff ff       	callq  400ae0 <puts@plt>
  401586:	bf 00 00 00 00       	mov    $0x0,%edi
  40158b:	e8 40 f6 ff ff       	callq  400bd0 <exit@plt>
  401590:	bf fe 25 40 00       	mov    $0x4025fe,%edi
  401595:	e8 46 f5 ff ff       	callq  400ae0 <puts@plt>
  40159a:	8b 05 cc 21 20 00    	mov    0x2021cc(%rip),%eax        # 60376c <num_input_strings>
  4015a0:	8d 50 01             	lea    0x1(%rax),%edx
  4015a3:	89 15 c3 21 20 00    	mov    %edx,0x2021c3(%rip)        # 60376c <num_input_strings>
  4015a9:	48 98                	cltq   
  4015ab:	48 6b c0 50          	imul   $0x50,%rax,%rax
  4015af:	48 be 2a 2a 2a 74 72 	movabs $0x636e7572742a2a2a,%rsi
  4015b6:	75 6e 63 
  4015b9:	48 bf 61 74 65 64 2a 	movabs $0x2a2a2a64657461,%rdi
  4015c0:	2a 2a 00 
  4015c3:	48 89 b0 80 37 60 00 	mov    %rsi,0x603780(%rax)
  4015ca:	48 89 b8 88 37 60 00 	mov    %rdi,0x603788(%rax)
  4015d1:	e8 71 fe ff ff       	callq  401447 <explode_bomb>

00000000004015d6 <phase_defused>:
  4015d6:	48 83 ec 78          	sub    $0x78,%rsp
  4015da:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  4015e1:	00 00 
  4015e3:	48 89 44 24 68       	mov    %rax,0x68(%rsp)
  4015e8:	31 c0                	xor    %eax,%eax
  4015ea:	83 3d 7b 21 20 00 06 	cmpl   $0x6,0x20217b(%rip)        # 60376c <num_input_strings>
  4015f1:	74 15                	je     401608 <phase_defused+0x32>
  4015f3:	48 8b 44 24 68       	mov    0x68(%rsp),%rax
  4015f8:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  4015ff:	00 00 
  401601:	75 67                	jne    40166a <phase_defused+0x94>
  401603:	48 83 c4 78          	add    $0x78,%rsp
  401607:	c3                   	retq   
  401608:	4c 8d 44 24 10       	lea    0x10(%rsp),%r8
  40160d:	48 8d 4c 24 0c       	lea    0xc(%rsp),%rcx
  401612:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx
  401617:	be 19 26 40 00       	mov    $0x402619,%esi
  40161c:	bf 70 38 60 00       	mov    $0x603870,%edi
  401621:	e8 7a f5 ff ff       	callq  400ba0 <__isoc99_sscanf@plt>
  401626:	83 f8 03             	cmp    $0x3,%eax
  401629:	74 0c                	je     401637 <phase_defused+0x61>
  40162b:	bf 58 25 40 00       	mov    $0x402558,%edi
  401630:	e8 ab f4 ff ff       	callq  400ae0 <puts@plt>
  401635:	eb bc                	jmp    4015f3 <phase_defused+0x1d>
  401637:	be 22 26 40 00       	mov    $0x402622,%esi
  40163c:	48 8d 7c 24 10       	lea    0x10(%rsp),%rdi
  401641:	e8 04 fd ff ff       	callq  40134a <strings_not_equal>
  401646:	85 c0                	test   %eax,%eax
  401648:	75 e1                	jne    40162b <phase_defused+0x55>
  40164a:	bf f8 24 40 00       	mov    $0x4024f8,%edi
  40164f:	e8 8c f4 ff ff       	callq  400ae0 <puts@plt>
  401654:	bf 20 25 40 00       	mov    $0x402520,%edi
  401659:	e8 82 f4 ff ff       	callq  400ae0 <puts@plt>
  40165e:	b8 00 00 00 00       	mov    $0x0,%eax
  401663:	e8 f7 fb ff ff       	callq  40125f <secret_phase>
  401668:	eb c1                	jmp    40162b <phase_defused+0x55>
  40166a:	e8 91 f4 ff ff       	callq  400b00 <__stack_chk_fail@plt>

000000000040166f <sigalrm_handler>:
  40166f:	48 83 ec 08          	sub    $0x8,%rsp
  401673:	b9 00 00 00 00       	mov    $0x0,%ecx
  401678:	ba 90 26 40 00       	mov    $0x402690,%edx
  40167d:	be 01 00 00 00       	mov    $0x1,%esi
  401682:	48 8b 3d d7 20 20 00 	mov    0x2020d7(%rip),%rdi        # 603760 <stderr@@GLIBC_2.2.5>
  401689:	b8 00 00 00 00       	mov    $0x0,%eax
  40168e:	e8 5d f5 ff ff       	callq  400bf0 <__fprintf_chk@plt>
  401693:	bf 01 00 00 00       	mov    $0x1,%edi
  401698:	e8 33 f5 ff ff       	callq  400bd0 <exit@plt>

000000000040169d <rio_readlineb>:
  40169d:	41 56                	push   %r14
  40169f:	41 55                	push   %r13
  4016a1:	41 54                	push   %r12
  4016a3:	55                   	push   %rbp
  4016a4:	53                   	push   %rbx
  4016a5:	48 89 fb             	mov    %rdi,%rbx
  4016a8:	49 89 f4             	mov    %rsi,%r12
  4016ab:	49 89 d6             	mov    %rdx,%r14
  4016ae:	41 bd 01 00 00 00    	mov    $0x1,%r13d
  4016b4:	48 8d 6f 10          	lea    0x10(%rdi),%rbp
  4016b8:	48 83 fa 01          	cmp    $0x1,%rdx
  4016bc:	77 0c                	ja     4016ca <rio_readlineb+0x2d>
  4016be:	eb 60                	jmp    401720 <rio_readlineb+0x83>
  4016c0:	e8 fb f3 ff ff       	callq  400ac0 <__errno_location@plt>
  4016c5:	83 38 04             	cmpl   $0x4,(%rax)
  4016c8:	75 67                	jne    401731 <rio_readlineb+0x94>
  4016ca:	8b 43 04             	mov    0x4(%rbx),%eax
  4016cd:	85 c0                	test   %eax,%eax
  4016cf:	7f 20                	jg     4016f1 <rio_readlineb+0x54>
  4016d1:	ba 00 20 00 00       	mov    $0x2000,%edx
  4016d6:	48 89 ee             	mov    %rbp,%rsi
  4016d9:	8b 3b                	mov    (%rbx),%edi
  4016db:	e8 50 f4 ff ff       	callq  400b30 <read@plt>
  4016e0:	89 43 04             	mov    %eax,0x4(%rbx)
  4016e3:	85 c0                	test   %eax,%eax
  4016e5:	78 d9                	js     4016c0 <rio_readlineb+0x23>
  4016e7:	85 c0                	test   %eax,%eax
  4016e9:	74 4f                	je     40173a <rio_readlineb+0x9d>
  4016eb:	48 89 6b 08          	mov    %rbp,0x8(%rbx)
  4016ef:	eb d9                	jmp    4016ca <rio_readlineb+0x2d>
  4016f1:	48 8b 53 08          	mov    0x8(%rbx),%rdx
  4016f5:	0f b6 0a             	movzbl (%rdx),%ecx
  4016f8:	48 83 c2 01          	add    $0x1,%rdx
  4016fc:	48 89 53 08          	mov    %rdx,0x8(%rbx)
  401700:	83 e8 01             	sub    $0x1,%eax
  401703:	89 43 04             	mov    %eax,0x4(%rbx)
  401706:	49 83 c4 01          	add    $0x1,%r12
  40170a:	41 88 4c 24 ff       	mov    %cl,-0x1(%r12)
  40170f:	80 f9 0a             	cmp    $0xa,%cl
  401712:	74 0c                	je     401720 <rio_readlineb+0x83>
  401714:	41 83 c5 01          	add    $0x1,%r13d
  401718:	49 63 c5             	movslq %r13d,%rax
  40171b:	4c 39 f0             	cmp    %r14,%rax
  40171e:	72 aa                	jb     4016ca <rio_readlineb+0x2d>
  401720:	41 c6 04 24 00       	movb   $0x0,(%r12)
  401725:	49 63 c5             	movslq %r13d,%rax
  401728:	5b                   	pop    %rbx
  401729:	5d                   	pop    %rbp
  40172a:	41 5c                	pop    %r12
  40172c:	41 5d                	pop    %r13
  40172e:	41 5e                	pop    %r14
  401730:	c3                   	retq   
  401731:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  401738:	eb 05                	jmp    40173f <rio_readlineb+0xa2>
  40173a:	b8 00 00 00 00       	mov    $0x0,%eax
  40173f:	85 c0                	test   %eax,%eax
  401741:	75 0d                	jne    401750 <rio_readlineb+0xb3>
  401743:	b8 00 00 00 00       	mov    $0x0,%eax
  401748:	41 83 fd 01          	cmp    $0x1,%r13d
  40174c:	75 d2                	jne    401720 <rio_readlineb+0x83>
  40174e:	eb d8                	jmp    401728 <rio_readlineb+0x8b>
  401750:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  401757:	eb cf                	jmp    401728 <rio_readlineb+0x8b>

0000000000401759 <submitr>:
  401759:	41 57                	push   %r15
  40175b:	41 56                	push   %r14
  40175d:	41 55                	push   %r13
  40175f:	41 54                	push   %r12
  401761:	55                   	push   %rbp
  401762:	53                   	push   %rbx
  401763:	48 81 ec 68 a0 00 00 	sub    $0xa068,%rsp
  40176a:	49 89 fd             	mov    %rdi,%r13
  40176d:	89 f5                	mov    %esi,%ebp
  40176f:	48 89 14 24          	mov    %rdx,(%rsp)
  401773:	48 89 4c 24 08       	mov    %rcx,0x8(%rsp)
  401778:	4c 89 44 24 18       	mov    %r8,0x18(%rsp)
  40177d:	4c 89 4c 24 10       	mov    %r9,0x10(%rsp)
  401782:	48 8b 9c 24 a0 a0 00 	mov    0xa0a0(%rsp),%rbx
  401789:	00 
  40178a:	4c 8b bc 24 a8 a0 00 	mov    0xa0a8(%rsp),%r15
  401791:	00 
  401792:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401799:	00 00 
  40179b:	48 89 84 24 58 a0 00 	mov    %rax,0xa058(%rsp)
  4017a2:	00 
  4017a3:	31 c0                	xor    %eax,%eax
  4017a5:	c7 44 24 2c 00 00 00 	movl   $0x0,0x2c(%rsp)
  4017ac:	00 
  4017ad:	ba 00 00 00 00       	mov    $0x0,%edx
  4017b2:	be 01 00 00 00       	mov    $0x1,%esi
  4017b7:	bf 02 00 00 00       	mov    $0x2,%edi
  4017bc:	e8 6f f4 ff ff       	callq  400c30 <socket@plt>
  4017c1:	85 c0                	test   %eax,%eax
  4017c3:	0f 88 24 01 00 00    	js     4018ed <submitr+0x194>
  4017c9:	41 89 c4             	mov    %eax,%r12d
  4017cc:	4c 89 ef             	mov    %r13,%rdi
  4017cf:	e8 8c f3 ff ff       	callq  400b60 <gethostbyname@plt>
  4017d4:	48 85 c0             	test   %rax,%rax
  4017d7:	0f 84 60 01 00 00    	je     40193d <submitr+0x1e4>
  4017dd:	48 c7 44 24 32 00 00 	movq   $0x0,0x32(%rsp)
  4017e4:	00 00 
  4017e6:	c7 44 24 3a 00 00 00 	movl   $0x0,0x3a(%rsp)
  4017ed:	00 
  4017ee:	66 c7 44 24 3e 00 00 	movw   $0x0,0x3e(%rsp)
  4017f5:	66 c7 44 24 30 02 00 	movw   $0x2,0x30(%rsp)
  4017fc:	48 63 50 14          	movslq 0x14(%rax),%rdx
  401800:	48 8b 40 18          	mov    0x18(%rax),%rax
  401804:	48 8d 7c 24 34       	lea    0x34(%rsp),%rdi
  401809:	b9 0c 00 00 00       	mov    $0xc,%ecx
  40180e:	48 8b 30             	mov    (%rax),%rsi
  401811:	e8 5a f3 ff ff       	callq  400b70 <__memmove_chk@plt>
  401816:	66 c1 cd 08          	ror    $0x8,%bp
  40181a:	66 89 6c 24 32       	mov    %bp,0x32(%rsp)
  40181f:	ba 10 00 00 00       	mov    $0x10,%edx
  401824:	48 8d 74 24 30       	lea    0x30(%rsp),%rsi
  401829:	44 89 e7             	mov    %r12d,%edi
  40182c:	e8 af f3 ff ff       	callq  400be0 <connect@plt>
  401831:	85 c0                	test   %eax,%eax
  401833:	0f 88 6f 01 00 00    	js     4019a8 <submitr+0x24f>
  401839:	49 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%r9
  401840:	b8 00 00 00 00       	mov    $0x0,%eax
  401845:	4c 89 c9             	mov    %r9,%rcx
  401848:	48 89 df             	mov    %rbx,%rdi
  40184b:	f2 ae                	repnz scas %es:(%rdi),%al
  40184d:	48 89 ce             	mov    %rcx,%rsi
  401850:	48 f7 d6             	not    %rsi
  401853:	4c 89 c9             	mov    %r9,%rcx
  401856:	48 8b 3c 24          	mov    (%rsp),%rdi
  40185a:	f2 ae                	repnz scas %es:(%rdi),%al
  40185c:	49 89 c8             	mov    %rcx,%r8
  40185f:	4c 89 c9             	mov    %r9,%rcx
  401862:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
  401867:	f2 ae                	repnz scas %es:(%rdi),%al
  401869:	48 89 ca             	mov    %rcx,%rdx
  40186c:	48 f7 d2             	not    %rdx
  40186f:	4c 89 c9             	mov    %r9,%rcx
  401872:	48 8b 7c 24 10       	mov    0x10(%rsp),%rdi
  401877:	f2 ae                	repnz scas %es:(%rdi),%al
  401879:	4c 29 c2             	sub    %r8,%rdx
  40187c:	48 29 ca             	sub    %rcx,%rdx
  40187f:	48 8d 44 76 fd       	lea    -0x3(%rsi,%rsi,2),%rax
  401884:	48 8d 44 02 7b       	lea    0x7b(%rdx,%rax,1),%rax
  401889:	48 3d 00 20 00 00    	cmp    $0x2000,%rax
  40188f:	0f 87 70 01 00 00    	ja     401a05 <submitr+0x2ac>
  401895:	48 8d 94 24 50 40 00 	lea    0x4050(%rsp),%rdx
  40189c:	00 
  40189d:	b9 00 04 00 00       	mov    $0x400,%ecx
  4018a2:	b8 00 00 00 00       	mov    $0x0,%eax
  4018a7:	48 89 d7             	mov    %rdx,%rdi
  4018aa:	f3 48 ab             	rep stos %rax,%es:(%rdi)
  4018ad:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  4018b4:	48 89 df             	mov    %rbx,%rdi
  4018b7:	f2 ae                	repnz scas %es:(%rdi),%al
  4018b9:	48 89 ca             	mov    %rcx,%rdx
  4018bc:	48 f7 d2             	not    %rdx
  4018bf:	48 89 d1             	mov    %rdx,%rcx
  4018c2:	48 83 e9 01          	sub    $0x1,%rcx
  4018c6:	85 c9                	test   %ecx,%ecx
  4018c8:	0f 84 26 06 00 00    	je     401ef4 <submitr+0x79b>
  4018ce:	8d 41 ff             	lea    -0x1(%rcx),%eax
  4018d1:	4c 8d 74 03 01       	lea    0x1(%rbx,%rax,1),%r14
  4018d6:	48 8d ac 24 50 40 00 	lea    0x4050(%rsp),%rbp
  4018dd:	00 
  4018de:	49 bd d9 ff 00 00 00 	movabs $0x2000000000ffd9,%r13
  4018e5:	00 20 00 
  4018e8:	e9 a6 01 00 00       	jmpq   401a93 <submitr+0x33a>
  4018ed:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  4018f4:	3a 20 43 
  4018f7:	48 ba 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rdx
  4018fe:	20 75 6e 
  401901:	49 89 07             	mov    %rax,(%r15)
  401904:	49 89 57 08          	mov    %rdx,0x8(%r15)
  401908:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  40190f:	74 6f 20 
  401912:	48 ba 63 72 65 61 74 	movabs $0x7320657461657263,%rdx
  401919:	65 20 73 
  40191c:	49 89 47 10          	mov    %rax,0x10(%r15)
  401920:	49 89 57 18          	mov    %rdx,0x18(%r15)
  401924:	41 c7 47 20 6f 63 6b 	movl   $0x656b636f,0x20(%r15)
  40192b:	65 
  40192c:	66 41 c7 47 24 74 00 	movw   $0x74,0x24(%r15)
  401933:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401938:	e9 8e 04 00 00       	jmpq   401dcb <submitr+0x672>
  40193d:	48 b8 45 72 72 6f 72 	movabs $0x44203a726f727245,%rax
  401944:	3a 20 44 
  401947:	48 ba 4e 53 20 69 73 	movabs $0x6e7520736920534e,%rdx
  40194e:	20 75 6e 
  401951:	49 89 07             	mov    %rax,(%r15)
  401954:	49 89 57 08          	mov    %rdx,0x8(%r15)
  401958:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  40195f:	74 6f 20 
  401962:	48 ba 72 65 73 6f 6c 	movabs $0x2065766c6f736572,%rdx
  401969:	76 65 20 
  40196c:	49 89 47 10          	mov    %rax,0x10(%r15)
  401970:	49 89 57 18          	mov    %rdx,0x18(%r15)
  401974:	48 b8 73 65 72 76 65 	movabs $0x6120726576726573,%rax
  40197b:	72 20 61 
  40197e:	49 89 47 20          	mov    %rax,0x20(%r15)
  401982:	41 c7 47 28 64 64 72 	movl   $0x65726464,0x28(%r15)
  401989:	65 
  40198a:	66 41 c7 47 2c 73 73 	movw   $0x7373,0x2c(%r15)
  401991:	41 c6 47 2e 00       	movb   $0x0,0x2e(%r15)
  401996:	44 89 e7             	mov    %r12d,%edi
  401999:	e8 82 f1 ff ff       	callq  400b20 <close@plt>
  40199e:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4019a3:	e9 23 04 00 00       	jmpq   401dcb <submitr+0x672>
  4019a8:	48 b8 45 72 72 6f 72 	movabs $0x55203a726f727245,%rax
  4019af:	3a 20 55 
  4019b2:	48 ba 6e 61 62 6c 65 	movabs $0x6f7420656c62616e,%rdx
  4019b9:	20 74 6f 
  4019bc:	49 89 07             	mov    %rax,(%r15)
  4019bf:	49 89 57 08          	mov    %rdx,0x8(%r15)
  4019c3:	48 b8 20 63 6f 6e 6e 	movabs $0x7463656e6e6f6320,%rax
  4019ca:	65 63 74 
  4019cd:	48 ba 20 74 6f 20 74 	movabs $0x20656874206f7420,%rdx
  4019d4:	68 65 20 
  4019d7:	49 89 47 10          	mov    %rax,0x10(%r15)
  4019db:	49 89 57 18          	mov    %rdx,0x18(%r15)
  4019df:	41 c7 47 20 73 65 72 	movl   $0x76726573,0x20(%r15)
  4019e6:	76 
  4019e7:	66 41 c7 47 24 65 72 	movw   $0x7265,0x24(%r15)
  4019ee:	41 c6 47 26 00       	movb   $0x0,0x26(%r15)
  4019f3:	44 89 e7             	mov    %r12d,%edi
  4019f6:	e8 25 f1 ff ff       	callq  400b20 <close@plt>
  4019fb:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401a00:	e9 c6 03 00 00       	jmpq   401dcb <submitr+0x672>
  401a05:	48 b8 45 72 72 6f 72 	movabs $0x52203a726f727245,%rax
  401a0c:	3a 20 52 
  401a0f:	48 ba 65 73 75 6c 74 	movabs $0x747320746c757365,%rdx
  401a16:	20 73 74 
  401a19:	49 89 07             	mov    %rax,(%r15)
  401a1c:	49 89 57 08          	mov    %rdx,0x8(%r15)
  401a20:	48 b8 72 69 6e 67 20 	movabs $0x6f6f7420676e6972,%rax
  401a27:	74 6f 6f 
  401a2a:	48 ba 20 6c 61 72 67 	movabs $0x202e656772616c20,%rdx
  401a31:	65 2e 20 
  401a34:	49 89 47 10          	mov    %rax,0x10(%r15)
  401a38:	49 89 57 18          	mov    %rdx,0x18(%r15)
  401a3c:	48 b8 49 6e 63 72 65 	movabs $0x6573616572636e49,%rax
  401a43:	61 73 65 
  401a46:	48 ba 20 53 55 42 4d 	movabs $0x5254494d42555320,%rdx
  401a4d:	49 54 52 
  401a50:	49 89 47 20          	mov    %rax,0x20(%r15)
  401a54:	49 89 57 28          	mov    %rdx,0x28(%r15)
  401a58:	48 b8 5f 4d 41 58 42 	movabs $0x46554258414d5f,%rax
  401a5f:	55 46 00 
  401a62:	49 89 47 30          	mov    %rax,0x30(%r15)
  401a66:	44 89 e7             	mov    %r12d,%edi
  401a69:	e8 b2 f0 ff ff       	callq  400b20 <close@plt>
  401a6e:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401a73:	e9 53 03 00 00       	jmpq   401dcb <submitr+0x672>
  401a78:	49 0f a3 c5          	bt     %rax,%r13
  401a7c:	73 21                	jae    401a9f <submitr+0x346>
  401a7e:	44 88 45 00          	mov    %r8b,0x0(%rbp)
  401a82:	48 8d 6d 01          	lea    0x1(%rbp),%rbp
  401a86:	48 83 c3 01          	add    $0x1,%rbx
  401a8a:	4c 39 f3             	cmp    %r14,%rbx
  401a8d:	0f 84 61 04 00 00    	je     401ef4 <submitr+0x79b>
  401a93:	44 0f b6 03          	movzbl (%rbx),%r8d
  401a97:	41 8d 40 d6          	lea    -0x2a(%r8),%eax
  401a9b:	3c 35                	cmp    $0x35,%al
  401a9d:	76 d9                	jbe    401a78 <submitr+0x31f>
  401a9f:	44 89 c0             	mov    %r8d,%eax
  401aa2:	83 e0 df             	and    $0xffffffdf,%eax
  401aa5:	83 e8 41             	sub    $0x41,%eax
  401aa8:	3c 19                	cmp    $0x19,%al
  401aaa:	76 d2                	jbe    401a7e <submitr+0x325>
  401aac:	41 80 f8 20          	cmp    $0x20,%r8b
  401ab0:	74 61                	je     401b13 <submitr+0x3ba>
  401ab2:	41 8d 40 e0          	lea    -0x20(%r8),%eax
  401ab6:	3c 5f                	cmp    $0x5f,%al
  401ab8:	76 0a                	jbe    401ac4 <submitr+0x36b>
  401aba:	41 80 f8 09          	cmp    $0x9,%r8b
  401abe:	0f 85 a3 03 00 00    	jne    401e67 <submitr+0x70e>
  401ac4:	45 0f b6 c0          	movzbl %r8b,%r8d
  401ac8:	b9 60 27 40 00       	mov    $0x402760,%ecx
  401acd:	ba 08 00 00 00       	mov    $0x8,%edx
  401ad2:	be 01 00 00 00       	mov    $0x1,%esi
  401ad7:	48 8d bc 24 50 80 00 	lea    0x8050(%rsp),%rdi
  401ade:	00 
  401adf:	b8 00 00 00 00       	mov    $0x0,%eax
  401ae4:	e8 37 f1 ff ff       	callq  400c20 <__sprintf_chk@plt>
  401ae9:	0f b6 84 24 50 80 00 	movzbl 0x8050(%rsp),%eax
  401af0:	00 
  401af1:	88 45 00             	mov    %al,0x0(%rbp)
  401af4:	0f b6 84 24 51 80 00 	movzbl 0x8051(%rsp),%eax
  401afb:	00 
  401afc:	88 45 01             	mov    %al,0x1(%rbp)
  401aff:	0f b6 84 24 52 80 00 	movzbl 0x8052(%rsp),%eax
  401b06:	00 
  401b07:	88 45 02             	mov    %al,0x2(%rbp)
  401b0a:	48 8d 6d 03          	lea    0x3(%rbp),%rbp
  401b0e:	e9 73 ff ff ff       	jmpq   401a86 <submitr+0x32d>
  401b13:	c6 45 00 2b          	movb   $0x2b,0x0(%rbp)
  401b17:	48 8d 6d 01          	lea    0x1(%rbp),%rbp
  401b1b:	e9 66 ff ff ff       	jmpq   401a86 <submitr+0x32d>
  401b20:	49 01 c5             	add    %rax,%r13
  401b23:	48 29 c5             	sub    %rax,%rbp
  401b26:	74 26                	je     401b4e <submitr+0x3f5>
  401b28:	48 89 ea             	mov    %rbp,%rdx
  401b2b:	4c 89 ee             	mov    %r13,%rsi
  401b2e:	44 89 e7             	mov    %r12d,%edi
  401b31:	e8 ba ef ff ff       	callq  400af0 <write@plt>
  401b36:	48 85 c0             	test   %rax,%rax
  401b39:	7f e5                	jg     401b20 <submitr+0x3c7>
  401b3b:	e8 80 ef ff ff       	callq  400ac0 <__errno_location@plt>
  401b40:	83 38 04             	cmpl   $0x4,(%rax)
  401b43:	0f 85 28 01 00 00    	jne    401c71 <submitr+0x518>
  401b49:	4c 89 f0             	mov    %r14,%rax
  401b4c:	eb d2                	jmp    401b20 <submitr+0x3c7>
  401b4e:	48 85 db             	test   %rbx,%rbx
  401b51:	0f 88 1a 01 00 00    	js     401c71 <submitr+0x518>
  401b57:	44 89 64 24 40       	mov    %r12d,0x40(%rsp)
  401b5c:	c7 44 24 44 00 00 00 	movl   $0x0,0x44(%rsp)
  401b63:	00 
  401b64:	48 8d 44 24 50       	lea    0x50(%rsp),%rax
  401b69:	48 89 44 24 48       	mov    %rax,0x48(%rsp)
  401b6e:	ba 00 20 00 00       	mov    $0x2000,%edx
  401b73:	48 8d b4 24 50 20 00 	lea    0x2050(%rsp),%rsi
  401b7a:	00 
  401b7b:	48 8d 7c 24 40       	lea    0x40(%rsp),%rdi
  401b80:	e8 18 fb ff ff       	callq  40169d <rio_readlineb>
  401b85:	48 85 c0             	test   %rax,%rax
  401b88:	0f 8e 42 01 00 00    	jle    401cd0 <submitr+0x577>
  401b8e:	4c 8d 84 24 50 80 00 	lea    0x8050(%rsp),%r8
  401b95:	00 
  401b96:	48 8d 4c 24 2c       	lea    0x2c(%rsp),%rcx
  401b9b:	48 8d 94 24 50 60 00 	lea    0x6050(%rsp),%rdx
  401ba2:	00 
  401ba3:	be 67 27 40 00       	mov    $0x402767,%esi
  401ba8:	48 8d bc 24 50 20 00 	lea    0x2050(%rsp),%rdi
  401baf:	00 
  401bb0:	b8 00 00 00 00       	mov    $0x0,%eax
  401bb5:	e8 e6 ef ff ff       	callq  400ba0 <__isoc99_sscanf@plt>
  401bba:	44 8b 44 24 2c       	mov    0x2c(%rsp),%r8d
  401bbf:	41 81 f8 c8 00 00 00 	cmp    $0xc8,%r8d
  401bc6:	0f 85 78 01 00 00    	jne    401d44 <submitr+0x5eb>
  401bcc:	48 8d 9c 24 50 20 00 	lea    0x2050(%rsp),%rbx
  401bd3:	00 
  401bd4:	bf 78 27 40 00       	mov    $0x402778,%edi
  401bd9:	b9 03 00 00 00       	mov    $0x3,%ecx
  401bde:	48 89 de             	mov    %rbx,%rsi
  401be1:	f3 a6                	repz cmpsb %es:(%rdi),%ds:(%rsi)
  401be3:	0f 97 c0             	seta   %al
  401be6:	1c 00                	sbb    $0x0,%al
  401be8:	84 c0                	test   %al,%al
  401bea:	0f 84 89 01 00 00    	je     401d79 <submitr+0x620>
  401bf0:	ba 00 20 00 00       	mov    $0x2000,%edx
  401bf5:	48 89 de             	mov    %rbx,%rsi
  401bf8:	48 8d 7c 24 40       	lea    0x40(%rsp),%rdi
  401bfd:	e8 9b fa ff ff       	callq  40169d <rio_readlineb>
  401c02:	48 85 c0             	test   %rax,%rax
  401c05:	7f cd                	jg     401bd4 <submitr+0x47b>
  401c07:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  401c0e:	3a 20 43 
  401c11:	48 ba 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rdx
  401c18:	20 75 6e 
  401c1b:	49 89 07             	mov    %rax,(%r15)
  401c1e:	49 89 57 08          	mov    %rdx,0x8(%r15)
  401c22:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  401c29:	74 6f 20 
  401c2c:	48 ba 72 65 61 64 20 	movabs $0x6165682064616572,%rdx
  401c33:	68 65 61 
  401c36:	49 89 47 10          	mov    %rax,0x10(%r15)
  401c3a:	49 89 57 18          	mov    %rdx,0x18(%r15)
  401c3e:	48 b8 64 65 72 73 20 	movabs $0x6f72662073726564,%rax
  401c45:	66 72 6f 
  401c48:	48 ba 6d 20 73 65 72 	movabs $0x726576726573206d,%rdx
  401c4f:	76 65 72 
  401c52:	49 89 47 20          	mov    %rax,0x20(%r15)
  401c56:	49 89 57 28          	mov    %rdx,0x28(%r15)
  401c5a:	41 c6 47 30 00       	movb   $0x0,0x30(%r15)
  401c5f:	44 89 e7             	mov    %r12d,%edi
  401c62:	e8 b9 ee ff ff       	callq  400b20 <close@plt>
  401c67:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401c6c:	e9 5a 01 00 00       	jmpq   401dcb <submitr+0x672>
  401c71:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  401c78:	3a 20 43 
  401c7b:	48 ba 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rdx
  401c82:	20 75 6e 
  401c85:	49 89 07             	mov    %rax,(%r15)
  401c88:	49 89 57 08          	mov    %rdx,0x8(%r15)
  401c8c:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  401c93:	74 6f 20 
  401c96:	48 ba 77 72 69 74 65 	movabs $0x6f74206574697277,%rdx
  401c9d:	20 74 6f 
  401ca0:	49 89 47 10          	mov    %rax,0x10(%r15)
  401ca4:	49 89 57 18          	mov    %rdx,0x18(%r15)
  401ca8:	48 b8 20 74 68 65 20 	movabs $0x7265732065687420,%rax
  401caf:	73 65 72 
  401cb2:	49 89 47 20          	mov    %rax,0x20(%r15)
  401cb6:	41 c7 47 28 76 65 72 	movl   $0x726576,0x28(%r15)
  401cbd:	00 
  401cbe:	44 89 e7             	mov    %r12d,%edi
  401cc1:	e8 5a ee ff ff       	callq  400b20 <close@plt>
  401cc6:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401ccb:	e9 fb 00 00 00       	jmpq   401dcb <submitr+0x672>
  401cd0:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  401cd7:	3a 20 43 
  401cda:	48 ba 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rdx
  401ce1:	20 75 6e 
  401ce4:	49 89 07             	mov    %rax,(%r15)
  401ce7:	49 89 57 08          	mov    %rdx,0x8(%r15)
  401ceb:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  401cf2:	74 6f 20 
  401cf5:	48 ba 72 65 61 64 20 	movabs $0x7269662064616572,%rdx
  401cfc:	66 69 72 
  401cff:	49 89 47 10          	mov    %rax,0x10(%r15)
  401d03:	49 89 57 18          	mov    %rdx,0x18(%r15)
  401d07:	48 b8 73 74 20 68 65 	movabs $0x6564616568207473,%rax
  401d0e:	61 64 65 
  401d11:	48 ba 72 20 66 72 6f 	movabs $0x73206d6f72662072,%rdx
  401d18:	6d 20 73 
  401d1b:	49 89 47 20          	mov    %rax,0x20(%r15)
  401d1f:	49 89 57 28          	mov    %rdx,0x28(%r15)
  401d23:	41 c7 47 30 65 72 76 	movl   $0x65767265,0x30(%r15)
  401d2a:	65 
  401d2b:	66 41 c7 47 34 72 00 	movw   $0x72,0x34(%r15)
  401d32:	44 89 e7             	mov    %r12d,%edi
  401d35:	e8 e6 ed ff ff       	callq  400b20 <close@plt>
  401d3a:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401d3f:	e9 87 00 00 00       	jmpq   401dcb <submitr+0x672>
  401d44:	4c 8d 8c 24 50 80 00 	lea    0x8050(%rsp),%r9
  401d4b:	00 
  401d4c:	b9 b8 26 40 00       	mov    $0x4026b8,%ecx
  401d51:	48 c7 c2 ff ff ff ff 	mov    $0xffffffffffffffff,%rdx
  401d58:	be 01 00 00 00       	mov    $0x1,%esi
  401d5d:	4c 89 ff             	mov    %r15,%rdi
  401d60:	b8 00 00 00 00       	mov    $0x0,%eax
  401d65:	e8 b6 ee ff ff       	callq  400c20 <__sprintf_chk@plt>
  401d6a:	44 89 e7             	mov    %r12d,%edi
  401d6d:	e8 ae ed ff ff       	callq  400b20 <close@plt>
  401d72:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401d77:	eb 52                	jmp    401dcb <submitr+0x672>
  401d79:	ba 00 20 00 00       	mov    $0x2000,%edx
  401d7e:	48 8d b4 24 50 20 00 	lea    0x2050(%rsp),%rsi
  401d85:	00 
  401d86:	48 8d 7c 24 40       	lea    0x40(%rsp),%rdi
  401d8b:	e8 0d f9 ff ff       	callq  40169d <rio_readlineb>
  401d90:	48 85 c0             	test   %rax,%rax
  401d93:	7e 5f                	jle    401df4 <submitr+0x69b>
  401d95:	48 8d b4 24 50 20 00 	lea    0x2050(%rsp),%rsi
  401d9c:	00 
  401d9d:	4c 89 ff             	mov    %r15,%rdi
  401da0:	e8 2b ed ff ff       	callq  400ad0 <strcpy@plt>
  401da5:	44 89 e7             	mov    %r12d,%edi
  401da8:	e8 73 ed ff ff       	callq  400b20 <close@plt>
  401dad:	bf 7b 27 40 00       	mov    $0x40277b,%edi
  401db2:	b9 03 00 00 00       	mov    $0x3,%ecx
  401db7:	4c 89 fe             	mov    %r15,%rsi
  401dba:	f3 a6                	repz cmpsb %es:(%rdi),%ds:(%rsi)
  401dbc:	0f 97 c0             	seta   %al
  401dbf:	1c 00                	sbb    $0x0,%al
  401dc1:	84 c0                	test   %al,%al
  401dc3:	0f 95 c0             	setne  %al
  401dc6:	0f b6 c0             	movzbl %al,%eax
  401dc9:	f7 d8                	neg    %eax
  401dcb:	48 8b 94 24 58 a0 00 	mov    0xa058(%rsp),%rdx
  401dd2:	00 
  401dd3:	64 48 33 14 25 28 00 	xor    %fs:0x28,%rdx
  401dda:	00 00 
  401ddc:	0f 85 93 01 00 00    	jne    401f75 <submitr+0x81c>
  401de2:	48 81 c4 68 a0 00 00 	add    $0xa068,%rsp
  401de9:	5b                   	pop    %rbx
  401dea:	5d                   	pop    %rbp
  401deb:	41 5c                	pop    %r12
  401ded:	41 5d                	pop    %r13
  401def:	41 5e                	pop    %r14
  401df1:	41 5f                	pop    %r15
  401df3:	c3                   	retq   
  401df4:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  401dfb:	3a 20 43 
  401dfe:	48 ba 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rdx
  401e05:	20 75 6e 
  401e08:	49 89 07             	mov    %rax,(%r15)
  401e0b:	49 89 57 08          	mov    %rdx,0x8(%r15)
  401e0f:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  401e16:	74 6f 20 
  401e19:	48 ba 72 65 61 64 20 	movabs $0x6174732064616572,%rdx
  401e20:	73 74 61 
  401e23:	49 89 47 10          	mov    %rax,0x10(%r15)
  401e27:	49 89 57 18          	mov    %rdx,0x18(%r15)
  401e2b:	48 b8 74 75 73 20 6d 	movabs $0x7373656d20737574,%rax
  401e32:	65 73 73 
  401e35:	48 ba 61 67 65 20 66 	movabs $0x6d6f726620656761,%rdx
  401e3c:	72 6f 6d 
  401e3f:	49 89 47 20          	mov    %rax,0x20(%r15)
  401e43:	49 89 57 28          	mov    %rdx,0x28(%r15)
  401e47:	48 b8 20 73 65 72 76 	movabs $0x72657672657320,%rax
  401e4e:	65 72 00 
  401e51:	49 89 47 30          	mov    %rax,0x30(%r15)
  401e55:	44 89 e7             	mov    %r12d,%edi
  401e58:	e8 c3 ec ff ff       	callq  400b20 <close@plt>
  401e5d:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401e62:	e9 64 ff ff ff       	jmpq   401dcb <submitr+0x672>
  401e67:	48 b8 45 72 72 6f 72 	movabs $0x52203a726f727245,%rax
  401e6e:	3a 20 52 
  401e71:	48 ba 65 73 75 6c 74 	movabs $0x747320746c757365,%rdx
  401e78:	20 73 74 
  401e7b:	49 89 07             	mov    %rax,(%r15)
  401e7e:	49 89 57 08          	mov    %rdx,0x8(%r15)
  401e82:	48 b8 72 69 6e 67 20 	movabs $0x6e6f6320676e6972,%rax
  401e89:	63 6f 6e 
  401e8c:	48 ba 74 61 69 6e 73 	movabs $0x6e6120736e696174,%rdx
  401e93:	20 61 6e 
  401e96:	49 89 47 10          	mov    %rax,0x10(%r15)
  401e9a:	49 89 57 18          	mov    %rdx,0x18(%r15)
  401e9e:	48 b8 20 69 6c 6c 65 	movabs $0x6c6167656c6c6920,%rax
  401ea5:	67 61 6c 
  401ea8:	48 ba 20 6f 72 20 75 	movabs $0x72706e7520726f20,%rdx
  401eaf:	6e 70 72 
  401eb2:	49 89 47 20          	mov    %rax,0x20(%r15)
  401eb6:	49 89 57 28          	mov    %rdx,0x28(%r15)
  401eba:	48 b8 69 6e 74 61 62 	movabs $0x20656c6261746e69,%rax
  401ec1:	6c 65 20 
  401ec4:	48 ba 63 68 61 72 61 	movabs $0x6574636172616863,%rdx
  401ecb:	63 74 65 
  401ece:	49 89 47 30          	mov    %rax,0x30(%r15)
  401ed2:	49 89 57 38          	mov    %rdx,0x38(%r15)
  401ed6:	66 41 c7 47 40 72 2e 	movw   $0x2e72,0x40(%r15)
  401edd:	41 c6 47 42 00       	movb   $0x0,0x42(%r15)
  401ee2:	44 89 e7             	mov    %r12d,%edi
  401ee5:	e8 36 ec ff ff       	callq  400b20 <close@plt>
  401eea:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401eef:	e9 d7 fe ff ff       	jmpq   401dcb <submitr+0x672>
  401ef4:	48 8d 9c 24 50 20 00 	lea    0x2050(%rsp),%rbx
  401efb:	00 
  401efc:	48 83 ec 08          	sub    $0x8,%rsp
  401f00:	48 8d 84 24 58 40 00 	lea    0x4058(%rsp),%rax
  401f07:	00 
  401f08:	50                   	push   %rax
  401f09:	ff 74 24 20          	pushq  0x20(%rsp)
  401f0d:	ff 74 24 30          	pushq  0x30(%rsp)
  401f11:	4c 8b 4c 24 28       	mov    0x28(%rsp),%r9
  401f16:	4c 8b 44 24 20       	mov    0x20(%rsp),%r8
  401f1b:	b9 e8 26 40 00       	mov    $0x4026e8,%ecx
  401f20:	ba 00 20 00 00       	mov    $0x2000,%edx
  401f25:	be 01 00 00 00       	mov    $0x1,%esi
  401f2a:	48 89 df             	mov    %rbx,%rdi
  401f2d:	b8 00 00 00 00       	mov    $0x0,%eax
  401f32:	e8 e9 ec ff ff       	callq  400c20 <__sprintf_chk@plt>
  401f37:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  401f3e:	b8 00 00 00 00       	mov    $0x0,%eax
  401f43:	48 89 df             	mov    %rbx,%rdi
  401f46:	f2 ae                	repnz scas %es:(%rdi),%al
  401f48:	48 f7 d1             	not    %rcx
  401f4b:	48 89 cb             	mov    %rcx,%rbx
  401f4e:	48 83 eb 01          	sub    $0x1,%rbx
  401f52:	48 83 c4 20          	add    $0x20,%rsp
  401f56:	48 89 dd             	mov    %rbx,%rbp
  401f59:	4c 8d ac 24 50 20 00 	lea    0x2050(%rsp),%r13
  401f60:	00 
  401f61:	41 be 00 00 00 00    	mov    $0x0,%r14d
  401f67:	48 85 db             	test   %rbx,%rbx
  401f6a:	0f 85 b8 fb ff ff    	jne    401b28 <submitr+0x3cf>
  401f70:	e9 e2 fb ff ff       	jmpq   401b57 <submitr+0x3fe>
  401f75:	e8 86 eb ff ff       	callq  400b00 <__stack_chk_fail@plt>

0000000000401f7a <init_timeout>:
  401f7a:	85 ff                	test   %edi,%edi
  401f7c:	74 23                	je     401fa1 <init_timeout+0x27>
  401f7e:	53                   	push   %rbx
  401f7f:	89 fb                	mov    %edi,%ebx
  401f81:	be 6f 16 40 00       	mov    $0x40166f,%esi
  401f86:	bf 0e 00 00 00       	mov    $0xe,%edi
  401f8b:	e8 c0 eb ff ff       	callq  400b50 <signal@plt>
  401f90:	85 db                	test   %ebx,%ebx
  401f92:	bf 00 00 00 00       	mov    $0x0,%edi
  401f97:	0f 49 fb             	cmovns %ebx,%edi
  401f9a:	e8 71 eb ff ff       	callq  400b10 <alarm@plt>
  401f9f:	5b                   	pop    %rbx
  401fa0:	c3                   	retq   
  401fa1:	f3 c3                	repz retq 

0000000000401fa3 <init_driver>:
  401fa3:	55                   	push   %rbp
  401fa4:	53                   	push   %rbx
  401fa5:	48 83 ec 28          	sub    $0x28,%rsp
  401fa9:	48 89 fd             	mov    %rdi,%rbp
  401fac:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401fb3:	00 00 
  401fb5:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
  401fba:	31 c0                	xor    %eax,%eax
  401fbc:	be 01 00 00 00       	mov    $0x1,%esi
  401fc1:	bf 0d 00 00 00       	mov    $0xd,%edi
  401fc6:	e8 85 eb ff ff       	callq  400b50 <signal@plt>
  401fcb:	be 01 00 00 00       	mov    $0x1,%esi
  401fd0:	bf 1d 00 00 00       	mov    $0x1d,%edi
  401fd5:	e8 76 eb ff ff       	callq  400b50 <signal@plt>
  401fda:	be 01 00 00 00       	mov    $0x1,%esi
  401fdf:	bf 1d 00 00 00       	mov    $0x1d,%edi
  401fe4:	e8 67 eb ff ff       	callq  400b50 <signal@plt>
  401fe9:	ba 00 00 00 00       	mov    $0x0,%edx
  401fee:	be 01 00 00 00       	mov    $0x1,%esi
  401ff3:	bf 02 00 00 00       	mov    $0x2,%edi
  401ff8:	e8 33 ec ff ff       	callq  400c30 <socket@plt>
  401ffd:	85 c0                	test   %eax,%eax
  401fff:	0f 88 9c 00 00 00    	js     4020a1 <init_driver+0xfe>
  402005:	89 c3                	mov    %eax,%ebx
  402007:	bf 7e 27 40 00       	mov    $0x40277e,%edi
  40200c:	e8 4f eb ff ff       	callq  400b60 <gethostbyname@plt>
  402011:	48 85 c0             	test   %rax,%rax
  402014:	0f 84 d3 00 00 00    	je     4020ed <init_driver+0x14a>
  40201a:	48 c7 44 24 02 00 00 	movq   $0x0,0x2(%rsp)
  402021:	00 00 
  402023:	c7 44 24 0a 00 00 00 	movl   $0x0,0xa(%rsp)
  40202a:	00 
  40202b:	66 c7 44 24 0e 00 00 	movw   $0x0,0xe(%rsp)
  402032:	66 c7 04 24 02 00    	movw   $0x2,(%rsp)
  402038:	48 63 50 14          	movslq 0x14(%rax),%rdx
  40203c:	48 8b 40 18          	mov    0x18(%rax),%rax
  402040:	48 8d 7c 24 04       	lea    0x4(%rsp),%rdi
  402045:	b9 0c 00 00 00       	mov    $0xc,%ecx
  40204a:	48 8b 30             	mov    (%rax),%rsi
  40204d:	e8 1e eb ff ff       	callq  400b70 <__memmove_chk@plt>
  402052:	66 c7 44 24 02 3b 6e 	movw   $0x6e3b,0x2(%rsp)
  402059:	ba 10 00 00 00       	mov    $0x10,%edx
  40205e:	48 89 e6             	mov    %rsp,%rsi
  402061:	89 df                	mov    %ebx,%edi
  402063:	e8 78 eb ff ff       	callq  400be0 <connect@plt>
  402068:	85 c0                	test   %eax,%eax
  40206a:	0f 88 e5 00 00 00    	js     402155 <init_driver+0x1b2>
  402070:	89 df                	mov    %ebx,%edi
  402072:	e8 a9 ea ff ff       	callq  400b20 <close@plt>
  402077:	66 c7 45 00 4f 4b    	movw   $0x4b4f,0x0(%rbp)
  40207d:	c6 45 02 00          	movb   $0x0,0x2(%rbp)
  402081:	b8 00 00 00 00       	mov    $0x0,%eax
  402086:	48 8b 4c 24 18       	mov    0x18(%rsp),%rcx
  40208b:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
  402092:	00 00 
  402094:	0f 85 f0 00 00 00    	jne    40218a <init_driver+0x1e7>
  40209a:	48 83 c4 28          	add    $0x28,%rsp
  40209e:	5b                   	pop    %rbx
  40209f:	5d                   	pop    %rbp
  4020a0:	c3                   	retq   
  4020a1:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  4020a8:	3a 20 43 
  4020ab:	48 ba 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rdx
  4020b2:	20 75 6e 
  4020b5:	48 89 45 00          	mov    %rax,0x0(%rbp)
  4020b9:	48 89 55 08          	mov    %rdx,0x8(%rbp)
  4020bd:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  4020c4:	74 6f 20 
  4020c7:	48 ba 63 72 65 61 74 	movabs $0x7320657461657263,%rdx
  4020ce:	65 20 73 
  4020d1:	48 89 45 10          	mov    %rax,0x10(%rbp)
  4020d5:	48 89 55 18          	mov    %rdx,0x18(%rbp)
  4020d9:	c7 45 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%rbp)
  4020e0:	66 c7 45 24 74 00    	movw   $0x74,0x24(%rbp)
  4020e6:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4020eb:	eb 99                	jmp    402086 <init_driver+0xe3>
  4020ed:	48 b8 45 72 72 6f 72 	movabs $0x44203a726f727245,%rax
  4020f4:	3a 20 44 
  4020f7:	48 ba 4e 53 20 69 73 	movabs $0x6e7520736920534e,%rdx
  4020fe:	20 75 6e 
  402101:	48 89 45 00          	mov    %rax,0x0(%rbp)
  402105:	48 89 55 08          	mov    %rdx,0x8(%rbp)
  402109:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402110:	74 6f 20 
  402113:	48 ba 72 65 73 6f 6c 	movabs $0x2065766c6f736572,%rdx
  40211a:	76 65 20 
  40211d:	48 89 45 10          	mov    %rax,0x10(%rbp)
  402121:	48 89 55 18          	mov    %rdx,0x18(%rbp)
  402125:	48 b8 73 65 72 76 65 	movabs $0x6120726576726573,%rax
  40212c:	72 20 61 
  40212f:	48 89 45 20          	mov    %rax,0x20(%rbp)
  402133:	c7 45 28 64 64 72 65 	movl   $0x65726464,0x28(%rbp)
  40213a:	66 c7 45 2c 73 73    	movw   $0x7373,0x2c(%rbp)
  402140:	c6 45 2e 00          	movb   $0x0,0x2e(%rbp)
  402144:	89 df                	mov    %ebx,%edi
  402146:	e8 d5 e9 ff ff       	callq  400b20 <close@plt>
  40214b:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402150:	e9 31 ff ff ff       	jmpq   402086 <init_driver+0xe3>
  402155:	41 b8 7e 27 40 00    	mov    $0x40277e,%r8d
  40215b:	b9 38 27 40 00       	mov    $0x402738,%ecx
  402160:	48 c7 c2 ff ff ff ff 	mov    $0xffffffffffffffff,%rdx
  402167:	be 01 00 00 00       	mov    $0x1,%esi
  40216c:	48 89 ef             	mov    %rbp,%rdi
  40216f:	b8 00 00 00 00       	mov    $0x0,%eax
  402174:	e8 a7 ea ff ff       	callq  400c20 <__sprintf_chk@plt>
  402179:	89 df                	mov    %ebx,%edi
  40217b:	e8 a0 e9 ff ff       	callq  400b20 <close@plt>
  402180:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402185:	e9 fc fe ff ff       	jmpq   402086 <init_driver+0xe3>
  40218a:	e8 71 e9 ff ff       	callq  400b00 <__stack_chk_fail@plt>

000000000040218f <driver_post>:
  40218f:	53                   	push   %rbx
  402190:	4c 89 c3             	mov    %r8,%rbx
  402193:	85 c9                	test   %ecx,%ecx
  402195:	75 17                	jne    4021ae <driver_post+0x1f>
  402197:	48 85 ff             	test   %rdi,%rdi
  40219a:	74 05                	je     4021a1 <driver_post+0x12>
  40219c:	80 3f 00             	cmpb   $0x0,(%rdi)
  40219f:	75 31                	jne    4021d2 <driver_post+0x43>
  4021a1:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
  4021a6:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
  4021aa:	89 c8                	mov    %ecx,%eax
  4021ac:	5b                   	pop    %rbx
  4021ad:	c3                   	retq   
  4021ae:	be 88 27 40 00       	mov    $0x402788,%esi
  4021b3:	bf 01 00 00 00       	mov    $0x1,%edi
  4021b8:	b8 00 00 00 00       	mov    $0x0,%eax
  4021bd:	e8 ee e9 ff ff       	callq  400bb0 <__printf_chk@plt>
  4021c2:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
  4021c7:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
  4021cb:	b8 00 00 00 00       	mov    $0x0,%eax
  4021d0:	eb da                	jmp    4021ac <driver_post+0x1d>
  4021d2:	41 50                	push   %r8
  4021d4:	52                   	push   %rdx
  4021d5:	41 b9 9f 27 40 00    	mov    $0x40279f,%r9d
  4021db:	49 89 f0             	mov    %rsi,%r8
  4021de:	48 89 f9             	mov    %rdi,%rcx
  4021e1:	4c 89 ca             	mov    %r9,%rdx
  4021e4:	be 6e 3b 00 00       	mov    $0x3b6e,%esi
  4021e9:	bf 7e 27 40 00       	mov    $0x40277e,%edi
  4021ee:	e8 66 f5 ff ff       	callq  401759 <submitr>
  4021f3:	48 83 c4 10          	add    $0x10,%rsp
  4021f7:	eb b3                	jmp    4021ac <driver_post+0x1d>
  4021f9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000402200 <__libc_csu_init>:
  402200:	41 57                	push   %r15
  402202:	41 56                	push   %r14
  402204:	49 89 d7             	mov    %rdx,%r15
  402207:	41 55                	push   %r13
  402209:	41 54                	push   %r12
  40220b:	4c 8d 25 fe 0b 20 00 	lea    0x200bfe(%rip),%r12        # 602e10 <__frame_dummy_init_array_entry>
  402212:	55                   	push   %rbp
  402213:	48 8d 2d fe 0b 20 00 	lea    0x200bfe(%rip),%rbp        # 602e18 <__init_array_end>
  40221a:	53                   	push   %rbx
  40221b:	41 89 fd             	mov    %edi,%r13d
  40221e:	49 89 f6             	mov    %rsi,%r14
  402221:	4c 29 e5             	sub    %r12,%rbp
  402224:	48 83 ec 08          	sub    $0x8,%rsp
  402228:	48 c1 fd 03          	sar    $0x3,%rbp
  40222c:	e8 4f e8 ff ff       	callq  400a80 <_init>
  402231:	48 85 ed             	test   %rbp,%rbp
  402234:	74 20                	je     402256 <__libc_csu_init+0x56>
  402236:	31 db                	xor    %ebx,%ebx
  402238:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  40223f:	00 
  402240:	4c 89 fa             	mov    %r15,%rdx
  402243:	4c 89 f6             	mov    %r14,%rsi
  402246:	44 89 ef             	mov    %r13d,%edi
  402249:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40224d:	48 83 c3 01          	add    $0x1,%rbx
  402251:	48 39 dd             	cmp    %rbx,%rbp
  402254:	75 ea                	jne    402240 <__libc_csu_init+0x40>
  402256:	48 83 c4 08          	add    $0x8,%rsp
  40225a:	5b                   	pop    %rbx
  40225b:	5d                   	pop    %rbp
  40225c:	41 5c                	pop    %r12
  40225e:	41 5d                	pop    %r13
  402260:	41 5e                	pop    %r14
  402262:	41 5f                	pop    %r15
  402264:	c3                   	retq   
  402265:	90                   	nop
  402266:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40226d:	00 00 00 

0000000000402270 <__libc_csu_fini>:
  402270:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000402274 <_fini>:
  402274:	48 83 ec 08          	sub    $0x8,%rsp
  402278:	48 83 c4 08          	add    $0x8,%rsp
  40227c:	c3                   	retq   
