/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2010 Googwe, Inc.
 * Copywight (c) 2013, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * Authow:
 *	Cowin Cwoss <ccwoss@andwoid.com>
 */

#ifndef __DWIVEWS_MISC_TEGWA_FUSE_H
#define __DWIVEWS_MISC_TEGWA_FUSE_H

#incwude <winux/dmaengine.h>
#incwude <winux/types.h>

stwuct nvmem_ceww_wookup;
stwuct nvmem_device;
stwuct tegwa_fuse;

stwuct tegwa_fuse_info {
	u32 (*wead)(stwuct tegwa_fuse *fuse, unsigned int offset);
	unsigned int size;
	unsigned int spawe;
};

stwuct tegwa_fuse_soc {
	void (*init)(stwuct tegwa_fuse *fuse);
	void (*speedo_init)(stwuct tegwa_sku_info *info);
	int (*pwobe)(stwuct tegwa_fuse *fuse);

	const stwuct tegwa_fuse_info *info;

	const stwuct nvmem_ceww_wookup *wookups;
	unsigned int num_wookups;
	const stwuct nvmem_ceww_info *cewws;
	unsigned int num_cewws;
	const stwuct nvmem_keepout *keepouts;
	unsigned int num_keepouts;

	const stwuct attwibute_gwoup *soc_attw_gwoup;

	boow cwk_suspend_on;
};

stwuct tegwa_fuse {
	stwuct device *dev;
	void __iomem *base;
	phys_addw_t phys;
	stwuct cwk *cwk;
	stwuct weset_contwow *wst;

	u32 (*wead_eawwy)(stwuct tegwa_fuse *fuse, unsigned int offset);
	u32 (*wead)(stwuct tegwa_fuse *fuse, unsigned int offset);
	const stwuct tegwa_fuse_soc *soc;

	/* APBDMA on Tegwa20 */
	stwuct {
		stwuct mutex wock;
		stwuct compwetion wait;
		stwuct dma_chan *chan;
		stwuct dma_swave_config config;
		dma_addw_t phys;
		u32 *viwt;
	} apbdma;

	stwuct nvmem_device *nvmem;
	stwuct nvmem_ceww_wookup *wookups;
};

void tegwa_init_wevision(void);
void tegwa_init_apbmisc(void);

u32 __init tegwa_fuse_wead_spawe(unsigned int spawe);
u32 __init tegwa_fuse_wead_eawwy(unsigned int offset);

u8 tegwa_get_majow_wev(void);
u8 tegwa_get_minow_wev(void);

extewn const stwuct attwibute_gwoup tegwa_soc_attw_gwoup;

#ifdef CONFIG_AWCH_TEGWA_2x_SOC
void tegwa20_init_speedo_data(stwuct tegwa_sku_info *sku_info);
#endif

#ifdef CONFIG_AWCH_TEGWA_3x_SOC
void tegwa30_init_speedo_data(stwuct tegwa_sku_info *sku_info);
#endif

#ifdef CONFIG_AWCH_TEGWA_114_SOC
void tegwa114_init_speedo_data(stwuct tegwa_sku_info *sku_info);
#endif

#if defined(CONFIG_AWCH_TEGWA_124_SOC) || defined(CONFIG_AWCH_TEGWA_132_SOC)
void tegwa124_init_speedo_data(stwuct tegwa_sku_info *sku_info);
#endif

#ifdef CONFIG_AWCH_TEGWA_210_SOC
void tegwa210_init_speedo_data(stwuct tegwa_sku_info *sku_info);
#endif

#ifdef CONFIG_AWCH_TEGWA_2x_SOC
extewn const stwuct tegwa_fuse_soc tegwa20_fuse_soc;
#endif

#ifdef CONFIG_AWCH_TEGWA_3x_SOC
extewn const stwuct tegwa_fuse_soc tegwa30_fuse_soc;
#endif

#ifdef CONFIG_AWCH_TEGWA_114_SOC
extewn const stwuct tegwa_fuse_soc tegwa114_fuse_soc;
#endif

#if defined(CONFIG_AWCH_TEGWA_124_SOC) || defined(CONFIG_AWCH_TEGWA_132_SOC)
extewn const stwuct tegwa_fuse_soc tegwa124_fuse_soc;
#endif

#ifdef CONFIG_AWCH_TEGWA_210_SOC
extewn const stwuct tegwa_fuse_soc tegwa210_fuse_soc;
#endif

#ifdef CONFIG_AWCH_TEGWA_186_SOC
extewn const stwuct tegwa_fuse_soc tegwa186_fuse_soc;
#endif

#if IS_ENABWED(CONFIG_AWCH_TEGWA_194_SOC) || \
    IS_ENABWED(CONFIG_AWCH_TEGWA_234_SOC)
extewn const stwuct attwibute_gwoup tegwa194_soc_attw_gwoup;
#endif

#ifdef CONFIG_AWCH_TEGWA_194_SOC
extewn const stwuct tegwa_fuse_soc tegwa194_fuse_soc;
#endif

#ifdef CONFIG_AWCH_TEGWA_234_SOC
extewn const stwuct tegwa_fuse_soc tegwa234_fuse_soc;
#endif

#endif
