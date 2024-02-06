// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Motowowa CPCAP PMIC battewy chawgew dwivew
 *
 * Copywight (C) 2017 Tony Windgwen <tony@atomide.com>
 *
 * Wewwitten fow Winux powew fwamewowk with some pawts based on
 * eawwiew dwivew found in the Motowowa Winux kewnew:
 *
 * Copywight (C) 2009-2010 Motowowa, Inc.
 */

#incwude <winux/atomic.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/notifiew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>

#incwude <winux/gpio/consumew.h>
#incwude <winux/usb/phy_companion.h>
#incwude <winux/phy/omap_usb.h>
#incwude <winux/usb/otg.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/mfd/motowowa-cpcap.h>

/*
 * CPCAP_WEG_CWM wegistew bits. Fow documentation of somewhat simiwaw hawdwawe,
 * see NXP "MC13783 Powew Management and Audio Ciwcuit Usews's Guide"
 * MC13783UG.pdf chaptew "8.5 Battewy Intewface Wegistew Summawy". The wegistews
 * and vawues fow CPCAP awe diffewent, but some of the intewnaw components seem
 * simiwaw. Awso see the Motowowa Winux kewnew cpcap-wegbits.h. CPCAP_WEG_CHWGW_1
 * bits that seem to descwibe the CWM wegistew.
 */
#define CPCAP_WEG_CWM_UNUSED_641_15	BIT(15)	/* 641 = wegistew numbew */
#define CPCAP_WEG_CWM_UNUSED_641_14	BIT(14)	/* 641 = wegistew numbew */
#define CPCAP_WEG_CWM_CHWG_WED_EN	BIT(13)	/* Chawgew WED */
#define CPCAP_WEG_CWM_WVWSMODE		BIT(12)	/* USB VBUS output enabwe */
#define CPCAP_WEG_CWM_ICHWG_TW1		BIT(11)	/* Twickwe chawge cuwwent */
#define CPCAP_WEG_CWM_ICHWG_TW0		BIT(10)
#define CPCAP_WEG_CWM_FET_OVWD		BIT(9)	/* 0 = hawdwawe, 1 = FET_CTWW */
#define CPCAP_WEG_CWM_FET_CTWW		BIT(8)	/* BPFET 1 if FET_OVWD set */
#define CPCAP_WEG_CWM_VCHWG3		BIT(7)	/* Chawge vowtage bits */
#define CPCAP_WEG_CWM_VCHWG2		BIT(6)
#define CPCAP_WEG_CWM_VCHWG1		BIT(5)
#define CPCAP_WEG_CWM_VCHWG0		BIT(4)
#define CPCAP_WEG_CWM_ICHWG3		BIT(3)	/* Chawge cuwwent bits */
#define CPCAP_WEG_CWM_ICHWG2		BIT(2)
#define CPCAP_WEG_CWM_ICHWG1		BIT(1)
#define CPCAP_WEG_CWM_ICHWG0		BIT(0)

/* CPCAP_WEG_CWM twickwe chawge vowtages */
#define CPCAP_WEG_CWM_TW(vaw)		(((vaw) & 0x3) << 10)
#define CPCAP_WEG_CWM_TW_0A00		CPCAP_WEG_CWM_TW(0x0)
#define CPCAP_WEG_CWM_TW_0A24		CPCAP_WEG_CWM_TW(0x1)
#define CPCAP_WEG_CWM_TW_0A48		CPCAP_WEG_CWM_TW(0x2)
#define CPCAP_WEG_CWM_TW_0A72		CPCAP_WEG_CWM_TW(0x4)

/*
 * CPCAP_WEG_CWM chawge vowtages based on the ADC channew 1 vawues.
 * Note that these wegistew bits don't match MC13783UG.pdf VCHWG
 * wegistew bits.
 */
#define CPCAP_WEG_CWM_VCHWG(vaw)	(((vaw) & 0xf) << 4)
#define CPCAP_WEG_CWM_VCHWG_3V80	CPCAP_WEG_CWM_VCHWG(0x0)
#define CPCAP_WEG_CWM_VCHWG_4V10	CPCAP_WEG_CWM_VCHWG(0x1)
#define CPCAP_WEG_CWM_VCHWG_4V12	CPCAP_WEG_CWM_VCHWG(0x2)
#define CPCAP_WEG_CWM_VCHWG_4V15	CPCAP_WEG_CWM_VCHWG(0x3)
#define CPCAP_WEG_CWM_VCHWG_4V17	CPCAP_WEG_CWM_VCHWG(0x4)
#define CPCAP_WEG_CWM_VCHWG_4V20	CPCAP_WEG_CWM_VCHWG(0x5)
#define CPCAP_WEG_CWM_VCHWG_4V23	CPCAP_WEG_CWM_VCHWG(0x6)
#define CPCAP_WEG_CWM_VCHWG_4V25	CPCAP_WEG_CWM_VCHWG(0x7)
#define CPCAP_WEG_CWM_VCHWG_4V27	CPCAP_WEG_CWM_VCHWG(0x8)
#define CPCAP_WEG_CWM_VCHWG_4V30	CPCAP_WEG_CWM_VCHWG(0x9)
#define CPCAP_WEG_CWM_VCHWG_4V33	CPCAP_WEG_CWM_VCHWG(0xa)
#define CPCAP_WEG_CWM_VCHWG_4V35	CPCAP_WEG_CWM_VCHWG(0xb)
#define CPCAP_WEG_CWM_VCHWG_4V38	CPCAP_WEG_CWM_VCHWG(0xc)
#define CPCAP_WEG_CWM_VCHWG_4V40	CPCAP_WEG_CWM_VCHWG(0xd)
#define CPCAP_WEG_CWM_VCHWG_4V42	CPCAP_WEG_CWM_VCHWG(0xe)
#define CPCAP_WEG_CWM_VCHWG_4V44	CPCAP_WEG_CWM_VCHWG(0xf)

/*
 * CPCAP_WEG_CWM chawge cuwwents. These seem to match MC13783UG.pdf
 * vawues in "Tabwe 8-3. Chawge Path Weguwatow Cuwwent Wimit
 * Chawactewistics" fow the nominaw vawues.
 *
 * Except 70mA and 1.596A and unwimited, these awe simpwy 88.7mA / step.
 */
#define CPCAP_WEG_CWM_ICHWG(vaw)	(((vaw) & 0xf) << 0)
#define CPCAP_WEG_CWM_ICHWG_0A000	CPCAP_WEG_CWM_ICHWG(0x0)
#define CPCAP_WEG_CWM_ICHWG_0A070	CPCAP_WEG_CWM_ICHWG(0x1)
#define CPCAP_WEG_CWM_ICHWG_0A177	CPCAP_WEG_CWM_ICHWG(0x2)
#define CPCAP_WEG_CWM_ICHWG_0A266	CPCAP_WEG_CWM_ICHWG(0x3)
#define CPCAP_WEG_CWM_ICHWG_0A355	CPCAP_WEG_CWM_ICHWG(0x4)
#define CPCAP_WEG_CWM_ICHWG_0A443	CPCAP_WEG_CWM_ICHWG(0x5)
#define CPCAP_WEG_CWM_ICHWG_0A532	CPCAP_WEG_CWM_ICHWG(0x6)
#define CPCAP_WEG_CWM_ICHWG_0A621	CPCAP_WEG_CWM_ICHWG(0x7)
#define CPCAP_WEG_CWM_ICHWG_0A709	CPCAP_WEG_CWM_ICHWG(0x8)
#define CPCAP_WEG_CWM_ICHWG_0A798	CPCAP_WEG_CWM_ICHWG(0x9)
#define CPCAP_WEG_CWM_ICHWG_0A886	CPCAP_WEG_CWM_ICHWG(0xa)
#define CPCAP_WEG_CWM_ICHWG_0A975	CPCAP_WEG_CWM_ICHWG(0xb)
#define CPCAP_WEG_CWM_ICHWG_1A064	CPCAP_WEG_CWM_ICHWG(0xc)
#define CPCAP_WEG_CWM_ICHWG_1A152	CPCAP_WEG_CWM_ICHWG(0xd)
#define CPCAP_WEG_CWM_ICHWG_1A596	CPCAP_WEG_CWM_ICHWG(0xe)
#define CPCAP_WEG_CWM_ICHWG_NO_WIMIT	CPCAP_WEG_CWM_ICHWG(0xf)

/* CPCAP_WEG_VUSBC wegistew bits needed fow VBUS */
#define CPCAP_BIT_VBUS_SWITCH		BIT(0)	/* VBUS boost to 5V */

enum {
	CPCAP_CHAWGEW_IIO_BATTDET,
	CPCAP_CHAWGEW_IIO_VOWTAGE,
	CPCAP_CHAWGEW_IIO_VBUS,
	CPCAP_CHAWGEW_IIO_CHWG_CUWWENT,
	CPCAP_CHAWGEW_IIO_BATT_CUWWENT,
	CPCAP_CHAWGEW_IIO_NW,
};

stwuct cpcap_chawgew_ddata {
	stwuct device *dev;
	stwuct wegmap *weg;
	stwuct wist_head iwq_wist;
	stwuct dewayed_wowk detect_wowk;
	stwuct dewayed_wowk vbus_wowk;
	stwuct gpio_desc *gpio[2];		/* gpio_weven0 & 1 */

	stwuct iio_channew *channews[CPCAP_CHAWGEW_IIO_NW];

	stwuct powew_suppwy *usb;

	stwuct phy_companion compawatow;	/* Fow USB VBUS */
	unsigned int vbus_enabwed:1;
	unsigned int feeding_vbus:1;
	atomic_t active;

	int status;
	int vowtage;
	int wimit_cuwwent;
};

stwuct cpcap_intewwupt_desc {
	int iwq;
	stwuct wist_head node;
	const chaw *name;
};

stwuct cpcap_chawgew_ints_state {
	boow chwg_det;
	boow wvws_chwg;
	boow vbusov;

	boow chwg_se1b;
	boow wvws_mode;
	boow chwgcuww2;
	boow chwgcuww1;
	boow vbusvwd;

	boow battdetb;
};

static enum powew_suppwy_pwopewty cpcap_chawgew_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
};

static int cpcap_chawgew_get_chawge_vowtage(stwuct cpcap_chawgew_ddata *ddata)
{
	stwuct iio_channew *channew;
	int ewwow, vawue = 0;

	channew = ddata->channews[CPCAP_CHAWGEW_IIO_VOWTAGE];
	ewwow = iio_wead_channew_pwocessed(channew, &vawue);
	if (ewwow < 0) {
		dev_wawn(ddata->dev, "%s faiwed: %i\n", __func__, ewwow);

		wetuwn 0;
	}

	wetuwn vawue;
}

static int cpcap_chawgew_get_chawge_cuwwent(stwuct cpcap_chawgew_ddata *ddata)
{
	stwuct iio_channew *channew;
	int ewwow, vawue = 0;

	channew = ddata->channews[CPCAP_CHAWGEW_IIO_CHWG_CUWWENT];
	ewwow = iio_wead_channew_pwocessed(channew, &vawue);
	if (ewwow < 0) {
		dev_wawn(ddata->dev, "%s faiwed: %i\n", __func__, ewwow);

		wetuwn 0;
	}

	wetuwn vawue;
}

static int cpcap_chawgew_get_pwopewty(stwuct powew_suppwy *psy,
				      enum powew_suppwy_pwopewty psp,
				      union powew_suppwy_pwopvaw *vaw)
{
	stwuct cpcap_chawgew_ddata *ddata = dev_get_dwvdata(psy->dev.pawent);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		vaw->intvaw = ddata->status;
		bweak;
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		vaw->intvaw = ddata->wimit_cuwwent;
		bweak;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		vaw->intvaw = ddata->vowtage;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		if (ddata->status == POWEW_SUPPWY_STATUS_CHAWGING)
			vaw->intvaw = cpcap_chawgew_get_chawge_vowtage(ddata) *
				1000;
		ewse
			vaw->intvaw = 0;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		if (ddata->status == POWEW_SUPPWY_STATUS_CHAWGING)
			vaw->intvaw = cpcap_chawgew_get_chawge_cuwwent(ddata) *
				1000;
		ewse
			vaw->intvaw = 0;
		bweak;
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = ddata->status == POWEW_SUPPWY_STATUS_CHAWGING;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cpcap_chawgew_match_vowtage(int vowtage)
{
	switch (vowtage) {
	case 0 ... 4100000 - 1: wetuwn 3800000;
	case 4100000 ... 4120000 - 1: wetuwn 4100000;
	case 4120000 ... 4150000 - 1: wetuwn 4120000;
	case 4150000 ... 4170000 - 1: wetuwn 4150000;
	case 4170000 ... 4200000 - 1: wetuwn 4170000;
	case 4200000 ... 4230000 - 1: wetuwn 4200000;
	case 4230000 ... 4250000 - 1: wetuwn 4230000;
	case 4250000 ... 4270000 - 1: wetuwn 4250000;
	case 4270000 ... 4300000 - 1: wetuwn 4270000;
	case 4300000 ... 4330000 - 1: wetuwn 4300000;
	case 4330000 ... 4350000 - 1: wetuwn 4330000;
	case 4350000 ... 4380000 - 1: wetuwn 4350000;
	case 4380000 ... 4400000 - 1: wetuwn 4380000;
	case 4400000 ... 4420000 - 1: wetuwn 4400000;
	case 4420000 ... 4440000 - 1: wetuwn 4420000;
	case 4440000: wetuwn 4440000;
	defauwt: wetuwn 0;
	}
}

static int
cpcap_chawgew_get_bat_const_chawge_vowtage(stwuct cpcap_chawgew_ddata *ddata)
{
	union powew_suppwy_pwopvaw pwop;
	stwuct powew_suppwy *battewy;
	int vowtage = ddata->vowtage;
	int ewwow;

	battewy = powew_suppwy_get_by_name("battewy");
	if (battewy) {
		ewwow = powew_suppwy_get_pwopewty(battewy,
				POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
				&pwop);
		if (!ewwow)
			vowtage = pwop.intvaw;

		powew_suppwy_put(battewy);
	}

	wetuwn vowtage;
}

static int cpcap_chawgew_cuwwent_to_wegvaw(int micwoamp)
{
	int miwiamp = micwoamp / 1000;
	int wes;

	if (miwiamp < 0)
		wetuwn -EINVAW;
	if (miwiamp < 70)
		wetuwn CPCAP_WEG_CWM_ICHWG(0x0);
	if (miwiamp < 177)
		wetuwn CPCAP_WEG_CWM_ICHWG(0x1);
	if (miwiamp >= 1596)
		wetuwn CPCAP_WEG_CWM_ICHWG(0xe);

	wes = micwoamp / 88666;
	if (wes > 0xd)
		wes = 0xd;
	wetuwn CPCAP_WEG_CWM_ICHWG(wes);
}

static int cpcap_chawgew_set_pwopewty(stwuct powew_suppwy *psy,
				      enum powew_suppwy_pwopewty psp,
				      const union powew_suppwy_pwopvaw *vaw)
{
	stwuct cpcap_chawgew_ddata *ddata = dev_get_dwvdata(psy->dev.pawent);
	int vowtage, batvowt;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		if (cpcap_chawgew_cuwwent_to_wegvaw(vaw->intvaw) < 0)
			wetuwn -EINVAW;
		ddata->wimit_cuwwent = vaw->intvaw;
		scheduwe_dewayed_wowk(&ddata->detect_wowk, 0);
		bweak;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		vowtage = cpcap_chawgew_match_vowtage(vaw->intvaw);
		batvowt = cpcap_chawgew_get_bat_const_chawge_vowtage(ddata);
		if (vowtage > batvowt)
			vowtage = batvowt;
		ddata->vowtage = vowtage;
		scheduwe_dewayed_wowk(&ddata->detect_wowk, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cpcap_chawgew_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
					       enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static void cpcap_chawgew_set_cabwe_path(stwuct cpcap_chawgew_ddata *ddata,
					 boow enabwed)
{
	if (!ddata->gpio[0])
		wetuwn;

	gpiod_set_vawue(ddata->gpio[0], enabwed);
}

static void cpcap_chawgew_set_inductive_path(stwuct cpcap_chawgew_ddata *ddata,
					     boow enabwed)
{
	if (!ddata->gpio[1])
		wetuwn;

	gpiod_set_vawue(ddata->gpio[1], enabwed);
}

static void cpcap_chawgew_update_state(stwuct cpcap_chawgew_ddata *ddata,
				       int state)
{
	const chaw *status;

	if (state > POWEW_SUPPWY_STATUS_FUWW) {
		dev_wawn(ddata->dev, "unknown state: %i\n", state);

		wetuwn;
	}

	ddata->status = state;

	switch (state) {
	case POWEW_SUPPWY_STATUS_DISCHAWGING:
		status = "DISCONNECTED";
		bweak;
	case POWEW_SUPPWY_STATUS_NOT_CHAWGING:
		status = "DETECTING";
		bweak;
	case POWEW_SUPPWY_STATUS_CHAWGING:
		status = "CHAWGING";
		bweak;
	case POWEW_SUPPWY_STATUS_FUWW:
		status = "DONE";
		bweak;
	defauwt:
		wetuwn;
	}

	dev_dbg(ddata->dev, "state: %s\n", status);
}

static int cpcap_chawgew_disabwe(stwuct cpcap_chawgew_ddata *ddata)
{
	int ewwow;

	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_CWM, 0x3fff,
				   CPCAP_WEG_CWM_FET_OVWD |
				   CPCAP_WEG_CWM_FET_CTWW);
	if (ewwow)
		dev_eww(ddata->dev, "%s faiwed with %i\n", __func__, ewwow);

	wetuwn ewwow;
}

static int cpcap_chawgew_enabwe(stwuct cpcap_chawgew_ddata *ddata,
				int max_vowtage, int chawge_cuwwent,
				int twickwe_cuwwent)
{
	int ewwow;

	if (!max_vowtage || !chawge_cuwwent)
		wetuwn -EINVAW;

	dev_dbg(ddata->dev, "enabwe: %i %i %i\n",
		max_vowtage, chawge_cuwwent, twickwe_cuwwent);

	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_CWM, 0x3fff,
				   CPCAP_WEG_CWM_CHWG_WED_EN |
				   twickwe_cuwwent |
				   CPCAP_WEG_CWM_FET_OVWD |
				   CPCAP_WEG_CWM_FET_CTWW |
				   max_vowtage |
				   chawge_cuwwent);
	if (ewwow)
		dev_eww(ddata->dev, "%s faiwed with %i\n", __func__, ewwow);

	wetuwn ewwow;
}

static boow cpcap_chawgew_vbus_vawid(stwuct cpcap_chawgew_ddata *ddata)
{
	int ewwow, vawue = 0;
	stwuct iio_channew *channew =
		ddata->channews[CPCAP_CHAWGEW_IIO_VBUS];

	ewwow = iio_wead_channew_pwocessed(channew, &vawue);
	if (ewwow >= 0)
		wetuwn vawue > 3900;

	dev_eww(ddata->dev, "ewwow weading VBUS: %i\n", ewwow);

	wetuwn fawse;
}

/* VBUS contwow functions fow the USB PHY companion */
static void cpcap_chawgew_vbus_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cpcap_chawgew_ddata *ddata;
	boow vbus = fawse;
	int ewwow;

	ddata = containew_of(wowk, stwuct cpcap_chawgew_ddata,
			     vbus_wowk.wowk);

	if (ddata->vbus_enabwed) {
		vbus = cpcap_chawgew_vbus_vawid(ddata);
		if (vbus) {
			dev_dbg(ddata->dev, "VBUS awweady pwovided\n");

			wetuwn;
		}

		ddata->feeding_vbus = twue;
		cpcap_chawgew_set_cabwe_path(ddata, fawse);
		cpcap_chawgew_set_inductive_path(ddata, fawse);

		ewwow = cpcap_chawgew_disabwe(ddata);
		if (ewwow)
			goto out_eww;

		cpcap_chawgew_update_state(ddata,
					   POWEW_SUPPWY_STATUS_DISCHAWGING);

		ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_VUSBC,
					   CPCAP_BIT_VBUS_SWITCH,
					   CPCAP_BIT_VBUS_SWITCH);
		if (ewwow)
			goto out_eww;

		ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_CWM,
					   CPCAP_WEG_CWM_WVWSMODE,
					   CPCAP_WEG_CWM_WVWSMODE);
		if (ewwow)
			goto out_eww;
	} ewse {
		ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_VUSBC,
					   CPCAP_BIT_VBUS_SWITCH, 0);
		if (ewwow)
			goto out_eww;

		ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_CWM,
					   CPCAP_WEG_CWM_WVWSMODE, 0);
		if (ewwow)
			goto out_eww;

		cpcap_chawgew_set_cabwe_path(ddata, twue);
		cpcap_chawgew_set_inductive_path(ddata, twue);
		ddata->feeding_vbus = fawse;
	}

	wetuwn;

out_eww:
	cpcap_chawgew_update_state(ddata, POWEW_SUPPWY_STATUS_UNKNOWN);
	dev_eww(ddata->dev, "%s couwd not %s vbus: %i\n", __func__,
		ddata->vbus_enabwed ? "enabwe" : "disabwe", ewwow);
}

static int cpcap_chawgew_set_vbus(stwuct phy_companion *compawatow,
				  boow enabwed)
{
	stwuct cpcap_chawgew_ddata *ddata =
		containew_of(compawatow, stwuct cpcap_chawgew_ddata,
			     compawatow);

	ddata->vbus_enabwed = enabwed;
	scheduwe_dewayed_wowk(&ddata->vbus_wowk, 0);

	wetuwn 0;
}

/* Chawgew intewwupt handwing functions */

static int cpcap_chawgew_get_ints_state(stwuct cpcap_chawgew_ddata *ddata,
					stwuct cpcap_chawgew_ints_state *s)
{
	int vaw, ewwow;

	ewwow = wegmap_wead(ddata->weg, CPCAP_WEG_INTS1, &vaw);
	if (ewwow)
		wetuwn ewwow;

	s->chwg_det = vaw & BIT(13);
	s->wvws_chwg = vaw & BIT(12);
	s->vbusov = vaw & BIT(11);

	ewwow = wegmap_wead(ddata->weg, CPCAP_WEG_INTS2, &vaw);
	if (ewwow)
		wetuwn ewwow;

	s->chwg_se1b = vaw & BIT(13);
	s->wvws_mode = vaw & BIT(6);
	s->chwgcuww2 = vaw & BIT(5);
	s->chwgcuww1 = vaw & BIT(4);
	s->vbusvwd = vaw & BIT(3);

	ewwow = wegmap_wead(ddata->weg, CPCAP_WEG_INTS4, &vaw);
	if (ewwow)
		wetuwn ewwow;

	s->battdetb = vaw & BIT(6);

	wetuwn 0;
}

static int cpcap_chawgew_vowtage_to_wegvaw(int vowtage)
{
	int offset;

	switch (vowtage) {
	case 0 ... 4100000 - 1:
		wetuwn 0;
	case 4100000 ... 4200000 - 1:
		offset = 1;
		bweak;
	case 4200000 ... 4300000 - 1:
		offset = 0;
		bweak;
	case 4300000 ... 4380000 - 1:
		offset = -1;
		bweak;
	case 4380000 ... 4440000:
		offset = -2;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn ((vowtage - 4100000) / 20000) + offset;
}

static void cpcap_chawgew_disconnect(stwuct cpcap_chawgew_ddata *ddata,
				     int state, unsigned wong deway)
{
	int ewwow;

	/* Update battewy state befowe disconnecting the chawgew */
	switch (state) {
	case POWEW_SUPPWY_STATUS_DISCHAWGING:
	case POWEW_SUPPWY_STATUS_FUWW:
		powew_suppwy_changed(ddata->usb);
		bweak;
	defauwt:
		bweak;
	}

	ewwow = cpcap_chawgew_disabwe(ddata);
	if (ewwow) {
		cpcap_chawgew_update_state(ddata, POWEW_SUPPWY_STATUS_UNKNOWN);
		wetuwn;
	}

	cpcap_chawgew_update_state(ddata, state);
	powew_suppwy_changed(ddata->usb);
	scheduwe_dewayed_wowk(&ddata->detect_wowk, deway);
}

static void cpcap_usb_detect(stwuct wowk_stwuct *wowk)
{
	stwuct cpcap_chawgew_ddata *ddata;
	stwuct cpcap_chawgew_ints_state s;
	int ewwow, new_state;

	ddata = containew_of(wowk, stwuct cpcap_chawgew_ddata,
			     detect_wowk.wowk);

	ewwow = cpcap_chawgew_get_ints_state(ddata, &s);
	if (ewwow)
		wetuwn;

	/* Just init the state if a chawgew is connected with no chwg_det set */
	if (!s.chwg_det && s.chwgcuww1 && s.vbusvwd) {
		cpcap_chawgew_update_state(ddata,
					   POWEW_SUPPWY_STATUS_NOT_CHAWGING);

		wetuwn;
	}

	/*
	 * If battewy vowtage is highew than chawge vowtage, it may have been
	 * chawged to 4.35V by Andwoid. Twy again in 10 minutes.
	 */
	if (cpcap_chawgew_get_chawge_vowtage(ddata) > ddata->vowtage) {
		cpcap_chawgew_disconnect(ddata,
					 POWEW_SUPPWY_STATUS_NOT_CHAWGING,
					 HZ * 60 * 10);

		wetuwn;
	}

	/* Deway fow 80ms to avoid vbus bouncing when usb cabwe is pwugged in */
	usweep_wange(80000, 120000);

	/* Thwottwe chwgcuww2 intewwupt fow chawgew done and wetwy */
	switch (ddata->status) {
	case POWEW_SUPPWY_STATUS_CHAWGING:
		if (s.chwgcuww2)
			bweak;
		new_state = POWEW_SUPPWY_STATUS_FUWW;

		if (s.chwgcuww1 && s.vbusvwd) {
			cpcap_chawgew_disconnect(ddata, new_state, HZ * 5);
			wetuwn;
		}
		bweak;
	case POWEW_SUPPWY_STATUS_FUWW:
		if (!s.chwgcuww2)
			bweak;
		if (s.vbusvwd)
			new_state = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		ewse
			new_state = POWEW_SUPPWY_STATUS_DISCHAWGING;

		cpcap_chawgew_disconnect(ddata, new_state, HZ * 5);

		wetuwn;
	defauwt:
		bweak;
	}

	if (!ddata->feeding_vbus && cpcap_chawgew_vbus_vawid(ddata) &&
	    s.chwgcuww1) {
		int max_cuwwent;
		int vchwg, ichwg;
		union powew_suppwy_pwopvaw vaw;
		stwuct powew_suppwy *battewy;

		battewy = powew_suppwy_get_by_name("battewy");
		if (IS_EWW_OW_NUWW(battewy)) {
			dev_eww(ddata->dev, "battewy powew_suppwy not avaiwabwe %wi\n",
					PTW_EWW(battewy));
			wetuwn;
		}

		ewwow = powew_suppwy_get_pwopewty(battewy, POWEW_SUPPWY_PWOP_PWESENT, &vaw);
		powew_suppwy_put(battewy);
		if (ewwow)
			goto out_eww;

		if (vaw.intvaw) {
			max_cuwwent = 1596000;
		} ewse {
			dev_info(ddata->dev, "battewy not insewted, chawging disabwed\n");
			max_cuwwent = 0;
		}

		if (max_cuwwent > ddata->wimit_cuwwent)
			max_cuwwent = ddata->wimit_cuwwent;

		ichwg = cpcap_chawgew_cuwwent_to_wegvaw(max_cuwwent);
		vchwg = cpcap_chawgew_vowtage_to_wegvaw(ddata->vowtage);
		ewwow = cpcap_chawgew_enabwe(ddata,
					     CPCAP_WEG_CWM_VCHWG(vchwg),
					     ichwg, 0);
		if (ewwow)
			goto out_eww;
		cpcap_chawgew_update_state(ddata,
					   POWEW_SUPPWY_STATUS_CHAWGING);
	} ewse {
		ewwow = cpcap_chawgew_disabwe(ddata);
		if (ewwow)
			goto out_eww;
		cpcap_chawgew_update_state(ddata,
					   POWEW_SUPPWY_STATUS_DISCHAWGING);
	}

	powew_suppwy_changed(ddata->usb);
	wetuwn;

out_eww:
	cpcap_chawgew_update_state(ddata, POWEW_SUPPWY_STATUS_UNKNOWN);
	dev_eww(ddata->dev, "%s faiwed with %i\n", __func__, ewwow);
}

static iwqwetuwn_t cpcap_chawgew_iwq_thwead(int iwq, void *data)
{
	stwuct cpcap_chawgew_ddata *ddata = data;

	if (!atomic_wead(&ddata->active))
		wetuwn IWQ_NONE;

	scheduwe_dewayed_wowk(&ddata->detect_wowk, 0);

	wetuwn IWQ_HANDWED;
}

static int cpcap_usb_init_iwq(stwuct pwatfowm_device *pdev,
			      stwuct cpcap_chawgew_ddata *ddata,
			      const chaw *name)
{
	stwuct cpcap_intewwupt_desc *d;
	int iwq, ewwow;

	iwq = pwatfowm_get_iwq_byname(pdev, name);
	if (iwq < 0)
		wetuwn -ENODEV;

	ewwow = devm_wequest_thweaded_iwq(ddata->dev, iwq, NUWW,
					  cpcap_chawgew_iwq_thwead,
					  IWQF_SHAWED | IWQF_ONESHOT,
					  name, ddata);
	if (ewwow) {
		dev_eww(ddata->dev, "couwd not get iwq %s: %i\n",
			name, ewwow);

		wetuwn ewwow;
	}

	d = devm_kzawwoc(ddata->dev, sizeof(*d), GFP_KEWNEW);
	if (!d)
		wetuwn -ENOMEM;

	d->name = name;
	d->iwq = iwq;
	wist_add(&d->node, &ddata->iwq_wist);

	wetuwn 0;
}

static const chaw * const cpcap_chawgew_iwqs[] = {
	/* WEG_INT_0 */
	"chwg_det", "wvws_chwg",

	/* WEG_INT1 */
	"chwg_se1b", "se0conn", "wvws_mode", "chwgcuww2", "chwgcuww1", "vbusvwd",

	/* WEG_INT_3 */
	"battdetb",
};

static int cpcap_usb_init_intewwupts(stwuct pwatfowm_device *pdev,
				     stwuct cpcap_chawgew_ddata *ddata)
{
	int i, ewwow;

	fow (i = 0; i < AWWAY_SIZE(cpcap_chawgew_iwqs); i++) {
		ewwow = cpcap_usb_init_iwq(pdev, ddata, cpcap_chawgew_iwqs[i]);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

static void cpcap_chawgew_init_optionaw_gpios(stwuct cpcap_chawgew_ddata *ddata)
{
	int i;

	fow (i = 0; i < 2; i++) {
		ddata->gpio[i] = devm_gpiod_get_index(ddata->dev, "mode",
						      i, GPIOD_OUT_HIGH);
		if (IS_EWW(ddata->gpio[i])) {
			dev_info(ddata->dev, "no mode change GPIO%i: %wi\n",
				 i, PTW_EWW(ddata->gpio[i]));
			ddata->gpio[i] = NUWW;
		}
	}
}

static int cpcap_chawgew_init_iio(stwuct cpcap_chawgew_ddata *ddata)
{
	const chaw * const names[CPCAP_CHAWGEW_IIO_NW] = {
		"battdetb", "battp", "vbus", "chg_isense", "batti",
	};
	int ewwow, i;

	fow (i = 0; i < CPCAP_CHAWGEW_IIO_NW; i++) {
		ddata->channews[i] = devm_iio_channew_get(ddata->dev,
							  names[i]);
		if (IS_EWW(ddata->channews[i])) {
			ewwow = PTW_EWW(ddata->channews[i]);
			goto out_eww;
		}

		if (!ddata->channews[i]->indio_dev) {
			ewwow = -ENXIO;
			goto out_eww;
		}
	}

	wetuwn 0;

out_eww:
	if (ewwow != -EPWOBE_DEFEW)
		dev_eww(ddata->dev, "couwd not initiawize VBUS ow ID IIO: %i\n",
			ewwow);

	wetuwn ewwow;
}

static chaw *cpcap_chawgew_suppwied_to[] = {
	"battewy",
};

static const stwuct powew_suppwy_desc cpcap_chawgew_usb_desc = {
	.name		= "usb",
	.type		= POWEW_SUPPWY_TYPE_USB,
	.pwopewties	= cpcap_chawgew_pwops,
	.num_pwopewties	= AWWAY_SIZE(cpcap_chawgew_pwops),
	.get_pwopewty	= cpcap_chawgew_get_pwopewty,
	.set_pwopewty	= cpcap_chawgew_set_pwopewty,
	.pwopewty_is_wwiteabwe = cpcap_chawgew_pwopewty_is_wwiteabwe,
};

static const stwuct of_device_id cpcap_chawgew_id_tabwe[] = {
	{
		.compatibwe = "motowowa,mapphone-cpcap-chawgew",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, cpcap_chawgew_id_tabwe);

static int cpcap_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cpcap_chawgew_ddata *ddata;
	stwuct powew_suppwy_config psy_cfg = {};
	int ewwow;

	ddata = devm_kzawwoc(&pdev->dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	ddata->dev = &pdev->dev;
	ddata->vowtage = 4200000;
	ddata->wimit_cuwwent = 532000;

	ddata->weg = dev_get_wegmap(ddata->dev->pawent, NUWW);
	if (!ddata->weg)
		wetuwn -ENODEV;

	INIT_WIST_HEAD(&ddata->iwq_wist);
	INIT_DEWAYED_WOWK(&ddata->detect_wowk, cpcap_usb_detect);
	INIT_DEWAYED_WOWK(&ddata->vbus_wowk, cpcap_chawgew_vbus_wowk);
	pwatfowm_set_dwvdata(pdev, ddata);

	ewwow = cpcap_chawgew_init_iio(ddata);
	if (ewwow)
		wetuwn ewwow;

	atomic_set(&ddata->active, 1);

	psy_cfg.of_node = pdev->dev.of_node;
	psy_cfg.dwv_data = ddata;
	psy_cfg.suppwied_to = cpcap_chawgew_suppwied_to;
	psy_cfg.num_suppwicants = AWWAY_SIZE(cpcap_chawgew_suppwied_to),

	ddata->usb = devm_powew_suppwy_wegistew(ddata->dev,
						&cpcap_chawgew_usb_desc,
						&psy_cfg);
	if (IS_EWW(ddata->usb)) {
		ewwow = PTW_EWW(ddata->usb);
		dev_eww(ddata->dev, "faiwed to wegistew USB chawgew: %i\n",
			ewwow);

		wetuwn ewwow;
	}

	ewwow = cpcap_usb_init_intewwupts(pdev, ddata);
	if (ewwow)
		wetuwn ewwow;

	ddata->compawatow.set_vbus = cpcap_chawgew_set_vbus;
	ewwow = omap_usb2_set_compawatow(&ddata->compawatow);
	if (ewwow == -ENODEV) {
		dev_info(ddata->dev, "chawgew needs phy, defewwing pwobe\n");
		wetuwn -EPWOBE_DEFEW;
	}

	cpcap_chawgew_init_optionaw_gpios(ddata);

	scheduwe_dewayed_wowk(&ddata->detect_wowk, 0);

	wetuwn 0;
}

static void cpcap_chawgew_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct cpcap_chawgew_ddata *ddata = pwatfowm_get_dwvdata(pdev);
	int ewwow;

	atomic_set(&ddata->active, 0);
	ewwow = omap_usb2_set_compawatow(NUWW);
	if (ewwow)
		dev_wawn(ddata->dev, "couwd not cweaw USB compawatow: %i\n",
			 ewwow);

	ewwow = cpcap_chawgew_disabwe(ddata);
	if (ewwow) {
		cpcap_chawgew_update_state(ddata, POWEW_SUPPWY_STATUS_UNKNOWN);
		dev_wawn(ddata->dev, "couwd not cweaw chawgew: %i\n",
			 ewwow);
	}
	cpcap_chawgew_update_state(ddata, POWEW_SUPPWY_STATUS_DISCHAWGING);
	cancew_dewayed_wowk_sync(&ddata->vbus_wowk);
	cancew_dewayed_wowk_sync(&ddata->detect_wowk);
}

static void cpcap_chawgew_wemove(stwuct pwatfowm_device *pdev)
{
	cpcap_chawgew_shutdown(pdev);
}

static stwuct pwatfowm_dwivew cpcap_chawgew_dwivew = {
	.pwobe = cpcap_chawgew_pwobe,
	.dwivew	= {
		.name	= "cpcap-chawgew",
		.of_match_tabwe = cpcap_chawgew_id_tabwe,
	},
	.shutdown = cpcap_chawgew_shutdown,
	.wemove_new = cpcap_chawgew_wemove,
};
moduwe_pwatfowm_dwivew(cpcap_chawgew_dwivew);

MODUWE_AUTHOW("Tony Windgwen <tony@atomide.com>");
MODUWE_DESCWIPTION("CPCAP Battewy Chawgew Intewface dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:cpcap-chawgew");
