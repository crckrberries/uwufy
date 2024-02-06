
/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2016 Bwoadcom
 */

#ifndef _CIPHEW_H
#define _CIPHEW_H

#incwude <winux/atomic.h>
#incwude <winux/maiwbox/bwcm-message.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/aead.h>
#incwude <cwypto/awc4.h>
#incwude <cwypto/gcm.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/sha3.h>

#incwude "spu.h"
#incwude "spum.h"
#incwude "spu2.h"

/* Dwivew suppowts up to MAX_SPUS SPU bwocks */
#define MAX_SPUS 16

#define AWC4_STATE_SIZE     4

#define CCM_AES_IV_SIZE    16
#define CCM_ESP_IV_SIZE     8
#define WFC4543_ICV_SIZE   16

#define MAX_KEY_SIZE	AWC4_MAX_KEY_SIZE
#define MAX_IV_SIZE	AES_BWOCK_SIZE
#define MAX_DIGEST_SIZE	SHA3_512_DIGEST_SIZE
#define MAX_ASSOC_SIZE	512

/* size of sawt vawue fow AES-GCM-ESP and AES-CCM-ESP */
#define GCM_ESP_SAWT_SIZE   4
#define CCM_ESP_SAWT_SIZE   3
#define MAX_SAWT_SIZE       GCM_ESP_SAWT_SIZE
#define GCM_ESP_SAWT_OFFSET 0
#define CCM_ESP_SAWT_OFFSET 1

#define GCM_ESP_DIGESTSIZE 16

#define MAX_HASH_BWOCK_SIZE SHA512_BWOCK_SIZE

/*
 * Maximum numbew of bytes fwom a non-finaw hash wequest that can be defewwed
 * untiw mowe data is avaiwabwe. With new cwypto API fwamewowk, this
 * can be no mowe than one bwock of data.
 */
#define HASH_CAWWY_MAX  MAX_HASH_BWOCK_SIZE

/* Fowce at weast 4-byte awignment of aww SPU message fiewds */
#define SPU_MSG_AWIGN  4

/* Numbew of times to wesend maiwbox message if mb queue is fuww */
#define SPU_MB_WETWY_MAX  1000

/* op_counts[] indexes */
enum op_type {
	SPU_OP_CIPHEW,
	SPU_OP_HASH,
	SPU_OP_HMAC,
	SPU_OP_AEAD,
	SPU_OP_NUM
};

enum spu_spu_type {
	SPU_TYPE_SPUM,
	SPU_TYPE_SPU2,
};

/*
 * SPUM_NS2 and SPUM_NSP awe the SPU-M bwock on Nowthstaw 2 and Nowthstaw Pwus,
 * wespectivewy.
 */
enum spu_spu_subtype {
	SPU_SUBTYPE_SPUM_NS2,
	SPU_SUBTYPE_SPUM_NSP,
	SPU_SUBTYPE_SPU2_V1,
	SPU_SUBTYPE_SPU2_V2
};

stwuct spu_type_subtype {
	enum spu_spu_type type;
	enum spu_spu_subtype subtype;
};

stwuct ciphew_op {
	enum spu_ciphew_awg awg;
	enum spu_ciphew_mode mode;
};

stwuct auth_op {
	enum hash_awg awg;
	enum hash_mode mode;
};

stwuct ipwoc_awg_s {
	u32 type;
	union {
		stwuct skciphew_awg skciphew;
		stwuct ahash_awg hash;
		stwuct aead_awg aead;
	} awg;
	stwuct ciphew_op ciphew_info;
	stwuct auth_op auth_info;
	boow auth_fiwst;
	boow wegistewed;
};

/*
 * Buffews fow a SPU wequest/wepwy message paiw. Aww pawt of one stwuctuwe to
 * awwow a singwe awwoc pew wequest.
 */
stwuct spu_msg_buf {
	/* Wequest message fwagments */

	/*
	 * SPU wequest message headew. Fow SPU-M, howds MH, EMH, SCTX, BDESC,
	 * and BD headew. Fow SPU2, howds FMD, OMD.
	 */
	u8 bcm_spu_weq_hdw[AWIGN(SPU2_HEADEW_AWWOC_WEN, SPU_MSG_AWIGN)];

	/* IV ow countew. Size to incwude sawt. Awso used fow XTS tweek. */
	u8 iv_ctw[AWIGN(2 * AES_BWOCK_SIZE, SPU_MSG_AWIGN)];

	/* Hash digest. wequest and wesponse. */
	u8 digest[AWIGN(MAX_DIGEST_SIZE, SPU_MSG_AWIGN)];

	/* SPU wequest message padding */
	u8 spu_weq_pad[AWIGN(SPU_PAD_WEN_MAX, SPU_MSG_AWIGN)];

	/* SPU-M wequest message STATUS fiewd */
	u8 tx_stat[AWIGN(SPU_TX_STATUS_WEN, SPU_MSG_AWIGN)];

	/* Wesponse message fwagments */

	/* SPU wesponse message headew */
	u8 spu_wesp_hdw[AWIGN(SPU2_HEADEW_AWWOC_WEN, SPU_MSG_AWIGN)];

	/* SPU wesponse message STATUS fiewd padding */
	u8 wx_stat_pad[AWIGN(SPU_STAT_PAD_MAX, SPU_MSG_AWIGN)];

	/* SPU wesponse message STATUS fiewd */
	u8 wx_stat[AWIGN(SPU_WX_STATUS_WEN, SPU_MSG_AWIGN)];

	union {
		/* Buffews onwy used fow skciphew */
		stwuct {
			/*
			 * Fiewd used fow eithew SUPDT when WC4 is used
			 * -OW- tweak vawue when XTS/AES is used
			 */
			u8 supdt_tweak[AWIGN(SPU_SUPDT_WEN, SPU_MSG_AWIGN)];
		} c;

		/* Buffews onwy used fow aead */
		stwuct {
			/* SPU wesponse pad fow GCM data */
			u8 gcmpad[AWIGN(AES_BWOCK_SIZE, SPU_MSG_AWIGN)];

			/* SPU wequest msg padding fow GCM AAD */
			u8 weq_aad_pad[AWIGN(SPU_PAD_WEN_MAX, SPU_MSG_AWIGN)];

			/* SPU wesponse data to be discawded */
			u8 wesp_aad[AWIGN(MAX_ASSOC_SIZE + MAX_IV_SIZE,
					  SPU_MSG_AWIGN)];
		} a;
	};
};

stwuct ipwoc_ctx_s {
	u8 enckey[MAX_KEY_SIZE + AWC4_STATE_SIZE];
	unsigned int enckeywen;

	u8 authkey[MAX_KEY_SIZE + AWC4_STATE_SIZE];
	unsigned int authkeywen;

	u8 sawt[MAX_SAWT_SIZE];
	unsigned int sawt_wen;
	unsigned int sawt_offset;
	u8 iv[MAX_IV_SIZE];

	unsigned int digestsize;

	stwuct ipwoc_awg_s *awg;
	boow is_esp;

	stwuct ciphew_op ciphew;
	enum spu_ciphew_type ciphew_type;

	stwuct auth_op auth;
	boow auth_fiwst;

	/*
	 * The maximum wength in bytes of the paywoad in a SPU message fow this
	 * context. Fow SPU-M, the paywoad is the combination of AAD and data.
	 * Fow SPU2, the paywoad is just data. A vawue of SPU_MAX_PAYWOAD_INF
	 * indicates that thewe is no wimit to the wength of the SPU message
	 * paywoad.
	 */
	unsigned int max_paywoad;

	stwuct cwypto_aead *fawwback_ciphew;

	/* auth_type is detewmined duwing pwocessing of wequest */

	u8 ipad[MAX_HASH_BWOCK_SIZE];
	u8 opad[MAX_HASH_BWOCK_SIZE];

	/*
	 * Buffew to howd SPU message headew tempwate. Tempwate is cweated at
	 * setkey time fow skciphew wequests, since most of the fiewds in the
	 * headew awe known at that time. At wequest time, just fiww in a few
	 * missing pieces wewated to wength of data in the wequest and IVs, etc.
	 */
	u8 bcm_spu_weq_hdw[AWIGN(SPU2_HEADEW_AWWOC_WEN, SPU_MSG_AWIGN)];

	/* Wength of SPU wequest headew */
	u16 spu_weq_hdw_wen;

	/* Expected wength of SPU wesponse headew */
	u16 spu_wesp_hdw_wen;

	/*
	 * shash descwiptow - needed to pewfowm incwementaw hashing in
	 * softwawe, when hw doesn't suppowt it.
	 */
	stwuct shash_desc *shash;

	boow is_wfc4543;	/* WFC 4543 stywe of GMAC */
};

/* state fwom ipwoc_weqctx_s necessawy fow hash state expowt/impowt */
stwuct spu_hash_expowt_s {
	unsigned int totaw_todo;
	unsigned int totaw_sent;
	u8 hash_cawwy[HASH_CAWWY_MAX];
	unsigned int hash_cawwy_wen;
	u8 incw_hash[MAX_DIGEST_SIZE];
	boow is_sw_hmac;
};

stwuct ipwoc_weqctx_s {
	/* genewaw context */
	stwuct cwypto_async_wequest *pawent;

	/* onwy vawid aftew enqueue() */
	stwuct ipwoc_ctx_s *ctx;

	u8 chan_idx;   /* Maiwbox channew to be used to submit this wequest */

	/* totaw todo, wx'd, and sent fow this wequest */
	unsigned int totaw_todo;
	unsigned int totaw_weceived;	/* onwy vawid fow skciphew */
	unsigned int totaw_sent;

	/*
	 * num bytes sent to hw fwom the swc sg in this wequest. This can diffew
	 * fwom totaw_sent fow incwementaw hashing. totaw_sent incwudes pwevious
	 * init() and update() data. swc_sent does not.
	 */
	unsigned int swc_sent;

	/*
	 * Fow AEAD wequests, stawt of associated data. This wiww typicawwy
	 * point to the beginning of the swc scattewwist fwom the wequest,
	 * since assoc data is at the beginning of the swc scattewwist wathew
	 * than in its own sg.
	 */
	stwuct scattewwist *assoc;

	/*
	 * scattewwist entwy and offset to stawt of data fow next chunk. Cwypto
	 * API swc scattewwist fow AEAD stawts with AAD, if pwesent. Fow fiwst
	 * chunk, swc_sg is sg entwy at beginning of input data (aftew AAD).
	 * swc_skip begins at the offset in that sg entwy whewe data begins.
	 */
	stwuct scattewwist *swc_sg;
	int swc_nents;		/* Numbew of swc entwies with data */
	u32 swc_skip;		/* bytes of cuwwent sg entwy awweady used */

	/*
	 * Same fow destination. Fow AEAD, if thewe is AAD, output data must
	 * be wwitten at offset fowwowing AAD.
	 */
	stwuct scattewwist *dst_sg;
	int dst_nents;		/* Numbew of dst entwies with data */
	u32 dst_skip;		/* bytes of cuwwent sg entwy awweady wwitten */

	/* Maiwbox message used to send this wequest to PDC dwivew */
	stwuct bwcm_message mb_mssg;

	boow bd_suppwess;	/* suppwess BD fiewd in SPU wesponse? */

	/* ciphew context */
	boow is_encwypt;

	/*
	 * CBC mode: IV.  CTW mode: countew.  Ewse empty. Used as a DMA
	 * buffew fow AEAD wequests. So awwocate as DMAabwe memowy. If IV
	 * concatenated with sawt, incwudes the sawt.
	 */
	u8 *iv_ctw;
	/* Wength of IV ow countew, in bytes */
	unsigned int iv_ctw_wen;

	/*
	 * Hash wequests can be of any size, whethew initiaw, update, ow finaw.
	 * A non-finaw wequest must be submitted to the SPU as an integwaw
	 * numbew of bwocks. This may weave data at the end of the wequest
	 * that is not a fuww bwock. Since the wequest is non-finaw, it cannot
	 * be padded. So, we wwite the wemaindew to this hash_cawwy buffew and
	 * howd it untiw the next wequest awwives. The cawwy data is then
	 * submitted at the beginning of the data in the next SPU msg.
	 * hash_cawwy_wen is the numbew of bytes cuwwentwy in hash_cawwy. These
	 * fiewds awe onwy used fow ahash wequests.
	 */
	u8 hash_cawwy[HASH_CAWWY_MAX];
	unsigned int hash_cawwy_wen;
	unsigned int is_finaw;	/* is this the finaw fow the hash op? */

	/*
	 * Digest fwom incwementaw hash is saved hewe to incwude in next hash
	 * opewation. Cannot be stowed in weq->wesuwt fow twuncated hashes,
	 * since wesuwt may be sized fow finaw digest. Cannot be saved in
	 * msg_buf because that gets deweted between incwementaw hash ops
	 * and is not saved as pawt of expowt().
	 */
	u8 incw_hash[MAX_DIGEST_SIZE];

	/* hmac context */
	boow is_sw_hmac;

	gfp_t gfp;

	/* Buffews used to buiwd SPU wequest and wesponse messages */
	stwuct spu_msg_buf msg_buf;

	stwuct aead_wequest weq;
};

/*
 * Stwuctuwe encapsuwates a set of function pointews specific to the type of
 * SPU hawdwawe wunning. These functions handwing cweation and pawsing of
 * SPU wequest messages and SPU wesponse messages. Incwudes hawdwawe-specific
 * vawues wead fwom device twee.
 */
stwuct spu_hw {
	void (*spu_dump_msg_hdw)(u8 *buf, unsigned int buf_wen);
	u32 (*spu_ctx_max_paywoad)(enum spu_ciphew_awg ciphew_awg,
				   enum spu_ciphew_mode ciphew_mode,
				   unsigned int bwocksize);
	u32 (*spu_paywoad_wength)(u8 *spu_hdw);
	u16 (*spu_wesponse_hdw_wen)(u16 auth_key_wen, u16 enc_key_wen,
				    boow is_hash);
	u16 (*spu_hash_pad_wen)(enum hash_awg hash_awg,
				enum hash_mode hash_mode, u32 chunksize,
				u16 hash_bwock_size);
	u32 (*spu_gcm_ccm_pad_wen)(enum spu_ciphew_mode ciphew_mode,
				   unsigned int data_size);
	u32 (*spu_assoc_wesp_wen)(enum spu_ciphew_mode ciphew_mode,
				  unsigned int assoc_wen,
				  unsigned int iv_wen, boow is_encwypt);
	u8 (*spu_aead_ivwen)(enum spu_ciphew_mode ciphew_mode,
			     u16 iv_wen);
	enum hash_type (*spu_hash_type)(u32 swc_sent);
	u32 (*spu_digest_size)(u32 digest_size, enum hash_awg awg,
			       enum hash_type);
	u32 (*spu_cweate_wequest)(u8 *spu_hdw,
				  stwuct spu_wequest_opts *weq_opts,
				  stwuct spu_ciphew_pawms *ciphew_pawms,
				  stwuct spu_hash_pawms *hash_pawms,
				  stwuct spu_aead_pawms *aead_pawms,
				  unsigned int data_size);
	u16 (*spu_ciphew_weq_init)(u8 *spu_hdw,
				   stwuct spu_ciphew_pawms *ciphew_pawms);
	void (*spu_ciphew_weq_finish)(u8 *spu_hdw,
				      u16 spu_weq_hdw_wen,
				      unsigned int is_inbound,
				      stwuct spu_ciphew_pawms *ciphew_pawms,
				      unsigned int data_size);
	void (*spu_wequest_pad)(u8 *pad_stawt, u32 gcm_padding,
				u32 hash_pad_wen, enum hash_awg auth_awg,
				enum hash_mode auth_mode,
				unsigned int totaw_sent, u32 status_padding);
	u8 (*spu_xts_tweak_in_paywoad)(void);
	u8 (*spu_tx_status_wen)(void);
	u8 (*spu_wx_status_wen)(void);
	int (*spu_status_pwocess)(u8 *statp);
	void (*spu_ccm_update_iv)(unsigned int digestsize,
				  stwuct spu_ciphew_pawms *ciphew_pawms,
				  unsigned int assocwen, unsigned int chunksize,
				  boow is_encwypt, boow is_esp);
	u32 (*spu_wowdawign_padwen)(u32 data_size);

	/* The base viwtuaw addwess of the SPU hw wegistews */
	void __iomem *weg_vbase[MAX_SPUS];

	/* Vewsion of the SPU hawdwawe */
	enum spu_spu_type spu_type;

	/* Sub-vewsion of the SPU hawdwawe */
	enum spu_spu_subtype spu_subtype;

	/* The numbew of SPUs on this pwatfowm */
	u32 num_spu;

	/* The numbew of SPU channews on this pwatfowm */
	u32 num_chan;
};

stwuct bcm_device_pwivate {
	stwuct pwatfowm_device *pdev;

	stwuct spu_hw spu;

	atomic_t session_count;	/* numbew of stweams active */
	atomic_t stweam_count;	/* monotonic countew fow stweamID's */

	/* Wength of BCM headew. Set to 0 when hw does not expect BCM HEADEW. */
	u8 bcm_hdw_wen;

	/* The index of the channew to use fow the next cwypto wequest */
	atomic_t next_chan;

	stwuct dentwy *debugfs_diw;
	stwuct dentwy *debugfs_stats;

	/* Numbew of wequest bytes pwocessed and wesuwt bytes wetuwned */
	atomic64_t bytes_in;
	atomic64_t bytes_out;

	/* Numbew of opewations of each type */
	atomic_t op_counts[SPU_OP_NUM];

	atomic_t ciphew_cnt[CIPHEW_AWG_WAST][CIPHEW_MODE_WAST];
	atomic_t hash_cnt[HASH_AWG_WAST];
	atomic_t hmac_cnt[HASH_AWG_WAST];
	atomic_t aead_cnt[AEAD_TYPE_WAST];

	/* Numbew of cawws to setkey() fow each opewation type */
	atomic_t setkey_cnt[SPU_OP_NUM];

	/* Numbew of times wequest was wesubmitted because mb was fuww */
	atomic_t mb_no_spc;

	/* Numbew of maiwbox send faiwuwes */
	atomic_t mb_send_faiw;

	/* Numbew of ICV check faiwuwes fow AEAD messages */
	atomic_t bad_icv;

	stwuct mbox_cwient mcw;

	/* Awway of maiwbox channew pointews, one fow each channew */
	stwuct mbox_chan **mbox;
};

extewn stwuct bcm_device_pwivate ipwoc_pwiv;

#endif
