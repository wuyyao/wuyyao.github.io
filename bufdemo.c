/* Demonstration of buffer overflow */
#include <stdio.h>
#include <stdlib.h>

/* Implementation of library function gets() */
char *gets(char *dest)
{
  int c = getchar();
  char *p = dest;
  while (c != EOF && c != '\n') {
    *p++ = c;
    c = getchar();
  }
  *p = '\0';
  return dest;
}

/* Read input line and write it back */
void echo()
{
    char buf[4];  /* Way too small! */
    gets(buf);
    puts(buf);
}

void call_echo() 
{
    echo();
}

/*void smash() 
{
    printf("I've been smashed!\n");
    exit(0);
}
*/

int main()
{
    printf("Type a string:");
    call_echo();
    return 0;
}

/*gcc -S bufdemo.c的时候会有警告
bufdemo.c: In function ‘echo’:
bufdemo.c:22:5: warning: ‘gets’ is deprecated (declared at /usr/include/stdio.h:638) [-Wdeprecated-declarations]
     gets(buf);
     ^
	 
运行结果：
 ***@ubuntu:/mnt/hgfs/share/csapp_code$ ./a.out
Type a string:0123
0123
***@ubuntu:/mnt/hgfs/share/csapp_code$ ./a.out
Type a string:012345
012345
*** stack smashing detected ***: ./a.out terminated
已放弃 (核心已转储)

objdump -S a.out

a.out：     文件格式 elf32-i386


Disassembly of section .init:

08048354 <_init>:
 8048354:	53                   	push   %ebx
 8048355:	83 ec 08             	sub    $0x8,%esp
 8048358:	e8 c3 00 00 00       	call   8048420 <__x86.get_pc_thunk.bx>
 804835d:	81 c3 a3 1c 00 00    	add    $0x1ca3,%ebx
 8048363:	8b 83 fc ff ff ff    	mov    -0x4(%ebx),%eax
 8048369:	85 c0                	test   %eax,%eax
 804836b:	74 05                	je     8048372 <_init+0x1e>
 804836d:	e8 5e 00 00 00       	call   80483d0 <__gmon_start__@plt>
 8048372:	83 c4 08             	add    $0x8,%esp
 8048375:	5b                   	pop    %ebx
 8048376:	c3                   	ret    

Disassembly of section .plt:

08048380 <printf@plt-0x10>:
 8048380:	ff 35 04 a0 04 08    	pushl  0x804a004
 8048386:	ff 25 08 a0 04 08    	jmp    *0x804a008
 804838c:	00 00                	add    %al,(%eax)
	...

08048390 <printf@plt>:
 8048390:	ff 25 0c a0 04 08    	jmp    *0x804a00c
 8048396:	68 00 00 00 00       	push   $0x0
 804839b:	e9 e0 ff ff ff       	jmp    8048380 <_init+0x2c>

080483a0 <getchar@plt>:
 80483a0:	ff 25 10 a0 04 08    	jmp    *0x804a010
 80483a6:	68 08 00 00 00       	push   $0x8
 80483ab:	e9 d0 ff ff ff       	jmp    8048380 <_init+0x2c>

080483b0 <__stack_chk_fail@plt>:
 80483b0:	ff 25 14 a0 04 08    	jmp    *0x804a014
 80483b6:	68 10 00 00 00       	push   $0x10
 80483bb:	e9 c0 ff ff ff       	jmp    8048380 <_init+0x2c>

080483c0 <puts@plt>:
 80483c0:	ff 25 18 a0 04 08    	jmp    *0x804a018
 80483c6:	68 18 00 00 00       	push   $0x18
 80483cb:	e9 b0 ff ff ff       	jmp    8048380 <_init+0x2c>

080483d0 <__gmon_start__@plt>:
 80483d0:	ff 25 1c a0 04 08    	jmp    *0x804a01c
 80483d6:	68 20 00 00 00       	push   $0x20
 80483db:	e9 a0 ff ff ff       	jmp    8048380 <_init+0x2c>

080483e0 <__libc_start_main@plt>:
 80483e0:	ff 25 20 a0 04 08    	jmp    *0x804a020
 80483e6:	68 28 00 00 00       	push   $0x28
 80483eb:	e9 90 ff ff ff       	jmp    8048380 <_init+0x2c>

Disassembly of section .text:

080483f0 <_start>:
 80483f0:	31 ed                	xor    %ebp,%ebp
 80483f2:	5e                   	pop    %esi
 80483f3:	89 e1                	mov    %esp,%ecx
 80483f5:	83 e4 f0             	and    $0xfffffff0,%esp
 80483f8:	50                   	push   %eax
 80483f9:	54                   	push   %esp
 80483fa:	52                   	push   %edx
 80483fb:	68 10 86 04 08       	push   $0x8048610
 8048400:	68 a0 85 04 08       	push   $0x80485a0
 8048405:	51                   	push   %ecx
 8048406:	56                   	push   %esi
 8048407:	68 77 85 04 08       	push   $0x8048577
 804840c:	e8 cf ff ff ff       	call   80483e0 <__libc_start_main@plt>
 8048411:	f4                   	hlt    
 8048412:	66 90                	xchg   %ax,%ax
 8048414:	66 90                	xchg   %ax,%ax
 8048416:	66 90                	xchg   %ax,%ax
 8048418:	66 90                	xchg   %ax,%ax
 804841a:	66 90                	xchg   %ax,%ax
 804841c:	66 90                	xchg   %ax,%ax
 804841e:	66 90                	xchg   %ax,%ax

08048420 <__x86.get_pc_thunk.bx>:
 8048420:	8b 1c 24             	mov    (%esp),%ebx
 8048423:	c3                   	ret    
 8048424:	66 90                	xchg   %ax,%ax
 8048426:	66 90                	xchg   %ax,%ax
 8048428:	66 90                	xchg   %ax,%ax
 804842a:	66 90                	xchg   %ax,%ax
 804842c:	66 90                	xchg   %ax,%ax
 804842e:	66 90                	xchg   %ax,%ax

08048430 <deregister_tm_clones>:
 8048430:	b8 2f a0 04 08       	mov    $0x804a02f,%eax
 8048435:	2d 2c a0 04 08       	sub    $0x804a02c,%eax
 804843a:	83 f8 06             	cmp    $0x6,%eax
 804843d:	77 01                	ja     8048440 <deregister_tm_clones+0x10>
 804843f:	c3                   	ret    
 8048440:	b8 00 00 00 00       	mov    $0x0,%eax
 8048445:	85 c0                	test   %eax,%eax
 8048447:	74 f6                	je     804843f <deregister_tm_clones+0xf>
 8048449:	55                   	push   %ebp
 804844a:	89 e5                	mov    %esp,%ebp
 804844c:	83 ec 18             	sub    $0x18,%esp
 804844f:	c7 04 24 2c a0 04 08 	movl   $0x804a02c,(%esp)
 8048456:	ff d0                	call   *%eax
 8048458:	c9                   	leave  
 8048459:	c3                   	ret    
 804845a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

08048460 <register_tm_clones>:
 8048460:	b8 2c a0 04 08       	mov    $0x804a02c,%eax
 8048465:	2d 2c a0 04 08       	sub    $0x804a02c,%eax
 804846a:	c1 f8 02             	sar    $0x2,%eax
 804846d:	89 c2                	mov    %eax,%edx
 804846f:	c1 ea 1f             	shr    $0x1f,%edx
 8048472:	01 d0                	add    %edx,%eax
 8048474:	d1 f8                	sar    %eax
 8048476:	75 01                	jne    8048479 <register_tm_clones+0x19>
 8048478:	c3                   	ret    
 8048479:	ba 00 00 00 00       	mov    $0x0,%edx
 804847e:	85 d2                	test   %edx,%edx
 8048480:	74 f6                	je     8048478 <register_tm_clones+0x18>
 8048482:	55                   	push   %ebp
 8048483:	89 e5                	mov    %esp,%ebp
 8048485:	83 ec 18             	sub    $0x18,%esp
 8048488:	89 44 24 04          	mov    %eax,0x4(%esp)
 804848c:	c7 04 24 2c a0 04 08 	movl   $0x804a02c,(%esp)
 8048493:	ff d2                	call   *%edx
 8048495:	c9                   	leave  
 8048496:	c3                   	ret    
 8048497:	89 f6                	mov    %esi,%esi
 8048499:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

080484a0 <__do_global_dtors_aux>:
 80484a0:	80 3d 2c a0 04 08 00 	cmpb   $0x0,0x804a02c
 80484a7:	75 13                	jne    80484bc <__do_global_dtors_aux+0x1c>
 80484a9:	55                   	push   %ebp
 80484aa:	89 e5                	mov    %esp,%ebp
 80484ac:	83 ec 08             	sub    $0x8,%esp
 80484af:	e8 7c ff ff ff       	call   8048430 <deregister_tm_clones>
 80484b4:	c6 05 2c a0 04 08 01 	movb   $0x1,0x804a02c
 80484bb:	c9                   	leave  
 80484bc:	f3 c3                	repz ret 
 80484be:	66 90                	xchg   %ax,%ax

080484c0 <frame_dummy>:
 80484c0:	a1 10 9f 04 08       	mov    0x8049f10,%eax
 80484c5:	85 c0                	test   %eax,%eax
 80484c7:	74 1f                	je     80484e8 <frame_dummy+0x28>
 80484c9:	b8 00 00 00 00       	mov    $0x0,%eax
 80484ce:	85 c0                	test   %eax,%eax
 80484d0:	74 16                	je     80484e8 <frame_dummy+0x28>
 80484d2:	55                   	push   %ebp
 80484d3:	89 e5                	mov    %esp,%ebp
 80484d5:	83 ec 18             	sub    $0x18,%esp
 80484d8:	c7 04 24 10 9f 04 08 	movl   $0x8049f10,(%esp)
 80484df:	ff d0                	call   *%eax
 80484e1:	c9                   	leave  
 80484e2:	e9 79 ff ff ff       	jmp    8048460 <register_tm_clones>
 80484e7:	90                   	nop
 80484e8:	e9 73 ff ff ff       	jmp    8048460 <register_tm_clones>

080484ed <gets>:
 80484ed:	55                   	push   %ebp
 80484ee:	89 e5                	mov    %esp,%ebp
 80484f0:	83 ec 18             	sub    $0x18,%esp
 80484f3:	e8 a8 fe ff ff       	call   80483a0 <getchar@plt>
 80484f8:	89 45 f0             	mov    %eax,-0x10(%ebp)
 80484fb:	8b 45 08             	mov    0x8(%ebp),%eax
 80484fe:	89 45 f4             	mov    %eax,-0xc(%ebp)
 8048501:	eb 16                	jmp    8048519 <gets+0x2c>
 8048503:	8b 45 f4             	mov    -0xc(%ebp),%eax
 8048506:	8d 50 01             	lea    0x1(%eax),%edx
 8048509:	89 55 f4             	mov    %edx,-0xc(%ebp)
 804850c:	8b 55 f0             	mov    -0x10(%ebp),%edx
 804850f:	88 10                	mov    %dl,(%eax)
 8048511:	e8 8a fe ff ff       	call   80483a0 <getchar@plt>
 8048516:	89 45 f0             	mov    %eax,-0x10(%ebp)
 8048519:	83 7d f0 ff          	cmpl   $0xffffffff,-0x10(%ebp)
 804851d:	74 06                	je     8048525 <gets+0x38>
 804851f:	83 7d f0 0a          	cmpl   $0xa,-0x10(%ebp)
 8048523:	75 de                	jne    8048503 <gets+0x16>
 8048525:	8b 45 f4             	mov    -0xc(%ebp),%eax
 8048528:	c6 00 00             	movb   $0x0,(%eax)
 804852b:	8b 45 08             	mov    0x8(%ebp),%eax
 804852e:	c9                   	leave  
 804852f:	c3                   	ret    

08048530 <echo>:
 8048530:	55                   	push   %ebp
 8048531:	89 e5                	mov    %esp,%ebp
 8048533:	83 ec 28             	sub    $0x28,%esp
 8048536:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 804853c:	89 45 f4             	mov    %eax,-0xc(%ebp)
 804853f:	31 c0                	xor    %eax,%eax
 8048541:	8d 45 f0             	lea    -0x10(%ebp),%eax
 8048544:	89 04 24             	mov    %eax,(%esp)
 8048547:	e8 a1 ff ff ff       	call   80484ed <gets>
 804854c:	8d 45 f0             	lea    -0x10(%ebp),%eax
 804854f:	89 04 24             	mov    %eax,(%esp)
 8048552:	e8 69 fe ff ff       	call   80483c0 <puts@plt>
 8048557:	8b 45 f4             	mov    -0xc(%ebp),%eax
 804855a:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8048561:	74 05                	je     8048568 <echo+0x38>
 8048563:	e8 48 fe ff ff       	call   80483b0 <__stack_chk_fail@plt>
 8048568:	c9                   	leave  
 8048569:	c3                   	ret    

0804856a <call_echo>:
 804856a:	55                   	push   %ebp
 804856b:	89 e5                	mov    %esp,%ebp
 804856d:	83 ec 08             	sub    $0x8,%esp
 8048570:	e8 bb ff ff ff       	call   8048530 <echo>
 8048575:	c9                   	leave  
 8048576:	c3                   	ret    

08048577 <main>:
 8048577:	55                   	push   %ebp
 8048578:	89 e5                	mov    %esp,%ebp
 804857a:	83 e4 f0             	and    $0xfffffff0,%esp
 804857d:	83 ec 10             	sub    $0x10,%esp
 8048580:	c7 04 24 30 86 04 08 	movl   $0x8048630,(%esp)
 8048587:	e8 04 fe ff ff       	call   8048390 <printf@plt>
 804858c:	e8 d9 ff ff ff       	call   804856a <call_echo>
 8048591:	b8 00 00 00 00       	mov    $0x0,%eax
 8048596:	c9                   	leave  
 8048597:	c3                   	ret    
 8048598:	66 90                	xchg   %ax,%ax
 804859a:	66 90                	xchg   %ax,%ax
 804859c:	66 90                	xchg   %ax,%ax
 804859e:	66 90                	xchg   %ax,%ax

080485a0 <__libc_csu_init>:
 80485a0:	55                   	push   %ebp
 80485a1:	57                   	push   %edi
 80485a2:	31 ff                	xor    %edi,%edi
 80485a4:	56                   	push   %esi
 80485a5:	53                   	push   %ebx
 80485a6:	e8 75 fe ff ff       	call   8048420 <__x86.get_pc_thunk.bx>
 80485ab:	81 c3 55 1a 00 00    	add    $0x1a55,%ebx
 80485b1:	83 ec 1c             	sub    $0x1c,%esp
 80485b4:	8b 6c 24 30          	mov    0x30(%esp),%ebp
 80485b8:	8d b3 0c ff ff ff    	lea    -0xf4(%ebx),%esi
 80485be:	e8 91 fd ff ff       	call   8048354 <_init>
 80485c3:	8d 83 08 ff ff ff    	lea    -0xf8(%ebx),%eax
 80485c9:	29 c6                	sub    %eax,%esi
 80485cb:	c1 fe 02             	sar    $0x2,%esi
 80485ce:	85 f6                	test   %esi,%esi
 80485d0:	74 27                	je     80485f9 <__libc_csu_init+0x59>
 80485d2:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 80485d8:	8b 44 24 38          	mov    0x38(%esp),%eax
 80485dc:	89 2c 24             	mov    %ebp,(%esp)
 80485df:	89 44 24 08          	mov    %eax,0x8(%esp)
 80485e3:	8b 44 24 34          	mov    0x34(%esp),%eax
 80485e7:	89 44 24 04          	mov    %eax,0x4(%esp)
 80485eb:	ff 94 bb 08 ff ff ff 	call   *-0xf8(%ebx,%edi,4)
 80485f2:	83 c7 01             	add    $0x1,%edi
 80485f5:	39 f7                	cmp    %esi,%edi
 80485f7:	75 df                	jne    80485d8 <__libc_csu_init+0x38>
 80485f9:	83 c4 1c             	add    $0x1c,%esp
 80485fc:	5b                   	pop    %ebx
 80485fd:	5e                   	pop    %esi
 80485fe:	5f                   	pop    %edi
 80485ff:	5d                   	pop    %ebp
 8048600:	c3                   	ret    
 8048601:	eb 0d                	jmp    8048610 <__libc_csu_fini>
 8048603:	90                   	nop
 8048604:	90                   	nop
 8048605:	90                   	nop
 8048606:	90                   	nop
 8048607:	90                   	nop
 8048608:	90                   	nop
 8048609:	90                   	nop
 804860a:	90                   	nop
 804860b:	90                   	nop
 804860c:	90                   	nop
 804860d:	90                   	nop
 804860e:	90                   	nop
 804860f:	90                   	nop

08048610 <__libc_csu_fini>:
 8048610:	f3 c3                	repz ret 

Disassembly of section .fini:
*/
