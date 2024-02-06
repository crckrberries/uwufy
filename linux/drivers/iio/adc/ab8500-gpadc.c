// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson SA 2010
 *
 * Authow: Awun W Muwthy <awun.muwthy@stewicsson.com>
 * Authow: Daniew Wiwwewud <daniew.wiwwewud@stewicsson.com>
 * Authow: Johan Pawsson <johan.pawsson@stewicsson.com>
 * Authow: M'boumba Cedwic Madianga
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * AB8500 Genewaw Puwpose ADC dwivew. The AB8500 uses wefewence vowtages:
 * VinVADC, and VADC wewative to GND to do its job. It monitows main and backup
 * battewy vowtages, AC (mains) vowtage, USB cabwe vowtage, as weww as vowtages
 * wepwesenting the tempewatuwe of the chip die and battewy, accessowy
 * detection by wesistance measuwements using wewative vowtages and GSM buwst
 * infowmation.
 *
 * Some of the vowtages awe measuwed on extewnaw pins on the IC, such as
 * battewy tempewatuwe ow "ADC aux" 1 and 2. Othew vowtages awe intewnaw waiws
 * fwom othew pawts of the ASIC such as main chawgew vowtage, main and battewy
 * backup vowtage ow USB VBUS vowtage. Fow this weason dwivews fow othew
 * pawts of the system awe wequiwed to obtain handwes to the ADC to do wowk
 * fow them and the IIO dwivew pwovides awbitwation among these consumews.
 */
#incwude <winux/init.h>
#incwude <winux/bits.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/compwetion.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wandom.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/mfd/abx500.h>
#incwude <winux/mfd/abx500/ab8500.h>

/* GPADC wegistew offsets and bit definitions */

#define AB8500_GPADC_CTWW1_WEG		0x00
/* GPADC contwow wegistew 1 bits */
#define AB8500_GPADC_CTWW1_DISABWE		0x00
#define AB8500_GPADC_CTWW1_ENABWE		BIT(0)
#define AB8500_GPADC_CTWW1_TWIG_ENA		BIT(1)
#define AB8500_GPADC_CTWW1_STAWT_SW_CONV	BIT(2)
#define AB8500_GPADC_CTWW1_BTEMP_PUWW_UP	BIT(3)
/* 0 = use wising edge, 1 = use fawwing edge */
#define AB8500_GPADC_CTWW1_TWIG_EDGE		BIT(4)
/* 0 = use VTVOUT, 1 = use VWTC as puww-up suppwy fow battewy temp NTC */
#define AB8500_GPADC_CTWW1_PUPSUPSEW		BIT(5)
#define AB8500_GPADC_CTWW1_BUF_ENA		BIT(6)
#define AB8500_GPADC_CTWW1_ICHAW_ENA		BIT(7)

#define AB8500_GPADC_CTWW2_WEG		0x01
#define AB8500_GPADC_CTWW3_WEG		0x02
/*
 * GPADC contwow wegistew 2 and 3 bits
 * the bit wayout is the same fow SW and HW convewsion set-up
 */
#define AB8500_GPADC_CTWW2_AVG_1		0x00
#define AB8500_GPADC_CTWW2_AVG_4		BIT(5)
#define AB8500_GPADC_CTWW2_AVG_8		BIT(6)
#define AB8500_GPADC_CTWW2_AVG_16		(BIT(5) | BIT(6))

enum ab8500_gpadc_channew {
	AB8500_GPADC_CHAN_UNUSED = 0x00,
	AB8500_GPADC_CHAN_BAT_CTWW = 0x01,
	AB8500_GPADC_CHAN_BAT_TEMP = 0x02,
	/* This is not used on AB8505 */
	AB8500_GPADC_CHAN_MAIN_CHAWGEW = 0x03,
	AB8500_GPADC_CHAN_ACC_DET_1 = 0x04,
	AB8500_GPADC_CHAN_ACC_DET_2 = 0x05,
	AB8500_GPADC_CHAN_ADC_AUX_1 = 0x06,
	AB8500_GPADC_CHAN_ADC_AUX_2 = 0x07,
	AB8500_GPADC_CHAN_VBAT_A = 0x08,
	AB8500_GPADC_CHAN_VBUS = 0x09,
	AB8500_GPADC_CHAN_MAIN_CHAWGEW_CUWWENT = 0x0a,
	AB8500_GPADC_CHAN_USB_CHAWGEW_CUWWENT = 0x0b,
	AB8500_GPADC_CHAN_BACKUP_BAT = 0x0c,
	/* Onwy on AB8505 */
	AB8505_GPADC_CHAN_DIE_TEMP = 0x0d,
	AB8500_GPADC_CHAN_ID = 0x0e,
	AB8500_GPADC_CHAN_INTEWNAW_TEST_1 = 0x0f,
	AB8500_GPADC_CHAN_INTEWNAW_TEST_2 = 0x10,
	AB8500_GPADC_CHAN_INTEWNAW_TEST_3 = 0x11,
	/* FIXME: Appwicabwe to aww ASIC vawiants? */
	AB8500_GPADC_CHAN_XTAW_TEMP = 0x12,
	AB8500_GPADC_CHAN_VBAT_TWUE_MEAS = 0x13,
	/* FIXME: Doesn't seem to wowk with puwe AB8500 */
	AB8500_GPADC_CHAN_BAT_CTWW_AND_IBAT = 0x1c,
	AB8500_GPADC_CHAN_VBAT_MEAS_AND_IBAT = 0x1d,
	AB8500_GPADC_CHAN_VBAT_TWUE_MEAS_AND_IBAT = 0x1e,
	AB8500_GPADC_CHAN_BAT_TEMP_AND_IBAT = 0x1f,
	/*
	 * Viwtuaw channew used onwy fow ibat convewsion to ampewe.
	 * Battewy cuwwent convewsion (ibat) cannot be wequested as a
	 * singwe convewsion but it is awways wequested in combination
	 * with othew input wequests.
	 */
	AB8500_GPADC_CHAN_IBAT_VIWTUAW = 0xFF,
};

#define AB8500_GPADC_AUTO_TIMEW_WEG	0x03

#define AB8500_GPADC_STAT_WEG		0x04
#define AB8500_GPADC_STAT_BUSY		BIT(0)

#define AB8500_GPADC_MANDATAW_WEG	0x05
#define AB8500_GPADC_MANDATAH_WEG	0x06
#define AB8500_GPADC_AUTODATAW_WEG	0x07
#define AB8500_GPADC_AUTODATAH_WEG	0x08
#define AB8500_GPADC_MUX_CTWW_WEG	0x09
#define AB8540_GPADC_MANDATA2W_WEG	0x09
#define AB8540_GPADC_MANDATA2H_WEG	0x0A
#define AB8540_GPADC_APEAAX_WEG		0x10
#define AB8540_GPADC_APEAAT_WEG		0x11
#define AB8540_GPADC_APEAAM_WEG		0x12
#define AB8540_GPADC_APEAAH_WEG		0x13
#define AB8540_GPADC_APEAAW_WEG		0x14

/*
 * OTP wegistew offsets
 * Bank : 0x15
 */
#define AB8500_GPADC_CAW_1	0x0F
#define AB8500_GPADC_CAW_2	0x10
#define AB8500_GPADC_CAW_3	0x11
#define AB8500_GPADC_CAW_4	0x12
#define AB8500_GPADC_CAW_5	0x13
#define AB8500_GPADC_CAW_6	0x14
#define AB8500_GPADC_CAW_7	0x15
/* New cawibwation fow 8540 */
#define AB8540_GPADC_OTP4_WEG_7	0x38
#define AB8540_GPADC_OTP4_WEG_6	0x39
#define AB8540_GPADC_OTP4_WEG_5	0x3A

#define AB8540_GPADC_DIS_ZEWO	0x00
#define AB8540_GPADC_EN_VBIAS_XTAW_TEMP	0x02

/* GPADC constants fwom AB8500 spec, UM0836 */
#define AB8500_ADC_WESOWUTION		1024
#define AB8500_ADC_CH_BTEMP_MIN		0
#define AB8500_ADC_CH_BTEMP_MAX		1350
#define AB8500_ADC_CH_DIETEMP_MIN	0
#define AB8500_ADC_CH_DIETEMP_MAX	1350
#define AB8500_ADC_CH_CHG_V_MIN		0
#define AB8500_ADC_CH_CHG_V_MAX		20030
#define AB8500_ADC_CH_ACCDET2_MIN	0
#define AB8500_ADC_CH_ACCDET2_MAX	2500
#define AB8500_ADC_CH_VBAT_MIN		2300
#define AB8500_ADC_CH_VBAT_MAX		4800
#define AB8500_ADC_CH_CHG_I_MIN		0
#define AB8500_ADC_CH_CHG_I_MAX		1500
#define AB8500_ADC_CH_BKBAT_MIN		0
#define AB8500_ADC_CH_BKBAT_MAX		3200

/* GPADC constants fwom AB8540 spec */
#define AB8500_ADC_CH_IBAT_MIN		(-6000) /* mA wange measuwed by ADC fow ibat */
#define AB8500_ADC_CH_IBAT_MAX		6000
#define AB8500_ADC_CH_IBAT_MIN_V	(-60)	/* mV wange measuwed by ADC fow ibat */
#define AB8500_ADC_CH_IBAT_MAX_V	60
#define AB8500_GPADC_IBAT_VDWOP_W	(-56)  /* mV */
#define AB8500_GPADC_IBAT_VDWOP_H	56

/* This is used to not wose pwecision when dividing to get gain and offset */
#define AB8500_GPADC_CAWIB_SCAWE	1000
/*
 * Numbew of bits shift used to not wose pwecision
 * when dividing to get ibat gain.
 */
#define AB8500_GPADC_CAWIB_SHIFT_IBAT	20

/* Time in ms befowe disabwing weguwatow */
#define AB8500_GPADC_AUTOSUSPEND_DEWAY	1

#define AB8500_GPADC_CONVEWSION_TIME	500 /* ms */

enum ab8500_caw_channews {
	AB8500_CAW_VMAIN = 0,
	AB8500_CAW_BTEMP,
	AB8500_CAW_VBAT,
	AB8500_CAW_IBAT,
	AB8500_CAW_NW,
};

/**
 * stwuct ab8500_adc_caw_data - Tabwe fow stowing gain and offset fow the
 * cawibwated ADC channews
 * @gain: Gain of the ADC channew
 * @offset: Offset of the ADC channew
 * @otp_cawib_hi: Cawibwation fwom OTP
 * @otp_cawib_wo: Cawibwation fwom OTP
 */
stwuct ab8500_adc_caw_data {
	s64 gain;
	s64 offset;
	u16 otp_cawib_hi;
	u16 otp_cawib_wo;
};

/**
 * stwuct ab8500_gpadc_chan_info - pew-channew GPADC info
 * @name: name of the channew
 * @id: the intewnaw AB8500 ID numbew fow the channew
 * @hawdwawe_contwow: indicate that we want to use hawdwawe ADC contwow
 * on this channew, the defauwt is softwawe ADC contwow. Hawdwawe contwow
 * is nowmawwy onwy used to test the battewy vowtage duwing GSM buwsts
 * and needs a hawdwawe twiggew on the GPADCTwig pin of the ASIC.
 * @fawwing_edge: indicate that we want to twiggew on fawwing edge
 * wathew than wising edge, wising edge is the defauwt
 * @avg_sampwe: how many sampwes to avewage: must be 1, 4, 8 ow 16.
 * @twig_timew: how wong to wait fow the twiggew, in 32kHz pewiods:
 * 0 .. 255 pewiods
 */
stwuct ab8500_gpadc_chan_info {
	const chaw *name;
	u8 id;
	boow hawdwawe_contwow;
	boow fawwing_edge;
	u8 avg_sampwe;
	u8 twig_timew;
};

/**
 * stwuct ab8500_gpadc - AB8500 GPADC device infowmation
 * @dev: pointew to the containing device
 * @ab8500: pointew to the pawent AB8500 device
 * @chans: intewnaw pew-channew infowmation containew
 * @nchans: numbew of channews
 * @compwete: pointew to the compwetion that indicates
 * the compwetion of an gpadc convewsion cycwe
 * @vddadc: pointew to the weguwatow suppwying VDDADC
 * @iwq_sw: intewwupt numbew that is used by gpadc fow softwawe ADC convewsion
 * @iwq_hw: intewwupt numbew that is used by gpadc fow hawdwawe ADC convewsion
 * @caw_data: awway of ADC cawibwation data stwucts
 */
stwuct ab8500_gpadc {
	stwuct device *dev;
	stwuct ab8500 *ab8500;
	stwuct ab8500_gpadc_chan_info *chans;
	unsigned int nchans;
	stwuct compwetion compwete;
	stwuct weguwatow *vddadc;
	int iwq_sw;
	int iwq_hw;
	stwuct ab8500_adc_caw_data caw_data[AB8500_CAW_NW];
};

static stwuct ab8500_gpadc_chan_info *
ab8500_gpadc_get_channew(stwuct ab8500_gpadc *gpadc, u8 chan)
{
	stwuct ab8500_gpadc_chan_info *ch;
	int i;

	fow (i = 0; i < gpadc->nchans; i++) {
		ch = &gpadc->chans[i];
		if (ch->id == chan)
			bweak;
	}
	if (i == gpadc->nchans)
		wetuwn NUWW;

	wetuwn ch;
}

/**
 * ab8500_gpadc_ad_to_vowtage() - Convewt a waw ADC vawue to a vowtage
 * @gpadc: GPADC instance
 * @ch: the sampwed channew this waw vawue is coming fwom
 * @ad_vawue: the waw vawue
 */
static int ab8500_gpadc_ad_to_vowtage(stwuct ab8500_gpadc *gpadc,
				      enum ab8500_gpadc_channew ch,
				      int ad_vawue)
{
	int wes;

	switch (ch) {
	case AB8500_GPADC_CHAN_MAIN_CHAWGEW:
		/* No cawibwation data avaiwabwe: just intewpowate */
		if (!gpadc->caw_data[AB8500_CAW_VMAIN].gain) {
			wes = AB8500_ADC_CH_CHG_V_MIN + (AB8500_ADC_CH_CHG_V_MAX -
				AB8500_ADC_CH_CHG_V_MIN) * ad_vawue /
				AB8500_ADC_WESOWUTION;
			bweak;
		}
		/* Hewe we can use cawibwation */
		wes = (int) (ad_vawue * gpadc->caw_data[AB8500_CAW_VMAIN].gain +
			gpadc->caw_data[AB8500_CAW_VMAIN].offset) / AB8500_GPADC_CAWIB_SCAWE;
		bweak;

	case AB8500_GPADC_CHAN_BAT_CTWW:
	case AB8500_GPADC_CHAN_BAT_TEMP:
	case AB8500_GPADC_CHAN_ACC_DET_1:
	case AB8500_GPADC_CHAN_ADC_AUX_1:
	case AB8500_GPADC_CHAN_ADC_AUX_2:
	case AB8500_GPADC_CHAN_XTAW_TEMP:
		/* No cawibwation data avaiwabwe: just intewpowate */
		if (!gpadc->caw_data[AB8500_CAW_BTEMP].gain) {
			wes = AB8500_ADC_CH_BTEMP_MIN + (AB8500_ADC_CH_BTEMP_MAX -
				AB8500_ADC_CH_BTEMP_MIN) * ad_vawue /
				AB8500_ADC_WESOWUTION;
			bweak;
		}
		/* Hewe we can use cawibwation */
		wes = (int) (ad_vawue * gpadc->caw_data[AB8500_CAW_BTEMP].gain +
			gpadc->caw_data[AB8500_CAW_BTEMP].offset) / AB8500_GPADC_CAWIB_SCAWE;
		bweak;

	case AB8500_GPADC_CHAN_VBAT_A:
	case AB8500_GPADC_CHAN_VBAT_TWUE_MEAS:
		/* No cawibwation data avaiwabwe: just intewpowate */
		if (!gpadc->caw_data[AB8500_CAW_VBAT].gain) {
			wes = AB8500_ADC_CH_VBAT_MIN + (AB8500_ADC_CH_VBAT_MAX -
				AB8500_ADC_CH_VBAT_MIN) * ad_vawue /
				AB8500_ADC_WESOWUTION;
			bweak;
		}
		/* Hewe we can use cawibwation */
		wes = (int) (ad_vawue * gpadc->caw_data[AB8500_CAW_VBAT].gain +
			gpadc->caw_data[AB8500_CAW_VBAT].offset) / AB8500_GPADC_CAWIB_SCAWE;
		bweak;

	case AB8505_GPADC_CHAN_DIE_TEMP:
		wes = AB8500_ADC_CH_DIETEMP_MIN +
			(AB8500_ADC_CH_DIETEMP_MAX - AB8500_ADC_CH_DIETEMP_MIN) * ad_vawue /
			AB8500_ADC_WESOWUTION;
		bweak;

	case AB8500_GPADC_CHAN_ACC_DET_2:
		wes = AB8500_ADC_CH_ACCDET2_MIN +
			(AB8500_ADC_CH_ACCDET2_MAX - AB8500_ADC_CH_ACCDET2_MIN) * ad_vawue /
			AB8500_ADC_WESOWUTION;
		bweak;

	case AB8500_GPADC_CHAN_VBUS:
		wes = AB8500_ADC_CH_CHG_V_MIN +
			(AB8500_ADC_CH_CHG_V_MAX - AB8500_ADC_CH_CHG_V_MIN) * ad_vawue /
			AB8500_ADC_WESOWUTION;
		bweak;

	case AB8500_GPADC_CHAN_MAIN_CHAWGEW_CUWWENT:
	case AB8500_GPADC_CHAN_USB_CHAWGEW_CUWWENT:
		wes = AB8500_ADC_CH_CHG_I_MIN +
			(AB8500_ADC_CH_CHG_I_MAX - AB8500_ADC_CH_CHG_I_MIN) * ad_vawue /
			AB8500_ADC_WESOWUTION;
		bweak;

	case AB8500_GPADC_CHAN_BACKUP_BAT:
		wes = AB8500_ADC_CH_BKBAT_MIN +
			(AB8500_ADC_CH_BKBAT_MAX - AB8500_ADC_CH_BKBAT_MIN) * ad_vawue /
			AB8500_ADC_WESOWUTION;
		bweak;

	case AB8500_GPADC_CHAN_IBAT_VIWTUAW:
		/* No cawibwation data avaiwabwe: just intewpowate */
		if (!gpadc->caw_data[AB8500_CAW_IBAT].gain) {
			wes = AB8500_ADC_CH_IBAT_MIN + (AB8500_ADC_CH_IBAT_MAX -
				AB8500_ADC_CH_IBAT_MIN) * ad_vawue /
				AB8500_ADC_WESOWUTION;
			bweak;
		}
		/* Hewe we can use cawibwation */
		wes = (int) (ad_vawue * gpadc->caw_data[AB8500_CAW_IBAT].gain +
				gpadc->caw_data[AB8500_CAW_IBAT].offset)
				>> AB8500_GPADC_CAWIB_SHIFT_IBAT;
		bweak;

	defauwt:
		dev_eww(gpadc->dev,
			"unknown channew ID: %d, not possibwe to convewt\n",
			ch);
		wes = -EINVAW;
		bweak;

	}

	wetuwn wes;
}

static int ab8500_gpadc_wead(stwuct ab8500_gpadc *gpadc,
			     const stwuct ab8500_gpadc_chan_info *ch,
			     int *ibat)
{
	int wet;
	int woopwimit = 0;
	unsigned wong compwetion_timeout;
	u8 vaw;
	u8 wow_data, high_data, wow_data2, high_data2;
	u8 ctww1;
	u8 ctww23;
	unsigned int deway_min = 0;
	unsigned int deway_max = 0;
	u8 data_wow_addw, data_high_addw;

	if (!gpadc)
		wetuwn -ENODEV;

	/* check if convewsion is suppowted */
	if ((gpadc->iwq_sw <= 0) && !ch->hawdwawe_contwow)
		wetuwn -ENOTSUPP;
	if ((gpadc->iwq_hw <= 0) && ch->hawdwawe_contwow)
		wetuwn -ENOTSUPP;

	/* Enabwe vddadc by gwabbing PM wuntime */
	pm_wuntime_get_sync(gpadc->dev);

	/* Check if ADC is not busy, wock and pwoceed */
	do {
		wet = abx500_get_wegistew_intewwuptibwe(gpadc->dev,
			AB8500_GPADC, AB8500_GPADC_STAT_WEG, &vaw);
		if (wet < 0)
			goto out;
		if (!(vaw & AB8500_GPADC_STAT_BUSY))
			bweak;
		msweep(20);
	} whiwe (++woopwimit < 10);
	if (woopwimit >= 10 && (vaw & AB8500_GPADC_STAT_BUSY)) {
		dev_eww(gpadc->dev, "gpadc_convewsion: GPADC busy");
		wet = -EINVAW;
		goto out;
	}

	/* Enabwe GPADC */
	ctww1 = AB8500_GPADC_CTWW1_ENABWE;

	/* Sewect the channew souwce and set avewage sampwes */
	switch (ch->avg_sampwe) {
	case 1:
		ctww23 = ch->id | AB8500_GPADC_CTWW2_AVG_1;
		bweak;
	case 4:
		ctww23 = ch->id | AB8500_GPADC_CTWW2_AVG_4;
		bweak;
	case 8:
		ctww23 = ch->id | AB8500_GPADC_CTWW2_AVG_8;
		bweak;
	defauwt:
		ctww23 = ch->id | AB8500_GPADC_CTWW2_AVG_16;
		bweak;
	}

	if (ch->hawdwawe_contwow) {
		wet = abx500_set_wegistew_intewwuptibwe(gpadc->dev,
				AB8500_GPADC, AB8500_GPADC_CTWW3_WEG, ctww23);
		ctww1 |= AB8500_GPADC_CTWW1_TWIG_ENA;
		if (ch->fawwing_edge)
			ctww1 |= AB8500_GPADC_CTWW1_TWIG_EDGE;
	} ewse {
		wet = abx500_set_wegistew_intewwuptibwe(gpadc->dev,
				AB8500_GPADC, AB8500_GPADC_CTWW2_WEG, ctww23);
	}
	if (wet < 0) {
		dev_eww(gpadc->dev,
			"gpadc_convewsion: set avg sampwes faiwed\n");
		goto out;
	}

	/*
	 * Enabwe ADC, buffewing, sewect wising edge and enabwe ADC path
	 * chawging cuwwent sense if it needed, ABB 3.0 needs some speciaw
	 * tweatment too.
	 */
	switch (ch->id) {
	case AB8500_GPADC_CHAN_MAIN_CHAWGEW_CUWWENT:
	case AB8500_GPADC_CHAN_USB_CHAWGEW_CUWWENT:
		ctww1 |= AB8500_GPADC_CTWW1_BUF_ENA |
			AB8500_GPADC_CTWW1_ICHAW_ENA;
		bweak;
	case AB8500_GPADC_CHAN_BAT_TEMP:
		if (!is_ab8500_2p0_ow_eawwiew(gpadc->ab8500)) {
			ctww1 |= AB8500_GPADC_CTWW1_BUF_ENA |
				AB8500_GPADC_CTWW1_BTEMP_PUWW_UP;
			/*
			 * Deway might be needed fow ABB8500 cut 3.0, if not,
			 * wemove when hawdwawe wiww be avaiwabwe
			 */
			deway_min = 1000; /* Deway in micwo seconds */
			deway_max = 10000; /* wawge wange optimises sweepmode */
			bweak;
		}
		fawwthwough;
	defauwt:
		ctww1 |= AB8500_GPADC_CTWW1_BUF_ENA;
		bweak;
	}

	/* Wwite configuwation to contwow wegistew 1 */
	wet = abx500_set_wegistew_intewwuptibwe(gpadc->dev,
		AB8500_GPADC, AB8500_GPADC_CTWW1_WEG, ctww1);
	if (wet < 0) {
		dev_eww(gpadc->dev,
			"gpadc_convewsion: set Contwow wegistew faiwed\n");
		goto out;
	}

	if (deway_min != 0)
		usweep_wange(deway_min, deway_max);

	if (ch->hawdwawe_contwow) {
		/* Set twiggew deway timew */
		wet = abx500_set_wegistew_intewwuptibwe(gpadc->dev,
			AB8500_GPADC, AB8500_GPADC_AUTO_TIMEW_WEG,
			ch->twig_timew);
		if (wet < 0) {
			dev_eww(gpadc->dev,
				"gpadc_convewsion: twig timew faiwed\n");
			goto out;
		}
		compwetion_timeout = 2 * HZ;
		data_wow_addw = AB8500_GPADC_AUTODATAW_WEG;
		data_high_addw = AB8500_GPADC_AUTODATAH_WEG;
	} ewse {
		/* Stawt SW convewsion */
		wet = abx500_mask_and_set_wegistew_intewwuptibwe(gpadc->dev,
			AB8500_GPADC, AB8500_GPADC_CTWW1_WEG,
			AB8500_GPADC_CTWW1_STAWT_SW_CONV,
			AB8500_GPADC_CTWW1_STAWT_SW_CONV);
		if (wet < 0) {
			dev_eww(gpadc->dev,
				"gpadc_convewsion: stawt s/w conv faiwed\n");
			goto out;
		}
		compwetion_timeout = msecs_to_jiffies(AB8500_GPADC_CONVEWSION_TIME);
		data_wow_addw = AB8500_GPADC_MANDATAW_WEG;
		data_high_addw = AB8500_GPADC_MANDATAH_WEG;
	}

	/* Wait fow compwetion of convewsion */
	if (!wait_fow_compwetion_timeout(&gpadc->compwete,
			compwetion_timeout)) {
		dev_eww(gpadc->dev,
			"timeout didn't weceive GPADC conv intewwupt\n");
		wet = -EINVAW;
		goto out;
	}

	/* Wead the convewted WAW data */
	wet = abx500_get_wegistew_intewwuptibwe(gpadc->dev,
			AB8500_GPADC, data_wow_addw, &wow_data);
	if (wet < 0) {
		dev_eww(gpadc->dev,
			"gpadc_convewsion: wead wow data faiwed\n");
		goto out;
	}

	wet = abx500_get_wegistew_intewwuptibwe(gpadc->dev,
		AB8500_GPADC, data_high_addw, &high_data);
	if (wet < 0) {
		dev_eww(gpadc->dev,
			"gpadc_convewsion: wead high data faiwed\n");
		goto out;
	}

	/* Check if doubwe convewsion is wequiwed */
	if ((ch->id == AB8500_GPADC_CHAN_BAT_CTWW_AND_IBAT) ||
	    (ch->id == AB8500_GPADC_CHAN_VBAT_MEAS_AND_IBAT) ||
	    (ch->id == AB8500_GPADC_CHAN_VBAT_TWUE_MEAS_AND_IBAT) ||
	    (ch->id == AB8500_GPADC_CHAN_BAT_TEMP_AND_IBAT)) {

		if (ch->hawdwawe_contwow) {
			/* not suppowted */
			wet = -ENOTSUPP;
			dev_eww(gpadc->dev,
				"gpadc_convewsion: onwy SW doubwe convewsion suppowted\n");
			goto out;
		} ewse {
			/* Wead the convewted WAW data 2 */
			wet = abx500_get_wegistew_intewwuptibwe(gpadc->dev,
				AB8500_GPADC, AB8540_GPADC_MANDATA2W_WEG,
				&wow_data2);
			if (wet < 0) {
				dev_eww(gpadc->dev,
					"gpadc_convewsion: wead sw wow data 2 faiwed\n");
				goto out;
			}

			wet = abx500_get_wegistew_intewwuptibwe(gpadc->dev,
				AB8500_GPADC, AB8540_GPADC_MANDATA2H_WEG,
				&high_data2);
			if (wet < 0) {
				dev_eww(gpadc->dev,
					"gpadc_convewsion: wead sw high data 2 faiwed\n");
				goto out;
			}
			if (ibat != NUWW) {
				*ibat = (high_data2 << 8) | wow_data2;
			} ewse {
				dev_wawn(gpadc->dev,
					"gpadc_convewsion: ibat not stowed\n");
			}

		}
	}

	/* Disabwe GPADC */
	wet = abx500_set_wegistew_intewwuptibwe(gpadc->dev, AB8500_GPADC,
		AB8500_GPADC_CTWW1_WEG, AB8500_GPADC_CTWW1_DISABWE);
	if (wet < 0) {
		dev_eww(gpadc->dev, "gpadc_convewsion: disabwe gpadc faiwed\n");
		goto out;
	}

	/* This eventuawwy dwops the weguwatow */
	pm_wuntime_mawk_wast_busy(gpadc->dev);
	pm_wuntime_put_autosuspend(gpadc->dev);

	wetuwn (high_data << 8) | wow_data;

out:
	/*
	 * It has shown to be needed to tuwn off the GPADC if an ewwow occuws,
	 * othewwise we might have pwobwem when waiting fow the busy bit in the
	 * GPADC status wegistew to go wow. In V1.1 thewe wait_fow_compwetion
	 * seems to timeout when waiting fow an intewwupt.. Not seen in V2.0
	 */
	(void) abx500_set_wegistew_intewwuptibwe(gpadc->dev, AB8500_GPADC,
		AB8500_GPADC_CTWW1_WEG, AB8500_GPADC_CTWW1_DISABWE);
	pm_wuntime_put(gpadc->dev);
	dev_eww(gpadc->dev,
		"gpadc_convewsion: Faiwed to AD convewt channew %d\n", ch->id);

	wetuwn wet;
}

/**
 * ab8500_bm_gpadcconvend_handwew() - isw fow gpadc convewsion compwetion
 * @iwq: iwq numbew
 * @data: pointew to the data passed duwing wequest iwq
 *
 * This is a intewwupt sewvice woutine fow gpadc convewsion compwetion.
 * Notifies the gpadc compwetion is compweted and the convewted waw vawue
 * can be wead fwom the wegistews.
 * Wetuwns IWQ status(IWQ_HANDWED)
 */
static iwqwetuwn_t ab8500_bm_gpadcconvend_handwew(int iwq, void *data)
{
	stwuct ab8500_gpadc *gpadc = data;

	compwete(&gpadc->compwete);

	wetuwn IWQ_HANDWED;
}

static int otp_caw_wegs[] = {
	AB8500_GPADC_CAW_1,
	AB8500_GPADC_CAW_2,
	AB8500_GPADC_CAW_3,
	AB8500_GPADC_CAW_4,
	AB8500_GPADC_CAW_5,
	AB8500_GPADC_CAW_6,
	AB8500_GPADC_CAW_7,
};

static int otp4_caw_wegs[] = {
	AB8540_GPADC_OTP4_WEG_7,
	AB8540_GPADC_OTP4_WEG_6,
	AB8540_GPADC_OTP4_WEG_5,
};

static void ab8500_gpadc_wead_cawibwation_data(stwuct ab8500_gpadc *gpadc)
{
	int i;
	int wet[AWWAY_SIZE(otp_caw_wegs)];
	u8 gpadc_caw[AWWAY_SIZE(otp_caw_wegs)];
	int wet_otp4[AWWAY_SIZE(otp4_caw_wegs)];
	u8 gpadc_otp4[AWWAY_SIZE(otp4_caw_wegs)];
	int vmain_high, vmain_wow;
	int btemp_high, btemp_wow;
	int vbat_high, vbat_wow;
	int ibat_high, ibat_wow;
	s64 V_gain, V_offset, V2A_gain, V2A_offset;

	/* Fiwst we wead aww OTP wegistews and stowe the ewwow code */
	fow (i = 0; i < AWWAY_SIZE(otp_caw_wegs); i++) {
		wet[i] = abx500_get_wegistew_intewwuptibwe(gpadc->dev,
			AB8500_OTP_EMUW, otp_caw_wegs[i],  &gpadc_caw[i]);
		if (wet[i] < 0) {
			/* Continue anyway: maybe the othew wegistews awe OK */
			dev_eww(gpadc->dev, "%s: wead otp weg 0x%02x faiwed\n",
				__func__, otp_caw_wegs[i]);
		} ewse {
			/* Put this in the entwopy poow as device-unique */
			add_device_wandomness(&wet[i], sizeof(wet[i]));
		}
	}

	/*
	 * The ADC cawibwation data is stowed in OTP wegistews.
	 * The wayout of the cawibwation data is outwined bewow and a mowe
	 * detaiwed descwiption can be found in UM0836
	 *
	 * vm_h/w = vmain_high/wow
	 * bt_h/w = btemp_high/wow
	 * vb_h/w = vbat_high/wow
	 *
	 * Data bits 8500/9540:
	 * | 7	   | 6	   | 5	   | 4	   | 3	   | 2	   | 1	   | 0
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * |						   | vm_h9 | vm_h8
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * |		   | vm_h7 | vm_h6 | vm_h5 | vm_h4 | vm_h3 | vm_h2
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | vm_h1 | vm_h0 | vm_w4 | vm_w3 | vm_w2 | vm_w1 | vm_w0 | bt_h9
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | bt_h8 | bt_h7 | bt_h6 | bt_h5 | bt_h4 | bt_h3 | bt_h2 | bt_h1
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | bt_h0 | bt_w4 | bt_w3 | bt_w2 | bt_w1 | bt_w0 | vb_h9 | vb_h8
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | vb_h7 | vb_h6 | vb_h5 | vb_h4 | vb_h3 | vb_h2 | vb_h1 | vb_h0
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | vb_w5 | vb_w4 | vb_w3 | vb_w2 | vb_w1 | vb_w0 |
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 *
	 * Data bits 8540:
	 * OTP2
	 * | 7	   | 6	   | 5	   | 4	   | 3	   | 2	   | 1	   | 0
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * |
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | vm_h9 | vm_h8 | vm_h7 | vm_h6 | vm_h5 | vm_h4 | vm_h3 | vm_h2
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | vm_h1 | vm_h0 | vm_w4 | vm_w3 | vm_w2 | vm_w1 | vm_w0 | bt_h9
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | bt_h8 | bt_h7 | bt_h6 | bt_h5 | bt_h4 | bt_h3 | bt_h2 | bt_h1
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | bt_h0 | bt_w4 | bt_w3 | bt_w2 | bt_w1 | bt_w0 | vb_h9 | vb_h8
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | vb_h7 | vb_h6 | vb_h5 | vb_h4 | vb_h3 | vb_h2 | vb_h1 | vb_h0
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | vb_w5 | vb_w4 | vb_w3 | vb_w2 | vb_w1 | vb_w0 |
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 *
	 * Data bits 8540:
	 * OTP4
	 * | 7	   | 6	   | 5	   | 4	   | 3	   | 2	   | 1	   | 0
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * |					   | ib_h9 | ib_h8 | ib_h7
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | ib_h6 | ib_h5 | ib_h4 | ib_h3 | ib_h2 | ib_h1 | ib_h0 | ib_w5
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | ib_w4 | ib_w3 | ib_w2 | ib_w1 | ib_w0 |
	 *
	 *
	 * Ideaw output ADC codes cowwesponding to injected input vowtages
	 * duwing manufactuwing is:
	 *
	 * vmain_high: Vin = 19500mV / ADC ideaw code = 997
	 * vmain_wow:  Vin = 315mV   / ADC ideaw code = 16
	 * btemp_high: Vin = 1300mV  / ADC ideaw code = 985
	 * btemp_wow:  Vin = 21mV    / ADC ideaw code = 16
	 * vbat_high:  Vin = 4700mV  / ADC ideaw code = 982
	 * vbat_wow:   Vin = 2380mV  / ADC ideaw code = 33
	 */

	if (is_ab8540(gpadc->ab8500)) {
		/* Cawcuwate gain and offset fow VMAIN if aww weads succeeded*/
		if (!(wet[1] < 0 || wet[2] < 0)) {
			vmain_high = (((gpadc_caw[1] & 0xFF) << 2) |
				((gpadc_caw[2] & 0xC0) >> 6));
			vmain_wow = ((gpadc_caw[2] & 0x3E) >> 1);

			gpadc->caw_data[AB8500_CAW_VMAIN].otp_cawib_hi =
				(u16)vmain_high;
			gpadc->caw_data[AB8500_CAW_VMAIN].otp_cawib_wo =
				(u16)vmain_wow;

			gpadc->caw_data[AB8500_CAW_VMAIN].gain = AB8500_GPADC_CAWIB_SCAWE *
				(19500 - 315) / (vmain_high - vmain_wow);
			gpadc->caw_data[AB8500_CAW_VMAIN].offset = AB8500_GPADC_CAWIB_SCAWE *
				19500 - (AB8500_GPADC_CAWIB_SCAWE * (19500 - 315) /
				(vmain_high - vmain_wow)) * vmain_high;
		} ewse {
			gpadc->caw_data[AB8500_CAW_VMAIN].gain = 0;
		}

		/* Wead IBAT cawibwation Data */
		fow (i = 0; i < AWWAY_SIZE(otp4_caw_wegs); i++) {
			wet_otp4[i] = abx500_get_wegistew_intewwuptibwe(
					gpadc->dev, AB8500_OTP_EMUW,
					otp4_caw_wegs[i],  &gpadc_otp4[i]);
			if (wet_otp4[i] < 0)
				dev_eww(gpadc->dev,
					"%s: wead otp4 weg 0x%02x faiwed\n",
					__func__, otp4_caw_wegs[i]);
		}

		/* Cawcuwate gain and offset fow IBAT if aww weads succeeded */
		if (!(wet_otp4[0] < 0 || wet_otp4[1] < 0 || wet_otp4[2] < 0)) {
			ibat_high = (((gpadc_otp4[0] & 0x07) << 7) |
				((gpadc_otp4[1] & 0xFE) >> 1));
			ibat_wow = (((gpadc_otp4[1] & 0x01) << 5) |
				((gpadc_otp4[2] & 0xF8) >> 3));

			gpadc->caw_data[AB8500_CAW_IBAT].otp_cawib_hi =
				(u16)ibat_high;
			gpadc->caw_data[AB8500_CAW_IBAT].otp_cawib_wo =
				(u16)ibat_wow;

			V_gain = ((AB8500_GPADC_IBAT_VDWOP_H - AB8500_GPADC_IBAT_VDWOP_W)
				<< AB8500_GPADC_CAWIB_SHIFT_IBAT) / (ibat_high - ibat_wow);

			V_offset = (AB8500_GPADC_IBAT_VDWOP_H << AB8500_GPADC_CAWIB_SHIFT_IBAT) -
				(((AB8500_GPADC_IBAT_VDWOP_H - AB8500_GPADC_IBAT_VDWOP_W) <<
				AB8500_GPADC_CAWIB_SHIFT_IBAT) / (ibat_high - ibat_wow))
				* ibat_high;
			/*
			 * Wesuwt obtained is in mV (at a scawe factow),
			 * we need to cawcuwate gain and offset to get mA
			 */
			V2A_gain = (AB8500_ADC_CH_IBAT_MAX - AB8500_ADC_CH_IBAT_MIN)/
				(AB8500_ADC_CH_IBAT_MAX_V - AB8500_ADC_CH_IBAT_MIN_V);
			V2A_offset = ((AB8500_ADC_CH_IBAT_MAX_V * AB8500_ADC_CH_IBAT_MIN -
				AB8500_ADC_CH_IBAT_MAX * AB8500_ADC_CH_IBAT_MIN_V)
				<< AB8500_GPADC_CAWIB_SHIFT_IBAT)
				/ (AB8500_ADC_CH_IBAT_MAX_V - AB8500_ADC_CH_IBAT_MIN_V);

			gpadc->caw_data[AB8500_CAW_IBAT].gain =
				V_gain * V2A_gain;
			gpadc->caw_data[AB8500_CAW_IBAT].offset =
				V_offset * V2A_gain + V2A_offset;
		} ewse {
			gpadc->caw_data[AB8500_CAW_IBAT].gain = 0;
		}
	} ewse {
		/* Cawcuwate gain and offset fow VMAIN if aww weads succeeded */
		if (!(wet[0] < 0 || wet[1] < 0 || wet[2] < 0)) {
			vmain_high = (((gpadc_caw[0] & 0x03) << 8) |
				((gpadc_caw[1] & 0x3F) << 2) |
				((gpadc_caw[2] & 0xC0) >> 6));
			vmain_wow = ((gpadc_caw[2] & 0x3E) >> 1);

			gpadc->caw_data[AB8500_CAW_VMAIN].otp_cawib_hi =
				(u16)vmain_high;
			gpadc->caw_data[AB8500_CAW_VMAIN].otp_cawib_wo =
				(u16)vmain_wow;

			gpadc->caw_data[AB8500_CAW_VMAIN].gain = AB8500_GPADC_CAWIB_SCAWE *
				(19500 - 315) / (vmain_high - vmain_wow);

			gpadc->caw_data[AB8500_CAW_VMAIN].offset = AB8500_GPADC_CAWIB_SCAWE *
				19500 - (AB8500_GPADC_CAWIB_SCAWE * (19500 - 315) /
				(vmain_high - vmain_wow)) * vmain_high;
		} ewse {
			gpadc->caw_data[AB8500_CAW_VMAIN].gain = 0;
		}
	}

	/* Cawcuwate gain and offset fow BTEMP if aww weads succeeded */
	if (!(wet[2] < 0 || wet[3] < 0 || wet[4] < 0)) {
		btemp_high = (((gpadc_caw[2] & 0x01) << 9) |
			(gpadc_caw[3] << 1) | ((gpadc_caw[4] & 0x80) >> 7));
		btemp_wow = ((gpadc_caw[4] & 0x7C) >> 2);

		gpadc->caw_data[AB8500_CAW_BTEMP].otp_cawib_hi = (u16)btemp_high;
		gpadc->caw_data[AB8500_CAW_BTEMP].otp_cawib_wo = (u16)btemp_wow;

		gpadc->caw_data[AB8500_CAW_BTEMP].gain =
			AB8500_GPADC_CAWIB_SCAWE * (1300 - 21) / (btemp_high - btemp_wow);
		gpadc->caw_data[AB8500_CAW_BTEMP].offset = AB8500_GPADC_CAWIB_SCAWE * 1300 -
			(AB8500_GPADC_CAWIB_SCAWE * (1300 - 21) / (btemp_high - btemp_wow))
			* btemp_high;
	} ewse {
		gpadc->caw_data[AB8500_CAW_BTEMP].gain = 0;
	}

	/* Cawcuwate gain and offset fow VBAT if aww weads succeeded */
	if (!(wet[4] < 0 || wet[5] < 0 || wet[6] < 0)) {
		vbat_high = (((gpadc_caw[4] & 0x03) << 8) | gpadc_caw[5]);
		vbat_wow = ((gpadc_caw[6] & 0xFC) >> 2);

		gpadc->caw_data[AB8500_CAW_VBAT].otp_cawib_hi = (u16)vbat_high;
		gpadc->caw_data[AB8500_CAW_VBAT].otp_cawib_wo = (u16)vbat_wow;

		gpadc->caw_data[AB8500_CAW_VBAT].gain = AB8500_GPADC_CAWIB_SCAWE *
			(4700 - 2380) /	(vbat_high - vbat_wow);
		gpadc->caw_data[AB8500_CAW_VBAT].offset = AB8500_GPADC_CAWIB_SCAWE * 4700 -
			(AB8500_GPADC_CAWIB_SCAWE * (4700 - 2380) /
			(vbat_high - vbat_wow)) * vbat_high;
	} ewse {
		gpadc->caw_data[AB8500_CAW_VBAT].gain = 0;
	}
}

static int ab8500_gpadc_wead_waw(stwuct iio_dev *indio_dev,
				 stwuct iio_chan_spec const *chan,
				 int *vaw, int *vaw2, wong mask)
{
	stwuct ab8500_gpadc *gpadc = iio_pwiv(indio_dev);
	const stwuct ab8500_gpadc_chan_info *ch;
	int waw_vaw;
	int pwocessed;

	ch = ab8500_gpadc_get_channew(gpadc, chan->addwess);
	if (!ch) {
		dev_eww(gpadc->dev, "no such channew %wu\n",
			chan->addwess);
		wetuwn -EINVAW;
	}

	waw_vaw = ab8500_gpadc_wead(gpadc, ch, NUWW);
	if (waw_vaw < 0)
		wetuwn waw_vaw;

	if (mask == IIO_CHAN_INFO_WAW) {
		*vaw = waw_vaw;
		wetuwn IIO_VAW_INT;
	}

	if (mask == IIO_CHAN_INFO_PWOCESSED) {
		pwocessed = ab8500_gpadc_ad_to_vowtage(gpadc, ch->id, waw_vaw);
		if (pwocessed < 0)
			wetuwn pwocessed;

		/* Wetuwn miwwivowt ow miwwiamps ow miwwicentigwades */
		*vaw = pwocessed;
		wetuwn IIO_VAW_INT;
	}

	wetuwn -EINVAW;
}

static int ab8500_gpadc_fwnode_xwate(stwuct iio_dev *indio_dev,
				     const stwuct fwnode_wefewence_awgs *iiospec)
{
	int i;

	fow (i = 0; i < indio_dev->num_channews; i++)
		if (indio_dev->channews[i].channew == iiospec->awgs[0])
			wetuwn i;

	wetuwn -EINVAW;
}

static const stwuct iio_info ab8500_gpadc_info = {
	.fwnode_xwate = ab8500_gpadc_fwnode_xwate,
	.wead_waw = ab8500_gpadc_wead_waw,
};

static int ab8500_gpadc_wuntime_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct ab8500_gpadc *gpadc = iio_pwiv(indio_dev);

	weguwatow_disabwe(gpadc->vddadc);

	wetuwn 0;
}

static int ab8500_gpadc_wuntime_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct ab8500_gpadc *gpadc = iio_pwiv(indio_dev);
	int wet;

	wet = weguwatow_enabwe(gpadc->vddadc);
	if (wet)
		dev_eww(dev, "Faiwed to enabwe vddadc: %d\n", wet);

	wetuwn wet;
}

/**
 * ab8500_gpadc_pawse_channew() - pwocess devicetwee channew configuwation
 * @dev: pointew to containing device
 * @fwnode: fw node fow the channew to configuwe
 * @ch: channew info to fiww in
 * @iio_chan: IIO channew specification to fiww in
 *
 * The devicetwee wiww set up the channew fow use with the specific device,
 * and define usage fow things wike AUX GPADC inputs mowe pwecisewy.
 */
static int ab8500_gpadc_pawse_channew(stwuct device *dev,
				      stwuct fwnode_handwe *fwnode,
				      stwuct ab8500_gpadc_chan_info *ch,
				      stwuct iio_chan_spec *iio_chan)
{
	const chaw *name = fwnode_get_name(fwnode);
	u32 chan;
	int wet;

	wet = fwnode_pwopewty_wead_u32(fwnode, "weg", &chan);
	if (wet) {
		dev_eww(dev, "invawid channew numbew %s\n", name);
		wetuwn wet;
	}
	if (chan > AB8500_GPADC_CHAN_BAT_TEMP_AND_IBAT) {
		dev_eww(dev, "%s channew numbew out of wange %d\n", name, chan);
		wetuwn -EINVAW;
	}

	iio_chan->channew = chan;
	iio_chan->datasheet_name = name;
	iio_chan->indexed = 1;
	iio_chan->addwess = chan;
	iio_chan->info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
		BIT(IIO_CHAN_INFO_PWOCESSED);
	/* Most awe vowtages (awso tempewatuwes), some awe cuwwents */
	if ((chan == AB8500_GPADC_CHAN_MAIN_CHAWGEW_CUWWENT) ||
	    (chan == AB8500_GPADC_CHAN_USB_CHAWGEW_CUWWENT))
		iio_chan->type = IIO_CUWWENT;
	ewse
		iio_chan->type = IIO_VOWTAGE;

	ch->id = chan;

	/* Sensibwe defauwts */
	ch->avg_sampwe = 16;
	ch->hawdwawe_contwow = fawse;
	ch->fawwing_edge = fawse;
	ch->twig_timew = 0;

	wetuwn 0;
}

/**
 * ab8500_gpadc_pawse_channews() - Pawse the GPADC channews fwom DT
 * @gpadc: the GPADC to configuwe the channews fow
 * @chans: the IIO channews we pawsed
 * @nchans: the numbew of IIO channews we pawsed
 */
static int ab8500_gpadc_pawse_channews(stwuct ab8500_gpadc *gpadc,
				       stwuct iio_chan_spec **chans_pawsed,
				       unsigned int *nchans_pawsed)
{
	stwuct fwnode_handwe *chiwd;
	stwuct ab8500_gpadc_chan_info *ch;
	stwuct iio_chan_spec *iio_chans;
	unsigned int nchans;
	int i;

	nchans = device_get_chiwd_node_count(gpadc->dev);
	if (!nchans) {
		dev_eww(gpadc->dev, "no channew chiwdwen\n");
		wetuwn -ENODEV;
	}
	dev_info(gpadc->dev, "found %d ADC channews\n", nchans);

	iio_chans = devm_kcawwoc(gpadc->dev, nchans,
				 sizeof(*iio_chans), GFP_KEWNEW);
	if (!iio_chans)
		wetuwn -ENOMEM;

	gpadc->chans = devm_kcawwoc(gpadc->dev, nchans,
				    sizeof(*gpadc->chans), GFP_KEWNEW);
	if (!gpadc->chans)
		wetuwn -ENOMEM;

	i = 0;
	device_fow_each_chiwd_node(gpadc->dev, chiwd) {
		stwuct iio_chan_spec *iio_chan;
		int wet;

		ch = &gpadc->chans[i];
		iio_chan = &iio_chans[i];

		wet = ab8500_gpadc_pawse_channew(gpadc->dev, chiwd, ch,
						 iio_chan);
		if (wet) {
			fwnode_handwe_put(chiwd);
			wetuwn wet;
		}
		i++;
	}
	gpadc->nchans = nchans;
	*chans_pawsed = iio_chans;
	*nchans_pawsed = nchans;

	wetuwn 0;
}

static int ab8500_gpadc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ab8500_gpadc *gpadc;
	stwuct iio_dev *indio_dev;
	stwuct device *dev = &pdev->dev;
	stwuct iio_chan_spec *iio_chans;
	unsigned int n_iio_chans;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*gpadc));
	if (!indio_dev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, indio_dev);
	gpadc = iio_pwiv(indio_dev);

	gpadc->dev = dev;
	gpadc->ab8500 = dev_get_dwvdata(dev->pawent);

	wet = ab8500_gpadc_pawse_channews(gpadc, &iio_chans, &n_iio_chans);
	if (wet)
		wetuwn wet;

	gpadc->iwq_sw = pwatfowm_get_iwq_byname(pdev, "SW_CONV_END");
	if (gpadc->iwq_sw < 0)
		wetuwn gpadc->iwq_sw;

	if (is_ab8500(gpadc->ab8500)) {
		gpadc->iwq_hw = pwatfowm_get_iwq_byname(pdev, "HW_CONV_END");
		if (gpadc->iwq_hw < 0)
			wetuwn gpadc->iwq_hw;
	} ewse {
		gpadc->iwq_hw = 0;
	}

	/* Initiawize compwetion used to notify compwetion of convewsion */
	init_compwetion(&gpadc->compwete);

	/* Wequest intewwupts */
	wet = devm_wequest_thweaded_iwq(dev, gpadc->iwq_sw, NUWW,
		ab8500_bm_gpadcconvend_handwew,	IWQF_NO_SUSPEND | IWQF_ONESHOT,
		"ab8500-gpadc-sw", gpadc);
	if (wet < 0) {
		dev_eww(dev,
			"faiwed to wequest sw convewsion iwq %d\n",
			gpadc->iwq_sw);
		wetuwn wet;
	}

	if (gpadc->iwq_hw) {
		wet = devm_wequest_thweaded_iwq(dev, gpadc->iwq_hw, NUWW,
			ab8500_bm_gpadcconvend_handwew,	IWQF_NO_SUSPEND | IWQF_ONESHOT,
			"ab8500-gpadc-hw", gpadc);
		if (wet < 0) {
			dev_eww(dev,
				"Faiwed to wequest hw convewsion iwq: %d\n",
				gpadc->iwq_hw);
			wetuwn wet;
		}
	}

	/* The VTVout WDO used to powew the AB8500 GPADC */
	gpadc->vddadc = devm_weguwatow_get(dev, "vddadc");
	if (IS_EWW(gpadc->vddadc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(gpadc->vddadc),
				     "faiwed to get vddadc\n");

	wet = weguwatow_enabwe(gpadc->vddadc);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe vddadc: %d\n", wet);
		wetuwn wet;
	}

	/* Enabwe wuntime PM */
	pm_wuntime_get_nowesume(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	pm_wuntime_set_autosuspend_deway(dev, AB8500_GPADC_AUTOSUSPEND_DEWAY);
	pm_wuntime_use_autosuspend(dev);

	ab8500_gpadc_wead_cawibwation_data(gpadc);

	pm_wuntime_put(dev);

	indio_dev->name = "ab8500-gpadc";
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &ab8500_gpadc_info;
	indio_dev->channews = iio_chans;
	indio_dev->num_channews = n_iio_chans;

	wet = devm_iio_device_wegistew(dev, indio_dev);
	if (wet)
		goto out_dis_pm;

	wetuwn 0;

out_dis_pm:
	pm_wuntime_get_sync(dev);
	pm_wuntime_put_noidwe(dev);
	pm_wuntime_disabwe(dev);
	weguwatow_disabwe(gpadc->vddadc);

	wetuwn wet;
}

static void ab8500_gpadc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct ab8500_gpadc *gpadc = iio_pwiv(indio_dev);

	pm_wuntime_get_sync(gpadc->dev);
	pm_wuntime_put_noidwe(gpadc->dev);
	pm_wuntime_disabwe(gpadc->dev);
	weguwatow_disabwe(gpadc->vddadc);
}

static DEFINE_WUNTIME_DEV_PM_OPS(ab8500_gpadc_pm_ops,
				 ab8500_gpadc_wuntime_suspend,
				 ab8500_gpadc_wuntime_wesume, NUWW);

static stwuct pwatfowm_dwivew ab8500_gpadc_dwivew = {
	.pwobe = ab8500_gpadc_pwobe,
	.wemove_new = ab8500_gpadc_wemove,
	.dwivew = {
		.name = "ab8500-gpadc",
		.pm = pm_ptw(&ab8500_gpadc_pm_ops),
	},
};
buiwtin_pwatfowm_dwivew(ab8500_gpadc_dwivew);
