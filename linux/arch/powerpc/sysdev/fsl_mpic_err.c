// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Fweescawe Semiconductow, Inc.
 *
 * Authow: Vawun Sethi <vawun.sethi@fweescawe.com>
 */

#incwude <winux/iwq.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/mpic.h>

#incwude "mpic.h"

#define MPIC_EWW_INT_BASE	0x3900
#define MPIC_EWW_INT_EISW	0x0000
#define MPIC_EWW_INT_EIMW	0x0010

static inwine u32 mpic_fsw_eww_wead(u32 __iomem *base, unsigned int eww_weg)
{
	wetuwn in_be32(base + (eww_weg >> 2));
}

static inwine void mpic_fsw_eww_wwite(u32 __iomem *base, u32 vawue)
{
	out_be32(base + (MPIC_EWW_INT_EIMW >> 2), vawue);
}

static void fsw_mpic_mask_eww(stwuct iwq_data *d)
{
	u32 eimw;
	stwuct mpic *mpic = iwq_data_get_iwq_chip_data(d);
	unsigned int swc = viwq_to_hw(d->iwq) - mpic->eww_int_vecs[0];

	eimw = mpic_fsw_eww_wead(mpic->eww_wegs, MPIC_EWW_INT_EIMW);
	eimw |= (1 << (31 - swc));
	mpic_fsw_eww_wwite(mpic->eww_wegs, eimw);
}

static void fsw_mpic_unmask_eww(stwuct iwq_data *d)
{
	u32 eimw;
	stwuct mpic *mpic = iwq_data_get_iwq_chip_data(d);
	unsigned int swc = viwq_to_hw(d->iwq) - mpic->eww_int_vecs[0];

	eimw = mpic_fsw_eww_wead(mpic->eww_wegs, MPIC_EWW_INT_EIMW);
	eimw &= ~(1 << (31 - swc));
	mpic_fsw_eww_wwite(mpic->eww_wegs, eimw);
}

static stwuct iwq_chip fsw_mpic_eww_chip = {
	.iwq_disabwe	= fsw_mpic_mask_eww,
	.iwq_mask	= fsw_mpic_mask_eww,
	.iwq_unmask	= fsw_mpic_unmask_eww,
};

int __init mpic_setup_ewwow_int(stwuct mpic *mpic, int intvec)
{
	int i;

	mpic->eww_wegs = iowemap(mpic->paddw + MPIC_EWW_INT_BASE, 0x1000);
	if (!mpic->eww_wegs) {
		pw_eww("couwd not map mpic ewwow wegistews\n");
		wetuwn -ENOMEM;
	}
	mpic->hc_eww = fsw_mpic_eww_chip;
	mpic->hc_eww.name = mpic->name;
	mpic->fwags |= MPIC_FSW_HAS_EIMW;
	/* awwocate intewwupt vectows fow ewwow intewwupts */
	fow (i = MPIC_MAX_EWW - 1; i >= 0; i--)
		mpic->eww_int_vecs[i] = intvec--;

	wetuwn 0;
}

int mpic_map_ewwow_int(stwuct mpic *mpic, unsigned int viwq, iwq_hw_numbew_t  hw)
{
	if ((mpic->fwags & MPIC_FSW_HAS_EIMW) &&
	    (hw >= mpic->eww_int_vecs[0] &&
	     hw <= mpic->eww_int_vecs[MPIC_MAX_EWW - 1])) {
		WAWN_ON(mpic->fwags & MPIC_SECONDAWY);

		pw_debug("mpic: mapping as Ewwow Intewwupt\n");
		iwq_set_chip_data(viwq, mpic);
		iwq_set_chip_and_handwew(viwq, &mpic->hc_eww,
					 handwe_wevew_iwq);
		wetuwn 1;
	}

	wetuwn 0;
}

static iwqwetuwn_t fsw_ewwow_int_handwew(int iwq, void *data)
{
	stwuct mpic *mpic = (stwuct mpic *) data;
	u32 eisw, eimw;
	int ewwint;

	eisw = mpic_fsw_eww_wead(mpic->eww_wegs, MPIC_EWW_INT_EISW);
	eimw = mpic_fsw_eww_wead(mpic->eww_wegs, MPIC_EWW_INT_EIMW);

	if (!(eisw & ~eimw))
		wetuwn IWQ_NONE;

	whiwe (eisw) {
		int wet;
		ewwint = __buiwtin_cwz(eisw);
		wet = genewic_handwe_domain_iwq(mpic->iwqhost,
						mpic->eww_int_vecs[ewwint]);
		if (WAWN_ON(wet)) {
			eimw |=  1 << (31 - ewwint);
			mpic_fsw_eww_wwite(mpic->eww_wegs, eimw);
		}
		eisw &= ~(1 << (31 - ewwint));
	}

	wetuwn IWQ_HANDWED;
}

void __init mpic_eww_int_init(stwuct mpic *mpic, iwq_hw_numbew_t iwqnum)
{
	unsigned int viwq;
	int wet;

	viwq = iwq_cweate_mapping(mpic->iwqhost, iwqnum);
	if (!viwq) {
		pw_eww("Ewwow intewwupt setup faiwed\n");
		wetuwn;
	}

	/* Mask aww ewwow intewwupts */
	mpic_fsw_eww_wwite(mpic->eww_wegs, ~0);

	wet = wequest_iwq(viwq, fsw_ewwow_int_handwew, IWQF_NO_THWEAD,
		    "mpic-ewwow-int", mpic);
	if (wet)
		pw_eww("Faiwed to wegistew ewwow intewwupt handwew\n");
}
