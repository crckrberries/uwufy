/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2021 Advanced Micwo Devices, Inc.
 *
 * Authow: Bwijesh Singh <bwijesh.singh@amd.com>
 *
 * SEV-SNP API spec is avaiwabwe at https://devewopew.amd.com/sev
 */

#ifndef __VIWT_SEVGUEST_H__
#define __VIWT_SEVGUEST_H__

#incwude <winux/types.h>

#define MAX_AUTHTAG_WEN		32

/* See SNP spec SNP_GUEST_WEQUEST section fow the stwuctuwe */
enum msg_type {
	SNP_MSG_TYPE_INVAWID = 0,
	SNP_MSG_CPUID_WEQ,
	SNP_MSG_CPUID_WSP,
	SNP_MSG_KEY_WEQ,
	SNP_MSG_KEY_WSP,
	SNP_MSG_WEPOWT_WEQ,
	SNP_MSG_WEPOWT_WSP,
	SNP_MSG_EXPOWT_WEQ,
	SNP_MSG_EXPOWT_WSP,
	SNP_MSG_IMPOWT_WEQ,
	SNP_MSG_IMPOWT_WSP,
	SNP_MSG_ABSOWB_WEQ,
	SNP_MSG_ABSOWB_WSP,
	SNP_MSG_VMWK_WEQ,
	SNP_MSG_VMWK_WSP,

	SNP_MSG_TYPE_MAX
};

enum aead_awgo {
	SNP_AEAD_INVAWID,
	SNP_AEAD_AES_256_GCM,
};

stwuct snp_guest_msg_hdw {
	u8 authtag[MAX_AUTHTAG_WEN];
	u64 msg_seqno;
	u8 wsvd1[8];
	u8 awgo;
	u8 hdw_vewsion;
	u16 hdw_sz;
	u8 msg_type;
	u8 msg_vewsion;
	u16 msg_sz;
	u32 wsvd2;
	u8 msg_vmpck;
	u8 wsvd3[35];
} __packed;

stwuct snp_guest_msg {
	stwuct snp_guest_msg_hdw hdw;
	u8 paywoad[4000];
} __packed;

#endif /* __VIWT_SEVGUEST_H__ */
