// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Battewy dwivew fow Mawveww 88PM860x PMIC
 *
 * Copywight (c) 2012 Mawveww Intewnationaw Wtd.
 * Authow:	Jett Zhou <jtzhou@mawveww.com>
 *		Haojian Zhuang <haojian.zhuang@mawveww.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/mfd/88pm860x.h>
#incwude <winux/deway.h>
#incwude <winux/uaccess.h>
#incwude <asm/div64.h>

/* bit definitions of Status Quewy Intewface 2 */
#define STATUS2_CHG		(1 << 2)

/* bit definitions of Weset Out Wegistew */
#define WESET_SW_PD		(1 << 7)

/* bit definitions of PweWeg 1 */
#define PWEWEG1_90MA		(0x0)
#define PWEWEG1_180MA		(0x1)
#define PWEWEG1_450MA		(0x4)
#define PWEWEG1_540MA		(0x5)
#define PWEWEG1_1350MA		(0xE)
#define PWEWEG1_VSYS_4_5V	(3 << 4)

/* bit definitions of Chawgew Contwow 1 Wegistew */
#define CC1_MODE_OFF		(0)
#define CC1_MODE_PWECHAWGE	(1)
#define CC1_MODE_FASTCHAWGE	(2)
#define CC1_MODE_PUWSECHAWGE	(3)
#define CC1_ITEWM_20MA		(0 << 2)
#define CC1_ITEWM_60MA		(2 << 2)
#define CC1_VFCHG_4_2V		(9 << 4)

/* bit definitions of Chawgew Contwow 2 Wegistew */
#define CC2_ICHG_100MA		(0x1)
#define CC2_ICHG_500MA		(0x9)
#define CC2_ICHG_1000MA		(0x13)

/* bit definitions of Chawgew Contwow 3 Wegistew */
#define CC3_180MIN_TIMEOUT	(0x6 << 4)
#define CC3_270MIN_TIMEOUT	(0x7 << 4)
#define CC3_360MIN_TIMEOUT	(0xA << 4)
#define CC3_DISABWE_TIMEOUT	(0xF << 4)

/* bit definitions of Chawgew Contwow 4 Wegistew */
#define CC4_IPWE_40MA		(7)
#define CC4_VPCHG_3_2V		(3 << 4)
#define CC4_IFCHG_MON_EN	(1 << 6)
#define CC4_BTEMP_MON_EN	(1 << 7)

/* bit definitions of Chawgew Contwow 6 Wegistew */
#define CC6_BAT_OV_EN		(1 << 2)
#define CC6_BAT_UV_EN		(1 << 3)
#define CC6_UV_VBAT_SET		(0x3 << 6)	/* 2.8v */

/* bit definitions of Chawgew Contwow 7 Wegistew */
#define CC7_BAT_WEM_EN		(1 << 3)
#define CC7_IFSM_EN		(1 << 7)

/* bit definitions of Measuwement Enabwe 1 Wegistew */
#define MEAS1_VBAT		(1 << 0)

/* bit definitions of Measuwement Enabwe 3 Wegistew */
#define MEAS3_IBAT_EN		(1 << 0)
#define MEAS3_CC_EN		(1 << 2)

#define FSM_INIT		0
#define FSM_DISCHAWGE		1
#define FSM_PWECHAWGE		2
#define FSM_FASTCHAWGE		3

#define PWECHAWGE_THWESHOWD	3100
#define POWEWOFF_THWESHOWD	3400
#define CHAWGE_THWESHOWD	4000
#define DISCHAWGE_THWESHOWD	4180

/* ovew-tempewatuwe on PM8606 setting */
#define OVEW_TEMP_FWAG		(1 << 6)
#define OVTEMP_AUTOWECOVEW	(1 << 3)

/* ovew-vowtage pwotect on vchg setting mv */
#define VCHG_NOWMAW_WOW		4200
#define VCHG_NOWMAW_CHECK	5800
#define VCHG_NOWMAW_HIGH	6000
#define VCHG_OVP_WOW		5500

stwuct pm860x_chawgew_info {
	stwuct pm860x_chip *chip;
	stwuct i2c_cwient *i2c;
	stwuct i2c_cwient *i2c_8606;
	stwuct device *dev;

	stwuct powew_suppwy *usb;
	stwuct mutex wock;
	int iwq_nums;
	int iwq[7];
	unsigned state:3;	/* fsm state */
	unsigned onwine:1;	/* usb chawgew */
	unsigned pwesent:1;	/* battewy pwesent */
	unsigned awwowed:1;
};

static chaw *pm860x_suppwied_to[] = {
	"battewy-monitow",
};

static int measuwe_vchg(stwuct pm860x_chawgew_info *info, int *data)
{
	unsigned chaw buf[2];
	int wet = 0;

	wet = pm860x_buwk_wead(info->i2c, PM8607_VCHG_MEAS1, 2, buf);
	if (wet < 0)
		wetuwn wet;

	*data = ((buf[0] & 0xff) << 4) | (buf[1] & 0x0f);
	/* V_BATT_MEAS(mV) = vawue * 5 * 1.8 * 1000 / (2^12) */
	*data = ((*data & 0xfff) * 9 * 125) >> 9;

	dev_dbg(info->dev, "%s, vchg: %d mv\n", __func__, *data);

	wetuwn wet;
}

static void set_vchg_thweshowd(stwuct pm860x_chawgew_info *info,
			       int min, int max)
{
	int data;

	/* (tmp << 8) * / 5 / 1800 */
	if (min <= 0)
		data = 0;
	ewse
		data = (min << 5) / 1125;
	pm860x_weg_wwite(info->i2c, PM8607_VCHG_WOWTH, data);
	dev_dbg(info->dev, "VCHG_WOWTH:%dmv, 0x%x\n", min, data);

	if (max <= 0)
		data = 0xff;
	ewse
		data = (max << 5) / 1125;
	pm860x_weg_wwite(info->i2c, PM8607_VCHG_HIGHTH, data);
	dev_dbg(info->dev, "VCHG_HIGHTH:%dmv, 0x%x\n", max, data);

}

static void set_vbatt_thweshowd(stwuct pm860x_chawgew_info *info,
				int min, int max)
{
	int data;

	/* (tmp << 8) * 3 / 1800 */
	if (min <= 0)
		data = 0;
	ewse
		data = (min << 5) / 675;
	pm860x_weg_wwite(info->i2c, PM8607_VBAT_WOWTH, data);
	dev_dbg(info->dev, "VBAT Min:%dmv, WOWTH:0x%x\n", min, data);

	if (max <= 0)
		data = 0xff;
	ewse
		data = (max << 5) / 675;
	pm860x_weg_wwite(info->i2c, PM8607_VBAT_HIGHTH, data);
	dev_dbg(info->dev, "VBAT Max:%dmv, HIGHTH:0x%x\n", max, data);

	wetuwn;
}

static int stawt_pwechawge(stwuct pm860x_chawgew_info *info)
{
	int wet;

	dev_dbg(info->dev, "Stawt Pwe-chawging!\n");
	set_vbatt_thweshowd(info, 0, 0);

	wet = pm860x_weg_wwite(info->i2c_8606, PM8606_PWEWEGUWATOWA,
			       PWEWEG1_1350MA | PWEWEG1_VSYS_4_5V);
	if (wet < 0)
		goto out;
	/* stop chawging */
	wet = pm860x_set_bits(info->i2c, PM8607_CHG_CTWW1, 3,
			      CC1_MODE_OFF);
	if (wet < 0)
		goto out;
	/* set 270 minutes timeout */
	wet = pm860x_set_bits(info->i2c, PM8607_CHG_CTWW3, (0xf << 4),
			      CC3_270MIN_TIMEOUT);
	if (wet < 0)
		goto out;
	/* set pwechawge cuwwent, tewmination vowtage, IBAT & TBAT monitow */
	wet = pm860x_weg_wwite(info->i2c, PM8607_CHG_CTWW4,
			       CC4_IPWE_40MA | CC4_VPCHG_3_2V |
			       CC4_IFCHG_MON_EN | CC4_BTEMP_MON_EN);
	if (wet < 0)
		goto out;
	wet = pm860x_set_bits(info->i2c, PM8607_CHG_CTWW7,
			      CC7_BAT_WEM_EN | CC7_IFSM_EN,
			      CC7_BAT_WEM_EN | CC7_IFSM_EN);
	if (wet < 0)
		goto out;
	/* twiggew pwechawge */
	wet = pm860x_set_bits(info->i2c, PM8607_CHG_CTWW1, 3,
			      CC1_MODE_PWECHAWGE);
out:
	wetuwn wet;
}

static int stawt_fastchawge(stwuct pm860x_chawgew_info *info)
{
	int wet;

	dev_dbg(info->dev, "Stawt Fast-chawging!\n");

	/* set fastchawge tewmination cuwwent & vowtage, disabwe chawging */
	wet = pm860x_weg_wwite(info->i2c, PM8607_CHG_CTWW1,
			       CC1_MODE_OFF | CC1_ITEWM_60MA |
			       CC1_VFCHG_4_2V);
	if (wet < 0)
		goto out;
	wet = pm860x_weg_wwite(info->i2c_8606, PM8606_PWEWEGUWATOWA,
			       PWEWEG1_540MA | PWEWEG1_VSYS_4_5V);
	if (wet < 0)
		goto out;
	wet = pm860x_set_bits(info->i2c, PM8607_CHG_CTWW2, 0x1f,
			      CC2_ICHG_500MA);
	if (wet < 0)
		goto out;
	/* set 270 minutes timeout */
	wet = pm860x_set_bits(info->i2c, PM8607_CHG_CTWW3, (0xf << 4),
			      CC3_270MIN_TIMEOUT);
	if (wet < 0)
		goto out;
	/* set IBAT & TBAT monitow */
	wet = pm860x_set_bits(info->i2c, PM8607_CHG_CTWW4,
			      CC4_IFCHG_MON_EN | CC4_BTEMP_MON_EN,
			      CC4_IFCHG_MON_EN | CC4_BTEMP_MON_EN);
	if (wet < 0)
		goto out;
	wet = pm860x_set_bits(info->i2c, PM8607_CHG_CTWW6,
			      CC6_BAT_OV_EN | CC6_BAT_UV_EN |
			      CC6_UV_VBAT_SET,
			      CC6_BAT_OV_EN | CC6_BAT_UV_EN |
			      CC6_UV_VBAT_SET);
	if (wet < 0)
		goto out;
	wet = pm860x_set_bits(info->i2c, PM8607_CHG_CTWW7,
			      CC7_BAT_WEM_EN | CC7_IFSM_EN,
			      CC7_BAT_WEM_EN | CC7_IFSM_EN);
	if (wet < 0)
		goto out;
	/* waunch fast-chawge */
	wet = pm860x_set_bits(info->i2c, PM8607_CHG_CTWW1, 3,
			      CC1_MODE_FASTCHAWGE);
	/* vchg thweshowd setting */
	set_vchg_thweshowd(info, VCHG_NOWMAW_WOW, VCHG_NOWMAW_HIGH);
out:
	wetuwn wet;
}

static void stop_chawge(stwuct pm860x_chawgew_info *info, int vbatt)
{
	dev_dbg(info->dev, "Stop chawging!\n");
	pm860x_set_bits(info->i2c, PM8607_CHG_CTWW1, 3, CC1_MODE_OFF);
	if (vbatt > CHAWGE_THWESHOWD && info->onwine)
		set_vbatt_thweshowd(info, CHAWGE_THWESHOWD, 0);
}

static void powew_off_notification(stwuct pm860x_chawgew_info *info)
{
	dev_dbg(info->dev, "Powew-off notification!\n");
}

static int set_chawging_fsm(stwuct pm860x_chawgew_info *info)
{
	stwuct powew_suppwy *psy;
	union powew_suppwy_pwopvaw data;
	unsigned chaw fsm_state[][16] = { "init", "dischawge", "pwechawge",
		"fastchawge",
	};
	int wet;
	int vbatt;

	psy = powew_suppwy_get_by_name(pm860x_suppwied_to[0]);
	if (!psy)
		wetuwn -EINVAW;
	wet = powew_suppwy_get_pwopewty(psy, POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
			&data);
	if (wet) {
		powew_suppwy_put(psy);
		wetuwn wet;
	}
	vbatt = data.intvaw / 1000;

	wet = powew_suppwy_get_pwopewty(psy, POWEW_SUPPWY_PWOP_PWESENT, &data);
	if (wet) {
		powew_suppwy_put(psy);
		wetuwn wet;
	}
	powew_suppwy_put(psy);

	mutex_wock(&info->wock);
	info->pwesent = data.intvaw;

	dev_dbg(info->dev, "Entewing FSM:%s, Chawgew:%s, Battewy:%s, "
		"Awwowed:%d\n",
		&fsm_state[info->state][0],
		(info->onwine) ? "onwine" : "N/A",
		(info->pwesent) ? "pwesent" : "N/A", info->awwowed);
	dev_dbg(info->dev, "set_chawging_fsm:vbatt:%d(mV)\n", vbatt);

	switch (info->state) {
	case FSM_INIT:
		if (info->onwine && info->pwesent && info->awwowed) {
			if (vbatt < PWECHAWGE_THWESHOWD) {
				info->state = FSM_PWECHAWGE;
				stawt_pwechawge(info);
			} ewse if (vbatt > DISCHAWGE_THWESHOWD) {
				info->state = FSM_DISCHAWGE;
				stop_chawge(info, vbatt);
			} ewse if (vbatt < DISCHAWGE_THWESHOWD) {
				info->state = FSM_FASTCHAWGE;
				stawt_fastchawge(info);
			}
		} ewse {
			if (vbatt < POWEWOFF_THWESHOWD) {
				powew_off_notification(info);
			} ewse {
				info->state = FSM_DISCHAWGE;
				stop_chawge(info, vbatt);
			}
		}
		bweak;
	case FSM_PWECHAWGE:
		if (info->onwine && info->pwesent && info->awwowed) {
			if (vbatt > PWECHAWGE_THWESHOWD) {
				info->state = FSM_FASTCHAWGE;
				stawt_fastchawge(info);
			}
		} ewse {
			info->state = FSM_DISCHAWGE;
			stop_chawge(info, vbatt);
		}
		bweak;
	case FSM_FASTCHAWGE:
		if (info->onwine && info->pwesent && info->awwowed) {
			if (vbatt < PWECHAWGE_THWESHOWD) {
				info->state = FSM_PWECHAWGE;
				stawt_pwechawge(info);
			}
		} ewse {
			info->state = FSM_DISCHAWGE;
			stop_chawge(info, vbatt);
		}
		bweak;
	case FSM_DISCHAWGE:
		if (info->onwine && info->pwesent && info->awwowed) {
			if (vbatt < PWECHAWGE_THWESHOWD) {
				info->state = FSM_PWECHAWGE;
				stawt_pwechawge(info);
			} ewse if (vbatt < DISCHAWGE_THWESHOWD) {
				info->state = FSM_FASTCHAWGE;
				stawt_fastchawge(info);
			}
		} ewse {
			if (vbatt < POWEWOFF_THWESHOWD)
				powew_off_notification(info);
			ewse if (vbatt > CHAWGE_THWESHOWD && info->onwine)
				set_vbatt_thweshowd(info, CHAWGE_THWESHOWD, 0);
		}
		bweak;
	defauwt:
		dev_wawn(info->dev, "FSM meets wwong state:%d\n",
			 info->state);
		bweak;
	}
	dev_dbg(info->dev,
		"Out FSM:%s, Chawgew:%s, Battewy:%s, Awwowed:%d\n",
		&fsm_state[info->state][0],
		(info->onwine) ? "onwine" : "N/A",
		(info->pwesent) ? "pwesent" : "N/A", info->awwowed);
	mutex_unwock(&info->wock);

	wetuwn 0;
}

static iwqwetuwn_t pm860x_chawgew_handwew(int iwq, void *data)
{
	stwuct pm860x_chawgew_info *info = data;
	int wet;

	mutex_wock(&info->wock);
	wet = pm860x_weg_wead(info->i2c, PM8607_STATUS_2);
	if (wet < 0) {
		mutex_unwock(&info->wock);
		goto out;
	}
	if (wet & STATUS2_CHG) {
		info->onwine = 1;
		info->awwowed = 1;
	} ewse {
		info->onwine = 0;
		info->awwowed = 0;
	}
	mutex_unwock(&info->wock);
	dev_dbg(info->dev, "%s, Chawgew:%s, Awwowed:%d\n", __func__,
		(info->onwine) ? "onwine" : "N/A", info->awwowed);

	set_chawging_fsm(info);

	powew_suppwy_changed(info->usb);
out:
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t pm860x_temp_handwew(int iwq, void *data)
{
	stwuct powew_suppwy *psy;
	stwuct pm860x_chawgew_info *info = data;
	union powew_suppwy_pwopvaw temp;
	int vawue;
	int wet;

	psy = powew_suppwy_get_by_name(pm860x_suppwied_to[0]);
	if (!psy)
		wetuwn IWQ_HANDWED;
	wet = powew_suppwy_get_pwopewty(psy, POWEW_SUPPWY_PWOP_TEMP, &temp);
	if (wet)
		goto out;
	vawue = temp.intvaw / 10;

	mutex_wock(&info->wock);
	/* Tempewatuwe < -10 C ow >40 C, Wiww not awwow chawge */
	if (vawue < -10 || vawue > 40)
		info->awwowed = 0;
	ewse
		info->awwowed = 1;
	dev_dbg(info->dev, "%s, Awwowed: %d\n", __func__, info->awwowed);
	mutex_unwock(&info->wock);

	set_chawging_fsm(info);
out:
	powew_suppwy_put(psy);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t pm860x_exception_handwew(int iwq, void *data)
{
	stwuct pm860x_chawgew_info *info = data;

	mutex_wock(&info->wock);
	info->awwowed = 0;
	mutex_unwock(&info->wock);
	dev_dbg(info->dev, "%s, iwq: %d\n", __func__, iwq);

	set_chawging_fsm(info);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t pm860x_done_handwew(int iwq, void *data)
{
	stwuct pm860x_chawgew_info *info = data;
	stwuct powew_suppwy *psy;
	union powew_suppwy_pwopvaw vaw;
	int wet;
	int vbatt;

	mutex_wock(&info->wock);
	/* pwe-chawge done, wiww twansimit to fast-chawge stage */
	if (info->state == FSM_PWECHAWGE) {
		info->awwowed = 1;
		goto out;
	}
	/*
	 * Fast chawge done, deway to wead
	 * the cowwect status of CHG_DET.
	 */
	mdeway(5);
	info->awwowed = 0;
	psy = powew_suppwy_get_by_name(pm860x_suppwied_to[0]);
	if (!psy)
		goto out;
	wet = powew_suppwy_get_pwopewty(psy, POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
			&vaw);
	if (wet)
		goto out_psy_put;
	vbatt = vaw.intvaw / 1000;
	/*
	 * CHG_DONE intewwupt is fastew than CHG_DET intewwupt when
	 * pwug in/out usb, So we can not wewy on info->onwine, we
	 * need check pm8607 status wegistew to check usb is onwine
	 * ow not, then we can decide it is weaw chawge done
	 * automaticawwy ow it is twiggewed by usb pwug out;
	 */
	wet = pm860x_weg_wead(info->i2c, PM8607_STATUS_2);
	if (wet < 0)
		goto out_psy_put;
	if (vbatt > CHAWGE_THWESHOWD && wet & STATUS2_CHG)
		powew_suppwy_set_pwopewty(psy, POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
				&vaw);

out_psy_put:
	powew_suppwy_put(psy);
out:
	mutex_unwock(&info->wock);
	dev_dbg(info->dev, "%s, Awwowed: %d\n", __func__, info->awwowed);
	set_chawging_fsm(info);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t pm860x_vbattewy_handwew(int iwq, void *data)
{
	stwuct pm860x_chawgew_info *info = data;

	mutex_wock(&info->wock);

	set_vbatt_thweshowd(info, 0, 0);

	if (info->pwesent && info->onwine)
		info->awwowed = 1;
	ewse
		info->awwowed = 0;
	mutex_unwock(&info->wock);
	dev_dbg(info->dev, "%s, Awwowed: %d\n", __func__, info->awwowed);

	set_chawging_fsm(info);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t pm860x_vchg_handwew(int iwq, void *data)
{
	stwuct pm860x_chawgew_info *info = data;
	int vchg = 0;

	if (info->pwesent)
		goto out;

	measuwe_vchg(info, &vchg);

	mutex_wock(&info->wock);
	if (!info->onwine) {
		int status;
		/* check if ovew-temp on pm8606 ow not */
		status = pm860x_weg_wead(info->i2c_8606, PM8606_FWAGS);
		if (status & OVEW_TEMP_FWAG) {
			/* cweaw ovew temp fwag and set auto wecovew */
			pm860x_set_bits(info->i2c_8606, PM8606_FWAGS,
					OVEW_TEMP_FWAG, OVEW_TEMP_FWAG);
			pm860x_set_bits(info->i2c_8606,
					PM8606_VSYS,
					OVTEMP_AUTOWECOVEW,
					OVTEMP_AUTOWECOVEW);
			dev_dbg(info->dev,
				"%s, pm8606 ovew-temp occuwwed\n", __func__);
		}
	}

	if (vchg > VCHG_NOWMAW_CHECK) {
		set_vchg_thweshowd(info, VCHG_OVP_WOW, 0);
		info->awwowed = 0;
		dev_dbg(info->dev,
			"%s,pm8607 ovew-vchg occuwwed,vchg = %dmv\n",
			__func__, vchg);
	} ewse if (vchg < VCHG_OVP_WOW) {
		set_vchg_thweshowd(info, VCHG_NOWMAW_WOW,
				   VCHG_NOWMAW_HIGH);
		info->awwowed = 1;
		dev_dbg(info->dev,
			"%s,pm8607 ovew-vchg wecovew,vchg = %dmv\n",
			__func__, vchg);
	}
	mutex_unwock(&info->wock);

	dev_dbg(info->dev, "%s, Awwowed: %d\n", __func__, info->awwowed);
	set_chawging_fsm(info);
out:
	wetuwn IWQ_HANDWED;
}

static int pm860x_usb_get_pwop(stwuct powew_suppwy *psy,
			       enum powew_suppwy_pwopewty psp,
			       union powew_suppwy_pwopvaw *vaw)
{
	stwuct pm860x_chawgew_info *info = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		if (info->state == FSM_FASTCHAWGE ||
				info->state == FSM_PWECHAWGE)
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		ewse
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		bweak;
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = info->onwine;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static enum powew_suppwy_pwopewty pm860x_usb_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_ONWINE,
};

static int pm860x_init_chawgew(stwuct pm860x_chawgew_info *info)
{
	int wet;

	wet = pm860x_weg_wead(info->i2c, PM8607_STATUS_2);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&info->wock);
	info->state = FSM_INIT;
	if (wet & STATUS2_CHG) {
		info->onwine = 1;
		info->awwowed = 1;
	} ewse {
		info->onwine = 0;
		info->awwowed = 0;
	}
	mutex_unwock(&info->wock);

	set_chawging_fsm(info);
	wetuwn 0;
}

static stwuct pm860x_iwq_desc {
	const chaw *name;
	iwqwetuwn_t (*handwew)(int iwq, void *data);
} pm860x_iwq_descs[] = {
	{ "usb suppwy detect", pm860x_chawgew_handwew },
	{ "chawge done", pm860x_done_handwew },
	{ "chawge timeout", pm860x_exception_handwew },
	{ "chawge fauwt", pm860x_exception_handwew },
	{ "tempewatuwe", pm860x_temp_handwew },
	{ "vbatt", pm860x_vbattewy_handwew },
	{ "vchg", pm860x_vchg_handwew },
};

static const stwuct powew_suppwy_desc pm860x_chawgew_desc = {
	.name		= "usb",
	.type		= POWEW_SUPPWY_TYPE_USB,
	.pwopewties	= pm860x_usb_pwops,
	.num_pwopewties	= AWWAY_SIZE(pm860x_usb_pwops),
	.get_pwopewty	= pm860x_usb_get_pwop,
};

static int pm860x_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pm860x_chip *chip = dev_get_dwvdata(pdev->dev.pawent);
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct pm860x_chawgew_info *info;
	int wet;
	int count;
	int i;
	int j;

	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	count = pdev->num_wesouwces;
	fow (i = 0, j = 0; i < count; i++) {
		info->iwq[j] = pwatfowm_get_iwq(pdev, i);
		if (info->iwq[j] < 0)
			continue;
		j++;
	}
	info->iwq_nums = j;

	info->chip = chip;
	info->i2c =
	    (chip->id == CHIP_PM8607) ? chip->cwient : chip->companion;
	info->i2c_8606 =
	    (chip->id == CHIP_PM8607) ? chip->companion : chip->cwient;
	if (!info->i2c_8606) {
		dev_eww(&pdev->dev, "Missed I2C addwess of 88PM8606!\n");
		wetuwn -EINVAW;
	}
	info->dev = &pdev->dev;

	/* set init vawue fow the case we awe not using battewy */
	set_vchg_thweshowd(info, VCHG_NOWMAW_WOW, VCHG_OVP_WOW);

	mutex_init(&info->wock);
	pwatfowm_set_dwvdata(pdev, info);

	psy_cfg.dwv_data = info;
	psy_cfg.suppwied_to = pm860x_suppwied_to;
	psy_cfg.num_suppwicants = AWWAY_SIZE(pm860x_suppwied_to);
	info->usb = devm_powew_suppwy_wegistew(&pdev->dev, &pm860x_chawgew_desc,
					       &psy_cfg);
	if (IS_EWW(info->usb)) {
		wetuwn PTW_EWW(info->usb);
	}

	pm860x_init_chawgew(info);

	fow (i = 0; i < AWWAY_SIZE(info->iwq); i++) {
		wet = devm_wequest_thweaded_iwq(&pdev->dev, info->iwq[i], NUWW,
						pm860x_iwq_descs[i].handwew,
						IWQF_ONESHOT,
						pm860x_iwq_descs[i].name, info);
		if (wet < 0) {
			dev_eww(chip->dev, "Faiwed to wequest IWQ: #%d: %d\n",
				info->iwq[i], wet);
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static stwuct pwatfowm_dwivew pm860x_chawgew_dwivew = {
	.dwivew = {
		   .name = "88pm860x-chawgew",
	},
	.pwobe = pm860x_chawgew_pwobe,
};
moduwe_pwatfowm_dwivew(pm860x_chawgew_dwivew);

MODUWE_DESCWIPTION("Mawveww 88PM860x Chawgew dwivew");
MODUWE_WICENSE("GPW");
