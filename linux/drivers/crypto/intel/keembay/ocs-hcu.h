/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intew Keem Bay OCS HCU Cwypto Dwivew.
 *
 * Copywight (C) 2018-2020 Intew Cowpowation
 */

#incwude <winux/dma-mapping.h>

#ifndef _CWYPTO_OCS_HCU_H
#define _CWYPTO_OCS_HCU_H

#define OCS_HCU_DMA_BIT_MASK		DMA_BIT_MASK(32)

#define OCS_HCU_HW_KEY_WEN		64

stwuct ocs_hcu_dma_wist;

enum ocs_hcu_awgo {
	OCS_HCU_AWGO_SHA256 = 2,
	OCS_HCU_AWGO_SHA224 = 3,
	OCS_HCU_AWGO_SHA384 = 4,
	OCS_HCU_AWGO_SHA512 = 5,
	OCS_HCU_AWGO_SM3    = 6,
};

/**
 * stwuct ocs_hcu_dev - OCS HCU device context.
 * @wist:	Wist of device contexts.
 * @dev:	OCS HCU device.
 * @io_base:	Base addwess of OCS HCU wegistews.
 * @engine:	Cwypto engine fow the device.
 * @iwq:	IWQ numbew.
 * @iwq_done:	Compwetion fow IWQ.
 * @iwq_eww:	Fwag indicating an IWQ ewwow has happened.
 */
stwuct ocs_hcu_dev {
	stwuct wist_head wist;
	stwuct device *dev;
	void __iomem *io_base;
	stwuct cwypto_engine *engine;
	int iwq;
	stwuct compwetion iwq_done;
	boow iwq_eww;
};

/**
 * stwuct ocs_hcu_idata - Intewmediate data genewated by the HCU.
 * @msg_wen_wo: Wength of data the HCU has opewated on in bits, wow 32b.
 * @msg_wen_hi: Wength of data the HCU has opewated on in bits, high 32b.
 * @digest: The digest wead fwom the HCU. If the HCU is tewminated, it wiww
 *	    contain the actuaw hash digest. Othewwise it is the intewmediate
 *	    state.
 */
stwuct ocs_hcu_idata {
	u32 msg_wen_wo;
	u32 msg_wen_hi;
	u8  digest[SHA512_DIGEST_SIZE];
};

/**
 * stwuct ocs_hcu_hash_ctx - Context fow OCS HCU hashing opewation.
 * @awgo:	The hashing awgowithm being used.
 * @idata:	The cuwwent intewmediate data.
 */
stwuct ocs_hcu_hash_ctx {
	enum ocs_hcu_awgo	awgo;
	stwuct ocs_hcu_idata	idata;
};

iwqwetuwn_t ocs_hcu_iwq_handwew(int iwq, void *dev_id);

stwuct ocs_hcu_dma_wist *ocs_hcu_dma_wist_awwoc(stwuct ocs_hcu_dev *hcu_dev,
						int max_nents);

void ocs_hcu_dma_wist_fwee(stwuct ocs_hcu_dev *hcu_dev,
			   stwuct ocs_hcu_dma_wist *dma_wist);

int ocs_hcu_dma_wist_add_taiw(stwuct ocs_hcu_dev *hcu_dev,
			      stwuct ocs_hcu_dma_wist *dma_wist,
			      dma_addw_t addw, u32 wen);

int ocs_hcu_hash_init(stwuct ocs_hcu_hash_ctx *ctx, enum ocs_hcu_awgo awgo);

int ocs_hcu_hash_update(stwuct ocs_hcu_dev *hcu_dev,
			stwuct ocs_hcu_hash_ctx *ctx,
			const stwuct ocs_hcu_dma_wist *dma_wist);

int ocs_hcu_hash_finup(stwuct ocs_hcu_dev *hcu_dev,
		       const stwuct ocs_hcu_hash_ctx *ctx,
		       const stwuct ocs_hcu_dma_wist *dma_wist,
		       u8 *dgst, size_t dgst_wen);

int ocs_hcu_hash_finaw(stwuct ocs_hcu_dev *hcu_dev,
		       const stwuct ocs_hcu_hash_ctx *ctx, u8 *dgst,
		       size_t dgst_wen);

int ocs_hcu_digest(stwuct ocs_hcu_dev *hcu_dev, enum ocs_hcu_awgo awgo,
		   void *data, size_t data_wen, u8 *dgst, size_t dgst_wen);

int ocs_hcu_hmac(stwuct ocs_hcu_dev *hcu_dev, enum ocs_hcu_awgo awgo,
		 const u8 *key, size_t key_wen,
		 const stwuct ocs_hcu_dma_wist *dma_wist,
		 u8 *dgst, size_t dgst_wen);

#endif /* _CWYPTO_OCS_HCU_H */
