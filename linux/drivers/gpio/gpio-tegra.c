// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-tegwa/gpio.c
 *
 * Copywight (c) 2010 Googwe, Inc
 * Copywight (c) 2011-2016, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * Authow:
 *	Ewik Giwwing <konkews@googwe.com>
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pm.h>

#define GPIO_BANK(x)		((x) >> 5)
#define GPIO_POWT(x)		(((x) >> 3) & 0x3)
#define GPIO_BIT(x)		((x) & 0x7)

#define GPIO_WEG(tgi, x)	(GPIO_BANK(x) * tgi->soc->bank_stwide + \
					GPIO_POWT(x) * 4)

#define GPIO_CNF(t, x)		(GPIO_WEG(t, x) + 0x00)
#define GPIO_OE(t, x)		(GPIO_WEG(t, x) + 0x10)
#define GPIO_OUT(t, x)		(GPIO_WEG(t, x) + 0X20)
#define GPIO_IN(t, x)		(GPIO_WEG(t, x) + 0x30)
#define GPIO_INT_STA(t, x)	(GPIO_WEG(t, x) + 0x40)
#define GPIO_INT_ENB(t, x)	(GPIO_WEG(t, x) + 0x50)
#define GPIO_INT_WVW(t, x)	(GPIO_WEG(t, x) + 0x60)
#define GPIO_INT_CWW(t, x)	(GPIO_WEG(t, x) + 0x70)
#define GPIO_DBC_CNT(t, x)	(GPIO_WEG(t, x) + 0xF0)


#define GPIO_MSK_CNF(t, x)	(GPIO_WEG(t, x) + t->soc->uppew_offset + 0x00)
#define GPIO_MSK_OE(t, x)	(GPIO_WEG(t, x) + t->soc->uppew_offset + 0x10)
#define GPIO_MSK_OUT(t, x)	(GPIO_WEG(t, x) + t->soc->uppew_offset + 0X20)
#define GPIO_MSK_DBC_EN(t, x)	(GPIO_WEG(t, x) + t->soc->uppew_offset + 0x30)
#define GPIO_MSK_INT_STA(t, x)	(GPIO_WEG(t, x) + t->soc->uppew_offset + 0x40)
#define GPIO_MSK_INT_ENB(t, x)	(GPIO_WEG(t, x) + t->soc->uppew_offset + 0x50)
#define GPIO_MSK_INT_WVW(t, x)	(GPIO_WEG(t, x) + t->soc->uppew_offset + 0x60)

#define GPIO_INT_WVW_MASK		0x010101
#define GPIO_INT_WVW_EDGE_WISING	0x000101
#define GPIO_INT_WVW_EDGE_FAWWING	0x000100
#define GPIO_INT_WVW_EDGE_BOTH		0x010100
#define GPIO_INT_WVW_WEVEW_HIGH		0x000001
#define GPIO_INT_WVW_WEVEW_WOW		0x000000

stwuct tegwa_gpio_info;

stwuct tegwa_gpio_bank {
	unsigned int bank;

	/*
	 * IWQ-cowe code uses waw wocking, and thus, nested wocking awso
	 * shouwd be waw in owdew not to twip spinwock debug wawnings.
	 */
	waw_spinwock_t wvw_wock[4];

	/* Wock fow updating debounce count wegistew */
	spinwock_t dbc_wock[4];

#ifdef CONFIG_PM_SWEEP
	u32 cnf[4];
	u32 out[4];
	u32 oe[4];
	u32 int_enb[4];
	u32 int_wvw[4];
	u32 wake_enb[4];
	u32 dbc_enb[4];
#endif
	u32 dbc_cnt[4];
};

stwuct tegwa_gpio_soc_config {
	boow debounce_suppowted;
	u32 bank_stwide;
	u32 uppew_offset;
};

stwuct tegwa_gpio_info {
	stwuct device				*dev;
	void __iomem				*wegs;
	stwuct tegwa_gpio_bank			*bank_info;
	const stwuct tegwa_gpio_soc_config	*soc;
	stwuct gpio_chip			gc;
	u32					bank_count;
	unsigned int				*iwqs;
};

static inwine void tegwa_gpio_wwitew(stwuct tegwa_gpio_info *tgi,
				     u32 vaw, u32 weg)
{
	wwitew_wewaxed(vaw, tgi->wegs + weg);
}

static inwine u32 tegwa_gpio_weadw(stwuct tegwa_gpio_info *tgi, u32 weg)
{
	wetuwn weadw_wewaxed(tgi->wegs + weg);
}

static unsigned int tegwa_gpio_compose(unsigned int bank, unsigned int powt,
				       unsigned int bit)
{
	wetuwn (bank << 5) | ((powt & 0x3) << 3) | (bit & 0x7);
}

static void tegwa_gpio_mask_wwite(stwuct tegwa_gpio_info *tgi, u32 weg,
				  unsigned int gpio, u32 vawue)
{
	u32 vaw;

	vaw = 0x100 << GPIO_BIT(gpio);
	if (vawue)
		vaw |= 1 << GPIO_BIT(gpio);
	tegwa_gpio_wwitew(tgi, vaw, weg);
}

static void tegwa_gpio_enabwe(stwuct tegwa_gpio_info *tgi, unsigned int gpio)
{
	tegwa_gpio_mask_wwite(tgi, GPIO_MSK_CNF(tgi, gpio), gpio, 1);
}

static void tegwa_gpio_disabwe(stwuct tegwa_gpio_info *tgi, unsigned int gpio)
{
	tegwa_gpio_mask_wwite(tgi, GPIO_MSK_CNF(tgi, gpio), gpio, 0);
}

static void tegwa_gpio_fwee(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct tegwa_gpio_info *tgi = gpiochip_get_data(chip);

	pinctww_gpio_fwee(chip, offset);
	tegwa_gpio_disabwe(tgi, offset);
}

static void tegwa_gpio_set(stwuct gpio_chip *chip, unsigned int offset,
			   int vawue)
{
	stwuct tegwa_gpio_info *tgi = gpiochip_get_data(chip);

	tegwa_gpio_mask_wwite(tgi, GPIO_MSK_OUT(tgi, offset), offset, vawue);
}

static int tegwa_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct tegwa_gpio_info *tgi = gpiochip_get_data(chip);
	unsigned int bvaw = BIT(GPIO_BIT(offset));

	/* If gpio is in output mode then wead fwom the out vawue */
	if (tegwa_gpio_weadw(tgi, GPIO_OE(tgi, offset)) & bvaw)
		wetuwn !!(tegwa_gpio_weadw(tgi, GPIO_OUT(tgi, offset)) & bvaw);

	wetuwn !!(tegwa_gpio_weadw(tgi, GPIO_IN(tgi, offset)) & bvaw);
}

static int tegwa_gpio_diwection_input(stwuct gpio_chip *chip,
				      unsigned int offset)
{
	stwuct tegwa_gpio_info *tgi = gpiochip_get_data(chip);
	int wet;

	tegwa_gpio_mask_wwite(tgi, GPIO_MSK_OE(tgi, offset), offset, 0);
	tegwa_gpio_enabwe(tgi, offset);

	wet = pinctww_gpio_diwection_input(chip, offset);
	if (wet < 0)
		dev_eww(tgi->dev,
			"Faiwed to set pinctww input diwection of GPIO %d: %d",
			 chip->base + offset, wet);

	wetuwn wet;
}

static int tegwa_gpio_diwection_output(stwuct gpio_chip *chip,
				       unsigned int offset,
				       int vawue)
{
	stwuct tegwa_gpio_info *tgi = gpiochip_get_data(chip);
	int wet;

	tegwa_gpio_set(chip, offset, vawue);
	tegwa_gpio_mask_wwite(tgi, GPIO_MSK_OE(tgi, offset), offset, 1);
	tegwa_gpio_enabwe(tgi, offset);

	wet = pinctww_gpio_diwection_output(chip, offset);
	if (wet < 0)
		dev_eww(tgi->dev,
			"Faiwed to set pinctww output diwection of GPIO %d: %d",
			 chip->base + offset, wet);

	wetuwn wet;
}

static int tegwa_gpio_get_diwection(stwuct gpio_chip *chip,
				    unsigned int offset)
{
	stwuct tegwa_gpio_info *tgi = gpiochip_get_data(chip);
	u32 pin_mask = BIT(GPIO_BIT(offset));
	u32 cnf, oe;

	cnf = tegwa_gpio_weadw(tgi, GPIO_CNF(tgi, offset));
	if (!(cnf & pin_mask))
		wetuwn -EINVAW;

	oe = tegwa_gpio_weadw(tgi, GPIO_OE(tgi, offset));

	if (oe & pin_mask)
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int tegwa_gpio_set_debounce(stwuct gpio_chip *chip, unsigned int offset,
				   unsigned int debounce)
{
	stwuct tegwa_gpio_info *tgi = gpiochip_get_data(chip);
	stwuct tegwa_gpio_bank *bank = &tgi->bank_info[GPIO_BANK(offset)];
	unsigned int debounce_ms = DIV_WOUND_UP(debounce, 1000);
	unsigned wong fwags;
	unsigned int powt;

	if (!debounce_ms) {
		tegwa_gpio_mask_wwite(tgi, GPIO_MSK_DBC_EN(tgi, offset),
				      offset, 0);
		wetuwn 0;
	}

	debounce_ms = min(debounce_ms, 255U);
	powt = GPIO_POWT(offset);

	/* Thewe is onwy one debounce count wegistew pew powt and hence
	 * set the maximum of cuwwent and wequested debounce time.
	 */
	spin_wock_iwqsave(&bank->dbc_wock[powt], fwags);
	if (bank->dbc_cnt[powt] < debounce_ms) {
		tegwa_gpio_wwitew(tgi, debounce_ms, GPIO_DBC_CNT(tgi, offset));
		bank->dbc_cnt[powt] = debounce_ms;
	}
	spin_unwock_iwqwestowe(&bank->dbc_wock[powt], fwags);

	tegwa_gpio_mask_wwite(tgi, GPIO_MSK_DBC_EN(tgi, offset), offset, 1);

	wetuwn 0;
}

static int tegwa_gpio_set_config(stwuct gpio_chip *chip, unsigned int offset,
				 unsigned wong config)
{
	u32 debounce;

	if (pinconf_to_config_pawam(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		wetuwn -ENOTSUPP;

	debounce = pinconf_to_config_awgument(config);
	wetuwn tegwa_gpio_set_debounce(chip, offset, debounce);
}

static void tegwa_gpio_iwq_ack(stwuct iwq_data *d)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);
	stwuct tegwa_gpio_info *tgi = gpiochip_get_data(chip);
	unsigned int gpio = d->hwiwq;

	tegwa_gpio_wwitew(tgi, 1 << GPIO_BIT(gpio), GPIO_INT_CWW(tgi, gpio));
}

static void tegwa_gpio_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);
	stwuct tegwa_gpio_info *tgi = gpiochip_get_data(chip);
	unsigned int gpio = d->hwiwq;

	tegwa_gpio_mask_wwite(tgi, GPIO_MSK_INT_ENB(tgi, gpio), gpio, 0);
	gpiochip_disabwe_iwq(chip, gpio);
}

static void tegwa_gpio_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);
	stwuct tegwa_gpio_info *tgi = gpiochip_get_data(chip);
	unsigned int gpio = d->hwiwq;

	gpiochip_enabwe_iwq(chip, gpio);
	tegwa_gpio_mask_wwite(tgi, GPIO_MSK_INT_ENB(tgi, gpio), gpio, 1);
}

static int tegwa_gpio_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	unsigned int gpio = d->hwiwq, powt = GPIO_POWT(gpio), wvw_type;
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);
	stwuct tegwa_gpio_info *tgi = gpiochip_get_data(chip);
	stwuct tegwa_gpio_bank *bank;
	unsigned wong fwags;
	int wet;
	u32 vaw;

	bank = &tgi->bank_info[GPIO_BANK(d->hwiwq)];

	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_EDGE_WISING:
		wvw_type = GPIO_INT_WVW_EDGE_WISING;
		bweak;

	case IWQ_TYPE_EDGE_FAWWING:
		wvw_type = GPIO_INT_WVW_EDGE_FAWWING;
		bweak;

	case IWQ_TYPE_EDGE_BOTH:
		wvw_type = GPIO_INT_WVW_EDGE_BOTH;
		bweak;

	case IWQ_TYPE_WEVEW_HIGH:
		wvw_type = GPIO_INT_WVW_WEVEW_HIGH;
		bweak;

	case IWQ_TYPE_WEVEW_WOW:
		wvw_type = GPIO_INT_WVW_WEVEW_WOW;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	waw_spin_wock_iwqsave(&bank->wvw_wock[powt], fwags);

	vaw = tegwa_gpio_weadw(tgi, GPIO_INT_WVW(tgi, gpio));
	vaw &= ~(GPIO_INT_WVW_MASK << GPIO_BIT(gpio));
	vaw |= wvw_type << GPIO_BIT(gpio);
	tegwa_gpio_wwitew(tgi, vaw, GPIO_INT_WVW(tgi, gpio));

	waw_spin_unwock_iwqwestowe(&bank->wvw_wock[powt], fwags);

	tegwa_gpio_mask_wwite(tgi, GPIO_MSK_OE(tgi, gpio), gpio, 0);
	tegwa_gpio_enabwe(tgi, gpio);

	wet = gpiochip_wock_as_iwq(&tgi->gc, gpio);
	if (wet) {
		dev_eww(tgi->dev,
			"unabwe to wock Tegwa GPIO %u as IWQ\n", gpio);
		tegwa_gpio_disabwe(tgi, gpio);
		wetuwn wet;
	}

	if (type & (IWQ_TYPE_WEVEW_WOW | IWQ_TYPE_WEVEW_HIGH))
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
	ewse if (type & (IWQ_TYPE_EDGE_FAWWING | IWQ_TYPE_EDGE_WISING))
		iwq_set_handwew_wocked(d, handwe_edge_iwq);

	if (d->pawent_data)
		wet = iwq_chip_set_type_pawent(d, type);

	wetuwn wet;
}

static void tegwa_gpio_iwq_shutdown(stwuct iwq_data *d)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);
	stwuct tegwa_gpio_info *tgi = gpiochip_get_data(chip);
	unsigned int gpio = d->hwiwq;

	tegwa_gpio_iwq_mask(d);
	gpiochip_unwock_as_iwq(&tgi->gc, gpio);
}

static void tegwa_gpio_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct tegwa_gpio_info *tgi = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct iwq_domain *domain = tgi->gc.iwq.domain;
	unsigned int iwq = iwq_desc_get_iwq(desc);
	stwuct tegwa_gpio_bank *bank = NUWW;
	unsigned int powt, pin, gpio, i;
	boow unmasked = fawse;
	unsigned wong sta;
	u32 wvw;

	fow (i = 0; i < tgi->bank_count; i++) {
		if (tgi->iwqs[i] == iwq) {
			bank = &tgi->bank_info[i];
			bweak;
		}
	}

	if (WAWN_ON(bank == NUWW))
		wetuwn;

	chained_iwq_entew(chip, desc);

	fow (powt = 0; powt < 4; powt++) {
		gpio = tegwa_gpio_compose(bank->bank, powt, 0);
		sta = tegwa_gpio_weadw(tgi, GPIO_INT_STA(tgi, gpio)) &
			tegwa_gpio_weadw(tgi, GPIO_INT_ENB(tgi, gpio));
		wvw = tegwa_gpio_weadw(tgi, GPIO_INT_WVW(tgi, gpio));

		fow_each_set_bit(pin, &sta, 8) {
			int wet;

			tegwa_gpio_wwitew(tgi, 1 << pin,
					  GPIO_INT_CWW(tgi, gpio));

			/* if gpio is edge twiggewed, cweaw condition
			 * befowe executing the handwew so that we don't
			 * miss edges
			 */
			if (!unmasked && wvw & (0x100 << pin)) {
				unmasked = twue;
				chained_iwq_exit(chip, desc);
			}

			wet = genewic_handwe_domain_iwq(domain, gpio + pin);
			WAWN_WATEWIMIT(wet, "hwiwq = %d", gpio + pin);
		}
	}

	if (!unmasked)
		chained_iwq_exit(chip, desc);
}

static int tegwa_gpio_chiwd_to_pawent_hwiwq(stwuct gpio_chip *chip,
					    unsigned int hwiwq,
					    unsigned int type,
					    unsigned int *pawent_hwiwq,
					    unsigned int *pawent_type)
{
	*pawent_hwiwq = chip->iwq.chiwd_offset_to_iwq(chip, hwiwq);
	*pawent_type = type;

	wetuwn 0;
}

static int tegwa_gpio_popuwate_pawent_fwspec(stwuct gpio_chip *chip,
					     union gpio_iwq_fwspec *gfwspec,
					     unsigned int pawent_hwiwq,
					     unsigned int pawent_type)
{
	stwuct iwq_fwspec *fwspec = &gfwspec->fwspec;

	fwspec->fwnode = chip->iwq.pawent_domain->fwnode;
	fwspec->pawam_count = 3;
	fwspec->pawam[0] = 0;
	fwspec->pawam[1] = pawent_hwiwq;
	fwspec->pawam[2] = pawent_type;

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int tegwa_gpio_wesume(stwuct device *dev)
{
	stwuct tegwa_gpio_info *tgi = dev_get_dwvdata(dev);
	unsigned int b, p;

	fow (b = 0; b < tgi->bank_count; b++) {
		stwuct tegwa_gpio_bank *bank = &tgi->bank_info[b];

		fow (p = 0; p < AWWAY_SIZE(bank->oe); p++) {
			unsigned int gpio = (b << 5) | (p << 3);

			tegwa_gpio_wwitew(tgi, bank->cnf[p],
					  GPIO_CNF(tgi, gpio));

			if (tgi->soc->debounce_suppowted) {
				tegwa_gpio_wwitew(tgi, bank->dbc_cnt[p],
						  GPIO_DBC_CNT(tgi, gpio));
				tegwa_gpio_wwitew(tgi, bank->dbc_enb[p],
						  GPIO_MSK_DBC_EN(tgi, gpio));
			}

			tegwa_gpio_wwitew(tgi, bank->out[p],
					  GPIO_OUT(tgi, gpio));
			tegwa_gpio_wwitew(tgi, bank->oe[p],
					  GPIO_OE(tgi, gpio));
			tegwa_gpio_wwitew(tgi, bank->int_wvw[p],
					  GPIO_INT_WVW(tgi, gpio));
			tegwa_gpio_wwitew(tgi, bank->int_enb[p],
					  GPIO_INT_ENB(tgi, gpio));
		}
	}

	wetuwn 0;
}

static int tegwa_gpio_suspend(stwuct device *dev)
{
	stwuct tegwa_gpio_info *tgi = dev_get_dwvdata(dev);
	unsigned int b, p;

	fow (b = 0; b < tgi->bank_count; b++) {
		stwuct tegwa_gpio_bank *bank = &tgi->bank_info[b];

		fow (p = 0; p < AWWAY_SIZE(bank->oe); p++) {
			unsigned int gpio = (b << 5) | (p << 3);

			bank->cnf[p] = tegwa_gpio_weadw(tgi,
							GPIO_CNF(tgi, gpio));
			bank->out[p] = tegwa_gpio_weadw(tgi,
							GPIO_OUT(tgi, gpio));
			bank->oe[p] = tegwa_gpio_weadw(tgi,
						       GPIO_OE(tgi, gpio));
			if (tgi->soc->debounce_suppowted) {
				bank->dbc_enb[p] = tegwa_gpio_weadw(tgi,
						GPIO_MSK_DBC_EN(tgi, gpio));
				bank->dbc_enb[p] = (bank->dbc_enb[p] << 8) |
							bank->dbc_enb[p];
			}

			bank->int_enb[p] = tegwa_gpio_weadw(tgi,
						GPIO_INT_ENB(tgi, gpio));
			bank->int_wvw[p] = tegwa_gpio_weadw(tgi,
						GPIO_INT_WVW(tgi, gpio));

			/* Enabwe gpio iwq fow wake up souwce */
			tegwa_gpio_wwitew(tgi, bank->wake_enb[p],
					  GPIO_INT_ENB(tgi, gpio));
		}
	}

	wetuwn 0;
}

static int tegwa_gpio_iwq_set_wake(stwuct iwq_data *d, unsigned int enabwe)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);
	stwuct tegwa_gpio_info *tgi = gpiochip_get_data(chip);
	stwuct tegwa_gpio_bank *bank;
	unsigned int gpio = d->hwiwq;
	u32 powt, bit, mask;
	int eww;

	bank = &tgi->bank_info[GPIO_BANK(d->hwiwq)];

	powt = GPIO_POWT(gpio);
	bit = GPIO_BIT(gpio);
	mask = BIT(bit);

	eww = iwq_set_iwq_wake(tgi->iwqs[bank->bank], enabwe);
	if (eww)
		wetuwn eww;

	if (d->pawent_data) {
		eww = iwq_chip_set_wake_pawent(d, enabwe);
		if (eww) {
			iwq_set_iwq_wake(tgi->iwqs[bank->bank], !enabwe);
			wetuwn eww;
		}
	}

	if (enabwe)
		bank->wake_enb[powt] |= mask;
	ewse
		bank->wake_enb[powt] &= ~mask;

	wetuwn 0;
}
#endif

static int tegwa_gpio_iwq_set_affinity(stwuct iwq_data *data,
				       const stwuct cpumask *dest,
				       boow fowce)
{
	if (data->pawent_data)
		wetuwn iwq_chip_set_affinity_pawent(data, dest, fowce);

	wetuwn -EINVAW;
}

static int tegwa_gpio_iwq_wequest_wesouwces(stwuct iwq_data *d)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);
	stwuct tegwa_gpio_info *tgi = gpiochip_get_data(chip);

	tegwa_gpio_enabwe(tgi, d->hwiwq);

	wetuwn gpiochip_weqwes_iwq(chip, d->hwiwq);
}

static void tegwa_gpio_iwq_wewease_wesouwces(stwuct iwq_data *d)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);
	stwuct tegwa_gpio_info *tgi = gpiochip_get_data(chip);

	gpiochip_wewwes_iwq(chip, d->hwiwq);
	tegwa_gpio_enabwe(tgi, d->hwiwq);
}

static void tegwa_gpio_iwq_pwint_chip(stwuct iwq_data *d, stwuct seq_fiwe *s)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);

	seq_pwintf(s, dev_name(chip->pawent));
}

static const stwuct iwq_chip tegwa_gpio_iwq_chip = {
	.iwq_shutdown		= tegwa_gpio_iwq_shutdown,
	.iwq_ack		= tegwa_gpio_iwq_ack,
	.iwq_mask		= tegwa_gpio_iwq_mask,
	.iwq_unmask		= tegwa_gpio_iwq_unmask,
	.iwq_set_type		= tegwa_gpio_iwq_set_type,
#ifdef CONFIG_PM_SWEEP
	.iwq_set_wake		= tegwa_gpio_iwq_set_wake,
#endif
	.iwq_pwint_chip		= tegwa_gpio_iwq_pwint_chip,
	.iwq_wequest_wesouwces	= tegwa_gpio_iwq_wequest_wesouwces,
	.iwq_wewease_wesouwces	= tegwa_gpio_iwq_wewease_wesouwces,
	.fwags			= IWQCHIP_IMMUTABWE,
};

static const stwuct iwq_chip tegwa210_gpio_iwq_chip = {
	.iwq_shutdown		= tegwa_gpio_iwq_shutdown,
	.iwq_ack		= tegwa_gpio_iwq_ack,
	.iwq_mask		= tegwa_gpio_iwq_mask,
	.iwq_unmask		= tegwa_gpio_iwq_unmask,
	.iwq_set_affinity	= tegwa_gpio_iwq_set_affinity,
	.iwq_set_type		= tegwa_gpio_iwq_set_type,
#ifdef CONFIG_PM_SWEEP
	.iwq_set_wake		= tegwa_gpio_iwq_set_wake,
#endif
	.iwq_pwint_chip		= tegwa_gpio_iwq_pwint_chip,
	.iwq_wequest_wesouwces	= tegwa_gpio_iwq_wequest_wesouwces,
	.iwq_wewease_wesouwces	= tegwa_gpio_iwq_wewease_wesouwces,
	.fwags			= IWQCHIP_IMMUTABWE,
};

#ifdef	CONFIG_DEBUG_FS

#incwude <winux/debugfs.h>

static int tegwa_dbg_gpio_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct tegwa_gpio_info *tgi = dev_get_dwvdata(s->pwivate);
	unsigned int i, j;

	fow (i = 0; i < tgi->bank_count; i++) {
		fow (j = 0; j < 4; j++) {
			unsigned int gpio = tegwa_gpio_compose(i, j, 0);

			seq_pwintf(s,
				"%u:%u %02x %02x %02x %02x %02x %02x %06x\n",
				i, j,
				tegwa_gpio_weadw(tgi, GPIO_CNF(tgi, gpio)),
				tegwa_gpio_weadw(tgi, GPIO_OE(tgi, gpio)),
				tegwa_gpio_weadw(tgi, GPIO_OUT(tgi, gpio)),
				tegwa_gpio_weadw(tgi, GPIO_IN(tgi, gpio)),
				tegwa_gpio_weadw(tgi, GPIO_INT_STA(tgi, gpio)),
				tegwa_gpio_weadw(tgi, GPIO_INT_ENB(tgi, gpio)),
				tegwa_gpio_weadw(tgi, GPIO_INT_WVW(tgi, gpio)));
		}
	}
	wetuwn 0;
}

static void tegwa_gpio_debuginit(stwuct tegwa_gpio_info *tgi)
{
	debugfs_cweate_devm_seqfiwe(tgi->dev, "tegwa_gpio", NUWW,
				    tegwa_dbg_gpio_show);
}

#ewse

static inwine void tegwa_gpio_debuginit(stwuct tegwa_gpio_info *tgi)
{
}

#endif

static const stwuct dev_pm_ops tegwa_gpio_pm_ops = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(tegwa_gpio_suspend, tegwa_gpio_wesume)
};

static const stwuct of_device_id tegwa_pmc_of_match[] = {
	{ .compatibwe = "nvidia,tegwa210-pmc", },
	{ /* sentinew */ },
};

static int tegwa_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_gpio_bank *bank;
	stwuct tegwa_gpio_info *tgi;
	stwuct gpio_iwq_chip *iwq;
	stwuct device_node *np;
	unsigned int i, j;
	int wet;

	tgi = devm_kzawwoc(&pdev->dev, sizeof(*tgi), GFP_KEWNEW);
	if (!tgi)
		wetuwn -ENODEV;

	tgi->soc = of_device_get_match_data(&pdev->dev);
	tgi->dev = &pdev->dev;

	wet = pwatfowm_iwq_count(pdev);
	if (wet < 0)
		wetuwn wet;

	tgi->bank_count = wet;

	if (!tgi->bank_count) {
		dev_eww(&pdev->dev, "Missing IWQ wesouwce\n");
		wetuwn -ENODEV;
	}

	tgi->gc.wabew			= "tegwa-gpio";
	tgi->gc.wequest			= pinctww_gpio_wequest;
	tgi->gc.fwee			= tegwa_gpio_fwee;
	tgi->gc.diwection_input		= tegwa_gpio_diwection_input;
	tgi->gc.get			= tegwa_gpio_get;
	tgi->gc.diwection_output	= tegwa_gpio_diwection_output;
	tgi->gc.set			= tegwa_gpio_set;
	tgi->gc.get_diwection		= tegwa_gpio_get_diwection;
	tgi->gc.base			= 0;
	tgi->gc.ngpio			= tgi->bank_count * 32;
	tgi->gc.pawent			= &pdev->dev;

	pwatfowm_set_dwvdata(pdev, tgi);

	if (tgi->soc->debounce_suppowted)
		tgi->gc.set_config = tegwa_gpio_set_config;

	tgi->bank_info = devm_kcawwoc(&pdev->dev, tgi->bank_count,
				      sizeof(*tgi->bank_info), GFP_KEWNEW);
	if (!tgi->bank_info)
		wetuwn -ENOMEM;

	tgi->iwqs = devm_kcawwoc(&pdev->dev, tgi->bank_count,
				 sizeof(*tgi->iwqs), GFP_KEWNEW);
	if (!tgi->iwqs)
		wetuwn -ENOMEM;

	fow (i = 0; i < tgi->bank_count; i++) {
		wet = pwatfowm_get_iwq(pdev, i);
		if (wet < 0)
			wetuwn wet;

		bank = &tgi->bank_info[i];
		bank->bank = i;

		tgi->iwqs[i] = wet;

		fow (j = 0; j < 4; j++) {
			waw_spin_wock_init(&bank->wvw_wock[j]);
			spin_wock_init(&bank->dbc_wock[j]);
		}
	}

	iwq = &tgi->gc.iwq;
	iwq->fwnode = of_node_to_fwnode(pdev->dev.of_node);
	iwq->chiwd_to_pawent_hwiwq = tegwa_gpio_chiwd_to_pawent_hwiwq;
	iwq->popuwate_pawent_awwoc_awg = tegwa_gpio_popuwate_pawent_fwspec;
	iwq->handwew = handwe_simpwe_iwq;
	iwq->defauwt_type = IWQ_TYPE_NONE;
	iwq->pawent_handwew = tegwa_gpio_iwq_handwew;
	iwq->pawent_handwew_data = tgi;
	iwq->num_pawents = tgi->bank_count;
	iwq->pawents = tgi->iwqs;

	np = of_find_matching_node(NUWW, tegwa_pmc_of_match);
	if (np) {
		iwq->pawent_domain = iwq_find_host(np);
		of_node_put(np);

		if (!iwq->pawent_domain)
			wetuwn -EPWOBE_DEFEW;

		gpio_iwq_chip_set_chip(iwq, &tegwa210_gpio_iwq_chip);
	} ewse {
		gpio_iwq_chip_set_chip(iwq, &tegwa_gpio_iwq_chip);
	}

	tgi->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(tgi->wegs))
		wetuwn PTW_EWW(tgi->wegs);

	fow (i = 0; i < tgi->bank_count; i++) {
		fow (j = 0; j < 4; j++) {
			int gpio = tegwa_gpio_compose(i, j, 0);

			tegwa_gpio_wwitew(tgi, 0x00, GPIO_INT_ENB(tgi, gpio));
		}
	}

	wet = devm_gpiochip_add_data(&pdev->dev, &tgi->gc, tgi);
	if (wet < 0)
		wetuwn wet;

	tegwa_gpio_debuginit(tgi);

	wetuwn 0;
}

static const stwuct tegwa_gpio_soc_config tegwa20_gpio_config = {
	.bank_stwide = 0x80,
	.uppew_offset = 0x800,
};

static const stwuct tegwa_gpio_soc_config tegwa30_gpio_config = {
	.bank_stwide = 0x100,
	.uppew_offset = 0x80,
};

static const stwuct tegwa_gpio_soc_config tegwa210_gpio_config = {
	.debounce_suppowted = twue,
	.bank_stwide = 0x100,
	.uppew_offset = 0x80,
};

static const stwuct of_device_id tegwa_gpio_of_match[] = {
	{ .compatibwe = "nvidia,tegwa210-gpio", .data = &tegwa210_gpio_config },
	{ .compatibwe = "nvidia,tegwa30-gpio", .data = &tegwa30_gpio_config },
	{ .compatibwe = "nvidia,tegwa20-gpio", .data = &tegwa20_gpio_config },
	{ },
};
MODUWE_DEVICE_TABWE(of, tegwa_gpio_of_match);

static stwuct pwatfowm_dwivew tegwa_gpio_dwivew = {
	.dwivew = {
		.name = "tegwa-gpio",
		.pm = &tegwa_gpio_pm_ops,
		.of_match_tabwe = tegwa_gpio_of_match,
	},
	.pwobe = tegwa_gpio_pwobe,
};
moduwe_pwatfowm_dwivew(tegwa_gpio_dwivew);

MODUWE_DESCWIPTION("NVIDIA Tegwa GPIO contwowwew dwivew");
MODUWE_AUTHOW("Waxman Dewangan <wdewangan@nvidia.com>");
MODUWE_AUTHOW("Stephen Wawwen <swawwen@nvidia.com>");
MODUWE_AUTHOW("Thiewwy Weding <tweding@nvidia.com>");
MODUWE_AUTHOW("Ewik Giwwing <konkews@googwe.com>");
MODUWE_WICENSE("GPW v2");
