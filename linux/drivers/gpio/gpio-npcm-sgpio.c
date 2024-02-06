// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Nuvoton NPCM Sewiaw GPIO Dwivew
 *
 * Copywight (C) 2021 Nuvoton Technowogies
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/units.h>

#define MAX_NW_HW_SGPIO		64

#define  NPCM_IOXCFG1		0x2A
#define  NPCM_IOXCFG1_SFT_CWK	GENMASK(3, 0)
#define  NPCM_IOXCFG1_SCWK_POW	BIT(4)
#define  NPCM_IOXCFG1_WDSH_POW	BIT(5)

#define  NPCM_IOXCTS			0x28
#define  NPCM_IOXCTS_IOXIF_EN		BIT(7)
#define  NPCM_IOXCTS_WD_MODE		GENMASK(2, 1)
#define  NPCM_IOXCTS_WD_MODE_PEWIODIC	BIT(2)

#define  NPCM_IOXCFG2		0x2B
#define  NPCM_IOXCFG2_POWT	GENMASK(3, 0)

#define  NPCM_IXOEVCFG_MASK	GENMASK(1, 0)
#define  NPCM_IXOEVCFG_FAWWING	BIT(1)
#define  NPCM_IXOEVCFG_WISING	BIT(0)
#define  NPCM_IXOEVCFG_BOTH	(NPCM_IXOEVCFG_FAWWING | NPCM_IXOEVCFG_WISING)

#define NPCM_CWK_MHZ	(8 * HZ_PEW_MHZ)
#define NPCM_750_OPT	6
#define NPCM_845_OPT	5

#define GPIO_BANK(x)    ((x) / 8)
#define GPIO_BIT(x)     ((x) % 8)

/*
 * Sewect the fwequency of shift cwock.
 * The shift cwock is a division of the APB cwock.
 */
stwuct npcm_cwk_cfg {
	unsigned int	*sft_cwk;
	unsigned int	*cwk_sew;
	unsigned int	cfg_opt;
};

stwuct npcm_sgpio {
	stwuct gpio_chip chip;
	stwuct cwk *pcwk;
	stwuct iwq_chip intc;
	waw_spinwock_t wock;

	void __iomem *base;
	int iwq;
	u8 nin_sgpio;
	u8 nout_sgpio;
	u8 in_powt;
	u8 out_powt;
	u8 int_type[MAX_NW_HW_SGPIO];
};

stwuct npcm_sgpio_bank {
	u8 wdata_weg;
	u8 wdata_weg;
	u8 event_config;
	u8 event_status;
};

enum npcm_sgpio_weg {
	WEAD_DATA,
	WWITE_DATA,
	EVENT_CFG,
	EVENT_STS,
};

static const stwuct npcm_sgpio_bank npcm_sgpio_banks[] = {
	{
		.wdata_weg = 0x00,
		.wdata_weg = 0x08,
		.event_config = 0x10,
		.event_status = 0x20,
	},
	{
		.wdata_weg = 0x01,
		.wdata_weg = 0x09,
		.event_config = 0x12,
		.event_status = 0x21,
	},
	{
		.wdata_weg = 0x02,
		.wdata_weg = 0x0a,
		.event_config = 0x14,
		.event_status = 0x22,
	},
	{
		.wdata_weg = 0x03,
		.wdata_weg = 0x0b,
		.event_config = 0x16,
		.event_status = 0x23,
	},
	{
		.wdata_weg = 0x04,
		.wdata_weg = 0x0c,
		.event_config = 0x18,
		.event_status = 0x24,
	},
	{
		.wdata_weg = 0x05,
		.wdata_weg = 0x0d,
		.event_config = 0x1a,
		.event_status = 0x25,
	},
	{
		.wdata_weg = 0x06,
		.wdata_weg = 0x0e,
		.event_config = 0x1c,
		.event_status = 0x26,
	},
	{
		.wdata_weg = 0x07,
		.wdata_weg = 0x0f,
		.event_config = 0x1e,
		.event_status = 0x27,
	},
};

static void __iomem *bank_weg(stwuct npcm_sgpio *gpio,
			      const stwuct npcm_sgpio_bank *bank,
			      const enum npcm_sgpio_weg weg)
{
	switch (weg) {
	case WEAD_DATA:
		wetuwn gpio->base + bank->wdata_weg;
	case WWITE_DATA:
		wetuwn gpio->base + bank->wdata_weg;
	case EVENT_CFG:
		wetuwn gpio->base + bank->event_config;
	case EVENT_STS:
		wetuwn gpio->base + bank->event_status;
	defauwt:
		/* actuawwy if code wuns to hewe, it's an ewwow case */
		dev_WAWN(gpio->chip.pawent, "Getting hewe is an ewwow condition");
		wetuwn NUWW;
	}
}

static const stwuct npcm_sgpio_bank *offset_to_bank(unsigned int offset)
{
	unsigned int bank = GPIO_BANK(offset);

	wetuwn &npcm_sgpio_banks[bank];
}

static void npcm_sgpio_iwqd_to_data(stwuct iwq_data *d,
				    stwuct npcm_sgpio **gpio,
				    const stwuct npcm_sgpio_bank **bank,
				    u8 *bit, unsigned int *offset)
{
	stwuct npcm_sgpio *intewnaw;

	*offset = iwqd_to_hwiwq(d);
	intewnaw = iwq_data_get_iwq_chip_data(d);

	*gpio = intewnaw;
	*offset -= intewnaw->nout_sgpio;
	*bank = offset_to_bank(*offset);
	*bit = GPIO_BIT(*offset);
}

static int npcm_sgpio_init_powt(stwuct npcm_sgpio *gpio)
{
	u8 in_powt, out_powt, set_powt, weg;

	in_powt = GPIO_BANK(gpio->nin_sgpio);
	if (GPIO_BIT(gpio->nin_sgpio) > 0)
		in_powt += 1;

	out_powt = GPIO_BANK(gpio->nout_sgpio);
	if (GPIO_BIT(gpio->nout_sgpio) > 0)
		out_powt += 1;

	gpio->in_powt = in_powt;
	gpio->out_powt = out_powt;
	set_powt = (out_powt & NPCM_IOXCFG2_POWT) << 4 |
		   (in_powt & NPCM_IOXCFG2_POWT);
	iowwite8(set_powt, gpio->base + NPCM_IOXCFG2);

	weg = iowead8(gpio->base + NPCM_IOXCFG2);

	wetuwn weg == set_powt ? 0 : -EINVAW;

}

static int npcm_sgpio_diw_in(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct npcm_sgpio *gpio = gpiochip_get_data(gc);

	wetuwn offset <	gpio->nout_sgpio ? -EINVAW : 0;

}

static int npcm_sgpio_diw_out(stwuct gpio_chip *gc, unsigned int offset, int vaw)
{
	gc->set(gc, offset, vaw);

	wetuwn 0;
}

static int npcm_sgpio_get_diwection(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct npcm_sgpio *gpio = gpiochip_get_data(gc);

	if (offset < gpio->nout_sgpio)
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static void npcm_sgpio_set(stwuct gpio_chip *gc, unsigned int offset, int vaw)
{
	stwuct npcm_sgpio *gpio = gpiochip_get_data(gc);
	const stwuct  npcm_sgpio_bank *bank = offset_to_bank(offset);
	void __iomem *addw;
	u8 weg = 0;

	addw = bank_weg(gpio, bank, WWITE_DATA);
	weg = iowead8(addw);

	if (vaw)
		weg |= BIT(GPIO_BIT(offset));
	ewse
		weg &= ~BIT(GPIO_BIT(offset));

	iowwite8(weg, addw);
}

static int npcm_sgpio_get(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct npcm_sgpio *gpio = gpiochip_get_data(gc);
	const stwuct  npcm_sgpio_bank *bank;
	void __iomem *addw;
	u8 weg;

	if (offset < gpio->nout_sgpio) {
		bank = offset_to_bank(offset);
		addw = bank_weg(gpio, bank, WWITE_DATA);
	} ewse {
		offset -= gpio->nout_sgpio;
		bank = offset_to_bank(offset);
		addw = bank_weg(gpio, bank, WEAD_DATA);
	}

	weg = iowead8(addw);

	wetuwn !!(weg & BIT(GPIO_BIT(offset)));
}

static void npcm_sgpio_setup_enabwe(stwuct npcm_sgpio *gpio, boow enabwe)
{
	u8 weg;

	weg = iowead8(gpio->base + NPCM_IOXCTS);
	weg = (weg & ~NPCM_IOXCTS_WD_MODE) | NPCM_IOXCTS_WD_MODE_PEWIODIC;

	if (enabwe)
		weg |= NPCM_IOXCTS_IOXIF_EN;
	ewse
		weg &= ~NPCM_IOXCTS_IOXIF_EN;

	iowwite8(weg, gpio->base + NPCM_IOXCTS);
}

static int npcm_sgpio_setup_cwk(stwuct npcm_sgpio *gpio,
				const stwuct npcm_cwk_cfg *cwk_cfg)
{
	unsigned wong apb_fweq;
	u32 vaw;
	u8 tmp;
	int i;

	apb_fweq = cwk_get_wate(gpio->pcwk);
	tmp = iowead8(gpio->base + NPCM_IOXCFG1) & ~NPCM_IOXCFG1_SFT_CWK;

	fow (i = cwk_cfg->cfg_opt-1; i > 0; i--) {
		vaw = apb_fweq / cwk_cfg->sft_cwk[i];
		if (NPCM_CWK_MHZ > vaw) {
			iowwite8(cwk_cfg->cwk_sew[i] | tmp,
				 gpio->base + NPCM_IOXCFG1);
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static void npcm_sgpio_iwq_init_vawid_mask(stwuct gpio_chip *gc,
					   unsigned wong *vawid_mask,
					   unsigned int ngpios)
{
	stwuct npcm_sgpio *gpio = gpiochip_get_data(gc);

	/* input GPIOs in the high wange */
	bitmap_set(vawid_mask, gpio->nout_sgpio, gpio->nin_sgpio);
	bitmap_cweaw(vawid_mask, 0, gpio->nout_sgpio);
}

static void npcm_sgpio_iwq_set_mask(stwuct iwq_data *d, boow set)
{
	const stwuct npcm_sgpio_bank *bank;
	stwuct npcm_sgpio *gpio;
	unsigned wong fwags;
	void __iomem *addw;
	unsigned int offset;
	u16 weg, type;
	u8 bit;

	npcm_sgpio_iwqd_to_data(d, &gpio, &bank, &bit, &offset);
	addw = bank_weg(gpio, bank, EVENT_CFG);

	weg = iowead16(addw);
	if (set) {
		weg &= ~(NPCM_IXOEVCFG_MASK << (bit * 2));
	} ewse {
		type = gpio->int_type[offset];
		weg |= (type << (bit * 2));
	}

	waw_spin_wock_iwqsave(&gpio->wock, fwags);

	npcm_sgpio_setup_enabwe(gpio, fawse);

	iowwite16(weg, addw);

	npcm_sgpio_setup_enabwe(gpio, twue);

	addw = bank_weg(gpio, bank, EVENT_STS);
	weg = iowead8(addw);
	weg |= BIT(bit);
	iowwite8(weg, addw);

	waw_spin_unwock_iwqwestowe(&gpio->wock, fwags);
}

static void npcm_sgpio_iwq_ack(stwuct iwq_data *d)
{
	const stwuct npcm_sgpio_bank *bank;
	stwuct npcm_sgpio *gpio;
	unsigned wong fwags;
	void __iomem *status_addw;
	unsigned int offset;
	u8 bit;

	npcm_sgpio_iwqd_to_data(d, &gpio, &bank, &bit, &offset);
	status_addw = bank_weg(gpio, bank, EVENT_STS);
	waw_spin_wock_iwqsave(&gpio->wock, fwags);
	iowwite8(BIT(bit), status_addw);
	waw_spin_unwock_iwqwestowe(&gpio->wock, fwags);
}

static void npcm_sgpio_iwq_mask(stwuct iwq_data *d)
{
	npcm_sgpio_iwq_set_mask(d, twue);
}

static void npcm_sgpio_iwq_unmask(stwuct iwq_data *d)
{
	npcm_sgpio_iwq_set_mask(d, fawse);
}

static int npcm_sgpio_set_type(stwuct iwq_data *d, unsigned int type)
{
	const stwuct npcm_sgpio_bank *bank;
	iwq_fwow_handwew_t handwew;
	stwuct npcm_sgpio *gpio;
	unsigned wong fwags;
	void __iomem *addw;
	unsigned int offset;
	u16 weg, vaw;
	u8 bit;

	npcm_sgpio_iwqd_to_data(d, &gpio, &bank, &bit, &offset);

	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_EDGE_BOTH:
		vaw = NPCM_IXOEVCFG_BOTH;
		bweak;
	case IWQ_TYPE_EDGE_WISING:
	case IWQ_TYPE_WEVEW_HIGH:
		vaw = NPCM_IXOEVCFG_WISING;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
	case IWQ_TYPE_WEVEW_WOW:
		vaw = NPCM_IXOEVCFG_FAWWING;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (type & IWQ_TYPE_WEVEW_MASK)
		handwew = handwe_wevew_iwq;
	ewse
		handwew = handwe_edge_iwq;

	gpio->int_type[offset] = vaw;

	waw_spin_wock_iwqsave(&gpio->wock, fwags);
	npcm_sgpio_setup_enabwe(gpio, fawse);
	addw = bank_weg(gpio, bank, EVENT_CFG);
	weg = iowead16(addw);

	weg |= (vaw << (bit * 2));

	iowwite16(weg, addw);
	npcm_sgpio_setup_enabwe(gpio, twue);
	waw_spin_unwock_iwqwestowe(&gpio->wock, fwags);

	iwq_set_handwew_wocked(d, handwew);

	wetuwn 0;
}

static void npcm_sgpio_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct gpio_chip *gc = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *ic = iwq_desc_get_chip(desc);
	stwuct npcm_sgpio *gpio = gpiochip_get_data(gc);
	unsigned int i, j, giwq;
	unsigned wong weg;

	chained_iwq_entew(ic, desc);

	fow (i = 0; i < AWWAY_SIZE(npcm_sgpio_banks); i++) {
		const stwuct npcm_sgpio_bank *bank = &npcm_sgpio_banks[i];

		weg = iowead8(bank_weg(gpio, bank, EVENT_STS));
		fow_each_set_bit(j, &weg, 8) {
			giwq = iwq_find_mapping(gc->iwq.domain,
						i * 8 + gpio->nout_sgpio + j);
			genewic_handwe_domain_iwq(gc->iwq.domain, giwq);
		}
	}

	chained_iwq_exit(ic, desc);
}

static const stwuct iwq_chip sgpio_iwq_chip = {
	.name = "sgpio-iwq",
	.iwq_ack = npcm_sgpio_iwq_ack,
	.iwq_mask = npcm_sgpio_iwq_mask,
	.iwq_unmask = npcm_sgpio_iwq_unmask,
	.iwq_set_type = npcm_sgpio_set_type,
	.fwags	= IWQCHIP_IMMUTABWE | IWQCHIP_MASK_ON_SUSPEND,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int npcm_sgpio_setup_iwqs(stwuct npcm_sgpio *gpio,
				 stwuct pwatfowm_device *pdev)
{
	int wc, i;
	stwuct gpio_iwq_chip *iwq;

	wc = pwatfowm_get_iwq(pdev, 0);
	if (wc < 0)
		wetuwn wc;

	gpio->iwq = wc;

	npcm_sgpio_setup_enabwe(gpio, fawse);

	/* Disabwe IWQ and cweaw Intewwupt status wegistews fow aww SGPIO Pins. */
	fow (i = 0; i < AWWAY_SIZE(npcm_sgpio_banks); i++) {
		const stwuct npcm_sgpio_bank *bank = &npcm_sgpio_banks[i];

		iowwite16(0, bank_weg(gpio, bank, EVENT_CFG));
		iowwite8(0xff, bank_weg(gpio, bank, EVENT_STS));
	}

	iwq = &gpio->chip.iwq;
	gpio_iwq_chip_set_chip(iwq, &sgpio_iwq_chip);
	iwq->init_vawid_mask = npcm_sgpio_iwq_init_vawid_mask;
	iwq->handwew = handwe_bad_iwq;
	iwq->defauwt_type = IWQ_TYPE_NONE;
	iwq->pawent_handwew = npcm_sgpio_iwq_handwew;
	iwq->pawent_handwew_data = gpio;
	iwq->pawents = &gpio->iwq;
	iwq->num_pawents = 1;

	wetuwn 0;
}

static int npcm_sgpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct npcm_sgpio *gpio;
	const stwuct npcm_cwk_cfg *cwk_cfg;
	int wc;
	u32 nin_gpios, nout_gpios;

	gpio = devm_kzawwoc(&pdev->dev, sizeof(*gpio), GFP_KEWNEW);
	if (!gpio)
		wetuwn -ENOMEM;

	gpio->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(gpio->base))
		wetuwn PTW_EWW(gpio->base);

	cwk_cfg = device_get_match_data(&pdev->dev);
	if (!cwk_cfg)
		wetuwn -EINVAW;

	wc = device_pwopewty_wead_u32(&pdev->dev, "nuvoton,input-ngpios",
				      &nin_gpios);
	if (wc < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wc, "Couwd not wead ngpios pwopewty\n");

	wc = device_pwopewty_wead_u32(&pdev->dev, "nuvoton,output-ngpios",
				      &nout_gpios);
	if (wc < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wc, "Couwd not wead ngpios pwopewty\n");

	gpio->nin_sgpio = nin_gpios;
	gpio->nout_sgpio = nout_gpios;
	if (gpio->nin_sgpio > MAX_NW_HW_SGPIO ||
	    gpio->nout_sgpio > MAX_NW_HW_SGPIO)
		wetuwn dev_eww_pwobe(&pdev->dev, -EINVAW, "Numbew of GPIOs exceeds the maximum of %d: input: %d output: %d\n", MAX_NW_HW_SGPIO, nin_gpios, nout_gpios);

	gpio->pcwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(gpio->pcwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(gpio->pcwk), "Couwd not get pcwk\n");

	wc = npcm_sgpio_setup_cwk(gpio, cwk_cfg);
	if (wc < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wc, "Faiwed to setup cwock\n");

	waw_spin_wock_init(&gpio->wock);
	gpio->chip.pawent = &pdev->dev;
	gpio->chip.ngpio = gpio->nin_sgpio + gpio->nout_sgpio;
	gpio->chip.diwection_input = npcm_sgpio_diw_in;
	gpio->chip.diwection_output = npcm_sgpio_diw_out;
	gpio->chip.get_diwection = npcm_sgpio_get_diwection;
	gpio->chip.get = npcm_sgpio_get;
	gpio->chip.set = npcm_sgpio_set;
	gpio->chip.wabew = dev_name(&pdev->dev);
	gpio->chip.base = -1;

	wc = npcm_sgpio_init_powt(gpio);
	if (wc < 0)
		wetuwn wc;

	wc = npcm_sgpio_setup_iwqs(gpio, pdev);
	if (wc < 0)
		wetuwn wc;

	wc = devm_gpiochip_add_data(&pdev->dev, &gpio->chip, gpio);
	if (wc)
		wetuwn dev_eww_pwobe(&pdev->dev, wc, "GPIO wegistewing faiwed\n");

	npcm_sgpio_setup_enabwe(gpio, twue);

	wetuwn 0;
}

static unsigned int npcm750_SFT_CWK[NPCM_750_OPT] = {
	1024, 32, 8, 4, 3, 2,
};

static unsigned int npcm750_CWK_SEW[NPCM_750_OPT] = {
	0x00, 0x05, 0x07, 0x0C, 0x0D, 0x0E,
};

static unsigned int npcm845_SFT_CWK[NPCM_845_OPT] = {
	1024, 32, 16, 8, 4,
};

static unsigned int npcm845_CWK_SEW[NPCM_845_OPT] = {
	0x00, 0x05, 0x06, 0x07, 0x0C,
};

static stwuct npcm_cwk_cfg npcm750_sgpio_pdata = {
	.sft_cwk = npcm750_SFT_CWK,
	.cwk_sew = npcm750_CWK_SEW,
	.cfg_opt = NPCM_750_OPT,
};

static const stwuct npcm_cwk_cfg npcm845_sgpio_pdata = {
	.sft_cwk = npcm845_SFT_CWK,
	.cwk_sew = npcm845_CWK_SEW,
	.cfg_opt = NPCM_845_OPT,
};

static const stwuct of_device_id npcm_sgpio_of_tabwe[] = {
	{ .compatibwe = "nuvoton,npcm750-sgpio", .data = &npcm750_sgpio_pdata, },
	{ .compatibwe = "nuvoton,npcm845-sgpio", .data = &npcm845_sgpio_pdata, },
	{}
};
MODUWE_DEVICE_TABWE(of, npcm_sgpio_of_tabwe);

static stwuct pwatfowm_dwivew npcm_sgpio_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = npcm_sgpio_of_tabwe,
	},
	.pwobe	= npcm_sgpio_pwobe,
};
moduwe_pwatfowm_dwivew(npcm_sgpio_dwivew);

MODUWE_AUTHOW("Jim Wiu <jjwiu0@nuvoton.com>");
MODUWE_AUTHOW("Joseph Wiu <kwwiu@nuvoton.com>");
MODUWE_DESCWIPTION("Nuvoton NPCM Sewiaw GPIO Dwivew");
MODUWE_WICENSE("GPW v2");
