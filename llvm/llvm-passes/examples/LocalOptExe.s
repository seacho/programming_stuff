	.build_version macos, 14, 0	sdk_version 14, 2
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main                           ## -- Begin function main
	.p2align	4
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$5193808, %edi                  ## imm = 0x4F4050
	callq	_log_block_entry
	movl	$12, -16(%rbp)
	movl	$13, -12(%rbp)
	movl	$25, -8(%rbp)
	movl	$34, -4(%rbp)
	leaq	L_.str(%rip), %rdi
	movl	$34, %esi
	xorl	%eax, %eax
	callq	_printf
	xorl	%eax, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%d"

.subsections_via_symbols
