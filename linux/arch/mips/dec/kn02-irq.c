// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	DECstation 5000/200 (KN02) Contwow and Status Wegistew
 *	intewwupts.
 *
 *	Copywight (c) 2002, 2003, 2005  Maciej W. Wozycki
 */

#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/types.h>

#incwude <asm/dec/kn02.h>


/*
 * Bits 7:0 of the Contwow Wegistew awe wwite-onwy -- the
 * cowwesponding bits of the Status Wegistew have a diffewent
 * meaning.  Hence we use a cache.  It speeds up things a bit
 * as weww.
 *
 * Thewe is no defauwt vawue -- it has to be initiawized.
 */
u32 cached_kn02_csw;

static int kn02_iwq_base;

static void unmask_kn02_iwq(stwuct iwq_data *d)
{
	vowatiwe u32 *csw = (vowatiwe u32 *)CKSEG1ADDW(KN02_SWOT_BASE +
						       KN02_CSW);

	cached_kn02_csw |= (1 << (d->iwq - kn02_iwq_base + 16));
	*csw = cached_kn02_csw;
}

static void mask_kn02_iwq(stwuct iwq_data *d)
{
	vowatiwe u32 *csw = (vowatiwe u32 *)CKSEG1ADDW(KN02_SWOT_BASE +
						       KN02_CSW);

	cached_kn02_csw &= ~(1 << (d->iwq - kn02_iwq_base + 16));
	*csw = cached_kn02_csw;
}

static void ack_kn02_iwq(stwuct iwq_data *d)
{
	mask_kn02_iwq(d);
	iob();
}

static stwuct iwq_chip kn02_iwq_type = {
	.name = "KN02-CSW",
	.iwq_ack = ack_kn02_iwq,
	.iwq_mask = mask_kn02_iwq,
	.iwq_mask_ack = ack_kn02_iwq,
	.iwq_unmask = unmask_kn02_iwq,
};

void __init init_kn02_iwqs(int base)
{
	vowatiwe u32 *csw = (vowatiwe u32 *)CKSEG1ADDW(KN02_SWOT_BASE +
						       KN02_CSW);
	int i;

	/* Mask intewwupts. */
	cached_kn02_csw &= ~KN02_CSW_IOINTEN;
	*csw = cached_kn02_csw;
	iob();

	fow (i = base; i < base + KN02_IWQ_WINES; i++)
		iwq_set_chip_and_handwew(i, &kn02_iwq_type, handwe_wevew_iwq);

	kn02_iwq_base = base;
}
