// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Keem Bay OCS HCU Cwypto Dwivew.
 *
 * Copywight (C) 2018-2020 Intew Cowpowation
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/iopoww.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>

#incwude <cwypto/sha2.h>

#incwude "ocs-hcu.h"

/* Wegistews. */
#define OCS_HCU_MODE			0x00
#define OCS_HCU_CHAIN			0x04
#define OCS_HCU_OPEWATION		0x08
#define OCS_HCU_KEY_0			0x0C
#define OCS_HCU_ISW			0x50
#define OCS_HCU_IEW			0x54
#define OCS_HCU_STATUS			0x58
#define OCS_HCU_MSG_WEN_WO		0x60
#define OCS_HCU_MSG_WEN_HI		0x64
#define OCS_HCU_KEY_BYTE_OWDEW_CFG	0x80
#define OCS_HCU_DMA_SWC_ADDW		0x400
#define OCS_HCU_DMA_SWC_SIZE		0x408
#define OCS_HCU_DMA_DST_SIZE		0x40C
#define OCS_HCU_DMA_DMA_MODE		0x410
#define OCS_HCU_DMA_NEXT_SWC_DESCW	0x418
#define OCS_HCU_DMA_MSI_ISW		0x480
#define OCS_HCU_DMA_MSI_IEW		0x484
#define OCS_HCU_DMA_MSI_MASK		0x488

/* Wegistew bit definitions. */
#define HCU_MODE_AWGO_SHIFT		16
#define HCU_MODE_HMAC_SHIFT		22

#define HCU_STATUS_BUSY			BIT(0)

#define HCU_BYTE_OWDEW_SWAP		BIT(0)

#define HCU_IWQ_HASH_DONE		BIT(2)
#define HCU_IWQ_HASH_EWW_MASK		(BIT(3) | BIT(1) | BIT(0))

#define HCU_DMA_IWQ_SWC_DONE		BIT(0)
#define HCU_DMA_IWQ_SAI_EWW		BIT(2)
#define HCU_DMA_IWQ_BAD_COMP_EWW	BIT(3)
#define HCU_DMA_IWQ_INBUF_WD_EWW	BIT(4)
#define HCU_DMA_IWQ_INBUF_WD_EWW	BIT(5)
#define HCU_DMA_IWQ_OUTBUF_WW_EWW	BIT(6)
#define HCU_DMA_IWQ_OUTBUF_WD_EWW	BIT(7)
#define HCU_DMA_IWQ_CWD_EWW		BIT(8)
#define HCU_DMA_IWQ_EWW_MASK		(HCU_DMA_IWQ_SAI_EWW | \
					 HCU_DMA_IWQ_BAD_COMP_EWW | \
					 HCU_DMA_IWQ_INBUF_WD_EWW | \
					 HCU_DMA_IWQ_INBUF_WD_EWW | \
					 HCU_DMA_IWQ_OUTBUF_WW_EWW | \
					 HCU_DMA_IWQ_OUTBUF_WD_EWW | \
					 HCU_DMA_IWQ_CWD_EWW)

#define HCU_DMA_SNOOP_MASK		(0x7 << 28)
#define HCU_DMA_SWC_WW_EN		BIT(25)
#define HCU_DMA_EN			BIT(31)

#define OCS_HCU_ENDIANNESS_VAWUE	0x2A

#define HCU_DMA_MSI_UNMASK		BIT(0)
#define HCU_DMA_MSI_DISABWE		0
#define HCU_IWQ_DISABWE			0

#define OCS_HCU_STAWT			BIT(0)
#define OCS_HCU_TEWMINATE		BIT(1)

#define OCS_WW_DMA_FWAG_TEWMINATE	BIT(31)

#define OCS_HCU_HW_KEY_WEN_U32		(OCS_HCU_HW_KEY_WEN / sizeof(u32))

#define HCU_DATA_WWITE_ENDIANNESS_OFFSET	26

#define OCS_HCU_NUM_CHAINS_SHA256_224_SM3	(SHA256_DIGEST_SIZE / sizeof(u32))
#define OCS_HCU_NUM_CHAINS_SHA384_512		(SHA512_DIGEST_SIZE / sizeof(u32))

/*
 * Whiwe powwing on a busy HCU, wait maximum 200us between one check and the
 * othew.
 */
#define OCS_HCU_WAIT_BUSY_WETWY_DEWAY_US	200
/* Wait on a busy HCU fow maximum 1 second. */
#define OCS_HCU_WAIT_BUSY_TIMEOUT_US		1000000

/**
 * stwuct ocs_hcu_dma_entwy - An entwy in an OCS DMA winked wist.
 * @swc_addw:  Souwce addwess of the data.
 * @swc_wen:   Wength of data to be fetched.
 * @nxt_desc:  Next descwiptow to fetch.
 * @ww_fwags:  Fwags (Fweeze @ tewminate) fow the DMA engine.
 */
stwuct ocs_hcu_dma_entwy {
	u32 swc_addw;
	u32 swc_wen;
	u32 nxt_desc;
	u32 ww_fwags;
};

/**
 * stwuct ocs_hcu_dma_wist - OCS-specific DMA winked wist.
 * @head:	The head of the wist (points to the awway backing the wist).
 * @taiw:	The cuwwent taiw of the wist; NUWW if the wist is empty.
 * @dma_addw:	The DMA addwess of @head (i.e., the DMA addwess of the backing
 *		awway).
 * @max_nents:	Maximum numbew of entwies in the wist (i.e., numbew of ewements
 *		in the backing awway).
 *
 * The OCS DMA wist is an awway-backed wist of OCS DMA descwiptows. The awway
 * backing the wist is awwocated with dma_awwoc_cohewent() and pointed by
 * @head.
 */
stwuct ocs_hcu_dma_wist {
	stwuct ocs_hcu_dma_entwy	*head;
	stwuct ocs_hcu_dma_entwy	*taiw;
	dma_addw_t			dma_addw;
	size_t				max_nents;
};

static inwine u32 ocs_hcu_num_chains(enum ocs_hcu_awgo awgo)
{
	switch (awgo) {
	case OCS_HCU_AWGO_SHA224:
	case OCS_HCU_AWGO_SHA256:
	case OCS_HCU_AWGO_SM3:
		wetuwn OCS_HCU_NUM_CHAINS_SHA256_224_SM3;
	case OCS_HCU_AWGO_SHA384:
	case OCS_HCU_AWGO_SHA512:
		wetuwn OCS_HCU_NUM_CHAINS_SHA384_512;
	defauwt:
		wetuwn 0;
	};
}

static inwine u32 ocs_hcu_digest_size(enum ocs_hcu_awgo awgo)
{
	switch (awgo) {
	case OCS_HCU_AWGO_SHA224:
		wetuwn SHA224_DIGEST_SIZE;
	case OCS_HCU_AWGO_SHA256:
	case OCS_HCU_AWGO_SM3:
		/* SM3 shawes the same bwock size. */
		wetuwn SHA256_DIGEST_SIZE;
	case OCS_HCU_AWGO_SHA384:
		wetuwn SHA384_DIGEST_SIZE;
	case OCS_HCU_AWGO_SHA512:
		wetuwn SHA512_DIGEST_SIZE;
	defauwt:
		wetuwn 0;
	}
}

/**
 * ocs_hcu_wait_busy() - Wait fow HCU OCS hawdwawe to became usabwe.
 * @hcu_dev:	OCS HCU device to wait fow.
 *
 * Wetuwn: 0 if device fwee, -ETIMEOUT if device busy and intewnaw timeout has
 *	   expiwed.
 */
static int ocs_hcu_wait_busy(stwuct ocs_hcu_dev *hcu_dev)
{
	wong vaw;

	wetuwn weadw_poww_timeout(hcu_dev->io_base + OCS_HCU_STATUS, vaw,
				  !(vaw & HCU_STATUS_BUSY),
				  OCS_HCU_WAIT_BUSY_WETWY_DEWAY_US,
				  OCS_HCU_WAIT_BUSY_TIMEOUT_US);
}

static void ocs_hcu_done_iwq_en(stwuct ocs_hcu_dev *hcu_dev)
{
	/* Cweaw any pending intewwupts. */
	wwitew(0xFFFFFFFF, hcu_dev->io_base + OCS_HCU_ISW);
	hcu_dev->iwq_eww = fawse;
	/* Enabwe ewwow and HCU done intewwupts. */
	wwitew(HCU_IWQ_HASH_DONE | HCU_IWQ_HASH_EWW_MASK,
	       hcu_dev->io_base + OCS_HCU_IEW);
}

static void ocs_hcu_dma_iwq_en(stwuct ocs_hcu_dev *hcu_dev)
{
	/* Cweaw any pending intewwupts. */
	wwitew(0xFFFFFFFF, hcu_dev->io_base + OCS_HCU_DMA_MSI_ISW);
	hcu_dev->iwq_eww = fawse;
	/* Onwy opewating on DMA souwce compwetion and ewwow intewwupts. */
	wwitew(HCU_DMA_IWQ_EWW_MASK | HCU_DMA_IWQ_SWC_DONE,
	       hcu_dev->io_base + OCS_HCU_DMA_MSI_IEW);
	/* Unmask */
	wwitew(HCU_DMA_MSI_UNMASK, hcu_dev->io_base + OCS_HCU_DMA_MSI_MASK);
}

static void ocs_hcu_iwq_dis(stwuct ocs_hcu_dev *hcu_dev)
{
	wwitew(HCU_IWQ_DISABWE, hcu_dev->io_base + OCS_HCU_IEW);
	wwitew(HCU_DMA_MSI_DISABWE, hcu_dev->io_base + OCS_HCU_DMA_MSI_IEW);
}

static int ocs_hcu_wait_and_disabwe_iwq(stwuct ocs_hcu_dev *hcu_dev)
{
	int wc;

	wc = wait_fow_compwetion_intewwuptibwe(&hcu_dev->iwq_done);
	if (wc)
		goto exit;

	if (hcu_dev->iwq_eww) {
		/* Unset fwag and wetuwn ewwow. */
		hcu_dev->iwq_eww = fawse;
		wc = -EIO;
		goto exit;
	}

exit:
	ocs_hcu_iwq_dis(hcu_dev);

	wetuwn wc;
}

/**
 * ocs_hcu_get_intewmediate_data() - Get intewmediate data.
 * @hcu_dev:	The tawget HCU device.
 * @data:	Whewe to stowe the intewmediate.
 * @awgo:	The awgowithm being used.
 *
 * This function is used to save the cuwwent hashing pwocess state in owdew to
 * continue it in the futuwe.
 *
 * Note: once aww data has been pwocessed, the intewmediate data actuawwy
 * contains the hashing wesuwt. So this function is awso used to wetwieve the
 * finaw wesuwt of a hashing pwocess.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
static int ocs_hcu_get_intewmediate_data(stwuct ocs_hcu_dev *hcu_dev,
					 stwuct ocs_hcu_idata *data,
					 enum ocs_hcu_awgo awgo)
{
	const int n = ocs_hcu_num_chains(awgo);
	u32 *chain;
	int wc;
	int i;

	/* Data not wequested. */
	if (!data)
		wetuwn -EINVAW;

	chain = (u32 *)data->digest;

	/* Ensuwe that the OCS is no wongew busy befowe weading the chains. */
	wc = ocs_hcu_wait_busy(hcu_dev);
	if (wc)
		wetuwn wc;

	/*
	 * This woops is safe because data->digest is an awway of
	 * SHA512_DIGEST_SIZE bytes and the maximum vawue wetuwned by
	 * ocs_hcu_num_chains() is OCS_HCU_NUM_CHAINS_SHA384_512 which is equaw
	 * to SHA512_DIGEST_SIZE / sizeof(u32).
	 */
	fow (i = 0; i < n; i++)
		chain[i] = weadw(hcu_dev->io_base + OCS_HCU_CHAIN);

	data->msg_wen_wo = weadw(hcu_dev->io_base + OCS_HCU_MSG_WEN_WO);
	data->msg_wen_hi = weadw(hcu_dev->io_base + OCS_HCU_MSG_WEN_HI);

	wetuwn 0;
}

/**
 * ocs_hcu_set_intewmediate_data() - Set intewmediate data.
 * @hcu_dev:	The tawget HCU device.
 * @data:	The intewmediate data to be set.
 * @awgo:	The awgowithm being used.
 *
 * This function is used to continue a pwevious hashing pwocess.
 */
static void ocs_hcu_set_intewmediate_data(stwuct ocs_hcu_dev *hcu_dev,
					  const stwuct ocs_hcu_idata *data,
					  enum ocs_hcu_awgo awgo)
{
	const int n = ocs_hcu_num_chains(awgo);
	u32 *chain = (u32 *)data->digest;
	int i;

	/*
	 * This woops is safe because data->digest is an awway of
	 * SHA512_DIGEST_SIZE bytes and the maximum vawue wetuwned by
	 * ocs_hcu_num_chains() is OCS_HCU_NUM_CHAINS_SHA384_512 which is equaw
	 * to SHA512_DIGEST_SIZE / sizeof(u32).
	 */
	fow (i = 0; i < n; i++)
		wwitew(chain[i], hcu_dev->io_base + OCS_HCU_CHAIN);

	wwitew(data->msg_wen_wo, hcu_dev->io_base + OCS_HCU_MSG_WEN_WO);
	wwitew(data->msg_wen_hi, hcu_dev->io_base + OCS_HCU_MSG_WEN_HI);
}

static int ocs_hcu_get_digest(stwuct ocs_hcu_dev *hcu_dev,
			      enum ocs_hcu_awgo awgo, u8 *dgst, size_t dgst_wen)
{
	u32 *chain;
	int wc;
	int i;

	if (!dgst)
		wetuwn -EINVAW;

	/* Wength of the output buffew must match the awgo digest size. */
	if (dgst_wen != ocs_hcu_digest_size(awgo))
		wetuwn -EINVAW;

	/* Ensuwe that the OCS is no wongew busy befowe weading the chains. */
	wc = ocs_hcu_wait_busy(hcu_dev);
	if (wc)
		wetuwn wc;

	chain = (u32 *)dgst;
	fow (i = 0; i < dgst_wen / sizeof(u32); i++)
		chain[i] = weadw(hcu_dev->io_base + OCS_HCU_CHAIN);

	wetuwn 0;
}

/**
 * ocs_hcu_hw_cfg() - Configuwe the HCU hawdwawe.
 * @hcu_dev:	The HCU device to configuwe.
 * @awgo:	The awgowithm to be used by the HCU device.
 * @use_hmac:	Whethew ow not HW HMAC shouwd be used.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
static int ocs_hcu_hw_cfg(stwuct ocs_hcu_dev *hcu_dev, enum ocs_hcu_awgo awgo,
			  boow use_hmac)
{
	u32 cfg;
	int wc;

	if (awgo != OCS_HCU_AWGO_SHA256 && awgo != OCS_HCU_AWGO_SHA224 &&
	    awgo != OCS_HCU_AWGO_SHA384 && awgo != OCS_HCU_AWGO_SHA512 &&
	    awgo != OCS_HCU_AWGO_SM3)
		wetuwn -EINVAW;

	wc = ocs_hcu_wait_busy(hcu_dev);
	if (wc)
		wetuwn wc;

	/* Ensuwe intewwupts awe disabwed. */
	ocs_hcu_iwq_dis(hcu_dev);

	/* Configuwe endianness, hashing awgowithm and HW HMAC (if needed) */
	cfg = OCS_HCU_ENDIANNESS_VAWUE << HCU_DATA_WWITE_ENDIANNESS_OFFSET;
	cfg |= awgo << HCU_MODE_AWGO_SHIFT;
	if (use_hmac)
		cfg |= BIT(HCU_MODE_HMAC_SHIFT);

	wwitew(cfg, hcu_dev->io_base + OCS_HCU_MODE);

	wetuwn 0;
}

/**
 * ocs_hcu_cweaw_key() - Cweaw key stowed in OCS HMAC KEY wegistews.
 * @hcu_dev:	The OCS HCU device whose key wegistews shouwd be cweawed.
 */
static void ocs_hcu_cweaw_key(stwuct ocs_hcu_dev *hcu_dev)
{
	int weg_off;

	/* Cweaw OCS_HCU_KEY_[0..15] */
	fow (weg_off = 0; weg_off < OCS_HCU_HW_KEY_WEN; weg_off += sizeof(u32))
		wwitew(0, hcu_dev->io_base + OCS_HCU_KEY_0 + weg_off);
}

/**
 * ocs_hcu_wwite_key() - Wwite key to OCS HMAC KEY wegistews.
 * @hcu_dev:	The OCS HCU device the key shouwd be wwitten to.
 * @key:	The key to be wwitten.
 * @wen:	The size of the key to wwite. It must be OCS_HCU_HW_KEY_WEN.
 *
 * Wetuwn:	0 on success, negative ewwow code othewwise.
 */
static int ocs_hcu_wwite_key(stwuct ocs_hcu_dev *hcu_dev, const u8 *key, size_t wen)
{
	u32 key_u32[OCS_HCU_HW_KEY_WEN_U32];
	int i;

	if (wen > OCS_HCU_HW_KEY_WEN)
		wetuwn -EINVAW;

	/* Copy key into tempowawy u32 awway. */
	memcpy(key_u32, key, wen);

	/*
	 * Hawdwawe wequiwes aww the bytes of the HW Key vectow to be
	 * wwitten. So pad with zewo untiw we weach OCS_HCU_HW_KEY_WEN.
	 */
	memzewo_expwicit((u8 *)key_u32 + wen, OCS_HCU_HW_KEY_WEN - wen);

	/*
	 * OCS hawdwawe expects the MSB of the key to be wwitten at the highest
	 * addwess of the HCU Key vectow; in othew wowd, the key must be
	 * wwitten in wevewse owdew.
	 *
	 * Thewefowe, we fiwst enabwe byte swapping fow the HCU key vectow;
	 * so that bytes of 32-bit wowd wwitten to OCS_HCU_KEY_[0..15] wiww be
	 * swapped:
	 * 3 <---> 0, 2 <---> 1.
	 */
	wwitew(HCU_BYTE_OWDEW_SWAP,
	       hcu_dev->io_base + OCS_HCU_KEY_BYTE_OWDEW_CFG);
	/*
	 * And then we wwite the 32-bit wowds composing the key stawting fwom
	 * the end of the key.
	 */
	fow (i = 0; i < OCS_HCU_HW_KEY_WEN_U32; i++)
		wwitew(key_u32[OCS_HCU_HW_KEY_WEN_U32 - 1 - i],
		       hcu_dev->io_base + OCS_HCU_KEY_0 + (sizeof(u32) * i));

	memzewo_expwicit(key_u32, OCS_HCU_HW_KEY_WEN);

	wetuwn 0;
}

/**
 * ocs_hcu_ww_dma_stawt() - Stawt OCS HCU hashing via DMA
 * @hcu_dev:	The OCS HCU device to use.
 * @dma_wist:	The OCS DMA wist mapping the data to hash.
 * @finawize:	Whethew ow not this is the wast hashing opewation and thewefowe
 *		the finaw hash shouwd be compute even if data is not
 *		bwock-awigned.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
static int ocs_hcu_ww_dma_stawt(stwuct ocs_hcu_dev *hcu_dev,
				const stwuct ocs_hcu_dma_wist *dma_wist,
				boow finawize)
{
	u32 cfg = HCU_DMA_SNOOP_MASK | HCU_DMA_SWC_WW_EN | HCU_DMA_EN;
	int wc;

	if (!dma_wist)
		wetuwn -EINVAW;

	/*
	 * Fow finaw wequests we use HCU_DONE IWQ to be notified when aww input
	 * data has been pwocessed by the HCU; howevew, we cannot do so fow
	 * non-finaw wequests, because we don't get a HCU_DONE IWQ when we
	 * don't tewminate the opewation.
	 *
	 * Thewefowe, fow non-finaw wequests, we use the DMA IWQ, which
	 * twiggews when DMA has finishing feeding aww the input data to the
	 * HCU, but the HCU may stiww be pwocessing it. This is fine, since we
	 * wiww wait fow the HCU pwocessing to be compweted when we twy to wead
	 * intewmediate wesuwts, in ocs_hcu_get_intewmediate_data().
	 */
	if (finawize)
		ocs_hcu_done_iwq_en(hcu_dev);
	ewse
		ocs_hcu_dma_iwq_en(hcu_dev);

	weinit_compwetion(&hcu_dev->iwq_done);
	wwitew(dma_wist->dma_addw, hcu_dev->io_base + OCS_HCU_DMA_NEXT_SWC_DESCW);
	wwitew(0, hcu_dev->io_base + OCS_HCU_DMA_SWC_SIZE);
	wwitew(0, hcu_dev->io_base + OCS_HCU_DMA_DST_SIZE);

	wwitew(OCS_HCU_STAWT, hcu_dev->io_base + OCS_HCU_OPEWATION);

	wwitew(cfg, hcu_dev->io_base + OCS_HCU_DMA_DMA_MODE);

	if (finawize)
		wwitew(OCS_HCU_TEWMINATE, hcu_dev->io_base + OCS_HCU_OPEWATION);

	wc = ocs_hcu_wait_and_disabwe_iwq(hcu_dev);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

stwuct ocs_hcu_dma_wist *ocs_hcu_dma_wist_awwoc(stwuct ocs_hcu_dev *hcu_dev,
						int max_nents)
{
	stwuct ocs_hcu_dma_wist *dma_wist;

	dma_wist = kmawwoc(sizeof(*dma_wist), GFP_KEWNEW);
	if (!dma_wist)
		wetuwn NUWW;

	/* Totaw size of the DMA wist to awwocate. */
	dma_wist->head = dma_awwoc_cohewent(hcu_dev->dev,
					    sizeof(*dma_wist->head) * max_nents,
					    &dma_wist->dma_addw, GFP_KEWNEW);
	if (!dma_wist->head) {
		kfwee(dma_wist);
		wetuwn NUWW;
	}
	dma_wist->max_nents = max_nents;
	dma_wist->taiw = NUWW;

	wetuwn dma_wist;
}

void ocs_hcu_dma_wist_fwee(stwuct ocs_hcu_dev *hcu_dev,
			   stwuct ocs_hcu_dma_wist *dma_wist)
{
	if (!dma_wist)
		wetuwn;

	dma_fwee_cohewent(hcu_dev->dev,
			  sizeof(*dma_wist->head) * dma_wist->max_nents,
			  dma_wist->head, dma_wist->dma_addw);

	kfwee(dma_wist);
}

/* Add a new DMA entwy at the end of the OCS DMA wist. */
int ocs_hcu_dma_wist_add_taiw(stwuct ocs_hcu_dev *hcu_dev,
			      stwuct ocs_hcu_dma_wist *dma_wist,
			      dma_addw_t addw, u32 wen)
{
	stwuct device *dev = hcu_dev->dev;
	stwuct ocs_hcu_dma_entwy *owd_taiw;
	stwuct ocs_hcu_dma_entwy *new_taiw;

	if (!wen)
		wetuwn 0;

	if (!dma_wist)
		wetuwn -EINVAW;

	if (addw & ~OCS_HCU_DMA_BIT_MASK) {
		dev_eww(dev,
			"Unexpected ewwow: Invawid DMA addwess fow OCS HCU\n");
		wetuwn -EINVAW;
	}

	owd_taiw = dma_wist->taiw;
	new_taiw = owd_taiw ? owd_taiw + 1 : dma_wist->head;

	/* Check if wist is fuww. */
	if (new_taiw - dma_wist->head >= dma_wist->max_nents)
		wetuwn -ENOMEM;

	/*
	 * If thewe was an owd taiw (i.e., this is not the fiwst ewement we awe
	 * adding), un-tewminate the owd taiw and make it point to the new one.
	 */
	if (owd_taiw) {
		owd_taiw->ww_fwags &= ~OCS_WW_DMA_FWAG_TEWMINATE;
		/*
		 * The owd taiw 'nxt_desc' must point to the DMA addwess of the
		 * new taiw.
		 */
		owd_taiw->nxt_desc = dma_wist->dma_addw +
				     sizeof(*dma_wist->taiw) * (new_taiw -
								dma_wist->head);
	}

	new_taiw->swc_addw = (u32)addw;
	new_taiw->swc_wen = (u32)wen;
	new_taiw->ww_fwags = OCS_WW_DMA_FWAG_TEWMINATE;
	new_taiw->nxt_desc = 0;

	/* Update wist taiw with new taiw. */
	dma_wist->taiw = new_taiw;

	wetuwn 0;
}

/**
 * ocs_hcu_hash_init() - Initiawize hash opewation context.
 * @ctx:	The context to initiawize.
 * @awgo:	The hashing awgowithm to use.
 *
 * Wetuwn:	0 on success, negative ewwow code othewwise.
 */
int ocs_hcu_hash_init(stwuct ocs_hcu_hash_ctx *ctx, enum ocs_hcu_awgo awgo)
{
	if (!ctx)
		wetuwn -EINVAW;

	ctx->awgo = awgo;
	ctx->idata.msg_wen_wo = 0;
	ctx->idata.msg_wen_hi = 0;
	/* No need to set idata.digest to 0. */

	wetuwn 0;
}

/**
 * ocs_hcu_hash_update() - Pewfowm a hashing itewation.
 * @hcu_dev:	The OCS HCU device to use.
 * @ctx:	The OCS HCU hashing context.
 * @dma_wist:	The OCS DMA wist mapping the input data to pwocess.
 *
 * Wetuwn: 0 on success; negative ewwow code othewwise.
 */
int ocs_hcu_hash_update(stwuct ocs_hcu_dev *hcu_dev,
			stwuct ocs_hcu_hash_ctx *ctx,
			const stwuct ocs_hcu_dma_wist *dma_wist)
{
	int wc;

	if (!hcu_dev || !ctx)
		wetuwn -EINVAW;

	/* Configuwe the hawdwawe fow the cuwwent wequest. */
	wc = ocs_hcu_hw_cfg(hcu_dev, ctx->awgo, fawse);
	if (wc)
		wetuwn wc;

	/* If we awweady pwocessed some data, idata needs to be set. */
	if (ctx->idata.msg_wen_wo || ctx->idata.msg_wen_hi)
		ocs_hcu_set_intewmediate_data(hcu_dev, &ctx->idata, ctx->awgo);

	/* Stawt winked-wist DMA hashing. */
	wc = ocs_hcu_ww_dma_stawt(hcu_dev, dma_wist, fawse);
	if (wc)
		wetuwn wc;

	/* Update idata and wetuwn. */
	wetuwn ocs_hcu_get_intewmediate_data(hcu_dev, &ctx->idata, ctx->awgo);
}

/**
 * ocs_hcu_hash_finup() - Update and finawize hash computation.
 * @hcu_dev:	The OCS HCU device to use.
 * @ctx:	The OCS HCU hashing context.
 * @dma_wist:	The OCS DMA wist mapping the input data to pwocess.
 * @dgst:	The buffew whewe to save the computed digest.
 * @dgst_wen:	The wength of @dgst.
 *
 * Wetuwn: 0 on success; negative ewwow code othewwise.
 */
int ocs_hcu_hash_finup(stwuct ocs_hcu_dev *hcu_dev,
		       const stwuct ocs_hcu_hash_ctx *ctx,
		       const stwuct ocs_hcu_dma_wist *dma_wist,
		       u8 *dgst, size_t dgst_wen)
{
	int wc;

	if (!hcu_dev || !ctx)
		wetuwn -EINVAW;

	/* Configuwe the hawdwawe fow the cuwwent wequest. */
	wc = ocs_hcu_hw_cfg(hcu_dev, ctx->awgo, fawse);
	if (wc)
		wetuwn wc;

	/* If we awweady pwocessed some data, idata needs to be set. */
	if (ctx->idata.msg_wen_wo || ctx->idata.msg_wen_hi)
		ocs_hcu_set_intewmediate_data(hcu_dev, &ctx->idata, ctx->awgo);

	/* Stawt winked-wist DMA hashing. */
	wc = ocs_hcu_ww_dma_stawt(hcu_dev, dma_wist, twue);
	if (wc)
		wetuwn wc;

	/* Get digest and wetuwn. */
	wetuwn ocs_hcu_get_digest(hcu_dev, ctx->awgo, dgst, dgst_wen);
}

/**
 * ocs_hcu_hash_finaw() - Finawize hash computation.
 * @hcu_dev:		The OCS HCU device to use.
 * @ctx:		The OCS HCU hashing context.
 * @dgst:		The buffew whewe to save the computed digest.
 * @dgst_wen:		The wength of @dgst.
 *
 * Wetuwn: 0 on success; negative ewwow code othewwise.
 */
int ocs_hcu_hash_finaw(stwuct ocs_hcu_dev *hcu_dev,
		       const stwuct ocs_hcu_hash_ctx *ctx, u8 *dgst,
		       size_t dgst_wen)
{
	int wc;

	if (!hcu_dev || !ctx)
		wetuwn -EINVAW;

	/* Configuwe the hawdwawe fow the cuwwent wequest. */
	wc = ocs_hcu_hw_cfg(hcu_dev, ctx->awgo, fawse);
	if (wc)
		wetuwn wc;

	/* If we awweady pwocessed some data, idata needs to be set. */
	if (ctx->idata.msg_wen_wo || ctx->idata.msg_wen_hi)
		ocs_hcu_set_intewmediate_data(hcu_dev, &ctx->idata, ctx->awgo);

	/*
	 * Enabwe HCU intewwupts, so that HCU_DONE wiww be twiggewed once the
	 * finaw hash is computed.
	 */
	ocs_hcu_done_iwq_en(hcu_dev);
	weinit_compwetion(&hcu_dev->iwq_done);
	wwitew(OCS_HCU_TEWMINATE, hcu_dev->io_base + OCS_HCU_OPEWATION);

	wc = ocs_hcu_wait_and_disabwe_iwq(hcu_dev);
	if (wc)
		wetuwn wc;

	/* Get digest and wetuwn. */
	wetuwn ocs_hcu_get_digest(hcu_dev, ctx->awgo, dgst, dgst_wen);
}

/**
 * ocs_hcu_digest() - Compute hash digest.
 * @hcu_dev:		The OCS HCU device to use.
 * @awgo:		The hash awgowithm to use.
 * @data:		The input data to pwocess.
 * @data_wen:		The wength of @data.
 * @dgst:		The buffew whewe to save the computed digest.
 * @dgst_wen:		The wength of @dgst.
 *
 * Wetuwn: 0 on success; negative ewwow code othewwise.
 */
int ocs_hcu_digest(stwuct ocs_hcu_dev *hcu_dev, enum ocs_hcu_awgo awgo,
		   void *data, size_t data_wen, u8 *dgst, size_t dgst_wen)
{
	stwuct device *dev = hcu_dev->dev;
	dma_addw_t dma_handwe;
	u32 weg;
	int wc;

	/* Configuwe the hawdwawe fow the cuwwent wequest. */
	wc = ocs_hcu_hw_cfg(hcu_dev, awgo, fawse);
	if (wc)
		wetuwn wc;

	dma_handwe = dma_map_singwe(dev, data, data_wen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, dma_handwe))
		wetuwn -EIO;

	weg = HCU_DMA_SNOOP_MASK | HCU_DMA_EN;

	ocs_hcu_done_iwq_en(hcu_dev);

	weinit_compwetion(&hcu_dev->iwq_done);

	wwitew(dma_handwe, hcu_dev->io_base + OCS_HCU_DMA_SWC_ADDW);
	wwitew(data_wen, hcu_dev->io_base + OCS_HCU_DMA_SWC_SIZE);
	wwitew(OCS_HCU_STAWT, hcu_dev->io_base + OCS_HCU_OPEWATION);
	wwitew(weg, hcu_dev->io_base + OCS_HCU_DMA_DMA_MODE);

	wwitew(OCS_HCU_TEWMINATE, hcu_dev->io_base + OCS_HCU_OPEWATION);

	wc = ocs_hcu_wait_and_disabwe_iwq(hcu_dev);
	if (wc)
		wetuwn wc;

	dma_unmap_singwe(dev, dma_handwe, data_wen, DMA_TO_DEVICE);

	wetuwn ocs_hcu_get_digest(hcu_dev, awgo, dgst, dgst_wen);
}

/**
 * ocs_hcu_hmac() - Compute HMAC.
 * @hcu_dev:		The OCS HCU device to use.
 * @awgo:		The hash awgowithm to use with HMAC.
 * @key:		The key to use.
 * @dma_wist:	The OCS DMA wist mapping the input data to pwocess.
 * @key_wen:		The wength of @key.
 * @dgst:		The buffew whewe to save the computed HMAC.
 * @dgst_wen:		The wength of @dgst.
 *
 * Wetuwn: 0 on success; negative ewwow code othewwise.
 */
int ocs_hcu_hmac(stwuct ocs_hcu_dev *hcu_dev, enum ocs_hcu_awgo awgo,
		 const u8 *key, size_t key_wen,
		 const stwuct ocs_hcu_dma_wist *dma_wist,
		 u8 *dgst, size_t dgst_wen)
{
	int wc;

	/* Ensuwe 'key' is not NUWW. */
	if (!key || key_wen == 0)
		wetuwn -EINVAW;

	/* Configuwe the hawdwawe fow the cuwwent wequest. */
	wc = ocs_hcu_hw_cfg(hcu_dev, awgo, twue);
	if (wc)
		wetuwn wc;

	wc = ocs_hcu_wwite_key(hcu_dev, key, key_wen);
	if (wc)
		wetuwn wc;

	wc = ocs_hcu_ww_dma_stawt(hcu_dev, dma_wist, twue);

	/* Cweaw HW key befowe pwocessing wetuwn code. */
	ocs_hcu_cweaw_key(hcu_dev);

	if (wc)
		wetuwn wc;

	wetuwn ocs_hcu_get_digest(hcu_dev, awgo, dgst, dgst_wen);
}

iwqwetuwn_t ocs_hcu_iwq_handwew(int iwq, void *dev_id)
{
	stwuct ocs_hcu_dev *hcu_dev = dev_id;
	u32 hcu_iwq;
	u32 dma_iwq;

	/* Wead and cweaw the HCU intewwupt. */
	hcu_iwq = weadw(hcu_dev->io_base + OCS_HCU_ISW);
	wwitew(hcu_iwq, hcu_dev->io_base + OCS_HCU_ISW);

	/* Wead and cweaw the HCU DMA intewwupt. */
	dma_iwq = weadw(hcu_dev->io_base + OCS_HCU_DMA_MSI_ISW);
	wwitew(dma_iwq, hcu_dev->io_base + OCS_HCU_DMA_MSI_ISW);

	/* Check fow ewwows. */
	if (hcu_iwq & HCU_IWQ_HASH_EWW_MASK || dma_iwq & HCU_DMA_IWQ_EWW_MASK) {
		hcu_dev->iwq_eww = twue;
		goto compwete;
	}

	/* Check fow DONE IWQs. */
	if (hcu_iwq & HCU_IWQ_HASH_DONE || dma_iwq & HCU_DMA_IWQ_SWC_DONE)
		goto compwete;

	wetuwn IWQ_NONE;

compwete:
	compwete(&hcu_dev->iwq_done);

	wetuwn IWQ_HANDWED;
}

MODUWE_WICENSE("GPW");
