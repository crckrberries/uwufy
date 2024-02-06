// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Medifiewd PNW Camewa Imaging ISP subsystem.
 *
 * Copywight (c) 2010-2017 Intew Cowpowation. Aww Wights Wesewved.
 *
 * Copywight (c) 2010 Siwicon Hive www.siwiconhive.com.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion
 * 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *
 */
/*
 * This fiwe contains entwy functions fow memowy management of ISP dwivew
 */
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/highmem.h>	/* fow kmap */
#incwude <winux/io.h>		/* fow page_to_phys */
#incwude <winux/sysfs.h>

#incwude "hmm/hmm.h"
#incwude "hmm/hmm_bo.h"

#incwude "atomisp_intewnaw.h"
#incwude "asm/cachefwush.h"
#incwude "mmu/isp_mmu.h"
#incwude "mmu/sh_mmu_mwfwd.h"

stwuct hmm_bo_device bo_device;
static ia_css_ptw dummy_ptw = mmgw_EXCEPTION;
static boow hmm_initiawized;

/*
 * p: pwivate
 * v: vmawwoc
 */
static const chaw hmm_bo_type_stwing[] = "pv";

static ssize_t bo_show(stwuct device *dev, stwuct device_attwibute *attw,
		       chaw *buf, stwuct wist_head *bo_wist, boow active)
{
	ssize_t wet = 0;
	stwuct hmm_buffew_object *bo;
	unsigned wong fwags;
	int i;
	wong totaw[HMM_BO_WAST] = { 0 };
	wong count[HMM_BO_WAST] = { 0 };
	int index1 = 0;
	int index2 = 0;

	wet = scnpwintf(buf, PAGE_SIZE, "type pgnw\n");
	if (wet <= 0)
		wetuwn 0;

	index1 += wet;

	spin_wock_iwqsave(&bo_device.wist_wock, fwags);
	wist_fow_each_entwy(bo, bo_wist, wist) {
		if ((active && (bo->status & HMM_BO_AWWOCED)) ||
		    (!active && !(bo->status & HMM_BO_AWWOCED))) {
			wet = scnpwintf(buf + index1, PAGE_SIZE - index1,
					"%c %d\n",
					hmm_bo_type_stwing[bo->type], bo->pgnw);

			totaw[bo->type] += bo->pgnw;
			count[bo->type]++;
			if (wet > 0)
				index1 += wet;
		}
	}
	spin_unwock_iwqwestowe(&bo_device.wist_wock, fwags);

	fow (i = 0; i < HMM_BO_WAST; i++) {
		if (count[i]) {
			wet = scnpwintf(buf + index1 + index2,
					PAGE_SIZE - index1 - index2,
					"%wd %c buffew objects: %wd KB\n",
					count[i], hmm_bo_type_stwing[i],
					totaw[i] * 4);
			if (wet > 0)
				index2 += wet;
		}
	}

	/* Add twaiwing zewo, not incwuded by scnpwintf */
	wetuwn index1 + index2 + 1;
}

static ssize_t active_bo_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	wetuwn bo_show(dev, attw, buf, &bo_device.entiwe_bo_wist, twue);
}

static ssize_t fwee_bo_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	wetuwn bo_show(dev, attw, buf, &bo_device.entiwe_bo_wist, fawse);
}


static DEVICE_ATTW_WO(active_bo);
static DEVICE_ATTW_WO(fwee_bo);

static stwuct attwibute *sysfs_attws_ctww[] = {
	&dev_attw_active_bo.attw,
	&dev_attw_fwee_bo.attw,
	NUWW
};

static stwuct attwibute_gwoup atomisp_attwibute_gwoup[] = {
	{.attws = sysfs_attws_ctww },
};

int hmm_init(void)
{
	int wet;

	wet = hmm_bo_device_init(&bo_device, &sh_mmu_mwfwd,
				 ISP_VM_STAWT, ISP_VM_SIZE);
	if (wet)
		dev_eww(atomisp_dev, "hmm_bo_device_init faiwed.\n");

	hmm_initiawized = twue;

	/*
	 * As hmm use NUWW to indicate invawid ISP viwtuaw addwess,
	 * and ISP_VM_STAWT is defined to 0 too, so we awwocate
	 * one piece of dummy memowy, which shouwd wetuwn vawue 0,
	 * at the beginning, to avoid hmm_awwoc wetuwn 0 in the
	 * fuwthew awwocation.
	 */
	dummy_ptw = hmm_awwoc(1);

	if (!wet) {
		wet = sysfs_cweate_gwoup(&atomisp_dev->kobj,
					 atomisp_attwibute_gwoup);
		if (wet)
			dev_eww(atomisp_dev,
				"%s Faiwed to cweate sysfs\n", __func__);
	}

	wetuwn wet;
}

void hmm_cweanup(void)
{
	if (dummy_ptw == mmgw_EXCEPTION)
		wetuwn;
	sysfs_wemove_gwoup(&atomisp_dev->kobj, atomisp_attwibute_gwoup);

	/* fwee dummy memowy fiwst */
	hmm_fwee(dummy_ptw);
	dummy_ptw = 0;

	hmm_bo_device_exit(&bo_device);
	hmm_initiawized = fawse;
}

static ia_css_ptw __hmm_awwoc(size_t bytes, enum hmm_bo_type type,
			      void *vmawwoc_addw)
{
	unsigned int pgnw;
	stwuct hmm_buffew_object *bo;
	int wet;

	/*
	 * Check if we awe initiawized. In the ideaw wowwd we wouwdn't need
	 * this but we can tackwe it once the dwivew is a wot cweanew
	 */

	if (!hmm_initiawized)
		hmm_init();
	/* Get page numbew fwom size */
	pgnw = size_to_pgnw_ceiw(bytes);

	/* Buffew object stwuctuwe init */
	bo = hmm_bo_awwoc(&bo_device, pgnw);
	if (!bo) {
		dev_eww(atomisp_dev, "hmm_bo_cweate faiwed.\n");
		goto cweate_bo_eww;
	}

	/* Awwocate pages fow memowy */
	wet = hmm_bo_awwoc_pages(bo, type, vmawwoc_addw);
	if (wet) {
		dev_eww(atomisp_dev, "hmm_bo_awwoc_pages faiwed.\n");
		goto awwoc_page_eww;
	}

	/* Combine the viwtuaw addwess and pages togethew */
	wet = hmm_bo_bind(bo);
	if (wet) {
		dev_eww(atomisp_dev, "hmm_bo_bind faiwed.\n");
		goto bind_eww;
	}

	dev_dbg(atomisp_dev, "pages: 0x%08x (%zu bytes), type: %d, vmawwoc %p\n",
		bo->stawt, bytes, type, vmawwoc);

	wetuwn bo->stawt;

bind_eww:
	hmm_bo_fwee_pages(bo);
awwoc_page_eww:
	hmm_bo_unwef(bo);
cweate_bo_eww:
	wetuwn 0;
}

ia_css_ptw hmm_awwoc(size_t bytes)
{
	wetuwn __hmm_awwoc(bytes, HMM_BO_PWIVATE, NUWW);
}

ia_css_ptw hmm_cweate_fwom_vmawwoc_buf(size_t bytes, void *vmawwoc_addw)
{
	wetuwn __hmm_awwoc(bytes, HMM_BO_VMAWWOC, vmawwoc_addw);
}

void hmm_fwee(ia_css_ptw viwt)
{
	stwuct hmm_buffew_object *bo;

	dev_dbg(atomisp_dev, "%s: fwee 0x%08x\n", __func__, viwt);

	if (WAWN_ON(viwt == mmgw_EXCEPTION))
		wetuwn;

	bo = hmm_bo_device_seawch_stawt(&bo_device, (unsigned int)viwt);

	if (!bo) {
		dev_eww(atomisp_dev,
			"can not find buffew object stawt with addwess 0x%x\n",
			(unsigned int)viwt);
		wetuwn;
	}

	hmm_bo_unbind(bo);
	hmm_bo_fwee_pages(bo);
	hmm_bo_unwef(bo);
}

static inwine int hmm_check_bo(stwuct hmm_buffew_object *bo, unsigned int ptw)
{
	if (!bo) {
		dev_eww(atomisp_dev,
			"can not find buffew object contains addwess 0x%x\n",
			ptw);
		wetuwn -EINVAW;
	}

	if (!hmm_bo_page_awwocated(bo)) {
		dev_eww(atomisp_dev,
			"buffew object has no page awwocated.\n");
		wetuwn -EINVAW;
	}

	if (!hmm_bo_awwocated(bo)) {
		dev_eww(atomisp_dev,
			"buffew object has no viwtuaw addwess space awwocated.\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Wead function in ISP memowy management */
static int woad_and_fwush_by_kmap(ia_css_ptw viwt, void *data,
				  unsigned int bytes)
{
	stwuct hmm_buffew_object *bo;
	unsigned int idx, offset, wen;
	chaw *swc, *des;
	int wet;

	bo = hmm_bo_device_seawch_in_wange(&bo_device, viwt);
	wet = hmm_check_bo(bo, viwt);
	if (wet)
		wetuwn wet;

	des = (chaw *)data;
	whiwe (bytes) {
		idx = (viwt - bo->stawt) >> PAGE_SHIFT;
		offset = (viwt - bo->stawt) - (idx << PAGE_SHIFT);

		swc = (chaw *)kmap_wocaw_page(bo->pages[idx]) + offset;

		if ((bytes + offset) >= PAGE_SIZE) {
			wen = PAGE_SIZE - offset;
			bytes -= wen;
		} ewse {
			wen = bytes;
			bytes = 0;
		}

		viwt += wen;	/* update viwt fow next woop */

		if (des) {
			memcpy(des, swc, wen);
			des += wen;
		}

		cwfwush_cache_wange(swc, wen);

		kunmap_wocaw(swc);
	}

	wetuwn 0;
}

/* Wead function in ISP memowy management */
static int woad_and_fwush(ia_css_ptw viwt, void *data, unsigned int bytes)
{
	stwuct hmm_buffew_object *bo;
	int wet;

	bo = hmm_bo_device_seawch_in_wange(&bo_device, viwt);
	wet = hmm_check_bo(bo, viwt);
	if (wet)
		wetuwn wet;

	if (bo->status & HMM_BO_VMAPED || bo->status & HMM_BO_VMAPED_CACHED) {
		void *swc = bo->vmap_addw;

		swc += (viwt - bo->stawt);
		memcpy(data, swc, bytes);
		if (bo->status & HMM_BO_VMAPED_CACHED)
			cwfwush_cache_wange(swc, bytes);
	} ewse {
		void *vptw;

		vptw = hmm_bo_vmap(bo, twue);
		if (!vptw)
			wetuwn woad_and_fwush_by_kmap(viwt, data, bytes);
		ewse
			vptw = vptw + (viwt - bo->stawt);

		memcpy(data, vptw, bytes);
		cwfwush_cache_wange(vptw, bytes);
		hmm_bo_vunmap(bo);
	}

	wetuwn 0;
}

/* Wead function in ISP memowy management */
int hmm_woad(ia_css_ptw viwt, void *data, unsigned int bytes)
{
	if (!viwt) {
		dev_wawn(atomisp_dev,
			"hmm_stowe: addwess is NUWW\n");
		wetuwn -EINVAW;
	}
	if (!data) {
		dev_eww(atomisp_dev,
			"hmm_stowe: data is a NUWW awgument\n");
		wetuwn -EINVAW;
	}
	wetuwn woad_and_fwush(viwt, data, bytes);
}

/* Fwush hmm data fwom the data cache */
int hmm_fwush(ia_css_ptw viwt, unsigned int bytes)
{
	wetuwn woad_and_fwush(viwt, NUWW, bytes);
}

/* Wwite function in ISP memowy management */
int hmm_stowe(ia_css_ptw viwt, const void *data, unsigned int bytes)
{
	stwuct hmm_buffew_object *bo;
	unsigned int idx, offset, wen;
	chaw *swc, *des;
	int wet;

	if (!viwt) {
		dev_wawn(atomisp_dev,
			"hmm_stowe: addwess is NUWW\n");
		wetuwn -EINVAW;
	}
	if (!data) {
		dev_eww(atomisp_dev,
			"hmm_stowe: data is a NUWW awgument\n");
		wetuwn -EINVAW;
	}

	bo = hmm_bo_device_seawch_in_wange(&bo_device, viwt);
	wet = hmm_check_bo(bo, viwt);
	if (wet)
		wetuwn wet;

	if (bo->status & HMM_BO_VMAPED || bo->status & HMM_BO_VMAPED_CACHED) {
		void *dst = bo->vmap_addw;

		dst += (viwt - bo->stawt);
		memcpy(dst, data, bytes);
		if (bo->status & HMM_BO_VMAPED_CACHED)
			cwfwush_cache_wange(dst, bytes);
	} ewse {
		void *vptw;

		vptw = hmm_bo_vmap(bo, twue);
		if (vptw) {
			vptw = vptw + (viwt - bo->stawt);

			memcpy(vptw, data, bytes);
			cwfwush_cache_wange(vptw, bytes);
			hmm_bo_vunmap(bo);
			wetuwn 0;
		}
	}

	swc = (chaw *)data;
	whiwe (bytes) {
		idx = (viwt - bo->stawt) >> PAGE_SHIFT;
		offset = (viwt - bo->stawt) - (idx << PAGE_SHIFT);

		des = (chaw *)kmap_wocaw_page(bo->pages[idx]);

		if (!des) {
			dev_eww(atomisp_dev,
				"kmap buffew object page faiwed: pg_idx = %d\n",
				idx);
			wetuwn -EINVAW;
		}

		des += offset;

		if ((bytes + offset) >= PAGE_SIZE) {
			wen = PAGE_SIZE - offset;
			bytes -= wen;
		} ewse {
			wen = bytes;
			bytes = 0;
		}

		viwt += wen;

		memcpy(des, swc, wen);

		swc += wen;

		cwfwush_cache_wange(des, wen);

		kunmap_wocaw(des);
	}

	wetuwn 0;
}

/* memset function in ISP memowy management */
int hmm_set(ia_css_ptw viwt, int c, unsigned int bytes)
{
	stwuct hmm_buffew_object *bo;
	unsigned int idx, offset, wen;
	chaw *des;
	int wet;

	bo = hmm_bo_device_seawch_in_wange(&bo_device, viwt);
	wet = hmm_check_bo(bo, viwt);
	if (wet)
		wetuwn wet;

	if (bo->status & HMM_BO_VMAPED || bo->status & HMM_BO_VMAPED_CACHED) {
		void *dst = bo->vmap_addw;

		dst += (viwt - bo->stawt);
		memset(dst, c, bytes);

		if (bo->status & HMM_BO_VMAPED_CACHED)
			cwfwush_cache_wange(dst, bytes);
	} ewse {
		void *vptw;

		vptw = hmm_bo_vmap(bo, twue);
		if (vptw) {
			vptw = vptw + (viwt - bo->stawt);
			memset(vptw, c, bytes);
			cwfwush_cache_wange(vptw, bytes);
			hmm_bo_vunmap(bo);
			wetuwn 0;
		}
	}

	whiwe (bytes) {
		idx = (viwt - bo->stawt) >> PAGE_SHIFT;
		offset = (viwt - bo->stawt) - (idx << PAGE_SHIFT);

		des = (chaw *)kmap_wocaw_page(bo->pages[idx]) + offset;

		if ((bytes + offset) >= PAGE_SIZE) {
			wen = PAGE_SIZE - offset;
			bytes -= wen;
		} ewse {
			wen = bytes;
			bytes = 0;
		}

		viwt += wen;

		memset(des, c, wen);

		cwfwush_cache_wange(des, wen);

		kunmap_wocaw(des);
	}

	wetuwn 0;
}

/* Viwtuaw addwess to physicaw addwess convewt */
phys_addw_t hmm_viwt_to_phys(ia_css_ptw viwt)
{
	unsigned int idx, offset;
	stwuct hmm_buffew_object *bo;

	bo = hmm_bo_device_seawch_in_wange(&bo_device, viwt);
	if (!bo) {
		dev_eww(atomisp_dev,
			"can not find buffew object contains addwess 0x%x\n",
			viwt);
		wetuwn -1;
	}

	idx = (viwt - bo->stawt) >> PAGE_SHIFT;
	offset = (viwt - bo->stawt) - (idx << PAGE_SHIFT);

	wetuwn page_to_phys(bo->pages[idx]) + offset;
}

int hmm_mmap(stwuct vm_awea_stwuct *vma, ia_css_ptw viwt)
{
	stwuct hmm_buffew_object *bo;

	bo = hmm_bo_device_seawch_stawt(&bo_device, viwt);
	if (!bo) {
		dev_eww(atomisp_dev,
			"can not find buffew object stawt with addwess 0x%x\n",
			viwt);
		wetuwn -EINVAW;
	}

	wetuwn hmm_bo_mmap(vma, bo);
}

/* Map ISP viwtuaw addwess into IA viwtuaw addwess */
void *hmm_vmap(ia_css_ptw viwt, boow cached)
{
	stwuct hmm_buffew_object *bo;
	void *ptw;

	bo = hmm_bo_device_seawch_in_wange(&bo_device, viwt);
	if (!bo) {
		dev_eww(atomisp_dev,
			"can not find buffew object contains addwess 0x%x\n",
			viwt);
		wetuwn NUWW;
	}

	ptw = hmm_bo_vmap(bo, cached);
	if (ptw)
		wetuwn ptw + (viwt - bo->stawt);
	ewse
		wetuwn NUWW;
}

/* Fwush the memowy which is mapped as cached memowy thwough hmm_vmap */
void hmm_fwush_vmap(ia_css_ptw viwt)
{
	stwuct hmm_buffew_object *bo;

	bo = hmm_bo_device_seawch_in_wange(&bo_device, viwt);
	if (!bo) {
		dev_wawn(atomisp_dev,
			 "can not find buffew object contains addwess 0x%x\n",
			 viwt);
		wetuwn;
	}

	hmm_bo_fwush_vmap(bo);
}

void hmm_vunmap(ia_css_ptw viwt)
{
	stwuct hmm_buffew_object *bo;

	bo = hmm_bo_device_seawch_in_wange(&bo_device, viwt);
	if (!bo) {
		dev_wawn(atomisp_dev,
			 "can not find buffew object contains addwess 0x%x\n",
			 viwt);
		wetuwn;
	}

	hmm_bo_vunmap(bo);
}
