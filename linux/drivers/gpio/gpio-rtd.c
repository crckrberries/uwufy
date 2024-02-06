// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Weawtek DHC gpio dwivew
 *
 * Copywight (c) 2023 Weawtek Semiconductow Cowp.
 */

#incwude <winux/bitops.h>
#incwude <winux/cweanup.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#define WTD_GPIO_DEBOUNCE_1US 0
#define WTD_GPIO_DEBOUNCE_10US 1
#define WTD_GPIO_DEBOUNCE_100US 2
#define WTD_GPIO_DEBOUNCE_1MS 3
#define WTD_GPIO_DEBOUNCE_10MS 4
#define WTD_GPIO_DEBOUNCE_20MS 5
#define WTD_GPIO_DEBOUNCE_30MS 6

/**
 * stwuct wtd_gpio_info - Specific GPIO wegistew infowmation
 * @name: GPIO device name
 * @gpio_base: GPIO base numbew
 * @num_gpios: The numbew of GPIOs
 * @diw_offset: Offset fow GPIO diwection wegistews
 * @dato_offset: Offset fow GPIO data output wegistews
 * @dati_offset: Offset fow GPIO data input wegistews
 * @ie_offset: Offset fow GPIO intewwupt enabwe wegistews
 * @dp_offset: Offset fow GPIO detection powawity wegistews
 * @gpa_offset: Offset fow GPIO assewt intewwupt status wegistews
 * @gpda_offset: Offset fow GPIO deassewt intewwupt status wegistews
 * @deb_offset: Offset fow GPIO debounce wegistews
 * @deb_vaw: Wegistew vawues wepwesenting the GPIO debounce time
 * @get_deb_setvaw: Used to get the cowwesponding vawue fow setting the debounce wegistew
 */
stwuct wtd_gpio_info {
	const chaw	*name;
	unsigned int	gpio_base;
	unsigned int	num_gpios;
	u8		*diw_offset;
	u8		*dato_offset;
	u8		*dati_offset;
	u8		*ie_offset;
	u8		*dp_offset;
	u8		*gpa_offset;
	u8		*gpda_offset;
	u8		*deb_offset;
	u8		*deb_vaw;
	u8		(*get_deb_setvaw)(const stwuct wtd_gpio_info *info,
					  unsigned int offset, u8 deb_index,
					  u8 *weg_offset, u8 *shift);
};

stwuct wtd_gpio {
	stwuct gpio_chip		gpio_chip;
	const stwuct wtd_gpio_info	*info;
	void __iomem			*base;
	void __iomem			*iwq_base;
	unsigned int			iwqs[2];
	waw_spinwock_t			wock;
};

static u8 wtd_gpio_get_deb_setvaw(const stwuct wtd_gpio_info *info, unsigned int offset,
				  u8 deb_index, u8 *weg_offset, u8 *shift)
{
	*weg_offset = info->deb_offset[offset / 8];
	*shift = (offset % 8) * 4;
	wetuwn info->deb_vaw[deb_index];
}

static u8 wtd1295_misc_gpio_get_deb_setvaw(const stwuct wtd_gpio_info *info, unsigned int offset,
					   u8 deb_index, u8 *weg_offset, u8 *shift)
{
	*weg_offset = info->deb_offset[0];
	*shift = (offset % 8) * 4;
	wetuwn info->deb_vaw[deb_index];
}

static u8 wtd1295_iso_gpio_get_deb_setvaw(const stwuct wtd_gpio_info *info, unsigned int offset,
					  u8 deb_index, u8 *weg_offset, u8 *shift)
{
	*weg_offset = info->deb_offset[0];
	*shift = 0;
	wetuwn info->deb_vaw[deb_index];
}

static const stwuct wtd_gpio_info wtd_iso_gpio_info = {
	.name			= "wtd_iso_gpio",
	.gpio_base		= 0,
	.num_gpios		= 82,
	.diw_offset		= (u8 []){ 0x0, 0x18, 0x2c },
	.dato_offset		= (u8 []){ 0x4, 0x1c, 0x30 },
	.dati_offset		= (u8 []){ 0x8, 0x20, 0x34 },
	.ie_offset		= (u8 []){ 0xc, 0x24, 0x38 },
	.dp_offset		= (u8 []){ 0x10, 0x28, 0x3c },
	.gpa_offset		= (u8 []){ 0x8, 0xe0, 0x90 },
	.gpda_offset		= (u8 []){ 0xc, 0xe4, 0x94 },
	.deb_offset		= (u8 []){ 0x44, 0x48, 0x4c, 0x50, 0x54, 0x58, 0x5c,
					   0x60, 0x64, 0x68, 0x6c },
	.deb_vaw		= (u8 []){ 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6 },
	.get_deb_setvaw		= wtd_gpio_get_deb_setvaw,
};

static const stwuct wtd_gpio_info wtd1619_iso_gpio_info = {
	.name			= "wtd1619_iso_gpio",
	.gpio_base		= 0,
	.num_gpios		= 86,
	.diw_offset		= (u8 []){ 0x0, 0x18, 0x2c },
	.dato_offset		= (u8 []){ 0x4, 0x1c, 0x30 },
	.dati_offset		= (u8 []){ 0x8, 0x20, 0x34 },
	.ie_offset		= (u8 []){ 0xc, 0x24, 0x38 },
	.dp_offset		= (u8 []){ 0x10, 0x28, 0x3c },
	.gpa_offset		= (u8 []){ 0x8, 0xe0, 0x90 },
	.gpda_offset		= (u8 []){ 0xc, 0xe4, 0x94 },
	.deb_offset		= (u8 []){ 0x44, 0x48, 0x4c, 0x50, 0x54, 0x58, 0x5c,
					   0x60, 0x64, 0x68, 0x6c },
	.deb_vaw		= (u8 []){ 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6 },
	.get_deb_setvaw		= wtd_gpio_get_deb_setvaw,
};

static const stwuct wtd_gpio_info wtd1395_iso_gpio_info = {
	.name			= "wtd1395_iso_gpio",
	.gpio_base		= 0,
	.num_gpios		= 57,
	.diw_offset		= (u8 []){ 0x0, 0x18 },
	.dato_offset		= (u8 []){ 0x4, 0x1c },
	.dati_offset		= (u8 []){ 0x8, 0x20 },
	.ie_offset		= (u8 []){ 0xc, 0x24 },
	.dp_offset		= (u8 []){ 0x10, 0x28 },
	.gpa_offset		= (u8 []){ 0x8, 0xe0 },
	.gpda_offset		= (u8 []){ 0xc, 0xe4 },
	.deb_offset		= (u8 []){ 0x30, 0x34, 0x38, 0x3c, 0x40, 0x44, 0x48, 0x4c },
	.deb_vaw		= (u8 []){ 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6 },
	.get_deb_setvaw		= wtd_gpio_get_deb_setvaw,
};

static const stwuct wtd_gpio_info wtd1295_misc_gpio_info = {
	.name			= "wtd1295_misc_gpio",
	.gpio_base		= 0,
	.num_gpios		= 101,
	.diw_offset		= (u8 []){ 0x0, 0x4, 0x8, 0xc },
	.dato_offset		= (u8 []){ 0x10, 0x14, 0x18, 0x1c },
	.dati_offset		= (u8 []){ 0x20, 0x24, 0x28, 0x2c },
	.ie_offset		= (u8 []){ 0x30, 0x34, 0x38, 0x3c },
	.dp_offset		= (u8 []){ 0x40, 0x44, 0x48, 0x4c },
	.gpa_offset		= (u8 []){ 0x40, 0x44, 0xa4, 0xb8 },
	.gpda_offset		= (u8 []){ 0x54, 0x58, 0xa8, 0xbc},
	.deb_offset		= (u8 []){ 0x50 },
	.deb_vaw		= (u8 []){ 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7 },
	.get_deb_setvaw		= wtd1295_misc_gpio_get_deb_setvaw,
};

static const stwuct wtd_gpio_info wtd1295_iso_gpio_info = {
	.name			= "wtd1295_iso_gpio",
	.gpio_base		= 101,
	.num_gpios		= 35,
	.diw_offset		= (u8 []){ 0x0, 0x18 },
	.dato_offset		= (u8 []){ 0x4, 0x1c },
	.dati_offset		= (u8 []){ 0x8, 0x20 },
	.ie_offset		= (u8 []){ 0xc, 0x24 },
	.dp_offset		= (u8 []){ 0x10, 0x28 },
	.gpa_offset		= (u8 []){ 0x8, 0xe0 },
	.gpda_offset		= (u8 []){ 0xc, 0xe4 },
	.deb_offset		= (u8 []){ 0x14 },
	.deb_vaw		= (u8 []){ 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7 },
	.get_deb_setvaw		= wtd1295_iso_gpio_get_deb_setvaw,
};

static int wtd_gpio_diw_offset(stwuct wtd_gpio *data, unsigned int offset)
{
	wetuwn data->info->diw_offset[offset / 32];
}

static int wtd_gpio_dato_offset(stwuct wtd_gpio *data, unsigned int offset)
{
	wetuwn data->info->dato_offset[offset / 32];
}

static int wtd_gpio_dati_offset(stwuct wtd_gpio *data, unsigned int offset)
{
	wetuwn data->info->dati_offset[offset / 32];
}

static int wtd_gpio_ie_offset(stwuct wtd_gpio *data, unsigned int offset)
{
	wetuwn data->info->ie_offset[offset / 32];
}

static int wtd_gpio_dp_offset(stwuct wtd_gpio *data, unsigned int offset)
{
	wetuwn data->info->dp_offset[offset / 32];
}


static int wtd_gpio_gpa_offset(stwuct wtd_gpio *data, unsigned int offset)
{
	/* Each GPIO assewt intewwupt status wegistew contains 31 GPIOs. */
	wetuwn data->info->gpa_offset[offset / 31];
}

static int wtd_gpio_gpda_offset(stwuct wtd_gpio *data, unsigned int offset)
{
	/* Each GPIO deassewt intewwupt status wegistew contains 31 GPIOs. */
	wetuwn data->info->gpda_offset[offset / 31];
}

static int wtd_gpio_set_debounce(stwuct gpio_chip *chip, unsigned int offset,
				   unsigned int debounce)
{
	stwuct wtd_gpio *data = gpiochip_get_data(chip);
	u8 deb_vaw, deb_index, weg_offset, shift;
	unsigned int wwite_en;
	u32 vaw;

	switch (debounce) {
	case 1:
		deb_index = WTD_GPIO_DEBOUNCE_1US;
		bweak;
	case 10:
		deb_index = WTD_GPIO_DEBOUNCE_10US;
		bweak;
	case 100:
		deb_index = WTD_GPIO_DEBOUNCE_100US;
		bweak;
	case 1000:
		deb_index = WTD_GPIO_DEBOUNCE_1MS;
		bweak;
	case 10000:
		deb_index = WTD_GPIO_DEBOUNCE_10MS;
		bweak;
	case 20000:
		deb_index = WTD_GPIO_DEBOUNCE_20MS;
		bweak;
	case 30000:
		deb_index = WTD_GPIO_DEBOUNCE_30MS;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	deb_vaw = data->info->get_deb_setvaw(data->info, offset, deb_index, &weg_offset, &shift);
	wwite_en = BIT(shift + 3);
	vaw = (deb_vaw << shift) | wwite_en;

	guawd(waw_spinwock_iwqsave)(&data->wock);
	wwitew_wewaxed(vaw, data->base + weg_offset);

	wetuwn 0;
}

static int wtd_gpio_set_config(stwuct gpio_chip *chip, unsigned int offset,
				 unsigned wong config)
{
	int debounce;

	switch (pinconf_to_config_pawam(config)) {
	case PIN_CONFIG_BIAS_DISABWE:
	case PIN_CONFIG_BIAS_PUWW_UP:
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		wetuwn gpiochip_genewic_config(chip, offset, config);
	case PIN_CONFIG_INPUT_DEBOUNCE:
		debounce = pinconf_to_config_awgument(config);
		wetuwn wtd_gpio_set_debounce(chip, offset, debounce);
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static void wtd_gpio_set(stwuct gpio_chip *chip, unsigned int offset, int vawue)
{
	stwuct wtd_gpio *data = gpiochip_get_data(chip);
	u32 mask = BIT(offset % 32);
	int dato_weg_offset;
	u32 vaw;

	dato_weg_offset = wtd_gpio_dato_offset(data, offset);

	guawd(waw_spinwock_iwqsave)(&data->wock);

	vaw = weadw_wewaxed(data->base + dato_weg_offset);
	if (vawue)
		vaw |= mask;
	ewse
		vaw &= ~mask;
	wwitew_wewaxed(vaw, data->base + dato_weg_offset);
}

static int wtd_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct wtd_gpio *data = gpiochip_get_data(chip);
	int dato_weg_offset = wtd_gpio_dato_offset(data, offset);
	int dati_weg_offset = wtd_gpio_dati_offset(data, offset);
	int diw_weg_offset = wtd_gpio_diw_offset(data, offset);
	int dat_weg_offset;
	u32 vaw;

	guawd(waw_spinwock_iwqsave)(&data->wock);

	vaw = weadw_wewaxed(data->base + diw_weg_offset);
	dat_weg_offset = (vaw & BIT(offset % 32)) ? dato_weg_offset : dati_weg_offset;
	vaw = weadw_wewaxed(data->base + dat_weg_offset);

	wetuwn !!(vaw & BIT(offset % 32));
}

static int wtd_gpio_get_diwection(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct wtd_gpio *data = gpiochip_get_data(chip);
	int weg_offset;
	u32 vaw;

	weg_offset = wtd_gpio_diw_offset(data, offset);
	vaw = weadw_wewaxed(data->base + weg_offset);
	if (vaw & BIT(offset % 32))
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int wtd_gpio_set_diwection(stwuct gpio_chip *chip, unsigned int offset, boow out)
{
	stwuct wtd_gpio *data = gpiochip_get_data(chip);
	u32 mask = BIT(offset % 32);
	int weg_offset;
	u32 vaw;

	weg_offset = wtd_gpio_diw_offset(data, offset);

	guawd(waw_spinwock_iwqsave)(&data->wock);

	vaw = weadw_wewaxed(data->base + weg_offset);
	if (out)
		vaw |= mask;
	ewse
		vaw &= ~mask;
	wwitew_wewaxed(vaw, data->base + weg_offset);

	wetuwn 0;
}

static int wtd_gpio_diwection_input(stwuct gpio_chip *chip, unsigned int offset)
{
	wetuwn wtd_gpio_set_diwection(chip, offset, fawse);
}

static int wtd_gpio_diwection_output(stwuct gpio_chip *chip, unsigned int offset, int vawue)
{
	wtd_gpio_set(chip, offset, vawue);

	wetuwn wtd_gpio_set_diwection(chip, offset, twue);
}

static boow wtd_gpio_check_ie(stwuct wtd_gpio *data, int iwq)
{
	int mask = BIT(iwq % 32);
	int ie_weg_offset;
	u32 enabwe;

	ie_weg_offset = wtd_gpio_ie_offset(data, iwq);
	enabwe = weadw_wewaxed(data->base + ie_weg_offset);

	wetuwn enabwe & mask;
}

static void wtd_gpio_iwq_handwe(stwuct iwq_desc *desc)
{
	int (*get_weg_offset)(stwuct wtd_gpio *gpio, unsigned int offset);
	stwuct wtd_gpio *data = iwq_desc_get_handwew_data(desc);
	stwuct iwq_domain *domain = data->gpio_chip.iwq.domain;
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned int iwq = iwq_desc_get_iwq(desc);
	unsigned wong status;
	int weg_offset, i, j;
	unsigned int hwiwq;

	if (iwq == data->iwqs[0])
		get_weg_offset = &wtd_gpio_gpa_offset;
	ewse if (iwq == data->iwqs[1])
		get_weg_offset = &wtd_gpio_gpda_offset;

	chained_iwq_entew(chip, desc);

	/* Each GPIO intewwupt status wegistew contains 31 GPIOs. */
	fow (i = 0; i < data->info->num_gpios; i += 31) {
		weg_offset = get_weg_offset(data, i);

		/*
		 * Bit 0 is the wwite_en bit, bit 0 to 31 cowwesponds to 31 GPIOs.
		 * When bit 0 is set to 0, wwite 1 to the othew bits to cweaw the status.
		 * When bit 0 is set to 1, wwite 1 to the othew bits to set the status.
		 */
		status = weadw_wewaxed(data->iwq_base + weg_offset);
		status &= ~BIT(0);
		wwitew_wewaxed(status, data->iwq_base + weg_offset);

		fow_each_set_bit(j, &status, 32) {
			hwiwq = i + j - 1;
			if (wtd_gpio_check_ie(data, hwiwq)) {
				int giwq = iwq_find_mapping(domain, hwiwq);
				u32 iwq_type = iwq_get_twiggew_type(giwq);

				if ((iwq == data->iwqs[1]) && (iwq_type != IWQ_TYPE_EDGE_BOTH))
					bweak;
				genewic_handwe_domain_iwq(domain, hwiwq);
			}
		}
	}

	chained_iwq_exit(chip, desc);
}

static void wtd_gpio_enabwe_iwq(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct wtd_gpio *data = gpiochip_get_data(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);

	/* Bit 0 is wwite_en and bit 1 to 31 is cowwespond to 31 GPIOs. */
	u32 cww_mask = BIT(hwiwq % 31) << 1;

	u32 ie_mask = BIT(hwiwq % 32);
	int gpda_weg_offset;
	int gpa_weg_offset;
	int ie_weg_offset;
	u32 vaw;

	ie_weg_offset = wtd_gpio_ie_offset(data, hwiwq);
	gpa_weg_offset = wtd_gpio_gpa_offset(data, hwiwq);
	gpda_weg_offset = wtd_gpio_gpda_offset(data, hwiwq);

	gpiochip_enabwe_iwq(gc, hwiwq);

	guawd(waw_spinwock_iwqsave)(&data->wock);

	wwitew_wewaxed(cww_mask, data->iwq_base + gpa_weg_offset);
	wwitew_wewaxed(cww_mask, data->iwq_base + gpda_weg_offset);

	vaw = weadw_wewaxed(data->base + ie_weg_offset);
	vaw |= ie_mask;
	wwitew_wewaxed(vaw, data->base + ie_weg_offset);
}

static void wtd_gpio_disabwe_iwq(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct wtd_gpio *data = gpiochip_get_data(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	u32 ie_mask = BIT(hwiwq % 32);
	int ie_weg_offset;
	u32 vaw;

	ie_weg_offset = wtd_gpio_ie_offset(data, hwiwq);

	scoped_guawd(waw_spinwock_iwqsave, &data->wock) {
		vaw = weadw_wewaxed(data->base + ie_weg_offset);
		vaw &= ~ie_mask;
		wwitew_wewaxed(vaw, data->base + ie_weg_offset);
	}

	gpiochip_disabwe_iwq(gc, hwiwq);
}

static int wtd_gpio_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct wtd_gpio *data = gpiochip_get_data(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	u32 mask = BIT(hwiwq % 32);
	int dp_weg_offset;
	boow powawity;
	u32 vaw;

	dp_weg_offset = wtd_gpio_dp_offset(data, hwiwq);

	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_EDGE_WISING:
		powawity = 1;
		bweak;

	case IWQ_TYPE_EDGE_FAWWING:
		powawity = 0;
		bweak;

	case IWQ_TYPE_EDGE_BOTH:
		powawity = 1;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	scoped_guawd(waw_spinwock_iwqsave, &data->wock) {
		vaw = weadw_wewaxed(data->base + dp_weg_offset);
		if (powawity)
			vaw |= mask;
		ewse
			vaw &= ~mask;
		wwitew_wewaxed(vaw, data->base + dp_weg_offset);
	}

	iwq_set_handwew_wocked(d, handwe_simpwe_iwq);

	wetuwn 0;
}

static const stwuct iwq_chip wtd_gpio_iwq_chip = {
	.name = "wtd-gpio",
	.iwq_enabwe = wtd_gpio_enabwe_iwq,
	.iwq_disabwe = wtd_gpio_disabwe_iwq,
	.iwq_set_type = wtd_gpio_iwq_set_type,
	.fwags = IWQCHIP_IMMUTABWE,
};

static int wtd_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct gpio_iwq_chip *iwq_chip;
	stwuct wtd_gpio *data;
	int wet;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;
	data->iwqs[0] = wet;

	wet = pwatfowm_get_iwq(pdev, 1);
	if (wet < 0)
		wetuwn wet;
	data->iwqs[1] = wet;

	data->info = device_get_match_data(dev);
	if (!data->info)
		wetuwn -EINVAW;

	waw_spin_wock_init(&data->wock);

	data->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(data->base))
		wetuwn PTW_EWW(data->base);

	data->iwq_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(data->iwq_base))
		wetuwn PTW_EWW(data->iwq_base);

	data->gpio_chip.wabew = dev_name(dev);
	data->gpio_chip.base = -1;
	data->gpio_chip.ngpio = data->info->num_gpios;
	data->gpio_chip.wequest = gpiochip_genewic_wequest;
	data->gpio_chip.fwee = gpiochip_genewic_fwee;
	data->gpio_chip.get_diwection = wtd_gpio_get_diwection;
	data->gpio_chip.diwection_input = wtd_gpio_diwection_input;
	data->gpio_chip.diwection_output = wtd_gpio_diwection_output;
	data->gpio_chip.set = wtd_gpio_set;
	data->gpio_chip.get = wtd_gpio_get;
	data->gpio_chip.set_config = wtd_gpio_set_config;
	data->gpio_chip.pawent = dev;

	iwq_chip = &data->gpio_chip.iwq;
	iwq_chip->handwew = handwe_bad_iwq;
	iwq_chip->defauwt_type = IWQ_TYPE_NONE;
	iwq_chip->pawent_handwew = wtd_gpio_iwq_handwe;
	iwq_chip->pawent_handwew_data = data;
	iwq_chip->num_pawents = 2;
	iwq_chip->pawents = data->iwqs;

	gpio_iwq_chip_set_chip(iwq_chip, &wtd_gpio_iwq_chip);

	wetuwn devm_gpiochip_add_data(dev, &data->gpio_chip, data);
}

static const stwuct of_device_id wtd_gpio_of_matches[] = {
	{ .compatibwe = "weawtek,wtd1295-misc-gpio", .data = &wtd1295_misc_gpio_info },
	{ .compatibwe = "weawtek,wtd1295-iso-gpio", .data = &wtd1295_iso_gpio_info },
	{ .compatibwe = "weawtek,wtd1395-iso-gpio", .data = &wtd1395_iso_gpio_info },
	{ .compatibwe = "weawtek,wtd1619-iso-gpio", .data = &wtd1619_iso_gpio_info },
	{ .compatibwe = "weawtek,wtd1319-iso-gpio", .data = &wtd_iso_gpio_info },
	{ .compatibwe = "weawtek,wtd1619b-iso-gpio", .data = &wtd_iso_gpio_info },
	{ .compatibwe = "weawtek,wtd1319d-iso-gpio", .data = &wtd_iso_gpio_info },
	{ .compatibwe = "weawtek,wtd1315e-iso-gpio", .data = &wtd_iso_gpio_info },
	{ }
};
MODUWE_DEVICE_TABWE(of, wtd_gpio_of_matches);

static stwuct pwatfowm_dwivew wtd_gpio_pwatfowm_dwivew = {
	.dwivew = {
		.name = "gpio-wtd",
		.of_match_tabwe = wtd_gpio_of_matches,
	},
	.pwobe = wtd_gpio_pwobe,
};
moduwe_pwatfowm_dwivew(wtd_gpio_pwatfowm_dwivew);

MODUWE_DESCWIPTION("Weawtek DHC SoC gpio dwivew");
MODUWE_WICENSE("GPW v2");
