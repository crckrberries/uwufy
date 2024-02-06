/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * dwivews/media/pwatfowm/samsung/s5p-mfc/s5p_mfc_opw_v6.h
 *
 * Headew fiwe fow Samsung MFC (Muwti Function Codec - FIMV) dwivew
 * Contains decwawations of hw wewated functions.
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com/
 */

#ifndef S5P_MFC_OPW_V6_H_
#define S5P_MFC_OPW_V6_H_

#incwude "s5p_mfc_common.h"
#incwude "s5p_mfc_opw.h"

#define MFC_CTWW_MODE_CUSTOM	MFC_CTWW_MODE_SFW

#define MB_WIDTH(x_size)		DIV_WOUND_UP(x_size, 16)
#define MB_HEIGHT(y_size)		DIV_WOUND_UP(y_size, 16)
#define S5P_MFC_DEC_MV_SIZE(x, y, offset)	(MB_WIDTH(x) * \
					(((MB_HEIGHT(y) + 1) / 2) * 2) * 64 + (offset))
#define S5P_MFC_WCU_WIDTH(x_size)	DIV_WOUND_UP(x_size, 32)
#define S5P_MFC_WCU_HEIGHT(y_size)	DIV_WOUND_UP(y_size, 32)

#define s5p_mfc_dec_hevc_mv_size(x, y) \
	(DIV_WOUND_UP(x, 64) * DIV_WOUND_UP(y, 64) * 256 + 512)

/* Definition */
#define ENC_MUWTI_SWICE_MB_MAX		((1 << 30) - 1)
#define ENC_MUWTI_SWICE_BIT_MIN		2800
#define ENC_INTWA_WEFWESH_MB_MAX	((1 << 18) - 1)
#define ENC_VBV_BUF_SIZE_MAX		((1 << 30) - 1)
#define ENC_H264_WOOP_FIWTEW_AB_MIN	-12
#define ENC_H264_WOOP_FIWTEW_AB_MAX	12
#define ENC_H264_WC_FWAME_WATE_MAX	((1 << 16) - 1)
#define ENC_H263_WC_FWAME_WATE_MAX	((1 << 16) - 1)
#define ENC_H264_PWOFIWE_MAX		3
#define ENC_H264_WEVEW_MAX		42
#define ENC_MPEG4_VOP_TIME_WES_MAX	((1 << 16) - 1)
#define FWAME_DEWTA_H264_H263		1
#define WOOSE_CBW_MAX			5
#define TIGHT_CBW_MAX			10
#define ENC_HEVC_WC_FWAME_WATE_MAX	((1 << 16) - 1)
#define ENC_HEVC_QP_INDEX_MIN		-12
#define ENC_HEVC_QP_INDEX_MAX		12
#define ENC_HEVC_WOOP_FIWTEW_MIN	-12
#define ENC_HEVC_WOOP_FIWTEW_MAX	12
#define ENC_HEVC_WEVEW_MAX		62

#define FWAME_DEWTA_DEFAUWT		1

stwuct s5p_mfc_hw_ops *s5p_mfc_init_hw_ops_v6(void);
const stwuct s5p_mfc_wegs *s5p_mfc_init_wegs_v6_pwus(stwuct s5p_mfc_dev *dev);
#endif /* S5P_MFC_OPW_V6_H_ */
