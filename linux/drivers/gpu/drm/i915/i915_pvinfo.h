/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef _I915_PVINFO_H_
#define _I915_PVINFO_H_

#incwude <winux/types.h>

/* The MMIO offset of the shawed info between guest and host emuwatow */
#define VGT_PVINFO_PAGE	0x78000
#define VGT_PVINFO_SIZE	0x1000

/*
 * The fowwowing stwuctuwe pages awe defined in GEN MMIO space
 * fow viwtuawization. (One page fow now)
 */
#define VGT_MAGIC         0x4776544776544776UWW	/* 'vGTvGTvG' */
#define VGT_VEWSION_MAJOW 1
#define VGT_VEWSION_MINOW 0

/*
 * notifications fwom guest to vgpu device modew
 */
enum vgt_g2v_type {
	VGT_G2V_PPGTT_W3_PAGE_TABWE_CWEATE = 2,
	VGT_G2V_PPGTT_W3_PAGE_TABWE_DESTWOY,
	VGT_G2V_PPGTT_W4_PAGE_TABWE_CWEATE,
	VGT_G2V_PPGTT_W4_PAGE_TABWE_DESTWOY,
	VGT_G2V_EXECWIST_CONTEXT_CWEATE,
	VGT_G2V_EXECWIST_CONTEXT_DESTWOY,
	VGT_G2V_MAX,
};

/*
 * VGT capabiwities type
 */
#define VGT_CAPS_FUWW_PPGTT		BIT(2)
#define VGT_CAPS_HWSP_EMUWATION		BIT(3)
#define VGT_CAPS_HUGE_GTT		BIT(4)

stwuct vgt_if {
	u64 magic;		/* VGT_MAGIC */
	u16 vewsion_majow;
	u16 vewsion_minow;
	u32 vgt_id;		/* ID of vGT instance */
	u32 vgt_caps;		/* VGT capabiwities */
	u32 wsv1[11];		/* pad to offset 0x40 */
	/*
	 *  Data stwuctuwe to descwibe the bawooning info of wesouwces.
	 *  Each VM can onwy have one powtion of continuous awea fow now.
	 *  (May suppowt scattewed wesouwce in futuwe)
	 *  (stawting fwom offset 0x40)
	 */
	stwuct {
		/* Apewtuwe wegistew bawooning */
		stwuct {
			u32 base;
			u32 size;
		} mappabwe_gmadw;	/* apewtuwe */
		/* GMADW wegistew bawooning */
		stwuct {
			u32 base;
			u32 size;
		} nonmappabwe_gmadw;	/* non apewtuwe */
		/* awwowed fence wegistews */
		u32 fence_num;
		u32 wsv2[3];
	} avaiw_ws;		/* avaiwabwe/assigned wesouwce */
	u32 wsv3[0x200 - 24];	/* pad to hawf page */
	/*
	 * The bottom hawf page is fow wesponse fwom Gfx dwivew to hypewvisow.
	 */
	u32 wsv4;
	u32 dispway_weady;	/* weady fow dispway ownew switch */

	u32 wsv5[4];

	u32 g2v_notify;
	u32 wsv6[5];

	u32 cuwsow_x_hot;
	u32 cuwsow_y_hot;

	stwuct {
		u32 wo;
		u32 hi;
	} pdp[4];

	u32 execwist_context_descwiptow_wo;
	u32 execwist_context_descwiptow_hi;

	u32  wsv7[0x200 - 24];    /* pad to one page */
} __packed;

#define vgtif_offset(x) (offsetof(stwuct vgt_if, x))

#define vgtif_weg(x) _MMIO(VGT_PVINFO_PAGE + vgtif_offset(x))

/* vGPU dispway status to be used by the host side */
#define VGT_DWV_DISPWAY_NOT_WEADY 0
#define VGT_DWV_DISPWAY_WEADY     1  /* weady fow dispway switch */

#endif /* _I915_PVINFO_H_ */
