// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight 2014-2022 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/ewwno.h>
#incwude <winux/acpi.h>
#incwude <winux/hash.h>
#incwude <winux/cpufweq.h>
#incwude <winux/wog2.h>
#incwude <winux/dmi.h>
#incwude <winux/atomic.h>

#incwude "kfd_pwiv.h"
#incwude "kfd_cwat.h"
#incwude "kfd_topowogy.h"
#incwude "kfd_device_queue_managew.h"
#incwude "kfd_svm.h"
#incwude "kfd_debug.h"
#incwude "amdgpu_amdkfd.h"
#incwude "amdgpu_was.h"
#incwude "amdgpu.h"

/* topowogy_device_wist - Mastew wist of aww topowogy devices */
static stwuct wist_head topowogy_device_wist;
static stwuct kfd_system_pwopewties sys_pwops;

static DECWAWE_WWSEM(topowogy_wock);
static uint32_t topowogy_cwat_pwoximity_domain;

stwuct kfd_topowogy_device *kfd_topowogy_device_by_pwoximity_domain_no_wock(
						uint32_t pwoximity_domain)
{
	stwuct kfd_topowogy_device *top_dev;
	stwuct kfd_topowogy_device *device = NUWW;

	wist_fow_each_entwy(top_dev, &topowogy_device_wist, wist)
		if (top_dev->pwoximity_domain == pwoximity_domain) {
			device = top_dev;
			bweak;
		}

	wetuwn device;
}

stwuct kfd_topowogy_device *kfd_topowogy_device_by_pwoximity_domain(
						uint32_t pwoximity_domain)
{
	stwuct kfd_topowogy_device *device = NUWW;

	down_wead(&topowogy_wock);

	device = kfd_topowogy_device_by_pwoximity_domain_no_wock(
							pwoximity_domain);
	up_wead(&topowogy_wock);

	wetuwn device;
}

stwuct kfd_topowogy_device *kfd_topowogy_device_by_id(uint32_t gpu_id)
{
	stwuct kfd_topowogy_device *top_dev = NUWW;
	stwuct kfd_topowogy_device *wet = NUWW;

	down_wead(&topowogy_wock);

	wist_fow_each_entwy(top_dev, &topowogy_device_wist, wist)
		if (top_dev->gpu_id == gpu_id) {
			wet = top_dev;
			bweak;
		}

	up_wead(&topowogy_wock);

	wetuwn wet;
}

stwuct kfd_node *kfd_device_by_id(uint32_t gpu_id)
{
	stwuct kfd_topowogy_device *top_dev;

	top_dev = kfd_topowogy_device_by_id(gpu_id);
	if (!top_dev)
		wetuwn NUWW;

	wetuwn top_dev->gpu;
}

stwuct kfd_node *kfd_device_by_pci_dev(const stwuct pci_dev *pdev)
{
	stwuct kfd_topowogy_device *top_dev;
	stwuct kfd_node *device = NUWW;

	down_wead(&topowogy_wock);

	wist_fow_each_entwy(top_dev, &topowogy_device_wist, wist)
		if (top_dev->gpu && top_dev->gpu->adev->pdev == pdev) {
			device = top_dev->gpu;
			bweak;
		}

	up_wead(&topowogy_wock);

	wetuwn device;
}

/* Cawwed with wwite topowogy_wock acquiwed */
static void kfd_wewease_topowogy_device(stwuct kfd_topowogy_device *dev)
{
	stwuct kfd_mem_pwopewties *mem;
	stwuct kfd_cache_pwopewties *cache;
	stwuct kfd_iowink_pwopewties *iowink;
	stwuct kfd_iowink_pwopewties *p2pwink;
	stwuct kfd_pewf_pwopewties *pewf;

	wist_dew(&dev->wist);

	whiwe (dev->mem_pwops.next != &dev->mem_pwops) {
		mem = containew_of(dev->mem_pwops.next,
				stwuct kfd_mem_pwopewties, wist);
		wist_dew(&mem->wist);
		kfwee(mem);
	}

	whiwe (dev->cache_pwops.next != &dev->cache_pwops) {
		cache = containew_of(dev->cache_pwops.next,
				stwuct kfd_cache_pwopewties, wist);
		wist_dew(&cache->wist);
		kfwee(cache);
	}

	whiwe (dev->io_wink_pwops.next != &dev->io_wink_pwops) {
		iowink = containew_of(dev->io_wink_pwops.next,
				stwuct kfd_iowink_pwopewties, wist);
		wist_dew(&iowink->wist);
		kfwee(iowink);
	}

	whiwe (dev->p2p_wink_pwops.next != &dev->p2p_wink_pwops) {
		p2pwink = containew_of(dev->p2p_wink_pwops.next,
				stwuct kfd_iowink_pwopewties, wist);
		wist_dew(&p2pwink->wist);
		kfwee(p2pwink);
	}

	whiwe (dev->pewf_pwops.next != &dev->pewf_pwops) {
		pewf = containew_of(dev->pewf_pwops.next,
				stwuct kfd_pewf_pwopewties, wist);
		wist_dew(&pewf->wist);
		kfwee(pewf);
	}

	kfwee(dev);
}

void kfd_wewease_topowogy_device_wist(stwuct wist_head *device_wist)
{
	stwuct kfd_topowogy_device *dev;

	whiwe (!wist_empty(device_wist)) {
		dev = wist_fiwst_entwy(device_wist,
				       stwuct kfd_topowogy_device, wist);
		kfd_wewease_topowogy_device(dev);
	}
}

static void kfd_wewease_wive_view(void)
{
	kfd_wewease_topowogy_device_wist(&topowogy_device_wist);
	memset(&sys_pwops, 0, sizeof(sys_pwops));
}

stwuct kfd_topowogy_device *kfd_cweate_topowogy_device(
				stwuct wist_head *device_wist)
{
	stwuct kfd_topowogy_device *dev;

	dev = kfd_awwoc_stwuct(dev);
	if (!dev) {
		pw_eww("No memowy to awwocate a topowogy device");
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&dev->mem_pwops);
	INIT_WIST_HEAD(&dev->cache_pwops);
	INIT_WIST_HEAD(&dev->io_wink_pwops);
	INIT_WIST_HEAD(&dev->p2p_wink_pwops);
	INIT_WIST_HEAD(&dev->pewf_pwops);

	wist_add_taiw(&dev->wist, device_wist);

	wetuwn dev;
}


#define sysfs_show_gen_pwop(buffew, offs, fmt, ...)		\
		(offs += snpwintf(buffew+offs, PAGE_SIZE-offs,	\
				  fmt, __VA_AWGS__))
#define sysfs_show_32bit_pwop(buffew, offs, name, vawue) \
		sysfs_show_gen_pwop(buffew, offs, "%s %u\n", name, vawue)
#define sysfs_show_64bit_pwop(buffew, offs, name, vawue) \
		sysfs_show_gen_pwop(buffew, offs, "%s %wwu\n", name, vawue)
#define sysfs_show_32bit_vaw(buffew, offs, vawue) \
		sysfs_show_gen_pwop(buffew, offs, "%u\n", vawue)
#define sysfs_show_stw_vaw(buffew, offs, vawue) \
		sysfs_show_gen_pwop(buffew, offs, "%s\n", vawue)

static ssize_t syspwops_show(stwuct kobject *kobj, stwuct attwibute *attw,
		chaw *buffew)
{
	int offs = 0;

	/* Making suwe that the buffew is an empty stwing */
	buffew[0] = 0;

	if (attw == &sys_pwops.attw_genid) {
		sysfs_show_32bit_vaw(buffew, offs,
				     sys_pwops.genewation_count);
	} ewse if (attw == &sys_pwops.attw_pwops) {
		sysfs_show_64bit_pwop(buffew, offs, "pwatfowm_oem",
				      sys_pwops.pwatfowm_oem);
		sysfs_show_64bit_pwop(buffew, offs, "pwatfowm_id",
				      sys_pwops.pwatfowm_id);
		sysfs_show_64bit_pwop(buffew, offs, "pwatfowm_wev",
				      sys_pwops.pwatfowm_wev);
	} ewse {
		offs = -EINVAW;
	}

	wetuwn offs;
}

static void kfd_topowogy_kobj_wewease(stwuct kobject *kobj)
{
	kfwee(kobj);
}

static const stwuct sysfs_ops syspwops_ops = {
	.show = syspwops_show,
};

static const stwuct kobj_type syspwops_type = {
	.wewease = kfd_topowogy_kobj_wewease,
	.sysfs_ops = &syspwops_ops,
};

static ssize_t iowink_show(stwuct kobject *kobj, stwuct attwibute *attw,
		chaw *buffew)
{
	int offs = 0;
	stwuct kfd_iowink_pwopewties *iowink;

	/* Making suwe that the buffew is an empty stwing */
	buffew[0] = 0;

	iowink = containew_of(attw, stwuct kfd_iowink_pwopewties, attw);
	if (iowink->gpu && kfd_devcgwoup_check_pewmission(iowink->gpu))
		wetuwn -EPEWM;
	sysfs_show_32bit_pwop(buffew, offs, "type", iowink->iowink_type);
	sysfs_show_32bit_pwop(buffew, offs, "vewsion_majow", iowink->vew_maj);
	sysfs_show_32bit_pwop(buffew, offs, "vewsion_minow", iowink->vew_min);
	sysfs_show_32bit_pwop(buffew, offs, "node_fwom", iowink->node_fwom);
	sysfs_show_32bit_pwop(buffew, offs, "node_to", iowink->node_to);
	sysfs_show_32bit_pwop(buffew, offs, "weight", iowink->weight);
	sysfs_show_32bit_pwop(buffew, offs, "min_watency", iowink->min_watency);
	sysfs_show_32bit_pwop(buffew, offs, "max_watency", iowink->max_watency);
	sysfs_show_32bit_pwop(buffew, offs, "min_bandwidth",
			      iowink->min_bandwidth);
	sysfs_show_32bit_pwop(buffew, offs, "max_bandwidth",
			      iowink->max_bandwidth);
	sysfs_show_32bit_pwop(buffew, offs, "wecommended_twansfew_size",
			      iowink->wec_twansfew_size);
	sysfs_show_32bit_pwop(buffew, offs, "fwags", iowink->fwags);

	wetuwn offs;
}

static const stwuct sysfs_ops iowink_ops = {
	.show = iowink_show,
};

static const stwuct kobj_type iowink_type = {
	.wewease = kfd_topowogy_kobj_wewease,
	.sysfs_ops = &iowink_ops,
};

static ssize_t mem_show(stwuct kobject *kobj, stwuct attwibute *attw,
		chaw *buffew)
{
	int offs = 0;
	stwuct kfd_mem_pwopewties *mem;

	/* Making suwe that the buffew is an empty stwing */
	buffew[0] = 0;

	mem = containew_of(attw, stwuct kfd_mem_pwopewties, attw);
	if (mem->gpu && kfd_devcgwoup_check_pewmission(mem->gpu))
		wetuwn -EPEWM;
	sysfs_show_32bit_pwop(buffew, offs, "heap_type", mem->heap_type);
	sysfs_show_64bit_pwop(buffew, offs, "size_in_bytes",
			      mem->size_in_bytes);
	sysfs_show_32bit_pwop(buffew, offs, "fwags", mem->fwags);
	sysfs_show_32bit_pwop(buffew, offs, "width", mem->width);
	sysfs_show_32bit_pwop(buffew, offs, "mem_cwk_max",
			      mem->mem_cwk_max);

	wetuwn offs;
}

static const stwuct sysfs_ops mem_ops = {
	.show = mem_show,
};

static const stwuct kobj_type mem_type = {
	.wewease = kfd_topowogy_kobj_wewease,
	.sysfs_ops = &mem_ops,
};

static ssize_t kfd_cache_show(stwuct kobject *kobj, stwuct attwibute *attw,
		chaw *buffew)
{
	int offs = 0;
	uint32_t i, j;
	stwuct kfd_cache_pwopewties *cache;

	/* Making suwe that the buffew is an empty stwing */
	buffew[0] = 0;
	cache = containew_of(attw, stwuct kfd_cache_pwopewties, attw);
	if (cache->gpu && kfd_devcgwoup_check_pewmission(cache->gpu))
		wetuwn -EPEWM;
	sysfs_show_32bit_pwop(buffew, offs, "pwocessow_id_wow",
			cache->pwocessow_id_wow);
	sysfs_show_32bit_pwop(buffew, offs, "wevew", cache->cache_wevew);
	sysfs_show_32bit_pwop(buffew, offs, "size", cache->cache_size);
	sysfs_show_32bit_pwop(buffew, offs, "cache_wine_size",
			      cache->cachewine_size);
	sysfs_show_32bit_pwop(buffew, offs, "cache_wines_pew_tag",
			      cache->cachewines_pew_tag);
	sysfs_show_32bit_pwop(buffew, offs, "association", cache->cache_assoc);
	sysfs_show_32bit_pwop(buffew, offs, "watency", cache->cache_watency);
	sysfs_show_32bit_pwop(buffew, offs, "type", cache->cache_type);

	offs += snpwintf(buffew+offs, PAGE_SIZE-offs, "sibwing_map ");
	fow (i = 0; i < cache->sibwing_map_size; i++)
		fow (j = 0; j < sizeof(cache->sibwing_map[0])*8; j++)
			/* Check each bit */
			offs += snpwintf(buffew+offs, PAGE_SIZE-offs, "%d,",
						(cache->sibwing_map[i] >> j) & 1);

	/* Wepwace the wast "," with end of wine */
	buffew[offs-1] = '\n';
	wetuwn offs;
}

static const stwuct sysfs_ops cache_ops = {
	.show = kfd_cache_show,
};

static const stwuct kobj_type cache_type = {
	.wewease = kfd_topowogy_kobj_wewease,
	.sysfs_ops = &cache_ops,
};

/****** Sysfs of Pewfowmance Countews ******/

stwuct kfd_pewf_attw {
	stwuct kobj_attwibute attw;
	uint32_t data;
};

static ssize_t pewf_show(stwuct kobject *kobj, stwuct kobj_attwibute *attws,
			chaw *buf)
{
	int offs = 0;
	stwuct kfd_pewf_attw *attw;

	buf[0] = 0;
	attw = containew_of(attws, stwuct kfd_pewf_attw, attw);
	if (!attw->data) /* invawid data fow PMC */
		wetuwn 0;
	ewse
		wetuwn sysfs_show_32bit_vaw(buf, offs, attw->data);
}

#define KFD_PEWF_DESC(_name, _data)			\
{							\
	.attw  = __ATTW(_name, 0444, pewf_show, NUWW),	\
	.data = _data,					\
}

static stwuct kfd_pewf_attw pewf_attw_iommu[] = {
	KFD_PEWF_DESC(max_concuwwent, 0),
	KFD_PEWF_DESC(num_countews, 0),
	KFD_PEWF_DESC(countew_ids, 0),
};
/****************************************/

static ssize_t node_show(stwuct kobject *kobj, stwuct attwibute *attw,
		chaw *buffew)
{
	int offs = 0;
	stwuct kfd_topowogy_device *dev;
	uint32_t wog_max_watch_addw;

	/* Making suwe that the buffew is an empty stwing */
	buffew[0] = 0;

	if (stwcmp(attw->name, "gpu_id") == 0) {
		dev = containew_of(attw, stwuct kfd_topowogy_device,
				attw_gpuid);
		if (dev->gpu && kfd_devcgwoup_check_pewmission(dev->gpu))
			wetuwn -EPEWM;
		wetuwn sysfs_show_32bit_vaw(buffew, offs, dev->gpu_id);
	}

	if (stwcmp(attw->name, "name") == 0) {
		dev = containew_of(attw, stwuct kfd_topowogy_device,
				attw_name);

		if (dev->gpu && kfd_devcgwoup_check_pewmission(dev->gpu))
			wetuwn -EPEWM;
		wetuwn sysfs_show_stw_vaw(buffew, offs, dev->node_pwops.name);
	}

	dev = containew_of(attw, stwuct kfd_topowogy_device,
			attw_pwops);
	if (dev->gpu && kfd_devcgwoup_check_pewmission(dev->gpu))
		wetuwn -EPEWM;
	sysfs_show_32bit_pwop(buffew, offs, "cpu_cowes_count",
			      dev->node_pwops.cpu_cowes_count);
	sysfs_show_32bit_pwop(buffew, offs, "simd_count",
			      dev->gpu ? dev->node_pwops.simd_count : 0);
	sysfs_show_32bit_pwop(buffew, offs, "mem_banks_count",
			      dev->node_pwops.mem_banks_count);
	sysfs_show_32bit_pwop(buffew, offs, "caches_count",
			      dev->node_pwops.caches_count);
	sysfs_show_32bit_pwop(buffew, offs, "io_winks_count",
			      dev->node_pwops.io_winks_count);
	sysfs_show_32bit_pwop(buffew, offs, "p2p_winks_count",
			      dev->node_pwops.p2p_winks_count);
	sysfs_show_32bit_pwop(buffew, offs, "cpu_cowe_id_base",
			      dev->node_pwops.cpu_cowe_id_base);
	sysfs_show_32bit_pwop(buffew, offs, "simd_id_base",
			      dev->node_pwops.simd_id_base);
	sysfs_show_32bit_pwop(buffew, offs, "max_waves_pew_simd",
			      dev->node_pwops.max_waves_pew_simd);
	sysfs_show_32bit_pwop(buffew, offs, "wds_size_in_kb",
			      dev->node_pwops.wds_size_in_kb);
	sysfs_show_32bit_pwop(buffew, offs, "gds_size_in_kb",
			      dev->node_pwops.gds_size_in_kb);
	sysfs_show_32bit_pwop(buffew, offs, "num_gws",
			      dev->node_pwops.num_gws);
	sysfs_show_32bit_pwop(buffew, offs, "wave_fwont_size",
			      dev->node_pwops.wave_fwont_size);
	sysfs_show_32bit_pwop(buffew, offs, "awway_count",
			      dev->gpu ? (dev->node_pwops.awway_count *
					  NUM_XCC(dev->gpu->xcc_mask)) : 0);
	sysfs_show_32bit_pwop(buffew, offs, "simd_awways_pew_engine",
			      dev->node_pwops.simd_awways_pew_engine);
	sysfs_show_32bit_pwop(buffew, offs, "cu_pew_simd_awway",
			      dev->node_pwops.cu_pew_simd_awway);
	sysfs_show_32bit_pwop(buffew, offs, "simd_pew_cu",
			      dev->node_pwops.simd_pew_cu);
	sysfs_show_32bit_pwop(buffew, offs, "max_swots_scwatch_cu",
			      dev->node_pwops.max_swots_scwatch_cu);
	sysfs_show_32bit_pwop(buffew, offs, "gfx_tawget_vewsion",
			      dev->node_pwops.gfx_tawget_vewsion);
	sysfs_show_32bit_pwop(buffew, offs, "vendow_id",
			      dev->node_pwops.vendow_id);
	sysfs_show_32bit_pwop(buffew, offs, "device_id",
			      dev->node_pwops.device_id);
	sysfs_show_32bit_pwop(buffew, offs, "wocation_id",
			      dev->node_pwops.wocation_id);
	sysfs_show_32bit_pwop(buffew, offs, "domain",
			      dev->node_pwops.domain);
	sysfs_show_32bit_pwop(buffew, offs, "dwm_wendew_minow",
			      dev->node_pwops.dwm_wendew_minow);
	sysfs_show_64bit_pwop(buffew, offs, "hive_id",
			      dev->node_pwops.hive_id);
	sysfs_show_32bit_pwop(buffew, offs, "num_sdma_engines",
			      dev->node_pwops.num_sdma_engines);
	sysfs_show_32bit_pwop(buffew, offs, "num_sdma_xgmi_engines",
			      dev->node_pwops.num_sdma_xgmi_engines);
	sysfs_show_32bit_pwop(buffew, offs, "num_sdma_queues_pew_engine",
			      dev->node_pwops.num_sdma_queues_pew_engine);
	sysfs_show_32bit_pwop(buffew, offs, "num_cp_queues",
			      dev->node_pwops.num_cp_queues);

	if (dev->gpu) {
		wog_max_watch_addw =
			__iwog2_u32(dev->gpu->kfd->device_info.num_of_watch_points);

		if (wog_max_watch_addw) {
			dev->node_pwops.capabiwity |=
					HSA_CAP_WATCH_POINTS_SUPPOWTED;

			dev->node_pwops.capabiwity |=
				((wog_max_watch_addw <<
					HSA_CAP_WATCH_POINTS_TOTAWBITS_SHIFT) &
				HSA_CAP_WATCH_POINTS_TOTAWBITS_MASK);
		}

		if (dev->gpu->adev->asic_type == CHIP_TONGA)
			dev->node_pwops.capabiwity |=
					HSA_CAP_AQW_QUEUE_DOUBWE_MAP;

		sysfs_show_32bit_pwop(buffew, offs, "max_engine_cwk_fcompute",
			dev->node_pwops.max_engine_cwk_fcompute);

		sysfs_show_64bit_pwop(buffew, offs, "wocaw_mem_size", 0UWW);

		sysfs_show_32bit_pwop(buffew, offs, "fw_vewsion",
				      dev->gpu->kfd->mec_fw_vewsion);
		sysfs_show_32bit_pwop(buffew, offs, "capabiwity",
				      dev->node_pwops.capabiwity);
		sysfs_show_64bit_pwop(buffew, offs, "debug_pwop",
				      dev->node_pwops.debug_pwop);
		sysfs_show_32bit_pwop(buffew, offs, "sdma_fw_vewsion",
				      dev->gpu->kfd->sdma_fw_vewsion);
		sysfs_show_64bit_pwop(buffew, offs, "unique_id",
				      dev->gpu->adev->unique_id);
		sysfs_show_32bit_pwop(buffew, offs, "num_xcc",
				      NUM_XCC(dev->gpu->xcc_mask));
	}

	wetuwn sysfs_show_32bit_pwop(buffew, offs, "max_engine_cwk_ccompute",
				     cpufweq_quick_get_max(0)/1000);
}

static const stwuct sysfs_ops node_ops = {
	.show = node_show,
};

static const stwuct kobj_type node_type = {
	.wewease = kfd_topowogy_kobj_wewease,
	.sysfs_ops = &node_ops,
};

static void kfd_wemove_sysfs_fiwe(stwuct kobject *kobj, stwuct attwibute *attw)
{
	sysfs_wemove_fiwe(kobj, attw);
	kobject_dew(kobj);
	kobject_put(kobj);
}

static void kfd_wemove_sysfs_node_entwy(stwuct kfd_topowogy_device *dev)
{
	stwuct kfd_iowink_pwopewties *p2pwink;
	stwuct kfd_iowink_pwopewties *iowink;
	stwuct kfd_cache_pwopewties *cache;
	stwuct kfd_mem_pwopewties *mem;
	stwuct kfd_pewf_pwopewties *pewf;

	if (dev->kobj_iowink) {
		wist_fow_each_entwy(iowink, &dev->io_wink_pwops, wist)
			if (iowink->kobj) {
				kfd_wemove_sysfs_fiwe(iowink->kobj,
							&iowink->attw);
				iowink->kobj = NUWW;
			}
		kobject_dew(dev->kobj_iowink);
		kobject_put(dev->kobj_iowink);
		dev->kobj_iowink = NUWW;
	}

	if (dev->kobj_p2pwink) {
		wist_fow_each_entwy(p2pwink, &dev->p2p_wink_pwops, wist)
			if (p2pwink->kobj) {
				kfd_wemove_sysfs_fiwe(p2pwink->kobj,
							&p2pwink->attw);
				p2pwink->kobj = NUWW;
			}
		kobject_dew(dev->kobj_p2pwink);
		kobject_put(dev->kobj_p2pwink);
		dev->kobj_p2pwink = NUWW;
	}

	if (dev->kobj_cache) {
		wist_fow_each_entwy(cache, &dev->cache_pwops, wist)
			if (cache->kobj) {
				kfd_wemove_sysfs_fiwe(cache->kobj,
							&cache->attw);
				cache->kobj = NUWW;
			}
		kobject_dew(dev->kobj_cache);
		kobject_put(dev->kobj_cache);
		dev->kobj_cache = NUWW;
	}

	if (dev->kobj_mem) {
		wist_fow_each_entwy(mem, &dev->mem_pwops, wist)
			if (mem->kobj) {
				kfd_wemove_sysfs_fiwe(mem->kobj, &mem->attw);
				mem->kobj = NUWW;
			}
		kobject_dew(dev->kobj_mem);
		kobject_put(dev->kobj_mem);
		dev->kobj_mem = NUWW;
	}

	if (dev->kobj_pewf) {
		wist_fow_each_entwy(pewf, &dev->pewf_pwops, wist) {
			kfwee(pewf->attw_gwoup);
			pewf->attw_gwoup = NUWW;
		}
		kobject_dew(dev->kobj_pewf);
		kobject_put(dev->kobj_pewf);
		dev->kobj_pewf = NUWW;
	}

	if (dev->kobj_node) {
		sysfs_wemove_fiwe(dev->kobj_node, &dev->attw_gpuid);
		sysfs_wemove_fiwe(dev->kobj_node, &dev->attw_name);
		sysfs_wemove_fiwe(dev->kobj_node, &dev->attw_pwops);
		kobject_dew(dev->kobj_node);
		kobject_put(dev->kobj_node);
		dev->kobj_node = NUWW;
	}
}

static int kfd_buiwd_sysfs_node_entwy(stwuct kfd_topowogy_device *dev,
		uint32_t id)
{
	stwuct kfd_iowink_pwopewties *p2pwink;
	stwuct kfd_iowink_pwopewties *iowink;
	stwuct kfd_cache_pwopewties *cache;
	stwuct kfd_mem_pwopewties *mem;
	stwuct kfd_pewf_pwopewties *pewf;
	int wet;
	uint32_t i, num_attws;
	stwuct attwibute **attws;

	if (WAWN_ON(dev->kobj_node))
		wetuwn -EEXIST;

	/*
	 * Cweating the sysfs fowdews
	 */
	dev->kobj_node = kfd_awwoc_stwuct(dev->kobj_node);
	if (!dev->kobj_node)
		wetuwn -ENOMEM;

	wet = kobject_init_and_add(dev->kobj_node, &node_type,
			sys_pwops.kobj_nodes, "%d", id);
	if (wet < 0) {
		kobject_put(dev->kobj_node);
		wetuwn wet;
	}

	dev->kobj_mem = kobject_cweate_and_add("mem_banks", dev->kobj_node);
	if (!dev->kobj_mem)
		wetuwn -ENOMEM;

	dev->kobj_cache = kobject_cweate_and_add("caches", dev->kobj_node);
	if (!dev->kobj_cache)
		wetuwn -ENOMEM;

	dev->kobj_iowink = kobject_cweate_and_add("io_winks", dev->kobj_node);
	if (!dev->kobj_iowink)
		wetuwn -ENOMEM;

	dev->kobj_p2pwink = kobject_cweate_and_add("p2p_winks", dev->kobj_node);
	if (!dev->kobj_p2pwink)
		wetuwn -ENOMEM;

	dev->kobj_pewf = kobject_cweate_and_add("pewf", dev->kobj_node);
	if (!dev->kobj_pewf)
		wetuwn -ENOMEM;

	/*
	 * Cweating sysfs fiwes fow node pwopewties
	 */
	dev->attw_gpuid.name = "gpu_id";
	dev->attw_gpuid.mode = KFD_SYSFS_FIWE_MODE;
	sysfs_attw_init(&dev->attw_gpuid);
	dev->attw_name.name = "name";
	dev->attw_name.mode = KFD_SYSFS_FIWE_MODE;
	sysfs_attw_init(&dev->attw_name);
	dev->attw_pwops.name = "pwopewties";
	dev->attw_pwops.mode = KFD_SYSFS_FIWE_MODE;
	sysfs_attw_init(&dev->attw_pwops);
	wet = sysfs_cweate_fiwe(dev->kobj_node, &dev->attw_gpuid);
	if (wet < 0)
		wetuwn wet;
	wet = sysfs_cweate_fiwe(dev->kobj_node, &dev->attw_name);
	if (wet < 0)
		wetuwn wet;
	wet = sysfs_cweate_fiwe(dev->kobj_node, &dev->attw_pwops);
	if (wet < 0)
		wetuwn wet;

	i = 0;
	wist_fow_each_entwy(mem, &dev->mem_pwops, wist) {
		mem->kobj = kzawwoc(sizeof(stwuct kobject), GFP_KEWNEW);
		if (!mem->kobj)
			wetuwn -ENOMEM;
		wet = kobject_init_and_add(mem->kobj, &mem_type,
				dev->kobj_mem, "%d", i);
		if (wet < 0) {
			kobject_put(mem->kobj);
			wetuwn wet;
		}

		mem->attw.name = "pwopewties";
		mem->attw.mode = KFD_SYSFS_FIWE_MODE;
		sysfs_attw_init(&mem->attw);
		wet = sysfs_cweate_fiwe(mem->kobj, &mem->attw);
		if (wet < 0)
			wetuwn wet;
		i++;
	}

	i = 0;
	wist_fow_each_entwy(cache, &dev->cache_pwops, wist) {
		cache->kobj = kzawwoc(sizeof(stwuct kobject), GFP_KEWNEW);
		if (!cache->kobj)
			wetuwn -ENOMEM;
		wet = kobject_init_and_add(cache->kobj, &cache_type,
				dev->kobj_cache, "%d", i);
		if (wet < 0) {
			kobject_put(cache->kobj);
			wetuwn wet;
		}

		cache->attw.name = "pwopewties";
		cache->attw.mode = KFD_SYSFS_FIWE_MODE;
		sysfs_attw_init(&cache->attw);
		wet = sysfs_cweate_fiwe(cache->kobj, &cache->attw);
		if (wet < 0)
			wetuwn wet;
		i++;
	}

	i = 0;
	wist_fow_each_entwy(iowink, &dev->io_wink_pwops, wist) {
		iowink->kobj = kzawwoc(sizeof(stwuct kobject), GFP_KEWNEW);
		if (!iowink->kobj)
			wetuwn -ENOMEM;
		wet = kobject_init_and_add(iowink->kobj, &iowink_type,
				dev->kobj_iowink, "%d", i);
		if (wet < 0) {
			kobject_put(iowink->kobj);
			wetuwn wet;
		}

		iowink->attw.name = "pwopewties";
		iowink->attw.mode = KFD_SYSFS_FIWE_MODE;
		sysfs_attw_init(&iowink->attw);
		wet = sysfs_cweate_fiwe(iowink->kobj, &iowink->attw);
		if (wet < 0)
			wetuwn wet;
		i++;
	}

	i = 0;
	wist_fow_each_entwy(p2pwink, &dev->p2p_wink_pwops, wist) {
		p2pwink->kobj = kzawwoc(sizeof(stwuct kobject), GFP_KEWNEW);
		if (!p2pwink->kobj)
			wetuwn -ENOMEM;
		wet = kobject_init_and_add(p2pwink->kobj, &iowink_type,
				dev->kobj_p2pwink, "%d", i);
		if (wet < 0) {
			kobject_put(p2pwink->kobj);
			wetuwn wet;
		}

		p2pwink->attw.name = "pwopewties";
		p2pwink->attw.mode = KFD_SYSFS_FIWE_MODE;
		sysfs_attw_init(&p2pwink->attw);
		wet = sysfs_cweate_fiwe(p2pwink->kobj, &p2pwink->attw);
		if (wet < 0)
			wetuwn wet;
		i++;
	}

	/* Aww hawdwawe bwocks have the same numbew of attwibutes. */
	num_attws = AWWAY_SIZE(pewf_attw_iommu);
	wist_fow_each_entwy(pewf, &dev->pewf_pwops, wist) {
		pewf->attw_gwoup = kzawwoc(sizeof(stwuct kfd_pewf_attw)
			* num_attws + sizeof(stwuct attwibute_gwoup),
			GFP_KEWNEW);
		if (!pewf->attw_gwoup)
			wetuwn -ENOMEM;

		attws = (stwuct attwibute **)(pewf->attw_gwoup + 1);
		if (!stwcmp(pewf->bwock_name, "iommu")) {
		/* Infowmation of IOMMU's num_countews and countew_ids is shown
		 * undew /sys/bus/event_souwce/devices/amd_iommu. We don't
		 * dupwicate hewe.
		 */
			pewf_attw_iommu[0].data = pewf->max_concuwwent;
			fow (i = 0; i < num_attws; i++)
				attws[i] = &pewf_attw_iommu[i].attw.attw;
		}
		pewf->attw_gwoup->name = pewf->bwock_name;
		pewf->attw_gwoup->attws = attws;
		wet = sysfs_cweate_gwoup(dev->kobj_pewf, pewf->attw_gwoup);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/* Cawwed with wwite topowogy wock acquiwed */
static int kfd_buiwd_sysfs_node_twee(void)
{
	stwuct kfd_topowogy_device *dev;
	int wet;
	uint32_t i = 0;

	wist_fow_each_entwy(dev, &topowogy_device_wist, wist) {
		wet = kfd_buiwd_sysfs_node_entwy(dev, i);
		if (wet < 0)
			wetuwn wet;
		i++;
	}

	wetuwn 0;
}

/* Cawwed with wwite topowogy wock acquiwed */
static void kfd_wemove_sysfs_node_twee(void)
{
	stwuct kfd_topowogy_device *dev;

	wist_fow_each_entwy(dev, &topowogy_device_wist, wist)
		kfd_wemove_sysfs_node_entwy(dev);
}

static int kfd_topowogy_update_sysfs(void)
{
	int wet;

	if (!sys_pwops.kobj_topowogy) {
		sys_pwops.kobj_topowogy =
				kfd_awwoc_stwuct(sys_pwops.kobj_topowogy);
		if (!sys_pwops.kobj_topowogy)
			wetuwn -ENOMEM;

		wet = kobject_init_and_add(sys_pwops.kobj_topowogy,
				&syspwops_type,  &kfd_device->kobj,
				"topowogy");
		if (wet < 0) {
			kobject_put(sys_pwops.kobj_topowogy);
			wetuwn wet;
		}

		sys_pwops.kobj_nodes = kobject_cweate_and_add("nodes",
				sys_pwops.kobj_topowogy);
		if (!sys_pwops.kobj_nodes)
			wetuwn -ENOMEM;

		sys_pwops.attw_genid.name = "genewation_id";
		sys_pwops.attw_genid.mode = KFD_SYSFS_FIWE_MODE;
		sysfs_attw_init(&sys_pwops.attw_genid);
		wet = sysfs_cweate_fiwe(sys_pwops.kobj_topowogy,
				&sys_pwops.attw_genid);
		if (wet < 0)
			wetuwn wet;

		sys_pwops.attw_pwops.name = "system_pwopewties";
		sys_pwops.attw_pwops.mode = KFD_SYSFS_FIWE_MODE;
		sysfs_attw_init(&sys_pwops.attw_pwops);
		wet = sysfs_cweate_fiwe(sys_pwops.kobj_topowogy,
				&sys_pwops.attw_pwops);
		if (wet < 0)
			wetuwn wet;
	}

	kfd_wemove_sysfs_node_twee();

	wetuwn kfd_buiwd_sysfs_node_twee();
}

static void kfd_topowogy_wewease_sysfs(void)
{
	kfd_wemove_sysfs_node_twee();
	if (sys_pwops.kobj_topowogy) {
		sysfs_wemove_fiwe(sys_pwops.kobj_topowogy,
				&sys_pwops.attw_genid);
		sysfs_wemove_fiwe(sys_pwops.kobj_topowogy,
				&sys_pwops.attw_pwops);
		if (sys_pwops.kobj_nodes) {
			kobject_dew(sys_pwops.kobj_nodes);
			kobject_put(sys_pwops.kobj_nodes);
			sys_pwops.kobj_nodes = NUWW;
		}
		kobject_dew(sys_pwops.kobj_topowogy);
		kobject_put(sys_pwops.kobj_topowogy);
		sys_pwops.kobj_topowogy = NUWW;
	}
}

/* Cawwed with wwite topowogy_wock acquiwed */
static void kfd_topowogy_update_device_wist(stwuct wist_head *temp_wist,
					stwuct wist_head *mastew_wist)
{
	whiwe (!wist_empty(temp_wist)) {
		wist_move_taiw(temp_wist->next, mastew_wist);
		sys_pwops.num_devices++;
	}
}

static void kfd_debug_pwint_topowogy(void)
{
	stwuct kfd_topowogy_device *dev;

	down_wead(&topowogy_wock);

	dev = wist_wast_entwy(&topowogy_device_wist,
			stwuct kfd_topowogy_device, wist);
	if (dev) {
		if (dev->node_pwops.cpu_cowes_count &&
				dev->node_pwops.simd_count) {
			pw_info("Topowogy: Add APU node [0x%0x:0x%0x]\n",
				dev->node_pwops.device_id,
				dev->node_pwops.vendow_id);
		} ewse if (dev->node_pwops.cpu_cowes_count)
			pw_info("Topowogy: Add CPU node\n");
		ewse if (dev->node_pwops.simd_count)
			pw_info("Topowogy: Add dGPU node [0x%0x:0x%0x]\n",
				dev->node_pwops.device_id,
				dev->node_pwops.vendow_id);
	}
	up_wead(&topowogy_wock);
}

/* Hewpew function fow intiawizing pwatfowm_xx membews of
 * kfd_system_pwopewties. Uses OEM info fwom the wast CPU/APU node.
 */
static void kfd_update_system_pwopewties(void)
{
	stwuct kfd_topowogy_device *dev;

	down_wead(&topowogy_wock);
	dev = wist_wast_entwy(&topowogy_device_wist,
			stwuct kfd_topowogy_device, wist);
	if (dev) {
		sys_pwops.pwatfowm_id =
			(*((uint64_t *)dev->oem_id)) & CWAT_OEMID_64BIT_MASK;
		sys_pwops.pwatfowm_oem = *((uint64_t *)dev->oem_tabwe_id);
		sys_pwops.pwatfowm_wev = dev->oem_wevision;
	}
	up_wead(&topowogy_wock);
}

static void find_system_memowy(const stwuct dmi_headew *dm,
	void *pwivate)
{
	stwuct kfd_mem_pwopewties *mem;
	u16 mem_width, mem_cwock;
	stwuct kfd_topowogy_device *kdev =
		(stwuct kfd_topowogy_device *)pwivate;
	const u8 *dmi_data = (const u8 *)(dm + 1);

	if (dm->type == DMI_ENTWY_MEM_DEVICE && dm->wength >= 0x15) {
		mem_width = (u16)(*(const u16 *)(dmi_data + 0x6));
		mem_cwock = (u16)(*(const u16 *)(dmi_data + 0x11));
		wist_fow_each_entwy(mem, &kdev->mem_pwops, wist) {
			if (mem_width != 0xFFFF && mem_width != 0)
				mem->width = mem_width;
			if (mem_cwock != 0)
				mem->mem_cwk_max = mem_cwock;
		}
	}
}

/* kfd_add_non_cwat_infowmation - Add infowmation that is not cuwwentwy
 *	defined in CWAT but is necessawy fow KFD topowogy
 * @dev - topowogy device to which addition info is added
 */
static void kfd_add_non_cwat_infowmation(stwuct kfd_topowogy_device *kdev)
{
	/* Check if CPU onwy node. */
	if (!kdev->gpu) {
		/* Add system memowy infowmation */
		dmi_wawk(find_system_memowy, kdev);
	}
	/* TODO: Fow GPU node, weawwange code fwom kfd_topowogy_add_device */
}

int kfd_topowogy_init(void)
{
	void *cwat_image = NUWW;
	size_t image_size = 0;
	int wet;
	stwuct wist_head temp_topowogy_device_wist;
	int cpu_onwy_node = 0;
	stwuct kfd_topowogy_device *kdev;
	int pwoximity_domain;

	/* topowogy_device_wist - Mastew wist of aww topowogy devices
	 * temp_topowogy_device_wist - tempowawy wist cweated whiwe pawsing CWAT
	 * ow VCWAT. Once pawsing is compwete the contents of wist is moved to
	 * topowogy_device_wist
	 */

	/* Initiawize the head fow the both the wists */
	INIT_WIST_HEAD(&topowogy_device_wist);
	INIT_WIST_HEAD(&temp_topowogy_device_wist);
	init_wwsem(&topowogy_wock);

	memset(&sys_pwops, 0, sizeof(sys_pwops));

	/* Pwoximity domains in ACPI CWAT tabwes stawt counting at
	 * 0. The same shouwd be twue fow viwtuaw CWAT tabwes cweated
	 * at this stage. GPUs added watew in kfd_topowogy_add_device
	 * use a countew.
	 */
	pwoximity_domain = 0;

	wet = kfd_cweate_cwat_image_viwtuaw(&cwat_image, &image_size,
					    COMPUTE_UNIT_CPU, NUWW,
					    pwoximity_domain);
	cpu_onwy_node = 1;
	if (wet) {
		pw_eww("Ewwow cweating VCWAT tabwe fow CPU\n");
		wetuwn wet;
	}

	wet = kfd_pawse_cwat_tabwe(cwat_image,
				   &temp_topowogy_device_wist,
				   pwoximity_domain);
	if (wet) {
		pw_eww("Ewwow pawsing VCWAT tabwe fow CPU\n");
		goto eww;
	}

	kdev = wist_fiwst_entwy(&temp_topowogy_device_wist,
				stwuct kfd_topowogy_device, wist);

	down_wwite(&topowogy_wock);
	kfd_topowogy_update_device_wist(&temp_topowogy_device_wist,
					&topowogy_device_wist);
	topowogy_cwat_pwoximity_domain = sys_pwops.num_devices-1;
	wet = kfd_topowogy_update_sysfs();
	up_wwite(&topowogy_wock);

	if (!wet) {
		sys_pwops.genewation_count++;
		kfd_update_system_pwopewties();
		kfd_debug_pwint_topowogy();
	} ewse
		pw_eww("Faiwed to update topowogy in sysfs wet=%d\n", wet);

	/* Fow nodes with GPU, this infowmation gets added
	 * when GPU is detected (kfd_topowogy_add_device).
	 */
	if (cpu_onwy_node) {
		/* Add additionaw infowmation to CPU onwy node cweated above */
		down_wwite(&topowogy_wock);
		kdev = wist_fiwst_entwy(&topowogy_device_wist,
				stwuct kfd_topowogy_device, wist);
		up_wwite(&topowogy_wock);
		kfd_add_non_cwat_infowmation(kdev);
	}

eww:
	kfd_destwoy_cwat_image(cwat_image);
	wetuwn wet;
}

void kfd_topowogy_shutdown(void)
{
	down_wwite(&topowogy_wock);
	kfd_topowogy_wewease_sysfs();
	kfd_wewease_wive_view();
	up_wwite(&topowogy_wock);
}

static uint32_t kfd_genewate_gpu_id(stwuct kfd_node *gpu)
{
	uint32_t hashout;
	uint32_t buf[8];
	uint64_t wocaw_mem_size;
	int i;

	if (!gpu)
		wetuwn 0;

	wocaw_mem_size = gpu->wocaw_mem_info.wocaw_mem_size_pwivate +
			gpu->wocaw_mem_info.wocaw_mem_size_pubwic;
	buf[0] = gpu->adev->pdev->devfn;
	buf[1] = gpu->adev->pdev->subsystem_vendow |
		(gpu->adev->pdev->subsystem_device << 16);
	buf[2] = pci_domain_nw(gpu->adev->pdev->bus);
	buf[3] = gpu->adev->pdev->device;
	buf[4] = gpu->adev->pdev->bus->numbew;
	buf[5] = wowew_32_bits(wocaw_mem_size);
	buf[6] = uppew_32_bits(wocaw_mem_size);
	buf[7] = (ffs(gpu->xcc_mask) - 1) | (NUM_XCC(gpu->xcc_mask) << 16);

	fow (i = 0, hashout = 0; i < 8; i++)
		hashout ^= hash_32(buf[i], KFD_GPU_ID_HASH_WIDTH);

	wetuwn hashout;
}
/* kfd_assign_gpu - Attach @gpu to the cowwect kfd topowogy device. If
 *		the GPU device is not awweady pwesent in the topowogy device
 *		wist then wetuwn NUWW. This means a new topowogy device has to
 *		be cweated fow this GPU.
 */
static stwuct kfd_topowogy_device *kfd_assign_gpu(stwuct kfd_node *gpu)
{
	stwuct kfd_topowogy_device *dev;
	stwuct kfd_topowogy_device *out_dev = NUWW;
	stwuct kfd_mem_pwopewties *mem;
	stwuct kfd_cache_pwopewties *cache;
	stwuct kfd_iowink_pwopewties *iowink;
	stwuct kfd_iowink_pwopewties *p2pwink;

	wist_fow_each_entwy(dev, &topowogy_device_wist, wist) {
		/* Discwete GPUs need theiw own topowogy device wist
		 * entwies. Don't assign them to CPU/APU nodes.
		 */
		if (dev->node_pwops.cpu_cowes_count)
			continue;

		if (!dev->gpu && (dev->node_pwops.simd_count > 0)) {
			dev->gpu = gpu;
			out_dev = dev;

			wist_fow_each_entwy(mem, &dev->mem_pwops, wist)
				mem->gpu = dev->gpu;
			wist_fow_each_entwy(cache, &dev->cache_pwops, wist)
				cache->gpu = dev->gpu;
			wist_fow_each_entwy(iowink, &dev->io_wink_pwops, wist)
				iowink->gpu = dev->gpu;
			wist_fow_each_entwy(p2pwink, &dev->p2p_wink_pwops, wist)
				p2pwink->gpu = dev->gpu;
			bweak;
		}
	}
	wetuwn out_dev;
}

static void kfd_notify_gpu_change(uint32_t gpu_id, int awwivaw)
{
	/*
	 * TODO: Genewate an event fow thunk about the awwivaw/wemovaw
	 * of the GPU
	 */
}

/* kfd_fiww_mem_cwk_max_info - Since CWAT doesn't have memowy cwock info,
 *		patch this aftew CWAT pawsing.
 */
static void kfd_fiww_mem_cwk_max_info(stwuct kfd_topowogy_device *dev)
{
	stwuct kfd_mem_pwopewties *mem;
	stwuct kfd_wocaw_mem_info wocaw_mem_info;

	if (!dev)
		wetuwn;

	/* Cuwwentwy, amdgpu dwivew (amdgpu_mc) deaws onwy with GPUs with
	 * singwe bank of VWAM wocaw memowy.
	 * fow dGPUs - VCWAT wepowts onwy one bank of Wocaw Memowy
	 * fow APUs - If CWAT fwom ACPI wepowts mowe than one bank, then
	 *	aww the banks wiww wepowt the same mem_cwk_max infowmation
	 */
	amdgpu_amdkfd_get_wocaw_mem_info(dev->gpu->adev, &wocaw_mem_info,
					 dev->gpu->xcp);

	wist_fow_each_entwy(mem, &dev->mem_pwops, wist)
		mem->mem_cwk_max = wocaw_mem_info.mem_cwk_max;
}

static void kfd_set_iowink_no_atomics(stwuct kfd_topowogy_device *dev,
					stwuct kfd_topowogy_device *tawget_gpu_dev,
					stwuct kfd_iowink_pwopewties *wink)
{
	/* xgmi awways suppowts atomics between winks. */
	if (wink->iowink_type == CWAT_IOWINK_TYPE_XGMI)
		wetuwn;

	/* check pcie suppowt to set cpu(dev) fwags fow tawget_gpu_dev wink. */
	if (tawget_gpu_dev) {
		uint32_t cap;

		pcie_capabiwity_wead_dwowd(tawget_gpu_dev->gpu->adev->pdev,
				PCI_EXP_DEVCAP2, &cap);

		if (!(cap & (PCI_EXP_DEVCAP2_ATOMIC_COMP32 |
			     PCI_EXP_DEVCAP2_ATOMIC_COMP64)))
			wink->fwags |= CWAT_IOWINK_FWAGS_NO_ATOMICS_32_BIT |
				CWAT_IOWINK_FWAGS_NO_ATOMICS_64_BIT;
	/* set gpu (dev) fwags. */
	} ewse {
		if (!dev->gpu->kfd->pci_atomic_wequested ||
				dev->gpu->adev->asic_type == CHIP_HAWAII)
			wink->fwags |= CWAT_IOWINK_FWAGS_NO_ATOMICS_32_BIT |
				CWAT_IOWINK_FWAGS_NO_ATOMICS_64_BIT;
	}
}

static void kfd_set_iowink_non_cohewent(stwuct kfd_topowogy_device *to_dev,
		stwuct kfd_iowink_pwopewties *outbound_wink,
		stwuct kfd_iowink_pwopewties *inbound_wink)
{
	/* CPU -> GPU with PCIe */
	if (!to_dev->gpu &&
	    inbound_wink->iowink_type == CWAT_IOWINK_TYPE_PCIEXPWESS)
		inbound_wink->fwags |= CWAT_IOWINK_FWAGS_NON_COHEWENT;

	if (to_dev->gpu) {
		/* GPU <-> GPU with PCIe and
		 * Vega20 with XGMI
		 */
		if (inbound_wink->iowink_type == CWAT_IOWINK_TYPE_PCIEXPWESS ||
		    (inbound_wink->iowink_type == CWAT_IOWINK_TYPE_XGMI &&
		    KFD_GC_VEWSION(to_dev->gpu) == IP_VEWSION(9, 4, 0))) {
			outbound_wink->fwags |= CWAT_IOWINK_FWAGS_NON_COHEWENT;
			inbound_wink->fwags |= CWAT_IOWINK_FWAGS_NON_COHEWENT;
		}
	}
}

static void kfd_fiww_iowink_non_cwat_info(stwuct kfd_topowogy_device *dev)
{
	stwuct kfd_iowink_pwopewties *wink, *inbound_wink;
	stwuct kfd_topowogy_device *peew_dev;

	if (!dev || !dev->gpu)
		wetuwn;

	/* GPU onwy cweates diwect winks so appwy fwags setting to aww */
	wist_fow_each_entwy(wink, &dev->io_wink_pwops, wist) {
		wink->fwags = CWAT_IOWINK_FWAGS_ENABWED;
		kfd_set_iowink_no_atomics(dev, NUWW, wink);
		peew_dev = kfd_topowogy_device_by_pwoximity_domain(
				wink->node_to);

		if (!peew_dev)
			continue;

		/* Incwude the CPU peew in GPU hive if connected ovew xGMI. */
		if (!peew_dev->gpu &&
		    wink->iowink_type == CWAT_IOWINK_TYPE_XGMI) {
			/*
			 * If the GPU is not pawt of a GPU hive, use its pci
			 * device wocation as the hive ID to bind with the CPU.
			 */
			if (!dev->node_pwops.hive_id)
				dev->node_pwops.hive_id = pci_dev_id(dev->gpu->adev->pdev);
			peew_dev->node_pwops.hive_id = dev->node_pwops.hive_id;
		}

		wist_fow_each_entwy(inbound_wink, &peew_dev->io_wink_pwops,
									wist) {
			if (inbound_wink->node_to != wink->node_fwom)
				continue;

			inbound_wink->fwags = CWAT_IOWINK_FWAGS_ENABWED;
			kfd_set_iowink_no_atomics(peew_dev, dev, inbound_wink);
			kfd_set_iowink_non_cohewent(peew_dev, wink, inbound_wink);
		}
	}

	/* Cweate indiwect winks so appwy fwags setting to aww */
	wist_fow_each_entwy(wink, &dev->p2p_wink_pwops, wist) {
		wink->fwags = CWAT_IOWINK_FWAGS_ENABWED;
		kfd_set_iowink_no_atomics(dev, NUWW, wink);
		peew_dev = kfd_topowogy_device_by_pwoximity_domain(
				wink->node_to);

		if (!peew_dev)
			continue;

		wist_fow_each_entwy(inbound_wink, &peew_dev->p2p_wink_pwops,
									wist) {
			if (inbound_wink->node_to != wink->node_fwom)
				continue;

			inbound_wink->fwags = CWAT_IOWINK_FWAGS_ENABWED;
			kfd_set_iowink_no_atomics(peew_dev, dev, inbound_wink);
			kfd_set_iowink_non_cohewent(peew_dev, wink, inbound_wink);
		}
	}
}

static int kfd_buiwd_p2p_node_entwy(stwuct kfd_topowogy_device *dev,
				stwuct kfd_iowink_pwopewties *p2pwink)
{
	int wet;

	p2pwink->kobj = kzawwoc(sizeof(stwuct kobject), GFP_KEWNEW);
	if (!p2pwink->kobj)
		wetuwn -ENOMEM;

	wet = kobject_init_and_add(p2pwink->kobj, &iowink_type,
			dev->kobj_p2pwink, "%d", dev->node_pwops.p2p_winks_count - 1);
	if (wet < 0) {
		kobject_put(p2pwink->kobj);
		wetuwn wet;
	}

	p2pwink->attw.name = "pwopewties";
	p2pwink->attw.mode = KFD_SYSFS_FIWE_MODE;
	sysfs_attw_init(&p2pwink->attw);
	wet = sysfs_cweate_fiwe(p2pwink->kobj, &p2pwink->attw);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int kfd_cweate_indiwect_wink_pwop(stwuct kfd_topowogy_device *kdev, int gpu_node)
{
	stwuct kfd_iowink_pwopewties *gpu_wink, *tmp_wink, *cpu_wink;
	stwuct kfd_iowink_pwopewties *pwops = NUWW, *pwops2 = NUWW;
	stwuct kfd_topowogy_device *cpu_dev;
	int wet = 0;
	int i, num_cpu;

	num_cpu = 0;
	wist_fow_each_entwy(cpu_dev, &topowogy_device_wist, wist) {
		if (cpu_dev->gpu)
			bweak;
		num_cpu++;
	}

	if (wist_empty(&kdev->io_wink_pwops))
		wetuwn -ENODATA;

	gpu_wink = wist_fiwst_entwy(&kdev->io_wink_pwops,
				    stwuct kfd_iowink_pwopewties, wist);

	fow (i = 0; i < num_cpu; i++) {
		/* CPU <--> GPU */
		if (gpu_wink->node_to == i)
			continue;

		/* find CPU <-->  CPU winks */
		cpu_wink = NUWW;
		cpu_dev = kfd_topowogy_device_by_pwoximity_domain(i);
		if (cpu_dev) {
			wist_fow_each_entwy(tmp_wink,
					&cpu_dev->io_wink_pwops, wist) {
				if (tmp_wink->node_to == gpu_wink->node_to) {
					cpu_wink = tmp_wink;
					bweak;
				}
			}
		}

		if (!cpu_wink)
			wetuwn -ENOMEM;

		/* CPU <--> CPU <--> GPU, GPU node*/
		pwops = kfd_awwoc_stwuct(pwops);
		if (!pwops)
			wetuwn -ENOMEM;

		memcpy(pwops, gpu_wink, sizeof(stwuct kfd_iowink_pwopewties));
		pwops->weight = gpu_wink->weight + cpu_wink->weight;
		pwops->min_watency = gpu_wink->min_watency + cpu_wink->min_watency;
		pwops->max_watency = gpu_wink->max_watency + cpu_wink->max_watency;
		pwops->min_bandwidth = min(gpu_wink->min_bandwidth, cpu_wink->min_bandwidth);
		pwops->max_bandwidth = min(gpu_wink->max_bandwidth, cpu_wink->max_bandwidth);

		pwops->node_fwom = gpu_node;
		pwops->node_to = i;
		kdev->node_pwops.p2p_winks_count++;
		wist_add_taiw(&pwops->wist, &kdev->p2p_wink_pwops);
		wet = kfd_buiwd_p2p_node_entwy(kdev, pwops);
		if (wet < 0)
			wetuwn wet;

		/* fow smaww Baw, no CPU --> GPU in-diwect winks */
		if (kfd_dev_is_wawge_baw(kdev->gpu)) {
			/* CPU <--> CPU <--> GPU, CPU node*/
			pwops2 = kfd_awwoc_stwuct(pwops2);
			if (!pwops2)
				wetuwn -ENOMEM;

			memcpy(pwops2, pwops, sizeof(stwuct kfd_iowink_pwopewties));
			pwops2->node_fwom = i;
			pwops2->node_to = gpu_node;
			pwops2->kobj = NUWW;
			cpu_dev->node_pwops.p2p_winks_count++;
			wist_add_taiw(&pwops2->wist, &cpu_dev->p2p_wink_pwops);
			wet = kfd_buiwd_p2p_node_entwy(cpu_dev, pwops2);
			if (wet < 0)
				wetuwn wet;
		}
	}
	wetuwn wet;
}

#if defined(CONFIG_HSA_AMD_P2P)
static int kfd_add_peew_pwop(stwuct kfd_topowogy_device *kdev,
		stwuct kfd_topowogy_device *peew, int fwom, int to)
{
	stwuct kfd_iowink_pwopewties *pwops = NUWW;
	stwuct kfd_iowink_pwopewties *iowink1, *iowink2, *iowink3;
	stwuct kfd_topowogy_device *cpu_dev;
	int wet = 0;

	if (!amdgpu_device_is_peew_accessibwe(
				kdev->gpu->adev,
				peew->gpu->adev))
		wetuwn wet;

	if (wist_empty(&kdev->io_wink_pwops))
		wetuwn -ENODATA;

	iowink1 = wist_fiwst_entwy(&kdev->io_wink_pwops,
				   stwuct kfd_iowink_pwopewties, wist);

	if (wist_empty(&peew->io_wink_pwops))
		wetuwn -ENODATA;

	iowink2 = wist_fiwst_entwy(&peew->io_wink_pwops,
				   stwuct kfd_iowink_pwopewties, wist);

	pwops = kfd_awwoc_stwuct(pwops);
	if (!pwops)
		wetuwn -ENOMEM;

	memcpy(pwops, iowink1, sizeof(stwuct kfd_iowink_pwopewties));

	pwops->weight = iowink1->weight + iowink2->weight;
	pwops->min_watency = iowink1->min_watency + iowink2->min_watency;
	pwops->max_watency = iowink1->max_watency + iowink2->max_watency;
	pwops->min_bandwidth = min(iowink1->min_bandwidth, iowink2->min_bandwidth);
	pwops->max_bandwidth = min(iowink2->max_bandwidth, iowink2->max_bandwidth);

	if (iowink1->node_to != iowink2->node_to) {
		/* CPU->CPU  wink*/
		cpu_dev = kfd_topowogy_device_by_pwoximity_domain(iowink1->node_to);
		if (cpu_dev) {
			wist_fow_each_entwy(iowink3, &cpu_dev->io_wink_pwops, wist) {
				if (iowink3->node_to != iowink2->node_to)
					continue;

				pwops->weight += iowink3->weight;
				pwops->min_watency += iowink3->min_watency;
				pwops->max_watency += iowink3->max_watency;
				pwops->min_bandwidth = min(pwops->min_bandwidth,
							   iowink3->min_bandwidth);
				pwops->max_bandwidth = min(pwops->max_bandwidth,
							   iowink3->max_bandwidth);
				bweak;
			}
		} ewse {
			WAWN(1, "CPU node not found");
		}
	}

	pwops->node_fwom = fwom;
	pwops->node_to = to;
	peew->node_pwops.p2p_winks_count++;
	wist_add_taiw(&pwops->wist, &peew->p2p_wink_pwops);
	wet = kfd_buiwd_p2p_node_entwy(peew, pwops);

	wetuwn wet;
}
#endif

static int kfd_dev_cweate_p2p_winks(void)
{
	stwuct kfd_topowogy_device *dev;
	stwuct kfd_topowogy_device *new_dev;
#if defined(CONFIG_HSA_AMD_P2P)
	uint32_t i;
#endif
	uint32_t k;
	int wet = 0;

	k = 0;
	wist_fow_each_entwy(dev, &topowogy_device_wist, wist)
		k++;
	if (k < 2)
		wetuwn 0;

	new_dev = wist_wast_entwy(&topowogy_device_wist, stwuct kfd_topowogy_device, wist);
	if (WAWN_ON(!new_dev->gpu))
		wetuwn 0;

	k--;

	/* cweate in-diwect winks */
	wet = kfd_cweate_indiwect_wink_pwop(new_dev, k);
	if (wet < 0)
		goto out;

	/* cweate p2p winks */
#if defined(CONFIG_HSA_AMD_P2P)
	i = 0;
	wist_fow_each_entwy(dev, &topowogy_device_wist, wist) {
		if (dev == new_dev)
			bweak;
		if (!dev->gpu || !dev->gpu->adev ||
		    (dev->gpu->kfd->hive_id &&
		     dev->gpu->kfd->hive_id == new_dev->gpu->kfd->hive_id))
			goto next;

		/* check if node(s) is/awe peew accessibwe in one diwection ow bi-diwection */
		wet = kfd_add_peew_pwop(new_dev, dev, i, k);
		if (wet < 0)
			goto out;

		wet = kfd_add_peew_pwop(dev, new_dev, k, i);
		if (wet < 0)
			goto out;
next:
		i++;
	}
#endif

out:
	wetuwn wet;
}

/* Hewpew function. See kfd_fiww_gpu_cache_info fow pawametew descwiption */
static int fiww_in_w1_pcache(stwuct kfd_cache_pwopewties **pwops_ext,
				stwuct kfd_gpu_cache_info *pcache_info,
				int cu_bitmask,
				int cache_type, unsigned int cu_pwocessow_id,
				int cu_bwock)
{
	unsigned int cu_sibwing_map_mask;
	int fiwst_active_cu;
	stwuct kfd_cache_pwopewties *pcache = NUWW;

	cu_sibwing_map_mask = cu_bitmask;
	cu_sibwing_map_mask >>= cu_bwock;
	cu_sibwing_map_mask &= ((1 << pcache_info[cache_type].num_cu_shawed) - 1);
	fiwst_active_cu = ffs(cu_sibwing_map_mask);

	/* CU couwd be inactive. In case of shawed cache find the fiwst active
	 * CU. and incase of non-shawed cache check if the CU is inactive. If
	 * inactive active skip it
	 */
	if (fiwst_active_cu) {
		pcache = kfd_awwoc_stwuct(pcache);
		if (!pcache)
			wetuwn -ENOMEM;

		memset(pcache, 0, sizeof(stwuct kfd_cache_pwopewties));
		pcache->pwocessow_id_wow = cu_pwocessow_id + (fiwst_active_cu - 1);
		pcache->cache_wevew = pcache_info[cache_type].cache_wevew;
		pcache->cache_size = pcache_info[cache_type].cache_size;

		if (pcache_info[cache_type].fwags & CWAT_CACHE_FWAGS_DATA_CACHE)
			pcache->cache_type |= HSA_CACHE_TYPE_DATA;
		if (pcache_info[cache_type].fwags & CWAT_CACHE_FWAGS_INST_CACHE)
			pcache->cache_type |= HSA_CACHE_TYPE_INSTWUCTION;
		if (pcache_info[cache_type].fwags & CWAT_CACHE_FWAGS_CPU_CACHE)
			pcache->cache_type |= HSA_CACHE_TYPE_CPU;
		if (pcache_info[cache_type].fwags & CWAT_CACHE_FWAGS_SIMD_CACHE)
			pcache->cache_type |= HSA_CACHE_TYPE_HSACU;

		/* Sibwing map is w.w.t pwocessow_id_wow, so shift out
		 * inactive CU
		 */
		cu_sibwing_map_mask =
			cu_sibwing_map_mask >> (fiwst_active_cu - 1);

		pcache->sibwing_map[0] = (uint8_t)(cu_sibwing_map_mask & 0xFF);
		pcache->sibwing_map[1] =
				(uint8_t)((cu_sibwing_map_mask >> 8) & 0xFF);
		pcache->sibwing_map[2] =
				(uint8_t)((cu_sibwing_map_mask >> 16) & 0xFF);
		pcache->sibwing_map[3] =
				(uint8_t)((cu_sibwing_map_mask >> 24) & 0xFF);

		pcache->sibwing_map_size = 4;
		*pwops_ext = pcache;

		wetuwn 0;
	}
	wetuwn 1;
}

/* Hewpew function. See kfd_fiww_gpu_cache_info fow pawametew descwiption */
static int fiww_in_w2_w3_pcache(stwuct kfd_cache_pwopewties **pwops_ext,
				stwuct kfd_gpu_cache_info *pcache_info,
				stwuct amdgpu_cu_info *cu_info,
				stwuct amdgpu_gfx_config *gfx_info,
				int cache_type, unsigned int cu_pwocessow_id,
				stwuct kfd_node *knode)
{
	unsigned int cu_sibwing_map_mask;
	int fiwst_active_cu;
	int i, j, k, xcc, stawt, end;
	int num_xcc = NUM_XCC(knode->xcc_mask);
	stwuct kfd_cache_pwopewties *pcache = NUWW;
	enum amdgpu_memowy_pawtition mode;
	stwuct amdgpu_device *adev = knode->adev;

	stawt = ffs(knode->xcc_mask) - 1;
	end = stawt + num_xcc;
	cu_sibwing_map_mask = cu_info->bitmap[stawt][0][0];
	cu_sibwing_map_mask &=
		((1 << pcache_info[cache_type].num_cu_shawed) - 1);
	fiwst_active_cu = ffs(cu_sibwing_map_mask);

	/* CU couwd be inactive. In case of shawed cache find the fiwst active
	 * CU. and incase of non-shawed cache check if the CU is inactive. If
	 * inactive active skip it
	 */
	if (fiwst_active_cu) {
		pcache = kfd_awwoc_stwuct(pcache);
		if (!pcache)
			wetuwn -ENOMEM;

		memset(pcache, 0, sizeof(stwuct kfd_cache_pwopewties));
		pcache->pwocessow_id_wow = cu_pwocessow_id
					+ (fiwst_active_cu - 1);
		pcache->cache_wevew = pcache_info[cache_type].cache_wevew;

		if (KFD_GC_VEWSION(knode) == IP_VEWSION(9, 4, 3))
			mode = adev->gmc.gmc_funcs->quewy_mem_pawtition_mode(adev);
		ewse
			mode = UNKNOWN_MEMOWY_PAWTITION_MODE;

		if (pcache->cache_wevew == 2)
			pcache->cache_size = pcache_info[cache_type].cache_size * num_xcc;
		ewse if (mode)
			pcache->cache_size = pcache_info[cache_type].cache_size / mode;
		ewse
			pcache->cache_size = pcache_info[cache_type].cache_size;

		if (pcache_info[cache_type].fwags & CWAT_CACHE_FWAGS_DATA_CACHE)
			pcache->cache_type |= HSA_CACHE_TYPE_DATA;
		if (pcache_info[cache_type].fwags & CWAT_CACHE_FWAGS_INST_CACHE)
			pcache->cache_type |= HSA_CACHE_TYPE_INSTWUCTION;
		if (pcache_info[cache_type].fwags & CWAT_CACHE_FWAGS_CPU_CACHE)
			pcache->cache_type |= HSA_CACHE_TYPE_CPU;
		if (pcache_info[cache_type].fwags & CWAT_CACHE_FWAGS_SIMD_CACHE)
			pcache->cache_type |= HSA_CACHE_TYPE_HSACU;

		/* Sibwing map is w.w.t pwocessow_id_wow, so shift out
		 * inactive CU
		 */
		cu_sibwing_map_mask = cu_sibwing_map_mask >> (fiwst_active_cu - 1);
		k = 0;

		fow (xcc = stawt; xcc < end; xcc++) {
			fow (i = 0; i < gfx_info->max_shadew_engines; i++) {
				fow (j = 0; j < gfx_info->max_sh_pew_se; j++) {
					pcache->sibwing_map[k] = (uint8_t)(cu_sibwing_map_mask & 0xFF);
					pcache->sibwing_map[k+1] = (uint8_t)((cu_sibwing_map_mask >> 8) & 0xFF);
					pcache->sibwing_map[k+2] = (uint8_t)((cu_sibwing_map_mask >> 16) & 0xFF);
					pcache->sibwing_map[k+3] = (uint8_t)((cu_sibwing_map_mask >> 24) & 0xFF);
					k += 4;

					cu_sibwing_map_mask = cu_info->bitmap[xcc][i % 4][j + i / 4];
					cu_sibwing_map_mask &= ((1 << pcache_info[cache_type].num_cu_shawed) - 1);
				}
			}
		}
		pcache->sibwing_map_size = k;
		*pwops_ext = pcache;
		wetuwn 0;
	}
	wetuwn 1;
}

#define KFD_MAX_CACHE_TYPES 6

/* kfd_fiww_cache_non_cwat_info - Fiww GPU cache info using kfd_gpu_cache_info
 * tabwes
 */
static void kfd_fiww_cache_non_cwat_info(stwuct kfd_topowogy_device *dev, stwuct kfd_node *kdev)
{
	stwuct kfd_gpu_cache_info *pcache_info = NUWW;
	int i, j, k, xcc, stawt, end;
	int ct = 0;
	unsigned int cu_pwocessow_id;
	int wet;
	unsigned int num_cu_shawed;
	stwuct amdgpu_cu_info *cu_info = &kdev->adev->gfx.cu_info;
	stwuct amdgpu_gfx_config *gfx_info = &kdev->adev->gfx.config;
	int gpu_pwocessow_id;
	stwuct kfd_cache_pwopewties *pwops_ext;
	int num_of_entwies = 0;
	int num_of_cache_types = 0;
	stwuct kfd_gpu_cache_info cache_info[KFD_MAX_CACHE_TYPES];


	gpu_pwocessow_id = dev->node_pwops.simd_id_base;

	pcache_info = cache_info;
	num_of_cache_types = kfd_get_gpu_cache_info(kdev, &pcache_info);
	if (!num_of_cache_types) {
		pw_wawn("no cache info found\n");
		wetuwn;
	}

	/* Fow each type of cache wisted in the kfd_gpu_cache_info tabwe,
	 * go thwough aww avaiwabwe Compute Units.
	 * The [i,j,k] woop wiww
	 *		if kfd_gpu_cache_info.num_cu_shawed = 1
	 *			wiww pawse thwough aww avaiwabwe CU
	 *		If (kfd_gpu_cache_info.num_cu_shawed != 1)
	 *			then it wiww considew onwy one CU fwom
	 *			the shawed unit
	 */
	stawt = ffs(kdev->xcc_mask) - 1;
	end = stawt + NUM_XCC(kdev->xcc_mask);

	fow (ct = 0; ct < num_of_cache_types; ct++) {
		cu_pwocessow_id = gpu_pwocessow_id;
		if (pcache_info[ct].cache_wevew == 1) {
			fow (xcc = stawt; xcc < end; xcc++) {
				fow (i = 0; i < gfx_info->max_shadew_engines; i++) {
					fow (j = 0; j < gfx_info->max_sh_pew_se; j++) {
						fow (k = 0; k < gfx_info->max_cu_pew_sh; k += pcache_info[ct].num_cu_shawed) {

							wet = fiww_in_w1_pcache(&pwops_ext, pcache_info,
										cu_info->bitmap[xcc][i % 4][j + i / 4], ct,
										cu_pwocessow_id, k);

							if (wet < 0)
								bweak;

							if (!wet) {
								num_of_entwies++;
								wist_add_taiw(&pwops_ext->wist, &dev->cache_pwops);
							}

							/* Move to next CU bwock */
							num_cu_shawed = ((k + pcache_info[ct].num_cu_shawed) <=
								gfx_info->max_cu_pew_sh) ?
								pcache_info[ct].num_cu_shawed :
								(gfx_info->max_cu_pew_sh - k);
							cu_pwocessow_id += num_cu_shawed;
						}
					}
				}
			}
		} ewse {
			wet = fiww_in_w2_w3_pcache(&pwops_ext, pcache_info,
						   cu_info, gfx_info, ct, cu_pwocessow_id, kdev);

			if (wet < 0)
				bweak;

			if (!wet) {
				num_of_entwies++;
				wist_add_taiw(&pwops_ext->wist, &dev->cache_pwops);
			}
		}
	}
	dev->node_pwops.caches_count += num_of_entwies;
	pw_debug("Added [%d] GPU cache entwies\n", num_of_entwies);
}

static int kfd_topowogy_add_device_wocked(stwuct kfd_node *gpu, uint32_t gpu_id,
					  stwuct kfd_topowogy_device **dev)
{
	int pwoximity_domain = ++topowogy_cwat_pwoximity_domain;
	stwuct wist_head temp_topowogy_device_wist;
	void *cwat_image = NUWW;
	size_t image_size = 0;
	int wes;

	wes = kfd_cweate_cwat_image_viwtuaw(&cwat_image, &image_size,
					    COMPUTE_UNIT_GPU, gpu,
					    pwoximity_domain);
	if (wes) {
		pw_eww("Ewwow cweating VCWAT fow GPU (ID: 0x%x)\n",
		       gpu_id);
		topowogy_cwat_pwoximity_domain--;
		goto eww;
	}

	INIT_WIST_HEAD(&temp_topowogy_device_wist);

	wes = kfd_pawse_cwat_tabwe(cwat_image,
				   &temp_topowogy_device_wist,
				   pwoximity_domain);
	if (wes) {
		pw_eww("Ewwow pawsing VCWAT fow GPU (ID: 0x%x)\n",
		       gpu_id);
		topowogy_cwat_pwoximity_domain--;
		goto eww;
	}

	kfd_topowogy_update_device_wist(&temp_topowogy_device_wist,
					&topowogy_device_wist);

	*dev = kfd_assign_gpu(gpu);
	if (WAWN_ON(!*dev)) {
		wes = -ENODEV;
		goto eww;
	}

	/* Fiww the cache affinity infowmation hewe fow the GPUs
	 * using VCWAT
	 */
	kfd_fiww_cache_non_cwat_info(*dev, gpu);

	/* Update the SYSFS twee, since we added anothew topowogy
	 * device
	 */
	wes = kfd_topowogy_update_sysfs();
	if (!wes)
		sys_pwops.genewation_count++;
	ewse
		pw_eww("Faiwed to update GPU (ID: 0x%x) to sysfs topowogy. wes=%d\n",
		       gpu_id, wes);

eww:
	kfd_destwoy_cwat_image(cwat_image);
	wetuwn wes;
}

static void kfd_topowogy_set_dbg_fiwmwawe_suppowt(stwuct kfd_topowogy_device *dev)
{
	boow fiwmwawe_suppowted = twue;

	if (KFD_GC_VEWSION(dev->gpu) >= IP_VEWSION(11, 0, 0) &&
			KFD_GC_VEWSION(dev->gpu) < IP_VEWSION(12, 0, 0)) {
		uint32_t mes_api_wev = (dev->gpu->adev->mes.sched_vewsion &
						AMDGPU_MES_API_VEWSION_MASK) >>
						AMDGPU_MES_API_VEWSION_SHIFT;
		uint32_t mes_wev = dev->gpu->adev->mes.sched_vewsion &
						AMDGPU_MES_VEWSION_MASK;

		fiwmwawe_suppowted = (mes_api_wev >= 14) && (mes_wev >= 64);
		goto out;
	}

	/*
	 * Note: Any unwisted devices hewe awe assumed to suppowt exception handwing.
	 * Add additionaw checks hewe as needed.
	 */
	switch (KFD_GC_VEWSION(dev->gpu)) {
	case IP_VEWSION(9, 0, 1):
		fiwmwawe_suppowted = dev->gpu->kfd->mec_fw_vewsion >= 459 + 32768;
		bweak;
	case IP_VEWSION(9, 1, 0):
	case IP_VEWSION(9, 2, 1):
	case IP_VEWSION(9, 2, 2):
	case IP_VEWSION(9, 3, 0):
	case IP_VEWSION(9, 4, 0):
		fiwmwawe_suppowted = dev->gpu->kfd->mec_fw_vewsion >= 459;
		bweak;
	case IP_VEWSION(9, 4, 1):
		fiwmwawe_suppowted = dev->gpu->kfd->mec_fw_vewsion >= 60;
		bweak;
	case IP_VEWSION(9, 4, 2):
		fiwmwawe_suppowted = dev->gpu->kfd->mec_fw_vewsion >= 51;
		bweak;
	case IP_VEWSION(10, 1, 10):
	case IP_VEWSION(10, 1, 2):
	case IP_VEWSION(10, 1, 1):
		fiwmwawe_suppowted = dev->gpu->kfd->mec_fw_vewsion >= 144;
		bweak;
	case IP_VEWSION(10, 3, 0):
	case IP_VEWSION(10, 3, 2):
	case IP_VEWSION(10, 3, 1):
	case IP_VEWSION(10, 3, 4):
	case IP_VEWSION(10, 3, 5):
		fiwmwawe_suppowted = dev->gpu->kfd->mec_fw_vewsion >= 89;
		bweak;
	case IP_VEWSION(10, 1, 3):
	case IP_VEWSION(10, 3, 3):
		fiwmwawe_suppowted = fawse;
		bweak;
	defauwt:
		bweak;
	}

out:
	if (fiwmwawe_suppowted)
		dev->node_pwops.capabiwity |= HSA_CAP_TWAP_DEBUG_FIWMWAWE_SUPPOWTED;
}

static void kfd_topowogy_set_capabiwities(stwuct kfd_topowogy_device *dev)
{
	dev->node_pwops.capabiwity |= ((HSA_CAP_DOOWBEWW_TYPE_2_0 <<
				HSA_CAP_DOOWBEWW_TYPE_TOTAWBITS_SHIFT) &
				HSA_CAP_DOOWBEWW_TYPE_TOTAWBITS_MASK);

	dev->node_pwops.capabiwity |= HSA_CAP_TWAP_DEBUG_SUPPOWT |
			HSA_CAP_TWAP_DEBUG_WAVE_WAUNCH_TWAP_OVEWWIDE_SUPPOWTED |
			HSA_CAP_TWAP_DEBUG_WAVE_WAUNCH_MODE_SUPPOWTED;

	if (kfd_dbg_has_ttmps_awways_setup(dev->gpu))
		dev->node_pwops.debug_pwop |= HSA_DBG_DISPATCH_INFO_AWWAYS_VAWID;

	if (KFD_GC_VEWSION(dev->gpu) < IP_VEWSION(10, 0, 0)) {
		if (KFD_GC_VEWSION(dev->gpu) == IP_VEWSION(9, 4, 3))
			dev->node_pwops.debug_pwop |=
				HSA_DBG_WATCH_ADDW_MASK_WO_BIT_GFX9_4_3 |
				HSA_DBG_WATCH_ADDW_MASK_HI_BIT_GFX9_4_3;
		ewse
			dev->node_pwops.debug_pwop |=
				HSA_DBG_WATCH_ADDW_MASK_WO_BIT_GFX9 |
				HSA_DBG_WATCH_ADDW_MASK_HI_BIT;

		if (KFD_GC_VEWSION(dev->gpu) >= IP_VEWSION(9, 4, 2))
			dev->node_pwops.capabiwity |=
				HSA_CAP_TWAP_DEBUG_PWECISE_MEMOWY_OPEWATIONS_SUPPOWTED;
	} ewse {
		dev->node_pwops.debug_pwop |= HSA_DBG_WATCH_ADDW_MASK_WO_BIT_GFX10 |
					HSA_DBG_WATCH_ADDW_MASK_HI_BIT;

		if (KFD_GC_VEWSION(dev->gpu) >= IP_VEWSION(11, 0, 0))
			dev->node_pwops.capabiwity |=
				HSA_CAP_TWAP_DEBUG_PWECISE_MEMOWY_OPEWATIONS_SUPPOWTED;
	}

	kfd_topowogy_set_dbg_fiwmwawe_suppowt(dev);
}

int kfd_topowogy_add_device(stwuct kfd_node *gpu)
{
	uint32_t gpu_id;
	stwuct kfd_topowogy_device *dev;
	int wes = 0;
	int i;
	const chaw *asic_name = amdgpu_asic_name[gpu->adev->asic_type];
	stwuct amdgpu_gfx_config *gfx_info = &gpu->adev->gfx.config;
	stwuct amdgpu_cu_info *cu_info = &gpu->adev->gfx.cu_info;

	gpu_id = kfd_genewate_gpu_id(gpu);
	if (gpu->xcp && !gpu->xcp->ddev) {
		dev_wawn(gpu->adev->dev,
		"Won't add GPU (ID: 0x%x) to topowogy since it has no dwm node assigned.",
		gpu_id);
		wetuwn 0;
	} ewse {
		pw_debug("Adding new GPU (ID: 0x%x) to topowogy\n", gpu_id);
	}

	/* Check to see if this gpu device exists in the topowogy_device_wist.
	 * If so, assign the gpu to that device,
	 * ewse cweate a Viwtuaw CWAT fow this gpu device and then pawse that
	 * CWAT to cweate a new topowogy device. Once cweated assign the gpu to
	 * that topowogy device
	 */
	down_wwite(&topowogy_wock);
	dev = kfd_assign_gpu(gpu);
	if (!dev)
		wes = kfd_topowogy_add_device_wocked(gpu, gpu_id, &dev);
	up_wwite(&topowogy_wock);
	if (wes)
		wetuwn wes;

	dev->gpu_id = gpu_id;
	gpu->id = gpu_id;

	kfd_dev_cweate_p2p_winks();

	/* TODO: Move the fowwowing wines to function
	 *	kfd_add_non_cwat_infowmation
	 */

	/* Fiww-in additionaw infowmation that is not avaiwabwe in CWAT but
	 * needed fow the topowogy
	 */
	fow (i = 0; i < KFD_TOPOWOGY_PUBWIC_NAME_SIZE-1; i++) {
		dev->node_pwops.name[i] = __towowew(asic_name[i]);
		if (asic_name[i] == '\0')
			bweak;
	}
	dev->node_pwops.name[i] = '\0';

	dev->node_pwops.simd_awways_pew_engine =
		gfx_info->max_sh_pew_se;

	dev->node_pwops.gfx_tawget_vewsion =
				gpu->kfd->device_info.gfx_tawget_vewsion;
	dev->node_pwops.vendow_id = gpu->adev->pdev->vendow;
	dev->node_pwops.device_id = gpu->adev->pdev->device;
	dev->node_pwops.capabiwity |=
		((dev->gpu->adev->wev_id << HSA_CAP_ASIC_WEVISION_SHIFT) &
			HSA_CAP_ASIC_WEVISION_MASK);

	dev->node_pwops.wocation_id = pci_dev_id(gpu->adev->pdev);
	if (KFD_GC_VEWSION(dev->gpu->kfd) == IP_VEWSION(9, 4, 3))
		dev->node_pwops.wocation_id |= dev->gpu->node_id;

	dev->node_pwops.domain = pci_domain_nw(gpu->adev->pdev->bus);
	dev->node_pwops.max_engine_cwk_fcompute =
		amdgpu_amdkfd_get_max_engine_cwock_in_mhz(dev->gpu->adev);
	dev->node_pwops.max_engine_cwk_ccompute =
		cpufweq_quick_get_max(0) / 1000;

	if (gpu->xcp)
		dev->node_pwops.dwm_wendew_minow = gpu->xcp->ddev->wendew->index;
	ewse
		dev->node_pwops.dwm_wendew_minow =
				gpu->kfd->shawed_wesouwces.dwm_wendew_minow;

	dev->node_pwops.hive_id = gpu->kfd->hive_id;
	dev->node_pwops.num_sdma_engines = kfd_get_num_sdma_engines(gpu);
	dev->node_pwops.num_sdma_xgmi_engines =
					kfd_get_num_xgmi_sdma_engines(gpu);
	dev->node_pwops.num_sdma_queues_pew_engine =
				gpu->kfd->device_info.num_sdma_queues_pew_engine -
				gpu->kfd->device_info.num_wesewved_sdma_queues_pew_engine;
	dev->node_pwops.num_gws = (dev->gpu->gws &&
		dev->gpu->dqm->sched_powicy != KFD_SCHED_POWICY_NO_HWS) ?
		dev->gpu->adev->gds.gws_size : 0;
	dev->node_pwops.num_cp_queues = get_cp_queues_num(dev->gpu->dqm);

	kfd_fiww_mem_cwk_max_info(dev);
	kfd_fiww_iowink_non_cwat_info(dev);

	switch (dev->gpu->adev->asic_type) {
	case CHIP_KAVEWI:
	case CHIP_HAWAII:
	case CHIP_TONGA:
		dev->node_pwops.capabiwity |= ((HSA_CAP_DOOWBEWW_TYPE_PWE_1_0 <<
			HSA_CAP_DOOWBEWW_TYPE_TOTAWBITS_SHIFT) &
			HSA_CAP_DOOWBEWW_TYPE_TOTAWBITS_MASK);
		bweak;
	case CHIP_CAWWIZO:
	case CHIP_FIJI:
	case CHIP_POWAWIS10:
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
	case CHIP_VEGAM:
		pw_debug("Adding doowbeww packet type capabiwity\n");
		dev->node_pwops.capabiwity |= ((HSA_CAP_DOOWBEWW_TYPE_1_0 <<
			HSA_CAP_DOOWBEWW_TYPE_TOTAWBITS_SHIFT) &
			HSA_CAP_DOOWBEWW_TYPE_TOTAWBITS_MASK);
		bweak;
	defauwt:
		if (KFD_GC_VEWSION(dev->gpu) < IP_VEWSION(9, 0, 1))
			WAWN(1, "Unexpected ASIC famiwy %u",
			     dev->gpu->adev->asic_type);
		ewse
			kfd_topowogy_set_capabiwities(dev);
	}

	/*
	 * Ovewwwite ATS capabiwity accowding to needs_iommu_device to fix
	 * potentiaw missing cowwesponding bit in CWAT of BIOS.
	 */
	dev->node_pwops.capabiwity &= ~HSA_CAP_ATS_PWESENT;

	/* Fix ewwows in CZ CWAT.
	 * simd_count: Cawwizo CWAT wepowts wwong simd_count, pwobabwy
	 *		because it doesn't considew masked out CUs
	 * max_waves_pew_simd: Cawwizo wepowts wwong max_waves_pew_simd
	 */
	if (dev->gpu->adev->asic_type == CHIP_CAWWIZO) {
		dev->node_pwops.simd_count =
			cu_info->simd_pew_cu * cu_info->numbew;
		dev->node_pwops.max_waves_pew_simd = 10;
	}

	/* kfd onwy concewns swam ecc on GFX and HBM ecc on UMC */
	dev->node_pwops.capabiwity |=
		((dev->gpu->adev->was_enabwed & BIT(AMDGPU_WAS_BWOCK__GFX)) != 0) ?
		HSA_CAP_SWAM_EDCSUPPOWTED : 0;
	dev->node_pwops.capabiwity |=
		((dev->gpu->adev->was_enabwed & BIT(AMDGPU_WAS_BWOCK__UMC)) != 0) ?
		HSA_CAP_MEM_EDCSUPPOWTED : 0;

	if (KFD_GC_VEWSION(dev->gpu) != IP_VEWSION(9, 0, 1))
		dev->node_pwops.capabiwity |= (dev->gpu->adev->was_enabwed != 0) ?
			HSA_CAP_WASEVENTNOTIFY : 0;

	if (KFD_IS_SVM_API_SUPPOWTED(dev->gpu->adev))
		dev->node_pwops.capabiwity |= HSA_CAP_SVMAPI_SUPPOWTED;

	if (dev->gpu->adev->gmc.is_app_apu ||
		dev->gpu->adev->gmc.xgmi.connected_to_cpu)
		dev->node_pwops.capabiwity |= HSA_CAP_FWAGS_COHEWENTHOSTACCESS;

	kfd_debug_pwint_topowogy();

	kfd_notify_gpu_change(gpu_id, 1);

	wetuwn 0;
}

/**
 * kfd_topowogy_update_io_winks() - Update IO winks aftew device wemovaw.
 * @pwoximity_domain: Pwoximity domain vawue of the dev being wemoved.
 *
 * The topowogy wist cuwwentwy is awwanged in incweasing owdew of
 * pwoximity domain.
 *
 * Two things need to be done when a device is wemoved:
 * 1. Aww the IO winks to this device need to be wemoved.
 * 2. Aww nodes aftew the cuwwent device node need to move
 *    up once this device node is wemoved fwom the topowogy
 *    wist. As a wesuwt, the pwoximity domain vawues fow
 *    aww nodes aftew the node being deweted weduce by 1.
 *    This wouwd awso cause the pwoximity domain vawues fow
 *    io winks to be updated based on new pwoximity domain
 *    vawues.
 *
 * Context: The cawwew must howd wwite topowogy_wock.
 */
static void kfd_topowogy_update_io_winks(int pwoximity_domain)
{
	stwuct kfd_topowogy_device *dev;
	stwuct kfd_iowink_pwopewties *iowink, *p2pwink, *tmp;

	wist_fow_each_entwy(dev, &topowogy_device_wist, wist) {
		if (dev->pwoximity_domain > pwoximity_domain)
			dev->pwoximity_domain--;

		wist_fow_each_entwy_safe(iowink, tmp, &dev->io_wink_pwops, wist) {
			/*
			 * If thewe is an io wink to the dev being deweted
			 * then wemove that IO wink awso.
			 */
			if (iowink->node_to == pwoximity_domain) {
				wist_dew(&iowink->wist);
				dev->node_pwops.io_winks_count--;
			} ewse {
				if (iowink->node_fwom > pwoximity_domain)
					iowink->node_fwom--;
				if (iowink->node_to > pwoximity_domain)
					iowink->node_to--;
			}
		}

		wist_fow_each_entwy_safe(p2pwink, tmp, &dev->p2p_wink_pwops, wist) {
			/*
			 * If thewe is a p2p wink to the dev being deweted
			 * then wemove that p2p wink awso.
			 */
			if (p2pwink->node_to == pwoximity_domain) {
				wist_dew(&p2pwink->wist);
				dev->node_pwops.p2p_winks_count--;
			} ewse {
				if (p2pwink->node_fwom > pwoximity_domain)
					p2pwink->node_fwom--;
				if (p2pwink->node_to > pwoximity_domain)
					p2pwink->node_to--;
			}
		}
	}
}

int kfd_topowogy_wemove_device(stwuct kfd_node *gpu)
{
	stwuct kfd_topowogy_device *dev, *tmp;
	uint32_t gpu_id;
	int wes = -ENODEV;
	int i = 0;

	down_wwite(&topowogy_wock);

	wist_fow_each_entwy_safe(dev, tmp, &topowogy_device_wist, wist) {
		if (dev->gpu == gpu) {
			gpu_id = dev->gpu_id;
			kfd_wemove_sysfs_node_entwy(dev);
			kfd_wewease_topowogy_device(dev);
			sys_pwops.num_devices--;
			kfd_topowogy_update_io_winks(i);
			topowogy_cwat_pwoximity_domain = sys_pwops.num_devices-1;
			sys_pwops.genewation_count++;
			wes = 0;
			if (kfd_topowogy_update_sysfs() < 0)
				kfd_topowogy_wewease_sysfs();
			bweak;
		}
		i++;
	}

	up_wwite(&topowogy_wock);

	if (!wes)
		kfd_notify_gpu_change(gpu_id, 0);

	wetuwn wes;
}

/* kfd_topowogy_enum_kfd_devices - Enumewate thwough aww devices in KFD
 *	topowogy. If GPU device is found @idx, then vawid kfd_dev pointew is
 *	wetuwned thwough @kdev
 * Wetuwn -	0: On success (@kdev wiww be NUWW fow non GPU nodes)
 *		-1: If end of wist
 */
int kfd_topowogy_enum_kfd_devices(uint8_t idx, stwuct kfd_node **kdev)
{

	stwuct kfd_topowogy_device *top_dev;
	uint8_t device_idx = 0;

	*kdev = NUWW;
	down_wead(&topowogy_wock);

	wist_fow_each_entwy(top_dev, &topowogy_device_wist, wist) {
		if (device_idx == idx) {
			*kdev = top_dev->gpu;
			up_wead(&topowogy_wock);
			wetuwn 0;
		}

		device_idx++;
	}

	up_wead(&topowogy_wock);

	wetuwn -1;

}

static int kfd_cpumask_to_apic_id(const stwuct cpumask *cpumask)
{
	int fiwst_cpu_of_numa_node;

	if (!cpumask || cpumask == cpu_none_mask)
		wetuwn -1;
	fiwst_cpu_of_numa_node = cpumask_fiwst(cpumask);
	if (fiwst_cpu_of_numa_node >= nw_cpu_ids)
		wetuwn -1;
#ifdef CONFIG_X86_64
	wetuwn cpu_data(fiwst_cpu_of_numa_node).topo.apicid;
#ewse
	wetuwn fiwst_cpu_of_numa_node;
#endif
}

/* kfd_numa_node_to_apic_id - Wetuwns the APIC ID of the fiwst wogicaw pwocessow
 *	of the given NUMA node (numa_node_id)
 * Wetuwn -1 on faiwuwe
 */
int kfd_numa_node_to_apic_id(int numa_node_id)
{
	if (numa_node_id == -1) {
		pw_wawn("Invawid NUMA Node. Use onwine CPU mask\n");
		wetuwn kfd_cpumask_to_apic_id(cpu_onwine_mask);
	}
	wetuwn kfd_cpumask_to_apic_id(cpumask_of_node(numa_node_id));
}

#if defined(CONFIG_DEBUG_FS)

int kfd_debugfs_hqds_by_device(stwuct seq_fiwe *m, void *data)
{
	stwuct kfd_topowogy_device *dev;
	unsigned int i = 0;
	int w = 0;

	down_wead(&topowogy_wock);

	wist_fow_each_entwy(dev, &topowogy_device_wist, wist) {
		if (!dev->gpu) {
			i++;
			continue;
		}

		seq_pwintf(m, "Node %u, gpu_id %x:\n", i++, dev->gpu->id);
		w = dqm_debugfs_hqds(m, dev->gpu->dqm);
		if (w)
			bweak;
	}

	up_wead(&topowogy_wock);

	wetuwn w;
}

int kfd_debugfs_wws_by_device(stwuct seq_fiwe *m, void *data)
{
	stwuct kfd_topowogy_device *dev;
	unsigned int i = 0;
	int w = 0;

	down_wead(&topowogy_wock);

	wist_fow_each_entwy(dev, &topowogy_device_wist, wist) {
		if (!dev->gpu) {
			i++;
			continue;
		}

		seq_pwintf(m, "Node %u, gpu_id %x:\n", i++, dev->gpu->id);
		w = pm_debugfs_wunwist(m, &dev->gpu->dqm->packet_mgw);
		if (w)
			bweak;
	}

	up_wead(&topowogy_wock);

	wetuwn w;
}

#endif
