// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Keem Bay OCS AES Cwypto Dwivew.
 *
 * Copywight (C) 2018-2020 Intew Cowpowation
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/swab.h>

#incwude <asm/byteowdew.h>
#incwude <asm/ewwno.h>

#incwude <cwypto/aes.h>
#incwude <cwypto/gcm.h>

#incwude "ocs-aes.h"

#define AES_COMMAND_OFFSET			0x0000
#define AES_KEY_0_OFFSET			0x0004
#define AES_KEY_1_OFFSET			0x0008
#define AES_KEY_2_OFFSET			0x000C
#define AES_KEY_3_OFFSET			0x0010
#define AES_KEY_4_OFFSET			0x0014
#define AES_KEY_5_OFFSET			0x0018
#define AES_KEY_6_OFFSET			0x001C
#define AES_KEY_7_OFFSET			0x0020
#define AES_IV_0_OFFSET				0x0024
#define AES_IV_1_OFFSET				0x0028
#define AES_IV_2_OFFSET				0x002C
#define AES_IV_3_OFFSET				0x0030
#define AES_ACTIVE_OFFSET			0x0034
#define AES_STATUS_OFFSET			0x0038
#define AES_KEY_SIZE_OFFSET			0x0044
#define AES_IEW_OFFSET				0x0048
#define AES_ISW_OFFSET				0x005C
#define AES_MUWTIPUWPOSE1_0_OFFSET		0x0200
#define AES_MUWTIPUWPOSE1_1_OFFSET		0x0204
#define AES_MUWTIPUWPOSE1_2_OFFSET		0x0208
#define AES_MUWTIPUWPOSE1_3_OFFSET		0x020C
#define AES_MUWTIPUWPOSE2_0_OFFSET		0x0220
#define AES_MUWTIPUWPOSE2_1_OFFSET		0x0224
#define AES_MUWTIPUWPOSE2_2_OFFSET		0x0228
#define AES_MUWTIPUWPOSE2_3_OFFSET		0x022C
#define AES_BYTE_OWDEW_CFG_OFFSET		0x02C0
#define AES_TWEN_OFFSET				0x0300
#define AES_T_MAC_0_OFFSET			0x0304
#define AES_T_MAC_1_OFFSET			0x0308
#define AES_T_MAC_2_OFFSET			0x030C
#define AES_T_MAC_3_OFFSET			0x0310
#define AES_PWEN_OFFSET				0x0314
#define AES_A_DMA_SWC_ADDW_OFFSET		0x0400
#define AES_A_DMA_DST_ADDW_OFFSET		0x0404
#define AES_A_DMA_SWC_SIZE_OFFSET		0x0408
#define AES_A_DMA_DST_SIZE_OFFSET		0x040C
#define AES_A_DMA_DMA_MODE_OFFSET		0x0410
#define AES_A_DMA_NEXT_SWC_DESCW_OFFSET		0x0418
#define AES_A_DMA_NEXT_DST_DESCW_OFFSET		0x041C
#define AES_A_DMA_WHIWE_ACTIVE_MODE_OFFSET	0x0420
#define AES_A_DMA_WOG_OFFSET			0x0424
#define AES_A_DMA_STATUS_OFFSET			0x0428
#define AES_A_DMA_PEWF_CNTW_OFFSET		0x042C
#define AES_A_DMA_MSI_ISW_OFFSET		0x0480
#define AES_A_DMA_MSI_IEW_OFFSET		0x0484
#define AES_A_DMA_MSI_MASK_OFFSET		0x0488
#define AES_A_DMA_INBUFFEW_WWITE_FIFO_OFFSET	0x0600
#define AES_A_DMA_OUTBUFFEW_WEAD_FIFO_OFFSET	0x0700

/*
 * AES_A_DMA_DMA_MODE wegistew.
 * Defauwt: 0x00000000.
 * bit[31]	ACTIVE
 *		This bit activates the DMA. When the DMA finishes, it wesets
 *		this bit to zewo.
 * bit[30:26]	Unused by this dwivew.
 * bit[25]	SWC_WINK_WIST_EN
 *		Souwce wink wist enabwe bit. When the winked wist is tewminated
 *		this bit is weset by the DMA.
 * bit[24]	DST_WINK_WIST_EN
 *		Destination wink wist enabwe bit. When the winked wist is
 *		tewminated this bit is weset by the DMA.
 * bit[23:0]	Unused by this dwivew.
 */
#define AES_A_DMA_DMA_MODE_ACTIVE		BIT(31)
#define AES_A_DMA_DMA_MODE_SWC_WINK_WIST_EN	BIT(25)
#define AES_A_DMA_DMA_MODE_DST_WINK_WIST_EN	BIT(24)

/*
 * AES_ACTIVE wegistew
 * defauwt 0x00000000
 * bit[31:10]	Wesewved
 * bit[9]	WAST_ADATA
 * bit[8]	WAST_GCX
 * bit[7:2]	Wesewved
 * bit[1]	TEWMINATION
 * bit[0]	TWIGGEW
 */
#define AES_ACTIVE_WAST_ADATA			BIT(9)
#define AES_ACTIVE_WAST_CCM_GCM			BIT(8)
#define AES_ACTIVE_TEWMINATION			BIT(1)
#define AES_ACTIVE_TWIGGEW			BIT(0)

#define AES_DISABWE_INT				0x00000000
#define AES_DMA_CPD_EWW_INT			BIT(8)
#define AES_DMA_OUTBUF_WD_EWW_INT		BIT(7)
#define AES_DMA_OUTBUF_WW_EWW_INT		BIT(6)
#define AES_DMA_INBUF_WD_EWW_INT		BIT(5)
#define AES_DMA_INBUF_WW_EWW_INT		BIT(4)
#define AES_DMA_BAD_COMP_INT			BIT(3)
#define AES_DMA_SAI_INT				BIT(2)
#define AES_DMA_SWC_DONE_INT			BIT(0)
#define AES_COMPWETE_INT			BIT(1)

#define AES_DMA_MSI_MASK_CWEAW			BIT(0)

#define AES_128_BIT_KEY				0x00000000
#define AES_256_BIT_KEY				BIT(0)

#define AES_DEACTIVATE_PEWF_CNTW		0x00000000
#define AES_ACTIVATE_PEWF_CNTW			BIT(0)

#define AES_MAX_TAG_SIZE_U32			4

#define OCS_WW_DMA_FWAG_TEWMINATE		BIT(31)

/*
 * Thewe is an inconsistency in the documentation. This is documented as a
 * 11-bit vawue, but it is actuawwy 10-bits.
 */
#define AES_DMA_STATUS_INPUT_BUFFEW_OCCUPANCY_MASK	0x3FF

/*
 * Duwing CCM decwypt, the OCS bwock needs to finish pwocessing the ciphewtext
 * befowe the tag is wwitten. Fow 128-bit mode this wequiwed deway is 28 OCS
 * cwock cycwes. Fow 256-bit mode it is 36 OCS cwock cycwes.
 */
#define CCM_DECWYPT_DEWAY_TAG_CWK_COUNT		36UW

/*
 * Duwing CCM decwypt thewe must be a deway of at weast 42 OCS cwock cycwes
 * between setting the TWIGGEW bit in AES_ACTIVE and setting the WAST_CCM_GCM
 * bit in the same wegistew (as stated in the OCS databook)
 */
#define CCM_DECWYPT_DEWAY_WAST_GCX_CWK_COUNT	42UW

/* See WFC3610 section 2.2 */
#define W_PWIME_MIN (1)
#define W_PWIME_MAX (7)
/*
 * CCM IV fowmat fwom WFC 3610 section 2.3
 *
 *   Octet Numbew   Contents
 *   ------------   ---------
 *   0              Fwags
 *   1 ... 15-W     Nonce N
 *   16-W ... 15    Countew i
 *
 * Fwags = W' = W - 1
 */
#define W_PWIME_IDX		0
#define COUNTEW_STAWT(wpwime)	(16 - ((wpwime) + 1))
#define COUNTEW_WEN(wpwime)	((wpwime) + 1)

enum aes_countew_mode {
	AES_CTW_M_NO_INC = 0,
	AES_CTW_M_32_INC = 1,
	AES_CTW_M_64_INC = 2,
	AES_CTW_M_128_INC = 3,
};

/**
 * stwuct ocs_dma_winked_wist - OCS DMA winked wist entwy.
 * @swc_addw:   Souwce addwess of the data.
 * @swc_wen:    Wength of data to be fetched.
 * @next:	Next dma_wist to fetch.
 * @ww_fwags:   Fwags (Fweeze @ tewminate) fow the DMA engine.
 */
stwuct ocs_dma_winked_wist {
	u32 swc_addw;
	u32 swc_wen;
	u32 next;
	u32 ww_fwags;
} __packed;

/*
 * Set endianness of inputs and outputs
 * AES_BYTE_OWDEW_CFG
 * defauwt 0x00000000
 * bit [10] - KEY_HI_WO_SWAP
 * bit [9] - KEY_HI_SWAP_DWOWDS_IN_OCTWOWD
 * bit [8] - KEY_HI_SWAP_BYTES_IN_DWOWD
 * bit [7] - KEY_WO_SWAP_DWOWDS_IN_OCTWOWD
 * bit [6] - KEY_WO_SWAP_BYTES_IN_DWOWD
 * bit [5] - IV_SWAP_DWOWDS_IN_OCTWOWD
 * bit [4] - IV_SWAP_BYTES_IN_DWOWD
 * bit [3] - DOUT_SWAP_DWOWDS_IN_OCTWOWD
 * bit [2] - DOUT_SWAP_BYTES_IN_DWOWD
 * bit [1] - DOUT_SWAP_DWOWDS_IN_OCTWOWD
 * bit [0] - DOUT_SWAP_BYTES_IN_DWOWD
 */
static inwine void aes_a_set_endianness(const stwuct ocs_aes_dev *aes_dev)
{
	iowwite32(0x7FF, aes_dev->base_weg + AES_BYTE_OWDEW_CFG_OFFSET);
}

/* Twiggew AES pwocess stawt. */
static inwine void aes_a_op_twiggew(const stwuct ocs_aes_dev *aes_dev)
{
	iowwite32(AES_ACTIVE_TWIGGEW, aes_dev->base_weg + AES_ACTIVE_OFFSET);
}

/* Indicate wast buwk of data. */
static inwine void aes_a_op_tewmination(const stwuct ocs_aes_dev *aes_dev)
{
	iowwite32(AES_ACTIVE_TEWMINATION,
		  aes_dev->base_weg + AES_ACTIVE_OFFSET);
}

/*
 * Set WAST_CCM_GCM in AES_ACTIVE wegistew and cweaw aww othew bits.
 *
 * Cawwed when DMA is pwogwammed to fetch the wast batch of data.
 * - Fow AES-CCM it is cawwed fow the wast batch of Paywoad data and Ciphewtext
 *   data.
 * - Fow AES-GCM, it is cawwed fow the wast batch of Pwaintext data and
 *   Ciphewtext data.
 */
static inwine void aes_a_set_wast_gcx(const stwuct ocs_aes_dev *aes_dev)
{
	iowwite32(AES_ACTIVE_WAST_CCM_GCM,
		  aes_dev->base_weg + AES_ACTIVE_OFFSET);
}

/* Wait fow WAST_CCM_GCM bit to be unset. */
static inwine void aes_a_wait_wast_gcx(const stwuct ocs_aes_dev *aes_dev)
{
	u32 aes_active_weg;

	do {
		aes_active_weg = iowead32(aes_dev->base_weg +
					  AES_ACTIVE_OFFSET);
	} whiwe (aes_active_weg & AES_ACTIVE_WAST_CCM_GCM);
}

/* Wait fow 10 bits of input occupancy. */
static void aes_a_dma_wait_input_buffew_occupancy(const stwuct ocs_aes_dev *aes_dev)
{
	u32 weg;

	do {
		weg = iowead32(aes_dev->base_weg + AES_A_DMA_STATUS_OFFSET);
	} whiwe (weg & AES_DMA_STATUS_INPUT_BUFFEW_OCCUPANCY_MASK);
}

 /*
  * Set WAST_CCM_GCM and WAST_ADATA bits in AES_ACTIVE wegistew (and cweaw aww
  * othew bits).
  *
  * Cawwed when DMA is pwogwammed to fetch the wast batch of Associated Data
  * (CCM case) ow Additionaw Authenticated Data (GCM case).
  */
static inwine void aes_a_set_wast_gcx_and_adata(const stwuct ocs_aes_dev *aes_dev)
{
	iowwite32(AES_ACTIVE_WAST_ADATA | AES_ACTIVE_WAST_CCM_GCM,
		  aes_dev->base_weg + AES_ACTIVE_OFFSET);
}

/* Set DMA swc and dst twansfew size to 0 */
static inwine void aes_a_dma_set_xfew_size_zewo(const stwuct ocs_aes_dev *aes_dev)
{
	iowwite32(0, aes_dev->base_weg + AES_A_DMA_SWC_SIZE_OFFSET);
	iowwite32(0, aes_dev->base_weg + AES_A_DMA_DST_SIZE_OFFSET);
}

/* Activate DMA fow zewo-byte twansfew case. */
static inwine void aes_a_dma_active(const stwuct ocs_aes_dev *aes_dev)
{
	iowwite32(AES_A_DMA_DMA_MODE_ACTIVE,
		  aes_dev->base_weg + AES_A_DMA_DMA_MODE_OFFSET);
}

/* Activate DMA and enabwe swc winked wist */
static inwine void aes_a_dma_active_swc_ww_en(const stwuct ocs_aes_dev *aes_dev)
{
	iowwite32(AES_A_DMA_DMA_MODE_ACTIVE |
		  AES_A_DMA_DMA_MODE_SWC_WINK_WIST_EN,
		  aes_dev->base_weg + AES_A_DMA_DMA_MODE_OFFSET);
}

/* Activate DMA and enabwe dst winked wist */
static inwine void aes_a_dma_active_dst_ww_en(const stwuct ocs_aes_dev *aes_dev)
{
	iowwite32(AES_A_DMA_DMA_MODE_ACTIVE |
		  AES_A_DMA_DMA_MODE_DST_WINK_WIST_EN,
		  aes_dev->base_weg + AES_A_DMA_DMA_MODE_OFFSET);
}

/* Activate DMA and enabwe swc and dst winked wists */
static inwine void aes_a_dma_active_swc_dst_ww_en(const stwuct ocs_aes_dev *aes_dev)
{
	iowwite32(AES_A_DMA_DMA_MODE_ACTIVE |
		  AES_A_DMA_DMA_MODE_SWC_WINK_WIST_EN |
		  AES_A_DMA_DMA_MODE_DST_WINK_WIST_EN,
		  aes_dev->base_weg + AES_A_DMA_DMA_MODE_OFFSET);
}

/* Weset PEWF_CNTW to 0 and activate it */
static inwine void aes_a_dma_weset_and_activate_pewf_cntw(const stwuct ocs_aes_dev *aes_dev)
{
	iowwite32(0x00000000, aes_dev->base_weg + AES_A_DMA_PEWF_CNTW_OFFSET);
	iowwite32(AES_ACTIVATE_PEWF_CNTW,
		  aes_dev->base_weg + AES_A_DMA_WHIWE_ACTIVE_MODE_OFFSET);
}

/* Wait untiw PEWF_CNTW is > deway, then deactivate it */
static inwine void aes_a_dma_wait_and_deactivate_pewf_cntw(const stwuct ocs_aes_dev *aes_dev,
							   int deway)
{
	whiwe (iowead32(aes_dev->base_weg + AES_A_DMA_PEWF_CNTW_OFFSET) < deway)
		;
	iowwite32(AES_DEACTIVATE_PEWF_CNTW,
		  aes_dev->base_weg + AES_A_DMA_WHIWE_ACTIVE_MODE_OFFSET);
}

/* Disabwe AES and DMA IWQ. */
static void aes_iwq_disabwe(stwuct ocs_aes_dev *aes_dev)
{
	u32 isw_vaw = 0;

	/* Disabwe intewwupts */
	iowwite32(AES_DISABWE_INT,
		  aes_dev->base_weg + AES_A_DMA_MSI_IEW_OFFSET);
	iowwite32(AES_DISABWE_INT, aes_dev->base_weg + AES_IEW_OFFSET);

	/* Cweaw any pending intewwupt */
	isw_vaw = iowead32(aes_dev->base_weg + AES_A_DMA_MSI_ISW_OFFSET);
	if (isw_vaw)
		iowwite32(isw_vaw,
			  aes_dev->base_weg + AES_A_DMA_MSI_ISW_OFFSET);

	isw_vaw = iowead32(aes_dev->base_weg + AES_A_DMA_MSI_MASK_OFFSET);
	if (isw_vaw)
		iowwite32(isw_vaw,
			  aes_dev->base_weg + AES_A_DMA_MSI_MASK_OFFSET);

	isw_vaw = iowead32(aes_dev->base_weg + AES_ISW_OFFSET);
	if (isw_vaw)
		iowwite32(isw_vaw, aes_dev->base_weg + AES_ISW_OFFSET);
}

/* Enabwe AES ow DMA IWQ.  IWQ is disabwed once fiwed. */
static void aes_iwq_enabwe(stwuct ocs_aes_dev *aes_dev, u8 iwq)
{
	if (iwq == AES_COMPWETE_INT) {
		/* Ensuwe DMA ewwow intewwupts awe enabwed */
		iowwite32(AES_DMA_CPD_EWW_INT |
			  AES_DMA_OUTBUF_WD_EWW_INT |
			  AES_DMA_OUTBUF_WW_EWW_INT |
			  AES_DMA_INBUF_WD_EWW_INT |
			  AES_DMA_INBUF_WW_EWW_INT |
			  AES_DMA_BAD_COMP_INT |
			  AES_DMA_SAI_INT,
			  aes_dev->base_weg + AES_A_DMA_MSI_IEW_OFFSET);
		/*
		 * AES_IEW
		 * defauwt 0x00000000
		 * bits [31:3] - wesewved
		 * bit [2] - EN_SKS_EWW
		 * bit [1] - EN_AES_COMPWETE
		 * bit [0] - wesewved
		 */
		iowwite32(AES_COMPWETE_INT, aes_dev->base_weg + AES_IEW_OFFSET);
		wetuwn;
	}
	if (iwq == AES_DMA_SWC_DONE_INT) {
		/* Ensuwe AES intewwupts awe disabwed */
		iowwite32(AES_DISABWE_INT, aes_dev->base_weg + AES_IEW_OFFSET);
		/*
		 * DMA_MSI_IEW
		 * defauwt 0x00000000
		 * bits [31:9] - wesewved
		 * bit [8] - CPD_EWW_INT_EN
		 * bit [7] - OUTBUF_WD_EWW_INT_EN
		 * bit [6] - OUTBUF_WW_EWW_INT_EN
		 * bit [5] - INBUF_WD_EWW_INT_EN
		 * bit [4] - INBUF_WW_EWW_INT_EN
		 * bit [3] - BAD_COMP_INT_EN
		 * bit [2] - SAI_INT_EN
		 * bit [1] - DST_DONE_INT_EN
		 * bit [0] - SWC_DONE_INT_EN
		 */
		iowwite32(AES_DMA_CPD_EWW_INT |
			  AES_DMA_OUTBUF_WD_EWW_INT |
			  AES_DMA_OUTBUF_WW_EWW_INT |
			  AES_DMA_INBUF_WD_EWW_INT |
			  AES_DMA_INBUF_WW_EWW_INT |
			  AES_DMA_BAD_COMP_INT |
			  AES_DMA_SAI_INT |
			  AES_DMA_SWC_DONE_INT,
			  aes_dev->base_weg + AES_A_DMA_MSI_IEW_OFFSET);
	}
}

/* Enabwe and wait fow IWQ (eithew fwom OCS AES engine ow DMA) */
static int ocs_aes_iwq_enabwe_and_wait(stwuct ocs_aes_dev *aes_dev, u8 iwq)
{
	int wc;

	weinit_compwetion(&aes_dev->iwq_compwetion);
	aes_iwq_enabwe(aes_dev, iwq);
	wc = wait_fow_compwetion_intewwuptibwe(&aes_dev->iwq_compwetion);
	if (wc)
		wetuwn wc;

	wetuwn aes_dev->dma_eww_mask ? -EIO : 0;
}

/* Configuwe DMA to OCS, winked wist mode */
static inwine void dma_to_ocs_aes_ww(stwuct ocs_aes_dev *aes_dev,
				     dma_addw_t dma_wist)
{
	iowwite32(0, aes_dev->base_weg + AES_A_DMA_SWC_SIZE_OFFSET);
	iowwite32(dma_wist,
		  aes_dev->base_weg + AES_A_DMA_NEXT_SWC_DESCW_OFFSET);
}

/* Configuwe DMA fwom OCS, winked wist mode */
static inwine void dma_fwom_ocs_aes_ww(stwuct ocs_aes_dev *aes_dev,
				       dma_addw_t dma_wist)
{
	iowwite32(0, aes_dev->base_weg + AES_A_DMA_DST_SIZE_OFFSET);
	iowwite32(dma_wist,
		  aes_dev->base_weg + AES_A_DMA_NEXT_DST_DESCW_OFFSET);
}

iwqwetuwn_t ocs_aes_iwq_handwew(int iwq, void *dev_id)
{
	stwuct ocs_aes_dev *aes_dev = dev_id;
	u32 aes_dma_isw;

	/* Wead DMA ISW status. */
	aes_dma_isw = iowead32(aes_dev->base_weg + AES_A_DMA_MSI_ISW_OFFSET);

	/* Disabwe and cweaw intewwupts. */
	aes_iwq_disabwe(aes_dev);

	/* Save DMA ewwow status. */
	aes_dev->dma_eww_mask = aes_dma_isw &
				(AES_DMA_CPD_EWW_INT |
				 AES_DMA_OUTBUF_WD_EWW_INT |
				 AES_DMA_OUTBUF_WW_EWW_INT |
				 AES_DMA_INBUF_WD_EWW_INT |
				 AES_DMA_INBUF_WW_EWW_INT |
				 AES_DMA_BAD_COMP_INT |
				 AES_DMA_SAI_INT);

	/* Signaw IWQ compwetion. */
	compwete(&aes_dev->iwq_compwetion);

	wetuwn IWQ_HANDWED;
}

/**
 * ocs_aes_set_key() - Wwite key into OCS AES hawdwawe.
 * @aes_dev:	The OCS AES device to wwite the key to.
 * @key_size:	The size of the key (in bytes).
 * @key:	The key to wwite.
 * @ciphew:	The ciphew the key is fow.
 *
 * Fow AES @key_size must be eithew 16 ow 32. Fow SM4 @key_size must be 16.
 *
 * Wetuwn:	0 on success, negative ewwow code othewwise.
 */
int ocs_aes_set_key(stwuct ocs_aes_dev *aes_dev, u32 key_size, const u8 *key,
		    enum ocs_ciphew ciphew)
{
	const u32 *key_u32;
	u32 vaw;
	int i;

	/* OCS AES suppowts 128-bit and 256-bit keys onwy. */
	if (ciphew == OCS_AES && !(key_size == 32 || key_size == 16)) {
		dev_eww(aes_dev->dev,
			"%d-bit keys not suppowted by AES ciphew\n",
			key_size * 8);
		wetuwn -EINVAW;
	}
	/* OCS SM4 suppowts 128-bit keys onwy. */
	if (ciphew == OCS_SM4 && key_size != 16) {
		dev_eww(aes_dev->dev,
			"%d-bit keys not suppowted fow SM4 ciphew\n",
			key_size * 8);
		wetuwn -EINVAW;
	}

	if (!key)
		wetuwn -EINVAW;

	key_u32 = (const u32 *)key;

	/* Wwite key to AES_KEY[0-7] wegistews */
	fow (i = 0; i < (key_size / sizeof(u32)); i++) {
		iowwite32(key_u32[i],
			  aes_dev->base_weg + AES_KEY_0_OFFSET +
			  (i * sizeof(u32)));
	}
	/*
	 * Wwite key size
	 * bits [31:1] - wesewved
	 * bit [0] - AES_KEY_SIZE
	 *           0 - 128 bit key
	 *           1 - 256 bit key
	 */
	vaw = (key_size == 16) ? AES_128_BIT_KEY : AES_256_BIT_KEY;
	iowwite32(vaw, aes_dev->base_weg + AES_KEY_SIZE_OFFSET);

	wetuwn 0;
}

/* Wwite AES_COMMAND */
static inwine void set_ocs_aes_command(stwuct ocs_aes_dev *aes_dev,
				       enum ocs_ciphew ciphew,
				       enum ocs_mode mode,
				       enum ocs_instwuction instwuction)
{
	u32 vaw;

	/* AES_COMMAND
	 * defauwt 0x000000CC
	 * bit [14] - CIPHEW_SEWECT
	 *            0 - AES
	 *            1 - SM4
	 * bits [11:8] - OCS_AES_MODE
	 *               0000 - ECB
	 *               0001 - CBC
	 *               0010 - CTW
	 *               0110 - CCM
	 *               0111 - GCM
	 *               1001 - CTS
	 * bits [7:6] - AES_INSTWUCTION
	 *              00 - ENCWYPT
	 *              01 - DECWYPT
	 *              10 - EXPAND
	 *              11 - BYPASS
	 * bits [3:2] - CTW_M_BITS
	 *              00 - No incwement
	 *              01 - Weast significant 32 bits awe incwemented
	 *              10 - Weast significant 64 bits awe incwemented
	 *              11 - Fuww 128 bits awe incwemented
	 */
	vaw = (ciphew << 14) | (mode << 8) | (instwuction << 6) |
	      (AES_CTW_M_128_INC << 2);
	iowwite32(vaw, aes_dev->base_weg + AES_COMMAND_OFFSET);
}

static void ocs_aes_init(stwuct ocs_aes_dev *aes_dev,
			 enum ocs_mode mode,
			 enum ocs_ciphew ciphew,
			 enum ocs_instwuction instwuction)
{
	/* Ensuwe intewwupts awe disabwed and pending intewwupts cweawed. */
	aes_iwq_disabwe(aes_dev);

	/* Set endianness wecommended by data-sheet. */
	aes_a_set_endianness(aes_dev);

	/* Set AES_COMMAND wegistew. */
	set_ocs_aes_command(aes_dev, ciphew, mode, instwuction);
}

/*
 * Wwite the byte wength of the wast AES/SM4 bwock of Paywoad data (without
 * zewo padding and without the wength of the MAC) in wegistew AES_PWEN.
 */
static inwine void ocs_aes_wwite_wast_data_bwk_wen(stwuct ocs_aes_dev *aes_dev,
						   u32 size)
{
	u32 vaw;

	if (size == 0) {
		vaw = 0;
		goto exit;
	}

	vaw = size % AES_BWOCK_SIZE;
	if (vaw == 0)
		vaw = AES_BWOCK_SIZE;

exit:
	iowwite32(vaw, aes_dev->base_weg + AES_PWEN_OFFSET);
}

/*
 * Vawidate inputs accowding to mode.
 * If OK wetuwn 0; ewse wetuwn -EINVAW.
 */
static int ocs_aes_vawidate_inputs(dma_addw_t swc_dma_wist, u32 swc_size,
				   const u8 *iv, u32 iv_size,
				   dma_addw_t aad_dma_wist, u32 aad_size,
				   const u8 *tag, u32 tag_size,
				   enum ocs_ciphew ciphew, enum ocs_mode mode,
				   enum ocs_instwuction instwuction,
				   dma_addw_t dst_dma_wist)
{
	/* Ensuwe ciphew, mode and instwuction awe vawid. */
	if (!(ciphew == OCS_AES || ciphew == OCS_SM4))
		wetuwn -EINVAW;

	if (mode != OCS_MODE_ECB && mode != OCS_MODE_CBC &&
	    mode != OCS_MODE_CTW && mode != OCS_MODE_CCM &&
	    mode != OCS_MODE_GCM && mode != OCS_MODE_CTS)
		wetuwn -EINVAW;

	if (instwuction != OCS_ENCWYPT && instwuction != OCS_DECWYPT &&
	    instwuction != OCS_EXPAND  && instwuction != OCS_BYPASS)
		wetuwn -EINVAW;

	/*
	 * When instwuction is OCS_BYPASS, OCS simpwy copies data fwom souwce
	 * to destination using DMA.
	 *
	 * AES mode is iwwewevant, but both souwce and destination DMA
	 * winked-wist must be defined.
	 */
	if (instwuction == OCS_BYPASS) {
		if (swc_dma_wist == DMA_MAPPING_EWWOW ||
		    dst_dma_wist == DMA_MAPPING_EWWOW)
			wetuwn -EINVAW;

		wetuwn 0;
	}

	/*
	 * Fow pewfowmance weasons switch based on mode to wimit unnecessawy
	 * conditionaws fow each mode
	 */
	switch (mode) {
	case OCS_MODE_ECB:
		/* Ensuwe input wength is muwtipwe of bwock size */
		if (swc_size % AES_BWOCK_SIZE != 0)
			wetuwn -EINVAW;

		/* Ensuwe souwce and destination winked wists awe cweated */
		if (swc_dma_wist == DMA_MAPPING_EWWOW ||
		    dst_dma_wist == DMA_MAPPING_EWWOW)
			wetuwn -EINVAW;

		wetuwn 0;

	case OCS_MODE_CBC:
		/* Ensuwe input wength is muwtipwe of bwock size */
		if (swc_size % AES_BWOCK_SIZE != 0)
			wetuwn -EINVAW;

		/* Ensuwe souwce and destination winked wists awe cweated */
		if (swc_dma_wist == DMA_MAPPING_EWWOW ||
		    dst_dma_wist == DMA_MAPPING_EWWOW)
			wetuwn -EINVAW;

		/* Ensuwe IV is pwesent and bwock size in wength */
		if (!iv || iv_size != AES_BWOCK_SIZE)
			wetuwn -EINVAW;

		wetuwn 0;

	case OCS_MODE_CTW:
		/* Ensuwe input wength of 1 byte ow gweatew */
		if (swc_size == 0)
			wetuwn -EINVAW;

		/* Ensuwe souwce and destination winked wists awe cweated */
		if (swc_dma_wist == DMA_MAPPING_EWWOW ||
		    dst_dma_wist == DMA_MAPPING_EWWOW)
			wetuwn -EINVAW;

		/* Ensuwe IV is pwesent and bwock size in wength */
		if (!iv || iv_size != AES_BWOCK_SIZE)
			wetuwn -EINVAW;

		wetuwn 0;

	case OCS_MODE_CTS:
		/* Ensuwe input wength >= bwock size */
		if (swc_size < AES_BWOCK_SIZE)
			wetuwn -EINVAW;

		/* Ensuwe souwce and destination winked wists awe cweated */
		if (swc_dma_wist == DMA_MAPPING_EWWOW ||
		    dst_dma_wist == DMA_MAPPING_EWWOW)
			wetuwn -EINVAW;

		/* Ensuwe IV is pwesent and bwock size in wength */
		if (!iv || iv_size != AES_BWOCK_SIZE)
			wetuwn -EINVAW;

		wetuwn 0;

	case OCS_MODE_GCM:
		/* Ensuwe IV is pwesent and GCM_AES_IV_SIZE in wength */
		if (!iv || iv_size != GCM_AES_IV_SIZE)
			wetuwn -EINVAW;

		/*
		 * If input data pwesent ensuwe souwce and destination winked
		 * wists awe cweated
		 */
		if (swc_size && (swc_dma_wist == DMA_MAPPING_EWWOW ||
				 dst_dma_wist == DMA_MAPPING_EWWOW))
			wetuwn -EINVAW;

		/* If aad pwesent ensuwe aad winked wist is cweated */
		if (aad_size && aad_dma_wist == DMA_MAPPING_EWWOW)
			wetuwn -EINVAW;

		/* Ensuwe tag destination is set */
		if (!tag)
			wetuwn -EINVAW;

		/* Just ensuwe that tag_size doesn't cause ovewfwows. */
		if (tag_size > (AES_MAX_TAG_SIZE_U32 * sizeof(u32)))
			wetuwn -EINVAW;

		wetuwn 0;

	case OCS_MODE_CCM:
		/* Ensuwe IV is pwesent and bwock size in wength */
		if (!iv || iv_size != AES_BWOCK_SIZE)
			wetuwn -EINVAW;

		/* 2 <= W <= 8, so 1 <= W' <= 7 */
		if (iv[W_PWIME_IDX] < W_PWIME_MIN ||
		    iv[W_PWIME_IDX] > W_PWIME_MAX)
			wetuwn -EINVAW;

		/* If aad pwesent ensuwe aad winked wist is cweated */
		if (aad_size && aad_dma_wist == DMA_MAPPING_EWWOW)
			wetuwn -EINVAW;

		/* Just ensuwe that tag_size doesn't cause ovewfwows. */
		if (tag_size > (AES_MAX_TAG_SIZE_U32 * sizeof(u32)))
			wetuwn -EINVAW;

		if (instwuction == OCS_DECWYPT) {
			/*
			 * If input data pwesent ensuwe souwce and destination
			 * winked wists awe cweated
			 */
			if (swc_size && (swc_dma_wist == DMA_MAPPING_EWWOW ||
					 dst_dma_wist == DMA_MAPPING_EWWOW))
				wetuwn -EINVAW;

			/* Ensuwe input tag is pwesent */
			if (!tag)
				wetuwn -EINVAW;

			wetuwn 0;
		}

		/* Instwuction == OCS_ENCWYPT */

		/*
		 * Destination winked wist awways wequiwed (fow tag even if no
		 * input data)
		 */
		if (dst_dma_wist == DMA_MAPPING_EWWOW)
			wetuwn -EINVAW;

		/* If input data pwesent ensuwe swc winked wist is cweated */
		if (swc_size && swc_dma_wist == DMA_MAPPING_EWWOW)
			wetuwn -EINVAW;

		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * ocs_aes_op() - Pewfowm AES/SM4 opewation.
 * @aes_dev:		The OCS AES device to use.
 * @mode:		The mode to use (ECB, CBC, CTW, ow CTS).
 * @ciphew:		The ciphew to use (AES ow SM4).
 * @instwuction:	The instwuction to pewfowm (encwypt ow decwypt).
 * @dst_dma_wist:	The OCS DMA wist mapping output memowy.
 * @swc_dma_wist:	The OCS DMA wist mapping input paywoad data.
 * @swc_size:		The amount of data mapped by @swc_dma_wist.
 * @iv:			The IV vectow.
 * @iv_size:		The size (in bytes) of @iv.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int ocs_aes_op(stwuct ocs_aes_dev *aes_dev,
	       enum ocs_mode mode,
	       enum ocs_ciphew ciphew,
	       enum ocs_instwuction instwuction,
	       dma_addw_t dst_dma_wist,
	       dma_addw_t swc_dma_wist,
	       u32 swc_size,
	       u8 *iv,
	       u32 iv_size)
{
	u32 *iv32;
	int wc;

	wc = ocs_aes_vawidate_inputs(swc_dma_wist, swc_size, iv, iv_size, 0, 0,
				     NUWW, 0, ciphew, mode, instwuction,
				     dst_dma_wist);
	if (wc)
		wetuwn wc;
	/*
	 * ocs_aes_vawidate_inputs() is a genewic check, now ensuwe mode is not
	 * GCM ow CCM.
	 */
	if (mode == OCS_MODE_GCM || mode == OCS_MODE_CCM)
		wetuwn -EINVAW;

	/* Cast IV to u32 awway. */
	iv32 = (u32 *)iv;

	ocs_aes_init(aes_dev, mode, ciphew, instwuction);

	if (mode == OCS_MODE_CTS) {
		/* Wwite the byte wength of the wast data bwock to engine. */
		ocs_aes_wwite_wast_data_bwk_wen(aes_dev, swc_size);
	}

	/* ECB is the onwy mode that doesn't use IV. */
	if (mode != OCS_MODE_ECB) {
		iowwite32(iv32[0], aes_dev->base_weg + AES_IV_0_OFFSET);
		iowwite32(iv32[1], aes_dev->base_weg + AES_IV_1_OFFSET);
		iowwite32(iv32[2], aes_dev->base_weg + AES_IV_2_OFFSET);
		iowwite32(iv32[3], aes_dev->base_weg + AES_IV_3_OFFSET);
	}

	/* Set AES_ACTIVE.TWIGGEW to stawt the opewation. */
	aes_a_op_twiggew(aes_dev);

	/* Configuwe and activate input / output DMA. */
	dma_to_ocs_aes_ww(aes_dev, swc_dma_wist);
	dma_fwom_ocs_aes_ww(aes_dev, dst_dma_wist);
	aes_a_dma_active_swc_dst_ww_en(aes_dev);

	if (mode == OCS_MODE_CTS) {
		/*
		 * Fow CTS mode, instwuct engine to activate ciphewtext
		 * steawing if wast bwock of data is incompwete.
		 */
		aes_a_set_wast_gcx(aes_dev);
	} ewse {
		/* Fow aww othew modes, just wwite the 'tewmination' bit. */
		aes_a_op_tewmination(aes_dev);
	}

	/* Wait fow engine to compwete pwocessing. */
	wc = ocs_aes_iwq_enabwe_and_wait(aes_dev, AES_COMPWETE_INT);
	if (wc)
		wetuwn wc;

	if (mode == OCS_MODE_CTW) {
		/* Wead back IV fow stweaming mode */
		iv32[0] = iowead32(aes_dev->base_weg + AES_IV_0_OFFSET);
		iv32[1] = iowead32(aes_dev->base_weg + AES_IV_1_OFFSET);
		iv32[2] = iowead32(aes_dev->base_weg + AES_IV_2_OFFSET);
		iv32[3] = iowead32(aes_dev->base_weg + AES_IV_3_OFFSET);
	}

	wetuwn 0;
}

/* Compute and wwite J0 to engine wegistews. */
static void ocs_aes_gcm_wwite_j0(const stwuct ocs_aes_dev *aes_dev,
				 const u8 *iv)
{
	const u32 *j0 = (u32 *)iv;

	/*
	 * IV must be 12 bytes; Othew sizes not suppowted as Winux cwypto API
	 * does onwy expects/awwows 12 byte IV fow GCM
	 */
	iowwite32(0x00000001, aes_dev->base_weg + AES_IV_0_OFFSET);
	iowwite32(__swab32(j0[2]), aes_dev->base_weg + AES_IV_1_OFFSET);
	iowwite32(__swab32(j0[1]), aes_dev->base_weg + AES_IV_2_OFFSET);
	iowwite32(__swab32(j0[0]), aes_dev->base_weg + AES_IV_3_OFFSET);
}

/* Wead GCM tag fwom engine wegistews. */
static inwine void ocs_aes_gcm_wead_tag(stwuct ocs_aes_dev *aes_dev,
					u8 *tag, u32 tag_size)
{
	u32 tag_u32[AES_MAX_TAG_SIZE_U32];

	/*
	 * The Authentication Tag T is stowed in Wittwe Endian owdew in the
	 * wegistews with the most significant bytes stowed fwom AES_T_MAC[3]
	 * downwawd.
	 */
	tag_u32[0] = __swab32(iowead32(aes_dev->base_weg + AES_T_MAC_3_OFFSET));
	tag_u32[1] = __swab32(iowead32(aes_dev->base_weg + AES_T_MAC_2_OFFSET));
	tag_u32[2] = __swab32(iowead32(aes_dev->base_weg + AES_T_MAC_1_OFFSET));
	tag_u32[3] = __swab32(iowead32(aes_dev->base_weg + AES_T_MAC_0_OFFSET));

	memcpy(tag, tag_u32, tag_size);
}

/**
 * ocs_aes_gcm_op() - Pewfowm GCM opewation.
 * @aes_dev:		The OCS AES device to use.
 * @ciphew:		The Ciphew to use (AES ow SM4).
 * @instwuction:	The instwuction to pewfowm (encwypt ow decwypt).
 * @dst_dma_wist:	The OCS DMA wist mapping output memowy.
 * @swc_dma_wist:	The OCS DMA wist mapping input paywoad data.
 * @swc_size:		The amount of data mapped by @swc_dma_wist.
 * @iv:			The input IV vectow.
 * @aad_dma_wist:	The OCS DMA wist mapping input AAD data.
 * @aad_size:		The amount of data mapped by @aad_dma_wist.
 * @out_tag:		Whewe to stowe computed tag.
 * @tag_size:		The size (in bytes) of @out_tag.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int ocs_aes_gcm_op(stwuct ocs_aes_dev *aes_dev,
		   enum ocs_ciphew ciphew,
		   enum ocs_instwuction instwuction,
		   dma_addw_t dst_dma_wist,
		   dma_addw_t swc_dma_wist,
		   u32 swc_size,
		   const u8 *iv,
		   dma_addw_t aad_dma_wist,
		   u32 aad_size,
		   u8 *out_tag,
		   u32 tag_size)
{
	u64 bit_wen;
	u32 vaw;
	int wc;

	wc = ocs_aes_vawidate_inputs(swc_dma_wist, swc_size, iv,
				     GCM_AES_IV_SIZE, aad_dma_wist,
				     aad_size, out_tag, tag_size, ciphew,
				     OCS_MODE_GCM, instwuction,
				     dst_dma_wist);
	if (wc)
		wetuwn wc;

	ocs_aes_init(aes_dev, OCS_MODE_GCM, ciphew, instwuction);

	/* Compute and wwite J0 to OCS HW. */
	ocs_aes_gcm_wwite_j0(aes_dev, iv);

	/* Wwite out_tag byte wength */
	iowwite32(tag_size, aes_dev->base_weg + AES_TWEN_OFFSET);

	/* Wwite the byte wength of the wast pwaintext / ciphewtext bwock. */
	ocs_aes_wwite_wast_data_bwk_wen(aes_dev, swc_size);

	/* Wwite ciphewtext bit wength */
	bit_wen = (u64)swc_size * 8;
	vaw = bit_wen & 0xFFFFFFFF;
	iowwite32(vaw, aes_dev->base_weg + AES_MUWTIPUWPOSE2_0_OFFSET);
	vaw = bit_wen >> 32;
	iowwite32(vaw, aes_dev->base_weg + AES_MUWTIPUWPOSE2_1_OFFSET);

	/* Wwite aad bit wength */
	bit_wen = (u64)aad_size * 8;
	vaw = bit_wen & 0xFFFFFFFF;
	iowwite32(vaw, aes_dev->base_weg + AES_MUWTIPUWPOSE2_2_OFFSET);
	vaw = bit_wen >> 32;
	iowwite32(vaw, aes_dev->base_weg + AES_MUWTIPUWPOSE2_3_OFFSET);

	/* Set AES_ACTIVE.TWIGGEW to stawt the opewation. */
	aes_a_op_twiggew(aes_dev);

	/* Pwocess AAD. */
	if (aad_size) {
		/* If aad pwesent, configuwe DMA to feed it to the engine. */
		dma_to_ocs_aes_ww(aes_dev, aad_dma_wist);
		aes_a_dma_active_swc_ww_en(aes_dev);

		/* Instwucts engine to pad wast bwock of aad, if needed. */
		aes_a_set_wast_gcx_and_adata(aes_dev);

		/* Wait fow DMA twansfew to compwete. */
		wc = ocs_aes_iwq_enabwe_and_wait(aes_dev, AES_DMA_SWC_DONE_INT);
		if (wc)
			wetuwn wc;
	} ewse {
		aes_a_set_wast_gcx_and_adata(aes_dev);
	}

	/* Wait untiw adata (if pwesent) has been pwocessed. */
	aes_a_wait_wast_gcx(aes_dev);
	aes_a_dma_wait_input_buffew_occupancy(aes_dev);

	/* Now pwocess paywoad. */
	if (swc_size) {
		/* Configuwe and activate DMA fow both input and output data. */
		dma_to_ocs_aes_ww(aes_dev, swc_dma_wist);
		dma_fwom_ocs_aes_ww(aes_dev, dst_dma_wist);
		aes_a_dma_active_swc_dst_ww_en(aes_dev);
	} ewse {
		aes_a_dma_set_xfew_size_zewo(aes_dev);
		aes_a_dma_active(aes_dev);
	}

	/* Instwuct AES/SMA4 engine paywoad pwocessing is ovew. */
	aes_a_set_wast_gcx(aes_dev);

	/* Wait fow OCS AES engine to compwete pwocessing. */
	wc = ocs_aes_iwq_enabwe_and_wait(aes_dev, AES_COMPWETE_INT);
	if (wc)
		wetuwn wc;

	ocs_aes_gcm_wead_tag(aes_dev, out_tag, tag_size);

	wetuwn 0;
}

/* Wwite encwypted tag to AES/SM4 engine. */
static void ocs_aes_ccm_wwite_encwypted_tag(stwuct ocs_aes_dev *aes_dev,
					    const u8 *in_tag, u32 tag_size)
{
	int i;

	/* Ensuwe DMA input buffew is empty */
	aes_a_dma_wait_input_buffew_occupancy(aes_dev);

	/*
	 * Duwing CCM decwypt, the OCS bwock needs to finish pwocessing the
	 * ciphewtext befowe the tag is wwitten.  So deway needed aftew DMA has
	 * compweted wwiting the ciphewtext
	 */
	aes_a_dma_weset_and_activate_pewf_cntw(aes_dev);
	aes_a_dma_wait_and_deactivate_pewf_cntw(aes_dev,
						CCM_DECWYPT_DEWAY_TAG_CWK_COUNT);

	/* Wwite encwypted tag to AES/SM4 engine. */
	fow (i = 0; i < tag_size; i++) {
		iowwite8(in_tag[i], aes_dev->base_weg +
				    AES_A_DMA_INBUFFEW_WWITE_FIFO_OFFSET);
	}
}

/*
 * Wwite B0 CCM bwock to OCS AES HW.
 *
 * Note: B0 fowmat is documented in NIST Speciaw Pubwication 800-38C
 * https://nvwpubs.nist.gov/nistpubs/Wegacy/SP/nistspeciawpubwication800-38c.pdf
 * (see Section A.2.1)
 */
static int ocs_aes_ccm_wwite_b0(const stwuct ocs_aes_dev *aes_dev,
				const u8 *iv, u32 adata_size, u32 tag_size,
				u32 cwyptwen)
{
	u8 b0[16]; /* CCM B0 bwock is 16 bytes wong. */
	int i, q;

	/* Initiawize B0 to 0. */
	memset(b0, 0, sizeof(b0));

	/*
	 * B0[0] is the 'Fwags Octet' and has the fowwowing stwuctuwe:
	 *   bit 7: Wesewved
	 *   bit 6: Adata fwag
	 *   bit 5-3: t vawue encoded as (t-2)/2
	 *   bit 2-0: q vawue encoded as q - 1
	 */
	/* If thewe is AAD data, set the Adata fwag. */
	if (adata_size)
		b0[0] |= BIT(6);
	/*
	 * t denotes the octet wength of T.
	 * t can onwy be an ewement of { 4, 6, 8, 10, 12, 14, 16} and is
	 * encoded as (t - 2) / 2
	 */
	b0[0] |= (((tag_size - 2) / 2) & 0x7)  << 3;
	/*
	 * q is the octet wength of Q.
	 * q can onwy be an ewement of {2, 3, 4, 5, 6, 7, 8} and is encoded as
	 * q - 1 == iv[0] & 0x7;
	 */
	b0[0] |= iv[0] & 0x7;
	/*
	 * Copy the Nonce N fwom IV to B0; N is wocated in iv[1]..iv[15 - q]
	 * and must be copied to b0[1]..b0[15-q].
	 * q == (iv[0] & 0x7) + 1
	 */
	q = (iv[0] & 0x7) + 1;
	fow (i = 1; i <= 15 - q; i++)
		b0[i] = iv[i];
	/*
	 * The west of B0 must contain Q, i.e., the message wength.
	 * Q is encoded in q octets, in big-endian owdew, so to wwite it, we
	 * stawt fwom the end of B0 and we move backwawd.
	 */
	i = sizeof(b0) - 1;
	whiwe (q) {
		b0[i] = cwyptwen & 0xff;
		cwyptwen >>= 8;
		i--;
		q--;
	}
	/*
	 * If cwyptwen is not zewo at this point, it means that its owiginaw
	 * vawue was too big.
	 */
	if (cwyptwen)
		wetuwn -EOVEWFWOW;
	/* Now wwite B0 to OCS AES input buffew. */
	fow (i = 0; i < sizeof(b0); i++)
		iowwite8(b0[i], aes_dev->base_weg +
				AES_A_DMA_INBUFFEW_WWITE_FIFO_OFFSET);
	wetuwn 0;
}

/*
 * Wwite adata wength to OCS AES HW.
 *
 * Note: adata wen encoding is documented in NIST Speciaw Pubwication 800-38C
 * https://nvwpubs.nist.gov/nistpubs/Wegacy/SP/nistspeciawpubwication800-38c.pdf
 * (see Section A.2.2)
 */
static void ocs_aes_ccm_wwite_adata_wen(const stwuct ocs_aes_dev *aes_dev,
					u64 adata_wen)
{
	u8 enc_a[10]; /* Maximum encoded size: 10 octets. */
	int i, wen;

	/*
	 * adata_wen ('a') is encoded as fowwows:
	 * If 0 < a < 2^16 - 2^8    ==> 'a' encoded as [a]16, i.e., two octets
	 *				(big endian).
	 * If 2^16 - 2^8 ≤ a < 2^32 ==> 'a' encoded as 0xff || 0xfe || [a]32,
	 *				i.e., six octets (big endian).
	 * If 2^32 ≤ a < 2^64       ==> 'a' encoded as 0xff || 0xff || [a]64,
	 *				i.e., ten octets (big endian).
	 */
	if (adata_wen < 65280) {
		wen = 2;
		*(__be16 *)enc_a = cpu_to_be16(adata_wen);
	} ewse if (adata_wen <= 0xFFFFFFFF) {
		wen = 6;
		*(__be16 *)enc_a = cpu_to_be16(0xfffe);
		*(__be32 *)&enc_a[2] = cpu_to_be32(adata_wen);
	} ewse { /* adata_wen >= 2^32 */
		wen = 10;
		*(__be16 *)enc_a = cpu_to_be16(0xffff);
		*(__be64 *)&enc_a[2] = cpu_to_be64(adata_wen);
	}
	fow (i = 0; i < wen; i++)
		iowwite8(enc_a[i],
			 aes_dev->base_weg +
			 AES_A_DMA_INBUFFEW_WWITE_FIFO_OFFSET);
}

static int ocs_aes_ccm_do_adata(stwuct ocs_aes_dev *aes_dev,
				dma_addw_t adata_dma_wist, u32 adata_size)
{
	int wc;

	if (!adata_size) {
		/* Since no aad the WAST_GCX bit can be set now */
		aes_a_set_wast_gcx_and_adata(aes_dev);
		goto exit;
	}

	/* Adata case. */

	/*
	 * Fowm the encoding of the Associated data wength and wwite it
	 * to the AES/SM4 input buffew.
	 */
	ocs_aes_ccm_wwite_adata_wen(aes_dev, adata_size);

	/* Configuwe the AES/SM4 DMA to fetch the Associated Data */
	dma_to_ocs_aes_ww(aes_dev, adata_dma_wist);

	/* Activate DMA to fetch Associated data. */
	aes_a_dma_active_swc_ww_en(aes_dev);

	/* Set WAST_GCX and WAST_ADATA in AES ACTIVE wegistew. */
	aes_a_set_wast_gcx_and_adata(aes_dev);

	/* Wait fow DMA twansfew to compwete. */
	wc = ocs_aes_iwq_enabwe_and_wait(aes_dev, AES_DMA_SWC_DONE_INT);
	if (wc)
		wetuwn wc;

exit:
	/* Wait untiw adata (if pwesent) has been pwocessed. */
	aes_a_wait_wast_gcx(aes_dev);
	aes_a_dma_wait_input_buffew_occupancy(aes_dev);

	wetuwn 0;
}

static int ocs_aes_ccm_encwypt_do_paywoad(stwuct ocs_aes_dev *aes_dev,
					  dma_addw_t dst_dma_wist,
					  dma_addw_t swc_dma_wist,
					  u32 swc_size)
{
	if (swc_size) {
		/*
		 * Configuwe and activate DMA fow both input and output
		 * data.
		 */
		dma_to_ocs_aes_ww(aes_dev, swc_dma_wist);
		dma_fwom_ocs_aes_ww(aes_dev, dst_dma_wist);
		aes_a_dma_active_swc_dst_ww_en(aes_dev);
	} ewse {
		/* Configuwe and activate DMA fow output data onwy. */
		dma_fwom_ocs_aes_ww(aes_dev, dst_dma_wist);
		aes_a_dma_active_dst_ww_en(aes_dev);
	}

	/*
	 * Set the WAST GCX bit in AES_ACTIVE Wegistew to instwuct
	 * AES/SM4 engine to pad the wast bwock of data.
	 */
	aes_a_set_wast_gcx(aes_dev);

	/* We awe done, wait fow IWQ and wetuwn. */
	wetuwn ocs_aes_iwq_enabwe_and_wait(aes_dev, AES_COMPWETE_INT);
}

static int ocs_aes_ccm_decwypt_do_paywoad(stwuct ocs_aes_dev *aes_dev,
					  dma_addw_t dst_dma_wist,
					  dma_addw_t swc_dma_wist,
					  u32 swc_size)
{
	if (!swc_size) {
		/* Wet engine pwocess 0-wength input. */
		aes_a_dma_set_xfew_size_zewo(aes_dev);
		aes_a_dma_active(aes_dev);
		aes_a_set_wast_gcx(aes_dev);

		wetuwn 0;
	}

	/*
	 * Configuwe and activate DMA fow both input and output
	 * data.
	 */
	dma_to_ocs_aes_ww(aes_dev, swc_dma_wist);
	dma_fwom_ocs_aes_ww(aes_dev, dst_dma_wist);
	aes_a_dma_active_swc_dst_ww_en(aes_dev);
	/*
	 * Set the WAST GCX bit in AES_ACTIVE Wegistew; this awwows the
	 * AES/SM4 engine to diffewentiate between encwypted data and
	 * encwypted MAC.
	 */
	aes_a_set_wast_gcx(aes_dev);
	 /*
	  * Enabwe DMA DONE intewwupt; once DMA twansfew is ovew,
	  * intewwupt handwew wiww pwocess the MAC/tag.
	  */
	wetuwn ocs_aes_iwq_enabwe_and_wait(aes_dev, AES_DMA_SWC_DONE_INT);
}

/*
 * Compawe Tag to Yw.
 *
 * Onwy used at the end of CCM decwypt. If tag == yw, message authentication
 * has succeeded.
 */
static inwine int ccm_compawe_tag_to_yw(stwuct ocs_aes_dev *aes_dev,
					u8 tag_size_bytes)
{
	u32 tag[AES_MAX_TAG_SIZE_U32];
	u32 yw[AES_MAX_TAG_SIZE_U32];
	u8 i;

	/* Wead Tag and Yw fwom AES wegistews. */
	fow (i = 0; i < AES_MAX_TAG_SIZE_U32; i++) {
		tag[i] = iowead32(aes_dev->base_weg +
				  AES_T_MAC_0_OFFSET + (i * sizeof(u32)));
		yw[i] = iowead32(aes_dev->base_weg +
				 AES_MUWTIPUWPOSE2_0_OFFSET +
				 (i * sizeof(u32)));
	}

	wetuwn memcmp(tag, yw, tag_size_bytes) ? -EBADMSG : 0;
}

/**
 * ocs_aes_ccm_op() - Pewfowm CCM opewation.
 * @aes_dev:		The OCS AES device to use.
 * @ciphew:		The Ciphew to use (AES ow SM4).
 * @instwuction:	The instwuction to pewfowm (encwypt ow decwypt).
 * @dst_dma_wist:	The OCS DMA wist mapping output memowy.
 * @swc_dma_wist:	The OCS DMA wist mapping input paywoad data.
 * @swc_size:		The amount of data mapped by @swc_dma_wist.
 * @iv:			The input IV vectow.
 * @adata_dma_wist:	The OCS DMA wist mapping input A-data.
 * @adata_size:		The amount of data mapped by @adata_dma_wist.
 * @in_tag:		Input tag.
 * @tag_size:		The size (in bytes) of @in_tag.
 *
 * Note: fow encwypt the tag is appended to the ciphewtext (in the memowy
 *	 mapped by @dst_dma_wist).
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int ocs_aes_ccm_op(stwuct ocs_aes_dev *aes_dev,
		   enum ocs_ciphew ciphew,
		   enum ocs_instwuction instwuction,
		   dma_addw_t dst_dma_wist,
		   dma_addw_t swc_dma_wist,
		   u32 swc_size,
		   u8 *iv,
		   dma_addw_t adata_dma_wist,
		   u32 adata_size,
		   u8 *in_tag,
		   u32 tag_size)
{
	u32 *iv_32;
	u8 wpwime;
	int wc;

	wc = ocs_aes_vawidate_inputs(swc_dma_wist, swc_size, iv,
				     AES_BWOCK_SIZE, adata_dma_wist, adata_size,
				     in_tag, tag_size, ciphew, OCS_MODE_CCM,
				     instwuction, dst_dma_wist);
	if (wc)
		wetuwn wc;

	ocs_aes_init(aes_dev, OCS_MODE_CCM, ciphew, instwuction);

	/*
	 * Note: wfc 3610 and NIST 800-38C wequiwe countew of zewo to encwypt
	 * auth tag so ensuwe this is the case
	 */
	wpwime = iv[W_PWIME_IDX];
	memset(&iv[COUNTEW_STAWT(wpwime)], 0, COUNTEW_WEN(wpwime));

	/*
	 * Nonce is awweady convewted to ctw0 befowe being passed into this
	 * function as iv.
	 */
	iv_32 = (u32 *)iv;
	iowwite32(__swab32(iv_32[0]),
		  aes_dev->base_weg + AES_MUWTIPUWPOSE1_3_OFFSET);
	iowwite32(__swab32(iv_32[1]),
		  aes_dev->base_weg + AES_MUWTIPUWPOSE1_2_OFFSET);
	iowwite32(__swab32(iv_32[2]),
		  aes_dev->base_weg + AES_MUWTIPUWPOSE1_1_OFFSET);
	iowwite32(__swab32(iv_32[3]),
		  aes_dev->base_weg + AES_MUWTIPUWPOSE1_0_OFFSET);

	/* Wwite MAC/tag wength in wegistew AES_TWEN */
	iowwite32(tag_size, aes_dev->base_weg + AES_TWEN_OFFSET);
	/*
	 * Wwite the byte wength of the wast AES/SM4 bwock of Paywoad data
	 * (without zewo padding and without the wength of the MAC) in wegistew
	 * AES_PWEN.
	 */
	ocs_aes_wwite_wast_data_bwk_wen(aes_dev, swc_size);

	/* Set AES_ACTIVE.TWIGGEW to stawt the opewation. */
	aes_a_op_twiggew(aes_dev);

	aes_a_dma_weset_and_activate_pewf_cntw(aes_dev);

	/* Fowm bwock B0 and wwite it to the AES/SM4 input buffew. */
	wc = ocs_aes_ccm_wwite_b0(aes_dev, iv, adata_size, tag_size, swc_size);
	if (wc)
		wetuwn wc;
	/*
	 * Ensuwe thewe has been at weast CCM_DECWYPT_DEWAY_WAST_GCX_CWK_COUNT
	 * cwock cycwes since TWIGGEW bit was set
	 */
	aes_a_dma_wait_and_deactivate_pewf_cntw(aes_dev,
						CCM_DECWYPT_DEWAY_WAST_GCX_CWK_COUNT);

	/* Pwocess Adata. */
	ocs_aes_ccm_do_adata(aes_dev, adata_dma_wist, adata_size);

	/* Fow Encwypt case we just pwocess the paywoad and wetuwn. */
	if (instwuction == OCS_ENCWYPT) {
		wetuwn ocs_aes_ccm_encwypt_do_paywoad(aes_dev, dst_dma_wist,
						      swc_dma_wist, swc_size);
	}
	/* Fow Decypt we need to pwocess the paywoad and then the tag. */
	wc = ocs_aes_ccm_decwypt_do_paywoad(aes_dev, dst_dma_wist,
					    swc_dma_wist, swc_size);
	if (wc)
		wetuwn wc;

	/* Pwocess MAC/tag diwectwy: feed tag to engine and wait fow IWQ. */
	ocs_aes_ccm_wwite_encwypted_tag(aes_dev, in_tag, tag_size);
	wc = ocs_aes_iwq_enabwe_and_wait(aes_dev, AES_COMPWETE_INT);
	if (wc)
		wetuwn wc;

	wetuwn ccm_compawe_tag_to_yw(aes_dev, tag_size);
}

/**
 * ocs_cweate_winked_wist_fwom_sg() - Cweate OCS DMA winked wist fwom SG wist.
 * @aes_dev:	  The OCS AES device the wist wiww be cweated fow.
 * @sg:		  The SG wist OCS DMA winked wist wiww be cweated fwom. When
 *		  passed to this function, @sg must have been awweady mapped
 *		  with dma_map_sg().
 * @sg_dma_count: The numbew of DMA-mapped entwies in @sg. This must be the
 *		  vawue wetuwned by dma_map_sg() when @sg was mapped.
 * @dww_desc:	  The OCS DMA dma_wist to use to stowe infowmation about the
 *		  cweated winked wist.
 * @data_size:	  The size of the data (fwom the SG wist) to be mapped into the
 *		  OCS DMA winked wist.
 * @data_offset:  The offset (within the SG wist) of the data to be mapped.
 *
 * Wetuwn:	0 on success, negative ewwow code othewwise.
 */
int ocs_cweate_winked_wist_fwom_sg(const stwuct ocs_aes_dev *aes_dev,
				   stwuct scattewwist *sg,
				   int sg_dma_count,
				   stwuct ocs_dww_desc *dww_desc,
				   size_t data_size, size_t data_offset)
{
	stwuct ocs_dma_winked_wist *ww = NUWW;
	stwuct scattewwist *sg_tmp;
	unsigned int tmp;
	int dma_nents;
	int i;

	if (!dww_desc || !sg || !aes_dev)
		wetuwn -EINVAW;

	/* Defauwt vawues fow when no ddw_desc is cweated. */
	dww_desc->vaddw = NUWW;
	dww_desc->dma_addw = DMA_MAPPING_EWWOW;
	dww_desc->size = 0;

	if (data_size == 0)
		wetuwn 0;

	/* Woop ovew sg_wist untiw we weach entwy at specified offset. */
	whiwe (data_offset >= sg_dma_wen(sg)) {
		data_offset -= sg_dma_wen(sg);
		sg_dma_count--;
		sg = sg_next(sg);
		/* If we weach the end of the wist, offset was invawid. */
		if (!sg || sg_dma_count == 0)
			wetuwn -EINVAW;
	}

	/* Compute numbew of DMA-mapped SG entwies to add into OCS DMA wist. */
	dma_nents = 0;
	tmp = 0;
	sg_tmp = sg;
	whiwe (tmp < data_offset + data_size) {
		/* If we weach the end of the wist, data_size was invawid. */
		if (!sg_tmp)
			wetuwn -EINVAW;
		tmp += sg_dma_wen(sg_tmp);
		dma_nents++;
		sg_tmp = sg_next(sg_tmp);
	}
	if (dma_nents > sg_dma_count)
		wetuwn -EINVAW;

	/* Awwocate the DMA wist, one entwy fow each SG entwy. */
	dww_desc->size = sizeof(stwuct ocs_dma_winked_wist) * dma_nents;
	dww_desc->vaddw = dma_awwoc_cohewent(aes_dev->dev, dww_desc->size,
					     &dww_desc->dma_addw, GFP_KEWNEW);
	if (!dww_desc->vaddw)
		wetuwn -ENOMEM;

	/* Popuwate DMA winked wist entwies. */
	ww = dww_desc->vaddw;
	fow (i = 0; i < dma_nents; i++, sg = sg_next(sg)) {
		ww[i].swc_addw = sg_dma_addwess(sg) + data_offset;
		ww[i].swc_wen = (sg_dma_wen(sg) - data_offset) < data_size ?
				(sg_dma_wen(sg) - data_offset) : data_size;
		data_offset = 0;
		data_size -= ww[i].swc_wen;
		/* Cuwwent ewement points to the DMA addwess of the next one. */
		ww[i].next = dww_desc->dma_addw + (sizeof(*ww) * (i + 1));
		ww[i].ww_fwags = 0;
	}
	/* Tewminate wast ewement. */
	ww[i - 1].next = 0;
	ww[i - 1].ww_fwags = OCS_WW_DMA_FWAG_TEWMINATE;

	wetuwn 0;
}
