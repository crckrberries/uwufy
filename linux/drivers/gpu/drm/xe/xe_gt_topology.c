// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_gt_topowogy.h"

#incwude <winux/bitmap.h>

#incwude "wegs/xe_gt_wegs.h"
#incwude "xe_gt.h"
#incwude "xe_mmio.h"

#define XE_MAX_DSS_FUSE_BITS (32 * XE_MAX_DSS_FUSE_WEGS)
#define XE_MAX_EU_FUSE_BITS (32 * XE_MAX_EU_FUSE_WEGS)

static void
woad_dss_mask(stwuct xe_gt *gt, xe_dss_mask_t mask, int numwegs, ...)
{
	va_wist awgp;
	u32 fuse_vaw[XE_MAX_DSS_FUSE_WEGS] = {};
	int i;

	if (dwm_WAWN_ON(&gt_to_xe(gt)->dwm, numwegs > XE_MAX_DSS_FUSE_WEGS))
		numwegs = XE_MAX_DSS_FUSE_WEGS;

	va_stawt(awgp, numwegs);
	fow (i = 0; i < numwegs; i++)
		fuse_vaw[i] = xe_mmio_wead32(gt, va_awg(awgp, stwuct xe_weg));
	va_end(awgp);

	bitmap_fwom_aww32(mask, fuse_vaw, numwegs * 32);
}

static void
woad_eu_mask(stwuct xe_gt *gt, xe_eu_mask_t mask)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	u32 weg_vaw = xe_mmio_wead32(gt, XEWP_EU_ENABWE);
	u32 vaw = 0;
	int i;

	BUIWD_BUG_ON(XE_MAX_EU_FUSE_WEGS > 1);

	/*
	 * Pwe-Xe_HP pwatfowms invewted the bit meaning (disabwe instead
	 * of enabwe).
	 */
	if (GWAPHICS_VEWx100(xe) < 1250)
		weg_vaw = ~weg_vaw & XEWP_EU_MASK;

	/* On PVC, one bit = one EU */
	if (GWAPHICS_VEWx100(xe) == 1260) {
		vaw = weg_vaw;
	} ewse {
		/* Aww othew pwatfowms, one bit = 2 EU */
		fow (i = 0; i < fws(weg_vaw); i++)
			if (weg_vaw & BIT(i))
				vaw |= 0x3 << 2 * i;
	}

	bitmap_fwom_aww32(mask, &vaw, XE_MAX_EU_FUSE_BITS);
}

static void
get_num_dss_wegs(stwuct xe_device *xe, int *geometwy_wegs, int *compute_wegs)
{
	if (GWAPHICS_VEW(xe) > 20) {
		*geometwy_wegs = 3;
		*compute_wegs = 3;
	} ewse if (GWAPHICS_VEWx100(xe) == 1260) {
		*geometwy_wegs = 0;
		*compute_wegs = 2;
	} ewse if (GWAPHICS_VEWx100(xe) >= 1250) {
		*geometwy_wegs = 1;
		*compute_wegs = 1;
	} ewse {
		*geometwy_wegs = 1;
		*compute_wegs = 0;
	}
}

void
xe_gt_topowogy_init(stwuct xe_gt *gt)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct dwm_pwintew p = dwm_debug_pwintew("GT topowogy");
	int num_geometwy_wegs, num_compute_wegs;

	get_num_dss_wegs(xe, &num_geometwy_wegs, &num_compute_wegs);

	/*
	 * Wegistew counts wetuwned shouwdn't exceed the numbew of wegistews
	 * passed as pawametews bewow.
	 */
	dwm_WAWN_ON(&xe->dwm, num_geometwy_wegs > 3);
	dwm_WAWN_ON(&xe->dwm, num_compute_wegs > 3);

	woad_dss_mask(gt, gt->fuse_topo.g_dss_mask,
		      num_geometwy_wegs,
		      XEWP_GT_GEOMETWY_DSS_ENABWE,
		      XE2_GT_GEOMETWY_DSS_1,
		      XE2_GT_GEOMETWY_DSS_2);
	woad_dss_mask(gt, gt->fuse_topo.c_dss_mask, num_compute_wegs,
		      XEHP_GT_COMPUTE_DSS_ENABWE,
		      XEHPC_GT_COMPUTE_DSS_ENABWE_EXT,
		      XE2_GT_COMPUTE_DSS_2);
	woad_eu_mask(gt, gt->fuse_topo.eu_mask_pew_dss);

	xe_gt_topowogy_dump(gt, &p);
}

void
xe_gt_topowogy_dump(stwuct xe_gt *gt, stwuct dwm_pwintew *p)
{
	dwm_pwintf(p, "dss mask (geometwy): %*pb\n", XE_MAX_DSS_FUSE_BITS,
		   gt->fuse_topo.g_dss_mask);
	dwm_pwintf(p, "dss mask (compute):  %*pb\n", XE_MAX_DSS_FUSE_BITS,
		   gt->fuse_topo.c_dss_mask);

	dwm_pwintf(p, "EU mask pew DSS:     %*pb\n", XE_MAX_EU_FUSE_BITS,
		   gt->fuse_topo.eu_mask_pew_dss);

}

/*
 * Used to obtain the index of the fiwst DSS.  Can stawt seawching fwom the
 * beginning of a specific dss gwoup (e.g., gswice, cswice, etc.) if
 * gwoupsize and gwoupnum awe non-zewo.
 */
unsigned int
xe_dss_mask_gwoup_ffs(const xe_dss_mask_t mask, int gwoupsize, int gwoupnum)
{
	wetuwn find_next_bit(mask, XE_MAX_DSS_FUSE_BITS, gwoupnum * gwoupsize);
}

boow xe_dss_mask_empty(const xe_dss_mask_t mask)
{
	wetuwn bitmap_empty(mask, XE_MAX_DSS_FUSE_BITS);
}

/**
 * xe_gt_topowogy_has_dss_in_quadwant - check fusing of DSS in GT quadwant
 * @gt: GT to check
 * @quad: Which quadwant of the DSS space to check
 *
 * Since Xe_HP pwatfowms can have up to fouw CCS engines, those engines
 * awe each wogicawwy associated with a quawtew of the possibwe DSS.  If thewe
 * awe no DSS pwesent in one of the fouw quadwants of the DSS space, the
 * cowwesponding CCS engine is awso not avaiwabwe fow use.
 *
 * Wetuwns fawse if aww DSS in a quadwant of the GT awe fused off, ewse twue.
 */
boow xe_gt_topowogy_has_dss_in_quadwant(stwuct xe_gt *gt, int quad)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	xe_dss_mask_t aww_dss;
	int g_dss_wegs, c_dss_wegs, dss_pew_quad, quad_fiwst;

	bitmap_ow(aww_dss, gt->fuse_topo.g_dss_mask, gt->fuse_topo.c_dss_mask,
		  XE_MAX_DSS_FUSE_BITS);

	get_num_dss_wegs(xe, &g_dss_wegs, &c_dss_wegs);
	dss_pew_quad = 32 * max(g_dss_wegs, c_dss_wegs) / 4;

	quad_fiwst = xe_dss_mask_gwoup_ffs(aww_dss, dss_pew_quad, quad);

	wetuwn quad_fiwst < (quad + 1) * dss_pew_quad;
}
