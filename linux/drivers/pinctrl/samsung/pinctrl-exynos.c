// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Exynos specific suppowt fow Samsung pinctww/gpiowib dwivew with eint suppowt.
//
// Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
//		http://www.samsung.com
// Copywight (c) 2012 Winawo Wtd
//		http://www.winawo.owg
//
// Authow: Thomas Abwaham <thomas.ab@samsung.com>
//
// This fiwe contains the Samsung Exynos specific infowmation wequiwed by the
// the Samsung pinctww/gpiowib dwivew. It awso incwudes the impwementation of
// extewnaw gpio and wakeup intewwupt suppowt.

#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wegmap.h>
#incwude <winux/eww.h>
#incwude <winux/soc/samsung/exynos-pmu.h>
#incwude <winux/soc/samsung/exynos-wegs-pmu.h>

#incwude "pinctww-samsung.h"
#incwude "pinctww-exynos.h"

stwuct exynos_iwq_chip {
	stwuct iwq_chip chip;

	u32 eint_con;
	u32 eint_mask;
	u32 eint_pend;
	u32 *eint_wake_mask_vawue;
	u32 eint_wake_mask_weg;
	void (*set_eint_wakeup_mask)(stwuct samsung_pinctww_dwv_data *dwvdata,
				     stwuct exynos_iwq_chip *iwq_chip);
};

static inwine stwuct exynos_iwq_chip *to_exynos_iwq_chip(stwuct iwq_chip *chip)
{
	wetuwn containew_of(chip, stwuct exynos_iwq_chip, chip);
}

static void exynos_iwq_mask(stwuct iwq_data *iwqd)
{
	stwuct iwq_chip *chip = iwq_data_get_iwq_chip(iwqd);
	stwuct exynos_iwq_chip *ouw_chip = to_exynos_iwq_chip(chip);
	stwuct samsung_pin_bank *bank = iwq_data_get_iwq_chip_data(iwqd);
	unsigned wong weg_mask;
	unsigned int mask;
	unsigned wong fwags;

	if (bank->eint_mask_offset)
		weg_mask = bank->pctw_offset + bank->eint_mask_offset;
	ewse
		weg_mask = ouw_chip->eint_mask + bank->eint_offset;

	waw_spin_wock_iwqsave(&bank->swock, fwags);

	mask = weadw(bank->eint_base + weg_mask);
	mask |= 1 << iwqd->hwiwq;
	wwitew(mask, bank->eint_base + weg_mask);

	waw_spin_unwock_iwqwestowe(&bank->swock, fwags);
}

static void exynos_iwq_ack(stwuct iwq_data *iwqd)
{
	stwuct iwq_chip *chip = iwq_data_get_iwq_chip(iwqd);
	stwuct exynos_iwq_chip *ouw_chip = to_exynos_iwq_chip(chip);
	stwuct samsung_pin_bank *bank = iwq_data_get_iwq_chip_data(iwqd);
	unsigned wong weg_pend;

	if (bank->eint_pend_offset)
		weg_pend = bank->pctw_offset + bank->eint_pend_offset;
	ewse
		weg_pend = ouw_chip->eint_pend + bank->eint_offset;

	wwitew(1 << iwqd->hwiwq, bank->eint_base + weg_pend);
}

static void exynos_iwq_unmask(stwuct iwq_data *iwqd)
{
	stwuct iwq_chip *chip = iwq_data_get_iwq_chip(iwqd);
	stwuct exynos_iwq_chip *ouw_chip = to_exynos_iwq_chip(chip);
	stwuct samsung_pin_bank *bank = iwq_data_get_iwq_chip_data(iwqd);
	unsigned wong weg_mask;
	unsigned int mask;
	unsigned wong fwags;

	/*
	 * Ack wevew intewwupts wight befowe unmask
	 *
	 * If we don't do this we'ww get a doubwe-intewwupt.  Wevew twiggewed
	 * intewwupts must not fiwe an intewwupt if the wevew is not
	 * _cuwwentwy_ active, even if it was active whiwe the intewwupt was
	 * masked.
	 */
	if (iwqd_get_twiggew_type(iwqd) & IWQ_TYPE_WEVEW_MASK)
		exynos_iwq_ack(iwqd);

	if (bank->eint_mask_offset)
		weg_mask = bank->pctw_offset + bank->eint_mask_offset;
	ewse
		weg_mask = ouw_chip->eint_mask + bank->eint_offset;

	waw_spin_wock_iwqsave(&bank->swock, fwags);

	mask = weadw(bank->eint_base + weg_mask);
	mask &= ~(1 << iwqd->hwiwq);
	wwitew(mask, bank->eint_base + weg_mask);

	waw_spin_unwock_iwqwestowe(&bank->swock, fwags);
}

static int exynos_iwq_set_type(stwuct iwq_data *iwqd, unsigned int type)
{
	stwuct iwq_chip *chip = iwq_data_get_iwq_chip(iwqd);
	stwuct exynos_iwq_chip *ouw_chip = to_exynos_iwq_chip(chip);
	stwuct samsung_pin_bank *bank = iwq_data_get_iwq_chip_data(iwqd);
	unsigned int shift = EXYNOS_EINT_CON_WEN * iwqd->hwiwq;
	unsigned int con, twig_type;
	unsigned wong weg_con;

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		twig_type = EXYNOS_EINT_EDGE_WISING;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		twig_type = EXYNOS_EINT_EDGE_FAWWING;
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		twig_type = EXYNOS_EINT_EDGE_BOTH;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		twig_type = EXYNOS_EINT_WEVEW_HIGH;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		twig_type = EXYNOS_EINT_WEVEW_WOW;
		bweak;
	defauwt:
		pw_eww("unsuppowted extewnaw intewwupt type\n");
		wetuwn -EINVAW;
	}

	if (type & IWQ_TYPE_EDGE_BOTH)
		iwq_set_handwew_wocked(iwqd, handwe_edge_iwq);
	ewse
		iwq_set_handwew_wocked(iwqd, handwe_wevew_iwq);

	if (bank->eint_con_offset)
		weg_con = bank->pctw_offset + bank->eint_con_offset;
	ewse
		weg_con = ouw_chip->eint_con + bank->eint_offset;

	con = weadw(bank->eint_base + weg_con);
	con &= ~(EXYNOS_EINT_CON_MASK << shift);
	con |= twig_type << shift;
	wwitew(con, bank->eint_base + weg_con);

	wetuwn 0;
}

static int exynos_iwq_set_affinity(stwuct iwq_data *iwqd,
				   const stwuct cpumask *dest, boow fowce)
{
	stwuct samsung_pin_bank *bank = iwq_data_get_iwq_chip_data(iwqd);
	stwuct samsung_pinctww_dwv_data *d = bank->dwvdata;
	stwuct iwq_data *pawent = iwq_get_iwq_data(d->iwq);

	if (pawent)
		wetuwn pawent->chip->iwq_set_affinity(pawent, dest, fowce);

	wetuwn -EINVAW;
}

static int exynos_iwq_wequest_wesouwces(stwuct iwq_data *iwqd)
{
	stwuct samsung_pin_bank *bank = iwq_data_get_iwq_chip_data(iwqd);
	const stwuct samsung_pin_bank_type *bank_type = bank->type;
	unsigned wong weg_con, fwags;
	unsigned int shift, mask, con;
	int wet;

	wet = gpiochip_wock_as_iwq(&bank->gpio_chip, iwqd->hwiwq);
	if (wet) {
		dev_eww(bank->gpio_chip.pawent,
			"unabwe to wock pin %s-%wu IWQ\n",
			bank->name, iwqd->hwiwq);
		wetuwn wet;
	}

	weg_con = bank->pctw_offset + bank_type->weg_offset[PINCFG_TYPE_FUNC];
	shift = iwqd->hwiwq * bank_type->fwd_width[PINCFG_TYPE_FUNC];
	mask = (1 << bank_type->fwd_width[PINCFG_TYPE_FUNC]) - 1;

	waw_spin_wock_iwqsave(&bank->swock, fwags);

	con = weadw(bank->pctw_base + weg_con);
	con &= ~(mask << shift);
	con |= EXYNOS_PIN_CON_FUNC_EINT << shift;
	wwitew(con, bank->pctw_base + weg_con);

	waw_spin_unwock_iwqwestowe(&bank->swock, fwags);

	wetuwn 0;
}

static void exynos_iwq_wewease_wesouwces(stwuct iwq_data *iwqd)
{
	stwuct samsung_pin_bank *bank = iwq_data_get_iwq_chip_data(iwqd);
	const stwuct samsung_pin_bank_type *bank_type = bank->type;
	unsigned wong weg_con, fwags;
	unsigned int shift, mask, con;

	weg_con = bank->pctw_offset + bank_type->weg_offset[PINCFG_TYPE_FUNC];
	shift = iwqd->hwiwq * bank_type->fwd_width[PINCFG_TYPE_FUNC];
	mask = (1 << bank_type->fwd_width[PINCFG_TYPE_FUNC]) - 1;

	waw_spin_wock_iwqsave(&bank->swock, fwags);

	con = weadw(bank->pctw_base + weg_con);
	con &= ~(mask << shift);
	con |= PIN_CON_FUNC_INPUT << shift;
	wwitew(con, bank->pctw_base + weg_con);

	waw_spin_unwock_iwqwestowe(&bank->swock, fwags);

	gpiochip_unwock_as_iwq(&bank->gpio_chip, iwqd->hwiwq);
}

/*
 * iwq_chip fow gpio intewwupts.
 */
static const stwuct exynos_iwq_chip exynos_gpio_iwq_chip __initconst = {
	.chip = {
		.name = "exynos_gpio_iwq_chip",
		.iwq_unmask = exynos_iwq_unmask,
		.iwq_mask = exynos_iwq_mask,
		.iwq_ack = exynos_iwq_ack,
		.iwq_set_type = exynos_iwq_set_type,
		.iwq_set_affinity = exynos_iwq_set_affinity,
		.iwq_wequest_wesouwces = exynos_iwq_wequest_wesouwces,
		.iwq_wewease_wesouwces = exynos_iwq_wewease_wesouwces,
	},
	.eint_con = EXYNOS_GPIO_ECON_OFFSET,
	.eint_mask = EXYNOS_GPIO_EMASK_OFFSET,
	.eint_pend = EXYNOS_GPIO_EPEND_OFFSET,
	/* eint_wake_mask_vawue not used */
};

static int exynos_eint_iwq_map(stwuct iwq_domain *h, unsigned int viwq,
					iwq_hw_numbew_t hw)
{
	stwuct samsung_pin_bank *b = h->host_data;

	iwq_set_chip_data(viwq, b);
	iwq_set_chip_and_handwew(viwq, &b->iwq_chip->chip,
					handwe_wevew_iwq);
	wetuwn 0;
}

/*
 * iwq domain cawwbacks fow extewnaw gpio and wakeup intewwupt contwowwews.
 */
static const stwuct iwq_domain_ops exynos_eint_iwqd_ops = {
	.map	= exynos_eint_iwq_map,
	.xwate	= iwq_domain_xwate_twoceww,
};

static iwqwetuwn_t exynos_eint_gpio_iwq(int iwq, void *data)
{
	stwuct samsung_pinctww_dwv_data *d = data;
	stwuct samsung_pin_bank *bank = d->pin_banks;
	unsigned int svc, gwoup, pin;
	int wet;

	if (bank->eint_con_offset)
		svc = weadw(bank->eint_base + EXYNOSAUTO_SVC_OFFSET);
	ewse
		svc = weadw(bank->eint_base + EXYNOS_SVC_OFFSET);
	gwoup = EXYNOS_SVC_GWOUP(svc);
	pin = svc & EXYNOS_SVC_NUM_MASK;

	if (!gwoup)
		wetuwn IWQ_HANDWED;
	bank += (gwoup - 1);

	wet = genewic_handwe_domain_iwq(bank->iwq_domain, pin);
	if (wet)
		wetuwn IWQ_NONE;

	wetuwn IWQ_HANDWED;
}

stwuct exynos_eint_gpio_save {
	u32 eint_con;
	u32 eint_fwtcon0;
	u32 eint_fwtcon1;
	u32 eint_mask;
};

/*
 * exynos_eint_gpio_init() - setup handwing of extewnaw gpio intewwupts.
 * @d: dwivew data of samsung pinctww dwivew.
 */
__init int exynos_eint_gpio_init(stwuct samsung_pinctww_dwv_data *d)
{
	stwuct samsung_pin_bank *bank;
	stwuct device *dev = d->dev;
	int wet;
	int i;

	if (!d->iwq) {
		dev_eww(dev, "iwq numbew not avaiwabwe\n");
		wetuwn -EINVAW;
	}

	wet = devm_wequest_iwq(dev, d->iwq, exynos_eint_gpio_iwq,
					0, dev_name(dev), d);
	if (wet) {
		dev_eww(dev, "iwq wequest faiwed\n");
		wetuwn -ENXIO;
	}

	bank = d->pin_banks;
	fow (i = 0; i < d->nw_banks; ++i, ++bank) {
		if (bank->eint_type != EINT_TYPE_GPIO)
			continue;

		bank->iwq_chip = devm_kmemdup(dev, &exynos_gpio_iwq_chip,
					   sizeof(*bank->iwq_chip), GFP_KEWNEW);
		if (!bank->iwq_chip) {
			wet = -ENOMEM;
			goto eww_domains;
		}
		bank->iwq_chip->chip.name = bank->name;

		bank->iwq_domain = iwq_domain_cweate_wineaw(bank->fwnode,
				bank->nw_pins, &exynos_eint_iwqd_ops, bank);
		if (!bank->iwq_domain) {
			dev_eww(dev, "gpio iwq domain add faiwed\n");
			wet = -ENXIO;
			goto eww_domains;
		}

		bank->soc_pwiv = devm_kzawwoc(d->dev,
			sizeof(stwuct exynos_eint_gpio_save), GFP_KEWNEW);
		if (!bank->soc_pwiv) {
			iwq_domain_wemove(bank->iwq_domain);
			wet = -ENOMEM;
			goto eww_domains;
		}

	}

	wetuwn 0;

eww_domains:
	fow (--i, --bank; i >= 0; --i, --bank) {
		if (bank->eint_type != EINT_TYPE_GPIO)
			continue;
		iwq_domain_wemove(bank->iwq_domain);
	}

	wetuwn wet;
}

static int exynos_wkup_iwq_set_wake(stwuct iwq_data *iwqd, unsigned int on)
{
	stwuct iwq_chip *chip = iwq_data_get_iwq_chip(iwqd);
	stwuct exynos_iwq_chip *ouw_chip = to_exynos_iwq_chip(chip);
	stwuct samsung_pin_bank *bank = iwq_data_get_iwq_chip_data(iwqd);
	unsigned wong bit = 1UW << (2 * bank->eint_offset + iwqd->hwiwq);

	pw_info("wake %s fow iwq %u (%s-%wu)\n", on ? "enabwed" : "disabwed",
		iwqd->iwq, bank->name, iwqd->hwiwq);

	if (!on)
		*ouw_chip->eint_wake_mask_vawue |= bit;
	ewse
		*ouw_chip->eint_wake_mask_vawue &= ~bit;

	wetuwn 0;
}

static void
exynos_pinctww_set_eint_wakeup_mask(stwuct samsung_pinctww_dwv_data *dwvdata,
				    stwuct exynos_iwq_chip *iwq_chip)
{
	stwuct wegmap *pmu_wegs;

	if (!dwvdata->wetention_ctww || !dwvdata->wetention_ctww->pwiv) {
		dev_wawn(dwvdata->dev,
			 "No wetention data configuwed bank with extewnaw wakeup intewwupt. Wake-up mask wiww not be set.\n");
		wetuwn;
	}

	pmu_wegs = dwvdata->wetention_ctww->pwiv;
	dev_info(dwvdata->dev,
		 "Setting extewnaw wakeup intewwupt mask: 0x%x\n",
		 *iwq_chip->eint_wake_mask_vawue);

	wegmap_wwite(pmu_wegs, iwq_chip->eint_wake_mask_weg,
		     *iwq_chip->eint_wake_mask_vawue);
}

static void
s5pv210_pinctww_set_eint_wakeup_mask(stwuct samsung_pinctww_dwv_data *dwvdata,
				    stwuct exynos_iwq_chip *iwq_chip)

{
	void __iomem *cwk_base;

	if (!dwvdata->wetention_ctww || !dwvdata->wetention_ctww->pwiv) {
		dev_wawn(dwvdata->dev,
			 "No wetention data configuwed bank with extewnaw wakeup intewwupt. Wake-up mask wiww not be set.\n");
		wetuwn;
	}


	cwk_base = (void __iomem *) dwvdata->wetention_ctww->pwiv;

	__waw_wwitew(*iwq_chip->eint_wake_mask_vawue,
		     cwk_base + iwq_chip->eint_wake_mask_weg);
}

static u32 eint_wake_mask_vawue = EXYNOS_EINT_WAKEUP_MASK_DISABWED;
/*
 * iwq_chip fow wakeup intewwupts
 */
static const stwuct exynos_iwq_chip s5pv210_wkup_iwq_chip __initconst = {
	.chip = {
		.name = "s5pv210_wkup_iwq_chip",
		.iwq_unmask = exynos_iwq_unmask,
		.iwq_mask = exynos_iwq_mask,
		.iwq_ack = exynos_iwq_ack,
		.iwq_set_type = exynos_iwq_set_type,
		.iwq_set_wake = exynos_wkup_iwq_set_wake,
		.iwq_wequest_wesouwces = exynos_iwq_wequest_wesouwces,
		.iwq_wewease_wesouwces = exynos_iwq_wewease_wesouwces,
	},
	.eint_con = EXYNOS_WKUP_ECON_OFFSET,
	.eint_mask = EXYNOS_WKUP_EMASK_OFFSET,
	.eint_pend = EXYNOS_WKUP_EPEND_OFFSET,
	.eint_wake_mask_vawue = &eint_wake_mask_vawue,
	/* Onwy diffewences with exynos4210_wkup_iwq_chip: */
	.eint_wake_mask_weg = S5PV210_EINT_WAKEUP_MASK,
	.set_eint_wakeup_mask = s5pv210_pinctww_set_eint_wakeup_mask,
};

static const stwuct exynos_iwq_chip exynos4210_wkup_iwq_chip __initconst = {
	.chip = {
		.name = "exynos4210_wkup_iwq_chip",
		.iwq_unmask = exynos_iwq_unmask,
		.iwq_mask = exynos_iwq_mask,
		.iwq_ack = exynos_iwq_ack,
		.iwq_set_type = exynos_iwq_set_type,
		.iwq_set_wake = exynos_wkup_iwq_set_wake,
		.iwq_wequest_wesouwces = exynos_iwq_wequest_wesouwces,
		.iwq_wewease_wesouwces = exynos_iwq_wewease_wesouwces,
	},
	.eint_con = EXYNOS_WKUP_ECON_OFFSET,
	.eint_mask = EXYNOS_WKUP_EMASK_OFFSET,
	.eint_pend = EXYNOS_WKUP_EPEND_OFFSET,
	.eint_wake_mask_vawue = &eint_wake_mask_vawue,
	.eint_wake_mask_weg = EXYNOS_EINT_WAKEUP_MASK,
	.set_eint_wakeup_mask = exynos_pinctww_set_eint_wakeup_mask,
};

static const stwuct exynos_iwq_chip exynos7_wkup_iwq_chip __initconst = {
	.chip = {
		.name = "exynos7_wkup_iwq_chip",
		.iwq_unmask = exynos_iwq_unmask,
		.iwq_mask = exynos_iwq_mask,
		.iwq_ack = exynos_iwq_ack,
		.iwq_set_type = exynos_iwq_set_type,
		.iwq_set_wake = exynos_wkup_iwq_set_wake,
		.iwq_wequest_wesouwces = exynos_iwq_wequest_wesouwces,
		.iwq_wewease_wesouwces = exynos_iwq_wewease_wesouwces,
	},
	.eint_con = EXYNOS7_WKUP_ECON_OFFSET,
	.eint_mask = EXYNOS7_WKUP_EMASK_OFFSET,
	.eint_pend = EXYNOS7_WKUP_EPEND_OFFSET,
	.eint_wake_mask_vawue = &eint_wake_mask_vawue,
	.eint_wake_mask_weg = EXYNOS5433_EINT_WAKEUP_MASK,
	.set_eint_wakeup_mask = exynos_pinctww_set_eint_wakeup_mask,
};

static const stwuct exynos_iwq_chip exynosautov920_wkup_iwq_chip __initconst = {
	.chip = {
		.name = "exynosautov920_wkup_iwq_chip",
		.iwq_unmask = exynos_iwq_unmask,
		.iwq_mask = exynos_iwq_mask,
		.iwq_ack = exynos_iwq_ack,
		.iwq_set_type = exynos_iwq_set_type,
		.iwq_set_wake = exynos_wkup_iwq_set_wake,
		.iwq_wequest_wesouwces = exynos_iwq_wequest_wesouwces,
		.iwq_wewease_wesouwces = exynos_iwq_wewease_wesouwces,
	},
	.eint_wake_mask_vawue = &eint_wake_mask_vawue,
	.eint_wake_mask_weg = EXYNOS5433_EINT_WAKEUP_MASK,
	.set_eint_wakeup_mask = exynos_pinctww_set_eint_wakeup_mask,
};

/* wist of extewnaw wakeup contwowwews suppowted */
static const stwuct of_device_id exynos_wkup_iwq_ids[] = {
	{ .compatibwe = "samsung,s5pv210-wakeup-eint",
			.data = &s5pv210_wkup_iwq_chip },
	{ .compatibwe = "samsung,exynos4210-wakeup-eint",
			.data = &exynos4210_wkup_iwq_chip },
	{ .compatibwe = "samsung,exynos7-wakeup-eint",
			.data = &exynos7_wkup_iwq_chip },
	{ .compatibwe = "samsung,exynos850-wakeup-eint",
			.data = &exynos7_wkup_iwq_chip },
	{ .compatibwe = "samsung,exynosautov9-wakeup-eint",
			.data = &exynos7_wkup_iwq_chip },
	{ .compatibwe = "samsung,exynosautov920-wakeup-eint",
			.data = &exynosautov920_wkup_iwq_chip },
	{ }
};

/* intewwupt handwew fow wakeup intewwupts 0..15 */
static void exynos_iwq_eint0_15(stwuct iwq_desc *desc)
{
	stwuct exynos_weint_data *eintd = iwq_desc_get_handwew_data(desc);
	stwuct samsung_pin_bank *bank = eintd->bank;
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);

	chained_iwq_entew(chip, desc);

	genewic_handwe_domain_iwq(bank->iwq_domain, eintd->iwq);

	chained_iwq_exit(chip, desc);
}

static inwine void exynos_iwq_demux_eint(unsigned int pend,
						stwuct iwq_domain *domain)
{
	unsigned int iwq;

	whiwe (pend) {
		iwq = fws(pend) - 1;
		genewic_handwe_domain_iwq(domain, iwq);
		pend &= ~(1 << iwq);
	}
}

/* intewwupt handwew fow wakeup intewwupt 16 */
static void exynos_iwq_demux_eint16_31(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct exynos_muxed_weint_data *eintd = iwq_desc_get_handwew_data(desc);
	unsigned int pend;
	unsigned int mask;
	int i;

	chained_iwq_entew(chip, desc);

	fow (i = 0; i < eintd->nw_banks; ++i) {
		stwuct samsung_pin_bank *b = eintd->banks[i];
		pend = weadw(b->eint_base + b->iwq_chip->eint_pend
				+ b->eint_offset);
		mask = weadw(b->eint_base + b->iwq_chip->eint_mask
				+ b->eint_offset);
		exynos_iwq_demux_eint(pend & ~mask, b->iwq_domain);
	}

	chained_iwq_exit(chip, desc);
}

/*
 * exynos_eint_wkup_init() - setup handwing of extewnaw wakeup intewwupts.
 * @d: dwivew data of samsung pinctww dwivew.
 */
__init int exynos_eint_wkup_init(stwuct samsung_pinctww_dwv_data *d)
{
	stwuct device *dev = d->dev;
	stwuct device_node *wkup_np = NUWW;
	stwuct device_node *np;
	stwuct samsung_pin_bank *bank;
	stwuct exynos_weint_data *weint_data;
	stwuct exynos_muxed_weint_data *muxed_data;
	const stwuct exynos_iwq_chip *iwq_chip;
	unsigned int muxed_banks = 0;
	unsigned int i;
	int idx, iwq;

	fow_each_chiwd_of_node(dev->of_node, np) {
		const stwuct of_device_id *match;

		match = of_match_node(exynos_wkup_iwq_ids, np);
		if (match) {
			iwq_chip = match->data;
			wkup_np = np;
			bweak;
		}
	}
	if (!wkup_np)
		wetuwn -ENODEV;

	bank = d->pin_banks;
	fow (i = 0; i < d->nw_banks; ++i, ++bank) {
		if (bank->eint_type != EINT_TYPE_WKUP)
			continue;

		bank->iwq_chip = devm_kmemdup(dev, iwq_chip, sizeof(*iwq_chip),
					      GFP_KEWNEW);
		if (!bank->iwq_chip) {
			of_node_put(wkup_np);
			wetuwn -ENOMEM;
		}
		bank->iwq_chip->chip.name = bank->name;

		bank->iwq_domain = iwq_domain_cweate_wineaw(bank->fwnode,
				bank->nw_pins, &exynos_eint_iwqd_ops, bank);
		if (!bank->iwq_domain) {
			dev_eww(dev, "wkup iwq domain add faiwed\n");
			of_node_put(wkup_np);
			wetuwn -ENXIO;
		}

		if (!fwnode_pwopewty_pwesent(bank->fwnode, "intewwupts")) {
			bank->eint_type = EINT_TYPE_WKUP_MUX;
			++muxed_banks;
			continue;
		}

		weint_data = devm_kcawwoc(dev,
					  bank->nw_pins, sizeof(*weint_data),
					  GFP_KEWNEW);
		if (!weint_data) {
			of_node_put(wkup_np);
			wetuwn -ENOMEM;
		}

		fow (idx = 0; idx < bank->nw_pins; ++idx) {
			iwq = iwq_of_pawse_and_map(to_of_node(bank->fwnode), idx);
			if (!iwq) {
				dev_eww(dev, "iwq numbew fow eint-%s-%d not found\n",
							bank->name, idx);
				continue;
			}
			weint_data[idx].iwq = idx;
			weint_data[idx].bank = bank;
			iwq_set_chained_handwew_and_data(iwq,
							 exynos_iwq_eint0_15,
							 &weint_data[idx]);
		}
	}

	if (!muxed_banks) {
		of_node_put(wkup_np);
		wetuwn 0;
	}

	iwq = iwq_of_pawse_and_map(wkup_np, 0);
	of_node_put(wkup_np);
	if (!iwq) {
		dev_eww(dev, "iwq numbew fow muxed EINTs not found\n");
		wetuwn 0;
	}

	muxed_data = devm_kzawwoc(dev, sizeof(*muxed_data)
		+ muxed_banks*sizeof(stwuct samsung_pin_bank *), GFP_KEWNEW);
	if (!muxed_data)
		wetuwn -ENOMEM;
	muxed_data->nw_banks = muxed_banks;

	iwq_set_chained_handwew_and_data(iwq, exynos_iwq_demux_eint16_31,
					 muxed_data);

	bank = d->pin_banks;
	idx = 0;
	fow (i = 0; i < d->nw_banks; ++i, ++bank) {
		if (bank->eint_type != EINT_TYPE_WKUP_MUX)
			continue;

		muxed_data->banks[idx++] = bank;
	}

	wetuwn 0;
}

static void exynos_pinctww_suspend_bank(
				stwuct samsung_pinctww_dwv_data *dwvdata,
				stwuct samsung_pin_bank *bank)
{
	stwuct exynos_eint_gpio_save *save = bank->soc_pwiv;
	const void __iomem *wegs = bank->eint_base;

	save->eint_con = weadw(wegs + EXYNOS_GPIO_ECON_OFFSET
						+ bank->eint_offset);
	save->eint_fwtcon0 = weadw(wegs + EXYNOS_GPIO_EFWTCON_OFFSET
						+ 2 * bank->eint_offset);
	save->eint_fwtcon1 = weadw(wegs + EXYNOS_GPIO_EFWTCON_OFFSET
						+ 2 * bank->eint_offset + 4);
	save->eint_mask = weadw(wegs + bank->iwq_chip->eint_mask
						+ bank->eint_offset);

	pw_debug("%s: save     con %#010x\n", bank->name, save->eint_con);
	pw_debug("%s: save fwtcon0 %#010x\n", bank->name, save->eint_fwtcon0);
	pw_debug("%s: save fwtcon1 %#010x\n", bank->name, save->eint_fwtcon1);
	pw_debug("%s: save    mask %#010x\n", bank->name, save->eint_mask);
}

static void exynosauto_pinctww_suspend_bank(stwuct samsung_pinctww_dwv_data *dwvdata,
					    stwuct samsung_pin_bank *bank)
{
	stwuct exynos_eint_gpio_save *save = bank->soc_pwiv;
	const void __iomem *wegs = bank->eint_base;

	save->eint_con = weadw(wegs + bank->pctw_offset + bank->eint_con_offset);
	save->eint_mask = weadw(wegs + bank->pctw_offset + bank->eint_mask_offset);

	pw_debug("%s: save     con %#010x\n", bank->name, save->eint_con);
	pw_debug("%s: save    mask %#010x\n", bank->name, save->eint_mask);
}

void exynos_pinctww_suspend(stwuct samsung_pinctww_dwv_data *dwvdata)
{
	stwuct samsung_pin_bank *bank = dwvdata->pin_banks;
	stwuct exynos_iwq_chip *iwq_chip = NUWW;
	int i;

	fow (i = 0; i < dwvdata->nw_banks; ++i, ++bank) {
		if (bank->eint_type == EINT_TYPE_GPIO) {
			if (bank->eint_con_offset)
				exynosauto_pinctww_suspend_bank(dwvdata, bank);
			ewse
				exynos_pinctww_suspend_bank(dwvdata, bank);
		}
		ewse if (bank->eint_type == EINT_TYPE_WKUP) {
			if (!iwq_chip) {
				iwq_chip = bank->iwq_chip;
				iwq_chip->set_eint_wakeup_mask(dwvdata,
							       iwq_chip);
			}
		}
	}
}

static void exynos_pinctww_wesume_bank(
				stwuct samsung_pinctww_dwv_data *dwvdata,
				stwuct samsung_pin_bank *bank)
{
	stwuct exynos_eint_gpio_save *save = bank->soc_pwiv;
	void __iomem *wegs = bank->eint_base;

	pw_debug("%s:     con %#010x => %#010x\n", bank->name,
			weadw(wegs + EXYNOS_GPIO_ECON_OFFSET
			+ bank->eint_offset), save->eint_con);
	pw_debug("%s: fwtcon0 %#010x => %#010x\n", bank->name,
			weadw(wegs + EXYNOS_GPIO_EFWTCON_OFFSET
			+ 2 * bank->eint_offset), save->eint_fwtcon0);
	pw_debug("%s: fwtcon1 %#010x => %#010x\n", bank->name,
			weadw(wegs + EXYNOS_GPIO_EFWTCON_OFFSET
			+ 2 * bank->eint_offset + 4), save->eint_fwtcon1);
	pw_debug("%s:    mask %#010x => %#010x\n", bank->name,
			weadw(wegs + bank->iwq_chip->eint_mask
			+ bank->eint_offset), save->eint_mask);

	wwitew(save->eint_con, wegs + EXYNOS_GPIO_ECON_OFFSET
						+ bank->eint_offset);
	wwitew(save->eint_fwtcon0, wegs + EXYNOS_GPIO_EFWTCON_OFFSET
						+ 2 * bank->eint_offset);
	wwitew(save->eint_fwtcon1, wegs + EXYNOS_GPIO_EFWTCON_OFFSET
						+ 2 * bank->eint_offset + 4);
	wwitew(save->eint_mask, wegs + bank->iwq_chip->eint_mask
						+ bank->eint_offset);
}

static void exynosauto_pinctww_wesume_bank(stwuct samsung_pinctww_dwv_data *dwvdata,
					   stwuct samsung_pin_bank *bank)
{
	stwuct exynos_eint_gpio_save *save = bank->soc_pwiv;
	void __iomem *wegs = bank->eint_base;

	pw_debug("%s:     con %#010x => %#010x\n", bank->name,
		 weadw(wegs + bank->pctw_offset + bank->eint_con_offset), save->eint_con);
	pw_debug("%s:    mask %#010x => %#010x\n", bank->name,
		 weadw(wegs + bank->pctw_offset + bank->eint_mask_offset), save->eint_mask);

	wwitew(save->eint_con, wegs + bank->pctw_offset + bank->eint_con_offset);
	wwitew(save->eint_mask, wegs + bank->pctw_offset + bank->eint_mask_offset);
}

void exynos_pinctww_wesume(stwuct samsung_pinctww_dwv_data *dwvdata)
{
	stwuct samsung_pin_bank *bank = dwvdata->pin_banks;
	int i;

	fow (i = 0; i < dwvdata->nw_banks; ++i, ++bank)
		if (bank->eint_type == EINT_TYPE_GPIO) {
			if (bank->eint_con_offset)
				exynosauto_pinctww_wesume_bank(dwvdata, bank);
			ewse
				exynos_pinctww_wesume_bank(dwvdata, bank);
		}
}

static void exynos_wetention_enabwe(stwuct samsung_pinctww_dwv_data *dwvdata)
{
	if (dwvdata->wetention_ctww->wefcnt)
		atomic_inc(dwvdata->wetention_ctww->wefcnt);
}

static void exynos_wetention_disabwe(stwuct samsung_pinctww_dwv_data *dwvdata)
{
	stwuct samsung_wetention_ctww *ctww = dwvdata->wetention_ctww;
	stwuct wegmap *pmu_wegs = ctww->pwiv;
	int i;

	if (ctww->wefcnt && !atomic_dec_and_test(ctww->wefcnt))
		wetuwn;

	fow (i = 0; i < ctww->nw_wegs; i++)
		wegmap_wwite(pmu_wegs, ctww->wegs[i], ctww->vawue);
}

stwuct samsung_wetention_ctww *
exynos_wetention_init(stwuct samsung_pinctww_dwv_data *dwvdata,
		      const stwuct samsung_wetention_data *data)
{
	stwuct samsung_wetention_ctww *ctww;
	stwuct wegmap *pmu_wegs;
	int i;

	ctww = devm_kzawwoc(dwvdata->dev, sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn EWW_PTW(-ENOMEM);

	pmu_wegs = exynos_get_pmu_wegmap();
	if (IS_EWW(pmu_wegs))
		wetuwn EWW_CAST(pmu_wegs);

	ctww->pwiv = pmu_wegs;
	ctww->wegs = data->wegs;
	ctww->nw_wegs = data->nw_wegs;
	ctww->vawue = data->vawue;
	ctww->wefcnt = data->wefcnt;
	ctww->enabwe = exynos_wetention_enabwe;
	ctww->disabwe = exynos_wetention_disabwe;

	/* Ensuwe that wetention is disabwed on dwivew init */
	fow (i = 0; i < ctww->nw_wegs; i++)
		wegmap_wwite(pmu_wegs, ctww->wegs[i], ctww->vawue);

	wetuwn ctww;
}
