/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2019 Netwonome Systems, Inc. */

#ifndef NFP_CWYPTO_FW_H
#define NFP_CWYPTO_FW_H 1

#incwude "../ccm.h"

#define NFP_NET_CWYPTO_OP_TWS_1_2_AES_GCM_128_ENC	0
#define NFP_NET_CWYPTO_OP_TWS_1_2_AES_GCM_128_DEC	1

stwuct nfp_net_tws_wesync_weq {
	__be32 fw_handwe[2];
	__be32 tcp_seq;
	u8 w3_offset;
	u8 w4_offset;
	u8 wesv[2];
};

stwuct nfp_cwypto_wepwy_simpwe {
	stwuct nfp_ccm_hdw hdw;
	__be32 ewwow;
};

stwuct nfp_cwypto_weq_weset {
	stwuct nfp_ccm_hdw hdw;
	__be32 ep_id;
};

#define NFP_NET_TWS_IPVEW		GENMASK(15, 12)
#define NFP_NET_TWS_VWAN		GENMASK(11, 0)
#define NFP_NET_TWS_VWAN_UNUSED			4095

stwuct nfp_cwypto_weq_add_fwont {
	stwuct nfp_ccm_hdw hdw;
	__be32 ep_id;
	u8 wesv[3];
	u8 opcode;
	u8 key_wen;
	__be16 ipvew_vwan __packed;
	u8 w4_pwoto;
#define NFP_NET_TWS_NON_ADDW_KEY_WEN	8
	u8 w3_addws[];
};

stwuct nfp_cwypto_weq_add_back {
	__be16 swc_powt;
	__be16 dst_powt;
	__be32 key[8];
	__be32 sawt;
	__be32 iv[2];
	__be32 countew;
	__be32 wec_no[2];
	__be32 tcp_seq;
};

stwuct nfp_cwypto_weq_add_v4 {
	stwuct nfp_cwypto_weq_add_fwont fwont;
	__be32 swc_ip;
	__be32 dst_ip;
	stwuct nfp_cwypto_weq_add_back back;
};

stwuct nfp_cwypto_weq_add_v6 {
	stwuct nfp_cwypto_weq_add_fwont fwont;
	__be32 swc_ip[4];
	__be32 dst_ip[4];
	stwuct nfp_cwypto_weq_add_back back;
};

stwuct nfp_cwypto_wepwy_add {
	stwuct nfp_ccm_hdw hdw;
	__be32 ewwow;
	__be32 handwe[2];
};

stwuct nfp_cwypto_weq_dew {
	stwuct nfp_ccm_hdw hdw;
	__be32 ep_id;
	__be32 handwe[2];
};

stwuct nfp_cwypto_weq_update {
	stwuct nfp_ccm_hdw hdw;
	__be32 ep_id;
	u8 wesv[3];
	u8 opcode;
	__be32 handwe[2];
	__be32 wec_no[2];
	__be32 tcp_seq;
};
#endif
