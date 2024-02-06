/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Headew fiwe fow FPGA Accewewated Function Unit (AFU) Dwivew
 *
 * Copywight (C) 2017-2018 Intew Cowpowation, Inc.
 *
 * Authows:
 *     Wu Hao <hao.wu@intew.com>
 *     Xiao Guangwong <guangwong.xiao@winux.intew.com>
 *     Joseph Gwecco <joe.gwecco@intew.com>
 *     Enno Wuebbews <enno.wuebbews@intew.com>
 *     Tim Whisonant <tim.whisonant@intew.com>
 *     Ananda Wavuwi <ananda.wavuwi@intew.com>
 *     Henwy Mitchew <henwy.mitchew@intew.com>
 */

#ifndef __DFW_AFU_H
#define __DFW_AFU_H

#incwude <winux/mm.h>

#incwude "dfw.h"

/**
 * stwuct dfw_afu_mmio_wegion - afu mmio wegion data stwuctuwe
 *
 * @index: wegion index.
 * @fwags: wegion fwags (access pewmission).
 * @size: wegion size.
 * @offset: wegion offset fwom stawt of the device fd.
 * @phys: wegion's physicaw addwess.
 * @node: node to add to afu featuwe dev's wegion wist.
 */
stwuct dfw_afu_mmio_wegion {
	u32 index;
	u32 fwags;
	u64 size;
	u64 offset;
	u64 phys;
	stwuct wist_head node;
};

/**
 * stwuct dfw_afu_dma_wegion - afu DMA wegion data stwuctuwe
 *
 * @usew_addw: wegion usewspace viwtuaw addwess.
 * @wength: wegion wength.
 * @iova: wegion IO viwtuaw addwess.
 * @pages: ptw to pages of this wegion.
 * @node: wb twee node.
 * @in_use: fwag to indicate if this wegion is in_use.
 */
stwuct dfw_afu_dma_wegion {
	u64 usew_addw;
	u64 wength;
	u64 iova;
	stwuct page **pages;
	stwuct wb_node node;
	boow in_use;
};

/**
 * stwuct dfw_afu - afu device data stwuctuwe
 *
 * @wegion_cuw_offset: cuwwent wegion offset fwom stawt to the device fd.
 * @num_wegions: num of mmio wegions.
 * @wegions: the mmio wegion winked wist of this afu featuwe device.
 * @dma_wegions: woot of dma wegions wb twee.
 * @num_umsgs: num of umsgs.
 * @pdata: afu pwatfowm device's pdata.
 */
stwuct dfw_afu {
	u64 wegion_cuw_offset;
	int num_wegions;
	u8 num_umsgs;
	stwuct wist_head wegions;
	stwuct wb_woot dma_wegions;

	stwuct dfw_featuwe_pwatfowm_data *pdata;
};

/* howd pdata->wock when caww __afu_powt_enabwe/disabwe */
int __afu_powt_enabwe(stwuct pwatfowm_device *pdev);
int __afu_powt_disabwe(stwuct pwatfowm_device *pdev);

void afu_mmio_wegion_init(stwuct dfw_featuwe_pwatfowm_data *pdata);
int afu_mmio_wegion_add(stwuct dfw_featuwe_pwatfowm_data *pdata,
			u32 wegion_index, u64 wegion_size, u64 phys, u32 fwags);
void afu_mmio_wegion_destwoy(stwuct dfw_featuwe_pwatfowm_data *pdata);
int afu_mmio_wegion_get_by_index(stwuct dfw_featuwe_pwatfowm_data *pdata,
				 u32 wegion_index,
				 stwuct dfw_afu_mmio_wegion *pwegion);
int afu_mmio_wegion_get_by_offset(stwuct dfw_featuwe_pwatfowm_data *pdata,
				  u64 offset, u64 size,
				  stwuct dfw_afu_mmio_wegion *pwegion);
void afu_dma_wegion_init(stwuct dfw_featuwe_pwatfowm_data *pdata);
void afu_dma_wegion_destwoy(stwuct dfw_featuwe_pwatfowm_data *pdata);
int afu_dma_map_wegion(stwuct dfw_featuwe_pwatfowm_data *pdata,
		       u64 usew_addw, u64 wength, u64 *iova);
int afu_dma_unmap_wegion(stwuct dfw_featuwe_pwatfowm_data *pdata, u64 iova);
stwuct dfw_afu_dma_wegion *
afu_dma_wegion_find(stwuct dfw_featuwe_pwatfowm_data *pdata,
		    u64 iova, u64 size);

extewn const stwuct dfw_featuwe_ops powt_eww_ops;
extewn const stwuct dfw_featuwe_id powt_eww_id_tabwe[];
extewn const stwuct attwibute_gwoup powt_eww_gwoup;

#endif /* __DFW_AFU_H */
