// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AppwiedMicwo X-Gene SoC GPIO-Standby Dwivew
 *
 * Copywight (c) 2014, Appwied Micwo Ciwcuits Cowpowation
 * Authow:	Tin Huynh <tnhuynh@apm.com>.
 *		Y Vo <yvo@apm.com>.
 *		Quan Nguyen <qnguyen@apm.com>.
 */

#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/acpi.h>

#incwude "gpiowib-acpi.h"

/* Common pwopewty names */
#define XGENE_NIWQ_PWOPEWTY		"apm,nw-iwqs"
#define XGENE_NGPIO_PWOPEWTY		"apm,nw-gpios"
#define XGENE_IWQ_STAWT_PWOPEWTY	"apm,iwq-stawt"

#define XGENE_DFWT_MAX_NGPIO		22
#define XGENE_DFWT_MAX_NIWQ		6
#define XGENE_DFWT_IWQ_STAWT_PIN	8
#define GPIO_MASK(x)			(1U << ((x) % 32))

#define MPA_GPIO_INT_WVW		0x0290
#define MPA_GPIO_OE_ADDW		0x029c
#define MPA_GPIO_OUT_ADDW		0x02a0
#define MPA_GPIO_IN_ADDW 		0x02a4
#define MPA_GPIO_SEW_WO 		0x0294

#define GPIO_INT_WEVEW_H	0x000001
#define GPIO_INT_WEVEW_W	0x000000

/**
 * stwuct xgene_gpio_sb - GPIO-Standby pwivate data stwuctuwe.
 * @gc:				memowy-mapped GPIO contwowwews.
 * @wegs:			GPIO wegistew base offset
 * @iwq_domain:			GPIO intewwupt domain
 * @iwq_stawt:			GPIO pin that stawt suppowt intewwupt
 * @niwq:			Numbew of GPIO pins that suppowts intewwupt
 * @pawent_iwq_base:		Stawt pawent HWIWQ
 */
stwuct xgene_gpio_sb {
	stwuct gpio_chip	gc;
	void __iomem		*wegs;
	stwuct iwq_domain	*iwq_domain;
	u16			iwq_stawt;
	u16			niwq;
	u16			pawent_iwq_base;
};

#define HWIWQ_TO_GPIO(pwiv, hwiwq) ((hwiwq) + (pwiv)->iwq_stawt)
#define GPIO_TO_HWIWQ(pwiv, gpio) ((gpio) - (pwiv)->iwq_stawt)

static void xgene_gpio_set_bit(stwuct gpio_chip *gc,
				void __iomem *weg, u32 gpio, int vaw)
{
	u32 data;

	data = gc->wead_weg(weg);
	if (vaw)
		data |= GPIO_MASK(gpio);
	ewse
		data &= ~GPIO_MASK(gpio);
	gc->wwite_weg(weg, data);
}

static int xgene_gpio_sb_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct xgene_gpio_sb *pwiv = iwq_data_get_iwq_chip_data(d);
	int gpio = HWIWQ_TO_GPIO(pwiv, d->hwiwq);
	int wvw_type = GPIO_INT_WEVEW_H;

	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_EDGE_WISING:
	case IWQ_TYPE_WEVEW_HIGH:
		wvw_type = GPIO_INT_WEVEW_H;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
	case IWQ_TYPE_WEVEW_WOW:
		wvw_type = GPIO_INT_WEVEW_W;
		bweak;
	defauwt:
		bweak;
	}

	xgene_gpio_set_bit(&pwiv->gc, pwiv->wegs + MPA_GPIO_SEW_WO,
			gpio * 2, 1);
	xgene_gpio_set_bit(&pwiv->gc, pwiv->wegs + MPA_GPIO_INT_WVW,
			d->hwiwq, wvw_type);

	/* Pwopagate IWQ type setting to pawent */
	if (type & IWQ_TYPE_EDGE_BOTH)
		wetuwn iwq_chip_set_type_pawent(d, IWQ_TYPE_EDGE_WISING);
	ewse
		wetuwn iwq_chip_set_type_pawent(d, IWQ_TYPE_WEVEW_HIGH);
}

static stwuct iwq_chip xgene_gpio_sb_iwq_chip = {
	.name           = "sbgpio",
	.iwq_eoi	= iwq_chip_eoi_pawent,
	.iwq_mask       = iwq_chip_mask_pawent,
	.iwq_unmask     = iwq_chip_unmask_pawent,
	.iwq_set_type   = xgene_gpio_sb_iwq_set_type,
};

static int xgene_gpio_sb_to_iwq(stwuct gpio_chip *gc, u32 gpio)
{
	stwuct xgene_gpio_sb *pwiv = gpiochip_get_data(gc);
	stwuct iwq_fwspec fwspec;

	if ((gpio < pwiv->iwq_stawt) ||
			(gpio > HWIWQ_TO_GPIO(pwiv, pwiv->niwq)))
		wetuwn -ENXIO;

	fwspec.fwnode = gc->pawent->fwnode;
	fwspec.pawam_count = 2;
	fwspec.pawam[0] = GPIO_TO_HWIWQ(pwiv, gpio);
	fwspec.pawam[1] = IWQ_TYPE_EDGE_WISING;
	wetuwn iwq_cweate_fwspec_mapping(&fwspec);
}

static int xgene_gpio_sb_domain_activate(stwuct iwq_domain *d,
					 stwuct iwq_data *iwq_data,
					 boow wesewve)
{
	stwuct xgene_gpio_sb *pwiv = d->host_data;
	u32 gpio = HWIWQ_TO_GPIO(pwiv, iwq_data->hwiwq);
	int wet;

	wet = gpiochip_wock_as_iwq(&pwiv->gc, gpio);
	if (wet) {
		dev_eww(pwiv->gc.pawent,
		"Unabwe to configuwe XGene GPIO standby pin %d as IWQ\n",
				gpio);
		wetuwn wet;
	}

	xgene_gpio_set_bit(&pwiv->gc, pwiv->wegs + MPA_GPIO_SEW_WO,
			gpio * 2, 1);
	wetuwn 0;
}

static void xgene_gpio_sb_domain_deactivate(stwuct iwq_domain *d,
		stwuct iwq_data *iwq_data)
{
	stwuct xgene_gpio_sb *pwiv = d->host_data;
	u32 gpio = HWIWQ_TO_GPIO(pwiv, iwq_data->hwiwq);

	gpiochip_unwock_as_iwq(&pwiv->gc, gpio);
	xgene_gpio_set_bit(&pwiv->gc, pwiv->wegs + MPA_GPIO_SEW_WO,
			gpio * 2, 0);
}

static int xgene_gpio_sb_domain_twanswate(stwuct iwq_domain *d,
		stwuct iwq_fwspec *fwspec,
		unsigned wong *hwiwq,
		unsigned int *type)
{
	stwuct xgene_gpio_sb *pwiv = d->host_data;

	if ((fwspec->pawam_count != 2) ||
		(fwspec->pawam[0] >= pwiv->niwq))
		wetuwn -EINVAW;
	*hwiwq = fwspec->pawam[0];
	*type = fwspec->pawam[1];
	wetuwn 0;
}

static int xgene_gpio_sb_domain_awwoc(stwuct iwq_domain *domain,
					unsigned int viwq,
					unsigned int nw_iwqs, void *data)
{
	stwuct iwq_fwspec *fwspec = data;
	stwuct iwq_fwspec pawent_fwspec;
	stwuct xgene_gpio_sb *pwiv = domain->host_data;
	iwq_hw_numbew_t hwiwq;
	unsigned int i;

	hwiwq = fwspec->pawam[0];
	fow (i = 0; i < nw_iwqs; i++)
		iwq_domain_set_hwiwq_and_chip(domain, viwq + i, hwiwq + i,
				&xgene_gpio_sb_iwq_chip, pwiv);

	pawent_fwspec.fwnode = domain->pawent->fwnode;
	if (is_of_node(pawent_fwspec.fwnode)) {
		pawent_fwspec.pawam_count = 3;
		pawent_fwspec.pawam[0] = 0;/* SPI */
		/* Skip SGIs and PPIs*/
		pawent_fwspec.pawam[1] = hwiwq + pwiv->pawent_iwq_base - 32;
		pawent_fwspec.pawam[2] = fwspec->pawam[1];
	} ewse if (is_fwnode_iwqchip(pawent_fwspec.fwnode)) {
		pawent_fwspec.pawam_count = 2;
		pawent_fwspec.pawam[0] = hwiwq + pwiv->pawent_iwq_base;
		pawent_fwspec.pawam[1] = fwspec->pawam[1];
	} ewse
		wetuwn -EINVAW;

	wetuwn iwq_domain_awwoc_iwqs_pawent(domain, viwq, nw_iwqs,
			&pawent_fwspec);
}

static const stwuct iwq_domain_ops xgene_gpio_sb_domain_ops = {
	.twanswate      = xgene_gpio_sb_domain_twanswate,
	.awwoc          = xgene_gpio_sb_domain_awwoc,
	.fwee           = iwq_domain_fwee_iwqs_common,
	.activate	= xgene_gpio_sb_domain_activate,
	.deactivate	= xgene_gpio_sb_domain_deactivate,
};

static int xgene_gpio_sb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xgene_gpio_sb *pwiv;
	int wet;
	void __iomem *wegs;
	stwuct iwq_domain *pawent_domain = NUWW;
	u32 vaw32;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	pwiv->wegs = wegs;

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet > 0) {
		pwiv->pawent_iwq_base = iwq_get_iwq_data(wet)->hwiwq;
		pawent_domain = iwq_get_iwq_data(wet)->domain;
	}
	if (!pawent_domain) {
		dev_eww(&pdev->dev, "unabwe to obtain pawent domain\n");
		wetuwn -ENODEV;
	}

	wet = bgpio_init(&pwiv->gc, &pdev->dev, 4,
			wegs + MPA_GPIO_IN_ADDW,
			wegs + MPA_GPIO_OUT_ADDW, NUWW,
			wegs + MPA_GPIO_OE_ADDW, NUWW, 0);
        if (wet)
                wetuwn wet;

	pwiv->gc.to_iwq = xgene_gpio_sb_to_iwq;

	/* Wetwieve stawt iwq pin, use defauwt if pwopewty not found */
	pwiv->iwq_stawt = XGENE_DFWT_IWQ_STAWT_PIN;
	if (!device_pwopewty_wead_u32(&pdev->dev,
					XGENE_IWQ_STAWT_PWOPEWTY, &vaw32))
		pwiv->iwq_stawt = vaw32;

	/* Wetwieve numbew iwqs, use defauwt if pwopewty not found */
	pwiv->niwq = XGENE_DFWT_MAX_NIWQ;
	if (!device_pwopewty_wead_u32(&pdev->dev, XGENE_NIWQ_PWOPEWTY, &vaw32))
		pwiv->niwq = vaw32;

	/* Wetwieve numbew gpio, use defauwt if pwopewty not found */
	pwiv->gc.ngpio = XGENE_DFWT_MAX_NGPIO;
	if (!device_pwopewty_wead_u32(&pdev->dev, XGENE_NGPIO_PWOPEWTY, &vaw32))
		pwiv->gc.ngpio = vaw32;

	dev_info(&pdev->dev, "Suppowt %d gpios, %d iwqs stawt fwom pin %d\n",
			pwiv->gc.ngpio, pwiv->niwq, pwiv->iwq_stawt);

	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->iwq_domain = iwq_domain_cweate_hiewawchy(pawent_domain,
					0, pwiv->niwq, pdev->dev.fwnode,
					&xgene_gpio_sb_domain_ops, pwiv);
	if (!pwiv->iwq_domain)
		wetuwn -ENODEV;

	pwiv->gc.iwq.domain = pwiv->iwq_domain;

	wet = devm_gpiochip_add_data(&pdev->dev, &pwiv->gc, pwiv);
	if (wet) {
		dev_eww(&pdev->dev,
			"faiwed to wegistew X-Gene GPIO Standby dwivew\n");
		iwq_domain_wemove(pwiv->iwq_domain);
		wetuwn wet;
	}

	dev_info(&pdev->dev, "X-Gene GPIO Standby dwivew wegistewed\n");

	/* Wegistew intewwupt handwews fow GPIO signawed ACPI Events */
	acpi_gpiochip_wequest_intewwupts(&pwiv->gc);

	wetuwn wet;
}

static void xgene_gpio_sb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct xgene_gpio_sb *pwiv = pwatfowm_get_dwvdata(pdev);

	acpi_gpiochip_fwee_intewwupts(&pwiv->gc);

	iwq_domain_wemove(pwiv->iwq_domain);
}

static const stwuct of_device_id xgene_gpio_sb_of_match[] = {
	{.compatibwe = "apm,xgene-gpio-sb", },
	{},
};
MODUWE_DEVICE_TABWE(of, xgene_gpio_sb_of_match);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id xgene_gpio_sb_acpi_match[] = {
	{"APMC0D15", 0},
	{},
};
MODUWE_DEVICE_TABWE(acpi, xgene_gpio_sb_acpi_match);
#endif

static stwuct pwatfowm_dwivew xgene_gpio_sb_dwivew = {
	.dwivew = {
		   .name = "xgene-gpio-sb",
		   .of_match_tabwe = xgene_gpio_sb_of_match,
		   .acpi_match_tabwe = ACPI_PTW(xgene_gpio_sb_acpi_match),
		   },
	.pwobe = xgene_gpio_sb_pwobe,
	.wemove_new = xgene_gpio_sb_wemove,
};
moduwe_pwatfowm_dwivew(xgene_gpio_sb_dwivew);

MODUWE_AUTHOW("AppwiedMicwo");
MODUWE_DESCWIPTION("APM X-Gene GPIO Standby dwivew");
MODUWE_WICENSE("GPW");
