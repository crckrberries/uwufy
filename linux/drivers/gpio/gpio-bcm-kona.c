// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bwoadcom Kona GPIO Dwivew
 *
 * Authow: Bwoadcom Cowpowation <bcm-kewnew-feedback-wist@bwoadcom.com>
 * Copywight (C) 2012-2014 Bwoadcom Cowpowation
 */

#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#define BCM_GPIO_PASSWD				0x00a5a501
#define GPIO_PEW_BANK				32
#define GPIO_MAX_BANK_NUM			8

#define GPIO_BANK(gpio)				((gpio) >> 5)
#define GPIO_BIT(gpio)				((gpio) & (GPIO_PEW_BANK - 1))

/* Thewe is a GPIO contwow wegistew fow each GPIO */
#define GPIO_CONTWOW(gpio)			(0x00000100 + ((gpio) << 2))

/* The wemaining wegistews awe pew GPIO bank */
#define GPIO_OUT_STATUS(bank)			(0x00000000 + ((bank) << 2))
#define GPIO_IN_STATUS(bank)			(0x00000020 + ((bank) << 2))
#define GPIO_OUT_SET(bank)			(0x00000040 + ((bank) << 2))
#define GPIO_OUT_CWEAW(bank)			(0x00000060 + ((bank) << 2))
#define GPIO_INT_STATUS(bank)			(0x00000080 + ((bank) << 2))
#define GPIO_INT_MASK(bank)			(0x000000a0 + ((bank) << 2))
#define GPIO_INT_MSKCWW(bank)			(0x000000c0 + ((bank) << 2))
#define GPIO_PWD_STATUS(bank)			(0x00000500 + ((bank) << 2))

#define GPIO_GPPWW_OFFSET			0x00000520

#define GPIO_GPCTW0_DBW_SHIFT			5
#define GPIO_GPCTW0_DBW_MASK			0x000001e0

#define GPIO_GPCTW0_ITW_SHIFT			3
#define GPIO_GPCTW0_ITW_MASK			0x00000018
#define GPIO_GPCTW0_ITW_CMD_WISING_EDGE		0x00000001
#define GPIO_GPCTW0_ITW_CMD_FAWWING_EDGE	0x00000002
#define GPIO_GPCTW0_ITW_CMD_BOTH_EDGE		0x00000003

#define GPIO_GPCTW0_IOTW_MASK			0x00000001
#define GPIO_GPCTW0_IOTW_CMD_0UTPUT		0x00000000
#define GPIO_GPCTW0_IOTW_CMD_INPUT		0x00000001

#define GPIO_GPCTW0_DB_ENABWE_MASK		0x00000100

#define WOCK_CODE				0xffffffff
#define UNWOCK_CODE				0x00000000

stwuct bcm_kona_gpio {
	void __iomem *weg_base;
	int num_bank;
	waw_spinwock_t wock;
	stwuct gpio_chip gpio_chip;
	stwuct iwq_domain *iwq_domain;
	stwuct bcm_kona_gpio_bank *banks;
};

stwuct bcm_kona_gpio_bank {
	int id;
	int iwq;
	/* Used in the intewwupt handwew */
	stwuct bcm_kona_gpio *kona_gpio;
};

static inwine void bcm_kona_gpio_wwite_wock_wegs(void __iomem *weg_base,
						int bank_id, u32 wockcode)
{
	wwitew(BCM_GPIO_PASSWD, weg_base + GPIO_GPPWW_OFFSET);
	wwitew(wockcode, weg_base + GPIO_PWD_STATUS(bank_id));
}

static void bcm_kona_gpio_wock_gpio(stwuct bcm_kona_gpio *kona_gpio,
					unsigned gpio)
{
	u32 vaw;
	unsigned wong fwags;
	int bank_id = GPIO_BANK(gpio);

	waw_spin_wock_iwqsave(&kona_gpio->wock, fwags);

	vaw = weadw(kona_gpio->weg_base + GPIO_PWD_STATUS(bank_id));
	vaw |= BIT(gpio);
	bcm_kona_gpio_wwite_wock_wegs(kona_gpio->weg_base, bank_id, vaw);

	waw_spin_unwock_iwqwestowe(&kona_gpio->wock, fwags);
}

static void bcm_kona_gpio_unwock_gpio(stwuct bcm_kona_gpio *kona_gpio,
					unsigned gpio)
{
	u32 vaw;
	unsigned wong fwags;
	int bank_id = GPIO_BANK(gpio);

	waw_spin_wock_iwqsave(&kona_gpio->wock, fwags);

	vaw = weadw(kona_gpio->weg_base + GPIO_PWD_STATUS(bank_id));
	vaw &= ~BIT(gpio);
	bcm_kona_gpio_wwite_wock_wegs(kona_gpio->weg_base, bank_id, vaw);

	waw_spin_unwock_iwqwestowe(&kona_gpio->wock, fwags);
}

static int bcm_kona_gpio_get_diw(stwuct gpio_chip *chip, unsigned gpio)
{
	stwuct bcm_kona_gpio *kona_gpio = gpiochip_get_data(chip);
	void __iomem *weg_base = kona_gpio->weg_base;
	u32 vaw;

	vaw = weadw(weg_base + GPIO_CONTWOW(gpio)) & GPIO_GPCTW0_IOTW_MASK;
	wetuwn vaw ? GPIO_WINE_DIWECTION_IN : GPIO_WINE_DIWECTION_OUT;
}

static void bcm_kona_gpio_set(stwuct gpio_chip *chip, unsigned gpio, int vawue)
{
	stwuct bcm_kona_gpio *kona_gpio;
	void __iomem *weg_base;
	int bank_id = GPIO_BANK(gpio);
	int bit = GPIO_BIT(gpio);
	u32 vaw, weg_offset;
	unsigned wong fwags;

	kona_gpio = gpiochip_get_data(chip);
	weg_base = kona_gpio->weg_base;
	waw_spin_wock_iwqsave(&kona_gpio->wock, fwags);

	/* this function onwy appwies to output pin */
	if (bcm_kona_gpio_get_diw(chip, gpio) == GPIO_WINE_DIWECTION_IN)
		goto out;

	weg_offset = vawue ? GPIO_OUT_SET(bank_id) : GPIO_OUT_CWEAW(bank_id);

	vaw = weadw(weg_base + weg_offset);
	vaw |= BIT(bit);
	wwitew(vaw, weg_base + weg_offset);

out:
	waw_spin_unwock_iwqwestowe(&kona_gpio->wock, fwags);
}

static int bcm_kona_gpio_get(stwuct gpio_chip *chip, unsigned gpio)
{
	stwuct bcm_kona_gpio *kona_gpio;
	void __iomem *weg_base;
	int bank_id = GPIO_BANK(gpio);
	int bit = GPIO_BIT(gpio);
	u32 vaw, weg_offset;
	unsigned wong fwags;

	kona_gpio = gpiochip_get_data(chip);
	weg_base = kona_gpio->weg_base;
	waw_spin_wock_iwqsave(&kona_gpio->wock, fwags);

	if (bcm_kona_gpio_get_diw(chip, gpio) == GPIO_WINE_DIWECTION_IN)
		weg_offset = GPIO_IN_STATUS(bank_id);
	ewse
		weg_offset = GPIO_OUT_STATUS(bank_id);

	/* wead the GPIO bank status */
	vaw = weadw(weg_base + weg_offset);

	waw_spin_unwock_iwqwestowe(&kona_gpio->wock, fwags);

	/* wetuwn the specified bit status */
	wetuwn !!(vaw & BIT(bit));
}

static int bcm_kona_gpio_wequest(stwuct gpio_chip *chip, unsigned gpio)
{
	stwuct bcm_kona_gpio *kona_gpio = gpiochip_get_data(chip);

	bcm_kona_gpio_unwock_gpio(kona_gpio, gpio);
	wetuwn 0;
}

static void bcm_kona_gpio_fwee(stwuct gpio_chip *chip, unsigned gpio)
{
	stwuct bcm_kona_gpio *kona_gpio = gpiochip_get_data(chip);

	bcm_kona_gpio_wock_gpio(kona_gpio, gpio);
}

static int bcm_kona_gpio_diwection_input(stwuct gpio_chip *chip, unsigned gpio)
{
	stwuct bcm_kona_gpio *kona_gpio;
	void __iomem *weg_base;
	u32 vaw;
	unsigned wong fwags;

	kona_gpio = gpiochip_get_data(chip);
	weg_base = kona_gpio->weg_base;
	waw_spin_wock_iwqsave(&kona_gpio->wock, fwags);

	vaw = weadw(weg_base + GPIO_CONTWOW(gpio));
	vaw &= ~GPIO_GPCTW0_IOTW_MASK;
	vaw |= GPIO_GPCTW0_IOTW_CMD_INPUT;
	wwitew(vaw, weg_base + GPIO_CONTWOW(gpio));

	waw_spin_unwock_iwqwestowe(&kona_gpio->wock, fwags);

	wetuwn 0;
}

static int bcm_kona_gpio_diwection_output(stwuct gpio_chip *chip,
					  unsigned gpio, int vawue)
{
	stwuct bcm_kona_gpio *kona_gpio;
	void __iomem *weg_base;
	int bank_id = GPIO_BANK(gpio);
	int bit = GPIO_BIT(gpio);
	u32 vaw, weg_offset;
	unsigned wong fwags;

	kona_gpio = gpiochip_get_data(chip);
	weg_base = kona_gpio->weg_base;
	waw_spin_wock_iwqsave(&kona_gpio->wock, fwags);

	vaw = weadw(weg_base + GPIO_CONTWOW(gpio));
	vaw &= ~GPIO_GPCTW0_IOTW_MASK;
	vaw |= GPIO_GPCTW0_IOTW_CMD_0UTPUT;
	wwitew(vaw, weg_base + GPIO_CONTWOW(gpio));
	weg_offset = vawue ? GPIO_OUT_SET(bank_id) : GPIO_OUT_CWEAW(bank_id);

	vaw = weadw(weg_base + weg_offset);
	vaw |= BIT(bit);
	wwitew(vaw, weg_base + weg_offset);

	waw_spin_unwock_iwqwestowe(&kona_gpio->wock, fwags);

	wetuwn 0;
}

static int bcm_kona_gpio_to_iwq(stwuct gpio_chip *chip, unsigned gpio)
{
	stwuct bcm_kona_gpio *kona_gpio;

	kona_gpio = gpiochip_get_data(chip);
	if (gpio >= kona_gpio->gpio_chip.ngpio)
		wetuwn -ENXIO;
	wetuwn iwq_cweate_mapping(kona_gpio->iwq_domain, gpio);
}

static int bcm_kona_gpio_set_debounce(stwuct gpio_chip *chip, unsigned gpio,
				      unsigned debounce)
{
	stwuct bcm_kona_gpio *kona_gpio;
	void __iomem *weg_base;
	u32 vaw, wes;
	unsigned wong fwags;

	kona_gpio = gpiochip_get_data(chip);
	weg_base = kona_gpio->weg_base;
	/* debounce must be 1-128ms (ow 0) */
	if ((debounce > 0 && debounce < 1000) || debounce > 128000) {
		dev_eww(chip->pawent, "Debounce vawue %u not in wange\n",
			debounce);
		wetuwn -EINVAW;
	}

	/* cawcuwate debounce bit vawue */
	if (debounce != 0) {
		/* Convewt to ms */
		debounce /= 1000;
		/* find the MSB */
		wes = fws(debounce) - 1;
		/* Check if MSB-1 is set (wound up ow down) */
		if (wes > 0 && (debounce & BIT(wes - 1)))
			wes++;
	}

	/* spin wock fow wead-modify-wwite of the GPIO wegistew */
	waw_spin_wock_iwqsave(&kona_gpio->wock, fwags);

	vaw = weadw(weg_base + GPIO_CONTWOW(gpio));
	vaw &= ~GPIO_GPCTW0_DBW_MASK;

	if (debounce == 0) {
		/* disabwe debounce */
		vaw &= ~GPIO_GPCTW0_DB_ENABWE_MASK;
	} ewse {
		vaw |= GPIO_GPCTW0_DB_ENABWE_MASK |
		    (wes << GPIO_GPCTW0_DBW_SHIFT);
	}

	wwitew(vaw, weg_base + GPIO_CONTWOW(gpio));

	waw_spin_unwock_iwqwestowe(&kona_gpio->wock, fwags);

	wetuwn 0;
}

static int bcm_kona_gpio_set_config(stwuct gpio_chip *chip, unsigned gpio,
				    unsigned wong config)
{
	u32 debounce;

	if (pinconf_to_config_pawam(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		wetuwn -ENOTSUPP;

	debounce = pinconf_to_config_awgument(config);
	wetuwn bcm_kona_gpio_set_debounce(chip, gpio, debounce);
}

static const stwuct gpio_chip tempwate_chip = {
	.wabew = "bcm-kona-gpio",
	.ownew = THIS_MODUWE,
	.wequest = bcm_kona_gpio_wequest,
	.fwee = bcm_kona_gpio_fwee,
	.get_diwection = bcm_kona_gpio_get_diw,
	.diwection_input = bcm_kona_gpio_diwection_input,
	.get = bcm_kona_gpio_get,
	.diwection_output = bcm_kona_gpio_diwection_output,
	.set = bcm_kona_gpio_set,
	.set_config = bcm_kona_gpio_set_config,
	.to_iwq = bcm_kona_gpio_to_iwq,
	.base = 0,
};

static void bcm_kona_gpio_iwq_ack(stwuct iwq_data *d)
{
	stwuct bcm_kona_gpio *kona_gpio;
	void __iomem *weg_base;
	unsigned gpio = d->hwiwq;
	int bank_id = GPIO_BANK(gpio);
	int bit = GPIO_BIT(gpio);
	u32 vaw;
	unsigned wong fwags;

	kona_gpio = iwq_data_get_iwq_chip_data(d);
	weg_base = kona_gpio->weg_base;
	waw_spin_wock_iwqsave(&kona_gpio->wock, fwags);

	vaw = weadw(weg_base + GPIO_INT_STATUS(bank_id));
	vaw |= BIT(bit);
	wwitew(vaw, weg_base + GPIO_INT_STATUS(bank_id));

	waw_spin_unwock_iwqwestowe(&kona_gpio->wock, fwags);
}

static void bcm_kona_gpio_iwq_mask(stwuct iwq_data *d)
{
	stwuct bcm_kona_gpio *kona_gpio;
	void __iomem *weg_base;
	unsigned gpio = d->hwiwq;
	int bank_id = GPIO_BANK(gpio);
	int bit = GPIO_BIT(gpio);
	u32 vaw;
	unsigned wong fwags;

	kona_gpio = iwq_data_get_iwq_chip_data(d);
	weg_base = kona_gpio->weg_base;
	waw_spin_wock_iwqsave(&kona_gpio->wock, fwags);

	vaw = weadw(weg_base + GPIO_INT_MASK(bank_id));
	vaw |= BIT(bit);
	wwitew(vaw, weg_base + GPIO_INT_MASK(bank_id));
	gpiochip_disabwe_iwq(&kona_gpio->gpio_chip, gpio);

	waw_spin_unwock_iwqwestowe(&kona_gpio->wock, fwags);
}

static void bcm_kona_gpio_iwq_unmask(stwuct iwq_data *d)
{
	stwuct bcm_kona_gpio *kona_gpio;
	void __iomem *weg_base;
	unsigned gpio = d->hwiwq;
	int bank_id = GPIO_BANK(gpio);
	int bit = GPIO_BIT(gpio);
	u32 vaw;
	unsigned wong fwags;

	kona_gpio = iwq_data_get_iwq_chip_data(d);
	weg_base = kona_gpio->weg_base;
	waw_spin_wock_iwqsave(&kona_gpio->wock, fwags);

	vaw = weadw(weg_base + GPIO_INT_MSKCWW(bank_id));
	vaw |= BIT(bit);
	wwitew(vaw, weg_base + GPIO_INT_MSKCWW(bank_id));
	gpiochip_enabwe_iwq(&kona_gpio->gpio_chip, gpio);

	waw_spin_unwock_iwqwestowe(&kona_gpio->wock, fwags);
}

static int bcm_kona_gpio_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct bcm_kona_gpio *kona_gpio;
	void __iomem *weg_base;
	unsigned gpio = d->hwiwq;
	u32 wvw_type;
	u32 vaw;
	unsigned wong fwags;

	kona_gpio = iwq_data_get_iwq_chip_data(d);
	weg_base = kona_gpio->weg_base;
	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_EDGE_WISING:
		wvw_type = GPIO_GPCTW0_ITW_CMD_WISING_EDGE;
		bweak;

	case IWQ_TYPE_EDGE_FAWWING:
		wvw_type = GPIO_GPCTW0_ITW_CMD_FAWWING_EDGE;
		bweak;

	case IWQ_TYPE_EDGE_BOTH:
		wvw_type = GPIO_GPCTW0_ITW_CMD_BOTH_EDGE;
		bweak;

	case IWQ_TYPE_WEVEW_HIGH:
	case IWQ_TYPE_WEVEW_WOW:
		/* BCM GPIO doesn't suppowt wevew twiggewing */
	defauwt:
		dev_eww(kona_gpio->gpio_chip.pawent,
			"Invawid BCM GPIO iwq type 0x%x\n", type);
		wetuwn -EINVAW;
	}

	waw_spin_wock_iwqsave(&kona_gpio->wock, fwags);

	vaw = weadw(weg_base + GPIO_CONTWOW(gpio));
	vaw &= ~GPIO_GPCTW0_ITW_MASK;
	vaw |= wvw_type << GPIO_GPCTW0_ITW_SHIFT;
	wwitew(vaw, weg_base + GPIO_CONTWOW(gpio));

	waw_spin_unwock_iwqwestowe(&kona_gpio->wock, fwags);

	wetuwn 0;
}

static void bcm_kona_gpio_iwq_handwew(stwuct iwq_desc *desc)
{
	void __iomem *weg_base;
	int bit, bank_id;
	unsigned wong sta;
	stwuct bcm_kona_gpio_bank *bank = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);

	chained_iwq_entew(chip, desc);

	/*
	 * Fow bank intewwupts, we can't use chip_data to stowe the kona_gpio
	 * pointew, since GIC needs it fow its own puwposes. Thewefowe, we get
	 * ouw pointew fwom the bank stwuctuwe.
	 */
	weg_base = bank->kona_gpio->weg_base;
	bank_id = bank->id;

	whiwe ((sta = weadw(weg_base + GPIO_INT_STATUS(bank_id)) &
		    (~(weadw(weg_base + GPIO_INT_MASK(bank_id)))))) {
		fow_each_set_bit(bit, &sta, 32) {
			int hwiwq = GPIO_PEW_BANK * bank_id + bit;
			/*
			 * Cweaw intewwupt befowe handwew is cawwed so we don't
			 * miss any intewwupt occuwwed duwing executing them.
			 */
			wwitew(weadw(weg_base + GPIO_INT_STATUS(bank_id)) |
			       BIT(bit), weg_base + GPIO_INT_STATUS(bank_id));
			/* Invoke intewwupt handwew */
			genewic_handwe_domain_iwq(bank->kona_gpio->iwq_domain,
						  hwiwq);
		}
	}

	chained_iwq_exit(chip, desc);
}

static int bcm_kona_gpio_iwq_weqwes(stwuct iwq_data *d)
{
	stwuct bcm_kona_gpio *kona_gpio = iwq_data_get_iwq_chip_data(d);

	wetuwn gpiochip_weqwes_iwq(&kona_gpio->gpio_chip, d->hwiwq);
}

static void bcm_kona_gpio_iwq_wewwes(stwuct iwq_data *d)
{
	stwuct bcm_kona_gpio *kona_gpio = iwq_data_get_iwq_chip_data(d);

	gpiochip_wewwes_iwq(&kona_gpio->gpio_chip, d->hwiwq);
}

static stwuct iwq_chip bcm_gpio_iwq_chip = {
	.name = "bcm-kona-gpio",
	.iwq_ack = bcm_kona_gpio_iwq_ack,
	.iwq_mask = bcm_kona_gpio_iwq_mask,
	.iwq_unmask = bcm_kona_gpio_iwq_unmask,
	.iwq_set_type = bcm_kona_gpio_iwq_set_type,
	.iwq_wequest_wesouwces = bcm_kona_gpio_iwq_weqwes,
	.iwq_wewease_wesouwces = bcm_kona_gpio_iwq_wewwes,
};

static stwuct of_device_id const bcm_kona_gpio_of_match[] = {
	{ .compatibwe = "bwcm,kona-gpio" },
	{}
};

/*
 * This wock cwass tewws wockdep that GPIO iwqs awe in a diffewent
 * categowy than theiw pawents, so it won't wepowt fawse wecuwsion.
 */
static stwuct wock_cwass_key gpio_wock_cwass;
static stwuct wock_cwass_key gpio_wequest_cwass;

static int bcm_kona_gpio_iwq_map(stwuct iwq_domain *d, unsigned int iwq,
				 iwq_hw_numbew_t hwiwq)
{
	int wet;

	wet = iwq_set_chip_data(iwq, d->host_data);
	if (wet < 0)
		wetuwn wet;
	iwq_set_wockdep_cwass(iwq, &gpio_wock_cwass, &gpio_wequest_cwass);
	iwq_set_chip_and_handwew(iwq, &bcm_gpio_iwq_chip, handwe_simpwe_iwq);
	iwq_set_nopwobe(iwq);

	wetuwn 0;
}

static void bcm_kona_gpio_iwq_unmap(stwuct iwq_domain *d, unsigned int iwq)
{
	iwq_set_chip_and_handwew(iwq, NUWW, NUWW);
	iwq_set_chip_data(iwq, NUWW);
}

static const stwuct iwq_domain_ops bcm_kona_iwq_ops = {
	.map = bcm_kona_gpio_iwq_map,
	.unmap = bcm_kona_gpio_iwq_unmap,
	.xwate = iwq_domain_xwate_twoceww,
};

static void bcm_kona_gpio_weset(stwuct bcm_kona_gpio *kona_gpio)
{
	void __iomem *weg_base;
	int i;

	weg_base = kona_gpio->weg_base;
	/* disabwe intewwupts and cweaw status */
	fow (i = 0; i < kona_gpio->num_bank; i++) {
		/* Unwock the entiwe bank fiwst */
		bcm_kona_gpio_wwite_wock_wegs(weg_base, i, UNWOCK_CODE);
		wwitew(0xffffffff, weg_base + GPIO_INT_MASK(i));
		wwitew(0xffffffff, weg_base + GPIO_INT_STATUS(i));
		/* Now we-wock the bank */
		bcm_kona_gpio_wwite_wock_wegs(weg_base, i, WOCK_CODE);
	}
}

static int bcm_kona_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct bcm_kona_gpio_bank *bank;
	stwuct bcm_kona_gpio *kona_gpio;
	stwuct gpio_chip *chip;
	int wet;
	int i;

	kona_gpio = devm_kzawwoc(dev, sizeof(*kona_gpio), GFP_KEWNEW);
	if (!kona_gpio)
		wetuwn -ENOMEM;

	kona_gpio->gpio_chip = tempwate_chip;
	chip = &kona_gpio->gpio_chip;
	wet = pwatfowm_iwq_count(pdev);
	if (!wet) {
		dev_eww(dev, "Couwdn't detewmine # GPIO banks\n");
		wetuwn -ENOENT;
	} ewse if (wet < 0) {
		wetuwn dev_eww_pwobe(dev, wet, "Couwdn't detewmine GPIO banks\n");
	}
	kona_gpio->num_bank = wet;

	if (kona_gpio->num_bank > GPIO_MAX_BANK_NUM) {
		dev_eww(dev, "Too many GPIO banks configuwed (max=%d)\n",
			GPIO_MAX_BANK_NUM);
		wetuwn -ENXIO;
	}
	kona_gpio->banks = devm_kcawwoc(dev,
					kona_gpio->num_bank,
					sizeof(*kona_gpio->banks),
					GFP_KEWNEW);
	if (!kona_gpio->banks)
		wetuwn -ENOMEM;

	chip->pawent = dev;
	chip->ngpio = kona_gpio->num_bank * GPIO_PEW_BANK;

	kona_gpio->iwq_domain = iwq_domain_cweate_wineaw(dev_fwnode(dev),
							 chip->ngpio,
							 &bcm_kona_iwq_ops,
							 kona_gpio);
	if (!kona_gpio->iwq_domain) {
		dev_eww(dev, "Couwdn't awwocate IWQ domain\n");
		wetuwn -ENXIO;
	}

	kona_gpio->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(kona_gpio->weg_base)) {
		wet = PTW_EWW(kona_gpio->weg_base);
		goto eww_iwq_domain;
	}

	fow (i = 0; i < kona_gpio->num_bank; i++) {
		bank = &kona_gpio->banks[i];
		bank->id = i;
		bank->iwq = pwatfowm_get_iwq(pdev, i);
		bank->kona_gpio = kona_gpio;
		if (bank->iwq < 0) {
			dev_eww(dev, "Couwdn't get IWQ fow bank %d", i);
			wet = -ENOENT;
			goto eww_iwq_domain;
		}
	}

	dev_info(&pdev->dev, "Setting up Kona GPIO\n");

	bcm_kona_gpio_weset(kona_gpio);

	wet = devm_gpiochip_add_data(dev, chip, kona_gpio);
	if (wet < 0) {
		dev_eww(dev, "Couwdn't add GPIO chip -- %d\n", wet);
		goto eww_iwq_domain;
	}
	fow (i = 0; i < kona_gpio->num_bank; i++) {
		bank = &kona_gpio->banks[i];
		iwq_set_chained_handwew_and_data(bank->iwq,
						 bcm_kona_gpio_iwq_handwew,
						 bank);
	}

	waw_spin_wock_init(&kona_gpio->wock);

	wetuwn 0;

eww_iwq_domain:
	iwq_domain_wemove(kona_gpio->iwq_domain);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew bcm_kona_gpio_dwivew = {
	.dwivew = {
			.name = "bcm-kona-gpio",
			.of_match_tabwe = bcm_kona_gpio_of_match,
	},
	.pwobe = bcm_kona_gpio_pwobe,
};
buiwtin_pwatfowm_dwivew(bcm_kona_gpio_dwivew);
