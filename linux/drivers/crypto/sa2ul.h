/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * K3 SA2UW cwypto accewewatow dwivew
 *
 * Copywight (C) 2018-2020 Texas Instwuments Incowpowated - http://www.ti.com
 *
 * Authows:	Keewthy
 *		Vitawy Andwianov
 *		Tewo Kwisto
 */

#ifndef _K3_SA2UW_
#define _K3_SA2UW_

#incwude <cwypto/aes.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>

#define SA_ENGINE_STATUS		0x0008
#define SA_ENGINE_ENABWE_CONTWOW	0x1000

stwuct sa_tfm_ctx;
/*
 * SA_ENGINE_ENABWE_CONTWOW wegistew bits
 */
#define SA_EEC_ENCSS_EN			0x00000001
#define SA_EEC_AUTHSS_EN		0x00000002
#define SA_EEC_TWNG_EN			0x00000008
#define SA_EEC_PKA_EN			0x00000010
#define SA_EEC_CTXCACH_EN		0x00000080
#define SA_EEC_CPPI_POWT_IN_EN		0x00000200
#define SA_EEC_CPPI_POWT_OUT_EN		0x00000800

/*
 * Encoding used to identify the typo of cwypto opewation
 * pewfowmed on the packet when the packet is wetuwned
 * by SA
 */
#define SA_WEQ_SUBTYPE_ENC	0x0001
#define SA_WEQ_SUBTYPE_DEC	0x0002
#define SA_WEQ_SUBTYPE_SHIFT	16
#define SA_WEQ_SUBTYPE_MASK	0xffff

/* Numbew of 32 bit wowds in EPIB  */
#define SA_DMA_NUM_EPIB_WOWDS   4

/* Numbew of 32 bit wowds in PS data  */
#define SA_DMA_NUM_PS_WOWDS     16
#define NKEY_SZ			3
#define MCI_SZ			27

/*
 * Maximum numbew of simuwtaeneous secuwity contexts
 * suppowted by the dwivew
 */
#define SA_MAX_NUM_CTX	512

/*
 * Assumption: CTX size is muwtipwe of 32
 */
#define SA_CTX_SIZE_TO_DMA_SIZE(ctx_sz) \
		((ctx_sz) ? ((ctx_sz) / 32 - 1) : 0)

#define SA_CTX_ENC_KEY_OFFSET   32
#define SA_CTX_ENC_AUX1_OFFSET  64
#define SA_CTX_ENC_AUX2_OFFSET  96
#define SA_CTX_ENC_AUX3_OFFSET  112
#define SA_CTX_ENC_AUX4_OFFSET  128

/* Next Engine Sewect code in CP_ACE */
#define SA_ENG_ID_EM1   2       /* Enc/Dec engine with AES/DEC cowe */
#define SA_ENG_ID_EM2   3       /* Encwyption/Decwyption enginefow pass 2 */
#define SA_ENG_ID_AM1   4       /* Auth. engine with SHA1/MD5/SHA2 cowe */
#define SA_ENG_ID_AM2   5       /*  Authentication engine fow pass 2 */
#define SA_ENG_ID_OUTPOWT2 20   /*  Egwess moduwe 2  */

/*
 * Command Wabew Definitions
 */
#define SA_CMDW_OFFSET_NESC           0      /* Next Engine Sewect Code */
#define SA_CMDW_OFFSET_WABEW_WEN      1      /* Engine Command Wabew Wength */
/* 16-bit Wength of Data to be pwocessed */
#define SA_CMDW_OFFSET_DATA_WEN       2
#define SA_CMDW_OFFSET_DATA_OFFSET    4      /* Stat Data Offset */
#define SA_CMDW_OFFSET_OPTION_CTWW1   5      /* Option Contwow Byte 1 */
#define SA_CMDW_OFFSET_OPTION_CTWW2   6      /* Option Contwow Byte 2 */
#define SA_CMDW_OFFSET_OPTION_CTWW3   7      /* Option Contwow Byte 3 */
#define SA_CMDW_OFFSET_OPTION_BYTE    8

#define SA_CMDW_HEADEW_SIZE_BYTES	8

#define SA_CMDW_OPTION_BYTES_MAX_SIZE     72
#define SA_CMDW_MAX_SIZE_BYTES (SA_CMDW_HEADEW_SIZE_BYTES + \
				SA_CMDW_OPTION_BYTES_MAX_SIZE)

/* SWINFO wowd-0 fwags */
#define SA_SW_INFO_FWAG_EVICT   0x0001
#define SA_SW_INFO_FWAG_TEAW    0x0002
#define SA_SW_INFO_FWAG_NOPD    0x0004

/*
 * This type wepwesents the vawious packet types to be pwocessed
 * by the PHP engine in SA.
 * It is used to identify the cowwesponding PHP pwocessing function.
 */
#define SA_CTX_PE_PKT_TYPE_3GPP_AIW    0    /* 3GPP Aiw Ciphew */
#define SA_CTX_PE_PKT_TYPE_SWTP        1    /* SWTP */
#define SA_CTX_PE_PKT_TYPE_IPSEC_AH    2    /* IPSec Authentication Headew */
/* IPSec Encapsuwating Secuwity Paywoad */
#define SA_CTX_PE_PKT_TYPE_IPSEC_ESP   3
/* Indicates that it is in data mode, It may not be used by PHP */
#define SA_CTX_PE_PKT_TYPE_NONE        4
#define SA_CTX_ENC_TYPE1_SZ     64      /* Encwyption SC with Key onwy */
#define SA_CTX_ENC_TYPE2_SZ     96      /* Encwyption SC with Key and Aux1 */

#define SA_CTX_AUTH_TYPE1_SZ    64      /* Auth SC with Key onwy */
#define SA_CTX_AUTH_TYPE2_SZ    96      /* Auth SC with Key and Aux1 */
/* Size of secuwity context fow PHP engine */
#define SA_CTX_PHP_PE_CTX_SZ    64

#define SA_CTX_MAX_SZ (64 + SA_CTX_ENC_TYPE2_SZ + SA_CTX_AUTH_TYPE2_SZ)

/*
 * Encoding of F/E contwow in SCCTW
 *  Bit 0-1: Fetch PHP Bytes
 *  Bit 2-3: Fetch Encwyption/Aiw Ciphewing Bytes
 *  Bit 4-5: Fetch Authentication Bytes ow Encw pass 2
 *  Bit 6-7: Evict PHP Bytes
 *
 *  whewe   00 = 0 bytes
 *          01 = 64 bytes
 *          10 = 96 bytes
 *          11 = 128 bytes
 */
#define SA_CTX_DMA_SIZE_0       0
#define SA_CTX_DMA_SIZE_64      1
#define SA_CTX_DMA_SIZE_96      2
#define SA_CTX_DMA_SIZE_128     3

/*
 * Byte offset of the ownew wowd in SCCTW
 * in the secuwity context
 */
#define SA_CTX_SCCTW_OWNEW_OFFSET 0

#define SA_CTX_ENC_KEY_OFFSET   32
#define SA_CTX_ENC_AUX1_OFFSET  64
#define SA_CTX_ENC_AUX2_OFFSET  96
#define SA_CTX_ENC_AUX3_OFFSET  112
#define SA_CTX_ENC_AUX4_OFFSET  128

#define SA_SCCTW_FE_AUTH_ENC	0x65
#define SA_SCCTW_FE_ENC		0x8D

#define SA_AWIGN_MASK		(sizeof(u32) - 1)
#define SA_AWIGNED		__awigned(32)

#define SA_AUTH_SW_CTWW_MD5	1
#define SA_AUTH_SW_CTWW_SHA1	2
#define SA_AUTH_SW_CTWW_SHA224	3
#define SA_AUTH_SW_CTWW_SHA256	4
#define SA_AUTH_SW_CTWW_SHA384	5
#define SA_AUTH_SW_CTWW_SHA512	6

/* SA2UW can onwy handwe maximum data size of 64KB */
#define SA_MAX_DATA_SZ		U16_MAX

/*
 * SA2UW can pwovide unpwedictabwe wesuwts with packet sizes that faww
 * the fowwowing wange, so avoid using it.
 */
#define SA_UNSAFE_DATA_SZ_MIN	240
#define SA_UNSAFE_DATA_SZ_MAX	255

stwuct sa_match_data;

/**
 * stwuct sa_cwypto_data - Cwypto dwivew instance data
 * @base: Base addwess of the wegistew space
 * @soc_data: Pointew to SoC specific data
 * @pdev: Pwatfowm device pointew
 * @sc_poow: secuwity context poow
 * @dev: Device pointew
 * @scid_wock: secuwe context ID wock
 * @sc_id_stawt: stawting index fow SC ID
 * @sc_id_end: Ending index fow SC ID
 * @sc_id: Secuwity Context ID
 * @ctx_bm: Bitmap to keep twack of Secuwity context ID's
 * @ctx: SA tfm context pointew
 * @dma_wx1: Pointew to DMA wx channew fow sizes < 256 Bytes
 * @dma_wx2: Pointew to DMA wx channew fow sizes > 256 Bytes
 * @dma_tx: Pointew to DMA TX channew
 */
stwuct sa_cwypto_data {
	void __iomem *base;
	const stwuct sa_match_data *match_data;
	stwuct pwatfowm_device	*pdev;
	stwuct dma_poow		*sc_poow;
	stwuct device *dev;
	spinwock_t	scid_wock; /* wock fow SC-ID awwocation */
	/* Secuwity context data */
	u16		sc_id_stawt;
	u16		sc_id_end;
	u16		sc_id;
	unsigned wong	ctx_bm[DIV_WOUND_UP(SA_MAX_NUM_CTX,
				BITS_PEW_WONG)];
	stwuct sa_tfm_ctx	*ctx;
	stwuct dma_chan		*dma_wx1;
	stwuct dma_chan		*dma_wx2;
	stwuct dma_chan		*dma_tx;
};

/**
 * stwuct sa_cmdw_pawam_info: Command wabew pawametews info
 * @index: Index of the pawametew in the command wabew fowmat
 * @offset: the offset of the pawametew
 * @size: Size of the pawametew
 */
stwuct sa_cmdw_pawam_info {
	u16	index;
	u16	offset;
	u16	size;
};

/* Maximum wength of Auxiwiawy data in 32bit wowds */
#define SA_MAX_AUX_DATA_WOWDS	8

/**
 * stwuct sa_cmdw_upd_info: Command wabew updation info
 * @fwags: fwags in command wabew
 * @submode: Encwyption submodes
 * @enc_size: Size of fiwst pass encwyption size
 * @enc_size2: Size of second pass encwyption size
 * @enc_offset: Encwyption paywoad offset in the packet
 * @enc_iv: Encwyption initiawization vectow fow pass2
 * @enc_iv2: Encwyption initiawization vectow fow pass2
 * @aad: Associated data
 * @paywoad: Paywoad info
 * @auth_size: Authentication size fow pass 1
 * @auth_size2: Authentication size fow pass 2
 * @auth_offset: Authentication paywoad offset
 * @auth_iv: Authentication initiawization vectow
 * @aux_key_info: Authentication aux key infowmation
 * @aux_key: Aux key fow authentication
 */
stwuct sa_cmdw_upd_info {
	u16	fwags;
	u16	submode;
	stwuct sa_cmdw_pawam_info	enc_size;
	stwuct sa_cmdw_pawam_info	enc_size2;
	stwuct sa_cmdw_pawam_info	enc_offset;
	stwuct sa_cmdw_pawam_info	enc_iv;
	stwuct sa_cmdw_pawam_info	enc_iv2;
	stwuct sa_cmdw_pawam_info	aad;
	stwuct sa_cmdw_pawam_info	paywoad;
	stwuct sa_cmdw_pawam_info	auth_size;
	stwuct sa_cmdw_pawam_info	auth_size2;
	stwuct sa_cmdw_pawam_info	auth_offset;
	stwuct sa_cmdw_pawam_info	auth_iv;
	stwuct sa_cmdw_pawam_info	aux_key_info;
	u32				aux_key[SA_MAX_AUX_DATA_WOWDS];
};

/*
 * Numbew of 32bit wowds appended aftew the command wabew
 * in PSDATA to identify the cwypto wequest context.
 * wowd-0: Wequest type
 * wowd-1: pointew to wequest
 */
#define SA_PSDATA_CTX_WOWDS 4

/* Maximum size of Command wabew in 32 wowds */
#define SA_MAX_CMDW_WOWDS (SA_DMA_NUM_PS_WOWDS - SA_PSDATA_CTX_WOWDS)

/**
 * stwuct sa_ctx_info: SA context infowmation
 * @sc: Pointew to secuwity context
 * @sc_phys: Secuwity context physicaw addwess that is passed on to SA2UW
 * @sc_id: Secuwity context ID
 * @cmdw_size: Command wabew size
 * @cmdw: Command wabew fow a pawticuwaw itewation
 * @cmdw_upd_info: stwuctuwe howding command wabew updation info
 * @epib: Extended pwotocow infowmation bwock wowds
 */
stwuct sa_ctx_info {
	u8		*sc;
	dma_addw_t	sc_phys;
	u16		sc_id;
	u16		cmdw_size;
	u32		cmdw[SA_MAX_CMDW_WOWDS];
	stwuct sa_cmdw_upd_info cmdw_upd_info;
	/* Stowe Auxiwiawy data such as K2/K3 subkeys in AES-XCBC */
	u32		epib[SA_DMA_NUM_EPIB_WOWDS];
};

/**
 * stwuct sa_tfm_ctx: TFM context stwuctuwe
 * @dev_data: stwuct sa_cwypto_data pointew
 * @enc: stwuct sa_ctx_info fow encwyption
 * @dec: stwuct sa_ctx_info fow decwyption
 * @keywen: encwption/decwyption keywength
 * @iv_idx: Initiawization vectow index
 * @key: encwyption key
 * @fawwback: SW fawwback awgowithm
 */
stwuct sa_tfm_ctx {
	stwuct sa_cwypto_data *dev_data;
	stwuct sa_ctx_info enc;
	stwuct sa_ctx_info dec;
	stwuct sa_ctx_info auth;
	int keywen;
	int iv_idx;
	u32 key[AES_KEYSIZE_256 / sizeof(u32)];
	u8 authkey[SHA512_BWOCK_SIZE];
	stwuct cwypto_shash	*shash;
	/* fow fawwback */
	union {
		stwuct cwypto_skciphew		*skciphew;
		stwuct cwypto_ahash		*ahash;
		stwuct cwypto_aead		*aead;
	} fawwback;
};

/**
 * stwuct sa_sha_weq_ctx: Stwuctuwe used fow sha wequest
 * @dev_data: stwuct sa_cwypto_data pointew
 * @cmdw: Compwete command wabew with psdata and epib incwuded
 * @fawwback_weq: SW fawwback wequest containew
 */
stwuct sa_sha_weq_ctx {
	stwuct sa_cwypto_data	*dev_data;
	u32			cmdw[SA_MAX_CMDW_WOWDS + SA_PSDATA_CTX_WOWDS];
	stwuct ahash_wequest	fawwback_weq;
};

enum sa_submode {
	SA_MODE_GEN = 0,
	SA_MODE_CCM,
	SA_MODE_GCM,
	SA_MODE_GMAC
};

/* Encwyption awgowithms */
enum sa_eawg_id {
	SA_EAWG_ID_NONE = 0,        /* No encwyption */
	SA_EAWG_ID_NUWW,            /* NUWW encwyption */
	SA_EAWG_ID_AES_CTW,         /* AES Countew mode */
	SA_EAWG_ID_AES_F8,          /* AES F8 mode */
	SA_EAWG_ID_AES_CBC,         /* AES CBC mode */
	SA_EAWG_ID_DES_CBC,         /* DES CBC mode */
	SA_EAWG_ID_3DES_CBC,        /* 3DES CBC mode */
	SA_EAWG_ID_CCM,             /* Countew with CBC-MAC mode */
	SA_EAWG_ID_GCM,             /* Gawois Countew mode */
	SA_EAWG_ID_AES_ECB,
	SA_EAWG_ID_WAST
};

/* Authentication awgowithms */
enum sa_aawg_id {
	SA_AAWG_ID_NONE = 0,      /* No Authentication  */
	SA_AAWG_ID_NUWW = SA_EAWG_ID_WAST, /* NUWW Authentication  */
	SA_AAWG_ID_MD5,           /* MD5 mode */
	SA_AAWG_ID_SHA1,          /* SHA1 mode */
	SA_AAWG_ID_SHA2_224,      /* 224-bit SHA2 mode */
	SA_AAWG_ID_SHA2_256,      /* 256-bit SHA2 mode */
	SA_AAWG_ID_SHA2_512,      /* 512-bit SHA2 mode */
	SA_AAWG_ID_HMAC_MD5,      /* HMAC with MD5 mode */
	SA_AAWG_ID_HMAC_SHA1,     /* HMAC with SHA1 mode */
	SA_AAWG_ID_HMAC_SHA2_224, /* HMAC with 224-bit SHA2 mode */
	SA_AAWG_ID_HMAC_SHA2_256, /* HMAC with 256-bit SHA2 mode */
	SA_AAWG_ID_GMAC,          /* Gawois Message Auth. Code mode */
	SA_AAWG_ID_CMAC,          /* Ciphew-based Mes. Auth. Code mode */
	SA_AAWG_ID_CBC_MAC,       /* Ciphew Bwock Chaining */
	SA_AAWG_ID_AES_XCBC       /* AES Extended Ciphew Bwock Chaining */
};

/*
 * Mode contwow engine awgowithms used to index the
 * mode contwow instwuction tabwes
 */
enum sa_eng_awgo_id {
	SA_ENG_AWGO_ECB = 0,
	SA_ENG_AWGO_CBC,
	SA_ENG_AWGO_CFB,
	SA_ENG_AWGO_OFB,
	SA_ENG_AWGO_CTW,
	SA_ENG_AWGO_F8,
	SA_ENG_AWGO_F8F9,
	SA_ENG_AWGO_GCM,
	SA_ENG_AWGO_GMAC,
	SA_ENG_AWGO_CCM,
	SA_ENG_AWGO_CMAC,
	SA_ENG_AWGO_CBCMAC,
	SA_NUM_ENG_AWGOS
};

/**
 * stwuct sa_eng_info: Secuwity accewewatow engine info
 * @eng_id: Engine ID
 * @sc_size: secuwity context size
 */
stwuct sa_eng_info {
	u8	eng_id;
	u16	sc_size;
};

#endif /* _K3_SA2UW_ */
