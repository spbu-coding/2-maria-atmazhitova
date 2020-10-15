	.file	"sort.c"
	.text
	.globl	sort
	.def	sort;	.scl	2;	.type	32;	.endef
	.seh_proc	sort
sort:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	%r8, 32(%rbp)
	movq	$0, -8(%rbp)
	jmp	.L2
.L3:
	movq	-8(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movq	-8(%rbp), %rdx
	leaq	0(,%rdx,8), %rcx
	movq	24(%rbp), %rdx
	addq	%rcx, %rdx
	movq	(%rax), %rax
	movq	%rax, (%rdx)
	addq	$1, -8(%rbp)
.L2:
	movq	-8(%rbp), %rax
	cmpq	32(%rbp), %rax
	jb	.L3
	movq	$0, -16(%rbp)
	jmp	.L4
.L9:
	movq	-16(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-16(%rbp), %rax
	addl	$1, %eax
	movl	%eax, -28(%rbp)
	jmp	.L5
.L7:
	movl	-28(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	leaq	0(,%rax,8), %rcx
	movq	24(%rbp), %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	cmpq	%rax, %rdx
	jge	.L6
	movl	-28(%rbp), %eax
	cltq
	movq	%rax, -24(%rbp)
.L6:
	addl	$1, -28(%rbp)
.L5:
	movl	-28(%rbp), %eax
	cltq
	cmpq	%rax, 32(%rbp)
	ja	.L7
	movq	-24(%rbp), %rax
	cmpq	-16(%rbp), %rax
	je	.L8
	movq	-16(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -40(%rbp)
	movq	-24(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rdx, %rax
	movq	-16(%rbp), %rdx
	leaq	0(,%rdx,8), %rcx
	movq	24(%rbp), %rdx
	addq	%rcx, %rdx
	movq	(%rax), %rax
	movq	%rax, (%rdx)
	movq	-24(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	movq	24(%rbp), %rax
	addq	%rax, %rdx
	movq	-40(%rbp), %rax
	movq	%rax, (%rdx)
.L8:
	addq	$1, -16(%rbp)
.L4:
	movq	32(%rbp), %rax
	subq	$1, %rax
	cmpq	%rax, -16(%rbp)
	jb	.L9
	nop
	nop
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (Rev3, Built by MSYS2 project) 10.2.0"
