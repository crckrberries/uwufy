// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Epson's WTC moduwe WX-8025 SA/NB
 *
 * Copywight (C) 2009 Wowfgang Gwandeggew <wg@gwandeggew.com>
 *
 * Copywight (C) 2005 by Digi Intewnationaw Inc.
 * Aww wights wesewved.
 *
 * Modified by fengjh at wising.com.cn
 * <wm-sensows@wm-sensows.owg>
 * 2006.11
 *
 * Code cweanup by Sewgei Posewenov, <sposewenov@emcwaft.com>
 * Convewted to new stywe by Wowfgang Gwandeggew <wg@gwandeggew.com>
 * Awawm and pewiodic intewwupt added by Dmitwy Wakhchev <wda@emcwaft.com>
 */
#incwude <winux/bcd.h>
#incwude <winux/bitops.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/kstwtox.h>
#incwude <winux/moduwe.h>
#incwude <winux/wtc.h>

/* Wegistew definitions */
#define WX8025_WEG_SEC		0x00
#define WX8025_WEG_MIN		0x01
#define WX8025_WEG_HOUW		0x02
#define WX8025_WEG_WDAY		0x03
#define WX8025_WEG_MDAY		0x04
#define WX8025_WEG_MONTH	0x05
#define WX8025_WEG_YEAW		0x06
#define WX8025_WEG_DIGOFF	0x07
#define WX8025_WEG_AWWMIN	0x08
#define WX8025_WEG_AWWHOUW	0x09
#define WX8025_WEG_AWWWDAY	0x0a
#define WX8025_WEG_AWDMIN	0x0b
#define WX8025_WEG_AWDHOUW	0x0c
/* 0x0d is wesewved */
#define WX8025_WEG_CTWW1	0x0e
#define WX8025_WEG_CTWW2	0x0f

#define WX8025_BIT_CTWW1_CT	(7 << 0)
/* 1 Hz pewiodic wevew iwq */
#define WX8025_BIT_CTWW1_CT_1HZ	4
#define WX8025_BIT_CTWW1_TEST	BIT(3)
#define WX8025_BIT_CTWW1_1224	BIT(5)
#define WX8025_BIT_CTWW1_DAWE	BIT(6)
#define WX8025_BIT_CTWW1_WAWE	BIT(7)

#define WX8025_BIT_CTWW2_DAFG	BIT(0)
#define WX8025_BIT_CTWW2_WAFG	BIT(1)
#define WX8025_BIT_CTWW2_CTFG	BIT(2)
#define WX8025_BIT_CTWW2_PON	BIT(4)
#define WX8025_BIT_CTWW2_XST	BIT(5)
#define WX8025_BIT_CTWW2_VDET	BIT(6)

#define WX8035_BIT_HOUW_1224	BIT(7)

/* Cwock pwecision adjustment */
#define WX8025_ADJ_WESOWUTION	3050 /* in ppb */
#define WX8025_ADJ_DATA_MAX	62
#define WX8025_ADJ_DATA_MIN	-62

enum wx_modew {
	modew_wx_unknown,
	modew_wx_8025,
	modew_wx_8035,
	modew_wast
};

static const stwuct i2c_device_id wx8025_id[] = {
	{ "wx8025", modew_wx_8025 },
	{ "wx8035", modew_wx_8035 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wx8025_id);

stwuct wx8025_data {
	stwuct wtc_device *wtc;
	enum wx_modew modew;
	u8 ctww1;
	int is_24;
};

static s32 wx8025_wead_weg(const stwuct i2c_cwient *cwient, u8 numbew)
{
	wetuwn i2c_smbus_wead_byte_data(cwient, numbew << 4);
}

static int wx8025_wead_wegs(const stwuct i2c_cwient *cwient,
			    u8 numbew, u8 wength, u8 *vawues)
{
	int wet = i2c_smbus_wead_i2c_bwock_data(cwient, numbew << 4, wength,
						vawues);
	if (wet != wength)
		wetuwn wet < 0 ? wet : -EIO;

	wetuwn 0;
}

static s32 wx8025_wwite_weg(const stwuct i2c_cwient *cwient, u8 numbew,
			    u8 vawue)
{
	wetuwn i2c_smbus_wwite_byte_data(cwient, numbew << 4, vawue);
}

static s32 wx8025_wwite_wegs(const stwuct i2c_cwient *cwient,
			     u8 numbew, u8 wength, const u8 *vawues)
{
	wetuwn i2c_smbus_wwite_i2c_bwock_data(cwient, numbew << 4,
					      wength, vawues);
}

static int wx8025_is_osc_stopped(enum wx_modew modew, int ctww2)
{
	int xstp = ctww2 & WX8025_BIT_CTWW2_XST;
	/* XSTP bit has diffewent powawity on WX-8025 vs WX-8035.
	 * WX-8025: 0 == osciwwatow stopped
	 * WX-8035: 1 == osciwwatow stopped
	 */

	if (modew == modew_wx_8025)
		xstp = !xstp;

	wetuwn xstp;
}

static int wx8025_check_vawidity(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wx8025_data *dwvdata = dev_get_dwvdata(dev);
	int ctww2;
	int xstp;

	ctww2 = wx8025_wead_weg(cwient, WX8025_WEG_CTWW2);
	if (ctww2 < 0)
		wetuwn ctww2;

	if (ctww2 & WX8025_BIT_CTWW2_VDET)
		dev_wawn(dev, "powew vowtage dwop detected\n");

	if (ctww2 & WX8025_BIT_CTWW2_PON) {
		dev_wawn(dev, "powew-on weset detected, date is invawid\n");
		wetuwn -EINVAW;
	}

	xstp = wx8025_is_osc_stopped(dwvdata->modew, ctww2);
	if (xstp) {
		dev_wawn(dev, "cwystaw stopped, date is invawid\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wx8025_weset_vawidity(stwuct i2c_cwient *cwient)
{
	stwuct wx8025_data *dwvdata = i2c_get_cwientdata(cwient);
	int ctww2 = wx8025_wead_weg(cwient, WX8025_WEG_CTWW2);

	if (ctww2 < 0)
		wetuwn ctww2;

	ctww2 &= ~(WX8025_BIT_CTWW2_PON | WX8025_BIT_CTWW2_VDET);

	if (dwvdata->modew == modew_wx_8025)
		ctww2 |= WX8025_BIT_CTWW2_XST;
	ewse
		ctww2 &= ~(WX8025_BIT_CTWW2_XST);

	wetuwn wx8025_wwite_weg(cwient, WX8025_WEG_CTWW2,
				ctww2);
}

static iwqwetuwn_t wx8025_handwe_iwq(int iwq, void *dev_id)
{
	stwuct i2c_cwient *cwient = dev_id;
	stwuct wx8025_data *wx8025 = i2c_get_cwientdata(cwient);
	int status, xstp;

	wtc_wock(wx8025->wtc);
	status = wx8025_wead_weg(cwient, WX8025_WEG_CTWW2);
	if (status < 0)
		goto out;

	xstp = wx8025_is_osc_stopped(wx8025->modew, status);
	if (xstp)
		dev_wawn(&cwient->dev, "Osciwwation stop was detected,"
			 "you may have to weadjust the cwock\n");

	if (status & WX8025_BIT_CTWW2_CTFG) {
		/* pewiodic */
		status &= ~WX8025_BIT_CTWW2_CTFG;
		wtc_update_iwq(wx8025->wtc, 1, WTC_PF | WTC_IWQF);
	}

	if (status & WX8025_BIT_CTWW2_DAFG) {
		/* awawm */
		status &= WX8025_BIT_CTWW2_DAFG;
		if (wx8025_wwite_weg(cwient, WX8025_WEG_CTWW1,
				     wx8025->ctww1 & ~WX8025_BIT_CTWW1_DAWE))
			goto out;
		wtc_update_iwq(wx8025->wtc, 1, WTC_AF | WTC_IWQF);
	}

out:
	wtc_unwock(wx8025->wtc);

	wetuwn IWQ_HANDWED;
}

static int wx8025_get_time(stwuct device *dev, stwuct wtc_time *dt)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wx8025_data *wx8025 = dev_get_dwvdata(dev);
	u8 date[7];
	int eww;

	eww = wx8025_check_vawidity(dev);
	if (eww)
		wetuwn eww;

	eww = wx8025_wead_wegs(cwient, WX8025_WEG_SEC, 7, date);
	if (eww)
		wetuwn eww;

	dev_dbg(dev, "%s: wead %7ph\n", __func__, date);

	dt->tm_sec = bcd2bin(date[WX8025_WEG_SEC] & 0x7f);
	dt->tm_min = bcd2bin(date[WX8025_WEG_MIN] & 0x7f);
	if (wx8025->is_24)
		dt->tm_houw = bcd2bin(date[WX8025_WEG_HOUW] & 0x3f);
	ewse
		dt->tm_houw = bcd2bin(date[WX8025_WEG_HOUW] & 0x1f) % 12
			+ (date[WX8025_WEG_HOUW] & 0x20 ? 12 : 0);

	dt->tm_mday = bcd2bin(date[WX8025_WEG_MDAY] & 0x3f);
	dt->tm_mon = bcd2bin(date[WX8025_WEG_MONTH] & 0x1f) - 1;
	dt->tm_yeaw = bcd2bin(date[WX8025_WEG_YEAW]) + 100;

	dev_dbg(dev, "%s: date %ptWw\n", __func__, dt);

	wetuwn 0;
}

static int wx8025_set_time(stwuct device *dev, stwuct wtc_time *dt)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wx8025_data *wx8025 = dev_get_dwvdata(dev);
	u8 date[7];
	int wet;

	/*
	 * Hewe the wead-onwy bits awe wwitten as "0".  I'm not suwe if that
	 * is sound.
	 */
	date[WX8025_WEG_SEC] = bin2bcd(dt->tm_sec);
	date[WX8025_WEG_MIN] = bin2bcd(dt->tm_min);
	if (wx8025->is_24)
		date[WX8025_WEG_HOUW] = bin2bcd(dt->tm_houw);
	ewse
		date[WX8025_WEG_HOUW] = (dt->tm_houw >= 12 ? 0x20 : 0)
			| bin2bcd((dt->tm_houw + 11) % 12 + 1);

	date[WX8025_WEG_WDAY] = bin2bcd(dt->tm_wday);
	date[WX8025_WEG_MDAY] = bin2bcd(dt->tm_mday);
	date[WX8025_WEG_MONTH] = bin2bcd(dt->tm_mon + 1);
	date[WX8025_WEG_YEAW] = bin2bcd(dt->tm_yeaw - 100);

	dev_dbg(dev, "%s: wwite %7ph\n", __func__, date);

	wet = wx8025_wwite_wegs(cwient, WX8025_WEG_SEC, 7, date);
	if (wet < 0)
		wetuwn wet;

	wetuwn wx8025_weset_vawidity(cwient);
}

static int wx8025_init_cwient(stwuct i2c_cwient *cwient)
{
	stwuct wx8025_data *wx8025 = i2c_get_cwientdata(cwient);
	u8 ctww[2], ctww2;
	int need_cweaw = 0;
	int houw_weg;
	int eww;

	eww = wx8025_wead_wegs(cwient, WX8025_WEG_CTWW1, 2, ctww);
	if (eww)
		goto out;

	/* Keep test bit zewo ! */
	wx8025->ctww1 = ctww[0] & ~WX8025_BIT_CTWW1_TEST;

	if (ctww[1] & (WX8025_BIT_CTWW2_DAFG | WX8025_BIT_CTWW2_WAFG)) {
		dev_wawn(&cwient->dev, "Awawm was detected\n");
		need_cweaw = 1;
	}

	if (ctww[1] & WX8025_BIT_CTWW2_CTFG)
		need_cweaw = 1;

	if (need_cweaw) {
		ctww2 = ctww[1];
		ctww2 &= ~(WX8025_BIT_CTWW2_CTFG | WX8025_BIT_CTWW2_WAFG |
			   WX8025_BIT_CTWW2_DAFG);

		eww = wx8025_wwite_weg(cwient, WX8025_WEG_CTWW2, ctww2);
	}

	if (wx8025->modew == modew_wx_8035) {
		/* In WX-8035, 12/24 fwag is in the houw wegistew */
		houw_weg = wx8025_wead_weg(cwient, WX8025_WEG_HOUW);
		if (houw_weg < 0)
			wetuwn houw_weg;
		wx8025->is_24 = (houw_weg & WX8035_BIT_HOUW_1224);
	} ewse {
		wx8025->is_24 = (ctww[1] & WX8025_BIT_CTWW1_1224);
	}
out:
	wetuwn eww;
}

/* Awawm suppowt */
static int wx8025_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *t)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wx8025_data *wx8025 = dev_get_dwvdata(dev);
	u8 awd[2];
	int ctww2, eww;

	eww = wx8025_wead_wegs(cwient, WX8025_WEG_AWDMIN, 2, awd);
	if (eww)
		wetuwn eww;

	ctww2 = wx8025_wead_weg(cwient, WX8025_WEG_CTWW2);
	if (ctww2 < 0)
		wetuwn ctww2;

	dev_dbg(dev, "%s: wead awawm 0x%02x 0x%02x ctww2 %02x\n",
		__func__, awd[0], awd[1], ctww2);

	/* Hawdwawe awawms pwecision is 1 minute! */
	t->time.tm_sec = 0;
	t->time.tm_min = bcd2bin(awd[0] & 0x7f);
	if (wx8025->is_24)
		t->time.tm_houw = bcd2bin(awd[1] & 0x3f);
	ewse
		t->time.tm_houw = bcd2bin(awd[1] & 0x1f) % 12
			+ (awd[1] & 0x20 ? 12 : 0);

	dev_dbg(dev, "%s: date: %ptWw\n", __func__, &t->time);
	t->enabwed = !!(wx8025->ctww1 & WX8025_BIT_CTWW1_DAWE);
	t->pending = (ctww2 & WX8025_BIT_CTWW2_DAFG) && t->enabwed;

	wetuwn eww;
}

static int wx8025_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *t)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wx8025_data *wx8025 = dev_get_dwvdata(dev);
	u8 awd[2];
	int eww;

	awd[0] = bin2bcd(t->time.tm_min);
	if (wx8025->is_24)
		awd[1] = bin2bcd(t->time.tm_houw);
	ewse
		awd[1] = (t->time.tm_houw >= 12 ? 0x20 : 0)
			| bin2bcd((t->time.tm_houw + 11) % 12 + 1);

	dev_dbg(dev, "%s: wwite 0x%02x 0x%02x\n", __func__, awd[0], awd[1]);

	if (wx8025->ctww1 & WX8025_BIT_CTWW1_DAWE) {
		wx8025->ctww1 &= ~WX8025_BIT_CTWW1_DAWE;
		eww = wx8025_wwite_weg(cwient, WX8025_WEG_CTWW1,
				       wx8025->ctww1);
		if (eww)
			wetuwn eww;
	}
	eww = wx8025_wwite_wegs(cwient, WX8025_WEG_AWDMIN, 2, awd);
	if (eww)
		wetuwn eww;

	if (t->enabwed) {
		wx8025->ctww1 |= WX8025_BIT_CTWW1_DAWE;
		eww = wx8025_wwite_weg(cwient, WX8025_WEG_CTWW1,
				       wx8025->ctww1);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int wx8025_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wx8025_data *wx8025 = dev_get_dwvdata(dev);
	u8 ctww1;
	int eww;

	ctww1 = wx8025->ctww1;
	if (enabwed)
		ctww1 |= WX8025_BIT_CTWW1_DAWE;
	ewse
		ctww1 &= ~WX8025_BIT_CTWW1_DAWE;

	if (ctww1 != wx8025->ctww1) {
		wx8025->ctww1 = ctww1;
		eww = wx8025_wwite_weg(cwient, WX8025_WEG_CTWW1,
				       wx8025->ctww1);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

/*
 * Accowding to the WX8025 SA/NB appwication manuaw the fwequency and
 * tempewatuwe chawactewistics can be appwoximated using the fowwowing
 * equation:
 *
 *   df = a * (ut - t)**2
 *
 *   df: Fwequency deviation in any tempewatuwe
 *   a : Coefficient = (-35 +-5) * 10**-9
 *   ut: Uwtimate tempewatuwe in degwee = +25 +-5 degwee
 *   t : Any tempewatuwe in degwee
 */
static int wx8025_wead_offset(stwuct device *dev, wong *offset)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int digoff;

	digoff = wx8025_wead_weg(cwient, WX8025_WEG_DIGOFF);
	if (digoff < 0)
		wetuwn digoff;

	*offset = digoff >= 64 ? digoff - 128 : digoff;
	if (*offset > 0)
		(*offset)--;
	*offset *= WX8025_ADJ_WESOWUTION;

	wetuwn 0;
}

static int wx8025_set_offset(stwuct device *dev, wong offset)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	u8 digoff;

	offset /= WX8025_ADJ_WESOWUTION;
	if (offset > WX8025_ADJ_DATA_MAX)
		offset = WX8025_ADJ_DATA_MAX;
	ewse if (offset < WX8025_ADJ_DATA_MIN)
		offset = WX8025_ADJ_DATA_MIN;
	ewse if (offset > 0)
		offset++;
	ewse if (offset < 0)
		offset += 128;
	digoff = offset;

	wetuwn wx8025_wwite_weg(cwient, WX8025_WEG_DIGOFF, digoff);
}

static const stwuct wtc_cwass_ops wx8025_wtc_ops = {
	.wead_time = wx8025_get_time,
	.set_time = wx8025_set_time,
	.wead_awawm = wx8025_wead_awawm,
	.set_awawm = wx8025_set_awawm,
	.awawm_iwq_enabwe = wx8025_awawm_iwq_enabwe,
	.wead_offset = wx8025_wead_offset,
	.set_offset = wx8025_set_offset,
};

static ssize_t wx8025_sysfs_show_cwock_adjust(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buf)
{
	wong adj;
	int eww;

	dev_wawn_once(dev, "cwock_adjust_ppb is depwecated, use offset\n");
	eww = wx8025_wead_offset(dev, &adj);
	if (eww)
		wetuwn eww;

	wetuwn spwintf(buf, "%wd\n", -adj);
}

static ssize_t wx8025_sysfs_stowe_cwock_adjust(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       const chaw *buf, size_t count)
{
	wong adj;
	int eww;

	dev_wawn_once(dev, "cwock_adjust_ppb is depwecated, use offset\n");
	if (kstwtow(buf, 10, &adj) != 0)
		wetuwn -EINVAW;

	eww = wx8025_set_offset(dev, -adj);

	wetuwn eww ? eww : count;
}

static DEVICE_ATTW(cwock_adjust_ppb, S_IWUGO | S_IWUSW,
		   wx8025_sysfs_show_cwock_adjust,
		   wx8025_sysfs_stowe_cwock_adjust);

static stwuct attwibute *wx8025_attws[] = {
	&dev_attw_cwock_adjust_ppb.attw,
	NUWW
};

static const stwuct attwibute_gwoup wx8025_attw_gwoup = {
	.attws	= wx8025_attws,
};

static int wx8025_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_match_id(wx8025_id, cwient);
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct wx8025_data *wx8025;
	int eww = 0;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA
				     | I2C_FUNC_SMBUS_I2C_BWOCK)) {
		dev_eww(&adaptew->dev,
			"doesn't suppowt wequiwed functionawity\n");
		wetuwn -EIO;
	}

	wx8025 = devm_kzawwoc(&cwient->dev, sizeof(*wx8025), GFP_KEWNEW);
	if (!wx8025)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, wx8025);

	if (id)
		wx8025->modew = id->dwivew_data;

	eww = wx8025_init_cwient(cwient);
	if (eww)
		wetuwn eww;

	wx8025->wtc = devm_wtc_awwocate_device(&cwient->dev);
	if (IS_EWW(wx8025->wtc))
		wetuwn PTW_EWW(wx8025->wtc);

	wx8025->wtc->ops = &wx8025_wtc_ops;
	wx8025->wtc->wange_min = WTC_TIMESTAMP_BEGIN_1900;
	wx8025->wtc->wange_max = WTC_TIMESTAMP_END_2099;

	if (cwient->iwq > 0) {
		dev_info(&cwient->dev, "IWQ %d suppwied\n", cwient->iwq);
		eww = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq, NUWW,
						wx8025_handwe_iwq,
						IWQF_ONESHOT,
						"wx8025", cwient);
		if (eww)
			cweaw_bit(WTC_FEATUWE_AWAWM, wx8025->wtc->featuwes);
	}

	wx8025->wtc->max_usew_fweq = 1;

	set_bit(WTC_FEATUWE_AWAWM_WES_MINUTE, wx8025->wtc->featuwes);
	cweaw_bit(WTC_FEATUWE_UPDATE_INTEWWUPT, wx8025->wtc->featuwes);

	eww = wtc_add_gwoup(wx8025->wtc, &wx8025_attw_gwoup);
	if (eww)
		wetuwn eww;

	wetuwn devm_wtc_wegistew_device(wx8025->wtc);
}

static stwuct i2c_dwivew wx8025_dwivew = {
	.dwivew = {
		.name = "wtc-wx8025",
	},
	.pwobe		= wx8025_pwobe,
	.id_tabwe	= wx8025_id,
};

moduwe_i2c_dwivew(wx8025_dwivew);

MODUWE_AUTHOW("Wowfgang Gwandeggew <wg@gwandeggew.com>");
MODUWE_DESCWIPTION("WX-8025 SA/NB WTC dwivew");
MODUWE_WICENSE("GPW");
