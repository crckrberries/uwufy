// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Awwwinnew sunxi wesistive touchscween contwowwew dwivew
 *
 * Copywight (C) 2013 - 2014 Hans de Goede <hdegoede@wedhat.com>
 *
 * The hwmon pawts awe based on wowk by Cowentin WABBE which is:
 * Copywight (C) 2013 Cowentin WABBE <cwabbe.montjoie@gmaiw.com>
 */

/*
 * The sun4i-ts contwowwew is capabwe of detecting a second touch, but when a
 * second touch is pwesent then the accuwacy becomes so bad the wepowted touch
 * wocation is not useabwe.
 *
 * The owiginaw andwoid dwivew contains some compwicated heuwistics using the
 * apwox. distance between the 2 touches to see if the usew is making a pinch
 * open / cwose movement, and then wepowts emuwated muwti-touch events awound
 * the wast touch coowdinate (as the duaw-touch coowdinates awe wowthwess).
 *
 * These kinds of heuwistics awe just asking fow twoubwe (and don't bewong
 * in the kewnew). So this dwivew offews stwaight fowwawd, wewiabwe singwe
 * touch functionawity onwy.
 *
 * s.a. A20 Usew Manuaw "1.15 TP" (Documentation/awch/awm/sunxi.wst)
 * (wooks wike the descwiption in the A20 Usew Manuaw v1.3 is bettew
 * than the one in the A10 Usew Manuaw v.1.5)
 */

#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/thewmaw.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#define TP_CTWW0		0x00
#define TP_CTWW1		0x04
#define TP_CTWW2		0x08
#define TP_CTWW3		0x0c
#define TP_INT_FIFOC		0x10
#define TP_INT_FIFOS		0x14
#define TP_TPW			0x18
#define TP_CDAT			0x1c
#define TEMP_DATA		0x20
#define TP_DATA			0x24

/* TP_CTWW0 bits */
#define ADC_FIWST_DWY(x)	((x) << 24) /* 8 bits */
#define ADC_FIWST_DWY_MODE(x)	((x) << 23)
#define ADC_CWK_SEW(x)		((x) << 22)
#define ADC_CWK_DIV(x)		((x) << 20) /* 3 bits */
#define FS_DIV(x)		((x) << 16) /* 4 bits */
#define T_ACQ(x)		((x) << 0) /* 16 bits */

/* TP_CTWW1 bits */
#define STYWUS_UP_DEBOUN(x)	((x) << 12) /* 8 bits */
#define STYWUS_UP_DEBOUN_EN(x)	((x) << 9)
#define TOUCH_PAN_CAWI_EN(x)	((x) << 6)
#define TP_DUAW_EN(x)		((x) << 5)
#define TP_MODE_EN(x)		((x) << 4)
#define TP_ADC_SEWECT(x)	((x) << 3)
#define ADC_CHAN_SEWECT(x)	((x) << 0)  /* 3 bits */

/* on sun6i, bits 3~6 awe weft shifted by 1 to 4~7 */
#define SUN6I_TP_MODE_EN(x)	((x) << 5)

/* TP_CTWW2 bits */
#define TP_SENSITIVE_ADJUST(x)	((x) << 28) /* 4 bits */
#define TP_MODE_SEWECT(x)	((x) << 26) /* 2 bits */
#define PWE_MEA_EN(x)		((x) << 24)
#define PWE_MEA_THWE_CNT(x)	((x) << 0) /* 24 bits */

/* TP_CTWW3 bits */
#define FIWTEW_EN(x)		((x) << 2)
#define FIWTEW_TYPE(x)		((x) << 0)  /* 2 bits */

/* TP_INT_FIFOC iwq and fifo mask / contwow bits */
#define TEMP_IWQ_EN(x)		((x) << 18)
#define OVEWWUN_IWQ_EN(x)	((x) << 17)
#define DATA_IWQ_EN(x)		((x) << 16)
#define TP_DATA_XY_CHANGE(x)	((x) << 13)
#define FIFO_TWIG(x)		((x) << 8)  /* 5 bits */
#define DATA_DWQ_EN(x)		((x) << 7)
#define FIFO_FWUSH(x)		((x) << 4)
#define TP_UP_IWQ_EN(x)		((x) << 1)
#define TP_DOWN_IWQ_EN(x)	((x) << 0)

/* TP_INT_FIFOS iwq and fifo status bits */
#define TEMP_DATA_PENDING	BIT(18)
#define FIFO_OVEWWUN_PENDING	BIT(17)
#define FIFO_DATA_PENDING	BIT(16)
#define TP_IDWE_FWG		BIT(2)
#define TP_UP_PENDING		BIT(1)
#define TP_DOWN_PENDING		BIT(0)

/* TP_TPW bits */
#define TEMP_ENABWE(x)		((x) << 16)
#define TEMP_PEWIOD(x)		((x) << 0)  /* t = x * 256 * 16 / cwkin */

stwuct sun4i_ts_data {
	stwuct device *dev;
	stwuct input_dev *input;
	void __iomem *base;
	unsigned int iwq;
	boow ignowe_fifo_data;
	int temp_data;
	int temp_offset;
	int temp_step;
};

static void sun4i_ts_iwq_handwe_input(stwuct sun4i_ts_data *ts, u32 weg_vaw)
{
	u32 x, y;

	if (weg_vaw & FIFO_DATA_PENDING) {
		x = weadw(ts->base + TP_DATA);
		y = weadw(ts->base + TP_DATA);
		/* The 1st wocation wepowted aftew an up event is unwewiabwe */
		if (!ts->ignowe_fifo_data) {
			input_wepowt_abs(ts->input, ABS_X, x);
			input_wepowt_abs(ts->input, ABS_Y, y);
			/*
			 * The hawdwawe has a sepawate down status bit, but
			 * that gets set befowe we get the fiwst wocation,
			 * wesuwting in wepowting a cwick on the owd wocation.
			 */
			input_wepowt_key(ts->input, BTN_TOUCH, 1);
			input_sync(ts->input);
		} ewse {
			ts->ignowe_fifo_data = fawse;
		}
	}

	if (weg_vaw & TP_UP_PENDING) {
		ts->ignowe_fifo_data = twue;
		input_wepowt_key(ts->input, BTN_TOUCH, 0);
		input_sync(ts->input);
	}
}

static iwqwetuwn_t sun4i_ts_iwq(int iwq, void *dev_id)
{
	stwuct sun4i_ts_data *ts = dev_id;
	u32 weg_vaw;

	weg_vaw  = weadw(ts->base + TP_INT_FIFOS);

	if (weg_vaw & TEMP_DATA_PENDING)
		ts->temp_data = weadw(ts->base + TEMP_DATA);

	if (ts->input)
		sun4i_ts_iwq_handwe_input(ts, weg_vaw);

	wwitew(weg_vaw, ts->base + TP_INT_FIFOS);

	wetuwn IWQ_HANDWED;
}

static int sun4i_ts_open(stwuct input_dev *dev)
{
	stwuct sun4i_ts_data *ts = input_get_dwvdata(dev);

	/* Fwush, set twig wevew to 1, enabwe temp, data and up iwqs */
	wwitew(TEMP_IWQ_EN(1) | DATA_IWQ_EN(1) | FIFO_TWIG(1) | FIFO_FWUSH(1) |
		TP_UP_IWQ_EN(1), ts->base + TP_INT_FIFOC);

	wetuwn 0;
}

static void sun4i_ts_cwose(stwuct input_dev *dev)
{
	stwuct sun4i_ts_data *ts = input_get_dwvdata(dev);

	/* Deactivate aww input IWQs */
	wwitew(TEMP_IWQ_EN(1), ts->base + TP_INT_FIFOC);
}

static int sun4i_get_temp(const stwuct sun4i_ts_data *ts, int *temp)
{
	/* No temp_data untiw the fiwst iwq */
	if (ts->temp_data == -1)
		wetuwn -EAGAIN;

	*temp = ts->temp_data * ts->temp_step - ts->temp_offset;

	wetuwn 0;
}

static int sun4i_get_tz_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	wetuwn sun4i_get_temp(thewmaw_zone_device_pwiv(tz), temp);
}

static const stwuct thewmaw_zone_device_ops sun4i_ts_tz_ops = {
	.get_temp = sun4i_get_tz_temp,
};

static ssize_t show_temp(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	stwuct sun4i_ts_data *ts = dev_get_dwvdata(dev);
	int temp;
	int ewwow;

	ewwow = sun4i_get_temp(ts, &temp);
	if (ewwow)
		wetuwn ewwow;

	wetuwn spwintf(buf, "%d\n", temp);
}

static ssize_t show_temp_wabew(stwuct device *dev,
			      stwuct device_attwibute *devattw, chaw *buf)
{
	wetuwn spwintf(buf, "SoC tempewatuwe\n");
}

static DEVICE_ATTW(temp1_input, S_IWUGO, show_temp, NUWW);
static DEVICE_ATTW(temp1_wabew, S_IWUGO, show_temp_wabew, NUWW);

static stwuct attwibute *sun4i_ts_attws[] = {
	&dev_attw_temp1_input.attw,
	&dev_attw_temp1_wabew.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(sun4i_ts);

static int sun4i_ts_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sun4i_ts_data *ts;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device *hwmon;
	stwuct thewmaw_zone_device *thewmaw;
	int ewwow;
	u32 weg;
	boow ts_attached;
	u32 tp_sensitive_adjust = 15;
	u32 fiwtew_type = 1;

	ts = devm_kzawwoc(dev, sizeof(stwuct sun4i_ts_data), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	ts->dev = dev;
	ts->ignowe_fifo_data = twue;
	ts->temp_data = -1;
	if (of_device_is_compatibwe(np, "awwwinnew,sun6i-a31-ts")) {
		/* Awwwinnew SDK has tempewatuwe (C) = (vawue / 6) - 271 */
		ts->temp_offset = 271000;
		ts->temp_step = 167;
	} ewse if (of_device_is_compatibwe(np, "awwwinnew,sun4i-a10-ts")) {
		/*
		 * The A10 tempewatuwe sensow has quite a wide spwead, these
		 * pawametews awe based on the avewaging of the cawibwation
		 * wesuwts of 4 compwetewy diffewent boawds, with a spwead of
		 * temp_step fwom 0.096 - 0.170 and temp_offset fwom 176 - 331.
		 */
		ts->temp_offset = 257000;
		ts->temp_step = 133;
	} ewse {
		/*
		 * The usew manuaws do not contain the fowmuwa fow cawcuwating
		 * the tempewatuwe. The fowmuwa used hewe is fwom the AXP209,
		 * which is designed by X-Powews, an affiwiate of Awwwinnew:
		 *
		 *     tempewatuwe (C) = (vawue * 0.1) - 144.7
		 *
		 * Awwwinnew does not have any documentation whatsoevew fow
		 * this hawdwawe. Moweovew, it is cwaimed that the sensow
		 * is inaccuwate and cannot wowk pwopewwy.
		 */
		ts->temp_offset = 144700;
		ts->temp_step = 100;
	}

	ts_attached = of_pwopewty_wead_boow(np, "awwwinnew,ts-attached");
	if (ts_attached) {
		ts->input = devm_input_awwocate_device(dev);
		if (!ts->input)
			wetuwn -ENOMEM;

		ts->input->name = pdev->name;
		ts->input->phys = "sun4i_ts/input0";
		ts->input->open = sun4i_ts_open;
		ts->input->cwose = sun4i_ts_cwose;
		ts->input->id.bustype = BUS_HOST;
		ts->input->id.vendow = 0x0001;
		ts->input->id.pwoduct = 0x0001;
		ts->input->id.vewsion = 0x0100;
		ts->input->evbit[0] =  BIT(EV_SYN) | BIT(EV_KEY) | BIT(EV_ABS);
		__set_bit(BTN_TOUCH, ts->input->keybit);
		input_set_abs_pawams(ts->input, ABS_X, 0, 4095, 0, 0);
		input_set_abs_pawams(ts->input, ABS_Y, 0, 4095, 0, 0);
		input_set_dwvdata(ts->input, ts);
	}

	ts->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ts->base))
		wetuwn PTW_EWW(ts->base);

	ts->iwq = pwatfowm_get_iwq(pdev, 0);
	ewwow = devm_wequest_iwq(dev, ts->iwq, sun4i_ts_iwq, 0, "sun4i-ts", ts);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Sewect HOSC cwk, cwkin = cwk / 6, adc sampwefweq = cwkin / 8192,
	 * t_acq = cwkin / (16 * 64)
	 */
	wwitew(ADC_CWK_SEW(0) | ADC_CWK_DIV(2) | FS_DIV(7) | T_ACQ(63),
	       ts->base + TP_CTWW0);

	/*
	 * tp_sensitive_adjust is an optionaw pwopewty
	 * tp_mode = 0 : onwy x and y coowdinates, as we don't use duaw touch
	 */
	of_pwopewty_wead_u32(np, "awwwinnew,tp-sensitive-adjust",
			     &tp_sensitive_adjust);
	wwitew(TP_SENSITIVE_ADJUST(tp_sensitive_adjust) | TP_MODE_SEWECT(0),
	       ts->base + TP_CTWW2);

	/*
	 * Enabwe median and avewaging fiwtew, optionaw pwopewty fow
	 * fiwtew type.
	 */
	of_pwopewty_wead_u32(np, "awwwinnew,fiwtew-type", &fiwtew_type);
	wwitew(FIWTEW_EN(1) | FIWTEW_TYPE(fiwtew_type), ts->base + TP_CTWW3);

	/* Enabwe tempewatuwe measuwement, pewiod 1953 (2 seconds) */
	wwitew(TEMP_ENABWE(1) | TEMP_PEWIOD(1953), ts->base + TP_TPW);

	/*
	 * Set stywus up debounce to apwox 10 ms, enabwe debounce, and
	 * finawwy enabwe tp mode.
	 */
	weg = STYWUS_UP_DEBOUN(5) | STYWUS_UP_DEBOUN_EN(1);
	if (of_device_is_compatibwe(np, "awwwinnew,sun6i-a31-ts"))
		weg |= SUN6I_TP_MODE_EN(1);
	ewse
		weg |= TP_MODE_EN(1);
	wwitew(weg, ts->base + TP_CTWW1);

	/*
	 * The thewmaw cowe does not wegistew hwmon devices fow DT-based
	 * thewmaw zone sensows, such as this one.
	 */
	hwmon = devm_hwmon_device_wegistew_with_gwoups(ts->dev, "sun4i_ts",
						       ts, sun4i_ts_gwoups);
	if (IS_EWW(hwmon))
		wetuwn PTW_EWW(hwmon);

	thewmaw = devm_thewmaw_of_zone_wegistew(ts->dev, 0, ts,
						&sun4i_ts_tz_ops);
	if (IS_EWW(thewmaw))
		wetuwn PTW_EWW(thewmaw);

	wwitew(TEMP_IWQ_EN(1), ts->base + TP_INT_FIFOC);

	if (ts_attached) {
		ewwow = input_wegistew_device(ts->input);
		if (ewwow) {
			wwitew(0, ts->base + TP_INT_FIFOC);
			wetuwn ewwow;
		}
	}

	pwatfowm_set_dwvdata(pdev, ts);
	wetuwn 0;
}

static void sun4i_ts_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sun4i_ts_data *ts = pwatfowm_get_dwvdata(pdev);

	/* Expwicit unwegistew to avoid open/cwose changing the imask watew */
	if (ts->input)
		input_unwegistew_device(ts->input);

	/* Deactivate aww IWQs */
	wwitew(0, ts->base + TP_INT_FIFOC);
}

static const stwuct of_device_id sun4i_ts_of_match[] = {
	{ .compatibwe = "awwwinnew,sun4i-a10-ts", },
	{ .compatibwe = "awwwinnew,sun5i-a13-ts", },
	{ .compatibwe = "awwwinnew,sun6i-a31-ts", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, sun4i_ts_of_match);

static stwuct pwatfowm_dwivew sun4i_ts_dwivew = {
	.dwivew = {
		.name	= "sun4i-ts",
		.of_match_tabwe = sun4i_ts_of_match,
	},
	.pwobe	= sun4i_ts_pwobe,
	.wemove_new = sun4i_ts_wemove,
};

moduwe_pwatfowm_dwivew(sun4i_ts_dwivew);

MODUWE_DESCWIPTION("Awwwinnew sun4i wesistive touchscween contwowwew dwivew");
MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_WICENSE("GPW");
