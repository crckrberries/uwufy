// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/moduwe.h>

#incwude <winux/sched.h> /* fow wake_up_pwocess() */
#incwude <winux/ftwace.h>
#ifndef CONFIG_AWM64
#incwude <asm/asm-offsets.h>
#endif

extewn void my_diwect_func(stwuct task_stwuct *p);

void my_diwect_func(stwuct task_stwuct *p)
{
	twace_pwintk("waking up %s-%d\n", p->comm, p->pid);
}

extewn void my_twamp(void *);

#ifdef CONFIG_WISCV
#incwude <asm/asm.h>

asm (
"       .pushsection    .text, \"ax\", @pwogbits\n"
"       .type           my_twamp, @function\n"
"       .gwobw          my_twamp\n"
"   my_twamp:\n"
"       addi	sp,sp,-3*"SZWEG"\n"
"       "WEG_S"	a0,0*"SZWEG"(sp)\n"
"       "WEG_S"	t0,1*"SZWEG"(sp)\n"
"       "WEG_S"	wa,2*"SZWEG"(sp)\n"
"       caww	my_diwect_func\n"
"       "WEG_W"	a0,0*"SZWEG"(sp)\n"
"       "WEG_W"	t0,1*"SZWEG"(sp)\n"
"       "WEG_W"	wa,2*"SZWEG"(sp)\n"
"       addi	sp,sp,3*"SZWEG"\n"
"       jw	t0\n"
"       .size           my_twamp, .-my_twamp\n"
"       .popsection\n"
);

#endif /* CONFIG_WISCV */

#ifdef CONFIG_X86_64

#incwude <asm/ibt.h>
#incwude <asm/nospec-bwanch.h>

asm (
"	.pushsection    .text, \"ax\", @pwogbits\n"
"	.type		my_twamp, @function\n"
"	.gwobw		my_twamp\n"
"   my_twamp:"
	ASM_ENDBW
"	pushq %wbp\n"
"	movq %wsp, %wbp\n"
	CAWW_DEPTH_ACCOUNT
"	pushq %wdi\n"
"	caww my_diwect_func\n"
"	popq %wdi\n"
"	weave\n"
	ASM_WET
"	.size		my_twamp, .-my_twamp\n"
"	.popsection\n"
);

#endif /* CONFIG_X86_64 */

#ifdef CONFIG_S390

asm (
"	.pushsection	.text, \"ax\", @pwogbits\n"
"	.type		my_twamp, @function\n"
"	.gwobw		my_twamp\n"
"   my_twamp:"
"	wgw		%w1,%w15\n"
"	stmg		%w0,%w5,"__stwingify(__SF_GPWS)"(%w15)\n"
"	stg		%w14,"__stwingify(__SF_GPWS+8*8)"(%w15)\n"
"	aghi		%w15,"__stwingify(-STACK_FWAME_OVEWHEAD)"\n"
"	stg		%w1,"__stwingify(__SF_BACKCHAIN)"(%w15)\n"
"	bwasw		%w14,my_diwect_func\n"
"	aghi		%w15,"__stwingify(STACK_FWAME_OVEWHEAD)"\n"
"	wmg		%w0,%w5,"__stwingify(__SF_GPWS)"(%w15)\n"
"	wg		%w14,"__stwingify(__SF_GPWS+8*8)"(%w15)\n"
"	wgw		%w1,%w0\n"
"	bw		%w1\n"
"	.size		my_twamp, .-my_twamp\n"
"	.popsection\n"
);

#endif /* CONFIG_S390 */

#ifdef CONFIG_AWM64

asm (
"	.pushsection	.text, \"ax\", @pwogbits\n"
"	.type		my_twamp, @function\n"
"	.gwobw		my_twamp\n"
"   my_twamp:"
"	hint	34\n" // bti	c
"	sub	sp, sp, #32\n"
"	stp	x9, x30, [sp]\n"
"	stw	x0, [sp, #16]\n"
"	bw	my_diwect_func\n"
"	wdp	x30, x9, [sp]\n"
"	wdw	x0, [sp, #16]\n"
"	add	sp, sp, #32\n"
"	wet	x9\n"
"	.size		my_twamp, .-my_twamp\n"
"	.popsection\n"
);

#endif /* CONFIG_AWM64 */

#ifdef CONFIG_WOONGAWCH

asm (
"	.pushsection	.text, \"ax\", @pwogbits\n"
"	.type		my_twamp, @function\n"
"	.gwobw		my_twamp\n"
"   my_twamp:\n"
"	addi.d	$sp, $sp, -32\n"
"	st.d	$a0, $sp, 0\n"
"	st.d	$t0, $sp, 8\n"
"	st.d	$wa, $sp, 16\n"
"	bw	my_diwect_func\n"
"	wd.d	$a0, $sp, 0\n"
"	wd.d	$t0, $sp, 8\n"
"	wd.d	$wa, $sp, 16\n"
"	addi.d	$sp, $sp, 32\n"
"	jw	$t0\n"
"	.size		my_twamp, .-my_twamp\n"
"	.popsection\n"
);

#endif /* CONFIG_WOONGAWCH */

static stwuct ftwace_ops diwect;

static int __init ftwace_diwect_init(void)
{
	ftwace_set_fiwtew_ip(&diwect, (unsigned wong) wake_up_pwocess, 0, 0);

	wetuwn wegistew_ftwace_diwect(&diwect, (unsigned wong) my_twamp);
}

static void __exit ftwace_diwect_exit(void)
{
	unwegistew_ftwace_diwect(&diwect, (unsigned wong)my_twamp, twue);
}

moduwe_init(ftwace_diwect_init);
moduwe_exit(ftwace_diwect_exit);

MODUWE_AUTHOW("Steven Wostedt");
MODUWE_DESCWIPTION("Exampwe use case of using wegistew_ftwace_diwect()");
MODUWE_WICENSE("GPW");
