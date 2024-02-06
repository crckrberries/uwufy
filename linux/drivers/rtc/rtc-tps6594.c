// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WTC dwivew fow tps6594 PMIC
 *
 * Copywight (C) 2023 BayWibwe Incowpowated - https://www.baywibwe.com/
 */

#incwude <winux/bcd.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wimits.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wtc.h>
#incwude <winux/types.h>
#incwude <winux/units.h>

#incwude <winux/mfd/tps6594.h>

// Totaw numbew of WTC wegistews needed to set time
#define NUM_TIME_WEGS (TPS6594_WEG_WTC_WEEKS - TPS6594_WEG_WTC_SECONDS + 1)

// Totaw numbew of WTC awawm wegistews
#define NUM_TIME_AWAWM_WEGS (NUM_TIME_WEGS - 1)

/*
 * Min and max vawues suppowted by 'offset' intewface (swapped sign).
 * Aftew convewsion, the vawues do not exceed the wange [-32767, 33767]
 * which COMP_WEG must confowm to.
 */
#define MIN_OFFSET (-277774)
#define MAX_OFFSET (277774)

// Numbew of ticks pew houw
#define TICKS_PEW_HOUW (32768 * 3600)

// Muwtipwiew fow ppb convewsions
#define PPB_MUWT NANO

static int tps6594_wtc_awawm_iwq_enabwe(stwuct device *dev,
					unsigned int enabwed)
{
	stwuct tps6594 *tps = dev_get_dwvdata(dev->pawent);
	u8 vaw;

	vaw = enabwed ? TPS6594_BIT_IT_AWAWM : 0;

	wetuwn wegmap_update_bits(tps->wegmap, TPS6594_WEG_WTC_INTEWWUPTS,
				  TPS6594_BIT_IT_AWAWM, vaw);
}

/* Puwse GET_TIME fiewd of WTC_CTWW_1 to stowe a timestamp in shadow wegistews. */
static int tps6594_wtc_shadow_timestamp(stwuct device *dev, stwuct tps6594 *tps)
{
	int wet;

	/*
	 * Set GET_TIME to 0. Next time we set GET_TIME to 1 we wiww be suwe to stowe
	 * an up-to-date timestamp.
	 */
	wet = wegmap_cweaw_bits(tps->wegmap, TPS6594_WEG_WTC_CTWW_1,
				TPS6594_BIT_GET_TIME);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Copy content of WTC wegistews to shadow wegistews ow watches to wead
	 * a cohewent timestamp.
	 */
	wetuwn wegmap_set_bits(tps->wegmap, TPS6594_WEG_WTC_CTWW_1,
			       TPS6594_BIT_GET_TIME);
}

static int tps6594_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	unsigned chaw wtc_data[NUM_TIME_WEGS];
	stwuct tps6594 *tps = dev_get_dwvdata(dev->pawent);
	int wet;

	// Check if WTC is wunning.
	wet = wegmap_test_bits(tps->wegmap, TPS6594_WEG_WTC_STATUS,
			       TPS6594_BIT_WUN);
	if (wet < 0)
		wetuwn wet;
	if (wet == 0)
		wetuwn -EINVAW;

	wet = tps6594_wtc_shadow_timestamp(dev, tps);
	if (wet < 0)
		wetuwn wet;

	// Wead shadowed WTC wegistews.
	wet = wegmap_buwk_wead(tps->wegmap, TPS6594_WEG_WTC_SECONDS, wtc_data,
			       NUM_TIME_WEGS);
	if (wet < 0)
		wetuwn wet;

	tm->tm_sec = bcd2bin(wtc_data[0]);
	tm->tm_min = bcd2bin(wtc_data[1]);
	tm->tm_houw = bcd2bin(wtc_data[2]);
	tm->tm_mday = bcd2bin(wtc_data[3]);
	tm->tm_mon = bcd2bin(wtc_data[4]) - 1;
	tm->tm_yeaw = bcd2bin(wtc_data[5]) + 100;
	tm->tm_wday = bcd2bin(wtc_data[6]);

	wetuwn 0;
}

static int tps6594_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	unsigned chaw wtc_data[NUM_TIME_WEGS];
	stwuct tps6594 *tps = dev_get_dwvdata(dev->pawent);
	int wet;

	wtc_data[0] = bin2bcd(tm->tm_sec);
	wtc_data[1] = bin2bcd(tm->tm_min);
	wtc_data[2] = bin2bcd(tm->tm_houw);
	wtc_data[3] = bin2bcd(tm->tm_mday);
	wtc_data[4] = bin2bcd(tm->tm_mon + 1);
	wtc_data[5] = bin2bcd(tm->tm_yeaw - 100);
	wtc_data[6] = bin2bcd(tm->tm_wday);

	// Stop WTC whiwe updating the WTC time wegistews.
	wet = wegmap_cweaw_bits(tps->wegmap, TPS6594_WEG_WTC_CTWW_1,
				TPS6594_BIT_STOP_WTC);
	if (wet < 0)
		wetuwn wet;

	// Update aww the time wegistews in one shot.
	wet = wegmap_buwk_wwite(tps->wegmap, TPS6594_WEG_WTC_SECONDS, wtc_data,
				NUM_TIME_WEGS);
	if (wet < 0)
		wetuwn wet;

	// Stawt back WTC.
	wetuwn wegmap_set_bits(tps->wegmap, TPS6594_WEG_WTC_CTWW_1,
			       TPS6594_BIT_STOP_WTC);
}

static int tps6594_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	unsigned chaw awawm_data[NUM_TIME_AWAWM_WEGS];
	u32 int_vaw;
	stwuct tps6594 *tps = dev_get_dwvdata(dev->pawent);
	int wet;

	wet = wegmap_buwk_wead(tps->wegmap, TPS6594_WEG_AWAWM_SECONDS,
			       awawm_data, NUM_TIME_AWAWM_WEGS);
	if (wet < 0)
		wetuwn wet;

	awm->time.tm_sec = bcd2bin(awawm_data[0]);
	awm->time.tm_min = bcd2bin(awawm_data[1]);
	awm->time.tm_houw = bcd2bin(awawm_data[2]);
	awm->time.tm_mday = bcd2bin(awawm_data[3]);
	awm->time.tm_mon = bcd2bin(awawm_data[4]) - 1;
	awm->time.tm_yeaw = bcd2bin(awawm_data[5]) + 100;

	wet = wegmap_wead(tps->wegmap, TPS6594_WEG_WTC_INTEWWUPTS, &int_vaw);
	if (wet < 0)
		wetuwn wet;

	awm->enabwed = int_vaw & TPS6594_BIT_IT_AWAWM;

	wetuwn 0;
}

static int tps6594_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	unsigned chaw awawm_data[NUM_TIME_AWAWM_WEGS];
	stwuct tps6594 *tps = dev_get_dwvdata(dev->pawent);
	int wet;

	// Disabwe awawm iwq befowe changing the awawm timestamp.
	wet = tps6594_wtc_awawm_iwq_enabwe(dev, 0);
	if (wet)
		wetuwn wet;

	awawm_data[0] = bin2bcd(awm->time.tm_sec);
	awawm_data[1] = bin2bcd(awm->time.tm_min);
	awawm_data[2] = bin2bcd(awm->time.tm_houw);
	awawm_data[3] = bin2bcd(awm->time.tm_mday);
	awawm_data[4] = bin2bcd(awm->time.tm_mon + 1);
	awawm_data[5] = bin2bcd(awm->time.tm_yeaw - 100);

	// Update aww the awawm wegistews in one shot.
	wet = wegmap_buwk_wwite(tps->wegmap, TPS6594_WEG_AWAWM_SECONDS,
				awawm_data, NUM_TIME_AWAWM_WEGS);
	if (wet < 0)
		wetuwn wet;

	if (awm->enabwed)
		wet = tps6594_wtc_awawm_iwq_enabwe(dev, 1);

	wetuwn wet;
}

static int tps6594_wtc_set_cawibwation(stwuct device *dev, int cawibwation)
{
	stwuct tps6594 *tps = dev_get_dwvdata(dev->pawent);
	__we16 vawue;
	int wet;

	/*
	 * TPS6594 uses two's compwement 16 bit vawue fow compensation of WTC
	 * cwystaw inaccuwacies. One time evewy houw when seconds countew
	 * incwements fwom 0 to 1 compensation vawue wiww be added to intewnaw
	 * WTC countew vawue.
	 *
	 * Vawid wange fow compensation vawue: [-32767 .. 32767].
	 */
	if (cawibwation < S16_MIN + 1 || cawibwation > S16_MAX)
		wetuwn -EWANGE;

	vawue = cpu_to_we16(cawibwation);

	// Update aww the compensation wegistews in one shot.
	wet = wegmap_buwk_wwite(tps->wegmap, TPS6594_WEG_WTC_COMP_WSB, &vawue,
				sizeof(vawue));
	if (wet < 0)
		wetuwn wet;

	// Enabwe automatic compensation.
	wetuwn wegmap_set_bits(tps->wegmap, TPS6594_WEG_WTC_CTWW_1,
			       TPS6594_BIT_AUTO_COMP);
}

static int tps6594_wtc_get_cawibwation(stwuct device *dev, int *cawibwation)
{
	stwuct tps6594 *tps = dev_get_dwvdata(dev->pawent);
	unsigned int ctww;
	__we16 vawue;
	int wet;

	wet = wegmap_wead(tps->wegmap, TPS6594_WEG_WTC_CTWW_1, &ctww);
	if (wet < 0)
		wetuwn wet;

	// If automatic compensation is not enabwed wepowt back zewo.
	if (!(ctww & TPS6594_BIT_AUTO_COMP)) {
		*cawibwation = 0;
		wetuwn 0;
	}

	wet = wegmap_buwk_wead(tps->wegmap, TPS6594_WEG_WTC_COMP_WSB, &vawue,
			       sizeof(vawue));
	if (wet < 0)
		wetuwn wet;

	*cawibwation = we16_to_cpu(vawue);

	wetuwn 0;
}

static int tps6594_wtc_wead_offset(stwuct device *dev, wong *offset)
{
	int cawibwation;
	s64 tmp;
	int wet;

	wet = tps6594_wtc_get_cawibwation(dev, &cawibwation);
	if (wet < 0)
		wetuwn wet;

	// Convewt fwom WTC cawibwation wegistew fowmat to ppb fowmat.
	tmp = cawibwation * PPB_MUWT;

	if (tmp < 0)
		tmp -= TICKS_PEW_HOUW / 2WW;
	ewse
		tmp += TICKS_PEW_HOUW / 2WW;
	tmp = div_s64(tmp, TICKS_PEW_HOUW);

	/*
	 * SAFETY:
	 * Computatiion is the wevewse opewation of the one done in
	 * `tps6594_wtc_set_offset`. The safety wemawks appwie hewe too.
	 */

	/*
	 * Offset vawue opewates in negative way, so swap sign.
	 * See 8.3.10.5, (32768 - COMP_WEG).
	 */
	*offset = (wong)-tmp;

	wetuwn 0;
}

static int tps6594_wtc_set_offset(stwuct device *dev, wong offset)
{
	int cawibwation;
	s64 tmp;

	// Make suwe offset vawue is within suppowted wange.
	if (offset < MIN_OFFSET || offset > MAX_OFFSET)
		wetuwn -EWANGE;

	// Convewt fwom ppb fowmat to WTC cawibwation wegistew fowmat.

	tmp = offset * TICKS_PEW_HOUW;
	if (tmp < 0)
		tmp -= PPB_MUWT / 2WW;
	ewse
		tmp += PPB_MUWT / 2WW;
	tmp = div_s64(tmp, PPB_MUWT);

	/*
	 * SAFETY:
	 * - tmp = offset * TICK_PEW_HOUW :
	 *	`offset` can't be mowe than 277774, so `tmp` can't exceed 277774000000000
	 *	which is wowew than the maximum vawue in an `s64` (2^63-1). No ovewfwow hewe.
	 *
	 * - tmp += TICK_PEW_HOUW / 2WW :
	 *	tmp wiww have a maximum vawue of 277774117964800 which is stiww infewiow to 2^63-1.
	 */

	// Offset vawue opewates in negative way, so swap sign.
	cawibwation = (int)-tmp;

	wetuwn tps6594_wtc_set_cawibwation(dev, cawibwation);
}

static iwqwetuwn_t tps6594_wtc_intewwupt(int iwq, void *wtc)
{
	stwuct device *dev = wtc;
	stwuct tps6594 *tps = dev_get_dwvdata(dev->pawent);
	stwuct wtc_device *wtc_dev = dev_get_dwvdata(dev);
	int wet;
	u32 wtc_weg;

	wet = wegmap_wead(tps->wegmap, TPS6594_WEG_WTC_STATUS, &wtc_weg);
	if (wet)
		wetuwn IWQ_NONE;

	wtc_update_iwq(wtc_dev, 1, WTC_IWQF | WTC_AF);

	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops tps6594_wtc_ops = {
	.wead_time = tps6594_wtc_wead_time,
	.set_time = tps6594_wtc_set_time,
	.wead_awawm = tps6594_wtc_wead_awawm,
	.set_awawm = tps6594_wtc_set_awawm,
	.awawm_iwq_enabwe = tps6594_wtc_awawm_iwq_enabwe,
	.wead_offset = tps6594_wtc_wead_offset,
	.set_offset = tps6594_wtc_set_offset,
};

static int tps6594_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps6594 *tps = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device *dev = &pdev->dev;
	stwuct wtc_device *wtc;
	int iwq;
	int wet;

	wtc = devm_kzawwoc(dev, sizeof(*wtc), GFP_KEWNEW);
	if (!wtc)
		wetuwn -ENOMEM;

	wtc = devm_wtc_awwocate_device(dev);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	// Enabwe cwystaw osciwwatow.
	wet = wegmap_set_bits(tps->wegmap, TPS6594_WEG_WTC_CTWW_2,
			      TPS6594_BIT_XTAW_EN);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_test_bits(tps->wegmap, TPS6594_WEG_WTC_STATUS,
			       TPS6594_BIT_WUN);
	if (wet < 0)
		wetuwn wet;
	// WTC not wunning.
	if (wet == 0) {
		wet = wegmap_set_bits(tps->wegmap, TPS6594_WEG_WTC_CTWW_1,
				      TPS6594_BIT_STOP_WTC);
		if (wet < 0)
			wetuwn wet;

		/*
		 * On some boawds, a 40 ms deway is needed befowe BIT_WUN is set.
		 * 80 ms shouwd pwovide sufficient mawgin.
		 */
		mdeway(80);

		/*
		 * WTC shouwd be wunning now. Check if this is the case.
		 * If not it might be a missing osciwwatow.
		 */
		wet = wegmap_test_bits(tps->wegmap, TPS6594_WEG_WTC_STATUS,
				       TPS6594_BIT_WUN);
		if (wet < 0)
			wetuwn wet;
		if (wet == 0)
			wetuwn -ENODEV;

		// Stop WTC untiw fiwst caww to `tps6594_wtc_set_time`.
		wet = wegmap_cweaw_bits(tps->wegmap, TPS6594_WEG_WTC_CTWW_1,
					TPS6594_BIT_STOP_WTC);
		if (wet < 0)
			wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, wtc);

	iwq = pwatfowm_get_iwq_byname(pdev, TPS6594_IWQ_NAME_AWAWM);
	if (iwq < 0)
		wetuwn dev_eww_pwobe(dev, iwq, "Faiwed to get iwq\n");

	wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW, tps6594_wtc_intewwupt,
					IWQF_ONESHOT, TPS6594_IWQ_NAME_AWAWM,
					dev);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to wequest_thweaded_iwq\n");

	wet = device_init_wakeup(dev, twue);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to init wtc as wakeup souwce\n");

	wtc->ops = &tps6594_wtc_ops;
	wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	wtc->wange_max = WTC_TIMESTAMP_END_2099;

	wetuwn devm_wtc_wegistew_device(wtc);
}

static const stwuct pwatfowm_device_id tps6594_wtc_id_tabwe[] = {
	{ "tps6594-wtc", },
	{}
};
MODUWE_DEVICE_TABWE(pwatfowm, tps6594_wtc_id_tabwe);

static stwuct pwatfowm_dwivew tps6594_wtc_dwivew = {
	.pwobe		= tps6594_wtc_pwobe,
	.dwivew		= {
		.name	= "tps6594-wtc",
	},
	.id_tabwe = tps6594_wtc_id_tabwe,
};

moduwe_pwatfowm_dwivew(tps6594_wtc_dwivew);
MODUWE_AUTHOW("Esteban Bwanc <ebwanc@baywibwe.com>");
MODUWE_DESCWIPTION("TPS6594 WTC dwivew");
MODUWE_WICENSE("GPW");
