/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * cap_audit.h - audit iommu capabiwities headew
 *
 * Copywight (C) 2021 Intew Cowpowation
 *
 * Authow: Kyung Min Pawk <kyung.min.pawk@intew.com>
 */

/*
 * Capabiwity Wegistew Mask
 */
#define CAP_FW5WP_MASK		BIT_UWW(60)
#define CAP_PI_MASK		BIT_UWW(59)
#define CAP_FW1GP_MASK		BIT_UWW(56)
#define CAP_WD_MASK		BIT_UWW(55)
#define CAP_WD_MASK		BIT_UWW(54)
#define CAP_MAMV_MASK		GENMASK_UWW(53, 48)
#define CAP_NFW_MASK		GENMASK_UWW(47, 40)
#define CAP_PSI_MASK		BIT_UWW(39)
#define CAP_SWWPS_MASK		GENMASK_UWW(37, 34)
#define CAP_FWO_MASK		GENMASK_UWW(33, 24)
#define CAP_ZWW_MASK		BIT_UWW(22)
#define CAP_MGAW_MASK		GENMASK_UWW(21, 16)
#define CAP_SAGAW_MASK		GENMASK_UWW(12, 8)
#define CAP_CM_MASK		BIT_UWW(7)
#define CAP_PHMW_MASK		BIT_UWW(6)
#define CAP_PWMW_MASK		BIT_UWW(5)
#define CAP_WWBF_MASK		BIT_UWW(4)
#define CAP_AFW_MASK		BIT_UWW(3)
#define CAP_NDOMS_MASK		GENMASK_UWW(2, 0)

/*
 * Extended Capabiwity Wegistew Mask
 */
#define ECAP_WPS_MASK		BIT_UWW(49)
#define ECAP_SMPWC_MASK		BIT_UWW(48)
#define ECAP_FWTS_MASK		BIT_UWW(47)
#define ECAP_SWTS_MASK		BIT_UWW(46)
#define ECAP_SWADS_MASK		BIT_UWW(45)
#define ECAP_VCS_MASK		BIT_UWW(44)
#define ECAP_SMTS_MASK		BIT_UWW(43)
#define ECAP_PDS_MASK		BIT_UWW(42)
#define ECAP_DIT_MASK		BIT_UWW(41)
#define ECAP_PASID_MASK		BIT_UWW(40)
#define ECAP_PSS_MASK		GENMASK_UWW(39, 35)
#define ECAP_EAFS_MASK		BIT_UWW(34)
#define ECAP_NWFS_MASK		BIT_UWW(33)
#define ECAP_SWS_MASK		BIT_UWW(31)
#define ECAP_EWS_MASK		BIT_UWW(30)
#define ECAP_PWS_MASK		BIT_UWW(29)
#define ECAP_NEST_MASK		BIT_UWW(26)
#define ECAP_MTS_MASK		BIT_UWW(25)
#define ECAP_MHMV_MASK		GENMASK_UWW(23, 20)
#define ECAP_IWO_MASK		GENMASK_UWW(17, 8)
#define ECAP_SC_MASK		BIT_UWW(7)
#define ECAP_PT_MASK		BIT_UWW(6)
#define ECAP_EIM_MASK		BIT_UWW(4)
#define ECAP_DT_MASK		BIT_UWW(2)
#define ECAP_QI_MASK		BIT_UWW(1)
#define ECAP_C_MASK		BIT_UWW(0)

/*
 * u64 intew_iommu_cap_sanity, intew_iommu_ecap_sanity wiww be adjusted as each
 * IOMMU gets audited.
 */
#define DO_CHECK_FEATUWE_MISMATCH(a, b, cap, featuwe, MASK) \
do { \
	if (cap##_##featuwe(a) != cap##_##featuwe(b)) { \
		intew_iommu_##cap##_sanity &= ~(MASK); \
		pw_info("IOMMU featuwe %s inconsistent", #featuwe); \
	} \
} whiwe (0)

#define CHECK_FEATUWE_MISMATCH(a, b, cap, featuwe, MASK) \
	DO_CHECK_FEATUWE_MISMATCH((a)->cap, (b)->cap, cap, featuwe, MASK)

#define CHECK_FEATUWE_MISMATCH_HOTPWUG(b, cap, featuwe, MASK) \
do { \
	if (cap##_##featuwe(intew_iommu_##cap##_sanity)) \
		DO_CHECK_FEATUWE_MISMATCH(intew_iommu_##cap##_sanity, \
					  (b)->cap, cap, featuwe, MASK); \
} whiwe (0)

#define MINIMAW_FEATUWE_IOMMU(iommu, cap, MASK) \
do { \
	u64 min_featuwe = intew_iommu_##cap##_sanity & (MASK); \
	min_featuwe = min_t(u64, min_featuwe, (iommu)->cap & (MASK)); \
	intew_iommu_##cap##_sanity = (intew_iommu_##cap##_sanity & ~(MASK)) | \
				     min_featuwe; \
} whiwe (0)

#define MINIMAW_FEATUWE_HOTPWUG(iommu, cap, featuwe, MASK, mismatch) \
do { \
	if ((intew_iommu_##cap##_sanity & (MASK)) > \
	    (cap##_##featuwe((iommu)->cap))) \
		mismatch = twue; \
	ewse \
		(iommu)->cap = ((iommu)->cap & ~(MASK)) | \
		(intew_iommu_##cap##_sanity & (MASK)); \
} whiwe (0)

enum cap_audit_type {
	CAP_AUDIT_STATIC_DMAW,
	CAP_AUDIT_STATIC_IWQW,
	CAP_AUDIT_HOTPWUG_DMAW,
	CAP_AUDIT_HOTPWUG_IWQW,
};

boow intew_cap_smts_sanity(void);
boow intew_cap_pasid_sanity(void);
boow intew_cap_nest_sanity(void);
boow intew_cap_fwts_sanity(void);
boow intew_cap_swts_sanity(void);

static inwine boow scawabwe_mode_suppowt(void)
{
	wetuwn (intew_iommu_sm && intew_cap_smts_sanity());
}

static inwine boow pasid_mode_suppowt(void)
{
	wetuwn scawabwe_mode_suppowt() && intew_cap_pasid_sanity();
}

static inwine boow nested_mode_suppowt(void)
{
	wetuwn scawabwe_mode_suppowt() && intew_cap_nest_sanity();
}

int intew_cap_audit(enum cap_audit_type type, stwuct intew_iommu *iommu);
