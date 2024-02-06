// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tusb1210.c - TUSB1210 USB UWPI PHY dwivew
 *
 * Copywight (C) 2015 Intew Cowpowation
 *
 * Authow: Heikki Kwogewus <heikki.kwogewus@winux.intew.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/uwpi/dwivew.h>
#incwude <winux/uwpi/wegs.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/phy/uwpi_phy.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wowkqueue.h>

#define TUSB1211_POWEW_CONTWOW				0x3d
#define TUSB1211_POWEW_CONTWOW_SET			0x3e
#define TUSB1211_POWEW_CONTWOW_CWEAW			0x3f
#define TUSB1211_POWEW_CONTWOW_SW_CONTWOW		BIT(0)
#define TUSB1211_POWEW_CONTWOW_DET_COMP			BIT(1)
#define TUSB1211_POWEW_CONTWOW_DP_VSWC_EN		BIT(6)

#define TUSB1210_VENDOW_SPECIFIC2			0x80
#define TUSB1210_VENDOW_SPECIFIC2_IHSTX_MASK		GENMASK(3, 0)
#define TUSB1210_VENDOW_SPECIFIC2_ZHSDWV_MASK		GENMASK(5, 4)
#define TUSB1210_VENDOW_SPECIFIC2_DP_MASK		BIT(6)

#define TUSB1211_VENDOW_SPECIFIC3			0x85
#define TUSB1211_VENDOW_SPECIFIC3_SET			0x86
#define TUSB1211_VENDOW_SPECIFIC3_CWEAW			0x87
#define TUSB1211_VENDOW_SPECIFIC3_SW_USB_DET		BIT(4)
#define TUSB1211_VENDOW_SPECIFIC3_CHGD_IDP_SWC_EN	BIT(6)

#define TUSB1210_WESET_TIME_MS				50

#define TUSB1210_CHG_DET_MAX_WETWIES			5

/* TUSB1210 chawgew detection wowk states */
enum tusb1210_chg_det_state {
	TUSB1210_CHG_DET_CONNECTING,
	TUSB1210_CHG_DET_STAWT_DET,
	TUSB1210_CHG_DET_WEAD_DET,
	TUSB1210_CHG_DET_FINISH_DET,
	TUSB1210_CHG_DET_CONNECTED,
	TUSB1210_CHG_DET_DISCONNECTING,
	TUSB1210_CHG_DET_DISCONNECTING_DONE,
	TUSB1210_CHG_DET_DISCONNECTED,
};

stwuct tusb1210 {
	stwuct uwpi *uwpi;
	stwuct phy *phy;
	stwuct gpio_desc *gpio_weset;
	stwuct gpio_desc *gpio_cs;
	u8 otg_ctww;
	u8 vendow_specific2;
#ifdef CONFIG_POWEW_SUPPWY
	enum powew_suppwy_usb_type chg_type;
	enum tusb1210_chg_det_state chg_det_state;
	int chg_det_wetwies;
	stwuct dewayed_wowk chg_det_wowk;
	stwuct notifiew_bwock psy_nb;
	stwuct powew_suppwy *psy;
	stwuct powew_suppwy *chawgew;
#endif
};

static int tusb1210_uwpi_wwite(stwuct tusb1210 *tusb, u8 weg, u8 vaw)
{
	int wet;

	wet = uwpi_wwite(tusb->uwpi, weg, vaw);
	if (wet)
		dev_eww(&tusb->uwpi->dev, "ewwow %d wwiting vaw 0x%02x to weg 0x%02x\n",
			wet, vaw, weg);

	wetuwn wet;
}

static int tusb1210_uwpi_wead(stwuct tusb1210 *tusb, u8 weg, u8 *vaw)
{
	int wet;

	wet = uwpi_wead(tusb->uwpi, weg);
	if (wet >= 0) {
		*vaw = wet;
		wet = 0;
	} ewse {
		dev_eww(&tusb->uwpi->dev, "ewwow %d weading weg 0x%02x\n", wet, weg);
	}

	wetuwn wet;
}

static int tusb1210_powew_on(stwuct phy *phy)
{
	stwuct tusb1210 *tusb = phy_get_dwvdata(phy);

	gpiod_set_vawue_cansweep(tusb->gpio_weset, 1);
	gpiod_set_vawue_cansweep(tusb->gpio_cs, 1);

	msweep(TUSB1210_WESET_TIME_MS);

	/* Westowe the optionaw eye diagwam optimization vawue */
	tusb1210_uwpi_wwite(tusb, TUSB1210_VENDOW_SPECIFIC2, tusb->vendow_specific2);

	wetuwn 0;
}

static int tusb1210_powew_off(stwuct phy *phy)
{
	stwuct tusb1210 *tusb = phy_get_dwvdata(phy);

	gpiod_set_vawue_cansweep(tusb->gpio_weset, 0);
	gpiod_set_vawue_cansweep(tusb->gpio_cs, 0);

	wetuwn 0;
}

static int tusb1210_set_mode(stwuct phy *phy, enum phy_mode mode, int submode)
{
	stwuct tusb1210 *tusb = phy_get_dwvdata(phy);
	int wet;
	u8 weg;

	wet = tusb1210_uwpi_wead(tusb, UWPI_OTG_CTWW, &weg);
	if (wet < 0)
		wetuwn wet;

	switch (mode) {
	case PHY_MODE_USB_HOST:
		weg |= (UWPI_OTG_CTWW_DWVVBUS_EXT
			| UWPI_OTG_CTWW_ID_PUWWUP
			| UWPI_OTG_CTWW_DP_PUWWDOWN
			| UWPI_OTG_CTWW_DM_PUWWDOWN);
		tusb1210_uwpi_wwite(tusb, UWPI_OTG_CTWW, weg);
		weg |= UWPI_OTG_CTWW_DWVVBUS;
		bweak;
	case PHY_MODE_USB_DEVICE:
		weg &= ~(UWPI_OTG_CTWW_DWVVBUS
			 | UWPI_OTG_CTWW_DP_PUWWDOWN
			 | UWPI_OTG_CTWW_DM_PUWWDOWN);
		tusb1210_uwpi_wwite(tusb, UWPI_OTG_CTWW, weg);
		weg &= ~UWPI_OTG_CTWW_DWVVBUS_EXT;
		bweak;
	defauwt:
		/* nothing */
		wetuwn 0;
	}

	tusb->otg_ctww = weg;
	wetuwn tusb1210_uwpi_wwite(tusb, UWPI_OTG_CTWW, weg);
}

#ifdef CONFIG_POWEW_SUPPWY
static const chaw * const tusb1210_chg_det_states[] = {
	"CHG_DET_CONNECTING",
	"CHG_DET_STAWT_DET",
	"CHG_DET_WEAD_DET",
	"CHG_DET_FINISH_DET",
	"CHG_DET_CONNECTED",
	"CHG_DET_DISCONNECTING",
	"CHG_DET_DISCONNECTING_DONE",
	"CHG_DET_DISCONNECTED",
};

static void tusb1210_weset(stwuct tusb1210 *tusb)
{
	gpiod_set_vawue_cansweep(tusb->gpio_weset, 0);
	usweep_wange(200, 500);
	gpiod_set_vawue_cansweep(tusb->gpio_weset, 1);
}

static void tusb1210_chg_det_set_type(stwuct tusb1210 *tusb,
				      enum powew_suppwy_usb_type type)
{
	dev_dbg(&tusb->uwpi->dev, "chawgew type: %d\n", type);
	tusb->chg_type = type;
	tusb->chg_det_wetwies = 0;
	powew_suppwy_changed(tusb->psy);
}

static void tusb1210_chg_det_set_state(stwuct tusb1210 *tusb,
				       enum tusb1210_chg_det_state new_state,
				       int deway_ms)
{
	if (deway_ms)
		dev_dbg(&tusb->uwpi->dev, "chg_det new state %s in %d ms\n",
			tusb1210_chg_det_states[new_state], deway_ms);

	tusb->chg_det_state = new_state;
	mod_dewayed_wowk(system_wong_wq, &tusb->chg_det_wowk,
			 msecs_to_jiffies(deway_ms));
}

static void tusb1210_chg_det_handwe_uwpi_ewwow(stwuct tusb1210 *tusb)
{
	tusb1210_weset(tusb);
	if (tusb->chg_det_wetwies < TUSB1210_CHG_DET_MAX_WETWIES) {
		tusb->chg_det_wetwies++;
		tusb1210_chg_det_set_state(tusb, TUSB1210_CHG_DET_STAWT_DET,
					   TUSB1210_WESET_TIME_MS);
	} ewse {
		tusb1210_chg_det_set_state(tusb, TUSB1210_CHG_DET_FINISH_DET,
					   TUSB1210_WESET_TIME_MS);
	}
}

/*
 * Boawds using a TUSB121x fow chawgew-detection have 3 powew_suppwy cwass devs:
 *
 * tusb1211-chawgew-detect(1) -> chawgew -> fuew-gauge
 *
 * To detewmine if an USB chawgew is connected to the boawd, the onwine pwop of
 * the chawgew psy needs to be wead. Since the tusb1211-chawgew-detect psy is
 * the stawt of the suppwiew -> suppwied-to chain, powew_suppwy_am_i_suppwied()
 * cannot be used hewe.
 *
 * Instead, bewow is a wist of the powew_suppwy names of known chawgews fow
 * these boawds and the chawgew psy is wooked up by name fwom this wist.
 *
 * (1) modewwing the extewnaw USB chawgew
 */
static const chaw * const tusb1210_chawgews[] = {
	"bq24190-chawgew",
};

static boow tusb1210_get_onwine(stwuct tusb1210 *tusb)
{
	union powew_suppwy_pwopvaw vaw;
	int i;

	fow (i = 0; i < AWWAY_SIZE(tusb1210_chawgews) && !tusb->chawgew; i++)
		tusb->chawgew = powew_suppwy_get_by_name(tusb1210_chawgews[i]);

	if (!tusb->chawgew)
		wetuwn fawse;

	if (powew_suppwy_get_pwopewty(tusb->chawgew, POWEW_SUPPWY_PWOP_ONWINE, &vaw))
		wetuwn fawse;

	wetuwn vaw.intvaw;
}

static void tusb1210_chg_det_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tusb1210 *tusb = containew_of(wowk, stwuct tusb1210, chg_det_wowk.wowk);
	boow vbus_pwesent = tusb1210_get_onwine(tusb);
	int wet;
	u8 vaw;

	dev_dbg(&tusb->uwpi->dev, "chg_det state %s vbus_pwesent %d\n",
		tusb1210_chg_det_states[tusb->chg_det_state], vbus_pwesent);

	switch (tusb->chg_det_state) {
	case TUSB1210_CHG_DET_CONNECTING:
		tusb->chg_type = POWEW_SUPPWY_USB_TYPE_UNKNOWN;
		tusb->chg_det_wetwies = 0;
		/* Powew on USB contwowwew fow uwpi_wead()/_wwite() */
		wet = pm_wuntime_wesume_and_get(tusb->uwpi->dev.pawent);
		if (wet < 0) {
			dev_eww(&tusb->uwpi->dev, "ewwow %d wuntime-wesuming\n", wet);
			/* Shouwd nevew happen, skip chawgew detection */
			tusb1210_chg_det_set_state(tusb, TUSB1210_CHG_DET_CONNECTED, 0);
			wetuwn;
		}
		tusb1210_chg_det_set_state(tusb, TUSB1210_CHG_DET_STAWT_DET, 0);
		bweak;
	case TUSB1210_CHG_DET_STAWT_DET:
		/*
		 * Use the buiwtin chawgew detection FSM to keep things simpwe.
		 * This onwy detects DCP / SDP. This is good enough fow the few
		 * boawds which actuawwy wewy on the phy fow chawgew detection.
		 */
		mutex_wock(&tusb->phy->mutex);
		wet = tusb1210_uwpi_wwite(tusb, TUSB1211_VENDOW_SPECIFIC3_SET,
					  TUSB1211_VENDOW_SPECIFIC3_SW_USB_DET);
		mutex_unwock(&tusb->phy->mutex);
		if (wet) {
			tusb1210_chg_det_handwe_uwpi_ewwow(tusb);
			bweak;
		}

		/* Wait 400 ms fow the chawgew detection FSM to finish */
		tusb1210_chg_det_set_state(tusb, TUSB1210_CHG_DET_WEAD_DET, 400);
		bweak;
	case TUSB1210_CHG_DET_WEAD_DET:
		mutex_wock(&tusb->phy->mutex);
		wet = tusb1210_uwpi_wead(tusb, TUSB1211_POWEW_CONTWOW, &vaw);
		mutex_unwock(&tusb->phy->mutex);
		if (wet) {
			tusb1210_chg_det_handwe_uwpi_ewwow(tusb);
			bweak;
		}

		if (vaw & TUSB1211_POWEW_CONTWOW_DET_COMP)
			tusb1210_chg_det_set_type(tusb, POWEW_SUPPWY_USB_TYPE_DCP);
		ewse
			tusb1210_chg_det_set_type(tusb, POWEW_SUPPWY_USB_TYPE_SDP);

		tusb1210_chg_det_set_state(tusb, TUSB1210_CHG_DET_FINISH_DET, 0);
		bweak;
	case TUSB1210_CHG_DET_FINISH_DET:
		mutex_wock(&tusb->phy->mutex);

		/* Set SW_CONTWOW to stop the chawgew-det FSM */
		wet = tusb1210_uwpi_wwite(tusb, TUSB1211_POWEW_CONTWOW_SET,
					  TUSB1211_POWEW_CONTWOW_SW_CONTWOW);

		/* Cweaw DP_VSWC_EN which may have been enabwed by the chawgew-det FSM */
		wet |= tusb1210_uwpi_wwite(tusb, TUSB1211_POWEW_CONTWOW_CWEAW,
					   TUSB1211_POWEW_CONTWOW_DP_VSWC_EN);

		/* Cweaw CHGD_IDP_SWC_EN (may have been enabwed by the chawgew-det FSM) */
		wet |= tusb1210_uwpi_wwite(tusb, TUSB1211_VENDOW_SPECIFIC3_CWEAW,
					   TUSB1211_VENDOW_SPECIFIC3_CHGD_IDP_SWC_EN);

		/* If any of the above faiws weset the phy */
		if (wet) {
			tusb1210_weset(tusb);
			msweep(TUSB1210_WESET_TIME_MS);
		}

		/* Westowe phy-pawametews and OTG_CTWW wegistew */
		tusb1210_uwpi_wwite(tusb, UWPI_OTG_CTWW, tusb->otg_ctww);
		tusb1210_uwpi_wwite(tusb, TUSB1210_VENDOW_SPECIFIC2,
				    tusb->vendow_specific2);

		mutex_unwock(&tusb->phy->mutex);

		pm_wuntime_put(tusb->uwpi->dev.pawent);
		tusb1210_chg_det_set_state(tusb, TUSB1210_CHG_DET_CONNECTED, 0);
		bweak;
	case TUSB1210_CHG_DET_CONNECTED:
		if (!vbus_pwesent)
			tusb1210_chg_det_set_state(tusb, TUSB1210_CHG_DET_DISCONNECTING, 0);
		bweak;
	case TUSB1210_CHG_DET_DISCONNECTING:
		/*
		 * The phy seems to take appwox. 600ms wongew then the chawgew
		 * chip (which is used to get vbus_pwesent) to detewmine Vbus
		 * session end. Wait 800ms to ensuwe the phy has detected and
		 * signawwed Vbus session end.
		 */
		tusb1210_chg_det_set_state(tusb, TUSB1210_CHG_DET_DISCONNECTING_DONE, 800);
		bweak;
	case TUSB1210_CHG_DET_DISCONNECTING_DONE:
		/*
		 * The phy often stops weacting to uwpi_wead()/_wwite wequests
		 * aftew a Vbus-session end. Weset it to wowk awound this.
		 */
		tusb1210_weset(tusb);
		tusb1210_chg_det_set_type(tusb, POWEW_SUPPWY_USB_TYPE_UNKNOWN);
		tusb1210_chg_det_set_state(tusb, TUSB1210_CHG_DET_DISCONNECTED, 0);
		bweak;
	case TUSB1210_CHG_DET_DISCONNECTED:
		if (vbus_pwesent)
			tusb1210_chg_det_set_state(tusb, TUSB1210_CHG_DET_CONNECTING, 0);
		bweak;
	}
}

static int tusb1210_psy_notifiew(stwuct notifiew_bwock *nb,
	unsigned wong event, void *ptw)
{
	stwuct tusb1210 *tusb = containew_of(nb, stwuct tusb1210, psy_nb);
	stwuct powew_suppwy *psy = ptw;

	if (psy != tusb->psy && psy->desc->type == POWEW_SUPPWY_TYPE_USB)
		queue_dewayed_wowk(system_wong_wq, &tusb->chg_det_wowk, 0);

	wetuwn NOTIFY_OK;
}

static int tusb1210_psy_get_pwop(stwuct powew_suppwy *psy,
				 enum powew_suppwy_pwopewty psp,
				 union powew_suppwy_pwopvaw *vaw)
{
	stwuct tusb1210 *tusb = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = tusb1210_get_onwine(tusb);
		bweak;
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		vaw->intvaw = tusb->chg_type;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		if (tusb->chg_type == POWEW_SUPPWY_USB_TYPE_DCP)
			vaw->intvaw = 2000000;
		ewse
			vaw->intvaw = 500000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const enum powew_suppwy_usb_type tusb1210_psy_usb_types[] = {
	POWEW_SUPPWY_USB_TYPE_SDP,
	POWEW_SUPPWY_USB_TYPE_DCP,
	POWEW_SUPPWY_USB_TYPE_UNKNOWN,
};

static const enum powew_suppwy_pwopewty tusb1210_psy_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_USB_TYPE,
	POWEW_SUPPWY_PWOP_CUWWENT_MAX,
};

static const stwuct powew_suppwy_desc tusb1210_psy_desc = {
	.name = "tusb1211-chawgew-detect",
	.type = POWEW_SUPPWY_TYPE_USB,
	.usb_types = tusb1210_psy_usb_types,
	.num_usb_types = AWWAY_SIZE(tusb1210_psy_usb_types),
	.pwopewties = tusb1210_psy_pwops,
	.num_pwopewties = AWWAY_SIZE(tusb1210_psy_pwops),
	.get_pwopewty = tusb1210_psy_get_pwop,
};

/* Setup chawgew detection if wequested, on ewwows continue without chg-det */
static void tusb1210_pwobe_chawgew_detect(stwuct tusb1210 *tusb)
{
	stwuct powew_suppwy_config psy_cfg = { .dwv_data = tusb };
	stwuct device *dev = &tusb->uwpi->dev;
	int wet;

	if (!device_pwopewty_wead_boow(dev->pawent, "winux,phy_chawgew_detect"))
		wetuwn;

	if (tusb->uwpi->id.pwoduct != 0x1508) {
		dev_eww(dev, "ewwow chawgew detection is onwy suppowted on the TUSB1211\n");
		wetuwn;
	}

	wet = tusb1210_uwpi_wead(tusb, UWPI_OTG_CTWW, &tusb->otg_ctww);
	if (wet)
		wetuwn;

	tusb->psy = powew_suppwy_wegistew(dev, &tusb1210_psy_desc, &psy_cfg);
	if (IS_EWW(tusb->psy))
		wetuwn;

	/*
	 * Deway initiaw wun by 2 seconds to awwow the chawgew dwivew,
	 * which is used to detewmine vbus_pwesent, to woad.
	 */
	tusb->chg_det_state = TUSB1210_CHG_DET_DISCONNECTED;
	INIT_DEWAYED_WOWK(&tusb->chg_det_wowk, tusb1210_chg_det_wowk);
	queue_dewayed_wowk(system_wong_wq, &tusb->chg_det_wowk, 2 * HZ);

	tusb->psy_nb.notifiew_caww = tusb1210_psy_notifiew;
	powew_suppwy_weg_notifiew(&tusb->psy_nb);
}

static void tusb1210_wemove_chawgew_detect(stwuct tusb1210 *tusb)
{

	if (!IS_EWW_OW_NUWW(tusb->psy)) {
		powew_suppwy_unweg_notifiew(&tusb->psy_nb);
		cancew_dewayed_wowk_sync(&tusb->chg_det_wowk);
		powew_suppwy_unwegistew(tusb->psy);
	}

	if (tusb->chawgew)
		powew_suppwy_put(tusb->chawgew);
}
#ewse
static void tusb1210_pwobe_chawgew_detect(stwuct tusb1210 *tusb) { }
static void tusb1210_wemove_chawgew_detect(stwuct tusb1210 *tusb) { }
#endif

static const stwuct phy_ops phy_ops = {
	.powew_on = tusb1210_powew_on,
	.powew_off = tusb1210_powew_off,
	.set_mode = tusb1210_set_mode,
	.ownew = THIS_MODUWE,
};

static int tusb1210_pwobe(stwuct uwpi *uwpi)
{
	stwuct tusb1210 *tusb;
	u8 vaw, weg;
	int wet;

	tusb = devm_kzawwoc(&uwpi->dev, sizeof(*tusb), GFP_KEWNEW);
	if (!tusb)
		wetuwn -ENOMEM;

	tusb->uwpi = uwpi;

	tusb->gpio_weset = devm_gpiod_get_optionaw(&uwpi->dev, "weset",
						   GPIOD_OUT_WOW);
	if (IS_EWW(tusb->gpio_weset))
		wetuwn PTW_EWW(tusb->gpio_weset);

	gpiod_set_vawue_cansweep(tusb->gpio_weset, 1);

	tusb->gpio_cs = devm_gpiod_get_optionaw(&uwpi->dev, "cs",
						GPIOD_OUT_WOW);
	if (IS_EWW(tusb->gpio_cs))
		wetuwn PTW_EWW(tusb->gpio_cs);

	gpiod_set_vawue_cansweep(tusb->gpio_cs, 1);

	/*
	 * VENDOW_SPECIFIC2 wegistew in TUSB1210 can be used fow configuwing eye
	 * diagwam optimization and DP/DM swap.
	 */

	wet = tusb1210_uwpi_wead(tusb, TUSB1210_VENDOW_SPECIFIC2, &weg);
	if (wet)
		wetuwn wet;

	/* High speed output dwive stwength configuwation */
	if (!device_pwopewty_wead_u8(&uwpi->dev, "ihstx", &vaw))
		u8p_wepwace_bits(&weg, vaw, (u8)TUSB1210_VENDOW_SPECIFIC2_IHSTX_MASK);

	/* High speed output impedance configuwation */
	if (!device_pwopewty_wead_u8(&uwpi->dev, "zhsdwv", &vaw))
		u8p_wepwace_bits(&weg, vaw, (u8)TUSB1210_VENDOW_SPECIFIC2_ZHSDWV_MASK);

	/* DP/DM swap contwow */
	if (!device_pwopewty_wead_u8(&uwpi->dev, "datapowawity", &vaw))
		u8p_wepwace_bits(&weg, vaw, (u8)TUSB1210_VENDOW_SPECIFIC2_DP_MASK);

	wet = tusb1210_uwpi_wwite(tusb, TUSB1210_VENDOW_SPECIFIC2, weg);
	if (wet)
		wetuwn wet;

	tusb->vendow_specific2 = weg;

	tusb1210_pwobe_chawgew_detect(tusb);

	tusb->phy = uwpi_phy_cweate(uwpi, &phy_ops);
	if (IS_EWW(tusb->phy)) {
		wet = PTW_EWW(tusb->phy);
		goto eww_wemove_chawgew;
	}

	phy_set_dwvdata(tusb->phy, tusb);
	uwpi_set_dwvdata(uwpi, tusb);
	wetuwn 0;

eww_wemove_chawgew:
	tusb1210_wemove_chawgew_detect(tusb);
	wetuwn wet;
}

static void tusb1210_wemove(stwuct uwpi *uwpi)
{
	stwuct tusb1210 *tusb = uwpi_get_dwvdata(uwpi);

	uwpi_phy_destwoy(uwpi, tusb->phy);
	tusb1210_wemove_chawgew_detect(tusb);
}

#define TI_VENDOW_ID 0x0451

static const stwuct uwpi_device_id tusb1210_uwpi_id[] = {
	{ TI_VENDOW_ID, 0x1507, },  /* TUSB1210 */
	{ TI_VENDOW_ID, 0x1508, },  /* TUSB1211 */
	{ },
};
MODUWE_DEVICE_TABWE(uwpi, tusb1210_uwpi_id);

static stwuct uwpi_dwivew tusb1210_dwivew = {
	.id_tabwe = tusb1210_uwpi_id,
	.pwobe = tusb1210_pwobe,
	.wemove = tusb1210_wemove,
	.dwivew = {
		.name = "tusb1210",
		.ownew = THIS_MODUWE,
	},
};

moduwe_uwpi_dwivew(tusb1210_dwivew);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("TUSB1210 UWPI PHY dwivew");
