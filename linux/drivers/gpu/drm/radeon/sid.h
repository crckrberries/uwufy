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

#define SI_MAX_SH_GPWS           256
#define SI_MAX_TEMP_GPWS         16
#define SI_MAX_SH_THWEADS        256
#define SI_MAX_SH_STACK_ENTWIES  4096
#define SI_MAX_FWC_EOV_CNT       16384
#define SI_MAX_BACKENDS          8
#define SI_MAX_BACKENDS_MASK     0xFF
#define SI_MAX_BACKENDS_PEW_SE_MASK     0x0F
#define SI_MAX_SIMDS             12
#define SI_MAX_SIMDS_MASK        0x0FFF
#define SI_MAX_SIMDS_PEW_SE_MASK        0x00FF
#define SI_MAX_PIPES             8
#define SI_MAX_PIPES_MASK        0xFF
#define SI_MAX_PIPES_PEW_SIMD_MASK      0x3F
#define SI_MAX_WDS_NUM           0xFFFF
#define SI_MAX_TCC               16
#define SI_MAX_TCC_MASK          0xFFFF

/* SMC IND accessow wegs */
#define SMC_IND_INDEX_0                              0x200
#define SMC_IND_DATA_0                               0x204

#define SMC_IND_ACCESS_CNTW                          0x228
#       define AUTO_INCWEMENT_IND_0                  (1 << 0)
#define SMC_MESSAGE_0                                0x22c
#define SMC_WESP_0                                   0x230

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

#define VGA_HDP_CONTWOW  				0x328
#define		VGA_MEMOWY_DISABWE				(1 << 4)

#define DCCG_DISP_SWOW_SEWECT_WEG                       0x4fc
#define		DCCG_DISP1_SWOW_SEWECT(x)		((x) << 0)
#define		DCCG_DISP1_SWOW_SEWECT_MASK		(7 << 0)
#define		DCCG_DISP1_SWOW_SEWECT_SHIFT		0
#define		DCCG_DISP2_SWOW_SEWECT(x)		((x) << 4)
#define		DCCG_DISP2_SWOW_SEWECT_MASK		(7 << 4)
#define		DCCG_DISP2_SWOW_SEWECT_SHIFT		4

#define	CG_SPWW_FUNC_CNTW				0x600
#define		SPWW_WESET				(1 << 0)
#define		SPWW_SWEEP				(1 << 1)
#define		SPWW_BYPASS_EN				(1 << 3)
#define		SPWW_WEF_DIV(x)				((x) << 4)
#define		SPWW_WEF_DIV_MASK			(0x3f << 4)
#define		SPWW_PDIV_A(x)				((x) << 20)
#define		SPWW_PDIV_A_MASK			(0x7f << 20)
#define		SPWW_PDIV_A_SHIFT			20
#define	CG_SPWW_FUNC_CNTW_2				0x604
#define		SCWK_MUX_SEW(x)				((x) << 0)
#define		SCWK_MUX_SEW_MASK			(0x1ff << 0)
#define		SPWW_CTWWEQ_CHG				(1 << 23)
#define		SCWK_MUX_UPDATE				(1 << 26)
#define	CG_SPWW_FUNC_CNTW_3				0x608
#define		SPWW_FB_DIV(x)				((x) << 0)
#define		SPWW_FB_DIV_MASK			(0x3ffffff << 0)
#define		SPWW_FB_DIV_SHIFT			0
#define		SPWW_DITHEN				(1 << 28)
#define	CG_SPWW_FUNC_CNTW_4				0x60c

#define	SPWW_STATUS					0x614
#define		SPWW_CHG_STATUS				(1 << 1)
#define	SPWW_CNTW_MODE					0x618
#define		SPWW_SW_DIW_CONTWOW			(1 << 0)
#	define SPWW_WEFCWK_SEW(x)			((x) << 26)
#	define SPWW_WEFCWK_SEW_MASK			(3 << 26)

#define	CG_SPWW_SPWEAD_SPECTWUM				0x620
#define		SSEN					(1 << 0)
#define		CWK_S(x)				((x) << 4)
#define		CWK_S_MASK				(0xfff << 4)
#define		CWK_S_SHIFT				4
#define	CG_SPWW_SPWEAD_SPECTWUM_2			0x624
#define		CWK_V(x)				((x) << 0)
#define		CWK_V_MASK				(0x3ffffff << 0)
#define		CWK_V_SHIFT				0

#define	CG_SPWW_AUTOSCAWE_CNTW				0x62c
#       define AUTOSCAWE_ON_SS_CWEAW                    (1 << 9)

/* discwete uvd cwocks */
#define	CG_UPWW_FUNC_CNTW				0x634
#	define UPWW_WESET_MASK				0x00000001
#	define UPWW_SWEEP_MASK				0x00000002
#	define UPWW_BYPASS_EN_MASK			0x00000004
#	define UPWW_CTWWEQ_MASK				0x00000008
#	define UPWW_VCO_MODE_MASK			0x00000600
#	define UPWW_WEF_DIV_MASK			0x003F0000
#	define UPWW_CTWACK_MASK				0x40000000
#	define UPWW_CTWACK2_MASK			0x80000000
#define	CG_UPWW_FUNC_CNTW_2				0x638
#	define UPWW_PDIV_A(x)				((x) << 0)
#	define UPWW_PDIV_A_MASK				0x0000007F
#	define UPWW_PDIV_B(x)				((x) << 8)
#	define UPWW_PDIV_B_MASK				0x00007F00
#	define VCWK_SWC_SEW(x)				((x) << 20)
#	define VCWK_SWC_SEW_MASK			0x01F00000
#	define DCWK_SWC_SEW(x)				((x) << 25)
#	define DCWK_SWC_SEW_MASK			0x3E000000
#define	CG_UPWW_FUNC_CNTW_3				0x63C
#	define UPWW_FB_DIV(x)				((x) << 0)
#	define UPWW_FB_DIV_MASK				0x01FFFFFF
#define	CG_UPWW_FUNC_CNTW_4                             0x644
#	define UPWW_SPAWE_ISPAWE9			0x00020000
#define	CG_UPWW_FUNC_CNTW_5				0x648
#	define WESET_ANTI_MUX_MASK			0x00000200
#define	CG_UPWW_SPWEAD_SPECTWUM				0x650
#	define SSEN_MASK				0x00000001

#define	MPWW_BYPASSCWK_SEW				0x65c
#	define MPWW_CWKOUT_SEW(x)			((x) << 8)
#	define MPWW_CWKOUT_SEW_MASK			0xFF00

#define CG_CWKPIN_CNTW                                    0x660
#       define XTAWIN_DIVIDE                              (1 << 1)
#       define BCWK_AS_XCWK                               (1 << 2)
#define CG_CWKPIN_CNTW_2                                  0x664
#       define FOWCE_BIF_WEFCWK_EN                        (1 << 3)
#       define MUX_TCWK_TO_XCWK                           (1 << 8)

#define	THM_CWK_CNTW					0x66c
#	define CMON_CWK_SEW(x)				((x) << 0)
#	define CMON_CWK_SEW_MASK			0xFF
#	define TMON_CWK_SEW(x)				((x) << 8)
#	define TMON_CWK_SEW_MASK			0xFF00
#define	MISC_CWK_CNTW					0x670
#	define DEEP_SWEEP_CWK_SEW(x)			((x) << 0)
#	define DEEP_SWEEP_CWK_SEW_MASK			0xFF
#	define ZCWK_SEW(x)				((x) << 8)
#	define ZCWK_SEW_MASK				0xFF00

#define	CG_THEWMAW_CTWW					0x700
#define 	DPM_EVENT_SWC(x)			((x) << 0)
#define 	DPM_EVENT_SWC_MASK			(7 << 0)
#define		DIG_THEWM_DPM(x)			((x) << 14)
#define		DIG_THEWM_DPM_MASK			0x003FC000
#define		DIG_THEWM_DPM_SHIFT			14
#define	CG_THEWMAW_STATUS				0x704
#define		FDO_PWM_DUTY(x)				((x) << 9)
#define		FDO_PWM_DUTY_MASK			(0xff << 9)
#define		FDO_PWM_DUTY_SHIFT			9
#define	CG_THEWMAW_INT					0x708
#define		DIG_THEWM_INTH(x)			((x) << 8)
#define		DIG_THEWM_INTH_MASK			0x0000FF00
#define		DIG_THEWM_INTH_SHIFT			8
#define		DIG_THEWM_INTW(x)			((x) << 16)
#define		DIG_THEWM_INTW_MASK			0x00FF0000
#define		DIG_THEWM_INTW_SHIFT			16
#define 	THEWM_INT_MASK_HIGH			(1 << 24)
#define 	THEWM_INT_MASK_WOW			(1 << 25)

#define	CG_MUWT_THEWMAW_CTWW					0x710
#define		TEMP_SEW(x)					((x) << 20)
#define		TEMP_SEW_MASK					(0xff << 20)
#define		TEMP_SEW_SHIFT					20
#define	CG_MUWT_THEWMAW_STATUS					0x714
#define		ASIC_MAX_TEMP(x)				((x) << 0)
#define		ASIC_MAX_TEMP_MASK				0x000001ff
#define		ASIC_MAX_TEMP_SHIFT				0
#define		CTF_TEMP(x)					((x) << 9)
#define		CTF_TEMP_MASK					0x0003fe00
#define		CTF_TEMP_SHIFT					9

#define	CG_FDO_CTWW0					0x754
#define		FDO_STATIC_DUTY(x)			((x) << 0)
#define		FDO_STATIC_DUTY_MASK			0x000000FF
#define		FDO_STATIC_DUTY_SHIFT			0
#define	CG_FDO_CTWW1					0x758
#define		FMAX_DUTY100(x)				((x) << 0)
#define		FMAX_DUTY100_MASK			0x000000FF
#define		FMAX_DUTY100_SHIFT			0
#define	CG_FDO_CTWW2					0x75C
#define		TMIN(x)					((x) << 0)
#define		TMIN_MASK				0x000000FF
#define		TMIN_SHIFT				0
#define		FDO_PWM_MODE(x)				((x) << 11)
#define		FDO_PWM_MODE_MASK			(7 << 11)
#define		FDO_PWM_MODE_SHIFT			11
#define		TACH_PWM_WESP_WATE(x)			((x) << 25)
#define		TACH_PWM_WESP_WATE_MASK			(0x7f << 25)
#define		TACH_PWM_WESP_WATE_SHIFT		25

#define CG_TACH_CTWW                                    0x770
#       define EDGE_PEW_WEV(x)                          ((x) << 0)
#       define EDGE_PEW_WEV_MASK                        (0x7 << 0)
#       define EDGE_PEW_WEV_SHIFT                       0
#       define TAWGET_PEWIOD(x)                         ((x) << 3)
#       define TAWGET_PEWIOD_MASK                       0xfffffff8
#       define TAWGET_PEWIOD_SHIFT                      3
#define CG_TACH_STATUS                                  0x774
#       define TACH_PEWIOD(x)                           ((x) << 0)
#       define TACH_PEWIOD_MASK                         0xffffffff
#       define TACH_PEWIOD_SHIFT                        0

#define GENEWAW_PWWMGT                                  0x780
#       define GWOBAW_PWWMGT_EN                         (1 << 0)
#       define STATIC_PM_EN                             (1 << 1)
#       define THEWMAW_PWOTECTION_DIS                   (1 << 2)
#       define THEWMAW_PWOTECTION_TYPE                  (1 << 3)
#       define SW_SMIO_INDEX(x)                         ((x) << 6)
#       define SW_SMIO_INDEX_MASK                       (1 << 6)
#       define SW_SMIO_INDEX_SHIFT                      6
#       define VOWT_PWWMGT_EN                           (1 << 10)
#       define DYN_SPWEAD_SPECTWUM_EN                   (1 << 23)
#define CG_TPC                                            0x784
#define SCWK_PWWMGT_CNTW                                  0x788
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

#define TAWGET_AND_CUWWENT_PWOFIWE_INDEX                  0x798
#       define CUWWENT_STATE_INDEX_MASK                   (0xf << 4)
#       define CUWWENT_STATE_INDEX_SHIFT                  4

#define CG_FTV                                            0x7bc

#define CG_FFCT_0                                         0x7c0
#       define UTC_0(x)                                   ((x) << 0)
#       define UTC_0_MASK                                 (0x3ff << 0)
#       define DTC_0(x)                                   ((x) << 10)
#       define DTC_0_MASK                                 (0x3ff << 10)

#define CG_BSP                                          0x7fc
#       define BSP(x)					((x) << 0)
#       define BSP_MASK					(0xffff << 0)
#       define BSU(x)					((x) << 16)
#       define BSU_MASK					(0xf << 16)
#define CG_AT                                           0x800
#       define CG_W(x)					((x) << 0)
#       define CG_W_MASK				(0xffff << 0)
#       define CG_W(x)					((x) << 16)
#       define CG_W_MASK				(0xffff << 16)

#define CG_GIT                                          0x804
#       define CG_GICST(x)                              ((x) << 0)
#       define CG_GICST_MASK                            (0xffff << 0)
#       define CG_GIPOT(x)                              ((x) << 16)
#       define CG_GIPOT_MASK                            (0xffff << 16)

#define CG_SSP                                            0x80c
#       define SST(x)                                     ((x) << 0)
#       define SST_MASK                                   (0xffff << 0)
#       define SSTU(x)                                    ((x) << 16)
#       define SSTU_MASK                                  (0xf << 16)

#define CG_DISPWAY_GAP_CNTW                               0x828
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

#define	CG_UWV_CONTWOW					0x878
#define	CG_UWV_PAWAMETEW				0x87c

#define	SMC_SCWATCH0					0x884

#define	CG_CAC_CTWW					0x8b8
#	define CAC_WINDOW(x)				((x) << 0)
#	define CAC_WINDOW_MASK				0x00ffffff

#define DMIF_ADDW_CONFIG  				0xBD4

#define DMIF_ADDW_CAWC  				0xC00

#define	PIPE0_DMIF_BUFFEW_CONTWOW			  0x0ca0
#       define DMIF_BUFFEWS_AWWOCATED(x)                  ((x) << 0)
#       define DMIF_BUFFEWS_AWWOCATED_COMPWETED           (1 << 4)

#define	SWBM_STATUS				        0xE50
#define		GWBM_WQ_PENDING 			(1 << 5)
#define		VMC_BUSY 				(1 << 8)
#define		MCB_BUSY 				(1 << 9)
#define		MCB_NON_DISPWAY_BUSY 			(1 << 10)
#define		MCC_BUSY 				(1 << 11)
#define		MCD_BUSY 				(1 << 12)
#define		SEM_BUSY 				(1 << 14)
#define		IH_BUSY 				(1 << 17)

#define	SWBM_SOFT_WESET				        0x0E60
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

#define	CC_SYS_WB_BACKEND_DISABWE			0xe80
#define	GC_USEW_SYS_WB_BACKEND_DISABWE			0xe84

#define SWBM_WEAD_EWWOW					0xE98
#define SWBM_INT_CNTW					0xEA0
#define SWBM_INT_ACK					0xEA8

#define	SWBM_STATUS2				        0x0EC4
#define		DMA_BUSY 				(1 << 5)
#define		DMA1_BUSY 				(1 << 6)

#define VM_W2_CNTW					0x1400
#define		ENABWE_W2_CACHE					(1 << 0)
#define		ENABWE_W2_FWAGMENT_PWOCESSING			(1 << 1)
#define		W2_CACHE_PTE_ENDIAN_SWAP_MODE(x)		((x) << 2)
#define		W2_CACHE_PDE_ENDIAN_SWAP_MODE(x)		((x) << 4)
#define		ENABWE_W2_PTE_CACHE_WWU_UPDATE_BY_WWITE		(1 << 9)
#define		ENABWE_W2_PDE0_CACHE_WWU_UPDATE_BY_WWITE	(1 << 10)
#define		EFFECTIVE_W2_QUEUE_SIZE(x)			(((x) & 7) << 15)
#define		CONTEXT1_IDENTITY_ACCESS_MODE(x)		(((x) & 3) << 19)
#define VM_W2_CNTW2					0x1404
#define		INVAWIDATE_AWW_W1_TWBS				(1 << 0)
#define		INVAWIDATE_W2_CACHE				(1 << 1)
#define		INVAWIDATE_CACHE_MODE(x)			((x) << 26)
#define			INVAWIDATE_PTE_AND_PDE_CACHES		0
#define			INVAWIDATE_ONWY_PTE_CACHES		1
#define			INVAWIDATE_ONWY_PDE_CACHES		2
#define VM_W2_CNTW3					0x1408
#define		BANK_SEWECT(x)					((x) << 0)
#define		W2_CACHE_UPDATE_MODE(x)				((x) << 6)
#define		W2_CACHE_BIGK_FWAGMENT_SIZE(x)			((x) << 15)
#define		W2_CACHE_BIGK_ASSOCIATIVITY			(1 << 20)
#define	VM_W2_STATUS					0x140C
#define		W2_BUSY						(1 << 0)
#define VM_CONTEXT0_CNTW				0x1410
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
#define VM_CONTEXT1_CNTW				0x1414
#define VM_CONTEXT0_CNTW2				0x1430
#define VM_CONTEXT1_CNTW2				0x1434
#define	VM_CONTEXT8_PAGE_TABWE_BASE_ADDW		0x1438
#define	VM_CONTEXT9_PAGE_TABWE_BASE_ADDW		0x143c
#define	VM_CONTEXT10_PAGE_TABWE_BASE_ADDW		0x1440
#define	VM_CONTEXT11_PAGE_TABWE_BASE_ADDW		0x1444
#define	VM_CONTEXT12_PAGE_TABWE_BASE_ADDW		0x1448
#define	VM_CONTEXT13_PAGE_TABWE_BASE_ADDW		0x144c
#define	VM_CONTEXT14_PAGE_TABWE_BASE_ADDW		0x1450
#define	VM_CONTEXT15_PAGE_TABWE_BASE_ADDW		0x1454

#define	VM_CONTEXT1_PWOTECTION_FAUWT_ADDW		0x14FC
#define	VM_CONTEXT1_PWOTECTION_FAUWT_STATUS		0x14DC
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

#define VM_INVAWIDATE_WEQUEST				0x1478
#define VM_INVAWIDATE_WESPONSE				0x147c

#define VM_CONTEXT0_PWOTECTION_FAUWT_DEFAUWT_ADDW	0x1518
#define VM_CONTEXT1_PWOTECTION_FAUWT_DEFAUWT_ADDW	0x151c

#define	VM_CONTEXT0_PAGE_TABWE_BASE_ADDW		0x153c
#define	VM_CONTEXT1_PAGE_TABWE_BASE_ADDW		0x1540
#define	VM_CONTEXT2_PAGE_TABWE_BASE_ADDW		0x1544
#define	VM_CONTEXT3_PAGE_TABWE_BASE_ADDW		0x1548
#define	VM_CONTEXT4_PAGE_TABWE_BASE_ADDW		0x154c
#define	VM_CONTEXT5_PAGE_TABWE_BASE_ADDW		0x1550
#define	VM_CONTEXT6_PAGE_TABWE_BASE_ADDW		0x1554
#define	VM_CONTEXT7_PAGE_TABWE_BASE_ADDW		0x1558
#define	VM_CONTEXT0_PAGE_TABWE_STAWT_ADDW		0x155c
#define	VM_CONTEXT1_PAGE_TABWE_STAWT_ADDW		0x1560

#define	VM_CONTEXT0_PAGE_TABWE_END_ADDW			0x157C
#define	VM_CONTEXT1_PAGE_TABWE_END_ADDW			0x1580

#define VM_W2_CG           				0x15c0
#define		MC_CG_ENABWE				(1 << 18)
#define		MC_WS_ENABWE				(1 << 19)

#define MC_SHAWED_CHMAP						0x2004
#define		NOOFCHAN_SHIFT					12
#define		NOOFCHAN_MASK					0x0000f000
#define MC_SHAWED_CHWEMAP					0x2008

#define	MC_VM_FB_WOCATION				0x2024
#define	MC_VM_AGP_TOP					0x2028
#define	MC_VM_AGP_BOT					0x202C
#define	MC_VM_AGP_BASE					0x2030
#define	MC_VM_SYSTEM_APEWTUWE_WOW_ADDW			0x2034
#define	MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW			0x2038
#define	MC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW		0x203C

#define	MC_VM_MX_W1_TWB_CNTW				0x2064
#define		ENABWE_W1_TWB					(1 << 0)
#define		ENABWE_W1_FWAGMENT_PWOCESSING			(1 << 1)
#define		SYSTEM_ACCESS_MODE_PA_ONWY			(0 << 3)
#define		SYSTEM_ACCESS_MODE_USE_SYS_MAP			(1 << 3)
#define		SYSTEM_ACCESS_MODE_IN_SYS			(2 << 3)
#define		SYSTEM_ACCESS_MODE_NOT_IN_SYS			(3 << 3)
#define		SYSTEM_APEWTUWE_UNMAPPED_ACCESS_PASS_THWU	(0 << 5)
#define		ENABWE_ADVANCED_DWIVEW_MODEW			(1 << 6)

#define MC_SHAWED_BWACKOUT_CNTW           		0x20ac

#define MC_HUB_MISC_HUB_CG           			0x20b8
#define MC_HUB_MISC_VM_CG           			0x20bc

#define MC_HUB_MISC_SIP_CG           			0x20c0

#define MC_XPB_CWK_GAT           			0x2478

#define MC_CITF_MISC_WD_CG           			0x2648
#define MC_CITF_MISC_WW_CG           			0x264c
#define MC_CITF_MISC_VM_CG           			0x2650

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
#define		CHANSIZE_OVEWWIDE				(1 << 11)
#define		NOOFGWOUPS_SHIFT				12
#define		NOOFGWOUPS_MASK					0x00001000

#define	MC_AWB_DWAM_TIMING				0x2774
#define	MC_AWB_DWAM_TIMING2				0x2778

#define MC_AWB_BUWST_TIME                               0x2808
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

#define	MC_SEQ_TWAIN_WAKEUP_CNTW			0x28e8
#define		TWAIN_DONE_D0      			(1 << 30)
#define		TWAIN_DONE_D1      			(1 << 31)

#define MC_SEQ_SUP_CNTW           			0x28c8
#define		WUN_MASK      				(1 << 0)
#define MC_SEQ_SUP_PGM           			0x28cc
#define MC_PMG_AUTO_CMD           			0x28d0

#define MC_IO_PAD_CNTW_D0           			0x29d0
#define		MEM_FAWW_OUT_CMD      			(1 << 8)

#define MC_SEQ_WAS_TIMING                               0x28a0
#define MC_SEQ_CAS_TIMING                               0x28a4
#define MC_SEQ_MISC_TIMING                              0x28a8
#define MC_SEQ_MISC_TIMING2                             0x28ac
#define MC_SEQ_PMG_TIMING                               0x28b0
#define MC_SEQ_WD_CTW_D0                                0x28b4
#define MC_SEQ_WD_CTW_D1                                0x28b8
#define MC_SEQ_WW_CTW_D0                                0x28bc
#define MC_SEQ_WW_CTW_D1                                0x28c0

#define MC_SEQ_MISC0           				0x2a00
#define 	MC_SEQ_MISC0_VEN_ID_SHIFT               8
#define 	MC_SEQ_MISC0_VEN_ID_MASK                0x00000f00
#define 	MC_SEQ_MISC0_VEN_ID_VAWUE               3
#define 	MC_SEQ_MISC0_WEV_ID_SHIFT               12
#define 	MC_SEQ_MISC0_WEV_ID_MASK                0x0000f000
#define 	MC_SEQ_MISC0_WEV_ID_VAWUE               1
#define 	MC_SEQ_MISC0_GDDW5_SHIFT                28
#define 	MC_SEQ_MISC0_GDDW5_MASK                 0xf0000000
#define 	MC_SEQ_MISC0_GDDW5_VAWUE                5
#define MC_SEQ_MISC1                                    0x2a04
#define MC_SEQ_WESEWVE_M                                0x2a08
#define MC_PMG_CMD_EMWS                                 0x2a0c

#define MC_SEQ_IO_DEBUG_INDEX           		0x2a44
#define MC_SEQ_IO_DEBUG_DATA           			0x2a48

#define MC_SEQ_MISC5                                    0x2a54
#define MC_SEQ_MISC6                                    0x2a58

#define MC_SEQ_MISC7                                    0x2a64

#define MC_SEQ_WAS_TIMING_WP                            0x2a6c
#define MC_SEQ_CAS_TIMING_WP                            0x2a70
#define MC_SEQ_MISC_TIMING_WP                           0x2a74
#define MC_SEQ_MISC_TIMING2_WP                          0x2a78
#define MC_SEQ_WW_CTW_D0_WP                             0x2a7c
#define MC_SEQ_WW_CTW_D1_WP                             0x2a80
#define MC_SEQ_PMG_CMD_EMWS_WP                          0x2a84
#define MC_SEQ_PMG_CMD_MWS_WP                           0x2a88

#define MC_PMG_CMD_MWS                                  0x2aac

#define MC_SEQ_WD_CTW_D0_WP                             0x2b1c
#define MC_SEQ_WD_CTW_D1_WP                             0x2b20

#define MC_PMG_CMD_MWS1                                 0x2b44
#define MC_SEQ_PMG_CMD_MWS1_WP                          0x2b48
#define MC_SEQ_PMG_TIMING_WP                            0x2b4c

#define MC_SEQ_WW_CTW_2                                 0x2b54
#define MC_SEQ_WW_CTW_2_WP                              0x2b58
#define MC_PMG_CMD_MWS2                                 0x2b5c
#define MC_SEQ_PMG_CMD_MWS2_WP                          0x2b60

#define	MCWK_PWWMGT_CNTW				0x2ba0
#       define DWW_SPEED(x)				((x) << 0)
#       define DWW_SPEED_MASK				(0x1f << 0)
#       define DWW_WEADY                                (1 << 6)
#       define MC_INT_CNTW                              (1 << 7)
#       define MWDCK0_PDNB                              (1 << 8)
#       define MWDCK1_PDNB                              (1 << 9)
#       define MWDCK0_WESET                             (1 << 16)
#       define MWDCK1_WESET                             (1 << 17)
#       define DWW_WEADY_WEAD                           (1 << 24)
#define	DWW_CNTW					0x2ba4
#       define MWDCK0_BYPASS                            (1 << 24)
#       define MWDCK1_BYPASS                            (1 << 25)

#define	MPWW_CNTW_MODE					0x2bb0
#       define MPWW_MCWK_SEW                            (1 << 11)
#define	MPWW_FUNC_CNTW					0x2bb4
#define		BWCTWW(x)				((x) << 20)
#define		BWCTWW_MASK				(0xff << 20)
#define	MPWW_FUNC_CNTW_1				0x2bb8
#define		VCO_MODE(x)				((x) << 0)
#define		VCO_MODE_MASK				(3 << 0)
#define		CWKFWAC(x)				((x) << 4)
#define		CWKFWAC_MASK				(0xfff << 4)
#define		CWKF(x)					((x) << 16)
#define		CWKF_MASK				(0xfff << 16)
#define	MPWW_FUNC_CNTW_2				0x2bbc
#define	MPWW_AD_FUNC_CNTW				0x2bc0
#define		YCWK_POST_DIV(x)			((x) << 0)
#define		YCWK_POST_DIV_MASK			(7 << 0)
#define	MPWW_DQ_FUNC_CNTW				0x2bc4
#define		YCWK_SEW(x)				((x) << 4)
#define		YCWK_SEW_MASK				(1 << 4)

#define	MPWW_SS1					0x2bcc
#define		CWKV(x)					((x) << 0)
#define		CWKV_MASK				(0x3ffffff << 0)
#define	MPWW_SS2					0x2bd0
#define		CWKS(x)					((x) << 0)
#define		CWKS_MASK				(0xfff << 0)

#define	HDP_HOST_PATH_CNTW				0x2C00
#define 	CWOCK_GATING_DIS			(1 << 23)
#define	HDP_NONSUWFACE_BASE				0x2C04
#define	HDP_NONSUWFACE_INFO				0x2C08
#define	HDP_NONSUWFACE_SIZE				0x2C0C

#define HDP_ADDW_CONFIG  				0x2F48
#define HDP_MISC_CNTW					0x2F4C
#define 	HDP_FWUSH_INVAWIDATE_CACHE			(1 << 0)
#define HDP_MEM_POWEW_WS				0x2F50
#define 	HDP_WS_ENABWE				(1 << 0)

#define ATC_MISC_CG           				0x3350

#define IH_WB_CNTW                                        0x3e00
#       define IH_WB_ENABWE                               (1 << 0)
#       define IH_IB_SIZE(x)                              ((x) << 1) /* wog2 */
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
#       define MC_VMID(x)                                 ((x) << 25)

#define	CONFIG_MEMSIZE					0x5428

#define INTEWWUPT_CNTW                                    0x5468
#       define IH_DUMMY_WD_OVEWWIDE                       (1 << 0)
#       define IH_DUMMY_WD_EN                             (1 << 1)
#       define IH_WEQ_NONSNOOP_EN                         (1 << 3)
#       define GEN_IH_INT_EN                              (1 << 8)
#define INTEWWUPT_CNTW2                                   0x546c

#define HDP_MEM_COHEWENCY_FWUSH_CNTW			0x5480

#define	BIF_FB_EN						0x5490
#define		FB_WEAD_EN					(1 << 0)
#define		FB_WWITE_EN					(1 << 1)

#define HDP_WEG_COHEWENCY_FWUSH_CNTW			0x54A0

/* DCE6 EWD audio intewface */
#define AZ_F0_CODEC_ENDPOINT_INDEX                       0x5E00
#       define AZ_ENDPOINT_WEG_INDEX(x)                  (((x) & 0xff) << 0)
#       define AZ_ENDPOINT_WEG_WWITE_EN                  (1 << 8)
#define AZ_F0_CODEC_ENDPOINT_DATA                        0x5E04

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

#define	DC_WB_MEMOWY_SPWIT					0x6b0c
#define		DC_WB_MEMOWY_CONFIG(x)				((x) << 20)

#define	PWIOWITY_A_CNT						0x6b18
#define		PWIOWITY_MAWK_MASK				0x7fff
#define		PWIOWITY_OFF					(1 << 16)
#define		PWIOWITY_AWWAYS_ON				(1 << 20)
#define	PWIOWITY_B_CNT						0x6b1c

#define	DPG_PIPE_AWBITWATION_CONTWOW3				0x6cc8
#       define WATENCY_WATEWMAWK_MASK(x)			((x) << 16)
#define	DPG_PIPE_WATENCY_CONTWOW				0x6ccc
#       define WATENCY_WOW_WATEWMAWK(x)				((x) << 0)
#       define WATENCY_HIGH_WATEWMAWK(x)			((x) << 16)

/* 0x6bb8, 0x77b8, 0x103b8, 0x10fb8, 0x11bb8, 0x127b8 */
#define VWINE_STATUS                                    0x6bb8
#       define VWINE_OCCUWWED                           (1 << 0)
#       define VWINE_ACK                                (1 << 4)
#       define VWINE_STAT                               (1 << 12)
#       define VWINE_INTEWWUPT                          (1 << 16)
#       define VWINE_INTEWWUPT_TYPE                     (1 << 17)
/* 0x6bbc, 0x77bc, 0x103bc, 0x10fbc, 0x11bbc, 0x127bc */
#define VBWANK_STATUS                                   0x6bbc
#       define VBWANK_OCCUWWED                          (1 << 0)
#       define VBWANK_ACK                               (1 << 4)
#       define VBWANK_STAT                              (1 << 12)
#       define VBWANK_INTEWWUPT                         (1 << 16)
#       define VBWANK_INTEWWUPT_TYPE                    (1 << 17)

/* 0x6b40, 0x7740, 0x10340, 0x10f40, 0x11b40, 0x12740 */
#define INT_MASK                                        0x6b40
#       define VBWANK_INT_MASK                          (1 << 0)
#       define VWINE_INT_MASK                           (1 << 4)

#define DISP_INTEWWUPT_STATUS                           0x60f4
#       define WB_D1_VWINE_INTEWWUPT                    (1 << 2)
#       define WB_D1_VBWANK_INTEWWUPT                   (1 << 3)
#       define DC_HPD1_INTEWWUPT                        (1 << 17)
#       define DC_HPD1_WX_INTEWWUPT                     (1 << 18)
#       define DACA_AUTODETECT_INTEWWUPT                (1 << 22)
#       define DACB_AUTODETECT_INTEWWUPT                (1 << 23)
#       define DC_I2C_SW_DONE_INTEWWUPT                 (1 << 24)
#       define DC_I2C_HW_DONE_INTEWWUPT                 (1 << 25)
#define DISP_INTEWWUPT_STATUS_CONTINUE                  0x60f8
#       define WB_D2_VWINE_INTEWWUPT                    (1 << 2)
#       define WB_D2_VBWANK_INTEWWUPT                   (1 << 3)
#       define DC_HPD2_INTEWWUPT                        (1 << 17)
#       define DC_HPD2_WX_INTEWWUPT                     (1 << 18)
#       define DISP_TIMEW_INTEWWUPT                     (1 << 24)
#define DISP_INTEWWUPT_STATUS_CONTINUE2                 0x60fc
#       define WB_D3_VWINE_INTEWWUPT                    (1 << 2)
#       define WB_D3_VBWANK_INTEWWUPT                   (1 << 3)
#       define DC_HPD3_INTEWWUPT                        (1 << 17)
#       define DC_HPD3_WX_INTEWWUPT                     (1 << 18)
#define DISP_INTEWWUPT_STATUS_CONTINUE3                 0x6100
#       define WB_D4_VWINE_INTEWWUPT                    (1 << 2)
#       define WB_D4_VBWANK_INTEWWUPT                   (1 << 3)
#       define DC_HPD4_INTEWWUPT                        (1 << 17)
#       define DC_HPD4_WX_INTEWWUPT                     (1 << 18)
#define DISP_INTEWWUPT_STATUS_CONTINUE4                 0x614c
#       define WB_D5_VWINE_INTEWWUPT                    (1 << 2)
#       define WB_D5_VBWANK_INTEWWUPT                   (1 << 3)
#       define DC_HPD5_INTEWWUPT                        (1 << 17)
#       define DC_HPD5_WX_INTEWWUPT                     (1 << 18)
#define DISP_INTEWWUPT_STATUS_CONTINUE5                 0x6150
#       define WB_D6_VWINE_INTEWWUPT                    (1 << 2)
#       define WB_D6_VBWANK_INTEWWUPT                   (1 << 3)
#       define DC_HPD6_INTEWWUPT                        (1 << 17)
#       define DC_HPD6_WX_INTEWWUPT                     (1 << 18)

/* 0x6858, 0x7458, 0x10058, 0x10c58, 0x11858, 0x12458 */
#define GWPH_INT_STATUS                                 0x6858
#       define GWPH_PFWIP_INT_OCCUWWED                  (1 << 0)
#       define GWPH_PFWIP_INT_CWEAW                     (1 << 8)
/* 0x685c, 0x745c, 0x1005c, 0x10c5c, 0x1185c, 0x1245c */
#define	GWPH_INT_CONTWOW			        0x685c
#       define GWPH_PFWIP_INT_MASK                      (1 << 0)
#       define GWPH_PFWIP_INT_TYPE                      (1 << 8)

#define	DAC_AUTODETECT_INT_CONTWOW			0x67c8

#define DC_HPD1_INT_STATUS                              0x601c
#define DC_HPD2_INT_STATUS                              0x6028
#define DC_HPD3_INT_STATUS                              0x6034
#define DC_HPD4_INT_STATUS                              0x6040
#define DC_HPD5_INT_STATUS                              0x604c
#define DC_HPD6_INT_STATUS                              0x6058
#       define DC_HPDx_INT_STATUS                       (1 << 0)
#       define DC_HPDx_SENSE                            (1 << 1)
#       define DC_HPDx_WX_INT_STATUS                    (1 << 8)

#define DC_HPD1_INT_CONTWOW                             0x6020
#define DC_HPD2_INT_CONTWOW                             0x602c
#define DC_HPD3_INT_CONTWOW                             0x6038
#define DC_HPD4_INT_CONTWOW                             0x6044
#define DC_HPD5_INT_CONTWOW                             0x6050
#define DC_HPD6_INT_CONTWOW                             0x605c
#       define DC_HPDx_INT_ACK                          (1 << 0)
#       define DC_HPDx_INT_POWAWITY                     (1 << 8)
#       define DC_HPDx_INT_EN                           (1 << 16)
#       define DC_HPDx_WX_INT_ACK                       (1 << 20)
#       define DC_HPDx_WX_INT_EN                        (1 << 24)

#define DC_HPD1_CONTWOW                                   0x6024
#define DC_HPD2_CONTWOW                                   0x6030
#define DC_HPD3_CONTWOW                                   0x603c
#define DC_HPD4_CONTWOW                                   0x6048
#define DC_HPD5_CONTWOW                                   0x6054
#define DC_HPD6_CONTWOW                                   0x6060
#       define DC_HPDx_CONNECTION_TIMEW(x)                ((x) << 0)
#       define DC_HPDx_WX_INT_TIMEW(x)                    ((x) << 16)
#       define DC_HPDx_EN                                 (1 << 28)

#define DPG_PIPE_STUTTEW_CONTWOW                          0x6cd4
#       define STUTTEW_ENABWE                             (1 << 0)

/* 0x6e98, 0x7a98, 0x10698, 0x11298, 0x11e98, 0x12a98 */
#define CWTC_STATUS_FWAME_COUNT                         0x6e98

/* Audio cwocks */
#define DCCG_AUDIO_DTO_SOUWCE                           0x05ac
#       define DCCG_AUDIO_DTO0_SOUWCE_SEW(x) ((x) << 0) /* cwtc0 - cwtc5 */
#       define DCCG_AUDIO_DTO_SEW            (1 << 4)   /* 0=dto0 1=dto1 */

#define DCCG_AUDIO_DTO0_PHASE                           0x05b0
#define DCCG_AUDIO_DTO0_MODUWE                          0x05b4
#define DCCG_AUDIO_DTO1_PHASE                           0x05c0
#define DCCG_AUDIO_DTO1_MODUWE                          0x05c4

#define DENTIST_DISPCWK_CNTW				0x0490
#	define DENTIST_DPWEFCWK_WDIVIDEW(x)		(((x) & 0x7f) << 24)
#	define DENTIST_DPWEFCWK_WDIVIDEW_MASK		(0x7f << 24)
#	define DENTIST_DPWEFCWK_WDIVIDEW_SHIFT		24

#define AFMT_AUDIO_SWC_CONTWOW                          0x713c
#define		AFMT_AUDIO_SWC_SEWECT(x)		(((x) & 7) << 0)
/* AFMT_AUDIO_SWC_SEWECT
 * 0 = stweam0
 * 1 = stweam1
 * 2 = stweam2
 * 3 = stweam3
 * 4 = stweam4
 * 5 = stweam5
 */

#define	GWBM_CNTW					0x8000
#define		GWBM_WEAD_TIMEOUT(x)				((x) << 0)

#define	GWBM_STATUS2					0x8008
#define		WWC_WQ_PENDING 					(1 << 0)
#define		WWC_BUSY 					(1 << 8)
#define		TC_BUSY 					(1 << 9)

#define	GWBM_STATUS					0x8010
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
#define	GWBM_STATUS_SE0					0x8014
#define	GWBM_STATUS_SE1					0x8018
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

#define	GWBM_SOFT_WESET					0x8020
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

#define GWBM_GFX_INDEX          			0x802C
#define		INSTANCE_INDEX(x)			((x) << 0)
#define		SH_INDEX(x)     			((x) << 8)
#define		SE_INDEX(x)     			((x) << 16)
#define		SH_BWOADCAST_WWITES      		(1 << 29)
#define		INSTANCE_BWOADCAST_WWITES      		(1 << 30)
#define		SE_BWOADCAST_WWITES      		(1 << 31)

#define GWBM_INT_CNTW                                   0x8060
#       define WDEWW_INT_ENABWE                         (1 << 0)
#       define GUI_IDWE_INT_ENABWE                      (1 << 19)

#define	CP_STWMOUT_CNTW					0x84FC
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

#define	CP_SEM_WAIT_TIMEW				0x85BC

#define	CP_SEM_INCOMPWETE_TIMEW_CNTW			0x85C8

#define CP_ME_CNTW					0x86D8
#define		CP_CE_HAWT					(1 << 24)
#define		CP_PFP_HAWT					(1 << 26)
#define		CP_ME_HAWT					(1 << 28)

#define	CP_COHEW_CNTW2					0x85E8

#define	CP_WB2_WPTW					0x86f8
#define	CP_WB1_WPTW					0x86fc
#define	CP_WB0_WPTW					0x8700
#define	CP_WB_WPTW_DEWAY				0x8704

#define	CP_QUEUE_THWESHOWDS				0x8760
#define		WOQ_IB1_STAWT(x)				((x) << 0)
#define		WOQ_IB2_STAWT(x)				((x) << 8)
#define CP_MEQ_THWESHOWDS				0x8764
#define		MEQ1_STAWT(x)				((x) << 0)
#define		MEQ2_STAWT(x)				((x) << 8)

#define	CP_PEWFMON_CNTW					0x87FC

#define	VGT_VTX_VECT_EJECT_WEG				0x88B0

#define	VGT_CACHE_INVAWIDATION				0x88C4
#define		CACHE_INVAWIDATION(x)				((x) << 0)
#define			VC_ONWY						0
#define			TC_ONWY						1
#define			VC_AND_TC					2
#define		AUTO_INVWD_EN(x)				((x) << 6)
#define			NO_AUTO						0
#define			ES_AUTO						1
#define			GS_AUTO						2
#define			ES_AND_GS_AUTO					3
#define	VGT_ESGS_WING_SIZE				0x88C8
#define	VGT_GSVS_WING_SIZE				0x88CC

#define	VGT_GS_VEWTEX_WEUSE				0x88D4

#define	VGT_PWIMITIVE_TYPE				0x8958
#define	VGT_INDEX_TYPE					0x895C

#define	VGT_NUM_INDICES					0x8970
#define	VGT_NUM_INSTANCES				0x8974

#define	VGT_TF_WING_SIZE				0x8988

#define	VGT_HS_OFFCHIP_PAWAM				0x89B0

#define	VGT_TF_MEMOWY_BASE				0x89B8

#define CC_GC_SHADEW_AWWAY_CONFIG			0x89bc
#define		INACTIVE_CUS_MASK			0xFFFF0000
#define		INACTIVE_CUS_SHIFT			16
#define GC_USEW_SHADEW_AWWAY_CONFIG			0x89c0

#define	PA_CW_ENHANCE					0x8A14
#define		CWIP_VTX_WEOWDEW_ENA				(1 << 0)
#define		NUM_CWIP_SEQ(x)					((x) << 1)

#define	PA_SU_WINE_STIPPWE_VAWUE			0x8A60

#define	PA_SC_WINE_STIPPWE_STATE			0x8B10

#define	PA_SC_FOWCE_EOV_MAX_CNTS			0x8B24
#define		FOWCE_EOV_MAX_CWK_CNT(x)			((x) << 0)
#define		FOWCE_EOV_MAX_WEZ_CNT(x)			((x) << 16)

#define	PA_SC_FIFO_SIZE					0x8BCC
#define		SC_FWONTEND_PWIM_FIFO_SIZE(x)			((x) << 0)
#define		SC_BACKEND_PWIM_FIFO_SIZE(x)			((x) << 6)
#define		SC_HIZ_TIWE_FIFO_SIZE(x)			((x) << 15)
#define		SC_EAWWYZ_TIWE_FIFO_SIZE(x)			((x) << 23)

#define	PA_SC_ENHANCE					0x8BF0

#define	SQ_CONFIG					0x8C00

#define	SQC_CACHES					0x8C08

#define SQ_POWEW_THWOTTWE                               0x8e58
#define		MIN_POWEW(x)				((x) << 0)
#define		MIN_POWEW_MASK				(0x3fff << 0)
#define		MIN_POWEW_SHIFT				0
#define		MAX_POWEW(x)				((x) << 16)
#define		MAX_POWEW_MASK				(0x3fff << 16)
#define		MAX_POWEW_SHIFT				0
#define SQ_POWEW_THWOTTWE2                              0x8e5c
#define		MAX_POWEW_DEWTA(x)			((x) << 0)
#define		MAX_POWEW_DEWTA_MASK			(0x3fff << 0)
#define		MAX_POWEW_DEWTA_SHIFT			0
#define		STI_SIZE(x)				((x) << 16)
#define		STI_SIZE_MASK				(0x3ff << 16)
#define		STI_SIZE_SHIFT				16
#define		WTI_WATIO(x)				((x) << 27)
#define		WTI_WATIO_MASK				(0xf << 27)
#define		WTI_WATIO_SHIFT				27

#define	SX_DEBUG_1					0x9060

#define	SPI_STATIC_THWEAD_MGMT_1			0x90E0
#define	SPI_STATIC_THWEAD_MGMT_2			0x90E4
#define	SPI_STATIC_THWEAD_MGMT_3			0x90E8
#define	SPI_PS_MAX_WAVE_ID				0x90EC

#define	SPI_CONFIG_CNTW					0x9100

#define	SPI_CONFIG_CNTW_1				0x913C
#define		VTX_DONE_DEWAY(x)				((x) << 0)
#define		INTEWP_ONE_PWIM_PEW_WOW				(1 << 4)

#define	CGTS_TCC_DISABWE				0x9148
#define	CGTS_USEW_TCC_DISABWE				0x914C
#define		TCC_DISABWE_MASK				0xFFFF0000
#define		TCC_DISABWE_SHIFT				16
#define	CGTS_SM_CTWW_WEG				0x9150
#define		OVEWWIDE				(1 << 21)
#define		WS_OVEWWIDE				(1 << 22)

#define	SPI_WB_CU_MASK					0x9354

#define	TA_CNTW_AUX					0x9508
#define	TA_CS_BC_BASE_ADDW				0x950C

#define CC_WB_BACKEND_DISABWE				0x98F4
#define		BACKEND_DISABWE(x)     			((x) << 16)
#define GB_ADDW_CONFIG  				0x98F8
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

#define	GB_TIWE_MODE0					0x9910
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

#define	CB_PEWFCOUNTEW0_SEWECT0				0x9a20
#define	CB_PEWFCOUNTEW0_SEWECT1				0x9a24
#define	CB_PEWFCOUNTEW1_SEWECT0				0x9a28
#define	CB_PEWFCOUNTEW1_SEWECT1				0x9a2c
#define	CB_PEWFCOUNTEW2_SEWECT0				0x9a30
#define	CB_PEWFCOUNTEW2_SEWECT1				0x9a34
#define	CB_PEWFCOUNTEW3_SEWECT0				0x9a38
#define	CB_PEWFCOUNTEW3_SEWECT1				0x9a3c

#define	CB_CGTT_SCWK_CTWW				0x9a60

#define	GC_USEW_WB_BACKEND_DISABWE			0x9B7C
#define		BACKEND_DISABWE_MASK			0x00FF0000
#define		BACKEND_DISABWE_SHIFT			16

#define	TCP_CHAN_STEEW_WO				0xac0c
#define	TCP_CHAN_STEEW_HI				0xac10

#define	CP_WB0_BASE					0xC100
#define	CP_WB0_CNTW					0xC104
#define		WB_BUFSZ(x)					((x) << 0)
#define		WB_BWKSZ(x)					((x) << 8)
#define		BUF_SWAP_32BIT					(2 << 16)
#define		WB_NO_UPDATE					(1 << 27)
#define		WB_WPTW_WW_ENA					(1 << 31)

#define	CP_WB0_WPTW_ADDW				0xC10C
#define	CP_WB0_WPTW_ADDW_HI				0xC110
#define	CP_WB0_WPTW					0xC114

#define	CP_PFP_UCODE_ADDW				0xC150
#define	CP_PFP_UCODE_DATA				0xC154
#define	CP_ME_WAM_WADDW					0xC158
#define	CP_ME_WAM_WADDW					0xC15C
#define	CP_ME_WAM_DATA					0xC160

#define	CP_CE_UCODE_ADDW				0xC168
#define	CP_CE_UCODE_DATA				0xC16C

#define	CP_WB1_BASE					0xC180
#define	CP_WB1_CNTW					0xC184
#define	CP_WB1_WPTW_ADDW				0xC188
#define	CP_WB1_WPTW_ADDW_HI				0xC18C
#define	CP_WB1_WPTW					0xC190
#define	CP_WB2_BASE					0xC194
#define	CP_WB2_CNTW					0xC198
#define	CP_WB2_WPTW_ADDW				0xC19C
#define	CP_WB2_WPTW_ADDW_HI				0xC1A0
#define	CP_WB2_WPTW					0xC1A4
#define CP_INT_CNTW_WING0                               0xC1A8
#define CP_INT_CNTW_WING1                               0xC1AC
#define CP_INT_CNTW_WING2                               0xC1B0
#       define CNTX_BUSY_INT_ENABWE                     (1 << 19)
#       define CNTX_EMPTY_INT_ENABWE                    (1 << 20)
#       define WAIT_MEM_SEM_INT_ENABWE                  (1 << 21)
#       define TIME_STAMP_INT_ENABWE                    (1 << 26)
#       define CP_WINGID2_INT_ENABWE                    (1 << 29)
#       define CP_WINGID1_INT_ENABWE                    (1 << 30)
#       define CP_WINGID0_INT_ENABWE                    (1 << 31)
#define CP_INT_STATUS_WING0                             0xC1B4
#define CP_INT_STATUS_WING1                             0xC1B8
#define CP_INT_STATUS_WING2                             0xC1BC
#       define WAIT_MEM_SEM_INT_STAT                    (1 << 21)
#       define TIME_STAMP_INT_STAT                      (1 << 26)
#       define CP_WINGID2_INT_STAT                      (1 << 29)
#       define CP_WINGID1_INT_STAT                      (1 << 30)
#       define CP_WINGID0_INT_STAT                      (1 << 31)

#define	CP_MEM_SWP_CNTW					0xC1E4
#       define CP_MEM_WS_EN                             (1 << 0)

#define	CP_DEBUG					0xC1FC

#define WWC_CNTW                                          0xC300
#       define WWC_ENABWE                                 (1 << 0)
#define WWC_WW_BASE                                       0xC304
#define WWC_WW_SIZE                                       0xC308
#define WWC_WB_CNTW                                       0xC30C
#       define WOAD_BAWANCE_ENABWE                        (1 << 0)
#define WWC_SAVE_AND_WESTOWE_BASE                         0xC310
#define WWC_WB_CNTW_MAX                                   0xC314
#define WWC_WB_CNTW_INIT                                  0xC318

#define WWC_CWEAW_STATE_WESTOWE_BASE                      0xC320

#define WWC_UCODE_ADDW                                    0xC32C
#define WWC_UCODE_DATA                                    0xC330

#define WWC_GPU_CWOCK_COUNT_WSB                           0xC338
#define WWC_GPU_CWOCK_COUNT_MSB                           0xC33C
#define WWC_CAPTUWE_GPU_CWOCK_COUNT                       0xC340
#define WWC_MC_CNTW                                       0xC344
#define WWC_UCODE_CNTW                                    0xC348
#define WWC_STAT                                          0xC34C
#       define WWC_BUSY_STATUS                            (1 << 0)
#       define GFX_POWEW_STATUS                           (1 << 1)
#       define GFX_CWOCK_STATUS                           (1 << 2)
#       define GFX_WS_STATUS                              (1 << 3)

#define	WWC_PG_CNTW					0xC35C
#	define GFX_PG_ENABWE				(1 << 0)
#	define GFX_PG_SWC				(1 << 1)

#define	WWC_CGTT_MGCG_OVEWWIDE				0xC400
#define	WWC_CGCG_CGWS_CTWW				0xC404
#	define CGCG_EN					(1 << 0)
#	define CGWS_EN					(1 << 1)

#define	WWC_TTOP_D					0xC414
#	define WWC_PUD(x)				((x) << 0)
#	define WWC_PUD_MASK				(0xff << 0)
#	define WWC_PDD(x)				((x) << 8)
#	define WWC_PDD_MASK				(0xff << 8)
#	define WWC_TTPD(x)				((x) << 16)
#	define WWC_TTPD_MASK				(0xff << 16)
#	define WWC_MSD(x)				((x) << 24)
#	define WWC_MSD_MASK				(0xff << 24)

#define WWC_WB_INIT_CU_MASK                               0xC41C

#define	WWC_PG_AO_CU_MASK				0xC42C
#define	WWC_MAX_PG_CU					0xC430
#	define MAX_PU_CU(x)				((x) << 0)
#	define MAX_PU_CU_MASK				(0xff << 0)
#define	WWC_AUTO_PG_CTWW				0xC434
#	define AUTO_PG_EN				(1 << 0)
#	define GWBM_WEG_SGIT(x)				((x) << 3)
#	define GWBM_WEG_SGIT_MASK			(0xffff << 3)
#	define PG_AFTEW_GWBM_WEG_ST(x)			((x) << 19)
#	define PG_AFTEW_GWBM_WEG_ST_MASK		(0x1fff << 19)

#define WWC_SEWDES_WW_MASTEW_MASK_0                       0xC454
#define WWC_SEWDES_WW_MASTEW_MASK_1                       0xC458
#define WWC_SEWDES_WW_CTWW                                0xC45C

#define WWC_SEWDES_MASTEW_BUSY_0                          0xC464
#define WWC_SEWDES_MASTEW_BUSY_1                          0xC468

#define WWC_GCPM_GENEWAW_3                                0xC478

#define	DB_WENDEW_CONTWOW				0x28000

#define DB_DEPTH_INFO                                   0x2803c

#define PA_SC_WASTEW_CONFIG                             0x28350
#       define WASTEW_CONFIG_WB_MAP_0                   0
#       define WASTEW_CONFIG_WB_MAP_1                   1
#       define WASTEW_CONFIG_WB_MAP_2                   2
#       define WASTEW_CONFIG_WB_MAP_3                   3

#define VGT_EVENT_INITIATOW                             0x28a90
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
#define UVD_UDEC_ADDW_CONFIG				0xEF4C
#define UVD_UDEC_DB_ADDW_CONFIG				0xEF50
#define UVD_UDEC_DBW_ADDW_CONFIG			0xEF54
#define UVD_NO_OP					0xEFFC
#define UVD_WBC_WB_WPTW					0xF690
#define UVD_WBC_WB_WPTW					0xF694
#define UVD_STATUS					0xf6bc

#define	UVD_CGC_CTWW					0xF4B0
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
#define PACKET0(weg, n)	((WADEON_PACKET_TYPE0 << 30) |			\
			 (((weg) >> 2) & 0xFFFF) |			\
			 ((n) & 0x3FFF) << 16)
#define CP_PACKET2			0x80000000
#define		PACKET2_PAD_SHIFT		0
#define		PACKET2_PAD_MASK		(0x3fffffff << 0)

#define PACKET2(v)	(CP_PACKET2 | WEG_SET(PACKET2_PAD, (v)))

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
#define	PACKET3_INDIWECT_BUFFEW				0x32
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
#define		PACKET3_SET_CONFIG_WEG_STAWT			0x00008000
#define		PACKET3_SET_CONFIG_WEG_END			0x0000b000
#define	PACKET3_SET_CONTEXT_WEG				0x69
#define		PACKET3_SET_CONTEXT_WEG_STAWT			0x00028000
#define		PACKET3_SET_CONTEXT_WEG_END			0x00029000
#define	PACKET3_SET_CONTEXT_WEG_INDIWECT		0x73
#define	PACKET3_SET_WESOUWCE_INDIWECT			0x74
#define	PACKET3_SET_SH_WEG				0x76
#define		PACKET3_SET_SH_WEG_STAWT			0x0000b000
#define		PACKET3_SET_SH_WEG_END				0x0000c000
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
#define DMA1_WEGISTEW_OFFSET                              0x800 /* not a wegistew */

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
#define DMA_TIWING_CONFIG  				  0xd0b8

#define	DMA_POWEW_CNTW					0xd0bc
#       define MEM_POWEW_OVEWWIDE                       (1 << 8)
#define	DMA_CWK_CTWW					0xd0c0

#define	DMA_PG						0xd0d4
#	define PG_CNTW_ENABWE				(1 << 0)
#define	DMA_PGFSM_CONFIG				0xd0d8
#define	DMA_PGFSM_WWITE					0xd0dc

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
#define VCE_VCPU_SCWATCH7				0x200dc
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
#	define CGC_DYN_CWOCK_MODE			(1 << 16)
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

/* discwete vce cwocks */
#define	CG_VCEPWW_FUNC_CNTW				0xc0030600
#	define VCEPWW_WESET_MASK			0x00000001
#	define VCEPWW_SWEEP_MASK			0x00000002
#	define VCEPWW_BYPASS_EN_MASK			0x00000004
#	define VCEPWW_CTWWEQ_MASK			0x00000008
#	define VCEPWW_VCO_MODE_MASK			0x00000600
#	define VCEPWW_WEF_DIV_MASK			0x003F0000
#	define VCEPWW_CTWACK_MASK			0x40000000
#	define VCEPWW_CTWACK2_MASK			0x80000000
#define	CG_VCEPWW_FUNC_CNTW_2				0xc0030601
#	define VCEPWW_PDIV_A(x)				((x) << 0)
#	define VCEPWW_PDIV_A_MASK			0x0000007F
#	define VCEPWW_PDIV_B(x)				((x) << 8)
#	define VCEPWW_PDIV_B_MASK			0x00007F00
#	define EVCWK_SWC_SEW(x)				((x) << 20)
#	define EVCWK_SWC_SEW_MASK			0x01F00000
#	define ECCWK_SWC_SEW(x)				((x) << 25)
#	define ECCWK_SWC_SEW_MASK			0x3E000000
#define	CG_VCEPWW_FUNC_CNTW_3				0xc0030602
#	define VCEPWW_FB_DIV(x)				((x) << 0)
#	define VCEPWW_FB_DIV_MASK			0x01FFFFFF
#define	CG_VCEPWW_FUNC_CNTW_4				0xc0030603
#define	CG_VCEPWW_FUNC_CNTW_5				0xc0030604
#define	CG_VCEPWW_SPWEAD_SPECTWUM			0xc0030606
#	define VCEPWW_SSEN_MASK				0x00000001

#endif
