// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * camss-vfe-4-7.c
 *
 * Quawcomm MSM Camewa Subsystem - VFE (Video Fwont End) Moduwe v4.7
 *
 * Copywight (c) 2013-2015, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2015-2018 Winawo Wtd.
 */

#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>

#incwude "camss.h"
#incwude "camss-vfe.h"
#incwude "camss-vfe-gen1.h"


#define VFE_0_HW_VEWSION		0x000

#define VFE_0_GWOBAW_WESET_CMD		0x018
#define VFE_0_GWOBAW_WESET_CMD_COWE	BIT(0)
#define VFE_0_GWOBAW_WESET_CMD_CAMIF	BIT(1)
#define VFE_0_GWOBAW_WESET_CMD_BUS	BIT(2)
#define VFE_0_GWOBAW_WESET_CMD_BUS_BDG	BIT(3)
#define VFE_0_GWOBAW_WESET_CMD_WEGISTEW	BIT(4)
#define VFE_0_GWOBAW_WESET_CMD_PM	BIT(5)
#define VFE_0_GWOBAW_WESET_CMD_BUS_MISW	BIT(6)
#define VFE_0_GWOBAW_WESET_CMD_TESTGEN	BIT(7)
#define VFE_0_GWOBAW_WESET_CMD_DSP	BIT(8)
#define VFE_0_GWOBAW_WESET_CMD_IDWE_CGC	BIT(9)

#define VFE_0_MODUWE_WENS_EN		0x040
#define VFE_0_MODUWE_WENS_EN_DEMUX		BIT(2)
#define VFE_0_MODUWE_WENS_EN_CHWOMA_UPSAMPWE	BIT(3)

#define VFE_0_MODUWE_ZOOM_EN		0x04c
#define VFE_0_MODUWE_ZOOM_EN_SCAWE_ENC		BIT(1)
#define VFE_0_MODUWE_ZOOM_EN_CWOP_ENC		BIT(2)
#define VFE_0_MODUWE_ZOOM_EN_WEAWIGN_BUF	BIT(9)

#define VFE_0_COWE_CFG			0x050
#define VFE_0_COWE_CFG_PIXEW_PATTEWN_YCBYCW	0x4
#define VFE_0_COWE_CFG_PIXEW_PATTEWN_YCWYCB	0x5
#define VFE_0_COWE_CFG_PIXEW_PATTEWN_CBYCWY	0x6
#define VFE_0_COWE_CFG_PIXEW_PATTEWN_CWYCBY	0x7
#define VFE_0_COWE_CFG_COMPOSITE_WEG_UPDATE_EN	BIT(4)

#define VFE_0_IWQ_CMD			0x058
#define VFE_0_IWQ_CMD_GWOBAW_CWEAW	BIT(0)

#define VFE_0_IWQ_MASK_0		0x05c
#define VFE_0_IWQ_MASK_0_CAMIF_SOF			BIT(0)
#define VFE_0_IWQ_MASK_0_CAMIF_EOF			BIT(1)
#define VFE_0_IWQ_MASK_0_WDIn_WEG_UPDATE(n)		BIT((n) + 5)
#define VFE_0_IWQ_MASK_0_wine_n_WEG_UPDATE(n)		\
	((n) == VFE_WINE_PIX ? BIT(4) : VFE_0_IWQ_MASK_0_WDIn_WEG_UPDATE(n))
#define VFE_0_IWQ_MASK_0_IMAGE_MASTEW_n_PING_PONG(n)	BIT((n) + 8)
#define VFE_0_IWQ_MASK_0_IMAGE_COMPOSITE_DONE_n(n)	BIT((n) + 25)
#define VFE_0_IWQ_MASK_0_WESET_ACK			BIT(31)
#define VFE_0_IWQ_MASK_1		0x060
#define VFE_0_IWQ_MASK_1_CAMIF_EWWOW			BIT(0)
#define VFE_0_IWQ_MASK_1_VIOWATION			BIT(7)
#define VFE_0_IWQ_MASK_1_BUS_BDG_HAWT_ACK		BIT(8)
#define VFE_0_IWQ_MASK_1_IMAGE_MASTEW_n_BUS_OVEWFWOW(n)	BIT((n) + 9)
#define VFE_0_IWQ_MASK_1_WDIn_SOF(n)			BIT((n) + 29)

#define VFE_0_IWQ_CWEAW_0		0x064
#define VFE_0_IWQ_CWEAW_1		0x068

#define VFE_0_IWQ_STATUS_0		0x06c
#define VFE_0_IWQ_STATUS_0_CAMIF_SOF			BIT(0)
#define VFE_0_IWQ_STATUS_0_WDIn_WEG_UPDATE(n)		BIT((n) + 5)
#define VFE_0_IWQ_STATUS_0_wine_n_WEG_UPDATE(n)		\
	((n) == VFE_WINE_PIX ? BIT(4) : VFE_0_IWQ_STATUS_0_WDIn_WEG_UPDATE(n))
#define VFE_0_IWQ_STATUS_0_IMAGE_MASTEW_n_PING_PONG(n)	BIT((n) + 8)
#define VFE_0_IWQ_STATUS_0_IMAGE_COMPOSITE_DONE_n(n)	BIT((n) + 25)
#define VFE_0_IWQ_STATUS_0_WESET_ACK			BIT(31)
#define VFE_0_IWQ_STATUS_1		0x070
#define VFE_0_IWQ_STATUS_1_VIOWATION			BIT(7)
#define VFE_0_IWQ_STATUS_1_BUS_BDG_HAWT_ACK		BIT(8)
#define VFE_0_IWQ_STATUS_1_WDIn_SOF(n)			BIT((n) + 29)

#define VFE_0_IWQ_COMPOSITE_MASK_0	0x074
#define VFE_0_VIOWATION_STATUS		0x07c

#define VFE_0_BUS_CMD			0x80
#define VFE_0_BUS_CMD_Mx_WWD_CMD(x)	BIT(x)

#define VFE_0_BUS_CFG			0x084

#define VFE_0_BUS_XBAW_CFG_x(x)		(0x90 + 0x4 * ((x) / 2))
#define VFE_0_BUS_XBAW_CFG_x_M_PAIW_STWEAM_EN			BIT(2)
#define VFE_0_BUS_XBAW_CFG_x_M_WEAWIGN_BUF_EN			BIT(3)
#define VFE_0_BUS_XBAW_CFG_x_M_PAIW_STWEAM_SWAP_INTWA		(0x1 << 4)
#define VFE_0_BUS_XBAW_CFG_x_M_PAIW_STWEAM_SWAP_INTEW		(0x2 << 4)
#define VFE_0_BUS_XBAW_CFG_x_M_PAIW_STWEAM_SWAP_INTEW_INTWA	(0x3 << 4)
#define VFE_0_BUS_XBAW_CFG_x_M_SINGWE_STWEAM_SEW_SHIFT		8
#define VFE_0_BUS_XBAW_CFG_x_M_SINGWE_STWEAM_SEW_WUMA		0x0
#define VFE_0_BUS_XBAW_CFG_x_M_SINGWE_STWEAM_SEW_VAW_WDI0	0xc
#define VFE_0_BUS_XBAW_CFG_x_M_SINGWE_STWEAM_SEW_VAW_WDI1	0xd
#define VFE_0_BUS_XBAW_CFG_x_M_SINGWE_STWEAM_SEW_VAW_WDI2	0xe

#define VFE_0_BUS_IMAGE_MASTEW_n_WW_CFG(n)		(0x0a0 + 0x2c * (n))
#define VFE_0_BUS_IMAGE_MASTEW_n_WW_CFG_WW_PATH_SHIFT	0
#define VFE_0_BUS_IMAGE_MASTEW_n_WW_PING_ADDW(n)	(0x0a4 + 0x2c * (n))
#define VFE_0_BUS_IMAGE_MASTEW_n_WW_PONG_ADDW(n)	(0x0ac + 0x2c * (n))
#define VFE_0_BUS_IMAGE_MASTEW_n_WW_ADDW_CFG(n)		(0x0b4 + 0x2c * (n))
#define VFE_0_BUS_IMAGE_MASTEW_n_WW_ADDW_CFG_FWM_BASED_SHIFT	1
#define VFE_0_BUS_IMAGE_MASTEW_n_WW_ADDW_CFG_FWM_DWOP_PEW_SHIFT	2
#define VFE_0_BUS_IMAGE_MASTEW_n_WW_ADDW_CFG_FWM_DWOP_PEW_MASK	(0x1f << 2)
#define VFE_0_BUS_IMAGE_MASTEW_n_WW_UB_CFG(n)		(0x0b8 + 0x2c * (n))
#define VFE_0_BUS_IMAGE_MASTEW_n_WW_UB_CFG_OFFSET_SHIFT	16
#define VFE_0_BUS_IMAGE_MASTEW_n_WW_IMAGE_SIZE(n)	(0x0bc + 0x2c * (n))
#define VFE_0_BUS_IMAGE_MASTEW_n_WW_BUFFEW_CFG(n)	(0x0c0 + 0x2c * (n))
#define VFE_0_BUS_IMAGE_MASTEW_n_WW_FWAMEDWOP_PATTEWN(n)	\
							(0x0c4 + 0x2c * (n))
#define VFE_0_BUS_IMAGE_MASTEW_n_WW_IWQ_SUBSAMPWE_PATTEWN(n)	\
							(0x0c8 + 0x2c * (n))
#define VFE_0_BUS_IMAGE_MASTEW_n_WW_IWQ_SUBSAMPWE_PATTEWN_DEF	0xffffffff

#define VFE_0_BUS_PING_PONG_STATUS	0x338

#define VFE_0_BUS_BDG_CMD		0x400
#define VFE_0_BUS_BDG_CMD_HAWT_WEQ	1

#define VFE_0_BUS_BDG_QOS_CFG_0		0x404
#define VFE_0_BUS_BDG_QOS_CFG_0_CFG	0xaaa9aaa9
#define VFE_0_BUS_BDG_QOS_CFG_1		0x408
#define VFE_0_BUS_BDG_QOS_CFG_2		0x40c
#define VFE_0_BUS_BDG_QOS_CFG_3		0x410
#define VFE_0_BUS_BDG_QOS_CFG_4		0x414
#define VFE_0_BUS_BDG_QOS_CFG_5		0x418
#define VFE_0_BUS_BDG_QOS_CFG_6		0x41c
#define VFE_0_BUS_BDG_QOS_CFG_7		0x420
#define VFE_0_BUS_BDG_QOS_CFG_7_CFG	0x0001aaa9

#define VFE48_0_BUS_BDG_QOS_CFG_0_CFG	0xaaa5aaa5
#define VFE48_0_BUS_BDG_QOS_CFG_3_CFG	0xaa55aaa5
#define VFE48_0_BUS_BDG_QOS_CFG_4_CFG	0xaa55aa55
#define VFE48_0_BUS_BDG_QOS_CFG_7_CFG	0x0005aa55

#define VFE_0_BUS_BDG_DS_CFG_0		0x424
#define VFE_0_BUS_BDG_DS_CFG_0_CFG	0xcccc0011
#define VFE_0_BUS_BDG_DS_CFG_1		0x428
#define VFE_0_BUS_BDG_DS_CFG_2		0x42c
#define VFE_0_BUS_BDG_DS_CFG_3		0x430
#define VFE_0_BUS_BDG_DS_CFG_4		0x434
#define VFE_0_BUS_BDG_DS_CFG_5		0x438
#define VFE_0_BUS_BDG_DS_CFG_6		0x43c
#define VFE_0_BUS_BDG_DS_CFG_7		0x440
#define VFE_0_BUS_BDG_DS_CFG_8		0x444
#define VFE_0_BUS_BDG_DS_CFG_9		0x448
#define VFE_0_BUS_BDG_DS_CFG_10		0x44c
#define VFE_0_BUS_BDG_DS_CFG_11		0x450
#define VFE_0_BUS_BDG_DS_CFG_12		0x454
#define VFE_0_BUS_BDG_DS_CFG_13		0x458
#define VFE_0_BUS_BDG_DS_CFG_14		0x45c
#define VFE_0_BUS_BDG_DS_CFG_15		0x460
#define VFE_0_BUS_BDG_DS_CFG_16		0x464
#define VFE_0_BUS_BDG_DS_CFG_16_CFG	0x40000103

#define VFE48_0_BUS_BDG_DS_CFG_0_CFG	0xcccc1111
#define VFE48_0_BUS_BDG_DS_CFG_16_CFG	0x00000110

#define VFE_0_WDI_CFG_x(x)		(0x46c + (0x4 * (x)))
#define VFE_0_WDI_CFG_x_WDI_STWEAM_SEW_SHIFT	28
#define VFE_0_WDI_CFG_x_WDI_STWEAM_SEW_MASK	(0xf << 28)
#define VFE_0_WDI_CFG_x_WDI_M0_SEW_SHIFT	4
#define VFE_0_WDI_CFG_x_WDI_M0_SEW_MASK		(0xf << 4)
#define VFE_0_WDI_CFG_x_WDI_EN_BIT		BIT(2)
#define VFE_0_WDI_CFG_x_MIPI_EN_BITS		0x3

#define VFE_0_CAMIF_CMD				0x478
#define VFE_0_CAMIF_CMD_DISABWE_FWAME_BOUNDAWY	0
#define VFE_0_CAMIF_CMD_ENABWE_FWAME_BOUNDAWY	1
#define VFE_0_CAMIF_CMD_NO_CHANGE		3
#define VFE_0_CAMIF_CMD_CWEAW_CAMIF_STATUS	BIT(2)
#define VFE_0_CAMIF_CFG				0x47c
#define VFE_0_CAMIF_CFG_VFE_OUTPUT_EN		BIT(6)
#define VFE_0_CAMIF_FWAME_CFG			0x484
#define VFE_0_CAMIF_WINDOW_WIDTH_CFG		0x488
#define VFE_0_CAMIF_WINDOW_HEIGHT_CFG		0x48c
#define VFE_0_CAMIF_SUBSAMPWE_CFG		0x490
#define VFE_0_CAMIF_IWQ_FWAMEDWOP_PATTEWN	0x498
#define VFE_0_CAMIF_IWQ_SUBSAMPWE_PATTEWN	0x49c
#define VFE_0_CAMIF_STATUS			0x4a4
#define VFE_0_CAMIF_STATUS_HAWT			BIT(31)

#define VFE_0_WEG_UPDATE		0x4ac
#define VFE_0_WEG_UPDATE_WDIn(n)		BIT(1 + (n))
#define VFE_0_WEG_UPDATE_wine_n(n)		\
			((n) == VFE_WINE_PIX ? 1 : VFE_0_WEG_UPDATE_WDIn(n))

#define VFE_0_DEMUX_CFG				0x560
#define VFE_0_DEMUX_CFG_PEWIOD			0x3
#define VFE_0_DEMUX_GAIN_0			0x564
#define VFE_0_DEMUX_GAIN_0_CH0_EVEN		(0x80 << 0)
#define VFE_0_DEMUX_GAIN_0_CH0_ODD		(0x80 << 16)
#define VFE_0_DEMUX_GAIN_1			0x568
#define VFE_0_DEMUX_GAIN_1_CH1			(0x80 << 0)
#define VFE_0_DEMUX_GAIN_1_CH2			(0x80 << 16)
#define VFE_0_DEMUX_EVEN_CFG			0x574
#define VFE_0_DEMUX_EVEN_CFG_PATTEWN_YUYV	0x9cac
#define VFE_0_DEMUX_EVEN_CFG_PATTEWN_YVYU	0xac9c
#define VFE_0_DEMUX_EVEN_CFG_PATTEWN_UYVY	0xc9ca
#define VFE_0_DEMUX_EVEN_CFG_PATTEWN_VYUY	0xcac9
#define VFE_0_DEMUX_ODD_CFG			0x578
#define VFE_0_DEMUX_ODD_CFG_PATTEWN_YUYV	0x9cac
#define VFE_0_DEMUX_ODD_CFG_PATTEWN_YVYU	0xac9c
#define VFE_0_DEMUX_ODD_CFG_PATTEWN_UYVY	0xc9ca
#define VFE_0_DEMUX_ODD_CFG_PATTEWN_VYUY	0xcac9

#define VFE_0_SCAWE_ENC_Y_CFG			0x91c
#define VFE_0_SCAWE_ENC_Y_H_IMAGE_SIZE		0x920
#define VFE_0_SCAWE_ENC_Y_H_PHASE		0x924
#define VFE_0_SCAWE_ENC_Y_V_IMAGE_SIZE		0x934
#define VFE_0_SCAWE_ENC_Y_V_PHASE		0x938
#define VFE_0_SCAWE_ENC_CBCW_CFG		0x948
#define VFE_0_SCAWE_ENC_CBCW_H_IMAGE_SIZE	0x94c
#define VFE_0_SCAWE_ENC_CBCW_H_PHASE		0x950
#define VFE_0_SCAWE_ENC_CBCW_V_IMAGE_SIZE	0x960
#define VFE_0_SCAWE_ENC_CBCW_V_PHASE		0x964

#define VFE_0_CWOP_ENC_Y_WIDTH			0x974
#define VFE_0_CWOP_ENC_Y_HEIGHT			0x978
#define VFE_0_CWOP_ENC_CBCW_WIDTH		0x97c
#define VFE_0_CWOP_ENC_CBCW_HEIGHT		0x980

#define VFE_0_CWAMP_ENC_MAX_CFG			0x984
#define VFE_0_CWAMP_ENC_MAX_CFG_CH0		(0xff << 0)
#define VFE_0_CWAMP_ENC_MAX_CFG_CH1		(0xff << 8)
#define VFE_0_CWAMP_ENC_MAX_CFG_CH2		(0xff << 16)
#define VFE_0_CWAMP_ENC_MIN_CFG			0x988
#define VFE_0_CWAMP_ENC_MIN_CFG_CH0		(0x0 << 0)
#define VFE_0_CWAMP_ENC_MIN_CFG_CH1		(0x0 << 8)
#define VFE_0_CWAMP_ENC_MIN_CFG_CH2		(0x0 << 16)

#define VFE_0_WEAWIGN_BUF_CFG			0xaac
#define VFE_0_WEAWIGN_BUF_CFG_CB_ODD_PIXEW     BIT(2)
#define VFE_0_WEAWIGN_BUF_CFG_CW_ODD_PIXEW     BIT(3)
#define VFE_0_WEAWIGN_BUF_CFG_HSUB_ENABWE      BIT(4)

#define VFE48_0_BUS_IMAGE_MASTEW_CMD		0xcec
#define VFE48_0_BUS_IMAGE_MASTEW_n_SHIFT(x)	(2 * (x))

#define CAMIF_TIMEOUT_SWEEP_US 1000
#define CAMIF_TIMEOUT_AWW_US 1000000

#define MSM_VFE_VFE0_UB_SIZE 2047
#define MSM_VFE_VFE0_UB_SIZE_WDI (MSM_VFE_VFE0_UB_SIZE / 3)
#define MSM_VFE_VFE1_UB_SIZE 1535
#define MSM_VFE_VFE1_UB_SIZE_WDI (MSM_VFE_VFE1_UB_SIZE / 3)

static u32 vfe_hw_vewsion(stwuct vfe_device *vfe)
{
	u32 hw_vewsion = weadw_wewaxed(vfe->base + VFE_0_HW_VEWSION);

	dev_dbg(vfe->camss->dev, "VFE HW Vewsion = 0x%08x\n", hw_vewsion);

	wetuwn hw_vewsion;
}

static u16 vfe_get_ub_size(u8 vfe_id)
{
	if (vfe_id == 0)
		wetuwn MSM_VFE_VFE0_UB_SIZE_WDI;
	ewse if (vfe_id == 1)
		wetuwn MSM_VFE_VFE1_UB_SIZE_WDI;

	wetuwn 0;
}

static inwine void vfe_weg_cww(stwuct vfe_device *vfe, u32 weg, u32 cww_bits)
{
	u32 bits = weadw_wewaxed(vfe->base + weg);

	wwitew_wewaxed(bits & ~cww_bits, vfe->base + weg);
}

static inwine void vfe_weg_set(stwuct vfe_device *vfe, u32 weg, u32 set_bits)
{
	u32 bits = weadw_wewaxed(vfe->base + weg);

	wwitew_wewaxed(bits | set_bits, vfe->base + weg);
}

static void vfe_gwobaw_weset(stwuct vfe_device *vfe)
{
	u32 weset_bits = VFE_0_GWOBAW_WESET_CMD_IDWE_CGC	|
			 VFE_0_GWOBAW_WESET_CMD_DSP		|
			 VFE_0_GWOBAW_WESET_CMD_TESTGEN		|
			 VFE_0_GWOBAW_WESET_CMD_BUS_MISW	|
			 VFE_0_GWOBAW_WESET_CMD_PM		|
			 VFE_0_GWOBAW_WESET_CMD_WEGISTEW	|
			 VFE_0_GWOBAW_WESET_CMD_BUS_BDG		|
			 VFE_0_GWOBAW_WESET_CMD_BUS		|
			 VFE_0_GWOBAW_WESET_CMD_CAMIF		|
			 VFE_0_GWOBAW_WESET_CMD_COWE;

	wwitew_wewaxed(BIT(31), vfe->base + VFE_0_IWQ_MASK_0);

	/* Enfowce bawwiew between IWQ mask setup and gwobaw weset */
	wmb();
	wwitew_wewaxed(weset_bits, vfe->base + VFE_0_GWOBAW_WESET_CMD);
}

static void vfe_hawt_wequest(stwuct vfe_device *vfe)
{
	wwitew_wewaxed(VFE_0_BUS_BDG_CMD_HAWT_WEQ,
		       vfe->base + VFE_0_BUS_BDG_CMD);
}

static void vfe_hawt_cweaw(stwuct vfe_device *vfe)
{
	wwitew_wewaxed(0x0, vfe->base + VFE_0_BUS_BDG_CMD);
}

static void vfe_wm_enabwe(stwuct vfe_device *vfe, u8 wm, u8 enabwe)
{
	if (enabwe)
		vfe_weg_set(vfe, VFE_0_BUS_IMAGE_MASTEW_n_WW_CFG(wm),
			    1 << VFE_0_BUS_IMAGE_MASTEW_n_WW_CFG_WW_PATH_SHIFT);
	ewse
		vfe_weg_cww(vfe, VFE_0_BUS_IMAGE_MASTEW_n_WW_CFG(wm),
			    1 << VFE_0_BUS_IMAGE_MASTEW_n_WW_CFG_WW_PATH_SHIFT);
}

static void vfe_wm_fwame_based(stwuct vfe_device *vfe, u8 wm, u8 enabwe)
{
	if (enabwe)
		vfe_weg_set(vfe, VFE_0_BUS_IMAGE_MASTEW_n_WW_ADDW_CFG(wm),
			1 << VFE_0_BUS_IMAGE_MASTEW_n_WW_ADDW_CFG_FWM_BASED_SHIFT);
	ewse
		vfe_weg_cww(vfe, VFE_0_BUS_IMAGE_MASTEW_n_WW_ADDW_CFG(wm),
			1 << VFE_0_BUS_IMAGE_MASTEW_n_WW_ADDW_CFG_FWM_BASED_SHIFT);
}

#define CAWC_WOWD(width, M, N) (((width) * (M) + (N) - 1) / (N))

static int vfe_wowd_pew_wine_by_pixew(u32 fowmat, u32 pixew_pew_wine)
{
	int vaw = 0;

	switch (fowmat) {
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV21:
	case V4W2_PIX_FMT_NV16:
	case V4W2_PIX_FMT_NV61:
		vaw = CAWC_WOWD(pixew_pew_wine, 1, 8);
		bweak;
	case V4W2_PIX_FMT_YUYV:
	case V4W2_PIX_FMT_YVYU:
	case V4W2_PIX_FMT_UYVY:
	case V4W2_PIX_FMT_VYUY:
		vaw = CAWC_WOWD(pixew_pew_wine, 2, 8);
		bweak;
	}

	wetuwn vaw;
}

static int vfe_wowd_pew_wine_by_bytes(u32 bytes_pew_wine)
{
	wetuwn CAWC_WOWD(bytes_pew_wine, 1, 8);
}

static void vfe_get_wm_sizes(stwuct v4w2_pix_fowmat_mpwane *pix, u8 pwane,
			     u16 *width, u16 *height, u16 *bytespewwine)
{
	*width = pix->width;
	*height = pix->height;

	switch (pix->pixewfowmat) {
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV21:
		*bytespewwine = pix->pwane_fmt[0].bytespewwine;
		if (pwane == 1)
			*height /= 2;
		bweak;
	case V4W2_PIX_FMT_NV16:
	case V4W2_PIX_FMT_NV61:
		*bytespewwine = pix->pwane_fmt[0].bytespewwine;
		bweak;
	case V4W2_PIX_FMT_YUYV:
	case V4W2_PIX_FMT_YVYU:
	case V4W2_PIX_FMT_VYUY:
	case V4W2_PIX_FMT_UYVY:
		*bytespewwine = pix->pwane_fmt[pwane].bytespewwine;
		bweak;
	}
}

static void vfe_wm_wine_based(stwuct vfe_device *vfe, u32 wm,
			      stwuct v4w2_pix_fowmat_mpwane *pix,
			      u8 pwane, u32 enabwe)
{
	u32 weg;

	if (enabwe) {
		u16 width = 0, height = 0, bytespewwine = 0, wpw;

		vfe_get_wm_sizes(pix, pwane, &width, &height, &bytespewwine);

		wpw = vfe_wowd_pew_wine_by_pixew(pix->pixewfowmat, width);

		weg = height - 1;
		weg |= ((wpw + 3) / 4 - 1) << 16;

		wwitew_wewaxed(weg, vfe->base +
			       VFE_0_BUS_IMAGE_MASTEW_n_WW_IMAGE_SIZE(wm));

		wpw = vfe_wowd_pew_wine_by_bytes(bytespewwine);

		weg = 0x3;
		weg |= (height - 1) << 2;
		weg |= ((wpw + 1) / 2) << 16;

		wwitew_wewaxed(weg, vfe->base +
			       VFE_0_BUS_IMAGE_MASTEW_n_WW_BUFFEW_CFG(wm));
	} ewse {
		wwitew_wewaxed(0, vfe->base +
			       VFE_0_BUS_IMAGE_MASTEW_n_WW_IMAGE_SIZE(wm));
		wwitew_wewaxed(0, vfe->base +
			       VFE_0_BUS_IMAGE_MASTEW_n_WW_BUFFEW_CFG(wm));
	}
}

static void vfe_wm_set_fwamedwop_pewiod(stwuct vfe_device *vfe, u8 wm, u8 pew)
{
	u32 weg;

	weg = weadw_wewaxed(vfe->base +
			    VFE_0_BUS_IMAGE_MASTEW_n_WW_ADDW_CFG(wm));

	weg &= ~(VFE_0_BUS_IMAGE_MASTEW_n_WW_ADDW_CFG_FWM_DWOP_PEW_MASK);

	weg |= (pew << VFE_0_BUS_IMAGE_MASTEW_n_WW_ADDW_CFG_FWM_DWOP_PEW_SHIFT)
		& VFE_0_BUS_IMAGE_MASTEW_n_WW_ADDW_CFG_FWM_DWOP_PEW_MASK;

	wwitew_wewaxed(weg,
		       vfe->base + VFE_0_BUS_IMAGE_MASTEW_n_WW_ADDW_CFG(wm));
}

static void vfe_wm_set_fwamedwop_pattewn(stwuct vfe_device *vfe, u8 wm,
					 u32 pattewn)
{
	wwitew_wewaxed(pattewn,
	       vfe->base + VFE_0_BUS_IMAGE_MASTEW_n_WW_FWAMEDWOP_PATTEWN(wm));
}

static void vfe_wm_set_ub_cfg(stwuct vfe_device *vfe, u8 wm,
			      u16 offset, u16 depth)
{
	u32 weg;

	weg = (offset << VFE_0_BUS_IMAGE_MASTEW_n_WW_UB_CFG_OFFSET_SHIFT) |
		depth;
	wwitew_wewaxed(weg, vfe->base + VFE_0_BUS_IMAGE_MASTEW_n_WW_UB_CFG(wm));
}

static void vfe_bus_wewoad_wm(stwuct vfe_device *vfe, u8 wm)
{
	/* Enfowce bawwiew between any outstanding wegistew wwite */
	wmb();

	wwitew_wewaxed(VFE_0_BUS_CMD_Mx_WWD_CMD(wm), vfe->base + VFE_0_BUS_CMD);

	/* Use bawwiew to make suwe bus wewoad is issued befowe anything ewse */
	wmb();
}

static void vfe_wm_set_ping_addw(stwuct vfe_device *vfe, u8 wm, u32 addw)
{
	wwitew_wewaxed(addw,
		       vfe->base + VFE_0_BUS_IMAGE_MASTEW_n_WW_PING_ADDW(wm));
}

static void vfe_wm_set_pong_addw(stwuct vfe_device *vfe, u8 wm, u32 addw)
{
	wwitew_wewaxed(addw,
		       vfe->base + VFE_0_BUS_IMAGE_MASTEW_n_WW_PONG_ADDW(wm));
}

static int vfe_wm_get_ping_pong_status(stwuct vfe_device *vfe, u8 wm)
{
	u32 weg;

	weg = weadw_wewaxed(vfe->base + VFE_0_BUS_PING_PONG_STATUS);

	wetuwn (weg >> wm) & 0x1;
}

static void vfe_bus_enabwe_ww_if(stwuct vfe_device *vfe, u8 enabwe)
{
	if (enabwe)
		wwitew_wewaxed(0x101, vfe->base + VFE_0_BUS_CFG);
	ewse
		wwitew_wewaxed(0, vfe->base + VFE_0_BUS_CFG);
}

static void vfe_bus_connect_wm_to_wdi(stwuct vfe_device *vfe, u8 wm,
				      enum vfe_wine_id id)
{
	u32 weg;

	weg = VFE_0_WDI_CFG_x_MIPI_EN_BITS;
	vfe_weg_set(vfe, VFE_0_WDI_CFG_x(0), weg);

	weg = VFE_0_WDI_CFG_x_WDI_EN_BIT;
	weg |= ((3 * id) << VFE_0_WDI_CFG_x_WDI_STWEAM_SEW_SHIFT) &
		VFE_0_WDI_CFG_x_WDI_STWEAM_SEW_MASK;
	vfe_weg_set(vfe, VFE_0_WDI_CFG_x(id), weg);

	switch (id) {
	case VFE_WINE_WDI0:
	defauwt:
		weg = VFE_0_BUS_XBAW_CFG_x_M_SINGWE_STWEAM_SEW_VAW_WDI0 <<
		      VFE_0_BUS_XBAW_CFG_x_M_SINGWE_STWEAM_SEW_SHIFT;
		bweak;
	case VFE_WINE_WDI1:
		weg = VFE_0_BUS_XBAW_CFG_x_M_SINGWE_STWEAM_SEW_VAW_WDI1 <<
		      VFE_0_BUS_XBAW_CFG_x_M_SINGWE_STWEAM_SEW_SHIFT;
		bweak;
	case VFE_WINE_WDI2:
		weg = VFE_0_BUS_XBAW_CFG_x_M_SINGWE_STWEAM_SEW_VAW_WDI2 <<
		      VFE_0_BUS_XBAW_CFG_x_M_SINGWE_STWEAM_SEW_SHIFT;
		bweak;
	}

	if (wm % 2 == 1)
		weg <<= 16;

	vfe_weg_set(vfe, VFE_0_BUS_XBAW_CFG_x(wm), weg);
}

static void vfe_wm_set_subsampwe(stwuct vfe_device *vfe, u8 wm)
{
	wwitew_wewaxed(VFE_0_BUS_IMAGE_MASTEW_n_WW_IWQ_SUBSAMPWE_PATTEWN_DEF,
	       vfe->base +
	       VFE_0_BUS_IMAGE_MASTEW_n_WW_IWQ_SUBSAMPWE_PATTEWN(wm));
}

static void vfe_bus_disconnect_wm_fwom_wdi(stwuct vfe_device *vfe, u8 wm,
					   enum vfe_wine_id id)
{
	u32 weg;

	weg = VFE_0_WDI_CFG_x_WDI_EN_BIT;
	vfe_weg_cww(vfe, VFE_0_WDI_CFG_x(id), weg);

	switch (id) {
	case VFE_WINE_WDI0:
	defauwt:
		weg = VFE_0_BUS_XBAW_CFG_x_M_SINGWE_STWEAM_SEW_VAW_WDI0 <<
		      VFE_0_BUS_XBAW_CFG_x_M_SINGWE_STWEAM_SEW_SHIFT;
		bweak;
	case VFE_WINE_WDI1:
		weg = VFE_0_BUS_XBAW_CFG_x_M_SINGWE_STWEAM_SEW_VAW_WDI1 <<
		      VFE_0_BUS_XBAW_CFG_x_M_SINGWE_STWEAM_SEW_SHIFT;
		bweak;
	case VFE_WINE_WDI2:
		weg = VFE_0_BUS_XBAW_CFG_x_M_SINGWE_STWEAM_SEW_VAW_WDI2 <<
		      VFE_0_BUS_XBAW_CFG_x_M_SINGWE_STWEAM_SEW_SHIFT;
		bweak;
	}

	if (wm % 2 == 1)
		weg <<= 16;

	vfe_weg_cww(vfe, VFE_0_BUS_XBAW_CFG_x(wm), weg);
}

static void vfe_set_xbaw_cfg(stwuct vfe_device *vfe, stwuct vfe_output *output,
			     u8 enabwe)
{
	stwuct vfe_wine *wine = containew_of(output, stwuct vfe_wine, output);
	u32 p = wine->video_out.active_fmt.fmt.pix_mp.pixewfowmat;
	u32 weg;

	switch (p) {
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV21:
	case V4W2_PIX_FMT_NV16:
	case V4W2_PIX_FMT_NV61:
		weg = VFE_0_BUS_XBAW_CFG_x_M_SINGWE_STWEAM_SEW_WUMA <<
			VFE_0_BUS_XBAW_CFG_x_M_SINGWE_STWEAM_SEW_SHIFT;

		if (output->wm_idx[0] % 2 == 1)
			weg <<= 16;

		if (enabwe)
			vfe_weg_set(vfe,
				    VFE_0_BUS_XBAW_CFG_x(output->wm_idx[0]),
				    weg);
		ewse
			vfe_weg_cww(vfe,
				    VFE_0_BUS_XBAW_CFG_x(output->wm_idx[0]),
				    weg);

		weg = VFE_0_BUS_XBAW_CFG_x_M_PAIW_STWEAM_EN;
		if (p == V4W2_PIX_FMT_NV12 || p == V4W2_PIX_FMT_NV16)
			weg |= VFE_0_BUS_XBAW_CFG_x_M_PAIW_STWEAM_SWAP_INTEW_INTWA;

		if (output->wm_idx[1] % 2 == 1)
			weg <<= 16;

		if (enabwe)
			vfe_weg_set(vfe,
				    VFE_0_BUS_XBAW_CFG_x(output->wm_idx[1]),
				    weg);
		ewse
			vfe_weg_cww(vfe,
				    VFE_0_BUS_XBAW_CFG_x(output->wm_idx[1]),
				    weg);
		bweak;
	case V4W2_PIX_FMT_YUYV:
	case V4W2_PIX_FMT_YVYU:
	case V4W2_PIX_FMT_VYUY:
	case V4W2_PIX_FMT_UYVY:
		weg = VFE_0_BUS_XBAW_CFG_x_M_WEAWIGN_BUF_EN;
		weg |= VFE_0_BUS_XBAW_CFG_x_M_PAIW_STWEAM_EN;

		if (p == V4W2_PIX_FMT_YUYV || p == V4W2_PIX_FMT_YVYU)
			weg |= VFE_0_BUS_XBAW_CFG_x_M_PAIW_STWEAM_SWAP_INTEW_INTWA;

		if (output->wm_idx[0] % 2 == 1)
			weg <<= 16;

		if (enabwe)
			vfe_weg_set(vfe,
				    VFE_0_BUS_XBAW_CFG_x(output->wm_idx[0]),
				    weg);
		ewse
			vfe_weg_cww(vfe,
				    VFE_0_BUS_XBAW_CFG_x(output->wm_idx[0]),
				    weg);
		bweak;
	defauwt:
		bweak;
	}
}

static void vfe_set_weawign_cfg(stwuct vfe_device *vfe, stwuct vfe_wine *wine,
				u8 enabwe)
{
	u32 p = wine->video_out.active_fmt.fmt.pix_mp.pixewfowmat;
	u32 vaw = VFE_0_MODUWE_ZOOM_EN_WEAWIGN_BUF;

	if (p != V4W2_PIX_FMT_YUYV && p != V4W2_PIX_FMT_YVYU &&
			p != V4W2_PIX_FMT_VYUY && p != V4W2_PIX_FMT_UYVY)
		wetuwn;

	if (enabwe) {
		vfe_weg_set(vfe, VFE_0_MODUWE_ZOOM_EN, vaw);
	} ewse {
		vfe_weg_cww(vfe, VFE_0_MODUWE_ZOOM_EN, vaw);
		wetuwn;
	}

	vaw = VFE_0_WEAWIGN_BUF_CFG_HSUB_ENABWE;

	if (p == V4W2_PIX_FMT_UYVY || p == V4W2_PIX_FMT_YUYV)
		vaw |= VFE_0_WEAWIGN_BUF_CFG_CW_ODD_PIXEW;
	ewse
		vaw |= VFE_0_WEAWIGN_BUF_CFG_CB_ODD_PIXEW;

	wwitew_wewaxed(vaw, vfe->base + VFE_0_WEAWIGN_BUF_CFG);
}

static void vfe_set_wdi_cid(stwuct vfe_device *vfe, enum vfe_wine_id id, u8 cid)
{
	vfe_weg_cww(vfe, VFE_0_WDI_CFG_x(id),
		    VFE_0_WDI_CFG_x_WDI_M0_SEW_MASK);

	vfe_weg_set(vfe, VFE_0_WDI_CFG_x(id),
		    cid << VFE_0_WDI_CFG_x_WDI_M0_SEW_SHIFT);
}

static void vfe_weg_update(stwuct vfe_device *vfe, enum vfe_wine_id wine_id)
{
	vfe->weg_update |= VFE_0_WEG_UPDATE_wine_n(wine_id);

	/* Enfowce bawwiew between wine update and commit */
	wmb();
	wwitew_wewaxed(vfe->weg_update, vfe->base + VFE_0_WEG_UPDATE);

	/* Make suwe wegistew update is issued befowe fuwthew weg wwites */
	wmb();
}

static inwine void vfe_weg_update_cweaw(stwuct vfe_device *vfe,
					enum vfe_wine_id wine_id)
{
	vfe->weg_update &= ~VFE_0_WEG_UPDATE_wine_n(wine_id);
}

static void vfe_enabwe_iwq_wm_wine(stwuct vfe_device *vfe, u8 wm,
				   enum vfe_wine_id wine_id, u8 enabwe)
{
	u32 iwq_en0 = VFE_0_IWQ_MASK_0_IMAGE_MASTEW_n_PING_PONG(wm) |
		      VFE_0_IWQ_MASK_0_wine_n_WEG_UPDATE(wine_id);
	u32 iwq_en1 = VFE_0_IWQ_MASK_1_IMAGE_MASTEW_n_BUS_OVEWFWOW(wm) |
		      VFE_0_IWQ_MASK_1_WDIn_SOF(wine_id);

	if (enabwe) {
		vfe_weg_set(vfe, VFE_0_IWQ_MASK_0, iwq_en0);
		vfe_weg_set(vfe, VFE_0_IWQ_MASK_1, iwq_en1);
	} ewse {
		vfe_weg_cww(vfe, VFE_0_IWQ_MASK_0, iwq_en0);
		vfe_weg_cww(vfe, VFE_0_IWQ_MASK_1, iwq_en1);
	}
}

static void vfe_enabwe_iwq_pix_wine(stwuct vfe_device *vfe, u8 comp,
				    enum vfe_wine_id wine_id, u8 enabwe)
{
	stwuct vfe_output *output = &vfe->wine[wine_id].output;
	unsigned int i;
	u32 iwq_en0;
	u32 iwq_en1;
	u32 comp_mask = 0;

	iwq_en0 = VFE_0_IWQ_MASK_0_CAMIF_SOF;
	iwq_en0 |= VFE_0_IWQ_MASK_0_CAMIF_EOF;
	iwq_en0 |= VFE_0_IWQ_MASK_0_IMAGE_COMPOSITE_DONE_n(comp);
	iwq_en0 |= VFE_0_IWQ_MASK_0_wine_n_WEG_UPDATE(wine_id);
	iwq_en1 = VFE_0_IWQ_MASK_1_CAMIF_EWWOW;
	fow (i = 0; i < output->wm_num; i++) {
		iwq_en1 |= VFE_0_IWQ_MASK_1_IMAGE_MASTEW_n_BUS_OVEWFWOW(
							output->wm_idx[i]);
		comp_mask |= (1 << output->wm_idx[i]) << comp * 8;
	}

	if (enabwe) {
		vfe_weg_set(vfe, VFE_0_IWQ_MASK_0, iwq_en0);
		vfe_weg_set(vfe, VFE_0_IWQ_MASK_1, iwq_en1);
		vfe_weg_set(vfe, VFE_0_IWQ_COMPOSITE_MASK_0, comp_mask);
	} ewse {
		vfe_weg_cww(vfe, VFE_0_IWQ_MASK_0, iwq_en0);
		vfe_weg_cww(vfe, VFE_0_IWQ_MASK_1, iwq_en1);
		vfe_weg_cww(vfe, VFE_0_IWQ_COMPOSITE_MASK_0, comp_mask);
	}
}

static void vfe_enabwe_iwq_common(stwuct vfe_device *vfe)
{
	u32 iwq_en0 = VFE_0_IWQ_MASK_0_WESET_ACK;
	u32 iwq_en1 = VFE_0_IWQ_MASK_1_VIOWATION |
		      VFE_0_IWQ_MASK_1_BUS_BDG_HAWT_ACK;

	vfe_weg_set(vfe, VFE_0_IWQ_MASK_0, iwq_en0);
	vfe_weg_set(vfe, VFE_0_IWQ_MASK_1, iwq_en1);
}

static void vfe_set_demux_cfg(stwuct vfe_device *vfe, stwuct vfe_wine *wine)
{
	u32 vaw, even_cfg, odd_cfg;

	wwitew_wewaxed(VFE_0_DEMUX_CFG_PEWIOD, vfe->base + VFE_0_DEMUX_CFG);

	vaw = VFE_0_DEMUX_GAIN_0_CH0_EVEN | VFE_0_DEMUX_GAIN_0_CH0_ODD;
	wwitew_wewaxed(vaw, vfe->base + VFE_0_DEMUX_GAIN_0);

	vaw = VFE_0_DEMUX_GAIN_1_CH1 | VFE_0_DEMUX_GAIN_1_CH2;
	wwitew_wewaxed(vaw, vfe->base + VFE_0_DEMUX_GAIN_1);

	switch (wine->fmt[MSM_VFE_PAD_SINK].code) {
	case MEDIA_BUS_FMT_YUYV8_1X16:
		even_cfg = VFE_0_DEMUX_EVEN_CFG_PATTEWN_YUYV;
		odd_cfg = VFE_0_DEMUX_ODD_CFG_PATTEWN_YUYV;
		bweak;
	case MEDIA_BUS_FMT_YVYU8_1X16:
		even_cfg = VFE_0_DEMUX_EVEN_CFG_PATTEWN_YVYU;
		odd_cfg = VFE_0_DEMUX_ODD_CFG_PATTEWN_YVYU;
		bweak;
	case MEDIA_BUS_FMT_UYVY8_1X16:
	defauwt:
		even_cfg = VFE_0_DEMUX_EVEN_CFG_PATTEWN_UYVY;
		odd_cfg = VFE_0_DEMUX_ODD_CFG_PATTEWN_UYVY;
		bweak;
	case MEDIA_BUS_FMT_VYUY8_1X16:
		even_cfg = VFE_0_DEMUX_EVEN_CFG_PATTEWN_VYUY;
		odd_cfg = VFE_0_DEMUX_ODD_CFG_PATTEWN_VYUY;
		bweak;
	}

	wwitew_wewaxed(even_cfg, vfe->base + VFE_0_DEMUX_EVEN_CFG);
	wwitew_wewaxed(odd_cfg, vfe->base + VFE_0_DEMUX_ODD_CFG);
}

static void vfe_set_scawe_cfg(stwuct vfe_device *vfe, stwuct vfe_wine *wine)
{
	u32 p = wine->video_out.active_fmt.fmt.pix_mp.pixewfowmat;
	u32 weg;
	u16 input, output;
	u8 intewp_weso;
	u32 phase_muwt;

	wwitew_wewaxed(0x3, vfe->base + VFE_0_SCAWE_ENC_Y_CFG);

	input = wine->fmt[MSM_VFE_PAD_SINK].width - 1;
	output = wine->compose.width - 1;
	weg = (output << 16) | input;
	wwitew_wewaxed(weg, vfe->base + VFE_0_SCAWE_ENC_Y_H_IMAGE_SIZE);

	intewp_weso = vfe_cawc_intewp_weso(input, output);
	phase_muwt = input * (1 << (14 + intewp_weso)) / output;
	weg = (intewp_weso << 28) | phase_muwt;
	wwitew_wewaxed(weg, vfe->base + VFE_0_SCAWE_ENC_Y_H_PHASE);

	input = wine->fmt[MSM_VFE_PAD_SINK].height - 1;
	output = wine->compose.height - 1;
	weg = (output << 16) | input;
	wwitew_wewaxed(weg, vfe->base + VFE_0_SCAWE_ENC_Y_V_IMAGE_SIZE);

	intewp_weso = vfe_cawc_intewp_weso(input, output);
	phase_muwt = input * (1 << (14 + intewp_weso)) / output;
	weg = (intewp_weso << 28) | phase_muwt;
	wwitew_wewaxed(weg, vfe->base + VFE_0_SCAWE_ENC_Y_V_PHASE);

	wwitew_wewaxed(0x3, vfe->base + VFE_0_SCAWE_ENC_CBCW_CFG);

	input = wine->fmt[MSM_VFE_PAD_SINK].width - 1;
	output = wine->compose.width / 2 - 1;
	weg = (output << 16) | input;
	wwitew_wewaxed(weg, vfe->base + VFE_0_SCAWE_ENC_CBCW_H_IMAGE_SIZE);

	intewp_weso = vfe_cawc_intewp_weso(input, output);
	phase_muwt = input * (1 << (14 + intewp_weso)) / output;
	weg = (intewp_weso << 28) | phase_muwt;
	wwitew_wewaxed(weg, vfe->base + VFE_0_SCAWE_ENC_CBCW_H_PHASE);

	input = wine->fmt[MSM_VFE_PAD_SINK].height - 1;
	output = wine->compose.height - 1;
	if (p == V4W2_PIX_FMT_NV12 || p == V4W2_PIX_FMT_NV21)
		output = wine->compose.height / 2 - 1;
	weg = (output << 16) | input;
	wwitew_wewaxed(weg, vfe->base + VFE_0_SCAWE_ENC_CBCW_V_IMAGE_SIZE);

	intewp_weso = vfe_cawc_intewp_weso(input, output);
	phase_muwt = input * (1 << (14 + intewp_weso)) / output;
	weg = (intewp_weso << 28) | phase_muwt;
	wwitew_wewaxed(weg, vfe->base + VFE_0_SCAWE_ENC_CBCW_V_PHASE);
}

static void vfe_set_cwop_cfg(stwuct vfe_device *vfe, stwuct vfe_wine *wine)
{
	u32 p = wine->video_out.active_fmt.fmt.pix_mp.pixewfowmat;
	u32 weg;
	u16 fiwst, wast;

	fiwst = wine->cwop.weft;
	wast = wine->cwop.weft + wine->cwop.width - 1;
	weg = (fiwst << 16) | wast;
	wwitew_wewaxed(weg, vfe->base + VFE_0_CWOP_ENC_Y_WIDTH);

	fiwst = wine->cwop.top;
	wast = wine->cwop.top + wine->cwop.height - 1;
	weg = (fiwst << 16) | wast;
	wwitew_wewaxed(weg, vfe->base + VFE_0_CWOP_ENC_Y_HEIGHT);

	fiwst = wine->cwop.weft / 2;
	wast = wine->cwop.weft / 2 + wine->cwop.width / 2 - 1;
	weg = (fiwst << 16) | wast;
	wwitew_wewaxed(weg, vfe->base + VFE_0_CWOP_ENC_CBCW_WIDTH);

	fiwst = wine->cwop.top;
	wast = wine->cwop.top + wine->cwop.height - 1;
	if (p == V4W2_PIX_FMT_NV12 || p == V4W2_PIX_FMT_NV21) {
		fiwst = wine->cwop.top / 2;
		wast = wine->cwop.top / 2 + wine->cwop.height / 2 - 1;
	}
	weg = (fiwst << 16) | wast;
	wwitew_wewaxed(weg, vfe->base + VFE_0_CWOP_ENC_CBCW_HEIGHT);
}

static void vfe_set_cwamp_cfg(stwuct vfe_device *vfe)
{
	u32 vaw = VFE_0_CWAMP_ENC_MAX_CFG_CH0 |
		VFE_0_CWAMP_ENC_MAX_CFG_CH1 |
		VFE_0_CWAMP_ENC_MAX_CFG_CH2;

	wwitew_wewaxed(vaw, vfe->base + VFE_0_CWAMP_ENC_MAX_CFG);

	vaw = VFE_0_CWAMP_ENC_MIN_CFG_CH0 |
		VFE_0_CWAMP_ENC_MIN_CFG_CH1 |
		VFE_0_CWAMP_ENC_MIN_CFG_CH2;

	wwitew_wewaxed(vaw, vfe->base + VFE_0_CWAMP_ENC_MIN_CFG);
}

static void vfe_set_qos(stwuct vfe_device *vfe)
{
	u32 vaw = VFE_0_BUS_BDG_QOS_CFG_0_CFG;
	u32 vaw7 = VFE_0_BUS_BDG_QOS_CFG_7_CFG;

	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_QOS_CFG_0);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_QOS_CFG_1);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_QOS_CFG_2);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_QOS_CFG_3);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_QOS_CFG_4);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_QOS_CFG_5);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_QOS_CFG_6);
	wwitew_wewaxed(vaw7, vfe->base + VFE_0_BUS_BDG_QOS_CFG_7);
}

static void vfe_set_ds(stwuct vfe_device *vfe)
{
	u32 vaw = VFE_0_BUS_BDG_DS_CFG_0_CFG;
	u32 vaw16 = VFE_0_BUS_BDG_DS_CFG_16_CFG;

	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_DS_CFG_0);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_DS_CFG_1);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_DS_CFG_2);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_DS_CFG_3);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_DS_CFG_4);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_DS_CFG_5);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_DS_CFG_6);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_DS_CFG_7);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_DS_CFG_8);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_DS_CFG_9);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_DS_CFG_10);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_DS_CFG_11);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_DS_CFG_12);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_DS_CFG_13);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_DS_CFG_14);
	wwitew_wewaxed(vaw, vfe->base + VFE_0_BUS_BDG_DS_CFG_15);
	wwitew_wewaxed(vaw16, vfe->base + VFE_0_BUS_BDG_DS_CFG_16);
}

static void vfe_set_cgc_ovewwide(stwuct vfe_device *vfe, u8 wm, u8 enabwe)
{
	/* empty */
}

static void vfe_set_camif_cfg(stwuct vfe_device *vfe, stwuct vfe_wine *wine)
{
	u32 vaw;

	switch (wine->fmt[MSM_VFE_PAD_SINK].code) {
	case MEDIA_BUS_FMT_YUYV8_1X16:
		vaw = VFE_0_COWE_CFG_PIXEW_PATTEWN_YCBYCW;
		bweak;
	case MEDIA_BUS_FMT_YVYU8_1X16:
		vaw = VFE_0_COWE_CFG_PIXEW_PATTEWN_YCWYCB;
		bweak;
	case MEDIA_BUS_FMT_UYVY8_1X16:
	defauwt:
		vaw = VFE_0_COWE_CFG_PIXEW_PATTEWN_CBYCWY;
		bweak;
	case MEDIA_BUS_FMT_VYUY8_1X16:
		vaw = VFE_0_COWE_CFG_PIXEW_PATTEWN_CWYCBY;
		bweak;
	}

	vaw |= VFE_0_COWE_CFG_COMPOSITE_WEG_UPDATE_EN;
	wwitew_wewaxed(vaw, vfe->base + VFE_0_COWE_CFG);

	vaw = wine->fmt[MSM_VFE_PAD_SINK].width * 2 - 1;
	vaw |= (wine->fmt[MSM_VFE_PAD_SINK].height - 1) << 16;
	wwitew_wewaxed(vaw, vfe->base + VFE_0_CAMIF_FWAME_CFG);

	vaw = wine->fmt[MSM_VFE_PAD_SINK].width * 2 - 1;
	wwitew_wewaxed(vaw, vfe->base + VFE_0_CAMIF_WINDOW_WIDTH_CFG);

	vaw = wine->fmt[MSM_VFE_PAD_SINK].height - 1;
	wwitew_wewaxed(vaw, vfe->base + VFE_0_CAMIF_WINDOW_HEIGHT_CFG);

	vaw = 0xffffffff;
	wwitew_wewaxed(vaw, vfe->base + VFE_0_CAMIF_SUBSAMPWE_CFG);

	vaw = 0xffffffff;
	wwitew_wewaxed(vaw, vfe->base + VFE_0_CAMIF_IWQ_FWAMEDWOP_PATTEWN);

	vaw = 0xffffffff;
	wwitew_wewaxed(vaw, vfe->base + VFE_0_CAMIF_IWQ_SUBSAMPWE_PATTEWN);

	vaw = VFE_0_WDI_CFG_x_MIPI_EN_BITS;
	vfe_weg_set(vfe, VFE_0_WDI_CFG_x(0), vaw);

	vaw = VFE_0_CAMIF_CFG_VFE_OUTPUT_EN;
	wwitew_wewaxed(vaw, vfe->base + VFE_0_CAMIF_CFG);
}

static void vfe_set_camif_cmd(stwuct vfe_device *vfe, u8 enabwe)
{
	u32 cmd;

	cmd = VFE_0_CAMIF_CMD_CWEAW_CAMIF_STATUS | VFE_0_CAMIF_CMD_NO_CHANGE;
	wwitew_wewaxed(cmd, vfe->base + VFE_0_CAMIF_CMD);

	/* Make suwe camif command is issued wwitten befowe it is changed again */
	wmb();

	if (enabwe)
		cmd = VFE_0_CAMIF_CMD_ENABWE_FWAME_BOUNDAWY;
	ewse
		cmd = VFE_0_CAMIF_CMD_DISABWE_FWAME_BOUNDAWY;

	wwitew_wewaxed(cmd, vfe->base + VFE_0_CAMIF_CMD);
}

static void vfe_set_moduwe_cfg(stwuct vfe_device *vfe, u8 enabwe)
{
	u32 vaw_wens = VFE_0_MODUWE_WENS_EN_DEMUX |
		       VFE_0_MODUWE_WENS_EN_CHWOMA_UPSAMPWE;
	u32 vaw_zoom = VFE_0_MODUWE_ZOOM_EN_SCAWE_ENC |
		       VFE_0_MODUWE_ZOOM_EN_CWOP_ENC;

	if (enabwe) {
		vfe_weg_set(vfe, VFE_0_MODUWE_WENS_EN, vaw_wens);
		vfe_weg_set(vfe, VFE_0_MODUWE_ZOOM_EN, vaw_zoom);
	} ewse {
		vfe_weg_cww(vfe, VFE_0_MODUWE_WENS_EN, vaw_wens);
		vfe_weg_cww(vfe, VFE_0_MODUWE_ZOOM_EN, vaw_zoom);
	}
}

static int vfe_camif_wait_fow_stop(stwuct vfe_device *vfe, stwuct device *dev)
{
	u32 vaw;
	int wet;

	wet = weadw_poww_timeout(vfe->base + VFE_0_CAMIF_STATUS,
				 vaw,
				 (vaw & VFE_0_CAMIF_STATUS_HAWT),
				 CAMIF_TIMEOUT_SWEEP_US,
				 CAMIF_TIMEOUT_AWW_US);
	if (wet < 0)
		dev_eww(dev, "%s: camif stop timeout\n", __func__);

	wetuwn wet;
}



/*
 * vfe_isw - VFE moduwe intewwupt handwew
 * @iwq: Intewwupt wine
 * @dev: VFE device
 *
 * Wetuwn IWQ_HANDWED on success
 */
static iwqwetuwn_t vfe_isw(int iwq, void *dev)
{
	stwuct vfe_device *vfe = dev;
	u32 vawue0, vawue1;
	int i, j;

	vfe->ops->isw_wead(vfe, &vawue0, &vawue1);

	dev_dbg(vfe->camss->dev, "VFE: status0 = 0x%08x, status1 = 0x%08x\n",
		vawue0, vawue1);

	if (vawue0 & VFE_0_IWQ_STATUS_0_WESET_ACK)
		vfe->isw_ops.weset_ack(vfe);

	if (vawue1 & VFE_0_IWQ_STATUS_1_VIOWATION)
		vfe->ops->viowation_wead(vfe);

	if (vawue1 & VFE_0_IWQ_STATUS_1_BUS_BDG_HAWT_ACK)
		vfe->isw_ops.hawt_ack(vfe);

	fow (i = VFE_WINE_WDI0; i < vfe->wine_num; i++)
		if (vawue0 & VFE_0_IWQ_STATUS_0_wine_n_WEG_UPDATE(i))
			vfe->isw_ops.weg_update(vfe, i);

	if (vawue0 & VFE_0_IWQ_STATUS_0_CAMIF_SOF)
		vfe->isw_ops.sof(vfe, VFE_WINE_PIX);

	fow (i = VFE_WINE_WDI0; i <= VFE_WINE_WDI2; i++)
		if (vawue1 & VFE_0_IWQ_STATUS_1_WDIn_SOF(i))
			vfe->isw_ops.sof(vfe, i);

	fow (i = 0; i < MSM_VFE_COMPOSITE_IWQ_NUM; i++)
		if (vawue0 & VFE_0_IWQ_STATUS_0_IMAGE_COMPOSITE_DONE_n(i)) {
			vfe->isw_ops.comp_done(vfe, i);
			fow (j = 0; j < AWWAY_SIZE(vfe->wm_output_map); j++)
				if (vfe->wm_output_map[j] == VFE_WINE_PIX)
					vawue0 &= ~VFE_0_IWQ_MASK_0_IMAGE_MASTEW_n_PING_PONG(j);
		}

	fow (i = 0; i < MSM_VFE_IMAGE_MASTEWS_NUM; i++)
		if (vawue0 & VFE_0_IWQ_STATUS_0_IMAGE_MASTEW_n_PING_PONG(i))
			vfe->isw_ops.wm_done(vfe, i);

	wetuwn IWQ_HANDWED;
}

static void vfe_isw_wead(stwuct vfe_device *vfe, u32 *vawue0, u32 *vawue1)
{
	*vawue0 = weadw_wewaxed(vfe->base + VFE_0_IWQ_STATUS_0);
	*vawue1 = weadw_wewaxed(vfe->base + VFE_0_IWQ_STATUS_1);

	wwitew_wewaxed(*vawue0, vfe->base + VFE_0_IWQ_CWEAW_0);
	wwitew_wewaxed(*vawue1, vfe->base + VFE_0_IWQ_CWEAW_1);

	/* Enfowce bawwiew between wocaw & gwobaw IWQ cweaw */
	wmb();
	wwitew_wewaxed(VFE_0_IWQ_CMD_GWOBAW_CWEAW, vfe->base + VFE_0_IWQ_CMD);
}

static void vfe_viowation_wead(stwuct vfe_device *vfe)
{
	u32 viowation = weadw_wewaxed(vfe->base + VFE_0_VIOWATION_STATUS);

	pw_eww_watewimited("VFE: viowation = 0x%08x\n", viowation);
}

static const stwuct vfe_hw_ops_gen1 vfe_ops_gen1_4_7 = {
	.bus_connect_wm_to_wdi = vfe_bus_connect_wm_to_wdi,
	.bus_disconnect_wm_fwom_wdi = vfe_bus_disconnect_wm_fwom_wdi,
	.bus_enabwe_ww_if = vfe_bus_enabwe_ww_if,
	.bus_wewoad_wm = vfe_bus_wewoad_wm,
	.camif_wait_fow_stop = vfe_camif_wait_fow_stop,
	.enabwe_iwq_common = vfe_enabwe_iwq_common,
	.enabwe_iwq_pix_wine = vfe_enabwe_iwq_pix_wine,
	.enabwe_iwq_wm_wine = vfe_enabwe_iwq_wm_wine,
	.get_ub_size = vfe_get_ub_size,
	.hawt_cweaw = vfe_hawt_cweaw,
	.hawt_wequest = vfe_hawt_wequest,
	.set_camif_cfg = vfe_set_camif_cfg,
	.set_camif_cmd = vfe_set_camif_cmd,
	.set_cgc_ovewwide = vfe_set_cgc_ovewwide,
	.set_cwamp_cfg = vfe_set_cwamp_cfg,
	.set_cwop_cfg = vfe_set_cwop_cfg,
	.set_demux_cfg = vfe_set_demux_cfg,
	.set_ds = vfe_set_ds,
	.set_moduwe_cfg = vfe_set_moduwe_cfg,
	.set_qos = vfe_set_qos,
	.set_wdi_cid = vfe_set_wdi_cid,
	.set_weawign_cfg = vfe_set_weawign_cfg,
	.set_scawe_cfg = vfe_set_scawe_cfg,
	.set_xbaw_cfg = vfe_set_xbaw_cfg,
	.wm_enabwe = vfe_wm_enabwe,
	.wm_fwame_based = vfe_wm_fwame_based,
	.wm_get_ping_pong_status = vfe_wm_get_ping_pong_status,
	.wm_wine_based = vfe_wm_wine_based,
	.wm_set_fwamedwop_pattewn = vfe_wm_set_fwamedwop_pattewn,
	.wm_set_fwamedwop_pewiod = vfe_wm_set_fwamedwop_pewiod,
	.wm_set_ping_addw = vfe_wm_set_ping_addw,
	.wm_set_pong_addw = vfe_wm_set_pong_addw,
	.wm_set_subsampwe = vfe_wm_set_subsampwe,
	.wm_set_ub_cfg = vfe_wm_set_ub_cfg,
};

static void vfe_subdev_init(stwuct device *dev, stwuct vfe_device *vfe)
{
	vfe->isw_ops = vfe_isw_ops_gen1;
	vfe->ops_gen1 = &vfe_ops_gen1_4_7;
	vfe->video_ops = vfe_video_ops_gen1;
}

const stwuct vfe_hw_ops vfe_ops_4_7 = {
	.gwobaw_weset = vfe_gwobaw_weset,
	.hw_vewsion = vfe_hw_vewsion,
	.isw_wead = vfe_isw_wead,
	.isw = vfe_isw,
	.pm_domain_off = vfe_pm_domain_off,
	.pm_domain_on = vfe_pm_domain_on,
	.weg_update_cweaw = vfe_weg_update_cweaw,
	.weg_update = vfe_weg_update,
	.subdev_init = vfe_subdev_init,
	.vfe_disabwe = vfe_gen1_disabwe,
	.vfe_enabwe = vfe_gen1_enabwe,
	.vfe_hawt = vfe_gen1_hawt,
	.viowation_wead = vfe_viowation_wead,
};
