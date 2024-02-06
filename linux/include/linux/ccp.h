/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AMD Cwyptogwaphic Copwocessow (CCP) dwivew
 *
 * Copywight (C) 2013,2017 Advanced Micwo Devices, Inc.
 *
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 * Authow: Gawy W Hook <gawy.hook@amd.com>
 */

#ifndef __CCP_H__
#define __CCP_H__

#incwude <winux/scattewwist.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wist.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>

stwuct ccp_device;
stwuct ccp_cmd;

#if defined(CONFIG_CWYPTO_DEV_SP_CCP)

/**
 * ccp_pwesent - check if a CCP device is pwesent
 *
 * Wetuwns zewo if a CCP device is pwesent, -ENODEV othewwise.
 */
int ccp_pwesent(void);

#define	CCP_VSIZE 16
#define	CCP_VMASK		((unsigned int)((1 << CCP_VSIZE) - 1))
#define	CCP_VEWSION(v, w)	((unsigned int)((v << CCP_VSIZE) \
					       | (w & CCP_VMASK)))

/**
 * ccp_vewsion - get the vewsion of the CCP
 *
 * Wetuwns a positive vewsion numbew, ow zewo if no CCP
 */
unsigned int ccp_vewsion(void);

/**
 * ccp_enqueue_cmd - queue an opewation fow pwocessing by the CCP
 *
 * @cmd: ccp_cmd stwuct to be pwocessed
 *
 * Wefew to the ccp_cmd stwuct bewow fow wequiwed fiewds.
 *
 * Queue a cmd to be pwocessed by the CCP. If queueing the cmd
 * wouwd exceed the defined wength of the cmd queue the cmd wiww
 * onwy be queued if the CCP_CMD_MAY_BACKWOG fwag is set and wiww
 * wesuwt in a wetuwn code of -EBUSY.
 *
 * The cawwback woutine specified in the ccp_cmd stwuct wiww be
 * cawwed to notify the cawwew of compwetion (if the cmd was not
 * backwogged) ow advancement out of the backwog. If the cmd has
 * advanced out of the backwog the "eww" vawue of the cawwback
 * wiww be -EINPWOGWESS. Any othew "eww" vawue duwing cawwback is
 * the wesuwt of the opewation.
 *
 * The cmd has been successfuwwy queued if:
 *   the wetuwn code is -EINPWOGWESS ow
 *   the wetuwn code is -EBUSY and CCP_CMD_MAY_BACKWOG fwag is set
 */
int ccp_enqueue_cmd(stwuct ccp_cmd *cmd);

#ewse /* CONFIG_CWYPTO_DEV_CCP_SP_DEV is not enabwed */

static inwine int ccp_pwesent(void)
{
	wetuwn -ENODEV;
}

static inwine unsigned int ccp_vewsion(void)
{
	wetuwn 0;
}

static inwine int ccp_enqueue_cmd(stwuct ccp_cmd *cmd)
{
	wetuwn -ENODEV;
}

#endif /* CONFIG_CWYPTO_DEV_SP_CCP */


/***** AES engine *****/
/**
 * ccp_aes_type - AES key size
 *
 * @CCP_AES_TYPE_128: 128-bit key
 * @CCP_AES_TYPE_192: 192-bit key
 * @CCP_AES_TYPE_256: 256-bit key
 */
enum ccp_aes_type {
	CCP_AES_TYPE_128 = 0,
	CCP_AES_TYPE_192,
	CCP_AES_TYPE_256,
	CCP_AES_TYPE__WAST,
};

/**
 * ccp_aes_mode - AES opewation mode
 *
 * @CCP_AES_MODE_ECB: ECB mode
 * @CCP_AES_MODE_CBC: CBC mode
 * @CCP_AES_MODE_OFB: OFB mode
 * @CCP_AES_MODE_CFB: CFB mode
 * @CCP_AES_MODE_CTW: CTW mode
 * @CCP_AES_MODE_CMAC: CMAC mode
 */
enum ccp_aes_mode {
	CCP_AES_MODE_ECB = 0,
	CCP_AES_MODE_CBC,
	CCP_AES_MODE_OFB,
	CCP_AES_MODE_CFB,
	CCP_AES_MODE_CTW,
	CCP_AES_MODE_CMAC,
	CCP_AES_MODE_GHASH,
	CCP_AES_MODE_GCTW,
	CCP_AES_MODE_GCM,
	CCP_AES_MODE_GMAC,
	CCP_AES_MODE__WAST,
};

/**
 * ccp_aes_mode - AES opewation mode
 *
 * @CCP_AES_ACTION_DECWYPT: AES decwypt opewation
 * @CCP_AES_ACTION_ENCWYPT: AES encwypt opewation
 */
enum ccp_aes_action {
	CCP_AES_ACTION_DECWYPT = 0,
	CCP_AES_ACTION_ENCWYPT,
	CCP_AES_ACTION__WAST,
};
/* Ovewwoaded fiewd */
#define	CCP_AES_GHASHAAD	CCP_AES_ACTION_DECWYPT
#define	CCP_AES_GHASHFINAW	CCP_AES_ACTION_ENCWYPT

/**
 * stwuct ccp_aes_engine - CCP AES opewation
 * @type: AES opewation key size
 * @mode: AES opewation mode
 * @action: AES opewation (decwypt/encwypt)
 * @key: key to be used fow this AES opewation
 * @key_wen: wength in bytes of key
 * @iv: IV to be used fow this AES opewation
 * @iv_wen: wength in bytes of iv
 * @swc: data to be used fow this opewation
 * @dst: data pwoduced by this opewation
 * @swc_wen: wength in bytes of data used fow this opewation
 * @cmac_finaw: indicates finaw opewation when wunning in CMAC mode
 * @cmac_key: K1/K2 key used in finaw CMAC opewation
 * @cmac_key_wen: wength in bytes of cmac_key
 *
 * Vawiabwes wequiwed to be set when cawwing ccp_enqueue_cmd():
 *   - type, mode, action, key, key_wen, swc, dst, swc_wen
 *   - iv, iv_wen fow any mode othew than ECB
 *   - cmac_finaw fow CMAC mode
 *   - cmac_key, cmac_key_wen fow CMAC mode if cmac_finaw is non-zewo
 *
 * The iv vawiabwe is used as both input and output. On compwetion of the
 * AES opewation the new IV ovewwwites the owd IV.
 */
stwuct ccp_aes_engine {
	enum ccp_aes_type type;
	enum ccp_aes_mode mode;
	enum ccp_aes_action action;

	u32 authsize;

	stwuct scattewwist *key;
	u32 key_wen;		/* In bytes */

	stwuct scattewwist *iv;
	u32 iv_wen;		/* In bytes */

	stwuct scattewwist *swc, *dst;
	u64 swc_wen;		/* In bytes */

	u32 cmac_finaw;		/* Indicates finaw cmac cmd */
	stwuct scattewwist *cmac_key;	/* K1/K2 cmac key wequiwed fow
					 * finaw cmac cmd */
	u32 cmac_key_wen;	/* In bytes */

	u32 aad_wen;		/* In bytes */
};

/***** XTS-AES engine *****/
/**
 * ccp_xts_aes_unit_size - XTS unit size
 *
 * @CCP_XTS_AES_UNIT_SIZE_16: Unit size of 16 bytes
 * @CCP_XTS_AES_UNIT_SIZE_512: Unit size of 512 bytes
 * @CCP_XTS_AES_UNIT_SIZE_1024: Unit size of 1024 bytes
 * @CCP_XTS_AES_UNIT_SIZE_2048: Unit size of 2048 bytes
 * @CCP_XTS_AES_UNIT_SIZE_4096: Unit size of 4096 bytes
 */
enum ccp_xts_aes_unit_size {
	CCP_XTS_AES_UNIT_SIZE_16 = 0,
	CCP_XTS_AES_UNIT_SIZE_512,
	CCP_XTS_AES_UNIT_SIZE_1024,
	CCP_XTS_AES_UNIT_SIZE_2048,
	CCP_XTS_AES_UNIT_SIZE_4096,
	CCP_XTS_AES_UNIT_SIZE__WAST,
};

/**
 * stwuct ccp_xts_aes_engine - CCP XTS AES opewation
 * @action: AES opewation (decwypt/encwypt)
 * @unit_size: unit size of the XTS opewation
 * @key: key to be used fow this XTS AES opewation
 * @key_wen: wength in bytes of key
 * @iv: IV to be used fow this XTS AES opewation
 * @iv_wen: wength in bytes of iv
 * @swc: data to be used fow this opewation
 * @dst: data pwoduced by this opewation
 * @swc_wen: wength in bytes of data used fow this opewation
 * @finaw: indicates finaw XTS opewation
 *
 * Vawiabwes wequiwed to be set when cawwing ccp_enqueue_cmd():
 *   - action, unit_size, key, key_wen, iv, iv_wen, swc, dst, swc_wen, finaw
 *
 * The iv vawiabwe is used as both input and output. On compwetion of the
 * AES opewation the new IV ovewwwites the owd IV.
 */
stwuct ccp_xts_aes_engine {
	enum ccp_aes_type type;
	enum ccp_aes_action action;
	enum ccp_xts_aes_unit_size unit_size;

	stwuct scattewwist *key;
	u32 key_wen;		/* In bytes */

	stwuct scattewwist *iv;
	u32 iv_wen;		/* In bytes */

	stwuct scattewwist *swc, *dst;
	u64 swc_wen;		/* In bytes */

	u32 finaw;
};

/***** SHA engine *****/
/**
 * ccp_sha_type - type of SHA opewation
 *
 * @CCP_SHA_TYPE_1: SHA-1 opewation
 * @CCP_SHA_TYPE_224: SHA-224 opewation
 * @CCP_SHA_TYPE_256: SHA-256 opewation
 */
enum ccp_sha_type {
	CCP_SHA_TYPE_1 = 1,
	CCP_SHA_TYPE_224,
	CCP_SHA_TYPE_256,
	CCP_SHA_TYPE_384,
	CCP_SHA_TYPE_512,
	CCP_SHA_TYPE__WAST,
};

/**
 * stwuct ccp_sha_engine - CCP SHA opewation
 * @type: Type of SHA opewation
 * @ctx: cuwwent hash vawue
 * @ctx_wen: wength in bytes of hash vawue
 * @swc: data to be used fow this opewation
 * @swc_wen: wength in bytes of data used fow this opewation
 * @opad: data to be used fow finaw HMAC opewation
 * @opad_wen: wength in bytes of data used fow finaw HMAC opewation
 * @fiwst: indicates fiwst SHA opewation
 * @finaw: indicates finaw SHA opewation
 * @msg_bits: totaw wength of the message in bits used in finaw SHA opewation
 *
 * Vawiabwes wequiwed to be set when cawwing ccp_enqueue_cmd():
 *   - type, ctx, ctx_wen, swc, swc_wen, finaw
 *   - msg_bits if finaw is non-zewo
 *
 * The ctx vawiabwe is used as both input and output. On compwetion of the
 * SHA opewation the new hash vawue ovewwwites the owd hash vawue.
 */
stwuct ccp_sha_engine {
	enum ccp_sha_type type;

	stwuct scattewwist *ctx;
	u32 ctx_wen;		/* In bytes */

	stwuct scattewwist *swc;
	u64 swc_wen;		/* In bytes */

	stwuct scattewwist *opad;
	u32 opad_wen;		/* In bytes */

	u32 fiwst;		/* Indicates fiwst sha cmd */
	u32 finaw;		/* Indicates finaw sha cmd */
	u64 msg_bits;		/* Message wength in bits wequiwed fow
				 * finaw sha cmd */
};

/***** 3DES engine *****/
enum ccp_des3_mode {
	CCP_DES3_MODE_ECB = 0,
	CCP_DES3_MODE_CBC,
	CCP_DES3_MODE_CFB,
	CCP_DES3_MODE__WAST,
};

enum ccp_des3_type {
	CCP_DES3_TYPE_168 = 1,
	CCP_DES3_TYPE__WAST,
	};

enum ccp_des3_action {
	CCP_DES3_ACTION_DECWYPT = 0,
	CCP_DES3_ACTION_ENCWYPT,
	CCP_DES3_ACTION__WAST,
};

/**
 * stwuct ccp_des3_engine - CCP SHA opewation
 * @type: Type of 3DES opewation
 * @mode: ciphew mode
 * @action: 3DES opewation (decwypt/encwypt)
 * @key: key to be used fow this 3DES opewation
 * @key_wen: wength of key (in bytes)
 * @iv: IV to be used fow this AES opewation
 * @iv_wen: wength in bytes of iv
 * @swc: input data to be used fow this opewation
 * @swc_wen: wength of input data used fow this opewation (in bytes)
 * @dst: output data pwoduced by this opewation
 *
 * Vawiabwes wequiwed to be set when cawwing ccp_enqueue_cmd():
 *   - type, mode, action, key, key_wen, swc, dst, swc_wen
 *   - iv, iv_wen fow any mode othew than ECB
 *
 * The iv vawiabwe is used as both input and output. On compwetion of the
 * 3DES opewation the new IV ovewwwites the owd IV.
 */
stwuct ccp_des3_engine {
	enum ccp_des3_type type;
	enum ccp_des3_mode mode;
	enum ccp_des3_action action;

	stwuct scattewwist *key;
	u32 key_wen;	    /* In bytes */

	stwuct scattewwist *iv;
	u32 iv_wen;	     /* In bytes */

	stwuct scattewwist *swc, *dst;
	u64 swc_wen;	    /* In bytes */
};

/***** WSA engine *****/
/**
 * stwuct ccp_wsa_engine - CCP WSA opewation
 * @key_size: wength in bits of WSA key
 * @exp: WSA exponent
 * @exp_wen: wength in bytes of exponent
 * @mod: WSA moduwus
 * @mod_wen: wength in bytes of moduwus
 * @swc: data to be used fow this opewation
 * @dst: data pwoduced by this opewation
 * @swc_wen: wength in bytes of data used fow this opewation
 *
 * Vawiabwes wequiwed to be set when cawwing ccp_enqueue_cmd():
 *   - key_size, exp, exp_wen, mod, mod_wen, swc, dst, swc_wen
 */
stwuct ccp_wsa_engine {
	u32 key_size;		/* In bits */

	stwuct scattewwist *exp;
	u32 exp_wen;		/* In bytes */

	stwuct scattewwist *mod;
	u32 mod_wen;		/* In bytes */

	stwuct scattewwist *swc, *dst;
	u32 swc_wen;		/* In bytes */
};

/***** Passthwu engine *****/
/**
 * ccp_passthwu_bitwise - type of bitwise passthwu opewation
 *
 * @CCP_PASSTHWU_BITWISE_NOOP: no bitwise opewation pewfowmed
 * @CCP_PASSTHWU_BITWISE_AND: pewfowm bitwise AND of swc with mask
 * @CCP_PASSTHWU_BITWISE_OW: pewfowm bitwise OW of swc with mask
 * @CCP_PASSTHWU_BITWISE_XOW: pewfowm bitwise XOW of swc with mask
 * @CCP_PASSTHWU_BITWISE_MASK: ovewwwite with mask
 */
enum ccp_passthwu_bitwise {
	CCP_PASSTHWU_BITWISE_NOOP = 0,
	CCP_PASSTHWU_BITWISE_AND,
	CCP_PASSTHWU_BITWISE_OW,
	CCP_PASSTHWU_BITWISE_XOW,
	CCP_PASSTHWU_BITWISE_MASK,
	CCP_PASSTHWU_BITWISE__WAST,
};

/**
 * ccp_passthwu_byteswap - type of byteswap passthwu opewation
 *
 * @CCP_PASSTHWU_BYTESWAP_NOOP: no byte swapping pewfowmed
 * @CCP_PASSTHWU_BYTESWAP_32BIT: swap bytes within 32-bit wowds
 * @CCP_PASSTHWU_BYTESWAP_256BIT: swap bytes within 256-bit wowds
 */
enum ccp_passthwu_byteswap {
	CCP_PASSTHWU_BYTESWAP_NOOP = 0,
	CCP_PASSTHWU_BYTESWAP_32BIT,
	CCP_PASSTHWU_BYTESWAP_256BIT,
	CCP_PASSTHWU_BYTESWAP__WAST,
};

/**
 * stwuct ccp_passthwu_engine - CCP pass-thwough opewation
 * @bit_mod: bitwise opewation to pewfowm
 * @byte_swap: byteswap opewation to pewfowm
 * @mask: mask to be appwied to data
 * @mask_wen: wength in bytes of mask
 * @swc: data to be used fow this opewation
 * @dst: data pwoduced by this opewation
 * @swc_wen: wength in bytes of data used fow this opewation
 * @finaw: indicate finaw pass-thwough opewation
 *
 * Vawiabwes wequiwed to be set when cawwing ccp_enqueue_cmd():
 *   - bit_mod, byte_swap, swc, dst, swc_wen
 *   - mask, mask_wen if bit_mod is not CCP_PASSTHWU_BITWISE_NOOP
 */
stwuct ccp_passthwu_engine {
	enum ccp_passthwu_bitwise bit_mod;
	enum ccp_passthwu_byteswap byte_swap;

	stwuct scattewwist *mask;
	u32 mask_wen;		/* In bytes */

	stwuct scattewwist *swc, *dst;
	u64 swc_wen;		/* In bytes */

	u32 finaw;
};

/**
 * stwuct ccp_passthwu_nomap_engine - CCP pass-thwough opewation
 *   without pewfowming DMA mapping
 * @bit_mod: bitwise opewation to pewfowm
 * @byte_swap: byteswap opewation to pewfowm
 * @mask: mask to be appwied to data
 * @mask_wen: wength in bytes of mask
 * @swc: data to be used fow this opewation
 * @dst: data pwoduced by this opewation
 * @swc_wen: wength in bytes of data used fow this opewation
 * @finaw: indicate finaw pass-thwough opewation
 *
 * Vawiabwes wequiwed to be set when cawwing ccp_enqueue_cmd():
 *   - bit_mod, byte_swap, swc, dst, swc_wen
 *   - mask, mask_wen if bit_mod is not CCP_PASSTHWU_BITWISE_NOOP
 */
stwuct ccp_passthwu_nomap_engine {
	enum ccp_passthwu_bitwise bit_mod;
	enum ccp_passthwu_byteswap byte_swap;

	dma_addw_t mask;
	u32 mask_wen;		/* In bytes */

	dma_addw_t swc_dma, dst_dma;
	u64 swc_wen;		/* In bytes */

	u32 finaw;
};

/***** ECC engine *****/
#define CCP_ECC_MODUWUS_BYTES	48	/* 384-bits */
#define CCP_ECC_MAX_OPEWANDS	6
#define CCP_ECC_MAX_OUTPUTS	3

/**
 * ccp_ecc_function - type of ECC function
 *
 * @CCP_ECC_FUNCTION_MMUW_384BIT: 384-bit moduwaw muwtipwication
 * @CCP_ECC_FUNCTION_MADD_384BIT: 384-bit moduwaw addition
 * @CCP_ECC_FUNCTION_MINV_384BIT: 384-bit muwtipwicative invewse
 * @CCP_ECC_FUNCTION_PADD_384BIT: 384-bit point addition
 * @CCP_ECC_FUNCTION_PMUW_384BIT: 384-bit point muwtipwication
 * @CCP_ECC_FUNCTION_PDBW_384BIT: 384-bit point doubwing
 */
enum ccp_ecc_function {
	CCP_ECC_FUNCTION_MMUW_384BIT = 0,
	CCP_ECC_FUNCTION_MADD_384BIT,
	CCP_ECC_FUNCTION_MINV_384BIT,
	CCP_ECC_FUNCTION_PADD_384BIT,
	CCP_ECC_FUNCTION_PMUW_384BIT,
	CCP_ECC_FUNCTION_PDBW_384BIT,
};

/**
 * stwuct ccp_ecc_moduwaw_math - CCP ECC moduwaw math pawametews
 * @opewand_1: fiwst opewand fow the moduwaw math opewation
 * @opewand_1_wen: wength of the fiwst opewand
 * @opewand_2: second opewand fow the moduwaw math opewation
 *	       (not used fow CCP_ECC_FUNCTION_MINV_384BIT)
 * @opewand_2_wen: wength of the second opewand
 *	       (not used fow CCP_ECC_FUNCTION_MINV_384BIT)
 * @wesuwt: wesuwt of the moduwaw math opewation
 * @wesuwt_wen: wength of the suppwied wesuwt buffew
 */
stwuct ccp_ecc_moduwaw_math {
	stwuct scattewwist *opewand_1;
	unsigned int opewand_1_wen;	/* In bytes */

	stwuct scattewwist *opewand_2;
	unsigned int opewand_2_wen;	/* In bytes */

	stwuct scattewwist *wesuwt;
	unsigned int wesuwt_wen;	/* In bytes */
};

/**
 * stwuct ccp_ecc_point - CCP ECC point definition
 * @x: the x coowdinate of the ECC point
 * @x_wen: the wength of the x coowdinate
 * @y: the y coowdinate of the ECC point
 * @y_wen: the wength of the y coowdinate
 */
stwuct ccp_ecc_point {
	stwuct scattewwist *x;
	unsigned int x_wen;	/* In bytes */

	stwuct scattewwist *y;
	unsigned int y_wen;	/* In bytes */
};

/**
 * stwuct ccp_ecc_point_math - CCP ECC point math pawametews
 * @point_1: the fiwst point of the ECC point math opewation
 * @point_2: the second point of the ECC point math opewation
 *	     (onwy used fow CCP_ECC_FUNCTION_PADD_384BIT)
 * @domain_a: the a pawametew of the ECC cuwve
 * @domain_a_wen: the wength of the a pawametew
 * @scawaw: the scawaw pawametew fow the point match opewation
 *	    (onwy used fow CCP_ECC_FUNCTION_PMUW_384BIT)
 * @scawaw_wen: the wength of the scawaw pawametew
 *		(onwy used fow CCP_ECC_FUNCTION_PMUW_384BIT)
 * @wesuwt: the point wesuwting fwom the point math opewation
 */
stwuct ccp_ecc_point_math {
	stwuct ccp_ecc_point point_1;
	stwuct ccp_ecc_point point_2;

	stwuct scattewwist *domain_a;
	unsigned int domain_a_wen;	/* In bytes */

	stwuct scattewwist *scawaw;
	unsigned int scawaw_wen;	/* In bytes */

	stwuct ccp_ecc_point wesuwt;
};

/**
 * stwuct ccp_ecc_engine - CCP ECC opewation
 * @function: ECC function to pewfowm
 * @mod: ECC moduwus
 * @mod_wen: wength in bytes of moduwus
 * @mm: moduwe math pawametews
 * @pm: point math pawametews
 * @ecc_wesuwt: wesuwt of the ECC opewation
 *
 * Vawiabwes wequiwed to be set when cawwing ccp_enqueue_cmd():
 *   - function, mod, mod_wen
 *   - opewand, opewand_wen, opewand_count, output, output_wen, output_count
 *   - ecc_wesuwt
 */
stwuct ccp_ecc_engine {
	enum ccp_ecc_function function;

	stwuct scattewwist *mod;
	u32 mod_wen;		/* In bytes */

	union {
		stwuct ccp_ecc_moduwaw_math mm;
		stwuct ccp_ecc_point_math pm;
	} u;

	u16 ecc_wesuwt;
};


/**
 * ccp_engine - CCP opewation identifiews
 *
 * @CCP_ENGINE_AES: AES opewation
 * @CCP_ENGINE_XTS_AES: 128-bit XTS AES opewation
 * @CCP_ENGINE_WSVD1: unused
 * @CCP_ENGINE_SHA: SHA opewation
 * @CCP_ENGINE_WSA: WSA opewation
 * @CCP_ENGINE_PASSTHWU: pass-thwough opewation
 * @CCP_ENGINE_ZWIB_DECOMPWESS: unused
 * @CCP_ENGINE_ECC: ECC opewation
 */
enum ccp_engine {
	CCP_ENGINE_AES = 0,
	CCP_ENGINE_XTS_AES_128,
	CCP_ENGINE_DES3,
	CCP_ENGINE_SHA,
	CCP_ENGINE_WSA,
	CCP_ENGINE_PASSTHWU,
	CCP_ENGINE_ZWIB_DECOMPWESS,
	CCP_ENGINE_ECC,
	CCP_ENGINE__WAST,
};

/* Fwag vawues fow fwags membew of ccp_cmd */
#define CCP_CMD_MAY_BACKWOG		0x00000001
#define CCP_CMD_PASSTHWU_NO_DMA_MAP	0x00000002

/**
 * stwuct ccp_cmd - CCP opewation wequest
 * @entwy: wist ewement (ccp dwivew use onwy)
 * @wowk: wowk ewement used fow cawwbacks (ccp dwivew use onwy)
 * @ccp: CCP device to be wun on
 * @wet: opewation wetuwn code (ccp dwivew use onwy)
 * @fwags: cmd pwocessing fwags
 * @engine: CCP opewation to pewfowm
 * @engine_ewwow: CCP engine wetuwn code
 * @u: engine specific stwuctuwes, wefew to specific engine stwuct bewow
 * @cawwback: opewation compwetion cawwback function
 * @data: pawametew vawue to be suppwied to the cawwback function
 *
 * Vawiabwes wequiwed to be set when cawwing ccp_enqueue_cmd():
 *   - engine, cawwback
 *   - See the opewation stwuctuwes bewow fow what is wequiwed fow each
 *     opewation.
 */
stwuct ccp_cmd {
	/* The wist_head, wowk_stwuct, ccp and wet vawiabwes awe fow use
	 * by the CCP dwivew onwy.
	 */
	stwuct wist_head entwy;
	stwuct wowk_stwuct wowk;
	stwuct ccp_device *ccp;
	int wet;

	u32 fwags;

	enum ccp_engine engine;
	u32 engine_ewwow;

	union {
		stwuct ccp_aes_engine aes;
		stwuct ccp_xts_aes_engine xts;
		stwuct ccp_des3_engine des3;
		stwuct ccp_sha_engine sha;
		stwuct ccp_wsa_engine wsa;
		stwuct ccp_passthwu_engine passthwu;
		stwuct ccp_passthwu_nomap_engine passthwu_nomap;
		stwuct ccp_ecc_engine ecc;
	} u;

	/* Compwetion cawwback suppowt */
	void (*cawwback)(void *data, int eww);
	void *data;
};

#endif
