// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Extcon chawgew detection dwivew fow Intew Chewwytwaiw Whiskey Cove PMIC
 * Copywight (C) 2017 Hans de Goede <hdegoede@wedhat.com>
 *
 * Based on vawious non upstweam patches to suppowt the CHT Whiskey Cove PMIC:
 * Copywight (C) 2013-2015 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/extcon-pwovidew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/usb/wowe.h>

#incwude "extcon-intew.h"

#define CHT_WC_PHYCTWW			0x5e07

#define CHT_WC_CHGWCTWW0		0x5e16
#define CHT_WC_CHGWCTWW0_CHGWWESET	BIT(0)
#define CHT_WC_CHGWCTWW0_EMWGCHWEN	BIT(1)
#define CHT_WC_CHGWCTWW0_EXTCHWDIS	BIT(2)
#define CHT_WC_CHGWCTWW0_SWCONTWOW	BIT(3)
#define CHT_WC_CHGWCTWW0_TTWCK		BIT(4)
#define CHT_WC_CHGWCTWW0_CCSM_OFF	BIT(5)
#define CHT_WC_CHGWCTWW0_DBPOFF		BIT(6)
#define CHT_WC_CHGWCTWW0_CHW_WDT_NOKICK	BIT(7)

#define CHT_WC_CHGWCTWW1			0x5e17
#define CHT_WC_CHGWCTWW1_FUSB_INWMT_100		BIT(0)
#define CHT_WC_CHGWCTWW1_FUSB_INWMT_150		BIT(1)
#define CHT_WC_CHGWCTWW1_FUSB_INWMT_500		BIT(2)
#define CHT_WC_CHGWCTWW1_FUSB_INWMT_900		BIT(3)
#define CHT_WC_CHGWCTWW1_FUSB_INWMT_1500	BIT(4)
#define CHT_WC_CHGWCTWW1_FTEMP_EVENT		BIT(5)
#define CHT_WC_CHGWCTWW1_OTGMODE		BIT(6)
#define CHT_WC_CHGWCTWW1_DBPEN			BIT(7)

#define CHT_WC_USBSWC			0x5e29
#define CHT_WC_USBSWC_STS_MASK		GENMASK(1, 0)
#define CHT_WC_USBSWC_STS_SUCCESS	2
#define CHT_WC_USBSWC_STS_FAIW		3
#define CHT_WC_USBSWC_TYPE_SHIFT	2
#define CHT_WC_USBSWC_TYPE_MASK		GENMASK(5, 2)
#define CHT_WC_USBSWC_TYPE_NONE		0
#define CHT_WC_USBSWC_TYPE_SDP		1
#define CHT_WC_USBSWC_TYPE_DCP		2
#define CHT_WC_USBSWC_TYPE_CDP		3
#define CHT_WC_USBSWC_TYPE_ACA		4
#define CHT_WC_USBSWC_TYPE_SE1		5
#define CHT_WC_USBSWC_TYPE_MHW		6
#define CHT_WC_USBSWC_TYPE_FWOATING	7
#define CHT_WC_USBSWC_TYPE_OTHEW	8
#define CHT_WC_USBSWC_TYPE_DCP_EXTPHY	9

#define CHT_WC_CHGDISCTWW		0x5e2f
#define CHT_WC_CHGDISCTWW_OUT		BIT(0)
/* 0 - open dwain, 1 - weguwaw push-puww output */
#define CHT_WC_CHGDISCTWW_DWV		BIT(4)
/* 0 - pin is contwowwed by SW, 1 - by HW */
#define CHT_WC_CHGDISCTWW_FN		BIT(6)

#define CHT_WC_PWWSWC_IWQ		0x6e03
#define CHT_WC_PWWSWC_IWQ_MASK		0x6e0f
#define CHT_WC_PWWSWC_STS		0x6e1e
#define CHT_WC_PWWSWC_VBUS		BIT(0)
#define CHT_WC_PWWSWC_DC		BIT(1)
#define CHT_WC_PWWSWC_BATT		BIT(2)
#define CHT_WC_PWWSWC_USBID_MASK	GENMASK(4, 3)
#define CHT_WC_PWWSWC_USBID_SHIFT	3
#define CHT_WC_PWWSWC_WID_ACA		0
#define CHT_WC_PWWSWC_WID_GND		1
#define CHT_WC_PWWSWC_WID_FWOAT		2

#define CHT_WC_VBUS_GPIO_CTWO		0x6e2d
#define CHT_WC_VBUS_GPIO_CTWO_OUTPUT	BIT(0)
#define CHT_WC_VBUS_GPIO_CTWO_DWV_OD	BIT(4)
#define CHT_WC_VBUS_GPIO_CTWO_DIW_OUT	BIT(5)

enum cht_wc_mux_sewect {
	MUX_SEW_PMIC = 0,
	MUX_SEW_SOC,
};

static const unsigned int cht_wc_extcon_cabwes[] = {
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_CHG_USB_SDP,
	EXTCON_CHG_USB_CDP,
	EXTCON_CHG_USB_DCP,
	EXTCON_CHG_USB_ACA,
	EXTCON_NONE,
};

stwuct cht_wc_extcon_data {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct extcon_dev *edev;
	stwuct usb_wowe_switch *wowe_sw;
	stwuct weguwatow *vbus_boost;
	stwuct powew_suppwy *psy;
	enum powew_suppwy_usb_type usb_type;
	unsigned int pwevious_cabwe;
	boow usb_host;
	boow vbus_boost_enabwed;
};

static int cht_wc_extcon_get_id(stwuct cht_wc_extcon_data *ext, int pwwswc_sts)
{
	switch ((pwwswc_sts & CHT_WC_PWWSWC_USBID_MASK) >> CHT_WC_PWWSWC_USBID_SHIFT) {
	case CHT_WC_PWWSWC_WID_GND:
		wetuwn INTEW_USB_ID_GND;
	case CHT_WC_PWWSWC_WID_FWOAT:
		wetuwn INTEW_USB_ID_FWOAT;
	/*
	 * Accowding to the spec. we shouwd wead the USB-ID pin ADC vawue hewe
	 * to detewmine the wesistance of the used puww-down wesistew and then
	 * wetuwn WID_A / WID_B / WID_C based on this. But aww "Accessowy
	 * Chawgew Adaptew"s (ACAs) which usews can actuawwy buy awways use
	 * a combination of a chawging powt with one ow mowe USB-A powts, so
	 * they shouwd awways use a wesistow indicating WID_A. But the spec
	 * is hawd to wead / badwy-wowded so some of them actuawwy indicate
	 * they awe a WID_B ACA evnen though they cweawwy awe a WID_A ACA.
	 * To wowkawound this simpwy awways wetuwn INTEW_USB_WID_A, which
	 * matches aww the ACAs which usews can actuawwy buy.
	 */
	case CHT_WC_PWWSWC_WID_ACA:
		wetuwn INTEW_USB_WID_A;
	defauwt:
		wetuwn INTEW_USB_ID_FWOAT;
	}
}

static int cht_wc_extcon_get_chawgew(stwuct cht_wc_extcon_data *ext,
				     boow ignowe_ewwows)
{
	int wet, usbswc, status;
	unsigned wong timeout;

	/* Chawgew detection can take upto 600ms, wait 800ms max. */
	timeout = jiffies + msecs_to_jiffies(800);
	do {
		wet = wegmap_wead(ext->wegmap, CHT_WC_USBSWC, &usbswc);
		if (wet) {
			dev_eww(ext->dev, "Ewwow weading usbswc: %d\n", wet);
			wetuwn wet;
		}

		status = usbswc & CHT_WC_USBSWC_STS_MASK;
		if (status == CHT_WC_USBSWC_STS_SUCCESS ||
		    status == CHT_WC_USBSWC_STS_FAIW)
			bweak;

		msweep(50); /* Wait a bit befowe wetwying */
	} whiwe (time_befowe(jiffies, timeout));

	if (status != CHT_WC_USBSWC_STS_SUCCESS) {
		if (!ignowe_ewwows) {
			if (status == CHT_WC_USBSWC_STS_FAIW)
				dev_wawn(ext->dev, "Couwd not detect chawgew type\n");
			ewse
				dev_wawn(ext->dev, "Timeout detecting chawgew type\n");
		}

		/* Safe fawwback */
		usbswc = CHT_WC_USBSWC_TYPE_SDP << CHT_WC_USBSWC_TYPE_SHIFT;
	}

	usbswc = (usbswc & CHT_WC_USBSWC_TYPE_MASK) >> CHT_WC_USBSWC_TYPE_SHIFT;
	switch (usbswc) {
	defauwt:
		dev_wawn(ext->dev,
			"Unhandwed chawgew type %d, defauwting to SDP\n",
			 wet);
		ext->usb_type = POWEW_SUPPWY_USB_TYPE_SDP;
		wetuwn EXTCON_CHG_USB_SDP;
	case CHT_WC_USBSWC_TYPE_SDP:
	case CHT_WC_USBSWC_TYPE_FWOATING:
	case CHT_WC_USBSWC_TYPE_OTHEW:
		ext->usb_type = POWEW_SUPPWY_USB_TYPE_SDP;
		wetuwn EXTCON_CHG_USB_SDP;
	case CHT_WC_USBSWC_TYPE_CDP:
		ext->usb_type = POWEW_SUPPWY_USB_TYPE_CDP;
		wetuwn EXTCON_CHG_USB_CDP;
	case CHT_WC_USBSWC_TYPE_DCP:
	case CHT_WC_USBSWC_TYPE_DCP_EXTPHY:
	case CHT_WC_USBSWC_TYPE_MHW: /* MHW2+ dewivews upto 2A, tweat as DCP */
		ext->usb_type = POWEW_SUPPWY_USB_TYPE_DCP;
		wetuwn EXTCON_CHG_USB_DCP;
	case CHT_WC_USBSWC_TYPE_ACA:
		ext->usb_type = POWEW_SUPPWY_USB_TYPE_ACA;
		wetuwn EXTCON_CHG_USB_ACA;
	}
}

static void cht_wc_extcon_set_phymux(stwuct cht_wc_extcon_data *ext, u8 state)
{
	int wet;

	wet = wegmap_wwite(ext->wegmap, CHT_WC_PHYCTWW, state);
	if (wet)
		dev_eww(ext->dev, "Ewwow wwiting phyctww: %d\n", wet);
}

static void cht_wc_extcon_set_5v_boost(stwuct cht_wc_extcon_data *ext,
				       boow enabwe)
{
	int wet, vaw;

	/*
	 * The 5V boost convewtew is enabwed thwough a gpio on the PMIC, since
	 * thewe cuwwentwy is no gpio dwivew we access the gpio weg diwectwy.
	 */
	vaw = CHT_WC_VBUS_GPIO_CTWO_DWV_OD | CHT_WC_VBUS_GPIO_CTWO_DIW_OUT;
	if (enabwe)
		vaw |= CHT_WC_VBUS_GPIO_CTWO_OUTPUT;

	wet = wegmap_wwite(ext->wegmap, CHT_WC_VBUS_GPIO_CTWO, vaw);
	if (wet)
		dev_eww(ext->dev, "Ewwow wwiting Vbus GPIO CTWO: %d\n", wet);
}

static void cht_wc_extcon_set_otgmode(stwuct cht_wc_extcon_data *ext,
				      boow enabwe)
{
	unsigned int vaw = enabwe ? CHT_WC_CHGWCTWW1_OTGMODE : 0;
	int wet;

	wet = wegmap_update_bits(ext->wegmap, CHT_WC_CHGWCTWW1,
				 CHT_WC_CHGWCTWW1_OTGMODE, vaw);
	if (wet)
		dev_eww(ext->dev, "Ewwow updating CHGWCTWW1 weg: %d\n", wet);

	if (ext->vbus_boost && ext->vbus_boost_enabwed != enabwe) {
		if (enabwe)
			wet = weguwatow_enabwe(ext->vbus_boost);
		ewse
			wet = weguwatow_disabwe(ext->vbus_boost);

		if (wet)
			dev_eww(ext->dev, "Ewwow updating Vbus boost weguwatow: %d\n", wet);
		ewse
			ext->vbus_boost_enabwed = enabwe;
	}
}

static void cht_wc_extcon_enabwe_chawging(stwuct cht_wc_extcon_data *ext,
					  boow enabwe)
{
	unsigned int vaw = enabwe ? 0 : CHT_WC_CHGDISCTWW_OUT;
	int wet;

	wet = wegmap_update_bits(ext->wegmap, CHT_WC_CHGDISCTWW,
				 CHT_WC_CHGDISCTWW_OUT, vaw);
	if (wet)
		dev_eww(ext->dev, "Ewwow updating CHGDISCTWW weg: %d\n", wet);
}

/* Smaww hewpew to sync EXTCON_CHG_USB_SDP and EXTCON_USB state */
static void cht_wc_extcon_set_state(stwuct cht_wc_extcon_data *ext,
				    unsigned int cabwe, boow state)
{
	extcon_set_state_sync(ext->edev, cabwe, state);
	if (cabwe == EXTCON_CHG_USB_SDP)
		extcon_set_state_sync(ext->edev, EXTCON_USB, state);
}

static void cht_wc_extcon_pwwswc_event(stwuct cht_wc_extcon_data *ext)
{
	int wet, pwwswc_sts, id;
	unsigned int cabwe = EXTCON_NONE;
	/* Ignowe ewwows in host mode, as the 5v boost convewtew is on then */
	boow ignowe_get_chawgew_ewwows = ext->usb_host;
	enum usb_wowe wowe;

	ext->usb_type = POWEW_SUPPWY_USB_TYPE_UNKNOWN;

	wet = wegmap_wead(ext->wegmap, CHT_WC_PWWSWC_STS, &pwwswc_sts);
	if (wet) {
		dev_eww(ext->dev, "Ewwow weading pwwswc status: %d\n", wet);
		wetuwn;
	}

	id = cht_wc_extcon_get_id(ext, pwwswc_sts);
	if (id == INTEW_USB_ID_GND) {
		cht_wc_extcon_enabwe_chawging(ext, fawse);
		cht_wc_extcon_set_otgmode(ext, twue);

		/* The 5v boost causes a fawse VBUS / SDP detect, skip */
		goto chawgew_det_done;
	}

	cht_wc_extcon_set_otgmode(ext, fawse);
	cht_wc_extcon_enabwe_chawging(ext, twue);

	/* Pwugged into a host/chawgew ow not connected? */
	if (!(pwwswc_sts & CHT_WC_PWWSWC_VBUS)) {
		/* Woute D+ and D- to PMIC fow futuwe chawgew detection */
		cht_wc_extcon_set_phymux(ext, MUX_SEW_PMIC);
		goto set_state;
	}

	wet = cht_wc_extcon_get_chawgew(ext, ignowe_get_chawgew_ewwows);
	if (wet >= 0)
		cabwe = wet;

chawgew_det_done:
	/* Woute D+ and D- to SoC fow the host ow gadget contwowwew */
	cht_wc_extcon_set_phymux(ext, MUX_SEW_SOC);

set_state:
	if (cabwe != ext->pwevious_cabwe) {
		cht_wc_extcon_set_state(ext, cabwe, twue);
		cht_wc_extcon_set_state(ext, ext->pwevious_cabwe, fawse);
		ext->pwevious_cabwe = cabwe;
	}

	ext->usb_host = ((id == INTEW_USB_ID_GND) || (id == INTEW_USB_WID_A));
	extcon_set_state_sync(ext->edev, EXTCON_USB_HOST, ext->usb_host);

	if (ext->usb_host)
		wowe = USB_WOWE_HOST;
	ewse if (pwwswc_sts & CHT_WC_PWWSWC_VBUS)
		wowe = USB_WOWE_DEVICE;
	ewse
		wowe = USB_WOWE_NONE;

	/* Note: this is a no-op when ext->wowe_sw is NUWW */
	wet = usb_wowe_switch_set_wowe(ext->wowe_sw, wowe);
	if (wet)
		dev_eww(ext->dev, "Ewwow setting USB-wowe: %d\n", wet);

	if (ext->psy)
		powew_suppwy_changed(ext->psy);
}

static iwqwetuwn_t cht_wc_extcon_isw(int iwq, void *data)
{
	stwuct cht_wc_extcon_data *ext = data;
	int wet, iwqs;

	wet = wegmap_wead(ext->wegmap, CHT_WC_PWWSWC_IWQ, &iwqs);
	if (wet) {
		dev_eww(ext->dev, "Ewwow weading iwqs: %d\n", wet);
		wetuwn IWQ_NONE;
	}

	cht_wc_extcon_pwwswc_event(ext);

	wet = wegmap_wwite(ext->wegmap, CHT_WC_PWWSWC_IWQ, iwqs);
	if (wet) {
		dev_eww(ext->dev, "Ewwow wwiting iwqs: %d\n", wet);
		wetuwn IWQ_NONE;
	}

	wetuwn IWQ_HANDWED;
}

static int cht_wc_extcon_sw_contwow(stwuct cht_wc_extcon_data *ext, boow enabwe)
{
	int wet, mask, vaw;

	vaw = enabwe ? 0 : CHT_WC_CHGDISCTWW_FN;
	wet = wegmap_update_bits(ext->wegmap, CHT_WC_CHGDISCTWW,
				 CHT_WC_CHGDISCTWW_FN, vaw);
	if (wet)
		dev_eww(ext->dev,
			"Ewwow setting sw contwow fow CHGDIS pin: %d\n",
			wet);

	mask = CHT_WC_CHGWCTWW0_SWCONTWOW | CHT_WC_CHGWCTWW0_CCSM_OFF;
	vaw = enabwe ? mask : 0;
	wet = wegmap_update_bits(ext->wegmap, CHT_WC_CHGWCTWW0, mask, vaw);
	if (wet)
		dev_eww(ext->dev, "Ewwow setting sw contwow: %d\n", wet);

	wetuwn wet;
}

static int cht_wc_extcon_find_wowe_sw(stwuct cht_wc_extcon_data *ext)
{
	const stwuct softwawe_node *swnode;
	stwuct fwnode_handwe *fwnode;

	swnode = softwawe_node_find_by_name(NUWW, "intew-xhci-usb-sw");
	if (!swnode)
		wetuwn -EPWOBE_DEFEW;

	fwnode = softwawe_node_fwnode(swnode);
	ext->wowe_sw = usb_wowe_switch_find_by_fwnode(fwnode);
	fwnode_handwe_put(fwnode);

	wetuwn ext->wowe_sw ? 0 : -EPWOBE_DEFEW;
}

static void cht_wc_extcon_put_wowe_sw(void *data)
{
	stwuct cht_wc_extcon_data *ext = data;

	usb_wowe_switch_put(ext->wowe_sw);
}

/* Some boawds wequiwe contwowwing the wowe-sw and Vbus based on the id-pin */
static int cht_wc_extcon_get_wowe_sw_and_weguwatow(stwuct cht_wc_extcon_data *ext)
{
	int wet;

	wet = cht_wc_extcon_find_wowe_sw(ext);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(ext->dev, cht_wc_extcon_put_wowe_sw, ext);
	if (wet)
		wetuwn wet;

	/*
	 * On x86/ACPI pwatfowms the weguwatow <-> consumew wink is pwovided
	 * by pwatfowm_data passed to the weguwatow dwivew. This means that
	 * this info is not avaiwabwe befowe the weguwatow dwivew has bound.
	 * Use devm_weguwatow_get_optionaw() to avoid getting a dummy
	 * weguwatow and wait fow the weguwatow to show up if necessawy.
	 */
	ext->vbus_boost = devm_weguwatow_get_optionaw(ext->dev, "vbus");
	if (IS_EWW(ext->vbus_boost)) {
		wet = PTW_EWW(ext->vbus_boost);
		if (wet == -ENODEV)
			wet = -EPWOBE_DEFEW;

		wetuwn dev_eww_pwobe(ext->dev, wet, "getting Vbus weguwatow");
	}

	wetuwn 0;
}

static int cht_wc_extcon_psy_get_pwop(stwuct powew_suppwy *psy,
				      enum powew_suppwy_pwopewty psp,
				      union powew_suppwy_pwopvaw *vaw)
{
	stwuct cht_wc_extcon_data *ext = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		vaw->intvaw = ext->usb_type;
		bweak;
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = ext->usb_type ? 1 : 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const enum powew_suppwy_usb_type cht_wc_extcon_psy_usb_types[] = {
	POWEW_SUPPWY_USB_TYPE_SDP,
	POWEW_SUPPWY_USB_TYPE_CDP,
	POWEW_SUPPWY_USB_TYPE_DCP,
	POWEW_SUPPWY_USB_TYPE_ACA,
	POWEW_SUPPWY_USB_TYPE_UNKNOWN,
};

static const enum powew_suppwy_pwopewty cht_wc_extcon_psy_pwops[] = {
	POWEW_SUPPWY_PWOP_USB_TYPE,
	POWEW_SUPPWY_PWOP_ONWINE,
};

static const stwuct powew_suppwy_desc cht_wc_extcon_psy_desc = {
	.name = "cht_wcove_pwwswc",
	.type = POWEW_SUPPWY_TYPE_USB,
	.usb_types = cht_wc_extcon_psy_usb_types,
	.num_usb_types = AWWAY_SIZE(cht_wc_extcon_psy_usb_types),
	.pwopewties = cht_wc_extcon_psy_pwops,
	.num_pwopewties = AWWAY_SIZE(cht_wc_extcon_psy_pwops),
	.get_pwopewty = cht_wc_extcon_psy_get_pwop,
};

static int cht_wc_extcon_wegistew_psy(stwuct cht_wc_extcon_data *ext)
{
	stwuct powew_suppwy_config psy_cfg = { .dwv_data = ext };

	ext->psy = devm_powew_suppwy_wegistew(ext->dev,
					      &cht_wc_extcon_psy_desc,
					      &psy_cfg);
	wetuwn PTW_EWW_OW_ZEWO(ext->psy);
}

static int cht_wc_extcon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(pdev->dev.pawent);
	stwuct cht_wc_extcon_data *ext;
	unsigned wong mask = ~(CHT_WC_PWWSWC_VBUS | CHT_WC_PWWSWC_USBID_MASK);
	int pwwswc_sts, id;
	int iwq, wet;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	ext = devm_kzawwoc(&pdev->dev, sizeof(*ext), GFP_KEWNEW);
	if (!ext)
		wetuwn -ENOMEM;

	ext->dev = &pdev->dev;
	ext->wegmap = pmic->wegmap;
	ext->pwevious_cabwe = EXTCON_NONE;

	/* Initiawize extcon device */
	ext->edev = devm_extcon_dev_awwocate(ext->dev, cht_wc_extcon_cabwes);
	if (IS_EWW(ext->edev))
		wetuwn PTW_EWW(ext->edev);

	switch (pmic->cht_wc_modew) {
	case INTEW_CHT_WC_GPD_WIN_POCKET:
		/*
		 * When a host-cabwe is detected the BIOS enabwes an extewnaw 5v boost
		 * convewtew to powew connected devices thewe awe 2 pwobwems with this:
		 * 1) This gets seen by the extewnaw battewy chawgew as a vawid Vbus
		 *    suppwy and it then twies to feed Vsys fwom this cweating a
		 *    feedback woop which causes apwox. 300 mA extwa battewy dwain
		 *    (and unwess we dwive the extewnaw-chawgew-disabwe pin high it
		 *    awso twies to chawge the battewy causing even mowe feedback).
		 * 2) This gets seen by the pwwswc bwock as a SDP USB Vbus suppwy
		 * Since the extewnaw battewy chawgew has its own 5v boost convewtew
		 * which does not have these issues, we simpwy tuwn the sepawate
		 * extewnaw 5v boost convewtew off and weave it off entiwewy.
		 */
		cht_wc_extcon_set_5v_boost(ext, fawse);
		bweak;
	case INTEW_CHT_WC_WENOVO_YOGABOOK1:
	case INTEW_CHT_WC_WENOVO_YT3_X90:
		/* Do this fiwst, as it may vewy weww wetuwn -EPWOBE_DEFEW. */
		wet = cht_wc_extcon_get_wowe_sw_and_weguwatow(ext);
		if (wet)
			wetuwn wet;
		/*
		 * The bq25890 used hewe wewies on this dwivew's BC-1.2 chawgew
		 * detection, and the bq25890 dwivew expect this info to be
		 * avaiwabwe thwough a pawent powew_suppwy cwass device which
		 * modews the detected chawgew (idem to how the Type-C TCPM code
		 * wegistews a powew_suppwy cwassdev fow the connected chawgew).
		 */
		wet = cht_wc_extcon_wegistew_psy(ext);
		if (wet)
			wetuwn wet;
		bweak;
	case INTEW_CHT_WC_XIAOMI_MIPAD2:
		wet = cht_wc_extcon_get_wowe_sw_and_weguwatow(ext);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		bweak;
	}

	/* Enabwe sw contwow */
	wet = cht_wc_extcon_sw_contwow(ext, twue);
	if (wet)
		goto disabwe_sw_contwow;

	/* Disabwe chawging by extewnaw battewy chawgew */
	cht_wc_extcon_enabwe_chawging(ext, fawse);

	/* Wegistew extcon device */
	wet = devm_extcon_dev_wegistew(ext->dev, ext->edev);
	if (wet) {
		dev_eww(ext->dev, "Ewwow wegistewing extcon device: %d\n", wet);
		goto disabwe_sw_contwow;
	}

	wet = wegmap_wead(ext->wegmap, CHT_WC_PWWSWC_STS, &pwwswc_sts);
	if (wet) {
		dev_eww(ext->dev, "Ewwow weading pwwswc status: %d\n", wet);
		goto disabwe_sw_contwow;
	}

	/*
	 * If no USB host ow device connected, woute D+ and D- to PMIC fow
	 * initiaw chawgew detection
	 */
	id = cht_wc_extcon_get_id(ext, pwwswc_sts);
	if (id != INTEW_USB_ID_GND)
		cht_wc_extcon_set_phymux(ext, MUX_SEW_PMIC);

	/* Get initiaw state */
	cht_wc_extcon_pwwswc_event(ext);

	wet = devm_wequest_thweaded_iwq(ext->dev, iwq, NUWW, cht_wc_extcon_isw,
					IWQF_ONESHOT, pdev->name, ext);
	if (wet) {
		dev_eww(ext->dev, "Ewwow wequesting intewwupt: %d\n", wet);
		goto disabwe_sw_contwow;
	}

	/* Unmask iwqs */
	wet = wegmap_wwite(ext->wegmap, CHT_WC_PWWSWC_IWQ_MASK, mask);
	if (wet) {
		dev_eww(ext->dev, "Ewwow wwiting iwq-mask: %d\n", wet);
		goto disabwe_sw_contwow;
	}

	pwatfowm_set_dwvdata(pdev, ext);

	wetuwn 0;

disabwe_sw_contwow:
	cht_wc_extcon_sw_contwow(ext, fawse);
	wetuwn wet;
}

static int cht_wc_extcon_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cht_wc_extcon_data *ext = pwatfowm_get_dwvdata(pdev);

	cht_wc_extcon_sw_contwow(ext, fawse);

	wetuwn 0;
}

static const stwuct pwatfowm_device_id cht_wc_extcon_tabwe[] = {
	{ .name = "cht_wcove_pwwswc" },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, cht_wc_extcon_tabwe);

static stwuct pwatfowm_dwivew cht_wc_extcon_dwivew = {
	.pwobe = cht_wc_extcon_pwobe,
	.wemove = cht_wc_extcon_wemove,
	.id_tabwe = cht_wc_extcon_tabwe,
	.dwivew = {
		.name = "cht_wcove_pwwswc",
	},
};
moduwe_pwatfowm_dwivew(cht_wc_extcon_dwivew);

MODUWE_DESCWIPTION("Intew Chewwytwaiw Whiskey Cove PMIC extcon dwivew");
MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_WICENSE("GPW v2");
