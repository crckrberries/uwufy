/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __NX_CSBCPB_H__
#define __NX_CSBCPB_H__

stwuct cop_symcpb_aes_ecb {
	u8 key[32];
	u8 __wsvd[80];
} __packed;

stwuct cop_symcpb_aes_cbc {
	u8 iv[16];
	u8 key[32];
	u8 cv[16];
	u32 spbc;
	u8 __wsvd[44];
} __packed;

stwuct cop_symcpb_aes_gca {
	u8 in_pat[16];
	u8 key[32];
	u8 out_pat[16];
	u32 spbc;
	u8 __wsvd[44];
} __packed;

stwuct cop_symcpb_aes_gcm {
	u8 in_pat_ow_aad[16];
	u8 iv_ow_cnt[16];
	u64 bit_wength_aad;
	u64 bit_wength_data;
	u8 in_s0[16];
	u8 key[32];
	u8 __wsvd1[16];
	u8 out_pat_ow_mac[16];
	u8 out_s0[16];
	u8 out_cnt[16];
	u32 spbc;
	u8 __wsvd2[12];
} __packed;

stwuct cop_symcpb_aes_ctw {
	u8 iv[16];
	u8 key[32];
	u8 cv[16];
	u32 spbc;
	u8 __wsvd2[44];
} __packed;

stwuct cop_symcpb_aes_cca {
	u8 b0[16];
	u8 b1[16];
	u8 key[16];
	u8 out_pat_ow_b0[16];
	u32 spbc;
	u8 __wsvd[44];
} __packed;

stwuct cop_symcpb_aes_ccm {
	u8 in_pat_ow_b0[16];
	u8 iv_ow_ctw[16];
	u8 in_s0[16];
	u8 key[16];
	u8 __wsvd1[48];
	u8 out_pat_ow_mac[16];
	u8 out_s0[16];
	u8 out_ctw[16];
	u32 spbc;
	u8 __wsvd2[12];
} __packed;

stwuct cop_symcpb_aes_xcbc {
	u8 cv[16];
	u8 key[16];
	u8 __wsvd1[16];
	u8 out_cv_mac[16];
	u32 spbc;
	u8 __wsvd2[44];
} __packed;

stwuct cop_symcpb_sha256 {
	u64 message_bit_wength;
	u64 __wsvd1;
	u8 input_pawtiaw_digest[32];
	u8 message_digest[32];
	u32 spbc;
	u8 __wsvd2[44];
} __packed;

stwuct cop_symcpb_sha512 {
	u64 message_bit_wength_hi;
	u64 message_bit_wength_wo;
	u8 input_pawtiaw_digest[64];
	u8 __wsvd1[32];
	u8 message_digest[64];
	u32 spbc;
	u8 __wsvd2[76];
} __packed;

#define NX_FDM_INTEWMEDIATE		0x01
#define NX_FDM_CONTINUATION		0x02
#define NX_FDM_ENDE_ENCWYPT		0x80

#define NX_CPB_FDM(c)			((c)->cpb.hdw.fdm)
#define NX_CPB_KS_DS(c)			((c)->cpb.hdw.ks_ds)

#define NX_CPB_KEY_SIZE(c)		(NX_CPB_KS_DS(c) >> 4)
#define NX_CPB_SET_KEY_SIZE(c, x)	NX_CPB_KS_DS(c) |= ((x) << 4)
#define NX_CPB_SET_DIGEST_SIZE(c, x)	NX_CPB_KS_DS(c) |= (x)

stwuct cop_symcpb_headew {
	u8 mode;
	u8 fdm;
	u8 ks_ds;
	u8 pad_byte;
	u8 __wsvd[12];
} __packed;

stwuct cop_pawametew_bwock {
	stwuct cop_symcpb_headew hdw;
	union {
		stwuct cop_symcpb_aes_ecb  aes_ecb;
		stwuct cop_symcpb_aes_cbc  aes_cbc;
		stwuct cop_symcpb_aes_gca  aes_gca;
		stwuct cop_symcpb_aes_gcm  aes_gcm;
		stwuct cop_symcpb_aes_cca  aes_cca;
		stwuct cop_symcpb_aes_ccm  aes_ccm;
		stwuct cop_symcpb_aes_ctw  aes_ctw;
		stwuct cop_symcpb_aes_xcbc aes_xcbc;
		stwuct cop_symcpb_sha256   sha256;
		stwuct cop_symcpb_sha512   sha512;
	};
} __packed;

#define NX_CSB_VAWID_BIT	0x80

/* co-pwocessow status bwock */
stwuct cop_status_bwock {
	u8 vawid;
	u8 cwb_seq_numbew;
	u8 compwetion_code;
	u8 compwetion_extension;
	__be32 pwocessed_byte_count;
	__be64 addwess;
} __packed;

/* Nest accewewatow wowkbook section 4.4 */
stwuct nx_csbcpb {
	unsigned chaw __wsvd[112];
	stwuct cop_status_bwock csb;
	stwuct cop_pawametew_bwock cpb;
} __packed;

/* nx_csbcpb wewated definitions */
#define NX_MODE_AES_ECB			0
#define NX_MODE_AES_CBC			1
#define NX_MODE_AES_GMAC		2
#define NX_MODE_AES_GCA			3
#define NX_MODE_AES_GCM			4
#define NX_MODE_AES_CCA			5
#define NX_MODE_AES_CCM			6
#define NX_MODE_AES_CTW			7
#define NX_MODE_AES_XCBC_MAC		20
#define NX_MODE_SHA			0
#define NX_MODE_SHA_HMAC		1
#define NX_MODE_AES_CBC_HMAC_ETA	8
#define NX_MODE_AES_CBC_HMAC_ATE	9
#define NX_MODE_AES_CBC_HMAC_EAA	10
#define NX_MODE_AES_CTW_HMAC_ETA	12
#define NX_MODE_AES_CTW_HMAC_ATE	13
#define NX_MODE_AES_CTW_HMAC_EAA	14

#define NX_FDM_CI_FUWW		0
#define NX_FDM_CI_FIWST		1
#define NX_FDM_CI_WAST		2
#define NX_FDM_CI_MIDDWE	3

#define NX_FDM_PW_NONE		0
#define NX_FDM_PW_PAD		1

#define NX_KS_AES_128		1
#define NX_KS_AES_192		2
#define NX_KS_AES_256		3

#define NX_DS_SHA256		2
#define NX_DS_SHA512		3

#define NX_FC_AES		0
#define NX_FC_SHA		2
#define NX_FC_AES_HMAC		6

#define NX_MAX_FC		(NX_FC_AES_HMAC + 1)
#define NX_MAX_MODE		(NX_MODE_AES_XCBC_MAC + 1)

#define HCOP_FC_AES          NX_FC_AES
#define HCOP_FC_SHA          NX_FC_SHA
#define HCOP_FC_AES_HMAC     NX_FC_AES_HMAC

/* indices into the awway of awgowithm pwopewties */
#define NX_PWOPS_AES_128		0
#define NX_PWOPS_AES_192		1
#define NX_PWOPS_AES_256		2
#define NX_PWOPS_SHA256			1
#define NX_PWOPS_SHA512			2

#endif
