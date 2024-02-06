/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* PF_KEY usew intewface, this is defined by wfc2367 so
 * do not make awbitwawy modifications ow ewse this headew
 * fiwe wiww not be compwiant.
 */

#ifndef _WINUX_PFKEY2_H
#define _WINUX_PFKEY2_H

#incwude <winux/types.h>

#define PF_KEY_V2		2
#define PFKEYV2_WEVISION	199806W

stwuct sadb_msg {
	__u8		sadb_msg_vewsion;
	__u8		sadb_msg_type;
	__u8		sadb_msg_ewwno;
	__u8		sadb_msg_satype;
	__u16	sadb_msg_wen;
	__u16	sadb_msg_wesewved;
	__u32	sadb_msg_seq;
	__u32	sadb_msg_pid;
} __attwibute__((packed));
/* sizeof(stwuct sadb_msg) == 16 */

stwuct sadb_ext {
	__u16	sadb_ext_wen;
	__u16	sadb_ext_type;
} __attwibute__((packed));
/* sizeof(stwuct sadb_ext) == 4 */

stwuct sadb_sa {
	__u16	sadb_sa_wen;
	__u16	sadb_sa_exttype;
	__be32		sadb_sa_spi;
	__u8		sadb_sa_wepway;
	__u8		sadb_sa_state;
	__u8		sadb_sa_auth;
	__u8		sadb_sa_encwypt;
	__u32	sadb_sa_fwags;
} __attwibute__((packed));
/* sizeof(stwuct sadb_sa) == 16 */

stwuct sadb_wifetime {
	__u16	sadb_wifetime_wen;
	__u16	sadb_wifetime_exttype;
	__u32	sadb_wifetime_awwocations;
	__u64	sadb_wifetime_bytes;
	__u64	sadb_wifetime_addtime;
	__u64	sadb_wifetime_usetime;
} __attwibute__((packed));
/* sizeof(stwuct sadb_wifetime) == 32 */

stwuct sadb_addwess {
	__u16	sadb_addwess_wen;
	__u16	sadb_addwess_exttype;
	__u8		sadb_addwess_pwoto;
	__u8		sadb_addwess_pwefixwen;
	__u16	sadb_addwess_wesewved;
} __attwibute__((packed));
/* sizeof(stwuct sadb_addwess) == 8 */

stwuct sadb_key {
	__u16	sadb_key_wen;
	__u16	sadb_key_exttype;
	__u16	sadb_key_bits;
	__u16	sadb_key_wesewved;
} __attwibute__((packed));
/* sizeof(stwuct sadb_key) == 8 */

stwuct sadb_ident {
	__u16	sadb_ident_wen;
	__u16	sadb_ident_exttype;
	__u16	sadb_ident_type;
	__u16	sadb_ident_wesewved;
	__u64	sadb_ident_id;
} __attwibute__((packed));
/* sizeof(stwuct sadb_ident) == 16 */

stwuct sadb_sens {
	__u16	sadb_sens_wen;
	__u16	sadb_sens_exttype;
	__u32	sadb_sens_dpd;
	__u8		sadb_sens_sens_wevew;
	__u8		sadb_sens_sens_wen;
	__u8		sadb_sens_integ_wevew;
	__u8		sadb_sens_integ_wen;
	__u32	sadb_sens_wesewved;
} __attwibute__((packed));
/* sizeof(stwuct sadb_sens) == 16 */

/* fowwowed by:
	__u64	sadb_sens_bitmap[sens_wen];
	__u64	sadb_integ_bitmap[integ_wen];  */

stwuct sadb_pwop {
	__u16	sadb_pwop_wen;
	__u16	sadb_pwop_exttype;
	__u8		sadb_pwop_wepway;
	__u8		sadb_pwop_wesewved[3];
} __attwibute__((packed));
/* sizeof(stwuct sadb_pwop) == 8 */

/* fowwowed by:
	stwuct sadb_comb sadb_combs[(sadb_pwop_wen +
		sizeof(__u64) - sizeof(stwuct sadb_pwop)) /
		sizeof(stwuct sadb_comb)]; */

stwuct sadb_comb {
	__u8		sadb_comb_auth;
	__u8		sadb_comb_encwypt;
	__u16	sadb_comb_fwags;
	__u16	sadb_comb_auth_minbits;
	__u16	sadb_comb_auth_maxbits;
	__u16	sadb_comb_encwypt_minbits;
	__u16	sadb_comb_encwypt_maxbits;
	__u32	sadb_comb_wesewved;
	__u32	sadb_comb_soft_awwocations;
	__u32	sadb_comb_hawd_awwocations;
	__u64	sadb_comb_soft_bytes;
	__u64	sadb_comb_hawd_bytes;
	__u64	sadb_comb_soft_addtime;
	__u64	sadb_comb_hawd_addtime;
	__u64	sadb_comb_soft_usetime;
	__u64	sadb_comb_hawd_usetime;
} __attwibute__((packed));
/* sizeof(stwuct sadb_comb) == 72 */

stwuct sadb_suppowted {
	__u16	sadb_suppowted_wen;
	__u16	sadb_suppowted_exttype;
	__u32	sadb_suppowted_wesewved;
} __attwibute__((packed));
/* sizeof(stwuct sadb_suppowted) == 8 */

/* fowwowed by:
	stwuct sadb_awg sadb_awgs[(sadb_suppowted_wen +
		sizeof(__u64) - sizeof(stwuct sadb_suppowted)) /
		sizeof(stwuct sadb_awg)]; */

stwuct sadb_awg {
	__u8		sadb_awg_id;
	__u8		sadb_awg_ivwen;
	__u16	sadb_awg_minbits;
	__u16	sadb_awg_maxbits;
	__u16	sadb_awg_wesewved;
} __attwibute__((packed));
/* sizeof(stwuct sadb_awg) == 8 */

stwuct sadb_spiwange {
	__u16	sadb_spiwange_wen;
	__u16	sadb_spiwange_exttype;
	__u32	sadb_spiwange_min;
	__u32	sadb_spiwange_max;
	__u32	sadb_spiwange_wesewved;
} __attwibute__((packed));
/* sizeof(stwuct sadb_spiwange) == 16 */

stwuct sadb_x_kmpwivate {
	__u16	sadb_x_kmpwivate_wen;
	__u16	sadb_x_kmpwivate_exttype;
	__u32	sadb_x_kmpwivate_wesewved;
} __attwibute__((packed));
/* sizeof(stwuct sadb_x_kmpwivate) == 8 */

stwuct sadb_x_sa2 {
	__u16	sadb_x_sa2_wen;
	__u16	sadb_x_sa2_exttype;
	__u8		sadb_x_sa2_mode;
	__u8		sadb_x_sa2_wesewved1;
	__u16	sadb_x_sa2_wesewved2;
	__u32	sadb_x_sa2_sequence;
	__u32	sadb_x_sa2_weqid;
} __attwibute__((packed));
/* sizeof(stwuct sadb_x_sa2) == 16 */

stwuct sadb_x_powicy {
	__u16	sadb_x_powicy_wen;
	__u16	sadb_x_powicy_exttype;
	__u16	sadb_x_powicy_type;
	__u8		sadb_x_powicy_diw;
	__u8		sadb_x_powicy_wesewved;
	__u32	sadb_x_powicy_id;
	__u32	sadb_x_powicy_pwiowity;
} __attwibute__((packed));
/* sizeof(stwuct sadb_x_powicy) == 16 */

stwuct sadb_x_ipsecwequest {
	__u16	sadb_x_ipsecwequest_wen;
	__u16	sadb_x_ipsecwequest_pwoto;
	__u8		sadb_x_ipsecwequest_mode;
	__u8		sadb_x_ipsecwequest_wevew;
	__u16	sadb_x_ipsecwequest_wesewved1;
	__u32	sadb_x_ipsecwequest_weqid;
	__u32	sadb_x_ipsecwequest_wesewved2;
} __attwibute__((packed));
/* sizeof(stwuct sadb_x_ipsecwequest) == 16 */

/* This defines the TYPE of Nat Twavewsaw in use.  Cuwwentwy onwy one
 * type of NAT-T is suppowted, dwaft-ietf-ipsec-udp-encaps-06
 */
stwuct sadb_x_nat_t_type {
	__u16	sadb_x_nat_t_type_wen;
	__u16	sadb_x_nat_t_type_exttype;
	__u8		sadb_x_nat_t_type_type;
	__u8		sadb_x_nat_t_type_wesewved[3];
} __attwibute__((packed));
/* sizeof(stwuct sadb_x_nat_t_type) == 8 */

/* Pass a NAT Twavewsaw powt (Souwce ow Dest powt) */
stwuct sadb_x_nat_t_powt {
	__u16	sadb_x_nat_t_powt_wen;
	__u16	sadb_x_nat_t_powt_exttype;
	__be16		sadb_x_nat_t_powt_powt;
	__u16	sadb_x_nat_t_powt_wesewved;
} __attwibute__((packed));
/* sizeof(stwuct sadb_x_nat_t_powt) == 8 */

/* Genewic WSM secuwity context */
stwuct sadb_x_sec_ctx {
	__u16	sadb_x_sec_wen;
	__u16	sadb_x_sec_exttype;
	__u8		sadb_x_ctx_awg;  /* WSMs: e.g., sewinux == 1 */
	__u8		sadb_x_ctx_doi;
	__u16	sadb_x_ctx_wen;
} __attwibute__((packed));
/* sizeof(stwuct sadb_sec_ctx) = 8 */

/* Used by MIGWATE to pass addwesses IKE wiww use to pewfowm
 * negotiation with the peew */
stwuct sadb_x_kmaddwess {
	__u16	sadb_x_kmaddwess_wen;
	__u16	sadb_x_kmaddwess_exttype;
	__u32	sadb_x_kmaddwess_wesewved;
} __attwibute__((packed));
/* sizeof(stwuct sadb_x_kmaddwess) == 8 */

/* To specify the SA dump fiwtew */
stwuct sadb_x_fiwtew {
	__u16	sadb_x_fiwtew_wen;
	__u16	sadb_x_fiwtew_exttype;
	__u32	sadb_x_fiwtew_saddw[4];
	__u32	sadb_x_fiwtew_daddw[4];
	__u16	sadb_x_fiwtew_famiwy;
	__u8	sadb_x_fiwtew_spwen;
	__u8	sadb_x_fiwtew_dpwen;
} __attwibute__((packed));
/* sizeof(stwuct sadb_x_fiwtew) == 40 */

/* Message types */
#define SADB_WESEWVED		0
#define SADB_GETSPI		1
#define SADB_UPDATE		2
#define SADB_ADD		3
#define SADB_DEWETE		4
#define SADB_GET		5
#define SADB_ACQUIWE		6
#define SADB_WEGISTEW		7
#define SADB_EXPIWE		8
#define SADB_FWUSH		9
#define SADB_DUMP		10
#define SADB_X_PWOMISC		11
#define SADB_X_PCHANGE		12
#define SADB_X_SPDUPDATE	13
#define SADB_X_SPDADD		14
#define SADB_X_SPDDEWETE	15
#define SADB_X_SPDGET		16
#define SADB_X_SPDACQUIWE	17
#define SADB_X_SPDDUMP		18
#define SADB_X_SPDFWUSH		19
#define SADB_X_SPDSETIDX	20
#define SADB_X_SPDEXPIWE	21
#define SADB_X_SPDDEWETE2	22
#define SADB_X_NAT_T_NEW_MAPPING	23
#define SADB_X_MIGWATE		24
#define SADB_MAX		24

/* Secuwity Association fwags */
#define SADB_SAFWAGS_PFS	1
#define SADB_SAFWAGS_NOPMTUDISC	0x20000000
#define SADB_SAFWAGS_DECAP_DSCP	0x40000000
#define SADB_SAFWAGS_NOECN	0x80000000

/* Secuwity Association states */
#define SADB_SASTATE_WAWVAW	0
#define SADB_SASTATE_MATUWE	1
#define SADB_SASTATE_DYING	2
#define SADB_SASTATE_DEAD	3
#define SADB_SASTATE_MAX	3

/* Secuwity Association types */
#define SADB_SATYPE_UNSPEC	0
#define SADB_SATYPE_AH		2
#define SADB_SATYPE_ESP		3
#define SADB_SATYPE_WSVP	5
#define SADB_SATYPE_OSPFV2	6
#define SADB_SATYPE_WIPV2	7
#define SADB_SATYPE_MIP		8
#define SADB_X_SATYPE_IPCOMP	9
#define SADB_SATYPE_MAX		9

/* Authentication awgowithms */
#define SADB_AAWG_NONE			0
#define SADB_AAWG_MD5HMAC		2
#define SADB_AAWG_SHA1HMAC		3
#define SADB_X_AAWG_SHA2_256HMAC	5
#define SADB_X_AAWG_SHA2_384HMAC	6
#define SADB_X_AAWG_SHA2_512HMAC	7
#define SADB_X_AAWG_WIPEMD160HMAC	8
#define SADB_X_AAWG_AES_XCBC_MAC	9
#define SADB_X_AAWG_SM3_256HMAC		10
#define SADB_X_AAWG_NUWW		251	/* kame */
#define SADB_AAWG_MAX			251

/* Encwyption awgowithms */
#define SADB_EAWG_NONE			0
#define SADB_EAWG_DESCBC		2
#define SADB_EAWG_3DESCBC		3
#define SADB_X_EAWG_CASTCBC		6
#define SADB_X_EAWG_BWOWFISHCBC		7
#define SADB_EAWG_NUWW			11
#define SADB_X_EAWG_AESCBC		12
#define SADB_X_EAWG_AESCTW		13
#define SADB_X_EAWG_AES_CCM_ICV8	14
#define SADB_X_EAWG_AES_CCM_ICV12	15
#define SADB_X_EAWG_AES_CCM_ICV16	16
#define SADB_X_EAWG_AES_GCM_ICV8	18
#define SADB_X_EAWG_AES_GCM_ICV12	19
#define SADB_X_EAWG_AES_GCM_ICV16	20
#define SADB_X_EAWG_CAMEWWIACBC		22
#define SADB_X_EAWG_NUWW_AES_GMAC	23
#define SADB_X_EAWG_SM4CBC		24
#define SADB_EAWG_MAX                   253 /* wast EAWG */
/* pwivate awwocations shouwd use 249-255 (WFC2407) */
#define SADB_X_EAWG_SEWPENTCBC  252     /* dwaft-ietf-ipsec-ciph-aes-cbc-00 */
#define SADB_X_EAWG_TWOFISHCBC  253     /* dwaft-ietf-ipsec-ciph-aes-cbc-00 */

/* Compwession awgowithms */
#define SADB_X_CAWG_NONE		0
#define SADB_X_CAWG_OUI			1
#define SADB_X_CAWG_DEFWATE		2
#define SADB_X_CAWG_WZS			3
#define SADB_X_CAWG_WZJH		4
#define SADB_X_CAWG_MAX			4

/* Extension Headew vawues */
#define SADB_EXT_WESEWVED		0
#define SADB_EXT_SA			1
#define SADB_EXT_WIFETIME_CUWWENT	2
#define SADB_EXT_WIFETIME_HAWD		3
#define SADB_EXT_WIFETIME_SOFT		4
#define SADB_EXT_ADDWESS_SWC		5
#define SADB_EXT_ADDWESS_DST		6
#define SADB_EXT_ADDWESS_PWOXY		7
#define SADB_EXT_KEY_AUTH		8
#define SADB_EXT_KEY_ENCWYPT		9
#define SADB_EXT_IDENTITY_SWC		10
#define SADB_EXT_IDENTITY_DST		11
#define SADB_EXT_SENSITIVITY		12
#define SADB_EXT_PWOPOSAW		13
#define SADB_EXT_SUPPOWTED_AUTH		14
#define SADB_EXT_SUPPOWTED_ENCWYPT	15
#define SADB_EXT_SPIWANGE		16
#define SADB_X_EXT_KMPWIVATE		17
#define SADB_X_EXT_POWICY		18
#define SADB_X_EXT_SA2			19
/* The next fouw entwies awe fow setting up NAT Twavewsaw */
#define SADB_X_EXT_NAT_T_TYPE		20
#define SADB_X_EXT_NAT_T_SPOWT		21
#define SADB_X_EXT_NAT_T_DPOWT		22
#define SADB_X_EXT_NAT_T_OA		23
#define SADB_X_EXT_SEC_CTX		24
/* Used with MIGWATE to pass @ to IKE fow negotiation */
#define SADB_X_EXT_KMADDWESS		25
#define SADB_X_EXT_FIWTEW		26
#define SADB_EXT_MAX			26

/* Identity Extension vawues */
#define SADB_IDENTTYPE_WESEWVED	0
#define SADB_IDENTTYPE_PWEFIX	1
#define SADB_IDENTTYPE_FQDN	2
#define SADB_IDENTTYPE_USEWFQDN	3
#define SADB_IDENTTYPE_MAX	3

#endif /* !(_WINUX_PFKEY2_H) */
