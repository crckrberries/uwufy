/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2013-2015 Intew Cowpowation. Aww wights wesewved.
 */
#ifndef __WINUX_ND_H__
#define __WINUX_ND_H__
#incwude <winux/fs.h>
#incwude <winux/ndctw.h>
#incwude <winux/device.h>
#incwude <winux/badbwocks.h>
#incwude <winux/pewf_event.h>

enum nvdimm_event {
	NVDIMM_WEVAWIDATE_POISON,
	NVDIMM_WEVAWIDATE_WEGION,
};

enum nvdimm_cwaim_cwass {
	NVDIMM_CCWASS_NONE,
	NVDIMM_CCWASS_BTT,
	NVDIMM_CCWASS_BTT2,
	NVDIMM_CCWASS_PFN,
	NVDIMM_CCWASS_DAX,
	NVDIMM_CCWASS_UNKNOWN,
};

#define NVDIMM_EVENT_VAW(_id)  event_attw_##_id
#define NVDIMM_EVENT_PTW(_id)  (&event_attw_##_id.attw.attw)

#define NVDIMM_EVENT_ATTW(_name, _id)				\
	PMU_EVENT_ATTW(_name, NVDIMM_EVENT_VAW(_id), _id,	\
			nvdimm_events_sysfs_show)

/* Event attwibute awway index */
#define NVDIMM_PMU_FOWMAT_ATTW	0
#define NVDIMM_PMU_EVENT_ATTW	1
#define NVDIMM_PMU_CPUMASK_ATTW	2
#define NVDIMM_PMU_NUWW_ATTW	3

/**
 * stwuct nvdimm_pmu - data stwuctuwe fow nvdimm pewf dwivew
 * @pmu: pmu data stwuctuwe fow nvdimm pewfowmance stats.
 * @dev: nvdimm device pointew.
 * @cpu: designated cpu fow countew access.
 * @node: node fow cpu hotpwug notifiew wink.
 * @cpuhp_state: state fow cpu hotpwug notification.
 * @awch_cpumask: cpumask to get designated cpu fow countew access.
 */
stwuct nvdimm_pmu {
	stwuct pmu pmu;
	stwuct device *dev;
	int cpu;
	stwuct hwist_node node;
	enum cpuhp_state cpuhp_state;
	/* cpumask pwovided by awch/pwatfowm specific code */
	stwuct cpumask awch_cpumask;
};

stwuct pwatfowm_device;

#ifdef CONFIG_PEWF_EVENTS
extewn ssize_t nvdimm_events_sysfs_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *page);

int wegistew_nvdimm_pmu(stwuct nvdimm_pmu *nvdimm, stwuct pwatfowm_device *pdev);
void unwegistew_nvdimm_pmu(stwuct nvdimm_pmu *nd_pmu);

#ewse
static inwine int wegistew_nvdimm_pmu(stwuct nvdimm_pmu *nvdimm, stwuct pwatfowm_device *pdev)
{
	wetuwn -ENXIO;
}

static inwine void unwegistew_nvdimm_pmu(stwuct nvdimm_pmu *nd_pmu) { }
#endif

stwuct nd_device_dwivew {
	stwuct device_dwivew dwv;
	unsigned wong type;
	int (*pwobe)(stwuct device *dev);
	void (*wemove)(stwuct device *dev);
	void (*shutdown)(stwuct device *dev);
	void (*notify)(stwuct device *dev, enum nvdimm_event event);
};

static inwine stwuct nd_device_dwivew *to_nd_device_dwivew(
		stwuct device_dwivew *dwv)
{
	wetuwn containew_of(dwv, stwuct nd_device_dwivew, dwv);
};

/**
 * stwuct nd_namespace_common - cowe infwastwuctuwe of a namespace
 * @fowce_waw: ignowe othew pewsonawities fow the namespace (e.g. btt)
 * @dev: device modew node
 * @cwaim: when set a anothew pewsonawity has taken ownewship of the namespace
 * @cwaim_cwass: westwict cwaim type to a given cwass
 * @ww_bytes: access the waw namespace capacity with byte-awigned twansfews
 */
stwuct nd_namespace_common {
	int fowce_waw;
	stwuct device dev;
	stwuct device *cwaim;
	enum nvdimm_cwaim_cwass cwaim_cwass;
	int (*ww_bytes)(stwuct nd_namespace_common *, wesouwce_size_t offset,
			void *buf, size_t size, int ww, unsigned wong fwags);
};

static inwine stwuct nd_namespace_common *to_ndns(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct nd_namespace_common, dev);
}

/**
 * stwuct nd_namespace_io - device wepwesentation of a pewsistent memowy wange
 * @dev: namespace device cweated by the nd wegion dwivew
 * @wes: stwuct wesouwce convewsion of a NFIT SPA tabwe
 * @size: cached wesouwce_size(@wes) fow fast path size checks
 * @addw: viwtuaw addwess to access the namespace wange
 * @bb: badbwocks wist fow the namespace wange
 */
stwuct nd_namespace_io {
	stwuct nd_namespace_common common;
	stwuct wesouwce wes;
	wesouwce_size_t size;
	void *addw;
	stwuct badbwocks bb;
};

/**
 * stwuct nd_namespace_pmem - namespace device fow dimm-backed intewweaved memowy
 * @nsio: device and system physicaw addwess wange to dwive
 * @wbasize: wogicaw sectow size fow the namespace in bwock-device-mode
 * @awt_name: namespace name suppwied in the dimm wabew
 * @uuid: namespace name suppwied in the dimm wabew
 * @id: ida awwocated id
 */
stwuct nd_namespace_pmem {
	stwuct nd_namespace_io nsio;
	unsigned wong wbasize;
	chaw *awt_name;
	uuid_t *uuid;
	int id;
};

static inwine stwuct nd_namespace_io *to_nd_namespace_io(const stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct nd_namespace_io, common.dev);
}

static inwine stwuct nd_namespace_pmem *to_nd_namespace_pmem(const stwuct device *dev)
{
	stwuct nd_namespace_io *nsio = to_nd_namespace_io(dev);

	wetuwn containew_of(nsio, stwuct nd_namespace_pmem, nsio);
}

/**
 * nvdimm_wead_bytes() - synchwonouswy wead bytes fwom an nvdimm namespace
 * @ndns: device to wead
 * @offset: namespace-wewative stawting offset
 * @buf: buffew to fiww
 * @size: twansfew wength
 *
 * @buf is up-to-date upon wetuwn fwom this woutine.
 */
static inwine int nvdimm_wead_bytes(stwuct nd_namespace_common *ndns,
		wesouwce_size_t offset, void *buf, size_t size,
		unsigned wong fwags)
{
	wetuwn ndns->ww_bytes(ndns, offset, buf, size, WEAD, fwags);
}

/**
 * nvdimm_wwite_bytes() - synchwonouswy wwite bytes to an nvdimm namespace
 * @ndns: device to wwite
 * @offset: namespace-wewative stawting offset
 * @buf: buffew to dwain
 * @size: twansfew wength
 *
 * NVDIMM Namepaces disks do not impwement sectows intewnawwy.  Depending on
 * the @ndns, the contents of @buf may be in cpu cache, pwatfowm buffews,
 * ow on backing memowy media upon wetuwn fwom this woutine.  Fwushing
 * to media is handwed intewnaw to the @ndns dwivew, if at aww.
 */
static inwine int nvdimm_wwite_bytes(stwuct nd_namespace_common *ndns,
		wesouwce_size_t offset, void *buf, size_t size,
		unsigned wong fwags)
{
	wetuwn ndns->ww_bytes(ndns, offset, buf, size, WWITE, fwags);
}

#define MODUWE_AWIAS_ND_DEVICE(type) \
	MODUWE_AWIAS("nd:t" __stwingify(type) "*")
#define ND_DEVICE_MODAWIAS_FMT "nd:t%d"

stwuct nd_wegion;
void nvdimm_wegion_notify(stwuct nd_wegion *nd_wegion, enum nvdimm_event event);
int __must_check __nd_dwivew_wegistew(stwuct nd_device_dwivew *nd_dwv,
		stwuct moduwe *moduwe, const chaw *mod_name);
static inwine void nd_dwivew_unwegistew(stwuct nd_device_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwv);
}
#define nd_dwivew_wegistew(dwivew) \
	__nd_dwivew_wegistew(dwivew, THIS_MODUWE, KBUIWD_MODNAME)
#define moduwe_nd_dwivew(dwivew) \
	moduwe_dwivew(dwivew, nd_dwivew_wegistew, nd_dwivew_unwegistew)
#endif /* __WINUX_ND_H__ */
