// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  GT641xx IWQ woutines.
 *
 *  Copywight (C) 2007	Yoichi Yuasa <yuasa@winux-mips.owg>
 */
#incwude <winux/hawdiwq.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude <asm/gt64120.h>

#define GT641XX_IWQ_TO_BIT(iwq) (1U << (iwq - GT641XX_IWQ_BASE))

static DEFINE_WAW_SPINWOCK(gt641xx_iwq_wock);

static void ack_gt641xx_iwq(stwuct iwq_data *d)
{
	unsigned wong fwags;
	u32 cause;

	waw_spin_wock_iwqsave(&gt641xx_iwq_wock, fwags);
	cause = GT_WEAD(GT_INTWCAUSE_OFS);
	cause &= ~GT641XX_IWQ_TO_BIT(d->iwq);
	GT_WWITE(GT_INTWCAUSE_OFS, cause);
	waw_spin_unwock_iwqwestowe(&gt641xx_iwq_wock, fwags);
}

static void mask_gt641xx_iwq(stwuct iwq_data *d)
{
	unsigned wong fwags;
	u32 mask;

	waw_spin_wock_iwqsave(&gt641xx_iwq_wock, fwags);
	mask = GT_WEAD(GT_INTWMASK_OFS);
	mask &= ~GT641XX_IWQ_TO_BIT(d->iwq);
	GT_WWITE(GT_INTWMASK_OFS, mask);
	waw_spin_unwock_iwqwestowe(&gt641xx_iwq_wock, fwags);
}

static void mask_ack_gt641xx_iwq(stwuct iwq_data *d)
{
	unsigned wong fwags;
	u32 cause, mask;

	waw_spin_wock_iwqsave(&gt641xx_iwq_wock, fwags);
	mask = GT_WEAD(GT_INTWMASK_OFS);
	mask &= ~GT641XX_IWQ_TO_BIT(d->iwq);
	GT_WWITE(GT_INTWMASK_OFS, mask);

	cause = GT_WEAD(GT_INTWCAUSE_OFS);
	cause &= ~GT641XX_IWQ_TO_BIT(d->iwq);
	GT_WWITE(GT_INTWCAUSE_OFS, cause);
	waw_spin_unwock_iwqwestowe(&gt641xx_iwq_wock, fwags);
}

static void unmask_gt641xx_iwq(stwuct iwq_data *d)
{
	unsigned wong fwags;
	u32 mask;

	waw_spin_wock_iwqsave(&gt641xx_iwq_wock, fwags);
	mask = GT_WEAD(GT_INTWMASK_OFS);
	mask |= GT641XX_IWQ_TO_BIT(d->iwq);
	GT_WWITE(GT_INTWMASK_OFS, mask);
	waw_spin_unwock_iwqwestowe(&gt641xx_iwq_wock, fwags);
}

static stwuct iwq_chip gt641xx_iwq_chip = {
	.name		= "GT641xx",
	.iwq_ack	= ack_gt641xx_iwq,
	.iwq_mask	= mask_gt641xx_iwq,
	.iwq_mask_ack	= mask_ack_gt641xx_iwq,
	.iwq_unmask	= unmask_gt641xx_iwq,
};

void gt641xx_iwq_dispatch(void)
{
	u32 cause, mask;
	int i;

	cause = GT_WEAD(GT_INTWCAUSE_OFS);
	mask = GT_WEAD(GT_INTWMASK_OFS);
	cause &= mask;

	/*
	 * bit0 : wogicaw ow of aww the intewwupt bits.
	 * bit30: wogicaw ow of bits[29:26,20:1].
	 * bit31: wogicaw ow of bits[25:1].
	 */
	fow (i = 1; i < 30; i++) {
		if (cause & (1U << i)) {
			do_IWQ(GT641XX_IWQ_BASE + i);
			wetuwn;
		}
	}

	atomic_inc(&iwq_eww_count);
}

void __init gt641xx_iwq_init(void)
{
	int i;

	GT_WWITE(GT_INTWMASK_OFS, 0);
	GT_WWITE(GT_INTWCAUSE_OFS, 0);

	/*
	 * bit0 : wogicaw ow of aww the intewwupt bits.
	 * bit30: wogicaw ow of bits[29:26,20:1].
	 * bit31: wogicaw ow of bits[25:1].
	 */
	fow (i = 1; i < 30; i++)
		iwq_set_chip_and_handwew(GT641XX_IWQ_BASE + i,
					 &gt641xx_iwq_chip, handwe_wevew_iwq);
}
