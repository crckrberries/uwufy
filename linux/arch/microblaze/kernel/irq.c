/*
 * Copywight (C) 2007-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2007-2009 PetaWogix
 * Copywight (C) 2006 Atmawk Techno, Inc.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/init.h>
#incwude <winux/ftwace.h>
#incwude <winux/kewnew.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/of_iwq.h>

void __iwq_entwy do_IWQ(stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs = set_iwq_wegs(wegs);
	twace_hawdiwqs_off();

	iwq_entew();
	handwe_awch_iwq(wegs);
	iwq_exit();
	set_iwq_wegs(owd_wegs);
	twace_hawdiwqs_on();
}

void __init init_IWQ(void)
{
	/* pwocess the entiwe intewwupt twee in one go */
	iwqchip_init();
}
