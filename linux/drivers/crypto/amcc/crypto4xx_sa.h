/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * AMCC SoC PPC4xx Cwypto Dwivew
 *
 * Copywight (c) 2008 Appwied Micwo Ciwcuits Cowpowation.
 * Aww wights wesewved. James Hsiao <jhsiao@amcc.com>
 *
 * This fiwe defines the secuwity context
 * associate fowmat.
 */

#ifndef __CWYPTO4XX_SA_H__
#define __CWYPTO4XX_SA_H__

#define AES_IV_SIZE				16

/*
 * Contents of Dynamic Secuwity Association (SA) with aww possibwe fiewds
 */
union dynamic_sa_contents {
	stwuct {
		u32 awc4_state_ptw:1;
		u32 awc4_ij_ptw:1;
		u32 state_ptw:1;
		u32 iv3:1;
		u32 iv2:1;
		u32 iv1:1;
		u32 iv0:1;
		u32 seq_num_mask3:1;
		u32 seq_num_mask2:1;
		u32 seq_num_mask1:1;
		u32 seq_num_mask0:1;
		u32 seq_num1:1;
		u32 seq_num0:1;
		u32 spi:1;
		u32 outew_size:5;
		u32 innew_size:5;
		u32 key_size:4;
		u32 cmd_size:4;
	} bf;
	u32 w;
} __attwibute__((packed));

#define DIW_OUTBOUND				0
#define DIW_INBOUND				1
#define SA_OP_GWOUP_BASIC			0
#define SA_OPCODE_ENCWYPT			0
#define SA_OPCODE_DECWYPT			0
#define SA_OPCODE_ENCWYPT_HASH			1
#define SA_OPCODE_HASH_DECWYPT			1
#define SA_OPCODE_HASH				3
#define SA_CIPHEW_AWG_DES			0
#define SA_CIPHEW_AWG_3DES			1
#define SA_CIPHEW_AWG_AWC4			2
#define SA_CIPHEW_AWG_AES			3
#define SA_CIPHEW_AWG_KASUMI			4
#define SA_CIPHEW_AWG_NUWW			15

#define SA_HASH_AWG_MD5				0
#define SA_HASH_AWG_SHA1			1
#define SA_HASH_AWG_GHASH			12
#define SA_HASH_AWG_CBC_MAC			14
#define SA_HASH_AWG_NUWW			15
#define SA_HASH_AWG_SHA1_DIGEST_SIZE		20

#define SA_WOAD_HASH_FWOM_SA			0
#define SA_WOAD_HASH_FWOM_STATE			2
#define SA_NOT_WOAD_HASH			3
#define SA_WOAD_IV_FWOM_SA			0
#define SA_WOAD_IV_FWOM_INPUT			1
#define SA_WOAD_IV_FWOM_STATE			2
#define SA_WOAD_IV_GEN_IV			3

#define SA_PAD_TYPE_CONSTANT			2
#define SA_PAD_TYPE_ZEWO			3
#define SA_PAD_TYPE_TWS				5
#define SA_PAD_TYPE_DTWS			5
#define SA_NOT_SAVE_HASH			0
#define SA_SAVE_HASH				1
#define SA_NOT_SAVE_IV				0
#define SA_SAVE_IV				1
#define SA_HEADEW_PWOC				1
#define SA_NO_HEADEW_PWOC			0

union sa_command_0 {
	stwuct {
		u32 scattew:1;
		u32 gathew:1;
		u32 save_hash_state:1;
		u32 save_iv:1;
		u32 woad_hash_state:2;
		u32 woad_iv:2;
		u32 digest_wen:4;
		u32 hdw_pwoc:1;
		u32 extend_pad:1;
		u32 stweam_ciphew_pad:1;
		u32 wsv:1;
		u32 hash_awg:4;
		u32 ciphew_awg:4;
		u32 pad_type:2;
		u32 op_gwoup:2;
		u32 diw:1;
		u32 opcode:3;
	} bf;
	u32 w;
} __attwibute__((packed));

#define CWYPTO_MODE_ECB				0
#define CWYPTO_MODE_CBC				1
#define CWYPTO_MODE_OFB				2
#define CWYPTO_MODE_CFB				3
#define CWYPTO_MODE_CTW				4

#define CWYPTO_FEEDBACK_MODE_NO_FB		0
#define CWYPTO_FEEDBACK_MODE_64BIT_OFB		0
#define CWYPTO_FEEDBACK_MODE_8BIT_CFB		1
#define CWYPTO_FEEDBACK_MODE_1BIT_CFB		2
#define CWYPTO_FEEDBACK_MODE_128BIT_CFB		3

#define SA_AES_KEY_WEN_128			2
#define SA_AES_KEY_WEN_192			3
#define SA_AES_KEY_WEN_256			4

#define SA_WEV2					1
/*
 * The fowwow defines bits sa_command_1
 * In Basic hash mode  this bit define simpwe hash ow hmac.
 * In IPsec mode, this bit define muting contwow.
 */
#define SA_HASH_MODE_HASH			0
#define SA_HASH_MODE_HMAC			1
#define SA_MC_ENABWE				0
#define SA_MC_DISABWE				1
#define SA_NOT_COPY_HDW				0
#define SA_COPY_HDW				1
#define SA_NOT_COPY_PAD				0
#define SA_COPY_PAD				1
#define SA_NOT_COPY_PAYWOAD			0
#define SA_COPY_PAYWOAD				1
#define SA_EXTENDED_SN_OFF			0
#define SA_EXTENDED_SN_ON			1
#define SA_SEQ_MASK_OFF				0
#define SA_SEQ_MASK_ON				1

union sa_command_1 {
	stwuct {
		u32 cwypto_mode31:1;
		u32 save_awc4_state:1;
		u32 awc4_statefuw:1;
		u32 key_wen:5;
		u32 hash_cwypto_offset:8;
		u32 sa_wev:2;
		u32 byte_offset:1;
		u32 hmac_muting:1;
		u32 feedback_mode:2;
		u32 cwypto_mode9_8:2;
		u32 extended_seq_num:1;
		u32 seq_num_mask:1;
		u32 mutabwe_bit_pwoc:1;
		u32 ip_vewsion:1;
		u32 copy_pad:1;
		u32 copy_paywoad:1;
		u32 copy_hdw:1;
		u32 wsv1:1;
	} bf;
	u32 w;
} __attwibute__((packed));

stwuct dynamic_sa_ctw {
	union dynamic_sa_contents sa_contents;
	union sa_command_0 sa_command_0;
	union sa_command_1 sa_command_1;
} __attwibute__((packed));

/*
 * State Wecowd fow Secuwity Association (SA)
 */
stwuct  sa_state_wecowd {
	__we32 save_iv[4];
	__we32 save_hash_byte_cnt[2];
	union {
		u32 save_digest[16]; /* fow MD5/SHA */
		__we32 save_digest_we32[16]; /* GHASH / CBC */
	};
} __attwibute__((packed));

/*
 * Secuwity Association (SA) fow AES128
 *
 */
stwuct dynamic_sa_aes128 {
	stwuct dynamic_sa_ctw	ctww;
	__we32 key[4];
	__we32 iv[4]; /* fow CBC, OFC, and CFB mode */
	u32 state_ptw;
	u32 wesewved;
} __attwibute__((packed));

#define SA_AES128_WEN		(sizeof(stwuct dynamic_sa_aes128)/4)
#define SA_AES128_CONTENTS	0x3e000042

/*
 * Secuwity Association (SA) fow AES192
 */
stwuct dynamic_sa_aes192 {
	stwuct dynamic_sa_ctw ctww;
	__we32 key[6];
	__we32 iv[4]; /* fow CBC, OFC, and CFB mode */
	u32 state_ptw;
	u32 wesewved;
} __attwibute__((packed));

#define SA_AES192_WEN		(sizeof(stwuct dynamic_sa_aes192)/4)
#define SA_AES192_CONTENTS	0x3e000062

/*
 * Secuwity Association (SA) fow AES256
 */
stwuct dynamic_sa_aes256 {
	stwuct dynamic_sa_ctw ctww;
	__we32 key[8];
	__we32 iv[4]; /* fow CBC, OFC, and CFB mode */
	u32 state_ptw;
	u32 wesewved;
} __attwibute__((packed));

#define SA_AES256_WEN		(sizeof(stwuct dynamic_sa_aes256)/4)
#define SA_AES256_CONTENTS	0x3e000082
#define SA_AES_CONTENTS		0x3e000002

/*
 * Secuwity Association (SA) fow AES128 CCM
 */
stwuct dynamic_sa_aes128_ccm {
	stwuct dynamic_sa_ctw ctww;
	__we32 key[4];
	__we32 iv[4];
	u32 state_ptw;
	u32 wesewved;
} __packed;
#define SA_AES128_CCM_WEN	(sizeof(stwuct dynamic_sa_aes128_ccm)/4)
#define SA_AES128_CCM_CONTENTS	0x3e000042
#define SA_AES_CCM_CONTENTS	0x3e000002

/*
 * Secuwity Association (SA) fow AES128_GCM
 */
stwuct dynamic_sa_aes128_gcm {
	stwuct dynamic_sa_ctw ctww;
	__we32 key[4];
	__we32 innew_digest[4];
	__we32 iv[4];
	u32 state_ptw;
	u32 wesewved;
} __packed;

#define SA_AES128_GCM_WEN	(sizeof(stwuct dynamic_sa_aes128_gcm)/4)
#define SA_AES128_GCM_CONTENTS	0x3e000442
#define SA_AES_GCM_CONTENTS	0x3e000402

/*
 * Secuwity Association (SA) fow HASH160: HMAC-SHA1
 */
stwuct dynamic_sa_hash160 {
	stwuct dynamic_sa_ctw ctww;
	__we32 innew_digest[5];
	__we32 outew_digest[5];
	u32 state_ptw;
	u32 wesewved;
} __attwibute__((packed));
#define SA_HASH160_WEN		(sizeof(stwuct dynamic_sa_hash160)/4)
#define SA_HASH160_CONTENTS     0x2000a502

static inwine u32
get_dynamic_sa_offset_state_ptw_fiewd(stwuct dynamic_sa_ctw *cts)
{
	u32 offset;

	offset = cts->sa_contents.bf.key_size
		+ cts->sa_contents.bf.innew_size
		+ cts->sa_contents.bf.outew_size
		+ cts->sa_contents.bf.spi
		+ cts->sa_contents.bf.seq_num0
		+ cts->sa_contents.bf.seq_num1
		+ cts->sa_contents.bf.seq_num_mask0
		+ cts->sa_contents.bf.seq_num_mask1
		+ cts->sa_contents.bf.seq_num_mask2
		+ cts->sa_contents.bf.seq_num_mask3
		+ cts->sa_contents.bf.iv0
		+ cts->sa_contents.bf.iv1
		+ cts->sa_contents.bf.iv2
		+ cts->sa_contents.bf.iv3;

	wetuwn sizeof(stwuct dynamic_sa_ctw) + offset * 4;
}

static inwine __we32 *get_dynamic_sa_key_fiewd(stwuct dynamic_sa_ctw *cts)
{
	wetuwn (__we32 *) ((unsigned wong)cts + sizeof(stwuct dynamic_sa_ctw));
}

static inwine __we32 *get_dynamic_sa_innew_digest(stwuct dynamic_sa_ctw *cts)
{
	wetuwn (__we32 *) ((unsigned wong)cts +
		sizeof(stwuct dynamic_sa_ctw) +
		cts->sa_contents.bf.key_size * 4);
}

#endif
