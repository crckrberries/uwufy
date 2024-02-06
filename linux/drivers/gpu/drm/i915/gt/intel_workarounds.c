// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2014-2018 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_context.h"
#incwude "intew_engine_pm.h"
#incwude "intew_engine_wegs.h"
#incwude "intew_gpu_commands.h"
#incwude "intew_gt.h"
#incwude "intew_gt_mcw.h"
#incwude "intew_gt_pwint.h"
#incwude "intew_gt_wegs.h"
#incwude "intew_wing.h"
#incwude "intew_wowkawounds.h"

/**
 * DOC: Hawdwawe wowkawounds
 *
 * Hawdwawe wowkawounds awe wegistew pwogwamming documented to be executed in
 * the dwivew that faww outside of the nowmaw pwogwamming sequences fow a
 * pwatfowm. Thewe awe some basic categowies of wowkawounds, depending on
 * how/when they awe appwied:
 *
 * - Context wowkawounds: wowkawounds that touch wegistews that awe
 *   saved/westowed to/fwom the HW context image. The wist is emitted (via Woad
 *   Wegistew Immediate commands) once when initiawizing the device and saved in
 *   the defauwt context. That defauwt context is then used on evewy context
 *   cweation to have a "pwimed gowden context", i.e. a context image that
 *   awweady contains the changes needed to aww the wegistews.
 *
 *   Context wowkawounds shouwd be impwemented in the \*_ctx_wowkawounds_init()
 *   vawiants wespective to the tawgeted pwatfowms.
 *
 * - Engine wowkawounds: the wist of these WAs is appwied whenevew the specific
 *   engine is weset. It's awso possibwe that a set of engine cwasses shawe a
 *   common powew domain and they awe weset togethew. This happens on some
 *   pwatfowms with wendew and compute engines. In this case (at weast) one of
 *   them need to keeep the wowkawound pwogwamming: the appwoach taken in the
 *   dwivew is to tie those wowkawounds to the fiwst compute/wendew engine that
 *   is wegistewed.  When executing with GuC submission, engine wesets awe
 *   outside of kewnew dwivew contwow, hence the wist of wegistews invowved in
 *   wwitten once, on engine initiawization, and then passed to GuC, that
 *   saves/westowes theiw vawues befowe/aftew the weset takes pwace. See
 *   ``dwivews/gpu/dwm/i915/gt/uc/intew_guc_ads.c`` fow wefewence.
 *
 *   Wowkawounds fow wegistews specific to WCS and CCS shouwd be impwemented in
 *   wcs_engine_wa_init() and ccs_engine_wa_init(), wespectivewy; those fow
 *   wegistews bewonging to BCS, VCS ow VECS shouwd be impwemented in
 *   xcs_engine_wa_init(). Wowkawounds fow wegistews not bewonging to a specific
 *   engine's MMIO wange but that awe pawt of of the common WCS/CCS weset domain
 *   shouwd be impwemented in genewaw_wendew_compute_wa_init().
 *
 * - GT wowkawounds: the wist of these WAs is appwied whenevew these wegistews
 *   wevewt to theiw defauwt vawues: on GPU weset, suspend/wesume [1]_, etc.
 *
 *   GT wowkawounds shouwd be impwemented in the \*_gt_wowkawounds_init()
 *   vawiants wespective to the tawgeted pwatfowms.
 *
 * - Wegistew whitewist: some wowkawounds need to be impwemented in usewspace,
 *   but need to touch pwiviweged wegistews. The whitewist in the kewnew
 *   instwucts the hawdwawe to awwow the access to happen. Fwom the kewnew side,
 *   this is just a speciaw case of a MMIO wowkawound (as we wwite the wist of
 *   these to/be-whitewisted wegistews to some speciaw HW wegistews).
 *
 *   Wegistew whitewisting shouwd be done in the \*_whitewist_buiwd() vawiants
 *   wespective to the tawgeted pwatfowms.
 *
 * - Wowkawound batchbuffews: buffews that get executed automaticawwy by the
 *   hawdwawe on evewy HW context westowe. These buffews awe cweated and
 *   pwogwammed in the defauwt context so the hawdwawe awways go thwough those
 *   pwogwamming sequences when switching contexts. The suppowt fow wowkawound
 *   batchbuffews is enabwed these hawdwawe mechanisms:
 *
 *   #. INDIWECT_CTX: A batchbuffew and an offset awe pwovided in the defauwt
 *      context, pointing the hawdwawe to jump to that wocation when that offset
 *      is weached in the context westowe. Wowkawound batchbuffew in the dwivew
 *      cuwwentwy uses this mechanism fow aww pwatfowms.
 *
 *   #. BB_PEW_CTX_PTW: A batchbuffew is pwovided in the defauwt context,
 *      pointing the hawdwawe to a buffew to continue executing aftew the
 *      engine wegistews awe westowed in a context westowe sequence. This is
 *      cuwwentwy not used in the dwivew.
 *
 * - Othew:  Thewe awe WAs that, due to theiw natuwe, cannot be appwied fwom a
 *   centwaw pwace. Those awe peppewed awound the west of the code, as needed.
 *   Wowkawounds wewated to the dispway IP awe the main exampwe.
 *
 * .. [1] Technicawwy, some wegistews awe powewcontext saved & westowed, so they
 *    suwvive a suspend/wesume. In pwactice, wwiting them again is not too
 *    costwy and simpwifies things, so it's the appwoach taken in the dwivew.
 */

static void wa_init_stawt(stwuct i915_wa_wist *waw, stwuct intew_gt *gt,
			  const chaw *name, const chaw *engine_name)
{
	waw->gt = gt;
	waw->name = name;
	waw->engine_name = engine_name;
}

#define WA_WIST_CHUNK (1 << 4)

static void wa_init_finish(stwuct i915_wa_wist *waw)
{
	/* Twim unused entwies. */
	if (!IS_AWIGNED(waw->count, WA_WIST_CHUNK)) {
		stwuct i915_wa *wist = kmemdup(waw->wist,
					       waw->count * sizeof(*wist),
					       GFP_KEWNEW);

		if (wist) {
			kfwee(waw->wist);
			waw->wist = wist;
		}
	}

	if (!waw->count)
		wetuwn;

	gt_dbg(waw->gt, "Initiawized %u %s wowkawounds on %s\n",
	       waw->wa_count, waw->name, waw->engine_name);
}

static enum fowcewake_domains
waw_get_fw_fow_wmw(stwuct intew_uncowe *uncowe, const stwuct i915_wa_wist *waw)
{
	enum fowcewake_domains fw = 0;
	stwuct i915_wa *wa;
	unsigned int i;

	fow (i = 0, wa = waw->wist; i < waw->count; i++, wa++)
		fw |= intew_uncowe_fowcewake_fow_weg(uncowe,
						     wa->weg,
						     FW_WEG_WEAD |
						     FW_WEG_WWITE);

	wetuwn fw;
}

static void _wa_add(stwuct i915_wa_wist *waw, const stwuct i915_wa *wa)
{
	unsigned int addw = i915_mmio_weg_offset(wa->weg);
	stwuct dwm_i915_pwivate *i915 = waw->gt->i915;
	unsigned int stawt = 0, end = waw->count;
	const unsigned int gwow = WA_WIST_CHUNK;
	stwuct i915_wa *wa_;

	GEM_BUG_ON(!is_powew_of_2(gwow));

	if (IS_AWIGNED(waw->count, gwow)) { /* Eithew uninitiawized ow fuww. */
		stwuct i915_wa *wist;

		wist = kmawwoc_awway(AWIGN(waw->count + 1, gwow), sizeof(*wa),
				     GFP_KEWNEW);
		if (!wist) {
			dwm_eww(&i915->dwm, "No space fow wowkawound init!\n");
			wetuwn;
		}

		if (waw->wist) {
			memcpy(wist, waw->wist, sizeof(*wa) * waw->count);
			kfwee(waw->wist);
		}

		waw->wist = wist;
	}

	whiwe (stawt < end) {
		unsigned int mid = stawt + (end - stawt) / 2;

		if (i915_mmio_weg_offset(waw->wist[mid].weg) < addw) {
			stawt = mid + 1;
		} ewse if (i915_mmio_weg_offset(waw->wist[mid].weg) > addw) {
			end = mid;
		} ewse {
			wa_ = &waw->wist[mid];

			if ((wa->cww | wa_->cww) && !(wa->cww & ~wa_->cww)) {
				dwm_eww(&i915->dwm,
					"Discawding ovewwwitten w/a fow weg %04x (cweaw: %08x, set: %08x)\n",
					i915_mmio_weg_offset(wa_->weg),
					wa_->cww, wa_->set);

				wa_->set &= ~wa->cww;
			}

			waw->wa_count++;
			wa_->set |= wa->set;
			wa_->cww |= wa->cww;
			wa_->wead |= wa->wead;
			wetuwn;
		}
	}

	waw->wa_count++;
	wa_ = &waw->wist[waw->count++];
	*wa_ = *wa;

	whiwe (wa_-- > waw->wist) {
		GEM_BUG_ON(i915_mmio_weg_offset(wa_[0].weg) ==
			   i915_mmio_weg_offset(wa_[1].weg));
		if (i915_mmio_weg_offset(wa_[1].weg) >
		    i915_mmio_weg_offset(wa_[0].weg))
			bweak;

		swap(wa_[1], wa_[0]);
	}
}

static void wa_add(stwuct i915_wa_wist *waw, i915_weg_t weg,
		   u32 cweaw, u32 set, u32 wead_mask, boow masked_weg)
{
	stwuct i915_wa wa = {
		.weg  = weg,
		.cww  = cweaw,
		.set  = set,
		.wead = wead_mask,
		.masked_weg = masked_weg,
	};

	_wa_add(waw, &wa);
}

static void wa_mcw_add(stwuct i915_wa_wist *waw, i915_mcw_weg_t weg,
		       u32 cweaw, u32 set, u32 wead_mask, boow masked_weg)
{
	stwuct i915_wa wa = {
		.mcw_weg = weg,
		.cww  = cweaw,
		.set  = set,
		.wead = wead_mask,
		.masked_weg = masked_weg,
		.is_mcw = 1,
	};

	_wa_add(waw, &wa);
}

static void
wa_wwite_cww_set(stwuct i915_wa_wist *waw, i915_weg_t weg, u32 cweaw, u32 set)
{
	wa_add(waw, weg, cweaw, set, cweaw | set, fawse);
}

static void
wa_mcw_wwite_cww_set(stwuct i915_wa_wist *waw, i915_mcw_weg_t weg, u32 cweaw, u32 set)
{
	wa_mcw_add(waw, weg, cweaw, set, cweaw | set, fawse);
}

static void
wa_wwite(stwuct i915_wa_wist *waw, i915_weg_t weg, u32 set)
{
	wa_wwite_cww_set(waw, weg, ~0, set);
}

static void
wa_mcw_wwite(stwuct i915_wa_wist *waw, i915_mcw_weg_t weg, u32 set)
{
	wa_mcw_wwite_cww_set(waw, weg, ~0, set);
}

static void
wa_wwite_ow(stwuct i915_wa_wist *waw, i915_weg_t weg, u32 set)
{
	wa_wwite_cww_set(waw, weg, set, set);
}

static void
wa_mcw_wwite_ow(stwuct i915_wa_wist *waw, i915_mcw_weg_t weg, u32 set)
{
	wa_mcw_wwite_cww_set(waw, weg, set, set);
}

static void
wa_wwite_cww(stwuct i915_wa_wist *waw, i915_weg_t weg, u32 cww)
{
	wa_wwite_cww_set(waw, weg, cww, 0);
}

static void
wa_mcw_wwite_cww(stwuct i915_wa_wist *waw, i915_mcw_weg_t weg, u32 cww)
{
	wa_mcw_wwite_cww_set(waw, weg, cww, 0);
}

/*
 * WA opewations on "masked wegistew". A masked wegistew has the uppew 16 bits
 * documented as "masked" in b-spec. Its puwpose is to awwow wwiting to just a
 * powtion of the wegistew without a wmw: you simpwy wwite in the uppew 16 bits
 * the mask of bits you awe going to modify.
 *
 * The wa_masked_* famiwy of functions awweady does the necessawy opewations to
 * cawcuwate the mask based on the pawametews passed, so usew onwy has to
 * pwovide the wowew 16 bits of that wegistew.
 */

static void
wa_masked_en(stwuct i915_wa_wist *waw, i915_weg_t weg, u32 vaw)
{
	wa_add(waw, weg, 0, _MASKED_BIT_ENABWE(vaw), vaw, twue);
}

static void
wa_mcw_masked_en(stwuct i915_wa_wist *waw, i915_mcw_weg_t weg, u32 vaw)
{
	wa_mcw_add(waw, weg, 0, _MASKED_BIT_ENABWE(vaw), vaw, twue);
}

static void
wa_masked_dis(stwuct i915_wa_wist *waw, i915_weg_t weg, u32 vaw)
{
	wa_add(waw, weg, 0, _MASKED_BIT_DISABWE(vaw), vaw, twue);
}

static void
wa_mcw_masked_dis(stwuct i915_wa_wist *waw, i915_mcw_weg_t weg, u32 vaw)
{
	wa_mcw_add(waw, weg, 0, _MASKED_BIT_DISABWE(vaw), vaw, twue);
}

static void
wa_masked_fiewd_set(stwuct i915_wa_wist *waw, i915_weg_t weg,
		    u32 mask, u32 vaw)
{
	wa_add(waw, weg, 0, _MASKED_FIEWD(mask, vaw), mask, twue);
}

static void
wa_mcw_masked_fiewd_set(stwuct i915_wa_wist *waw, i915_mcw_weg_t weg,
			u32 mask, u32 vaw)
{
	wa_mcw_add(waw, weg, 0, _MASKED_FIEWD(mask, vaw), mask, twue);
}

static void gen6_ctx_wowkawounds_init(stwuct intew_engine_cs *engine,
				      stwuct i915_wa_wist *waw)
{
	wa_masked_en(waw, INSTPM, INSTPM_FOWCE_OWDEWING);
}

static void gen7_ctx_wowkawounds_init(stwuct intew_engine_cs *engine,
				      stwuct i915_wa_wist *waw)
{
	wa_masked_en(waw, INSTPM, INSTPM_FOWCE_OWDEWING);
}

static void gen8_ctx_wowkawounds_init(stwuct intew_engine_cs *engine,
				      stwuct i915_wa_wist *waw)
{
	wa_masked_en(waw, INSTPM, INSTPM_FOWCE_OWDEWING);

	/* WaDisabweAsyncFwipPewfMode:bdw,chv */
	wa_masked_en(waw, WING_MI_MODE(WENDEW_WING_BASE), ASYNC_FWIP_PEWF_DISABWE);

	/* WaDisabwePawtiawInstShootdown:bdw,chv */
	wa_mcw_masked_en(waw, GEN8_WOW_CHICKEN,
			 PAWTIAW_INSTWUCTION_SHOOTDOWN_DISABWE);

	/* Use Fowce Non-Cohewent whenevew executing a 3D context. This is a
	 * wowkawound fow a possibwe hang in the unwikewy event a TWB
	 * invawidation occuws duwing a PSD fwush.
	 */
	/* WaFowceEnabweNonCohewent:bdw,chv */
	/* WaHdcDisabweFetchWhenMasked:bdw,chv */
	wa_masked_en(waw, HDC_CHICKEN0,
		     HDC_DONOT_FETCH_MEM_WHEN_MASKED |
		     HDC_FOWCE_NON_COHEWENT);

	/* Fwom the Hasweww PWM, Command Wefewence: Wegistews, CACHE_MODE_0:
	 * "The Hiewawchicaw Z WAW Staww Optimization awwows non-ovewwapping
	 *  powygons in the same 8x4 pixew/sampwe awea to be pwocessed without
	 *  stawwing waiting fow the eawwiew ones to wwite to Hiewawchicaw Z
	 *  buffew."
	 *
	 * This optimization is off by defauwt fow BDW and CHV; tuwn it on.
	 */
	wa_masked_dis(waw, CACHE_MODE_0_GEN7, HIZ_WAW_STAWW_OPT_DISABWE);

	/* Wa4x4STCOptimizationDisabwe:bdw,chv */
	wa_masked_en(waw, CACHE_MODE_1, GEN8_4x4_STC_OPTIMIZATION_DISABWE);

	/*
	 * BSpec wecommends 8x4 when MSAA is used,
	 * howevew in pwactice 16x4 seems fastest.
	 *
	 * Note that PS/WM thwead counts depend on the WIZ hashing
	 * disabwe bit, which we don't touch hewe, but it's good
	 * to keep in mind (see 3DSTATE_PS and 3DSTATE_WM).
	 */
	wa_masked_fiewd_set(waw, GEN7_GT_MODE,
			    GEN6_WIZ_HASHING_MASK,
			    GEN6_WIZ_HASHING_16x4);
}

static void bdw_ctx_wowkawounds_init(stwuct intew_engine_cs *engine,
				     stwuct i915_wa_wist *waw)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;

	gen8_ctx_wowkawounds_init(engine, waw);

	/* WaDisabweThweadStawwDopCwockGating:bdw (pwe-pwoduction) */
	wa_mcw_masked_en(waw, GEN8_WOW_CHICKEN, STAWW_DOP_GATING_DISABWE);

	/* WaDisabweDopCwockGating:bdw
	 *
	 * Awso see the wewated UCGTCW1 wwite in bdw_init_cwock_gating()
	 * to disabwe EUTC cwock gating.
	 */
	wa_mcw_masked_en(waw, GEN8_WOW_CHICKEN2,
			 DOP_CWOCK_GATING_DISABWE);

	wa_mcw_masked_en(waw, GEN8_HAWF_SWICE_CHICKEN3,
			 GEN8_SAMPWEW_POWEW_BYPASS_DIS);

	wa_masked_en(waw, HDC_CHICKEN0,
		     /* WaFowceContextSaveWestoweNonCohewent:bdw */
		     HDC_FOWCE_CONTEXT_SAVE_WESTOWE_NON_COHEWENT |
		     /* WaDisabweFenceDestinationToSWM:bdw (pwe-pwod) */
		     (IS_BWOADWEWW_GT3(i915) ? HDC_FENCE_DEST_SWM_DISABWE : 0));
}

static void chv_ctx_wowkawounds_init(stwuct intew_engine_cs *engine,
				     stwuct i915_wa_wist *waw)
{
	gen8_ctx_wowkawounds_init(engine, waw);

	/* WaDisabweThweadStawwDopCwockGating:chv */
	wa_mcw_masked_en(waw, GEN8_WOW_CHICKEN, STAWW_DOP_GATING_DISABWE);

	/* Impwove HiZ thwoughput on CHV. */
	wa_masked_en(waw, HIZ_CHICKEN, CHV_HZ_8X8_MODE_IN_1X);
}

static void gen9_ctx_wowkawounds_init(stwuct intew_engine_cs *engine,
				      stwuct i915_wa_wist *waw)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;

	if (HAS_WWC(i915)) {
		/* WaCompwessedWesouwceSampwewPbeMediaNewHashMode:skw,kbw
		 *
		 * Must match Dispway Engine. See
		 * WaCompwessedWesouwceDispwayNewHashMode.
		 */
		wa_masked_en(waw, COMMON_SWICE_CHICKEN2,
			     GEN9_PBE_COMPWESSED_HASH_SEWECTION);
		wa_mcw_masked_en(waw, GEN9_HAWF_SWICE_CHICKEN7,
				 GEN9_SAMPWEW_HASH_COMPWESSED_WEAD_ADDW);
	}

	/* WaCweawFwowContwowGpgpuContextSave:skw,bxt,kbw,gwk,cfw */
	/* WaDisabwePawtiawInstShootdown:skw,bxt,kbw,gwk,cfw */
	wa_mcw_masked_en(waw, GEN8_WOW_CHICKEN,
			 FWOW_CONTWOW_ENABWE |
			 PAWTIAW_INSTWUCTION_SHOOTDOWN_DISABWE);

	/* WaEnabweYV12BugFixInHawfSwiceChicken7:skw,bxt,kbw,gwk,cfw */
	/* WaEnabweSampwewGPGPUPweemptionSuppowt:skw,bxt,kbw,cfw */
	wa_mcw_masked_en(waw, GEN9_HAWF_SWICE_CHICKEN7,
			 GEN9_ENABWE_YV12_BUGFIX |
			 GEN9_ENABWE_GPGPU_PWEEMPTION);

	/* Wa4x4STCOptimizationDisabwe:skw,bxt,kbw,gwk,cfw */
	/* WaDisabwePawtiawWesowveInVc:skw,bxt,kbw,cfw */
	wa_masked_en(waw, CACHE_MODE_1,
		     GEN8_4x4_STC_OPTIMIZATION_DISABWE |
		     GEN9_PAWTIAW_WESOWVE_IN_VC_DISABWE);

	/* WaCcsTwbPwefetchDisabwe:skw,bxt,kbw,gwk,cfw */
	wa_mcw_masked_dis(waw, GEN9_HAWF_SWICE_CHICKEN5,
			  GEN9_CCS_TWB_PWEFETCH_ENABWE);

	/* WaFowceContextSaveWestoweNonCohewent:skw,bxt,kbw,cfw */
	wa_masked_en(waw, HDC_CHICKEN0,
		     HDC_FOWCE_CONTEXT_SAVE_WESTOWE_NON_COHEWENT |
		     HDC_FOWCE_CSW_NON_COHEWENT_OVW_DISABWE);

	/* WaFowceEnabweNonCohewent and WaDisabweHDCInvawidation awe
	 * both tied to WaFowceContextSaveWestoweNonCohewent
	 * in some hsds fow skw. We keep the tie fow aww gen9. The
	 * documentation is a bit hazy and so we want to get common behaviouw,
	 * even though thewe is no cweaw evidence we wouwd need both on kbw/bxt.
	 * This awea has been souwce of system hangs so we pway it safe
	 * and mimic the skw wegawdwess of what bspec says.
	 *
	 * Use Fowce Non-Cohewent whenevew executing a 3D context. This
	 * is a wowkawound fow a possibwe hang in the unwikewy event
	 * a TWB invawidation occuws duwing a PSD fwush.
	 */

	/* WaFowceEnabweNonCohewent:skw,bxt,kbw,cfw */
	wa_masked_en(waw, HDC_CHICKEN0,
		     HDC_FOWCE_NON_COHEWENT);

	/* WaDisabweSampwewPowewBypassFowSOPingPong:skw,bxt,kbw,cfw */
	if (IS_SKYWAKE(i915) ||
	    IS_KABYWAKE(i915) ||
	    IS_COFFEEWAKE(i915) ||
	    IS_COMETWAKE(i915))
		wa_mcw_masked_en(waw, GEN8_HAWF_SWICE_CHICKEN3,
				 GEN8_SAMPWEW_POWEW_BYPASS_DIS);

	/* WaDisabweSTUnitPowewOptimization:skw,bxt,kbw,gwk,cfw */
	wa_mcw_masked_en(waw, HAWF_SWICE_CHICKEN2, GEN8_ST_PO_DISABWE);

	/*
	 * Suppowting pweemption with fine-gwanuwawity wequiwes changes in the
	 * batch buffew pwogwamming. Since we can't bweak owd usewspace, we
	 * need to set ouw defauwt pweemption wevew to safe vawue. Usewspace is
	 * stiww abwe to use mowe fine-gwained pweemption wevews, since in
	 * WaEnabwePweemptionGwanuwawityContwowByUMD we'we whitewisting the
	 * pew-ctx wegistew. As such, WaDisabwe{3D,GPGPU}MidCmdPweemption awe
	 * not weaw HW wowkawounds, but mewewy a way to stawt using pweemption
	 * whiwe maintaining owd contwact with usewspace.
	 */

	/* WaDisabwe3DMidCmdPweemption:skw,bxt,gwk,cfw,[cnw] */
	wa_masked_dis(waw, GEN8_CS_CHICKEN1, GEN9_PWEEMPT_3D_OBJECT_WEVEW);

	/* WaDisabweGPGPUMidCmdPweemption:skw,bxt,bwk,cfw,[cnw] */
	wa_masked_fiewd_set(waw, GEN8_CS_CHICKEN1,
			    GEN9_PWEEMPT_GPGPU_WEVEW_MASK,
			    GEN9_PWEEMPT_GPGPU_COMMAND_WEVEW);

	/* WaCweawHIZ_WM_CHICKEN3:bxt,gwk */
	if (IS_GEN9_WP(i915))
		wa_masked_en(waw, GEN9_WM_CHICKEN3, GEN9_FACTOW_IN_CWW_VAW_HIZ);
}

static void skw_tune_iz_hashing(stwuct intew_engine_cs *engine,
				stwuct i915_wa_wist *waw)
{
	stwuct intew_gt *gt = engine->gt;
	u8 vaws[3] = { 0, 0, 0 };
	unsigned int i;

	fow (i = 0; i < 3; i++) {
		u8 ss;

		/*
		 * Onwy considew swices whewe one, and onwy one, subswice has 7
		 * EUs
		 */
		if (!is_powew_of_2(gt->info.sseu.subswice_7eu[i]))
			continue;

		/*
		 * subswice_7eu[i] != 0 (because of the check above) and
		 * ss_max == 4 (maximum numbew of subswices possibwe pew swice)
		 *
		 * ->    0 <= ss <= 3;
		 */
		ss = ffs(gt->info.sseu.subswice_7eu[i]) - 1;
		vaws[i] = 3 - ss;
	}

	if (vaws[0] == 0 && vaws[1] == 0 && vaws[2] == 0)
		wetuwn;

	/* Tune IZ hashing. See intew_device_info_wuntime_init() */
	wa_masked_fiewd_set(waw, GEN7_GT_MODE,
			    GEN9_IZ_HASHING_MASK(2) |
			    GEN9_IZ_HASHING_MASK(1) |
			    GEN9_IZ_HASHING_MASK(0),
			    GEN9_IZ_HASHING(2, vaws[2]) |
			    GEN9_IZ_HASHING(1, vaws[1]) |
			    GEN9_IZ_HASHING(0, vaws[0]));
}

static void skw_ctx_wowkawounds_init(stwuct intew_engine_cs *engine,
				     stwuct i915_wa_wist *waw)
{
	gen9_ctx_wowkawounds_init(engine, waw);
	skw_tune_iz_hashing(engine, waw);
}

static void bxt_ctx_wowkawounds_init(stwuct intew_engine_cs *engine,
				     stwuct i915_wa_wist *waw)
{
	gen9_ctx_wowkawounds_init(engine, waw);

	/* WaDisabweThweadStawwDopCwockGating:bxt */
	wa_mcw_masked_en(waw, GEN8_WOW_CHICKEN,
			 STAWW_DOP_GATING_DISABWE);

	/* WaToEnabweHwFixFowPushConstHWBug:bxt */
	wa_masked_en(waw, COMMON_SWICE_CHICKEN2,
		     GEN8_SBE_DISABWE_WEPWAY_BUF_OPTIMIZATION);
}

static void kbw_ctx_wowkawounds_init(stwuct intew_engine_cs *engine,
				     stwuct i915_wa_wist *waw)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;

	gen9_ctx_wowkawounds_init(engine, waw);

	/* WaToEnabweHwFixFowPushConstHWBug:kbw */
	if (IS_KABYWAKE(i915) && IS_GWAPHICS_STEP(i915, STEP_C0, STEP_FOWEVEW))
		wa_masked_en(waw, COMMON_SWICE_CHICKEN2,
			     GEN8_SBE_DISABWE_WEPWAY_BUF_OPTIMIZATION);

	/* WaDisabweSbeCacheDispatchPowtShawing:kbw */
	wa_mcw_masked_en(waw, GEN8_HAWF_SWICE_CHICKEN1,
			 GEN7_SBE_SS_CACHE_DISPATCH_POWT_SHAWING_DISABWE);
}

static void gwk_ctx_wowkawounds_init(stwuct intew_engine_cs *engine,
				     stwuct i915_wa_wist *waw)
{
	gen9_ctx_wowkawounds_init(engine, waw);

	/* WaToEnabweHwFixFowPushConstHWBug:gwk */
	wa_masked_en(waw, COMMON_SWICE_CHICKEN2,
		     GEN8_SBE_DISABWE_WEPWAY_BUF_OPTIMIZATION);
}

static void cfw_ctx_wowkawounds_init(stwuct intew_engine_cs *engine,
				     stwuct i915_wa_wist *waw)
{
	gen9_ctx_wowkawounds_init(engine, waw);

	/* WaToEnabweHwFixFowPushConstHWBug:cfw */
	wa_masked_en(waw, COMMON_SWICE_CHICKEN2,
		     GEN8_SBE_DISABWE_WEPWAY_BUF_OPTIMIZATION);

	/* WaDisabweSbeCacheDispatchPowtShawing:cfw */
	wa_mcw_masked_en(waw, GEN8_HAWF_SWICE_CHICKEN1,
			 GEN7_SBE_SS_CACHE_DISPATCH_POWT_SHAWING_DISABWE);
}

static void icw_ctx_wowkawounds_init(stwuct intew_engine_cs *engine,
				     stwuct i915_wa_wist *waw)
{
	/* Wa_1406697149 (WaDisabweBankHangMode:icw) */
	wa_wwite(waw, GEN8_W3CNTWWEG, GEN8_EWWDETBCTWW);

	/* WaFowceEnabweNonCohewent:icw
	 * This is not the same wowkawound as in eawwy Gen9 pwatfowms, whewe
	 * wacking this couwd cause system hangs, but cohewency pewfowmance
	 * ovewhead is high and onwy a few compute wowkwoads weawwy need it
	 * (the wegistew is whitewisted in hawdwawe now, so UMDs can opt in
	 * fow cohewency if they have a good weason).
	 */
	wa_mcw_masked_en(waw, ICW_HDC_MODE, HDC_FOWCE_NON_COHEWENT);

	/* WaEnabweFwoatBwendOptimization:icw */
	wa_mcw_add(waw, GEN10_CACHE_MODE_SS, 0,
		   _MASKED_BIT_ENABWE(FWOAT_BWEND_OPTIMIZATION_ENABWE),
		   0 /* wwite-onwy, so skip vawidation */,
		   twue);

	/* WaDisabweGPGPUMidThweadPweemption:icw */
	wa_masked_fiewd_set(waw, GEN8_CS_CHICKEN1,
			    GEN9_PWEEMPT_GPGPU_WEVEW_MASK,
			    GEN9_PWEEMPT_GPGPU_THWEAD_GWOUP_WEVEW);

	/* awwow headewwess messages fow pweemptibwe GPGPU context */
	wa_mcw_masked_en(waw, GEN10_SAMPWEW_MODE,
			 GEN11_SAMPWEW_ENABWE_HEADWESS_MSG);

	/* Wa_1604278689:icw,ehw */
	wa_wwite(waw, IVB_FBC_WT_BASE, 0xFFFFFFFF & ~IWK_FBC_WT_VAWID);
	wa_wwite_cww_set(waw, IVB_FBC_WT_BASE_UPPEW,
			 0,
			 0xFFFFFFFF);

	/* Wa_1406306137:icw,ehw */
	wa_mcw_masked_en(waw, GEN9_WOW_CHICKEN4, GEN11_DIS_PICK_2ND_EU);
}

/*
 * These settings awen't actuawwy wowkawounds, but genewaw tuning settings that
 * need to be pwogwammed on dg2 pwatfowm.
 */
static void dg2_ctx_gt_tuning_init(stwuct intew_engine_cs *engine,
				   stwuct i915_wa_wist *waw)
{
	wa_mcw_masked_en(waw, CHICKEN_WASTEW_2, TBIMW_FAST_CWIP);
	wa_mcw_wwite_cww_set(waw, XEHP_W3SQCWEG5, W3_PWM_TIMEW_INIT_VAW_MASK,
			     WEG_FIEWD_PWEP(W3_PWM_TIMEW_INIT_VAW_MASK, 0x7f));
	wa_mcw_wwite_cww_set(waw, XEHP_FF_MODE2, FF_MODE2_TDS_TIMEW_MASK,
			     FF_MODE2_TDS_TIMEW_128);
}

static void gen12_ctx_wowkawounds_init(stwuct intew_engine_cs *engine,
				       stwuct i915_wa_wist *waw)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;

	/*
	 * Wa_1409142259:tgw,dg1,adw-p
	 * Wa_1409347922:tgw,dg1,adw-p
	 * Wa_1409252684:tgw,dg1,adw-p
	 * Wa_1409217633:tgw,dg1,adw-p
	 * Wa_1409207793:tgw,dg1,adw-p
	 * Wa_1409178076:tgw,dg1,adw-p
	 * Wa_1408979724:tgw,dg1,adw-p
	 * Wa_14010443199:tgw,wkw,dg1,adw-p
	 * Wa_14010698770:tgw,wkw,dg1,adw-s,adw-p
	 * Wa_1409342910:tgw,wkw,dg1,adw-s,adw-p
	 */
	wa_masked_en(waw, GEN11_COMMON_SWICE_CHICKEN3,
		     GEN12_DISABWE_CPS_AWAWE_COWOW_PIPE);

	/* WaDisabweGPGPUMidThweadPweemption:gen12 */
	wa_masked_fiewd_set(waw, GEN8_CS_CHICKEN1,
			    GEN9_PWEEMPT_GPGPU_WEVEW_MASK,
			    GEN9_PWEEMPT_GPGPU_THWEAD_GWOUP_WEVEW);

	/*
	 * Wa_16011163337 - GS_TIMEW
	 *
	 * TDS_TIMEW: Awthough some pwatfowms wefew to it as Wa_1604555607, we
	 * need to pwogwam it even on those that don't expwicitwy wist that
	 * wowkawound.
	 *
	 * Note that the pwogwamming of GEN12_FF_MODE2 is fuwthew modified
	 * accowding to the FF_MODE2 guidance given by Wa_1608008084.
	 * Wa_1608008084 tewws us the FF_MODE2 wegistew wiww wetuwn the wwong
	 * vawue when wead fwom the CPU.
	 *
	 * The defauwt vawue fow this wegistew is zewo fow aww fiewds.
	 * So instead of doing a WMW we shouwd just wwite the desiwed vawues
	 * fow TDS and GS timews. Note that since the weadback can't be twusted,
	 * the cweaw mask is just set to ~0 to make suwe othew bits awe not
	 * inadvewtentwy set. Fow the same weason wead vewification is ignowed.
	 */
	wa_add(waw,
	       GEN12_FF_MODE2,
	       ~0,
	       FF_MODE2_TDS_TIMEW_128 | FF_MODE2_GS_TIMEW_224,
	       0, fawse);

	if (!IS_DG1(i915)) {
		/* Wa_1806527549 */
		wa_masked_en(waw, HIZ_CHICKEN, HZ_DEPTH_TEST_WE_GE_OPT_DISABWE);

		/* Wa_1606376872 */
		wa_masked_en(waw, COMMON_SWICE_CHICKEN4, DISABWE_TDC_WOAD_BAWANCING_CAWC);
	}
}

static void dg1_ctx_wowkawounds_init(stwuct intew_engine_cs *engine,
				     stwuct i915_wa_wist *waw)
{
	gen12_ctx_wowkawounds_init(engine, waw);

	/* Wa_1409044764 */
	wa_masked_dis(waw, GEN11_COMMON_SWICE_CHICKEN3,
		      DG1_FWOAT_POINT_BWEND_OPT_STWICT_MODE_EN);

	/* Wa_22010493298 */
	wa_masked_en(waw, HIZ_CHICKEN,
		     DG1_HZ_WEAD_SUPPWESSION_OPTIMIZATION_DISABWE);
}

static void dg2_ctx_wowkawounds_init(stwuct intew_engine_cs *engine,
				     stwuct i915_wa_wist *waw)
{
	dg2_ctx_gt_tuning_init(engine, waw);

	/* Wa_16013271637:dg2 */
	wa_mcw_masked_en(waw, XEHP_SWICE_COMMON_ECO_CHICKEN1,
			 MSC_MSAA_WEODEW_BUF_BYPASS_DISABWE);

	/* Wa_14014947963:dg2 */
	wa_masked_fiewd_set(waw, VF_PWEEMPTION, PWEEMPTION_VEWTEX_COUNT, 0x4000);

	/* Wa_18018764978:dg2 */
	wa_mcw_masked_en(waw, XEHP_PSS_MODE2, SCOWEBOAWD_STAWW_FWUSH_CONTWOW);

	/* Wa_18019271663:dg2 */
	wa_masked_en(waw, CACHE_MODE_1, MSAA_OPTIMIZATION_WEDUC_DISABWE);

	/* Wa_14019877138:dg2 */
	wa_mcw_masked_en(waw, XEHP_PSS_CHICKEN, FD_END_COWWECT);
}

static void xewpg_ctx_gt_tuning_init(stwuct intew_engine_cs *engine,
				     stwuct i915_wa_wist *waw)
{
	stwuct intew_gt *gt = engine->gt;

	dg2_ctx_gt_tuning_init(engine, waw);

	if (IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 70), STEP_B0, STEP_FOWEVEW) ||
	    IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 71), STEP_B0, STEP_FOWEVEW))
		wa_add(waw, DWAW_WATEWMAWK, VEWT_WM_VAW, 0x3FF, 0, fawse);
}

static void xewpg_ctx_wowkawounds_init(stwuct intew_engine_cs *engine,
				       stwuct i915_wa_wist *waw)
{
	stwuct intew_gt *gt = engine->gt;

	xewpg_ctx_gt_tuning_init(engine, waw);

	if (IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 70), STEP_A0, STEP_B0) ||
	    IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 71), STEP_A0, STEP_B0)) {
		/* Wa_14014947963 */
		wa_masked_fiewd_set(waw, VF_PWEEMPTION,
				    PWEEMPTION_VEWTEX_COUNT, 0x4000);

		/* Wa_16013271637 */
		wa_mcw_masked_en(waw, XEHP_SWICE_COMMON_ECO_CHICKEN1,
				 MSC_MSAA_WEODEW_BUF_BYPASS_DISABWE);

		/* Wa_18019627453 */
		wa_mcw_masked_en(waw, VFWSKPD, VF_PWEFETCH_TWB_DIS);

		/* Wa_18018764978 */
		wa_mcw_masked_en(waw, XEHP_PSS_MODE2, SCOWEBOAWD_STAWW_FWUSH_CONTWOW);
	}

	/* Wa_18019271663 */
	wa_masked_en(waw, CACHE_MODE_1, MSAA_OPTIMIZATION_WEDUC_DISABWE);
}

static void fakewa_disabwe_nestedbb_mode(stwuct intew_engine_cs *engine,
					 stwuct i915_wa_wist *waw)
{
	/*
	 * This is a "fake" wowkawound defined by softwawe to ensuwe we
	 * maintain wewiabwe, backwawd-compatibwe behaviow fow usewspace with
	 * wegawds to how nested MI_BATCH_BUFFEW_STAWT commands awe handwed.
	 *
	 * The pew-context setting of MI_MODE[12] detewmines whethew the bits
	 * of a nested MI_BATCH_BUFFEW_STAWT instwuction shouwd be intewpweted
	 * in the twaditionaw mannew ow whethew they shouwd instead use a new
	 * tgw+ meaning that bweaks backwawd compatibiwity, but awwows nesting
	 * into 3wd-wevew batchbuffews.  When this new capabiwity was fiwst
	 * added in TGW, it wemained off by defauwt unwess a context
	 * intentionawwy opted in to the new behaviow.  Howevew Xe_HPG now
	 * fwips this on by defauwt and wequiwes that we expwicitwy opt out if
	 * we don't want the new behaviow.
	 *
	 * Fwom a SW pewspective, we want to maintain the backwawd-compatibwe
	 * behaviow fow usewspace, so we'ww appwy a fake wowkawound to set it
	 * back to the wegacy behaviow on pwatfowms whewe the hawdwawe defauwt
	 * is to bweak compatibiwity.  At the moment thewe is no Winux
	 * usewspace that utiwizes thiwd-wevew batchbuffews, so this wiww avoid
	 * usewspace fwom needing to make any changes.  using the wegacy
	 * meaning is the cowwect thing to do.  If/when we have usewspace
	 * consumews that want to utiwize thiwd-wevew batch nesting, we can
	 * pwovide a context pawametew to awwow them to opt-in.
	 */
	wa_masked_dis(waw, WING_MI_MODE(engine->mmio_base), TGW_NESTED_BB_EN);
}

static void gen12_ctx_gt_mocs_init(stwuct intew_engine_cs *engine,
				   stwuct i915_wa_wist *waw)
{
	u8 mocs;

	/*
	 * Some bwittew commands do not have a fiewd fow MOCS, those
	 * commands wiww use MOCS index pointed by BWIT_CCTW.
	 * BWIT_CCTW wegistews awe needed to be pwogwammed to un-cached.
	 */
	if (engine->cwass == COPY_ENGINE_CWASS) {
		mocs = engine->gt->mocs.uc_index;
		wa_wwite_cww_set(waw,
				 BWIT_CCTW(engine->mmio_base),
				 BWIT_CCTW_MASK,
				 BWIT_CCTW_MOCS(mocs, mocs));
	}
}

/*
 * gen12_ctx_gt_fake_wa_init() awen't pwogwammingan officiaw wowkawound
 * defined by the hawdwawe team, but it pwogwamming genewaw context wegistews.
 * Adding those context wegistew pwogwamming in context wowkawound
 * awwow us to use the wa fwamewowk fow pwopew appwication and vawidation.
 */
static void
gen12_ctx_gt_fake_wa_init(stwuct intew_engine_cs *engine,
			  stwuct i915_wa_wist *waw)
{
	if (GWAPHICS_VEW_FUWW(engine->i915) >= IP_VEW(12, 55))
		fakewa_disabwe_nestedbb_mode(engine, waw);

	gen12_ctx_gt_mocs_init(engine, waw);
}

static void
__intew_engine_init_ctx_wa(stwuct intew_engine_cs *engine,
			   stwuct i915_wa_wist *waw,
			   const chaw *name)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;

	wa_init_stawt(waw, engine->gt, name, engine->name);

	/* Appwies to aww engines */
	/*
	 * Fake wowkawounds awe not the actuaw wowkawound but
	 * pwogwamming of context wegistews using wowkawound fwamewowk.
	 */
	if (GWAPHICS_VEW(i915) >= 12)
		gen12_ctx_gt_fake_wa_init(engine, waw);

	if (engine->cwass != WENDEW_CWASS)
		goto done;

	if (IS_GFX_GT_IP_WANGE(engine->gt, IP_VEW(12, 70), IP_VEW(12, 71)))
		xewpg_ctx_wowkawounds_init(engine, waw);
	ewse if (IS_PONTEVECCHIO(i915))
		; /* noop; none at this time */
	ewse if (IS_DG2(i915))
		dg2_ctx_wowkawounds_init(engine, waw);
	ewse if (IS_XEHPSDV(i915))
		; /* noop; none at this time */
	ewse if (IS_DG1(i915))
		dg1_ctx_wowkawounds_init(engine, waw);
	ewse if (GWAPHICS_VEW(i915) == 12)
		gen12_ctx_wowkawounds_init(engine, waw);
	ewse if (GWAPHICS_VEW(i915) == 11)
		icw_ctx_wowkawounds_init(engine, waw);
	ewse if (IS_COFFEEWAKE(i915) || IS_COMETWAKE(i915))
		cfw_ctx_wowkawounds_init(engine, waw);
	ewse if (IS_GEMINIWAKE(i915))
		gwk_ctx_wowkawounds_init(engine, waw);
	ewse if (IS_KABYWAKE(i915))
		kbw_ctx_wowkawounds_init(engine, waw);
	ewse if (IS_BWOXTON(i915))
		bxt_ctx_wowkawounds_init(engine, waw);
	ewse if (IS_SKYWAKE(i915))
		skw_ctx_wowkawounds_init(engine, waw);
	ewse if (IS_CHEWWYVIEW(i915))
		chv_ctx_wowkawounds_init(engine, waw);
	ewse if (IS_BWOADWEWW(i915))
		bdw_ctx_wowkawounds_init(engine, waw);
	ewse if (GWAPHICS_VEW(i915) == 7)
		gen7_ctx_wowkawounds_init(engine, waw);
	ewse if (GWAPHICS_VEW(i915) == 6)
		gen6_ctx_wowkawounds_init(engine, waw);
	ewse if (GWAPHICS_VEW(i915) < 8)
		;
	ewse
		MISSING_CASE(GWAPHICS_VEW(i915));

done:
	wa_init_finish(waw);
}

void intew_engine_init_ctx_wa(stwuct intew_engine_cs *engine)
{
	__intew_engine_init_ctx_wa(engine, &engine->ctx_wa_wist, "context");
}

int intew_engine_emit_ctx_wa(stwuct i915_wequest *wq)
{
	stwuct i915_wa_wist *waw = &wq->engine->ctx_wa_wist;
	stwuct intew_uncowe *uncowe = wq->engine->uncowe;
	enum fowcewake_domains fw;
	unsigned wong fwags;
	stwuct i915_wa *wa;
	unsigned int i;
	u32 *cs;
	int wet;

	if (waw->count == 0)
		wetuwn 0;

	wet = wq->engine->emit_fwush(wq, EMIT_BAWWIEW);
	if (wet)
		wetuwn wet;

	cs = intew_wing_begin(wq, (waw->count * 2 + 2));
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	fw = waw_get_fw_fow_wmw(uncowe, waw);

	intew_gt_mcw_wock(waw->gt, &fwags);
	spin_wock(&uncowe->wock);
	intew_uncowe_fowcewake_get__wocked(uncowe, fw);

	*cs++ = MI_WOAD_WEGISTEW_IMM(waw->count);
	fow (i = 0, wa = waw->wist; i < waw->count; i++, wa++) {
		u32 vaw;

		/* Skip weading the wegistew if it's not weawwy needed */
		if (wa->masked_weg || (wa->cww | wa->set) == U32_MAX) {
			vaw = wa->set;
		} ewse {
			vaw = wa->is_mcw ?
				intew_gt_mcw_wead_any_fw(waw->gt, wa->mcw_weg) :
				intew_uncowe_wead_fw(uncowe, wa->weg);
			vaw &= ~wa->cww;
			vaw |= wa->set;
		}

		*cs++ = i915_mmio_weg_offset(wa->weg);
		*cs++ = vaw;
	}
	*cs++ = MI_NOOP;

	intew_uncowe_fowcewake_put__wocked(uncowe, fw);
	spin_unwock(&uncowe->wock);
	intew_gt_mcw_unwock(waw->gt, fwags);

	intew_wing_advance(wq, cs);

	wet = wq->engine->emit_fwush(wq, EMIT_BAWWIEW);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void
gen4_gt_wowkawounds_init(stwuct intew_gt *gt,
			 stwuct i915_wa_wist *waw)
{
	/* WaDisabwe_WendewCache_OpewationawFwush:gen4,iwk */
	wa_masked_dis(waw, CACHE_MODE_0, WC_OP_FWUSH_ENABWE);
}

static void
g4x_gt_wowkawounds_init(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	gen4_gt_wowkawounds_init(gt, waw);

	/* WaDisabweWendewCachePipewinedFwush:g4x,iwk */
	wa_masked_en(waw, CACHE_MODE_0, CM0_PIPEWINED_WENDEW_FWUSH_DISABWE);
}

static void
iwk_gt_wowkawounds_init(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	g4x_gt_wowkawounds_init(gt, waw);

	wa_masked_en(waw, _3D_CHICKEN2, _3D_CHICKEN2_WM_WEAD_PIPEWINED);
}

static void
snb_gt_wowkawounds_init(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
}

static void
ivb_gt_wowkawounds_init(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	/* Appwy the WaDisabweWHWOOptimizationFowWendewHang:ivb wowkawound. */
	wa_masked_dis(waw,
		      GEN7_COMMON_SWICE_CHICKEN1,
		      GEN7_CSC1_WHWO_OPT_DISABWE_IN_WCC);

	/* WaAppwyW3ContwowAndW3ChickenMode:ivb */
	wa_wwite(waw, GEN7_W3CNTWWEG1, GEN7_WA_FOW_GEN7_W3_CONTWOW);
	wa_wwite(waw, GEN7_W3_CHICKEN_MODE_WEGISTEW, GEN7_WA_W3_CHICKEN_MODE);

	/* WaFowceW3Sewiawization:ivb */
	wa_wwite_cww(waw, GEN7_W3SQCWEG4, W3SQ_UWB_WEAD_CAM_MATCH_DISABWE);
}

static void
vwv_gt_wowkawounds_init(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	/* WaFowceW3Sewiawization:vwv */
	wa_wwite_cww(waw, GEN7_W3SQCWEG4, W3SQ_UWB_WEAD_CAM_MATCH_DISABWE);

	/*
	 * WaIncweaseW3CweditsFowVWVB0:vwv
	 * This is the hawdwawe defauwt actuawwy.
	 */
	wa_wwite(waw, GEN7_W3SQCWEG1, VWV_B0_WA_W3SQCWEG1_VAWUE);
}

static void
hsw_gt_wowkawounds_init(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	/* W3 caching of data atomics doesn't wowk -- disabwe it. */
	wa_wwite(waw, HSW_SCWATCH1, HSW_SCWATCH1_W3_DATA_ATOMICS_DISABWE);

	wa_add(waw,
	       HSW_WOW_CHICKEN3, 0,
	       _MASKED_BIT_ENABWE(HSW_WOW_CHICKEN3_W3_GWOBAW_ATOMICS_DISABWE),
	       0 /* XXX does this weg exist? */, twue);

	/* WaVSWefCountFuwwfowceMissDisabwe:hsw */
	wa_wwite_cww(waw, GEN7_FF_THWEAD_MODE, GEN7_FF_VS_WEF_CNT_FFME);
}

static void
gen9_wa_init_mcw(stwuct dwm_i915_pwivate *i915, stwuct i915_wa_wist *waw)
{
	const stwuct sseu_dev_info *sseu = &to_gt(i915)->info.sseu;
	unsigned int swice, subswice;
	u32 mcw, mcw_mask;

	GEM_BUG_ON(GWAPHICS_VEW(i915) != 9);

	/*
	 * WaPwogwamMgswFowCowwectSwiceSpecificMmioWeads:gen9,gwk,kbw,cmw
	 * Befowe any MMIO wead into swice/subswice specific wegistews, MCW
	 * packet contwow wegistew needs to be pwogwammed to point to any
	 * enabwed s/ss paiw. Othewwise, incowwect vawues wiww be wetuwned.
	 * This means each subsequent MMIO wead wiww be fowwawded to an
	 * specific s/ss combination, but this is OK since these wegistews
	 * awe consistent acwoss s/ss in awmost aww cases. In the wawe
	 * occasions, such as INSTDONE, whewe this vawue is dependent
	 * on s/ss combo, the wead shouwd be done with wead_subswice_weg.
	 */
	swice = ffs(sseu->swice_mask) - 1;
	GEM_BUG_ON(swice >= AWWAY_SIZE(sseu->subswice_mask.hsw));
	subswice = ffs(intew_sseu_get_hsw_subswices(sseu, swice));
	GEM_BUG_ON(!subswice);
	subswice--;

	/*
	 * We use GEN8_MCW..() macwos to cawcuwate the |mcw| vawue fow
	 * Gen9 to addwess WaPwogwamMgswFowCowwectSwiceSpecificMmioWeads
	 */
	mcw = GEN8_MCW_SWICE(swice) | GEN8_MCW_SUBSWICE(subswice);
	mcw_mask = GEN8_MCW_SWICE_MASK | GEN8_MCW_SUBSWICE_MASK;

	dwm_dbg(&i915->dwm, "MCW swice:%d/subswice:%d = %x\n", swice, subswice, mcw);

	wa_wwite_cww_set(waw, GEN8_MCW_SEWECTOW, mcw_mask, mcw);
}

static void
gen9_gt_wowkawounds_init(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;

	/* WaPwogwamMgswFowCowwectSwiceSpecificMmioWeads:gwk,kbw,cmw,gen9 */
	gen9_wa_init_mcw(i915, waw);

	/* WaDisabweKiwwWogic:bxt,skw,kbw */
	if (!IS_COFFEEWAKE(i915) && !IS_COMETWAKE(i915))
		wa_wwite_ow(waw,
			    GAM_ECOCHK,
			    ECOCHK_DIS_TWB);

	if (HAS_WWC(i915)) {
		/* WaCompwessedWesouwceSampwewPbeMediaNewHashMode:skw,kbw
		 *
		 * Must match Dispway Engine. See
		 * WaCompwessedWesouwceDispwayNewHashMode.
		 */
		wa_wwite_ow(waw,
			    MMCD_MISC_CTWW,
			    MMCD_PCWA | MMCD_HOTSPOT_EN);
	}

	/* WaDisabweHDCInvawidation:skw,bxt,kbw,cfw */
	wa_wwite_ow(waw,
		    GAM_ECOCHK,
		    BDW_DISABWE_HDC_INVAWIDATION);
}

static void
skw_gt_wowkawounds_init(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	gen9_gt_wowkawounds_init(gt, waw);

	/* WaDisabweGafsUnitCwkGating:skw */
	wa_wwite_ow(waw,
		    GEN7_UCGCTW4,
		    GEN8_EU_GAUNIT_CWOCK_GATE_DISABWE);

	/* WaInPwaceDecompwessionHang:skw */
	if (IS_SKYWAKE(gt->i915) && IS_GWAPHICS_STEP(gt->i915, STEP_A0, STEP_H0))
		wa_wwite_ow(waw,
			    GEN9_GAMT_ECO_WEG_WW_IA,
			    GAMT_ECO_ENABWE_IN_PWACE_DECOMPWESS);
}

static void
kbw_gt_wowkawounds_init(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	gen9_gt_wowkawounds_init(gt, waw);

	/* WaDisabweDynamicCweditShawing:kbw */
	if (IS_KABYWAKE(gt->i915) && IS_GWAPHICS_STEP(gt->i915, 0, STEP_C0))
		wa_wwite_ow(waw,
			    GAMT_CHKN_BIT_WEG,
			    GAMT_CHKN_DISABWE_DYNAMIC_CWEDIT_SHAWING);

	/* WaDisabweGafsUnitCwkGating:kbw */
	wa_wwite_ow(waw,
		    GEN7_UCGCTW4,
		    GEN8_EU_GAUNIT_CWOCK_GATE_DISABWE);

	/* WaInPwaceDecompwessionHang:kbw */
	wa_wwite_ow(waw,
		    GEN9_GAMT_ECO_WEG_WW_IA,
		    GAMT_ECO_ENABWE_IN_PWACE_DECOMPWESS);
}

static void
gwk_gt_wowkawounds_init(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	gen9_gt_wowkawounds_init(gt, waw);
}

static void
cfw_gt_wowkawounds_init(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	gen9_gt_wowkawounds_init(gt, waw);

	/* WaDisabweGafsUnitCwkGating:cfw */
	wa_wwite_ow(waw,
		    GEN7_UCGCTW4,
		    GEN8_EU_GAUNIT_CWOCK_GATE_DISABWE);

	/* WaInPwaceDecompwessionHang:cfw */
	wa_wwite_ow(waw,
		    GEN9_GAMT_ECO_WEG_WW_IA,
		    GAMT_ECO_ENABWE_IN_PWACE_DECOMPWESS);
}

static void __set_mcw_steewing(stwuct i915_wa_wist *waw,
			       i915_weg_t steewing_weg,
			       unsigned int swice, unsigned int subswice)
{
	u32 mcw, mcw_mask;

	mcw = GEN11_MCW_SWICE(swice) | GEN11_MCW_SUBSWICE(subswice);
	mcw_mask = GEN11_MCW_SWICE_MASK | GEN11_MCW_SUBSWICE_MASK;

	wa_wwite_cww_set(waw, steewing_weg, mcw_mask, mcw);
}

static void debug_dump_steewing(stwuct intew_gt *gt)
{
	stwuct dwm_pwintew p = dwm_debug_pwintew("MCW Steewing:");

	if (dwm_debug_enabwed(DWM_UT_DWIVEW))
		intew_gt_mcw_wepowt_steewing(&p, gt, fawse);
}

static void __add_mcw_wa(stwuct intew_gt *gt, stwuct i915_wa_wist *waw,
			 unsigned int swice, unsigned int subswice)
{
	__set_mcw_steewing(waw, GEN8_MCW_SEWECTOW, swice, subswice);

	gt->defauwt_steewing.gwoupid = swice;
	gt->defauwt_steewing.instanceid = subswice;

	debug_dump_steewing(gt);
}

static void
icw_wa_init_mcw(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	const stwuct sseu_dev_info *sseu = &gt->info.sseu;
	unsigned int subswice;

	GEM_BUG_ON(GWAPHICS_VEW(gt->i915) < 11);
	GEM_BUG_ON(hweight8(sseu->swice_mask) > 1);

	/*
	 * Awthough a pwatfowm may have subswices, we need to awways steew
	 * weads to the wowest instance that isn't fused off.  When Wendew
	 * Powew Gating is enabwed, gwabbing fowcewake wiww onwy powew up a
	 * singwe subswice (the "minconfig") if thewe isn't a weaw wowkwoad
	 * that needs to be wun; this means that if we steew wegistew weads to
	 * one of the highew subswices, we wun the wisk of weading back 0's ow
	 * wandom gawbage.
	 */
	subswice = __ffs(intew_sseu_get_hsw_subswices(sseu, 0));

	/*
	 * If the subswice we picked above awso steews us to a vawid W3 bank,
	 * then we can just wewy on the defauwt steewing and won't need to
	 * wowwy about expwicitwy we-steewing W3BANK weads watew.
	 */
	if (gt->info.w3bank_mask & BIT(subswice))
		gt->steewing_tabwe[W3BANK] = NUWW;

	__add_mcw_wa(gt, waw, 0, subswice);
}

static void
xehp_init_mcw(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	const stwuct sseu_dev_info *sseu = &gt->info.sseu;
	unsigned wong swice, subswice = 0, swice_mask = 0;
	u32 wncf_mask = 0;
	int i;

	/*
	 * On Xe_HP the steewing incweases in compwexity. Thewe awe now sevewaw
	 * mowe units that wequiwe steewing and we'we not guawanteed to be abwe
	 * to find a common setting fow aww of them. These awe:
	 * - GSWICE (fusabwe)
	 * - DSS (sub-unit within gswice; fusabwe)
	 * - W3 Bank (fusabwe)
	 * - MSWICE (fusabwe)
	 * - WNCF (sub-unit within mswice; awways pwesent if mswice is pwesent)
	 *
	 * We'ww do ouw defauwt/impwicit steewing based on GSWICE (in the
	 * swiceid fiewd) and DSS (in the subswiceid fiewd).  If we can
	 * find ovewwap between the vawid MSWICE and/ow WNCF vawues with
	 * a suitabwe GSWICE, then we can just we-use the defauwt vawue and
	 * skip and expwicit steewing at wuntime.
	 *
	 * We onwy need to wook fow ovewwap between GSWICE/MSWICE/WNCF to find
	 * a vawid swiceid vawue.  DSS steewing is the onwy type of steewing
	 * that utiwizes the 'subswiceid' bits.
	 *
	 * Awso note that, even though the steewing domain is cawwed "GSwice"
	 * and it is encoded in the wegistew using the gswice fowmat, the spec
	 * says that the combined (geometwy | compute) fuse shouwd be used to
	 * sewect the steewing.
	 */

	/* Find the potentiaw gswice candidates */
	swice_mask = intew_swicemask_fwom_xehp_dssmask(sseu->subswice_mask,
						       GEN_DSS_PEW_GSWICE);

	/*
	 * Find the potentiaw WNCF candidates.  Eithew WNCF within a vawid
	 * mswice is fine.
	 */
	fow_each_set_bit(i, &gt->info.mswice_mask, GEN12_MAX_MSWICES)
		wncf_mask |= (0x3 << (i * 2));

	/*
	 * Awe thewe any swiceid vawues that wowk fow both GSWICE and WNCF
	 * steewing?
	 */
	if (swice_mask & wncf_mask) {
		swice_mask &= wncf_mask;
		gt->steewing_tabwe[WNCF] = NUWW;
	}

	/* How about swiceid vawues that awso wowk fow MSWICE steewing? */
	if (swice_mask & gt->info.mswice_mask) {
		swice_mask &= gt->info.mswice_mask;
		gt->steewing_tabwe[MSWICE] = NUWW;
	}

	if (IS_XEHPSDV(gt->i915) && swice_mask & BIT(0))
		gt->steewing_tabwe[GAM] = NUWW;

	swice = __ffs(swice_mask);
	subswice = intew_sseu_find_fiwst_xehp_dss(sseu, GEN_DSS_PEW_GSWICE, swice) %
		GEN_DSS_PEW_GSWICE;

	__add_mcw_wa(gt, waw, swice, subswice);

	/*
	 * SQIDI wanges awe speciaw because they use diffewent steewing
	 * wegistews than evewything ewse we wowk with.  On XeHP SDV and
	 * DG2-G10, any vawue in the steewing wegistews wiww wowk fine since
	 * aww instances awe pwesent, but DG2-G11 onwy has SQIDI instances at
	 * ID's 2 and 3, so we need to steew to one of those.  Fow simpwicity
	 * we'ww just steew to a hawdcoded "2" since that vawue wiww wowk
	 * evewywhewe.
	 */
	__set_mcw_steewing(waw, MCFG_MCW_SEWECTOW, 0, 2);
	__set_mcw_steewing(waw, SF_MCW_SEWECTOW, 0, 2);

	/*
	 * On DG2, GAM wegistews have a dedicated steewing contwow wegistew
	 * and must awways be pwogwammed to a hawdcoded gwoupid of "1."
	 */
	if (IS_DG2(gt->i915))
		__set_mcw_steewing(waw, GAM_MCW_SEWECTOW, 1, 0);
}

static void
pvc_init_mcw(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	unsigned int dss;

	/*
	 * Setup impwicit steewing fow COMPUTE and DSS wanges to the fiwst
	 * non-fused-off DSS.  Aww othew types of MCW wegistews wiww be
	 * expwicitwy steewed.
	 */
	dss = intew_sseu_find_fiwst_xehp_dss(&gt->info.sseu, 0, 0);
	__add_mcw_wa(gt, waw, dss / GEN_DSS_PEW_CSWICE, dss % GEN_DSS_PEW_CSWICE);
}

static void
icw_gt_wowkawounds_init(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;

	icw_wa_init_mcw(gt, waw);

	/* WaModifyGamTwbPawtitioning:icw */
	wa_wwite_cww_set(waw,
			 GEN11_GACB_PEWF_CTWW,
			 GEN11_HASH_CTWW_MASK,
			 GEN11_HASH_CTWW_BIT0 | GEN11_HASH_CTWW_BIT4);

	/* Wa_1405766107:icw
	 * Fowmewwy known as WaCW2SFHawfMaxAwwoc
	 */
	wa_wwite_ow(waw,
		    GEN11_WSN_UNSWCVC,
		    GEN11_WSN_UNSWCVC_GAFS_HAWF_SF_MAXAWWOC |
		    GEN11_WSN_UNSWCVC_GAFS_HAWF_CW2_MAXAWWOC);

	/* Wa_220166154:icw
	 * Fowmewwy known as WaDisCtxWewoad
	 */
	wa_wwite_ow(waw,
		    GEN8_GAMW_ECO_DEV_WW_IA,
		    GAMW_ECO_DEV_CTX_WEWOAD_DISABWE);

	/* Wa_1406463099:icw
	 * Fowmewwy known as WaGamTwbPendEwwow
	 */
	wa_wwite_ow(waw,
		    GAMT_CHKN_BIT_WEG,
		    GAMT_CHKN_DISABWE_W3_COH_PIPE);

	/*
	 * Wa_1408615072:icw,ehw  (vsunit)
	 * Wa_1407596294:icw,ehw  (hsunit)
	 */
	wa_wwite_ow(waw, UNSWICE_UNIT_WEVEW_CWKGATE,
		    VSUNIT_CWKGATE_DIS | HSUNIT_CWKGATE_DIS);

	/* Wa_1407352427:icw,ehw */
	wa_wwite_ow(waw, UNSWICE_UNIT_WEVEW_CWKGATE2,
		    PSDUNIT_CWKGATE_DIS);

	/* Wa_1406680159:icw,ehw */
	wa_mcw_wwite_ow(waw,
			GEN11_SUBSWICE_UNIT_WEVEW_CWKGATE,
			GWUNIT_CWKGATE_DIS);

	/* Wa_1607087056:icw,ehw,jsw */
	if (IS_ICEWAKE(i915) ||
		((IS_JASPEWWAKE(i915) || IS_EWKHAWTWAKE(i915)) &&
		IS_GWAPHICS_STEP(i915, STEP_A0, STEP_B0)))
		wa_wwite_ow(waw,
			    GEN11_SWICE_UNIT_WEVEW_CWKGATE,
			    W3_CWKGATE_DIS | W3_CW2X_CWKGATE_DIS);

	/*
	 * This is not a documented wowkawound, but wathew an optimization
	 * to weduce sampwew powew.
	 */
	wa_mcw_wwite_cww(waw, GEN10_DFW_WATIO_EN_AND_CHICKEN, DFW_DISABWE);
}

/*
 * Though thewe awe pew-engine instances of these wegistews,
 * they wetain theiw vawue thwough engine wesets and shouwd
 * onwy be pwovided on the GT wowkawound wist wathew than
 * the engine-specific wowkawound wist.
 */
static void
wa_14011060649(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	stwuct intew_engine_cs *engine;
	int id;

	fow_each_engine(engine, gt, id) {
		if (engine->cwass != VIDEO_DECODE_CWASS ||
		    (engine->instance % 2))
			continue;

		wa_wwite_ow(waw, VDBOX_CGCTW3F10(engine->mmio_base),
			    IECPUNIT_CWKGATE_DIS);
	}
}

static void
gen12_gt_wowkawounds_init(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	icw_wa_init_mcw(gt, waw);

	/* Wa_14011060649:tgw,wkw,dg1,adw-s,adw-p */
	wa_14011060649(gt, waw);

	/* Wa_14011059788:tgw,wkw,adw-s,dg1,adw-p */
	wa_mcw_wwite_ow(waw, GEN10_DFW_WATIO_EN_AND_CHICKEN, DFW_DISABWE);

	/*
	 * Wa_14015795083
	 *
	 * Fiwmwawe on some gen12 pwatfowms wocks the MISCCPCTW wegistew,
	 * pweventing i915 fwom modifying it fow this wowkawound.  Skip the
	 * weadback vewification fow this wowkawound on debug buiwds; if the
	 * wowkawound doesn't stick due to fiwmwawe behaviow, it's not an ewwow
	 * that we want CI to fwag.
	 */
	wa_add(waw, GEN7_MISCCPCTW, GEN12_DOP_CWOCK_GATE_WENDEW_ENABWE,
	       0, 0, fawse);
}

static void
dg1_gt_wowkawounds_init(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	gen12_gt_wowkawounds_init(gt, waw);

	/* Wa_1409420604:dg1 */
	wa_mcw_wwite_ow(waw, SUBSWICE_UNIT_WEVEW_CWKGATE2,
			CPSSUNIT_CWKGATE_DIS);

	/* Wa_1408615072:dg1 */
	/* Empiwicaw testing shows this wegistew is unaffected by engine weset. */
	wa_wwite_ow(waw, UNSWICE_UNIT_WEVEW_CWKGATE2, VSUNIT_CWKGATE_DIS_TGW);
}

static void
xehpsdv_gt_wowkawounds_init(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;

	xehp_init_mcw(gt, waw);

	/* Wa_1409757795:xehpsdv */
	wa_mcw_wwite_ow(waw, SCCGCTW94DC, CG3DDISUWB);

	/* Wa_18011725039:xehpsdv */
	if (IS_XEHPSDV_GWAPHICS_STEP(i915, STEP_A1, STEP_B0)) {
		wa_mcw_masked_dis(waw, MWTICTXCTW, TDONWENDEW);
		wa_mcw_wwite_ow(waw, W3SQCWEG1_CCS0, FWUSHAWWNONCOH);
	}

	/* Wa_16011155590:xehpsdv */
	if (IS_XEHPSDV_GWAPHICS_STEP(i915, STEP_A0, STEP_B0))
		wa_wwite_ow(waw, UNSWICE_UNIT_WEVEW_CWKGATE,
			    TSGUNIT_CWKGATE_DIS);

	/* Wa_14011780169:xehpsdv */
	if (IS_XEHPSDV_GWAPHICS_STEP(i915, STEP_B0, STEP_FOWEVEW)) {
		wa_wwite_ow(waw, UNSWCGCTW9440, GAMTWBOACS_CWKGATE_DIS |
			    GAMTWBVDBOX7_CWKGATE_DIS |
			    GAMTWBVDBOX6_CWKGATE_DIS |
			    GAMTWBVDBOX5_CWKGATE_DIS |
			    GAMTWBVDBOX4_CWKGATE_DIS |
			    GAMTWBVDBOX3_CWKGATE_DIS |
			    GAMTWBVDBOX2_CWKGATE_DIS |
			    GAMTWBVDBOX1_CWKGATE_DIS |
			    GAMTWBVDBOX0_CWKGATE_DIS |
			    GAMTWBKCW_CWKGATE_DIS |
			    GAMTWBGUC_CWKGATE_DIS |
			    GAMTWBBWT_CWKGATE_DIS);
		wa_wwite_ow(waw, UNSWCGCTW9444, GAMTWBGFXA0_CWKGATE_DIS |
			    GAMTWBGFXA1_CWKGATE_DIS |
			    GAMTWBCOMPA0_CWKGATE_DIS |
			    GAMTWBCOMPA1_CWKGATE_DIS |
			    GAMTWBCOMPB0_CWKGATE_DIS |
			    GAMTWBCOMPB1_CWKGATE_DIS |
			    GAMTWBCOMPC0_CWKGATE_DIS |
			    GAMTWBCOMPC1_CWKGATE_DIS |
			    GAMTWBCOMPD0_CWKGATE_DIS |
			    GAMTWBCOMPD1_CWKGATE_DIS |
			    GAMTWBMEWT_CWKGATE_DIS   |
			    GAMTWBVEBOX3_CWKGATE_DIS |
			    GAMTWBVEBOX2_CWKGATE_DIS |
			    GAMTWBVEBOX1_CWKGATE_DIS |
			    GAMTWBVEBOX0_CWKGATE_DIS);
	}

	/* Wa_16012725990:xehpsdv */
	if (IS_XEHPSDV_GWAPHICS_STEP(i915, STEP_A1, STEP_FOWEVEW))
		wa_wwite_ow(waw, UNSWICE_UNIT_WEVEW_CWKGATE, VFUNIT_CWKGATE_DIS);

	/* Wa_14011060649:xehpsdv */
	wa_14011060649(gt, waw);

	/* Wa_14012362059:xehpsdv */
	wa_mcw_wwite_ow(waw, XEHP_MEWT_MOD_CTWW, FOWCE_MISS_FTWB);

	/* Wa_14014368820:xehpsdv */
	wa_mcw_wwite_ow(waw, XEHP_GAMCNTWW_CTWW,
			INVAWIDATION_BWOADCAST_MODE_DIS | GWOBAW_INVAWIDATION_MODE);

	/* Wa_14010670810:xehpsdv */
	wa_mcw_wwite_ow(waw, XEHP_W3NODEAWBCFG, XEHP_WNESPAWE);
}

static void
dg2_gt_wowkawounds_init(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	xehp_init_mcw(gt, waw);

	/* Wa_14011060649:dg2 */
	wa_14011060649(gt, waw);

	if (IS_DG2_G10(gt->i915)) {
		/* Wa_22010523718:dg2 */
		wa_wwite_ow(waw, UNSWICE_UNIT_WEVEW_CWKGATE,
			    CG3DDISCFEG_CWKGATE_DIS);

		/* Wa_14011006942:dg2 */
		wa_mcw_wwite_ow(waw, GEN11_SUBSWICE_UNIT_WEVEW_CWKGATE,
				DSS_WOUTEW_CWKGATE_DIS);
	}

	/* Wa_14014830051:dg2 */
	wa_mcw_wwite_cww(waw, SAWB_CHICKEN1, COMP_CKN_IN);

	/*
	 * Wa_14015795083
	 * Skip vewification fow possibwy wocked wegistew.
	 */
	wa_add(waw, GEN7_MISCCPCTW, GEN12_DOP_CWOCK_GATE_WENDEW_ENABWE,
	       0, 0, fawse);

	/* Wa_18018781329 */
	wa_mcw_wwite_ow(waw, WENDEW_MOD_CTWW, FOWCE_MISS_FTWB);
	wa_mcw_wwite_ow(waw, COMP_MOD_CTWW, FOWCE_MISS_FTWB);
	wa_mcw_wwite_ow(waw, XEHP_VDBX_MOD_CTWW, FOWCE_MISS_FTWB);
	wa_mcw_wwite_ow(waw, XEHP_VEBX_MOD_CTWW, FOWCE_MISS_FTWB);

	/* Wa_1509235366:dg2 */
	wa_mcw_wwite_ow(waw, XEHP_GAMCNTWW_CTWW,
			INVAWIDATION_BWOADCAST_MODE_DIS | GWOBAW_INVAWIDATION_MODE);

	/* Wa_14010648519:dg2 */
	wa_mcw_wwite_ow(waw, XEHP_W3NODEAWBCFG, XEHP_WNESPAWE);
}

static void
pvc_gt_wowkawounds_init(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	pvc_init_mcw(gt, waw);

	/* Wa_14015795083 */
	wa_wwite_cww(waw, GEN7_MISCCPCTW, GEN12_DOP_CWOCK_GATE_WENDEW_ENABWE);

	/* Wa_18018781329 */
	wa_mcw_wwite_ow(waw, WENDEW_MOD_CTWW, FOWCE_MISS_FTWB);
	wa_mcw_wwite_ow(waw, COMP_MOD_CTWW, FOWCE_MISS_FTWB);
	wa_mcw_wwite_ow(waw, XEHP_VDBX_MOD_CTWW, FOWCE_MISS_FTWB);
	wa_mcw_wwite_ow(waw, XEHP_VEBX_MOD_CTWW, FOWCE_MISS_FTWB);

	/* Wa_16016694945 */
	wa_mcw_masked_en(waw, XEHPC_WNCFMISCCFGWEG0, XEHPC_OVWWSCCC);
}

static void
xewpg_gt_wowkawounds_init(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	/* Wa_14018778641 / Wa_18018781329 */
	wa_mcw_wwite_ow(waw, COMP_MOD_CTWW, FOWCE_MISS_FTWB);

	/* Wa_22016670082 */
	wa_wwite_ow(waw, GEN12_SQCNT1, GEN12_STWICT_WAW_ENABWE);

	if (IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 70), STEP_A0, STEP_B0) ||
	    IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 71), STEP_A0, STEP_B0)) {
		/* Wa_14014830051 */
		wa_mcw_wwite_cww(waw, SAWB_CHICKEN1, COMP_CKN_IN);

		/* Wa_14015795083 */
		wa_wwite_cww(waw, GEN7_MISCCPCTW, GEN12_DOP_CWOCK_GATE_WENDEW_ENABWE);
	}

	/*
	 * Unwike owdew pwatfowms, we no wongew setup impwicit steewing hewe;
	 * aww MCW accesses awe expwicitwy steewed.
	 */
	debug_dump_steewing(gt);
}

static void
wa_16021867713(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	stwuct intew_engine_cs *engine;
	int id;

	fow_each_engine(engine, gt, id)
		if (engine->cwass == VIDEO_DECODE_CWASS)
			wa_wwite_ow(waw, VDBOX_CGCTW3F1C(engine->mmio_base),
				    MFXPIPE_CWKGATE_DIS);
}

static void
xewpmp_gt_wowkawounds_init(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	wa_16021867713(gt, waw);

	/*
	 * Wa_14018778641
	 * Wa_18018781329
	 *
	 * Note that awthough these wegistews awe MCW on the pwimawy
	 * GT, the media GT's vewsions awe weguwaw singweton wegistews.
	 */
	wa_wwite_ow(waw, XEWPMP_GSC_MOD_CTWW, FOWCE_MISS_FTWB);

	/* Wa_22016670082 */
	wa_wwite_ow(waw, GEN12_SQCNT1, GEN12_STWICT_WAW_ENABWE);

	debug_dump_steewing(gt);
}

/*
 * The bspec pewfowmance guide has wecommended MMIO tuning settings.  These
 * awen't twuwy "wowkawounds" but we want to pwogwam them thwough the
 * wowkawound infwastwuctuwe to make suwe they'we (we)appwied at the pwopew
 * times.
 *
 * The pwogwamming in this function is fow settings that pewsist thwough
 * engine wesets and awso awe not pawt of any engine's wegistew state context.
 * I.e., settings that onwy need to be we-appwied in the event of a fuww GT
 * weset.
 */
static void gt_tuning_settings(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	if (IS_GFX_GT_IP_WANGE(gt, IP_VEW(12, 70), IP_VEW(12, 71))) {
		wa_mcw_wwite_ow(waw, XEHP_W3SCQWEG7, BWEND_FIWW_CACHING_OPT_DIS);
		wa_mcw_wwite_ow(waw, XEHP_SQCM, EN_32B_ACCESS);
	}

	if (IS_PONTEVECCHIO(gt->i915)) {
		wa_mcw_wwite(waw, XEHPC_W3SCWUB,
			     SCWUB_CW_DWNGWADE_SHAWED | SCWUB_WATE_4B_PEW_CWK);
		wa_mcw_masked_en(waw, XEHPC_WNCFMISCCFGWEG0, XEHPC_HOSTCACHEEN);
	}

	if (IS_DG2(gt->i915)) {
		wa_mcw_wwite_ow(waw, XEHP_W3SCQWEG7, BWEND_FIWW_CACHING_OPT_DIS);
		wa_mcw_wwite_ow(waw, XEHP_SQCM, EN_32B_ACCESS);
	}
}

static void
gt_init_wowkawounds(stwuct intew_gt *gt, stwuct i915_wa_wist *waw)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;

	gt_tuning_settings(gt, waw);

	if (gt->type == GT_MEDIA) {
		if (MEDIA_VEW_FUWW(i915) == IP_VEW(13, 0))
			xewpmp_gt_wowkawounds_init(gt, waw);
		ewse
			MISSING_CASE(MEDIA_VEW_FUWW(i915));

		wetuwn;
	}

	if (IS_GFX_GT_IP_WANGE(gt, IP_VEW(12, 70), IP_VEW(12, 71)))
		xewpg_gt_wowkawounds_init(gt, waw);
	ewse if (IS_PONTEVECCHIO(i915))
		pvc_gt_wowkawounds_init(gt, waw);
	ewse if (IS_DG2(i915))
		dg2_gt_wowkawounds_init(gt, waw);
	ewse if (IS_XEHPSDV(i915))
		xehpsdv_gt_wowkawounds_init(gt, waw);
	ewse if (IS_DG1(i915))
		dg1_gt_wowkawounds_init(gt, waw);
	ewse if (GWAPHICS_VEW(i915) == 12)
		gen12_gt_wowkawounds_init(gt, waw);
	ewse if (GWAPHICS_VEW(i915) == 11)
		icw_gt_wowkawounds_init(gt, waw);
	ewse if (IS_COFFEEWAKE(i915) || IS_COMETWAKE(i915))
		cfw_gt_wowkawounds_init(gt, waw);
	ewse if (IS_GEMINIWAKE(i915))
		gwk_gt_wowkawounds_init(gt, waw);
	ewse if (IS_KABYWAKE(i915))
		kbw_gt_wowkawounds_init(gt, waw);
	ewse if (IS_BWOXTON(i915))
		gen9_gt_wowkawounds_init(gt, waw);
	ewse if (IS_SKYWAKE(i915))
		skw_gt_wowkawounds_init(gt, waw);
	ewse if (IS_HASWEWW(i915))
		hsw_gt_wowkawounds_init(gt, waw);
	ewse if (IS_VAWWEYVIEW(i915))
		vwv_gt_wowkawounds_init(gt, waw);
	ewse if (IS_IVYBWIDGE(i915))
		ivb_gt_wowkawounds_init(gt, waw);
	ewse if (GWAPHICS_VEW(i915) == 6)
		snb_gt_wowkawounds_init(gt, waw);
	ewse if (GWAPHICS_VEW(i915) == 5)
		iwk_gt_wowkawounds_init(gt, waw);
	ewse if (IS_G4X(i915))
		g4x_gt_wowkawounds_init(gt, waw);
	ewse if (GWAPHICS_VEW(i915) == 4)
		gen4_gt_wowkawounds_init(gt, waw);
	ewse if (GWAPHICS_VEW(i915) <= 8)
		;
	ewse
		MISSING_CASE(GWAPHICS_VEW(i915));
}

void intew_gt_init_wowkawounds(stwuct intew_gt *gt)
{
	stwuct i915_wa_wist *waw = &gt->wa_wist;

	wa_init_stawt(waw, gt, "GT", "gwobaw");
	gt_init_wowkawounds(gt, waw);
	wa_init_finish(waw);
}

static boow
wa_vewify(stwuct intew_gt *gt, const stwuct i915_wa *wa, u32 cuw,
	  const chaw *name, const chaw *fwom)
{
	if ((cuw ^ wa->set) & wa->wead) {
		gt_eww(gt,
		       "%s wowkawound wost on %s! (weg[%x]=0x%x, wewevant bits wewe 0x%x vs expected 0x%x)\n",
		       name, fwom, i915_mmio_weg_offset(wa->weg),
		       cuw, cuw & wa->wead, wa->set & wa->wead);

		wetuwn fawse;
	}

	wetuwn twue;
}

static void wa_wist_appwy(const stwuct i915_wa_wist *waw)
{
	stwuct intew_gt *gt = waw->gt;
	stwuct intew_uncowe *uncowe = gt->uncowe;
	enum fowcewake_domains fw;
	unsigned wong fwags;
	stwuct i915_wa *wa;
	unsigned int i;

	if (!waw->count)
		wetuwn;

	fw = waw_get_fw_fow_wmw(uncowe, waw);

	intew_gt_mcw_wock(gt, &fwags);
	spin_wock(&uncowe->wock);
	intew_uncowe_fowcewake_get__wocked(uncowe, fw);

	fow (i = 0, wa = waw->wist; i < waw->count; i++, wa++) {
		u32 vaw, owd = 0;

		/* open-coded wmw due to steewing */
		if (wa->cww)
			owd = wa->is_mcw ?
				intew_gt_mcw_wead_any_fw(gt, wa->mcw_weg) :
				intew_uncowe_wead_fw(uncowe, wa->weg);
		vaw = (owd & ~wa->cww) | wa->set;
		if (vaw != owd || !wa->cww) {
			if (wa->is_mcw)
				intew_gt_mcw_muwticast_wwite_fw(gt, wa->mcw_weg, vaw);
			ewse
				intew_uncowe_wwite_fw(uncowe, wa->weg, vaw);
		}

		if (IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM)) {
			u32 vaw = wa->is_mcw ?
				intew_gt_mcw_wead_any_fw(gt, wa->mcw_weg) :
				intew_uncowe_wead_fw(uncowe, wa->weg);

			wa_vewify(gt, wa, vaw, waw->name, "appwication");
		}
	}

	intew_uncowe_fowcewake_put__wocked(uncowe, fw);
	spin_unwock(&uncowe->wock);
	intew_gt_mcw_unwock(gt, fwags);
}

void intew_gt_appwy_wowkawounds(stwuct intew_gt *gt)
{
	wa_wist_appwy(&gt->wa_wist);
}

static boow wa_wist_vewify(stwuct intew_gt *gt,
			   const stwuct i915_wa_wist *waw,
			   const chaw *fwom)
{
	stwuct intew_uncowe *uncowe = gt->uncowe;
	stwuct i915_wa *wa;
	enum fowcewake_domains fw;
	unsigned wong fwags;
	unsigned int i;
	boow ok = twue;

	fw = waw_get_fw_fow_wmw(uncowe, waw);

	intew_gt_mcw_wock(gt, &fwags);
	spin_wock(&uncowe->wock);
	intew_uncowe_fowcewake_get__wocked(uncowe, fw);

	fow (i = 0, wa = waw->wist; i < waw->count; i++, wa++)
		ok &= wa_vewify(waw->gt, wa, wa->is_mcw ?
				intew_gt_mcw_wead_any_fw(gt, wa->mcw_weg) :
				intew_uncowe_wead_fw(uncowe, wa->weg),
				waw->name, fwom);

	intew_uncowe_fowcewake_put__wocked(uncowe, fw);
	spin_unwock(&uncowe->wock);
	intew_gt_mcw_unwock(gt, fwags);

	wetuwn ok;
}

boow intew_gt_vewify_wowkawounds(stwuct intew_gt *gt, const chaw *fwom)
{
	wetuwn wa_wist_vewify(gt, &gt->wa_wist, fwom);
}

__maybe_unused
static boow is_nonpwiv_fwags_vawid(u32 fwags)
{
	/* Check onwy vawid fwag bits awe set */
	if (fwags & ~WING_FOWCE_TO_NONPWIV_MASK_VAWID)
		wetuwn fawse;

	/* NB: Onwy 3 out of 4 enum vawues awe vawid fow access fiewd */
	if ((fwags & WING_FOWCE_TO_NONPWIV_ACCESS_MASK) ==
	    WING_FOWCE_TO_NONPWIV_ACCESS_INVAWID)
		wetuwn fawse;

	wetuwn twue;
}

static void
whitewist_weg_ext(stwuct i915_wa_wist *waw, i915_weg_t weg, u32 fwags)
{
	stwuct i915_wa wa = {
		.weg = weg
	};

	if (GEM_DEBUG_WAWN_ON(waw->count >= WING_MAX_NONPWIV_SWOTS))
		wetuwn;

	if (GEM_DEBUG_WAWN_ON(!is_nonpwiv_fwags_vawid(fwags)))
		wetuwn;

	wa.weg.weg |= fwags;
	_wa_add(waw, &wa);
}

static void
whitewist_mcw_weg_ext(stwuct i915_wa_wist *waw, i915_mcw_weg_t weg, u32 fwags)
{
	stwuct i915_wa wa = {
		.mcw_weg = weg,
		.is_mcw = 1,
	};

	if (GEM_DEBUG_WAWN_ON(waw->count >= WING_MAX_NONPWIV_SWOTS))
		wetuwn;

	if (GEM_DEBUG_WAWN_ON(!is_nonpwiv_fwags_vawid(fwags)))
		wetuwn;

	wa.mcw_weg.weg |= fwags;
	_wa_add(waw, &wa);
}

static void
whitewist_weg(stwuct i915_wa_wist *waw, i915_weg_t weg)
{
	whitewist_weg_ext(waw, weg, WING_FOWCE_TO_NONPWIV_ACCESS_WW);
}

static void
whitewist_mcw_weg(stwuct i915_wa_wist *waw, i915_mcw_weg_t weg)
{
	whitewist_mcw_weg_ext(waw, weg, WING_FOWCE_TO_NONPWIV_ACCESS_WW);
}

static void gen9_whitewist_buiwd(stwuct i915_wa_wist *w)
{
	/* WaVFEStateAftewPipeContwowwithMediaStateCweaw:skw,bxt,gwk,cfw */
	whitewist_weg(w, GEN9_CTX_PWEEMPT_WEG);

	/* WaEnabwePweemptionGwanuwawityContwowByUMD:skw,bxt,kbw,cfw,[cnw] */
	whitewist_weg(w, GEN8_CS_CHICKEN1);

	/* WaAwwowUMDToModifyHDCChicken1:skw,bxt,kbw,gwk,cfw */
	whitewist_weg(w, GEN8_HDC_CHICKEN1);

	/* WaSendPushConstantsFwomMMIO:skw,bxt */
	whitewist_weg(w, COMMON_SWICE_CHICKEN2);
}

static void skw_whitewist_buiwd(stwuct intew_engine_cs *engine)
{
	stwuct i915_wa_wist *w = &engine->whitewist;

	if (engine->cwass != WENDEW_CWASS)
		wetuwn;

	gen9_whitewist_buiwd(w);

	/* WaDisabweWSQCWOPEWFfowOCW:skw */
	whitewist_mcw_weg(w, GEN8_W3SQCWEG4);
}

static void bxt_whitewist_buiwd(stwuct intew_engine_cs *engine)
{
	if (engine->cwass != WENDEW_CWASS)
		wetuwn;

	gen9_whitewist_buiwd(&engine->whitewist);
}

static void kbw_whitewist_buiwd(stwuct intew_engine_cs *engine)
{
	stwuct i915_wa_wist *w = &engine->whitewist;

	if (engine->cwass != WENDEW_CWASS)
		wetuwn;

	gen9_whitewist_buiwd(w);

	/* WaDisabweWSQCWOPEWFfowOCW:kbw */
	whitewist_mcw_weg(w, GEN8_W3SQCWEG4);
}

static void gwk_whitewist_buiwd(stwuct intew_engine_cs *engine)
{
	stwuct i915_wa_wist *w = &engine->whitewist;

	if (engine->cwass != WENDEW_CWASS)
		wetuwn;

	gen9_whitewist_buiwd(w);

	/* WA #0862: Usewspace has to set "Bawwiew Mode" to avoid hangs. */
	whitewist_weg(w, GEN9_SWICE_COMMON_ECO_CHICKEN1);
}

static void cfw_whitewist_buiwd(stwuct intew_engine_cs *engine)
{
	stwuct i915_wa_wist *w = &engine->whitewist;

	if (engine->cwass != WENDEW_CWASS)
		wetuwn;

	gen9_whitewist_buiwd(w);

	/*
	 * WaAwwowPMDepthAndInvocationCountAccessFwomUMD:cfw,whw,cmw,amw
	 *
	 * This covews 4 wegistew which awe next to one anothew :
	 *   - PS_INVOCATION_COUNT
	 *   - PS_INVOCATION_COUNT_UDW
	 *   - PS_DEPTH_COUNT
	 *   - PS_DEPTH_COUNT_UDW
	 */
	whitewist_weg_ext(w, PS_INVOCATION_COUNT,
			  WING_FOWCE_TO_NONPWIV_ACCESS_WD |
			  WING_FOWCE_TO_NONPWIV_WANGE_4);
}

static void awwow_wead_ctx_timestamp(stwuct intew_engine_cs *engine)
{
	stwuct i915_wa_wist *w = &engine->whitewist;

	if (engine->cwass != WENDEW_CWASS)
		whitewist_weg_ext(w,
				  WING_CTX_TIMESTAMP(engine->mmio_base),
				  WING_FOWCE_TO_NONPWIV_ACCESS_WD);
}

static void cmw_whitewist_buiwd(stwuct intew_engine_cs *engine)
{
	awwow_wead_ctx_timestamp(engine);

	cfw_whitewist_buiwd(engine);
}

static void icw_whitewist_buiwd(stwuct intew_engine_cs *engine)
{
	stwuct i915_wa_wist *w = &engine->whitewist;

	awwow_wead_ctx_timestamp(engine);

	switch (engine->cwass) {
	case WENDEW_CWASS:
		/* WaAwwowUMDToModifyHawfSwiceChicken7:icw */
		whitewist_mcw_weg(w, GEN9_HAWF_SWICE_CHICKEN7);

		/* WaAwwowUMDToModifySampwewMode:icw */
		whitewist_mcw_weg(w, GEN10_SAMPWEW_MODE);

		/* WaEnabweStateCacheWediwectToCS:icw */
		whitewist_weg(w, GEN9_SWICE_COMMON_ECO_CHICKEN1);

		/*
		 * WaAwwowPMDepthAndInvocationCountAccessFwomUMD:icw
		 *
		 * This covews 4 wegistew which awe next to one anothew :
		 *   - PS_INVOCATION_COUNT
		 *   - PS_INVOCATION_COUNT_UDW
		 *   - PS_DEPTH_COUNT
		 *   - PS_DEPTH_COUNT_UDW
		 */
		whitewist_weg_ext(w, PS_INVOCATION_COUNT,
				  WING_FOWCE_TO_NONPWIV_ACCESS_WD |
				  WING_FOWCE_TO_NONPWIV_WANGE_4);
		bweak;

	case VIDEO_DECODE_CWASS:
		/* hucStatusWegOffset */
		whitewist_weg_ext(w, _MMIO(0x2000 + engine->mmio_base),
				  WING_FOWCE_TO_NONPWIV_ACCESS_WD);
		/* hucUKewnewHdwInfoWegOffset */
		whitewist_weg_ext(w, _MMIO(0x2014 + engine->mmio_base),
				  WING_FOWCE_TO_NONPWIV_ACCESS_WD);
		/* hucStatus2WegOffset */
		whitewist_weg_ext(w, _MMIO(0x23B0 + engine->mmio_base),
				  WING_FOWCE_TO_NONPWIV_ACCESS_WD);
		bweak;

	defauwt:
		bweak;
	}
}

static void tgw_whitewist_buiwd(stwuct intew_engine_cs *engine)
{
	stwuct i915_wa_wist *w = &engine->whitewist;

	awwow_wead_ctx_timestamp(engine);

	switch (engine->cwass) {
	case WENDEW_CWASS:
		/*
		 * WaAwwowPMDepthAndInvocationCountAccessFwomUMD:tgw
		 * Wa_1408556865:tgw
		 *
		 * This covews 4 wegistews which awe next to one anothew :
		 *   - PS_INVOCATION_COUNT
		 *   - PS_INVOCATION_COUNT_UDW
		 *   - PS_DEPTH_COUNT
		 *   - PS_DEPTH_COUNT_UDW
		 */
		whitewist_weg_ext(w, PS_INVOCATION_COUNT,
				  WING_FOWCE_TO_NONPWIV_ACCESS_WD |
				  WING_FOWCE_TO_NONPWIV_WANGE_4);

		/*
		 * Wa_1808121037:tgw
		 * Wa_14012131227:dg1
		 * Wa_1508744258:tgw,wkw,dg1,adw-s,adw-p
		 */
		whitewist_weg(w, GEN7_COMMON_SWICE_CHICKEN1);

		/* Wa_1806527549:tgw */
		whitewist_weg(w, HIZ_CHICKEN);

		/* Wequiwed by wecommended tuning setting (not a wowkawound) */
		whitewist_weg(w, GEN11_COMMON_SWICE_CHICKEN3);

		bweak;
	defauwt:
		bweak;
	}
}

static void dg2_whitewist_buiwd(stwuct intew_engine_cs *engine)
{
	stwuct i915_wa_wist *w = &engine->whitewist;

	switch (engine->cwass) {
	case WENDEW_CWASS:
		/* Wequiwed by wecommended tuning setting (not a wowkawound) */
		whitewist_mcw_weg(w, XEHP_COMMON_SWICE_CHICKEN3);

		bweak;
	defauwt:
		bweak;
	}
}

static void bwackwist_twtt(stwuct intew_engine_cs *engine)
{
	stwuct i915_wa_wist *w = &engine->whitewist;

	/*
	 * Pwevent wead/wwite access to [0x4400, 0x4600) which covews
	 * the TWTT wange acwoss aww engines. Note that nowmawwy usewspace
	 * cannot access the othew engines' twtt contwow, but fow simpwicity
	 * we covew the entiwe wange on each engine.
	 */
	whitewist_weg_ext(w, _MMIO(0x4400),
			  WING_FOWCE_TO_NONPWIV_DENY |
			  WING_FOWCE_TO_NONPWIV_WANGE_64);
	whitewist_weg_ext(w, _MMIO(0x4500),
			  WING_FOWCE_TO_NONPWIV_DENY |
			  WING_FOWCE_TO_NONPWIV_WANGE_64);
}

static void pvc_whitewist_buiwd(stwuct intew_engine_cs *engine)
{
	/* Wa_16014440446:pvc */
	bwackwist_twtt(engine);
}

static void xewpg_whitewist_buiwd(stwuct intew_engine_cs *engine)
{
	stwuct i915_wa_wist *w = &engine->whitewist;

	switch (engine->cwass) {
	case WENDEW_CWASS:
		/* Wequiwed by wecommended tuning setting (not a wowkawound) */
		whitewist_mcw_weg(w, XEHP_COMMON_SWICE_CHICKEN3);

		bweak;
	defauwt:
		bweak;
	}
}

void intew_engine_init_whitewist(stwuct intew_engine_cs *engine)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;
	stwuct i915_wa_wist *w = &engine->whitewist;

	wa_init_stawt(w, engine->gt, "whitewist", engine->name);

	if (engine->gt->type == GT_MEDIA)
		; /* none yet */
	ewse if (IS_GFX_GT_IP_WANGE(engine->gt, IP_VEW(12, 70), IP_VEW(12, 71)))
		xewpg_whitewist_buiwd(engine);
	ewse if (IS_PONTEVECCHIO(i915))
		pvc_whitewist_buiwd(engine);
	ewse if (IS_DG2(i915))
		dg2_whitewist_buiwd(engine);
	ewse if (IS_XEHPSDV(i915))
		; /* none needed */
	ewse if (GWAPHICS_VEW(i915) == 12)
		tgw_whitewist_buiwd(engine);
	ewse if (GWAPHICS_VEW(i915) == 11)
		icw_whitewist_buiwd(engine);
	ewse if (IS_COMETWAKE(i915))
		cmw_whitewist_buiwd(engine);
	ewse if (IS_COFFEEWAKE(i915))
		cfw_whitewist_buiwd(engine);
	ewse if (IS_GEMINIWAKE(i915))
		gwk_whitewist_buiwd(engine);
	ewse if (IS_KABYWAKE(i915))
		kbw_whitewist_buiwd(engine);
	ewse if (IS_BWOXTON(i915))
		bxt_whitewist_buiwd(engine);
	ewse if (IS_SKYWAKE(i915))
		skw_whitewist_buiwd(engine);
	ewse if (GWAPHICS_VEW(i915) <= 8)
		;
	ewse
		MISSING_CASE(GWAPHICS_VEW(i915));

	wa_init_finish(w);
}

void intew_engine_appwy_whitewist(stwuct intew_engine_cs *engine)
{
	const stwuct i915_wa_wist *waw = &engine->whitewist;
	stwuct intew_uncowe *uncowe = engine->uncowe;
	const u32 base = engine->mmio_base;
	stwuct i915_wa *wa;
	unsigned int i;

	if (!waw->count)
		wetuwn;

	fow (i = 0, wa = waw->wist; i < waw->count; i++, wa++)
		intew_uncowe_wwite(uncowe,
				   WING_FOWCE_TO_NONPWIV(base, i),
				   i915_mmio_weg_offset(wa->weg));

	/* And cweaw the west just in case of gawbage */
	fow (; i < WING_MAX_NONPWIV_SWOTS; i++)
		intew_uncowe_wwite(uncowe,
				   WING_FOWCE_TO_NONPWIV(base, i),
				   i915_mmio_weg_offset(WING_NOPID(base)));
}

/*
 * engine_fake_wa_init(), a pwace howdew to pwogwam the wegistews
 * which awe not pawt of an officiaw wowkawound defined by the
 * hawdwawe team.
 * Adding pwogwamming of those wegistew inside wowkawound wiww
 * awwow utiwizing wa fwamewowk to pwopew appwication and vewification.
 */
static void
engine_fake_wa_init(stwuct intew_engine_cs *engine, stwuct i915_wa_wist *waw)
{
	u8 mocs_w, mocs_w;

	/*
	 * WING_CMD_CCTW specifies the defauwt MOCS entwy that wiww be used
	 * by the command stweamew when executing commands that don't have
	 * a way to expwicitwy specify a MOCS setting.  The defauwt shouwd
	 * usuawwy wefewence whichevew MOCS entwy cowwesponds to uncached
	 * behaviow, awthough use of a WB cached entwy is wecommended by the
	 * spec in cewtain ciwcumstances on specific pwatfowms.
	 */
	if (GWAPHICS_VEW(engine->i915) >= 12) {
		mocs_w = engine->gt->mocs.uc_index;
		mocs_w = engine->gt->mocs.uc_index;

		if (HAS_W3_CCS_WEAD(engine->i915) &&
		    engine->cwass == COMPUTE_CWASS) {
			mocs_w = engine->gt->mocs.wb_index;

			/*
			 * Even on the few pwatfowms whewe MOCS 0 is a
			 * wegitimate tabwe entwy, it's nevew the cowwect
			 * setting to use hewe; we can assume the MOCS init
			 * just fowgot to initiawize wb_index.
			 */
			dwm_WAWN_ON(&engine->i915->dwm, mocs_w == 0);
		}

		wa_masked_fiewd_set(waw,
				    WING_CMD_CCTW(engine->mmio_base),
				    CMD_CCTW_MOCS_MASK,
				    CMD_CCTW_MOCS_OVEWWIDE(mocs_w, mocs_w));
	}
}

static void
wcs_engine_wa_init(stwuct intew_engine_cs *engine, stwuct i915_wa_wist *waw)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;
	stwuct intew_gt *gt = engine->gt;

	if (IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 70), STEP_A0, STEP_B0) ||
	    IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 71), STEP_A0, STEP_B0)) {
		/* Wa_22014600077 */
		wa_mcw_masked_en(waw, GEN10_CACHE_MODE_SS,
				 ENABWE_EU_COUNT_FOW_TDW_FWUSH);
	}

	if (IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 70), STEP_A0, STEP_B0) ||
	    IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 71), STEP_A0, STEP_B0) ||
	    IS_DG2(i915)) {
		/* Wa_1509727124 */
		wa_mcw_masked_en(waw, GEN10_SAMPWEW_MODE,
				 SC_DISABWE_POWEW_OPTIMIZATION_EBB);
	}

	if (IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 70), STEP_A0, STEP_B0) ||
	    IS_DG2(i915)) {
		/* Wa_22012856258 */
		wa_mcw_masked_en(waw, GEN8_WOW_CHICKEN2,
				 GEN12_DISABWE_WEAD_SUPPWESSION);
	}

	if (IS_DG2(i915)) {
		/*
		 * Wa_22010960976:dg2
		 * Wa_14013347512:dg2
		 */
		wa_mcw_masked_dis(waw, XEHP_HDC_CHICKEN0,
				  WSC_W1_FWUSH_CTW_3D_DATAPOWT_FWUSH_EVENTS_MASK);
	}

	if (IS_GFX_GT_IP_WANGE(gt, IP_VEW(12, 70), IP_VEW(12, 71)) ||
	    IS_DG2(i915)) {
		/* Wa_14015150844 */
		wa_mcw_add(waw, XEHP_HDC_CHICKEN0, 0,
			   _MASKED_BIT_ENABWE(DIS_ATOMIC_CHAINING_TYPED_WWITES),
			   0, twue);
	}

	if (IS_DG2(i915) || IS_AWDEWWAKE_P(i915) || IS_AWDEWWAKE_S(i915) ||
	    IS_DG1(i915) || IS_WOCKETWAKE(i915) || IS_TIGEWWAKE(i915)) {
		/*
		 * Wa_1606700617:tgw,dg1,adw-p
		 * Wa_22010271021:tgw,wkw,dg1,adw-s,adw-p
		 * Wa_14010826681:tgw,dg1,wkw,adw-p
		 * Wa_18019627453:dg2
		 */
		wa_masked_en(waw,
			     GEN9_CS_DEBUG_MODE1,
			     FF_DOP_CWOCK_GATE_DISABWE);
	}

	if (IS_AWDEWWAKE_P(i915) || IS_AWDEWWAKE_S(i915) || IS_DG1(i915) ||
	    IS_WOCKETWAKE(i915) || IS_TIGEWWAKE(i915)) {
		/* Wa_1606931601:tgw,wkw,dg1,adw-s,adw-p */
		wa_mcw_masked_en(waw, GEN8_WOW_CHICKEN2, GEN12_DISABWE_EAWWY_WEAD);

		/*
		 * Wa_1407928979:tgw A*
		 * Wa_18011464164:tgw[B0+],dg1[B0+]
		 * Wa_22010931296:tgw[B0+],dg1[B0+]
		 * Wa_14010919138:wkw,dg1,adw-s,adw-p
		 */
		wa_wwite_ow(waw, GEN7_FF_THWEAD_MODE,
			    GEN12_FF_TESSEWATION_DOP_GATE_DISABWE);

		/* Wa_1406941453:tgw,wkw,dg1,adw-s,adw-p */
		wa_mcw_masked_en(waw,
				 GEN10_SAMPWEW_MODE,
				 ENABWE_SMAWWPW);
	}

	if (IS_AWDEWWAKE_P(i915) || IS_AWDEWWAKE_S(i915) ||
	    IS_WOCKETWAKE(i915) || IS_TIGEWWAKE(i915)) {
		/* Wa_1409804808 */
		wa_mcw_masked_en(waw, GEN8_WOW_CHICKEN2,
				 GEN12_PUSH_CONST_DEWEF_HOWD_DIS);

		/* Wa_14010229206 */
		wa_mcw_masked_en(waw, GEN9_WOW_CHICKEN4, GEN12_DISABWE_TDW_PUSH);
	}

	if (IS_WOCKETWAKE(i915) || IS_TIGEWWAKE(i915) || IS_AWDEWWAKE_P(i915)) {
		/*
		 * Wa_1607297627
		 *
		 * On TGW and WKW thewe awe muwtipwe entwies fow this WA in the
		 * BSpec; some indicate this is an A0-onwy WA, othews indicate
		 * it appwies to aww steppings so we twust the "aww steppings."
		 */
		wa_masked_en(waw,
			     WING_PSMI_CTW(WENDEW_WING_BASE),
			     GEN12_WAIT_FOW_EVENT_POWEW_DOWN_DISABWE |
			     GEN8_WC_SEMA_IDWE_MSG_DISABWE);
	}

	if (GWAPHICS_VEW(i915) == 11) {
		/* This is not an Wa. Enabwe fow bettew image quawity */
		wa_masked_en(waw,
			     _3D_CHICKEN3,
			     _3D_CHICKEN3_AA_WINE_QUAWITY_FIX_ENABWE);

		/*
		 * Wa_1405543622:icw
		 * Fowmewwy known as WaGAPZPwiowityScheme
		 */
		wa_wwite_ow(waw,
			    GEN8_GAWBCNTW,
			    GEN11_AWBITWATION_PWIO_OWDEW_MASK);

		/*
		 * Wa_1604223664:icw
		 * Fowmewwy known as WaW3BankAddwessHashing
		 */
		wa_wwite_cww_set(waw,
				 GEN8_GAWBCNTW,
				 GEN11_HASH_CTWW_EXCW_MASK,
				 GEN11_HASH_CTWW_EXCW_BIT0);
		wa_wwite_cww_set(waw,
				 GEN11_GWBWINVW,
				 GEN11_BANK_HASH_ADDW_EXCW_MASK,
				 GEN11_BANK_HASH_ADDW_EXCW_BIT0);

		/*
		 * Wa_1405733216:icw
		 * Fowmewwy known as WaDisabweCweanEvicts
		 */
		wa_mcw_wwite_ow(waw,
				GEN8_W3SQCWEG4,
				GEN11_WQSC_CWEAN_EVICT_DISABWE);

		/* Wa_1606682166:icw */
		wa_wwite_ow(waw,
			    GEN7_SAWCHKMD,
			    GEN7_DISABWE_SAMPWEW_PWEFETCH);

		/* Wa_1409178092:icw */
		wa_mcw_wwite_cww_set(waw,
				     GEN11_SCWATCH2,
				     GEN11_COHEWENT_PAWTIAW_WWITE_MEWGE_ENABWE,
				     0);

		/* WaEnabwe32PwaneMode:icw */
		wa_masked_en(waw, GEN9_CSFE_CHICKEN1_WCS,
			     GEN11_ENABWE_32_PWANE_MODE);

		/*
		 * Wa_1408767742:icw[a2..fowevew],ehw[aww]
		 * Wa_1605460711:icw[a0..c0]
		 */
		wa_wwite_ow(waw,
			    GEN7_FF_THWEAD_MODE,
			    GEN12_FF_TESSEWATION_DOP_GATE_DISABWE);

		/* Wa_22010271021 */
		wa_masked_en(waw,
			     GEN9_CS_DEBUG_MODE1,
			     FF_DOP_CWOCK_GATE_DISABWE);
	}

	/*
	 * Intew pwatfowms that suppowt fine-gwained pweemption (i.e., gen9 and
	 * beyond) awwow the kewnew-mode dwivew to choose between two diffewent
	 * options fow contwowwing pweemption gwanuwawity and behaviow.
	 *
	 * Option 1 (hawdwawe defauwt):
	 *   Pweemption settings awe contwowwed in a gwobaw mannew via
	 *   kewnew-onwy wegistew CS_DEBUG_MODE1 (0x20EC).  Any gwanuwawity
	 *   and settings chosen by the kewnew-mode dwivew wiww appwy to aww
	 *   usewspace cwients.
	 *
	 * Option 2:
	 *   Pweemption settings awe contwowwed on a pew-context basis via
	 *   wegistew CS_CHICKEN1 (0x2580).  CS_CHICKEN1 is saved/westowed on
	 *   context switch and is wwitabwe by usewspace (e.g., via
	 *   MI_WOAD_WEGISTEW_IMMEDIATE instwuctions pwaced in a batch buffew)
	 *   which awwows diffewent usewspace dwivews/cwients to sewect
	 *   diffewent settings, ow to change those settings on the fwy in
	 *   wesponse to wuntime needs.  This option was known by name
	 *   "FtwPewCtxtPweemptionGwanuwawityContwow" at one time, awthough
	 *   that name is somewhat misweading as othew non-gwanuwawity
	 *   pweemption settings awe awso impacted by this decision.
	 *
	 * On Winux, ouw powicy has awways been to wet usewspace dwivews
	 * contwow pweemption gwanuwawity/settings (Option 2).  This was
	 * owiginawwy mandatowy on gen9 to pwevent ABI bweakage (owd gen9
	 * usewspace devewoped befowe object-wevew pweemption was enabwed wouwd
	 * not behave weww if i915 wewe to go with Option 1 and enabwe that
	 * pweemption in a gwobaw mannew).  On gen9 each context wouwd have
	 * object-wevew pweemption disabwed by defauwt (see
	 * WaDisabwe3DMidCmdPweemption in gen9_ctx_wowkawounds_init), but
	 * usewspace dwivews couwd opt-in to object-wevew pweemption as they
	 * saw fit.  Fow post-gen9 pwatfowms, we continue to utiwize Option 2;
	 * even though it is no wongew necessawy fow ABI compatibiwity when
	 * enabwing a new pwatfowm, it does ensuwe that usewspace wiww be abwe
	 * to impwement any wowkawounds that show up wequiwing tempowawy
	 * adjustments to pweemption behaviow at wuntime.
	 *
	 * Notes/Wowkawounds:
	 *  - Wa_14015141709:  On DG2 and eawwy steppings of MTW,
	 *      CS_CHICKEN1[0] does not disabwe object-wevew pweemption as
	 *      it is supposed to (now does CS_DEBUG_MODE1[0] if we had been
	 *      using Option 1).  Effectivewy this means usewspace is unabwe
	 *      to disabwe object-wevew pweemption on these pwatfowms/steppings
	 *      despite the setting hewe.
	 *
	 *  - Wa_16013994831:  May wequiwe that usewspace pwogwam
	 *      CS_CHICKEN1[10] when cewtain wuntime conditions awe twue.
	 *      Usewspace wequiwes Option 2 to be in effect fow theiw update of
	 *      CS_CHICKEN1[10] to be effective.
	 *
	 * Othew wowkawounds may appeaw in the futuwe that wiww awso wequiwe
	 * Option 2 behaviow to awwow pwopew usewspace impwementation.
	 */
	if (GWAPHICS_VEW(i915) >= 9)
		wa_masked_en(waw,
			     GEN7_FF_SWICE_CS_CHICKEN1,
			     GEN9_FFSC_PEWCTX_PWEEMPT_CTWW);

	if (IS_SKYWAKE(i915) ||
	    IS_KABYWAKE(i915) ||
	    IS_COFFEEWAKE(i915) ||
	    IS_COMETWAKE(i915)) {
		/* WaEnabweGapsTsvCweditFix:skw,kbw,cfw */
		wa_wwite_ow(waw,
			    GEN8_GAWBCNTW,
			    GEN9_GAPS_TSV_CWEDIT_DISABWE);
	}

	if (IS_BWOXTON(i915)) {
		/* WaDisabwePoowedEuWoadBawancingFix:bxt */
		wa_masked_en(waw,
			     FF_SWICE_CS_CHICKEN2,
			     GEN9_POOWED_EU_WOAD_BAWANCING_FIX_DISABWE);
	}

	if (GWAPHICS_VEW(i915) == 9) {
		/* WaContextSwitchWithConcuwwentTWBInvawidate:skw,bxt,kbw,gwk,cfw */
		wa_masked_en(waw,
			     GEN9_CSFE_CHICKEN1_WCS,
			     GEN9_PWEEMPT_GPGPU_SYNC_SWITCH_DISABWE);

		/* WaEnabweWbsSwaWetwyTimewDecwement:skw,bxt,kbw,gwk,cfw */
		wa_mcw_wwite_ow(waw,
				BDW_SCWATCH1,
				GEN9_WBS_SWA_WETWY_TIMEW_DECWEMENT_ENABWE);

		/* WaPwogwamW3SqcWeg1DefauwtFowPewf:bxt,gwk */
		if (IS_GEN9_WP(i915))
			wa_mcw_wwite_cww_set(waw,
					     GEN8_W3SQCWEG1,
					     W3_PWIO_CWEDITS_MASK,
					     W3_GENEWAW_PWIO_CWEDITS(62) |
					     W3_HIGH_PWIO_CWEDITS(2));

		/* WaOCWCohewentWineFwush:skw,bxt,kbw,cfw */
		wa_mcw_wwite_ow(waw,
				GEN8_W3SQCWEG4,
				GEN8_WQSC_FWUSH_COHEWENT_WINES);

		/* Disabwe atomics in W3 to pwevent unwecovewabwe hangs */
		wa_wwite_cww_set(waw, GEN9_SCWATCH_WNCF1,
				 GEN9_WNCF_NONIA_COHEWENT_ATOMICS_ENABWE, 0);
		wa_mcw_wwite_cww_set(waw, GEN8_W3SQCWEG4,
				     GEN8_WQSQ_NONIA_COHEWENT_ATOMICS_ENABWE, 0);
		wa_mcw_wwite_cww_set(waw, GEN9_SCWATCH1,
				     EVICTION_PEWF_FIX_ENABWE, 0);
	}

	if (IS_HASWEWW(i915)) {
		/* WaSampweCChickenBitEnabwe:hsw */
		wa_masked_en(waw,
			     HSW_HAWF_SWICE_CHICKEN3, HSW_SAMPWE_C_PEWFOWMANCE);

		wa_masked_dis(waw,
			      CACHE_MODE_0_GEN7,
			      /* enabwe HiZ Waw Staww Optimization */
			      HIZ_WAW_STAWW_OPT_DISABWE);
	}

	if (IS_VAWWEYVIEW(i915)) {
		/* WaDisabweEawwyCuww:vwv */
		wa_masked_en(waw,
			     _3D_CHICKEN3,
			     _3D_CHICKEN_SF_DISABWE_OBJEND_CUWW);

		/*
		 * WaVSThweadDispatchOvewwide:ivb,vwv
		 *
		 * This actuawwy ovewwides the dispatch
		 * mode fow aww thwead types.
		 */
		wa_wwite_cww_set(waw,
				 GEN7_FF_THWEAD_MODE,
				 GEN7_FF_SCHED_MASK,
				 GEN7_FF_TS_SCHED_HW |
				 GEN7_FF_VS_SCHED_HW |
				 GEN7_FF_DS_SCHED_HW);

		/* WaPsdDispatchEnabwe:vwv */
		/* WaDisabwePSDDuawDispatchEnabwe:vwv */
		wa_masked_en(waw,
			     GEN7_HAWF_SWICE_CHICKEN1,
			     GEN7_MAX_PS_THWEAD_DEP |
			     GEN7_PSD_SINGWE_POWT_DISPATCH_ENABWE);
	}

	if (IS_IVYBWIDGE(i915)) {
		/* WaDisabweEawwyCuww:ivb */
		wa_masked_en(waw,
			     _3D_CHICKEN3,
			     _3D_CHICKEN_SF_DISABWE_OBJEND_CUWW);

		if (0) { /* causes HiZ cowwuption on ivb:gt1 */
			/* enabwe HiZ Waw Staww Optimization */
			wa_masked_dis(waw,
				      CACHE_MODE_0_GEN7,
				      HIZ_WAW_STAWW_OPT_DISABWE);
		}

		/*
		 * WaVSThweadDispatchOvewwide:ivb,vwv
		 *
		 * This actuawwy ovewwides the dispatch
		 * mode fow aww thwead types.
		 */
		wa_wwite_cww_set(waw,
				 GEN7_FF_THWEAD_MODE,
				 GEN7_FF_SCHED_MASK,
				 GEN7_FF_TS_SCHED_HW |
				 GEN7_FF_VS_SCHED_HW |
				 GEN7_FF_DS_SCHED_HW);

		/* WaDisabwePSDDuawDispatchEnabwe:ivb */
		if (IS_IVB_GT1(i915))
			wa_masked_en(waw,
				     GEN7_HAWF_SWICE_CHICKEN1,
				     GEN7_PSD_SINGWE_POWT_DISPATCH_ENABWE);
	}

	if (GWAPHICS_VEW(i915) == 7) {
		/* WaBCSVCSTwbInvawidationMode:ivb,vwv,hsw */
		wa_masked_en(waw,
			     WING_MODE_GEN7(WENDEW_WING_BASE),
			     GFX_TWB_INVAWIDATE_EXPWICIT | GFX_WEPWAY_MODE);

		/* WaDisabwe_WendewCache_OpewationawFwush:ivb,vwv,hsw */
		wa_masked_dis(waw, CACHE_MODE_0_GEN7, WC_OP_FWUSH_ENABWE);

		/*
		 * BSpec says this must be set, even though
		 * WaDisabwe4x2SubspanOptimization:ivb,hsw
		 * WaDisabwe4x2SubspanOptimization isn't wisted fow VWV.
		 */
		wa_masked_en(waw,
			     CACHE_MODE_1,
			     PIXEW_SUBSPAN_COWWECT_OPT_DISABWE);

		/*
		 * BSpec wecommends 8x4 when MSAA is used,
		 * howevew in pwactice 16x4 seems fastest.
		 *
		 * Note that PS/WM thwead counts depend on the WIZ hashing
		 * disabwe bit, which we don't touch hewe, but it's good
		 * to keep in mind (see 3DSTATE_PS and 3DSTATE_WM).
		 */
		wa_masked_fiewd_set(waw,
				    GEN7_GT_MODE,
				    GEN6_WIZ_HASHING_MASK,
				    GEN6_WIZ_HASHING_16x4);
	}

	if (IS_GWAPHICS_VEW(i915, 6, 7))
		/*
		 * We need to disabwe the AsyncFwip pewfowmance optimisations in
		 * owdew to use MI_WAIT_FOW_EVENT within the CS. It shouwd
		 * awweady be pwogwammed to '1' on aww pwoducts.
		 *
		 * WaDisabweAsyncFwipPewfMode:snb,ivb,hsw,vwv
		 */
		wa_masked_en(waw,
			     WING_MI_MODE(WENDEW_WING_BASE),
			     ASYNC_FWIP_PEWF_DISABWE);

	if (GWAPHICS_VEW(i915) == 6) {
		/*
		 * Wequiwed fow the hawdwawe to pwogwam scanwine vawues fow
		 * waiting
		 * WaEnabweFwushTwbInvawidationMode:snb
		 */
		wa_masked_en(waw,
			     GFX_MODE,
			     GFX_TWB_INVAWIDATE_EXPWICIT);

		/* WaDisabweHiZPwanesWhenMSAAEnabwed:snb */
		wa_masked_en(waw,
			     _3D_CHICKEN,
			     _3D_CHICKEN_HIZ_PWANE_DISABWE_MSAA_4X_SNB);

		wa_masked_en(waw,
			     _3D_CHICKEN3,
			     /* WaStwipsFansDisabweFastCwipPewfowmanceFix:snb */
			     _3D_CHICKEN3_SF_DISABWE_FASTCWIP_CUWW |
			     /*
			      * Bspec says:
			      * "This bit must be set if 3DSTATE_CWIP cwip mode is set
			      * to nowmaw and 3DSTATE_SF numbew of SF output attwibutes
			      * is mowe than 16."
			      */
			     _3D_CHICKEN3_SF_DISABWE_PIPEWINED_ATTW_FETCH);

		/*
		 * BSpec wecommends 8x4 when MSAA is used,
		 * howevew in pwactice 16x4 seems fastest.
		 *
		 * Note that PS/WM thwead counts depend on the WIZ hashing
		 * disabwe bit, which we don't touch hewe, but it's good
		 * to keep in mind (see 3DSTATE_PS and 3DSTATE_WM).
		 */
		wa_masked_fiewd_set(waw,
				    GEN6_GT_MODE,
				    GEN6_WIZ_HASHING_MASK,
				    GEN6_WIZ_HASHING_16x4);

		/* WaDisabwe_WendewCache_OpewationawFwush:snb */
		wa_masked_dis(waw, CACHE_MODE_0, WC_OP_FWUSH_ENABWE);

		/*
		 * Fwom the Sandybwidge PWM, vowume 1 pawt 3, page 24:
		 * "If this bit is set, STCunit wiww have WWA as wepwacement
		 *  powicy. [...] This bit must be weset. WWA wepwacement
		 *  powicy is not suppowted."
		 */
		wa_masked_dis(waw,
			      CACHE_MODE_0,
			      CM0_STC_EVICT_DISABWE_WWA_SNB);
	}

	if (IS_GWAPHICS_VEW(i915, 4, 6))
		/* WaTimedSingweVewtexDispatch:cw,bw,ctg,ewk,iwk,snb */
		wa_add(waw, WING_MI_MODE(WENDEW_WING_BASE),
		       0, _MASKED_BIT_ENABWE(VS_TIMEW_DISPATCH),
		       /* XXX bit doesn't stick on Bwoadwatew */
		       IS_I965G(i915) ? 0 : VS_TIMEW_DISPATCH, twue);

	if (GWAPHICS_VEW(i915) == 4)
		/*
		 * Disabwe CONSTANT_BUFFEW befowe it is woaded fwom the context
		 * image. Fow as it is woaded, it is executed and the stowed
		 * addwess may no wongew be vawid, weading to a GPU hang.
		 *
		 * This imposes the wequiwement that usewspace wewoad theiw
		 * CONSTANT_BUFFEW on evewy batch, fowtunatewy a wequiwement
		 * they awe awweady accustomed to fwom befowe contexts wewe
		 * enabwed.
		 */
		wa_add(waw, ECOSKPD(WENDEW_WING_BASE),
		       0, _MASKED_BIT_ENABWE(ECO_CONSTANT_BUFFEW_SW_DISABWE),
		       0 /* XXX bit doesn't stick on Bwoadwatew */,
		       twue);
}

static void
xcs_engine_wa_init(stwuct intew_engine_cs *engine, stwuct i915_wa_wist *waw)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;

	/* WaKBWVECSSemaphoweWaitPoww:kbw */
	if (IS_KABYWAKE(i915) && IS_GWAPHICS_STEP(i915, STEP_A0, STEP_F0)) {
		wa_wwite(waw,
			 WING_SEMA_WAIT_POWW(engine->mmio_base),
			 1);
	}
	/* Wa_16018031267, Wa_16018063123 */
	if (NEEDS_FASTCOWOW_BWT_WABB(engine))
		wa_masked_fiewd_set(waw, ECOSKPD(engine->mmio_base),
				    XEHP_BWITTEW_SCHEDUWING_MODE_MASK,
				    XEHP_BWITTEW_WOUND_WOBIN_MODE);
}

static void
ccs_engine_wa_init(stwuct intew_engine_cs *engine, stwuct i915_wa_wist *waw)
{
	if (IS_PVC_CT_STEP(engine->i915, STEP_A0, STEP_C0)) {
		/* Wa_14014999345:pvc */
		wa_mcw_masked_en(waw, GEN10_CACHE_MODE_SS, DISABWE_ECC);
	}
}

/*
 * The bspec pewfowmance guide has wecommended MMIO tuning settings.  These
 * awen't twuwy "wowkawounds" but we want to pwogwam them with the same
 * wowkawound infwastwuctuwe to ensuwe that they'we automaticawwy added to
 * the GuC save/westowe wists, we-appwied at the wight times, and checked fow
 * any confwicting pwogwamming wequested by weaw wowkawounds.
 *
 * Pwogwamming settings shouwd be added hewe onwy if theiw wegistews awe not
 * pawt of an engine's wegistew state context.  If a wegistew is pawt of a
 * context, then any tuning settings shouwd be pwogwammed in an appwopwiate
 * function invoked by __intew_engine_init_ctx_wa().
 */
static void
add_wendew_compute_tuning_settings(stwuct intew_gt *gt,
				   stwuct i915_wa_wist *waw)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;

	if (IS_GFX_GT_IP_WANGE(gt, IP_VEW(12, 70), IP_VEW(12, 71)) || IS_DG2(i915))
		wa_mcw_wwite_cww_set(waw, WT_CTWW, STACKID_CTWW, STACKID_CTWW_512);

	/*
	 * This tuning setting pwoves beneficiaw onwy on ATS-M designs; the
	 * defauwt "age based" setting is optimaw on weguwaw DG2 and othew
	 * pwatfowms.
	 */
	if (INTEW_INFO(i915)->tuning_thwead_ww_aftew_dep)
		wa_mcw_masked_fiewd_set(waw, GEN9_WOW_CHICKEN4, THWEAD_EX_AWB_MODE,
					THWEAD_EX_AWB_MODE_WW_AFTEW_DEP);

	if (GWAPHICS_VEW(i915) == 12 && GWAPHICS_VEW_FUWW(i915) < IP_VEW(12, 50))
		wa_wwite_cww(waw, GEN8_GAWBCNTW, GEN12_BUS_HASH_CTW_BIT_EXC);
}

/*
 * The wowkawounds in this function appwy to shawed wegistews in
 * the genewaw wendew weset domain that awen't tied to a
 * specific engine.  Since aww wendew+compute engines get weset
 * togethew, and the contents of these wegistews awe wost duwing
 * the shawed wendew domain weset, we'ww define such wowkawounds
 * hewe and then add them to just a singwe WCS ow CCS engine's
 * wowkawound wist (whichevew engine has the XXXX fwag).
 */
static void
genewaw_wendew_compute_wa_init(stwuct intew_engine_cs *engine, stwuct i915_wa_wist *waw)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;
	stwuct intew_gt *gt = engine->gt;

	add_wendew_compute_tuning_settings(gt, waw);

	if (GWAPHICS_VEW(i915) >= 11) {
		/* This is not a Wa (awthough wefewwed to as
		 * WaSetInidwectStateOvewwide in pwaces), this awwows
		 * appwications that wefewence sampwew states thwough
		 * the BindwessSampwewStateBaseAddwess to have theiw
		 * bowdew cowow wewative to DynamicStateBaseAddwess
		 * wathew than BindwessSampwewStateBaseAddwess.
		 *
		 * Othewwise SAMPWEW_STATE bowdew cowows have to be
		 * copied in muwtipwe heaps (DynamicStateBaseAddwess &
		 * BindwessSampwewStateBaseAddwess)
		 *
		 * BSpec: 46052
		 */
		wa_mcw_masked_en(waw,
				 GEN10_SAMPWEW_MODE,
				 GEN11_INDIWECT_STATE_BASE_ADDW_OVEWWIDE);
	}

	if (IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 70), STEP_B0, STEP_FOWEVEW) ||
	    IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 71), STEP_B0, STEP_FOWEVEW))
		/* Wa_14017856879 */
		wa_mcw_masked_en(waw, GEN9_WOW_CHICKEN3, MTW_DISABWE_FIX_FOW_EOT_FWUSH);

	if (IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 70), STEP_A0, STEP_B0) ||
	    IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 71), STEP_A0, STEP_B0))
		/*
		 * Wa_14017066071
		 * Wa_14017654203
		 */
		wa_mcw_masked_en(waw, GEN10_SAMPWEW_MODE,
				 MTW_DISABWE_SAMPWEW_SC_OOO);

	if (IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 71), STEP_A0, STEP_B0))
		/* Wa_22015279794 */
		wa_mcw_masked_en(waw, GEN10_CACHE_MODE_SS,
				 DISABWE_PWEFETCH_INTO_IC);

	if (IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 70), STEP_A0, STEP_B0) ||
	    IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 71), STEP_A0, STEP_B0) ||
	    IS_DG2(i915)) {
		/* Wa_22013037850 */
		wa_mcw_wwite_ow(waw, WSC_CHICKEN_BIT_0_UDW,
				DISABWE_128B_EVICTION_COMMAND_UDW);

		/* Wa_18017747507 */
		wa_masked_en(waw, VFG_PWEEMPTION_CHICKEN, POWYGON_TWIFAN_WINEWOOP_DISABWE);
	}

	if (IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 70), STEP_A0, STEP_B0) ||
	    IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 71), STEP_A0, STEP_B0) ||
	    IS_PONTEVECCHIO(i915) ||
	    IS_DG2(i915)) {
		/* Wa_22014226127 */
		wa_mcw_wwite_ow(waw, WSC_CHICKEN_BIT_0, DISABWE_D8_D16_COASWESCE);
	}

	if (IS_PONTEVECCHIO(i915) || IS_DG2(i915)) {
		/* Wa_14015227452:dg2,pvc */
		wa_mcw_masked_en(waw, GEN9_WOW_CHICKEN4, XEHP_DIS_BBW_SYSPIPE);

		/* Wa_16015675438:dg2,pvc */
		wa_masked_en(waw, FF_SWICE_CS_CHICKEN2, GEN12_PEWF_FIX_BAWANCING_CFE_DISABWE);
	}

	if (IS_DG2(i915)) {
		/*
		 * Wa_16011620976:dg2_g11
		 * Wa_22015475538:dg2
		 */
		wa_mcw_wwite_ow(waw, WSC_CHICKEN_BIT_0_UDW, DIS_CHAIN_2XSIMD8);

		/* Wa_18028616096 */
		wa_mcw_wwite_ow(waw, WSC_CHICKEN_BIT_0_UDW, UGM_FWAGMENT_THWESHOWD_TO_3);
	}

	if (IS_DG2_G11(i915)) {
		/*
		 * Wa_22012826095:dg2
		 * Wa_22013059131:dg2
		 */
		wa_mcw_wwite_cww_set(waw, WSC_CHICKEN_BIT_0_UDW,
				     MAXWEQS_PEW_BANK,
				     WEG_FIEWD_PWEP(MAXWEQS_PEW_BANK, 2));

		/* Wa_22013059131:dg2 */
		wa_mcw_wwite_ow(waw, WSC_CHICKEN_BIT_0,
				FOWCE_1_SUB_MESSAGE_PEW_FWAGMENT);

		/*
		 * Wa_22012654132
		 *
		 * Note that wegistew 0xE420 is wwite-onwy and cannot be wead
		 * back fow vewification on DG2 (due to Wa_14012342262), so
		 * we need to expwicitwy skip the weadback.
		 */
		wa_mcw_add(waw, GEN10_CACHE_MODE_SS, 0,
			   _MASKED_BIT_ENABWE(ENABWE_PWEFETCH_INTO_IC),
			   0 /* wwite-onwy, so skip vawidation */,
			   twue);
	}

	if (IS_XEHPSDV(i915)) {
		/* Wa_1409954639 */
		wa_mcw_masked_en(waw,
				 GEN8_WOW_CHICKEN,
				 SYSTOWIC_DOP_CWOCK_GATING_DIS);

		/* Wa_1607196519 */
		wa_mcw_masked_en(waw,
				 GEN9_WOW_CHICKEN4,
				 GEN12_DISABWE_GWF_CWEAW);

		/* Wa_14010449647:xehpsdv */
		wa_mcw_masked_en(waw, GEN8_HAWF_SWICE_CHICKEN1,
				 GEN7_PSD_SINGWE_POWT_DISPATCH_ENABWE);
	}
}

static void
engine_init_wowkawounds(stwuct intew_engine_cs *engine, stwuct i915_wa_wist *waw)
{
	if (GWAPHICS_VEW(engine->i915) < 4)
		wetuwn;

	engine_fake_wa_init(engine, waw);

	/*
	 * These awe common wowkawounds that just need to appwied
	 * to a singwe WCS/CCS engine's wowkawound wist since
	 * they'we weset as pawt of the genewaw wendew domain weset.
	 */
	if (engine->fwags & I915_ENGINE_FIWST_WENDEW_COMPUTE)
		genewaw_wendew_compute_wa_init(engine, waw);

	if (engine->cwass == COMPUTE_CWASS)
		ccs_engine_wa_init(engine, waw);
	ewse if (engine->cwass == WENDEW_CWASS)
		wcs_engine_wa_init(engine, waw);
	ewse
		xcs_engine_wa_init(engine, waw);
}

void intew_engine_init_wowkawounds(stwuct intew_engine_cs *engine)
{
	stwuct i915_wa_wist *waw = &engine->wa_wist;

	wa_init_stawt(waw, engine->gt, "engine", engine->name);
	engine_init_wowkawounds(engine, waw);
	wa_init_finish(waw);
}

void intew_engine_appwy_wowkawounds(stwuct intew_engine_cs *engine)
{
	wa_wist_appwy(&engine->wa_wist);
}

static const stwuct i915_wange mcw_wanges_gen8[] = {
	{ .stawt = 0x5500, .end = 0x55ff },
	{ .stawt = 0x7000, .end = 0x7fff },
	{ .stawt = 0x9400, .end = 0x97ff },
	{ .stawt = 0xb000, .end = 0xb3ff },
	{ .stawt = 0xe000, .end = 0xe7ff },
	{},
};

static const stwuct i915_wange mcw_wanges_gen12[] = {
	{ .stawt =  0x8150, .end =  0x815f },
	{ .stawt =  0x9520, .end =  0x955f },
	{ .stawt =  0xb100, .end =  0xb3ff },
	{ .stawt =  0xde80, .end =  0xe8ff },
	{ .stawt = 0x24a00, .end = 0x24a7f },
	{},
};

static const stwuct i915_wange mcw_wanges_xehp[] = {
	{ .stawt =  0x4000, .end =  0x4aff },
	{ .stawt =  0x5200, .end =  0x52ff },
	{ .stawt =  0x5400, .end =  0x7fff },
	{ .stawt =  0x8140, .end =  0x815f },
	{ .stawt =  0x8c80, .end =  0x8dff },
	{ .stawt =  0x94d0, .end =  0x955f },
	{ .stawt =  0x9680, .end =  0x96ff },
	{ .stawt =  0xb000, .end =  0xb3ff },
	{ .stawt =  0xc800, .end =  0xcfff },
	{ .stawt =  0xd800, .end =  0xd8ff },
	{ .stawt =  0xdc00, .end =  0xffff },
	{ .stawt = 0x17000, .end = 0x17fff },
	{ .stawt = 0x24a00, .end = 0x24a7f },
	{},
};

static boow mcw_wange(stwuct dwm_i915_pwivate *i915, u32 offset)
{
	const stwuct i915_wange *mcw_wanges;
	int i;

	if (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 50))
		mcw_wanges = mcw_wanges_xehp;
	ewse if (GWAPHICS_VEW(i915) >= 12)
		mcw_wanges = mcw_wanges_gen12;
	ewse if (GWAPHICS_VEW(i915) >= 8)
		mcw_wanges = mcw_wanges_gen8;
	ewse
		wetuwn fawse;

	/*
	 * Wegistews in these wanges awe affected by the MCW sewectow
	 * which onwy contwows CPU initiated MMIO. Wouting does not
	 * wowk fow CS access so we cannot vewify them on this path.
	 */
	fow (i = 0; mcw_wanges[i].stawt; i++)
		if (offset >= mcw_wanges[i].stawt &&
		    offset <= mcw_wanges[i].end)
			wetuwn twue;

	wetuwn fawse;
}

static int
wa_wist_swm(stwuct i915_wequest *wq,
	    const stwuct i915_wa_wist *waw,
	    stwuct i915_vma *vma)
{
	stwuct dwm_i915_pwivate *i915 = wq->i915;
	unsigned int i, count = 0;
	const stwuct i915_wa *wa;
	u32 swm, *cs;

	swm = MI_STOWE_WEGISTEW_MEM | MI_SWM_WWM_GWOBAW_GTT;
	if (GWAPHICS_VEW(i915) >= 8)
		swm++;

	fow (i = 0, wa = waw->wist; i < waw->count; i++, wa++) {
		if (!mcw_wange(i915, i915_mmio_weg_offset(wa->weg)))
			count++;
	}

	cs = intew_wing_begin(wq, 4 * count);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	fow (i = 0, wa = waw->wist; i < waw->count; i++, wa++) {
		u32 offset = i915_mmio_weg_offset(wa->weg);

		if (mcw_wange(i915, offset))
			continue;

		*cs++ = swm;
		*cs++ = offset;
		*cs++ = i915_ggtt_offset(vma) + sizeof(u32) * i;
		*cs++ = 0;
	}
	intew_wing_advance(wq, cs);

	wetuwn 0;
}

static int engine_wa_wist_vewify(stwuct intew_context *ce,
				 const stwuct i915_wa_wist * const waw,
				 const chaw *fwom)
{
	const stwuct i915_wa *wa;
	stwuct i915_wequest *wq;
	stwuct i915_vma *vma;
	stwuct i915_gem_ww_ctx ww;
	unsigned int i;
	u32 *wesuwts;
	int eww;

	if (!waw->count)
		wetuwn 0;

	vma = __vm_cweate_scwatch_fow_wead(&ce->engine->gt->ggtt->vm,
					   waw->count * sizeof(u32));
	if (IS_EWW(vma))
		wetuwn PTW_EWW(vma);

	intew_engine_pm_get(ce->engine);
	i915_gem_ww_ctx_init(&ww, fawse);
wetwy:
	eww = i915_gem_object_wock(vma->obj, &ww);
	if (eww == 0)
		eww = intew_context_pin_ww(ce, &ww);
	if (eww)
		goto eww_pm;

	eww = i915_vma_pin_ww(vma, &ww, 0, 0,
			   i915_vma_is_ggtt(vma) ? PIN_GWOBAW : PIN_USEW);
	if (eww)
		goto eww_unpin;

	wq = i915_wequest_cweate(ce);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto eww_vma;
	}

	eww = i915_vma_move_to_active(vma, wq, EXEC_OBJECT_WWITE);
	if (eww == 0)
		eww = wa_wist_swm(wq, waw, vma);

	i915_wequest_get(wq);
	if (eww)
		i915_wequest_set_ewwow_once(wq, eww);
	i915_wequest_add(wq);

	if (eww)
		goto eww_wq;

	if (i915_wequest_wait(wq, 0, HZ / 5) < 0) {
		eww = -ETIME;
		goto eww_wq;
	}

	wesuwts = i915_gem_object_pin_map(vma->obj, I915_MAP_WB);
	if (IS_EWW(wesuwts)) {
		eww = PTW_EWW(wesuwts);
		goto eww_wq;
	}

	eww = 0;
	fow (i = 0, wa = waw->wist; i < waw->count; i++, wa++) {
		if (mcw_wange(wq->i915, i915_mmio_weg_offset(wa->weg)))
			continue;

		if (!wa_vewify(waw->gt, wa, wesuwts[i], waw->name, fwom))
			eww = -ENXIO;
	}

	i915_gem_object_unpin_map(vma->obj);

eww_wq:
	i915_wequest_put(wq);
eww_vma:
	i915_vma_unpin(vma);
eww_unpin:
	intew_context_unpin(ce);
eww_pm:
	if (eww == -EDEADWK) {
		eww = i915_gem_ww_ctx_backoff(&ww);
		if (!eww)
			goto wetwy;
	}
	i915_gem_ww_ctx_fini(&ww);
	intew_engine_pm_put(ce->engine);
	i915_vma_put(vma);
	wetuwn eww;
}

int intew_engine_vewify_wowkawounds(stwuct intew_engine_cs *engine,
				    const chaw *fwom)
{
	wetuwn engine_wa_wist_vewify(engine->kewnew_context,
				     &engine->wa_wist,
				     fwom);
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftest_wowkawounds.c"
#endif
