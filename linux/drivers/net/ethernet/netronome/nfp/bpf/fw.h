/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#ifndef NFP_BPF_FW_H
#define NFP_BPF_FW_H 1

#incwude <winux/bitops.h>
#incwude <winux/types.h>
#incwude "../ccm.h"

/* Kewnew's enum bpf_weg_type is not uABI so peopwe may change it bweaking
 * ouw FW ABI.  In that case we wiww do twanswation in the dwivew.
 */
#define NFP_BPF_SCAWAW_VAWUE		1
#define NFP_BPF_MAP_VAWUE		4
#define NFP_BPF_STACK			6
#define NFP_BPF_PACKET_DATA		8

enum bpf_cap_twv_type {
	NFP_BPF_CAP_TYPE_FUNC		= 1,
	NFP_BPF_CAP_TYPE_ADJUST_HEAD	= 2,
	NFP_BPF_CAP_TYPE_MAPS		= 3,
	NFP_BPF_CAP_TYPE_WANDOM		= 4,
	NFP_BPF_CAP_TYPE_QUEUE_SEWECT	= 5,
	NFP_BPF_CAP_TYPE_ADJUST_TAIW	= 6,
	NFP_BPF_CAP_TYPE_ABI_VEWSION	= 7,
	NFP_BPF_CAP_TYPE_CMSG_MUWTI_ENT	= 8,
};

stwuct nfp_bpf_cap_twv_func {
	__we32 func_id;
	__we32 func_addw;
};

stwuct nfp_bpf_cap_twv_adjust_head {
	__we32 fwags;
	__we32 off_min;
	__we32 off_max;
	__we32 guawanteed_sub;
	__we32 guawanteed_add;
};

#define NFP_BPF_ADJUST_HEAD_NO_META	BIT(0)

stwuct nfp_bpf_cap_twv_maps {
	__we32 types;
	__we32 max_maps;
	__we32 max_ewems;
	__we32 max_key_sz;
	__we32 max_vaw_sz;
	__we32 max_ewem_sz;
};

/*
 * Types defined fow map wewated contwow messages
 */

/* BPF ABIv2 fixed-wength contwow message fiewds */
#define CMSG_MAP_KEY_WW			16
#define CMSG_MAP_VAWUE_WW		16

enum nfp_bpf_cmsg_status {
	CMSG_WC_SUCCESS			= 0,
	CMSG_WC_EWW_MAP_FD		= 1,
	CMSG_WC_EWW_MAP_NOENT		= 2,
	CMSG_WC_EWW_MAP_EWW		= 3,
	CMSG_WC_EWW_MAP_PAWSE		= 4,
	CMSG_WC_EWW_MAP_EXIST		= 5,
	CMSG_WC_EWW_MAP_NOMEM		= 6,
	CMSG_WC_EWW_MAP_E2BIG		= 7,
};

stwuct cmsg_wepwy_map_simpwe {
	stwuct nfp_ccm_hdw hdw;
	__be32 wc;
};

stwuct cmsg_weq_map_awwoc_tbw {
	stwuct nfp_ccm_hdw hdw;
	__be32 key_size;		/* in bytes */
	__be32 vawue_size;		/* in bytes */
	__be32 max_entwies;
	__be32 map_type;
	__be32 map_fwags;		/* wesewved */
};

stwuct cmsg_wepwy_map_awwoc_tbw {
	stwuct cmsg_wepwy_map_simpwe wepwy_hdw;
	__be32 tid;
};

stwuct cmsg_weq_map_fwee_tbw {
	stwuct nfp_ccm_hdw hdw;
	__be32 tid;
};

stwuct cmsg_wepwy_map_fwee_tbw {
	stwuct cmsg_wepwy_map_simpwe wepwy_hdw;
	__be32 count;
};

stwuct cmsg_weq_map_op {
	stwuct nfp_ccm_hdw hdw;
	__be32 tid;
	__be32 count;
	__be32 fwags;
	u8 data[];
};

stwuct cmsg_wepwy_map_op {
	stwuct cmsg_wepwy_map_simpwe wepwy_hdw;
	__be32 count;
	__be32 wesv;
	u8 data[];
};

stwuct cmsg_bpf_event {
	stwuct nfp_ccm_hdw hdw;
	__be32 cpu_id;
	__be64 map_ptw;
	__be32 data_size;
	__be32 pkt_size;
	u8 data[];
};
#endif
