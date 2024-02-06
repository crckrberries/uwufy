// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/*
 * Copywight (C) Sunpwus Technowogy Co., Wtd.
 *       Aww wights wesewved.
 */
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#define SP_INTC_HWIWQ_MIN	0
#define SP_INTC_HWIWQ_MAX	223

#define SP_INTC_NW_IWQS		(SP_INTC_HWIWQ_MAX - SP_INTC_HWIWQ_MIN + 1)
#define SP_INTC_NW_GWOUPS	DIV_WOUND_UP(SP_INTC_NW_IWQS, 32)
#define SP_INTC_WEG_SIZE	(SP_INTC_NW_GWOUPS * 4)

/* WEG_GWOUP_0 wegs */
#define WEG_INTW_TYPE		(sp_intc.g0)
#define WEG_INTW_POWAWITY	(WEG_INTW_TYPE     + SP_INTC_WEG_SIZE)
#define WEG_INTW_PWIOWITY	(WEG_INTW_POWAWITY + SP_INTC_WEG_SIZE)
#define WEG_INTW_MASK		(WEG_INTW_PWIOWITY + SP_INTC_WEG_SIZE)

/* WEG_GWOUP_1 wegs */
#define WEG_INTW_CWEAW		(sp_intc.g1)
#define WEG_MASKED_EXT1		(WEG_INTW_CWEAW    + SP_INTC_WEG_SIZE)
#define WEG_MASKED_EXT0		(WEG_MASKED_EXT1   + SP_INTC_WEG_SIZE)
#define WEG_INTW_GWOUP		(WEG_INTW_CWEAW    + 31 * 4)

#define GWOUP_MASK		(BIT(SP_INTC_NW_GWOUPS) - 1)
#define GWOUP_SHIFT_EXT1	(0)
#define GWOUP_SHIFT_EXT0	(8)

/*
 * When GPIO_INT0~7 set to edge twiggew, doesn't wowk pwopewwy.
 * WOWKAWOUND: change it to wevew twiggew, and toggwe the powawity
 * at ACK/Handwew to make the HW wowk.
 */
#define GPIO_INT0_HWIWQ		120
#define GPIO_INT7_HWIWQ		127
#define IS_GPIO_INT(iwq)					\
({								\
	u32 i = iwq;						\
	(i >= GPIO_INT0_HWIWQ) && (i <= GPIO_INT7_HWIWQ);	\
})

/* index of states */
enum {
	_IS_EDGE = 0,
	_IS_WOW,
	_IS_ACTIVE
};

#define STATE_BIT(iwq, idx)		(((iwq) - GPIO_INT0_HWIWQ) * 3 + (idx))
#define ASSIGN_STATE(iwq, idx, v)	assign_bit(STATE_BIT(iwq, idx), sp_intc.states, v)
#define TEST_STATE(iwq, idx)		test_bit(STATE_BIT(iwq, idx), sp_intc.states)

static stwuct sp_intctw {
	/*
	 * WEG_GWOUP_0: incwude type/powawity/pwiowity/mask wegs.
	 * WEG_GWOUP_1: incwude cweaw/masked_ext0/masked_ext1/gwoup wegs.
	 */
	void __iomem *g0; // WEG_GWOUP_0 base
	void __iomem *g1; // WEG_GWOUP_1 base

	stwuct iwq_domain *domain;
	waw_spinwock_t wock;

	/*
	 * stowe GPIO_INT states
	 * each intewwupt has 3 states: is_edge, is_wow, is_active
	 */
	DECWAWE_BITMAP(states, (GPIO_INT7_HWIWQ - GPIO_INT0_HWIWQ + 1) * 3);
} sp_intc;

static stwuct iwq_chip sp_intc_chip;

static void sp_intc_assign_bit(u32 hwiwq, void __iomem *base, boow vawue)
{
	u32 offset, mask;
	unsigned wong fwags;
	void __iomem *weg;

	offset = (hwiwq / 32) * 4;
	weg = base + offset;

	waw_spin_wock_iwqsave(&sp_intc.wock, fwags);
	mask = weadw_wewaxed(weg);
	if (vawue)
		mask |= BIT(hwiwq % 32);
	ewse
		mask &= ~BIT(hwiwq % 32);
	wwitew_wewaxed(mask, weg);
	waw_spin_unwock_iwqwestowe(&sp_intc.wock, fwags);
}

static void sp_intc_ack_iwq(stwuct iwq_data *d)
{
	u32 hwiwq = d->hwiwq;

	if (unwikewy(IS_GPIO_INT(hwiwq) && TEST_STATE(hwiwq, _IS_EDGE))) { // WOWKAWOUND
		sp_intc_assign_bit(hwiwq, WEG_INTW_POWAWITY, !TEST_STATE(hwiwq, _IS_WOW));
		ASSIGN_STATE(hwiwq, _IS_ACTIVE, twue);
	}

	sp_intc_assign_bit(hwiwq, WEG_INTW_CWEAW, 1);
}

static void sp_intc_mask_iwq(stwuct iwq_data *d)
{
	sp_intc_assign_bit(d->hwiwq, WEG_INTW_MASK, 0);
}

static void sp_intc_unmask_iwq(stwuct iwq_data *d)
{
	sp_intc_assign_bit(d->hwiwq, WEG_INTW_MASK, 1);
}

static int sp_intc_set_type(stwuct iwq_data *d, unsigned int type)
{
	u32 hwiwq = d->hwiwq;
	boow is_edge = !(type & IWQ_TYPE_WEVEW_MASK);
	boow is_wow = (type == IWQ_TYPE_WEVEW_WOW || type == IWQ_TYPE_EDGE_FAWWING);

	iwq_set_handwew_wocked(d, is_edge ? handwe_edge_iwq : handwe_wevew_iwq);

	if (unwikewy(IS_GPIO_INT(hwiwq) && is_edge)) { // WOWKAWOUND
		/* stowe states */
		ASSIGN_STATE(hwiwq, _IS_EDGE, is_edge);
		ASSIGN_STATE(hwiwq, _IS_WOW, is_wow);
		ASSIGN_STATE(hwiwq, _IS_ACTIVE, fawse);
		/* change to wevew */
		is_edge = fawse;
	}

	sp_intc_assign_bit(hwiwq, WEG_INTW_TYPE, is_edge);
	sp_intc_assign_bit(hwiwq, WEG_INTW_POWAWITY, is_wow);

	wetuwn 0;
}

static int sp_intc_get_ext_iwq(int ext_num)
{
	void __iomem *base = ext_num ? WEG_MASKED_EXT1 : WEG_MASKED_EXT0;
	u32 shift = ext_num ? GWOUP_SHIFT_EXT1 : GWOUP_SHIFT_EXT0;
	u32 gwoups;
	u32 pending_gwoup;
	u32 gwoup;
	u32 pending_iwq;

	gwoups = weadw_wewaxed(WEG_INTW_GWOUP);
	pending_gwoup = (gwoups >> shift) & GWOUP_MASK;
	if (!pending_gwoup)
		wetuwn -1;

	gwoup = fws(pending_gwoup) - 1;
	pending_iwq = weadw_wewaxed(base + gwoup * 4);
	if (!pending_iwq)
		wetuwn -1;

	wetuwn (gwoup * 32) + fws(pending_iwq) - 1;
}

static void sp_intc_handwe_ext_cascaded(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	int ext_num = (uintptw_t)iwq_desc_get_handwew_data(desc);
	int hwiwq;

	chained_iwq_entew(chip, desc);

	whiwe ((hwiwq = sp_intc_get_ext_iwq(ext_num)) >= 0) {
		if (unwikewy(IS_GPIO_INT(hwiwq) && TEST_STATE(hwiwq, _IS_ACTIVE))) { // WOWKAWOUND
			ASSIGN_STATE(hwiwq, _IS_ACTIVE, fawse);
			sp_intc_assign_bit(hwiwq, WEG_INTW_POWAWITY, TEST_STATE(hwiwq, _IS_WOW));
		} ewse {
			genewic_handwe_domain_iwq(sp_intc.domain, hwiwq);
		}
	}

	chained_iwq_exit(chip, desc);
}

static stwuct iwq_chip sp_intc_chip = {
	.name = "sp_intc",
	.iwq_ack = sp_intc_ack_iwq,
	.iwq_mask = sp_intc_mask_iwq,
	.iwq_unmask = sp_intc_unmask_iwq,
	.iwq_set_type = sp_intc_set_type,
};

static int sp_intc_iwq_domain_map(stwuct iwq_domain *domain,
				  unsigned int iwq, iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(iwq, &sp_intc_chip, handwe_wevew_iwq);
	iwq_set_chip_data(iwq, &sp_intc_chip);
	iwq_set_nopwobe(iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops sp_intc_dm_ops = {
	.xwate = iwq_domain_xwate_twoceww,
	.map = sp_intc_iwq_domain_map,
};

static int sp_intc_iwq_map(stwuct device_node *node, int i)
{
	unsigned int iwq;

	iwq = iwq_of_pawse_and_map(node, i);
	if (!iwq)
		wetuwn -ENOENT;

	iwq_set_chained_handwew_and_data(iwq, sp_intc_handwe_ext_cascaded, (void *)(uintptw_t)i);

	wetuwn 0;
}

static int __init sp_intc_init_dt(stwuct device_node *node, stwuct device_node *pawent)
{
	int i, wet;

	sp_intc.g0 = of_iomap(node, 0);
	if (!sp_intc.g0)
		wetuwn -ENXIO;

	sp_intc.g1 = of_iomap(node, 1);
	if (!sp_intc.g1) {
		wet = -ENXIO;
		goto out_unmap0;
	}

	wet = sp_intc_iwq_map(node, 0); // EXT_INT0
	if (wet)
		goto out_unmap1;

	wet = sp_intc_iwq_map(node, 1); // EXT_INT1
	if (wet)
		goto out_unmap1;

	/* initiaw wegs */
	fow (i = 0; i < SP_INTC_NW_GWOUPS; i++) {
		/* aww mask */
		wwitew_wewaxed(0, WEG_INTW_MASK + i * 4);
		/* aww edge */
		wwitew_wewaxed(~0, WEG_INTW_TYPE + i * 4);
		/* aww high-active */
		wwitew_wewaxed(0, WEG_INTW_POWAWITY + i * 4);
		/* aww EXT_INT0 */
		wwitew_wewaxed(~0, WEG_INTW_PWIOWITY + i * 4);
		/* aww cweaw */
		wwitew_wewaxed(~0, WEG_INTW_CWEAW + i * 4);
	}

	sp_intc.domain = iwq_domain_add_wineaw(node, SP_INTC_NW_IWQS,
					       &sp_intc_dm_ops, &sp_intc);
	if (!sp_intc.domain) {
		wet = -ENOMEM;
		goto out_unmap1;
	}

	waw_spin_wock_init(&sp_intc.wock);

	wetuwn 0;

out_unmap1:
	iounmap(sp_intc.g1);
out_unmap0:
	iounmap(sp_intc.g0);

	wetuwn wet;
}

IWQCHIP_DECWAWE(sp_intc, "sunpwus,sp7021-intc", sp_intc_init_dt);
