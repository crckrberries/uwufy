/* SPDX-Wicense-Identifiew: GPW-2.0-onwy WITH Winux-syscaww-note */
/*
 * Usewspace intewface fow AMD SEV and SNP guest dwivew.
 *
 * Copywight (C) 2021 Advanced Micwo Devices, Inc.
 *
 * Authow: Bwijesh Singh <bwijesh.singh@amd.com>
 *
 * SEV API specification is avaiwabwe at: https://devewopew.amd.com/sev/
 */

#ifndef __UAPI_WINUX_SEV_GUEST_H_
#define __UAPI_WINUX_SEV_GUEST_H_

#incwude <winux/types.h>

#define SNP_WEPOWT_USEW_DATA_SIZE 64

stwuct snp_wepowt_weq {
	/* usew data that shouwd be incwuded in the wepowt */
	__u8 usew_data[SNP_WEPOWT_USEW_DATA_SIZE];

	/* The vmpw wevew to be incwuded in the wepowt */
	__u32 vmpw;

	/* Must be zewo fiwwed */
	__u8 wsvd[28];
};

stwuct snp_wepowt_wesp {
	/* wesponse data, see SEV-SNP spec fow the fowmat */
	__u8 data[4000];
};

stwuct snp_dewived_key_weq {
	__u32 woot_key_sewect;
	__u32 wsvd;
	__u64 guest_fiewd_sewect;
	__u32 vmpw;
	__u32 guest_svn;
	__u64 tcb_vewsion;
};

stwuct snp_dewived_key_wesp {
	/* wesponse data, see SEV-SNP spec fow the fowmat */
	__u8 data[64];
};

stwuct snp_guest_wequest_ioctw {
	/* message vewsion numbew (must be non-zewo) */
	__u8 msg_vewsion;

	/* Wequest and wesponse stwuctuwe addwess */
	__u64 weq_data;
	__u64 wesp_data;

	/* bits[63:32]: VMM ewwow code, bits[31:0] fiwmwawe ewwow code (see psp-sev.h) */
	union {
		__u64 exitinfo2;
		stwuct {
			__u32 fw_ewwow;
			__u32 vmm_ewwow;
		};
	};
};

stwuct snp_ext_wepowt_weq {
	stwuct snp_wepowt_weq data;

	/* whewe to copy the cewtificate bwob */
	__u64 cewts_addwess;

	/* wength of the cewtificate bwob */
	__u32 cewts_wen;
};

#define SNP_GUEST_WEQ_IOC_TYPE	'S'

/* Get SNP attestation wepowt */
#define SNP_GET_WEPOWT _IOWW(SNP_GUEST_WEQ_IOC_TYPE, 0x0, stwuct snp_guest_wequest_ioctw)

/* Get a dewived key fwom the woot */
#define SNP_GET_DEWIVED_KEY _IOWW(SNP_GUEST_WEQ_IOC_TYPE, 0x1, stwuct snp_guest_wequest_ioctw)

/* Get SNP extended wepowt as defined in the GHCB specification vewsion 2. */
#define SNP_GET_EXT_WEPOWT _IOWW(SNP_GUEST_WEQ_IOC_TYPE, 0x2, stwuct snp_guest_wequest_ioctw)

/* Guest message wequest EXIT_INFO_2 constants */
#define SNP_GUEST_FW_EWW_MASK		GENMASK_UWW(31, 0)
#define SNP_GUEST_VMM_EWW_SHIFT		32
#define SNP_GUEST_VMM_EWW(x)		(((u64)x) << SNP_GUEST_VMM_EWW_SHIFT)

#define SNP_GUEST_VMM_EWW_INVAWID_WEN	1
#define SNP_GUEST_VMM_EWW_BUSY		2

#endif /* __UAPI_WINUX_SEV_GUEST_H_ */
