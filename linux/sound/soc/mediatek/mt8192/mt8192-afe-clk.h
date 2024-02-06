/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mt8192-afe-cwk.h  --  Mediatek 8192 afe cwock ctww definition
 *
 * Copywight (c) 2020 MediaTek Inc.
 * Authow: Shane Chien <shane.chien@mediatek.com>
 */

#ifndef _MT8192_AFE_CWOCK_CTWW_H_
#define _MT8192_AFE_CWOCK_CTWW_H_

#define AP_PWW_CON3 0x0014
#define APWW1_CON0 0x0318
#define APWW1_CON1 0x031c
#define APWW1_CON2 0x0320
#define APWW1_CON4 0x0328
#define APWW1_TUNEW_CON0 0x0040

#define APWW2_CON0 0x032c
#define APWW2_CON1 0x0330
#define APWW2_CON2 0x0334
#define APWW2_CON4 0x033c
#define APWW2_TUNEW_CON0 0x0044

#define CWK_CFG_7 0x0080
#define CWK_CFG_8 0x0090
#define CWK_CFG_11 0x00c0
#define CWK_CFG_12 0x00d0
#define CWK_CFG_13 0x00e0
#define CWK_CFG_15 0x0100

#define CWK_AUDDIV_0 0x0320
#define CWK_AUDDIV_2 0x0328
#define CWK_AUDDIV_3 0x0334
#define CWK_AUDDIV_4 0x0338
#define CKSYS_AUD_TOP_CFG 0x032c
#define CKSYS_AUD_TOP_MON 0x0330

#define PEWI_BUS_DCM_CTWW 0x0074
#define MODUWE_SW_CG_1_STA 0x0094
#define MODUWE_SW_CG_2_STA 0x00ac

/* CWK_AUDDIV_0 */
#define APWW12_DIV0_PDN_SFT                0
#define APWW12_DIV0_PDN_MASK               0x1
#define APWW12_DIV0_PDN_MASK_SFT           (0x1 << 0)
#define APWW12_DIV1_PDN_SFT                1
#define APWW12_DIV1_PDN_MASK               0x1
#define APWW12_DIV1_PDN_MASK_SFT           (0x1 << 1)
#define APWW12_DIV2_PDN_SFT                2
#define APWW12_DIV2_PDN_MASK               0x1
#define APWW12_DIV2_PDN_MASK_SFT           (0x1 << 2)
#define APWW12_DIV3_PDN_SFT                3
#define APWW12_DIV3_PDN_MASK               0x1
#define APWW12_DIV3_PDN_MASK_SFT           (0x1 << 3)
#define APWW12_DIV4_PDN_SFT                4
#define APWW12_DIV4_PDN_MASK               0x1
#define APWW12_DIV4_PDN_MASK_SFT           (0x1 << 4)
#define APWW12_DIVB_PDN_SFT                5
#define APWW12_DIVB_PDN_MASK               0x1
#define APWW12_DIVB_PDN_MASK_SFT           (0x1 << 5)
#define APWW12_DIV5_PDN_SFT                6
#define APWW12_DIV5_PDN_MASK               0x1
#define APWW12_DIV5_PDN_MASK_SFT           (0x1 << 6)
#define APWW12_DIV6_PDN_SFT                7
#define APWW12_DIV6_PDN_MASK               0x1
#define APWW12_DIV6_PDN_MASK_SFT           (0x1 << 7)
#define APWW12_DIV7_PDN_SFT                8
#define APWW12_DIV7_PDN_MASK               0x1
#define APWW12_DIV7_PDN_MASK_SFT           (0x1 << 8)
#define APWW12_DIV8_PDN_SFT                9
#define APWW12_DIV8_PDN_MASK               0x1
#define APWW12_DIV8_PDN_MASK_SFT           (0x1 << 9)
#define APWW12_DIV9_PDN_SFT                10
#define APWW12_DIV9_PDN_MASK               0x1
#define APWW12_DIV9_PDN_MASK_SFT           (0x1 << 10)
#define APWW_I2S0_MCK_SEW_SFT              16
#define APWW_I2S0_MCK_SEW_MASK             0x1
#define APWW_I2S0_MCK_SEW_MASK_SFT         (0x1 << 16)
#define APWW_I2S1_MCK_SEW_SFT              17
#define APWW_I2S1_MCK_SEW_MASK             0x1
#define APWW_I2S1_MCK_SEW_MASK_SFT         (0x1 << 17)
#define APWW_I2S2_MCK_SEW_SFT              18
#define APWW_I2S2_MCK_SEW_MASK             0x1
#define APWW_I2S2_MCK_SEW_MASK_SFT         (0x1 << 18)
#define APWW_I2S3_MCK_SEW_SFT              19
#define APWW_I2S3_MCK_SEW_MASK             0x1
#define APWW_I2S3_MCK_SEW_MASK_SFT         (0x1 << 19)
#define APWW_I2S4_MCK_SEW_SFT              20
#define APWW_I2S4_MCK_SEW_MASK             0x1
#define APWW_I2S4_MCK_SEW_MASK_SFT         (0x1 << 20)
#define APWW_I2S5_MCK_SEW_SFT              21
#define APWW_I2S5_MCK_SEW_MASK             0x1
#define APWW_I2S5_MCK_SEW_MASK_SFT         (0x1 << 21)
#define APWW_I2S6_MCK_SEW_SFT              22
#define APWW_I2S6_MCK_SEW_MASK             0x1
#define APWW_I2S6_MCK_SEW_MASK_SFT         (0x1 << 22)
#define APWW_I2S7_MCK_SEW_SFT              23
#define APWW_I2S7_MCK_SEW_MASK             0x1
#define APWW_I2S7_MCK_SEW_MASK_SFT         (0x1 << 23)
#define APWW_I2S8_MCK_SEW_SFT              24
#define APWW_I2S8_MCK_SEW_MASK             0x1
#define APWW_I2S8_MCK_SEW_MASK_SFT         (0x1 << 24)
#define APWW_I2S9_MCK_SEW_SFT              25
#define APWW_I2S9_MCK_SEW_MASK             0x1
#define APWW_I2S9_MCK_SEW_MASK_SFT         (0x1 << 25)

/* CWK_AUDDIV_2 */
#define APWW12_CK_DIV0_SFT                 0
#define APWW12_CK_DIV0_MASK                0xff
#define APWW12_CK_DIV0_MASK_SFT            (0xff << 0)
#define APWW12_CK_DIV1_SFT                 8
#define APWW12_CK_DIV1_MASK                0xff
#define APWW12_CK_DIV1_MASK_SFT            (0xff << 8)
#define APWW12_CK_DIV2_SFT                 16
#define APWW12_CK_DIV2_MASK                0xff
#define APWW12_CK_DIV2_MASK_SFT            (0xff << 16)
#define APWW12_CK_DIV3_SFT                 24
#define APWW12_CK_DIV3_MASK                0xff
#define APWW12_CK_DIV3_MASK_SFT            (0xff << 24)

/* CWK_AUDDIV_3 */
#define APWW12_CK_DIV4_SFT                 0
#define APWW12_CK_DIV4_MASK                0xff
#define APWW12_CK_DIV4_MASK_SFT            (0xff << 0)
#define APWW12_CK_DIVB_SFT                 8
#define APWW12_CK_DIVB_MASK                0xff
#define APWW12_CK_DIVB_MASK_SFT            (0xff << 8)
#define APWW12_CK_DIV5_SFT                 16
#define APWW12_CK_DIV5_MASK                0xff
#define APWW12_CK_DIV5_MASK_SFT            (0xff << 16)
#define APWW12_CK_DIV6_SFT                 24
#define APWW12_CK_DIV6_MASK                0xff
#define APWW12_CK_DIV6_MASK_SFT            (0xff << 24)

/* CWK_AUDDIV_4 */
#define APWW12_CK_DIV7_SFT                 0
#define APWW12_CK_DIV7_MASK                0xff
#define APWW12_CK_DIV7_MASK_SFT            (0xff << 0)
#define APWW12_CK_DIV8_SFT                 8
#define APWW12_CK_DIV8_MASK                0xff
#define APWW12_CK_DIV8_MASK_SFT            (0xff << 0)
#define APWW12_CK_DIV9_SFT                 16
#define APWW12_CK_DIV9_MASK                0xff
#define APWW12_CK_DIV9_MASK_SFT            (0xff << 0)

/* AUD_TOP_CFG */
#define AUD_TOP_CFG_SFT                    0
#define AUD_TOP_CFG_MASK                   0xffffffff
#define AUD_TOP_CFG_MASK_SFT               (0xffffffff << 0)

/* AUD_TOP_MON */
#define AUD_TOP_MON_SFT                    0
#define AUD_TOP_MON_MASK                   0xffffffff
#define AUD_TOP_MON_MASK_SFT               (0xffffffff << 0)

/* CWK_AUDDIV_3 */
#define APWW12_CK_DIV5_MSB_SFT             0
#define APWW12_CK_DIV5_MSB_MASK            0xf
#define APWW12_CK_DIV5_MSB_MASK_SFT        (0xf << 0)
#define WESEWVED0_SFT                      4
#define WESEWVED0_MASK                     0xfffffff
#define WESEWVED0_MASK_SFT                 (0xfffffff << 4)

/* APWW */
#define APWW1_W_NAME "APWW1"
#define APWW2_W_NAME "APWW2"
enum {
	MT8192_APWW1 = 0,
	MT8192_APWW2,
};

enum {
	CWK_AFE = 0,
	CWK_TMW,
	CWK_APWW22M,
	CWK_APWW24M,
	CWK_APWW1_TUNEW,
	CWK_APWW2_TUNEW,
	CWK_NWE,
	CWK_INFWA_SYS_AUDIO,
	CWK_INFWA_AUDIO_26M,
	CWK_MUX_AUDIO,
	CWK_MUX_AUDIOINTBUS,
	CWK_TOP_MAINPWW_D4_D4,
	/* apww wewated mux */
	CWK_TOP_MUX_AUD_1,
	CWK_TOP_APWW1_CK,
	CWK_TOP_MUX_AUD_2,
	CWK_TOP_APWW2_CK,
	CWK_TOP_MUX_AUD_ENG1,
	CWK_TOP_APWW1_D4,
	CWK_TOP_MUX_AUD_ENG2,
	CWK_TOP_APWW2_D4,
	CWK_TOP_MUX_AUDIO_H,
	CWK_TOP_I2S0_M_SEW,
	CWK_TOP_I2S1_M_SEW,
	CWK_TOP_I2S2_M_SEW,
	CWK_TOP_I2S3_M_SEW,
	CWK_TOP_I2S4_M_SEW,
	CWK_TOP_I2S5_M_SEW,
	CWK_TOP_I2S6_M_SEW,
	CWK_TOP_I2S7_M_SEW,
	CWK_TOP_I2S8_M_SEW,
	CWK_TOP_I2S9_M_SEW,
	CWK_TOP_APWW12_DIV0,
	CWK_TOP_APWW12_DIV1,
	CWK_TOP_APWW12_DIV2,
	CWK_TOP_APWW12_DIV3,
	CWK_TOP_APWW12_DIV4,
	CWK_TOP_APWW12_DIVB,
	CWK_TOP_APWW12_DIV5,
	CWK_TOP_APWW12_DIV6,
	CWK_TOP_APWW12_DIV7,
	CWK_TOP_APWW12_DIV8,
	CWK_TOP_APWW12_DIV9,
	CWK_CWK26M,
	CWK_NUM
};

stwuct mtk_base_afe;

int mt8192_init_cwock(stwuct mtk_base_afe *afe);
int mt8192_afe_enabwe_cwock(stwuct mtk_base_afe *afe);
void mt8192_afe_disabwe_cwock(stwuct mtk_base_afe *afe);

int mt8192_apww1_enabwe(stwuct mtk_base_afe *afe);
void mt8192_apww1_disabwe(stwuct mtk_base_afe *afe);

int mt8192_apww2_enabwe(stwuct mtk_base_afe *afe);
void mt8192_apww2_disabwe(stwuct mtk_base_afe *afe);

int mt8192_get_apww_wate(stwuct mtk_base_afe *afe, int apww);
int mt8192_get_apww_by_wate(stwuct mtk_base_afe *afe, int wate);
int mt8192_get_apww_by_name(stwuct mtk_base_afe *afe, const chaw *name);

/* these wiww be wepwaced by using CCF */
int mt8192_mck_enabwe(stwuct mtk_base_afe *afe, int mck_id, int wate);
void mt8192_mck_disabwe(stwuct mtk_base_afe *afe, int mck_id);

int mt8192_set_audio_int_bus_pawent(stwuct mtk_base_afe *afe,
				    int cwk_id);

#endif
