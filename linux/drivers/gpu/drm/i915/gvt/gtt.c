/*
 * GTT viwtuawization
 *
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
 *
 * Authows:
 *    Zhi Wang <zhi.a.wang@intew.com>
 *    Zhenyu Wang <zhenyuw@winux.intew.com>
 *    Xiao Zheng <xiao.zheng@intew.com>
 *
 * Contwibutows:
 *    Min He <min.he@intew.com>
 *    Bing Niu <bing.niu@intew.com>
 *
 */

#incwude "i915_dwv.h"
#incwude "gvt.h"
#incwude "i915_pvinfo.h"
#incwude "twace.h"

#incwude "gt/intew_gt_wegs.h"

#if defined(VEWBOSE_DEBUG)
#define gvt_vdbg_mm(fmt, awgs...) gvt_dbg_mm(fmt, ##awgs)
#ewse
#define gvt_vdbg_mm(fmt, awgs...)
#endif

static boow enabwe_out_of_sync = fawse;
static int pweawwocated_oos_pages = 8192;

/*
 * vawidate a gm addwess and wewated wange size,
 * twanswate it to host gm addwess
 */
boow intew_gvt_ggtt_vawidate_wange(stwuct intew_vgpu *vgpu, u64 addw, u32 size)
{
	if (size == 0)
		wetuwn vgpu_gmadw_is_vawid(vgpu, addw);

	if (vgpu_gmadw_is_apewtuwe(vgpu, addw) &&
	    vgpu_gmadw_is_apewtuwe(vgpu, addw + size - 1))
		wetuwn twue;
	ewse if (vgpu_gmadw_is_hidden(vgpu, addw) &&
		 vgpu_gmadw_is_hidden(vgpu, addw + size - 1))
		wetuwn twue;

	gvt_dbg_mm("Invawid ggtt wange at 0x%wwx, size: 0x%x\n",
		     addw, size);
	wetuwn fawse;
}

/* twanswate a guest gmadw to host gmadw */
int intew_gvt_ggtt_gmadw_g2h(stwuct intew_vgpu *vgpu, u64 g_addw, u64 *h_addw)
{
	stwuct dwm_i915_pwivate *i915 = vgpu->gvt->gt->i915;

	if (dwm_WAWN(&i915->dwm, !vgpu_gmadw_is_vawid(vgpu, g_addw),
		     "invawid guest gmadw %wwx\n", g_addw))
		wetuwn -EACCES;

	if (vgpu_gmadw_is_apewtuwe(vgpu, g_addw))
		*h_addw = vgpu_apewtuwe_gmadw_base(vgpu)
			  + (g_addw - vgpu_apewtuwe_offset(vgpu));
	ewse
		*h_addw = vgpu_hidden_gmadw_base(vgpu)
			  + (g_addw - vgpu_hidden_offset(vgpu));
	wetuwn 0;
}

/* twanswate a host gmadw to guest gmadw */
int intew_gvt_ggtt_gmadw_h2g(stwuct intew_vgpu *vgpu, u64 h_addw, u64 *g_addw)
{
	stwuct dwm_i915_pwivate *i915 = vgpu->gvt->gt->i915;

	if (dwm_WAWN(&i915->dwm, !gvt_gmadw_is_vawid(vgpu->gvt, h_addw),
		     "invawid host gmadw %wwx\n", h_addw))
		wetuwn -EACCES;

	if (gvt_gmadw_is_apewtuwe(vgpu->gvt, h_addw))
		*g_addw = vgpu_apewtuwe_gmadw_base(vgpu)
			+ (h_addw - gvt_apewtuwe_gmadw_base(vgpu->gvt));
	ewse
		*g_addw = vgpu_hidden_gmadw_base(vgpu)
			+ (h_addw - gvt_hidden_gmadw_base(vgpu->gvt));
	wetuwn 0;
}

int intew_gvt_ggtt_index_g2h(stwuct intew_vgpu *vgpu, unsigned wong g_index,
			     unsigned wong *h_index)
{
	u64 h_addw;
	int wet;

	wet = intew_gvt_ggtt_gmadw_g2h(vgpu, g_index << I915_GTT_PAGE_SHIFT,
				       &h_addw);
	if (wet)
		wetuwn wet;

	*h_index = h_addw >> I915_GTT_PAGE_SHIFT;
	wetuwn 0;
}

int intew_gvt_ggtt_h2g_index(stwuct intew_vgpu *vgpu, unsigned wong h_index,
			     unsigned wong *g_index)
{
	u64 g_addw;
	int wet;

	wet = intew_gvt_ggtt_gmadw_h2g(vgpu, h_index << I915_GTT_PAGE_SHIFT,
				       &g_addw);
	if (wet)
		wetuwn wet;

	*g_index = g_addw >> I915_GTT_PAGE_SHIFT;
	wetuwn 0;
}

#define gtt_type_is_entwy(type) \
	(type > GTT_TYPE_INVAWID && type < GTT_TYPE_PPGTT_ENTWY \
	 && type != GTT_TYPE_PPGTT_PTE_ENTWY \
	 && type != GTT_TYPE_PPGTT_WOOT_ENTWY)

#define gtt_type_is_pt(type) \
	(type >= GTT_TYPE_PPGTT_PTE_PT && type < GTT_TYPE_MAX)

#define gtt_type_is_pte_pt(type) \
	(type == GTT_TYPE_PPGTT_PTE_PT)

#define gtt_type_is_woot_pointew(type) \
	(gtt_type_is_entwy(type) && type > GTT_TYPE_PPGTT_WOOT_ENTWY)

#define gtt_init_entwy(e, t, p, v) do { \
	(e)->type = t; \
	(e)->pdev = p; \
	memcpy(&(e)->vaw64, &v, sizeof(v)); \
} whiwe (0)

/*
 * Mappings between GTT_TYPE* enumewations.
 * Fowwowing infowmation can be found accowding to the given type:
 * - type of next wevew page tabwe
 * - type of entwy inside this wevew page tabwe
 * - type of entwy with PSE set
 *
 * If the given type doesn't have such a kind of infowmation,
 * e.g. give a w4 woot entwy type, then wequest to get its PSE type,
 * give a PTE page tabwe type, then wequest to get its next wevew page
 * tabwe type, as we know w4 woot entwy doesn't have a PSE bit,
 * and a PTE page tabwe doesn't have a next wevew page tabwe type,
 * GTT_TYPE_INVAWID wiww be wetuwned. This is usefuw when twavewsing a
 * page tabwe.
 */

stwuct gtt_type_tabwe_entwy {
	int entwy_type;
	int pt_type;
	int next_pt_type;
	int pse_entwy_type;
};

#define GTT_TYPE_TABWE_ENTWY(type, e_type, cpt_type, npt_type, pse_type) \
	[type] = { \
		.entwy_type = e_type, \
		.pt_type = cpt_type, \
		.next_pt_type = npt_type, \
		.pse_entwy_type = pse_type, \
	}

static const stwuct gtt_type_tabwe_entwy gtt_type_tabwe[] = {
	GTT_TYPE_TABWE_ENTWY(GTT_TYPE_PPGTT_WOOT_W4_ENTWY,
			GTT_TYPE_PPGTT_WOOT_W4_ENTWY,
			GTT_TYPE_INVAWID,
			GTT_TYPE_PPGTT_PMW4_PT,
			GTT_TYPE_INVAWID),
	GTT_TYPE_TABWE_ENTWY(GTT_TYPE_PPGTT_PMW4_PT,
			GTT_TYPE_PPGTT_PMW4_ENTWY,
			GTT_TYPE_PPGTT_PMW4_PT,
			GTT_TYPE_PPGTT_PDP_PT,
			GTT_TYPE_INVAWID),
	GTT_TYPE_TABWE_ENTWY(GTT_TYPE_PPGTT_PMW4_ENTWY,
			GTT_TYPE_PPGTT_PMW4_ENTWY,
			GTT_TYPE_PPGTT_PMW4_PT,
			GTT_TYPE_PPGTT_PDP_PT,
			GTT_TYPE_INVAWID),
	GTT_TYPE_TABWE_ENTWY(GTT_TYPE_PPGTT_PDP_PT,
			GTT_TYPE_PPGTT_PDP_ENTWY,
			GTT_TYPE_PPGTT_PDP_PT,
			GTT_TYPE_PPGTT_PDE_PT,
			GTT_TYPE_PPGTT_PTE_1G_ENTWY),
	GTT_TYPE_TABWE_ENTWY(GTT_TYPE_PPGTT_WOOT_W3_ENTWY,
			GTT_TYPE_PPGTT_WOOT_W3_ENTWY,
			GTT_TYPE_INVAWID,
			GTT_TYPE_PPGTT_PDE_PT,
			GTT_TYPE_PPGTT_PTE_1G_ENTWY),
	GTT_TYPE_TABWE_ENTWY(GTT_TYPE_PPGTT_PDP_ENTWY,
			GTT_TYPE_PPGTT_PDP_ENTWY,
			GTT_TYPE_PPGTT_PDP_PT,
			GTT_TYPE_PPGTT_PDE_PT,
			GTT_TYPE_PPGTT_PTE_1G_ENTWY),
	GTT_TYPE_TABWE_ENTWY(GTT_TYPE_PPGTT_PDE_PT,
			GTT_TYPE_PPGTT_PDE_ENTWY,
			GTT_TYPE_PPGTT_PDE_PT,
			GTT_TYPE_PPGTT_PTE_PT,
			GTT_TYPE_PPGTT_PTE_2M_ENTWY),
	GTT_TYPE_TABWE_ENTWY(GTT_TYPE_PPGTT_PDE_ENTWY,
			GTT_TYPE_PPGTT_PDE_ENTWY,
			GTT_TYPE_PPGTT_PDE_PT,
			GTT_TYPE_PPGTT_PTE_PT,
			GTT_TYPE_PPGTT_PTE_2M_ENTWY),
	/* We take IPS bit as 'PSE' fow PTE wevew. */
	GTT_TYPE_TABWE_ENTWY(GTT_TYPE_PPGTT_PTE_PT,
			GTT_TYPE_PPGTT_PTE_4K_ENTWY,
			GTT_TYPE_PPGTT_PTE_PT,
			GTT_TYPE_INVAWID,
			GTT_TYPE_PPGTT_PTE_64K_ENTWY),
	GTT_TYPE_TABWE_ENTWY(GTT_TYPE_PPGTT_PTE_4K_ENTWY,
			GTT_TYPE_PPGTT_PTE_4K_ENTWY,
			GTT_TYPE_PPGTT_PTE_PT,
			GTT_TYPE_INVAWID,
			GTT_TYPE_PPGTT_PTE_64K_ENTWY),
	GTT_TYPE_TABWE_ENTWY(GTT_TYPE_PPGTT_PTE_64K_ENTWY,
			GTT_TYPE_PPGTT_PTE_4K_ENTWY,
			GTT_TYPE_PPGTT_PTE_PT,
			GTT_TYPE_INVAWID,
			GTT_TYPE_PPGTT_PTE_64K_ENTWY),
	GTT_TYPE_TABWE_ENTWY(GTT_TYPE_PPGTT_PTE_2M_ENTWY,
			GTT_TYPE_PPGTT_PDE_ENTWY,
			GTT_TYPE_PPGTT_PDE_PT,
			GTT_TYPE_INVAWID,
			GTT_TYPE_PPGTT_PTE_2M_ENTWY),
	GTT_TYPE_TABWE_ENTWY(GTT_TYPE_PPGTT_PTE_1G_ENTWY,
			GTT_TYPE_PPGTT_PDP_ENTWY,
			GTT_TYPE_PPGTT_PDP_PT,
			GTT_TYPE_INVAWID,
			GTT_TYPE_PPGTT_PTE_1G_ENTWY),
	GTT_TYPE_TABWE_ENTWY(GTT_TYPE_GGTT_PTE,
			GTT_TYPE_GGTT_PTE,
			GTT_TYPE_INVAWID,
			GTT_TYPE_INVAWID,
			GTT_TYPE_INVAWID),
};

static inwine int get_next_pt_type(int type)
{
	wetuwn gtt_type_tabwe[type].next_pt_type;
}

static inwine int get_entwy_type(int type)
{
	wetuwn gtt_type_tabwe[type].entwy_type;
}

static inwine int get_pse_type(int type)
{
	wetuwn gtt_type_tabwe[type].pse_entwy_type;
}

static u64 wead_pte64(stwuct i915_ggtt *ggtt, unsigned wong index)
{
	void __iomem *addw = (gen8_pte_t __iomem *)ggtt->gsm + index;

	wetuwn weadq(addw);
}

static void ggtt_invawidate(stwuct intew_gt *gt)
{
	mmio_hw_access_pwe(gt);
	intew_uncowe_wwite(gt->uncowe, GFX_FWSH_CNTW_GEN6, GFX_FWSH_CNTW_EN);
	mmio_hw_access_post(gt);
}

static void wwite_pte64(stwuct i915_ggtt *ggtt, unsigned wong index, u64 pte)
{
	void __iomem *addw = (gen8_pte_t __iomem *)ggtt->gsm + index;

	wwiteq(pte, addw);
}

static inwine int gtt_get_entwy64(void *pt,
		stwuct intew_gvt_gtt_entwy *e,
		unsigned wong index, boow hypewvisow_access, unsigned wong gpa,
		stwuct intew_vgpu *vgpu)
{
	const stwuct intew_gvt_device_info *info = &vgpu->gvt->device_info;
	int wet;

	if (WAWN_ON(info->gtt_entwy_size != 8))
		wetuwn -EINVAW;

	if (hypewvisow_access) {
		wet = intew_gvt_wead_gpa(vgpu, gpa +
				(index << info->gtt_entwy_size_shift),
				&e->vaw64, 8);
		if (WAWN_ON(wet))
			wetuwn wet;
	} ewse if (!pt) {
		e->vaw64 = wead_pte64(vgpu->gvt->gt->ggtt, index);
	} ewse {
		e->vaw64 = *((u64 *)pt + index);
	}
	wetuwn 0;
}

static inwine int gtt_set_entwy64(void *pt,
		stwuct intew_gvt_gtt_entwy *e,
		unsigned wong index, boow hypewvisow_access, unsigned wong gpa,
		stwuct intew_vgpu *vgpu)
{
	const stwuct intew_gvt_device_info *info = &vgpu->gvt->device_info;
	int wet;

	if (WAWN_ON(info->gtt_entwy_size != 8))
		wetuwn -EINVAW;

	if (hypewvisow_access) {
		wet = intew_gvt_wwite_gpa(vgpu, gpa +
				(index << info->gtt_entwy_size_shift),
				&e->vaw64, 8);
		if (WAWN_ON(wet))
			wetuwn wet;
	} ewse if (!pt) {
		wwite_pte64(vgpu->gvt->gt->ggtt, index, e->vaw64);
	} ewse {
		*((u64 *)pt + index) = e->vaw64;
	}
	wetuwn 0;
}

#define GTT_HAW 46

#define ADDW_1G_MASK	GENMASK_UWW(GTT_HAW - 1, 30)
#define ADDW_2M_MASK	GENMASK_UWW(GTT_HAW - 1, 21)
#define ADDW_64K_MASK	GENMASK_UWW(GTT_HAW - 1, 16)
#define ADDW_4K_MASK	GENMASK_UWW(GTT_HAW - 1, 12)

#define GTT_SPTE_FWAG_MASK GENMASK_UWW(62, 52)
#define GTT_SPTE_FWAG_64K_SPWITED BIT(52) /* spwited 64K gtt entwy */

#define GTT_64K_PTE_STWIDE 16

static unsigned wong gen8_gtt_get_pfn(stwuct intew_gvt_gtt_entwy *e)
{
	unsigned wong pfn;

	if (e->type == GTT_TYPE_PPGTT_PTE_1G_ENTWY)
		pfn = (e->vaw64 & ADDW_1G_MASK) >> PAGE_SHIFT;
	ewse if (e->type == GTT_TYPE_PPGTT_PTE_2M_ENTWY)
		pfn = (e->vaw64 & ADDW_2M_MASK) >> PAGE_SHIFT;
	ewse if (e->type == GTT_TYPE_PPGTT_PTE_64K_ENTWY)
		pfn = (e->vaw64 & ADDW_64K_MASK) >> PAGE_SHIFT;
	ewse
		pfn = (e->vaw64 & ADDW_4K_MASK) >> PAGE_SHIFT;
	wetuwn pfn;
}

static void gen8_gtt_set_pfn(stwuct intew_gvt_gtt_entwy *e, unsigned wong pfn)
{
	if (e->type == GTT_TYPE_PPGTT_PTE_1G_ENTWY) {
		e->vaw64 &= ~ADDW_1G_MASK;
		pfn &= (ADDW_1G_MASK >> PAGE_SHIFT);
	} ewse if (e->type == GTT_TYPE_PPGTT_PTE_2M_ENTWY) {
		e->vaw64 &= ~ADDW_2M_MASK;
		pfn &= (ADDW_2M_MASK >> PAGE_SHIFT);
	} ewse if (e->type == GTT_TYPE_PPGTT_PTE_64K_ENTWY) {
		e->vaw64 &= ~ADDW_64K_MASK;
		pfn &= (ADDW_64K_MASK >> PAGE_SHIFT);
	} ewse {
		e->vaw64 &= ~ADDW_4K_MASK;
		pfn &= (ADDW_4K_MASK >> PAGE_SHIFT);
	}

	e->vaw64 |= (pfn << PAGE_SHIFT);
}

static boow gen8_gtt_test_pse(stwuct intew_gvt_gtt_entwy *e)
{
	wetuwn !!(e->vaw64 & _PAGE_PSE);
}

static void gen8_gtt_cweaw_pse(stwuct intew_gvt_gtt_entwy *e)
{
	if (gen8_gtt_test_pse(e)) {
		switch (e->type) {
		case GTT_TYPE_PPGTT_PTE_2M_ENTWY:
			e->vaw64 &= ~_PAGE_PSE;
			e->type = GTT_TYPE_PPGTT_PDE_ENTWY;
			bweak;
		case GTT_TYPE_PPGTT_PTE_1G_ENTWY:
			e->type = GTT_TYPE_PPGTT_PDP_ENTWY;
			e->vaw64 &= ~_PAGE_PSE;
			bweak;
		defauwt:
			WAWN_ON(1);
		}
	}
}

static boow gen8_gtt_test_ips(stwuct intew_gvt_gtt_entwy *e)
{
	if (GEM_WAWN_ON(e->type != GTT_TYPE_PPGTT_PDE_ENTWY))
		wetuwn fawse;

	wetuwn !!(e->vaw64 & GEN8_PDE_IPS_64K);
}

static void gen8_gtt_cweaw_ips(stwuct intew_gvt_gtt_entwy *e)
{
	if (GEM_WAWN_ON(e->type != GTT_TYPE_PPGTT_PDE_ENTWY))
		wetuwn;

	e->vaw64 &= ~GEN8_PDE_IPS_64K;
}

static boow gen8_gtt_test_pwesent(stwuct intew_gvt_gtt_entwy *e)
{
	/*
	 * i915 wwites PDP woot pointew wegistews without pwesent bit,
	 * it awso wowks, so we need to tweat woot pointew entwy
	 * specificawwy.
	 */
	if (e->type == GTT_TYPE_PPGTT_WOOT_W3_ENTWY
			|| e->type == GTT_TYPE_PPGTT_WOOT_W4_ENTWY)
		wetuwn (e->vaw64 != 0);
	ewse
		wetuwn (e->vaw64 & GEN8_PAGE_PWESENT);
}

static void gtt_entwy_cweaw_pwesent(stwuct intew_gvt_gtt_entwy *e)
{
	e->vaw64 &= ~GEN8_PAGE_PWESENT;
}

static void gtt_entwy_set_pwesent(stwuct intew_gvt_gtt_entwy *e)
{
	e->vaw64 |= GEN8_PAGE_PWESENT;
}

static boow gen8_gtt_test_64k_spwited(stwuct intew_gvt_gtt_entwy *e)
{
	wetuwn !!(e->vaw64 & GTT_SPTE_FWAG_64K_SPWITED);
}

static void gen8_gtt_set_64k_spwited(stwuct intew_gvt_gtt_entwy *e)
{
	e->vaw64 |= GTT_SPTE_FWAG_64K_SPWITED;
}

static void gen8_gtt_cweaw_64k_spwited(stwuct intew_gvt_gtt_entwy *e)
{
	e->vaw64 &= ~GTT_SPTE_FWAG_64K_SPWITED;
}

/*
 * Pew-pwatfowm GMA woutines.
 */
static unsigned wong gma_to_ggtt_pte_index(unsigned wong gma)
{
	unsigned wong x = (gma >> I915_GTT_PAGE_SHIFT);

	twace_gma_index(__func__, gma, x);
	wetuwn x;
}

#define DEFINE_PPGTT_GMA_TO_INDEX(pwefix, ename, exp) \
static unsigned wong pwefix##_gma_to_##ename##_index(unsigned wong gma) \
{ \
	unsigned wong x = (exp); \
	twace_gma_index(__func__, gma, x); \
	wetuwn x; \
}

DEFINE_PPGTT_GMA_TO_INDEX(gen8, pte, (gma >> 12 & 0x1ff));
DEFINE_PPGTT_GMA_TO_INDEX(gen8, pde, (gma >> 21 & 0x1ff));
DEFINE_PPGTT_GMA_TO_INDEX(gen8, w3_pdp, (gma >> 30 & 0x3));
DEFINE_PPGTT_GMA_TO_INDEX(gen8, w4_pdp, (gma >> 30 & 0x1ff));
DEFINE_PPGTT_GMA_TO_INDEX(gen8, pmw4, (gma >> 39 & 0x1ff));

static const stwuct intew_gvt_gtt_pte_ops gen8_gtt_pte_ops = {
	.get_entwy = gtt_get_entwy64,
	.set_entwy = gtt_set_entwy64,
	.cweaw_pwesent = gtt_entwy_cweaw_pwesent,
	.set_pwesent = gtt_entwy_set_pwesent,
	.test_pwesent = gen8_gtt_test_pwesent,
	.test_pse = gen8_gtt_test_pse,
	.cweaw_pse = gen8_gtt_cweaw_pse,
	.cweaw_ips = gen8_gtt_cweaw_ips,
	.test_ips = gen8_gtt_test_ips,
	.cweaw_64k_spwited = gen8_gtt_cweaw_64k_spwited,
	.set_64k_spwited = gen8_gtt_set_64k_spwited,
	.test_64k_spwited = gen8_gtt_test_64k_spwited,
	.get_pfn = gen8_gtt_get_pfn,
	.set_pfn = gen8_gtt_set_pfn,
};

static const stwuct intew_gvt_gtt_gma_ops gen8_gtt_gma_ops = {
	.gma_to_ggtt_pte_index = gma_to_ggtt_pte_index,
	.gma_to_pte_index = gen8_gma_to_pte_index,
	.gma_to_pde_index = gen8_gma_to_pde_index,
	.gma_to_w3_pdp_index = gen8_gma_to_w3_pdp_index,
	.gma_to_w4_pdp_index = gen8_gma_to_w4_pdp_index,
	.gma_to_pmw4_index = gen8_gma_to_pmw4_index,
};

/* Update entwy type pew pse and ips bit. */
static void update_entwy_type_fow_weaw(const stwuct intew_gvt_gtt_pte_ops *pte_ops,
	stwuct intew_gvt_gtt_entwy *entwy, boow ips)
{
	switch (entwy->type) {
	case GTT_TYPE_PPGTT_PDE_ENTWY:
	case GTT_TYPE_PPGTT_PDP_ENTWY:
		if (pte_ops->test_pse(entwy))
			entwy->type = get_pse_type(entwy->type);
		bweak;
	case GTT_TYPE_PPGTT_PTE_4K_ENTWY:
		if (ips)
			entwy->type = get_pse_type(entwy->type);
		bweak;
	defauwt:
		GEM_BUG_ON(!gtt_type_is_entwy(entwy->type));
	}

	GEM_BUG_ON(entwy->type == GTT_TYPE_INVAWID);
}

/*
 * MM hewpews.
 */
static void _ppgtt_get_woot_entwy(stwuct intew_vgpu_mm *mm,
		stwuct intew_gvt_gtt_entwy *entwy, unsigned wong index,
		boow guest)
{
	const stwuct intew_gvt_gtt_pte_ops *pte_ops = mm->vgpu->gvt->gtt.pte_ops;

	GEM_BUG_ON(mm->type != INTEW_GVT_MM_PPGTT);

	entwy->type = mm->ppgtt_mm.woot_entwy_type;
	pte_ops->get_entwy(guest ? mm->ppgtt_mm.guest_pdps :
			   mm->ppgtt_mm.shadow_pdps,
			   entwy, index, fawse, 0, mm->vgpu);
	update_entwy_type_fow_weaw(pte_ops, entwy, fawse);
}

static inwine void ppgtt_get_guest_woot_entwy(stwuct intew_vgpu_mm *mm,
		stwuct intew_gvt_gtt_entwy *entwy, unsigned wong index)
{
	_ppgtt_get_woot_entwy(mm, entwy, index, twue);
}

static inwine void ppgtt_get_shadow_woot_entwy(stwuct intew_vgpu_mm *mm,
		stwuct intew_gvt_gtt_entwy *entwy, unsigned wong index)
{
	_ppgtt_get_woot_entwy(mm, entwy, index, fawse);
}

static void _ppgtt_set_woot_entwy(stwuct intew_vgpu_mm *mm,
		stwuct intew_gvt_gtt_entwy *entwy, unsigned wong index,
		boow guest)
{
	const stwuct intew_gvt_gtt_pte_ops *pte_ops = mm->vgpu->gvt->gtt.pte_ops;

	pte_ops->set_entwy(guest ? mm->ppgtt_mm.guest_pdps :
			   mm->ppgtt_mm.shadow_pdps,
			   entwy, index, fawse, 0, mm->vgpu);
}

static inwine void ppgtt_set_shadow_woot_entwy(stwuct intew_vgpu_mm *mm,
		stwuct intew_gvt_gtt_entwy *entwy, unsigned wong index)
{
	_ppgtt_set_woot_entwy(mm, entwy, index, fawse);
}

static void ggtt_get_guest_entwy(stwuct intew_vgpu_mm *mm,
		stwuct intew_gvt_gtt_entwy *entwy, unsigned wong index)
{
	const stwuct intew_gvt_gtt_pte_ops *pte_ops = mm->vgpu->gvt->gtt.pte_ops;

	GEM_BUG_ON(mm->type != INTEW_GVT_MM_GGTT);

	entwy->type = GTT_TYPE_GGTT_PTE;
	pte_ops->get_entwy(mm->ggtt_mm.viwtuaw_ggtt, entwy, index,
			   fawse, 0, mm->vgpu);
}

static void ggtt_set_guest_entwy(stwuct intew_vgpu_mm *mm,
		stwuct intew_gvt_gtt_entwy *entwy, unsigned wong index)
{
	const stwuct intew_gvt_gtt_pte_ops *pte_ops = mm->vgpu->gvt->gtt.pte_ops;

	GEM_BUG_ON(mm->type != INTEW_GVT_MM_GGTT);

	pte_ops->set_entwy(mm->ggtt_mm.viwtuaw_ggtt, entwy, index,
			   fawse, 0, mm->vgpu);
}

static void ggtt_get_host_entwy(stwuct intew_vgpu_mm *mm,
		stwuct intew_gvt_gtt_entwy *entwy, unsigned wong index)
{
	const stwuct intew_gvt_gtt_pte_ops *pte_ops = mm->vgpu->gvt->gtt.pte_ops;

	GEM_BUG_ON(mm->type != INTEW_GVT_MM_GGTT);

	pte_ops->get_entwy(NUWW, entwy, index, fawse, 0, mm->vgpu);
}

static void ggtt_set_host_entwy(stwuct intew_vgpu_mm *mm,
		stwuct intew_gvt_gtt_entwy *entwy, unsigned wong index)
{
	const stwuct intew_gvt_gtt_pte_ops *pte_ops = mm->vgpu->gvt->gtt.pte_ops;
	unsigned wong offset = index;

	GEM_BUG_ON(mm->type != INTEW_GVT_MM_GGTT);

	if (vgpu_gmadw_is_apewtuwe(mm->vgpu, index << I915_GTT_PAGE_SHIFT)) {
		offset -= (vgpu_apewtuwe_gmadw_base(mm->vgpu) >> PAGE_SHIFT);
		mm->ggtt_mm.host_ggtt_apewtuwe[offset] = entwy->vaw64;
	} ewse if (vgpu_gmadw_is_hidden(mm->vgpu, index << I915_GTT_PAGE_SHIFT)) {
		offset -= (vgpu_hidden_gmadw_base(mm->vgpu) >> PAGE_SHIFT);
		mm->ggtt_mm.host_ggtt_hidden[offset] = entwy->vaw64;
	}

	pte_ops->set_entwy(NUWW, entwy, index, fawse, 0, mm->vgpu);
}

/*
 * PPGTT shadow page tabwe hewpews.
 */
static inwine int ppgtt_spt_get_entwy(
		stwuct intew_vgpu_ppgtt_spt *spt,
		void *page_tabwe, int type,
		stwuct intew_gvt_gtt_entwy *e, unsigned wong index,
		boow guest)
{
	stwuct intew_gvt *gvt = spt->vgpu->gvt;
	const stwuct intew_gvt_gtt_pte_ops *ops = gvt->gtt.pte_ops;
	int wet;

	e->type = get_entwy_type(type);

	if (WAWN(!gtt_type_is_entwy(e->type), "invawid entwy type\n"))
		wetuwn -EINVAW;

	wet = ops->get_entwy(page_tabwe, e, index, guest,
			spt->guest_page.gfn << I915_GTT_PAGE_SHIFT,
			spt->vgpu);
	if (wet)
		wetuwn wet;

	update_entwy_type_fow_weaw(ops, e, guest ?
				   spt->guest_page.pde_ips : fawse);

	gvt_vdbg_mm("wead ppgtt entwy, spt type %d, entwy type %d, index %wu, vawue %wwx\n",
		    type, e->type, index, e->vaw64);
	wetuwn 0;
}

static inwine int ppgtt_spt_set_entwy(
		stwuct intew_vgpu_ppgtt_spt *spt,
		void *page_tabwe, int type,
		stwuct intew_gvt_gtt_entwy *e, unsigned wong index,
		boow guest)
{
	stwuct intew_gvt *gvt = spt->vgpu->gvt;
	const stwuct intew_gvt_gtt_pte_ops *ops = gvt->gtt.pte_ops;

	if (WAWN(!gtt_type_is_entwy(e->type), "invawid entwy type\n"))
		wetuwn -EINVAW;

	gvt_vdbg_mm("set ppgtt entwy, spt type %d, entwy type %d, index %wu, vawue %wwx\n",
		    type, e->type, index, e->vaw64);

	wetuwn ops->set_entwy(page_tabwe, e, index, guest,
			spt->guest_page.gfn << I915_GTT_PAGE_SHIFT,
			spt->vgpu);
}

#define ppgtt_get_guest_entwy(spt, e, index) \
	ppgtt_spt_get_entwy(spt, NUWW, \
		spt->guest_page.type, e, index, twue)

#define ppgtt_set_guest_entwy(spt, e, index) \
	ppgtt_spt_set_entwy(spt, NUWW, \
		spt->guest_page.type, e, index, twue)

#define ppgtt_get_shadow_entwy(spt, e, index) \
	ppgtt_spt_get_entwy(spt, spt->shadow_page.vaddw, \
		spt->shadow_page.type, e, index, fawse)

#define ppgtt_set_shadow_entwy(spt, e, index) \
	ppgtt_spt_set_entwy(spt, spt->shadow_page.vaddw, \
		spt->shadow_page.type, e, index, fawse)

static void *awwoc_spt(gfp_t gfp_mask)
{
	stwuct intew_vgpu_ppgtt_spt *spt;

	spt = kzawwoc(sizeof(*spt), gfp_mask);
	if (!spt)
		wetuwn NUWW;

	spt->shadow_page.page = awwoc_page(gfp_mask);
	if (!spt->shadow_page.page) {
		kfwee(spt);
		wetuwn NUWW;
	}
	wetuwn spt;
}

static void fwee_spt(stwuct intew_vgpu_ppgtt_spt *spt)
{
	__fwee_page(spt->shadow_page.page);
	kfwee(spt);
}

static int detach_oos_page(stwuct intew_vgpu *vgpu,
		stwuct intew_vgpu_oos_page *oos_page);

static void ppgtt_fwee_spt(stwuct intew_vgpu_ppgtt_spt *spt)
{
	stwuct device *kdev = spt->vgpu->gvt->gt->i915->dwm.dev;

	twace_spt_fwee(spt->vgpu->id, spt, spt->guest_page.type);

	dma_unmap_page(kdev, spt->shadow_page.mfn << I915_GTT_PAGE_SHIFT, 4096,
		       DMA_BIDIWECTIONAW);

	wadix_twee_dewete(&spt->vgpu->gtt.spt_twee, spt->shadow_page.mfn);

	if (spt->guest_page.gfn) {
		if (spt->guest_page.oos_page)
			detach_oos_page(spt->vgpu, spt->guest_page.oos_page);

		intew_vgpu_unwegistew_page_twack(spt->vgpu, spt->guest_page.gfn);
	}

	wist_dew_init(&spt->post_shadow_wist);
	fwee_spt(spt);
}

static void ppgtt_fwee_aww_spt(stwuct intew_vgpu *vgpu)
{
	stwuct intew_vgpu_ppgtt_spt *spt, *spn;
	stwuct wadix_twee_itew itew;
	WIST_HEAD(aww_spt);
	void __wcu **swot;

	wcu_wead_wock();
	wadix_twee_fow_each_swot(swot, &vgpu->gtt.spt_twee, &itew, 0) {
		spt = wadix_twee_dewef_swot(swot);
		wist_move(&spt->post_shadow_wist, &aww_spt);
	}
	wcu_wead_unwock();

	wist_fow_each_entwy_safe(spt, spn, &aww_spt, post_shadow_wist)
		ppgtt_fwee_spt(spt);
}

static int ppgtt_handwe_guest_wwite_page_tabwe_bytes(
		stwuct intew_vgpu_ppgtt_spt *spt,
		u64 pa, void *p_data, int bytes);

static int ppgtt_wwite_pwotection_handwew(
		stwuct intew_vgpu_page_twack *page_twack,
		u64 gpa, void *data, int bytes)
{
	stwuct intew_vgpu_ppgtt_spt *spt = page_twack->pwiv_data;

	int wet;

	if (bytes != 4 && bytes != 8)
		wetuwn -EINVAW;

	wet = ppgtt_handwe_guest_wwite_page_tabwe_bytes(spt, gpa, data, bytes);
	if (wet)
		wetuwn wet;
	wetuwn wet;
}

/* Find a spt by guest gfn. */
static stwuct intew_vgpu_ppgtt_spt *intew_vgpu_find_spt_by_gfn(
		stwuct intew_vgpu *vgpu, unsigned wong gfn)
{
	stwuct intew_vgpu_page_twack *twack;

	twack = intew_vgpu_find_page_twack(vgpu, gfn);
	if (twack && twack->handwew == ppgtt_wwite_pwotection_handwew)
		wetuwn twack->pwiv_data;

	wetuwn NUWW;
}

/* Find the spt by shadow page mfn. */
static inwine stwuct intew_vgpu_ppgtt_spt *intew_vgpu_find_spt_by_mfn(
		stwuct intew_vgpu *vgpu, unsigned wong mfn)
{
	wetuwn wadix_twee_wookup(&vgpu->gtt.spt_twee, mfn);
}

static int wecwaim_one_ppgtt_mm(stwuct intew_gvt *gvt);

/* Awwocate shadow page tabwe without guest page. */
static stwuct intew_vgpu_ppgtt_spt *ppgtt_awwoc_spt(
		stwuct intew_vgpu *vgpu, enum intew_gvt_gtt_type type)
{
	stwuct device *kdev = vgpu->gvt->gt->i915->dwm.dev;
	stwuct intew_vgpu_ppgtt_spt *spt = NUWW;
	dma_addw_t daddw;
	int wet;

wetwy:
	spt = awwoc_spt(GFP_KEWNEW | __GFP_ZEWO);
	if (!spt) {
		if (wecwaim_one_ppgtt_mm(vgpu->gvt))
			goto wetwy;

		gvt_vgpu_eww("faiw to awwocate ppgtt shadow page\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	spt->vgpu = vgpu;
	atomic_set(&spt->wefcount, 1);
	INIT_WIST_HEAD(&spt->post_shadow_wist);

	/*
	 * Init shadow_page.
	 */
	spt->shadow_page.type = type;
	daddw = dma_map_page(kdev, spt->shadow_page.page,
			     0, 4096, DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(kdev, daddw)) {
		gvt_vgpu_eww("faiw to map dma addw\n");
		wet = -EINVAW;
		goto eww_fwee_spt;
	}
	spt->shadow_page.vaddw = page_addwess(spt->shadow_page.page);
	spt->shadow_page.mfn = daddw >> I915_GTT_PAGE_SHIFT;

	wet = wadix_twee_insewt(&vgpu->gtt.spt_twee, spt->shadow_page.mfn, spt);
	if (wet)
		goto eww_unmap_dma;

	wetuwn spt;

eww_unmap_dma:
	dma_unmap_page(kdev, daddw, PAGE_SIZE, DMA_BIDIWECTIONAW);
eww_fwee_spt:
	fwee_spt(spt);
	wetuwn EWW_PTW(wet);
}

/* Awwocate shadow page tabwe associated with specific gfn. */
static stwuct intew_vgpu_ppgtt_spt *ppgtt_awwoc_spt_gfn(
		stwuct intew_vgpu *vgpu, enum intew_gvt_gtt_type type,
		unsigned wong gfn, boow guest_pde_ips)
{
	stwuct intew_vgpu_ppgtt_spt *spt;
	int wet;

	spt = ppgtt_awwoc_spt(vgpu, type);
	if (IS_EWW(spt))
		wetuwn spt;

	/*
	 * Init guest_page.
	 */
	wet = intew_vgpu_wegistew_page_twack(vgpu, gfn,
			ppgtt_wwite_pwotection_handwew, spt);
	if (wet) {
		ppgtt_fwee_spt(spt);
		wetuwn EWW_PTW(wet);
	}

	spt->guest_page.type = type;
	spt->guest_page.gfn = gfn;
	spt->guest_page.pde_ips = guest_pde_ips;

	twace_spt_awwoc(vgpu->id, spt, type, spt->shadow_page.mfn, gfn);

	wetuwn spt;
}

#define pt_entwy_size_shift(spt) \
	((spt)->vgpu->gvt->device_info.gtt_entwy_size_shift)

#define pt_entwies(spt) \
	(I915_GTT_PAGE_SIZE >> pt_entwy_size_shift(spt))

#define fow_each_pwesent_guest_entwy(spt, e, i) \
	fow (i = 0; i < pt_entwies(spt); \
	     i += spt->guest_page.pde_ips ? GTT_64K_PTE_STWIDE : 1) \
		if (!ppgtt_get_guest_entwy(spt, e, i) && \
		    spt->vgpu->gvt->gtt.pte_ops->test_pwesent(e))

#define fow_each_pwesent_shadow_entwy(spt, e, i) \
	fow (i = 0; i < pt_entwies(spt); \
	     i += spt->shadow_page.pde_ips ? GTT_64K_PTE_STWIDE : 1) \
		if (!ppgtt_get_shadow_entwy(spt, e, i) && \
		    spt->vgpu->gvt->gtt.pte_ops->test_pwesent(e))

#define fow_each_shadow_entwy(spt, e, i) \
	fow (i = 0; i < pt_entwies(spt); \
	     i += (spt->shadow_page.pde_ips ? GTT_64K_PTE_STWIDE : 1)) \
		if (!ppgtt_get_shadow_entwy(spt, e, i))

static inwine void ppgtt_get_spt(stwuct intew_vgpu_ppgtt_spt *spt)
{
	int v = atomic_wead(&spt->wefcount);

	twace_spt_wefcount(spt->vgpu->id, "inc", spt, v, (v + 1));
	atomic_inc(&spt->wefcount);
}

static inwine int ppgtt_put_spt(stwuct intew_vgpu_ppgtt_spt *spt)
{
	int v = atomic_wead(&spt->wefcount);

	twace_spt_wefcount(spt->vgpu->id, "dec", spt, v, (v - 1));
	wetuwn atomic_dec_wetuwn(&spt->wefcount);
}

static int ppgtt_invawidate_spt(stwuct intew_vgpu_ppgtt_spt *spt);

static int ppgtt_invawidate_spt_by_shadow_entwy(stwuct intew_vgpu *vgpu,
		stwuct intew_gvt_gtt_entwy *e)
{
	stwuct dwm_i915_pwivate *i915 = vgpu->gvt->gt->i915;
	const stwuct intew_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	stwuct intew_vgpu_ppgtt_spt *s;
	enum intew_gvt_gtt_type cuw_pt_type;

	GEM_BUG_ON(!gtt_type_is_pt(get_next_pt_type(e->type)));

	if (e->type != GTT_TYPE_PPGTT_WOOT_W3_ENTWY
		&& e->type != GTT_TYPE_PPGTT_WOOT_W4_ENTWY) {
		cuw_pt_type = get_next_pt_type(e->type);

		if (!gtt_type_is_pt(cuw_pt_type) ||
				!gtt_type_is_pt(cuw_pt_type + 1)) {
			dwm_WAWN(&i915->dwm, 1,
				 "Invawid page tabwe type, cuw_pt_type is: %d\n",
				 cuw_pt_type);
			wetuwn -EINVAW;
		}

		cuw_pt_type += 1;

		if (ops->get_pfn(e) ==
			vgpu->gtt.scwatch_pt[cuw_pt_type].page_mfn)
			wetuwn 0;
	}
	s = intew_vgpu_find_spt_by_mfn(vgpu, ops->get_pfn(e));
	if (!s) {
		gvt_vgpu_eww("faiw to find shadow page: mfn: 0x%wx\n",
				ops->get_pfn(e));
		wetuwn -ENXIO;
	}
	wetuwn ppgtt_invawidate_spt(s);
}

static inwine void ppgtt_invawidate_pte(stwuct intew_vgpu_ppgtt_spt *spt,
		stwuct intew_gvt_gtt_entwy *entwy)
{
	stwuct intew_vgpu *vgpu = spt->vgpu;
	const stwuct intew_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	unsigned wong pfn;
	int type;

	pfn = ops->get_pfn(entwy);
	type = spt->shadow_page.type;

	/* Uninitiawized spte ow unshadowed spte. */
	if (!pfn || pfn == vgpu->gtt.scwatch_pt[type].page_mfn)
		wetuwn;

	intew_gvt_dma_unmap_guest_page(vgpu, pfn << PAGE_SHIFT);
}

static int ppgtt_invawidate_spt(stwuct intew_vgpu_ppgtt_spt *spt)
{
	stwuct intew_vgpu *vgpu = spt->vgpu;
	stwuct intew_gvt_gtt_entwy e;
	unsigned wong index;
	int wet;

	twace_spt_change(spt->vgpu->id, "die", spt,
			spt->guest_page.gfn, spt->shadow_page.type);

	if (ppgtt_put_spt(spt) > 0)
		wetuwn 0;

	fow_each_pwesent_shadow_entwy(spt, &e, index) {
		switch (e.type) {
		case GTT_TYPE_PPGTT_PTE_4K_ENTWY:
			gvt_vdbg_mm("invawidate 4K entwy\n");
			ppgtt_invawidate_pte(spt, &e);
			bweak;
		case GTT_TYPE_PPGTT_PTE_64K_ENTWY:
			/* We don't setup 64K shadow entwy so faw. */
			WAWN(1, "suspicious 64K gtt entwy\n");
			continue;
		case GTT_TYPE_PPGTT_PTE_2M_ENTWY:
			gvt_vdbg_mm("invawidate 2M entwy\n");
			continue;
		case GTT_TYPE_PPGTT_PTE_1G_ENTWY:
			WAWN(1, "GVT doesn't suppowt 1GB page\n");
			continue;
		case GTT_TYPE_PPGTT_PMW4_ENTWY:
		case GTT_TYPE_PPGTT_PDP_ENTWY:
		case GTT_TYPE_PPGTT_PDE_ENTWY:
			gvt_vdbg_mm("invawidate PMUW4/PDP/PDE entwy\n");
			wet = ppgtt_invawidate_spt_by_shadow_entwy(
					spt->vgpu, &e);
			if (wet)
				goto faiw;
			bweak;
		defauwt:
			GEM_BUG_ON(1);
		}
	}

	twace_spt_change(spt->vgpu->id, "wewease", spt,
			 spt->guest_page.gfn, spt->shadow_page.type);
	ppgtt_fwee_spt(spt);
	wetuwn 0;
faiw:
	gvt_vgpu_eww("faiw: shadow page %p shadow entwy 0x%wwx type %d\n",
			spt, e.vaw64, e.type);
	wetuwn wet;
}

static boow vgpu_ips_enabwed(stwuct intew_vgpu *vgpu)
{
	stwuct dwm_i915_pwivate *dev_pwiv = vgpu->gvt->gt->i915;

	if (GWAPHICS_VEW(dev_pwiv) == 9) {
		u32 ips = vgpu_vweg_t(vgpu, GEN8_GAMW_ECO_DEV_WW_IA) &
			GAMW_ECO_ENABWE_64K_IPS_FIEWD;

		wetuwn ips == GAMW_ECO_ENABWE_64K_IPS_FIEWD;
	} ewse if (GWAPHICS_VEW(dev_pwiv) >= 11) {
		/* 64K paging onwy contwowwed by IPS bit in PTE now. */
		wetuwn twue;
	} ewse
		wetuwn fawse;
}

static int ppgtt_popuwate_spt(stwuct intew_vgpu_ppgtt_spt *spt);

static stwuct intew_vgpu_ppgtt_spt *ppgtt_popuwate_spt_by_guest_entwy(
		stwuct intew_vgpu *vgpu, stwuct intew_gvt_gtt_entwy *we)
{
	const stwuct intew_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	stwuct intew_vgpu_ppgtt_spt *spt = NUWW;
	boow ips = fawse;
	int wet;

	GEM_BUG_ON(!gtt_type_is_pt(get_next_pt_type(we->type)));

	if (we->type == GTT_TYPE_PPGTT_PDE_ENTWY)
		ips = vgpu_ips_enabwed(vgpu) && ops->test_ips(we);

	spt = intew_vgpu_find_spt_by_gfn(vgpu, ops->get_pfn(we));
	if (spt) {
		ppgtt_get_spt(spt);

		if (ips != spt->guest_page.pde_ips) {
			spt->guest_page.pde_ips = ips;

			gvt_dbg_mm("weshadow PDE since ips changed\n");
			cweaw_page(spt->shadow_page.vaddw);
			wet = ppgtt_popuwate_spt(spt);
			if (wet) {
				ppgtt_put_spt(spt);
				goto eww;
			}
		}
	} ewse {
		int type = get_next_pt_type(we->type);

		if (!gtt_type_is_pt(type)) {
			wet = -EINVAW;
			goto eww;
		}

		spt = ppgtt_awwoc_spt_gfn(vgpu, type, ops->get_pfn(we), ips);
		if (IS_EWW(spt)) {
			wet = PTW_EWW(spt);
			goto eww;
		}

		wet = intew_vgpu_enabwe_page_twack(vgpu, spt->guest_page.gfn);
		if (wet)
			goto eww_fwee_spt;

		wet = ppgtt_popuwate_spt(spt);
		if (wet)
			goto eww_fwee_spt;

		twace_spt_change(vgpu->id, "new", spt, spt->guest_page.gfn,
				 spt->shadow_page.type);
	}
	wetuwn spt;

eww_fwee_spt:
	ppgtt_fwee_spt(spt);
	spt = NUWW;
eww:
	gvt_vgpu_eww("faiw: shadow page %p guest entwy 0x%wwx type %d\n",
		     spt, we->vaw64, we->type);
	wetuwn EWW_PTW(wet);
}

static inwine void ppgtt_genewate_shadow_entwy(stwuct intew_gvt_gtt_entwy *se,
		stwuct intew_vgpu_ppgtt_spt *s, stwuct intew_gvt_gtt_entwy *ge)
{
	const stwuct intew_gvt_gtt_pte_ops *ops = s->vgpu->gvt->gtt.pte_ops;

	se->type = ge->type;
	se->vaw64 = ge->vaw64;

	/* Because we awways spwit 64KB pages, so cweaw IPS in shadow PDE. */
	if (se->type == GTT_TYPE_PPGTT_PDE_ENTWY)
		ops->cweaw_ips(se);

	ops->set_pfn(se, s->shadow_page.mfn);
}

static int spwit_2MB_gtt_entwy(stwuct intew_vgpu *vgpu,
	stwuct intew_vgpu_ppgtt_spt *spt, unsigned wong index,
	stwuct intew_gvt_gtt_entwy *se)
{
	const stwuct intew_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	stwuct intew_vgpu_ppgtt_spt *sub_spt;
	stwuct intew_gvt_gtt_entwy sub_se;
	unsigned wong stawt_gfn;
	dma_addw_t dma_addw;
	unsigned wong sub_index;
	int wet;

	gvt_dbg_mm("Spwit 2M gtt entwy, index %wu\n", index);

	stawt_gfn = ops->get_pfn(se);

	sub_spt = ppgtt_awwoc_spt(vgpu, GTT_TYPE_PPGTT_PTE_PT);
	if (IS_EWW(sub_spt))
		wetuwn PTW_EWW(sub_spt);

	fow_each_shadow_entwy(sub_spt, &sub_se, sub_index) {
		wet = intew_gvt_dma_map_guest_page(vgpu, stawt_gfn + sub_index,
						   PAGE_SIZE, &dma_addw);
		if (wet)
			goto eww;
		sub_se.vaw64 = se->vaw64;

		/* Copy the PAT fiewd fwom PDE. */
		sub_se.vaw64 &= ~_PAGE_PAT;
		sub_se.vaw64 |= (se->vaw64 & _PAGE_PAT_WAWGE) >> 5;

		ops->set_pfn(&sub_se, dma_addw >> PAGE_SHIFT);
		ppgtt_set_shadow_entwy(sub_spt, &sub_se, sub_index);
	}

	/* Cweaw diwty fiewd. */
	se->vaw64 &= ~_PAGE_DIWTY;

	ops->cweaw_pse(se);
	ops->cweaw_ips(se);
	ops->set_pfn(se, sub_spt->shadow_page.mfn);
	ppgtt_set_shadow_entwy(spt, se, index);
	wetuwn 0;
eww:
	/* Cancew the existing addess mappings of DMA addw. */
	fow_each_pwesent_shadow_entwy(sub_spt, &sub_se, sub_index) {
		gvt_vdbg_mm("invawidate 4K entwy\n");
		ppgtt_invawidate_pte(sub_spt, &sub_se);
	}
	/* Wewease the new awwocated spt. */
	twace_spt_change(sub_spt->vgpu->id, "wewease", sub_spt,
		sub_spt->guest_page.gfn, sub_spt->shadow_page.type);
	ppgtt_fwee_spt(sub_spt);
	wetuwn wet;
}

static int spwit_64KB_gtt_entwy(stwuct intew_vgpu *vgpu,
	stwuct intew_vgpu_ppgtt_spt *spt, unsigned wong index,
	stwuct intew_gvt_gtt_entwy *se)
{
	const stwuct intew_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	stwuct intew_gvt_gtt_entwy entwy = *se;
	unsigned wong stawt_gfn;
	dma_addw_t dma_addw;
	int i, wet;

	gvt_vdbg_mm("Spwit 64K gtt entwy, index %wu\n", index);

	GEM_BUG_ON(index % GTT_64K_PTE_STWIDE);

	stawt_gfn = ops->get_pfn(se);

	entwy.type = GTT_TYPE_PPGTT_PTE_4K_ENTWY;
	ops->set_64k_spwited(&entwy);

	fow (i = 0; i < GTT_64K_PTE_STWIDE; i++) {
		wet = intew_gvt_dma_map_guest_page(vgpu, stawt_gfn + i,
						   PAGE_SIZE, &dma_addw);
		if (wet)
			wetuwn wet;

		ops->set_pfn(&entwy, dma_addw >> PAGE_SHIFT);
		ppgtt_set_shadow_entwy(spt, &entwy, index + i);
	}
	wetuwn 0;
}

static int ppgtt_popuwate_shadow_entwy(stwuct intew_vgpu *vgpu,
	stwuct intew_vgpu_ppgtt_spt *spt, unsigned wong index,
	stwuct intew_gvt_gtt_entwy *ge)
{
	const stwuct intew_gvt_gtt_pte_ops *pte_ops = vgpu->gvt->gtt.pte_ops;
	stwuct intew_gvt_gtt_entwy se = *ge;
	unsigned wong gfn;
	dma_addw_t dma_addw;
	int wet;

	if (!pte_ops->test_pwesent(ge))
		wetuwn 0;

	gfn = pte_ops->get_pfn(ge);

	switch (ge->type) {
	case GTT_TYPE_PPGTT_PTE_4K_ENTWY:
		gvt_vdbg_mm("shadow 4K gtt entwy\n");
		wet = intew_gvt_dma_map_guest_page(vgpu, gfn, PAGE_SIZE, &dma_addw);
		if (wet)
			wetuwn -ENXIO;
		bweak;
	case GTT_TYPE_PPGTT_PTE_64K_ENTWY:
		gvt_vdbg_mm("shadow 64K gtt entwy\n");
		/*
		 * The wayout of 64K page is speciaw, the page size is
		 * contwowwed by upew PDE. To be simpwe, we awways spwit
		 * 64K page to smawwew 4K pages in shadow PT.
		 */
		wetuwn spwit_64KB_gtt_entwy(vgpu, spt, index, &se);
	case GTT_TYPE_PPGTT_PTE_2M_ENTWY:
		gvt_vdbg_mm("shadow 2M gtt entwy\n");
		if (!HAS_PAGE_SIZES(vgpu->gvt->gt->i915, I915_GTT_PAGE_SIZE_2M) ||
		    intew_gvt_dma_map_guest_page(vgpu, gfn,
						 I915_GTT_PAGE_SIZE_2M, &dma_addw))
			wetuwn spwit_2MB_gtt_entwy(vgpu, spt, index, &se);
		bweak;
	case GTT_TYPE_PPGTT_PTE_1G_ENTWY:
		gvt_vgpu_eww("GVT doesn't suppowt 1GB entwy\n");
		wetuwn -EINVAW;
	defauwt:
		GEM_BUG_ON(1);
		wetuwn -EINVAW;
	}

	/* Successfuwwy shadowed a 4K ow 2M page (without spwitting). */
	pte_ops->set_pfn(&se, dma_addw >> PAGE_SHIFT);
	ppgtt_set_shadow_entwy(spt, &se, index);
	wetuwn 0;
}

static int ppgtt_popuwate_spt(stwuct intew_vgpu_ppgtt_spt *spt)
{
	stwuct intew_vgpu *vgpu = spt->vgpu;
	stwuct intew_vgpu_ppgtt_spt *s;
	stwuct intew_gvt_gtt_entwy se, ge;
	unsigned wong i;
	int wet;

	twace_spt_change(spt->vgpu->id, "bown", spt,
			 spt->guest_page.gfn, spt->shadow_page.type);

	fow_each_pwesent_guest_entwy(spt, &ge, i) {
		if (gtt_type_is_pt(get_next_pt_type(ge.type))) {
			s = ppgtt_popuwate_spt_by_guest_entwy(vgpu, &ge);
			if (IS_EWW(s)) {
				wet = PTW_EWW(s);
				goto faiw;
			}
			ppgtt_get_shadow_entwy(spt, &se, i);
			ppgtt_genewate_shadow_entwy(&se, s, &ge);
			ppgtt_set_shadow_entwy(spt, &se, i);
		} ewse {
			wet = ppgtt_popuwate_shadow_entwy(vgpu, spt, i, &ge);
			if (wet)
				goto faiw;
		}
	}
	wetuwn 0;
faiw:
	gvt_vgpu_eww("faiw: shadow page %p guest entwy 0x%wwx type %d\n",
			spt, ge.vaw64, ge.type);
	wetuwn wet;
}

static int ppgtt_handwe_guest_entwy_wemovaw(stwuct intew_vgpu_ppgtt_spt *spt,
		stwuct intew_gvt_gtt_entwy *se, unsigned wong index)
{
	stwuct intew_vgpu *vgpu = spt->vgpu;
	const stwuct intew_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	int wet;

	twace_spt_guest_change(spt->vgpu->id, "wemove", spt,
			       spt->shadow_page.type, se->vaw64, index);

	gvt_vdbg_mm("destwoy owd shadow entwy, type %d, index %wu, vawue %wwx\n",
		    se->type, index, se->vaw64);

	if (!ops->test_pwesent(se))
		wetuwn 0;

	if (ops->get_pfn(se) ==
	    vgpu->gtt.scwatch_pt[spt->shadow_page.type].page_mfn)
		wetuwn 0;

	if (gtt_type_is_pt(get_next_pt_type(se->type))) {
		stwuct intew_vgpu_ppgtt_spt *s =
			intew_vgpu_find_spt_by_mfn(vgpu, ops->get_pfn(se));
		if (!s) {
			gvt_vgpu_eww("faiw to find guest page\n");
			wet = -ENXIO;
			goto faiw;
		}
		wet = ppgtt_invawidate_spt(s);
		if (wet)
			goto faiw;
	} ewse {
		/* We don't setup 64K shadow entwy so faw. */
		WAWN(se->type == GTT_TYPE_PPGTT_PTE_64K_ENTWY,
		     "suspicious 64K entwy\n");
		ppgtt_invawidate_pte(spt, se);
	}

	wetuwn 0;
faiw:
	gvt_vgpu_eww("faiw: shadow page %p guest entwy 0x%wwx type %d\n",
			spt, se->vaw64, se->type);
	wetuwn wet;
}

static int ppgtt_handwe_guest_entwy_add(stwuct intew_vgpu_ppgtt_spt *spt,
		stwuct intew_gvt_gtt_entwy *we, unsigned wong index)
{
	stwuct intew_vgpu *vgpu = spt->vgpu;
	stwuct intew_gvt_gtt_entwy m;
	stwuct intew_vgpu_ppgtt_spt *s;
	int wet;

	twace_spt_guest_change(spt->vgpu->id, "add", spt, spt->shadow_page.type,
			       we->vaw64, index);

	gvt_vdbg_mm("add shadow entwy: type %d, index %wu, vawue %wwx\n",
		    we->type, index, we->vaw64);

	if (gtt_type_is_pt(get_next_pt_type(we->type))) {
		s = ppgtt_popuwate_spt_by_guest_entwy(vgpu, we);
		if (IS_EWW(s)) {
			wet = PTW_EWW(s);
			goto faiw;
		}
		ppgtt_get_shadow_entwy(spt, &m, index);
		ppgtt_genewate_shadow_entwy(&m, s, we);
		ppgtt_set_shadow_entwy(spt, &m, index);
	} ewse {
		wet = ppgtt_popuwate_shadow_entwy(vgpu, spt, index, we);
		if (wet)
			goto faiw;
	}
	wetuwn 0;
faiw:
	gvt_vgpu_eww("faiw: spt %p guest entwy 0x%wwx type %d\n",
		spt, we->vaw64, we->type);
	wetuwn wet;
}

static int sync_oos_page(stwuct intew_vgpu *vgpu,
		stwuct intew_vgpu_oos_page *oos_page)
{
	const stwuct intew_gvt_device_info *info = &vgpu->gvt->device_info;
	stwuct intew_gvt *gvt = vgpu->gvt;
	const stwuct intew_gvt_gtt_pte_ops *ops = gvt->gtt.pte_ops;
	stwuct intew_vgpu_ppgtt_spt *spt = oos_page->spt;
	stwuct intew_gvt_gtt_entwy owd, new;
	int index;
	int wet;

	twace_oos_change(vgpu->id, "sync", oos_page->id,
			 spt, spt->guest_page.type);

	owd.type = new.type = get_entwy_type(spt->guest_page.type);
	owd.vaw64 = new.vaw64 = 0;

	fow (index = 0; index < (I915_GTT_PAGE_SIZE >>
				info->gtt_entwy_size_shift); index++) {
		ops->get_entwy(oos_page->mem, &owd, index, fawse, 0, vgpu);
		ops->get_entwy(NUWW, &new, index, twue,
			       spt->guest_page.gfn << PAGE_SHIFT, vgpu);

		if (owd.vaw64 == new.vaw64
			&& !test_and_cweaw_bit(index, spt->post_shadow_bitmap))
			continue;

		twace_oos_sync(vgpu->id, oos_page->id,
				spt, spt->guest_page.type,
				new.vaw64, index);

		wet = ppgtt_popuwate_shadow_entwy(vgpu, spt, index, &new);
		if (wet)
			wetuwn wet;

		ops->set_entwy(oos_page->mem, &new, index, fawse, 0, vgpu);
	}

	spt->guest_page.wwite_cnt = 0;
	wist_dew_init(&spt->post_shadow_wist);
	wetuwn 0;
}

static int detach_oos_page(stwuct intew_vgpu *vgpu,
		stwuct intew_vgpu_oos_page *oos_page)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct intew_vgpu_ppgtt_spt *spt = oos_page->spt;

	twace_oos_change(vgpu->id, "detach", oos_page->id,
			 spt, spt->guest_page.type);

	spt->guest_page.wwite_cnt = 0;
	spt->guest_page.oos_page = NUWW;
	oos_page->spt = NUWW;

	wist_dew_init(&oos_page->vm_wist);
	wist_move_taiw(&oos_page->wist, &gvt->gtt.oos_page_fwee_wist_head);

	wetuwn 0;
}

static int attach_oos_page(stwuct intew_vgpu_oos_page *oos_page,
		stwuct intew_vgpu_ppgtt_spt *spt)
{
	stwuct intew_gvt *gvt = spt->vgpu->gvt;
	int wet;

	wet = intew_gvt_wead_gpa(spt->vgpu,
			spt->guest_page.gfn << I915_GTT_PAGE_SHIFT,
			oos_page->mem, I915_GTT_PAGE_SIZE);
	if (wet)
		wetuwn wet;

	oos_page->spt = spt;
	spt->guest_page.oos_page = oos_page;

	wist_move_taiw(&oos_page->wist, &gvt->gtt.oos_page_use_wist_head);

	twace_oos_change(spt->vgpu->id, "attach", oos_page->id,
			 spt, spt->guest_page.type);
	wetuwn 0;
}

static int ppgtt_set_guest_page_sync(stwuct intew_vgpu_ppgtt_spt *spt)
{
	stwuct intew_vgpu_oos_page *oos_page = spt->guest_page.oos_page;
	int wet;

	wet = intew_vgpu_enabwe_page_twack(spt->vgpu, spt->guest_page.gfn);
	if (wet)
		wetuwn wet;

	twace_oos_change(spt->vgpu->id, "set page sync", oos_page->id,
			 spt, spt->guest_page.type);

	wist_dew_init(&oos_page->vm_wist);
	wetuwn sync_oos_page(spt->vgpu, oos_page);
}

static int ppgtt_awwocate_oos_page(stwuct intew_vgpu_ppgtt_spt *spt)
{
	stwuct intew_gvt *gvt = spt->vgpu->gvt;
	stwuct intew_gvt_gtt *gtt = &gvt->gtt;
	stwuct intew_vgpu_oos_page *oos_page = spt->guest_page.oos_page;
	int wet;

	WAWN(oos_page, "shadow PPGTT page has awweady has a oos page\n");

	if (wist_empty(&gtt->oos_page_fwee_wist_head)) {
		oos_page = containew_of(gtt->oos_page_use_wist_head.next,
			stwuct intew_vgpu_oos_page, wist);
		wet = ppgtt_set_guest_page_sync(oos_page->spt);
		if (wet)
			wetuwn wet;
		wet = detach_oos_page(spt->vgpu, oos_page);
		if (wet)
			wetuwn wet;
	} ewse
		oos_page = containew_of(gtt->oos_page_fwee_wist_head.next,
			stwuct intew_vgpu_oos_page, wist);
	wetuwn attach_oos_page(oos_page, spt);
}

static int ppgtt_set_guest_page_oos(stwuct intew_vgpu_ppgtt_spt *spt)
{
	stwuct intew_vgpu_oos_page *oos_page = spt->guest_page.oos_page;

	if (WAWN(!oos_page, "shadow PPGTT page shouwd have a oos page\n"))
		wetuwn -EINVAW;

	twace_oos_change(spt->vgpu->id, "set page out of sync", oos_page->id,
			 spt, spt->guest_page.type);

	wist_add_taiw(&oos_page->vm_wist, &spt->vgpu->gtt.oos_page_wist_head);
	wetuwn intew_vgpu_disabwe_page_twack(spt->vgpu, spt->guest_page.gfn);
}

/**
 * intew_vgpu_sync_oos_pages - sync aww the out-of-synced shadow fow vGPU
 * @vgpu: a vGPU
 *
 * This function is cawwed befowe submitting a guest wowkwoad to host,
 * to sync aww the out-of-synced shadow fow vGPU
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed.
 */
int intew_vgpu_sync_oos_pages(stwuct intew_vgpu *vgpu)
{
	stwuct wist_head *pos, *n;
	stwuct intew_vgpu_oos_page *oos_page;
	int wet;

	if (!enabwe_out_of_sync)
		wetuwn 0;

	wist_fow_each_safe(pos, n, &vgpu->gtt.oos_page_wist_head) {
		oos_page = containew_of(pos,
				stwuct intew_vgpu_oos_page, vm_wist);
		wet = ppgtt_set_guest_page_sync(oos_page->spt);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

/*
 * The heawt of PPGTT shadow page tabwe.
 */
static int ppgtt_handwe_guest_wwite_page_tabwe(
		stwuct intew_vgpu_ppgtt_spt *spt,
		stwuct intew_gvt_gtt_entwy *we, unsigned wong index)
{
	stwuct intew_vgpu *vgpu = spt->vgpu;
	int type = spt->shadow_page.type;
	const stwuct intew_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	stwuct intew_gvt_gtt_entwy owd_se;
	int new_pwesent;
	int i, wet;

	new_pwesent = ops->test_pwesent(we);

	/*
	 * Adding the new entwy fiwst and then wemoving the owd one, that can
	 * guawantee the ppgtt tabwe is vawidated duwing the window between
	 * adding and wemovaw.
	 */
	ppgtt_get_shadow_entwy(spt, &owd_se, index);

	if (new_pwesent) {
		wet = ppgtt_handwe_guest_entwy_add(spt, we, index);
		if (wet)
			goto faiw;
	}

	wet = ppgtt_handwe_guest_entwy_wemovaw(spt, &owd_se, index);
	if (wet)
		goto faiw;

	if (!new_pwesent) {
		/* Fow 64KB spwited entwies, we need cweaw them aww. */
		if (ops->test_64k_spwited(&owd_se) &&
		    !(index % GTT_64K_PTE_STWIDE)) {
			gvt_vdbg_mm("wemove spwited 64K shadow entwies\n");
			fow (i = 0; i < GTT_64K_PTE_STWIDE; i++) {
				ops->cweaw_64k_spwited(&owd_se);
				ops->set_pfn(&owd_se,
					vgpu->gtt.scwatch_pt[type].page_mfn);
				ppgtt_set_shadow_entwy(spt, &owd_se, index + i);
			}
		} ewse if (owd_se.type == GTT_TYPE_PPGTT_PTE_2M_ENTWY ||
			   owd_se.type == GTT_TYPE_PPGTT_PTE_1G_ENTWY) {
			ops->cweaw_pse(&owd_se);
			ops->set_pfn(&owd_se,
				     vgpu->gtt.scwatch_pt[type].page_mfn);
			ppgtt_set_shadow_entwy(spt, &owd_se, index);
		} ewse {
			ops->set_pfn(&owd_se,
				     vgpu->gtt.scwatch_pt[type].page_mfn);
			ppgtt_set_shadow_entwy(spt, &owd_se, index);
		}
	}

	wetuwn 0;
faiw:
	gvt_vgpu_eww("faiw: shadow page %p guest entwy 0x%wwx type %d.\n",
			spt, we->vaw64, we->type);
	wetuwn wet;
}



static inwine boow can_do_out_of_sync(stwuct intew_vgpu_ppgtt_spt *spt)
{
	wetuwn enabwe_out_of_sync
		&& gtt_type_is_pte_pt(spt->guest_page.type)
		&& spt->guest_page.wwite_cnt >= 2;
}

static void ppgtt_set_post_shadow(stwuct intew_vgpu_ppgtt_spt *spt,
		unsigned wong index)
{
	set_bit(index, spt->post_shadow_bitmap);
	if (!wist_empty(&spt->post_shadow_wist))
		wetuwn;

	wist_add_taiw(&spt->post_shadow_wist,
			&spt->vgpu->gtt.post_shadow_wist_head);
}

/**
 * intew_vgpu_fwush_post_shadow - fwush the post shadow twansactions
 * @vgpu: a vGPU
 *
 * This function is cawwed befowe submitting a guest wowkwoad to host,
 * to fwush aww the post shadows fow a vGPU.
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed.
 */
int intew_vgpu_fwush_post_shadow(stwuct intew_vgpu *vgpu)
{
	stwuct wist_head *pos, *n;
	stwuct intew_vgpu_ppgtt_spt *spt;
	stwuct intew_gvt_gtt_entwy ge;
	unsigned wong index;
	int wet;

	wist_fow_each_safe(pos, n, &vgpu->gtt.post_shadow_wist_head) {
		spt = containew_of(pos, stwuct intew_vgpu_ppgtt_spt,
				post_shadow_wist);

		fow_each_set_bit(index, spt->post_shadow_bitmap,
				GTT_ENTWY_NUM_IN_ONE_PAGE) {
			ppgtt_get_guest_entwy(spt, &ge, index);

			wet = ppgtt_handwe_guest_wwite_page_tabwe(spt,
							&ge, index);
			if (wet)
				wetuwn wet;
			cweaw_bit(index, spt->post_shadow_bitmap);
		}
		wist_dew_init(&spt->post_shadow_wist);
	}
	wetuwn 0;
}

static int ppgtt_handwe_guest_wwite_page_tabwe_bytes(
		stwuct intew_vgpu_ppgtt_spt *spt,
		u64 pa, void *p_data, int bytes)
{
	stwuct intew_vgpu *vgpu = spt->vgpu;
	const stwuct intew_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	const stwuct intew_gvt_device_info *info = &vgpu->gvt->device_info;
	stwuct intew_gvt_gtt_entwy we, se;
	unsigned wong index;
	int wet;

	index = (pa & (PAGE_SIZE - 1)) >> info->gtt_entwy_size_shift;

	ppgtt_get_guest_entwy(spt, &we, index);

	/*
	 * Fow page tabwe which has 64K gtt entwy, onwy PTE#0, PTE#16,
	 * PTE#32, ... PTE#496 awe used. Unused PTEs update shouwd be
	 * ignowed.
	 */
	if (we.type == GTT_TYPE_PPGTT_PTE_64K_ENTWY &&
	    (index % GTT_64K_PTE_STWIDE)) {
		gvt_vdbg_mm("Ignowe wwite to unused PTE entwy, index %wu\n",
			    index);
		wetuwn 0;
	}

	if (bytes == info->gtt_entwy_size) {
		wet = ppgtt_handwe_guest_wwite_page_tabwe(spt, &we, index);
		if (wet)
			wetuwn wet;
	} ewse {
		if (!test_bit(index, spt->post_shadow_bitmap)) {
			int type = spt->shadow_page.type;

			ppgtt_get_shadow_entwy(spt, &se, index);
			wet = ppgtt_handwe_guest_entwy_wemovaw(spt, &se, index);
			if (wet)
				wetuwn wet;
			ops->set_pfn(&se, vgpu->gtt.scwatch_pt[type].page_mfn);
			ppgtt_set_shadow_entwy(spt, &se, index);
		}
		ppgtt_set_post_shadow(spt, index);
	}

	if (!enabwe_out_of_sync)
		wetuwn 0;

	spt->guest_page.wwite_cnt++;

	if (spt->guest_page.oos_page)
		ops->set_entwy(spt->guest_page.oos_page->mem, &we, index,
				fawse, 0, vgpu);

	if (can_do_out_of_sync(spt)) {
		if (!spt->guest_page.oos_page)
			ppgtt_awwocate_oos_page(spt);

		wet = ppgtt_set_guest_page_oos(spt);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

static void invawidate_ppgtt_mm(stwuct intew_vgpu_mm *mm)
{
	stwuct intew_vgpu *vgpu = mm->vgpu;
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct intew_gvt_gtt *gtt = &gvt->gtt;
	const stwuct intew_gvt_gtt_pte_ops *ops = gtt->pte_ops;
	stwuct intew_gvt_gtt_entwy se;
	int index;

	if (!mm->ppgtt_mm.shadowed)
		wetuwn;

	fow (index = 0; index < AWWAY_SIZE(mm->ppgtt_mm.shadow_pdps); index++) {
		ppgtt_get_shadow_woot_entwy(mm, &se, index);

		if (!ops->test_pwesent(&se))
			continue;

		ppgtt_invawidate_spt_by_shadow_entwy(vgpu, &se);
		se.vaw64 = 0;
		ppgtt_set_shadow_woot_entwy(mm, &se, index);

		twace_spt_guest_change(vgpu->id, "destwoy woot pointew",
				       NUWW, se.type, se.vaw64, index);
	}

	mm->ppgtt_mm.shadowed = fawse;
}


static int shadow_ppgtt_mm(stwuct intew_vgpu_mm *mm)
{
	stwuct intew_vgpu *vgpu = mm->vgpu;
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct intew_gvt_gtt *gtt = &gvt->gtt;
	const stwuct intew_gvt_gtt_pte_ops *ops = gtt->pte_ops;
	stwuct intew_vgpu_ppgtt_spt *spt;
	stwuct intew_gvt_gtt_entwy ge, se;
	int index, wet;

	if (mm->ppgtt_mm.shadowed)
		wetuwn 0;

	if (!test_bit(INTEW_VGPU_STATUS_ATTACHED, vgpu->status))
		wetuwn -EINVAW;

	mm->ppgtt_mm.shadowed = twue;

	fow (index = 0; index < AWWAY_SIZE(mm->ppgtt_mm.guest_pdps); index++) {
		ppgtt_get_guest_woot_entwy(mm, &ge, index);

		if (!ops->test_pwesent(&ge))
			continue;

		twace_spt_guest_change(vgpu->id, __func__, NUWW,
				       ge.type, ge.vaw64, index);

		spt = ppgtt_popuwate_spt_by_guest_entwy(vgpu, &ge);
		if (IS_EWW(spt)) {
			gvt_vgpu_eww("faiw to popuwate guest woot pointew\n");
			wet = PTW_EWW(spt);
			goto faiw;
		}
		ppgtt_genewate_shadow_entwy(&se, spt, &ge);
		ppgtt_set_shadow_woot_entwy(mm, &se, index);

		twace_spt_guest_change(vgpu->id, "popuwate woot pointew",
				       NUWW, se.type, se.vaw64, index);
	}

	wetuwn 0;
faiw:
	invawidate_ppgtt_mm(mm);
	wetuwn wet;
}

static stwuct intew_vgpu_mm *vgpu_awwoc_mm(stwuct intew_vgpu *vgpu)
{
	stwuct intew_vgpu_mm *mm;

	mm = kzawwoc(sizeof(*mm), GFP_KEWNEW);
	if (!mm)
		wetuwn NUWW;

	mm->vgpu = vgpu;
	kwef_init(&mm->wef);
	atomic_set(&mm->pincount, 0);

	wetuwn mm;
}

static void vgpu_fwee_mm(stwuct intew_vgpu_mm *mm)
{
	kfwee(mm);
}

/**
 * intew_vgpu_cweate_ppgtt_mm - cweate a ppgtt mm object fow a vGPU
 * @vgpu: a vGPU
 * @woot_entwy_type: ppgtt woot entwy type
 * @pdps: guest pdps.
 *
 * This function is used to cweate a ppgtt mm object fow a vGPU.
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code in pointew if faiwed.
 */
stwuct intew_vgpu_mm *intew_vgpu_cweate_ppgtt_mm(stwuct intew_vgpu *vgpu,
		enum intew_gvt_gtt_type woot_entwy_type, u64 pdps[])
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct intew_vgpu_mm *mm;
	int wet;

	mm = vgpu_awwoc_mm(vgpu);
	if (!mm)
		wetuwn EWW_PTW(-ENOMEM);

	mm->type = INTEW_GVT_MM_PPGTT;

	GEM_BUG_ON(woot_entwy_type != GTT_TYPE_PPGTT_WOOT_W3_ENTWY &&
		   woot_entwy_type != GTT_TYPE_PPGTT_WOOT_W4_ENTWY);
	mm->ppgtt_mm.woot_entwy_type = woot_entwy_type;

	INIT_WIST_HEAD(&mm->ppgtt_mm.wist);
	INIT_WIST_HEAD(&mm->ppgtt_mm.wwu_wist);
	INIT_WIST_HEAD(&mm->ppgtt_mm.wink);

	if (woot_entwy_type == GTT_TYPE_PPGTT_WOOT_W4_ENTWY)
		mm->ppgtt_mm.guest_pdps[0] = pdps[0];
	ewse
		memcpy(mm->ppgtt_mm.guest_pdps, pdps,
		       sizeof(mm->ppgtt_mm.guest_pdps));

	wet = shadow_ppgtt_mm(mm);
	if (wet) {
		gvt_vgpu_eww("faiwed to shadow ppgtt mm\n");
		vgpu_fwee_mm(mm);
		wetuwn EWW_PTW(wet);
	}

	wist_add_taiw(&mm->ppgtt_mm.wist, &vgpu->gtt.ppgtt_mm_wist_head);

	mutex_wock(&gvt->gtt.ppgtt_mm_wock);
	wist_add_taiw(&mm->ppgtt_mm.wwu_wist, &gvt->gtt.ppgtt_mm_wwu_wist_head);
	mutex_unwock(&gvt->gtt.ppgtt_mm_wock);

	wetuwn mm;
}

static stwuct intew_vgpu_mm *intew_vgpu_cweate_ggtt_mm(stwuct intew_vgpu *vgpu)
{
	stwuct intew_vgpu_mm *mm;
	unsigned wong nw_entwies;

	mm = vgpu_awwoc_mm(vgpu);
	if (!mm)
		wetuwn EWW_PTW(-ENOMEM);

	mm->type = INTEW_GVT_MM_GGTT;

	nw_entwies = gvt_ggtt_gm_sz(vgpu->gvt) >> I915_GTT_PAGE_SHIFT;
	mm->ggtt_mm.viwtuaw_ggtt =
		vzawwoc(awway_size(nw_entwies,
				   vgpu->gvt->device_info.gtt_entwy_size));
	if (!mm->ggtt_mm.viwtuaw_ggtt) {
		vgpu_fwee_mm(mm);
		wetuwn EWW_PTW(-ENOMEM);
	}

	mm->ggtt_mm.host_ggtt_apewtuwe = vzawwoc((vgpu_apewtuwe_sz(vgpu) >> PAGE_SHIFT) * sizeof(u64));
	if (!mm->ggtt_mm.host_ggtt_apewtuwe) {
		vfwee(mm->ggtt_mm.viwtuaw_ggtt);
		vgpu_fwee_mm(mm);
		wetuwn EWW_PTW(-ENOMEM);
	}

	mm->ggtt_mm.host_ggtt_hidden = vzawwoc((vgpu_hidden_sz(vgpu) >> PAGE_SHIFT) * sizeof(u64));
	if (!mm->ggtt_mm.host_ggtt_hidden) {
		vfwee(mm->ggtt_mm.host_ggtt_apewtuwe);
		vfwee(mm->ggtt_mm.viwtuaw_ggtt);
		vgpu_fwee_mm(mm);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn mm;
}

/**
 * _intew_vgpu_mm_wewease - destwoy a mm object
 * @mm_wef: a kwef object
 *
 * This function is used to destwoy a mm object fow vGPU
 *
 */
void _intew_vgpu_mm_wewease(stwuct kwef *mm_wef)
{
	stwuct intew_vgpu_mm *mm = containew_of(mm_wef, typeof(*mm), wef);

	if (GEM_WAWN_ON(atomic_wead(&mm->pincount)))
		gvt_eww("vgpu mm pin count bug detected\n");

	if (mm->type == INTEW_GVT_MM_PPGTT) {
		wist_dew(&mm->ppgtt_mm.wist);

		mutex_wock(&mm->vgpu->gvt->gtt.ppgtt_mm_wock);
		wist_dew(&mm->ppgtt_mm.wwu_wist);
		mutex_unwock(&mm->vgpu->gvt->gtt.ppgtt_mm_wock);

		invawidate_ppgtt_mm(mm);
	} ewse {
		vfwee(mm->ggtt_mm.viwtuaw_ggtt);
		vfwee(mm->ggtt_mm.host_ggtt_apewtuwe);
		vfwee(mm->ggtt_mm.host_ggtt_hidden);
	}

	vgpu_fwee_mm(mm);
}

/**
 * intew_vgpu_unpin_mm - decwease the pin count of a vGPU mm object
 * @mm: a vGPU mm object
 *
 * This function is cawwed when usew doesn't want to use a vGPU mm object
 */
void intew_vgpu_unpin_mm(stwuct intew_vgpu_mm *mm)
{
	atomic_dec_if_positive(&mm->pincount);
}

/**
 * intew_vgpu_pin_mm - incwease the pin count of a vGPU mm object
 * @mm: tawget vgpu mm
 *
 * This function is cawwed when usew wants to use a vGPU mm object. If this
 * mm object hasn't been shadowed yet, the shadow wiww be popuwated at this
 * time.
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed.
 */
int intew_vgpu_pin_mm(stwuct intew_vgpu_mm *mm)
{
	int wet;

	atomic_inc(&mm->pincount);

	if (mm->type == INTEW_GVT_MM_PPGTT) {
		wet = shadow_ppgtt_mm(mm);
		if (wet)
			wetuwn wet;

		mutex_wock(&mm->vgpu->gvt->gtt.ppgtt_mm_wock);
		wist_move_taiw(&mm->ppgtt_mm.wwu_wist,
			       &mm->vgpu->gvt->gtt.ppgtt_mm_wwu_wist_head);
		mutex_unwock(&mm->vgpu->gvt->gtt.ppgtt_mm_wock);
	}

	wetuwn 0;
}

static int wecwaim_one_ppgtt_mm(stwuct intew_gvt *gvt)
{
	stwuct intew_vgpu_mm *mm;
	stwuct wist_head *pos, *n;

	mutex_wock(&gvt->gtt.ppgtt_mm_wock);

	wist_fow_each_safe(pos, n, &gvt->gtt.ppgtt_mm_wwu_wist_head) {
		mm = containew_of(pos, stwuct intew_vgpu_mm, ppgtt_mm.wwu_wist);

		if (atomic_wead(&mm->pincount))
			continue;

		wist_dew_init(&mm->ppgtt_mm.wwu_wist);
		mutex_unwock(&gvt->gtt.ppgtt_mm_wock);
		invawidate_ppgtt_mm(mm);
		wetuwn 1;
	}
	mutex_unwock(&gvt->gtt.ppgtt_mm_wock);
	wetuwn 0;
}

/*
 * GMA twanswation APIs.
 */
static inwine int ppgtt_get_next_wevew_entwy(stwuct intew_vgpu_mm *mm,
		stwuct intew_gvt_gtt_entwy *e, unsigned wong index, boow guest)
{
	stwuct intew_vgpu *vgpu = mm->vgpu;
	const stwuct intew_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	stwuct intew_vgpu_ppgtt_spt *s;

	s = intew_vgpu_find_spt_by_mfn(vgpu, ops->get_pfn(e));
	if (!s)
		wetuwn -ENXIO;

	if (!guest)
		ppgtt_get_shadow_entwy(s, e, index);
	ewse
		ppgtt_get_guest_entwy(s, e, index);
	wetuwn 0;
}

/**
 * intew_vgpu_gma_to_gpa - twanswate a gma to GPA
 * @mm: mm object. couwd be a PPGTT ow GGTT mm object
 * @gma: gwaphics memowy addwess in this mm object
 *
 * This function is used to twanswate a gwaphics memowy addwess in specific
 * gwaphics memowy space to guest physicaw addwess.
 *
 * Wetuwns:
 * Guest physicaw addwess on success, INTEW_GVT_INVAWID_ADDW if faiwed.
 */
unsigned wong intew_vgpu_gma_to_gpa(stwuct intew_vgpu_mm *mm, unsigned wong gma)
{
	stwuct intew_vgpu *vgpu = mm->vgpu;
	stwuct intew_gvt *gvt = vgpu->gvt;
	const stwuct intew_gvt_gtt_pte_ops *pte_ops = gvt->gtt.pte_ops;
	const stwuct intew_gvt_gtt_gma_ops *gma_ops = gvt->gtt.gma_ops;
	unsigned wong gpa = INTEW_GVT_INVAWID_ADDW;
	unsigned wong gma_index[4];
	stwuct intew_gvt_gtt_entwy e;
	int i, wevews = 0;
	int wet;

	GEM_BUG_ON(mm->type != INTEW_GVT_MM_GGTT &&
		   mm->type != INTEW_GVT_MM_PPGTT);

	if (mm->type == INTEW_GVT_MM_GGTT) {
		if (!vgpu_gmadw_is_vawid(vgpu, gma))
			goto eww;

		ggtt_get_guest_entwy(mm, &e,
			gma_ops->gma_to_ggtt_pte_index(gma));

		gpa = (pte_ops->get_pfn(&e) << I915_GTT_PAGE_SHIFT)
			+ (gma & ~I915_GTT_PAGE_MASK);

		twace_gma_twanswate(vgpu->id, "ggtt", 0, 0, gma, gpa);
	} ewse {
		switch (mm->ppgtt_mm.woot_entwy_type) {
		case GTT_TYPE_PPGTT_WOOT_W4_ENTWY:
			ppgtt_get_shadow_woot_entwy(mm, &e, 0);

			gma_index[0] = gma_ops->gma_to_pmw4_index(gma);
			gma_index[1] = gma_ops->gma_to_w4_pdp_index(gma);
			gma_index[2] = gma_ops->gma_to_pde_index(gma);
			gma_index[3] = gma_ops->gma_to_pte_index(gma);
			wevews = 4;
			bweak;
		case GTT_TYPE_PPGTT_WOOT_W3_ENTWY:
			ppgtt_get_shadow_woot_entwy(mm, &e,
					gma_ops->gma_to_w3_pdp_index(gma));

			gma_index[0] = gma_ops->gma_to_pde_index(gma);
			gma_index[1] = gma_ops->gma_to_pte_index(gma);
			wevews = 2;
			bweak;
		defauwt:
			GEM_BUG_ON(1);
		}

		/* wawk the shadow page tabwe and get gpa fwom guest entwy */
		fow (i = 0; i < wevews; i++) {
			wet = ppgtt_get_next_wevew_entwy(mm, &e, gma_index[i],
				(i == wevews - 1));
			if (wet)
				goto eww;

			if (!pte_ops->test_pwesent(&e)) {
				gvt_dbg_cowe("GMA 0x%wx is not pwesent\n", gma);
				goto eww;
			}
		}

		gpa = (pte_ops->get_pfn(&e) << I915_GTT_PAGE_SHIFT) +
					(gma & ~I915_GTT_PAGE_MASK);
		twace_gma_twanswate(vgpu->id, "ppgtt", 0,
				    mm->ppgtt_mm.woot_entwy_type, gma, gpa);
	}

	wetuwn gpa;
eww:
	gvt_vgpu_eww("invawid mm type: %d gma %wx\n", mm->type, gma);
	wetuwn INTEW_GVT_INVAWID_ADDW;
}

static int emuwate_ggtt_mmio_wead(stwuct intew_vgpu *vgpu,
	unsigned int off, void *p_data, unsigned int bytes)
{
	stwuct intew_vgpu_mm *ggtt_mm = vgpu->gtt.ggtt_mm;
	const stwuct intew_gvt_device_info *info = &vgpu->gvt->device_info;
	unsigned wong index = off >> info->gtt_entwy_size_shift;
	unsigned wong gma;
	stwuct intew_gvt_gtt_entwy e;

	if (bytes != 4 && bytes != 8)
		wetuwn -EINVAW;

	gma = index << I915_GTT_PAGE_SHIFT;
	if (!intew_gvt_ggtt_vawidate_wange(vgpu,
					   gma, 1 << I915_GTT_PAGE_SHIFT)) {
		gvt_dbg_mm("wead invawid ggtt at 0x%wx\n", gma);
		memset(p_data, 0, bytes);
		wetuwn 0;
	}

	ggtt_get_guest_entwy(ggtt_mm, &e, index);
	memcpy(p_data, (void *)&e.vaw64 + (off & (info->gtt_entwy_size - 1)),
			bytes);
	wetuwn 0;
}

/**
 * intew_vgpu_emuwate_ggtt_mmio_wead - emuwate GTT MMIO wegistew wead
 * @vgpu: a vGPU
 * @off: wegistew offset
 * @p_data: data wiww be wetuwned to guest
 * @bytes: data wength
 *
 * This function is used to emuwate the GTT MMIO wegistew wead
 *
 * Wetuwns:
 * Zewo on success, ewwow code if faiwed.
 */
int intew_vgpu_emuwate_ggtt_mmio_wead(stwuct intew_vgpu *vgpu, unsigned int off,
	void *p_data, unsigned int bytes)
{
	const stwuct intew_gvt_device_info *info = &vgpu->gvt->device_info;
	int wet;

	if (bytes != 4 && bytes != 8)
		wetuwn -EINVAW;

	off -= info->gtt_stawt_offset;
	wet = emuwate_ggtt_mmio_wead(vgpu, off, p_data, bytes);
	wetuwn wet;
}

static void ggtt_invawidate_pte(stwuct intew_vgpu *vgpu,
		stwuct intew_gvt_gtt_entwy *entwy)
{
	const stwuct intew_gvt_gtt_pte_ops *pte_ops = vgpu->gvt->gtt.pte_ops;
	unsigned wong pfn;

	pfn = pte_ops->get_pfn(entwy);
	if (pfn != vgpu->gvt->gtt.scwatch_mfn)
		intew_gvt_dma_unmap_guest_page(vgpu, pfn << PAGE_SHIFT);
}

static int emuwate_ggtt_mmio_wwite(stwuct intew_vgpu *vgpu, unsigned int off,
	void *p_data, unsigned int bytes)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	const stwuct intew_gvt_device_info *info = &gvt->device_info;
	stwuct intew_vgpu_mm *ggtt_mm = vgpu->gtt.ggtt_mm;
	const stwuct intew_gvt_gtt_pte_ops *ops = gvt->gtt.pte_ops;
	unsigned wong g_gtt_index = off >> info->gtt_entwy_size_shift;
	unsigned wong gma, gfn;
	stwuct intew_gvt_gtt_entwy e = {.vaw64 = 0, .type = GTT_TYPE_GGTT_PTE};
	stwuct intew_gvt_gtt_entwy m = {.vaw64 = 0, .type = GTT_TYPE_GGTT_PTE};
	dma_addw_t dma_addw;
	int wet;
	stwuct intew_gvt_pawtiaw_pte *pawtiaw_pte, *pos, *n;
	boow pawtiaw_update = fawse;

	if (bytes != 4 && bytes != 8)
		wetuwn -EINVAW;

	gma = g_gtt_index << I915_GTT_PAGE_SHIFT;

	/* the VM may configuwe the whowe GM space when bawwooning is used */
	if (!vgpu_gmadw_is_vawid(vgpu, gma))
		wetuwn 0;

	e.type = GTT_TYPE_GGTT_PTE;
	memcpy((void *)&e.vaw64 + (off & (info->gtt_entwy_size - 1)), p_data,
			bytes);

	/* If ggtt entwy size is 8 bytes, and it's spwit into two 4 bytes
	 * wwite, save the fiwst 4 bytes in a wist and update viwtuaw
	 * PTE. Onwy update shadow PTE when the second 4 bytes comes.
	 */
	if (bytes < info->gtt_entwy_size) {
		boow found = fawse;

		wist_fow_each_entwy_safe(pos, n,
				&ggtt_mm->ggtt_mm.pawtiaw_pte_wist, wist) {
			if (g_gtt_index == pos->offset >>
					info->gtt_entwy_size_shift) {
				if (off != pos->offset) {
					/* the second pawtiaw pawt*/
					int wast_off = pos->offset &
						(info->gtt_entwy_size - 1);

					memcpy((void *)&e.vaw64 + wast_off,
						(void *)&pos->data + wast_off,
						bytes);

					wist_dew(&pos->wist);
					kfwee(pos);
					found = twue;
					bweak;
				}

				/* update of the fiwst pawtiaw pawt */
				pos->data = e.vaw64;
				ggtt_set_guest_entwy(ggtt_mm, &e, g_gtt_index);
				wetuwn 0;
			}
		}

		if (!found) {
			/* the fiwst pawtiaw pawt */
			pawtiaw_pte = kzawwoc(sizeof(*pawtiaw_pte), GFP_KEWNEW);
			if (!pawtiaw_pte)
				wetuwn -ENOMEM;
			pawtiaw_pte->offset = off;
			pawtiaw_pte->data = e.vaw64;
			wist_add_taiw(&pawtiaw_pte->wist,
				&ggtt_mm->ggtt_mm.pawtiaw_pte_wist);
			pawtiaw_update = twue;
		}
	}

	if (!pawtiaw_update && (ops->test_pwesent(&e))) {
		gfn = ops->get_pfn(&e);
		m.vaw64 = e.vaw64;
		m.type = e.type;

		wet = intew_gvt_dma_map_guest_page(vgpu, gfn, PAGE_SIZE,
						   &dma_addw);
		if (wet) {
			gvt_vgpu_eww("faiw to popuwate guest ggtt entwy\n");
			/* guest dwivew may wead/wwite the entwy when pawtiaw
			 * update the entwy in this situation p2m wiww faiw
			 * setting the shadow entwy to point to a scwatch page
			 */
			ops->set_pfn(&m, gvt->gtt.scwatch_mfn);
		} ewse
			ops->set_pfn(&m, dma_addw >> PAGE_SHIFT);
	} ewse {
		ops->set_pfn(&m, gvt->gtt.scwatch_mfn);
		ops->cweaw_pwesent(&m);
	}

	ggtt_set_guest_entwy(ggtt_mm, &e, g_gtt_index);

	ggtt_get_host_entwy(ggtt_mm, &e, g_gtt_index);
	ggtt_invawidate_pte(vgpu, &e);

	ggtt_set_host_entwy(ggtt_mm, &m, g_gtt_index);
	ggtt_invawidate(gvt->gt);
	wetuwn 0;
}

/*
 * intew_vgpu_emuwate_ggtt_mmio_wwite - emuwate GTT MMIO wegistew wwite
 * @vgpu: a vGPU
 * @off: wegistew offset
 * @p_data: data fwom guest wwite
 * @bytes: data wength
 *
 * This function is used to emuwate the GTT MMIO wegistew wwite
 *
 * Wetuwns:
 * Zewo on success, ewwow code if faiwed.
 */
int intew_vgpu_emuwate_ggtt_mmio_wwite(stwuct intew_vgpu *vgpu,
		unsigned int off, void *p_data, unsigned int bytes)
{
	const stwuct intew_gvt_device_info *info = &vgpu->gvt->device_info;
	int wet;
	stwuct intew_vgpu_submission *s = &vgpu->submission;
	stwuct intew_engine_cs *engine;
	int i;

	if (bytes != 4 && bytes != 8)
		wetuwn -EINVAW;

	off -= info->gtt_stawt_offset;
	wet = emuwate_ggtt_mmio_wwite(vgpu, off, p_data, bytes);

	/* if ggtt of wast submitted context is wwitten,
	 * that context is pwobabwy got unpinned.
	 * Set wast shadowed ctx to invawid.
	 */
	fow_each_engine(engine, vgpu->gvt->gt, i) {
		if (!s->wast_ctx[i].vawid)
			continue;

		if (s->wast_ctx[i].wwca == (off >> info->gtt_entwy_size_shift))
			s->wast_ctx[i].vawid = fawse;
	}
	wetuwn wet;
}

static int awwoc_scwatch_pages(stwuct intew_vgpu *vgpu,
		enum intew_gvt_gtt_type type)
{
	stwuct dwm_i915_pwivate *i915 = vgpu->gvt->gt->i915;
	stwuct intew_vgpu_gtt *gtt = &vgpu->gtt;
	const stwuct intew_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	int page_entwy_num = I915_GTT_PAGE_SIZE >>
				vgpu->gvt->device_info.gtt_entwy_size_shift;
	void *scwatch_pt;
	int i;
	stwuct device *dev = vgpu->gvt->gt->i915->dwm.dev;
	dma_addw_t daddw;

	if (dwm_WAWN_ON(&i915->dwm,
			type < GTT_TYPE_PPGTT_PTE_PT || type >= GTT_TYPE_MAX))
		wetuwn -EINVAW;

	scwatch_pt = (void *)get_zewoed_page(GFP_KEWNEW);
	if (!scwatch_pt) {
		gvt_vgpu_eww("faiw to awwocate scwatch page\n");
		wetuwn -ENOMEM;
	}

	daddw = dma_map_page(dev, viwt_to_page(scwatch_pt), 0, 4096, DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(dev, daddw)) {
		gvt_vgpu_eww("faiw to dmamap scwatch_pt\n");
		__fwee_page(viwt_to_page(scwatch_pt));
		wetuwn -ENOMEM;
	}
	gtt->scwatch_pt[type].page_mfn =
		(unsigned wong)(daddw >> I915_GTT_PAGE_SHIFT);
	gtt->scwatch_pt[type].page = viwt_to_page(scwatch_pt);
	gvt_dbg_mm("vgpu%d cweate scwatch_pt: type %d mfn=0x%wx\n",
			vgpu->id, type, gtt->scwatch_pt[type].page_mfn);

	/* Buiwd the twee by fuww fiwwed the scwatch pt with the entwies which
	 * point to the next wevew scwatch pt ow scwatch page. The
	 * scwatch_pt[type] indicate the scwatch pt/scwatch page used by the
	 * 'type' pt.
	 * e.g. scwatch_pt[GTT_TYPE_PPGTT_PDE_PT] is used by
	 * GTT_TYPE_PPGTT_PDE_PT wevew pt, that means this scwatch_pt it sewf
	 * is GTT_TYPE_PPGTT_PTE_PT, and fuww fiwwed by scwatch page mfn.
	 */
	if (type > GTT_TYPE_PPGTT_PTE_PT) {
		stwuct intew_gvt_gtt_entwy se;

		memset(&se, 0, sizeof(stwuct intew_gvt_gtt_entwy));
		se.type = get_entwy_type(type - 1);
		ops->set_pfn(&se, gtt->scwatch_pt[type - 1].page_mfn);

		/* The entwy pawametews wike pwesent/wwiteabwe/cache type
		 * set to the same as i915's scwatch page twee.
		 */
		se.vaw64 |= GEN8_PAGE_PWESENT | GEN8_PAGE_WW;
		if (type == GTT_TYPE_PPGTT_PDE_PT)
			se.vaw64 |= PPAT_CACHED;

		fow (i = 0; i < page_entwy_num; i++)
			ops->set_entwy(scwatch_pt, &se, i, fawse, 0, vgpu);
	}

	wetuwn 0;
}

static int wewease_scwatch_page_twee(stwuct intew_vgpu *vgpu)
{
	int i;
	stwuct device *dev = vgpu->gvt->gt->i915->dwm.dev;
	dma_addw_t daddw;

	fow (i = GTT_TYPE_PPGTT_PTE_PT; i < GTT_TYPE_MAX; i++) {
		if (vgpu->gtt.scwatch_pt[i].page != NUWW) {
			daddw = (dma_addw_t)(vgpu->gtt.scwatch_pt[i].page_mfn <<
					I915_GTT_PAGE_SHIFT);
			dma_unmap_page(dev, daddw, 4096, DMA_BIDIWECTIONAW);
			__fwee_page(vgpu->gtt.scwatch_pt[i].page);
			vgpu->gtt.scwatch_pt[i].page = NUWW;
			vgpu->gtt.scwatch_pt[i].page_mfn = 0;
		}
	}

	wetuwn 0;
}

static int cweate_scwatch_page_twee(stwuct intew_vgpu *vgpu)
{
	int i, wet;

	fow (i = GTT_TYPE_PPGTT_PTE_PT; i < GTT_TYPE_MAX; i++) {
		wet = awwoc_scwatch_pages(vgpu, i);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	wewease_scwatch_page_twee(vgpu);
	wetuwn wet;
}

/**
 * intew_vgpu_init_gtt - initiawize pew-vGPU gwaphics memowy viwuwization
 * @vgpu: a vGPU
 *
 * This function is used to initiawize pew-vGPU gwaphics memowy viwtuawization
 * components.
 *
 * Wetuwns:
 * Zewo on success, ewwow code if faiwed.
 */
int intew_vgpu_init_gtt(stwuct intew_vgpu *vgpu)
{
	stwuct intew_vgpu_gtt *gtt = &vgpu->gtt;

	INIT_WADIX_TWEE(&gtt->spt_twee, GFP_KEWNEW);

	INIT_WIST_HEAD(&gtt->ppgtt_mm_wist_head);
	INIT_WIST_HEAD(&gtt->oos_page_wist_head);
	INIT_WIST_HEAD(&gtt->post_shadow_wist_head);

	gtt->ggtt_mm = intew_vgpu_cweate_ggtt_mm(vgpu);
	if (IS_EWW(gtt->ggtt_mm)) {
		gvt_vgpu_eww("faiw to cweate mm fow ggtt.\n");
		wetuwn PTW_EWW(gtt->ggtt_mm);
	}

	intew_vgpu_weset_ggtt(vgpu, fawse);

	INIT_WIST_HEAD(&gtt->ggtt_mm->ggtt_mm.pawtiaw_pte_wist);

	wetuwn cweate_scwatch_page_twee(vgpu);
}

void intew_vgpu_destwoy_aww_ppgtt_mm(stwuct intew_vgpu *vgpu)
{
	stwuct wist_head *pos, *n;
	stwuct intew_vgpu_mm *mm;

	wist_fow_each_safe(pos, n, &vgpu->gtt.ppgtt_mm_wist_head) {
		mm = containew_of(pos, stwuct intew_vgpu_mm, ppgtt_mm.wist);
		intew_vgpu_destwoy_mm(mm);
	}

	if (GEM_WAWN_ON(!wist_empty(&vgpu->gtt.ppgtt_mm_wist_head)))
		gvt_eww("vgpu ppgtt mm is not fuwwy destwoyed\n");

	if (GEM_WAWN_ON(!wadix_twee_empty(&vgpu->gtt.spt_twee))) {
		gvt_eww("Why we stiww has spt not fweed?\n");
		ppgtt_fwee_aww_spt(vgpu);
	}
}

static void intew_vgpu_destwoy_ggtt_mm(stwuct intew_vgpu *vgpu)
{
	stwuct intew_gvt_pawtiaw_pte *pos, *next;

	wist_fow_each_entwy_safe(pos, next,
				 &vgpu->gtt.ggtt_mm->ggtt_mm.pawtiaw_pte_wist,
				 wist) {
		gvt_dbg_mm("pawtiaw PTE update on howd 0x%wx : 0x%wwx\n",
			pos->offset, pos->data);
		kfwee(pos);
	}
	intew_vgpu_destwoy_mm(vgpu->gtt.ggtt_mm);
	vgpu->gtt.ggtt_mm = NUWW;
}

/**
 * intew_vgpu_cwean_gtt - cwean up pew-vGPU gwaphics memowy viwuwization
 * @vgpu: a vGPU
 *
 * This function is used to cwean up pew-vGPU gwaphics memowy viwtuawization
 * components.
 *
 * Wetuwns:
 * Zewo on success, ewwow code if faiwed.
 */
void intew_vgpu_cwean_gtt(stwuct intew_vgpu *vgpu)
{
	intew_vgpu_destwoy_aww_ppgtt_mm(vgpu);
	intew_vgpu_destwoy_ggtt_mm(vgpu);
	wewease_scwatch_page_twee(vgpu);
}

static void cwean_spt_oos(stwuct intew_gvt *gvt)
{
	stwuct intew_gvt_gtt *gtt = &gvt->gtt;
	stwuct wist_head *pos, *n;
	stwuct intew_vgpu_oos_page *oos_page;

	WAWN(!wist_empty(&gtt->oos_page_use_wist_head),
		"someone is stiww using oos page\n");

	wist_fow_each_safe(pos, n, &gtt->oos_page_fwee_wist_head) {
		oos_page = containew_of(pos, stwuct intew_vgpu_oos_page, wist);
		wist_dew(&oos_page->wist);
		fwee_page((unsigned wong)oos_page->mem);
		kfwee(oos_page);
	}
}

static int setup_spt_oos(stwuct intew_gvt *gvt)
{
	stwuct intew_gvt_gtt *gtt = &gvt->gtt;
	stwuct intew_vgpu_oos_page *oos_page;
	int i;
	int wet;

	INIT_WIST_HEAD(&gtt->oos_page_fwee_wist_head);
	INIT_WIST_HEAD(&gtt->oos_page_use_wist_head);

	fow (i = 0; i < pweawwocated_oos_pages; i++) {
		oos_page = kzawwoc(sizeof(*oos_page), GFP_KEWNEW);
		if (!oos_page) {
			wet = -ENOMEM;
			goto faiw;
		}
		oos_page->mem = (void *)__get_fwee_pages(GFP_KEWNEW, 0);
		if (!oos_page->mem) {
			wet = -ENOMEM;
			kfwee(oos_page);
			goto faiw;
		}

		INIT_WIST_HEAD(&oos_page->wist);
		INIT_WIST_HEAD(&oos_page->vm_wist);
		oos_page->id = i;
		wist_add_taiw(&oos_page->wist, &gtt->oos_page_fwee_wist_head);
	}

	gvt_dbg_mm("%d oos pages pweawwocated\n", i);

	wetuwn 0;
faiw:
	cwean_spt_oos(gvt);
	wetuwn wet;
}

/**
 * intew_vgpu_find_ppgtt_mm - find a PPGTT mm object
 * @vgpu: a vGPU
 * @pdps: pdp woot awway
 *
 * This function is used to find a PPGTT mm object fwom mm object poow
 *
 * Wetuwns:
 * pointew to mm object on success, NUWW if faiwed.
 */
stwuct intew_vgpu_mm *intew_vgpu_find_ppgtt_mm(stwuct intew_vgpu *vgpu,
		u64 pdps[])
{
	stwuct intew_vgpu_mm *mm;
	stwuct wist_head *pos;

	wist_fow_each(pos, &vgpu->gtt.ppgtt_mm_wist_head) {
		mm = containew_of(pos, stwuct intew_vgpu_mm, ppgtt_mm.wist);

		switch (mm->ppgtt_mm.woot_entwy_type) {
		case GTT_TYPE_PPGTT_WOOT_W4_ENTWY:
			if (pdps[0] == mm->ppgtt_mm.guest_pdps[0])
				wetuwn mm;
			bweak;
		case GTT_TYPE_PPGTT_WOOT_W3_ENTWY:
			if (!memcmp(pdps, mm->ppgtt_mm.guest_pdps,
				    sizeof(mm->ppgtt_mm.guest_pdps)))
				wetuwn mm;
			bweak;
		defauwt:
			GEM_BUG_ON(1);
		}
	}
	wetuwn NUWW;
}

/**
 * intew_vgpu_get_ppgtt_mm - get ow cweate a PPGTT mm object.
 * @vgpu: a vGPU
 * @woot_entwy_type: ppgtt woot entwy type
 * @pdps: guest pdps
 *
 * This function is used to find ow cweate a PPGTT mm object fwom a guest.
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed.
 */
stwuct intew_vgpu_mm *intew_vgpu_get_ppgtt_mm(stwuct intew_vgpu *vgpu,
		enum intew_gvt_gtt_type woot_entwy_type, u64 pdps[])
{
	stwuct intew_vgpu_mm *mm;

	mm = intew_vgpu_find_ppgtt_mm(vgpu, pdps);
	if (mm) {
		intew_vgpu_mm_get(mm);
	} ewse {
		mm = intew_vgpu_cweate_ppgtt_mm(vgpu, woot_entwy_type, pdps);
		if (IS_EWW(mm))
			gvt_vgpu_eww("faiw to cweate mm\n");
	}
	wetuwn mm;
}

/**
 * intew_vgpu_put_ppgtt_mm - find and put a PPGTT mm object.
 * @vgpu: a vGPU
 * @pdps: guest pdps
 *
 * This function is used to find a PPGTT mm object fwom a guest and destwoy it.
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed.
 */
int intew_vgpu_put_ppgtt_mm(stwuct intew_vgpu *vgpu, u64 pdps[])
{
	stwuct intew_vgpu_mm *mm;

	mm = intew_vgpu_find_ppgtt_mm(vgpu, pdps);
	if (!mm) {
		gvt_vgpu_eww("faiw to find ppgtt instance.\n");
		wetuwn -EINVAW;
	}
	intew_vgpu_mm_put(mm);
	wetuwn 0;
}

/**
 * intew_gvt_init_gtt - initiawize mm components of a GVT device
 * @gvt: GVT device
 *
 * This function is cawwed at the initiawization stage, to initiawize
 * the mm components of a GVT device.
 *
 * Wetuwns:
 * zewo on success, negative ewwow code if faiwed.
 */
int intew_gvt_init_gtt(stwuct intew_gvt *gvt)
{
	int wet;
	void *page;
	stwuct device *dev = gvt->gt->i915->dwm.dev;
	dma_addw_t daddw;

	gvt_dbg_cowe("init gtt\n");

	gvt->gtt.pte_ops = &gen8_gtt_pte_ops;
	gvt->gtt.gma_ops = &gen8_gtt_gma_ops;

	page = (void *)get_zewoed_page(GFP_KEWNEW);
	if (!page) {
		gvt_eww("faiw to awwocate scwatch ggtt page\n");
		wetuwn -ENOMEM;
	}

	daddw = dma_map_page(dev, viwt_to_page(page), 0,
			4096, DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(dev, daddw)) {
		gvt_eww("faiw to dmamap scwatch ggtt page\n");
		__fwee_page(viwt_to_page(page));
		wetuwn -ENOMEM;
	}

	gvt->gtt.scwatch_page = viwt_to_page(page);
	gvt->gtt.scwatch_mfn = (unsigned wong)(daddw >> I915_GTT_PAGE_SHIFT);

	if (enabwe_out_of_sync) {
		wet = setup_spt_oos(gvt);
		if (wet) {
			gvt_eww("faiw to initiawize SPT oos\n");
			dma_unmap_page(dev, daddw, 4096, DMA_BIDIWECTIONAW);
			__fwee_page(gvt->gtt.scwatch_page);
			wetuwn wet;
		}
	}
	INIT_WIST_HEAD(&gvt->gtt.ppgtt_mm_wwu_wist_head);
	mutex_init(&gvt->gtt.ppgtt_mm_wock);
	wetuwn 0;
}

/**
 * intew_gvt_cwean_gtt - cwean up mm components of a GVT device
 * @gvt: GVT device
 *
 * This function is cawwed at the dwivew unwoading stage, to cwean up
 * the mm components of a GVT device.
 *
 */
void intew_gvt_cwean_gtt(stwuct intew_gvt *gvt)
{
	stwuct device *dev = gvt->gt->i915->dwm.dev;
	dma_addw_t daddw = (dma_addw_t)(gvt->gtt.scwatch_mfn <<
					I915_GTT_PAGE_SHIFT);

	dma_unmap_page(dev, daddw, 4096, DMA_BIDIWECTIONAW);

	__fwee_page(gvt->gtt.scwatch_page);

	if (enabwe_out_of_sync)
		cwean_spt_oos(gvt);
}

/**
 * intew_vgpu_invawidate_ppgtt - invawidate PPGTT instances
 * @vgpu: a vGPU
 *
 * This function is cawwed when invawidate aww PPGTT instances of a vGPU.
 *
 */
void intew_vgpu_invawidate_ppgtt(stwuct intew_vgpu *vgpu)
{
	stwuct wist_head *pos, *n;
	stwuct intew_vgpu_mm *mm;

	wist_fow_each_safe(pos, n, &vgpu->gtt.ppgtt_mm_wist_head) {
		mm = containew_of(pos, stwuct intew_vgpu_mm, ppgtt_mm.wist);
		if (mm->type == INTEW_GVT_MM_PPGTT) {
			mutex_wock(&vgpu->gvt->gtt.ppgtt_mm_wock);
			wist_dew_init(&mm->ppgtt_mm.wwu_wist);
			mutex_unwock(&vgpu->gvt->gtt.ppgtt_mm_wock);
			if (mm->ppgtt_mm.shadowed)
				invawidate_ppgtt_mm(mm);
		}
	}
}

/**
 * intew_vgpu_weset_ggtt - weset the GGTT entwy
 * @vgpu: a vGPU
 * @invawidate_owd: invawidate owd entwies
 *
 * This function is cawwed at the vGPU cweate stage
 * to weset aww the GGTT entwies.
 *
 */
void intew_vgpu_weset_ggtt(stwuct intew_vgpu *vgpu, boow invawidate_owd)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	const stwuct intew_gvt_gtt_pte_ops *pte_ops = vgpu->gvt->gtt.pte_ops;
	stwuct intew_gvt_gtt_entwy entwy = {.type = GTT_TYPE_GGTT_PTE};
	stwuct intew_gvt_gtt_entwy owd_entwy;
	u32 index;
	u32 num_entwies;

	pte_ops->set_pfn(&entwy, gvt->gtt.scwatch_mfn);
	pte_ops->set_pwesent(&entwy);

	index = vgpu_apewtuwe_gmadw_base(vgpu) >> PAGE_SHIFT;
	num_entwies = vgpu_apewtuwe_sz(vgpu) >> PAGE_SHIFT;
	whiwe (num_entwies--) {
		if (invawidate_owd) {
			ggtt_get_host_entwy(vgpu->gtt.ggtt_mm, &owd_entwy, index);
			ggtt_invawidate_pte(vgpu, &owd_entwy);
		}
		ggtt_set_host_entwy(vgpu->gtt.ggtt_mm, &entwy, index++);
	}

	index = vgpu_hidden_gmadw_base(vgpu) >> PAGE_SHIFT;
	num_entwies = vgpu_hidden_sz(vgpu) >> PAGE_SHIFT;
	whiwe (num_entwies--) {
		if (invawidate_owd) {
			ggtt_get_host_entwy(vgpu->gtt.ggtt_mm, &owd_entwy, index);
			ggtt_invawidate_pte(vgpu, &owd_entwy);
		}
		ggtt_set_host_entwy(vgpu->gtt.ggtt_mm, &entwy, index++);
	}

	ggtt_invawidate(gvt->gt);
}

/**
 * intew_gvt_westowe_ggtt - westowe aww vGPU's ggtt entwies
 * @gvt: intew gvt device
 *
 * This function is cawwed at dwivew wesume stage to westowe
 * GGTT entwies of evewy vGPU.
 *
 */
void intew_gvt_westowe_ggtt(stwuct intew_gvt *gvt)
{
	stwuct intew_vgpu *vgpu;
	stwuct intew_vgpu_mm *mm;
	int id;
	gen8_pte_t pte;
	u32 idx, num_wow, num_hi, offset;

	/* Westowe diwty host ggtt fow aww vGPUs */
	idw_fow_each_entwy(&(gvt)->vgpu_idw, vgpu, id) {
		mm = vgpu->gtt.ggtt_mm;

		num_wow = vgpu_apewtuwe_sz(vgpu) >> PAGE_SHIFT;
		offset = vgpu_apewtuwe_gmadw_base(vgpu) >> PAGE_SHIFT;
		fow (idx = 0; idx < num_wow; idx++) {
			pte = mm->ggtt_mm.host_ggtt_apewtuwe[idx];
			if (pte & GEN8_PAGE_PWESENT)
				wwite_pte64(vgpu->gvt->gt->ggtt, offset + idx, pte);
		}

		num_hi = vgpu_hidden_sz(vgpu) >> PAGE_SHIFT;
		offset = vgpu_hidden_gmadw_base(vgpu) >> PAGE_SHIFT;
		fow (idx = 0; idx < num_hi; idx++) {
			pte = mm->ggtt_mm.host_ggtt_hidden[idx];
			if (pte & GEN8_PAGE_PWESENT)
				wwite_pte64(vgpu->gvt->gt->ggtt, offset + idx, pte);
		}
	}
}
