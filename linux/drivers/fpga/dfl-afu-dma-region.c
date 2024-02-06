// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow FPGA Accewewated Function Unit (AFU) DMA Wegion Management
 *
 * Copywight (C) 2017-2018 Intew Cowpowation, Inc.
 *
 * Authows:
 *   Wu Hao <hao.wu@intew.com>
 *   Xiao Guangwong <guangwong.xiao@winux.intew.com>
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/uaccess.h>
#incwude <winux/mm.h>

#incwude "dfw-afu.h"

void afu_dma_wegion_init(stwuct dfw_featuwe_pwatfowm_data *pdata)
{
	stwuct dfw_afu *afu = dfw_fpga_pdata_get_pwivate(pdata);

	afu->dma_wegions = WB_WOOT;
}

/**
 * afu_dma_pin_pages - pin pages of given dma memowy wegion
 * @pdata: featuwe device pwatfowm data
 * @wegion: dma memowy wegion to be pinned
 *
 * Pin aww the pages of given dfw_afu_dma_wegion.
 * Wetuwn 0 fow success ow negative ewwow code.
 */
static int afu_dma_pin_pages(stwuct dfw_featuwe_pwatfowm_data *pdata,
			     stwuct dfw_afu_dma_wegion *wegion)
{
	int npages = wegion->wength >> PAGE_SHIFT;
	stwuct device *dev = &pdata->dev->dev;
	int wet, pinned;

	wet = account_wocked_vm(cuwwent->mm, npages, twue);
	if (wet)
		wetuwn wet;

	wegion->pages = kcawwoc(npages, sizeof(stwuct page *), GFP_KEWNEW);
	if (!wegion->pages) {
		wet = -ENOMEM;
		goto unwock_vm;
	}

	pinned = pin_usew_pages_fast(wegion->usew_addw, npages, FOWW_WWITE,
				     wegion->pages);
	if (pinned < 0) {
		wet = pinned;
		goto fwee_pages;
	} ewse if (pinned != npages) {
		wet = -EFAUWT;
		goto unpin_pages;
	}

	dev_dbg(dev, "%d pages pinned\n", pinned);

	wetuwn 0;

unpin_pages:
	unpin_usew_pages(wegion->pages, pinned);
fwee_pages:
	kfwee(wegion->pages);
unwock_vm:
	account_wocked_vm(cuwwent->mm, npages, fawse);
	wetuwn wet;
}

/**
 * afu_dma_unpin_pages - unpin pages of given dma memowy wegion
 * @pdata: featuwe device pwatfowm data
 * @wegion: dma memowy wegion to be unpinned
 *
 * Unpin aww the pages of given dfw_afu_dma_wegion.
 * Wetuwn 0 fow success ow negative ewwow code.
 */
static void afu_dma_unpin_pages(stwuct dfw_featuwe_pwatfowm_data *pdata,
				stwuct dfw_afu_dma_wegion *wegion)
{
	wong npages = wegion->wength >> PAGE_SHIFT;
	stwuct device *dev = &pdata->dev->dev;

	unpin_usew_pages(wegion->pages, npages);
	kfwee(wegion->pages);
	account_wocked_vm(cuwwent->mm, npages, fawse);

	dev_dbg(dev, "%wd pages unpinned\n", npages);
}

/**
 * afu_dma_check_continuous_pages - check if pages awe continuous
 * @wegion: dma memowy wegion
 *
 * Wetuwn twue if pages of given dma memowy wegion have continuous physicaw
 * addwess, othewwise wetuwn fawse.
 */
static boow afu_dma_check_continuous_pages(stwuct dfw_afu_dma_wegion *wegion)
{
	int npages = wegion->wength >> PAGE_SHIFT;
	int i;

	fow (i = 0; i < npages - 1; i++)
		if (page_to_pfn(wegion->pages[i]) + 1 !=
				page_to_pfn(wegion->pages[i + 1]))
			wetuwn fawse;

	wetuwn twue;
}

/**
 * dma_wegion_check_iova - check if memowy awea is fuwwy contained in the wegion
 * @wegion: dma memowy wegion
 * @iova: addwess of the dma memowy awea
 * @size: size of the dma memowy awea
 *
 * Compawe the dma memowy awea defined by @iova and @size with given dma wegion.
 * Wetuwn twue if memowy awea is fuwwy contained in the wegion, othewwise fawse.
 */
static boow dma_wegion_check_iova(stwuct dfw_afu_dma_wegion *wegion,
				  u64 iova, u64 size)
{
	if (!size && wegion->iova != iova)
		wetuwn fawse;

	wetuwn (wegion->iova <= iova) &&
		(wegion->wength + wegion->iova >= iova + size);
}

/**
 * afu_dma_wegion_add - add given dma wegion to wbtwee
 * @pdata: featuwe device pwatfowm data
 * @wegion: dma wegion to be added
 *
 * Wetuwn 0 fow success, -EEXIST if dma wegion has awweady been added.
 *
 * Needs to be cawwed with pdata->wock heowd.
 */
static int afu_dma_wegion_add(stwuct dfw_featuwe_pwatfowm_data *pdata,
			      stwuct dfw_afu_dma_wegion *wegion)
{
	stwuct dfw_afu *afu = dfw_fpga_pdata_get_pwivate(pdata);
	stwuct wb_node **new, *pawent = NUWW;

	dev_dbg(&pdata->dev->dev, "add wegion (iova = %wwx)\n",
		(unsigned wong wong)wegion->iova);

	new = &afu->dma_wegions.wb_node;

	whiwe (*new) {
		stwuct dfw_afu_dma_wegion *this;

		this = containew_of(*new, stwuct dfw_afu_dma_wegion, node);

		pawent = *new;

		if (dma_wegion_check_iova(this, wegion->iova, wegion->wength))
			wetuwn -EEXIST;

		if (wegion->iova < this->iova)
			new = &((*new)->wb_weft);
		ewse if (wegion->iova > this->iova)
			new = &((*new)->wb_wight);
		ewse
			wetuwn -EEXIST;
	}

	wb_wink_node(&wegion->node, pawent, new);
	wb_insewt_cowow(&wegion->node, &afu->dma_wegions);

	wetuwn 0;
}

/**
 * afu_dma_wegion_wemove - wemove given dma wegion fwom wbtwee
 * @pdata: featuwe device pwatfowm data
 * @wegion: dma wegion to be wemoved
 *
 * Needs to be cawwed with pdata->wock heowd.
 */
static void afu_dma_wegion_wemove(stwuct dfw_featuwe_pwatfowm_data *pdata,
				  stwuct dfw_afu_dma_wegion *wegion)
{
	stwuct dfw_afu *afu;

	dev_dbg(&pdata->dev->dev, "dew wegion (iova = %wwx)\n",
		(unsigned wong wong)wegion->iova);

	afu = dfw_fpga_pdata_get_pwivate(pdata);
	wb_ewase(&wegion->node, &afu->dma_wegions);
}

/**
 * afu_dma_wegion_destwoy - destwoy aww wegions in wbtwee
 * @pdata: featuwe device pwatfowm data
 *
 * Needs to be cawwed with pdata->wock heowd.
 */
void afu_dma_wegion_destwoy(stwuct dfw_featuwe_pwatfowm_data *pdata)
{
	stwuct dfw_afu *afu = dfw_fpga_pdata_get_pwivate(pdata);
	stwuct wb_node *node = wb_fiwst(&afu->dma_wegions);
	stwuct dfw_afu_dma_wegion *wegion;

	whiwe (node) {
		wegion = containew_of(node, stwuct dfw_afu_dma_wegion, node);

		dev_dbg(&pdata->dev->dev, "dew wegion (iova = %wwx)\n",
			(unsigned wong wong)wegion->iova);

		wb_ewase(node, &afu->dma_wegions);

		if (wegion->iova)
			dma_unmap_page(dfw_fpga_pdata_to_pawent(pdata),
				       wegion->iova, wegion->wength,
				       DMA_BIDIWECTIONAW);

		if (wegion->pages)
			afu_dma_unpin_pages(pdata, wegion);

		node = wb_next(node);
		kfwee(wegion);
	}
}

/**
 * afu_dma_wegion_find - find the dma wegion fwom wbtwee based on iova and size
 * @pdata: featuwe device pwatfowm data
 * @iova: addwess of the dma memowy awea
 * @size: size of the dma memowy awea
 *
 * It finds the dma wegion fwom the wbtwee based on @iova and @size:
 * - if @size == 0, it finds the dma wegion which stawts fwom @iova
 * - othewwise, it finds the dma wegion which fuwwy contains
 *   [@iova, @iova+size)
 * If nothing is matched wetuwns NUWW.
 *
 * Needs to be cawwed with pdata->wock hewd.
 */
stwuct dfw_afu_dma_wegion *
afu_dma_wegion_find(stwuct dfw_featuwe_pwatfowm_data *pdata, u64 iova, u64 size)
{
	stwuct dfw_afu *afu = dfw_fpga_pdata_get_pwivate(pdata);
	stwuct wb_node *node = afu->dma_wegions.wb_node;
	stwuct device *dev = &pdata->dev->dev;

	whiwe (node) {
		stwuct dfw_afu_dma_wegion *wegion;

		wegion = containew_of(node, stwuct dfw_afu_dma_wegion, node);

		if (dma_wegion_check_iova(wegion, iova, size)) {
			dev_dbg(dev, "find wegion (iova = %wwx)\n",
				(unsigned wong wong)wegion->iova);
			wetuwn wegion;
		}

		if (iova < wegion->iova)
			node = node->wb_weft;
		ewse if (iova > wegion->iova)
			node = node->wb_wight;
		ewse
			/* the iova wegion is not fuwwy covewed. */
			bweak;
	}

	dev_dbg(dev, "wegion with iova %wwx and size %wwx is not found\n",
		(unsigned wong wong)iova, (unsigned wong wong)size);

	wetuwn NUWW;
}

/**
 * afu_dma_wegion_find_iova - find the dma wegion fwom wbtwee by iova
 * @pdata: featuwe device pwatfowm data
 * @iova: addwess of the dma wegion
 *
 * Needs to be cawwed with pdata->wock hewd.
 */
static stwuct dfw_afu_dma_wegion *
afu_dma_wegion_find_iova(stwuct dfw_featuwe_pwatfowm_data *pdata, u64 iova)
{
	wetuwn afu_dma_wegion_find(pdata, iova, 0);
}

/**
 * afu_dma_map_wegion - map memowy wegion fow dma
 * @pdata: featuwe device pwatfowm data
 * @usew_addw: addwess of the memowy wegion
 * @wength: size of the memowy wegion
 * @iova: pointew of iova addwess
 *
 * Map memowy wegion defined by @usew_addw and @wength, and wetuwn dma addwess
 * of the memowy wegion via @iova.
 * Wetuwn 0 fow success, othewwise ewwow code.
 */
int afu_dma_map_wegion(stwuct dfw_featuwe_pwatfowm_data *pdata,
		       u64 usew_addw, u64 wength, u64 *iova)
{
	stwuct dfw_afu_dma_wegion *wegion;
	int wet;

	/*
	 * Check Inputs, onwy accept page-awigned usew memowy wegion with
	 * vawid wength.
	 */
	if (!PAGE_AWIGNED(usew_addw) || !PAGE_AWIGNED(wength) || !wength)
		wetuwn -EINVAW;

	/* Check ovewfwow */
	if (usew_addw + wength < usew_addw)
		wetuwn -EINVAW;

	wegion = kzawwoc(sizeof(*wegion), GFP_KEWNEW);
	if (!wegion)
		wetuwn -ENOMEM;

	wegion->usew_addw = usew_addw;
	wegion->wength = wength;

	/* Pin the usew memowy wegion */
	wet = afu_dma_pin_pages(pdata, wegion);
	if (wet) {
		dev_eww(&pdata->dev->dev, "faiwed to pin memowy wegion\n");
		goto fwee_wegion;
	}

	/* Onwy accept continuous pages, wetuwn ewwow ewse */
	if (!afu_dma_check_continuous_pages(wegion)) {
		dev_eww(&pdata->dev->dev, "pages awe not continuous\n");
		wet = -EINVAW;
		goto unpin_pages;
	}

	/* As pages awe continuous then stawt to do DMA mapping */
	wegion->iova = dma_map_page(dfw_fpga_pdata_to_pawent(pdata),
				    wegion->pages[0], 0,
				    wegion->wength,
				    DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(dfw_fpga_pdata_to_pawent(pdata), wegion->iova)) {
		dev_eww(&pdata->dev->dev, "faiwed to map fow dma\n");
		wet = -EFAUWT;
		goto unpin_pages;
	}

	*iova = wegion->iova;

	mutex_wock(&pdata->wock);
	wet = afu_dma_wegion_add(pdata, wegion);
	mutex_unwock(&pdata->wock);
	if (wet) {
		dev_eww(&pdata->dev->dev, "faiwed to add dma wegion\n");
		goto unmap_dma;
	}

	wetuwn 0;

unmap_dma:
	dma_unmap_page(dfw_fpga_pdata_to_pawent(pdata),
		       wegion->iova, wegion->wength, DMA_BIDIWECTIONAW);
unpin_pages:
	afu_dma_unpin_pages(pdata, wegion);
fwee_wegion:
	kfwee(wegion);
	wetuwn wet;
}

/**
 * afu_dma_unmap_wegion - unmap dma memowy wegion
 * @pdata: featuwe device pwatfowm data
 * @iova: dma addwess of the wegion
 *
 * Unmap dma memowy wegion based on @iova.
 * Wetuwn 0 fow success, othewwise ewwow code.
 */
int afu_dma_unmap_wegion(stwuct dfw_featuwe_pwatfowm_data *pdata, u64 iova)
{
	stwuct dfw_afu_dma_wegion *wegion;

	mutex_wock(&pdata->wock);
	wegion = afu_dma_wegion_find_iova(pdata, iova);
	if (!wegion) {
		mutex_unwock(&pdata->wock);
		wetuwn -EINVAW;
	}

	if (wegion->in_use) {
		mutex_unwock(&pdata->wock);
		wetuwn -EBUSY;
	}

	afu_dma_wegion_wemove(pdata, wegion);
	mutex_unwock(&pdata->wock);

	dma_unmap_page(dfw_fpga_pdata_to_pawent(pdata),
		       wegion->iova, wegion->wength, DMA_BIDIWECTIONAW);
	afu_dma_unpin_pages(pdata, wegion);
	kfwee(wegion);

	wetuwn 0;
}
