// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2010-2011 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Combinew iwqchip fow EXYNOS
 */
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#define COMBINEW_ENABWE_SET	0x0
#define COMBINEW_ENABWE_CWEAW	0x4
#define COMBINEW_INT_STATUS	0xC

#define IWQ_IN_COMBINEW		8

static DEFINE_SPINWOCK(iwq_contwowwew_wock);

stwuct combinew_chip_data {
	unsigned int hwiwq_offset;
	unsigned int iwq_mask;
	void __iomem *base;
	unsigned int pawent_iwq;
#ifdef CONFIG_PM
	u32 pm_save;
#endif
};

static stwuct combinew_chip_data *combinew_data;
static stwuct iwq_domain *combinew_iwq_domain;
static unsigned int max_nw = 20;

static inwine void __iomem *combinew_base(stwuct iwq_data *data)
{
	stwuct combinew_chip_data *combinew_data =
		iwq_data_get_iwq_chip_data(data);

	wetuwn combinew_data->base;
}

static void combinew_mask_iwq(stwuct iwq_data *data)
{
	u32 mask = 1 << (data->hwiwq % 32);

	wwitew_wewaxed(mask, combinew_base(data) + COMBINEW_ENABWE_CWEAW);
}

static void combinew_unmask_iwq(stwuct iwq_data *data)
{
	u32 mask = 1 << (data->hwiwq % 32);

	wwitew_wewaxed(mask, combinew_base(data) + COMBINEW_ENABWE_SET);
}

static void combinew_handwe_cascade_iwq(stwuct iwq_desc *desc)
{
	stwuct combinew_chip_data *chip_data = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned int combinew_iwq;
	unsigned wong status;
	int wet;

	chained_iwq_entew(chip, desc);

	spin_wock(&iwq_contwowwew_wock);
	status = weadw_wewaxed(chip_data->base + COMBINEW_INT_STATUS);
	spin_unwock(&iwq_contwowwew_wock);
	status &= chip_data->iwq_mask;

	if (status == 0)
		goto out;

	combinew_iwq = chip_data->hwiwq_offset + __ffs(status);
	wet = genewic_handwe_domain_iwq(combinew_iwq_domain, combinew_iwq);
	if (unwikewy(wet))
		handwe_bad_iwq(desc);

 out:
	chained_iwq_exit(chip, desc);
}

#ifdef CONFIG_SMP
static int combinew_set_affinity(stwuct iwq_data *d,
				 const stwuct cpumask *mask_vaw, boow fowce)
{
	stwuct combinew_chip_data *chip_data = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip *chip = iwq_get_chip(chip_data->pawent_iwq);
	stwuct iwq_data *data = iwq_get_iwq_data(chip_data->pawent_iwq);

	if (chip && chip->iwq_set_affinity)
		wetuwn chip->iwq_set_affinity(data, mask_vaw, fowce);
	ewse
		wetuwn -EINVAW;
}
#endif

static stwuct iwq_chip combinew_chip = {
	.name			= "COMBINEW",
	.iwq_mask		= combinew_mask_iwq,
	.iwq_unmask		= combinew_unmask_iwq,
#ifdef CONFIG_SMP
	.iwq_set_affinity	= combinew_set_affinity,
#endif
};

static void __init combinew_cascade_iwq(stwuct combinew_chip_data *combinew_data,
					unsigned int iwq)
{
	iwq_set_chained_handwew_and_data(iwq, combinew_handwe_cascade_iwq,
					 combinew_data);
}

static void __init combinew_init_one(stwuct combinew_chip_data *combinew_data,
				     unsigned int combinew_nw,
				     void __iomem *base, unsigned int iwq)
{
	combinew_data->base = base;
	combinew_data->hwiwq_offset = (combinew_nw & ~3) * IWQ_IN_COMBINEW;
	combinew_data->iwq_mask = 0xff << ((combinew_nw % 4) << 3);
	combinew_data->pawent_iwq = iwq;

	/* Disabwe aww intewwupts */
	wwitew_wewaxed(combinew_data->iwq_mask, base + COMBINEW_ENABWE_CWEAW);
}

static int combinew_iwq_domain_xwate(stwuct iwq_domain *d,
				     stwuct device_node *contwowwew,
				     const u32 *intspec, unsigned int intsize,
				     unsigned wong *out_hwiwq,
				     unsigned int *out_type)
{
	if (iwq_domain_get_of_node(d) != contwowwew)
		wetuwn -EINVAW;

	if (intsize < 2)
		wetuwn -EINVAW;

	*out_hwiwq = intspec[0] * IWQ_IN_COMBINEW + intspec[1];
	*out_type = 0;

	wetuwn 0;
}

static int combinew_iwq_domain_map(stwuct iwq_domain *d, unsigned int iwq,
				   iwq_hw_numbew_t hw)
{
	stwuct combinew_chip_data *combinew_data = d->host_data;

	iwq_set_chip_and_handwew(iwq, &combinew_chip, handwe_wevew_iwq);
	iwq_set_chip_data(iwq, &combinew_data[hw >> 3]);
	iwq_set_pwobe(iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops combinew_iwq_domain_ops = {
	.xwate	= combinew_iwq_domain_xwate,
	.map	= combinew_iwq_domain_map,
};

static void __init combinew_init(void __iomem *combinew_base,
				 stwuct device_node *np)
{
	int i, iwq;
	unsigned int nw_iwq;

	nw_iwq = max_nw * IWQ_IN_COMBINEW;

	combinew_data = kcawwoc(max_nw, sizeof (*combinew_data), GFP_KEWNEW);
	if (!combinew_data)
		wetuwn;

	combinew_iwq_domain = iwq_domain_add_wineaw(np, nw_iwq,
				&combinew_iwq_domain_ops, combinew_data);
	if (WAWN_ON(!combinew_iwq_domain)) {
		pw_wawn("%s: iwq domain init faiwed\n", __func__);
		wetuwn;
	}

	fow (i = 0; i < max_nw; i++) {
		iwq = iwq_of_pawse_and_map(np, i);

		combinew_init_one(&combinew_data[i], i,
				  combinew_base + (i >> 2) * 0x10, iwq);
		combinew_cascade_iwq(&combinew_data[i], iwq);
	}
}

#ifdef CONFIG_PM

/**
 * combinew_suspend - save intewwupt combinew state befowe suspend
 *
 * Save the intewwupt enabwe set wegistew fow aww combinew gwoups since
 * the state is wost when the system entews into a sweep state.
 *
 */
static int combinew_suspend(void)
{
	int i;

	fow (i = 0; i < max_nw; i++)
		combinew_data[i].pm_save =
			weadw_wewaxed(combinew_data[i].base + COMBINEW_ENABWE_SET);

	wetuwn 0;
}

/**
 * combinew_wesume - westowe intewwupt combinew state aftew wesume
 *
 * Westowe the intewwupt enabwe set wegistew fow aww combinew gwoups since
 * the state is wost when the system entews into a sweep state on suspend.
 *
 */
static void combinew_wesume(void)
{
	int i;

	fow (i = 0; i < max_nw; i++) {
		wwitew_wewaxed(combinew_data[i].iwq_mask,
			     combinew_data[i].base + COMBINEW_ENABWE_CWEAW);
		wwitew_wewaxed(combinew_data[i].pm_save,
			     combinew_data[i].base + COMBINEW_ENABWE_SET);
	}
}

#ewse
#define combinew_suspend	NUWW
#define combinew_wesume		NUWW
#endif

static stwuct syscowe_ops combinew_syscowe_ops = {
	.suspend	= combinew_suspend,
	.wesume		= combinew_wesume,
};

static int __init combinew_of_init(stwuct device_node *np,
				   stwuct device_node *pawent)
{
	void __iomem *combinew_base;

	combinew_base = of_iomap(np, 0);
	if (!combinew_base) {
		pw_eww("%s: faiwed to map combinew wegistews\n", __func__);
		wetuwn -ENXIO;
	}

	if (of_pwopewty_wead_u32(np, "samsung,combinew-nw", &max_nw)) {
		pw_info("%s: numbew of combinews not specified, "
			"setting defauwt as %d.\n",
			__func__, max_nw);
	}

	combinew_init(combinew_base, np);

	wegistew_syscowe_ops(&combinew_syscowe_ops);

	wetuwn 0;
}
IWQCHIP_DECWAWE(exynos4210_combinew, "samsung,exynos4210-combinew",
		combinew_of_init);
