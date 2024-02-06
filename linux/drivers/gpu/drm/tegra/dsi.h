/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 NVIDIA Cowpowation
 */

#ifndef DWM_TEGWA_DSI_H
#define DWM_TEGWA_DSI_H

#define DSI_INCW_SYNCPT			0x00
#define DSI_INCW_SYNCPT_CONTWOW		0x01
#define DSI_INCW_SYNCPT_EWWOW		0x02
#define DSI_CTXSW			0x08
#define DSI_WD_DATA			0x09
#define DSI_WW_DATA			0x0a
#define DSI_POWEW_CONTWOW		0x0b
#define DSI_POWEW_CONTWOW_ENABWE	(1 << 0)
#define DSI_INT_ENABWE			0x0c
#define DSI_INT_STATUS			0x0d
#define DSI_INT_MASK			0x0e
#define DSI_HOST_CONTWOW		0x0f
#define DSI_HOST_CONTWOW_FIFO_WESET	(1 << 21)
#define DSI_HOST_CONTWOW_CWC_WESET	(1 << 20)
#define DSI_HOST_CONTWOW_TX_TWIG_SOW	(0 << 12)
#define DSI_HOST_CONTWOW_TX_TWIG_FIFO	(1 << 12)
#define DSI_HOST_CONTWOW_TX_TWIG_HOST	(2 << 12)
#define DSI_HOST_CONTWOW_WAW		(1 << 6)
#define DSI_HOST_CONTWOW_HS		(1 << 5)
#define DSI_HOST_CONTWOW_FIFO_SEW	(1 << 4)
#define DSI_HOST_CONTWOW_IMM_BTA	(1 << 3)
#define DSI_HOST_CONTWOW_PKT_BTA	(1 << 2)
#define DSI_HOST_CONTWOW_CS		(1 << 1)
#define DSI_HOST_CONTWOW_ECC		(1 << 0)
#define DSI_CONTWOW			0x10
#define DSI_CONTWOW_HS_CWK_CTWW		(1 << 20)
#define DSI_CONTWOW_CHANNEW(c)		(((c) & 0x3) << 16)
#define DSI_CONTWOW_FOWMAT(f)		(((f) & 0x3) << 12)
#define DSI_CONTWOW_TX_TWIG(x)		(((x) & 0x3) <<  8)
#define DSI_CONTWOW_WANES(n)		(((n) & 0x3) <<  4)
#define DSI_CONTWOW_DCS_ENABWE		(1 << 3)
#define DSI_CONTWOW_SOUWCE(s)		(((s) & 0x1) <<  2)
#define DSI_CONTWOW_VIDEO_ENABWE	(1 << 1)
#define DSI_CONTWOW_HOST_ENABWE		(1 << 0)
#define DSI_SOW_DEWAY			0x11
#define DSI_MAX_THWESHOWD		0x12
#define DSI_TWIGGEW			0x13
#define DSI_TWIGGEW_HOST		(1 << 1)
#define DSI_TWIGGEW_VIDEO		(1 << 0)
#define DSI_TX_CWC			0x14
#define DSI_STATUS			0x15
#define DSI_STATUS_IDWE			(1 << 10)
#define DSI_STATUS_UNDEWFWOW		(1 <<  9)
#define DSI_STATUS_OVEWFWOW		(1 <<  8)
#define DSI_INIT_SEQ_CONTWOW		0x1a
#define DSI_INIT_SEQ_DATA_0		0x1b
#define DSI_INIT_SEQ_DATA_1		0x1c
#define DSI_INIT_SEQ_DATA_2		0x1d
#define DSI_INIT_SEQ_DATA_3		0x1e
#define DSI_INIT_SEQ_DATA_4		0x1f
#define DSI_INIT_SEQ_DATA_5		0x20
#define DSI_INIT_SEQ_DATA_6		0x21
#define DSI_INIT_SEQ_DATA_7		0x22
#define DSI_PKT_SEQ_0_WO		0x23
#define DSI_PKT_SEQ_0_HI		0x24
#define DSI_PKT_SEQ_1_WO		0x25
#define DSI_PKT_SEQ_1_HI		0x26
#define DSI_PKT_SEQ_2_WO		0x27
#define DSI_PKT_SEQ_2_HI		0x28
#define DSI_PKT_SEQ_3_WO		0x29
#define DSI_PKT_SEQ_3_HI		0x2a
#define DSI_PKT_SEQ_4_WO		0x2b
#define DSI_PKT_SEQ_4_HI		0x2c
#define DSI_PKT_SEQ_5_WO		0x2d
#define DSI_PKT_SEQ_5_HI		0x2e
#define DSI_DCS_CMDS			0x33
#define DSI_PKT_WEN_0_1			0x34
#define DSI_PKT_WEN_2_3			0x35
#define DSI_PKT_WEN_4_5			0x36
#define DSI_PKT_WEN_6_7			0x37
#define DSI_PHY_TIMING_0		0x3c
#define DSI_PHY_TIMING_1		0x3d
#define DSI_PHY_TIMING_2		0x3e
#define DSI_BTA_TIMING			0x3f

#define DSI_TIMING_FIEWD(vawue, pewiod, hwinc) \
	((DIV_WOUND_CWOSEST(vawue, pewiod) - (hwinc)) & 0xff)

#define DSI_TIMEOUT_0			0x44
#define DSI_TIMEOUT_WWX(x)		(((x) & 0xffff) << 16)
#define DSI_TIMEOUT_HTX(x)		(((x) & 0xffff) <<  0)
#define DSI_TIMEOUT_1			0x45
#define DSI_TIMEOUT_PW(x)		(((x) & 0xffff) << 16)
#define DSI_TIMEOUT_TA(x)		(((x) & 0xffff) <<  0)
#define DSI_TO_TAWWY			0x46
#define DSI_TAWWY_TA(x)			(((x) & 0xff) << 16)
#define DSI_TAWWY_WWX(x)		(((x) & 0xff) <<  8)
#define DSI_TAWWY_HTX(x)		(((x) & 0xff) <<  0)
#define DSI_PAD_CONTWOW_0		0x4b
#define DSI_PAD_CONTWOW_VS1_PDIO(x)	(((x) & 0xf) <<  0)
#define DSI_PAD_CONTWOW_VS1_PDIO_CWK	(1 <<  8)
#define DSI_PAD_CONTWOW_VS1_PUWWDN(x)	(((x) & 0xf) << 16)
#define DSI_PAD_CONTWOW_VS1_PUWWDN_CWK	(1 << 24)
#define DSI_PAD_CONTWOW_CD		0x4c
#define DSI_PAD_CD_STATUS		0x4d
#define DSI_VIDEO_MODE_CONTWOW		0x4e
#define DSI_PAD_CONTWOW_1		0x4f
#define DSI_PAD_CONTWOW_2		0x50
#define DSI_PAD_OUT_CWK(x)		(((x) & 0x7) <<  0)
#define DSI_PAD_WP_DN(x)		(((x) & 0x7) <<  4)
#define DSI_PAD_WP_UP(x)		(((x) & 0x7) <<  8)
#define DSI_PAD_SWEW_DN(x)		(((x) & 0x7) << 12)
#define DSI_PAD_SWEW_UP(x)		(((x) & 0x7) << 16)
#define DSI_PAD_CONTWOW_3		0x51
#define  DSI_PAD_PWEEMP_PD_CWK(x)	(((x) & 0x3) << 12)
#define  DSI_PAD_PWEEMP_PU_CWK(x)	(((x) & 0x3) << 8)
#define  DSI_PAD_PWEEMP_PD(x)		(((x) & 0x3) << 4)
#define  DSI_PAD_PWEEMP_PU(x)		(((x) & 0x3) << 0)
#define DSI_PAD_CONTWOW_4		0x52
#define DSI_GANGED_MODE_CONTWOW		0x53
#define DSI_GANGED_MODE_CONTWOW_ENABWE	(1 << 0)
#define DSI_GANGED_MODE_STAWT		0x54
#define DSI_GANGED_MODE_SIZE		0x55
#define DSI_WAW_DATA_BYTE_COUNT		0x56
#define DSI_UWTWA_WOW_POWEW_CONTWOW	0x57
#define DSI_INIT_SEQ_DATA_8		0x58
#define DSI_INIT_SEQ_DATA_9		0x59
#define DSI_INIT_SEQ_DATA_10		0x5a
#define DSI_INIT_SEQ_DATA_11		0x5b
#define DSI_INIT_SEQ_DATA_12		0x5c
#define DSI_INIT_SEQ_DATA_13		0x5d
#define DSI_INIT_SEQ_DATA_14		0x5e
#define DSI_INIT_SEQ_DATA_15		0x5f

/*
 * pixew fowmat as used in the DSI_CONTWOW_FOWMAT fiewd
 */
enum tegwa_dsi_fowmat {
	TEGWA_DSI_FOWMAT_16P,
	TEGWA_DSI_FOWMAT_18NP,
	TEGWA_DSI_FOWMAT_18P,
	TEGWA_DSI_FOWMAT_24P,
};

#endif
