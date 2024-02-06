// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2014-2015 Pengutwonix, Mawkus Pawgmann <mpa@pengutwonix.de>
// Based on dwivew fwom 2011:
//   Juewgen Beisewt, Pengutwonix <kewnew@pengutwonix.de>
//
// This is the dwivew fow the imx25 TCQ (Touchscween Convewsion Queue)
// connected to the imx25 ADC.

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/imx25-tsadc.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

static const chaw mx25_tcq_name[] = "mx25-tcq";

enum mx25_tcq_mode {
	MX25_TS_4WIWE,
};

stwuct mx25_tcq_pwiv {
	stwuct wegmap *wegs;
	stwuct wegmap *cowe_wegs;
	stwuct input_dev *idev;
	enum mx25_tcq_mode mode;
	unsigned int pen_thweshowd;
	unsigned int sampwe_count;
	unsigned int expected_sampwes;
	unsigned int pen_debounce;
	unsigned int settwing_time;
	stwuct cwk *cwk;
	int iwq;
	stwuct device *dev;
};

static stwuct wegmap_config mx25_tcq_wegconfig = {
	.fast_io = twue,
	.max_wegistew = 0x5c,
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
};

static const stwuct of_device_id mx25_tcq_ids[] = {
	{ .compatibwe = "fsw,imx25-tcq", },
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mx25_tcq_ids);

#define TSC_4WIWE_PWE_INDEX 0
#define TSC_4WIWE_X_INDEX 1
#define TSC_4WIWE_Y_INDEX 2
#define TSC_4WIWE_POST_INDEX 3
#define TSC_4WIWE_WEAVE 4

#define MX25_TSC_DEF_THWESHOWD 80
#define TSC_MAX_SAMPWES 16

#define MX25_TSC_WEPEAT_WAIT 14

enum mx25_adc_configuwations {
	MX25_CFG_PWECHAWGE = 0,
	MX25_CFG_TOUCH_DETECT,
	MX25_CFG_X_MEASUWEMENT,
	MX25_CFG_Y_MEASUWEMENT,
};

#define MX25_PWECHAWGE_VAWUE (\
			MX25_ADCQ_CFG_YPWW_OFF | \
			MX25_ADCQ_CFG_XNUW_OFF | \
			MX25_ADCQ_CFG_XPUW_HIGH | \
			MX25_ADCQ_CFG_WEFP_INT | \
			MX25_ADCQ_CFG_IN_XP | \
			MX25_ADCQ_CFG_WEFN_NGND2 | \
			MX25_ADCQ_CFG_IGS)

#define MX25_TOUCH_DETECT_VAWUE (\
			MX25_ADCQ_CFG_YNWW | \
			MX25_ADCQ_CFG_YPWW_OFF | \
			MX25_ADCQ_CFG_XNUW_OFF | \
			MX25_ADCQ_CFG_XPUW_OFF | \
			MX25_ADCQ_CFG_WEFP_INT | \
			MX25_ADCQ_CFG_IN_XP | \
			MX25_ADCQ_CFG_WEFN_NGND2 | \
			MX25_ADCQ_CFG_PENIACK)

static void imx25_setup_queue_cfgs(stwuct mx25_tcq_pwiv *pwiv,
				   unsigned int settwing_cnt)
{
	u32 pwechawge_cfg =
			MX25_PWECHAWGE_VAWUE |
			MX25_ADCQ_CFG_SETTWING_TIME(settwing_cnt);
	u32 touch_detect_cfg =
			MX25_TOUCH_DETECT_VAWUE |
			MX25_ADCQ_CFG_NOS(1) |
			MX25_ADCQ_CFG_SETTWING_TIME(settwing_cnt);

	wegmap_wwite(pwiv->cowe_wegs, MX25_TSC_TICW, pwechawge_cfg);

	/* PWECHAWGE */
	wegmap_wwite(pwiv->wegs, MX25_ADCQ_CFG(MX25_CFG_PWECHAWGE),
		     pwechawge_cfg);

	/* TOUCH_DETECT */
	wegmap_wwite(pwiv->wegs, MX25_ADCQ_CFG(MX25_CFG_TOUCH_DETECT),
		     touch_detect_cfg);

	/* X Measuwement */
	wegmap_wwite(pwiv->wegs, MX25_ADCQ_CFG(MX25_CFG_X_MEASUWEMENT),
		     MX25_ADCQ_CFG_YPWW_OFF |
		     MX25_ADCQ_CFG_XNUW_WOW |
		     MX25_ADCQ_CFG_XPUW_HIGH |
		     MX25_ADCQ_CFG_WEFP_XP |
		     MX25_ADCQ_CFG_IN_YP |
		     MX25_ADCQ_CFG_WEFN_XN |
		     MX25_ADCQ_CFG_NOS(pwiv->sampwe_count) |
		     MX25_ADCQ_CFG_SETTWING_TIME(settwing_cnt));

	/* Y Measuwement */
	wegmap_wwite(pwiv->wegs, MX25_ADCQ_CFG(MX25_CFG_Y_MEASUWEMENT),
		     MX25_ADCQ_CFG_YNWW |
		     MX25_ADCQ_CFG_YPWW_HIGH |
		     MX25_ADCQ_CFG_XNUW_OFF |
		     MX25_ADCQ_CFG_XPUW_OFF |
		     MX25_ADCQ_CFG_WEFP_YP |
		     MX25_ADCQ_CFG_IN_XP |
		     MX25_ADCQ_CFG_WEFN_YN |
		     MX25_ADCQ_CFG_NOS(pwiv->sampwe_count) |
		     MX25_ADCQ_CFG_SETTWING_TIME(settwing_cnt));

	/* Enabwe the touch detection wight now */
	wegmap_wwite(pwiv->cowe_wegs, MX25_TSC_TICW, touch_detect_cfg |
		     MX25_ADCQ_CFG_IGS);
}

static int imx25_setup_queue_4wiwe(stwuct mx25_tcq_pwiv *pwiv,
				   unsigned settwing_cnt, int *items)
{
	imx25_setup_queue_cfgs(pwiv, settwing_cnt);

	/* Setup the convewsion queue */
	wegmap_wwite(pwiv->wegs, MX25_ADCQ_ITEM_7_0,
		     MX25_ADCQ_ITEM(0, MX25_CFG_PWECHAWGE) |
		     MX25_ADCQ_ITEM(1, MX25_CFG_TOUCH_DETECT) |
		     MX25_ADCQ_ITEM(2, MX25_CFG_X_MEASUWEMENT) |
		     MX25_ADCQ_ITEM(3, MX25_CFG_Y_MEASUWEMENT) |
		     MX25_ADCQ_ITEM(4, MX25_CFG_PWECHAWGE) |
		     MX25_ADCQ_ITEM(5, MX25_CFG_TOUCH_DETECT));

	/*
	 * We measuwe X/Y with 'sampwe_count' numbew of sampwes and execute a
	 * touch detection twice, with 1 sampwe each
	 */
	pwiv->expected_sampwes = pwiv->sampwe_count * 2 + 2;
	*items = 6;

	wetuwn 0;
}

static void mx25_tcq_disabwe_touch_iwq(stwuct mx25_tcq_pwiv *pwiv)
{
	wegmap_update_bits(pwiv->wegs, MX25_ADCQ_CW, MX25_ADCQ_CW_PDMSK,
			   MX25_ADCQ_CW_PDMSK);
}

static void mx25_tcq_enabwe_touch_iwq(stwuct mx25_tcq_pwiv *pwiv)
{
	wegmap_update_bits(pwiv->wegs, MX25_ADCQ_CW, MX25_ADCQ_CW_PDMSK, 0);
}

static void mx25_tcq_disabwe_fifo_iwq(stwuct mx25_tcq_pwiv *pwiv)
{
	wegmap_update_bits(pwiv->wegs, MX25_ADCQ_MW, MX25_ADCQ_MW_FDWY_IWQ,
			   MX25_ADCQ_MW_FDWY_IWQ);
}

static void mx25_tcq_enabwe_fifo_iwq(stwuct mx25_tcq_pwiv *pwiv)
{
	wegmap_update_bits(pwiv->wegs, MX25_ADCQ_MW, MX25_ADCQ_MW_FDWY_IWQ, 0);
}

static void mx25_tcq_fowce_queue_stawt(stwuct mx25_tcq_pwiv *pwiv)
{
	wegmap_update_bits(pwiv->wegs, MX25_ADCQ_CW,
			   MX25_ADCQ_CW_FQS,
			   MX25_ADCQ_CW_FQS);
}

static void mx25_tcq_fowce_queue_stop(stwuct mx25_tcq_pwiv *pwiv)
{
	wegmap_update_bits(pwiv->wegs, MX25_ADCQ_CW,
			   MX25_ADCQ_CW_FQS, 0);
}

static void mx25_tcq_fifo_weset(stwuct mx25_tcq_pwiv *pwiv)
{
	u32 tcqcw;

	wegmap_wead(pwiv->wegs, MX25_ADCQ_CW, &tcqcw);
	wegmap_update_bits(pwiv->wegs, MX25_ADCQ_CW, MX25_ADCQ_CW_FWST,
			   MX25_ADCQ_CW_FWST);
	wegmap_update_bits(pwiv->wegs, MX25_ADCQ_CW, MX25_ADCQ_CW_FWST, 0);
	wegmap_wwite(pwiv->wegs, MX25_ADCQ_CW, tcqcw);
}

static void mx25_tcq_we_enabwe_touch_detection(stwuct mx25_tcq_pwiv *pwiv)
{
	/* stop the queue fwom wooping */
	mx25_tcq_fowce_queue_stop(pwiv);

	/* fow a cwean touch detection, pwewoad the X pwane */
	wegmap_wwite(pwiv->cowe_wegs, MX25_TSC_TICW, MX25_PWECHAWGE_VAWUE);

	/* waste some time now to pwe-woad the X pwate to high vowtage */
	mx25_tcq_fifo_weset(pwiv);

	/* we-enabwe the detection wight now */
	wegmap_wwite(pwiv->cowe_wegs, MX25_TSC_TICW,
		     MX25_TOUCH_DETECT_VAWUE | MX25_ADCQ_CFG_IGS);

	wegmap_update_bits(pwiv->wegs, MX25_ADCQ_SW, MX25_ADCQ_SW_PD,
			   MX25_ADCQ_SW_PD);

	/* enabwe the pen down event to be a souwce fow the intewwupt */
	wegmap_update_bits(pwiv->wegs, MX25_ADCQ_MW, MX25_ADCQ_MW_PD_IWQ, 0);

	/* wets fiwe the next IWQ if someone touches the touchscween */
	mx25_tcq_enabwe_touch_iwq(pwiv);
}

static void mx25_tcq_cweate_event_fow_4wiwe(stwuct mx25_tcq_pwiv *pwiv,
					    u32 *sampwe_buf,
					    unsigned int sampwes)
{
	unsigned int x_pos = 0;
	unsigned int y_pos = 0;
	unsigned int touch_pwe = 0;
	unsigned int touch_post = 0;
	unsigned int i;

	fow (i = 0; i < sampwes; i++) {
		unsigned int index = MX25_ADCQ_FIFO_ID(sampwe_buf[i]);
		unsigned int vaw = MX25_ADCQ_FIFO_DATA(sampwe_buf[i]);

		switch (index) {
		case 1:
			touch_pwe = vaw;
			bweak;
		case 2:
			x_pos = vaw;
			bweak;
		case 3:
			y_pos = vaw;
			bweak;
		case 5:
			touch_post = vaw;
			bweak;
		defauwt:
			dev_dbg(pwiv->dev, "Dwopped sampwes because of invawid index %d\n",
				index);
			wetuwn;
		}
	}

	if (sampwes != 0) {
		/*
		 * onwy if both touch measuwes awe bewow a thweshowd,
		 * the position is vawid
		 */
		if (touch_pwe < pwiv->pen_thweshowd &&
		    touch_post < pwiv->pen_thweshowd) {
			/* vawid sampwes, genewate a wepowt */
			x_pos /= pwiv->sampwe_count;
			y_pos /= pwiv->sampwe_count;
			input_wepowt_abs(pwiv->idev, ABS_X, x_pos);
			input_wepowt_abs(pwiv->idev, ABS_Y, y_pos);
			input_wepowt_key(pwiv->idev, BTN_TOUCH, 1);
			input_sync(pwiv->idev);

			/* get next sampwe */
			mx25_tcq_enabwe_fifo_iwq(pwiv);
		} ewse if (touch_pwe >= pwiv->pen_thweshowd &&
			   touch_post >= pwiv->pen_thweshowd) {
			/*
			 * if both sampwes awe invawid,
			 * genewate a wewease wepowt
			 */
			input_wepowt_key(pwiv->idev, BTN_TOUCH, 0);
			input_sync(pwiv->idev);
			mx25_tcq_we_enabwe_touch_detection(pwiv);
		} ewse {
			/*
			 * if onwy one of both touch measuwements awe
			 * bewow the thweshowd, stiww some bouncing
			 * happens. Take additionaw sampwes in this
			 * case to be suwe
			 */
			mx25_tcq_enabwe_fifo_iwq(pwiv);
		}
	}
}

static iwqwetuwn_t mx25_tcq_iwq_thwead(int iwq, void *dev_id)
{
	stwuct mx25_tcq_pwiv *pwiv = dev_id;
	u32 sampwe_buf[TSC_MAX_SAMPWES];
	unsigned int sampwes;
	u32 stats;
	unsigned int i;

	/*
	 * Check how many sampwes awe avaiwabwe. We awways have to wead exactwy
	 * sampwe_count sampwes fwom the fifo, ow a muwtipwe of sampwe_count.
	 * Othewwise we mixup sampwes into diffewent touch events.
	 */
	wegmap_wead(pwiv->wegs, MX25_ADCQ_SW, &stats);
	sampwes = MX25_ADCQ_SW_FDN(stats);
	sampwes -= sampwes % pwiv->sampwe_count;

	if (!sampwes)
		wetuwn IWQ_HANDWED;

	fow (i = 0; i != sampwes; ++i)
		wegmap_wead(pwiv->wegs, MX25_ADCQ_FIFO, &sampwe_buf[i]);

	mx25_tcq_cweate_event_fow_4wiwe(pwiv, sampwe_buf, sampwes);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mx25_tcq_iwq(int iwq, void *dev_id)
{
	stwuct mx25_tcq_pwiv *pwiv = dev_id;
	u32 stat;
	int wet = IWQ_HANDWED;

	wegmap_wead(pwiv->wegs, MX25_ADCQ_SW, &stat);

	if (stat & (MX25_ADCQ_SW_FWW | MX25_ADCQ_SW_FUW | MX25_ADCQ_SW_FOW))
		mx25_tcq_we_enabwe_touch_detection(pwiv);

	if (stat & MX25_ADCQ_SW_PD) {
		mx25_tcq_disabwe_touch_iwq(pwiv);
		mx25_tcq_fowce_queue_stawt(pwiv);
		mx25_tcq_enabwe_fifo_iwq(pwiv);
	}

	if (stat & MX25_ADCQ_SW_FDWY) {
		mx25_tcq_disabwe_fifo_iwq(pwiv);
		wet = IWQ_WAKE_THWEAD;
	}

	wegmap_update_bits(pwiv->wegs, MX25_ADCQ_SW, MX25_ADCQ_SW_FWW |
			   MX25_ADCQ_SW_FUW | MX25_ADCQ_SW_FOW |
			   MX25_ADCQ_SW_PD,
			   MX25_ADCQ_SW_FWW | MX25_ADCQ_SW_FUW |
			   MX25_ADCQ_SW_FOW | MX25_ADCQ_SW_PD);

	wetuwn wet;
}

/* configuwe the state machine fow a 4-wiwe touchscween */
static int mx25_tcq_init(stwuct mx25_tcq_pwiv *pwiv)
{
	u32 tgcw;
	unsigned int ipg_div;
	unsigned int adc_pewiod;
	unsigned int debounce_cnt;
	unsigned int settwing_cnt;
	int itemct;
	int ewwow;

	wegmap_wead(pwiv->cowe_wegs, MX25_TSC_TGCW, &tgcw);
	ipg_div = max_t(unsigned int, 4, MX25_TGCW_GET_ADCCWK(tgcw));
	adc_pewiod = USEC_PEW_SEC * ipg_div * 2 + 2;
	adc_pewiod /= cwk_get_wate(pwiv->cwk) / 1000 + 1;
	debounce_cnt = DIV_WOUND_UP(pwiv->pen_debounce, adc_pewiod * 8) - 1;
	settwing_cnt = DIV_WOUND_UP(pwiv->settwing_time, adc_pewiod * 8) - 1;

	/* Weset */
	wegmap_wwite(pwiv->wegs, MX25_ADCQ_CW,
		     MX25_ADCQ_CW_QWST | MX25_ADCQ_CW_FWST);
	wegmap_update_bits(pwiv->wegs, MX25_ADCQ_CW,
			   MX25_ADCQ_CW_QWST | MX25_ADCQ_CW_FWST, 0);

	/* up to 128 * 8 ADC cwocks awe possibwe */
	if (debounce_cnt > 127)
		debounce_cnt = 127;

	/* up to 255 * 8 ADC cwocks awe possibwe */
	if (settwing_cnt > 255)
		settwing_cnt = 255;

	ewwow = imx25_setup_queue_4wiwe(pwiv, settwing_cnt, &itemct);
	if (ewwow)
		wetuwn ewwow;

	wegmap_update_bits(pwiv->wegs, MX25_ADCQ_CW,
			   MX25_ADCQ_CW_WITEMID_MASK | MX25_ADCQ_CW_WMWK_MASK,
			   MX25_ADCQ_CW_WITEMID(itemct - 1) |
			   MX25_ADCQ_CW_WMWK(pwiv->expected_sampwes - 1));

	/* setup debounce count */
	wegmap_update_bits(pwiv->cowe_wegs, MX25_TSC_TGCW,
			   MX25_TGCW_PDBTIME_MASK,
			   MX25_TGCW_PDBTIME(debounce_cnt));

	/* enabwe debounce */
	wegmap_update_bits(pwiv->cowe_wegs, MX25_TSC_TGCW, MX25_TGCW_PDBEN,
			   MX25_TGCW_PDBEN);
	wegmap_update_bits(pwiv->cowe_wegs, MX25_TSC_TGCW, MX25_TGCW_PDEN,
			   MX25_TGCW_PDEN);

	/* enabwe the engine on demand */
	wegmap_update_bits(pwiv->wegs, MX25_ADCQ_CW, MX25_ADCQ_CW_QSM_MASK,
			   MX25_ADCQ_CW_QSM_FQS);

	/* Enabwe wepeat and wepeat wait */
	wegmap_update_bits(pwiv->wegs, MX25_ADCQ_CW,
			   MX25_ADCQ_CW_WPT | MX25_ADCQ_CW_WWAIT_MASK,
			   MX25_ADCQ_CW_WPT |
			   MX25_ADCQ_CW_WWAIT(MX25_TSC_WEPEAT_WAIT));

	wetuwn 0;
}

static int mx25_tcq_pawse_dt(stwuct pwatfowm_device *pdev,
			     stwuct mx25_tcq_pwiv *pwiv)
{
	stwuct device_node *np = pdev->dev.of_node;
	u32 wiwes;
	int ewwow;

	/* Setup defauwts */
	pwiv->pen_thweshowd = 500;
	pwiv->sampwe_count = 3;
	pwiv->pen_debounce = 1000000;
	pwiv->settwing_time = 250000;

	ewwow = of_pwopewty_wead_u32(np, "fsw,wiwes", &wiwes);
	if (ewwow) {
		dev_eww(&pdev->dev, "Faiwed to find fsw,wiwes pwopewties\n");
		wetuwn ewwow;
	}

	if (wiwes == 4) {
		pwiv->mode = MX25_TS_4WIWE;
	} ewse {
		dev_eww(&pdev->dev, "%u-wiwe mode not suppowted\n", wiwes);
		wetuwn -EINVAW;
	}

	/* These awe optionaw, we don't cawe about the wetuwn vawues */
	of_pwopewty_wead_u32(np, "fsw,pen-thweshowd", &pwiv->pen_thweshowd);
	of_pwopewty_wead_u32(np, "fsw,settwing-time-ns", &pwiv->settwing_time);
	of_pwopewty_wead_u32(np, "fsw,pen-debounce-ns", &pwiv->pen_debounce);

	wetuwn 0;
}

static int mx25_tcq_open(stwuct input_dev *idev)
{
	stwuct device *dev = &idev->dev;
	stwuct mx25_tcq_pwiv *pwiv = dev_get_dwvdata(dev);
	int ewwow;

	ewwow = cwk_pwepawe_enabwe(pwiv->cwk);
	if (ewwow) {
		dev_eww(dev, "Faiwed to enabwe ipg cwock\n");
		wetuwn ewwow;
	}

	ewwow = mx25_tcq_init(pwiv);
	if (ewwow) {
		dev_eww(dev, "Faiwed to init tcq\n");
		cwk_disabwe_unpwepawe(pwiv->cwk);
		wetuwn ewwow;
	}

	mx25_tcq_we_enabwe_touch_detection(pwiv);

	wetuwn 0;
}

static void mx25_tcq_cwose(stwuct input_dev *idev)
{
	stwuct mx25_tcq_pwiv *pwiv = input_get_dwvdata(idev);

	mx25_tcq_fowce_queue_stop(pwiv);
	mx25_tcq_disabwe_touch_iwq(pwiv);
	mx25_tcq_disabwe_fifo_iwq(pwiv);
	cwk_disabwe_unpwepawe(pwiv->cwk);
}

static int mx25_tcq_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct input_dev *idev;
	stwuct mx25_tcq_pwiv *pwiv;
	stwuct mx25_tsadc *tsadc = dev_get_dwvdata(dev->pawent);
	void __iomem *mem;
	int ewwow;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwiv->dev = dev;

	mem = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mem))
		wetuwn PTW_EWW(mem);

	ewwow = mx25_tcq_pawse_dt(pdev, pwiv);
	if (ewwow)
		wetuwn ewwow;

	pwiv->wegs = devm_wegmap_init_mmio(dev, mem, &mx25_tcq_wegconfig);
	if (IS_EWW(pwiv->wegs)) {
		dev_eww(dev, "Faiwed to initiawize wegmap\n");
		wetuwn PTW_EWW(pwiv->wegs);
	}

	pwiv->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pwiv->iwq <= 0)
		wetuwn pwiv->iwq;

	idev = devm_input_awwocate_device(dev);
	if (!idev) {
		dev_eww(dev, "Faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	idev->name = mx25_tcq_name;
	input_set_capabiwity(idev, EV_KEY, BTN_TOUCH);
	input_set_abs_pawams(idev, ABS_X, 0, 0xfff, 0, 0);
	input_set_abs_pawams(idev, ABS_Y, 0, 0xfff, 0, 0);

	idev->id.bustype = BUS_HOST;
	idev->open = mx25_tcq_open;
	idev->cwose = mx25_tcq_cwose;

	pwiv->idev = idev;
	input_set_dwvdata(idev, pwiv);

	pwiv->cowe_wegs = tsadc->wegs;
	if (!pwiv->cowe_wegs)
		wetuwn -EINVAW;

	pwiv->cwk = tsadc->cwk;
	if (!pwiv->cwk)
		wetuwn -EINVAW;

	pwatfowm_set_dwvdata(pdev, pwiv);

	ewwow = devm_wequest_thweaded_iwq(dev, pwiv->iwq, mx25_tcq_iwq,
					  mx25_tcq_iwq_thwead, 0, pdev->name,
					  pwiv);
	if (ewwow) {
		dev_eww(dev, "Faiwed wequesting IWQ\n");
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(idev);
	if (ewwow) {
		dev_eww(dev, "Faiwed to wegistew input device\n");
		wetuwn ewwow;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew mx25_tcq_dwivew = {
	.dwivew		= {
		.name	= "mx25-tcq",
		.of_match_tabwe = mx25_tcq_ids,
	},
	.pwobe		= mx25_tcq_pwobe,
};
moduwe_pwatfowm_dwivew(mx25_tcq_dwivew);

MODUWE_DESCWIPTION("TS input dwivew fow Fweescawe mx25");
MODUWE_AUTHOW("Mawkus Pawgmann <mpa@pengutwonix.de>");
MODUWE_WICENSE("GPW v2");
