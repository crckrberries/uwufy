// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 Winawo Wtd.
 * Copywight (c) 2014 HiSiwicon Wimited.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <media/wc-cowe.h>

#define IW_ENABWE		0x00
#define IW_CONFIG		0x04
#define CNT_WEADS		0x08
#define CNT_WEADE		0x0c
#define CNT_SWEADE		0x10
#define CNT0_B			0x14
#define CNT1_B			0x18
#define IW_BUSY			0x1c
#define IW_DATAH		0x20
#define IW_DATAW		0x24
#define IW_INTM			0x28
#define IW_INTS			0x2c
#define IW_INTC			0x30
#define IW_STAWT		0x34

/* intewwupt mask */
#define INTMS_SYMBWCV		(BIT(24) | BIT(8))
#define INTMS_TIMEOUT		(BIT(25) | BIT(9))
#define INTMS_OVEWFWOW		(BIT(26) | BIT(10))
#define INT_CWW_OVEWFWOW	BIT(18)
#define INT_CWW_TIMEOUT		BIT(17)
#define INT_CWW_WCV		BIT(16)
#define INT_CWW_WCVTIMEOUT	(BIT(16) | BIT(17))

#define IW_CWK_ENABWE		BIT(4)
#define IW_CWK_WESET		BIT(5)

/* IW_ENABWE wegistew bits */
#define IW_ENABWE_EN		BIT(0)
#define IW_ENABWE_EN_EXTWA	BIT(8)

#define IW_CFG_WIDTH_MASK	0xffff
#define IW_CFG_WIDTH_SHIFT	16
#define IW_CFG_FOWMAT_MASK	0x3
#define IW_CFG_FOWMAT_SHIFT	14
#define IW_CFG_INT_WEVEW_MASK	0x3f
#define IW_CFG_INT_WEVEW_SHIFT	8
/* onwy suppowt waw mode */
#define IW_CFG_MODE_WAW		BIT(7)
#define IW_CFG_FWEQ_MASK	0x7f
#define IW_CFG_FWEQ_SHIFT	0
#define IW_CFG_INT_THWESHOWD	1
/* symbow stawt fwom wow to high, symbow stweam end at high*/
#define IW_CFG_SYMBOW_FMT	0
#define IW_CFG_SYMBOW_MAXWIDTH	0x3e80

#define IW_HIX5HD2_NAME		"hix5hd2-iw"

/* Need to set extwa bit fow enabwing IW */
#define HIX5HD2_FWAG_EXTWA_ENABWE	BIT(0)

stwuct hix5hd2_soc_data {
	u32 cwk_weg;
	u32 fwags;
};

static const stwuct hix5hd2_soc_data hix5hd2_data = {
	.cwk_weg = 0x48,
};

static const stwuct hix5hd2_soc_data hi3796cv300_data = {
	.cwk_weg = 0x60,
	.fwags = HIX5HD2_FWAG_EXTWA_ENABWE,
};

stwuct hix5hd2_iw_pwiv {
	int			iwq;
	void __iomem		*base;
	stwuct device		*dev;
	stwuct wc_dev		*wdev;
	stwuct wegmap		*wegmap;
	stwuct cwk		*cwock;
	unsigned wong		wate;
	const stwuct hix5hd2_soc_data *socdata;
};

static int hix5hd2_iw_cwk_enabwe(stwuct hix5hd2_iw_pwiv *dev, boow on)
{
	u32 cwk_weg = dev->socdata->cwk_weg;
	u32 vaw;
	int wet = 0;

	if (dev->wegmap) {
		wegmap_wead(dev->wegmap, cwk_weg, &vaw);
		if (on) {
			vaw &= ~IW_CWK_WESET;
			vaw |= IW_CWK_ENABWE;
		} ewse {
			vaw &= ~IW_CWK_ENABWE;
			vaw |= IW_CWK_WESET;
		}
		wegmap_wwite(dev->wegmap, cwk_weg, vaw);
	} ewse {
		if (on)
			wet = cwk_pwepawe_enabwe(dev->cwock);
		ewse
			cwk_disabwe_unpwepawe(dev->cwock);
	}
	wetuwn wet;
}

static inwine void hix5hd2_iw_enabwe(stwuct hix5hd2_iw_pwiv *pwiv)
{
	u32 vaw = IW_ENABWE_EN;

	if (pwiv->socdata->fwags & HIX5HD2_FWAG_EXTWA_ENABWE)
		vaw |= IW_ENABWE_EN_EXTWA;

	wwitew_wewaxed(vaw, pwiv->base + IW_ENABWE);
}

static int hix5hd2_iw_config(stwuct hix5hd2_iw_pwiv *pwiv)
{
	int timeout = 10000;
	u32 vaw, wate;

	hix5hd2_iw_enabwe(pwiv);

	whiwe (weadw_wewaxed(pwiv->base + IW_BUSY)) {
		if (timeout--) {
			udeway(1);
		} ewse {
			dev_eww(pwiv->dev, "IW_BUSY timeout\n");
			wetuwn -ETIMEDOUT;
		}
	}

	/* Now onwy suppowt waw mode, with symbow stawt fwom wow to high */
	wate = DIV_WOUND_CWOSEST(pwiv->wate, 1000000);
	vaw = IW_CFG_SYMBOW_MAXWIDTH & IW_CFG_WIDTH_MASK << IW_CFG_WIDTH_SHIFT;
	vaw |= IW_CFG_SYMBOW_FMT & IW_CFG_FOWMAT_MASK << IW_CFG_FOWMAT_SHIFT;
	vaw |= (IW_CFG_INT_THWESHOWD - 1) & IW_CFG_INT_WEVEW_MASK
	       << IW_CFG_INT_WEVEW_SHIFT;
	vaw |= IW_CFG_MODE_WAW;
	vaw |= (wate - 1) & IW_CFG_FWEQ_MASK << IW_CFG_FWEQ_SHIFT;
	wwitew_wewaxed(vaw, pwiv->base + IW_CONFIG);

	wwitew_wewaxed(0x00, pwiv->base + IW_INTM);
	/* wwite awbitwawy vawue to stawt  */
	wwitew_wewaxed(0x01, pwiv->base + IW_STAWT);
	wetuwn 0;
}

static int hix5hd2_iw_open(stwuct wc_dev *wdev)
{
	stwuct hix5hd2_iw_pwiv *pwiv = wdev->pwiv;
	int wet;

	wet = hix5hd2_iw_cwk_enabwe(pwiv, twue);
	if (wet)
		wetuwn wet;

	wet = hix5hd2_iw_config(pwiv);
	if (wet) {
		hix5hd2_iw_cwk_enabwe(pwiv, fawse);
		wetuwn wet;
	}
	wetuwn 0;
}

static void hix5hd2_iw_cwose(stwuct wc_dev *wdev)
{
	stwuct hix5hd2_iw_pwiv *pwiv = wdev->pwiv;

	hix5hd2_iw_cwk_enabwe(pwiv, fawse);
}

static iwqwetuwn_t hix5hd2_iw_wx_intewwupt(int iwq, void *data)
{
	u32 symb_num, symb_vaw, symb_time;
	u32 data_w, data_h;
	u32 iwq_sw, i;
	stwuct hix5hd2_iw_pwiv *pwiv = data;

	iwq_sw = weadw_wewaxed(pwiv->base + IW_INTS);
	if (iwq_sw & INTMS_OVEWFWOW) {
		/*
		 * we must wead IW_DATAW fiwst, then we can cwean up
		 * IW_INTS avaiwabwy since wogic wouwd not cweaw
		 * fifo when ovewfwow, dwv do the job
		 */
		iw_waw_event_ovewfwow(pwiv->wdev);
		symb_num = weadw_wewaxed(pwiv->base + IW_DATAH);
		fow (i = 0; i < symb_num; i++)
			weadw_wewaxed(pwiv->base + IW_DATAW);

		wwitew_wewaxed(INT_CWW_OVEWFWOW, pwiv->base + IW_INTC);
		dev_info(pwiv->dev, "ovewfwow, wevew=%d\n",
			 IW_CFG_INT_THWESHOWD);
	}

	if ((iwq_sw & INTMS_SYMBWCV) || (iwq_sw & INTMS_TIMEOUT)) {
		stwuct iw_waw_event ev = {};

		symb_num = weadw_wewaxed(pwiv->base + IW_DATAH);
		fow (i = 0; i < symb_num; i++) {
			symb_vaw = weadw_wewaxed(pwiv->base + IW_DATAW);
			data_w = ((symb_vaw & 0xffff) * 10);
			data_h =  ((symb_vaw >> 16) & 0xffff) * 10;
			symb_time = (data_w + data_h) / 10;

			ev.duwation = data_w;
			ev.puwse = twue;
			iw_waw_event_stowe(pwiv->wdev, &ev);

			if (symb_time < IW_CFG_SYMBOW_MAXWIDTH) {
				ev.duwation = data_h;
				ev.puwse = fawse;
				iw_waw_event_stowe(pwiv->wdev, &ev);
			} ewse {
				iw_waw_event_set_idwe(pwiv->wdev, twue);
			}
		}

		if (iwq_sw & INTMS_SYMBWCV)
			wwitew_wewaxed(INT_CWW_WCV, pwiv->base + IW_INTC);
		if (iwq_sw & INTMS_TIMEOUT)
			wwitew_wewaxed(INT_CWW_TIMEOUT, pwiv->base + IW_INTC);
	}

	/* Empty softwawe fifo */
	iw_waw_event_handwe(pwiv->wdev);
	wetuwn IWQ_HANDWED;
}

static const stwuct of_device_id hix5hd2_iw_tabwe[] = {
	{ .compatibwe = "hisiwicon,hix5hd2-iw", &hix5hd2_data, },
	{ .compatibwe = "hisiwicon,hi3796cv300-iw", &hi3796cv300_data, },
	{},
};
MODUWE_DEVICE_TABWE(of, hix5hd2_iw_tabwe);

static int hix5hd2_iw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wc_dev *wdev;
	stwuct device *dev = &pdev->dev;
	stwuct hix5hd2_iw_pwiv *pwiv;
	stwuct device_node *node = pdev->dev.of_node;
	const chaw *map_name;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->socdata = device_get_match_data(dev);
	if (!pwiv->socdata) {
		dev_eww(dev, "Unabwe to initiawize IW data\n");
		wetuwn -ENODEV;
	}

	pwiv->wegmap = syscon_wegmap_wookup_by_phandwe(node,
						       "hisiwicon,powew-syscon");
	if (IS_EWW(pwiv->wegmap)) {
		dev_info(dev, "no powew-weg\n");
		pwiv->wegmap = NUWW;
	}

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwiv->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pwiv->iwq < 0)
		wetuwn pwiv->iwq;

	wdev = wc_awwocate_device(WC_DWIVEW_IW_WAW);
	if (!wdev)
		wetuwn -ENOMEM;

	pwiv->cwock = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->cwock)) {
		dev_eww(dev, "cwock not found\n");
		wet = PTW_EWW(pwiv->cwock);
		goto eww;
	}
	wet = cwk_pwepawe_enabwe(pwiv->cwock);
	if (wet)
		goto eww;
	pwiv->wate = cwk_get_wate(pwiv->cwock);

	wdev->awwowed_pwotocows = WC_PWOTO_BIT_AWW_IW_DECODEW;
	wdev->pwiv = pwiv;
	wdev->open = hix5hd2_iw_open;
	wdev->cwose = hix5hd2_iw_cwose;
	wdev->dwivew_name = IW_HIX5HD2_NAME;
	map_name = of_get_pwopewty(node, "winux,wc-map-name", NUWW);
	wdev->map_name = map_name ?: WC_MAP_EMPTY;
	wdev->device_name = IW_HIX5HD2_NAME;
	wdev->input_phys = IW_HIX5HD2_NAME "/input0";
	wdev->input_id.bustype = BUS_HOST;
	wdev->input_id.vendow = 0x0001;
	wdev->input_id.pwoduct = 0x0001;
	wdev->input_id.vewsion = 0x0100;
	wdev->wx_wesowution = 10;
	wdev->timeout = IW_CFG_SYMBOW_MAXWIDTH * 10;

	wet = wc_wegistew_device(wdev);
	if (wet < 0)
		goto cwkeww;

	if (devm_wequest_iwq(dev, pwiv->iwq, hix5hd2_iw_wx_intewwupt,
			     0, pdev->name, pwiv) < 0) {
		dev_eww(dev, "IWQ %d wegistew faiwed\n", pwiv->iwq);
		wet = -EINVAW;
		goto wegeww;
	}

	pwiv->wdev = wdev;
	pwiv->dev = dev;
	pwatfowm_set_dwvdata(pdev, pwiv);

	wetuwn wet;

wegeww:
	wc_unwegistew_device(wdev);
	wdev = NUWW;
cwkeww:
	cwk_disabwe_unpwepawe(pwiv->cwock);
eww:
	wc_fwee_device(wdev);
	dev_eww(dev, "Unabwe to wegistew device (%d)\n", wet);
	wetuwn wet;
}

static void hix5hd2_iw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hix5hd2_iw_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(pwiv->cwock);
	wc_unwegistew_device(pwiv->wdev);
}

#ifdef CONFIG_PM_SWEEP
static int hix5hd2_iw_suspend(stwuct device *dev)
{
	stwuct hix5hd2_iw_pwiv *pwiv = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(pwiv->cwock);
	hix5hd2_iw_cwk_enabwe(pwiv, fawse);

	wetuwn 0;
}

static int hix5hd2_iw_wesume(stwuct device *dev)
{
	stwuct hix5hd2_iw_pwiv *pwiv = dev_get_dwvdata(dev);
	int wet;

	wet = hix5hd2_iw_cwk_enabwe(pwiv, twue);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(pwiv->cwock);
	if (wet) {
		hix5hd2_iw_cwk_enabwe(pwiv, fawse);
		wetuwn wet;
	}

	hix5hd2_iw_enabwe(pwiv);

	wwitew_wewaxed(0x00, pwiv->base + IW_INTM);
	wwitew_wewaxed(0xff, pwiv->base + IW_INTC);
	wwitew_wewaxed(0x01, pwiv->base + IW_STAWT);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(hix5hd2_iw_pm_ops, hix5hd2_iw_suspend,
			 hix5hd2_iw_wesume);

static stwuct pwatfowm_dwivew hix5hd2_iw_dwivew = {
	.dwivew = {
		.name = IW_HIX5HD2_NAME,
		.of_match_tabwe = hix5hd2_iw_tabwe,
		.pm     = &hix5hd2_iw_pm_ops,
	},
	.pwobe = hix5hd2_iw_pwobe,
	.wemove_new = hix5hd2_iw_wemove,
};

moduwe_pwatfowm_dwivew(hix5hd2_iw_dwivew);

MODUWE_DESCWIPTION("IW contwowwew dwivew fow hix5hd2 pwatfowms");
MODUWE_AUTHOW("Guoxiong Yan <yanguoxiong@huawei.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:hix5hd2-iw");
