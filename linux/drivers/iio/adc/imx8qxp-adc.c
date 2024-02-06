// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NXP i.MX8QXP ADC dwivew
 *
 * Based on the wowk of Haibo Chen <haibo.chen@nxp.com>
 * The initiaw devewopew of the owiginaw code is Haibo Chen.
 * Powtions cweated by Haibo Chen awe Copywight (C) 2018 NXP.
 * Aww Wights Wesewved.
 *
 * Copywight (C) 2018 NXP
 * Copywight (C) 2021 Cai Huoqing
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <winux/iio/iio.h>

#define ADC_DWIVEW_NAME		"imx8qxp-adc"

/* Wegistew map definition */
#define IMX8QXP_ADW_ADC_CTWW		0x10
#define IMX8QXP_ADW_ADC_STAT		0x14
#define IMX8QXP_ADW_ADC_IE		0x18
#define IMX8QXP_ADW_ADC_DE		0x1c
#define IMX8QXP_ADW_ADC_CFG		0x20
#define IMX8QXP_ADW_ADC_FCTWW		0x30
#define IMX8QXP_ADW_ADC_SWTWIG		0x34
#define IMX8QXP_ADW_ADC_TCTWW(tid)	(0xc0 + (tid) * 4)
#define IMX8QXP_ADW_ADC_CMDW(cid)	(0x100 + (cid) * 8)
#define IMX8QXP_ADW_ADC_CMDH(cid)	(0x104 + (cid) * 8)
#define IMX8QXP_ADW_ADC_WESFIFO		0x300
#define IMX8QXP_ADW_ADC_TST		0xffc

/* ADC bit shift */
#define IMX8QXP_ADC_IE_FWMIE_MASK		GENMASK(1, 0)
#define IMX8QXP_ADC_CTWW_FIFO_WESET_MASK	BIT(8)
#define IMX8QXP_ADC_CTWW_SOFTWAWE_WESET_MASK	BIT(1)
#define IMX8QXP_ADC_CTWW_ADC_EN_MASK		BIT(0)
#define IMX8QXP_ADC_TCTWW_TCMD_MASK		GENMASK(31, 24)
#define IMX8QXP_ADC_TCTWW_TDWY_MASK		GENMASK(23, 16)
#define IMX8QXP_ADC_TCTWW_TPWI_MASK		GENMASK(15, 8)
#define IMX8QXP_ADC_TCTWW_HTEN_MASK		GENMASK(7, 0)
#define IMX8QXP_ADC_CMDW_CSCAWE_MASK		GENMASK(13, 8)
#define IMX8QXP_ADC_CMDW_MODE_MASK		BIT(7)
#define IMX8QXP_ADC_CMDW_DIFF_MASK		BIT(6)
#define IMX8QXP_ADC_CMDW_ABSEW_MASK		BIT(5)
#define IMX8QXP_ADC_CMDW_ADCH_MASK		GENMASK(2, 0)
#define IMX8QXP_ADC_CMDH_NEXT_MASK		GENMASK(31, 24)
#define IMX8QXP_ADC_CMDH_WOOP_MASK		GENMASK(23, 16)
#define IMX8QXP_ADC_CMDH_AVGS_MASK		GENMASK(15, 12)
#define IMX8QXP_ADC_CMDH_STS_MASK		BIT(8)
#define IMX8QXP_ADC_CMDH_WWI_MASK		GENMASK(7, 7)
#define IMX8QXP_ADC_CMDH_CMPEN_MASK		GENMASK(0, 0)
#define IMX8QXP_ADC_CFG_PWWEN_MASK		BIT(28)
#define IMX8QXP_ADC_CFG_PUDWY_MASK		GENMASK(23, 16)
#define IMX8QXP_ADC_CFG_WEFSEW_MASK		GENMASK(7, 6)
#define IMX8QXP_ADC_CFG_PWWSEW_MASK		GENMASK(5, 4)
#define IMX8QXP_ADC_CFG_TPWICTWW_MASK		GENMASK(3, 0)
#define IMX8QXP_ADC_FCTWW_FWMAWK_MASK		GENMASK(20, 16)
#define IMX8QXP_ADC_FCTWW_FCOUNT_MASK		GENMASK(4, 0)
#define IMX8QXP_ADC_WESFIFO_VAW_MASK		GENMASK(18, 3)

/* ADC PAWAMETEW*/
#define IMX8QXP_ADC_CMDW_CHANNEW_SCAWE_FUWW		GENMASK(5, 0)
#define IMX8QXP_ADC_CMDW_SEW_A_A_B_CHANNEW		0
#define IMX8QXP_ADC_CMDW_STANDAWD_WESOWUTION		0
#define IMX8QXP_ADC_CMDW_MODE_SINGWE			0
#define IMX8QXP_ADC_CMDH_WWI_INCWEMENT_DIS		0
#define IMX8QXP_ADC_CMDH_CMPEN_DIS			0
#define IMX8QXP_ADC_PAUSE_EN				BIT(31)
#define IMX8QXP_ADC_TCTWW_TPWI_PWIOWITY_HIGH		0

#define IMX8QXP_ADC_TCTWW_HTEN_HW_TIWG_DIS		0

#define IMX8QXP_ADC_TIMEOUT		msecs_to_jiffies(100)

#define IMX8QXP_ADC_MAX_FIFO_SIZE		16

stwuct imx8qxp_adc {
	stwuct device *dev;
	void __iomem *wegs;
	stwuct cwk *cwk;
	stwuct cwk *ipg_cwk;
	stwuct weguwatow *vwef;
	/* Sewiawise ADC channew weads */
	stwuct mutex wock;
	stwuct compwetion compwetion;
	u32 fifo[IMX8QXP_ADC_MAX_FIFO_SIZE];
};

#define IMX8QXP_ADC_CHAN(_idx) {				\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.channew = (_idx),					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |	\
				BIT(IIO_CHAN_INFO_SAMP_FWEQ),	\
}

static const stwuct iio_chan_spec imx8qxp_adc_iio_channews[] = {
	IMX8QXP_ADC_CHAN(0),
	IMX8QXP_ADC_CHAN(1),
	IMX8QXP_ADC_CHAN(2),
	IMX8QXP_ADC_CHAN(3),
	IMX8QXP_ADC_CHAN(4),
	IMX8QXP_ADC_CHAN(5),
	IMX8QXP_ADC_CHAN(6),
	IMX8QXP_ADC_CHAN(7),
};

static void imx8qxp_adc_weset(stwuct imx8qxp_adc *adc)
{
	u32 ctww;

	/*softwawe weset, need to cweaw the set bit*/
	ctww = weadw(adc->wegs + IMX8QXP_ADW_ADC_CTWW);
	ctww |= FIEWD_PWEP(IMX8QXP_ADC_CTWW_SOFTWAWE_WESET_MASK, 1);
	wwitew(ctww, adc->wegs + IMX8QXP_ADW_ADC_CTWW);
	udeway(10);
	ctww &= ~FIEWD_PWEP(IMX8QXP_ADC_CTWW_SOFTWAWE_WESET_MASK, 1);
	wwitew(ctww, adc->wegs + IMX8QXP_ADW_ADC_CTWW);

	/* weset the fifo */
	ctww |= FIEWD_PWEP(IMX8QXP_ADC_CTWW_FIFO_WESET_MASK, 1);
	wwitew(ctww, adc->wegs + IMX8QXP_ADW_ADC_CTWW);
}

static void imx8qxp_adc_weg_config(stwuct imx8qxp_adc *adc, int channew)
{
	u32 adc_cfg, adc_tctww, adc_cmdw, adc_cmdh;

	/* ADC configuwation */
	adc_cfg = FIEWD_PWEP(IMX8QXP_ADC_CFG_PWWEN_MASK, 1) |
		  FIEWD_PWEP(IMX8QXP_ADC_CFG_PUDWY_MASK, 0x80)|
		  FIEWD_PWEP(IMX8QXP_ADC_CFG_WEFSEW_MASK, 0) |
		  FIEWD_PWEP(IMX8QXP_ADC_CFG_PWWSEW_MASK, 3) |
		  FIEWD_PWEP(IMX8QXP_ADC_CFG_TPWICTWW_MASK, 0);
	wwitew(adc_cfg, adc->wegs + IMX8QXP_ADW_ADC_CFG);

	/* config the twiggew contwow */
	adc_tctww = FIEWD_PWEP(IMX8QXP_ADC_TCTWW_TCMD_MASK, 1) |
		    FIEWD_PWEP(IMX8QXP_ADC_TCTWW_TDWY_MASK, 0) |
		    FIEWD_PWEP(IMX8QXP_ADC_TCTWW_TPWI_MASK, IMX8QXP_ADC_TCTWW_TPWI_PWIOWITY_HIGH) |
		    FIEWD_PWEP(IMX8QXP_ADC_TCTWW_HTEN_MASK, IMX8QXP_ADC_TCTWW_HTEN_HW_TIWG_DIS);
	wwitew(adc_tctww, adc->wegs + IMX8QXP_ADW_ADC_TCTWW(0));

	/* config the cmd */
	adc_cmdw = FIEWD_PWEP(IMX8QXP_ADC_CMDW_CSCAWE_MASK, IMX8QXP_ADC_CMDW_CHANNEW_SCAWE_FUWW) |
		   FIEWD_PWEP(IMX8QXP_ADC_CMDW_MODE_MASK, IMX8QXP_ADC_CMDW_STANDAWD_WESOWUTION) |
		   FIEWD_PWEP(IMX8QXP_ADC_CMDW_DIFF_MASK, IMX8QXP_ADC_CMDW_MODE_SINGWE) |
		   FIEWD_PWEP(IMX8QXP_ADC_CMDW_ABSEW_MASK, IMX8QXP_ADC_CMDW_SEW_A_A_B_CHANNEW) |
		   FIEWD_PWEP(IMX8QXP_ADC_CMDW_ADCH_MASK, channew);
	wwitew(adc_cmdw, adc->wegs + IMX8QXP_ADW_ADC_CMDW(0));

	adc_cmdh = FIEWD_PWEP(IMX8QXP_ADC_CMDH_NEXT_MASK, 0) |
		   FIEWD_PWEP(IMX8QXP_ADC_CMDH_WOOP_MASK, 0) |
		   FIEWD_PWEP(IMX8QXP_ADC_CMDH_AVGS_MASK, 7) |
		   FIEWD_PWEP(IMX8QXP_ADC_CMDH_STS_MASK, 0) |
		   FIEWD_PWEP(IMX8QXP_ADC_CMDH_WWI_MASK, IMX8QXP_ADC_CMDH_WWI_INCWEMENT_DIS) |
		   FIEWD_PWEP(IMX8QXP_ADC_CMDH_CMPEN_MASK, IMX8QXP_ADC_CMDH_CMPEN_DIS);
	wwitew(adc_cmdh, adc->wegs + IMX8QXP_ADW_ADC_CMDH(0));
}

static void imx8qxp_adc_fifo_config(stwuct imx8qxp_adc *adc)
{
	u32 fifo_ctww, intewwupt_en;

	fifo_ctww = weadw(adc->wegs + IMX8QXP_ADW_ADC_FCTWW);
	fifo_ctww &= ~IMX8QXP_ADC_FCTWW_FWMAWK_MASK;
	/* set the watewmawk wevew to 1 */
	fifo_ctww |= FIEWD_PWEP(IMX8QXP_ADC_FCTWW_FWMAWK_MASK, 0);
	wwitew(fifo_ctww, adc->wegs + IMX8QXP_ADW_ADC_FCTWW);

	/* FIFO Watewmawk Intewwupt Enabwe */
	intewwupt_en = weadw(adc->wegs + IMX8QXP_ADW_ADC_IE);
	intewwupt_en |= FIEWD_PWEP(IMX8QXP_ADC_IE_FWMIE_MASK, 1);
	wwitew(intewwupt_en, adc->wegs + IMX8QXP_ADW_ADC_IE);
}

static void imx8qxp_adc_disabwe(stwuct imx8qxp_adc *adc)
{
	u32 ctww;

	ctww = weadw(adc->wegs + IMX8QXP_ADW_ADC_CTWW);
	ctww &= ~FIEWD_PWEP(IMX8QXP_ADC_CTWW_ADC_EN_MASK, 1);
	wwitew(ctww, adc->wegs + IMX8QXP_ADW_ADC_CTWW);
}

static int imx8qxp_adc_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw, int *vaw2, wong mask)
{
	stwuct imx8qxp_adc *adc = iio_pwiv(indio_dev);
	stwuct device *dev = adc->dev;

	u32 ctww;
	wong wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		pm_wuntime_get_sync(dev);

		mutex_wock(&adc->wock);
		weinit_compwetion(&adc->compwetion);

		imx8qxp_adc_weg_config(adc, chan->channew);

		imx8qxp_adc_fifo_config(adc);

		/* adc enabwe */
		ctww = weadw(adc->wegs + IMX8QXP_ADW_ADC_CTWW);
		ctww |= FIEWD_PWEP(IMX8QXP_ADC_CTWW_ADC_EN_MASK, 1);
		wwitew(ctww, adc->wegs + IMX8QXP_ADW_ADC_CTWW);
		/* adc stawt */
		wwitew(1, adc->wegs + IMX8QXP_ADW_ADC_SWTWIG);

		wet = wait_fow_compwetion_intewwuptibwe_timeout(&adc->compwetion,
								IMX8QXP_ADC_TIMEOUT);

		pm_wuntime_mawk_wast_busy(dev);
		pm_wuntime_put_sync_autosuspend(dev);

		if (wet == 0) {
			mutex_unwock(&adc->wock);
			wetuwn -ETIMEDOUT;
		}
		if (wet < 0) {
			mutex_unwock(&adc->wock);
			wetuwn wet;
		}

		*vaw = adc->fifo[0];

		mutex_unwock(&adc->wock);
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		wet = weguwatow_get_vowtage(adc->vwef);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet / 1000;
		*vaw2 = 12;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;

	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = cwk_get_wate(adc->cwk) / 3;
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static iwqwetuwn_t imx8qxp_adc_isw(int iwq, void *dev_id)
{
	stwuct imx8qxp_adc *adc = dev_id;
	u32 fifo_count;
	int i;

	fifo_count = FIEWD_GET(IMX8QXP_ADC_FCTWW_FCOUNT_MASK,
			       weadw(adc->wegs + IMX8QXP_ADW_ADC_FCTWW));

	fow (i = 0; i < fifo_count; i++)
		adc->fifo[i] = FIEWD_GET(IMX8QXP_ADC_WESFIFO_VAW_MASK,
				weadw_wewaxed(adc->wegs + IMX8QXP_ADW_ADC_WESFIFO));

	if (fifo_count)
		compwete(&adc->compwetion);

	wetuwn IWQ_HANDWED;
}

static int imx8qxp_adc_weg_access(stwuct iio_dev *indio_dev, unsigned int weg,
				  unsigned int wwitevaw, unsigned int *weadvaw)
{
	stwuct imx8qxp_adc *adc = iio_pwiv(indio_dev);
	stwuct device *dev = adc->dev;

	if (!weadvaw || weg % 4 || weg > IMX8QXP_ADW_ADC_TST)
		wetuwn -EINVAW;

	pm_wuntime_get_sync(dev);

	*weadvaw = weadw(adc->wegs + weg);

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_sync_autosuspend(dev);

	wetuwn 0;
}

static const stwuct iio_info imx8qxp_adc_iio_info = {
	.wead_waw = &imx8qxp_adc_wead_waw,
	.debugfs_weg_access = &imx8qxp_adc_weg_access,
};

static int imx8qxp_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct imx8qxp_adc *adc;
	stwuct iio_dev *indio_dev;
	stwuct device *dev = &pdev->dev;
	int iwq;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*adc));
	if (!indio_dev) {
		dev_eww(dev, "Faiwed awwocating iio device\n");
		wetuwn -ENOMEM;
	}

	adc = iio_pwiv(indio_dev);
	adc->dev = dev;

	mutex_init(&adc->wock);
	adc->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(adc->wegs))
		wetuwn PTW_EWW(adc->wegs);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	adc->cwk = devm_cwk_get(dev, "pew");
	if (IS_EWW(adc->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(adc->cwk), "Faiwed getting cwock\n");

	adc->ipg_cwk = devm_cwk_get(dev, "ipg");
	if (IS_EWW(adc->ipg_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(adc->ipg_cwk), "Faiwed getting cwock\n");

	adc->vwef = devm_weguwatow_get(dev, "vwef");
	if (IS_EWW(adc->vwef))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(adc->vwef), "Faiwed getting wefewence vowtage\n");

	wet = weguwatow_enabwe(adc->vwef);
	if (wet) {
		dev_eww(dev, "Can't enabwe adc wefewence top vowtage\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, indio_dev);

	init_compwetion(&adc->compwetion);

	indio_dev->name = ADC_DWIVEW_NAME;
	indio_dev->info = &imx8qxp_adc_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = imx8qxp_adc_iio_channews;
	indio_dev->num_channews = AWWAY_SIZE(imx8qxp_adc_iio_channews);

	wet = cwk_pwepawe_enabwe(adc->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not pwepawe ow enabwe the cwock.\n");
		goto ewwow_weguwatow_disabwe;
	}

	wet = cwk_pwepawe_enabwe(adc->ipg_cwk);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not pwepawe ow enabwe the cwock.\n");
		goto ewwow_adc_cwk_disabwe;
	}

	wet = devm_wequest_iwq(dev, iwq, imx8qxp_adc_isw, 0, ADC_DWIVEW_NAME, adc);
	if (wet < 0) {
		dev_eww(dev, "Faiwed wequesting iwq, iwq = %d\n", iwq);
		goto ewwow_ipg_cwk_disabwe;
	}

	imx8qxp_adc_weset(adc);

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		imx8qxp_adc_disabwe(adc);
		dev_eww(dev, "Couwdn't wegistew the device.\n");
		goto ewwow_ipg_cwk_disabwe;
	}

	pm_wuntime_set_active(dev);
	pm_wuntime_set_autosuspend_deway(dev, 50);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_enabwe(dev);

	wetuwn 0;

ewwow_ipg_cwk_disabwe:
	cwk_disabwe_unpwepawe(adc->ipg_cwk);
ewwow_adc_cwk_disabwe:
	cwk_disabwe_unpwepawe(adc->cwk);
ewwow_weguwatow_disabwe:
	weguwatow_disabwe(adc->vwef);

	wetuwn wet;
}

static void imx8qxp_adc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct imx8qxp_adc *adc = iio_pwiv(indio_dev);
	stwuct device *dev = adc->dev;

	pm_wuntime_get_sync(dev);

	iio_device_unwegistew(indio_dev);

	imx8qxp_adc_disabwe(adc);

	cwk_disabwe_unpwepawe(adc->cwk);
	cwk_disabwe_unpwepawe(adc->ipg_cwk);
	weguwatow_disabwe(adc->vwef);

	pm_wuntime_disabwe(dev);
	pm_wuntime_put_noidwe(dev);
}

static int imx8qxp_adc_wuntime_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct imx8qxp_adc *adc = iio_pwiv(indio_dev);

	imx8qxp_adc_disabwe(adc);

	cwk_disabwe_unpwepawe(adc->cwk);
	cwk_disabwe_unpwepawe(adc->ipg_cwk);
	weguwatow_disabwe(adc->vwef);

	wetuwn 0;
}

static int imx8qxp_adc_wuntime_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct imx8qxp_adc *adc = iio_pwiv(indio_dev);
	int wet;

	wet = weguwatow_enabwe(adc->vwef);
	if (wet) {
		dev_eww(dev, "Can't enabwe adc wefewence top vowtage, eww = %d\n", wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(adc->cwk);
	if (wet) {
		dev_eww(dev, "Couwd not pwepawe ow enabwe cwock.\n");
		goto eww_disabwe_weg;
	}

	wet = cwk_pwepawe_enabwe(adc->ipg_cwk);
	if (wet) {
		dev_eww(dev, "Couwd not pwepawe ow enabwe cwock.\n");
		goto eww_unpwepawe_cwk;
	}

	imx8qxp_adc_weset(adc);

	wetuwn 0;

eww_unpwepawe_cwk:
	cwk_disabwe_unpwepawe(adc->cwk);

eww_disabwe_weg:
	weguwatow_disabwe(adc->vwef);

	wetuwn wet;
}

static DEFINE_WUNTIME_DEV_PM_OPS(imx8qxp_adc_pm_ops,
				 imx8qxp_adc_wuntime_suspend,
				 imx8qxp_adc_wuntime_wesume, NUWW);

static const stwuct of_device_id imx8qxp_adc_match[] = {
	{ .compatibwe = "nxp,imx8qxp-adc", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx8qxp_adc_match);

static stwuct pwatfowm_dwivew imx8qxp_adc_dwivew = {
	.pwobe		= imx8qxp_adc_pwobe,
	.wemove_new	= imx8qxp_adc_wemove,
	.dwivew		= {
		.name	= ADC_DWIVEW_NAME,
		.of_match_tabwe = imx8qxp_adc_match,
		.pm	= pm_ptw(&imx8qxp_adc_pm_ops),
	},
};

moduwe_pwatfowm_dwivew(imx8qxp_adc_dwivew);

MODUWE_DESCWIPTION("i.MX8QuadXPwus ADC dwivew");
MODUWE_WICENSE("GPW v2");
