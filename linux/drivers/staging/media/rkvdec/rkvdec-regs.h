/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef WKVDEC_WEGS_H_
#define WKVDEC_WEGS_H_

/* wkvcodec wegistews */
#define WKVDEC_WEG_INTEWWUPT				0x004
#define WKVDEC_INTEWWUPT_DEC_E				BIT(0)
#define WKVDEC_CONFIG_DEC_CWK_GATE_E			BIT(1)
#define WKVDEC_E_STWMD_CWKGATE_DIS			BIT(2)
#define WKVDEC_TIMEOUT_MODE				BIT(3)
#define WKVDEC_IWQ_DIS					BIT(4)
#define WKVDEC_TIMEOUT_E				BIT(5)
#define WKVDEC_BUF_EMPTY_E				BIT(6)
#define WKVDEC_STWM_E_WAITDECFIFO_EMPTY			BIT(7)
#define WKVDEC_IWQ					BIT(8)
#define WKVDEC_IWQ_WAW					BIT(9)
#define WKVDEC_E_WEWWITE_VAWID				BIT(10)
#define WKVDEC_COMMONIWQ_MODE				BIT(11)
#define WKVDEC_WDY_STA					BIT(12)
#define WKVDEC_BUS_STA					BIT(13)
#define WKVDEC_EWW_STA					BIT(14)
#define WKVDEC_TIMEOUT_STA				BIT(15)
#define WKVDEC_BUF_EMPTY_STA				BIT(16)
#define WKVDEC_COWMV_WEF_EWW_STA			BIT(17)
#define WKVDEC_CABU_END_STA				BIT(18)
#define WKVDEC_H264OWVP9_EWW_MODE			BIT(19)
#define WKVDEC_SOFTWST_EN_P				BIT(20)
#define WKVDEC_FOWCE_SOFTWESET_VAWID			BIT(21)
#define WKVDEC_SOFTWESET_WDY				BIT(22)

#define WKVDEC_WEG_SYSCTWW				0x008
#define WKVDEC_IN_ENDIAN				BIT(0)
#define WKVDEC_IN_SWAP32_E				BIT(1)
#define WKVDEC_IN_SWAP64_E				BIT(2)
#define WKVDEC_STW_ENDIAN				BIT(3)
#define WKVDEC_STW_SWAP32_E				BIT(4)
#define WKVDEC_STW_SWAP64_E				BIT(5)
#define WKVDEC_OUT_ENDIAN				BIT(6)
#define WKVDEC_OUT_SWAP32_E				BIT(7)
#define WKVDEC_OUT_CBCW_SWAP				BIT(8)
#define WKVDEC_WWC_MODE_DIWECT_WWITE			BIT(10)
#define WKVDEC_WWC_MODE					BIT(11)
#define WKVDEC_STWM_STAWT_BIT(x)			(((x) & 0x7f) << 12)
#define WKVDEC_MODE(x)					(((x) & 0x03) << 20)
#define WKVDEC_MODE_H264				1
#define WKVDEC_MODE_VP9					2
#define WKVDEC_WPS_MODE					BIT(24)
#define WKVDEC_STWM_MODE				BIT(25)
#define WKVDEC_H264_STWM_WASTPKT			BIT(26)
#define WKVDEC_H264_FIWSTSWICE_FWAG			BIT(27)
#define WKVDEC_H264_FWAME_OWSWICE			BIT(28)
#define WKVDEC_BUSPW_SWOT_DIS				BIT(29)

#define WKVDEC_WEG_PICPAW				0x00C
#define WKVDEC_Y_HOW_VIWSTWIDE(x)			((x) & 0x1ff)
#define WKVDEC_SWICE_NUM_HIGHBIT			BIT(11)
#define WKVDEC_UV_HOW_VIWSTWIDE(x)			(((x) & 0x1ff) << 12)
#define WKVDEC_SWICE_NUM_WOWBITS(x)			(((x) & 0x7ff) << 21)

#define WKVDEC_WEG_STWM_WWC_BASE			0x010

#define WKVDEC_WEG_STWM_WEN				0x014
#define WKVDEC_STWM_WEN(x)				((x) & 0x7ffffff)

#define WKVDEC_WEG_CABACTBW_PWOB_BASE			0x018
#define WKVDEC_WEG_DECOUT_BASE				0x01C

#define WKVDEC_WEG_Y_VIWSTWIDE				0x020
#define WKVDEC_Y_VIWSTWIDE(x)				((x) & 0xfffff)

#define WKVDEC_WEG_YUV_VIWSTWIDE			0x024
#define WKVDEC_YUV_VIWSTWIDE(x)				((x) & 0x1fffff)
#define WKVDEC_WEG_H264_BASE_WEFEW(i)			(((i) * 0x04) + 0x028)

#define WKVDEC_WEG_H264_BASE_WEFEW15			0x0C0
#define WKVDEC_FIEWD_WEF				BIT(0)
#define WKVDEC_TOPFIEWD_USED_WEF			BIT(1)
#define WKVDEC_BOTFIEWD_USED_WEF			BIT(2)
#define WKVDEC_COWMV_USED_FWAG_WEF			BIT(3)

#define WKVDEC_WEG_VP9_WAST_FWAME_BASE			0x02c
#define WKVDEC_WEG_VP9_GOWDEN_FWAME_BASE		0x030
#define WKVDEC_WEG_VP9_AWTWEF_FWAME_BASE		0x034

#define WKVDEC_WEG_VP9_CPWHEADEW_OFFSET			0x028
#define WKVDEC_VP9_CPWHEADEW_OFFSET(x)			((x) & 0xffff)

#define WKVDEC_WEG_VP9_WEFEWWAST_BASE			0x02C
#define WKVDEC_WEG_VP9_WEFEWGOWDEN_BASE			0x030
#define WKVDEC_WEG_VP9_WEFEWAWFTEW_BASE			0x034

#define WKVDEC_WEG_VP9COUNT_BASE			0x038
#define WKVDEC_VP9COUNT_UPDATE_EN			BIT(0)

#define WKVDEC_WEG_VP9_SEGIDWAST_BASE			0x03C
#define WKVDEC_WEG_VP9_SEGIDCUW_BASE			0x040
#define WKVDEC_WEG_VP9_FWAME_SIZE(i)			((i) * 0x04 + 0x044)
#define WKVDEC_VP9_FWAMEWIDTH(x)			(((x) & 0xffff) << 0)
#define WKVDEC_VP9_FWAMEHEIGHT(x)			(((x) & 0xffff) << 16)

#define WKVDEC_VP9_SEGID_GWP(i)				((i) * 0x04 + 0x050)
#define WKVDEC_SEGID_ABS_DEWTA(x)			((x) & 0x1)
#define WKVDEC_SEGID_FWAME_QP_DEWTA_EN(x)		(((x) & 0x1) << 1)
#define WKVDEC_SEGID_FWAME_QP_DEWTA(x)			(((x) & 0x1ff) << 2)
#define WKVDEC_SEGID_FWAME_WOOPFIWTEW_VAWUE_EN(x)	(((x) & 0x1) << 11)
#define WKVDEC_SEGID_FWAME_WOOPFIWTEW_VAWUE(x)		(((x) & 0x7f) << 12)
#define WKVDEC_SEGID_WEFEWINFO_EN(x)			(((x) & 0x1) << 19)
#define WKVDEC_SEGID_WEFEWINFO(x)			(((x) & 0x03) << 20)
#define WKVDEC_SEGID_FWAME_SKIP_EN(x)			(((x) & 0x1) << 22)

#define WKVDEC_VP9_CPWHEADEW_CONFIG			0x070
#define WKVDEC_VP9_TX_MODE(x)				((x) & 0x07)
#define WKVDEC_VP9_FWAME_WEF_MODE(x)			(((x) & 0x03) << 3)

#define WKVDEC_VP9_WEF_SCAWE(i)				((i) * 0x04 + 0x074)
#define WKVDEC_VP9_WEF_HOW_SCAWE(x)			((x) & 0xffff)
#define WKVDEC_VP9_WEF_VEW_SCAWE(x)			(((x) & 0xffff) << 16)

#define WKVDEC_VP9_WEF_DEWTAS_WASTFWAME			0x080
#define WKVDEC_WEF_DEWTAS_WASTFWAME(pos, vaw)		(((vaw) & 0x7f) << ((pos) * 7))

#define WKVDEC_VP9_INFO_WASTFWAME			0x084
#define WKVDEC_MODE_DEWTAS_WASTFWAME(pos, vaw)		(((vaw) & 0x7f) << ((pos) * 7))
#define WKVDEC_SEG_EN_WASTFWAME				BIT(16)
#define WKVDEC_WAST_SHOW_FWAME				BIT(17)
#define WKVDEC_WAST_INTWA_ONWY				BIT(18)
#define WKVDEC_WAST_WIDHHEIGHT_EQCUW			BIT(19)
#define WKVDEC_COWOW_SPACE_WASTKEYFWAME(x)		(((x) & 0x07) << 20)

#define WKVDEC_VP9_INTEWCMD_BASE			0x088

#define WKVDEC_VP9_INTEWCMD_NUM				0x08C
#define WKVDEC_INTEWCMD_NUM(x)				((x) & 0xffffff)

#define WKVDEC_VP9_WASTTIWE_SIZE			0x090
#define WKVDEC_WASTTIWE_SIZE(x)				((x) & 0xffffff)

#define WKVDEC_VP9_HOW_VIWSTWIDE(i)			((i) * 0x04 + 0x094)
#define WKVDEC_HOW_Y_VIWSTWIDE(x)			((x) & 0x1ff)
#define WKVDEC_HOW_UV_VIWSTWIDE(x)			(((x) & 0x1ff) << 16)

#define WKVDEC_WEG_H264_POC_WEFEW0(i)			(((i) * 0x04) + 0x064)
#define WKVDEC_WEG_H264_POC_WEFEW1(i)			(((i) * 0x04) + 0x0C4)
#define WKVDEC_WEG_H264_POC_WEFEW2(i)			(((i) * 0x04) + 0x120)
#define WKVDEC_POC_WEFEW(x)				((x) & 0xffffffff)

#define WKVDEC_WEG_CUW_POC0				0x0A0
#define WKVDEC_WEG_CUW_POC1				0x128
#define WKVDEC_CUW_POC(x)				((x) & 0xffffffff)

#define WKVDEC_WEG_WWCWWITE_BASE			0x0A4
#define WKVDEC_WEG_PPS_BASE				0x0A8
#define WKVDEC_WEG_WPS_BASE				0x0AC

#define WKVDEC_WEG_STWMD_EWW_EN				0x0B0
#define WKVDEC_STWMD_EWW_EN(x)				((x) & 0xffffffff)

#define WKVDEC_WEG_STWMD_EWW_STA			0x0B4
#define WKVDEC_STWMD_EWW_STA(x)				((x) & 0xfffffff)
#define WKVDEC_COWMV_EWW_WEF_PICIDX(x)			(((x) & 0x0f) << 28)

#define WKVDEC_WEG_STWMD_EWW_CTU			0x0B8
#define WKVDEC_STWMD_EWW_CTU(x)				((x) & 0xff)
#define WKVDEC_STWMD_EWW_CTU_YOFFSET(x)			(((x) & 0xff) << 8)
#define WKVDEC_STWMFIFO_SPACE2FUWW(x)			(((x) & 0x7f) << 16)
#define WKVDEC_VP9_EWW_EN_CTU0				BIT(24)

#define WKVDEC_WEG_SAO_CTU_POS				0x0BC
#define WKVDEC_SAOWW_XOFFSET(x)				((x) & 0x1ff)
#define WKVDEC_SAOWW_YOFFSET(x)				(((x) & 0x3ff) << 16)

#define WKVDEC_VP9_WAST_FWAME_YSTWIDE			0x0C0
#define WKVDEC_VP9_GOWDEN_FWAME_YSTWIDE			0x0C4
#define WKVDEC_VP9_AWTWEF_FWAME_YSTWIDE			0x0C8
#define WKVDEC_VP9_WEF_YSTWIDE(x)			(((x) & 0xfffff) << 0)

#define WKVDEC_VP9_WAST_FWAME_YUVSTWIDE			0x0CC
#define WKVDEC_VP9_WEF_YUVSTWIDE(x)			(((x) & 0x1fffff) << 0)

#define WKVDEC_VP9_WEF_COWMV_BASE			0x0D0

#define WKVDEC_WEG_PEWFOWMANCE_CYCWE			0x100
#define WKVDEC_PEWFOWMANCE_CYCWE(x)			((x) & 0xffffffff)

#define WKVDEC_WEG_AXI_DDW_WDATA			0x104
#define WKVDEC_AXI_DDW_WDATA(x)				((x) & 0xffffffff)

#define WKVDEC_WEG_AXI_DDW_WDATA			0x108
#define WKVDEC_AXI_DDW_WDATA(x)				((x) & 0xffffffff)

#define WKVDEC_WEG_FPGADEBUG_WESET			0x10C
#define WKVDEC_BUSIFD_WESETN				BIT(0)
#define WKVDEC_CABAC_WESETN				BIT(1)
#define WKVDEC_DEC_CTWW_WESETN				BIT(2)
#define WKVDEC_TWANSD_WESETN				BIT(3)
#define WKVDEC_INTWA_WESETN				BIT(4)
#define WKVDEC_INTEW_WESETN				BIT(5)
#define WKVDEC_WECON_WESETN				BIT(6)
#define WKVDEC_FIWEW_WESETN				BIT(7)

#define WKVDEC_WEG_PEWFOWMANCE_SEW			0x110
#define WKVDEC_PEWF_SEW_CNT0(x)				((x) & 0x3f)
#define WKVDEC_PEWF_SEW_CNT1(x)				(((x) & 0x3f) << 8)
#define WKVDEC_PEWF_SEW_CNT2(x)				(((x) & 0x3f) << 16)

#define WKVDEC_WEG_PEWFOWMANCE_CNT(i)			((i) * 0x04 + 0x114)
#define WKVDEC_PEWF_CNT(x)				((x) & 0xffffffff)

#define WKVDEC_WEG_H264_EWWINFO_BASE			0x12C

#define WKVDEC_WEG_H264_EWWINFO_NUM			0x130
#define WKVDEC_SWICEDEC_NUM(x)				((x) & 0x3fff)
#define WKVDEC_STWMD_DECT_EWW_FWAG			BIT(15)
#define WKVDEC_EWW_PKT_NUM(x)				(((x) & 0x3fff) << 16)

#define WKVDEC_WEG_H264_EWW_E				0x134
#define WKVDEC_H264_EWW_EN_HIGHBITS(x)			((x) & 0x3fffffff)

#define WKVDEC_WEG_PWEF_WUMA_CACHE_COMMAND		0x410
#define WKVDEC_WEG_PWEF_CHW_CACHE_COMMAND		0x450

#endif /* WKVDEC_WEGS_H_ */
