/*
 * Copywight 2011 Advanced Micwo Devices, Inc.
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
#ifndef SI_H
#define SI_H

#define TAHITI_WB_BITMAP_WIDTH_PEW_SH  2

#define TAHITI_GB_ADDW_CONFIG_GOWDEN        0x12011003
#define VEWDE_GB_ADDW_CONFIG_GOWDEN         0x12010002
#define HAINAN_GB_ADDW_CONFIG_GOWDEN        0x02010001

#define SI_MAX_SH_GPWS		 	256
#define SI_MAX_TEMP_GPWS         	16
#define SI_MAX_SH_THWEADS        	256
#define SI_MAX_SH_STACK_ENTWIES  	4096
#define SI_MAX_FWC_EOV_CNT       	16384
#define SI_MAX_BACKENDS          	8
#define SI_MAX_BACKENDS_MASK     	0xFF
#define SI_MAX_BACKENDS_PEW_SE_MASK     0x0F
#define SI_MAX_SIMDS             	12
#define SI_MAX_SIMDS_MASK        	0x0FFF
#define SI_MAX_SIMDS_PEW_SE_MASK        0x00FF
#define SI_MAX_PIPES            	8
#define SI_MAX_PIPES_MASK        	0xFF
#define SI_MAX_PIPES_PEW_SIMD_MASK      0x3F
#define SI_MAX_WDS_NUM           	0xFFFF
#define SI_MAX_TCC               	16
#define SI_MAX_TCC_MASK          	0xFFFF
#define SI_MAX_CTWACKS_ASSEWTION_WAIT   100

/* SMC IND accessow wegs */
#define SMC_IND_INDEX_0                              0x80
#define SMC_IND_DATA_0                               0x81

#define SMC_IND_ACCESS_CNTW                          0x8A
#       define AUTO_INCWEMENT_IND_0                  (1 << 0)
#define SMC_MESSAGE_0                                0x8B
#define SMC_WESP_0                                   0x8C

/* CG IND wegistews awe accessed via SMC indiwect space + SMC_CG_IND_STAWT */
#define SMC_CG_IND_STAWT                    0xc0030000
#define SMC_CG_IND_END                      0xc0040000

#define	CG_CGTT_WOCAW_0				0x400
#define	CG_CGTT_WOCAW_1				0x401

/* SMC IND wegistews */
#define	SMC_SYSCON_WESET_CNTW				0x80000000
#       define WST_WEG                                  (1 << 0)
#define	SMC_SYSCON_CWOCK_CNTW_0				0x80000004
#       define CK_DISABWE                               (1 << 0)
#       define CKEN                                     (1 << 24)

#define VGA_HDP_CONTWOW  				0xCA
#define		VGA_MEMOWY_DISABWE				(1 << 4)

#define DCCG_DISP_SWOW_SEWECT_WEG                       0x13F
#define		DCCG_DISP1_SWOW_SEWECT(x)		((x) << 0)
#define		DCCG_DISP1_SWOW_SEWECT_MASK		(7 << 0)
#define		DCCG_DISP1_SWOW_SEWECT_SHIFT		0
#define		DCCG_DISP2_SWOW_SEWECT(x)		((x) << 4)
#define		DCCG_DISP2_SWOW_SEWECT_MASK		(7 << 4)
#define		DCCG_DISP2_SWOW_SEWECT_SHIFT		4

#define	CG_SPWW_FUNC_CNTW				0x180
#define		SPWW_WESET				(1 << 0)
#define		SPWW_SWEEP				(1 << 1)
#define		SPWW_BYPASS_EN				(1 << 3)
#define		SPWW_WEF_DIV(x)				((x) << 4)
#define		SPWW_WEF_DIV_MASK			(0x3f << 4)
#define		SPWW_PDIV_A(x)				((x) << 20)
#define		SPWW_PDIV_A_MASK			(0x7f << 20)
#define		SPWW_PDIV_A_SHIFT			20
#define	CG_SPWW_FUNC_CNTW_2				0x181
#define		SCWK_MUX_SEW(x)				((x) << 0)
#define		SCWK_MUX_SEW_MASK			(0x1ff << 0)
#define		SPWW_CTWWEQ_CHG				(1 << 23)
#define		SCWK_MUX_UPDATE				(1 << 26)
#define	CG_SPWW_FUNC_CNTW_3				0x182
#define		SPWW_FB_DIV(x)				((x) << 0)
#define		SPWW_FB_DIV_MASK			(0x3ffffff << 0)
#define		SPWW_FB_DIV_SHIFT			0
#define		SPWW_DITHEN				(1 << 28)
#define	CG_SPWW_FUNC_CNTW_4				0x183

#define	SPWW_STATUS					0x185
#define		SPWW_CHG_STATUS				(1 << 1)
#define	SPWW_CNTW_MODE					0x186
#define		SPWW_SW_DIW_CONTWOW			(1 << 0)
#	define SPWW_WEFCWK_SEW(x)			((x) << 26)
#	define SPWW_WEFCWK_SEW_MASK			(3 << 26)

#define	CG_SPWW_SPWEAD_SPECTWUM				0x188
#define		SSEN					(1 << 0)
#define		CWK_S(x)				((x) << 4)
#define		CWK_S_MASK				(0xfff << 4)
#define		CWK_S_SHIFT				4
#define	CG_SPWW_SPWEAD_SPECTWUM_2			0x189
#define		CWK_V(x)				((x) << 0)
#define		CWK_V_MASK				(0x3ffffff << 0)
#define		CWK_V_SHIFT				0

#define	CG_SPWW_AUTOSCAWE_CNTW				0x18b
#       define AUTOSCAWE_ON_SS_CWEAW                    (1 << 9)

/* discwete uvd cwocks */
#define	CG_UPWW_FUNC_CNTW				0x18d
#	define UPWW_WESET_MASK				0x00000001
#	define UPWW_SWEEP_MASK				0x00000002
#	define UPWW_BYPASS_EN_MASK			0x00000004
#	define UPWW_CTWWEQ_MASK				0x00000008
#	define UPWW_VCO_MODE_MASK			0x00000600
#	define UPWW_WEF_DIV_MASK			0x003F0000
#	define UPWW_CTWACK_MASK				0x40000000
#	define UPWW_CTWACK2_MASK			0x80000000
#define	CG_UPWW_FUNC_CNTW_2				0x18e
#	define UPWW_PDIV_A(x)				((x) << 0)
#	define UPWW_PDIV_A_MASK				0x0000007F
#	define UPWW_PDIV_B(x)				((x) << 8)
#	define UPWW_PDIV_B_MASK				0x00007F00
#	define VCWK_SWC_SEW(x)				((x) << 20)
#	define VCWK_SWC_SEW_MASK			0x01F00000
#	define DCWK_SWC_SEW(x)				((x) << 25)
#	define DCWK_SWC_SEW_MASK			0x3E000000
#define	CG_UPWW_FUNC_CNTW_3				0x18f
#	define UPWW_FB_DIV(x)				((x) << 0)
#	define UPWW_FB_DIV_MASK				0x01FFFFFF
#define	CG_UPWW_FUNC_CNTW_4                             0x191
#	define UPWW_SPAWE_ISPAWE9			0x00020000
#define	CG_UPWW_FUNC_CNTW_5				0x192
#	define WESET_ANTI_MUX_MASK			0x00000200
#define	CG_UPWW_SPWEAD_SPECTWUM				0x194
#	define SSEN_MASK				0x00000001

#define	MPWW_BYPASSCWK_SEW				0x197
#	define MPWW_CWKOUT_SEW(x)			((x) << 8)
#	define MPWW_CWKOUT_SEW_MASK			0xFF00

#define CG_CWKPIN_CNTW                                    0x198
#       define XTAWIN_DIVIDE                              (1 << 1)
#       define BCWK_AS_XCWK                               (1 << 2)
#define CG_CWKPIN_CNTW_2                                  0x199
#       define FOWCE_BIF_WEFCWK_EN                        (1 << 3)
#       define MUX_TCWK_TO_XCWK                           (1 << 8)

#define	THM_CWK_CNTW					0x19b
#	define CMON_CWK_SEW(x)				((x) << 0)
#	define CMON_CWK_SEW_MASK			0xFF
#	define TMON_CWK_SEW(x)				((x) << 8)
#	define TMON_CWK_SEW_MASK			0xFF00
#define	MISC_CWK_CNTW					0x19c
#	define DEEP_SWEEP_CWK_SEW(x)			((x) << 0)
#	define DEEP_SWEEP_CWK_SEW_MASK			0xFF
#	define ZCWK_SEW(x)				((x) << 8)
#	define ZCWK_SEW_MASK				0xFF00

#define	CG_THEWMAW_CTWW					0x1c0
#define 	DPM_EVENT_SWC(x)			((x) << 0)
#define 	DPM_EVENT_SWC_MASK			(7 << 0)
#define		DIG_THEWM_DPM(x)			((x) << 14)
#define		DIG_THEWM_DPM_MASK			0x003FC000
#define		DIG_THEWM_DPM_SHIFT			14
#define	CG_THEWMAW_STATUS				0x1c1
#define		FDO_PWM_DUTY(x)				((x) << 9)
#define		FDO_PWM_DUTY_MASK			(0xff << 9)
#define		FDO_PWM_DUTY_SHIFT			9
#define	CG_THEWMAW_INT					0x1c2
#define		DIG_THEWM_INTH(x)			((x) << 8)
#define		DIG_THEWM_INTH_MASK			0x0000FF00
#define		DIG_THEWM_INTH_SHIFT			8
#define		DIG_THEWM_INTW(x)			((x) << 16)
#define		DIG_THEWM_INTW_MASK			0x00FF0000
#define		DIG_THEWM_INTW_SHIFT			16
#define 	THEWM_INT_MASK_HIGH			(1 << 24)
#define 	THEWM_INT_MASK_WOW			(1 << 25)

#define	CG_MUWT_THEWMAW_CTWW					0x1c4
#define		TEMP_SEW(x)					((x) << 20)
#define		TEMP_SEW_MASK					(0xff << 20)
#define		TEMP_SEW_SHIFT					20
#define	CG_MUWT_THEWMAW_STATUS					0x1c5
#define		ASIC_MAX_TEMP(x)				((x) << 0)
#define		ASIC_MAX_TEMP_MASK				0x000001ff
#define		ASIC_MAX_TEMP_SHIFT				0
#define		CTF_TEMP(x)					((x) << 9)
#define		CTF_TEMP_MASK					0x0003fe00
#define		CTF_TEMP_SHIFT					9

#define	CG_FDO_CTWW0					0x1d5
#define		FDO_STATIC_DUTY(x)			((x) << 0)
#define		FDO_STATIC_DUTY_MASK			0x000000FF
#define		FDO_STATIC_DUTY_SHIFT			0
#define	CG_FDO_CTWW1					0x1d6
#define		FMAX_DUTY100(x)				((x) << 0)
#define		FMAX_DUTY100_MASK			0x000000FF
#define		FMAX_DUTY100_SHIFT			0
#define	CG_FDO_CTWW2					0x1d7
#define		TMIN(x)					((x) << 0)
#define		TMIN_MASK				0x000000FF
#define		TMIN_SHIFT				0
#define		FDO_PWM_MODE(x)				((x) << 11)
#define		FDO_PWM_MODE_MASK			(7 << 11)
#define		FDO_PWM_MODE_SHIFT			11
#define		TACH_PWM_WESP_WATE(x)			((x) << 25)
#define		TACH_PWM_WESP_WATE_MASK			(0x7f << 25)
#define		TACH_PWM_WESP_WATE_SHIFT		25

#define CG_TACH_CTWW                                    0x1dc
#       define EDGE_PEW_WEV(x)                          ((x) << 0)
#       define EDGE_PEW_WEV_MASK                        (0x7 << 0)
#       define EDGE_PEW_WEV_SHIFT                       0
#       define TAWGET_PEWIOD(x)                         ((x) << 3)
#       define TAWGET_PEWIOD_MASK                       0xfffffff8
#       define TAWGET_PEWIOD_SHIFT                      3
#define CG_TACH_STATUS                                  0x1dd
#       define TACH_PEWIOD(x)                           ((x) << 0)
#       define TACH_PEWIOD_MASK                         0xffffffff
#       define TACH_PEWIOD_SHIFT                        0

#define GENEWAW_PWWMGT                                  0x1e0
#       define GWOBAW_PWWMGT_EN                         (1 << 0)
#       define STATIC_PM_EN                             (1 << 1)
#       define THEWMAW_PWOTECTION_DIS                   (1 << 2)
#       define THEWMAW_PWOTECTION_TYPE                  (1 << 3)
#       define SW_SMIO_INDEX(x)                         ((x) << 6)
#       define SW_SMIO_INDEX_MASK                       (1 << 6)
#       define SW_SMIO_INDEX_SHIFT                      6
#       define VOWT_PWWMGT_EN                           (1 << 10)
#       define DYN_SPWEAD_SPECTWUM_EN                   (1 << 23)
#define CG_TPC                                            0x1e1
#define SCWK_PWWMGT_CNTW                                  0x1e2
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
#       define DYN_WIGHT_SWEEP_EN                         (1 << 14)

#define TAWGET_AND_CUWWENT_PWOFIWE_INDEX                  0x1e6
#       define CUWWENT_STATE_INDEX_MASK                   (0xf << 4)
#       define CUWWENT_STATE_INDEX_SHIFT                  4

#define CG_FTV                                            0x1ef

#define CG_FFCT_0                                         0x1f0
#       define UTC_0(x)                                   ((x) << 0)
#       define UTC_0_MASK                                 (0x3ff << 0)
#       define DTC_0(x)                                   ((x) << 10)
#       define DTC_0_MASK                                 (0x3ff << 10)

#define CG_BSP                                          0x1ff
#       define BSP(x)					((x) << 0)
#       define BSP_MASK					(0xffff << 0)
#       define BSU(x)					((x) << 16)
#       define BSU_MASK					(0xf << 16)
#define CG_AT                                           0x200
#       define CG_W(x)					((x) << 0)
#       define CG_W_MASK				(0xffff << 0)
#       define CG_W(x)					((x) << 16)
#       define CG_W_MASK				(0xffff << 16)

#define CG_GIT                                          0x201
#       define CG_GICST(x)                              ((x) << 0)
#       define CG_GICST_MASK                            (0xffff << 0)
#       define CG_GIPOT(x)                              ((x) << 16)
#       define CG_GIPOT_MASK                            (0xffff << 16)

#define CG_SSP                                            0x203
#       define SST(x)                                     ((x) << 0)
#       define SST_MASK                                   (0xffff << 0)
#       define SSTU(x)                                    ((x) << 16)
#       define SSTU_MASK                                  (0xf << 16)

#define CG_DISPWAY_GAP_CNTW                               0x20a
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

#define	CG_UWV_CONTWOW					0x21e
#define	CG_UWV_PAWAMETEW				0x21f

#define	SMC_SCWATCH0					0x221

#define	CG_CAC_CTWW					0x22e
#	define CAC_WINDOW(x)				((x) << 0)
#	define CAC_WINDOW_MASK				0x00ffffff

#define DMIF_ADDW_CONFIG  				0x2F5

#define DMIF_ADDW_CAWC  				0x300

#define	PIPE0_DMIF_BUFFEW_CONTWOW			  0x0328
#       define DMIF_BUFFEWS_AWWOCATED(x)                  ((x) << 0)
#       define DMIF_BUFFEWS_AWWOCATED_COMPWETED           (1 << 4)

#define	SWBM_STATUS				        0x394
#define		GWBM_WQ_PENDING 			(1 << 5)
#define		VMC_BUSY 				(1 << 8)
#define		MCB_BUSY 				(1 << 9)
#define		MCB_NON_DISPWAY_BUSY 			(1 << 10)
#define		MCC_BUSY 				(1 << 11)
#define		MCD_BUSY 				(1 << 12)
#define		SEM_BUSY 				(1 << 14)
#define		IH_BUSY 				(1 << 17)

#define	SWBM_SOFT_WESET				        0x398
#define		SOFT_WESET_BIF				(1 << 1)
#define		SOFT_WESET_DC				(1 << 5)
#define		SOFT_WESET_DMA1				(1 << 6)
#define		SOFT_WESET_GWBM				(1 << 8)
#define		SOFT_WESET_HDP				(1 << 9)
#define		SOFT_WESET_IH				(1 << 10)
#define		SOFT_WESET_MC				(1 << 11)
#define		SOFT_WESET_WOM				(1 << 14)
#define		SOFT_WESET_SEM				(1 << 15)
#define		SOFT_WESET_VMC				(1 << 17)
#define		SOFT_WESET_DMA				(1 << 20)
#define		SOFT_WESET_TST				(1 << 21)
#define		SOFT_WESET_WEGBB			(1 << 22)
#define		SOFT_WESET_OWB				(1 << 23)

#define	CC_SYS_WB_BACKEND_DISABWE			0x3A0
#define	GC_USEW_SYS_WB_BACKEND_DISABWE			0x3A1

#define SWBM_WEAD_EWWOW					0x3A6
#define SWBM_INT_CNTW					0x3A8
#define SWBM_INT_ACK					0x3AA

#define	SWBM_STATUS2				        0x3B1
#define		DMA_BUSY 				(1 << 5)
#define		DMA1_BUSY 				(1 << 6)

#define VM_W2_CNTW					0x500
#define		ENABWE_W2_CACHE					(1 << 0)
#define		ENABWE_W2_FWAGMENT_PWOCESSING			(1 << 1)
#define		W2_CACHE_PTE_ENDIAN_SWAP_MODE(x)		((x) << 2)
#define		W2_CACHE_PDE_ENDIAN_SWAP_MODE(x)		((x) << 4)
#define		ENABWE_W2_PTE_CACHE_WWU_UPDATE_BY_WWITE		(1 << 9)
#define		ENABWE_W2_PDE0_CACHE_WWU_UPDATE_BY_WWITE	(1 << 10)
#define		EFFECTIVE_W2_QUEUE_SIZE(x)			(((x) & 7) << 15)
#define		CONTEXT1_IDENTITY_ACCESS_MODE(x)		(((x) & 3) << 19)
#define VM_W2_CNTW2					0x501
#define		INVAWIDATE_AWW_W1_TWBS				(1 << 0)
#define		INVAWIDATE_W2_CACHE				(1 << 1)
#define		INVAWIDATE_CACHE_MODE(x)			((x) << 26)
#define			INVAWIDATE_PTE_AND_PDE_CACHES		0
#define			INVAWIDATE_ONWY_PTE_CACHES		1
#define			INVAWIDATE_ONWY_PDE_CACHES		2
#define VM_W2_CNTW3					0x502
#define		BANK_SEWECT(x)					((x) << 0)
#define		W2_CACHE_UPDATE_MODE(x)				((x) << 6)
#define		W2_CACHE_BIGK_FWAGMENT_SIZE(x)			((x) << 15)
#define		W2_CACHE_BIGK_ASSOCIATIVITY			(1 << 20)
#define	VM_W2_STATUS					0x503
#define		W2_BUSY						(1 << 0)
#define VM_CONTEXT0_CNTW				0x504
#define		ENABWE_CONTEXT					(1 << 0)
#define		PAGE_TABWE_DEPTH(x)				(((x) & 3) << 1)
#define		WANGE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT		(1 << 3)
#define		WANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT		(1 << 4)
#define		DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT	(1 << 6)
#define		DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT	(1 << 7)
#define		PDE0_PWOTECTION_FAUWT_ENABWE_INTEWWUPT		(1 << 9)
#define		PDE0_PWOTECTION_FAUWT_ENABWE_DEFAUWT		(1 << 10)
#define		VAWID_PWOTECTION_FAUWT_ENABWE_INTEWWUPT		(1 << 12)
#define		VAWID_PWOTECTION_FAUWT_ENABWE_DEFAUWT		(1 << 13)
#define		WEAD_PWOTECTION_FAUWT_ENABWE_INTEWWUPT		(1 << 15)
#define		WEAD_PWOTECTION_FAUWT_ENABWE_DEFAUWT		(1 << 16)
#define		WWITE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT		(1 << 18)
#define		WWITE_PWOTECTION_FAUWT_ENABWE_DEFAUWT		(1 << 19)
#define		PAGE_TABWE_BWOCK_SIZE(x)			(((x) & 0xF) << 24)
#define VM_CONTEXT1_CNTW				0x505
#define VM_CONTEXT0_CNTW2				0x50C
#define VM_CONTEXT1_CNTW2				0x50D
#define	VM_CONTEXT8_PAGE_TABWE_BASE_ADDW		0x50E
#define	VM_CONTEXT9_PAGE_TABWE_BASE_ADDW		0x50F
#define	VM_CONTEXT10_PAGE_TABWE_BASE_ADDW		0x510
#define	VM_CONTEXT11_PAGE_TABWE_BASE_ADDW		0x511
#define	VM_CONTEXT12_PAGE_TABWE_BASE_ADDW		0x512
#define	VM_CONTEXT13_PAGE_TABWE_BASE_ADDW		0x513
#define	VM_CONTEXT14_PAGE_TABWE_BASE_ADDW		0x514
#define	VM_CONTEXT15_PAGE_TABWE_BASE_ADDW		0x515

#define	VM_CONTEXT1_PWOTECTION_FAUWT_ADDW		0x53f
#define	VM_CONTEXT1_PWOTECTION_FAUWT_STATUS		0x537
#define		PWOTECTIONS_MASK			(0xf << 0)
#define		PWOTECTIONS_SHIFT			0
		/* bit 0: wange
		 * bit 1: pde0
		 * bit 2: vawid
		 * bit 3: wead
		 * bit 4: wwite
		 */
#define		MEMOWY_CWIENT_ID_MASK			(0xff << 12)
#define		MEMOWY_CWIENT_ID_SHIFT			12
#define		MEMOWY_CWIENT_WW_MASK			(1 << 24)
#define		MEMOWY_CWIENT_WW_SHIFT			24
#define		FAUWT_VMID_MASK				(0xf << 25)
#define		FAUWT_VMID_SHIFT			25

#define VM_INVAWIDATE_WEQUEST				0x51E
#define VM_INVAWIDATE_WESPONSE				0x51F

#define VM_CONTEXT0_PWOTECTION_FAUWT_DEFAUWT_ADDW	0x546
#define VM_CONTEXT1_PWOTECTION_FAUWT_DEFAUWT_ADDW	0x547

#define	VM_CONTEXT0_PAGE_TABWE_BASE_ADDW		0x54F
#define	VM_CONTEXT1_PAGE_TABWE_BASE_ADDW		0x550
#define	VM_CONTEXT2_PAGE_TABWE_BASE_ADDW		0x551
#define	VM_CONTEXT3_PAGE_TABWE_BASE_ADDW		0x552
#define	VM_CONTEXT4_PAGE_TABWE_BASE_ADDW		0x553
#define	VM_CONTEXT5_PAGE_TABWE_BASE_ADDW		0x554
#define	VM_CONTEXT6_PAGE_TABWE_BASE_ADDW		0x555
#define	VM_CONTEXT7_PAGE_TABWE_BASE_ADDW		0x556
#define	VM_CONTEXT0_PAGE_TABWE_STAWT_ADDW		0x557
#define	VM_CONTEXT1_PAGE_TABWE_STAWT_ADDW		0x558

#define	VM_CONTEXT0_PAGE_TABWE_END_ADDW			0x55F
#define	VM_CONTEXT1_PAGE_TABWE_END_ADDW			0x560

#define VM_W2_CG           				0x570
#define		MC_CG_ENABWE				(1 << 18)
#define		MC_WS_ENABWE				(1 << 19)

#define MC_SHAWED_CHMAP						0x801
#define		NOOFCHAN_SHIFT					12
#define		NOOFCHAN_MASK					0x0000f000
#define MC_SHAWED_CHWEMAP					0x802

#define	MC_VM_FB_WOCATION				0x809
#define	MC_VM_AGP_TOP					0x80A
#define	MC_VM_AGP_BOT					0x80B
#define	MC_VM_AGP_BASE					0x80C
#define	MC_VM_SYSTEM_APEWTUWE_WOW_ADDW			0x80D
#define	MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW			0x80E
#define	MC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW		0x80F

#define	MC_VM_MX_W1_TWB_CNTW				0x819
#define		ENABWE_W1_TWB					(1 << 0)
#define		ENABWE_W1_FWAGMENT_PWOCESSING			(1 << 1)
#define		SYSTEM_ACCESS_MODE_PA_ONWY			(0 << 3)
#define		SYSTEM_ACCESS_MODE_USE_SYS_MAP			(1 << 3)
#define		SYSTEM_ACCESS_MODE_IN_SYS			(2 << 3)
#define		SYSTEM_ACCESS_MODE_NOT_IN_SYS			(3 << 3)
#define		SYSTEM_APEWTUWE_UNMAPPED_ACCESS_PASS_THWU	(0 << 5)
#define		ENABWE_ADVANCED_DWIVEW_MODEW			(1 << 6)

#define MC_SHAWED_BWACKOUT_CNTW           		0x82B

#define MC_HUB_MISC_HUB_CG           			0x82E
#define MC_HUB_MISC_VM_CG           			0x82F

#define MC_HUB_MISC_SIP_CG           			0x830

#define MC_XPB_CWK_GAT           			0x91E

#define MC_CITF_MISC_WD_CG           			0x992
#define MC_CITF_MISC_WW_CG           			0x993
#define MC_CITF_MISC_VM_CG           			0x994

#define	MC_AWB_WAMCFG					0x9D8
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
#define		CHANSIZE_OVEWWIDE				(1 << 11)
#define		NOOFGWOUPS_SHIFT				12
#define		NOOFGWOUPS_MASK					0x00001000

#define	MC_AWB_DWAM_TIMING				0x9DD
#define	MC_AWB_DWAM_TIMING2				0x9DE

#define MC_AWB_BUWST_TIME                               0xA02
#define		STATE0(x)				((x) << 0)
#define		STATE0_MASK				(0x1f << 0)
#define		STATE0_SHIFT				0
#define		STATE1(x)				((x) << 5)
#define		STATE1_MASK				(0x1f << 5)
#define		STATE1_SHIFT				5
#define		STATE2(x)				((x) << 10)
#define		STATE2_MASK				(0x1f << 10)
#define		STATE2_SHIFT				10
#define		STATE3(x)				((x) << 15)
#define		STATE3_MASK				(0x1f << 15)
#define		STATE3_SHIFT				15

#define	MC_SEQ_TWAIN_WAKEUP_CNTW			0xA3A
#define		TWAIN_DONE_D0      			(1 << 30)
#define		TWAIN_DONE_D1      			(1 << 31)

#define MC_SEQ_SUP_CNTW           			0xA32
#define		WUN_MASK      				(1 << 0)
#define MC_SEQ_SUP_PGM           			0xA33
#define MC_PMG_AUTO_CMD           			0xA34

#define MC_IO_PAD_CNTW_D0           			0xA74
#define		MEM_FAWW_OUT_CMD      			(1 << 8)

#define MC_SEQ_WAS_TIMING                               0xA28
#define MC_SEQ_CAS_TIMING                               0xA29
#define MC_SEQ_MISC_TIMING                              0xA2A
#define MC_SEQ_MISC_TIMING2                             0xA2B
#define MC_SEQ_PMG_TIMING                               0xA2C
#define MC_SEQ_WD_CTW_D0                                0xA2D
#define MC_SEQ_WD_CTW_D1                                0xA2E
#define MC_SEQ_WW_CTW_D0                                0xA2F
#define MC_SEQ_WW_CTW_D1                                0xA30

#define MC_SEQ_MISC0           				0xA80
#define 	MC_SEQ_MISC0_VEN_ID_SHIFT               8
#define 	MC_SEQ_MISC0_VEN_ID_MASK                0x00000f00
#define 	MC_SEQ_MISC0_VEN_ID_VAWUE               3
#define 	MC_SEQ_MISC0_WEV_ID_SHIFT               12
#define 	MC_SEQ_MISC0_WEV_ID_MASK                0x0000f000
#define 	MC_SEQ_MISC0_WEV_ID_VAWUE               1
#define 	MC_SEQ_MISC0_GDDW5_SHIFT                28
#define 	MC_SEQ_MISC0_GDDW5_MASK                 0xf0000000
#define 	MC_SEQ_MISC0_GDDW5_VAWUE                5
#define MC_SEQ_MISC1                                    0xA81
#define MC_SEQ_WESEWVE_M                                0xA82
#define MC_PMG_CMD_EMWS                                 0xA83

#define MC_SEQ_IO_DEBUG_INDEX           		0xA91
#define MC_SEQ_IO_DEBUG_DATA           			0xA92

#define MC_SEQ_MISC5                                    0xA95
#define MC_SEQ_MISC6                                    0xA96

#define MC_SEQ_MISC7                                    0xA99

#define MC_SEQ_WAS_TIMING_WP                            0xA9B
#define MC_SEQ_CAS_TIMING_WP                            0xA9C
#define MC_SEQ_MISC_TIMING_WP                           0xA9D
#define MC_SEQ_MISC_TIMING2_WP                          0xA9E
#define MC_SEQ_WW_CTW_D0_WP                             0xA9F
#define MC_SEQ_WW_CTW_D1_WP                             0xAA0
#define MC_SEQ_PMG_CMD_EMWS_WP                          0xAA1
#define MC_SEQ_PMG_CMD_MWS_WP                           0xAA2

#define MC_PMG_CMD_MWS                                  0xAAB

#define MC_SEQ_WD_CTW_D0_WP                             0xAC7
#define MC_SEQ_WD_CTW_D1_WP                             0xAC8

#define MC_PMG_CMD_MWS1                                 0xAD1
#define MC_SEQ_PMG_CMD_MWS1_WP                          0xAD2
#define MC_SEQ_PMG_TIMING_WP                            0xAD3

#define MC_SEQ_WW_CTW_2                                 0xAD5
#define MC_SEQ_WW_CTW_2_WP                              0xAD6
#define MC_PMG_CMD_MWS2                                 0xAD7
#define MC_SEQ_PMG_CMD_MWS2_WP                          0xAD8

#define	MCWK_PWWMGT_CNTW				0xAE8
#       define DWW_SPEED(x)				((x) << 0)
#       define DWW_SPEED_MASK				(0x1f << 0)
#       define DWW_WEADY                                (1 << 6)
#       define MC_INT_CNTW                              (1 << 7)
#       define MWDCK0_PDNB                              (1 << 8)
#       define MWDCK1_PDNB                              (1 << 9)
#       define MWDCK0_WESET                             (1 << 16)
#       define MWDCK1_WESET                             (1 << 17)
#       define DWW_WEADY_WEAD                           (1 << 24)
#define	DWW_CNTW					0xAE9
#       define MWDCK0_BYPASS                            (1 << 24)
#       define MWDCK1_BYPASS                            (1 << 25)

#define	MPWW_CNTW_MODE					0xAEC
#       define MPWW_MCWK_SEW                            (1 << 11)
#define	MPWW_FUNC_CNTW					0xAED
#define		BWCTWW(x)				((x) << 20)
#define		BWCTWW_MASK				(0xff << 20)
#define	MPWW_FUNC_CNTW_1				0xAEE
#define		VCO_MODE(x)				((x) << 0)
#define		VCO_MODE_MASK				(3 << 0)
#define		CWKFWAC(x)				((x) << 4)
#define		CWKFWAC_MASK				(0xfff << 4)
#define		CWKF(x)					((x) << 16)
#define		CWKF_MASK				(0xfff << 16)
#define	MPWW_FUNC_CNTW_2				0xAEF
#define	MPWW_AD_FUNC_CNTW				0xAF0
#define		YCWK_POST_DIV(x)			((x) << 0)
#define		YCWK_POST_DIV_MASK			(7 << 0)
#define	MPWW_DQ_FUNC_CNTW				0xAF1
#define		YCWK_SEW(x)				((x) << 4)
#define		YCWK_SEW_MASK				(1 << 4)

#define	MPWW_SS1					0xAF3
#define		CWKV(x)					((x) << 0)
#define		CWKV_MASK				(0x3ffffff << 0)
#define	MPWW_SS2					0xAF4
#define		CWKS(x)					((x) << 0)
#define		CWKS_MASK				(0xfff << 0)

#define	HDP_HOST_PATH_CNTW				0xB00
#define 	CWOCK_GATING_DIS			(1 << 23)
#define	HDP_NONSUWFACE_BASE				0xB01
#define	HDP_NONSUWFACE_INFO				0xB02
#define	HDP_NONSUWFACE_SIZE				0xB03

#define HDP_DEBUG0  					0xBCC

#define HDP_ADDW_CONFIG  				0xBD2
#define HDP_MISC_CNTW					0xBD3
#define 	HDP_FWUSH_INVAWIDATE_CACHE			(1 << 0)
#define HDP_MEM_POWEW_WS				0xBD4
#define 	HDP_WS_ENABWE				(1 << 0)

#define ATC_MISC_CG           				0xCD4

#define IH_WB_CNTW                                        0xF80
#       define IH_WB_ENABWE                               (1 << 0)
#       define IH_IB_SIZE(x)                              ((x) << 1) /* wog2 */
#       define IH_WB_FUWW_DWAIN_ENABWE                    (1 << 6)
#       define IH_WPTW_WWITEBACK_ENABWE                   (1 << 8)
#       define IH_WPTW_WWITEBACK_TIMEW(x)                 ((x) << 9) /* wog2 */
#       define IH_WPTW_OVEWFWOW_ENABWE                    (1 << 16)
#       define IH_WPTW_OVEWFWOW_CWEAW                     (1 << 31)
#define IH_WB_BASE                                        0xF81
#define IH_WB_WPTW                                        0xF82
#define IH_WB_WPTW                                        0xF83
#       define WB_OVEWFWOW                                (1 << 0)
#       define WPTW_OFFSET_MASK                           0x3fffc
#define IH_WB_WPTW_ADDW_HI                                0xF84
#define IH_WB_WPTW_ADDW_WO                                0xF85
#define IH_CNTW                                           0xF86
#       define ENABWE_INTW                                (1 << 0)
#       define IH_MC_SWAP(x)                              ((x) << 1)
#       define IH_MC_SWAP_NONE                            0
#       define IH_MC_SWAP_16BIT                           1
#       define IH_MC_SWAP_32BIT                           2
#       define IH_MC_SWAP_64BIT                           3
#       define WPTW_WEAWM                                 (1 << 4)
#       define MC_WWWEQ_CWEDIT(x)                         ((x) << 15)
#       define MC_WW_CWEAN_CNT(x)                         ((x) << 20)
#       define MC_VMID(x)                                 ((x) << 25)

#define	CONFIG_MEMSIZE					0x150A

#define INTEWWUPT_CNTW                                    0x151A
#       define IH_DUMMY_WD_OVEWWIDE                       (1 << 0)
#       define IH_DUMMY_WD_EN                             (1 << 1)
#       define IH_WEQ_NONSNOOP_EN                         (1 << 3)
#       define GEN_IH_INT_EN                              (1 << 8)
#define INTEWWUPT_CNTW2                                   0x151B

#define HDP_MEM_COHEWENCY_FWUSH_CNTW			0x1520

#define	BIF_FB_EN						0x1524
#define		FB_WEAD_EN					(1 << 0)
#define		FB_WWITE_EN					(1 << 1)

#define HDP_WEG_COHEWENCY_FWUSH_CNTW			0x1528

/* DCE6 EWD audio intewface */
#define AZ_F0_CODEC_ENDPOINT_INDEX                       0x1780
#       define AZ_ENDPOINT_WEG_INDEX(x)                  (((x) & 0xff) << 0)
#       define AZ_ENDPOINT_WEG_WWITE_EN                  (1 << 8)
#define AZ_F0_CODEC_ENDPOINT_DATA                        0x1781

#define AZ_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW          0x25
#define		SPEAKEW_AWWOCATION(x)			(((x) & 0x7f) << 0)
#define		SPEAKEW_AWWOCATION_MASK			(0x7f << 0)
#define		SPEAKEW_AWWOCATION_SHIFT		0
#define		HDMI_CONNECTION				(1 << 16)
#define		DP_CONNECTION				(1 << 17)

#define AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW0        0x28 /* WPCM */
#define AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW1        0x29 /* AC3 */
#define AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW2        0x2A /* MPEG1 */
#define AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW3        0x2B /* MP3 */
#define AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW4        0x2C /* MPEG2 */
#define AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW5        0x2D /* AAC */
#define AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW6        0x2E /* DTS */
#define AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW7        0x2F /* ATWAC */
#define AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW8        0x30 /* one bit audio - weave at 0 (defauwt) */
#define AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW9        0x31 /* Dowby Digitaw */
#define AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW10       0x32 /* DTS-HD */
#define AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW11       0x33 /* MAT-MWP */
#define AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW12       0x34 /* DTS */
#define AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW13       0x35 /* WMA Pwo */
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

#define AZ_F0_CODEC_PIN_CONTWOW_WESPONSE_WIPSYNC         0x37
#       define VIDEO_WIPSYNC(x)                           (((x) & 0xff) << 0)
#       define AUDIO_WIPSYNC(x)                           (((x) & 0xff) << 8)
/* VIDEO_WIPSYNC, AUDIO_WIPSYNC
 * 0   = invawid
 * x   = wegaw deway vawue
 * 255 = sync not suppowted
 */
#define AZ_F0_CODEC_PIN_CONTWOW_WESPONSE_HBW             0x38
#       define HBW_CAPABWE                                (1 << 0) /* enabwed by defauwt */

#define AZ_F0_CODEC_PIN_CONTWOW_SINK_INFO0               0x3a
#       define MANUFACTUWEW_ID(x)                        (((x) & 0xffff) << 0)
#       define PWODUCT_ID(x)                             (((x) & 0xffff) << 16)
#define AZ_F0_CODEC_PIN_CONTWOW_SINK_INFO1               0x3b
#       define SINK_DESCWIPTION_WEN(x)                   (((x) & 0xff) << 0)
#define AZ_F0_CODEC_PIN_CONTWOW_SINK_INFO2               0x3c
#       define POWT_ID0(x)                               (((x) & 0xffffffff) << 0)
#define AZ_F0_CODEC_PIN_CONTWOW_SINK_INFO3               0x3d
#       define POWT_ID1(x)                               (((x) & 0xffffffff) << 0)
#define AZ_F0_CODEC_PIN_CONTWOW_SINK_INFO4               0x3e
#       define DESCWIPTION0(x)                           (((x) & 0xff) << 0)
#       define DESCWIPTION1(x)                           (((x) & 0xff) << 8)
#       define DESCWIPTION2(x)                           (((x) & 0xff) << 16)
#       define DESCWIPTION3(x)                           (((x) & 0xff) << 24)
#define AZ_F0_CODEC_PIN_CONTWOW_SINK_INFO5               0x3f
#       define DESCWIPTION4(x)                           (((x) & 0xff) << 0)
#       define DESCWIPTION5(x)                           (((x) & 0xff) << 8)
#       define DESCWIPTION6(x)                           (((x) & 0xff) << 16)
#       define DESCWIPTION7(x)                           (((x) & 0xff) << 24)
#define AZ_F0_CODEC_PIN_CONTWOW_SINK_INFO6               0x40
#       define DESCWIPTION8(x)                           (((x) & 0xff) << 0)
#       define DESCWIPTION9(x)                           (((x) & 0xff) << 8)
#       define DESCWIPTION10(x)                          (((x) & 0xff) << 16)
#       define DESCWIPTION11(x)                          (((x) & 0xff) << 24)
#define AZ_F0_CODEC_PIN_CONTWOW_SINK_INFO7               0x41
#       define DESCWIPTION12(x)                          (((x) & 0xff) << 0)
#       define DESCWIPTION13(x)                          (((x) & 0xff) << 8)
#       define DESCWIPTION14(x)                          (((x) & 0xff) << 16)
#       define DESCWIPTION15(x)                          (((x) & 0xff) << 24)
#define AZ_F0_CODEC_PIN_CONTWOW_SINK_INFO8               0x42
#       define DESCWIPTION16(x)                          (((x) & 0xff) << 0)
#       define DESCWIPTION17(x)                          (((x) & 0xff) << 8)

#define AZ_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW         0x54
#       define AUDIO_ENABWED                             (1 << 31)

#define AZ_F0_CODEC_PIN_CONTWOW_WESPONSE_CONFIGUWATION_DEFAUWT  0x56
#define		POWT_CONNECTIVITY_MASK				(3 << 30)
#define		POWT_CONNECTIVITY_SHIFT				30

#define	DC_WB_MEMOWY_SPWIT					0x1AC3
#define		DC_WB_MEMOWY_CONFIG(x)				((x) << 20)

#define	PWIOWITY_A_CNT						0x1AC6
#define		PWIOWITY_MAWK_MASK				0x7fff
#define		PWIOWITY_OFF					(1 << 16)
#define		PWIOWITY_AWWAYS_ON				(1 << 20)
#define	PWIOWITY_B_CNT						0x1AC7

#define	DPG_PIPE_AWBITWATION_CONTWOW3				0x1B32
#       define WATENCY_WATEWMAWK_MASK(x)			((x) << 16)
#define	DPG_PIPE_WATENCY_CONTWOW				0x1B33
#       define WATENCY_WOW_WATEWMAWK(x)				((x) << 0)
#       define WATENCY_HIGH_WATEWMAWK(x)			((x) << 16)

/* 0x6bb8, 0x77b8, 0x103b8, 0x10fb8, 0x11bb8, 0x127b8 */
#define VWINE_STATUS                                    0x1AEE
#       define VWINE_OCCUWWED                           (1 << 0)
#       define VWINE_ACK                                (1 << 4)
#       define VWINE_STAT                               (1 << 12)
#       define VWINE_INTEWWUPT                          (1 << 16)
#       define VWINE_INTEWWUPT_TYPE                     (1 << 17)
/* 0x6bbc, 0x77bc, 0x103bc, 0x10fbc, 0x11bbc, 0x127bc */
#define VBWANK_STATUS                                   0x1AEF
#       define VBWANK_OCCUWWED                          (1 << 0)
#       define VBWANK_ACK                               (1 << 4)
#       define VBWANK_STAT                              (1 << 12)
#       define VBWANK_INTEWWUPT                         (1 << 16)
#       define VBWANK_INTEWWUPT_TYPE                    (1 << 17)

/* 0x6b40, 0x7740, 0x10340, 0x10f40, 0x11b40, 0x12740 */
#define INT_MASK                                        0x1AD0
#       define VBWANK_INT_MASK                          (1 << 0)
#       define VWINE_INT_MASK                           (1 << 4)

#define DISP_INTEWWUPT_STATUS                           0x183D
#       define WB_D1_VWINE_INTEWWUPT                    (1 << 2)
#       define WB_D1_VBWANK_INTEWWUPT                   (1 << 3)
#       define DC_HPD1_INTEWWUPT                        (1 << 17)
#       define DC_HPD1_WX_INTEWWUPT                     (1 << 18)
#       define DACA_AUTODETECT_INTEWWUPT                (1 << 22)
#       define DACB_AUTODETECT_INTEWWUPT                (1 << 23)
#       define DC_I2C_SW_DONE_INTEWWUPT                 (1 << 24)
#       define DC_I2C_HW_DONE_INTEWWUPT                 (1 << 25)
#define DISP_INTEWWUPT_STATUS_CONTINUE                  0x183E
#       define WB_D2_VWINE_INTEWWUPT                    (1 << 2)
#       define WB_D2_VBWANK_INTEWWUPT                   (1 << 3)
#       define DC_HPD2_INTEWWUPT                        (1 << 17)
#       define DC_HPD2_WX_INTEWWUPT                     (1 << 18)
#       define DISP_TIMEW_INTEWWUPT                     (1 << 24)
#define DISP_INTEWWUPT_STATUS_CONTINUE2                 0x183F
#       define WB_D3_VWINE_INTEWWUPT                    (1 << 2)
#       define WB_D3_VBWANK_INTEWWUPT                   (1 << 3)
#       define DC_HPD3_INTEWWUPT                        (1 << 17)
#       define DC_HPD3_WX_INTEWWUPT                     (1 << 18)
#define DISP_INTEWWUPT_STATUS_CONTINUE3                 0x1840
#       define WB_D4_VWINE_INTEWWUPT                    (1 << 2)
#       define WB_D4_VBWANK_INTEWWUPT                   (1 << 3)
#       define DC_HPD4_INTEWWUPT                        (1 << 17)
#       define DC_HPD4_WX_INTEWWUPT                     (1 << 18)
#define DISP_INTEWWUPT_STATUS_CONTINUE4                 0x1853
#       define WB_D5_VWINE_INTEWWUPT                    (1 << 2)
#       define WB_D5_VBWANK_INTEWWUPT                   (1 << 3)
#       define DC_HPD5_INTEWWUPT                        (1 << 17)
#       define DC_HPD5_WX_INTEWWUPT                     (1 << 18)
#define DISP_INTEWWUPT_STATUS_CONTINUE5                 0x1854
#       define WB_D6_VWINE_INTEWWUPT                    (1 << 2)
#       define WB_D6_VBWANK_INTEWWUPT                   (1 << 3)
#       define DC_HPD6_INTEWWUPT                        (1 << 17)
#       define DC_HPD6_WX_INTEWWUPT                     (1 << 18)

/* 0x6858, 0x7458, 0x10058, 0x10c58, 0x11858, 0x12458 */
#define GWPH_INT_STATUS                                 0x1A16
#       define GWPH_PFWIP_INT_OCCUWWED                  (1 << 0)
#       define GWPH_PFWIP_INT_CWEAW                     (1 << 8)
/* 0x685c, 0x745c, 0x1005c, 0x10c5c, 0x1185c, 0x1245c */
#define	GWPH_INT_CONTWOW			        0x1A17
#       define GWPH_PFWIP_INT_MASK                      (1 << 0)
#       define GWPH_PFWIP_INT_TYPE                      (1 << 8)

#define	DAC_AUTODETECT_INT_CONTWOW			0x19F2

#define DC_HPD1_INT_STATUS                              0x1807
#define DC_HPD2_INT_STATUS                              0x180A
#define DC_HPD3_INT_STATUS                              0x180D
#define DC_HPD4_INT_STATUS                              0x1810
#define DC_HPD5_INT_STATUS                              0x1813
#define DC_HPD6_INT_STATUS                              0x1816
#       define DC_HPDx_INT_STATUS                       (1 << 0)
#       define DC_HPDx_SENSE                            (1 << 1)
#       define DC_HPDx_WX_INT_STATUS                    (1 << 8)

#define DC_HPD1_INT_CONTWOW                             0x1808
#define DC_HPD2_INT_CONTWOW                             0x180B
#define DC_HPD3_INT_CONTWOW                             0x180E
#define DC_HPD4_INT_CONTWOW                             0x1811
#define DC_HPD5_INT_CONTWOW                             0x1814
#define DC_HPD6_INT_CONTWOW                             0x1817
#       define DC_HPDx_INT_ACK                          (1 << 0)
#       define DC_HPDx_INT_POWAWITY                     (1 << 8)
#       define DC_HPDx_INT_EN                           (1 << 16)
#       define DC_HPDx_WX_INT_ACK                       (1 << 20)
#       define DC_HPDx_WX_INT_EN                        (1 << 24)

#define DC_HPD1_CONTWOW                                   0x1809
#define DC_HPD2_CONTWOW                                   0x180C
#define DC_HPD3_CONTWOW                                   0x180F
#define DC_HPD4_CONTWOW                                   0x1812
#define DC_HPD5_CONTWOW                                   0x1815
#define DC_HPD6_CONTWOW                                   0x1818
#       define DC_HPDx_CONNECTION_TIMEW(x)                ((x) << 0)
#       define DC_HPDx_WX_INT_TIMEW(x)                    ((x) << 16)
#       define DC_HPDx_EN                                 (1 << 28)

#define DPG_PIPE_STUTTEW_CONTWOW                          0x1B35
#       define STUTTEW_ENABWE                             (1 << 0)

/* 0x6e98, 0x7a98, 0x10698, 0x11298, 0x11e98, 0x12a98 */
#define CWTC_STATUS_FWAME_COUNT                         0x1BA6

/* Audio cwocks */
#define DCCG_AUDIO_DTO_SOUWCE                           0x05ac
#       define DCCG_AUDIO_DTO0_SOUWCE_SEW(x) ((x) << 0) /* cwtc0 - cwtc5 */
#       define DCCG_AUDIO_DTO_SEW            (1 << 4)   /* 0=dto0 1=dto1 */

#define DCCG_AUDIO_DTO0_PHASE                           0x05b0
#define DCCG_AUDIO_DTO0_MODUWE                          0x05b4
#define DCCG_AUDIO_DTO1_PHASE                           0x05c0
#define DCCG_AUDIO_DTO1_MODUWE                          0x05c4

#define AFMT_AUDIO_SWC_CONTWOW                          0x1c4f
#define		AFMT_AUDIO_SWC_SEWECT(x)		(((x) & 7) << 0)
/* AFMT_AUDIO_SWC_SEWECT
 * 0 = stweam0
 * 1 = stweam1
 * 2 = stweam2
 * 3 = stweam3
 * 4 = stweam4
 * 5 = stweam5
 */

#define	GWBM_CNTW					0x2000
#define		GWBM_WEAD_TIMEOUT(x)				((x) << 0)

#define	GWBM_STATUS2					0x2002
#define		WWC_WQ_PENDING 					(1 << 0)
#define		WWC_BUSY 					(1 << 8)
#define		TC_BUSY 					(1 << 9)

#define	GWBM_STATUS					0x2004
#define		CMDFIFO_AVAIW_MASK				0x0000000F
#define		WING2_WQ_PENDING				(1 << 4)
#define		SWBM_WQ_PENDING					(1 << 5)
#define		WING1_WQ_PENDING				(1 << 6)
#define		CF_WQ_PENDING					(1 << 7)
#define		PF_WQ_PENDING					(1 << 8)
#define		GDS_DMA_WQ_PENDING				(1 << 9)
#define		GWBM_EE_BUSY					(1 << 10)
#define		DB_CWEAN					(1 << 12)
#define		CB_CWEAN					(1 << 13)
#define		TA_BUSY 					(1 << 14)
#define		GDS_BUSY 					(1 << 15)
#define		VGT_BUSY					(1 << 17)
#define		IA_BUSY_NO_DMA					(1 << 18)
#define		IA_BUSY						(1 << 19)
#define		SX_BUSY 					(1 << 20)
#define		SPI_BUSY					(1 << 22)
#define		BCI_BUSY					(1 << 23)
#define		SC_BUSY 					(1 << 24)
#define		PA_BUSY 					(1 << 25)
#define		DB_BUSY 					(1 << 26)
#define		CP_COHEWENCY_BUSY      				(1 << 28)
#define		CP_BUSY 					(1 << 29)
#define		CB_BUSY 					(1 << 30)
#define		GUI_ACTIVE					(1 << 31)
#define	GWBM_STATUS_SE0					0x2005
#define	GWBM_STATUS_SE1					0x2006
#define		SE_DB_CWEAN					(1 << 1)
#define		SE_CB_CWEAN					(1 << 2)
#define		SE_BCI_BUSY					(1 << 22)
#define		SE_VGT_BUSY					(1 << 23)
#define		SE_PA_BUSY					(1 << 24)
#define		SE_TA_BUSY					(1 << 25)
#define		SE_SX_BUSY					(1 << 26)
#define		SE_SPI_BUSY					(1 << 27)
#define		SE_SC_BUSY					(1 << 29)
#define		SE_DB_BUSY					(1 << 30)
#define		SE_CB_BUSY					(1 << 31)

#define	GWBM_SOFT_WESET					0x2008
#define		SOFT_WESET_CP					(1 << 0)
#define		SOFT_WESET_CB					(1 << 1)
#define		SOFT_WESET_WWC					(1 << 2)
#define		SOFT_WESET_DB					(1 << 3)
#define		SOFT_WESET_GDS					(1 << 4)
#define		SOFT_WESET_PA					(1 << 5)
#define		SOFT_WESET_SC					(1 << 6)
#define		SOFT_WESET_BCI					(1 << 7)
#define		SOFT_WESET_SPI					(1 << 8)
#define		SOFT_WESET_SX					(1 << 10)
#define		SOFT_WESET_TC					(1 << 11)
#define		SOFT_WESET_TA					(1 << 12)
#define		SOFT_WESET_VGT					(1 << 14)
#define		SOFT_WESET_IA					(1 << 15)

#define GWBM_GFX_INDEX          			0x200B
#define		INSTANCE_INDEX(x)			((x) << 0)
#define		SH_INDEX(x)     			((x) << 8)
#define		SE_INDEX(x)     			((x) << 16)
#define		SH_BWOADCAST_WWITES      		(1 << 29)
#define		INSTANCE_BWOADCAST_WWITES      		(1 << 30)
#define		SE_BWOADCAST_WWITES      		(1 << 31)

#define GWBM_INT_CNTW                                   0x2018
#       define WDEWW_INT_ENABWE                         (1 << 0)
#       define GUI_IDWE_INT_ENABWE                      (1 << 19)

#define	CP_STWMOUT_CNTW					0x213F
#define	SCWATCH_WEG0					0x2140
#define	SCWATCH_WEG1					0x2141
#define	SCWATCH_WEG2					0x2142
#define	SCWATCH_WEG3					0x2143
#define	SCWATCH_WEG4					0x2144
#define	SCWATCH_WEG5					0x2145
#define	SCWATCH_WEG6					0x2146
#define	SCWATCH_WEG7					0x2147

#define	SCWATCH_UMSK					0x2150
#define	SCWATCH_ADDW					0x2151

#define	CP_SEM_WAIT_TIMEW				0x216F

#define	CP_SEM_INCOMPWETE_TIMEW_CNTW			0x2172

#define CP_ME_CNTW					0x21B6
#define		CP_CE_HAWT					(1 << 24)
#define		CP_PFP_HAWT					(1 << 26)
#define		CP_ME_HAWT					(1 << 28)

#define	CP_COHEW_CNTW2					0x217A

#define	CP_WB2_WPTW					0x21BE
#define	CP_WB1_WPTW					0x21BF
#define	CP_WB0_WPTW					0x21C0
#define	CP_WB_WPTW_DEWAY				0x21C1

#define	CP_QUEUE_THWESHOWDS				0x21D8
#define		WOQ_IB1_STAWT(x)				((x) << 0)
#define		WOQ_IB2_STAWT(x)				((x) << 8)
#define CP_MEQ_THWESHOWDS				0x21D9
#define		MEQ1_STAWT(x)				((x) << 0)
#define		MEQ2_STAWT(x)				((x) << 8)

#define	CP_PEWFMON_CNTW					0x21FF

#define	VGT_VTX_VECT_EJECT_WEG				0x222C

#define	VGT_CACHE_INVAWIDATION				0x2231
#define		CACHE_INVAWIDATION(x)				((x) << 0)
#define			VC_ONWY						0
#define			TC_ONWY						1
#define			VC_AND_TC					2
#define		AUTO_INVWD_EN(x)				((x) << 6)
#define			NO_AUTO						0
#define			ES_AUTO						1
#define			GS_AUTO						2
#define			ES_AND_GS_AUTO					3
#define	VGT_ESGS_WING_SIZE				0x2232
#define	VGT_GSVS_WING_SIZE				0x2233

#define	VGT_GS_VEWTEX_WEUSE				0x2235

#define	VGT_PWIMITIVE_TYPE				0x2256
#define	VGT_INDEX_TYPE					0x2257

#define	VGT_NUM_INDICES					0x225C
#define	VGT_NUM_INSTANCES				0x225D

#define	VGT_TF_WING_SIZE				0x2262

#define	VGT_HS_OFFCHIP_PAWAM				0x226C

#define	VGT_TF_MEMOWY_BASE				0x226E

#define CC_GC_SHADEW_AWWAY_CONFIG			0x226F
#define		INACTIVE_CUS_MASK			0xFFFF0000
#define		INACTIVE_CUS_SHIFT			16
#define GC_USEW_SHADEW_AWWAY_CONFIG			0x2270

#define	PA_CW_ENHANCE					0x2285
#define		CWIP_VTX_WEOWDEW_ENA				(1 << 0)
#define		NUM_CWIP_SEQ(x)					((x) << 1)

#define	PA_SU_WINE_STIPPWE_VAWUE			0x2298

#define	PA_SC_WINE_STIPPWE_STATE			0x22C4

#define	PA_SC_FOWCE_EOV_MAX_CNTS			0x22C9
#define		FOWCE_EOV_MAX_CWK_CNT(x)			((x) << 0)
#define		FOWCE_EOV_MAX_WEZ_CNT(x)			((x) << 16)

#define	PA_SC_FIFO_SIZE					0x22F3
#define		SC_FWONTEND_PWIM_FIFO_SIZE(x)			((x) << 0)
#define		SC_BACKEND_PWIM_FIFO_SIZE(x)			((x) << 6)
#define		SC_HIZ_TIWE_FIFO_SIZE(x)			((x) << 15)
#define		SC_EAWWYZ_TIWE_FIFO_SIZE(x)			((x) << 23)

#define	PA_SC_ENHANCE					0x22FC

#define	SQ_CONFIG					0x2300

#define	SQC_CACHES					0x2302

#define SQ_POWEW_THWOTTWE                               0x2396
#define		MIN_POWEW(x)				((x) << 0)
#define		MIN_POWEW_MASK				(0x3fff << 0)
#define		MIN_POWEW_SHIFT				0
#define		MAX_POWEW(x)				((x) << 16)
#define		MAX_POWEW_MASK				(0x3fff << 16)
#define		MAX_POWEW_SHIFT				0
#define SQ_POWEW_THWOTTWE2                              0x2397
#define		MAX_POWEW_DEWTA(x)			((x) << 0)
#define		MAX_POWEW_DEWTA_MASK			(0x3fff << 0)
#define		MAX_POWEW_DEWTA_SHIFT			0
#define		STI_SIZE(x)				((x) << 16)
#define		STI_SIZE_MASK				(0x3ff << 16)
#define		STI_SIZE_SHIFT				16
#define		WTI_WATIO(x)				((x) << 27)
#define		WTI_WATIO_MASK				(0xf << 27)
#define		WTI_WATIO_SHIFT				27

#define	SX_DEBUG_1					0x2418

#define	SPI_STATIC_THWEAD_MGMT_1			0x2438
#define	SPI_STATIC_THWEAD_MGMT_2			0x2439
#define	SPI_STATIC_THWEAD_MGMT_3			0x243A
#define	SPI_PS_MAX_WAVE_ID				0x243B

#define	SPI_CONFIG_CNTW					0x2440

#define	SPI_CONFIG_CNTW_1				0x244F
#define		VTX_DONE_DEWAY(x)				((x) << 0)
#define		INTEWP_ONE_PWIM_PEW_WOW				(1 << 4)

#define	CGTS_TCC_DISABWE				0x2452
#define	CGTS_USEW_TCC_DISABWE				0x2453
#define		TCC_DISABWE_MASK				0xFFFF0000
#define		TCC_DISABWE_SHIFT				16
#define	CGTS_SM_CTWW_WEG				0x2454
#define		OVEWWIDE				(1 << 21)
#define		WS_OVEWWIDE				(1 << 22)

#define	SPI_WB_CU_MASK					0x24D5

#define	TA_CNTW_AUX					0x2542

#define CC_WB_BACKEND_DISABWE				0x263D
#define		BACKEND_DISABWE(x)     			((x) << 16)
#define GB_ADDW_CONFIG  				0x263E
#define		NUM_PIPES(x)				((x) << 0)
#define		NUM_PIPES_MASK				0x00000007
#define		NUM_PIPES_SHIFT				0
#define		PIPE_INTEWWEAVE_SIZE(x)			((x) << 4)
#define		PIPE_INTEWWEAVE_SIZE_MASK		0x00000070
#define		PIPE_INTEWWEAVE_SIZE_SHIFT		4
#define		NUM_SHADEW_ENGINES(x)			((x) << 12)
#define		NUM_SHADEW_ENGINES_MASK			0x00003000
#define		NUM_SHADEW_ENGINES_SHIFT		12
#define		SHADEW_ENGINE_TIWE_SIZE(x)     		((x) << 16)
#define		SHADEW_ENGINE_TIWE_SIZE_MASK		0x00070000
#define		SHADEW_ENGINE_TIWE_SIZE_SHIFT		16
#define		NUM_GPUS(x)     			((x) << 20)
#define		NUM_GPUS_MASK				0x00700000
#define		NUM_GPUS_SHIFT				20
#define		MUWTI_GPU_TIWE_SIZE(x)     		((x) << 24)
#define		MUWTI_GPU_TIWE_SIZE_MASK		0x03000000
#define		MUWTI_GPU_TIWE_SIZE_SHIFT		24
#define		WOW_SIZE(x)             		((x) << 28)
#define		WOW_SIZE_MASK				0x30000000
#define		WOW_SIZE_SHIFT				28

#define	GB_TIWE_MODE0					0x2644
#       define MICWO_TIWE_MODE(x)				((x) << 0)
#              define	ADDW_SUWF_DISPWAY_MICWO_TIWING		0
#              define	ADDW_SUWF_THIN_MICWO_TIWING		1
#              define	ADDW_SUWF_DEPTH_MICWO_TIWING		2
#       define AWWAY_MODE(x)					((x) << 2)
#              define	AWWAY_WINEAW_GENEWAW			0
#              define	AWWAY_WINEAW_AWIGNED			1
#              define	AWWAY_1D_TIWED_THIN1			2
#              define	AWWAY_2D_TIWED_THIN1			4
#       define PIPE_CONFIG(x)					((x) << 6)
#              define	ADDW_SUWF_P2				0
#              define	ADDW_SUWF_P4_8x16			4
#              define	ADDW_SUWF_P4_16x16			5
#              define	ADDW_SUWF_P4_16x32			6
#              define	ADDW_SUWF_P4_32x32			7
#              define	ADDW_SUWF_P8_16x16_8x16			8
#              define	ADDW_SUWF_P8_16x32_8x16			9
#              define	ADDW_SUWF_P8_32x32_8x16			10
#              define	ADDW_SUWF_P8_16x32_16x16		11
#              define	ADDW_SUWF_P8_32x32_16x16		12
#              define	ADDW_SUWF_P8_32x32_16x32		13
#              define	ADDW_SUWF_P8_32x64_32x32		14
#       define TIWE_SPWIT(x)					((x) << 11)
#              define	ADDW_SUWF_TIWE_SPWIT_64B		0
#              define	ADDW_SUWF_TIWE_SPWIT_128B		1
#              define	ADDW_SUWF_TIWE_SPWIT_256B		2
#              define	ADDW_SUWF_TIWE_SPWIT_512B		3
#              define	ADDW_SUWF_TIWE_SPWIT_1KB		4
#              define	ADDW_SUWF_TIWE_SPWIT_2KB		5
#              define	ADDW_SUWF_TIWE_SPWIT_4KB		6
#       define BANK_WIDTH(x)					((x) << 14)
#              define	ADDW_SUWF_BANK_WIDTH_1			0
#              define	ADDW_SUWF_BANK_WIDTH_2			1
#              define	ADDW_SUWF_BANK_WIDTH_4			2
#              define	ADDW_SUWF_BANK_WIDTH_8			3
#       define BANK_HEIGHT(x)					((x) << 16)
#              define	ADDW_SUWF_BANK_HEIGHT_1			0
#              define	ADDW_SUWF_BANK_HEIGHT_2			1
#              define	ADDW_SUWF_BANK_HEIGHT_4			2
#              define	ADDW_SUWF_BANK_HEIGHT_8			3
#       define MACWO_TIWE_ASPECT(x)				((x) << 18)
#              define	ADDW_SUWF_MACWO_ASPECT_1		0
#              define	ADDW_SUWF_MACWO_ASPECT_2		1
#              define	ADDW_SUWF_MACWO_ASPECT_4		2
#              define	ADDW_SUWF_MACWO_ASPECT_8		3
#       define NUM_BANKS(x)					((x) << 20)
#              define	ADDW_SUWF_2_BANK			0
#              define	ADDW_SUWF_4_BANK			1
#              define	ADDW_SUWF_8_BANK			2
#              define	ADDW_SUWF_16_BANK			3
#define	GB_TIWE_MODE1					0x2645
#define	GB_TIWE_MODE2					0x2646
#define	GB_TIWE_MODE3					0x2647
#define	GB_TIWE_MODE4					0x2648
#define	GB_TIWE_MODE5					0x2649
#define	GB_TIWE_MODE6					0x264a
#define	GB_TIWE_MODE7					0x264b
#define	GB_TIWE_MODE8					0x264c
#define	GB_TIWE_MODE9					0x264d
#define	GB_TIWE_MODE10					0x264e
#define	GB_TIWE_MODE11					0x264f
#define	GB_TIWE_MODE12					0x2650
#define	GB_TIWE_MODE13					0x2651
#define	GB_TIWE_MODE14					0x2652
#define	GB_TIWE_MODE15					0x2653
#define	GB_TIWE_MODE16					0x2654
#define	GB_TIWE_MODE17					0x2655
#define	GB_TIWE_MODE18					0x2656
#define	GB_TIWE_MODE19					0x2657
#define	GB_TIWE_MODE20					0x2658
#define	GB_TIWE_MODE21					0x2659
#define	GB_TIWE_MODE22					0x265a
#define	GB_TIWE_MODE23					0x265b
#define	GB_TIWE_MODE24					0x265c
#define	GB_TIWE_MODE25					0x265d
#define	GB_TIWE_MODE26					0x265e
#define	GB_TIWE_MODE27					0x265f
#define	GB_TIWE_MODE28					0x2660
#define	GB_TIWE_MODE29					0x2661
#define	GB_TIWE_MODE30					0x2662
#define	GB_TIWE_MODE31					0x2663

#define	CB_PEWFCOUNTEW0_SEWECT0				0x2688
#define	CB_PEWFCOUNTEW0_SEWECT1				0x2689
#define	CB_PEWFCOUNTEW1_SEWECT0				0x268A
#define	CB_PEWFCOUNTEW1_SEWECT1				0x268B
#define	CB_PEWFCOUNTEW2_SEWECT0				0x268C
#define	CB_PEWFCOUNTEW2_SEWECT1				0x268D
#define	CB_PEWFCOUNTEW3_SEWECT0				0x268E
#define	CB_PEWFCOUNTEW3_SEWECT1				0x268F

#define	CB_CGTT_SCWK_CTWW				0x2698

#define	GC_USEW_WB_BACKEND_DISABWE			0x26DF
#define		BACKEND_DISABWE_MASK			0x00FF0000
#define		BACKEND_DISABWE_SHIFT			16

#define	TCP_CHAN_STEEW_WO				0x2B03
#define	TCP_CHAN_STEEW_HI				0x2B94

#define	CP_WB0_BASE					0x3040
#define	CP_WB0_CNTW					0x3041
#define		WB_BUFSZ(x)					((x) << 0)
#define		WB_BWKSZ(x)					((x) << 8)
#define		BUF_SWAP_32BIT					(2 << 16)
#define		WB_NO_UPDATE					(1 << 27)
#define		WB_WPTW_WW_ENA					(1 << 31)

#define	CP_WB0_WPTW_ADDW				0x3043
#define	CP_WB0_WPTW_ADDW_HI				0x3044
#define	CP_WB0_WPTW					0x3045

#define	CP_PFP_UCODE_ADDW				0x3054
#define	CP_PFP_UCODE_DATA				0x3055
#define	CP_ME_WAM_WADDW					0x3056
#define	CP_ME_WAM_WADDW					0x3057
#define	CP_ME_WAM_DATA					0x3058

#define	CP_CE_UCODE_ADDW				0x305A
#define	CP_CE_UCODE_DATA				0x305B

#define	CP_WB1_BASE					0x3060
#define	CP_WB1_CNTW					0x3061
#define	CP_WB1_WPTW_ADDW				0x3062
#define	CP_WB1_WPTW_ADDW_HI				0x3063
#define	CP_WB1_WPTW					0x3064
#define	CP_WB2_BASE					0x3065
#define	CP_WB2_CNTW					0x3066
#define	CP_WB2_WPTW_ADDW				0x3067
#define	CP_WB2_WPTW_ADDW_HI				0x3068
#define	CP_WB2_WPTW					0x3069
#define CP_INT_CNTW_WING0                               0x306A
#define CP_INT_CNTW_WING1                               0x306B
#define CP_INT_CNTW_WING2                               0x306C
#       define CNTX_BUSY_INT_ENABWE                     (1 << 19)
#       define CNTX_EMPTY_INT_ENABWE                    (1 << 20)
#       define WAIT_MEM_SEM_INT_ENABWE                  (1 << 21)
#       define TIME_STAMP_INT_ENABWE                    (1 << 26)
#       define CP_WINGID2_INT_ENABWE                    (1 << 29)
#       define CP_WINGID1_INT_ENABWE                    (1 << 30)
#       define CP_WINGID0_INT_ENABWE                    (1 << 31)
#define CP_INT_STATUS_WING0                             0x306D
#define CP_INT_STATUS_WING1                             0x306E
#define CP_INT_STATUS_WING2                             0x306F
#       define WAIT_MEM_SEM_INT_STAT                    (1 << 21)
#       define TIME_STAMP_INT_STAT                      (1 << 26)
#       define CP_WINGID2_INT_STAT                      (1 << 29)
#       define CP_WINGID1_INT_STAT                      (1 << 30)
#       define CP_WINGID0_INT_STAT                      (1 << 31)

#define	CP_MEM_SWP_CNTW					0x3079
#       define CP_MEM_WS_EN                             (1 << 0)

#define	CP_DEBUG					0x307F

#define WWC_CNTW                                          0x30C0
#       define WWC_ENABWE                                 (1 << 0)
#define WWC_WW_BASE                                       0x30C1
#define WWC_WW_SIZE                                       0x30C2
#define WWC_WB_CNTW                                       0x30C3
#       define WOAD_BAWANCE_ENABWE                        (1 << 0)
#define WWC_SAVE_AND_WESTOWE_BASE                         0x30C4
#define WWC_WB_CNTW_MAX                                   0x30C5
#define WWC_WB_CNTW_INIT                                  0x30C6

#define WWC_CWEAW_STATE_WESTOWE_BASE                      0x30C8

#define WWC_UCODE_ADDW                                    0x30CB
#define WWC_UCODE_DATA                                    0x30CC

#define WWC_GPU_CWOCK_COUNT_WSB                           0x30CE
#define WWC_GPU_CWOCK_COUNT_MSB                           0x30CF
#define WWC_CAPTUWE_GPU_CWOCK_COUNT                       0x30D0
#define WWC_MC_CNTW                                       0x30D1
#define WWC_UCODE_CNTW                                    0x30D2
#define WWC_STAT                                          0x30D3
#       define WWC_BUSY_STATUS                            (1 << 0)
#       define GFX_POWEW_STATUS                           (1 << 1)
#       define GFX_CWOCK_STATUS                           (1 << 2)
#       define GFX_WS_STATUS                              (1 << 3)

#define	WWC_PG_CNTW					0x30D7
#	define GFX_PG_ENABWE				(1 << 0)
#	define GFX_PG_SWC				(1 << 1)

#define	WWC_CGTT_MGCG_OVEWWIDE				0x3100
#define	WWC_CGCG_CGWS_CTWW				0x3101
#	define CGCG_EN					(1 << 0)
#	define CGWS_EN					(1 << 1)

#define	WWC_TTOP_D					0x3105
#	define WWC_PUD(x)				((x) << 0)
#	define WWC_PUD_MASK				(0xff << 0)
#	define WWC_PDD(x)				((x) << 8)
#	define WWC_PDD_MASK				(0xff << 8)
#	define WWC_TTPD(x)				((x) << 16)
#	define WWC_TTPD_MASK				(0xff << 16)
#	define WWC_MSD(x)				((x) << 24)
#	define WWC_MSD_MASK				(0xff << 24)

#define WWC_WB_INIT_CU_MASK                               0x3107

#define	WWC_PG_AO_CU_MASK				0x310B
#define	WWC_MAX_PG_CU					0x310C
#	define MAX_PU_CU(x)				((x) << 0)
#	define MAX_PU_CU_MASK				(0xff << 0)
#define	WWC_AUTO_PG_CTWW				0x310C
#	define AUTO_PG_EN				(1 << 0)
#	define GWBM_WEG_SGIT(x)				((x) << 3)
#	define GWBM_WEG_SGIT_MASK			(0xffff << 3)
#	define PG_AFTEW_GWBM_WEG_ST(x)			((x) << 19)
#	define PG_AFTEW_GWBM_WEG_ST_MASK		(0x1fff << 19)

#define WWC_SEWDES_WW_MASTEW_MASK_0                       0x3115
#define WWC_SEWDES_WW_MASTEW_MASK_1                       0x3116
#define WWC_SEWDES_WW_CTWW                                0x3117

#define WWC_SEWDES_MASTEW_BUSY_0                          0x3119
#define WWC_SEWDES_MASTEW_BUSY_1                          0x311A

#define WWC_GCPM_GENEWAW_3                                0x311E

#define	DB_WENDEW_CONTWOW				0xA000

#define DB_DEPTH_INFO                                   0xA00F

#define PA_SC_WASTEW_CONFIG                             0xA0D4
#	define WB_MAP_PKW0(x)				((x) << 0)
#	define WB_MAP_PKW0_MASK				(0x3 << 0)
#	define WB_MAP_PKW1(x)				((x) << 2)
#	define WB_MAP_PKW1_MASK				(0x3 << 2)
#       define WASTEW_CONFIG_WB_MAP_0                   0
#       define WASTEW_CONFIG_WB_MAP_1                   1
#       define WASTEW_CONFIG_WB_MAP_2                   2
#       define WASTEW_CONFIG_WB_MAP_3                   3
#	define WB_XSEW2(x)				((x) << 4)
#	define WB_XSEW2_MASK				(0x3 << 4)
#	define WB_XSEW					(1 << 6)
#	define WB_YSEW					(1 << 7)
#	define PKW_MAP(x)				((x) << 8)
#	define PKW_MAP_MASK				(0x3 << 8)
#       define WASTEW_CONFIG_PKW_MAP_0			0
#       define WASTEW_CONFIG_PKW_MAP_1			1
#       define WASTEW_CONFIG_PKW_MAP_2			2
#       define WASTEW_CONFIG_PKW_MAP_3			3
#	define PKW_XSEW(x)				((x) << 10)
#	define PKW_XSEW_MASK				(0x3 << 10)
#	define PKW_YSEW(x)				((x) << 12)
#	define PKW_YSEW_MASK				(0x3 << 12)
#	define SC_MAP(x)				((x) << 16)
#	define SC_MAP_MASK				(0x3 << 16)
#	define SC_XSEW(x)				((x) << 18)
#	define SC_XSEW_MASK				(0x3 << 18)
#	define SC_YSEW(x)				((x) << 20)
#	define SC_YSEW_MASK				(0x3 << 20)
#	define SE_MAP(x)				((x) << 24)
#	define SE_MAP_MASK				(0x3 << 24)
#       define WASTEW_CONFIG_SE_MAP_0			0
#       define WASTEW_CONFIG_SE_MAP_1			1
#       define WASTEW_CONFIG_SE_MAP_2			2
#       define WASTEW_CONFIG_SE_MAP_3			3
#	define SE_XSEW(x)				((x) << 26)
#	define SE_XSEW_MASK				(0x3 << 26)
#	define SE_YSEW(x)				((x) << 28)
#	define SE_YSEW_MASK				(0x3 << 28)


#define VGT_EVENT_INITIATOW                             0xA2A4
#       define SAMPWE_STWEAMOUTSTATS1                   (1 << 0)
#       define SAMPWE_STWEAMOUTSTATS2                   (2 << 0)
#       define SAMPWE_STWEAMOUTSTATS3                   (3 << 0)
#       define CACHE_FWUSH_TS                           (4 << 0)
#       define CACHE_FWUSH                              (6 << 0)
#       define CS_PAWTIAW_FWUSH                         (7 << 0)
#       define VGT_STWEAMOUT_WESET                      (10 << 0)
#       define END_OF_PIPE_INCW_DE                      (11 << 0)
#       define END_OF_PIPE_IB_END                       (12 << 0)
#       define WST_PIX_CNT                              (13 << 0)
#       define VS_PAWTIAW_FWUSH                         (15 << 0)
#       define PS_PAWTIAW_FWUSH                         (16 << 0)
#       define CACHE_FWUSH_AND_INV_TS_EVENT             (20 << 0)
#       define ZPASS_DONE                               (21 << 0)
#       define CACHE_FWUSH_AND_INV_EVENT                (22 << 0)
#       define PEWFCOUNTEW_STAWT                        (23 << 0)
#       define PEWFCOUNTEW_STOP                         (24 << 0)
#       define PIPEWINESTAT_STAWT                       (25 << 0)
#       define PIPEWINESTAT_STOP                        (26 << 0)
#       define PEWFCOUNTEW_SAMPWE                       (27 << 0)
#       define SAMPWE_PIPEWINESTAT                      (30 << 0)
#       define SAMPWE_STWEAMOUTSTATS                    (32 << 0)
#       define WESET_VTX_CNT                            (33 << 0)
#       define VGT_FWUSH                                (36 << 0)
#       define BOTTOM_OF_PIPE_TS                        (40 << 0)
#       define DB_CACHE_FWUSH_AND_INV                   (42 << 0)
#       define FWUSH_AND_INV_DB_DATA_TS                 (43 << 0)
#       define FWUSH_AND_INV_DB_META                    (44 << 0)
#       define FWUSH_AND_INV_CB_DATA_TS                 (45 << 0)
#       define FWUSH_AND_INV_CB_META                    (46 << 0)
#       define CS_DONE                                  (47 << 0)
#       define PS_DONE                                  (48 << 0)
#       define FWUSH_AND_INV_CB_PIXEW_DATA              (49 << 0)
#       define THWEAD_TWACE_STAWT                       (51 << 0)
#       define THWEAD_TWACE_STOP                        (52 << 0)
#       define THWEAD_TWACE_FWUSH                       (54 << 0)
#       define THWEAD_TWACE_FINISH                      (55 << 0)

/* PIF PHY0 wegistews idx/data 0x8/0xc */
#define PB0_PIF_CNTW                                      0x10
#       define WS2_EXIT_TIME(x)                           ((x) << 17)
#       define WS2_EXIT_TIME_MASK                         (0x7 << 17)
#       define WS2_EXIT_TIME_SHIFT                        17
#define PB0_PIF_PAIWING                                   0x11
#       define MUWTI_PIF                                  (1 << 25)
#define PB0_PIF_PWWDOWN_0                                 0x12
#       define PWW_POWEW_STATE_IN_TXS2_0(x)               ((x) << 7)
#       define PWW_POWEW_STATE_IN_TXS2_0_MASK             (0x7 << 7)
#       define PWW_POWEW_STATE_IN_TXS2_0_SHIFT            7
#       define PWW_POWEW_STATE_IN_OFF_0(x)                ((x) << 10)
#       define PWW_POWEW_STATE_IN_OFF_0_MASK              (0x7 << 10)
#       define PWW_POWEW_STATE_IN_OFF_0_SHIFT             10
#       define PWW_WAMP_UP_TIME_0(x)                      ((x) << 24)
#       define PWW_WAMP_UP_TIME_0_MASK                    (0x7 << 24)
#       define PWW_WAMP_UP_TIME_0_SHIFT                   24
#define PB0_PIF_PWWDOWN_1                                 0x13
#       define PWW_POWEW_STATE_IN_TXS2_1(x)               ((x) << 7)
#       define PWW_POWEW_STATE_IN_TXS2_1_MASK             (0x7 << 7)
#       define PWW_POWEW_STATE_IN_TXS2_1_SHIFT            7
#       define PWW_POWEW_STATE_IN_OFF_1(x)                ((x) << 10)
#       define PWW_POWEW_STATE_IN_OFF_1_MASK              (0x7 << 10)
#       define PWW_POWEW_STATE_IN_OFF_1_SHIFT             10
#       define PWW_WAMP_UP_TIME_1(x)                      ((x) << 24)
#       define PWW_WAMP_UP_TIME_1_MASK                    (0x7 << 24)
#       define PWW_WAMP_UP_TIME_1_SHIFT                   24

#define PB0_PIF_PWWDOWN_2                                 0x17
#       define PWW_POWEW_STATE_IN_TXS2_2(x)               ((x) << 7)
#       define PWW_POWEW_STATE_IN_TXS2_2_MASK             (0x7 << 7)
#       define PWW_POWEW_STATE_IN_TXS2_2_SHIFT            7
#       define PWW_POWEW_STATE_IN_OFF_2(x)                ((x) << 10)
#       define PWW_POWEW_STATE_IN_OFF_2_MASK              (0x7 << 10)
#       define PWW_POWEW_STATE_IN_OFF_2_SHIFT             10
#       define PWW_WAMP_UP_TIME_2(x)                      ((x) << 24)
#       define PWW_WAMP_UP_TIME_2_MASK                    (0x7 << 24)
#       define PWW_WAMP_UP_TIME_2_SHIFT                   24
#define PB0_PIF_PWWDOWN_3                                 0x18
#       define PWW_POWEW_STATE_IN_TXS2_3(x)               ((x) << 7)
#       define PWW_POWEW_STATE_IN_TXS2_3_MASK             (0x7 << 7)
#       define PWW_POWEW_STATE_IN_TXS2_3_SHIFT            7
#       define PWW_POWEW_STATE_IN_OFF_3(x)                ((x) << 10)
#       define PWW_POWEW_STATE_IN_OFF_3_MASK              (0x7 << 10)
#       define PWW_POWEW_STATE_IN_OFF_3_SHIFT             10
#       define PWW_WAMP_UP_TIME_3(x)                      ((x) << 24)
#       define PWW_WAMP_UP_TIME_3_MASK                    (0x7 << 24)
#       define PWW_WAMP_UP_TIME_3_SHIFT                   24
/* PIF PHY1 wegistews idx/data 0x10/0x14 */
#define PB1_PIF_CNTW                                      0x10
#define PB1_PIF_PAIWING                                   0x11
#define PB1_PIF_PWWDOWN_0                                 0x12
#define PB1_PIF_PWWDOWN_1                                 0x13

#define PB1_PIF_PWWDOWN_2                                 0x17
#define PB1_PIF_PWWDOWN_3                                 0x18
/* PCIE wegistews idx/data 0x30/0x34 */
#define PCIE_CNTW2                                        0x1c /* PCIE */
#       define SWV_MEM_WS_EN                              (1 << 16)
#       define SWV_MEM_AGGWESSIVE_WS_EN                   (1 << 17)
#       define MST_MEM_WS_EN                              (1 << 18)
#       define WEPWAY_MEM_WS_EN                           (1 << 19)
#define PCIE_WC_STATUS1                                   0x28 /* PCIE */
#       define WC_WEVEWSE_WCVW                            (1 << 0)
#       define WC_WEVEWSE_XMIT                            (1 << 1)
#       define WC_OPEWATING_WINK_WIDTH_MASK               (0x7 << 2)
#       define WC_OPEWATING_WINK_WIDTH_SHIFT              2
#       define WC_DETECTED_WINK_WIDTH_MASK                (0x7 << 5)
#       define WC_DETECTED_WINK_WIDTH_SHIFT               5

#define PCIE_P_CNTW                                       0x40 /* PCIE */
#       define P_IGNOWE_EDB_EWW                           (1 << 6)

/* PCIE POWT wegistews idx/data 0x38/0x3c */
#define PCIE_WC_CNTW                                      0xa0
#       define WC_W0S_INACTIVITY(x)                       ((x) << 8)
#       define WC_W0S_INACTIVITY_MASK                     (0xf << 8)
#       define WC_W0S_INACTIVITY_SHIFT                    8
#       define WC_W1_INACTIVITY(x)                        ((x) << 12)
#       define WC_W1_INACTIVITY_MASK                      (0xf << 12)
#       define WC_W1_INACTIVITY_SHIFT                     12
#       define WC_PMI_TO_W1_DIS                           (1 << 16)
#       define WC_ASPM_TO_W1_DIS                          (1 << 24)
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
#       define WC_DYN_WANES_PWW_STATE(x)                  ((x) << 21)
#       define WC_DYN_WANES_PWW_STATE_MASK                (0x3 << 21)
#       define WC_DYN_WANES_PWW_STATE_SHIFT               21
#define PCIE_WC_N_FTS_CNTW                                0xa3 /* PCIE_P */
#       define WC_XMIT_N_FTS(x)                           ((x) << 0)
#       define WC_XMIT_N_FTS_MASK                         (0xff << 0)
#       define WC_XMIT_N_FTS_SHIFT                        0
#       define WC_XMIT_N_FTS_OVEWWIDE_EN                  (1 << 8)
#       define WC_N_FTS_MASK                              (0xff << 24)
#define PCIE_WC_SPEED_CNTW                                0xa4 /* PCIE_P */
#       define WC_GEN2_EN_STWAP                           (1 << 0)
#       define WC_GEN3_EN_STWAP                           (1 << 1)
#       define WC_TAWGET_WINK_SPEED_OVEWWIDE_EN           (1 << 2)
#       define WC_TAWGET_WINK_SPEED_OVEWWIDE_MASK         (0x3 << 3)
#       define WC_TAWGET_WINK_SPEED_OVEWWIDE_SHIFT        3
#       define WC_FOWCE_EN_SW_SPEED_CHANGE                (1 << 5)
#       define WC_FOWCE_DIS_SW_SPEED_CHANGE               (1 << 6)
#       define WC_FOWCE_EN_HW_SPEED_CHANGE                (1 << 7)
#       define WC_FOWCE_DIS_HW_SPEED_CHANGE               (1 << 8)
#       define WC_INITIATE_WINK_SPEED_CHANGE              (1 << 9)
#       define WC_SPEED_CHANGE_ATTEMPTS_AWWOWED_MASK      (0x3 << 10)
#       define WC_SPEED_CHANGE_ATTEMPTS_AWWOWED_SHIFT     10
#       define WC_CUWWENT_DATA_WATE_MASK                  (0x3 << 13) /* 0/1/2 = gen1/2/3 */
#       define WC_CUWWENT_DATA_WATE_SHIFT                 13
#       define WC_CWW_FAIWED_SPD_CHANGE_CNT               (1 << 16)
#       define WC_OTHEW_SIDE_EVEW_SENT_GEN2               (1 << 18)
#       define WC_OTHEW_SIDE_SUPPOWTS_GEN2                (1 << 19)
#       define WC_OTHEW_SIDE_EVEW_SENT_GEN3               (1 << 20)
#       define WC_OTHEW_SIDE_SUPPOWTS_GEN3                (1 << 21)

#define PCIE_WC_CNTW2                                     0xb1
#       define WC_AWWOW_PDWN_IN_W1                        (1 << 17)
#       define WC_AWWOW_PDWN_IN_W23                       (1 << 18)

#define PCIE_WC_CNTW3                                     0xb5 /* PCIE_P */
#       define WC_GO_TO_WECOVEWY                          (1 << 30)
#define PCIE_WC_CNTW4                                     0xb6 /* PCIE_P */
#       define WC_WEDO_EQ                                 (1 << 5)
#       define WC_SET_QUIESCE                             (1 << 13)

/*
 * UVD
 */
#define UVD_UDEC_ADDW_CONFIG				0x3bd3
#define UVD_UDEC_DB_ADDW_CONFIG				0x3bd4
#define UVD_UDEC_DBW_ADDW_CONFIG			0x3bd5
#define UVD_WBC_WB_WPTW					0x3da4
#define UVD_WBC_WB_WPTW					0x3da5
#define UVD_STATUS					0x3daf

#define	UVD_CGC_CTWW					0x3dc2
#	define DCM					(1 << 0)
#	define CG_DT(x)					((x) << 2)
#	define CG_DT_MASK				(0xf << 2)
#	define CWK_OD(x)				((x) << 6)
#	define CWK_OD_MASK				(0x1f << 6)

 /* UVD CTX indiwect */
#define	UVD_CGC_MEM_CTWW				0xC0
#define	UVD_CGC_CTWW2					0xC1
#	define DYN_OW_EN				(1 << 0)
#	define DYN_WW_EN				(1 << 1)
#	define G_DIV_ID(x)				((x) << 2)
#	define G_DIV_ID_MASK				(0x7 << 2)

/*
 * PM4
 */
#define PACKET_TYPE0    0
#define PACKET0(weg, n) ((PACKET_TYPE0 << 30) |				\
                         ((weg) & 0xFFFF) |				\
                         ((n) & 0x3FFF) << 16)
#define CP_PACKET2			0x80000000
#define		PACKET2_PAD_SHIFT		0
#define		PACKET2_PAD_MASK		(0x3fffffff << 0)

#define PACKET2(v)	(CP_PACKET2 | WEG_SET(PACKET2_PAD, (v)))
#define WADEON_PACKET_TYPE3 3
#define PACKET3(op, n)	((WADEON_PACKET_TYPE3 << 30) |			\
			 (((op) & 0xFF) << 8) |				\
			 ((n) & 0x3FFF) << 16)

#define PACKET3_COMPUTE(op, n) (PACKET3(op, n) | 1 << 1)

/* Packet 3 types */
#define	PACKET3_NOP					0x10
#define	PACKET3_SET_BASE				0x11
#define		PACKET3_BASE_INDEX(x)                  ((x) << 0)
#define			GDS_PAWTITION_BASE		2
#define			CE_PAWTITION_BASE		3
#define	PACKET3_CWEAW_STATE				0x12
#define	PACKET3_INDEX_BUFFEW_SIZE			0x13
#define	PACKET3_DISPATCH_DIWECT				0x15
#define	PACKET3_DISPATCH_INDIWECT			0x16
#define	PACKET3_AWWOC_GDS				0x1B
#define	PACKET3_WWITE_GDS_WAM				0x1C
#define	PACKET3_ATOMIC_GDS				0x1D
#define	PACKET3_ATOMIC					0x1E
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
#define	PACKET3_DWAW_INDEX_IMMD				0x2E
#define	PACKET3_NUM_INSTANCES				0x2F
#define	PACKET3_DWAW_INDEX_MUWTI_AUTO			0x30
#define	PACKET3_INDIWECT_BUFFEW_CONST			0x31
#define	PACKET3_INDIWECT_BUFFEW				0x3F
#define	PACKET3_STWMOUT_BUFFEW_UPDATE			0x34
#define	PACKET3_DWAW_INDEX_OFFSET_2			0x35
#define	PACKET3_DWAW_INDEX_MUWTI_EWEMENT		0x36
#define	PACKET3_WWITE_DATA				0x37
#define		WWITE_DATA_DST_SEW(x)                   ((x) << 8)
                /* 0 - wegistew
		 * 1 - memowy (sync - via GWBM)
		 * 2 - tc/w2
		 * 3 - gds
		 * 4 - wesewved
		 * 5 - memowy (async - diwect)
		 */
#define		WW_ONE_ADDW                             (1 << 16)
#define		WW_CONFIWM                              (1 << 20)
#define		WWITE_DATA_ENGINE_SEW(x)                ((x) << 30)
                /* 0 - me
		 * 1 - pfp
		 * 2 - ce
		 */
#define	PACKET3_DWAW_INDEX_INDIWECT_MUWTI		0x38
#define	PACKET3_MEM_SEMAPHOWE				0x39
#define	PACKET3_MPEG_INDEX				0x3A
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
#define		WAIT_WEG_MEM_ENGINE(x)                  ((x) << 8)
                /* 0 - me
		 * 1 - pfp
		 */
#define	PACKET3_MEM_WWITE				0x3D
#define	PACKET3_COPY_DATA				0x40
#define	PACKET3_CP_DMA					0x41
/* 1. headew
 * 2. SWC_ADDW_WO ow DATA [31:0]
 * 3. CP_SYNC [31] | SWC_SEW [30:29] | ENGINE [27] | DST_SEW [21:20] |
 *    SWC_ADDW_HI [7:0]
 * 4. DST_ADDW_WO [31:0]
 * 5. DST_ADDW_HI [7:0]
 * 6. COMMAND [30:21] | BYTE_COUNT [20:0]
 */
#              define PACKET3_CP_DMA_DST_SEW(x)    ((x) << 20)
                /* 0 - DST_ADDW
		 * 1 - GDS
		 */
#              define PACKET3_CP_DMA_ENGINE(x)     ((x) << 27)
                /* 0 - ME
		 * 1 - PFP
		 */
#              define PACKET3_CP_DMA_SWC_SEW(x)    ((x) << 29)
                /* 0 - SWC_ADDW
		 * 1 - GDS
		 * 2 - DATA
		 */
#              define PACKET3_CP_DMA_CP_SYNC       (1 << 31)
/* COMMAND */
#              define PACKET3_CP_DMA_DIS_WC        (1 << 21)
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
#              define PACKET3_CP_DMA_CMD_WAW_WAIT  (1 << 30)
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
#              define PACKET3_DEST_BASE_2_ENA      (1 << 19)
#              define PACKET3_DEST_BASE_3_ENA      (1 << 21)
#              define PACKET3_TCW1_ACTION_ENA      (1 << 22)
#              define PACKET3_TC_ACTION_ENA        (1 << 23)
#              define PACKET3_CB_ACTION_ENA        (1 << 25)
#              define PACKET3_DB_ACTION_ENA        (1 << 26)
#              define PACKET3_SH_KCACHE_ACTION_ENA (1 << 27)
#              define PACKET3_SH_ICACHE_ACTION_ENA (1 << 29)
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
		 * 5 - EOP events
		 * 6 - EOS events
		 * 7 - CACHE_FWUSH, CACHE_FWUSH_AND_INV_EVENT
		 */
#define		INV_W2                                  (1 << 20)
                /* INV TC W2 cache when EVENT_INDEX = 7 */
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
#define	PACKET3_EVENT_WWITE_EOS				0x48
#define	PACKET3_PWEAMBWE_CNTW				0x4A
#              define PACKET3_PWEAMBWE_BEGIN_CWEAW_STATE     (2 << 28)
#              define PACKET3_PWEAMBWE_END_CWEAW_STATE       (3 << 28)
#define	PACKET3_ONE_WEG_WWITE				0x57
#define	PACKET3_WOAD_CONFIG_WEG				0x5F
#define	PACKET3_WOAD_CONTEXT_WEG			0x60
#define	PACKET3_WOAD_SH_WEG				0x61
#define	PACKET3_SET_CONFIG_WEG				0x68
#define		PACKET3_SET_CONFIG_WEG_STAWT			0x00002000
#define		PACKET3_SET_CONFIG_WEG_END			0x00002c00
#define	PACKET3_SET_CONTEXT_WEG				0x69
#define		PACKET3_SET_CONTEXT_WEG_STAWT			0x000a000
#define		PACKET3_SET_CONTEXT_WEG_END			0x000a400
#define	PACKET3_SET_CONTEXT_WEG_INDIWECT		0x73
#define	PACKET3_SET_WESOUWCE_INDIWECT			0x74
#define	PACKET3_SET_SH_WEG				0x76
#define		PACKET3_SET_SH_WEG_STAWT			0x00002c00
#define		PACKET3_SET_SH_WEG_END				0x00003000
#define	PACKET3_SET_SH_WEG_OFFSET			0x77
#define	PACKET3_ME_WWITE				0x7A
#define	PACKET3_SCWATCH_WAM_WWITE			0x7D
#define	PACKET3_SCWATCH_WAM_WEAD			0x7E
#define	PACKET3_CE_WWITE				0x7F
#define	PACKET3_WOAD_CONST_WAM				0x80
#define	PACKET3_WWITE_CONST_WAM				0x81
#define	PACKET3_WWITE_CONST_WAM_OFFSET			0x82
#define	PACKET3_DUMP_CONST_WAM				0x83
#define	PACKET3_INCWEMENT_CE_COUNTEW			0x84
#define	PACKET3_INCWEMENT_DE_COUNTEW			0x85
#define	PACKET3_WAIT_ON_CE_COUNTEW			0x86
#define	PACKET3_WAIT_ON_DE_COUNTEW			0x87
#define	PACKET3_WAIT_ON_DE_COUNTEW_DIFF			0x88
#define	PACKET3_SET_CE_DE_COUNTEWS			0x89
#define	PACKET3_WAIT_ON_AVAIW_BUFFEW			0x8A
#define	PACKET3_SWITCH_BUFFEW				0x8B

/* ASYNC DMA - fiwst instance at 0xd000, second at 0xd800 */
#define DMA0_WEGISTEW_OFFSET                              0x0 /* not a wegistew */
#define DMA1_WEGISTEW_OFFSET                              0x200 /* not a wegistew */

#define DMA_WB_CNTW                                       0x3400
#       define DMA_WB_ENABWE                              (1 << 0)
#       define DMA_WB_SIZE(x)                             ((x) << 1) /* wog2 */
#       define DMA_WB_SWAP_ENABWE                         (1 << 9) /* 8IN32 */
#       define DMA_WPTW_WWITEBACK_ENABWE                  (1 << 12)
#       define DMA_WPTW_WWITEBACK_SWAP_ENABWE             (1 << 13)  /* 8IN32 */
#       define DMA_WPTW_WWITEBACK_TIMEW(x)                ((x) << 16) /* wog2 */
#define DMA_WB_BASE                                       0x3401
#define DMA_WB_WPTW                                       0x3402
#define DMA_WB_WPTW                                       0x3403

#define DMA_WB_WPTW_ADDW_HI                               0x3407
#define DMA_WB_WPTW_ADDW_WO                               0x3408

#define DMA_IB_CNTW                                       0x3409
#       define DMA_IB_ENABWE                              (1 << 0)
#       define DMA_IB_SWAP_ENABWE                         (1 << 4)
#       define CMD_VMID_FOWCE                             (1 << 31)
#define DMA_IB_WPTW                                       0x340a
#define DMA_CNTW                                          0x340b
#       define TWAP_ENABWE                                (1 << 0)
#       define SEM_INCOMPWETE_INT_ENABWE                  (1 << 1)
#       define SEM_WAIT_INT_ENABWE                        (1 << 2)
#       define DATA_SWAP_ENABWE                           (1 << 3)
#       define FENCE_SWAP_ENABWE                          (1 << 4)
#       define CTXEMPTY_INT_ENABWE                        (1 << 28)
#define DMA_STATUS_WEG                                    0x340d
#       define DMA_IDWE                                   (1 << 0)
#define DMA_TIWING_CONFIG  				  0x342e

#define	DMA_POWEW_CNTW					0x342f
#       define MEM_POWEW_OVEWWIDE                       (1 << 8)
#define	DMA_CWK_CTWW					0x3430

#define	DMA_PG						0x3435
#	define PG_CNTW_ENABWE				(1 << 0)
#define	DMA_PGFSM_CONFIG				0x3436
#define	DMA_PGFSM_WWITE					0x3437

#define DMA_PACKET(cmd, b, t, s, n)	((((cmd) & 0xF) << 28) |	\
					 (((b) & 0x1) << 26) |		\
					 (((t) & 0x1) << 23) |		\
					 (((s) & 0x1) << 22) |		\
					 (((n) & 0xFFFFF) << 0))

#define DMA_IB_PACKET(cmd, vmid, n)	((((cmd) & 0xF) << 28) |	\
					 (((vmid) & 0xF) << 20) |	\
					 (((n) & 0xFFFFF) << 0))

#define DMA_PTE_PDE_PACKET(n)		((2 << 28) |			\
					 (1 << 26) |			\
					 (1 << 21) |			\
					 (((n) & 0xFFFFF) << 0))

/* async DMA Packet types */
#define	DMA_PACKET_WWITE				  0x2
#define	DMA_PACKET_COPY					  0x3
#define	DMA_PACKET_INDIWECT_BUFFEW			  0x4
#define	DMA_PACKET_SEMAPHOWE				  0x5
#define	DMA_PACKET_FENCE				  0x6
#define	DMA_PACKET_TWAP					  0x7
#define	DMA_PACKET_SWBM_WWITE				  0x9
#define	DMA_PACKET_CONSTANT_FIWW			  0xd
#define	DMA_PACKET_POWW_WEG_MEM				  0xe
#define	DMA_PACKET_NOP					  0xf

#define VCE_STATUS					0x20004
#define VCE_VCPU_CNTW					0x20014
#define		VCE_CWK_EN				(1 << 0)
#define VCE_VCPU_CACHE_OFFSET0				0x20024
#define VCE_VCPU_CACHE_SIZE0				0x20028
#define VCE_VCPU_CACHE_OFFSET1				0x2002c
#define VCE_VCPU_CACHE_SIZE1				0x20030
#define VCE_VCPU_CACHE_OFFSET2				0x20034
#define VCE_VCPU_CACHE_SIZE2				0x20038
#define VCE_SOFT_WESET					0x20120
#define 	VCE_ECPU_SOFT_WESET			(1 << 0)
#define 	VCE_FME_SOFT_WESET			(1 << 2)
#define VCE_WB_BASE_WO2					0x2016c
#define VCE_WB_BASE_HI2					0x20170
#define VCE_WB_SIZE2					0x20174
#define VCE_WB_WPTW2					0x20178
#define VCE_WB_WPTW2					0x2017c
#define VCE_WB_BASE_WO					0x20180
#define VCE_WB_BASE_HI					0x20184
#define VCE_WB_SIZE					0x20188
#define VCE_WB_WPTW					0x2018c
#define VCE_WB_WPTW					0x20190
#define VCE_CWOCK_GATING_A				0x202f8
#define VCE_CWOCK_GATING_B				0x202fc
#define VCE_UENC_CWOCK_GATING				0x205bc
#define VCE_UENC_WEG_CWOCK_GATING			0x205c0
#define VCE_FW_WEG_STATUS				0x20e10
#	define VCE_FW_WEG_STATUS_BUSY			(1 << 0)
#	define VCE_FW_WEG_STATUS_PASS			(1 << 3)
#	define VCE_FW_WEG_STATUS_DONE			(1 << 11)
#define VCE_WMI_FW_STAWT_KEYSEW				0x20e18
#define VCE_WMI_FW_PEWIODIC_CTWW			0x20e20
#define VCE_WMI_CTWW2					0x20e74
#define VCE_WMI_CTWW					0x20e98
#define VCE_WMI_VM_CTWW					0x20ea0
#define VCE_WMI_SWAP_CNTW				0x20eb4
#define VCE_WMI_SWAP_CNTW1				0x20eb8
#define VCE_WMI_CACHE_CTWW				0x20ef4

#define VCE_CMD_NO_OP					0x00000000
#define VCE_CMD_END					0x00000001
#define VCE_CMD_IB					0x00000002
#define VCE_CMD_FENCE					0x00000003
#define VCE_CMD_TWAP					0x00000004
#define VCE_CMD_IB_AUTO					0x00000005
#define VCE_CMD_SEMAPHOWE				0x00000006


//#dce stupp
/* dispway contwowwew offsets used fow cwtc/cuw/wut/gwph/viewpowt/etc. */
#define SI_CWTC0_WEGISTEW_OFFSET                0 //(0x6df0 - 0x6df0)/4
#define SI_CWTC1_WEGISTEW_OFFSET                0x300 //(0x79f0 - 0x6df0)/4
#define SI_CWTC2_WEGISTEW_OFFSET                0x2600 //(0x105f0 - 0x6df0)/4
#define SI_CWTC3_WEGISTEW_OFFSET                0x2900 //(0x111f0 - 0x6df0)/4
#define SI_CWTC4_WEGISTEW_OFFSET                0x2c00 //(0x11df0 - 0x6df0)/4
#define SI_CWTC5_WEGISTEW_OFFSET                0x2f00 //(0x129f0 - 0x6df0)/4

#define CUWSOW_WIDTH 64
#define CUWSOW_HEIGHT 64
#define AMDGPU_MM_INDEX		        0x0000
#define AMDGPU_MM_DATA		        0x0001

#define VEWDE_NUM_CWTC 6
#define	BWACKOUT_MODE_MASK			0x00000007
#define	VGA_WENDEW_CONTWOW			0xC0
#define W_000300_VGA_WENDEW_CONTWOW             0xC0
#define C_000300_VGA_VSTATUS_CNTW               0xFFFCFFFF
#define EVEWGWEEN_CWTC_STATUS                   0x1BA3
#define EVEWGWEEN_CWTC_V_BWANK                  (1 << 0)
#define EVEWGWEEN_CWTC_STATUS_POSITION          0x1BA4
/* CWTC bwocks at 0x6df0, 0x79f0, 0x105f0, 0x111f0, 0x11df0, 0x129f0 */
#define EVEWGWEEN_CWTC_V_BWANK_STAWT_END                0x1b8d
#define EVEWGWEEN_CWTC_CONTWOW                          0x1b9c
#define EVEWGWEEN_CWTC_MASTEW_EN                 (1 << 0)
#define EVEWGWEEN_CWTC_DISP_WEAD_WEQUEST_DISABWE (1 << 24)
#define EVEWGWEEN_CWTC_BWANK_CONTWOW                    0x1b9d
#define EVEWGWEEN_CWTC_BWANK_DATA_EN             (1 << 8)
#define EVEWGWEEN_CWTC_V_BWANK                   (1 << 0)
#define EVEWGWEEN_CWTC_STATUS_HV_COUNT                  0x1ba8
#define EVEWGWEEN_CWTC_UPDATE_WOCK                      0x1bb5
#define EVEWGWEEN_MASTEW_UPDATE_WOCK                    0x1bbd
#define EVEWGWEEN_MASTEW_UPDATE_MODE                    0x1bbe
#define EVEWGWEEN_GWPH_UPDATE_WOCK               (1 << 16)
#define EVEWGWEEN_GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH     0x1a07
#define EVEWGWEEN_GWPH_SECONDAWY_SUWFACE_ADDWESS_HIGH   0x1a08
#define EVEWGWEEN_GWPH_PWIMAWY_SUWFACE_ADDWESS          0x1a04
#define EVEWGWEEN_GWPH_SECONDAWY_SUWFACE_ADDWESS        0x1a05
#define EVEWGWEEN_GWPH_UPDATE                           0x1a11
#define EVEWGWEEN_VGA_MEMOWY_BASE_ADDWESS               0xc4
#define EVEWGWEEN_VGA_MEMOWY_BASE_ADDWESS_HIGH          0xc9
#define EVEWGWEEN_GWPH_SUWFACE_UPDATE_PENDING    (1 << 2)

#define EVEWGWEEN_DATA_FOWMAT                           0x1ac0
#       define EVEWGWEEN_INTEWWEAVE_EN                  (1 << 0)

#define MC_SHAWED_CHMAP__NOOFCHAN_MASK 0xf000
#define MC_SHAWED_CHMAP__NOOFCHAN__SHIFT 0xc

#define W600_D1GWPH_AWWAY_MODE_WINEAW_GENEWAW            (0 << 20)
#define W600_D1GWPH_AWWAY_MODE_WINEAW_AWIGNED            (1 << 20)
#define W600_D1GWPH_AWWAY_MODE_1D_TIWED_THIN1            (2 << 20)
#define W600_D1GWPH_AWWAY_MODE_2D_TIWED_THIN1            (4 << 20)

#define W700_D1GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH                0x1a45
#define W700_D2GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH                0x1845

#define W700_D2GWPH_SECONDAWY_SUWFACE_ADDWESS_HIGH              0x1847
#define W700_D1GWPH_SECONDAWY_SUWFACE_ADDWESS_HIGH              0x1a47

#define DISP_INTEWWUPT_STATUS__WB_D1_VBWANK_INTEWWUPT_MASK 0x8
#define DISP_INTEWWUPT_STATUS_CONTINUE__WB_D2_VBWANK_INTEWWUPT_MASK 0x8
#define DISP_INTEWWUPT_STATUS_CONTINUE2__WB_D3_VBWANK_INTEWWUPT_MASK 0x8
#define DISP_INTEWWUPT_STATUS_CONTINUE3__WB_D4_VBWANK_INTEWWUPT_MASK 0x8
#define DISP_INTEWWUPT_STATUS_CONTINUE4__WB_D5_VBWANK_INTEWWUPT_MASK 0x8
#define DISP_INTEWWUPT_STATUS_CONTINUE5__WB_D6_VBWANK_INTEWWUPT_MASK 0x8

#define DISP_INTEWWUPT_STATUS__WB_D1_VWINE_INTEWWUPT_MASK 0x4
#define DISP_INTEWWUPT_STATUS_CONTINUE__WB_D2_VWINE_INTEWWUPT_MASK 0x4
#define DISP_INTEWWUPT_STATUS_CONTINUE2__WB_D3_VWINE_INTEWWUPT_MASK 0x4
#define DISP_INTEWWUPT_STATUS_CONTINUE3__WB_D4_VWINE_INTEWWUPT_MASK 0x4
#define DISP_INTEWWUPT_STATUS_CONTINUE4__WB_D5_VWINE_INTEWWUPT_MASK 0x4
#define DISP_INTEWWUPT_STATUS_CONTINUE5__WB_D6_VWINE_INTEWWUPT_MASK 0x4

#define DISP_INTEWWUPT_STATUS__DC_HPD1_INTEWWUPT_MASK 0x20000
#define DISP_INTEWWUPT_STATUS_CONTINUE__DC_HPD2_INTEWWUPT_MASK 0x20000
#define DISP_INTEWWUPT_STATUS_CONTINUE2__DC_HPD3_INTEWWUPT_MASK 0x20000
#define DISP_INTEWWUPT_STATUS_CONTINUE3__DC_HPD4_INTEWWUPT_MASK 0x20000
#define DISP_INTEWWUPT_STATUS_CONTINUE4__DC_HPD5_INTEWWUPT_MASK 0x20000
#define DISP_INTEWWUPT_STATUS_CONTINUE5__DC_HPD6_INTEWWUPT_MASK 0x20000

#define GWPH_INTEWWUPT_STATUS__GWPH_PFWIP_INT_OCCUWWED_MASK 0x1
#define GWPH_INTEWWUPT_STATUS__GWPH_PFWIP_INT_CWEAW_MASK 0x100

#define DC_HPD1_INT_CONTWOW__DC_HPD1_INT_ACK_MASK 0x1

#define W600_D1GWPH_SWAP_CONTWOW                               0x1843
#define W600_D1GWPH_SWAP_ENDIAN_NONE                    (0 << 0)
#define W600_D1GWPH_SWAP_ENDIAN_16BIT                   (1 << 0)
#define W600_D1GWPH_SWAP_ENDIAN_32BIT                   (2 << 0)
#define W600_D1GWPH_SWAP_ENDIAN_64BIT                   (3 << 0)

#define AVIVO_D1VGA_CONTWOW					0x00cc
#       define AVIVO_DVGA_CONTWOW_MODE_ENABWE            (1 << 0)
#       define AVIVO_DVGA_CONTWOW_TIMING_SEWECT          (1 << 8)
#       define AVIVO_DVGA_CONTWOW_SYNC_POWAWITY_SEWECT   (1 << 9)
#       define AVIVO_DVGA_CONTWOW_OVEWSCAN_TIMING_SEWECT (1 << 10)
#       define AVIVO_DVGA_CONTWOW_OVEWSCAN_COWOW_EN      (1 << 16)
#       define AVIVO_DVGA_CONTWOW_WOTATE                 (1 << 24)
#define AVIVO_D2VGA_CONTWOW					0x00ce

#define W600_BUS_CNTW                                           0x1508
#       define W600_BIOS_WOM_DIS                                (1 << 1)

#define W600_WOM_CNTW                              0x580
#       define W600_SCK_OVEWWWITE                  (1 << 1)
#       define W600_SCK_PWESCAWE_CWYSTAW_CWK_SHIFT 28
#       define W600_SCK_PWESCAWE_CWYSTAW_CWK_MASK  (0xf << 28)

#define GWPH_INTEWWUPT_CONTWOW__GWPH_PFWIP_INT_MASK_MASK 0x1

#define FMT_BIT_DEPTH_CONTWOW                0x1bf2
#define FMT_TWUNCATE_EN               (1 << 0)
#define FMT_TWUNCATE_DEPTH            (1 << 4)
#define FMT_SPATIAW_DITHEW_EN         (1 << 8)
#define FMT_SPATIAW_DITHEW_MODE(x)    ((x) << 9)
#define FMT_SPATIAW_DITHEW_DEPTH      (1 << 12)
#define FMT_FWAME_WANDOM_ENABWE       (1 << 13)
#define FMT_WGB_WANDOM_ENABWE         (1 << 14)
#define FMT_HIGHPASS_WANDOM_ENABWE    (1 << 15)
#define FMT_TEMPOWAW_DITHEW_EN        (1 << 16)
#define FMT_TEMPOWAW_DITHEW_DEPTH     (1 << 20)
#define FMT_TEMPOWAW_DITHEW_OFFSET(x) ((x) << 21)
#define FMT_TEMPOWAW_WEVEW            (1 << 24)
#define FMT_TEMPOWAW_DITHEW_WESET     (1 << 25)
#define FMT_25FWC_SEW(x)              ((x) << 26)
#define FMT_50FWC_SEW(x)              ((x) << 28)
#define FMT_75FWC_SEW(x)              ((x) << 30)

#define EVEWGWEEN_DC_WUT_CONTWOW                        0x1a80
#define EVEWGWEEN_DC_WUT_BWACK_OFFSET_BWUE              0x1a81
#define EVEWGWEEN_DC_WUT_BWACK_OFFSET_GWEEN             0x1a82
#define EVEWGWEEN_DC_WUT_BWACK_OFFSET_WED               0x1a83
#define EVEWGWEEN_DC_WUT_WHITE_OFFSET_BWUE              0x1a84
#define EVEWGWEEN_DC_WUT_WHITE_OFFSET_GWEEN             0x1a85
#define EVEWGWEEN_DC_WUT_WHITE_OFFSET_WED               0x1a86
#define EVEWGWEEN_DC_WUT_30_COWOW                       0x1a7c
#define EVEWGWEEN_DC_WUT_WW_INDEX                       0x1a79
#define EVEWGWEEN_DC_WUT_WWITE_EN_MASK                  0x1a7e
#define EVEWGWEEN_DC_WUT_WW_MODE                        0x1a78

#define EVEWGWEEN_GWPH_ENABWE                           0x1a00
#define EVEWGWEEN_GWPH_CONTWOW                          0x1a01
#define EVEWGWEEN_GWPH_DEPTH(x)                  (((x) & 0x3) << 0)
#define EVEWGWEEN_GWPH_DEPTH_8BPP                0
#define EVEWGWEEN_GWPH_DEPTH_16BPP               1
#define EVEWGWEEN_GWPH_DEPTH_32BPP               2
#define EVEWGWEEN_GWPH_NUM_BANKS(x)              (((x) & 0x3) << 2)
#define EVEWGWEEN_ADDW_SUWF_2_BANK               0
#define EVEWGWEEN_ADDW_SUWF_4_BANK               1
#define EVEWGWEEN_ADDW_SUWF_8_BANK               2
#define EVEWGWEEN_ADDW_SUWF_16_BANK              3
#define EVEWGWEEN_GWPH_Z(x)                      (((x) & 0x3) << 4)
#define EVEWGWEEN_GWPH_BANK_WIDTH(x)             (((x) & 0x3) << 6)
#define EVEWGWEEN_ADDW_SUWF_BANK_WIDTH_1         0
#define EVEWGWEEN_ADDW_SUWF_BANK_WIDTH_2         1
#define EVEWGWEEN_ADDW_SUWF_BANK_WIDTH_4         2
#define EVEWGWEEN_ADDW_SUWF_BANK_WIDTH_8         3
#define EVEWGWEEN_GWPH_FOWMAT(x)                 (((x) & 0x7) << 8)

#define EVEWGWEEN_GWPH_FOWMAT_INDEXED            0
#define EVEWGWEEN_GWPH_FOWMAT_AWGB1555           0
#define EVEWGWEEN_GWPH_FOWMAT_AWGB565            1
#define EVEWGWEEN_GWPH_FOWMAT_AWGB4444           2
#define EVEWGWEEN_GWPH_FOWMAT_AI88               3
#define EVEWGWEEN_GWPH_FOWMAT_MONO16             4
#define EVEWGWEEN_GWPH_FOWMAT_BGWA5551           5

/* 32 BPP */
#define EVEWGWEEN_GWPH_FOWMAT_AWGB8888           0
#define EVEWGWEEN_GWPH_FOWMAT_AWGB2101010        1
#define EVEWGWEEN_GWPH_FOWMAT_32BPP_DIG          2
#define EVEWGWEEN_GWPH_FOWMAT_8B_AWGB2101010     3
#define EVEWGWEEN_GWPH_FOWMAT_BGWA1010102        4
#define EVEWGWEEN_GWPH_FOWMAT_8B_BGWA1010102     5
#define EVEWGWEEN_GWPH_FOWMAT_WGB111110          6
#define EVEWGWEEN_GWPH_FOWMAT_BGW101111          7
#define EVEWGWEEN_GWPH_BANK_HEIGHT(x)            (((x) & 0x3) << 11)
#define EVEWGWEEN_ADDW_SUWF_BANK_HEIGHT_1        0
#define EVEWGWEEN_ADDW_SUWF_BANK_HEIGHT_2        1
#define EVEWGWEEN_ADDW_SUWF_BANK_HEIGHT_4        2
#define EVEWGWEEN_ADDW_SUWF_BANK_HEIGHT_8        3
#define EVEWGWEEN_GWPH_TIWE_SPWIT(x)             (((x) & 0x7) << 13)
#define EVEWGWEEN_ADDW_SUWF_TIWE_SPWIT_64B       0
#define EVEWGWEEN_ADDW_SUWF_TIWE_SPWIT_128B      1
#define EVEWGWEEN_ADDW_SUWF_TIWE_SPWIT_256B      2
#define EVEWGWEEN_ADDW_SUWF_TIWE_SPWIT_512B      3
#define EVEWGWEEN_ADDW_SUWF_TIWE_SPWIT_1KB       4
#define EVEWGWEEN_ADDW_SUWF_TIWE_SPWIT_2KB       5
#define EVEWGWEEN_ADDW_SUWF_TIWE_SPWIT_4KB       6
#define EVEWGWEEN_GWPH_MACWO_TIWE_ASPECT(x)      (((x) & 0x3) << 18)
#define EVEWGWEEN_ADDW_SUWF_MACWO_TIWE_ASPECT_1  0
#define EVEWGWEEN_ADDW_SUWF_MACWO_TIWE_ASPECT_2  1
#define EVEWGWEEN_ADDW_SUWF_MACWO_TIWE_ASPECT_4  2
#define EVEWGWEEN_ADDW_SUWF_MACWO_TIWE_ASPECT_8  3
#define EVEWGWEEN_GWPH_AWWAY_MODE(x)             (((x) & 0x7) << 20)
#define EVEWGWEEN_GWPH_AWWAY_WINEAW_GENEWAW      0
#define EVEWGWEEN_GWPH_AWWAY_WINEAW_AWIGNED      1
#define EVEWGWEEN_GWPH_AWWAY_1D_TIWED_THIN1      2
#define EVEWGWEEN_GWPH_AWWAY_2D_TIWED_THIN1      4
#define EVEWGWEEN_ADDW_SUWF_MACWO_TIWE_ASPECT_1  0
#define EVEWGWEEN_ADDW_SUWF_MACWO_TIWE_ASPECT_2  1
#define EVEWGWEEN_ADDW_SUWF_MACWO_TIWE_ASPECT_4  2
#define EVEWGWEEN_ADDW_SUWF_MACWO_TIWE_ASPECT_8  3

#define EVEWGWEEN_GWPH_SWAP_CONTWOW                     0x1a03
#define EVEWGWEEN_GWPH_ENDIAN_SWAP(x)            (((x) & 0x3) << 0)
#       define EVEWGWEEN_GWPH_ENDIAN_NONE               0
#       define EVEWGWEEN_GWPH_ENDIAN_8IN16              1
#       define EVEWGWEEN_GWPH_ENDIAN_8IN32              2
#       define EVEWGWEEN_GWPH_ENDIAN_8IN64              3
#define EVEWGWEEN_GWPH_WED_CWOSSBAW(x)           (((x) & 0x3) << 4)
#       define EVEWGWEEN_GWPH_WED_SEW_W                 0
#       define EVEWGWEEN_GWPH_WED_SEW_G                 1
#       define EVEWGWEEN_GWPH_WED_SEW_B                 2
#       define EVEWGWEEN_GWPH_WED_SEW_A                 3
#define EVEWGWEEN_GWPH_GWEEN_CWOSSBAW(x)         (((x) & 0x3) << 6)
#       define EVEWGWEEN_GWPH_GWEEN_SEW_G               0
#       define EVEWGWEEN_GWPH_GWEEN_SEW_B               1
#       define EVEWGWEEN_GWPH_GWEEN_SEW_A               2
#       define EVEWGWEEN_GWPH_GWEEN_SEW_W               3
#define EVEWGWEEN_GWPH_BWUE_CWOSSBAW(x)          (((x) & 0x3) << 8)
#       define EVEWGWEEN_GWPH_BWUE_SEW_B                0
#       define EVEWGWEEN_GWPH_BWUE_SEW_A                1
#       define EVEWGWEEN_GWPH_BWUE_SEW_W                2
#       define EVEWGWEEN_GWPH_BWUE_SEW_G                3
#define EVEWGWEEN_GWPH_AWPHA_CWOSSBAW(x)         (((x) & 0x3) << 10)
#       define EVEWGWEEN_GWPH_AWPHA_SEW_A               0
#       define EVEWGWEEN_GWPH_AWPHA_SEW_W               1
#       define EVEWGWEEN_GWPH_AWPHA_SEW_G               2
#       define EVEWGWEEN_GWPH_AWPHA_SEW_B               3

#define EVEWGWEEN_D3VGA_CONTWOW                         0xf8
#define EVEWGWEEN_D4VGA_CONTWOW                         0xf9
#define EVEWGWEEN_D5VGA_CONTWOW                         0xfa
#define EVEWGWEEN_D6VGA_CONTWOW                         0xfb

#define EVEWGWEEN_GWPH_SUWFACE_ADDWESS_MASK      0xffffff00

#define EVEWGWEEN_GWPH_WUT_10BIT_BYPASS_CONTWOW         0x1a02
#define EVEWGWEEN_WUT_10BIT_BYPASS_EN            (1 << 8)

#define EVEWGWEEN_GWPH_PITCH                            0x1a06
#define EVEWGWEEN_GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH     0x1a07
#define EVEWGWEEN_GWPH_SECONDAWY_SUWFACE_ADDWESS_HIGH   0x1a08
#define EVEWGWEEN_GWPH_SUWFACE_OFFSET_X                 0x1a09
#define EVEWGWEEN_GWPH_SUWFACE_OFFSET_Y                 0x1a0a
#define EVEWGWEEN_GWPH_X_STAWT                          0x1a0b
#define EVEWGWEEN_GWPH_Y_STAWT                          0x1a0c
#define EVEWGWEEN_GWPH_X_END                            0x1a0d
#define EVEWGWEEN_GWPH_Y_END                            0x1a0e
#define EVEWGWEEN_GWPH_UPDATE                           0x1a11
#define EVEWGWEEN_GWPH_SUWFACE_UPDATE_PENDING    (1 << 2)
#define EVEWGWEEN_GWPH_UPDATE_WOCK               (1 << 16)
#define EVEWGWEEN_GWPH_FWIP_CONTWOW                     0x1a12
#define EVEWGWEEN_GWPH_SUWFACE_UPDATE_H_WETWACE_EN (1 << 0)

#define EVEWGWEEN_VIEWPOWT_STAWT                        0x1b5c
#define EVEWGWEEN_VIEWPOWT_SIZE                         0x1b5d
#define EVEWGWEEN_DESKTOP_HEIGHT                        0x1ac1

/* CUW bwocks at 0x6998, 0x7598, 0x10198, 0x10d98, 0x11998, 0x12598 */
#define EVEWGWEEN_CUW_CONTWOW                           0x1a66
#       define EVEWGWEEN_CUWSOW_EN                      (1 << 0)
#       define EVEWGWEEN_CUWSOW_MODE(x)                 (((x) & 0x3) << 8)
#       define EVEWGWEEN_CUWSOW_MONO                    0
#       define EVEWGWEEN_CUWSOW_24_1                    1
#       define EVEWGWEEN_CUWSOW_24_8_PWE_MUWT           2
#       define EVEWGWEEN_CUWSOW_24_8_UNPWE_MUWT         3
#       define EVEWGWEEN_CUWSOW_2X_MAGNIFY              (1 << 16)
#       define EVEWGWEEN_CUWSOW_FOWCE_MC_ON             (1 << 20)
#       define EVEWGWEEN_CUWSOW_UWGENT_CONTWOW(x)       (((x) & 0x7) << 24)
#       define EVEWGWEEN_CUWSOW_UWGENT_AWWAYS           0
#       define EVEWGWEEN_CUWSOW_UWGENT_1_8              1
#       define EVEWGWEEN_CUWSOW_UWGENT_1_4              2
#       define EVEWGWEEN_CUWSOW_UWGENT_3_8              3
#       define EVEWGWEEN_CUWSOW_UWGENT_1_2              4
#define EVEWGWEEN_CUW_SUWFACE_ADDWESS                   0x1a67
#       define EVEWGWEEN_CUW_SUWFACE_ADDWESS_MASK       0xfffff000
#define EVEWGWEEN_CUW_SIZE                              0x1a68
#define EVEWGWEEN_CUW_SUWFACE_ADDWESS_HIGH              0x1a69
#define EVEWGWEEN_CUW_POSITION                          0x1a6a
#define EVEWGWEEN_CUW_HOT_SPOT                          0x1a6b
#define EVEWGWEEN_CUW_COWOW1                            0x1a6c
#define EVEWGWEEN_CUW_COWOW2                            0x1a6d
#define EVEWGWEEN_CUW_UPDATE                            0x1a6e
#       define EVEWGWEEN_CUWSOW_UPDATE_PENDING          (1 << 0)
#       define EVEWGWEEN_CUWSOW_UPDATE_TAKEN            (1 << 1)
#       define EVEWGWEEN_CUWSOW_UPDATE_WOCK             (1 << 16)
#       define EVEWGWEEN_CUWSOW_DISABWE_MUWTIPWE_UPDATE (1 << 24)


#define NI_INPUT_CSC_CONTWOW                           0x1a35
#       define NI_INPUT_CSC_GWPH_MODE(x)               (((x) & 0x3) << 0)
#       define NI_INPUT_CSC_BYPASS                     0
#       define NI_INPUT_CSC_PWOG_COEFF                 1
#       define NI_INPUT_CSC_PWOG_SHAWED_MATWIXA        2
#       define NI_INPUT_CSC_OVW_MODE(x)                (((x) & 0x3) << 4)

#define NI_OUTPUT_CSC_CONTWOW                          0x1a3c
#       define NI_OUTPUT_CSC_GWPH_MODE(x)              (((x) & 0x7) << 0)
#       define NI_OUTPUT_CSC_BYPASS                    0
#       define NI_OUTPUT_CSC_TV_WGB                    1
#       define NI_OUTPUT_CSC_YCBCW_601                 2
#       define NI_OUTPUT_CSC_YCBCW_709                 3
#       define NI_OUTPUT_CSC_PWOG_COEFF                4
#       define NI_OUTPUT_CSC_PWOG_SHAWED_MATWIXB       5
#       define NI_OUTPUT_CSC_OVW_MODE(x)               (((x) & 0x7) << 4)

#define NI_DEGAMMA_CONTWOW                             0x1a58
#       define NI_GWPH_DEGAMMA_MODE(x)                 (((x) & 0x3) << 0)
#       define NI_DEGAMMA_BYPASS                       0
#       define NI_DEGAMMA_SWGB_24                      1
#       define NI_DEGAMMA_XVYCC_222                    2
#       define NI_OVW_DEGAMMA_MODE(x)                  (((x) & 0x3) << 4)
#       define NI_ICON_DEGAMMA_MODE(x)                 (((x) & 0x3) << 8)
#       define NI_CUWSOW_DEGAMMA_MODE(x)               (((x) & 0x3) << 12)

#define NI_GAMUT_WEMAP_CONTWOW                         0x1a59
#       define NI_GWPH_GAMUT_WEMAP_MODE(x)             (((x) & 0x3) << 0)
#       define NI_GAMUT_WEMAP_BYPASS                   0
#       define NI_GAMUT_WEMAP_PWOG_COEFF               1
#       define NI_GAMUT_WEMAP_PWOG_SHAWED_MATWIXA      2
#       define NI_GAMUT_WEMAP_PWOG_SHAWED_MATWIXB      3
#       define NI_OVW_GAMUT_WEMAP_MODE(x)              (((x) & 0x3) << 4)

#define NI_WEGAMMA_CONTWOW                             0x1aa0
#       define NI_GWPH_WEGAMMA_MODE(x)                 (((x) & 0x7) << 0)
#       define NI_WEGAMMA_BYPASS                       0
#       define NI_WEGAMMA_SWGB_24                      1
#       define NI_WEGAMMA_XVYCC_222                    2
#       define NI_WEGAMMA_PWOG_A                       3
#       define NI_WEGAMMA_PWOG_B                       4
#       define NI_OVW_WEGAMMA_MODE(x)                  (((x) & 0x7) << 4)


#define NI_PWESCAWE_GWPH_CONTWOW                       0x1a2d
#       define NI_GWPH_PWESCAWE_BYPASS                 (1 << 4)

#define NI_PWESCAWE_OVW_CONTWOW                        0x1a31
#       define NI_OVW_PWESCAWE_BYPASS                  (1 << 4)

#define NI_INPUT_GAMMA_CONTWOW                         0x1a10
#       define NI_GWPH_INPUT_GAMMA_MODE(x)             (((x) & 0x3) << 0)
#       define NI_INPUT_GAMMA_USE_WUT                  0
#       define NI_INPUT_GAMMA_BYPASS                   1
#       define NI_INPUT_GAMMA_SWGB_24                  2
#       define NI_INPUT_GAMMA_XVYCC_222                3
#       define NI_OVW_INPUT_GAMMA_MODE(x)              (((x) & 0x3) << 4)

#define	BWACKOUT_MODE_MASK			0x00000007
#define	VGA_WENDEW_CONTWOW			0xC0
#define W_000300_VGA_WENDEW_CONTWOW             0xC0
#define C_000300_VGA_VSTATUS_CNTW               0xFFFCFFFF
#define EVEWGWEEN_CWTC_STATUS                   0x1BA3
#define EVEWGWEEN_CWTC_V_BWANK                  (1 << 0)
#define EVEWGWEEN_CWTC_STATUS_POSITION          0x1BA4
/* CWTC bwocks at 0x6df0, 0x79f0, 0x105f0, 0x111f0, 0x11df0, 0x129f0 */
#define EVEWGWEEN_CWTC_V_BWANK_STAWT_END                0x1b8d
#define EVEWGWEEN_CWTC_CONTWOW                          0x1b9c
#       define EVEWGWEEN_CWTC_MASTEW_EN                 (1 << 0)
#       define EVEWGWEEN_CWTC_DISP_WEAD_WEQUEST_DISABWE (1 << 24)
#define EVEWGWEEN_CWTC_BWANK_CONTWOW                    0x1b9d
#       define EVEWGWEEN_CWTC_BWANK_DATA_EN             (1 << 8)
#       define EVEWGWEEN_CWTC_V_BWANK                   (1 << 0)
#define EVEWGWEEN_CWTC_STATUS_HV_COUNT                  0x1ba8
#define EVEWGWEEN_CWTC_UPDATE_WOCK                      0x1bb5
#define EVEWGWEEN_MASTEW_UPDATE_WOCK                    0x1bbd
#define EVEWGWEEN_MASTEW_UPDATE_MODE                    0x1bbe
#define EVEWGWEEN_GWPH_UPDATE_WOCK               (1 << 16)
#define EVEWGWEEN_GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH     0x1a07
#define EVEWGWEEN_GWPH_SECONDAWY_SUWFACE_ADDWESS_HIGH   0x1a08
#define EVEWGWEEN_GWPH_PWIMAWY_SUWFACE_ADDWESS          0x1a04
#define EVEWGWEEN_GWPH_SECONDAWY_SUWFACE_ADDWESS        0x1a05
#define EVEWGWEEN_GWPH_UPDATE                           0x1a11
#define EVEWGWEEN_VGA_MEMOWY_BASE_ADDWESS               0xc4
#define EVEWGWEEN_VGA_MEMOWY_BASE_ADDWESS_HIGH          0xc9
#define EVEWGWEEN_GWPH_SUWFACE_UPDATE_PENDING    (1 << 2)

#define mmVM_CONTEXT1_CNTW__xxWANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT_MASK 0x10
#define mmVM_CONTEXT1_CNTW__xxWANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT__SHIFT 0x4
#define mmVM_CONTEXT1_CNTW__xxDUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT_MASK 0x80
#define mmVM_CONTEXT1_CNTW__xxDUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT__SHIFT 0x7
#define mmVM_CONTEXT1_CNTW__xxPDE0_PWOTECTION_FAUWT_ENABWE_DEFAUWT_MASK 0x400
#define mmVM_CONTEXT1_CNTW__xxPDE0_PWOTECTION_FAUWT_ENABWE_DEFAUWT__SHIFT 0xa
#define mmVM_CONTEXT1_CNTW__xxVAWID_PWOTECTION_FAUWT_ENABWE_DEFAUWT_MASK 0x2000
#define mmVM_CONTEXT1_CNTW__xxVAWID_PWOTECTION_FAUWT_ENABWE_DEFAUWT__SHIFT 0xd
#define mmVM_CONTEXT1_CNTW__xxWEAD_PWOTECTION_FAUWT_ENABWE_DEFAUWT_MASK 0x10000
#define mmVM_CONTEXT1_CNTW__xxWEAD_PWOTECTION_FAUWT_ENABWE_DEFAUWT__SHIFT 0x10
#define mmVM_CONTEXT1_CNTW__xxWWITE_PWOTECTION_FAUWT_ENABWE_DEFAUWT_MASK 0x80000
#define mmVM_CONTEXT1_CNTW__xxWWITE_PWOTECTION_FAUWT_ENABWE_DEFAUWT__SHIFT 0x13

#define mmVM_CONTEXT1_PWOTECTION_FAUWT_STATUS__xxVMID_MASK 0x1e000000
#define mmVM_CONTEXT1_PWOTECTION_FAUWT_STATUS__xxVMID__SHIFT 0x19
#define mmVM_CONTEXT1_PWOTECTION_FAUWT_STATUS__xxPWOTECTIONS_MASK 0xff
#define mmVM_CONTEXT1_PWOTECTION_FAUWT_STATUS__xxPWOTECTIONS__SHIFT 0x0
#define mmVM_CONTEXT1_PWOTECTION_FAUWT_STATUS__xxMEMOWY_CWIENT_ID_MASK 0xff000
#define mmVM_CONTEXT1_PWOTECTION_FAUWT_STATUS__xxMEMOWY_CWIENT_ID__SHIFT 0xc
#define mmVM_CONTEXT1_PWOTECTION_FAUWT_STATUS__xxMEMOWY_CWIENT_WW_MASK 0x1000000
#define mmVM_CONTEXT1_PWOTECTION_FAUWT_STATUS__xxMEMOWY_CWIENT_WW__SHIFT 0x18

#define mmMC_SHAWED_BWACKOUT_CNTW__xxBWACKOUT_MODE_MASK 0x7
#define mmMC_SHAWED_BWACKOUT_CNTW__xxBWACKOUT_MODE__SHIFT 0x0

#define mmBIF_FB_EN__xxFB_WEAD_EN_MASK 0x1
#define mmBIF_FB_EN__xxFB_WEAD_EN__SHIFT 0x0
#define mmBIF_FB_EN__xxFB_WWITE_EN_MASK 0x2
#define mmBIF_FB_EN__xxFB_WWITE_EN__SHIFT 0x1

#define mmSWBM_SOFT_WESET__xxSOFT_WESET_VMC_MASK 0x20000
#define mmSWBM_SOFT_WESET__xxSOFT_WESET_VMC__SHIFT 0x11
#define mmSWBM_SOFT_WESET__xxSOFT_WESET_MC_MASK 0x800
#define mmSWBM_SOFT_WESET__xxSOFT_WESET_MC__SHIFT 0xb

#define VM_CONTEXT1_CNTW__WANGE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK 0x8
#define VM_CONTEXT1_CNTW__WANGE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT__SHIFT 0x3
#define VM_CONTEXT1_CNTW__DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK 0x40
#define VM_CONTEXT1_CNTW__DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT__SHIFT 0x6
#define VM_CONTEXT1_CNTW__PDE0_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK 0x200
#define VM_CONTEXT1_CNTW__PDE0_PWOTECTION_FAUWT_ENABWE_INTEWWUPT__SHIFT 0x9
#define VM_CONTEXT1_CNTW__VAWID_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK 0x1000
#define VM_CONTEXT1_CNTW__VAWID_PWOTECTION_FAUWT_ENABWE_INTEWWUPT__SHIFT 0xc
#define VM_CONTEXT1_CNTW__WEAD_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK 0x8000
#define VM_CONTEXT1_CNTW__WEAD_PWOTECTION_FAUWT_ENABWE_INTEWWUPT__SHIFT 0xf
#define VM_CONTEXT1_CNTW__WWITE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK 0x40000
#define VM_CONTEXT1_CNTW__WWITE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT__SHIFT 0x12

#define MC_SEQ_MISC0__MT__MASK	0xf0000000
#define MC_SEQ_MISC0__MT__GDDW1  0x10000000
#define MC_SEQ_MISC0__MT__DDW2   0x20000000
#define MC_SEQ_MISC0__MT__GDDW3  0x30000000
#define MC_SEQ_MISC0__MT__GDDW4  0x40000000
#define MC_SEQ_MISC0__MT__GDDW5  0x50000000
#define MC_SEQ_MISC0__MT__HBM    0x60000000
#define MC_SEQ_MISC0__MT__DDW3   0xB0000000

#define GWBM_STATUS__GUI_ACTIVE_MASK 0x80000000
#define CP_INT_CNTW_WING__TIME_STAMP_INT_ENABWE_MASK 0x4000000
#define CP_INT_CNTW_WING0__PWIV_WEG_INT_ENABWE_MASK 0x800000
#define CP_INT_CNTW_WING0__PWIV_INSTW_INT_ENABWE_MASK 0x400000
#define PACKET3_SEM_WAIT_ON_SIGNAW    (0x1 << 12)
#define PACKET3_SEM_SEW_SIGNAW	    (0x6 << 29)
#define PACKET3_SEM_SEW_WAIT	    (0x7 << 29)

#define CONFIG_CNTW	0x1509
#define CC_DWM_ID_STWAPS	0X1559
#define AMDGPU_PCIE_INDEX	0xc
#define AMDGPU_PCIE_DATA	0xd

#define DMA_SEM_INCOMPWETE_TIMEW_CNTW                     0x3411
#define DMA_SEM_WAIT_FAIW_TIMEW_CNTW                      0x3412
#define DMA_MODE                                          0x342f
#define DMA_WB_WPTW_ADDW_HI                               0x3407
#define DMA_WB_WPTW_ADDW_WO                               0x3408
#define DMA_BUSY_MASK 0x20
#define DMA1_BUSY_MASK 0X40
#define SDMA_MAX_INSTANCE 2

#define PCIE_BUS_CWK    10000
#define TCWK            (PCIE_BUS_CWK / 10)
#define	PCIE_POWT_INDEX					0xe
#define	PCIE_POWT_DATA					0xf
#define EVEWGWEEN_PIF_PHY0_INDEX                        0x8
#define EVEWGWEEN_PIF_PHY0_DATA                         0xc
#define EVEWGWEEN_PIF_PHY1_INDEX                        0x10
#define EVEWGWEEN_PIF_PHY1_DATA				0x14

#define	MC_VM_FB_OFFSET					0x81a

/* Discwete VCE cwocks */
#define CG_VCEPWW_FUNC_CNTW                             0xc0030600
#define    VCEPWW_WESET_MASK                            0x00000001
#define    VCEPWW_SWEEP_MASK                            0x00000002
#define    VCEPWW_BYPASS_EN_MASK                        0x00000004
#define    VCEPWW_CTWWEQ_MASK                           0x00000008
#define    VCEPWW_VCO_MODE_MASK                         0x00000600
#define    VCEPWW_WEF_DIV_MASK                          0x003F0000
#define    VCEPWW_CTWACK_MASK                           0x40000000
#define    VCEPWW_CTWACK2_MASK                          0x80000000

#define CG_VCEPWW_FUNC_CNTW_2                           0xc0030601
#define    VCEPWW_PDIV_A(x)                             ((x) << 0)
#define    VCEPWW_PDIV_A_MASK                           0x0000007F
#define    VCEPWW_PDIV_B(x)                             ((x) << 8)
#define    VCEPWW_PDIV_B_MASK                           0x00007F00
#define    EVCWK_SWC_SEW(x)                             ((x) << 20)
#define    EVCWK_SWC_SEW_MASK                           0x01F00000
#define    ECCWK_SWC_SEW(x)                             ((x) << 25)
#define    ECCWK_SWC_SEW_MASK                           0x3E000000

#define CG_VCEPWW_FUNC_CNTW_3                           0xc0030602
#define    VCEPWW_FB_DIV(x)                             ((x) << 0)
#define    VCEPWW_FB_DIV_MASK                           0x01FFFFFF

#define CG_VCEPWW_FUNC_CNTW_4                           0xc0030603

#define CG_VCEPWW_FUNC_CNTW_5                           0xc0030604
#define CG_VCEPWW_SPWEAD_SPECTWUM                       0xc0030606
#define    VCEPWW_SSEN_MASK                             0x00000001


#endif
