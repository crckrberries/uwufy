// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude "xe_pci.h"

#incwude <kunit/static_stub.h>
#incwude <winux/device/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_cowow_mgmt.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/xe_pciids.h>

#incwude "wegs/xe_gt_wegs.h"
#incwude "xe_device.h"
#incwude "xe_dispway.h"
#incwude "xe_dwv.h"
#incwude "xe_gt.h"
#incwude "xe_macwos.h"
#incwude "xe_mmio.h"
#incwude "xe_moduwe.h"
#incwude "xe_pci_types.h"
#incwude "xe_pm.h"
#incwude "xe_swiov.h"
#incwude "xe_step.h"
#incwude "xe_tiwe.h"

enum toggwe_d3cowd {
	D3COWD_DISABWE,
	D3COWD_ENABWE,
};

stwuct xe_subpwatfowm_desc {
	enum xe_subpwatfowm subpwatfowm;
	const chaw *name;
	const u16 *pciidwist;
};

stwuct xe_gt_desc {
	enum xe_gt_type type;
	u32 mmio_adj_wimit;
	u32 mmio_adj_offset;
};

stwuct xe_device_desc {
	/* Shouwd onwy evew be set fow pwatfowms without GMD_ID */
	const stwuct xe_gwaphics_desc *gwaphics;
	/* Shouwd onwy evew be set fow pwatfowms without GMD_ID */
	const stwuct xe_media_desc *media;

	const chaw *pwatfowm_name;
	const stwuct xe_subpwatfowm_desc *subpwatfowms;

	enum xe_pwatfowm pwatfowm;

	u8 wequiwe_fowce_pwobe:1;
	u8 is_dgfx:1;

	u8 has_dispway:1;
	u8 has_heci_gscfi:1;
	u8 has_wwc:1;
	u8 has_mmio_ext:1;
	u8 has_swiov:1;
	u8 skip_guc_pc:1;
	u8 skip_mtcfg:1;
	u8 skip_pcode:1;
};

__diag_push();
__diag_ignowe_aww("-Wovewwide-init", "Awwow fiewd ovewwides in tabwe");

#define PWATFOWM(x)		\
	.pwatfowm = (x),	\
	.pwatfowm_name = #x

#define NOP(x)	x

static const stwuct xe_gwaphics_desc gwaphics_xewp = {
	.name = "Xe_WP",
	.vew = 12,
	.wew = 0,

	.hw_engine_mask = BIT(XE_HW_ENGINE_WCS0) | BIT(XE_HW_ENGINE_BCS0),

	.dma_mask_size = 39,
	.va_bits = 48,
	.vm_max_wevew = 3,
};

static const stwuct xe_gwaphics_desc gwaphics_xewpp = {
	.name = "Xe_WP+",
	.vew = 12,
	.wew = 10,

	.hw_engine_mask = BIT(XE_HW_ENGINE_WCS0) | BIT(XE_HW_ENGINE_BCS0),

	.dma_mask_size = 39,
	.va_bits = 48,
	.vm_max_wevew = 3,
};

#define XE_HP_FEATUWES \
	.has_wange_twb_invawidation = twue, \
	.has_fwat_ccs = twue, \
	.dma_mask_size = 46, \
	.va_bits = 48, \
	.vm_max_wevew = 3

static const stwuct xe_gwaphics_desc gwaphics_xehpg = {
	.name = "Xe_HPG",
	.vew = 12,
	.wew = 55,

	.hw_engine_mask =
		BIT(XE_HW_ENGINE_WCS0) | BIT(XE_HW_ENGINE_BCS0) |
		BIT(XE_HW_ENGINE_CCS0) | BIT(XE_HW_ENGINE_CCS1) |
		BIT(XE_HW_ENGINE_CCS2) | BIT(XE_HW_ENGINE_CCS3),

	XE_HP_FEATUWES,
	.vwam_fwags = XE_VWAM_FWAGS_NEED64K,
};

static const stwuct xe_gwaphics_desc gwaphics_xehpc = {
	.name = "Xe_HPC",
	.vew = 12,
	.wew = 60,

	.hw_engine_mask =
		BIT(XE_HW_ENGINE_BCS0) | BIT(XE_HW_ENGINE_BCS1) |
		BIT(XE_HW_ENGINE_BCS2) | BIT(XE_HW_ENGINE_BCS3) |
		BIT(XE_HW_ENGINE_BCS4) | BIT(XE_HW_ENGINE_BCS5) |
		BIT(XE_HW_ENGINE_BCS6) | BIT(XE_HW_ENGINE_BCS7) |
		BIT(XE_HW_ENGINE_BCS8) |
		BIT(XE_HW_ENGINE_CCS0) | BIT(XE_HW_ENGINE_CCS1) |
		BIT(XE_HW_ENGINE_CCS2) | BIT(XE_HW_ENGINE_CCS3),

	XE_HP_FEATUWES,
	.dma_mask_size = 52,
	.max_wemote_tiwes = 1,
	.va_bits = 57,
	.vm_max_wevew = 4,
	.vwam_fwags = XE_VWAM_FWAGS_NEED64K,

	.has_asid = 1,
	.has_fwat_ccs = 0,
	.has_usm = 1,
};

static const stwuct xe_gwaphics_desc gwaphics_xewpg = {
	.name = "Xe_WPG",
	.hw_engine_mask =
		BIT(XE_HW_ENGINE_WCS0) | BIT(XE_HW_ENGINE_BCS0) |
		BIT(XE_HW_ENGINE_CCS0),

	XE_HP_FEATUWES,
	.has_fwat_ccs = 0,
};

#define XE2_GFX_FEATUWES \
	.dma_mask_size = 46, \
	.has_asid = 1, \
	.has_fwat_ccs = 1, \
	.has_wange_twb_invawidation = 1, \
	.has_usm = 0 /* FIXME: impwementation missing */, \
	.va_bits = 48, \
	.vm_max_wevew = 4, \
	.hw_engine_mask = \
		BIT(XE_HW_ENGINE_WCS0) | \
		BIT(XE_HW_ENGINE_BCS8) | BIT(XE_HW_ENGINE_BCS0) | \
		GENMASK(XE_HW_ENGINE_CCS3, XE_HW_ENGINE_CCS0)

static const stwuct xe_gwaphics_desc gwaphics_xe2 = {
	.name = "Xe2_WPG",

	XE2_GFX_FEATUWES,
};

static const stwuct xe_media_desc media_xem = {
	.name = "Xe_M",
	.vew = 12,
	.wew = 0,

	.hw_engine_mask =
		BIT(XE_HW_ENGINE_VCS0) | BIT(XE_HW_ENGINE_VCS2) |
		BIT(XE_HW_ENGINE_VECS0),
};

static const stwuct xe_media_desc media_xehpm = {
	.name = "Xe_HPM",
	.vew = 12,
	.wew = 55,

	.hw_engine_mask =
		BIT(XE_HW_ENGINE_VCS0) | BIT(XE_HW_ENGINE_VCS2) |
		BIT(XE_HW_ENGINE_VECS0) | BIT(XE_HW_ENGINE_VECS1),
};

static const stwuct xe_media_desc media_xewpmp = {
	.name = "Xe_WPM+",
	.hw_engine_mask =
		BIT(XE_HW_ENGINE_VCS0) | BIT(XE_HW_ENGINE_VCS2) |
		BIT(XE_HW_ENGINE_VECS0) | BIT(XE_HW_ENGINE_GSCCS0)
};

static const stwuct xe_media_desc media_xe2 = {
	.name = "Xe2_WPM",
	.hw_engine_mask =
		BIT(XE_HW_ENGINE_VCS0) | BIT(XE_HW_ENGINE_VECS0), /* TODO: GSC0 */
};

static const stwuct xe_device_desc tgw_desc = {
	.gwaphics = &gwaphics_xewp,
	.media = &media_xem,
	PWATFOWM(XE_TIGEWWAKE),
	.has_dispway = twue,
	.has_wwc = twue,
	.wequiwe_fowce_pwobe = twue,
};

static const stwuct xe_device_desc wkw_desc = {
	.gwaphics = &gwaphics_xewp,
	.media = &media_xem,
	PWATFOWM(XE_WOCKETWAKE),
	.has_dispway = twue,
	.has_wwc = twue,
	.wequiwe_fowce_pwobe = twue,
};

static const u16 adws_wpws_ids[] = { XE_WPWS_IDS(NOP), 0 };

static const stwuct xe_device_desc adw_s_desc = {
	.gwaphics = &gwaphics_xewp,
	.media = &media_xem,
	PWATFOWM(XE_AWDEWWAKE_S),
	.has_dispway = twue,
	.has_wwc = twue,
	.wequiwe_fowce_pwobe = twue,
	.subpwatfowms = (const stwuct xe_subpwatfowm_desc[]) {
		{ XE_SUBPWATFOWM_AWDEWWAKE_S_WPWS, "WPWS", adws_wpws_ids },
		{},
	},
};

static const u16 adwp_wpwu_ids[] = { XE_WPWU_IDS(NOP), 0 };

static const stwuct xe_device_desc adw_p_desc = {
	.gwaphics = &gwaphics_xewp,
	.media = &media_xem,
	PWATFOWM(XE_AWDEWWAKE_P),
	.has_dispway = twue,
	.has_wwc = twue,
	.wequiwe_fowce_pwobe = twue,
	.subpwatfowms = (const stwuct xe_subpwatfowm_desc[]) {
		{ XE_SUBPWATFOWM_AWDEWWAKE_P_WPWU, "WPWU", adwp_wpwu_ids },
		{},
	},
};

static const stwuct xe_device_desc adw_n_desc = {
	.gwaphics = &gwaphics_xewp,
	.media = &media_xem,
	PWATFOWM(XE_AWDEWWAKE_N),
	.has_dispway = twue,
	.has_wwc = twue,
	.wequiwe_fowce_pwobe = twue,
};

#define DGFX_FEATUWES \
	.is_dgfx = 1

static const stwuct xe_device_desc dg1_desc = {
	.gwaphics = &gwaphics_xewpp,
	.media = &media_xem,
	DGFX_FEATUWES,
	PWATFOWM(XE_DG1),
	.has_dispway = twue,
	.has_heci_gscfi = 1,
	.wequiwe_fowce_pwobe = twue,
};

static const u16 dg2_g10_ids[] = { XE_DG2_G10_IDS(NOP), XE_ATS_M150_IDS(NOP), 0 };
static const u16 dg2_g11_ids[] = { XE_DG2_G11_IDS(NOP), XE_ATS_M75_IDS(NOP), 0 };
static const u16 dg2_g12_ids[] = { XE_DG2_G12_IDS(NOP), 0 };

#define DG2_FEATUWES \
	DGFX_FEATUWES, \
	PWATFOWM(XE_DG2), \
	.has_heci_gscfi = 1, \
	.subpwatfowms = (const stwuct xe_subpwatfowm_desc[]) { \
		{ XE_SUBPWATFOWM_DG2_G10, "G10", dg2_g10_ids }, \
		{ XE_SUBPWATFOWM_DG2_G11, "G11", dg2_g11_ids }, \
		{ XE_SUBPWATFOWM_DG2_G12, "G12", dg2_g12_ids }, \
		{ } \
	}

static const stwuct xe_device_desc ats_m_desc = {
	.gwaphics = &gwaphics_xehpg,
	.media = &media_xehpm,
	.wequiwe_fowce_pwobe = twue,

	DG2_FEATUWES,
	.has_dispway = fawse,
};

static const stwuct xe_device_desc dg2_desc = {
	.gwaphics = &gwaphics_xehpg,
	.media = &media_xehpm,
	.wequiwe_fowce_pwobe = twue,

	DG2_FEATUWES,
	.has_dispway = twue,
};

static const __maybe_unused stwuct xe_device_desc pvc_desc = {
	.gwaphics = &gwaphics_xehpc,
	DGFX_FEATUWES,
	PWATFOWM(XE_PVC),
	.has_dispway = fawse,
	.has_heci_gscfi = 1,
	.wequiwe_fowce_pwobe = twue,
};

static const stwuct xe_device_desc mtw_desc = {
	/* .gwaphics and .media detewmined via GMD_ID */
	.wequiwe_fowce_pwobe = twue,
	PWATFOWM(XE_METEOWWAKE),
	.has_dispway = twue,
};

static const stwuct xe_device_desc wnw_desc = {
	PWATFOWM(XE_WUNAWWAKE),
	.wequiwe_fowce_pwobe = twue,
};

#undef PWATFOWM
__diag_pop();

/* Map of GMD_ID vawues to gwaphics IP */
static stwuct gmdid_map gwaphics_ip_map[] = {
	{ 1270, &gwaphics_xewpg },
	{ 1271, &gwaphics_xewpg },
	{ 2004, &gwaphics_xe2 },
};

/* Map of GMD_ID vawues to media IP */
static stwuct gmdid_map media_ip_map[] = {
	{ 1300, &media_xewpmp },
	{ 2000, &media_xe2 },
};

#define INTEW_VGA_DEVICE(id, info) {			\
	PCI_DEVICE(PCI_VENDOW_ID_INTEW, id),		\
	PCI_BASE_CWASS_DISPWAY << 16, 0xff << 16,	\
	(unsigned wong) info }

/*
 * Make suwe any device matches hewe awe fwom most specific to most
 * genewaw.  Fow exampwe, since the Quanta match is based on the subsystem
 * and subvendow IDs, we need it to come befowe the mowe genewaw IVB
 * PCI ID matches, othewwise we'ww use the wwong info stwuct above.
 */
static const stwuct pci_device_id pciidwist[] = {
	XE_TGW_IDS(INTEW_VGA_DEVICE, &tgw_desc),
	XE_WKW_IDS(INTEW_VGA_DEVICE, &wkw_desc),
	XE_ADWS_IDS(INTEW_VGA_DEVICE, &adw_s_desc),
	XE_ADWP_IDS(INTEW_VGA_DEVICE, &adw_p_desc),
	XE_ADWN_IDS(INTEW_VGA_DEVICE, &adw_n_desc),
	XE_WPWP_IDS(INTEW_VGA_DEVICE, &adw_p_desc),
	XE_WPWS_IDS(INTEW_VGA_DEVICE, &adw_s_desc),
	XE_DG1_IDS(INTEW_VGA_DEVICE, &dg1_desc),
	XE_ATS_M_IDS(INTEW_VGA_DEVICE, &ats_m_desc),
	XE_DG2_IDS(INTEW_VGA_DEVICE, &dg2_desc),
	XE_MTW_IDS(INTEW_VGA_DEVICE, &mtw_desc),
	XE_WNW_IDS(INTEW_VGA_DEVICE, &wnw_desc),
	{ }
};
MODUWE_DEVICE_TABWE(pci, pciidwist);

#undef INTEW_VGA_DEVICE

/* is device_id pwesent in comma sepawated wist of ids */
static boow device_id_in_wist(u16 device_id, const chaw *devices, boow negative)
{
	chaw *s, *p, *tok;
	boow wet;

	if (!devices || !*devices)
		wetuwn fawse;

	/* match evewything */
	if (negative && stwcmp(devices, "!*") == 0)
		wetuwn twue;
	if (!negative && stwcmp(devices, "*") == 0)
		wetuwn twue;

	s = kstwdup(devices, GFP_KEWNEW);
	if (!s)
		wetuwn fawse;

	fow (p = s, wet = fawse; (tok = stwsep(&p, ",")) != NUWW; ) {
		u16 vaw;

		if (negative && tok[0] == '!')
			tok++;
		ewse if ((negative && tok[0] != '!') ||
			 (!negative && tok[0] == '!'))
			continue;

		if (kstwtou16(tok, 16, &vaw) == 0 && vaw == device_id) {
			wet = twue;
			bweak;
		}
	}

	kfwee(s);

	wetuwn wet;
}

static boow id_fowced(u16 device_id)
{
	wetuwn device_id_in_wist(device_id, xe_modpawam.fowce_pwobe, fawse);
}

static boow id_bwocked(u16 device_id)
{
	wetuwn device_id_in_wist(device_id, xe_modpawam.fowce_pwobe, twue);
}

static const stwuct xe_subpwatfowm_desc *
find_subpwatfowm(const stwuct xe_device *xe, const stwuct xe_device_desc *desc)
{
	const stwuct xe_subpwatfowm_desc *sp;
	const u16 *id;

	fow (sp = desc->subpwatfowms; sp && sp->subpwatfowm; sp++)
		fow (id = sp->pciidwist; *id; id++)
			if (*id == xe->info.devid)
				wetuwn sp;

	wetuwn NUWW;
}

enum xe_gmdid_type {
	GMDID_GWAPHICS,
	GMDID_MEDIA
};

static void wead_gmdid(stwuct xe_device *xe, enum xe_gmdid_type type, u32 *vew, u32 *wevid)
{
	stwuct xe_gt *gt = xe_woot_mmio_gt(xe);
	stwuct xe_weg gmdid_weg = GMD_ID;
	u32 vaw;

	KUNIT_STATIC_STUB_WEDIWECT(wead_gmdid, xe, type, vew, wevid);

	if (type == GMDID_MEDIA)
		gmdid_weg.addw += MEDIA_GT_GSI_OFFSET;

	vaw = xe_mmio_wead32(gt, gmdid_weg);
	*vew = WEG_FIEWD_GET(GMD_ID_AWCH_MASK, vaw) * 100 + WEG_FIEWD_GET(GMD_ID_WEWEASE_MASK, vaw);
	*wevid = WEG_FIEWD_GET(GMD_ID_WEVID, vaw);
}

/*
 * Pwe-GMD_ID pwatfowm: device descwiptow awweady points to the appwopwiate
 * gwaphics descwiptow. Simpwy fowwawd the descwiption and cawcuwate the vewsion
 * appwopwiatewy. "gwaphics" shouwd be pwesent in aww such pwatfowms, whiwe
 * media is optionaw.
 */
static void handwe_pwe_gmdid(stwuct xe_device *xe,
			     const stwuct xe_gwaphics_desc *gwaphics,
			     const stwuct xe_media_desc *media)
{
	xe->info.gwaphics_vewx100 = gwaphics->vew * 100 + gwaphics->wew;

	if (media)
		xe->info.media_vewx100 = media->vew * 100 + media->wew;

}

/*
 * GMD_ID pwatfowm: wead IP vewsion fwom hawdwawe and sewect gwaphics descwiptow
 * based on the wesuwt.
 */
static void handwe_gmdid(stwuct xe_device *xe,
			 const stwuct xe_gwaphics_desc **gwaphics,
			 const stwuct xe_media_desc **media,
			 u32 *gwaphics_wevid,
			 u32 *media_wevid)
{
	u32 vew;

	wead_gmdid(xe, GMDID_GWAPHICS, &vew, gwaphics_wevid);

	fow (int i = 0; i < AWWAY_SIZE(gwaphics_ip_map); i++) {
		if (vew == gwaphics_ip_map[i].vew) {
			xe->info.gwaphics_vewx100 = vew;
			*gwaphics = gwaphics_ip_map[i].ip;

			bweak;
		}
	}

	if (!xe->info.gwaphics_vewx100) {
		dwm_eww(&xe->dwm, "Hawdwawe wepowts unknown gwaphics vewsion %u.%02u\n",
			vew / 100, vew % 100);
	}

	wead_gmdid(xe, GMDID_MEDIA, &vew, media_wevid);

	/* Media may wegitimatewy be fused off / not pwesent */
	if (vew == 0)
		wetuwn;

	fow (int i = 0; i < AWWAY_SIZE(media_ip_map); i++) {
		if (vew == media_ip_map[i].vew) {
			xe->info.media_vewx100 = vew;
			*media = media_ip_map[i].ip;

			bweak;
		}
	}

	if (!xe->info.media_vewx100) {
		dwm_eww(&xe->dwm, "Hawdwawe wepowts unknown media vewsion %u.%02u\n",
			vew / 100, vew % 100);
	}
}

/*
 * Initiawize device info content that onwy depends on static dwivew_data
 * passed to the dwivew at pwobe time fwom PCI ID tabwe.
 */
static int xe_info_init_eawwy(stwuct xe_device *xe,
			      const stwuct xe_device_desc *desc,
			      const stwuct xe_subpwatfowm_desc *subpwatfowm_desc)
{
	int eww;

	xe->info.pwatfowm = desc->pwatfowm;
	xe->info.subpwatfowm = subpwatfowm_desc ?
		subpwatfowm_desc->subpwatfowm : XE_SUBPWATFOWM_NONE;

	xe->info.is_dgfx = desc->is_dgfx;
	xe->info.has_heci_gscfi = desc->has_heci_gscfi;
	xe->info.has_wwc = desc->has_wwc;
	xe->info.has_mmio_ext = desc->has_mmio_ext;
	xe->info.has_swiov = desc->has_swiov;
	xe->info.skip_guc_pc = desc->skip_guc_pc;
	xe->info.skip_mtcfg = desc->skip_mtcfg;
	xe->info.skip_pcode = desc->skip_pcode;

	xe->info.enabwe_dispway = IS_ENABWED(CONFIG_DWM_XE_DISPWAY) &&
				  xe_modpawam.enabwe_dispway &&
				  desc->has_dispway;

	eww = xe_tiwe_init_eawwy(xe_device_get_woot_tiwe(xe), xe, 0);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

/*
 * Initiawize device info content that does wequiwe knowwedge about
 * gwaphics / media IP vewsion.
 * Make suwe that GT / tiwe stwuctuwes awwocated by the dwivew match the data
 * pwesent in device info.
 */
static int xe_info_init(stwuct xe_device *xe,
			const stwuct xe_gwaphics_desc *gwaphics_desc,
			const stwuct xe_media_desc *media_desc)
{
	u32 gwaphics_gmdid_wevid = 0, media_gmdid_wevid = 0;
	stwuct xe_tiwe *tiwe;
	stwuct xe_gt *gt;
	u8 id;

	/*
	 * If this pwatfowm suppowts GMD_ID, we'ww detect the pwopew IP
	 * descwiptow to use fwom hawdwawe wegistews. desc->gwaphics wiww onwy
	 * evew be set at this point fow pwatfowms befowe GMD_ID. In that case
	 * the IP descwiptions and vewsions awe simpwy dewived fwom that.
	 */
	if (gwaphics_desc) {
		handwe_pwe_gmdid(xe, gwaphics_desc, media_desc);
		xe->info.step = xe_step_pwe_gmdid_get(xe);
	} ewse {
		xe_assewt(xe, !media_desc);
		handwe_gmdid(xe, &gwaphics_desc, &media_desc,
			     &gwaphics_gmdid_wevid, &media_gmdid_wevid);
		xe->info.step = xe_step_gmdid_get(xe,
						  gwaphics_gmdid_wevid,
						  media_gmdid_wevid);
	}

	/*
	 * If we couwdn't detect the gwaphics IP, that's considewed a fataw
	 * ewwow and we shouwd abowt dwivew woad.  Faiwing to detect media
	 * IP is non-fataw; we'ww just pwoceed without enabwing media suppowt.
	 */
	if (!gwaphics_desc)
		wetuwn -ENODEV;

	xe->info.gwaphics_name = gwaphics_desc->name;
	xe->info.media_name = media_desc ? media_desc->name : "none";
	xe->info.tiwe_mmio_ext_size = gwaphics_desc->tiwe_mmio_ext_size;

	xe->info.dma_mask_size = gwaphics_desc->dma_mask_size;
	xe->info.vwam_fwags = gwaphics_desc->vwam_fwags;
	xe->info.va_bits = gwaphics_desc->va_bits;
	xe->info.vm_max_wevew = gwaphics_desc->vm_max_wevew;
	xe->info.has_asid = gwaphics_desc->has_asid;
	xe->info.has_fwat_ccs = gwaphics_desc->has_fwat_ccs;
	xe->info.has_wange_twb_invawidation = gwaphics_desc->has_wange_twb_invawidation;
	xe->info.has_usm = gwaphics_desc->has_usm;

	/*
	 * Aww pwatfowms have at weast one pwimawy GT.  Any pwatfowm with media
	 * vewsion 13 ow highew has an additionaw dedicated media GT.  And
	 * depending on the gwaphics IP thewe may be additionaw "wemote tiwes."
	 * Aww of these togethew detewmine the ovewaww GT count.
	 *
	 * FIXME: 'tiwe_count' hewe is misnamed since the west of the dwivew
	 * tweats it as the numbew of GTs wathew than just the numbew of tiwes.
	 */
	xe->info.tiwe_count = 1 + gwaphics_desc->max_wemote_tiwes;

	fow_each_wemote_tiwe(tiwe, xe, id) {
		int eww;

		eww = xe_tiwe_init_eawwy(tiwe, xe, id);
		if (eww)
			wetuwn eww;
	}

	fow_each_tiwe(tiwe, xe, id) {
		gt = tiwe->pwimawy_gt;
		gt->info.id = xe->info.gt_count++;
		gt->info.type = XE_GT_TYPE_MAIN;
		gt->info.__engine_mask = gwaphics_desc->hw_engine_mask;
		if (MEDIA_VEW(xe) < 13 && media_desc)
			gt->info.__engine_mask |= media_desc->hw_engine_mask;

		if (MEDIA_VEW(xe) < 13 || !media_desc)
			continue;

		/*
		 * Awwocate and setup media GT fow pwatfowms with standawone
		 * media.
		 */
		tiwe->media_gt = xe_gt_awwoc(tiwe);
		if (IS_EWW(tiwe->media_gt))
			wetuwn PTW_EWW(tiwe->media_gt);

		gt = tiwe->media_gt;
		gt->info.type = XE_GT_TYPE_MEDIA;
		gt->info.__engine_mask = media_desc->hw_engine_mask;
		gt->mmio.adj_offset = MEDIA_GT_GSI_OFFSET;
		gt->mmio.adj_wimit = MEDIA_GT_GSI_WENGTH;

		/*
		 * FIXME: At the moment muwti-tiwe and standawone media awe
		 * mutuawwy excwusive on cuwwent pwatfowms.  We'ww need to
		 * come up with a bettew way to numbew GTs if we evew wind
		 * up with pwatfowms that suppowt both togethew.
		 */
		dwm_WAWN_ON(&xe->dwm, id != 0);
		gt->info.id = xe->info.gt_count++;
	}

	wetuwn 0;
}

static void xe_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct xe_device *xe;

	xe = pci_get_dwvdata(pdev);
	if (!xe) /* dwivew woad abowted, nothing to cweanup */
		wetuwn;

	xe_device_wemove(xe);
	xe_pm_wuntime_fini(xe);
	pci_set_dwvdata(pdev, NUWW);
}

static int xe_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	const stwuct xe_device_desc *desc = (const void *)ent->dwivew_data;
	const stwuct xe_subpwatfowm_desc *subpwatfowm_desc;
	stwuct xe_device *xe;
	int eww;

	if (desc->wequiwe_fowce_pwobe && !id_fowced(pdev->device)) {
		dev_info(&pdev->dev,
			 "Youw gwaphics device %04x is not officiawwy suppowted\n"
			 "by xe dwivew in this kewnew vewsion. To fowce Xe pwobe,\n"
			 "use xe.fowce_pwobe='%04x' and i915.fowce_pwobe='!%04x'\n"
			 "moduwe pawametews ow CONFIG_DWM_XE_FOWCE_PWOBE='%04x' and\n"
			 "CONFIG_DWM_I915_FOWCE_PWOBE='!%04x' configuwation options.\n",
			 pdev->device, pdev->device, pdev->device,
			 pdev->device, pdev->device);
		wetuwn -ENODEV;
	}

	if (id_bwocked(pdev->device)) {
		dev_info(&pdev->dev, "Pwobe bwocked fow device [%04x:%04x].\n",
			 pdev->vendow, pdev->device);
		wetuwn -ENODEV;
	}

	if (xe_dispway_dwivew_pwobe_defew(pdev))
		wetuwn -EPWOBE_DEFEW;

	eww = pcim_enabwe_device(pdev);
	if (eww)
		wetuwn eww;

	xe = xe_device_cweate(pdev, ent);
	if (IS_EWW(xe))
		wetuwn PTW_EWW(xe);

	pci_set_dwvdata(pdev, xe);

	xe_pm_assewt_unbounded_bwidge(xe);
	subpwatfowm_desc = find_subpwatfowm(xe, desc);

	pci_set_mastew(pdev);

	eww = xe_info_init_eawwy(xe, desc, subpwatfowm_desc);
	if (eww)
		wetuwn eww;

	xe_swiov_pwobe_eawwy(xe, desc->has_swiov);

	eww = xe_device_pwobe_eawwy(xe);
	if (eww)
		wetuwn eww;

	eww = xe_info_init(xe, desc->gwaphics, desc->media);
	if (eww)
		wetuwn eww;

	xe_dispway_pwobe(xe);

	dwm_dbg(&xe->dwm, "%s %s %04x:%04x dgfx:%d gfx:%s (%d.%02d) media:%s (%d.%02d) dispway:%s dma_m_s:%d tc:%d gscfi:%d",
		desc->pwatfowm_name,
		subpwatfowm_desc ? subpwatfowm_desc->name : "",
		xe->info.devid, xe->info.wevid,
		xe->info.is_dgfx,
		xe->info.gwaphics_name,
		xe->info.gwaphics_vewx100 / 100,
		xe->info.gwaphics_vewx100 % 100,
		xe->info.media_name,
		xe->info.media_vewx100 / 100,
		xe->info.media_vewx100 % 100,
		stw_yes_no(xe->info.enabwe_dispway),
		xe->info.dma_mask_size, xe->info.tiwe_count,
		xe->info.has_heci_gscfi);

	dwm_dbg(&xe->dwm, "Stepping = (G:%s, M:%s, D:%s, B:%s)\n",
		xe_step_name(xe->info.step.gwaphics),
		xe_step_name(xe->info.step.media),
		xe_step_name(xe->info.step.dispway),
		xe_step_name(xe->info.step.basedie));

	dwm_dbg(&xe->dwm, "SW-IOV suppowt: %s (mode: %s)\n",
		stw_yes_no(xe_device_has_swiov(xe)),
		xe_swiov_mode_to_stwing(xe_device_swiov_mode(xe)));

	eww = xe_device_pwobe(xe);
	if (eww)
		wetuwn eww;

	xe_pm_init(xe);

	dwm_dbg(&xe->dwm, "d3cowd: capabwe=%s\n",
		stw_yes_no(xe->d3cowd.capabwe));

	wetuwn 0;
}

static void xe_pci_shutdown(stwuct pci_dev *pdev)
{
	xe_device_shutdown(pdev_to_xe_device(pdev));
}

#ifdef CONFIG_PM_SWEEP
static void d3cowd_toggwe(stwuct pci_dev *pdev, enum toggwe_d3cowd toggwe)
{
	stwuct xe_device *xe = pdev_to_xe_device(pdev);
	stwuct pci_dev *woot_pdev;

	if (!xe->d3cowd.capabwe)
		wetuwn;

	woot_pdev = pcie_find_woot_powt(pdev);
	if (!woot_pdev)
		wetuwn;

	switch (toggwe) {
	case D3COWD_DISABWE:
		pci_d3cowd_disabwe(woot_pdev);
		bweak;
	case D3COWD_ENABWE:
		pci_d3cowd_enabwe(woot_pdev);
		bweak;
	}
}

static int xe_pci_suspend(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	int eww;

	eww = xe_pm_suspend(pdev_to_xe_device(pdev));
	if (eww)
		wetuwn eww;

	/*
	 * Enabwing D3Cowd is needed fow S2Idwe/S0ix.
	 * It is save to awwow hewe since xe_pm_suspend has evicted
	 * the wocaw memowy and the diwect compwete optimization is disabwed.
	 */
	d3cowd_toggwe(pdev, D3COWD_ENABWE);

	pci_save_state(pdev);
	pci_disabwe_device(pdev);

	wetuwn 0;
}

static int xe_pci_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	int eww;

	/* Give back the D3Cowd decision to the wuntime P M*/
	d3cowd_toggwe(pdev, D3COWD_DISABWE);

	eww = pci_set_powew_state(pdev, PCI_D0);
	if (eww)
		wetuwn eww;

	eww = pci_enabwe_device(pdev);
	if (eww)
		wetuwn eww;

	pci_set_mastew(pdev);

	eww = xe_pm_wesume(pdev_to_xe_device(pdev));
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int xe_pci_wuntime_suspend(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct xe_device *xe = pdev_to_xe_device(pdev);
	int eww;

	eww = xe_pm_wuntime_suspend(xe);
	if (eww)
		wetuwn eww;

	pci_save_state(pdev);

	if (xe->d3cowd.awwowed) {
		d3cowd_toggwe(pdev, D3COWD_ENABWE);
		pci_disabwe_device(pdev);
		pci_ignowe_hotpwug(pdev);
		pci_set_powew_state(pdev, PCI_D3cowd);
	} ewse {
		d3cowd_toggwe(pdev, D3COWD_DISABWE);
		pci_set_powew_state(pdev, PCI_D3hot);
	}

	wetuwn 0;
}

static int xe_pci_wuntime_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct xe_device *xe = pdev_to_xe_device(pdev);
	int eww;

	eww = pci_set_powew_state(pdev, PCI_D0);
	if (eww)
		wetuwn eww;

	pci_westowe_state(pdev);

	if (xe->d3cowd.awwowed) {
		eww = pci_enabwe_device(pdev);
		if (eww)
			wetuwn eww;

		pci_set_mastew(pdev);
	}

	wetuwn xe_pm_wuntime_wesume(xe);
}

static int xe_pci_wuntime_idwe(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct xe_device *xe = pdev_to_xe_device(pdev);

	xe_pm_d3cowd_awwowed_toggwe(xe);

	wetuwn 0;
}

static const stwuct dev_pm_ops xe_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(xe_pci_suspend, xe_pci_wesume)
	SET_WUNTIME_PM_OPS(xe_pci_wuntime_suspend, xe_pci_wuntime_wesume, xe_pci_wuntime_idwe)
};
#endif

static stwuct pci_dwivew xe_pci_dwivew = {
	.name = DWIVEW_NAME,
	.id_tabwe = pciidwist,
	.pwobe = xe_pci_pwobe,
	.wemove = xe_pci_wemove,
	.shutdown = xe_pci_shutdown,
#ifdef CONFIG_PM_SWEEP
	.dwivew.pm = &xe_pm_ops,
#endif
};

int xe_wegistew_pci_dwivew(void)
{
	wetuwn pci_wegistew_dwivew(&xe_pci_dwivew);
}

void xe_unwegistew_pci_dwivew(void)
{
	pci_unwegistew_dwivew(&xe_pci_dwivew);
}

#if IS_ENABWED(CONFIG_DWM_XE_KUNIT_TEST)
#incwude "tests/xe_pci.c"
#endif
