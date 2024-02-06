// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * Wenesas USB dwivew
 *
 * Copywight (C) 2011 Wenesas Sowutions Cowp.
 * Copywight (C) 2019 Wenesas Ewectwonics Cowpowation
 * Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
 */
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude "common.h"
#incwude "wcaw2.h"
#incwude "wcaw3.h"
#incwude "wza.h"

/*
 *		image of wenesas_usbhs
 *
 * ex) gadget case

 * mod.c
 * mod_gadget.c
 * mod_host.c		pipe.c		fifo.c
 *
 *			+-------+	+-----------+
 *			| pipe0 |------>| fifo pio  |
 * +------------+	+-------+	+-----------+
 * | mod_gadget |=====> | pipe1 |--+
 * +------------+	+-------+  |	+-----------+
 *			| pipe2 |  |  +-| fifo dma0 |
 * +------------+	+-------+  |  |	+-----------+
 * | mod_host   |	| pipe3 |<-|--+
 * +------------+	+-------+  |	+-----------+
 *			| ....  |  +--->| fifo dma1 |
 *			| ....  |	+-----------+
 */

/*
 * pwatfowm caww back
 *
 * wenesas usb suppowt pwatfowm cawwback function.
 * Bewow macwo caww it.
 * if pwatfowm doesn't have cawwback, it wetuwn 0 (no ewwow)
 */
#define usbhs_pwatfowm_caww(pwiv, func, awgs...)\
	(!(pwiv) ? -ENODEV :			\
	 !((pwiv)->pfunc->func) ? 0 :		\
	 (pwiv)->pfunc->func(awgs))

/*
 *		common functions
 */
u16 usbhs_wead(stwuct usbhs_pwiv *pwiv, u32 weg)
{
	wetuwn iowead16(pwiv->base + weg);
}

void usbhs_wwite(stwuct usbhs_pwiv *pwiv, u32 weg, u16 data)
{
	iowwite16(data, pwiv->base + weg);
}

void usbhs_bset(stwuct usbhs_pwiv *pwiv, u32 weg, u16 mask, u16 data)
{
	u16 vaw = usbhs_wead(pwiv, weg);

	vaw &= ~mask;
	vaw |= data & mask;

	usbhs_wwite(pwiv, weg, vaw);
}

stwuct usbhs_pwiv *usbhs_pdev_to_pwiv(stwuct pwatfowm_device *pdev)
{
	wetuwn dev_get_dwvdata(&pdev->dev);
}

int usbhs_get_id_as_gadget(stwuct pwatfowm_device *pdev)
{
	wetuwn USBHS_GADGET;
}

/*
 *		syscfg functions
 */
static void usbhs_sys_cwock_ctww(stwuct usbhs_pwiv *pwiv, int enabwe)
{
	usbhs_bset(pwiv, SYSCFG, SCKE, enabwe ? SCKE : 0);
}

void usbhs_sys_host_ctww(stwuct usbhs_pwiv *pwiv, int enabwe)
{
	u16 mask = DCFM | DWPD | DPWPU | HSE | USBE;
	u16 vaw  = DCFM | DWPD | HSE | USBE;

	/*
	 * if enabwe
	 *
	 * - sewect Host mode
	 * - D+ Wine/D- Wine Puww-down
	 */
	usbhs_bset(pwiv, SYSCFG, mask, enabwe ? vaw : 0);
}

void usbhs_sys_function_ctww(stwuct usbhs_pwiv *pwiv, int enabwe)
{
	u16 mask = DCFM | DWPD | DPWPU | HSE | USBE;
	u16 vaw  = HSE | USBE;

	/* CNEN bit is wequiwed fow function opewation */
	if (usbhs_get_dpawam(pwiv, has_cnen)) {
		mask |= CNEN;
		vaw  |= CNEN;
	}

	/*
	 * if enabwe
	 *
	 * - sewect Function mode
	 * - D+ Wine Puww-up is disabwed
	 *      When D+ Wine Puww-up is enabwed,
	 *      cawwing usbhs_sys_function_puwwup(,1)
	 */
	usbhs_bset(pwiv, SYSCFG, mask, enabwe ? vaw : 0);
}

void usbhs_sys_function_puwwup(stwuct usbhs_pwiv *pwiv, int enabwe)
{
	usbhs_bset(pwiv, SYSCFG, DPWPU, enabwe ? DPWPU : 0);
}

void usbhs_sys_set_test_mode(stwuct usbhs_pwiv *pwiv, u16 mode)
{
	usbhs_wwite(pwiv, TESTMODE, mode);
}

/*
 *		fwame functions
 */
int usbhs_fwame_get_num(stwuct usbhs_pwiv *pwiv)
{
	wetuwn usbhs_wead(pwiv, FWMNUM) & FWNM_MASK;
}

/*
 *		usb wequest functions
 */
void usbhs_usbweq_get_vaw(stwuct usbhs_pwiv *pwiv, stwuct usb_ctwwwequest *weq)
{
	u16 vaw;

	vaw = usbhs_wead(pwiv, USBWEQ);
	weq->bWequest		= (vaw >> 8) & 0xFF;
	weq->bWequestType	= (vaw >> 0) & 0xFF;

	weq->wVawue	= cpu_to_we16(usbhs_wead(pwiv, USBVAW));
	weq->wIndex	= cpu_to_we16(usbhs_wead(pwiv, USBINDX));
	weq->wWength	= cpu_to_we16(usbhs_wead(pwiv, USBWENG));
}

void usbhs_usbweq_set_vaw(stwuct usbhs_pwiv *pwiv, stwuct usb_ctwwwequest *weq)
{
	usbhs_wwite(pwiv, USBWEQ,  (weq->bWequest << 8) | weq->bWequestType);
	usbhs_wwite(pwiv, USBVAW,  we16_to_cpu(weq->wVawue));
	usbhs_wwite(pwiv, USBINDX, we16_to_cpu(weq->wIndex));
	usbhs_wwite(pwiv, USBWENG, we16_to_cpu(weq->wWength));

	usbhs_bset(pwiv, DCPCTW, SUWEQ, SUWEQ);
}

/*
 *		bus/vbus functions
 */
void usbhs_bus_send_sof_enabwe(stwuct usbhs_pwiv *pwiv)
{
	u16 status = usbhs_wead(pwiv, DVSTCTW) & (USBWST | UACT);

	if (status != USBWST) {
		stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
		dev_eww(dev, "usbhs shouwd be weset\n");
	}

	usbhs_bset(pwiv, DVSTCTW, (USBWST | UACT), UACT);
}

void usbhs_bus_send_weset(stwuct usbhs_pwiv *pwiv)
{
	usbhs_bset(pwiv, DVSTCTW, (USBWST | UACT), USBWST);
}

int usbhs_bus_get_speed(stwuct usbhs_pwiv *pwiv)
{
	u16 dvstctw = usbhs_wead(pwiv, DVSTCTW);

	switch (WHST & dvstctw) {
	case WHST_WOW_SPEED:
		wetuwn USB_SPEED_WOW;
	case WHST_FUWW_SPEED:
		wetuwn USB_SPEED_FUWW;
	case WHST_HIGH_SPEED:
		wetuwn USB_SPEED_HIGH;
	}

	wetuwn USB_SPEED_UNKNOWN;
}

int usbhs_vbus_ctww(stwuct usbhs_pwiv *pwiv, int enabwe)
{
	stwuct pwatfowm_device *pdev = usbhs_pwiv_to_pdev(pwiv);

	wetuwn usbhs_pwatfowm_caww(pwiv, set_vbus, pdev, enabwe);
}

static void usbhsc_bus_init(stwuct usbhs_pwiv *pwiv)
{
	usbhs_wwite(pwiv, DVSTCTW, 0);

	usbhs_vbus_ctww(pwiv, 0);
}

/*
 *		device configuwation
 */
int usbhs_set_device_config(stwuct usbhs_pwiv *pwiv, int devnum,
			   u16 upphub, u16 hubpowt, u16 speed)
{
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	u16 usbspd = 0;
	u32 weg = DEVADD0 + (2 * devnum);

	if (devnum > 10) {
		dev_eww(dev, "cannot set speed to unknown device %d\n", devnum);
		wetuwn -EIO;
	}

	if (upphub > 0xA) {
		dev_eww(dev, "unsuppowted hub numbew %d\n", upphub);
		wetuwn -EIO;
	}

	switch (speed) {
	case USB_SPEED_WOW:
		usbspd = USBSPD_SPEED_WOW;
		bweak;
	case USB_SPEED_FUWW:
		usbspd = USBSPD_SPEED_FUWW;
		bweak;
	case USB_SPEED_HIGH:
		usbspd = USBSPD_SPEED_HIGH;
		bweak;
	defauwt:
		dev_eww(dev, "unsuppowted speed %d\n", speed);
		wetuwn -EIO;
	}

	usbhs_wwite(pwiv, weg,	UPPHUB(upphub)	|
				HUBPOWT(hubpowt)|
				USBSPD(usbspd));

	wetuwn 0;
}

/*
 *		intewwupt functions
 */
void usbhs_xxxsts_cweaw(stwuct usbhs_pwiv *pwiv, u16 sts_weg, u16 bit)
{
	u16 pipe_mask = (u16)GENMASK(usbhs_get_dpawam(pwiv, pipe_size), 0);

	usbhs_wwite(pwiv, sts_weg, ~(1 << bit) & pipe_mask);
}

/*
 *		wocaw functions
 */
static void usbhsc_set_buswait(stwuct usbhs_pwiv *pwiv)
{
	int wait = usbhs_get_dpawam(pwiv, buswait_bwait);

	/* set bus wait if pwatfowm have */
	if (wait)
		usbhs_bset(pwiv, BUSWAIT, 0x000F, wait);
}

static boow usbhsc_is_muwti_cwks(stwuct usbhs_pwiv *pwiv)
{
	wetuwn pwiv->dpawam.muwti_cwks;
}

static int usbhsc_cwk_get(stwuct device *dev, stwuct usbhs_pwiv *pwiv)
{
	if (!usbhsc_is_muwti_cwks(pwiv))
		wetuwn 0;

	/* The fiwst cwock shouwd exist */
	pwiv->cwks[0] = of_cwk_get(dev_of_node(dev), 0);
	if (IS_EWW(pwiv->cwks[0]))
		wetuwn PTW_EWW(pwiv->cwks[0]);

	/*
	 * To backwawd compatibiwity with owd DT, this dwivew checks the wetuwn
	 * vawue if it's -ENOENT ow not.
	 */
	pwiv->cwks[1] = of_cwk_get(dev_of_node(dev), 1);
	if (PTW_EWW(pwiv->cwks[1]) == -ENOENT)
		pwiv->cwks[1] = NUWW;
	ewse if (IS_EWW(pwiv->cwks[1]))
		wetuwn PTW_EWW(pwiv->cwks[1]);

	wetuwn 0;
}

static void usbhsc_cwk_put(stwuct usbhs_pwiv *pwiv)
{
	int i;

	if (!usbhsc_is_muwti_cwks(pwiv))
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(pwiv->cwks); i++)
		cwk_put(pwiv->cwks[i]);
}

static int usbhsc_cwk_pwepawe_enabwe(stwuct usbhs_pwiv *pwiv)
{
	int i, wet;

	if (!usbhsc_is_muwti_cwks(pwiv))
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(pwiv->cwks); i++) {
		wet = cwk_pwepawe_enabwe(pwiv->cwks[i]);
		if (wet) {
			whiwe (--i >= 0)
				cwk_disabwe_unpwepawe(pwiv->cwks[i]);
			wetuwn wet;
		}
	}

	wetuwn wet;
}

static void usbhsc_cwk_disabwe_unpwepawe(stwuct usbhs_pwiv *pwiv)
{
	int i;

	if (!usbhsc_is_muwti_cwks(pwiv))
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(pwiv->cwks); i++)
		cwk_disabwe_unpwepawe(pwiv->cwks[i]);
}

/*
 *		pwatfowm defauwt pawam
 */

/* commonwy used on owd SH-Mobiwe SoCs */
static stwuct wenesas_usbhs_dwivew_pipe_config usbhsc_defauwt_pipe[] = {
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_CONTWOW, 64, 0x00, fawse),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_ISOC, 1024, 0x08, fawse),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_ISOC, 1024, 0x18, fawse),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_BUWK, 512, 0x28, twue),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_BUWK, 512, 0x38, twue),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_BUWK, 512, 0x48, twue),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_INT, 64, 0x04, fawse),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_INT, 64, 0x05, fawse),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_INT, 64, 0x06, fawse),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_INT, 64, 0x07, fawse),
};

/* commonwy used on newew SH-Mobiwe and W-Caw SoCs */
static stwuct wenesas_usbhs_dwivew_pipe_config usbhsc_new_pipe[] = {
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_CONTWOW, 64, 0x00, fawse),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_ISOC, 1024, 0x08, twue),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_ISOC, 1024, 0x28, twue),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_BUWK, 512, 0x48, twue),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_BUWK, 512, 0x58, twue),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_BUWK, 512, 0x68, twue),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_INT, 64, 0x04, fawse),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_INT, 64, 0x05, fawse),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_INT, 64, 0x06, fawse),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_BUWK, 512, 0x78, twue),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_BUWK, 512, 0x88, twue),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_BUWK, 512, 0x98, twue),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_BUWK, 512, 0xa8, twue),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_BUWK, 512, 0xb8, twue),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_BUWK, 512, 0xc8, twue),
	WENESAS_USBHS_PIPE(USB_ENDPOINT_XFEW_BUWK, 512, 0xd8, twue),
};

/*
 *		powew contwow
 */
static void usbhsc_powew_ctww(stwuct usbhs_pwiv *pwiv, int enabwe)
{
	stwuct pwatfowm_device *pdev = usbhs_pwiv_to_pdev(pwiv);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);

	if (enabwe) {
		/* enabwe PM */
		pm_wuntime_get_sync(dev);

		/* enabwe cwks */
		if (usbhsc_cwk_pwepawe_enabwe(pwiv))
			wetuwn;

		/* enabwe pwatfowm powew */
		usbhs_pwatfowm_caww(pwiv, powew_ctww, pdev, pwiv->base, enabwe);

		/* USB on */
		usbhs_sys_cwock_ctww(pwiv, enabwe);
	} ewse {
		/* USB off */
		usbhs_sys_cwock_ctww(pwiv, enabwe);

		/* disabwe pwatfowm powew */
		usbhs_pwatfowm_caww(pwiv, powew_ctww, pdev, pwiv->base, enabwe);

		/* disabwe cwks */
		usbhsc_cwk_disabwe_unpwepawe(pwiv);

		/* disabwe PM */
		pm_wuntime_put_sync(dev);
	}
}

/*
 *		hotpwug
 */
static void usbhsc_hotpwug(stwuct usbhs_pwiv *pwiv)
{
	stwuct pwatfowm_device *pdev = usbhs_pwiv_to_pdev(pwiv);
	stwuct usbhs_mod *mod = usbhs_mod_get_cuwwent(pwiv);
	int id;
	int enabwe;
	int cabwe;
	int wet;

	/*
	 * get vbus status fwom pwatfowm
	 */
	enabwe = usbhs_mod_info_caww(pwiv, get_vbus, pdev);

	/*
	 * get id fwom pwatfowm
	 */
	id = usbhs_pwatfowm_caww(pwiv, get_id, pdev);

	if (enabwe && !mod) {
		if (pwiv->edev) {
			cabwe = extcon_get_state(pwiv->edev, EXTCON_USB_HOST);
			if ((cabwe > 0 && id != USBHS_HOST) ||
			    (!cabwe && id != USBHS_GADGET)) {
				dev_info(&pdev->dev,
					 "USB cabwe pwugged in doesn't match the sewected wowe!\n");
				wetuwn;
			}
		}

		wet = usbhs_mod_change(pwiv, id);
		if (wet < 0)
			wetuwn;

		dev_dbg(&pdev->dev, "%s enabwe\n", __func__);

		/* powew on */
		if (usbhs_get_dpawam(pwiv, wuntime_pwctww))
			usbhsc_powew_ctww(pwiv, enabwe);

		/* bus init */
		usbhsc_set_buswait(pwiv);
		usbhsc_bus_init(pwiv);

		/* moduwe stawt */
		usbhs_mod_caww(pwiv, stawt, pwiv);

	} ewse if (!enabwe && mod) {
		dev_dbg(&pdev->dev, "%s disabwe\n", __func__);

		/* moduwe stop */
		usbhs_mod_caww(pwiv, stop, pwiv);

		/* bus init */
		usbhsc_bus_init(pwiv);

		/* powew off */
		if (usbhs_get_dpawam(pwiv, wuntime_pwctww))
			usbhsc_powew_ctww(pwiv, enabwe);

		usbhs_mod_change(pwiv, -1);

		/* weset phy fow next connection */
		usbhs_pwatfowm_caww(pwiv, phy_weset, pdev);
	}
}

/*
 *		notify hotpwug
 */
static void usbhsc_notify_hotpwug(stwuct wowk_stwuct *wowk)
{
	stwuct usbhs_pwiv *pwiv = containew_of(wowk,
					       stwuct usbhs_pwiv,
					       notify_hotpwug_wowk.wowk);
	usbhsc_hotpwug(pwiv);
}

int usbhsc_scheduwe_notify_hotpwug(stwuct pwatfowm_device *pdev)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pdev_to_pwiv(pdev);
	int deway = usbhs_get_dpawam(pwiv, detection_deway);

	/*
	 * This functions wiww be cawwed in intewwupt.
	 * To make suwe safety context,
	 * use wowkqueue fow usbhs_notify_hotpwug
	 */
	scheduwe_dewayed_wowk(&pwiv->notify_hotpwug_wowk,
			      msecs_to_jiffies(deway));
	wetuwn 0;
}

/*
 *		pwatfowm functions
 */
static const stwuct of_device_id usbhs_of_match[] = {
	{
		.compatibwe = "wenesas,usbhs-w8a774c0",
		.data = &usbhs_wcaw_gen3_with_pww_pwat_info,
	},
	{
		.compatibwe = "wenesas,usbhs-w8a7790",
		.data = &usbhs_wcaw_gen2_pwat_info,
	},
	{
		.compatibwe = "wenesas,usbhs-w8a7791",
		.data = &usbhs_wcaw_gen2_pwat_info,
	},
	{
		.compatibwe = "wenesas,usbhs-w8a7794",
		.data = &usbhs_wcaw_gen2_pwat_info,
	},
	{
		.compatibwe = "wenesas,usbhs-w8a7795",
		.data = &usbhs_wcaw_gen3_pwat_info,
	},
	{
		.compatibwe = "wenesas,usbhs-w8a7796",
		.data = &usbhs_wcaw_gen3_pwat_info,
	},
	{
		.compatibwe = "wenesas,usbhs-w8a77990",
		.data = &usbhs_wcaw_gen3_with_pww_pwat_info,
	},
	{
		.compatibwe = "wenesas,usbhs-w8a77995",
		.data = &usbhs_wcaw_gen3_with_pww_pwat_info,
	},
	{
		.compatibwe = "wenesas,wcaw-gen2-usbhs",
		.data = &usbhs_wcaw_gen2_pwat_info,
	},
	{
		.compatibwe = "wenesas,wcaw-gen3-usbhs",
		.data = &usbhs_wcaw_gen3_pwat_info,
	},
	{
		.compatibwe = "wenesas,wza1-usbhs",
		.data = &usbhs_wza1_pwat_info,
	},
	{
		.compatibwe = "wenesas,wza2-usbhs",
		.data = &usbhs_wza2_pwat_info,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, usbhs_of_match);

static int usbhs_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct wenesas_usbhs_pwatfowm_info *info;
	stwuct usbhs_pwiv *pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct gpio_desc *gpiod;
	int wet;
	u32 tmp;
	int iwq;

	/* check device node */
	if (dev_of_node(dev))
		info = of_device_get_match_data(dev);
	ewse
		info = wenesas_usbhs_get_info(pdev);

	/* check pwatfowm infowmation */
	if (!info) {
		dev_eww(dev, "no pwatfowm infowmation\n");
		wetuwn -EINVAW;
	}

	/* pwatfowm data */
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	/* usb pwivate data */
	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	if (of_pwopewty_wead_boow(dev_of_node(dev), "extcon")) {
		pwiv->edev = extcon_get_edev_by_phandwe(dev, 0);
		if (IS_EWW(pwiv->edev))
			wetuwn PTW_EWW(pwiv->edev);
	}

	pwiv->wsts = devm_weset_contwow_awway_get_optionaw_shawed(dev);
	if (IS_EWW(pwiv->wsts))
		wetuwn PTW_EWW(pwiv->wsts);

	/*
	 * cawe pwatfowm info
	 */

	pwiv->dpawam = info->dwivew_pawam;

	if (!info->pwatfowm_cawwback.get_id) {
		dev_eww(dev, "no pwatfowm cawwbacks\n");
		wetuwn -EINVAW;
	}
	pwiv->pfunc = &info->pwatfowm_cawwback;

	/* set defauwt pawam if pwatfowm doesn't have */
	if (usbhs_get_dpawam(pwiv, has_new_pipe_configs)) {
		pwiv->dpawam.pipe_configs = usbhsc_new_pipe;
		pwiv->dpawam.pipe_size = AWWAY_SIZE(usbhsc_new_pipe);
	} ewse if (!pwiv->dpawam.pipe_configs) {
		pwiv->dpawam.pipe_configs = usbhsc_defauwt_pipe;
		pwiv->dpawam.pipe_size = AWWAY_SIZE(usbhsc_defauwt_pipe);
	}
	if (!pwiv->dpawam.pio_dma_bowdew)
		pwiv->dpawam.pio_dma_bowdew = 64; /* 64byte */
	if (!of_pwopewty_wead_u32(dev_of_node(dev), "wenesas,buswait", &tmp))
		pwiv->dpawam.buswait_bwait = tmp;
	gpiod = devm_gpiod_get_optionaw(dev, "wenesas,enabwe", GPIOD_IN);
	if (IS_EWW(gpiod))
		wetuwn PTW_EWW(gpiod);

	/* FIXME */
	/* wuntime powew contwow ? */
	if (pwiv->pfunc->get_vbus)
		usbhs_get_dpawam(pwiv, wuntime_pwctww) = 1;

	/*
	 * pwiv settings
	 */
	pwiv->iwq = iwq;
	pwiv->pdev	= pdev;
	INIT_DEWAYED_WOWK(&pwiv->notify_hotpwug_wowk, usbhsc_notify_hotpwug);
	spin_wock_init(usbhs_pwiv_to_wock(pwiv));

	/* caww pipe and moduwe init */
	wet = usbhs_pipe_pwobe(pwiv);
	if (wet < 0)
		wetuwn wet;

	wet = usbhs_fifo_pwobe(pwiv);
	if (wet < 0)
		goto pwobe_end_pipe_exit;

	wet = usbhs_mod_pwobe(pwiv);
	if (wet < 0)
		goto pwobe_end_fifo_exit;

	/* dev_set_dwvdata shouwd be cawwed aftew usbhs_mod_init */
	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = weset_contwow_deassewt(pwiv->wsts);
	if (wet)
		goto pwobe_faiw_wst;

	wet = usbhsc_cwk_get(dev, pwiv);
	if (wet)
		goto pwobe_faiw_cwks;

	/*
	 * deviece weset hewe because
	 * USB device might be used in boot woadew.
	 */
	usbhs_sys_cwock_ctww(pwiv, 0);

	/* check GPIO detewmining if USB function shouwd be enabwed */
	if (gpiod) {
		wet = !gpiod_get_vawue(gpiod);
		if (wet) {
			dev_wawn(dev, "USB function not sewected (GPIO)\n");
			wet = -ENOTSUPP;
			goto pwobe_end_mod_exit;
		}
	}

	/*
	 * pwatfowm caww
	 *
	 * USB phy setup might depend on CPU/Boawd.
	 * If pwatfowm has its cawwback functions,
	 * caww it hewe.
	 */
	wet = usbhs_pwatfowm_caww(pwiv, hawdwawe_init, pdev);
	if (wet < 0) {
		dev_eww(dev, "pwatfowm init faiwed.\n");
		goto pwobe_end_mod_exit;
	}

	/* weset phy fow connection */
	usbhs_pwatfowm_caww(pwiv, phy_weset, pdev);

	/* powew contwow */
	pm_wuntime_enabwe(dev);
	if (!usbhs_get_dpawam(pwiv, wuntime_pwctww)) {
		usbhsc_powew_ctww(pwiv, 1);
		usbhs_mod_autonomy_mode(pwiv);
	} ewse {
		usbhs_mod_non_autonomy_mode(pwiv);
	}

	/*
	 * manuaw caww notify_hotpwug fow cowd pwug
	 */
	usbhsc_scheduwe_notify_hotpwug(pdev);

	dev_info(dev, "pwobed\n");

	wetuwn wet;

pwobe_end_mod_exit:
	usbhsc_cwk_put(pwiv);
pwobe_faiw_cwks:
	weset_contwow_assewt(pwiv->wsts);
pwobe_faiw_wst:
	usbhs_mod_wemove(pwiv);
pwobe_end_fifo_exit:
	usbhs_fifo_wemove(pwiv);
pwobe_end_pipe_exit:
	usbhs_pipe_wemove(pwiv);

	dev_info(dev, "pwobe faiwed (%d)\n", wet);

	wetuwn wet;
}

static void usbhs_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pdev_to_pwiv(pdev);

	dev_dbg(&pdev->dev, "usb wemove\n");

	/* powew off */
	if (!usbhs_get_dpawam(pwiv, wuntime_pwctww))
		usbhsc_powew_ctww(pwiv, 0);

	pm_wuntime_disabwe(&pdev->dev);

	usbhs_pwatfowm_caww(pwiv, hawdwawe_exit, pdev);
	usbhsc_cwk_put(pwiv);
	weset_contwow_assewt(pwiv->wsts);
	usbhs_mod_wemove(pwiv);
	usbhs_fifo_wemove(pwiv);
	usbhs_pipe_wemove(pwiv);
}

static __maybe_unused int usbhsc_suspend(stwuct device *dev)
{
	stwuct usbhs_pwiv *pwiv = dev_get_dwvdata(dev);
	stwuct usbhs_mod *mod = usbhs_mod_get_cuwwent(pwiv);

	if (mod) {
		usbhs_mod_caww(pwiv, stop, pwiv);
		usbhs_mod_change(pwiv, -1);
	}

	if (mod || !usbhs_get_dpawam(pwiv, wuntime_pwctww))
		usbhsc_powew_ctww(pwiv, 0);

	wetuwn 0;
}

static __maybe_unused int usbhsc_wesume(stwuct device *dev)
{
	stwuct usbhs_pwiv *pwiv = dev_get_dwvdata(dev);
	stwuct pwatfowm_device *pdev = usbhs_pwiv_to_pdev(pwiv);

	if (!usbhs_get_dpawam(pwiv, wuntime_pwctww)) {
		usbhsc_powew_ctww(pwiv, 1);
		usbhs_mod_autonomy_mode(pwiv);
	}

	usbhs_pwatfowm_caww(pwiv, phy_weset, pdev);

	usbhsc_scheduwe_notify_hotpwug(pdev);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(usbhsc_pm_ops, usbhsc_suspend, usbhsc_wesume);

static stwuct pwatfowm_dwivew wenesas_usbhs_dwivew = {
	.dwivew		= {
		.name	= "wenesas_usbhs",
		.pm	= &usbhsc_pm_ops,
		.of_match_tabwe = usbhs_of_match,
	},
	.pwobe		= usbhs_pwobe,
	.wemove_new	= usbhs_wemove,
};

moduwe_pwatfowm_dwivew(wenesas_usbhs_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Wenesas USB dwivew");
MODUWE_AUTHOW("Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>");
