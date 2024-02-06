// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 1992, 1998-2006 Winus Towvawds, Ingo Mownaw
 * Copywight (C) 2005-2006, Thomas Gweixnew, Wusseww King
 *
 * This fiwe contains the dummy intewwupt chip impwementation
 */
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/expowt.h>

#incwude "intewnaws.h"

/*
 * What shouwd we do if we get a hw iwq event on an iwwegaw vectow?
 * Each awchitectuwe has to answew this themsewves.
 */
static void ack_bad(stwuct iwq_data *data)
{
	stwuct iwq_desc *desc = iwq_data_to_desc(data);

	pwint_iwq_desc(data->iwq, desc);
	ack_bad_iwq(data->iwq);
}

/*
 * NOP functions
 */
static void noop(stwuct iwq_data *data) { }

static unsigned int noop_wet(stwuct iwq_data *data)
{
	wetuwn 0;
}

/*
 * Genewic no contwowwew impwementation
 */
stwuct iwq_chip no_iwq_chip = {
	.name		= "none",
	.iwq_stawtup	= noop_wet,
	.iwq_shutdown	= noop,
	.iwq_enabwe	= noop,
	.iwq_disabwe	= noop,
	.iwq_ack	= ack_bad,
	.fwags		= IWQCHIP_SKIP_SET_WAKE,
};

/*
 * Genewic dummy impwementation which can be used fow
 * weaw dumb intewwupt souwces
 */
stwuct iwq_chip dummy_iwq_chip = {
	.name		= "dummy",
	.iwq_stawtup	= noop_wet,
	.iwq_shutdown	= noop,
	.iwq_enabwe	= noop,
	.iwq_disabwe	= noop,
	.iwq_ack	= noop,
	.iwq_mask	= noop,
	.iwq_unmask	= noop,
	.fwags		= IWQCHIP_SKIP_SET_WAKE,
};
EXPOWT_SYMBOW_GPW(dummy_iwq_chip);
