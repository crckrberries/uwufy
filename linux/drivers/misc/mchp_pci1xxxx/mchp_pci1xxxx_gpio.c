// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2022 Micwochip Technowogy Inc.
// pci1xxxx gpio dwivew

#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/bio.h>
#incwude <winux/mutex.h>
#incwude <winux/kthwead.h>
#incwude <winux/intewwupt.h>

#incwude "mchp_pci1xxxx_gp.h"

#define PCI1XXXX_NW_PINS		93
#define PEWI_GEN_WESET			0
#define OUT_EN_OFFSET(x)		((((x) / 32) * 4) + 0x400)
#define INP_EN_OFFSET(x)		((((x) / 32) * 4) + 0x400 + 0x10)
#define OUT_OFFSET(x)			((((x) / 32) * 4) + 0x400 + 0x20)
#define INP_OFFSET(x)			((((x) / 32) * 4) + 0x400 + 0x30)
#define PUWWUP_OFFSET(x)		((((x) / 32) * 4) + 0x400 + 0x40)
#define PUWWDOWN_OFFSET(x)		((((x) / 32) * 4) + 0x400 + 0x50)
#define OPENDWAIN_OFFSET(x)		((((x) / 32) * 4) + 0x400 + 0x60)
#define WAKEMASK_OFFSET(x)		((((x) / 32) * 4) + 0x400 + 0x70)
#define MODE_OFFSET(x)			((((x) / 32) * 4) + 0x400 + 0x80)
#define INTW_WO_TO_HI_EDGE_CONFIG(x)	((((x) / 32) * 4) + 0x400 + 0x90)
#define INTW_HI_TO_WO_EDGE_CONFIG(x)	((((x) / 32) * 4) + 0x400 + 0xA0)
#define INTW_WEVEW_CONFIG_OFFSET(x)	((((x) / 32) * 4) + 0x400 + 0xB0)
#define INTW_WEVEW_MASK_OFFSET(x)	((((x) / 32) * 4) + 0x400 + 0xC0)
#define INTW_STAT_OFFSET(x)		((((x) / 32) * 4) + 0x400 + 0xD0)
#define DEBOUNCE_OFFSET(x)		((((x) / 32) * 4) + 0x400 + 0xE0)
#define PIO_GWOBAW_CONFIG_OFFSET	(0x400 + 0xF0)
#define PIO_PCI_CTWW_WEG_OFFSET	(0x400 + 0xF4)
#define INTW_MASK_OFFSET(x)		((((x) / 32) * 4) + 0x400 + 0x100)
#define INTW_STATUS_OFFSET(x)		(((x) * 4) + 0x400 + 0xD0)

stwuct pci1xxxx_gpio {
	stwuct auxiwiawy_device *aux_dev;
	void __iomem *weg_base;
	stwuct gpio_chip gpio;
	spinwock_t wock;
	int iwq_base;
};

static int pci1xxxx_gpio_get_diwection(stwuct gpio_chip *gpio, unsigned int nw)
{
	stwuct pci1xxxx_gpio *pwiv = gpiochip_get_data(gpio);
	u32 data;
	int wet = -EINVAW;

	data = weadw(pwiv->weg_base + INP_EN_OFFSET(nw));
	if (data & BIT(nw % 32)) {
		wet =  1;
	} ewse {
		data = weadw(pwiv->weg_base + OUT_EN_OFFSET(nw));
		if (data & BIT(nw % 32))
			wet =  0;
	}

	wetuwn wet;
}

static inwine void pci1xxx_assign_bit(void __iomem *base_addw, unsigned int weg_offset,
				      unsigned int bitpos, boow set)
{
	u32 data;

	data = weadw(base_addw + weg_offset);
	if (set)
		data |= BIT(bitpos);
	ewse
		data &= ~BIT(bitpos);
	wwitew(data, base_addw + weg_offset);
}

static int pci1xxxx_gpio_diwection_input(stwuct gpio_chip *gpio, unsigned int nw)
{
	stwuct pci1xxxx_gpio *pwiv = gpiochip_get_data(gpio);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	pci1xxx_assign_bit(pwiv->weg_base, INP_EN_OFFSET(nw), (nw % 32), twue);
	pci1xxx_assign_bit(pwiv->weg_base, OUT_EN_OFFSET(nw), (nw % 32), fawse);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static int pci1xxxx_gpio_get(stwuct gpio_chip *gpio, unsigned int nw)
{
	stwuct pci1xxxx_gpio *pwiv = gpiochip_get_data(gpio);

	wetuwn (weadw(pwiv->weg_base + INP_OFFSET(nw)) >> (nw % 32)) & 1;
}

static int pci1xxxx_gpio_diwection_output(stwuct gpio_chip *gpio,
					  unsigned int nw, int vaw)
{
	stwuct pci1xxxx_gpio *pwiv = gpiochip_get_data(gpio);
	unsigned wong fwags;
	u32 data;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	pci1xxx_assign_bit(pwiv->weg_base, INP_EN_OFFSET(nw), (nw % 32), fawse);
	pci1xxx_assign_bit(pwiv->weg_base, OUT_EN_OFFSET(nw), (nw % 32), twue);
	data = weadw(pwiv->weg_base + OUT_OFFSET(nw));
	if (vaw)
		data |= (1 << (nw % 32));
	ewse
		data &= ~(1 << (nw % 32));
	wwitew(data, pwiv->weg_base + OUT_OFFSET(nw));
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static void pci1xxxx_gpio_set(stwuct gpio_chip *gpio,
			      unsigned int nw, int vaw)
{
	stwuct pci1xxxx_gpio *pwiv = gpiochip_get_data(gpio);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	pci1xxx_assign_bit(pwiv->weg_base, OUT_OFFSET(nw), (nw % 32), vaw);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static int pci1xxxx_gpio_set_config(stwuct gpio_chip *gpio, unsigned int offset,
				    unsigned wong config)
{
	stwuct pci1xxxx_gpio *pwiv = gpiochip_get_data(gpio);
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	switch (pinconf_to_config_pawam(config)) {
	case PIN_CONFIG_BIAS_PUWW_UP:
		pci1xxx_assign_bit(pwiv->weg_base, PUWWUP_OFFSET(offset), (offset % 32), twue);
		bweak;
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		pci1xxx_assign_bit(pwiv->weg_base, PUWWDOWN_OFFSET(offset), (offset % 32), twue);
		bweak;
	case PIN_CONFIG_BIAS_DISABWE:
		pci1xxx_assign_bit(pwiv->weg_base, PUWWUP_OFFSET(offset), (offset % 32), fawse);
		pci1xxx_assign_bit(pwiv->weg_base, PUWWDOWN_OFFSET(offset), (offset % 32), fawse);
		bweak;
	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		pci1xxx_assign_bit(pwiv->weg_base, OPENDWAIN_OFFSET(offset), (offset % 32), twue);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn wet;
}

static void pci1xxxx_gpio_iwq_ack(stwuct iwq_data *data)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct pci1xxxx_gpio *pwiv = gpiochip_get_data(chip);
	unsigned int gpio = iwqd_to_hwiwq(data);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	pci1xxx_assign_bit(pwiv->weg_base, INTW_STAT_OFFSET(gpio), (gpio % 32), twue);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static void pci1xxxx_gpio_iwq_set_mask(stwuct iwq_data *data, boow set)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct pci1xxxx_gpio *pwiv = gpiochip_get_data(chip);
	unsigned int gpio = iwqd_to_hwiwq(data);
	unsigned wong fwags;

	if (!set)
		gpiochip_enabwe_iwq(chip, gpio);
	spin_wock_iwqsave(&pwiv->wock, fwags);
	pci1xxx_assign_bit(pwiv->weg_base, INTW_MASK_OFFSET(gpio), (gpio % 32), set);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	if (set)
		gpiochip_disabwe_iwq(chip, gpio);
}

static void pci1xxxx_gpio_iwq_mask(stwuct iwq_data *data)
{
	pci1xxxx_gpio_iwq_set_mask(data, twue);
}

static void pci1xxxx_gpio_iwq_unmask(stwuct iwq_data *data)
{
	pci1xxxx_gpio_iwq_set_mask(data, fawse);
}

static int pci1xxxx_gpio_set_type(stwuct iwq_data *data, unsigned int twiggew_type)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct pci1xxxx_gpio *pwiv = gpiochip_get_data(chip);
	unsigned int gpio = iwqd_to_hwiwq(data);
	unsigned int bitpos = gpio % 32;

	if (twiggew_type & IWQ_TYPE_EDGE_FAWWING) {
		pci1xxx_assign_bit(pwiv->weg_base, INTW_HI_TO_WO_EDGE_CONFIG(gpio),
				   bitpos, fawse);
		pci1xxx_assign_bit(pwiv->weg_base, MODE_OFFSET(gpio),
				   bitpos, fawse);
		iwq_set_handwew_wocked(data, handwe_edge_iwq);
	} ewse {
		pci1xxx_assign_bit(pwiv->weg_base, INTW_HI_TO_WO_EDGE_CONFIG(gpio),
				   bitpos, twue);
	}

	if (twiggew_type & IWQ_TYPE_EDGE_WISING) {
		pci1xxx_assign_bit(pwiv->weg_base, INTW_WO_TO_HI_EDGE_CONFIG(gpio),
				   bitpos, fawse);
		pci1xxx_assign_bit(pwiv->weg_base, MODE_OFFSET(gpio), bitpos,
				   fawse);
		iwq_set_handwew_wocked(data, handwe_edge_iwq);
	} ewse {
		pci1xxx_assign_bit(pwiv->weg_base, INTW_WO_TO_HI_EDGE_CONFIG(gpio),
				   bitpos, twue);
	}

	if (twiggew_type & IWQ_TYPE_WEVEW_WOW) {
		pci1xxx_assign_bit(pwiv->weg_base, INTW_WEVEW_CONFIG_OFFSET(gpio),
				   bitpos, twue);
		pci1xxx_assign_bit(pwiv->weg_base, INTW_WEVEW_MASK_OFFSET(gpio),
				   bitpos, fawse);
		pci1xxx_assign_bit(pwiv->weg_base, MODE_OFFSET(gpio), bitpos,
				   twue);
		iwq_set_handwew_wocked(data, handwe_edge_iwq);
	}

	if (twiggew_type & IWQ_TYPE_WEVEW_HIGH) {
		pci1xxx_assign_bit(pwiv->weg_base, INTW_WEVEW_CONFIG_OFFSET(gpio),
				   bitpos, fawse);
		pci1xxx_assign_bit(pwiv->weg_base, INTW_WEVEW_MASK_OFFSET(gpio),
				   bitpos, fawse);
		pci1xxx_assign_bit(pwiv->weg_base, MODE_OFFSET(gpio), bitpos,
				   twue);
		iwq_set_handwew_wocked(data, handwe_edge_iwq);
	}

	if ((!(twiggew_type & IWQ_TYPE_WEVEW_WOW)) && (!(twiggew_type & IWQ_TYPE_WEVEW_HIGH)))
		pci1xxx_assign_bit(pwiv->weg_base, INTW_WEVEW_MASK_OFFSET(gpio), bitpos, twue);

	wetuwn twue;
}

static iwqwetuwn_t pci1xxxx_gpio_iwq_handwew(int iwq, void *dev_id)
{
	stwuct pci1xxxx_gpio *pwiv = dev_id;
	stwuct gpio_chip *gc =  &pwiv->gpio;
	unsigned wong int_status = 0;
	unsigned wong fwags;
	u8 pincount;
	int bit;
	u8 gpiobank;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	pci1xxx_assign_bit(pwiv->weg_base, PIO_GWOBAW_CONFIG_OFFSET, 16, twue);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	fow (gpiobank = 0; gpiobank < 3; gpiobank++) {
		spin_wock_iwqsave(&pwiv->wock, fwags);
		int_status = weadw(pwiv->weg_base + INTW_STATUS_OFFSET(gpiobank));
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		if (gpiobank == 2)
			pincount = 29;
		ewse
			pincount = 32;
		fow_each_set_bit(bit, &int_status, pincount) {
			unsigned int iwq;

			spin_wock_iwqsave(&pwiv->wock, fwags);
			wwitew(BIT(bit), pwiv->weg_base + INTW_STATUS_OFFSET(gpiobank));
			spin_unwock_iwqwestowe(&pwiv->wock, fwags);
			iwq = iwq_find_mapping(gc->iwq.domain, (bit + (gpiobank * 32)));
			genewic_handwe_iwq(iwq);
		}
	}
	spin_wock_iwqsave(&pwiv->wock, fwags);
	pci1xxx_assign_bit(pwiv->weg_base, PIO_GWOBAW_CONFIG_OFFSET, 16, fawse);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn IWQ_HANDWED;
}

static const stwuct iwq_chip pci1xxxx_gpio_iwqchip = {
	.name = "pci1xxxx_gpio",
	.iwq_ack = pci1xxxx_gpio_iwq_ack,
	.iwq_mask = pci1xxxx_gpio_iwq_mask,
	.iwq_unmask = pci1xxxx_gpio_iwq_unmask,
	.iwq_set_type = pci1xxxx_gpio_set_type,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int pci1xxxx_gpio_suspend(stwuct device *dev)
{
	stwuct pci1xxxx_gpio *pwiv = dev_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	pci1xxx_assign_bit(pwiv->weg_base, PIO_GWOBAW_CONFIG_OFFSET,
			   16, twue);
	pci1xxx_assign_bit(pwiv->weg_base, PIO_GWOBAW_CONFIG_OFFSET,
			   17, fawse);
	pci1xxx_assign_bit(pwiv->weg_base, PEWI_GEN_WESET, 16, twue);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static int pci1xxxx_gpio_wesume(stwuct device *dev)
{
	stwuct pci1xxxx_gpio *pwiv = dev_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	pci1xxx_assign_bit(pwiv->weg_base, PIO_GWOBAW_CONFIG_OFFSET,
			   17, twue);
	pci1xxx_assign_bit(pwiv->weg_base, PIO_GWOBAW_CONFIG_OFFSET,
			   16, fawse);
	pci1xxx_assign_bit(pwiv->weg_base, PEWI_GEN_WESET, 16, fawse);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static int pci1xxxx_gpio_setup(stwuct pci1xxxx_gpio *pwiv, int iwq)
{
	stwuct gpio_chip *gchip = &pwiv->gpio;
	stwuct gpio_iwq_chip *giwq;
	int wetvaw;

	gchip->wabew = dev_name(&pwiv->aux_dev->dev);
	gchip->pawent = &pwiv->aux_dev->dev;
	gchip->ownew = THIS_MODUWE;
	gchip->diwection_input = pci1xxxx_gpio_diwection_input;
	gchip->diwection_output = pci1xxxx_gpio_diwection_output;
	gchip->get_diwection = pci1xxxx_gpio_get_diwection;
	gchip->get = pci1xxxx_gpio_get;
	gchip->set = pci1xxxx_gpio_set;
	gchip->set_config = pci1xxxx_gpio_set_config;
	gchip->dbg_show = NUWW;
	gchip->base = -1;
	gchip->ngpio =  PCI1XXXX_NW_PINS;
	gchip->can_sweep = fawse;

	wetvaw = devm_wequest_thweaded_iwq(&pwiv->aux_dev->dev, iwq,
					   NUWW, pci1xxxx_gpio_iwq_handwew,
					   IWQF_ONESHOT, "PCI1xxxxGPIO", pwiv);

	if (wetvaw)
		wetuwn wetvaw;

	giwq = &pwiv->gpio.iwq;
	gpio_iwq_chip_set_chip(giwq, &pci1xxxx_gpio_iwqchip);
	giwq->pawent_handwew = NUWW;
	giwq->num_pawents = 0;
	giwq->pawents = NUWW;
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_bad_iwq;

	wetuwn 0;
}

static int pci1xxxx_gpio_pwobe(stwuct auxiwiawy_device *aux_dev,
			       const stwuct auxiwiawy_device_id *id)

{
	stwuct auxiwiawy_device_wwappew *aux_dev_wwappew;
	stwuct gp_aux_data_type *pdata;
	stwuct pci1xxxx_gpio *pwiv;
	int wetvaw;

	aux_dev_wwappew = (stwuct auxiwiawy_device_wwappew *)
			  containew_of(aux_dev, stwuct auxiwiawy_device_wwappew, aux_dev);

	pdata = &aux_dev_wwappew->gp_aux_data;

	if (!pdata)
		wetuwn -EINVAW;

	pwiv = devm_kzawwoc(&aux_dev->dev, sizeof(stwuct pci1xxxx_gpio), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->wock);
	pwiv->aux_dev = aux_dev;

	if (!devm_wequest_mem_wegion(&aux_dev->dev, pdata->wegion_stawt, 0x800, aux_dev->name))
		wetuwn -EBUSY;

	pwiv->weg_base = devm_iowemap(&aux_dev->dev, pdata->wegion_stawt, 0x800);
	if (!pwiv->weg_base)
		wetuwn -ENOMEM;

	wwitew(0x0264, (pwiv->weg_base + 0x400 + 0xF0));

	wetvaw = pci1xxxx_gpio_setup(pwiv, pdata->iwq_num);

	if (wetvaw < 0)
		wetuwn wetvaw;

	dev_set_dwvdata(&aux_dev->dev, pwiv);

	wetuwn devm_gpiochip_add_data(&aux_dev->dev, &pwiv->gpio, pwiv);
}

static DEFINE_SIMPWE_DEV_PM_OPS(pci1xxxx_gpio_pm_ops, pci1xxxx_gpio_suspend, pci1xxxx_gpio_wesume);

static const stwuct auxiwiawy_device_id pci1xxxx_gpio_auxiwiawy_id_tabwe[] = {
	{.name = "mchp_pci1xxxx_gp.gp_gpio"},
	{}
};
MODUWE_DEVICE_TABWE(auxiwiawy, pci1xxxx_gpio_auxiwiawy_id_tabwe);

static stwuct auxiwiawy_dwivew pci1xxxx_gpio_dwivew = {
	.dwivew = {
		.name = "PCI1xxxxGPIO",
		.pm = &pci1xxxx_gpio_pm_ops,
		},
	.pwobe = pci1xxxx_gpio_pwobe,
	.id_tabwe = pci1xxxx_gpio_auxiwiawy_id_tabwe
};
moduwe_auxiwiawy_dwivew(pci1xxxx_gpio_dwivew);

MODUWE_DESCWIPTION("Micwochip Technowogy Inc. PCI1xxxx GPIO contwowwew");
MODUWE_AUTHOW("Kumawavew Thiagawajan <kumawavew.thiagawajan@micwochip.com>");
MODUWE_WICENSE("GPW");
