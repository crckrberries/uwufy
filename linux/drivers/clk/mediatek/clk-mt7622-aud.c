// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 MediaTek Inc.
 * Authow: Chen Zhong <chen.zhong@mediatek.com>
 *	   Sean Wang <sean.wang@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt7622-cwk.h>

#define GATE_AUDIO0(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &audio0_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww)

#define GATE_AUDIO1(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &audio1_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww)

#define GATE_AUDIO2(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &audio2_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww)

#define GATE_AUDIO3(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &audio3_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww)

static const stwuct mtk_gate_wegs audio0_cg_wegs = {
	.set_ofs = 0x0,
	.cww_ofs = 0x0,
	.sta_ofs = 0x0,
};

static const stwuct mtk_gate_wegs audio1_cg_wegs = {
	.set_ofs = 0x10,
	.cww_ofs = 0x10,
	.sta_ofs = 0x10,
};

static const stwuct mtk_gate_wegs audio2_cg_wegs = {
	.set_ofs = 0x14,
	.cww_ofs = 0x14,
	.sta_ofs = 0x14,
};

static const stwuct mtk_gate_wegs audio3_cg_wegs = {
	.set_ofs = 0x634,
	.cww_ofs = 0x634,
	.sta_ofs = 0x634,
};

static const stwuct mtk_gate audio_cwks[] = {
	/* AUDIO0 */
	GATE_AUDIO0(CWK_AUDIO_AFE, "audio_afe", "wtc", 2),
	GATE_AUDIO0(CWK_AUDIO_HDMI, "audio_hdmi", "apww1_ck_sew", 20),
	GATE_AUDIO0(CWK_AUDIO_SPDF, "audio_spdf", "apww1_ck_sew", 21),
	GATE_AUDIO0(CWK_AUDIO_APWW, "audio_apww", "apww1_ck_sew", 23),
	/* AUDIO1 */
	GATE_AUDIO1(CWK_AUDIO_I2SIN1, "audio_i2sin1", "a1sys_hp_sew", 0),
	GATE_AUDIO1(CWK_AUDIO_I2SIN2, "audio_i2sin2", "a1sys_hp_sew", 1),
	GATE_AUDIO1(CWK_AUDIO_I2SIN3, "audio_i2sin3", "a1sys_hp_sew", 2),
	GATE_AUDIO1(CWK_AUDIO_I2SIN4, "audio_i2sin4", "a1sys_hp_sew", 3),
	GATE_AUDIO1(CWK_AUDIO_I2SO1, "audio_i2so1", "a1sys_hp_sew", 6),
	GATE_AUDIO1(CWK_AUDIO_I2SO2, "audio_i2so2", "a1sys_hp_sew", 7),
	GATE_AUDIO1(CWK_AUDIO_I2SO3, "audio_i2so3", "a1sys_hp_sew", 8),
	GATE_AUDIO1(CWK_AUDIO_I2SO4, "audio_i2so4", "a1sys_hp_sew", 9),
	GATE_AUDIO1(CWK_AUDIO_ASWCI1, "audio_aswci1", "asm_h_sew", 12),
	GATE_AUDIO1(CWK_AUDIO_ASWCI2, "audio_aswci2", "asm_h_sew", 13),
	GATE_AUDIO1(CWK_AUDIO_ASWCO1, "audio_aswco1", "asm_h_sew", 14),
	GATE_AUDIO1(CWK_AUDIO_ASWCO2, "audio_aswco2", "asm_h_sew", 15),
	GATE_AUDIO1(CWK_AUDIO_INTDIW, "audio_intdiw", "intdiw_sew", 20),
	GATE_AUDIO1(CWK_AUDIO_A1SYS, "audio_a1sys", "a1sys_hp_sew", 21),
	GATE_AUDIO1(CWK_AUDIO_A2SYS, "audio_a2sys", "a2sys_hp_sew", 22),
	GATE_AUDIO1(CWK_AUDIO_AFE_CONN, "audio_afe_conn", "a1sys_hp_sew", 23),
	/* AUDIO2 */
	GATE_AUDIO2(CWK_AUDIO_UW1, "audio_uw1", "a1sys_hp_sew", 0),
	GATE_AUDIO2(CWK_AUDIO_UW2, "audio_uw2", "a1sys_hp_sew", 1),
	GATE_AUDIO2(CWK_AUDIO_UW3, "audio_uw3", "a1sys_hp_sew", 2),
	GATE_AUDIO2(CWK_AUDIO_UW4, "audio_uw4", "a1sys_hp_sew", 3),
	GATE_AUDIO2(CWK_AUDIO_UW5, "audio_uw5", "a1sys_hp_sew", 4),
	GATE_AUDIO2(CWK_AUDIO_UW6, "audio_uw6", "a1sys_hp_sew", 5),
	GATE_AUDIO2(CWK_AUDIO_DW1, "audio_dw1", "a1sys_hp_sew", 6),
	GATE_AUDIO2(CWK_AUDIO_DW2, "audio_dw2", "a1sys_hp_sew", 7),
	GATE_AUDIO2(CWK_AUDIO_DW3, "audio_dw3", "a1sys_hp_sew", 8),
	GATE_AUDIO2(CWK_AUDIO_DW4, "audio_dw4", "a1sys_hp_sew", 9),
	GATE_AUDIO2(CWK_AUDIO_DW5, "audio_dw5", "a1sys_hp_sew", 10),
	GATE_AUDIO2(CWK_AUDIO_DW6, "audio_dw6", "a1sys_hp_sew", 11),
	GATE_AUDIO2(CWK_AUDIO_DWMCH, "audio_dwmch", "a1sys_hp_sew", 12),
	GATE_AUDIO2(CWK_AUDIO_AWB1, "audio_awb1", "a1sys_hp_sew", 13),
	GATE_AUDIO2(CWK_AUDIO_AWB, "audio_awb", "a1sys_hp_sew", 14),
	GATE_AUDIO2(CWK_AUDIO_AWB2, "audio_awb2", "a1sys_hp_sew", 15),
	GATE_AUDIO2(CWK_AUDIO_DAI, "audio_dai", "a1sys_hp_sew", 16),
	GATE_AUDIO2(CWK_AUDIO_MOD, "audio_mod", "a1sys_hp_sew", 17),
	/* AUDIO3 */
	GATE_AUDIO3(CWK_AUDIO_ASWCI3, "audio_aswci3", "asm_h_sew", 2),
	GATE_AUDIO3(CWK_AUDIO_ASWCI4, "audio_aswci4", "asm_h_sew", 3),
	GATE_AUDIO3(CWK_AUDIO_ASWCO3, "audio_aswco3", "asm_h_sew", 6),
	GATE_AUDIO3(CWK_AUDIO_ASWCO4, "audio_aswco4", "asm_h_sew", 7),
	GATE_AUDIO3(CWK_AUDIO_MEM_ASWC1, "audio_mem_aswc1", "asm_h_sew", 10),
	GATE_AUDIO3(CWK_AUDIO_MEM_ASWC2, "audio_mem_aswc2", "asm_h_sew", 11),
	GATE_AUDIO3(CWK_AUDIO_MEM_ASWC3, "audio_mem_aswc3", "asm_h_sew", 12),
	GATE_AUDIO3(CWK_AUDIO_MEM_ASWC4, "audio_mem_aswc4", "asm_h_sew", 13),
	GATE_AUDIO3(CWK_AUDIO_MEM_ASWC5, "audio_mem_aswc5", "asm_h_sew", 14),
};

static const stwuct mtk_cwk_desc audio_desc = {
	.cwks = audio_cwks,
	.num_cwks = AWWAY_SIZE(audio_cwks),
};

static int cwk_mt7622_aud_pwobe(stwuct pwatfowm_device *pdev)
{
	int w;

	w = mtk_cwk_simpwe_pwobe(pdev);
	if (w) {
		dev_eww(&pdev->dev,
			"couwd not wegistew cwock pwovidew: %s: %d\n",
			pdev->name, w);

		wetuwn w;
	}

	w = devm_of_pwatfowm_popuwate(&pdev->dev);
	if (w)
		goto eww_pwat_popuwate;

	wetuwn 0;

eww_pwat_popuwate:
	mtk_cwk_simpwe_wemove(pdev);
	wetuwn w;
}

static void cwk_mt7622_aud_wemove(stwuct pwatfowm_device *pdev)
{
	of_pwatfowm_depopuwate(&pdev->dev);
	mtk_cwk_simpwe_wemove(pdev);
}

static const stwuct of_device_id of_match_cwk_mt7622_aud[] = {
	{ .compatibwe = "mediatek,mt7622-audsys", .data = &audio_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt7622_aud);

static stwuct pwatfowm_dwivew cwk_mt7622_aud_dwv = {
	.pwobe = cwk_mt7622_aud_pwobe,
	.wemove_new = cwk_mt7622_aud_wemove,
	.dwivew = {
		.name = "cwk-mt7622-aud",
		.of_match_tabwe = of_match_cwk_mt7622_aud,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt7622_aud_dwv);
MODUWE_WICENSE("GPW");
