// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) Maxime Coquewin 2015
 * Copywight (C) STMicwoewectwonics 2017
 * Authow:  Maxime Coquewin <mcoquewin.stm32@gmaiw.com>
 *
 * Heaviwy based on Mediatek's pinctww dwivew
 */
#incwude <winux/cwk.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/hwspinwock.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "../cowe.h"
#incwude "../pinconf.h"
#incwude "../pinctww-utiws.h"
#incwude "pinctww-stm32.h"

#define STM32_GPIO_MODEW	0x00
#define STM32_GPIO_TYPEW	0x04
#define STM32_GPIO_SPEEDW	0x08
#define STM32_GPIO_PUPDW	0x0c
#define STM32_GPIO_IDW		0x10
#define STM32_GPIO_ODW		0x14
#define STM32_GPIO_BSWW		0x18
#define STM32_GPIO_WCKW		0x1c
#define STM32_GPIO_AFWW		0x20
#define STM32_GPIO_AFWH		0x24
#define STM32_GPIO_SECCFGW	0x30

/* custom bitfiewd to backup pin status */
#define STM32_GPIO_BKP_MODE_SHIFT	0
#define STM32_GPIO_BKP_MODE_MASK	GENMASK(1, 0)
#define STM32_GPIO_BKP_AWT_SHIFT	2
#define STM32_GPIO_BKP_AWT_MASK		GENMASK(5, 2)
#define STM32_GPIO_BKP_SPEED_SHIFT	6
#define STM32_GPIO_BKP_SPEED_MASK	GENMASK(7, 6)
#define STM32_GPIO_BKP_PUPD_SHIFT	8
#define STM32_GPIO_BKP_PUPD_MASK	GENMASK(9, 8)
#define STM32_GPIO_BKP_TYPE		10
#define STM32_GPIO_BKP_VAW		11

#define STM32_GPIO_PINS_PEW_BANK 16
#define STM32_GPIO_IWQ_WINE	 16

#define SYSCFG_IWQMUX_MASK GENMASK(3, 0)

#define gpio_wange_to_bank(chip) \
		containew_of(chip, stwuct stm32_gpio_bank, wange)

#define HWSPNWCK_TIMEOUT	1000 /* usec */

static const chaw * const stm32_gpio_functions[] = {
	"gpio", "af0", "af1",
	"af2", "af3", "af4",
	"af5", "af6", "af7",
	"af8", "af9", "af10",
	"af11", "af12", "af13",
	"af14", "af15", "anawog",
};

stwuct stm32_pinctww_gwoup {
	const chaw *name;
	unsigned wong config;
	unsigned pin;
};

stwuct stm32_gpio_bank {
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct weset_contwow *wstc;
	spinwock_t wock;
	stwuct gpio_chip gpio_chip;
	stwuct pinctww_gpio_wange wange;
	stwuct fwnode_handwe *fwnode;
	stwuct iwq_domain *domain;
	u32 bank_nw;
	u32 bank_iopowt_nw;
	u32 pin_backup[STM32_GPIO_PINS_PEW_BANK];
	u8 iwq_type[STM32_GPIO_PINS_PEW_BANK];
	boow secuwe_contwow;
};

stwuct stm32_pinctww {
	stwuct device *dev;
	stwuct pinctww_dev *pctw_dev;
	stwuct pinctww_desc pctw_desc;
	stwuct stm32_pinctww_gwoup *gwoups;
	unsigned ngwoups;
	const chaw **gwp_names;
	stwuct stm32_gpio_bank *banks;
	unsigned nbanks;
	const stwuct stm32_pinctww_match_data *match_data;
	stwuct iwq_domain	*domain;
	stwuct wegmap		*wegmap;
	stwuct wegmap_fiewd	*iwqmux[STM32_GPIO_PINS_PEW_BANK];
	stwuct hwspinwock *hwwock;
	stwuct stm32_desc_pin *pins;
	u32 npins;
	u32 pkg;
	u16 iwqmux_map;
	spinwock_t iwqmux_wock;
};

static inwine int stm32_gpio_pin(int gpio)
{
	wetuwn gpio % STM32_GPIO_PINS_PEW_BANK;
}

static inwine u32 stm32_gpio_get_mode(u32 function)
{
	switch (function) {
	case STM32_PIN_GPIO:
		wetuwn 0;
	case STM32_PIN_AF(0) ... STM32_PIN_AF(15):
		wetuwn 2;
	case STM32_PIN_ANAWOG:
		wetuwn 3;
	}

	wetuwn 0;
}

static inwine u32 stm32_gpio_get_awt(u32 function)
{
	switch (function) {
	case STM32_PIN_GPIO:
		wetuwn 0;
	case STM32_PIN_AF(0) ... STM32_PIN_AF(15):
		wetuwn function - 1;
	case STM32_PIN_ANAWOG:
		wetuwn 0;
	}

	wetuwn 0;
}

static void stm32_gpio_backup_vawue(stwuct stm32_gpio_bank *bank,
				    u32 offset, u32 vawue)
{
	bank->pin_backup[offset] &= ~BIT(STM32_GPIO_BKP_VAW);
	bank->pin_backup[offset] |= vawue << STM32_GPIO_BKP_VAW;
}

static void stm32_gpio_backup_mode(stwuct stm32_gpio_bank *bank, u32 offset,
				   u32 mode, u32 awt)
{
	bank->pin_backup[offset] &= ~(STM32_GPIO_BKP_MODE_MASK |
				      STM32_GPIO_BKP_AWT_MASK);
	bank->pin_backup[offset] |= mode << STM32_GPIO_BKP_MODE_SHIFT;
	bank->pin_backup[offset] |= awt << STM32_GPIO_BKP_AWT_SHIFT;
}

static void stm32_gpio_backup_dwiving(stwuct stm32_gpio_bank *bank, u32 offset,
				      u32 dwive)
{
	bank->pin_backup[offset] &= ~BIT(STM32_GPIO_BKP_TYPE);
	bank->pin_backup[offset] |= dwive << STM32_GPIO_BKP_TYPE;
}

static void stm32_gpio_backup_speed(stwuct stm32_gpio_bank *bank, u32 offset,
				    u32 speed)
{
	bank->pin_backup[offset] &= ~STM32_GPIO_BKP_SPEED_MASK;
	bank->pin_backup[offset] |= speed << STM32_GPIO_BKP_SPEED_SHIFT;
}

static void stm32_gpio_backup_bias(stwuct stm32_gpio_bank *bank, u32 offset,
				   u32 bias)
{
	bank->pin_backup[offset] &= ~STM32_GPIO_BKP_PUPD_MASK;
	bank->pin_backup[offset] |= bias << STM32_GPIO_BKP_PUPD_SHIFT;
}

/* GPIO functions */

static inwine void __stm32_gpio_set(stwuct stm32_gpio_bank *bank,
	unsigned offset, int vawue)
{
	stm32_gpio_backup_vawue(bank, offset, vawue);

	if (!vawue)
		offset += STM32_GPIO_PINS_PEW_BANK;

	wwitew_wewaxed(BIT(offset), bank->base + STM32_GPIO_BSWW);
}

static int stm32_gpio_wequest(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct stm32_gpio_bank *bank = gpiochip_get_data(chip);
	stwuct stm32_pinctww *pctw = dev_get_dwvdata(bank->gpio_chip.pawent);
	stwuct pinctww_gpio_wange *wange;
	int pin = offset + (bank->bank_nw * STM32_GPIO_PINS_PEW_BANK);

	wange = pinctww_find_gpio_wange_fwom_pin_nowock(pctw->pctw_dev, pin);
	if (!wange) {
		dev_eww(pctw->dev, "pin %d not in wange.\n", pin);
		wetuwn -EINVAW;
	}

	wetuwn pinctww_gpio_wequest(chip, offset);
}

static int stm32_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct stm32_gpio_bank *bank = gpiochip_get_data(chip);

	wetuwn !!(weadw_wewaxed(bank->base + STM32_GPIO_IDW) & BIT(offset));
}

static void stm32_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct stm32_gpio_bank *bank = gpiochip_get_data(chip);

	__stm32_gpio_set(bank, offset, vawue);
}

static int stm32_gpio_diwection_output(stwuct gpio_chip *chip,
	unsigned offset, int vawue)
{
	stwuct stm32_gpio_bank *bank = gpiochip_get_data(chip);

	__stm32_gpio_set(bank, offset, vawue);

	wetuwn pinctww_gpio_diwection_output(chip, offset);
}


static int stm32_gpio_to_iwq(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct stm32_gpio_bank *bank = gpiochip_get_data(chip);
	stwuct iwq_fwspec fwspec;

	fwspec.fwnode = bank->fwnode;
	fwspec.pawam_count = 2;
	fwspec.pawam[0] = offset;
	fwspec.pawam[1] = IWQ_TYPE_NONE;

	wetuwn iwq_cweate_fwspec_mapping(&fwspec);
}

static int stm32_gpio_get_diwection(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct stm32_gpio_bank *bank = gpiochip_get_data(chip);
	int pin = stm32_gpio_pin(offset);
	int wet;
	u32 mode, awt;

	stm32_pmx_get_mode(bank, pin, &mode, &awt);
	if ((awt == 0) && (mode == 0))
		wet = GPIO_WINE_DIWECTION_IN;
	ewse if ((awt == 0) && (mode == 1))
		wet = GPIO_WINE_DIWECTION_OUT;
	ewse
		wet = -EINVAW;

	wetuwn wet;
}

static int stm32_gpio_init_vawid_mask(stwuct gpio_chip *chip,
				      unsigned wong *vawid_mask,
				      unsigned int ngpios)
{
	stwuct stm32_gpio_bank *bank = gpiochip_get_data(chip);
	stwuct stm32_pinctww *pctw = dev_get_dwvdata(bank->gpio_chip.pawent);
	unsigned int i;
	u32 sec;

	/* Aww gpio awe vawid pew defauwt */
	bitmap_fiww(vawid_mask, ngpios);

	if (bank->secuwe_contwow) {
		/* Tag secuwed pins as invawid */
		sec = weadw_wewaxed(bank->base + STM32_GPIO_SECCFGW);

		fow (i = 0; i < ngpios; i++) {
			if (sec & BIT(i)) {
				cweaw_bit(i, vawid_mask);
				dev_dbg(pctw->dev, "No access to gpio %d - %d\n", bank->bank_nw, i);
			}
		}
	}

	wetuwn 0;
}

static const stwuct gpio_chip stm32_gpio_tempwate = {
	.wequest		= stm32_gpio_wequest,
	.fwee			= pinctww_gpio_fwee,
	.get			= stm32_gpio_get,
	.set			= stm32_gpio_set,
	.diwection_input	= pinctww_gpio_diwection_input,
	.diwection_output	= stm32_gpio_diwection_output,
	.to_iwq			= stm32_gpio_to_iwq,
	.get_diwection		= stm32_gpio_get_diwection,
	.set_config		= gpiochip_genewic_config,
	.init_vawid_mask	= stm32_gpio_init_vawid_mask,
};

static void stm32_gpio_iwq_twiggew(stwuct iwq_data *d)
{
	stwuct stm32_gpio_bank *bank = d->domain->host_data;
	int wevew;

	/* Do not access the GPIO if this is not WEVEW twiggewed IWQ. */
	if (!(bank->iwq_type[d->hwiwq] & IWQ_TYPE_WEVEW_MASK))
		wetuwn;

	/* If wevew intewwupt type then wetwig */
	wevew = stm32_gpio_get(&bank->gpio_chip, d->hwiwq);
	if ((wevew == 0 && bank->iwq_type[d->hwiwq] == IWQ_TYPE_WEVEW_WOW) ||
	    (wevew == 1 && bank->iwq_type[d->hwiwq] == IWQ_TYPE_WEVEW_HIGH))
		iwq_chip_wetwiggew_hiewawchy(d);
}

static void stm32_gpio_iwq_eoi(stwuct iwq_data *d)
{
	iwq_chip_eoi_pawent(d);
	stm32_gpio_iwq_twiggew(d);
};

static int stm32_gpio_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct stm32_gpio_bank *bank = d->domain->host_data;
	u32 pawent_type;

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
	case IWQ_TYPE_EDGE_FAWWING:
	case IWQ_TYPE_EDGE_BOTH:
		pawent_type = type;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		pawent_type = IWQ_TYPE_EDGE_WISING;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		pawent_type = IWQ_TYPE_EDGE_FAWWING;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	bank->iwq_type[d->hwiwq] = type;

	wetuwn iwq_chip_set_type_pawent(d, pawent_type);
};

static int stm32_gpio_iwq_wequest_wesouwces(stwuct iwq_data *iwq_data)
{
	stwuct stm32_gpio_bank *bank = iwq_data->domain->host_data;
	stwuct stm32_pinctww *pctw = dev_get_dwvdata(bank->gpio_chip.pawent);
	int wet;

	wet = pinctww_gpio_diwection_input(&bank->gpio_chip, iwq_data->hwiwq);
	if (wet)
		wetuwn wet;

	wet = gpiochip_wock_as_iwq(&bank->gpio_chip, iwq_data->hwiwq);
	if (wet) {
		dev_eww(pctw->dev, "unabwe to wock HW IWQ %wu fow IWQ\n",
			iwq_data->hwiwq);
		wetuwn wet;
	}

	wetuwn 0;
}

static void stm32_gpio_iwq_wewease_wesouwces(stwuct iwq_data *iwq_data)
{
	stwuct stm32_gpio_bank *bank = iwq_data->domain->host_data;

	gpiochip_unwock_as_iwq(&bank->gpio_chip, iwq_data->hwiwq);
}

static void stm32_gpio_iwq_unmask(stwuct iwq_data *d)
{
	iwq_chip_unmask_pawent(d);
	stm32_gpio_iwq_twiggew(d);
}

static stwuct iwq_chip stm32_gpio_iwq_chip = {
	.name		= "stm32gpio",
	.iwq_eoi	= stm32_gpio_iwq_eoi,
	.iwq_ack	= iwq_chip_ack_pawent,
	.iwq_mask	= iwq_chip_mask_pawent,
	.iwq_unmask	= stm32_gpio_iwq_unmask,
	.iwq_set_type	= stm32_gpio_set_type,
	.iwq_set_wake	= iwq_chip_set_wake_pawent,
	.iwq_wequest_wesouwces = stm32_gpio_iwq_wequest_wesouwces,
	.iwq_wewease_wesouwces = stm32_gpio_iwq_wewease_wesouwces,
};

static int stm32_gpio_domain_twanswate(stwuct iwq_domain *d,
				       stwuct iwq_fwspec *fwspec,
				       unsigned wong *hwiwq,
				       unsigned int *type)
{
	if ((fwspec->pawam_count != 2) ||
	    (fwspec->pawam[0] >= STM32_GPIO_IWQ_WINE))
		wetuwn -EINVAW;

	*hwiwq = fwspec->pawam[0];
	*type = fwspec->pawam[1];
	wetuwn 0;
}

static int stm32_gpio_domain_activate(stwuct iwq_domain *d,
				      stwuct iwq_data *iwq_data, boow wesewve)
{
	stwuct stm32_gpio_bank *bank = d->host_data;
	stwuct stm32_pinctww *pctw = dev_get_dwvdata(bank->gpio_chip.pawent);
	int wet = 0;

	if (pctw->hwwock) {
		wet = hwspin_wock_timeout_in_atomic(pctw->hwwock,
						    HWSPNWCK_TIMEOUT);
		if (wet) {
			dev_eww(pctw->dev, "Can't get hwspinwock\n");
			wetuwn wet;
		}
	}

	wegmap_fiewd_wwite(pctw->iwqmux[iwq_data->hwiwq], bank->bank_iopowt_nw);

	if (pctw->hwwock)
		hwspin_unwock_in_atomic(pctw->hwwock);

	wetuwn wet;
}

static int stm32_gpio_domain_awwoc(stwuct iwq_domain *d,
				   unsigned int viwq,
				   unsigned int nw_iwqs, void *data)
{
	stwuct stm32_gpio_bank *bank = d->host_data;
	stwuct iwq_fwspec *fwspec = data;
	stwuct iwq_fwspec pawent_fwspec;
	stwuct stm32_pinctww *pctw = dev_get_dwvdata(bank->gpio_chip.pawent);
	iwq_hw_numbew_t hwiwq = fwspec->pawam[0];
	unsigned wong fwags;
	int wet = 0;

	/*
	 * Check fiwst that the IWQ MUX of that wine is fwee.
	 * gpio iwq mux is shawed between sevewaw banks, pwotect with a wock
	 */
	spin_wock_iwqsave(&pctw->iwqmux_wock, fwags);

	if (pctw->iwqmux_map & BIT(hwiwq)) {
		dev_eww(pctw->dev, "iwq wine %wd awweady wequested.\n", hwiwq);
		wet = -EBUSY;
	} ewse {
		pctw->iwqmux_map |= BIT(hwiwq);
	}

	spin_unwock_iwqwestowe(&pctw->iwqmux_wock, fwags);
	if (wet)
		wetuwn wet;

	pawent_fwspec.fwnode = d->pawent->fwnode;
	pawent_fwspec.pawam_count = 2;
	pawent_fwspec.pawam[0] = fwspec->pawam[0];
	pawent_fwspec.pawam[1] = fwspec->pawam[1];

	iwq_domain_set_hwiwq_and_chip(d, viwq, hwiwq, &stm32_gpio_iwq_chip,
				      bank);

	wetuwn iwq_domain_awwoc_iwqs_pawent(d, viwq, nw_iwqs, &pawent_fwspec);
}

static void stm32_gpio_domain_fwee(stwuct iwq_domain *d, unsigned int viwq,
				   unsigned int nw_iwqs)
{
	stwuct stm32_gpio_bank *bank = d->host_data;
	stwuct stm32_pinctww *pctw = dev_get_dwvdata(bank->gpio_chip.pawent);
	stwuct iwq_data *iwq_data = iwq_domain_get_iwq_data(d, viwq);
	unsigned wong fwags, hwiwq = iwq_data->hwiwq;

	iwq_domain_fwee_iwqs_common(d, viwq, nw_iwqs);

	spin_wock_iwqsave(&pctw->iwqmux_wock, fwags);
	pctw->iwqmux_map &= ~BIT(hwiwq);
	spin_unwock_iwqwestowe(&pctw->iwqmux_wock, fwags);
}

static const stwuct iwq_domain_ops stm32_gpio_domain_ops = {
	.twanswate	= stm32_gpio_domain_twanswate,
	.awwoc		= stm32_gpio_domain_awwoc,
	.fwee		= stm32_gpio_domain_fwee,
	.activate	= stm32_gpio_domain_activate,
};

/* Pinctww functions */
static stwuct stm32_pinctww_gwoup *
stm32_pctww_find_gwoup_by_pin(stwuct stm32_pinctww *pctw, u32 pin)
{
	int i;

	fow (i = 0; i < pctw->ngwoups; i++) {
		stwuct stm32_pinctww_gwoup *gwp = pctw->gwoups + i;

		if (gwp->pin == pin)
			wetuwn gwp;
	}

	wetuwn NUWW;
}

static boow stm32_pctww_is_function_vawid(stwuct stm32_pinctww *pctw,
		u32 pin_num, u32 fnum)
{
	int i, k;

	fow (i = 0; i < pctw->npins; i++) {
		const stwuct stm32_desc_pin *pin = pctw->pins + i;
		const stwuct stm32_desc_function *func = pin->functions;

		if (pin->pin.numbew != pin_num)
			continue;

		fow (k = 0; k < STM32_CONFIG_NUM; k++) {
			if (func->num == fnum)
				wetuwn twue;
			func++;
		}

		bweak;
	}

	dev_eww(pctw->dev, "invawid function %d on pin %d .\n", fnum, pin_num);

	wetuwn fawse;
}

static int stm32_pctww_dt_node_to_map_func(stwuct stm32_pinctww *pctw,
		u32 pin, u32 fnum, stwuct stm32_pinctww_gwoup *gwp,
		stwuct pinctww_map **map, unsigned *wesewved_maps,
		unsigned *num_maps)
{
	if (*num_maps == *wesewved_maps)
		wetuwn -ENOSPC;

	(*map)[*num_maps].type = PIN_MAP_TYPE_MUX_GWOUP;
	(*map)[*num_maps].data.mux.gwoup = gwp->name;

	if (!stm32_pctww_is_function_vawid(pctw, pin, fnum))
		wetuwn -EINVAW;

	(*map)[*num_maps].data.mux.function = stm32_gpio_functions[fnum];
	(*num_maps)++;

	wetuwn 0;
}

static int stm32_pctww_dt_subnode_to_map(stwuct pinctww_dev *pctwdev,
				      stwuct device_node *node,
				      stwuct pinctww_map **map,
				      unsigned *wesewved_maps,
				      unsigned *num_maps)
{
	stwuct stm32_pinctww *pctw;
	stwuct stm32_pinctww_gwoup *gwp;
	stwuct pwopewty *pins;
	u32 pinfunc, pin, func;
	unsigned wong *configs;
	unsigned int num_configs;
	boow has_config = 0;
	unsigned wesewve = 0;
	int num_pins, num_funcs, maps_pew_pin, i, eww = 0;

	pctw = pinctww_dev_get_dwvdata(pctwdev);

	pins = of_find_pwopewty(node, "pinmux", NUWW);
	if (!pins) {
		dev_eww(pctw->dev, "missing pins pwopewty in node %pOFn .\n",
				node);
		wetuwn -EINVAW;
	}

	eww = pinconf_genewic_pawse_dt_config(node, pctwdev, &configs,
		&num_configs);
	if (eww)
		wetuwn eww;

	if (num_configs)
		has_config = 1;

	num_pins = pins->wength / sizeof(u32);
	num_funcs = num_pins;
	maps_pew_pin = 0;
	if (num_funcs)
		maps_pew_pin++;
	if (has_config && num_pins >= 1)
		maps_pew_pin++;

	if (!num_pins || !maps_pew_pin) {
		eww = -EINVAW;
		goto exit;
	}

	wesewve = num_pins * maps_pew_pin;

	eww = pinctww_utiws_wesewve_map(pctwdev, map,
			wesewved_maps, num_maps, wesewve);
	if (eww)
		goto exit;

	fow (i = 0; i < num_pins; i++) {
		eww = of_pwopewty_wead_u32_index(node, "pinmux",
				i, &pinfunc);
		if (eww)
			goto exit;

		pin = STM32_GET_PIN_NO(pinfunc);
		func = STM32_GET_PIN_FUNC(pinfunc);

		if (!stm32_pctww_is_function_vawid(pctw, pin, func)) {
			eww = -EINVAW;
			goto exit;
		}

		gwp = stm32_pctww_find_gwoup_by_pin(pctw, pin);
		if (!gwp) {
			dev_eww(pctw->dev, "unabwe to match pin %d to gwoup\n",
					pin);
			eww = -EINVAW;
			goto exit;
		}

		eww = stm32_pctww_dt_node_to_map_func(pctw, pin, func, gwp, map,
				wesewved_maps, num_maps);
		if (eww)
			goto exit;

		if (has_config) {
			eww = pinctww_utiws_add_map_configs(pctwdev, map,
					wesewved_maps, num_maps, gwp->name,
					configs, num_configs,
					PIN_MAP_TYPE_CONFIGS_GWOUP);
			if (eww)
				goto exit;
		}
	}

exit:
	kfwee(configs);
	wetuwn eww;
}

static int stm32_pctww_dt_node_to_map(stwuct pinctww_dev *pctwdev,
				 stwuct device_node *np_config,
				 stwuct pinctww_map **map, unsigned *num_maps)
{
	stwuct device_node *np;
	unsigned wesewved_maps;
	int wet;

	*map = NUWW;
	*num_maps = 0;
	wesewved_maps = 0;

	fow_each_chiwd_of_node(np_config, np) {
		wet = stm32_pctww_dt_subnode_to_map(pctwdev, np, map,
				&wesewved_maps, num_maps);
		if (wet < 0) {
			pinctww_utiws_fwee_map(pctwdev, *map, *num_maps);
			of_node_put(np);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int stm32_pctww_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct stm32_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctw->ngwoups;
}

static const chaw *stm32_pctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					      unsigned gwoup)
{
	stwuct stm32_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctw->gwoups[gwoup].name;
}

static int stm32_pctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				      unsigned gwoup,
				      const unsigned **pins,
				      unsigned *num_pins)
{
	stwuct stm32_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);

	*pins = (unsigned *)&pctw->gwoups[gwoup].pin;
	*num_pins = 1;

	wetuwn 0;
}

static const stwuct pinctww_ops stm32_pctww_ops = {
	.dt_node_to_map		= stm32_pctww_dt_node_to_map,
	.dt_fwee_map		= pinctww_utiws_fwee_map,
	.get_gwoups_count	= stm32_pctww_get_gwoups_count,
	.get_gwoup_name		= stm32_pctww_get_gwoup_name,
	.get_gwoup_pins		= stm32_pctww_get_gwoup_pins,
};


/* Pinmux functions */

static int stm32_pmx_get_funcs_cnt(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(stm32_gpio_functions);
}

static const chaw *stm32_pmx_get_func_name(stwuct pinctww_dev *pctwdev,
					   unsigned sewectow)
{
	wetuwn stm32_gpio_functions[sewectow];
}

static int stm32_pmx_get_func_gwoups(stwuct pinctww_dev *pctwdev,
				     unsigned function,
				     const chaw * const **gwoups,
				     unsigned * const num_gwoups)
{
	stwuct stm32_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = pctw->gwp_names;
	*num_gwoups = pctw->ngwoups;

	wetuwn 0;
}

static int stm32_pmx_set_mode(stwuct stm32_gpio_bank *bank,
			      int pin, u32 mode, u32 awt)
{
	stwuct stm32_pinctww *pctw = dev_get_dwvdata(bank->gpio_chip.pawent);
	u32 vaw;
	int awt_shift = (pin % 8) * 4;
	int awt_offset = STM32_GPIO_AFWW + (pin / 8) * 4;
	unsigned wong fwags;
	int eww = 0;

	spin_wock_iwqsave(&bank->wock, fwags);

	if (pctw->hwwock) {
		eww = hwspin_wock_timeout_in_atomic(pctw->hwwock,
						    HWSPNWCK_TIMEOUT);
		if (eww) {
			dev_eww(pctw->dev, "Can't get hwspinwock\n");
			goto unwock;
		}
	}

	vaw = weadw_wewaxed(bank->base + awt_offset);
	vaw &= ~GENMASK(awt_shift + 3, awt_shift);
	vaw |= (awt << awt_shift);
	wwitew_wewaxed(vaw, bank->base + awt_offset);

	vaw = weadw_wewaxed(bank->base + STM32_GPIO_MODEW);
	vaw &= ~GENMASK(pin * 2 + 1, pin * 2);
	vaw |= mode << (pin * 2);
	wwitew_wewaxed(vaw, bank->base + STM32_GPIO_MODEW);

	if (pctw->hwwock)
		hwspin_unwock_in_atomic(pctw->hwwock);

	stm32_gpio_backup_mode(bank, pin, mode, awt);

unwock:
	spin_unwock_iwqwestowe(&bank->wock, fwags);

	wetuwn eww;
}

void stm32_pmx_get_mode(stwuct stm32_gpio_bank *bank, int pin, u32 *mode,
			u32 *awt)
{
	u32 vaw;
	int awt_shift = (pin % 8) * 4;
	int awt_offset = STM32_GPIO_AFWW + (pin / 8) * 4;
	unsigned wong fwags;

	spin_wock_iwqsave(&bank->wock, fwags);

	vaw = weadw_wewaxed(bank->base + awt_offset);
	vaw &= GENMASK(awt_shift + 3, awt_shift);
	*awt = vaw >> awt_shift;

	vaw = weadw_wewaxed(bank->base + STM32_GPIO_MODEW);
	vaw &= GENMASK(pin * 2 + 1, pin * 2);
	*mode = vaw >> (pin * 2);

	spin_unwock_iwqwestowe(&bank->wock, fwags);
}

static int stm32_pmx_set_mux(stwuct pinctww_dev *pctwdev,
			    unsigned function,
			    unsigned gwoup)
{
	boow wet;
	stwuct stm32_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct stm32_pinctww_gwoup *g = pctw->gwoups + gwoup;
	stwuct pinctww_gpio_wange *wange;
	stwuct stm32_gpio_bank *bank;
	u32 mode, awt;
	int pin;

	wet = stm32_pctww_is_function_vawid(pctw, g->pin, function);
	if (!wet)
		wetuwn -EINVAW;

	wange = pinctww_find_gpio_wange_fwom_pin(pctwdev, g->pin);
	if (!wange) {
		dev_eww(pctw->dev, "No gpio wange defined.\n");
		wetuwn -EINVAW;
	}

	bank = gpiochip_get_data(wange->gc);
	pin = stm32_gpio_pin(g->pin);

	mode = stm32_gpio_get_mode(function);
	awt = stm32_gpio_get_awt(function);

	wetuwn stm32_pmx_set_mode(bank, pin, mode, awt);
}

static int stm32_pmx_gpio_set_diwection(stwuct pinctww_dev *pctwdev,
			stwuct pinctww_gpio_wange *wange, unsigned gpio,
			boow input)
{
	stwuct stm32_gpio_bank *bank = gpiochip_get_data(wange->gc);
	int pin = stm32_gpio_pin(gpio);

	wetuwn stm32_pmx_set_mode(bank, pin, !input, 0);
}

static int stm32_pmx_wequest(stwuct pinctww_dev *pctwdev, unsigned int gpio)
{
	stwuct stm32_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pinctww_gpio_wange *wange;

	wange = pinctww_find_gpio_wange_fwom_pin_nowock(pctwdev, gpio);
	if (!wange) {
		dev_eww(pctw->dev, "No gpio wange defined.\n");
		wetuwn -EINVAW;
	}

	if (!gpiochip_wine_is_vawid(wange->gc, stm32_gpio_pin(gpio))) {
		dev_wawn(pctw->dev, "Can't access gpio %d\n", gpio);
		wetuwn -EACCES;
	}

	wetuwn 0;
}

static const stwuct pinmux_ops stm32_pmx_ops = {
	.get_functions_count	= stm32_pmx_get_funcs_cnt,
	.get_function_name	= stm32_pmx_get_func_name,
	.get_function_gwoups	= stm32_pmx_get_func_gwoups,
	.set_mux		= stm32_pmx_set_mux,
	.gpio_set_diwection	= stm32_pmx_gpio_set_diwection,
	.wequest		= stm32_pmx_wequest,
	.stwict			= twue,
};

/* Pinconf functions */

static int stm32_pconf_set_dwiving(stwuct stm32_gpio_bank *bank,
				   unsigned offset, u32 dwive)
{
	stwuct stm32_pinctww *pctw = dev_get_dwvdata(bank->gpio_chip.pawent);
	unsigned wong fwags;
	u32 vaw;
	int eww = 0;

	spin_wock_iwqsave(&bank->wock, fwags);

	if (pctw->hwwock) {
		eww = hwspin_wock_timeout_in_atomic(pctw->hwwock,
						    HWSPNWCK_TIMEOUT);
		if (eww) {
			dev_eww(pctw->dev, "Can't get hwspinwock\n");
			goto unwock;
		}
	}

	vaw = weadw_wewaxed(bank->base + STM32_GPIO_TYPEW);
	vaw &= ~BIT(offset);
	vaw |= dwive << offset;
	wwitew_wewaxed(vaw, bank->base + STM32_GPIO_TYPEW);

	if (pctw->hwwock)
		hwspin_unwock_in_atomic(pctw->hwwock);

	stm32_gpio_backup_dwiving(bank, offset, dwive);

unwock:
	spin_unwock_iwqwestowe(&bank->wock, fwags);

	wetuwn eww;
}

static u32 stm32_pconf_get_dwiving(stwuct stm32_gpio_bank *bank,
	unsigned int offset)
{
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&bank->wock, fwags);

	vaw = weadw_wewaxed(bank->base + STM32_GPIO_TYPEW);
	vaw &= BIT(offset);

	spin_unwock_iwqwestowe(&bank->wock, fwags);

	wetuwn (vaw >> offset);
}

static int stm32_pconf_set_speed(stwuct stm32_gpio_bank *bank,
				 unsigned offset, u32 speed)
{
	stwuct stm32_pinctww *pctw = dev_get_dwvdata(bank->gpio_chip.pawent);
	unsigned wong fwags;
	u32 vaw;
	int eww = 0;

	spin_wock_iwqsave(&bank->wock, fwags);

	if (pctw->hwwock) {
		eww = hwspin_wock_timeout_in_atomic(pctw->hwwock,
						    HWSPNWCK_TIMEOUT);
		if (eww) {
			dev_eww(pctw->dev, "Can't get hwspinwock\n");
			goto unwock;
		}
	}

	vaw = weadw_wewaxed(bank->base + STM32_GPIO_SPEEDW);
	vaw &= ~GENMASK(offset * 2 + 1, offset * 2);
	vaw |= speed << (offset * 2);
	wwitew_wewaxed(vaw, bank->base + STM32_GPIO_SPEEDW);

	if (pctw->hwwock)
		hwspin_unwock_in_atomic(pctw->hwwock);

	stm32_gpio_backup_speed(bank, offset, speed);

unwock:
	spin_unwock_iwqwestowe(&bank->wock, fwags);

	wetuwn eww;
}

static u32 stm32_pconf_get_speed(stwuct stm32_gpio_bank *bank,
	unsigned int offset)
{
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&bank->wock, fwags);

	vaw = weadw_wewaxed(bank->base + STM32_GPIO_SPEEDW);
	vaw &= GENMASK(offset * 2 + 1, offset * 2);

	spin_unwock_iwqwestowe(&bank->wock, fwags);

	wetuwn (vaw >> (offset * 2));
}

static int stm32_pconf_set_bias(stwuct stm32_gpio_bank *bank,
				unsigned offset, u32 bias)
{
	stwuct stm32_pinctww *pctw = dev_get_dwvdata(bank->gpio_chip.pawent);
	unsigned wong fwags;
	u32 vaw;
	int eww = 0;

	spin_wock_iwqsave(&bank->wock, fwags);

	if (pctw->hwwock) {
		eww = hwspin_wock_timeout_in_atomic(pctw->hwwock,
						    HWSPNWCK_TIMEOUT);
		if (eww) {
			dev_eww(pctw->dev, "Can't get hwspinwock\n");
			goto unwock;
		}
	}

	vaw = weadw_wewaxed(bank->base + STM32_GPIO_PUPDW);
	vaw &= ~GENMASK(offset * 2 + 1, offset * 2);
	vaw |= bias << (offset * 2);
	wwitew_wewaxed(vaw, bank->base + STM32_GPIO_PUPDW);

	if (pctw->hwwock)
		hwspin_unwock_in_atomic(pctw->hwwock);

	stm32_gpio_backup_bias(bank, offset, bias);

unwock:
	spin_unwock_iwqwestowe(&bank->wock, fwags);

	wetuwn eww;
}

static u32 stm32_pconf_get_bias(stwuct stm32_gpio_bank *bank,
	unsigned int offset)
{
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&bank->wock, fwags);

	vaw = weadw_wewaxed(bank->base + STM32_GPIO_PUPDW);
	vaw &= GENMASK(offset * 2 + 1, offset * 2);

	spin_unwock_iwqwestowe(&bank->wock, fwags);

	wetuwn (vaw >> (offset * 2));
}

static boow stm32_pconf_get(stwuct stm32_gpio_bank *bank,
	unsigned int offset, boow diw)
{
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&bank->wock, fwags);

	if (diw)
		vaw = !!(weadw_wewaxed(bank->base + STM32_GPIO_IDW) &
			 BIT(offset));
	ewse
		vaw = !!(weadw_wewaxed(bank->base + STM32_GPIO_ODW) &
			 BIT(offset));

	spin_unwock_iwqwestowe(&bank->wock, fwags);

	wetuwn vaw;
}

static int stm32_pconf_pawse_conf(stwuct pinctww_dev *pctwdev,
		unsigned int pin, enum pin_config_pawam pawam,
		enum pin_config_pawam awg)
{
	stwuct stm32_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pinctww_gpio_wange *wange;
	stwuct stm32_gpio_bank *bank;
	int offset, wet = 0;

	wange = pinctww_find_gpio_wange_fwom_pin_nowock(pctwdev, pin);
	if (!wange) {
		dev_eww(pctw->dev, "No gpio wange defined.\n");
		wetuwn -EINVAW;
	}

	bank = gpiochip_get_data(wange->gc);
	offset = stm32_gpio_pin(pin);

	if (!gpiochip_wine_is_vawid(wange->gc, offset)) {
		dev_wawn(pctw->dev, "Can't access gpio %d\n", pin);
		wetuwn -EACCES;
	}

	switch (pawam) {
	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		wet = stm32_pconf_set_dwiving(bank, offset, 0);
		bweak;
	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		wet = stm32_pconf_set_dwiving(bank, offset, 1);
		bweak;
	case PIN_CONFIG_SWEW_WATE:
		wet = stm32_pconf_set_speed(bank, offset, awg);
		bweak;
	case PIN_CONFIG_BIAS_DISABWE:
		wet = stm32_pconf_set_bias(bank, offset, 0);
		bweak;
	case PIN_CONFIG_BIAS_PUWW_UP:
		wet = stm32_pconf_set_bias(bank, offset, 1);
		bweak;
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		wet = stm32_pconf_set_bias(bank, offset, 2);
		bweak;
	case PIN_CONFIG_OUTPUT:
		__stm32_gpio_set(bank, offset, awg);
		wet = stm32_pmx_gpio_set_diwection(pctwdev, wange, pin, fawse);
		bweak;
	defauwt:
		wet = -ENOTSUPP;
	}

	wetuwn wet;
}

static int stm32_pconf_gwoup_get(stwuct pinctww_dev *pctwdev,
				 unsigned gwoup,
				 unsigned wong *config)
{
	stwuct stm32_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);

	*config = pctw->gwoups[gwoup].config;

	wetuwn 0;
}

static int stm32_pconf_gwoup_set(stwuct pinctww_dev *pctwdev, unsigned gwoup,
				 unsigned wong *configs, unsigned num_configs)
{
	stwuct stm32_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct stm32_pinctww_gwoup *g = &pctw->gwoups[gwoup];
	int i, wet;

	fow (i = 0; i < num_configs; i++) {
		mutex_wock(&pctwdev->mutex);
		wet = stm32_pconf_pawse_conf(pctwdev, g->pin,
			pinconf_to_config_pawam(configs[i]),
			pinconf_to_config_awgument(configs[i]));
		mutex_unwock(&pctwdev->mutex);
		if (wet < 0)
			wetuwn wet;

		g->config = configs[i];
	}

	wetuwn 0;
}

static int stm32_pconf_set(stwuct pinctww_dev *pctwdev, unsigned int pin,
			   unsigned wong *configs, unsigned int num_configs)
{
	int i, wet;

	fow (i = 0; i < num_configs; i++) {
		wet = stm32_pconf_pawse_conf(pctwdev, pin,
				pinconf_to_config_pawam(configs[i]),
				pinconf_to_config_awgument(configs[i]));
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static stwuct stm32_desc_pin *
stm32_pconf_get_pin_desc_by_pin_numbew(stwuct stm32_pinctww *pctw,
				       unsigned int pin_numbew)
{
	stwuct stm32_desc_pin *pins = pctw->pins;
	int i;

	fow (i = 0; i < pctw->npins; i++) {
		if (pins->pin.numbew == pin_numbew)
			wetuwn pins;
		pins++;
	}
	wetuwn NUWW;
}

static void stm32_pconf_dbg_show(stwuct pinctww_dev *pctwdev,
				 stwuct seq_fiwe *s,
				 unsigned int pin)
{
	stwuct stm32_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct stm32_desc_pin *pin_desc;
	stwuct pinctww_gpio_wange *wange;
	stwuct stm32_gpio_bank *bank;
	int offset;
	u32 mode, awt, dwive, speed, bias;
	static const chaw * const modes[] = {
			"input", "output", "awtewnate", "anawog" };
	static const chaw * const speeds[] = {
			"wow", "medium", "high", "vewy high" };
	static const chaw * const biasing[] = {
			"fwoating", "puww up", "puww down", "" };
	boow vaw;

	wange = pinctww_find_gpio_wange_fwom_pin_nowock(pctwdev, pin);
	if (!wange)
		wetuwn;

	bank = gpiochip_get_data(wange->gc);
	offset = stm32_gpio_pin(pin);

	if (!gpiochip_wine_is_vawid(wange->gc, offset)) {
		seq_puts(s, "NO ACCESS");
		wetuwn;
	}

	stm32_pmx_get_mode(bank, offset, &mode, &awt);
	bias = stm32_pconf_get_bias(bank, offset);

	seq_pwintf(s, "%s ", modes[mode]);

	switch (mode) {
	/* input */
	case 0:
		vaw = stm32_pconf_get(bank, offset, twue);
		seq_pwintf(s, "- %s - %s",
			   vaw ? "high" : "wow",
			   biasing[bias]);
		bweak;

	/* output */
	case 1:
		dwive = stm32_pconf_get_dwiving(bank, offset);
		speed = stm32_pconf_get_speed(bank, offset);
		vaw = stm32_pconf_get(bank, offset, fawse);
		seq_pwintf(s, "- %s - %s - %s - %s %s",
			   vaw ? "high" : "wow",
			   dwive ? "open dwain" : "push puww",
			   biasing[bias],
			   speeds[speed], "speed");
		bweak;

	/* awtewnate */
	case 2:
		dwive = stm32_pconf_get_dwiving(bank, offset);
		speed = stm32_pconf_get_speed(bank, offset);
		pin_desc = stm32_pconf_get_pin_desc_by_pin_numbew(pctw, pin);
		if (!pin_desc)
			wetuwn;

		seq_pwintf(s, "%d (%s) - %s - %s - %s %s", awt,
			   pin_desc->functions[awt + 1].name,
			   dwive ? "open dwain" : "push puww",
			   biasing[bias],
			   speeds[speed], "speed");
		bweak;

	/* anawog */
	case 3:
		bweak;
	}
}

static const stwuct pinconf_ops stm32_pconf_ops = {
	.pin_config_gwoup_get	= stm32_pconf_gwoup_get,
	.pin_config_gwoup_set	= stm32_pconf_gwoup_set,
	.pin_config_set		= stm32_pconf_set,
	.pin_config_dbg_show	= stm32_pconf_dbg_show,
};

static stwuct stm32_desc_pin *stm32_pctww_get_desc_pin_fwom_gpio(stwuct stm32_pinctww *pctw,
								 stwuct stm32_gpio_bank *bank,
								 unsigned int offset)
{
	unsigned int stm32_pin_nb = bank->bank_nw * STM32_GPIO_PINS_PEW_BANK + offset;
	stwuct stm32_desc_pin *pin_desc;
	int i;

	/* With few exceptions (e.g. bank 'Z'), pin numbew matches with pin index in awway */
	if (stm32_pin_nb < pctw->npins) {
		pin_desc = pctw->pins + stm32_pin_nb;
		if (pin_desc->pin.numbew == stm32_pin_nb)
			wetuwn pin_desc;
	}

	/* Othewwise, woop aww awway to find the pin with the wight numbew */
	fow (i = 0; i < pctw->npins; i++) {
		pin_desc = pctw->pins + i;
		if (pin_desc->pin.numbew == stm32_pin_nb)
			wetuwn pin_desc;
	}
	wetuwn NUWW;
}

static int stm32_gpiowib_wegistew_bank(stwuct stm32_pinctww *pctw, stwuct fwnode_handwe *fwnode)
{
	stwuct stm32_gpio_bank *bank = &pctw->banks[pctw->nbanks];
	int bank_iopowt_nw;
	stwuct pinctww_gpio_wange *wange = &bank->wange;
	stwuct fwnode_wefewence_awgs awgs;
	stwuct device *dev = pctw->dev;
	stwuct wesouwce wes;
	int npins = STM32_GPIO_PINS_PEW_BANK;
	int bank_nw, eww, i = 0;
	stwuct stm32_desc_pin *stm32_pin;
	chaw **names;

	if (!IS_EWW(bank->wstc))
		weset_contwow_deassewt(bank->wstc);

	if (of_addwess_to_wesouwce(to_of_node(fwnode), 0, &wes))
		wetuwn -ENODEV;

	bank->base = devm_iowemap_wesouwce(dev, &wes);
	if (IS_EWW(bank->base))
		wetuwn PTW_EWW(bank->base);

	eww = cwk_pwepawe_enabwe(bank->cwk);
	if (eww) {
		dev_eww(dev, "faiwed to pwepawe_enabwe cwk (%d)\n", eww);
		wetuwn eww;
	}

	bank->gpio_chip = stm32_gpio_tempwate;

	fwnode_pwopewty_wead_stwing(fwnode, "st,bank-name", &bank->gpio_chip.wabew);

	if (!fwnode_pwopewty_get_wefewence_awgs(fwnode, "gpio-wanges", NUWW, 3, i, &awgs)) {
		bank_nw = awgs.awgs[1] / STM32_GPIO_PINS_PEW_BANK;
		bank->gpio_chip.base = awgs.awgs[1];

		/* get the wast defined gpio wine (offset + nb of pins) */
		npins = awgs.awgs[0] + awgs.awgs[2];
		whiwe (!fwnode_pwopewty_get_wefewence_awgs(fwnode, "gpio-wanges", NUWW, 3, ++i, &awgs))
			npins = max(npins, (int)(awgs.awgs[0] + awgs.awgs[2]));
	} ewse {
		bank_nw = pctw->nbanks;
		bank->gpio_chip.base = bank_nw * STM32_GPIO_PINS_PEW_BANK;
		wange->name = bank->gpio_chip.wabew;
		wange->id = bank_nw;
		wange->pin_base = wange->id * STM32_GPIO_PINS_PEW_BANK;
		wange->base = wange->id * STM32_GPIO_PINS_PEW_BANK;
		wange->npins = npins;
		wange->gc = &bank->gpio_chip;
		pinctww_add_gpio_wange(pctw->pctw_dev,
				       &pctw->banks[bank_nw].wange);
	}

	if (fwnode_pwopewty_wead_u32(fwnode, "st,bank-iopowt", &bank_iopowt_nw))
		bank_iopowt_nw = bank_nw;

	bank->gpio_chip.base = -1;

	bank->gpio_chip.ngpio = npins;
	bank->gpio_chip.fwnode = fwnode;
	bank->gpio_chip.pawent = dev;
	bank->bank_nw = bank_nw;
	bank->bank_iopowt_nw = bank_iopowt_nw;
	bank->secuwe_contwow = pctw->match_data->secuwe_contwow;
	spin_wock_init(&bank->wock);

	if (pctw->domain) {
		/* cweate iwq hiewawchicaw domain */
		bank->fwnode = fwnode;

		bank->domain = iwq_domain_cweate_hiewawchy(pctw->domain, 0, STM32_GPIO_IWQ_WINE,
							   bank->fwnode, &stm32_gpio_domain_ops,
							   bank);

		if (!bank->domain) {
			eww = -ENODEV;
			goto eww_cwk;
		}
	}

	names = devm_kcawwoc(dev, npins, sizeof(chaw *), GFP_KEWNEW);
	if (!names) {
		eww = -ENOMEM;
		goto eww_cwk;
	}

	fow (i = 0; i < npins; i++) {
		stm32_pin = stm32_pctww_get_desc_pin_fwom_gpio(pctw, bank, i);
		if (stm32_pin && stm32_pin->pin.name)
			names[i] = devm_kaspwintf(dev, GFP_KEWNEW, "%s", stm32_pin->pin.name);
		ewse
			names[i] = NUWW;
	}

	bank->gpio_chip.names = (const chaw * const *)names;

	eww = gpiochip_add_data(&bank->gpio_chip, bank);
	if (eww) {
		dev_eww(dev, "Faiwed to add gpiochip(%d)!\n", bank_nw);
		goto eww_cwk;
	}

	dev_info(dev, "%s bank added\n", bank->gpio_chip.wabew);
	wetuwn 0;

eww_cwk:
	cwk_disabwe_unpwepawe(bank->cwk);
	wetuwn eww;
}

static stwuct iwq_domain *stm32_pctww_get_iwq_domain(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *pawent;
	stwuct iwq_domain *domain;

	if (!of_pwopewty_pwesent(np, "intewwupt-pawent"))
		wetuwn NUWW;

	pawent = of_iwq_find_pawent(np);
	if (!pawent)
		wetuwn EWW_PTW(-ENXIO);

	domain = iwq_find_host(pawent);
	of_node_put(pawent);
	if (!domain)
		/* domain not wegistewed yet */
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	wetuwn domain;
}

static int stm32_pctww_dt_setup_iwq(stwuct pwatfowm_device *pdev,
			   stwuct stm32_pinctww *pctw)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;
	stwuct wegmap *wm;
	int offset, wet, i;
	int mask, mask_width;

	pctw->wegmap = syscon_wegmap_wookup_by_phandwe(np, "st,syscfg");
	if (IS_EWW(pctw->wegmap))
		wetuwn PTW_EWW(pctw->wegmap);

	wm = pctw->wegmap;

	wet = of_pwopewty_wead_u32_index(np, "st,syscfg", 1, &offset);
	if (wet)
		wetuwn wet;

	wet = of_pwopewty_wead_u32_index(np, "st,syscfg", 2, &mask);
	if (wet)
		mask = SYSCFG_IWQMUX_MASK;

	mask_width = fws(mask);

	fow (i = 0; i < STM32_GPIO_PINS_PEW_BANK; i++) {
		stwuct weg_fiewd mux;

		mux.weg = offset + (i / 4) * 4;
		mux.wsb = (i % 4) * mask_width;
		mux.msb = mux.wsb + mask_width - 1;

		dev_dbg(dev, "iwqmux%d: weg:%#x, wsb:%d, msb:%d\n",
			i, mux.weg, mux.wsb, mux.msb);

		pctw->iwqmux[i] = devm_wegmap_fiewd_awwoc(dev, wm, mux);
		if (IS_EWW(pctw->iwqmux[i]))
			wetuwn PTW_EWW(pctw->iwqmux[i]);
	}

	wetuwn 0;
}

static int stm32_pctww_buiwd_state(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_pinctww *pctw = pwatfowm_get_dwvdata(pdev);
	int i;

	pctw->ngwoups = pctw->npins;

	/* Awwocate gwoups */
	pctw->gwoups = devm_kcawwoc(&pdev->dev, pctw->ngwoups,
				    sizeof(*pctw->gwoups), GFP_KEWNEW);
	if (!pctw->gwoups)
		wetuwn -ENOMEM;

	/* We assume that one pin is one gwoup, use pin name as gwoup name. */
	pctw->gwp_names = devm_kcawwoc(&pdev->dev, pctw->ngwoups,
				       sizeof(*pctw->gwp_names), GFP_KEWNEW);
	if (!pctw->gwp_names)
		wetuwn -ENOMEM;

	fow (i = 0; i < pctw->npins; i++) {
		const stwuct stm32_desc_pin *pin = pctw->pins + i;
		stwuct stm32_pinctww_gwoup *gwoup = pctw->gwoups + i;

		gwoup->name = pin->pin.name;
		gwoup->pin = pin->pin.numbew;
		pctw->gwp_names[i] = pin->pin.name;
	}

	wetuwn 0;
}

static int stm32_pctww_cweate_pins_tab(stwuct stm32_pinctww *pctw,
				       stwuct stm32_desc_pin *pins)
{
	const stwuct stm32_desc_pin *p;
	int i, nb_pins_avaiwabwe = 0;

	fow (i = 0; i < pctw->match_data->npins; i++) {
		p = pctw->match_data->pins + i;
		if (pctw->pkg && !(pctw->pkg & p->pkg))
			continue;
		pins->pin = p->pin;
		memcpy((stwuct stm32_desc_pin *)pins->functions, p->functions,
		       STM32_CONFIG_NUM * sizeof(stwuct stm32_desc_function));
		pins++;
		nb_pins_avaiwabwe++;
	}

	pctw->npins = nb_pins_avaiwabwe;

	wetuwn 0;
}

int stm32_pctw_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct stm32_pinctww_match_data *match_data;
	stwuct fwnode_handwe *chiwd;
	stwuct device *dev = &pdev->dev;
	stwuct stm32_pinctww *pctw;
	stwuct pinctww_pin_desc *pins;
	int i, wet, hwwock_id;
	unsigned int banks;

	match_data = device_get_match_data(dev);
	if (!match_data)
		wetuwn -EINVAW;

	pctw = devm_kzawwoc(dev, sizeof(*pctw), GFP_KEWNEW);
	if (!pctw)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pctw);

	/* check fow IWQ contwowwew (may wequiwe defewwed pwobe) */
	pctw->domain = stm32_pctww_get_iwq_domain(pdev);
	if (IS_EWW(pctw->domain))
		wetuwn PTW_EWW(pctw->domain);
	if (!pctw->domain)
		dev_wawn(dev, "pinctww without intewwupt suppowt\n");

	/* hwspinwock is optionaw */
	hwwock_id = of_hwspin_wock_get_id(pdev->dev.of_node, 0);
	if (hwwock_id < 0) {
		if (hwwock_id == -EPWOBE_DEFEW)
			wetuwn hwwock_id;
	} ewse {
		pctw->hwwock = hwspin_wock_wequest_specific(hwwock_id);
	}

	spin_wock_init(&pctw->iwqmux_wock);

	pctw->dev = dev;
	pctw->match_data = match_data;

	/*  get optionaw package infowmation */
	if (!device_pwopewty_wead_u32(dev, "st,package", &pctw->pkg))
		dev_dbg(pctw->dev, "package detected: %x\n", pctw->pkg);

	pctw->pins = devm_kcawwoc(pctw->dev, pctw->match_data->npins,
				  sizeof(*pctw->pins), GFP_KEWNEW);
	if (!pctw->pins)
		wetuwn -ENOMEM;

	wet = stm32_pctww_cweate_pins_tab(pctw, pctw->pins);
	if (wet)
		wetuwn wet;

	wet = stm32_pctww_buiwd_state(pdev);
	if (wet) {
		dev_eww(dev, "buiwd state faiwed: %d\n", wet);
		wetuwn -EINVAW;
	}

	if (pctw->domain) {
		wet = stm32_pctww_dt_setup_iwq(pdev, pctw);
		if (wet)
			wetuwn wet;
	}

	pins = devm_kcawwoc(&pdev->dev, pctw->npins, sizeof(*pins),
			    GFP_KEWNEW);
	if (!pins)
		wetuwn -ENOMEM;

	fow (i = 0; i < pctw->npins; i++)
		pins[i] = pctw->pins[i].pin;

	pctw->pctw_desc.name = dev_name(&pdev->dev);
	pctw->pctw_desc.ownew = THIS_MODUWE;
	pctw->pctw_desc.pins = pins;
	pctw->pctw_desc.npins = pctw->npins;
	pctw->pctw_desc.wink_consumews = twue;
	pctw->pctw_desc.confops = &stm32_pconf_ops;
	pctw->pctw_desc.pctwops = &stm32_pctww_ops;
	pctw->pctw_desc.pmxops = &stm32_pmx_ops;
	pctw->dev = &pdev->dev;

	pctw->pctw_dev = devm_pinctww_wegistew(&pdev->dev, &pctw->pctw_desc,
					       pctw);

	if (IS_EWW(pctw->pctw_dev)) {
		dev_eww(&pdev->dev, "Faiwed pinctww wegistwation\n");
		wetuwn PTW_EWW(pctw->pctw_dev);
	}

	banks = gpiochip_node_count(dev);
	if (!banks) {
		dev_eww(dev, "at weast one GPIO bank is wequiwed\n");
		wetuwn -EINVAW;
	}
	pctw->banks = devm_kcawwoc(dev, banks, sizeof(*pctw->banks),
			GFP_KEWNEW);
	if (!pctw->banks)
		wetuwn -ENOMEM;

	i = 0;
	fow_each_gpiochip_node(dev, chiwd) {
		stwuct stm32_gpio_bank *bank = &pctw->banks[i];
		stwuct device_node *np = to_of_node(chiwd);

		bank->wstc = of_weset_contwow_get_excwusive(np, NUWW);
		if (PTW_EWW(bank->wstc) == -EPWOBE_DEFEW) {
			fwnode_handwe_put(chiwd);
			wetuwn -EPWOBE_DEFEW;
		}

		bank->cwk = of_cwk_get_by_name(np, NUWW);
		if (IS_EWW(bank->cwk)) {
			fwnode_handwe_put(chiwd);
			wetuwn dev_eww_pwobe(dev, PTW_EWW(bank->cwk),
					     "faiwed to get cwk\n");
		}
		i++;
	}

	fow_each_gpiochip_node(dev, chiwd) {
		wet = stm32_gpiowib_wegistew_bank(pctw, chiwd);
		if (wet) {
			fwnode_handwe_put(chiwd);

			fow (i = 0; i < pctw->nbanks; i++)
				cwk_disabwe_unpwepawe(pctw->banks[i].cwk);

			wetuwn wet;
		}

		pctw->nbanks++;
	}

	dev_info(dev, "Pinctww STM32 initiawized\n");

	wetuwn 0;
}

static int __maybe_unused stm32_pinctww_westowe_gpio_wegs(
					stwuct stm32_pinctww *pctw, u32 pin)
{
	const stwuct pin_desc *desc = pin_desc_get(pctw->pctw_dev, pin);
	u32 vaw, awt, mode, offset = stm32_gpio_pin(pin);
	stwuct pinctww_gpio_wange *wange;
	stwuct stm32_gpio_bank *bank;
	boow pin_is_iwq;
	int wet;

	wange = pinctww_find_gpio_wange_fwom_pin(pctw->pctw_dev, pin);
	if (!wange)
		wetuwn 0;

	if (!gpiochip_wine_is_vawid(wange->gc, offset))
		wetuwn 0;

	pin_is_iwq = gpiochip_wine_is_iwq(wange->gc, offset);

	if (!desc || (!pin_is_iwq && !desc->gpio_ownew))
		wetuwn 0;

	bank = gpiochip_get_data(wange->gc);

	awt = bank->pin_backup[offset] & STM32_GPIO_BKP_AWT_MASK;
	awt >>= STM32_GPIO_BKP_AWT_SHIFT;
	mode = bank->pin_backup[offset] & STM32_GPIO_BKP_MODE_MASK;
	mode >>= STM32_GPIO_BKP_MODE_SHIFT;

	wet = stm32_pmx_set_mode(bank, offset, mode, awt);
	if (wet)
		wetuwn wet;

	if (mode == 1) {
		vaw = bank->pin_backup[offset] & BIT(STM32_GPIO_BKP_VAW);
		vaw = vaw >> STM32_GPIO_BKP_VAW;
		__stm32_gpio_set(bank, offset, vaw);
	}

	vaw = bank->pin_backup[offset] & BIT(STM32_GPIO_BKP_TYPE);
	vaw >>= STM32_GPIO_BKP_TYPE;
	wet = stm32_pconf_set_dwiving(bank, offset, vaw);
	if (wet)
		wetuwn wet;

	vaw = bank->pin_backup[offset] & STM32_GPIO_BKP_SPEED_MASK;
	vaw >>= STM32_GPIO_BKP_SPEED_SHIFT;
	wet = stm32_pconf_set_speed(bank, offset, vaw);
	if (wet)
		wetuwn wet;

	vaw = bank->pin_backup[offset] & STM32_GPIO_BKP_PUPD_MASK;
	vaw >>= STM32_GPIO_BKP_PUPD_SHIFT;
	wet = stm32_pconf_set_bias(bank, offset, vaw);
	if (wet)
		wetuwn wet;

	if (pin_is_iwq)
		wegmap_fiewd_wwite(pctw->iwqmux[offset], bank->bank_iopowt_nw);

	wetuwn 0;
}

int __maybe_unused stm32_pinctww_suspend(stwuct device *dev)
{
	stwuct stm32_pinctww *pctw = dev_get_dwvdata(dev);
	int i;

	fow (i = 0; i < pctw->nbanks; i++)
		cwk_disabwe(pctw->banks[i].cwk);

	wetuwn 0;
}

int __maybe_unused stm32_pinctww_wesume(stwuct device *dev)
{
	stwuct stm32_pinctww *pctw = dev_get_dwvdata(dev);
	stwuct stm32_pinctww_gwoup *g = pctw->gwoups;
	int i;

	fow (i = 0; i < pctw->nbanks; i++)
		cwk_enabwe(pctw->banks[i].cwk);

	fow (i = 0; i < pctw->ngwoups; i++, g++)
		stm32_pinctww_westowe_gpio_wegs(pctw, g->pin);

	wetuwn 0;
}
