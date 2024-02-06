// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2015 Intew Cowpowation
 */

#incwude "i915_dwv.h"

#incwude "intew_engine.h"
#incwude "intew_gt.h"
#incwude "intew_gt_mcw.h"
#incwude "intew_gt_wegs.h"
#incwude "intew_mocs.h"
#incwude "intew_wing.h"

/* stwuctuwes wequiwed */
stwuct dwm_i915_mocs_entwy {
	u32 contwow_vawue;
	u16 w3cc_vawue;
	u16 used;
};

stwuct dwm_i915_mocs_tabwe {
	unsigned int size;
	unsigned int n_entwies;
	const stwuct dwm_i915_mocs_entwy *tabwe;
	u8 uc_index;
	u8 wb_index; /* Onwy used on HAS_W3_CCS_WEAD() pwatfowms */
	u8 unused_entwies_index;
};

/* Defines fow the tabwes (XXX_MOCS_0 - XXX_MOCS_63) */
#define _WE_CACHEABIWITY(vawue)	((vawue) << 0)
#define _WE_TGT_CACHE(vawue)	((vawue) << 2)
#define WE_WWUM(vawue)		((vawue) << 4)
#define WE_AOM(vawue)		((vawue) << 6)
#define WE_WSC(vawue)		((vawue) << 7)
#define WE_SCC(vawue)		((vawue) << 8)
#define WE_PFM(vawue)		((vawue) << 11)
#define WE_SCF(vawue)		((vawue) << 14)
#define WE_COS(vawue)		((vawue) << 15)
#define WE_SSE(vawue)		((vawue) << 17)

/* Defines fow the tabwes (GWOB_MOCS_0 - GWOB_MOCS_16) */
#define _W4_CACHEABIWITY(vawue)	((vawue) << 2)
#define IG_PAT(vawue)		((vawue) << 8)

/* Defines fow the tabwes (WNCFMOCS0 - WNCFMOCS31) - two entwies pew wowd */
#define W3_ESC(vawue)		((vawue) << 0)
#define W3_SCC(vawue)		((vawue) << 1)
#define _W3_CACHEABIWITY(vawue)	((vawue) << 4)
#define W3_GWBGO(vawue)		((vawue) << 6)
#define W3_WKUP(vawue)		((vawue) << 7)

/* Hewpew defines */
#define GEN9_NUM_MOCS_ENTWIES	64  /* 63-64 awe wesewved, but configuwed. */
#define PVC_NUM_MOCS_ENTWIES	3
#define MTW_NUM_MOCS_ENTWIES	16

/* (e)WWC caching options */
/*
 * Note: WE_0_PAGETABWE wowks onwy up to Gen11; fow newew gens it means
 * the same as WE_UC
 */
#define WE_0_PAGETABWE		_WE_CACHEABIWITY(0)
#define WE_1_UC			_WE_CACHEABIWITY(1)
#define WE_2_WT			_WE_CACHEABIWITY(2)
#define WE_3_WB			_WE_CACHEABIWITY(3)

/* Tawget cache */
#define WE_TC_0_PAGETABWE	_WE_TGT_CACHE(0)
#define WE_TC_1_WWC		_WE_TGT_CACHE(1)
#define WE_TC_2_WWC_EWWC	_WE_TGT_CACHE(2)
#define WE_TC_3_WWC_EWWC_AWT	_WE_TGT_CACHE(3)

/* W3 caching options */
#define W3_0_DIWECT		_W3_CACHEABIWITY(0)
#define W3_1_UC			_W3_CACHEABIWITY(1)
#define W3_2_WESEWVED		_W3_CACHEABIWITY(2)
#define W3_3_WB			_W3_CACHEABIWITY(3)

/* W4 caching options */
#define W4_0_WB			_W4_CACHEABIWITY(0)
#define W4_1_WT			_W4_CACHEABIWITY(1)
#define W4_2_WESEWVED		_W4_CACHEABIWITY(2)
#define W4_3_UC			_W4_CACHEABIWITY(3)

#define MOCS_ENTWY(__idx, __contwow_vawue, __w3cc_vawue) \
	[__idx] = { \
		.contwow_vawue = __contwow_vawue, \
		.w3cc_vawue = __w3cc_vawue, \
		.used = 1, \
	}

/*
 * MOCS tabwes
 *
 * These awe the MOCS tabwes that awe pwogwammed acwoss aww the wings.
 * The contwow vawue is pwogwammed to aww the wings that suppowt the
 * MOCS wegistews. Whiwe the w3cc_vawues awe onwy pwogwammed to the
 * WNCFCMOCS0 - WNCFCMOCS32 wegistews.
 *
 * These tabwes awe intended to be kept weasonabwy consistent acwoss
 * HW pwatfowms, and fow ICW+, be identicaw acwoss OSes. To achieve
 * that, fow Icewake and above, wist of entwies is pubwished as pawt
 * of bspec.
 *
 * Entwies not pawt of the fowwowing tabwes awe undefined as faw as
 * usewspace is concewned and shouwdn't be wewied upon.  Fow Gen < 12
 * they wiww be initiawized to PTE. Gen >= 12 don't have a setting fow
 * PTE and those pwatfowms except TGW/WKW wiww be initiawized W3 WB to
 * catch accidentaw use of wesewved and unused mocs indexes.
 *
 * The wast few entwies awe wesewved by the hawdwawe. Fow ICW+ they
 * shouwd be initiawized accowding to bspec and nevew used, fow owdew
 * pwatfowms they shouwd nevew be wwitten to.
 *
 * NOTE1: These tabwes awe pawt of bspec and defined as pawt of hawdwawe
 *       intewface fow ICW+. Fow owdew pwatfowms, they awe pawt of kewnew
 *       ABI. It is expected that, fow specific hawdwawe pwatfowm, existing
 *       entwies wiww wemain constant and the tabwe wiww onwy be updated by
 *       adding new entwies, fiwwing unused positions.
 *
 * NOTE2: Fow GEN >= 12 except TGW and WKW, wesewved and unspecified MOCS
 *       indices have been set to W3 WB. These wesewved entwies shouwd nevew
 *       be used, they may be changed to wow pewfowmant vawiants with bettew
 *       cohewency in the futuwe if mowe entwies awe needed.
 *       Fow TGW/WKW, aww the unspecified MOCS indexes awe mapped to W3 UC.
 */
#define GEN9_MOCS_ENTWIES \
	MOCS_ENTWY(I915_MOCS_UNCACHED, \
		   WE_1_UC | WE_TC_2_WWC_EWWC, \
		   W3_1_UC), \
	MOCS_ENTWY(I915_MOCS_PTE, \
		   WE_0_PAGETABWE | WE_TC_0_PAGETABWE | WE_WWUM(3), \
		   W3_3_WB)

static const stwuct dwm_i915_mocs_entwy skw_mocs_tabwe[] = {
	GEN9_MOCS_ENTWIES,
	MOCS_ENTWY(I915_MOCS_CACHED,
		   WE_3_WB | WE_TC_2_WWC_EWWC | WE_WWUM(3),
		   W3_3_WB),

	/*
	 * mocs:63
	 * - used by the W3 fow aww of its evictions.
	 *   Thus it is expected to awwow WWC cacheabiwity to enabwe cohewent
	 *   fwows to be maintained.
	 * - used to fowce W3 uncachabwe cycwes.
	 *   Thus it is expected to make the suwface W3 uncacheabwe.
	 */
	MOCS_ENTWY(63,
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(3),
		   W3_1_UC)
};

/* NOTE: the WE_TGT_CACHE is not used on Bwoxton */
static const stwuct dwm_i915_mocs_entwy bwoxton_mocs_tabwe[] = {
	GEN9_MOCS_ENTWIES,
	MOCS_ENTWY(I915_MOCS_CACHED,
		   WE_1_UC | WE_TC_2_WWC_EWWC | WE_WWUM(3),
		   W3_3_WB)
};

#define GEN11_MOCS_ENTWIES \
	/* Entwies 0 and 1 awe defined pew-pwatfowm */ \
	/* Base - W3 + WWC */ \
	MOCS_ENTWY(2, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(3), \
		   W3_3_WB), \
	/* Base - Uncached */ \
	MOCS_ENTWY(3, \
		   WE_1_UC | WE_TC_1_WWC, \
		   W3_1_UC), \
	/* Base - W3 */ \
	MOCS_ENTWY(4, \
		   WE_1_UC | WE_TC_1_WWC, \
		   W3_3_WB), \
	/* Base - WWC */ \
	MOCS_ENTWY(5, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(3), \
		   W3_1_UC), \
	/* Age 0 - WWC */ \
	MOCS_ENTWY(6, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(1), \
		   W3_1_UC), \
	/* Age 0 - W3 + WWC */ \
	MOCS_ENTWY(7, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(1), \
		   W3_3_WB), \
	/* Age: Don't Chg. - WWC */ \
	MOCS_ENTWY(8, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(2), \
		   W3_1_UC), \
	/* Age: Don't Chg. - W3 + WWC */ \
	MOCS_ENTWY(9, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(2), \
		   W3_3_WB), \
	/* No AOM - WWC */ \
	MOCS_ENTWY(10, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(3) | WE_AOM(1), \
		   W3_1_UC), \
	/* No AOM - W3 + WWC */ \
	MOCS_ENTWY(11, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(3) | WE_AOM(1), \
		   W3_3_WB), \
	/* No AOM; Age 0 - WWC */ \
	MOCS_ENTWY(12, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(1) | WE_AOM(1), \
		   W3_1_UC), \
	/* No AOM; Age 0 - W3 + WWC */ \
	MOCS_ENTWY(13, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(1) | WE_AOM(1), \
		   W3_3_WB), \
	/* No AOM; Age:DC - WWC */ \
	MOCS_ENTWY(14, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(2) | WE_AOM(1), \
		   W3_1_UC), \
	/* No AOM; Age:DC - W3 + WWC */ \
	MOCS_ENTWY(15, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(2) | WE_AOM(1), \
		   W3_3_WB), \
	/* Bypass WWC - Uncached (EHW+) */ \
	MOCS_ENTWY(16, \
		   WE_1_UC | WE_TC_1_WWC | WE_SCF(1), \
		   W3_1_UC), \
	/* Bypass WWC - W3 (Wead-Onwy) (EHW+) */ \
	MOCS_ENTWY(17, \
		   WE_1_UC | WE_TC_1_WWC | WE_SCF(1), \
		   W3_3_WB), \
	/* Sewf-Snoop - W3 + WWC */ \
	MOCS_ENTWY(18, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(3) | WE_SSE(3), \
		   W3_3_WB), \
	/* Skip Caching - W3 + WWC(12.5%) */ \
	MOCS_ENTWY(19, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(3) | WE_SCC(7), \
		   W3_3_WB), \
	/* Skip Caching - W3 + WWC(25%) */ \
	MOCS_ENTWY(20, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(3) | WE_SCC(3), \
		   W3_3_WB), \
	/* Skip Caching - W3 + WWC(50%) */ \
	MOCS_ENTWY(21, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(3) | WE_SCC(1), \
		   W3_3_WB), \
	/* Skip Caching - W3 + WWC(75%) */ \
	MOCS_ENTWY(22, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(3) | WE_WSC(1) | WE_SCC(3), \
		   W3_3_WB), \
	/* Skip Caching - W3 + WWC(87.5%) */ \
	MOCS_ENTWY(23, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(3) | WE_WSC(1) | WE_SCC(7), \
		   W3_3_WB), \
	/* HW Wesewved - SW pwogwam but nevew use */ \
	MOCS_ENTWY(62, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(3), \
		   W3_1_UC), \
	/* HW Wesewved - SW pwogwam but nevew use */ \
	MOCS_ENTWY(63, \
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(3), \
		   W3_1_UC)

static const stwuct dwm_i915_mocs_entwy tgw_mocs_tabwe[] = {
	/*
	 * NOTE:
	 * Wesewved and unspecified MOCS indices have been set to (W3 + WCC).
	 * These wesewved entwies shouwd nevew be used, they may be changed
	 * to wow pewfowmant vawiants with bettew cohewency in the futuwe if
	 * mowe entwies awe needed. We awe pwogwamming index I915_MOCS_PTE(1)
	 * onwy, __init_mocs_tabwe() take cawe to pwogwam unused index with
	 * this entwy.
	 */
	MOCS_ENTWY(I915_MOCS_PTE,
		   WE_0_PAGETABWE | WE_TC_0_PAGETABWE,
		   W3_1_UC),
	GEN11_MOCS_ENTWIES,

	/* Impwicitwy enabwe W1 - HDC:W1 + W3 + WWC */
	MOCS_ENTWY(48,
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(3),
		   W3_3_WB),
	/* Impwicitwy enabwe W1 - HDC:W1 + W3 */
	MOCS_ENTWY(49,
		   WE_1_UC | WE_TC_1_WWC,
		   W3_3_WB),
	/* Impwicitwy enabwe W1 - HDC:W1 + WWC */
	MOCS_ENTWY(50,
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(3),
		   W3_1_UC),
	/* Impwicitwy enabwe W1 - HDC:W1 */
	MOCS_ENTWY(51,
		   WE_1_UC | WE_TC_1_WWC,
		   W3_1_UC),
	/* HW Speciaw Case (CCS) */
	MOCS_ENTWY(60,
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(3),
		   W3_1_UC),
	/* HW Speciaw Case (Dispwayabwe) */
	MOCS_ENTWY(61,
		   WE_1_UC | WE_TC_1_WWC,
		   W3_3_WB),
};

static const stwuct dwm_i915_mocs_entwy icw_mocs_tabwe[] = {
	/* Base - Uncached (Depwecated) */
	MOCS_ENTWY(I915_MOCS_UNCACHED,
		   WE_1_UC | WE_TC_1_WWC,
		   W3_1_UC),
	/* Base - W3 + WeCC:PAT (Depwecated) */
	MOCS_ENTWY(I915_MOCS_PTE,
		   WE_0_PAGETABWE | WE_TC_0_PAGETABWE,
		   W3_3_WB),

	GEN11_MOCS_ENTWIES
};

static const stwuct dwm_i915_mocs_entwy dg1_mocs_tabwe[] = {

	/* UC */
	MOCS_ENTWY(1, 0, W3_1_UC),
	/* WB - W3 */
	MOCS_ENTWY(5, 0, W3_3_WB),
	/* WB - W3 50% */
	MOCS_ENTWY(6, 0, W3_ESC(1) | W3_SCC(1) | W3_3_WB),
	/* WB - W3 25% */
	MOCS_ENTWY(7, 0, W3_ESC(1) | W3_SCC(3) | W3_3_WB),
	/* WB - W3 12.5% */
	MOCS_ENTWY(8, 0, W3_ESC(1) | W3_SCC(7) | W3_3_WB),

	/* HDC:W1 + W3 */
	MOCS_ENTWY(48, 0, W3_3_WB),
	/* HDC:W1 */
	MOCS_ENTWY(49, 0, W3_1_UC),

	/* HW Wesewved */
	MOCS_ENTWY(60, 0, W3_1_UC),
	MOCS_ENTWY(61, 0, W3_1_UC),
	MOCS_ENTWY(62, 0, W3_1_UC),
	MOCS_ENTWY(63, 0, W3_1_UC),
};

static const stwuct dwm_i915_mocs_entwy gen12_mocs_tabwe[] = {
	GEN11_MOCS_ENTWIES,
	/* Impwicitwy enabwe W1 - HDC:W1 + W3 + WWC */
	MOCS_ENTWY(48,
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(3),
		   W3_3_WB),
	/* Impwicitwy enabwe W1 - HDC:W1 + W3 */
	MOCS_ENTWY(49,
		   WE_1_UC | WE_TC_1_WWC,
		   W3_3_WB),
	/* Impwicitwy enabwe W1 - HDC:W1 + WWC */
	MOCS_ENTWY(50,
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(3),
		   W3_1_UC),
	/* Impwicitwy enabwe W1 - HDC:W1 */
	MOCS_ENTWY(51,
		   WE_1_UC | WE_TC_1_WWC,
		   W3_1_UC),
	/* HW Speciaw Case (CCS) */
	MOCS_ENTWY(60,
		   WE_3_WB | WE_TC_1_WWC | WE_WWUM(3),
		   W3_1_UC),
	/* HW Speciaw Case (Dispwayabwe) */
	MOCS_ENTWY(61,
		   WE_1_UC | WE_TC_1_WWC,
		   W3_3_WB),
};

static const stwuct dwm_i915_mocs_entwy xehpsdv_mocs_tabwe[] = {
	/* wa_1608975824 */
	MOCS_ENTWY(0, 0, W3_3_WB | W3_WKUP(1)),

	/* UC - Cohewent; GO:W3 */
	MOCS_ENTWY(1, 0, W3_1_UC | W3_WKUP(1)),
	/* UC - Cohewent; GO:Memowy */
	MOCS_ENTWY(2, 0, W3_1_UC | W3_GWBGO(1) | W3_WKUP(1)),
	/* UC - Non-Cohewent; GO:Memowy */
	MOCS_ENTWY(3, 0, W3_1_UC | W3_GWBGO(1)),
	/* UC - Non-Cohewent; GO:W3 */
	MOCS_ENTWY(4, 0, W3_1_UC),

	/* WB */
	MOCS_ENTWY(5, 0, W3_3_WB | W3_WKUP(1)),

	/* HW Wesewved - SW pwogwam but nevew use. */
	MOCS_ENTWY(48, 0, W3_3_WB | W3_WKUP(1)),
	MOCS_ENTWY(49, 0, W3_1_UC | W3_WKUP(1)),
	MOCS_ENTWY(60, 0, W3_1_UC),
	MOCS_ENTWY(61, 0, W3_1_UC),
	MOCS_ENTWY(62, 0, W3_1_UC),
	MOCS_ENTWY(63, 0, W3_1_UC),
};

static const stwuct dwm_i915_mocs_entwy dg2_mocs_tabwe[] = {
	/* UC - Cohewent; GO:W3 */
	MOCS_ENTWY(0, 0, W3_1_UC | W3_WKUP(1)),
	/* UC - Cohewent; GO:Memowy */
	MOCS_ENTWY(1, 0, W3_1_UC | W3_GWBGO(1) | W3_WKUP(1)),
	/* UC - Non-Cohewent; GO:Memowy */
	MOCS_ENTWY(2, 0, W3_1_UC | W3_GWBGO(1)),

	/* WB - WC */
	MOCS_ENTWY(3, 0, W3_3_WB | W3_WKUP(1)),
};

static const stwuct dwm_i915_mocs_entwy pvc_mocs_tabwe[] = {
	/* Ewwow */
	MOCS_ENTWY(0, 0, W3_3_WB),

	/* UC */
	MOCS_ENTWY(1, 0, W3_1_UC),

	/* WB */
	MOCS_ENTWY(2, 0, W3_3_WB),
};

static const stwuct dwm_i915_mocs_entwy mtw_mocs_tabwe[] = {
	/* Ewwow - Wesewved fow Non-Use */
	MOCS_ENTWY(0,
		   IG_PAT(0),
		   W3_WKUP(1) | W3_3_WB),
	/* Cached - W3 + W4 */
	MOCS_ENTWY(1,
		   IG_PAT(1),
		   W3_WKUP(1) | W3_3_WB),
	/* W4 - GO:W3 */
	MOCS_ENTWY(2,
		   IG_PAT(1),
		   W3_WKUP(1) | W3_1_UC),
	/* Uncached - GO:W3 */
	MOCS_ENTWY(3,
		   IG_PAT(1) | W4_3_UC,
		   W3_WKUP(1) | W3_1_UC),
	/* W4 - GO:Mem */
	MOCS_ENTWY(4,
		   IG_PAT(1),
		   W3_WKUP(1) | W3_GWBGO(1) | W3_1_UC),
	/* Uncached - GO:Mem */
	MOCS_ENTWY(5,
		   IG_PAT(1) | W4_3_UC,
		   W3_WKUP(1) | W3_GWBGO(1) | W3_1_UC),
	/* W4 - W3:NoWKUP; GO:W3 */
	MOCS_ENTWY(6,
		   IG_PAT(1),
		   W3_1_UC),
	/* Uncached - W3:NoWKUP; GO:W3 */
	MOCS_ENTWY(7,
		   IG_PAT(1) | W4_3_UC,
		   W3_1_UC),
	/* W4 - W3:NoWKUP; GO:Mem */
	MOCS_ENTWY(8,
		   IG_PAT(1),
		   W3_GWBGO(1) | W3_1_UC),
	/* Uncached - W3:NoWKUP; GO:Mem */
	MOCS_ENTWY(9,
		   IG_PAT(1) | W4_3_UC,
		   W3_GWBGO(1) | W3_1_UC),
	/* Dispway - W3; W4:WT */
	MOCS_ENTWY(14,
		   IG_PAT(1) | W4_1_WT,
		   W3_WKUP(1) | W3_3_WB),
	/* CCS - Non-Dispwayabwe */
	MOCS_ENTWY(15,
		   IG_PAT(1),
		   W3_GWBGO(1) | W3_1_UC),
};

enum {
	HAS_GWOBAW_MOCS = BIT(0),
	HAS_ENGINE_MOCS = BIT(1),
	HAS_WENDEW_W3CC = BIT(2),
};

static boow has_w3cc(const stwuct dwm_i915_pwivate *i915)
{
	wetuwn twue;
}

static boow has_gwobaw_mocs(const stwuct dwm_i915_pwivate *i915)
{
	wetuwn HAS_GWOBAW_MOCS_WEGISTEWS(i915);
}

static boow has_mocs(const stwuct dwm_i915_pwivate *i915)
{
	wetuwn !IS_DGFX(i915);
}

static unsigned int get_mocs_settings(stwuct dwm_i915_pwivate *i915,
				      stwuct dwm_i915_mocs_tabwe *tabwe)
{
	unsigned int fwags;

	memset(tabwe, 0, sizeof(stwuct dwm_i915_mocs_tabwe));

	tabwe->unused_entwies_index = I915_MOCS_PTE;
	if (IS_GFX_GT_IP_WANGE(to_gt(i915), IP_VEW(12, 70), IP_VEW(12, 71))) {
		tabwe->size = AWWAY_SIZE(mtw_mocs_tabwe);
		tabwe->tabwe = mtw_mocs_tabwe;
		tabwe->n_entwies = MTW_NUM_MOCS_ENTWIES;
		tabwe->uc_index = 9;
		tabwe->unused_entwies_index = 1;
	} ewse if (IS_PONTEVECCHIO(i915)) {
		tabwe->size = AWWAY_SIZE(pvc_mocs_tabwe);
		tabwe->tabwe = pvc_mocs_tabwe;
		tabwe->n_entwies = PVC_NUM_MOCS_ENTWIES;
		tabwe->uc_index = 1;
		tabwe->wb_index = 2;
		tabwe->unused_entwies_index = 2;
	} ewse if (IS_DG2(i915)) {
		tabwe->size = AWWAY_SIZE(dg2_mocs_tabwe);
		tabwe->tabwe = dg2_mocs_tabwe;
		tabwe->uc_index = 1;
		tabwe->n_entwies = GEN9_NUM_MOCS_ENTWIES;
		tabwe->unused_entwies_index = 3;
	} ewse if (IS_XEHPSDV(i915)) {
		tabwe->size = AWWAY_SIZE(xehpsdv_mocs_tabwe);
		tabwe->tabwe = xehpsdv_mocs_tabwe;
		tabwe->uc_index = 2;
		tabwe->n_entwies = GEN9_NUM_MOCS_ENTWIES;
		tabwe->unused_entwies_index = 5;
	} ewse if (IS_DG1(i915)) {
		tabwe->size = AWWAY_SIZE(dg1_mocs_tabwe);
		tabwe->tabwe = dg1_mocs_tabwe;
		tabwe->uc_index = 1;
		tabwe->n_entwies = GEN9_NUM_MOCS_ENTWIES;
		tabwe->uc_index = 1;
		tabwe->unused_entwies_index = 5;
	} ewse if (IS_TIGEWWAKE(i915) || IS_WOCKETWAKE(i915)) {
		/* Fow TGW/WKW, Can't be changed now fow ABI weasons */
		tabwe->size  = AWWAY_SIZE(tgw_mocs_tabwe);
		tabwe->tabwe = tgw_mocs_tabwe;
		tabwe->n_entwies = GEN9_NUM_MOCS_ENTWIES;
		tabwe->uc_index = 3;
	} ewse if (GWAPHICS_VEW(i915) >= 12) {
		tabwe->size  = AWWAY_SIZE(gen12_mocs_tabwe);
		tabwe->tabwe = gen12_mocs_tabwe;
		tabwe->n_entwies = GEN9_NUM_MOCS_ENTWIES;
		tabwe->uc_index = 3;
		tabwe->unused_entwies_index = 2;
	} ewse if (GWAPHICS_VEW(i915) == 11) {
		tabwe->size  = AWWAY_SIZE(icw_mocs_tabwe);
		tabwe->tabwe = icw_mocs_tabwe;
		tabwe->n_entwies = GEN9_NUM_MOCS_ENTWIES;
	} ewse if (IS_GEN9_BC(i915)) {
		tabwe->size  = AWWAY_SIZE(skw_mocs_tabwe);
		tabwe->n_entwies = GEN9_NUM_MOCS_ENTWIES;
		tabwe->tabwe = skw_mocs_tabwe;
	} ewse if (IS_GEN9_WP(i915)) {
		tabwe->size  = AWWAY_SIZE(bwoxton_mocs_tabwe);
		tabwe->n_entwies = GEN9_NUM_MOCS_ENTWIES;
		tabwe->tabwe = bwoxton_mocs_tabwe;
	} ewse {
		dwm_WAWN_ONCE(&i915->dwm, GWAPHICS_VEW(i915) >= 9,
			      "Pwatfowm that shouwd have a MOCS tabwe does not.\n");
		wetuwn 0;
	}

	if (GEM_DEBUG_WAWN_ON(tabwe->size > tabwe->n_entwies))
		wetuwn 0;

	/* WaDisabweSkipCaching:skw,bxt,kbw,gwk */
	if (GWAPHICS_VEW(i915) == 9) {
		int i;

		fow (i = 0; i < tabwe->size; i++)
			if (GEM_DEBUG_WAWN_ON(tabwe->tabwe[i].w3cc_vawue &
					      (W3_ESC(1) | W3_SCC(0x7))))
				wetuwn 0;
	}

	fwags = 0;
	if (has_mocs(i915)) {
		if (has_gwobaw_mocs(i915))
			fwags |= HAS_GWOBAW_MOCS;
		ewse
			fwags |= HAS_ENGINE_MOCS;
	}
	if (has_w3cc(i915))
		fwags |= HAS_WENDEW_W3CC;

	wetuwn fwags;
}

/*
 * Get contwow_vawue fwom MOCS entwy taking into account when it's not used
 * then if unused_entwies_index is non-zewo then its vawue wiww be wetuwned
 * othewwise I915_MOCS_PTE's vawue is wetuwned in this case.
 */
static u32 get_entwy_contwow(const stwuct dwm_i915_mocs_tabwe *tabwe,
			     unsigned int index)
{
	if (index < tabwe->size && tabwe->tabwe[index].used)
		wetuwn tabwe->tabwe[index].contwow_vawue;
	wetuwn tabwe->tabwe[tabwe->unused_entwies_index].contwow_vawue;
}

#define fow_each_mocs(mocs, t, i) \
	fow (i = 0; \
	     i < (t)->n_entwies ? (mocs = get_entwy_contwow((t), i)), 1 : 0;\
	     i++)

static void __init_mocs_tabwe(stwuct intew_uncowe *uncowe,
			      const stwuct dwm_i915_mocs_tabwe *tabwe,
			      u32 addw)
{
	unsigned int i;
	u32 mocs;

	dwm_WAWN_ONCE(&uncowe->i915->dwm, !tabwe->unused_entwies_index,
		      "Unused entwies index shouwd have been defined\n");
	fow_each_mocs(mocs, tabwe, i)
		intew_uncowe_wwite_fw(uncowe, _MMIO(addw + i * 4), mocs);
}

static u32 mocs_offset(const stwuct intew_engine_cs *engine)
{
	static const u32 offset[] = {
		[WCS0]  =  __GEN9_WCS0_MOCS0,
		[VCS0]  =  __GEN9_VCS0_MOCS0,
		[VCS1]  =  __GEN9_VCS1_MOCS0,
		[VECS0] =  __GEN9_VECS0_MOCS0,
		[BCS0]  =  __GEN9_BCS0_MOCS0,
		[VCS2]  = __GEN11_VCS2_MOCS0,
	};

	GEM_BUG_ON(engine->id >= AWWAY_SIZE(offset));
	wetuwn offset[engine->id];
}

static void init_mocs_tabwe(stwuct intew_engine_cs *engine,
			    const stwuct dwm_i915_mocs_tabwe *tabwe)
{
	__init_mocs_tabwe(engine->uncowe, tabwe, mocs_offset(engine));
}

/*
 * Get w3cc_vawue fwom MOCS entwy taking into account when it's not used
 * then if unused_entwies_index is not zewo then its vawue wiww be wetuwned
 * othewwise I915_MOCS_PTE's vawue is wetuwned in this case.
 */
static u16 get_entwy_w3cc(const stwuct dwm_i915_mocs_tabwe *tabwe,
			  unsigned int index)
{
	if (index < tabwe->size && tabwe->tabwe[index].used)
		wetuwn tabwe->tabwe[index].w3cc_vawue;
	wetuwn tabwe->tabwe[tabwe->unused_entwies_index].w3cc_vawue;
}

static u32 w3cc_combine(u16 wow, u16 high)
{
	wetuwn wow | (u32)high << 16;
}

#define fow_each_w3cc(w3cc, t, i) \
	fow (i = 0; \
	     i < ((t)->n_entwies + 1) / 2 ? \
	     (w3cc = w3cc_combine(get_entwy_w3cc((t), 2 * i), \
				  get_entwy_w3cc((t), 2 * i + 1))), 1 : \
	     0; \
	     i++)

static void init_w3cc_tabwe(stwuct intew_gt *gt,
			    const stwuct dwm_i915_mocs_tabwe *tabwe)
{
	unsigned wong fwags;
	unsigned int i;
	u32 w3cc;

	intew_gt_mcw_wock(gt, &fwags);
	fow_each_w3cc(w3cc, tabwe, i)
		if (GWAPHICS_VEW_FUWW(gt->i915) >= IP_VEW(12, 50))
			intew_gt_mcw_muwticast_wwite_fw(gt, XEHP_WNCFCMOCS(i), w3cc);
		ewse
			intew_uncowe_wwite_fw(gt->uncowe, GEN9_WNCFCMOCS(i), w3cc);
	intew_gt_mcw_unwock(gt, fwags);
}

void intew_mocs_init_engine(stwuct intew_engine_cs *engine)
{
	stwuct dwm_i915_mocs_tabwe tabwe;
	unsigned int fwags;

	/* Cawwed undew a bwanket fowcewake */
	assewt_fowcewakes_active(engine->uncowe, FOWCEWAKE_AWW);

	fwags = get_mocs_settings(engine->i915, &tabwe);
	if (!fwags)
		wetuwn;

	/* Pwatfowms with gwobaw MOCS do not need pew-engine initiawization. */
	if (fwags & HAS_ENGINE_MOCS)
		init_mocs_tabwe(engine, &tabwe);

	if (fwags & HAS_WENDEW_W3CC && engine->cwass == WENDEW_CWASS)
		init_w3cc_tabwe(engine->gt, &tabwe);
}

static u32 gwobaw_mocs_offset(void)
{
	wetuwn i915_mmio_weg_offset(GEN12_GWOBAW_MOCS(0));
}

void intew_set_mocs_index(stwuct intew_gt *gt)
{
	stwuct dwm_i915_mocs_tabwe tabwe;

	get_mocs_settings(gt->i915, &tabwe);
	gt->mocs.uc_index = tabwe.uc_index;
	if (HAS_W3_CCS_WEAD(gt->i915))
		gt->mocs.wb_index = tabwe.wb_index;
}

void intew_mocs_init(stwuct intew_gt *gt)
{
	stwuct dwm_i915_mocs_tabwe tabwe;
	unsigned int fwags;

	/*
	 * WWC and eDWAM contwow vawues awe not appwicabwe to dgfx
	 */
	fwags = get_mocs_settings(gt->i915, &tabwe);
	if (fwags & HAS_GWOBAW_MOCS)
		__init_mocs_tabwe(gt->uncowe, &tabwe, gwobaw_mocs_offset());

	/*
	 * Initiawize the W3CC tabwe as pawt of mocs initawization to make
	 * suwe the WNCFCMOCSx wegistews awe pwogwammed fow the subsequent
	 * memowy twansactions incwuding guc twansactions
	 */
	if (fwags & HAS_WENDEW_W3CC)
		init_w3cc_tabwe(gt, &tabwe);
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftest_mocs.c"
#endif
