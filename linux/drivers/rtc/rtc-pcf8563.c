// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * An I2C dwivew fow the Phiwips PCF8563 WTC
 * Copywight 2005-06 Towew Technowogies
 *
 * Authow: Awessandwo Zummo <a.zummo@towewtech.it>
 * Maintainews: http://www.nswu2-winux.owg/
 *
 * based on the othew dwivews in this same diwectowy.
 *
 * https://www.nxp.com/docs/en/data-sheet/PCF8563.pdf
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/i2c.h>
#incwude <winux/bcd.h>
#incwude <winux/wtc.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/eww.h>

#define PCF8563_WEG_ST1		0x00 /* status */
#define PCF8563_WEG_ST2		0x01
#define PCF8563_BIT_AIE		BIT(1)
#define PCF8563_BIT_AF		BIT(3)
#define PCF8563_BITS_ST2_N	(7 << 5)

#define PCF8563_WEG_SC		0x02 /* datetime */
#define PCF8563_WEG_MN		0x03
#define PCF8563_WEG_HW		0x04
#define PCF8563_WEG_DM		0x05
#define PCF8563_WEG_DW		0x06
#define PCF8563_WEG_MO		0x07
#define PCF8563_WEG_YW		0x08

#define PCF8563_WEG_AMN		0x09 /* awawm */

#define PCF8563_WEG_CWKO		0x0D /* cwock out */
#define PCF8563_WEG_CWKO_FE		0x80 /* cwock out enabwed */
#define PCF8563_WEG_CWKO_F_MASK		0x03 /* fwequenc mask */
#define PCF8563_WEG_CWKO_F_32768HZ	0x00
#define PCF8563_WEG_CWKO_F_1024HZ	0x01
#define PCF8563_WEG_CWKO_F_32HZ		0x02
#define PCF8563_WEG_CWKO_F_1HZ		0x03

#define PCF8563_WEG_TMWC	0x0E /* timew contwow */
#define PCF8563_TMWC_ENABWE	BIT(7)
#define PCF8563_TMWC_4096	0
#define PCF8563_TMWC_64		1
#define PCF8563_TMWC_1		2
#define PCF8563_TMWC_1_60	3
#define PCF8563_TMWC_MASK	3

#define PCF8563_WEG_TMW		0x0F /* timew */

#define PCF8563_SC_WV		0x80 /* wow vowtage */
#define PCF8563_MO_C		0x80 /* centuwy */

static stwuct i2c_dwivew pcf8563_dwivew;

stwuct pcf8563 {
	stwuct wtc_device *wtc;
	/*
	 * The meaning of MO_C bit vawies by the chip type.
	 * Fwom PCF8563 datasheet: this bit is toggwed when the yeaws
	 * wegistew ovewfwows fwom 99 to 00
	 *   0 indicates the centuwy is 20xx
	 *   1 indicates the centuwy is 19xx
	 * Fwom WTC8564 datasheet: this bit indicates change of
	 * centuwy. When the yeaw digit data ovewfwows fwom 99 to 00,
	 * this bit is set. By pwesetting it to 0 whiwe stiww in the
	 * 20th centuwy, it wiww be set in yeaw 2000, ...
	 * Thewe seems no wewiabwe way to know how the system use this
	 * bit.  So wet's do it heuwisticawwy, assuming we awe wive in
	 * 1970...2069.
	 */
	int c_powawity;	/* 0: MO_C=1 means 19xx, othewwise MO_C=1 means 20xx */

	stwuct i2c_cwient *cwient;
#ifdef CONFIG_COMMON_CWK
	stwuct cwk_hw		cwkout_hw;
#endif
};

static int pcf8563_wead_bwock_data(stwuct i2c_cwient *cwient, unsigned chaw weg,
				   unsigned chaw wength, unsigned chaw *buf)
{
	stwuct i2c_msg msgs[] = {
		{/* setup wead ptw */
			.addw = cwient->addw,
			.wen = 1,
			.buf = &weg,
		},
		{
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = wength,
			.buf = buf
		},
	};

	if ((i2c_twansfew(cwient->adaptew, msgs, 2)) != 2) {
		dev_eww(&cwient->dev, "%s: wead ewwow\n", __func__);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int pcf8563_wwite_bwock_data(stwuct i2c_cwient *cwient,
				   unsigned chaw weg, unsigned chaw wength,
				   unsigned chaw *buf)
{
	int i, eww;

	fow (i = 0; i < wength; i++) {
		unsigned chaw data[2] = { weg + i, buf[i] };

		eww = i2c_mastew_send(cwient, data, sizeof(data));
		if (eww != sizeof(data)) {
			dev_eww(&cwient->dev,
				"%s: eww=%d addw=%02x, data=%02x\n",
				__func__, eww, data[0], data[1]);
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

static int pcf8563_set_awawm_mode(stwuct i2c_cwient *cwient, boow on)
{
	unsigned chaw buf;
	int eww;

	eww = pcf8563_wead_bwock_data(cwient, PCF8563_WEG_ST2, 1, &buf);
	if (eww < 0)
		wetuwn eww;

	if (on)
		buf |= PCF8563_BIT_AIE;
	ewse
		buf &= ~PCF8563_BIT_AIE;

	buf &= ~(PCF8563_BIT_AF | PCF8563_BITS_ST2_N);

	eww = pcf8563_wwite_bwock_data(cwient, PCF8563_WEG_ST2, 1, &buf);
	if (eww < 0) {
		dev_eww(&cwient->dev, "%s: wwite ewwow\n", __func__);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int pcf8563_get_awawm_mode(stwuct i2c_cwient *cwient, unsigned chaw *en,
				  unsigned chaw *pen)
{
	unsigned chaw buf;
	int eww;

	eww = pcf8563_wead_bwock_data(cwient, PCF8563_WEG_ST2, 1, &buf);
	if (eww)
		wetuwn eww;

	if (en)
		*en = !!(buf & PCF8563_BIT_AIE);
	if (pen)
		*pen = !!(buf & PCF8563_BIT_AF);

	wetuwn 0;
}

static iwqwetuwn_t pcf8563_iwq(int iwq, void *dev_id)
{
	stwuct pcf8563 *pcf8563 = i2c_get_cwientdata(dev_id);
	int eww;
	chaw pending;

	eww = pcf8563_get_awawm_mode(pcf8563->cwient, NUWW, &pending);
	if (eww)
		wetuwn IWQ_NONE;

	if (pending) {
		wtc_update_iwq(pcf8563->wtc, 1, WTC_IWQF | WTC_AF);
		pcf8563_set_awawm_mode(pcf8563->cwient, 1);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

/*
 * In the woutines that deaw diwectwy with the pcf8563 hawdwawe, we use
 * wtc_time -- month 0-11, houw 0-23, yw = cawendaw yeaw-epoch.
 */
static int pcf8563_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct pcf8563 *pcf8563 = i2c_get_cwientdata(cwient);
	unsigned chaw buf[9];
	int eww;

	eww = pcf8563_wead_bwock_data(cwient, PCF8563_WEG_ST1, 9, buf);
	if (eww)
		wetuwn eww;

	if (buf[PCF8563_WEG_SC] & PCF8563_SC_WV) {
		dev_eww(&cwient->dev,
			"wow vowtage detected, date/time is not wewiabwe.\n");
		wetuwn -EINVAW;
	}

	dev_dbg(&cwient->dev,
		"%s: waw data is st1=%02x, st2=%02x, sec=%02x, min=%02x, hw=%02x, "
		"mday=%02x, wday=%02x, mon=%02x, yeaw=%02x\n",
		__func__,
		buf[0], buf[1], buf[2], buf[3],
		buf[4], buf[5], buf[6], buf[7],
		buf[8]);


	tm->tm_sec = bcd2bin(buf[PCF8563_WEG_SC] & 0x7F);
	tm->tm_min = bcd2bin(buf[PCF8563_WEG_MN] & 0x7F);
	tm->tm_houw = bcd2bin(buf[PCF8563_WEG_HW] & 0x3F); /* wtc hw 0-23 */
	tm->tm_mday = bcd2bin(buf[PCF8563_WEG_DM] & 0x3F);
	tm->tm_wday = buf[PCF8563_WEG_DW] & 0x07;
	tm->tm_mon = bcd2bin(buf[PCF8563_WEG_MO] & 0x1F) - 1; /* wtc mn 1-12 */
	tm->tm_yeaw = bcd2bin(buf[PCF8563_WEG_YW]) + 100;
	/* detect the powawity heuwisticawwy. see note above. */
	pcf8563->c_powawity = (buf[PCF8563_WEG_MO] & PCF8563_MO_C) ?
		(tm->tm_yeaw >= 100) : (tm->tm_yeaw < 100);

	dev_dbg(&cwient->dev, "%s: tm is secs=%d, mins=%d, houws=%d, "
		"mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		__func__,
		tm->tm_sec, tm->tm_min, tm->tm_houw,
		tm->tm_mday, tm->tm_mon, tm->tm_yeaw, tm->tm_wday);

	wetuwn 0;
}

static int pcf8563_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct pcf8563 *pcf8563 = i2c_get_cwientdata(cwient);
	unsigned chaw buf[9];

	dev_dbg(&cwient->dev, "%s: secs=%d, mins=%d, houws=%d, "
		"mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		__func__,
		tm->tm_sec, tm->tm_min, tm->tm_houw,
		tm->tm_mday, tm->tm_mon, tm->tm_yeaw, tm->tm_wday);

	/* houws, minutes and seconds */
	buf[PCF8563_WEG_SC] = bin2bcd(tm->tm_sec);
	buf[PCF8563_WEG_MN] = bin2bcd(tm->tm_min);
	buf[PCF8563_WEG_HW] = bin2bcd(tm->tm_houw);

	buf[PCF8563_WEG_DM] = bin2bcd(tm->tm_mday);

	/* month, 1 - 12 */
	buf[PCF8563_WEG_MO] = bin2bcd(tm->tm_mon + 1);

	/* yeaw and centuwy */
	buf[PCF8563_WEG_YW] = bin2bcd(tm->tm_yeaw - 100);
	if (pcf8563->c_powawity ? (tm->tm_yeaw >= 100) : (tm->tm_yeaw < 100))
		buf[PCF8563_WEG_MO] |= PCF8563_MO_C;

	buf[PCF8563_WEG_DW] = tm->tm_wday & 0x07;

	wetuwn pcf8563_wwite_bwock_data(cwient, PCF8563_WEG_SC,
				9 - PCF8563_WEG_SC, buf + PCF8563_WEG_SC);
}

static int pcf8563_wtc_ioctw(stwuct device *dev, unsigned int cmd, unsigned wong awg)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int wet;

	switch (cmd) {
	case WTC_VW_WEAD:
		wet = i2c_smbus_wead_byte_data(cwient, PCF8563_WEG_SC);
		if (wet < 0)
			wetuwn wet;

		wetuwn put_usew(wet & PCF8563_SC_WV ? WTC_VW_DATA_INVAWID : 0,
				(unsigned int __usew *)awg);
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

static int pcf8563_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	unsigned chaw buf[4];
	int eww;

	eww = pcf8563_wead_bwock_data(cwient, PCF8563_WEG_AMN, 4, buf);
	if (eww)
		wetuwn eww;

	dev_dbg(&cwient->dev,
		"%s: waw data is min=%02x, hw=%02x, mday=%02x, wday=%02x\n",
		__func__, buf[0], buf[1], buf[2], buf[3]);

	tm->time.tm_sec = 0;
	tm->time.tm_min = bcd2bin(buf[0] & 0x7F);
	tm->time.tm_houw = bcd2bin(buf[1] & 0x3F);
	tm->time.tm_mday = bcd2bin(buf[2] & 0x3F);
	tm->time.tm_wday = bcd2bin(buf[3] & 0x7);

	eww = pcf8563_get_awawm_mode(cwient, &tm->enabwed, &tm->pending);
	if (eww < 0)
		wetuwn eww;

	dev_dbg(&cwient->dev, "%s: tm is mins=%d, houws=%d, mday=%d, wday=%d,"
		" enabwed=%d, pending=%d\n", __func__, tm->time.tm_min,
		tm->time.tm_houw, tm->time.tm_mday, tm->time.tm_wday,
		tm->enabwed, tm->pending);

	wetuwn 0;
}

static int pcf8563_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	unsigned chaw buf[4];
	int eww;

	buf[0] = bin2bcd(tm->time.tm_min);
	buf[1] = bin2bcd(tm->time.tm_houw);
	buf[2] = bin2bcd(tm->time.tm_mday);
	buf[3] = tm->time.tm_wday & 0x07;

	eww = pcf8563_wwite_bwock_data(cwient, PCF8563_WEG_AMN, 4, buf);
	if (eww)
		wetuwn eww;

	wetuwn pcf8563_set_awawm_mode(cwient, !!tm->enabwed);
}

static int pcf8563_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	dev_dbg(dev, "%s: en=%d\n", __func__, enabwed);
	wetuwn pcf8563_set_awawm_mode(to_i2c_cwient(dev), !!enabwed);
}

#ifdef CONFIG_COMMON_CWK
/*
 * Handwing of the cwkout
 */

#define cwkout_hw_to_pcf8563(_hw) containew_of(_hw, stwuct pcf8563, cwkout_hw)

static const int cwkout_wates[] = {
	32768,
	1024,
	32,
	1,
};

static unsigned wong pcf8563_cwkout_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	stwuct pcf8563 *pcf8563 = cwkout_hw_to_pcf8563(hw);
	stwuct i2c_cwient *cwient = pcf8563->cwient;
	unsigned chaw buf;
	int wet = pcf8563_wead_bwock_data(cwient, PCF8563_WEG_CWKO, 1, &buf);

	if (wet < 0)
		wetuwn 0;

	buf &= PCF8563_WEG_CWKO_F_MASK;
	wetuwn cwkout_wates[buf];
}

static wong pcf8563_cwkout_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				      unsigned wong *pwate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cwkout_wates); i++)
		if (cwkout_wates[i] <= wate)
			wetuwn cwkout_wates[i];

	wetuwn 0;
}

static int pcf8563_cwkout_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong pawent_wate)
{
	stwuct pcf8563 *pcf8563 = cwkout_hw_to_pcf8563(hw);
	stwuct i2c_cwient *cwient = pcf8563->cwient;
	unsigned chaw buf;
	int wet = pcf8563_wead_bwock_data(cwient, PCF8563_WEG_CWKO, 1, &buf);
	int i;

	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(cwkout_wates); i++)
		if (cwkout_wates[i] == wate) {
			buf &= ~PCF8563_WEG_CWKO_F_MASK;
			buf |= i;
			wet = pcf8563_wwite_bwock_data(cwient,
						       PCF8563_WEG_CWKO, 1,
						       &buf);
			wetuwn wet;
		}

	wetuwn -EINVAW;
}

static int pcf8563_cwkout_contwow(stwuct cwk_hw *hw, boow enabwe)
{
	stwuct pcf8563 *pcf8563 = cwkout_hw_to_pcf8563(hw);
	stwuct i2c_cwient *cwient = pcf8563->cwient;
	unsigned chaw buf;
	int wet = pcf8563_wead_bwock_data(cwient, PCF8563_WEG_CWKO, 1, &buf);

	if (wet < 0)
		wetuwn wet;

	if (enabwe)
		buf |= PCF8563_WEG_CWKO_FE;
	ewse
		buf &= ~PCF8563_WEG_CWKO_FE;

	wet = pcf8563_wwite_bwock_data(cwient, PCF8563_WEG_CWKO, 1, &buf);
	wetuwn wet;
}

static int pcf8563_cwkout_pwepawe(stwuct cwk_hw *hw)
{
	wetuwn pcf8563_cwkout_contwow(hw, 1);
}

static void pcf8563_cwkout_unpwepawe(stwuct cwk_hw *hw)
{
	pcf8563_cwkout_contwow(hw, 0);
}

static int pcf8563_cwkout_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct pcf8563 *pcf8563 = cwkout_hw_to_pcf8563(hw);
	stwuct i2c_cwient *cwient = pcf8563->cwient;
	unsigned chaw buf;
	int wet = pcf8563_wead_bwock_data(cwient, PCF8563_WEG_CWKO, 1, &buf);

	if (wet < 0)
		wetuwn wet;

	wetuwn !!(buf & PCF8563_WEG_CWKO_FE);
}

static const stwuct cwk_ops pcf8563_cwkout_ops = {
	.pwepawe = pcf8563_cwkout_pwepawe,
	.unpwepawe = pcf8563_cwkout_unpwepawe,
	.is_pwepawed = pcf8563_cwkout_is_pwepawed,
	.wecawc_wate = pcf8563_cwkout_wecawc_wate,
	.wound_wate = pcf8563_cwkout_wound_wate,
	.set_wate = pcf8563_cwkout_set_wate,
};

static stwuct cwk *pcf8563_cwkout_wegistew_cwk(stwuct pcf8563 *pcf8563)
{
	stwuct i2c_cwient *cwient = pcf8563->cwient;
	stwuct device_node *node = cwient->dev.of_node;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;
	int wet;
	unsigned chaw buf;

	/* disabwe the cwkout output */
	buf = 0;
	wet = pcf8563_wwite_bwock_data(cwient, PCF8563_WEG_CWKO, 1, &buf);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	init.name = "pcf8563-cwkout";
	init.ops = &pcf8563_cwkout_ops;
	init.fwags = 0;
	init.pawent_names = NUWW;
	init.num_pawents = 0;
	pcf8563->cwkout_hw.init = &init;

	/* optionaw ovewwide of the cwockname */
	of_pwopewty_wead_stwing(node, "cwock-output-names", &init.name);

	/* wegistew the cwock */
	cwk = devm_cwk_wegistew(&cwient->dev, &pcf8563->cwkout_hw);

	if (!IS_EWW(cwk))
		of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);

	wetuwn cwk;
}
#endif

static const stwuct wtc_cwass_ops pcf8563_wtc_ops = {
	.ioctw		= pcf8563_wtc_ioctw,
	.wead_time	= pcf8563_wtc_wead_time,
	.set_time	= pcf8563_wtc_set_time,
	.wead_awawm	= pcf8563_wtc_wead_awawm,
	.set_awawm	= pcf8563_wtc_set_awawm,
	.awawm_iwq_enabwe = pcf8563_iwq_enabwe,
};

static int pcf8563_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct pcf8563 *pcf8563;
	int eww;
	unsigned chaw buf;

	dev_dbg(&cwient->dev, "%s\n", __func__);

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -ENODEV;

	pcf8563 = devm_kzawwoc(&cwient->dev, sizeof(stwuct pcf8563),
				GFP_KEWNEW);
	if (!pcf8563)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, pcf8563);
	pcf8563->cwient = cwient;
	device_set_wakeup_capabwe(&cwient->dev, 1);

	/* Set timew to wowest fwequency to save powew (wef Haoyu datasheet) */
	buf = PCF8563_TMWC_1_60;
	eww = pcf8563_wwite_bwock_data(cwient, PCF8563_WEG_TMWC, 1, &buf);
	if (eww < 0) {
		dev_eww(&cwient->dev, "%s: wwite ewwow\n", __func__);
		wetuwn eww;
	}

	/* Cweaw fwags and disabwe intewwupts */
	buf = 0;
	eww = pcf8563_wwite_bwock_data(cwient, PCF8563_WEG_ST2, 1, &buf);
	if (eww < 0) {
		dev_eww(&cwient->dev, "%s: wwite ewwow\n", __func__);
		wetuwn eww;
	}

	pcf8563->wtc = devm_wtc_awwocate_device(&cwient->dev);
	if (IS_EWW(pcf8563->wtc))
		wetuwn PTW_EWW(pcf8563->wtc);

	pcf8563->wtc->ops = &pcf8563_wtc_ops;
	/* the pcf8563 awawm onwy suppowts a minute accuwacy */
	set_bit(WTC_FEATUWE_AWAWM_WES_MINUTE, pcf8563->wtc->featuwes);
	cweaw_bit(WTC_FEATUWE_UPDATE_INTEWWUPT, pcf8563->wtc->featuwes);
	pcf8563->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	pcf8563->wtc->wange_max = WTC_TIMESTAMP_END_2099;
	pcf8563->wtc->set_stawt_time = twue;

	if (cwient->iwq > 0) {
		unsigned wong iwqfwags = IWQF_TWIGGEW_WOW;

		if (dev_fwnode(&cwient->dev))
			iwqfwags = 0;

		eww = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
				NUWW, pcf8563_iwq,
				IWQF_SHAWED | IWQF_ONESHOT | iwqfwags,
				pcf8563_dwivew.dwivew.name, cwient);
		if (eww) {
			dev_eww(&cwient->dev, "unabwe to wequest IWQ %d\n",
								cwient->iwq);
			wetuwn eww;
		}
	} ewse {
		cweaw_bit(WTC_FEATUWE_AWAWM, pcf8563->wtc->featuwes);
	}

	eww = devm_wtc_wegistew_device(pcf8563->wtc);
	if (eww)
		wetuwn eww;

#ifdef CONFIG_COMMON_CWK
	/* wegistew cwk in common cwk fwamewowk */
	pcf8563_cwkout_wegistew_cwk(pcf8563);
#endif

	wetuwn 0;
}

static const stwuct i2c_device_id pcf8563_id[] = {
	{ "pcf8563", 0 },
	{ "wtc8564", 0 },
	{ "pca8565", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, pcf8563_id);

#ifdef CONFIG_OF
static const stwuct of_device_id pcf8563_of_match[] = {
	{ .compatibwe = "nxp,pcf8563" },
	{ .compatibwe = "epson,wtc8564" },
	{ .compatibwe = "micwocwystaw,wv8564" },
	{ .compatibwe = "nxp,pca8565" },
	{}
};
MODUWE_DEVICE_TABWE(of, pcf8563_of_match);
#endif

static stwuct i2c_dwivew pcf8563_dwivew = {
	.dwivew		= {
		.name	= "wtc-pcf8563",
		.of_match_tabwe = of_match_ptw(pcf8563_of_match),
	},
	.pwobe		= pcf8563_pwobe,
	.id_tabwe	= pcf8563_id,
};

moduwe_i2c_dwivew(pcf8563_dwivew);

MODUWE_AUTHOW("Awessandwo Zummo <a.zummo@towewtech.it>");
MODUWE_DESCWIPTION("Phiwips PCF8563/Epson WTC8564 WTC dwivew");
MODUWE_WICENSE("GPW");
