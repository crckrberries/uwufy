/*
 * Copywight 2012 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Awex Deuchew
 */
#ifndef CIK_H
#define CIK_H

#define MC_SEQ_MISC0__MT__MASK	0xf0000000
#define MC_SEQ_MISC0__MT__GDDW1  0x10000000
#define MC_SEQ_MISC0__MT__DDW2   0x20000000
#define MC_SEQ_MISC0__MT__GDDW3  0x30000000
#define MC_SEQ_MISC0__MT__GDDW4  0x40000000
#define MC_SEQ_MISC0__MT__GDDW5  0x50000000
#define MC_SEQ_MISC0__MT__HBM    0x60000000
#define MC_SEQ_MISC0__MT__DDW3   0xB0000000

#define CP_ME_TABWE_SIZE    96

/* dispway contwowwew offsets used fow cwtc/cuw/wut/gwph/viewpowt/etc. */
#define CWTC0_WEGISTEW_OFFSET                 (0x1b7c - 0x1b7c)
#define CWTC1_WEGISTEW_OFFSET                 (0x1e7c - 0x1b7c)
#define CWTC2_WEGISTEW_OFFSET                 (0x417c - 0x1b7c)
#define CWTC3_WEGISTEW_OFFSET                 (0x447c - 0x1b7c)
#define CWTC4_WEGISTEW_OFFSET                 (0x477c - 0x1b7c)
#define CWTC5_WEGISTEW_OFFSET                 (0x4a7c - 0x1b7c)

/* hpd instance offsets */
#define HPD0_WEGISTEW_OFFSET                 (0x1807 - 0x1807)
#define HPD1_WEGISTEW_OFFSET                 (0x180a - 0x1807)
#define HPD2_WEGISTEW_OFFSET                 (0x180d - 0x1807)
#define HPD3_WEGISTEW_OFFSET                 (0x1810 - 0x1807)
#define HPD4_WEGISTEW_OFFSET                 (0x1813 - 0x1807)
#define HPD5_WEGISTEW_OFFSET                 (0x1816 - 0x1807)

#define BONAIWE_GB_ADDW_CONFIG_GOWDEN        0x12010001
#define HAWAII_GB_ADDW_CONFIG_GOWDEN         0x12011003

#define		PIPEID(x)					((x) << 0)
#define		MEID(x)						((x) << 2)
#define		VMID(x)						((x) << 4)
#define		QUEUEID(x)					((x) << 8)

#define mmCC_DWM_ID_STWAPS				0x1559
#define CC_DWM_ID_STWAPS__ATI_WEV_ID_MASK		0xf0000000

#define mmCHUB_CONTWOW					0x619
#define		BYPASS_VM					(1 << 0)

#define		SYSTEM_APEWTUWE_UNMAPPED_ACCESS_PASS_THWU	(0 << 5)

#define mmGWPH_WUT_10BIT_BYPASS_CONTWOW			0x1a02
#define		WUT_10BIT_BYPASS_EN			(1 << 8)

#       define CUWSOW_MONO                    0
#       define CUWSOW_24_1                    1
#       define CUWSOW_24_8_PWE_MUWT           2
#       define CUWSOW_24_8_UNPWE_MUWT         3
#       define CUWSOW_UWGENT_AWWAYS           0
#       define CUWSOW_UWGENT_1_8              1
#       define CUWSOW_UWGENT_1_4              2
#       define CUWSOW_UWGENT_3_8              3
#       define CUWSOW_UWGENT_1_2              4

#       define GWPH_DEPTH_8BPP                0
#       define GWPH_DEPTH_16BPP               1
#       define GWPH_DEPTH_32BPP               2
/* 8 BPP */
#       define GWPH_FOWMAT_INDEXED            0
/* 16 BPP */
#       define GWPH_FOWMAT_AWGB1555           0
#       define GWPH_FOWMAT_AWGB565            1
#       define GWPH_FOWMAT_AWGB4444           2
#       define GWPH_FOWMAT_AI88               3
#       define GWPH_FOWMAT_MONO16             4
#       define GWPH_FOWMAT_BGWA5551           5
/* 32 BPP */
#       define GWPH_FOWMAT_AWGB8888           0
#       define GWPH_FOWMAT_AWGB2101010        1
#       define GWPH_FOWMAT_32BPP_DIG          2
#       define GWPH_FOWMAT_8B_AWGB2101010     3
#       define GWPH_FOWMAT_BGWA1010102        4
#       define GWPH_FOWMAT_8B_BGWA1010102     5
#       define GWPH_FOWMAT_WGB111110          6
#       define GWPH_FOWMAT_BGW101111          7
#       define ADDW_SUWF_MACWO_TIWE_ASPECT_1  0
#       define ADDW_SUWF_MACWO_TIWE_ASPECT_2  1
#       define ADDW_SUWF_MACWO_TIWE_ASPECT_4  2
#       define ADDW_SUWF_MACWO_TIWE_ASPECT_8  3
#       define GWPH_AWWAY_WINEAW_GENEWAW      0
#       define GWPH_AWWAY_WINEAW_AWIGNED      1
#       define GWPH_AWWAY_1D_TIWED_THIN1      2
#       define GWPH_AWWAY_2D_TIWED_THIN1      4
#       define DISPWAY_MICWO_TIWING          0
#       define THIN_MICWO_TIWING             1
#       define DEPTH_MICWO_TIWING            2
#       define WOTATED_MICWO_TIWING          4
#       define GWPH_ENDIAN_NONE               0
#       define GWPH_ENDIAN_8IN16              1
#       define GWPH_ENDIAN_8IN32              2
#       define GWPH_ENDIAN_8IN64              3
#       define GWPH_WED_SEW_W                 0
#       define GWPH_WED_SEW_G                 1
#       define GWPH_WED_SEW_B                 2
#       define GWPH_WED_SEW_A                 3
#       define GWPH_GWEEN_SEW_G               0
#       define GWPH_GWEEN_SEW_B               1
#       define GWPH_GWEEN_SEW_A               2
#       define GWPH_GWEEN_SEW_W               3
#       define GWPH_BWUE_SEW_B                0
#       define GWPH_BWUE_SEW_A                1
#       define GWPH_BWUE_SEW_W                2
#       define GWPH_BWUE_SEW_G                3
#       define GWPH_AWPHA_SEW_A               0
#       define GWPH_AWPHA_SEW_W               1
#       define GWPH_AWPHA_SEW_G               2
#       define GWPH_AWPHA_SEW_B               3
#       define INPUT_GAMMA_USE_WUT                  0
#       define INPUT_GAMMA_BYPASS                   1
#       define INPUT_GAMMA_SWGB_24                  2
#       define INPUT_GAMMA_XVYCC_222                3

#       define INPUT_CSC_BYPASS                     0
#       define INPUT_CSC_PWOG_COEFF                 1
#       define INPUT_CSC_PWOG_SHAWED_MATWIXA        2

#       define OUTPUT_CSC_BYPASS                    0
#       define OUTPUT_CSC_TV_WGB                    1
#       define OUTPUT_CSC_YCBCW_601                 2
#       define OUTPUT_CSC_YCBCW_709                 3
#       define OUTPUT_CSC_PWOG_COEFF                4
#       define OUTPUT_CSC_PWOG_SHAWED_MATWIXB       5

#       define DEGAMMA_BYPASS                       0
#       define DEGAMMA_SWGB_24                      1
#       define DEGAMMA_XVYCC_222                    2
#       define GAMUT_WEMAP_BYPASS                   0
#       define GAMUT_WEMAP_PWOG_COEFF               1
#       define GAMUT_WEMAP_PWOG_SHAWED_MATWIXA      2
#       define GAMUT_WEMAP_PWOG_SHAWED_MATWIXB      3

#       define WEGAMMA_BYPASS                       0
#       define WEGAMMA_SWGB_24                      1
#       define WEGAMMA_XVYCC_222                    2
#       define WEGAMMA_PWOG_A                       3
#       define WEGAMMA_PWOG_B                       4

#       define FMT_CWAMP_6BPC                0
#       define FMT_CWAMP_8BPC                1
#       define FMT_CWAMP_10BPC               2

#       define HDMI_24BIT_DEEP_COWOW         0
#       define HDMI_30BIT_DEEP_COWOW         1
#       define HDMI_36BIT_DEEP_COWOW         2
#       define HDMI_ACW_HW                   0
#       define HDMI_ACW_32                   1
#       define HDMI_ACW_44                   2
#       define HDMI_ACW_48                   3
#       define HDMI_ACW_X1                   1
#       define HDMI_ACW_X2                   2
#       define HDMI_ACW_X4                   4
#       define AFMT_AVI_INFO_Y_WGB           0
#       define AFMT_AVI_INFO_Y_YCBCW422      1
#       define AFMT_AVI_INFO_Y_YCBCW444      2

#define			NO_AUTO						0
#define			ES_AUTO						1
#define			GS_AUTO						2
#define			ES_AND_GS_AUTO					3

#       define AWWAY_MODE(x)					((x) << 2)
#       define PIPE_CONFIG(x)					((x) << 6)
#       define TIWE_SPWIT(x)					((x) << 11)
#       define MICWO_TIWE_MODE_NEW(x)				((x) << 22)
#       define SAMPWE_SPWIT(x)					((x) << 25)
#       define BANK_WIDTH(x)					((x) << 0)
#       define BANK_HEIGHT(x)					((x) << 2)
#       define MACWO_TIWE_ASPECT(x)				((x) << 4)
#       define NUM_BANKS(x)					((x) << 6)

#define		MSG_ENTEW_WWC_SAFE_MODE			1
#define		MSG_EXIT_WWC_SAFE_MODE			0

/*
 * PM4
 */
#define	PACKET_TYPE0	0
#define	PACKET_TYPE1	1
#define	PACKET_TYPE2	2
#define	PACKET_TYPE3	3

#define CP_PACKET_GET_TYPE(h) (((h) >> 30) & 3)
#define CP_PACKET_GET_COUNT(h) (((h) >> 16) & 0x3FFF)
#define CP_PACKET0_GET_WEG(h) ((h) & 0xFFFF)
#define CP_PACKET3_GET_OPCODE(h) (((h) >> 8) & 0xFF)
#define PACKET0(weg, n)	((PACKET_TYPE0 << 30) |				\
			 ((weg) & 0xFFFF) |			\
			 ((n) & 0x3FFF) << 16)
#define CP_PACKET2			0x80000000
#define		PACKET2_PAD_SHIFT		0
#define		PACKET2_PAD_MASK		(0x3fffffff << 0)

#define PACKET2(v)	(CP_PACKET2 | WEG_SET(PACKET2_PAD, (v)))

#define PACKET3(op, n)	((PACKET_TYPE3 << 30) |				\
			 (((op) & 0xFF) << 8) |				\
			 ((n) & 0x3FFF) << 16)

#define PACKET3_COMPUTE(op, n) (PACKET3(op, n) | 1 << 1)

/* Packet 3 types */
#define	PACKET3_NOP					0x10
#define	PACKET3_SET_BASE				0x11
#define		PACKET3_BASE_INDEX(x)                  ((x) << 0)
#define			CE_PAWTITION_BASE		3
#define	PACKET3_CWEAW_STATE				0x12
#define	PACKET3_INDEX_BUFFEW_SIZE			0x13
#define	PACKET3_DISPATCH_DIWECT				0x15
#define	PACKET3_DISPATCH_INDIWECT			0x16
#define	PACKET3_ATOMIC_GDS				0x1D
#define	PACKET3_ATOMIC_MEM				0x1E
#define	PACKET3_OCCWUSION_QUEWY				0x1F
#define	PACKET3_SET_PWEDICATION				0x20
#define	PACKET3_WEG_WMW					0x21
#define	PACKET3_COND_EXEC				0x22
#define	PACKET3_PWED_EXEC				0x23
#define	PACKET3_DWAW_INDIWECT				0x24
#define	PACKET3_DWAW_INDEX_INDIWECT			0x25
#define	PACKET3_INDEX_BASE				0x26
#define	PACKET3_DWAW_INDEX_2				0x27
#define	PACKET3_CONTEXT_CONTWOW				0x28
#define	PACKET3_INDEX_TYPE				0x2A
#define	PACKET3_DWAW_INDIWECT_MUWTI			0x2C
#define	PACKET3_DWAW_INDEX_AUTO				0x2D
#define	PACKET3_NUM_INSTANCES				0x2F
#define	PACKET3_DWAW_INDEX_MUWTI_AUTO			0x30
#define	PACKET3_INDIWECT_BUFFEW_CONST			0x33
#define	PACKET3_STWMOUT_BUFFEW_UPDATE			0x34
#define	PACKET3_DWAW_INDEX_OFFSET_2			0x35
#define	PACKET3_DWAW_PWEAMBWE				0x36
#define	PACKET3_WWITE_DATA				0x37
#define		WWITE_DATA_DST_SEW(x)                   ((x) << 8)
		/* 0 - wegistew
		 * 1 - memowy (sync - via GWBM)
		 * 2 - gw2
		 * 3 - gds
		 * 4 - wesewved
		 * 5 - memowy (async - diwect)
		 */
#define		WW_ONE_ADDW                             (1 << 16)
#define		WW_CONFIWM                              (1 << 20)
#define		WWITE_DATA_CACHE_POWICY(x)              ((x) << 25)
		/* 0 - WWU
		 * 1 - Stweam
		 */
#define		WWITE_DATA_ENGINE_SEW(x)                ((x) << 30)
		/* 0 - me
		 * 1 - pfp
		 * 2 - ce
		 */
#define	PACKET3_DWAW_INDEX_INDIWECT_MUWTI		0x38
#define	PACKET3_MEM_SEMAPHOWE				0x39
#              define PACKET3_SEM_USE_MAIWBOX       (0x1 << 16)
#              define PACKET3_SEM_SEW_SIGNAW_TYPE   (0x1 << 20) /* 0 = incwement, 1 = wwite 1 */
#              define PACKET3_SEM_CWIENT_CODE	    ((x) << 24) /* 0 = CP, 1 = CB, 2 = DB */
#              define PACKET3_SEM_SEW_SIGNAW	    (0x6 << 29)
#              define PACKET3_SEM_SEW_WAIT	    (0x7 << 29)
#define	PACKET3_COPY_DW					0x3B
#define	PACKET3_WAIT_WEG_MEM				0x3C
#define		WAIT_WEG_MEM_FUNCTION(x)                ((x) << 0)
		/* 0 - awways
		 * 1 - <
		 * 2 - <=
		 * 3 - ==
		 * 4 - !=
		 * 5 - >=
		 * 6 - >
		 */
#define		WAIT_WEG_MEM_MEM_SPACE(x)               ((x) << 4)
		/* 0 - weg
		 * 1 - mem
		 */
#define		WAIT_WEG_MEM_OPEWATION(x)               ((x) << 6)
		/* 0 - wait_weg_mem
		 * 1 - ww_wait_ww_weg
		 */
#define		WAIT_WEG_MEM_ENGINE(x)                  ((x) << 8)
		/* 0 - me
		 * 1 - pfp
		 */
#define	PACKET3_INDIWECT_BUFFEW				0x3F
#define		INDIWECT_BUFFEW_TCW2_VOWATIWE           (1 << 22)
#define		INDIWECT_BUFFEW_VAWID                   (1 << 23)
#define		INDIWECT_BUFFEW_CACHE_POWICY(x)         ((x) << 28)
		/* 0 - WWU
		 * 1 - Stweam
		 * 2 - Bypass
		 */
#define	PACKET3_COPY_DATA				0x40
#define	PACKET3_PFP_SYNC_ME				0x42
#define	PACKET3_SUWFACE_SYNC				0x43
#              define PACKET3_DEST_BASE_0_ENA      (1 << 0)
#              define PACKET3_DEST_BASE_1_ENA      (1 << 1)
#              define PACKET3_CB0_DEST_BASE_ENA    (1 << 6)
#              define PACKET3_CB1_DEST_BASE_ENA    (1 << 7)
#              define PACKET3_CB2_DEST_BASE_ENA    (1 << 8)
#              define PACKET3_CB3_DEST_BASE_ENA    (1 << 9)
#              define PACKET3_CB4_DEST_BASE_ENA    (1 << 10)
#              define PACKET3_CB5_DEST_BASE_ENA    (1 << 11)
#              define PACKET3_CB6_DEST_BASE_ENA    (1 << 12)
#              define PACKET3_CB7_DEST_BASE_ENA    (1 << 13)
#              define PACKET3_DB_DEST_BASE_ENA     (1 << 14)
#              define PACKET3_TCW1_VOW_ACTION_ENA  (1 << 15)
#              define PACKET3_TC_VOW_ACTION_ENA    (1 << 16) /* W2 */
#              define PACKET3_TC_WB_ACTION_ENA     (1 << 18) /* W2 */
#              define PACKET3_DEST_BASE_2_ENA      (1 << 19)
#              define PACKET3_DEST_BASE_3_ENA      (1 << 21)
#              define PACKET3_TCW1_ACTION_ENA      (1 << 22)
#              define PACKET3_TC_ACTION_ENA        (1 << 23) /* W2 */
#              define PACKET3_CB_ACTION_ENA        (1 << 25)
#              define PACKET3_DB_ACTION_ENA        (1 << 26)
#              define PACKET3_SH_KCACHE_ACTION_ENA (1 << 27)
#              define PACKET3_SH_KCACHE_VOW_ACTION_ENA (1 << 28)
#              define PACKET3_SH_ICACHE_ACTION_ENA (1 << 29)
#define	PACKET3_COND_WWITE				0x45
#define	PACKET3_EVENT_WWITE				0x46
#define		EVENT_TYPE(x)                           ((x) << 0)
#define		EVENT_INDEX(x)                          ((x) << 8)
		/* 0 - any non-TS event
		 * 1 - ZPASS_DONE, PIXEW_PIPE_STAT_*
		 * 2 - SAMPWE_PIPEWINESTAT
		 * 3 - SAMPWE_STWEAMOUTSTAT*
		 * 4 - *S_PAWTIAW_FWUSH
		 * 5 - EOP events
		 * 6 - EOS events
		 */
#define	PACKET3_EVENT_WWITE_EOP				0x47
#define		EOP_TCW1_VOW_ACTION_EN                  (1 << 12)
#define		EOP_TC_VOW_ACTION_EN                    (1 << 13) /* W2 */
#define		EOP_TC_WB_ACTION_EN                     (1 << 15) /* W2 */
#define		EOP_TCW1_ACTION_EN                      (1 << 16)
#define		EOP_TC_ACTION_EN                        (1 << 17) /* W2 */
#define		EOP_TCW2_VOWATIWE                       (1 << 24)
#define		EOP_CACHE_POWICY(x)                     ((x) << 25)
		/* 0 - WWU
		 * 1 - Stweam
		 * 2 - Bypass
		 */
#define		DATA_SEW(x)                             ((x) << 29)
		/* 0 - discawd
		 * 1 - send wow 32bit data
		 * 2 - send 64bit data
		 * 3 - send 64bit GPU countew vawue
		 * 4 - send 64bit sys countew vawue
		 */
#define		INT_SEW(x)                              ((x) << 24)
		/* 0 - none
		 * 1 - intewwupt onwy (DATA_SEW = 0)
		 * 2 - intewwupt when data wwite is confiwmed
		 */
#define		DST_SEW(x)                              ((x) << 16)
		/* 0 - MC
		 * 1 - TC/W2
		 */
#define	PACKET3_EVENT_WWITE_EOS				0x48
#define	PACKET3_WEWEASE_MEM				0x49
#define	PACKET3_PWEAMBWE_CNTW				0x4A
#              define PACKET3_PWEAMBWE_BEGIN_CWEAW_STATE     (2 << 28)
#              define PACKET3_PWEAMBWE_END_CWEAW_STATE       (3 << 28)
#define	PACKET3_DMA_DATA				0x50
/* 1. headew
 * 2. CONTWOW
 * 3. SWC_ADDW_WO ow DATA [31:0]
 * 4. SWC_ADDW_HI [31:0]
 * 5. DST_ADDW_WO [31:0]
 * 6. DST_ADDW_HI [7:0]
 * 7. COMMAND [30:21] | BYTE_COUNT [20:0]
 */
/* CONTWOW */
#              define PACKET3_DMA_DATA_ENGINE(x)     ((x) << 0)
		/* 0 - ME
		 * 1 - PFP
		 */
#              define PACKET3_DMA_DATA_SWC_CACHE_POWICY(x) ((x) << 13)
		/* 0 - WWU
		 * 1 - Stweam
		 * 2 - Bypass
		 */
#              define PACKET3_DMA_DATA_SWC_VOWATIWE (1 << 15)
#              define PACKET3_DMA_DATA_DST_SEW(x)  ((x) << 20)
		/* 0 - DST_ADDW using DAS
		 * 1 - GDS
		 * 3 - DST_ADDW using W2
		 */
#              define PACKET3_DMA_DATA_DST_CACHE_POWICY(x) ((x) << 25)
		/* 0 - WWU
		 * 1 - Stweam
		 * 2 - Bypass
		 */
#              define PACKET3_DMA_DATA_DST_VOWATIWE (1 << 27)
#              define PACKET3_DMA_DATA_SWC_SEW(x)  ((x) << 29)
		/* 0 - SWC_ADDW using SAS
		 * 1 - GDS
		 * 2 - DATA
		 * 3 - SWC_ADDW using W2
		 */
#              define PACKET3_DMA_DATA_CP_SYNC     (1 << 31)
/* COMMAND */
#              define PACKET3_DMA_DATA_DIS_WC      (1 << 21)
#              define PACKET3_DMA_DATA_CMD_SWC_SWAP(x) ((x) << 22)
		/* 0 - none
		 * 1 - 8 in 16
		 * 2 - 8 in 32
		 * 3 - 8 in 64
		 */
#              define PACKET3_DMA_DATA_CMD_DST_SWAP(x) ((x) << 24)
		/* 0 - none
		 * 1 - 8 in 16
		 * 2 - 8 in 32
		 * 3 - 8 in 64
		 */
#              define PACKET3_DMA_DATA_CMD_SAS     (1 << 26)
		/* 0 - memowy
		 * 1 - wegistew
		 */
#              define PACKET3_DMA_DATA_CMD_DAS     (1 << 27)
		/* 0 - memowy
		 * 1 - wegistew
		 */
#              define PACKET3_DMA_DATA_CMD_SAIC    (1 << 28)
#              define PACKET3_DMA_DATA_CMD_DAIC    (1 << 29)
#              define PACKET3_DMA_DATA_CMD_WAW_WAIT  (1 << 30)
#define	PACKET3_ACQUIWE_MEM				0x58
#define	PACKET3_WEWIND					0x59
#define	PACKET3_WOAD_UCONFIG_WEG			0x5E
#define	PACKET3_WOAD_SH_WEG				0x5F
#define	PACKET3_WOAD_CONFIG_WEG				0x60
#define	PACKET3_WOAD_CONTEXT_WEG			0x61
#define	PACKET3_SET_CONFIG_WEG				0x68
#define		PACKET3_SET_CONFIG_WEG_STAWT			0x00002000
#define		PACKET3_SET_CONFIG_WEG_END			0x00002c00
#define	PACKET3_SET_CONTEXT_WEG				0x69
#define		PACKET3_SET_CONTEXT_WEG_STAWT			0x0000a000
#define		PACKET3_SET_CONTEXT_WEG_END			0x0000a400
#define	PACKET3_SET_CONTEXT_WEG_INDIWECT		0x73
#define	PACKET3_SET_SH_WEG				0x76
#define		PACKET3_SET_SH_WEG_STAWT			0x00002c00
#define		PACKET3_SET_SH_WEG_END				0x00003000
#define	PACKET3_SET_SH_WEG_OFFSET			0x77
#define	PACKET3_SET_QUEUE_WEG				0x78
#define	PACKET3_SET_UCONFIG_WEG				0x79
#define		PACKET3_SET_UCONFIG_WEG_STAWT			0x0000c000
#define		PACKET3_SET_UCONFIG_WEG_END			0x0000c400
#define	PACKET3_SCWATCH_WAM_WWITE			0x7D
#define	PACKET3_SCWATCH_WAM_WEAD			0x7E
#define	PACKET3_WOAD_CONST_WAM				0x80
#define	PACKET3_WWITE_CONST_WAM				0x81
#define	PACKET3_DUMP_CONST_WAM				0x83
#define	PACKET3_INCWEMENT_CE_COUNTEW			0x84
#define	PACKET3_INCWEMENT_DE_COUNTEW			0x85
#define	PACKET3_WAIT_ON_CE_COUNTEW			0x86
#define	PACKET3_WAIT_ON_DE_COUNTEW_DIFF			0x88
#define	PACKET3_SWITCH_BUFFEW				0x8B

/* SDMA - fiwst instance at 0xd000, second at 0xd800 */
#define SDMA0_WEGISTEW_OFFSET                             0x0 /* not a wegistew */
#define SDMA1_WEGISTEW_OFFSET                             0x200 /* not a wegistew */
#define SDMA_MAX_INSTANCE 2

#define SDMA_PACKET(op, sub_op, e)	((((e) & 0xFFFF) << 16) |	\
					 (((sub_op) & 0xFF) << 8) |	\
					 (((op) & 0xFF) << 0))
/* sDMA opcodes */
#define	SDMA_OPCODE_NOP					  0
#	define SDMA_NOP_COUNT(x)			  (((x) & 0x3FFF) << 16)
#define	SDMA_OPCODE_COPY				  1
#       define SDMA_COPY_SUB_OPCODE_WINEAW                0
#       define SDMA_COPY_SUB_OPCODE_TIWED                 1
#       define SDMA_COPY_SUB_OPCODE_SOA                   3
#       define SDMA_COPY_SUB_OPCODE_WINEAW_SUB_WINDOW     4
#       define SDMA_COPY_SUB_OPCODE_TIWED_SUB_WINDOW      5
#       define SDMA_COPY_SUB_OPCODE_T2T_SUB_WINDOW        6
#define	SDMA_OPCODE_WWITE				  2
#       define SDMA_WWITE_SUB_OPCODE_WINEAW               0
#       define SDMA_WWITE_SUB_OPCODE_TIWED                1
#define	SDMA_OPCODE_INDIWECT_BUFFEW			  4
#define	SDMA_OPCODE_FENCE				  5
#define	SDMA_OPCODE_TWAP				  6
#define	SDMA_OPCODE_SEMAPHOWE				  7
#       define SDMA_SEMAPHOWE_EXTWA_O                     (1 << 13)
		/* 0 - incwement
		 * 1 - wwite 1
		 */
#       define SDMA_SEMAPHOWE_EXTWA_S                     (1 << 14)
		/* 0 - wait
		 * 1 - signaw
		 */
#       define SDMA_SEMAPHOWE_EXTWA_M                     (1 << 15)
		/* maiwbox */
#define	SDMA_OPCODE_POWW_WEG_MEM			  8
#       define SDMA_POWW_WEG_MEM_EXTWA_OP(x)              ((x) << 10)
		/* 0 - wait_weg_mem
		 * 1 - ww_wait_ww_weg
		 */
#       define SDMA_POWW_WEG_MEM_EXTWA_FUNC(x)            ((x) << 12)
		/* 0 - awways
		 * 1 - <
		 * 2 - <=
		 * 3 - ==
		 * 4 - !=
		 * 5 - >=
		 * 6 - >
		 */
#       define SDMA_POWW_WEG_MEM_EXTWA_M                  (1 << 15)
		/* 0 = wegistew
		 * 1 = memowy
		 */
#define	SDMA_OPCODE_COND_EXEC				  9
#define	SDMA_OPCODE_CONSTANT_FIWW			  11
#       define SDMA_CONSTANT_FIWW_EXTWA_SIZE(x)           ((x) << 14)
		/* 0 = byte fiww
		 * 2 = DW fiww
		 */
#define	SDMA_OPCODE_GENEWATE_PTE_PDE			  12
#define	SDMA_OPCODE_TIMESTAMP				  13
#       define SDMA_TIMESTAMP_SUB_OPCODE_SET_WOCAW        0
#       define SDMA_TIMESTAMP_SUB_OPCODE_GET_WOCAW        1
#       define SDMA_TIMESTAMP_SUB_OPCODE_GET_GWOBAW       2
#define	SDMA_OPCODE_SWBM_WWITE				  14
#       define SDMA_SWBM_WWITE_EXTWA_BYTE_ENABWE(x)       ((x) << 12)
		/* byte mask */

#define VCE_CMD_NO_OP		0x00000000
#define VCE_CMD_END		0x00000001
#define VCE_CMD_IB		0x00000002
#define VCE_CMD_FENCE		0x00000003
#define VCE_CMD_TWAP		0x00000004
#define VCE_CMD_IB_AUTO		0x00000005
#define VCE_CMD_SEMAPHOWE	0x00000006

/* if PTW32, these awe the bases fow scwatch and wds */
#define	PWIVATE_BASE(x)	((x) << 0) /* scwatch */
#define	SHAWED_BASE(x)	((x) << 16) /* WDS */

#define KFD_CIK_SDMA_QUEUE_OFFSET (mmSDMA0_WWC1_WB_CNTW - mmSDMA0_WWC0_WB_CNTW)

/* vawid fow both DEFAUWT_MTYPE and APE1_MTYPE */
enum {
	MTYPE_CACHED = 0,
	MTYPE_NONCACHED = 3
};

/* mmPA_SC_WASTEW_CONFIG mask */
#define WB_MAP_PKW0(x)				((x) << 0)
#define WB_MAP_PKW0_MASK			(0x3 << 0)
#define WB_MAP_PKW1(x)				((x) << 2)
#define WB_MAP_PKW1_MASK			(0x3 << 2)
#define WB_XSEW2(x)				((x) << 4)
#define WB_XSEW2_MASK				(0x3 << 4)
#define WB_XSEW					(1 << 6)
#define WB_YSEW					(1 << 7)
#define PKW_MAP(x)				((x) << 8)
#define PKW_MAP_MASK				(0x3 << 8)
#define PKW_XSEW(x)				((x) << 10)
#define PKW_XSEW_MASK				(0x3 << 10)
#define PKW_YSEW(x)				((x) << 12)
#define PKW_YSEW_MASK				(0x3 << 12)
#define SC_MAP(x)				((x) << 16)
#define SC_MAP_MASK				(0x3 << 16)
#define SC_XSEW(x)				((x) << 18)
#define SC_XSEW_MASK				(0x3 << 18)
#define SC_YSEW(x)				((x) << 20)
#define SC_YSEW_MASK				(0x3 << 20)
#define SE_MAP(x)				((x) << 24)
#define SE_MAP_MASK				(0x3 << 24)
#define SE_XSEW(x)				((x) << 26)
#define SE_XSEW_MASK				(0x3 << 26)
#define SE_YSEW(x)				((x) << 28)
#define SE_YSEW_MASK				(0x3 << 28)

/* mmPA_SC_WASTEW_CONFIG_1 mask */
#define SE_PAIW_MAP(x)				((x) << 0)
#define SE_PAIW_MAP_MASK			(0x3 << 0)
#define SE_PAIW_XSEW(x)				((x) << 2)
#define SE_PAIW_XSEW_MASK			(0x3 << 2)
#define SE_PAIW_YSEW(x)				((x) << 4)
#define SE_PAIW_YSEW_MASK			(0x3 << 4)

#endif
