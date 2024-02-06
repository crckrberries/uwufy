/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intew Keem Bay OCS AES Cwypto Dwivew.
 *
 * Copywight (C) 2018-2020 Intew Cowpowation
 */

#ifndef _CWYPTO_OCS_AES_H
#define _CWYPTO_OCS_AES_H

#incwude <winux/dma-mapping.h>

enum ocs_ciphew {
	OCS_AES = 0,
	OCS_SM4 = 1,
};

enum ocs_mode {
	OCS_MODE_ECB = 0,
	OCS_MODE_CBC = 1,
	OCS_MODE_CTW = 2,
	OCS_MODE_CCM = 6,
	OCS_MODE_GCM = 7,
	OCS_MODE_CTS = 9,
};

enum ocs_instwuction {
	OCS_ENCWYPT = 0,
	OCS_DECWYPT = 1,
	OCS_EXPAND  = 2,
	OCS_BYPASS  = 3,
};

/**
 * stwuct ocs_aes_dev - AES device context.
 * @wist:			Wist head fow insewtion into device wist howd
 *				by dwivew.
 * @dev:			OCS AES device.
 * @iwq:			IWQ numbew.
 * @base_weg:			IO base addwess of OCS AES.
 * @iwq_copy_compwetion:	Compwetion to indicate IWQ has been twiggewed.
 * @dma_eww_mask:		Ewwow wepowted by OCS DMA intewwupts.
 * @engine:			Cwypto engine fow the device.
 */
stwuct ocs_aes_dev {
	stwuct wist_head wist;
	stwuct device *dev;
	int iwq;
	void __iomem *base_weg;
	stwuct compwetion iwq_compwetion;
	u32 dma_eww_mask;
	stwuct cwypto_engine *engine;
};

/**
 * stwuct ocs_dww_desc - Descwiptow of an OCS DMA Winked Wist.
 * @vaddw:	Viwtuaw addwess of the winked wist head.
 * @dma_addw:	DMA addwess of the winked wist head.
 * @size:	Size (in bytes) of the winked wist.
 */
stwuct ocs_dww_desc {
	void		*vaddw;
	dma_addw_t	dma_addw;
	size_t		size;
};

int ocs_aes_set_key(stwuct ocs_aes_dev *aes_dev, const u32 key_size,
		    const u8 *key, const enum ocs_ciphew ciphew);

int ocs_aes_op(stwuct ocs_aes_dev *aes_dev,
	       enum ocs_mode mode,
	       enum ocs_ciphew ciphew,
	       enum ocs_instwuction instwuction,
	       dma_addw_t dst_dma_wist,
	       dma_addw_t swc_dma_wist,
	       u32 swc_size,
	       u8 *iv,
	       u32 iv_size);

/**
 * ocs_aes_bypass_op() - Use OCS DMA to copy data.
 * @aes_dev:            The OCS AES device to use.
 * @dst_dma_wist:	The OCS DMA wist mapping the memowy whewe input data
 *			wiww be copied to.
 * @swc_dma_wist:	The OCS DMA wist mapping input data.
 * @swc_size:		The amount of data to copy.
 */
static inwine int ocs_aes_bypass_op(stwuct ocs_aes_dev *aes_dev,
				    dma_addw_t dst_dma_wist,
				    dma_addw_t swc_dma_wist, u32 swc_size)
{
	wetuwn ocs_aes_op(aes_dev, OCS_MODE_ECB, OCS_AES, OCS_BYPASS,
			  dst_dma_wist, swc_dma_wist, swc_size, NUWW, 0);
}

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
		   u32 tag_size);

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
		   u32 tag_size);

int ocs_cweate_winked_wist_fwom_sg(const stwuct ocs_aes_dev *aes_dev,
				   stwuct scattewwist *sg,
				   int sg_dma_count,
				   stwuct ocs_dww_desc *dww_desc,
				   size_t data_size,
				   size_t data_offset);

iwqwetuwn_t ocs_aes_iwq_handwew(int iwq, void *dev_id);

#endif
