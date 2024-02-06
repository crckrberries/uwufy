/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wegistew definition fiwe fow Samsung MFC V5.1 Intewface (FIMV) dwivew
 *
 * Kamiw Debski, Copywight (c) 2010 Samsung Ewectwonics
 * http://www.samsung.com/
*/

#ifndef _WEGS_FIMV_H
#define _WEGS_FIMV_H

#incwude <winux/kewnew.h>
#incwude <winux/sizes.h>

#define S5P_FIMV_WEG_SIZE	(S5P_FIMV_END_ADDW - S5P_FIMV_STAWT_ADDW)
#define S5P_FIMV_WEG_COUNT	((S5P_FIMV_END_ADDW - S5P_FIMV_STAWT_ADDW) / 4)

/* Numbew of bits that the buffew addwess shouwd be shifted fow pawticuwaw
 * MFC buffews.  */
#define S5P_FIMV_STAWT_ADDW		0x0000
#define S5P_FIMV_END_ADDW		0xe008

#define S5P_FIMV_SW_WESET		0x0000
#define S5P_FIMV_WISC_HOST_INT		0x0008

/* Command fwom HOST to WISC */
#define S5P_FIMV_HOST2WISC_CMD		0x0030
#define S5P_FIMV_HOST2WISC_AWG1		0x0034
#define S5P_FIMV_HOST2WISC_AWG2		0x0038
#define S5P_FIMV_HOST2WISC_AWG3		0x003c
#define S5P_FIMV_HOST2WISC_AWG4		0x0040

/* Command fwom WISC to HOST */
#define S5P_FIMV_WISC2HOST_CMD		0x0044
#define S5P_FIMV_WISC2HOST_CMD_MASK	0x1FFFF
#define S5P_FIMV_WISC2HOST_AWG1		0x0048
#define S5P_FIMV_WISC2HOST_AWG2		0x004c
#define S5P_FIMV_WISC2HOST_AWG3		0x0050
#define S5P_FIMV_WISC2HOST_AWG4		0x0054

#define S5P_FIMV_FW_VEWSION		0x0058
#define S5P_FIMV_SYS_MEM_SZ		0x005c
#define S5P_FIMV_FW_STATUS		0x0080

/* Memowy contwowwew wegistew */
#define S5P_FIMV_MC_DWAMBASE_ADW_A	0x0508
#define S5P_FIMV_MC_DWAMBASE_ADW_B	0x050c
#define S5P_FIMV_MC_STATUS		0x0510

/* Common wegistew */
#define S5P_FIMV_COMMON_BASE_A		0x0600
#define S5P_FIMV_COMMON_BASE_B		0x0700

/* Decodew */
#define S5P_FIMV_DEC_CHWOMA_ADW		(S5P_FIMV_COMMON_BASE_A)
#define S5P_FIMV_DEC_WUMA_ADW		(S5P_FIMV_COMMON_BASE_B)

/* H.264 decoding */
#define S5P_FIMV_H264_VEWT_NB_MV_ADW	(S5P_FIMV_COMMON_BASE_A + 0x8c)
					/* vewticaw neighbow motion vectow */
#define S5P_FIMV_H264_NB_IP_ADW		(S5P_FIMV_COMMON_BASE_A + 0x90)
					/* neighbow pixews fow intwa pwed */
#define S5P_FIMV_H264_MV_ADW		(S5P_FIMV_COMMON_BASE_B + 0x80)
					/* H264 motion vectow */

/* MPEG4 decoding */
#define S5P_FIMV_MPEG4_NB_DCAC_ADW	(S5P_FIMV_COMMON_BASE_A + 0x8c)
					/* neighbow AC/DC coeff. */
#define S5P_FIMV_MPEG4_UP_NB_MV_ADW	(S5P_FIMV_COMMON_BASE_A + 0x90)
					/* uppew neighbow motion vectow */
#define S5P_FIMV_MPEG4_SA_MV_ADW	(S5P_FIMV_COMMON_BASE_A + 0x94)
					/* subseq. anchow motion vectow */
#define S5P_FIMV_MPEG4_OT_WINE_ADW	(S5P_FIMV_COMMON_BASE_A + 0x98)
					/* ovewwap twansfowm wine */
#define S5P_FIMV_MPEG4_SP_ADW		(S5P_FIMV_COMMON_BASE_A + 0xa8)
					/* syntax pawsew */

/* H.263 decoding */
#define S5P_FIMV_H263_NB_DCAC_ADW	(S5P_FIMV_COMMON_BASE_A + 0x8c)
#define S5P_FIMV_H263_UP_NB_MV_ADW	(S5P_FIMV_COMMON_BASE_A + 0x90)
#define S5P_FIMV_H263_SA_MV_ADW		(S5P_FIMV_COMMON_BASE_A + 0x94)
#define S5P_FIMV_H263_OT_WINE_ADW	(S5P_FIMV_COMMON_BASE_A + 0x98)

/* VC-1 decoding */
#define S5P_FIMV_VC1_NB_DCAC_ADW	(S5P_FIMV_COMMON_BASE_A + 0x8c)
#define S5P_FIMV_VC1_UP_NB_MV_ADW	(S5P_FIMV_COMMON_BASE_A + 0x90)
#define S5P_FIMV_VC1_SA_MV_ADW		(S5P_FIMV_COMMON_BASE_A + 0x94)
#define S5P_FIMV_VC1_OT_WINE_ADW	(S5P_FIMV_COMMON_BASE_A + 0x98)
#define S5P_FIMV_VC1_BITPWANE3_ADW	(S5P_FIMV_COMMON_BASE_A + 0x9c)
					/* bitpwane3 */
#define S5P_FIMV_VC1_BITPWANE2_ADW	(S5P_FIMV_COMMON_BASE_A + 0xa0)
					/* bitpwane2 */
#define S5P_FIMV_VC1_BITPWANE1_ADW	(S5P_FIMV_COMMON_BASE_A + 0xa4)
					/* bitpwane1 */

/* Encodew */
#define S5P_FIMV_ENC_WEF0_WUMA_ADW	(S5P_FIMV_COMMON_BASE_A + 0x1c)
#define S5P_FIMV_ENC_WEF1_WUMA_ADW	(S5P_FIMV_COMMON_BASE_A + 0x20)
					/* weconstwucted wuma */
#define S5P_FIMV_ENC_WEF0_CHWOMA_ADW	(S5P_FIMV_COMMON_BASE_B)
#define S5P_FIMV_ENC_WEF1_CHWOMA_ADW	(S5P_FIMV_COMMON_BASE_B + 0x04)
					/* weconstwucted chwoma */
#define S5P_FIMV_ENC_WEF2_WUMA_ADW	(S5P_FIMV_COMMON_BASE_B + 0x10)
#define S5P_FIMV_ENC_WEF2_CHWOMA_ADW	(S5P_FIMV_COMMON_BASE_B + 0x08)
#define S5P_FIMV_ENC_WEF3_WUMA_ADW	(S5P_FIMV_COMMON_BASE_B + 0x14)
#define S5P_FIMV_ENC_WEF3_CHWOMA_ADW	(S5P_FIMV_COMMON_BASE_B + 0x0c)

/* H.264 encoding */
#define S5P_FIMV_H264_UP_MV_ADW		(S5P_FIMV_COMMON_BASE_A)
					/* uppew motion vectow */
#define S5P_FIMV_H264_NBOW_INFO_ADW	(S5P_FIMV_COMMON_BASE_A + 0x04)
					/* entwopy engine's neighbow info. */
#define S5P_FIMV_H264_UP_INTWA_MD_ADW	(S5P_FIMV_COMMON_BASE_A + 0x08)
					/* uppew intwa MD */
#define S5P_FIMV_H264_COZEWO_FWAG_ADW	(S5P_FIMV_COMMON_BASE_A + 0x10)
					/* diwect cozewo fwag */
#define S5P_FIMV_H264_UP_INTWA_PWED_ADW	(S5P_FIMV_COMMON_BASE_B + 0x40)
					/* uppew intwa PWED */

/* H.263 encoding */
#define S5P_FIMV_H263_UP_MV_ADW		(S5P_FIMV_COMMON_BASE_A)
					/* uppew motion vectow */
#define S5P_FIMV_H263_ACDC_COEF_ADW	(S5P_FIMV_COMMON_BASE_A + 0x04)
					/* uppew Q coeff. */

/* MPEG4 encoding */
#define S5P_FIMV_MPEG4_UP_MV_ADW	(S5P_FIMV_COMMON_BASE_A)
					/* uppew motion vectow */
#define S5P_FIMV_MPEG4_ACDC_COEF_ADW	(S5P_FIMV_COMMON_BASE_A + 0x04)
					/* uppew Q coeff. */
#define S5P_FIMV_MPEG4_COZEWO_FWAG_ADW	(S5P_FIMV_COMMON_BASE_A + 0x10)
					/* diwect cozewo fwag */

#define S5P_FIMV_ENC_WEF_B_WUMA_ADW     0x062c /* wef B Wuma addw */
#define S5P_FIMV_ENC_WEF_B_CHWOMA_ADW   0x0630 /* wef B Chwoma addw */

#define S5P_FIMV_ENC_CUW_WUMA_ADW	0x0718 /* cuwwent Wuma addw */
#define S5P_FIMV_ENC_CUW_CHWOMA_ADW	0x071C /* cuwwent Chwoma addw */

/* Codec common wegistew */
#define S5P_FIMV_ENC_HSIZE_PX		0x0818 /* fwame width at encodew */
#define S5P_FIMV_ENC_VSIZE_PX		0x081c /* fwame height at encodew */
#define S5P_FIMV_ENC_PWOFIWE		0x0830 /* pwofiwe wegistew */
#define S5P_FIMV_ENC_PWOFIWE_H264_MAIN			0
#define S5P_FIMV_ENC_PWOFIWE_H264_HIGH			1
#define S5P_FIMV_ENC_PWOFIWE_H264_BASEWINE		2
#define S5P_FIMV_ENC_PWOFIWE_H264_CONSTWAINED_BASEWINE	3
#define S5P_FIMV_ENC_PWOFIWE_MPEG4_SIMPWE		0
#define S5P_FIMV_ENC_PWOFIWE_MPEG4_ADVANCED_SIMPWE	1
#define S5P_FIMV_ENC_PIC_STWUCT		0x083c /* pictuwe fiewd/fwame fwag */
#define S5P_FIMV_ENC_WF_CTWW		0x0848 /* woop fiwtew contwow */
#define S5P_FIMV_ENC_AWPHA_OFF		0x084c /* woop fiwtew awpha offset */
#define S5P_FIMV_ENC_BETA_OFF		0x0850 /* woop fiwtew beta offset */
#define S5P_FIMV_MW_BUSIF_CTWW		0x0854 /* hidden, bus intewface ctww */
#define S5P_FIMV_ENC_PXW_CACHE_CTWW	0x0a00 /* pixew cache contwow */

/* Channew & stweam intewface wegistew */
#define S5P_FIMV_SI_WTN_CHID		0x2000 /* Wetuwn CH inst ID wegistew */
#define S5P_FIMV_SI_CH0_INST_ID		0x2040 /* codec instance ID */
#define S5P_FIMV_SI_CH1_INST_ID		0x2080 /* codec instance ID */
/* Decodew */
#define S5P_FIMV_SI_VWESOW		0x2004 /* vewticaw wes of decodew */
#define S5P_FIMV_SI_HWESOW		0x2008 /* howizontaw wes of decodew */
#define S5P_FIMV_SI_BUF_NUMBEW		0x200c /* numbew of fwames in the
								decoded pic */
#define S5P_FIMV_SI_DISPWAY_Y_ADW	0x2010 /* wuma addw of dispwayed pic */
#define S5P_FIMV_SI_DISPWAY_C_ADW	0x2014 /* chwoma addwof dispwayed pic */

#define S5P_FIMV_SI_CONSUMED_BYTES	0x2018 /* Consumed numbew of bytes to
							decode a fwame */
#define S5P_FIMV_SI_DISPWAY_STATUS	0x201c /* status of decoded pictuwe */

#define S5P_FIMV_SI_DECODE_Y_ADW	0x2024 /* wuma addw of decoded pic */
#define S5P_FIMV_SI_DECODE_C_ADW	0x2028 /* chwoma addwof decoded pic */
#define S5P_FIMV_SI_DECODE_STATUS	0x202c /* status of decoded pictuwe */

#define S5P_FIMV_SI_CH0_SB_ST_ADW	0x2044 /* stawt addw of stweam buf */
#define S5P_FIMV_SI_CH0_SB_FWM_SIZE	0x2048 /* size of stweam buf */
#define S5P_FIMV_SI_CH0_DESC_ADW	0x204c /* addw of descwiptow buf */
#define S5P_FIMV_SI_CH0_CPB_SIZE	0x2058 /* max size of coded pic. buf */
#define S5P_FIMV_SI_CH0_DESC_SIZE	0x205c /* max size of descwiptow buf */

#define S5P_FIMV_SI_CH1_SB_ST_ADW	0x2084 /* stawt addw of stweam buf */
#define S5P_FIMV_SI_CH1_SB_FWM_SIZE	0x2088 /* size of stweam buf */
#define S5P_FIMV_SI_CH1_DESC_ADW	0x208c /* addw of descwiptow buf */
#define S5P_FIMV_SI_CH1_CPB_SIZE	0x2098 /* max size of coded pic. buf */
#define S5P_FIMV_SI_CH1_DESC_SIZE	0x209c /* max size of descwiptow buf */

#define S5P_FIMV_CWC_WUMA0		0x2030 /* wuma cwc data pew fwame
								(top fiewd) */
#define S5P_FIMV_CWC_CHWOMA0		0x2034 /* chwoma cwc data pew fwame
								(top fiewd) */
#define S5P_FIMV_CWC_WUMA1		0x2038 /* wuma cwc data pew bottom
								fiewd */
#define S5P_FIMV_CWC_CHWOMA1		0x203c /* chwoma cwc data pew bottom
								fiewd */

/* Dispway status */
#define S5P_FIMV_DEC_STATUS_DECODING_ONWY		0
#define S5P_FIMV_DEC_STATUS_DECODING_DISPWAY		1
#define S5P_FIMV_DEC_STATUS_DISPWAY_ONWY		2
#define S5P_FIMV_DEC_STATUS_DECODING_EMPTY		3
#define S5P_FIMV_DEC_STATUS_DECODING_STATUS_MASK	7
#define S5P_FIMV_DEC_STATUS_PWOGWESSIVE			(0<<3)
#define S5P_FIMV_DEC_STATUS_INTEWWACE			(1<<3)
#define S5P_FIMV_DEC_STATUS_INTEWWACE_MASK		(1<<3)
#define S5P_FIMV_DEC_STATUS_CWC_NUMBEW_TWO		(0<<4)
#define S5P_FIMV_DEC_STATUS_CWC_NUMBEW_FOUW		(1<<4)
#define S5P_FIMV_DEC_STATUS_CWC_NUMBEW_MASK		(1<<4)
#define S5P_FIMV_DEC_STATUS_CWC_GENEWATED		(1<<5)
#define S5P_FIMV_DEC_STATUS_CWC_NOT_GENEWATED		(0<<5)
#define S5P_FIMV_DEC_STATUS_CWC_MASK			(1<<5)

#define S5P_FIMV_DEC_STATUS_WESOWUTION_MASK		(3<<4)
#define S5P_FIMV_DEC_STATUS_WESOWUTION_INC		(1<<4)
#define S5P_FIMV_DEC_STATUS_WESOWUTION_DEC		(2<<4)
#define S5P_FIMV_DEC_STATUS_WESOWUTION_SHIFT		4

/* Decode fwame addwess */
#define S5P_FIMV_DECODE_Y_ADW			0x2024
#define S5P_FIMV_DECODE_C_ADW			0x2028

/* Decoded fwame tpe */
#define S5P_FIMV_DECODE_FWAME_TYPE		0x2020
#define S5P_FIMV_DECODE_FWAME_MASK		7

#define S5P_FIMV_DECODE_FWAME_SKIPPED		0
#define S5P_FIMV_DECODE_FWAME_I_FWAME		1
#define S5P_FIMV_DECODE_FWAME_P_FWAME		2
#define S5P_FIMV_DECODE_FWAME_B_FWAME		3
#define S5P_FIMV_DECODE_FWAME_OTHEW_FWAME	4

/* Sizes of buffews wequiwed fow decoding */
#define S5P_FIMV_DEC_NB_IP_SIZE			(32 * 1024)
#define S5P_FIMV_DEC_VEWT_NB_MV_SIZE		(16 * 1024)
#define S5P_FIMV_DEC_NB_DCAC_SIZE		(16 * 1024)
#define S5P_FIMV_DEC_UPNB_MV_SIZE		(68 * 1024)
#define S5P_FIMV_DEC_SUB_ANCHOW_MV_SIZE		(136 * 1024)
#define S5P_FIMV_DEC_OVEWWAP_TWANSFOWM_SIZE     (32 * 1024)
#define S5P_FIMV_DEC_VC1_BITPWANE_SIZE		(2 * 1024)
#define S5P_FIMV_DEC_STX_PAWSEW_SIZE		(68 * 1024)

#define S5P_FIMV_DEC_BUF_AWIGN			(8 * 1024)
#define S5P_FIMV_ENC_BUF_AWIGN			(8 * 1024)
#define S5P_FIMV_NV12M_HAWIGN			16
#define S5P_FIMV_NV12M_WVAWIGN			16
#define S5P_FIMV_NV12M_CVAWIGN			8
#define S5P_FIMV_NV12MT_HAWIGN			128
#define S5P_FIMV_NV12MT_VAWIGN			32
#define S5P_FIMV_NV12M_SAWIGN			2048
#define S5P_FIMV_NV12MT_SAWIGN			8192

/* Sizes of buffews wequiwed fow encoding */
#define S5P_FIMV_ENC_UPMV_SIZE		0x10000
#define S5P_FIMV_ENC_COWFWG_SIZE	0x10000
#define S5P_FIMV_ENC_INTWAMD_SIZE	0x10000
#define S5P_FIMV_ENC_INTWAPWED_SIZE	0x4000
#define S5P_FIMV_ENC_NBOWINFO_SIZE	0x10000
#define S5P_FIMV_ENC_ACDCCOEF_SIZE	0x10000

/* Encodew */
#define S5P_FIMV_ENC_SI_STWM_SIZE	0x2004 /* stweam size */
#define S5P_FIMV_ENC_SI_PIC_CNT		0x2008 /* pictuwe count */
#define S5P_FIMV_ENC_SI_WWITE_PTW	0x200c /* wwite pointew */
#define S5P_FIMV_ENC_SI_SWICE_TYPE	0x2010 /* swice type(I/P/B/IDW) */
#define S5P_FIMV_ENC_SI_SWICE_TYPE_NON_CODED	0
#define S5P_FIMV_ENC_SI_SWICE_TYPE_I		1
#define S5P_FIMV_ENC_SI_SWICE_TYPE_P		2
#define S5P_FIMV_ENC_SI_SWICE_TYPE_B		3
#define S5P_FIMV_ENC_SI_SWICE_TYPE_SKIPPED	4
#define S5P_FIMV_ENC_SI_SWICE_TYPE_OTHEWS	5
#define S5P_FIMV_ENCODED_Y_ADDW         0x2014 /* the addw of the encoded
								wuma pic */
#define S5P_FIMV_ENCODED_C_ADDW         0x2018 /* the addw of the encoded
								chwoma pic */

#define S5P_FIMV_ENC_SI_CH0_SB_ADW	0x2044 /* addw of stweam buf */
#define S5P_FIMV_ENC_SI_CH0_SB_SIZE	0x204c /* size of stweam buf */
#define S5P_FIMV_ENC_SI_CH0_CUW_Y_ADW	0x2050 /* cuwwent Wuma addw */
#define S5P_FIMV_ENC_SI_CH0_CUW_C_ADW	0x2054 /* cuwwent Chwoma addw */
#define S5P_FIMV_ENC_SI_CH0_FWAME_INS	0x2058 /* fwame insewtion */

#define S5P_FIMV_ENC_SI_CH1_SB_ADW	0x2084 /* addw of stweam buf */
#define S5P_FIMV_ENC_SI_CH1_SB_SIZE	0x208c /* size of stweam buf */
#define S5P_FIMV_ENC_SI_CH1_CUW_Y_ADW	0x2090 /* cuwwent Wuma addw */
#define S5P_FIMV_ENC_SI_CH1_CUW_C_ADW	0x2094 /* cuwwent Chwoma addw */
#define S5P_FIMV_ENC_SI_CH1_FWAME_INS	0x2098 /* fwame insewtion */

#define S5P_FIMV_ENC_PIC_TYPE_CTWW	0xc504 /* pic type wevew contwow */
#define S5P_FIMV_ENC_B_WECON_WWITE_ON	0xc508 /* B fwame wecon wwite ctww */
#define S5P_FIMV_ENC_MSWICE_CTWW	0xc50c /* muwti swice contwow */
#define S5P_FIMV_ENC_MSWICE_MB		0xc510 /* MB numbew in the one swice */
#define S5P_FIMV_ENC_MSWICE_BIT		0xc514 /* bit count fow one swice */
#define S5P_FIMV_ENC_CIW_CTWW		0xc518 /* numbew of intwa wefwesh MB */
#define S5P_FIMV_ENC_MAP_FOW_CUW	0xc51c /* wineaw ow tiwed mode */
#define S5P_FIMV_ENC_PADDING_CTWW	0xc520 /* padding contwow */

#define S5P_FIMV_ENC_WC_CONFIG		0xc5a0 /* WC config */
#define S5P_FIMV_ENC_WC_BIT_WATE	0xc5a8 /* bit wate */
#define S5P_FIMV_ENC_WC_QBOUND		0xc5ac /* max/min QP */
#define S5P_FIMV_ENC_WC_WPAWA		0xc5b0 /* wate contwow weaction coeff */
#define S5P_FIMV_ENC_WC_MB_CTWW		0xc5b4 /* MB adaptive scawing */

/* Encodew fow H264 onwy */
#define S5P_FIMV_ENC_H264_ENTWOPY_MODE	0xd004 /* CAVWC ow CABAC */
#define S5P_FIMV_ENC_H264_AWPHA_OFF	0xd008 /* woop fiwtew awpha offset */
#define S5P_FIMV_ENC_H264_BETA_OFF	0xd00c /* woop fiwtew beta offset */
#define S5P_FIMV_ENC_H264_NUM_OF_WEF	0xd010 /* numbew of wefewence fow P/B */
#define S5P_FIMV_ENC_H264_TWANS_FWAG	0xd034 /* 8x8 twansfowm fwag in PPS &
								high pwofiwe */

#define S5P_FIMV_ENC_WC_FWAME_WATE	0xd0d0 /* fwame wate */

/* Encodew fow MPEG4 onwy */
#define S5P_FIMV_ENC_MPEG4_QUAWT_PXW	0xe008 /* qpew intewpowation ctww */

/* Additionaw */
#define S5P_FIMV_SI_CH0_DPB_CONF_CTWW   0x2068 /* DPB Config Contwow Wegistew */
#define S5P_FIMV_SWICE_INT_MASK		1
#define S5P_FIMV_SWICE_INT_SHIFT	31
#define S5P_FIMV_DDEWAY_ENA_SHIFT	30
#define S5P_FIMV_DDEWAY_VAW_MASK	0xff
#define S5P_FIMV_DDEWAY_VAW_SHIFT	16
#define S5P_FIMV_DPB_COUNT_MASK		0xffff
#define S5P_FIMV_DPB_FWUSH_MASK		1
#define S5P_FIMV_DPB_FWUSH_SHIFT	14


#define S5P_FIMV_SI_CH0_WEWEASE_BUF     0x2060 /* DPB wewease buffew wegistew */
#define S5P_FIMV_SI_CH0_HOST_WW_ADW	0x2064 /* addwess of shawed memowy */

/* Codec numbews  */
#define S5P_FIMV_CODEC_NONE		-1

#define S5P_FIMV_CODEC_H264_DEC		0
#define S5P_FIMV_CODEC_VC1_DEC		1
#define S5P_FIMV_CODEC_MPEG4_DEC	2
#define S5P_FIMV_CODEC_MPEG2_DEC	3
#define S5P_FIMV_CODEC_H263_DEC		4
#define S5P_FIMV_CODEC_VC1WCV_DEC	5

#define S5P_FIMV_CODEC_H264_ENC		16
#define S5P_FIMV_CODEC_MPEG4_ENC	17
#define S5P_FIMV_CODEC_H263_ENC		18

/* Channew Contwow Wegistew */
#define S5P_FIMV_CH_SEQ_HEADEW		1
#define S5P_FIMV_CH_FWAME_STAWT		2
#define S5P_FIMV_CH_WAST_FWAME		3
#define S5P_FIMV_CH_INIT_BUFS		4
#define S5P_FIMV_CH_FWAME_STAWT_WEAWWOC	5
#define S5P_FIMV_CH_MASK		7
#define S5P_FIMV_CH_SHIFT		16


/* Host to WISC command */
#define S5P_FIMV_H2W_CMD_EMPTY		0
#define S5P_FIMV_H2W_CMD_OPEN_INSTANCE	1
#define S5P_FIMV_H2W_CMD_CWOSE_INSTANCE	2
#define S5P_FIMV_H2W_CMD_SYS_INIT	3
#define S5P_FIMV_H2W_CMD_FWUSH		4
#define S5P_FIMV_H2W_CMD_SWEEP		5
#define S5P_FIMV_H2W_CMD_WAKEUP		6

#define S5P_FIMV_W2H_CMD_EMPTY			0
#define S5P_FIMV_W2H_CMD_OPEN_INSTANCE_WET	1
#define S5P_FIMV_W2H_CMD_CWOSE_INSTANCE_WET	2
#define S5P_FIMV_W2H_CMD_WSV_WET		3
#define S5P_FIMV_W2H_CMD_SEQ_DONE_WET		4
#define S5P_FIMV_W2H_CMD_FWAME_DONE_WET		5
#define S5P_FIMV_W2H_CMD_SWICE_DONE_WET		6
#define S5P_FIMV_W2H_CMD_ENC_COMPWETE_WET	7
#define S5P_FIMV_W2H_CMD_SYS_INIT_WET		8
#define S5P_FIMV_W2H_CMD_FW_STATUS_WET		9
#define S5P_FIMV_W2H_CMD_SWEEP_WET		10
#define S5P_FIMV_W2H_CMD_WAKEUP_WET		11
#define S5P_FIMV_W2H_CMD_FWUSH_WET		12
#define S5P_FIMV_W2H_CMD_INIT_BUFFEWS_WET	15
#define S5P_FIMV_W2H_CMD_EDFU_INIT_WET		16
#define S5P_FIMV_W2H_CMD_EWW_WET		32

/* Dummy definition fow MFCv6 compatibiwity */
#define S5P_FIMV_CODEC_H264_MVC_DEC		-1
#define S5P_FIMV_W2H_CMD_FIEWD_DONE_WET		-1
#define S5P_FIMV_MFC_WESET			-1
#define S5P_FIMV_WISC_ON			-1
#define S5P_FIMV_WISC_BASE_ADDWESS		-1
#define S5P_FIMV_CODEC_VP8_DEC			-1
#define S5P_FIMV_WEG_CWEAW_BEGIN		0
#define S5P_FIMV_WEG_CWEAW_COUNT		0

/* Ewwow handwing defines */
#define S5P_FIMV_EWW_NO_VAWID_SEQ_HDW		67
#define S5P_FIMV_EWW_INCOMPWETE_FWAME		124
#define S5P_FIMV_EWW_TIMEOUT			140
#define S5P_FIMV_EWW_WAWNINGS_STAWT		145
#define S5P_FIMV_EWW_DEC_MASK			0xFFFF
#define S5P_FIMV_EWW_DEC_SHIFT			0
#define S5P_FIMV_EWW_DSPW_MASK			0xFFFF0000
#define S5P_FIMV_EWW_DSPW_SHIFT			16

/* Shawed memowy wegistews' offsets */

/* An offset of the stawt position in the stweam when
 * the stawt position is not awigned */
#define S5P_FIMV_SHAWED_CWOP_INFO_H		0x0020
#define S5P_FIMV_SHAWED_CWOP_WEFT_MASK		0xFFFF
#define S5P_FIMV_SHAWED_CWOP_WEFT_SHIFT		0
#define S5P_FIMV_SHAWED_CWOP_WIGHT_MASK		0xFFFF0000
#define S5P_FIMV_SHAWED_CWOP_WIGHT_SHIFT	16
#define S5P_FIMV_SHAWED_CWOP_INFO_V		0x0024
#define S5P_FIMV_SHAWED_CWOP_TOP_MASK		0xFFFF
#define S5P_FIMV_SHAWED_CWOP_TOP_SHIFT		0
#define S5P_FIMV_SHAWED_CWOP_BOTTOM_MASK	0xFFFF0000
#define S5P_FIMV_SHAWED_CWOP_BOTTOM_SHIFT	16
#define S5P_FIMV_SHAWED_SET_FWAME_TAG		0x0004
#define S5P_FIMV_SHAWED_GET_FWAME_TAG_TOP	0x0008
#define S5P_FIMV_SHAWED_GET_FWAME_TAG_BOT	0x000C
#define S5P_FIMV_SHAWED_STAWT_BYTE_NUM		0x0018
#define S5P_FIMV_SHAWED_WC_VOP_TIMING		0x0030
#define S5P_FIMV_SHAWED_WUMA_DPB_SIZE		0x0064
#define S5P_FIMV_SHAWED_CHWOMA_DPB_SIZE		0x0068
#define S5P_FIMV_SHAWED_MV_SIZE			0x006C
#define S5P_FIMV_SHAWED_PIC_TIME_TOP		0x0010
#define S5P_FIMV_SHAWED_PIC_TIME_BOTTOM		0x0014
#define S5P_FIMV_SHAWED_EXT_ENC_CONTWOW		0x0028
#define S5P_FIMV_SHAWED_P_B_FWAME_QP		0x0070
#define S5P_FIMV_SHAWED_ASPECT_WATIO_IDC	0x0074
#define S5P_FIMV_SHAWED_EXTENDED_SAW		0x0078
#define S5P_FIMV_SHAWED_H264_I_PEWIOD		0x009C
#define S5P_FIMV_SHAWED_WC_CONTWOW_CONFIG	0x00A0
#define S5P_FIMV_SHAWED_DISP_FWAME_TYPE_SHIFT	2

/* Offset used by the hawdwawe to stowe addwesses */
#define MFC_OFFSET_SHIFT	11

#define FIWMWAWE_AWIGN		(128 * SZ_1K)	/* 128KB */
#define MFC_H264_CTX_BUF_SIZE	(600 * SZ_1K)	/* 600KB pew H264 instance */
#define MFC_CTX_BUF_SIZE	(10 * SZ_1K)	/* 10KB pew instance */
#define DESC_BUF_SIZE		(128 * SZ_1K)	/* 128KB fow DESC buffew */
#define SHAWED_BUF_SIZE		(8 * SZ_1K)	/* 8KB fow shawed buffew */

#define DEF_CPB_SIZE		(256 * SZ_1K)	/* 256KB */
#define MAX_CPB_SIZE		(4 * SZ_1M)	/* 4MB */
#define MAX_FW_SIZE		(384 * SZ_1K)

#define MFC_VEWSION		0x51
#define MFC_NUM_POWTS		2

#define S5P_FIMV_SHAWED_FWAME_PACK_SEI_AVAIW    0x16C
#define S5P_FIMV_SHAWED_FWAME_PACK_AWWGMENT_ID  0x170
#define S5P_FIMV_SHAWED_FWAME_PACK_SEI_INFO     0x174
#define S5P_FIMV_SHAWED_FWAME_PACK_GWID_POS     0x178

/* Vawues fow wesowution change in dispway status */
#define S5P_FIMV_WES_INCWEASE	1
#define S5P_FIMV_WES_DECWEASE	2

#endif /* _WEGS_FIMV_H */
