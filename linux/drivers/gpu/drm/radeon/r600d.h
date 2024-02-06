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
#ifndef W600D_H
#define W600D_H

#define CP_PACKET2			0x80000000
#define		PACKET2_PAD_SHIFT		0
#define		PACKET2_PAD_MASK		(0x3fffffff << 0)

#define PACKET2(v)	(CP_PACKET2 | WEG_SET(PACKET2_PAD, (v)))

#define W6XX_MAX_SH_GPWS			256
#define W6XX_MAX_TEMP_GPWS			16
#define W6XX_MAX_SH_THWEADS			256
#define W6XX_MAX_SH_STACK_ENTWIES		4096
#define W6XX_MAX_BACKENDS			8
#define W6XX_MAX_BACKENDS_MASK			0xff
#define W6XX_MAX_SIMDS				8
#define W6XX_MAX_SIMDS_MASK			0xff
#define W6XX_MAX_PIPES				8
#define W6XX_MAX_PIPES_MASK			0xff

/* tiwing bits */
#define     AWWAY_WINEAW_GENEWAW              0x00000000
#define     AWWAY_WINEAW_AWIGNED              0x00000001
#define     AWWAY_1D_TIWED_THIN1              0x00000002
#define     AWWAY_2D_TIWED_THIN1              0x00000004

/* Wegistews */
#define	AWB_POP						0x2418
#define 	ENABWE_TC128					(1 << 30)
#define	AWB_GDEC_WD_CNTW				0x246C

#define	CC_GC_SHADEW_PIPE_CONFIG			0x8950
#define	CC_WB_BACKEND_DISABWE				0x98F4
#define		BACKEND_DISABWE(x)				((x) << 16)

#define W_028808_CB_COWOW_CONTWOW			0x28808
#define   S_028808_SPECIAW_OP(x)                       (((x) & 0x7) << 4)
#define   G_028808_SPECIAW_OP(x)                       (((x) >> 4) & 0x7)
#define   C_028808_SPECIAW_OP                          0xFFFFFF8F
#define     V_028808_SPECIAW_NOWMAW                     0x00
#define     V_028808_SPECIAW_DISABWE                    0x01
#define     V_028808_SPECIAW_WESOWVE_BOX                0x07

#define	CB_COWOW0_BASE					0x28040
#define	CB_COWOW1_BASE					0x28044
#define	CB_COWOW2_BASE					0x28048
#define	CB_COWOW3_BASE					0x2804C
#define	CB_COWOW4_BASE					0x28050
#define	CB_COWOW5_BASE					0x28054
#define	CB_COWOW6_BASE					0x28058
#define	CB_COWOW7_BASE					0x2805C
#define	CB_COWOW7_FWAG					0x280FC

#define CB_COWOW0_SIZE                                  0x28060
#define CB_COWOW0_VIEW                                  0x28080
#define W_028080_CB_COWOW0_VIEW                      0x028080
#define   S_028080_SWICE_STAWT(x)                      (((x) & 0x7FF) << 0)
#define   G_028080_SWICE_STAWT(x)                      (((x) >> 0) & 0x7FF)
#define   C_028080_SWICE_STAWT                         0xFFFFF800
#define   S_028080_SWICE_MAX(x)                        (((x) & 0x7FF) << 13)
#define   G_028080_SWICE_MAX(x)                        (((x) >> 13) & 0x7FF)
#define   C_028080_SWICE_MAX                           0xFF001FFF
#define W_028084_CB_COWOW1_VIEW                      0x028084
#define W_028088_CB_COWOW2_VIEW                      0x028088
#define W_02808C_CB_COWOW3_VIEW                      0x02808C
#define W_028090_CB_COWOW4_VIEW                      0x028090
#define W_028094_CB_COWOW5_VIEW                      0x028094
#define W_028098_CB_COWOW6_VIEW                      0x028098
#define W_02809C_CB_COWOW7_VIEW                      0x02809C
#define W_028100_CB_COWOW0_MASK                      0x028100
#define   S_028100_CMASK_BWOCK_MAX(x)                  (((x) & 0xFFF) << 0)
#define   G_028100_CMASK_BWOCK_MAX(x)                  (((x) >> 0) & 0xFFF)
#define   C_028100_CMASK_BWOCK_MAX                     0xFFFFF000
#define   S_028100_FMASK_TIWE_MAX(x)                   (((x) & 0xFFFFF) << 12)
#define   G_028100_FMASK_TIWE_MAX(x)                   (((x) >> 12) & 0xFFFFF)
#define   C_028100_FMASK_TIWE_MAX                      0x00000FFF
#define W_028104_CB_COWOW1_MASK                      0x028104
#define W_028108_CB_COWOW2_MASK                      0x028108
#define W_02810C_CB_COWOW3_MASK                      0x02810C
#define W_028110_CB_COWOW4_MASK                      0x028110
#define W_028114_CB_COWOW5_MASK                      0x028114
#define W_028118_CB_COWOW6_MASK                      0x028118
#define W_02811C_CB_COWOW7_MASK                      0x02811C
#define CB_COWOW0_INFO                                  0x280a0
#	define CB_FOWMAT(x)				((x) << 2)
#       define CB_AWWAY_MODE(x)                         ((x) << 8)
#	define CB_SOUWCE_FOWMAT(x)			((x) << 27)
#	define CB_SF_EXPOWT_FUWW			0
#	define CB_SF_EXPOWT_NOWM			1
#define CB_COWOW0_TIWE                                  0x280c0
#define CB_COWOW0_FWAG                                  0x280e0
#define CB_COWOW0_MASK                                  0x28100

#define SQ_AWU_CONST_CACHE_PS_0				0x28940
#define SQ_AWU_CONST_CACHE_PS_1				0x28944
#define SQ_AWU_CONST_CACHE_PS_2				0x28948
#define SQ_AWU_CONST_CACHE_PS_3				0x2894c
#define SQ_AWU_CONST_CACHE_PS_4				0x28950
#define SQ_AWU_CONST_CACHE_PS_5				0x28954
#define SQ_AWU_CONST_CACHE_PS_6				0x28958
#define SQ_AWU_CONST_CACHE_PS_7				0x2895c
#define SQ_AWU_CONST_CACHE_PS_8				0x28960
#define SQ_AWU_CONST_CACHE_PS_9				0x28964
#define SQ_AWU_CONST_CACHE_PS_10			0x28968
#define SQ_AWU_CONST_CACHE_PS_11			0x2896c
#define SQ_AWU_CONST_CACHE_PS_12			0x28970
#define SQ_AWU_CONST_CACHE_PS_13			0x28974
#define SQ_AWU_CONST_CACHE_PS_14			0x28978
#define SQ_AWU_CONST_CACHE_PS_15			0x2897c
#define SQ_AWU_CONST_CACHE_VS_0				0x28980
#define SQ_AWU_CONST_CACHE_VS_1				0x28984
#define SQ_AWU_CONST_CACHE_VS_2				0x28988
#define SQ_AWU_CONST_CACHE_VS_3				0x2898c
#define SQ_AWU_CONST_CACHE_VS_4				0x28990
#define SQ_AWU_CONST_CACHE_VS_5				0x28994
#define SQ_AWU_CONST_CACHE_VS_6				0x28998
#define SQ_AWU_CONST_CACHE_VS_7				0x2899c
#define SQ_AWU_CONST_CACHE_VS_8				0x289a0
#define SQ_AWU_CONST_CACHE_VS_9				0x289a4
#define SQ_AWU_CONST_CACHE_VS_10			0x289a8
#define SQ_AWU_CONST_CACHE_VS_11			0x289ac
#define SQ_AWU_CONST_CACHE_VS_12			0x289b0
#define SQ_AWU_CONST_CACHE_VS_13			0x289b4
#define SQ_AWU_CONST_CACHE_VS_14			0x289b8
#define SQ_AWU_CONST_CACHE_VS_15			0x289bc
#define SQ_AWU_CONST_CACHE_GS_0				0x289c0
#define SQ_AWU_CONST_CACHE_GS_1				0x289c4
#define SQ_AWU_CONST_CACHE_GS_2				0x289c8
#define SQ_AWU_CONST_CACHE_GS_3				0x289cc
#define SQ_AWU_CONST_CACHE_GS_4				0x289d0
#define SQ_AWU_CONST_CACHE_GS_5				0x289d4
#define SQ_AWU_CONST_CACHE_GS_6				0x289d8
#define SQ_AWU_CONST_CACHE_GS_7				0x289dc
#define SQ_AWU_CONST_CACHE_GS_8				0x289e0
#define SQ_AWU_CONST_CACHE_GS_9				0x289e4
#define SQ_AWU_CONST_CACHE_GS_10			0x289e8
#define SQ_AWU_CONST_CACHE_GS_11			0x289ec
#define SQ_AWU_CONST_CACHE_GS_12			0x289f0
#define SQ_AWU_CONST_CACHE_GS_13			0x289f4
#define SQ_AWU_CONST_CACHE_GS_14			0x289f8
#define SQ_AWU_CONST_CACHE_GS_15			0x289fc

#define	CONFIG_MEMSIZE					0x5428
#define CONFIG_CNTW					0x5424
#define	CP_STAWWED_STAT1			0x8674
#define	CP_STAWWED_STAT2			0x8678
#define	CP_BUSY_STAT				0x867C
#define	CP_STAT						0x8680
#define	CP_COHEW_BASE					0x85F8
#define	CP_DEBUG					0xC1FC
#define	W_0086D8_CP_ME_CNTW			0x86D8
#define		S_0086D8_CP_PFP_HAWT(x)			(((x) & 1)<<26)
#define		C_0086D8_CP_PFP_HAWT(x)			((x) & 0xFBFFFFFF)
#define		S_0086D8_CP_ME_HAWT(x)			(((x) & 1)<<28)
#define		C_0086D8_CP_ME_HAWT(x)			((x) & 0xEFFFFFFF)
#define	CP_ME_WAM_DATA					0xC160
#define	CP_ME_WAM_WADDW					0xC158
#define	CP_ME_WAM_WADDW					0xC15C
#define CP_MEQ_THWESHOWDS				0x8764
#define		MEQ_END(x)					((x) << 16)
#define		WOQ_END(x)					((x) << 24)
#define	CP_PEWFMON_CNTW					0x87FC
#define	CP_PFP_UCODE_ADDW				0xC150
#define	CP_PFP_UCODE_DATA				0xC154
#define	CP_QUEUE_THWESHOWDS				0x8760
#define		WOQ_IB1_STAWT(x)				((x) << 0)
#define		WOQ_IB2_STAWT(x)				((x) << 8)
#define	CP_WB_BASE					0xC100
#define	CP_WB_CNTW					0xC104
#define		WB_BUFSZ(x)					((x) << 0)
#define		WB_BWKSZ(x)					((x) << 8)
#define		WB_NO_UPDATE					(1 << 27)
#define		WB_WPTW_WW_ENA					(1 << 31)
#define		BUF_SWAP_32BIT					(2 << 16)
#define	CP_WB_WPTW					0x8700
#define	CP_WB_WPTW_ADDW					0xC10C
#define		WB_WPTW_SWAP(x)					((x) << 0)
#define	CP_WB_WPTW_ADDW_HI				0xC110
#define	CP_WB_WPTW_WW					0xC108
#define	CP_WB_WPTW					0xC114
#define	CP_WB_WPTW_ADDW					0xC118
#define	CP_WB_WPTW_ADDW_HI				0xC11C
#define	CP_WB_WPTW_DEWAY				0x8704
#define	CP_WOQ_IB1_STAT					0x8784
#define	CP_WOQ_IB2_STAT					0x8788
#define	CP_SEM_WAIT_TIMEW				0x85BC

#define	DB_DEBUG					0x9830
#define		PWEZ_MUST_WAIT_FOW_POSTZ_DONE			(1 << 31)
#define	DB_DEPTH_BASE					0x2800C
#define	DB_HTIWE_DATA_BASE				0x28014
#define	DB_HTIWE_SUWFACE				0x28D24
#define   S_028D24_HTIWE_WIDTH(x)                      (((x) & 0x1) << 0)
#define   G_028D24_HTIWE_WIDTH(x)                      (((x) >> 0) & 0x1)
#define   C_028D24_HTIWE_WIDTH                         0xFFFFFFFE
#define   S_028D24_HTIWE_HEIGHT(x)                      (((x) & 0x1) << 1)
#define   G_028D24_HTIWE_HEIGHT(x)                      (((x) >> 1) & 0x1)
#define   C_028D24_HTIWE_HEIGHT                         0xFFFFFFFD
#define   G_028D24_WINEAW(x)                           (((x) >> 2) & 0x1)
#define	DB_WATEWMAWKS					0x9838
#define		DEPTH_FWEE(x)					((x) << 0)
#define		DEPTH_FWUSH(x)					((x) << 5)
#define		DEPTH_PENDING_FWEE(x)				((x) << 15)
#define		DEPTH_CACHEWINE_FWEE(x)				((x) << 20)

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

#define	GC_USEW_SHADEW_PIPE_CONFIG			0x8954
#define		INACTIVE_QD_PIPES(x)				((x) << 8)
#define		INACTIVE_QD_PIPES_MASK				0x0000FF00
#define		INACTIVE_SIMDS(x)				((x) << 16)
#define		INACTIVE_SIMDS_MASK				0x00FF0000

#define SQ_CONFIG                                         0x8c00
#       define VC_ENABWE                                  (1 << 0)
#       define EXPOWT_SWC_C                               (1 << 1)
#       define DX9_CONSTS                                 (1 << 2)
#       define AWU_INST_PWEFEW_VECTOW                     (1 << 3)
#       define DX10_CWAMP                                 (1 << 4)
#       define CWAUSE_SEQ_PWIO(x)                         ((x) << 8)
#       define PS_PWIO(x)                                 ((x) << 24)
#       define VS_PWIO(x)                                 ((x) << 26)
#       define GS_PWIO(x)                                 ((x) << 28)
#       define ES_PWIO(x)                                 ((x) << 30)
#define SQ_GPW_WESOUWCE_MGMT_1                            0x8c04
#       define NUM_PS_GPWS(x)                             ((x) << 0)
#       define NUM_VS_GPWS(x)                             ((x) << 16)
#       define NUM_CWAUSE_TEMP_GPWS(x)                    ((x) << 28)
#define SQ_GPW_WESOUWCE_MGMT_2                            0x8c08
#       define NUM_GS_GPWS(x)                             ((x) << 0)
#       define NUM_ES_GPWS(x)                             ((x) << 16)
#define SQ_THWEAD_WESOUWCE_MGMT                           0x8c0c
#       define NUM_PS_THWEADS(x)                          ((x) << 0)
#       define NUM_VS_THWEADS(x)                          ((x) << 8)
#       define NUM_GS_THWEADS(x)                          ((x) << 16)
#       define NUM_ES_THWEADS(x)                          ((x) << 24)
#define SQ_STACK_WESOUWCE_MGMT_1                          0x8c10
#       define NUM_PS_STACK_ENTWIES(x)                    ((x) << 0)
#       define NUM_VS_STACK_ENTWIES(x)                    ((x) << 16)
#define SQ_STACK_WESOUWCE_MGMT_2                          0x8c14
#       define NUM_GS_STACK_ENTWIES(x)                    ((x) << 0)
#       define NUM_ES_STACK_ENTWIES(x)                    ((x) << 16)
#define SQ_ESGS_WING_BASE                               0x8c40
#define SQ_GSVS_WING_BASE                               0x8c48
#define SQ_ESTMP_WING_BASE                              0x8c50
#define SQ_GSTMP_WING_BASE                              0x8c58
#define SQ_VSTMP_WING_BASE                              0x8c60
#define SQ_PSTMP_WING_BASE                              0x8c68
#define SQ_FBUF_WING_BASE                               0x8c70
#define SQ_WEDUC_WING_BASE                              0x8c78

#define GWBM_CNTW                                       0x8000
#       define GWBM_WEAD_TIMEOUT(x)                     ((x) << 0)
#define	GWBM_STATUS					0x8010
#define		CMDFIFO_AVAIW_MASK				0x0000001F
#define		GUI_ACTIVE					(1<<31)
#define	GWBM_STATUS2					0x8014
#define	GWBM_SOFT_WESET					0x8020
#define		SOFT_WESET_CP					(1<<0)

#define	CG_THEWMAW_CTWW					0x7F0
#define		DIG_THEWM_DPM(x)			((x) << 12)
#define		DIG_THEWM_DPM_MASK			0x000FF000
#define		DIG_THEWM_DPM_SHIFT			12
#define	CG_THEWMAW_STATUS				0x7F4
#define		ASIC_T(x)			        ((x) << 0)
#define		ASIC_T_MASK			        0x1FF
#define		ASIC_T_SHIFT			        0
#define	CG_THEWMAW_INT					0x7F8
#define		DIG_THEWM_INTH(x)			((x) << 8)
#define		DIG_THEWM_INTH_MASK			0x0000FF00
#define		DIG_THEWM_INTH_SHIFT			8
#define		DIG_THEWM_INTW(x)			((x) << 16)
#define		DIG_THEWM_INTW_MASK			0x00FF0000
#define		DIG_THEWM_INTW_SHIFT			16
#define 	THEWM_INT_MASK_HIGH			(1 << 24)
#define 	THEWM_INT_MASK_WOW			(1 << 25)

#define	WV770_CG_THEWMAW_INT				0x734

#define	HDP_HOST_PATH_CNTW				0x2C00
#define	HDP_NONSUWFACE_BASE				0x2C04
#define	HDP_NONSUWFACE_INFO				0x2C08
#define	HDP_NONSUWFACE_SIZE				0x2C0C
#define HDP_WEG_COHEWENCY_FWUSH_CNTW			0x54A0
#define	HDP_TIWING_CONFIG				0x2F3C
#define HDP_DEBUG1                                      0x2F34

#define MC_CONFIG					0x2000
#define MC_VM_AGP_TOP					0x2184
#define MC_VM_AGP_BOT					0x2188
#define	MC_VM_AGP_BASE					0x218C
#define MC_VM_FB_WOCATION				0x2180
#define MC_VM_W1_TWB_MCB_WD_UVD_CNTW			0x2124
#define 	ENABWE_W1_TWB					(1 << 0)
#define		ENABWE_W1_FWAGMENT_PWOCESSING			(1 << 1)
#define		ENABWE_W1_STWICT_OWDEWING			(1 << 2)
#define		SYSTEM_ACCESS_MODE_MASK				0x000000C0
#define		SYSTEM_ACCESS_MODE_SHIFT			6
#define		SYSTEM_ACCESS_MODE_PA_ONWY			(0 << 6)
#define		SYSTEM_ACCESS_MODE_USE_SYS_MAP			(1 << 6)
#define		SYSTEM_ACCESS_MODE_IN_SYS			(2 << 6)
#define		SYSTEM_ACCESS_MODE_NOT_IN_SYS			(3 << 6)
#define		SYSTEM_APEWTUWE_UNMAPPED_ACCESS_PASS_THWU	(0 << 8)
#define		SYSTEM_APEWTUWE_UNMAPPED_ACCESS_DEFAUWT_PAGE	(1 << 8)
#define		ENABWE_SEMAPHOWE_MODE				(1 << 10)
#define		ENABWE_WAIT_W2_QUEWY				(1 << 11)
#define		EFFECTIVE_W1_TWB_SIZE(x)			(((x) & 7) << 12)
#define		EFFECTIVE_W1_TWB_SIZE_MASK			0x00007000
#define		EFFECTIVE_W1_TWB_SIZE_SHIFT			12
#define		EFFECTIVE_W1_QUEUE_SIZE(x)			(((x) & 7) << 15)
#define		EFFECTIVE_W1_QUEUE_SIZE_MASK			0x00038000
#define		EFFECTIVE_W1_QUEUE_SIZE_SHIFT			15
#define MC_VM_W1_TWB_MCD_WD_A_CNTW			0x219C
#define MC_VM_W1_TWB_MCD_WD_B_CNTW			0x21A0
#define MC_VM_W1_TWB_MCB_WD_GFX_CNTW			0x21FC
#define MC_VM_W1_TWB_MCB_WD_HDP_CNTW			0x2204
#define MC_VM_W1_TWB_MCB_WD_PDMA_CNTW			0x2208
#define MC_VM_W1_TWB_MCB_WD_SEM_CNTW			0x220C
#define	MC_VM_W1_TWB_MCB_WD_SYS_CNTW			0x2200
#define MC_VM_W1_TWB_MCB_WW_UVD_CNTW			0x212c
#define MC_VM_W1_TWB_MCD_WW_A_CNTW			0x21A4
#define MC_VM_W1_TWB_MCD_WW_B_CNTW			0x21A8
#define MC_VM_W1_TWB_MCB_WW_GFX_CNTW			0x2210
#define MC_VM_W1_TWB_MCB_WW_HDP_CNTW			0x2218
#define MC_VM_W1_TWB_MCB_WW_PDMA_CNTW			0x221C
#define MC_VM_W1_TWB_MCB_WW_SEM_CNTW			0x2220
#define MC_VM_W1_TWB_MCB_WW_SYS_CNTW			0x2214
#define MC_VM_SYSTEM_APEWTUWE_WOW_ADDW			0x2190
#define		WOGICAW_PAGE_NUMBEW_MASK			0x000FFFFF
#define		WOGICAW_PAGE_NUMBEW_SHIFT			0
#define MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW			0x2194
#define MC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW		0x2198

#define WS_DQ_WD_WET_CONF				0x2348

#define	PA_CW_ENHANCE					0x8A14
#define		CWIP_VTX_WEOWDEW_ENA				(1 << 0)
#define		NUM_CWIP_SEQ(x)					((x) << 1)
#define PA_SC_AA_CONFIG					0x28C04
#define	PA_SC_AA_SAMPWE_WOCS_2S				0x8B40
#define	PA_SC_AA_SAMPWE_WOCS_4S				0x8B44
#define	PA_SC_AA_SAMPWE_WOCS_8S_WD0			0x8B48
#define	PA_SC_AA_SAMPWE_WOCS_8S_WD1			0x8B4C
#define		S0_X(x)						((x) << 0)
#define		S0_Y(x)						((x) << 4)
#define		S1_X(x)						((x) << 8)
#define		S1_Y(x)						((x) << 12)
#define		S2_X(x)						((x) << 16)
#define		S2_Y(x)						((x) << 20)
#define		S3_X(x)						((x) << 24)
#define		S3_Y(x)						((x) << 28)
#define		S4_X(x)						((x) << 0)
#define		S4_Y(x)						((x) << 4)
#define		S5_X(x)						((x) << 8)
#define		S5_Y(x)						((x) << 12)
#define		S6_X(x)						((x) << 16)
#define		S6_Y(x)						((x) << 20)
#define		S7_X(x)						((x) << 24)
#define		S7_Y(x)						((x) << 28)
#define PA_SC_CWIPWECT_WUWE				0x2820c
#define	PA_SC_ENHANCE					0x8BF0
#define		FOWCE_EOV_MAX_CWK_CNT(x)			((x) << 0)
#define		FOWCE_EOV_MAX_TIWE_CNT(x)			((x) << 12)
#define PA_SC_WINE_STIPPWE				0x28A0C
#define	PA_SC_WINE_STIPPWE_STATE			0x8B10
#define PA_SC_MODE_CNTW					0x28A4C
#define	PA_SC_MUWTI_CHIP_CNTW				0x8B20

#define PA_SC_SCWEEN_SCISSOW_TW                         0x28030
#define PA_SC_GENEWIC_SCISSOW_TW                        0x28240
#define PA_SC_WINDOW_SCISSOW_TW                         0x28204

#define	PCIE_POWT_INDEX					0x0038
#define	PCIE_POWT_DATA					0x003C

#define CHMAP						0x2004
#define		NOOFCHAN_SHIFT					12
#define		NOOFCHAN_MASK					0x00003000

#define WAMCFG						0x2408
#define		NOOFBANK_SHIFT					0
#define		NOOFBANK_MASK					0x00000001
#define		NOOFWANK_SHIFT					1
#define		NOOFWANK_MASK					0x00000002
#define		NOOFWOWS_SHIFT					2
#define		NOOFWOWS_MASK					0x0000001C
#define		NOOFCOWS_SHIFT					5
#define		NOOFCOWS_MASK					0x00000060
#define		CHANSIZE_SHIFT					7
#define		CHANSIZE_MASK					0x00000080
#define		BUWSTWENGTH_SHIFT				8
#define		BUWSTWENGTH_MASK				0x00000100
#define		CHANSIZE_OVEWWIDE				(1 << 10)

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
#define	SPI_PS_IN_CONTWOW_1				0x286D0
#define		GEN_INDEX_PIX					(1<<0)
#define		GEN_INDEX_PIX_ADDW(x)				((x)<<1)
#define		FWONT_FACE_ENA					(1<<8)
#define		FWONT_FACE_CHAN(x)				((x)<<9)
#define		FWONT_FACE_AWW_BITS				(1<<11)
#define		FWONT_FACE_ADDW(x)				((x)<<12)
#define		FOG_ADDW(x)					((x)<<17)
#define		FIXED_PT_POSITION_ENA				(1<<24)
#define		FIXED_PT_POSITION_ADDW(x)			((x)<<25)

#define	SQ_MS_FIFO_SIZES				0x8CF0
#define		CACHE_FIFO_SIZE(x)				((x) << 0)
#define		FETCH_FIFO_HIWATEW(x)				((x) << 8)
#define		DONE_FIFO_HIWATEW(x)				((x) << 16)
#define		AWU_UPDATE_FIFO_HIWATEW(x)			((x) << 24)
#define	SQ_PGM_STAWT_ES					0x28880
#define	SQ_PGM_STAWT_FS					0x28894
#define	SQ_PGM_STAWT_GS					0x2886C
#define	SQ_PGM_STAWT_PS					0x28840
#define SQ_PGM_WESOUWCES_PS                             0x28850
#define SQ_PGM_EXPOWTS_PS                               0x28854
#define SQ_PGM_CF_OFFSET_PS                             0x288cc
#define	SQ_PGM_STAWT_VS					0x28858
#define SQ_PGM_WESOUWCES_VS                             0x28868
#define SQ_PGM_CF_OFFSET_VS                             0x288d0

#define SQ_VTX_CONSTANT_WOWD0_0				0x30000
#define SQ_VTX_CONSTANT_WOWD1_0				0x30004
#define SQ_VTX_CONSTANT_WOWD2_0				0x30008
#	define SQ_VTXC_BASE_ADDW_HI(x)			((x) << 0)
#	define SQ_VTXC_STWIDE(x)			((x) << 8)
#	define SQ_VTXC_ENDIAN_SWAP(x)			((x) << 30)
#	define SQ_ENDIAN_NONE				0
#	define SQ_ENDIAN_8IN16				1
#	define SQ_ENDIAN_8IN32				2
#define SQ_VTX_CONSTANT_WOWD3_0				0x3000c
#define	SQ_VTX_CONSTANT_WOWD6_0				0x38018
#define		S__SQ_VTX_CONSTANT_TYPE(x)			(((x) & 3) << 30)
#define		G__SQ_VTX_CONSTANT_TYPE(x)			(((x) >> 30) & 3)
#define			SQ_TEX_VTX_INVAWID_TEXTUWE			0x0
#define			SQ_TEX_VTX_INVAWID_BUFFEW			0x1
#define			SQ_TEX_VTX_VAWID_TEXTUWE			0x2
#define			SQ_TEX_VTX_VAWID_BUFFEW				0x3


#define	SX_MISC						0x28350
#define	SX_MEMOWY_EXPOWT_BASE				0x9010
#define	SX_DEBUG_1					0x9054
#define		SMX_EVENT_WEWEASE				(1 << 0)
#define		ENABWE_NEW_SMX_ADDWESS				(1 << 16)

#define	TA_CNTW_AUX					0x9508
#define		DISABWE_CUBE_WWAP				(1 << 0)
#define		DISABWE_CUBE_ANISO				(1 << 1)
#define		SYNC_GWADIENT					(1 << 24)
#define		SYNC_WAWKEW					(1 << 25)
#define		SYNC_AWIGNEW					(1 << 26)
#define		BIWINEAW_PWECISION_6_BIT			(0 << 31)
#define		BIWINEAW_PWECISION_8_BIT			(1 << 31)

#define	TC_CNTW						0x9608
#define		TC_W2_SIZE(x)					((x)<<5)
#define		W2_DISABWE_WATE_HIT				(1<<9)

#define	VC_ENHANCE					0x9714

#define	VGT_CACHE_INVAWIDATION				0x88C4
#define		CACHE_INVAWIDATION(x)				((x)<<0)
#define			VC_ONWY						0
#define			TC_ONWY						1
#define			VC_AND_TC					2
#define	VGT_DMA_BASE					0x287E8
#define	VGT_DMA_BASE_HI					0x287E4
#define	VGT_ES_PEW_GS					0x88CC
#define	VGT_GS_PEW_ES					0x88C8
#define	VGT_GS_PEW_VS					0x88E8
#define	VGT_GS_VEWTEX_WEUSE				0x88D4
#define VGT_PWIMITIVE_TYPE                              0x8958
#define	VGT_NUM_INSTANCES				0x8974
#define	VGT_OUT_DEAWWOC_CNTW				0x28C5C
#define		DEAWWOC_DIST_MASK				0x0000007F
#define	VGT_STWMOUT_BASE_OFFSET_0			0x28B10
#define	VGT_STWMOUT_BASE_OFFSET_1			0x28B14
#define	VGT_STWMOUT_BASE_OFFSET_2			0x28B18
#define	VGT_STWMOUT_BASE_OFFSET_3			0x28B1c
#define	VGT_STWMOUT_BASE_OFFSET_HI_0			0x28B44
#define	VGT_STWMOUT_BASE_OFFSET_HI_1			0x28B48
#define	VGT_STWMOUT_BASE_OFFSET_HI_2			0x28B4c
#define	VGT_STWMOUT_BASE_OFFSET_HI_3			0x28B50
#define	VGT_STWMOUT_BUFFEW_BASE_0			0x28AD8
#define	VGT_STWMOUT_BUFFEW_BASE_1			0x28AE8
#define	VGT_STWMOUT_BUFFEW_BASE_2			0x28AF8
#define	VGT_STWMOUT_BUFFEW_BASE_3			0x28B08
#define	VGT_STWMOUT_BUFFEW_OFFSET_0			0x28ADC
#define	VGT_STWMOUT_BUFFEW_OFFSET_1			0x28AEC
#define	VGT_STWMOUT_BUFFEW_OFFSET_2			0x28AFC
#define	VGT_STWMOUT_BUFFEW_OFFSET_3			0x28B0C
#define VGT_STWMOUT_BUFFEW_SIZE_0			0x28AD0
#define VGT_STWMOUT_BUFFEW_SIZE_1			0x28AE0
#define VGT_STWMOUT_BUFFEW_SIZE_2			0x28AF0
#define VGT_STWMOUT_BUFFEW_SIZE_3			0x28B00

#define	VGT_STWMOUT_EN					0x28AB0
#define	VGT_VEWTEX_WEUSE_BWOCK_CNTW			0x28C58
#define		VTX_WEUSE_DEPTH_MASK				0x000000FF
#define VGT_EVENT_INITIATOW                             0x28a90
#       define CACHE_FWUSH_AND_INV_EVENT_TS                     (0x14 << 0)
#       define CACHE_FWUSH_AND_INV_EVENT                        (0x16 << 0)

#define VM_CONTEXT0_CNTW				0x1410
#define		ENABWE_CONTEXT					(1 << 0)
#define		PAGE_TABWE_DEPTH(x)				(((x) & 3) << 1)
#define		WANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT		(1 << 4)
#define VM_CONTEXT0_INVAWIDATION_WOW_ADDW		0x1490
#define VM_CONTEXT0_INVAWIDATION_HIGH_ADDW		0x14B0
#define VM_CONTEXT0_PAGE_TABWE_BASE_ADDW		0x1574
#define VM_CONTEXT0_PAGE_TABWE_STAWT_ADDW		0x1594
#define VM_CONTEXT0_PAGE_TABWE_END_ADDW			0x15B4
#define VM_CONTEXT0_PWOTECTION_FAUWT_DEFAUWT_ADDW	0x1554
#define VM_CONTEXT0_WEQUEST_WESPONSE			0x1470
#define		WEQUEST_TYPE(x)					(((x) & 0xf) << 0)
#define		WESPONSE_TYPE_MASK				0x000000F0
#define		WESPONSE_TYPE_SHIFT				4
#define VM_W2_CNTW					0x1400
#define		ENABWE_W2_CACHE					(1 << 0)
#define		ENABWE_W2_FWAGMENT_PWOCESSING			(1 << 1)
#define		ENABWE_W2_PTE_CACHE_WWU_UPDATE_BY_WWITE		(1 << 9)
#define		EFFECTIVE_W2_QUEUE_SIZE(x)			(((x) & 7) << 13)
#define VM_W2_CNTW2					0x1404
#define		INVAWIDATE_AWW_W1_TWBS				(1 << 0)
#define		INVAWIDATE_W2_CACHE				(1 << 1)
#define VM_W2_CNTW3					0x1408
#define		BANK_SEWECT_0(x)				(((x) & 0x1f) << 0)
#define		BANK_SEWECT_1(x)				(((x) & 0x1f) << 5)
#define		W2_CACHE_UPDATE_MODE(x)				(((x) & 3) << 10)
#define	VM_W2_STATUS					0x140C
#define		W2_BUSY						(1 << 0)

#define	WAIT_UNTIW					0x8040
#define         WAIT_CP_DMA_IDWE_bit                            (1 << 8)
#define         WAIT_2D_IDWE_bit                                (1 << 14)
#define         WAIT_3D_IDWE_bit                                (1 << 15)
#define         WAIT_2D_IDWECWEAN_bit                           (1 << 16)
#define         WAIT_3D_IDWECWEAN_bit                           (1 << 17)

/* async DMA */
#define DMA_TIWING_CONFIG                                 0x3ec4
#define DMA_CONFIG                                        0x3e4c

#define DMA_WB_CNTW                                       0xd000
#       define DMA_WB_ENABWE                              (1 << 0)
#       define DMA_WB_SIZE(x)                             ((x) << 1) /* wog2 */
#       define DMA_WB_SWAP_ENABWE                         (1 << 9) /* 8IN32 */
#       define DMA_WPTW_WWITEBACK_ENABWE                  (1 << 12)
#       define DMA_WPTW_WWITEBACK_SWAP_ENABWE             (1 << 13)  /* 8IN32 */
#       define DMA_WPTW_WWITEBACK_TIMEW(x)                ((x) << 16) /* wog2 */
#define DMA_WB_BASE                                       0xd004
#define DMA_WB_WPTW                                       0xd008
#define DMA_WB_WPTW                                       0xd00c

#define DMA_WB_WPTW_ADDW_HI                               0xd01c
#define DMA_WB_WPTW_ADDW_WO                               0xd020

#define DMA_IB_CNTW                                       0xd024
#       define DMA_IB_ENABWE                              (1 << 0)
#       define DMA_IB_SWAP_ENABWE                         (1 << 4)
#define DMA_IB_WPTW                                       0xd028
#define DMA_CNTW                                          0xd02c
#       define TWAP_ENABWE                                (1 << 0)
#       define SEM_INCOMPWETE_INT_ENABWE                  (1 << 1)
#       define SEM_WAIT_INT_ENABWE                        (1 << 2)
#       define DATA_SWAP_ENABWE                           (1 << 3)
#       define FENCE_SWAP_ENABWE                          (1 << 4)
#       define CTXEMPTY_INT_ENABWE                        (1 << 28)
#define DMA_STATUS_WEG                                    0xd034
#       define DMA_IDWE                                   (1 << 0)
#define DMA_SEM_INCOMPWETE_TIMEW_CNTW                     0xd044
#define DMA_SEM_WAIT_FAIW_TIMEW_CNTW                      0xd048
#define DMA_MODE                                          0xd0bc

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
#define	DMA_PACKET_CONSTANT_FIWW			  0xd /* 7xx onwy */
#define	DMA_PACKET_NOP					  0xf

#define IH_WB_CNTW                                        0x3e00
#       define IH_WB_ENABWE                               (1 << 0)
#       define IH_WB_SIZE(x)                              ((x) << 1) /* wog2 */
#       define IH_WB_FUWW_DWAIN_ENABWE                    (1 << 6)
#       define IH_WPTW_WWITEBACK_ENABWE                   (1 << 8)
#       define IH_WPTW_WWITEBACK_TIMEW(x)                 ((x) << 9) /* wog2 */
#       define IH_WPTW_OVEWFWOW_ENABWE                    (1 << 16)
#       define IH_WPTW_OVEWFWOW_CWEAW                     (1 << 31)
#define IH_WB_BASE                                        0x3e04
#define IH_WB_WPTW                                        0x3e08
#define IH_WB_WPTW                                        0x3e0c
#       define WB_OVEWFWOW                                (1 << 0)
#       define WPTW_OFFSET_MASK                           0x3fffc
#define IH_WB_WPTW_ADDW_HI                                0x3e10
#define IH_WB_WPTW_ADDW_WO                                0x3e14
#define IH_CNTW                                           0x3e18
#       define ENABWE_INTW                                (1 << 0)
#       define IH_MC_SWAP(x)                              ((x) << 1)
#       define IH_MC_SWAP_NONE                            0
#       define IH_MC_SWAP_16BIT                           1
#       define IH_MC_SWAP_32BIT                           2
#       define IH_MC_SWAP_64BIT                           3
#       define WPTW_WEAWM                                 (1 << 4)
#       define MC_WWWEQ_CWEDIT(x)                         ((x) << 15)
#       define MC_WW_CWEAN_CNT(x)                         ((x) << 20)

#define WWC_CNTW                                          0x3f00
#       define WWC_ENABWE                                 (1 << 0)
#define WWC_HB_BASE                                       0x3f10
#define WWC_HB_CNTW                                       0x3f0c
#define WWC_HB_WPTW                                       0x3f20
#define WWC_HB_WPTW                                       0x3f1c
#define WWC_HB_WPTW_WSB_ADDW                              0x3f14
#define WWC_HB_WPTW_MSB_ADDW                              0x3f18
#define WWC_GPU_CWOCK_COUNT_WSB				  0x3f38
#define WWC_GPU_CWOCK_COUNT_MSB				  0x3f3c
#define WWC_CAPTUWE_GPU_CWOCK_COUNT			  0x3f40
#define WWC_MC_CNTW                                       0x3f44
#define WWC_UCODE_CNTW                                    0x3f48
#define WWC_UCODE_ADDW                                    0x3f2c
#define WWC_UCODE_DATA                                    0x3f30

#define SWBM_SOFT_WESET                                   0xe60
#       define SOFT_WESET_BIF                             (1 << 1)
#       define SOFT_WESET_DMA                             (1 << 12)
#       define SOFT_WESET_WWC                             (1 << 13)
#       define SOFT_WESET_UVD                             (1 << 18)
#       define WV770_SOFT_WESET_DMA                       (1 << 20)

#define BIF_SCWATCH0                                      0x5438

#define BUS_CNTW                                          0x5420
#       define BIOS_WOM_DIS                               (1 << 1)
#       define VGA_COHE_SPEC_TIMEW_DIS                    (1 << 9)

#define CP_INT_CNTW                                       0xc124
#       define CNTX_BUSY_INT_ENABWE                       (1 << 19)
#       define CNTX_EMPTY_INT_ENABWE                      (1 << 20)
#       define SCWATCH_INT_ENABWE                         (1 << 25)
#       define TIME_STAMP_INT_ENABWE                      (1 << 26)
#       define IB2_INT_ENABWE                             (1 << 29)
#       define IB1_INT_ENABWE                             (1 << 30)
#       define WB_INT_ENABWE                              (1 << 31)
#define CP_INT_STATUS                                     0xc128
#       define SCWATCH_INT_STAT                           (1 << 25)
#       define TIME_STAMP_INT_STAT                        (1 << 26)
#       define IB2_INT_STAT                               (1 << 29)
#       define IB1_INT_STAT                               (1 << 30)
#       define WB_INT_STAT                                (1 << 31)

#define GWBM_INT_CNTW                                     0x8060
#       define WDEWW_INT_ENABWE                           (1 << 0)
#       define WAIT_COUNT_TIMEOUT_INT_ENABWE              (1 << 1)
#       define GUI_IDWE_INT_ENABWE                        (1 << 19)

#define INTEWWUPT_CNTW                                    0x5468
#       define IH_DUMMY_WD_OVEWWIDE                       (1 << 0)
#       define IH_DUMMY_WD_EN                             (1 << 1)
#       define IH_WEQ_NONSNOOP_EN                         (1 << 3)
#       define GEN_IH_INT_EN                              (1 << 8)
#define INTEWWUPT_CNTW2                                   0x546c

#define D1MODE_VBWANK_STATUS                              0x6534
#define D2MODE_VBWANK_STATUS                              0x6d34
#       define DxMODE_VBWANK_OCCUWWED                     (1 << 0)
#       define DxMODE_VBWANK_ACK                          (1 << 4)
#       define DxMODE_VBWANK_STAT                         (1 << 12)
#       define DxMODE_VBWANK_INTEWWUPT                    (1 << 16)
#       define DxMODE_VBWANK_INTEWWUPT_TYPE               (1 << 17)
#define D1MODE_VWINE_STATUS                               0x653c
#define D2MODE_VWINE_STATUS                               0x6d3c
#       define DxMODE_VWINE_OCCUWWED                      (1 << 0)
#       define DxMODE_VWINE_ACK                           (1 << 4)
#       define DxMODE_VWINE_STAT                          (1 << 12)
#       define DxMODE_VWINE_INTEWWUPT                     (1 << 16)
#       define DxMODE_VWINE_INTEWWUPT_TYPE                (1 << 17)
#define DxMODE_INT_MASK                                   0x6540
#       define D1MODE_VBWANK_INT_MASK                     (1 << 0)
#       define D1MODE_VWINE_INT_MASK                      (1 << 4)
#       define D2MODE_VBWANK_INT_MASK                     (1 << 8)
#       define D2MODE_VWINE_INT_MASK                      (1 << 12)
#define DCE3_DISP_INTEWWUPT_STATUS                        0x7ddc
#       define DC_HPD1_INTEWWUPT                          (1 << 18)
#       define DC_HPD2_INTEWWUPT                          (1 << 19)
#define DISP_INTEWWUPT_STATUS                             0x7edc
#       define WB_D1_VWINE_INTEWWUPT                      (1 << 2)
#       define WB_D2_VWINE_INTEWWUPT                      (1 << 3)
#       define WB_D1_VBWANK_INTEWWUPT                     (1 << 4)
#       define WB_D2_VBWANK_INTEWWUPT                     (1 << 5)
#       define DACA_AUTODETECT_INTEWWUPT                  (1 << 16)
#       define DACB_AUTODETECT_INTEWWUPT                  (1 << 17)
#       define DC_HOT_PWUG_DETECT1_INTEWWUPT              (1 << 18)
#       define DC_HOT_PWUG_DETECT2_INTEWWUPT              (1 << 19)
#       define DC_I2C_SW_DONE_INTEWWUPT                   (1 << 20)
#       define DC_I2C_HW_DONE_INTEWWUPT                   (1 << 21)
#define DISP_INTEWWUPT_STATUS_CONTINUE                    0x7ee8
#define DCE3_DISP_INTEWWUPT_STATUS_CONTINUE               0x7de8
#       define DC_HPD4_INTEWWUPT                          (1 << 14)
#       define DC_HPD4_WX_INTEWWUPT                       (1 << 15)
#       define DC_HPD3_INTEWWUPT                          (1 << 28)
#       define DC_HPD1_WX_INTEWWUPT                       (1 << 29)
#       define DC_HPD2_WX_INTEWWUPT                       (1 << 30)
#define DCE3_DISP_INTEWWUPT_STATUS_CONTINUE2              0x7dec
#       define DC_HPD3_WX_INTEWWUPT                       (1 << 0)
#       define DIGA_DP_VID_STWEAM_DISABWE_INTEWWUPT       (1 << 1)
#       define DIGA_DP_STEEW_FIFO_OVEWFWOW_INTEWWUPT      (1 << 2)
#       define DIGB_DP_VID_STWEAM_DISABWE_INTEWWUPT       (1 << 3)
#       define DIGB_DP_STEEW_FIFO_OVEWFWOW_INTEWWUPT      (1 << 4)
#       define AUX1_SW_DONE_INTEWWUPT                     (1 << 5)
#       define AUX1_WS_DONE_INTEWWUPT                     (1 << 6)
#       define AUX2_SW_DONE_INTEWWUPT                     (1 << 7)
#       define AUX2_WS_DONE_INTEWWUPT                     (1 << 8)
#       define AUX3_SW_DONE_INTEWWUPT                     (1 << 9)
#       define AUX3_WS_DONE_INTEWWUPT                     (1 << 10)
#       define AUX4_SW_DONE_INTEWWUPT                     (1 << 11)
#       define AUX4_WS_DONE_INTEWWUPT                     (1 << 12)
#       define DIGA_DP_FAST_TWAINING_COMPWETE_INTEWWUPT   (1 << 13)
#       define DIGB_DP_FAST_TWAINING_COMPWETE_INTEWWUPT   (1 << 14)
/* DCE 3.2 */
#       define AUX5_SW_DONE_INTEWWUPT                     (1 << 15)
#       define AUX5_WS_DONE_INTEWWUPT                     (1 << 16)
#       define AUX6_SW_DONE_INTEWWUPT                     (1 << 17)
#       define AUX6_WS_DONE_INTEWWUPT                     (1 << 18)
#       define DC_HPD5_INTEWWUPT                          (1 << 19)
#       define DC_HPD5_WX_INTEWWUPT                       (1 << 20)
#       define DC_HPD6_INTEWWUPT                          (1 << 21)
#       define DC_HPD6_WX_INTEWWUPT                       (1 << 22)

#define DACA_AUTO_DETECT_CONTWOW                          0x7828
#define DACB_AUTO_DETECT_CONTWOW                          0x7a28
#define DCE3_DACA_AUTO_DETECT_CONTWOW                     0x7028
#define DCE3_DACB_AUTO_DETECT_CONTWOW                     0x7128
#       define DACx_AUTODETECT_MODE(x)                    ((x) << 0)
#       define DACx_AUTODETECT_MODE_NONE                  0
#       define DACx_AUTODETECT_MODE_CONNECT               1
#       define DACx_AUTODETECT_MODE_DISCONNECT            2
#       define DACx_AUTODETECT_FWAME_TIME_COUNTEW(x)      ((x) << 8)
/* bit 18 = W/C, 17 = G/Y, 16 = B/Comp */
#       define DACx_AUTODETECT_CHECK_MASK(x)              ((x) << 16)

#define DCE3_DACA_AUTODETECT_INT_CONTWOW                  0x7038
#define DCE3_DACB_AUTODETECT_INT_CONTWOW                  0x7138
#define DACA_AUTODETECT_INT_CONTWOW                       0x7838
#define DACB_AUTODETECT_INT_CONTWOW                       0x7a38
#       define DACx_AUTODETECT_ACK                        (1 << 0)
#       define DACx_AUTODETECT_INT_ENABWE                 (1 << 16)

#define DC_HOT_PWUG_DETECT1_CONTWOW                       0x7d00
#define DC_HOT_PWUG_DETECT2_CONTWOW                       0x7d10
#define DC_HOT_PWUG_DETECT3_CONTWOW                       0x7d24
#       define DC_HOT_PWUG_DETECTx_EN                     (1 << 0)

#define DC_HOT_PWUG_DETECT1_INT_STATUS                    0x7d04
#define DC_HOT_PWUG_DETECT2_INT_STATUS                    0x7d14
#define DC_HOT_PWUG_DETECT3_INT_STATUS                    0x7d28
#       define DC_HOT_PWUG_DETECTx_INT_STATUS             (1 << 0)
#       define DC_HOT_PWUG_DETECTx_SENSE                  (1 << 1)

/* DCE 3.0 */
#define DC_HPD1_INT_STATUS                                0x7d00
#define DC_HPD2_INT_STATUS                                0x7d0c
#define DC_HPD3_INT_STATUS                                0x7d18
#define DC_HPD4_INT_STATUS                                0x7d24
/* DCE 3.2 */
#define DC_HPD5_INT_STATUS                                0x7dc0
#define DC_HPD6_INT_STATUS                                0x7df4
#       define DC_HPDx_INT_STATUS                         (1 << 0)
#       define DC_HPDx_SENSE                              (1 << 1)
#       define DC_HPDx_WX_INT_STATUS                      (1 << 8)

#define DC_HOT_PWUG_DETECT1_INT_CONTWOW                   0x7d08
#define DC_HOT_PWUG_DETECT2_INT_CONTWOW                   0x7d18
#define DC_HOT_PWUG_DETECT3_INT_CONTWOW                   0x7d2c
#       define DC_HOT_PWUG_DETECTx_INT_ACK                (1 << 0)
#       define DC_HOT_PWUG_DETECTx_INT_POWAWITY           (1 << 8)
#       define DC_HOT_PWUG_DETECTx_INT_EN                 (1 << 16)
/* DCE 3.0 */
#define DC_HPD1_INT_CONTWOW                               0x7d04
#define DC_HPD2_INT_CONTWOW                               0x7d10
#define DC_HPD3_INT_CONTWOW                               0x7d1c
#define DC_HPD4_INT_CONTWOW                               0x7d28
/* DCE 3.2 */
#define DC_HPD5_INT_CONTWOW                               0x7dc4
#define DC_HPD6_INT_CONTWOW                               0x7df8
#       define DC_HPDx_INT_ACK                            (1 << 0)
#       define DC_HPDx_INT_POWAWITY                       (1 << 8)
#       define DC_HPDx_INT_EN                             (1 << 16)
#       define DC_HPDx_WX_INT_ACK                         (1 << 20)
#       define DC_HPDx_WX_INT_EN                          (1 << 24)

/* DCE 3.0 */
#define DC_HPD1_CONTWOW                                   0x7d08
#define DC_HPD2_CONTWOW                                   0x7d14
#define DC_HPD3_CONTWOW                                   0x7d20
#define DC_HPD4_CONTWOW                                   0x7d2c
/* DCE 3.2 */
#define DC_HPD5_CONTWOW                                   0x7dc8
#define DC_HPD6_CONTWOW                                   0x7dfc
#       define DC_HPDx_CONNECTION_TIMEW(x)                ((x) << 0)
#       define DC_HPDx_WX_INT_TIMEW(x)                    ((x) << 16)
/* DCE 3.2 */
#       define DC_HPDx_EN                                 (1 << 28)

#define D1GWPH_INTEWWUPT_STATUS                           0x6158
#define D2GWPH_INTEWWUPT_STATUS                           0x6958
#       define DxGWPH_PFWIP_INT_OCCUWWED                  (1 << 0)
#       define DxGWPH_PFWIP_INT_CWEAW                     (1 << 8)
#define D1GWPH_INTEWWUPT_CONTWOW                          0x615c
#define D2GWPH_INTEWWUPT_CONTWOW                          0x695c
#       define DxGWPH_PFWIP_INT_MASK                      (1 << 0)
#       define DxGWPH_PFWIP_INT_TYPE                      (1 << 8)

/* PCIE wink stuff */
#define PCIE_WC_TWAINING_CNTW                             0xa1 /* PCIE_P */
#       define WC_POINT_7_PWUS_EN                         (1 << 6)
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
#       define WC_VOWTAGE_TIMEW_SEW_MASK                  (0xf << 14)
#       define WC_CWW_FAIWED_SPD_CHANGE_CNT               (1 << 21)
#       define WC_OTHEW_SIDE_EVEW_SENT_GEN2               (1 << 23)
#       define WC_OTHEW_SIDE_SUPPOWTS_GEN2                (1 << 24)
#define MM_CFGWEGS_CNTW                                   0x544c
#       define MM_WW_TO_CFG_EN                            (1 << 3)
#define WINK_CNTW2                                        0x88 /* F0 */
#       define TAWGET_WINK_SPEED_MASK                     (0xf << 0)
#       define SEWECTABWE_DEEMPHASIS                      (1 << 6)

/* Audio */
#define AZ_HOT_PWUG_CONTWOW               0x7300
#       define AZ_FOWCE_CODEC_WAKE        (1 << 0)
#       define JACK_DETECTION_ENABWE      (1 << 4)
#       define UNSOWICITED_WESPONSE_ENABWE (1 << 8)
#       define CODEC_HOT_PWUG_ENABWE      (1 << 12)
#       define AUDIO_ENABWED              (1 << 31)
/* DCE3 adds */
#       define PIN0_JACK_DETECTION_ENABWE (1 << 4)
#       define PIN1_JACK_DETECTION_ENABWE (1 << 5)
#       define PIN2_JACK_DETECTION_ENABWE (1 << 6)
#       define PIN3_JACK_DETECTION_ENABWE (1 << 7)
#       define PIN0_AUDIO_ENABWED         (1 << 24)
#       define PIN1_AUDIO_ENABWED         (1 << 25)
#       define PIN2_AUDIO_ENABWED         (1 << 26)
#       define PIN3_AUDIO_ENABWED         (1 << 27)

/* Audio cwocks DCE 2.0/3.0 */
#define AUDIO_DTO                         0x7340
#       define AUDIO_DTO_PHASE(x)         (((x) & 0xffff) << 0)
#       define AUDIO_DTO_MODUWE(x)        (((x) & 0xffff) << 16)

/* Audio cwocks DCE 3.2 */
#define DCCG_AUDIO_DTO0_PHASE             0x0514
#define DCCG_AUDIO_DTO0_MODUWE            0x0518
#define DCCG_AUDIO_DTO0_WOAD              0x051c
#       define DTO_WOAD                   (1 << 31)
#define DCCG_AUDIO_DTO0_CNTW              0x0520
#       define DCCG_AUDIO_DTO_WAWWCWOCK_WATIO(x) (((x) & 7) << 0)
#       define DCCG_AUDIO_DTO_WAWWCWOCK_WATIO_MASK 7
#       define DCCG_AUDIO_DTO_WAWWCWOCK_WATIO_SHIFT 0

#define DCCG_AUDIO_DTO1_PHASE             0x0524
#define DCCG_AUDIO_DTO1_MODUWE            0x0528
#define DCCG_AUDIO_DTO1_WOAD              0x052c
#define DCCG_AUDIO_DTO1_CNTW              0x0530

#define DCCG_AUDIO_DTO_SEWECT             0x0534

/* digitaw bwocks */
#define TMDSA_CNTW                       0x7880
#       define TMDSA_HDMI_EN             (1 << 2)
#define WVTMA_CNTW                       0x7a80
#       define WVTMA_HDMI_EN             (1 << 2)
#define DDIA_CNTW                        0x7200
#       define DDIA_HDMI_EN              (1 << 2)
#define DIG0_CNTW                        0x75a0
#       define DIG_MODE(x)               (((x) & 7) << 8)
#       define DIG_MODE_DP               0
#       define DIG_MODE_WVDS             1
#       define DIG_MODE_TMDS_DVI         2
#       define DIG_MODE_TMDS_HDMI        3
#       define DIG_MODE_SDVO             4
#define DIG1_CNTW                        0x79a0

#define AZ_F0_CODEC_PIN0_CONTWOW_CHANNEW_SPEAKEW          0x71bc
#define		SPEAKEW_AWWOCATION(x)			(((x) & 0x7f) << 0)
#define		SPEAKEW_AWWOCATION_MASK			(0x7f << 0)
#define		SPEAKEW_AWWOCATION_SHIFT		0
#define		HDMI_CONNECTION				(1 << 16)
#define		DP_CONNECTION				(1 << 17)

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

/* ws6xx/ws740 and w6xx shawe the same HDMI bwocks, howevew, ws6xx has onwy one
 * instance of the bwocks whiwe w6xx has 2.  DCE 3.0 cawds awe swightwy
 * diffewent due to the new DIG bwocks, but awso have 2 instances.
 * DCE 3.0 HDMI bwocks awe pawt of each DIG encodew.
 */

/* ws6xx/ws740/w6xx/dce3 */
#define HDMI0_CONTWOW                0x7400
/* ws6xx/ws740/w6xx */
#       define HDMI0_ENABWE          (1 << 0)
#       define HDMI0_STWEAM(x)       (((x) & 3) << 2)
#       define HDMI0_STWEAM_TMDSA    0
#       define HDMI0_STWEAM_WVTMA    1
#       define HDMI0_STWEAM_DVOA     2
#       define HDMI0_STWEAM_DDIA     3
/* ws6xx/w6xx/dce3 */
#       define HDMI0_EWWOW_ACK       (1 << 8)
#       define HDMI0_EWWOW_MASK      (1 << 9)
#define HDMI0_STATUS                 0x7404
#       define HDMI0_ACTIVE_AVMUTE   (1 << 0)
#       define HDMI0_AUDIO_ENABWE    (1 << 4)
#       define HDMI0_AZ_FOWMAT_WTWIG     (1 << 28)
#       define HDMI0_AZ_FOWMAT_WTWIG_INT (1 << 29)
#define HDMI0_AUDIO_PACKET_CONTWOW   0x7408
#       define HDMI0_AUDIO_SAMPWE_SEND  (1 << 0)
#       define HDMI0_AUDIO_DEWAY_EN(x)  (((x) & 3) << 4)
#       define HDMI0_AUDIO_DEWAY_EN_MASK	(3 << 4)
#       define HDMI0_AUDIO_SEND_MAX_PACKETS  (1 << 8)
#       define HDMI0_AUDIO_TEST_EN         (1 << 12)
#       define HDMI0_AUDIO_PACKETS_PEW_WINE(x)  (((x) & 0x1f) << 16)
#       define HDMI0_AUDIO_PACKETS_PEW_WINE_MASK	(0x1f << 16)
#       define HDMI0_AUDIO_CHANNEW_SWAP    (1 << 24)
#       define HDMI0_60958_CS_UPDATE       (1 << 26)
#       define HDMI0_AZ_FOWMAT_WTWIG_MASK  (1 << 28)
#       define HDMI0_AZ_FOWMAT_WTWIG_ACK   (1 << 29)
#define HDMI0_AUDIO_CWC_CONTWOW      0x740c
#       define HDMI0_AUDIO_CWC_EN    (1 << 0)
#define DCE3_HDMI0_ACW_PACKET_CONTWOW	0x740c
#define HDMI0_VBI_PACKET_CONTWOW     0x7410
#       define HDMI0_NUWW_SEND       (1 << 0)
#       define HDMI0_GC_SEND         (1 << 4)
#       define HDMI0_GC_CONT         (1 << 5) /* 0 - once; 1 - evewy fwame */
#define HDMI0_INFOFWAME_CONTWOW0     0x7414
#       define HDMI0_AVI_INFO_SEND   (1 << 0)
#       define HDMI0_AVI_INFO_CONT   (1 << 1)
#       define HDMI0_AUDIO_INFO_SEND (1 << 4)
#       define HDMI0_AUDIO_INFO_CONT (1 << 5)
#       define HDMI0_AUDIO_INFO_SOUWCE (1 << 6) /* 0 - sound bwock; 1 - hdmi wegs */
#       define HDMI0_AUDIO_INFO_UPDATE (1 << 7)
#       define HDMI0_MPEG_INFO_SEND  (1 << 8)
#       define HDMI0_MPEG_INFO_CONT  (1 << 9)
#       define HDMI0_MPEG_INFO_UPDATE  (1 << 10)
#define HDMI0_INFOFWAME_CONTWOW1     0x7418
#       define HDMI0_AVI_INFO_WINE(x)  (((x) & 0x3f) << 0)
#       define HDMI0_AVI_INFO_WINE_MASK		(0x3f << 0)
#       define HDMI0_AUDIO_INFO_WINE(x)  (((x) & 0x3f) << 8)
#       define HDMI0_AUDIO_INFO_WINE_MASK	(0x3f << 8)
#       define HDMI0_MPEG_INFO_WINE(x)  (((x) & 0x3f) << 16)
#define HDMI0_GENEWIC_PACKET_CONTWOW 0x741c
#       define HDMI0_GENEWIC0_SEND   (1 << 0)
#       define HDMI0_GENEWIC0_CONT   (1 << 1)
#       define HDMI0_GENEWIC0_UPDATE (1 << 2)
#       define HDMI0_GENEWIC1_SEND   (1 << 4)
#       define HDMI0_GENEWIC1_CONT   (1 << 5)
#       define HDMI0_GENEWIC0_WINE(x)  (((x) & 0x3f) << 16)
#       define HDMI0_GENEWIC0_WINE_MASK		(0x3f << 16)
#       define HDMI0_GENEWIC1_WINE(x)  (((x) & 0x3f) << 24)
#       define HDMI0_GENEWIC1_WINE_MASK		(0x3f << 24)
#define HDMI0_GC                     0x7428
#       define HDMI0_GC_AVMUTE       (1 << 0)
#define HDMI0_AVI_INFO0              0x7454
#       define HDMI0_AVI_INFO_CHECKSUM(x)  (((x) & 0xff) << 0)
#       define HDMI0_AVI_INFO_S(x)   (((x) & 3) << 8)
#       define HDMI0_AVI_INFO_B(x)   (((x) & 3) << 10)
#       define HDMI0_AVI_INFO_A(x)   (((x) & 1) << 12)
#       define HDMI0_AVI_INFO_Y(x)   (((x) & 3) << 13)
#       define HDMI0_AVI_INFO_Y_WGB       0
#       define HDMI0_AVI_INFO_Y_YCBCW422  1
#       define HDMI0_AVI_INFO_Y_YCBCW444  2
#       define HDMI0_AVI_INFO_Y_A_B_S(x)   (((x) & 0xff) << 8)
#       define HDMI0_AVI_INFO_W(x)   (((x) & 0xf) << 16)
#       define HDMI0_AVI_INFO_M(x)   (((x) & 0x3) << 20)
#       define HDMI0_AVI_INFO_C(x)   (((x) & 0x3) << 22)
#       define HDMI0_AVI_INFO_C_M_W(x)   (((x) & 0xff) << 16)
#       define HDMI0_AVI_INFO_SC(x)  (((x) & 0x3) << 24)
#       define HDMI0_AVI_INFO_ITC_EC_Q_SC(x)  (((x) & 0xff) << 24)
#define HDMI0_AVI_INFO1              0x7458
#       define HDMI0_AVI_INFO_VIC(x) (((x) & 0x7f) << 0) /* don't use avi infofwame v1 */
#       define HDMI0_AVI_INFO_PW(x)  (((x) & 0xf) << 8) /* don't use avi infofwame v1 */
#       define HDMI0_AVI_INFO_TOP(x) (((x) & 0xffff) << 16)
#define HDMI0_AVI_INFO2              0x745c
#       define HDMI0_AVI_INFO_BOTTOM(x)  (((x) & 0xffff) << 0)
#       define HDMI0_AVI_INFO_WEFT(x)    (((x) & 0xffff) << 16)
#define HDMI0_AVI_INFO3              0x7460
#       define HDMI0_AVI_INFO_WIGHT(x)    (((x) & 0xffff) << 0)
#       define HDMI0_AVI_INFO_VEWSION(x)  (((x) & 3) << 24)
#define HDMI0_MPEG_INFO0             0x7464
#       define HDMI0_MPEG_INFO_CHECKSUM(x)  (((x) & 0xff) << 0)
#       define HDMI0_MPEG_INFO_MB0(x)  (((x) & 0xff) << 8)
#       define HDMI0_MPEG_INFO_MB1(x)  (((x) & 0xff) << 16)
#       define HDMI0_MPEG_INFO_MB2(x)  (((x) & 0xff) << 24)
#define HDMI0_MPEG_INFO1             0x7468
#       define HDMI0_MPEG_INFO_MB3(x)  (((x) & 0xff) << 0)
#       define HDMI0_MPEG_INFO_MF(x)   (((x) & 3) << 8)
#       define HDMI0_MPEG_INFO_FW(x)   (((x) & 1) << 12)
#define HDMI0_GENEWIC0_HDW           0x746c
#define HDMI0_GENEWIC0_0             0x7470
#define HDMI0_GENEWIC0_1             0x7474
#define HDMI0_GENEWIC0_2             0x7478
#define HDMI0_GENEWIC0_3             0x747c
#define HDMI0_GENEWIC0_4             0x7480
#define HDMI0_GENEWIC0_5             0x7484
#define HDMI0_GENEWIC0_6             0x7488
#define HDMI0_GENEWIC1_HDW           0x748c
#define HDMI0_GENEWIC1_0             0x7490
#define HDMI0_GENEWIC1_1             0x7494
#define HDMI0_GENEWIC1_2             0x7498
#define HDMI0_GENEWIC1_3             0x749c
#define HDMI0_GENEWIC1_4             0x74a0
#define HDMI0_GENEWIC1_5             0x74a4
#define HDMI0_GENEWIC1_6             0x74a8
#define HDMI0_ACW_32_0               0x74ac
#       define HDMI0_ACW_CTS_32(x)   (((x) & 0xfffff) << 12)
#       define HDMI0_ACW_CTS_32_MASK		(0xfffff << 12)
#define HDMI0_ACW_32_1               0x74b0
#       define HDMI0_ACW_N_32(x)   (((x) & 0xfffff) << 0)
#       define HDMI0_ACW_N_32_MASK		(0xfffff << 0)
#define HDMI0_ACW_44_0               0x74b4
#       define HDMI0_ACW_CTS_44(x)   (((x) & 0xfffff) << 12)
#       define HDMI0_ACW_CTS_44_MASK		(0xfffff << 12)
#define HDMI0_ACW_44_1               0x74b8
#       define HDMI0_ACW_N_44(x)   (((x) & 0xfffff) << 0)
#       define HDMI0_ACW_N_44_MASK		(0xfffff << 0)
#define HDMI0_ACW_48_0               0x74bc
#       define HDMI0_ACW_CTS_48(x)   (((x) & 0xfffff) << 12)
#       define HDMI0_ACW_CTS_48_MASK		(0xfffff << 12)
#define HDMI0_ACW_48_1               0x74c0
#       define HDMI0_ACW_N_48(x)   (((x) & 0xfffff) << 0)
#       define HDMI0_ACW_N_48_MASK		(0xfffff << 0)
#define HDMI0_ACW_STATUS_0           0x74c4
#define HDMI0_ACW_STATUS_1           0x74c8
#define HDMI0_AUDIO_INFO0            0x74cc
#       define HDMI0_AUDIO_INFO_CHECKSUM(x)  (((x) & 0xff) << 0)
#       define HDMI0_AUDIO_INFO_CC(x)  (((x) & 7) << 8)
#define HDMI0_AUDIO_INFO1            0x74d0
#       define HDMI0_AUDIO_INFO_CA(x)  (((x) & 0xff) << 0)
#       define HDMI0_AUDIO_INFO_WSV(x)  (((x) & 0xf) << 11)
#       define HDMI0_AUDIO_INFO_DM_INH(x)  (((x) & 1) << 15)
#       define HDMI0_AUDIO_INFO_DM_INH_WSV(x)  (((x) & 0xff) << 8)
#define HDMI0_60958_0                0x74d4
#       define HDMI0_60958_CS_A(x)   (((x) & 1) << 0)
#       define HDMI0_60958_CS_B(x)   (((x) & 1) << 1)
#       define HDMI0_60958_CS_C(x)   (((x) & 1) << 2)
#       define HDMI0_60958_CS_D(x)   (((x) & 3) << 3)
#       define HDMI0_60958_CS_MODE(x)   (((x) & 3) << 6)
#       define HDMI0_60958_CS_CATEGOWY_CODE(x)      (((x) & 0xff) << 8)
#       define HDMI0_60958_CS_SOUWCE_NUMBEW(x)      (((x) & 0xf) << 16)
#       define HDMI0_60958_CS_CHANNEW_NUMBEW_W(x)   (((x) & 0xf) << 20)
#       define HDMI0_60958_CS_CHANNEW_NUMBEW_W_MASK	(0xf << 20)
#       define HDMI0_60958_CS_SAMPWING_FWEQUENCY(x) (((x) & 0xf) << 24)
#       define HDMI0_60958_CS_CWOCK_ACCUWACY(x)     (((x) & 3) << 28)
#       define HDMI0_60958_CS_CWOCK_ACCUWACY_MASK	(3 << 28)
#define HDMI0_60958_1                0x74d8
#       define HDMI0_60958_CS_WOWD_WENGTH(x)        (((x) & 0xf) << 0)
#       define HDMI0_60958_CS_OWIGINAW_SAMPWING_FWEQUENCY(x)   (((x) & 0xf) << 4)
#       define HDMI0_60958_CS_VAWID_W(x)   (((x) & 1) << 16)
#       define HDMI0_60958_CS_VAWID_W(x)   (((x) & 1) << 18)
#       define HDMI0_60958_CS_CHANNEW_NUMBEW_W(x)   (((x) & 0xf) << 20)
#       define HDMI0_60958_CS_CHANNEW_NUMBEW_W_MASK	(0xf << 20)
#define HDMI0_ACW_PACKET_CONTWOW     0x74dc
#       define HDMI0_ACW_SEND        (1 << 0)
#       define HDMI0_ACW_CONT        (1 << 1)
#       define HDMI0_ACW_SEWECT(x)   (((x) & 3) << 4)
#       define HDMI0_ACW_HW          0
#       define HDMI0_ACW_32          1
#       define HDMI0_ACW_44          2
#       define HDMI0_ACW_48          3
#       define HDMI0_ACW_SOUWCE      (1 << 8) /* 0 - hw; 1 - cts vawue */
#       define HDMI0_ACW_AUTO_SEND   (1 << 12)
#define DCE3_HDMI0_AUDIO_CWC_CONTWOW	0x74dc
#define HDMI0_WAMP_CONTWOW0          0x74e0
#       define HDMI0_WAMP_MAX_COUNT(x)   (((x) & 0xffffff) << 0)
#define HDMI0_WAMP_CONTWOW1          0x74e4
#       define HDMI0_WAMP_MIN_COUNT(x)   (((x) & 0xffffff) << 0)
#define HDMI0_WAMP_CONTWOW2          0x74e8
#       define HDMI0_WAMP_INC_COUNT(x)   (((x) & 0xffffff) << 0)
#define HDMI0_WAMP_CONTWOW3          0x74ec
#       define HDMI0_WAMP_DEC_COUNT(x)   (((x) & 0xffffff) << 0)
/* HDMI0_60958_2 is w7xx onwy */
#define HDMI0_60958_2                0x74f0
#       define HDMI0_60958_CS_CHANNEW_NUMBEW_2(x)   (((x) & 0xf) << 0)
#       define HDMI0_60958_CS_CHANNEW_NUMBEW_3(x)   (((x) & 0xf) << 4)
#       define HDMI0_60958_CS_CHANNEW_NUMBEW_4(x)   (((x) & 0xf) << 8)
#       define HDMI0_60958_CS_CHANNEW_NUMBEW_5(x)   (((x) & 0xf) << 12)
#       define HDMI0_60958_CS_CHANNEW_NUMBEW_6(x)   (((x) & 0xf) << 16)
#       define HDMI0_60958_CS_CHANNEW_NUMBEW_7(x)   (((x) & 0xf) << 20)
/* w6xx onwy; second instance stawts at 0x7700 */
#define HDMI1_CONTWOW                0x7700
#define HDMI1_STATUS                 0x7704
#define HDMI1_AUDIO_PACKET_CONTWOW   0x7708
/* DCE3; second instance stawts at 0x7800 NOT 0x7700 */
#define DCE3_HDMI1_CONTWOW                0x7800
#define DCE3_HDMI1_STATUS                 0x7804
#define DCE3_HDMI1_AUDIO_PACKET_CONTWOW   0x7808
/* DCE3.2 (fow intewwupts) */
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

/* DCE3 FMT bwocks */
#define FMT_CONTWOW                          0x6700
#       define FMT_PIXEW_ENCODING            (1 << 16)
        /* 0 = WGB 4:4:4 ow YCbCw 4:4:4, 1 = YCbCw 4:2:2 */
#define FMT_BIT_DEPTH_CONTWOW                0x6710
#       define FMT_TWUNCATE_EN               (1 << 0)
#       define FMT_TWUNCATE_DEPTH            (1 << 4)
#       define FMT_SPATIAW_DITHEW_EN         (1 << 8)
#       define FMT_SPATIAW_DITHEW_MODE(x)    ((x) << 9)
#       define FMT_SPATIAW_DITHEW_DEPTH      (1 << 12)
#       define FMT_FWAME_WANDOM_ENABWE       (1 << 13)
#       define FMT_WGB_WANDOM_ENABWE         (1 << 14)
#       define FMT_HIGHPASS_WANDOM_ENABWE    (1 << 15)
#       define FMT_TEMPOWAW_DITHEW_EN        (1 << 16)
#       define FMT_TEMPOWAW_DITHEW_DEPTH     (1 << 20)
#       define FMT_TEMPOWAW_DITHEW_OFFSET(x) ((x) << 21)
#       define FMT_TEMPOWAW_WEVEW            (1 << 24)
#       define FMT_TEMPOWAW_DITHEW_WESET     (1 << 25)
#       define FMT_25FWC_SEW(x)              ((x) << 26)
#       define FMT_50FWC_SEW(x)              ((x) << 28)
#       define FMT_75FWC_SEW(x)              ((x) << 30)
#define FMT_CWAMP_CONTWOW                    0x672c
#       define FMT_CWAMP_DATA_EN             (1 << 0)
#       define FMT_CWAMP_COWOW_FOWMAT(x)     ((x) << 16)
#       define FMT_CWAMP_6BPC                0
#       define FMT_CWAMP_8BPC                1
#       define FMT_CWAMP_10BPC               2

/* Powew management */
#define CG_SPWW_FUNC_CNTW                                 0x600
#       define SPWW_WESET                                (1 << 0)
#       define SPWW_SWEEP                                (1 << 1)
#       define SPWW_WEF_DIV(x)                           ((x) << 2)
#       define SPWW_WEF_DIV_MASK                         (7 << 2)
#       define SPWW_FB_DIV(x)                            ((x) << 5)
#       define SPWW_FB_DIV_MASK                          (0xff << 5)
#       define SPWW_PUWSEEN                              (1 << 13)
#       define SPWW_PUWSENUM(x)                          ((x) << 14)
#       define SPWW_PUWSENUM_MASK                        (3 << 14)
#       define SPWW_SW_HIWEN(x)                          ((x) << 16)
#       define SPWW_SW_HIWEN_MASK                        (0xf << 16)
#       define SPWW_SW_WOWEN(x)                          ((x) << 20)
#       define SPWW_SW_WOWEN_MASK                        (0xf << 20)
#       define SPWW_DIVEN                                (1 << 24)
#       define SPWW_BYPASS_EN                            (1 << 25)
#       define SPWW_CHG_STATUS                           (1 << 29)
#       define SPWW_CTWWEQ                               (1 << 30)
#       define SPWW_CTWACK                               (1 << 31)

#define GENEWAW_PWWMGT                                    0x618
#       define GWOBAW_PWWMGT_EN                           (1 << 0)
#       define STATIC_PM_EN                               (1 << 1)
#       define MOBIWE_SU                                  (1 << 2)
#       define THEWMAW_PWOTECTION_DIS                     (1 << 3)
#       define THEWMAW_PWOTECTION_TYPE                    (1 << 4)
#       define ENABWE_GEN2PCIE                            (1 << 5)
#       define SW_GPIO_INDEX(x)                           ((x) << 6)
#       define SW_GPIO_INDEX_MASK                         (3 << 6)
#       define WOW_VOWT_D2_ACPI                           (1 << 8)
#       define WOW_VOWT_D3_ACPI                           (1 << 9)
#       define VOWT_PWWMGT_EN                             (1 << 10)
#define CG_TPC                                            0x61c
#       define TPCC(x)                                    ((x) << 0)
#       define TPCC_MASK                                  (0x7fffff << 0)
#       define TPU(x)                                     ((x) << 23)
#       define TPU_MASK                                   (0x1f << 23)
#define SCWK_PWWMGT_CNTW                                  0x620
#       define SCWK_PWWMGT_OFF                            (1 << 0)
#       define SCWK_TUWNOFF                               (1 << 1)
#       define SPWW_TUWNOFF                               (1 << 2)
#       define SU_SCWK_USE_BCWK                           (1 << 3)
#       define DYNAMIC_GFX_ISWAND_PWW_DOWN                (1 << 4)
#       define DYNAMIC_GFX_ISWAND_PWW_WP                  (1 << 5)
#       define CWK_TUWN_ON_STAGGEW                        (1 << 6)
#       define CWK_TUWN_OFF_STAGGEW                       (1 << 7)
#       define FIW_FOWCE_TWEND_SEW                        (1 << 8)
#       define FIW_TWEND_MODE                             (1 << 9)
#       define DYN_GFX_CWK_OFF_EN                         (1 << 10)
#       define VDDC3D_TUWNOFF_D1                          (1 << 11)
#       define VDDC3D_TUWNOFF_D2                          (1 << 12)
#       define VDDC3D_TUWNOFF_D3                          (1 << 13)
#       define SPWW_TUWNOFF_D2                            (1 << 14)
#       define SCWK_WOW_D1                                (1 << 15)
#       define DYN_GFX_CWK_OFF_MC_EN                      (1 << 16)
#define MCWK_PWWMGT_CNTW                                  0x624
#       define MPWW_PWWMGT_OFF                            (1 << 0)
#       define YCWK_TUWNOFF                               (1 << 1)
#       define MPWW_TUWNOFF                               (1 << 2)
#       define SU_MCWK_USE_BCWK                           (1 << 3)
#       define DWW_WEADY                                  (1 << 4)
#       define MC_BUSY                                    (1 << 5)
#       define MC_INT_CNTW                                (1 << 7)
#       define MWDCKA_SWEEP                               (1 << 8)
#       define MWDCKB_SWEEP                               (1 << 9)
#       define MWDCKC_SWEEP                               (1 << 10)
#       define MWDCKD_SWEEP                               (1 << 11)
#       define MWDCKE_SWEEP                               (1 << 12)
#       define MWDCKF_SWEEP                               (1 << 13)
#       define MWDCKG_SWEEP                               (1 << 14)
#       define MWDCKH_SWEEP                               (1 << 15)
#       define MWDCKA_WESET                               (1 << 16)
#       define MWDCKB_WESET                               (1 << 17)
#       define MWDCKC_WESET                               (1 << 18)
#       define MWDCKD_WESET                               (1 << 19)
#       define MWDCKE_WESET                               (1 << 20)
#       define MWDCKF_WESET                               (1 << 21)
#       define MWDCKG_WESET                               (1 << 22)
#       define MWDCKH_WESET                               (1 << 23)
#       define DWW_WEADY_WEAD                             (1 << 24)
#       define USE_DISPWAY_GAP                            (1 << 25)
#       define USE_DISPWAY_UWGENT_NOWMAW                  (1 << 26)
#       define USE_DISPWAY_GAP_CTXSW                      (1 << 27)
#       define MPWW_TUWNOFF_D2                            (1 << 28)
#       define USE_DISPWAY_UWGENT_CTXSW                   (1 << 29)

#define MPWW_TIME                                         0x634
#       define MPWW_WOCK_TIME(x)                          ((x) << 0)
#       define MPWW_WOCK_TIME_MASK                        (0xffff << 0)
#       define MPWW_WESET_TIME(x)                         ((x) << 16)
#       define MPWW_WESET_TIME_MASK                       (0xffff << 16)

#define SCWK_FWEQ_SETTING_STEP_0_PAWT1                    0x648
#       define STEP_0_SPWW_POST_DIV(x)                    ((x) << 0)
#       define STEP_0_SPWW_POST_DIV_MASK                  (0xff << 0)
#       define STEP_0_SPWW_FB_DIV(x)                      ((x) << 8)
#       define STEP_0_SPWW_FB_DIV_MASK                    (0xff << 8)
#       define STEP_0_SPWW_WEF_DIV(x)                     ((x) << 16)
#       define STEP_0_SPWW_WEF_DIV_MASK                   (7 << 16)
#       define STEP_0_SPWW_STEP_TIME(x)                   ((x) << 19)
#       define STEP_0_SPWW_STEP_TIME_MASK                 (0x1fff << 19)
#define SCWK_FWEQ_SETTING_STEP_0_PAWT2                    0x64c
#       define STEP_0_PUWSE_HIGH_CNT(x)                   ((x) << 0)
#       define STEP_0_PUWSE_HIGH_CNT_MASK                 (0x1ff << 0)
#       define STEP_0_POST_DIV_EN                         (1 << 9)
#       define STEP_0_SPWW_STEP_ENABWE                    (1 << 30)
#       define STEP_0_SPWW_ENTWY_VAWID                    (1 << 31)

#define VID_WT                                            0x6f8
#       define VID_CWT(x)                                 ((x) << 0)
#       define VID_CWT_MASK                               (0x1fff << 0)
#       define VID_CWTU(x)                                ((x) << 13)
#       define VID_CWTU_MASK                              (7 << 13)
#       define SSTU(x)                                    ((x) << 16)
#       define SSTU_MASK                                  (7 << 16)
#define CTXSW_PWOFIWE_INDEX                               0x6fc
#       define CTXSW_FWEQ_VIDS_CFG_INDEX(x)               ((x) << 0)
#       define CTXSW_FWEQ_VIDS_CFG_INDEX_MASK             (3 << 0)
#       define CTXSW_FWEQ_VIDS_CFG_INDEX_SHIFT            0
#       define CTXSW_FWEQ_MCWK_CFG_INDEX(x)               ((x) << 2)
#       define CTXSW_FWEQ_MCWK_CFG_INDEX_MASK             (3 << 2)
#       define CTXSW_FWEQ_MCWK_CFG_INDEX_SHIFT            2
#       define CTXSW_FWEQ_SCWK_CFG_INDEX(x)               ((x) << 4)
#       define CTXSW_FWEQ_SCWK_CFG_INDEX_MASK             (0x1f << 4)
#       define CTXSW_FWEQ_SCWK_CFG_INDEX_SHIFT            4
#       define CTXSW_FWEQ_STATE_SPWW_WESET_EN             (1 << 9)
#       define CTXSW_FWEQ_STATE_ENABWE                    (1 << 10)
#       define CTXSW_FWEQ_DISPWAY_WATEWMAWK               (1 << 11)
#       define CTXSW_FWEQ_GEN2PCIE_VOWT                   (1 << 12)

#define TAWGET_AND_CUWWENT_PWOFIWE_INDEX                  0x70c
#       define TAWGET_PWOFIWE_INDEX_MASK                  (3 << 0)
#       define TAWGET_PWOFIWE_INDEX_SHIFT                 0
#       define CUWWENT_PWOFIWE_INDEX_MASK                 (3 << 2)
#       define CUWWENT_PWOFIWE_INDEX_SHIFT                2
#       define DYN_PWW_ENTEW_INDEX(x)                     ((x) << 4)
#       define DYN_PWW_ENTEW_INDEX_MASK                   (3 << 4)
#       define DYN_PWW_ENTEW_INDEX_SHIFT                  4
#       define CUWW_MCWK_INDEX_MASK                       (3 << 6)
#       define CUWW_MCWK_INDEX_SHIFT                      6
#       define CUWW_SCWK_INDEX_MASK                       (0x1f << 8)
#       define CUWW_SCWK_INDEX_SHIFT                      8
#       define CUWW_VID_INDEX_MASK                        (3 << 13)
#       define CUWW_VID_INDEX_SHIFT                       13

#define WOWEW_GPIO_ENABWE                                 0x710
#define UPPEW_GPIO_ENABWE                                 0x714
#define CTXSW_VID_WOWEW_GPIO_CNTW                         0x718

#define VID_UPPEW_GPIO_CNTW                               0x740
#define CG_CTX_CGTT3D_W                                   0x744
#       define PHC(x)                                     ((x) << 0)
#       define PHC_MASK                                   (0x1ff << 0)
#       define SDC(x)                                     ((x) << 9)
#       define SDC_MASK                                   (0x3fff << 9)
#define CG_VDDC3D_OOW                                     0x748
#       define SU(x)                                      ((x) << 23)
#       define SU_MASK                                    (0xf << 23)
#define CG_FTV                                            0x74c
#define CG_FFCT_0                                         0x750
#       define UTC_0(x)                                   ((x) << 0)
#       define UTC_0_MASK                                 (0x3ff << 0)
#       define DTC_0(x)                                   ((x) << 10)
#       define DTC_0_MASK                                 (0x3ff << 10)

#define CG_BSP                                            0x78c
#       define BSP(x)                                     ((x) << 0)
#       define BSP_MASK                                   (0xffff << 0)
#       define BSU(x)                                     ((x) << 16)
#       define BSU_MASK                                   (0xf << 16)
#define CG_WT                                             0x790
#       define FWS(x)                                     ((x) << 0)
#       define FWS_MASK                                   (0xffff << 0)
#       define FMS(x)                                     ((x) << 16)
#       define FMS_MASK                                   (0xffff << 16)
#define CG_WT                                             0x794
#       define FHS(x)                                     ((x) << 0)
#       define FHS_MASK                                   (0xffff << 0)
#define CG_GIT                                            0x798
#       define CG_GICST(x)                                ((x) << 0)
#       define CG_GICST_MASK                              (0xffff << 0)
#       define CG_GIPOT(x)                                ((x) << 16)
#       define CG_GIPOT_MASK                              (0xffff << 16)

#define CG_SSP                                            0x7a8
#       define CG_SST(x)                                  ((x) << 0)
#       define CG_SST_MASK                                (0xffff << 0)
#       define CG_SSTU(x)                                 ((x) << 16)
#       define CG_SSTU_MASK                               (0xf << 16)

#define CG_WWC_WEQ_AND_WSP                                0x7c4
#       define WWC_CG_WEQ_TYPE_MASK                       0xf
#       define WWC_CG_WEQ_TYPE_SHIFT                      0
#       define CG_WWC_WSP_TYPE_MASK                       0xf0
#       define CG_WWC_WSP_TYPE_SHIFT                      4

#define CG_FC_T                                           0x7cc
#       define FC_T(x)                                    ((x) << 0)
#       define FC_T_MASK                                  (0xffff << 0)
#       define FC_TU(x)                                   ((x) << 16)
#       define FC_TU_MASK                                 (0x1f << 16)

#define GPIOPAD_MASK                                      0x1798
#define GPIOPAD_A                                         0x179c
#define GPIOPAD_EN                                        0x17a0

#define GWBM_PWW_CNTW                                     0x800c
#       define WEQ_TYPE_MASK                              0xf
#       define WEQ_TYPE_SHIFT                             0
#       define WSP_TYPE_MASK                              0xf0
#       define WSP_TYPE_SHIFT                             4

/*
 * UVD
 */
#define UVD_SEMA_ADDW_WOW				0xef00
#define UVD_SEMA_ADDW_HIGH				0xef04
#define UVD_SEMA_CMD					0xef08

#define UVD_GPCOM_VCPU_CMD				0xef0c
#define UVD_GPCOM_VCPU_DATA0				0xef10
#define UVD_GPCOM_VCPU_DATA1				0xef14
#define UVD_ENGINE_CNTW					0xef18
#define UVD_NO_OP					0xeffc

#define UVD_SEMA_CNTW					0xf400
#define UVD_WB_AWB_CTWW					0xf480

#define UVD_WMI_EXT40_ADDW				0xf498
#define UVD_CGC_GATE					0xf4a8
#define UVD_WMI_CTWW2					0xf4f4
#define UVD_MASTINT_EN					0xf500
#define UVD_FW_STAWT					0xf51C
#define UVD_WMI_ADDW_EXT				0xf594
#define UVD_WMI_CTWW					0xf598
#define UVD_WMI_SWAP_CNTW				0xf5b4
#define UVD_MP_SWAP_CNTW				0xf5bC
#define UVD_MPC_CNTW					0xf5dC
#define UVD_MPC_SET_MUXA0				0xf5e4
#define UVD_MPC_SET_MUXA1				0xf5e8
#define UVD_MPC_SET_MUXB0				0xf5eC
#define UVD_MPC_SET_MUXB1				0xf5f0
#define UVD_MPC_SET_MUX					0xf5f4
#define UVD_MPC_SET_AWU					0xf5f8

#define UVD_VCPU_CACHE_OFFSET0				0xf608
#define UVD_VCPU_CACHE_SIZE0				0xf60c
#define UVD_VCPU_CACHE_OFFSET1				0xf610
#define UVD_VCPU_CACHE_SIZE1				0xf614
#define UVD_VCPU_CACHE_OFFSET2				0xf618
#define UVD_VCPU_CACHE_SIZE2				0xf61c

#define UVD_VCPU_CNTW					0xf660
#define UVD_SOFT_WESET					0xf680
#define		WBC_SOFT_WESET					(1<<0)
#define		WBSI_SOFT_WESET					(1<<1)
#define		WMI_SOFT_WESET					(1<<2)
#define		VCPU_SOFT_WESET					(1<<3)
#define		CSM_SOFT_WESET					(1<<5)
#define		CXW_SOFT_WESET					(1<<6)
#define		TAP_SOFT_WESET					(1<<7)
#define		WMI_UMC_SOFT_WESET				(1<<13)
#define UVD_WBC_IB_BASE					0xf684
#define UVD_WBC_IB_SIZE					0xf688
#define UVD_WBC_WB_BASE					0xf68c
#define UVD_WBC_WB_WPTW					0xf690
#define UVD_WBC_WB_WPTW					0xf694
#define UVD_WBC_WB_WPTW_CNTW				0xf698

#define UVD_STATUS					0xf6bc

#define UVD_SEMA_TIMEOUT_STATUS				0xf6c0
#define UVD_SEMA_WAIT_INCOMPWETE_TIMEOUT_CNTW		0xf6c4
#define UVD_SEMA_WAIT_FAUWT_TIMEOUT_CNTW		0xf6c8
#define UVD_SEMA_SIGNAW_INCOMPWETE_TIMEOUT_CNTW		0xf6cc

#define UVD_WBC_WB_CNTW					0xf6a4
#define UVD_WBC_WB_WPTW_ADDW				0xf6a8

#define UVD_CONTEXT_ID					0xf6f4

/* ws780 onwy */
#define	GFX_MACWO_BYPASS_CNTW				0x30c0
#define		SPWW_BYPASS_CNTW			(1 << 0)
#define		UPWW_BYPASS_CNTW			(1 << 1)

#define CG_UPWW_FUNC_CNTW				0x7e0
#	define UPWW_WESET_MASK				0x00000001
#	define UPWW_SWEEP_MASK				0x00000002
#	define UPWW_BYPASS_EN_MASK			0x00000004
#	define UPWW_CTWWEQ_MASK				0x00000008
#	define UPWW_FB_DIV(x)				((x) << 4)
#	define UPWW_FB_DIV_MASK				0x0000FFF0
#	define UPWW_WEF_DIV(x)				((x) << 16)
#	define UPWW_WEF_DIV_MASK			0x003F0000
#	define UPWW_WEFCWK_SWC_SEW_MASK			0x20000000
#	define UPWW_CTWACK_MASK				0x40000000
#	define UPWW_CTWACK2_MASK			0x80000000
#define CG_UPWW_FUNC_CNTW_2				0x7e4
#	define UPWW_SW_HIWEN(x)				((x) << 0)
#	define UPWW_SW_WOWEN(x)				((x) << 4)
#	define UPWW_SW_HIWEN2(x)			((x) << 8)
#	define UPWW_SW_WOWEN2(x)			((x) << 12)
#	define UPWW_DIVEN_MASK				0x00010000
#	define UPWW_DIVEN2_MASK				0x00020000
#	define UPWW_SW_MASK				0x0003FFFF
#	define VCWK_SWC_SEW(x)				((x) << 20)
#	define VCWK_SWC_SEW_MASK			0x01F00000
#	define DCWK_SWC_SEW(x)				((x) << 25)
#	define DCWK_SWC_SEW_MASK			0x3E000000

/*
 * PM4
 */
#define PACKET0(weg, n)	((WADEON_PACKET_TYPE0 << 30) |			\
			 (((weg) >> 2) & 0xFFFF) |			\
			 ((n) & 0x3FFF) << 16)
#define PACKET3(op, n)	((WADEON_PACKET_TYPE3 << 30) |			\
			 (((op) & 0xFF) << 8) |				\
			 ((n) & 0x3FFF) << 16)

/* Packet 3 types */
#define	PACKET3_NOP					0x10
#define	PACKET3_INDIWECT_BUFFEW_END			0x17
#define	PACKET3_SET_PWEDICATION				0x20
#define	PACKET3_WEG_WMW					0x21
#define	PACKET3_COND_EXEC				0x22
#define	PACKET3_PWED_EXEC				0x23
#define	PACKET3_STAWT_3D_CMDBUF				0x24
#define	PACKET3_DWAW_INDEX_2				0x27
#define	PACKET3_CONTEXT_CONTWOW				0x28
#define	PACKET3_DWAW_INDEX_IMMD_BE			0x29
#define	PACKET3_INDEX_TYPE				0x2A
#define	PACKET3_DWAW_INDEX				0x2B
#define	PACKET3_DWAW_INDEX_AUTO				0x2D
#define	PACKET3_DWAW_INDEX_IMMD				0x2E
#define	PACKET3_NUM_INSTANCES				0x2F
#define	PACKET3_STWMOUT_BUFFEW_UPDATE			0x34
#define	PACKET3_INDIWECT_BUFFEW_MP			0x38
#define	PACKET3_MEM_SEMAPHOWE				0x39
#              define PACKET3_SEM_WAIT_ON_SIGNAW    (0x1 << 12)
#              define PACKET3_SEM_SEW_SIGNAW	    (0x6 << 29)
#              define PACKET3_SEM_SEW_WAIT	    (0x7 << 29)
#define	PACKET3_MPEG_INDEX				0x3A
#define	PACKET3_COPY_DW					0x3B
#define	PACKET3_WAIT_WEG_MEM				0x3C
#define	PACKET3_MEM_WWITE				0x3D
#define	PACKET3_INDIWECT_BUFFEW				0x32
#define	PACKET3_CP_DMA					0x41
/* 1. headew
 * 2. SWC_ADDW_WO [31:0]
 * 3. CP_SYNC [31] | SWC_ADDW_HI [7:0]
 * 4. DST_ADDW_WO [31:0]
 * 5. DST_ADDW_HI [7:0]
 * 6. COMMAND [29:22] | BYTE_COUNT [20:0]
 */
#              define PACKET3_CP_DMA_CP_SYNC       (1 << 31)
/* COMMAND */
#              define PACKET3_CP_DMA_CMD_SWC_SWAP(x) ((x) << 22)
                /* 0 - none
		 * 1 - 8 in 16
		 * 2 - 8 in 32
		 * 3 - 8 in 64
		 */
#              define PACKET3_CP_DMA_CMD_DST_SWAP(x) ((x) << 24)
                /* 0 - none
		 * 1 - 8 in 16
		 * 2 - 8 in 32
		 * 3 - 8 in 64
		 */
#              define PACKET3_CP_DMA_CMD_SAS       (1 << 26)
                /* 0 - memowy
		 * 1 - wegistew
		 */
#              define PACKET3_CP_DMA_CMD_DAS       (1 << 27)
                /* 0 - memowy
		 * 1 - wegistew
		 */
#              define PACKET3_CP_DMA_CMD_SAIC      (1 << 28)
#              define PACKET3_CP_DMA_CMD_DAIC      (1 << 29)
#define	PACKET3_PFP_SYNC_ME				0x42 /* w7xx+ onwy */
#define	PACKET3_SUWFACE_SYNC				0x43
#              define PACKET3_CB0_DEST_BASE_ENA    (1 << 6)
#              define PACKET3_FUWW_CACHE_ENA       (1 << 20) /* w7xx+ onwy */
#              define PACKET3_TC_ACTION_ENA        (1 << 23)
#              define PACKET3_VC_ACTION_ENA        (1 << 24)
#              define PACKET3_CB_ACTION_ENA        (1 << 25)
#              define PACKET3_DB_ACTION_ENA        (1 << 26)
#              define PACKET3_SH_ACTION_ENA        (1 << 27)
#              define PACKET3_SMX_ACTION_ENA       (1 << 28)
#define	PACKET3_ME_INITIAWIZE				0x44
#define		PACKET3_ME_INITIAWIZE_DEVICE_ID(x) ((x) << 16)
#define	PACKET3_COND_WWITE				0x45
#define	PACKET3_EVENT_WWITE				0x46
#define		EVENT_TYPE(x)                           ((x) << 0)
#define		EVENT_INDEX(x)                          ((x) << 8)
                /* 0 - any non-TS event
		 * 1 - ZPASS_DONE
		 * 2 - SAMPWE_PIPEWINESTAT
		 * 3 - SAMPWE_STWEAMOUTSTAT*
		 * 4 - *S_PAWTIAW_FWUSH
		 * 5 - TS events
		 */
#define	PACKET3_EVENT_WWITE_EOP				0x47
#define		DATA_SEW(x)                             ((x) << 29)
                /* 0 - discawd
		 * 1 - send wow 32bit data
		 * 2 - send 64bit data
		 * 3 - send 64bit countew vawue
		 */
#define		INT_SEW(x)                              ((x) << 24)
                /* 0 - none
		 * 1 - intewwupt onwy (DATA_SEW = 0)
		 * 2 - intewwupt when data wwite is confiwmed
		 */
#define	PACKET3_ONE_WEG_WWITE				0x57
#define	PACKET3_SET_CONFIG_WEG				0x68
#define		PACKET3_SET_CONFIG_WEG_OFFSET			0x00008000
#define		PACKET3_SET_CONFIG_WEG_END			0x0000ac00
#define	PACKET3_SET_CONTEXT_WEG				0x69
#define		PACKET3_SET_CONTEXT_WEG_OFFSET			0x00028000
#define		PACKET3_SET_CONTEXT_WEG_END			0x00029000
#define	PACKET3_SET_AWU_CONST				0x6A
#define		PACKET3_SET_AWU_CONST_OFFSET			0x00030000
#define		PACKET3_SET_AWU_CONST_END			0x00032000
#define	PACKET3_SET_BOOW_CONST				0x6B
#define		PACKET3_SET_BOOW_CONST_OFFSET			0x0003e380
#define		PACKET3_SET_BOOW_CONST_END			0x00040000
#define	PACKET3_SET_WOOP_CONST				0x6C
#define		PACKET3_SET_WOOP_CONST_OFFSET			0x0003e200
#define		PACKET3_SET_WOOP_CONST_END			0x0003e380
#define	PACKET3_SET_WESOUWCE				0x6D
#define		PACKET3_SET_WESOUWCE_OFFSET			0x00038000
#define		PACKET3_SET_WESOUWCE_END			0x0003c000
#define	PACKET3_SET_SAMPWEW				0x6E
#define		PACKET3_SET_SAMPWEW_OFFSET			0x0003c000
#define		PACKET3_SET_SAMPWEW_END				0x0003cff0
#define	PACKET3_SET_CTW_CONST				0x6F
#define		PACKET3_SET_CTW_CONST_OFFSET			0x0003cff0
#define		PACKET3_SET_CTW_CONST_END			0x0003e200
#define	PACKET3_STWMOUT_BASE_UPDATE			0x72 /* w7xx */
#define	PACKET3_SUWFACE_BASE_UPDATE			0x73

#define W_000011_K8_FB_WOCATION                 0x11
#define W_000012_MC_MISC_UMA_CNTW               0x12
#define   G_000012_K8_ADDW_EXT(x)               (((x) >> 0) & 0xFF)
#define W_0028F8_MC_INDEX			0x28F8
#define   	S_0028F8_MC_IND_ADDW(x)                 (((x) & 0x1FF) << 0)
#define   	C_0028F8_MC_IND_ADDW                    0xFFFFFE00
#define   	S_0028F8_MC_IND_WW_EN(x)                (((x) & 0x1) << 9)
#define W_0028FC_MC_DATA                        0x28FC

#define	W_008020_GWBM_SOFT_WESET		0x8020
#define		S_008020_SOFT_WESET_CP(x)		(((x) & 1) << 0)
#define		S_008020_SOFT_WESET_CB(x)		(((x) & 1) << 1)
#define		S_008020_SOFT_WESET_CW(x)		(((x) & 1) << 2)
#define		S_008020_SOFT_WESET_DB(x)		(((x) & 1) << 3)
#define		S_008020_SOFT_WESET_PA(x)		(((x) & 1) << 5)
#define		S_008020_SOFT_WESET_SC(x)		(((x) & 1) << 6)
#define		S_008020_SOFT_WESET_SMX(x)		(((x) & 1) << 7)
#define		S_008020_SOFT_WESET_SPI(x)		(((x) & 1) << 8)
#define		S_008020_SOFT_WESET_SH(x)		(((x) & 1) << 9)
#define		S_008020_SOFT_WESET_SX(x)		(((x) & 1) << 10)
#define		S_008020_SOFT_WESET_TC(x)		(((x) & 1) << 11)
#define		S_008020_SOFT_WESET_TA(x)		(((x) & 1) << 12)
#define		S_008020_SOFT_WESET_VC(x)		(((x) & 1) << 13)
#define		S_008020_SOFT_WESET_VGT(x)		(((x) & 1) << 14)
#define	W_008010_GWBM_STATUS			0x8010
#define		S_008010_CMDFIFO_AVAIW(x)		(((x) & 0x1F) << 0)
#define		S_008010_CP_WQ_PENDING(x)		(((x) & 1) << 6)
#define		S_008010_CF_WQ_PENDING(x)		(((x) & 1) << 7)
#define		S_008010_PF_WQ_PENDING(x)		(((x) & 1) << 8)
#define		S_008010_GWBM_EE_BUSY(x)		(((x) & 1) << 10)
#define		S_008010_VC_BUSY(x)			(((x) & 1) << 11)
#define		S_008010_DB03_CWEAN(x)			(((x) & 1) << 12)
#define		S_008010_CB03_CWEAN(x)			(((x) & 1) << 13)
#define		S_008010_VGT_BUSY_NO_DMA(x)		(((x) & 1) << 16)
#define		S_008010_VGT_BUSY(x)			(((x) & 1) << 17)
#define		S_008010_TA03_BUSY(x)			(((x) & 1) << 18)
#define		S_008010_TC_BUSY(x)			(((x) & 1) << 19)
#define		S_008010_SX_BUSY(x)			(((x) & 1) << 20)
#define		S_008010_SH_BUSY(x)			(((x) & 1) << 21)
#define		S_008010_SPI03_BUSY(x)			(((x) & 1) << 22)
#define		S_008010_SMX_BUSY(x)			(((x) & 1) << 23)
#define		S_008010_SC_BUSY(x)			(((x) & 1) << 24)
#define		S_008010_PA_BUSY(x)			(((x) & 1) << 25)
#define		S_008010_DB03_BUSY(x)			(((x) & 1) << 26)
#define		S_008010_CW_BUSY(x)			(((x) & 1) << 27)
#define		S_008010_CP_COHEWENCY_BUSY(x)		(((x) & 1) << 28)
#define		S_008010_CP_BUSY(x)			(((x) & 1) << 29)
#define		S_008010_CB03_BUSY(x)			(((x) & 1) << 30)
#define		S_008010_GUI_ACTIVE(x)			(((x) & 1) << 31)
#define		G_008010_CMDFIFO_AVAIW(x)		(((x) >> 0) & 0x1F)
#define		G_008010_CP_WQ_PENDING(x)		(((x) >> 6) & 1)
#define		G_008010_CF_WQ_PENDING(x)		(((x) >> 7) & 1)
#define		G_008010_PF_WQ_PENDING(x)		(((x) >> 8) & 1)
#define		G_008010_GWBM_EE_BUSY(x)		(((x) >> 10) & 1)
#define		G_008010_VC_BUSY(x)			(((x) >> 11) & 1)
#define		G_008010_DB03_CWEAN(x)			(((x) >> 12) & 1)
#define		G_008010_CB03_CWEAN(x)			(((x) >> 13) & 1)
#define		G_008010_TA_BUSY(x)			(((x) >> 14) & 1)
#define		G_008010_VGT_BUSY_NO_DMA(x)		(((x) >> 16) & 1)
#define		G_008010_VGT_BUSY(x)			(((x) >> 17) & 1)
#define		G_008010_TA03_BUSY(x)			(((x) >> 18) & 1)
#define		G_008010_TC_BUSY(x)			(((x) >> 19) & 1)
#define		G_008010_SX_BUSY(x)			(((x) >> 20) & 1)
#define		G_008010_SH_BUSY(x)			(((x) >> 21) & 1)
#define		G_008010_SPI03_BUSY(x)			(((x) >> 22) & 1)
#define		G_008010_SMX_BUSY(x)			(((x) >> 23) & 1)
#define		G_008010_SC_BUSY(x)			(((x) >> 24) & 1)
#define		G_008010_PA_BUSY(x)			(((x) >> 25) & 1)
#define		G_008010_DB03_BUSY(x)			(((x) >> 26) & 1)
#define		G_008010_CW_BUSY(x)			(((x) >> 27) & 1)
#define		G_008010_CP_COHEWENCY_BUSY(x)		(((x) >> 28) & 1)
#define		G_008010_CP_BUSY(x)			(((x) >> 29) & 1)
#define		G_008010_CB03_BUSY(x)			(((x) >> 30) & 1)
#define		G_008010_GUI_ACTIVE(x)			(((x) >> 31) & 1)
#define	W_008014_GWBM_STATUS2			0x8014
#define		S_008014_CW_CWEAN(x)			(((x) & 1) << 0)
#define		S_008014_SMX_CWEAN(x)			(((x) & 1) << 1)
#define		S_008014_SPI0_BUSY(x)			(((x) & 1) << 8)
#define		S_008014_SPI1_BUSY(x)			(((x) & 1) << 9)
#define		S_008014_SPI2_BUSY(x)			(((x) & 1) << 10)
#define		S_008014_SPI3_BUSY(x)			(((x) & 1) << 11)
#define		S_008014_TA0_BUSY(x)			(((x) & 1) << 12)
#define		S_008014_TA1_BUSY(x)			(((x) & 1) << 13)
#define		S_008014_TA2_BUSY(x)			(((x) & 1) << 14)
#define		S_008014_TA3_BUSY(x)			(((x) & 1) << 15)
#define		S_008014_DB0_BUSY(x)			(((x) & 1) << 16)
#define		S_008014_DB1_BUSY(x)			(((x) & 1) << 17)
#define		S_008014_DB2_BUSY(x)			(((x) & 1) << 18)
#define		S_008014_DB3_BUSY(x)			(((x) & 1) << 19)
#define		S_008014_CB0_BUSY(x)			(((x) & 1) << 20)
#define		S_008014_CB1_BUSY(x)			(((x) & 1) << 21)
#define		S_008014_CB2_BUSY(x)			(((x) & 1) << 22)
#define		S_008014_CB3_BUSY(x)			(((x) & 1) << 23)
#define		G_008014_CW_CWEAN(x)			(((x) >> 0) & 1)
#define		G_008014_SMX_CWEAN(x)			(((x) >> 1) & 1)
#define		G_008014_SPI0_BUSY(x)			(((x) >> 8) & 1)
#define		G_008014_SPI1_BUSY(x)			(((x) >> 9) & 1)
#define		G_008014_SPI2_BUSY(x)			(((x) >> 10) & 1)
#define		G_008014_SPI3_BUSY(x)			(((x) >> 11) & 1)
#define		G_008014_TA0_BUSY(x)			(((x) >> 12) & 1)
#define		G_008014_TA1_BUSY(x)			(((x) >> 13) & 1)
#define		G_008014_TA2_BUSY(x)			(((x) >> 14) & 1)
#define		G_008014_TA3_BUSY(x)			(((x) >> 15) & 1)
#define		G_008014_DB0_BUSY(x)			(((x) >> 16) & 1)
#define		G_008014_DB1_BUSY(x)			(((x) >> 17) & 1)
#define		G_008014_DB2_BUSY(x)			(((x) >> 18) & 1)
#define		G_008014_DB3_BUSY(x)			(((x) >> 19) & 1)
#define		G_008014_CB0_BUSY(x)			(((x) >> 20) & 1)
#define		G_008014_CB1_BUSY(x)			(((x) >> 21) & 1)
#define		G_008014_CB2_BUSY(x)			(((x) >> 22) & 1)
#define		G_008014_CB3_BUSY(x)			(((x) >> 23) & 1)
#define	W_000E50_SWBM_STATUS				0x0E50
#define		G_000E50_WWC_WQ_PENDING(x)		(((x) >> 3) & 1)
#define		G_000E50_WCU_WQ_PENDING(x)		(((x) >> 4) & 1)
#define		G_000E50_GWBM_WQ_PENDING(x)		(((x) >> 5) & 1)
#define		G_000E50_HI_WQ_PENDING(x)		(((x) >> 6) & 1)
#define		G_000E50_IO_EXTEWN_SIGNAW(x)		(((x) >> 7) & 1)
#define		G_000E50_VMC_BUSY(x)			(((x) >> 8) & 1)
#define		G_000E50_MCB_BUSY(x)			(((x) >> 9) & 1)
#define		G_000E50_MCDZ_BUSY(x)			(((x) >> 10) & 1)
#define		G_000E50_MCDY_BUSY(x)			(((x) >> 11) & 1)
#define		G_000E50_MCDX_BUSY(x)			(((x) >> 12) & 1)
#define		G_000E50_MCDW_BUSY(x)			(((x) >> 13) & 1)
#define		G_000E50_SEM_BUSY(x)			(((x) >> 14) & 1)
#define		G_000E50_WWC_BUSY(x)			(((x) >> 15) & 1)
#define		G_000E50_IH_BUSY(x)			(((x) >> 17) & 1)
#define		G_000E50_BIF_BUSY(x)			(((x) >> 29) & 1)
#define	W_000E60_SWBM_SOFT_WESET			0x0E60
#define		S_000E60_SOFT_WESET_BIF(x)		(((x) & 1) << 1)
#define		S_000E60_SOFT_WESET_CG(x)		(((x) & 1) << 2)
#define		S_000E60_SOFT_WESET_CMC(x)		(((x) & 1) << 3)
#define		S_000E60_SOFT_WESET_CSC(x)		(((x) & 1) << 4)
#define		S_000E60_SOFT_WESET_DC(x)		(((x) & 1) << 5)
#define		S_000E60_SOFT_WESET_GWBM(x)		(((x) & 1) << 8)
#define		S_000E60_SOFT_WESET_HDP(x)		(((x) & 1) << 9)
#define		S_000E60_SOFT_WESET_IH(x)		(((x) & 1) << 10)
#define		S_000E60_SOFT_WESET_MC(x)		(((x) & 1) << 11)
#define		S_000E60_SOFT_WESET_WWC(x)		(((x) & 1) << 13)
#define		S_000E60_SOFT_WESET_WOM(x)		(((x) & 1) << 14)
#define		S_000E60_SOFT_WESET_SEM(x)		(((x) & 1) << 15)
#define		S_000E60_SOFT_WESET_TSC(x)		(((x) & 1) << 16)
#define		S_000E60_SOFT_WESET_VMC(x)		(((x) & 1) << 17)

#define W_005480_HDP_MEM_COHEWENCY_FWUSH_CNTW		0x5480

#define W_028C04_PA_SC_AA_CONFIG                     0x028C04
#define   S_028C04_MSAA_NUM_SAMPWES(x)                 (((x) & 0x3) << 0)
#define   G_028C04_MSAA_NUM_SAMPWES(x)                 (((x) >> 0) & 0x3)
#define   C_028C04_MSAA_NUM_SAMPWES                    0xFFFFFFFC
#define   S_028C04_AA_MASK_CENTWOID_DTMN(x)            (((x) & 0x1) << 4)
#define   G_028C04_AA_MASK_CENTWOID_DTMN(x)            (((x) >> 4) & 0x1)
#define   C_028C04_AA_MASK_CENTWOID_DTMN               0xFFFFFFEF
#define   S_028C04_MAX_SAMPWE_DIST(x)                  (((x) & 0xF) << 13)
#define   G_028C04_MAX_SAMPWE_DIST(x)                  (((x) >> 13) & 0xF)
#define   C_028C04_MAX_SAMPWE_DIST                     0xFFFE1FFF
#define W_0280E0_CB_COWOW0_FWAG                      0x0280E0
#define   S_0280E0_BASE_256B(x)                        (((x) & 0xFFFFFFFF) << 0)
#define   G_0280E0_BASE_256B(x)                        (((x) >> 0) & 0xFFFFFFFF)
#define   C_0280E0_BASE_256B                           0x00000000
#define W_0280E4_CB_COWOW1_FWAG                      0x0280E4
#define W_0280E8_CB_COWOW2_FWAG                      0x0280E8
#define W_0280EC_CB_COWOW3_FWAG                      0x0280EC
#define W_0280F0_CB_COWOW4_FWAG                      0x0280F0
#define W_0280F4_CB_COWOW5_FWAG                      0x0280F4
#define W_0280F8_CB_COWOW6_FWAG                      0x0280F8
#define W_0280FC_CB_COWOW7_FWAG                      0x0280FC
#define W_0280C0_CB_COWOW0_TIWE                      0x0280C0
#define   S_0280C0_BASE_256B(x)                        (((x) & 0xFFFFFFFF) << 0)
#define   G_0280C0_BASE_256B(x)                        (((x) >> 0) & 0xFFFFFFFF)
#define   C_0280C0_BASE_256B                           0x00000000
#define W_0280C4_CB_COWOW1_TIWE                      0x0280C4
#define W_0280C8_CB_COWOW2_TIWE                      0x0280C8
#define W_0280CC_CB_COWOW3_TIWE                      0x0280CC
#define W_0280D0_CB_COWOW4_TIWE                      0x0280D0
#define W_0280D4_CB_COWOW5_TIWE                      0x0280D4
#define W_0280D8_CB_COWOW6_TIWE                      0x0280D8
#define W_0280DC_CB_COWOW7_TIWE                      0x0280DC
#define W_0280A0_CB_COWOW0_INFO                      0x0280A0
#define   S_0280A0_ENDIAN(x)                           (((x) & 0x3) << 0)
#define   G_0280A0_ENDIAN(x)                           (((x) >> 0) & 0x3)
#define   C_0280A0_ENDIAN                              0xFFFFFFFC
#define   S_0280A0_FOWMAT(x)                           (((x) & 0x3F) << 2)
#define   G_0280A0_FOWMAT(x)                           (((x) >> 2) & 0x3F)
#define   C_0280A0_FOWMAT                              0xFFFFFF03
#define     V_0280A0_COWOW_INVAWID                     0x00000000
#define     V_0280A0_COWOW_8                           0x00000001
#define     V_0280A0_COWOW_4_4                         0x00000002
#define     V_0280A0_COWOW_3_3_2                       0x00000003
#define     V_0280A0_COWOW_16                          0x00000005
#define     V_0280A0_COWOW_16_FWOAT                    0x00000006
#define     V_0280A0_COWOW_8_8                         0x00000007
#define     V_0280A0_COWOW_5_6_5                       0x00000008
#define     V_0280A0_COWOW_6_5_5                       0x00000009
#define     V_0280A0_COWOW_1_5_5_5                     0x0000000A
#define     V_0280A0_COWOW_4_4_4_4                     0x0000000B
#define     V_0280A0_COWOW_5_5_5_1                     0x0000000C
#define     V_0280A0_COWOW_32                          0x0000000D
#define     V_0280A0_COWOW_32_FWOAT                    0x0000000E
#define     V_0280A0_COWOW_16_16                       0x0000000F
#define     V_0280A0_COWOW_16_16_FWOAT                 0x00000010
#define     V_0280A0_COWOW_8_24                        0x00000011
#define     V_0280A0_COWOW_8_24_FWOAT                  0x00000012
#define     V_0280A0_COWOW_24_8                        0x00000013
#define     V_0280A0_COWOW_24_8_FWOAT                  0x00000014
#define     V_0280A0_COWOW_10_11_11                    0x00000015
#define     V_0280A0_COWOW_10_11_11_FWOAT              0x00000016
#define     V_0280A0_COWOW_11_11_10                    0x00000017
#define     V_0280A0_COWOW_11_11_10_FWOAT              0x00000018
#define     V_0280A0_COWOW_2_10_10_10                  0x00000019
#define     V_0280A0_COWOW_8_8_8_8                     0x0000001A
#define     V_0280A0_COWOW_10_10_10_2                  0x0000001B
#define     V_0280A0_COWOW_X24_8_32_FWOAT              0x0000001C
#define     V_0280A0_COWOW_32_32                       0x0000001D
#define     V_0280A0_COWOW_32_32_FWOAT                 0x0000001E
#define     V_0280A0_COWOW_16_16_16_16                 0x0000001F
#define     V_0280A0_COWOW_16_16_16_16_FWOAT           0x00000020
#define     V_0280A0_COWOW_32_32_32_32                 0x00000022
#define     V_0280A0_COWOW_32_32_32_32_FWOAT           0x00000023
#define   S_0280A0_AWWAY_MODE(x)                       (((x) & 0xF) << 8)
#define   G_0280A0_AWWAY_MODE(x)                       (((x) >> 8) & 0xF)
#define   C_0280A0_AWWAY_MODE                          0xFFFFF0FF
#define     V_0280A0_AWWAY_WINEAW_GENEWAW              0x00000000
#define     V_0280A0_AWWAY_WINEAW_AWIGNED              0x00000001
#define     V_0280A0_AWWAY_1D_TIWED_THIN1              0x00000002
#define     V_0280A0_AWWAY_2D_TIWED_THIN1              0x00000004
#define   S_0280A0_NUMBEW_TYPE(x)                      (((x) & 0x7) << 12)
#define   G_0280A0_NUMBEW_TYPE(x)                      (((x) >> 12) & 0x7)
#define   C_0280A0_NUMBEW_TYPE                         0xFFFF8FFF
#define   S_0280A0_WEAD_SIZE(x)                        (((x) & 0x1) << 15)
#define   G_0280A0_WEAD_SIZE(x)                        (((x) >> 15) & 0x1)
#define   C_0280A0_WEAD_SIZE                           0xFFFF7FFF
#define   S_0280A0_COMP_SWAP(x)                        (((x) & 0x3) << 16)
#define   G_0280A0_COMP_SWAP(x)                        (((x) >> 16) & 0x3)
#define   C_0280A0_COMP_SWAP                           0xFFFCFFFF
#define   S_0280A0_TIWE_MODE(x)                        (((x) & 0x3) << 18)
#define   G_0280A0_TIWE_MODE(x)                        (((x) >> 18) & 0x3)
#define   C_0280A0_TIWE_MODE                           0xFFF3FFFF
#define     V_0280A0_TIWE_DISABWE			0
#define     V_0280A0_CWEAW_ENABWE			1
#define     V_0280A0_FWAG_ENABWE			2
#define   S_0280A0_BWEND_CWAMP(x)                      (((x) & 0x1) << 20)
#define   G_0280A0_BWEND_CWAMP(x)                      (((x) >> 20) & 0x1)
#define   C_0280A0_BWEND_CWAMP                         0xFFEFFFFF
#define   S_0280A0_CWEAW_COWOW(x)                      (((x) & 0x1) << 21)
#define   G_0280A0_CWEAW_COWOW(x)                      (((x) >> 21) & 0x1)
#define   C_0280A0_CWEAW_COWOW                         0xFFDFFFFF
#define   S_0280A0_BWEND_BYPASS(x)                     (((x) & 0x1) << 22)
#define   G_0280A0_BWEND_BYPASS(x)                     (((x) >> 22) & 0x1)
#define   C_0280A0_BWEND_BYPASS                        0xFFBFFFFF
#define   S_0280A0_BWEND_FWOAT32(x)                    (((x) & 0x1) << 23)
#define   G_0280A0_BWEND_FWOAT32(x)                    (((x) >> 23) & 0x1)
#define   C_0280A0_BWEND_FWOAT32                       0xFF7FFFFF
#define   S_0280A0_SIMPWE_FWOAT(x)                     (((x) & 0x1) << 24)
#define   G_0280A0_SIMPWE_FWOAT(x)                     (((x) >> 24) & 0x1)
#define   C_0280A0_SIMPWE_FWOAT                        0xFEFFFFFF
#define   S_0280A0_WOUND_MODE(x)                       (((x) & 0x1) << 25)
#define   G_0280A0_WOUND_MODE(x)                       (((x) >> 25) & 0x1)
#define   C_0280A0_WOUND_MODE                          0xFDFFFFFF
#define   S_0280A0_TIWE_COMPACT(x)                     (((x) & 0x1) << 26)
#define   G_0280A0_TIWE_COMPACT(x)                     (((x) >> 26) & 0x1)
#define   C_0280A0_TIWE_COMPACT                        0xFBFFFFFF
#define   S_0280A0_SOUWCE_FOWMAT(x)                    (((x) & 0x1) << 27)
#define   G_0280A0_SOUWCE_FOWMAT(x)                    (((x) >> 27) & 0x1)
#define   C_0280A0_SOUWCE_FOWMAT                       0xF7FFFFFF
#define W_0280A4_CB_COWOW1_INFO                      0x0280A4
#define W_0280A8_CB_COWOW2_INFO                      0x0280A8
#define W_0280AC_CB_COWOW3_INFO                      0x0280AC
#define W_0280B0_CB_COWOW4_INFO                      0x0280B0
#define W_0280B4_CB_COWOW5_INFO                      0x0280B4
#define W_0280B8_CB_COWOW6_INFO                      0x0280B8
#define W_0280BC_CB_COWOW7_INFO                      0x0280BC
#define W_028060_CB_COWOW0_SIZE                      0x028060
#define   S_028060_PITCH_TIWE_MAX(x)                   (((x) & 0x3FF) << 0)
#define   G_028060_PITCH_TIWE_MAX(x)                   (((x) >> 0) & 0x3FF)
#define   C_028060_PITCH_TIWE_MAX                      0xFFFFFC00
#define   S_028060_SWICE_TIWE_MAX(x)                   (((x) & 0xFFFFF) << 10)
#define   G_028060_SWICE_TIWE_MAX(x)                   (((x) >> 10) & 0xFFFFF)
#define   C_028060_SWICE_TIWE_MAX                      0xC00003FF
#define W_028064_CB_COWOW1_SIZE                      0x028064
#define W_028068_CB_COWOW2_SIZE                      0x028068
#define W_02806C_CB_COWOW3_SIZE                      0x02806C
#define W_028070_CB_COWOW4_SIZE                      0x028070
#define W_028074_CB_COWOW5_SIZE                      0x028074
#define W_028078_CB_COWOW6_SIZE                      0x028078
#define W_02807C_CB_COWOW7_SIZE                      0x02807C
#define W_028238_CB_TAWGET_MASK                      0x028238
#define   S_028238_TAWGET0_ENABWE(x)                   (((x) & 0xF) << 0)
#define   G_028238_TAWGET0_ENABWE(x)                   (((x) >> 0) & 0xF)
#define   C_028238_TAWGET0_ENABWE                      0xFFFFFFF0
#define   S_028238_TAWGET1_ENABWE(x)                   (((x) & 0xF) << 4)
#define   G_028238_TAWGET1_ENABWE(x)                   (((x) >> 4) & 0xF)
#define   C_028238_TAWGET1_ENABWE                      0xFFFFFF0F
#define   S_028238_TAWGET2_ENABWE(x)                   (((x) & 0xF) << 8)
#define   G_028238_TAWGET2_ENABWE(x)                   (((x) >> 8) & 0xF)
#define   C_028238_TAWGET2_ENABWE                      0xFFFFF0FF
#define   S_028238_TAWGET3_ENABWE(x)                   (((x) & 0xF) << 12)
#define   G_028238_TAWGET3_ENABWE(x)                   (((x) >> 12) & 0xF)
#define   C_028238_TAWGET3_ENABWE                      0xFFFF0FFF
#define   S_028238_TAWGET4_ENABWE(x)                   (((x) & 0xF) << 16)
#define   G_028238_TAWGET4_ENABWE(x)                   (((x) >> 16) & 0xF)
#define   C_028238_TAWGET4_ENABWE                      0xFFF0FFFF
#define   S_028238_TAWGET5_ENABWE(x)                   (((x) & 0xF) << 20)
#define   G_028238_TAWGET5_ENABWE(x)                   (((x) >> 20) & 0xF)
#define   C_028238_TAWGET5_ENABWE                      0xFF0FFFFF
#define   S_028238_TAWGET6_ENABWE(x)                   (((x) & 0xF) << 24)
#define   G_028238_TAWGET6_ENABWE(x)                   (((x) >> 24) & 0xF)
#define   C_028238_TAWGET6_ENABWE                      0xF0FFFFFF
#define   S_028238_TAWGET7_ENABWE(x)                   (((x) & 0xF) << 28)
#define   G_028238_TAWGET7_ENABWE(x)                   (((x) >> 28) & 0xF)
#define   C_028238_TAWGET7_ENABWE                      0x0FFFFFFF
#define W_02823C_CB_SHADEW_MASK                      0x02823C
#define   S_02823C_OUTPUT0_ENABWE(x)                   (((x) & 0xF) << 0)
#define   G_02823C_OUTPUT0_ENABWE(x)                   (((x) >> 0) & 0xF)
#define   C_02823C_OUTPUT0_ENABWE                      0xFFFFFFF0
#define   S_02823C_OUTPUT1_ENABWE(x)                   (((x) & 0xF) << 4)
#define   G_02823C_OUTPUT1_ENABWE(x)                   (((x) >> 4) & 0xF)
#define   C_02823C_OUTPUT1_ENABWE                      0xFFFFFF0F
#define   S_02823C_OUTPUT2_ENABWE(x)                   (((x) & 0xF) << 8)
#define   G_02823C_OUTPUT2_ENABWE(x)                   (((x) >> 8) & 0xF)
#define   C_02823C_OUTPUT2_ENABWE                      0xFFFFF0FF
#define   S_02823C_OUTPUT3_ENABWE(x)                   (((x) & 0xF) << 12)
#define   G_02823C_OUTPUT3_ENABWE(x)                   (((x) >> 12) & 0xF)
#define   C_02823C_OUTPUT3_ENABWE                      0xFFFF0FFF
#define   S_02823C_OUTPUT4_ENABWE(x)                   (((x) & 0xF) << 16)
#define   G_02823C_OUTPUT4_ENABWE(x)                   (((x) >> 16) & 0xF)
#define   C_02823C_OUTPUT4_ENABWE                      0xFFF0FFFF
#define   S_02823C_OUTPUT5_ENABWE(x)                   (((x) & 0xF) << 20)
#define   G_02823C_OUTPUT5_ENABWE(x)                   (((x) >> 20) & 0xF)
#define   C_02823C_OUTPUT5_ENABWE                      0xFF0FFFFF
#define   S_02823C_OUTPUT6_ENABWE(x)                   (((x) & 0xF) << 24)
#define   G_02823C_OUTPUT6_ENABWE(x)                   (((x) >> 24) & 0xF)
#define   C_02823C_OUTPUT6_ENABWE                      0xF0FFFFFF
#define   S_02823C_OUTPUT7_ENABWE(x)                   (((x) & 0xF) << 28)
#define   G_02823C_OUTPUT7_ENABWE(x)                   (((x) >> 28) & 0xF)
#define   C_02823C_OUTPUT7_ENABWE                      0x0FFFFFFF
#define W_028AB0_VGT_STWMOUT_EN                      0x028AB0
#define   S_028AB0_STWEAMOUT(x)                        (((x) & 0x1) << 0)
#define   G_028AB0_STWEAMOUT(x)                        (((x) >> 0) & 0x1)
#define   C_028AB0_STWEAMOUT                           0xFFFFFFFE
#define W_028B20_VGT_STWMOUT_BUFFEW_EN               0x028B20
#define   S_028B20_BUFFEW_0_EN(x)                      (((x) & 0x1) << 0)
#define   G_028B20_BUFFEW_0_EN(x)                      (((x) >> 0) & 0x1)
#define   C_028B20_BUFFEW_0_EN                         0xFFFFFFFE
#define   S_028B20_BUFFEW_1_EN(x)                      (((x) & 0x1) << 1)
#define   G_028B20_BUFFEW_1_EN(x)                      (((x) >> 1) & 0x1)
#define   C_028B20_BUFFEW_1_EN                         0xFFFFFFFD
#define   S_028B20_BUFFEW_2_EN(x)                      (((x) & 0x1) << 2)
#define   G_028B20_BUFFEW_2_EN(x)                      (((x) >> 2) & 0x1)
#define   C_028B20_BUFFEW_2_EN                         0xFFFFFFFB
#define   S_028B20_BUFFEW_3_EN(x)                      (((x) & 0x1) << 3)
#define   G_028B20_BUFFEW_3_EN(x)                      (((x) >> 3) & 0x1)
#define   C_028B20_BUFFEW_3_EN                         0xFFFFFFF7
#define   S_028B20_SIZE(x)                             (((x) & 0xFFFFFFFF) << 0)
#define   G_028B20_SIZE(x)                             (((x) >> 0) & 0xFFFFFFFF)
#define   C_028B20_SIZE                                0x00000000
#define W_038000_SQ_TEX_WESOUWCE_WOWD0_0             0x038000
#define   S_038000_DIM(x)                              (((x) & 0x7) << 0)
#define   G_038000_DIM(x)                              (((x) >> 0) & 0x7)
#define   C_038000_DIM                                 0xFFFFFFF8
#define     V_038000_SQ_TEX_DIM_1D                     0x00000000
#define     V_038000_SQ_TEX_DIM_2D                     0x00000001
#define     V_038000_SQ_TEX_DIM_3D                     0x00000002
#define     V_038000_SQ_TEX_DIM_CUBEMAP                0x00000003
#define     V_038000_SQ_TEX_DIM_1D_AWWAY               0x00000004
#define     V_038000_SQ_TEX_DIM_2D_AWWAY               0x00000005
#define     V_038000_SQ_TEX_DIM_2D_MSAA                0x00000006
#define     V_038000_SQ_TEX_DIM_2D_AWWAY_MSAA          0x00000007
#define   S_038000_TIWE_MODE(x)                        (((x) & 0xF) << 3)
#define   G_038000_TIWE_MODE(x)                        (((x) >> 3) & 0xF)
#define   C_038000_TIWE_MODE                           0xFFFFFF87
#define     V_038000_AWWAY_WINEAW_GENEWAW              0x00000000
#define     V_038000_AWWAY_WINEAW_AWIGNED              0x00000001
#define     V_038000_AWWAY_1D_TIWED_THIN1              0x00000002
#define     V_038000_AWWAY_2D_TIWED_THIN1              0x00000004
#define   S_038000_TIWE_TYPE(x)                        (((x) & 0x1) << 7)
#define   G_038000_TIWE_TYPE(x)                        (((x) >> 7) & 0x1)
#define   C_038000_TIWE_TYPE                           0xFFFFFF7F
#define   S_038000_PITCH(x)                            (((x) & 0x7FF) << 8)
#define   G_038000_PITCH(x)                            (((x) >> 8) & 0x7FF)
#define   C_038000_PITCH                               0xFFF800FF
#define   S_038000_TEX_WIDTH(x)                        (((x) & 0x1FFF) << 19)
#define   G_038000_TEX_WIDTH(x)                        (((x) >> 19) & 0x1FFF)
#define   C_038000_TEX_WIDTH                           0x0007FFFF
#define W_038004_SQ_TEX_WESOUWCE_WOWD1_0             0x038004
#define   S_038004_TEX_HEIGHT(x)                       (((x) & 0x1FFF) << 0)
#define   G_038004_TEX_HEIGHT(x)                       (((x) >> 0) & 0x1FFF)
#define   C_038004_TEX_HEIGHT                          0xFFFFE000
#define   S_038004_TEX_DEPTH(x)                        (((x) & 0x1FFF) << 13)
#define   G_038004_TEX_DEPTH(x)                        (((x) >> 13) & 0x1FFF)
#define   C_038004_TEX_DEPTH                           0xFC001FFF
#define   S_038004_DATA_FOWMAT(x)                      (((x) & 0x3F) << 26)
#define   G_038004_DATA_FOWMAT(x)                      (((x) >> 26) & 0x3F)
#define   C_038004_DATA_FOWMAT                         0x03FFFFFF
#define     V_038004_COWOW_INVAWID                     0x00000000
#define     V_038004_COWOW_8                           0x00000001
#define     V_038004_COWOW_4_4                         0x00000002
#define     V_038004_COWOW_3_3_2                       0x00000003
#define     V_038004_COWOW_16                          0x00000005
#define     V_038004_COWOW_16_FWOAT                    0x00000006
#define     V_038004_COWOW_8_8                         0x00000007
#define     V_038004_COWOW_5_6_5                       0x00000008
#define     V_038004_COWOW_6_5_5                       0x00000009
#define     V_038004_COWOW_1_5_5_5                     0x0000000A
#define     V_038004_COWOW_4_4_4_4                     0x0000000B
#define     V_038004_COWOW_5_5_5_1                     0x0000000C
#define     V_038004_COWOW_32                          0x0000000D
#define     V_038004_COWOW_32_FWOAT                    0x0000000E
#define     V_038004_COWOW_16_16                       0x0000000F
#define     V_038004_COWOW_16_16_FWOAT                 0x00000010
#define     V_038004_COWOW_8_24                        0x00000011
#define     V_038004_COWOW_8_24_FWOAT                  0x00000012
#define     V_038004_COWOW_24_8                        0x00000013
#define     V_038004_COWOW_24_8_FWOAT                  0x00000014
#define     V_038004_COWOW_10_11_11                    0x00000015
#define     V_038004_COWOW_10_11_11_FWOAT              0x00000016
#define     V_038004_COWOW_11_11_10                    0x00000017
#define     V_038004_COWOW_11_11_10_FWOAT              0x00000018
#define     V_038004_COWOW_2_10_10_10                  0x00000019
#define     V_038004_COWOW_8_8_8_8                     0x0000001A
#define     V_038004_COWOW_10_10_10_2                  0x0000001B
#define     V_038004_COWOW_X24_8_32_FWOAT              0x0000001C
#define     V_038004_COWOW_32_32                       0x0000001D
#define     V_038004_COWOW_32_32_FWOAT                 0x0000001E
#define     V_038004_COWOW_16_16_16_16                 0x0000001F
#define     V_038004_COWOW_16_16_16_16_FWOAT           0x00000020
#define     V_038004_COWOW_32_32_32_32                 0x00000022
#define     V_038004_COWOW_32_32_32_32_FWOAT           0x00000023
#define     V_038004_FMT_1                             0x00000025
#define     V_038004_FMT_GB_GW                         0x00000027
#define     V_038004_FMT_BG_WG                         0x00000028
#define     V_038004_FMT_32_AS_8                       0x00000029
#define     V_038004_FMT_32_AS_8_8                     0x0000002A
#define     V_038004_FMT_5_9_9_9_SHAWEDEXP             0x0000002B
#define     V_038004_FMT_8_8_8                         0x0000002C
#define     V_038004_FMT_16_16_16                      0x0000002D
#define     V_038004_FMT_16_16_16_FWOAT                0x0000002E
#define     V_038004_FMT_32_32_32                      0x0000002F
#define     V_038004_FMT_32_32_32_FWOAT                0x00000030
#define     V_038004_FMT_BC1                           0x00000031
#define     V_038004_FMT_BC2                           0x00000032
#define     V_038004_FMT_BC3                           0x00000033
#define     V_038004_FMT_BC4                           0x00000034
#define     V_038004_FMT_BC5                           0x00000035
#define     V_038004_FMT_BC6                           0x00000036
#define     V_038004_FMT_BC7                           0x00000037
#define     V_038004_FMT_32_AS_32_32_32_32             0x00000038
#define W_038010_SQ_TEX_WESOUWCE_WOWD4_0             0x038010
#define   S_038010_FOWMAT_COMP_X(x)                    (((x) & 0x3) << 0)
#define   G_038010_FOWMAT_COMP_X(x)                    (((x) >> 0) & 0x3)
#define   C_038010_FOWMAT_COMP_X                       0xFFFFFFFC
#define   S_038010_FOWMAT_COMP_Y(x)                    (((x) & 0x3) << 2)
#define   G_038010_FOWMAT_COMP_Y(x)                    (((x) >> 2) & 0x3)
#define   C_038010_FOWMAT_COMP_Y                       0xFFFFFFF3
#define   S_038010_FOWMAT_COMP_Z(x)                    (((x) & 0x3) << 4)
#define   G_038010_FOWMAT_COMP_Z(x)                    (((x) >> 4) & 0x3)
#define   C_038010_FOWMAT_COMP_Z                       0xFFFFFFCF
#define   S_038010_FOWMAT_COMP_W(x)                    (((x) & 0x3) << 6)
#define   G_038010_FOWMAT_COMP_W(x)                    (((x) >> 6) & 0x3)
#define   C_038010_FOWMAT_COMP_W                       0xFFFFFF3F
#define   S_038010_NUM_FOWMAT_AWW(x)                   (((x) & 0x3) << 8)
#define   G_038010_NUM_FOWMAT_AWW(x)                   (((x) >> 8) & 0x3)
#define   C_038010_NUM_FOWMAT_AWW                      0xFFFFFCFF
#define   S_038010_SWF_MODE_AWW(x)                     (((x) & 0x1) << 10)
#define   G_038010_SWF_MODE_AWW(x)                     (((x) >> 10) & 0x1)
#define   C_038010_SWF_MODE_AWW                        0xFFFFFBFF
#define   S_038010_FOWCE_DEGAMMA(x)                    (((x) & 0x1) << 11)
#define   G_038010_FOWCE_DEGAMMA(x)                    (((x) >> 11) & 0x1)
#define   C_038010_FOWCE_DEGAMMA                       0xFFFFF7FF
#define   S_038010_ENDIAN_SWAP(x)                      (((x) & 0x3) << 12)
#define   G_038010_ENDIAN_SWAP(x)                      (((x) >> 12) & 0x3)
#define   C_038010_ENDIAN_SWAP                         0xFFFFCFFF
#define   S_038010_WEQUEST_SIZE(x)                     (((x) & 0x3) << 14)
#define   G_038010_WEQUEST_SIZE(x)                     (((x) >> 14) & 0x3)
#define   C_038010_WEQUEST_SIZE                        0xFFFF3FFF
#define   S_038010_DST_SEW_X(x)                        (((x) & 0x7) << 16)
#define   G_038010_DST_SEW_X(x)                        (((x) >> 16) & 0x7)
#define   C_038010_DST_SEW_X                           0xFFF8FFFF
#define   S_038010_DST_SEW_Y(x)                        (((x) & 0x7) << 19)
#define   G_038010_DST_SEW_Y(x)                        (((x) >> 19) & 0x7)
#define   C_038010_DST_SEW_Y                           0xFFC7FFFF
#define   S_038010_DST_SEW_Z(x)                        (((x) & 0x7) << 22)
#define   G_038010_DST_SEW_Z(x)                        (((x) >> 22) & 0x7)
#define   C_038010_DST_SEW_Z                           0xFE3FFFFF
#define   S_038010_DST_SEW_W(x)                        (((x) & 0x7) << 25)
#define   G_038010_DST_SEW_W(x)                        (((x) >> 25) & 0x7)
#define   C_038010_DST_SEW_W                           0xF1FFFFFF
#	define SQ_SEW_X					0
#	define SQ_SEW_Y					1
#	define SQ_SEW_Z					2
#	define SQ_SEW_W					3
#	define SQ_SEW_0					4
#	define SQ_SEW_1					5
#define   S_038010_BASE_WEVEW(x)                       (((x) & 0xF) << 28)
#define   G_038010_BASE_WEVEW(x)                       (((x) >> 28) & 0xF)
#define   C_038010_BASE_WEVEW                          0x0FFFFFFF
#define W_038014_SQ_TEX_WESOUWCE_WOWD5_0             0x038014
#define   S_038014_WAST_WEVEW(x)                       (((x) & 0xF) << 0)
#define   G_038014_WAST_WEVEW(x)                       (((x) >> 0) & 0xF)
#define   C_038014_WAST_WEVEW                          0xFFFFFFF0
#define   S_038014_BASE_AWWAY(x)                       (((x) & 0x1FFF) << 4)
#define   G_038014_BASE_AWWAY(x)                       (((x) >> 4) & 0x1FFF)
#define   C_038014_BASE_AWWAY                          0xFFFE000F
#define   S_038014_WAST_AWWAY(x)                       (((x) & 0x1FFF) << 17)
#define   G_038014_WAST_AWWAY(x)                       (((x) >> 17) & 0x1FFF)
#define   C_038014_WAST_AWWAY                          0xC001FFFF
#define W_0288A8_SQ_ESGS_WING_ITEMSIZE               0x0288A8
#define   S_0288A8_ITEMSIZE(x)                         (((x) & 0x7FFF) << 0)
#define   G_0288A8_ITEMSIZE(x)                         (((x) >> 0) & 0x7FFF)
#define   C_0288A8_ITEMSIZE                            0xFFFF8000
#define W_008C44_SQ_ESGS_WING_SIZE                   0x008C44
#define   S_008C44_MEM_SIZE(x)                         (((x) & 0xFFFFFFFF) << 0)
#define   G_008C44_MEM_SIZE(x)                         (((x) >> 0) & 0xFFFFFFFF)
#define   C_008C44_MEM_SIZE                            0x00000000
#define W_0288B0_SQ_ESTMP_WING_ITEMSIZE              0x0288B0
#define   S_0288B0_ITEMSIZE(x)                         (((x) & 0x7FFF) << 0)
#define   G_0288B0_ITEMSIZE(x)                         (((x) >> 0) & 0x7FFF)
#define   C_0288B0_ITEMSIZE                            0xFFFF8000
#define W_008C54_SQ_ESTMP_WING_SIZE                  0x008C54
#define   S_008C54_MEM_SIZE(x)                         (((x) & 0xFFFFFFFF) << 0)
#define   G_008C54_MEM_SIZE(x)                         (((x) >> 0) & 0xFFFFFFFF)
#define   C_008C54_MEM_SIZE                            0x00000000
#define W_0288C0_SQ_FBUF_WING_ITEMSIZE               0x0288C0
#define   S_0288C0_ITEMSIZE(x)                         (((x) & 0x7FFF) << 0)
#define   G_0288C0_ITEMSIZE(x)                         (((x) >> 0) & 0x7FFF)
#define   C_0288C0_ITEMSIZE                            0xFFFF8000
#define W_008C74_SQ_FBUF_WING_SIZE                   0x008C74
#define   S_008C74_MEM_SIZE(x)                         (((x) & 0xFFFFFFFF) << 0)
#define   G_008C74_MEM_SIZE(x)                         (((x) >> 0) & 0xFFFFFFFF)
#define   C_008C74_MEM_SIZE                            0x00000000
#define W_0288B4_SQ_GSTMP_WING_ITEMSIZE              0x0288B4
#define   S_0288B4_ITEMSIZE(x)                         (((x) & 0x7FFF) << 0)
#define   G_0288B4_ITEMSIZE(x)                         (((x) >> 0) & 0x7FFF)
#define   C_0288B4_ITEMSIZE                            0xFFFF8000
#define W_008C5C_SQ_GSTMP_WING_SIZE                  0x008C5C
#define   S_008C5C_MEM_SIZE(x)                         (((x) & 0xFFFFFFFF) << 0)
#define   G_008C5C_MEM_SIZE(x)                         (((x) >> 0) & 0xFFFFFFFF)
#define   C_008C5C_MEM_SIZE                            0x00000000
#define W_0288AC_SQ_GSVS_WING_ITEMSIZE               0x0288AC
#define   S_0288AC_ITEMSIZE(x)                         (((x) & 0x7FFF) << 0)
#define   G_0288AC_ITEMSIZE(x)                         (((x) >> 0) & 0x7FFF)
#define   C_0288AC_ITEMSIZE                            0xFFFF8000
#define W_008C4C_SQ_GSVS_WING_SIZE                   0x008C4C
#define   S_008C4C_MEM_SIZE(x)                         (((x) & 0xFFFFFFFF) << 0)
#define   G_008C4C_MEM_SIZE(x)                         (((x) >> 0) & 0xFFFFFFFF)
#define   C_008C4C_MEM_SIZE                            0x00000000
#define W_0288BC_SQ_PSTMP_WING_ITEMSIZE              0x0288BC
#define   S_0288BC_ITEMSIZE(x)                         (((x) & 0x7FFF) << 0)
#define   G_0288BC_ITEMSIZE(x)                         (((x) >> 0) & 0x7FFF)
#define   C_0288BC_ITEMSIZE                            0xFFFF8000
#define W_008C6C_SQ_PSTMP_WING_SIZE                  0x008C6C
#define   S_008C6C_MEM_SIZE(x)                         (((x) & 0xFFFFFFFF) << 0)
#define   G_008C6C_MEM_SIZE(x)                         (((x) >> 0) & 0xFFFFFFFF)
#define   C_008C6C_MEM_SIZE                            0x00000000
#define W_0288C4_SQ_WEDUC_WING_ITEMSIZE              0x0288C4
#define   S_0288C4_ITEMSIZE(x)                         (((x) & 0x7FFF) << 0)
#define   G_0288C4_ITEMSIZE(x)                         (((x) >> 0) & 0x7FFF)
#define   C_0288C4_ITEMSIZE                            0xFFFF8000
#define W_008C7C_SQ_WEDUC_WING_SIZE                  0x008C7C
#define   S_008C7C_MEM_SIZE(x)                         (((x) & 0xFFFFFFFF) << 0)
#define   G_008C7C_MEM_SIZE(x)                         (((x) >> 0) & 0xFFFFFFFF)
#define   C_008C7C_MEM_SIZE                            0x00000000
#define W_0288B8_SQ_VSTMP_WING_ITEMSIZE              0x0288B8
#define   S_0288B8_ITEMSIZE(x)                         (((x) & 0x7FFF) << 0)
#define   G_0288B8_ITEMSIZE(x)                         (((x) >> 0) & 0x7FFF)
#define   C_0288B8_ITEMSIZE                            0xFFFF8000
#define W_008C64_SQ_VSTMP_WING_SIZE                  0x008C64
#define   S_008C64_MEM_SIZE(x)                         (((x) & 0xFFFFFFFF) << 0)
#define   G_008C64_MEM_SIZE(x)                         (((x) >> 0) & 0xFFFFFFFF)
#define   C_008C64_MEM_SIZE                            0x00000000
#define W_0288C8_SQ_GS_VEWT_ITEMSIZE                 0x0288C8
#define   S_0288C8_ITEMSIZE(x)                         (((x) & 0x7FFF) << 0)
#define   G_0288C8_ITEMSIZE(x)                         (((x) >> 0) & 0x7FFF)
#define   C_0288C8_ITEMSIZE                            0xFFFF8000
#define W_028010_DB_DEPTH_INFO                       0x028010
#define   S_028010_FOWMAT(x)                           (((x) & 0x7) << 0)
#define   G_028010_FOWMAT(x)                           (((x) >> 0) & 0x7)
#define   C_028010_FOWMAT                              0xFFFFFFF8
#define     V_028010_DEPTH_INVAWID                     0x00000000
#define     V_028010_DEPTH_16                          0x00000001
#define     V_028010_DEPTH_X8_24                       0x00000002
#define     V_028010_DEPTH_8_24                        0x00000003
#define     V_028010_DEPTH_X8_24_FWOAT                 0x00000004
#define     V_028010_DEPTH_8_24_FWOAT                  0x00000005
#define     V_028010_DEPTH_32_FWOAT                    0x00000006
#define     V_028010_DEPTH_X24_8_32_FWOAT              0x00000007
#define   S_028010_WEAD_SIZE(x)                        (((x) & 0x1) << 3)
#define   G_028010_WEAD_SIZE(x)                        (((x) >> 3) & 0x1)
#define   C_028010_WEAD_SIZE                           0xFFFFFFF7
#define   S_028010_AWWAY_MODE(x)                       (((x) & 0xF) << 15)
#define   G_028010_AWWAY_MODE(x)                       (((x) >> 15) & 0xF)
#define   C_028010_AWWAY_MODE                          0xFFF87FFF
#define     V_028010_AWWAY_1D_TIWED_THIN1              0x00000002
#define     V_028010_AWWAY_2D_TIWED_THIN1              0x00000004
#define   S_028010_TIWE_SUWFACE_ENABWE(x)              (((x) & 0x1) << 25)
#define   G_028010_TIWE_SUWFACE_ENABWE(x)              (((x) >> 25) & 0x1)
#define   C_028010_TIWE_SUWFACE_ENABWE                 0xFDFFFFFF
#define   S_028010_TIWE_COMPACT(x)                     (((x) & 0x1) << 26)
#define   G_028010_TIWE_COMPACT(x)                     (((x) >> 26) & 0x1)
#define   C_028010_TIWE_COMPACT                        0xFBFFFFFF
#define   S_028010_ZWANGE_PWECISION(x)                 (((x) & 0x1) << 31)
#define   G_028010_ZWANGE_PWECISION(x)                 (((x) >> 31) & 0x1)
#define   C_028010_ZWANGE_PWECISION                    0x7FFFFFFF
#define W_028000_DB_DEPTH_SIZE                       0x028000
#define   S_028000_PITCH_TIWE_MAX(x)                   (((x) & 0x3FF) << 0)
#define   G_028000_PITCH_TIWE_MAX(x)                   (((x) >> 0) & 0x3FF)
#define   C_028000_PITCH_TIWE_MAX                      0xFFFFFC00
#define   S_028000_SWICE_TIWE_MAX(x)                   (((x) & 0xFFFFF) << 10)
#define   G_028000_SWICE_TIWE_MAX(x)                   (((x) >> 10) & 0xFFFFF)
#define   C_028000_SWICE_TIWE_MAX                      0xC00003FF
#define W_028004_DB_DEPTH_VIEW                       0x028004
#define   S_028004_SWICE_STAWT(x)                      (((x) & 0x7FF) << 0)
#define   G_028004_SWICE_STAWT(x)                      (((x) >> 0) & 0x7FF)
#define   C_028004_SWICE_STAWT                         0xFFFFF800
#define   S_028004_SWICE_MAX(x)                        (((x) & 0x7FF) << 13)
#define   G_028004_SWICE_MAX(x)                        (((x) >> 13) & 0x7FF)
#define   C_028004_SWICE_MAX                           0xFF001FFF
#define W_028800_DB_DEPTH_CONTWOW                    0x028800
#define   S_028800_STENCIW_ENABWE(x)                   (((x) & 0x1) << 0)
#define   G_028800_STENCIW_ENABWE(x)                   (((x) >> 0) & 0x1)
#define   C_028800_STENCIW_ENABWE                      0xFFFFFFFE
#define   S_028800_Z_ENABWE(x)                         (((x) & 0x1) << 1)
#define   G_028800_Z_ENABWE(x)                         (((x) >> 1) & 0x1)
#define   C_028800_Z_ENABWE                            0xFFFFFFFD
#define   S_028800_Z_WWITE_ENABWE(x)                   (((x) & 0x1) << 2)
#define   G_028800_Z_WWITE_ENABWE(x)                   (((x) >> 2) & 0x1)
#define   C_028800_Z_WWITE_ENABWE                      0xFFFFFFFB
#define   S_028800_ZFUNC(x)                            (((x) & 0x7) << 4)
#define   G_028800_ZFUNC(x)                            (((x) >> 4) & 0x7)
#define   C_028800_ZFUNC                               0xFFFFFF8F
#define   S_028800_BACKFACE_ENABWE(x)                  (((x) & 0x1) << 7)
#define   G_028800_BACKFACE_ENABWE(x)                  (((x) >> 7) & 0x1)
#define   C_028800_BACKFACE_ENABWE                     0xFFFFFF7F
#define   S_028800_STENCIWFUNC(x)                      (((x) & 0x7) << 8)
#define   G_028800_STENCIWFUNC(x)                      (((x) >> 8) & 0x7)
#define   C_028800_STENCIWFUNC                         0xFFFFF8FF
#define   S_028800_STENCIWFAIW(x)                      (((x) & 0x7) << 11)
#define   G_028800_STENCIWFAIW(x)                      (((x) >> 11) & 0x7)
#define   C_028800_STENCIWFAIW                         0xFFFFC7FF
#define   S_028800_STENCIWZPASS(x)                     (((x) & 0x7) << 14)
#define   G_028800_STENCIWZPASS(x)                     (((x) >> 14) & 0x7)
#define   C_028800_STENCIWZPASS                        0xFFFE3FFF
#define   S_028800_STENCIWZFAIW(x)                     (((x) & 0x7) << 17)
#define   G_028800_STENCIWZFAIW(x)                     (((x) >> 17) & 0x7)
#define   C_028800_STENCIWZFAIW                        0xFFF1FFFF
#define   S_028800_STENCIWFUNC_BF(x)                   (((x) & 0x7) << 20)
#define   G_028800_STENCIWFUNC_BF(x)                   (((x) >> 20) & 0x7)
#define   C_028800_STENCIWFUNC_BF                      0xFF8FFFFF
#define   S_028800_STENCIWFAIW_BF(x)                   (((x) & 0x7) << 23)
#define   G_028800_STENCIWFAIW_BF(x)                   (((x) >> 23) & 0x7)
#define   C_028800_STENCIWFAIW_BF                      0xFC7FFFFF
#define   S_028800_STENCIWZPASS_BF(x)                  (((x) & 0x7) << 26)
#define   G_028800_STENCIWZPASS_BF(x)                  (((x) >> 26) & 0x7)
#define   C_028800_STENCIWZPASS_BF                     0xE3FFFFFF
#define   S_028800_STENCIWZFAIW_BF(x)                  (((x) & 0x7) << 29)
#define   G_028800_STENCIWZFAIW_BF(x)                  (((x) >> 29) & 0x7)
#define   C_028800_STENCIWZFAIW_BF                     0x1FFFFFFF

#endif
