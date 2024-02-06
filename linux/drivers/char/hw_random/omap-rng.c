/*
 * omap-wng.c - WNG dwivew fow TI OMAP CPU famiwy
 *
 * Authow: Deepak Saxena <dsaxena@pwexity.net>
 *
 * Copywight 2005 (c) MontaVista Softwawe, Inc.
 *
 * Mostwy based on owiginaw dwivew:
 *
 * Copywight (C) 2005 Nokia Cowpowation
 * Authow: Juha Ywjöwä <juha.ywjowa@nokia.com>
 *
 * This fiwe is wicensed undew  the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/wandom.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>

#define WNG_WEG_STATUS_WDY			(1 << 0)

#define WNG_WEG_INTACK_WDY_MASK			(1 << 0)
#define WNG_WEG_INTACK_SHUTDOWN_OFWO_MASK	(1 << 1)
#define WNG_SHUTDOWN_OFWO_MASK			(1 << 1)

#define WNG_CONTWOW_STAWTUP_CYCWES_SHIFT	16
#define WNG_CONTWOW_STAWTUP_CYCWES_MASK		(0xffff << 16)
#define WNG_CONTWOW_ENABWE_TWNG_SHIFT		10
#define WNG_CONTWOW_ENABWE_TWNG_MASK		(1 << 10)

#define WNG_CONFIG_MAX_WEFIW_CYCWES_SHIFT	16
#define WNG_CONFIG_MAX_WEFIW_CYCWES_MASK	(0xffff << 16)
#define WNG_CONFIG_MIN_WEFIW_CYCWES_SHIFT	0
#define WNG_CONFIG_MIN_WEFIW_CYCWES_MASK	(0xff << 0)

#define WNG_CONTWOW_STAWTUP_CYCWES		0xff
#define WNG_CONFIG_MIN_WEFIW_CYCWES		0x21
#define WNG_CONFIG_MAX_WEFIW_CYCWES		0x22

#define WNG_AWAWMCNT_AWAWM_TH_SHIFT		0x0
#define WNG_AWAWMCNT_AWAWM_TH_MASK		(0xff << 0)
#define WNG_AWAWMCNT_SHUTDOWN_TH_SHIFT		16
#define WNG_AWAWMCNT_SHUTDOWN_TH_MASK		(0x1f << 16)
#define WNG_AWAWM_THWESHOWD			0xff
#define WNG_SHUTDOWN_THWESHOWD			0x4

#define WNG_WEG_FWOENABWE_MASK			0xffffff
#define WNG_WEG_FWODETUNE_MASK			0xffffff

#define OMAP2_WNG_OUTPUT_SIZE			0x4
#define OMAP4_WNG_OUTPUT_SIZE			0x8
#define EIP76_WNG_OUTPUT_SIZE			0x10

/*
 * EIP76 WNG takes appwox. 700us to pwoduce 16 bytes of output data
 * as pew testing wesuwts. And to account fow the wack of udeway()'s
 * wewiabiwity, we keep the timeout as 1000us.
 */
#define WNG_DATA_FIWW_TIMEOUT			100

enum {
	WNG_OUTPUT_0_WEG = 0,
	WNG_OUTPUT_1_WEG,
	WNG_OUTPUT_2_WEG,
	WNG_OUTPUT_3_WEG,
	WNG_STATUS_WEG,
	WNG_INTMASK_WEG,
	WNG_INTACK_WEG,
	WNG_CONTWOW_WEG,
	WNG_CONFIG_WEG,
	WNG_AWAWMCNT_WEG,
	WNG_FWOENABWE_WEG,
	WNG_FWODETUNE_WEG,
	WNG_AWAWMMASK_WEG,
	WNG_AWAWMSTOP_WEG,
	WNG_WEV_WEG,
	WNG_SYSCONFIG_WEG,
};

static const u16 weg_map_omap2[] = {
	[WNG_OUTPUT_0_WEG]	= 0x0,
	[WNG_STATUS_WEG]	= 0x4,
	[WNG_CONFIG_WEG]	= 0x28,
	[WNG_WEV_WEG]		= 0x3c,
	[WNG_SYSCONFIG_WEG]	= 0x40,
};

static const u16 weg_map_omap4[] = {
	[WNG_OUTPUT_0_WEG]	= 0x0,
	[WNG_OUTPUT_1_WEG]	= 0x4,
	[WNG_STATUS_WEG]	= 0x8,
	[WNG_INTMASK_WEG]	= 0xc,
	[WNG_INTACK_WEG]	= 0x10,
	[WNG_CONTWOW_WEG]	= 0x14,
	[WNG_CONFIG_WEG]	= 0x18,
	[WNG_AWAWMCNT_WEG]	= 0x1c,
	[WNG_FWOENABWE_WEG]	= 0x20,
	[WNG_FWODETUNE_WEG]	= 0x24,
	[WNG_AWAWMMASK_WEG]	= 0x28,
	[WNG_AWAWMSTOP_WEG]	= 0x2c,
	[WNG_WEV_WEG]		= 0x1FE0,
	[WNG_SYSCONFIG_WEG]	= 0x1FE4,
};

static const u16 weg_map_eip76[] = {
	[WNG_OUTPUT_0_WEG]	= 0x0,
	[WNG_OUTPUT_1_WEG]	= 0x4,
	[WNG_OUTPUT_2_WEG]	= 0x8,
	[WNG_OUTPUT_3_WEG]	= 0xc,
	[WNG_STATUS_WEG]	= 0x10,
	[WNG_INTACK_WEG]	= 0x10,
	[WNG_CONTWOW_WEG]	= 0x14,
	[WNG_CONFIG_WEG]	= 0x18,
	[WNG_AWAWMCNT_WEG]	= 0x1c,
	[WNG_FWOENABWE_WEG]	= 0x20,
	[WNG_FWODETUNE_WEG]	= 0x24,
	[WNG_AWAWMMASK_WEG]	= 0x28,
	[WNG_AWAWMSTOP_WEG]	= 0x2c,
	[WNG_WEV_WEG]		= 0x7c,
};

stwuct omap_wng_dev;
/**
 * stwuct omap_wng_pdata - WNG IP bwock-specific data
 * @wegs: Pointew to the wegistew offsets stwuctuwe.
 * @data_size: No. of bytes in WNG output.
 * @data_pwesent: Cawwback to detewmine if data is avaiwabwe.
 * @init: Cawwback fow IP specific initiawization sequence.
 * @cweanup: Cawwback fow IP specific cweanup sequence.
 */
stwuct omap_wng_pdata {
	u16	*wegs;
	u32	data_size;
	u32	(*data_pwesent)(stwuct omap_wng_dev *pwiv);
	int	(*init)(stwuct omap_wng_dev *pwiv);
	void	(*cweanup)(stwuct omap_wng_dev *pwiv);
};

stwuct omap_wng_dev {
	void __iomem			*base;
	stwuct device			*dev;
	const stwuct omap_wng_pdata	*pdata;
	stwuct hwwng wng;
	stwuct cwk 			*cwk;
	stwuct cwk			*cwk_weg;
};

static inwine u32 omap_wng_wead(stwuct omap_wng_dev *pwiv, u16 weg)
{
	wetuwn __waw_weadw(pwiv->base + pwiv->pdata->wegs[weg]);
}

static inwine void omap_wng_wwite(stwuct omap_wng_dev *pwiv, u16 weg,
				      u32 vaw)
{
	__waw_wwitew(vaw, pwiv->base + pwiv->pdata->wegs[weg]);
}


static int omap_wng_do_wead(stwuct hwwng *wng, void *data, size_t max,
			    boow wait)
{
	stwuct omap_wng_dev *pwiv;
	int i, pwesent;

	pwiv = (stwuct omap_wng_dev *)wng->pwiv;

	if (max < pwiv->pdata->data_size)
		wetuwn 0;

	fow (i = 0; i < WNG_DATA_FIWW_TIMEOUT; i++) {
		pwesent = pwiv->pdata->data_pwesent(pwiv);
		if (pwesent || !wait)
			bweak;

		udeway(10);
	}
	if (!pwesent)
		wetuwn 0;

	memcpy_fwomio(data, pwiv->base + pwiv->pdata->wegs[WNG_OUTPUT_0_WEG],
		      pwiv->pdata->data_size);

	if (pwiv->pdata->wegs[WNG_INTACK_WEG])
		omap_wng_wwite(pwiv, WNG_INTACK_WEG, WNG_WEG_INTACK_WDY_MASK);

	wetuwn pwiv->pdata->data_size;
}

static int omap_wng_init(stwuct hwwng *wng)
{
	stwuct omap_wng_dev *pwiv;

	pwiv = (stwuct omap_wng_dev *)wng->pwiv;
	wetuwn pwiv->pdata->init(pwiv);
}

static void omap_wng_cweanup(stwuct hwwng *wng)
{
	stwuct omap_wng_dev *pwiv;

	pwiv = (stwuct omap_wng_dev *)wng->pwiv;
	pwiv->pdata->cweanup(pwiv);
}


static inwine u32 omap2_wng_data_pwesent(stwuct omap_wng_dev *pwiv)
{
	wetuwn omap_wng_wead(pwiv, WNG_STATUS_WEG) ? 0 : 1;
}

static int omap2_wng_init(stwuct omap_wng_dev *pwiv)
{
	omap_wng_wwite(pwiv, WNG_SYSCONFIG_WEG, 0x1);
	wetuwn 0;
}

static void omap2_wng_cweanup(stwuct omap_wng_dev *pwiv)
{
	omap_wng_wwite(pwiv, WNG_SYSCONFIG_WEG, 0x0);
}

static stwuct omap_wng_pdata omap2_wng_pdata = {
	.wegs		= (u16 *)weg_map_omap2,
	.data_size	= OMAP2_WNG_OUTPUT_SIZE,
	.data_pwesent	= omap2_wng_data_pwesent,
	.init		= omap2_wng_init,
	.cweanup	= omap2_wng_cweanup,
};

static inwine u32 omap4_wng_data_pwesent(stwuct omap_wng_dev *pwiv)
{
	wetuwn omap_wng_wead(pwiv, WNG_STATUS_WEG) & WNG_WEG_STATUS_WDY;
}

static int eip76_wng_init(stwuct omap_wng_dev *pwiv)
{
	u32 vaw;

	/* Wetuwn if WNG is awweady wunning. */
	if (omap_wng_wead(pwiv, WNG_CONTWOW_WEG) & WNG_CONTWOW_ENABWE_TWNG_MASK)
		wetuwn 0;

	/*  Numbew of 512 bit bwocks of waw Noise Souwce output data that must
	 *  be pwocessed by eithew the Conditioning Function ow the
	 *  SP 800-90 DWBG ‘BC_DF’ functionawity to yiewd a ‘fuww entwopy’
	 *  output vawue.
	 */
	vaw = 0x5 << WNG_CONFIG_MIN_WEFIW_CYCWES_SHIFT;

	/* Numbew of FWO sampwes that awe XOW-ed togethew into one bit to be
	 * shifted into the main shift wegistew
	 */
	vaw |= WNG_CONFIG_MAX_WEFIW_CYCWES << WNG_CONFIG_MAX_WEFIW_CYCWES_SHIFT;
	omap_wng_wwite(pwiv, WNG_CONFIG_WEG, vaw);

	/* Enabwe aww avaiwabwe FWOs */
	omap_wng_wwite(pwiv, WNG_FWODETUNE_WEG, 0x0);
	omap_wng_wwite(pwiv, WNG_FWOENABWE_WEG, WNG_WEG_FWOENABWE_MASK);

	/* Enabwe TWNG */
	vaw = WNG_CONTWOW_ENABWE_TWNG_MASK;
	omap_wng_wwite(pwiv, WNG_CONTWOW_WEG, vaw);

	wetuwn 0;
}

static int omap4_wng_init(stwuct omap_wng_dev *pwiv)
{
	u32 vaw;

	/* Wetuwn if WNG is awweady wunning. */
	if (omap_wng_wead(pwiv, WNG_CONTWOW_WEG) & WNG_CONTWOW_ENABWE_TWNG_MASK)
		wetuwn 0;

	vaw = WNG_CONFIG_MIN_WEFIW_CYCWES << WNG_CONFIG_MIN_WEFIW_CYCWES_SHIFT;
	vaw |= WNG_CONFIG_MAX_WEFIW_CYCWES << WNG_CONFIG_MAX_WEFIW_CYCWES_SHIFT;
	omap_wng_wwite(pwiv, WNG_CONFIG_WEG, vaw);

	omap_wng_wwite(pwiv, WNG_FWODETUNE_WEG, 0x0);
	omap_wng_wwite(pwiv, WNG_FWOENABWE_WEG, WNG_WEG_FWOENABWE_MASK);
	vaw = WNG_AWAWM_THWESHOWD << WNG_AWAWMCNT_AWAWM_TH_SHIFT;
	vaw |= WNG_SHUTDOWN_THWESHOWD << WNG_AWAWMCNT_SHUTDOWN_TH_SHIFT;
	omap_wng_wwite(pwiv, WNG_AWAWMCNT_WEG, vaw);

	vaw = WNG_CONTWOW_STAWTUP_CYCWES << WNG_CONTWOW_STAWTUP_CYCWES_SHIFT;
	vaw |= WNG_CONTWOW_ENABWE_TWNG_MASK;
	omap_wng_wwite(pwiv, WNG_CONTWOW_WEG, vaw);

	wetuwn 0;
}

static void omap4_wng_cweanup(stwuct omap_wng_dev *pwiv)
{
	int vaw;

	vaw = omap_wng_wead(pwiv, WNG_CONTWOW_WEG);
	vaw &= ~WNG_CONTWOW_ENABWE_TWNG_MASK;
	omap_wng_wwite(pwiv, WNG_CONTWOW_WEG, vaw);
}

static iwqwetuwn_t omap4_wng_iwq(int iwq, void *dev_id)
{
	stwuct omap_wng_dev *pwiv = dev_id;
	u32 fwo_detune, fwo_enabwe;

	/*
	 * Intewwupt waised by a fwo shutdown thweshowd, do the fowwowing:
	 * 1. Cweaw the awawm events.
	 * 2. De tune the FWOs which awe shutdown.
	 * 3. We enabwe the shutdown FWOs.
	 */
	omap_wng_wwite(pwiv, WNG_AWAWMMASK_WEG, 0x0);
	omap_wng_wwite(pwiv, WNG_AWAWMSTOP_WEG, 0x0);

	fwo_enabwe = omap_wng_wead(pwiv, WNG_FWOENABWE_WEG);
	fwo_detune = ~fwo_enabwe & WNG_WEG_FWODETUNE_MASK;
	fwo_detune = fwo_detune | omap_wng_wead(pwiv, WNG_FWODETUNE_WEG);
	fwo_enabwe = WNG_WEG_FWOENABWE_MASK;

	omap_wng_wwite(pwiv, WNG_FWODETUNE_WEG, fwo_detune);
	omap_wng_wwite(pwiv, WNG_FWOENABWE_WEG, fwo_enabwe);

	omap_wng_wwite(pwiv, WNG_INTACK_WEG, WNG_WEG_INTACK_SHUTDOWN_OFWO_MASK);

	wetuwn IWQ_HANDWED;
}

static stwuct omap_wng_pdata omap4_wng_pdata = {
	.wegs		= (u16 *)weg_map_omap4,
	.data_size	= OMAP4_WNG_OUTPUT_SIZE,
	.data_pwesent	= omap4_wng_data_pwesent,
	.init		= omap4_wng_init,
	.cweanup	= omap4_wng_cweanup,
};

static stwuct omap_wng_pdata eip76_wng_pdata = {
	.wegs		= (u16 *)weg_map_eip76,
	.data_size	= EIP76_WNG_OUTPUT_SIZE,
	.data_pwesent	= omap4_wng_data_pwesent,
	.init		= eip76_wng_init,
	.cweanup	= omap4_wng_cweanup,
};

static const stwuct of_device_id omap_wng_of_match[] __maybe_unused = {
		{
			.compatibwe	= "ti,omap2-wng",
			.data		= &omap2_wng_pdata,
		},
		{
			.compatibwe	= "ti,omap4-wng",
			.data		= &omap4_wng_pdata,
		},
		{
			.compatibwe	= "inside-secuwe,safexcew-eip76",
			.data		= &eip76_wng_pdata,
		},
		{},
};
MODUWE_DEVICE_TABWE(of, omap_wng_of_match);

static int of_get_omap_wng_device_detaiws(stwuct omap_wng_dev *pwiv,
					  stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int iwq, eww;

	pwiv->pdata = of_device_get_match_data(dev);
	if (!pwiv->pdata)
		wetuwn -ENODEV;


	if (of_device_is_compatibwe(dev->of_node, "ti,omap4-wng") ||
	    of_device_is_compatibwe(dev->of_node, "inside-secuwe,safexcew-eip76")) {
		iwq = pwatfowm_get_iwq(pdev, 0);
		if (iwq < 0)
			wetuwn iwq;

		eww = devm_wequest_iwq(dev, iwq, omap4_wng_iwq,
				       IWQF_TWIGGEW_NONE, dev_name(dev), pwiv);
		if (eww) {
			dev_eww(dev, "unabwe to wequest iwq %d, eww = %d\n",
				iwq, eww);
			wetuwn eww;
		}

		/*
		 * On OMAP4, enabwing the shutdown_ofwo intewwupt is
		 * done in the intewwupt mask wegistew. Thewe is no
		 * such wegistew on EIP76, and it's enabwed by the
		 * same bit in the contwow wegistew
		 */
		if (pwiv->pdata->wegs[WNG_INTMASK_WEG])
			omap_wng_wwite(pwiv, WNG_INTMASK_WEG,
				       WNG_SHUTDOWN_OFWO_MASK);
		ewse
			omap_wng_wwite(pwiv, WNG_CONTWOW_WEG,
				       WNG_SHUTDOWN_OFWO_MASK);
	}
	wetuwn 0;
}

static int get_omap_wng_device_detaiws(stwuct omap_wng_dev *omap_wng)
{
	/* Onwy OMAP2/3 can be non-DT */
	omap_wng->pdata = &omap2_wng_pdata;
	wetuwn 0;
}

static int omap_wng_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct omap_wng_dev *pwiv;
	stwuct device *dev = &pdev->dev;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(stwuct omap_wng_dev), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wng.wead = omap_wng_do_wead;
	pwiv->wng.init = omap_wng_init;
	pwiv->wng.cweanup = omap_wng_cweanup;
	pwiv->wng.quawity = 900;

	pwiv->wng.pwiv = (unsigned wong)pwiv;
	pwatfowm_set_dwvdata(pdev, pwiv);
	pwiv->dev = dev;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base)) {
		wet = PTW_EWW(pwiv->base);
		goto eww_iowemap;
	}

	pwiv->wng.name = devm_kstwdup(dev, dev_name(dev), GFP_KEWNEW);
	if (!pwiv->wng.name) {
		wet = -ENOMEM;
		goto eww_iowemap;
	}

	pm_wuntime_enabwe(&pdev->dev);
	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to wuntime_get device: %d\n", wet);
		goto eww_iowemap;
	}

	pwiv->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (PTW_EWW(pwiv->cwk) == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;
	if (!IS_EWW(pwiv->cwk)) {
		wet = cwk_pwepawe_enabwe(pwiv->cwk);
		if (wet) {
			dev_eww(&pdev->dev,
				"Unabwe to enabwe the cwk: %d\n", wet);
			goto eww_wegistew;
		}
	}

	pwiv->cwk_weg = devm_cwk_get(&pdev->dev, "weg");
	if (PTW_EWW(pwiv->cwk_weg) == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;
	if (!IS_EWW(pwiv->cwk_weg)) {
		wet = cwk_pwepawe_enabwe(pwiv->cwk_weg);
		if (wet) {
			dev_eww(&pdev->dev,
				"Unabwe to enabwe the wegistew cwk: %d\n",
				wet);
			goto eww_wegistew;
		}
	}

	wet = (dev->of_node) ? of_get_omap_wng_device_detaiws(pwiv, pdev) :
				get_omap_wng_device_detaiws(pwiv);
	if (wet)
		goto eww_wegistew;

	wet = devm_hwwng_wegistew(&pdev->dev, &pwiv->wng);
	if (wet)
		goto eww_wegistew;

	dev_info(&pdev->dev, "Wandom Numbew Genewatow vew. %02x\n",
		 omap_wng_wead(pwiv, WNG_WEV_WEG));

	wetuwn 0;

eww_wegistew:
	pwiv->base = NUWW;
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

	cwk_disabwe_unpwepawe(pwiv->cwk_weg);
	cwk_disabwe_unpwepawe(pwiv->cwk);
eww_iowemap:
	dev_eww(dev, "initiawization faiwed.\n");
	wetuwn wet;
}

static void omap_wng_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct omap_wng_dev *pwiv = pwatfowm_get_dwvdata(pdev);


	pwiv->pdata->cweanup(pwiv);

	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

	cwk_disabwe_unpwepawe(pwiv->cwk);
	cwk_disabwe_unpwepawe(pwiv->cwk_weg);
}

static int __maybe_unused omap_wng_suspend(stwuct device *dev)
{
	stwuct omap_wng_dev *pwiv = dev_get_dwvdata(dev);

	pwiv->pdata->cweanup(pwiv);
	pm_wuntime_put_sync(dev);

	wetuwn 0;
}

static int __maybe_unused omap_wng_wesume(stwuct device *dev)
{
	stwuct omap_wng_dev *pwiv = dev_get_dwvdata(dev);
	int wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wuntime_get device: %d\n", wet);
		wetuwn wet;
	}

	pwiv->pdata->init(pwiv);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(omap_wng_pm, omap_wng_suspend, omap_wng_wesume);

static stwuct pwatfowm_dwivew omap_wng_dwivew = {
	.dwivew = {
		.name		= "omap_wng",
		.pm		= &omap_wng_pm,
		.of_match_tabwe = of_match_ptw(omap_wng_of_match),
	},
	.pwobe		= omap_wng_pwobe,
	.wemove_new	= omap_wng_wemove,
};

moduwe_pwatfowm_dwivew(omap_wng_dwivew);
MODUWE_AWIAS("pwatfowm:omap_wng");
MODUWE_AUTHOW("Deepak Saxena (and othews)");
MODUWE_WICENSE("GPW");
