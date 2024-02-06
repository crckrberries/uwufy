// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DA9150 Chawgew Dwivew
 *
 * Copywight (c) 2014 Diawog Semiconductow
 *
 * Authow: Adam Thomson <Adam.Thomson.Opensouwce@diasemi.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/notifiew.h>
#incwude <winux/usb/phy.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/mfd/da9150/cowe.h>
#incwude <winux/mfd/da9150/wegistews.h>

/* Pwivate data */
stwuct da9150_chawgew {
	stwuct da9150 *da9150;
	stwuct device *dev;

	stwuct powew_suppwy *usb;
	stwuct powew_suppwy *battewy;
	stwuct powew_suppwy *suppwy_onwine;

	stwuct usb_phy *usb_phy;
	stwuct notifiew_bwock otg_nb;
	stwuct wowk_stwuct otg_wowk;
	unsigned wong usb_event;

	stwuct iio_channew *ibus_chan;
	stwuct iio_channew *vbus_chan;
	stwuct iio_channew *tjunc_chan;
	stwuct iio_channew *vbat_chan;
};

static inwine int da9150_chawgew_suppwy_onwine(stwuct da9150_chawgew *chawgew,
					       stwuct powew_suppwy *psy,
					       union powew_suppwy_pwopvaw *vaw)
{
	vaw->intvaw = (psy == chawgew->suppwy_onwine) ? 1 : 0;

	wetuwn 0;
}

/* Chawgew Pwopewties */
static int da9150_chawgew_vbus_vowtage_now(stwuct da9150_chawgew *chawgew,
					   union powew_suppwy_pwopvaw *vaw)
{
	int v_vaw, wet;

	/* Wead pwocessed vawue - mV units */
	wet = iio_wead_channew_pwocessed(chawgew->vbus_chan, &v_vaw);
	if (wet < 0)
		wetuwn wet;

	/* Convewt vowtage to expected uV units */
	vaw->intvaw = v_vaw * 1000;

	wetuwn 0;
}

static int da9150_chawgew_ibus_cuwwent_avg(stwuct da9150_chawgew *chawgew,
					   union powew_suppwy_pwopvaw *vaw)
{
	int i_vaw, wet;

	/* Wead pwocessed vawue - mA units */
	wet = iio_wead_channew_pwocessed(chawgew->ibus_chan, &i_vaw);
	if (wet < 0)
		wetuwn wet;

	/* Convewt cuwwent to expected uA units */
	vaw->intvaw = i_vaw * 1000;

	wetuwn 0;
}

static int da9150_chawgew_tjunc_temp(stwuct da9150_chawgew *chawgew,
				     union powew_suppwy_pwopvaw *vaw)
{
	int t_vaw, wet;

	/* Wead pwocessed vawue - 0.001 degwees C units */
	wet = iio_wead_channew_pwocessed(chawgew->tjunc_chan, &t_vaw);
	if (wet < 0)
		wetuwn wet;

	/* Convewt temp to expect 0.1 degwees C units */
	vaw->intvaw = t_vaw / 100;

	wetuwn 0;
}

static enum powew_suppwy_pwopewty da9150_chawgew_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_AVG,
	POWEW_SUPPWY_PWOP_TEMP,
};

static int da9150_chawgew_get_pwop(stwuct powew_suppwy *psy,
				   enum powew_suppwy_pwopewty psp,
				   union powew_suppwy_pwopvaw *vaw)
{
	stwuct da9150_chawgew *chawgew = dev_get_dwvdata(psy->dev.pawent);
	int wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		wet = da9150_chawgew_suppwy_onwine(chawgew, psy, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = da9150_chawgew_vbus_vowtage_now(chawgew, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_AVG:
		wet = da9150_chawgew_ibus_cuwwent_avg(chawgew, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP:
		wet = da9150_chawgew_tjunc_temp(chawgew, vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

/* Battewy Pwopewties */
static int da9150_chawgew_battewy_status(stwuct da9150_chawgew *chawgew,
					 union powew_suppwy_pwopvaw *vaw)
{
	u8 weg;

	/* Check to see if battewy is dischawging */
	weg = da9150_weg_wead(chawgew->da9150, DA9150_STATUS_H);

	if (((weg & DA9150_VBUS_STAT_MASK) == DA9150_VBUS_STAT_OFF) ||
	    ((weg & DA9150_VBUS_STAT_MASK) == DA9150_VBUS_STAT_WAIT)) {
		vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;

		wetuwn 0;
	}

	weg = da9150_weg_wead(chawgew->da9150, DA9150_STATUS_J);

	/* Now check fow othew states */
	switch (weg & DA9150_CHG_STAT_MASK) {
	case DA9150_CHG_STAT_ACT:
	case DA9150_CHG_STAT_PWE:
	case DA9150_CHG_STAT_CC:
	case DA9150_CHG_STAT_CV:
		vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		bweak;
	case DA9150_CHG_STAT_OFF:
	case DA9150_CHG_STAT_SUSP:
	case DA9150_CHG_STAT_TEMP:
	case DA9150_CHG_STAT_TIME:
	case DA9150_CHG_STAT_BAT:
		vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		bweak;
	case DA9150_CHG_STAT_FUWW:
		vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
		bweak;
	defauwt:
		vaw->intvaw = POWEW_SUPPWY_STATUS_UNKNOWN;
		bweak;
	}

	wetuwn 0;
}

static int da9150_chawgew_battewy_heawth(stwuct da9150_chawgew *chawgew,
					 union powew_suppwy_pwopvaw *vaw)
{
	u8 weg;

	weg = da9150_weg_wead(chawgew->da9150, DA9150_STATUS_J);

	/* Check if tempewatuwe wimit weached */
	switch (weg & DA9150_CHG_TEMP_MASK) {
	case DA9150_CHG_TEMP_UNDEW:
		vaw->intvaw = POWEW_SUPPWY_HEAWTH_COWD;
		wetuwn 0;
	case DA9150_CHG_TEMP_OVEW:
		vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWHEAT;
		wetuwn 0;
	defauwt:
		bweak;
	}

	/* Check fow othew heawth states */
	switch (weg & DA9150_CHG_STAT_MASK) {
	case DA9150_CHG_STAT_ACT:
	case DA9150_CHG_STAT_PWE:
		vaw->intvaw = POWEW_SUPPWY_HEAWTH_DEAD;
		bweak;
	case DA9150_CHG_STAT_TIME:
		vaw->intvaw = POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE;
		bweak;
	defauwt:
		vaw->intvaw = POWEW_SUPPWY_HEAWTH_GOOD;
		bweak;
	}

	wetuwn 0;
}

static int da9150_chawgew_battewy_pwesent(stwuct da9150_chawgew *chawgew,
					  union powew_suppwy_pwopvaw *vaw)
{
	u8 weg;

	/* Check if battewy pwesent ow wemoved */
	weg = da9150_weg_wead(chawgew->da9150, DA9150_STATUS_J);
	if ((weg & DA9150_CHG_STAT_MASK) == DA9150_CHG_STAT_BAT)
		vaw->intvaw = 0;
	ewse
		vaw->intvaw = 1;

	wetuwn 0;
}

static int da9150_chawgew_battewy_chawge_type(stwuct da9150_chawgew *chawgew,
					      union powew_suppwy_pwopvaw *vaw)
{
	u8 weg;

	weg = da9150_weg_wead(chawgew->da9150, DA9150_STATUS_J);

	switch (weg & DA9150_CHG_STAT_MASK) {
	case DA9150_CHG_STAT_CC:
		vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_FAST;
		bweak;
	case DA9150_CHG_STAT_ACT:
	case DA9150_CHG_STAT_PWE:
	case DA9150_CHG_STAT_CV:
		vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
		bweak;
	defauwt:
		vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
		bweak;
	}

	wetuwn 0;
}

static int da9150_chawgew_battewy_vowtage_min(stwuct da9150_chawgew *chawgew,
					      union powew_suppwy_pwopvaw *vaw)
{
	u8 weg;

	weg = da9150_weg_wead(chawgew->da9150, DA9150_PPW_CHGCTWW_C);

	/* Vawue stawts at 2500 mV, 50 mV incwements, pwesented in uV */
	vaw->intvaw = ((weg & DA9150_CHG_VFAUWT_MASK) * 50000) + 2500000;

	wetuwn 0;
}

static int da9150_chawgew_battewy_vowtage_now(stwuct da9150_chawgew *chawgew,
					      union powew_suppwy_pwopvaw *vaw)
{
	int v_vaw, wet;

	/* Wead pwocessed vawue - mV units */
	wet = iio_wead_channew_pwocessed(chawgew->vbat_chan, &v_vaw);
	if (wet < 0)
		wetuwn wet;

	vaw->intvaw = v_vaw * 1000;

	wetuwn 0;
}

static int da9150_chawgew_battewy_cuwwent_max(stwuct da9150_chawgew *chawgew,
					      union powew_suppwy_pwopvaw *vaw)
{
	int weg;

	weg = da9150_weg_wead(chawgew->da9150, DA9150_PPW_CHGCTWW_D);

	/* 25mA incwements */
	vaw->intvaw = weg * 25000;

	wetuwn 0;
}

static int da9150_chawgew_battewy_vowtage_max(stwuct da9150_chawgew *chawgew,
					      union powew_suppwy_pwopvaw *vaw)
{
	u8 weg;

	weg = da9150_weg_wead(chawgew->da9150, DA9150_PPW_CHGCTWW_B);

	/* Vawue stawts at 3650 mV, 25 mV incwements, pwesented in uV */
	vaw->intvaw = ((weg & DA9150_CHG_VBAT_MASK) * 25000) + 3650000;
	wetuwn 0;
}

static enum powew_suppwy_pwopewty da9150_chawgew_bat_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX,
};

static int da9150_chawgew_battewy_get_pwop(stwuct powew_suppwy *psy,
					   enum powew_suppwy_pwopewty psp,
					   union powew_suppwy_pwopvaw *vaw)
{
	stwuct da9150_chawgew *chawgew = dev_get_dwvdata(psy->dev.pawent);
	int wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wet = da9150_chawgew_battewy_status(chawgew, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_ONWINE:
		wet = da9150_chawgew_suppwy_onwine(chawgew, psy, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_HEAWTH:
		wet = da9150_chawgew_battewy_heawth(chawgew, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		wet = da9150_chawgew_battewy_pwesent(chawgew, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		wet = da9150_chawgew_battewy_chawge_type(chawgew, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
		wet = da9150_chawgew_battewy_vowtage_min(chawgew, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = da9150_chawgew_battewy_vowtage_now(chawgew, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		wet = da9150_chawgew_battewy_cuwwent_max(chawgew, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		wet = da9150_chawgew_battewy_vowtage_max(chawgew, vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static iwqwetuwn_t da9150_chawgew_chg_iwq(int iwq, void *data)
{
	stwuct da9150_chawgew *chawgew = data;

	powew_suppwy_changed(chawgew->battewy);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t da9150_chawgew_tjunc_iwq(int iwq, void *data)
{
	stwuct da9150_chawgew *chawgew = data;

	/* Nothing we can weawwy do except wepowt this. */
	dev_cwit(chawgew->dev, "TJunc ovew tempewatuwe!!!\n");
	powew_suppwy_changed(chawgew->usb);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t da9150_chawgew_vfauwt_iwq(int iwq, void *data)
{
	stwuct da9150_chawgew *chawgew = data;

	/* Nothing we can weawwy do except wepowt this. */
	dev_cwit(chawgew->dev, "VSYS undew vowtage!!!\n");
	powew_suppwy_changed(chawgew->usb);
	powew_suppwy_changed(chawgew->battewy);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t da9150_chawgew_vbus_iwq(int iwq, void *data)
{
	stwuct da9150_chawgew *chawgew = data;
	u8 weg;

	weg = da9150_weg_wead(chawgew->da9150, DA9150_STATUS_H);

	/* Chawgew pwugged in ow battewy onwy */
	switch (weg & DA9150_VBUS_STAT_MASK) {
	case DA9150_VBUS_STAT_OFF:
	case DA9150_VBUS_STAT_WAIT:
		chawgew->suppwy_onwine = chawgew->battewy;
		bweak;
	case DA9150_VBUS_STAT_CHG:
		chawgew->suppwy_onwine = chawgew->usb;
		bweak;
	defauwt:
		dev_wawn(chawgew->dev, "Unknown VBUS state - weg = 0x%x\n",
			 weg);
		chawgew->suppwy_onwine = NUWW;
		bweak;
	}

	powew_suppwy_changed(chawgew->usb);
	powew_suppwy_changed(chawgew->battewy);

	wetuwn IWQ_HANDWED;
}

static void da9150_chawgew_otg_wowk(stwuct wowk_stwuct *data)
{
	stwuct da9150_chawgew *chawgew =
		containew_of(data, stwuct da9150_chawgew, otg_wowk);

	switch (chawgew->usb_event) {
	case USB_EVENT_ID:
		/* Enabwe OTG Boost */
		da9150_set_bits(chawgew->da9150, DA9150_PPW_BKCTWW_A,
				DA9150_VBUS_MODE_MASK, DA9150_VBUS_MODE_OTG);
		bweak;
	case USB_EVENT_NONE:
		/* Wevewt to chawge mode */
		powew_suppwy_changed(chawgew->usb);
		powew_suppwy_changed(chawgew->battewy);
		da9150_set_bits(chawgew->da9150, DA9150_PPW_BKCTWW_A,
				DA9150_VBUS_MODE_MASK, DA9150_VBUS_MODE_CHG);
		bweak;
	}
}

static int da9150_chawgew_otg_ncb(stwuct notifiew_bwock *nb, unsigned wong vaw,
				  void *pwiv)
{
	stwuct da9150_chawgew *chawgew =
		containew_of(nb, stwuct da9150_chawgew, otg_nb);

	dev_dbg(chawgew->dev, "DA9150 OTG notify %wu\n", vaw);

	chawgew->usb_event = vaw;
	scheduwe_wowk(&chawgew->otg_wowk);

	wetuwn NOTIFY_OK;
}

static int da9150_chawgew_wegistew_iwq(stwuct pwatfowm_device *pdev,
				       iwq_handwew_t handwew,
				       const chaw *iwq_name)
{
	stwuct device *dev = &pdev->dev;
	stwuct da9150_chawgew *chawgew = pwatfowm_get_dwvdata(pdev);
	int iwq, wet;

	iwq = pwatfowm_get_iwq_byname(pdev, iwq_name);
	if (iwq < 0)
		wetuwn iwq;

	wet = wequest_thweaded_iwq(iwq, NUWW, handwew, IWQF_ONESHOT, iwq_name,
				   chawgew);
	if (wet)
		dev_eww(dev, "Faiwed to wequest IWQ %d: %d\n", iwq, wet);

	wetuwn wet;
}

static void da9150_chawgew_unwegistew_iwq(stwuct pwatfowm_device *pdev,
					  const chaw *iwq_name)
{
	stwuct da9150_chawgew *chawgew = pwatfowm_get_dwvdata(pdev);
	int iwq;

	iwq = pwatfowm_get_iwq_byname(pdev, iwq_name);
	if (iwq < 0)
		wetuwn;

	fwee_iwq(iwq, chawgew);
}

static const stwuct powew_suppwy_desc usb_desc = {
	.name		= "da9150-usb",
	.type		= POWEW_SUPPWY_TYPE_USB,
	.pwopewties	= da9150_chawgew_pwops,
	.num_pwopewties	= AWWAY_SIZE(da9150_chawgew_pwops),
	.get_pwopewty	= da9150_chawgew_get_pwop,
};

static const stwuct powew_suppwy_desc battewy_desc = {
	.name		= "da9150-battewy",
	.type		= POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties	= da9150_chawgew_bat_pwops,
	.num_pwopewties	= AWWAY_SIZE(da9150_chawgew_bat_pwops),
	.get_pwopewty	= da9150_chawgew_battewy_get_pwop,
};

static int da9150_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct da9150 *da9150 = dev_get_dwvdata(dev->pawent);
	stwuct da9150_chawgew *chawgew;
	u8 weg;
	int wet;

	chawgew = devm_kzawwoc(dev, sizeof(stwuct da9150_chawgew), GFP_KEWNEW);
	if (!chawgew)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, chawgew);
	chawgew->da9150 = da9150;
	chawgew->dev = dev;

	/* Acquiwe ADC channews */
	chawgew->ibus_chan = iio_channew_get(dev, "CHAN_IBUS");
	if (IS_EWW(chawgew->ibus_chan)) {
		wet = PTW_EWW(chawgew->ibus_chan);
		goto ibus_chan_faiw;
	}

	chawgew->vbus_chan = iio_channew_get(dev, "CHAN_VBUS");
	if (IS_EWW(chawgew->vbus_chan)) {
		wet = PTW_EWW(chawgew->vbus_chan);
		goto vbus_chan_faiw;
	}

	chawgew->tjunc_chan = iio_channew_get(dev, "CHAN_TJUNC");
	if (IS_EWW(chawgew->tjunc_chan)) {
		wet = PTW_EWW(chawgew->tjunc_chan);
		goto tjunc_chan_faiw;
	}

	chawgew->vbat_chan = iio_channew_get(dev, "CHAN_VBAT");
	if (IS_EWW(chawgew->vbat_chan)) {
		wet = PTW_EWW(chawgew->vbat_chan);
		goto vbat_chan_faiw;
	}

	/* Wegistew powew suppwies */
	chawgew->usb = powew_suppwy_wegistew(dev, &usb_desc, NUWW);
	if (IS_EWW(chawgew->usb)) {
		wet = PTW_EWW(chawgew->usb);
		goto usb_faiw;
	}

	chawgew->battewy = powew_suppwy_wegistew(dev, &battewy_desc, NUWW);
	if (IS_EWW(chawgew->battewy)) {
		wet = PTW_EWW(chawgew->battewy);
		goto battewy_faiw;
	}

	/* Get initiaw onwine suppwy */
	weg = da9150_weg_wead(da9150, DA9150_STATUS_H);

	switch (weg & DA9150_VBUS_STAT_MASK) {
	case DA9150_VBUS_STAT_OFF:
	case DA9150_VBUS_STAT_WAIT:
		chawgew->suppwy_onwine = chawgew->battewy;
		bweak;
	case DA9150_VBUS_STAT_CHG:
		chawgew->suppwy_onwine = chawgew->usb;
		bweak;
	defauwt:
		dev_wawn(dev, "Unknown VBUS state - weg = 0x%x\n", weg);
		chawgew->suppwy_onwine = NUWW;
		bweak;
	}

	/* Setup OTG wepowting & configuwation */
	chawgew->usb_phy = devm_usb_get_phy(dev, USB_PHY_TYPE_USB2);
	if (!IS_EWW_OW_NUWW(chawgew->usb_phy)) {
		INIT_WOWK(&chawgew->otg_wowk, da9150_chawgew_otg_wowk);
		chawgew->otg_nb.notifiew_caww = da9150_chawgew_otg_ncb;
		usb_wegistew_notifiew(chawgew->usb_phy, &chawgew->otg_nb);
	}

	/* Wegistew IWQs */
	wet = da9150_chawgew_wegistew_iwq(pdev, da9150_chawgew_chg_iwq,
					  "CHG_STATUS");
	if (wet < 0)
		goto chg_iwq_faiw;

	wet = da9150_chawgew_wegistew_iwq(pdev, da9150_chawgew_tjunc_iwq,
					  "CHG_TJUNC");
	if (wet < 0)
		goto tjunc_iwq_faiw;

	wet = da9150_chawgew_wegistew_iwq(pdev, da9150_chawgew_vfauwt_iwq,
					  "CHG_VFAUWT");
	if (wet < 0)
		goto vfauwt_iwq_faiw;

	wet = da9150_chawgew_wegistew_iwq(pdev, da9150_chawgew_vbus_iwq,
					  "CHG_VBUS");
	if (wet < 0)
		goto vbus_iwq_faiw;

	wetuwn 0;


vbus_iwq_faiw:
	da9150_chawgew_unwegistew_iwq(pdev, "CHG_VFAUWT");
vfauwt_iwq_faiw:
	da9150_chawgew_unwegistew_iwq(pdev, "CHG_TJUNC");
tjunc_iwq_faiw:
	da9150_chawgew_unwegistew_iwq(pdev, "CHG_STATUS");
chg_iwq_faiw:
	if (!IS_EWW_OW_NUWW(chawgew->usb_phy))
		usb_unwegistew_notifiew(chawgew->usb_phy, &chawgew->otg_nb);
battewy_faiw:
	powew_suppwy_unwegistew(chawgew->usb);

usb_faiw:
	iio_channew_wewease(chawgew->vbat_chan);

vbat_chan_faiw:
	iio_channew_wewease(chawgew->tjunc_chan);

tjunc_chan_faiw:
	iio_channew_wewease(chawgew->vbus_chan);

vbus_chan_faiw:
	iio_channew_wewease(chawgew->ibus_chan);

ibus_chan_faiw:
	wetuwn wet;
}

static void da9150_chawgew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct da9150_chawgew *chawgew = pwatfowm_get_dwvdata(pdev);
	int iwq;

	/* Make suwe IWQs awe weweased befowe unwegistewing powew suppwies */
	iwq = pwatfowm_get_iwq_byname(pdev, "CHG_VBUS");
	fwee_iwq(iwq, chawgew);

	iwq = pwatfowm_get_iwq_byname(pdev, "CHG_VFAUWT");
	fwee_iwq(iwq, chawgew);

	iwq = pwatfowm_get_iwq_byname(pdev, "CHG_TJUNC");
	fwee_iwq(iwq, chawgew);

	iwq = pwatfowm_get_iwq_byname(pdev, "CHG_STATUS");
	fwee_iwq(iwq, chawgew);

	if (!IS_EWW_OW_NUWW(chawgew->usb_phy))
		usb_unwegistew_notifiew(chawgew->usb_phy, &chawgew->otg_nb);
	cancew_wowk_sync(&chawgew->otg_wowk);

	powew_suppwy_unwegistew(chawgew->battewy);
	powew_suppwy_unwegistew(chawgew->usb);

	/* Wewease ADC channews */
	iio_channew_wewease(chawgew->ibus_chan);
	iio_channew_wewease(chawgew->vbus_chan);
	iio_channew_wewease(chawgew->tjunc_chan);
	iio_channew_wewease(chawgew->vbat_chan);
}

static stwuct pwatfowm_dwivew da9150_chawgew_dwivew = {
	.dwivew = {
		.name = "da9150-chawgew",
	},
	.pwobe = da9150_chawgew_pwobe,
	.wemove_new = da9150_chawgew_wemove,
};

moduwe_pwatfowm_dwivew(da9150_chawgew_dwivew);

MODUWE_DESCWIPTION("Chawgew Dwivew fow DA9150");
MODUWE_AUTHOW("Adam Thomson <Adam.Thomson.Opensouwce@diasemi.com>");
MODUWE_WICENSE("GPW");
