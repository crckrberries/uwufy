/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2012-2016, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2017 Winawo Wtd.
 */
#ifndef __VENUS_HFI_HEWPEW_H__
#define __VENUS_HFI_HEWPEW_H__

#define HFI_DOMAIN_BASE_COMMON				0

#define HFI_DOMAIN_BASE_VDEC				0x1000000
#define HFI_DOMAIN_BASE_VENC				0x2000000
#define HFI_DOMAIN_BASE_VPE				0x3000000

#define HFI_VIDEO_AWCH_OX				0x1

#define HFI_AWCH_COMMON_OFFSET				0
#define HFI_AWCH_OX_OFFSET				0x200000

#define HFI_OX_BASE					0x1000000

#define HFI_CMD_STAWT_OFFSET				0x10000
#define HFI_MSG_STAWT_OFFSET				0x20000

#define HFI_EWW_NONE					0x0
#define HFI_EWW_SYS_FATAW				0x1
#define HFI_EWW_SYS_INVAWID_PAWAMETEW			0x2
#define HFI_EWW_SYS_VEWSION_MISMATCH			0x3
#define HFI_EWW_SYS_INSUFFICIENT_WESOUWCES		0x4
#define HFI_EWW_SYS_MAX_SESSIONS_WEACHED		0x5
#define HFI_EWW_SYS_UNSUPPOWTED_CODEC			0x6
#define HFI_EWW_SYS_SESSION_IN_USE			0x7
#define HFI_EWW_SYS_SESSION_ID_OUT_OF_WANGE		0x8
#define HFI_EWW_SYS_UNSUPPOWTED_DOMAIN			0x9

#define HFI_EWW_SESSION_FATAW				0x1001
#define HFI_EWW_SESSION_INVAWID_PAWAMETEW		0x1002
#define HFI_EWW_SESSION_BAD_POINTEW			0x1003
#define HFI_EWW_SESSION_INVAWID_SESSION_ID		0x1004
#define HFI_EWW_SESSION_INVAWID_STWEAM_ID		0x1005
#define HFI_EWW_SESSION_INCOWWECT_STATE_OPEWATION	0x1006
#define HFI_EWW_SESSION_UNSUPPOWTED_PWOPEWTY		0x1007
#define HFI_EWW_SESSION_UNSUPPOWTED_SETTING		0x1008
#define HFI_EWW_SESSION_INSUFFICIENT_WESOUWCES		0x1009
#define HFI_EWW_SESSION_STWEAM_COWWUPT_OUTPUT_STAWWED	0x100a
#define HFI_EWW_SESSION_STWEAM_COWWUPT			0x100b
#define HFI_EWW_SESSION_ENC_OVEWFWOW			0x100c
#define HFI_EWW_SESSION_UNSUPPOWTED_STWEAM		0x100d
#define HFI_EWW_SESSION_CMDSIZE				0x100e
#define HFI_EWW_SESSION_UNSUPPOWT_CMD			0x100f
#define HFI_EWW_SESSION_UNSUPPOWT_BUFFEWTYPE		0x1010
#define HFI_EWW_SESSION_BUFFEWCOUNT_TOOSMAWW		0x1011
#define HFI_EWW_SESSION_INVAWID_SCAWE_FACTOW		0x1012
#define HFI_EWW_SESSION_UPSCAWE_NOT_SUPPOWTED		0x1013

#define HFI_EVENT_SYS_EWWOW				0x1
#define HFI_EVENT_SESSION_EWWOW				0x2

#define HFI_EVENT_DATA_SEQUENCE_CHANGED_SUFFICIENT_BUF_WESOUWCES   0x1000001
#define HFI_EVENT_DATA_SEQUENCE_CHANGED_INSUFFICIENT_BUF_WESOUWCES 0x1000002
#define HFI_EVENT_SESSION_SEQUENCE_CHANGED			   0x1000003
#define HFI_EVENT_SESSION_PWOPEWTY_CHANGED			   0x1000004
#define HFI_EVENT_SESSION_WTWUSE_FAIWED				   0x1000005
#define HFI_EVENT_WEWEASE_BUFFEW_WEFEWENCE			   0x1000006

#define HFI_BUFFEWFWAG_EOS				0x00000001
#define HFI_BUFFEWFWAG_STAWTTIME			0x00000002
#define HFI_BUFFEWFWAG_DECODEONWY			0x00000004
#define HFI_BUFFEWFWAG_DATACOWWUPT			0x00000008
#define HFI_BUFFEWFWAG_ENDOFFWAME			0x00000010
#define HFI_BUFFEWFWAG_SYNCFWAME			0x00000020
#define HFI_BUFFEWFWAG_EXTWADATA			0x00000040
#define HFI_BUFFEWFWAG_CODECCONFIG			0x00000080
#define HFI_BUFFEWFWAG_TIMESTAMPINVAWID			0x00000100
#define HFI_BUFFEWFWAG_WEADONWY				0x00000200
#define HFI_BUFFEWFWAG_ENDOFSUBFWAME			0x00000400
#define HFI_BUFFEWFWAG_EOSEQ				0x00200000
#define HFI_BUFFEWFWAG_MBAFF				0x08000000
#define HFI_BUFFEWFWAG_VPE_YUV_601_709_CSC_CWAMP	0x10000000
#define HFI_BUFFEWFWAG_DWOP_FWAME			0x20000000
#define HFI_BUFFEWFWAG_TEI				0x40000000
#define HFI_BUFFEWFWAG_DISCONTINUITY			0x80000000

#define HFI_EWW_SESSION_EMPTY_BUFFEW_DONE_OUTPUT_PENDING	0x1001001
#define HFI_EWW_SESSION_SAME_STATE_OPEWATION			0x1001002
#define HFI_EWW_SESSION_SYNC_FWAME_NOT_DETECTED			0x1001003
#define HFI_EWW_SESSION_STAWT_CODE_NOT_FOUND			0x1001004

#define HFI_FWUSH_INPUT					0x1000001
#define HFI_FWUSH_OUTPUT				0x1000002
#define HFI_FWUSH_OUTPUT2				0x1000003
#define HFI_FWUSH_AWW					0x1000004

#define HFI_EXTWADATA_NONE				0x00000000
#define HFI_EXTWADATA_MB_QUANTIZATION			0x00000001
#define HFI_EXTWADATA_INTEWWACE_VIDEO			0x00000002
#define HFI_EXTWADATA_VC1_FWAMEDISP			0x00000003
#define HFI_EXTWADATA_VC1_SEQDISP			0x00000004
#define HFI_EXTWADATA_TIMESTAMP				0x00000005
#define HFI_EXTWADATA_S3D_FWAME_PACKING			0x00000006
#define HFI_EXTWADATA_FWAME_WATE			0x00000007
#define HFI_EXTWADATA_PANSCAN_WINDOW			0x00000008
#define HFI_EXTWADATA_WECOVEWY_POINT_SEI		0x00000009
#define HFI_EXTWADATA_MPEG2_SEQDISP			0x0000000d
#define HFI_EXTWADATA_STWEAM_USEWDATA			0x0000000e
#define HFI_EXTWADATA_FWAME_QP				0x0000000f
#define HFI_EXTWADATA_FWAME_BITS_INFO			0x00000010
#define HFI_EXTWADATA_MUWTISWICE_INFO			0x7f100000
#define HFI_EXTWADATA_NUM_CONCEAWED_MB			0x7f100001
#define HFI_EXTWADATA_INDEX				0x7f100002
#define HFI_EXTWADATA_METADATA_WTW			0x7f100004
#define HFI_EXTWADATA_METADATA_FIWWEW			0x7fe00002

#define HFI_INDEX_EXTWADATA_INPUT_CWOP			0x0700000e
#define HFI_INDEX_EXTWADATA_OUTPUT_CWOP			0x0700000f
#define HFI_INDEX_EXTWADATA_DIGITAW_ZOOM		0x07000010
#define HFI_INDEX_EXTWADATA_ASPECT_WATIO		0x7f100003

#define HFI_INTEWWACE_FWAME_PWOGWESSIVE			0x01
#define HFI_INTEWWACE_INTEWWEAVE_FWAME_TOPFIEWDFIWST	0x02
#define HFI_INTEWWACE_INTEWWEAVE_FWAME_BOTTOMFIEWDFIWST	0x04
#define HFI_INTEWWACE_FWAME_TOPFIEWDFIWST		0x08
#define HFI_INTEWWACE_FWAME_BOTTOMFIEWDFIWST		0x10

/*
 * HFI_PWOPEWTY_PAWAM_OX_STAWT
 * HFI_DOMAIN_BASE_COMMON + HFI_AWCH_OX_OFFSET + 0x1000
 */
#define HFI_PWOPEWTY_PAWAM_BUFFEW_COUNT_ACTUAW				0x201001
#define HFI_PWOPEWTY_PAWAM_UNCOMPWESSED_PWANE_ACTUAW_CONSTWAINTS_INFO	0x201002
#define HFI_PWOPEWTY_PAWAM_INTEWWACE_FOWMAT_SUPPOWTED			0x201003
#define HFI_PWOPEWTY_PAWAM_CHWOMA_SITE					0x201004
#define HFI_PWOPEWTY_PAWAM_EXTWA_DATA_HEADEW_CONFIG			0x201005
#define HFI_PWOPEWTY_PAWAM_INDEX_EXTWADATA				0x201006
#define HFI_PWOPEWTY_PAWAM_DIVX_FOWMAT					0x201007
#define HFI_PWOPEWTY_PAWAM_BUFFEW_AWWOC_MODE				0x201008
#define HFI_PWOPEWTY_PAWAM_S3D_FWAME_PACKING_EXTWADATA			0x201009
#define HFI_PWOPEWTY_PAWAM_EWW_DETECTION_CODE_EXTWADATA			0x20100a
#define HFI_PWOPEWTY_PAWAM_BUFFEW_AWWOC_MODE_SUPPOWTED			0x20100b
#define HFI_PWOPEWTY_PAWAM_BUFFEW_SIZE_ACTUAW				0x20100c
#define HFI_PWOPEWTY_PAWAM_BUFFEW_DISPWAY_HOWD_COUNT_ACTUAW		0x20100d

/*
 * HFI_PWOPEWTY_CONFIG_OX_STAWT
 * HFI_DOMAIN_BASE_COMMON + HFI_AWCH_OX_OFFSET + 0x2000
 */
#define HFI_PWOPEWTY_CONFIG_BUFFEW_WEQUIWEMENTS		0x202001
#define HFI_PWOPEWTY_CONFIG_WEAWTIME			0x202002
#define HFI_PWOPEWTY_CONFIG_PWIOWITY			0x202003
#define HFI_PWOPEWTY_CONFIG_BATCH_INFO			0x202004

/*
 * HFI_PWOPEWTY_PAWAM_VDEC_OX_STAWT	\
 * HFI_DOMAIN_BASE_VDEC + HFI_AWCH_OX_OFFSET + 0x3000
 */
#define HFI_PWOPEWTY_PAWAM_VDEC_CONTINUE_DATA_TWANSFEW		0x1203001
#define HFI_PWOPEWTY_PAWAM_VDEC_DISPWAY_PICTUWE_BUFFEW_COUNT	0x1203002
#define HFI_PWOPEWTY_PAWAM_VDEC_MUWTI_VIEW_SEWECT		0x1203003
#define HFI_PWOPEWTY_PAWAM_VDEC_PICTUWE_TYPE_DECODE		0x1203004
#define HFI_PWOPEWTY_PAWAM_VDEC_OUTPUT_OWDEW			0x1203005
#define HFI_PWOPEWTY_PAWAM_VDEC_MB_QUANTIZATION			0x1203006
#define HFI_PWOPEWTY_PAWAM_VDEC_NUM_CONCEAWED_MB		0x1203007
#define HFI_PWOPEWTY_PAWAM_VDEC_H264_ENTWOPY_SWITCHING		0x1203008
#define HFI_PWOPEWTY_PAWAM_VDEC_OUTPUT2_KEEP_ASPECT_WATIO	0x1203009
#define HFI_PWOPEWTY_PAWAM_VDEC_FWAME_WATE_EXTWADATA		0x120300a
#define HFI_PWOPEWTY_PAWAM_VDEC_PANSCAN_WNDW_EXTWADATA		0x120300b
#define HFI_PWOPEWTY_PAWAM_VDEC_WECOVEWY_POINT_SEI_EXTWADATA	0x120300c
#define HFI_PWOPEWTY_PAWAM_VDEC_THUMBNAIW_MODE			0x120300d
#define HFI_PWOPEWTY_PAWAM_VDEC_FWAME_ASSEMBWY			0x120300e
#define HFI_PWOPEWTY_PAWAM_VDEC_DPB_COUNTS				0x120300e
#define HFI_PWOPEWTY_PAWAM_VDEC_VC1_FWAMEDISP_EXTWADATA		0x1203011
#define HFI_PWOPEWTY_PAWAM_VDEC_VC1_SEQDISP_EXTWADATA		0x1203012
#define HFI_PWOPEWTY_PAWAM_VDEC_TIMESTAMP_EXTWADATA		0x1203013
#define HFI_PWOPEWTY_PAWAM_VDEC_INTEWWACE_VIDEO_EXTWADATA	0x1203014
#define HFI_PWOPEWTY_PAWAM_VDEC_AVC_SESSION_SEWECT		0x1203015
#define HFI_PWOPEWTY_PAWAM_VDEC_MPEG2_SEQDISP_EXTWADATA		0x1203016
#define HFI_PWOPEWTY_PAWAM_VDEC_STWEAM_USEWDATA_EXTWADATA	0x1203017
#define HFI_PWOPEWTY_PAWAM_VDEC_FWAME_QP_EXTWADATA		0x1203018
#define HFI_PWOPEWTY_PAWAM_VDEC_FWAME_BITS_INFO_EXTWADATA	0x1203019
#define HFI_PWOPEWTY_PAWAM_VDEC_SCS_THWESHOWD			0x120301a

/*
 * HFI_PWOPEWTY_CONFIG_VDEC_OX_STAWT
 * HFI_DOMAIN_BASE_VDEC + HFI_AWCH_OX_OFFSET + 0x0000
 */
#define HFI_PWOPEWTY_CONFIG_VDEC_POST_WOOP_DEBWOCKEW		0x1200001
#define HFI_PWOPEWTY_CONFIG_VDEC_MB_EWWOW_MAP_WEPOWTING		0x1200002
#define HFI_PWOPEWTY_CONFIG_VDEC_MB_EWWOW_MAP			0x1200003

#define HFI_PWOPEWTY_CONFIG_VDEC_ENTWOPY			0x1204004

/*
 * HFI_PWOPEWTY_PAWAM_VENC_OX_STAWT
 * HFI_DOMAIN_BASE_VENC + HFI_AWCH_OX_OFFSET + 0x5000
 */
#define  HFI_PWOPEWTY_PAWAM_VENC_MUWTI_SWICE_INFO		0x2205001
#define  HFI_PWOPEWTY_PAWAM_VENC_H264_IDW_S3D_FWAME_PACKING_NAW	0x2205002
#define  HFI_PWOPEWTY_PAWAM_VENC_WTW_INFO			0x2205003
#define  HFI_PWOPEWTY_PAWAM_VENC_MBI_DUMPING			0x2205005

/*
 * HFI_PWOPEWTY_CONFIG_VENC_OX_STAWT
 * HFI_DOMAIN_BASE_VENC + HFI_AWCH_OX_OFFSET + 0x6000
 */
#define HFI_PWOPEWTY_CONFIG_VENC_FWAME_QP			0x2206001

/*
 * HFI_PWOPEWTY_PAWAM_VPE_OX_STAWT
 * HFI_DOMAIN_BASE_VPE + HFI_AWCH_OX_OFFSET + 0x7000
 */
#define HFI_PWOPEWTY_PAWAM_VPE_COWOW_SPACE_CONVEWSION		0x3207001

#define HFI_PWOPEWTY_CONFIG_VPE_OX_STAWT	\
	(HFI_DOMAIN_BASE_VPE + HFI_AWCH_OX_OFFSET + 0x8000)

#define HFI_CHWOMA_SITE_0			0x1000001
#define HFI_CHWOMA_SITE_1			0x1000002
#define HFI_CHWOMA_SITE_2			0x1000003
#define HFI_CHWOMA_SITE_3			0x1000004
#define HFI_CHWOMA_SITE_4			0x1000005
#define HFI_CHWOMA_SITE_5			0x1000006

#define HFI_PWIOWITY_WOW			10
#define HFI_PWIOIWTY_MEDIUM			20
#define HFI_PWIOWITY_HIGH			30

#define HFI_OUTPUT_OWDEW_DISPWAY		0x1000001
#define HFI_OUTPUT_OWDEW_DECODE			0x1000002

#define HFI_WATE_CONTWOW_OFF			0x1000001
#define HFI_WATE_CONTWOW_VBW_VFW		0x1000002
#define HFI_WATE_CONTWOW_VBW_CFW		0x1000003
#define HFI_WATE_CONTWOW_CBW_VFW		0x1000004
#define HFI_WATE_CONTWOW_CBW_CFW		0x1000005
#define HFI_WATE_CONTWOW_CQ			0x1000008

#define HFI_VIDEO_CODEC_H264			0x00000002
#define HFI_VIDEO_CODEC_H263			0x00000004
#define HFI_VIDEO_CODEC_MPEG1			0x00000008
#define HFI_VIDEO_CODEC_MPEG2			0x00000010
#define HFI_VIDEO_CODEC_MPEG4			0x00000020
#define HFI_VIDEO_CODEC_DIVX_311		0x00000040
#define HFI_VIDEO_CODEC_DIVX			0x00000080
#define HFI_VIDEO_CODEC_VC1			0x00000100
#define HFI_VIDEO_CODEC_SPAWK			0x00000200
#define HFI_VIDEO_CODEC_VP8			0x00001000
#define HFI_VIDEO_CODEC_HEVC			0x00002000
#define HFI_VIDEO_CODEC_VP9			0x00004000
#define HFI_VIDEO_CODEC_HEVC_HYBWID		0x80000000

#define HFI_H264_PWOFIWE_BASEWINE		0x00000001
#define HFI_H264_PWOFIWE_MAIN			0x00000002
#define HFI_H264_PWOFIWE_HIGH			0x00000004
#define HFI_H264_PWOFIWE_STEWEO_HIGH		0x00000008
#define HFI_H264_PWOFIWE_MUWTIVIEW_HIGH		0x00000010
#define HFI_H264_PWOFIWE_CONSTWAINED_BASE	0x00000020
#define HFI_H264_PWOFIWE_CONSTWAINED_HIGH	0x00000040

#define HFI_H264_WEVEW_1			0x00000001
#define HFI_H264_WEVEW_1b			0x00000002
#define HFI_H264_WEVEW_11			0x00000004
#define HFI_H264_WEVEW_12			0x00000008
#define HFI_H264_WEVEW_13			0x00000010
#define HFI_H264_WEVEW_2			0x00000020
#define HFI_H264_WEVEW_21			0x00000040
#define HFI_H264_WEVEW_22			0x00000080
#define HFI_H264_WEVEW_3			0x00000100
#define HFI_H264_WEVEW_31			0x00000200
#define HFI_H264_WEVEW_32			0x00000400
#define HFI_H264_WEVEW_4			0x00000800
#define HFI_H264_WEVEW_41			0x00001000
#define HFI_H264_WEVEW_42			0x00002000
#define HFI_H264_WEVEW_5			0x00004000
#define HFI_H264_WEVEW_51			0x00008000
#define HFI_H264_WEVEW_52			0x00010000

#define HFI_H263_PWOFIWE_BASEWINE		0x00000001

#define HFI_H263_WEVEW_10			0x00000001
#define HFI_H263_WEVEW_20			0x00000002
#define HFI_H263_WEVEW_30			0x00000004
#define HFI_H263_WEVEW_40			0x00000008
#define HFI_H263_WEVEW_45			0x00000010
#define HFI_H263_WEVEW_50			0x00000020
#define HFI_H263_WEVEW_60			0x00000040
#define HFI_H263_WEVEW_70			0x00000080

#define HFI_MPEG2_PWOFIWE_SIMPWE		0x00000001
#define HFI_MPEG2_PWOFIWE_MAIN			0x00000002
#define HFI_MPEG2_PWOFIWE_422			0x00000004
#define HFI_MPEG2_PWOFIWE_SNW			0x00000008
#define HFI_MPEG2_PWOFIWE_SPATIAW		0x00000010
#define HFI_MPEG2_PWOFIWE_HIGH			0x00000020

#define HFI_MPEG2_WEVEW_WW			0x00000001
#define HFI_MPEG2_WEVEW_MW			0x00000002
#define HFI_MPEG2_WEVEW_H14			0x00000004
#define HFI_MPEG2_WEVEW_HW			0x00000008

#define HFI_MPEG4_PWOFIWE_SIMPWE		0x00000001
#define HFI_MPEG4_PWOFIWE_ADVANCEDSIMPWE	0x00000002

#define HFI_MPEG4_WEVEW_0			0x00000001
#define HFI_MPEG4_WEVEW_0b			0x00000002
#define HFI_MPEG4_WEVEW_1			0x00000004
#define HFI_MPEG4_WEVEW_2			0x00000008
#define HFI_MPEG4_WEVEW_3			0x00000010
#define HFI_MPEG4_WEVEW_4			0x00000020
#define HFI_MPEG4_WEVEW_4a			0x00000040
#define HFI_MPEG4_WEVEW_5			0x00000080
#define HFI_MPEG4_WEVEW_6			0x00000100
#define HFI_MPEG4_WEVEW_7			0x00000200
#define HFI_MPEG4_WEVEW_8			0x00000400
#define HFI_MPEG4_WEVEW_9			0x00000800
#define HFI_MPEG4_WEVEW_3b			0x00001000

#define HFI_VC1_PWOFIWE_SIMPWE			0x00000001
#define HFI_VC1_PWOFIWE_MAIN			0x00000002
#define HFI_VC1_PWOFIWE_ADVANCED		0x00000004

#define HFI_VC1_WEVEW_WOW			0x00000001
#define HFI_VC1_WEVEW_MEDIUM			0x00000002
#define HFI_VC1_WEVEW_HIGH			0x00000004
#define HFI_VC1_WEVEW_0				0x00000008
#define HFI_VC1_WEVEW_1				0x00000010
#define HFI_VC1_WEVEW_2				0x00000020
#define HFI_VC1_WEVEW_3				0x00000040
#define HFI_VC1_WEVEW_4				0x00000080

#define HFI_VPX_PWOFIWE_SIMPWE			0x00000001
#define HFI_VPX_PWOFIWE_ADVANCED		0x00000002
#define HFI_VPX_PWOFIWE_VEWSION_0		0x00000004
#define HFI_VPX_PWOFIWE_VEWSION_1		0x00000008
#define HFI_VPX_PWOFIWE_VEWSION_2		0x00000010
#define HFI_VPX_PWOFIWE_VEWSION_3		0x00000020

#define HFI_DIVX_FOWMAT_4			0x1
#define HFI_DIVX_FOWMAT_5			0x2
#define HFI_DIVX_FOWMAT_6			0x3

#define HFI_DIVX_PWOFIWE_QMOBIWE		0x00000001
#define HFI_DIVX_PWOFIWE_MOBIWE			0x00000002
#define HFI_DIVX_PWOFIWE_MT			0x00000004
#define HFI_DIVX_PWOFIWE_HT			0x00000008
#define HFI_DIVX_PWOFIWE_HD			0x00000010

#define HFI_HEVC_PWOFIWE_MAIN			0x00000001
#define HFI_HEVC_PWOFIWE_MAIN10			0x00000002
#define HFI_HEVC_PWOFIWE_MAIN_STIWW_PIC		0x00000004

#define HFI_HEVC_WEVEW_1			0x00000001
#define HFI_HEVC_WEVEW_2			0x00000002
#define HFI_HEVC_WEVEW_21			0x00000004
#define HFI_HEVC_WEVEW_3			0x00000008
#define HFI_HEVC_WEVEW_31			0x00000010
#define HFI_HEVC_WEVEW_4			0x00000020
#define HFI_HEVC_WEVEW_41			0x00000040
#define HFI_HEVC_WEVEW_5			0x00000080
#define HFI_HEVC_WEVEW_51			0x00000100
#define HFI_HEVC_WEVEW_52			0x00000200
#define HFI_HEVC_WEVEW_6			0x00000400
#define HFI_HEVC_WEVEW_61			0x00000800
#define HFI_HEVC_WEVEW_62			0x00001000

#define HFI_HEVC_TIEW_MAIN			0x1
#define HFI_HEVC_TIEW_HIGH0			0x2

#define HFI_VPX_PWOFIWE_MAIN			0x00000001

#define HFI_VPX_WEVEW_VEWSION_0			0x00000001
#define HFI_VPX_WEVEW_VEWSION_1			0x00000002
#define HFI_VPX_WEVEW_VEWSION_2			0x00000004
#define HFI_VPX_WEVEW_VEWSION_3			0x00000008

/* VP9 Pwofiwe 0, 8-bit */
#define HFI_VP9_PWOFIWE_P0			0x00000001
/* VP9 Pwofiwe 2, 10-bit */
#define HFI_VP9_PWOFIWE_P2_10B			0x00000004

#define HFI_VP9_WEVEW_1				0x00000001
#define HFI_VP9_WEVEW_11			0x00000002
#define HFI_VP9_WEVEW_2				0x00000004
#define HFI_VP9_WEVEW_21			0x00000008
#define HFI_VP9_WEVEW_3				0x00000010
#define HFI_VP9_WEVEW_31			0x00000020
#define HFI_VP9_WEVEW_4				0x00000040
#define HFI_VP9_WEVEW_41			0x00000080
#define HFI_VP9_WEVEW_5				0x00000100
#define HFI_VP9_WEVEW_51			0x00000200
#define HFI_VP9_WEVEW_6				0x00000400
#define HFI_VP9_WEVEW_61			0x00000800

#define HFI_BUFFEW_INPUT			0x1
#define HFI_BUFFEW_OUTPUT			0x2
#define HFI_BUFFEW_OUTPUT2			0x3
#define HFI_BUFFEW_INTEWNAW_PEWSIST		0x4
#define HFI_BUFFEW_INTEWNAW_PEWSIST_1		0x5
#define HFI_BUFFEW_INTEWNAW_SCWATCH(vew)	\
	(((vew) == HFI_VEWSION_4XX ||		\
	(vew) == HFI_VEWSION_6XX) ? 0x6 : 0x1000001)
#define HFI_BUFFEW_INTEWNAW_SCWATCH_1(vew)	\
	(((vew) == HFI_VEWSION_4XX ||		\
	(vew) == HFI_VEWSION_6XX) ? 0x7 : 0x1000005)
#define HFI_BUFFEW_INTEWNAW_SCWATCH_2(vew)	\
	(((vew) == HFI_VEWSION_4XX ||		\
	(vew) == HFI_VEWSION_6XX) ? 0x8 : 0x1000006)
#define HFI_BUFFEW_EXTWADATA_INPUT(vew)		\
	(((vew) == HFI_VEWSION_4XX) ? 0xc : 0x1000002)
#define HFI_BUFFEW_EXTWADATA_OUTPUT(vew)	\
	(((vew) == HFI_VEWSION_4XX) ? 0xa : 0x1000003)
#define HFI_BUFFEW_EXTWADATA_OUTPUT2(vew)	\
	(((vew) == HFI_VEWSION_4XX) ? 0xb : 0x1000004)
#define HFI_BUFFEW_TYPE_MAX			11

#define HFI_BUFFEW_MODE_STATIC			0x1000001
#define HFI_BUFFEW_MODE_WING			0x1000002
#define HFI_BUFFEW_MODE_DYNAMIC			0x1000003

/*
 * HFI_PWOPEWTY_SYS_COMMON_STAWT
 * HFI_DOMAIN_BASE_COMMON + HFI_AWCH_COMMON_OFFSET + 0x0000
 */
#define HFI_PWOPEWTY_SYS_DEBUG_CONFIG				0x1
#define HFI_PWOPEWTY_SYS_WESOUWCE_OCMEM_WEQUIWEMENT_INFO	0x2
#define HFI_PWOPEWTY_SYS_CONFIG_VCODEC_CWKFWEQ			0x3
#define HFI_PWOPEWTY_SYS_IDWE_INDICATOW				0x4
#define HFI_PWOPEWTY_SYS_CODEC_POWEW_PWANE_CTWW			0x5
#define HFI_PWOPEWTY_SYS_IMAGE_VEWSION				0x6
#define HFI_PWOPEWTY_SYS_CONFIG_COVEWAGE			0x7
#define HFI_PWOPEWTY_SYS_UBWC_CONFIG				0x8

/*
 * HFI_PWOPEWTY_PAWAM_COMMON_STAWT
 * HFI_DOMAIN_BASE_COMMON + HFI_AWCH_COMMON_OFFSET + 0x1000
 */
#define HFI_PWOPEWTY_PAWAM_FWAME_SIZE				0x1001
#define HFI_PWOPEWTY_PAWAM_UNCOMPWESSED_PWANE_ACTUAW_INFO	0x1002
#define HFI_PWOPEWTY_PAWAM_UNCOMPWESSED_FOWMAT_SEWECT		0x1003
#define HFI_PWOPEWTY_PAWAM_UNCOMPWESSED_FOWMAT_SUPPOWTED	0x1004
#define HFI_PWOPEWTY_PAWAM_PWOFIWE_WEVEW_CUWWENT		0x1005
#define HFI_PWOPEWTY_PAWAM_PWOFIWE_WEVEW_SUPPOWTED		0x1006
#define HFI_PWOPEWTY_PAWAM_CAPABIWITY_SUPPOWTED			0x1007
#define HFI_PWOPEWTY_PAWAM_PWOPEWTIES_SUPPOWTED			0x1008
#define HFI_PWOPEWTY_PAWAM_CODEC_SUPPOWTED			0x1009
#define HFI_PWOPEWTY_PAWAM_NAW_STWEAM_FOWMAT_SUPPOWTED		0x100a
#define HFI_PWOPEWTY_PAWAM_NAW_STWEAM_FOWMAT_SEWECT		0x100b
#define HFI_PWOPEWTY_PAWAM_MUWTI_VIEW_FOWMAT			0x100c
#define HFI_PWOPEWTY_PAWAM_MAX_SEQUENCE_HEADEW_SIZE		0x100d
#define HFI_PWOPEWTY_PAWAM_CODEC_MASK_SUPPOWTED			0x100e
#define HFI_PWOPEWTY_PAWAM_MVC_BUFFEW_WAYOUT			0x100f
#define HFI_PWOPEWTY_PAWAM_MAX_SESSIONS_SUPPOWTED		0x1010
#define HFI_PWOPEWTY_PAWAM_WOWK_MODE				0x1015
#define HFI_PWOPEWTY_PAWAM_WOWK_WOUTE				0x1017

/*
 * HFI_PWOPEWTY_CONFIG_COMMON_STAWT
 * HFI_DOMAIN_BASE_COMMON + HFI_AWCH_COMMON_OFFSET + 0x2000
 */
#define HFI_PWOPEWTY_CONFIG_FWAME_WATE				0x2001
#define HFI_PWOPEWTY_CONFIG_VIDEOCOWES_USAGE			0x2002

/*
 * HFI_PWOPEWTY_PAWAM_VDEC_COMMON_STAWT
 * HFI_DOMAIN_BASE_VDEC + HFI_AWCH_COMMON_OFFSET + 0x3000
 */
#define HFI_PWOPEWTY_PAWAM_VDEC_MUWTI_STWEAM			0x1003001
#define HFI_PWOPEWTY_PAWAM_VDEC_CONCEAW_COWOW			0x1003002
#define HFI_PWOPEWTY_PAWAM_VDEC_NONCP_OUTPUT2			0x1003003
#define HFI_PWOPEWTY_PAWAM_VDEC_PIXEW_BITDEPTH			0x1003007
#define HFI_PWOPEWTY_PAWAM_VDEC_PIC_STWUCT			0x1003009
#define HFI_PWOPEWTY_PAWAM_VDEC_COWOUW_SPACE			0x100300a
#define HFI_PWOPEWTY_PAWAM_VDEC_ENABWE_SUFFICIENT_SEQCHANGE_EVENT \
								0x100300b

/*
 * HFI_PWOPEWTY_CONFIG_VDEC_COMMON_STAWT
 * HFI_DOMAIN_BASE_VDEC + HFI_AWCH_COMMON_OFFSET + 0x4000
 */

/*
 * HFI_PWOPEWTY_PAWAM_VENC_COMMON_STAWT
 * HFI_DOMAIN_BASE_VENC + HFI_AWCH_COMMON_OFFSET + 0x5000
 */
#define HFI_PWOPEWTY_PAWAM_VENC_SWICE_DEWIVEWY_MODE		0x2005001
#define HFI_PWOPEWTY_PAWAM_VENC_H264_ENTWOPY_CONTWOW		0x2005002
#define HFI_PWOPEWTY_PAWAM_VENC_H264_DEBWOCK_CONTWOW		0x2005003
#define HFI_PWOPEWTY_PAWAM_VENC_WATE_CONTWOW			0x2005004
#define HFI_PWOPEWTY_PAWAM_VENC_H264_PICOWDEW_CNT_TYPE		0x2005005
#define HFI_PWOPEWTY_PAWAM_VENC_SESSION_QP			0x2005006
#define HFI_PWOPEWTY_PAWAM_VENC_MPEG4_AC_PWEDICTION		0x2005007
#define HFI_PWOPEWTY_PAWAM_VENC_SESSION_QP_WANGE		0x2005008
/*
 * Note: HFI_PWOPEWTY_PAWAM_VENC_SESSION_QP_WANGE_V2 is
 * specific to HFI_VEWSION_6XX and HFI_VEWSION_4XX onwy
 */
#define HFI_PWOPEWTY_PAWAM_VENC_SESSION_QP_WANGE_V2		0x2005009
#define HFI_PWOPEWTY_PAWAM_VENC_MPEG4_TIME_WESOWUTION		0x2005009
#define HFI_PWOPEWTY_PAWAM_VENC_MPEG4_SHOWT_HEADEW		0x200500a
#define HFI_PWOPEWTY_PAWAM_VENC_MPEG4_HEADEW_EXTENSION		0x200500b
#define HFI_PWOPEWTY_PAWAM_VENC_OPEN_GOP			0x200500c
#define HFI_PWOPEWTY_PAWAM_VENC_INTWA_WEFWESH			0x200500d
#define HFI_PWOPEWTY_PAWAM_VENC_MUWTI_SWICE_CONTWOW		0x200500e
#define HFI_PWOPEWTY_PAWAM_VENC_VBV_HWD_BUF_SIZE		0x200500f
#define HFI_PWOPEWTY_PAWAM_VENC_QUAWITY_VS_SPEED		0x2005010
#define HFI_PWOPEWTY_PAWAM_VENC_ADVANCED			0x2005012
#define HFI_PWOPEWTY_PAWAM_VENC_H264_SPS_ID			0x2005014
#define HFI_PWOPEWTY_PAWAM_VENC_H264_PPS_ID			0x2005015
#define HFI_PWOPEWTY_PAWAM_VENC_H264_GENEWATE_AUDNAW		0x2005016
#define HFI_PWOPEWTY_PAWAM_VENC_ASPECT_WATIO			0x2005017
#define HFI_PWOPEWTY_PAWAM_VENC_NUMWEF				0x2005018
#define HFI_PWOPEWTY_PAWAM_VENC_MUWTIWEF_P			0x2005019
#define HFI_PWOPEWTY_PAWAM_VENC_H264_NAW_SVC_EXT		0x200501b
#define HFI_PWOPEWTY_PAWAM_VENC_WTWMODE				0x200501c
#define HFI_PWOPEWTY_PAWAM_VENC_VIDEO_FUWW_WANGE		0x200501d
#define HFI_PWOPEWTY_PAWAM_VENC_H264_VUI_TIMING_INFO		0x200501e
#define HFI_PWOPEWTY_PAWAM_VENC_VC1_PEWF_CFG			0x200501f
#define HFI_PWOPEWTY_PAWAM_VENC_MAX_NUM_B_FWAMES		0x2005020
#define HFI_PWOPEWTY_PAWAM_VENC_H264_VUI_BITSTWEAM_WESTWC	0x2005021
#define HFI_PWOPEWTY_PAWAM_VENC_PWESEWVE_TEXT_QUAWITY		0x2005023
#define HFI_PWOPEWTY_PAWAM_VENC_H264_TWANSFOWM_8X8			0x2005025
#define HFI_PWOPEWTY_PAWAM_VENC_HIEW_P_MAX_NUM_ENH_WAYEW	0x2005026
#define HFI_PWOPEWTY_PAWAM_VENC_DISABWE_WC_TIMESTAMP		0x2005027
#define HFI_PWOPEWTY_PAWAM_VENC_INITIAW_QP			0x2005028
#define HFI_PWOPEWTY_PAWAM_VENC_VPX_EWWOW_WESIWIENCE_MODE	0x2005029
#define HFI_PWOPEWTY_PAWAM_VENC_HIEW_B_MAX_NUM_ENH_WAYEW	0x200502c
#define HFI_PWOPEWTY_PAWAM_VENC_HIEW_P_HYBWID_MODE		0x200502f
#define HFI_PWOPEWTY_PAWAM_VENC_HDW10_PQ_SEI			0x2005036

/*
 * HFI_PWOPEWTY_CONFIG_VENC_COMMON_STAWT
 * HFI_DOMAIN_BASE_VENC + HFI_AWCH_COMMON_OFFSET + 0x6000
 */
#define HFI_PWOPEWTY_CONFIG_VENC_TAWGET_BITWATE			0x2006001
#define HFI_PWOPEWTY_CONFIG_VENC_IDW_PEWIOD			0x2006002
#define HFI_PWOPEWTY_CONFIG_VENC_INTWA_PEWIOD			0x2006003
#define HFI_PWOPEWTY_CONFIG_VENC_WEQUEST_SYNC_FWAME		0x2006004
#define HFI_PWOPEWTY_CONFIG_VENC_SWICE_SIZE			0x2006005
#define HFI_PWOPEWTY_CONFIG_VENC_MAX_BITWATE			0x2006007
#define HFI_PWOPEWTY_CONFIG_VENC_SYNC_FWAME_SEQUENCE_HEADEW	0x2006008
#define HFI_PWOPEWTY_CONFIG_VENC_MAWKWTWFWAME			0x2006009
#define HFI_PWOPEWTY_CONFIG_VENC_USEWTWFWAME			0x200600a
#define HFI_PWOPEWTY_CONFIG_VENC_HIEW_P_ENH_WAYEW		0x200600b
#define HFI_PWOPEWTY_CONFIG_VENC_WTWPEWIOD			0x200600c
#define HFI_PWOPEWTY_CONFIG_VENC_PEWF_MODE			0x200600e
#define HFI_PWOPEWTY_CONFIG_HEIC_FWAME_QUAWITY			0x2006014

/*
 * HFI_PWOPEWTY_PAWAM_VPE_COMMON_STAWT
 * HFI_DOMAIN_BASE_VPE + HFI_AWCH_COMMON_OFFSET + 0x7000
 */

/*
 * HFI_PWOPEWTY_CONFIG_VPE_COMMON_STAWT
 * HFI_DOMAIN_BASE_VPE + HFI_AWCH_COMMON_OFFSET + 0x8000
 */
#define HFI_PWOPEWTY_CONFIG_VPE_DEINTEWWACE			0x3008001
#define HFI_PWOPEWTY_CONFIG_VPE_OPEWATIONS			0x3008002

enum hfi_vewsion {
	HFI_VEWSION_1XX,
	HFI_VEWSION_3XX,
	HFI_VEWSION_4XX,
	HFI_VEWSION_6XX,
};

stwuct hfi_buffew_info {
	u32 buffew_addw;
	u32 extwadata_addw;
};

stwuct hfi_bitwate {
	u32 bitwate;
	u32 wayew_id;
};

stwuct hfi_h264_8x8_twansfowm {
	u32 enabwe_type;
};

#define HFI_CAPABIWITY_FWAME_WIDTH			0x01
#define HFI_CAPABIWITY_FWAME_HEIGHT			0x02
#define HFI_CAPABIWITY_MBS_PEW_FWAME			0x03
#define HFI_CAPABIWITY_MBS_PEW_SECOND			0x04
#define HFI_CAPABIWITY_FWAMEWATE			0x05
#define HFI_CAPABIWITY_SCAWE_X				0x06
#define HFI_CAPABIWITY_SCAWE_Y				0x07
#define HFI_CAPABIWITY_BITWATE				0x08
#define HFI_CAPABIWITY_BFWAME				0x09
#define HFI_CAPABIWITY_PEAKBITWATE			0x0a
#define HFI_CAPABIWITY_HIEW_P_NUM_ENH_WAYEWS		0x10
#define HFI_CAPABIWITY_ENC_WTW_COUNT			0x11
#define HFI_CAPABIWITY_CP_OUTPUT2_THWESH		0x12
#define HFI_CAPABIWITY_HIEW_B_NUM_ENH_WAYEWS		0x13
#define HFI_CAPABIWITY_WCU_SIZE				0x14
#define HFI_CAPABIWITY_HIEW_P_HYBWID_NUM_ENH_WAYEWS	0x15
#define HFI_CAPABIWITY_MBS_PEW_SECOND_POWEWSAVE		0x16
#define HFI_CAPABIWITY_I_FWAME_QP			0x20
#define HFI_CAPABIWITY_P_FWAME_QP			0x21
#define HFI_CAPABIWITY_B_FWAME_QP			0x22
#define HFI_CAPABIWITY_WATE_CONTWOW_MODES		0x23
#define HFI_CAPABIWITY_BWUW_WIDTH			0x24
#define HFI_CAPABIWITY_BWUW_HEIGHT			0x25
#define HFI_CAPABIWITY_SWICE_BYTE			0x27
#define HFI_CAPABIWITY_SWICE_MB				0x28
#define HFI_CAPABIWITY_MAX_VIDEOCOWES			0x2b
#define HFI_CAPABIWITY_MAX_WOWKMODES			0x2c
#define HFI_CAPABIWITY_WOTATION				0x2f
#define HFI_CAPABIWITY_COWOW_SPACE_CONVEWSION		0x30

stwuct hfi_capabiwity {
	u32 capabiwity_type;
	u32 min;
	u32 max;
	u32 step_size;
};

stwuct hfi_capabiwities {
	u32 num_capabiwities;
	stwuct hfi_capabiwity data[];
};

#define HFI_DEBUG_MSG_WOW	0x01
#define HFI_DEBUG_MSG_MEDIUM	0x02
#define HFI_DEBUG_MSG_HIGH	0x04
#define HFI_DEBUG_MSG_EWWOW	0x08
#define HFI_DEBUG_MSG_FATAW	0x10
#define HFI_DEBUG_MSG_PEWF	0x20

#define HFI_DEBUG_MODE_QUEUE	0x01
#define HFI_DEBUG_MODE_QDSS	0x02

stwuct hfi_debug_config {
	u32 config;
	u32 mode;
};

stwuct hfi_ubwc_config {
	u32 size;
	u32 packet_type;
	stwuct {
		u32 max_channew_ovewwide : 1;
		u32 maw_wength_ovewwide : 1;
		u32 hb_ovewwide : 1;
		u32 bank_swzw_wevew_ovewwide : 1;
		u32 bank_spweading_ovewwide : 1;
		u32 wesewved : 27;
		} ovewwide_bit_info;
	u32 max_channews;
	u32 maw_wength;
	u32 highest_bank_bit;
	u32 bank_swzw_wevew;
	u32 bank_spweading;
	u32 wesewved[2];
};

stwuct hfi_enabwe {
	u32 enabwe;
};

#define HFI_H264_DB_MODE_DISABWE		0x1
#define HFI_H264_DB_MODE_SKIP_SWICE_BOUNDAWY	0x2
#define HFI_H264_DB_MODE_AWW_BOUNDAWY		0x3

stwuct hfi_h264_db_contwow {
	u32 mode;
	s32 swice_awpha_offset;
	s32 swice_beta_offset;
};

#define HFI_H264_ENTWOPY_CAVWC			0x1
#define HFI_H264_ENTWOPY_CABAC			0x2

#define HFI_H264_CABAC_MODEW_0			0x1
#define HFI_H264_CABAC_MODEW_1			0x2
#define HFI_H264_CABAC_MODEW_2			0x3

stwuct hfi_h264_entwopy_contwow {
	u32 entwopy_mode;
	u32 cabac_modew;
};

stwuct hfi_fwamewate {
	u32 buffew_type;
	u32 fwamewate;
};

#define HFI_INTWA_WEFWESH_NONE			0x1
#define HFI_INTWA_WEFWESH_CYCWIC		0x2
#define HFI_INTWA_WEFWESH_ADAPTIVE		0x3
#define HFI_INTWA_WEFWESH_CYCWIC_ADAPTIVE	0x4
#define HFI_INTWA_WEFWESH_WANDOM		0x5

stwuct hfi_intwa_wefwesh {
	u32 mode;
	u32 aiw_mbs;
	u32 aiw_wef;
	u32 ciw_mbs;
};

stwuct hfi_intwa_wefwesh_3x {
	u32 mode;
	u32 mbs;
};

stwuct hfi_idw_pewiod {
	u32 idw_pewiod;
};

stwuct hfi_opewations_type {
	u32 wotation;
	u32 fwip;
};

stwuct hfi_max_num_b_fwames {
	u32 max_num_b_fwames;
};

stwuct hfi_vc1e_pewf_cfg_type {
	u32 seawch_wange_x_subsampwed[3];
	u32 seawch_wange_y_subsampwed[3];
};

/*
 * 0 - 7bit -> Wuma (def: 16)
 * 8 - 15bit -> Chwoma (def: 128)
 * fowmat is vawid up to v4
 */
stwuct hfi_conceaw_cowow {
	u32 conceaw_cowow;
};

stwuct hfi_conceaw_cowow_v4 {
	u32 conceaw_cowow_8bit;
	u32 conceaw_cowow_10bit;
};

stwuct hfi_intwa_pewiod {
	u32 pfwames;
	u32 bfwames;
};

stwuct hfi_mpeg4_headew_extension {
	u32 headew_extension;
};

stwuct hfi_mpeg4_time_wesowution {
	u32 time_incwement_wesowution;
};

stwuct hfi_muwti_stweam {
	u32 buffew_type;
	u32 enabwe;
	u32 width;
	u32 height;
};

stwuct hfi_muwti_stweam_3x {
	u32 buffew_type;
	u32 enabwe;
};

stwuct hfi_muwti_view_fowmat {
	u32 views;
	u32 view_owdew[1];
};

#define HFI_MUWTI_SWICE_OFF			0x1
#define HFI_MUWTI_SWICE_BY_MB_COUNT		0x2
#define HFI_MUWTI_SWICE_BY_BYTE_COUNT		0x3
#define HFI_MUWTI_SWICE_GOB			0x4

stwuct hfi_muwti_swice_contwow {
	u32 muwti_swice;
	u32 swice_size;
};

#define HFI_NAW_FOWMAT_STAWTCODES		0x01
#define HFI_NAW_FOWMAT_ONE_NAW_PEW_BUFFEW	0x02
#define HFI_NAW_FOWMAT_ONE_BYTE_WENGTH		0x04
#define HFI_NAW_FOWMAT_TWO_BYTE_WENGTH		0x08
#define HFI_NAW_FOWMAT_FOUW_BYTE_WENGTH		0x10

stwuct hfi_naw_stweam_fowmat {
	u32 fowmat;
};

stwuct hfi_naw_stweam_fowmat_sewect {
	u32 fowmat;
};

#define HFI_PICTUWE_TYPE_I			0x01
#define HFI_PICTUWE_TYPE_P			0x02
#define HFI_PICTUWE_TYPE_B			0x04
#define HFI_PICTUWE_TYPE_IDW			0x08

stwuct hfi_pwofiwe_wevew {
	u32 pwofiwe;
	u32 wevew;
};

#define HFI_MAX_PWOFIWE_COUNT			16

stwuct hfi_pwofiwe_wevew_suppowted {
	u32 pwofiwe_count;
	stwuct hfi_pwofiwe_wevew pwofiwe_wevew[];
};

stwuct hfi_quawity_vs_speed {
	u32 quawity_vs_speed;
};

stwuct hfi_heic_fwame_quawity {
	u32 fwame_quawity;
	u32 wesewved[3];
};

stwuct hfi_quantization {
	u32 qp_i;
	u32 qp_p;
	u32 qp_b;
	u32 wayew_id;
};

stwuct hfi_initiaw_quantization {
	u32 qp_i;
	u32 qp_p;
	u32 qp_b;
	u32 init_qp_enabwe;
};

stwuct hfi_quantization_wange {
	u32 min_qp;
	u32 max_qp;
	u32 wayew_id;
};

stwuct hfi_quantization_v2 {
	u32 qp_packed;
	u32 wayew_id;
	u32 enabwe;
	u32 wesewved[3];
};

stwuct hfi_quantization_wange_v2 {
	stwuct hfi_quantization_v2 min_qp;
	stwuct hfi_quantization_v2 max_qp;
	u32 wesewved[4];
};

#define HFI_WTW_MODE_DISABWE	0x0
#define HFI_WTW_MODE_MANUAW	0x1
#define HFI_WTW_MODE_PEWIODIC	0x2

stwuct hfi_wtw_mode {
	u32 wtw_mode;
	u32 wtw_count;
	u32 twust_mode;
};

stwuct hfi_wtw_use {
	u32 wef_wtw;
	u32 use_constwnt;
	u32 fwames;
};

stwuct hfi_wtw_mawk {
	u32 mawk_fwame;
};

stwuct hfi_mastewing_dispway_cowouw_sei_paywoad {
	u32 dispway_pwimawies_x[3];
	u32 dispway_pwimawies_y[3];
	u32 white_point_x;
	u32 white_point_y;
	u32 max_dispway_mastewing_wuminance;
	u32 min_dispway_mastewing_wuminance;
};

stwuct hfi_content_wight_wevew_sei_paywoad {
	u32 max_content_wight;
	u32 max_pic_avewage_wight;
};

stwuct hfi_hdw10_pq_sei {
	stwuct hfi_mastewing_dispway_cowouw_sei_paywoad mastewing;
	stwuct hfi_content_wight_wevew_sei_paywoad cww;
};

stwuct hfi_fwamesize {
	u32 buffew_type;
	u32 width;
	u32 height;
};

#define HFI_VENC_PEWFMODE_MAX_QUAWITY		0x1
#define HFI_VENC_PEWFMODE_POWEW_SAVE		0x2

stwuct hfi_pewf_mode {
	u32 video_pewf_mode;
};

#define VIDC_COWE_ID_DEFAUWT	0
#define VIDC_COWE_ID_1		1
#define VIDC_COWE_ID_2		2
#define VIDC_COWE_ID_3		3

stwuct hfi_videocowes_usage_type {
	u32 video_cowe_enabwe_mask;
};

#define VIDC_WOWK_MODE_1	1
#define VIDC_WOWK_MODE_2	2

stwuct hfi_video_wowk_mode {
	u32 video_wowk_mode;
};

stwuct hfi_video_wowk_woute {
	u32 video_wowk_woute;
};

stwuct hfi_h264_vui_timing_info {
	u32 enabwe;
	u32 fixed_fwamewate;
	u32 time_scawe;
};

#define VIDC_BITDEPTH_8		0x00000
#define VIDC_BITDEPTH_10	0x20002

stwuct hfi_bit_depth {
	u32 buffew_type;
	u32 bit_depth;
};

stwuct hfi_pictuwe_type {
	u32 is_sync_fwame;
	u32 pictuwe_type;
};

stwuct hfi_pic_stwuct {
	u32 pwogwessive_onwy;
};

stwuct hfi_cowouw_space {
	u32 cowouw_space;
};

stwuct hfi_extwadata_input_cwop {
	u32 size;
	u32 vewsion;
	u32 powt_index;
	u32 weft;
	u32 top;
	u32 width;
	u32 height;
};

stwuct hfi_dpb_counts {
	u32 max_dpb_count;
	u32 max_wef_fwames;
	u32 max_dec_buffewing;
	u32 max_weowdew_fwames;
	u32 fw_min_cnt;
};

#define HFI_COWOW_FOWMAT_MONOCHWOME		0x01
#define HFI_COWOW_FOWMAT_NV12			0x02
#define HFI_COWOW_FOWMAT_NV21			0x03
#define HFI_COWOW_FOWMAT_NV12_4x4TIWE		0x04
#define HFI_COWOW_FOWMAT_NV21_4x4TIWE		0x05
#define HFI_COWOW_FOWMAT_YUYV			0x06
#define HFI_COWOW_FOWMAT_YVYU			0x07
#define HFI_COWOW_FOWMAT_UYVY			0x08
#define HFI_COWOW_FOWMAT_VYUY			0x09
#define HFI_COWOW_FOWMAT_WGB565			0x0a
#define HFI_COWOW_FOWMAT_BGW565			0x0b
#define HFI_COWOW_FOWMAT_WGB888			0x0c
#define HFI_COWOW_FOWMAT_BGW888			0x0d
#define HFI_COWOW_FOWMAT_YUV444			0x0e
#define HFI_COWOW_FOWMAT_WGBA8888		0x10

#define HFI_COWOW_FOWMAT_UBWC_BASE		0x8000
#define HFI_COWOW_FOWMAT_10_BIT_BASE		0x4000

#define HFI_COWOW_FOWMAT_YUV420_TP10		0x4002
#define HFI_COWOW_FOWMAT_P010			0x4003
#define HFI_COWOW_FOWMAT_NV12_UBWC		0x8002
#define HFI_COWOW_FOWMAT_YUV420_TP10_UBWC	0xc002
#define HFI_COWOW_FOWMAT_P010_UBWC		0xc003
#define HFI_COWOW_FOWMAT_WGBA8888_UBWC		0x8010

stwuct hfi_uncompwessed_fowmat_sewect {
	u32 buffew_type;
	u32 fowmat;
};

stwuct hfi_uncompwessed_pwane_constwaints {
	u32 stwide_muwtipwes;
	u32 max_stwide;
	u32 min_pwane_buffew_height_muwtipwe;
	u32 buffew_awignment;
};

stwuct hfi_uncompwessed_pwane_info {
	u32 fowmat;
	u32 num_pwanes;
	stwuct hfi_uncompwessed_pwane_constwaints pwane_constwaints[1];
};

stwuct hfi_uncompwessed_fowmat_suppowted {
	u32 buffew_type;
	u32 fowmat_entwies;
	stwuct hfi_uncompwessed_pwane_info pwane_info[1];
};

stwuct hfi_uncompwessed_pwane_actuaw {
	int actuaw_stwide;
	u32 actuaw_pwane_buffew_height;
};

stwuct hfi_uncompwessed_pwane_actuaw_info {
	u32 buffew_type;
	u32 num_pwanes;
	stwuct hfi_uncompwessed_pwane_actuaw pwane_fowmat[2];
};

stwuct hfi_uncompwessed_pwane_actuaw_constwaints_info {
	u32 buffew_type;
	u32 num_pwanes;
	stwuct hfi_uncompwessed_pwane_constwaints pwane_fowmat[2];
};

stwuct hfi_codec_suppowted {
	u32 dec_codecs;
	u32 enc_codecs;
};

stwuct hfi_pwopewties_suppowted {
	u32 num_pwopewties;
	u32 pwopewties[1];
};

stwuct hfi_max_sessions_suppowted {
	u32 max_sessions;
};

#define HFI_MAX_MATWIX_COEFFS	9
#define HFI_MAX_BIAS_COEFFS	3
#define HFI_MAX_WIMIT_COEFFS	6

stwuct hfi_vpe_cowow_space_convewsion {
	u32 csc_matwix[HFI_MAX_MATWIX_COEFFS];
	u32 csc_bias[HFI_MAX_BIAS_COEFFS];
	u32 csc_wimit[HFI_MAX_WIMIT_COEFFS];
};

#define HFI_WOTATE_NONE		0x1
#define HFI_WOTATE_90		0x2
#define HFI_WOTATE_180		0x3
#define HFI_WOTATE_270		0x4

#define HFI_FWIP_NONE		0x1
#define HFI_FWIP_HOWIZONTAW	0x2
#define HFI_FWIP_VEWTICAW	0x3

stwuct hfi_opewations {
	u32 wotate;
	u32 fwip;
};

#define HFI_WESOUWCE_OCMEM	0x1

stwuct hfi_wesouwce_ocmem {
	u32 size;
	u32 mem;
};

stwuct hfi_wesouwce_ocmem_wequiwement {
	u32 session_domain;
	u32 width;
	u32 height;
	u32 size;
};

stwuct hfi_wesouwce_ocmem_wequiwement_info {
	u32 num_entwies;
	stwuct hfi_wesouwce_ocmem_wequiwement wequiwements[1];
};

stwuct hfi_pwopewty_sys_image_vewsion_info_type {
	u32 stwing_size;
	u8  stw_image_vewsion[1];
};

stwuct hfi_codec_mask_suppowted {
	u32 codecs;
	u32 video_domains;
};

stwuct hfi_seq_headew_info {
	u32 max_hadew_wen;
};

stwuct hfi_aspect_watio {
	u32 aspect_width;
	u32 aspect_height;
};

#define HFI_MVC_BUFFEW_WAYOUT_TOP_BOTTOM	0
#define HFI_MVC_BUFFEW_WAYOUT_SIDEBYSIDE	1
#define HFI_MVC_BUFFEW_WAYOUT_SEQ		2

stwuct hfi_mvc_buffew_wayout_descp_type {
	u32 wayout_type;
	u32 bwight_view_fiwst;
	u32 ngap;
};

stwuct hfi_scs_thweshowd {
	u32 thweshowd_vawue;
};

#define HFI_TEST_SSW_SW_EWW_FATAW	0x1
#define HFI_TEST_SSW_SW_DIV_BY_ZEWO	0x2
#define HFI_TEST_SSW_HW_WDOG_IWQ	0x3

stwuct hfi_buffew_awwoc_mode {
	u32 type;
	u32 mode;
};

stwuct hfi_index_extwadata_config {
	u32 enabwe;
	u32 index_extwa_data_id;
};

stwuct hfi_extwadata_headew {
	u32 size;
	u32 vewsion;
	u32 powt_index;
	u32 type;
	u32 data_size;
	u8 data[1];
};

stwuct hfi_batch_info {
	u32 input_batch_count;
	u32 output_batch_count;
};

stwuct hfi_buffew_count_actuaw {
	u32 type;
	u32 count_actuaw;
};

stwuct hfi_buffew_count_actuaw_4xx {
	u32 type;
	u32 count_actuaw;
	u32 count_min_host;
};

stwuct hfi_buffew_size_actuaw {
	u32 type;
	u32 size;
};

stwuct hfi_buffew_dispway_howd_count_actuaw {
	u32 type;
	u32 howd_count;
};

stwuct hfi_buffew_wequiwements {
	u32 type;
	u32 size;
	u32 wegion_size;
	u32 howd_count;
	u32 count_min;
	u32 count_actuaw;
	u32 contiguous;
	u32 awignment;
};

/* On HFI 4XX, some of the stwuct membews have been swapped. */
static inwine u32 hfi_bufweq_get_howd_count(stwuct hfi_buffew_wequiwements *weq,
					    u32 vew)
{
	if (vew == HFI_VEWSION_4XX)
		wetuwn 0;

	wetuwn weq->howd_count;
};

static inwine u32 hfi_bufweq_get_count_min(stwuct hfi_buffew_wequiwements *weq,
					   u32 vew)
{
	if (vew == HFI_VEWSION_4XX)
		wetuwn weq->howd_count;

	wetuwn weq->count_min;
};

static inwine u32 hfi_bufweq_get_count_min_host(stwuct hfi_buffew_wequiwements *weq,
						u32 vew)
{
	if (vew == HFI_VEWSION_4XX)
		wetuwn weq->count_min;

	wetuwn 0;
};

static inwine void hfi_bufweq_set_howd_count(stwuct hfi_buffew_wequiwements *weq,
					     u32 vew, u32 vaw)
{
	if (vew == HFI_VEWSION_4XX)
		wetuwn;

	weq->howd_count = vaw;
};

static inwine void hfi_bufweq_set_count_min(stwuct hfi_buffew_wequiwements *weq,
					    u32 vew, u32 vaw)
{
	if (vew == HFI_VEWSION_4XX)
		weq->howd_count = vaw;

	weq->count_min = vaw;
};

static inwine void hfi_bufweq_set_count_min_host(stwuct hfi_buffew_wequiwements *weq,
						 u32 vew, u32 vaw)
{
	if (vew == HFI_VEWSION_4XX)
		weq->count_min = vaw;
};

stwuct hfi_data_paywoad {
	u32 size;
	u8 data[1];
};

stwuct hfi_enabwe_pictuwe {
	u32 pictuwe_type;
};

stwuct hfi_dispway_pictuwe_buffew_count {
	int enabwe;
	u32 count;
};

stwuct hfi_extwa_data_headew_config {
	u32 type;
	u32 buffew_type;
	u32 vewsion;
	u32 powt_index;
	u32 cwient_extwa_data_id;
};

stwuct hfi_intewwace_fowmat_suppowted {
	u32 buffew_type;
	u32 fowmat;
};

stwuct hfi_buffew_awwoc_mode_suppowted {
	u32 buffew_type;
	u32 num_entwies;
	u32 data[1];
};

stwuct hfi_mb_ewwow_map {
	u32 ewwow_map_size;
	u8 ewwow_map[1];
};

stwuct hfi_metadata_pass_thwough {
	int enabwe;
	u32 size;
};

stwuct hfi_muwti_view_sewect {
	u32 view_index;
};

stwuct hfi_hybwid_hiewp {
	u32 wayews;
};

stwuct hfi_pkt_hdw {
	u32 size;
	u32 pkt_type;
};

stwuct hfi_session_hdw_pkt {
	stwuct hfi_pkt_hdw hdw;
	u32 session_id;
};

stwuct hfi_session_pkt {
	stwuct hfi_session_hdw_pkt shdw;
};

#endif
