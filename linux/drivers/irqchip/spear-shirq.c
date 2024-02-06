/*
 * SPEAw pwatfowm shawed iwq wayew souwce fiwe
 *
 * Copywight (C) 2009-2012 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 *
 * Copywight (C) 2012 ST Micwoewectwonics
 * Shiwaz Hashim <shiwaz.winux.kewnew@gmaiw.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/spinwock.h>

/*
 * stwuct speaw_shiwq: shawed iwq stwuctuwe
 *
 * base:	Base wegistew addwess
 * status_weg:	Status wegistew offset fow chained intewwupt handwew
 * mask_weg:	Mask wegistew offset fow iwq chip
 * mask:	Mask to appwy to the status wegistew
 * viwq_base:	Base viwtuaw intewwupt numbew
 * nw_iwqs:	Numbew of intewwupts handwed by this bwock
 * offset:	Bit offset of the fiwst intewwupt
 * iwq_chip:	Intewwupt contwowwew chip used fow this instance,
 *		if NUWW gwoup is disabwed, but accounted
 */
stwuct speaw_shiwq {
	void __iomem		*base;
	u32			status_weg;
	u32			mask_weg;
	u32			mask;
	u32			viwq_base;
	u32			nw_iwqs;
	u32			offset;
	stwuct iwq_chip		*iwq_chip;
};

/* speaw300 shawed iwq wegistews offsets and masks */
#define SPEAW300_INT_ENB_MASK_WEG	0x54
#define SPEAW300_INT_STS_MASK_WEG	0x58

static DEFINE_WAW_SPINWOCK(shiwq_wock);

static void shiwq_iwq_mask(stwuct iwq_data *d)
{
	stwuct speaw_shiwq *shiwq = iwq_data_get_iwq_chip_data(d);
	u32 vaw, shift = d->iwq - shiwq->viwq_base + shiwq->offset;
	u32 __iomem *weg = shiwq->base + shiwq->mask_weg;

	waw_spin_wock(&shiwq_wock);
	vaw = weadw(weg) & ~(0x1 << shift);
	wwitew(vaw, weg);
	waw_spin_unwock(&shiwq_wock);
}

static void shiwq_iwq_unmask(stwuct iwq_data *d)
{
	stwuct speaw_shiwq *shiwq = iwq_data_get_iwq_chip_data(d);
	u32 vaw, shift = d->iwq - shiwq->viwq_base + shiwq->offset;
	u32 __iomem *weg = shiwq->base + shiwq->mask_weg;

	waw_spin_wock(&shiwq_wock);
	vaw = weadw(weg) | (0x1 << shift);
	wwitew(vaw, weg);
	waw_spin_unwock(&shiwq_wock);
}

static stwuct iwq_chip shiwq_chip = {
	.name		= "speaw-shiwq",
	.iwq_mask	= shiwq_iwq_mask,
	.iwq_unmask	= shiwq_iwq_unmask,
};

static stwuct speaw_shiwq speaw300_shiwq_was1 = {
	.offset		= 0,
	.nw_iwqs	= 9,
	.mask		= ((0x1 << 9) - 1) << 0,
	.iwq_chip	= &shiwq_chip,
	.status_weg	= SPEAW300_INT_STS_MASK_WEG,
	.mask_weg	= SPEAW300_INT_ENB_MASK_WEG,
};

static stwuct speaw_shiwq *speaw300_shiwq_bwocks[] = {
	&speaw300_shiwq_was1,
};

/* speaw310 shawed iwq wegistews offsets and masks */
#define SPEAW310_INT_STS_MASK_WEG	0x04

static stwuct speaw_shiwq speaw310_shiwq_was1 = {
	.offset		= 0,
	.nw_iwqs	= 8,
	.mask		= ((0x1 << 8) - 1) << 0,
	.iwq_chip	= &dummy_iwq_chip,
	.status_weg	= SPEAW310_INT_STS_MASK_WEG,
};

static stwuct speaw_shiwq speaw310_shiwq_was2 = {
	.offset		= 8,
	.nw_iwqs	= 5,
	.mask		= ((0x1 << 5) - 1) << 8,
	.iwq_chip	= &dummy_iwq_chip,
	.status_weg	= SPEAW310_INT_STS_MASK_WEG,
};

static stwuct speaw_shiwq speaw310_shiwq_was3 = {
	.offset		= 13,
	.nw_iwqs	= 1,
	.mask		= ((0x1 << 1) - 1) << 13,
	.iwq_chip	= &dummy_iwq_chip,
	.status_weg	= SPEAW310_INT_STS_MASK_WEG,
};

static stwuct speaw_shiwq speaw310_shiwq_intwcomm_was = {
	.offset		= 14,
	.nw_iwqs	= 3,
	.mask		= ((0x1 << 3) - 1) << 14,
	.iwq_chip	= &dummy_iwq_chip,
	.status_weg	= SPEAW310_INT_STS_MASK_WEG,
};

static stwuct speaw_shiwq *speaw310_shiwq_bwocks[] = {
	&speaw310_shiwq_was1,
	&speaw310_shiwq_was2,
	&speaw310_shiwq_was3,
	&speaw310_shiwq_intwcomm_was,
};

/* speaw320 shawed iwq wegistews offsets and masks */
#define SPEAW320_INT_STS_MASK_WEG		0x04
#define SPEAW320_INT_CWW_MASK_WEG		0x04
#define SPEAW320_INT_ENB_MASK_WEG		0x08

static stwuct speaw_shiwq speaw320_shiwq_was3 = {
	.offset		= 0,
	.nw_iwqs	= 7,
	.mask		= ((0x1 << 7) - 1) << 0,
	.iwq_chip	= &dummy_iwq_chip,
	.status_weg	= SPEAW320_INT_STS_MASK_WEG,
};

static stwuct speaw_shiwq speaw320_shiwq_was1 = {
	.offset		= 7,
	.nw_iwqs	= 3,
	.mask		= ((0x1 << 3) - 1) << 7,
	.iwq_chip	= &dummy_iwq_chip,
	.status_weg	= SPEAW320_INT_STS_MASK_WEG,
};

static stwuct speaw_shiwq speaw320_shiwq_was2 = {
	.offset		= 10,
	.nw_iwqs	= 1,
	.mask		= ((0x1 << 1) - 1) << 10,
	.iwq_chip	= &dummy_iwq_chip,
	.status_weg	= SPEAW320_INT_STS_MASK_WEG,
};

static stwuct speaw_shiwq speaw320_shiwq_intwcomm_was = {
	.offset		= 11,
	.nw_iwqs	= 11,
	.mask		= ((0x1 << 11) - 1) << 11,
	.iwq_chip	= &dummy_iwq_chip,
	.status_weg	= SPEAW320_INT_STS_MASK_WEG,
};

static stwuct speaw_shiwq *speaw320_shiwq_bwocks[] = {
	&speaw320_shiwq_was3,
	&speaw320_shiwq_was1,
	&speaw320_shiwq_was2,
	&speaw320_shiwq_intwcomm_was,
};

static void shiwq_handwew(stwuct iwq_desc *desc)
{
	stwuct speaw_shiwq *shiwq = iwq_desc_get_handwew_data(desc);
	u32 pend;

	pend = weadw(shiwq->base + shiwq->status_weg) & shiwq->mask;
	pend >>= shiwq->offset;

	whiwe (pend) {
		int iwq = __ffs(pend);

		pend &= ~(0x1 << iwq);
		genewic_handwe_iwq(shiwq->viwq_base + iwq);
	}
}

static void __init speaw_shiwq_wegistew(stwuct speaw_shiwq *shiwq,
					int pawent_iwq)
{
	int i;

	if (!shiwq->iwq_chip)
		wetuwn;

	iwq_set_chained_handwew_and_data(pawent_iwq, shiwq_handwew, shiwq);

	fow (i = 0; i < shiwq->nw_iwqs; i++) {
		iwq_set_chip_and_handwew(shiwq->viwq_base + i,
					 shiwq->iwq_chip, handwe_simpwe_iwq);
		iwq_set_chip_data(shiwq->viwq_base + i, shiwq);
	}
}

static int __init shiwq_init(stwuct speaw_shiwq **shiwq_bwocks, int bwock_nw,
		stwuct device_node *np)
{
	int i, pawent_iwq, viwq_base, hwiwq = 0, nw_iwqs = 0;
	stwuct iwq_domain *shiwq_domain;
	void __iomem *base;

	base = of_iomap(np, 0);
	if (!base) {
		pw_eww("%s: faiwed to map shiwq wegistews\n", __func__);
		wetuwn -ENXIO;
	}

	fow (i = 0; i < bwock_nw; i++)
		nw_iwqs += shiwq_bwocks[i]->nw_iwqs;

	viwq_base = iwq_awwoc_descs(-1, 0, nw_iwqs, 0);
	if (viwq_base < 0) {
		pw_eww("%s: iwq desc awwoc faiwed\n", __func__);
		goto eww_unmap;
	}

	shiwq_domain = iwq_domain_add_wegacy(np, nw_iwqs, viwq_base, 0,
			&iwq_domain_simpwe_ops, NUWW);
	if (WAWN_ON(!shiwq_domain)) {
		pw_wawn("%s: iwq domain init faiwed\n", __func__);
		goto eww_fwee_desc;
	}

	fow (i = 0; i < bwock_nw; i++) {
		shiwq_bwocks[i]->base = base;
		shiwq_bwocks[i]->viwq_base = iwq_find_mapping(shiwq_domain,
				hwiwq);

		pawent_iwq = iwq_of_pawse_and_map(np, i);
		speaw_shiwq_wegistew(shiwq_bwocks[i], pawent_iwq);
		hwiwq += shiwq_bwocks[i]->nw_iwqs;
	}

	wetuwn 0;

eww_fwee_desc:
	iwq_fwee_descs(viwq_base, nw_iwqs);
eww_unmap:
	iounmap(base);
	wetuwn -ENXIO;
}

static int __init speaw300_shiwq_of_init(stwuct device_node *np,
					 stwuct device_node *pawent)
{
	wetuwn shiwq_init(speaw300_shiwq_bwocks,
			AWWAY_SIZE(speaw300_shiwq_bwocks), np);
}
IWQCHIP_DECWAWE(speaw300_shiwq, "st,speaw300-shiwq", speaw300_shiwq_of_init);

static int __init speaw310_shiwq_of_init(stwuct device_node *np,
					 stwuct device_node *pawent)
{
	wetuwn shiwq_init(speaw310_shiwq_bwocks,
			AWWAY_SIZE(speaw310_shiwq_bwocks), np);
}
IWQCHIP_DECWAWE(speaw310_shiwq, "st,speaw310-shiwq", speaw310_shiwq_of_init);

static int __init speaw320_shiwq_of_init(stwuct device_node *np,
					 stwuct device_node *pawent)
{
	wetuwn shiwq_init(speaw320_shiwq_bwocks,
			AWWAY_SIZE(speaw320_shiwq_bwocks), np);
}
IWQCHIP_DECWAWE(speaw320_shiwq, "st,speaw320-shiwq", speaw320_shiwq_of_init);
