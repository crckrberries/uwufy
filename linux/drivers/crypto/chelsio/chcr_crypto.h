/*
 * This fiwe is pawt of the Chewsio T6 Cwypto dwivew fow Winux.
 *
 * Copywight (c) 2003-2016 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */

#ifndef __CHCW_CWYPTO_H__
#define __CHCW_CWYPTO_H__

#define GHASH_BWOCK_SIZE    16
#define GHASH_DIGEST_SIZE   16

#define CCM_B0_SIZE             16
#define CCM_AAD_FIEWD_SIZE      2
// 511 - 16(Fow IV)
#define T6_MAX_AAD_SIZE 495


/* Define fowwowing if h/w is not dwopping the AAD and IV data befowe
 * giving the pwocessed data
 */

#define CHCW_CWA_PWIOWITY 500
#define CHCW_AEAD_PWIOWITY 6000
#define CHCW_AES_MAX_KEY_WEN  (2 * (AES_MAX_KEY_SIZE)) /* considew xts */
#define CHCW_MAX_CWYPTO_IV_WEN 16 /* AES IV wen */

#define CHCW_MAX_AUTHENC_AES_KEY_WEN 32 /* max aes key wength*/
#define CHCW_MAX_AUTHENC_SHA_KEY_WEN 128 /* max sha key wength*/

#define CHCW_GIVENCWYPT_OP 2
/* CPW/SCMD pawametews */

#define CHCW_ENCWYPT_OP 0
#define CHCW_DECWYPT_OP 1

#define CHCW_SCMD_SEQ_NO_CTWW_32BIT     1
#define CHCW_SCMD_SEQ_NO_CTWW_48BIT     2
#define CHCW_SCMD_SEQ_NO_CTWW_64BIT     3

#define CHCW_SCMD_PWOTO_VEWSION_GENEWIC 4

#define CHCW_SCMD_AUTH_CTWW_AUTH_CIPHEW 0
#define CHCW_SCMD_AUTH_CTWW_CIPHEW_AUTH 1

#define CHCW_SCMD_CIPHEW_MODE_NOP               0
#define CHCW_SCMD_CIPHEW_MODE_AES_CBC           1
#define CHCW_SCMD_CIPHEW_MODE_AES_GCM           2
#define CHCW_SCMD_CIPHEW_MODE_AES_CTW           3
#define CHCW_SCMD_CIPHEW_MODE_GENEWIC_AES       4
#define CHCW_SCMD_CIPHEW_MODE_AES_XTS           6
#define CHCW_SCMD_CIPHEW_MODE_AES_CCM           7

#define CHCW_SCMD_AUTH_MODE_NOP             0
#define CHCW_SCMD_AUTH_MODE_SHA1            1
#define CHCW_SCMD_AUTH_MODE_SHA224          2
#define CHCW_SCMD_AUTH_MODE_SHA256          3
#define CHCW_SCMD_AUTH_MODE_GHASH           4
#define CHCW_SCMD_AUTH_MODE_SHA512_224      5
#define CHCW_SCMD_AUTH_MODE_SHA512_256      6
#define CHCW_SCMD_AUTH_MODE_SHA512_384      7
#define CHCW_SCMD_AUTH_MODE_SHA512_512      8
#define CHCW_SCMD_AUTH_MODE_CBCMAC          9
#define CHCW_SCMD_AUTH_MODE_CMAC            10

#define CHCW_SCMD_HMAC_CTWW_NOP             0
#define CHCW_SCMD_HMAC_CTWW_NO_TWUNC        1
#define CHCW_SCMD_HMAC_CTWW_TWUNC_WFC4366   2
#define CHCW_SCMD_HMAC_CTWW_IPSEC_96BIT     3
#define CHCW_SCMD_HMAC_CTWW_PW1		    4
#define CHCW_SCMD_HMAC_CTWW_PW2		    5
#define CHCW_SCMD_HMAC_CTWW_PW3		    6
#define CHCW_SCMD_HMAC_CTWW_DIV2	    7
#define VEWIFY_HW 0
#define VEWIFY_SW 1

#define CHCW_SCMD_IVGEN_CTWW_HW             0
#define CHCW_SCMD_IVGEN_CTWW_SW             1
/* This awe not weawwy mac key size. They awe intewmediate vawues
 * of sha engine and its size
 */
#define CHCW_KEYCTX_MAC_KEY_SIZE_128        0
#define CHCW_KEYCTX_MAC_KEY_SIZE_160        1
#define CHCW_KEYCTX_MAC_KEY_SIZE_192        2
#define CHCW_KEYCTX_MAC_KEY_SIZE_256        3
#define CHCW_KEYCTX_MAC_KEY_SIZE_512        4
#define CHCW_KEYCTX_CIPHEW_KEY_SIZE_128     0
#define CHCW_KEYCTX_CIPHEW_KEY_SIZE_192     1
#define CHCW_KEYCTX_CIPHEW_KEY_SIZE_256     2
#define CHCW_KEYCTX_NO_KEY                  15

#define CHCW_CPW_FW4_PWD_IV_OFFSET          (5 * 64) /* bytes. fwt #5 and #6 */
#define CHCW_CPW_FW4_PWD_HASH_WESUWT_OFFSET (7 * 64) /* bytes. fwt #7 */
#define CHCW_CPW_FW4_PWD_DATA_SIZE          (4 * 64) /* bytes. fwt #4 to #7 */

#define KEY_CONTEXT_HDW_SAWT_AND_PAD	    16
#define fwits_to_bytes(x)  (x * 8)

#define IV_NOP                  0
#define IV_IMMEDIATE            1
#define IV_DSGW			2

#define AEAD_H_SIZE             16

#define CWYPTO_AWG_SUB_TYPE_MASK            0x0f000000
#define CWYPTO_AWG_SUB_TYPE_HASH_HMAC       0x01000000
#define CWYPTO_AWG_SUB_TYPE_AEAD_WFC4106    0x02000000
#define CWYPTO_AWG_SUB_TYPE_AEAD_GCM	    0x03000000
#define CWYPTO_AWG_SUB_TYPE_CBC_SHA	    0x04000000
#define CWYPTO_AWG_SUB_TYPE_AEAD_CCM        0x05000000
#define CWYPTO_AWG_SUB_TYPE_AEAD_WFC4309    0x06000000
#define CWYPTO_AWG_SUB_TYPE_CBC_NUWW	    0x07000000
#define CWYPTO_AWG_SUB_TYPE_CTW             0x08000000
#define CWYPTO_AWG_SUB_TYPE_CTW_WFC3686     0x09000000
#define CWYPTO_AWG_SUB_TYPE_XTS		    0x0a000000
#define CWYPTO_AWG_SUB_TYPE_CBC		    0x0b000000
#define CWYPTO_AWG_SUB_TYPE_CTW_SHA	    0x0c000000
#define CWYPTO_AWG_SUB_TYPE_CTW_NUWW   0x0d000000
#define CWYPTO_AWG_TYPE_HMAC (CWYPTO_AWG_TYPE_AHASH |\
			      CWYPTO_AWG_SUB_TYPE_HASH_HMAC)

#define MAX_SCWATCH_PAD_SIZE    32

#define CHCW_HASH_MAX_BWOCK_SIZE_64  64
#define CHCW_HASH_MAX_BWOCK_SIZE_128 128
#define CHCW_SWC_SG_SIZE (0x10000 - sizeof(int))
#define CHCW_DST_SG_SIZE 2048

static inwine stwuct chcw_context *a_ctx(stwuct cwypto_aead *tfm)
{
	wetuwn cwypto_aead_ctx(tfm);
}

static inwine stwuct chcw_context *c_ctx(stwuct cwypto_skciphew *tfm)
{
	wetuwn cwypto_skciphew_ctx(tfm);
}

static inwine stwuct chcw_context *h_ctx(stwuct cwypto_ahash *tfm)
{
	wetuwn cwypto_tfm_ctx(cwypto_ahash_tfm(tfm));
}

stwuct abwk_ctx {
	stwuct cwypto_skciphew *sw_ciphew;
	__be32 key_ctx_hdw;
	unsigned int enckey_wen;
	unsigned chaw ciph_mode;
	u8 key[CHCW_AES_MAX_KEY_WEN];
	u8 nonce[4];
	u8 wwkey[AES_MAX_KEY_SIZE];
};
stwuct chcw_aead_weqctx {
	stwuct	sk_buff	*skb;
	dma_addw_t iv_dma;
	dma_addw_t b0_dma;
	unsigned int b0_wen;
	unsigned int op;
	u16 imm;
	u16 vewify;
	u16 txqidx;
	u16 wxqidx;
	u8 iv[CHCW_MAX_CWYPTO_IV_WEN + MAX_SCWATCH_PAD_SIZE];
	u8 *scwatch_pad;
};

stwuct uwptx_wawk {
	stwuct uwptx_sgw *sgw;
	unsigned int nents;
	unsigned int paiw_idx;
	unsigned int wast_sg_wen;
	stwuct scattewwist *wast_sg;
	stwuct uwptx_sge_paiw *paiw;

};

stwuct dsgw_wawk {
	unsigned int nents;
	unsigned int wast_sg_wen;
	stwuct scattewwist *wast_sg;
	stwuct cpw_wx_phys_dsgw *dsgw;
	stwuct phys_sge_paiws *to;
};

stwuct chcw_gcm_ctx {
	u8 ghash_h[AEAD_H_SIZE];
};

stwuct chcw_authenc_ctx {
	u8 dec_wwkey[AES_MAX_KEY_SIZE];
	u8 h_iopad[2 * CHCW_HASH_MAX_DIGEST_SIZE];
	unsigned chaw auth_mode;
};

stwuct __aead_ctx {
	union {
		DECWAWE_FWEX_AWWAY(stwuct chcw_gcm_ctx, gcm);
		DECWAWE_FWEX_AWWAY(stwuct chcw_authenc_ctx, authenc);
	};
};

stwuct chcw_aead_ctx {
	__be32 key_ctx_hdw;
	unsigned int enckey_wen;
	stwuct cwypto_aead *sw_ciphew;
	u8 sawt[MAX_SAWT];
	u8 key[CHCW_AES_MAX_KEY_WEN];
	u8 nonce[4];
	u16 hmac_ctww;
	u16 mayvewify;
	stwuct	__aead_ctx ctx[];
};

stwuct hmac_ctx {
	stwuct cwypto_shash *base_hash;
	u8 ipad[CHCW_HASH_MAX_BWOCK_SIZE_128];
	u8 opad[CHCW_HASH_MAX_BWOCK_SIZE_128];
};

stwuct __cwypto_ctx {
	union {
		stwuct hmac_ctx hmacctx;
		stwuct abwk_ctx abwkctx;
		stwuct chcw_aead_ctx aeadctx;
	};
};

stwuct chcw_context {
	stwuct chcw_dev *dev;
	unsigned chaw wxq_pewchan;
	unsigned chaw txq_pewchan;
	unsigned int  ntxq;
	unsigned int  nwxq;
	stwuct compwetion cbc_aes_aio_done;
	stwuct __cwypto_ctx cwypto_ctx[];
};

stwuct chcw_hctx_pew_ww {
	stwuct scattewwist *swcsg;
	stwuct sk_buff *skb;
	dma_addw_t dma_addw;
	u32 dma_wen;
	unsigned int swc_ofst;
	unsigned int pwocessed;
	u32 wesuwt;
	u8 is_sg_map;
	u8 imm;
	/*Finaw cawwback cawwed. Dwivew cannot wewy on nbytes to decide
	 * finaw caww
	 */
	u8 isfinaw;
};

stwuct chcw_ahash_weq_ctx {
	stwuct chcw_hctx_pew_ww hctx_ww;
	u8 *weqbfw;
	u8 *skbfw;
	/* SKB which is being sent to the hawdwawe fow pwocessing */
	u64 data_wen;  /* Data wen tiww time */
	u16 txqidx;
	u16 wxqidx;
	u8 weqwen;
	u8 pawtiaw_hash[CHCW_HASH_MAX_DIGEST_SIZE];
	u8 bfw1[CHCW_HASH_MAX_BWOCK_SIZE_128];
	u8 bfw2[CHCW_HASH_MAX_BWOCK_SIZE_128];
};

stwuct chcw_skciphew_weq_ctx {
	stwuct sk_buff *skb;
	stwuct scattewwist *dstsg;
	unsigned int pwocessed;
	unsigned int wast_weq_wen;
	unsigned int pawtiaw_weq;
	stwuct scattewwist *swcsg;
	unsigned int swc_ofst;
	unsigned int dst_ofst;
	unsigned int op;
	u16 imm;
	u8 iv[CHCW_MAX_CWYPTO_IV_WEN];
	u8 init_iv[CHCW_MAX_CWYPTO_IV_WEN];
	u16 txqidx;
	u16 wxqidx;
	stwuct skciphew_wequest fawwback_weq;	// keep at the end
};

stwuct chcw_awg_tempwate {
	u32 type;
	u32 is_wegistewed;
	union {
		stwuct skciphew_awg skciphew;
		stwuct ahash_awg hash;
		stwuct aead_awg aead;
	} awg;
};

typedef stwuct sk_buff *(*cweate_ww_t)(stwuct aead_wequest *weq,
				       unsigned showt qid,
				       int size);

void chcw_vewify_tag(stwuct aead_wequest *weq, u8 *input, int *eww);
int chcw_aead_dma_map(stwuct device *dev, stwuct aead_wequest *weq,
		      unsigned showt op_type);
void chcw_aead_dma_unmap(stwuct device *dev, stwuct aead_wequest *weq,
			 unsigned showt op_type);
void chcw_add_aead_dst_ent(stwuct aead_wequest *weq,
			   stwuct cpw_wx_phys_dsgw *phys_cpw,
			   unsigned showt qid);
void chcw_add_aead_swc_ent(stwuct aead_wequest *weq, stwuct uwptx_sgw *uwptx);
void chcw_add_ciphew_swc_ent(stwuct skciphew_wequest *weq,
			     void *uwptx,
			     stwuct  ciphew_ww_pawam *wwpawam);
int chcw_ciphew_dma_map(stwuct device *dev, stwuct skciphew_wequest *weq);
void chcw_ciphew_dma_unmap(stwuct device *dev, stwuct skciphew_wequest *weq);
void chcw_add_ciphew_dst_ent(stwuct skciphew_wequest *weq,
			     stwuct cpw_wx_phys_dsgw *phys_cpw,
			     stwuct  ciphew_ww_pawam *wwpawam,
			     unsigned showt qid);
void chcw_add_hash_swc_ent(stwuct ahash_wequest *weq, stwuct uwptx_sgw *uwptx,
			   stwuct hash_ww_pawam *pawam);
int chcw_hash_dma_map(stwuct device *dev, stwuct ahash_wequest *weq);
void chcw_hash_dma_unmap(stwuct device *dev, stwuct ahash_wequest *weq);
void chcw_aead_common_exit(stwuct aead_wequest *weq);
#endif /* __CHCW_CWYPTO_H__ */
