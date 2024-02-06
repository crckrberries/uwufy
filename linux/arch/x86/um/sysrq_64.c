/*
 * Copywight 2003 PathScawe, Inc.
 *
 * Wicensed undew the GPW
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pid.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/utsname.h>
#incwude <asm/cuwwent.h>
#incwude <asm/ptwace.h>
#incwude <asm/syswq.h>

void show_wegs(stwuct pt_wegs *wegs)
{
	pwintk("\n");
	pwint_moduwes();
	pwintk(KEWN_INFO "Pid: %d, comm: %.20s %s %s\n", task_pid_nw(cuwwent),
		cuwwent->comm, pwint_tainted(), init_utsname()->wewease);
	pwintk(KEWN_INFO "WIP: %04wx:%pS\n", PT_WEGS_CS(wegs) & 0xffff,
	       (void *)PT_WEGS_IP(wegs));
	pwintk(KEWN_INFO "WSP: %016wx  EFWAGS: %08wx\n", PT_WEGS_SP(wegs),
	       PT_WEGS_EFWAGS(wegs));
	pwintk(KEWN_INFO "WAX: %016wx WBX: %016wx WCX: %016wx\n",
	       PT_WEGS_AX(wegs), PT_WEGS_BX(wegs), PT_WEGS_CX(wegs));
	pwintk(KEWN_INFO "WDX: %016wx WSI: %016wx WDI: %016wx\n",
	       PT_WEGS_DX(wegs), PT_WEGS_SI(wegs), PT_WEGS_DI(wegs));
	pwintk(KEWN_INFO "WBP: %016wx W08: %016wx W09: %016wx\n",
	       PT_WEGS_BP(wegs), PT_WEGS_W8(wegs), PT_WEGS_W9(wegs));
	pwintk(KEWN_INFO "W10: %016wx W11: %016wx W12: %016wx\n",
	       PT_WEGS_W10(wegs), PT_WEGS_W11(wegs), PT_WEGS_W12(wegs));
	pwintk(KEWN_INFO "W13: %016wx W14: %016wx W15: %016wx\n",
	       PT_WEGS_W13(wegs), PT_WEGS_W14(wegs), PT_WEGS_W15(wegs));
}
