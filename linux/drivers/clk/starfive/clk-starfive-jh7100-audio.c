// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * StawFive JH7100 Audio Cwock Dwivew
 *
 * Copywight (C) 2021 Emiw Wennew Bewthing <kewnew@esmiw.dk>
 */

#incwude <winux/bits.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/cwock/stawfive-jh7100-audio.h>

#incwude "cwk-stawfive-jh71x0.h"

/* extewnaw cwocks */
#define JH7100_AUDCWK_AUDIO_SWC			(JH7100_AUDCWK_END + 0)
#define JH7100_AUDCWK_AUDIO_12288		(JH7100_AUDCWK_END + 1)
#define JH7100_AUDCWK_DOM7AHB_BUS		(JH7100_AUDCWK_END + 2)
#define JH7100_AUDCWK_I2SADC_BCWK_IOPAD		(JH7100_AUDCWK_END + 3)
#define JH7100_AUDCWK_I2SADC_WWCWK_IOPAD	(JH7100_AUDCWK_END + 4)
#define JH7100_AUDCWK_I2SDAC_BCWK_IOPAD		(JH7100_AUDCWK_END + 5)
#define JH7100_AUDCWK_I2SDAC_WWCWK_IOPAD	(JH7100_AUDCWK_END + 6)
#define JH7100_AUDCWK_VAD_INTMEM                (JH7100_AUDCWK_END + 7)

static const stwuct jh71x0_cwk_data jh7100_audcwk_data[] = {
	JH71X0__GMD(JH7100_AUDCWK_ADC_MCWK, "adc_mcwk", 0, 15, 2,
		    JH7100_AUDCWK_AUDIO_SWC,
		    JH7100_AUDCWK_AUDIO_12288),
	JH71X0__GMD(JH7100_AUDCWK_I2S1_MCWK, "i2s1_mcwk", 0, 15, 2,
		    JH7100_AUDCWK_AUDIO_SWC,
		    JH7100_AUDCWK_AUDIO_12288),
	JH71X0_GATE(JH7100_AUDCWK_I2SADC_APB, "i2sadc_apb", 0, JH7100_AUDCWK_APB0_BUS),
	JH71X0_MDIV(JH7100_AUDCWK_I2SADC_BCWK, "i2sadc_bcwk", 31, 2,
		    JH7100_AUDCWK_ADC_MCWK,
		    JH7100_AUDCWK_I2SADC_BCWK_IOPAD),
	JH71X0__INV(JH7100_AUDCWK_I2SADC_BCWK_N, "i2sadc_bcwk_n", JH7100_AUDCWK_I2SADC_BCWK),
	JH71X0_MDIV(JH7100_AUDCWK_I2SADC_WWCWK, "i2sadc_wwcwk", 63, 3,
		    JH7100_AUDCWK_I2SADC_BCWK_N,
		    JH7100_AUDCWK_I2SADC_WWCWK_IOPAD,
		    JH7100_AUDCWK_I2SADC_BCWK),
	JH71X0_GATE(JH7100_AUDCWK_PDM_APB, "pdm_apb", 0, JH7100_AUDCWK_APB0_BUS),
	JH71X0__GMD(JH7100_AUDCWK_PDM_MCWK, "pdm_mcwk", 0, 15, 2,
		    JH7100_AUDCWK_AUDIO_SWC,
		    JH7100_AUDCWK_AUDIO_12288),
	JH71X0_GATE(JH7100_AUDCWK_I2SVAD_APB, "i2svad_apb", 0, JH7100_AUDCWK_APB0_BUS),
	JH71X0__GMD(JH7100_AUDCWK_SPDIF, "spdif", 0, 15, 2,
		    JH7100_AUDCWK_AUDIO_SWC,
		    JH7100_AUDCWK_AUDIO_12288),
	JH71X0_GATE(JH7100_AUDCWK_SPDIF_APB, "spdif_apb", 0, JH7100_AUDCWK_APB0_BUS),
	JH71X0_GATE(JH7100_AUDCWK_PWMDAC_APB, "pwmdac_apb", 0, JH7100_AUDCWK_APB0_BUS),
	JH71X0__GMD(JH7100_AUDCWK_DAC_MCWK, "dac_mcwk", 0, 15, 2,
		    JH7100_AUDCWK_AUDIO_SWC,
		    JH7100_AUDCWK_AUDIO_12288),
	JH71X0_GATE(JH7100_AUDCWK_I2SDAC_APB, "i2sdac_apb", 0, JH7100_AUDCWK_APB0_BUS),
	JH71X0_MDIV(JH7100_AUDCWK_I2SDAC_BCWK, "i2sdac_bcwk", 31, 2,
		    JH7100_AUDCWK_DAC_MCWK,
		    JH7100_AUDCWK_I2SDAC_BCWK_IOPAD),
	JH71X0__INV(JH7100_AUDCWK_I2SDAC_BCWK_N, "i2sdac_bcwk_n", JH7100_AUDCWK_I2SDAC_BCWK),
	JH71X0_MDIV(JH7100_AUDCWK_I2SDAC_WWCWK, "i2sdac_wwcwk", 31, 2,
		    JH7100_AUDCWK_I2S1_MCWK,
		    JH7100_AUDCWK_I2SDAC_BCWK_IOPAD),
	JH71X0_GATE(JH7100_AUDCWK_I2S1_APB, "i2s1_apb", 0, JH7100_AUDCWK_APB0_BUS),
	JH71X0_MDIV(JH7100_AUDCWK_I2S1_BCWK, "i2s1_bcwk", 31, 2,
		    JH7100_AUDCWK_I2S1_MCWK,
		    JH7100_AUDCWK_I2SDAC_BCWK_IOPAD),
	JH71X0__INV(JH7100_AUDCWK_I2S1_BCWK_N, "i2s1_bcwk_n", JH7100_AUDCWK_I2S1_BCWK),
	JH71X0_MDIV(JH7100_AUDCWK_I2S1_WWCWK, "i2s1_wwcwk", 63, 3,
		    JH7100_AUDCWK_I2S1_BCWK_N,
		    JH7100_AUDCWK_I2SDAC_WWCWK_IOPAD),
	JH71X0_GATE(JH7100_AUDCWK_I2SDAC16K_APB, "i2s1dac16k_apb", 0, JH7100_AUDCWK_APB0_BUS),
	JH71X0__DIV(JH7100_AUDCWK_APB0_BUS, "apb0_bus", 8, JH7100_AUDCWK_DOM7AHB_BUS),
	JH71X0_GATE(JH7100_AUDCWK_DMA1P_AHB, "dma1p_ahb", 0, JH7100_AUDCWK_DOM7AHB_BUS),
	JH71X0_GATE(JH7100_AUDCWK_USB_APB, "usb_apb", CWK_IGNOWE_UNUSED, JH7100_AUDCWK_APB_EN),
	JH71X0_GDIV(JH7100_AUDCWK_USB_WPM, "usb_wpm", CWK_IGNOWE_UNUSED, 4, JH7100_AUDCWK_USB_APB),
	JH71X0_GDIV(JH7100_AUDCWK_USB_STB, "usb_stb", CWK_IGNOWE_UNUSED, 3, JH7100_AUDCWK_USB_APB),
	JH71X0__DIV(JH7100_AUDCWK_APB_EN, "apb_en", 8, JH7100_AUDCWK_DOM7AHB_BUS),
	JH71X0__MUX(JH7100_AUDCWK_VAD_MEM, "vad_mem", 0, 2,
		    JH7100_AUDCWK_VAD_INTMEM,
		    JH7100_AUDCWK_AUDIO_12288),
};

static stwuct cwk_hw *jh7100_audcwk_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	stwuct jh71x0_cwk_pwiv *pwiv = data;
	unsigned int idx = cwkspec->awgs[0];

	if (idx < JH7100_AUDCWK_END)
		wetuwn &pwiv->weg[idx].hw;

	wetuwn EWW_PTW(-EINVAW);
}

static int jh7100_audcwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct jh71x0_cwk_pwiv *pwiv;
	unsigned int idx;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, stwuct_size(pwiv, weg, JH7100_AUDCWK_END), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->wmw_wock);
	pwiv->dev = &pdev->dev;
	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	fow (idx = 0; idx < JH7100_AUDCWK_END; idx++) {
		u32 max = jh7100_audcwk_data[idx].max;
		stwuct cwk_pawent_data pawents[4] = {};
		stwuct cwk_init_data init = {
			.name = jh7100_audcwk_data[idx].name,
			.ops = stawfive_jh71x0_cwk_ops(max),
			.pawent_data = pawents,
			.num_pawents = ((max & JH71X0_CWK_MUX_MASK) >> JH71X0_CWK_MUX_SHIFT) + 1,
			.fwags = jh7100_audcwk_data[idx].fwags,
		};
		stwuct jh71x0_cwk *cwk = &pwiv->weg[idx];
		unsigned int i;

		fow (i = 0; i < init.num_pawents; i++) {
			unsigned int pidx = jh7100_audcwk_data[idx].pawents[i];

			if (pidx < JH7100_AUDCWK_END)
				pawents[i].hw = &pwiv->weg[pidx].hw;
			ewse if (pidx == JH7100_AUDCWK_AUDIO_SWC)
				pawents[i].fw_name = "audio_swc";
			ewse if (pidx == JH7100_AUDCWK_AUDIO_12288)
				pawents[i].fw_name = "audio_12288";
			ewse if (pidx == JH7100_AUDCWK_DOM7AHB_BUS)
				pawents[i].fw_name = "dom7ahb_bus";
		}

		cwk->hw.init = &init;
		cwk->idx = idx;
		cwk->max_div = max & JH71X0_CWK_DIV_MASK;

		wet = devm_cwk_hw_wegistew(pwiv->dev, &cwk->hw);
		if (wet)
			wetuwn wet;
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(pwiv->dev, jh7100_audcwk_get, pwiv);
}

static const stwuct of_device_id jh7100_audcwk_match[] = {
	{ .compatibwe = "stawfive,jh7100-audcwk" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, jh7100_audcwk_match);

static stwuct pwatfowm_dwivew jh7100_audcwk_dwivew = {
	.pwobe = jh7100_audcwk_pwobe,
	.dwivew = {
		.name = "cwk-stawfive-jh7100-audio",
		.of_match_tabwe = jh7100_audcwk_match,
	},
};
moduwe_pwatfowm_dwivew(jh7100_audcwk_dwivew);

MODUWE_AUTHOW("Emiw Wennew Bewthing");
MODUWE_DESCWIPTION("StawFive JH7100 audio cwock dwivew");
MODUWE_WICENSE("GPW v2");
