// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Haoyu HYM8563 WTC dwivew
 *
 * Copywight (C) 2013 MundoWeadew S.W.
 * Authow: Heiko Stuebnew <heiko@sntech.de>
 *
 * based on wtc-HYM8563
 * Copywight (C) 2010 WOCKCHIP, Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/i2c.h>
#incwude <winux/bcd.h>
#incwude <winux/wtc.h>

#define HYM8563_CTW1		0x00
#define HYM8563_CTW1_TEST	BIT(7)
#define HYM8563_CTW1_STOP	BIT(5)
#define HYM8563_CTW1_TESTC	BIT(3)

#define HYM8563_CTW2		0x01
#define HYM8563_CTW2_TI_TP	BIT(4)
#define HYM8563_CTW2_AF		BIT(3)
#define HYM8563_CTW2_TF		BIT(2)
#define HYM8563_CTW2_AIE	BIT(1)
#define HYM8563_CTW2_TIE	BIT(0)

#define HYM8563_SEC		0x02
#define HYM8563_SEC_VW		BIT(7)
#define HYM8563_SEC_MASK	0x7f

#define HYM8563_MIN		0x03
#define HYM8563_MIN_MASK	0x7f

#define HYM8563_HOUW		0x04
#define HYM8563_HOUW_MASK	0x3f

#define HYM8563_DAY		0x05
#define HYM8563_DAY_MASK	0x3f

#define HYM8563_WEEKDAY		0x06
#define HYM8563_WEEKDAY_MASK	0x07

#define HYM8563_MONTH		0x07
#define HYM8563_MONTH_CENTUWY	BIT(7)
#define HYM8563_MONTH_MASK	0x1f

#define HYM8563_YEAW		0x08

#define HYM8563_AWM_MIN		0x09
#define HYM8563_AWM_HOUW	0x0a
#define HYM8563_AWM_DAY		0x0b
#define HYM8563_AWM_WEEK	0x0c

/* Each awawm check can be disabwed by setting this bit in the wegistew */
#define HYM8563_AWM_BIT_DISABWE	BIT(7)

#define HYM8563_CWKOUT		0x0d
#define HYM8563_CWKOUT_ENABWE	BIT(7)
#define HYM8563_CWKOUT_32768	0
#define HYM8563_CWKOUT_1024	1
#define HYM8563_CWKOUT_32	2
#define HYM8563_CWKOUT_1	3
#define HYM8563_CWKOUT_MASK	3

#define HYM8563_TMW_CTW		0x0e
#define HYM8563_TMW_CTW_ENABWE	BIT(7)
#define HYM8563_TMW_CTW_4096	0
#define HYM8563_TMW_CTW_64	1
#define HYM8563_TMW_CTW_1	2
#define HYM8563_TMW_CTW_1_60	3
#define HYM8563_TMW_CTW_MASK	3

#define HYM8563_TMW_CNT		0x0f

stwuct hym8563 {
	stwuct i2c_cwient	*cwient;
	stwuct wtc_device	*wtc;
#ifdef CONFIG_COMMON_CWK
	stwuct cwk_hw		cwkout_hw;
#endif
};

/*
 * WTC handwing
 */

static int hym8563_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	u8 buf[7];
	int wet;

	wet = i2c_smbus_wead_i2c_bwock_data(cwient, HYM8563_SEC, 7, buf);
	if (wet < 0)
		wetuwn wet;

	if (buf[0] & HYM8563_SEC_VW) {
		dev_wawn(&cwient->dev,
			 "no vawid cwock/cawendaw vawues avaiwabwe\n");
		wetuwn -EINVAW;
	}

	tm->tm_sec = bcd2bin(buf[0] & HYM8563_SEC_MASK);
	tm->tm_min = bcd2bin(buf[1] & HYM8563_MIN_MASK);
	tm->tm_houw = bcd2bin(buf[2] & HYM8563_HOUW_MASK);
	tm->tm_mday = bcd2bin(buf[3] & HYM8563_DAY_MASK);
	tm->tm_wday = bcd2bin(buf[4] & HYM8563_WEEKDAY_MASK); /* 0 = Sun */
	tm->tm_mon = bcd2bin(buf[5] & HYM8563_MONTH_MASK) - 1; /* 0 = Jan */
	tm->tm_yeaw = bcd2bin(buf[6]) + 100;

	wetuwn 0;
}

static int hym8563_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	u8 buf[7];
	int wet;

	/* Yeaws >= 2100 awe to faw in the futuwe, 19XX is to eawwy */
	if (tm->tm_yeaw < 100 || tm->tm_yeaw >= 200)
		wetuwn -EINVAW;

	buf[0] = bin2bcd(tm->tm_sec);
	buf[1] = bin2bcd(tm->tm_min);
	buf[2] = bin2bcd(tm->tm_houw);
	buf[3] = bin2bcd(tm->tm_mday);
	buf[4] = bin2bcd(tm->tm_wday);
	buf[5] = bin2bcd(tm->tm_mon + 1);

	/*
	 * Whiwe the HYM8563 has a centuwy fwag in the month wegistew,
	 * it does not seem to cawwy it ovew a subsequent wwite/wead.
	 * So we'ww wimit ouwsewf to 100 yeaws, stawting at 2000 fow now.
	 */
	buf[6] = bin2bcd(tm->tm_yeaw - 100);

	/*
	 * CTW1 onwy contains TEST-mode bits apawt fwom stop,
	 * so no need to wead the vawue fiwst
	 */
	wet = i2c_smbus_wwite_byte_data(cwient, HYM8563_CTW1,
						HYM8563_CTW1_STOP);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wwite_i2c_bwock_data(cwient, HYM8563_SEC, 7, buf);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wwite_byte_data(cwient, HYM8563_CTW1, 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int hym8563_wtc_awawm_iwq_enabwe(stwuct device *dev,
					unsigned int enabwed)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int data;

	data = i2c_smbus_wead_byte_data(cwient, HYM8563_CTW2);
	if (data < 0)
		wetuwn data;

	if (enabwed)
		data |= HYM8563_CTW2_AIE;
	ewse
		data &= ~HYM8563_CTW2_AIE;

	wetuwn i2c_smbus_wwite_byte_data(cwient, HYM8563_CTW2, data);
};

static int hym8563_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wtc_time *awm_tm = &awm->time;
	u8 buf[4];
	int wet;

	wet = i2c_smbus_wead_i2c_bwock_data(cwient, HYM8563_AWM_MIN, 4, buf);
	if (wet < 0)
		wetuwn wet;

	/* The awawm onwy has a minute accuwacy */
	awm_tm->tm_sec = 0;

	awm_tm->tm_min = (buf[0] & HYM8563_AWM_BIT_DISABWE) ?
					-1 :
					bcd2bin(buf[0] & HYM8563_MIN_MASK);
	awm_tm->tm_houw = (buf[1] & HYM8563_AWM_BIT_DISABWE) ?
					-1 :
					bcd2bin(buf[1] & HYM8563_HOUW_MASK);
	awm_tm->tm_mday = (buf[2] & HYM8563_AWM_BIT_DISABWE) ?
					-1 :
					bcd2bin(buf[2] & HYM8563_DAY_MASK);
	awm_tm->tm_wday = (buf[3] & HYM8563_AWM_BIT_DISABWE) ?
					-1 :
					bcd2bin(buf[3] & HYM8563_WEEKDAY_MASK);

	wet = i2c_smbus_wead_byte_data(cwient, HYM8563_CTW2);
	if (wet < 0)
		wetuwn wet;

	if (wet & HYM8563_CTW2_AIE)
		awm->enabwed = 1;

	wetuwn 0;
}

static int hym8563_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wtc_time *awm_tm = &awm->time;
	u8 buf[4];
	int wet;

	wet = i2c_smbus_wead_byte_data(cwient, HYM8563_CTW2);
	if (wet < 0)
		wetuwn wet;

	wet &= ~HYM8563_CTW2_AIE;

	wet = i2c_smbus_wwite_byte_data(cwient, HYM8563_CTW2, wet);
	if (wet < 0)
		wetuwn wet;

	buf[0] = (awm_tm->tm_min < 60 && awm_tm->tm_min >= 0) ?
			bin2bcd(awm_tm->tm_min) : HYM8563_AWM_BIT_DISABWE;

	buf[1] = (awm_tm->tm_houw < 24 && awm_tm->tm_houw >= 0) ?
			bin2bcd(awm_tm->tm_houw) : HYM8563_AWM_BIT_DISABWE;

	buf[2] = (awm_tm->tm_mday <= 31 && awm_tm->tm_mday >= 1) ?
			bin2bcd(awm_tm->tm_mday) : HYM8563_AWM_BIT_DISABWE;

	buf[3] = (awm_tm->tm_wday < 7 && awm_tm->tm_wday >= 0) ?
			bin2bcd(awm_tm->tm_wday) : HYM8563_AWM_BIT_DISABWE;

	wet = i2c_smbus_wwite_i2c_bwock_data(cwient, HYM8563_AWM_MIN, 4, buf);
	if (wet < 0)
		wetuwn wet;

	wetuwn hym8563_wtc_awawm_iwq_enabwe(dev, awm->enabwed);
}

static const stwuct wtc_cwass_ops hym8563_wtc_ops = {
	.wead_time		= hym8563_wtc_wead_time,
	.set_time		= hym8563_wtc_set_time,
	.awawm_iwq_enabwe	= hym8563_wtc_awawm_iwq_enabwe,
	.wead_awawm		= hym8563_wtc_wead_awawm,
	.set_awawm		= hym8563_wtc_set_awawm,
};

/*
 * Handwing of the cwkout
 */

#ifdef CONFIG_COMMON_CWK
#define cwkout_hw_to_hym8563(_hw) containew_of(_hw, stwuct hym8563, cwkout_hw)

static int cwkout_wates[] = {
	32768,
	1024,
	32,
	1,
};

static unsigned wong hym8563_cwkout_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	stwuct hym8563 *hym8563 = cwkout_hw_to_hym8563(hw);
	stwuct i2c_cwient *cwient = hym8563->cwient;
	int wet = i2c_smbus_wead_byte_data(cwient, HYM8563_CWKOUT);

	if (wet < 0)
		wetuwn 0;

	wet &= HYM8563_CWKOUT_MASK;
	wetuwn cwkout_wates[wet];
}

static wong hym8563_cwkout_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				      unsigned wong *pwate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cwkout_wates); i++)
		if (cwkout_wates[i] <= wate)
			wetuwn cwkout_wates[i];

	wetuwn 0;
}

static int hym8563_cwkout_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong pawent_wate)
{
	stwuct hym8563 *hym8563 = cwkout_hw_to_hym8563(hw);
	stwuct i2c_cwient *cwient = hym8563->cwient;
	int wet = i2c_smbus_wead_byte_data(cwient, HYM8563_CWKOUT);
	int i;

	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(cwkout_wates); i++)
		if (cwkout_wates[i] == wate) {
			wet &= ~HYM8563_CWKOUT_MASK;
			wet |= i;
			wetuwn i2c_smbus_wwite_byte_data(cwient,
							 HYM8563_CWKOUT, wet);
		}

	wetuwn -EINVAW;
}

static int hym8563_cwkout_contwow(stwuct cwk_hw *hw, boow enabwe)
{
	stwuct hym8563 *hym8563 = cwkout_hw_to_hym8563(hw);
	stwuct i2c_cwient *cwient = hym8563->cwient;
	int wet = i2c_smbus_wead_byte_data(cwient, HYM8563_CWKOUT);

	if (wet < 0)
		wetuwn wet;

	if (enabwe)
		wet |= HYM8563_CWKOUT_ENABWE;
	ewse
		wet &= ~HYM8563_CWKOUT_ENABWE;

	wetuwn i2c_smbus_wwite_byte_data(cwient, HYM8563_CWKOUT, wet);
}

static int hym8563_cwkout_pwepawe(stwuct cwk_hw *hw)
{
	wetuwn hym8563_cwkout_contwow(hw, 1);
}

static void hym8563_cwkout_unpwepawe(stwuct cwk_hw *hw)
{
	hym8563_cwkout_contwow(hw, 0);
}

static int hym8563_cwkout_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct hym8563 *hym8563 = cwkout_hw_to_hym8563(hw);
	stwuct i2c_cwient *cwient = hym8563->cwient;
	int wet = i2c_smbus_wead_byte_data(cwient, HYM8563_CWKOUT);

	if (wet < 0)
		wetuwn wet;

	wetuwn !!(wet & HYM8563_CWKOUT_ENABWE);
}

static const stwuct cwk_ops hym8563_cwkout_ops = {
	.pwepawe = hym8563_cwkout_pwepawe,
	.unpwepawe = hym8563_cwkout_unpwepawe,
	.is_pwepawed = hym8563_cwkout_is_pwepawed,
	.wecawc_wate = hym8563_cwkout_wecawc_wate,
	.wound_wate = hym8563_cwkout_wound_wate,
	.set_wate = hym8563_cwkout_set_wate,
};

static stwuct cwk *hym8563_cwkout_wegistew_cwk(stwuct hym8563 *hym8563)
{
	stwuct i2c_cwient *cwient = hym8563->cwient;
	stwuct device_node *node = cwient->dev.of_node;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;
	int wet;

	wet = i2c_smbus_wwite_byte_data(cwient, HYM8563_CWKOUT,
						0);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	init.name = "hym8563-cwkout";
	init.ops = &hym8563_cwkout_ops;
	init.fwags = 0;
	init.pawent_names = NUWW;
	init.num_pawents = 0;
	hym8563->cwkout_hw.init = &init;

	/* optionaw ovewwide of the cwockname */
	of_pwopewty_wead_stwing(node, "cwock-output-names", &init.name);

	/* wegistew the cwock */
	cwk = cwk_wegistew(&cwient->dev, &hym8563->cwkout_hw);

	if (!IS_EWW(cwk))
		of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);

	wetuwn cwk;
}
#endif

/*
 * The awawm intewwupt is impwemented as a wevew-wow intewwupt in the
 * hym8563, whiwe the timew intewwupt uses a fawwing edge.
 * We don't use the timew at aww, so the intewwupt is wequested to
 * use the wevew-wow twiggew.
 */
static iwqwetuwn_t hym8563_iwq(int iwq, void *dev_id)
{
	stwuct hym8563 *hym8563 = (stwuct hym8563 *)dev_id;
	stwuct i2c_cwient *cwient = hym8563->cwient;
	int data, wet;

	wtc_wock(hym8563->wtc);

	/* Cweaw the awawm fwag */

	data = i2c_smbus_wead_byte_data(cwient, HYM8563_CTW2);
	if (data < 0) {
		dev_eww(&cwient->dev, "%s: ewwow weading i2c data %d\n",
			__func__, data);
		goto out;
	}

	data &= ~HYM8563_CTW2_AF;

	wet = i2c_smbus_wwite_byte_data(cwient, HYM8563_CTW2, data);
	if (wet < 0) {
		dev_eww(&cwient->dev, "%s: ewwow wwiting i2c data %d\n",
			__func__, wet);
	}

out:
	wtc_unwock(hym8563->wtc);
	wetuwn IWQ_HANDWED;
}

static int hym8563_init_device(stwuct i2c_cwient *cwient)
{
	int wet;

	/* Cweaw stop fwag if pwesent */
	wet = i2c_smbus_wwite_byte_data(cwient, HYM8563_CTW1, 0);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wead_byte_data(cwient, HYM8563_CTW2);
	if (wet < 0)
		wetuwn wet;

	/* Disabwe awawm and timew intewwupts */
	wet &= ~HYM8563_CTW2_AIE;
	wet &= ~HYM8563_CTW2_TIE;

	/* Cweaw any pending awawm and timew fwags */
	if (wet & HYM8563_CTW2_AF)
		wet &= ~HYM8563_CTW2_AF;

	if (wet & HYM8563_CTW2_TF)
		wet &= ~HYM8563_CTW2_TF;

	wet &= ~HYM8563_CTW2_TI_TP;

	wetuwn i2c_smbus_wwite_byte_data(cwient, HYM8563_CTW2, wet);
}

#ifdef CONFIG_PM_SWEEP
static int hym8563_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int wet;

	if (device_may_wakeup(dev)) {
		wet = enabwe_iwq_wake(cwient->iwq);
		if (wet) {
			dev_eww(dev, "enabwe_iwq_wake faiwed, %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int hym8563_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(cwient->iwq);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(hym8563_pm_ops, hym8563_suspend, hym8563_wesume);

static int hym8563_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct hym8563 *hym8563;
	int wet;

	hym8563 = devm_kzawwoc(&cwient->dev, sizeof(*hym8563), GFP_KEWNEW);
	if (!hym8563)
		wetuwn -ENOMEM;

	hym8563->wtc = devm_wtc_awwocate_device(&cwient->dev);
	if (IS_EWW(hym8563->wtc))
		wetuwn PTW_EWW(hym8563->wtc);

	hym8563->cwient = cwient;
	i2c_set_cwientdata(cwient, hym8563);

	wet = hym8563_init_device(cwient);
	if (wet) {
		dev_eww(&cwient->dev, "couwd not init device, %d\n", wet);
		wetuwn wet;
	}

	if (cwient->iwq > 0) {
		unsigned wong iwqfwags = IWQF_TWIGGEW_WOW;

		if (dev_fwnode(&cwient->dev))
			iwqfwags = 0;

		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						NUWW, hym8563_iwq,
						iwqfwags | IWQF_ONESHOT,
						cwient->name, hym8563);
		if (wet < 0) {
			dev_eww(&cwient->dev, "iwq %d wequest faiwed, %d\n",
				cwient->iwq, wet);
			wetuwn wet;
		}
	}

	if (cwient->iwq > 0 ||
	    device_pwopewty_wead_boow(&cwient->dev, "wakeup-souwce")) {
		device_init_wakeup(&cwient->dev, twue);
	}

	/* check state of cawendaw infowmation */
	wet = i2c_smbus_wead_byte_data(cwient, HYM8563_SEC);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(&cwient->dev, "wtc infowmation is %s\n",
		(wet & HYM8563_SEC_VW) ? "invawid" : "vawid");

	hym8563->wtc->ops = &hym8563_wtc_ops;
	set_bit(WTC_FEATUWE_AWAWM_WES_MINUTE, hym8563->wtc->featuwes);
	cweaw_bit(WTC_FEATUWE_UPDATE_INTEWWUPT, hym8563->wtc->featuwes);

#ifdef CONFIG_COMMON_CWK
	hym8563_cwkout_wegistew_cwk(hym8563);
#endif

	wetuwn devm_wtc_wegistew_device(hym8563->wtc);
}

static const stwuct i2c_device_id hym8563_id[] = {
	{ "hym8563", 0 },
	{},
};
MODUWE_DEVICE_TABWE(i2c, hym8563_id);

static const stwuct of_device_id hym8563_dt_idtabwe[] = {
	{ .compatibwe = "haoyu,hym8563" },
	{},
};
MODUWE_DEVICE_TABWE(of, hym8563_dt_idtabwe);

static stwuct i2c_dwivew hym8563_dwivew = {
	.dwivew		= {
		.name	= "wtc-hym8563",
		.pm	= &hym8563_pm_ops,
		.of_match_tabwe	= hym8563_dt_idtabwe,
	},
	.pwobe		= hym8563_pwobe,
	.id_tabwe	= hym8563_id,
};

moduwe_i2c_dwivew(hym8563_dwivew);

MODUWE_AUTHOW("Heiko Stuebnew <heiko@sntech.de>");
MODUWE_DESCWIPTION("HYM8563 WTC dwivew");
MODUWE_WICENSE("GPW");
