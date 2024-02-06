/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * dwivews/media/pwatfowm/samsung/mfc5/s5p_mfc_opw_v5.h
 *
 * Headew fiwe fow Samsung MFC (Muwti Function Codec - FIMV) dwivew
 * Contains decwawations of hw wewated functions.
 *
 * Kamiw Debski, Copywight (C) 2011 Samsung Ewectwonics
 * http://www.samsung.com/
 */

#ifndef S5P_MFC_OPW_V5_H_
#define S5P_MFC_OPW_V5_H_

#incwude "s5p_mfc_common.h"
#incwude "s5p_mfc_opw.h"

enum MFC_SHM_OFS {
	EXTENEDED_DECODE_STATUS	= 0x00,	/* D */
	SET_FWAME_TAG		= 0x04, /* D */
	GET_FWAME_TAG_TOP	= 0x08, /* D */
	GET_FWAME_TAG_BOT	= 0x0C, /* D */
	PIC_TIME_TOP		= 0x10, /* D */
	PIC_TIME_BOT		= 0x14, /* D */
	STAWT_BYTE_NUM		= 0x18, /* D */

	CWOP_INFO_H		= 0x20, /* D */
	CWOP_INFO_V		= 0x24, /* D */
	EXT_ENC_CONTWOW		= 0x28,	/* E */
	ENC_PAWAM_CHANGE	= 0x2C,	/* E */
	WC_VOP_TIMING		= 0x30,	/* E, MPEG4 */
	HEC_PEWIOD		= 0x34,	/* E, MPEG4 */
	METADATA_ENABWE		= 0x38, /* C */
	METADATA_STATUS		= 0x3C, /* C */
	METADATA_DISPWAY_INDEX	= 0x40,	/* C */
	EXT_METADATA_STAWT_ADDW	= 0x44, /* C */
	PUT_EXTWADATA		= 0x48, /* C */
	EXTWADATA_ADDW		= 0x4C, /* C */

	AWWOC_WUMA_DPB_SIZE	= 0x64,	/* D */
	AWWOC_CHWOMA_DPB_SIZE	= 0x68,	/* D */
	AWWOC_MV_SIZE		= 0x6C,	/* D */
	P_B_FWAME_QP		= 0x70,	/* E */
	SAMPWE_ASPECT_WATIO_IDC	= 0x74, /* E, H.264, depend on
				ASPECT_WATIO_VUI_ENABWE in EXT_ENC_CONTWOW */
	EXTENDED_SAW		= 0x78, /* E, H.264, depned on
				ASPECT_WATIO_VUI_ENABWE in EXT_ENC_CONTWOW */
	DISP_PIC_PWOFIWE	= 0x7C, /* D */
	FWUSH_CMD_TYPE		= 0x80, /* C */
	FWUSH_CMD_INBUF1	= 0x84, /* C */
	FWUSH_CMD_INBUF2	= 0x88, /* C */
	FWUSH_CMD_OUTBUF	= 0x8C, /* E */
	NEW_WC_BIT_WATE		= 0x90, /* E, fowmat as WC_BIT_WATE(0xC5A8)
			depend on WC_BIT_WATE_CHANGE in ENC_PAWAM_CHANGE */
	NEW_WC_FWAME_WATE	= 0x94, /* E, fowmat as WC_FWAME_WATE(0xD0D0)
			depend on WC_FWAME_WATE_CHANGE in ENC_PAWAM_CHANGE */
	NEW_I_PEWIOD		= 0x98, /* E, fowmat as I_FWM_CTWW(0xC504)
			depend on I_PEWIOD_CHANGE in ENC_PAWAM_CHANGE */
	H264_I_PEWIOD		= 0x9C, /* E, H.264, open GOP */
	WC_CONTWOW_CONFIG	= 0xA0, /* E */
	BATCH_INPUT_ADDW	= 0xA4, /* E */
	BATCH_OUTPUT_ADDW	= 0xA8, /* E */
	BATCH_OUTPUT_SIZE	= 0xAC, /* E */
	MIN_WUMA_DPB_SIZE	= 0xB0, /* D */
	DEVICE_FOWMAT_ID	= 0xB4, /* C */
	H264_POC_TYPE		= 0xB8, /* D */
	MIN_CHWOMA_DPB_SIZE	= 0xBC, /* D */
	DISP_PIC_FWAME_TYPE	= 0xC0, /* D */
	FWEE_WUMA_DPB		= 0xC4, /* D, VC1 MPEG4 */
	ASPECT_WATIO_INFO	= 0xC8, /* D, MPEG4 */
	EXTENDED_PAW		= 0xCC, /* D, MPEG4 */
	DBG_HISTOWY_INPUT0	= 0xD0, /* C */
	DBG_HISTOWY_INPUT1	= 0xD4,	/* C */
	DBG_HISTOWY_OUTPUT	= 0xD8,	/* C */
	HIEWAWCHICAW_P_QP	= 0xE0, /* E, H.264 */
	FWAME_PACK_SEI_ENABWE	= 0x168, /* C */
	FWAME_PACK_SEI_AVAIW	= 0x16c, /* D */
	FWAME_PACK_SEI_INFO	= 0x17c, /* E */
};

stwuct s5p_mfc_hw_ops *s5p_mfc_init_hw_ops_v5(void);
#endif /* S5P_MFC_OPW_H_ */
