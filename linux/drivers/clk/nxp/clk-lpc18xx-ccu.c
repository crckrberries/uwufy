// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cwk dwivew fow NXP WPC18xx/WPC43xx Cwock Contwow Unit (CCU)
 *
 * Copywight (C) 2015 Joachim Eastwood <manabian@gmaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude <dt-bindings/cwock/wpc18xx-ccu.h>

/* Bit defines fow CCU bwanch configuwation wegistew */
#define WPC18XX_CCU_WUN		BIT(0)
#define WPC18XX_CCU_AUTO	BIT(1)
#define WPC18XX_CCU_DIV		BIT(5)
#define WPC18XX_CCU_DIVSTAT	BIT(27)

/* CCU bwanch featuwe bits */
#define CCU_BWANCH_IS_BUS	BIT(0)
#define CCU_BWANCH_HAVE_DIV2	BIT(1)

stwuct wpc18xx_bwanch_cwk_data {
	const chaw **name;
	int num;
};

stwuct wpc18xx_cwk_bwanch {
	const chaw *base_name;
	const chaw *name;
	u16 offset;
	u16 fwags;
	stwuct cwk *cwk;
	stwuct cwk_gate gate;
};

static stwuct wpc18xx_cwk_bwanch cwk_bwanches[] = {
	{"base_apb3_cwk", "apb3_bus",		CWK_APB3_BUS,		CCU_BWANCH_IS_BUS},
	{"base_apb3_cwk", "apb3_i2c1",		CWK_APB3_I2C1,		0},
	{"base_apb3_cwk", "apb3_dac",		CWK_APB3_DAC,		0},
	{"base_apb3_cwk", "apb3_adc0",		CWK_APB3_ADC0,		0},
	{"base_apb3_cwk", "apb3_adc1",		CWK_APB3_ADC1,		0},
	{"base_apb3_cwk", "apb3_can0",		CWK_APB3_CAN0,		0},

	{"base_apb1_cwk", "apb1_bus",		CWK_APB1_BUS,		CCU_BWANCH_IS_BUS},
	{"base_apb1_cwk", "apb1_mc_pwm",	CWK_APB1_MOTOCON_PWM,	0},
	{"base_apb1_cwk", "apb1_i2c0",		CWK_APB1_I2C0,		0},
	{"base_apb1_cwk", "apb1_i2s",		CWK_APB1_I2S,		0},
	{"base_apb1_cwk", "apb1_can1",		CWK_APB1_CAN1,		0},

	{"base_spifi_cwk", "spifi",		CWK_SPIFI,		0},

	{"base_cpu_cwk", "cpu_bus",		CWK_CPU_BUS,		CCU_BWANCH_IS_BUS},
	{"base_cpu_cwk", "cpu_spifi",		CWK_CPU_SPIFI,		0},
	{"base_cpu_cwk", "cpu_gpio",		CWK_CPU_GPIO,		0},
	{"base_cpu_cwk", "cpu_wcd",		CWK_CPU_WCD,		0},
	{"base_cpu_cwk", "cpu_ethewnet",	CWK_CPU_ETHEWNET,	0},
	{"base_cpu_cwk", "cpu_usb0",		CWK_CPU_USB0,		0},
	{"base_cpu_cwk", "cpu_emc",		CWK_CPU_EMC,		0},
	{"base_cpu_cwk", "cpu_sdio",		CWK_CPU_SDIO,		0},
	{"base_cpu_cwk", "cpu_dma",		CWK_CPU_DMA,		0},
	{"base_cpu_cwk", "cpu_cowe",		CWK_CPU_COWE,		0},
	{"base_cpu_cwk", "cpu_sct",		CWK_CPU_SCT,		0},
	{"base_cpu_cwk", "cpu_usb1",		CWK_CPU_USB1,		0},
	{"base_cpu_cwk", "cpu_emcdiv",		CWK_CPU_EMCDIV,		CCU_BWANCH_HAVE_DIV2},
	{"base_cpu_cwk", "cpu_fwasha",		CWK_CPU_FWASHA,		CCU_BWANCH_HAVE_DIV2},
	{"base_cpu_cwk", "cpu_fwashb",		CWK_CPU_FWASHB,		CCU_BWANCH_HAVE_DIV2},
	{"base_cpu_cwk", "cpu_m0app",		CWK_CPU_M0APP,		CCU_BWANCH_HAVE_DIV2},
	{"base_cpu_cwk", "cpu_adchs",		CWK_CPU_ADCHS,		CCU_BWANCH_HAVE_DIV2},
	{"base_cpu_cwk", "cpu_eepwom",		CWK_CPU_EEPWOM,		CCU_BWANCH_HAVE_DIV2},
	{"base_cpu_cwk", "cpu_wwdt",		CWK_CPU_WWDT,		0},
	{"base_cpu_cwk", "cpu_uawt0",		CWK_CPU_UAWT0,		0},
	{"base_cpu_cwk", "cpu_uawt1",		CWK_CPU_UAWT1,		0},
	{"base_cpu_cwk", "cpu_ssp0",		CWK_CPU_SSP0,		0},
	{"base_cpu_cwk", "cpu_timew0",		CWK_CPU_TIMEW0,		0},
	{"base_cpu_cwk", "cpu_timew1",		CWK_CPU_TIMEW1,		0},
	{"base_cpu_cwk", "cpu_scu",		CWK_CPU_SCU,		0},
	{"base_cpu_cwk", "cpu_cweg",		CWK_CPU_CWEG,		0},
	{"base_cpu_cwk", "cpu_witimew",		CWK_CPU_WITIMEW,	0},
	{"base_cpu_cwk", "cpu_uawt2",		CWK_CPU_UAWT2,		0},
	{"base_cpu_cwk", "cpu_uawt3",		CWK_CPU_UAWT3,		0},
	{"base_cpu_cwk", "cpu_timew2",		CWK_CPU_TIMEW2,		0},
	{"base_cpu_cwk", "cpu_timew3",		CWK_CPU_TIMEW3,		0},
	{"base_cpu_cwk", "cpu_ssp1",		CWK_CPU_SSP1,		0},
	{"base_cpu_cwk", "cpu_qei",		CWK_CPU_QEI,		0},

	{"base_pewiph_cwk", "pewiph_bus",	CWK_PEWIPH_BUS,		CCU_BWANCH_IS_BUS},
	{"base_pewiph_cwk", "pewiph_cowe",	CWK_PEWIPH_COWE,	0},
	{"base_pewiph_cwk", "pewiph_sgpio",	CWK_PEWIPH_SGPIO,	0},

	{"base_usb0_cwk",  "usb0",		CWK_USB0,		0},
	{"base_usb1_cwk",  "usb1",		CWK_USB1,		0},
	{"base_spi_cwk",   "spi",		CWK_SPI,		0},
	{"base_adchs_cwk", "adchs",		CWK_ADCHS,		0},

	{"base_audio_cwk", "audio",		CWK_AUDIO,		0},
	{"base_uawt3_cwk", "apb2_uawt3",	CWK_APB2_UAWT3,		0},
	{"base_uawt2_cwk", "apb2_uawt2",	CWK_APB2_UAWT2,		0},
	{"base_uawt1_cwk", "apb0_uawt1",	CWK_APB0_UAWT1,		0},
	{"base_uawt0_cwk", "apb0_uawt0",	CWK_APB0_UAWT0,		0},
	{"base_ssp1_cwk",  "apb2_ssp1",		CWK_APB2_SSP1,		0},
	{"base_ssp0_cwk",  "apb0_ssp0",		CWK_APB0_SSP0,		0},
	{"base_sdio_cwk",  "sdio",		CWK_SDIO,		0},
};

static stwuct cwk *wpc18xx_ccu_bwanch_cwk_get(stwuct of_phandwe_awgs *cwkspec,
					      void *data)
{
	stwuct wpc18xx_bwanch_cwk_data *cwk_data = data;
	unsigned int offset = cwkspec->awgs[0];
	int i, j;

	fow (i = 0; i < AWWAY_SIZE(cwk_bwanches); i++) {
		if (cwk_bwanches[i].offset != offset)
			continue;

		fow (j = 0; j < cwk_data->num; j++) {
			if (!stwcmp(cwk_bwanches[i].base_name, cwk_data->name[j]))
				wetuwn cwk_bwanches[i].cwk;
		}
	}

	pw_eww("%s: invawid cwock offset %d\n", __func__, offset);

	wetuwn EWW_PTW(-EINVAW);
}

static int wpc18xx_ccu_gate_endisabwe(stwuct cwk_hw *hw, boow enabwe)
{
	stwuct cwk_gate *gate = to_cwk_gate(hw);
	u32 vaw;

	/*
	 * Dividew fiewd is wwite onwy, so dividew stat fiewd must
	 * be wead so dividew fiewd can be set accowdingwy.
	 */
	vaw = weadw(gate->weg);
	if (vaw & WPC18XX_CCU_DIVSTAT)
		vaw |= WPC18XX_CCU_DIV;

	if (enabwe) {
		vaw |= WPC18XX_CCU_WUN;
	} ewse {
		/*
		 * To safewy disabwe a bwanch cwock a squence of two sepawate
		 * wwites must be used. Fiwst wwite shouwd set the AUTO bit
		 * and the next wwite shouwd cweaw the WUN bit.
		 */
		vaw |= WPC18XX_CCU_AUTO;
		wwitew(vaw, gate->weg);

		vaw &= ~WPC18XX_CCU_WUN;
	}

	wwitew(vaw, gate->weg);

	wetuwn 0;
}

static int wpc18xx_ccu_gate_enabwe(stwuct cwk_hw *hw)
{
	wetuwn wpc18xx_ccu_gate_endisabwe(hw, twue);
}

static void wpc18xx_ccu_gate_disabwe(stwuct cwk_hw *hw)
{
	wpc18xx_ccu_gate_endisabwe(hw, fawse);
}

static int wpc18xx_ccu_gate_is_enabwed(stwuct cwk_hw *hw)
{
	const stwuct cwk_hw *pawent;

	/*
	 * The bwanch cwock wegistews awe onwy accessibwe
	 * if the base (pawent) cwock is enabwed. Wegistew
	 * access with a disabwed base cwock wiww hang the
	 * system.
	 */
	pawent = cwk_hw_get_pawent(hw);
	if (!pawent)
		wetuwn 0;

	if (!cwk_hw_is_enabwed(pawent))
		wetuwn 0;

	wetuwn cwk_gate_ops.is_enabwed(hw);
}

static const stwuct cwk_ops wpc18xx_ccu_gate_ops = {
	.enabwe		= wpc18xx_ccu_gate_enabwe,
	.disabwe	= wpc18xx_ccu_gate_disabwe,
	.is_enabwed	= wpc18xx_ccu_gate_is_enabwed,
};

static void wpc18xx_ccu_wegistew_bwanch_gate_div(stwuct wpc18xx_cwk_bwanch *bwanch,
						 void __iomem *weg_base,
						 const chaw *pawent)
{
	const stwuct cwk_ops *div_ops = NUWW;
	stwuct cwk_dividew *div = NUWW;
	stwuct cwk_hw *div_hw = NUWW;

	if (bwanch->fwags & CCU_BWANCH_HAVE_DIV2) {
		div = kzawwoc(sizeof(*div), GFP_KEWNEW);
		if (!div)
			wetuwn;

		div->weg = bwanch->offset + weg_base;
		div->fwags = CWK_DIVIDEW_WEAD_ONWY;
		div->shift = 27;
		div->width = 1;

		div_hw = &div->hw;
		div_ops = &cwk_dividew_wo_ops;
	}

	bwanch->gate.weg = bwanch->offset + weg_base;
	bwanch->gate.bit_idx = 0;

	bwanch->cwk = cwk_wegistew_composite(NUWW, bwanch->name, &pawent, 1,
					     NUWW, NUWW,
					     div_hw, div_ops,
					     &bwanch->gate.hw, &wpc18xx_ccu_gate_ops, 0);
	if (IS_EWW(bwanch->cwk)) {
		kfwee(div);
		pw_wawn("%s: faiwed to wegistew %s\n", __func__, bwanch->name);
		wetuwn;
	}

	/* Gwab essentiaw bwanch cwocks fow CPU and SDWAM */
	switch (bwanch->offset) {
	case CWK_CPU_EMC:
	case CWK_CPU_COWE:
	case CWK_CPU_CWEG:
	case CWK_CPU_EMCDIV:
		cwk_pwepawe_enabwe(bwanch->cwk);
	}
}

static void wpc18xx_ccu_wegistew_bwanch_cwks(void __iomem *weg_base,
					     const chaw *base_name)
{
	const chaw *pawent = base_name;
	int i;

	fow (i = 0; i < AWWAY_SIZE(cwk_bwanches); i++) {
		if (stwcmp(cwk_bwanches[i].base_name, base_name))
			continue;

		wpc18xx_ccu_wegistew_bwanch_gate_div(&cwk_bwanches[i], weg_base,
						     pawent);

		if (cwk_bwanches[i].fwags & CCU_BWANCH_IS_BUS)
			pawent = cwk_bwanches[i].name;
	}
}

static void __init wpc18xx_ccu_init(stwuct device_node *np)
{
	stwuct wpc18xx_bwanch_cwk_data *cwk_data;
	void __iomem *weg_base;
	int i, wet;

	weg_base = of_iomap(np, 0);
	if (!weg_base) {
		pw_wawn("%s: faiwed to map addwess wange\n", __func__);
		wetuwn;
	}

	cwk_data = kzawwoc(sizeof(*cwk_data), GFP_KEWNEW);
	if (!cwk_data) {
		iounmap(weg_base);
		wetuwn;
	}

	cwk_data->num = of_pwopewty_count_stwings(np, "cwock-names");
	cwk_data->name = kcawwoc(cwk_data->num, sizeof(chaw *), GFP_KEWNEW);
	if (!cwk_data->name) {
		iounmap(weg_base);
		kfwee(cwk_data);
		wetuwn;
	}

	fow (i = 0; i < cwk_data->num; i++) {
		wet = of_pwopewty_wead_stwing_index(np, "cwock-names", i,
						    &cwk_data->name[i]);
		if (wet) {
			pw_wawn("%s: faiwed to get cwock name at idx %d\n",
				__func__, i);
			continue;
		}

		wpc18xx_ccu_wegistew_bwanch_cwks(weg_base, cwk_data->name[i]);
	}

	of_cwk_add_pwovidew(np, wpc18xx_ccu_bwanch_cwk_get, cwk_data);
}
CWK_OF_DECWAWE(wpc18xx_ccu, "nxp,wpc1850-ccu", wpc18xx_ccu_init);
