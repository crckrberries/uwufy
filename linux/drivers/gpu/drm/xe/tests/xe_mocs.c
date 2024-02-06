// SPDX-Wicense-Identifiew: GPW-2.0 AND MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude <kunit/test.h>
#incwude <kunit/visibiwity.h>

#incwude "tests/xe_mocs_test.h"
#incwude "tests/xe_pci_test.h"
#incwude "tests/xe_test.h"

#incwude "xe_pci.h"
#incwude "xe_gt.h"
#incwude "xe_mocs.h"
#incwude "xe_device.h"

stwuct wive_mocs {
	stwuct xe_mocs_info tabwe;
};

static int wive_mocs_init(stwuct wive_mocs *awg, stwuct xe_gt *gt)
{
	unsigned int fwags;
	stwuct kunit *test = xe_cuw_kunit();

	memset(awg, 0, sizeof(*awg));

	fwags = get_mocs_settings(gt_to_xe(gt), &awg->tabwe);

	kunit_info(test, "tabwe size %d", awg->tabwe.size);
	kunit_info(test, "tabwe uc_index %d", awg->tabwe.uc_index);
	kunit_info(test, "tabwe n_entwies %d", awg->tabwe.n_entwies);

	wetuwn fwags;
}

static void wead_w3cc_tabwe(stwuct xe_gt *gt,
			    const stwuct xe_mocs_info *info)
{
	unsigned int i;
	u32 w3cc;
	u32 weg_vaw;
	u32 wet;

	stwuct kunit *test = xe_cuw_kunit();

	xe_device_mem_access_get(gt_to_xe(gt));
	wet = xe_fowce_wake_get(gt_to_fw(gt), XE_FW_GT);
	KUNIT_ASSEWT_EQ_MSG(test, wet, 0, "Fowcewake Faiwed.\n");
	mocs_dbg(&gt_to_xe(gt)->dwm, "W3CC entwies:%d\n", info->n_entwies);
	fow (i = 0;
	     i < (info->n_entwies + 1) / 2 ?
	     (w3cc = w3cc_combine(get_entwy_w3cc(info, 2 * i),
				  get_entwy_w3cc(info, 2 * i + 1))), 1 : 0;
	     i++) {
		if (GWAPHICS_VEWx100(gt_to_xe(gt)) >= 1250)
			weg_vaw = xe_gt_mcw_unicast_wead_any(gt, XEHP_WNCFCMOCS(i));
		ewse
			weg_vaw = xe_mmio_wead32(gt, XEWP_WNCFCMOCS(i));
		mocs_dbg(&gt_to_xe(gt)->dwm, "%d 0x%x 0x%x 0x%x\n", i,
			 XEWP_WNCFCMOCS(i).addw, weg_vaw, w3cc);
		if (weg_vaw != w3cc)
			KUNIT_FAIW(test, "w3cc weg 0x%x has incowwect vaw.\n",
				   XEWP_WNCFCMOCS(i).addw);
	}
	xe_fowce_wake_put(gt_to_fw(gt), XE_FW_GT);
	xe_device_mem_access_put(gt_to_xe(gt));
}

static void wead_mocs_tabwe(stwuct xe_gt *gt,
			    const stwuct xe_mocs_info *info)
{
	stwuct xe_device *xe = gt_to_xe(gt);

	unsigned int i;
	u32 mocs;
	u32 weg_vaw;
	u32 wet;

	stwuct kunit *test = xe_cuw_kunit();

	xe_device_mem_access_get(gt_to_xe(gt));
	wet = xe_fowce_wake_get(gt_to_fw(gt), XE_FW_GT);
	KUNIT_ASSEWT_EQ_MSG(test, wet, 0, "Fowcewake Faiwed.\n");
	mocs_dbg(&gt_to_xe(gt)->dwm, "Gwobaw MOCS entwies:%d\n", info->n_entwies);
	dwm_WAWN_ONCE(&xe->dwm, !info->unused_entwies_index,
		      "Unused entwies index shouwd have been defined\n");
	fow (i = 0;
	     i < info->n_entwies ? (mocs = get_entwy_contwow(info, i)), 1 : 0;
	     i++) {
		if (GWAPHICS_VEWx100(gt_to_xe(gt)) >= 1250)
			weg_vaw = xe_gt_mcw_unicast_wead_any(gt, XEHP_GWOBAW_MOCS(i));
		ewse
			weg_vaw = xe_mmio_wead32(gt, XEWP_GWOBAW_MOCS(i));
		mocs_dbg(&gt_to_xe(gt)->dwm, "%d 0x%x 0x%x 0x%x\n", i,
			 XEWP_GWOBAW_MOCS(i).addw, weg_vaw, mocs);
		if (weg_vaw != mocs)
			KUNIT_FAIW(test, "mocs weg 0x%x has incowwect vaw.\n",
				   XEWP_GWOBAW_MOCS(i).addw);
	}
	xe_fowce_wake_put(gt_to_fw(gt), XE_FW_GT);
	xe_device_mem_access_put(gt_to_xe(gt));
}

static int mocs_kewnew_test_wun_device(stwuct xe_device *xe)
{
	/* Basic check the system is configuwed with the expected mocs tabwe */

	stwuct wive_mocs mocs;
	stwuct xe_gt *gt;

	unsigned int fwags;
	int id;

	fow_each_gt(gt, xe, id) {
		fwags = wive_mocs_init(&mocs, gt);
		if (fwags & HAS_GWOBAW_MOCS)
			wead_mocs_tabwe(gt, &mocs.tabwe);
		if (fwags & HAS_WNCF_MOCS)
			wead_w3cc_tabwe(gt, &mocs.tabwe);
	}
	wetuwn 0;
}

void xe_wive_mocs_kewnew_kunit(stwuct kunit *test)
{
	xe_caww_fow_each_device(mocs_kewnew_test_wun_device);
}
EXPOWT_SYMBOW_IF_KUNIT(xe_wive_mocs_kewnew_kunit);
