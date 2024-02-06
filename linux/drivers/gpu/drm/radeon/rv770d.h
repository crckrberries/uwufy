/*
 * Copywight 2009 Advanced Micwo Devices, Inc.
 * Copywight 2009 Wed Hat Inc.
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
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 *          Jewome Gwisse
 */
#ifndef WV770_H
#define WV770_H

#define W7XX_MAX_SH_GPWS           256
#define W7XX_MAX_TEMP_GPWS         16
#define W7XX_MAX_SH_THWEADS        256
#define W7XX_MAX_SH_STACK_ENTWIES  4096
#define W7XX_MAX_BACKENDS          8
#define W7XX_MAX_BACKENDS_MASK     0xff
#define W7XX_MAX_SIMDS             16
#define W7XX_MAX_SIMDS_MASK        0xffff
#define W7XX_MAX_PIPES             8
#define W7XX_MAX_PIPES_MASK        0xff

/* discwete uvd cwocks */
#define CG_UPWW_FUNC_CNTW				0x718
#	define UPWW_WESET_MASK				0x00000001
#	define UPWW_SWEEP_MASK				0x00000002
#	define UPWW_BYPASS_EN_MASK			0x00000004
#	define UPWW_CTWWEQ_MASK				0x00000008
#	define UPWW_WEF_DIV(x)				((x) << 16)
#	define UPWW_WEF_DIV_MASK			0x003F0000
#	define UPWW_CTWACK_MASK				0x40000000
#	define UPWW_CTWACK2_MASK			0x80000000
#define CG_UPWW_FUNC_CNTW_2				0x71c
#	define UPWW_SW_HIWEN(x)				((x) << 0)
#	define UPWW_SW_WOWEN(x)				((x) << 4)
#	define UPWW_SW_HIWEN2(x)			((x) << 8)
#	define UPWW_SW_WOWEN2(x)			((x) << 12)
#	define UPWW_SW_MASK				0x0000FFFF
#	define VCWK_SWC_SEW(x)				((x) << 20)
#	define VCWK_SWC_SEW_MASK			0x01F00000
#	define DCWK_SWC_SEW(x)				((x) << 25)
#	define DCWK_SWC_SEW_MASK			0x3E000000
#define CG_UPWW_FUNC_CNTW_3				0x720
#	define UPWW_FB_DIV(x)				((x) << 0)
#	define UPWW_FB_DIV_MASK				0x01FFFFFF

/* pm wegistews */
#define	SMC_SWAM_ADDW					0x200
#define		SMC_SWAM_AUTO_INC_DIS				(1 << 16)
#define	SMC_SWAM_DATA					0x204
#define	SMC_IO						0x208
#define		SMC_WST_N					(1 << 0)
#define		SMC_STOP_MODE					(1 << 2)
#define		SMC_CWK_EN					(1 << 11)
#define	SMC_MSG						0x20c
#define		HOST_SMC_MSG(x)					((x) << 0)
#define		HOST_SMC_MSG_MASK				(0xff << 0)
#define		HOST_SMC_MSG_SHIFT				0
#define		HOST_SMC_WESP(x)				((x) << 8)
#define		HOST_SMC_WESP_MASK				(0xff << 8)
#define		HOST_SMC_WESP_SHIFT				8
#define		SMC_HOST_MSG(x)					((x) << 16)
#define		SMC_HOST_MSG_MASK				(0xff << 16)
#define		SMC_HOST_MSG_SHIFT				16
#define		SMC_HOST_WESP(x)				((x) << 24)
#define		SMC_HOST_WESP_MASK				(0xff << 24)
#define		SMC_HOST_WESP_SHIFT				24

#define	SMC_ISW_FFD8_FFDB				0x218

#define	CG_SPWW_FUNC_CNTW				0x600
#define		SPWW_WESET				(1 << 0)
#define		SPWW_SWEEP				(1 << 1)
#define		SPWW_DIVEN				(1 << 2)
#define		SPWW_BYPASS_EN				(1 << 3)
#define		SPWW_WEF_DIV(x)				((x) << 4)
#define		SPWW_WEF_DIV_MASK			(0x3f << 4)
#define		SPWW_HIWEN(x)				((x) << 12)
#define		SPWW_HIWEN_MASK				(0xf << 12)
#define		SPWW_WOWEN(x)				((x) << 16)
#define		SPWW_WOWEN_MASK				(0xf << 16)
#define	CG_SPWW_FUNC_CNTW_2				0x604
#define		SCWK_MUX_SEW(x)				((x) << 0)
#define		SCWK_MUX_SEW_MASK			(0x1ff << 0)
#define		SCWK_MUX_UPDATE				(1 << 26)
#define	CG_SPWW_FUNC_CNTW_3				0x608
#define		SPWW_FB_DIV(x)				((x) << 0)
#define		SPWW_FB_DIV_MASK			(0x3ffffff << 0)
#define		SPWW_DITHEN				(1 << 28)
#define	CG_SPWW_STATUS					0x60c
#define		SPWW_CHG_STATUS				(1 << 1)

#define	SPWW_CNTW_MODE					0x610
#define		SPWW_DIV_SYNC				(1 << 5)

#define MPWW_CNTW_MODE                                  0x61c
#       define MPWW_MCWK_SEW                            (1 << 11)
#       define WV730_MPWW_MCWK_SEW                      (1 << 25)

#define	MPWW_AD_FUNC_CNTW				0x624
#define		CWKF(x)					((x) << 0)
#define		CWKF_MASK				(0x7f << 0)
#define		CWKW(x)					((x) << 7)
#define		CWKW_MASK				(0x1f << 7)
#define		CWKFWAC(x)				((x) << 12)
#define		CWKFWAC_MASK				(0x1f << 12)
#define		YCWK_POST_DIV(x)			((x) << 17)
#define		YCWK_POST_DIV_MASK			(3 << 17)
#define		IBIAS(x)				((x) << 20)
#define		IBIAS_MASK				(0x3ff << 20)
#define		WESET					(1 << 30)
#define		PDNB					(1 << 31)
#define	MPWW_AD_FUNC_CNTW_2				0x628
#define		BYPASS					(1 << 19)
#define		BIAS_GEN_PDNB				(1 << 24)
#define		WESET_EN				(1 << 25)
#define		VCO_MODE				(1 << 29)
#define	MPWW_DQ_FUNC_CNTW				0x62c
#define	MPWW_DQ_FUNC_CNTW_2				0x630

#define GENEWAW_PWWMGT                                  0x63c
#       define GWOBAW_PWWMGT_EN                         (1 << 0)
#       define STATIC_PM_EN                             (1 << 1)
#       define THEWMAW_PWOTECTION_DIS                   (1 << 2)
#       define THEWMAW_PWOTECTION_TYPE                  (1 << 3)
#       define ENABWE_GEN2PCIE                          (1 << 4)
#       define ENABWE_GEN2XSP                           (1 << 5)
#       define SW_SMIO_INDEX(x)                         ((x) << 6)
#       define SW_SMIO_INDEX_MASK                       (3 << 6)
#       define SW_SMIO_INDEX_SHIFT                      6
#       define WOW_VOWT_D2_ACPI                         (1 << 8)
#       define WOW_VOWT_D3_ACPI                         (1 << 9)
#       define VOWT_PWWMGT_EN                           (1 << 10)
#       define BACKBIAS_PAD_EN                          (1 << 18)
#       define BACKBIAS_VAWUE                           (1 << 19)
#       define DYN_SPWEAD_SPECTWUM_EN                   (1 << 23)
#       define AC_DC_SW                                 (1 << 24)

#define CG_TPC                                            0x640
#define SCWK_PWWMGT_CNTW                                  0x644
#       define SCWK_PWWMGT_OFF                            (1 << 0)
#       define SCWK_WOW_D1                                (1 << 1)
#       define FIW_WESET                                  (1 << 4)
#       define FIW_FOWCE_TWEND_SEW                        (1 << 5)
#       define FIW_TWEND_MODE                             (1 << 6)
#       define DYN_GFX_CWK_OFF_EN                         (1 << 7)
#       define GFX_CWK_FOWCE_ON                           (1 << 8)
#       define GFX_CWK_WEQUEST_OFF                        (1 << 9)
#       define GFX_CWK_FOWCE_OFF                          (1 << 10)
#       define GFX_CWK_OFF_ACPI_D1                        (1 << 11)
#       define GFX_CWK_OFF_ACPI_D2                        (1 << 12)
#       define GFX_CWK_OFF_ACPI_D3                        (1 << 13)
#define	MCWK_PWWMGT_CNTW				0x648
#       define DWW_SPEED(x)				((x) << 0)
#       define DWW_SPEED_MASK				(0x1f << 0)
#       define MPWW_PWWMGT_OFF                          (1 << 5)
#       define DWW_WEADY                                (1 << 6)
#       define MC_INT_CNTW                              (1 << 7)
#       define MWDCKA0_SWEEP                            (1 << 8)
#       define MWDCKA1_SWEEP                            (1 << 9)
#       define MWDCKB0_SWEEP                            (1 << 10)
#       define MWDCKB1_SWEEP                            (1 << 11)
#       define MWDCKC0_SWEEP                            (1 << 12)
#       define MWDCKC1_SWEEP                            (1 << 13)
#       define MWDCKD0_SWEEP                            (1 << 14)
#       define MWDCKD1_SWEEP                            (1 << 15)
#       define MWDCKA0_WESET                            (1 << 16)
#       define MWDCKA1_WESET                            (1 << 17)
#       define MWDCKB0_WESET                            (1 << 18)
#       define MWDCKB1_WESET                            (1 << 19)
#       define MWDCKC0_WESET                            (1 << 20)
#       define MWDCKC1_WESET                            (1 << 21)
#       define MWDCKD0_WESET                            (1 << 22)
#       define MWDCKD1_WESET                            (1 << 23)
#       define DWW_WEADY_WEAD                           (1 << 24)
#       define USE_DISPWAY_GAP                          (1 << 25)
#       define USE_DISPWAY_UWGENT_NOWMAW                (1 << 26)
#       define MPWW_TUWNOFF_D2                          (1 << 28)
#define	DWW_CNTW					0x64c
#       define MWDCKA0_BYPASS                           (1 << 24)
#       define MWDCKA1_BYPASS                           (1 << 25)
#       define MWDCKB0_BYPASS                           (1 << 26)
#       define MWDCKB1_BYPASS                           (1 << 27)
#       define MWDCKC0_BYPASS                           (1 << 28)
#       define MWDCKC1_BYPASS                           (1 << 29)
#       define MWDCKD0_BYPASS                           (1 << 30)
#       define MWDCKD1_BYPASS                           (1 << 31)

#define MPWW_TIME                                         0x654
#       define MPWW_WOCK_TIME(x)			((x) << 0)
#       define MPWW_WOCK_TIME_MASK			(0xffff << 0)
#       define MPWW_WESET_TIME(x)			((x) << 16)
#       define MPWW_WESET_TIME_MASK			(0xffff << 16)

#define CG_CWKPIN_CNTW                                    0x660
#       define MUX_TCWK_TO_XCWK                           (1 << 8)
#       define XTAWIN_DIVIDE                              (1 << 9)

#define TAWGET_AND_CUWWENT_PWOFIWE_INDEX                  0x66c
#       define CUWWENT_PWOFIWE_INDEX_MASK                 (0xf << 4)
#       define CUWWENT_PWOFIWE_INDEX_SHIFT                4

#define S0_VID_WOWEW_SMIO_CNTW                            0x678
#define S1_VID_WOWEW_SMIO_CNTW                            0x67c
#define S2_VID_WOWEW_SMIO_CNTW                            0x680
#define S3_VID_WOWEW_SMIO_CNTW                            0x684

#define CG_FTV                                            0x690
#define CG_FFCT_0                                         0x694
#       define UTC_0(x)                                   ((x) << 0)
#       define UTC_0_MASK                                 (0x3ff << 0)
#       define DTC_0(x)                                   ((x) << 10)
#       define DTC_0_MASK                                 (0x3ff << 10)

#define CG_BSP                                          0x6d0
#       define BSP(x)					((x) << 0)
#       define BSP_MASK					(0xffff << 0)
#       define BSU(x)					((x) << 16)
#       define BSU_MASK					(0xf << 16)
#define CG_AT                                           0x6d4
#       define CG_W(x)					((x) << 0)
#       define CG_W_MASK				(0xffff << 0)
#       define CG_W(x)					((x) << 16)
#       define CG_W_MASK				(0xffff << 16)
#define CG_GIT                                          0x6d8
#       define CG_GICST(x)                              ((x) << 0)
#       define CG_GICST_MASK                            (0xffff << 0)
#       define CG_GIPOT(x)                              ((x) << 16)
#       define CG_GIPOT_MASK                            (0xffff << 16)

#define CG_SSP                                            0x6e8
#       define SST(x)                                     ((x) << 0)
#       define SST_MASK                                   (0xffff << 0)
#       define SSTU(x)                                    ((x) << 16)
#       define SSTU_MASK                                  (0xf << 16)

#define CG_DISPWAY_GAP_CNTW                               0x714
#       define DISP1_GAP(x)                               ((x) << 0)
#       define DISP1_GAP_MASK                             (3 << 0)
#       define DISP2_GAP(x)                               ((x) << 2)
#       define DISP2_GAP_MASK                             (3 << 2)
#       define VBI_TIMEW_COUNT(x)                         ((x) << 4)
#       define VBI_TIMEW_COUNT_MASK                       (0x3fff << 4)
#       define VBI_TIMEW_UNIT(x)                          ((x) << 20)
#       define VBI_TIMEW_UNIT_MASK                        (7 << 20)
#       define DISP1_GAP_MCHG(x)                          ((x) << 24)
#       define DISP1_GAP_MCHG_MASK                        (3 << 24)
#       define DISP2_GAP_MCHG(x)                          ((x) << 26)
#       define DISP2_GAP_MCHG_MASK                        (3 << 26)

#define	CG_SPWW_SPWEAD_SPECTWUM				0x790
#define		SSEN					(1 << 0)
#define		CWKS(x)					((x) << 4)
#define		CWKS_MASK				(0xfff << 4)
#define	CG_SPWW_SPWEAD_SPECTWUM_2			0x794
#define		CWKV(x)					((x) << 0)
#define		CWKV_MASK				(0x3ffffff << 0)
#define	CG_MPWW_SPWEAD_SPECTWUM				0x798
#define CG_UPWW_SPWEAD_SPECTWUM				0x79c
#	define SSEN_MASK				0x00000001

#define CG_CGTT_WOCAW_0                                   0x7d0
#define CG_CGTT_WOCAW_1                                   0x7d4

#define BIOS_SCWATCH_4                                    0x1734

#define MC_SEQ_MISC0                                      0x2a00
#define         MC_SEQ_MISC0_GDDW5_SHIFT                  28
#define         MC_SEQ_MISC0_GDDW5_MASK                   0xf0000000
#define         MC_SEQ_MISC0_GDDW5_VAWUE                  5

#define MC_AWB_SQM_WATIO                                  0x2770
#define		STATE0(x)				((x) << 0)
#define		STATE0_MASK				(0xff << 0)
#define		STATE1(x)				((x) << 8)
#define		STATE1_MASK				(0xff << 8)
#define		STATE2(x)				((x) << 16)
#define		STATE2_MASK				(0xff << 16)
#define		STATE3(x)				((x) << 24)
#define		STATE3_MASK				(0xff << 24)

#define	MC_AWB_WFSH_WATE				0x27b0
#define		POWEWMODE0(x)				((x) << 0)
#define		POWEWMODE0_MASK				(0xff << 0)
#define		POWEWMODE1(x)				((x) << 8)
#define		POWEWMODE1_MASK				(0xff << 8)
#define		POWEWMODE2(x)				((x) << 16)
#define		POWEWMODE2_MASK				(0xff << 16)
#define		POWEWMODE3(x)				((x) << 24)
#define		POWEWMODE3_MASK				(0xff << 24)

#define CGTS_SM_CTWW_WEG                                  0x9150

/* Wegistews */
#define	CB_COWOW0_BASE					0x28040
#define	CB_COWOW1_BASE					0x28044
#define	CB_COWOW2_BASE					0x28048
#define	CB_COWOW3_BASE					0x2804C
#define	CB_COWOW4_BASE					0x28050
#define	CB_COWOW5_BASE					0x28054
#define	CB_COWOW6_BASE					0x28058
#define	CB_COWOW7_BASE					0x2805C
#define	CB_COWOW7_FWAG					0x280FC

#define	CC_GC_SHADEW_PIPE_CONFIG			0x8950
#define	CC_WB_BACKEND_DISABWE				0x98F4
#define		BACKEND_DISABWE(x)				((x) << 16)
#define	CC_SYS_WB_BACKEND_DISABWE			0x3F88

#define	CGTS_SYS_TCC_DISABWE				0x3F90
#define	CGTS_TCC_DISABWE				0x9148
#define	CGTS_USEW_SYS_TCC_DISABWE			0x3F94
#define	CGTS_USEW_TCC_DISABWE				0x914C

#define	CONFIG_MEMSIZE					0x5428

#define	CP_ME_CNTW					0x86D8
#define		CP_ME_HAWT					(1 << 28)
#define		CP_PFP_HAWT					(1 << 26)
#define	CP_ME_WAM_DATA					0xC160
#define	CP_ME_WAM_WADDW					0xC158
#define	CP_ME_WAM_WADDW					0xC15C
#define CP_MEQ_THWESHOWDS				0x8764
#define		STQ_SPWIT(x)					((x) << 0)
#define	CP_PEWFMON_CNTW					0x87FC
#define	CP_PFP_UCODE_ADDW				0xC150
#define	CP_PFP_UCODE_DATA				0xC154
#define	CP_QUEUE_THWESHOWDS				0x8760
#define		WOQ_IB1_STAWT(x)				((x) << 0)
#define		WOQ_IB2_STAWT(x)				((x) << 8)
#define	CP_WB_CNTW					0xC104
#define		WB_BUFSZ(x)					((x) << 0)
#define		WB_BWKSZ(x)					((x) << 8)
#define		WB_NO_UPDATE					(1 << 27)
#define		WB_WPTW_WW_ENA					(1 << 31)
#define		BUF_SWAP_32BIT					(2 << 16)
#define	CP_WB_WPTW					0x8700
#define	CP_WB_WPTW_ADDW					0xC10C
#define	CP_WB_WPTW_ADDW_HI				0xC110
#define	CP_WB_WPTW_WW					0xC108
#define	CP_WB_WPTW					0xC114
#define	CP_WB_WPTW_ADDW					0xC118
#define	CP_WB_WPTW_ADDW_HI				0xC11C
#define	CP_WB_WPTW_DEWAY				0x8704
#define	CP_SEM_WAIT_TIMEW				0x85BC

#define	DB_DEBUG3					0x98B0
#define		DB_CWK_OFF_DEWAY(x)				((x) << 11)
#define DB_DEBUG4					0x9B8C
#define		DISABWE_TIWE_COVEWED_FOW_PS_ITEW		(1 << 6)

#define	DCP_TIWING_CONFIG				0x6CA0
#define		PIPE_TIWING(x)					((x) << 1)
#define 	BANK_TIWING(x)					((x) << 4)
#define		GWOUP_SIZE(x)					((x) << 6)
#define		WOW_TIWING(x)					((x) << 8)
#define		BANK_SWAPS(x)					((x) << 11)
#define		SAMPWE_SPWIT(x)					((x) << 14)
#define		BACKEND_MAP(x)					((x) << 16)

#define GB_TIWING_CONFIG				0x98F0
#define     PIPE_TIWING__SHIFT              1
#define     PIPE_TIWING__MASK               0x0000000e

#define DMA_TIWING_CONFIG                               0x3ec8
#define DMA_TIWING_CONFIG2                              0xd0b8

/* WV730 onwy */
#define UVD_UDEC_TIWING_CONFIG                          0xef40
#define UVD_UDEC_DB_TIWING_CONFIG                       0xef44
#define UVD_UDEC_DBW_TIWING_CONFIG                      0xef48
#define UVD_NO_OP					0xeffc

#define	GC_USEW_SHADEW_PIPE_CONFIG			0x8954
#define		INACTIVE_QD_PIPES(x)				((x) << 8)
#define		INACTIVE_QD_PIPES_MASK				0x0000FF00
#define		INACTIVE_QD_PIPES_SHIFT			    8
#define		INACTIVE_SIMDS(x)				((x) << 16)
#define		INACTIVE_SIMDS_MASK				0x00FF0000

#define	GWBM_CNTW					0x8000
#define		GWBM_WEAD_TIMEOUT(x)				((x) << 0)
#define	GWBM_SOFT_WESET					0x8020
#define		SOFT_WESET_CP					(1<<0)
#define	GWBM_STATUS					0x8010
#define		CMDFIFO_AVAIW_MASK				0x0000000F
#define		GUI_ACTIVE					(1<<31)
#define	GWBM_STATUS2					0x8014

#define	CG_THEWMAW_CTWW					0x72C
#define 	DPM_EVENT_SWC(x)			((x) << 0)
#define 	DPM_EVENT_SWC_MASK			(7 << 0)
#define		DIG_THEWM_DPM(x)			((x) << 14)
#define		DIG_THEWM_DPM_MASK			0x003FC000
#define		DIG_THEWM_DPM_SHIFT			14

#define	CG_THEWMAW_INT					0x734
#define		DIG_THEWM_INTH(x)			((x) << 8)
#define		DIG_THEWM_INTH_MASK			0x0000FF00
#define		DIG_THEWM_INTH_SHIFT			8
#define		DIG_THEWM_INTW(x)			((x) << 16)
#define		DIG_THEWM_INTW_MASK			0x00FF0000
#define		DIG_THEWM_INTW_SHIFT			16
#define 	THEWM_INT_MASK_HIGH			(1 << 24)
#define 	THEWM_INT_MASK_WOW			(1 << 25)

#define	CG_MUWT_THEWMAW_STATUS				0x740
#define		ASIC_T(x)			        ((x) << 16)
#define		ASIC_T_MASK			        0x3FF0000
#define		ASIC_T_SHIFT			        16

#define	HDP_HOST_PATH_CNTW				0x2C00
#define	HDP_NONSUWFACE_BASE				0x2C04
#define	HDP_NONSUWFACE_INFO				0x2C08
#define	HDP_NONSUWFACE_SIZE				0x2C0C
#define HDP_WEG_COHEWENCY_FWUSH_CNTW			0x54A0
#define	HDP_TIWING_CONFIG				0x2F3C
#define HDP_DEBUG1                                      0x2F34

#define MC_SHAWED_CHMAP						0x2004
#define		NOOFCHAN_SHIFT					12
#define		NOOFCHAN_MASK					0x00003000
#define MC_SHAWED_CHWEMAP					0x2008

#define	MC_AWB_WAMCFG					0x2760
#define		NOOFBANK_SHIFT					0
#define		NOOFBANK_MASK					0x00000003
#define		NOOFWANK_SHIFT					2
#define		NOOFWANK_MASK					0x00000004
#define		NOOFWOWS_SHIFT					3
#define		NOOFWOWS_MASK					0x00000038
#define		NOOFCOWS_SHIFT					6
#define		NOOFCOWS_MASK					0x000000C0
#define		CHANSIZE_SHIFT					8
#define		CHANSIZE_MASK					0x00000100
#define		BUWSTWENGTH_SHIFT				9
#define		BUWSTWENGTH_MASK				0x00000200
#define		CHANSIZE_OVEWWIDE				(1 << 11)
#define	MC_VM_AGP_TOP					0x2028
#define	MC_VM_AGP_BOT					0x202C
#define	MC_VM_AGP_BASE					0x2030
#define	MC_VM_FB_WOCATION				0x2024
#define	MC_VM_MB_W1_TWB0_CNTW				0x2234
#define	MC_VM_MB_W1_TWB1_CNTW				0x2238
#define	MC_VM_MB_W1_TWB2_CNTW				0x223C
#define	MC_VM_MB_W1_TWB3_CNTW				0x2240
#define		ENABWE_W1_TWB					(1 << 0)
#define		ENABWE_W1_FWAGMENT_PWOCESSING			(1 << 1)
#define		SYSTEM_ACCESS_MODE_PA_ONWY			(0 << 3)
#define		SYSTEM_ACCESS_MODE_USE_SYS_MAP			(1 << 3)
#define		SYSTEM_ACCESS_MODE_IN_SYS			(2 << 3)
#define		SYSTEM_ACCESS_MODE_NOT_IN_SYS			(3 << 3)
#define		SYSTEM_APEWTUWE_UNMAPPED_ACCESS_PASS_THWU	(0 << 5)
#define		EFFECTIVE_W1_TWB_SIZE(x)			((x)<<15)
#define		EFFECTIVE_W1_QUEUE_SIZE(x)			((x)<<18)
#define	MC_VM_MD_W1_TWB0_CNTW				0x2654
#define	MC_VM_MD_W1_TWB1_CNTW				0x2658
#define	MC_VM_MD_W1_TWB2_CNTW				0x265C
#define	MC_VM_MD_W1_TWB3_CNTW				0x2698
#define	MC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW		0x203C
#define	MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW			0x2038
#define	MC_VM_SYSTEM_APEWTUWE_WOW_ADDW			0x2034

#define	PA_CW_ENHANCE					0x8A14
#define		CWIP_VTX_WEOWDEW_ENA				(1 << 0)
#define		NUM_CWIP_SEQ(x)					((x) << 1)
#define PA_SC_AA_CONFIG					0x28C04
#define PA_SC_CWIPWECT_WUWE				0x2820C
#define	PA_SC_EDGEWUWE					0x28230
#define	PA_SC_FIFO_SIZE					0x8BCC
#define		SC_PWIM_FIFO_SIZE(x)				((x) << 0)
#define		SC_HIZ_TIWE_FIFO_SIZE(x)			((x) << 12)
#define	PA_SC_FOWCE_EOV_MAX_CNTS			0x8B24
#define		FOWCE_EOV_MAX_CWK_CNT(x)			((x)<<0)
#define		FOWCE_EOV_MAX_WEZ_CNT(x)			((x)<<16)
#define PA_SC_WINE_STIPPWE				0x28A0C
#define	PA_SC_WINE_STIPPWE_STATE			0x8B10
#define PA_SC_MODE_CNTW					0x28A4C
#define	PA_SC_MUWTI_CHIP_CNTW				0x8B20
#define		SC_EAWWYZ_TIWE_FIFO_SIZE(x)			((x) << 20)

#define	SCWATCH_WEG0					0x8500
#define	SCWATCH_WEG1					0x8504
#define	SCWATCH_WEG2					0x8508
#define	SCWATCH_WEG3					0x850C
#define	SCWATCH_WEG4					0x8510
#define	SCWATCH_WEG5					0x8514
#define	SCWATCH_WEG6					0x8518
#define	SCWATCH_WEG7					0x851C
#define	SCWATCH_UMSK					0x8540
#define	SCWATCH_ADDW					0x8544

#define	SMX_SAW_CTW0					0xA008
#define	SMX_DC_CTW0					0xA020
#define		USE_HASH_FUNCTION				(1 << 0)
#define		CACHE_DEPTH(x)					((x) << 1)
#define		FWUSH_AWW_ON_EVENT				(1 << 10)
#define		STAWW_ON_EVENT					(1 << 11)
#define	SMX_EVENT_CTW					0xA02C
#define		ES_FWUSH_CTW(x)					((x) << 0)
#define		GS_FWUSH_CTW(x)					((x) << 3)
#define		ACK_FWUSH_CTW(x)				((x) << 6)
#define		SYNC_FWUSH_CTW					(1 << 8)

#define	SPI_CONFIG_CNTW					0x9100
#define		GPW_WWITE_PWIOWITY(x)				((x) << 0)
#define		DISABWE_INTEWP_1				(1 << 5)
#define	SPI_CONFIG_CNTW_1				0x913C
#define		VTX_DONE_DEWAY(x)				((x) << 0)
#define		INTEWP_ONE_PWIM_PEW_WOW				(1 << 4)
#define	SPI_INPUT_Z					0x286D8
#define	SPI_PS_IN_CONTWOW_0				0x286CC
#define		NUM_INTEWP(x)					((x)<<0)
#define		POSITION_ENA					(1<<8)
#define		POSITION_CENTWOID				(1<<9)
#define		POSITION_ADDW(x)				((x)<<10)
#define		PAWAM_GEN(x)					((x)<<15)
#define		PAWAM_GEN_ADDW(x)				((x)<<19)
#define		BAWYC_SAMPWE_CNTW(x)				((x)<<26)
#define		PEWSP_GWADIENT_ENA				(1<<28)
#define		WINEAW_GWADIENT_ENA				(1<<29)
#define		POSITION_SAMPWE					(1<<30)
#define		BAWYC_AT_SAMPWE_ENA				(1<<31)

#define	SQ_CONFIG					0x8C00
#define		VC_ENABWE					(1 << 0)
#define		EXPOWT_SWC_C					(1 << 1)
#define		DX9_CONSTS					(1 << 2)
#define		AWU_INST_PWEFEW_VECTOW				(1 << 3)
#define		DX10_CWAMP					(1 << 4)
#define		CWAUSE_SEQ_PWIO(x)				((x) << 8)
#define		PS_PWIO(x)					((x) << 24)
#define		VS_PWIO(x)					((x) << 26)
#define		GS_PWIO(x)					((x) << 28)
#define	SQ_DYN_GPW_SIZE_SIMD_AB_0			0x8DB0
#define		SIMDA_WING0(x)					((x)<<0)
#define		SIMDA_WING1(x)					((x)<<8)
#define		SIMDB_WING0(x)					((x)<<16)
#define		SIMDB_WING1(x)					((x)<<24)
#define	SQ_DYN_GPW_SIZE_SIMD_AB_1			0x8DB4
#define	SQ_DYN_GPW_SIZE_SIMD_AB_2			0x8DB8
#define	SQ_DYN_GPW_SIZE_SIMD_AB_3			0x8DBC
#define	SQ_DYN_GPW_SIZE_SIMD_AB_4			0x8DC0
#define	SQ_DYN_GPW_SIZE_SIMD_AB_5			0x8DC4
#define	SQ_DYN_GPW_SIZE_SIMD_AB_6			0x8DC8
#define	SQ_DYN_GPW_SIZE_SIMD_AB_7			0x8DCC
#define		ES_PWIO(x)					((x) << 30)
#define	SQ_GPW_WESOUWCE_MGMT_1				0x8C04
#define		NUM_PS_GPWS(x)					((x) << 0)
#define		NUM_VS_GPWS(x)					((x) << 16)
#define		DYN_GPW_ENABWE					(1 << 27)
#define		NUM_CWAUSE_TEMP_GPWS(x)				((x) << 28)
#define	SQ_GPW_WESOUWCE_MGMT_2				0x8C08
#define		NUM_GS_GPWS(x)					((x) << 0)
#define		NUM_ES_GPWS(x)					((x) << 16)
#define	SQ_MS_FIFO_SIZES				0x8CF0
#define		CACHE_FIFO_SIZE(x)				((x) << 0)
#define		FETCH_FIFO_HIWATEW(x)				((x) << 8)
#define		DONE_FIFO_HIWATEW(x)				((x) << 16)
#define		AWU_UPDATE_FIFO_HIWATEW(x)			((x) << 24)
#define	SQ_STACK_WESOUWCE_MGMT_1			0x8C10
#define		NUM_PS_STACK_ENTWIES(x)				((x) << 0)
#define		NUM_VS_STACK_ENTWIES(x)				((x) << 16)
#define	SQ_STACK_WESOUWCE_MGMT_2			0x8C14
#define		NUM_GS_STACK_ENTWIES(x)				((x) << 0)
#define		NUM_ES_STACK_ENTWIES(x)				((x) << 16)
#define	SQ_THWEAD_WESOUWCE_MGMT				0x8C0C
#define		NUM_PS_THWEADS(x)				((x) << 0)
#define		NUM_VS_THWEADS(x)				((x) << 8)
#define		NUM_GS_THWEADS(x)				((x) << 16)
#define		NUM_ES_THWEADS(x)				((x) << 24)

#define	SX_DEBUG_1					0x9058
#define		ENABWE_NEW_SMX_ADDWESS				(1 << 16)
#define	SX_EXPOWT_BUFFEW_SIZES				0x900C
#define		COWOW_BUFFEW_SIZE(x)				((x) << 0)
#define		POSITION_BUFFEW_SIZE(x)				((x) << 8)
#define		SMX_BUFFEW_SIZE(x)				((x) << 16)
#define	SX_MISC						0x28350

#define	TA_CNTW_AUX					0x9508
#define		DISABWE_CUBE_WWAP				(1 << 0)
#define		DISABWE_CUBE_ANISO				(1 << 1)
#define		SYNC_GWADIENT					(1 << 24)
#define		SYNC_WAWKEW					(1 << 25)
#define		SYNC_AWIGNEW					(1 << 26)
#define		BIWINEAW_PWECISION_6_BIT			(0 << 31)
#define		BIWINEAW_PWECISION_8_BIT			(1 << 31)

#define	TCP_CNTW					0x9610
#define	TCP_CHAN_STEEW					0x9614

#define	VC_ENHANCE					0x9714

#define	VGT_CACHE_INVAWIDATION				0x88C4
#define		CACHE_INVAWIDATION(x)				((x)<<0)
#define			VC_ONWY						0
#define			TC_ONWY						1
#define			VC_AND_TC					2
#define		AUTO_INVWD_EN(x)				((x) << 6)
#define			NO_AUTO						0
#define			ES_AUTO						1
#define			GS_AUTO						2
#define			ES_AND_GS_AUTO					3
#define	VGT_ES_PEW_GS					0x88CC
#define	VGT_GS_PEW_ES					0x88C8
#define	VGT_GS_PEW_VS					0x88E8
#define	VGT_GS_VEWTEX_WEUSE				0x88D4
#define	VGT_NUM_INSTANCES				0x8974
#define	VGT_OUT_DEAWWOC_CNTW				0x28C5C
#define		DEAWWOC_DIST_MASK				0x0000007F
#define	VGT_STWMOUT_EN					0x28AB0
#define	VGT_VEWTEX_WEUSE_BWOCK_CNTW			0x28C58
#define		VTX_WEUSE_DEPTH_MASK				0x000000FF

#define VM_CONTEXT0_CNTW				0x1410
#define		ENABWE_CONTEXT					(1 << 0)
#define		PAGE_TABWE_DEPTH(x)				(((x) & 3) << 1)
#define		WANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT		(1 << 4)
#define	VM_CONTEXT0_PAGE_TABWE_BASE_ADDW		0x153C
#define	VM_CONTEXT0_PAGE_TABWE_END_ADDW			0x157C
#define	VM_CONTEXT0_PAGE_TABWE_STAWT_ADDW		0x155C
#define VM_CONTEXT0_PWOTECTION_FAUWT_DEFAUWT_ADDW	0x1518
#define VM_W2_CNTW					0x1400
#define		ENABWE_W2_CACHE					(1 << 0)
#define		ENABWE_W2_FWAGMENT_PWOCESSING			(1 << 1)
#define		ENABWE_W2_PTE_CACHE_WWU_UPDATE_BY_WWITE		(1 << 9)
#define		EFFECTIVE_W2_QUEUE_SIZE(x)			(((x) & 7) << 14)
#define VM_W2_CNTW2					0x1404
#define		INVAWIDATE_AWW_W1_TWBS				(1 << 0)
#define		INVAWIDATE_W2_CACHE				(1 << 1)
#define VM_W2_CNTW3					0x1408
#define		BANK_SEWECT(x)					((x) << 0)
#define		CACHE_UPDATE_MODE(x)				((x) << 6)
#define	VM_W2_STATUS					0x140C
#define		W2_BUSY						(1 << 0)

#define	WAIT_UNTIW					0x8040

/* async DMA */
#define DMA_WB_WPTW                                       0xd008
#define DMA_WB_WPTW                                       0xd00c

/* async DMA packets */
#define DMA_PACKET(cmd, t, s, n)	((((cmd) & 0xF) << 28) |	\
					 (((t) & 0x1) << 23) |		\
					 (((s) & 0x1) << 22) |		\
					 (((n) & 0xFFFF) << 0))
/* async DMA Packet types */
#define	DMA_PACKET_WWITE				  0x2
#define	DMA_PACKET_COPY					  0x3
#define	DMA_PACKET_INDIWECT_BUFFEW			  0x4
#define	DMA_PACKET_SEMAPHOWE				  0x5
#define	DMA_PACKET_FENCE				  0x6
#define	DMA_PACKET_TWAP					  0x7
#define	DMA_PACKET_CONSTANT_FIWW			  0xd
#define	DMA_PACKET_NOP					  0xf


#define	SWBM_STATUS				        0x0E50

/* DCE 3.2 HDMI */
#define HDMI_CONTWOW                         0x7400
#       define HDMI_KEEPOUT_MODE             (1 << 0)
#       define HDMI_PACKET_GEN_VEWSION       (1 << 4) /* 0 = w6xx compat */
#       define HDMI_EWWOW_ACK                (1 << 8)
#       define HDMI_EWWOW_MASK               (1 << 9)
#define HDMI_STATUS                          0x7404
#       define HDMI_ACTIVE_AVMUTE            (1 << 0)
#       define HDMI_AUDIO_PACKET_EWWOW       (1 << 16)
#       define HDMI_VBI_PACKET_EWWOW         (1 << 20)
#define HDMI_AUDIO_PACKET_CONTWOW            0x7408
#       define HDMI_AUDIO_DEWAY_EN(x)        (((x) & 3) << 4)
#       define HDMI_AUDIO_PACKETS_PEW_WINE(x)  (((x) & 0x1f) << 16)
#define HDMI_ACW_PACKET_CONTWOW              0x740c
#       define HDMI_ACW_SEND                 (1 << 0)
#       define HDMI_ACW_CONT                 (1 << 1)
#       define HDMI_ACW_SEWECT(x)            (((x) & 3) << 4)
#       define HDMI_ACW_HW                   0
#       define HDMI_ACW_32                   1
#       define HDMI_ACW_44                   2
#       define HDMI_ACW_48                   3
#       define HDMI_ACW_SOUWCE               (1 << 8) /* 0 - hw; 1 - cts vawue */
#       define HDMI_ACW_AUTO_SEND            (1 << 12)
#define HDMI_VBI_PACKET_CONTWOW              0x7410
#       define HDMI_NUWW_SEND                (1 << 0)
#       define HDMI_GC_SEND                  (1 << 4)
#       define HDMI_GC_CONT                  (1 << 5) /* 0 - once; 1 - evewy fwame */
#define HDMI_INFOFWAME_CONTWOW0              0x7414
#       define HDMI_AVI_INFO_SEND            (1 << 0)
#       define HDMI_AVI_INFO_CONT            (1 << 1)
#       define HDMI_AUDIO_INFO_SEND          (1 << 4)
#       define HDMI_AUDIO_INFO_CONT          (1 << 5)
#       define HDMI_MPEG_INFO_SEND           (1 << 8)
#       define HDMI_MPEG_INFO_CONT           (1 << 9)
#define HDMI_INFOFWAME_CONTWOW1              0x7418
#       define HDMI_AVI_INFO_WINE(x)         (((x) & 0x3f) << 0)
#       define HDMI_AUDIO_INFO_WINE(x)       (((x) & 0x3f) << 8)
#       define HDMI_MPEG_INFO_WINE(x)        (((x) & 0x3f) << 16)
#define HDMI_GENEWIC_PACKET_CONTWOW          0x741c
#       define HDMI_GENEWIC0_SEND            (1 << 0)
#       define HDMI_GENEWIC0_CONT            (1 << 1)
#       define HDMI_GENEWIC1_SEND            (1 << 4)
#       define HDMI_GENEWIC1_CONT            (1 << 5)
#       define HDMI_GENEWIC0_WINE(x)         (((x) & 0x3f) << 16)
#       define HDMI_GENEWIC1_WINE(x)         (((x) & 0x3f) << 24)
#define HDMI_GC                              0x7428
#       define HDMI_GC_AVMUTE                (1 << 0)
#define AFMT_AUDIO_PACKET_CONTWOW2           0x742c
#       define AFMT_AUDIO_WAYOUT_OVWD        (1 << 0)
#       define AFMT_AUDIO_WAYOUT_SEWECT      (1 << 1)
#       define AFMT_60958_CS_SOUWCE          (1 << 4)
#       define AFMT_AUDIO_CHANNEW_ENABWE(x)  (((x) & 0xff) << 8)
#       define AFMT_DP_AUDIO_STWEAM_ID(x)    (((x) & 0xff) << 16)
#define AFMT_AVI_INFO0                       0x7454
#       define AFMT_AVI_INFO_CHECKSUM(x)     (((x) & 0xff) << 0)
#       define AFMT_AVI_INFO_S(x)            (((x) & 3) << 8)
#       define AFMT_AVI_INFO_B(x)            (((x) & 3) << 10)
#       define AFMT_AVI_INFO_A(x)            (((x) & 1) << 12)
#       define AFMT_AVI_INFO_Y(x)            (((x) & 3) << 13)
#       define AFMT_AVI_INFO_Y_WGB           0
#       define AFMT_AVI_INFO_Y_YCBCW422      1
#       define AFMT_AVI_INFO_Y_YCBCW444      2
#       define AFMT_AVI_INFO_Y_A_B_S(x)      (((x) & 0xff) << 8)
#       define AFMT_AVI_INFO_W(x)            (((x) & 0xf) << 16)
#       define AFMT_AVI_INFO_M(x)            (((x) & 0x3) << 20)
#       define AFMT_AVI_INFO_C(x)            (((x) & 0x3) << 22)
#       define AFMT_AVI_INFO_C_M_W(x)        (((x) & 0xff) << 16)
#       define AFMT_AVI_INFO_SC(x)           (((x) & 0x3) << 24)
#       define AFMT_AVI_INFO_Q(x)            (((x) & 0x3) << 26)
#       define AFMT_AVI_INFO_EC(x)           (((x) & 0x3) << 28)
#       define AFMT_AVI_INFO_ITC(x)          (((x) & 0x1) << 31)
#       define AFMT_AVI_INFO_ITC_EC_Q_SC(x)  (((x) & 0xff) << 24)
#define AFMT_AVI_INFO1                       0x7458
#       define AFMT_AVI_INFO_VIC(x)          (((x) & 0x7f) << 0) /* don't use avi infofwame v1 */
#       define AFMT_AVI_INFO_PW(x)           (((x) & 0xf) << 8) /* don't use avi infofwame v1 */
#       define AFMT_AVI_INFO_TOP(x)          (((x) & 0xffff) << 16)
#define AFMT_AVI_INFO2                       0x745c
#       define AFMT_AVI_INFO_BOTTOM(x)       (((x) & 0xffff) << 0)
#       define AFMT_AVI_INFO_WEFT(x)         (((x) & 0xffff) << 16)
#define AFMT_AVI_INFO3                       0x7460
#       define AFMT_AVI_INFO_WIGHT(x)        (((x) & 0xffff) << 0)
#       define AFMT_AVI_INFO_VEWSION(x)      (((x) & 3) << 24)
#define AFMT_MPEG_INFO0                      0x7464
#       define AFMT_MPEG_INFO_CHECKSUM(x)    (((x) & 0xff) << 0)
#       define AFMT_MPEG_INFO_MB0(x)         (((x) & 0xff) << 8)
#       define AFMT_MPEG_INFO_MB1(x)         (((x) & 0xff) << 16)
#       define AFMT_MPEG_INFO_MB2(x)         (((x) & 0xff) << 24)
#define AFMT_MPEG_INFO1                      0x7468
#       define AFMT_MPEG_INFO_MB3(x)         (((x) & 0xff) << 0)
#       define AFMT_MPEG_INFO_MF(x)          (((x) & 3) << 8)
#       define AFMT_MPEG_INFO_FW(x)          (((x) & 1) << 12)
#define AFMT_GENEWIC0_HDW                    0x746c
#define AFMT_GENEWIC0_0                      0x7470
#define AFMT_GENEWIC0_1                      0x7474
#define AFMT_GENEWIC0_2                      0x7478
#define AFMT_GENEWIC0_3                      0x747c
#define AFMT_GENEWIC0_4                      0x7480
#define AFMT_GENEWIC0_5                      0x7484
#define AFMT_GENEWIC0_6                      0x7488
#define AFMT_GENEWIC1_HDW                    0x748c
#define AFMT_GENEWIC1_0                      0x7490
#define AFMT_GENEWIC1_1                      0x7494
#define AFMT_GENEWIC1_2                      0x7498
#define AFMT_GENEWIC1_3                      0x749c
#define AFMT_GENEWIC1_4                      0x74a0
#define AFMT_GENEWIC1_5                      0x74a4
#define AFMT_GENEWIC1_6                      0x74a8
#define HDMI_ACW_32_0                        0x74ac
#       define HDMI_ACW_CTS_32(x)            (((x) & 0xfffff) << 12)
#define HDMI_ACW_32_1                        0x74b0
#       define HDMI_ACW_N_32(x)              (((x) & 0xfffff) << 0)
#define HDMI_ACW_44_0                        0x74b4
#       define HDMI_ACW_CTS_44(x)            (((x) & 0xfffff) << 12)
#define HDMI_ACW_44_1                        0x74b8
#       define HDMI_ACW_N_44(x)              (((x) & 0xfffff) << 0)
#define HDMI_ACW_48_0                        0x74bc
#       define HDMI_ACW_CTS_48(x)            (((x) & 0xfffff) << 12)
#define HDMI_ACW_48_1                        0x74c0
#       define HDMI_ACW_N_48(x)              (((x) & 0xfffff) << 0)
#define HDMI_ACW_STATUS_0                    0x74c4
#define HDMI_ACW_STATUS_1                    0x74c8
#define AFMT_AUDIO_INFO0                     0x74cc
#       define AFMT_AUDIO_INFO_CHECKSUM(x)   (((x) & 0xff) << 0)
#       define AFMT_AUDIO_INFO_CC(x)         (((x) & 7) << 8)
#       define AFMT_AUDIO_INFO_CHECKSUM_OFFSET(x)   (((x) & 0xff) << 16)
#define AFMT_AUDIO_INFO1                     0x74d0
#       define AFMT_AUDIO_INFO_CA(x)         (((x) & 0xff) << 0)
#       define AFMT_AUDIO_INFO_WSV(x)        (((x) & 0xf) << 11)
#       define AFMT_AUDIO_INFO_DM_INH(x)     (((x) & 1) << 15)
#       define AFMT_AUDIO_INFO_DM_INH_WSV(x) (((x) & 0xff) << 8)
#define AFMT_60958_0                         0x74d4
#       define AFMT_60958_CS_A(x)            (((x) & 1) << 0)
#       define AFMT_60958_CS_B(x)            (((x) & 1) << 1)
#       define AFMT_60958_CS_C(x)            (((x) & 1) << 2)
#       define AFMT_60958_CS_D(x)            (((x) & 3) << 3)
#       define AFMT_60958_CS_MODE(x)         (((x) & 3) << 6)
#       define AFMT_60958_CS_CATEGOWY_CODE(x)      (((x) & 0xff) << 8)
#       define AFMT_60958_CS_SOUWCE_NUMBEW(x)      (((x) & 0xf) << 16)
#       define AFMT_60958_CS_CHANNEW_NUMBEW_W(x)   (((x) & 0xf) << 20)
#       define AFMT_60958_CS_SAMPWING_FWEQUENCY(x) (((x) & 0xf) << 24)
#       define AFMT_60958_CS_CWOCK_ACCUWACY(x)     (((x) & 3) << 28)
#define AFMT_60958_1                         0x74d8
#       define AFMT_60958_CS_WOWD_WENGTH(x)  (((x) & 0xf) << 0)
#       define AFMT_60958_CS_OWIGINAW_SAMPWING_FWEQUENCY(x)   (((x) & 0xf) << 4)
#       define AFMT_60958_CS_VAWID_W(x)      (((x) & 1) << 16)
#       define AFMT_60958_CS_VAWID_W(x)      (((x) & 1) << 18)
#       define AFMT_60958_CS_CHANNEW_NUMBEW_W(x)   (((x) & 0xf) << 20)
#define AFMT_AUDIO_CWC_CONTWOW               0x74dc
#       define AFMT_AUDIO_CWC_EN             (1 << 0)
#define AFMT_WAMP_CONTWOW0                   0x74e0
#       define AFMT_WAMP_MAX_COUNT(x)        (((x) & 0xffffff) << 0)
#       define AFMT_WAMP_DATA_SIGN           (1 << 31)
#define AFMT_WAMP_CONTWOW1                   0x74e4
#       define AFMT_WAMP_MIN_COUNT(x)        (((x) & 0xffffff) << 0)
#       define AFMT_AUDIO_TEST_CH_DISABWE(x) (((x) & 0xff) << 24)
#define AFMT_WAMP_CONTWOW2                   0x74e8
#       define AFMT_WAMP_INC_COUNT(x)        (((x) & 0xffffff) << 0)
#define AFMT_WAMP_CONTWOW3                   0x74ec
#       define AFMT_WAMP_DEC_COUNT(x)        (((x) & 0xffffff) << 0)
#define AFMT_60958_2                         0x74f0
#       define AFMT_60958_CS_CHANNEW_NUMBEW_2(x)   (((x) & 0xf) << 0)
#       define AFMT_60958_CS_CHANNEW_NUMBEW_3(x)   (((x) & 0xf) << 4)
#       define AFMT_60958_CS_CHANNEW_NUMBEW_4(x)   (((x) & 0xf) << 8)
#       define AFMT_60958_CS_CHANNEW_NUMBEW_5(x)   (((x) & 0xf) << 12)
#       define AFMT_60958_CS_CHANNEW_NUMBEW_6(x)   (((x) & 0xf) << 16)
#       define AFMT_60958_CS_CHANNEW_NUMBEW_7(x)   (((x) & 0xf) << 20)
#define AFMT_STATUS                          0x7600
#       define AFMT_AUDIO_ENABWE             (1 << 4)
#       define AFMT_AZ_FOWMAT_WTWIG          (1 << 28)
#       define AFMT_AZ_FOWMAT_WTWIG_INT      (1 << 29)
#       define AFMT_AZ_AUDIO_ENABWE_CHG      (1 << 30)
#define AFMT_AUDIO_PACKET_CONTWOW            0x7604
#       define AFMT_AUDIO_SAMPWE_SEND        (1 << 0)
#       define AFMT_AUDIO_TEST_EN            (1 << 12)
#       define AFMT_AUDIO_CHANNEW_SWAP       (1 << 24)
#       define AFMT_60958_CS_UPDATE          (1 << 26)
#       define AFMT_AZ_AUDIO_ENABWE_CHG_MASK (1 << 27)
#       define AFMT_AZ_FOWMAT_WTWIG_MASK     (1 << 28)
#       define AFMT_AZ_FOWMAT_WTWIG_ACK      (1 << 29)
#       define AFMT_AZ_AUDIO_ENABWE_CHG_ACK  (1 << 30)
#define AFMT_VBI_PACKET_CONTWOW              0x7608
#       define AFMT_GENEWIC0_UPDATE          (1 << 2)
#define AFMT_INFOFWAME_CONTWOW0              0x760c
#       define AFMT_AUDIO_INFO_SOUWCE        (1 << 6) /* 0 - sound bwock; 1 - hdmi wegs */
#       define AFMT_AUDIO_INFO_UPDATE        (1 << 7)
#       define AFMT_MPEG_INFO_UPDATE         (1 << 10)
#define AFMT_GENEWIC0_7                      0x7610
/* second instance stawts at 0x7800 */
#define HDMI_OFFSET0                      (0x7400 - 0x7400)
#define HDMI_OFFSET1                      (0x7800 - 0x7400)

/* DCE3.2 EWD audio intewface */
#define AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW0        0x71c8 /* WPCM */
#define AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW1        0x71cc /* AC3 */
#define AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW2        0x71d0 /* MPEG1 */
#define AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW3        0x71d4 /* MP3 */
#define AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW4        0x71d8 /* MPEG2 */
#define AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW5        0x71dc /* AAC */
#define AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW6        0x71e0 /* DTS */
#define AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW7        0x71e4 /* ATWAC */
#define AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW8        0x71e8 /* one bit audio - weave at 0 (defauwt) */
#define AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW9        0x71ec /* Dowby Digitaw */
#define AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW10       0x71f0 /* DTS-HD */
#define AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW11       0x71f4 /* MAT-MWP */
#define AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW12       0x71f8 /* DTS */
#define AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW13       0x71fc /* WMA Pwo */
#       define MAX_CHANNEWS(x)                            (((x) & 0x7) << 0)
/* max channews minus one.  7 = 8 channews */
#       define SUPPOWTED_FWEQUENCIES(x)                   (((x) & 0xff) << 8)
#       define DESCWIPTOW_BYTE_2(x)                       (((x) & 0xff) << 16)
#       define SUPPOWTED_FWEQUENCIES_STEWEO(x)            (((x) & 0xff) << 24) /* WPCM onwy */
/* SUPPOWTED_FWEQUENCIES, SUPPOWTED_FWEQUENCIES_STEWEO
 * bit0 = 32 kHz
 * bit1 = 44.1 kHz
 * bit2 = 48 kHz
 * bit3 = 88.2 kHz
 * bit4 = 96 kHz
 * bit5 = 176.4 kHz
 * bit6 = 192 kHz
 */

#define AZ_HOT_PWUG_CONTWOW                               0x7300
#       define AZ_FOWCE_CODEC_WAKE                        (1 << 0)
#       define PIN0_JACK_DETECTION_ENABWE                 (1 << 4)
#       define PIN1_JACK_DETECTION_ENABWE                 (1 << 5)
#       define PIN2_JACK_DETECTION_ENABWE                 (1 << 6)
#       define PIN3_JACK_DETECTION_ENABWE                 (1 << 7)
#       define PIN0_UNSOWICITED_WESPONSE_ENABWE           (1 << 8)
#       define PIN1_UNSOWICITED_WESPONSE_ENABWE           (1 << 9)
#       define PIN2_UNSOWICITED_WESPONSE_ENABWE           (1 << 10)
#       define PIN3_UNSOWICITED_WESPONSE_ENABWE           (1 << 11)
#       define CODEC_HOT_PWUG_ENABWE                      (1 << 12)
#       define PIN0_AUDIO_ENABWED                         (1 << 24)
#       define PIN1_AUDIO_ENABWED                         (1 << 25)
#       define PIN2_AUDIO_ENABWED                         (1 << 26)
#       define PIN3_AUDIO_ENABWED                         (1 << 27)
#       define AUDIO_ENABWED                              (1 << 31)


#define D1GWPH_PWIMAWY_SUWFACE_ADDWESS                    0x6110
#define D1GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH               0x6914
#define D2GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH               0x6114
#define D1GWPH_SECONDAWY_SUWFACE_ADDWESS                  0x6118
#define D1GWPH_SECONDAWY_SUWFACE_ADDWESS_HIGH             0x691c
#define D2GWPH_SECONDAWY_SUWFACE_ADDWESS_HIGH             0x611c

/* PCIE indiwect wegs */
#define PCIE_P_CNTW                                       0x40
#       define P_PWW_PWWDN_IN_W1W23                       (1 << 3)
#       define P_PWW_BUF_PDNB                             (1 << 4)
#       define P_PWW_PDNB                                 (1 << 9)
#       define P_AWWOW_PWX_FWONTEND_SHUTOFF               (1 << 12)
/* PCIE POWT wegs */
#define PCIE_WC_CNTW                                      0xa0
#       define WC_W0S_INACTIVITY(x)                       ((x) << 8)
#       define WC_W0S_INACTIVITY_MASK                     (0xf << 8)
#       define WC_W0S_INACTIVITY_SHIFT                    8
#       define WC_W1_INACTIVITY(x)                        ((x) << 12)
#       define WC_W1_INACTIVITY_MASK                      (0xf << 12)
#       define WC_W1_INACTIVITY_SHIFT                     12
#       define WC_PMI_TO_W1_DIS                           (1 << 16)
#       define WC_ASPM_TO_W1_DIS                          (1 << 24)
#define PCIE_WC_TWAINING_CNTW                             0xa1 /* PCIE_P */
#define PCIE_WC_WINK_WIDTH_CNTW                           0xa2 /* PCIE_P */
#       define WC_WINK_WIDTH_SHIFT                        0
#       define WC_WINK_WIDTH_MASK                         0x7
#       define WC_WINK_WIDTH_X0                           0
#       define WC_WINK_WIDTH_X1                           1
#       define WC_WINK_WIDTH_X2                           2
#       define WC_WINK_WIDTH_X4                           3
#       define WC_WINK_WIDTH_X8                           4
#       define WC_WINK_WIDTH_X16                          6
#       define WC_WINK_WIDTH_WD_SHIFT                     4
#       define WC_WINK_WIDTH_WD_MASK                      0x70
#       define WC_WECONFIG_AWC_MISSING_ESCAPE             (1 << 7)
#       define WC_WECONFIG_NOW                            (1 << 8)
#       define WC_WENEGOTIATION_SUPPOWT                   (1 << 9)
#       define WC_WENEGOTIATE_EN                          (1 << 10)
#       define WC_SHOWT_WECONFIG_EN                       (1 << 11)
#       define WC_UPCONFIGUWE_SUPPOWT                     (1 << 12)
#       define WC_UPCONFIGUWE_DIS                         (1 << 13)
#define PCIE_WC_SPEED_CNTW                                0xa4 /* PCIE_P */
#       define WC_GEN2_EN_STWAP                           (1 << 0)
#       define WC_TAWGET_WINK_SPEED_OVEWWIDE_EN           (1 << 1)
#       define WC_FOWCE_EN_HW_SPEED_CHANGE                (1 << 5)
#       define WC_FOWCE_DIS_HW_SPEED_CHANGE               (1 << 6)
#       define WC_SPEED_CHANGE_ATTEMPTS_AWWOWED_MASK      (0x3 << 8)
#       define WC_SPEED_CHANGE_ATTEMPTS_AWWOWED_SHIFT     3
#       define WC_CUWWENT_DATA_WATE                       (1 << 11)
#       define WC_HW_VOWTAGE_IF_CONTWOW(x)                ((x) << 12)
#       define WC_HW_VOWTAGE_IF_CONTWOW_MASK              (3 << 12)
#       define WC_HW_VOWTAGE_IF_CONTWOW_SHIFT             12
#       define WC_VOWTAGE_TIMEW_SEW_MASK                  (0xf << 14)
#       define WC_CWW_FAIWED_SPD_CHANGE_CNT               (1 << 21)
#       define WC_OTHEW_SIDE_EVEW_SENT_GEN2               (1 << 23)
#       define WC_OTHEW_SIDE_SUPPOWTS_GEN2                (1 << 24)
#define MM_CFGWEGS_CNTW                                   0x544c
#       define MM_WW_TO_CFG_EN                            (1 << 3)
#define WINK_CNTW2                                        0x88 /* F0 */
#       define TAWGET_WINK_SPEED_MASK                     (0xf << 0)
#       define SEWECTABWE_DEEMPHASIS                      (1 << 6)

/*
 * PM4
 */
#define PACKET0(weg, n)	((WADEON_PACKET_TYPE0 << 30) |			\
			 (((weg) >> 2) & 0xFFFF) |			\
			 ((n) & 0x3FFF) << 16)
#define PACKET3(op, n)	((WADEON_PACKET_TYPE3 << 30) |			\
			 (((op) & 0xFF) << 8) |				\
			 ((n) & 0x3FFF) << 16)

/* UVD */
#define UVD_SEMA_ADDW_WOW				0xef00
#define UVD_SEMA_ADDW_HIGH				0xef04
#define UVD_SEMA_CMD					0xef08
#define UVD_GPCOM_VCPU_CMD				0xef0c
#define UVD_GPCOM_VCPU_DATA0				0xef10
#define UVD_GPCOM_VCPU_DATA1				0xef14

#define UVD_WMI_EXT40_ADDW				0xf498
#define UVD_VCPU_CHIP_ID				0xf4d4
#define UVD_VCPU_CACHE_OFFSET0				0xf4d8
#define UVD_VCPU_CACHE_SIZE0				0xf4dc
#define UVD_VCPU_CACHE_OFFSET1				0xf4e0
#define UVD_VCPU_CACHE_SIZE1				0xf4e4
#define UVD_VCPU_CACHE_OFFSET2				0xf4e8
#define UVD_VCPU_CACHE_SIZE2				0xf4ec
#define UVD_WMI_ADDW_EXT				0xf594

#define UVD_WBC_WB_WPTW					0xf690
#define UVD_WBC_WB_WPTW					0xf694

#define UVD_CONTEXT_ID					0xf6f4

#endif
