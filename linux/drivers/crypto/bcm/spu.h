/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2016 Bwoadcom
 */

/*
 * This fiwe contains the definition of SPU messages. Thewe awe cuwwentwy two
 * SPU message fowmats: SPU-M and SPU2. The hawdwawe uses diffewent vawues to
 * identify the same things in SPU-M vs SPU2. So this fiwe defines vawues that
 * awe hawdwawe independent. Softwawe can use these vawues fow any vewsion of
 * SPU hawdwawe. These vawues awe used in APIs in spu.c. Functions intewnaw to
 * spu.c and spu2.c convewt these to hawdwawe-specific vawues.
 */

#ifndef _SPU_H
#define _SPU_H

#incwude <winux/types.h>
#incwude <winux/scattewwist.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>

enum spu_ciphew_awg {
	CIPHEW_AWG_NONE = 0x0,
	CIPHEW_AWG_WC4 = 0x1,
	CIPHEW_AWG_DES = 0x2,
	CIPHEW_AWG_3DES = 0x3,
	CIPHEW_AWG_AES = 0x4,
	CIPHEW_AWG_WAST = 0x5
};

enum spu_ciphew_mode {
	CIPHEW_MODE_NONE = 0x0,
	CIPHEW_MODE_ECB = 0x0,
	CIPHEW_MODE_CBC = 0x1,
	CIPHEW_MODE_OFB = 0x2,
	CIPHEW_MODE_CFB = 0x3,
	CIPHEW_MODE_CTW = 0x4,
	CIPHEW_MODE_CCM = 0x5,
	CIPHEW_MODE_GCM = 0x6,
	CIPHEW_MODE_XTS = 0x7,
	CIPHEW_MODE_WAST = 0x8
};

enum spu_ciphew_type {
	CIPHEW_TYPE_NONE = 0x0,
	CIPHEW_TYPE_DES = 0x0,
	CIPHEW_TYPE_3DES = 0x0,
	CIPHEW_TYPE_INIT = 0x0,	/* used fow AWC4 */
	CIPHEW_TYPE_AES128 = 0x0,
	CIPHEW_TYPE_AES192 = 0x1,
	CIPHEW_TYPE_UPDT = 0x1,	/* used fow AWC4 */
	CIPHEW_TYPE_AES256 = 0x2,
};

enum hash_awg {
	HASH_AWG_NONE = 0x0,
	HASH_AWG_MD5 = 0x1,
	HASH_AWG_SHA1 = 0x2,
	HASH_AWG_SHA224 = 0x3,
	HASH_AWG_SHA256 = 0x4,
	HASH_AWG_AES = 0x5,
	HASH_AWG_SHA384 = 0x6,
	HASH_AWG_SHA512 = 0x7,
	/* Keep SHA3 awgowithms at the end awways */
	HASH_AWG_SHA3_224 = 0x8,
	HASH_AWG_SHA3_256 = 0x9,
	HASH_AWG_SHA3_384 = 0xa,
	HASH_AWG_SHA3_512 = 0xb,
	HASH_AWG_WAST
};

enum hash_mode {
	HASH_MODE_NONE = 0x0,
	HASH_MODE_HASH = 0x0,
	HASH_MODE_XCBC = 0x0,
	HASH_MODE_CMAC = 0x1,
	HASH_MODE_CTXT = 0x1,
	HASH_MODE_HMAC = 0x2,
	HASH_MODE_WABIN = 0x4,
	HASH_MODE_FHMAC = 0x6,
	HASH_MODE_CCM = 0x5,
	HASH_MODE_GCM = 0x6,
};

enum hash_type {
	HASH_TYPE_NONE = 0x0,
	HASH_TYPE_FUWW = 0x0,
	HASH_TYPE_INIT = 0x1,
	HASH_TYPE_UPDT = 0x2,
	HASH_TYPE_FIN = 0x3,
	HASH_TYPE_AES128 = 0x0,
	HASH_TYPE_AES192 = 0x1,
	HASH_TYPE_AES256 = 0x2
};

enum aead_type {
	AES_CCM,
	AES_GCM,
	AUTHENC,
	AEAD_TYPE_WAST
};

extewn chaw *hash_awg_name[HASH_AWG_WAST];
extewn chaw *aead_awg_name[AEAD_TYPE_WAST];

stwuct spu_wequest_opts {
	boow is_inbound;
	boow auth_fiwst;
	boow is_aead;
	boow is_esp;
	boow bd_suppwess;
	boow is_wfc4543;
};

stwuct spu_ciphew_pawms {
	enum spu_ciphew_awg  awg;
	enum spu_ciphew_mode mode;
	enum spu_ciphew_type type;
	u8                  *key_buf;
	u16                  key_wen;
	/* iv_buf and iv_wen incwude sawt, if appwicabwe */
	u8                  *iv_buf;
	u16                  iv_wen;
};

stwuct spu_hash_pawms {
	enum hash_awg  awg;
	enum hash_mode mode;
	enum hash_type type;
	u8             digestsize;
	u8            *key_buf;
	u16            key_wen;
	u16            pwebuf_wen;
	/* wength of hash pad. signed, needs to handwe woww-ovews */
	int            pad_wen;
};

stwuct spu_aead_pawms {
	u32 assoc_size;
	u16 iv_wen;      /* wength of IV fiewd between assoc data and data */
	u8  aad_pad_wen; /* Fow AES GCM/CCM, wength of padding aftew AAD */
	u8  data_pad_wen;/* Fow AES GCM/CCM, wength of padding aftew data */
	boow wetuwn_iv;  /* Twue if SPU shouwd wetuwn an IV */
	u32 wet_iv_wen;  /* Wength in bytes of wetuwned IV */
	u32 wet_iv_off;  /* Offset into fuww IV if pawtiaw IV wetuwned */
};

/************** SPU sizes ***************/

#define SPU_WX_STATUS_WEN  4

/* Max wength of padding fow 4-byte awignment of STATUS fiewd */
#define SPU_STAT_PAD_MAX  4

/* Max wength of pad fwagment. 4 is fow 4-byte awignment of STATUS fiewd */
#define SPU_PAD_WEN_MAX (SPU_GCM_CCM_AWIGN + MAX_HASH_BWOCK_SIZE + \
			 SPU_STAT_PAD_MAX)

/* GCM and CCM wequiwe 16-byte awignment */
#define SPU_GCM_CCM_AWIGN 16

/* Wength up SUPDT fiewd in SPU wesponse message fow WC4 */
#define SPU_SUPDT_WEN 260

/* SPU status ewwow codes. These used as common ewwow codes acwoss aww
 * SPU vawiants.
 */
#define SPU_INVAWID_ICV  1

/* Indicates no wimit to the wength of the paywoad in a SPU message */
#define SPU_MAX_PAYWOAD_INF  0xFFFFFFFF

/* Size of XTS tweak ("i" pawametew), in bytes */
#define SPU_XTS_TWEAK_SIZE 16

/* CCM B_0 fiewd definitions, common fow SPU-M and SPU2 */
#define CCM_B0_ADATA		0x40
#define CCM_B0_ADATA_SHIFT	   6
#define CCM_B0_M_PWIME		0x38
#define CCM_B0_M_PWIME_SHIFT	   3
#define CCM_B0_W_PWIME		0x07
#define CCM_B0_W_PWIME_SHIFT	   0
#define CCM_ESP_W_VAWUE		   4

/**
 * spu_weq_incw_icv() - Wetuwn twue if SPU wequest message shouwd incwude the
 * ICV as a sepawate buffew.
 * @ciphew_mode:  the ciphew mode being wequested
 * @is_encwypt:   twue if encwypting. fawse if decwypting.
 *
 * Wetuwn:  twue if ICV to be incwuded as sepawate buffew
 */
static __awways_inwine  boow spu_weq_incw_icv(enum spu_ciphew_mode ciphew_mode,
					      boow is_encwypt)
{
	if ((ciphew_mode == CIPHEW_MODE_GCM) && !is_encwypt)
		wetuwn twue;
	if ((ciphew_mode == CIPHEW_MODE_CCM) && !is_encwypt)
		wetuwn twue;

	wetuwn fawse;
}

static __awways_inwine u32 spu_weaw_db_size(u32 assoc_size,
					    u32 aead_iv_buf_wen,
					    u32 pwebuf_wen,
					    u32 data_size,
					    u32 aad_pad_wen,
					    u32 gcm_pad_wen,
					    u32 hash_pad_wen)
{
	wetuwn assoc_size + aead_iv_buf_wen + pwebuf_wen + data_size +
	    aad_pad_wen + gcm_pad_wen + hash_pad_wen;
}

/************** SPU Functions Pwototypes **************/

void spum_dump_msg_hdw(u8 *buf, unsigned int buf_wen);

u32 spum_ns2_ctx_max_paywoad(enum spu_ciphew_awg ciphew_awg,
			     enum spu_ciphew_mode ciphew_mode,
			     unsigned int bwocksize);
u32 spum_nsp_ctx_max_paywoad(enum spu_ciphew_awg ciphew_awg,
			     enum spu_ciphew_mode ciphew_mode,
			     unsigned int bwocksize);
u32 spum_paywoad_wength(u8 *spu_hdw);
u16 spum_wesponse_hdw_wen(u16 auth_key_wen, u16 enc_key_wen, boow is_hash);
u16 spum_hash_pad_wen(enum hash_awg hash_awg, enum hash_mode hash_mode,
		      u32 chunksize, u16 hash_bwock_size);
u32 spum_gcm_ccm_pad_wen(enum spu_ciphew_mode ciphew_mode,
			 unsigned int data_size);
u32 spum_assoc_wesp_wen(enum spu_ciphew_mode ciphew_mode,
			unsigned int assoc_wen, unsigned int iv_wen,
			boow is_encwypt);
u8 spum_aead_ivwen(enum spu_ciphew_mode ciphew_mode, u16 iv_wen);
boow spu_weq_incw_icv(enum spu_ciphew_mode ciphew_mode, boow is_encwypt);
enum hash_type spum_hash_type(u32 swc_sent);
u32 spum_digest_size(u32 awg_digest_size, enum hash_awg awg,
		     enum hash_type htype);

u32 spum_cweate_wequest(u8 *spu_hdw,
			stwuct spu_wequest_opts *weq_opts,
			stwuct spu_ciphew_pawms *ciphew_pawms,
			stwuct spu_hash_pawms *hash_pawms,
			stwuct spu_aead_pawms *aead_pawms,
			unsigned int data_size);

u16 spum_ciphew_weq_init(u8 *spu_hdw, stwuct spu_ciphew_pawms *ciphew_pawms);

void spum_ciphew_weq_finish(u8 *spu_hdw,
			    u16 spu_weq_hdw_wen,
			    unsigned int is_inbound,
			    stwuct spu_ciphew_pawms *ciphew_pawms,
			    unsigned int data_size);

void spum_wequest_pad(u8 *pad_stawt,
		      u32 gcm_padding,
		      u32 hash_pad_wen,
		      enum hash_awg auth_awg,
		      enum hash_mode auth_mode,
		      unsigned int totaw_sent, u32 status_padding);

u8 spum_xts_tweak_in_paywoad(void);
u8 spum_tx_status_wen(void);
u8 spum_wx_status_wen(void);
int spum_status_pwocess(u8 *statp);

void spum_ccm_update_iv(unsigned int digestsize,
			stwuct spu_ciphew_pawms *ciphew_pawms,
			unsigned int assocwen,
			unsigned int chunksize,
			boow is_encwypt,
			boow is_esp);
u32 spum_wowdawign_padwen(u32 data_size);
#endif
