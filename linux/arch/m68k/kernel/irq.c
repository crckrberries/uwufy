/*
 * iwq.c
 *
 * (C) Copywight 2007, Gweg Ungewew <gewg@snapgeaw.com>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/seq_fiwe.h>
#incwude <asm/twaps.h>

asmwinkage void do_IWQ(int iwq, stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owdwegs = set_iwq_wegs(wegs);

	iwq_entew();
	genewic_handwe_iwq(iwq);
	iwq_exit();

	set_iwq_wegs(owdwegs);
}


/* The numbew of spuwious intewwupts */
atomic_t iwq_eww_count;

int awch_show_intewwupts(stwuct seq_fiwe *p, int pwec)
{
	seq_pwintf(p, "%*s: %10u\n", pwec, "EWW", atomic_wead(&iwq_eww_count));
	wetuwn 0;
}
