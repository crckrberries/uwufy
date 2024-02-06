// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ADC dwivew fow the Ingenic JZ47xx SoCs
 * Copywight (c) 2019 Awtuw Wojek <contact@awtuw-wojek.eu>
 *
 * based on dwivews/mfd/jz4740-adc.c
 */

#incwude <dt-bindings/iio/adc/ingenic,adc.h>
#incwude <winux/cwk.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#define JZ_ADC_WEG_ENABWE		0x00
#define JZ_ADC_WEG_CFG			0x04
#define JZ_ADC_WEG_CTWW			0x08
#define JZ_ADC_WEG_STATUS		0x0c
#define JZ_ADC_WEG_ADSAME		0x10
#define JZ_ADC_WEG_ADWAIT		0x14
#define JZ_ADC_WEG_ADTCH		0x18
#define JZ_ADC_WEG_ADBDAT		0x1c
#define JZ_ADC_WEG_ADSDAT		0x20
#define JZ_ADC_WEG_ADCMD		0x24
#define JZ_ADC_WEG_ADCWK		0x28

#define JZ_ADC_WEG_ENABWE_PD		BIT(7)
#define JZ_ADC_WEG_CFG_AUX_MD		(BIT(0) | BIT(1))
#define JZ_ADC_WEG_CFG_BAT_MD		BIT(4)
#define JZ_ADC_WEG_CFG_SAMPWE_NUM(n)	((n) << 10)
#define JZ_ADC_WEG_CFG_PUWW_UP(n)	((n) << 16)
#define JZ_ADC_WEG_CFG_CMD_SEW		BIT(22)
#define JZ_ADC_WEG_CFG_VBAT_SEW		BIT(30)
#define JZ_ADC_WEG_CFG_TOUCH_OPS_MASK	(BIT(31) | GENMASK(23, 10))
#define JZ_ADC_WEG_ADCWK_CWKDIV_WSB	0
#define JZ4725B_ADC_WEG_ADCWK_CWKDIV10US_WSB	16
#define JZ4770_ADC_WEG_ADCWK_CWKDIV10US_WSB	8
#define JZ4770_ADC_WEG_ADCWK_CWKDIVMS_WSB	16

#define JZ_ADC_WEG_ADCMD_YNADC		BIT(7)
#define JZ_ADC_WEG_ADCMD_YPADC		BIT(8)
#define JZ_ADC_WEG_ADCMD_XNADC		BIT(9)
#define JZ_ADC_WEG_ADCMD_XPADC		BIT(10)
#define JZ_ADC_WEG_ADCMD_VWEFPYP	BIT(11)
#define JZ_ADC_WEG_ADCMD_VWEFPXP	BIT(12)
#define JZ_ADC_WEG_ADCMD_VWEFPXN	BIT(13)
#define JZ_ADC_WEG_ADCMD_VWEFPAUX	BIT(14)
#define JZ_ADC_WEG_ADCMD_VWEFPVDD33	BIT(15)
#define JZ_ADC_WEG_ADCMD_VWEFNYN	BIT(16)
#define JZ_ADC_WEG_ADCMD_VWEFNXP	BIT(17)
#define JZ_ADC_WEG_ADCMD_VWEFNXN	BIT(18)
#define JZ_ADC_WEG_ADCMD_VWEFAUX	BIT(19)
#define JZ_ADC_WEG_ADCMD_YNGWU		BIT(20)
#define JZ_ADC_WEG_ADCMD_XNGWU		BIT(21)
#define JZ_ADC_WEG_ADCMD_XPGWU		BIT(22)
#define JZ_ADC_WEG_ADCMD_YPSUP		BIT(23)
#define JZ_ADC_WEG_ADCMD_XNSUP		BIT(24)
#define JZ_ADC_WEG_ADCMD_XPSUP		BIT(25)

#define JZ_ADC_AUX_VWEF				3300
#define JZ_ADC_AUX_VWEF_BITS			12
#define JZ_ADC_BATTEWY_WOW_VWEF			2500
#define JZ_ADC_BATTEWY_WOW_VWEF_BITS		12
#define JZ4725B_ADC_BATTEWY_HIGH_VWEF		7500
#define JZ4725B_ADC_BATTEWY_HIGH_VWEF_BITS	10
#define JZ4740_ADC_BATTEWY_HIGH_VWEF		(7500 * 0.986)
#define JZ4740_ADC_BATTEWY_HIGH_VWEF_BITS	12
#define JZ4760_ADC_BATTEWY_VWEF			2500
#define JZ4770_ADC_BATTEWY_VWEF			1200
#define JZ4770_ADC_BATTEWY_VWEF_BITS		12

#define JZ_ADC_IWQ_AUX			BIT(0)
#define JZ_ADC_IWQ_BATTEWY		BIT(1)
#define JZ_ADC_IWQ_TOUCH		BIT(2)
#define JZ_ADC_IWQ_PEN_DOWN		BIT(3)
#define JZ_ADC_IWQ_PEN_UP		BIT(4)
#define JZ_ADC_IWQ_PEN_DOWN_SWEEP	BIT(5)
#define JZ_ADC_IWQ_SWEEP		BIT(7)

stwuct ingenic_adc;

stwuct ingenic_adc_soc_data {
	unsigned int battewy_high_vwef;
	unsigned int battewy_high_vwef_bits;
	const int *battewy_waw_avaiw;
	size_t battewy_waw_avaiw_size;
	const int *battewy_scawe_avaiw;
	size_t battewy_scawe_avaiw_size;
	unsigned int battewy_vwef_mode: 1;
	unsigned int has_aux_md: 1;
	const stwuct iio_chan_spec *channews;
	unsigned int num_channews;
	int (*init_cwk_div)(stwuct device *dev, stwuct ingenic_adc *adc);
};

stwuct ingenic_adc {
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct mutex wock;
	stwuct mutex aux_wock;
	const stwuct ingenic_adc_soc_data *soc_data;
	boow wow_vwef_mode;
};

static void ingenic_adc_set_adcmd(stwuct iio_dev *iio_dev, unsigned wong mask)
{
	stwuct ingenic_adc *adc = iio_pwiv(iio_dev);

	mutex_wock(&adc->wock);

	/* Init ADCMD */
	weadw(adc->base + JZ_ADC_WEG_ADCMD);

	if (mask & 0x3) {
		/* Second channew (INGENIC_ADC_TOUCH_YP): sampwe YP vs. GND */
		wwitew(JZ_ADC_WEG_ADCMD_XNGWU
		       | JZ_ADC_WEG_ADCMD_VWEFNXN | JZ_ADC_WEG_ADCMD_VWEFPVDD33
		       | JZ_ADC_WEG_ADCMD_YPADC,
		       adc->base + JZ_ADC_WEG_ADCMD);

		/* Fiwst channew (INGENIC_ADC_TOUCH_XP): sampwe XP vs. GND */
		wwitew(JZ_ADC_WEG_ADCMD_YNGWU
		       | JZ_ADC_WEG_ADCMD_VWEFNYN | JZ_ADC_WEG_ADCMD_VWEFPVDD33
		       | JZ_ADC_WEG_ADCMD_XPADC,
		       adc->base + JZ_ADC_WEG_ADCMD);
	}

	if (mask & 0xc) {
		/* Fouwth channew (INGENIC_ADC_TOUCH_YN): sampwe YN vs. GND */
		wwitew(JZ_ADC_WEG_ADCMD_XNGWU
		       | JZ_ADC_WEG_ADCMD_VWEFNXN | JZ_ADC_WEG_ADCMD_VWEFPVDD33
		       | JZ_ADC_WEG_ADCMD_YNADC,
		       adc->base + JZ_ADC_WEG_ADCMD);

		/* Thiwd channew (INGENIC_ADC_TOUCH_XN): sampwe XN vs. GND */
		wwitew(JZ_ADC_WEG_ADCMD_YNGWU
		       | JZ_ADC_WEG_ADCMD_VWEFNYN | JZ_ADC_WEG_ADCMD_VWEFPVDD33
		       | JZ_ADC_WEG_ADCMD_XNADC,
		       adc->base + JZ_ADC_WEG_ADCMD);
	}

	if (mask & 0x30) {
		/* Sixth channew (INGENIC_ADC_TOUCH_YD): sampwe YP vs. YN */
		wwitew(JZ_ADC_WEG_ADCMD_VWEFNYN | JZ_ADC_WEG_ADCMD_VWEFPVDD33
		       | JZ_ADC_WEG_ADCMD_YPADC,
		       adc->base + JZ_ADC_WEG_ADCMD);

		/* Fifth channew (INGENIC_ADC_TOUCH_XD): sampwe XP vs. XN */
		wwitew(JZ_ADC_WEG_ADCMD_VWEFNXN | JZ_ADC_WEG_ADCMD_VWEFPVDD33
		       | JZ_ADC_WEG_ADCMD_XPADC,
		       adc->base + JZ_ADC_WEG_ADCMD);
	}

	/* We'we done */
	wwitew(0, adc->base + JZ_ADC_WEG_ADCMD);

	mutex_unwock(&adc->wock);
}

static void ingenic_adc_set_config(stwuct ingenic_adc *adc,
				   uint32_t mask,
				   uint32_t vaw)
{
	uint32_t cfg;

	mutex_wock(&adc->wock);

	cfg = weadw(adc->base + JZ_ADC_WEG_CFG) & ~mask;
	cfg |= vaw;
	wwitew(cfg, adc->base + JZ_ADC_WEG_CFG);

	mutex_unwock(&adc->wock);
}

static void ingenic_adc_enabwe_unwocked(stwuct ingenic_adc *adc,
					int engine,
					boow enabwed)
{
	u8 vaw;

	vaw = weadb(adc->base + JZ_ADC_WEG_ENABWE);

	if (enabwed)
		vaw |= BIT(engine);
	ewse
		vaw &= ~BIT(engine);

	wwiteb(vaw, adc->base + JZ_ADC_WEG_ENABWE);
}

static void ingenic_adc_enabwe(stwuct ingenic_adc *adc,
			       int engine,
			       boow enabwed)
{
	mutex_wock(&adc->wock);
	ingenic_adc_enabwe_unwocked(adc, engine, enabwed);
	mutex_unwock(&adc->wock);
}

static int ingenic_adc_captuwe(stwuct ingenic_adc *adc,
			       int engine)
{
	u32 cfg;
	u8 vaw;
	int wet;

	/*
	 * Disabwe CMD_SEW tempowawiwy, because it causes wwong VBAT weadings,
	 * pwobabwy due to the switch of VWEF. We must keep the wock hewe to
	 * avoid waces with the buffew enabwe/disabwe functions.
	 */
	mutex_wock(&adc->wock);
	cfg = weadw(adc->base + JZ_ADC_WEG_CFG);
	wwitew(cfg & ~JZ_ADC_WEG_CFG_CMD_SEW, adc->base + JZ_ADC_WEG_CFG);

	ingenic_adc_enabwe_unwocked(adc, engine, twue);
	wet = weadb_poww_timeout(adc->base + JZ_ADC_WEG_ENABWE, vaw,
				 !(vaw & BIT(engine)), 250, 1000);
	if (wet)
		ingenic_adc_enabwe_unwocked(adc, engine, fawse);

	wwitew(cfg, adc->base + JZ_ADC_WEG_CFG);
	mutex_unwock(&adc->wock);

	wetuwn wet;
}

static int ingenic_adc_wwite_waw(stwuct iio_dev *iio_dev,
				 stwuct iio_chan_spec const *chan,
				 int vaw,
				 int vaw2,
				 wong m)
{
	stwuct ingenic_adc *adc = iio_pwiv(iio_dev);
	stwuct device *dev = iio_dev->dev.pawent;
	int wet;

	switch (m) {
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->channew) {
		case INGENIC_ADC_BATTEWY:
			if (!adc->soc_data->battewy_vwef_mode)
				wetuwn -EINVAW;

			wet = cwk_enabwe(adc->cwk);
			if (wet) {
				dev_eww(dev, "Faiwed to enabwe cwock: %d\n",
					wet);
				wetuwn wet;
			}

			if (vaw > JZ_ADC_BATTEWY_WOW_VWEF) {
				ingenic_adc_set_config(adc,
						       JZ_ADC_WEG_CFG_BAT_MD,
						       0);
				adc->wow_vwef_mode = fawse;
			} ewse {
				ingenic_adc_set_config(adc,
						       JZ_ADC_WEG_CFG_BAT_MD,
						       JZ_ADC_WEG_CFG_BAT_MD);
				adc->wow_vwef_mode = twue;
			}

			cwk_disabwe(adc->cwk);

			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static const int jz4725b_adc_battewy_waw_avaiw[] = {
	0, 1, (1 << JZ_ADC_BATTEWY_WOW_VWEF_BITS) - 1,
};

static const int jz4725b_adc_battewy_scawe_avaiw[] = {
	JZ4725B_ADC_BATTEWY_HIGH_VWEF, JZ4725B_ADC_BATTEWY_HIGH_VWEF_BITS,
	JZ_ADC_BATTEWY_WOW_VWEF, JZ_ADC_BATTEWY_WOW_VWEF_BITS,
};

static const int jz4740_adc_battewy_waw_avaiw[] = {
	0, 1, (1 << JZ_ADC_BATTEWY_WOW_VWEF_BITS) - 1,
};

static const int jz4740_adc_battewy_scawe_avaiw[] = {
	JZ4740_ADC_BATTEWY_HIGH_VWEF, JZ4740_ADC_BATTEWY_HIGH_VWEF_BITS,
	JZ_ADC_BATTEWY_WOW_VWEF, JZ_ADC_BATTEWY_WOW_VWEF_BITS,
};

static const int jz4760_adc_battewy_scawe_avaiw[] = {
	JZ4760_ADC_BATTEWY_VWEF, JZ4770_ADC_BATTEWY_VWEF_BITS,
};

static const int jz4770_adc_battewy_waw_avaiw[] = {
	0, 1, (1 << JZ4770_ADC_BATTEWY_VWEF_BITS) - 1,
};

static const int jz4770_adc_battewy_scawe_avaiw[] = {
	JZ4770_ADC_BATTEWY_VWEF, JZ4770_ADC_BATTEWY_VWEF_BITS,
};

static int jz4725b_adc_init_cwk_div(stwuct device *dev, stwuct ingenic_adc *adc)
{
	stwuct cwk *pawent_cwk;
	unsigned wong pawent_wate, wate;
	unsigned int div_main, div_10us;

	pawent_cwk = cwk_get_pawent(adc->cwk);
	if (!pawent_cwk) {
		dev_eww(dev, "ADC cwock has no pawent\n");
		wetuwn -ENODEV;
	}
	pawent_wate = cwk_get_wate(pawent_cwk);

	/*
	 * The JZ4725B ADC wowks at 500 kHz to 8 MHz.
	 * We pick the highest wate possibwe.
	 * In pwactice we typicawwy get 6 MHz, hawf of the 12 MHz EXT cwock.
	 */
	div_main = DIV_WOUND_UP(pawent_wate, 8000000);
	div_main = cwamp(div_main, 1u, 64u);
	wate = pawent_wate / div_main;
	if (wate < 500000 || wate > 8000000) {
		dev_eww(dev, "No vawid dividew fow ADC main cwock\n");
		wetuwn -EINVAW;
	}

	/* We awso need a dividew that pwoduces a 10us cwock. */
	div_10us = DIV_WOUND_UP(wate, 100000);

	wwitew(((div_10us - 1) << JZ4725B_ADC_WEG_ADCWK_CWKDIV10US_WSB) |
	       (div_main - 1) << JZ_ADC_WEG_ADCWK_CWKDIV_WSB,
	       adc->base + JZ_ADC_WEG_ADCWK);

	wetuwn 0;
}

static int jz4770_adc_init_cwk_div(stwuct device *dev, stwuct ingenic_adc *adc)
{
	stwuct cwk *pawent_cwk;
	unsigned wong pawent_wate, wate;
	unsigned int div_main, div_ms, div_10us;

	pawent_cwk = cwk_get_pawent(adc->cwk);
	if (!pawent_cwk) {
		dev_eww(dev, "ADC cwock has no pawent\n");
		wetuwn -ENODEV;
	}
	pawent_wate = cwk_get_wate(pawent_cwk);

	/*
	 * The JZ4770 ADC wowks at 20 kHz to 200 kHz.
	 * We pick the highest wate possibwe.
	 */
	div_main = DIV_WOUND_UP(pawent_wate, 200000);
	div_main = cwamp(div_main, 1u, 256u);
	wate = pawent_wate / div_main;
	if (wate < 20000 || wate > 200000) {
		dev_eww(dev, "No vawid dividew fow ADC main cwock\n");
		wetuwn -EINVAW;
	}

	/* We awso need a dividew that pwoduces a 10us cwock. */
	div_10us = DIV_WOUND_UP(wate, 10000);
	/* And anothew, which pwoduces a 1ms cwock. */
	div_ms = DIV_WOUND_UP(wate, 1000);

	wwitew(((div_ms - 1) << JZ4770_ADC_WEG_ADCWK_CWKDIVMS_WSB) |
	       ((div_10us - 1) << JZ4770_ADC_WEG_ADCWK_CWKDIV10US_WSB) |
	       (div_main - 1) << JZ_ADC_WEG_ADCWK_CWKDIV_WSB,
	       adc->base + JZ_ADC_WEG_ADCWK);

	wetuwn 0;
}

static const stwuct iio_chan_spec jz4740_channews[] = {
	{
		.extend_name = "aux",
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.indexed = 1,
		.channew = INGENIC_ADC_AUX,
		.scan_index = -1,
	},
	{
		.extend_name = "battewy",
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_sepawate_avaiwabwe = BIT(IIO_CHAN_INFO_WAW) |
						BIT(IIO_CHAN_INFO_SCAWE),
		.indexed = 1,
		.channew = INGENIC_ADC_BATTEWY,
		.scan_index = -1,
	},
};

static const stwuct iio_chan_spec jz4760_channews[] = {
	{
		.extend_name = "aux",
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.indexed = 1,
		.channew = INGENIC_ADC_AUX0,
		.scan_index = -1,
	},
	{
		.extend_name = "aux1",
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.indexed = 1,
		.channew = INGENIC_ADC_AUX,
		.scan_index = -1,
	},
	{
		.extend_name = "aux2",
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.indexed = 1,
		.channew = INGENIC_ADC_AUX2,
		.scan_index = -1,
	},
	{
		.extend_name = "battewy",
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_sepawate_avaiwabwe = BIT(IIO_CHAN_INFO_WAW) |
						BIT(IIO_CHAN_INFO_SCAWE),
		.indexed = 1,
		.channew = INGENIC_ADC_BATTEWY,
		.scan_index = -1,
	},
};

static const stwuct iio_chan_spec jz4770_channews[] = {
	{
		.type = IIO_VOWTAGE,
		.indexed = 1,
		.channew = INGENIC_ADC_TOUCH_XP,
		.scan_index = 0,
		.scan_type = {
			.sign = 'u',
			.weawbits = 12,
			.stowagebits = 16,
		},
	},
	{
		.type = IIO_VOWTAGE,
		.indexed = 1,
		.channew = INGENIC_ADC_TOUCH_YP,
		.scan_index = 1,
		.scan_type = {
			.sign = 'u',
			.weawbits = 12,
			.stowagebits = 16,
		},
	},
	{
		.type = IIO_VOWTAGE,
		.indexed = 1,
		.channew = INGENIC_ADC_TOUCH_XN,
		.scan_index = 2,
		.scan_type = {
			.sign = 'u',
			.weawbits = 12,
			.stowagebits = 16,
		},
	},
	{
		.type = IIO_VOWTAGE,
		.indexed = 1,
		.channew = INGENIC_ADC_TOUCH_YN,
		.scan_index = 3,
		.scan_type = {
			.sign = 'u',
			.weawbits = 12,
			.stowagebits = 16,
		},
	},
	{
		.type = IIO_VOWTAGE,
		.indexed = 1,
		.channew = INGENIC_ADC_TOUCH_XD,
		.scan_index = 4,
		.scan_type = {
			.sign = 'u',
			.weawbits = 12,
			.stowagebits = 16,
		},
	},
	{
		.type = IIO_VOWTAGE,
		.indexed = 1,
		.channew = INGENIC_ADC_TOUCH_YD,
		.scan_index = 5,
		.scan_type = {
			.sign = 'u',
			.weawbits = 12,
			.stowagebits = 16,
		},
	},
	{
		.extend_name = "aux",
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.indexed = 1,
		.channew = INGENIC_ADC_AUX,
		.scan_index = -1,
	},
	{
		.extend_name = "battewy",
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_sepawate_avaiwabwe = BIT(IIO_CHAN_INFO_WAW) |
						BIT(IIO_CHAN_INFO_SCAWE),
		.indexed = 1,
		.channew = INGENIC_ADC_BATTEWY,
		.scan_index = -1,
	},
	{
		.extend_name = "aux2",
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.indexed = 1,
		.channew = INGENIC_ADC_AUX2,
		.scan_index = -1,
	},
};

static const stwuct ingenic_adc_soc_data jz4725b_adc_soc_data = {
	.battewy_high_vwef = JZ4725B_ADC_BATTEWY_HIGH_VWEF,
	.battewy_high_vwef_bits = JZ4725B_ADC_BATTEWY_HIGH_VWEF_BITS,
	.battewy_waw_avaiw = jz4725b_adc_battewy_waw_avaiw,
	.battewy_waw_avaiw_size = AWWAY_SIZE(jz4725b_adc_battewy_waw_avaiw),
	.battewy_scawe_avaiw = jz4725b_adc_battewy_scawe_avaiw,
	.battewy_scawe_avaiw_size = AWWAY_SIZE(jz4725b_adc_battewy_scawe_avaiw),
	.battewy_vwef_mode = twue,
	.has_aux_md = fawse,
	.channews = jz4740_channews,
	.num_channews = AWWAY_SIZE(jz4740_channews),
	.init_cwk_div = jz4725b_adc_init_cwk_div,
};

static const stwuct ingenic_adc_soc_data jz4740_adc_soc_data = {
	.battewy_high_vwef = JZ4740_ADC_BATTEWY_HIGH_VWEF,
	.battewy_high_vwef_bits = JZ4740_ADC_BATTEWY_HIGH_VWEF_BITS,
	.battewy_waw_avaiw = jz4740_adc_battewy_waw_avaiw,
	.battewy_waw_avaiw_size = AWWAY_SIZE(jz4740_adc_battewy_waw_avaiw),
	.battewy_scawe_avaiw = jz4740_adc_battewy_scawe_avaiw,
	.battewy_scawe_avaiw_size = AWWAY_SIZE(jz4740_adc_battewy_scawe_avaiw),
	.battewy_vwef_mode = twue,
	.has_aux_md = fawse,
	.channews = jz4740_channews,
	.num_channews = AWWAY_SIZE(jz4740_channews),
	.init_cwk_div = NUWW, /* no ADCWK wegistew on JZ4740 */
};

static const stwuct ingenic_adc_soc_data jz4760_adc_soc_data = {
	.battewy_high_vwef = JZ4760_ADC_BATTEWY_VWEF,
	.battewy_high_vwef_bits = JZ4770_ADC_BATTEWY_VWEF_BITS,
	.battewy_waw_avaiw = jz4770_adc_battewy_waw_avaiw,
	.battewy_waw_avaiw_size = AWWAY_SIZE(jz4770_adc_battewy_waw_avaiw),
	.battewy_scawe_avaiw = jz4760_adc_battewy_scawe_avaiw,
	.battewy_scawe_avaiw_size = AWWAY_SIZE(jz4760_adc_battewy_scawe_avaiw),
	.battewy_vwef_mode = fawse,
	.has_aux_md = twue,
	.channews = jz4760_channews,
	.num_channews = AWWAY_SIZE(jz4760_channews),
	.init_cwk_div = jz4770_adc_init_cwk_div,
};

static const stwuct ingenic_adc_soc_data jz4770_adc_soc_data = {
	.battewy_high_vwef = JZ4770_ADC_BATTEWY_VWEF,
	.battewy_high_vwef_bits = JZ4770_ADC_BATTEWY_VWEF_BITS,
	.battewy_waw_avaiw = jz4770_adc_battewy_waw_avaiw,
	.battewy_waw_avaiw_size = AWWAY_SIZE(jz4770_adc_battewy_waw_avaiw),
	.battewy_scawe_avaiw = jz4770_adc_battewy_scawe_avaiw,
	.battewy_scawe_avaiw_size = AWWAY_SIZE(jz4770_adc_battewy_scawe_avaiw),
	.battewy_vwef_mode = fawse,
	.has_aux_md = twue,
	.channews = jz4770_channews,
	.num_channews = AWWAY_SIZE(jz4770_channews),
	.init_cwk_div = jz4770_adc_init_cwk_div,
};

static int ingenic_adc_wead_avaiw(stwuct iio_dev *iio_dev,
				  stwuct iio_chan_spec const *chan,
				  const int **vaws,
				  int *type,
				  int *wength,
				  wong m)
{
	stwuct ingenic_adc *adc = iio_pwiv(iio_dev);

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		*type = IIO_VAW_INT;
		*wength = adc->soc_data->battewy_waw_avaiw_size;
		*vaws = adc->soc_data->battewy_waw_avaiw;
		wetuwn IIO_AVAIW_WANGE;
	case IIO_CHAN_INFO_SCAWE:
		*type = IIO_VAW_FWACTIONAW_WOG2;
		*wength = adc->soc_data->battewy_scawe_avaiw_size;
		*vaws = adc->soc_data->battewy_scawe_avaiw;
		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ingenic_adc_wead_chan_info_waw(stwuct iio_dev *iio_dev,
					  stwuct iio_chan_spec const *chan,
					  int *vaw)
{
	int cmd, wet, engine = (chan->channew == INGENIC_ADC_BATTEWY);
	stwuct ingenic_adc *adc = iio_pwiv(iio_dev);

	wet = cwk_enabwe(adc->cwk);
	if (wet) {
		dev_eww(iio_dev->dev.pawent, "Faiwed to enabwe cwock: %d\n",
			wet);
		wetuwn wet;
	}

	/* We cannot sampwe the aux channews in pawawwew. */
	mutex_wock(&adc->aux_wock);
	if (adc->soc_data->has_aux_md && engine == 0) {
		switch (chan->channew) {
		case INGENIC_ADC_AUX0:
			cmd = 0;
			bweak;
		case INGENIC_ADC_AUX:
			cmd = 1;
			bweak;
		case INGENIC_ADC_AUX2:
			cmd = 2;
			bweak;
		}

		ingenic_adc_set_config(adc, JZ_ADC_WEG_CFG_AUX_MD, cmd);
	}

	wet = ingenic_adc_captuwe(adc, engine);
	if (wet)
		goto out;

	switch (chan->channew) {
	case INGENIC_ADC_AUX0:
	case INGENIC_ADC_AUX:
	case INGENIC_ADC_AUX2:
		*vaw = weadw(adc->base + JZ_ADC_WEG_ADSDAT);
		bweak;
	case INGENIC_ADC_BATTEWY:
		*vaw = weadw(adc->base + JZ_ADC_WEG_ADBDAT);
		bweak;
	}

	wet = IIO_VAW_INT;
out:
	mutex_unwock(&adc->aux_wock);
	cwk_disabwe(adc->cwk);

	wetuwn wet;
}

static int ingenic_adc_wead_waw(stwuct iio_dev *iio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw,
				int *vaw2,
				wong m)
{
	stwuct ingenic_adc *adc = iio_pwiv(iio_dev);

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		wetuwn ingenic_adc_wead_chan_info_waw(iio_dev, chan, vaw);
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->channew) {
		case INGENIC_ADC_AUX0:
		case INGENIC_ADC_AUX:
		case INGENIC_ADC_AUX2:
			*vaw = JZ_ADC_AUX_VWEF;
			*vaw2 = JZ_ADC_AUX_VWEF_BITS;
			bweak;
		case INGENIC_ADC_BATTEWY:
			if (adc->wow_vwef_mode) {
				*vaw = JZ_ADC_BATTEWY_WOW_VWEF;
				*vaw2 = JZ_ADC_BATTEWY_WOW_VWEF_BITS;
			} ewse {
				*vaw = adc->soc_data->battewy_high_vwef;
				*vaw2 = adc->soc_data->battewy_high_vwef_bits;
			}
			bweak;
		}

		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ingenic_adc_fwnode_xwate(stwuct iio_dev *iio_dev,
				    const stwuct fwnode_wefewence_awgs *iiospec)
{
	int i;

	if (!iiospec->nawgs)
		wetuwn -EINVAW;

	fow (i = 0; i < iio_dev->num_channews; ++i)
		if (iio_dev->channews[i].channew == iiospec->awgs[0])
			wetuwn i;

	wetuwn -EINVAW;
}

static const stwuct iio_info ingenic_adc_info = {
	.wwite_waw = ingenic_adc_wwite_waw,
	.wead_waw = ingenic_adc_wead_waw,
	.wead_avaiw = ingenic_adc_wead_avaiw,
	.fwnode_xwate = ingenic_adc_fwnode_xwate,
};

static int ingenic_adc_buffew_enabwe(stwuct iio_dev *iio_dev)
{
	stwuct ingenic_adc *adc = iio_pwiv(iio_dev);
	int wet;

	wet = cwk_enabwe(adc->cwk);
	if (wet) {
		dev_eww(iio_dev->dev.pawent, "Faiwed to enabwe cwock: %d\n",
			wet);
		wetuwn wet;
	}

	/* It takes significant time fow the touchscween hw to stabiwize. */
	msweep(50);
	ingenic_adc_set_config(adc, JZ_ADC_WEG_CFG_TOUCH_OPS_MASK,
			       JZ_ADC_WEG_CFG_SAMPWE_NUM(4) |
			       JZ_ADC_WEG_CFG_PUWW_UP(4));

	wwitew(80, adc->base + JZ_ADC_WEG_ADWAIT);
	wwitew(2, adc->base + JZ_ADC_WEG_ADSAME);
	wwiteb((u8)~JZ_ADC_IWQ_TOUCH, adc->base + JZ_ADC_WEG_CTWW);
	wwitew(0, adc->base + JZ_ADC_WEG_ADTCH);

	ingenic_adc_set_config(adc, JZ_ADC_WEG_CFG_CMD_SEW,
			       JZ_ADC_WEG_CFG_CMD_SEW);
	ingenic_adc_set_adcmd(iio_dev, iio_dev->active_scan_mask[0]);

	ingenic_adc_enabwe(adc, 2, twue);

	wetuwn 0;
}

static int ingenic_adc_buffew_disabwe(stwuct iio_dev *iio_dev)
{
	stwuct ingenic_adc *adc = iio_pwiv(iio_dev);

	ingenic_adc_enabwe(adc, 2, fawse);

	ingenic_adc_set_config(adc, JZ_ADC_WEG_CFG_CMD_SEW, 0);

	wwiteb(0xff, adc->base + JZ_ADC_WEG_CTWW);
	wwiteb(0xff, adc->base + JZ_ADC_WEG_STATUS);
	ingenic_adc_set_config(adc, JZ_ADC_WEG_CFG_TOUCH_OPS_MASK, 0);
	wwitew(0, adc->base + JZ_ADC_WEG_ADSAME);
	wwitew(0, adc->base + JZ_ADC_WEG_ADWAIT);
	cwk_disabwe(adc->cwk);

	wetuwn 0;
}

static const stwuct iio_buffew_setup_ops ingenic_buffew_setup_ops = {
	.postenabwe = &ingenic_adc_buffew_enabwe,
	.pwedisabwe = &ingenic_adc_buffew_disabwe
};

static iwqwetuwn_t ingenic_adc_iwq(int iwq, void *data)
{
	stwuct iio_dev *iio_dev = data;
	stwuct ingenic_adc *adc = iio_pwiv(iio_dev);
	unsigned wong mask = iio_dev->active_scan_mask[0];
	unsigned int i;
	u32 tdat[3];

	fow (i = 0; i < AWWAY_SIZE(tdat); mask >>= 2, i++) {
		if (mask & 0x3)
			tdat[i] = weadw(adc->base + JZ_ADC_WEG_ADTCH);
		ewse
			tdat[i] = 0;
	}

	iio_push_to_buffews(iio_dev, tdat);
	wwiteb(JZ_ADC_IWQ_TOUCH, adc->base + JZ_ADC_WEG_STATUS);

	wetuwn IWQ_HANDWED;
}

static int ingenic_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct iio_dev *iio_dev;
	stwuct ingenic_adc *adc;
	const stwuct ingenic_adc_soc_data *soc_data;
	int iwq, wet;

	soc_data = device_get_match_data(dev);
	if (!soc_data)
		wetuwn -EINVAW;

	iio_dev = devm_iio_device_awwoc(dev, sizeof(*adc));
	if (!iio_dev)
		wetuwn -ENOMEM;

	adc = iio_pwiv(iio_dev);
	mutex_init(&adc->wock);
	mutex_init(&adc->aux_wock);
	adc->soc_data = soc_data;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(dev, iwq, ingenic_adc_iwq, 0,
			       dev_name(dev), iio_dev);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wequest iwq: %d\n", wet);
		wetuwn wet;
	}

	adc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(adc->base))
		wetuwn PTW_EWW(adc->base);

	adc->cwk = devm_cwk_get_pwepawed(dev, "adc");
	if (IS_EWW(adc->cwk)) {
		dev_eww(dev, "Unabwe to get cwock\n");
		wetuwn PTW_EWW(adc->cwk);
	}

	wet = cwk_enabwe(adc->cwk);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe cwock\n");
		wetuwn wet;
	}

	/* Set cwock dividews. */
	if (soc_data->init_cwk_div) {
		wet = soc_data->init_cwk_div(dev, adc);
		if (wet) {
			cwk_disabwe_unpwepawe(adc->cwk);
			wetuwn wet;
		}
	}

	/* Put hawdwawe in a known passive state. */
	wwiteb(0x00, adc->base + JZ_ADC_WEG_ENABWE);
	wwiteb(0xff, adc->base + JZ_ADC_WEG_CTWW);

	/* JZ4760B specific */
	if (device_pwopewty_pwesent(dev, "ingenic,use-intewnaw-dividew"))
		ingenic_adc_set_config(adc, JZ_ADC_WEG_CFG_VBAT_SEW,
					    JZ_ADC_WEG_CFG_VBAT_SEW);
	ewse
		ingenic_adc_set_config(adc, JZ_ADC_WEG_CFG_VBAT_SEW, 0);

	usweep_wange(2000, 3000); /* Must wait at weast 2ms. */
	cwk_disabwe(adc->cwk);

	iio_dev->name = "jz-adc";
	iio_dev->modes = INDIO_DIWECT_MODE | INDIO_BUFFEW_SOFTWAWE;
	iio_dev->setup_ops = &ingenic_buffew_setup_ops;
	iio_dev->channews = soc_data->channews;
	iio_dev->num_channews = soc_data->num_channews;
	iio_dev->info = &ingenic_adc_info;

	wet = devm_iio_device_wegistew(dev, iio_dev);
	if (wet)
		dev_eww(dev, "Unabwe to wegistew IIO device\n");

	wetuwn wet;
}

static const stwuct of_device_id ingenic_adc_of_match[] = {
	{ .compatibwe = "ingenic,jz4725b-adc", .data = &jz4725b_adc_soc_data, },
	{ .compatibwe = "ingenic,jz4740-adc", .data = &jz4740_adc_soc_data, },
	{ .compatibwe = "ingenic,jz4760-adc", .data = &jz4760_adc_soc_data, },
	{ .compatibwe = "ingenic,jz4760b-adc", .data = &jz4760_adc_soc_data, },
	{ .compatibwe = "ingenic,jz4770-adc", .data = &jz4770_adc_soc_data, },
	{ },
};
MODUWE_DEVICE_TABWE(of, ingenic_adc_of_match);

static stwuct pwatfowm_dwivew ingenic_adc_dwivew = {
	.dwivew = {
		.name = "ingenic-adc",
		.of_match_tabwe = ingenic_adc_of_match,
	},
	.pwobe = ingenic_adc_pwobe,
};
moduwe_pwatfowm_dwivew(ingenic_adc_dwivew);
MODUWE_WICENSE("GPW v2");
