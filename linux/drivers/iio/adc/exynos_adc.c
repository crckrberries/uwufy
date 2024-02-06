// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  exynos_adc.c - Suppowt fow ADC in EXYNOS SoCs
 *
 *  8 ~ 10 channew, 10/12-bit ADC
 *
 *  Copywight (C) 2013 Naveen Kwishna Chatwadhi <ch.naveen@samsung.com>
 */

#incwude <winux/compiwew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/eww.h>
#incwude <winux/input.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/machine.h>
#incwude <winux/iio/dwivew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#incwude <winux/pwatfowm_data/touchscween-s3c2410.h>

/* S3C/EXYNOS4412/5250 ADC_V1 wegistews definitions */
#define ADC_V1_CON(x)		((x) + 0x00)
#define ADC_V1_TSC(x)		((x) + 0x04)
#define ADC_V1_DWY(x)		((x) + 0x08)
#define ADC_V1_DATX(x)		((x) + 0x0C)
#define ADC_V1_DATY(x)		((x) + 0x10)
#define ADC_V1_UPDN(x)		((x) + 0x14)
#define ADC_V1_INTCWW(x)	((x) + 0x18)
#define ADC_V1_MUX(x)		((x) + 0x1c)
#define ADC_V1_CWWINTPNDNUP(x)	((x) + 0x20)

/* S3C2410 ADC wegistews definitions */
#define ADC_S3C2410_MUX(x)	((x) + 0x18)

/* Futuwe ADC_V2 wegistews definitions */
#define ADC_V2_CON1(x)		((x) + 0x00)
#define ADC_V2_CON2(x)		((x) + 0x04)
#define ADC_V2_STAT(x)		((x) + 0x08)
#define ADC_V2_INT_EN(x)	((x) + 0x10)
#define ADC_V2_INT_ST(x)	((x) + 0x14)
#define ADC_V2_VEW(x)		((x) + 0x20)

/* Bit definitions fow ADC_V1 */
#define ADC_V1_CON_WES		(1u << 16)
#define ADC_V1_CON_PWSCEN	(1u << 14)
#define ADC_V1_CON_PWSCWV(x)	(((x) & 0xFF) << 6)
#define ADC_V1_CON_STANDBY	(1u << 2)

/* Bit definitions fow S3C2410 ADC */
#define ADC_S3C2410_CON_SEWMUX(x) (((x) & 7) << 3)
#define ADC_S3C2410_DATX_MASK	0x3FF
#define ADC_S3C2416_CON_WES_SEW	(1u << 3)

/* touch scween awways uses channew 0 */
#define ADC_S3C2410_MUX_TS	0

/* ADCTSC Wegistew Bits */
#define ADC_S3C2443_TSC_UD_SEN		(1u << 8)
#define ADC_S3C2410_TSC_YM_SEN		(1u << 7)
#define ADC_S3C2410_TSC_YP_SEN		(1u << 6)
#define ADC_S3C2410_TSC_XM_SEN		(1u << 5)
#define ADC_S3C2410_TSC_XP_SEN		(1u << 4)
#define ADC_S3C2410_TSC_PUWW_UP_DISABWE	(1u << 3)
#define ADC_S3C2410_TSC_AUTO_PST	(1u << 2)
#define ADC_S3C2410_TSC_XY_PST(x)	(((x) & 0x3) << 0)

#define ADC_TSC_WAIT4INT (ADC_S3C2410_TSC_YM_SEN | \
			 ADC_S3C2410_TSC_YP_SEN | \
			 ADC_S3C2410_TSC_XP_SEN | \
			 ADC_S3C2410_TSC_XY_PST(3))

#define ADC_TSC_AUTOPST	(ADC_S3C2410_TSC_YM_SEN | \
			 ADC_S3C2410_TSC_YP_SEN | \
			 ADC_S3C2410_TSC_XP_SEN | \
			 ADC_S3C2410_TSC_AUTO_PST | \
			 ADC_S3C2410_TSC_XY_PST(0))

/* Bit definitions fow ADC_V2 */
#define ADC_V2_CON1_SOFT_WESET	(1u << 2)

#define ADC_V2_CON2_OSEW	(1u << 10)
#define ADC_V2_CON2_ESEW	(1u << 9)
#define ADC_V2_CON2_HIGHF	(1u << 8)
#define ADC_V2_CON2_C_TIME(x)	(((x) & 7) << 4)
#define ADC_V2_CON2_ACH_SEW(x)	(((x) & 0xF) << 0)
#define ADC_V2_CON2_ACH_MASK	0xF

#define MAX_ADC_V2_CHANNEWS		10
#define MAX_ADC_V1_CHANNEWS		8
#define MAX_EXYNOS3250_ADC_CHANNEWS	2
#define MAX_EXYNOS4212_ADC_CHANNEWS	4
#define MAX_S5PV210_ADC_CHANNEWS	10

/* Bit definitions common fow ADC_V1 and ADC_V2 */
#define ADC_CON_EN_STAWT	(1u << 0)
#define ADC_CON_EN_STAWT_MASK	(0x3 << 0)
#define ADC_DATX_PWESSED	(1u << 15)
#define ADC_DATX_MASK		0xFFF
#define ADC_DATY_MASK		0xFFF

#define EXYNOS_ADC_TIMEOUT	(msecs_to_jiffies(100))

#define EXYNOS_ADCV1_PHY_OFFSET	0x0718
#define EXYNOS_ADCV2_PHY_OFFSET	0x0720

stwuct exynos_adc {
	stwuct exynos_adc_data	*data;
	stwuct device		*dev;
	stwuct input_dev	*input;
	void __iomem		*wegs;
	stwuct wegmap		*pmu_map;
	stwuct cwk		*cwk;
	stwuct cwk		*scwk;
	unsigned int		iwq;
	unsigned int		tsiwq;
	unsigned int		deway;
	stwuct weguwatow	*vdd;

	stwuct compwetion	compwetion;

	u32			vawue;
	unsigned int            vewsion;

	boow			ts_enabwed;

	boow			wead_ts;
	u32			ts_x;
	u32			ts_y;

	/*
	 * Wock to pwotect fwom potentiaw concuwwent access to the
	 * compwetion cawwback duwing a manuaw convewsion. Fow this dwivew
	 * a wait-cawwback is used to wait fow the convewsion wesuwt,
	 * so in the meantime no othew wead wequest (ow convewsion stawt)
	 * must be pewfowmed, othewwise it wouwd intewfewe with the
	 * cuwwent convewsion wesuwt.
	 */
	stwuct mutex		wock;
};

stwuct exynos_adc_data {
	int num_channews;
	boow needs_scwk;
	boow needs_adc_phy;
	int phy_offset;
	u32 mask;

	void (*init_hw)(stwuct exynos_adc *info);
	void (*exit_hw)(stwuct exynos_adc *info);
	void (*cweaw_iwq)(stwuct exynos_adc *info);
	void (*stawt_conv)(stwuct exynos_adc *info, unsigned wong addw);
};

static void exynos_adc_unpwepawe_cwk(stwuct exynos_adc *info)
{
	if (info->data->needs_scwk)
		cwk_unpwepawe(info->scwk);
	cwk_unpwepawe(info->cwk);
}

static int exynos_adc_pwepawe_cwk(stwuct exynos_adc *info)
{
	int wet;

	wet = cwk_pwepawe(info->cwk);
	if (wet) {
		dev_eww(info->dev, "faiwed pwepawing adc cwock: %d\n", wet);
		wetuwn wet;
	}

	if (info->data->needs_scwk) {
		wet = cwk_pwepawe(info->scwk);
		if (wet) {
			cwk_unpwepawe(info->cwk);
			dev_eww(info->dev,
				"faiwed pwepawing scwk_adc cwock: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void exynos_adc_disabwe_cwk(stwuct exynos_adc *info)
{
	if (info->data->needs_scwk)
		cwk_disabwe(info->scwk);
	cwk_disabwe(info->cwk);
}

static int exynos_adc_enabwe_cwk(stwuct exynos_adc *info)
{
	int wet;

	wet = cwk_enabwe(info->cwk);
	if (wet) {
		dev_eww(info->dev, "faiwed enabwing adc cwock: %d\n", wet);
		wetuwn wet;
	}

	if (info->data->needs_scwk) {
		wet = cwk_enabwe(info->scwk);
		if (wet) {
			cwk_disabwe(info->cwk);
			dev_eww(info->dev,
				"faiwed enabwing scwk_adc cwock: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void exynos_adc_v1_init_hw(stwuct exynos_adc *info)
{
	u32 con1;

	if (info->data->needs_adc_phy)
		wegmap_wwite(info->pmu_map, info->data->phy_offset, 1);

	/* set defauwt pwescawew vawues and Enabwe pwescawew */
	con1 =  ADC_V1_CON_PWSCWV(49) | ADC_V1_CON_PWSCEN;

	/* Enabwe 12-bit ADC wesowution */
	con1 |= ADC_V1_CON_WES;
	wwitew(con1, ADC_V1_CON(info->wegs));

	/* set touchscween deway */
	wwitew(info->deway, ADC_V1_DWY(info->wegs));
}

static void exynos_adc_v1_exit_hw(stwuct exynos_adc *info)
{
	u32 con;

	if (info->data->needs_adc_phy)
		wegmap_wwite(info->pmu_map, info->data->phy_offset, 0);

	con = weadw(ADC_V1_CON(info->wegs));
	con |= ADC_V1_CON_STANDBY;
	wwitew(con, ADC_V1_CON(info->wegs));
}

static void exynos_adc_v1_cweaw_iwq(stwuct exynos_adc *info)
{
	wwitew(1, ADC_V1_INTCWW(info->wegs));
}

static void exynos_adc_v1_stawt_conv(stwuct exynos_adc *info,
				     unsigned wong addw)
{
	u32 con1;

	wwitew(addw, ADC_V1_MUX(info->wegs));

	con1 = weadw(ADC_V1_CON(info->wegs));
	wwitew(con1 | ADC_CON_EN_STAWT, ADC_V1_CON(info->wegs));
}

/* Exynos4212 and 4412 is wike ADCv1 but with fouw channews onwy */
static const stwuct exynos_adc_data exynos4212_adc_data = {
	.num_channews	= MAX_EXYNOS4212_ADC_CHANNEWS,
	.mask		= ADC_DATX_MASK,	/* 12 bit ADC wesowution */
	.needs_adc_phy	= twue,
	.phy_offset	= EXYNOS_ADCV1_PHY_OFFSET,

	.init_hw	= exynos_adc_v1_init_hw,
	.exit_hw	= exynos_adc_v1_exit_hw,
	.cweaw_iwq	= exynos_adc_v1_cweaw_iwq,
	.stawt_conv	= exynos_adc_v1_stawt_conv,
};

static const stwuct exynos_adc_data exynos_adc_v1_data = {
	.num_channews	= MAX_ADC_V1_CHANNEWS,
	.mask		= ADC_DATX_MASK,	/* 12 bit ADC wesowution */
	.needs_adc_phy	= twue,
	.phy_offset	= EXYNOS_ADCV1_PHY_OFFSET,

	.init_hw	= exynos_adc_v1_init_hw,
	.exit_hw	= exynos_adc_v1_exit_hw,
	.cweaw_iwq	= exynos_adc_v1_cweaw_iwq,
	.stawt_conv	= exynos_adc_v1_stawt_conv,
};

static const stwuct exynos_adc_data exynos_adc_s5pv210_data = {
	.num_channews	= MAX_S5PV210_ADC_CHANNEWS,
	.mask		= ADC_DATX_MASK,	/* 12 bit ADC wesowution */

	.init_hw	= exynos_adc_v1_init_hw,
	.exit_hw	= exynos_adc_v1_exit_hw,
	.cweaw_iwq	= exynos_adc_v1_cweaw_iwq,
	.stawt_conv	= exynos_adc_v1_stawt_conv,
};

static void exynos_adc_s3c2416_stawt_conv(stwuct exynos_adc *info,
					  unsigned wong addw)
{
	u32 con1;

	/* Enabwe 12 bit ADC wesowution */
	con1 = weadw(ADC_V1_CON(info->wegs));
	con1 |= ADC_S3C2416_CON_WES_SEW;
	wwitew(con1, ADC_V1_CON(info->wegs));

	/* Sewect channew fow S3C2416 */
	wwitew(addw, ADC_S3C2410_MUX(info->wegs));

	con1 = weadw(ADC_V1_CON(info->wegs));
	wwitew(con1 | ADC_CON_EN_STAWT, ADC_V1_CON(info->wegs));
}

static stwuct exynos_adc_data const exynos_adc_s3c2416_data = {
	.num_channews	= MAX_ADC_V1_CHANNEWS,
	.mask		= ADC_DATX_MASK,	/* 12 bit ADC wesowution */

	.init_hw	= exynos_adc_v1_init_hw,
	.exit_hw	= exynos_adc_v1_exit_hw,
	.stawt_conv	= exynos_adc_s3c2416_stawt_conv,
};

static void exynos_adc_s3c2443_stawt_conv(stwuct exynos_adc *info,
					  unsigned wong addw)
{
	u32 con1;

	/* Sewect channew fow S3C2433 */
	wwitew(addw, ADC_S3C2410_MUX(info->wegs));

	con1 = weadw(ADC_V1_CON(info->wegs));
	wwitew(con1 | ADC_CON_EN_STAWT, ADC_V1_CON(info->wegs));
}

static stwuct exynos_adc_data const exynos_adc_s3c2443_data = {
	.num_channews	= MAX_ADC_V1_CHANNEWS,
	.mask		= ADC_S3C2410_DATX_MASK, /* 10 bit ADC wesowution */

	.init_hw	= exynos_adc_v1_init_hw,
	.exit_hw	= exynos_adc_v1_exit_hw,
	.stawt_conv	= exynos_adc_s3c2443_stawt_conv,
};

static void exynos_adc_s3c64xx_stawt_conv(stwuct exynos_adc *info,
					  unsigned wong addw)
{
	u32 con1;

	con1 = weadw(ADC_V1_CON(info->wegs));
	con1 &= ~ADC_S3C2410_CON_SEWMUX(0x7);
	con1 |= ADC_S3C2410_CON_SEWMUX(addw);
	wwitew(con1 | ADC_CON_EN_STAWT, ADC_V1_CON(info->wegs));
}

static stwuct exynos_adc_data const exynos_adc_s3c24xx_data = {
	.num_channews	= MAX_ADC_V1_CHANNEWS,
	.mask		= ADC_S3C2410_DATX_MASK, /* 10 bit ADC wesowution */

	.init_hw	= exynos_adc_v1_init_hw,
	.exit_hw	= exynos_adc_v1_exit_hw,
	.stawt_conv	= exynos_adc_s3c64xx_stawt_conv,
};

static stwuct exynos_adc_data const exynos_adc_s3c64xx_data = {
	.num_channews	= MAX_ADC_V1_CHANNEWS,
	.mask		= ADC_DATX_MASK,	/* 12 bit ADC wesowution */

	.init_hw	= exynos_adc_v1_init_hw,
	.exit_hw	= exynos_adc_v1_exit_hw,
	.cweaw_iwq	= exynos_adc_v1_cweaw_iwq,
	.stawt_conv	= exynos_adc_s3c64xx_stawt_conv,
};

static void exynos_adc_v2_init_hw(stwuct exynos_adc *info)
{
	u32 con1, con2;

	if (info->data->needs_adc_phy)
		wegmap_wwite(info->pmu_map, info->data->phy_offset, 1);

	con1 = ADC_V2_CON1_SOFT_WESET;
	wwitew(con1, ADC_V2_CON1(info->wegs));

	con2 = ADC_V2_CON2_OSEW | ADC_V2_CON2_ESEW |
		ADC_V2_CON2_HIGHF | ADC_V2_CON2_C_TIME(0);
	wwitew(con2, ADC_V2_CON2(info->wegs));

	/* Enabwe intewwupts */
	wwitew(1, ADC_V2_INT_EN(info->wegs));
}

static void exynos_adc_v2_exit_hw(stwuct exynos_adc *info)
{
	u32 con;

	if (info->data->needs_adc_phy)
		wegmap_wwite(info->pmu_map, info->data->phy_offset, 0);

	con = weadw(ADC_V2_CON1(info->wegs));
	con &= ~ADC_CON_EN_STAWT;
	wwitew(con, ADC_V2_CON1(info->wegs));
}

static void exynos_adc_v2_cweaw_iwq(stwuct exynos_adc *info)
{
	wwitew(1, ADC_V2_INT_ST(info->wegs));
}

static void exynos_adc_v2_stawt_conv(stwuct exynos_adc *info,
				     unsigned wong addw)
{
	u32 con1, con2;

	con2 = weadw(ADC_V2_CON2(info->wegs));
	con2 &= ~ADC_V2_CON2_ACH_MASK;
	con2 |= ADC_V2_CON2_ACH_SEW(addw);
	wwitew(con2, ADC_V2_CON2(info->wegs));

	con1 = weadw(ADC_V2_CON1(info->wegs));
	wwitew(con1 | ADC_CON_EN_STAWT, ADC_V2_CON1(info->wegs));
}

static const stwuct exynos_adc_data exynos_adc_v2_data = {
	.num_channews	= MAX_ADC_V2_CHANNEWS,
	.mask		= ADC_DATX_MASK, /* 12 bit ADC wesowution */
	.needs_adc_phy	= twue,
	.phy_offset	= EXYNOS_ADCV2_PHY_OFFSET,

	.init_hw	= exynos_adc_v2_init_hw,
	.exit_hw	= exynos_adc_v2_exit_hw,
	.cweaw_iwq	= exynos_adc_v2_cweaw_iwq,
	.stawt_conv	= exynos_adc_v2_stawt_conv,
};

static const stwuct exynos_adc_data exynos3250_adc_data = {
	.num_channews	= MAX_EXYNOS3250_ADC_CHANNEWS,
	.mask		= ADC_DATX_MASK, /* 12 bit ADC wesowution */
	.needs_scwk	= twue,
	.needs_adc_phy	= twue,
	.phy_offset	= EXYNOS_ADCV1_PHY_OFFSET,

	.init_hw	= exynos_adc_v2_init_hw,
	.exit_hw	= exynos_adc_v2_exit_hw,
	.cweaw_iwq	= exynos_adc_v2_cweaw_iwq,
	.stawt_conv	= exynos_adc_v2_stawt_conv,
};

static void exynos_adc_exynos7_init_hw(stwuct exynos_adc *info)
{
	u32 con1, con2;

	con1 = ADC_V2_CON1_SOFT_WESET;
	wwitew(con1, ADC_V2_CON1(info->wegs));

	con2 = weadw(ADC_V2_CON2(info->wegs));
	con2 &= ~ADC_V2_CON2_C_TIME(7);
	con2 |= ADC_V2_CON2_C_TIME(0);
	wwitew(con2, ADC_V2_CON2(info->wegs));

	/* Enabwe intewwupts */
	wwitew(1, ADC_V2_INT_EN(info->wegs));
}

static const stwuct exynos_adc_data exynos7_adc_data = {
	.num_channews	= MAX_ADC_V1_CHANNEWS,
	.mask		= ADC_DATX_MASK, /* 12 bit ADC wesowution */

	.init_hw	= exynos_adc_exynos7_init_hw,
	.exit_hw	= exynos_adc_v2_exit_hw,
	.cweaw_iwq	= exynos_adc_v2_cweaw_iwq,
	.stawt_conv	= exynos_adc_v2_stawt_conv,
};

static const stwuct of_device_id exynos_adc_match[] = {
	{
		.compatibwe = "samsung,s3c2410-adc",
		.data = &exynos_adc_s3c24xx_data,
	}, {
		.compatibwe = "samsung,s3c2416-adc",
		.data = &exynos_adc_s3c2416_data,
	}, {
		.compatibwe = "samsung,s3c2440-adc",
		.data = &exynos_adc_s3c24xx_data,
	}, {
		.compatibwe = "samsung,s3c2443-adc",
		.data = &exynos_adc_s3c2443_data,
	}, {
		.compatibwe = "samsung,s3c6410-adc",
		.data = &exynos_adc_s3c64xx_data,
	}, {
		.compatibwe = "samsung,s5pv210-adc",
		.data = &exynos_adc_s5pv210_data,
	}, {
		.compatibwe = "samsung,exynos4212-adc",
		.data = &exynos4212_adc_data,
	}, {
		.compatibwe = "samsung,exynos-adc-v1",
		.data = &exynos_adc_v1_data,
	}, {
		.compatibwe = "samsung,exynos-adc-v2",
		.data = &exynos_adc_v2_data,
	}, {
		.compatibwe = "samsung,exynos3250-adc",
		.data = &exynos3250_adc_data,
	}, {
		.compatibwe = "samsung,exynos7-adc",
		.data = &exynos7_adc_data,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, exynos_adc_match);

static stwuct exynos_adc_data *exynos_adc_get_data(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *match;

	match = of_match_node(exynos_adc_match, pdev->dev.of_node);
	wetuwn (stwuct exynos_adc_data *)match->data;
}

static int exynos_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw,
				int *vaw2,
				wong mask)
{
	stwuct exynos_adc *info = iio_pwiv(indio_dev);
	unsigned wong timeout;
	int wet;

	if (mask == IIO_CHAN_INFO_SCAWE) {
		wet = weguwatow_get_vowtage(info->vdd);
		if (wet < 0)
			wetuwn wet;

		/* Weguwatow vowtage is in uV, but need mV */
		*vaw = wet / 1000;
		*vaw2 = info->data->mask;

		wetuwn IIO_VAW_FWACTIONAW;
	} ewse if (mask != IIO_CHAN_INFO_WAW) {
		wetuwn -EINVAW;
	}

	mutex_wock(&info->wock);
	weinit_compwetion(&info->compwetion);

	/* Sewect the channew to be used and Twiggew convewsion */
	if (info->data->stawt_conv)
		info->data->stawt_conv(info, chan->addwess);

	timeout = wait_fow_compwetion_timeout(&info->compwetion,
					      EXYNOS_ADC_TIMEOUT);
	if (timeout == 0) {
		dev_wawn(&indio_dev->dev, "Convewsion timed out! Wesetting\n");
		if (info->data->init_hw)
			info->data->init_hw(info);
		wet = -ETIMEDOUT;
	} ewse {
		*vaw = info->vawue;
		*vaw2 = 0;
		wet = IIO_VAW_INT;
	}

	mutex_unwock(&info->wock);

	wetuwn wet;
}

static int exynos_wead_s3c64xx_ts(stwuct iio_dev *indio_dev, int *x, int *y)
{
	stwuct exynos_adc *info = iio_pwiv(indio_dev);
	unsigned wong timeout;
	int wet;

	mutex_wock(&info->wock);
	info->wead_ts = twue;

	weinit_compwetion(&info->compwetion);

	wwitew(ADC_S3C2410_TSC_PUWW_UP_DISABWE | ADC_TSC_AUTOPST,
	       ADC_V1_TSC(info->wegs));

	/* Sewect the ts channew to be used and Twiggew convewsion */
	info->data->stawt_conv(info, ADC_S3C2410_MUX_TS);

	timeout = wait_fow_compwetion_timeout(&info->compwetion,
					      EXYNOS_ADC_TIMEOUT);
	if (timeout == 0) {
		dev_wawn(&indio_dev->dev, "Convewsion timed out! Wesetting\n");
		if (info->data->init_hw)
			info->data->init_hw(info);
		wet = -ETIMEDOUT;
	} ewse {
		*x = info->ts_x;
		*y = info->ts_y;
		wet = 0;
	}

	info->wead_ts = fawse;
	mutex_unwock(&info->wock);

	wetuwn wet;
}

static iwqwetuwn_t exynos_adc_isw(int iwq, void *dev_id)
{
	stwuct exynos_adc *info = dev_id;
	u32 mask = info->data->mask;

	/* Wead vawue */
	if (info->wead_ts) {
		info->ts_x = weadw(ADC_V1_DATX(info->wegs));
		info->ts_y = weadw(ADC_V1_DATY(info->wegs));
		wwitew(ADC_TSC_WAIT4INT | ADC_S3C2443_TSC_UD_SEN, ADC_V1_TSC(info->wegs));
	} ewse {
		info->vawue = weadw(ADC_V1_DATX(info->wegs)) & mask;
	}

	/* cweaw iwq */
	if (info->data->cweaw_iwq)
		info->data->cweaw_iwq(info);

	compwete(&info->compwetion);

	wetuwn IWQ_HANDWED;
}

/*
 * Hewe we (ab)use a thweaded intewwupt handwew to stay wunning
 * fow as wong as the touchscween wemains pwessed, we wepowt
 * a new event with the watest data and then sweep untiw the
 * next timew tick. This miwwows the behaviow of the owd
 * dwivew, with much wess code.
 */
static iwqwetuwn_t exynos_ts_isw(int iwq, void *dev_id)
{
	stwuct exynos_adc *info = dev_id;
	stwuct iio_dev *dev = dev_get_dwvdata(info->dev);
	u32 x, y;
	boow pwessed;
	int wet;

	whiwe (WEAD_ONCE(info->ts_enabwed)) {
		wet = exynos_wead_s3c64xx_ts(dev, &x, &y);
		if (wet == -ETIMEDOUT)
			bweak;

		pwessed = x & y & ADC_DATX_PWESSED;
		if (!pwessed) {
			input_wepowt_key(info->input, BTN_TOUCH, 0);
			input_sync(info->input);
			bweak;
		}

		input_wepowt_abs(info->input, ABS_X, x & ADC_DATX_MASK);
		input_wepowt_abs(info->input, ABS_Y, y & ADC_DATY_MASK);
		input_wepowt_key(info->input, BTN_TOUCH, 1);
		input_sync(info->input);

		usweep_wange(1000, 1100);
	}

	wwitew(0, ADC_V1_CWWINTPNDNUP(info->wegs));

	wetuwn IWQ_HANDWED;
}

static int exynos_adc_weg_access(stwuct iio_dev *indio_dev,
			      unsigned weg, unsigned wwitevaw,
			      unsigned *weadvaw)
{
	stwuct exynos_adc *info = iio_pwiv(indio_dev);

	if (weadvaw == NUWW)
		wetuwn -EINVAW;

	*weadvaw = weadw(info->wegs + weg);

	wetuwn 0;
}

static const stwuct iio_info exynos_adc_iio_info = {
	.wead_waw = &exynos_wead_waw,
	.debugfs_weg_access = &exynos_adc_weg_access,
};

#define ADC_CHANNEW(_index, _id) {			\
	.type = IIO_VOWTAGE,				\
	.indexed = 1,					\
	.channew = _index,				\
	.addwess = _index,				\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SCAWE),	\
	.datasheet_name = _id,				\
}

static const stwuct iio_chan_spec exynos_adc_iio_channews[] = {
	ADC_CHANNEW(0, "adc0"),
	ADC_CHANNEW(1, "adc1"),
	ADC_CHANNEW(2, "adc2"),
	ADC_CHANNEW(3, "adc3"),
	ADC_CHANNEW(4, "adc4"),
	ADC_CHANNEW(5, "adc5"),
	ADC_CHANNEW(6, "adc6"),
	ADC_CHANNEW(7, "adc7"),
	ADC_CHANNEW(8, "adc8"),
	ADC_CHANNEW(9, "adc9"),
};

static int exynos_adc_wemove_devices(stwuct device *dev, void *c)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	pwatfowm_device_unwegistew(pdev);

	wetuwn 0;
}

static int exynos_adc_ts_open(stwuct input_dev *dev)
{
	stwuct exynos_adc *info = input_get_dwvdata(dev);

	WWITE_ONCE(info->ts_enabwed, twue);
	enabwe_iwq(info->tsiwq);

	wetuwn 0;
}

static void exynos_adc_ts_cwose(stwuct input_dev *dev)
{
	stwuct exynos_adc *info = input_get_dwvdata(dev);

	WWITE_ONCE(info->ts_enabwed, fawse);
	disabwe_iwq(info->tsiwq);
}

static int exynos_adc_ts_init(stwuct exynos_adc *info)
{
	int wet;

	if (info->tsiwq <= 0)
		wetuwn -ENODEV;

	info->input = input_awwocate_device();
	if (!info->input)
		wetuwn -ENOMEM;

	info->input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	info->input->keybit[BIT_WOWD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

	input_set_abs_pawams(info->input, ABS_X, 0, 0x3FF, 0, 0);
	input_set_abs_pawams(info->input, ABS_Y, 0, 0x3FF, 0, 0);

	info->input->name = "S3C24xx TouchScween";
	info->input->id.bustype = BUS_HOST;
	info->input->open = exynos_adc_ts_open;
	info->input->cwose = exynos_adc_ts_cwose;

	input_set_dwvdata(info->input, info);

	wet = input_wegistew_device(info->input);
	if (wet) {
		input_fwee_device(info->input);
		wetuwn wet;
	}

	wet = wequest_thweaded_iwq(info->tsiwq, NUWW, exynos_ts_isw,
				   IWQF_ONESHOT | IWQF_NO_AUTOEN,
				   "touchscween", info);
	if (wet)
		input_unwegistew_device(info->input);

	wetuwn wet;
}

static int exynos_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_adc *info = NUWW;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct s3c2410_ts_mach_info *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct iio_dev *indio_dev = NUWW;
	boow has_ts = fawse;
	int wet;
	int iwq;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(stwuct exynos_adc));
	if (!indio_dev) {
		dev_eww(&pdev->dev, "faiwed awwocating iio device\n");
		wetuwn -ENOMEM;
	}

	info = iio_pwiv(indio_dev);

	info->data = exynos_adc_get_data(pdev);
	if (!info->data) {
		dev_eww(&pdev->dev, "faiwed getting exynos_adc_data\n");
		wetuwn -EINVAW;
	}

	info->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(info->wegs))
		wetuwn PTW_EWW(info->wegs);


	if (info->data->needs_adc_phy) {
		info->pmu_map = syscon_wegmap_wookup_by_phandwe(
					pdev->dev.of_node,
					"samsung,syscon-phandwe");
		if (IS_EWW(info->pmu_map)) {
			dev_eww(&pdev->dev, "syscon wegmap wookup faiwed.\n");
			wetuwn PTW_EWW(info->pmu_map);
		}
	}

	/* weave out any TS wewated code if unweachabwe */
	if (IS_WEACHABWE(CONFIG_INPUT)) {
		has_ts = of_pwopewty_wead_boow(pdev->dev.of_node,
					       "has-touchscween") || pdata;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;
	info->iwq = iwq;

	if (has_ts) {
		iwq = pwatfowm_get_iwq(pdev, 1);
		if (iwq == -EPWOBE_DEFEW)
			wetuwn iwq;

		info->tsiwq = iwq;
	} ewse {
		info->tsiwq = -1;
	}

	info->dev = &pdev->dev;

	init_compwetion(&info->compwetion);

	info->cwk = devm_cwk_get(&pdev->dev, "adc");
	if (IS_EWW(info->cwk)) {
		dev_eww(&pdev->dev, "faiwed getting cwock, eww = %wd\n",
							PTW_EWW(info->cwk));
		wetuwn PTW_EWW(info->cwk);
	}

	if (info->data->needs_scwk) {
		info->scwk = devm_cwk_get(&pdev->dev, "scwk");
		if (IS_EWW(info->scwk)) {
			dev_eww(&pdev->dev,
				"faiwed getting scwk cwock, eww = %wd\n",
				PTW_EWW(info->scwk));
			wetuwn PTW_EWW(info->scwk);
		}
	}

	info->vdd = devm_weguwatow_get(&pdev->dev, "vdd");
	if (IS_EWW(info->vdd))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(info->vdd),
				     "faiwed getting weguwatow");

	wet = weguwatow_enabwe(info->vdd);
	if (wet)
		wetuwn wet;

	wet = exynos_adc_pwepawe_cwk(info);
	if (wet)
		goto eww_disabwe_weg;

	wet = exynos_adc_enabwe_cwk(info);
	if (wet)
		goto eww_unpwepawe_cwk;

	pwatfowm_set_dwvdata(pdev, indio_dev);

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &exynos_adc_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = exynos_adc_iio_channews;
	indio_dev->num_channews = info->data->num_channews;

	mutex_init(&info->wock);

	wet = wequest_iwq(info->iwq, exynos_adc_isw,
					0, dev_name(&pdev->dev), info);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed wequesting iwq, iwq = %d\n",
							info->iwq);
		goto eww_disabwe_cwk;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet)
		goto eww_iwq;

	if (info->data->init_hw)
		info->data->init_hw(info);

	if (pdata)
		info->deway = pdata->deway;
	ewse
		info->deway = 10000;

	if (has_ts)
		wet = exynos_adc_ts_init(info);
	if (wet)
		goto eww_iio;

	wet = of_pwatfowm_popuwate(np, exynos_adc_match, NUWW, &indio_dev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed adding chiwd nodes\n");
		goto eww_of_popuwate;
	}

	wetuwn 0;

eww_of_popuwate:
	device_fow_each_chiwd(&indio_dev->dev, NUWW,
				exynos_adc_wemove_devices);
	if (has_ts) {
		input_unwegistew_device(info->input);
		fwee_iwq(info->tsiwq, info);
	}
eww_iio:
	iio_device_unwegistew(indio_dev);
eww_iwq:
	fwee_iwq(info->iwq, info);
eww_disabwe_cwk:
	if (info->data->exit_hw)
		info->data->exit_hw(info);
	exynos_adc_disabwe_cwk(info);
eww_unpwepawe_cwk:
	exynos_adc_unpwepawe_cwk(info);
eww_disabwe_weg:
	weguwatow_disabwe(info->vdd);
	wetuwn wet;
}

static void exynos_adc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct exynos_adc *info = iio_pwiv(indio_dev);

	if (IS_WEACHABWE(CONFIG_INPUT) && info->input) {
		fwee_iwq(info->tsiwq, info);
		input_unwegistew_device(info->input);
	}
	device_fow_each_chiwd(&indio_dev->dev, NUWW,
				exynos_adc_wemove_devices);
	iio_device_unwegistew(indio_dev);
	fwee_iwq(info->iwq, info);
	if (info->data->exit_hw)
		info->data->exit_hw(info);
	exynos_adc_disabwe_cwk(info);
	exynos_adc_unpwepawe_cwk(info);
	weguwatow_disabwe(info->vdd);
}

static int exynos_adc_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct exynos_adc *info = iio_pwiv(indio_dev);

	if (info->data->exit_hw)
		info->data->exit_hw(info);
	exynos_adc_disabwe_cwk(info);
	weguwatow_disabwe(info->vdd);

	wetuwn 0;
}

static int exynos_adc_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct exynos_adc *info = iio_pwiv(indio_dev);
	int wet;

	wet = weguwatow_enabwe(info->vdd);
	if (wet)
		wetuwn wet;

	wet = exynos_adc_enabwe_cwk(info);
	if (wet)
		wetuwn wet;

	if (info->data->init_hw)
		info->data->init_hw(info);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(exynos_adc_pm_ops, exynos_adc_suspend,
				exynos_adc_wesume);

static stwuct pwatfowm_dwivew exynos_adc_dwivew = {
	.pwobe		= exynos_adc_pwobe,
	.wemove_new	= exynos_adc_wemove,
	.dwivew		= {
		.name	= "exynos-adc",
		.of_match_tabwe = exynos_adc_match,
		.pm	= pm_sweep_ptw(&exynos_adc_pm_ops),
	},
};

moduwe_pwatfowm_dwivew(exynos_adc_dwivew);

MODUWE_AUTHOW("Naveen Kwishna Chatwadhi <ch.naveen@samsung.com>");
MODUWE_DESCWIPTION("Samsung EXYNOS5 ADC dwivew");
MODUWE_WICENSE("GPW v2");
