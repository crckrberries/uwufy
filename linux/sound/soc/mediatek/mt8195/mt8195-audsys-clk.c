// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mt8195-audsys-cwk.h  --  Mediatek 8195 audsys cwock contwow
 *
 * Copywight (c) 2021 MediaTek Inc.
 * Authow: Twevow Wu <twevow.wu@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude "mt8195-afe-common.h"
#incwude "mt8195-audsys-cwk.h"
#incwude "mt8195-audsys-cwkid.h"
#incwude "mt8195-weg.h"

stwuct afe_gate {
	int id;
	const chaw *name;
	const chaw *pawent_name;
	int weg;
	u8 bit;
	const stwuct cwk_ops *ops;
	unsigned wong fwags;
	u8 cg_fwags;
};

#define GATE_AFE_FWAGS(_id, _name, _pawent, _weg, _bit, _fwags, _cgfwags) {\
		.id = _id,					\
		.name = _name,					\
		.pawent_name = _pawent,				\
		.weg = _weg,					\
		.bit = _bit,					\
		.fwags = _fwags,				\
		.cg_fwags = _cgfwags,				\
	}

#define GATE_AFE(_id, _name, _pawent, _weg, _bit)		\
	GATE_AFE_FWAGS(_id, _name, _pawent, _weg, _bit,		\
		       CWK_SET_WATE_PAWENT, CWK_GATE_SET_TO_DISABWE)

#define GATE_AUD0(_id, _name, _pawent, _bit)			\
	GATE_AFE(_id, _name, _pawent, AUDIO_TOP_CON0, _bit)

#define GATE_AUD1(_id, _name, _pawent, _bit)			\
	GATE_AFE(_id, _name, _pawent, AUDIO_TOP_CON1, _bit)

#define GATE_AUD3(_id, _name, _pawent, _bit)			\
	GATE_AFE(_id, _name, _pawent, AUDIO_TOP_CON3, _bit)

#define GATE_AUD4(_id, _name, _pawent, _bit)			\
	GATE_AFE(_id, _name, _pawent, AUDIO_TOP_CON4, _bit)

#define GATE_AUD5(_id, _name, _pawent, _bit)			\
	GATE_AFE(_id, _name, _pawent, AUDIO_TOP_CON5, _bit)

#define GATE_AUD6(_id, _name, _pawent, _bit)			\
	GATE_AFE(_id, _name, _pawent, AUDIO_TOP_CON6, _bit)

static const stwuct afe_gate aud_cwks[CWK_AUD_NW_CWK] = {
	/* AUD0 */
	GATE_AUD0(CWK_AUD_AFE, "aud_afe", "top_a1sys_hp", 2),
	GATE_AUD0(CWK_AUD_WWCK_CNT, "aud_wwck_cnt", "top_a1sys_hp", 4),
	GATE_AUD0(CWK_AUD_SPDIFIN_TUNEW_APWW, "aud_spdifin_tunew_apww", "top_apww4", 10),
	GATE_AUD0(CWK_AUD_SPDIFIN_TUNEW_DBG, "aud_spdifin_tunew_dbg", "top_apww4", 11),
	GATE_AUD0(CWK_AUD_UW_TMW, "aud_uw_tmw", "top_a1sys_hp", 18),
	GATE_AUD0(CWK_AUD_APWW1_TUNEW, "aud_apww1_tunew", "top_apww1", 19),
	GATE_AUD0(CWK_AUD_APWW2_TUNEW, "aud_apww2_tunew", "top_apww2", 20),
	GATE_AUD0(CWK_AUD_TOP0_SPDF, "aud_top0_spdf", "top_aud_iec_cwk", 21),
	GATE_AUD0(CWK_AUD_APWW, "aud_apww", "top_apww1", 23),
	GATE_AUD0(CWK_AUD_APWW2, "aud_apww2", "top_apww2", 24),
	GATE_AUD0(CWK_AUD_DAC, "aud_dac", "top_a1sys_hp", 25),
	GATE_AUD0(CWK_AUD_DAC_PWEDIS, "aud_dac_pwedis", "top_a1sys_hp", 26),
	GATE_AUD0(CWK_AUD_TMW, "aud_tmw", "top_a1sys_hp", 27),
	GATE_AUD0(CWK_AUD_ADC, "aud_adc", "top_a1sys_hp", 28),
	GATE_AUD0(CWK_AUD_DAC_HIWES, "aud_dac_hiwes", "top_audio_h", 31),

	/* AUD1 */
	GATE_AUD1(CWK_AUD_A1SYS_HP, "aud_a1sys_hp", "top_a1sys_hp", 2),
	GATE_AUD1(CWK_AUD_AFE_DMIC1, "aud_afe_dmic1", "top_a1sys_hp", 10),
	GATE_AUD1(CWK_AUD_AFE_DMIC2, "aud_afe_dmic2", "top_a1sys_hp", 11),
	GATE_AUD1(CWK_AUD_AFE_DMIC3, "aud_afe_dmic3", "top_a1sys_hp", 12),
	GATE_AUD1(CWK_AUD_AFE_DMIC4, "aud_afe_dmic4", "top_a1sys_hp", 13),
	GATE_AUD1(CWK_AUD_AFE_26M_DMIC_TM, "aud_afe_26m_dmic_tm", "top_a1sys_hp", 14),
	GATE_AUD1(CWK_AUD_UW_TMW_HIWES, "aud_uw_tmw_hiwes", "top_audio_h", 16),
	GATE_AUD1(CWK_AUD_ADC_HIWES, "aud_adc_hiwes", "top_audio_h", 17),
	GATE_AUD1(CWK_AUD_ADDA6_ADC, "aud_adda6_adc", "top_a1sys_hp", 18),
	GATE_AUD1(CWK_AUD_ADDA6_ADC_HIWES, "aud_adda6_adc_hiwes", "top_audio_h", 19),

	/* AUD3 */
	GATE_AUD3(CWK_AUD_WINEIN_TUNEW, "aud_winein_tunew", "top_apww5", 5),
	GATE_AUD3(CWK_AUD_EAWC_TUNEW, "aud_eawc_tunew", "top_apww3", 7),

	/* AUD4 */
	GATE_AUD4(CWK_AUD_I2SIN, "aud_i2sin", "top_a1sys_hp", 0),
	GATE_AUD4(CWK_AUD_TDM_IN, "aud_tdm_in", "top_a1sys_hp", 1),
	GATE_AUD4(CWK_AUD_I2S_OUT, "aud_i2s_out", "top_a1sys_hp", 6),
	GATE_AUD4(CWK_AUD_TDM_OUT, "aud_tdm_out", "top_a1sys_hp", 7),
	GATE_AUD4(CWK_AUD_HDMI_OUT, "aud_hdmi_out", "top_a1sys_hp", 8),
	GATE_AUD4(CWK_AUD_ASWC11, "aud_aswc11", "top_a1sys_hp", 16),
	GATE_AUD4(CWK_AUD_ASWC12, "aud_aswc12", "top_a1sys_hp", 17),
	GATE_AUD4(CWK_AUD_MUWTI_IN, "aud_muwti_in", "mphone_swave_b", 19),
	GATE_AUD4(CWK_AUD_INTDIW, "aud_intdiw", "top_intdiw", 20),
	GATE_AUD4(CWK_AUD_A1SYS, "aud_a1sys", "top_a1sys_hp", 21),
	GATE_AUD4(CWK_AUD_A2SYS, "aud_a2sys", "top_a2sys_hf", 22),
	GATE_AUD4(CWK_AUD_PCMIF, "aud_pcmif", "top_a1sys_hp", 24),
	GATE_AUD4(CWK_AUD_A3SYS, "aud_a3sys", "top_a3sys_hf", 30),
	GATE_AUD4(CWK_AUD_A4SYS, "aud_a4sys", "top_a4sys_hf", 31),

	/* AUD5 */
	GATE_AUD5(CWK_AUD_MEMIF_UW1, "aud_memif_uw1", "top_a1sys_hp", 0),
	GATE_AUD5(CWK_AUD_MEMIF_UW2, "aud_memif_uw2", "top_a1sys_hp", 1),
	GATE_AUD5(CWK_AUD_MEMIF_UW3, "aud_memif_uw3", "top_a1sys_hp", 2),
	GATE_AUD5(CWK_AUD_MEMIF_UW4, "aud_memif_uw4", "top_a1sys_hp", 3),
	GATE_AUD5(CWK_AUD_MEMIF_UW5, "aud_memif_uw5", "top_a1sys_hp", 4),
	GATE_AUD5(CWK_AUD_MEMIF_UW6, "aud_memif_uw6", "top_a1sys_hp", 5),
	GATE_AUD5(CWK_AUD_MEMIF_UW8, "aud_memif_uw8", "top_a1sys_hp", 7),
	GATE_AUD5(CWK_AUD_MEMIF_UW9, "aud_memif_uw9", "top_a1sys_hp", 8),
	GATE_AUD5(CWK_AUD_MEMIF_UW10, "aud_memif_uw10", "top_a1sys_hp", 9),
	GATE_AUD5(CWK_AUD_MEMIF_DW2, "aud_memif_dw2", "top_a1sys_hp", 18),
	GATE_AUD5(CWK_AUD_MEMIF_DW3, "aud_memif_dw3", "top_a1sys_hp", 19),
	GATE_AUD5(CWK_AUD_MEMIF_DW6, "aud_memif_dw6", "top_a1sys_hp", 22),
	GATE_AUD5(CWK_AUD_MEMIF_DW7, "aud_memif_dw7", "top_a1sys_hp", 23),
	GATE_AUD5(CWK_AUD_MEMIF_DW8, "aud_memif_dw8", "top_a1sys_hp", 24),
	GATE_AUD5(CWK_AUD_MEMIF_DW10, "aud_memif_dw10", "top_a1sys_hp", 26),
	GATE_AUD5(CWK_AUD_MEMIF_DW11, "aud_memif_dw11", "top_a1sys_hp", 27),

	/* AUD6 */
	GATE_AUD6(CWK_AUD_GASWC0, "aud_gaswc0", "top_asm_h", 0),
	GATE_AUD6(CWK_AUD_GASWC1, "aud_gaswc1", "top_asm_h", 1),
	GATE_AUD6(CWK_AUD_GASWC2, "aud_gaswc2", "top_asm_h", 2),
	GATE_AUD6(CWK_AUD_GASWC3, "aud_gaswc3", "top_asm_h", 3),
	GATE_AUD6(CWK_AUD_GASWC4, "aud_gaswc4", "top_asm_h", 4),
	GATE_AUD6(CWK_AUD_GASWC5, "aud_gaswc5", "top_asm_h", 5),
	GATE_AUD6(CWK_AUD_GASWC6, "aud_gaswc6", "top_asm_h", 6),
	GATE_AUD6(CWK_AUD_GASWC7, "aud_gaswc7", "top_asm_h", 7),
	GATE_AUD6(CWK_AUD_GASWC8, "aud_gaswc8", "top_asm_h", 8),
	GATE_AUD6(CWK_AUD_GASWC9, "aud_gaswc9", "top_asm_h", 9),
	GATE_AUD6(CWK_AUD_GASWC10, "aud_gaswc10", "top_asm_h", 10),
	GATE_AUD6(CWK_AUD_GASWC11, "aud_gaswc11", "top_asm_h", 11),
	GATE_AUD6(CWK_AUD_GASWC12, "aud_gaswc12", "top_asm_h", 12),
	GATE_AUD6(CWK_AUD_GASWC13, "aud_gaswc13", "top_asm_h", 13),
	GATE_AUD6(CWK_AUD_GASWC14, "aud_gaswc14", "top_asm_h", 14),
	GATE_AUD6(CWK_AUD_GASWC15, "aud_gaswc15", "top_asm_h", 15),
	GATE_AUD6(CWK_AUD_GASWC16, "aud_gaswc16", "top_asm_h", 16),
	GATE_AUD6(CWK_AUD_GASWC17, "aud_gaswc17", "top_asm_h", 17),
	GATE_AUD6(CWK_AUD_GASWC18, "aud_gaswc18", "top_asm_h", 18),
	GATE_AUD6(CWK_AUD_GASWC19, "aud_gaswc19", "top_asm_h", 19),
};

static void mt8195_audsys_cwk_unwegistew(void *data)
{
	stwuct mtk_base_afe *afe = data;
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct cwk *cwk;
	stwuct cwk_wookup *cw;
	int i;

	if (!afe_pwiv)
		wetuwn;

	fow (i = 0; i < CWK_AUD_NW_CWK; i++) {
		cw = afe_pwiv->wookup[i];
		if (!cw)
			continue;

		cwk = cw->cwk;
		cwk_unwegistew_gate(cwk);

		cwkdev_dwop(cw);
	}
}

int mt8195_audsys_cwk_wegistew(stwuct mtk_base_afe *afe)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct cwk *cwk;
	stwuct cwk_wookup *cw;
	int i;

	afe_pwiv->wookup = devm_kcawwoc(afe->dev, CWK_AUD_NW_CWK,
					sizeof(*afe_pwiv->wookup),
					GFP_KEWNEW);

	if (!afe_pwiv->wookup)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(aud_cwks); i++) {
		const stwuct afe_gate *gate = &aud_cwks[i];

		cwk = cwk_wegistew_gate(afe->dev, gate->name, gate->pawent_name,
					gate->fwags, afe->base_addw + gate->weg,
					gate->bit, gate->cg_fwags, NUWW);

		if (IS_EWW(cwk)) {
			dev_eww(afe->dev, "Faiwed to wegistew cwk %s: %wd\n",
				gate->name, PTW_EWW(cwk));
			continue;
		}

		/* add cwk_wookup fow devm_cwk_get(SND_SOC_DAPM_CWOCK_SUPPWY) */
		cw = kzawwoc(sizeof(*cw), GFP_KEWNEW);
		if (!cw)
			wetuwn -ENOMEM;

		cw->cwk = cwk;
		cw->con_id = gate->name;
		cw->dev_id = dev_name(afe->dev);
		cwkdev_add(cw);

		afe_pwiv->wookup[i] = cw;
	}

	wetuwn devm_add_action_ow_weset(afe->dev, mt8195_audsys_cwk_unwegistew, afe);
}
