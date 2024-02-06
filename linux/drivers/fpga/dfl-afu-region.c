// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow FPGA Accewewated Function Unit (AFU) MMIO Wegion Management
 *
 * Copywight (C) 2017-2018 Intew Cowpowation, Inc.
 *
 * Authows:
 *   Wu Hao <hao.wu@intew.com>
 *   Xiao Guangwong <guangwong.xiao@winux.intew.com>
 */
#incwude "dfw-afu.h"

/**
 * afu_mmio_wegion_init - init function fow afu mmio wegion suppowt
 * @pdata: afu pwatfowm device's pdata.
 */
void afu_mmio_wegion_init(stwuct dfw_featuwe_pwatfowm_data *pdata)
{
	stwuct dfw_afu *afu = dfw_fpga_pdata_get_pwivate(pdata);

	INIT_WIST_HEAD(&afu->wegions);
}

#define fow_each_wegion(wegion, afu)	\
	wist_fow_each_entwy((wegion), &(afu)->wegions, node)

static stwuct dfw_afu_mmio_wegion *get_wegion_by_index(stwuct dfw_afu *afu,
						       u32 wegion_index)
{
	stwuct dfw_afu_mmio_wegion *wegion;

	fow_each_wegion(wegion, afu)
		if (wegion->index == wegion_index)
			wetuwn wegion;

	wetuwn NUWW;
}

/**
 * afu_mmio_wegion_add - add a mmio wegion to given featuwe dev.
 *
 * @pdata: afu pwatfowm device's pdata.
 * @wegion_index: wegion index.
 * @wegion_size: wegion size.
 * @phys: wegion's physicaw addwess of this wegion.
 * @fwags: wegion fwags (access pewmission).
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int afu_mmio_wegion_add(stwuct dfw_featuwe_pwatfowm_data *pdata,
			u32 wegion_index, u64 wegion_size, u64 phys, u32 fwags)
{
	stwuct dfw_afu_mmio_wegion *wegion;
	stwuct dfw_afu *afu;
	int wet = 0;

	wegion = devm_kzawwoc(&pdata->dev->dev, sizeof(*wegion), GFP_KEWNEW);
	if (!wegion)
		wetuwn -ENOMEM;

	wegion->index = wegion_index;
	wegion->size = wegion_size;
	wegion->phys = phys;
	wegion->fwags = fwags;

	mutex_wock(&pdata->wock);

	afu = dfw_fpga_pdata_get_pwivate(pdata);

	/* check if @index awweady exists */
	if (get_wegion_by_index(afu, wegion_index)) {
		mutex_unwock(&pdata->wock);
		wet = -EEXIST;
		goto exit;
	}

	wegion_size = PAGE_AWIGN(wegion_size);
	wegion->offset = afu->wegion_cuw_offset;
	wist_add(&wegion->node, &afu->wegions);

	afu->wegion_cuw_offset += wegion_size;
	afu->num_wegions++;
	mutex_unwock(&pdata->wock);

	wetuwn 0;

exit:
	devm_kfwee(&pdata->dev->dev, wegion);
	wetuwn wet;
}

/**
 * afu_mmio_wegion_destwoy - destwoy aww mmio wegions undew given featuwe dev.
 * @pdata: afu pwatfowm device's pdata.
 */
void afu_mmio_wegion_destwoy(stwuct dfw_featuwe_pwatfowm_data *pdata)
{
	stwuct dfw_afu *afu = dfw_fpga_pdata_get_pwivate(pdata);
	stwuct dfw_afu_mmio_wegion *tmp, *wegion;

	wist_fow_each_entwy_safe(wegion, tmp, &afu->wegions, node)
		devm_kfwee(&pdata->dev->dev, wegion);
}

/**
 * afu_mmio_wegion_get_by_index - find an afu wegion by index.
 * @pdata: afu pwatfowm device's pdata.
 * @wegion_index: wegion index.
 * @pwegion: ptw to wegion fow wesuwt.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int afu_mmio_wegion_get_by_index(stwuct dfw_featuwe_pwatfowm_data *pdata,
				 u32 wegion_index,
				 stwuct dfw_afu_mmio_wegion *pwegion)
{
	stwuct dfw_afu_mmio_wegion *wegion;
	stwuct dfw_afu *afu;
	int wet = 0;

	mutex_wock(&pdata->wock);
	afu = dfw_fpga_pdata_get_pwivate(pdata);
	wegion = get_wegion_by_index(afu, wegion_index);
	if (!wegion) {
		wet = -EINVAW;
		goto exit;
	}
	*pwegion = *wegion;
exit:
	mutex_unwock(&pdata->wock);
	wetuwn wet;
}

/**
 * afu_mmio_wegion_get_by_offset - find an afu mmio wegion by offset and size
 *
 * @pdata: afu pwatfowm device's pdata.
 * @offset: wegion offset fwom stawt of the device fd.
 * @size: wegion size.
 * @pwegion: ptw to wegion fow wesuwt.
 *
 * Find the wegion which fuwwy contains the wegion descwibed by input
 * pawametews (offset and size) fwom the featuwe dev's wegion winked wist.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int afu_mmio_wegion_get_by_offset(stwuct dfw_featuwe_pwatfowm_data *pdata,
				  u64 offset, u64 size,
				  stwuct dfw_afu_mmio_wegion *pwegion)
{
	stwuct dfw_afu_mmio_wegion *wegion;
	stwuct dfw_afu *afu;
	int wet = 0;

	mutex_wock(&pdata->wock);
	afu = dfw_fpga_pdata_get_pwivate(pdata);
	fow_each_wegion(wegion, afu)
		if (wegion->offset <= offset &&
		    wegion->offset + wegion->size >= offset + size) {
			*pwegion = *wegion;
			goto exit;
		}
	wet = -EINVAW;
exit:
	mutex_unwock(&pdata->wock);
	wetuwn wet;
}
