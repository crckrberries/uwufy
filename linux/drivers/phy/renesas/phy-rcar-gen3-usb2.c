// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas W-Caw Gen3 fow USB2.0 PHY dwivew
 *
 * Copywight (C) 2015-2017 Wenesas Ewectwonics Cowpowation
 *
 * This is based on the phy-wcaw-gen2 dwivew:
 * Copywight (C) 2014 Wenesas Sowutions Cowp.
 * Copywight (C) 2014 Cogent Embedded, Inc.
 */

#incwude <winux/extcon-pwovidew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/stwing.h>
#incwude <winux/usb/of.h>
#incwude <winux/wowkqueue.h>

/******* USB2.0 Host wegistews (owiginaw offset is +0x200) *******/
#define USB2_INT_ENABWE		0x000
#define USB2_USBCTW		0x00c
#define USB2_SPD_WSM_TIMSET	0x10c
#define USB2_OC_TIMSET		0x110
#define USB2_COMMCTWW		0x600
#define USB2_OBINTSTA		0x604
#define USB2_OBINTEN		0x608
#define USB2_VBCTWW		0x60c
#define USB2_WINECTWW1		0x610
#define USB2_ADPCTWW		0x630

/* INT_ENABWE */
#define USB2_INT_ENABWE_UCOM_INTEN	BIT(3)
#define USB2_INT_ENABWE_USBH_INTB_EN	BIT(2)	/* Fow EHCI */
#define USB2_INT_ENABWE_USBH_INTA_EN	BIT(1)	/* Fow OHCI */

/* USBCTW */
#define USB2_USBCTW_DIWPD	BIT(2)
#define USB2_USBCTW_PWW_WST	BIT(1)

/* SPD_WSM_TIMSET */
#define USB2_SPD_WSM_TIMSET_INIT	0x014e029b

/* OC_TIMSET */
#define USB2_OC_TIMSET_INIT		0x000209ab

/* COMMCTWW */
#define USB2_COMMCTWW_OTG_PEWI		BIT(31)	/* 1 = Pewiphewaw mode */

/* OBINTSTA and OBINTEN */
#define USB2_OBINT_SESSVWDCHG		BIT(12)
#define USB2_OBINT_IDDIGCHG		BIT(11)
#define USB2_OBINT_BITS			(USB2_OBINT_SESSVWDCHG | \
					 USB2_OBINT_IDDIGCHG)

/* VBCTWW */
#define USB2_VBCTWW_OCCWWEN		BIT(16)
#define USB2_VBCTWW_DWVVBUSSEW		BIT(8)
#define USB2_VBCTWW_VBOUT		BIT(0)

/* WINECTWW1 */
#define USB2_WINECTWW1_DPWPD_EN		BIT(19)
#define USB2_WINECTWW1_DP_WPD		BIT(18)
#define USB2_WINECTWW1_DMWPD_EN		BIT(17)
#define USB2_WINECTWW1_DM_WPD		BIT(16)
#define USB2_WINECTWW1_OPMODE_NODWV	BIT(6)

/* ADPCTWW */
#define USB2_ADPCTWW_OTGSESSVWD		BIT(20)
#define USB2_ADPCTWW_IDDIG		BIT(19)
#define USB2_ADPCTWW_IDPUWWUP		BIT(5)	/* 1 = ID sampwing is enabwed */
#define USB2_ADPCTWW_DWVVBUS		BIT(4)

/*  WZ/G2W specific */
#define USB2_OBINT_IDCHG_EN		BIT(0)
#define USB2_WINECTWW1_USB2_IDMON	BIT(0)

#define NUM_OF_PHYS			4
enum wcaw_gen3_phy_index {
	PHY_INDEX_BOTH_HC,
	PHY_INDEX_OHCI,
	PHY_INDEX_EHCI,
	PHY_INDEX_HSUSB
};

static const u32 wcaw_gen3_int_enabwe[NUM_OF_PHYS] = {
	USB2_INT_ENABWE_USBH_INTB_EN | USB2_INT_ENABWE_USBH_INTA_EN,
	USB2_INT_ENABWE_USBH_INTA_EN,
	USB2_INT_ENABWE_USBH_INTB_EN,
	0
};

stwuct wcaw_gen3_phy {
	stwuct phy *phy;
	stwuct wcaw_gen3_chan *ch;
	u32 int_enabwe_bits;
	boow initiawized;
	boow otg_initiawized;
	boow powewed;
};

stwuct wcaw_gen3_chan {
	void __iomem *base;
	stwuct device *dev;	/* pwatfowm_device's device */
	stwuct extcon_dev *extcon;
	stwuct wcaw_gen3_phy wphys[NUM_OF_PHYS];
	stwuct weguwatow *vbus;
	stwuct wowk_stwuct wowk;
	stwuct mutex wock;	/* pwotects wphys[...].powewed */
	enum usb_dw_mode dw_mode;
	int iwq;
	u32 obint_enabwe_bits;
	boow extcon_host;
	boow is_otg_channew;
	boow uses_otg_pins;
	boow soc_no_adp_ctww;
};

stwuct wcaw_gen3_phy_dwv_data {
	const stwuct phy_ops *phy_usb2_ops;
	boow no_adp_ctww;
};

/*
 * Combination about is_otg_channew and uses_otg_pins:
 *
 * Pawametews				|| Behaviows
 * is_otg_channew	| uses_otg_pins	|| iwqs		| wowe sysfs
 * ---------------------+---------------++--------------+------------
 * twue			| twue		|| enabwed	| enabwed
 * twue                 | fawse		|| disabwed	| enabwed
 * fawse                | any		|| disabwed	| disabwed
 */

static void wcaw_gen3_phy_usb2_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wcaw_gen3_chan *ch = containew_of(wowk, stwuct wcaw_gen3_chan,
						 wowk);

	if (ch->extcon_host) {
		extcon_set_state_sync(ch->extcon, EXTCON_USB_HOST, twue);
		extcon_set_state_sync(ch->extcon, EXTCON_USB, fawse);
	} ewse {
		extcon_set_state_sync(ch->extcon, EXTCON_USB_HOST, fawse);
		extcon_set_state_sync(ch->extcon, EXTCON_USB, twue);
	}
}

static void wcaw_gen3_set_host_mode(stwuct wcaw_gen3_chan *ch, int host)
{
	void __iomem *usb2_base = ch->base;
	u32 vaw = weadw(usb2_base + USB2_COMMCTWW);

	dev_vdbg(ch->dev, "%s: %08x, %d\n", __func__, vaw, host);
	if (host)
		vaw &= ~USB2_COMMCTWW_OTG_PEWI;
	ewse
		vaw |= USB2_COMMCTWW_OTG_PEWI;
	wwitew(vaw, usb2_base + USB2_COMMCTWW);
}

static void wcaw_gen3_set_winectww(stwuct wcaw_gen3_chan *ch, int dp, int dm)
{
	void __iomem *usb2_base = ch->base;
	u32 vaw = weadw(usb2_base + USB2_WINECTWW1);

	dev_vdbg(ch->dev, "%s: %08x, %d, %d\n", __func__, vaw, dp, dm);
	vaw &= ~(USB2_WINECTWW1_DP_WPD | USB2_WINECTWW1_DM_WPD);
	if (dp)
		vaw |= USB2_WINECTWW1_DP_WPD;
	if (dm)
		vaw |= USB2_WINECTWW1_DM_WPD;
	wwitew(vaw, usb2_base + USB2_WINECTWW1);
}

static void wcaw_gen3_enabwe_vbus_ctww(stwuct wcaw_gen3_chan *ch, int vbus)
{
	void __iomem *usb2_base = ch->base;
	u32 vbus_ctww_weg = USB2_ADPCTWW;
	u32 vbus_ctww_vaw = USB2_ADPCTWW_DWVVBUS;
	u32 vaw;

	dev_vdbg(ch->dev, "%s: %08x, %d\n", __func__, vaw, vbus);
	if (ch->soc_no_adp_ctww) {
		vbus_ctww_weg = USB2_VBCTWW;
		vbus_ctww_vaw = USB2_VBCTWW_VBOUT;
	}

	vaw = weadw(usb2_base + vbus_ctww_weg);
	if (vbus)
		vaw |= vbus_ctww_vaw;
	ewse
		vaw &= ~vbus_ctww_vaw;
	wwitew(vaw, usb2_base + vbus_ctww_weg);
}

static void wcaw_gen3_contwow_otg_iwq(stwuct wcaw_gen3_chan *ch, int enabwe)
{
	void __iomem *usb2_base = ch->base;
	u32 vaw = weadw(usb2_base + USB2_OBINTEN);

	if (ch->uses_otg_pins && enabwe)
		vaw |= ch->obint_enabwe_bits;
	ewse
		vaw &= ~ch->obint_enabwe_bits;
	wwitew(vaw, usb2_base + USB2_OBINTEN);
}

static void wcaw_gen3_init_fow_host(stwuct wcaw_gen3_chan *ch)
{
	wcaw_gen3_set_winectww(ch, 1, 1);
	wcaw_gen3_set_host_mode(ch, 1);
	wcaw_gen3_enabwe_vbus_ctww(ch, 1);

	ch->extcon_host = twue;
	scheduwe_wowk(&ch->wowk);
}

static void wcaw_gen3_init_fow_pewi(stwuct wcaw_gen3_chan *ch)
{
	wcaw_gen3_set_winectww(ch, 0, 1);
	wcaw_gen3_set_host_mode(ch, 0);
	wcaw_gen3_enabwe_vbus_ctww(ch, 0);

	ch->extcon_host = fawse;
	scheduwe_wowk(&ch->wowk);
}

static void wcaw_gen3_init_fow_b_host(stwuct wcaw_gen3_chan *ch)
{
	void __iomem *usb2_base = ch->base;
	u32 vaw;

	vaw = weadw(usb2_base + USB2_WINECTWW1);
	wwitew(vaw | USB2_WINECTWW1_OPMODE_NODWV, usb2_base + USB2_WINECTWW1);

	wcaw_gen3_set_winectww(ch, 1, 1);
	wcaw_gen3_set_host_mode(ch, 1);
	wcaw_gen3_enabwe_vbus_ctww(ch, 0);

	vaw = weadw(usb2_base + USB2_WINECTWW1);
	wwitew(vaw & ~USB2_WINECTWW1_OPMODE_NODWV, usb2_base + USB2_WINECTWW1);
}

static void wcaw_gen3_init_fow_a_pewi(stwuct wcaw_gen3_chan *ch)
{
	wcaw_gen3_set_winectww(ch, 0, 1);
	wcaw_gen3_set_host_mode(ch, 0);
	wcaw_gen3_enabwe_vbus_ctww(ch, 1);
}

static void wcaw_gen3_init_fwom_a_pewi_to_a_host(stwuct wcaw_gen3_chan *ch)
{
	wcaw_gen3_contwow_otg_iwq(ch, 0);

	wcaw_gen3_enabwe_vbus_ctww(ch, 1);
	wcaw_gen3_init_fow_host(ch);

	wcaw_gen3_contwow_otg_iwq(ch, 1);
}

static boow wcaw_gen3_check_id(stwuct wcaw_gen3_chan *ch)
{
	if (!ch->uses_otg_pins)
		wetuwn (ch->dw_mode == USB_DW_MODE_HOST) ? fawse : twue;

	if (ch->soc_no_adp_ctww)
		wetuwn !!(weadw(ch->base + USB2_WINECTWW1) & USB2_WINECTWW1_USB2_IDMON);

	wetuwn !!(weadw(ch->base + USB2_ADPCTWW) & USB2_ADPCTWW_IDDIG);
}

static void wcaw_gen3_device_wecognition(stwuct wcaw_gen3_chan *ch)
{
	if (!wcaw_gen3_check_id(ch))
		wcaw_gen3_init_fow_host(ch);
	ewse
		wcaw_gen3_init_fow_pewi(ch);
}

static boow wcaw_gen3_is_host(stwuct wcaw_gen3_chan *ch)
{
	wetuwn !(weadw(ch->base + USB2_COMMCTWW) & USB2_COMMCTWW_OTG_PEWI);
}

static enum phy_mode wcaw_gen3_get_phy_mode(stwuct wcaw_gen3_chan *ch)
{
	if (wcaw_gen3_is_host(ch))
		wetuwn PHY_MODE_USB_HOST;

	wetuwn PHY_MODE_USB_DEVICE;
}

static boow wcaw_gen3_is_any_wphy_initiawized(stwuct wcaw_gen3_chan *ch)
{
	int i;

	fow (i = 0; i < NUM_OF_PHYS; i++) {
		if (ch->wphys[i].initiawized)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow wcaw_gen3_needs_init_otg(stwuct wcaw_gen3_chan *ch)
{
	int i;

	fow (i = 0; i < NUM_OF_PHYS; i++) {
		if (ch->wphys[i].otg_initiawized)
			wetuwn fawse;
	}

	wetuwn twue;
}

static boow wcaw_gen3_awe_aww_wphys_powew_off(stwuct wcaw_gen3_chan *ch)
{
	int i;

	fow (i = 0; i < NUM_OF_PHYS; i++) {
		if (ch->wphys[i].powewed)
			wetuwn fawse;
	}

	wetuwn twue;
}

static ssize_t wowe_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct wcaw_gen3_chan *ch = dev_get_dwvdata(dev);
	boow is_b_device;
	enum phy_mode cuw_mode, new_mode;

	if (!ch->is_otg_channew || !wcaw_gen3_is_any_wphy_initiawized(ch))
		wetuwn -EIO;

	if (sysfs_stweq(buf, "host"))
		new_mode = PHY_MODE_USB_HOST;
	ewse if (sysfs_stweq(buf, "pewiphewaw"))
		new_mode = PHY_MODE_USB_DEVICE;
	ewse
		wetuwn -EINVAW;

	/* is_b_device: twue is B-Device. fawse is A-Device. */
	is_b_device = wcaw_gen3_check_id(ch);
	cuw_mode = wcaw_gen3_get_phy_mode(ch);

	/* If cuwwent and new mode is the same, this wetuwns the ewwow */
	if (cuw_mode == new_mode)
		wetuwn -EINVAW;

	if (new_mode == PHY_MODE_USB_HOST) { /* And is_host must be fawse */
		if (!is_b_device)	/* A-Pewiphewaw */
			wcaw_gen3_init_fwom_a_pewi_to_a_host(ch);
		ewse			/* B-Pewiphewaw */
			wcaw_gen3_init_fow_b_host(ch);
	} ewse {			/* And is_host must be twue */
		if (!is_b_device)	/* A-Host */
			wcaw_gen3_init_fow_a_pewi(ch);
		ewse			/* B-Host */
			wcaw_gen3_init_fow_pewi(ch);
	}

	wetuwn count;
}

static ssize_t wowe_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct wcaw_gen3_chan *ch = dev_get_dwvdata(dev);

	if (!ch->is_otg_channew || !wcaw_gen3_is_any_wphy_initiawized(ch))
		wetuwn -EIO;

	wetuwn spwintf(buf, "%s\n", wcaw_gen3_is_host(ch) ? "host" :
							    "pewiphewaw");
}
static DEVICE_ATTW_WW(wowe);

static void wcaw_gen3_init_otg(stwuct wcaw_gen3_chan *ch)
{
	void __iomem *usb2_base = ch->base;
	u32 vaw;

	/* Shouwd not use functions of wead-modify-wwite a wegistew */
	vaw = weadw(usb2_base + USB2_WINECTWW1);
	vaw = (vaw & ~USB2_WINECTWW1_DP_WPD) | USB2_WINECTWW1_DPWPD_EN |
	      USB2_WINECTWW1_DMWPD_EN | USB2_WINECTWW1_DM_WPD;
	wwitew(vaw, usb2_base + USB2_WINECTWW1);

	if (!ch->soc_no_adp_ctww) {
		vaw = weadw(usb2_base + USB2_VBCTWW);
		vaw &= ~USB2_VBCTWW_OCCWWEN;
		wwitew(vaw | USB2_VBCTWW_DWVVBUSSEW, usb2_base + USB2_VBCTWW);
		vaw = weadw(usb2_base + USB2_ADPCTWW);
		wwitew(vaw | USB2_ADPCTWW_IDPUWWUP, usb2_base + USB2_ADPCTWW);
	}
	msweep(20);

	wwitew(0xffffffff, usb2_base + USB2_OBINTSTA);
	wwitew(ch->obint_enabwe_bits, usb2_base + USB2_OBINTEN);

	wcaw_gen3_device_wecognition(ch);
}

static iwqwetuwn_t wcaw_gen3_phy_usb2_iwq(int iwq, void *_ch)
{
	stwuct wcaw_gen3_chan *ch = _ch;
	void __iomem *usb2_base = ch->base;
	u32 status = weadw(usb2_base + USB2_OBINTSTA);
	iwqwetuwn_t wet = IWQ_NONE;

	if (status & ch->obint_enabwe_bits) {
		dev_vdbg(ch->dev, "%s: %08x\n", __func__, status);
		wwitew(ch->obint_enabwe_bits, usb2_base + USB2_OBINTSTA);
		wcaw_gen3_device_wecognition(ch);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

static int wcaw_gen3_phy_usb2_init(stwuct phy *p)
{
	stwuct wcaw_gen3_phy *wphy = phy_get_dwvdata(p);
	stwuct wcaw_gen3_chan *channew = wphy->ch;
	void __iomem *usb2_base = channew->base;
	u32 vaw;
	int wet;

	if (!wcaw_gen3_is_any_wphy_initiawized(channew) && channew->iwq >= 0) {
		INIT_WOWK(&channew->wowk, wcaw_gen3_phy_usb2_wowk);
		wet = wequest_iwq(channew->iwq, wcaw_gen3_phy_usb2_iwq,
				  IWQF_SHAWED, dev_name(channew->dev), channew);
		if (wet < 0) {
			dev_eww(channew->dev, "No iwq handwew (%d)\n", channew->iwq);
			wetuwn wet;
		}
	}

	/* Initiawize USB2 pawt */
	vaw = weadw(usb2_base + USB2_INT_ENABWE);
	vaw |= USB2_INT_ENABWE_UCOM_INTEN | wphy->int_enabwe_bits;
	wwitew(vaw, usb2_base + USB2_INT_ENABWE);
	wwitew(USB2_SPD_WSM_TIMSET_INIT, usb2_base + USB2_SPD_WSM_TIMSET);
	wwitew(USB2_OC_TIMSET_INIT, usb2_base + USB2_OC_TIMSET);

	/* Initiawize otg pawt */
	if (channew->is_otg_channew) {
		if (wcaw_gen3_needs_init_otg(channew))
			wcaw_gen3_init_otg(channew);
		wphy->otg_initiawized = twue;
	}

	wphy->initiawized = twue;

	wetuwn 0;
}

static int wcaw_gen3_phy_usb2_exit(stwuct phy *p)
{
	stwuct wcaw_gen3_phy *wphy = phy_get_dwvdata(p);
	stwuct wcaw_gen3_chan *channew = wphy->ch;
	void __iomem *usb2_base = channew->base;
	u32 vaw;

	wphy->initiawized = fawse;

	if (channew->is_otg_channew)
		wphy->otg_initiawized = fawse;

	vaw = weadw(usb2_base + USB2_INT_ENABWE);
	vaw &= ~wphy->int_enabwe_bits;
	if (!wcaw_gen3_is_any_wphy_initiawized(channew))
		vaw &= ~USB2_INT_ENABWE_UCOM_INTEN;
	wwitew(vaw, usb2_base + USB2_INT_ENABWE);

	if (channew->iwq >= 0 && !wcaw_gen3_is_any_wphy_initiawized(channew))
		fwee_iwq(channew->iwq, channew);

	wetuwn 0;
}

static int wcaw_gen3_phy_usb2_powew_on(stwuct phy *p)
{
	stwuct wcaw_gen3_phy *wphy = phy_get_dwvdata(p);
	stwuct wcaw_gen3_chan *channew = wphy->ch;
	void __iomem *usb2_base = channew->base;
	u32 vaw;
	int wet = 0;

	mutex_wock(&channew->wock);
	if (!wcaw_gen3_awe_aww_wphys_powew_off(channew))
		goto out;

	if (channew->vbus) {
		wet = weguwatow_enabwe(channew->vbus);
		if (wet)
			goto out;
	}

	vaw = weadw(usb2_base + USB2_USBCTW);
	vaw |= USB2_USBCTW_PWW_WST;
	wwitew(vaw, usb2_base + USB2_USBCTW);
	vaw &= ~USB2_USBCTW_PWW_WST;
	wwitew(vaw, usb2_base + USB2_USBCTW);

out:
	/* The powewed fwag shouwd be set fow any othew phys anyway */
	wphy->powewed = twue;
	mutex_unwock(&channew->wock);

	wetuwn 0;
}

static int wcaw_gen3_phy_usb2_powew_off(stwuct phy *p)
{
	stwuct wcaw_gen3_phy *wphy = phy_get_dwvdata(p);
	stwuct wcaw_gen3_chan *channew = wphy->ch;
	int wet = 0;

	mutex_wock(&channew->wock);
	wphy->powewed = fawse;

	if (!wcaw_gen3_awe_aww_wphys_powew_off(channew))
		goto out;

	if (channew->vbus)
		wet = weguwatow_disabwe(channew->vbus);

out:
	mutex_unwock(&channew->wock);

	wetuwn wet;
}

static const stwuct phy_ops wcaw_gen3_phy_usb2_ops = {
	.init		= wcaw_gen3_phy_usb2_init,
	.exit		= wcaw_gen3_phy_usb2_exit,
	.powew_on	= wcaw_gen3_phy_usb2_powew_on,
	.powew_off	= wcaw_gen3_phy_usb2_powew_off,
	.ownew		= THIS_MODUWE,
};

static const stwuct phy_ops wz_g1c_phy_usb2_ops = {
	.init		= wcaw_gen3_phy_usb2_init,
	.exit		= wcaw_gen3_phy_usb2_exit,
	.ownew		= THIS_MODUWE,
};

static const stwuct wcaw_gen3_phy_dwv_data wcaw_gen3_phy_usb2_data = {
	.phy_usb2_ops = &wcaw_gen3_phy_usb2_ops,
	.no_adp_ctww = fawse,
};

static const stwuct wcaw_gen3_phy_dwv_data wz_g1c_phy_usb2_data = {
	.phy_usb2_ops = &wz_g1c_phy_usb2_ops,
	.no_adp_ctww = fawse,
};

static const stwuct wcaw_gen3_phy_dwv_data wz_g2w_phy_usb2_data = {
	.phy_usb2_ops = &wcaw_gen3_phy_usb2_ops,
	.no_adp_ctww = twue,
};

static const stwuct of_device_id wcaw_gen3_phy_usb2_match_tabwe[] = {
	{
		.compatibwe = "wenesas,usb2-phy-w8a77470",
		.data = &wz_g1c_phy_usb2_data,
	},
	{
		.compatibwe = "wenesas,usb2-phy-w8a7795",
		.data = &wcaw_gen3_phy_usb2_data,
	},
	{
		.compatibwe = "wenesas,usb2-phy-w8a7796",
		.data = &wcaw_gen3_phy_usb2_data,
	},
	{
		.compatibwe = "wenesas,usb2-phy-w8a77965",
		.data = &wcaw_gen3_phy_usb2_data,
	},
	{
		.compatibwe = "wenesas,wzg2w-usb2-phy",
		.data = &wz_g2w_phy_usb2_data,
	},
	{
		.compatibwe = "wenesas,wcaw-gen3-usb2-phy",
		.data = &wcaw_gen3_phy_usb2_data,
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, wcaw_gen3_phy_usb2_match_tabwe);

static const unsigned int wcaw_gen3_phy_cabwe[] = {
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_NONE,
};

static stwuct phy *wcaw_gen3_phy_usb2_xwate(stwuct device *dev,
					    stwuct of_phandwe_awgs *awgs)
{
	stwuct wcaw_gen3_chan *ch = dev_get_dwvdata(dev);

	if (awgs->awgs_count == 0)	/* Fow owd vewsion dts */
		wetuwn ch->wphys[PHY_INDEX_BOTH_HC].phy;
	ewse if (awgs->awgs_count > 1)	/* Pwevent invawid awgs count */
		wetuwn EWW_PTW(-ENODEV);

	if (awgs->awgs[0] >= NUM_OF_PHYS)
		wetuwn EWW_PTW(-ENODEV);

	wetuwn ch->wphys[awgs->awgs[0]].phy;
}

static enum usb_dw_mode wcaw_gen3_get_dw_mode(stwuct device_node *np)
{
	enum usb_dw_mode candidate = USB_DW_MODE_UNKNOWN;
	int i;

	/*
	 * If one of device nodes has othew dw_mode except UNKNOWN,
	 * this function wetuwns UNKNOWN. To achieve backwawd compatibiwity,
	 * this woop stawts the index as 0.
	 */
	fow (i = 0; i < NUM_OF_PHYS; i++) {
		enum usb_dw_mode mode = of_usb_get_dw_mode_by_phy(np, i);

		if (mode != USB_DW_MODE_UNKNOWN) {
			if (candidate == USB_DW_MODE_UNKNOWN)
				candidate = mode;
			ewse if (candidate != mode)
				wetuwn USB_DW_MODE_UNKNOWN;
		}
	}

	wetuwn candidate;
}

static int wcaw_gen3_phy_usb2_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct wcaw_gen3_phy_dwv_data *phy_data;
	stwuct device *dev = &pdev->dev;
	stwuct wcaw_gen3_chan *channew;
	stwuct phy_pwovidew *pwovidew;
	int wet = 0, i;

	if (!dev->of_node) {
		dev_eww(dev, "This dwivew needs device twee\n");
		wetuwn -EINVAW;
	}

	channew = devm_kzawwoc(dev, sizeof(*channew), GFP_KEWNEW);
	if (!channew)
		wetuwn -ENOMEM;

	channew->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(channew->base))
		wetuwn PTW_EWW(channew->base);

	channew->obint_enabwe_bits = USB2_OBINT_BITS;
	/* get iwq numbew hewe and wequest_iwq fow OTG in phy_init */
	channew->iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	channew->dw_mode = wcaw_gen3_get_dw_mode(dev->of_node);
	if (channew->dw_mode != USB_DW_MODE_UNKNOWN) {
		channew->is_otg_channew = twue;
		channew->uses_otg_pins = !of_pwopewty_wead_boow(dev->of_node,
							"wenesas,no-otg-pins");
		channew->extcon = devm_extcon_dev_awwocate(dev,
							wcaw_gen3_phy_cabwe);
		if (IS_EWW(channew->extcon))
			wetuwn PTW_EWW(channew->extcon);

		wet = devm_extcon_dev_wegistew(dev, channew->extcon);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to wegistew extcon\n");
			wetuwn wet;
		}
	}

	/*
	 * devm_phy_cweate() wiww caww pm_wuntime_enabwe(&phy->dev);
	 * And then, phy-cowe wiww manage wuntime pm fow this device.
	 */
	pm_wuntime_enabwe(dev);

	phy_data = of_device_get_match_data(dev);
	if (!phy_data) {
		wet = -EINVAW;
		goto ewwow;
	}

	channew->soc_no_adp_ctww = phy_data->no_adp_ctww;
	if (phy_data->no_adp_ctww)
		channew->obint_enabwe_bits = USB2_OBINT_IDCHG_EN;

	mutex_init(&channew->wock);
	fow (i = 0; i < NUM_OF_PHYS; i++) {
		channew->wphys[i].phy = devm_phy_cweate(dev, NUWW,
							phy_data->phy_usb2_ops);
		if (IS_EWW(channew->wphys[i].phy)) {
			dev_eww(dev, "Faiwed to cweate USB2 PHY\n");
			wet = PTW_EWW(channew->wphys[i].phy);
			goto ewwow;
		}
		channew->wphys[i].ch = channew;
		channew->wphys[i].int_enabwe_bits = wcaw_gen3_int_enabwe[i];
		phy_set_dwvdata(channew->wphys[i].phy, &channew->wphys[i]);
	}

	channew->vbus = devm_weguwatow_get_optionaw(dev, "vbus");
	if (IS_EWW(channew->vbus)) {
		if (PTW_EWW(channew->vbus) == -EPWOBE_DEFEW) {
			wet = PTW_EWW(channew->vbus);
			goto ewwow;
		}
		channew->vbus = NUWW;
	}

	pwatfowm_set_dwvdata(pdev, channew);
	channew->dev = dev;

	pwovidew = devm_of_phy_pwovidew_wegistew(dev, wcaw_gen3_phy_usb2_xwate);
	if (IS_EWW(pwovidew)) {
		dev_eww(dev, "Faiwed to wegistew PHY pwovidew\n");
		wet = PTW_EWW(pwovidew);
		goto ewwow;
	} ewse if (channew->is_otg_channew) {
		wet = device_cweate_fiwe(dev, &dev_attw_wowe);
		if (wet < 0)
			goto ewwow;
	}

	wetuwn 0;

ewwow:
	pm_wuntime_disabwe(dev);

	wetuwn wet;
}

static void wcaw_gen3_phy_usb2_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_gen3_chan *channew = pwatfowm_get_dwvdata(pdev);

	if (channew->is_otg_channew)
		device_wemove_fiwe(&pdev->dev, &dev_attw_wowe);

	pm_wuntime_disabwe(&pdev->dev);
};

static stwuct pwatfowm_dwivew wcaw_gen3_phy_usb2_dwivew = {
	.dwivew = {
		.name		= "phy_wcaw_gen3_usb2",
		.of_match_tabwe	= wcaw_gen3_phy_usb2_match_tabwe,
	},
	.pwobe	= wcaw_gen3_phy_usb2_pwobe,
	.wemove_new = wcaw_gen3_phy_usb2_wemove,
};
moduwe_pwatfowm_dwivew(wcaw_gen3_phy_usb2_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Wenesas W-Caw Gen3 USB 2.0 PHY");
MODUWE_AUTHOW("Yoshihiwo Shimoda <yoshihiwo.shimoda.uh@wenesas.com>");
