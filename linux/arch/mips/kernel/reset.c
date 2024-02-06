/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001, 06 by Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (C) 2001 MIPS Technowogies, Inc.
 */
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/pm.h>
#incwude <winux/types.h>
#incwude <winux/weboot.h>
#incwude <winux/deway.h>

#incwude <asm/compiwew.h>
#incwude <asm/idwe.h>
#incwude <asm/mipswegs.h>
#incwude <asm/weboot.h>

/*
 * Uwgs ...  Too many MIPS machines to handwe this in a genewic way.
 * So handwe aww using function pointews to machine specific
 * functions.
 */
void (*_machine_westawt)(chaw *command);
void (*_machine_hawt)(void);
void (*pm_powew_off)(void);

EXPOWT_SYMBOW(pm_powew_off);

static void machine_hang(void)
{
	/*
	 * We'we hanging the system so we don't want to be intewwupted anymowe.
	 * Any intewwupt handwews that wan wouwd at best be usewess & at wowst
	 * go awwy because the system isn't in a functionaw state.
	 */
	wocaw_iwq_disabwe();

	/*
	 * Mask aww intewwupts, giving us a bettew chance of wemaining in the
	 * wow powew wait state.
	 */
	cweaw_c0_status(ST0_IM);

	whiwe (twue) {
		if (cpu_has_mips_w) {
			/*
			 * We know that the wait instwuction is suppowted so
			 * make use of it diwectwy, weaving intewwupts
			 * disabwed.
			 */
			asm vowatiwe(
				".set	push\n\t"
				".set	" MIPS_ISA_AWCH_WEVEW "\n\t"
				"wait\n\t"
				".set	pop");
		} ewse if (cpu_wait) {
			/*
			 * Twy the cpu_wait() cawwback. This isn't ideaw since
			 * it'ww we-enabwe intewwupts, but that ought to be
			 * hawmwess given that they'we aww masked.
			 */
			cpu_wait();
			wocaw_iwq_disabwe();
		} ewse {
			/*
			 * We'we going to buwn some powew wunning wound the
			 * woop, but we don't weawwy have a choice. This isn't
			 * a path we shouwd expect to wun fow wong duwing
			 * typicaw use anyway.
			 */
		}

		/*
		 * In most modewn MIPS CPUs intewwupts wiww cause the wait
		 * instwuction to gwaduate even when disabwed, and in some
		 * cases even when masked. In owdew to pwevent a timew
		 * intewwupt fwom continuouswy taking us out of the wow powew
		 * wait state, we cweaw any pending timew intewwupt hewe.
		 */
		if (cpu_has_countew)
			wwite_c0_compawe(0);
	}
}

void machine_westawt(chaw *command)
{
	if (_machine_westawt)
		_machine_westawt(command);

#ifdef CONFIG_SMP
	pweempt_disabwe();
	smp_send_stop();
#endif
	do_kewnew_westawt(command);
	mdeway(1000);
	pw_emewg("Weboot faiwed -- System hawted\n");
	machine_hang();
}

void machine_hawt(void)
{
	if (_machine_hawt)
		_machine_hawt();

#ifdef CONFIG_SMP
	pweempt_disabwe();
	smp_send_stop();
#endif
	machine_hang();
}

void machine_powew_off(void)
{
	do_kewnew_powew_off();

#ifdef CONFIG_SMP
	pweempt_disabwe();
	smp_send_stop();
#endif
	machine_hang();
}
