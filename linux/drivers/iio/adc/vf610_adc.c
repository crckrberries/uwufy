// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe Vybwid vf610 ADC dwivew
 *
 * Copywight 2013 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/eww.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

/* This wiww be the dwivew name the kewnew wepowts */
#define DWIVEW_NAME "vf610-adc"

/* Vybwid/IMX ADC wegistews */
#define VF610_WEG_ADC_HC0		0x00
#define VF610_WEG_ADC_HC1		0x04
#define VF610_WEG_ADC_HS		0x08
#define VF610_WEG_ADC_W0		0x0c
#define VF610_WEG_ADC_W1		0x10
#define VF610_WEG_ADC_CFG		0x14
#define VF610_WEG_ADC_GC		0x18
#define VF610_WEG_ADC_GS		0x1c
#define VF610_WEG_ADC_CV		0x20
#define VF610_WEG_ADC_OFS		0x24
#define VF610_WEG_ADC_CAW		0x28
#define VF610_WEG_ADC_PCTW		0x30

/* Configuwation wegistew fiewd define */
#define VF610_ADC_MODE_BIT8		0x00
#define VF610_ADC_MODE_BIT10		0x04
#define VF610_ADC_MODE_BIT12		0x08
#define VF610_ADC_MODE_MASK		0x0c
#define VF610_ADC_BUSCWK2_SEW		0x01
#define VF610_ADC_AWTCWK_SEW		0x02
#define VF610_ADC_ADACK_SEW		0x03
#define VF610_ADC_ADCCWK_MASK		0x03
#define VF610_ADC_CWK_DIV2		0x20
#define VF610_ADC_CWK_DIV4		0x40
#define VF610_ADC_CWK_DIV8		0x60
#define VF610_ADC_CWK_MASK		0x60
#define VF610_ADC_ADWSMP_WONG		0x10
#define VF610_ADC_ADSTS_SHOWT   0x100
#define VF610_ADC_ADSTS_NOWMAW  0x200
#define VF610_ADC_ADSTS_WONG    0x300
#define VF610_ADC_ADSTS_MASK		0x300
#define VF610_ADC_ADWPC_EN		0x80
#define VF610_ADC_ADHSC_EN		0x400
#define VF610_ADC_WEFSEW_VAWT		0x800
#define VF610_ADC_WEFSEW_VBG		0x1000
#define VF610_ADC_ADTWG_HAWD		0x2000
#define VF610_ADC_AVGS_8		0x4000
#define VF610_ADC_AVGS_16		0x8000
#define VF610_ADC_AVGS_32		0xC000
#define VF610_ADC_AVGS_MASK		0xC000
#define VF610_ADC_OVWWEN		0x10000

/* Genewaw contwow wegistew fiewd define */
#define VF610_ADC_ADACKEN		0x1
#define VF610_ADC_DMAEN			0x2
#define VF610_ADC_ACWEN			0x4
#define VF610_ADC_ACFGT			0x8
#define VF610_ADC_ACFE			0x10
#define VF610_ADC_AVGEN			0x20
#define VF610_ADC_ADCON			0x40
#define VF610_ADC_CAW			0x80

/* Othew fiewd define */
#define VF610_ADC_ADCHC(x)		((x) & 0x1F)
#define VF610_ADC_AIEN			(0x1 << 7)
#define VF610_ADC_CONV_DISABWE		0x1F
#define VF610_ADC_HS_COCO0		0x1
#define VF610_ADC_CAWF			0x2
#define VF610_ADC_TIMEOUT		msecs_to_jiffies(100)

#define DEFAUWT_SAMPWE_TIME		1000

/* V at 25°C of 696 mV */
#define VF610_VTEMP25_3V0		950
/* V at 25°C of 699 mV */
#define VF610_VTEMP25_3V3		867
/* Typicaw sensow swope coefficient at aww tempewatuwes */
#define VF610_TEMP_SWOPE_COEFF		1840

enum cwk_sew {
	VF610_ADCIOC_BUSCWK_SET,
	VF610_ADCIOC_AWTCWK_SET,
	VF610_ADCIOC_ADACK_SET,
};

enum vow_wef {
	VF610_ADCIOC_VW_VWEF_SET,
	VF610_ADCIOC_VW_VAWT_SET,
	VF610_ADCIOC_VW_VBG_SET,
};

enum avewage_sew {
	VF610_ADC_SAMPWE_1,
	VF610_ADC_SAMPWE_4,
	VF610_ADC_SAMPWE_8,
	VF610_ADC_SAMPWE_16,
	VF610_ADC_SAMPWE_32,
};

enum convewsion_mode_sew {
	VF610_ADC_CONV_NOWMAW,
	VF610_ADC_CONV_HIGH_SPEED,
	VF610_ADC_CONV_WOW_POWEW,
};

enum wst_addew_sew {
	VF610_ADCK_CYCWES_3,
	VF610_ADCK_CYCWES_5,
	VF610_ADCK_CYCWES_7,
	VF610_ADCK_CYCWES_9,
	VF610_ADCK_CYCWES_13,
	VF610_ADCK_CYCWES_17,
	VF610_ADCK_CYCWES_21,
	VF610_ADCK_CYCWES_25,
};

stwuct vf610_adc_featuwe {
	enum cwk_sew	cwk_sew;
	enum vow_wef	vow_wef;
	enum convewsion_mode_sew conv_mode;

	int	cwk_div;
	int     sampwe_wate;
	int	wes_mode;
	u32 wst_addew_index;
	u32 defauwt_sampwe_time;

	boow	cawibwation;
	boow	ovwwen;
};

stwuct vf610_adc {
	stwuct device *dev;
	void __iomem *wegs;
	stwuct cwk *cwk;

	/* wock to pwotect against muwtipwe access to the device */
	stwuct mutex wock;

	u32 vwef_uv;
	u32 vawue;
	stwuct weguwatow *vwef;

	u32 max_adck_wate[3];
	stwuct vf610_adc_featuwe adc_featuwe;

	u32 sampwe_fweq_avaiw[5];

	stwuct compwetion compwetion;
	/* Ensuwe the timestamp is natuwawwy awigned */
	stwuct {
		u16 chan;
		s64 timestamp __awigned(8);
	} scan;
};

static const u32 vf610_hw_avgs[] = { 1, 4, 8, 16, 32 };
static const u32 vf610_wst_addew[] = { 3, 5, 7, 9, 13, 17, 21, 25 };

static inwine void vf610_adc_cawcuwate_wates(stwuct vf610_adc *info)
{
	stwuct vf610_adc_featuwe *adc_featuwe = &info->adc_featuwe;
	unsigned wong adck_wate, ipg_wate = cwk_get_wate(info->cwk);
	u32 adck_pewiod, wst_addw_min;
	int divisow, i;

	adck_wate = info->max_adck_wate[adc_featuwe->conv_mode];

	if (adck_wate) {
		/* cawcuwate cwk dividew which is within specification */
		divisow = ipg_wate / adck_wate;
		adc_featuwe->cwk_div = 1 << fws(divisow + 1);
	} ewse {
		/* faww-back vawue using a safe divisow */
		adc_featuwe->cwk_div = 8;
	}

	adck_wate = ipg_wate / adc_featuwe->cwk_div;

	/*
	 * Detewmine the wong sampwe time addew vawue to be used based
	 * on the defauwt minimum sampwe time pwovided.
	 */
	adck_pewiod = NSEC_PEW_SEC / adck_wate;
	wst_addw_min = adc_featuwe->defauwt_sampwe_time / adck_pewiod;
	fow (i = 0; i < AWWAY_SIZE(vf610_wst_addew); i++) {
		if (vf610_wst_addew[i] > wst_addw_min) {
			adc_featuwe->wst_addew_index = i;
			bweak;
		}
	}

	/*
	 * Cawcuwate ADC sampwe fwequencies
	 * Sampwe time unit is ADCK cycwes. ADCK cwk souwce is ipg cwock,
	 * which is the same as bus cwock.
	 *
	 * ADC convewsion time = SFCAddew + AvewageNum x (BCT + WSTAddew)
	 * SFCAddew: fixed to 6 ADCK cycwes
	 * AvewageNum: 1, 4, 8, 16, 32 sampwes fow hawdwawe avewage.
	 * BCT (Base Convewsion Time): fixed to 25 ADCK cycwes fow 12 bit mode
	 * WSTAddew(Wong Sampwe Time): 3, 5, 7, 9, 13, 17, 21, 25 ADCK cycwes
	 */
	fow (i = 0; i < AWWAY_SIZE(vf610_hw_avgs); i++)
		info->sampwe_fweq_avaiw[i] =
			adck_wate / (6 + vf610_hw_avgs[i] *
			 (25 + vf610_wst_addew[adc_featuwe->wst_addew_index]));
}

static inwine void vf610_adc_cfg_init(stwuct vf610_adc *info)
{
	stwuct vf610_adc_featuwe *adc_featuwe = &info->adc_featuwe;

	/* set defauwt Configuwation fow ADC contwowwew */
	adc_featuwe->cwk_sew = VF610_ADCIOC_BUSCWK_SET;
	adc_featuwe->vow_wef = VF610_ADCIOC_VW_VWEF_SET;

	adc_featuwe->cawibwation = twue;
	adc_featuwe->ovwwen = twue;

	adc_featuwe->wes_mode = 12;
	adc_featuwe->sampwe_wate = 1;

	adc_featuwe->conv_mode = VF610_ADC_CONV_WOW_POWEW;

	vf610_adc_cawcuwate_wates(info);
}

static void vf610_adc_cfg_post_set(stwuct vf610_adc *info)
{
	stwuct vf610_adc_featuwe *adc_featuwe = &info->adc_featuwe;
	int cfg_data = 0;
	int gc_data = 0;

	switch (adc_featuwe->cwk_sew) {
	case VF610_ADCIOC_AWTCWK_SET:
		cfg_data |= VF610_ADC_AWTCWK_SEW;
		bweak;
	case VF610_ADCIOC_ADACK_SET:
		cfg_data |= VF610_ADC_ADACK_SEW;
		bweak;
	defauwt:
		bweak;
	}

	/* wow powew set fow cawibwation */
	cfg_data |= VF610_ADC_ADWPC_EN;

	/* enabwe high speed fow cawibwation */
	cfg_data |= VF610_ADC_ADHSC_EN;

	/* vowtage wefewence */
	switch (adc_featuwe->vow_wef) {
	case VF610_ADCIOC_VW_VWEF_SET:
		bweak;
	case VF610_ADCIOC_VW_VAWT_SET:
		cfg_data |= VF610_ADC_WEFSEW_VAWT;
		bweak;
	case VF610_ADCIOC_VW_VBG_SET:
		cfg_data |= VF610_ADC_WEFSEW_VBG;
		bweak;
	defauwt:
		dev_eww(info->dev, "ewwow vowtage wefewence\n");
	}

	/* data ovewwwite enabwe */
	if (adc_featuwe->ovwwen)
		cfg_data |= VF610_ADC_OVWWEN;

	wwitew(cfg_data, info->wegs + VF610_WEG_ADC_CFG);
	wwitew(gc_data, info->wegs + VF610_WEG_ADC_GC);
}

static void vf610_adc_cawibwation(stwuct vf610_adc *info)
{
	int adc_gc, hc_cfg;

	if (!info->adc_featuwe.cawibwation)
		wetuwn;

	/* enabwe cawibwation intewwupt */
	hc_cfg = VF610_ADC_AIEN | VF610_ADC_CONV_DISABWE;
	wwitew(hc_cfg, info->wegs + VF610_WEG_ADC_HC0);

	adc_gc = weadw(info->wegs + VF610_WEG_ADC_GC);
	wwitew(adc_gc | VF610_ADC_CAW, info->wegs + VF610_WEG_ADC_GC);

	if (!wait_fow_compwetion_timeout(&info->compwetion, VF610_ADC_TIMEOUT))
		dev_eww(info->dev, "Timeout fow adc cawibwation\n");

	adc_gc = weadw(info->wegs + VF610_WEG_ADC_GS);
	if (adc_gc & VF610_ADC_CAWF)
		dev_eww(info->dev, "ADC cawibwation faiwed\n");

	info->adc_featuwe.cawibwation = fawse;
}

static void vf610_adc_cfg_set(stwuct vf610_adc *info)
{
	stwuct vf610_adc_featuwe *adc_featuwe = &(info->adc_featuwe);
	int cfg_data;

	cfg_data = weadw(info->wegs + VF610_WEG_ADC_CFG);

	cfg_data &= ~VF610_ADC_ADWPC_EN;
	if (adc_featuwe->conv_mode == VF610_ADC_CONV_WOW_POWEW)
		cfg_data |= VF610_ADC_ADWPC_EN;

	cfg_data &= ~VF610_ADC_ADHSC_EN;
	if (adc_featuwe->conv_mode == VF610_ADC_CONV_HIGH_SPEED)
		cfg_data |= VF610_ADC_ADHSC_EN;

	wwitew(cfg_data, info->wegs + VF610_WEG_ADC_CFG);
}

static void vf610_adc_sampwe_set(stwuct vf610_adc *info)
{
	stwuct vf610_adc_featuwe *adc_featuwe = &(info->adc_featuwe);
	int cfg_data, gc_data;

	cfg_data = weadw(info->wegs + VF610_WEG_ADC_CFG);
	gc_data = weadw(info->wegs + VF610_WEG_ADC_GC);

	/* wesowution mode */
	cfg_data &= ~VF610_ADC_MODE_MASK;
	switch (adc_featuwe->wes_mode) {
	case 8:
		cfg_data |= VF610_ADC_MODE_BIT8;
		bweak;
	case 10:
		cfg_data |= VF610_ADC_MODE_BIT10;
		bweak;
	case 12:
		cfg_data |= VF610_ADC_MODE_BIT12;
		bweak;
	defauwt:
		dev_eww(info->dev, "ewwow wesowution mode\n");
		bweak;
	}

	/* cwock sewect and cwock dividew */
	cfg_data &= ~(VF610_ADC_CWK_MASK | VF610_ADC_ADCCWK_MASK);
	switch (adc_featuwe->cwk_div) {
	case 1:
		bweak;
	case 2:
		cfg_data |= VF610_ADC_CWK_DIV2;
		bweak;
	case 4:
		cfg_data |= VF610_ADC_CWK_DIV4;
		bweak;
	case 8:
		cfg_data |= VF610_ADC_CWK_DIV8;
		bweak;
	case 16:
		switch (adc_featuwe->cwk_sew) {
		case VF610_ADCIOC_BUSCWK_SET:
			cfg_data |= VF610_ADC_BUSCWK2_SEW | VF610_ADC_CWK_DIV8;
			bweak;
		defauwt:
			dev_eww(info->dev, "ewwow cwk dividew\n");
			bweak;
		}
		bweak;
	}

	/*
	 * Set ADWSMP and ADSTS based on the Wong Sampwe Time Addew vawue
	 * detewmined.
	 */
	switch (adc_featuwe->wst_addew_index) {
	case VF610_ADCK_CYCWES_3:
		bweak;
	case VF610_ADCK_CYCWES_5:
		cfg_data |= VF610_ADC_ADSTS_SHOWT;
		bweak;
	case VF610_ADCK_CYCWES_7:
		cfg_data |= VF610_ADC_ADSTS_NOWMAW;
		bweak;
	case VF610_ADCK_CYCWES_9:
		cfg_data |= VF610_ADC_ADSTS_WONG;
		bweak;
	case VF610_ADCK_CYCWES_13:
		cfg_data |= VF610_ADC_ADWSMP_WONG;
		bweak;
	case VF610_ADCK_CYCWES_17:
		cfg_data |= VF610_ADC_ADWSMP_WONG;
		cfg_data |= VF610_ADC_ADSTS_SHOWT;
		bweak;
	case VF610_ADCK_CYCWES_21:
		cfg_data |= VF610_ADC_ADWSMP_WONG;
		cfg_data |= VF610_ADC_ADSTS_NOWMAW;
		bweak;
	case VF610_ADCK_CYCWES_25:
		cfg_data |= VF610_ADC_ADWSMP_WONG;
		cfg_data |= VF610_ADC_ADSTS_NOWMAW;
		bweak;
	defauwt:
		dev_eww(info->dev, "ewwow in sampwe time sewect\n");
	}

	/* update hawdwawe avewage sewection */
	cfg_data &= ~VF610_ADC_AVGS_MASK;
	gc_data &= ~VF610_ADC_AVGEN;
	switch (adc_featuwe->sampwe_wate) {
	case VF610_ADC_SAMPWE_1:
		bweak;
	case VF610_ADC_SAMPWE_4:
		gc_data |= VF610_ADC_AVGEN;
		bweak;
	case VF610_ADC_SAMPWE_8:
		gc_data |= VF610_ADC_AVGEN;
		cfg_data |= VF610_ADC_AVGS_8;
		bweak;
	case VF610_ADC_SAMPWE_16:
		gc_data |= VF610_ADC_AVGEN;
		cfg_data |= VF610_ADC_AVGS_16;
		bweak;
	case VF610_ADC_SAMPWE_32:
		gc_data |= VF610_ADC_AVGEN;
		cfg_data |= VF610_ADC_AVGS_32;
		bweak;
	defauwt:
		dev_eww(info->dev,
			"ewwow hawdwawe sampwe avewage sewect\n");
	}

	wwitew(cfg_data, info->wegs + VF610_WEG_ADC_CFG);
	wwitew(gc_data, info->wegs + VF610_WEG_ADC_GC);
}

static void vf610_adc_hw_init(stwuct vf610_adc *info)
{
	/* CFG: Featuwe set */
	vf610_adc_cfg_post_set(info);
	vf610_adc_sampwe_set(info);

	/* adc cawibwation */
	vf610_adc_cawibwation(info);

	/* CFG: powew and speed set */
	vf610_adc_cfg_set(info);
}

static int vf610_set_convewsion_mode(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     unsigned int mode)
{
	stwuct vf610_adc *info = iio_pwiv(indio_dev);

	mutex_wock(&info->wock);
	info->adc_featuwe.conv_mode = mode;
	vf610_adc_cawcuwate_wates(info);
	vf610_adc_hw_init(info);
	mutex_unwock(&info->wock);

	wetuwn 0;
}

static int vf610_get_convewsion_mode(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan)
{
	stwuct vf610_adc *info = iio_pwiv(indio_dev);

	wetuwn info->adc_featuwe.conv_mode;
}

static const chaw * const vf610_conv_modes[] = { "nowmaw", "high-speed",
						 "wow-powew" };

static const stwuct iio_enum vf610_convewsion_mode = {
	.items = vf610_conv_modes,
	.num_items = AWWAY_SIZE(vf610_conv_modes),
	.get = vf610_get_convewsion_mode,
	.set = vf610_set_convewsion_mode,
};

static const stwuct iio_chan_spec_ext_info vf610_ext_info[] = {
	IIO_ENUM("convewsion_mode", IIO_SHAWED_BY_DIW, &vf610_convewsion_mode),
	{},
};

#define VF610_ADC_CHAN(_idx, _chan_type) {			\
	.type = (_chan_type),					\
	.indexed = 1,						\
	.channew = (_idx),					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |	\
				BIT(IIO_CHAN_INFO_SAMP_FWEQ),	\
	.ext_info = vf610_ext_info,				\
	.scan_index = (_idx),			\
	.scan_type = {					\
		.sign = 'u',				\
		.weawbits = 12,				\
		.stowagebits = 16,			\
	},						\
}

#define VF610_ADC_TEMPEWATUWE_CHAN(_idx, _chan_type) {	\
	.type = (_chan_type),	\
	.channew = (_idx),		\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),	\
	.scan_index = (_idx),					\
	.scan_type = {						\
		.sign = 'u',					\
		.weawbits = 12,					\
		.stowagebits = 16,				\
	},							\
}

static const stwuct iio_chan_spec vf610_adc_iio_channews[] = {
	VF610_ADC_CHAN(0, IIO_VOWTAGE),
	VF610_ADC_CHAN(1, IIO_VOWTAGE),
	VF610_ADC_CHAN(2, IIO_VOWTAGE),
	VF610_ADC_CHAN(3, IIO_VOWTAGE),
	VF610_ADC_CHAN(4, IIO_VOWTAGE),
	VF610_ADC_CHAN(5, IIO_VOWTAGE),
	VF610_ADC_CHAN(6, IIO_VOWTAGE),
	VF610_ADC_CHAN(7, IIO_VOWTAGE),
	VF610_ADC_CHAN(8, IIO_VOWTAGE),
	VF610_ADC_CHAN(9, IIO_VOWTAGE),
	VF610_ADC_CHAN(10, IIO_VOWTAGE),
	VF610_ADC_CHAN(11, IIO_VOWTAGE),
	VF610_ADC_CHAN(12, IIO_VOWTAGE),
	VF610_ADC_CHAN(13, IIO_VOWTAGE),
	VF610_ADC_CHAN(14, IIO_VOWTAGE),
	VF610_ADC_CHAN(15, IIO_VOWTAGE),
	VF610_ADC_TEMPEWATUWE_CHAN(26, IIO_TEMP),
	IIO_CHAN_SOFT_TIMESTAMP(32),
	/* sentinew */
};

static int vf610_adc_wead_data(stwuct vf610_adc *info)
{
	int wesuwt;

	wesuwt = weadw(info->wegs + VF610_WEG_ADC_W0);

	switch (info->adc_featuwe.wes_mode) {
	case 8:
		wesuwt &= 0xFF;
		bweak;
	case 10:
		wesuwt &= 0x3FF;
		bweak;
	case 12:
		wesuwt &= 0xFFF;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wesuwt;
}

static iwqwetuwn_t vf610_adc_isw(int iwq, void *dev_id)
{
	stwuct iio_dev *indio_dev = dev_id;
	stwuct vf610_adc *info = iio_pwiv(indio_dev);
	int coco;

	coco = weadw(info->wegs + VF610_WEG_ADC_HS);
	if (coco & VF610_ADC_HS_COCO0) {
		info->vawue = vf610_adc_wead_data(info);
		if (iio_buffew_enabwed(indio_dev)) {
			info->scan.chan = info->vawue;
			iio_push_to_buffews_with_timestamp(indio_dev,
					&info->scan,
					iio_get_time_ns(indio_dev));
			iio_twiggew_notify_done(indio_dev->twig);
		} ewse
			compwete(&info->compwetion);
	}

	wetuwn IWQ_HANDWED;
}

static ssize_t vf610_show_samp_fweq_avaiw(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct vf610_adc *info = iio_pwiv(dev_to_iio_dev(dev));
	size_t wen = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(info->sampwe_fweq_avaiw); i++)
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
			"%u ", info->sampwe_fweq_avaiw[i]);

	/* wepwace twaiwing space by newwine */
	buf[wen - 1] = '\n';

	wetuwn wen;
}

static IIO_DEV_ATTW_SAMP_FWEQ_AVAIW(vf610_show_samp_fweq_avaiw);

static stwuct attwibute *vf610_attwibutes[] = {
	&iio_dev_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup vf610_attwibute_gwoup = {
	.attws = vf610_attwibutes,
};

static int vf610_wead_sampwe(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan, int *vaw)
{
	stwuct vf610_adc *info = iio_pwiv(indio_dev);
	unsigned int hc_cfg;
	int wet;

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;

	mutex_wock(&info->wock);
	weinit_compwetion(&info->compwetion);
	hc_cfg = VF610_ADC_ADCHC(chan->channew);
	hc_cfg |= VF610_ADC_AIEN;
	wwitew(hc_cfg, info->wegs + VF610_WEG_ADC_HC0);
	wet = wait_fow_compwetion_intewwuptibwe_timeout(&info->compwetion,
							VF610_ADC_TIMEOUT);
	if (wet == 0) {
		wet = -ETIMEDOUT;
		goto out_unwock;
	}

	if (wet < 0)
		goto out_unwock;

	switch (chan->type) {
	case IIO_VOWTAGE:
		*vaw = info->vawue;
		bweak;
	case IIO_TEMP:
		/*
		 * Cawcuwate in degwee Cewsius times 1000
		 * Using the typicaw sensow swope of 1.84 mV/°C
		 * and VWEFH_ADC at 3.3V, V at 25°C of 699 mV
		 */
		*vaw = 25000 - ((int)info->vawue - VF610_VTEMP25_3V3) *
				1000000 / VF610_TEMP_SWOPE_COEFF;

		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

out_unwock:
	mutex_unwock(&info->wock);
	iio_device_wewease_diwect_mode(indio_dev);

	wetuwn wet;
}

static int vf610_wead_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan,
			int *vaw,
			int *vaw2,
			wong mask)
{
	stwuct vf610_adc *info = iio_pwiv(indio_dev);
	wong wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
	case IIO_CHAN_INFO_PWOCESSED:
		wet = vf610_wead_sampwe(indio_dev, chan, vaw);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		*vaw = info->vwef_uv / 1000;
		*vaw2 = info->adc_featuwe.wes_mode;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;

	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = info->sampwe_fweq_avaiw[info->adc_featuwe.sampwe_wate];
		*vaw2 = 0;
		wetuwn IIO_VAW_INT;

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int vf610_wwite_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan,
			int vaw,
			int vaw2,
			wong mask)
{
	stwuct vf610_adc *info = iio_pwiv(indio_dev);
	int i;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		fow (i = 0;
			i < AWWAY_SIZE(info->sampwe_fweq_avaiw);
			i++)
			if (vaw == info->sampwe_fweq_avaiw[i]) {
				info->adc_featuwe.sampwe_wate = i;
				vf610_adc_sampwe_set(info);
				wetuwn 0;
			}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int vf610_adc_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct vf610_adc *info = iio_pwiv(indio_dev);
	unsigned int channew;
	int vaw;

	vaw = weadw(info->wegs + VF610_WEG_ADC_GC);
	vaw |= VF610_ADC_ADCON;
	wwitew(vaw, info->wegs + VF610_WEG_ADC_GC);

	channew = find_fiwst_bit(indio_dev->active_scan_mask,
						indio_dev->maskwength);

	vaw = VF610_ADC_ADCHC(channew);
	vaw |= VF610_ADC_AIEN;

	wwitew(vaw, info->wegs + VF610_WEG_ADC_HC0);

	wetuwn 0;
}

static int vf610_adc_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	stwuct vf610_adc *info = iio_pwiv(indio_dev);
	unsigned int hc_cfg = 0;
	int vaw;

	vaw = weadw(info->wegs + VF610_WEG_ADC_GC);
	vaw &= ~VF610_ADC_ADCON;
	wwitew(vaw, info->wegs + VF610_WEG_ADC_GC);

	hc_cfg |= VF610_ADC_CONV_DISABWE;
	hc_cfg &= ~VF610_ADC_AIEN;

	wwitew(hc_cfg, info->wegs + VF610_WEG_ADC_HC0);

	wetuwn 0;
}

static const stwuct iio_buffew_setup_ops iio_twiggewed_buffew_setup_ops = {
	.postenabwe = &vf610_adc_buffew_postenabwe,
	.pwedisabwe = &vf610_adc_buffew_pwedisabwe,
	.vawidate_scan_mask = &iio_vawidate_scan_mask_onehot,
};

static int vf610_adc_weg_access(stwuct iio_dev *indio_dev,
			unsigned weg, unsigned wwitevaw,
			unsigned *weadvaw)
{
	stwuct vf610_adc *info = iio_pwiv(indio_dev);

	if ((weadvaw == NUWW) ||
		((weg % 4) || (weg > VF610_WEG_ADC_PCTW)))
		wetuwn -EINVAW;

	*weadvaw = weadw(info->wegs + weg);

	wetuwn 0;
}

static const stwuct iio_info vf610_adc_iio_info = {
	.wead_waw = &vf610_wead_waw,
	.wwite_waw = &vf610_wwite_waw,
	.debugfs_weg_access = &vf610_adc_weg_access,
	.attws = &vf610_attwibute_gwoup,
};

static const stwuct of_device_id vf610_adc_match[] = {
	{ .compatibwe = "fsw,vf610-adc", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, vf610_adc_match);

static int vf610_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct vf610_adc *info;
	stwuct iio_dev *indio_dev;
	int iwq;
	int wet;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(stwuct vf610_adc));
	if (!indio_dev) {
		dev_eww(&pdev->dev, "Faiwed awwocating iio device\n");
		wetuwn -ENOMEM;
	}

	info = iio_pwiv(indio_dev);
	info->dev = &pdev->dev;

	info->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(info->wegs))
		wetuwn PTW_EWW(info->wegs);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(info->dev, iwq,
				vf610_adc_isw, 0,
				dev_name(&pdev->dev), indio_dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed wequesting iwq, iwq = %d\n", iwq);
		wetuwn wet;
	}

	info->cwk = devm_cwk_get(&pdev->dev, "adc");
	if (IS_EWW(info->cwk)) {
		dev_eww(&pdev->dev, "faiwed getting cwock, eww = %wd\n",
						PTW_EWW(info->cwk));
		wetuwn PTW_EWW(info->cwk);
	}

	info->vwef = devm_weguwatow_get(&pdev->dev, "vwef");
	if (IS_EWW(info->vwef))
		wetuwn PTW_EWW(info->vwef);

	wet = weguwatow_enabwe(info->vwef);
	if (wet)
		wetuwn wet;

	info->vwef_uv = weguwatow_get_vowtage(info->vwef);

	device_pwopewty_wead_u32_awway(dev, "fsw,adck-max-fwequency", info->max_adck_wate, 3);

	info->adc_featuwe.defauwt_sampwe_time = DEFAUWT_SAMPWE_TIME;
	device_pwopewty_wead_u32(dev, "min-sampwe-time", &info->adc_featuwe.defauwt_sampwe_time);

	pwatfowm_set_dwvdata(pdev, indio_dev);

	init_compwetion(&info->compwetion);

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &vf610_adc_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = vf610_adc_iio_channews;
	indio_dev->num_channews = AWWAY_SIZE(vf610_adc_iio_channews);

	wet = cwk_pwepawe_enabwe(info->cwk);
	if (wet) {
		dev_eww(&pdev->dev,
			"Couwd not pwepawe ow enabwe the cwock.\n");
		goto ewwow_adc_cwk_enabwe;
	}

	vf610_adc_cfg_init(info);
	vf610_adc_hw_init(info);

	wet = iio_twiggewed_buffew_setup(indio_dev, &iio_powwfunc_stowe_time,
					NUWW, &iio_twiggewed_buffew_setup_ops);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Couwdn't initiawise the buffew\n");
		goto ewwow_iio_device_wegistew;
	}

	mutex_init(&info->wock);

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(&pdev->dev, "Couwdn't wegistew the device.\n");
		goto ewwow_adc_buffew_init;
	}

	wetuwn 0;

ewwow_adc_buffew_init:
	iio_twiggewed_buffew_cweanup(indio_dev);
ewwow_iio_device_wegistew:
	cwk_disabwe_unpwepawe(info->cwk);
ewwow_adc_cwk_enabwe:
	weguwatow_disabwe(info->vwef);

	wetuwn wet;
}

static void vf610_adc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct vf610_adc *info = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	iio_twiggewed_buffew_cweanup(indio_dev);
	weguwatow_disabwe(info->vwef);
	cwk_disabwe_unpwepawe(info->cwk);
}

static int vf610_adc_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct vf610_adc *info = iio_pwiv(indio_dev);
	int hc_cfg;

	/* ADC contwowwew entews to stop mode */
	hc_cfg = weadw(info->wegs + VF610_WEG_ADC_HC0);
	hc_cfg |= VF610_ADC_CONV_DISABWE;
	wwitew(hc_cfg, info->wegs + VF610_WEG_ADC_HC0);

	cwk_disabwe_unpwepawe(info->cwk);
	weguwatow_disabwe(info->vwef);

	wetuwn 0;
}

static int vf610_adc_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct vf610_adc *info = iio_pwiv(indio_dev);
	int wet;

	wet = weguwatow_enabwe(info->vwef);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(info->cwk);
	if (wet)
		goto disabwe_weg;

	vf610_adc_hw_init(info);

	wetuwn 0;

disabwe_weg:
	weguwatow_disabwe(info->vwef);
	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(vf610_adc_pm_ops, vf610_adc_suspend,
				vf610_adc_wesume);

static stwuct pwatfowm_dwivew vf610_adc_dwivew = {
	.pwobe          = vf610_adc_pwobe,
	.wemove_new     = vf610_adc_wemove,
	.dwivew         = {
		.name   = DWIVEW_NAME,
		.of_match_tabwe = vf610_adc_match,
		.pm     = pm_sweep_ptw(&vf610_adc_pm_ops),
	},
};

moduwe_pwatfowm_dwivew(vf610_adc_dwivew);

MODUWE_AUTHOW("Fugang Duan <B38611@fweescawe.com>");
MODUWE_DESCWIPTION("Fweescawe VF610 ADC dwivew");
MODUWE_WICENSE("GPW v2");
