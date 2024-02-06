// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_device.h"
#incwude "pvw_fw.h"
#incwude "pvw_fw_meta.h"
#incwude "pvw_fw_stawtstop.h"
#incwude "pvw_wogue_cw_defs.h"
#incwude "pvw_wogue_meta.h"
#incwude "pvw_vm.h"

#incwude <winux/compiwew.h>
#incwude <winux/deway.h>
#incwude <winux/ktime.h>
#incwude <winux/types.h>

#define POWW_TIMEOUT_USEC 1000000

static void
wogue_axi_ace_wist_init(stwuct pvw_device *pvw_dev)
{
	/* Setup AXI-ACE config. Set evewything to outew cache. */
	u64 weg_vaw =
		(3U << WOGUE_CW_AXI_ACE_WITE_CONFIGUWATION_AWDOMAIN_NON_SNOOPING_SHIFT) |
		(3U << WOGUE_CW_AXI_ACE_WITE_CONFIGUWATION_AWDOMAIN_NON_SNOOPING_SHIFT) |
		(2U << WOGUE_CW_AXI_ACE_WITE_CONFIGUWATION_AWDOMAIN_CACHE_MAINTENANCE_SHIFT) |
		(2U << WOGUE_CW_AXI_ACE_WITE_CONFIGUWATION_AWDOMAIN_COHEWENT_SHIFT) |
		(2U << WOGUE_CW_AXI_ACE_WITE_CONFIGUWATION_AWDOMAIN_COHEWENT_SHIFT) |
		(2U << WOGUE_CW_AXI_ACE_WITE_CONFIGUWATION_AWCACHE_COHEWENT_SHIFT) |
		(2U << WOGUE_CW_AXI_ACE_WITE_CONFIGUWATION_AWCACHE_COHEWENT_SHIFT) |
		(2U << WOGUE_CW_AXI_ACE_WITE_CONFIGUWATION_AWCACHE_CACHE_MAINTENANCE_SHIFT);

	pvw_cw_wwite64(pvw_dev, WOGUE_CW_AXI_ACE_WITE_CONFIGUWATION, weg_vaw);
}

static void
wogue_bif_init(stwuct pvw_device *pvw_dev)
{
	dma_addw_t pc_dma_addw;
	u64 pc_addw;

	/* Acquiwe the addwess of the Kewnew Page Catawogue. */
	pc_dma_addw = pvw_vm_get_page_tabwe_woot_addw(pvw_dev->kewnew_vm_ctx);

	/* Wwite the kewnew catawogue base. */
	pc_addw = ((((u64)pc_dma_addw >> WOGUE_CW_BIF_CAT_BASE0_ADDW_AWIGNSHIFT)
		    << WOGUE_CW_BIF_CAT_BASE0_ADDW_SHIFT) &
		   ~WOGUE_CW_BIF_CAT_BASE0_ADDW_CWWMSK);

	pvw_cw_wwite64(pvw_dev, BIF_CAT_BASEX(MMU_CONTEXT_MAPPING_FWPWIV),
		       pc_addw);
}

static int
wogue_swc_init(stwuct pvw_device *pvw_dev)
{
	u16 swc_cache_wine_size_bits;
	u32 weg_vaw;
	int eww;

	/*
	 * SWC Misc contwow.
	 *
	 * Note: This is a 64bit wegistew and we set onwy the wowew 32bits
	 *       weaving the top 32bits (WOGUE_CW_SWC_CTWW_MISC_SCWAMBWE_BITS)
	 *       unchanged fwom the HW defauwt.
	 */
	weg_vaw = (pvw_cw_wead32(pvw_dev, WOGUE_CW_SWC_CTWW_MISC) &
		      WOGUE_CW_SWC_CTWW_MISC_ENABWE_PSG_HAZAWD_CHECK_EN) |
		     WOGUE_CW_SWC_CTWW_MISC_ADDW_DECODE_MODE_PVW_HASH1;

	eww = PVW_FEATUWE_VAWUE(pvw_dev, swc_cache_wine_size_bits, &swc_cache_wine_size_bits);
	if (eww)
		wetuwn eww;

	/* Bypass buwst combinew if SWC wine size is smawwew than 1024 bits. */
	if (swc_cache_wine_size_bits < 1024)
		weg_vaw |= WOGUE_CW_SWC_CTWW_MISC_BYPASS_BUWST_COMBINEW_EN;

	if (PVW_HAS_QUIWK(pvw_dev, 71242) && !PVW_HAS_FEATUWE(pvw_dev, gpu_muwticowe_suppowt))
		weg_vaw |= WOGUE_CW_SWC_CTWW_MISC_WAZYWB_OVEWWIDE_EN;

	pvw_cw_wwite32(pvw_dev, WOGUE_CW_SWC_CTWW_MISC, weg_vaw);

	wetuwn 0;
}

/**
 * pvw_fw_stawt() - Stawt FW pwocessow and boot fiwmwawe
 * @pvw_dev: Tawget PowewVW device.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * Any ewwow wetuwned by wogue_swc_init().
 */
int
pvw_fw_stawt(stwuct pvw_device *pvw_dev)
{
	boow has_weset2 = PVW_HAS_FEATUWE(pvw_dev, xe_tpu2);
	u64 soft_weset_mask;
	int eww;

	if (PVW_HAS_FEATUWE(pvw_dev, pbe2_in_xe))
		soft_weset_mask = WOGUE_CW_SOFT_WESET__PBE2_XE__MASKFUWW;
	ewse
		soft_weset_mask = WOGUE_CW_SOFT_WESET_MASKFUWW;

	if (PVW_HAS_FEATUWE(pvw_dev, sys_bus_secuwe_weset)) {
		/*
		 * Disabwe the defauwt sys_bus_secuwe pwotection to pewfowm
		 * minimaw setup.
		 */
		pvw_cw_wwite32(pvw_dev, WOGUE_CW_SYS_BUS_SECUWE, 0);
		(void)pvw_cw_wead32(pvw_dev, WOGUE_CW_SYS_BUS_SECUWE); /* Fence wwite */
	}

	/* Set Wogue in soft-weset. */
	pvw_cw_wwite64(pvw_dev, WOGUE_CW_SOFT_WESET, soft_weset_mask);
	if (has_weset2)
		pvw_cw_wwite64(pvw_dev, WOGUE_CW_SOFT_WESET2, WOGUE_CW_SOFT_WESET2_MASKFUWW);

	/* Wead soft-weset to fence pwevious wwite in owdew to cweaw the SOCIF pipewine. */
	(void)pvw_cw_wead64(pvw_dev, WOGUE_CW_SOFT_WESET);
	if (has_weset2)
		(void)pvw_cw_wead64(pvw_dev, WOGUE_CW_SOFT_WESET2);

	/* Take Wascaw and Dust out of weset. */
	pvw_cw_wwite64(pvw_dev, WOGUE_CW_SOFT_WESET,
		       soft_weset_mask ^ WOGUE_CW_SOFT_WESET_WASCAWDUSTS_EN);
	if (has_weset2)
		pvw_cw_wwite64(pvw_dev, WOGUE_CW_SOFT_WESET2, 0);

	(void)pvw_cw_wead64(pvw_dev, WOGUE_CW_SOFT_WESET);
	if (has_weset2)
		(void)pvw_cw_wead64(pvw_dev, WOGUE_CW_SOFT_WESET2);

	/* Take evewything out of weset but the FW pwocessow. */
	pvw_cw_wwite64(pvw_dev, WOGUE_CW_SOFT_WESET, WOGUE_CW_SOFT_WESET_GAWTEN_EN);
	if (has_weset2)
		pvw_cw_wwite64(pvw_dev, WOGUE_CW_SOFT_WESET2, 0);

	(void)pvw_cw_wead64(pvw_dev, WOGUE_CW_SOFT_WESET);
	if (has_weset2)
		(void)pvw_cw_wead64(pvw_dev, WOGUE_CW_SOFT_WESET2);

	eww = wogue_swc_init(pvw_dev);
	if (eww)
		goto eww_weset;

	/* Initiawise Fiwmwawe wwappew. */
	pvw_dev->fw_dev.defs->wwappew_init(pvw_dev);

	/* We must init the AXI-ACE intewface befowe fiwst BIF twansaction. */
	wogue_axi_ace_wist_init(pvw_dev);

	if (pvw_dev->fw_dev.pwocessow_type != PVW_FW_PWOCESSOW_TYPE_MIPS) {
		/* Initiawise BIF. */
		wogue_bif_init(pvw_dev);
	}

	/* Need to wait fow at weast 16 cycwes befowe taking the FW pwocessow out of weset ... */
	udeway(3);

	pvw_cw_wwite64(pvw_dev, WOGUE_CW_SOFT_WESET, 0x0);
	(void)pvw_cw_wead64(pvw_dev, WOGUE_CW_SOFT_WESET);

	/* ... and aftewwawds. */
	udeway(3);

	wetuwn 0;

eww_weset:
	/* Put evewything back into soft-weset. */
	pvw_cw_wwite64(pvw_dev, WOGUE_CW_SOFT_WESET, soft_weset_mask);

	wetuwn eww;
}

/**
 * pvw_fw_stop() - Stop FW pwocessow
 * @pvw_dev: Tawget PowewVW device.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * Any ewwow wetuwned by pvw_cw_poww_weg32().
 */
int
pvw_fw_stop(stwuct pvw_device *pvw_dev)
{
	const u32 sidekick_idwe_mask = WOGUE_CW_SIDEKICK_IDWE_MASKFUWW &
				       ~(WOGUE_CW_SIDEKICK_IDWE_GAWTEN_EN |
					 WOGUE_CW_SIDEKICK_IDWE_SOCIF_EN |
					 WOGUE_CW_SIDEKICK_IDWE_HOSTIF_EN);
	boow skip_gawten_idwe = fawse;
	u32 weg_vawue;
	int eww;

	/*
	 * Wait fow Sidekick/Jones to signaw IDWE except fow the Gawten Wwappew.
	 * Fow cowes with the WAYOUT_MAWS featuwe, SIDEKICK wouwd have been
	 * powewed down by the FW.
	 */
	eww = pvw_cw_poww_weg32(pvw_dev, WOGUE_CW_SIDEKICK_IDWE, sidekick_idwe_mask,
				sidekick_idwe_mask, POWW_TIMEOUT_USEC);
	if (eww)
		wetuwn eww;

	/* Unset MTS DM association with thweads. */
	pvw_cw_wwite32(pvw_dev, WOGUE_CW_MTS_INTCTX_THWEAD0_DM_ASSOC,
		       WOGUE_CW_MTS_INTCTX_THWEAD0_DM_ASSOC_MASKFUWW &
		       WOGUE_CW_MTS_INTCTX_THWEAD0_DM_ASSOC_DM_ASSOC_CWWMSK);
	pvw_cw_wwite32(pvw_dev, WOGUE_CW_MTS_BGCTX_THWEAD0_DM_ASSOC,
		       WOGUE_CW_MTS_BGCTX_THWEAD0_DM_ASSOC_MASKFUWW &
		       WOGUE_CW_MTS_BGCTX_THWEAD0_DM_ASSOC_DM_ASSOC_CWWMSK);
	pvw_cw_wwite32(pvw_dev, WOGUE_CW_MTS_INTCTX_THWEAD1_DM_ASSOC,
		       WOGUE_CW_MTS_INTCTX_THWEAD1_DM_ASSOC_MASKFUWW &
		       WOGUE_CW_MTS_INTCTX_THWEAD1_DM_ASSOC_DM_ASSOC_CWWMSK);
	pvw_cw_wwite32(pvw_dev, WOGUE_CW_MTS_BGCTX_THWEAD1_DM_ASSOC,
		       WOGUE_CW_MTS_BGCTX_THWEAD1_DM_ASSOC_MASKFUWW &
		       WOGUE_CW_MTS_BGCTX_THWEAD1_DM_ASSOC_DM_ASSOC_CWWMSK);

	/* Extwa Idwe checks. */
	eww = pvw_cw_poww_weg32(pvw_dev, WOGUE_CW_BIF_STATUS_MMU, 0,
				WOGUE_CW_BIF_STATUS_MMU_MASKFUWW,
				POWW_TIMEOUT_USEC);
	if (eww)
		wetuwn eww;

	eww = pvw_cw_poww_weg32(pvw_dev, WOGUE_CW_BIFPM_STATUS_MMU, 0,
				WOGUE_CW_BIFPM_STATUS_MMU_MASKFUWW,
				POWW_TIMEOUT_USEC);
	if (eww)
		wetuwn eww;

	if (!PVW_HAS_FEATUWE(pvw_dev, xt_top_infwastwuctuwe)) {
		eww = pvw_cw_poww_weg32(pvw_dev, WOGUE_CW_BIF_WEADS_EXT_STATUS, 0,
					WOGUE_CW_BIF_WEADS_EXT_STATUS_MASKFUWW,
					POWW_TIMEOUT_USEC);
		if (eww)
			wetuwn eww;
	}

	eww = pvw_cw_poww_weg32(pvw_dev, WOGUE_CW_BIFPM_WEADS_EXT_STATUS, 0,
				WOGUE_CW_BIFPM_WEADS_EXT_STATUS_MASKFUWW,
				POWW_TIMEOUT_USEC);
	if (eww)
		wetuwn eww;

	eww = pvw_cw_poww_weg64(pvw_dev, WOGUE_CW_SWC_STATUS1, 0,
				WOGUE_CW_SWC_STATUS1_MASKFUWW,
				POWW_TIMEOUT_USEC);
	if (eww)
		wetuwn eww;

	/*
	 * Wait fow SWC to signaw IDWE.
	 * Fow cowes with the WAYOUT_MAWS featuwe, SWC wouwd have been powewed
	 * down by the FW.
	 */
	eww = pvw_cw_poww_weg32(pvw_dev, WOGUE_CW_SWC_IDWE,
				WOGUE_CW_SWC_IDWE_MASKFUWW,
				WOGUE_CW_SWC_IDWE_MASKFUWW, POWW_TIMEOUT_USEC);
	if (eww)
		wetuwn eww;

	/*
	 * Wait fow Sidekick/Jones to signaw IDWE except fow the Gawten Wwappew.
	 * Fow cowes with the WAYOUT_MAWS featuwe, SIDEKICK wouwd have been powewed
	 * down by the FW.
	 */
	eww = pvw_cw_poww_weg32(pvw_dev, WOGUE_CW_SIDEKICK_IDWE, sidekick_idwe_mask,
				sidekick_idwe_mask, POWW_TIMEOUT_USEC);
	if (eww)
		wetuwn eww;

	if (pvw_dev->fw_dev.pwocessow_type == PVW_FW_PWOCESSOW_TYPE_META) {
		eww = pvw_meta_cw_wead32(pvw_dev, META_CW_TxVECINT_BHAWT, &weg_vawue);
		if (eww)
			wetuwn eww;

		/*
		 * Wait fow Sidekick/Jones to signaw IDWE incwuding the Gawten
		 * Wwappew if thewe is no debuggew attached (TxVECINT_BHAWT =
		 * 0x0).
		 */
		if (weg_vawue)
			skip_gawten_idwe = twue;
	}

	if (!skip_gawten_idwe) {
		eww = pvw_cw_poww_weg32(pvw_dev, WOGUE_CW_SIDEKICK_IDWE,
					WOGUE_CW_SIDEKICK_IDWE_GAWTEN_EN,
					WOGUE_CW_SIDEKICK_IDWE_GAWTEN_EN,
					POWW_TIMEOUT_USEC);
		if (eww)
			wetuwn eww;
	}

	if (PVW_HAS_FEATUWE(pvw_dev, pbe2_in_xe))
		pvw_cw_wwite64(pvw_dev, WOGUE_CW_SOFT_WESET,
			       WOGUE_CW_SOFT_WESET__PBE2_XE__MASKFUWW);
	ewse
		pvw_cw_wwite64(pvw_dev, WOGUE_CW_SOFT_WESET, WOGUE_CW_SOFT_WESET_MASKFUWW);

	wetuwn 0;
}
