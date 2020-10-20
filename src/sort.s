	.file	"sort.c"
	.text
	.p2align 4
	.globl	sort
	.type	sort, @function
sort:
.LFB16:
	.cfi_startproc
	endbr64
	testq	%rsi, %rsi
	je	.L1
	xorl	%r8d, %r8d
	leaq	1(%r8), %rcx
	cmpq	%rcx, %rsi
	jbe	.L1
	.p2align 4,,10
	.p2align 3
.L15:
	movq	%rcx, %rax
	movq	%r8, %rdx
	.p2align 4,,10
	.p2align 3
.L4:
	movq	(%rdi,%rdx,8), %r9
	cmpq	%r9, (%rdi,%rax,8)
	cmovl	%rax, %rdx
	addq	$1, %rax
	cmpq	%rax, %rsi
	jne	.L4
	cmpq	%r8, %rdx
	je	.L8
	leaq	(%rdi,%rdx,8), %rax
	movq	-8(%rdi,%rcx,8), %r8
	movq	(%rax), %rdx
	movq	%rdx, -8(%rdi,%rcx,8)
	movq	%r8, (%rax)
	cmpq	%rcx, %rsi
	jbe	.L1
.L8:
	movq	%rcx, %r8
	leaq	1(%r8), %rcx
	cmpq	%rcx, %rsi
	ja	.L15
.L1:
	ret
	.cfi_endproc
.LFE16:
	.size	sort, .-sort
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
