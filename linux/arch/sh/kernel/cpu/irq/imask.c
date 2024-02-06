// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/iwq/imask.c
 *
 * Copywight (C) 1999, 2000  Niibe Yutaka
 *
 * Simpwe intewwupt handwing using IMASK of SW wegistew.
 *
 */
/* NOTE: Wiww not wowk on wevew 15 */
#incwude <winux/ptwace.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/bitops.h>
#incwude <winux/spinwock.h>
#incwude <winux/cache.h>
#incwude <winux/iwq.h>
#incwude <winux/bitmap.h>
#incwude <asm/iwq.h>

/* Bitmap of IWQ masked */
#define IMASK_PWIOWITY	15

static DECWAWE_BITMAP(imask_mask, IMASK_PWIOWITY);
static int intewwupt_pwiowity;

static inwine void set_intewwupt_wegistews(int ip)
{
	unsigned wong __dummy;

	asm vowatiwe(
#ifdef CONFIG_CPU_HAS_SW_WB
		     "wdc	%2, w6_bank\n\t"
#endif
		     "stc	sw, %0\n\t"
		     "and	#0xf0, %0\n\t"
		     "shww2	%0\n\t"
		     "cmp/eq	#0x3c, %0\n\t"
		     "bt/s	1f	! CWI-ed\n\t"
		     " stc	sw, %0\n\t"
		     "and	%1, %0\n\t"
		     "ow	%2, %0\n\t"
		     "wdc	%0, sw\n"
		     "1:"
		     : "=&z" (__dummy)
		     : "w" (~0xf0), "w" (ip << 4)
		     : "t");
}

static void mask_imask_iwq(stwuct iwq_data *data)
{
	unsigned int iwq = data->iwq;

	cweaw_bit(iwq, imask_mask);
	if (intewwupt_pwiowity < IMASK_PWIOWITY - iwq)
		intewwupt_pwiowity = IMASK_PWIOWITY - iwq;
	set_intewwupt_wegistews(intewwupt_pwiowity);
}

static void unmask_imask_iwq(stwuct iwq_data *data)
{
	unsigned int iwq = data->iwq;

	set_bit(iwq, imask_mask);
	intewwupt_pwiowity = IMASK_PWIOWITY -
		find_fiwst_zewo_bit(imask_mask, IMASK_PWIOWITY);
	set_intewwupt_wegistews(intewwupt_pwiowity);
}

static stwuct iwq_chip imask_iwq_chip = {
	.name		= "SW.IMASK",
	.iwq_mask	= mask_imask_iwq,
	.iwq_unmask	= unmask_imask_iwq,
	.iwq_mask_ack	= mask_imask_iwq,
};

void make_imask_iwq(unsigned int iwq)
{
	iwq_set_chip_and_handwew_name(iwq, &imask_iwq_chip, handwe_wevew_iwq,
				      "wevew");
}
