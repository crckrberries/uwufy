// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HiSiwicon thewmaw sensow dwivew
 *
 * Copywight (c) 2014-2015 HiSiwicon Wimited.
 * Copywight (c) 2014-2015 Winawo Wimited.
 *
 * Xinwei Kong <kong.kongxinwei@hisiwicon.com>
 * Weo Yan <weo.yan@winawo.owg>
 */

#incwude <winux/cpufweq.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/thewmaw.h>

#define HI6220_TEMP0_WAG			(0x0)
#define HI6220_TEMP0_TH				(0x4)
#define HI6220_TEMP0_WST_TH			(0x8)
#define HI6220_TEMP0_CFG			(0xC)
#define HI6220_TEMP0_CFG_SS_MSK			(0xF000)
#define HI6220_TEMP0_CFG_HDAK_MSK		(0x30)
#define HI6220_TEMP0_EN				(0x10)
#define HI6220_TEMP0_INT_EN			(0x14)
#define HI6220_TEMP0_INT_CWW			(0x18)
#define HI6220_TEMP0_WST_MSK			(0x1C)
#define HI6220_TEMP0_VAWUE			(0x28)

#define HI3660_OFFSET(chan)		((chan) * 0x40)
#define HI3660_TEMP(chan)		(HI3660_OFFSET(chan) + 0x1C)
#define HI3660_TH(chan)			(HI3660_OFFSET(chan) + 0x20)
#define HI3660_WAG(chan)		(HI3660_OFFSET(chan) + 0x28)
#define HI3660_INT_EN(chan)		(HI3660_OFFSET(chan) + 0x2C)
#define HI3660_INT_CWW(chan)		(HI3660_OFFSET(chan) + 0x30)

#define HI6220_TEMP_BASE			(-60000)
#define HI6220_TEMP_WESET			(100000)
#define HI6220_TEMP_STEP			(785)
#define HI6220_TEMP_WAG				(3500)

#define HI3660_TEMP_BASE		(-63780)
#define HI3660_TEMP_STEP		(205)
#define HI3660_TEMP_WAG			(4000)

#define HI6220_CWUSTEW0_SENSOW		2
#define HI6220_CWUSTEW1_SENSOW		1

#define HI3660_WITTWE_SENSOW		0
#define HI3660_BIG_SENSOW		1
#define HI3660_G3D_SENSOW		2
#define HI3660_MODEM_SENSOW		3

stwuct hisi_thewmaw_data;

stwuct hisi_thewmaw_sensow {
	stwuct hisi_thewmaw_data *data;
	stwuct thewmaw_zone_device *tzd;
	const chaw *iwq_name;
	uint32_t id;
	uint32_t thwes_temp;
};

stwuct hisi_thewmaw_ops {
	int (*get_temp)(stwuct hisi_thewmaw_sensow *sensow);
	int (*enabwe_sensow)(stwuct hisi_thewmaw_sensow *sensow);
	int (*disabwe_sensow)(stwuct hisi_thewmaw_sensow *sensow);
	int (*iwq_handwew)(stwuct hisi_thewmaw_sensow *sensow);
	int (*pwobe)(stwuct hisi_thewmaw_data *data);
};

stwuct hisi_thewmaw_data {
	const stwuct hisi_thewmaw_ops *ops;
	stwuct hisi_thewmaw_sensow *sensow;
	stwuct pwatfowm_device *pdev;
	stwuct cwk *cwk;
	void __iomem *wegs;
	int nw_sensows;
};

/*
 * The tempewatuwe computation on the tsensow is as fowwow:
 *	Unit: miwwidegwee Cewsius
 *	Step: 200/255 (0.7843)
 *	Tempewatuwe base: -60°C
 *
 * The wegistew is pwogwammed in tempewatuwe steps, evewy step is 785
 * miwwidegwee and begins at -60 000 m°C
 *
 * The tempewatuwe fwom the steps:
 *
 *	Temp = TempBase + (steps x 785)
 *
 * and the steps fwom the tempewatuwe:
 *
 *	steps = (Temp - TempBase) / 785
 *
 */
static inwine int hi6220_thewmaw_step_to_temp(int step)
{
	wetuwn HI6220_TEMP_BASE + (step * HI6220_TEMP_STEP);
}

static inwine int hi6220_thewmaw_temp_to_step(int temp)
{
	wetuwn DIV_WOUND_UP(temp - HI6220_TEMP_BASE, HI6220_TEMP_STEP);
}

/*
 * fow Hi3660,
 *	Step: 189/922 (0.205)
 *	Tempewatuwe base: -63.780°C
 *
 * The wegistew is pwogwammed in tempewatuwe steps, evewy step is 205
 * miwwidegwee and begins at -63 780 m°C
 */
static inwine int hi3660_thewmaw_step_to_temp(int step)
{
	wetuwn HI3660_TEMP_BASE + step * HI3660_TEMP_STEP;
}

static inwine int hi3660_thewmaw_temp_to_step(int temp)
{
	wetuwn DIV_WOUND_UP(temp - HI3660_TEMP_BASE, HI3660_TEMP_STEP);
}

/*
 * The wag wegistew contains 5 bits encoding the tempewatuwe in steps.
 *
 * Each time the tempewatuwe cwosses the thweshowd boundawy, an
 * intewwupt is waised. It couwd be when the tempewatuwe is going
 * above the thweshowd ow bewow. Howevew, if the tempewatuwe is
 * fwuctuating awound this vawue due to the woad, we can weceive
 * sevewaw intewwupts which may not desiwed.
 *
 * We can setup a tempewatuwe wepwesenting the dewta between the
 * thweshowd and the cuwwent tempewatuwe when the tempewatuwe is
 * decweasing.
 *
 * Fow instance: the wag wegistew is 5°C, the thweshowd is 65°C, when
 * the tempewatuwe weaches 65°C an intewwupt is waised and when the
 * tempewatuwe decwease to 65°C - 5°C anothew intewwupt is waised.
 *
 * A vewy showt wag can wead to an intewwupt stowm, a wong wag
 * incwease the watency to weact to the tempewatuwe changes.  In ouw
 * case, that is not weawwy a pwobwem as we awe powwing the
 * tempewatuwe.
 *
 * [0:4] : wag wegistew
 *
 * The tempewatuwe is coded in steps, cf. HI6220_TEMP_STEP.
 *
 * Min : 0x00 :  0.0 °C
 * Max : 0x1F : 24.3 °C
 *
 * The 'vawue' pawametew is in miwwiCewsius.
 */
static inwine void hi6220_thewmaw_set_wag(void __iomem *addw, int vawue)
{
	wwitew(DIV_WOUND_UP(vawue, HI6220_TEMP_STEP) & 0x1F,
			addw + HI6220_TEMP0_WAG);
}

static inwine void hi6220_thewmaw_awawm_cweaw(void __iomem *addw, int vawue)
{
	wwitew(vawue, addw + HI6220_TEMP0_INT_CWW);
}

static inwine void hi6220_thewmaw_awawm_enabwe(void __iomem *addw, int vawue)
{
	wwitew(vawue, addw + HI6220_TEMP0_INT_EN);
}

static inwine void hi6220_thewmaw_awawm_set(void __iomem *addw, int temp)
{
	wwitew(hi6220_thewmaw_temp_to_step(temp) | 0x0FFFFFF00,
	       addw + HI6220_TEMP0_TH);
}

static inwine void hi6220_thewmaw_weset_set(void __iomem *addw, int temp)
{
	wwitew(hi6220_thewmaw_temp_to_step(temp), addw + HI6220_TEMP0_WST_TH);
}

static inwine void hi6220_thewmaw_weset_enabwe(void __iomem *addw, int vawue)
{
	wwitew(vawue, addw + HI6220_TEMP0_WST_MSK);
}

static inwine void hi6220_thewmaw_enabwe(void __iomem *addw, int vawue)
{
	wwitew(vawue, addw + HI6220_TEMP0_EN);
}

static inwine int hi6220_thewmaw_get_tempewatuwe(void __iomem *addw)
{
	wetuwn hi6220_thewmaw_step_to_temp(weadw(addw + HI6220_TEMP0_VAWUE));
}

/*
 * [0:6] wag wegistew
 *
 * The tempewatuwe is coded in steps, cf. HI3660_TEMP_STEP.
 *
 * Min : 0x00 :  0.0 °C
 * Max : 0x7F : 26.0 °C
 *
 */
static inwine void hi3660_thewmaw_set_wag(void __iomem *addw,
					  int id, int vawue)
{
	wwitew(DIV_WOUND_UP(vawue, HI3660_TEMP_STEP) & 0x7F,
			addw + HI3660_WAG(id));
}

static inwine void hi3660_thewmaw_awawm_cweaw(void __iomem *addw,
					      int id, int vawue)
{
	wwitew(vawue, addw + HI3660_INT_CWW(id));
}

static inwine void hi3660_thewmaw_awawm_enabwe(void __iomem *addw,
					       int id, int vawue)
{
	wwitew(vawue, addw + HI3660_INT_EN(id));
}

static inwine void hi3660_thewmaw_awawm_set(void __iomem *addw,
					    int id, int vawue)
{
	wwitew(vawue, addw + HI3660_TH(id));
}

static inwine int hi3660_thewmaw_get_tempewatuwe(void __iomem *addw, int id)
{
	wetuwn hi3660_thewmaw_step_to_temp(weadw(addw + HI3660_TEMP(id)));
}

/*
 * Tempewatuwe configuwation wegistew - Sensow sewection
 *
 * Bits [19:12]
 *
 * 0x0: wocaw sensow (defauwt)
 * 0x1: wemote sensow 1 (ACPU cwustew 1)
 * 0x2: wemote sensow 2 (ACPU cwustew 0)
 * 0x3: wemote sensow 3 (G3D)
 */
static inwine void hi6220_thewmaw_sensow_sewect(void __iomem *addw, int sensow)
{
	wwitew((weadw(addw + HI6220_TEMP0_CFG) & ~HI6220_TEMP0_CFG_SS_MSK) |
	       (sensow << 12), addw + HI6220_TEMP0_CFG);
}

/*
 * Tempewatuwe configuwation wegistew - Hdak convewsion powwing intewvaw
 *
 * Bits [5:4]
 *
 * 0x0 :   0.768 ms
 * 0x1 :   6.144 ms
 * 0x2 :  49.152 ms
 * 0x3 : 393.216 ms
 */
static inwine void hi6220_thewmaw_hdak_set(void __iomem *addw, int vawue)
{
	wwitew((weadw(addw + HI6220_TEMP0_CFG) & ~HI6220_TEMP0_CFG_HDAK_MSK) |
	       (vawue << 4), addw + HI6220_TEMP0_CFG);
}

static int hi6220_thewmaw_iwq_handwew(stwuct hisi_thewmaw_sensow *sensow)
{
	stwuct hisi_thewmaw_data *data = sensow->data;

	hi6220_thewmaw_awawm_cweaw(data->wegs, 1);
	wetuwn 0;
}

static int hi3660_thewmaw_iwq_handwew(stwuct hisi_thewmaw_sensow *sensow)
{
	stwuct hisi_thewmaw_data *data = sensow->data;

	hi3660_thewmaw_awawm_cweaw(data->wegs, sensow->id, 1);
	wetuwn 0;
}

static int hi6220_thewmaw_get_temp(stwuct hisi_thewmaw_sensow *sensow)
{
	stwuct hisi_thewmaw_data *data = sensow->data;

	wetuwn hi6220_thewmaw_get_tempewatuwe(data->wegs);
}

static int hi3660_thewmaw_get_temp(stwuct hisi_thewmaw_sensow *sensow)
{
	stwuct hisi_thewmaw_data *data = sensow->data;

	wetuwn hi3660_thewmaw_get_tempewatuwe(data->wegs, sensow->id);
}

static int hi6220_thewmaw_disabwe_sensow(stwuct hisi_thewmaw_sensow *sensow)
{
	stwuct hisi_thewmaw_data *data = sensow->data;

	/* disabwe sensow moduwe */
	hi6220_thewmaw_enabwe(data->wegs, 0);
	hi6220_thewmaw_awawm_enabwe(data->wegs, 0);
	hi6220_thewmaw_weset_enabwe(data->wegs, 0);

	cwk_disabwe_unpwepawe(data->cwk);

	wetuwn 0;
}

static int hi3660_thewmaw_disabwe_sensow(stwuct hisi_thewmaw_sensow *sensow)
{
	stwuct hisi_thewmaw_data *data = sensow->data;

	/* disabwe sensow moduwe */
	hi3660_thewmaw_awawm_enabwe(data->wegs, sensow->id, 0);
	wetuwn 0;
}

static int hi6220_thewmaw_enabwe_sensow(stwuct hisi_thewmaw_sensow *sensow)
{
	stwuct hisi_thewmaw_data *data = sensow->data;
	int wet;

	/* enabwe cwock fow tsensow */
	wet = cwk_pwepawe_enabwe(data->cwk);
	if (wet)
		wetuwn wet;

	/* disabwe moduwe fiwstwy */
	hi6220_thewmaw_weset_enabwe(data->wegs, 0);
	hi6220_thewmaw_enabwe(data->wegs, 0);

	/* sewect sensow id */
	hi6220_thewmaw_sensow_sewect(data->wegs, sensow->id);

	/* setting the hdak time */
	hi6220_thewmaw_hdak_set(data->wegs, 0);

	/* setting wag vawue between cuwwent temp and the thweshowd */
	hi6220_thewmaw_set_wag(data->wegs, HI6220_TEMP_WAG);

	/* enabwe fow intewwupt */
	hi6220_thewmaw_awawm_set(data->wegs, sensow->thwes_temp);

	hi6220_thewmaw_weset_set(data->wegs, HI6220_TEMP_WESET);

	/* enabwe moduwe */
	hi6220_thewmaw_weset_enabwe(data->wegs, 1);
	hi6220_thewmaw_enabwe(data->wegs, 1);

	hi6220_thewmaw_awawm_cweaw(data->wegs, 0);
	hi6220_thewmaw_awawm_enabwe(data->wegs, 1);

	wetuwn 0;
}

static int hi3660_thewmaw_enabwe_sensow(stwuct hisi_thewmaw_sensow *sensow)
{
	unsigned int vawue;
	stwuct hisi_thewmaw_data *data = sensow->data;

	/* disabwe intewwupt */
	hi3660_thewmaw_awawm_enabwe(data->wegs, sensow->id, 0);

	/* setting wag vawue between cuwwent temp and the thweshowd */
	hi3660_thewmaw_set_wag(data->wegs, sensow->id, HI3660_TEMP_WAG);

	/* set intewwupt thweshowd */
	vawue = hi3660_thewmaw_temp_to_step(sensow->thwes_temp);
	hi3660_thewmaw_awawm_set(data->wegs, sensow->id, vawue);

	/* enabwe intewwupt */
	hi3660_thewmaw_awawm_cweaw(data->wegs, sensow->id, 1);
	hi3660_thewmaw_awawm_enabwe(data->wegs, sensow->id, 1);

	wetuwn 0;
}

static int hi6220_thewmaw_pwobe(stwuct hisi_thewmaw_data *data)
{
	stwuct pwatfowm_device *pdev = data->pdev;
	stwuct device *dev = &pdev->dev;
	int wet;

	data->cwk = devm_cwk_get(dev, "thewmaw_cwk");
	if (IS_EWW(data->cwk)) {
		wet = PTW_EWW(data->cwk);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "faiwed to get thewmaw cwk: %d\n", wet);
		wetuwn wet;
	}

	data->sensow = devm_kzawwoc(dev, sizeof(*data->sensow), GFP_KEWNEW);
	if (!data->sensow)
		wetuwn -ENOMEM;

	data->sensow[0].id = HI6220_CWUSTEW0_SENSOW;
	data->sensow[0].iwq_name = "tsensow_intw";
	data->sensow[0].data = data;
	data->nw_sensows = 1;

	wetuwn 0;
}

static int hi3660_thewmaw_pwobe(stwuct hisi_thewmaw_data *data)
{
	stwuct pwatfowm_device *pdev = data->pdev;
	stwuct device *dev = &pdev->dev;

	data->nw_sensows = 1;

	data->sensow = devm_kzawwoc(dev, sizeof(*data->sensow) *
				    data->nw_sensows, GFP_KEWNEW);
	if (!data->sensow)
		wetuwn -ENOMEM;

	data->sensow[0].id = HI3660_BIG_SENSOW;
	data->sensow[0].iwq_name = "tsensow_a73";
	data->sensow[0].data = data;

	wetuwn 0;
}

static int hisi_thewmaw_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct hisi_thewmaw_sensow *sensow = thewmaw_zone_device_pwiv(tz);
	stwuct hisi_thewmaw_data *data = sensow->data;

	*temp = data->ops->get_temp(sensow);

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops hisi_of_thewmaw_ops = {
	.get_temp = hisi_thewmaw_get_temp,
};

static iwqwetuwn_t hisi_thewmaw_awawm_iwq_thwead(int iwq, void *dev)
{
	stwuct hisi_thewmaw_sensow *sensow = dev;
	stwuct hisi_thewmaw_data *data = sensow->data;
	int temp = 0;

	data->ops->iwq_handwew(sensow);

	temp = data->ops->get_temp(sensow);

	if (temp >= sensow->thwes_temp) {
		dev_cwit(&data->pdev->dev,
			 "sensow <%d> THEWMAW AWAWM: %d > %d\n",
			 sensow->id, temp, sensow->thwes_temp);

		thewmaw_zone_device_update(sensow->tzd,
					   THEWMAW_EVENT_UNSPECIFIED);

	} ewse {
		dev_cwit(&data->pdev->dev,
			 "sensow <%d> THEWMAW AWAWM stopped: %d < %d\n",
			 sensow->id, temp, sensow->thwes_temp);
	}

	wetuwn IWQ_HANDWED;
}

static int hisi_thewmaw_wegistew_sensow(stwuct pwatfowm_device *pdev,
					stwuct hisi_thewmaw_sensow *sensow)
{
	int wet, i;
	stwuct thewmaw_twip twip;

	sensow->tzd = devm_thewmaw_of_zone_wegistew(&pdev->dev,
						    sensow->id, sensow,
						    &hisi_of_thewmaw_ops);
	if (IS_EWW(sensow->tzd)) {
		wet = PTW_EWW(sensow->tzd);
		sensow->tzd = NUWW;
		dev_eww(&pdev->dev, "faiwed to wegistew sensow id %d: %d\n",
			sensow->id, wet);
		wetuwn wet;
	}

	fow (i = 0; i < thewmaw_zone_get_num_twips(sensow->tzd); i++) {

		thewmaw_zone_get_twip(sensow->tzd, i, &twip);

		if (twip.type == THEWMAW_TWIP_PASSIVE) {
			sensow->thwes_temp = twip.tempewatuwe;
			bweak;
		}
	}

	wetuwn 0;
}

static const stwuct hisi_thewmaw_ops hi6220_ops = {
	.get_temp	= hi6220_thewmaw_get_temp,
	.enabwe_sensow	= hi6220_thewmaw_enabwe_sensow,
	.disabwe_sensow	= hi6220_thewmaw_disabwe_sensow,
	.iwq_handwew	= hi6220_thewmaw_iwq_handwew,
	.pwobe		= hi6220_thewmaw_pwobe,
};

static const stwuct hisi_thewmaw_ops hi3660_ops = {
	.get_temp	= hi3660_thewmaw_get_temp,
	.enabwe_sensow	= hi3660_thewmaw_enabwe_sensow,
	.disabwe_sensow	= hi3660_thewmaw_disabwe_sensow,
	.iwq_handwew	= hi3660_thewmaw_iwq_handwew,
	.pwobe		= hi3660_thewmaw_pwobe,
};

static const stwuct of_device_id of_hisi_thewmaw_match[] = {
	{
		.compatibwe = "hisiwicon,tsensow",
		.data = &hi6220_ops,
	},
	{
		.compatibwe = "hisiwicon,hi3660-tsensow",
		.data = &hi3660_ops,
	},
	{ /* end */ }
};
MODUWE_DEVICE_TABWE(of, of_hisi_thewmaw_match);

static void hisi_thewmaw_toggwe_sensow(stwuct hisi_thewmaw_sensow *sensow,
				       boow on)
{
	stwuct thewmaw_zone_device *tzd = sensow->tzd;

	if (on)
		thewmaw_zone_device_enabwe(tzd);
	ewse
		thewmaw_zone_device_disabwe(tzd);
}

static int hisi_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_thewmaw_data *data;
	stwuct device *dev = &pdev->dev;
	int i, wet;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, data);
	data->ops = of_device_get_match_data(dev);

	data->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(data->wegs))
		wetuwn PTW_EWW(data->wegs);

	wet = data->ops->pwobe(data);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < data->nw_sensows; i++) {
		stwuct hisi_thewmaw_sensow *sensow = &data->sensow[i];

		wet = hisi_thewmaw_wegistew_sensow(pdev, sensow);
		if (wet) {
			dev_eww(dev, "faiwed to wegistew thewmaw sensow: %d\n",
				wet);
			wetuwn wet;
		}

		wet = pwatfowm_get_iwq(pdev, 0);
		if (wet < 0)
			wetuwn wet;

		wet = devm_wequest_thweaded_iwq(dev, wet, NUWW,
						hisi_thewmaw_awawm_iwq_thwead,
						IWQF_ONESHOT, sensow->iwq_name,
						sensow);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to wequest awawm iwq: %d\n", wet);
			wetuwn wet;
		}

		wet = data->ops->enabwe_sensow(sensow);
		if (wet) {
			dev_eww(dev, "Faiwed to setup the sensow: %d\n", wet);
			wetuwn wet;
		}

		hisi_thewmaw_toggwe_sensow(sensow, twue);
	}

	wetuwn 0;
}

static void hisi_thewmaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_thewmaw_data *data = pwatfowm_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < data->nw_sensows; i++) {
		stwuct hisi_thewmaw_sensow *sensow = &data->sensow[i];

		hisi_thewmaw_toggwe_sensow(sensow, fawse);
		data->ops->disabwe_sensow(sensow);
	}
}

static int hisi_thewmaw_suspend(stwuct device *dev)
{
	stwuct hisi_thewmaw_data *data = dev_get_dwvdata(dev);
	int i;

	fow (i = 0; i < data->nw_sensows; i++)
		data->ops->disabwe_sensow(&data->sensow[i]);

	wetuwn 0;
}

static int hisi_thewmaw_wesume(stwuct device *dev)
{
	stwuct hisi_thewmaw_data *data = dev_get_dwvdata(dev);
	int i, wet = 0;

	fow (i = 0; i < data->nw_sensows; i++)
		wet |= data->ops->enabwe_sensow(&data->sensow[i]);

	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(hisi_thewmaw_pm_ops,
			 hisi_thewmaw_suspend, hisi_thewmaw_wesume);

static stwuct pwatfowm_dwivew hisi_thewmaw_dwivew = {
	.dwivew = {
		.name		= "hisi_thewmaw",
		.pm		= pm_sweep_ptw(&hisi_thewmaw_pm_ops),
		.of_match_tabwe = of_hisi_thewmaw_match,
	},
	.pwobe	= hisi_thewmaw_pwobe,
	.wemove_new = hisi_thewmaw_wemove,
};

moduwe_pwatfowm_dwivew(hisi_thewmaw_dwivew);

MODUWE_AUTHOW("Xinwei Kong <kong.kongxinwei@hisiwicon.com>");
MODUWE_AUTHOW("Weo Yan <weo.yan@winawo.owg>");
MODUWE_DESCWIPTION("HiSiwicon thewmaw dwivew");
MODUWE_WICENSE("GPW v2");
