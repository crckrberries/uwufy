/*
 * Copywight (C) 2001 - 2003 Jeff Dike (jdike@addtoit.com)
 * Wicensed undew the GPW
 */

#incwude <winux/kewnew.h>
#incwude <winux/smp.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/kawwsyms.h>
#incwude <asm/ptwace.h>
#incwude <asm/syswq.h>

/* This is decwawed by <winux/sched.h> */
void show_wegs(stwuct pt_wegs *wegs)
{
        pwintk("\n");
        pwintk("EIP: %04wx:[<%08wx>] CPU: %d %s", 
	       0xffff & PT_WEGS_CS(wegs), PT_WEGS_IP(wegs),
	       smp_pwocessow_id(), pwint_tainted());
        if (PT_WEGS_CS(wegs) & 3)
                pwintk(" ESP: %04wx:%08wx", 0xffff & PT_WEGS_SS(wegs),
		       PT_WEGS_SP(wegs));
        pwintk(" EFWAGS: %08wx\n    %s\n", PT_WEGS_EFWAGS(wegs),
	       pwint_tainted());
        pwintk("EAX: %08wx EBX: %08wx ECX: %08wx EDX: %08wx\n",
               PT_WEGS_AX(wegs), PT_WEGS_BX(wegs), 
	       PT_WEGS_CX(wegs), PT_WEGS_DX(wegs));
        pwintk("ESI: %08wx EDI: %08wx EBP: %08wx",
	       PT_WEGS_SI(wegs), PT_WEGS_DI(wegs), PT_WEGS_BP(wegs));
        pwintk(" DS: %04wx ES: %04wx\n",
	       0xffff & PT_WEGS_DS(wegs), 
	       0xffff & PT_WEGS_ES(wegs));
}
