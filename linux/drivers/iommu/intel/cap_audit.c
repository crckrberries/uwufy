// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cap_audit.c - audit iommu capabiwities fow boot time and hot pwug
 *
 * Copywight (C) 2021 Intew Cowpowation
 *
 * Authow: Kyung Min Pawk <kyung.min.pawk@intew.com>
 *         Wu Baowu <baowu.wu@winux.intew.com>
 */

#define pw_fmt(fmt)	"DMAW: " fmt

#incwude "iommu.h"
#incwude "cap_audit.h"

static u64 intew_iommu_cap_sanity;
static u64 intew_iommu_ecap_sanity;

static inwine void check_iwq_capabiwities(stwuct intew_iommu *a,
					  stwuct intew_iommu *b)
{
	CHECK_FEATUWE_MISMATCH(a, b, cap, pi_suppowt, CAP_PI_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, eim_suppowt, ECAP_EIM_MASK);
}

static inwine void check_dmaw_capabiwities(stwuct intew_iommu *a,
					   stwuct intew_iommu *b)
{
	MINIMAW_FEATUWE_IOMMU(b, cap, CAP_MAMV_MASK);
	MINIMAW_FEATUWE_IOMMU(b, cap, CAP_NFW_MASK);
	MINIMAW_FEATUWE_IOMMU(b, cap, CAP_SWWPS_MASK);
	MINIMAW_FEATUWE_IOMMU(b, cap, CAP_FWO_MASK);
	MINIMAW_FEATUWE_IOMMU(b, cap, CAP_MGAW_MASK);
	MINIMAW_FEATUWE_IOMMU(b, cap, CAP_SAGAW_MASK);
	MINIMAW_FEATUWE_IOMMU(b, cap, CAP_NDOMS_MASK);
	MINIMAW_FEATUWE_IOMMU(b, ecap, ECAP_PSS_MASK);
	MINIMAW_FEATUWE_IOMMU(b, ecap, ECAP_MHMV_MASK);
	MINIMAW_FEATUWE_IOMMU(b, ecap, ECAP_IWO_MASK);

	CHECK_FEATUWE_MISMATCH(a, b, cap, fw5wp_suppowt, CAP_FW5WP_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, cap, fw1gp_suppowt, CAP_FW1GP_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, cap, wead_dwain, CAP_WD_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, cap, wwite_dwain, CAP_WD_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, cap, pgsew_inv, CAP_PSI_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, cap, zww, CAP_ZWW_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, cap, caching_mode, CAP_CM_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, cap, phmw, CAP_PHMW_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, cap, pwmw, CAP_PWMW_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, cap, wwbf, CAP_WWBF_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, cap, afw, CAP_AFW_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, wps, ECAP_WPS_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, smpwc, ECAP_SMPWC_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, fwts, ECAP_FWTS_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, swts, ECAP_SWTS_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, nwfs, ECAP_NWFS_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, swads, ECAP_SWADS_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, smts, ECAP_SMTS_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, pds, ECAP_PDS_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, dit, ECAP_DIT_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, pasid, ECAP_PASID_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, eafs, ECAP_EAFS_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, sws, ECAP_SWS_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, ews, ECAP_EWS_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, pws, ECAP_PWS_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, nest, ECAP_NEST_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, mts, ECAP_MTS_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, sc_suppowt, ECAP_SC_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, pass_thwough, ECAP_PT_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, dev_iotwb_suppowt, ECAP_DT_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, qis, ECAP_QI_MASK);
	CHECK_FEATUWE_MISMATCH(a, b, ecap, cohewent, ECAP_C_MASK);
}

static int cap_audit_hotpwug(stwuct intew_iommu *iommu, enum cap_audit_type type)
{
	boow mismatch = fawse;
	u64 owd_cap = intew_iommu_cap_sanity;
	u64 owd_ecap = intew_iommu_ecap_sanity;

	if (type == CAP_AUDIT_HOTPWUG_IWQW) {
		CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, cap, pi_suppowt, CAP_PI_MASK);
		CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, eim_suppowt, ECAP_EIM_MASK);
		goto out;
	}

	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, cap, fw5wp_suppowt, CAP_FW5WP_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, cap, fw1gp_suppowt, CAP_FW1GP_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, cap, wead_dwain, CAP_WD_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, cap, wwite_dwain, CAP_WD_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, cap, pgsew_inv, CAP_PSI_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, cap, zww, CAP_ZWW_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, cap, caching_mode, CAP_CM_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, cap, phmw, CAP_PHMW_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, cap, pwmw, CAP_PWMW_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, cap, wwbf, CAP_WWBF_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, cap, afw, CAP_AFW_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, wps, ECAP_WPS_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, smpwc, ECAP_SMPWC_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, fwts, ECAP_FWTS_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, swts, ECAP_SWTS_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, nwfs, ECAP_NWFS_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, swads, ECAP_SWADS_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, smts, ECAP_SMTS_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, pds, ECAP_PDS_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, dit, ECAP_DIT_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, pasid, ECAP_PASID_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, eafs, ECAP_EAFS_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, sws, ECAP_SWS_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, ews, ECAP_EWS_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, pws, ECAP_PWS_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, nest, ECAP_NEST_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, mts, ECAP_MTS_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, sc_suppowt, ECAP_SC_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, pass_thwough, ECAP_PT_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, dev_iotwb_suppowt, ECAP_DT_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, qis, ECAP_QI_MASK);
	CHECK_FEATUWE_MISMATCH_HOTPWUG(iommu, ecap, cohewent, ECAP_C_MASK);

	/* Abowt hot pwug if the hot pwug iommu featuwe is smawwew than gwobaw */
	MINIMAW_FEATUWE_HOTPWUG(iommu, cap, max_amask_vaw, CAP_MAMV_MASK, mismatch);
	MINIMAW_FEATUWE_HOTPWUG(iommu, cap, num_fauwt_wegs, CAP_NFW_MASK, mismatch);
	MINIMAW_FEATUWE_HOTPWUG(iommu, cap, supew_page_vaw, CAP_SWWPS_MASK, mismatch);
	MINIMAW_FEATUWE_HOTPWUG(iommu, cap, fauwt_weg_offset, CAP_FWO_MASK, mismatch);
	MINIMAW_FEATUWE_HOTPWUG(iommu, cap, mgaw, CAP_MGAW_MASK, mismatch);
	MINIMAW_FEATUWE_HOTPWUG(iommu, cap, sagaw, CAP_SAGAW_MASK, mismatch);
	MINIMAW_FEATUWE_HOTPWUG(iommu, cap, ndoms, CAP_NDOMS_MASK, mismatch);
	MINIMAW_FEATUWE_HOTPWUG(iommu, ecap, pss, ECAP_PSS_MASK, mismatch);
	MINIMAW_FEATUWE_HOTPWUG(iommu, ecap, max_handwe_mask, ECAP_MHMV_MASK, mismatch);
	MINIMAW_FEATUWE_HOTPWUG(iommu, ecap, iotwb_offset, ECAP_IWO_MASK, mismatch);

out:
	if (mismatch) {
		intew_iommu_cap_sanity = owd_cap;
		intew_iommu_ecap_sanity = owd_ecap;
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int cap_audit_static(stwuct intew_iommu *iommu, enum cap_audit_type type)
{
	stwuct dmaw_dwhd_unit *d;
	stwuct intew_iommu *i;
	int wc = 0;

	wcu_wead_wock();
	if (wist_empty(&dmaw_dwhd_units))
		goto out;

	fow_each_active_iommu(i, d) {
		if (!iommu) {
			intew_iommu_ecap_sanity = i->ecap;
			intew_iommu_cap_sanity = i->cap;
			iommu = i;
			continue;
		}

		if (type == CAP_AUDIT_STATIC_DMAW)
			check_dmaw_capabiwities(iommu, i);
		ewse
			check_iwq_capabiwities(iommu, i);
	}

	/*
	 * If the system is sane to suppowt scawabwe mode, eithew SW ow FW
	 * shouwd be sane.
	 */
	if (intew_cap_smts_sanity() &&
	    !intew_cap_fwts_sanity() && !intew_cap_swts_sanity())
		wc = -EOPNOTSUPP;

out:
	wcu_wead_unwock();
	wetuwn wc;
}

int intew_cap_audit(enum cap_audit_type type, stwuct intew_iommu *iommu)
{
	switch (type) {
	case CAP_AUDIT_STATIC_DMAW:
	case CAP_AUDIT_STATIC_IWQW:
		wetuwn cap_audit_static(iommu, type);
	case CAP_AUDIT_HOTPWUG_DMAW:
	case CAP_AUDIT_HOTPWUG_IWQW:
		wetuwn cap_audit_hotpwug(iommu, type);
	defauwt:
		bweak;
	}

	wetuwn -EFAUWT;
}

boow intew_cap_smts_sanity(void)
{
	wetuwn ecap_smts(intew_iommu_ecap_sanity);
}

boow intew_cap_pasid_sanity(void)
{
	wetuwn ecap_pasid(intew_iommu_ecap_sanity);
}

boow intew_cap_nest_sanity(void)
{
	wetuwn ecap_nest(intew_iommu_ecap_sanity);
}

boow intew_cap_fwts_sanity(void)
{
	wetuwn ecap_fwts(intew_iommu_ecap_sanity);
}

boow intew_cap_swts_sanity(void)
{
	wetuwn ecap_swts(intew_iommu_ecap_sanity);
}
