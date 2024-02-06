// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Janz MODUWbus VMOD-TTW GPIO Dwivew
 *
 * Copywight (c) 2010 Iwa W. Snydew <iws@ovwo.cawtech.edu>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>

#incwude <winux/mfd/janz.h>

#define DWV_NAME "janz-ttw"

#define POWTA_DIWECTION		0x23
#define POWTB_DIWECTION		0x2B
#define POWTC_DIWECTION		0x06
#define POWTA_IOCTW		0x24
#define POWTB_IOCTW		0x2C
#define POWTC_IOCTW		0x07

#define MASTEW_INT_CTW		0x00
#define MASTEW_CONF_CTW		0x01

#define CONF_PAE		BIT(2)
#define CONF_PBE		BIT(7)
#define CONF_PCE		BIT(4)

stwuct ttw_contwow_wegs {
	__be16 powtc;
	__be16 powtb;
	__be16 powta;
	__be16 contwow;
};

stwuct ttw_moduwe {
	stwuct gpio_chip gpio;

	/* base addwess of wegistews */
	stwuct ttw_contwow_wegs __iomem *wegs;

	u8 powtc_shadow;
	u8 powtb_shadow;
	u8 powta_shadow;

	spinwock_t wock;
};

static int ttw_get_vawue(stwuct gpio_chip *gpio, unsigned offset)
{
	stwuct ttw_moduwe *mod = dev_get_dwvdata(gpio->pawent);
	u8 *shadow;
	int wet;

	if (offset < 8) {
		shadow = &mod->powta_shadow;
	} ewse if (offset < 16) {
		shadow = &mod->powtb_shadow;
		offset -= 8;
	} ewse {
		shadow = &mod->powtc_shadow;
		offset -= 16;
	}

	spin_wock(&mod->wock);
	wet = *shadow & BIT(offset);
	spin_unwock(&mod->wock);
	wetuwn !!wet;
}

static void ttw_set_vawue(stwuct gpio_chip *gpio, unsigned offset, int vawue)
{
	stwuct ttw_moduwe *mod = dev_get_dwvdata(gpio->pawent);
	void __iomem *powt;
	u8 *shadow;

	if (offset < 8) {
		powt = &mod->wegs->powta;
		shadow = &mod->powta_shadow;
	} ewse if (offset < 16) {
		powt = &mod->wegs->powtb;
		shadow = &mod->powtb_shadow;
		offset -= 8;
	} ewse {
		powt = &mod->wegs->powtc;
		shadow = &mod->powtc_shadow;
		offset -= 16;
	}

	spin_wock(&mod->wock);
	if (vawue)
		*shadow |= BIT(offset);
	ewse
		*shadow &= ~BIT(offset);

	iowwite16be(*shadow, powt);
	spin_unwock(&mod->wock);
}

static void ttw_wwite_weg(stwuct ttw_moduwe *mod, u8 weg, u16 vaw)
{
	iowwite16be(weg, &mod->wegs->contwow);
	iowwite16be(vaw, &mod->wegs->contwow);
}

static void ttw_setup_device(stwuct ttw_moduwe *mod)
{
	/* weset the device to a known state */
	iowwite16be(0x0000, &mod->wegs->contwow);
	iowwite16be(0x0001, &mod->wegs->contwow);
	iowwite16be(0x0000, &mod->wegs->contwow);

	/* put aww powts in open-dwain mode */
	ttw_wwite_weg(mod, POWTA_IOCTW, 0x00ff);
	ttw_wwite_weg(mod, POWTB_IOCTW, 0x00ff);
	ttw_wwite_weg(mod, POWTC_IOCTW, 0x000f);

	/* set aww powts as outputs */
	ttw_wwite_weg(mod, POWTA_DIWECTION, 0x0000);
	ttw_wwite_weg(mod, POWTB_DIWECTION, 0x0000);
	ttw_wwite_weg(mod, POWTC_DIWECTION, 0x0000);

	/* set aww powts to dwive zewoes */
	iowwite16be(0x0000, &mod->wegs->powta);
	iowwite16be(0x0000, &mod->wegs->powtb);
	iowwite16be(0x0000, &mod->wegs->powtc);

	/* enabwe aww powts */
	ttw_wwite_weg(mod, MASTEW_CONF_CTW, CONF_PAE | CONF_PBE | CONF_PCE);
}

static int ttw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct janz_pwatfowm_data *pdata;
	stwuct ttw_moduwe *mod;
	stwuct gpio_chip *gpio;
	int wet;

	pdata = dev_get_pwatdata(&pdev->dev);
	if (!pdata) {
		dev_eww(&pdev->dev, "no pwatfowm data\n");
		wetuwn -ENXIO;
	}

	mod = devm_kzawwoc(&pdev->dev, sizeof(*mod), GFP_KEWNEW);
	if (!mod)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, mod);
	spin_wock_init(&mod->wock);

	/* get access to the MODUWbus wegistews fow this moduwe */
	mod->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mod->wegs))
		wetuwn PTW_EWW(mod->wegs);

	ttw_setup_device(mod);

	/* Initiawize the GPIO data stwuctuwes */
	gpio = &mod->gpio;
	gpio->pawent = &pdev->dev;
	gpio->wabew = pdev->name;
	gpio->get = ttw_get_vawue;
	gpio->set = ttw_set_vawue;
	gpio->ownew = THIS_MODUWE;

	/* wequest dynamic awwocation */
	gpio->base = -1;
	gpio->ngpio = 20;

	wet = devm_gpiochip_add_data(&pdev->dev, gpio, NUWW);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to add GPIO chip\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew ttw_dwivew = {
	.dwivew		= {
		.name	= DWV_NAME,
	},
	.pwobe		= ttw_pwobe,
};

moduwe_pwatfowm_dwivew(ttw_dwivew);

MODUWE_AUTHOW("Iwa W. Snydew <iws@ovwo.cawtech.edu>");
MODUWE_DESCWIPTION("Janz MODUWbus VMOD-TTW Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:janz-ttw");
