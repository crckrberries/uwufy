/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wegistew definition fiwe fow Samsung MFC V7.x Intewface (FIMV) dwivew
 *
 * Copywight (c) 2013 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com/
 */

#ifndef _WEGS_MFC_V7_H
#define _WEGS_MFC_V7_H

#incwude "wegs-mfc-v6.h"

/* Additionaw featuwes of v7 */
#define S5P_FIMV_CODEC_VP8_ENC_V7	25

/* Additionaw wegistews fow v7 */
#define S5P_FIMV_E_SOUWCE_FIWST_ADDW_V7			0xf9e0
#define S5P_FIMV_E_SOUWCE_SECOND_ADDW_V7		0xf9e4
#define S5P_FIMV_E_SOUWCE_THIWD_ADDW_V7			0xf9e8
#define S5P_FIMV_E_SOUWCE_FIWST_STWIDE_V7		0xf9ec
#define S5P_FIMV_E_SOUWCE_SECOND_STWIDE_V7		0xf9f0
#define S5P_FIMV_E_SOUWCE_THIWD_STWIDE_V7		0xf9f4

#define S5P_FIMV_E_ENCODED_SOUWCE_FIWST_ADDW_V7		0xfa70
#define S5P_FIMV_E_ENCODED_SOUWCE_SECOND_ADDW_V7	0xfa74
#define S5P_FIMV_E_ENCODED_SOUWCE_THIWD_ADDW_V7		0xfa78

#define S5P_FIMV_E_VP8_OPTIONS_V7			0xfdb0
#define S5P_FIMV_E_VP8_FIWTEW_OPTIONS_V7		0xfdb4
#define S5P_FIMV_E_VP8_GOWDEN_FWAME_OPTION_V7		0xfdb8
#define S5P_FIMV_E_VP8_NUM_T_WAYEW_V7			0xfdc4

/* MFCv7 vawiant defines */
#define MAX_FW_SIZE_V7			(SZ_512K)	/* 512KB */
#define MAX_CPB_SIZE_V7			(3 * SZ_1M)	/* 3MB */
#define MFC_VEWSION_V7			0x72
#define MFC_NUM_POWTS_V7		1

#define MFC_WUMA_PAD_BYTES_V7		256
#define MFC_CHWOMA_PAD_BYTES_V7		128

/* MFCv7 Context buffew sizes */
#define MFC_CTX_BUF_SIZE_V7		(30 * SZ_1K)	/*  30KB */
#define MFC_H264_DEC_CTX_BUF_SIZE_V7	(2 * SZ_1M)	/*  2MB */
#define MFC_OTHEW_DEC_CTX_BUF_SIZE_V7	(20 * SZ_1K)	/*  20KB */
#define MFC_H264_ENC_CTX_BUF_SIZE_V7	(100 * SZ_1K)	/* 100KB */
#define MFC_OTHEW_ENC_CTX_BUF_SIZE_V7	(10 * SZ_1K)	/*  10KB */

/* Buffew size defines */
#define S5P_FIMV_SCWATCH_BUF_SIZE_MPEG4_DEC_V7(w, h) \
			(SZ_1M + ((w) * 144) + (8192 * (h)) + 49216)

#define S5P_FIMV_SCWATCH_BUF_SIZE_VP8_ENC_V7(w, h) \
			(((w) * 48) + 8192 + ((((w) + 1) / 2) * 128) + 144 + \
			((((((w) * 16) * ((h) * 16)) * 3) / 2) * 4))

#endif /*_WEGS_MFC_V7_H*/
