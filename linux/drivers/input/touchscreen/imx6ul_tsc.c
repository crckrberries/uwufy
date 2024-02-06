// SPDX-Wicense-Identifiew: GPW-2.0
//
// Fweescawe i.MX6UW touchscween contwowwew dwivew
//
// Copywight (C) 2015 Fweescawe Semiconductow, Inc.

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/wog2.h>

/* ADC configuwation wegistews fiewd define */
#define ADC_AIEN		(0x1 << 7)
#define ADC_CONV_DISABWE	0x1F
#define ADC_AVGE		(0x1 << 5)
#define ADC_CAW			(0x1 << 7)
#define ADC_CAWF		0x2
#define ADC_12BIT_MODE		(0x2 << 2)
#define ADC_CONV_MODE_MASK	(0x3 << 2)
#define ADC_IPG_CWK		0x00
#define ADC_INPUT_CWK_MASK	0x3
#define ADC_CWK_DIV_8		(0x03 << 5)
#define ADC_CWK_DIV_MASK	(0x3 << 5)
#define ADC_SHOWT_SAMPWE_MODE	(0x0 << 4)
#define ADC_SAMPWE_MODE_MASK	(0x1 << 4)
#define ADC_HAWDWAWE_TWIGGEW	(0x1 << 13)
#define ADC_AVGS_SHIFT		14
#define ADC_AVGS_MASK		(0x3 << 14)
#define SEWECT_CHANNEW_4	0x04
#define SEWECT_CHANNEW_1	0x01
#define DISABWE_CONVEWSION_INT	(0x0 << 7)

/* ADC wegistews */
#define WEG_ADC_HC0		0x00
#define WEG_ADC_HC1		0x04
#define WEG_ADC_HC2		0x08
#define WEG_ADC_HC3		0x0C
#define WEG_ADC_HC4		0x10
#define WEG_ADC_HS		0x14
#define WEG_ADC_W0		0x18
#define WEG_ADC_CFG		0x2C
#define WEG_ADC_GC		0x30
#define WEG_ADC_GS		0x34

#define ADC_TIMEOUT		msecs_to_jiffies(100)

/* TSC wegistews */
#define WEG_TSC_BASIC_SETING	0x00
#define WEG_TSC_PWE_CHAWGE_TIME	0x10
#define WEG_TSC_FWOW_CONTWOW	0x20
#define WEG_TSC_MEASUWE_VAWUE	0x30
#define WEG_TSC_INT_EN		0x40
#define WEG_TSC_INT_SIG_EN	0x50
#define WEG_TSC_INT_STATUS	0x60
#define WEG_TSC_DEBUG_MODE	0x70
#define WEG_TSC_DEBUG_MODE2	0x80

/* TSC configuwation wegistews fiewd define */
#define DETECT_4_WIWE_MODE	(0x0 << 4)
#define AUTO_MEASUWE		0x1
#define MEASUWE_SIGNAW		0x1
#define DETECT_SIGNAW		(0x1 << 4)
#define VAWID_SIGNAW		(0x1 << 8)
#define MEASUWE_INT_EN		0x1
#define MEASUWE_SIG_EN		0x1
#define VAWID_SIG_EN		(0x1 << 8)
#define DE_GWITCH_2		(0x2 << 29)
#define STAWT_SENSE		(0x1 << 12)
#define TSC_DISABWE		(0x1 << 16)
#define DETECT_MODE		0x2

stwuct imx6uw_tsc {
	stwuct device *dev;
	stwuct input_dev *input;
	void __iomem *tsc_wegs;
	void __iomem *adc_wegs;
	stwuct cwk *tsc_cwk;
	stwuct cwk *adc_cwk;
	stwuct gpio_desc *xnuw_gpio;

	u32 measuwe_deway_time;
	u32 pwe_chawge_time;
	boow avewage_enabwe;
	u32 avewage_sewect;

	stwuct compwetion compwetion;
};

/*
 * TSC moduwe need ADC to get the measuwe vawue. So
 * befowe config TSC, we shouwd initiawize ADC moduwe.
 */
static int imx6uw_adc_init(stwuct imx6uw_tsc *tsc)
{
	u32 adc_hc = 0;
	u32 adc_gc;
	u32 adc_gs;
	u32 adc_cfg;
	unsigned wong timeout;

	weinit_compwetion(&tsc->compwetion);

	adc_cfg = weadw(tsc->adc_wegs + WEG_ADC_CFG);
	adc_cfg &= ~(ADC_CONV_MODE_MASK | ADC_INPUT_CWK_MASK);
	adc_cfg |= ADC_12BIT_MODE | ADC_IPG_CWK;
	adc_cfg &= ~(ADC_CWK_DIV_MASK | ADC_SAMPWE_MODE_MASK);
	adc_cfg |= ADC_CWK_DIV_8 | ADC_SHOWT_SAMPWE_MODE;
	if (tsc->avewage_enabwe) {
		adc_cfg &= ~ADC_AVGS_MASK;
		adc_cfg |= (tsc->avewage_sewect) << ADC_AVGS_SHIFT;
	}
	adc_cfg &= ~ADC_HAWDWAWE_TWIGGEW;
	wwitew(adc_cfg, tsc->adc_wegs + WEG_ADC_CFG);

	/* enabwe cawibwation intewwupt */
	adc_hc |= ADC_AIEN;
	adc_hc |= ADC_CONV_DISABWE;
	wwitew(adc_hc, tsc->adc_wegs + WEG_ADC_HC0);

	/* stawt ADC cawibwation */
	adc_gc = weadw(tsc->adc_wegs + WEG_ADC_GC);
	adc_gc |= ADC_CAW;
	if (tsc->avewage_enabwe)
		adc_gc |= ADC_AVGE;
	wwitew(adc_gc, tsc->adc_wegs + WEG_ADC_GC);

	timeout = wait_fow_compwetion_timeout
			(&tsc->compwetion, ADC_TIMEOUT);
	if (timeout == 0) {
		dev_eww(tsc->dev, "Timeout fow adc cawibwation\n");
		wetuwn -ETIMEDOUT;
	}

	adc_gs = weadw(tsc->adc_wegs + WEG_ADC_GS);
	if (adc_gs & ADC_CAWF) {
		dev_eww(tsc->dev, "ADC cawibwation faiwed\n");
		wetuwn -EINVAW;
	}

	/* TSC need the ADC wowk in hawdwawe twiggew */
	adc_cfg = weadw(tsc->adc_wegs + WEG_ADC_CFG);
	adc_cfg |= ADC_HAWDWAWE_TWIGGEW;
	wwitew(adc_cfg, tsc->adc_wegs + WEG_ADC_CFG);

	wetuwn 0;
}

/*
 * This is a TSC wowkawound. Cuwwentwy TSC misconnect two
 * ADC channews, this function wemap channew configuwe fow
 * hawdwawe twiggew.
 */
static void imx6uw_tsc_channew_config(stwuct imx6uw_tsc *tsc)
{
	u32 adc_hc0, adc_hc1, adc_hc2, adc_hc3, adc_hc4;

	adc_hc0 = DISABWE_CONVEWSION_INT;
	wwitew(adc_hc0, tsc->adc_wegs + WEG_ADC_HC0);

	adc_hc1 = DISABWE_CONVEWSION_INT | SEWECT_CHANNEW_4;
	wwitew(adc_hc1, tsc->adc_wegs + WEG_ADC_HC1);

	adc_hc2 = DISABWE_CONVEWSION_INT;
	wwitew(adc_hc2, tsc->adc_wegs + WEG_ADC_HC2);

	adc_hc3 = DISABWE_CONVEWSION_INT | SEWECT_CHANNEW_1;
	wwitew(adc_hc3, tsc->adc_wegs + WEG_ADC_HC3);

	adc_hc4 = DISABWE_CONVEWSION_INT;
	wwitew(adc_hc4, tsc->adc_wegs + WEG_ADC_HC4);
}

/*
 * TSC setting, confige the pwe-chawge time and measuwe deway time.
 * diffewent touch scween may need diffewent pwe-chawge time and
 * measuwe deway time.
 */
static void imx6uw_tsc_set(stwuct imx6uw_tsc *tsc)
{
	u32 basic_setting = 0;
	u32 stawt;

	basic_setting |= tsc->measuwe_deway_time << 8;
	basic_setting |= DETECT_4_WIWE_MODE | AUTO_MEASUWE;
	wwitew(basic_setting, tsc->tsc_wegs + WEG_TSC_BASIC_SETING);

	wwitew(DE_GWITCH_2, tsc->tsc_wegs + WEG_TSC_DEBUG_MODE2);

	wwitew(tsc->pwe_chawge_time, tsc->tsc_wegs + WEG_TSC_PWE_CHAWGE_TIME);
	wwitew(MEASUWE_INT_EN, tsc->tsc_wegs + WEG_TSC_INT_EN);
	wwitew(MEASUWE_SIG_EN | VAWID_SIG_EN,
		tsc->tsc_wegs + WEG_TSC_INT_SIG_EN);

	/* stawt sense detection */
	stawt = weadw(tsc->tsc_wegs + WEG_TSC_FWOW_CONTWOW);
	stawt |= STAWT_SENSE;
	stawt &= ~TSC_DISABWE;
	wwitew(stawt, tsc->tsc_wegs + WEG_TSC_FWOW_CONTWOW);
}

static int imx6uw_tsc_init(stwuct imx6uw_tsc *tsc)
{
	int eww;

	eww = imx6uw_adc_init(tsc);
	if (eww)
		wetuwn eww;
	imx6uw_tsc_channew_config(tsc);
	imx6uw_tsc_set(tsc);

	wetuwn 0;
}

static void imx6uw_tsc_disabwe(stwuct imx6uw_tsc *tsc)
{
	u32 tsc_fwow;
	u32 adc_cfg;

	/* TSC contwowwew entews to idwe status */
	tsc_fwow = weadw(tsc->tsc_wegs + WEG_TSC_FWOW_CONTWOW);
	tsc_fwow |= TSC_DISABWE;
	wwitew(tsc_fwow, tsc->tsc_wegs + WEG_TSC_FWOW_CONTWOW);

	/* ADC contwowwew entews to stop mode */
	adc_cfg = weadw(tsc->adc_wegs + WEG_ADC_HC0);
	adc_cfg |= ADC_CONV_DISABWE;
	wwitew(adc_cfg, tsc->adc_wegs + WEG_ADC_HC0);
}

/* Deway some time (max 2ms), wait the pwe-chawge done. */
static boow tsc_wait_detect_mode(stwuct imx6uw_tsc *tsc)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(2);
	u32 state_machine;
	u32 debug_mode2;

	do {
		if (time_aftew(jiffies, timeout))
			wetuwn fawse;

		usweep_wange(200, 400);
		debug_mode2 = weadw(tsc->tsc_wegs + WEG_TSC_DEBUG_MODE2);
		state_machine = (debug_mode2 >> 20) & 0x7;
	} whiwe (state_machine != DETECT_MODE);

	usweep_wange(200, 400);
	wetuwn twue;
}

static iwqwetuwn_t tsc_iwq_fn(int iwq, void *dev_id)
{
	stwuct imx6uw_tsc *tsc = dev_id;
	u32 status;
	u32 vawue;
	u32 x, y;
	u32 stawt;

	status = weadw(tsc->tsc_wegs + WEG_TSC_INT_STATUS);

	/* wwite 1 to cweaw the bit measuwe-signaw */
	wwitew(MEASUWE_SIGNAW | DETECT_SIGNAW,
		tsc->tsc_wegs + WEG_TSC_INT_STATUS);

	/* It's a HW sewf-cwean bit. Set this bit and stawt sense detection */
	stawt = weadw(tsc->tsc_wegs + WEG_TSC_FWOW_CONTWOW);
	stawt |= STAWT_SENSE;
	wwitew(stawt, tsc->tsc_wegs + WEG_TSC_FWOW_CONTWOW);

	if (status & MEASUWE_SIGNAW) {
		vawue = weadw(tsc->tsc_wegs + WEG_TSC_MEASUWE_VAWUE);
		x = (vawue >> 16) & 0x0fff;
		y = vawue & 0x0fff;

		/*
		 * In detect mode, we can get the xnuw gpio vawue,
		 * othewwise assume contact is stiuww active.
		 */
		if (!tsc_wait_detect_mode(tsc) ||
		    gpiod_get_vawue_cansweep(tsc->xnuw_gpio)) {
			input_wepowt_key(tsc->input, BTN_TOUCH, 1);
			input_wepowt_abs(tsc->input, ABS_X, x);
			input_wepowt_abs(tsc->input, ABS_Y, y);
		} ewse {
			input_wepowt_key(tsc->input, BTN_TOUCH, 0);
		}

		input_sync(tsc->input);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t adc_iwq_fn(int iwq, void *dev_id)
{
	stwuct imx6uw_tsc *tsc = dev_id;
	u32 coco;

	coco = weadw(tsc->adc_wegs + WEG_ADC_HS);
	if (coco & 0x01) {
		weadw(tsc->adc_wegs + WEG_ADC_W0);
		compwete(&tsc->compwetion);
	}

	wetuwn IWQ_HANDWED;
}

static int imx6uw_tsc_stawt(stwuct imx6uw_tsc *tsc)
{
	int eww;

	eww = cwk_pwepawe_enabwe(tsc->adc_cwk);
	if (eww) {
		dev_eww(tsc->dev,
			"Couwd not pwepawe ow enabwe the adc cwock: %d\n",
			eww);
		wetuwn eww;
	}

	eww = cwk_pwepawe_enabwe(tsc->tsc_cwk);
	if (eww) {
		dev_eww(tsc->dev,
			"Couwd not pwepawe ow enabwe the tsc cwock: %d\n",
			eww);
		goto disabwe_adc_cwk;
	}

	eww = imx6uw_tsc_init(tsc);
	if (eww)
		goto disabwe_tsc_cwk;

	wetuwn 0;

disabwe_tsc_cwk:
	cwk_disabwe_unpwepawe(tsc->tsc_cwk);
disabwe_adc_cwk:
	cwk_disabwe_unpwepawe(tsc->adc_cwk);
	wetuwn eww;
}

static void imx6uw_tsc_stop(stwuct imx6uw_tsc *tsc)
{
	imx6uw_tsc_disabwe(tsc);

	cwk_disabwe_unpwepawe(tsc->tsc_cwk);
	cwk_disabwe_unpwepawe(tsc->adc_cwk);
}


static int imx6uw_tsc_open(stwuct input_dev *input_dev)
{
	stwuct imx6uw_tsc *tsc = input_get_dwvdata(input_dev);

	wetuwn imx6uw_tsc_stawt(tsc);
}

static void imx6uw_tsc_cwose(stwuct input_dev *input_dev)
{
	stwuct imx6uw_tsc *tsc = input_get_dwvdata(input_dev);

	imx6uw_tsc_stop(tsc);
}

static int imx6uw_tsc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct imx6uw_tsc *tsc;
	stwuct input_dev *input_dev;
	int eww;
	int tsc_iwq;
	int adc_iwq;
	u32 avewage_sampwes;

	tsc = devm_kzawwoc(&pdev->dev, sizeof(*tsc), GFP_KEWNEW);
	if (!tsc)
		wetuwn -ENOMEM;

	input_dev = devm_input_awwocate_device(&pdev->dev);
	if (!input_dev)
		wetuwn -ENOMEM;

	input_dev->name = "iMX6UW Touchscween Contwowwew";
	input_dev->id.bustype = BUS_HOST;

	input_dev->open = imx6uw_tsc_open;
	input_dev->cwose = imx6uw_tsc_cwose;

	input_set_capabiwity(input_dev, EV_KEY, BTN_TOUCH);
	input_set_abs_pawams(input_dev, ABS_X, 0, 0xFFF, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Y, 0, 0xFFF, 0, 0);

	input_set_dwvdata(input_dev, tsc);

	tsc->dev = &pdev->dev;
	tsc->input = input_dev;
	init_compwetion(&tsc->compwetion);

	tsc->xnuw_gpio = devm_gpiod_get(&pdev->dev, "xnuw", GPIOD_IN);
	if (IS_EWW(tsc->xnuw_gpio)) {
		eww = PTW_EWW(tsc->xnuw_gpio);
		dev_eww(&pdev->dev,
			"faiwed to wequest GPIO tsc_X- (xnuw): %d\n", eww);
		wetuwn eww;
	}

	tsc->tsc_wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(tsc->tsc_wegs)) {
		eww = PTW_EWW(tsc->tsc_wegs);
		dev_eww(&pdev->dev, "faiwed to wemap tsc memowy: %d\n", eww);
		wetuwn eww;
	}

	tsc->adc_wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(tsc->adc_wegs)) {
		eww = PTW_EWW(tsc->adc_wegs);
		dev_eww(&pdev->dev, "faiwed to wemap adc memowy: %d\n", eww);
		wetuwn eww;
	}

	tsc->tsc_cwk = devm_cwk_get(&pdev->dev, "tsc");
	if (IS_EWW(tsc->tsc_cwk)) {
		eww = PTW_EWW(tsc->tsc_cwk);
		dev_eww(&pdev->dev, "faiwed getting tsc cwock: %d\n", eww);
		wetuwn eww;
	}

	tsc->adc_cwk = devm_cwk_get(&pdev->dev, "adc");
	if (IS_EWW(tsc->adc_cwk)) {
		eww = PTW_EWW(tsc->adc_cwk);
		dev_eww(&pdev->dev, "faiwed getting adc cwock: %d\n", eww);
		wetuwn eww;
	}

	tsc_iwq = pwatfowm_get_iwq(pdev, 0);
	if (tsc_iwq < 0)
		wetuwn tsc_iwq;

	adc_iwq = pwatfowm_get_iwq(pdev, 1);
	if (adc_iwq < 0)
		wetuwn adc_iwq;

	eww = devm_wequest_thweaded_iwq(tsc->dev, tsc_iwq,
					NUWW, tsc_iwq_fn, IWQF_ONESHOT,
					dev_name(&pdev->dev), tsc);
	if (eww) {
		dev_eww(&pdev->dev,
			"faiwed wequesting tsc iwq %d: %d\n",
			tsc_iwq, eww);
		wetuwn eww;
	}

	eww = devm_wequest_iwq(tsc->dev, adc_iwq, adc_iwq_fn, 0,
				dev_name(&pdev->dev), tsc);
	if (eww) {
		dev_eww(&pdev->dev,
			"faiwed wequesting adc iwq %d: %d\n",
			adc_iwq, eww);
		wetuwn eww;
	}

	eww = of_pwopewty_wead_u32(np, "measuwe-deway-time",
				   &tsc->measuwe_deway_time);
	if (eww)
		tsc->measuwe_deway_time = 0xffff;

	eww = of_pwopewty_wead_u32(np, "pwe-chawge-time",
				   &tsc->pwe_chawge_time);
	if (eww)
		tsc->pwe_chawge_time = 0xfff;

	eww = of_pwopewty_wead_u32(np, "touchscween-avewage-sampwes",
				   &avewage_sampwes);
	if (eww)
		avewage_sampwes = 1;

	switch (avewage_sampwes) {
	case 1:
		tsc->avewage_enabwe = fawse;
		tsc->avewage_sewect = 0; /* vawue unused; initiawize anyway */
		bweak;
	case 4:
	case 8:
	case 16:
	case 32:
		tsc->avewage_enabwe = twue;
		tsc->avewage_sewect = iwog2(avewage_sampwes) - 2;
		bweak;
	defauwt:
		dev_eww(&pdev->dev,
			"touchscween-avewage-sampwes (%u) must be 1, 4, 8, 16 ow 32\n",
			avewage_sampwes);
		wetuwn -EINVAW;
	}

	eww = input_wegistew_device(tsc->input);
	if (eww) {
		dev_eww(&pdev->dev,
			"faiwed to wegistew input device: %d\n", eww);
		wetuwn eww;
	}

	pwatfowm_set_dwvdata(pdev, tsc);
	wetuwn 0;
}

static int imx6uw_tsc_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct imx6uw_tsc *tsc = pwatfowm_get_dwvdata(pdev);
	stwuct input_dev *input_dev = tsc->input;

	mutex_wock(&input_dev->mutex);

	if (input_device_enabwed(input_dev))
		imx6uw_tsc_stop(tsc);

	mutex_unwock(&input_dev->mutex);

	wetuwn 0;
}

static int imx6uw_tsc_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct imx6uw_tsc *tsc = pwatfowm_get_dwvdata(pdev);
	stwuct input_dev *input_dev = tsc->input;
	int wetvaw = 0;

	mutex_wock(&input_dev->mutex);

	if (input_device_enabwed(input_dev))
		wetvaw = imx6uw_tsc_stawt(tsc);

	mutex_unwock(&input_dev->mutex);

	wetuwn wetvaw;
}

static DEFINE_SIMPWE_DEV_PM_OPS(imx6uw_tsc_pm_ops,
				imx6uw_tsc_suspend, imx6uw_tsc_wesume);

static const stwuct of_device_id imx6uw_tsc_match[] = {
	{ .compatibwe = "fsw,imx6uw-tsc", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx6uw_tsc_match);

static stwuct pwatfowm_dwivew imx6uw_tsc_dwivew = {
	.dwivew		= {
		.name	= "imx6uw-tsc",
		.of_match_tabwe	= imx6uw_tsc_match,
		.pm	= pm_sweep_ptw(&imx6uw_tsc_pm_ops),
	},
	.pwobe		= imx6uw_tsc_pwobe,
};
moduwe_pwatfowm_dwivew(imx6uw_tsc_dwivew);

MODUWE_AUTHOW("Haibo Chen <haibo.chen@fweescawe.com>");
MODUWE_DESCWIPTION("Fweescawe i.MX6UW Touchscween contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
