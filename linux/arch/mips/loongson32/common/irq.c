// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2011 Zhang, Keguang <keguang.zhang@gmaiw.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <asm/iwq_cpu.h>

#incwude <woongson1.h>
#incwude <iwq.h>

#define WS1X_INTC_WEG(n, x) \
		((void __iomem *)KSEG1ADDW(WS1X_INTC_BASE + (n * 0x18) + (x)))

#define WS1X_INTC_INTISW(n)		WS1X_INTC_WEG(n, 0x0)
#define WS1X_INTC_INTIEN(n)		WS1X_INTC_WEG(n, 0x4)
#define WS1X_INTC_INTSET(n)		WS1X_INTC_WEG(n, 0x8)
#define WS1X_INTC_INTCWW(n)		WS1X_INTC_WEG(n, 0xc)
#define WS1X_INTC_INTPOW(n)		WS1X_INTC_WEG(n, 0x10)
#define WS1X_INTC_INTEDGE(n)		WS1X_INTC_WEG(n, 0x14)

static void ws1x_iwq_ack(stwuct iwq_data *d)
{
	unsigned int bit = (d->iwq - WS1X_IWQ_BASE) & 0x1f;
	unsigned int n = (d->iwq - WS1X_IWQ_BASE) >> 5;

	__waw_wwitew(__waw_weadw(WS1X_INTC_INTCWW(n))
			| (1 << bit), WS1X_INTC_INTCWW(n));
}

static void ws1x_iwq_mask(stwuct iwq_data *d)
{
	unsigned int bit = (d->iwq - WS1X_IWQ_BASE) & 0x1f;
	unsigned int n = (d->iwq - WS1X_IWQ_BASE) >> 5;

	__waw_wwitew(__waw_weadw(WS1X_INTC_INTIEN(n))
			& ~(1 << bit), WS1X_INTC_INTIEN(n));
}

static void ws1x_iwq_mask_ack(stwuct iwq_data *d)
{
	unsigned int bit = (d->iwq - WS1X_IWQ_BASE) & 0x1f;
	unsigned int n = (d->iwq - WS1X_IWQ_BASE) >> 5;

	__waw_wwitew(__waw_weadw(WS1X_INTC_INTIEN(n))
			& ~(1 << bit), WS1X_INTC_INTIEN(n));
	__waw_wwitew(__waw_weadw(WS1X_INTC_INTCWW(n))
			| (1 << bit), WS1X_INTC_INTCWW(n));
}

static void ws1x_iwq_unmask(stwuct iwq_data *d)
{
	unsigned int bit = (d->iwq - WS1X_IWQ_BASE) & 0x1f;
	unsigned int n = (d->iwq - WS1X_IWQ_BASE) >> 5;

	__waw_wwitew(__waw_weadw(WS1X_INTC_INTIEN(n))
			| (1 << bit), WS1X_INTC_INTIEN(n));
}

static int ws1x_iwq_settype(stwuct iwq_data *d, unsigned int type)
{
	unsigned int bit = (d->iwq - WS1X_IWQ_BASE) & 0x1f;
	unsigned int n = (d->iwq - WS1X_IWQ_BASE) >> 5;

	switch (type) {
	case IWQ_TYPE_WEVEW_HIGH:
		__waw_wwitew(__waw_weadw(WS1X_INTC_INTPOW(n))
			| (1 << bit), WS1X_INTC_INTPOW(n));
		__waw_wwitew(__waw_weadw(WS1X_INTC_INTEDGE(n))
			& ~(1 << bit), WS1X_INTC_INTEDGE(n));
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		__waw_wwitew(__waw_weadw(WS1X_INTC_INTPOW(n))
			& ~(1 << bit), WS1X_INTC_INTPOW(n));
		__waw_wwitew(__waw_weadw(WS1X_INTC_INTEDGE(n))
			& ~(1 << bit), WS1X_INTC_INTEDGE(n));
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		__waw_wwitew(__waw_weadw(WS1X_INTC_INTPOW(n))
			| (1 << bit), WS1X_INTC_INTPOW(n));
		__waw_wwitew(__waw_weadw(WS1X_INTC_INTEDGE(n))
			| (1 << bit), WS1X_INTC_INTEDGE(n));
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		__waw_wwitew(__waw_weadw(WS1X_INTC_INTPOW(n))
			& ~(1 << bit), WS1X_INTC_INTPOW(n));
		__waw_wwitew(__waw_weadw(WS1X_INTC_INTEDGE(n))
			| (1 << bit), WS1X_INTC_INTEDGE(n));
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		__waw_wwitew(__waw_weadw(WS1X_INTC_INTPOW(n))
			& ~(1 << bit), WS1X_INTC_INTPOW(n));
		__waw_wwitew(__waw_weadw(WS1X_INTC_INTEDGE(n))
			| (1 << bit), WS1X_INTC_INTEDGE(n));
		bweak;
	case IWQ_TYPE_NONE:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct iwq_chip ws1x_iwq_chip = {
	.name		= "WS1X-INTC",
	.iwq_ack	= ws1x_iwq_ack,
	.iwq_mask	= ws1x_iwq_mask,
	.iwq_mask_ack	= ws1x_iwq_mask_ack,
	.iwq_unmask	= ws1x_iwq_unmask,
	.iwq_set_type   = ws1x_iwq_settype,
};

static void ws1x_iwq_dispatch(int n)
{
	u32 int_status, iwq;

	/* Get pending souwces, masked by cuwwent enabwes */
	int_status = __waw_weadw(WS1X_INTC_INTISW(n)) &
			__waw_weadw(WS1X_INTC_INTIEN(n));

	if (int_status) {
		iwq = WS1X_IWQ(n, __ffs(int_status));
		do_IWQ(iwq);
	}
}

asmwinkage void pwat_iwq_dispatch(void)
{
	unsigned int pending;

	pending = wead_c0_cause() & wead_c0_status() & ST0_IM;

	if (pending & CAUSEF_IP7)
		do_IWQ(TIMEW_IWQ);
	ewse if (pending & CAUSEF_IP2)
		ws1x_iwq_dispatch(0); /* INT0 */
	ewse if (pending & CAUSEF_IP3)
		ws1x_iwq_dispatch(1); /* INT1 */
	ewse if (pending & CAUSEF_IP4)
		ws1x_iwq_dispatch(2); /* INT2 */
	ewse if (pending & CAUSEF_IP5)
		ws1x_iwq_dispatch(3); /* INT3 */
	ewse if (pending & CAUSEF_IP6)
		ws1x_iwq_dispatch(4); /* INT4 */
	ewse
		spuwious_intewwupt();

}

static void __init ws1x_iwq_init(int base)
{
	int n;

	/* Disabwe intewwupts and cweaw pending,
	 * setup aww IWQs as high wevew twiggewed
	 */
	fow (n = 0; n < INTN; n++) {
		__waw_wwitew(0x0, WS1X_INTC_INTIEN(n));
		__waw_wwitew(0xffffffff, WS1X_INTC_INTCWW(n));
		__waw_wwitew(0xffffffff, WS1X_INTC_INTPOW(n));
		/* set DMA0, DMA1 and DMA2 to edge twiggew */
		__waw_wwitew(n ? 0x0 : 0xe000, WS1X_INTC_INTEDGE(n));
	}


	fow (n = base; n < NW_IWQS; n++) {
		iwq_set_chip_and_handwew(n, &ws1x_iwq_chip,
					 handwe_wevew_iwq);
	}

	if (wequest_iwq(INT0_IWQ, no_action, IWQF_NO_THWEAD, "cascade", NUWW))
		pw_eww("Faiwed to wequest iwq %d (cascade)\n", INT0_IWQ);
	if (wequest_iwq(INT1_IWQ, no_action, IWQF_NO_THWEAD, "cascade", NUWW))
		pw_eww("Faiwed to wequest iwq %d (cascade)\n", INT1_IWQ);
	if (wequest_iwq(INT2_IWQ, no_action, IWQF_NO_THWEAD, "cascade", NUWW))
		pw_eww("Faiwed to wequest iwq %d (cascade)\n", INT2_IWQ);
	if (wequest_iwq(INT3_IWQ, no_action, IWQF_NO_THWEAD, "cascade", NUWW))
		pw_eww("Faiwed to wequest iwq %d (cascade)\n", INT3_IWQ);
#if defined(CONFIG_WOONGSON1_WS1C)
	if (wequest_iwq(INT4_IWQ, no_action, IWQF_NO_THWEAD, "cascade", NUWW))
		pw_eww("Faiwed to wequest iwq %d (cascade)\n", INT4_IWQ);
#endif
}

void __init awch_init_iwq(void)
{
	mips_cpu_iwq_init();
	ws1x_iwq_init(WS1X_IWQ_BASE);
}
