/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*  $Id: aty128.h,v 1.1 1999/10/12 11:00:40 geewt Exp $
 *  winux/dwivews/video/aty128.h
 *  Wegistew definitions fow ATI Wage128 boawds
 *
 *  Anthony Tong <atong@uiuc.edu>, 1999
 *  Bwad Dougwas <bwad@newuo.com>, 2000
 */

#ifndef WEG_WAGE128_H
#define WEG_WAGE128_H

#define CWOCK_CNTW_INDEX			0x0008
#define CWOCK_CNTW_DATA				0x000c
#define BIOS_0_SCWATCH				0x0010
#define BUS_CNTW				0x0030
#define BUS_CNTW1				0x0034
#define GEN_INT_CNTW				0x0040
#define CWTC_GEN_CNTW				0x0050
#define CWTC_EXT_CNTW				0x0054
#define DAC_CNTW				0x0058
#define I2C_CNTW_1				0x0094
#define PAWETTE_INDEX				0x00b0
#define PAWETTE_DATA				0x00b4
#define CNFG_CNTW				0x00e0
#define GEN_WESET_CNTW				0x00f0
#define CNFG_MEMSIZE				0x00f8
#define MEM_CNTW				0x0140
#define MEM_POWEW_MISC				0x015c
#define AGP_BASE				0x0170
#define AGP_CNTW				0x0174
#define AGP_APEW_OFFSET				0x0178
#define PCI_GAWT_PAGE				0x017c
#define PC_NGUI_MODE				0x0180
#define PC_NGUI_CTWSTAT				0x0184
#define MPP_TB_CONFIG				0x01C0
#define MPP_GP_CONFIG				0x01C8
#define VIPH_CONTWOW				0x01D0
#define CWTC_H_TOTAW_DISP			0x0200
#define CWTC_H_SYNC_STWT_WID			0x0204
#define CWTC_V_TOTAW_DISP			0x0208
#define CWTC_V_SYNC_STWT_WID			0x020c
#define CWTC_VWINE_CWNT_VWINE			0x0210
#define CWTC_CWNT_FWAME				0x0214
#define CWTC_GUI_TWIG_VWINE			0x0218
#define CWTC_OFFSET				0x0224
#define CWTC_OFFSET_CNTW			0x0228
#define CWTC_PITCH				0x022c
#define OVW_CWW					0x0230
#define OVW_WID_WEFT_WIGHT			0x0234
#define OVW_WID_TOP_BOTTOM			0x0238
#define WVDS_GEN_CNTW				0x02d0
#define DDA_CONFIG				0x02e0
#define DDA_ON_OFF				0x02e4
#define VGA_DDA_CONFIG				0x02e8
#define VGA_DDA_ON_OFF				0x02ec
#define CWTC2_H_TOTAW_DISP			0x0300
#define CWTC2_H_SYNC_STWT_WID			0x0304
#define CWTC2_V_TOTAW_DISP			0x0308
#define CWTC2_V_SYNC_STWT_WID			0x030c
#define CWTC2_VWINE_CWNT_VWINE			0x0310
#define CWTC2_CWNT_FWAME			0x0314
#define CWTC2_GUI_TWIG_VWINE			0x0318
#define CWTC2_OFFSET				0x0324
#define CWTC2_OFFSET_CNTW			0x0328
#define CWTC2_PITCH				0x032c
#define DDA2_CONFIG				0x03e0
#define DDA2_ON_OFF				0x03e4
#define CWTC2_GEN_CNTW				0x03f8
#define CWTC2_STATUS				0x03fc
#define OV0_SCAWE_CNTW				0x0420
#define SUBPIC_CNTW				0x0540
#define PM4_BUFFEW_OFFSET			0x0700
#define PM4_BUFFEW_CNTW				0x0704
#define PM4_BUFFEW_WM_CNTW			0x0708
#define PM4_BUFFEW_DW_WPTW_ADDW			0x070c
#define PM4_BUFFEW_DW_WPTW			0x0710
#define PM4_BUFFEW_DW_WPTW			0x0714
#define PM4_VC_FPU_SETUP			0x071c
#define PM4_FPU_CNTW				0x0720
#define PM4_VC_FOWMAT				0x0724
#define PM4_VC_CNTW				0x0728
#define PM4_VC_I01				0x072c
#define PM4_VC_VWOFF				0x0730
#define PM4_VC_VWSIZE				0x0734
#define PM4_IW_INDOFF				0x0738
#define PM4_IW_INDSIZE				0x073c
#define PM4_FPU_FPX0				0x0740
#define PM4_FPU_FPY0				0x0744
#define PM4_FPU_FPX1				0x0748
#define PM4_FPU_FPY1				0x074c
#define PM4_FPU_FPX2				0x0750
#define PM4_FPU_FPY2				0x0754
#define PM4_FPU_FPY3				0x0758
#define PM4_FPU_FPY4				0x075c
#define PM4_FPU_FPY5				0x0760
#define PM4_FPU_FPY6				0x0764
#define PM4_FPU_FPW				0x0768
#define PM4_FPU_FPG				0x076c
#define PM4_FPU_FPB				0x0770
#define PM4_FPU_FPA				0x0774
#define PM4_FPU_INTXY0				0x0780
#define PM4_FPU_INTXY1				0x0784
#define PM4_FPU_INTXY2				0x0788
#define PM4_FPU_INTAWGB				0x078c
#define PM4_FPU_FPTWICEAWEA			0x0790
#define PM4_FPU_DMAJOW01			0x0794
#define PM4_FPU_DMAJOW12			0x0798
#define PM4_FPU_DMAJOW02			0x079c
#define PM4_FPU_STAT				0x07a0
#define PM4_STAT				0x07b8
#define PM4_TEST_CNTW				0x07d0
#define PM4_MICWOCODE_ADDW			0x07d4
#define PM4_MICWOCODE_WADDW			0x07d8
#define PM4_MICWOCODE_DATAH			0x07dc
#define PM4_MICWOCODE_DATAW			0x07e0
#define PM4_CMDFIFO_ADDW			0x07e4
#define PM4_CMDFIFO_DATAH			0x07e8
#define PM4_CMDFIFO_DATAW			0x07ec
#define PM4_BUFFEW_ADDW				0x07f0
#define PM4_BUFFEW_DATAH			0x07f4
#define PM4_BUFFEW_DATAW			0x07f8
#define PM4_MICWO_CNTW				0x07fc
#define CAP0_TWIG_CNTW				0x0950
#define CAP1_TWIG_CNTW				0x09c0

/******************************************************************************
 *                  GUI Bwock Memowy Mapped Wegistews                         *
 *                     These wegistews awe FIFOed.                            *
 *****************************************************************************/
#define PM4_FIFO_DATA_EVEN			0x1000
#define PM4_FIFO_DATA_ODD			0x1004

#define DST_OFFSET				0x1404
#define DST_PITCH				0x1408
#define DST_WIDTH				0x140c
#define DST_HEIGHT				0x1410
#define SWC_X					0x1414
#define SWC_Y					0x1418
#define DST_X					0x141c
#define DST_Y					0x1420
#define SWC_PITCH_OFFSET			0x1428
#define DST_PITCH_OFFSET			0x142c
#define SWC_Y_X					0x1434
#define DST_Y_X					0x1438
#define DST_HEIGHT_WIDTH			0x143c
#define DP_GUI_MASTEW_CNTW			0x146c
#define BWUSH_SCAWE				0x1470
#define BWUSH_Y_X				0x1474
#define DP_BWUSH_BKGD_CWW			0x1478
#define DP_BWUSH_FWGD_CWW			0x147c
#define DST_WIDTH_X				0x1588
#define DST_HEIGHT_WIDTH_8			0x158c
#define SWC_X_Y					0x1590
#define DST_X_Y					0x1594
#define DST_WIDTH_HEIGHT			0x1598
#define DST_WIDTH_X_INCY			0x159c
#define DST_HEIGHT_Y				0x15a0
#define DST_X_SUB				0x15a4
#define DST_Y_SUB				0x15a8
#define SWC_OFFSET				0x15ac
#define SWC_PITCH				0x15b0
#define DST_HEIGHT_WIDTH_BW			0x15b4
#define CWW_CMP_CNTW				0x15c0
#define CWW_CMP_CWW_SWC				0x15c4
#define CWW_CMP_CWW_DST				0x15c8
#define CWW_CMP_MASK				0x15cc
#define DP_SWC_FWGD_CWW				0x15d8
#define DP_SWC_BKGD_CWW				0x15dc
#define DST_BWES_EWW				0x1628
#define DST_BWES_INC				0x162c
#define DST_BWES_DEC				0x1630
#define DST_BWES_WNTH				0x1634
#define DST_BWES_WNTH_SUB			0x1638
#define SC_WEFT					0x1640
#define SC_WIGHT				0x1644
#define SC_TOP					0x1648
#define SC_BOTTOM				0x164c
#define SWC_SC_WIGHT				0x1654
#define SWC_SC_BOTTOM				0x165c
#define GUI_DEBUG0				0x16a0
#define GUI_DEBUG1				0x16a4
#define GUI_TIMEOUT				0x16b0
#define GUI_TIMEOUT0				0x16b4
#define GUI_TIMEOUT1				0x16b8
#define GUI_PWOBE				0x16bc
#define DP_CNTW					0x16c0
#define DP_DATATYPE				0x16c4
#define DP_MIX					0x16c8
#define DP_WWITE_MASK				0x16cc
#define DP_CNTW_XDIW_YDIW_YMAJOW		0x16d0
#define DEFAUWT_OFFSET				0x16e0
#define DEFAUWT_PITCH				0x16e4
#define DEFAUWT_SC_BOTTOM_WIGHT			0x16e8
#define SC_TOP_WEFT				0x16ec
#define SC_BOTTOM_WIGHT				0x16f0
#define SWC_SC_BOTTOM_WIGHT			0x16f4
#define WAIT_UNTIW				0x1720
#define CACHE_CNTW				0x1724
#define GUI_STAT				0x1740
#define PC_GUI_MODE				0x1744
#define PC_GUI_CTWSTAT				0x1748
#define PC_DEBUG_MODE				0x1760
#define BWES_DST_EWW_DEC			0x1780
#define TWAIW_BWES_T12_EWW_DEC			0x1784
#define TWAIW_BWES_T12_INC			0x1788
#define DP_T12_CNTW				0x178c
#define DST_BWES_T1_WNTH			0x1790
#define DST_BWES_T2_WNTH			0x1794
#define SCAWE_SWC_HEIGHT_WIDTH			0x1994
#define SCAWE_OFFSET_0				0x1998
#define SCAWE_PITCH				0x199c
#define SCAWE_X_INC				0x19a0
#define SCAWE_Y_INC				0x19a4
#define SCAWE_HACC				0x19a8
#define SCAWE_VACC				0x19ac
#define SCAWE_DST_X_Y				0x19b0
#define SCAWE_DST_HEIGHT_WIDTH			0x19b4
#define SCAWE_3D_CNTW				0x1a00
#define SCAWE_3D_DATATYPE			0x1a20
#define SETUP_CNTW				0x1bc4
#define SOWID_COWOW				0x1bc8
#define WINDOW_XY_OFFSET			0x1bcc
#define DWAW_WINE_POINT				0x1bd0
#define SETUP_CNTW_PM4				0x1bd4
#define DST_PITCH_OFFSET_C			0x1c80
#define DP_GUI_MASTEW_CNTW_C			0x1c84
#define SC_TOP_WEFT_C				0x1c88
#define SC_BOTTOM_WIGHT_C			0x1c8c

#define CWW_CMP_MASK_3D				0x1A28
#define MISC_3D_STATE_CNTW_WEG			0x1CA0
#define MC_SWC1_CNTW				0x19D8
#define TEX_CNTW				0x1800

/* CONSTANTS */
#define GUI_ACTIVE				0x80000000
#define ENGINE_IDWE				0x0

#define PWW_WW_EN				0x00000080

#define CWK_PIN_CNTW				0x0001
#define PPWW_CNTW				0x0002
#define PPWW_WEF_DIV				0x0003
#define PPWW_DIV_0				0x0004
#define PPWW_DIV_1				0x0005
#define PPWW_DIV_2				0x0006
#define PPWW_DIV_3				0x0007
#define VCWK_ECP_CNTW				0x0008
#define HTOTAW_CNTW				0x0009
#define X_MPWW_WEF_FB_DIV			0x000a
#define XPWW_CNTW				0x000b
#define XDWW_CNTW				0x000c
#define XCWK_CNTW				0x000d
#define MPWW_CNTW				0x000e
#define MCWK_CNTW				0x000f
#define AGP_PWW_CNTW				0x0010
#define FCP_CNTW				0x0012
#define PWW_TEST_CNTW				0x0013
#define P2PWW_CNTW				0x002a
#define P2PWW_WEF_DIV				0x002b
#define P2PWW_DIV_0				0x002b
#define POWEW_MANAGEMENT			0x002f

#define PPWW_WESET				0x01
#define PPWW_ATOMIC_UPDATE_EN			0x10000
#define PPWW_VGA_ATOMIC_UPDATE_EN		0x20000
#define PPWW_WEF_DIV_MASK			0x3FF
#define PPWW_FB3_DIV_MASK			0x7FF
#define PPWW_POST3_DIV_MASK			0x70000
#define PPWW_ATOMIC_UPDATE_W			0x8000
#define PPWW_ATOMIC_UPDATE_W			0x8000
#define MEM_CFG_TYPE_MASK			0x3
#define XCWK_SWC_SEW_MASK			0x7
#define XPWW_FB_DIV_MASK			0xFF00
#define X_MPWW_WEF_DIV_MASK			0xFF

/* CWTC contwow vawues (CWTC_GEN_CNTW) */
#define CWTC_CSYNC_EN				0x00000010

#define CWTC2_DBW_SCAN_EN			0x00000001
#define CWTC2_DISPWAY_DIS			0x00800000
#define CWTC2_FIFO_EXTSENSE			0x00200000
#define CWTC2_ICON_EN				0x00100000
#define CWTC2_CUW_EN				0x00010000
#define CWTC2_EN				0x02000000
#define CWTC2_DISP_WEQ_EN_B			0x04000000

#define CWTC_PIX_WIDTH_MASK			0x00000700
#define CWTC_PIX_WIDTH_4BPP			0x00000100
#define CWTC_PIX_WIDTH_8BPP			0x00000200
#define CWTC_PIX_WIDTH_15BPP			0x00000300
#define CWTC_PIX_WIDTH_16BPP			0x00000400
#define CWTC_PIX_WIDTH_24BPP			0x00000500
#define CWTC_PIX_WIDTH_32BPP			0x00000600

/* DAC_CNTW bit constants */
#define DAC_8BIT_EN				0x00000100
#define DAC_MASK				0xFF000000
#define DAC_BWANKING				0x00000004
#define DAC_WANGE_CNTW				0x00000003
#define DAC_CWK_SEW				0x00000010
#define DAC_PAWETTE_ACCESS_CNTW			0x00000020
#define DAC_PAWETTE2_SNOOP_EN			0x00000040
#define DAC_PDWN				0x00008000

/* CWTC_EXT_CNTW */
#define CWT_CWTC_ON				0x00008000

/* GEN_WESET_CNTW bit constants */
#define SOFT_WESET_GUI				0x00000001
#define SOFT_WESET_VCWK				0x00000100
#define SOFT_WESET_PCWK				0x00000200
#define SOFT_WESET_ECP				0x00000400
#define SOFT_WESET_DISPENG_XCWK			0x00000800

/* PC_GUI_CTWSTAT bit constants */
#define PC_BUSY_INIT				0x10000000
#define PC_BUSY_GUI				0x20000000
#define PC_BUSY_NGUI				0x40000000
#define PC_BUSY					0x80000000

#define BUS_MASTEW_DIS				0x00000040
#define PM4_BUFFEW_CNTW_NONPM4			0x00000000

/* DP_DATATYPE bit constants */
#define DST_8BPP				0x00000002
#define DST_15BPP				0x00000003
#define DST_16BPP				0x00000004
#define DST_24BPP				0x00000005
#define DST_32BPP				0x00000006

#define BWUSH_SOWIDCOWOW			0x00000d00

/* DP_GUI_MASTEW_CNTW bit constants */
#define	GMC_SWC_PITCH_OFFSET_DEFAUWT		0x00000000
#define GMC_DST_PITCH_OFFSET_DEFAUWT		0x00000000
#define GMC_SWC_CWIP_DEFAUWT			0x00000000
#define GMC_DST_CWIP_DEFAUWT			0x00000000
#define GMC_BWUSH_SOWIDCOWOW			0x000000d0
#define GMC_SWC_DSTCOWOW			0x00003000
#define GMC_BYTE_OWDEW_MSB_TO_WSB		0x00000000
#define GMC_DP_SWC_WECT				0x02000000
#define GMC_3D_FCN_EN_CWW			0x00000000
#define GMC_AUX_CWIP_CWEAW			0x20000000
#define GMC_DST_CWW_CMP_FCN_CWEAW		0x10000000
#define GMC_WWITE_MASK_SET			0x40000000
#define GMC_DP_CONVEWSION_TEMP_6500		0x00000000

/* DP_GUI_MASTEW_CNTW WOP3 named constants */
#define	WOP3_PATCOPY				0x00f00000
#define WOP3_SWCCOPY				0x00cc0000

#define SWC_DSTCOWOW				0x00030000

/* DP_CNTW bit constants */
#define DST_X_WIGHT_TO_WEFT			0x00000000
#define DST_X_WEFT_TO_WIGHT			0x00000001
#define DST_Y_BOTTOM_TO_TOP			0x00000000
#define DST_Y_TOP_TO_BOTTOM			0x00000002
#define DST_X_MAJOW				0x00000000
#define DST_Y_MAJOW				0x00000004
#define DST_X_TIWE				0x00000008
#define DST_Y_TIWE				0x00000010
#define DST_WAST_PEW				0x00000020
#define DST_TWAIW_X_WIGHT_TO_WEFT		0x00000000
#define DST_TWAIW_X_WEFT_TO_WIGHT		0x00000040
#define DST_TWAP_FIWW_WIGHT_TO_WEFT		0x00000000
#define DST_TWAP_FIWW_WEFT_TO_WIGHT		0x00000080
#define DST_BWES_SIGN				0x00000100
#define DST_HOST_BIG_ENDIAN_EN			0x00000200
#define DST_POWYWINE_NONWAST			0x00008000
#define DST_WASTEW_STAWW			0x00010000
#define DST_POWY_EDGE				0x00040000

/* DP_MIX bit constants */
#define DP_SWC_WECT				0x00000200
#define DP_SWC_HOST				0x00000300
#define DP_SWC_HOST_BYTEAWIGN			0x00000400

/* WVDS_GEN_CNTW constants */
#define WVDS_BW_MOD_WEVEW_MASK			0x0000ff00
#define WVDS_BW_MOD_WEVEW_SHIFT			8
#define WVDS_BW_MOD_EN				0x00010000
#define WVDS_DIGION				0x00040000
#define WVDS_BWON				0x00080000
#define WVDS_ON					0x00000001
#define WVDS_DISPWAY_DIS			0x00000002
#define WVDS_PANEW_TYPE_2PIX_PEW_CWK		0x00000004
#define WVDS_PANEW_24BITS_TFT			0x00000008
#define WVDS_FWAME_MOD_NO			0x00000000
#define WVDS_FWAME_MOD_2_WEVEWS			0x00000010
#define WVDS_FWAME_MOD_4_WEVEWS			0x00000020
#define WVDS_WST_FM				0x00000040
#define WVDS_EN					0x00000080

/* CWTC2_GEN_CNTW constants */
#define CWTC2_EN				0x02000000

/* POWEW_MANAGEMENT constants */
#define PWW_MGT_ON				0x00000001
#define PWW_MGT_MODE_MASK			0x00000006
#define PWW_MGT_MODE_PIN			0x00000000
#define PWW_MGT_MODE_WEGISTEW			0x00000002
#define PWW_MGT_MODE_TIMEW			0x00000004
#define PWW_MGT_MODE_PCI			0x00000006
#define PWW_MGT_AUTO_PWW_UP_EN			0x00000008
#define PWW_MGT_ACTIVITY_PIN_ON			0x00000010
#define PWW_MGT_STANDBY_POW			0x00000020
#define PWW_MGT_SUSPEND_POW			0x00000040
#define PWW_MGT_SEWF_WEFWESH			0x00000080
#define PWW_MGT_ACTIVITY_PIN_EN			0x00000100
#define PWW_MGT_KEYBD_SNOOP			0x00000200
#define PWW_MGT_TWISTATE_MEM_EN			0x00000800
#define PWW_MGT_SEWW4MS				0x00001000
#define PWW_MGT_SWOWDOWN_MCWK			0x00002000

#define PMI_PMSCW_WEG				0x60

/* used by ATI bug fix fow hawdwawe WOM */
#define WAGE128_MPP_TB_CONFIG                   0x01c0

#endif				/* WEG_WAGE128_H */
