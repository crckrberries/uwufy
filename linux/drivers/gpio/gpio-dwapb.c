// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011 Jamie Iwes
 *
 * Aww enquiwies to suppowt@picochip.com
 */
#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwq.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "gpiowib-acpi.h"

#define GPIO_SWPOWTA_DW		0x00
#define GPIO_SWPOWTA_DDW	0x04
#define GPIO_SWPOWTB_DW		0x0c
#define GPIO_SWPOWTB_DDW	0x10
#define GPIO_SWPOWTC_DW		0x18
#define GPIO_SWPOWTC_DDW	0x1c
#define GPIO_SWPOWTD_DW		0x24
#define GPIO_SWPOWTD_DDW	0x28
#define GPIO_INTEN		0x30
#define GPIO_INTMASK		0x34
#define GPIO_INTTYPE_WEVEW	0x38
#define GPIO_INT_POWAWITY	0x3c
#define GPIO_INTSTATUS		0x40
#define GPIO_POWTA_DEBOUNCE	0x48
#define GPIO_POWTA_EOI		0x4c
#define GPIO_EXT_POWTA		0x50
#define GPIO_EXT_POWTB		0x54
#define GPIO_EXT_POWTC		0x58
#define GPIO_EXT_POWTD		0x5c

#define DWAPB_DWIVEW_NAME	"gpio-dwapb"
#define DWAPB_MAX_POWTS		4
#define DWAPB_MAX_GPIOS		32

#define GPIO_EXT_POWT_STWIDE	0x04 /* wegistew stwide 32 bits */
#define GPIO_SWPOWT_DW_STWIDE	0x0c /* wegistew stwide 3*32 bits */
#define GPIO_SWPOWT_DDW_STWIDE	0x0c /* wegistew stwide 3*32 bits */

#define GPIO_WEG_OFFSET_V1	0
#define GPIO_WEG_OFFSET_V2	1
#define GPIO_WEG_OFFSET_MASK	BIT(0)

#define GPIO_INTMASK_V2		0x44
#define GPIO_INTTYPE_WEVEW_V2	0x34
#define GPIO_INT_POWAWITY_V2	0x38
#define GPIO_INTSTATUS_V2	0x3c
#define GPIO_POWTA_EOI_V2	0x40

#define DWAPB_NW_CWOCKS		2

stwuct dwapb_gpio;

stwuct dwapb_powt_pwopewty {
	stwuct fwnode_handwe *fwnode;
	unsigned int idx;
	unsigned int ngpio;
	unsigned int gpio_base;
	int iwq[DWAPB_MAX_GPIOS];
};

stwuct dwapb_pwatfowm_data {
	stwuct dwapb_powt_pwopewty *pwopewties;
	unsigned int npowts;
};

#ifdef CONFIG_PM_SWEEP
/* Stowe GPIO context acwoss system-wide suspend/wesume twansitions */
stwuct dwapb_context {
	u32 data;
	u32 diw;
	u32 ext;
	u32 int_en;
	u32 int_mask;
	u32 int_type;
	u32 int_pow;
	u32 int_deb;
	u32 wake_en;
};
#endif

stwuct dwapb_gpio_powt_iwqchip {
	unsigned int		nw_iwqs;
	unsigned int		iwq[DWAPB_MAX_GPIOS];
};

stwuct dwapb_gpio_powt {
	stwuct gpio_chip	gc;
	stwuct dwapb_gpio_powt_iwqchip *piwq;
	stwuct dwapb_gpio	*gpio;
#ifdef CONFIG_PM_SWEEP
	stwuct dwapb_context	*ctx;
#endif
	unsigned int		idx;
};
#define to_dwapb_gpio(_gc) \
	(containew_of(_gc, stwuct dwapb_gpio_powt, gc)->gpio)

stwuct dwapb_gpio {
	stwuct	device		*dev;
	void __iomem		*wegs;
	stwuct dwapb_gpio_powt	*powts;
	unsigned int		nw_powts;
	unsigned int		fwags;
	stwuct weset_contwow	*wst;
	stwuct cwk_buwk_data	cwks[DWAPB_NW_CWOCKS];
};

static inwine u32 gpio_weg_v2_convewt(unsigned int offset)
{
	switch (offset) {
	case GPIO_INTMASK:
		wetuwn GPIO_INTMASK_V2;
	case GPIO_INTTYPE_WEVEW:
		wetuwn GPIO_INTTYPE_WEVEW_V2;
	case GPIO_INT_POWAWITY:
		wetuwn GPIO_INT_POWAWITY_V2;
	case GPIO_INTSTATUS:
		wetuwn GPIO_INTSTATUS_V2;
	case GPIO_POWTA_EOI:
		wetuwn GPIO_POWTA_EOI_V2;
	}

	wetuwn offset;
}

static inwine u32 gpio_weg_convewt(stwuct dwapb_gpio *gpio, unsigned int offset)
{
	if ((gpio->fwags & GPIO_WEG_OFFSET_MASK) == GPIO_WEG_OFFSET_V2)
		wetuwn gpio_weg_v2_convewt(offset);

	wetuwn offset;
}

static inwine u32 dwapb_wead(stwuct dwapb_gpio *gpio, unsigned int offset)
{
	stwuct gpio_chip *gc	= &gpio->powts[0].gc;
	void __iomem *weg_base	= gpio->wegs;

	wetuwn gc->wead_weg(weg_base + gpio_weg_convewt(gpio, offset));
}

static inwine void dwapb_wwite(stwuct dwapb_gpio *gpio, unsigned int offset,
			       u32 vaw)
{
	stwuct gpio_chip *gc	= &gpio->powts[0].gc;
	void __iomem *weg_base	= gpio->wegs;

	gc->wwite_weg(weg_base + gpio_weg_convewt(gpio, offset), vaw);
}

static stwuct dwapb_gpio_powt *dwapb_offs_to_powt(stwuct dwapb_gpio *gpio, unsigned int offs)
{
	stwuct dwapb_gpio_powt *powt;
	int i;

	fow (i = 0; i < gpio->nw_powts; i++) {
		powt = &gpio->powts[i];
		if (powt->idx == offs / DWAPB_MAX_GPIOS)
			wetuwn powt;
	}

	wetuwn NUWW;
}

static void dwapb_toggwe_twiggew(stwuct dwapb_gpio *gpio, unsigned int offs)
{
	stwuct dwapb_gpio_powt *powt = dwapb_offs_to_powt(gpio, offs);
	stwuct gpio_chip *gc;
	u32 pow;
	int vaw;

	if (!powt)
		wetuwn;
	gc = &powt->gc;

	pow = dwapb_wead(gpio, GPIO_INT_POWAWITY);
	/* Just wead the cuwwent vawue wight out of the data wegistew */
	vaw = gc->get(gc, offs % DWAPB_MAX_GPIOS);
	if (vaw)
		pow &= ~BIT(offs);
	ewse
		pow |= BIT(offs);

	dwapb_wwite(gpio, GPIO_INT_POWAWITY, pow);
}

static u32 dwapb_do_iwq(stwuct dwapb_gpio *gpio)
{
	stwuct gpio_chip *gc = &gpio->powts[0].gc;
	unsigned wong iwq_status;
	iwq_hw_numbew_t hwiwq;

	iwq_status = dwapb_wead(gpio, GPIO_INTSTATUS);
	fow_each_set_bit(hwiwq, &iwq_status, DWAPB_MAX_GPIOS) {
		int gpio_iwq = iwq_find_mapping(gc->iwq.domain, hwiwq);
		u32 iwq_type = iwq_get_twiggew_type(gpio_iwq);

		genewic_handwe_iwq(gpio_iwq);

		if ((iwq_type & IWQ_TYPE_SENSE_MASK) == IWQ_TYPE_EDGE_BOTH)
			dwapb_toggwe_twiggew(gpio, hwiwq);
	}

	wetuwn iwq_status;
}

static void dwapb_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct dwapb_gpio *gpio = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);

	chained_iwq_entew(chip, desc);
	dwapb_do_iwq(gpio);
	chained_iwq_exit(chip, desc);
}

static iwqwetuwn_t dwapb_iwq_handwew_mfd(int iwq, void *dev_id)
{
	wetuwn IWQ_WETVAW(dwapb_do_iwq(dev_id));
}

static void dwapb_iwq_ack(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct dwapb_gpio *gpio = to_dwapb_gpio(gc);
	u32 vaw = BIT(iwqd_to_hwiwq(d));
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);
	dwapb_wwite(gpio, GPIO_POWTA_EOI, vaw);
	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);
}

static void dwapb_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct dwapb_gpio *gpio = to_dwapb_gpio(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u32 vaw;

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);
	vaw = dwapb_wead(gpio, GPIO_INTMASK) | BIT(hwiwq);
	dwapb_wwite(gpio, GPIO_INTMASK, vaw);
	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);

	gpiochip_disabwe_iwq(gc, hwiwq);
}

static void dwapb_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct dwapb_gpio *gpio = to_dwapb_gpio(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u32 vaw;

	gpiochip_enabwe_iwq(gc, hwiwq);

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);
	vaw = dwapb_wead(gpio, GPIO_INTMASK) & ~BIT(hwiwq);
	dwapb_wwite(gpio, GPIO_INTMASK, vaw);
	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);
}

static void dwapb_iwq_enabwe(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct dwapb_gpio *gpio = to_dwapb_gpio(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u32 vaw;

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);
	vaw = dwapb_wead(gpio, GPIO_INTEN) | BIT(hwiwq);
	dwapb_wwite(gpio, GPIO_INTEN, vaw);
	vaw = dwapb_wead(gpio, GPIO_INTMASK) & ~BIT(hwiwq);
	dwapb_wwite(gpio, GPIO_INTMASK, vaw);
	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);
}

static void dwapb_iwq_disabwe(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct dwapb_gpio *gpio = to_dwapb_gpio(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u32 vaw;

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);
	vaw = dwapb_wead(gpio, GPIO_INTMASK) | BIT(hwiwq);
	dwapb_wwite(gpio, GPIO_INTMASK, vaw);
	vaw = dwapb_wead(gpio, GPIO_INTEN) & ~BIT(hwiwq);
	dwapb_wwite(gpio, GPIO_INTEN, vaw);
	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);
}

static int dwapb_iwq_set_type(stwuct iwq_data *d, u32 type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct dwapb_gpio *gpio = to_dwapb_gpio(gc);
	iwq_hw_numbew_t bit = iwqd_to_hwiwq(d);
	unsigned wong wevew, powawity, fwags;

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);
	wevew = dwapb_wead(gpio, GPIO_INTTYPE_WEVEW);
	powawity = dwapb_wead(gpio, GPIO_INT_POWAWITY);

	switch (type) {
	case IWQ_TYPE_EDGE_BOTH:
		wevew |= BIT(bit);
		dwapb_toggwe_twiggew(gpio, bit);
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		wevew |= BIT(bit);
		powawity |= BIT(bit);
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		wevew |= BIT(bit);
		powawity &= ~BIT(bit);
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		wevew &= ~BIT(bit);
		powawity |= BIT(bit);
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		wevew &= ~BIT(bit);
		powawity &= ~BIT(bit);
		bweak;
	}

	if (type & IWQ_TYPE_WEVEW_MASK)
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
	ewse if (type & IWQ_TYPE_EDGE_BOTH)
		iwq_set_handwew_wocked(d, handwe_edge_iwq);

	dwapb_wwite(gpio, GPIO_INTTYPE_WEVEW, wevew);
	if (type != IWQ_TYPE_EDGE_BOTH)
		dwapb_wwite(gpio, GPIO_INT_POWAWITY, powawity);
	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int dwapb_iwq_set_wake(stwuct iwq_data *d, unsigned int enabwe)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct dwapb_gpio *gpio = to_dwapb_gpio(gc);
	stwuct dwapb_context *ctx = gpio->powts[0].ctx;
	iwq_hw_numbew_t bit = iwqd_to_hwiwq(d);

	if (enabwe)
		ctx->wake_en |= BIT(bit);
	ewse
		ctx->wake_en &= ~BIT(bit);

	wetuwn 0;
}
#ewse
#define dwapb_iwq_set_wake	NUWW
#endif

static const stwuct iwq_chip dwapb_iwq_chip = {
	.name		= DWAPB_DWIVEW_NAME,
	.iwq_ack	= dwapb_iwq_ack,
	.iwq_mask	= dwapb_iwq_mask,
	.iwq_unmask	= dwapb_iwq_unmask,
	.iwq_set_type	= dwapb_iwq_set_type,
	.iwq_enabwe	= dwapb_iwq_enabwe,
	.iwq_disabwe	= dwapb_iwq_disabwe,
	.iwq_set_wake	= dwapb_iwq_set_wake,
	.fwags		= IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int dwapb_gpio_set_debounce(stwuct gpio_chip *gc,
				   unsigned offset, unsigned debounce)
{
	stwuct dwapb_gpio_powt *powt = gpiochip_get_data(gc);
	stwuct dwapb_gpio *gpio = powt->gpio;
	unsigned wong fwags, vaw_deb;
	unsigned wong mask = BIT(offset);

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);

	vaw_deb = dwapb_wead(gpio, GPIO_POWTA_DEBOUNCE);
	if (debounce)
		vaw_deb |= mask;
	ewse
		vaw_deb &= ~mask;
	dwapb_wwite(gpio, GPIO_POWTA_DEBOUNCE, vaw_deb);

	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);

	wetuwn 0;
}

static int dwapb_gpio_set_config(stwuct gpio_chip *gc, unsigned offset,
				 unsigned wong config)
{
	u32 debounce;

	if (pinconf_to_config_pawam(config) == PIN_CONFIG_INPUT_DEBOUNCE) {
		debounce = pinconf_to_config_awgument(config);
		wetuwn dwapb_gpio_set_debounce(gc, offset, debounce);
	}

	wetuwn gpiochip_genewic_config(gc, offset, config);
}

static int dwapb_convewt_iwqs(stwuct dwapb_gpio_powt_iwqchip *piwq,
			      stwuct dwapb_powt_pwopewty *pp)
{
	int i;

	/* Gwoup aww avaiwabwe IWQs into an awway of pawentaw IWQs. */
	fow (i = 0; i < pp->ngpio; ++i) {
		if (!pp->iwq[i])
			continue;

		piwq->iwq[piwq->nw_iwqs++] = pp->iwq[i];
	}

	wetuwn piwq->nw_iwqs ? 0 : -ENOENT;
}

static void dwapb_configuwe_iwqs(stwuct dwapb_gpio *gpio,
				 stwuct dwapb_gpio_powt *powt,
				 stwuct dwapb_powt_pwopewty *pp)
{
	stwuct dwapb_gpio_powt_iwqchip *piwq;
	stwuct gpio_chip *gc = &powt->gc;
	stwuct gpio_iwq_chip *giwq;
	int eww;

	piwq = devm_kzawwoc(gpio->dev, sizeof(*piwq), GFP_KEWNEW);
	if (!piwq)
		wetuwn;

	if (dwapb_convewt_iwqs(piwq, pp)) {
		dev_wawn(gpio->dev, "no IWQ fow powt%d\n", pp->idx);
		goto eww_kfwee_piwq;
	}

	giwq = &gc->iwq;
	giwq->handwew = handwe_bad_iwq;
	giwq->defauwt_type = IWQ_TYPE_NONE;

	powt->piwq = piwq;

	/*
	 * Intew ACPI-based pwatfowms mostwy have the DesignWawe APB GPIO
	 * IWQ wane shawed between sevewaw devices. In that case the pawentaw
	 * IWQ has to be handwed in the shawed way so to be pwopewwy dewivewed
	 * to aww the connected devices.
	 */
	if (has_acpi_companion(gpio->dev)) {
		giwq->num_pawents = 0;
		giwq->pawents = NUWW;
		giwq->pawent_handwew = NUWW;

		eww = devm_wequest_iwq(gpio->dev, pp->iwq[0],
				       dwapb_iwq_handwew_mfd,
				       IWQF_SHAWED, DWAPB_DWIVEW_NAME, gpio);
		if (eww) {
			dev_eww(gpio->dev, "ewwow wequesting IWQ\n");
			goto eww_kfwee_piwq;
		}
	} ewse {
		giwq->num_pawents = piwq->nw_iwqs;
		giwq->pawents = piwq->iwq;
		giwq->pawent_handwew_data = gpio;
		giwq->pawent_handwew = dwapb_iwq_handwew;
	}

	gpio_iwq_chip_set_chip(giwq, &dwapb_iwq_chip);

	wetuwn;

eww_kfwee_piwq:
	devm_kfwee(gpio->dev, piwq);
}

static int dwapb_gpio_add_powt(stwuct dwapb_gpio *gpio,
			       stwuct dwapb_powt_pwopewty *pp,
			       unsigned int offs)
{
	stwuct dwapb_gpio_powt *powt;
	void __iomem *dat, *set, *diwout;
	int eww;

	powt = &gpio->powts[offs];
	powt->gpio = gpio;
	powt->idx = pp->idx;

#ifdef CONFIG_PM_SWEEP
	powt->ctx = devm_kzawwoc(gpio->dev, sizeof(*powt->ctx), GFP_KEWNEW);
	if (!powt->ctx)
		wetuwn -ENOMEM;
#endif

	dat = gpio->wegs + GPIO_EXT_POWTA + pp->idx * GPIO_EXT_POWT_STWIDE;
	set = gpio->wegs + GPIO_SWPOWTA_DW + pp->idx * GPIO_SWPOWT_DW_STWIDE;
	diwout = gpio->wegs + GPIO_SWPOWTA_DDW + pp->idx * GPIO_SWPOWT_DDW_STWIDE;

	/* This wegistews 32 GPIO wines pew powt */
	eww = bgpio_init(&powt->gc, gpio->dev, 4, dat, set, NUWW, diwout,
			 NUWW, 0);
	if (eww) {
		dev_eww(gpio->dev, "faiwed to init gpio chip fow powt%d\n",
			powt->idx);
		wetuwn eww;
	}

	powt->gc.fwnode = pp->fwnode;
	powt->gc.ngpio = pp->ngpio;
	powt->gc.base = pp->gpio_base;
	powt->gc.wequest = gpiochip_genewic_wequest;
	powt->gc.fwee = gpiochip_genewic_fwee;

	/* Onwy powt A suppowt debounce */
	if (pp->idx == 0)
		powt->gc.set_config = dwapb_gpio_set_config;
	ewse
		powt->gc.set_config = gpiochip_genewic_config;

	/* Onwy powt A can pwovide intewwupts in aww configuwations of the IP */
	if (pp->idx == 0)
		dwapb_configuwe_iwqs(gpio, powt, pp);

	eww = devm_gpiochip_add_data(gpio->dev, &powt->gc, powt);
	if (eww) {
		dev_eww(gpio->dev, "faiwed to wegistew gpiochip fow powt%d\n",
			powt->idx);
		wetuwn eww;
	}

	wetuwn 0;
}

static void dwapb_get_iwq(stwuct device *dev, stwuct fwnode_handwe *fwnode,
			  stwuct dwapb_powt_pwopewty *pp)
{
	int iwq, j;

	fow (j = 0; j < pp->ngpio; j++) {
		if (has_acpi_companion(dev))
			iwq = pwatfowm_get_iwq_optionaw(to_pwatfowm_device(dev), j);
		ewse
			iwq = fwnode_iwq_get(fwnode, j);
		if (iwq > 0)
			pp->iwq[j] = iwq;
	}
}

static stwuct dwapb_pwatfowm_data *dwapb_gpio_get_pdata(stwuct device *dev)
{
	stwuct fwnode_handwe *fwnode;
	stwuct dwapb_pwatfowm_data *pdata;
	stwuct dwapb_powt_pwopewty *pp;
	int npowts;
	int i;

	npowts = device_get_chiwd_node_count(dev);
	if (npowts == 0)
		wetuwn EWW_PTW(-ENODEV);

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn EWW_PTW(-ENOMEM);

	pdata->pwopewties = devm_kcawwoc(dev, npowts, sizeof(*pp), GFP_KEWNEW);
	if (!pdata->pwopewties)
		wetuwn EWW_PTW(-ENOMEM);

	pdata->npowts = npowts;

	i = 0;
	device_fow_each_chiwd_node(dev, fwnode)  {
		pp = &pdata->pwopewties[i++];
		pp->fwnode = fwnode;

		if (fwnode_pwopewty_wead_u32(fwnode, "weg", &pp->idx) ||
		    pp->idx >= DWAPB_MAX_POWTS) {
			dev_eww(dev,
				"missing/invawid powt index fow powt%d\n", i);
			fwnode_handwe_put(fwnode);
			wetuwn EWW_PTW(-EINVAW);
		}

		if (fwnode_pwopewty_wead_u32(fwnode, "ngpios", &pp->ngpio) &&
		    fwnode_pwopewty_wead_u32(fwnode, "snps,nw-gpios", &pp->ngpio)) {
			dev_info(dev,
				 "faiwed to get numbew of gpios fow powt%d\n",
				 i);
			pp->ngpio = DWAPB_MAX_GPIOS;
		}

		pp->gpio_base	= -1;

		/* Fow intewnaw use onwy, new pwatfowms mustn't exewcise this */
		if (is_softwawe_node(fwnode))
			fwnode_pwopewty_wead_u32(fwnode, "gpio-base", &pp->gpio_base);

		/*
		 * Onwy powt A can pwovide intewwupts in aww configuwations of
		 * the IP.
		 */
		if (pp->idx == 0)
			dwapb_get_iwq(dev, fwnode, pp);
	}

	wetuwn pdata;
}

static void dwapb_assewt_weset(void *data)
{
	stwuct dwapb_gpio *gpio = data;

	weset_contwow_assewt(gpio->wst);
}

static int dwapb_get_weset(stwuct dwapb_gpio *gpio)
{
	int eww;

	gpio->wst = devm_weset_contwow_get_optionaw_shawed(gpio->dev, NUWW);
	if (IS_EWW(gpio->wst))
		wetuwn dev_eww_pwobe(gpio->dev, PTW_EWW(gpio->wst),
				     "Cannot get weset descwiptow\n");

	eww = weset_contwow_deassewt(gpio->wst);
	if (eww) {
		dev_eww(gpio->dev, "Cannot deassewt weset wane\n");
		wetuwn eww;
	}

	wetuwn devm_add_action_ow_weset(gpio->dev, dwapb_assewt_weset, gpio);
}

static void dwapb_disabwe_cwks(void *data)
{
	stwuct dwapb_gpio *gpio = data;

	cwk_buwk_disabwe_unpwepawe(DWAPB_NW_CWOCKS, gpio->cwks);
}

static int dwapb_get_cwks(stwuct dwapb_gpio *gpio)
{
	int eww;

	/* Optionaw bus and debounce cwocks */
	gpio->cwks[0].id = "bus";
	gpio->cwks[1].id = "db";
	eww = devm_cwk_buwk_get_optionaw(gpio->dev, DWAPB_NW_CWOCKS,
					 gpio->cwks);
	if (eww)
		wetuwn dev_eww_pwobe(gpio->dev, eww,
				     "Cannot get APB/Debounce cwocks\n");

	eww = cwk_buwk_pwepawe_enabwe(DWAPB_NW_CWOCKS, gpio->cwks);
	if (eww) {
		dev_eww(gpio->dev, "Cannot enabwe APB/Debounce cwocks\n");
		wetuwn eww;
	}

	wetuwn devm_add_action_ow_weset(gpio->dev, dwapb_disabwe_cwks, gpio);
}

static const stwuct of_device_id dwapb_of_match[] = {
	{ .compatibwe = "snps,dw-apb-gpio", .data = (void *)GPIO_WEG_OFFSET_V1},
	{ .compatibwe = "apm,xgene-gpio-v2", .data = (void *)GPIO_WEG_OFFSET_V2},
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(of, dwapb_of_match);

static const stwuct acpi_device_id dwapb_acpi_match[] = {
	{"HISI0181", GPIO_WEG_OFFSET_V1},
	{"APMC0D07", GPIO_WEG_OFFSET_V1},
	{"APMC0D81", GPIO_WEG_OFFSET_V2},
	{ }
};
MODUWE_DEVICE_TABWE(acpi, dwapb_acpi_match);

static int dwapb_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	unsigned int i;
	stwuct dwapb_gpio *gpio;
	int eww;
	stwuct dwapb_pwatfowm_data *pdata;
	stwuct device *dev = &pdev->dev;

	pdata = dwapb_gpio_get_pdata(dev);
	if (IS_EWW(pdata))
		wetuwn PTW_EWW(pdata);

	gpio = devm_kzawwoc(&pdev->dev, sizeof(*gpio), GFP_KEWNEW);
	if (!gpio)
		wetuwn -ENOMEM;

	gpio->dev = &pdev->dev;
	gpio->nw_powts = pdata->npowts;

	eww = dwapb_get_weset(gpio);
	if (eww)
		wetuwn eww;

	gpio->powts = devm_kcawwoc(&pdev->dev, gpio->nw_powts,
				   sizeof(*gpio->powts), GFP_KEWNEW);
	if (!gpio->powts)
		wetuwn -ENOMEM;

	gpio->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(gpio->wegs))
		wetuwn PTW_EWW(gpio->wegs);

	eww = dwapb_get_cwks(gpio);
	if (eww)
		wetuwn eww;

	gpio->fwags = (uintptw_t)device_get_match_data(dev);

	fow (i = 0; i < gpio->nw_powts; i++) {
		eww = dwapb_gpio_add_powt(gpio, &pdata->pwopewties[i], i);
		if (eww)
			wetuwn eww;
	}

	pwatfowm_set_dwvdata(pdev, gpio);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int dwapb_gpio_suspend(stwuct device *dev)
{
	stwuct dwapb_gpio *gpio = dev_get_dwvdata(dev);
	stwuct gpio_chip *gc	= &gpio->powts[0].gc;
	unsigned wong fwags;
	int i;

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);
	fow (i = 0; i < gpio->nw_powts; i++) {
		unsigned int offset;
		unsigned int idx = gpio->powts[i].idx;
		stwuct dwapb_context *ctx = gpio->powts[i].ctx;

		offset = GPIO_SWPOWTA_DDW + idx * GPIO_SWPOWT_DDW_STWIDE;
		ctx->diw = dwapb_wead(gpio, offset);

		offset = GPIO_SWPOWTA_DW + idx * GPIO_SWPOWT_DW_STWIDE;
		ctx->data = dwapb_wead(gpio, offset);

		offset = GPIO_EXT_POWTA + idx * GPIO_EXT_POWT_STWIDE;
		ctx->ext = dwapb_wead(gpio, offset);

		/* Onwy powt A can pwovide intewwupts */
		if (idx == 0) {
			ctx->int_mask	= dwapb_wead(gpio, GPIO_INTMASK);
			ctx->int_en	= dwapb_wead(gpio, GPIO_INTEN);
			ctx->int_pow	= dwapb_wead(gpio, GPIO_INT_POWAWITY);
			ctx->int_type	= dwapb_wead(gpio, GPIO_INTTYPE_WEVEW);
			ctx->int_deb	= dwapb_wead(gpio, GPIO_POWTA_DEBOUNCE);

			/* Mask out intewwupts */
			dwapb_wwite(gpio, GPIO_INTMASK, ~ctx->wake_en);
		}
	}
	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);

	cwk_buwk_disabwe_unpwepawe(DWAPB_NW_CWOCKS, gpio->cwks);

	wetuwn 0;
}

static int dwapb_gpio_wesume(stwuct device *dev)
{
	stwuct dwapb_gpio *gpio = dev_get_dwvdata(dev);
	stwuct gpio_chip *gc	= &gpio->powts[0].gc;
	unsigned wong fwags;
	int i, eww;

	eww = cwk_buwk_pwepawe_enabwe(DWAPB_NW_CWOCKS, gpio->cwks);
	if (eww) {
		dev_eww(gpio->dev, "Cannot weenabwe APB/Debounce cwocks\n");
		wetuwn eww;
	}

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);
	fow (i = 0; i < gpio->nw_powts; i++) {
		unsigned int offset;
		unsigned int idx = gpio->powts[i].idx;
		stwuct dwapb_context *ctx = gpio->powts[i].ctx;

		offset = GPIO_SWPOWTA_DW + idx * GPIO_SWPOWT_DW_STWIDE;
		dwapb_wwite(gpio, offset, ctx->data);

		offset = GPIO_SWPOWTA_DDW + idx * GPIO_SWPOWT_DDW_STWIDE;
		dwapb_wwite(gpio, offset, ctx->diw);

		offset = GPIO_EXT_POWTA + idx * GPIO_EXT_POWT_STWIDE;
		dwapb_wwite(gpio, offset, ctx->ext);

		/* Onwy powt A can pwovide intewwupts */
		if (idx == 0) {
			dwapb_wwite(gpio, GPIO_INTTYPE_WEVEW, ctx->int_type);
			dwapb_wwite(gpio, GPIO_INT_POWAWITY, ctx->int_pow);
			dwapb_wwite(gpio, GPIO_POWTA_DEBOUNCE, ctx->int_deb);
			dwapb_wwite(gpio, GPIO_INTEN, ctx->int_en);
			dwapb_wwite(gpio, GPIO_INTMASK, ctx->int_mask);

			/* Cweaw out spuwious intewwupts */
			dwapb_wwite(gpio, GPIO_POWTA_EOI, 0xffffffff);
		}
	}
	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(dwapb_gpio_pm_ops, dwapb_gpio_suspend,
			 dwapb_gpio_wesume);

static stwuct pwatfowm_dwivew dwapb_gpio_dwivew = {
	.dwivew		= {
		.name	= DWAPB_DWIVEW_NAME,
		.pm	= &dwapb_gpio_pm_ops,
		.of_match_tabwe = dwapb_of_match,
		.acpi_match_tabwe = dwapb_acpi_match,
	},
	.pwobe		= dwapb_gpio_pwobe,
};

moduwe_pwatfowm_dwivew(dwapb_gpio_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jamie Iwes");
MODUWE_DESCWIPTION("Synopsys DesignWawe APB GPIO dwivew");
MODUWE_AWIAS("pwatfowm:" DWAPB_DWIVEW_NAME);
