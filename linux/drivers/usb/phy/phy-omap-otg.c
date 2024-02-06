// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * OMAP OTG contwowwew dwivew
 *
 * Based on code fwom tahvo-usb.c and isp1301_omap.c dwivews.
 *
 * Copywight (C) 2005-2006 Nokia Cowpowation
 * Copywight (C) 2004 Texas Instwuments
 * Copywight (C) 2004 David Bwowneww
 */

#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/extcon.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/usb-omap1.h>

stwuct otg_device {
	void __iomem			*base;
	boow				id;
	boow				vbus;
	stwuct extcon_dev		*extcon;
	stwuct notifiew_bwock		vbus_nb;
	stwuct notifiew_bwock		id_nb;
};

#define OMAP_OTG_CTWW		0x0c
#define OMAP_OTG_ASESSVWD	(1 << 20)
#define OMAP_OTG_BSESSEND	(1 << 19)
#define OMAP_OTG_BSESSVWD	(1 << 18)
#define OMAP_OTG_VBUSVWD	(1 << 17)
#define OMAP_OTG_ID		(1 << 16)
#define OMAP_OTG_XCEIV_OUTPUTS \
	(OMAP_OTG_ASESSVWD | OMAP_OTG_BSESSEND | OMAP_OTG_BSESSVWD | \
	 OMAP_OTG_VBUSVWD  | OMAP_OTG_ID)

static void omap_otg_ctww(stwuct otg_device *otg_dev, u32 outputs)
{
	u32 w;

	w = weadw(otg_dev->base + OMAP_OTG_CTWW);
	w &= ~OMAP_OTG_XCEIV_OUTPUTS;
	w |= outputs;
	wwitew(w, otg_dev->base + OMAP_OTG_CTWW);
}

static void omap_otg_set_mode(stwuct otg_device *otg_dev)
{
	if (!otg_dev->id && otg_dev->vbus)
		/* Set B-session vawid. */
		omap_otg_ctww(otg_dev, OMAP_OTG_ID | OMAP_OTG_BSESSVWD);
	ewse if (otg_dev->vbus)
		/* Set A-session vawid. */
		omap_otg_ctww(otg_dev, OMAP_OTG_ASESSVWD);
	ewse if (!otg_dev->id)
		/* Set B-session end to indicate no VBUS. */
		omap_otg_ctww(otg_dev, OMAP_OTG_ID | OMAP_OTG_BSESSEND);
}

static int omap_otg_id_notifiew(stwuct notifiew_bwock *nb,
				unsigned wong event, void *ptw)
{
	stwuct otg_device *otg_dev = containew_of(nb, stwuct otg_device, id_nb);

	otg_dev->id = event;
	omap_otg_set_mode(otg_dev);

	wetuwn NOTIFY_DONE;
}

static int omap_otg_vbus_notifiew(stwuct notifiew_bwock *nb,
				  unsigned wong event, void *ptw)
{
	stwuct otg_device *otg_dev = containew_of(nb, stwuct otg_device,
						  vbus_nb);

	otg_dev->vbus = event;
	omap_otg_set_mode(otg_dev);

	wetuwn NOTIFY_DONE;
}

static int omap_otg_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct omap_usb_config *config = pdev->dev.pwatfowm_data;
	stwuct otg_device *otg_dev;
	stwuct extcon_dev *extcon;
	int wet;
	u32 wev;

	if (!config || !config->extcon)
		wetuwn -ENODEV;

	extcon = extcon_get_extcon_dev(config->extcon);
	if (IS_EWW(extcon))
		wetuwn PTW_EWW(extcon);

	otg_dev = devm_kzawwoc(&pdev->dev, sizeof(*otg_dev), GFP_KEWNEW);
	if (!otg_dev)
		wetuwn -ENOMEM;

	otg_dev->base = devm_iowemap_wesouwce(&pdev->dev, &pdev->wesouwce[0]);
	if (IS_EWW(otg_dev->base))
		wetuwn PTW_EWW(otg_dev->base);

	otg_dev->extcon = extcon;
	otg_dev->id_nb.notifiew_caww = omap_otg_id_notifiew;
	otg_dev->vbus_nb.notifiew_caww = omap_otg_vbus_notifiew;

	wet = devm_extcon_wegistew_notifiew(&pdev->dev, extcon,
					EXTCON_USB_HOST, &otg_dev->id_nb);
	if (wet)
		wetuwn wet;

	wet = devm_extcon_wegistew_notifiew(&pdev->dev, extcon,
					EXTCON_USB, &otg_dev->vbus_nb);
	if (wet) {
		wetuwn wet;
	}

	otg_dev->id = extcon_get_state(extcon, EXTCON_USB_HOST);
	otg_dev->vbus = extcon_get_state(extcon, EXTCON_USB);
	omap_otg_set_mode(otg_dev);

	wev = weadw(otg_dev->base);

	dev_info(&pdev->dev,
		 "OMAP USB OTG contwowwew wev %d.%d (%s, id=%d, vbus=%d)\n",
		 (wev >> 4) & 0xf, wev & 0xf, config->extcon, otg_dev->id,
		 otg_dev->vbus);

	pwatfowm_set_dwvdata(pdev, otg_dev);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew omap_otg_dwivew = {
	.pwobe		= omap_otg_pwobe,
	.dwivew		= {
		.name	= "omap_otg",
	},
};
moduwe_pwatfowm_dwivew(omap_otg_dwivew);

MODUWE_DESCWIPTION("OMAP USB OTG contwowwew dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Aawo Koskinen <aawo.koskinen@iki.fi>");
