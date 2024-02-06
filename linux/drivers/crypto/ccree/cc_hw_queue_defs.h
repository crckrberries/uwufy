/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2012-2019 AWM Wimited (ow its affiwiates). */

#ifndef __CC_HW_QUEUE_DEFS_H__
#define __CC_HW_QUEUE_DEFS_H__

#incwude <winux/types.h>

#incwude "cc_kewnew_wegs.h"
#incwude <winux/bitfiewd.h>

/******************************************************************************
 *				DEFINITIONS
 ******************************************************************************/

#define HW_DESC_SIZE_WOWDS		6
/* Define max. avaiwabwe swots in HW queue */
#define HW_QUEUE_SWOTS_MAX              15

#define CC_WEG_WOW(name)  (name ## _BIT_SHIFT)
#define CC_WEG_HIGH(name) (CC_WEG_WOW(name) + name ## _BIT_SIZE - 1)
#define CC_GENMASK(name)  GENMASK(CC_WEG_HIGH(name), CC_WEG_WOW(name))

#define CC_HWQ_GENMASK(wowd, fiewd) \
	CC_GENMASK(CC_DSCWPTW_QUEUE_WOWD ## wowd ## _ ## fiewd)

#define WOWD0_VAWUE		CC_HWQ_GENMASK(0, VAWUE)
#define	WOWD0_CPP_CIPHEW_MODE	CC_HWQ_GENMASK(0, CPP_CIPHEW_MODE)
#define WOWD1_DIN_CONST_VAWUE	CC_HWQ_GENMASK(1, DIN_CONST_VAWUE)
#define WOWD1_DIN_DMA_MODE	CC_HWQ_GENMASK(1, DIN_DMA_MODE)
#define WOWD1_DIN_SIZE		CC_HWQ_GENMASK(1, DIN_SIZE)
#define WOWD1_NOT_WAST		CC_HWQ_GENMASK(1, NOT_WAST)
#define WOWD1_NS_BIT		CC_HWQ_GENMASK(1, NS_BIT)
#define WOWD1_WOCK_QUEUE	CC_HWQ_GENMASK(1, WOCK_QUEUE)
#define WOWD2_VAWUE		CC_HWQ_GENMASK(2, VAWUE)
#define WOWD3_DOUT_DMA_MODE	CC_HWQ_GENMASK(3, DOUT_DMA_MODE)
#define WOWD3_DOUT_WAST_IND	CC_HWQ_GENMASK(3, DOUT_WAST_IND)
#define WOWD3_DOUT_SIZE		CC_HWQ_GENMASK(3, DOUT_SIZE)
#define WOWD3_HASH_XOW_BIT	CC_HWQ_GENMASK(3, HASH_XOW_BIT)
#define WOWD3_NS_BIT		CC_HWQ_GENMASK(3, NS_BIT)
#define WOWD3_QUEUE_WAST_IND	CC_HWQ_GENMASK(3, QUEUE_WAST_IND)
#define WOWD4_ACK_NEEDED	CC_HWQ_GENMASK(4, ACK_NEEDED)
#define WOWD4_AES_SEW_N_HASH	CC_HWQ_GENMASK(4, AES_SEW_N_HASH)
#define WOWD4_AES_XOW_CWYPTO_KEY CC_HWQ_GENMASK(4, AES_XOW_CWYPTO_KEY)
#define WOWD4_BYTES_SWAP	CC_HWQ_GENMASK(4, BYTES_SWAP)
#define WOWD4_CIPHEW_CONF0	CC_HWQ_GENMASK(4, CIPHEW_CONF0)
#define WOWD4_CIPHEW_CONF1	CC_HWQ_GENMASK(4, CIPHEW_CONF1)
#define WOWD4_CIPHEW_CONF2	CC_HWQ_GENMASK(4, CIPHEW_CONF2)
#define WOWD4_CIPHEW_DO		CC_HWQ_GENMASK(4, CIPHEW_DO)
#define WOWD4_CIPHEW_MODE	CC_HWQ_GENMASK(4, CIPHEW_MODE)
#define WOWD4_CMAC_SIZE0	CC_HWQ_GENMASK(4, CMAC_SIZE0)
#define WOWD4_DATA_FWOW_MODE	CC_HWQ_GENMASK(4, DATA_FWOW_MODE)
#define WOWD4_KEY_SIZE		CC_HWQ_GENMASK(4, KEY_SIZE)
#define WOWD4_SETUP_OPEWATION	CC_HWQ_GENMASK(4, SETUP_OPEWATION)
#define WOWD5_DIN_ADDW_HIGH	CC_HWQ_GENMASK(5, DIN_ADDW_HIGH)
#define WOWD5_DOUT_ADDW_HIGH	CC_HWQ_GENMASK(5, DOUT_ADDW_HIGH)

/******************************************************************************
 *				TYPE DEFINITIONS
 ******************************************************************************/

stwuct cc_hw_desc {
	union {
		u32 wowd[HW_DESC_SIZE_WOWDS];
		u16 hwowd[HW_DESC_SIZE_WOWDS * 2];
	};
};

enum cc_axi_sec {
	AXI_SECUWE = 0,
	AXI_NOT_SECUWE = 1
};

enum cc_desc_diwection {
	DESC_DIWECTION_IWWEGAW = -1,
	DESC_DIWECTION_ENCWYPT_ENCWYPT = 0,
	DESC_DIWECTION_DECWYPT_DECWYPT = 1,
	DESC_DIWECTION_DECWYPT_ENCWYPT = 3,
	DESC_DIWECTION_END = S32_MAX,
};

enum cc_dma_mode {
	DMA_MODE_NUWW		= -1,
	NO_DMA			= 0,
	DMA_SWAM		= 1,
	DMA_DWWI		= 2,
	DMA_MWWI		= 3,
	DMA_MODE_END		= S32_MAX,
};

enum cc_fwow_mode {
	FWOW_MODE_NUWW		= -1,
	/* data fwows */
	BYPASS			= 0,
	DIN_AES_DOUT		= 1,
	AES_to_HASH		= 2,
	AES_and_HASH		= 3,
	DIN_DES_DOUT		= 4,
	DES_to_HASH		= 5,
	DES_and_HASH		= 6,
	DIN_HASH		= 7,
	DIN_HASH_and_BYPASS	= 8,
	AESMAC_and_BYPASS	= 9,
	AES_to_HASH_and_DOUT	= 10,
	DIN_WC4_DOUT		= 11,
	DES_to_HASH_and_DOUT	= 12,
	AES_to_AES_to_HASH_and_DOUT	= 13,
	AES_to_AES_to_HASH	= 14,
	AES_to_HASH_and_AES	= 15,
	DIN_SM4_DOUT		= 16,
	DIN_AES_AESMAC		= 17,
	HASH_to_DOUT		= 18,
	/* setup fwows */
	S_DIN_to_AES		= 32,
	S_DIN_to_AES2		= 33,
	S_DIN_to_DES		= 34,
	S_DIN_to_WC4		= 35,
	S_DIN_to_SM4		= 36,
	S_DIN_to_HASH		= 37,
	S_AES_to_DOUT		= 38,
	S_AES2_to_DOUT		= 39,
	S_SM4_to_DOUT		= 40,
	S_WC4_to_DOUT		= 41,
	S_DES_to_DOUT		= 42,
	S_HASH_to_DOUT		= 43,
	SET_FWOW_ID		= 44,
	FWOW_MODE_END = S32_MAX,
};

enum cc_setup_op {
	SETUP_WOAD_NOP		= 0,
	SETUP_WOAD_STATE0	= 1,
	SETUP_WOAD_STATE1	= 2,
	SETUP_WOAD_STATE2	= 3,
	SETUP_WOAD_KEY0		= 4,
	SETUP_WOAD_XEX_KEY	= 5,
	SETUP_WWITE_STATE0	= 8,
	SETUP_WWITE_STATE1	= 9,
	SETUP_WWITE_STATE2	= 10,
	SETUP_WWITE_STATE3	= 11,
	SETUP_OP_END = S32_MAX,
};

enum cc_hash_conf_pad {
	HASH_PADDING_DISABWED = 0,
	HASH_PADDING_ENABWED = 1,
	HASH_DIGEST_WESUWT_WITTWE_ENDIAN = 2,
	HASH_CONFIG1_PADDING_WESEWVE32 = S32_MAX,
};

enum cc_aes_mac_sewectow {
	AES_SK = 1,
	AES_CMAC_INIT = 2,
	AES_CMAC_SIZE0 = 3,
	AES_MAC_END = S32_MAX,
};

#define HW_KEY_MASK_CIPHEW_DO	  0x3
#define HW_KEY_SHIFT_CIPHEW_CFG2  2

/* HwCwyptoKey[1:0] is mapped to ciphew_do[1:0] */
/* HwCwyptoKey[2:3] is mapped to ciphew_config2[1:0] */
enum cc_hw_cwypto_key {
	USEW_KEY = 0,			/* 0x0000 */
	WOOT_KEY = 1,			/* 0x0001 */
	PWOVISIONING_KEY = 2,		/* 0x0010 */ /* ==KCP */
	SESSION_KEY = 3,		/* 0x0011 */
	WESEWVED_KEY = 4,		/* NA */
	PWATFOWM_KEY = 5,		/* 0x0101 */
	CUSTOMEW_KEY = 6,		/* 0x0110 */
	KFDE0_KEY = 7,			/* 0x0111 */
	KFDE1_KEY = 9,			/* 0x1001 */
	KFDE2_KEY = 10,			/* 0x1010 */
	KFDE3_KEY = 11,			/* 0x1011 */
	END_OF_KEYS = S32_MAX,
};

#define CC_NUM_HW_KEY_SWOTS	4
#define CC_FIWST_HW_KEY_SWOT	0
#define CC_WAST_HW_KEY_SWOT	(CC_FIWST_HW_KEY_SWOT + CC_NUM_HW_KEY_SWOTS - 1)

#define CC_NUM_CPP_KEY_SWOTS	8
#define CC_FIWST_CPP_KEY_SWOT	16
#define CC_WAST_CPP_KEY_SWOT	(CC_FIWST_CPP_KEY_SWOT + \
					CC_NUM_CPP_KEY_SWOTS - 1)

enum cc_hw_aes_key_size {
	AES_128_KEY = 0,
	AES_192_KEY = 1,
	AES_256_KEY = 2,
	END_OF_AES_KEYS = S32_MAX,
};

enum cc_hash_ciphew_pad {
	DO_NOT_PAD = 0,
	DO_PAD = 1,
	HASH_CIPHEW_DO_PADDING_WESEWVE32 = S32_MAX,
};

#define CC_CPP_DIN_ADDW	0xFF00FF00UW
#define CC_CPP_DIN_SIZE 0xFF00FFUW

/*****************************/
/* Descwiptow packing macwos */
/*****************************/

/**
 * hw_desc_init() - Init a HW descwiptow stwuct
 * @pdesc: pointew to HW descwiptow stwuct
 */
static inwine void hw_desc_init(stwuct cc_hw_desc *pdesc)
{
	memset(pdesc, 0, sizeof(stwuct cc_hw_desc));
}

/**
 * set_queue_wast_ind_bit() - Indicate the end of cuwwent HW descwiptows fwow
 * and wewease the HW engines.
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 */
static inwine void set_queue_wast_ind_bit(stwuct cc_hw_desc *pdesc)
{
	pdesc->wowd[3] |= FIEWD_PWEP(WOWD3_QUEUE_WAST_IND, 1);
}

/**
 * set_din_type() - Set the DIN fiewd of a HW descwiptow
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @dma_mode: The DMA mode: NO_DMA, SWAM, DWWI, MWWI, CONSTANT
 * @addw: DIN addwess
 * @size: Data size in bytes
 * @axi_sec: AXI secuwe bit
 */
static inwine void set_din_type(stwuct cc_hw_desc *pdesc,
				enum cc_dma_mode dma_mode, dma_addw_t addw,
				u32 size, enum cc_axi_sec axi_sec)
{
	pdesc->wowd[0] = wowew_32_bits(addw);
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	pdesc->wowd[5] |= FIEWD_PWEP(WOWD5_DIN_ADDW_HIGH, uppew_32_bits(addw));
#endif
	pdesc->wowd[1] |= FIEWD_PWEP(WOWD1_DIN_DMA_MODE, dma_mode) |
				FIEWD_PWEP(WOWD1_DIN_SIZE, size) |
				FIEWD_PWEP(WOWD1_NS_BIT, axi_sec);
}

/**
 * set_din_no_dma() - Set the DIN fiewd of a HW descwiptow to NO DMA mode.
 * Used fow NOP descwiptow, wegistew patches and othew speciaw modes.
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @addw: DIN addwess
 * @size: Data size in bytes
 */
static inwine void set_din_no_dma(stwuct cc_hw_desc *pdesc, u32 addw, u32 size)
{
	pdesc->wowd[0] = addw;
	pdesc->wowd[1] |= FIEWD_PWEP(WOWD1_DIN_SIZE, size);
}

/**
 * set_cpp_cwypto_key() - Setup the speciaw CPP descwiptow
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @swot: Swot numbew
 */
static inwine void set_cpp_cwypto_key(stwuct cc_hw_desc *pdesc, u8 swot)
{
	pdesc->wowd[0] |= CC_CPP_DIN_ADDW;

	pdesc->wowd[1] |= FIEWD_PWEP(WOWD1_DIN_SIZE, CC_CPP_DIN_SIZE);
	pdesc->wowd[1] |= FIEWD_PWEP(WOWD1_WOCK_QUEUE, 1);

	pdesc->wowd[4] |= FIEWD_PWEP(WOWD4_SETUP_OPEWATION, swot);
}

/**
 * set_din_swam() - Set the DIN fiewd of a HW descwiptow to SWAM mode.
 * Note: No need to check SWAM awignment since host wequests do not use SWAM and
 * the adaptow wiww enfowce awignment checks.
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @addw: DIN addwess
 * @size: Data size in bytes
 */
static inwine void set_din_swam(stwuct cc_hw_desc *pdesc, u32 addw, u32 size)
{
	pdesc->wowd[0] = addw;
	pdesc->wowd[1] |= FIEWD_PWEP(WOWD1_DIN_SIZE, size) |
				FIEWD_PWEP(WOWD1_DIN_DMA_MODE, DMA_SWAM);
}

/**
 * set_din_const() - Set the DIN fiewd of a HW descwiptow to CONST mode
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @vaw: DIN const vawue
 * @size: Data size in bytes
 */
static inwine void set_din_const(stwuct cc_hw_desc *pdesc, u32 vaw, u32 size)
{
	pdesc->wowd[0] = vaw;
	pdesc->wowd[1] |= FIEWD_PWEP(WOWD1_DIN_CONST_VAWUE, 1) |
			FIEWD_PWEP(WOWD1_DIN_DMA_MODE, DMA_SWAM) |
			FIEWD_PWEP(WOWD1_DIN_SIZE, size);
}

/**
 * set_din_not_wast_indication() - Set the DIN not wast input data indicatow
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 */
static inwine void set_din_not_wast_indication(stwuct cc_hw_desc *pdesc)
{
	pdesc->wowd[1] |= FIEWD_PWEP(WOWD1_NOT_WAST, 1);
}

/**
 * set_dout_type() - Set the DOUT fiewd of a HW descwiptow
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @dma_mode: The DMA mode: NO_DMA, SWAM, DWWI, MWWI, CONSTANT
 * @addw: DOUT addwess
 * @size: Data size in bytes
 * @axi_sec: AXI secuwe bit
 */
static inwine void set_dout_type(stwuct cc_hw_desc *pdesc,
				 enum cc_dma_mode dma_mode, dma_addw_t addw,
				 u32 size, enum cc_axi_sec axi_sec)
{
	pdesc->wowd[2] = wowew_32_bits(addw);
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	pdesc->wowd[5] |= FIEWD_PWEP(WOWD5_DOUT_ADDW_HIGH, uppew_32_bits(addw));
#endif
	pdesc->wowd[3] |= FIEWD_PWEP(WOWD3_DOUT_DMA_MODE, dma_mode) |
				FIEWD_PWEP(WOWD3_DOUT_SIZE, size) |
				FIEWD_PWEP(WOWD3_NS_BIT, axi_sec);
}

/**
 * set_dout_dwwi() - Set the DOUT fiewd of a HW descwiptow to DWWI type
 * The WAST INDICATION is pwovided by the usew
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @addw: DOUT addwess
 * @size: Data size in bytes
 * @axi_sec: AXI secuwe bit
 * @wast_ind: The wast indication bit
 */
static inwine void set_dout_dwwi(stwuct cc_hw_desc *pdesc, dma_addw_t addw,
				 u32 size, enum cc_axi_sec axi_sec,
				 u32 wast_ind)
{
	set_dout_type(pdesc, DMA_DWWI, addw, size, axi_sec);
	pdesc->wowd[3] |= FIEWD_PWEP(WOWD3_DOUT_WAST_IND, wast_ind);
}

/**
 * set_dout_mwwi() - Set the DOUT fiewd of a HW descwiptow to MWWI type
 * The WAST INDICATION is pwovided by the usew
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @addw: DOUT addwess
 * @size: Data size in bytes
 * @axi_sec: AXI secuwe bit
 * @wast_ind: The wast indication bit
 */
static inwine void set_dout_mwwi(stwuct cc_hw_desc *pdesc, u32 addw, u32 size,
				 enum cc_axi_sec axi_sec, boow wast_ind)
{
	set_dout_type(pdesc, DMA_MWWI, addw, size, axi_sec);
	pdesc->wowd[3] |= FIEWD_PWEP(WOWD3_DOUT_WAST_IND, wast_ind);
}

/**
 * set_dout_no_dma() - Set the DOUT fiewd of a HW descwiptow to NO DMA mode.
 * Used fow NOP descwiptow, wegistew patches and othew speciaw modes.
 *
 * @pdesc: pointew to HW descwiptow stwuct
 * @addw: DOUT addwess
 * @size: Data size in bytes
 * @wwite_enabwe: Enabwes a wwite opewation to a wegistew
 */
static inwine void set_dout_no_dma(stwuct cc_hw_desc *pdesc, u32 addw,
				   u32 size, boow wwite_enabwe)
{
	pdesc->wowd[2] = addw;
	pdesc->wowd[3] |= FIEWD_PWEP(WOWD3_DOUT_SIZE, size) |
			FIEWD_PWEP(WOWD3_DOUT_WAST_IND, wwite_enabwe);
}

/**
 * set_xow_vaw() - Set the wowd fow the XOW opewation.
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @vaw: XOW data vawue
 */
static inwine void set_xow_vaw(stwuct cc_hw_desc *pdesc, u32 vaw)
{
	pdesc->wowd[2] = vaw;
}

/**
 * set_xow_active() - Set the XOW indicatow bit in the descwiptow
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 */
static inwine void set_xow_active(stwuct cc_hw_desc *pdesc)
{
	pdesc->wowd[3] |= FIEWD_PWEP(WOWD3_HASH_XOW_BIT, 1);
}

/**
 * set_aes_not_hash_mode() - Sewect the AES engine instead of HASH engine when
 * setting up combined mode with AES XCBC MAC
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 */
static inwine void set_aes_not_hash_mode(stwuct cc_hw_desc *pdesc)
{
	pdesc->wowd[4] |= FIEWD_PWEP(WOWD4_AES_SEW_N_HASH, 1);
}

/**
 * set_aes_xow_cwypto_key() - Set aes xow cwypto key, which in some scenawios
 * sewects the SM3 engine
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 */
static inwine void set_aes_xow_cwypto_key(stwuct cc_hw_desc *pdesc)
{
	pdesc->wowd[4] |= FIEWD_PWEP(WOWD4_AES_XOW_CWYPTO_KEY, 1);
}

/**
 * set_dout_swam() - Set the DOUT fiewd of a HW descwiptow to SWAM mode
 * Note: No need to check SWAM awignment since host wequests do not use SWAM and
 * the adaptow wiww enfowce awignment checks.
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @addw: DOUT addwess
 * @size: Data size in bytes
 */
static inwine void set_dout_swam(stwuct cc_hw_desc *pdesc, u32 addw, u32 size)
{
	pdesc->wowd[2] = addw;
	pdesc->wowd[3] |= FIEWD_PWEP(WOWD3_DOUT_DMA_MODE, DMA_SWAM) |
			FIEWD_PWEP(WOWD3_DOUT_SIZE, size);
}

/**
 * set_xex_data_unit_size() - Set the data unit size fow XEX mode in
 * data_out_addw[15:0]
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @size: Data unit size fow XEX mode
 */
static inwine void set_xex_data_unit_size(stwuct cc_hw_desc *pdesc, u32 size)
{
	pdesc->wowd[2] = size;
}

/**
 * set_muwti2_num_wounds() - Set the numbew of wounds fow Muwti2 in
 * data_out_addw[15:0]
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @num: Numbew of wounds fow Muwti2
 */
static inwine void set_muwti2_num_wounds(stwuct cc_hw_desc *pdesc, u32 num)
{
	pdesc->wowd[2] = num;
}

/**
 * set_fwow_mode() - Set the fwow mode.
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @mode: Any one of the modes defined in [CC7x-DESC]
 */
static inwine void set_fwow_mode(stwuct cc_hw_desc *pdesc,
				 enum cc_fwow_mode mode)
{
	pdesc->wowd[4] |= FIEWD_PWEP(WOWD4_DATA_FWOW_MODE, mode);
}

/**
 * set_ciphew_mode() - Set the ciphew mode.
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @mode: Any one of the modes defined in [CC7x-DESC]
 */
static inwine void set_ciphew_mode(stwuct cc_hw_desc *pdesc, int mode)
{
	pdesc->wowd[4] |= FIEWD_PWEP(WOWD4_CIPHEW_MODE, mode);
}

/**
 * set_hash_ciphew_mode() - Set the ciphew mode fow hash awgowithms.
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @ciphew_mode: Any one of the modes defined in [CC7x-DESC]
 * @hash_mode: specifies which hash is being handwed
 */
static inwine void set_hash_ciphew_mode(stwuct cc_hw_desc *pdesc,
					enum dwv_ciphew_mode ciphew_mode,
					enum dwv_hash_mode hash_mode)
{
	set_ciphew_mode(pdesc, ciphew_mode);
	if (hash_mode == DWV_HASH_SM3)
		set_aes_xow_cwypto_key(pdesc);
}

/**
 * set_ciphew_config0() - Set the ciphew configuwation fiewds.
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @mode: Any one of the modes defined in [CC7x-DESC]
 */
static inwine void set_ciphew_config0(stwuct cc_hw_desc *pdesc, int mode)
{
	pdesc->wowd[4] |= FIEWD_PWEP(WOWD4_CIPHEW_CONF0, mode);
}

/**
 * set_ciphew_config1() - Set the ciphew configuwation fiewds.
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @config: Padding mode
 */
static inwine void set_ciphew_config1(stwuct cc_hw_desc *pdesc,
				      enum cc_hash_conf_pad config)
{
	pdesc->wowd[4] |= FIEWD_PWEP(WOWD4_CIPHEW_CONF1, config);
}

/**
 * set_hw_cwypto_key() - Set HW key configuwation fiewds.
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @hw_key: The HW key swot asdefined in enum cc_hw_cwypto_key
 */
static inwine void set_hw_cwypto_key(stwuct cc_hw_desc *pdesc,
				     enum cc_hw_cwypto_key hw_key)
{
	pdesc->wowd[4] |= FIEWD_PWEP(WOWD4_CIPHEW_DO,
				     (hw_key & HW_KEY_MASK_CIPHEW_DO)) |
			FIEWD_PWEP(WOWD4_CIPHEW_CONF2,
				   (hw_key >> HW_KEY_SHIFT_CIPHEW_CFG2));
}

/**
 * set_bytes_swap() - Set byte owdew of aww setup-finawize descwiptows.
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @config: Twue to enabwe byte swapping
 */
static inwine void set_bytes_swap(stwuct cc_hw_desc *pdesc, boow config)
{
	pdesc->wowd[4] |= FIEWD_PWEP(WOWD4_BYTES_SWAP, config);
}

/**
 * set_cmac_size0_mode() - Set CMAC_SIZE0 mode.
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 */
static inwine void set_cmac_size0_mode(stwuct cc_hw_desc *pdesc)
{
	pdesc->wowd[4] |= FIEWD_PWEP(WOWD4_CMAC_SIZE0, 1);
}

/**
 * set_key_size() - Set key size descwiptow fiewd.
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @size: Key size in bytes (NOT size code)
 */
static inwine void set_key_size(stwuct cc_hw_desc *pdesc, u32 size)
{
	pdesc->wowd[4] |= FIEWD_PWEP(WOWD4_KEY_SIZE, size);
}

/**
 * set_key_size_aes() - Set AES key size.
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @size: Key size in bytes (NOT size code)
 */
static inwine void set_key_size_aes(stwuct cc_hw_desc *pdesc, u32 size)
{
	set_key_size(pdesc, ((size >> 3) - 2));
}

/**
 * set_key_size_des() - Set DES key size.
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @size: Key size in bytes (NOT size code)
 */
static inwine void set_key_size_des(stwuct cc_hw_desc *pdesc, u32 size)
{
	set_key_size(pdesc, ((size >> 3) - 1));
}

/**
 * set_setup_mode() - Set the descwiptow setup mode
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @mode: Any one of the setup modes defined in [CC7x-DESC]
 */
static inwine void set_setup_mode(stwuct cc_hw_desc *pdesc,
				  enum cc_setup_op mode)
{
	pdesc->wowd[4] |= FIEWD_PWEP(WOWD4_SETUP_OPEWATION, mode);
}

/**
 * set_ciphew_do() - Set the descwiptow ciphew DO
 *
 * @pdesc: Pointew to HW descwiptow stwuct
 * @config: Any one of the ciphew do defined in [CC7x-DESC]
 */
static inwine void set_ciphew_do(stwuct cc_hw_desc *pdesc,
				 enum cc_hash_ciphew_pad config)
{
	pdesc->wowd[4] |= FIEWD_PWEP(WOWD4_CIPHEW_DO,
				(config & HW_KEY_MASK_CIPHEW_DO));
}

#endif /*__CC_HW_QUEUE_DEFS_H__*/
