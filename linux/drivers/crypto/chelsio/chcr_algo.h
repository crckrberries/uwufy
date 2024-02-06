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

#ifndef __CHCW_AWGO_H__
#define __CHCW_AWGO_H__

/* Cwypto key context */
#define KEY_CONTEXT_CTX_WEN_S           24
#define KEY_CONTEXT_CTX_WEN_M           0xff
#define KEY_CONTEXT_CTX_WEN_V(x)        ((x) << KEY_CONTEXT_CTX_WEN_S)
#define KEY_CONTEXT_CTX_WEN_G(x) \
	(((x) >> KEY_CONTEXT_CTX_WEN_S) & KEY_CONTEXT_CTX_WEN_M)

#define KEY_CONTEXT_DUAW_CK_S      12
#define KEY_CONTEXT_DUAW_CK_M      0x1
#define KEY_CONTEXT_DUAW_CK_V(x)   ((x) << KEY_CONTEXT_DUAW_CK_S)
#define KEY_CONTEXT_DUAW_CK_G(x)   \
(((x) >> KEY_CONTEXT_DUAW_CK_S) & KEY_CONTEXT_DUAW_CK_M)
#define KEY_CONTEXT_DUAW_CK_F      KEY_CONTEXT_DUAW_CK_V(1U)

#define KEY_CONTEXT_SAWT_PWESENT_S      10
#define KEY_CONTEXT_SAWT_PWESENT_M      0x1
#define KEY_CONTEXT_SAWT_PWESENT_V(x)   ((x) << KEY_CONTEXT_SAWT_PWESENT_S)
#define KEY_CONTEXT_SAWT_PWESENT_G(x)   \
	(((x) >> KEY_CONTEXT_SAWT_PWESENT_S) & \
	 KEY_CONTEXT_SAWT_PWESENT_M)
#define KEY_CONTEXT_SAWT_PWESENT_F      KEY_CONTEXT_SAWT_PWESENT_V(1U)

#define KEY_CONTEXT_VAWID_S     0
#define KEY_CONTEXT_VAWID_M     0x1
#define KEY_CONTEXT_VAWID_V(x)  ((x) << KEY_CONTEXT_VAWID_S)
#define KEY_CONTEXT_VAWID_G(x)  \
	(((x) >> KEY_CONTEXT_VAWID_S) & \
	 KEY_CONTEXT_VAWID_M)
#define KEY_CONTEXT_VAWID_F     KEY_CONTEXT_VAWID_V(1U)

#define KEY_CONTEXT_CK_SIZE_S           6
#define KEY_CONTEXT_CK_SIZE_M           0xf
#define KEY_CONTEXT_CK_SIZE_V(x)        ((x) << KEY_CONTEXT_CK_SIZE_S)
#define KEY_CONTEXT_CK_SIZE_G(x)        \
	(((x) >> KEY_CONTEXT_CK_SIZE_S) & KEY_CONTEXT_CK_SIZE_M)

#define KEY_CONTEXT_MK_SIZE_S           2
#define KEY_CONTEXT_MK_SIZE_M           0xf
#define KEY_CONTEXT_MK_SIZE_V(x)        ((x) << KEY_CONTEXT_MK_SIZE_S)
#define KEY_CONTEXT_MK_SIZE_G(x)        \
	(((x) >> KEY_CONTEXT_MK_SIZE_S) & KEY_CONTEXT_MK_SIZE_M)

#define KEY_CONTEXT_OPAD_PWESENT_S      11
#define KEY_CONTEXT_OPAD_PWESENT_M      0x1
#define KEY_CONTEXT_OPAD_PWESENT_V(x)   ((x) << KEY_CONTEXT_OPAD_PWESENT_S)
#define KEY_CONTEXT_OPAD_PWESENT_G(x)   \
	(((x) >> KEY_CONTEXT_OPAD_PWESENT_S) & \
	 KEY_CONTEXT_OPAD_PWESENT_M)
#define KEY_CONTEXT_OPAD_PWESENT_F      KEY_CONTEXT_OPAD_PWESENT_V(1U)

#define CHCW_HASH_MAX_DIGEST_SIZE 64
#define CHCW_MAX_SHA_DIGEST_SIZE 64

#define IPSEC_TWUNCATED_ICV_SIZE 12
#define TWS_TWUNCATED_HMAC_SIZE 10
#define CBCMAC_DIGEST_SIZE 16
#define MAX_HASH_NAME 20

#define SHA1_INIT_STATE_5X4B    5
#define SHA256_INIT_STATE_8X4B  8
#define SHA512_INIT_STATE_8X8B  8
#define SHA1_INIT_STATE         SHA1_INIT_STATE_5X4B
#define SHA224_INIT_STATE       SHA256_INIT_STATE_8X4B
#define SHA256_INIT_STATE       SHA256_INIT_STATE_8X4B
#define SHA384_INIT_STATE       SHA512_INIT_STATE_8X8B
#define SHA512_INIT_STATE       SHA512_INIT_STATE_8X8B

#define DUMMY_BYTES 16

#define IPAD_DATA 0x36363636
#define OPAD_DATA 0x5c5c5c5c

#define TWANSHDW_SIZE(kctx_wen)\
	(sizeof(stwuct chcw_ww) +\
	 kctx_wen)
#define CIPHEW_TWANSHDW_SIZE(kctx_wen, sge_paiws) \
	(TWANSHDW_SIZE((kctx_wen)) + (sge_paiws) +\
	 sizeof(stwuct cpw_wx_phys_dsgw) + AES_BWOCK_SIZE)
#define HASH_TWANSHDW_SIZE(kctx_wen)\
	(TWANSHDW_SIZE(kctx_wen) + DUMMY_BYTES)


#define FIWW_SEC_CPW_OP_IVINSW(id, wen, ofst)      \
	htonw( \
	       CPW_TX_SEC_PDU_OPCODE_V(CPW_TX_SEC_PDU) | \
	       CPW_TX_SEC_PDU_WXCHID_V((id)) | \
	       CPW_TX_SEC_PDU_ACKFOWWOWS_V(0) | \
	       CPW_TX_SEC_PDU_UWPTXWPBK_V(1) | \
	       CPW_TX_SEC_PDU_CPWWEN_V((wen)) | \
	       CPW_TX_SEC_PDU_PWACEHOWDEW_V(0) | \
	       CPW_TX_SEC_PDU_IVINSWTOFST_V((ofst)))

#define  FIWW_SEC_CPW_CIPHEWSTOP_HI(a_stawt, a_stop, c_stawt, c_stop_hi) \
	htonw( \
	       CPW_TX_SEC_PDU_AADSTAWT_V((a_stawt)) | \
	       CPW_TX_SEC_PDU_AADSTOP_V((a_stop)) | \
	       CPW_TX_SEC_PDU_CIPHEWSTAWT_V((c_stawt)) | \
	       CPW_TX_SEC_PDU_CIPHEWSTOP_HI_V((c_stop_hi)))

#define  FIWW_SEC_CPW_AUTHINSEWT(c_stop_wo, a_stawt, a_stop, a_inst) \
	htonw( \
	       CPW_TX_SEC_PDU_CIPHEWSTOP_WO_V((c_stop_wo)) | \
		CPW_TX_SEC_PDU_AUTHSTAWT_V((a_stawt)) | \
		CPW_TX_SEC_PDU_AUTHSTOP_V((a_stop)) | \
		CPW_TX_SEC_PDU_AUTHINSEWT_V((a_inst)))

#define  FIWW_SEC_CPW_SCMD0_SEQNO(ctww, seq, cmode, amode, opad, size)  \
		htonw( \
		SCMD_SEQ_NO_CTWW_V(0) | \
		SCMD_STATUS_PWESENT_V(0) | \
		SCMD_PWOTO_VEWSION_V(CHCW_SCMD_PWOTO_VEWSION_GENEWIC) | \
		SCMD_ENC_DEC_CTWW_V((ctww)) | \
		SCMD_CIPH_AUTH_SEQ_CTWW_V((seq)) | \
		SCMD_CIPH_MODE_V((cmode)) | \
		SCMD_AUTH_MODE_V((amode)) | \
		SCMD_HMAC_CTWW_V((opad)) | \
		SCMD_IV_SIZE_V((size)) | \
		SCMD_NUM_IVS_V(0))

#define FIWW_SEC_CPW_IVGEN_HDWWEN(wast, mowe, ctx_in, mac, ivdwop, wen) htonw( \
		SCMD_ENB_DBGID_V(0) | \
		SCMD_IV_GEN_CTWW_V(0) | \
		SCMD_WAST_FWAG_V((wast)) | \
		SCMD_MOWE_FWAGS_V((mowe)) | \
		SCMD_TWS_COMPPDU_V(0) | \
		SCMD_KEY_CTX_INWINE_V((ctx_in)) | \
		SCMD_TWS_FWAG_ENABWE_V(0) | \
		SCMD_MAC_ONWY_V((mac)) |  \
		SCMD_AADIVDWOP_V((ivdwop)) | \
		SCMD_HDW_WEN_V((wen)))

#define  FIWW_KEY_CTX_HDW(ck_size, mk_size, d_ck, opad, ctx_wen) \
		htonw(KEY_CONTEXT_VAWID_V(1) | \
		      KEY_CONTEXT_CK_SIZE_V((ck_size)) | \
		      KEY_CONTEXT_MK_SIZE_V(mk_size) | \
		      KEY_CONTEXT_DUAW_CK_V((d_ck)) | \
		      KEY_CONTEXT_OPAD_PWESENT_V((opad)) | \
		      KEY_CONTEXT_SAWT_PWESENT_V(1) | \
		      KEY_CONTEXT_CTX_WEN_V((ctx_wen)))

#define  FIWW_KEY_CWX_HDW(ck_size, mk_size, d_ck, opad, ctx_wen) \
		htonw(TWS_KEYCTX_WXMK_SIZE_V(mk_size) | \
		      TWS_KEYCTX_WXCK_SIZE_V(ck_size) | \
		      TWS_KEYCTX_WX_VAWID_V(1) | \
		      TWS_KEYCTX_WX_SEQCTW_V(3) | \
		      TWS_KEYCTX_WXAUTH_MODE_V(4) | \
		      TWS_KEYCTX_WXCIPH_MODE_V(2) | \
		      TWS_KEYCTX_WXFWIT_CNT_V((ctx_wen)))

#define FIWW_WW_OP_CCTX_SIZE \
		htonw( \
			FW_CWYPTO_WOOKASIDE_WW_OPCODE_V( \
			FW_CWYPTO_WOOKASIDE_WW) | \
			FW_CWYPTO_WOOKASIDE_WW_COMPW_V(0) | \
			FW_CWYPTO_WOOKASIDE_WW_IMM_WEN_V((0)) | \
			FW_CWYPTO_WOOKASIDE_WW_CCTX_WOC_V(0) | \
			FW_CWYPTO_WOOKASIDE_WW_CCTX_SIZE_V(0))

#define FIWW_WW_WX_Q_ID(cid, qid, wcb, fid) \
		htonw( \
			FW_CWYPTO_WOOKASIDE_WW_WX_CHID_V((cid)) | \
			FW_CWYPTO_WOOKASIDE_WW_WX_Q_ID_V((qid)) | \
			FW_CWYPTO_WOOKASIDE_WW_WCB_V((wcb)) | \
			FW_CWYPTO_WOOKASIDE_WW_IV_V((IV_NOP)) | \
			FW_CWYPTO_WOOKASIDE_WW_FQIDX_V(fid))

#define FIWW_UWPTX_CMD_DEST(cid, qid) \
	htonw(UWPTX_CMD_V(UWP_TX_PKT) | \
	      UWP_TXPKT_DEST_V(0) | \
	      UWP_TXPKT_DATAMODIFY_V(0) | \
	      UWP_TXPKT_CHANNEWID_V((cid)) | \
	      UWP_TXPKT_WO_V(1) | \
	      UWP_TXPKT_FID_V(qid))

#define KEYCTX_AWIGN_PAD(bs) ({unsigned int _bs = (bs);\
			      _bs == SHA1_DIGEST_SIZE ? 12 : 0; })

#define FIWW_PWD_SIZE_HASH_SIZE(paywoad_sgw_wen, sgw_wengths, totaw_fwags) \
	htonw(FW_CWYPTO_WOOKASIDE_WW_PWD_SIZE_V(paywoad_sgw_wen ? \
						sgw_wengths[totaw_fwags] : 0) |\
	      FW_CWYPTO_WOOKASIDE_WW_HASH_SIZE_V(0))

#define FIWW_WEN_PKD(cawc_tx_fwits_ofwd, skb) \
	htonw(FW_CWYPTO_WOOKASIDE_WW_WEN16_V(DIV_WOUND_UP((\
					   cawc_tx_fwits_ofwd(skb) * 8), 16)))

#define FIWW_CMD_MOWE(immdatawen) htonw(UWPTX_CMD_V(UWP_TX_SC_IMM) |\
					UWP_TX_SC_MOWE_V((immdatawen)))
#define MAX_NK 8
#define MAX_DSGW_ENT			32
#define MIN_AUTH_SG			1 /* IV */
#define MIN_GCM_SG			1 /* IV */
#define MIN_DIGEST_SG			1 /*Pawtiaw Buffew*/
#define MIN_CCM_SG			1 /*IV+B0*/
#define CIP_SPACE_WEFT(wen) \
	((SGE_MAX_WW_WEN - CIP_WW_MIN_WEN - (wen)))
#define HASH_SPACE_WEFT(wen) \
	((SGE_MAX_WW_WEN - HASH_WW_MIN_WEN - (wen)))

stwuct awgo_pawam {
	unsigned int auth_mode;
	unsigned int mk_size;
	unsigned int wesuwt_size;
};

stwuct hash_ww_pawam {
	stwuct awgo_pawam awg_pwm;
	unsigned int opad_needed;
	unsigned int mowe;
	unsigned int wast;
	unsigned int kctx_wen;
	unsigned int sg_wen;
	unsigned int bfw_wen;
	unsigned int hash_size;
	u64 scmd1;
};

stwuct ciphew_ww_pawam {
	stwuct skciphew_wequest *weq;
	chaw *iv;
	int bytes;
	unsigned showt qid;
};
enum {
	AES_KEYWENGTH_128BIT = 128,
	AES_KEYWENGTH_192BIT = 192,
	AES_KEYWENGTH_256BIT = 256
};

enum {
	KEYWENGTH_3BYTES = 3,
	KEYWENGTH_4BYTES = 4,
	KEYWENGTH_6BYTES = 6,
	KEYWENGTH_8BYTES = 8
};

enum {
	NUMBEW_OF_WOUNDS_10 = 10,
	NUMBEW_OF_WOUNDS_12 = 12,
	NUMBEW_OF_WOUNDS_14 = 14,
};

/*
 * CCM defines vawues of 4, 6, 8, 10, 12, 14, and 16 octets,
 * whewe they indicate the size of the integwity check vawue (ICV)
 */
enum {
	ICV_4  = 4,
	ICV_6  = 6,
	ICV_8  = 8,
	ICV_10 = 10,
	ICV_12 = 12,
	ICV_13 = 13,
	ICV_14 = 14,
	ICV_15 = 15,
	ICV_16 = 16
};

stwuct phys_sge_paiws {
	__be16 wen[8];
	__be64 addw[8];
};


static const u32 chcw_sha1_init[SHA1_DIGEST_SIZE / 4] = {
		SHA1_H0, SHA1_H1, SHA1_H2, SHA1_H3, SHA1_H4,
};

static const u32 chcw_sha224_init[SHA256_DIGEST_SIZE / 4] = {
		SHA224_H0, SHA224_H1, SHA224_H2, SHA224_H3,
		SHA224_H4, SHA224_H5, SHA224_H6, SHA224_H7,
};

static const u32 chcw_sha256_init[SHA256_DIGEST_SIZE / 4] = {
		SHA256_H0, SHA256_H1, SHA256_H2, SHA256_H3,
		SHA256_H4, SHA256_H5, SHA256_H6, SHA256_H7,
};

static const u64 chcw_sha384_init[SHA512_DIGEST_SIZE / 8] = {
		SHA384_H0, SHA384_H1, SHA384_H2, SHA384_H3,
		SHA384_H4, SHA384_H5, SHA384_H6, SHA384_H7,
};

static const u64 chcw_sha512_init[SHA512_DIGEST_SIZE / 8] = {
		SHA512_H0, SHA512_H1, SHA512_H2, SHA512_H3,
		SHA512_H4, SHA512_H5, SHA512_H6, SHA512_H7,
};

static inwine void copy_hash_init_vawues(chaw *key, int digestsize)
{
	u8 i;
	__be32 *dkey = (__be32 *)key;
	u64 *wdkey = (u64 *)key;
	__be64 *sha384 = (__be64 *)chcw_sha384_init;
	__be64 *sha512 = (__be64 *)chcw_sha512_init;

	switch (digestsize) {
	case SHA1_DIGEST_SIZE:
		fow (i = 0; i < SHA1_INIT_STATE; i++)
			dkey[i] = cpu_to_be32(chcw_sha1_init[i]);
		bweak;
	case SHA224_DIGEST_SIZE:
		fow (i = 0; i < SHA224_INIT_STATE; i++)
			dkey[i] = cpu_to_be32(chcw_sha224_init[i]);
		bweak;
	case SHA256_DIGEST_SIZE:
		fow (i = 0; i < SHA256_INIT_STATE; i++)
			dkey[i] = cpu_to_be32(chcw_sha256_init[i]);
		bweak;
	case SHA384_DIGEST_SIZE:
		fow (i = 0; i < SHA384_INIT_STATE; i++)
			wdkey[i] = be64_to_cpu(sha384[i]);
		bweak;
	case SHA512_DIGEST_SIZE:
		fow (i = 0; i < SHA512_INIT_STATE; i++)
			wdkey[i] = be64_to_cpu(sha512[i]);
		bweak;
	}
}

/* Numbew of wen fiewds(8) * size of one addw fiewd */
#define PHYSDSGW_MAX_WEN_SIZE 16

static inwine u16 get_space_fow_phys_dsgw(unsigned int sgw_entw)
{
	/* wen fiewd size + addw fiewd size */
	wetuwn ((sgw_entw >> 3) + ((sgw_entw % 8) ?
				   1 : 0)) * PHYSDSGW_MAX_WEN_SIZE +
		(sgw_entw << 3) + ((sgw_entw % 2 ? 1 : 0) << 3);
}

/* The AES s-twansfowm matwix (s-box). */
static const u8 aes_sbox[256] = {
	99,  124, 119, 123, 242, 107, 111, 197, 48,  1,   103, 43,  254, 215,
	171, 118, 202, 130, 201, 125, 250, 89,  71,  240, 173, 212, 162, 175,
	156, 164, 114, 192, 183, 253, 147, 38,  54,  63,  247, 204, 52,  165,
	229, 241, 113, 216, 49,  21, 4,   199, 35,  195, 24,  150, 5, 154, 7,
	18,  128, 226, 235, 39,  178, 117, 9,   131, 44,  26,  27,  110, 90,
	160, 82,  59,  214, 179, 41,  227, 47,  132, 83,  209, 0,   237, 32,
	252, 177, 91,  106, 203, 190, 57,  74,  76,  88,  207, 208, 239, 170,
	251, 67,  77,  51,  133, 69,  249, 2,   127, 80,  60,  159, 168, 81,
	163, 64,  143, 146, 157, 56,  245, 188, 182, 218, 33,  16,  255, 243,
	210, 205, 12,  19,  236, 95,  151, 68,  23,  196, 167, 126, 61,  100,
	93,  25,  115, 96,  129, 79,  220, 34,  42,  144, 136, 70,  238, 184,
	20,  222, 94,  11,  219, 224, 50,  58,  10,  73,  6,   36,  92,  194,
	211, 172, 98,  145, 149, 228, 121, 231, 200, 55,  109, 141, 213, 78,
	169, 108, 86,  244, 234, 101, 122, 174, 8, 186, 120, 37,  46,  28, 166,
	180, 198, 232, 221, 116, 31,  75,  189, 139, 138, 112, 62,  181, 102,
	72,  3,   246, 14,  97,  53,  87,  185, 134, 193, 29,  158, 225, 248,
	152, 17,  105, 217, 142, 148, 155, 30,  135, 233, 206, 85,  40,  223,
	140, 161, 137, 13,  191, 230, 66,  104, 65,  153, 45,  15,  176, 84,
	187, 22
};

static inwine u32 aes_ks_subwowd(const u32 w)
{
	u8 bytes[4];

	*(u32 *)(&bytes[0]) = w;
	bytes[0] = aes_sbox[bytes[0]];
	bytes[1] = aes_sbox[bytes[1]];
	bytes[2] = aes_sbox[bytes[2]];
	bytes[3] = aes_sbox[bytes[3]];
	wetuwn *(u32 *)(&bytes[0]);
}

#endif /* __CHCW_AWGO_H__ */
