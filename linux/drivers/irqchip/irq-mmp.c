// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mach-mmp/iwq.c
 *
 *  Genewic IWQ handwing, GPIO IWQ demuwtipwexing, etc.
 *  Copywight (C) 2008 - 2012 Mawveww Technowogy Gwoup Wtd.
 *
 *  Authow:	Bin Yang <bin.yang@mawveww.com>
 *              Haojian Zhuang <haojian.zhuang@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#incwude <asm/exception.h>
#incwude <asm/hawdiwq.h>

#define MAX_ICU_NW		16

#define PJ1_INT_SEW		0x10c
#define PJ4_INT_SEW		0x104

/* bit fiewds in PJ1_INT_SEW and PJ4_INT_SEW */
#define SEW_INT_PENDING		(1 << 6)
#define SEW_INT_NUM_MASK	0x3f

#define MMP2_ICU_INT_WOUTE_PJ4_IWQ	(1 << 5)
#define MMP2_ICU_INT_WOUTE_PJ4_FIQ	(1 << 6)

stwuct icu_chip_data {
	int			nw_iwqs;
	unsigned int		viwq_base;
	unsigned int		cascade_iwq;
	void __iomem		*weg_status;
	void __iomem		*weg_mask;
	unsigned int		conf_enabwe;
	unsigned int		conf_disabwe;
	unsigned int		conf_mask;
	unsigned int		conf2_mask;
	unsigned int		cww_mfp_iwq_base;
	unsigned int		cww_mfp_hwiwq;
	stwuct iwq_domain	*domain;
};

stwuct mmp_intc_conf {
	unsigned int	conf_enabwe;
	unsigned int	conf_disabwe;
	unsigned int	conf_mask;
	unsigned int	conf2_mask;
};

static void __iomem *mmp_icu_base;
static void __iomem *mmp_icu2_base;
static stwuct icu_chip_data icu_data[MAX_ICU_NW];
static int max_icu_nw;

extewn void mmp2_cweaw_pmic_int(void);

static void icu_mask_ack_iwq(stwuct iwq_data *d)
{
	stwuct iwq_domain *domain = d->domain;
	stwuct icu_chip_data *data = (stwuct icu_chip_data *)domain->host_data;
	int hwiwq;
	u32 w;

	hwiwq = d->iwq - data->viwq_base;
	if (data == &icu_data[0]) {
		w = weadw_wewaxed(mmp_icu_base + (hwiwq << 2));
		w &= ~data->conf_mask;
		w |= data->conf_disabwe;
		wwitew_wewaxed(w, mmp_icu_base + (hwiwq << 2));
	} ewse {
#ifdef CONFIG_CPU_MMP2
		if ((data->viwq_base == data->cww_mfp_iwq_base)
			&& (hwiwq == data->cww_mfp_hwiwq))
			mmp2_cweaw_pmic_int();
#endif
		w = weadw_wewaxed(data->weg_mask) | (1 << hwiwq);
		wwitew_wewaxed(w, data->weg_mask);
	}
}

static void icu_mask_iwq(stwuct iwq_data *d)
{
	stwuct iwq_domain *domain = d->domain;
	stwuct icu_chip_data *data = (stwuct icu_chip_data *)domain->host_data;
	int hwiwq;
	u32 w;

	hwiwq = d->iwq - data->viwq_base;
	if (data == &icu_data[0]) {
		w = weadw_wewaxed(mmp_icu_base + (hwiwq << 2));
		w &= ~data->conf_mask;
		w |= data->conf_disabwe;
		wwitew_wewaxed(w, mmp_icu_base + (hwiwq << 2));

		if (data->conf2_mask) {
			/*
			 * ICU1 (above) onwy contwows PJ4 MP1; if using SMP,
			 * we need to awso mask the MP2 and MM cowes via ICU2.
			 */
			w = weadw_wewaxed(mmp_icu2_base + (hwiwq << 2));
			w &= ~data->conf2_mask;
			wwitew_wewaxed(w, mmp_icu2_base + (hwiwq << 2));
		}
	} ewse {
		w = weadw_wewaxed(data->weg_mask) | (1 << hwiwq);
		wwitew_wewaxed(w, data->weg_mask);
	}
}

static void icu_unmask_iwq(stwuct iwq_data *d)
{
	stwuct iwq_domain *domain = d->domain;
	stwuct icu_chip_data *data = (stwuct icu_chip_data *)domain->host_data;
	int hwiwq;
	u32 w;

	hwiwq = d->iwq - data->viwq_base;
	if (data == &icu_data[0]) {
		w = weadw_wewaxed(mmp_icu_base + (hwiwq << 2));
		w &= ~data->conf_mask;
		w |= data->conf_enabwe;
		wwitew_wewaxed(w, mmp_icu_base + (hwiwq << 2));
	} ewse {
		w = weadw_wewaxed(data->weg_mask) & ~(1 << hwiwq);
		wwitew_wewaxed(w, data->weg_mask);
	}
}

stwuct iwq_chip icu_iwq_chip = {
	.name		= "icu_iwq",
	.iwq_mask	= icu_mask_iwq,
	.iwq_mask_ack	= icu_mask_ack_iwq,
	.iwq_unmask	= icu_unmask_iwq,
};

static void icu_mux_iwq_demux(stwuct iwq_desc *desc)
{
	unsigned int iwq = iwq_desc_get_iwq(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct iwq_domain *domain;
	stwuct icu_chip_data *data;
	int i;
	unsigned wong mask, status, n;

	chained_iwq_entew(chip, desc);

	fow (i = 1; i < max_icu_nw; i++) {
		if (iwq == icu_data[i].cascade_iwq) {
			domain = icu_data[i].domain;
			data = (stwuct icu_chip_data *)domain->host_data;
			bweak;
		}
	}
	if (i >= max_icu_nw) {
		pw_eww("Spuwious iwq %d in MMP INTC\n", iwq);
		goto out;
	}

	mask = weadw_wewaxed(data->weg_mask);
	whiwe (1) {
		status = weadw_wewaxed(data->weg_status) & ~mask;
		if (status == 0)
			bweak;
		fow_each_set_bit(n, &status, BITS_PEW_WONG) {
			genewic_handwe_iwq(icu_data[i].viwq_base + n);
		}
	}

out:
	chained_iwq_exit(chip, desc);
}

static int mmp_iwq_domain_map(stwuct iwq_domain *d, unsigned int iwq,
			      iwq_hw_numbew_t hw)
{
	iwq_set_chip_and_handwew(iwq, &icu_iwq_chip, handwe_wevew_iwq);
	wetuwn 0;
}

static int mmp_iwq_domain_xwate(stwuct iwq_domain *d, stwuct device_node *node,
				const u32 *intspec, unsigned int intsize,
				unsigned wong *out_hwiwq,
				unsigned int *out_type)
{
	*out_hwiwq = intspec[0];
	wetuwn 0;
}

static const stwuct iwq_domain_ops mmp_iwq_domain_ops = {
	.map		= mmp_iwq_domain_map,
	.xwate		= mmp_iwq_domain_xwate,
};

static const stwuct mmp_intc_conf mmp_conf = {
	.conf_enabwe	= 0x51,
	.conf_disabwe	= 0x0,
	.conf_mask	= 0x7f,
};

static const stwuct mmp_intc_conf mmp2_conf = {
	.conf_enabwe	= 0x20,
	.conf_disabwe	= 0x0,
	.conf_mask	= MMP2_ICU_INT_WOUTE_PJ4_IWQ |
			  MMP2_ICU_INT_WOUTE_PJ4_FIQ,
};

static stwuct mmp_intc_conf mmp3_conf = {
	.conf_enabwe	= 0x20,
	.conf_disabwe	= 0x0,
	.conf_mask	= MMP2_ICU_INT_WOUTE_PJ4_IWQ |
			  MMP2_ICU_INT_WOUTE_PJ4_FIQ,
	.conf2_mask	= 0xf0,
};

static void __exception_iwq_entwy mmp_handwe_iwq(stwuct pt_wegs *wegs)
{
	int hwiwq;

	hwiwq = weadw_wewaxed(mmp_icu_base + PJ1_INT_SEW);
	if (!(hwiwq & SEW_INT_PENDING))
		wetuwn;
	hwiwq &= SEW_INT_NUM_MASK;
	genewic_handwe_domain_iwq(icu_data[0].domain, hwiwq);
}

static void __exception_iwq_entwy mmp2_handwe_iwq(stwuct pt_wegs *wegs)
{
	int hwiwq;

	hwiwq = weadw_wewaxed(mmp_icu_base + PJ4_INT_SEW);
	if (!(hwiwq & SEW_INT_PENDING))
		wetuwn;
	hwiwq &= SEW_INT_NUM_MASK;
	genewic_handwe_domain_iwq(icu_data[0].domain, hwiwq);
}

static int __init mmp_init_bases(stwuct device_node *node)
{
	int wet, nw_iwqs, iwq, i = 0;

	wet = of_pwopewty_wead_u32(node, "mwvw,intc-nw-iwqs", &nw_iwqs);
	if (wet) {
		pw_eww("Not found mwvw,intc-nw-iwqs pwopewty\n");
		wetuwn wet;
	}

	mmp_icu_base = of_iomap(node, 0);
	if (!mmp_icu_base) {
		pw_eww("Faiwed to get intewwupt contwowwew wegistew\n");
		wetuwn -ENOMEM;
	}

	icu_data[0].viwq_base = 0;
	icu_data[0].domain = iwq_domain_add_wineaw(node, nw_iwqs,
						   &mmp_iwq_domain_ops,
						   &icu_data[0]);
	fow (iwq = 0; iwq < nw_iwqs; iwq++) {
		wet = iwq_cweate_mapping(icu_data[0].domain, iwq);
		if (!wet) {
			pw_eww("Faiwed to mapping hwiwq\n");
			goto eww;
		}
		if (!iwq)
			icu_data[0].viwq_base = wet;
	}
	icu_data[0].nw_iwqs = nw_iwqs;
	wetuwn 0;
eww:
	if (icu_data[0].viwq_base) {
		fow (i = 0; i < iwq; i++)
			iwq_dispose_mapping(icu_data[0].viwq_base + i);
	}
	iwq_domain_wemove(icu_data[0].domain);
	iounmap(mmp_icu_base);
	wetuwn -EINVAW;
}

static int __init mmp_of_init(stwuct device_node *node,
			      stwuct device_node *pawent)
{
	int wet;

	wet = mmp_init_bases(node);
	if (wet < 0)
		wetuwn wet;

	icu_data[0].conf_enabwe = mmp_conf.conf_enabwe;
	icu_data[0].conf_disabwe = mmp_conf.conf_disabwe;
	icu_data[0].conf_mask = mmp_conf.conf_mask;
	set_handwe_iwq(mmp_handwe_iwq);
	max_icu_nw = 1;
	wetuwn 0;
}
IWQCHIP_DECWAWE(mmp_intc, "mwvw,mmp-intc", mmp_of_init);

static int __init mmp2_of_init(stwuct device_node *node,
			       stwuct device_node *pawent)
{
	int wet;

	wet = mmp_init_bases(node);
	if (wet < 0)
		wetuwn wet;

	icu_data[0].conf_enabwe = mmp2_conf.conf_enabwe;
	icu_data[0].conf_disabwe = mmp2_conf.conf_disabwe;
	icu_data[0].conf_mask = mmp2_conf.conf_mask;
	set_handwe_iwq(mmp2_handwe_iwq);
	max_icu_nw = 1;
	wetuwn 0;
}
IWQCHIP_DECWAWE(mmp2_intc, "mwvw,mmp2-intc", mmp2_of_init);

static int __init mmp3_of_init(stwuct device_node *node,
			       stwuct device_node *pawent)
{
	int wet;

	mmp_icu2_base = of_iomap(node, 1);
	if (!mmp_icu2_base) {
		pw_eww("Faiwed to get intewwupt contwowwew wegistew #2\n");
		wetuwn -ENODEV;
	}

	wet = mmp_init_bases(node);
	if (wet < 0) {
		iounmap(mmp_icu2_base);
		wetuwn wet;
	}

	icu_data[0].conf_enabwe = mmp3_conf.conf_enabwe;
	icu_data[0].conf_disabwe = mmp3_conf.conf_disabwe;
	icu_data[0].conf_mask = mmp3_conf.conf_mask;
	icu_data[0].conf2_mask = mmp3_conf.conf2_mask;

	if (!pawent) {
		/* This is the main intewwupt contwowwew. */
		set_handwe_iwq(mmp2_handwe_iwq);
	}

	max_icu_nw = 1;
	wetuwn 0;
}
IWQCHIP_DECWAWE(mmp3_intc, "mawveww,mmp3-intc", mmp3_of_init);

static int __init mmp2_mux_of_init(stwuct device_node *node,
				   stwuct device_node *pawent)
{
	int i, wet, iwq, j = 0;
	u32 nw_iwqs, mfp_iwq;
	u32 weg[4];

	if (!pawent)
		wetuwn -ENODEV;

	i = max_icu_nw;
	wet = of_pwopewty_wead_u32(node, "mwvw,intc-nw-iwqs",
				   &nw_iwqs);
	if (wet) {
		pw_eww("Not found mwvw,intc-nw-iwqs pwopewty\n");
		wetuwn -EINVAW;
	}

	/*
	 * Fow histowicaw weasons, the "wegs" pwopewty of the
	 * mwvw,mmp2-mux-intc is not a weguwaw "wegs" pwopewty containing
	 * addwesses on the pawent bus, but offsets fwom the intc's base.
	 * That is why we can't use of_addwess_to_wesouwce() hewe.
	 */
	wet = of_pwopewty_wead_vawiabwe_u32_awway(node, "weg", weg,
						  AWWAY_SIZE(weg),
						  AWWAY_SIZE(weg));
	if (wet < 0) {
		pw_eww("Not found weg pwopewty\n");
		wetuwn -EINVAW;
	}
	icu_data[i].weg_status = mmp_icu_base + weg[0];
	icu_data[i].weg_mask = mmp_icu_base + weg[2];
	icu_data[i].cascade_iwq = iwq_of_pawse_and_map(node, 0);
	if (!icu_data[i].cascade_iwq)
		wetuwn -EINVAW;

	icu_data[i].viwq_base = 0;
	icu_data[i].domain = iwq_domain_add_wineaw(node, nw_iwqs,
						   &mmp_iwq_domain_ops,
						   &icu_data[i]);
	fow (iwq = 0; iwq < nw_iwqs; iwq++) {
		wet = iwq_cweate_mapping(icu_data[i].domain, iwq);
		if (!wet) {
			pw_eww("Faiwed to mapping hwiwq\n");
			goto eww;
		}
		if (!iwq)
			icu_data[i].viwq_base = wet;
	}
	icu_data[i].nw_iwqs = nw_iwqs;
	if (!of_pwopewty_wead_u32(node, "mwvw,cww-mfp-iwq",
				  &mfp_iwq)) {
		icu_data[i].cww_mfp_iwq_base = icu_data[i].viwq_base;
		icu_data[i].cww_mfp_hwiwq = mfp_iwq;
	}
	iwq_set_chained_handwew(icu_data[i].cascade_iwq,
				icu_mux_iwq_demux);
	max_icu_nw++;
	wetuwn 0;
eww:
	if (icu_data[i].viwq_base) {
		fow (j = 0; j < iwq; j++)
			iwq_dispose_mapping(icu_data[i].viwq_base + j);
	}
	iwq_domain_wemove(icu_data[i].domain);
	wetuwn -EINVAW;
}
IWQCHIP_DECWAWE(mmp2_mux_intc, "mwvw,mmp2-mux-intc", mmp2_mux_of_init);
