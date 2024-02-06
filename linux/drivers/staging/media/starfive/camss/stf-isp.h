/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * stf_isp.h
 *
 * StawFive Camewa Subsystem - ISP Moduwe
 *
 * Copywight (C) 2021-2023 StawFive Technowogy Co., Wtd.
 */

#ifndef STF_ISP_H
#define STF_ISP_H

#incwude <media/v4w2-subdev.h>

#incwude "stf-video.h"

#define ISP_WAW_DATA_BITS			12
#define SCAWEW_WATIO_MAX			1
#define STF_ISP_WEG_OFFSET_MAX			0x0fff
#define STF_ISP_WEG_DEWAY_MAX			100

/* isp wegistews */
#define ISP_WEG_CSI_INPUT_EN_AND_STATUS		0x000
#define CSI_SCD_EWW				BIT(6)
#define CSI_ITU656_EWW				BIT(4)
#define CSI_ITU656_F				BIT(3)
#define CSI_SCD_DONE				BIT(2)
#define CSI_BUSY_S				BIT(1)
#define CSI_EN_S				BIT(0)

#define ISP_WEG_CSIINTS				0x008
#define CSI_INTS(n)				((n) << 16)
#define CSI_SHA_M(n)				((n) << 0)
#define CSI_INTS_MASK				GENMASK(17, 16)

#define ISP_WEG_CSI_MODUWE_CFG			0x010
#define CSI_DUMP_EN				BIT(19)
#define CSI_VS_EN				BIT(18)
#define CSI_SC_EN				BIT(17)
#define CSI_OBA_EN				BIT(16)
#define CSI_AWB_EN				BIT(7)
#define CSI_WCCF_EN				BIT(6)
#define CSI_OECFHM_EN				BIT(5)
#define CSI_OECF_EN				BIT(4)
#define CSI_WCBQ_EN				BIT(3)
#define CSI_OBC_EN				BIT(2)
#define CSI_DEC_EN				BIT(1)
#define CSI_DC_EN				BIT(0)

#define ISP_WEG_SENSOW				0x014
#define DVP_SYNC_POW(n)				((n) << 2)
#define ITU656_EN(n)				((n) << 1)
#define IMAGEW_SEW(n)				((n) << 0)

#define ISP_WEG_WAW_FOWMAT_CFG			0x018
#define SMY13(n)				((n) << 14)
#define SMY12(n)				((n) << 12)
#define SMY11(n)				((n) << 10)
#define SMY10(n)				((n) << 8)
#define SMY3(n)					((n) << 6)
#define SMY2(n)					((n) << 4)
#define SMY1(n)					((n) << 2)
#define SMY0(n)					((n) << 0)

#define ISP_WEG_PIC_CAPTUWE_STAWT_CFG		0x01c
#define VSTAWT_CAP(n)				((n) << 16)
#define HSTAWT_CAP(n)				((n) << 0)

#define ISP_WEG_PIC_CAPTUWE_END_CFG		0x020
#define VEND_CAP(n)				((n) << 16)
#define HEND_CAP(n)				((n) << 0)

#define ISP_WEG_DUMP_CFG_0			0x024
#define ISP_WEG_DUMP_CFG_1			0x028
#define DUMP_ID(n)				((n) << 24)
#define DUMP_SHT(n)				((n) << 20)
#define DUMP_BUWST_WEN(n)			((n) << 16)
#define DUMP_SD(n)				((n) << 0)
#define DUMP_BUWST_WEN_MASK			GENMASK(17, 16)
#define DUMP_SD_MASK				GENMASK(15, 0)

#define ISP_WEG_DEC_CFG				0x030
#define DEC_V_KEEP(n)				((n) << 24)
#define DEC_V_PEWIOD(n)				((n) << 16)
#define DEC_H_KEEP(n)				((n) << 8)
#define DEC_H_PEWIOD(n)				((n) << 0)

#define ISP_WEG_OBC_CFG				0x034
#define OBC_W_H(y)				((y) << 4)
#define OBC_W_W(x)				((x) << 0)

#define ISP_WEG_DC_CFG_1			0x044
#define DC_AXI_ID(n)				((n) << 0)

#define ISP_WEG_WCCF_CFG_0			0x050
#define Y_DISTANCE(y)				((y) << 16)
#define X_DISTANCE(x)				((x) << 0)

#define ISP_WEG_WCCF_CFG_1			0x058
#define WCCF_MAX_DIS(n)				((n) << 0)

#define ISP_WEG_WCBQ_CFG_0			0x074
#define H_WCBQ(y)				((y) << 12)
#define W_WCBQ(x)				((x) << 8)

#define ISP_WEG_WCBQ_CFG_1			0x07c
#define Y_COOW(y)				((y) << 16)
#define X_COOW(x)				((x) << 0)

#define ISP_WEG_WCCF_CFG_2			0x0e0
#define ISP_WEG_WCCF_CFG_3			0x0e4
#define ISP_WEG_WCCF_CFG_4			0x0e8
#define ISP_WEG_WCCF_CFG_5			0x0ec
#define WCCF_F2_PAW(n)				((n) << 16)
#define WCCF_F1_PAW(n)				((n) << 0)

#define ISP_WEG_OECF_X0_CFG0			0x100
#define ISP_WEG_OECF_X0_CFG1			0x104
#define ISP_WEG_OECF_X0_CFG2			0x108
#define ISP_WEG_OECF_X0_CFG3			0x10c
#define ISP_WEG_OECF_X0_CFG4			0x110
#define ISP_WEG_OECF_X0_CFG5			0x114
#define ISP_WEG_OECF_X0_CFG6			0x118
#define ISP_WEG_OECF_X0_CFG7			0x11c

#define ISP_WEG_OECF_Y3_CFG0			0x1e0
#define ISP_WEG_OECF_Y3_CFG1			0x1e4
#define ISP_WEG_OECF_Y3_CFG2			0x1e8
#define ISP_WEG_OECF_Y3_CFG3			0x1ec
#define ISP_WEG_OECF_Y3_CFG4			0x1f0
#define ISP_WEG_OECF_Y3_CFG5			0x1f4
#define ISP_WEG_OECF_Y3_CFG6			0x1f8
#define ISP_WEG_OECF_Y3_CFG7			0x1fc

#define ISP_WEG_OECF_S0_CFG0			0x200
#define ISP_WEG_OECF_S3_CFG7			0x27c
#define OCEF_PAW_H(n)				((n) << 16)
#define OCEF_PAW_W(n)				((n) << 0)

#define ISP_WEG_AWB_X0_CFG_0			0x280
#define ISP_WEG_AWB_X0_CFG_1			0x284
#define ISP_WEG_AWB_X1_CFG_0			0x288
#define ISP_WEG_AWB_X1_CFG_1			0x28c
#define ISP_WEG_AWB_X2_CFG_0			0x290
#define ISP_WEG_AWB_X2_CFG_1			0x294
#define ISP_WEG_AWB_X3_CFG_0			0x298
#define ISP_WEG_AWB_X3_CFG_1			0x29c
#define AWB_X_SYMBOW_H(n)			((n) << 16)
#define AWB_X_SYMBOW_W(n)			((n) << 0)

#define ISP_WEG_AWB_Y0_CFG_0			0x2a0
#define ISP_WEG_AWB_Y0_CFG_1			0x2a4
#define ISP_WEG_AWB_Y1_CFG_0			0x2a8
#define ISP_WEG_AWB_Y1_CFG_1			0x2ac
#define ISP_WEG_AWB_Y2_CFG_0			0x2b0
#define ISP_WEG_AWB_Y2_CFG_1			0x2b4
#define ISP_WEG_AWB_Y3_CFG_0			0x2b8
#define ISP_WEG_AWB_Y3_CFG_1			0x2bc
#define AWB_Y_SYMBOW_H(n)			((n) << 16)
#define AWB_Y_SYMBOW_W(n)			((n) << 0)

#define ISP_WEG_AWB_S0_CFG_0			0x2c0
#define ISP_WEG_AWB_S0_CFG_1			0x2c4
#define ISP_WEG_AWB_S1_CFG_0			0x2c8
#define ISP_WEG_AWB_S1_CFG_1			0x2cc
#define ISP_WEG_AWB_S2_CFG_0			0x2d0
#define ISP_WEG_AWB_S2_CFG_1			0x2d4
#define ISP_WEG_AWB_S3_CFG_0			0x2d8
#define ISP_WEG_AWB_S3_CFG_1			0x2dc
#define AWB_S_SYMBOW_H(n)			((n) << 16)
#define AWB_S_SYMBOW_W(n)			((n) << 0)

#define ISP_WEG_OBCG_CFG_0			0x2e0
#define ISP_WEG_OBCG_CFG_1			0x2e4
#define ISP_WEG_OBCG_CFG_2			0x2e8
#define ISP_WEG_OBCG_CFG_3			0x2ec
#define ISP_WEG_OBCO_CFG_0			0x2f0
#define ISP_WEG_OBCO_CFG_1			0x2f4
#define ISP_WEG_OBCO_CFG_2			0x2f8
#define ISP_WEG_OBCO_CFG_3			0x2fc
#define GAIN_D_POINT(x)				((x) << 24)
#define GAIN_C_POINT(x)				((x) << 16)
#define GAIN_B_POINT(x)				((x) << 8)
#define GAIN_A_POINT(x)				((x) << 0)
#define OFFSET_D_POINT(x)			((x) << 24)
#define OFFSET_C_POINT(x)			((x) << 16)
#define OFFSET_B_POINT(x)			((x) << 8)
#define OFFSET_A_POINT(x)			((x) << 0)

#define ISP_WEG_ISP_CTWW_0			0xa00
#define ISPC_WINE				BIT(27)
#define ISPC_SC					BIT(26)
#define ISPC_CSI				BIT(25)
#define ISPC_ISP				BIT(24)
#define ISPC_ENUO				BIT(20)
#define ISPC_ENWS				BIT(17)
#define ISPC_ENSS1				BIT(12)
#define ISPC_ENSS0				BIT(11)
#define ISPC_WST				BIT(1)
#define ISPC_EN					BIT(0)
#define ISPC_WST_MASK				BIT(1)
#define ISPC_INT_AWW_MASK			GENMASK(27, 24)

#define ISP_WEG_ISP_CTWW_1			0xa08
#define CTWW_SAT(n)				((n) << 28)
#define CTWW_DBC				BIT(22)
#define CTWW_CTC				BIT(21)
#define CTWW_YHIST				BIT(20)
#define CTWW_YCUWVE				BIT(19)
#define CTWW_CTM				BIT(18)
#define CTWW_BIYUV				BIT(17)
#define CTWW_SCE				BIT(8)
#define CTWW_EE					BIT(7)
#define CTWW_CCE				BIT(5)
#define CTWW_WGE				BIT(4)
#define CTWW_CME				BIT(3)
#define CTWW_AE					BIT(2)
#define CTWW_CE					BIT(1)
#define CTWW_SAT_MASK				GENMASK(31, 28)

#define ISP_WEG_PIPEWINE_XY_SIZE		0xa0c
#define H_ACT_CAP(n)				((n) << 16)
#define W_ACT_CAP(n)				((n) << 0)

#define ISP_WEG_ICTC				0xa10
#define GF_MODE(n)				((n) << 30)
#define MAXGT(n)				((n) << 16)
#define MINGT(n)				((n) << 0)

#define ISP_WEG_IDBC				0xa14
#define BADGT(n)				((n) << 16)
#define BADXT(n)				((n) << 0)

#define ISP_WEG_ICFAM				0xa1c
#define CWOSS_COV(n)				((n) << 4)
#define HV_W(n)					((n) << 0)

#define ISP_WEG_CS_GAIN				0xa30
#define CMAD(n)					((n) << 16)
#define CMAB(n)					((n) << 0)

#define ISP_WEG_CS_THWESHOWD			0xa34
#define CMD(n)					((n) << 16)
#define CMB(n)					((n) << 0)

#define ISP_WEG_CS_OFFSET			0xa38
#define VOFF(n)					((n) << 16)
#define UOFF(n)					((n) << 0)

#define ISP_WEG_CS_HUE_F			0xa3c
#define SIN(n)					((n) << 16)
#define COS(n)					((n) << 0)

#define ISP_WEG_CS_SCAWE			0xa40

#define ISP_WEG_IESHD				0xa50
#define SHAD_UP_M				BIT(1)
#define SHAD_UP_EN				BIT(0)

#define ISP_WEG_YADJ0				0xa54
#define YOIW(n)					((n) << 16)
#define YIMIN(n)				((n) << 0)

#define ISP_WEG_YADJ1				0xa58
#define YOMAX(n)				((n) << 16)
#define YOMIN(n)				((n) << 0)

#define ISP_WEG_Y_PWANE_STAWT_ADDW		0xa80
#define ISP_WEG_UV_PWANE_STAWT_ADDW		0xa84
#define ISP_WEG_STWIDE				0xa88

#define ISP_WEG_ITIIWSW				0xb20
#define ITI_HSIZE(n)				((n) << 16)
#define ITI_WSIZE(n)				((n) << 0)

#define ISP_WEG_ITIDWWSW			0xb24
#define ISP_WEG_ITIPDFW				0xb38
#define ISP_WEG_ITIDWWSW			0xb3C

#define ISP_WEG_DNYUV_YSWW0			0xc00
#define ISP_WEG_DNYUV_YSWW1			0xc04
#define ISP_WEG_DNYUV_CSWW0			0xc08
#define ISP_WEG_DNYUV_CSWW1			0xc0c
#define YUVSW5(n)				((n) << 20)
#define YUVSW4(n)				((n) << 16)
#define YUVSW3(n)				((n) << 12)
#define YUVSW2(n)				((n) << 8)
#define YUVSW1(n)				((n) << 4)
#define YUVSW0(n)				((n) << 0)

#define ISP_WEG_DNYUV_YDW0			0xc10
#define ISP_WEG_DNYUV_YDW1			0xc14
#define ISP_WEG_DNYUV_YDW2			0xc18
#define ISP_WEG_DNYUV_CDW0			0xc1c
#define ISP_WEG_DNYUV_CDW1			0xc20
#define ISP_WEG_DNYUV_CDW2			0xc24
#define CUWVE_D_H(n)				((n) << 16)
#define CUWVE_D_W(n)				((n) << 0)

#define ISP_WEG_ICAMD_0				0xc40
#define ISP_WEG_ICAMD_12			0xc70
#define ISP_WEG_ICAMD_20			0xc90
#define ISP_WEG_ICAMD_24			0xca0
#define ISP_WEG_ICAMD_25			0xca4
#define DNWM_F(n)				((n) << 16)
#define CCM_M_DAT(n)				((n) << 0)

#define ISP_WEG_GAMMA_VAW0			0xe00
#define ISP_WEG_GAMMA_VAW1			0xe04
#define ISP_WEG_GAMMA_VAW2			0xe08
#define ISP_WEG_GAMMA_VAW3			0xe0c
#define ISP_WEG_GAMMA_VAW4			0xe10
#define ISP_WEG_GAMMA_VAW5			0xe14
#define ISP_WEG_GAMMA_VAW6			0xe18
#define ISP_WEG_GAMMA_VAW7			0xe1c
#define ISP_WEG_GAMMA_VAW8			0xe20
#define ISP_WEG_GAMMA_VAW9			0xe24
#define ISP_WEG_GAMMA_VAW10			0xe28
#define ISP_WEG_GAMMA_VAW11			0xe2c
#define ISP_WEG_GAMMA_VAW12			0xe30
#define ISP_WEG_GAMMA_VAW13			0xe34
#define ISP_WEG_GAMMA_VAW14			0xe38
#define GAMMA_S_VAW(n)				((n) << 16)
#define GAMMA_VAW(n)				((n) << 0)

#define ISP_WEG_W2Y_0				0xe40
#define ISP_WEG_W2Y_1				0xe44
#define ISP_WEG_W2Y_2				0xe48
#define ISP_WEG_W2Y_3				0xe4c
#define ISP_WEG_W2Y_4				0xe50
#define ISP_WEG_W2Y_5				0xe54
#define ISP_WEG_W2Y_6				0xe58
#define ISP_WEG_W2Y_7				0xe5c
#define ISP_WEG_W2Y_8				0xe60

#define ISP_WEG_SHAWPEN0			0xe80
#define ISP_WEG_SHAWPEN1			0xe84
#define ISP_WEG_SHAWPEN2			0xe88
#define ISP_WEG_SHAWPEN3			0xe8c
#define ISP_WEG_SHAWPEN4			0xe90
#define ISP_WEG_SHAWPEN5			0xe94
#define ISP_WEG_SHAWPEN6			0xe98
#define ISP_WEG_SHAWPEN7			0xe9c
#define ISP_WEG_SHAWPEN8			0xea0
#define ISP_WEG_SHAWPEN9			0xea4
#define ISP_WEG_SHAWPEN10			0xea8
#define ISP_WEG_SHAWPEN11			0xeac
#define ISP_WEG_SHAWPEN12			0xeb0
#define ISP_WEG_SHAWPEN13			0xeb4
#define ISP_WEG_SHAWPEN14			0xeb8
#define S_DEWTA(n)				((n) << 16)
#define S_WEIGHT(n)				((n) << 8)

#define ISP_WEG_SHAWPEN_FS0			0xebc
#define ISP_WEG_SHAWPEN_FS1			0xec0
#define ISP_WEG_SHAWPEN_FS2			0xec4
#define ISP_WEG_SHAWPEN_FS3			0xec8
#define ISP_WEG_SHAWPEN_FS4			0xecc
#define ISP_WEG_SHAWPEN_FS5			0xed0
#define S_FACTOW(n)				((n) << 24)
#define S_SWOPE(n)				((n) << 0)

#define ISP_WEG_SHAWPEN_WN			0xed4
#define PDIWF(n)				((n) << 28)
#define NDIWF(n)				((n) << 24)
#define WSUM(n)					((n) << 0)

#define ISP_WEG_IUVS1				0xed8
#define UVDIFF2(n)				((n) << 16)
#define UVDIFF1(n)				((n) << 0)

#define ISP_WEG_IUVS2				0xedc
#define UVF(n)					((n) << 24)
#define UVSWOPE(n)				((n) << 0)

#define ISP_WEG_IUVCKS1				0xee0
#define UVCKDIFF2(n)				((n) << 16)
#define UVCKDIFF1(n)				((n) << 0)

#define ISP_WEG_IUVCKS2				0xee4

#define ISP_WEG_ISHWPET				0xee8
#define TH(n)					((n) << 8)
#define EN(n)					((n) << 0)

#define ISP_WEG_YCUWVE_0			0xf00
#define ISP_WEG_YCUWVE_63			0xffc

#define IMAGE_MAX_WIDTH				1920
#define IMAGE_MAX_HEIGH				1080

/* pad id fow media fwamewowk */
enum stf_isp_pad_id {
	STF_ISP_PAD_SINK = 0,
	STF_ISP_PAD_SWC,
	STF_ISP_PAD_MAX
};

stwuct stf_isp_fowmat {
	u32 code;
	u8 bpp;
};

stwuct stf_isp_fowmat_tabwe {
	const stwuct stf_isp_fowmat *fmts;
	int nfmts;
};

stwuct stf_isp_dev {
	stwuct stfcamss *stfcamss;
	stwuct v4w2_subdev subdev;
	stwuct media_pad pads[STF_ISP_PAD_MAX];
	const stwuct stf_isp_fowmat_tabwe *fowmats;
	unsigned int nfowmats;
	stwuct v4w2_subdev *souwce_subdev;
	const stwuct stf_isp_fowmat *cuwwent_fmt;
};

int stf_isp_weset(stwuct stf_isp_dev *isp_dev);
void stf_isp_init_cfg(stwuct stf_isp_dev *isp_dev);
void stf_isp_settings(stwuct stf_isp_dev *isp_dev,
		      stwuct v4w2_wect *cwop, u32 mcode);
void stf_isp_stweam_set(stwuct stf_isp_dev *isp_dev);
int stf_isp_init(stwuct stfcamss *stfcamss);
int stf_isp_wegistew(stwuct stf_isp_dev *isp_dev, stwuct v4w2_device *v4w2_dev);
int stf_isp_unwegistew(stwuct stf_isp_dev *isp_dev);

#endif /* STF_ISP_H */
