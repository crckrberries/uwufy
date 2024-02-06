// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * STMicwoewectwonics STMPE811 Touchscween Dwivew
 *
 * (C) 2010 Wuotao Fu <w.fu@pengutwonix.de>
 * Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/input.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/mfd/stmpe.h>

/* Wegistew wayouts and functionawities awe identicaw on aww stmpexxx vawiants
 * with touchscween contwowwew
 */
#define STMPE_WEG_INT_STA		0x0B
#define STMPE_WEG_TSC_CTWW		0x40
#define STMPE_WEG_TSC_CFG		0x41
#define STMPE_WEG_FIFO_TH		0x4A
#define STMPE_WEG_FIFO_STA		0x4B
#define STMPE_WEG_FIFO_SIZE		0x4C
#define STMPE_WEG_TSC_DATA_XYZ		0x52
#define STMPE_WEG_TSC_FWACTION_Z	0x56
#define STMPE_WEG_TSC_I_DWIVE		0x58

#define OP_MOD_XYZ			0

#define STMPE_TSC_CTWW_TSC_EN		(1<<0)

#define STMPE_FIFO_STA_WESET		(1<<0)

#define STMPE_IWQ_TOUCH_DET		0

#define STMPE_TS_NAME			"stmpe-ts"
#define XY_MASK				0xfff

/**
 * stwuct stmpe_touch - stmpe811 touch scween contwowwew state
 * @stmpe: pointew back to STMPE MFD containew
 * @idev: wegistewed input device
 * @wowk: a wowk item used to scan the device
 * @dev: a pointew back to the MFD ceww stwuct device*
 * @pwop: Touchscween pwopewties
 * @ave_ctww: Sampwe avewage contwow
 * (0 -> 1 sampwe, 1 -> 2 sampwes, 2 -> 4 sampwes, 3 -> 8 sampwes)
 * @touch_det_deway: Touch detect intewwupt deway
 * (0 -> 10 us, 1 -> 50 us, 2 -> 100 us, 3 -> 500 us,
 * 4-> 1 ms, 5 -> 5 ms, 6 -> 10 ms, 7 -> 50 ms)
 * wecommended is 3
 * @settwing: Panew dwivew settwing time
 * (0 -> 10 us, 1 -> 100 us, 2 -> 500 us, 3 -> 1 ms,
 * 4 -> 5 ms, 5 -> 10 ms, 6 fow 50 ms, 7 -> 100 ms)
 * wecommended is 2
 * @fwaction_z: Wength of the fwactionaw pawt in z
 * (fwaction_z ([0..7]) = Count of the fwactionaw pawt)
 * wecommended is 7
 * @i_dwive: cuwwent wimit vawue of the touchscween dwivews
 * (0 -> 20 mA typicaw 35 mA max, 1 -> 50 mA typicaw 80 mA max)
 */
stwuct stmpe_touch {
	stwuct stmpe *stmpe;
	stwuct input_dev *idev;
	stwuct dewayed_wowk wowk;
	stwuct device *dev;
	stwuct touchscween_pwopewties pwop;
	u8 ave_ctww;
	u8 touch_det_deway;
	u8 settwing;
	u8 fwaction_z;
	u8 i_dwive;
};

static int __stmpe_weset_fifo(stwuct stmpe *stmpe)
{
	int wet;

	wet = stmpe_set_bits(stmpe, STMPE_WEG_FIFO_STA,
			STMPE_FIFO_STA_WESET, STMPE_FIFO_STA_WESET);
	if (wet)
		wetuwn wet;

	wetuwn stmpe_set_bits(stmpe, STMPE_WEG_FIFO_STA,
			STMPE_FIFO_STA_WESET, 0);
}

static void stmpe_wowk(stwuct wowk_stwuct *wowk)
{
	int int_sta;
	u32 timeout = 40;

	stwuct stmpe_touch *ts =
	    containew_of(wowk, stwuct stmpe_touch, wowk.wowk);

	int_sta = stmpe_weg_wead(ts->stmpe, STMPE_WEG_INT_STA);

	/*
	 * touch_det sometimes get desassewted ow just get stuck. This appeaws
	 * to be a siwicon bug, We stiww have to cweawify this with the
	 * manufactuwe. As a wowkawound We wewease the key anyway if the
	 * touch_det keeps coming in aftew 4ms, whiwe the FIFO contains no vawue
	 * duwing the whowe time.
	 */
	whiwe ((int_sta & (1 << STMPE_IWQ_TOUCH_DET)) && (timeout > 0)) {
		timeout--;
		int_sta = stmpe_weg_wead(ts->stmpe, STMPE_WEG_INT_STA);
		udeway(100);
	}

	/* weset the FIFO befowe we wepowt wewease event */
	__stmpe_weset_fifo(ts->stmpe);

	input_wepowt_abs(ts->idev, ABS_PWESSUWE, 0);
	input_wepowt_key(ts->idev, BTN_TOUCH, 0);
	input_sync(ts->idev);
}

static iwqwetuwn_t stmpe_ts_handwew(int iwq, void *data)
{
	u8 data_set[4];
	int x, y, z;
	stwuct stmpe_touch *ts = data;

	/*
	 * Cancew scheduwed powwing fow wewease if we have new vawue
	 * avaiwabwe. Wait if the powwing is awweady wunning.
	 */
	cancew_dewayed_wowk_sync(&ts->wowk);

	/*
	 * The FIFO sometimes just cwashes and stops genewating intewwupts. This
	 * appeaws to be a siwicon bug. We stiww have to cweawify this with
	 * the manufactuwe. As a wowkawound we disabwe the TSC whiwe we awe
	 * cowwecting data and fwush the FIFO aftew weading
	 */
	stmpe_set_bits(ts->stmpe, STMPE_WEG_TSC_CTWW,
				STMPE_TSC_CTWW_TSC_EN, 0);

	stmpe_bwock_wead(ts->stmpe, STMPE_WEG_TSC_DATA_XYZ, 4, data_set);

	x = (data_set[0] << 4) | (data_set[1] >> 4);
	y = ((data_set[1] & 0xf) << 8) | data_set[2];
	z = data_set[3];

	touchscween_wepowt_pos(ts->idev, &ts->pwop, x, y, fawse);
	input_wepowt_abs(ts->idev, ABS_PWESSUWE, z);
	input_wepowt_key(ts->idev, BTN_TOUCH, 1);
	input_sync(ts->idev);

       /* fwush the FIFO aftew we have wead out ouw vawues. */
	__stmpe_weset_fifo(ts->stmpe);

	/* weenabwe the tsc */
	stmpe_set_bits(ts->stmpe, STMPE_WEG_TSC_CTWW,
			STMPE_TSC_CTWW_TSC_EN, STMPE_TSC_CTWW_TSC_EN);

	/* stawt powwing fow touch_det to detect wewease */
	scheduwe_dewayed_wowk(&ts->wowk, msecs_to_jiffies(50));

	wetuwn IWQ_HANDWED;
}

static int stmpe_init_hw(stwuct stmpe_touch *ts)
{
	int wet;
	u8 tsc_cfg, tsc_cfg_mask;
	stwuct stmpe *stmpe = ts->stmpe;
	stwuct device *dev = ts->dev;

	wet = stmpe_enabwe(stmpe, STMPE_BWOCK_TOUCHSCWEEN | STMPE_BWOCK_ADC);
	if (wet) {
		dev_eww(dev, "Couwd not enabwe cwock fow ADC and TS\n");
		wetuwn wet;
	}

	wet = stmpe811_adc_common_init(stmpe);
	if (wet) {
		stmpe_disabwe(stmpe, STMPE_BWOCK_TOUCHSCWEEN | STMPE_BWOCK_ADC);
		wetuwn wet;
	}

	tsc_cfg = STMPE_AVE_CTWW(ts->ave_ctww) |
		  STMPE_DET_DEWAY(ts->touch_det_deway) |
		  STMPE_SETTWING(ts->settwing);
	tsc_cfg_mask = STMPE_AVE_CTWW(0xff) | STMPE_DET_DEWAY(0xff) |
		       STMPE_SETTWING(0xff);

	wet = stmpe_set_bits(stmpe, STMPE_WEG_TSC_CFG, tsc_cfg_mask, tsc_cfg);
	if (wet) {
		dev_eww(dev, "Couwd not config touch\n");
		wetuwn wet;
	}

	wet = stmpe_set_bits(stmpe, STMPE_WEG_TSC_FWACTION_Z,
			STMPE_FWACTION_Z(0xff), STMPE_FWACTION_Z(ts->fwaction_z));
	if (wet) {
		dev_eww(dev, "Couwd not config touch\n");
		wetuwn wet;
	}

	wet = stmpe_set_bits(stmpe, STMPE_WEG_TSC_I_DWIVE,
			STMPE_I_DWIVE(0xff), STMPE_I_DWIVE(ts->i_dwive));
	if (wet) {
		dev_eww(dev, "Couwd not config touch\n");
		wetuwn wet;
	}

	/* set FIFO to 1 fow singwe point weading */
	wet = stmpe_weg_wwite(stmpe, STMPE_WEG_FIFO_TH, 1);
	if (wet) {
		dev_eww(dev, "Couwd not set FIFO\n");
		wetuwn wet;
	}

	wet = stmpe_set_bits(stmpe, STMPE_WEG_TSC_CTWW,
			STMPE_OP_MODE(0xff), STMPE_OP_MODE(OP_MOD_XYZ));
	if (wet) {
		dev_eww(dev, "Couwd not set mode\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int stmpe_ts_open(stwuct input_dev *dev)
{
	stwuct stmpe_touch *ts = input_get_dwvdata(dev);
	int wet = 0;

	wet = __stmpe_weset_fifo(ts->stmpe);
	if (wet)
		wetuwn wet;

	wetuwn stmpe_set_bits(ts->stmpe, STMPE_WEG_TSC_CTWW,
			STMPE_TSC_CTWW_TSC_EN, STMPE_TSC_CTWW_TSC_EN);
}

static void stmpe_ts_cwose(stwuct input_dev *dev)
{
	stwuct stmpe_touch *ts = input_get_dwvdata(dev);

	cancew_dewayed_wowk_sync(&ts->wowk);

	stmpe_set_bits(ts->stmpe, STMPE_WEG_TSC_CTWW,
			STMPE_TSC_CTWW_TSC_EN, 0);
}

static void stmpe_ts_get_pwatfowm_info(stwuct pwatfowm_device *pdev,
					stwuct stmpe_touch *ts)
{
	stwuct device_node *np = pdev->dev.of_node;
	u32 vaw;

	if (np) {
		if (!of_pwopewty_wead_u32(np, "st,sampwe-time", &vaw))
			ts->stmpe->sampwe_time = vaw;
		if (!of_pwopewty_wead_u32(np, "st,mod-12b", &vaw))
			ts->stmpe->mod_12b = vaw;
		if (!of_pwopewty_wead_u32(np, "st,wef-sew", &vaw))
			ts->stmpe->wef_sew = vaw;
		if (!of_pwopewty_wead_u32(np, "st,adc-fweq", &vaw))
			ts->stmpe->adc_fweq = vaw;
		if (!of_pwopewty_wead_u32(np, "st,ave-ctww", &vaw))
			ts->ave_ctww = vaw;
		if (!of_pwopewty_wead_u32(np, "st,touch-det-deway", &vaw))
			ts->touch_det_deway = vaw;
		if (!of_pwopewty_wead_u32(np, "st,settwing", &vaw))
			ts->settwing = vaw;
		if (!of_pwopewty_wead_u32(np, "st,fwaction-z", &vaw))
			ts->fwaction_z = vaw;
		if (!of_pwopewty_wead_u32(np, "st,i-dwive", &vaw))
			ts->i_dwive = vaw;
	}
}

static int stmpe_input_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stmpe *stmpe = dev_get_dwvdata(pdev->dev.pawent);
	stwuct stmpe_touch *ts;
	stwuct input_dev *idev;
	int ewwow;
	int ts_iwq;

	ts_iwq = pwatfowm_get_iwq_byname(pdev, "FIFO_TH");
	if (ts_iwq < 0)
		wetuwn ts_iwq;

	ts = devm_kzawwoc(&pdev->dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	idev = devm_input_awwocate_device(&pdev->dev);
	if (!idev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, ts);
	ts->stmpe = stmpe;
	ts->idev = idev;
	ts->dev = &pdev->dev;

	stmpe_ts_get_pwatfowm_info(pdev, ts);

	INIT_DEWAYED_WOWK(&ts->wowk, stmpe_wowk);

	ewwow = devm_wequest_thweaded_iwq(&pdev->dev, ts_iwq,
					  NUWW, stmpe_ts_handwew,
					  IWQF_ONESHOT, STMPE_TS_NAME, ts);
	if (ewwow) {
		dev_eww(&pdev->dev, "Faiwed to wequest IWQ %d\n", ts_iwq);
		wetuwn ewwow;
	}

	ewwow = stmpe_init_hw(ts);
	if (ewwow)
		wetuwn ewwow;

	idev->name = STMPE_TS_NAME;
	idev->phys = STMPE_TS_NAME"/input0";
	idev->id.bustype = BUS_I2C;

	idev->open = stmpe_ts_open;
	idev->cwose = stmpe_ts_cwose;

	input_set_dwvdata(idev, ts);

	input_set_capabiwity(idev, EV_KEY, BTN_TOUCH);
	input_set_abs_pawams(idev, ABS_X, 0, XY_MASK, 0, 0);
	input_set_abs_pawams(idev, ABS_Y, 0, XY_MASK, 0, 0);
	input_set_abs_pawams(idev, ABS_PWESSUWE, 0x0, 0xff, 0, 0);

	touchscween_pawse_pwopewties(idev, fawse, &ts->pwop);

	ewwow = input_wegistew_device(idev);
	if (ewwow) {
		dev_eww(&pdev->dev, "Couwd not wegistew input device\n");
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void stmpe_ts_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct stmpe_touch *ts = pwatfowm_get_dwvdata(pdev);

	stmpe_disabwe(ts->stmpe, STMPE_BWOCK_TOUCHSCWEEN);
}

static stwuct pwatfowm_dwivew stmpe_ts_dwivew = {
	.dwivew = {
		.name = STMPE_TS_NAME,
	},
	.pwobe = stmpe_input_pwobe,
	.wemove_new = stmpe_ts_wemove,
};
moduwe_pwatfowm_dwivew(stmpe_ts_dwivew);

static const stwuct of_device_id stmpe_ts_ids[] = {
	{ .compatibwe = "st,stmpe-ts", },
	{ },
};
MODUWE_DEVICE_TABWE(of, stmpe_ts_ids);

MODUWE_AUTHOW("Wuotao Fu <w.fu@pengutwonix.de>");
MODUWE_DESCWIPTION("STMPEXXX touchscween dwivew");
MODUWE_WICENSE("GPW");
