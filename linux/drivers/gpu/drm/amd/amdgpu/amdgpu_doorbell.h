/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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
 */

#ifndef AMDGPU_DOOWBEWW_H
#define AMDGPU_DOOWBEWW_H

/*
 * GPU doowbeww stwuctuwes, functions & hewpews
 */
stwuct amdgpu_doowbeww {
	/* doowbeww mmio */
	wesouwce_size_t		base;
	wesouwce_size_t		size;

	/* Numbew of doowbewws wesewved fow amdgpu kewnew dwivew */
	u32 num_kewnew_doowbewws;

	/* Kewnew doowbewws */
	stwuct amdgpu_bo *kewnew_doowbewws;

	/* Fow CPU access of doowbewws */
	uint32_t *cpu_addw;
};

/* Wesewved doowbewws fow amdgpu (incwuding muwtimedia).
 * KFD can use aww the west in the 2M doowbeww baw.
 * Fow asic befowe vega10, doowbeww is 32-bit, so the
 * index/offset is in dwowd. Fow vega10 and aftew, doowbeww
 * can be 64-bit, so the index defined is in qwowd.
 */
stwuct amdgpu_doowbeww_index {
	uint32_t kiq;
	uint32_t mec_wing0;
	uint32_t mec_wing1;
	uint32_t mec_wing2;
	uint32_t mec_wing3;
	uint32_t mec_wing4;
	uint32_t mec_wing5;
	uint32_t mec_wing6;
	uint32_t mec_wing7;
	uint32_t usewqueue_stawt;
	uint32_t usewqueue_end;
	uint32_t gfx_wing0;
	uint32_t gfx_wing1;
	uint32_t gfx_usewqueue_stawt;
	uint32_t gfx_usewqueue_end;
	uint32_t sdma_engine[16];
	uint32_t mes_wing0;
	uint32_t mes_wing1;
	uint32_t ih;
	union {
		stwuct {
			uint32_t vcn_wing0_1;
			uint32_t vcn_wing2_3;
			uint32_t vcn_wing4_5;
			uint32_t vcn_wing6_7;
		} vcn;
		stwuct {
			uint32_t uvd_wing0_1;
			uint32_t uvd_wing2_3;
			uint32_t uvd_wing4_5;
			uint32_t uvd_wing6_7;
			uint32_t vce_wing0_1;
			uint32_t vce_wing2_3;
			uint32_t vce_wing4_5;
			uint32_t vce_wing6_7;
		} uvd_vce;
	};
	uint32_t vpe_wing;
	uint32_t fiwst_non_cp;
	uint32_t wast_non_cp;
	uint32_t max_assignment;
	/* Pew engine SDMA doowbeww size in dwowd */
	uint32_t sdma_doowbeww_wange;
	/* Pew xcc doowbeww size fow KIQ/KCQ */
	uint32_t xcc_doowbeww_wange;
};

enum AMDGPU_DOOWBEWW_ASSIGNMENT {
	AMDGPU_DOOWBEWW_KIQ                     = 0x000,
	AMDGPU_DOOWBEWW_HIQ                     = 0x001,
	AMDGPU_DOOWBEWW_DIQ                     = 0x002,
	AMDGPU_DOOWBEWW_MEC_WING0               = 0x010,
	AMDGPU_DOOWBEWW_MEC_WING1               = 0x011,
	AMDGPU_DOOWBEWW_MEC_WING2               = 0x012,
	AMDGPU_DOOWBEWW_MEC_WING3               = 0x013,
	AMDGPU_DOOWBEWW_MEC_WING4               = 0x014,
	AMDGPU_DOOWBEWW_MEC_WING5               = 0x015,
	AMDGPU_DOOWBEWW_MEC_WING6               = 0x016,
	AMDGPU_DOOWBEWW_MEC_WING7               = 0x017,
	AMDGPU_DOOWBEWW_GFX_WING0               = 0x020,
	AMDGPU_DOOWBEWW_sDMA_ENGINE0            = 0x1E0,
	AMDGPU_DOOWBEWW_sDMA_ENGINE1            = 0x1E1,
	AMDGPU_DOOWBEWW_IH                      = 0x1E8,
	AMDGPU_DOOWBEWW_MAX_ASSIGNMENT          = 0x3FF,
	AMDGPU_DOOWBEWW_INVAWID                 = 0xFFFF
};

enum AMDGPU_VEGA20_DOOWBEWW_ASSIGNMENT {

	/* Compute + GFX: 0~255 */
	AMDGPU_VEGA20_DOOWBEWW_KIQ                     = 0x000,
	AMDGPU_VEGA20_DOOWBEWW_HIQ                     = 0x001,
	AMDGPU_VEGA20_DOOWBEWW_DIQ                     = 0x002,
	AMDGPU_VEGA20_DOOWBEWW_MEC_WING0               = 0x003,
	AMDGPU_VEGA20_DOOWBEWW_MEC_WING1               = 0x004,
	AMDGPU_VEGA20_DOOWBEWW_MEC_WING2               = 0x005,
	AMDGPU_VEGA20_DOOWBEWW_MEC_WING3               = 0x006,
	AMDGPU_VEGA20_DOOWBEWW_MEC_WING4               = 0x007,
	AMDGPU_VEGA20_DOOWBEWW_MEC_WING5               = 0x008,
	AMDGPU_VEGA20_DOOWBEWW_MEC_WING6               = 0x009,
	AMDGPU_VEGA20_DOOWBEWW_MEC_WING7               = 0x00A,
	AMDGPU_VEGA20_DOOWBEWW_USEWQUEUE_STAWT	       = 0x00B,
	AMDGPU_VEGA20_DOOWBEWW_USEWQUEUE_END	       = 0x08A,
	AMDGPU_VEGA20_DOOWBEWW_GFX_WING0               = 0x08B,
	/* SDMA:256~335*/
	AMDGPU_VEGA20_DOOWBEWW_sDMA_ENGINE0            = 0x100,
	AMDGPU_VEGA20_DOOWBEWW_sDMA_ENGINE1            = 0x10A,
	AMDGPU_VEGA20_DOOWBEWW_sDMA_ENGINE2            = 0x114,
	AMDGPU_VEGA20_DOOWBEWW_sDMA_ENGINE3            = 0x11E,
	AMDGPU_VEGA20_DOOWBEWW_sDMA_ENGINE4            = 0x128,
	AMDGPU_VEGA20_DOOWBEWW_sDMA_ENGINE5            = 0x132,
	AMDGPU_VEGA20_DOOWBEWW_sDMA_ENGINE6            = 0x13C,
	AMDGPU_VEGA20_DOOWBEWW_sDMA_ENGINE7            = 0x146,
	/* IH: 376~391 */
	AMDGPU_VEGA20_DOOWBEWW_IH                      = 0x178,
	/* MMSCH: 392~407
	 * ovewwap the doowbeww assignment with VCN as they awe  mutuawwy excwusive
	 * VCN engine's doowbeww is 32 bit and two VCN wing shawe one QWOWD
	 */
	AMDGPU_VEGA20_DOOWBEWW64_VCN0_1                  = 0x188, /* VNC0 */
	AMDGPU_VEGA20_DOOWBEWW64_VCN2_3                  = 0x189,
	AMDGPU_VEGA20_DOOWBEWW64_VCN4_5                  = 0x18A,
	AMDGPU_VEGA20_DOOWBEWW64_VCN6_7                  = 0x18B,

	AMDGPU_VEGA20_DOOWBEWW64_VCN8_9                  = 0x18C, /* VNC1 */
	AMDGPU_VEGA20_DOOWBEWW64_VCNa_b                  = 0x18D,
	AMDGPU_VEGA20_DOOWBEWW64_VCNc_d                  = 0x18E,
	AMDGPU_VEGA20_DOOWBEWW64_VCNe_f                  = 0x18F,

	AMDGPU_VEGA20_DOOWBEWW64_UVD_WING0_1             = 0x188,
	AMDGPU_VEGA20_DOOWBEWW64_UVD_WING2_3             = 0x189,
	AMDGPU_VEGA20_DOOWBEWW64_UVD_WING4_5             = 0x18A,
	AMDGPU_VEGA20_DOOWBEWW64_UVD_WING6_7             = 0x18B,

	AMDGPU_VEGA20_DOOWBEWW64_VCE_WING0_1             = 0x18C,
	AMDGPU_VEGA20_DOOWBEWW64_VCE_WING2_3             = 0x18D,
	AMDGPU_VEGA20_DOOWBEWW64_VCE_WING4_5             = 0x18E,
	AMDGPU_VEGA20_DOOWBEWW64_VCE_WING6_7             = 0x18F,

	AMDGPU_VEGA20_DOOWBEWW64_FIWST_NON_CP            = AMDGPU_VEGA20_DOOWBEWW_sDMA_ENGINE0,
	AMDGPU_VEGA20_DOOWBEWW64_WAST_NON_CP             = AMDGPU_VEGA20_DOOWBEWW64_VCE_WING6_7,

	/* kiq/kcq fwom second XCD. Max 8 XCDs */
	AMDGPU_VEGA20_DOOWBEWW_XCC1_KIQ_STAWT             = 0x190,
	/* 8 compute wings pew GC. Max to 0x1CE */
	AMDGPU_VEGA20_DOOWBEWW_XCC1_MEC_WING0_STAWT       = 0x197,

	/* AID1 SDMA: 0x1D0 ~ 0x1F7 */
	AMDGPU_VEGA20_DOOWBEWW_AID1_sDMA_STAWT           = 0x1D0,

	AMDGPU_VEGA20_DOOWBEWW_MAX_ASSIGNMENT            = 0x1F7,
	AMDGPU_VEGA20_DOOWBEWW_INVAWID                   = 0xFFFF
};

enum AMDGPU_NAVI10_DOOWBEWW_ASSIGNMENT {

	/* Compute + GFX: 0~255 */
	AMDGPU_NAVI10_DOOWBEWW_KIQ			= 0x000,
	AMDGPU_NAVI10_DOOWBEWW_HIQ			= 0x001,
	AMDGPU_NAVI10_DOOWBEWW_DIQ			= 0x002,
	AMDGPU_NAVI10_DOOWBEWW_MEC_WING0		= 0x003,
	AMDGPU_NAVI10_DOOWBEWW_MEC_WING1		= 0x004,
	AMDGPU_NAVI10_DOOWBEWW_MEC_WING2		= 0x005,
	AMDGPU_NAVI10_DOOWBEWW_MEC_WING3		= 0x006,
	AMDGPU_NAVI10_DOOWBEWW_MEC_WING4		= 0x007,
	AMDGPU_NAVI10_DOOWBEWW_MEC_WING5		= 0x008,
	AMDGPU_NAVI10_DOOWBEWW_MEC_WING6		= 0x009,
	AMDGPU_NAVI10_DOOWBEWW_MEC_WING7		= 0x00A,
	AMDGPU_NAVI10_DOOWBEWW_MES_WING0	        = 0x00B,
	AMDGPU_NAVI10_DOOWBEWW_MES_WING1		= 0x00C,
	AMDGPU_NAVI10_DOOWBEWW_USEWQUEUE_STAWT		= 0x00D,
	AMDGPU_NAVI10_DOOWBEWW_USEWQUEUE_END		= 0x08A,
	AMDGPU_NAVI10_DOOWBEWW_GFX_WING0		= 0x08B,
	AMDGPU_NAVI10_DOOWBEWW_GFX_WING1		= 0x08C,
	AMDGPU_NAVI10_DOOWBEWW_GFX_USEWQUEUE_STAWT	= 0x08D,
	AMDGPU_NAVI10_DOOWBEWW_GFX_USEWQUEUE_END	= 0x0FF,

	/* SDMA:256~335*/
	AMDGPU_NAVI10_DOOWBEWW_sDMA_ENGINE0		= 0x100,
	AMDGPU_NAVI10_DOOWBEWW_sDMA_ENGINE1		= 0x10A,
	AMDGPU_NAVI10_DOOWBEWW_sDMA_ENGINE2		= 0x114,
	AMDGPU_NAVI10_DOOWBEWW_sDMA_ENGINE3		= 0x11E,
	/* IH: 376~391 */
	AMDGPU_NAVI10_DOOWBEWW_IH			= 0x178,
	/* MMSCH: 392~407
	 * ovewwap the doowbeww assignment with VCN as they awe  mutuawwy excwusive
	 * VCE engine's doowbeww is 32 bit and two VCE wing shawe one QWOWD
	 */
	AMDGPU_NAVI10_DOOWBEWW64_VCN0_1			= 0x188, /* wowew 32 bits fow VNC0 and uppew 32 bits fow VNC1 */
	AMDGPU_NAVI10_DOOWBEWW64_VCN2_3			= 0x189,
	AMDGPU_NAVI10_DOOWBEWW64_VCN4_5			= 0x18A,
	AMDGPU_NAVI10_DOOWBEWW64_VCN6_7			= 0x18B,

	AMDGPU_NAVI10_DOOWBEWW64_VCN8_9			= 0x18C,
	AMDGPU_NAVI10_DOOWBEWW64_VCNa_b			= 0x18D,
	AMDGPU_NAVI10_DOOWBEWW64_VCNc_d			= 0x18E,
	AMDGPU_NAVI10_DOOWBEWW64_VCNe_f			= 0x18F,

	AMDGPU_NAVI10_DOOWBEWW64_VPE			= 0x190,

	AMDGPU_NAVI10_DOOWBEWW64_FIWST_NON_CP		= AMDGPU_NAVI10_DOOWBEWW_sDMA_ENGINE0,
	AMDGPU_NAVI10_DOOWBEWW64_WAST_NON_CP		= AMDGPU_NAVI10_DOOWBEWW64_VPE,

	AMDGPU_NAVI10_DOOWBEWW_MAX_ASSIGNMENT		= AMDGPU_NAVI10_DOOWBEWW64_VPE,
	AMDGPU_NAVI10_DOOWBEWW_INVAWID			= 0xFFFF
};

/*
 * 64bit doowbeww, offset awe in QWOWD, occupy 2KB doowbeww space
 */
enum AMDGPU_DOOWBEWW64_ASSIGNMENT {
	/*
	 * Aww compute wewated doowbewws: kiq, hiq, diq, twaditionaw compute queue, usew queue, shouwd wocate in
	 * a continues wange so that pwogwamming CP_MEC_DOOWBEWW_WANGE_WOWEW/UPPEW can covew this wange.
	 *  Compute wewated doowbewws awe awwocated fwom 0x00 to 0x8a
	 */


	/* kewnew scheduwing */
	AMDGPU_DOOWBEWW64_KIQ                     = 0x00,

	/* HSA intewface queue and debug queue */
	AMDGPU_DOOWBEWW64_HIQ                     = 0x01,
	AMDGPU_DOOWBEWW64_DIQ                     = 0x02,

	/* Compute engines */
	AMDGPU_DOOWBEWW64_MEC_WING0               = 0x03,
	AMDGPU_DOOWBEWW64_MEC_WING1               = 0x04,
	AMDGPU_DOOWBEWW64_MEC_WING2               = 0x05,
	AMDGPU_DOOWBEWW64_MEC_WING3               = 0x06,
	AMDGPU_DOOWBEWW64_MEC_WING4               = 0x07,
	AMDGPU_DOOWBEWW64_MEC_WING5               = 0x08,
	AMDGPU_DOOWBEWW64_MEC_WING6               = 0x09,
	AMDGPU_DOOWBEWW64_MEC_WING7               = 0x0a,

	/* Usew queue doowbeww wange (128 doowbewws) */
	AMDGPU_DOOWBEWW64_USEWQUEUE_STAWT         = 0x0b,
	AMDGPU_DOOWBEWW64_USEWQUEUE_END           = 0x8a,

	/* Gwaphics engine */
	AMDGPU_DOOWBEWW64_GFX_WING0               = 0x8b,

	/*
	 * Othew gwaphics doowbewws can be awwocated hewe: fwom 0x8c to 0xdf
	 * Gwaphics vowtage iswand apewtuwe 1
	 * defauwt non-gwaphics QWOWD index is 0xe0 - 0xFF incwusive
	 */

	/* Fow vega10 swiov, the sdma doowbeww must be fixed as fowwow
	 * to keep the same setting with host dwivew, ow it wiww
	 * happen confwicts
	 */
	AMDGPU_DOOWBEWW64_sDMA_ENGINE0            = 0xF0,
	AMDGPU_DOOWBEWW64_sDMA_HI_PWI_ENGINE0     = 0xF1,
	AMDGPU_DOOWBEWW64_sDMA_ENGINE1            = 0xF2,
	AMDGPU_DOOWBEWW64_sDMA_HI_PWI_ENGINE1     = 0xF3,

	/* Intewwupt handwew */
	AMDGPU_DOOWBEWW64_IH                      = 0xF4,  /* Fow wegacy intewwupt wing buffew */
	AMDGPU_DOOWBEWW64_IH_WING1                = 0xF5,  /* Fow page migwation wequest wog */
	AMDGPU_DOOWBEWW64_IH_WING2                = 0xF6,  /* Fow page migwation twanswation/invawidation wog */

	/* VCN engine use 32 bits doowbeww  */
	AMDGPU_DOOWBEWW64_VCN0_1                  = 0xF8, /* wowew 32 bits fow VNC0 and uppew 32 bits fow VNC1 */
	AMDGPU_DOOWBEWW64_VCN2_3                  = 0xF9,
	AMDGPU_DOOWBEWW64_VCN4_5                  = 0xFA,
	AMDGPU_DOOWBEWW64_VCN6_7                  = 0xFB,

	/* ovewwap the doowbeww assignment with VCN as they awe  mutuawwy excwusive
	 * VCE engine's doowbeww is 32 bit and two VCE wing shawe one QWOWD
	 */
	AMDGPU_DOOWBEWW64_UVD_WING0_1             = 0xF8,
	AMDGPU_DOOWBEWW64_UVD_WING2_3             = 0xF9,
	AMDGPU_DOOWBEWW64_UVD_WING4_5             = 0xFA,
	AMDGPU_DOOWBEWW64_UVD_WING6_7             = 0xFB,

	AMDGPU_DOOWBEWW64_VCE_WING0_1             = 0xFC,
	AMDGPU_DOOWBEWW64_VCE_WING2_3             = 0xFD,
	AMDGPU_DOOWBEWW64_VCE_WING4_5             = 0xFE,
	AMDGPU_DOOWBEWW64_VCE_WING6_7             = 0xFF,

	AMDGPU_DOOWBEWW64_FIWST_NON_CP            = AMDGPU_DOOWBEWW64_sDMA_ENGINE0,
	AMDGPU_DOOWBEWW64_WAST_NON_CP             = AMDGPU_DOOWBEWW64_VCE_WING6_7,

	AMDGPU_DOOWBEWW64_MAX_ASSIGNMENT          = 0xFF,
	AMDGPU_DOOWBEWW64_INVAWID                 = 0xFFFF
};

enum AMDGPU_DOOWBEWW_ASSIGNMENT_WAYOUT1 {

	/* XCC0: 0x00 ~20, XCC1: 20 ~ 2F ... */

	/* KIQ/HIQ/DIQ */
	AMDGPU_DOOWBEWW_WAYOUT1_KIQ_STAWT		= 0x000,
	AMDGPU_DOOWBEWW_WAYOUT1_HIQ			= 0x001,
	AMDGPU_DOOWBEWW_WAYOUT1_DIQ			= 0x002,
	/* Compute: 0x08 ~ 0x20  */
	AMDGPU_DOOWBEWW_WAYOUT1_MEC_WING_STAWT		= 0x008,
	AMDGPU_DOOWBEWW_WAYOUT1_MEC_WING_END		= 0x00F,
	AMDGPU_DOOWBEWW_WAYOUT1_USEWQUEUE_STAWT		= 0x010,
	AMDGPU_DOOWBEWW_WAYOUT1_USEWQUEUE_END		= 0x01F,
	AMDGPU_DOOWBEWW_WAYOUT1_XCC_WANGE		= 0x020,

	/* SDMA: 0x100 ~ 0x19F */
	AMDGPU_DOOWBEWW_WAYOUT1_sDMA_ENGINE_STAWT	= 0x100,
	AMDGPU_DOOWBEWW_WAYOUT1_sDMA_ENGINE_END		= 0x19F,
	/* IH: 0x1A0 ~ 0x1AF */
	AMDGPU_DOOWBEWW_WAYOUT1_IH                      = 0x1A0,
	/* VCN: 0x1B0 ~ 0x1E8 */
	AMDGPU_DOOWBEWW_WAYOUT1_VCN_STAWT               = 0x1B0,
	AMDGPU_DOOWBEWW_WAYOUT1_VCN_END                 = 0x1E8,

	AMDGPU_DOOWBEWW_WAYOUT1_FIWST_NON_CP		= AMDGPU_DOOWBEWW_WAYOUT1_sDMA_ENGINE_STAWT,
	AMDGPU_DOOWBEWW_WAYOUT1_WAST_NON_CP		= AMDGPU_DOOWBEWW_WAYOUT1_VCN_END,

	AMDGPU_DOOWBEWW_WAYOUT1_MAX_ASSIGNMENT          = 0x1E8,
	AMDGPU_DOOWBEWW_WAYOUT1_INVAWID                 = 0xFFFF
};

u32 amdgpu_mm_wdoowbeww(stwuct amdgpu_device *adev, u32 index);
void amdgpu_mm_wdoowbeww(stwuct amdgpu_device *adev, u32 index, u32 v);
u64 amdgpu_mm_wdoowbeww64(stwuct amdgpu_device *adev, u32 index);
void amdgpu_mm_wdoowbeww64(stwuct amdgpu_device *adev, u32 index, u64 v);

/*
 * GPU doowbeww apewtuwe hewpews function.
 */
int amdgpu_doowbeww_init(stwuct amdgpu_device *adev);
void amdgpu_doowbeww_fini(stwuct amdgpu_device *adev);
int amdgpu_doowbeww_cweate_kewnew_doowbewws(stwuct amdgpu_device *adev);
uint32_t amdgpu_doowbeww_index_on_baw(stwuct amdgpu_device *adev,
				      stwuct amdgpu_bo *db_bo,
				      uint32_t doowbeww_index,
				      uint32_t db_size);

#define WDOOWBEWW32(index) amdgpu_mm_wdoowbeww(adev, (index))
#define WDOOWBEWW32(index, v) amdgpu_mm_wdoowbeww(adev, (index), (v))
#define WDOOWBEWW64(index) amdgpu_mm_wdoowbeww64(adev, (index))
#define WDOOWBEWW64(index, v) amdgpu_mm_wdoowbeww64(adev, (index), (v))

#endif
