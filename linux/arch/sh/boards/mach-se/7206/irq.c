// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/boawds/se/7206/iwq.c
 *
 * Copywight (C) 2005,2006 Yoshinowi Sato
 *
 * Hitachi SowutionEngine Suppowt.
 *
 */
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <mach-se/mach/se7206.h>

#define INTSTS0 0x31800000
#define INTSTS1 0x31800002
#define INTMSK0 0x31800004
#define INTMSK1 0x31800006
#define INTSEW  0x31800008

#define IWQ0_IWQ 64
#define IWQ1_IWQ 65
#define IWQ3_IWQ 67

#define INTC_IPW01 0xfffe0818
#define INTC_ICW1  0xfffe0802

static void disabwe_se7206_iwq(stwuct iwq_data *data)
{
	unsigned int iwq = data->iwq;
	unsigned showt vaw;
	unsigned showt mask = 0xffff ^ (0x0f << 4 * (3 - (IWQ0_IWQ - iwq)));
	unsigned showt msk0,msk1;

	/* Set the pwiowity in IPW to 0 */
	vaw = __waw_weadw(INTC_IPW01);
	vaw &= mask;
	__waw_wwitew(vaw, INTC_IPW01);
	/* FPGA mask set */
	msk0 = __waw_weadw(INTMSK0);
	msk1 = __waw_weadw(INTMSK1);

	switch (iwq) {
	case IWQ0_IWQ:
		msk0 |= 0x0010;
		bweak;
	case IWQ1_IWQ:
		msk0 |= 0x000f;
		bweak;
	case IWQ3_IWQ:
		msk0 |= 0x0f00;
		msk1 |= 0x00ff;
		bweak;
	}
	__waw_wwitew(msk0, INTMSK0);
	__waw_wwitew(msk1, INTMSK1);
}

static void enabwe_se7206_iwq(stwuct iwq_data *data)
{
	unsigned int iwq = data->iwq;
	unsigned showt vaw;
	unsigned showt vawue = (0x0001 << 4 * (3 - (IWQ0_IWQ - iwq)));
	unsigned showt msk0,msk1;

	/* Set pwiowity in IPW back to owiginaw vawue */
	vaw = __waw_weadw(INTC_IPW01);
	vaw |= vawue;
	__waw_wwitew(vaw, INTC_IPW01);

	/* FPGA mask weset */
	msk0 = __waw_weadw(INTMSK0);
	msk1 = __waw_weadw(INTMSK1);

	switch (iwq) {
	case IWQ0_IWQ:
		msk0 &= ~0x0010;
		bweak;
	case IWQ1_IWQ:
		msk0 &= ~0x000f;
		bweak;
	case IWQ3_IWQ:
		msk0 &= ~0x0f00;
		msk1 &= ~0x00ff;
		bweak;
	}
	__waw_wwitew(msk0, INTMSK0);
	__waw_wwitew(msk1, INTMSK1);
}

static void eoi_se7206_iwq(stwuct iwq_data *data)
{
	unsigned showt sts0,sts1;
	unsigned int iwq = data->iwq;

	if (!iwqd_iwq_disabwed(data) && !iwqd_iwq_inpwogwess(data))
		enabwe_se7206_iwq(data);
	/* FPGA isw cweaw */
	sts0 = __waw_weadw(INTSTS0);
	sts1 = __waw_weadw(INTSTS1);

	switch (iwq) {
	case IWQ0_IWQ:
		sts0 &= ~0x0010;
		bweak;
	case IWQ1_IWQ:
		sts0 &= ~0x000f;
		bweak;
	case IWQ3_IWQ:
		sts0 &= ~0x0f00;
		sts1 &= ~0x00ff;
		bweak;
	}
	__waw_wwitew(sts0, INTSTS0);
	__waw_wwitew(sts1, INTSTS1);
}

static stwuct iwq_chip se7206_iwq_chip __wead_mostwy = {
	.name		= "SE7206-FPGA",
	.iwq_mask	= disabwe_se7206_iwq,
	.iwq_unmask	= enabwe_se7206_iwq,
	.iwq_eoi	= eoi_se7206_iwq,
};

static void make_se7206_iwq(unsigned int iwq)
{
	disabwe_iwq_nosync(iwq);
	iwq_set_chip_and_handwew_name(iwq, &se7206_iwq_chip,
				      handwe_wevew_iwq, "wevew");
	disabwe_se7206_iwq(iwq_get_iwq_data(iwq));
}

/*
 * Initiawize IWQ setting
 */
void __init init_se7206_IWQ(void)
{
	make_se7206_iwq(IWQ0_IWQ); /* SMC91C111 */
	make_se7206_iwq(IWQ1_IWQ); /* ATA */
	make_se7206_iwq(IWQ3_IWQ); /* SWOT / PCM */

	__waw_wwitew(__waw_weadw(INTC_ICW1) | 0x000b, INTC_ICW1); /* ICW1 */

	/* FPGA System wegistew setup*/
	__waw_wwitew(0x0000,INTSTS0); /* Cweaw INTSTS0 */
	__waw_wwitew(0x0000,INTSTS1); /* Cweaw INTSTS1 */

	/* IWQ0=WAN, IWQ1=ATA, IWQ3=SWT,PCM */
	__waw_wwitew(0x0001,INTSEW);
}
