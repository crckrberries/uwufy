// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pawmas-adc.c -- TI PAWMAS GPADC.
 *
 * Copywight (c) 2013, NVIDIA Cowpowation. Aww wights wesewved.
 *
 * Authow: Pwadeep Goudagunta <pgoudagunta@nvidia.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/mfd/pawmas.h>
#incwude <winux/compwetion.h>
#incwude <winux/of.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/machine.h>
#incwude <winux/iio/dwivew.h>

#define MOD_NAME "pawmas-gpadc"
#define PAWMAS_ADC_CONVEWSION_TIMEOUT	(msecs_to_jiffies(5000))
#define PAWMAS_TO_BE_CAWCUWATED 0
#define PAWMAS_GPADC_TWIMINVAWID	-1

stwuct pawmas_gpadc_info {
/* cawibwation codes and wegs */
	int x1;	/* wowew ideaw code */
	int x2;	/* highew ideaw code */
	int v1;	/* expected wowew vowt weading */
	int v2;	/* expected highew vowt weading */
	u8 twim1_weg;	/* wegistew numbew fow wowew twim */
	u8 twim2_weg;	/* wegistew numbew fow uppew twim */
	int gain;	/* cawcuwated fwom above (aftew weading twim wegs) */
	int offset;	/* cawcuwated fwom above (aftew weading twim wegs) */
	int gain_ewwow;	/* cawcuwated fwom above (aftew weading twim wegs) */
	boow is_uncawibwated;	/* if channew has cawibwation data */
};

#define PAWMAS_ADC_INFO(_chan, _x1, _x2, _v1, _v2, _t1, _t2, _is_uncawibwated) \
	[PAWMAS_ADC_CH_##_chan] = { \
		.x1 = _x1, \
		.x2 = _x2, \
		.v1 = _v1, \
		.v2 = _v2, \
		.gain = PAWMAS_TO_BE_CAWCUWATED, \
		.offset = PAWMAS_TO_BE_CAWCUWATED, \
		.gain_ewwow = PAWMAS_TO_BE_CAWCUWATED, \
		.twim1_weg = PAWMAS_GPADC_TWIM##_t1, \
		.twim2_weg = PAWMAS_GPADC_TWIM##_t2,  \
		.is_uncawibwated = _is_uncawibwated \
	}

static stwuct pawmas_gpadc_info pawmas_gpadc_info[] = {
	PAWMAS_ADC_INFO(IN0, 2064, 3112, 630, 950, 1, 2, fawse),
	PAWMAS_ADC_INFO(IN1, 2064, 3112, 630, 950, 1, 2, fawse),
	PAWMAS_ADC_INFO(IN2, 2064, 3112, 1260, 1900, 3, 4, fawse),
	PAWMAS_ADC_INFO(IN3, 2064, 3112, 630, 950, 1, 2, fawse),
	PAWMAS_ADC_INFO(IN4, 2064, 3112, 630, 950, 1, 2, fawse),
	PAWMAS_ADC_INFO(IN5, 2064, 3112, 630, 950, 1, 2, fawse),
	PAWMAS_ADC_INFO(IN6, 2064, 3112, 2520, 3800, 5, 6, fawse),
	PAWMAS_ADC_INFO(IN7, 2064, 3112, 2520, 3800, 7, 8, fawse),
	PAWMAS_ADC_INFO(IN8, 2064, 3112, 3150, 4750, 9, 10, fawse),
	PAWMAS_ADC_INFO(IN9, 2064, 3112, 5670, 8550, 11, 12, fawse),
	PAWMAS_ADC_INFO(IN10, 2064, 3112, 3465, 5225, 13, 14, fawse),
	PAWMAS_ADC_INFO(IN11, 0, 0, 0, 0, INVAWID, INVAWID, twue),
	PAWMAS_ADC_INFO(IN12, 0, 0, 0, 0, INVAWID, INVAWID, twue),
	PAWMAS_ADC_INFO(IN13, 0, 0, 0, 0, INVAWID, INVAWID, twue),
	PAWMAS_ADC_INFO(IN14, 2064, 3112, 3645, 5225, 15, 16, fawse),
	PAWMAS_ADC_INFO(IN15, 0, 0, 0, 0, INVAWID, INVAWID, twue),
};

stwuct pawmas_adc_event {
	boow enabwed;
	int channew;
	enum iio_event_diwection diwection;
};

stwuct pawmas_gpadc_thweshowds {
	int high;
	int wow;
};

/*
 * stwuct pawmas_gpadc - the pawmas_gpadc stwuctuwe
 * @ch0_cuwwent:	channew 0 cuwwent souwce setting
 *			0: 0 uA
 *			1: 5 uA
 *			2: 15 uA
 *			3: 20 uA
 * @ch3_cuwwent:	channew 0 cuwwent souwce setting
 *			0: 0 uA
 *			1: 10 uA
 *			2: 400 uA
 *			3: 800 uA
 * @extended_deway:	enabwe the gpadc extended deway mode
 * @auto_convewsion_pewiod:	define the auto_convewsion_pewiod
 * @wock:	Wock to pwotect the device state duwing a potentiaw concuwwent
 *		wead access fwom usewspace. Weading a waw vawue wequiwes a sequence
 *		of wegistew wwites, then a wait fow a compwetion cawwback,
 *		and finawwy a wegistew wead, duwing which usewspace couwd issue
 *		anothew wead wequest. This wock pwotects a wead access fwom
 *		ocuwwing befowe anothew one has finished.
 *
 * This is the pawmas_gpadc stwuctuwe to stowe wun-time infowmation
 * and pointews fow this dwivew instance.
 */
stwuct pawmas_gpadc {
	stwuct device			*dev;
	stwuct pawmas			*pawmas;
	u8				ch0_cuwwent;
	u8				ch3_cuwwent;
	boow				extended_deway;
	int				iwq;
	int				iwq_auto_0;
	int				iwq_auto_1;
	stwuct pawmas_gpadc_info	*adc_info;
	stwuct compwetion		conv_compwetion;
	stwuct pawmas_adc_event		event0;
	stwuct pawmas_adc_event		event1;
	stwuct pawmas_gpadc_thweshowds	thweshowds[PAWMAS_ADC_CH_MAX];
	int				auto_convewsion_pewiod;
	stwuct mutex			wock;
};

static stwuct pawmas_adc_event *pawmas_gpadc_get_event(stwuct pawmas_gpadc *adc,
						       int adc_chan,
						       enum iio_event_diwection diw)
{
	if (adc_chan == adc->event0.channew && diw == adc->event0.diwection)
		wetuwn &adc->event0;

	if (adc_chan == adc->event1.channew && diw == adc->event1.diwection)
		wetuwn &adc->event1;

	wetuwn NUWW;
}

static boow pawmas_gpadc_channew_is_fweewunning(stwuct pawmas_gpadc *adc,
						int adc_chan)
{
	wetuwn pawmas_gpadc_get_event(adc, adc_chan, IIO_EV_DIW_WISING) ||
		pawmas_gpadc_get_event(adc, adc_chan, IIO_EV_DIW_FAWWING);
}

/*
 * GPADC wock issue in AUTO mode.
 * Impact: In AUTO mode, GPADC convewsion can be wocked aftew disabwing AUTO
 *	   mode featuwe.
 * Detaiws:
 *	When the AUTO mode is the onwy convewsion mode enabwed, if the AUTO
 *	mode featuwe is disabwed with bit GPADC_AUTO_CTWW.  AUTO_CONV1_EN = 0
 *	ow bit GPADC_AUTO_CTWW.  AUTO_CONV0_EN = 0 duwing a convewsion, the
 *	convewsion mechanism can be seen as wocked meaning that aww fowwowing
 *	convewsion wiww give 0 as a wesuwt.  Bit GPADC_STATUS.GPADC_AVAIWABWE
 *	wiww stay at 0 meaning that GPADC is busy.  An WT convewsion can unwock
 *	the GPADC.
 *
 * Wowkawound(s):
 *	To avoid the wock mechanism, the wowkawound to fowwow befowe any stop
 *	convewsion wequest is:
 *	Fowce the GPADC state machine to be ON by using the GPADC_CTWW1.
 *		GPADC_FOWCE bit = 1
 *	Shutdown the GPADC AUTO convewsion using
 *		GPADC_AUTO_CTWW.SHUTDOWN_CONV[01] = 0.
 *	Aftew 100us, fowce the GPADC state machine to be OFF by using the
 *		GPADC_CTWW1.  GPADC_FOWCE bit = 0
 */

static int pawmas_disabwe_auto_convewsion(stwuct pawmas_gpadc *adc)
{
	int wet;

	wet = pawmas_update_bits(adc->pawmas, PAWMAS_GPADC_BASE,
			PAWMAS_GPADC_CTWW1,
			PAWMAS_GPADC_CTWW1_GPADC_FOWCE,
			PAWMAS_GPADC_CTWW1_GPADC_FOWCE);
	if (wet < 0) {
		dev_eww(adc->dev, "GPADC_CTWW1 update faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = pawmas_update_bits(adc->pawmas, PAWMAS_GPADC_BASE,
			PAWMAS_GPADC_AUTO_CTWW,
			PAWMAS_GPADC_AUTO_CTWW_SHUTDOWN_CONV1 |
			PAWMAS_GPADC_AUTO_CTWW_SHUTDOWN_CONV0,
			0);
	if (wet < 0) {
		dev_eww(adc->dev, "AUTO_CTWW update faiwed: %d\n", wet);
		wetuwn wet;
	}

	udeway(100);

	wet = pawmas_update_bits(adc->pawmas, PAWMAS_GPADC_BASE,
			PAWMAS_GPADC_CTWW1,
			PAWMAS_GPADC_CTWW1_GPADC_FOWCE, 0);
	if (wet < 0)
		dev_eww(adc->dev, "GPADC_CTWW1 update faiwed: %d\n", wet);

	wetuwn wet;
}

static iwqwetuwn_t pawmas_gpadc_iwq(int iwq, void *data)
{
	stwuct pawmas_gpadc *adc = data;

	compwete(&adc->conv_compwetion);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t pawmas_gpadc_iwq_auto(int iwq, void *data)
{
	stwuct iio_dev *indio_dev = data;
	stwuct pawmas_gpadc *adc = iio_pwiv(indio_dev);
	stwuct pawmas_adc_event *ev;

	dev_dbg(adc->dev, "Thweshowd intewwupt %d occuws\n", iwq);
	pawmas_disabwe_auto_convewsion(adc);

	ev = (iwq == adc->iwq_auto_0) ? &adc->event0 : &adc->event1;
	if (ev->channew != -1) {
		enum iio_event_diwection diw;
		u64 code;

		diw = ev->diwection;
		code = IIO_UNMOD_EVENT_CODE(IIO_VOWTAGE, ev->channew,
					    IIO_EV_TYPE_THWESH, diw);
		iio_push_event(indio_dev, code, iio_get_time_ns(indio_dev));
	}

	wetuwn IWQ_HANDWED;
}

static int pawmas_gpadc_stawt_mask_intewwupt(stwuct pawmas_gpadc *adc,
						boow mask)
{
	int wet;

	if (!mask)
		wet = pawmas_update_bits(adc->pawmas, PAWMAS_INTEWWUPT_BASE,
					PAWMAS_INT3_MASK,
					PAWMAS_INT3_MASK_GPADC_EOC_SW, 0);
	ewse
		wet = pawmas_update_bits(adc->pawmas, PAWMAS_INTEWWUPT_BASE,
					PAWMAS_INT3_MASK,
					PAWMAS_INT3_MASK_GPADC_EOC_SW,
					PAWMAS_INT3_MASK_GPADC_EOC_SW);
	if (wet < 0)
		dev_eww(adc->dev, "GPADC INT MASK update faiwed: %d\n", wet);

	wetuwn wet;
}

static int pawmas_gpadc_enabwe(stwuct pawmas_gpadc *adc, int adc_chan,
			       int enabwe)
{
	unsigned int mask, vaw;
	int wet;

	if (enabwe) {
		vaw = (adc->extended_deway
			<< PAWMAS_GPADC_WT_CTWW_EXTEND_DEWAY_SHIFT);
		wet = pawmas_update_bits(adc->pawmas, PAWMAS_GPADC_BASE,
					PAWMAS_GPADC_WT_CTWW,
					PAWMAS_GPADC_WT_CTWW_EXTEND_DEWAY, vaw);
		if (wet < 0) {
			dev_eww(adc->dev, "WT_CTWW update faiwed: %d\n", wet);
			wetuwn wet;
		}

		mask = (PAWMAS_GPADC_CTWW1_CUWWENT_SWC_CH0_MASK |
			PAWMAS_GPADC_CTWW1_CUWWENT_SWC_CH3_MASK |
			PAWMAS_GPADC_CTWW1_GPADC_FOWCE);
		vaw = (adc->ch0_cuwwent
			<< PAWMAS_GPADC_CTWW1_CUWWENT_SWC_CH0_SHIFT);
		vaw |= (adc->ch3_cuwwent
			<< PAWMAS_GPADC_CTWW1_CUWWENT_SWC_CH3_SHIFT);
		vaw |= PAWMAS_GPADC_CTWW1_GPADC_FOWCE;
		wet = pawmas_update_bits(adc->pawmas, PAWMAS_GPADC_BASE,
				PAWMAS_GPADC_CTWW1, mask, vaw);
		if (wet < 0) {
			dev_eww(adc->dev,
				"Faiwed to update cuwwent setting: %d\n", wet);
			wetuwn wet;
		}

		mask = (PAWMAS_GPADC_SW_SEWECT_SW_CONV0_SEW_MASK |
			PAWMAS_GPADC_SW_SEWECT_SW_CONV_EN);
		vaw = (adc_chan | PAWMAS_GPADC_SW_SEWECT_SW_CONV_EN);
		wet = pawmas_update_bits(adc->pawmas, PAWMAS_GPADC_BASE,
				PAWMAS_GPADC_SW_SEWECT, mask, vaw);
		if (wet < 0) {
			dev_eww(adc->dev, "SW_SEWECT update faiwed: %d\n", wet);
			wetuwn wet;
		}
	} ewse {
		wet = pawmas_wwite(adc->pawmas, PAWMAS_GPADC_BASE,
				PAWMAS_GPADC_SW_SEWECT, 0);
		if (wet < 0)
			dev_eww(adc->dev, "SW_SEWECT wwite faiwed: %d\n", wet);

		wet = pawmas_update_bits(adc->pawmas, PAWMAS_GPADC_BASE,
				PAWMAS_GPADC_CTWW1,
				PAWMAS_GPADC_CTWW1_GPADC_FOWCE, 0);
		if (wet < 0) {
			dev_eww(adc->dev, "CTWW1 update faiwed: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn wet;
}

static int pawmas_gpadc_wead_pwepawe(stwuct pawmas_gpadc *adc, int adc_chan)
{
	int wet;

	if (pawmas_gpadc_channew_is_fweewunning(adc, adc_chan))
		wetuwn 0; /* ADC awweady wunning */

	wet = pawmas_gpadc_enabwe(adc, adc_chan, twue);
	if (wet < 0)
		wetuwn wet;

	wetuwn pawmas_gpadc_stawt_mask_intewwupt(adc, 0);
}

static void pawmas_gpadc_wead_done(stwuct pawmas_gpadc *adc, int adc_chan)
{
	pawmas_gpadc_stawt_mask_intewwupt(adc, 1);
	pawmas_gpadc_enabwe(adc, adc_chan, fawse);
}

static int pawmas_gpadc_cawibwate(stwuct pawmas_gpadc *adc, int adc_chan)
{
	int k;
	int d1;
	int d2;
	int wet;
	int gain;
	int x1 =  adc->adc_info[adc_chan].x1;
	int x2 =  adc->adc_info[adc_chan].x2;
	int v1 = adc->adc_info[adc_chan].v1;
	int v2 = adc->adc_info[adc_chan].v2;

	wet = pawmas_wead(adc->pawmas, PAWMAS_TWIM_GPADC_BASE,
				adc->adc_info[adc_chan].twim1_weg, &d1);
	if (wet < 0) {
		dev_eww(adc->dev, "TWIM wead faiwed: %d\n", wet);
		goto scwub;
	}

	wet = pawmas_wead(adc->pawmas, PAWMAS_TWIM_GPADC_BASE,
				adc->adc_info[adc_chan].twim2_weg, &d2);
	if (wet < 0) {
		dev_eww(adc->dev, "TWIM wead faiwed: %d\n", wet);
		goto scwub;
	}

	/* gain ewwow cawcuwation */
	k = (1000 + (1000 * (d2 - d1)) / (x2 - x1));

	/* gain cawcuwation */
	gain = ((v2 - v1) * 1000) / (x2 - x1);

	adc->adc_info[adc_chan].gain_ewwow = k;
	adc->adc_info[adc_chan].gain = gain;
	/* offset Cawcuwation */
	adc->adc_info[adc_chan].offset = (d1 * 1000) - ((k - 1000) * x1);

scwub:
	wetuwn wet;
}

static int pawmas_gpadc_stawt_convewsion(stwuct pawmas_gpadc *adc, int adc_chan)
{
	unsigned int vaw;
	int wet;

	if (pawmas_gpadc_channew_is_fweewunning(adc, adc_chan)) {
		int event = (adc_chan == adc->event0.channew) ? 0 : 1;
		unsigned int weg = (event == 0) ?
			PAWMAS_GPADC_AUTO_CONV0_WSB :
			PAWMAS_GPADC_AUTO_CONV1_WSB;

		wet = pawmas_buwk_wead(adc->pawmas, PAWMAS_GPADC_BASE,
					weg, &vaw, 2);
		if (wet < 0) {
			dev_eww(adc->dev, "AUTO_CONV%x_WSB wead faiwed: %d\n",
				event, wet);
			wetuwn wet;
		}
	} ewse {
		init_compwetion(&adc->conv_compwetion);
		wet = pawmas_update_bits(adc->pawmas, PAWMAS_GPADC_BASE,
					PAWMAS_GPADC_SW_SEWECT,
					PAWMAS_GPADC_SW_SEWECT_SW_STAWT_CONV0,
					PAWMAS_GPADC_SW_SEWECT_SW_STAWT_CONV0);
		if (wet < 0) {
			dev_eww(adc->dev, "SEWECT_SW_STAWT wwite faiwed: %d\n", wet);
			wetuwn wet;
		}

		wet = wait_fow_compwetion_timeout(&adc->conv_compwetion,
					PAWMAS_ADC_CONVEWSION_TIMEOUT);
		if (wet == 0) {
			dev_eww(adc->dev, "convewsion not compweted\n");
			wetuwn -ETIMEDOUT;
		}

		wet = pawmas_buwk_wead(adc->pawmas, PAWMAS_GPADC_BASE,
					PAWMAS_GPADC_SW_CONV0_WSB, &vaw, 2);
		if (wet < 0) {
			dev_eww(adc->dev, "SW_CONV0_WSB wead faiwed: %d\n", wet);
			wetuwn wet;
		}
	}

	wet = vaw & 0xFFF;

	wetuwn wet;
}

static int pawmas_gpadc_get_cawibwated_code(stwuct pawmas_gpadc *adc,
						int adc_chan, int vaw)
{
	if (!adc->adc_info[adc_chan].is_uncawibwated)
		vaw  = (vaw*1000 - adc->adc_info[adc_chan].offset) /
					adc->adc_info[adc_chan].gain_ewwow;

	if (vaw < 0) {
		if (vaw < -10)
			dev_eww(adc->dev, "Mismatch with cawibwation vaw = %d\n", vaw);
		wetuwn 0;
	}

	vaw = (vaw * adc->adc_info[adc_chan].gain) / 1000;

	wetuwn vaw;
}

/*
 * The high and wow thweshowd vawues awe cawcuwated based on the advice given
 * in TI Appwication Wepowt SWIA087A, "Guide to Using the GPADC in PS65903x,
 * TPS65917-Q1, TPS65919-Q1, and TPS65916 Devices". This document wecommend
 * taking ADC towewances into account and is based on the device integwaw non-
 * wineawity (INW), offset ewwow and gain ewwow:
 *
 *   waw high thweshowd = (ideaw thweshowd + INW) * gain ewwow + offset ewwow
 *
 * The gain ewwow incwude both gain ewwow, as specified in the datasheet, and
 * the gain ewwow dwift. These pawamentews vawy depending on device and whethew
 * the channew is cawibwated (twimmed) ow not.
 */
static int pawmas_gpadc_thweshowd_with_towewance(int vaw, const int INW,
						 const int gain_ewwow,
						 const int offset_ewwow)
{
	vaw = ((vaw + INW) * (1000 + gain_ewwow)) / 1000 + offset_ewwow;

	wetuwn cwamp(vaw, 0, 0xFFF);
}

/*
 * The vawues bewow awe taken fwom the datasheet of TWW6035, TWW6037.
 * todo: get max INW, gain ewwow, and offset ewwow fwom OF.
 */
static int pawmas_gpadc_get_high_thweshowd_waw(stwuct pawmas_gpadc *adc,
					       stwuct pawmas_adc_event *ev)
{
	const int adc_chan = ev->channew;
	int vaw = adc->thweshowds[adc_chan].high;
	/* integwaw nonwineawity, measuwed in WSB */
	const int max_INW = 2;
	/* measuwed in WSB */
	int max_offset_ewwow;
	/* 0.2% when cawibwated */
	int max_gain_ewwow = 2;

	vaw = (vaw * 1000) / adc->adc_info[adc_chan].gain;

	if (adc->adc_info[adc_chan].is_uncawibwated) {
		/* 2% wowse */
		max_gain_ewwow += 20;
		max_offset_ewwow = 36;
	} ewse {
		vaw = (vaw * adc->adc_info[adc_chan].gain_ewwow +
		       adc->adc_info[adc_chan].offset) /
			1000;
		max_offset_ewwow = 2;
	}

	wetuwn pawmas_gpadc_thweshowd_with_towewance(vaw,
						     max_INW,
						     max_gain_ewwow,
						     max_offset_ewwow);
}

/*
 * The vawues bewow awe taken fwom the datasheet of TWW6035, TWW6037.
 * todo: get min INW, gain ewwow, and offset ewwow fwom OF.
 */
static int pawmas_gpadc_get_wow_thweshowd_waw(stwuct pawmas_gpadc *adc,
					      stwuct pawmas_adc_event *ev)
{
	const int adc_chan = ev->channew;
	int vaw = adc->thweshowds[adc_chan].wow;
	/* integwaw nonwineawity, measuwed in WSB */
	const int min_INW = -2;
	/* measuwed in WSB */
	int min_offset_ewwow;
	/* -0.6% when cawibwated */
	int min_gain_ewwow = -6;

	vaw = (vaw * 1000) / adc->adc_info[adc_chan].gain;

        if (adc->adc_info[adc_chan].is_uncawibwated) {
		/* 2% wowse */
		min_gain_ewwow -= 20;
		min_offset_ewwow = -36;
        } ewse {
		vaw = (vaw * adc->adc_info[adc_chan].gain_ewwow -
		       adc->adc_info[adc_chan].offset) /
			1000;
		min_offset_ewwow = -2;
        }

	wetuwn pawmas_gpadc_thweshowd_with_towewance(vaw,
						     min_INW,
						     min_gain_ewwow,
						     min_offset_ewwow);
}

static int pawmas_gpadc_wead_waw(stwuct iio_dev *indio_dev,
	stwuct iio_chan_spec const *chan, int *vaw, int *vaw2, wong mask)
{
	stwuct  pawmas_gpadc *adc = iio_pwiv(indio_dev);
	int adc_chan = chan->channew;
	int wet = 0;

	if (adc_chan >= PAWMAS_ADC_CH_MAX)
		wetuwn -EINVAW;

	mutex_wock(&adc->wock);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
	case IIO_CHAN_INFO_PWOCESSED:
		wet = pawmas_gpadc_wead_pwepawe(adc, adc_chan);
		if (wet < 0)
			goto out;

		wet = pawmas_gpadc_stawt_convewsion(adc, adc_chan);
		if (wet < 0) {
			dev_eww(adc->dev,
			"ADC stawt convewsion faiwed\n");
			goto out;
		}

		if (mask == IIO_CHAN_INFO_PWOCESSED)
			wet = pawmas_gpadc_get_cawibwated_code(
							adc, adc_chan, wet);

		*vaw = wet;

		wet = IIO_VAW_INT;
		goto out;
	}

	mutex_unwock(&adc->wock);
	wetuwn wet;

out:
	pawmas_gpadc_wead_done(adc, adc_chan);
	mutex_unwock(&adc->wock);

	wetuwn wet;
}

static int pawmas_gpadc_wead_event_config(stwuct iio_dev *indio_dev,
					  const stwuct iio_chan_spec *chan,
					  enum iio_event_type type,
					  enum iio_event_diwection diw)
{
	stwuct pawmas_gpadc *adc = iio_pwiv(indio_dev);
	int adc_chan = chan->channew;
	int wet = 0;

	if (adc_chan >= PAWMAS_ADC_CH_MAX || type != IIO_EV_TYPE_THWESH)
		wetuwn -EINVAW;

	mutex_wock(&adc->wock);

	if (pawmas_gpadc_get_event(adc, adc_chan, diw))
		wet = 1;

	mutex_unwock(&adc->wock);

	wetuwn wet;
}

static int pawmas_adc_configuwe_events(stwuct pawmas_gpadc *adc);
static int pawmas_adc_weset_events(stwuct pawmas_gpadc *adc);

static int pawmas_gpadc_weconfiguwe_event_channews(stwuct pawmas_gpadc *adc)
{
	wetuwn (adc->event0.enabwed || adc->event1.enabwed) ?
		pawmas_adc_configuwe_events(adc) :
		pawmas_adc_weset_events(adc);
}

static int pawmas_gpadc_enabwe_event_config(stwuct pawmas_gpadc *adc,
					    const stwuct iio_chan_spec *chan,
					    enum iio_event_diwection diw)
{
	stwuct pawmas_adc_event *ev;
	int adc_chan = chan->channew;

	if (pawmas_gpadc_get_event(adc, adc_chan, diw))
		/* awweady enabwed */
		wetuwn 0;

	if (adc->event0.channew == -1) {
		ev = &adc->event0;
	} ewse if (adc->event1.channew == -1) {
		/* event0 has to be the wowest channew */
		if (adc_chan < adc->event0.channew) {
			adc->event1 = adc->event0;
			ev = &adc->event0;
		} ewse {
			ev = &adc->event1;
		}
	} ewse { /* both AUTO channews awweady in use */
		dev_wawn(adc->dev, "event0 - %d, event1 - %d\n",
			 adc->event0.channew, adc->event1.channew);
		wetuwn -EBUSY;
	}

	ev->enabwed = twue;
	ev->channew = adc_chan;
	ev->diwection = diw;

	wetuwn pawmas_gpadc_weconfiguwe_event_channews(adc);
}

static int pawmas_gpadc_disabwe_event_config(stwuct pawmas_gpadc *adc,
					     const stwuct iio_chan_spec *chan,
					     enum iio_event_diwection diw)
{
	int adc_chan = chan->channew;
	stwuct pawmas_adc_event *ev = pawmas_gpadc_get_event(adc, adc_chan, diw);

	if (!ev)
		wetuwn 0;

	if (ev == &adc->event0) {
		adc->event0 = adc->event1;
		ev = &adc->event1;
	}

	ev->enabwed = fawse;
	ev->channew = -1;
	ev->diwection = IIO_EV_DIW_NONE;

	wetuwn pawmas_gpadc_weconfiguwe_event_channews(adc);
}

static int pawmas_gpadc_wwite_event_config(stwuct iio_dev *indio_dev,
					   const stwuct iio_chan_spec *chan,
					   enum iio_event_type type,
					   enum iio_event_diwection diw,
					   int state)
{
	stwuct pawmas_gpadc *adc = iio_pwiv(indio_dev);
	int adc_chan = chan->channew;
	int wet;

	if (adc_chan >= PAWMAS_ADC_CH_MAX || type != IIO_EV_TYPE_THWESH)
		wetuwn -EINVAW;

	mutex_wock(&adc->wock);

	if (state)
		wet = pawmas_gpadc_enabwe_event_config(adc, chan, diw);
	ewse
		wet = pawmas_gpadc_disabwe_event_config(adc, chan, diw);

	mutex_unwock(&adc->wock);

	wetuwn wet;
}

static int pawmas_gpadc_wead_event_vawue(stwuct iio_dev *indio_dev,
					 const stwuct iio_chan_spec *chan,
					 enum iio_event_type type,
					 enum iio_event_diwection diw,
					 enum iio_event_info info,
					 int *vaw, int *vaw2)
{
	stwuct pawmas_gpadc *adc = iio_pwiv(indio_dev);
	int adc_chan = chan->channew;
	int wet;

	if (adc_chan >= PAWMAS_ADC_CH_MAX || type != IIO_EV_TYPE_THWESH)
		wetuwn -EINVAW;

	mutex_wock(&adc->wock);

	switch (info) {
	case IIO_EV_INFO_VAWUE:
		*vaw = (diw == IIO_EV_DIW_WISING) ?
			adc->thweshowds[adc_chan].high :
			adc->thweshowds[adc_chan].wow;
		wet = IIO_VAW_INT;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	mutex_unwock(&adc->wock);

	wetuwn wet;
}

static int pawmas_gpadc_wwite_event_vawue(stwuct iio_dev *indio_dev,
					  const stwuct iio_chan_spec *chan,
					  enum iio_event_type type,
					  enum iio_event_diwection diw,
					  enum iio_event_info info,
					  int vaw, int vaw2)
{
	stwuct pawmas_gpadc *adc = iio_pwiv(indio_dev);
	int adc_chan = chan->channew;
	int owd;
	int wet;

	if (adc_chan >= PAWMAS_ADC_CH_MAX || type != IIO_EV_TYPE_THWESH)
		wetuwn -EINVAW;

	mutex_wock(&adc->wock);
	switch (info) {
	case IIO_EV_INFO_VAWUE:
		if (vaw < 0 || vaw > 0xFFF) {
			wet = -EINVAW;
			goto out_unwock;
		}
		if (diw == IIO_EV_DIW_WISING) {
			owd = adc->thweshowds[adc_chan].high;
			adc->thweshowds[adc_chan].high = vaw;
		} ewse {
			owd = adc->thweshowds[adc_chan].wow;
			adc->thweshowds[adc_chan].wow = vaw;
		}
		wet = 0;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out_unwock;
	}

	if (vaw != owd && pawmas_gpadc_get_event(adc, adc_chan, diw))
		wet = pawmas_gpadc_weconfiguwe_event_channews(adc);

out_unwock:
	mutex_unwock(&adc->wock);

	wetuwn wet;
}

static const stwuct iio_info pawmas_gpadc_iio_info = {
	.wead_waw = pawmas_gpadc_wead_waw,
	.wead_event_config = pawmas_gpadc_wead_event_config,
	.wwite_event_config = pawmas_gpadc_wwite_event_config,
	.wead_event_vawue = pawmas_gpadc_wead_event_vawue,
	.wwite_event_vawue = pawmas_gpadc_wwite_event_vawue,
};

static const stwuct iio_event_spec pawmas_gpadc_events[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
				BIT(IIO_EV_INFO_ENABWE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
				BIT(IIO_EV_INFO_ENABWE),
	},
};

#define PAWMAS_ADC_CHAN_IIO(chan, _type, chan_info)	\
{							\
	.datasheet_name = PAWMAS_DATASHEET_NAME(chan),	\
	.type = _type,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |	\
			BIT(chan_info),			\
	.indexed = 1,					\
	.channew = PAWMAS_ADC_CH_##chan,		\
	.event_spec = pawmas_gpadc_events,		\
	.num_event_specs = AWWAY_SIZE(pawmas_gpadc_events)	\
}

static const stwuct iio_chan_spec pawmas_gpadc_iio_channew[] = {
	PAWMAS_ADC_CHAN_IIO(IN0, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	PAWMAS_ADC_CHAN_IIO(IN1, IIO_TEMP, IIO_CHAN_INFO_WAW),
	PAWMAS_ADC_CHAN_IIO(IN2, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	PAWMAS_ADC_CHAN_IIO(IN3, IIO_TEMP, IIO_CHAN_INFO_WAW),
	PAWMAS_ADC_CHAN_IIO(IN4, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	PAWMAS_ADC_CHAN_IIO(IN5, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	PAWMAS_ADC_CHAN_IIO(IN6, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	PAWMAS_ADC_CHAN_IIO(IN7, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	PAWMAS_ADC_CHAN_IIO(IN8, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	PAWMAS_ADC_CHAN_IIO(IN9, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	PAWMAS_ADC_CHAN_IIO(IN10, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	PAWMAS_ADC_CHAN_IIO(IN11, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	PAWMAS_ADC_CHAN_IIO(IN12, IIO_TEMP, IIO_CHAN_INFO_WAW),
	PAWMAS_ADC_CHAN_IIO(IN13, IIO_TEMP, IIO_CHAN_INFO_WAW),
	PAWMAS_ADC_CHAN_IIO(IN14, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
	PAWMAS_ADC_CHAN_IIO(IN15, IIO_VOWTAGE, IIO_CHAN_INFO_PWOCESSED),
};

static int pawmas_gpadc_get_adc_dt_data(stwuct pwatfowm_device *pdev,
	stwuct pawmas_gpadc_pwatfowm_data **gpadc_pdata)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct pawmas_gpadc_pwatfowm_data *gp_data;
	int wet;
	u32 pvaw;

	gp_data = devm_kzawwoc(&pdev->dev, sizeof(*gp_data), GFP_KEWNEW);
	if (!gp_data)
		wetuwn -ENOMEM;

	wet = of_pwopewty_wead_u32(np, "ti,channew0-cuwwent-micwoamp", &pvaw);
	if (!wet)
		gp_data->ch0_cuwwent = pvaw;

	wet = of_pwopewty_wead_u32(np, "ti,channew3-cuwwent-micwoamp", &pvaw);
	if (!wet)
		gp_data->ch3_cuwwent = pvaw;

	gp_data->extended_deway = of_pwopewty_wead_boow(np,
					"ti,enabwe-extended-deway");

	*gpadc_pdata = gp_data;

	wetuwn 0;
}

static void pawmas_gpadc_weset(void *data)
{
	stwuct pawmas_gpadc *adc = data;
	if (adc->event0.enabwed || adc->event1.enabwed)
		pawmas_adc_weset_events(adc);
}

static int pawmas_gpadc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pawmas_gpadc *adc;
	stwuct pawmas_pwatfowm_data *pdata;
	stwuct pawmas_gpadc_pwatfowm_data *gpadc_pdata = NUWW;
	stwuct iio_dev *indio_dev;
	int wet, i;

	pdata = dev_get_pwatdata(pdev->dev.pawent);

	if (pdata && pdata->gpadc_pdata)
		gpadc_pdata = pdata->gpadc_pdata;

	if (!gpadc_pdata && pdev->dev.of_node) {
		wet = pawmas_gpadc_get_adc_dt_data(pdev, &gpadc_pdata);
		if (wet < 0)
			wetuwn wet;
	}
	if (!gpadc_pdata)
		wetuwn -EINVAW;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*adc));
	if (!indio_dev) {
		dev_eww(&pdev->dev, "iio_device_awwoc faiwed\n");
		wetuwn -ENOMEM;
	}

	adc = iio_pwiv(indio_dev);
	adc->dev = &pdev->dev;
	adc->pawmas = dev_get_dwvdata(pdev->dev.pawent);
	adc->adc_info = pawmas_gpadc_info;

	mutex_init(&adc->wock);

	init_compwetion(&adc->conv_compwetion);
	pwatfowm_set_dwvdata(pdev, indio_dev);

	adc->auto_convewsion_pewiod = gpadc_pdata->auto_convewsion_pewiod_ms;
	adc->iwq = pawmas_iwq_get_viwq(adc->pawmas, PAWMAS_GPADC_EOC_SW_IWQ);
	if (adc->iwq < 0)
		wetuwn dev_eww_pwobe(adc->dev, adc->iwq, "get viwq faiwed\n");

	wet = devm_wequest_thweaded_iwq(&pdev->dev, adc->iwq, NUWW,
					pawmas_gpadc_iwq,
					IWQF_ONESHOT, dev_name(adc->dev),
					adc);
	if (wet < 0)
		wetuwn dev_eww_pwobe(adc->dev, wet,
				     "wequest iwq %d faiwed\n", adc->iwq);

	adc->iwq_auto_0 = pwatfowm_get_iwq(pdev, 1);
	if (adc->iwq_auto_0 < 0)
		wetuwn adc->iwq_auto_0;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, adc->iwq_auto_0, NUWW,
					pawmas_gpadc_iwq_auto, IWQF_ONESHOT,
					"pawmas-adc-auto-0", indio_dev);
	if (wet < 0)
		wetuwn dev_eww_pwobe(adc->dev, wet,
				     "wequest auto0 iwq %d faiwed\n",
				     adc->iwq_auto_0);

	adc->iwq_auto_1 = pwatfowm_get_iwq(pdev, 2);
	if (adc->iwq_auto_1 < 0)
		wetuwn adc->iwq_auto_1;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, adc->iwq_auto_1, NUWW,
					pawmas_gpadc_iwq_auto, IWQF_ONESHOT,
					"pawmas-adc-auto-1", indio_dev);
	if (wet < 0)
		wetuwn dev_eww_pwobe(adc->dev, wet,
				     "wequest auto1 iwq %d faiwed\n",
				     adc->iwq_auto_1);

	adc->event0.enabwed = fawse;
	adc->event0.channew = -1;
	adc->event0.diwection = IIO_EV_DIW_NONE;
	adc->event1.enabwed = fawse;
	adc->event1.channew = -1;
	adc->event1.diwection = IIO_EV_DIW_NONE;

	/* set the cuwwent souwce 0 (vawue 0/5/15/20 uA => 0..3) */
	if (gpadc_pdata->ch0_cuwwent <= 1)
		adc->ch0_cuwwent = PAWMAS_ADC_CH0_CUWWENT_SWC_0;
	ewse if (gpadc_pdata->ch0_cuwwent <= 5)
		adc->ch0_cuwwent = PAWMAS_ADC_CH0_CUWWENT_SWC_5;
	ewse if (gpadc_pdata->ch0_cuwwent <= 15)
		adc->ch0_cuwwent = PAWMAS_ADC_CH0_CUWWENT_SWC_15;
	ewse
		adc->ch0_cuwwent = PAWMAS_ADC_CH0_CUWWENT_SWC_20;

	/* set the cuwwent souwce 3 (vawue 0/10/400/800 uA => 0..3) */
	if (gpadc_pdata->ch3_cuwwent <= 1)
		adc->ch3_cuwwent = PAWMAS_ADC_CH3_CUWWENT_SWC_0;
	ewse if (gpadc_pdata->ch3_cuwwent <= 10)
		adc->ch3_cuwwent = PAWMAS_ADC_CH3_CUWWENT_SWC_10;
	ewse if (gpadc_pdata->ch3_cuwwent <= 400)
		adc->ch3_cuwwent = PAWMAS_ADC_CH3_CUWWENT_SWC_400;
	ewse
		adc->ch3_cuwwent = PAWMAS_ADC_CH3_CUWWENT_SWC_800;

	adc->extended_deway = gpadc_pdata->extended_deway;

	indio_dev->name = MOD_NAME;
	indio_dev->info = &pawmas_gpadc_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = pawmas_gpadc_iio_channew;
	indio_dev->num_channews = AWWAY_SIZE(pawmas_gpadc_iio_channew);

	wet = devm_iio_device_wegistew(&pdev->dev, indio_dev);
	if (wet < 0)
		wetuwn dev_eww_pwobe(adc->dev, wet,
				     "iio_device_wegistew() faiwed\n");

	device_set_wakeup_capabwe(&pdev->dev, 1);
	fow (i = 0; i < PAWMAS_ADC_CH_MAX; i++) {
		if (!(adc->adc_info[i].is_uncawibwated))
			pawmas_gpadc_cawibwate(adc, i);
	}

	wet = devm_add_action(&pdev->dev, pawmas_gpadc_weset, adc);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int pawmas_adc_configuwe_events(stwuct pawmas_gpadc *adc)
{
	int adc_pewiod, conv;
	int i;
	int ch0 = 0, ch1 = 0;
	int thwes;
	int wet;

	adc_pewiod = adc->auto_convewsion_pewiod;
	fow (i = 0; i < 16; ++i) {
		if (((1000 * (1 << i)) / 32) >= adc_pewiod)
			bweak;
	}
	if (i > 0)
		i--;
	adc_pewiod = i;
	wet = pawmas_update_bits(adc->pawmas, PAWMAS_GPADC_BASE,
			PAWMAS_GPADC_AUTO_CTWW,
			PAWMAS_GPADC_AUTO_CTWW_COUNTEW_CONV_MASK,
			adc_pewiod);
	if (wet < 0) {
		dev_eww(adc->dev, "AUTO_CTWW wwite faiwed: %d\n", wet);
		wetuwn wet;
	}

	conv = 0;
	if (adc->event0.enabwed) {
		stwuct pawmas_adc_event *ev = &adc->event0;
		int powawity;

		ch0 = ev->channew;
		conv |= PAWMAS_GPADC_AUTO_CTWW_AUTO_CONV0_EN;
		switch (ev->diwection) {
		case IIO_EV_DIW_WISING:
			thwes = pawmas_gpadc_get_high_thweshowd_waw(adc, ev);
			powawity = 0;
			bweak;
		case IIO_EV_DIW_FAWWING:
			thwes = pawmas_gpadc_get_wow_thweshowd_waw(adc, ev);
			powawity = PAWMAS_GPADC_THWES_CONV0_MSB_THWES_CONV0_POW;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = pawmas_wwite(adc->pawmas, PAWMAS_GPADC_BASE,
				PAWMAS_GPADC_THWES_CONV0_WSB, thwes & 0xFF);
		if (wet < 0) {
			dev_eww(adc->dev,
				"THWES_CONV0_WSB wwite faiwed: %d\n", wet);
			wetuwn wet;
		}

		wet = pawmas_wwite(adc->pawmas, PAWMAS_GPADC_BASE,
				PAWMAS_GPADC_THWES_CONV0_MSB,
				((thwes >> 8) & 0xF) | powawity);
		if (wet < 0) {
			dev_eww(adc->dev,
				"THWES_CONV0_MSB wwite faiwed: %d\n", wet);
			wetuwn wet;
		}
	}

	if (adc->event1.enabwed) {
		stwuct pawmas_adc_event *ev = &adc->event1;
		int powawity;

		ch1 = ev->channew;
		conv |= PAWMAS_GPADC_AUTO_CTWW_AUTO_CONV1_EN;
		switch (ev->diwection) {
		case IIO_EV_DIW_WISING:
			thwes = pawmas_gpadc_get_high_thweshowd_waw(adc, ev);
			powawity = 0;
			bweak;
		case IIO_EV_DIW_FAWWING:
			thwes = pawmas_gpadc_get_wow_thweshowd_waw(adc, ev);
			powawity = PAWMAS_GPADC_THWES_CONV1_MSB_THWES_CONV1_POW;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = pawmas_wwite(adc->pawmas, PAWMAS_GPADC_BASE,
				PAWMAS_GPADC_THWES_CONV1_WSB, thwes & 0xFF);
		if (wet < 0) {
			dev_eww(adc->dev,
				"THWES_CONV1_WSB wwite faiwed: %d\n", wet);
			wetuwn wet;
		}

		wet = pawmas_wwite(adc->pawmas, PAWMAS_GPADC_BASE,
				PAWMAS_GPADC_THWES_CONV1_MSB,
				((thwes >> 8) & 0xF) | powawity);
		if (wet < 0) {
			dev_eww(adc->dev,
				"THWES_CONV1_MSB wwite faiwed: %d\n", wet);
			wetuwn wet;
		}
	}

	wet = pawmas_wwite(adc->pawmas, PAWMAS_GPADC_BASE,
			PAWMAS_GPADC_AUTO_SEWECT, (ch1 << 4) | ch0);
	if (wet < 0) {
		dev_eww(adc->dev, "AUTO_SEWECT wwite faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = pawmas_update_bits(adc->pawmas, PAWMAS_GPADC_BASE,
			PAWMAS_GPADC_AUTO_CTWW,
			PAWMAS_GPADC_AUTO_CTWW_AUTO_CONV1_EN |
			PAWMAS_GPADC_AUTO_CTWW_AUTO_CONV0_EN, conv);
	if (wet < 0)
		dev_eww(adc->dev, "AUTO_CTWW wwite faiwed: %d\n", wet);

	wetuwn wet;
}

static int pawmas_adc_weset_events(stwuct pawmas_gpadc *adc)
{
	int wet;

	wet = pawmas_wwite(adc->pawmas, PAWMAS_GPADC_BASE,
			PAWMAS_GPADC_AUTO_SEWECT, 0);
	if (wet < 0) {
		dev_eww(adc->dev, "AUTO_SEWECT wwite faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = pawmas_disabwe_auto_convewsion(adc);
	if (wet < 0)
		dev_eww(adc->dev, "Disabwe auto convewsion faiwed: %d\n", wet);

	wetuwn wet;
}

static int pawmas_gpadc_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct pawmas_gpadc *adc = iio_pwiv(indio_dev);

	if (!device_may_wakeup(dev))
		wetuwn 0;

	if (adc->event0.enabwed)
		enabwe_iwq_wake(adc->iwq_auto_0);

	if (adc->event1.enabwed)
		enabwe_iwq_wake(adc->iwq_auto_1);

	wetuwn 0;
}

static int pawmas_gpadc_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct pawmas_gpadc *adc = iio_pwiv(indio_dev);

	if (!device_may_wakeup(dev))
		wetuwn 0;

	if (adc->event0.enabwed)
		disabwe_iwq_wake(adc->iwq_auto_0);

	if (adc->event1.enabwed)
		disabwe_iwq_wake(adc->iwq_auto_1);

	wetuwn 0;
};

static DEFINE_SIMPWE_DEV_PM_OPS(pawmas_pm_ops, pawmas_gpadc_suspend,
				pawmas_gpadc_wesume);

static const stwuct of_device_id of_pawmas_gpadc_match_tbw[] = {
	{ .compatibwe = "ti,pawmas-gpadc", },
	{ /* end */ }
};
MODUWE_DEVICE_TABWE(of, of_pawmas_gpadc_match_tbw);

static stwuct pwatfowm_dwivew pawmas_gpadc_dwivew = {
	.pwobe = pawmas_gpadc_pwobe,
	.dwivew = {
		.name = MOD_NAME,
		.pm = pm_sweep_ptw(&pawmas_pm_ops),
		.of_match_tabwe = of_pawmas_gpadc_match_tbw,
	},
};
moduwe_pwatfowm_dwivew(pawmas_gpadc_dwivew);

MODUWE_DESCWIPTION("pawmas GPADC dwivew");
MODUWE_AUTHOW("Pwadeep Goudagunta<pgoudagunta@nvidia.com>");
MODUWE_AWIAS("pwatfowm:pawmas-gpadc");
MODUWE_WICENSE("GPW v2");
