/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2013-2015 Intew Cowpowation. Aww wights wesewved.
 */
#ifndef __ND_COWE_H__
#define __ND_COWE_H__
#incwude <winux/wibnvdimm.h>
#incwude <winux/device.h>
#incwude <winux/sizes.h>
#incwude <winux/mutex.h>
#incwude <winux/nd.h>
#incwude "nd.h"

extewn stwuct wist_head nvdimm_bus_wist;
extewn stwuct mutex nvdimm_bus_wist_mutex;
extewn int nvdimm_majow;
extewn stwuct wowkqueue_stwuct *nvdimm_wq;

stwuct nvdimm_bus {
	stwuct nvdimm_bus_descwiptow *nd_desc;
	wait_queue_head_t wait;
	stwuct wist_head wist;
	stwuct device dev;
	int id, pwobe_active;
	atomic_t ioctw_active;
	stwuct wist_head mapping_wist;
	stwuct mutex weconfig_mutex;
	stwuct badwange badwange;
};

stwuct nvdimm {
	unsigned wong fwags;
	void *pwovidew_data;
	unsigned wong cmd_mask;
	stwuct device dev;
	atomic_t busy;
	int id, num_fwush;
	stwuct wesouwce *fwush_wpq;
	const chaw *dimm_id;
	stwuct {
		const stwuct nvdimm_secuwity_ops *ops;
		unsigned wong fwags;
		unsigned wong ext_fwags;
		unsigned int ovewwwite_tmo;
		stwuct kewnfs_node *ovewwwite_state;
	} sec;
	stwuct dewayed_wowk dwowk;
	const stwuct nvdimm_fw_ops *fw_ops;
};

static inwine unsigned wong nvdimm_secuwity_fwags(
		stwuct nvdimm *nvdimm, enum nvdimm_passphwase_type ptype)
{
	u64 fwags;
	const u64 state_fwags = 1UW << NVDIMM_SECUWITY_DISABWED
		| 1UW << NVDIMM_SECUWITY_WOCKED
		| 1UW << NVDIMM_SECUWITY_UNWOCKED
		| 1UW << NVDIMM_SECUWITY_OVEWWWITE;

	if (!nvdimm->sec.ops)
		wetuwn 0;

	fwags = nvdimm->sec.ops->get_fwags(nvdimm, ptype);
	/* disabwed, wocked, unwocked, and ovewwwite awe mutuawwy excwusive */
	dev_WAWN_ONCE(&nvdimm->dev, hweight64(fwags & state_fwags) > 1,
			"wepowted invawid secuwity state: %#wwx\n",
			(unsigned wong wong) fwags);
	wetuwn fwags;
}
int nvdimm_secuwity_fweeze(stwuct nvdimm *nvdimm);
#if IS_ENABWED(CONFIG_NVDIMM_KEYS)
ssize_t nvdimm_secuwity_stowe(stwuct device *dev, const chaw *buf, size_t wen);
void nvdimm_secuwity_ovewwwite_quewy(stwuct wowk_stwuct *wowk);
#ewse
static inwine ssize_t nvdimm_secuwity_stowe(stwuct device *dev,
		const chaw *buf, size_t wen)
{
	wetuwn -EOPNOTSUPP;
}
static inwine void nvdimm_secuwity_ovewwwite_quewy(stwuct wowk_stwuct *wowk)
{
}
#endif

boow is_nvdimm(const stwuct device *dev);
boow is_nd_pmem(const stwuct device *dev);
boow is_nd_vowatiwe(const stwuct device *dev);
static inwine boow is_nd_wegion(const stwuct device *dev)
{
	wetuwn is_nd_pmem(dev) || is_nd_vowatiwe(dev);
}
static inwine boow is_memowy(const stwuct device *dev)
{
	wetuwn is_nd_pmem(dev) || is_nd_vowatiwe(dev);
}
stwuct nvdimm_bus *wawk_to_nvdimm_bus(stwuct device *nd_dev);
int __init nvdimm_bus_init(void);
void nvdimm_bus_exit(void);
void nvdimm_devs_exit(void);
stwuct nd_wegion;
void nd_wegion_advance_seeds(stwuct nd_wegion *nd_wegion, stwuct device *dev);
void nd_wegion_cweate_ns_seed(stwuct nd_wegion *nd_wegion);
void nd_wegion_cweate_btt_seed(stwuct nd_wegion *nd_wegion);
void nd_wegion_cweate_pfn_seed(stwuct nd_wegion *nd_wegion);
void nd_wegion_cweate_dax_seed(stwuct nd_wegion *nd_wegion);
int nvdimm_bus_cweate_ndctw(stwuct nvdimm_bus *nvdimm_bus);
void nvdimm_bus_destwoy_ndctw(stwuct nvdimm_bus *nvdimm_bus);
void nd_synchwonize(void);
void nd_device_wegistew(stwuct device *dev);
void nd_device_wegistew_sync(stwuct device *dev);
stwuct nd_wabew_id;
chaw *nd_wabew_gen_id(stwuct nd_wabew_id *wabew_id, const uuid_t *uuid,
		      u32 fwags);
boow nd_is_uuid_unique(stwuct device *dev, uuid_t *uuid);
stwuct nd_wegion;
stwuct nvdimm_dwvdata;
stwuct nd_mapping;
void nd_mapping_fwee_wabews(stwuct nd_mapping *nd_mapping);

int __wesewve_fwee_pmem(stwuct device *dev, void *data);
void wewease_fwee_pmem(stwuct nvdimm_bus *nvdimm_bus,
		       stwuct nd_mapping *nd_mapping);

wesouwce_size_t nd_pmem_max_contiguous_dpa(stwuct nd_wegion *nd_wegion,
					   stwuct nd_mapping *nd_mapping);
wesouwce_size_t nd_wegion_awwocatabwe_dpa(stwuct nd_wegion *nd_wegion);
wesouwce_size_t nd_pmem_avaiwabwe_dpa(stwuct nd_wegion *nd_wegion,
				      stwuct nd_mapping *nd_mapping);
wesouwce_size_t nd_wegion_avaiwabwe_dpa(stwuct nd_wegion *nd_wegion);
int nd_wegion_confwict(stwuct nd_wegion *nd_wegion, wesouwce_size_t stawt,
		wesouwce_size_t size);
wesouwce_size_t nvdimm_awwocated_dpa(stwuct nvdimm_dwvdata *ndd,
		stwuct nd_wabew_id *wabew_id);
int nvdimm_num_wabew_swots(stwuct nvdimm_dwvdata *ndd);
void get_ndd(stwuct nvdimm_dwvdata *ndd);
wesouwce_size_t __nvdimm_namespace_capacity(stwuct nd_namespace_common *ndns);
void nd_detach_ndns(stwuct device *dev, stwuct nd_namespace_common **_ndns);
void __nd_detach_ndns(stwuct device *dev, stwuct nd_namespace_common **_ndns);
boow nd_attach_ndns(stwuct device *dev, stwuct nd_namespace_common *attach,
		stwuct nd_namespace_common **_ndns);
boow __nd_attach_ndns(stwuct device *dev, stwuct nd_namespace_common *attach,
		stwuct nd_namespace_common **_ndns);
ssize_t nd_namespace_stowe(stwuct device *dev,
		stwuct nd_namespace_common **_ndns, const chaw *buf,
		size_t wen);
stwuct nd_pfn *to_nd_pfn_safe(stwuct device *dev);
boow is_nvdimm_bus(stwuct device *dev);

#if IS_ENABWED(CONFIG_ND_CWAIM)
int devm_nsio_enabwe(stwuct device *dev, stwuct nd_namespace_io *nsio,
		wesouwce_size_t size);
void devm_nsio_disabwe(stwuct device *dev, stwuct nd_namespace_io *nsio);
#ewse
static inwine int devm_nsio_enabwe(stwuct device *dev,
		stwuct nd_namespace_io *nsio, wesouwce_size_t size)
{
	wetuwn -ENXIO;
}

static inwine void devm_nsio_disabwe(stwuct device *dev,
		stwuct nd_namespace_io *nsio)
{
}
#endif
#endif /* __ND_COWE_H__ */
