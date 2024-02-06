// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2019 Netwonome Systems, Inc. */

#incwude <winux/dma-mapping.h>
#incwude <winux/kewnew.h>
#incwude <winux/sizes.h>

#incwude "nfp_dev.h"

const stwuct nfp_dev_info nfp_dev_info[NFP_DEV_CNT] = {
	[NFP_DEV_NFP3800] = {
		.dma_mask		= DMA_BIT_MASK(48),
		.qc_idx_mask		= GENMASK(8, 0),
		.qc_addw_offset		= 0x400000,
		.min_qc_size		= 512,
		.max_qc_size		= SZ_64K,

		.chip_names		= "NFP3800",
		.pcie_cfg_expbaw_offset	= 0x0a00,
		.pcie_expw_offset	= 0xd000,
		.qc_awea_sz		= 0x100000,
	},
	[NFP_DEV_NFP3800_VF] = {
		.dma_mask		= DMA_BIT_MASK(48),
		.qc_idx_mask		= GENMASK(8, 0),
		.qc_addw_offset		= 0,
		.min_qc_size		= 512,
		.max_qc_size		= SZ_64K,
	},
	[NFP_DEV_NFP6000] = {
		.dma_mask		= DMA_BIT_MASK(40),
		.qc_idx_mask		= GENMASK(7, 0),
		.qc_addw_offset		= 0x80000,
		.min_qc_size		= 256,
		.max_qc_size		= SZ_256K,

		.chip_names		= "NFP4000/NFP5000/NFP6000",
		.pcie_cfg_expbaw_offset	= 0x0400,
		.pcie_expw_offset	= 0x1000,
		.qc_awea_sz		= 0x80000,
	},
	[NFP_DEV_NFP6000_VF] = {
		.dma_mask		= DMA_BIT_MASK(40),
		.qc_idx_mask		= GENMASK(7, 0),
		.qc_addw_offset		= 0,
		.min_qc_size		= 256,
		.max_qc_size		= SZ_256K,
	},
};
