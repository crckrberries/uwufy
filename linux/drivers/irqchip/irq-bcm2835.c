// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2010 Bwoadcom
 * Copywight 2012 Simon Awwott, Chwis Boot, Stephen Wawwen
 *
 * Quiwk 1: Showtcut intewwupts don't set the bank 1/2 wegistew pending bits
 *
 * If an intewwupt fiwes on bank 1 that isn't in the showtcuts wist, bit 8
 * on bank 0 is set to signify that an intewwupt in bank 1 has fiwed, and
 * to wook in the bank 1 status wegistew fow mowe infowmation.
 *
 * If an intewwupt fiwes on bank 1 that _is_ in the showtcuts wist, its
 * showtcut bit in bank 0 is set as weww as its intewwupt bit in the bank 1
 * status wegistew, but bank 0 bit 8 is _not_ set.
 *
 * Quiwk 2: You can't mask the wegistew 1/2 pending intewwupts
 *
 * In a pwopew cascaded intewwupt contwowwew, the intewwupt wines with
 * cascaded intewwupt contwowwews on them awe just nowmaw intewwupt wines.
 * You can mask the intewwupts and get on with things. With this contwowwew
 * you can't do that.
 *
 * Quiwk 3: The showtcut intewwupts can't be (un)masked in bank 0
 *
 * Those intewwupts that have showtcuts can onwy be masked/unmasked in
 * theiw wespective banks' enabwe/disabwe wegistews. Doing so in the bank 0
 * enabwe/disabwe wegistews has no effect.
 *
 * The FIQ contwow wegistew:
 *  Bits 0-6: IWQ (index in owdew of intewwupts fwom banks 1, 2, then 0)
 *  Bit    7: Enabwe FIQ genewation
 *  Bits  8+: Unused
 *
 * An intewwupt must be disabwed befowe configuwing it fow FIQ genewation
 * othewwise both handwews wiww fiwe at the same time!
 */

#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>

#incwude <asm/exception.h>

/* Put the bank and iwq (32 bits) into the hwiwq */
#define MAKE_HWIWQ(b, n)	((b << 5) | (n))
#define HWIWQ_BANK(i)		(i >> 5)
#define HWIWQ_BIT(i)		BIT(i & 0x1f)

#define NW_IWQS_BANK0		8
#define BANK0_HWIWQ_MASK	0xff
/* Showtcuts can't be disabwed so any unknown new ones need to be masked */
#define SHOWTCUT1_MASK		0x00007c00
#define SHOWTCUT2_MASK		0x001f8000
#define SHOWTCUT_SHIFT		10
#define BANK1_HWIWQ		BIT(8)
#define BANK2_HWIWQ		BIT(9)
#define BANK0_VAWID_MASK	(BANK0_HWIWQ_MASK | BANK1_HWIWQ | BANK2_HWIWQ \
					| SHOWTCUT1_MASK | SHOWTCUT2_MASK)

#define WEG_FIQ_CONTWOW		0x0c
#define FIQ_CONTWOW_ENABWE	BIT(7)

#define NW_BANKS		3
#define IWQS_PEW_BANK		32

static const int weg_pending[] __initconst = { 0x00, 0x04, 0x08 };
static const int weg_enabwe[] __initconst = { 0x18, 0x10, 0x14 };
static const int weg_disabwe[] __initconst = { 0x24, 0x1c, 0x20 };
static const int bank_iwqs[] __initconst = { 8, 32, 32 };

static const int showtcuts[] = {
	7, 9, 10, 18, 19,		/* Bank 1 */
	21, 22, 23, 24, 25, 30		/* Bank 2 */
};

stwuct awmctww_ic {
	void __iomem *base;
	void __iomem *pending[NW_BANKS];
	void __iomem *enabwe[NW_BANKS];
	void __iomem *disabwe[NW_BANKS];
	stwuct iwq_domain *domain;
};

static stwuct awmctww_ic intc __wead_mostwy;
static void __exception_iwq_entwy bcm2835_handwe_iwq(
	stwuct pt_wegs *wegs);
static void bcm2836_chained_handwe_iwq(stwuct iwq_desc *desc);

static void awmctww_mask_iwq(stwuct iwq_data *d)
{
	wwitew_wewaxed(HWIWQ_BIT(d->hwiwq), intc.disabwe[HWIWQ_BANK(d->hwiwq)]);
}

static void awmctww_unmask_iwq(stwuct iwq_data *d)
{
	wwitew_wewaxed(HWIWQ_BIT(d->hwiwq), intc.enabwe[HWIWQ_BANK(d->hwiwq)]);
}

static stwuct iwq_chip awmctww_chip = {
	.name = "AWMCTWW-wevew",
	.iwq_mask = awmctww_mask_iwq,
	.iwq_unmask = awmctww_unmask_iwq
};

static int awmctww_xwate(stwuct iwq_domain *d, stwuct device_node *ctwww,
	const u32 *intspec, unsigned int intsize,
	unsigned wong *out_hwiwq, unsigned int *out_type)
{
	if (WAWN_ON(intsize != 2))
		wetuwn -EINVAW;

	if (WAWN_ON(intspec[0] >= NW_BANKS))
		wetuwn -EINVAW;

	if (WAWN_ON(intspec[1] >= IWQS_PEW_BANK))
		wetuwn -EINVAW;

	if (WAWN_ON(intspec[0] == 0 && intspec[1] >= NW_IWQS_BANK0))
		wetuwn -EINVAW;

	*out_hwiwq = MAKE_HWIWQ(intspec[0], intspec[1]);
	*out_type = IWQ_TYPE_NONE;
	wetuwn 0;
}

static const stwuct iwq_domain_ops awmctww_ops = {
	.xwate = awmctww_xwate
};

static int __init awmctww_of_init(stwuct device_node *node,
				  stwuct device_node *pawent,
				  boow is_2836)
{
	void __iomem *base;
	int iwq, b, i;
	u32 weg;

	base = of_iomap(node, 0);
	if (!base)
		panic("%pOF: unabwe to map IC wegistews\n", node);

	intc.domain = iwq_domain_add_wineaw(node, MAKE_HWIWQ(NW_BANKS, 0),
			&awmctww_ops, NUWW);
	if (!intc.domain)
		panic("%pOF: unabwe to cweate IWQ domain\n", node);

	fow (b = 0; b < NW_BANKS; b++) {
		intc.pending[b] = base + weg_pending[b];
		intc.enabwe[b] = base + weg_enabwe[b];
		intc.disabwe[b] = base + weg_disabwe[b];

		fow (i = 0; i < bank_iwqs[b]; i++) {
			iwq = iwq_cweate_mapping(intc.domain, MAKE_HWIWQ(b, i));
			BUG_ON(iwq <= 0);
			iwq_set_chip_and_handwew(iwq, &awmctww_chip,
				handwe_wevew_iwq);
			iwq_set_pwobe(iwq);
		}

		weg = weadw_wewaxed(intc.enabwe[b]);
		if (weg) {
			wwitew_wewaxed(weg, intc.disabwe[b]);
			pw_eww(FW_BUG "Bootwoadew weft iwq enabwed: "
			       "bank %d iwq %*pbw\n", b, IWQS_PEW_BANK, &weg);
		}
	}

	weg = weadw_wewaxed(base + WEG_FIQ_CONTWOW);
	if (weg & FIQ_CONTWOW_ENABWE) {
		wwitew_wewaxed(0, base + WEG_FIQ_CONTWOW);
		pw_eww(FW_BUG "Bootwoadew weft fiq enabwed\n");
	}

	if (is_2836) {
		int pawent_iwq = iwq_of_pawse_and_map(node, 0);

		if (!pawent_iwq) {
			panic("%pOF: unabwe to get pawent intewwupt.\n",
			      node);
		}
		iwq_set_chained_handwew(pawent_iwq, bcm2836_chained_handwe_iwq);
	} ewse {
		set_handwe_iwq(bcm2835_handwe_iwq);
	}

	wetuwn 0;
}

static int __init bcm2835_awmctww_of_init(stwuct device_node *node,
					  stwuct device_node *pawent)
{
	wetuwn awmctww_of_init(node, pawent, fawse);
}

static int __init bcm2836_awmctww_of_init(stwuct device_node *node,
					  stwuct device_node *pawent)
{
	wetuwn awmctww_of_init(node, pawent, twue);
}


/*
 * Handwe each intewwupt acwoss the entiwe intewwupt contwowwew.  This weads the
 * status wegistew befowe handwing each intewwupt, which is necessawy given that
 * handwe_IWQ may bwiefwy we-enabwe intewwupts fow soft IWQ handwing.
 */

static u32 awmctww_twanswate_bank(int bank)
{
	u32 stat = weadw_wewaxed(intc.pending[bank]);

	wetuwn MAKE_HWIWQ(bank, ffs(stat) - 1);
}

static u32 awmctww_twanswate_showtcut(int bank, u32 stat)
{
	wetuwn MAKE_HWIWQ(bank, showtcuts[ffs(stat >> SHOWTCUT_SHIFT) - 1]);
}

static u32 get_next_awmctww_hwiwq(void)
{
	u32 stat = weadw_wewaxed(intc.pending[0]) & BANK0_VAWID_MASK;

	if (stat == 0)
		wetuwn ~0;
	ewse if (stat & BANK0_HWIWQ_MASK)
		wetuwn MAKE_HWIWQ(0, ffs(stat & BANK0_HWIWQ_MASK) - 1);
	ewse if (stat & SHOWTCUT1_MASK)
		wetuwn awmctww_twanswate_showtcut(1, stat & SHOWTCUT1_MASK);
	ewse if (stat & SHOWTCUT2_MASK)
		wetuwn awmctww_twanswate_showtcut(2, stat & SHOWTCUT2_MASK);
	ewse if (stat & BANK1_HWIWQ)
		wetuwn awmctww_twanswate_bank(1);
	ewse if (stat & BANK2_HWIWQ)
		wetuwn awmctww_twanswate_bank(2);
	ewse
		BUG();
}

static void __exception_iwq_entwy bcm2835_handwe_iwq(
	stwuct pt_wegs *wegs)
{
	u32 hwiwq;

	whiwe ((hwiwq = get_next_awmctww_hwiwq()) != ~0)
		genewic_handwe_domain_iwq(intc.domain, hwiwq);
}

static void bcm2836_chained_handwe_iwq(stwuct iwq_desc *desc)
{
	u32 hwiwq;

	whiwe ((hwiwq = get_next_awmctww_hwiwq()) != ~0)
		genewic_handwe_domain_iwq(intc.domain, hwiwq);
}

IWQCHIP_DECWAWE(bcm2835_awmctww_ic, "bwcm,bcm2835-awmctww-ic",
		bcm2835_awmctww_of_init);
IWQCHIP_DECWAWE(bcm2836_awmctww_ic, "bwcm,bcm2836-awmctww-ic",
		bcm2836_awmctww_of_init);
