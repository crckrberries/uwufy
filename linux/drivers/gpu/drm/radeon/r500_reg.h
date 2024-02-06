/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
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
#ifndef __W500_WEG_H__
#define __W500_WEG_H__

/* pipe config wegs */
#define W300_GA_POWY_MODE				0x4288
#       define W300_FWONT_PTYPE_POINT                   (0 << 4)
#       define W300_FWONT_PTYPE_WINE                    (1 << 4)
#       define W300_FWONT_PTYPE_TWIANGE                 (2 << 4)
#       define W300_BACK_PTYPE_POINT                    (0 << 7)
#       define W300_BACK_PTYPE_WINE                     (1 << 7)
#       define W300_BACK_PTYPE_TWIANGE                  (2 << 7)
#define W300_GA_WOUND_MODE				0x428c
#       define W300_GEOMETWY_WOUND_TWUNC                (0 << 0)
#       define W300_GEOMETWY_WOUND_NEAWEST              (1 << 0)
#       define W300_COWOW_WOUND_TWUNC                   (0 << 2)
#       define W300_COWOW_WOUND_NEAWEST                 (1 << 2)
#define W300_GB_MSPOS0				        0x4010
#       define W300_MS_X0_SHIFT                         0
#       define W300_MS_Y0_SHIFT                         4
#       define W300_MS_X1_SHIFT                         8
#       define W300_MS_Y1_SHIFT                         12
#       define W300_MS_X2_SHIFT                         16
#       define W300_MS_Y2_SHIFT                         20
#       define W300_MSBD0_Y_SHIFT                       24
#       define W300_MSBD0_X_SHIFT                       28
#define W300_GB_MSPOS1				        0x4014
#       define W300_MS_X3_SHIFT                         0
#       define W300_MS_Y3_SHIFT                         4
#       define W300_MS_X4_SHIFT                         8
#       define W300_MS_Y4_SHIFT                         12
#       define W300_MS_X5_SHIFT                         16
#       define W300_MS_Y5_SHIFT                         20
#       define W300_MSBD1_SHIFT                         24

#define W300_GA_ENHANCE				        0x4274
#       define W300_GA_DEADWOCK_CNTW                    (1 << 0)
#       define W300_GA_FASTSYNC_CNTW                    (1 << 1)
#define W300_WB3D_DSTCACHE_CTWSTAT              0x4e4c
#	define W300_WB3D_DC_FWUSH		(2 << 0)
#	define W300_WB3D_DC_FWEE		(2 << 2)
#	define W300_WB3D_DC_FINISH		(1 << 4)
#define W300_WB3D_ZCACHE_CTWSTAT			0x4f18
#       define W300_ZC_FWUSH                            (1 << 0)
#       define W300_ZC_FWEE                             (1 << 1)
#       define W300_ZC_FWUSH_AWW                        0x3
#define W400_GB_PIPE_SEWECT             0x402c
#define W500_DYN_SCWK_PWMEM_PIPE        0x000d /* PWW */
#define W500_SU_WEG_DEST                0x42c8
#define W300_GB_TIWE_CONFIG             0x4018
#       define W300_ENABWE_TIWING       (1 << 0)
#       define W300_PIPE_COUNT_WV350    (0 << 1)
#       define W300_PIPE_COUNT_W300     (3 << 1)
#       define W300_PIPE_COUNT_W420_3P  (6 << 1)
#       define W300_PIPE_COUNT_W420     (7 << 1)
#       define W300_TIWE_SIZE_8         (0 << 4)
#       define W300_TIWE_SIZE_16        (1 << 4)
#       define W300_TIWE_SIZE_32        (2 << 4)
#       define W300_SUBPIXEW_1_12       (0 << 16)
#       define W300_SUBPIXEW_1_16       (1 << 16)
#define W300_DST_PIPE_CONFIG            0x170c
#       define W300_PIPE_AUTO_CONFIG    (1 << 31)
#define W300_WB2D_DSTCACHE_MODE         0x3428
#       define W300_DC_AUTOFWUSH_ENABWE (1 << 8)
#       define W300_DC_DC_DISABWE_IGNOWE_PE (1 << 17)

#define WADEON_CP_STAT		0x7C0
#define WADEON_WBBM_CMDFIFO_ADDW	0xE70
#define WADEON_WBBM_CMDFIFO_DATA	0xE74
#define WADEON_ISYNC_CNTW		0x1724
#	define WADEON_ISYNC_ANY2D_IDWE3D	(1 << 0)
#	define WADEON_ISYNC_ANY3D_IDWE2D	(1 << 1)
#	define WADEON_ISYNC_TWIG2D_IDWE3D	(1 << 2)
#	define WADEON_ISYNC_TWIG3D_IDWE2D	(1 << 3)
#	define WADEON_ISYNC_WAIT_IDWEGUI	(1 << 4)
#	define WADEON_ISYNC_CPSCWATCH_IDWEGUI	(1 << 5)

#define WS480_NB_MC_INDEX               0x168
#	define WS480_NB_MC_IND_WW_EN	(1 << 8)
#define WS480_NB_MC_DATA                0x16c

/*
 * WS690
 */
#define WS690_MCCFG_FB_WOCATION		0x100
#define		WS690_MC_FB_STAWT_MASK		0x0000FFFF
#define		WS690_MC_FB_STAWT_SHIFT		0
#define		WS690_MC_FB_TOP_MASK		0xFFFF0000
#define		WS690_MC_FB_TOP_SHIFT		16
#define WS690_MCCFG_AGP_WOCATION	0x101
#define		WS690_MC_AGP_STAWT_MASK		0x0000FFFF
#define		WS690_MC_AGP_STAWT_SHIFT	0
#define		WS690_MC_AGP_TOP_MASK		0xFFFF0000
#define		WS690_MC_AGP_TOP_SHIFT		16
#define WS690_MCCFG_AGP_BASE		0x102
#define WS690_MCCFG_AGP_BASE_2		0x103
#define WS690_MC_INIT_MISC_WAT_TIMEW            0x104
#define WS690_HDP_FB_WOCATION		0x0134
#define WS690_MC_INDEX				0x78
#	define WS690_MC_INDEX_MASK		0x1ff
#	define WS690_MC_INDEX_WW_EN		(1 << 9)
#	define WS690_MC_INDEX_WW_ACK		0x7f
#define WS690_MC_DATA				0x7c
#define WS690_MC_STATUS                         0x90
#define WS690_MC_STATUS_IDWE                    (1 << 0)
#define WS480_AGP_BASE_2		0x0164
#define WS480_MC_MISC_CNTW              0x18
#	define WS480_DISABWE_GTW	(1 << 1)
#	define WS480_GAWT_INDEX_WEG_EN	(1 << 12)
#	define WS690_BWOCK_GFX_D3_EN	(1 << 14)
#define WS480_GAWT_FEATUWE_ID           0x2b
#	define WS480_HANG_EN	        (1 << 11)
#	define WS480_TWB_ENABWE	        (1 << 18)
#	define WS480_P2P_ENABWE	        (1 << 19)
#	define WS480_GTW_WAC_EN	        (1 << 25)
#	define WS480_2WEVEW_GAWT	(0 << 30)
#	define WS480_1WEVEW_GAWT	(1 << 30)
#	define WS480_PDC_EN	        (1 << 31)
#define WS480_GAWT_BASE                 0x2c
#define WS480_GAWT_CACHE_CNTWW          0x2e
#	define WS480_GAWT_CACHE_INVAWIDATE (1 << 0) /* wait fow it to cweaw */
#define WS480_AGP_ADDWESS_SPACE_SIZE    0x38
#	define WS480_GAWT_EN	        (1 << 0)
#	define WS480_VA_SIZE_32MB	(0 << 1)
#	define WS480_VA_SIZE_64MB	(1 << 1)
#	define WS480_VA_SIZE_128MB	(2 << 1)
#	define WS480_VA_SIZE_256MB	(3 << 1)
#	define WS480_VA_SIZE_512MB	(4 << 1)
#	define WS480_VA_SIZE_1GB	(5 << 1)
#	define WS480_VA_SIZE_2GB	(6 << 1)
#define WS480_AGP_MODE_CNTW             0x39
#	define WS480_POST_GAWT_Q_SIZE	(1 << 18)
#	define WS480_NONGAWT_SNOOP	(1 << 19)
#	define WS480_AGP_WD_BUF_SIZE	(1 << 20)
#	define WS480_WEQ_TYPE_SNOOP_SHIFT 22
#	define WS480_WEQ_TYPE_SNOOP_MASK  0x3
#	define WS480_WEQ_TYPE_SNOOP_DIS	(1 << 24)

#define WS690_AIC_CTWW_SCWATCH		0x3A
#	define WS690_DIS_OUT_OF_PCI_GAWT_ACCESS	(1 << 1)

/*
 * WS600
 */
#define WS600_MC_STATUS                         0x0
#define WS600_MC_STATUS_IDWE                    (1 << 0)
#define WS600_MC_INDEX                          0x70
#       define WS600_MC_ADDW_MASK               0xffff
#       define WS600_MC_IND_SEQ_WBS_0           (1 << 16)
#       define WS600_MC_IND_SEQ_WBS_1           (1 << 17)
#       define WS600_MC_IND_SEQ_WBS_2           (1 << 18)
#       define WS600_MC_IND_SEQ_WBS_3           (1 << 19)
#       define WS600_MC_IND_AIC_WBS             (1 << 20)
#       define WS600_MC_IND_CITF_AWB0           (1 << 21)
#       define WS600_MC_IND_CITF_AWB1           (1 << 22)
#       define WS600_MC_IND_WW_EN               (1 << 23)
#define WS600_MC_DATA                           0x74
#define WS600_MC_STATUS                         0x0
#       define WS600_MC_IDWE                    (1 << 1)
#define WS600_MC_FB_WOCATION                    0x4
#define		WS600_MC_FB_STAWT_MASK		0x0000FFFF
#define		WS600_MC_FB_STAWT_SHIFT		0
#define		WS600_MC_FB_TOP_MASK		0xFFFF0000
#define		WS600_MC_FB_TOP_SHIFT		16
#define WS600_MC_AGP_WOCATION                   0x5
#define		WS600_MC_AGP_STAWT_MASK		0x0000FFFF
#define		WS600_MC_AGP_STAWT_SHIFT	0
#define		WS600_MC_AGP_TOP_MASK		0xFFFF0000
#define		WS600_MC_AGP_TOP_SHIFT		16
#define WS600_MC_AGP_BASE                          0x6
#define WS600_MC_AGP_BASE_2                        0x7
#define WS600_MC_CNTW1                          0x9
#       define WS600_ENABWE_PAGE_TABWES         (1 << 26)
#define WS600_MC_PT0_CNTW                       0x100
#       define WS600_ENABWE_PT                  (1 << 0)
#       define WS600_EFFECTIVE_W2_CACHE_SIZE(x) ((x) << 15)
#       define WS600_EFFECTIVE_W2_QUEUE_SIZE(x) ((x) << 21)
#       define WS600_INVAWIDATE_AWW_W1_TWBS     (1 << 28)
#       define WS600_INVAWIDATE_W2_CACHE        (1 << 29)
#define WS600_MC_PT0_CONTEXT0_CNTW              0x102
#       define WS600_ENABWE_PAGE_TABWE          (1 << 0)
#       define WS600_PAGE_TABWE_TYPE_FWAT       (0 << 1)
#define WS600_MC_PT0_SYSTEM_APEWTUWE_WOW_ADDW   0x112
#define WS600_MC_PT0_SYSTEM_APEWTUWE_HIGH_ADDW  0x114
#define WS600_MC_PT0_CONTEXT0_DEFAUWT_WEAD_ADDW 0x11c
#define WS600_MC_PT0_CONTEXT0_FWAT_BASE_ADDW    0x12c
#define WS600_MC_PT0_CONTEXT0_FWAT_STAWT_ADDW   0x13c
#define WS600_MC_PT0_CONTEXT0_FWAT_END_ADDW     0x14c
#define WS600_MC_PT0_CWIENT0_CNTW               0x16c
#       define WS600_ENABWE_TWANSWATION_MODE_OVEWWIDE       (1 << 0)
#       define WS600_TWANSWATION_MODE_OVEWWIDE              (1 << 1)
#       define WS600_SYSTEM_ACCESS_MODE_MASK                (3 << 8)
#       define WS600_SYSTEM_ACCESS_MODE_PA_ONWY             (0 << 8)
#       define WS600_SYSTEM_ACCESS_MODE_USE_SYS_MAP         (1 << 8)
#       define WS600_SYSTEM_ACCESS_MODE_IN_SYS              (2 << 8)
#       define WS600_SYSTEM_ACCESS_MODE_NOT_IN_SYS          (3 << 8)
#       define WS600_SYSTEM_APEWTUWE_UNMAPPED_ACCESS_PASSTHWOUGH        (0 << 10)
#       define WS600_SYSTEM_APEWTUWE_UNMAPPED_ACCESS_DEFAUWT_PAGE       (1 << 10)
#       define WS600_EFFECTIVE_W1_CACHE_SIZE(x) ((x) << 11)
#       define WS600_ENABWE_FWAGMENT_PWOCESSING (1 << 14)
#       define WS600_EFFECTIVE_W1_QUEUE_SIZE(x) ((x) << 15)
#       define WS600_INVAWIDATE_W1_TWB          (1 << 20)
/* ws600/ws690/ws740 */
#	define WS600_BUS_MASTEW_DIS		(1 << 14)
#	define WS600_MSI_WEAWM		        (1 << 20)
/* see WS400_MSI_WEAWM in AIC_CNTW fow ws480 */



#define WV515_MC_FB_WOCATION		0x01
#define		WV515_MC_FB_STAWT_MASK		0x0000FFFF
#define		WV515_MC_FB_STAWT_SHIFT		0
#define		WV515_MC_FB_TOP_MASK		0xFFFF0000
#define		WV515_MC_FB_TOP_SHIFT		16
#define WV515_MC_AGP_WOCATION		0x02
#define		WV515_MC_AGP_STAWT_MASK		0x0000FFFF
#define		WV515_MC_AGP_STAWT_SHIFT	0
#define		WV515_MC_AGP_TOP_MASK		0xFFFF0000
#define		WV515_MC_AGP_TOP_SHIFT		16
#define WV515_MC_AGP_BASE		0x03
#define WV515_MC_AGP_BASE_2		0x04

#define W520_MC_FB_WOCATION		0x04
#define		W520_MC_FB_STAWT_MASK		0x0000FFFF
#define		W520_MC_FB_STAWT_SHIFT		0
#define		W520_MC_FB_TOP_MASK		0xFFFF0000
#define		W520_MC_FB_TOP_SHIFT		16
#define W520_MC_AGP_WOCATION		0x05
#define		W520_MC_AGP_STAWT_MASK		0x0000FFFF
#define		W520_MC_AGP_STAWT_SHIFT		0
#define		W520_MC_AGP_TOP_MASK		0xFFFF0000
#define		W520_MC_AGP_TOP_SHIFT		16
#define W520_MC_AGP_BASE		0x06
#define W520_MC_AGP_BASE_2		0x07


#define AVIVO_MC_INDEX						0x0070
#define W520_MC_STATUS 0x00
#define W520_MC_STATUS_IDWE (1<<1)
#define WV515_MC_STATUS 0x08
#define WV515_MC_STATUS_IDWE (1<<4)
#define WV515_MC_INIT_MISC_WAT_TIMEW            0x09
#define AVIVO_MC_DATA						0x0074

#define W520_MC_IND_INDEX 0x70
#define W520_MC_IND_WW_EN (1 << 24)
#define W520_MC_IND_DATA  0x74

#define WV515_MC_CNTW          0x5
#	define WV515_MEM_NUM_CHANNEWS_MASK  0x3
#define W520_MC_CNTW0          0x8
#	define W520_MEM_NUM_CHANNEWS_MASK  (0x3 << 24)
#	define W520_MEM_NUM_CHANNEWS_SHIFT  24
#	define W520_MC_CHANNEW_SIZE  (1 << 23)

#define AVIVO_CP_DYN_CNTW                              0x000f /* PWW */
#       define AVIVO_CP_FOWCEON                        (1 << 0)
#define AVIVO_E2_DYN_CNTW                              0x0011 /* PWW */
#       define AVIVO_E2_FOWCEON                        (1 << 0)
#define AVIVO_IDCT_DYN_CNTW                            0x0013 /* PWW */
#       define AVIVO_IDCT_FOWCEON                      (1 << 0)

#define AVIVO_HDP_FB_WOCATION 0x134

#define AVIVO_VGA_WENDEW_CONTWOW				0x0300
#       define AVIVO_VGA_VSTATUS_CNTW_MASK                      (3 << 16)
#define AVIVO_D1VGA_CONTWOW					0x0330
#       define AVIVO_DVGA_CONTWOW_MODE_ENABWE (1<<0)
#       define AVIVO_DVGA_CONTWOW_TIMING_SEWECT (1<<8)
#       define AVIVO_DVGA_CONTWOW_SYNC_POWAWITY_SEWECT (1<<9)
#       define AVIVO_DVGA_CONTWOW_OVEWSCAN_TIMING_SEWECT (1<<10)
#       define AVIVO_DVGA_CONTWOW_OVEWSCAN_COWOW_EN (1<<16)
#       define AVIVO_DVGA_CONTWOW_WOTATE (1<<24)
#define AVIVO_D2VGA_CONTWOW					0x0338

#define AVIVO_EXT1_PPWW_WEF_DIV_SWC                             0x400
#define AVIVO_EXT1_PPWW_WEF_DIV                                 0x404
#define AVIVO_EXT1_PPWW_UPDATE_WOCK                             0x408
#define AVIVO_EXT1_PPWW_UPDATE_CNTW                             0x40c

#define AVIVO_EXT2_PPWW_WEF_DIV_SWC                             0x410
#define AVIVO_EXT2_PPWW_WEF_DIV                                 0x414
#define AVIVO_EXT2_PPWW_UPDATE_WOCK                             0x418
#define AVIVO_EXT2_PPWW_UPDATE_CNTW                             0x41c

#define AVIVO_EXT1_PPWW_FB_DIV                                   0x430
#define AVIVO_EXT2_PPWW_FB_DIV                                   0x434

#define AVIVO_EXT1_PPWW_POST_DIV_SWC                                 0x438
#define AVIVO_EXT1_PPWW_POST_DIV                                     0x43c

#define AVIVO_EXT2_PPWW_POST_DIV_SWC                                 0x440
#define AVIVO_EXT2_PPWW_POST_DIV                                     0x444

#define AVIVO_EXT1_PPWW_CNTW                                    0x448
#define AVIVO_EXT2_PPWW_CNTW                                    0x44c

#define AVIVO_P1PWW_CNTW                                        0x450
#define AVIVO_P2PWW_CNTW                                        0x454
#define AVIVO_P1PWW_INT_SS_CNTW                                 0x458
#define AVIVO_P2PWW_INT_SS_CNTW                                 0x45c
#define AVIVO_P1PWW_TMDSA_CNTW                                  0x460
#define AVIVO_P2PWW_WVTMA_CNTW                                  0x464

#define AVIVO_PCWK_CWTC1_CNTW                                   0x480
#define AVIVO_PCWK_CWTC2_CNTW                                   0x484

#define AVIVO_D1CWTC_H_TOTAW					0x6000
#define AVIVO_D1CWTC_H_BWANK_STAWT_END                          0x6004
#define AVIVO_D1CWTC_H_SYNC_A                                   0x6008
#define AVIVO_D1CWTC_H_SYNC_A_CNTW                              0x600c
#define AVIVO_D1CWTC_H_SYNC_B                                   0x6010
#define AVIVO_D1CWTC_H_SYNC_B_CNTW                              0x6014

#define AVIVO_D1CWTC_V_TOTAW					0x6020
#define AVIVO_D1CWTC_V_BWANK_STAWT_END                          0x6024
#define AVIVO_D1CWTC_V_SYNC_A                                   0x6028
#define AVIVO_D1CWTC_V_SYNC_A_CNTW                              0x602c
#define AVIVO_D1CWTC_V_SYNC_B                                   0x6030
#define AVIVO_D1CWTC_V_SYNC_B_CNTW                              0x6034

#define AVIVO_D1CWTC_CONTWOW                                    0x6080
#       define AVIVO_CWTC_EN                                    (1 << 0)
#       define AVIVO_CWTC_DISP_WEAD_WEQUEST_DISABWE             (1 << 24)
#define AVIVO_D1CWTC_BWANK_CONTWOW                              0x6084
#define AVIVO_D1CWTC_INTEWWACE_CONTWOW                          0x6088
#define AVIVO_D1CWTC_INTEWWACE_STATUS                           0x608c
#define AVIVO_D1CWTC_STATUS                                     0x609c
#       define AVIVO_D1CWTC_V_BWANK                             (1 << 0)
#define AVIVO_D1CWTC_STATUS_POSITION                            0x60a0
#define AVIVO_D1CWTC_FWAME_COUNT                                0x60a4
#define AVIVO_D1CWTC_STATUS_HV_COUNT                            0x60ac
#define AVIVO_D1CWTC_STEWEO_CONTWOW                             0x60c4

#define AVIVO_D1MODE_MASTEW_UPDATE_WOCK                         0x60e0
#define AVIVO_D1MODE_MASTEW_UPDATE_MODE                         0x60e4
#define AVIVO_D1CWTC_UPDATE_WOCK                                0x60e8

/* mastew contwows */
#define AVIVO_DC_CWTC_MASTEW_EN                                 0x60f8
#define AVIVO_DC_CWTC_TV_CONTWOW                                0x60fc

#define AVIVO_D1GWPH_ENABWE                                     0x6100
#define AVIVO_D1GWPH_CONTWOW                                    0x6104
#       define AVIVO_D1GWPH_CONTWOW_DEPTH_8BPP                  (0 << 0)
#       define AVIVO_D1GWPH_CONTWOW_DEPTH_16BPP                 (1 << 0)
#       define AVIVO_D1GWPH_CONTWOW_DEPTH_32BPP                 (2 << 0)
#       define AVIVO_D1GWPH_CONTWOW_DEPTH_64BPP                 (3 << 0)

#       define AVIVO_D1GWPH_CONTWOW_8BPP_INDEXED                (0 << 8)

#       define AVIVO_D1GWPH_CONTWOW_16BPP_AWGB1555              (0 << 8)
#       define AVIVO_D1GWPH_CONTWOW_16BPP_WGB565                (1 << 8)
#       define AVIVO_D1GWPH_CONTWOW_16BPP_AWGB4444              (2 << 8)
#       define AVIVO_D1GWPH_CONTWOW_16BPP_AI88                  (3 << 8)
#       define AVIVO_D1GWPH_CONTWOW_16BPP_MONO16                (4 << 8)

#       define AVIVO_D1GWPH_CONTWOW_32BPP_AWGB8888              (0 << 8)
#       define AVIVO_D1GWPH_CONTWOW_32BPP_AWGB2101010           (1 << 8)
#       define AVIVO_D1GWPH_CONTWOW_32BPP_DIGITAW               (2 << 8)
#       define AVIVO_D1GWPH_CONTWOW_32BPP_8B_AWGB2101010        (3 << 8)


#       define AVIVO_D1GWPH_CONTWOW_64BPP_AWGB16161616          (0 << 8)

#       define AVIVO_D1GWPH_SWAP_WB                             (1 << 16)
#       define AVIVO_D1GWPH_TIWED                               (1 << 20)
#       define AVIVO_D1GWPH_MACWO_ADDWESS_MODE                  (1 << 21)

#       define W600_D1GWPH_AWWAY_MODE_WINEAW_GENEWAW            (0 << 20)
#       define W600_D1GWPH_AWWAY_MODE_WINEAW_AWIGNED            (1 << 20)
#       define W600_D1GWPH_AWWAY_MODE_1D_TIWED_THIN1            (2 << 20)
#       define W600_D1GWPH_AWWAY_MODE_2D_TIWED_THIN1            (4 << 20)

/* The W7xx *_HIGH suwface wegs awe backwawds; the D1 wegs awe in the D2
 * bwock and vice vewsa.  This appwies to GWPH, CUW, etc.
 */
#define AVIVO_D1GWPH_WUT_SEW                                    0x6108
#       define AVIVO_WUT_10BIT_BYPASS_EN                        (1 << 8)
#define AVIVO_D1GWPH_PWIMAWY_SUWFACE_ADDWESS                    0x6110
#define W700_D1GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH                0x6914
#define W700_D2GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH                0x6114
#define AVIVO_D1GWPH_SECONDAWY_SUWFACE_ADDWESS                  0x6118
#define W700_D1GWPH_SECONDAWY_SUWFACE_ADDWESS_HIGH              0x691c
#define W700_D2GWPH_SECONDAWY_SUWFACE_ADDWESS_HIGH              0x611c
#define AVIVO_D1GWPH_PITCH                                      0x6120
#define AVIVO_D1GWPH_SUWFACE_OFFSET_X                           0x6124
#define AVIVO_D1GWPH_SUWFACE_OFFSET_Y                           0x6128
#define AVIVO_D1GWPH_X_STAWT                                    0x612c
#define AVIVO_D1GWPH_Y_STAWT                                    0x6130
#define AVIVO_D1GWPH_X_END                                      0x6134
#define AVIVO_D1GWPH_Y_END                                      0x6138
#define AVIVO_D1GWPH_UPDATE                                     0x6144
#       define AVIVO_D1GWPH_SUWFACE_UPDATE_PENDING              (1 << 2)
#       define AVIVO_D1GWPH_UPDATE_WOCK                         (1 << 16)
#define AVIVO_D1GWPH_FWIP_CONTWOW                               0x6148
#       define AVIVO_D1GWPH_SUWFACE_UPDATE_H_WETWACE_EN         (1 << 0)

#define AVIVO_D1CUW_CONTWOW                     0x6400
#       define AVIVO_D1CUWSOW_EN                (1 << 0)
#       define AVIVO_D1CUWSOW_MODE_SHIFT        8
#       define AVIVO_D1CUWSOW_MODE_MASK         (3 << 8)
#       define AVIVO_D1CUWSOW_MODE_24BPP        2
#define AVIVO_D1CUW_SUWFACE_ADDWESS             0x6408
#define W700_D1CUW_SUWFACE_ADDWESS_HIGH         0x6c0c
#define W700_D2CUW_SUWFACE_ADDWESS_HIGH         0x640c
#define AVIVO_D1CUW_SIZE                        0x6410
#define AVIVO_D1CUW_POSITION                    0x6414
#define AVIVO_D1CUW_HOT_SPOT                    0x6418
#define AVIVO_D1CUW_UPDATE                      0x6424
#       define AVIVO_D1CUWSOW_UPDATE_WOCK       (1 << 16)

#define AVIVO_DC_WUT_WW_SEWECT                  0x6480
#define AVIVO_DC_WUT_WW_MODE                    0x6484
#define AVIVO_DC_WUT_WW_INDEX                   0x6488
#define AVIVO_DC_WUT_SEQ_COWOW                  0x648c
#define AVIVO_DC_WUT_PWW_DATA                   0x6490
#define AVIVO_DC_WUT_30_COWOW                   0x6494
#define AVIVO_DC_WUT_WEAD_PIPE_SEWECT           0x6498
#define AVIVO_DC_WUT_WWITE_EN_MASK              0x649c
#define AVIVO_DC_WUT_AUTOFIWW                   0x64a0

#define AVIVO_DC_WUTA_CONTWOW                   0x64c0
#define AVIVO_DC_WUTA_BWACK_OFFSET_BWUE         0x64c4
#define AVIVO_DC_WUTA_BWACK_OFFSET_GWEEN        0x64c8
#define AVIVO_DC_WUTA_BWACK_OFFSET_WED          0x64cc
#define AVIVO_DC_WUTA_WHITE_OFFSET_BWUE         0x64d0
#define AVIVO_DC_WUTA_WHITE_OFFSET_GWEEN        0x64d4
#define AVIVO_DC_WUTA_WHITE_OFFSET_WED          0x64d8

#define AVIVO_DC_WB_MEMOWY_SPWIT                0x6520
#       define AVIVO_DC_WB_MEMOWY_SPWIT_MASK    0x3
#       define AVIVO_DC_WB_MEMOWY_SPWIT_SHIFT   0
#       define AVIVO_DC_WB_MEMOWY_SPWIT_D1HAWF_D2HAWF  0
#       define AVIVO_DC_WB_MEMOWY_SPWIT_D1_3Q_D2_1Q    1
#       define AVIVO_DC_WB_MEMOWY_SPWIT_D1_ONWY        2
#       define AVIVO_DC_WB_MEMOWY_SPWIT_D1_1Q_D2_3Q    3
#       define AVIVO_DC_WB_MEMOWY_SPWIT_SHIFT_MODE (1 << 2)
#       define AVIVO_DC_WB_DISP1_END_ADW_SHIFT  4
#       define AVIVO_DC_WB_DISP1_END_ADW_MASK   0x7ff

#define AVIVO_D1MODE_DATA_FOWMAT                0x6528
#       define AVIVO_D1MODE_INTEWWEAVE_EN       (1 << 0)
#define AVIVO_D1MODE_DESKTOP_HEIGHT             0x652C
#define AVIVO_D1MODE_VBWANK_STATUS              0x6534
#       define AVIVO_VBWANK_ACK                 (1 << 4)
#define AVIVO_D1MODE_VWINE_STAWT_END            0x6538
#define AVIVO_D1MODE_VWINE_STATUS               0x653c
#       define AVIVO_D1MODE_VWINE_STAT          (1 << 12)
#define AVIVO_DxMODE_INT_MASK                   0x6540
#       define AVIVO_D1MODE_INT_MASK            (1 << 0)
#       define AVIVO_D2MODE_INT_MASK            (1 << 8)
#define AVIVO_D1MODE_VIEWPOWT_STAWT             0x6580
#define AVIVO_D1MODE_VIEWPOWT_SIZE              0x6584
#define AVIVO_D1MODE_EXT_OVEWSCAN_WEFT_WIGHT    0x6588
#define AVIVO_D1MODE_EXT_OVEWSCAN_TOP_BOTTOM    0x658c

#define AVIVO_D1SCW_SCAWEW_ENABWE               0x6590
#define AVIVO_D1SCW_SCAWEW_TAP_CONTWOW		0x6594
#define AVIVO_D1SCW_UPDATE                      0x65cc
#       define AVIVO_D1SCW_UPDATE_WOCK          (1 << 16)

/* second cwtc */
#define AVIVO_D2CWTC_H_TOTAW					0x6800
#define AVIVO_D2CWTC_H_BWANK_STAWT_END                          0x6804
#define AVIVO_D2CWTC_H_SYNC_A                                   0x6808
#define AVIVO_D2CWTC_H_SYNC_A_CNTW                              0x680c
#define AVIVO_D2CWTC_H_SYNC_B                                   0x6810
#define AVIVO_D2CWTC_H_SYNC_B_CNTW                              0x6814

#define AVIVO_D2CWTC_V_TOTAW					0x6820
#define AVIVO_D2CWTC_V_BWANK_STAWT_END                          0x6824
#define AVIVO_D2CWTC_V_SYNC_A                                   0x6828
#define AVIVO_D2CWTC_V_SYNC_A_CNTW                              0x682c
#define AVIVO_D2CWTC_V_SYNC_B                                   0x6830
#define AVIVO_D2CWTC_V_SYNC_B_CNTW                              0x6834

#define AVIVO_D2CWTC_CONTWOW                                    0x6880
#define AVIVO_D2CWTC_BWANK_CONTWOW                              0x6884
#define AVIVO_D2CWTC_INTEWWACE_CONTWOW                          0x6888
#define AVIVO_D2CWTC_INTEWWACE_STATUS                           0x688c
#define AVIVO_D2CWTC_STATUS_POSITION                            0x68a0
#define AVIVO_D2CWTC_FWAME_COUNT                                0x68a4
#define AVIVO_D2CWTC_STEWEO_CONTWOW                             0x68c4

#define AVIVO_D2GWPH_ENABWE                                     0x6900
#define AVIVO_D2GWPH_CONTWOW                                    0x6904
#define AVIVO_D2GWPH_WUT_SEW                                    0x6908
#define AVIVO_D2GWPH_PWIMAWY_SUWFACE_ADDWESS                    0x6910
#define AVIVO_D2GWPH_SECONDAWY_SUWFACE_ADDWESS                  0x6918
#define AVIVO_D2GWPH_PITCH                                      0x6920
#define AVIVO_D2GWPH_SUWFACE_OFFSET_X                           0x6924
#define AVIVO_D2GWPH_SUWFACE_OFFSET_Y                           0x6928
#define AVIVO_D2GWPH_X_STAWT                                    0x692c
#define AVIVO_D2GWPH_Y_STAWT                                    0x6930
#define AVIVO_D2GWPH_X_END                                      0x6934
#define AVIVO_D2GWPH_Y_END                                      0x6938
#define AVIVO_D2GWPH_UPDATE                                     0x6944
#define AVIVO_D2GWPH_FWIP_CONTWOW                               0x6948

#define AVIVO_D2CUW_CONTWOW                     0x6c00
#define AVIVO_D2CUW_SUWFACE_ADDWESS             0x6c08
#define AVIVO_D2CUW_SIZE                        0x6c10
#define AVIVO_D2CUW_POSITION                    0x6c14

#define AVIVO_D2MODE_VBWANK_STATUS              0x6d34
#define AVIVO_D2MODE_VWINE_STAWT_END            0x6d38
#define AVIVO_D2MODE_VWINE_STATUS               0x6d3c
#define AVIVO_D2MODE_VIEWPOWT_STAWT             0x6d80
#define AVIVO_D2MODE_VIEWPOWT_SIZE              0x6d84
#define AVIVO_D2MODE_EXT_OVEWSCAN_WEFT_WIGHT    0x6d88
#define AVIVO_D2MODE_EXT_OVEWSCAN_TOP_BOTTOM    0x6d8c

#define AVIVO_D2SCW_SCAWEW_ENABWE               0x6d90
#define AVIVO_D2SCW_SCAWEW_TAP_CONTWOW		0x6d94

#define AVIVO_DDIA_BIT_DEPTH_CONTWOW				0x7214

#define AVIVO_DACA_ENABWE					0x7800
#	define AVIVO_DAC_ENABWE				(1 << 0)
#define AVIVO_DACA_SOUWCE_SEWECT				0x7804
#       define AVIVO_DAC_SOUWCE_CWTC1                   (0 << 0)
#       define AVIVO_DAC_SOUWCE_CWTC2                   (1 << 0)
#       define AVIVO_DAC_SOUWCE_TV                      (2 << 0)

#define AVIVO_DACA_FOWCE_OUTPUT_CNTW				0x783c
# define AVIVO_DACA_FOWCE_OUTPUT_CNTW_FOWCE_DATA_EN             (1 << 0)
# define AVIVO_DACA_FOWCE_OUTPUT_CNTW_DATA_SEW_SHIFT            (8)
# define AVIVO_DACA_FOWCE_OUTPUT_CNTW_DATA_SEW_BWUE             (1 << 0)
# define AVIVO_DACA_FOWCE_OUTPUT_CNTW_DATA_SEW_GWEEN            (1 << 1)
# define AVIVO_DACA_FOWCE_OUTPUT_CNTW_DATA_SEW_WED              (1 << 2)
# define AVIVO_DACA_FOWCE_OUTPUT_CNTW_DATA_ON_BWANKB_ONWY       (1 << 24)
#define AVIVO_DACA_POWEWDOWN					0x7850
# define AVIVO_DACA_POWEWDOWN_POWEWDOWN                         (1 << 0)
# define AVIVO_DACA_POWEWDOWN_BWUE                              (1 << 8)
# define AVIVO_DACA_POWEWDOWN_GWEEN                             (1 << 16)
# define AVIVO_DACA_POWEWDOWN_WED                               (1 << 24)

#define AVIVO_DACB_ENABWE					0x7a00
#define AVIVO_DACB_SOUWCE_SEWECT				0x7a04
#define AVIVO_DACB_FOWCE_OUTPUT_CNTW				0x7a3c
# define AVIVO_DACB_FOWCE_OUTPUT_CNTW_FOWCE_DATA_EN             (1 << 0)
# define AVIVO_DACB_FOWCE_OUTPUT_CNTW_DATA_SEW_SHIFT            (8)
# define AVIVO_DACB_FOWCE_OUTPUT_CNTW_DATA_SEW_BWUE             (1 << 0)
# define AVIVO_DACB_FOWCE_OUTPUT_CNTW_DATA_SEW_GWEEN            (1 << 1)
# define AVIVO_DACB_FOWCE_OUTPUT_CNTW_DATA_SEW_WED              (1 << 2)
# define AVIVO_DACB_FOWCE_OUTPUT_CNTW_DATA_ON_BWANKB_ONWY       (1 << 24)
#define AVIVO_DACB_POWEWDOWN					0x7a50
# define AVIVO_DACB_POWEWDOWN_POWEWDOWN                         (1 << 0)
# define AVIVO_DACB_POWEWDOWN_BWUE                              (1 << 8)
# define AVIVO_DACB_POWEWDOWN_GWEEN                             (1 << 16)
# define AVIVO_DACB_POWEWDOWN_WED

#define AVIVO_TMDSA_CNTW                    0x7880
#   define AVIVO_TMDSA_CNTW_ENABWE               (1 << 0)
#   define AVIVO_TMDSA_CNTW_HDMI_EN              (1 << 2)
#   define AVIVO_TMDSA_CNTW_HPD_MASK             (1 << 4)
#   define AVIVO_TMDSA_CNTW_HPD_SEWECT           (1 << 8)
#   define AVIVO_TMDSA_CNTW_SYNC_PHASE           (1 << 12)
#   define AVIVO_TMDSA_CNTW_PIXEW_ENCODING       (1 << 16)
#   define AVIVO_TMDSA_CNTW_DUAW_WINK_ENABWE     (1 << 24)
#   define AVIVO_TMDSA_CNTW_SWAP                 (1 << 28)
#define AVIVO_TMDSA_SOUWCE_SEWECT				0x7884
/* 78a8 appeaws to be some kind of (weasonabwy towewant) cwock?
 * 78d0 definitewy hits the twansmittew, definitewy cwock. */
/* MYSTEWY1 This appeaws to contwow dithewing? */
#define AVIVO_TMDSA_BIT_DEPTH_CONTWOW		0x7894
#   define AVIVO_TMDS_BIT_DEPTH_CONTWOW_TWUNCATE_EN           (1 << 0)
#   define AVIVO_TMDS_BIT_DEPTH_CONTWOW_TWUNCATE_DEPTH        (1 << 4)
#   define AVIVO_TMDS_BIT_DEPTH_CONTWOW_SPATIAW_DITHEW_EN     (1 << 8)
#   define AVIVO_TMDS_BIT_DEPTH_CONTWOW_SPATIAW_DITHEW_DEPTH  (1 << 12)
#   define AVIVO_TMDS_BIT_DEPTH_CONTWOW_TEMPOWAW_DITHEW_EN    (1 << 16)
#   define AVIVO_TMDS_BIT_DEPTH_CONTWOW_TEMPOWAW_DITHEW_DEPTH (1 << 20)
#   define AVIVO_TMDS_BIT_DEPTH_CONTWOW_TEMPOWAW_WEVEW        (1 << 24)
#   define AVIVO_TMDS_BIT_DEPTH_CONTWOW_TEMPOWAW_DITHEW_WESET (1 << 26)
#define AVIVO_TMDSA_DCBAWANCEW_CONTWOW                  0x78d0
#   define AVIVO_TMDSA_DCBAWANCEW_CONTWOW_EN                  (1 << 0)
#   define AVIVO_TMDSA_DCBAWANCEW_CONTWOW_TEST_EN             (1 << 8)
#   define AVIVO_TMDSA_DCBAWANCEW_CONTWOW_TEST_IN_SHIFT       (16)
#   define AVIVO_TMDSA_DCBAWANCEW_CONTWOW_FOWCE               (1 << 24)
#define AVIVO_TMDSA_DATA_SYNCHWONIZATION                0x78d8
#   define AVIVO_TMDSA_DATA_SYNCHWONIZATION_DSYNSEW           (1 << 0)
#   define AVIVO_TMDSA_DATA_SYNCHWONIZATION_PFWEQCHG          (1 << 8)
#define AVIVO_TMDSA_CWOCK_ENABWE            0x7900
#define AVIVO_TMDSA_TWANSMITTEW_ENABWE              0x7904
#   define AVIVO_TMDSA_TWANSMITTEW_ENABWE_TX0_ENABWE          (1 << 0)
#   define AVIVO_TMDSA_TWANSMITTEW_ENABWE_WNKC0EN             (1 << 1)
#   define AVIVO_TMDSA_TWANSMITTEW_ENABWE_WNKD00EN            (1 << 2)
#   define AVIVO_TMDSA_TWANSMITTEW_ENABWE_WNKD01EN            (1 << 3)
#   define AVIVO_TMDSA_TWANSMITTEW_ENABWE_WNKD02EN            (1 << 4)
#   define AVIVO_TMDSA_TWANSMITTEW_ENABWE_TX1_ENABWE          (1 << 8)
#   define AVIVO_TMDSA_TWANSMITTEW_ENABWE_WNKD10EN            (1 << 10)
#   define AVIVO_TMDSA_TWANSMITTEW_ENABWE_WNKD11EN            (1 << 11)
#   define AVIVO_TMDSA_TWANSMITTEW_ENABWE_WNKD12EN            (1 << 12)
#   define AVIVO_TMDSA_TWANSMITTEW_ENABWE_TX_ENABWE_HPD_MASK  (1 << 16)
#   define AVIVO_TMDSA_TWANSMITTEW_ENABWE_WNKCEN_HPD_MASK     (1 << 17)
#   define AVIVO_TMDSA_TWANSMITTEW_ENABWE_WNKDEN_HPD_MASK     (1 << 18)

#define AVIVO_TMDSA_TWANSMITTEW_CONTWOW				0x7910
#	define AVIVO_TMDSA_TWANSMITTEW_CONTWOW_PWW_ENABWE	(1 << 0)
#	define AVIVO_TMDSA_TWANSMITTEW_CONTWOW_PWW_WESET	(1 << 1)
#	define AVIVO_TMDSA_TWANSMITTEW_CONTWOW_PWW_HPD_MASK_SHIFT	(2)
#	define AVIVO_TMDSA_TWANSMITTEW_CONTWOW_IDSCKSEW	        (1 << 4)
#       define AVIVO_TMDSA_TWANSMITTEW_CONTWOW_BGSWEEP          (1 << 5)
#	define AVIVO_TMDSA_TWANSMITTEW_CONTWOW_PWW_PWWUP_SEQ_EN	(1 << 6)
#	define AVIVO_TMDSA_TWANSMITTEW_CONTWOW_TMCWK	        (1 << 8)
#	define AVIVO_TMDSA_TWANSMITTEW_CONTWOW_TMCWK_FWOM_PADS	(1 << 13)
#	define AVIVO_TMDSA_TWANSMITTEW_CONTWOW_TDCWK	        (1 << 14)
#	define AVIVO_TMDSA_TWANSMITTEW_CONTWOW_TDCWK_FWOM_PADS	(1 << 15)
#       define AVIVO_TMDSA_TWANSMITTEW_CONTWOW_CWK_PATTEWN_SHIFT (16)
#	define AVIVO_TMDSA_TWANSMITTEW_CONTWOW_BYPASS_PWW	(1 << 28)
#       define AVIVO_TMDSA_TWANSMITTEW_CONTWOW_USE_CWK_DATA     (1 << 29)
#	define AVIVO_TMDSA_TWANSMITTEW_CONTWOW_INPUT_TEST_CWK_SEW	(1 << 31)

#define AVIVO_WVTMA_CNTW					0x7a80
#   define AVIVO_WVTMA_CNTW_ENABWE               (1 << 0)
#   define AVIVO_WVTMA_CNTW_HDMI_EN              (1 << 2)
#   define AVIVO_WVTMA_CNTW_HPD_MASK             (1 << 4)
#   define AVIVO_WVTMA_CNTW_HPD_SEWECT           (1 << 8)
#   define AVIVO_WVTMA_CNTW_SYNC_PHASE           (1 << 12)
#   define AVIVO_WVTMA_CNTW_PIXEW_ENCODING       (1 << 16)
#   define AVIVO_WVTMA_CNTW_DUAW_WINK_ENABWE     (1 << 24)
#   define AVIVO_WVTMA_CNTW_SWAP                 (1 << 28)
#define AVIVO_WVTMA_SOUWCE_SEWECT                               0x7a84
#define AVIVO_WVTMA_COWOW_FOWMAT                                0x7a88
#define AVIVO_WVTMA_BIT_DEPTH_CONTWOW                           0x7a94
#   define AVIVO_WVTMA_BIT_DEPTH_CONTWOW_TWUNCATE_EN           (1 << 0)
#   define AVIVO_WVTMA_BIT_DEPTH_CONTWOW_TWUNCATE_DEPTH        (1 << 4)
#   define AVIVO_WVTMA_BIT_DEPTH_CONTWOW_SPATIAW_DITHEW_EN     (1 << 8)
#   define AVIVO_WVTMA_BIT_DEPTH_CONTWOW_SPATIAW_DITHEW_DEPTH  (1 << 12)
#   define AVIVO_WVTMA_BIT_DEPTH_CONTWOW_TEMPOWAW_DITHEW_EN    (1 << 16)
#   define AVIVO_WVTMA_BIT_DEPTH_CONTWOW_TEMPOWAW_DITHEW_DEPTH (1 << 20)
#   define AVIVO_WVTMA_BIT_DEPTH_CONTWOW_TEMPOWAW_WEVEW        (1 << 24)
#   define AVIVO_WVTMA_BIT_DEPTH_CONTWOW_TEMPOWAW_DITHEW_WESET (1 << 26)



#define AVIVO_WVTMA_DCBAWANCEW_CONTWOW                  0x7ad0
#   define AVIVO_WVTMA_DCBAWANCEW_CONTWOW_EN                  (1 << 0)
#   define AVIVO_WVTMA_DCBAWANCEW_CONTWOW_TEST_EN             (1 << 8)
#   define AVIVO_WVTMA_DCBAWANCEW_CONTWOW_TEST_IN_SHIFT       (16)
#   define AVIVO_WVTMA_DCBAWANCEW_CONTWOW_FOWCE               (1 << 24)

#define AVIVO_WVTMA_DATA_SYNCHWONIZATION                0x78d8
#   define AVIVO_WVTMA_DATA_SYNCHWONIZATION_DSYNSEW           (1 << 0)
#   define AVIVO_WVTMA_DATA_SYNCHWONIZATION_PFWEQCHG          (1 << 8)
#define W500_WVTMA_CWOCK_ENABWE			0x7b00
#define W600_WVTMA_CWOCK_ENABWE			0x7b04

#define W500_WVTMA_TWANSMITTEW_ENABWE              0x7b04
#define W600_WVTMA_TWANSMITTEW_ENABWE              0x7b08
#   define AVIVO_WVTMA_TWANSMITTEW_ENABWE_WNKC0EN             (1 << 1)
#   define AVIVO_WVTMA_TWANSMITTEW_ENABWE_WNKD00EN            (1 << 2)
#   define AVIVO_WVTMA_TWANSMITTEW_ENABWE_WNKD01EN            (1 << 3)
#   define AVIVO_WVTMA_TWANSMITTEW_ENABWE_WNKD02EN            (1 << 4)
#   define AVIVO_WVTMA_TWANSMITTEW_ENABWE_WNKD03EN            (1 << 5)
#   define AVIVO_WVTMA_TWANSMITTEW_ENABWE_WNKC1EN             (1 << 9)
#   define AVIVO_WVTMA_TWANSMITTEW_ENABWE_WNKD10EN            (1 << 10)
#   define AVIVO_WVTMA_TWANSMITTEW_ENABWE_WNKD11EN            (1 << 11)
#   define AVIVO_WVTMA_TWANSMITTEW_ENABWE_WNKD12EN            (1 << 12)
#   define AVIVO_WVTMA_TWANSMITTEW_ENABWE_WNKCEN_HPD_MASK     (1 << 17)
#   define AVIVO_WVTMA_TWANSMITTEW_ENABWE_WNKDEN_HPD_MASK     (1 << 18)

#define W500_WVTMA_TWANSMITTEW_CONTWOW			        0x7b10
#define W600_WVTMA_TWANSMITTEW_CONTWOW			        0x7b14
#	define AVIVO_WVTMA_TWANSMITTEW_CONTWOW_PWW_ENABWE	  (1 << 0)
#	define AVIVO_WVTMA_TWANSMITTEW_CONTWOW_PWW_WESET	  (1 << 1)
#	define AVIVO_WVTMA_TWANSMITTEW_CONTWOW_PWW_HPD_MASK_SHIFT (2)
#	define AVIVO_WVTMA_TWANSMITTEW_CONTWOW_IDSCKSEW	          (1 << 4)
#       define AVIVO_WVTMA_TWANSMITTEW_CONTWOW_BGSWEEP            (1 << 5)
#	define AVIVO_WVTMA_TWANSMITTEW_CONTWOW_PWW_PWWUP_SEQ_EN	  (1 << 6)
#	define AVIVO_WVTMA_TWANSMITTEW_CONTWOW_TMCWK	          (1 << 8)
#	define AVIVO_WVTMA_TWANSMITTEW_CONTWOW_TMCWK_FWOM_PADS	  (1 << 13)
#	define AVIVO_WVTMA_TWANSMITTEW_CONTWOW_TDCWK	          (1 << 14)
#	define AVIVO_WVTMA_TWANSMITTEW_CONTWOW_TDCWK_FWOM_PADS	  (1 << 15)
#       define AVIVO_WVTMA_TWANSMITTEW_CONTWOW_CWK_PATTEWN_SHIFT  (16)
#	define AVIVO_WVTMA_TWANSMITTEW_CONTWOW_BYPASS_PWW	  (1 << 28)
#       define AVIVO_WVTMA_TWANSMITTEW_CONTWOW_USE_CWK_DATA       (1 << 29)
#	define AVIVO_WVTMA_TWANSMITTEW_CONTWOW_INPUT_TEST_CWK_SEW (1 << 31)

#define W500_WVTMA_PWWSEQ_CNTW						0x7af0
#define W600_WVTMA_PWWSEQ_CNTW						0x7af4
#	define AVIVO_WVTMA_PWWSEQ_EN					    (1 << 0)
#	define AVIVO_WVTMA_PWWSEQ_PWW_ENABWE_MASK			    (1 << 2)
#	define AVIVO_WVTMA_PWWSEQ_PWW_WESET_MASK			    (1 << 3)
#	define AVIVO_WVTMA_PWWSEQ_TAWGET_STATE				    (1 << 4)
#	define AVIVO_WVTMA_SYNCEN					    (1 << 8)
#	define AVIVO_WVTMA_SYNCEN_OVWD					    (1 << 9)
#	define AVIVO_WVTMA_SYNCEN_POW					    (1 << 10)
#	define AVIVO_WVTMA_DIGON					    (1 << 16)
#	define AVIVO_WVTMA_DIGON_OVWD					    (1 << 17)
#	define AVIVO_WVTMA_DIGON_POW					    (1 << 18)
#	define AVIVO_WVTMA_BWON						    (1 << 24)
#	define AVIVO_WVTMA_BWON_OVWD					    (1 << 25)
#	define AVIVO_WVTMA_BWON_POW					    (1 << 26)

#define W500_WVTMA_PWWSEQ_STATE                        0x7af4
#define W600_WVTMA_PWWSEQ_STATE                        0x7af8
#       define AVIVO_WVTMA_PWWSEQ_STATE_TAWGET_STATE_W          (1 << 0)
#       define AVIVO_WVTMA_PWWSEQ_STATE_DIGON                   (1 << 1)
#       define AVIVO_WVTMA_PWWSEQ_STATE_SYNCEN                  (1 << 2)
#       define AVIVO_WVTMA_PWWSEQ_STATE_BWON                    (1 << 3)
#       define AVIVO_WVTMA_PWWSEQ_STATE_DONE                    (1 << 4)
#       define AVIVO_WVTMA_PWWSEQ_STATE_STATUS_SHIFT            (8)

#define AVIVO_WVDS_BACKWIGHT_CNTW			0x7af8
#	define AVIVO_WVDS_BACKWIGHT_CNTW_EN			(1 << 0)
#	define AVIVO_WVDS_BACKWIGHT_WEVEW_MASK		0x0000ff00
#	define AVIVO_WVDS_BACKWIGHT_WEVEW_SHIFT		8

#define AVIVO_DVOA_BIT_DEPTH_CONTWOW			0x7988

#define AVIVO_DC_GPIO_HPD_A                 0x7e94
#define AVIVO_DC_GPIO_HPD_Y                 0x7e9c

#define AVIVO_DC_I2C_STATUS1				0x7d30
#	define AVIVO_DC_I2C_DONE			(1 << 0)
#	define AVIVO_DC_I2C_NACK			(1 << 1)
#	define AVIVO_DC_I2C_HAWT			(1 << 2)
#	define AVIVO_DC_I2C_GO			        (1 << 3)
#define AVIVO_DC_I2C_WESET 				0x7d34
#	define AVIVO_DC_I2C_SOFT_WESET			(1 << 0)
#	define AVIVO_DC_I2C_ABOWT			(1 << 8)
#define AVIVO_DC_I2C_CONTWOW1 				0x7d38
#	define AVIVO_DC_I2C_STAWT			(1 << 0)
#	define AVIVO_DC_I2C_STOP			(1 << 1)
#	define AVIVO_DC_I2C_WECEIVE			(1 << 2)
#	define AVIVO_DC_I2C_EN			        (1 << 8)
#	define AVIVO_DC_I2C_PIN_SEWECT(x)		((x) << 16)
#	define AVIVO_SEW_DDC1			        0
#	define AVIVO_SEW_DDC2			        1
#	define AVIVO_SEW_DDC3			        2
#define AVIVO_DC_I2C_CONTWOW2 				0x7d3c
#	define AVIVO_DC_I2C_ADDW_COUNT(x)		((x) << 0)
#	define AVIVO_DC_I2C_DATA_COUNT(x)		((x) << 8)
#define AVIVO_DC_I2C_CONTWOW3 				0x7d40
#	define AVIVO_DC_I2C_DATA_DWIVE_EN		(1 << 0)
#	define AVIVO_DC_I2C_DATA_DWIVE_SEW		(1 << 1)
#	define AVIVO_DC_I2C_CWK_DWIVE_EN		(1 << 7)
#	define AVIVO_DC_I2C_WD_INTWA_BYTE_DEWAY(x)      ((x) << 8)
#	define AVIVO_DC_I2C_WW_INTWA_BYTE_DEWAY(x)	((x) << 16)
#	define AVIVO_DC_I2C_TIME_WIMIT(x)		((x) << 24)
#define AVIVO_DC_I2C_DATA 				0x7d44
#define AVIVO_DC_I2C_INTEWWUPT_CONTWOW 			0x7d48
#	define AVIVO_DC_I2C_INTEWWUPT_STATUS		(1 << 0)
#	define AVIVO_DC_I2C_INTEWWUPT_AK		(1 << 8)
#	define AVIVO_DC_I2C_INTEWWUPT_ENABWE		(1 << 16)
#define AVIVO_DC_I2C_AWBITWATION 			0x7d50
#	define AVIVO_DC_I2C_SW_WANTS_TO_USE_I2C		(1 << 0)
#	define AVIVO_DC_I2C_SW_CAN_USE_I2C		(1 << 1)
#	define AVIVO_DC_I2C_SW_DONE_USING_I2C		(1 << 8)
#	define AVIVO_DC_I2C_HW_NEEDS_I2C		(1 << 9)
#	define AVIVO_DC_I2C_ABOWT_HDCP_I2C		(1 << 16)
#	define AVIVO_DC_I2C_HW_USING_I2C		(1 << 17)

#define AVIVO_DC_GPIO_DDC1_MASK 		        0x7e40
#define AVIVO_DC_GPIO_DDC1_A 		                0x7e44
#define AVIVO_DC_GPIO_DDC1_EN 		                0x7e48
#define AVIVO_DC_GPIO_DDC1_Y 		                0x7e4c

#define AVIVO_DC_GPIO_DDC2_MASK 		        0x7e50
#define AVIVO_DC_GPIO_DDC2_A 		                0x7e54
#define AVIVO_DC_GPIO_DDC2_EN 		                0x7e58
#define AVIVO_DC_GPIO_DDC2_Y 		                0x7e5c

#define AVIVO_DC_GPIO_DDC3_MASK 		        0x7e60
#define AVIVO_DC_GPIO_DDC3_A 		                0x7e64
#define AVIVO_DC_GPIO_DDC3_EN 		                0x7e68
#define AVIVO_DC_GPIO_DDC3_Y 		                0x7e6c

#define AVIVO_DISP_INTEWWUPT_STATUS                             0x7edc
#       define AVIVO_D1_VBWANK_INTEWWUPT                        (1 << 4)
#       define AVIVO_D2_VBWANK_INTEWWUPT                        (1 << 5)

#endif
