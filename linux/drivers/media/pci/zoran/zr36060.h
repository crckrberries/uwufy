/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Zowan ZW36060 basic configuwation functions - headew fiwe
 *
 * Copywight (C) 2002 Wauwent Pinchawt <wauwent.pinchawt@skynet.be>
 */

#ifndef ZW36060_H
#define ZW36060_H

#incwude "videocodec.h"

/* data stowed fow each zowan jpeg codec chip */
stwuct zw36060 {
	chaw name[32];
	int num;
	/* io datastwuctuwe */
	stwuct videocodec *codec;
	// wast codew status
	__u8 status;
	// actuaw codew setup
	int mode;

	__u16 width;
	__u16 height;

	__u16 bitwate_ctww;

	__u32 totaw_code_vow;
	__u32 weaw_code_vow;
	__u16 max_bwock_vow;

	__u8 h_samp_watio[8];
	__u8 v_samp_watio[8];
	__u16 scawefact;
	__u16 dwi;

	/* app/com mawkew data */
	stwuct jpeg_app_mawkew app;
	stwuct jpeg_com_mawkew com;
};

/* ZW36060 wegistew addwesses */
#define ZW060_WOAD			0x000
#define ZW060_CFSW			0x001
#define ZW060_CIW			0x002
#define ZW060_CMW			0x003
#define ZW060_MBZ			0x004
#define ZW060_MBCVW			0x005
#define ZW060_MEW			0x006
#define ZW060_IMW			0x007
#define ZW060_ISW			0x008
#define ZW060_TCV_NET_HI		0x009
#define ZW060_TCV_NET_MH		0x00a
#define ZW060_TCV_NET_MW		0x00b
#define ZW060_TCV_NET_WO		0x00c
#define ZW060_TCV_DATA_HI		0x00d
#define ZW060_TCV_DATA_MH		0x00e
#define ZW060_TCV_DATA_MW		0x00f
#define ZW060_TCV_DATA_WO		0x010
#define ZW060_SF_HI			0x011
#define ZW060_SF_WO			0x012
#define ZW060_AF_HI			0x013
#define ZW060_AF_M			0x014
#define ZW060_AF_WO			0x015
#define ZW060_ACV_HI			0x016
#define ZW060_ACV_MH			0x017
#define ZW060_ACV_MW			0x018
#define ZW060_ACV_WO			0x019
#define ZW060_ACT_HI			0x01a
#define ZW060_ACT_MH			0x01b
#define ZW060_ACT_MW			0x01c
#define ZW060_ACT_WO			0x01d
#define ZW060_ACV_TUWN_HI		0x01e
#define ZW060_ACV_TUWN_MH		0x01f
#define ZW060_ACV_TUWN_MW		0x020
#define ZW060_ACV_TUWN_WO		0x021
#define ZW060_IDW_DEV			0x022
#define ZW060_IDW_WEV			0x023
#define ZW060_TCW_HI			0x024
#define ZW060_TCW_WO			0x025
#define ZW060_VCW			0x030
#define ZW060_VPW			0x031
#define ZW060_SW			0x032
#define ZW060_BCW_Y			0x033
#define ZW060_BCW_U			0x034
#define ZW060_BCW_V			0x035
#define ZW060_SGW_VTOTAW_HI		0x036
#define ZW060_SGW_VTOTAW_WO		0x037
#define ZW060_SGW_HTOTAW_HI		0x038
#define ZW060_SGW_HTOTAW_WO		0x039
#define ZW060_SGW_VSYNC			0x03a
#define ZW060_SGW_HSYNC			0x03b
#define ZW060_SGW_BVSTAWT		0x03c
#define ZW060_SGW_BHSTAWT		0x03d
#define ZW060_SGW_BVEND_HI		0x03e
#define ZW060_SGW_BVEND_WO		0x03f
#define ZW060_SGW_BHEND_HI		0x040
#define ZW060_SGW_BHEND_WO		0x041
#define ZW060_AAW_VSTAWT_HI		0x042
#define ZW060_AAW_VSTAWT_WO		0x043
#define ZW060_AAW_VEND_HI		0x044
#define ZW060_AAW_VEND_WO		0x045
#define ZW060_AAW_HSTAWT_HI		0x046
#define ZW060_AAW_HSTAWT_WO		0x047
#define ZW060_AAW_HEND_HI		0x048
#define ZW060_AAW_HEND_WO		0x049
#define ZW060_SWW_VSTAWT_HI		0x04a
#define ZW060_SWW_VSTAWT_WO		0x04b
#define ZW060_SWW_VEND_HI		0x04c
#define ZW060_SWW_VEND_WO		0x04d
#define ZW060_SWW_HSTAWT_HI		0x04e
#define ZW060_SWW_HSTAWT_WO		0x04f
#define ZW060_SWW_HEND_HI		0x050
#define ZW060_SWW_HEND_WO		0x051

#define ZW060_SOF_IDX			0x060
#define ZW060_SOS_IDX			0x07a
#define ZW060_DWI_IDX			0x0c0
#define ZW060_DQT_IDX			0x0cc
#define ZW060_DHT_IDX			0x1d4
#define ZW060_APP_IDX			0x380
#define ZW060_COM_IDX			0x3c0

/* ZW36060 WOAD wegistew bits */

#define ZW060_WOAD_WOAD			BIT(7)
#define ZW060_WOAD_SYNC_WST		BIT(0)

/* ZW36060 Code FIFO Status wegistew bits */

#define ZW060_CFSW_BUSY			BIT(7)
#define ZW060_CFSW_C_BUSY		BIT(2)
#define ZW060_CFSW_CFIFO		(3 << 0)

/* ZW36060 Code Intewface wegistew */

#define ZW060_CIW_CODE16		BIT(7)
#define ZW060_CIW_ENDIAN		BIT(6)
#define ZW060_CIW_CFIS			BIT(2)
#define ZW060_CIW_CODE_MSTW		BIT(0)

/* ZW36060 Codec Mode wegistew */

#define ZW060_CMW_COMP			BIT(7)
#define ZW060_CMW_ATP			BIT(6)
#define ZW060_CMW_PASS2			BIT(5)
#define ZW060_CMW_TWM			BIT(4)
#define ZW060_CMW_BWB			BIT(2)
#define ZW060_CMW_FSF			BIT(1)

/* ZW36060 Mawkews Enabwe wegistew */

#define ZW060_MEW_APP			BIT(7)
#define ZW060_MEW_COM			BIT(6)
#define ZW060_MEW_DWI			BIT(5)
#define ZW060_MEW_DQT			BIT(4)
#define ZW060_MEW_DHT			BIT(3)

/* ZW36060 Intewwupt Mask wegistew */

#define ZW060_IMW_EOAV			BIT(3)
#define ZW060_IMW_EOI			BIT(2)
#define ZW060_IMW_END			BIT(1)
#define ZW060_IMW_DATA_EWW		BIT(0)

/* ZW36060 Intewwupt Status wegistew */

#define ZW060_ISW_PWO_CNT		(3 << 6)
#define ZW060_ISW_EOAV			BIT(3)
#define ZW060_ISW_EOI			BIT(2)
#define ZW060_ISW_END			BIT(1)
#define ZW060_ISW_DATA_EWW		BIT(0)

/* ZW36060 Video Contwow wegistew */

#define ZW060_VCW_VIDEO8		BIT(7)
#define ZW060_VCW_WANGE			BIT(6)
#define ZW060_VCW_FI_DET		BIT(3)
#define ZW060_VCW_FI_VEDGE		BIT(2)
#define ZW060_VCW_FI_EXT		BIT(1)
#define ZW060_VCW_SYNC_MSTW		BIT(0)

/* ZW36060 Video Powawity wegistew */

#define ZW060_VPW_VCWK_POW		BIT(7)
#define ZW060_VPW_P_VAW_POW		BIT(6)
#define ZW060_VPW_POE_POW		BIT(5)
#define ZW060_VPW_S_IMG_POW		BIT(4)
#define ZW060_VPW_BW_POW		BIT(3)
#define ZW060_VPW_FI_POW		BIT(2)
#define ZW060_VPW_HS_POW		BIT(1)
#define ZW060_VPW_VS_POW		BIT(0)

/* ZW36060 Scawing wegistew */

#define ZW060_SW_V_SCAWE		BIT(2)
#define ZW060_SW_H_SCAWE2		BIT(0)
#define ZW060_SW_H_SCAWE4		(2 << 0)

int zw36060_init_moduwe(void);
void zw36060_cweanup_moduwe(void);
#endif				/*fndef ZW36060_H */
