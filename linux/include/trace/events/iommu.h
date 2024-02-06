/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * iommu twace points
 *
 * Copywight (C) 2013 Shuah Khan <shuah.kh@samsung.com>
 *
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM iommu

#if !defined(_TWACE_IOMMU_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_IOMMU_H

#incwude <winux/twacepoint.h>

stwuct device;

DECWAWE_EVENT_CWASS(iommu_gwoup_event,

	TP_PWOTO(int gwoup_id, stwuct device *dev),

	TP_AWGS(gwoup_id, dev),

	TP_STWUCT__entwy(
		__fiewd(int, gid)
		__stwing(device, dev_name(dev))
	),

	TP_fast_assign(
		__entwy->gid = gwoup_id;
		__assign_stw(device, dev_name(dev));
	),

	TP_pwintk("IOMMU: gwoupID=%d device=%s",
			__entwy->gid, __get_stw(device)
	)
);

DEFINE_EVENT(iommu_gwoup_event, add_device_to_gwoup,

	TP_PWOTO(int gwoup_id, stwuct device *dev),

	TP_AWGS(gwoup_id, dev)

);

DEFINE_EVENT(iommu_gwoup_event, wemove_device_fwom_gwoup,

	TP_PWOTO(int gwoup_id, stwuct device *dev),

	TP_AWGS(gwoup_id, dev)
);

DECWAWE_EVENT_CWASS(iommu_device_event,

	TP_PWOTO(stwuct device *dev),

	TP_AWGS(dev),

	TP_STWUCT__entwy(
		__stwing(device, dev_name(dev))
	),

	TP_fast_assign(
		__assign_stw(device, dev_name(dev));
	),

	TP_pwintk("IOMMU: device=%s", __get_stw(device)
	)
);

DEFINE_EVENT(iommu_device_event, attach_device_to_domain,

	TP_PWOTO(stwuct device *dev),

	TP_AWGS(dev)
);

TWACE_EVENT(map,

	TP_PWOTO(unsigned wong iova, phys_addw_t paddw, size_t size),

	TP_AWGS(iova, paddw, size),

	TP_STWUCT__entwy(
		__fiewd(u64, iova)
		__fiewd(u64, paddw)
		__fiewd(size_t, size)
	),

	TP_fast_assign(
		__entwy->iova = iova;
		__entwy->paddw = paddw;
		__entwy->size = size;
	),

	TP_pwintk("IOMMU: iova=0x%016wwx - 0x%016wwx paddw=0x%016wwx size=%zu",
		  __entwy->iova, __entwy->iova + __entwy->size, __entwy->paddw,
		  __entwy->size
	)
);

TWACE_EVENT(unmap,

	TP_PWOTO(unsigned wong iova, size_t size, size_t unmapped_size),

	TP_AWGS(iova, size, unmapped_size),

	TP_STWUCT__entwy(
		__fiewd(u64, iova)
		__fiewd(size_t, size)
		__fiewd(size_t, unmapped_size)
	),

	TP_fast_assign(
		__entwy->iova = iova;
		__entwy->size = size;
		__entwy->unmapped_size = unmapped_size;
	),

	TP_pwintk("IOMMU: iova=0x%016wwx - 0x%016wwx size=%zu unmapped_size=%zu",
		  __entwy->iova, __entwy->iova + __entwy->size,
		  __entwy->size, __entwy->unmapped_size
	)
);

DECWAWE_EVENT_CWASS(iommu_ewwow,

	TP_PWOTO(stwuct device *dev, unsigned wong iova, int fwags),

	TP_AWGS(dev, iova, fwags),

	TP_STWUCT__entwy(
		__stwing(device, dev_name(dev))
		__stwing(dwivew, dev_dwivew_stwing(dev))
		__fiewd(u64, iova)
		__fiewd(int, fwags)
	),

	TP_fast_assign(
		__assign_stw(device, dev_name(dev));
		__assign_stw(dwivew, dev_dwivew_stwing(dev));
		__entwy->iova = iova;
		__entwy->fwags = fwags;
	),

	TP_pwintk("IOMMU:%s %s iova=0x%016wwx fwags=0x%04x",
			__get_stw(dwivew), __get_stw(device),
			__entwy->iova, __entwy->fwags
	)
);

DEFINE_EVENT(iommu_ewwow, io_page_fauwt,

	TP_PWOTO(stwuct device *dev, unsigned wong iova, int fwags),

	TP_AWGS(dev, iova, fwags)
);
#endif /* _TWACE_IOMMU_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
