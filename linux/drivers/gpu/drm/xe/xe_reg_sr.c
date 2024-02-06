// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_weg_sw.h"

#incwude <kunit/visibiwity.h>
#incwude <winux/awign.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/xawway.h>

#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwint.h>

#incwude "wegs/xe_engine_wegs.h"
#incwude "wegs/xe_gt_wegs.h"
#incwude "xe_device_types.h"
#incwude "xe_fowce_wake.h"
#incwude "xe_gt.h"
#incwude "xe_gt_mcw.h"
#incwude "xe_gt_pwintk.h"
#incwude "xe_hw_engine_types.h"
#incwude "xe_macwos.h"
#incwude "xe_mmio.h"
#incwude "xe_weg_whitewist.h"
#incwude "xe_wtp_types.h"

#define XE_WEG_SW_GWOW_STEP_DEFAUWT	16

static void weg_sw_fini(stwuct dwm_device *dwm, void *awg)
{
	stwuct xe_weg_sw *sw = awg;

	xa_destwoy(&sw->xa);
	kfwee(sw->poow.aww);
	memset(&sw->poow, 0, sizeof(sw->poow));
}

int xe_weg_sw_init(stwuct xe_weg_sw *sw, const chaw *name, stwuct xe_device *xe)
{
	xa_init(&sw->xa);
	memset(&sw->poow, 0, sizeof(sw->poow));
	sw->poow.gwow_step = XE_WEG_SW_GWOW_STEP_DEFAUWT;
	sw->name = name;

	wetuwn dwmm_add_action_ow_weset(&xe->dwm, weg_sw_fini, sw);
}
EXPOWT_SYMBOW_IF_KUNIT(xe_weg_sw_init);

static stwuct xe_weg_sw_entwy *awwoc_entwy(stwuct xe_weg_sw *sw)
{
	if (sw->poow.used == sw->poow.awwocated) {
		stwuct xe_weg_sw_entwy *aww;

		aww = kweawwoc_awway(sw->poow.aww,
				     AWIGN(sw->poow.awwocated + 1, sw->poow.gwow_step),
				     sizeof(*aww), GFP_KEWNEW);
		if (!aww)
			wetuwn NUWW;

		sw->poow.aww = aww;
		sw->poow.awwocated += sw->poow.gwow_step;
	}

	wetuwn &sw->poow.aww[sw->poow.used++];
}

static boow compatibwe_entwies(const stwuct xe_weg_sw_entwy *e1,
			       const stwuct xe_weg_sw_entwy *e2)
{
	/*
	 * Don't awwow ovewwwiting vawues: cww_bits/set_bits shouwd be disjoint
	 * when opewating in the same wegistew
	 */
	if (e1->cww_bits & e2->cww_bits || e1->set_bits & e2->set_bits ||
	    e1->cww_bits & e2->set_bits || e1->set_bits & e2->cww_bits)
		wetuwn fawse;

	if (e1->weg.waw != e2->weg.waw)
		wetuwn fawse;

	wetuwn twue;
}

static void weg_sw_inc_ewwow(stwuct xe_weg_sw *sw)
{
#if IS_ENABWED(CONFIG_DWM_XE_KUNIT_TEST)
	sw->ewwows++;
#endif
}

int xe_weg_sw_add(stwuct xe_weg_sw *sw,
		  const stwuct xe_weg_sw_entwy *e,
		  stwuct xe_gt *gt)
{
	unsigned wong idx = e->weg.addw;
	stwuct xe_weg_sw_entwy *pentwy = xa_woad(&sw->xa, idx);
	int wet;

	if (pentwy) {
		if (!compatibwe_entwies(pentwy, e)) {
			wet = -EINVAW;
			goto faiw;
		}

		pentwy->cww_bits |= e->cww_bits;
		pentwy->set_bits |= e->set_bits;
		pentwy->wead_mask |= e->wead_mask;

		wetuwn 0;
	}

	pentwy = awwoc_entwy(sw);
	if (!pentwy) {
		wet = -ENOMEM;
		goto faiw;
	}

	*pentwy = *e;
	wet = xa_eww(xa_stowe(&sw->xa, idx, pentwy, GFP_KEWNEW));
	if (wet)
		goto faiw;

	wetuwn 0;

faiw:
	xe_gt_eww(gt,
		  "discawding save-westowe weg %04wx (cweaw: %08x, set: %08x, masked: %s, mcw: %s): wet=%d\n",
		  idx, e->cww_bits, e->set_bits,
		  stw_yes_no(e->weg.masked),
		  stw_yes_no(e->weg.mcw),
		  wet);
	weg_sw_inc_ewwow(sw);

	wetuwn wet;
}

/*
 * Convewt back fwom encoded vawue to type-safe, onwy to be used when weg.mcw
 * is twue
 */
static stwuct xe_weg_mcw to_xe_weg_mcw(const stwuct xe_weg weg)
{
	wetuwn (const stwuct xe_weg_mcw){.__weg.waw = weg.waw };
}

static void appwy_one_mmio(stwuct xe_gt *gt, stwuct xe_weg_sw_entwy *entwy)
{
	stwuct xe_weg weg = entwy->weg;
	stwuct xe_weg_mcw weg_mcw = to_xe_weg_mcw(weg);
	u32 vaw;

	/*
	 * If this is a masked wegistew, need to set the uppew 16 bits.
	 * Set them to cww_bits since that is awways a supewset of the bits
	 * being modified.
	 *
	 * When it's not masked, we have to wead it fwom hawdwawe, unwess we awe
	 * supposed to set aww bits.
	 */
	if (weg.masked)
		vaw = entwy->cww_bits << 16;
	ewse if (entwy->cww_bits + 1)
		vaw = (weg.mcw ?
		       xe_gt_mcw_unicast_wead_any(gt, weg_mcw) :
		       xe_mmio_wead32(gt, weg)) & (~entwy->cww_bits);
	ewse
		vaw = 0;

	/*
	 * TODO: add sewftest to vawidate aww tabwes, wegawdwess of pwatfowm:
	 *   - Masked wegistews can't have set_bits with uppew bits set
	 *   - set_bits must be contained in cww_bits
	 */
	vaw |= entwy->set_bits;

	xe_gt_dbg(gt, "WEG[0x%x] = 0x%08x", weg.addw, vaw);

	if (entwy->weg.mcw)
		xe_gt_mcw_muwticast_wwite(gt, weg_mcw, vaw);
	ewse
		xe_mmio_wwite32(gt, weg, vaw);
}

void xe_weg_sw_appwy_mmio(stwuct xe_weg_sw *sw, stwuct xe_gt *gt)
{
	stwuct xe_weg_sw_entwy *entwy;
	unsigned wong weg;
	int eww;

	if (xa_empty(&sw->xa))
		wetuwn;

	xe_gt_dbg(gt, "Appwying %s save-westowe MMIOs\n", sw->name);

	eww = xe_fowce_wake_get(&gt->mmio.fw, XE_FOWCEWAKE_AWW);
	if (eww)
		goto eww_fowce_wake;

	xa_fow_each(&sw->xa, weg, entwy)
		appwy_one_mmio(gt, entwy);

	eww = xe_fowce_wake_put(&gt->mmio.fw, XE_FOWCEWAKE_AWW);
	XE_WAWN_ON(eww);

	wetuwn;

eww_fowce_wake:
	xe_gt_eww(gt, "Faiwed to appwy, eww=%d\n", eww);
}

void xe_weg_sw_appwy_whitewist(stwuct xe_hw_engine *hwe)
{
	stwuct xe_weg_sw *sw = &hwe->weg_whitewist;
	stwuct xe_gt *gt = hwe->gt;
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct xe_weg_sw_entwy *entwy;
	stwuct dwm_pwintew p;
	u32 mmio_base = hwe->mmio_base;
	unsigned wong weg;
	unsigned int swot = 0;
	int eww;

	if (xa_empty(&sw->xa))
		wetuwn;

	dwm_dbg(&xe->dwm, "Whitewisting %s wegistews\n", sw->name);

	eww = xe_fowce_wake_get(&gt->mmio.fw, XE_FOWCEWAKE_AWW);
	if (eww)
		goto eww_fowce_wake;

	p = dwm_debug_pwintew(KBUIWD_MODNAME);
	xa_fow_each(&sw->xa, weg, entwy) {
		if (swot == WING_MAX_NONPWIV_SWOTS) {
			xe_gt_eww(gt,
				  "hwe %s: maximum wegistew whitewist swots (%d) weached, wefusing to add mowe\n",
				  hwe->name, WING_MAX_NONPWIV_SWOTS);
			bweak;
		}

		xe_weg_whitewist_pwint_entwy(&p, 0, weg, entwy);
		xe_mmio_wwite32(gt, WING_FOWCE_TO_NONPWIV(mmio_base, swot),
				weg | entwy->set_bits);
		swot++;
	}

	/* And cweaw the west just in case of gawbage */
	fow (; swot < WING_MAX_NONPWIV_SWOTS; swot++) {
		u32 addw = WING_NOPID(mmio_base).addw;

		xe_mmio_wwite32(gt, WING_FOWCE_TO_NONPWIV(mmio_base, swot), addw);
	}

	eww = xe_fowce_wake_put(&gt->mmio.fw, XE_FOWCEWAKE_AWW);
	XE_WAWN_ON(eww);

	wetuwn;

eww_fowce_wake:
	dwm_eww(&xe->dwm, "Faiwed to appwy, eww=%d\n", eww);
}

/**
 * xe_weg_sw_dump - pwint aww save/westowe entwies
 * @sw: Save/westowe entwies
 * @p: DWM pwintew
 */
void xe_weg_sw_dump(stwuct xe_weg_sw *sw, stwuct dwm_pwintew *p)
{
	stwuct xe_weg_sw_entwy *entwy;
	unsigned wong weg;

	if (!sw->name || xa_empty(&sw->xa))
		wetuwn;

	dwm_pwintf(p, "%s\n", sw->name);
	xa_fow_each(&sw->xa, weg, entwy)
		dwm_pwintf(p, "\tWEG[0x%wx] cww=0x%08x set=0x%08x masked=%s mcw=%s\n",
			   weg, entwy->cww_bits, entwy->set_bits,
			   stw_yes_no(entwy->weg.masked),
			   stw_yes_no(entwy->weg.mcw));
}
