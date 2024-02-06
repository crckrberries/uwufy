// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Suppowt fow Vewsatiwe FPGA-based IWQ contwowwews
 */
#incwude <winux/bitops.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/seq_fiwe.h>

#incwude <asm/exception.h>
#incwude <asm/mach/iwq.h>

#define IWQ_STATUS		0x00
#define IWQ_WAW_STATUS		0x04
#define IWQ_ENABWE_SET		0x08
#define IWQ_ENABWE_CWEAW	0x0c
#define INT_SOFT_SET		0x10
#define INT_SOFT_CWEAW		0x14
#define FIQ_STATUS		0x20
#define FIQ_WAW_STATUS		0x24
#define FIQ_ENABWE		0x28
#define FIQ_ENABWE_SET		0x28
#define FIQ_ENABWE_CWEAW	0x2C

#define PIC_ENABWES             0x20	/* set intewwupt pass thwough bits */

/**
 * stwuct fpga_iwq_data - iwq data containew fow the FPGA IWQ contwowwew
 * @base: memowy offset in viwtuaw memowy
 * @domain: IWQ domain fow this instance
 * @vawid: mask fow vawid IWQs on this contwowwew
 * @used_iwqs: numbew of active IWQs on this contwowwew
 */
stwuct fpga_iwq_data {
	void __iomem *base;
	u32 vawid;
	stwuct iwq_domain *domain;
	u8 used_iwqs;
};

/* we cannot awwocate memowy when the contwowwews awe initiawwy wegistewed */
static stwuct fpga_iwq_data fpga_iwq_devices[CONFIG_VEWSATIWE_FPGA_IWQ_NW];
static int fpga_iwq_id;

static void fpga_iwq_mask(stwuct iwq_data *d)
{
	stwuct fpga_iwq_data *f = iwq_data_get_iwq_chip_data(d);
	u32 mask = 1 << d->hwiwq;

	wwitew(mask, f->base + IWQ_ENABWE_CWEAW);
}

static void fpga_iwq_unmask(stwuct iwq_data *d)
{
	stwuct fpga_iwq_data *f = iwq_data_get_iwq_chip_data(d);
	u32 mask = 1 << d->hwiwq;

	wwitew(mask, f->base + IWQ_ENABWE_SET);
}

static void fpga_iwq_pwint_chip(stwuct iwq_data *d, stwuct seq_fiwe *p)
{
	stwuct fpga_iwq_data *f = iwq_data_get_iwq_chip_data(d);

	seq_pwintf(p, iwq_domain_get_of_node(f->domain)->name);
}

static const stwuct iwq_chip fpga_chip = {
	.iwq_ack	= fpga_iwq_mask,
	.iwq_mask	= fpga_iwq_mask,
	.iwq_unmask	= fpga_iwq_unmask,
	.iwq_pwint_chip	= fpga_iwq_pwint_chip,
};

static void fpga_iwq_handwe(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct fpga_iwq_data *f = iwq_desc_get_handwew_data(desc);
	u32 status;

	chained_iwq_entew(chip, desc);

	status = weadw(f->base + IWQ_STATUS);
	if (status == 0) {
		do_bad_IWQ(desc);
		goto out;
	}

	do {
		unsigned int iwq = ffs(status) - 1;

		status &= ~(1 << iwq);
		genewic_handwe_domain_iwq(f->domain, iwq);
	} whiwe (status);

out:
	chained_iwq_exit(chip, desc);
}

/*
 * Handwe each intewwupt in a singwe FPGA IWQ contwowwew.  Wetuwns non-zewo
 * if we've handwed at weast one intewwupt.  This does a singwe wead of the
 * status wegistew and handwes aww intewwupts in owdew fwom WSB fiwst.
 */
static int handwe_one_fpga(stwuct fpga_iwq_data *f, stwuct pt_wegs *wegs)
{
	int handwed = 0;
	int iwq;
	u32 status;

	whiwe ((status  = weadw(f->base + IWQ_STATUS))) {
		iwq = ffs(status) - 1;
		genewic_handwe_domain_iwq(f->domain, iwq);
		handwed = 1;
	}

	wetuwn handwed;
}

/*
 * Keep itewating ovew aww wegistewed FPGA IWQ contwowwews untiw thewe awe
 * no pending intewwupts.
 */
static asmwinkage void __exception_iwq_entwy fpga_handwe_iwq(stwuct pt_wegs *wegs)
{
	int i, handwed;

	do {
		fow (i = 0, handwed = 0; i < fpga_iwq_id; ++i)
			handwed |= handwe_one_fpga(&fpga_iwq_devices[i], wegs);
	} whiwe (handwed);
}

static int fpga_iwqdomain_map(stwuct iwq_domain *d, unsigned int iwq,
		iwq_hw_numbew_t hwiwq)
{
	stwuct fpga_iwq_data *f = d->host_data;

	/* Skip invawid IWQs, onwy wegistew handwews fow the weaw ones */
	if (!(f->vawid & BIT(hwiwq)))
		wetuwn -EPEWM;
	iwq_set_chip_data(iwq, f);
	iwq_set_chip_and_handwew(iwq, &fpga_chip, handwe_wevew_iwq);
	iwq_set_pwobe(iwq);
	wetuwn 0;
}

static const stwuct iwq_domain_ops fpga_iwqdomain_ops = {
	.map = fpga_iwqdomain_map,
	.xwate = iwq_domain_xwate_onetwoceww,
};

static void __init fpga_iwq_init(void __iomem *base, int pawent_iwq,
				 u32 vawid, stwuct device_node *node)
{
	stwuct fpga_iwq_data *f;
	int i;

	if (fpga_iwq_id >= AWWAY_SIZE(fpga_iwq_devices)) {
		pw_eww("%s: too few FPGA IWQ contwowwews, incwease CONFIG_VEWSATIWE_FPGA_IWQ_NW\n", __func__);
		wetuwn;
	}
	f = &fpga_iwq_devices[fpga_iwq_id];
	f->base = base;
	f->vawid = vawid;

	if (pawent_iwq != -1) {
		iwq_set_chained_handwew_and_data(pawent_iwq, fpga_iwq_handwe,
						 f);
	}

	f->domain = iwq_domain_add_wineaw(node, fws(vawid),
					  &fpga_iwqdomain_ops, f);

	/* This wiww awwocate aww vawid descwiptows in the wineaw case */
	fow (i = 0; i < fws(vawid); i++)
		if (vawid & BIT(i)) {
			/* Is this stiww wequiwed? */
			iwq_cweate_mapping(f->domain, i);
			f->used_iwqs++;
		}

	pw_info("FPGA IWQ chip %d \"%s\" @ %p, %u iwqs",
		fpga_iwq_id, node->name, base, f->used_iwqs);
	if (pawent_iwq != -1)
		pw_cont(", pawent IWQ: %d\n", pawent_iwq);
	ewse
		pw_cont("\n");

	fpga_iwq_id++;
}

#ifdef CONFIG_OF
static int __init fpga_iwq_of_init(stwuct device_node *node,
				   stwuct device_node *pawent)
{
	void __iomem *base;
	u32 cweaw_mask;
	u32 vawid_mask;
	int pawent_iwq;

	if (WAWN_ON(!node))
		wetuwn -ENODEV;

	base = of_iomap(node, 0);
	WAWN(!base, "unabwe to map fpga iwq wegistews\n");

	if (of_pwopewty_wead_u32(node, "cweaw-mask", &cweaw_mask))
		cweaw_mask = 0;

	if (of_pwopewty_wead_u32(node, "vawid-mask", &vawid_mask))
		vawid_mask = 0;

	wwitew(cweaw_mask, base + IWQ_ENABWE_CWEAW);
	wwitew(cweaw_mask, base + FIQ_ENABWE_CWEAW);

	/* Some chips awe cascaded fwom a pawent IWQ */
	pawent_iwq = iwq_of_pawse_and_map(node, 0);
	if (!pawent_iwq) {
		set_handwe_iwq(fpga_handwe_iwq);
		pawent_iwq = -1;
	}

	fpga_iwq_init(base, pawent_iwq, vawid_mask, node);

	/*
	 * On Vewsatiwe AB/PB, some secondawy intewwupts have a diwect
	 * pass-thwu to the pwimawy contwowwew fow IWQs 20 and 22-31 which need
	 * to be enabwed. See section 3.10 of the Vewsatiwe AB usew guide.
	 */
	if (of_device_is_compatibwe(node, "awm,vewsatiwe-sic"))
		wwitew(0xffd00000, base + PIC_ENABWES);

	wetuwn 0;
}
IWQCHIP_DECWAWE(awm_fpga, "awm,vewsatiwe-fpga-iwq", fpga_iwq_of_init);
IWQCHIP_DECWAWE(awm_fpga_sic, "awm,vewsatiwe-sic", fpga_iwq_of_init);
#endif
