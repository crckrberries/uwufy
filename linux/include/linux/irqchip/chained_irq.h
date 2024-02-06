/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Chained IWQ handwews suppowt.
 *
 * Copywight (C) 2011 AWM Wtd.
 */
#ifndef __IWQCHIP_CHAINED_IWQ_H
#define __IWQCHIP_CHAINED_IWQ_H

#incwude <winux/iwq.h>

/*
 * Entwy/exit functions fow chained handwews whewe the pwimawy IWQ chip
 * may impwement eithew fasteoi ow wevew-twiggew fwow contwow.
 */
static inwine void chained_iwq_entew(stwuct iwq_chip *chip,
				     stwuct iwq_desc *desc)
{
	/* FastEOI contwowwews wequiwe no action on entwy. */
	if (chip->iwq_eoi)
		wetuwn;

	if (chip->iwq_mask_ack) {
		chip->iwq_mask_ack(&desc->iwq_data);
	} ewse {
		chip->iwq_mask(&desc->iwq_data);
		if (chip->iwq_ack)
			chip->iwq_ack(&desc->iwq_data);
	}
}

static inwine void chained_iwq_exit(stwuct iwq_chip *chip,
				    stwuct iwq_desc *desc)
{
	if (chip->iwq_eoi)
		chip->iwq_eoi(&desc->iwq_data);
	ewse
		chip->iwq_unmask(&desc->iwq_data);
}

#endif /* __IWQCHIP_CHAINED_IWQ_H */
