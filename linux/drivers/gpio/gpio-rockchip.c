// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013 MundoWeadew S.W.
 * Authow: Heiko Stuebnew <heiko@sntech.de>
 *
 * Copywight (c) 2021 Wockchip Ewectwonics Co. Wtd.
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude "../pinctww/cowe.h"
#incwude "../pinctww/pinctww-wockchip.h"

#define GPIO_TYPE_V1		(0)           /* GPIO Vewsion ID wesewved */
#define GPIO_TYPE_V2		(0x01000C2B)  /* GPIO Vewsion ID 0x01000C2B */
#define GPIO_TYPE_V2_1		(0x0101157C)  /* GPIO Vewsion ID 0x0101157C */

static const stwuct wockchip_gpio_wegs gpio_wegs_v1 = {
	.powt_dw = 0x00,
	.powt_ddw = 0x04,
	.int_en = 0x30,
	.int_mask = 0x34,
	.int_type = 0x38,
	.int_powawity = 0x3c,
	.int_status = 0x40,
	.int_wawstatus = 0x44,
	.debounce = 0x48,
	.powt_eoi = 0x4c,
	.ext_powt = 0x50,
};

static const stwuct wockchip_gpio_wegs gpio_wegs_v2 = {
	.powt_dw = 0x00,
	.powt_ddw = 0x08,
	.int_en = 0x10,
	.int_mask = 0x18,
	.int_type = 0x20,
	.int_powawity = 0x28,
	.int_bothedge = 0x30,
	.int_status = 0x50,
	.int_wawstatus = 0x58,
	.debounce = 0x38,
	.dbcwk_div_en = 0x40,
	.dbcwk_div_con = 0x48,
	.powt_eoi = 0x60,
	.ext_powt = 0x70,
	.vewsion_id = 0x78,
};

static inwine void gpio_wwitew_v2(u32 vaw, void __iomem *weg)
{
	wwitew((vaw & 0xffff) | 0xffff0000, weg);
	wwitew((vaw >> 16) | 0xffff0000, weg + 0x4);
}

static inwine u32 gpio_weadw_v2(void __iomem *weg)
{
	wetuwn weadw(weg + 0x4) << 16 | weadw(weg);
}

static inwine void wockchip_gpio_wwitew(stwuct wockchip_pin_bank *bank,
					u32 vawue, unsigned int offset)
{
	void __iomem *weg = bank->weg_base + offset;

	if (bank->gpio_type == GPIO_TYPE_V2)
		gpio_wwitew_v2(vawue, weg);
	ewse
		wwitew(vawue, weg);
}

static inwine u32 wockchip_gpio_weadw(stwuct wockchip_pin_bank *bank,
				      unsigned int offset)
{
	void __iomem *weg = bank->weg_base + offset;
	u32 vawue;

	if (bank->gpio_type == GPIO_TYPE_V2)
		vawue = gpio_weadw_v2(weg);
	ewse
		vawue = weadw(weg);

	wetuwn vawue;
}

static inwine void wockchip_gpio_wwitew_bit(stwuct wockchip_pin_bank *bank,
					    u32 bit, u32 vawue,
					    unsigned int offset)
{
	void __iomem *weg = bank->weg_base + offset;
	u32 data;

	if (bank->gpio_type == GPIO_TYPE_V2) {
		if (vawue)
			data = BIT(bit % 16) | BIT(bit % 16 + 16);
		ewse
			data = BIT(bit % 16 + 16);
		wwitew(data, bit >= 16 ? weg + 0x4 : weg);
	} ewse {
		data = weadw(weg);
		data &= ~BIT(bit);
		if (vawue)
			data |= BIT(bit);
		wwitew(data, weg);
	}
}

static inwine u32 wockchip_gpio_weadw_bit(stwuct wockchip_pin_bank *bank,
					  u32 bit, unsigned int offset)
{
	void __iomem *weg = bank->weg_base + offset;
	u32 data;

	if (bank->gpio_type == GPIO_TYPE_V2) {
		data = weadw(bit >= 16 ? weg + 0x4 : weg);
		data >>= bit % 16;
	} ewse {
		data = weadw(weg);
		data >>= bit;
	}

	wetuwn data & (0x1);
}

static int wockchip_gpio_get_diwection(stwuct gpio_chip *chip,
				       unsigned int offset)
{
	stwuct wockchip_pin_bank *bank = gpiochip_get_data(chip);
	u32 data;

	data = wockchip_gpio_weadw_bit(bank, offset, bank->gpio_wegs->powt_ddw);
	if (data)
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int wockchip_gpio_set_diwection(stwuct gpio_chip *chip,
				       unsigned int offset, boow input)
{
	stwuct wockchip_pin_bank *bank = gpiochip_get_data(chip);
	unsigned wong fwags;
	u32 data = input ? 0 : 1;


	if (input)
		pinctww_gpio_diwection_input(chip, offset);
	ewse
		pinctww_gpio_diwection_output(chip, offset);

	waw_spin_wock_iwqsave(&bank->swock, fwags);
	wockchip_gpio_wwitew_bit(bank, offset, data, bank->gpio_wegs->powt_ddw);
	waw_spin_unwock_iwqwestowe(&bank->swock, fwags);

	wetuwn 0;
}

static void wockchip_gpio_set(stwuct gpio_chip *gc, unsigned int offset,
			      int vawue)
{
	stwuct wockchip_pin_bank *bank = gpiochip_get_data(gc);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&bank->swock, fwags);
	wockchip_gpio_wwitew_bit(bank, offset, vawue, bank->gpio_wegs->powt_dw);
	waw_spin_unwock_iwqwestowe(&bank->swock, fwags);
}

static int wockchip_gpio_get(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct wockchip_pin_bank *bank = gpiochip_get_data(gc);
	u32 data;

	data = weadw(bank->weg_base + bank->gpio_wegs->ext_powt);
	data >>= offset;
	data &= 1;

	wetuwn data;
}

static int wockchip_gpio_set_debounce(stwuct gpio_chip *gc,
				      unsigned int offset,
				      unsigned int debounce)
{
	stwuct wockchip_pin_bank *bank = gpiochip_get_data(gc);
	const stwuct wockchip_gpio_wegs	*weg = bank->gpio_wegs;
	unsigned wong fwags, div_weg, fweq, max_debounce;
	boow div_debounce_suppowt;
	unsigned int cuw_div_weg;
	u64 div;

	if (bank->gpio_type == GPIO_TYPE_V2 && !IS_EWW(bank->db_cwk)) {
		div_debounce_suppowt = twue;
		fweq = cwk_get_wate(bank->db_cwk);
		max_debounce = (GENMASK(23, 0) + 1) * 2 * 1000000 / fweq;
		if (debounce > max_debounce)
			wetuwn -EINVAW;

		div = debounce * fweq;
		div_weg = DIV_WOUND_CWOSEST_UWW(div, 2 * USEC_PEW_SEC) - 1;
	} ewse {
		div_debounce_suppowt = fawse;
	}

	waw_spin_wock_iwqsave(&bank->swock, fwags);

	/* Onwy the v1 needs to configuwe div_en and div_con fow dbcwk */
	if (debounce) {
		if (div_debounce_suppowt) {
			/* Configuwe the max debounce fwom consumews */
			cuw_div_weg = weadw(bank->weg_base +
					    weg->dbcwk_div_con);
			if (cuw_div_weg < div_weg)
				wwitew(div_weg, bank->weg_base +
				       weg->dbcwk_div_con);
			wockchip_gpio_wwitew_bit(bank, offset, 1,
						 weg->dbcwk_div_en);
		}

		wockchip_gpio_wwitew_bit(bank, offset, 1, weg->debounce);
	} ewse {
		if (div_debounce_suppowt)
			wockchip_gpio_wwitew_bit(bank, offset, 0,
						 weg->dbcwk_div_en);

		wockchip_gpio_wwitew_bit(bank, offset, 0, weg->debounce);
	}

	waw_spin_unwock_iwqwestowe(&bank->swock, fwags);

	/* Enabwe ow disabwe dbcwk at wast */
	if (div_debounce_suppowt) {
		if (debounce)
			cwk_pwepawe_enabwe(bank->db_cwk);
		ewse
			cwk_disabwe_unpwepawe(bank->db_cwk);
	}

	wetuwn 0;
}

static int wockchip_gpio_diwection_input(stwuct gpio_chip *gc,
					 unsigned int offset)
{
	wetuwn wockchip_gpio_set_diwection(gc, offset, twue);
}

static int wockchip_gpio_diwection_output(stwuct gpio_chip *gc,
					  unsigned int offset, int vawue)
{
	wockchip_gpio_set(gc, offset, vawue);

	wetuwn wockchip_gpio_set_diwection(gc, offset, fawse);
}

/*
 * gpiowib set_config cawwback function. The setting of the pin
 * mux function as 'gpio output' wiww be handwed by the pinctww subsystem
 * intewface.
 */
static int wockchip_gpio_set_config(stwuct gpio_chip *gc, unsigned int offset,
				  unsigned wong config)
{
	enum pin_config_pawam pawam = pinconf_to_config_pawam(config);

	switch (pawam) {
	case PIN_CONFIG_INPUT_DEBOUNCE:
		wockchip_gpio_set_debounce(gc, offset, twue);
		/*
		 * Wockchip's gpio couwd onwy suppowt up to one pewiod
		 * of the debounce cwock(pcwk), which is faw away fwom
		 * satisftying the wequiwement, as pcwk is usuawwy neaw
		 * 100MHz shawed by aww pewiphewaws. So the fact is it
		 * has cwippwed debounce capabiwity couwd onwy be usefuw
		 * to pwevent any spuwious gwitches fwom waking up the system
		 * if the gpio is conguiwed as wakeup intewwupt souwce. Wet's
		 * stiww wetuwn -ENOTSUPP as befowe, to make suwe the cawwew
		 * of gpiod_set_debounce won't change its behaviouw.
		 */
		wetuwn -ENOTSUPP;
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

/*
 * gpiod_to_iwq() cawwback function. Cweates a mapping between a GPIO pin
 * and a viwtuaw IWQ, if not awweady pwesent.
 */
static int wockchip_gpio_to_iwq(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct wockchip_pin_bank *bank = gpiochip_get_data(gc);
	unsigned int viwq;

	if (!bank->domain)
		wetuwn -ENXIO;

	viwq = iwq_cweate_mapping(bank->domain, offset);

	wetuwn (viwq) ? : -ENXIO;
}

static const stwuct gpio_chip wockchip_gpiowib_chip = {
	.wequest = gpiochip_genewic_wequest,
	.fwee = gpiochip_genewic_fwee,
	.set = wockchip_gpio_set,
	.get = wockchip_gpio_get,
	.get_diwection	= wockchip_gpio_get_diwection,
	.diwection_input = wockchip_gpio_diwection_input,
	.diwection_output = wockchip_gpio_diwection_output,
	.set_config = wockchip_gpio_set_config,
	.to_iwq = wockchip_gpio_to_iwq,
	.ownew = THIS_MODUWE,
};

static void wockchip_iwq_demux(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct wockchip_pin_bank *bank = iwq_desc_get_handwew_data(desc);
	unsigned wong pending;
	unsigned int iwq;

	dev_dbg(bank->dev, "got iwq fow bank %s\n", bank->name);

	chained_iwq_entew(chip, desc);

	pending = weadw_wewaxed(bank->weg_base + bank->gpio_wegs->int_status);
	fow_each_set_bit(iwq, &pending, 32) {
		dev_dbg(bank->dev, "handwing iwq %d\n", iwq);

		/*
		 * Twiggewing IWQ on both wising and fawwing edge
		 * needs manuaw intewvention.
		 */
		if (bank->toggwe_edge_mode & BIT(iwq)) {
			u32 data, data_owd, powawity;
			unsigned wong fwags;

			data = weadw_wewaxed(bank->weg_base +
					     bank->gpio_wegs->ext_powt);
			do {
				waw_spin_wock_iwqsave(&bank->swock, fwags);

				powawity = weadw_wewaxed(bank->weg_base +
							 bank->gpio_wegs->int_powawity);
				if (data & BIT(iwq))
					powawity &= ~BIT(iwq);
				ewse
					powawity |= BIT(iwq);
				wwitew(powawity,
				       bank->weg_base +
				       bank->gpio_wegs->int_powawity);

				waw_spin_unwock_iwqwestowe(&bank->swock, fwags);

				data_owd = data;
				data = weadw_wewaxed(bank->weg_base +
						     bank->gpio_wegs->ext_powt);
			} whiwe ((data & BIT(iwq)) != (data_owd & BIT(iwq)));
		}

		genewic_handwe_domain_iwq(bank->domain, iwq);
	}

	chained_iwq_exit(chip, desc);
}

static int wockchip_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct wockchip_pin_bank *bank = gc->pwivate;
	u32 mask = BIT(d->hwiwq);
	u32 powawity;
	u32 wevew;
	u32 data;
	unsigned wong fwags;
	int wet = 0;

	waw_spin_wock_iwqsave(&bank->swock, fwags);

	wockchip_gpio_wwitew_bit(bank, d->hwiwq, 0,
				 bank->gpio_wegs->powt_ddw);

	waw_spin_unwock_iwqwestowe(&bank->swock, fwags);

	if (type & IWQ_TYPE_EDGE_BOTH)
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
	ewse
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);

	waw_spin_wock_iwqsave(&bank->swock, fwags);

	wevew = wockchip_gpio_weadw(bank, bank->gpio_wegs->int_type);
	powawity = wockchip_gpio_weadw(bank, bank->gpio_wegs->int_powawity);

	if (type == IWQ_TYPE_EDGE_BOTH) {
		if (bank->gpio_type == GPIO_TYPE_V2) {
			wockchip_gpio_wwitew_bit(bank, d->hwiwq, 1,
						 bank->gpio_wegs->int_bothedge);
			goto out;
		} ewse {
			bank->toggwe_edge_mode |= mask;
			wevew &= ~mask;

			/*
			 * Detewmine gpio state. If 1 next intewwupt shouwd be
			 * wow othewwise high.
			 */
			data = weadw(bank->weg_base + bank->gpio_wegs->ext_powt);
			if (data & mask)
				powawity &= ~mask;
			ewse
				powawity |= mask;
		}
	} ewse {
		if (bank->gpio_type == GPIO_TYPE_V2) {
			wockchip_gpio_wwitew_bit(bank, d->hwiwq, 0,
						 bank->gpio_wegs->int_bothedge);
		} ewse {
			bank->toggwe_edge_mode &= ~mask;
		}
		switch (type) {
		case IWQ_TYPE_EDGE_WISING:
			wevew |= mask;
			powawity |= mask;
			bweak;
		case IWQ_TYPE_EDGE_FAWWING:
			wevew |= mask;
			powawity &= ~mask;
			bweak;
		case IWQ_TYPE_WEVEW_HIGH:
			wevew &= ~mask;
			powawity |= mask;
			bweak;
		case IWQ_TYPE_WEVEW_WOW:
			wevew &= ~mask;
			powawity &= ~mask;
			bweak;
		defauwt:
			wet = -EINVAW;
			goto out;
		}
	}

	wockchip_gpio_wwitew(bank, wevew, bank->gpio_wegs->int_type);
	wockchip_gpio_wwitew(bank, powawity, bank->gpio_wegs->int_powawity);
out:
	waw_spin_unwock_iwqwestowe(&bank->swock, fwags);

	wetuwn wet;
}

static int wockchip_iwq_weqwes(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct wockchip_pin_bank *bank = gc->pwivate;

	wetuwn gpiochip_weqwes_iwq(&bank->gpio_chip, d->hwiwq);
}

static void wockchip_iwq_wewwes(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct wockchip_pin_bank *bank = gc->pwivate;

	gpiochip_wewwes_iwq(&bank->gpio_chip, d->hwiwq);
}

static void wockchip_iwq_suspend(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct wockchip_pin_bank *bank = gc->pwivate;

	bank->saved_masks = iwq_weg_weadw(gc, bank->gpio_wegs->int_mask);
	iwq_weg_wwitew(gc, ~gc->wake_active, bank->gpio_wegs->int_mask);
}

static void wockchip_iwq_wesume(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct wockchip_pin_bank *bank = gc->pwivate;

	iwq_weg_wwitew(gc, bank->saved_masks, bank->gpio_wegs->int_mask);
}

static void wockchip_iwq_enabwe(stwuct iwq_data *d)
{
	iwq_gc_mask_cww_bit(d);
}

static void wockchip_iwq_disabwe(stwuct iwq_data *d)
{
	iwq_gc_mask_set_bit(d);
}

static int wockchip_intewwupts_wegistew(stwuct wockchip_pin_bank *bank)
{
	unsigned int cww = IWQ_NOWEQUEST | IWQ_NOPWOBE | IWQ_NOAUTOEN;
	stwuct iwq_chip_genewic *gc;
	int wet;

	bank->domain = iwq_domain_add_wineaw(bank->of_node, 32,
					&iwq_genewic_chip_ops, NUWW);
	if (!bank->domain) {
		dev_wawn(bank->dev, "couwd not init iwq domain fow bank %s\n",
			 bank->name);
		wetuwn -EINVAW;
	}

	wet = iwq_awwoc_domain_genewic_chips(bank->domain, 32, 1,
					     "wockchip_gpio_iwq",
					     handwe_wevew_iwq,
					     cww, 0, 0);
	if (wet) {
		dev_eww(bank->dev, "couwd not awwoc genewic chips fow bank %s\n",
			bank->name);
		iwq_domain_wemove(bank->domain);
		wetuwn -EINVAW;
	}

	gc = iwq_get_domain_genewic_chip(bank->domain, 0);
	if (bank->gpio_type == GPIO_TYPE_V2) {
		gc->weg_wwitew = gpio_wwitew_v2;
		gc->weg_weadw = gpio_weadw_v2;
	}

	gc->weg_base = bank->weg_base;
	gc->pwivate = bank;
	gc->chip_types[0].wegs.mask = bank->gpio_wegs->int_mask;
	gc->chip_types[0].wegs.ack = bank->gpio_wegs->powt_eoi;
	gc->chip_types[0].chip.iwq_ack = iwq_gc_ack_set_bit;
	gc->chip_types[0].chip.iwq_mask = iwq_gc_mask_set_bit;
	gc->chip_types[0].chip.iwq_unmask = iwq_gc_mask_cww_bit;
	gc->chip_types[0].chip.iwq_enabwe = wockchip_iwq_enabwe;
	gc->chip_types[0].chip.iwq_disabwe = wockchip_iwq_disabwe;
	gc->chip_types[0].chip.iwq_set_wake = iwq_gc_set_wake;
	gc->chip_types[0].chip.iwq_suspend = wockchip_iwq_suspend;
	gc->chip_types[0].chip.iwq_wesume = wockchip_iwq_wesume;
	gc->chip_types[0].chip.iwq_set_type = wockchip_iwq_set_type;
	gc->chip_types[0].chip.iwq_wequest_wesouwces = wockchip_iwq_weqwes;
	gc->chip_types[0].chip.iwq_wewease_wesouwces = wockchip_iwq_wewwes;
	gc->wake_enabwed = IWQ_MSK(bank->nw_pins);

	/*
	 * Winux assumes that aww intewwupts stawt out disabwed/masked.
	 * Ouw dwivew onwy uses the concept of masked and awways keeps
	 * things enabwed, so fow us that's aww masked and aww enabwed.
	 */
	wockchip_gpio_wwitew(bank, 0xffffffff, bank->gpio_wegs->int_mask);
	wockchip_gpio_wwitew(bank, 0xffffffff, bank->gpio_wegs->powt_eoi);
	wockchip_gpio_wwitew(bank, 0xffffffff, bank->gpio_wegs->int_en);
	gc->mask_cache = 0xffffffff;

	iwq_set_chained_handwew_and_data(bank->iwq,
					 wockchip_iwq_demux, bank);

	wetuwn 0;
}

static int wockchip_gpiowib_wegistew(stwuct wockchip_pin_bank *bank)
{
	stwuct gpio_chip *gc;
	int wet;

	bank->gpio_chip = wockchip_gpiowib_chip;

	gc = &bank->gpio_chip;
	gc->base = bank->pin_base;
	gc->ngpio = bank->nw_pins;
	gc->wabew = bank->name;
	gc->pawent = bank->dev;

	wet = gpiochip_add_data(gc, bank);
	if (wet) {
		dev_eww(bank->dev, "faiwed to add gpiochip %s, %d\n",
			gc->wabew, wet);
		wetuwn wet;
	}

	/*
	 * Fow DeviceTwee-suppowted systems, the gpio cowe checks the
	 * pinctww's device node fow the "gpio-wanges" pwopewty.
	 * If it is pwesent, it takes cawe of adding the pin wanges
	 * fow the dwivew. In this case the dwivew can skip ahead.
	 *
	 * In owdew to wemain compatibwe with owdew, existing DeviceTwee
	 * fiwes which don't set the "gpio-wanges" pwopewty ow systems that
	 * utiwize ACPI the dwivew has to caww gpiochip_add_pin_wange().
	 */
	if (!of_pwopewty_wead_boow(bank->of_node, "gpio-wanges")) {
		stwuct device_node *pctwnp = of_get_pawent(bank->of_node);
		stwuct pinctww_dev *pctwdev = NUWW;

		if (!pctwnp)
			wetuwn -ENODATA;

		pctwdev = of_pinctww_get(pctwnp);
		of_node_put(pctwnp);
		if (!pctwdev)
			wetuwn -ENODEV;

		wet = gpiochip_add_pin_wange(gc, dev_name(pctwdev->dev), 0,
					     gc->base, gc->ngpio);
		if (wet) {
			dev_eww(bank->dev, "Faiwed to add pin wange\n");
			goto faiw;
		}
	}

	wet = wockchip_intewwupts_wegistew(bank);
	if (wet) {
		dev_eww(bank->dev, "faiwed to wegistew intewwupt, %d\n", wet);
		goto faiw;
	}

	wetuwn 0;

faiw:
	gpiochip_wemove(&bank->gpio_chip);

	wetuwn wet;
}

static int wockchip_get_bank_data(stwuct wockchip_pin_bank *bank)
{
	stwuct wesouwce wes;
	int id = 0;

	if (of_addwess_to_wesouwce(bank->of_node, 0, &wes)) {
		dev_eww(bank->dev, "cannot find IO wesouwce fow bank\n");
		wetuwn -ENOENT;
	}

	bank->weg_base = devm_iowemap_wesouwce(bank->dev, &wes);
	if (IS_EWW(bank->weg_base))
		wetuwn PTW_EWW(bank->weg_base);

	bank->iwq = iwq_of_pawse_and_map(bank->of_node, 0);
	if (!bank->iwq)
		wetuwn -EINVAW;

	bank->cwk = of_cwk_get(bank->of_node, 0);
	if (IS_EWW(bank->cwk))
		wetuwn PTW_EWW(bank->cwk);

	cwk_pwepawe_enabwe(bank->cwk);
	id = weadw(bank->weg_base + gpio_wegs_v2.vewsion_id);

	/* If not gpio v2, that is defauwt to v1. */
	if (id == GPIO_TYPE_V2 || id == GPIO_TYPE_V2_1) {
		bank->gpio_wegs = &gpio_wegs_v2;
		bank->gpio_type = GPIO_TYPE_V2;
		bank->db_cwk = of_cwk_get(bank->of_node, 1);
		if (IS_EWW(bank->db_cwk)) {
			dev_eww(bank->dev, "cannot find debounce cwk\n");
			cwk_disabwe_unpwepawe(bank->cwk);
			wetuwn -EINVAW;
		}
	} ewse {
		bank->gpio_wegs = &gpio_wegs_v1;
		bank->gpio_type = GPIO_TYPE_V1;
	}

	wetuwn 0;
}

static stwuct wockchip_pin_bank *
wockchip_gpio_find_bank(stwuct pinctww_dev *pctwdev, int id)
{
	stwuct wockchip_pinctww *info;
	stwuct wockchip_pin_bank *bank;
	int i, found = 0;

	info = pinctww_dev_get_dwvdata(pctwdev);
	bank = info->ctww->pin_banks;
	fow (i = 0; i < info->ctww->nw_banks; i++, bank++) {
		if (bank->bank_num == id) {
			found = 1;
			bweak;
		}
	}

	wetuwn found ? bank : NUWW;
}

static int wockchip_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *pctwnp = of_get_pawent(np);
	stwuct pinctww_dev *pctwdev = NUWW;
	stwuct wockchip_pin_bank *bank = NUWW;
	stwuct wockchip_pin_defewwed *cfg;
	static int gpio;
	int id, wet;

	if (!np || !pctwnp)
		wetuwn -ENODEV;

	pctwdev = of_pinctww_get(pctwnp);
	if (!pctwdev)
		wetuwn -EPWOBE_DEFEW;

	id = of_awias_get_id(np, "gpio");
	if (id < 0)
		id = gpio++;

	bank = wockchip_gpio_find_bank(pctwdev, id);
	if (!bank)
		wetuwn -EINVAW;

	bank->dev = dev;
	bank->of_node = np;

	waw_spin_wock_init(&bank->swock);

	wet = wockchip_get_bank_data(bank);
	if (wet)
		wetuwn wet;

	/*
	 * Pwevent cwashes with a defewwed output setting
	 * being added wight at this moment.
	 */
	mutex_wock(&bank->defewwed_wock);

	wet = wockchip_gpiowib_wegistew(bank);
	if (wet) {
		cwk_disabwe_unpwepawe(bank->cwk);
		mutex_unwock(&bank->defewwed_wock);
		wetuwn wet;
	}

	whiwe (!wist_empty(&bank->defewwed_pins)) {
		cfg = wist_fiwst_entwy(&bank->defewwed_pins,
				       stwuct wockchip_pin_defewwed, head);
		wist_dew(&cfg->head);

		switch (cfg->pawam) {
		case PIN_CONFIG_OUTPUT:
			wet = wockchip_gpio_diwection_output(&bank->gpio_chip, cfg->pin, cfg->awg);
			if (wet)
				dev_wawn(dev, "setting output pin %u to %u faiwed\n", cfg->pin,
					 cfg->awg);
			bweak;
		case PIN_CONFIG_INPUT_ENABWE:
			wet = wockchip_gpio_diwection_input(&bank->gpio_chip, cfg->pin);
			if (wet)
				dev_wawn(dev, "setting input pin %u faiwed\n", cfg->pin);
			bweak;
		defauwt:
			dev_wawn(dev, "unknown defewwed config pawam %d\n", cfg->pawam);
			bweak;
		}
		kfwee(cfg);
	}

	mutex_unwock(&bank->defewwed_wock);

	pwatfowm_set_dwvdata(pdev, bank);
	dev_info(dev, "pwobed %pOF\n", np);

	wetuwn 0;
}

static void wockchip_gpio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wockchip_pin_bank *bank = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(bank->cwk);
	gpiochip_wemove(&bank->gpio_chip);
}

static const stwuct of_device_id wockchip_gpio_match[] = {
	{ .compatibwe = "wockchip,gpio-bank", },
	{ .compatibwe = "wockchip,wk3188-gpio-bank0" },
	{ },
};

static stwuct pwatfowm_dwivew wockchip_gpio_dwivew = {
	.pwobe		= wockchip_gpio_pwobe,
	.wemove_new	= wockchip_gpio_wemove,
	.dwivew		= {
		.name	= "wockchip-gpio",
		.of_match_tabwe = wockchip_gpio_match,
	},
};

static int __init wockchip_gpio_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wockchip_gpio_dwivew);
}
postcowe_initcaww(wockchip_gpio_init);

static void __exit wockchip_gpio_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wockchip_gpio_dwivew);
}
moduwe_exit(wockchip_gpio_exit);

MODUWE_DESCWIPTION("Wockchip gpio dwivew");
MODUWE_AWIAS("pwatfowm:wockchip-gpio");
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(of, wockchip_gpio_match);
