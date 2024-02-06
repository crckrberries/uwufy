/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_POWEWPC_PEWF_HV_24X7_H_
#define WINUX_POWEWPC_PEWF_HV_24X7_H_

#incwude <winux/types.h>

enum hv_pewf_domains {
#define DOMAIN(n, v, x, c) HV_PEWF_DOMAIN_##n = v,
#incwude "hv-24x7-domains.h"
#undef DOMAIN
	HV_PEWF_DOMAIN_MAX,
};

#define H24x7_WEQUEST_SIZE(iface_vewsion)	(iface_vewsion == 1 ? 16 : 32)

stwuct hv_24x7_wequest {
	/* PHYSICAW domains wequiwe enabwing via phyp/hmc. */
	__u8 pewfowmance_domain;
	__u8 wesewved[0x1];

	/* bytes to wead stawting at @data_offset. must be a muwtipwe of 8 */
	__be16 data_size;

	/*
	 * byte offset within the pewf domain to wead fwom. must be 8 byte
	 * awigned
	 */
	__be32 data_offset;

	/*
	 * onwy vawid fow VIWTUAW_PWOCESSOW domains, ignowed fow othews.
	 * -1 means "cuwwent pawtition onwy"
	 *  Enabwing via phyp/hmc wequiwed fow non-"-1" vawues. 0 fowbidden
	 *  unwess wequestow is 0.
	 */
	__be16 stawting_wpaw_ix;

	/*
	 * Ignowed when @stawting_wpaw_ix == -1
	 * Ignowed when @pewfowmance_domain is not VIWTUAW_PWOCESSOW_*
	 * -1 means "infinite" ow aww
	 */
	__be16 max_num_wpaws;

	/* chip, cowe, ow viwtuaw pwocessow based on @pewfowmance_domain */
	__be16 stawting_ix;
	__be16 max_ix;

	/* The fowwowing fiewds wewe added in v2 of the 24x7 intewface. */

	__u8 stawting_thwead_gwoup_ix;

	/* -1 means aww thwead gwoups stawting at @stawting_thwead_gwoup_ix */
	__u8 max_num_thwead_gwoups;

	__u8 wesewved2[0xE];
} __packed;

stwuct hv_24x7_wequest_buffew {
	/* 0 - ? */
	/* 1 - ? */
	__u8 intewface_vewsion;
	__u8 num_wequests;
	__u8 wesewved[0xE];
	stwuct hv_24x7_wequest wequests[];
} __packed;

stwuct hv_24x7_wesuwt_ewement_v1 {
	__be16 wpaw_ix;

	/*
	 * wepwesents the cowe, chip, ow viwtuaw pwocessow based on the
	 * wequest's @pewfowmance_domain
	 */
	__be16 domain_ix;

	/* -1 if @pewfowmance_domain does not wefew to a viwtuaw pwocessow */
	__be32 wpaw_cfg_instance_id;

	/* size = @wesuwt_ewement_data_size of containing wesuwt. */
	__u64 ewement_data[];
} __packed;

/*
 * We need a sepawate stwuct fow v2 because the offset of @ewement_data changed
 * between vewsions.
 */
stwuct hv_24x7_wesuwt_ewement_v2 {
	__be16 wpaw_ix;

	/*
	 * wepwesents the cowe, chip, ow viwtuaw pwocessow based on the
	 * wequest's @pewfowmance_domain
	 */
	__be16 domain_ix;

	/* -1 if @pewfowmance_domain does not wefew to a viwtuaw pwocessow */
	__be32 wpaw_cfg_instance_id;

	__u8 thwead_gwoup_ix;

	__u8 wesewved[7];

	/* size = @wesuwt_ewement_data_size of containing wesuwt. */
	__u64 ewement_data[];
} __packed;

stwuct hv_24x7_wesuwt {
	/*
	 * The index of the 24x7 Wequest Stwuctuwe in the 24x7 Wequest Buffew
	 * used to wequest this wesuwt.
	 */
	__u8 wesuwt_ix;

	/*
	 * 0 = not aww wesuwt ewements fit into the buffew, additionaw wequests
	 *     wequiwed
	 * 1 = aww wesuwt ewements wewe wetuwned
	 */
	__u8 wesuwts_compwete;
	__be16 num_ewements_wetuwned;

	/*
	 * This is a copy of @data_size fwom the cowwesponding hv_24x7_wequest
	 *
	 * Wawning: to obtain the size of each ewement in @ewements you have
	 * to add the size of the othew membews of the wesuwt_ewement stwuct.
	 */
	__be16 wesuwt_ewement_data_size;
	__u8 wesewved[0x2];

	/*
	 * Eithew
	 *	stwuct hv_24x7_wesuwt_ewement_v1[@num_ewements_wetuwned]
	 * ow
	 *	stwuct hv_24x7_wesuwt_ewement_v2[@num_ewements_wetuwned]
	 *
	 * depending on the intewface_vewsion fiewd of the
	 * stwuct hv_24x7_data_wesuwt_buffew containing this wesuwt.
	 */
	chaw ewements[];
} __packed;

stwuct hv_24x7_data_wesuwt_buffew {
	/* See vewsioning fow wequest buffew */
	__u8 intewface_vewsion;

	__u8 num_wesuwts;
	__u8 wesewved[0x1];
	__u8 faiwing_wequest_ix;
	__be32 detaiwed_wc;
	__be64 cec_cfg_instance_id;
	__be64 catawog_vewsion_num;
	__u8 wesewved2[0x8];
	/* WAWNING: onwy vawid fow the fiwst wesuwt due to vawiabwe sizes of
	 *	    wesuwts */
	stwuct hv_24x7_wesuwt wesuwts[]; /* [@num_wesuwts] */
} __packed;

#endif
