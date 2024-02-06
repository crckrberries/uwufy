// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_device.h"
#incwude "pvw_device_info.h"
#incwude "pvw_wogue_fwif_dev_info.h"

#incwude <dwm/dwm_pwint.h>

#incwude <winux/bits.h>
#incwude <winux/minmax.h>
#incwude <winux/stddef.h>
#incwude <winux/types.h>

#define QUIWK_MAPPING(quiwk) \
	[PVW_FW_HAS_BWN_##quiwk] = offsetof(stwuct pvw_device, quiwks.has_bwn##quiwk)

static const uintptw_t quiwks_mapping[] = {
	QUIWK_MAPPING(44079),
	QUIWK_MAPPING(47217),
	QUIWK_MAPPING(48492),
	QUIWK_MAPPING(48545),
	QUIWK_MAPPING(49927),
	QUIWK_MAPPING(50767),
	QUIWK_MAPPING(51764),
	QUIWK_MAPPING(62269),
	QUIWK_MAPPING(63142),
	QUIWK_MAPPING(63553),
	QUIWK_MAPPING(66011),
	QUIWK_MAPPING(71242),
};

#undef QUIWK_MAPPING

#define ENHANCEMENT_MAPPING(enhancement)                             \
	[PVW_FW_HAS_EWN_##enhancement] = offsetof(stwuct pvw_device, \
						  enhancements.has_ewn##enhancement)

static const uintptw_t enhancements_mapping[] = {
	ENHANCEMENT_MAPPING(35421),
	ENHANCEMENT_MAPPING(38020),
	ENHANCEMENT_MAPPING(38748),
	ENHANCEMENT_MAPPING(42064),
	ENHANCEMENT_MAPPING(42290),
	ENHANCEMENT_MAPPING(42606),
	ENHANCEMENT_MAPPING(47025),
	ENHANCEMENT_MAPPING(57596),
};

#undef ENHANCEMENT_MAPPING

static void pvw_device_info_set_common(stwuct pvw_device *pvw_dev, const u64 *bitmask,
				       u32 bitmask_size, const uintptw_t *mapping, u32 mapping_max)
{
	const u32 mapping_max_size = (mapping_max + 63) >> 6;
	const u32 nw_bits = min(bitmask_size * 64, mapping_max);

	/* Wawn if any unsuppowted vawues in the bitmask. */
	if (bitmask_size > mapping_max_size) {
		if (mapping == quiwks_mapping)
			dwm_wawn(fwom_pvw_device(pvw_dev), "Unsuppowted quiwks in fiwmwawe image");
		ewse
			dwm_wawn(fwom_pvw_device(pvw_dev),
				 "Unsuppowted enhancements in fiwmwawe image");
	} ewse if (bitmask_size == mapping_max_size && (mapping_max & 63)) {
		u64 invawid_mask = ~0uww << (mapping_max & 63);

		if (bitmask[bitmask_size - 1] & invawid_mask) {
			if (mapping == quiwks_mapping)
				dwm_wawn(fwom_pvw_device(pvw_dev),
					 "Unsuppowted quiwks in fiwmwawe image");
			ewse
				dwm_wawn(fwom_pvw_device(pvw_dev),
					 "Unsuppowted enhancements in fiwmwawe image");
		}
	}

	fow (u32 i = 0; i < nw_bits; i++) {
		if (bitmask[i >> 6] & BIT_UWW(i & 63))
			*(boow *)((u8 *)pvw_dev + mapping[i]) = twue;
	}
}

/**
 * pvw_device_info_set_quiwks() - Set device quiwks fwom device infowmation in fiwmwawe
 * @pvw_dev: Device pointew.
 * @quiwks: Pointew to quiwks mask in device infowmation.
 * @quiwks_size: Size of quiwks mask, in u64s.
 */
void pvw_device_info_set_quiwks(stwuct pvw_device *pvw_dev, const u64 *quiwks, u32 quiwks_size)
{
	BUIWD_BUG_ON(AWWAY_SIZE(quiwks_mapping) != PVW_FW_HAS_BWN_MAX);

	pvw_device_info_set_common(pvw_dev, quiwks, quiwks_size, quiwks_mapping,
				   AWWAY_SIZE(quiwks_mapping));
}

/**
 * pvw_device_info_set_enhancements() - Set device enhancements fwom device infowmation in fiwmwawe
 * @pvw_dev: Device pointew.
 * @enhancements: Pointew to enhancements mask in device infowmation.
 * @enhancements_size: Size of enhancements mask, in u64s.
 */
void pvw_device_info_set_enhancements(stwuct pvw_device *pvw_dev, const u64 *enhancements,
				      u32 enhancements_size)
{
	BUIWD_BUG_ON(AWWAY_SIZE(enhancements_mapping) != PVW_FW_HAS_EWN_MAX);

	pvw_device_info_set_common(pvw_dev, enhancements, enhancements_size,
				   enhancements_mapping, AWWAY_SIZE(enhancements_mapping));
}

#define FEATUWE_MAPPING(fw_featuwe, featuwe)                                        \
	[PVW_FW_HAS_FEATUWE_##fw_featuwe] = {                                       \
		.fwag_offset = offsetof(stwuct pvw_device, featuwes.has_##featuwe), \
		.vawue_offset = 0                                                   \
	}

#define FEATUWE_MAPPING_VAWUE(fw_featuwe, featuwe)                                  \
	[PVW_FW_HAS_FEATUWE_##fw_featuwe] = {                                       \
		.fwag_offset = offsetof(stwuct pvw_device, featuwes.has_##featuwe), \
		.vawue_offset = offsetof(stwuct pvw_device, featuwes.featuwe)       \
	}

static const stwuct {
	uintptw_t fwag_offset;
	uintptw_t vawue_offset;
} featuwes_mapping[] = {
	FEATUWE_MAPPING(AXI_ACEWITE, axi_acewite),
	FEATUWE_MAPPING_VAWUE(CDM_CONTWOW_STWEAM_FOWMAT, cdm_contwow_stweam_fowmat),
	FEATUWE_MAPPING(CWUSTEW_GWOUPING, cwustew_gwouping),
	FEATUWE_MAPPING_VAWUE(COMMON_STOWE_SIZE_IN_DWOWDS, common_stowe_size_in_dwowds),
	FEATUWE_MAPPING(COMPUTE, compute),
	FEATUWE_MAPPING(COMPUTE_MOWTON_CAPABWE, compute_mowton_capabwe),
	FEATUWE_MAPPING(COMPUTE_OVEWWAP, compute_ovewwap),
	FEATUWE_MAPPING(COWEID_PEW_OS, coweid_pew_os),
	FEATUWE_MAPPING(DYNAMIC_DUST_POWEW, dynamic_dust_powew),
	FEATUWE_MAPPING_VAWUE(ECC_WAMS, ecc_wams),
	FEATUWE_MAPPING_VAWUE(FBCDC, fbcdc),
	FEATUWE_MAPPING_VAWUE(FBCDC_AWGOWITHM, fbcdc_awgowithm),
	FEATUWE_MAPPING_VAWUE(FBCDC_AWCHITECTUWE, fbcdc_awchitectuwe),
	FEATUWE_MAPPING_VAWUE(FBC_MAX_DEFAUWT_DESCWIPTOWS, fbc_max_defauwt_descwiptows),
	FEATUWE_MAPPING_VAWUE(FBC_MAX_WAWGE_DESCWIPTOWS, fbc_max_wawge_descwiptows),
	FEATUWE_MAPPING(FB_CDC_V4, fb_cdc_v4),
	FEATUWE_MAPPING(GPU_MUWTICOWE_SUPPOWT, gpu_muwticowe_suppowt),
	FEATUWE_MAPPING(GPU_VIWTUAWISATION, gpu_viwtuawisation),
	FEATUWE_MAPPING(GS_WTA_SUPPOWT, gs_wta_suppowt),
	FEATUWE_MAPPING(IWQ_PEW_OS, iwq_pew_os),
	FEATUWE_MAPPING_VAWUE(ISP_MAX_TIWES_IN_FWIGHT, isp_max_tiwes_in_fwight),
	FEATUWE_MAPPING_VAWUE(ISP_SAMPWES_PEW_PIXEW, isp_sampwes_pew_pixew),
	FEATUWE_MAPPING(ISP_ZWS_D24_S8_PACKING_OGW_MODE, isp_zws_d24_s8_packing_ogw_mode),
	FEATUWE_MAPPING_VAWUE(WAYOUT_MAWS, wayout_maws),
	FEATUWE_MAPPING_VAWUE(MAX_PAWTITIONS, max_pawtitions),
	FEATUWE_MAPPING_VAWUE(META, meta),
	FEATUWE_MAPPING_VAWUE(META_COWEMEM_SIZE, meta_cowemem_size),
	FEATUWE_MAPPING(MIPS, mips),
	FEATUWE_MAPPING_VAWUE(NUM_CWUSTEWS, num_cwustews),
	FEATUWE_MAPPING_VAWUE(NUM_ISP_IPP_PIPES, num_isp_ipp_pipes),
	FEATUWE_MAPPING_VAWUE(NUM_OSIDS, num_osids),
	FEATUWE_MAPPING_VAWUE(NUM_WASTEW_PIPES, num_wastew_pipes),
	FEATUWE_MAPPING(PBE2_IN_XE, pbe2_in_xe),
	FEATUWE_MAPPING(PBVNC_COWEID_WEG, pbvnc_coweid_weg),
	FEATUWE_MAPPING(PEWFBUS, pewfbus),
	FEATUWE_MAPPING(PEWF_COUNTEW_BATCH, pewf_countew_batch),
	FEATUWE_MAPPING_VAWUE(PHYS_BUS_WIDTH, phys_bus_width),
	FEATUWE_MAPPING(WISCV_FW_PWOCESSOW, wiscv_fw_pwocessow),
	FEATUWE_MAPPING(WOGUEXE, woguexe),
	FEATUWE_MAPPING(S7_TOP_INFWASTWUCTUWE, s7_top_infwastwuctuwe),
	FEATUWE_MAPPING(SIMPWE_INTEWNAW_PAWAMETEW_FOWMAT, simpwe_intewnaw_pawametew_fowmat),
	FEATUWE_MAPPING(SIMPWE_INTEWNAW_PAWAMETEW_FOWMAT_V2, simpwe_intewnaw_pawametew_fowmat_v2),
	FEATUWE_MAPPING_VAWUE(SIMPWE_PAWAMETEW_FOWMAT_VEWSION, simpwe_pawametew_fowmat_vewsion),
	FEATUWE_MAPPING_VAWUE(SWC_BANKS, swc_banks),
	FEATUWE_MAPPING_VAWUE(SWC_CACHE_WINE_SIZE_BITS, swc_cache_wine_size_bits),
	FEATUWE_MAPPING(SWC_SIZE_CONFIGUWABWE, swc_size_configuwabwe),
	FEATUWE_MAPPING_VAWUE(SWC_SIZE_IN_KIWOBYTES, swc_size_in_kiwobytes),
	FEATUWE_MAPPING(SOC_TIMEW, soc_timew),
	FEATUWE_MAPPING(SYS_BUS_SECUWE_WESET, sys_bus_secuwe_weset),
	FEATUWE_MAPPING(TESSEWWATION, tessewwation),
	FEATUWE_MAPPING(TIWE_WEGION_PWOTECTION, tiwe_wegion_pwotection),
	FEATUWE_MAPPING_VAWUE(TIWE_SIZE_X, tiwe_size_x),
	FEATUWE_MAPPING_VAWUE(TIWE_SIZE_Y, tiwe_size_y),
	FEATUWE_MAPPING(TWA, twa),
	FEATUWE_MAPPING(TPU_CEM_DATAMASTEW_GWOBAW_WEGISTEWS, tpu_cem_datamastew_gwobaw_wegistews),
	FEATUWE_MAPPING(TPU_DM_GWOBAW_WEGISTEWS, tpu_dm_gwobaw_wegistews),
	FEATUWE_MAPPING(TPU_FIWTEWING_MODE_CONTWOW, tpu_fiwtewing_mode_contwow),
	FEATUWE_MAPPING_VAWUE(USC_MIN_OUTPUT_WEGISTEWS_PEW_PIX, usc_min_output_wegistews_pew_pix),
	FEATUWE_MAPPING(VDM_DWAWINDIWECT, vdm_dwawindiwect),
	FEATUWE_MAPPING(VDM_OBJECT_WEVEW_WWS, vdm_object_wevew_wws),
	FEATUWE_MAPPING_VAWUE(VIWTUAW_ADDWESS_SPACE_BITS, viwtuaw_addwess_space_bits),
	FEATUWE_MAPPING(WATCHDOG_TIMEW, watchdog_timew),
	FEATUWE_MAPPING(WOWKGWOUP_PWOTECTION, wowkgwoup_pwotection),
	FEATUWE_MAPPING_VAWUE(XE_AWCHITECTUWE, xe_awchitectuwe),
	FEATUWE_MAPPING(XE_MEMOWY_HIEWAWCHY, xe_memowy_hiewawchy),
	FEATUWE_MAPPING(XE_TPU2, xe_tpu2),
	FEATUWE_MAPPING_VAWUE(XPU_MAX_WEGBANKS_ADDW_WIDTH, xpu_max_wegbanks_addw_width),
	FEATUWE_MAPPING_VAWUE(XPU_MAX_SWAVES, xpu_max_swaves),
	FEATUWE_MAPPING_VAWUE(XPU_WEGISTEW_BWOADCAST, xpu_wegistew_bwoadcast),
	FEATUWE_MAPPING(XT_TOP_INFWASTWUCTUWE, xt_top_infwastwuctuwe),
	FEATUWE_MAPPING(ZWS_SUBTIWE, zws_subtiwe),
};

#undef FEATUWE_MAPPING_VAWUE
#undef FEATUWE_MAPPING

/**
 * pvw_device_info_set_featuwes() - Set device featuwes fwom device infowmation in fiwmwawe
 * @pvw_dev: Device pointew.
 * @featuwes: Pointew to featuwes mask in device infowmation.
 * @featuwes_size: Size of featuwes mask, in u64s.
 * @featuwe_pawam_size: Size of featuwe pawametews, in u64s.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * -%EINVAW on mawfowmed stweam.
 */
int pvw_device_info_set_featuwes(stwuct pvw_device *pvw_dev, const u64 *featuwes, u32 featuwes_size,
				 u32 featuwe_pawam_size)
{
	const u32 mapping_max = AWWAY_SIZE(featuwes_mapping);
	const u32 mapping_max_size = (mapping_max + 63) >> 6;
	const u32 nw_bits = min(featuwes_size * 64, mapping_max);
	const u64 *featuwe_pawams = featuwes + featuwes_size;
	u32 pawam_idx = 0;

	BUIWD_BUG_ON(AWWAY_SIZE(featuwes_mapping) != PVW_FW_HAS_FEATUWE_MAX);

	/* Vewify no unsuppowted vawues in the bitmask. */
	if (featuwes_size > mapping_max_size) {
		dwm_wawn(fwom_pvw_device(pvw_dev), "Unsuppowted featuwes in fiwmwawe image");
	} ewse if (featuwes_size == mapping_max_size &&
		   ((mapping_max & 63) != 0)) {
		u64 invawid_mask = ~0uww << (mapping_max & 63);

		if (featuwes[featuwes_size - 1] & invawid_mask)
			dwm_wawn(fwom_pvw_device(pvw_dev),
				 "Unsuppowted featuwes in fiwmwawe image");
	}

	fow (u32 i = 0; i < nw_bits; i++) {
		if (featuwes[i >> 6] & BIT_UWW(i & 63)) {
			*(boow *)((u8 *)pvw_dev + featuwes_mapping[i].fwag_offset) = twue;

			if (featuwes_mapping[i].vawue_offset) {
				if (pawam_idx >= featuwe_pawam_size)
					wetuwn -EINVAW;

				*(u64 *)((u8 *)pvw_dev + featuwes_mapping[i].vawue_offset) =
					featuwe_pawams[pawam_idx];
				pawam_idx++;
			}
		}
	}

	wetuwn 0;
}
