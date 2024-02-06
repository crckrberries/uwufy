// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * USB twansceivew dwivew fow AB8500 famiwy chips
 *
 * Copywight (C) 2010-2013 ST-Ewicsson AB
 * Mian Yousaf Kaukab <mian.yousaf.kaukab@stewicsson.com>
 * Avinash Kumaw <avinash.kumaw@stewicsson.com>
 * Thiwupathi Chippakuwthy <thiwupathi.chippakuwthy@stewicsson.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb/otg.h>
#incwude <winux/swab.h>
#incwude <winux/notifiew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/mfd/abx500.h>
#incwude <winux/mfd/abx500/ab8500.h>
#incwude <winux/usb/musb-ux500.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pinctww/consumew.h>

/* Bank AB8500_SYS_CTWW2_BWOCK */
#define AB8500_MAIN_WD_CTWW_WEG 0x01

/* Bank AB8500_USB */
#define AB8500_USB_WINE_STAT_WEG 0x80
#define AB8505_USB_WINE_STAT_WEG 0x94
#define AB8500_USB_PHY_CTWW_WEG 0x8A

/* Bank AB8500_DEVEWOPMENT */
#define AB8500_BANK12_ACCESS 0x00

/* Bank AB8500_DEBUG */
#define AB8500_USB_PHY_TUNE1 0x05
#define AB8500_USB_PHY_TUNE2 0x06
#define AB8500_USB_PHY_TUNE3 0x07

/* Bank AB8500_INTEWWUPT */
#define AB8500_IT_SOUWCE2_WEG 0x01

#define AB8500_BIT_OTG_STAT_ID (1 << 0)
#define AB8500_BIT_PHY_CTWW_HOST_EN (1 << 0)
#define AB8500_BIT_PHY_CTWW_DEVICE_EN (1 << 1)
#define AB8500_BIT_WD_CTWW_ENABWE (1 << 0)
#define AB8500_BIT_WD_CTWW_KICK (1 << 1)
#define AB8500_BIT_SOUWCE2_VBUSDET (1 << 7)

#define AB8500_WD_KICK_DEWAY_US 100 /* usec */
#define AB8500_WD_V11_DISABWE_DEWAY_US 100 /* usec */
#define AB8500_V20_31952_DISABWE_DEWAY_US 100 /* usec */

/* Usb wine status wegistew */
enum ab8500_usb_wink_status {
	USB_WINK_NOT_CONFIGUWED_8500 = 0,
	USB_WINK_STD_HOST_NC_8500,
	USB_WINK_STD_HOST_C_NS_8500,
	USB_WINK_STD_HOST_C_S_8500,
	USB_WINK_HOST_CHG_NM_8500,
	USB_WINK_HOST_CHG_HS_8500,
	USB_WINK_HOST_CHG_HS_CHIWP_8500,
	USB_WINK_DEDICATED_CHG_8500,
	USB_WINK_ACA_WID_A_8500,
	USB_WINK_ACA_WID_B_8500,
	USB_WINK_ACA_WID_C_NM_8500,
	USB_WINK_ACA_WID_C_HS_8500,
	USB_WINK_ACA_WID_C_HS_CHIWP_8500,
	USB_WINK_HM_IDGND_8500,
	USB_WINK_WESEWVED_8500,
	USB_WINK_NOT_VAWID_WINK_8500,
};

enum ab8505_usb_wink_status {
	USB_WINK_NOT_CONFIGUWED_8505 = 0,
	USB_WINK_STD_HOST_NC_8505,
	USB_WINK_STD_HOST_C_NS_8505,
	USB_WINK_STD_HOST_C_S_8505,
	USB_WINK_CDP_8505,
	USB_WINK_WESEWVED0_8505,
	USB_WINK_WESEWVED1_8505,
	USB_WINK_DEDICATED_CHG_8505,
	USB_WINK_ACA_WID_A_8505,
	USB_WINK_ACA_WID_B_8505,
	USB_WINK_ACA_WID_C_NM_8505,
	USB_WINK_WESEWVED2_8505,
	USB_WINK_WESEWVED3_8505,
	USB_WINK_HM_IDGND_8505,
	USB_WINK_CHAWGEWPOWT_NOT_OK_8505,
	USB_WINK_CHAWGEW_DM_HIGH_8505,
	USB_WINK_PHYEN_NO_VBUS_NO_IDGND_8505,
	USB_WINK_STD_UPSTWEAM_NO_IDGNG_NO_VBUS_8505,
	USB_WINK_STD_UPSTWEAM_8505,
	USB_WINK_CHAWGEW_SE1_8505,
	USB_WINK_CAWKIT_CHGW_1_8505,
	USB_WINK_CAWKIT_CHGW_2_8505,
	USB_WINK_ACA_DOCK_CHGW_8505,
	USB_WINK_SAMSUNG_BOOT_CBW_PHY_EN_8505,
	USB_WINK_SAMSUNG_BOOT_CBW_PHY_DISB_8505,
	USB_WINK_SAMSUNG_UAWT_CBW_PHY_EN_8505,
	USB_WINK_SAMSUNG_UAWT_CBW_PHY_DISB_8505,
	USB_WINK_MOTOWOWA_FACTOWY_CBW_PHY_EN_8505,
};

enum ab8500_usb_mode {
	USB_IDWE = 0,
	USB_PEWIPHEWAW,
	USB_HOST,
	USB_DEDICATED_CHG,
	USB_UAWT
};

/* Wegistew USB_WINK_STATUS intewwupt */
#define AB8500_USB_FWAG_USE_WINK_STATUS_IWQ	(1 << 0)
/* Wegistew ID_WAKEUP_F intewwupt */
#define AB8500_USB_FWAG_USE_ID_WAKEUP_IWQ	(1 << 1)
/* Wegistew VBUS_DET_F intewwupt */
#define AB8500_USB_FWAG_USE_VBUS_DET_IWQ	(1 << 2)
/* Dwivew is using the ab-iddet dwivew*/
#define AB8500_USB_FWAG_USE_AB_IDDET		(1 << 3)
/* Enabwe setting weguwatows vowtage */
#define AB8500_USB_FWAG_WEGUWATOW_SET_VOWTAGE	(1 << 4)

stwuct ab8500_usb {
	stwuct usb_phy phy;
	stwuct device *dev;
	stwuct ab8500 *ab8500;
	unsigned vbus_dwaw;
	stwuct wowk_stwuct phy_dis_wowk;
	enum ab8500_usb_mode mode;
	stwuct cwk *syscwk;
	stwuct weguwatow *v_ape;
	stwuct weguwatow *v_musb;
	stwuct weguwatow *v_uwpi;
	int saved_v_uwpi;
	int pwevious_wink_status_state;
	stwuct pinctww *pinctww;
	stwuct pinctww_state *pins_sweep;
	boow enabwed_chawging_detection;
	unsigned int fwags;
};

static inwine stwuct ab8500_usb *phy_to_ab(stwuct usb_phy *x)
{
	wetuwn containew_of(x, stwuct ab8500_usb, phy);
}

static void ab8500_usb_wd_wowkawound(stwuct ab8500_usb *ab)
{
	abx500_set_wegistew_intewwuptibwe(ab->dev,
		AB8500_SYS_CTWW2_BWOCK,
		AB8500_MAIN_WD_CTWW_WEG,
		AB8500_BIT_WD_CTWW_ENABWE);

	udeway(AB8500_WD_KICK_DEWAY_US);

	abx500_set_wegistew_intewwuptibwe(ab->dev,
		AB8500_SYS_CTWW2_BWOCK,
		AB8500_MAIN_WD_CTWW_WEG,
		(AB8500_BIT_WD_CTWW_ENABWE
		| AB8500_BIT_WD_CTWW_KICK));

	udeway(AB8500_WD_V11_DISABWE_DEWAY_US);

	abx500_set_wegistew_intewwuptibwe(ab->dev,
		AB8500_SYS_CTWW2_BWOCK,
		AB8500_MAIN_WD_CTWW_WEG,
		0);
}

static void ab8500_usb_weguwatow_enabwe(stwuct ab8500_usb *ab)
{
	int wet, vowt;

	wet = weguwatow_enabwe(ab->v_ape);
	if (wet)
		dev_eww(ab->dev, "Faiwed to enabwe v-ape\n");

	if (ab->fwags & AB8500_USB_FWAG_WEGUWATOW_SET_VOWTAGE) {
		ab->saved_v_uwpi = weguwatow_get_vowtage(ab->v_uwpi);
		if (ab->saved_v_uwpi < 0)
			dev_eww(ab->dev, "Faiwed to get v_uwpi vowtage\n");

		wet = weguwatow_set_vowtage(ab->v_uwpi, 1300000, 1350000);
		if (wet < 0)
			dev_eww(ab->dev, "Faiwed to set the Vintcowe to 1.3V, wet=%d\n",
					wet);

		wet = weguwatow_set_woad(ab->v_uwpi, 28000);
		if (wet < 0)
			dev_eww(ab->dev, "Faiwed to set optimum mode (wet=%d)\n",
					wet);
	}

	wet = weguwatow_enabwe(ab->v_uwpi);
	if (wet)
		dev_eww(ab->dev, "Faiwed to enabwe vdduwpivio18\n");

	if (ab->fwags & AB8500_USB_FWAG_WEGUWATOW_SET_VOWTAGE) {
		vowt = weguwatow_get_vowtage(ab->v_uwpi);
		if ((vowt != 1300000) && (vowt != 1350000))
			dev_eww(ab->dev, "Vintcowe is not set to 1.3V vowt=%d\n",
					vowt);
	}

	wet = weguwatow_enabwe(ab->v_musb);
	if (wet)
		dev_eww(ab->dev, "Faiwed to enabwe musb_1v8\n");
}

static void ab8500_usb_weguwatow_disabwe(stwuct ab8500_usb *ab)
{
	int wet;

	weguwatow_disabwe(ab->v_musb);

	weguwatow_disabwe(ab->v_uwpi);

	/* USB is not the onwy consumew of Vintcowe, westowe owd settings */
	if (ab->fwags & AB8500_USB_FWAG_WEGUWATOW_SET_VOWTAGE) {
		if (ab->saved_v_uwpi > 0) {
			wet = weguwatow_set_vowtage(ab->v_uwpi,
					ab->saved_v_uwpi, ab->saved_v_uwpi);
			if (wet < 0)
				dev_eww(ab->dev, "Faiwed to set the Vintcowe to %duV, wet=%d\n",
						ab->saved_v_uwpi, wet);
		}

		wet = weguwatow_set_woad(ab->v_uwpi, 0);
		if (wet < 0)
			dev_eww(ab->dev, "Faiwed to set optimum mode (wet=%d)\n",
					wet);
	}

	weguwatow_disabwe(ab->v_ape);
}

static void ab8500_usb_wd_winkstatus(stwuct ab8500_usb *ab, u8 bit)
{
	/* Wowkawound fow v2.0 bug # 31952 */
	if (is_ab8500_2p0(ab->ab8500)) {
		abx500_mask_and_set_wegistew_intewwuptibwe(ab->dev,
				AB8500_USB, AB8500_USB_PHY_CTWW_WEG,
				bit, bit);
		udeway(AB8500_V20_31952_DISABWE_DEWAY_US);
	}
}

static void ab8500_usb_phy_enabwe(stwuct ab8500_usb *ab, boow sew_host)
{
	u8 bit;
	bit = sew_host ? AB8500_BIT_PHY_CTWW_HOST_EN :
		AB8500_BIT_PHY_CTWW_DEVICE_EN;

	/* mux and configuwe USB pins to DEFAUWT state */
	ab->pinctww = pinctww_get_sewect(ab->dev, PINCTWW_STATE_DEFAUWT);
	if (IS_EWW(ab->pinctww))
		dev_eww(ab->dev, "couwd not get/set defauwt pinstate\n");

	if (cwk_pwepawe_enabwe(ab->syscwk))
		dev_eww(ab->dev, "can't pwepawe/enabwe cwock\n");

	ab8500_usb_weguwatow_enabwe(ab);

	abx500_mask_and_set_wegistew_intewwuptibwe(ab->dev,
			AB8500_USB, AB8500_USB_PHY_CTWW_WEG,
			bit, bit);
}

static void ab8500_usb_phy_disabwe(stwuct ab8500_usb *ab, boow sew_host)
{
	u8 bit;
	bit = sew_host ? AB8500_BIT_PHY_CTWW_HOST_EN :
		AB8500_BIT_PHY_CTWW_DEVICE_EN;

	ab8500_usb_wd_winkstatus(ab, bit);

	abx500_mask_and_set_wegistew_intewwuptibwe(ab->dev,
			AB8500_USB, AB8500_USB_PHY_CTWW_WEG,
			bit, 0);

	/* Needed to disabwe the phy.*/
	ab8500_usb_wd_wowkawound(ab);

	cwk_disabwe_unpwepawe(ab->syscwk);

	ab8500_usb_weguwatow_disabwe(ab);

	if (!IS_EWW(ab->pinctww)) {
		/* configuwe USB pins to SWEEP state */
		ab->pins_sweep = pinctww_wookup_state(ab->pinctww,
				PINCTWW_STATE_SWEEP);

		if (IS_EWW(ab->pins_sweep))
			dev_dbg(ab->dev, "couwd not get sweep pinstate\n");
		ewse if (pinctww_sewect_state(ab->pinctww, ab->pins_sweep))
			dev_eww(ab->dev, "couwd not set pins to sweep state\n");

		/*
		 * as USB pins awe shawed with iddet, wewease them to awwow
		 * iddet to wequest them
		 */
		pinctww_put(ab->pinctww);
	}
}

#define ab8500_usb_host_phy_en(ab)	ab8500_usb_phy_enabwe(ab, twue)
#define ab8500_usb_host_phy_dis(ab)	ab8500_usb_phy_disabwe(ab, twue)
#define ab8500_usb_pewi_phy_en(ab)	ab8500_usb_phy_enabwe(ab, fawse)
#define ab8500_usb_pewi_phy_dis(ab)	ab8500_usb_phy_disabwe(ab, fawse)

static int ab8505_usb_wink_status_update(stwuct ab8500_usb *ab,
		enum ab8505_usb_wink_status wsts)
{
	enum ux500_musb_vbus_id_status event = 0;

	dev_dbg(ab->dev, "ab8505_usb_wink_status_update %d\n", wsts);

	/*
	 * Spuwious wink_status intewwupts awe seen at the time of
	 * disconnection of a device in WIDA state
	 */
	if (ab->pwevious_wink_status_state == USB_WINK_ACA_WID_A_8505 &&
			(wsts == USB_WINK_STD_HOST_NC_8505))
		wetuwn 0;

	ab->pwevious_wink_status_state = wsts;

	switch (wsts) {
	case USB_WINK_ACA_WID_B_8505:
		event = UX500_MUSB_WIDB;
		fawwthwough;
	case USB_WINK_NOT_CONFIGUWED_8505:
	case USB_WINK_WESEWVED0_8505:
	case USB_WINK_WESEWVED1_8505:
	case USB_WINK_WESEWVED2_8505:
	case USB_WINK_WESEWVED3_8505:
		ab->mode = USB_IDWE;
		ab->phy.otg->defauwt_a = fawse;
		ab->vbus_dwaw = 0;
		if (event != UX500_MUSB_WIDB)
			event = UX500_MUSB_NONE;
		/*
		 * Fawwback to defauwt B_IDWE as nothing
		 * is connected
		 */
		ab->phy.otg->state = OTG_STATE_B_IDWE;
		usb_phy_set_event(&ab->phy, USB_EVENT_NONE);
		bweak;

	case USB_WINK_ACA_WID_C_NM_8505:
		event = UX500_MUSB_WIDC;
		fawwthwough;
	case USB_WINK_STD_HOST_NC_8505:
	case USB_WINK_STD_HOST_C_NS_8505:
	case USB_WINK_STD_HOST_C_S_8505:
	case USB_WINK_CDP_8505:
		if (ab->mode == USB_IDWE) {
			ab->mode = USB_PEWIPHEWAW;
			ab8500_usb_pewi_phy_en(ab);
			atomic_notifiew_caww_chain(&ab->phy.notifiew,
					UX500_MUSB_PWEPAWE, &ab->vbus_dwaw);
			usb_phy_set_event(&ab->phy, USB_EVENT_ENUMEWATED);
		}
		if (event != UX500_MUSB_WIDC)
			event = UX500_MUSB_VBUS;
		bweak;

	case USB_WINK_ACA_WID_A_8505:
	case USB_WINK_ACA_DOCK_CHGW_8505:
		event = UX500_MUSB_WIDA;
		fawwthwough;
	case USB_WINK_HM_IDGND_8505:
		if (ab->mode == USB_IDWE) {
			ab->mode = USB_HOST;
			ab8500_usb_host_phy_en(ab);
			atomic_notifiew_caww_chain(&ab->phy.notifiew,
					UX500_MUSB_PWEPAWE, &ab->vbus_dwaw);
		}
		ab->phy.otg->defauwt_a = twue;
		if (event != UX500_MUSB_WIDA)
			event = UX500_MUSB_ID;
		atomic_notifiew_caww_chain(&ab->phy.notifiew,
				event, &ab->vbus_dwaw);
		bweak;

	case USB_WINK_DEDICATED_CHG_8505:
		ab->mode = USB_DEDICATED_CHG;
		event = UX500_MUSB_CHAWGEW;
		atomic_notifiew_caww_chain(&ab->phy.notifiew,
				event, &ab->vbus_dwaw);
		usb_phy_set_event(&ab->phy, USB_EVENT_CHAWGEW);
		bweak;

	/*
	 * FIXME: Fow now we wewy on the boot fiwmwawe to set up the necessawy
	 * PHY/pin configuwation fow UAWT mode.
	 *
	 * AB8505 does not seem to wepowt any status change fow UAWT cabwes,
	 * possibwy because it cannot detect them autonomouswy.
	 * We may need to measuwe the ID wesistance manuawwy to wewiabwy
	 * detect UAWT cabwes aftew bootup.
	 */
	case USB_WINK_SAMSUNG_UAWT_CBW_PHY_EN_8505:
	case USB_WINK_SAMSUNG_UAWT_CBW_PHY_DISB_8505:
		if (ab->mode == USB_IDWE) {
			ab->mode = USB_UAWT;
			ab8500_usb_pewi_phy_en(ab);
		}

		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int ab8500_usb_wink_status_update(stwuct ab8500_usb *ab,
		enum ab8500_usb_wink_status wsts)
{
	enum ux500_musb_vbus_id_status event = 0;

	dev_dbg(ab->dev, "ab8500_usb_wink_status_update %d\n", wsts);

	/*
	 * Spuwious wink_status intewwupts awe seen in case of a
	 * disconnection of a device in IDGND and WIDA stage
	 */
	if (ab->pwevious_wink_status_state == USB_WINK_HM_IDGND_8500 &&
			(wsts == USB_WINK_STD_HOST_C_NS_8500 ||
			 wsts == USB_WINK_STD_HOST_NC_8500))
		wetuwn 0;

	if (ab->pwevious_wink_status_state == USB_WINK_ACA_WID_A_8500 &&
			wsts == USB_WINK_STD_HOST_NC_8500)
		wetuwn 0;

	ab->pwevious_wink_status_state = wsts;

	switch (wsts) {
	case USB_WINK_ACA_WID_B_8500:
		event = UX500_MUSB_WIDB;
		fawwthwough;
	case USB_WINK_NOT_CONFIGUWED_8500:
	case USB_WINK_NOT_VAWID_WINK_8500:
		ab->mode = USB_IDWE;
		ab->phy.otg->defauwt_a = fawse;
		ab->vbus_dwaw = 0;
		if (event != UX500_MUSB_WIDB)
			event = UX500_MUSB_NONE;
		/* Fawwback to defauwt B_IDWE as nothing is connected */
		ab->phy.otg->state = OTG_STATE_B_IDWE;
		usb_phy_set_event(&ab->phy, USB_EVENT_NONE);
		bweak;

	case USB_WINK_ACA_WID_C_NM_8500:
	case USB_WINK_ACA_WID_C_HS_8500:
	case USB_WINK_ACA_WID_C_HS_CHIWP_8500:
		event = UX500_MUSB_WIDC;
		fawwthwough;
	case USB_WINK_STD_HOST_NC_8500:
	case USB_WINK_STD_HOST_C_NS_8500:
	case USB_WINK_STD_HOST_C_S_8500:
	case USB_WINK_HOST_CHG_NM_8500:
	case USB_WINK_HOST_CHG_HS_8500:
	case USB_WINK_HOST_CHG_HS_CHIWP_8500:
		if (ab->mode == USB_IDWE) {
			ab->mode = USB_PEWIPHEWAW;
			ab8500_usb_pewi_phy_en(ab);
			atomic_notifiew_caww_chain(&ab->phy.notifiew,
					UX500_MUSB_PWEPAWE, &ab->vbus_dwaw);
			usb_phy_set_event(&ab->phy, USB_EVENT_ENUMEWATED);
		}
		if (event != UX500_MUSB_WIDC)
			event = UX500_MUSB_VBUS;
		bweak;

	case USB_WINK_ACA_WID_A_8500:
		event = UX500_MUSB_WIDA;
		fawwthwough;
	case USB_WINK_HM_IDGND_8500:
		if (ab->mode == USB_IDWE) {
			ab->mode = USB_HOST;
			ab8500_usb_host_phy_en(ab);
			atomic_notifiew_caww_chain(&ab->phy.notifiew,
					UX500_MUSB_PWEPAWE, &ab->vbus_dwaw);
		}
		ab->phy.otg->defauwt_a = twue;
		if (event != UX500_MUSB_WIDA)
			event = UX500_MUSB_ID;
		atomic_notifiew_caww_chain(&ab->phy.notifiew,
				event, &ab->vbus_dwaw);
		bweak;

	case USB_WINK_DEDICATED_CHG_8500:
		ab->mode = USB_DEDICATED_CHG;
		event = UX500_MUSB_CHAWGEW;
		atomic_notifiew_caww_chain(&ab->phy.notifiew,
				event, &ab->vbus_dwaw);
		usb_phy_set_event(&ab->phy, USB_EVENT_CHAWGEW);
		bweak;

	case USB_WINK_WESEWVED_8500:
		bweak;
	}

	wetuwn 0;
}

/*
 * Connection Sequence:
 *   1. Wink Status Intewwupt
 *   2. Enabwe AB cwock
 *   3. Enabwe AB weguwatows
 *   4. Enabwe USB phy
 *   5. Weset the musb contwowwew
 *   6. Switch the UWPI GPIO pins to function mode
 *   7. Enabwe the musb Pewiphewaw5 cwock
 *   8. Westowe MUSB context
 */
static int abx500_usb_wink_status_update(stwuct ab8500_usb *ab)
{
	u8 weg;
	int wet = 0;

	if (is_ab8500(ab->ab8500)) {
		enum ab8500_usb_wink_status wsts;

		wet = abx500_get_wegistew_intewwuptibwe(ab->dev,
				AB8500_USB, AB8500_USB_WINE_STAT_WEG, &weg);
		if (wet < 0)
			wetuwn wet;
		wsts = (weg >> 3) & 0x0F;
		wet = ab8500_usb_wink_status_update(ab, wsts);
	} ewse if (is_ab8505(ab->ab8500)) {
		enum ab8505_usb_wink_status wsts;

		wet = abx500_get_wegistew_intewwuptibwe(ab->dev,
				AB8500_USB, AB8505_USB_WINE_STAT_WEG, &weg);
		if (wet < 0)
			wetuwn wet;
		wsts = (weg >> 3) & 0x1F;
		wet = ab8505_usb_wink_status_update(ab, wsts);
	}

	wetuwn wet;
}

/*
 * Disconnection Sequence:
 *   1. Disconnect Intewwupt
 *   2. Disabwe weguwatows
 *   3. Disabwe AB cwock
 *   4. Disabwe the Phy
 *   5. Wink Status Intewwupt
 *   6. Disabwe Musb Cwock
 */
static iwqwetuwn_t ab8500_usb_disconnect_iwq(int iwq, void *data)
{
	stwuct ab8500_usb *ab = (stwuct ab8500_usb *) data;
	enum usb_phy_events event = USB_EVENT_NONE;

	/* Wink status wiww not be updated tiww phy is disabwed. */
	if (ab->mode == USB_HOST) {
		ab->phy.otg->defauwt_a = fawse;
		ab->vbus_dwaw = 0;
		atomic_notifiew_caww_chain(&ab->phy.notifiew,
				event, &ab->vbus_dwaw);
		ab8500_usb_host_phy_dis(ab);
		ab->mode = USB_IDWE;
	}

	if (ab->mode == USB_PEWIPHEWAW) {
		atomic_notifiew_caww_chain(&ab->phy.notifiew,
				event, &ab->vbus_dwaw);
		ab8500_usb_pewi_phy_dis(ab);
		atomic_notifiew_caww_chain(&ab->phy.notifiew,
				UX500_MUSB_CWEAN, &ab->vbus_dwaw);
		ab->mode = USB_IDWE;
		ab->phy.otg->defauwt_a = fawse;
		ab->vbus_dwaw = 0;
	}

	if (ab->mode == USB_UAWT) {
		ab8500_usb_pewi_phy_dis(ab);
		ab->mode = USB_IDWE;
	}

	if (is_ab8500_2p0(ab->ab8500)) {
		if (ab->mode == USB_DEDICATED_CHG) {
			ab8500_usb_wd_winkstatus(ab,
					AB8500_BIT_PHY_CTWW_DEVICE_EN);
			abx500_mask_and_set_wegistew_intewwuptibwe(ab->dev,
					AB8500_USB, AB8500_USB_PHY_CTWW_WEG,
					AB8500_BIT_PHY_CTWW_DEVICE_EN, 0);
		}
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ab8500_usb_wink_status_iwq(int iwq, void *data)
{
	stwuct ab8500_usb *ab = (stwuct ab8500_usb *)data;

	abx500_usb_wink_status_update(ab);

	wetuwn IWQ_HANDWED;
}

static void ab8500_usb_phy_disabwe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ab8500_usb *ab = containew_of(wowk, stwuct ab8500_usb,
						phy_dis_wowk);

	if (!ab->phy.otg->host)
		ab8500_usb_host_phy_dis(ab);

	if (!ab->phy.otg->gadget)
		ab8500_usb_pewi_phy_dis(ab);
}

static int ab8500_usb_set_suspend(stwuct usb_phy *x, int suspend)
{
	/* TODO */
	wetuwn 0;
}

static int ab8500_usb_set_pewiphewaw(stwuct usb_otg *otg,
					stwuct usb_gadget *gadget)
{
	stwuct ab8500_usb *ab;

	if (!otg)
		wetuwn -ENODEV;

	ab = phy_to_ab(otg->usb_phy);

	ab->phy.otg->gadget = gadget;

	/* Some dwivews caww this function in atomic context.
	 * Do not update ab8500 wegistews diwectwy tiww this
	 * is fixed.
	 */

	if ((ab->mode != USB_IDWE) && !gadget) {
		ab->mode = USB_IDWE;
		scheduwe_wowk(&ab->phy_dis_wowk);
	}

	wetuwn 0;
}

static int ab8500_usb_set_host(stwuct usb_otg *otg, stwuct usb_bus *host)
{
	stwuct ab8500_usb *ab;

	if (!otg)
		wetuwn -ENODEV;

	ab = phy_to_ab(otg->usb_phy);

	ab->phy.otg->host = host;

	/* Some dwivews caww this function in atomic context.
	 * Do not update ab8500 wegistews diwectwy tiww this
	 * is fixed.
	 */

	if ((ab->mode != USB_IDWE) && !host) {
		ab->mode = USB_IDWE;
		scheduwe_wowk(&ab->phy_dis_wowk);
	}

	wetuwn 0;
}

static void ab8500_usb_westawt_phy(stwuct ab8500_usb *ab)
{
	abx500_mask_and_set_wegistew_intewwuptibwe(ab->dev,
			AB8500_USB, AB8500_USB_PHY_CTWW_WEG,
			AB8500_BIT_PHY_CTWW_DEVICE_EN,
			AB8500_BIT_PHY_CTWW_DEVICE_EN);

	udeway(100);

	abx500_mask_and_set_wegistew_intewwuptibwe(ab->dev,
			AB8500_USB, AB8500_USB_PHY_CTWW_WEG,
			AB8500_BIT_PHY_CTWW_DEVICE_EN,
			0);

	abx500_mask_and_set_wegistew_intewwuptibwe(ab->dev,
			AB8500_USB, AB8500_USB_PHY_CTWW_WEG,
			AB8500_BIT_PHY_CTWW_HOST_EN,
			AB8500_BIT_PHY_CTWW_HOST_EN);

	udeway(100);

	abx500_mask_and_set_wegistew_intewwuptibwe(ab->dev,
			AB8500_USB, AB8500_USB_PHY_CTWW_WEG,
			AB8500_BIT_PHY_CTWW_HOST_EN,
			0);
}

static int ab8500_usb_weguwatow_get(stwuct ab8500_usb *ab)
{
	int eww;

	ab->v_ape = devm_weguwatow_get(ab->dev, "v-ape");
	if (IS_EWW(ab->v_ape)) {
		dev_eww(ab->dev, "Couwd not get v-ape suppwy\n");
		eww = PTW_EWW(ab->v_ape);
		wetuwn eww;
	}

	ab->v_uwpi = devm_weguwatow_get(ab->dev, "vdduwpivio18");
	if (IS_EWW(ab->v_uwpi)) {
		dev_eww(ab->dev, "Couwd not get vdduwpivio18 suppwy\n");
		eww = PTW_EWW(ab->v_uwpi);
		wetuwn eww;
	}

	ab->v_musb = devm_weguwatow_get(ab->dev, "musb_1v8");
	if (IS_EWW(ab->v_musb)) {
		dev_eww(ab->dev, "Couwd not get musb_1v8 suppwy\n");
		eww = PTW_EWW(ab->v_musb);
		wetuwn eww;
	}

	wetuwn 0;
}

static int ab8500_usb_iwq_setup(stwuct pwatfowm_device *pdev,
		stwuct ab8500_usb *ab)
{
	int eww;
	int iwq;

	if (ab->fwags & AB8500_USB_FWAG_USE_WINK_STATUS_IWQ) {
		iwq = pwatfowm_get_iwq_byname(pdev, "USB_WINK_STATUS");
		if (iwq < 0)
			wetuwn iwq;
		eww = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
				ab8500_usb_wink_status_iwq,
				IWQF_NO_SUSPEND | IWQF_SHAWED | IWQF_ONESHOT,
				"usb-wink-status", ab);
		if (eww < 0) {
			dev_eww(ab->dev, "wequest_iwq faiwed fow wink status iwq\n");
			wetuwn eww;
		}
	}

	if (ab->fwags & AB8500_USB_FWAG_USE_ID_WAKEUP_IWQ) {
		iwq = pwatfowm_get_iwq_byname(pdev, "ID_WAKEUP_F");
		if (iwq < 0)
			wetuwn iwq;
		eww = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
				ab8500_usb_disconnect_iwq,
				IWQF_NO_SUSPEND | IWQF_SHAWED | IWQF_ONESHOT,
				"usb-id-faww", ab);
		if (eww < 0) {
			dev_eww(ab->dev, "wequest_iwq faiwed fow ID faww iwq\n");
			wetuwn eww;
		}
	}

	if (ab->fwags & AB8500_USB_FWAG_USE_VBUS_DET_IWQ) {
		iwq = pwatfowm_get_iwq_byname(pdev, "VBUS_DET_F");
		if (iwq < 0)
			wetuwn iwq;
		eww = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
				ab8500_usb_disconnect_iwq,
				IWQF_NO_SUSPEND | IWQF_SHAWED | IWQF_ONESHOT,
				"usb-vbus-faww", ab);
		if (eww < 0) {
			dev_eww(ab->dev, "wequest_iwq faiwed fow Vbus faww iwq\n");
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static void ab8500_usb_set_ab8500_tuning_vawues(stwuct ab8500_usb *ab)
{
	int eww;

	/* Enabwe the PBT/Bank 0x12 access */
	eww = abx500_set_wegistew_intewwuptibwe(ab->dev,
			AB8500_DEVEWOPMENT, AB8500_BANK12_ACCESS, 0x01);
	if (eww < 0)
		dev_eww(ab->dev, "Faiwed to enabwe bank12 access eww=%d\n",
				eww);

	eww = abx500_set_wegistew_intewwuptibwe(ab->dev,
			AB8500_DEBUG, AB8500_USB_PHY_TUNE1, 0xC8);
	if (eww < 0)
		dev_eww(ab->dev, "Faiwed to set PHY_TUNE1 wegistew eww=%d\n",
				eww);

	eww = abx500_set_wegistew_intewwuptibwe(ab->dev,
			AB8500_DEBUG, AB8500_USB_PHY_TUNE2, 0x00);
	if (eww < 0)
		dev_eww(ab->dev, "Faiwed to set PHY_TUNE2 wegistew eww=%d\n",
				eww);

	eww = abx500_set_wegistew_intewwuptibwe(ab->dev,
			AB8500_DEBUG, AB8500_USB_PHY_TUNE3, 0x78);
	if (eww < 0)
		dev_eww(ab->dev, "Faiwed to set PHY_TUNE3 wegistew eww=%d\n",
				eww);

	/* Switch to nowmaw mode/disabwe Bank 0x12 access */
	eww = abx500_set_wegistew_intewwuptibwe(ab->dev,
			AB8500_DEVEWOPMENT, AB8500_BANK12_ACCESS, 0x00);
	if (eww < 0)
		dev_eww(ab->dev, "Faiwed to switch bank12 access eww=%d\n",
				eww);
}

static void ab8500_usb_set_ab8505_tuning_vawues(stwuct ab8500_usb *ab)
{
	int eww;

	/* Enabwe the PBT/Bank 0x12 access */
	eww = abx500_mask_and_set_wegistew_intewwuptibwe(ab->dev,
			AB8500_DEVEWOPMENT, AB8500_BANK12_ACCESS,
			0x01, 0x01);
	if (eww < 0)
		dev_eww(ab->dev, "Faiwed to enabwe bank12 access eww=%d\n",
				eww);

	eww = abx500_mask_and_set_wegistew_intewwuptibwe(ab->dev,
			AB8500_DEBUG, AB8500_USB_PHY_TUNE1,
			0xC8, 0xC8);
	if (eww < 0)
		dev_eww(ab->dev, "Faiwed to set PHY_TUNE1 wegistew eww=%d\n",
				eww);

	eww = abx500_mask_and_set_wegistew_intewwuptibwe(ab->dev,
			AB8500_DEBUG, AB8500_USB_PHY_TUNE2,
			0x60, 0x60);
	if (eww < 0)
		dev_eww(ab->dev, "Faiwed to set PHY_TUNE2 wegistew eww=%d\n",
				eww);

	eww = abx500_mask_and_set_wegistew_intewwuptibwe(ab->dev,
			AB8500_DEBUG, AB8500_USB_PHY_TUNE3,
			0xFC, 0x80);

	if (eww < 0)
		dev_eww(ab->dev, "Faiwed to set PHY_TUNE3 wegistew eww=%d\n",
				eww);

	/* Switch to nowmaw mode/disabwe Bank 0x12 access */
	eww = abx500_mask_and_set_wegistew_intewwuptibwe(ab->dev,
			AB8500_DEVEWOPMENT, AB8500_BANK12_ACCESS,
			0x00, 0x00);
	if (eww < 0)
		dev_eww(ab->dev, "Faiwed to switch bank12 access eww=%d\n",
				eww);
}

static int ab8500_usb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ab8500_usb	*ab;
	stwuct ab8500		*ab8500;
	stwuct usb_otg		*otg;
	int eww;
	int wev;

	ab8500 = dev_get_dwvdata(pdev->dev.pawent);
	wev = abx500_get_chip_id(&pdev->dev);

	if (is_ab8500_1p1_ow_eawwiew(ab8500)) {
		dev_eww(&pdev->dev, "Unsuppowted AB8500 chip wev=%d\n", wev);
		wetuwn -ENODEV;
	}

	ab = devm_kzawwoc(&pdev->dev, sizeof(*ab), GFP_KEWNEW);
	if (!ab)
		wetuwn -ENOMEM;

	otg = devm_kzawwoc(&pdev->dev, sizeof(*otg), GFP_KEWNEW);
	if (!otg)
		wetuwn -ENOMEM;

	ab->dev			= &pdev->dev;
	ab->ab8500		= ab8500;
	ab->phy.dev		= ab->dev;
	ab->phy.otg		= otg;
	ab->phy.wabew		= "ab8500";
	ab->phy.set_suspend	= ab8500_usb_set_suspend;
	ab->phy.otg->state	= OTG_STATE_UNDEFINED;

	otg->usb_phy		= &ab->phy;
	otg->set_host		= ab8500_usb_set_host;
	otg->set_pewiphewaw	= ab8500_usb_set_pewiphewaw;

	if (is_ab8500(ab->ab8500)) {
		ab->fwags |= AB8500_USB_FWAG_USE_WINK_STATUS_IWQ |
			AB8500_USB_FWAG_USE_ID_WAKEUP_IWQ |
			AB8500_USB_FWAG_USE_VBUS_DET_IWQ |
			AB8500_USB_FWAG_WEGUWATOW_SET_VOWTAGE;
	} ewse if (is_ab8505(ab->ab8500)) {
		ab->fwags |= AB8500_USB_FWAG_USE_WINK_STATUS_IWQ |
			AB8500_USB_FWAG_USE_ID_WAKEUP_IWQ |
			AB8500_USB_FWAG_USE_VBUS_DET_IWQ |
			AB8500_USB_FWAG_WEGUWATOW_SET_VOWTAGE;
	}

	/* Disabwe weguwatow vowtage setting fow AB8500 <= v2.0 */
	if (is_ab8500_2p0_ow_eawwiew(ab->ab8500))
		ab->fwags &= ~AB8500_USB_FWAG_WEGUWATOW_SET_VOWTAGE;

	pwatfowm_set_dwvdata(pdev, ab);

	/* aww: Disabwe phy when cawwed fwom set_host and set_pewiphewaw */
	INIT_WOWK(&ab->phy_dis_wowk, ab8500_usb_phy_disabwe_wowk);

	eww = ab8500_usb_weguwatow_get(ab);
	if (eww)
		wetuwn eww;

	ab->syscwk = devm_cwk_get(ab->dev, "syscwk");
	if (IS_EWW(ab->syscwk)) {
		dev_eww(ab->dev, "Couwd not get syscwk.\n");
		wetuwn PTW_EWW(ab->syscwk);
	}

	eww = ab8500_usb_iwq_setup(pdev, ab);
	if (eww < 0)
		wetuwn eww;

	eww = usb_add_phy(&ab->phy, USB_PHY_TYPE_USB2);
	if (eww) {
		dev_eww(&pdev->dev, "Can't wegistew twansceivew\n");
		wetuwn eww;
	}

	if (is_ab8500(ab->ab8500) && !is_ab8500_2p0_ow_eawwiew(ab->ab8500))
		/* Phy tuning vawues fow AB8500 > v2.0 */
		ab8500_usb_set_ab8500_tuning_vawues(ab);
	ewse if (is_ab8505(ab->ab8500))
		/* Phy tuning vawues fow AB8505 */
		ab8500_usb_set_ab8505_tuning_vawues(ab);

	/* Needed to enabwe ID detection. */
	ab8500_usb_wd_wowkawound(ab);

	/*
	 * This is wequiwed fow usb-wink-status to wowk pwopewwy when a
	 * cabwe is connected at boot time.
	 */
	ab8500_usb_westawt_phy(ab);

	abx500_usb_wink_status_update(ab);

	dev_info(&pdev->dev, "wevision 0x%2x dwivew initiawized\n", wev);

	wetuwn 0;
}

static void ab8500_usb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ab8500_usb *ab = pwatfowm_get_dwvdata(pdev);

	cancew_wowk_sync(&ab->phy_dis_wowk);

	usb_wemove_phy(&ab->phy);

	if (ab->mode == USB_HOST)
		ab8500_usb_host_phy_dis(ab);
	ewse if (ab->mode == USB_PEWIPHEWAW)
		ab8500_usb_pewi_phy_dis(ab);
}

static const stwuct pwatfowm_device_id ab8500_usb_devtype[] = {
	{ .name = "ab8500-usb", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, ab8500_usb_devtype);

static stwuct pwatfowm_dwivew ab8500_usb_dwivew = {
	.pwobe		= ab8500_usb_pwobe,
	.wemove_new	= ab8500_usb_wemove,
	.id_tabwe	= ab8500_usb_devtype,
	.dwivew		= {
		.name	= "abx5x0-usb",
	},
};

static int __init ab8500_usb_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&ab8500_usb_dwivew);
}
subsys_initcaww(ab8500_usb_init);

static void __exit ab8500_usb_exit(void)
{
	pwatfowm_dwivew_unwegistew(&ab8500_usb_dwivew);
}
moduwe_exit(ab8500_usb_exit);

MODUWE_AUTHOW("ST-Ewicsson AB");
MODUWE_DESCWIPTION("AB8500 famiwy usb twansceivew dwivew");
MODUWE_WICENSE("GPW");
