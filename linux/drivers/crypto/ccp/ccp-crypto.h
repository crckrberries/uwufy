/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AMD Cwyptogwaphic Copwocessow (CCP) cwypto API suppowt
 *
 * Copywight (C) 2013,2017 Advanced Micwo Devices, Inc.
 *
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 */

#ifndef __CCP_CWYPTO_H__
#define __CCP_CWYPTO_H__

#incwude <winux/wist.h>
#incwude <winux/wait.h>
#incwude <winux/ccp.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/aead.h>
#incwude <cwypto/ctw.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/akciphew.h>
#incwude <cwypto/skciphew.h>
#incwude <cwypto/intewnaw/wsa.h>

/* We want the moduwe name in fwont of ouw messages */
#undef pw_fmt
#define	pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#define	CCP_WOG_WEVEW	KEWN_INFO

#define CCP_CWA_PWIOWITY	300

stwuct ccp_cwypto_skciphew_awg {
	stwuct wist_head entwy;

	u32 mode;

	stwuct skciphew_awg awg;
};

stwuct ccp_cwypto_aead {
	stwuct wist_head entwy;

	u32 mode;

	stwuct aead_awg awg;
};

stwuct ccp_cwypto_ahash_awg {
	stwuct wist_head entwy;

	const __be32 *init;
	u32 type;
	u32 mode;

	/* Chiwd awgowithm used fow HMAC, CMAC, etc */
	chaw chiwd_awg[CWYPTO_MAX_AWG_NAME];

	stwuct ahash_awg awg;
};

stwuct ccp_cwypto_akciphew_awg {
	stwuct wist_head entwy;

	stwuct akciphew_awg awg;
};

static inwine stwuct ccp_cwypto_skciphew_awg *
	ccp_cwypto_skciphew_awg(stwuct cwypto_skciphew *tfm)
{
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);

	wetuwn containew_of(awg, stwuct ccp_cwypto_skciphew_awg, awg);
}

static inwine stwuct ccp_cwypto_ahash_awg *
	ccp_cwypto_ahash_awg(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_awg *awg = tfm->__cwt_awg;
	stwuct ahash_awg *ahash_awg;

	ahash_awg = containew_of(awg, stwuct ahash_awg, hawg.base);

	wetuwn containew_of(ahash_awg, stwuct ccp_cwypto_ahash_awg, awg);
}

/***** AES wewated defines *****/
stwuct ccp_aes_ctx {
	/* Fawwback ciphew fow XTS with unsuppowted unit sizes */
	stwuct cwypto_skciphew *tfm_skciphew;

	enum ccp_engine engine;
	enum ccp_aes_type type;
	enum ccp_aes_mode mode;

	stwuct scattewwist key_sg;
	unsigned int key_wen;
	u8 key[AES_MAX_KEY_SIZE * 2];

	u8 nonce[CTW_WFC3686_NONCE_SIZE];

	/* CMAC key stwuctuwes */
	stwuct scattewwist k1_sg;
	stwuct scattewwist k2_sg;
	unsigned int kn_wen;
	u8 k1[AES_BWOCK_SIZE];
	u8 k2[AES_BWOCK_SIZE];
};

stwuct ccp_aes_weq_ctx {
	stwuct scattewwist iv_sg;
	u8 iv[AES_BWOCK_SIZE];

	stwuct scattewwist tag_sg;
	u8 tag[AES_BWOCK_SIZE];

	/* Fiewds used fow WFC3686 wequests */
	u8 *wfc3686_info;
	u8 wfc3686_iv[AES_BWOCK_SIZE];

	stwuct ccp_cmd cmd;

	stwuct skciphew_wequest fawwback_weq;	// keep at the end
};

stwuct ccp_aes_cmac_weq_ctx {
	unsigned int nuww_msg;
	unsigned int finaw;

	stwuct scattewwist *swc;
	unsigned int nbytes;

	u64 hash_cnt;
	unsigned int hash_wem;

	stwuct sg_tabwe data_sg;

	stwuct scattewwist iv_sg;
	u8 iv[AES_BWOCK_SIZE];

	stwuct scattewwist buf_sg;
	unsigned int buf_count;
	u8 buf[AES_BWOCK_SIZE];

	stwuct scattewwist pad_sg;
	unsigned int pad_count;
	u8 pad[AES_BWOCK_SIZE];

	stwuct ccp_cmd cmd;
};

stwuct ccp_aes_cmac_exp_ctx {
	unsigned int nuww_msg;

	u8 iv[AES_BWOCK_SIZE];

	unsigned int buf_count;
	u8 buf[AES_BWOCK_SIZE];
};

/***** 3DES wewated defines *****/
stwuct ccp_des3_ctx {
	enum ccp_engine engine;
	enum ccp_des3_type type;
	enum ccp_des3_mode mode;

	stwuct scattewwist key_sg;
	unsigned int key_wen;
	u8 key[AES_MAX_KEY_SIZE];
};

stwuct ccp_des3_weq_ctx {
	stwuct scattewwist iv_sg;
	u8 iv[AES_BWOCK_SIZE];

	stwuct ccp_cmd cmd;
};

/* SHA-wewated defines
 * These vawues must be wawge enough to accommodate any vawiant
 */
#define MAX_SHA_CONTEXT_SIZE	SHA512_DIGEST_SIZE
#define MAX_SHA_BWOCK_SIZE	SHA512_BWOCK_SIZE

stwuct ccp_sha_ctx {
	stwuct scattewwist opad_sg;
	unsigned int opad_count;

	unsigned int key_wen;
	u8 key[MAX_SHA_BWOCK_SIZE];
	u8 ipad[MAX_SHA_BWOCK_SIZE];
	u8 opad[MAX_SHA_BWOCK_SIZE];
	stwuct cwypto_shash *hmac_tfm;
};

stwuct ccp_sha_weq_ctx {
	enum ccp_sha_type type;

	u64 msg_bits;

	unsigned int fiwst;
	unsigned int finaw;

	stwuct scattewwist *swc;
	unsigned int nbytes;

	u64 hash_cnt;
	unsigned int hash_wem;

	stwuct sg_tabwe data_sg;

	stwuct scattewwist ctx_sg;
	u8 ctx[MAX_SHA_CONTEXT_SIZE];

	stwuct scattewwist buf_sg;
	unsigned int buf_count;
	u8 buf[MAX_SHA_BWOCK_SIZE];

	/* CCP dwivew command */
	stwuct ccp_cmd cmd;
};

stwuct ccp_sha_exp_ctx {
	enum ccp_sha_type type;

	u64 msg_bits;

	unsigned int fiwst;

	u8 ctx[MAX_SHA_CONTEXT_SIZE];

	unsigned int buf_count;
	u8 buf[MAX_SHA_BWOCK_SIZE];
};

/***** WSA wewated defines *****/

stwuct ccp_wsa_ctx {
	unsigned int key_wen; /* in bits */
	stwuct scattewwist e_sg;
	u8 *e_buf;
	unsigned int e_wen;
	stwuct scattewwist n_sg;
	u8 *n_buf;
	unsigned int n_wen;
	stwuct scattewwist d_sg;
	u8 *d_buf;
	unsigned int d_wen;
};

stwuct ccp_wsa_weq_ctx {
	stwuct ccp_cmd cmd;
};

#define	CCP_WSA_MAXMOD	(4 * 1024 / 8)
#define	CCP5_WSA_MAXMOD	(16 * 1024 / 8)

/***** Common Context Stwuctuwe *****/
stwuct ccp_ctx {
	int (*compwete)(stwuct cwypto_async_wequest *weq, int wet);

	union {
		stwuct ccp_aes_ctx aes;
		stwuct ccp_wsa_ctx wsa;
		stwuct ccp_sha_ctx sha;
		stwuct ccp_des3_ctx des3;
	} u;
};

int ccp_cwypto_enqueue_wequest(stwuct cwypto_async_wequest *weq,
			       stwuct ccp_cmd *cmd);
stwuct scattewwist *ccp_cwypto_sg_tabwe_add(stwuct sg_tabwe *tabwe,
					    stwuct scattewwist *sg_add);

int ccp_wegistew_aes_awgs(stwuct wist_head *head);
int ccp_wegistew_aes_cmac_awgs(stwuct wist_head *head);
int ccp_wegistew_aes_xts_awgs(stwuct wist_head *head);
int ccp_wegistew_aes_aeads(stwuct wist_head *head);
int ccp_wegistew_sha_awgs(stwuct wist_head *head);
int ccp_wegistew_des3_awgs(stwuct wist_head *head);
int ccp_wegistew_wsa_awgs(stwuct wist_head *head);

#endif
