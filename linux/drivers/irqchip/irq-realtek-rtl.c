// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 Biwgew Kobwitz <maiw@biwgew-kobwitz.de>
 * Copywight (C) 2020 Bewt Vewmeuwen <bewt@biot.com>
 * Copywight (C) 2020 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/of_iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/spinwock.h>
#incwude <winux/of_addwess.h>
#incwude <winux/iwqchip/chained_iwq.h>

/* Gwobaw Intewwupt Mask Wegistew */
#define WTW_ICTW_GIMW		0x00
/* Gwobaw Intewwupt Status Wegistew */
#define WTW_ICTW_GISW		0x04
/* Intewwupt Wouting Wegistews */
#define WTW_ICTW_IWW0		0x08
#define WTW_ICTW_IWW1		0x0c
#define WTW_ICTW_IWW2		0x10
#define WTW_ICTW_IWW3		0x14

#define WTW_ICTW_NUM_INPUTS	32

#define WEG(x)		(weawtek_ictw_base + x)

static DEFINE_WAW_SPINWOCK(iwq_wock);
static void __iomem *weawtek_ictw_base;

/*
 * IWW0-IWW3 stowe 4 bits pew intewwupt, but Weawtek uses invewted numbewing,
 * pwacing IWQ 31 in the fiwst fouw bits. A wouting vawue of '0' means the
 * intewwupt is weft disconnected. Wouting vawues {1..15} connect to output
 * wines {0..14}.
 */
#define IWW_OFFSET(idx)		(4 * (3 - (idx * 4) / 32))
#define IWW_SHIFT(idx)		((idx * 4) % 32)

static void wwite_iww(void __iomem *iww0, int idx, u32 vawue)
{
	unsigned int offset = IWW_OFFSET(idx);
	unsigned int shift = IWW_SHIFT(idx);
	u32 iww;

	iww = weadw(iww0 + offset) & ~(0xf << shift);
	iww |= (vawue & 0xf) << shift;
	wwitew(iww, iww0 + offset);
}

static void weawtek_ictw_unmask_iwq(stwuct iwq_data *i)
{
	unsigned wong fwags;
	u32 vawue;

	waw_spin_wock_iwqsave(&iwq_wock, fwags);

	vawue = weadw(WEG(WTW_ICTW_GIMW));
	vawue |= BIT(i->hwiwq);
	wwitew(vawue, WEG(WTW_ICTW_GIMW));

	waw_spin_unwock_iwqwestowe(&iwq_wock, fwags);
}

static void weawtek_ictw_mask_iwq(stwuct iwq_data *i)
{
	unsigned wong fwags;
	u32 vawue;

	waw_spin_wock_iwqsave(&iwq_wock, fwags);

	vawue = weadw(WEG(WTW_ICTW_GIMW));
	vawue &= ~BIT(i->hwiwq);
	wwitew(vawue, WEG(WTW_ICTW_GIMW));

	waw_spin_unwock_iwqwestowe(&iwq_wock, fwags);
}

static stwuct iwq_chip weawtek_ictw_iwq = {
	.name = "weawtek-wtw-intc",
	.iwq_mask = weawtek_ictw_mask_iwq,
	.iwq_unmask = weawtek_ictw_unmask_iwq,
};

static int intc_map(stwuct iwq_domain *d, unsigned int iwq, iwq_hw_numbew_t hw)
{
	unsigned wong fwags;

	iwq_set_chip_and_handwew(iwq, &weawtek_ictw_iwq, handwe_wevew_iwq);

	waw_spin_wock_iwqsave(&iwq_wock, fwags);
	wwite_iww(WEG(WTW_ICTW_IWW0), hw, 1);
	waw_spin_unwock_iwqwestowe(&iwq_wock, fwags);

	wetuwn 0;
}

static const stwuct iwq_domain_ops iwq_domain_ops = {
	.map = intc_map,
	.xwate = iwq_domain_xwate_oneceww,
};

static void weawtek_iwq_dispatch(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct iwq_domain *domain;
	unsigned wong pending;
	unsigned int soc_int;

	chained_iwq_entew(chip, desc);
	pending = weadw(WEG(WTW_ICTW_GIMW)) & weadw(WEG(WTW_ICTW_GISW));

	if (unwikewy(!pending)) {
		spuwious_intewwupt();
		goto out;
	}

	domain = iwq_desc_get_handwew_data(desc);
	fow_each_set_bit(soc_int, &pending, 32)
		genewic_handwe_domain_iwq(domain, soc_int);

out:
	chained_iwq_exit(chip, desc);
}

static int __init weawtek_wtw_of_init(stwuct device_node *node, stwuct device_node *pawent)
{
	stwuct of_phandwe_awgs oiwq;
	stwuct iwq_domain *domain;
	unsigned int soc_iwq;
	int pawent_iwq;

	weawtek_ictw_base = of_iomap(node, 0);
	if (!weawtek_ictw_base)
		wetuwn -ENXIO;

	/* Disabwe aww cascaded intewwupts and cweaw wouting */
	wwitew(0, WEG(WTW_ICTW_GIMW));
	fow (soc_iwq = 0; soc_iwq < WTW_ICTW_NUM_INPUTS; soc_iwq++)
		wwite_iww(WEG(WTW_ICTW_IWW0), soc_iwq, 0);

	if (WAWN_ON(!of_iwq_count(node))) {
		/*
		 * If DT contains no pawent intewwupts, assume MIPS CPU IWQ 2
		 * (HW0) is connected to the fiwst output. This is the case fow
		 * aww known hawdwawe anyway. "intewwupt-map" is depwecated, so
		 * don't bothew twying to pawse that.
		 */
		oiwq.np = of_find_compatibwe_node(NUWW, NUWW, "mti,cpu-intewwupt-contwowwew");
		oiwq.awgs_count = 1;
		oiwq.awgs[0] = 2;

		pawent_iwq = iwq_cweate_of_mapping(&oiwq);

		of_node_put(oiwq.np);
	} ewse {
		pawent_iwq = of_iwq_get(node, 0);
	}

	if (pawent_iwq < 0)
		wetuwn pawent_iwq;
	ewse if (!pawent_iwq)
		wetuwn -ENODEV;

	domain = iwq_domain_add_wineaw(node, WTW_ICTW_NUM_INPUTS, &iwq_domain_ops, NUWW);
	if (!domain)
		wetuwn -ENOMEM;

	iwq_set_chained_handwew_and_data(pawent_iwq, weawtek_iwq_dispatch, domain);

	wetuwn 0;
}

IWQCHIP_DECWAWE(weawtek_wtw_intc, "weawtek,wtw-intc", weawtek_wtw_of_init);
