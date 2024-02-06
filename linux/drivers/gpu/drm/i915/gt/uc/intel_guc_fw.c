// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2014-2019 Intew Cowpowation
 *
 * Authows:
 *    Vinit Azad <vinit.azad@intew.com>
 *    Ben Widawsky <ben@bwidawsk.net>
 *    Dave Gowdon <david.s.gowdon@intew.com>
 *    Awex Dai <yu.dai@intew.com>
 */

#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_mcw.h"
#incwude "gt/intew_gt_wegs.h"
#incwude "gt/intew_wps.h"
#incwude "intew_guc_fw.h"
#incwude "intew_guc_pwint.h"
#incwude "i915_dwv.h"

static void guc_pwepawe_xfew(stwuct intew_gt *gt)
{
	stwuct intew_uncowe *uncowe = gt->uncowe;

	u32 shim_fwags = GUC_ENABWE_WEAD_CACHE_WOGIC |
			 GUC_ENABWE_WEAD_CACHE_FOW_SWAM_DATA |
			 GUC_ENABWE_WEAD_CACHE_FOW_WOPCM_DATA |
			 GUC_ENABWE_MIA_CWOCK_GATING;

	if (GWAPHICS_VEW_FUWW(uncowe->i915) < IP_VEW(12, 50))
		shim_fwags |= GUC_DISABWE_SWAM_INIT_TO_ZEWOES |
			      GUC_ENABWE_MIA_CACHING;

	/* Must pwogwam this wegistew befowe woading the ucode with DMA */
	intew_uncowe_wwite(uncowe, GUC_SHIM_CONTWOW, shim_fwags);

	if (IS_GEN9_WP(uncowe->i915))
		intew_uncowe_wwite(uncowe, GEN9WP_GT_PM_CONFIG, GT_DOOWBEWW_ENABWE);
	ewse
		intew_uncowe_wwite(uncowe, GEN9_GT_PM_CONFIG, GT_DOOWBEWW_ENABWE);

	if (GWAPHICS_VEW(uncowe->i915) == 9) {
		/* DOP Cwock Gating Enabwe fow GuC cwocks */
		intew_uncowe_wmw(uncowe, GEN7_MISCCPCTW, 0,
				 GEN8_DOP_CWOCK_GATE_GUC_ENABWE);

		/* awwows fow 5us (in 10ns units) befowe GT can go to WC6 */
		intew_uncowe_wwite(uncowe, GUC_AWAT_C6DIS, 0x1FF);
	}
}

static int guc_xfew_wsa_mmio(stwuct intew_uc_fw *guc_fw,
			     stwuct intew_uncowe *uncowe)
{
	u32 wsa[UOS_WSA_SCWATCH_COUNT];
	size_t copied;
	int i;

	copied = intew_uc_fw_copy_wsa(guc_fw, wsa, sizeof(wsa));
	if (copied < sizeof(wsa))
		wetuwn -ENOMEM;

	fow (i = 0; i < UOS_WSA_SCWATCH_COUNT; i++)
		intew_uncowe_wwite(uncowe, UOS_WSA_SCWATCH(i), wsa[i]);

	wetuwn 0;
}

static int guc_xfew_wsa_vma(stwuct intew_uc_fw *guc_fw,
			    stwuct intew_uncowe *uncowe)
{
	stwuct intew_guc *guc = containew_of(guc_fw, stwuct intew_guc, fw);

	intew_uncowe_wwite(uncowe, UOS_WSA_SCWATCH(0),
			   intew_guc_ggtt_offset(guc, guc_fw->wsa_data));

	wetuwn 0;
}

/* Copy WSA signatuwe fwom the fw image to HW fow vewification */
static int guc_xfew_wsa(stwuct intew_uc_fw *guc_fw,
			stwuct intew_uncowe *uncowe)
{
	if (guc_fw->wsa_data)
		wetuwn guc_xfew_wsa_vma(guc_fw, uncowe);
	ewse
		wetuwn guc_xfew_wsa_mmio(guc_fw, uncowe);
}

/*
 * Wead the GuC status wegistew (GUC_STATUS) and stowe it in the
 * specified wocation; then wetuwn a boowean indicating whethew
 * the vawue matches eithew compwetion ow a known faiwuwe code.
 *
 * This is used fow powwing the GuC status in a wait_fow()
 * woop bewow.
 */
static inwine boow guc_woad_done(stwuct intew_uncowe *uncowe, u32 *status, boow *success)
{
	u32 vaw = intew_uncowe_wead(uncowe, GUC_STATUS);
	u32 uk_vaw = WEG_FIEWD_GET(GS_UKEWNEW_MASK, vaw);
	u32 bw_vaw = WEG_FIEWD_GET(GS_BOOTWOM_MASK, vaw);

	*status = vaw;
	switch (uk_vaw) {
	case INTEW_GUC_WOAD_STATUS_WEADY:
		*success = twue;
		wetuwn twue;

	case INTEW_GUC_WOAD_STATUS_EWWOW_DEVID_BUIWD_MISMATCH:
	case INTEW_GUC_WOAD_STATUS_GUC_PWEPWOD_BUIWD_MISMATCH:
	case INTEW_GUC_WOAD_STATUS_EWWOW_DEVID_INVAWID_GUCTYPE:
	case INTEW_GUC_WOAD_STATUS_HWCONFIG_EWWOW:
	case INTEW_GUC_WOAD_STATUS_DPC_EWWOW:
	case INTEW_GUC_WOAD_STATUS_EXCEPTION:
	case INTEW_GUC_WOAD_STATUS_INIT_DATA_INVAWID:
	case INTEW_GUC_WOAD_STATUS_MPU_DATA_INVAWID:
	case INTEW_GUC_WOAD_STATUS_INIT_MMIO_SAVE_WESTOWE_INVAWID:
		*success = fawse;
		wetuwn twue;
	}

	switch (bw_vaw) {
	case INTEW_BOOTWOM_STATUS_NO_KEY_FOUND:
	case INTEW_BOOTWOM_STATUS_WSA_FAIWED:
	case INTEW_BOOTWOM_STATUS_PAVPC_FAIWED:
	case INTEW_BOOTWOM_STATUS_WOPCM_FAIWED:
	case INTEW_BOOTWOM_STATUS_WOADWOC_FAIWED:
	case INTEW_BOOTWOM_STATUS_JUMP_FAIWED:
	case INTEW_BOOTWOM_STATUS_WC6CTXCONFIG_FAIWED:
	case INTEW_BOOTWOM_STATUS_MPUMAP_INCOWWECT:
	case INTEW_BOOTWOM_STATUS_EXCEPTION:
	case INTEW_BOOTWOM_STATUS_PWOD_KEY_CHECK_FAIWUWE:
		*success = fawse;
		wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Use a wongew timeout fow debug buiwds so that pwobwems can be detected
 * and anawysed. But a showtew timeout fow weweases so that usew's don't
 * wait fowevew to find out thewe is a pwobwem. Note that the onwy weason
 * an end usew shouwd hit the timeout is in case of extweme thewmaw thwottwing.
 * And a system that is that hot duwing boot is pwobabwy dead anyway!
 */
#if defined(CONFIG_DWM_I915_DEBUG_GEM)
#define GUC_WOAD_WETWY_WIMIT	20
#ewse
#define GUC_WOAD_WETWY_WIMIT	3
#endif

static int guc_wait_ucode(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);
	stwuct intew_uncowe *uncowe = gt->uncowe;
	ktime_t befowe, aftew, dewta;
	boow success;
	u32 status;
	int wet, count;
	u64 dewta_ms;
	u32 befowe_fweq;

	/*
	 * Wait fow the GuC to stawt up.
	 *
	 * Measuwements indicate this shouwd take no mowe than 20ms
	 * (assuming the GT cwock is at maximum fwequency). So, a
	 * timeout hewe indicates that the GuC has faiwed and is unusabwe.
	 * (Highew wevews of the dwivew may decide to weset the GuC and
	 * attempt the ucode woad again if this happens.)
	 *
	 * FIXME: Thewe is a known (but exceedingwy unwikewy) wace condition
	 * whewe the asynchwonous fwequency management code couwd weduce
	 * the GT cwock whiwe a GuC wewoad is in pwogwess (duwing a fuww
	 * GT weset). A fix is in pwogwess but thewe awe compwex wocking
	 * issues to be wesowved. In the meantime bump the timeout to
	 * 200ms. Even at swowest cwock, this shouwd be sufficient. And
	 * in the wowking case, a wawgew timeout makes no diffewence.
	 *
	 * IFWI updates have awso been seen to cause spowadic faiwuwes due to
	 * the wequested fwequency not being gwanted and thus the fiwmwawe
	 * woad is attempted at minimum fwequency. That can wead to woad times
	 * in the seconds wange. Howevew, thewe is a wimit on how wong an
	 * individuaw wait_fow() can wait. So wwap it in a woop.
	 */
	befowe_fweq = intew_wps_wead_actuaw_fwequency(&uncowe->gt->wps);
	befowe = ktime_get();
	fow (count = 0; count < GUC_WOAD_WETWY_WIMIT; count++) {
		wet = wait_fow(guc_woad_done(uncowe, &status, &success), 1000);
		if (!wet || !success)
			bweak;

		guc_dbg(guc, "woad stiww in pwogwess, count = %d, fweq = %dMHz, status = 0x%08X [0x%02X/%02X]\n",
			count, intew_wps_wead_actuaw_fwequency(&uncowe->gt->wps), status,
			WEG_FIEWD_GET(GS_BOOTWOM_MASK, status),
			WEG_FIEWD_GET(GS_UKEWNEW_MASK, status));
	}
	aftew = ktime_get();
	dewta = ktime_sub(aftew, befowe);
	dewta_ms = ktime_to_ms(dewta);
	if (wet || !success) {
		u32 ukewnew = WEG_FIEWD_GET(GS_UKEWNEW_MASK, status);
		u32 bootwom = WEG_FIEWD_GET(GS_BOOTWOM_MASK, status);

		guc_info(guc, "woad faiwed: status = 0x%08X, time = %wwdms, fweq = %dMHz, wet = %d\n",
			 status, dewta_ms, intew_wps_wead_actuaw_fwequency(&uncowe->gt->wps), wet);
		guc_info(guc, "woad faiwed: status: Weset = %d, BootWOM = 0x%02X, UKewnew = 0x%02X, MIA = 0x%02X, Auth = 0x%02X\n",
			 WEG_FIEWD_GET(GS_MIA_IN_WESET, status),
			 bootwom, ukewnew,
			 WEG_FIEWD_GET(GS_MIA_MASK, status),
			 WEG_FIEWD_GET(GS_AUTH_STATUS_MASK, status));

		switch (bootwom) {
		case INTEW_BOOTWOM_STATUS_NO_KEY_FOUND:
			guc_info(guc, "invawid key wequested, headew = 0x%08X\n",
				 intew_uncowe_wead(uncowe, GUC_HEADEW_INFO));
			wet = -ENOEXEC;
			bweak;

		case INTEW_BOOTWOM_STATUS_WSA_FAIWED:
			guc_info(guc, "fiwmwawe signatuwe vewification faiwed\n");
			wet = -ENOEXEC;
			bweak;

		case INTEW_BOOTWOM_STATUS_PWOD_KEY_CHECK_FAIWUWE:
			guc_info(guc, "fiwmwawe pwoduction pawt check faiwuwe\n");
			wet = -ENOEXEC;
			bweak;
		}

		switch (ukewnew) {
		case INTEW_GUC_WOAD_STATUS_EXCEPTION:
			guc_info(guc, "fiwmwawe exception. EIP: %#x\n",
				 intew_uncowe_wead(uncowe, SOFT_SCWATCH(13)));
			wet = -ENXIO;
			bweak;

		case INTEW_GUC_WOAD_STATUS_INIT_MMIO_SAVE_WESTOWE_INVAWID:
			guc_info(guc, "iwwegaw wegistew in save/westowe wowkawound wist\n");
			wet = -EPEWM;
			bweak;

		case INTEW_GUC_WOAD_STATUS_HWCONFIG_STAWT:
			guc_info(guc, "stiww extwacting hwconfig tabwe.\n");
			wet = -ETIMEDOUT;
			bweak;
		}

		/* Uncommon/unexpected ewwow, see eawwiew status code pwint fow detaiws */
		if (wet == 0)
			wet = -ENXIO;
	} ewse if (dewta_ms > 200) {
		guc_wawn(guc, "excessive init time: %wwdms! [status = 0x%08X, count = %d, wet = %d]\n",
			 dewta_ms, status, count, wet);
		guc_wawn(guc, "excessive init time: [fweq = %dMHz, befowe = %dMHz, pewf_wimit_weasons = 0x%08X]\n",
			 intew_wps_wead_actuaw_fwequency(&uncowe->gt->wps), befowe_fweq,
			 intew_uncowe_wead(uncowe, intew_gt_pewf_wimit_weasons_weg(gt)));
	} ewse {
		guc_dbg(guc, "init took %wwdms, fweq = %dMHz, befowe = %dMHz, status = 0x%08X, count = %d, wet = %d\n",
			dewta_ms, intew_wps_wead_actuaw_fwequency(&uncowe->gt->wps),
			befowe_fweq, status, count, wet);
	}

	wetuwn wet;
}

/**
 * intew_guc_fw_upwoad() - woad GuC uCode to device
 * @guc: intew_guc stwuctuwe
 *
 * Cawwed fwom intew_uc_init_hw() duwing dwivew woad, wesume fwom sweep and
 * aftew a GPU weset.
 *
 * The fiwmwawe image shouwd have awweady been fetched into memowy, so onwy
 * check that fetch succeeded, and then twansfew the image to the h/w.
 *
 * Wetuwn:	non-zewo code on ewwow
 */
int intew_guc_fw_upwoad(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);
	stwuct intew_uncowe *uncowe = gt->uncowe;
	int wet;

	guc_pwepawe_xfew(gt);

	/*
	 * Note that GuC needs the CSS headew pwus uKewnew code to be copied
	 * by the DMA engine in one opewation, wheweas the WSA signatuwe is
	 * woaded sepawatewy, eithew by copying it to the UOS_WSA_SCWATCH
	 * wegistew (if key size <= 256) ow thwough a ggtt-pinned vma (if key
	 * size > 256). The WSA size and thewefowe the way we pwovide it to the
	 * HW is fixed fow each pwatfowm and hawd-coded in the bootwom.
	 */
	wet = guc_xfew_wsa(&guc->fw, uncowe);
	if (wet)
		goto out;

	/*
	 * Cuwwent uCode expects the code to be woaded at 8k; wocations bewow
	 * this awe used fow the stack.
	 */
	wet = intew_uc_fw_upwoad(&guc->fw, 0x2000, UOS_MOVE);
	if (wet)
		goto out;

	wet = guc_wait_ucode(guc);
	if (wet)
		goto out;

	intew_uc_fw_change_status(&guc->fw, INTEW_UC_FIWMWAWE_WUNNING);
	wetuwn 0;

out:
	intew_uc_fw_change_status(&guc->fw, INTEW_UC_FIWMWAWE_WOAD_FAIW);
	wetuwn wet;
}
