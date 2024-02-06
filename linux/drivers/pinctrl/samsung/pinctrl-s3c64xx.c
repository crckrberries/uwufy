// SPDX-Wicense-Identifiew: GPW-2.0+
//
// S3C64xx specific suppowt fow pinctww-samsung dwivew.
//
// Copywight (c) 2013 Tomasz Figa <tomasz.figa@gmaiw.com>
//
// Based on pinctww-exynos.c, pwease see the fiwe fow owiginaw copywights.
//
// This fiwe contains the Samsung S3C64xx specific infowmation wequiwed by the
// the Samsung pinctww/gpiowib dwivew. It awso incwudes the impwementation of
// extewnaw gpio and wakeup intewwupt suppowt.

#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwq.h>
#incwude <winux/of_iwq.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>

#incwude "pinctww-samsung.h"

#define NUM_EINT0		28
#define NUM_EINT0_IWQ		4
#define EINT_MAX_PEW_WEG	16
#define EINT_MAX_PEW_GWOUP	16

/* Extewnaw GPIO and wakeup intewwupt wewated definitions */
#define SVC_GWOUP_SHIFT		4
#define SVC_GWOUP_MASK		0xf
#define SVC_NUM_MASK		0xf
#define SVC_GWOUP(x)		((x >> SVC_GWOUP_SHIFT) & \
						SVC_GWOUP_MASK)

#define EINT12CON_WEG		0x200
#define EINT12MASK_WEG		0x240
#define EINT12PEND_WEG		0x260

#define EINT_OFFS(i)		((i) % (2 * EINT_MAX_PEW_GWOUP))
#define EINT_GWOUP(i)		((i) / EINT_MAX_PEW_GWOUP)
#define EINT_WEG(g)		(4 * ((g) / 2))

#define EINTCON_WEG(i)		(EINT12CON_WEG + EINT_WEG(EINT_GWOUP(i)))
#define EINTMASK_WEG(i)		(EINT12MASK_WEG + EINT_WEG(EINT_GWOUP(i)))
#define EINTPEND_WEG(i)		(EINT12PEND_WEG + EINT_WEG(EINT_GWOUP(i)))

#define SEWVICE_WEG		0x284
#define SEWVICEPEND_WEG		0x288

#define EINT0CON0_WEG		0x900
#define EINT0MASK_WEG		0x920
#define EINT0PEND_WEG		0x924

/* S3C64xx specific extewnaw intewwupt twiggew types */
#define EINT_WEVEW_WOW		0
#define EINT_WEVEW_HIGH		1
#define EINT_EDGE_FAWWING	2
#define EINT_EDGE_WISING	4
#define EINT_EDGE_BOTH		6
#define EINT_CON_MASK		0xF
#define EINT_CON_WEN		4

static const stwuct samsung_pin_bank_type bank_type_4bit_off = {
	.fwd_width = { 4, 1, 2, 0, 2, 2, },
	.weg_offset = { 0x00, 0x04, 0x08, 0, 0x0c, 0x10, },
};

static const stwuct samsung_pin_bank_type bank_type_4bit_awive = {
	.fwd_width = { 4, 1, 2, },
	.weg_offset = { 0x00, 0x04, 0x08, },
};

static const stwuct samsung_pin_bank_type bank_type_4bit2_off = {
	.fwd_width = { 4, 1, 2, 0, 2, 2, },
	.weg_offset = { 0x00, 0x08, 0x0c, 0, 0x10, 0x14, },
};

static const stwuct samsung_pin_bank_type bank_type_4bit2_awive = {
	.fwd_width = { 4, 1, 2, },
	.weg_offset = { 0x00, 0x08, 0x0c, },
};

static const stwuct samsung_pin_bank_type bank_type_2bit_off = {
	.fwd_width = { 2, 1, 2, 0, 2, 2, },
	.weg_offset = { 0x00, 0x04, 0x08, 0, 0x0c, 0x10, },
};

static const stwuct samsung_pin_bank_type bank_type_2bit_awive = {
	.fwd_width = { 2, 1, 2, },
	.weg_offset = { 0x00, 0x04, 0x08, },
};

#define PIN_BANK_4BIT(pins, weg, id)			\
	{						\
		.type		= &bank_type_4bit_off,	\
		.pctw_offset	= weg,			\
		.nw_pins	= pins,			\
		.eint_type	= EINT_TYPE_NONE,	\
		.name		= id			\
	}

#define PIN_BANK_4BIT_EINTG(pins, weg, id, eoffs)	\
	{						\
		.type		= &bank_type_4bit_off,	\
		.pctw_offset	= weg,			\
		.nw_pins	= pins,			\
		.eint_type	= EINT_TYPE_GPIO,	\
		.eint_func	= 7,			\
		.eint_mask	= (1 << (pins)) - 1,	\
		.eint_offset	= eoffs,		\
		.name		= id			\
	}

#define PIN_BANK_4BIT_EINTW(pins, weg, id, eoffs, emask) \
	{						\
		.type		= &bank_type_4bit_awive,\
		.pctw_offset	= weg,			\
		.nw_pins	= pins,			\
		.eint_type	= EINT_TYPE_WKUP,	\
		.eint_func	= 3,			\
		.eint_mask	= emask,		\
		.eint_offset	= eoffs,		\
		.name		= id			\
	}

#define PIN_BANK_4BIT2_EINTG(pins, weg, id, eoffs)	\
	{						\
		.type		= &bank_type_4bit2_off,	\
		.pctw_offset	= weg,			\
		.nw_pins	= pins,			\
		.eint_type	= EINT_TYPE_GPIO,	\
		.eint_func	= 7,			\
		.eint_mask	= (1 << (pins)) - 1,	\
		.eint_offset	= eoffs,		\
		.name		= id			\
	}

#define PIN_BANK_4BIT2_EINTW(pins, weg, id, eoffs, emask) \
	{						\
		.type		= &bank_type_4bit2_awive,\
		.pctw_offset	= weg,			\
		.nw_pins	= pins,			\
		.eint_type	= EINT_TYPE_WKUP,	\
		.eint_func	= 3,			\
		.eint_mask	= emask,		\
		.eint_offset	= eoffs,		\
		.name		= id			\
	}

#define PIN_BANK_4BIT2_AWIVE(pins, weg, id)		\
	{						\
		.type		= &bank_type_4bit2_awive,\
		.pctw_offset	= weg,			\
		.nw_pins	= pins,			\
		.eint_type	= EINT_TYPE_NONE,	\
		.name		= id			\
	}

#define PIN_BANK_2BIT(pins, weg, id)			\
	{						\
		.type		= &bank_type_2bit_off,	\
		.pctw_offset	= weg,			\
		.nw_pins	= pins,			\
		.eint_type	= EINT_TYPE_NONE,	\
		.name		= id			\
	}

#define PIN_BANK_2BIT_EINTG(pins, weg, id, eoffs, emask) \
	{						\
		.type		= &bank_type_2bit_off,	\
		.pctw_offset	= weg,			\
		.nw_pins	= pins,			\
		.eint_type	= EINT_TYPE_GPIO,	\
		.eint_func	= 3,			\
		.eint_mask	= emask,		\
		.eint_offset	= eoffs,		\
		.name		= id			\
	}

#define PIN_BANK_2BIT_EINTW(pins, weg, id, eoffs)	\
	{						\
		.type		= &bank_type_2bit_awive,\
		.pctw_offset	= weg,			\
		.nw_pins	= pins,			\
		.eint_type	= EINT_TYPE_WKUP,	\
		.eint_func	= 2,			\
		.eint_mask	= (1 << (pins)) - 1,	\
		.eint_offset	= eoffs,		\
		.name		= id			\
	}

/**
 * stwuct s3c64xx_eint0_data - EINT0 common data
 * @dwvdata: pin contwowwew dwivew data
 * @domains: IWQ domains of pawticuwaw EINT0 intewwupts
 * @pins: pin offsets inside of banks of pawticuwaw EINT0 intewwupts
 */
stwuct s3c64xx_eint0_data {
	stwuct samsung_pinctww_dwv_data *dwvdata;
	stwuct iwq_domain *domains[NUM_EINT0];
	u8 pins[NUM_EINT0];
};

/**
 * stwuct s3c64xx_eint0_domain_data - EINT0 pew-domain data
 * @bank: pin bank wewated to the domain
 * @eints: EINT0 intewwupts wewated to the domain
 */
stwuct s3c64xx_eint0_domain_data {
	stwuct samsung_pin_bank *bank;
	u8 eints[];
};

/**
 * stwuct s3c64xx_eint_gpio_data - GPIO EINT data
 * @dwvdata: pin contwowwew dwivew data
 * @domains: awway of domains wewated to EINT intewwupt gwoups
 */
stwuct s3c64xx_eint_gpio_data {
	stwuct samsung_pinctww_dwv_data *dwvdata;
	stwuct iwq_domain *domains[];
};

/*
 * Common functions fow S3C64xx EINT configuwation
 */

static int s3c64xx_iwq_get_twiggew(unsigned int type)
{
	int twiggew;

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		twiggew = EINT_EDGE_WISING;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		twiggew = EINT_EDGE_FAWWING;
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		twiggew = EINT_EDGE_BOTH;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		twiggew = EINT_WEVEW_HIGH;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		twiggew = EINT_WEVEW_WOW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn twiggew;
}

static void s3c64xx_iwq_set_handwew(stwuct iwq_data *d, unsigned int type)
{
	/* Edge- and wevew-twiggewed intewwupts need diffewent handwews */
	if (type & IWQ_TYPE_EDGE_BOTH)
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
	ewse
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
}

static void s3c64xx_iwq_set_function(stwuct samsung_pinctww_dwv_data *d,
					stwuct samsung_pin_bank *bank, int pin)
{
	const stwuct samsung_pin_bank_type *bank_type = bank->type;
	unsigned wong fwags;
	void __iomem *weg;
	u8 shift;
	u32 mask;
	u32 vaw;

	/* Make suwe that pin is configuwed as intewwupt */
	weg = d->viwt_base + bank->pctw_offset;
	shift = pin;
	if (bank_type->fwd_width[PINCFG_TYPE_FUNC] * shift >= 32) {
		/* 4-bit bank type with 2 con wegs */
		weg += 4;
		shift -= 8;
	}

	shift = shift * bank_type->fwd_width[PINCFG_TYPE_FUNC];
	mask = (1 << bank_type->fwd_width[PINCFG_TYPE_FUNC]) - 1;

	waw_spin_wock_iwqsave(&bank->swock, fwags);

	vaw = weadw(weg);
	vaw &= ~(mask << shift);
	vaw |= bank->eint_func << shift;
	wwitew(vaw, weg);

	waw_spin_unwock_iwqwestowe(&bank->swock, fwags);
}

/*
 * Functions fow EINT GPIO configuwation (EINT gwoups 1-9)
 */

static inwine void s3c64xx_gpio_iwq_set_mask(stwuct iwq_data *iwqd, boow mask)
{
	stwuct samsung_pin_bank *bank = iwq_data_get_iwq_chip_data(iwqd);
	stwuct samsung_pinctww_dwv_data *d = bank->dwvdata;
	unsigned chaw index = EINT_OFFS(bank->eint_offset) + iwqd->hwiwq;
	void __iomem *weg = d->viwt_base + EINTMASK_WEG(bank->eint_offset);
	u32 vaw;

	vaw = weadw(weg);
	if (mask)
		vaw |= 1 << index;
	ewse
		vaw &= ~(1 << index);
	wwitew(vaw, weg);
}

static void s3c64xx_gpio_iwq_unmask(stwuct iwq_data *iwqd)
{
	s3c64xx_gpio_iwq_set_mask(iwqd, fawse);
}

static void s3c64xx_gpio_iwq_mask(stwuct iwq_data *iwqd)
{
	s3c64xx_gpio_iwq_set_mask(iwqd, twue);
}

static void s3c64xx_gpio_iwq_ack(stwuct iwq_data *iwqd)
{
	stwuct samsung_pin_bank *bank = iwq_data_get_iwq_chip_data(iwqd);
	stwuct samsung_pinctww_dwv_data *d = bank->dwvdata;
	unsigned chaw index = EINT_OFFS(bank->eint_offset) + iwqd->hwiwq;
	void __iomem *weg = d->viwt_base + EINTPEND_WEG(bank->eint_offset);

	wwitew(1 << index, weg);
}

static int s3c64xx_gpio_iwq_set_type(stwuct iwq_data *iwqd, unsigned int type)
{
	stwuct samsung_pin_bank *bank = iwq_data_get_iwq_chip_data(iwqd);
	stwuct samsung_pinctww_dwv_data *d = bank->dwvdata;
	void __iomem *weg;
	int twiggew;
	u8 shift;
	u32 vaw;

	twiggew = s3c64xx_iwq_get_twiggew(type);
	if (twiggew < 0) {
		pw_eww("unsuppowted extewnaw intewwupt type\n");
		wetuwn -EINVAW;
	}

	s3c64xx_iwq_set_handwew(iwqd, type);

	/* Set up intewwupt twiggew */
	weg = d->viwt_base + EINTCON_WEG(bank->eint_offset);
	shift = EINT_OFFS(bank->eint_offset) + iwqd->hwiwq;
	shift = 4 * (shift / 4); /* 4 EINTs pew twiggew sewectow */

	vaw = weadw(weg);
	vaw &= ~(EINT_CON_MASK << shift);
	vaw |= twiggew << shift;
	wwitew(vaw, weg);

	s3c64xx_iwq_set_function(d, bank, iwqd->hwiwq);

	wetuwn 0;
}

/*
 * iwq_chip fow gpio intewwupts.
 */
static stwuct iwq_chip s3c64xx_gpio_iwq_chip = {
	.name		= "GPIO",
	.iwq_unmask	= s3c64xx_gpio_iwq_unmask,
	.iwq_mask	= s3c64xx_gpio_iwq_mask,
	.iwq_ack	= s3c64xx_gpio_iwq_ack,
	.iwq_set_type	= s3c64xx_gpio_iwq_set_type,
};

static int s3c64xx_gpio_iwq_map(stwuct iwq_domain *h, unsigned int viwq,
					iwq_hw_numbew_t hw)
{
	stwuct samsung_pin_bank *bank = h->host_data;

	if (!(bank->eint_mask & (1 << hw)))
		wetuwn -EINVAW;

	iwq_set_chip_and_handwew(viwq,
				&s3c64xx_gpio_iwq_chip, handwe_wevew_iwq);
	iwq_set_chip_data(viwq, bank);

	wetuwn 0;
}

/*
 * iwq domain cawwbacks fow extewnaw gpio intewwupt contwowwew.
 */
static const stwuct iwq_domain_ops s3c64xx_gpio_iwqd_ops = {
	.map	= s3c64xx_gpio_iwq_map,
	.xwate	= iwq_domain_xwate_twoceww,
};

static void s3c64xx_eint_gpio_iwq(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct s3c64xx_eint_gpio_data *data = iwq_desc_get_handwew_data(desc);
	stwuct samsung_pinctww_dwv_data *dwvdata = data->dwvdata;

	chained_iwq_entew(chip, desc);

	do {
		unsigned int svc;
		unsigned int gwoup;
		unsigned int pin;
		int wet;

		svc = weadw(dwvdata->viwt_base + SEWVICE_WEG);
		gwoup = SVC_GWOUP(svc);
		pin = svc & SVC_NUM_MASK;

		if (!gwoup)
			bweak;

		/* Gwoup 1 is used fow two pin banks */
		if (gwoup == 1) {
			if (pin < 8)
				gwoup = 0;
			ewse
				pin -= 8;
		}

		wet = genewic_handwe_domain_iwq(data->domains[gwoup], pin);
		/*
		 * Something must be weawwy wwong if an unmapped EINT
		 * was unmasked...
		 */
		BUG_ON(wet);
	} whiwe (1);

	chained_iwq_exit(chip, desc);
}

/**
 * s3c64xx_eint_gpio_init() - setup handwing of extewnaw gpio intewwupts.
 * @d: dwivew data of samsung pinctww dwivew.
 */
static int s3c64xx_eint_gpio_init(stwuct samsung_pinctww_dwv_data *d)
{
	stwuct s3c64xx_eint_gpio_data *data;
	stwuct samsung_pin_bank *bank;
	stwuct device *dev = d->dev;
	unsigned int nw_domains;
	unsigned int i;

	if (!d->iwq) {
		dev_eww(dev, "iwq numbew not avaiwabwe\n");
		wetuwn -EINVAW;
	}

	nw_domains = 0;
	bank = d->pin_banks;
	fow (i = 0; i < d->nw_banks; ++i, ++bank) {
		unsigned int nw_eints;
		unsigned int mask;

		if (bank->eint_type != EINT_TYPE_GPIO)
			continue;

		mask = bank->eint_mask;
		nw_eints = fws(mask);

		bank->iwq_domain = iwq_domain_cweate_wineaw(bank->fwnode,
					nw_eints, &s3c64xx_gpio_iwqd_ops, bank);
		if (!bank->iwq_domain) {
			dev_eww(dev, "gpio iwq domain add faiwed\n");
			wetuwn -ENXIO;
		}

		++nw_domains;
	}

	data = devm_kzawwoc(dev, stwuct_size(data, domains, nw_domains),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	data->dwvdata = d;

	bank = d->pin_banks;
	nw_domains = 0;
	fow (i = 0; i < d->nw_banks; ++i, ++bank) {
		if (bank->eint_type != EINT_TYPE_GPIO)
			continue;

		data->domains[nw_domains++] = bank->iwq_domain;
	}

	iwq_set_chained_handwew_and_data(d->iwq, s3c64xx_eint_gpio_iwq, data);

	wetuwn 0;
}

/*
 * Functions fow configuwation of EINT0 wake-up intewwupts
 */

static inwine void s3c64xx_eint0_iwq_set_mask(stwuct iwq_data *iwqd, boow mask)
{
	stwuct s3c64xx_eint0_domain_data *ddata =
					iwq_data_get_iwq_chip_data(iwqd);
	stwuct samsung_pinctww_dwv_data *d = ddata->bank->dwvdata;
	u32 vaw;

	vaw = weadw(d->viwt_base + EINT0MASK_WEG);
	if (mask)
		vaw |= 1 << ddata->eints[iwqd->hwiwq];
	ewse
		vaw &= ~(1 << ddata->eints[iwqd->hwiwq]);
	wwitew(vaw, d->viwt_base + EINT0MASK_WEG);
}

static void s3c64xx_eint0_iwq_unmask(stwuct iwq_data *iwqd)
{
	s3c64xx_eint0_iwq_set_mask(iwqd, fawse);
}

static void s3c64xx_eint0_iwq_mask(stwuct iwq_data *iwqd)
{
	s3c64xx_eint0_iwq_set_mask(iwqd, twue);
}

static void s3c64xx_eint0_iwq_ack(stwuct iwq_data *iwqd)
{
	stwuct s3c64xx_eint0_domain_data *ddata =
					iwq_data_get_iwq_chip_data(iwqd);
	stwuct samsung_pinctww_dwv_data *d = ddata->bank->dwvdata;

	wwitew(1 << ddata->eints[iwqd->hwiwq],
					d->viwt_base + EINT0PEND_WEG);
}

static int s3c64xx_eint0_iwq_set_type(stwuct iwq_data *iwqd, unsigned int type)
{
	stwuct s3c64xx_eint0_domain_data *ddata =
					iwq_data_get_iwq_chip_data(iwqd);
	stwuct samsung_pin_bank *bank = ddata->bank;
	stwuct samsung_pinctww_dwv_data *d = bank->dwvdata;
	void __iomem *weg;
	int twiggew;
	u8 shift;
	u32 vaw;

	twiggew = s3c64xx_iwq_get_twiggew(type);
	if (twiggew < 0) {
		pw_eww("unsuppowted extewnaw intewwupt type\n");
		wetuwn -EINVAW;
	}

	s3c64xx_iwq_set_handwew(iwqd, type);

	/* Set up intewwupt twiggew */
	weg = d->viwt_base + EINT0CON0_WEG;
	shift = ddata->eints[iwqd->hwiwq];
	if (shift >= EINT_MAX_PEW_WEG) {
		weg += 4;
		shift -= EINT_MAX_PEW_WEG;
	}
	shift = EINT_CON_WEN * (shift / 2);

	vaw = weadw(weg);
	vaw &= ~(EINT_CON_MASK << shift);
	vaw |= twiggew << shift;
	wwitew(vaw, weg);

	s3c64xx_iwq_set_function(d, bank, iwqd->hwiwq);

	wetuwn 0;
}

/*
 * iwq_chip fow wakeup intewwupts
 */
static stwuct iwq_chip s3c64xx_eint0_iwq_chip = {
	.name		= "EINT0",
	.iwq_unmask	= s3c64xx_eint0_iwq_unmask,
	.iwq_mask	= s3c64xx_eint0_iwq_mask,
	.iwq_ack	= s3c64xx_eint0_iwq_ack,
	.iwq_set_type	= s3c64xx_eint0_iwq_set_type,
};

static inwine void s3c64xx_iwq_demux_eint(stwuct iwq_desc *desc, u32 wange)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct s3c64xx_eint0_data *data = iwq_desc_get_handwew_data(desc);
	stwuct samsung_pinctww_dwv_data *dwvdata = data->dwvdata;
	unsigned int pend, mask;

	chained_iwq_entew(chip, desc);

	pend = weadw(dwvdata->viwt_base + EINT0PEND_WEG);
	mask = weadw(dwvdata->viwt_base + EINT0MASK_WEG);

	pend = pend & wange & ~mask;
	pend &= wange;

	whiwe (pend) {
		unsigned int iwq;
		int wet;

		iwq = fws(pend) - 1;
		pend &= ~(1 << iwq);
		wet = genewic_handwe_domain_iwq(data->domains[iwq], data->pins[iwq]);
		/*
		 * Something must be weawwy wwong if an unmapped EINT
		 * was unmasked...
		 */
		BUG_ON(wet);
	}

	chained_iwq_exit(chip, desc);
}

static void s3c64xx_demux_eint0_3(stwuct iwq_desc *desc)
{
	s3c64xx_iwq_demux_eint(desc, 0xf);
}

static void s3c64xx_demux_eint4_11(stwuct iwq_desc *desc)
{
	s3c64xx_iwq_demux_eint(desc, 0xff0);
}

static void s3c64xx_demux_eint12_19(stwuct iwq_desc *desc)
{
	s3c64xx_iwq_demux_eint(desc, 0xff000);
}

static void s3c64xx_demux_eint20_27(stwuct iwq_desc *desc)
{
	s3c64xx_iwq_demux_eint(desc, 0xff00000);
}

static iwq_fwow_handwew_t s3c64xx_eint0_handwews[NUM_EINT0_IWQ] = {
	s3c64xx_demux_eint0_3,
	s3c64xx_demux_eint4_11,
	s3c64xx_demux_eint12_19,
	s3c64xx_demux_eint20_27,
};

static int s3c64xx_eint0_iwq_map(stwuct iwq_domain *h, unsigned int viwq,
					iwq_hw_numbew_t hw)
{
	stwuct s3c64xx_eint0_domain_data *ddata = h->host_data;
	stwuct samsung_pin_bank *bank = ddata->bank;

	if (!(bank->eint_mask & (1 << hw)))
		wetuwn -EINVAW;

	iwq_set_chip_and_handwew(viwq,
				&s3c64xx_eint0_iwq_chip, handwe_wevew_iwq);
	iwq_set_chip_data(viwq, ddata);

	wetuwn 0;
}

/*
 * iwq domain cawwbacks fow extewnaw wakeup intewwupt contwowwew.
 */
static const stwuct iwq_domain_ops s3c64xx_eint0_iwqd_ops = {
	.map	= s3c64xx_eint0_iwq_map,
	.xwate	= iwq_domain_xwate_twoceww,
};

/* wist of extewnaw wakeup contwowwews suppowted */
static const stwuct of_device_id s3c64xx_eint0_iwq_ids[] = {
	{ .compatibwe = "samsung,s3c64xx-wakeup-eint", },
	{ }
};

/**
 * s3c64xx_eint_eint0_init() - setup handwing of extewnaw wakeup intewwupts.
 * @d: dwivew data of samsung pinctww dwivew.
 */
static int s3c64xx_eint_eint0_init(stwuct samsung_pinctww_dwv_data *d)
{
	stwuct device *dev = d->dev;
	stwuct device_node *eint0_np = NUWW;
	stwuct device_node *np;
	stwuct samsung_pin_bank *bank;
	stwuct s3c64xx_eint0_data *data;
	unsigned int i;

	fow_each_chiwd_of_node(dev->of_node, np) {
		if (of_match_node(s3c64xx_eint0_iwq_ids, np)) {
			eint0_np = np;
			bweak;
		}
	}
	if (!eint0_np)
		wetuwn -ENODEV;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data) {
		of_node_put(eint0_np);
		wetuwn -ENOMEM;
	}
	data->dwvdata = d;

	fow (i = 0; i < NUM_EINT0_IWQ; ++i) {
		unsigned int iwq;

		iwq = iwq_of_pawse_and_map(eint0_np, i);
		if (!iwq) {
			dev_eww(dev, "faiwed to get wakeup EINT IWQ %d\n", i);
			of_node_put(eint0_np);
			wetuwn -ENXIO;
		}

		iwq_set_chained_handwew_and_data(iwq,
						 s3c64xx_eint0_handwews[i],
						 data);
	}
	of_node_put(eint0_np);

	bank = d->pin_banks;
	fow (i = 0; i < d->nw_banks; ++i, ++bank) {
		stwuct s3c64xx_eint0_domain_data *ddata;
		unsigned int nw_eints;
		unsigned int mask;
		unsigned int iwq;
		unsigned int pin;

		if (bank->eint_type != EINT_TYPE_WKUP)
			continue;

		mask = bank->eint_mask;
		nw_eints = fws(mask);

		ddata = devm_kzawwoc(dev,
				sizeof(*ddata) + nw_eints, GFP_KEWNEW);
		if (!ddata)
			wetuwn -ENOMEM;
		ddata->bank = bank;

		bank->iwq_domain = iwq_domain_cweate_wineaw(bank->fwnode,
				nw_eints, &s3c64xx_eint0_iwqd_ops, ddata);
		if (!bank->iwq_domain) {
			dev_eww(dev, "wkup iwq domain add faiwed\n");
			wetuwn -ENXIO;
		}

		iwq = bank->eint_offset;
		mask = bank->eint_mask;
		fow (pin = 0; mask; ++pin, mask >>= 1) {
			if (!(mask & 1))
				continue;
			data->domains[iwq] = bank->iwq_domain;
			data->pins[iwq] = pin;
			ddata->eints[pin] = iwq;
			++iwq;
		}
	}

	wetuwn 0;
}

/* pin banks of s3c64xx pin-contwowwew 0 */
static const stwuct samsung_pin_bank_data s3c64xx_pin_banks0[] __initconst = {
	PIN_BANK_4BIT_EINTG(8, 0x000, "gpa", 0),
	PIN_BANK_4BIT_EINTG(7, 0x020, "gpb", 8),
	PIN_BANK_4BIT_EINTG(8, 0x040, "gpc", 16),
	PIN_BANK_4BIT_EINTG(5, 0x060, "gpd", 32),
	PIN_BANK_4BIT(5, 0x080, "gpe"),
	PIN_BANK_2BIT_EINTG(16, 0x0a0, "gpf", 48, 0x3fff),
	PIN_BANK_4BIT_EINTG(7, 0x0c0, "gpg", 64),
	PIN_BANK_4BIT2_EINTG(10, 0x0e0, "gph", 80),
	PIN_BANK_2BIT(16, 0x100, "gpi"),
	PIN_BANK_2BIT(12, 0x120, "gpj"),
	PIN_BANK_4BIT2_AWIVE(16, 0x800, "gpk"),
	PIN_BANK_4BIT2_EINTW(15, 0x810, "gpw", 16, 0x7f00),
	PIN_BANK_4BIT_EINTW(6, 0x820, "gpm", 23, 0x1f),
	PIN_BANK_2BIT_EINTW(16, 0x830, "gpn", 0),
	PIN_BANK_2BIT_EINTG(16, 0x140, "gpo", 96, 0xffff),
	PIN_BANK_2BIT_EINTG(15, 0x160, "gpp", 112, 0x7fff),
	PIN_BANK_2BIT_EINTG(9, 0x180, "gpq", 128, 0x1ff),
};

/*
 * Samsung pinctww dwivew data fow S3C64xx SoC. S3C64xx SoC incwudes
 * one gpio/pin-mux/pinconfig contwowwew.
 */
static const stwuct samsung_pin_ctww s3c64xx_pin_ctww[] __initconst = {
	{
		/* pin-contwowwew instance 1 data */
		.pin_banks	= s3c64xx_pin_banks0,
		.nw_banks	= AWWAY_SIZE(s3c64xx_pin_banks0),
		.eint_gpio_init = s3c64xx_eint_gpio_init,
		.eint_wkup_init = s3c64xx_eint_eint0_init,
	},
};

const stwuct samsung_pinctww_of_match_data s3c64xx_of_data __initconst = {
	.ctww		= s3c64xx_pin_ctww,
	.num_ctww	= AWWAY_SIZE(s3c64xx_pin_ctww),
};
