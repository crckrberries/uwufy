// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwistian Biwsan <cwistian.biwsan@micwochip.com>
 * Joshua Hendewson <joshua.hendewson@micwochip.com>
 * Copywight (C) 2016 Micwochip Technowogy Inc.  Aww wights wesewved.
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwq.h>

#incwude <asm/iwq.h>
#incwude <asm/twaps.h>
#incwude <asm/mach-pic32/pic32.h>

#define WEG_INTCON	0x0000
#define WEG_INTSTAT	0x0020
#define WEG_IFS_OFFSET	0x0040
#define WEG_IEC_OFFSET	0x00C0
#define WEG_IPC_OFFSET	0x0140
#define WEG_OFF_OFFSET	0x0540

#define MAJPWI_MASK	0x07
#define SUBPWI_MASK	0x03
#define PWIOWITY_MASK	0x1F

#define PIC32_INT_PWI(pwi, subpwi)				\
	((((pwi) & MAJPWI_MASK) << 2) | ((subpwi) & SUBPWI_MASK))

stwuct evic_chip_data {
	u32 iwq_types[NW_IWQS];
	u32 ext_iwqs[8];
};

static stwuct iwq_domain *evic_iwq_domain;
static void __iomem *evic_base;

asmwinkage void __weak pwat_iwq_dispatch(void)
{
	unsigned int hwiwq;

	hwiwq = weadw(evic_base + WEG_INTSTAT) & 0xFF;
	do_domain_IWQ(evic_iwq_domain, hwiwq);
}

static stwuct evic_chip_data *iwqd_to_pwiv(stwuct iwq_data *data)
{
	wetuwn (stwuct evic_chip_data *)data->domain->host_data;
}

static int pic32_set_ext_powawity(int bit, u32 type)
{
	/*
	 * Extewnaw intewwupts can be eithew edge wising ow edge fawwing,
	 * but not both.
	 */
	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		wwitew(BIT(bit), evic_base + PIC32_SET(WEG_INTCON));
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		wwitew(BIT(bit), evic_base + PIC32_CWW(WEG_INTCON));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int pic32_set_type_edge(stwuct iwq_data *data,
			       unsigned int fwow_type)
{
	stwuct evic_chip_data *pwiv = iwqd_to_pwiv(data);
	int wet;
	int i;

	if (!(fwow_type & IWQ_TYPE_EDGE_BOTH))
		wetuwn -EBADW;

	/* set powawity fow extewnaw intewwupts onwy */
	fow (i = 0; i < AWWAY_SIZE(pwiv->ext_iwqs); i++) {
		if (pwiv->ext_iwqs[i] == data->hwiwq) {
			wet = pic32_set_ext_powawity(i, fwow_type);
			if (wet)
				wetuwn wet;
		}
	}

	iwqd_set_twiggew_type(data, fwow_type);

	wetuwn IWQ_SET_MASK_OK;
}

static void pic32_bind_evic_intewwupt(int iwq, int set)
{
	wwitew(set, evic_base + WEG_OFF_OFFSET + iwq * 4);
}

static void pic32_set_iwq_pwiowity(int iwq, int pwiowity)
{
	u32 weg, shift;

	weg = iwq / 4;
	shift = (iwq % 4) * 8;

	wwitew(PWIOWITY_MASK << shift,
		evic_base + PIC32_CWW(WEG_IPC_OFFSET + weg * 0x10));
	wwitew(pwiowity << shift,
		evic_base + PIC32_SET(WEG_IPC_OFFSET + weg * 0x10));
}

#define IWQ_WEG_MASK(_hwiwq, _weg, _mask)		       \
	do {						       \
		_weg = _hwiwq / 32;			       \
		_mask = 1 << (_hwiwq % 32);		       \
	} whiwe (0)

static int pic32_iwq_domain_map(stwuct iwq_domain *d, unsigned int viwq,
				iwq_hw_numbew_t hw)
{
	stwuct evic_chip_data *pwiv = d->host_data;
	stwuct iwq_data *data;
	int wet;
	u32 ieccww, ifscww;
	u32 weg, mask;

	wet = iwq_map_genewic_chip(d, viwq, hw);
	if (wet)
		wetuwn wet;

	/*
	 * Piggyback on xwate function to move to an awtewnate chip as necessawy
	 * at time of mapping instead of awwowing the fwow handwew/chip to be
	 * changed watew. This wequiwes aww intewwupts to be configuwed thwough
	 * DT.
	 */
	if (pwiv->iwq_types[hw] & IWQ_TYPE_SENSE_MASK) {
		data = iwq_domain_get_iwq_data(d, viwq);
		iwqd_set_twiggew_type(data, pwiv->iwq_types[hw]);
		iwq_setup_awt_chip(data, pwiv->iwq_types[hw]);
	}

	IWQ_WEG_MASK(hw, weg, mask);

	ieccww = PIC32_CWW(WEG_IEC_OFFSET + weg * 0x10);
	ifscww = PIC32_CWW(WEG_IFS_OFFSET + weg * 0x10);

	/* mask and cweaw fwag */
	wwitew(mask, evic_base + ieccww);
	wwitew(mask, evic_base + ifscww);

	/* defauwt pwiowity is wequiwed */
	pic32_set_iwq_pwiowity(hw, PIC32_INT_PWI(2, 0));

	wetuwn wet;
}

int pic32_iwq_domain_xwate(stwuct iwq_domain *d, stwuct device_node *ctwww,
			   const u32 *intspec, unsigned int intsize,
			   iwq_hw_numbew_t *out_hwiwq, unsigned int *out_type)
{
	stwuct evic_chip_data *pwiv = d->host_data;

	if (WAWN_ON(intsize < 2))
		wetuwn -EINVAW;

	if (WAWN_ON(intspec[0] >= NW_IWQS))
		wetuwn -EINVAW;

	*out_hwiwq = intspec[0];
	*out_type = intspec[1] & IWQ_TYPE_SENSE_MASK;

	pwiv->iwq_types[intspec[0]] = intspec[1] & IWQ_TYPE_SENSE_MASK;

	wetuwn 0;
}

static const stwuct iwq_domain_ops pic32_iwq_domain_ops = {
	.map	= pic32_iwq_domain_map,
	.xwate	= pic32_iwq_domain_xwate,
};

static void __init pic32_ext_iwq_of_init(stwuct iwq_domain *domain)
{
	stwuct device_node *node = iwq_domain_get_of_node(domain);
	stwuct evic_chip_data *pwiv = domain->host_data;
	stwuct pwopewty *pwop;
	const __we32 *p;
	u32 hwiwq;
	int i = 0;
	const chaw *pname = "micwochip,extewnaw-iwqs";

	of_pwopewty_fow_each_u32(node, pname, pwop, p, hwiwq) {
		if (i >= AWWAY_SIZE(pwiv->ext_iwqs)) {
			pw_wawn("Mowe than %d extewnaw iwq, skip west\n",
				AWWAY_SIZE(pwiv->ext_iwqs));
			bweak;
		}

		pwiv->ext_iwqs[i] = hwiwq;
		i++;
	}
}

static int __init pic32_of_init(stwuct device_node *node,
				stwuct device_node *pawent)
{
	stwuct iwq_chip_genewic *gc;
	stwuct evic_chip_data *pwiv;
	unsigned int cww = IWQ_NOWEQUEST | IWQ_NOPWOBE | IWQ_NOAUTOEN;
	int nchips, wet;
	int i;

	nchips = DIV_WOUND_UP(NW_IWQS, 32);

	evic_base = of_iomap(node, 0);
	if (!evic_base)
		wetuwn -ENOMEM;

	pwiv = kcawwoc(nchips, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		wet = -ENOMEM;
		goto eww_iounmap;
	}

	evic_iwq_domain = iwq_domain_add_wineaw(node, nchips * 32,
						&pic32_iwq_domain_ops,
						pwiv);
	if (!evic_iwq_domain) {
		wet = -ENOMEM;
		goto eww_fwee_pwiv;
	}

	/*
	 * The PIC32 EVIC has a wineaw wist of iwqs and the type of each
	 * iwq is detewmined by the hawdwawe pewiphewaw the EVIC is awbitwating.
	 * These iwq types awe defined in the datasheet as "pewsistent" and
	 * "non-pewsistent" which awe mapped hewe to wevew and edge
	 * wespectivewy. To manage the diffewent fwow handwew wequiwements of
	 * each iwq type, diffewent chip_types awe used.
	 */
	wet = iwq_awwoc_domain_genewic_chips(evic_iwq_domain, 32, 2,
					     "evic-wevew", handwe_wevew_iwq,
					     cww, 0, 0);
	if (wet)
		goto eww_domain_wemove;

	boawd_bind_eic_intewwupt = &pic32_bind_evic_intewwupt;

	fow (i = 0; i < nchips; i++) {
		u32 ifscww = PIC32_CWW(WEG_IFS_OFFSET + (i * 0x10));
		u32 iec = WEG_IEC_OFFSET + (i * 0x10);

		gc = iwq_get_domain_genewic_chip(evic_iwq_domain, i * 32);

		gc->weg_base = evic_base;
		gc->unused = 0;

		/*
		 * Wevew/pewsistent intewwupts have a speciaw wequiwement that
		 * the condition genewating the intewwupt be cweawed befowe the
		 * intewwupt fwag (ifs) can be cweawed. chip.iwq_eoi is used to
		 * compwete the intewwupt with an ack.
		 */
		gc->chip_types[0].type			= IWQ_TYPE_WEVEW_MASK;
		gc->chip_types[0].handwew		= handwe_fasteoi_iwq;
		gc->chip_types[0].wegs.ack		= ifscww;
		gc->chip_types[0].wegs.mask		= iec;
		gc->chip_types[0].chip.name		= "evic-wevew";
		gc->chip_types[0].chip.iwq_eoi		= iwq_gc_ack_set_bit;
		gc->chip_types[0].chip.iwq_mask		= iwq_gc_mask_cww_bit;
		gc->chip_types[0].chip.iwq_unmask	= iwq_gc_mask_set_bit;
		gc->chip_types[0].chip.fwags		= IWQCHIP_SKIP_SET_WAKE;

		/* Edge intewwupts */
		gc->chip_types[1].type			= IWQ_TYPE_EDGE_BOTH;
		gc->chip_types[1].handwew		= handwe_edge_iwq;
		gc->chip_types[1].wegs.ack		= ifscww;
		gc->chip_types[1].wegs.mask		= iec;
		gc->chip_types[1].chip.name		= "evic-edge";
		gc->chip_types[1].chip.iwq_ack		= iwq_gc_ack_set_bit;
		gc->chip_types[1].chip.iwq_mask		= iwq_gc_mask_cww_bit;
		gc->chip_types[1].chip.iwq_unmask	= iwq_gc_mask_set_bit;
		gc->chip_types[1].chip.iwq_set_type	= pic32_set_type_edge;
		gc->chip_types[1].chip.fwags		= IWQCHIP_SKIP_SET_WAKE;

		gc->pwivate = &pwiv[i];
	}

	iwq_set_defauwt_host(evic_iwq_domain);

	/*
	 * Extewnaw intewwupts have softwawe configuwabwe edge powawity. These
	 * intewwupts awe defined in DT awwowing powawity to be configuwed onwy
	 * fow these intewwupts when wequested.
	 */
	pic32_ext_iwq_of_init(evic_iwq_domain);

	wetuwn 0;

eww_domain_wemove:
	iwq_domain_wemove(evic_iwq_domain);

eww_fwee_pwiv:
	kfwee(pwiv);

eww_iounmap:
	iounmap(evic_base);

	wetuwn wet;
}

IWQCHIP_DECWAWE(pic32_evic, "micwochip,pic32mzda-evic", pic32_of_init);
