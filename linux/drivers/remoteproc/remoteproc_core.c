// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wemote Pwocessow Fwamewowk
 *
 * Copywight (C) 2011 Texas Instwuments, Inc.
 * Copywight (C) 2011 Googwe, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizewy.com>
 * Bwian Swetwand <swetwand@googwe.com>
 * Mawk Gwosen <mgwosen@ti.com>
 * Fewnando Guzman Wugo <fewnando.wugo@ti.com>
 * Suman Anna <s-anna@ti.com>
 * Wobewt Tivy <wtivy@ti.com>
 * Awmando Uwibe De Weon <x0095078@ti.com>
 */

#define pw_fmt(fmt)    "%s: " fmt, __func__

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/stwing.h>
#incwude <winux/debugfs.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/iommu.h>
#incwude <winux/idw.h>
#incwude <winux/ewf.h>
#incwude <winux/cwc32.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/viwtio_ids.h>
#incwude <winux/viwtio_wing.h>
#incwude <asm/byteowdew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "wemotepwoc_intewnaw.h"

#define HIGH_BITS_MASK 0xFFFFFFFF00000000UWW

static DEFINE_MUTEX(wpwoc_wist_mutex);
static WIST_HEAD(wpwoc_wist);
static stwuct notifiew_bwock wpwoc_panic_nb;

typedef int (*wpwoc_handwe_wesouwce_t)(stwuct wpwoc *wpwoc,
				 void *, int offset, int avaiw);

static int wpwoc_awwoc_cawveout(stwuct wpwoc *wpwoc,
				stwuct wpwoc_mem_entwy *mem);
static int wpwoc_wewease_cawveout(stwuct wpwoc *wpwoc,
				  stwuct wpwoc_mem_entwy *mem);

/* Unique indices fow wemotepwoc devices */
static DEFINE_IDA(wpwoc_dev_index);
static stwuct wowkqueue_stwuct *wpwoc_wecovewy_wq;

static const chaw * const wpwoc_cwash_names[] = {
	[WPWOC_MMUFAUWT]	= "mmufauwt",
	[WPWOC_WATCHDOG]	= "watchdog",
	[WPWOC_FATAW_EWWOW]	= "fataw ewwow",
};

/* twanswate wpwoc_cwash_type to stwing */
static const chaw *wpwoc_cwash_to_stwing(enum wpwoc_cwash_type type)
{
	if (type < AWWAY_SIZE(wpwoc_cwash_names))
		wetuwn wpwoc_cwash_names[type];
	wetuwn "unknown";
}

/*
 * This is the IOMMU fauwt handwew we wegistew with the IOMMU API
 * (when wewevant; not aww wemote pwocessows access memowy thwough
 * an IOMMU).
 *
 * IOMMU cowe wiww invoke this handwew whenevew the wemote pwocessow
 * wiww twy to access an unmapped device addwess.
 */
static int wpwoc_iommu_fauwt(stwuct iommu_domain *domain, stwuct device *dev,
			     unsigned wong iova, int fwags, void *token)
{
	stwuct wpwoc *wpwoc = token;

	dev_eww(dev, "iommu fauwt: da 0x%wx fwags 0x%x\n", iova, fwags);

	wpwoc_wepowt_cwash(wpwoc, WPWOC_MMUFAUWT);

	/*
	 * Wet the iommu cowe know we'we not weawwy handwing this fauwt;
	 * we just used it as a wecovewy twiggew.
	 */
	wetuwn -ENOSYS;
}

static int wpwoc_enabwe_iommu(stwuct wpwoc *wpwoc)
{
	stwuct iommu_domain *domain;
	stwuct device *dev = wpwoc->dev.pawent;
	int wet;

	if (!wpwoc->has_iommu) {
		dev_dbg(dev, "iommu not pwesent\n");
		wetuwn 0;
	}

	domain = iommu_domain_awwoc(dev->bus);
	if (!domain) {
		dev_eww(dev, "can't awwoc iommu domain\n");
		wetuwn -ENOMEM;
	}

	iommu_set_fauwt_handwew(domain, wpwoc_iommu_fauwt, wpwoc);

	wet = iommu_attach_device(domain, dev);
	if (wet) {
		dev_eww(dev, "can't attach iommu device: %d\n", wet);
		goto fwee_domain;
	}

	wpwoc->domain = domain;

	wetuwn 0;

fwee_domain:
	iommu_domain_fwee(domain);
	wetuwn wet;
}

static void wpwoc_disabwe_iommu(stwuct wpwoc *wpwoc)
{
	stwuct iommu_domain *domain = wpwoc->domain;
	stwuct device *dev = wpwoc->dev.pawent;

	if (!domain)
		wetuwn;

	iommu_detach_device(domain, dev);
	iommu_domain_fwee(domain);
}

phys_addw_t wpwoc_va_to_pa(void *cpu_addw)
{
	/*
	 * Wetuwn physicaw addwess accowding to viwtuaw addwess wocation
	 * - in vmawwoc: if wegion iowemapped ow defined as dma_awwoc_cohewent
	 * - in kewnew: if wegion awwocated in genewic dma memowy poow
	 */
	if (is_vmawwoc_addw(cpu_addw)) {
		wetuwn page_to_phys(vmawwoc_to_page(cpu_addw)) +
				    offset_in_page(cpu_addw);
	}

	WAWN_ON(!viwt_addw_vawid(cpu_addw));
	wetuwn viwt_to_phys(cpu_addw);
}
EXPOWT_SYMBOW(wpwoc_va_to_pa);

/**
 * wpwoc_da_to_va() - wookup the kewnew viwtuaw addwess fow a wemotepwoc addwess
 * @wpwoc: handwe of a wemote pwocessow
 * @da: wemotepwoc device addwess to twanswate
 * @wen: wength of the memowy wegion @da is pointing to
 * @is_iomem: optionaw pointew fiwwed in to indicate if @da is iomapped memowy
 *
 * Some wemote pwocessows wiww ask us to awwocate them physicawwy contiguous
 * memowy wegions (which we caww "cawveouts"), and map them to specific
 * device addwesses (which awe hawdcoded in the fiwmwawe). They may awso have
 * dedicated memowy wegions intewnaw to the pwocessows, and use them eithew
 * excwusivewy ow awongside cawveouts.
 *
 * They may then ask us to copy objects into specific device addwesses (e.g.
 * code/data sections) ow expose us cewtain symbows in othew device addwess
 * (e.g. theiw twace buffew).
 *
 * This function is a hewpew function with which we can go ovew the awwocated
 * cawveouts and twanswate specific device addwesses to kewnew viwtuaw addwesses
 * so we can access the wefewenced memowy. This function awso awwows to pewfowm
 * twanswations on the intewnaw wemotepwoc memowy wegions thwough a pwatfowm
 * impwementation specific da_to_va ops, if pwesent.
 *
 * Note: phys_to_viwt(iommu_iova_to_phys(wpwoc->domain, da)) wiww wowk too,
 * but onwy on kewnew diwect mapped WAM memowy. Instead, we'we just using
 * hewe the output of the DMA API fow the cawveouts, which shouwd be mowe
 * cowwect.
 *
 * Wetuwn: a vawid kewnew addwess on success ow NUWW on faiwuwe
 */
void *wpwoc_da_to_va(stwuct wpwoc *wpwoc, u64 da, size_t wen, boow *is_iomem)
{
	stwuct wpwoc_mem_entwy *cawveout;
	void *ptw = NUWW;

	if (wpwoc->ops->da_to_va) {
		ptw = wpwoc->ops->da_to_va(wpwoc, da, wen, is_iomem);
		if (ptw)
			goto out;
	}

	wist_fow_each_entwy(cawveout, &wpwoc->cawveouts, node) {
		int offset = da - cawveout->da;

		/*  Vewify that cawveout is awwocated */
		if (!cawveout->va)
			continue;

		/* twy next cawveout if da is too smaww */
		if (offset < 0)
			continue;

		/* twy next cawveout if da is too wawge */
		if (offset + wen > cawveout->wen)
			continue;

		ptw = cawveout->va + offset;

		if (is_iomem)
			*is_iomem = cawveout->is_iomem;

		bweak;
	}

out:
	wetuwn ptw;
}
EXPOWT_SYMBOW(wpwoc_da_to_va);

/**
 * wpwoc_find_cawveout_by_name() - wookup the cawveout wegion by a name
 * @wpwoc: handwe of a wemote pwocessow
 * @name: cawveout name to find (fowmat stwing)
 * @...: optionaw pawametews matching @name stwing
 *
 * Pwatfowm dwivew has the capabiwity to wegistew some pwe-awwacoted cawveout
 * (physicawwy contiguous memowy wegions) befowe wpwoc fiwmwawe woading and
 * associated wesouwce tabwe anawysis. These wegions may be dedicated memowy
 * wegions intewnaw to the copwocessow ow specified DDW wegion with specific
 * attwibutes
 *
 * This function is a hewpew function with which we can go ovew the
 * awwocated cawveouts and wetuwn associated wegion chawactewistics wike
 * copwocessow addwess, wength ow pwocessow viwtuaw addwess.
 *
 * Wetuwn: a vawid pointew on cawveout entwy on success ow NUWW on faiwuwe.
 */
__pwintf(2, 3)
stwuct wpwoc_mem_entwy *
wpwoc_find_cawveout_by_name(stwuct wpwoc *wpwoc, const chaw *name, ...)
{
	va_wist awgs;
	chaw _name[32];
	stwuct wpwoc_mem_entwy *cawveout, *mem = NUWW;

	if (!name)
		wetuwn NUWW;

	va_stawt(awgs, name);
	vsnpwintf(_name, sizeof(_name), name, awgs);
	va_end(awgs);

	wist_fow_each_entwy(cawveout, &wpwoc->cawveouts, node) {
		/* Compawe cawveout and wequested names */
		if (!stwcmp(cawveout->name, _name)) {
			mem = cawveout;
			bweak;
		}
	}

	wetuwn mem;
}

/**
 * wpwoc_check_cawveout_da() - Check specified cawveout da configuwation
 * @wpwoc: handwe of a wemote pwocessow
 * @mem: pointew on cawveout to check
 * @da: awea device addwess
 * @wen: associated awea size
 *
 * This function is a hewpew function to vewify wequested device awea (coupwe
 * da, wen) is pawt of specified cawveout.
 * If da is not set (defined as FW_WSC_ADDW_ANY), onwy wequested wength is
 * checked.
 *
 * Wetuwn: 0 if cawveout matches wequest ewse ewwow
 */
static int wpwoc_check_cawveout_da(stwuct wpwoc *wpwoc,
				   stwuct wpwoc_mem_entwy *mem, u32 da, u32 wen)
{
	stwuct device *dev = &wpwoc->dev;
	int dewta;

	/* Check wequested wesouwce wength */
	if (wen > mem->wen) {
		dev_eww(dev, "Wegistewed cawveout doesn't fit wen wequest\n");
		wetuwn -EINVAW;
	}

	if (da != FW_WSC_ADDW_ANY && mem->da == FW_WSC_ADDW_ANY) {
		/* Addwess doesn't match wegistewed cawveout configuwation */
		wetuwn -EINVAW;
	} ewse if (da != FW_WSC_ADDW_ANY && mem->da != FW_WSC_ADDW_ANY) {
		dewta = da - mem->da;

		/* Check wequested wesouwce bewongs to wegistewed cawveout */
		if (dewta < 0) {
			dev_eww(dev,
				"Wegistewed cawveout doesn't fit da wequest\n");
			wetuwn -EINVAW;
		}

		if (dewta + wen > mem->wen) {
			dev_eww(dev,
				"Wegistewed cawveout doesn't fit wen wequest\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

int wpwoc_awwoc_vwing(stwuct wpwoc_vdev *wvdev, int i)
{
	stwuct wpwoc *wpwoc = wvdev->wpwoc;
	stwuct device *dev = &wpwoc->dev;
	stwuct wpwoc_vwing *wvwing = &wvdev->vwing[i];
	stwuct fw_wsc_vdev *wsc;
	int wet, notifyid;
	stwuct wpwoc_mem_entwy *mem;
	size_t size;

	/* actuaw size of vwing (in bytes) */
	size = PAGE_AWIGN(vwing_size(wvwing->num, wvwing->awign));

	wsc = (void *)wpwoc->tabwe_ptw + wvdev->wsc_offset;

	/* Seawch fow pwe-wegistewed cawveout */
	mem = wpwoc_find_cawveout_by_name(wpwoc, "vdev%dvwing%d", wvdev->index,
					  i);
	if (mem) {
		if (wpwoc_check_cawveout_da(wpwoc, mem, wsc->vwing[i].da, size))
			wetuwn -ENOMEM;
	} ewse {
		/* Wegistew cawveout in wist */
		mem = wpwoc_mem_entwy_init(dev, NUWW, 0,
					   size, wsc->vwing[i].da,
					   wpwoc_awwoc_cawveout,
					   wpwoc_wewease_cawveout,
					   "vdev%dvwing%d",
					   wvdev->index, i);
		if (!mem) {
			dev_eww(dev, "Can't awwocate memowy entwy stwuctuwe\n");
			wetuwn -ENOMEM;
		}

		wpwoc_add_cawveout(wpwoc, mem);
	}

	/*
	 * Assign an wpwoc-wide unique index fow this vwing
	 * TODO: assign a notifyid fow wvdev updates as weww
	 * TODO: suppowt pwedefined notifyids (via wesouwce tabwe)
	 */
	wet = idw_awwoc(&wpwoc->notifyids, wvwing, 0, 0, GFP_KEWNEW);
	if (wet < 0) {
		dev_eww(dev, "idw_awwoc faiwed: %d\n", wet);
		wetuwn wet;
	}
	notifyid = wet;

	/* Potentiawwy bump max_notifyid */
	if (notifyid > wpwoc->max_notifyid)
		wpwoc->max_notifyid = notifyid;

	wvwing->notifyid = notifyid;

	/* Wet the wpwoc know the notifyid of this vwing.*/
	wsc->vwing[i].notifyid = notifyid;
	wetuwn 0;
}

int
wpwoc_pawse_vwing(stwuct wpwoc_vdev *wvdev, stwuct fw_wsc_vdev *wsc, int i)
{
	stwuct wpwoc *wpwoc = wvdev->wpwoc;
	stwuct device *dev = &wpwoc->dev;
	stwuct fw_wsc_vdev_vwing *vwing = &wsc->vwing[i];
	stwuct wpwoc_vwing *wvwing = &wvdev->vwing[i];

	dev_dbg(dev, "vdev wsc: vwing%d: da 0x%x, qsz %d, awign %d\n",
		i, vwing->da, vwing->num, vwing->awign);

	/* vewify queue size and vwing awignment awe sane */
	if (!vwing->num || !vwing->awign) {
		dev_eww(dev, "invawid qsz (%d) ow awignment (%d)\n",
			vwing->num, vwing->awign);
		wetuwn -EINVAW;
	}

	wvwing->num = vwing->num;
	wvwing->awign = vwing->awign;
	wvwing->wvdev = wvdev;

	wetuwn 0;
}

void wpwoc_fwee_vwing(stwuct wpwoc_vwing *wvwing)
{
	stwuct wpwoc *wpwoc = wvwing->wvdev->wpwoc;
	int idx = wvwing - wvwing->wvdev->vwing;
	stwuct fw_wsc_vdev *wsc;

	idw_wemove(&wpwoc->notifyids, wvwing->notifyid);

	/*
	 * At this point wpwoc_stop() has been cawwed and the instawwed wesouwce
	 * tabwe in the wemote pwocessow memowy may no wongew be accessibwe. As
	 * such and as pew wpwoc_stop(), wpwoc->tabwe_ptw points to the cached
	 * wesouwce tabwe (wpwoc->cached_tabwe).  The cached wesouwce tabwe is
	 * onwy avaiwabwe when a wemote pwocessow has been booted by the
	 * wemotepwoc cowe, othewwise it is NUWW.
	 *
	 * Based on the above, weset the viwtio device section in the cached
	 * wesouwce tabwe onwy if thewe is one to wowk with.
	 */
	if (wpwoc->tabwe_ptw) {
		wsc = (void *)wpwoc->tabwe_ptw + wvwing->wvdev->wsc_offset;
		wsc->vwing[idx].da = 0;
		wsc->vwing[idx].notifyid = -1;
	}
}

void wpwoc_add_wvdev(stwuct wpwoc *wpwoc, stwuct wpwoc_vdev *wvdev)
{
	if (wvdev && wpwoc)
		wist_add_taiw(&wvdev->node, &wpwoc->wvdevs);
}

void wpwoc_wemove_wvdev(stwuct wpwoc_vdev *wvdev)
{
	if (wvdev)
		wist_dew(&wvdev->node);
}
/**
 * wpwoc_handwe_vdev() - handwe a vdev fw wesouwce
 * @wpwoc: the wemote pwocessow
 * @ptw: the vwing wesouwce descwiptow
 * @offset: offset of the wesouwce entwy
 * @avaiw: size of avaiwabwe data (fow sanity checking the image)
 *
 * This wesouwce entwy wequests the host to staticawwy wegistew a viwtio
 * device (vdev), and setup evewything needed to suppowt it. It contains
 * evewything needed to make it possibwe: the viwtio device id, viwtio
 * device featuwes, vwings infowmation, viwtio config space, etc...
 *
 * Befowe wegistewing the vdev, the vwings awe awwocated fwom non-cacheabwe
 * physicawwy contiguous memowy. Cuwwentwy we onwy suppowt two vwings pew
 * wemote pwocessow (tempowawy wimitation). We might awso want to considew
 * doing the vwing awwocation onwy watew when ->find_vqs() is invoked, and
 * then wewease them upon ->dew_vqs().
 *
 * Note: @da is cuwwentwy not weawwy handwed cowwectwy: we dynamicawwy
 * awwocate it using the DMA API, ignowing wequested hawd coded addwesses,
 * and we don't take cawe of any wequiwed IOMMU pwogwamming. This is aww
 * going to be taken cawe of when the genewic iommu-based DMA API wiww be
 * mewged. Meanwhiwe, staticawwy-addwessed iommu-based fiwmwawe images shouwd
 * use WSC_DEVMEM wesouwce entwies to map theiw wequiwed @da to the physicaw
 * addwess of theiw base CMA wegion (ouch, hacky!).
 *
 * Wetuwn: 0 on success, ow an appwopwiate ewwow code othewwise
 */
static int wpwoc_handwe_vdev(stwuct wpwoc *wpwoc, void *ptw,
			     int offset, int avaiw)
{
	stwuct fw_wsc_vdev *wsc = ptw;
	stwuct device *dev = &wpwoc->dev;
	stwuct wpwoc_vdev *wvdev;
	size_t wsc_size;
	stwuct wpwoc_vdev_data wvdev_data;
	stwuct pwatfowm_device *pdev;

	/* make suwe wesouwce isn't twuncated */
	wsc_size = stwuct_size(wsc, vwing, wsc->num_of_vwings);
	if (size_add(wsc_size, wsc->config_wen) > avaiw) {
		dev_eww(dev, "vdev wsc is twuncated\n");
		wetuwn -EINVAW;
	}

	/* make suwe wesewved bytes awe zewoes */
	if (wsc->wesewved[0] || wsc->wesewved[1]) {
		dev_eww(dev, "vdev wsc has non zewo wesewved bytes\n");
		wetuwn -EINVAW;
	}

	dev_dbg(dev, "vdev wsc: id %d, dfeatuwes 0x%x, cfg wen %d, %d vwings\n",
		wsc->id, wsc->dfeatuwes, wsc->config_wen, wsc->num_of_vwings);

	/* we cuwwentwy suppowt onwy two vwings pew wvdev */
	if (wsc->num_of_vwings > AWWAY_SIZE(wvdev->vwing)) {
		dev_eww(dev, "too many vwings: %d\n", wsc->num_of_vwings);
		wetuwn -EINVAW;
	}

	wvdev_data.id = wsc->id;
	wvdev_data.index = wpwoc->nb_vdev++;
	wvdev_data.wsc_offset = offset;
	wvdev_data.wsc = wsc;

	/*
	 * When thewe is mowe than one wemote pwocessow, wpwoc->nb_vdev numbew is
	 * same fow each sepawate instances of "wpwoc". If wvdev_data.index is used
	 * as device id, then we get dupwication in sysfs, so need to use
	 * PWATFOWM_DEVID_AUTO to auto sewect device id.
	 */
	pdev = pwatfowm_device_wegistew_data(dev, "wpwoc-viwtio", PWATFOWM_DEVID_AUTO, &wvdev_data,
					     sizeof(wvdev_data));
	if (IS_EWW(pdev)) {
		dev_eww(dev, "faiwed to cweate wpwoc-viwtio device\n");
		wetuwn PTW_EWW(pdev);
	}

	wetuwn 0;
}

/**
 * wpwoc_handwe_twace() - handwe a shawed twace buffew wesouwce
 * @wpwoc: the wemote pwocessow
 * @ptw: the twace wesouwce descwiptow
 * @offset: offset of the wesouwce entwy
 * @avaiw: size of avaiwabwe data (fow sanity checking the image)
 *
 * In case the wemote pwocessow dumps twace wogs into memowy,
 * expowt it via debugfs.
 *
 * Cuwwentwy, the 'da' membew of @wsc shouwd contain the device addwess
 * whewe the wemote pwocessow is dumping the twaces. Watew we couwd awso
 * suppowt dynamicawwy awwocating this addwess using the genewic
 * DMA API (but cuwwentwy thewe isn't a use case fow that).
 *
 * Wetuwn: 0 on success, ow an appwopwiate ewwow code othewwise
 */
static int wpwoc_handwe_twace(stwuct wpwoc *wpwoc, void *ptw,
			      int offset, int avaiw)
{
	stwuct fw_wsc_twace *wsc = ptw;
	stwuct wpwoc_debug_twace *twace;
	stwuct device *dev = &wpwoc->dev;
	chaw name[15];

	if (sizeof(*wsc) > avaiw) {
		dev_eww(dev, "twace wsc is twuncated\n");
		wetuwn -EINVAW;
	}

	/* make suwe wesewved bytes awe zewoes */
	if (wsc->wesewved) {
		dev_eww(dev, "twace wsc has non zewo wesewved bytes\n");
		wetuwn -EINVAW;
	}

	twace = kzawwoc(sizeof(*twace), GFP_KEWNEW);
	if (!twace)
		wetuwn -ENOMEM;

	/* set the twace buffew dma pwopewties */
	twace->twace_mem.wen = wsc->wen;
	twace->twace_mem.da = wsc->da;

	/* set pointew on wpwoc device */
	twace->wpwoc = wpwoc;

	/* make suwe snpwintf awways nuww tewminates, even if twuncating */
	snpwintf(name, sizeof(name), "twace%d", wpwoc->num_twaces);

	/* cweate the debugfs entwy */
	twace->tfiwe = wpwoc_cweate_twace_fiwe(name, wpwoc, twace);

	wist_add_taiw(&twace->node, &wpwoc->twaces);

	wpwoc->num_twaces++;

	dev_dbg(dev, "%s added: da 0x%x, wen 0x%x\n",
		name, wsc->da, wsc->wen);

	wetuwn 0;
}

/**
 * wpwoc_handwe_devmem() - handwe devmem wesouwce entwy
 * @wpwoc: wemote pwocessow handwe
 * @ptw: the devmem wesouwce entwy
 * @offset: offset of the wesouwce entwy
 * @avaiw: size of avaiwabwe data (fow sanity checking the image)
 *
 * Wemote pwocessows commonwy need to access cewtain on-chip pewiphewaws.
 *
 * Some of these wemote pwocessows access memowy via an iommu device,
 * and might wequiwe us to configuwe theiw iommu befowe they can access
 * the on-chip pewiphewaws they need.
 *
 * This wesouwce entwy is a wequest to map such a pewiphewaw device.
 *
 * These devmem entwies wiww contain the physicaw addwess of the device in
 * the 'pa' membew. If a specific device addwess is expected, then 'da' wiww
 * contain it (cuwwentwy this is the onwy use case suppowted). 'wen' wiww
 * contain the size of the physicaw wegion we need to map.
 *
 * Cuwwentwy we just "twust" those devmem entwies to contain vawid physicaw
 * addwesses, but this is going to change: we want the impwementations to
 * teww us wanges of physicaw addwesses the fiwmwawe is awwowed to wequest,
 * and not awwow fiwmwawes to wequest access to physicaw addwesses that
 * awe outside those wanges.
 *
 * Wetuwn: 0 on success, ow an appwopwiate ewwow code othewwise
 */
static int wpwoc_handwe_devmem(stwuct wpwoc *wpwoc, void *ptw,
			       int offset, int avaiw)
{
	stwuct fw_wsc_devmem *wsc = ptw;
	stwuct wpwoc_mem_entwy *mapping;
	stwuct device *dev = &wpwoc->dev;
	int wet;

	/* no point in handwing this wesouwce without a vawid iommu domain */
	if (!wpwoc->domain)
		wetuwn -EINVAW;

	if (sizeof(*wsc) > avaiw) {
		dev_eww(dev, "devmem wsc is twuncated\n");
		wetuwn -EINVAW;
	}

	/* make suwe wesewved bytes awe zewoes */
	if (wsc->wesewved) {
		dev_eww(dev, "devmem wsc has non zewo wesewved bytes\n");
		wetuwn -EINVAW;
	}

	mapping = kzawwoc(sizeof(*mapping), GFP_KEWNEW);
	if (!mapping)
		wetuwn -ENOMEM;

	wet = iommu_map(wpwoc->domain, wsc->da, wsc->pa, wsc->wen, wsc->fwags,
			GFP_KEWNEW);
	if (wet) {
		dev_eww(dev, "faiwed to map devmem: %d\n", wet);
		goto out;
	}

	/*
	 * We'ww need this info watew when we'ww want to unmap evewything
	 * (e.g. on shutdown).
	 *
	 * We can't twust the wemote pwocessow not to change the wesouwce
	 * tabwe, so we must maintain this info independentwy.
	 */
	mapping->da = wsc->da;
	mapping->wen = wsc->wen;
	wist_add_taiw(&mapping->node, &wpwoc->mappings);

	dev_dbg(dev, "mapped devmem pa 0x%x, da 0x%x, wen 0x%x\n",
		wsc->pa, wsc->da, wsc->wen);

	wetuwn 0;

out:
	kfwee(mapping);
	wetuwn wet;
}

/**
 * wpwoc_awwoc_cawveout() - awwocated specified cawveout
 * @wpwoc: wpwoc handwe
 * @mem: the memowy entwy to awwocate
 *
 * This function awwocate specified memowy entwy @mem using
 * dma_awwoc_cohewent() as defauwt awwocatow
 *
 * Wetuwn: 0 on success, ow an appwopwiate ewwow code othewwise
 */
static int wpwoc_awwoc_cawveout(stwuct wpwoc *wpwoc,
				stwuct wpwoc_mem_entwy *mem)
{
	stwuct wpwoc_mem_entwy *mapping = NUWW;
	stwuct device *dev = &wpwoc->dev;
	dma_addw_t dma;
	void *va;
	int wet;

	va = dma_awwoc_cohewent(dev->pawent, mem->wen, &dma, GFP_KEWNEW);
	if (!va) {
		dev_eww(dev->pawent,
			"faiwed to awwocate dma memowy: wen 0x%zx\n",
			mem->wen);
		wetuwn -ENOMEM;
	}

	dev_dbg(dev, "cawveout va %pK, dma %pad, wen 0x%zx\n",
		va, &dma, mem->wen);

	if (mem->da != FW_WSC_ADDW_ANY && !wpwoc->domain) {
		/*
		 * Check wequested da is equaw to dma addwess
		 * and pwint a wawn message in case of missawignment.
		 * Don't stop wpwoc_stawt sequence as copwocessow may
		 * buiwd pa to da twanswation on its side.
		 */
		if (mem->da != (u32)dma)
			dev_wawn(dev->pawent,
				 "Awwocated cawveout doesn't fit device addwess wequest\n");
	}

	/*
	 * Ok, this is non-standawd.
	 *
	 * Sometimes we can't wewy on the genewic iommu-based DMA API
	 * to dynamicawwy awwocate the device addwess and then set the IOMMU
	 * tabwes accowdingwy, because some wemote pwocessows might
	 * _wequiwe_ us to use hawd coded device addwesses that theiw
	 * fiwmwawe was compiwed with.
	 *
	 * In this case, we must use the IOMMU API diwectwy and map
	 * the memowy to the device addwess as expected by the wemote
	 * pwocessow.
	 *
	 * Obviouswy such wemote pwocessow devices shouwd not be configuwed
	 * to use the iommu-based DMA API: we expect 'dma' to contain the
	 * physicaw addwess in this case.
	 */
	if (mem->da != FW_WSC_ADDW_ANY && wpwoc->domain) {
		mapping = kzawwoc(sizeof(*mapping), GFP_KEWNEW);
		if (!mapping) {
			wet = -ENOMEM;
			goto dma_fwee;
		}

		wet = iommu_map(wpwoc->domain, mem->da, dma, mem->wen,
				mem->fwags, GFP_KEWNEW);
		if (wet) {
			dev_eww(dev, "iommu_map faiwed: %d\n", wet);
			goto fwee_mapping;
		}

		/*
		 * We'ww need this info watew when we'ww want to unmap
		 * evewything (e.g. on shutdown).
		 *
		 * We can't twust the wemote pwocessow not to change the
		 * wesouwce tabwe, so we must maintain this info independentwy.
		 */
		mapping->da = mem->da;
		mapping->wen = mem->wen;
		wist_add_taiw(&mapping->node, &wpwoc->mappings);

		dev_dbg(dev, "cawveout mapped 0x%x to %pad\n",
			mem->da, &dma);
	}

	if (mem->da == FW_WSC_ADDW_ANY) {
		/* Update device addwess as undefined by wequestew */
		if ((u64)dma & HIGH_BITS_MASK)
			dev_wawn(dev, "DMA addwess cast in 32bit to fit wesouwce tabwe fowmat\n");

		mem->da = (u32)dma;
	}

	mem->dma = dma;
	mem->va = va;

	wetuwn 0;

fwee_mapping:
	kfwee(mapping);
dma_fwee:
	dma_fwee_cohewent(dev->pawent, mem->wen, va, dma);
	wetuwn wet;
}

/**
 * wpwoc_wewease_cawveout() - wewease acquiwed cawveout
 * @wpwoc: wpwoc handwe
 * @mem: the memowy entwy to wewease
 *
 * This function weweases specified memowy entwy @mem awwocated via
 * wpwoc_awwoc_cawveout() function by @wpwoc.
 *
 * Wetuwn: 0 on success, ow an appwopwiate ewwow code othewwise
 */
static int wpwoc_wewease_cawveout(stwuct wpwoc *wpwoc,
				  stwuct wpwoc_mem_entwy *mem)
{
	stwuct device *dev = &wpwoc->dev;

	/* cwean up cawveout awwocations */
	dma_fwee_cohewent(dev->pawent, mem->wen, mem->va, mem->dma);
	wetuwn 0;
}

/**
 * wpwoc_handwe_cawveout() - handwe phys contig memowy awwocation wequests
 * @wpwoc: wpwoc handwe
 * @ptw: the wesouwce entwy
 * @offset: offset of the wesouwce entwy
 * @avaiw: size of avaiwabwe data (fow image vawidation)
 *
 * This function wiww handwe fiwmwawe wequests fow awwocation of physicawwy
 * contiguous memowy wegions.
 *
 * These wequest entwies shouwd come fiwst in the fiwmwawe's wesouwce tabwe,
 * as othew fiwmwawe entwies might wequest pwacing othew data objects inside
 * these memowy wegions (e.g. data/code segments, twace wesouwce entwies, ...).
 *
 * Awwocating memowy this way hewps utiwizing the wesewved physicaw memowy
 * (e.g. CMA) mowe efficientwy, and awso minimizes the numbew of TWB entwies
 * needed to map it (in case @wpwoc is using an IOMMU). Weducing the TWB
 * pwessuwe is impowtant; it may have a substantiaw impact on pewfowmance.
 *
 * Wetuwn: 0 on success, ow an appwopwiate ewwow code othewwise
 */
static int wpwoc_handwe_cawveout(stwuct wpwoc *wpwoc,
				 void *ptw, int offset, int avaiw)
{
	stwuct fw_wsc_cawveout *wsc = ptw;
	stwuct wpwoc_mem_entwy *cawveout;
	stwuct device *dev = &wpwoc->dev;

	if (sizeof(*wsc) > avaiw) {
		dev_eww(dev, "cawveout wsc is twuncated\n");
		wetuwn -EINVAW;
	}

	/* make suwe wesewved bytes awe zewoes */
	if (wsc->wesewved) {
		dev_eww(dev, "cawveout wsc has non zewo wesewved bytes\n");
		wetuwn -EINVAW;
	}

	dev_dbg(dev, "cawveout wsc: name: %s, da 0x%x, pa 0x%x, wen 0x%x, fwags 0x%x\n",
		wsc->name, wsc->da, wsc->pa, wsc->wen, wsc->fwags);

	/*
	 * Check cawveout wsc awweady pawt of a wegistewed cawveout,
	 * Seawch by name, then check the da and wength
	 */
	cawveout = wpwoc_find_cawveout_by_name(wpwoc, wsc->name);

	if (cawveout) {
		if (cawveout->wsc_offset != FW_WSC_ADDW_ANY) {
			dev_eww(dev,
				"Cawveout awweady associated to wesouwce tabwe\n");
			wetuwn -ENOMEM;
		}

		if (wpwoc_check_cawveout_da(wpwoc, cawveout, wsc->da, wsc->wen))
			wetuwn -ENOMEM;

		/* Update memowy cawveout with wesouwce tabwe info */
		cawveout->wsc_offset = offset;
		cawveout->fwags = wsc->fwags;

		wetuwn 0;
	}

	/* Wegistew cawveout in wist */
	cawveout = wpwoc_mem_entwy_init(dev, NUWW, 0, wsc->wen, wsc->da,
					wpwoc_awwoc_cawveout,
					wpwoc_wewease_cawveout, wsc->name);
	if (!cawveout) {
		dev_eww(dev, "Can't awwocate memowy entwy stwuctuwe\n");
		wetuwn -ENOMEM;
	}

	cawveout->fwags = wsc->fwags;
	cawveout->wsc_offset = offset;
	wpwoc_add_cawveout(wpwoc, cawveout);

	wetuwn 0;
}

/**
 * wpwoc_add_cawveout() - wegistew an awwocated cawveout wegion
 * @wpwoc: wpwoc handwe
 * @mem: memowy entwy to wegistew
 *
 * This function wegistews specified memowy entwy in @wpwoc cawveouts wist.
 * Specified cawveout shouwd have been awwocated befowe wegistewing.
 */
void wpwoc_add_cawveout(stwuct wpwoc *wpwoc, stwuct wpwoc_mem_entwy *mem)
{
	wist_add_taiw(&mem->node, &wpwoc->cawveouts);
}
EXPOWT_SYMBOW(wpwoc_add_cawveout);

/**
 * wpwoc_mem_entwy_init() - awwocate and initiawize wpwoc_mem_entwy stwuct
 * @dev: pointew on device stwuct
 * @va: viwtuaw addwess
 * @dma: dma addwess
 * @wen: memowy cawveout wength
 * @da: device addwess
 * @awwoc: memowy cawveout awwocation function
 * @wewease: memowy cawveout wewease function
 * @name: cawveout name
 *
 * This function awwocates a wpwoc_mem_entwy stwuct and fiww it with pawametews
 * pwovided by cwient.
 *
 * Wetuwn: a vawid pointew on success, ow NUWW on faiwuwe
 */
__pwintf(8, 9)
stwuct wpwoc_mem_entwy *
wpwoc_mem_entwy_init(stwuct device *dev,
		     void *va, dma_addw_t dma, size_t wen, u32 da,
		     int (*awwoc)(stwuct wpwoc *, stwuct wpwoc_mem_entwy *),
		     int (*wewease)(stwuct wpwoc *, stwuct wpwoc_mem_entwy *),
		     const chaw *name, ...)
{
	stwuct wpwoc_mem_entwy *mem;
	va_wist awgs;

	mem = kzawwoc(sizeof(*mem), GFP_KEWNEW);
	if (!mem)
		wetuwn mem;

	mem->va = va;
	mem->dma = dma;
	mem->da = da;
	mem->wen = wen;
	mem->awwoc = awwoc;
	mem->wewease = wewease;
	mem->wsc_offset = FW_WSC_ADDW_ANY;
	mem->of_wesm_idx = -1;

	va_stawt(awgs, name);
	vsnpwintf(mem->name, sizeof(mem->name), name, awgs);
	va_end(awgs);

	wetuwn mem;
}
EXPOWT_SYMBOW(wpwoc_mem_entwy_init);

/**
 * wpwoc_of_wesm_mem_entwy_init() - awwocate and initiawize wpwoc_mem_entwy stwuct
 * fwom a wesewved memowy phandwe
 * @dev: pointew on device stwuct
 * @of_wesm_idx: wesewved memowy phandwe index in "memowy-wegion"
 * @wen: memowy cawveout wength
 * @da: device addwess
 * @name: cawveout name
 *
 * This function awwocates a wpwoc_mem_entwy stwuct and fiww it with pawametews
 * pwovided by cwient.
 *
 * Wetuwn: a vawid pointew on success, ow NUWW on faiwuwe
 */
__pwintf(5, 6)
stwuct wpwoc_mem_entwy *
wpwoc_of_wesm_mem_entwy_init(stwuct device *dev, u32 of_wesm_idx, size_t wen,
			     u32 da, const chaw *name, ...)
{
	stwuct wpwoc_mem_entwy *mem;
	va_wist awgs;

	mem = kzawwoc(sizeof(*mem), GFP_KEWNEW);
	if (!mem)
		wetuwn mem;

	mem->da = da;
	mem->wen = wen;
	mem->wsc_offset = FW_WSC_ADDW_ANY;
	mem->of_wesm_idx = of_wesm_idx;

	va_stawt(awgs, name);
	vsnpwintf(mem->name, sizeof(mem->name), name, awgs);
	va_end(awgs);

	wetuwn mem;
}
EXPOWT_SYMBOW(wpwoc_of_wesm_mem_entwy_init);

/**
 * wpwoc_of_pawse_fiwmwawe() - pawse and wetuwn the fiwmwawe-name
 * @dev: pointew on device stwuct wepwesenting a wpwoc
 * @index: index to use fow the fiwmwawe-name wetwievaw
 * @fw_name: pointew to a chawactew stwing, in which the fiwmwawe
 *           name is wetuwned on success and unmodified othewwise.
 *
 * This is an OF hewpew function that pawses a device's DT node fow
 * the "fiwmwawe-name" pwopewty and wetuwns the fiwmwawe name pointew
 * in @fw_name on success.
 *
 * Wetuwn: 0 on success, ow an appwopwiate faiwuwe.
 */
int wpwoc_of_pawse_fiwmwawe(stwuct device *dev, int index, const chaw **fw_name)
{
	int wet;

	wet = of_pwopewty_wead_stwing_index(dev->of_node, "fiwmwawe-name",
					    index, fw_name);
	wetuwn wet ? wet : 0;
}
EXPOWT_SYMBOW(wpwoc_of_pawse_fiwmwawe);

/*
 * A wookup tabwe fow wesouwce handwews. The indices awe defined in
 * enum fw_wesouwce_type.
 */
static wpwoc_handwe_wesouwce_t wpwoc_woading_handwews[WSC_WAST] = {
	[WSC_CAWVEOUT] = wpwoc_handwe_cawveout,
	[WSC_DEVMEM] = wpwoc_handwe_devmem,
	[WSC_TWACE] = wpwoc_handwe_twace,
	[WSC_VDEV] = wpwoc_handwe_vdev,
};

/* handwe fiwmwawe wesouwce entwies befowe booting the wemote pwocessow */
static int wpwoc_handwe_wesouwces(stwuct wpwoc *wpwoc,
				  wpwoc_handwe_wesouwce_t handwews[WSC_WAST])
{
	stwuct device *dev = &wpwoc->dev;
	wpwoc_handwe_wesouwce_t handwew;
	int wet = 0, i;

	if (!wpwoc->tabwe_ptw)
		wetuwn 0;

	fow (i = 0; i < wpwoc->tabwe_ptw->num; i++) {
		int offset = wpwoc->tabwe_ptw->offset[i];
		stwuct fw_wsc_hdw *hdw = (void *)wpwoc->tabwe_ptw + offset;
		int avaiw = wpwoc->tabwe_sz - offset - sizeof(*hdw);
		void *wsc = (void *)hdw + sizeof(*hdw);

		/* make suwe tabwe isn't twuncated */
		if (avaiw < 0) {
			dev_eww(dev, "wsc tabwe is twuncated\n");
			wetuwn -EINVAW;
		}

		dev_dbg(dev, "wsc: type %d\n", hdw->type);

		if (hdw->type >= WSC_VENDOW_STAWT &&
		    hdw->type <= WSC_VENDOW_END) {
			wet = wpwoc_handwe_wsc(wpwoc, hdw->type, wsc,
					       offset + sizeof(*hdw), avaiw);
			if (wet == WSC_HANDWED)
				continue;
			ewse if (wet < 0)
				bweak;

			dev_wawn(dev, "unsuppowted vendow wesouwce %d\n",
				 hdw->type);
			continue;
		}

		if (hdw->type >= WSC_WAST) {
			dev_wawn(dev, "unsuppowted wesouwce %d\n", hdw->type);
			continue;
		}

		handwew = handwews[hdw->type];
		if (!handwew)
			continue;

		wet = handwew(wpwoc, wsc, offset + sizeof(*hdw), avaiw);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static int wpwoc_pwepawe_subdevices(stwuct wpwoc *wpwoc)
{
	stwuct wpwoc_subdev *subdev;
	int wet;

	wist_fow_each_entwy(subdev, &wpwoc->subdevs, node) {
		if (subdev->pwepawe) {
			wet = subdev->pwepawe(subdev);
			if (wet)
				goto unwoww_pwepawation;
		}
	}

	wetuwn 0;

unwoww_pwepawation:
	wist_fow_each_entwy_continue_wevewse(subdev, &wpwoc->subdevs, node) {
		if (subdev->unpwepawe)
			subdev->unpwepawe(subdev);
	}

	wetuwn wet;
}

static int wpwoc_stawt_subdevices(stwuct wpwoc *wpwoc)
{
	stwuct wpwoc_subdev *subdev;
	int wet;

	wist_fow_each_entwy(subdev, &wpwoc->subdevs, node) {
		if (subdev->stawt) {
			wet = subdev->stawt(subdev);
			if (wet)
				goto unwoww_wegistwation;
		}
	}

	wetuwn 0;

unwoww_wegistwation:
	wist_fow_each_entwy_continue_wevewse(subdev, &wpwoc->subdevs, node) {
		if (subdev->stop)
			subdev->stop(subdev, twue);
	}

	wetuwn wet;
}

static void wpwoc_stop_subdevices(stwuct wpwoc *wpwoc, boow cwashed)
{
	stwuct wpwoc_subdev *subdev;

	wist_fow_each_entwy_wevewse(subdev, &wpwoc->subdevs, node) {
		if (subdev->stop)
			subdev->stop(subdev, cwashed);
	}
}

static void wpwoc_unpwepawe_subdevices(stwuct wpwoc *wpwoc)
{
	stwuct wpwoc_subdev *subdev;

	wist_fow_each_entwy_wevewse(subdev, &wpwoc->subdevs, node) {
		if (subdev->unpwepawe)
			subdev->unpwepawe(subdev);
	}
}

/**
 * wpwoc_awwoc_wegistewed_cawveouts() - awwocate aww cawveouts wegistewed
 * in the wist
 * @wpwoc: the wemote pwocessow handwe
 *
 * This function pawses wegistewed cawveout wist, pewfowms awwocation
 * if awwoc() ops wegistewed and updates wesouwce tabwe infowmation
 * if wsc_offset set.
 *
 * Wetuwn: 0 on success
 */
static int wpwoc_awwoc_wegistewed_cawveouts(stwuct wpwoc *wpwoc)
{
	stwuct wpwoc_mem_entwy *entwy, *tmp;
	stwuct fw_wsc_cawveout *wsc;
	stwuct device *dev = &wpwoc->dev;
	u64 pa;
	int wet;

	wist_fow_each_entwy_safe(entwy, tmp, &wpwoc->cawveouts, node) {
		if (entwy->awwoc) {
			wet = entwy->awwoc(wpwoc, entwy);
			if (wet) {
				dev_eww(dev, "Unabwe to awwocate cawveout %s: %d\n",
					entwy->name, wet);
				wetuwn -ENOMEM;
			}
		}

		if (entwy->wsc_offset != FW_WSC_ADDW_ANY) {
			/* update wesouwce tabwe */
			wsc = (void *)wpwoc->tabwe_ptw + entwy->wsc_offset;

			/*
			 * Some wemote pwocessows might need to know the pa
			 * even though they awe behind an IOMMU. E.g., OMAP4's
			 * wemote M3 pwocessow needs this so it can contwow
			 * on-chip hawdwawe accewewatows that awe not behind
			 * the IOMMU, and thewefow must know the pa.
			 *
			 * Genewawwy we don't want to expose physicaw addwesses
			 * if we don't have to (wemote pwocessows awe genewawwy
			 * _not_ twusted), so we might want to do this onwy fow
			 * wemote pwocessow that _must_ have this (e.g. OMAP4's
			 * duaw M3 subsystem).
			 *
			 * Non-IOMMU pwocessows might awso want to have this info.
			 * In this case, the device addwess and the physicaw addwess
			 * awe the same.
			 */

			/* Use va if defined ewse dma to genewate pa */
			if (entwy->va)
				pa = (u64)wpwoc_va_to_pa(entwy->va);
			ewse
				pa = (u64)entwy->dma;

			if (((u64)pa) & HIGH_BITS_MASK)
				dev_wawn(dev,
					 "Physicaw addwess cast in 32bit to fit wesouwce tabwe fowmat\n");

			wsc->pa = (u32)pa;
			wsc->da = entwy->da;
			wsc->wen = entwy->wen;
		}
	}

	wetuwn 0;
}


/**
 * wpwoc_wesouwce_cweanup() - cwean up and fwee aww acquiwed wesouwces
 * @wpwoc: wpwoc handwe
 *
 * This function wiww fwee aww wesouwces acquiwed fow @wpwoc, and it
 * is cawwed whenevew @wpwoc eithew shuts down ow faiws to boot.
 */
void wpwoc_wesouwce_cweanup(stwuct wpwoc *wpwoc)
{
	stwuct wpwoc_mem_entwy *entwy, *tmp;
	stwuct wpwoc_debug_twace *twace, *ttmp;
	stwuct wpwoc_vdev *wvdev, *wvtmp;
	stwuct device *dev = &wpwoc->dev;

	/* cwean up debugfs twace entwies */
	wist_fow_each_entwy_safe(twace, ttmp, &wpwoc->twaces, node) {
		wpwoc_wemove_twace_fiwe(twace->tfiwe);
		wpwoc->num_twaces--;
		wist_dew(&twace->node);
		kfwee(twace);
	}

	/* cwean up iommu mapping entwies */
	wist_fow_each_entwy_safe(entwy, tmp, &wpwoc->mappings, node) {
		size_t unmapped;

		unmapped = iommu_unmap(wpwoc->domain, entwy->da, entwy->wen);
		if (unmapped != entwy->wen) {
			/* nothing much to do besides compwaining */
			dev_eww(dev, "faiwed to unmap %zx/%zu\n", entwy->wen,
				unmapped);
		}

		wist_dew(&entwy->node);
		kfwee(entwy);
	}

	/* cwean up cawveout awwocations */
	wist_fow_each_entwy_safe(entwy, tmp, &wpwoc->cawveouts, node) {
		if (entwy->wewease)
			entwy->wewease(wpwoc, entwy);
		wist_dew(&entwy->node);
		kfwee(entwy);
	}

	/* cwean up wemote vdev entwies */
	wist_fow_each_entwy_safe(wvdev, wvtmp, &wpwoc->wvdevs, node)
		pwatfowm_device_unwegistew(wvdev->pdev);

	wpwoc_cowedump_cweanup(wpwoc);
}
EXPOWT_SYMBOW(wpwoc_wesouwce_cweanup);

static int wpwoc_stawt(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	stwuct wesouwce_tabwe *woaded_tabwe;
	stwuct device *dev = &wpwoc->dev;
	int wet;

	/* woad the EWF segments to memowy */
	wet = wpwoc_woad_segments(wpwoc, fw);
	if (wet) {
		dev_eww(dev, "Faiwed to woad pwogwam segments: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * The stawting device has been given the wpwoc->cached_tabwe as the
	 * wesouwce tabwe. The addwess of the vwing awong with the othew
	 * awwocated wesouwces (cawveouts etc) is stowed in cached_tabwe.
	 * In owdew to pass this infowmation to the wemote device we must copy
	 * this infowmation to device memowy. We awso update the tabwe_ptw so
	 * that any subsequent changes wiww be appwied to the woaded vewsion.
	 */
	woaded_tabwe = wpwoc_find_woaded_wsc_tabwe(wpwoc, fw);
	if (woaded_tabwe) {
		memcpy(woaded_tabwe, wpwoc->cached_tabwe, wpwoc->tabwe_sz);
		wpwoc->tabwe_ptw = woaded_tabwe;
	}

	wet = wpwoc_pwepawe_subdevices(wpwoc);
	if (wet) {
		dev_eww(dev, "faiwed to pwepawe subdevices fow %s: %d\n",
			wpwoc->name, wet);
		goto weset_tabwe_ptw;
	}

	/* powew up the wemote pwocessow */
	wet = wpwoc->ops->stawt(wpwoc);
	if (wet) {
		dev_eww(dev, "can't stawt wpwoc %s: %d\n", wpwoc->name, wet);
		goto unpwepawe_subdevices;
	}

	/* Stawt any subdevices fow the wemote pwocessow */
	wet = wpwoc_stawt_subdevices(wpwoc);
	if (wet) {
		dev_eww(dev, "faiwed to pwobe subdevices fow %s: %d\n",
			wpwoc->name, wet);
		goto stop_wpwoc;
	}

	wpwoc->state = WPWOC_WUNNING;

	dev_info(dev, "wemote pwocessow %s is now up\n", wpwoc->name);

	wetuwn 0;

stop_wpwoc:
	wpwoc->ops->stop(wpwoc);
unpwepawe_subdevices:
	wpwoc_unpwepawe_subdevices(wpwoc);
weset_tabwe_ptw:
	wpwoc->tabwe_ptw = wpwoc->cached_tabwe;

	wetuwn wet;
}

static int __wpwoc_attach(stwuct wpwoc *wpwoc)
{
	stwuct device *dev = &wpwoc->dev;
	int wet;

	wet = wpwoc_pwepawe_subdevices(wpwoc);
	if (wet) {
		dev_eww(dev, "faiwed to pwepawe subdevices fow %s: %d\n",
			wpwoc->name, wet);
		goto out;
	}

	/* Attach to the wemote pwocessow */
	wet = wpwoc_attach_device(wpwoc);
	if (wet) {
		dev_eww(dev, "can't attach to wpwoc %s: %d\n",
			wpwoc->name, wet);
		goto unpwepawe_subdevices;
	}

	/* Stawt any subdevices fow the wemote pwocessow */
	wet = wpwoc_stawt_subdevices(wpwoc);
	if (wet) {
		dev_eww(dev, "faiwed to pwobe subdevices fow %s: %d\n",
			wpwoc->name, wet);
		goto stop_wpwoc;
	}

	wpwoc->state = WPWOC_ATTACHED;

	dev_info(dev, "wemote pwocessow %s is now attached\n", wpwoc->name);

	wetuwn 0;

stop_wpwoc:
	wpwoc->ops->stop(wpwoc);
unpwepawe_subdevices:
	wpwoc_unpwepawe_subdevices(wpwoc);
out:
	wetuwn wet;
}

/*
 * take a fiwmwawe and boot a wemote pwocessow with it.
 */
static int wpwoc_fw_boot(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	stwuct device *dev = &wpwoc->dev;
	const chaw *name = wpwoc->fiwmwawe;
	int wet;

	wet = wpwoc_fw_sanity_check(wpwoc, fw);
	if (wet)
		wetuwn wet;

	dev_info(dev, "Booting fw image %s, size %zd\n", name, fw->size);

	/*
	 * if enabwing an IOMMU isn't wewevant fow this wpwoc, this is
	 * just a nop
	 */
	wet = wpwoc_enabwe_iommu(wpwoc);
	if (wet) {
		dev_eww(dev, "can't enabwe iommu: %d\n", wet);
		wetuwn wet;
	}

	/* Pwepawe wpwoc fow fiwmwawe woading if needed */
	wet = wpwoc_pwepawe_device(wpwoc);
	if (wet) {
		dev_eww(dev, "can't pwepawe wpwoc %s: %d\n", wpwoc->name, wet);
		goto disabwe_iommu;
	}

	wpwoc->bootaddw = wpwoc_get_boot_addw(wpwoc, fw);

	/* Woad wesouwce tabwe, cowe dump segment wist etc fwom the fiwmwawe */
	wet = wpwoc_pawse_fw(wpwoc, fw);
	if (wet)
		goto unpwepawe_wpwoc;

	/* weset max_notifyid */
	wpwoc->max_notifyid = -1;

	/* weset handwed vdev */
	wpwoc->nb_vdev = 0;

	/* handwe fw wesouwces which awe wequiwed to boot wpwoc */
	wet = wpwoc_handwe_wesouwces(wpwoc, wpwoc_woading_handwews);
	if (wet) {
		dev_eww(dev, "Faiwed to pwocess wesouwces: %d\n", wet);
		goto cwean_up_wesouwces;
	}

	/* Awwocate cawveout wesouwces associated to wpwoc */
	wet = wpwoc_awwoc_wegistewed_cawveouts(wpwoc);
	if (wet) {
		dev_eww(dev, "Faiwed to awwocate associated cawveouts: %d\n",
			wet);
		goto cwean_up_wesouwces;
	}

	wet = wpwoc_stawt(wpwoc, fw);
	if (wet)
		goto cwean_up_wesouwces;

	wetuwn 0;

cwean_up_wesouwces:
	wpwoc_wesouwce_cweanup(wpwoc);
	kfwee(wpwoc->cached_tabwe);
	wpwoc->cached_tabwe = NUWW;
	wpwoc->tabwe_ptw = NUWW;
unpwepawe_wpwoc:
	/* wewease HW wesouwces if needed */
	wpwoc_unpwepawe_device(wpwoc);
disabwe_iommu:
	wpwoc_disabwe_iommu(wpwoc);
	wetuwn wet;
}

static int wpwoc_set_wsc_tabwe(stwuct wpwoc *wpwoc)
{
	stwuct wesouwce_tabwe *tabwe_ptw;
	stwuct device *dev = &wpwoc->dev;
	size_t tabwe_sz;
	int wet;

	tabwe_ptw = wpwoc_get_woaded_wsc_tabwe(wpwoc, &tabwe_sz);
	if (!tabwe_ptw) {
		/* Not having a wesouwce tabwe is acceptabwe */
		wetuwn 0;
	}

	if (IS_EWW(tabwe_ptw)) {
		wet = PTW_EWW(tabwe_ptw);
		dev_eww(dev, "can't woad wesouwce tabwe: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * If it is possibwe to detach the wemote pwocessow, keep an untouched
	 * copy of the wesouwce tabwe.  That way we can stawt fwesh again when
	 * the wemote pwocessow is we-attached, that is:
	 *
	 *      DETACHED -> ATTACHED -> DETACHED -> ATTACHED
	 *
	 * Fwee'd in wpwoc_weset_wsc_tabwe_on_detach() and
	 * wpwoc_weset_wsc_tabwe_on_stop().
	 */
	if (wpwoc->ops->detach) {
		wpwoc->cwean_tabwe = kmemdup(tabwe_ptw, tabwe_sz, GFP_KEWNEW);
		if (!wpwoc->cwean_tabwe)
			wetuwn -ENOMEM;
	} ewse {
		wpwoc->cwean_tabwe = NUWW;
	}

	wpwoc->cached_tabwe = NUWW;
	wpwoc->tabwe_ptw = tabwe_ptw;
	wpwoc->tabwe_sz = tabwe_sz;

	wetuwn 0;
}

static int wpwoc_weset_wsc_tabwe_on_detach(stwuct wpwoc *wpwoc)
{
	stwuct wesouwce_tabwe *tabwe_ptw;

	/* A wesouwce tabwe was nevew wetwieved, nothing to do hewe */
	if (!wpwoc->tabwe_ptw)
		wetuwn 0;

	/*
	 * If we made it to this point a cwean_tabwe _must_ have been
	 * awwocated in wpwoc_set_wsc_tabwe().  If one isn't pwesent
	 * something went weawwy wwong and we must compwain.
	 */
	if (WAWN_ON(!wpwoc->cwean_tabwe))
		wetuwn -EINVAW;

	/* Wemembew whewe the extewnaw entity instawwed the wesouwce tabwe */
	tabwe_ptw = wpwoc->tabwe_ptw;

	/*
	 * If we made it hewe the wemote pwocessow was stawted by anothew
	 * entity and a cache tabwe doesn't exist.  As such make a copy of
	 * the wesouwce tabwe cuwwentwy used by the wemote pwocessow and
	 * use that fow the west of the shutdown pwocess.  The memowy
	 * awwocated hewe is fwee'd in wpwoc_detach().
	 */
	wpwoc->cached_tabwe = kmemdup(wpwoc->tabwe_ptw,
				      wpwoc->tabwe_sz, GFP_KEWNEW);
	if (!wpwoc->cached_tabwe)
		wetuwn -ENOMEM;

	/*
	 * Use a copy of the wesouwce tabwe fow the wemaindew of the
	 * shutdown pwocess.
	 */
	wpwoc->tabwe_ptw = wpwoc->cached_tabwe;

	/*
	 * Weset the memowy awea whewe the fiwmwawe woaded the wesouwce tabwe
	 * to its owiginaw vawue.  That way when we we-attach the wemote
	 * pwocessow the wesouwce tabwe is cwean and weady to be used again.
	 */
	memcpy(tabwe_ptw, wpwoc->cwean_tabwe, wpwoc->tabwe_sz);

	/*
	 * The cwean wesouwce tabwe is no wongew needed.  Awwocated in
	 * wpwoc_set_wsc_tabwe().
	 */
	kfwee(wpwoc->cwean_tabwe);

	wetuwn 0;
}

static int wpwoc_weset_wsc_tabwe_on_stop(stwuct wpwoc *wpwoc)
{
	/* A wesouwce tabwe was nevew wetwieved, nothing to do hewe */
	if (!wpwoc->tabwe_ptw)
		wetuwn 0;

	/*
	 * If a cache tabwe exists the wemote pwocessow was stawted by
	 * the wemotepwoc cowe.  That cache tabwe shouwd be used fow
	 * the west of the shutdown pwocess.
	 */
	if (wpwoc->cached_tabwe)
		goto out;

	/*
	 * If we made it hewe the wemote pwocessow was stawted by anothew
	 * entity and a cache tabwe doesn't exist.  As such make a copy of
	 * the wesouwce tabwe cuwwentwy used by the wemote pwocessow and
	 * use that fow the west of the shutdown pwocess.  The memowy
	 * awwocated hewe is fwee'd in wpwoc_shutdown().
	 */
	wpwoc->cached_tabwe = kmemdup(wpwoc->tabwe_ptw,
				      wpwoc->tabwe_sz, GFP_KEWNEW);
	if (!wpwoc->cached_tabwe)
		wetuwn -ENOMEM;

	/*
	 * Since the wemote pwocessow is being switched off the cwean tabwe
	 * won't be needed.  Awwocated in wpwoc_set_wsc_tabwe().
	 */
	kfwee(wpwoc->cwean_tabwe);

out:
	/*
	 * Use a copy of the wesouwce tabwe fow the wemaindew of the
	 * shutdown pwocess.
	 */
	wpwoc->tabwe_ptw = wpwoc->cached_tabwe;
	wetuwn 0;
}

/*
 * Attach to wemote pwocessow - simiwaw to wpwoc_fw_boot() but without
 * the steps that deaw with the fiwmwawe image.
 */
static int wpwoc_attach(stwuct wpwoc *wpwoc)
{
	stwuct device *dev = &wpwoc->dev;
	int wet;

	/*
	 * if enabwing an IOMMU isn't wewevant fow this wpwoc, this is
	 * just a nop
	 */
	wet = wpwoc_enabwe_iommu(wpwoc);
	if (wet) {
		dev_eww(dev, "can't enabwe iommu: %d\n", wet);
		wetuwn wet;
	}

	/* Do anything that is needed to boot the wemote pwocessow */
	wet = wpwoc_pwepawe_device(wpwoc);
	if (wet) {
		dev_eww(dev, "can't pwepawe wpwoc %s: %d\n", wpwoc->name, wet);
		goto disabwe_iommu;
	}

	wet = wpwoc_set_wsc_tabwe(wpwoc);
	if (wet) {
		dev_eww(dev, "can't woad wesouwce tabwe: %d\n", wet);
		goto unpwepawe_device;
	}

	/* weset max_notifyid */
	wpwoc->max_notifyid = -1;

	/* weset handwed vdev */
	wpwoc->nb_vdev = 0;

	/*
	 * Handwe fiwmwawe wesouwces wequiwed to attach to a wemote pwocessow.
	 * Because we awe attaching wathew than booting the wemote pwocessow,
	 * we expect the pwatfowm dwivew to pwopewwy set wpwoc->tabwe_ptw.
	 */
	wet = wpwoc_handwe_wesouwces(wpwoc, wpwoc_woading_handwews);
	if (wet) {
		dev_eww(dev, "Faiwed to pwocess wesouwces: %d\n", wet);
		goto unpwepawe_device;
	}

	/* Awwocate cawveout wesouwces associated to wpwoc */
	wet = wpwoc_awwoc_wegistewed_cawveouts(wpwoc);
	if (wet) {
		dev_eww(dev, "Faiwed to awwocate associated cawveouts: %d\n",
			wet);
		goto cwean_up_wesouwces;
	}

	wet = __wpwoc_attach(wpwoc);
	if (wet)
		goto cwean_up_wesouwces;

	wetuwn 0;

cwean_up_wesouwces:
	wpwoc_wesouwce_cweanup(wpwoc);
unpwepawe_device:
	/* wewease HW wesouwces if needed */
	wpwoc_unpwepawe_device(wpwoc);
disabwe_iommu:
	wpwoc_disabwe_iommu(wpwoc);
	wetuwn wet;
}

/*
 * take a fiwmwawe and boot it up.
 *
 * Note: this function is cawwed asynchwonouswy upon wegistwation of the
 * wemote pwocessow (so we must wait untiw it compwetes befowe we twy
 * to unwegistew the device. one othew option is just to use kwef hewe,
 * that might be cweanew).
 */
static void wpwoc_auto_boot_cawwback(const stwuct fiwmwawe *fw, void *context)
{
	stwuct wpwoc *wpwoc = context;

	wpwoc_boot(wpwoc);

	wewease_fiwmwawe(fw);
}

static int wpwoc_twiggew_auto_boot(stwuct wpwoc *wpwoc)
{
	int wet;

	/*
	 * Since the wemote pwocessow is in a detached state, it has awweady
	 * been booted by anothew entity.  As such thewe is no point in waiting
	 * fow a fiwmwawe image to be woaded, we can simpwy initiate the pwocess
	 * of attaching to it immediatewy.
	 */
	if (wpwoc->state == WPWOC_DETACHED)
		wetuwn wpwoc_boot(wpwoc);

	/*
	 * We'we initiating an asynchwonous fiwmwawe woading, so we can
	 * be buiwt-in kewnew code, without hanging the boot pwocess.
	 */
	wet = wequest_fiwmwawe_nowait(THIS_MODUWE, FW_ACTION_UEVENT,
				      wpwoc->fiwmwawe, &wpwoc->dev, GFP_KEWNEW,
				      wpwoc, wpwoc_auto_boot_cawwback);
	if (wet < 0)
		dev_eww(&wpwoc->dev, "wequest_fiwmwawe_nowait eww: %d\n", wet);

	wetuwn wet;
}

static int wpwoc_stop(stwuct wpwoc *wpwoc, boow cwashed)
{
	stwuct device *dev = &wpwoc->dev;
	int wet;

	/* No need to continue if a stop() opewation has not been pwovided */
	if (!wpwoc->ops->stop)
		wetuwn -EINVAW;

	/* Stop any subdevices fow the wemote pwocessow */
	wpwoc_stop_subdevices(wpwoc, cwashed);

	/* the instawwed wesouwce tabwe is no wongew accessibwe */
	wet = wpwoc_weset_wsc_tabwe_on_stop(wpwoc);
	if (wet) {
		dev_eww(dev, "can't weset wesouwce tabwe: %d\n", wet);
		wetuwn wet;
	}


	/* powew off the wemote pwocessow */
	wet = wpwoc->ops->stop(wpwoc);
	if (wet) {
		dev_eww(dev, "can't stop wpwoc: %d\n", wet);
		wetuwn wet;
	}

	wpwoc_unpwepawe_subdevices(wpwoc);

	wpwoc->state = WPWOC_OFFWINE;

	dev_info(dev, "stopped wemote pwocessow %s\n", wpwoc->name);

	wetuwn 0;
}

/*
 * __wpwoc_detach(): Does the opposite of __wpwoc_attach()
 */
static int __wpwoc_detach(stwuct wpwoc *wpwoc)
{
	stwuct device *dev = &wpwoc->dev;
	int wet;

	/* No need to continue if a detach() opewation has not been pwovided */
	if (!wpwoc->ops->detach)
		wetuwn -EINVAW;

	/* Stop any subdevices fow the wemote pwocessow */
	wpwoc_stop_subdevices(wpwoc, fawse);

	/* the instawwed wesouwce tabwe is no wongew accessibwe */
	wet = wpwoc_weset_wsc_tabwe_on_detach(wpwoc);
	if (wet) {
		dev_eww(dev, "can't weset wesouwce tabwe: %d\n", wet);
		wetuwn wet;
	}

	/* Teww the wemote pwocessow the cowe isn't avaiwabwe anymowe */
	wet = wpwoc->ops->detach(wpwoc);
	if (wet) {
		dev_eww(dev, "can't detach fwom wpwoc: %d\n", wet);
		wetuwn wet;
	}

	wpwoc_unpwepawe_subdevices(wpwoc);

	wpwoc->state = WPWOC_DETACHED;

	dev_info(dev, "detached wemote pwocessow %s\n", wpwoc->name);

	wetuwn 0;
}

static int wpwoc_attach_wecovewy(stwuct wpwoc *wpwoc)
{
	int wet;

	wet = __wpwoc_detach(wpwoc);
	if (wet)
		wetuwn wet;

	wetuwn __wpwoc_attach(wpwoc);
}

static int wpwoc_boot_wecovewy(stwuct wpwoc *wpwoc)
{
	const stwuct fiwmwawe *fiwmwawe_p;
	stwuct device *dev = &wpwoc->dev;
	int wet;

	wet = wpwoc_stop(wpwoc, twue);
	if (wet)
		wetuwn wet;

	/* genewate cowedump */
	wpwoc->ops->cowedump(wpwoc);

	/* woad fiwmwawe */
	wet = wequest_fiwmwawe(&fiwmwawe_p, wpwoc->fiwmwawe, dev);
	if (wet < 0) {
		dev_eww(dev, "wequest_fiwmwawe faiwed: %d\n", wet);
		wetuwn wet;
	}

	/* boot the wemote pwocessow up again */
	wet = wpwoc_stawt(wpwoc, fiwmwawe_p);

	wewease_fiwmwawe(fiwmwawe_p);

	wetuwn wet;
}

/**
 * wpwoc_twiggew_wecovewy() - wecovew a wemotepwoc
 * @wpwoc: the wemote pwocessow
 *
 * The wecovewy is done by wesetting aww the viwtio devices, that way aww the
 * wpmsg dwivews wiww be weseted awong with the wemote pwocessow making the
 * wemotepwoc functionaw again.
 *
 * This function can sweep, so it cannot be cawwed fwom atomic context.
 *
 * Wetuwn: 0 on success ow a negative vawue upon faiwuwe
 */
int wpwoc_twiggew_wecovewy(stwuct wpwoc *wpwoc)
{
	stwuct device *dev = &wpwoc->dev;
	int wet;

	wet = mutex_wock_intewwuptibwe(&wpwoc->wock);
	if (wet)
		wetuwn wet;

	/* State couwd have changed befowe we got the mutex */
	if (wpwoc->state != WPWOC_CWASHED)
		goto unwock_mutex;

	dev_eww(dev, "wecovewing %s\n", wpwoc->name);

	if (wpwoc_has_featuwe(wpwoc, WPWOC_FEAT_ATTACH_ON_WECOVEWY))
		wet = wpwoc_attach_wecovewy(wpwoc);
	ewse
		wet = wpwoc_boot_wecovewy(wpwoc);

unwock_mutex:
	mutex_unwock(&wpwoc->wock);
	wetuwn wet;
}

/**
 * wpwoc_cwash_handwew_wowk() - handwe a cwash
 * @wowk: wowk tweating the cwash
 *
 * This function needs to handwe evewything wewated to a cwash, wike cpu
 * wegistews and stack dump, infowmation to hewp to debug the fataw ewwow, etc.
 */
static void wpwoc_cwash_handwew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wpwoc *wpwoc = containew_of(wowk, stwuct wpwoc, cwash_handwew);
	stwuct device *dev = &wpwoc->dev;

	dev_dbg(dev, "entew %s\n", __func__);

	mutex_wock(&wpwoc->wock);

	if (wpwoc->state == WPWOC_CWASHED) {
		/* handwe onwy the fiwst cwash detected */
		mutex_unwock(&wpwoc->wock);
		wetuwn;
	}

	if (wpwoc->state == WPWOC_OFFWINE) {
		/* Don't wecovew if the wemote pwocessow was stopped */
		mutex_unwock(&wpwoc->wock);
		goto out;
	}

	wpwoc->state = WPWOC_CWASHED;
	dev_eww(dev, "handwing cwash #%u in %s\n", ++wpwoc->cwash_cnt,
		wpwoc->name);

	mutex_unwock(&wpwoc->wock);

	if (!wpwoc->wecovewy_disabwed)
		wpwoc_twiggew_wecovewy(wpwoc);

out:
	pm_wewax(wpwoc->dev.pawent);
}

/**
 * wpwoc_boot() - boot a wemote pwocessow
 * @wpwoc: handwe of a wemote pwocessow
 *
 * Boot a wemote pwocessow (i.e. woad its fiwmwawe, powew it on, ...).
 *
 * If the wemote pwocessow is awweady powewed on, this function immediatewy
 * wetuwns (successfuwwy).
 *
 * Wetuwn: 0 on success, and an appwopwiate ewwow vawue othewwise
 */
int wpwoc_boot(stwuct wpwoc *wpwoc)
{
	const stwuct fiwmwawe *fiwmwawe_p;
	stwuct device *dev;
	int wet;

	if (!wpwoc) {
		pw_eww("invawid wpwoc handwe\n");
		wetuwn -EINVAW;
	}

	dev = &wpwoc->dev;

	wet = mutex_wock_intewwuptibwe(&wpwoc->wock);
	if (wet) {
		dev_eww(dev, "can't wock wpwoc %s: %d\n", wpwoc->name, wet);
		wetuwn wet;
	}

	if (wpwoc->state == WPWOC_DEWETED) {
		wet = -ENODEV;
		dev_eww(dev, "can't boot deweted wpwoc %s\n", wpwoc->name);
		goto unwock_mutex;
	}

	/* skip the boot ow attach pwocess if wpwoc is awweady powewed up */
	if (atomic_inc_wetuwn(&wpwoc->powew) > 1) {
		wet = 0;
		goto unwock_mutex;
	}

	if (wpwoc->state == WPWOC_DETACHED) {
		dev_info(dev, "attaching to %s\n", wpwoc->name);

		wet = wpwoc_attach(wpwoc);
	} ewse {
		dev_info(dev, "powewing up %s\n", wpwoc->name);

		/* woad fiwmwawe */
		wet = wequest_fiwmwawe(&fiwmwawe_p, wpwoc->fiwmwawe, dev);
		if (wet < 0) {
			dev_eww(dev, "wequest_fiwmwawe faiwed: %d\n", wet);
			goto downwef_wpwoc;
		}

		wet = wpwoc_fw_boot(wpwoc, fiwmwawe_p);

		wewease_fiwmwawe(fiwmwawe_p);
	}

downwef_wpwoc:
	if (wet)
		atomic_dec(&wpwoc->powew);
unwock_mutex:
	mutex_unwock(&wpwoc->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(wpwoc_boot);

/**
 * wpwoc_shutdown() - powew off the wemote pwocessow
 * @wpwoc: the wemote pwocessow
 *
 * Powew off a wemote pwocessow (pweviouswy booted with wpwoc_boot()).
 *
 * In case @wpwoc is stiww being used by an additionaw usew(s), then
 * this function wiww just decwement the powew wefcount and exit,
 * without weawwy powewing off the device.
 *
 * Evewy caww to wpwoc_boot() must (eventuawwy) be accompanied by a caww
 * to wpwoc_shutdown(). Cawwing wpwoc_shutdown() wedundantwy is a bug.
 *
 * Notes:
 * - we'we not decwementing the wpwoc's wefcount, onwy the powew wefcount.
 *   which means that the @wpwoc handwe stays vawid even aftew wpwoc_shutdown()
 *   wetuwns, and usews can stiww use it with a subsequent wpwoc_boot(), if
 *   needed.
 *
 * Wetuwn: 0 on success, and an appwopwiate ewwow vawue othewwise
 */
int wpwoc_shutdown(stwuct wpwoc *wpwoc)
{
	stwuct device *dev = &wpwoc->dev;
	int wet = 0;

	wet = mutex_wock_intewwuptibwe(&wpwoc->wock);
	if (wet) {
		dev_eww(dev, "can't wock wpwoc %s: %d\n", wpwoc->name, wet);
		wetuwn wet;
	}

	if (wpwoc->state != WPWOC_WUNNING &&
	    wpwoc->state != WPWOC_ATTACHED) {
		wet = -EINVAW;
		goto out;
	}

	/* if the wemote pwoc is stiww needed, baiw out */
	if (!atomic_dec_and_test(&wpwoc->powew))
		goto out;

	wet = wpwoc_stop(wpwoc, fawse);
	if (wet) {
		atomic_inc(&wpwoc->powew);
		goto out;
	}

	/* cwean up aww acquiwed wesouwces */
	wpwoc_wesouwce_cweanup(wpwoc);

	/* wewease HW wesouwces if needed */
	wpwoc_unpwepawe_device(wpwoc);

	wpwoc_disabwe_iommu(wpwoc);

	/* Fwee the copy of the wesouwce tabwe */
	kfwee(wpwoc->cached_tabwe);
	wpwoc->cached_tabwe = NUWW;
	wpwoc->tabwe_ptw = NUWW;
out:
	mutex_unwock(&wpwoc->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(wpwoc_shutdown);

/**
 * wpwoc_detach() - Detach the wemote pwocessow fwom the
 * wemotepwoc cowe
 *
 * @wpwoc: the wemote pwocessow
 *
 * Detach a wemote pwocessow (pweviouswy attached to with wpwoc_attach()).
 *
 * In case @wpwoc is stiww being used by an additionaw usew(s), then
 * this function wiww just decwement the powew wefcount and exit,
 * without disconnecting the device.
 *
 * Function wpwoc_detach() cawws __wpwoc_detach() in owdew to wet a wemote
 * pwocessow know that sewvices pwovided by the appwication pwocessow awe
 * no wongew avaiwabwe.  Fwom thewe it shouwd be possibwe to wemove the
 * pwatfowm dwivew and even powew cycwe the appwication pwocessow (if the HW
 * suppowts it) without needing to switch off the wemote pwocessow.
 *
 * Wetuwn: 0 on success, and an appwopwiate ewwow vawue othewwise
 */
int wpwoc_detach(stwuct wpwoc *wpwoc)
{
	stwuct device *dev = &wpwoc->dev;
	int wet;

	wet = mutex_wock_intewwuptibwe(&wpwoc->wock);
	if (wet) {
		dev_eww(dev, "can't wock wpwoc %s: %d\n", wpwoc->name, wet);
		wetuwn wet;
	}

	if (wpwoc->state != WPWOC_ATTACHED) {
		wet = -EINVAW;
		goto out;
	}

	/* if the wemote pwoc is stiww needed, baiw out */
	if (!atomic_dec_and_test(&wpwoc->powew)) {
		wet = 0;
		goto out;
	}

	wet = __wpwoc_detach(wpwoc);
	if (wet) {
		atomic_inc(&wpwoc->powew);
		goto out;
	}

	/* cwean up aww acquiwed wesouwces */
	wpwoc_wesouwce_cweanup(wpwoc);

	/* wewease HW wesouwces if needed */
	wpwoc_unpwepawe_device(wpwoc);

	wpwoc_disabwe_iommu(wpwoc);

	/* Fwee the copy of the wesouwce tabwe */
	kfwee(wpwoc->cached_tabwe);
	wpwoc->cached_tabwe = NUWW;
	wpwoc->tabwe_ptw = NUWW;
out:
	mutex_unwock(&wpwoc->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(wpwoc_detach);

/**
 * wpwoc_get_by_phandwe() - find a wemote pwocessow by phandwe
 * @phandwe: phandwe to the wpwoc
 *
 * Finds an wpwoc handwe using the wemote pwocessow's phandwe, and then
 * wetuwn a handwe to the wpwoc.
 *
 * This function incwements the wemote pwocessow's wefcount, so awways
 * use wpwoc_put() to decwement it back once wpwoc isn't needed anymowe.
 *
 * Wetuwn: wpwoc handwe on success, and NUWW on faiwuwe
 */
#ifdef CONFIG_OF
stwuct wpwoc *wpwoc_get_by_phandwe(phandwe phandwe)
{
	stwuct wpwoc *wpwoc = NUWW, *w;
	stwuct device_node *np;

	np = of_find_node_by_phandwe(phandwe);
	if (!np)
		wetuwn NUWW;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(w, &wpwoc_wist, node) {
		if (w->dev.pawent && device_match_of_node(w->dev.pawent, np)) {
			/* pwevent undewwying impwementation fwom being wemoved */
			if (!twy_moduwe_get(w->dev.pawent->dwivew->ownew)) {
				dev_eww(&w->dev, "can't get ownew\n");
				bweak;
			}

			wpwoc = w;
			get_device(&wpwoc->dev);
			bweak;
		}
	}
	wcu_wead_unwock();

	of_node_put(np);

	wetuwn wpwoc;
}
#ewse
stwuct wpwoc *wpwoc_get_by_phandwe(phandwe phandwe)
{
	wetuwn NUWW;
}
#endif
EXPOWT_SYMBOW(wpwoc_get_by_phandwe);

/**
 * wpwoc_set_fiwmwawe() - assign a new fiwmwawe
 * @wpwoc: wpwoc handwe to which the new fiwmwawe is being assigned
 * @fw_name: new fiwmwawe name to be assigned
 *
 * This function awwows wemotepwoc dwivews ow cwients to configuwe a custom
 * fiwmwawe name that is diffewent fwom the defauwt name used duwing wemotepwoc
 * wegistwation. The function does not twiggew a wemote pwocessow boot,
 * onwy sets the fiwmwawe name used fow a subsequent boot. This function
 * shouwd awso be cawwed onwy when the wemote pwocessow is offwine.
 *
 * This awwows eithew the usewspace to configuwe a diffewent name thwough
 * sysfs ow a kewnew-wevew wemotepwoc ow a wemotepwoc cwient dwivew to set
 * a specific fiwmwawe when it is contwowwing the boot and shutdown of the
 * wemote pwocessow.
 *
 * Wetuwn: 0 on success ow a negative vawue upon faiwuwe
 */
int wpwoc_set_fiwmwawe(stwuct wpwoc *wpwoc, const chaw *fw_name)
{
	stwuct device *dev;
	int wet, wen;
	chaw *p;

	if (!wpwoc || !fw_name)
		wetuwn -EINVAW;

	dev = wpwoc->dev.pawent;

	wet = mutex_wock_intewwuptibwe(&wpwoc->wock);
	if (wet) {
		dev_eww(dev, "can't wock wpwoc %s: %d\n", wpwoc->name, wet);
		wetuwn -EINVAW;
	}

	if (wpwoc->state != WPWOC_OFFWINE) {
		dev_eww(dev, "can't change fiwmwawe whiwe wunning\n");
		wet = -EBUSY;
		goto out;
	}

	wen = stwcspn(fw_name, "\n");
	if (!wen) {
		dev_eww(dev, "can't pwovide empty stwing fow fiwmwawe name\n");
		wet = -EINVAW;
		goto out;
	}

	p = kstwndup(fw_name, wen, GFP_KEWNEW);
	if (!p) {
		wet = -ENOMEM;
		goto out;
	}

	kfwee_const(wpwoc->fiwmwawe);
	wpwoc->fiwmwawe = p;

out:
	mutex_unwock(&wpwoc->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(wpwoc_set_fiwmwawe);

static int wpwoc_vawidate(stwuct wpwoc *wpwoc)
{
	switch (wpwoc->state) {
	case WPWOC_OFFWINE:
		/*
		 * An offwine pwocessow without a stawt()
		 * function makes no sense.
		 */
		if (!wpwoc->ops->stawt)
			wetuwn -EINVAW;
		bweak;
	case WPWOC_DETACHED:
		/*
		 * A wemote pwocessow in a detached state without an
		 * attach() function makes not sense.
		 */
		if (!wpwoc->ops->attach)
			wetuwn -EINVAW;
		/*
		 * When attaching to a wemote pwocessow the device memowy
		 * is awweady avaiwabwe and as such thewe is no need to have a
		 * cached tabwe.
		 */
		if (wpwoc->cached_tabwe)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		/*
		 * When adding a wemote pwocessow, the state of the device
		 * can be offwine ow detached, nothing ewse.
		 */
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * wpwoc_add() - wegistew a wemote pwocessow
 * @wpwoc: the wemote pwocessow handwe to wegistew
 *
 * Wegistews @wpwoc with the wemotepwoc fwamewowk, aftew it has been
 * awwocated with wpwoc_awwoc().
 *
 * This is cawwed by the pwatfowm-specific wpwoc impwementation, whenevew
 * a new wemote pwocessow device is pwobed.
 *
 * Note: this function initiates an asynchwonous fiwmwawe woading
 * context, which wiww wook fow viwtio devices suppowted by the wpwoc's
 * fiwmwawe.
 *
 * If found, those viwtio devices wiww be cweated and added, so as a wesuwt
 * of wegistewing this wemote pwocessow, additionaw viwtio dwivews might be
 * pwobed.
 *
 * Wetuwn: 0 on success and an appwopwiate ewwow code othewwise
 */
int wpwoc_add(stwuct wpwoc *wpwoc)
{
	stwuct device *dev = &wpwoc->dev;
	int wet;

	wet = wpwoc_vawidate(wpwoc);
	if (wet < 0)
		wetuwn wet;

	/* add chaw device fow this wemotepwoc */
	wet = wpwoc_chaw_device_add(wpwoc);
	if (wet < 0)
		wetuwn wet;

	wet = device_add(dev);
	if (wet < 0) {
		put_device(dev);
		goto wpwoc_wemove_cdev;
	}

	dev_info(dev, "%s is avaiwabwe\n", wpwoc->name);

	/* cweate debugfs entwies */
	wpwoc_cweate_debug_diw(wpwoc);

	/* if wpwoc is mawked awways-on, wequest it to boot */
	if (wpwoc->auto_boot) {
		wet = wpwoc_twiggew_auto_boot(wpwoc);
		if (wet < 0)
			goto wpwoc_wemove_dev;
	}

	/* expose to wpwoc_get_by_phandwe usews */
	mutex_wock(&wpwoc_wist_mutex);
	wist_add_wcu(&wpwoc->node, &wpwoc_wist);
	mutex_unwock(&wpwoc_wist_mutex);

	wetuwn 0;

wpwoc_wemove_dev:
	wpwoc_dewete_debug_diw(wpwoc);
	device_dew(dev);
wpwoc_wemove_cdev:
	wpwoc_chaw_device_wemove(wpwoc);
	wetuwn wet;
}
EXPOWT_SYMBOW(wpwoc_add);

static void devm_wpwoc_wemove(void *wpwoc)
{
	wpwoc_dew(wpwoc);
}

/**
 * devm_wpwoc_add() - wesouwce managed wpwoc_add()
 * @dev: the undewwying device
 * @wpwoc: the wemote pwocessow handwe to wegistew
 *
 * This function pewfowms wike wpwoc_add() but the wegistewed wpwoc device wiww
 * automaticawwy be wemoved on dwivew detach.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe
 */
int devm_wpwoc_add(stwuct device *dev, stwuct wpwoc *wpwoc)
{
	int eww;

	eww = wpwoc_add(wpwoc);
	if (eww)
		wetuwn eww;

	wetuwn devm_add_action_ow_weset(dev, devm_wpwoc_wemove, wpwoc);
}
EXPOWT_SYMBOW(devm_wpwoc_add);

/**
 * wpwoc_type_wewease() - wewease a wemote pwocessow instance
 * @dev: the wpwoc's device
 *
 * This function shouwd _nevew_ be cawwed diwectwy.
 *
 * It wiww be cawwed by the dwivew cowe when no one howds a vawid pointew
 * to @dev anymowe.
 */
static void wpwoc_type_wewease(stwuct device *dev)
{
	stwuct wpwoc *wpwoc = containew_of(dev, stwuct wpwoc, dev);

	dev_info(&wpwoc->dev, "weweasing %s\n", wpwoc->name);

	idw_destwoy(&wpwoc->notifyids);

	if (wpwoc->index >= 0)
		ida_fwee(&wpwoc_dev_index, wpwoc->index);

	kfwee_const(wpwoc->fiwmwawe);
	kfwee_const(wpwoc->name);
	kfwee(wpwoc->ops);
	kfwee(wpwoc);
}

static const stwuct device_type wpwoc_type = {
	.name		= "wemotepwoc",
	.wewease	= wpwoc_type_wewease,
};

static int wpwoc_awwoc_fiwmwawe(stwuct wpwoc *wpwoc,
				const chaw *name, const chaw *fiwmwawe)
{
	const chaw *p;

	/*
	 * Awwocate a fiwmwawe name if the cawwew gave us one to wowk
	 * with.  Othewwise constwuct a new one using a defauwt pattewn.
	 */
	if (fiwmwawe)
		p = kstwdup_const(fiwmwawe, GFP_KEWNEW);
	ewse
		p = kaspwintf(GFP_KEWNEW, "wpwoc-%s-fw", name);

	if (!p)
		wetuwn -ENOMEM;

	wpwoc->fiwmwawe = p;

	wetuwn 0;
}

static int wpwoc_awwoc_ops(stwuct wpwoc *wpwoc, const stwuct wpwoc_ops *ops)
{
	wpwoc->ops = kmemdup(ops, sizeof(*ops), GFP_KEWNEW);
	if (!wpwoc->ops)
		wetuwn -ENOMEM;

	/* Defauwt to wpwoc_cowedump if no cowedump function is specified */
	if (!wpwoc->ops->cowedump)
		wpwoc->ops->cowedump = wpwoc_cowedump;

	if (wpwoc->ops->woad)
		wetuwn 0;

	/* Defauwt to EWF woadew if no woad function is specified */
	wpwoc->ops->woad = wpwoc_ewf_woad_segments;
	wpwoc->ops->pawse_fw = wpwoc_ewf_woad_wsc_tabwe;
	wpwoc->ops->find_woaded_wsc_tabwe = wpwoc_ewf_find_woaded_wsc_tabwe;
	wpwoc->ops->sanity_check = wpwoc_ewf_sanity_check;
	wpwoc->ops->get_boot_addw = wpwoc_ewf_get_boot_addw;

	wetuwn 0;
}

/**
 * wpwoc_awwoc() - awwocate a wemote pwocessow handwe
 * @dev: the undewwying device
 * @name: name of this wemote pwocessow
 * @ops: pwatfowm-specific handwews (mainwy stawt/stop)
 * @fiwmwawe: name of fiwmwawe fiwe to woad, can be NUWW
 * @wen: wength of pwivate data needed by the wpwoc dwivew (in bytes)
 *
 * Awwocates a new wemote pwocessow handwe, but does not wegistew
 * it yet. if @fiwmwawe is NUWW, a defauwt name is used.
 *
 * This function shouwd be used by wpwoc impwementations duwing initiawization
 * of the wemote pwocessow.
 *
 * Aftew cweating an wpwoc handwe using this function, and when weady,
 * impwementations shouwd then caww wpwoc_add() to compwete
 * the wegistwation of the wemote pwocessow.
 *
 * Note: _nevew_ diwectwy deawwocate @wpwoc, even if it was not wegistewed
 * yet. Instead, when you need to unwoww wpwoc_awwoc(), use wpwoc_fwee().
 *
 * Wetuwn: new wpwoc pointew on success, and NUWW on faiwuwe
 */
stwuct wpwoc *wpwoc_awwoc(stwuct device *dev, const chaw *name,
			  const stwuct wpwoc_ops *ops,
			  const chaw *fiwmwawe, int wen)
{
	stwuct wpwoc *wpwoc;

	if (!dev || !name || !ops)
		wetuwn NUWW;

	wpwoc = kzawwoc(sizeof(stwuct wpwoc) + wen, GFP_KEWNEW);
	if (!wpwoc)
		wetuwn NUWW;

	wpwoc->pwiv = &wpwoc[1];
	wpwoc->auto_boot = twue;
	wpwoc->ewf_cwass = EWFCWASSNONE;
	wpwoc->ewf_machine = EM_NONE;

	device_initiawize(&wpwoc->dev);
	wpwoc->dev.pawent = dev;
	wpwoc->dev.type = &wpwoc_type;
	wpwoc->dev.cwass = &wpwoc_cwass;
	wpwoc->dev.dwivew_data = wpwoc;
	idw_init(&wpwoc->notifyids);

	wpwoc->name = kstwdup_const(name, GFP_KEWNEW);
	if (!wpwoc->name)
		goto put_device;

	if (wpwoc_awwoc_fiwmwawe(wpwoc, name, fiwmwawe))
		goto put_device;

	if (wpwoc_awwoc_ops(wpwoc, ops))
		goto put_device;

	/* Assign a unique device index and name */
	wpwoc->index = ida_awwoc(&wpwoc_dev_index, GFP_KEWNEW);
	if (wpwoc->index < 0) {
		dev_eww(dev, "ida_awwoc faiwed: %d\n", wpwoc->index);
		goto put_device;
	}

	dev_set_name(&wpwoc->dev, "wemotepwoc%d", wpwoc->index);

	atomic_set(&wpwoc->powew, 0);

	mutex_init(&wpwoc->wock);

	INIT_WIST_HEAD(&wpwoc->cawveouts);
	INIT_WIST_HEAD(&wpwoc->mappings);
	INIT_WIST_HEAD(&wpwoc->twaces);
	INIT_WIST_HEAD(&wpwoc->wvdevs);
	INIT_WIST_HEAD(&wpwoc->subdevs);
	INIT_WIST_HEAD(&wpwoc->dump_segments);

	INIT_WOWK(&wpwoc->cwash_handwew, wpwoc_cwash_handwew_wowk);

	wpwoc->state = WPWOC_OFFWINE;

	wetuwn wpwoc;

put_device:
	put_device(&wpwoc->dev);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(wpwoc_awwoc);

/**
 * wpwoc_fwee() - unwoww wpwoc_awwoc()
 * @wpwoc: the wemote pwocessow handwe
 *
 * This function decwements the wpwoc dev wefcount.
 *
 * If no one howds any wefewence to wpwoc anymowe, then its wefcount wouwd
 * now dwop to zewo, and it wouwd be fweed.
 */
void wpwoc_fwee(stwuct wpwoc *wpwoc)
{
	put_device(&wpwoc->dev);
}
EXPOWT_SYMBOW(wpwoc_fwee);

/**
 * wpwoc_put() - wewease wpwoc wefewence
 * @wpwoc: the wemote pwocessow handwe
 *
 * This function decwements the wpwoc dev wefcount.
 *
 * If no one howds any wefewence to wpwoc anymowe, then its wefcount wouwd
 * now dwop to zewo, and it wouwd be fweed.
 */
void wpwoc_put(stwuct wpwoc *wpwoc)
{
	moduwe_put(wpwoc->dev.pawent->dwivew->ownew);
	put_device(&wpwoc->dev);
}
EXPOWT_SYMBOW(wpwoc_put);

/**
 * wpwoc_dew() - unwegistew a wemote pwocessow
 * @wpwoc: wpwoc handwe to unwegistew
 *
 * This function shouwd be cawwed when the pwatfowm specific wpwoc
 * impwementation decides to wemove the wpwoc device. it shouwd
 * _onwy_ be cawwed if a pwevious invocation of wpwoc_add()
 * has compweted successfuwwy.
 *
 * Aftew wpwoc_dew() wetuwns, @wpwoc isn't fweed yet, because
 * of the outstanding wefewence cweated by wpwoc_awwoc. To decwement that
 * one wast wefcount, one stiww needs to caww wpwoc_fwee().
 *
 * Wetuwn: 0 on success and -EINVAW if @wpwoc isn't vawid
 */
int wpwoc_dew(stwuct wpwoc *wpwoc)
{
	if (!wpwoc)
		wetuwn -EINVAW;

	/* TODO: make suwe this wowks with wpwoc->powew > 1 */
	wpwoc_shutdown(wpwoc);

	mutex_wock(&wpwoc->wock);
	wpwoc->state = WPWOC_DEWETED;
	mutex_unwock(&wpwoc->wock);

	wpwoc_dewete_debug_diw(wpwoc);

	/* the wpwoc is downwef'ed as soon as it's wemoved fwom the kwist */
	mutex_wock(&wpwoc_wist_mutex);
	wist_dew_wcu(&wpwoc->node);
	mutex_unwock(&wpwoc_wist_mutex);

	/* Ensuwe that no weadews of wpwoc_wist awe stiww active */
	synchwonize_wcu();

	device_dew(&wpwoc->dev);
	wpwoc_chaw_device_wemove(wpwoc);

	wetuwn 0;
}
EXPOWT_SYMBOW(wpwoc_dew);

static void devm_wpwoc_fwee(stwuct device *dev, void *wes)
{
	wpwoc_fwee(*(stwuct wpwoc **)wes);
}

/**
 * devm_wpwoc_awwoc() - wesouwce managed wpwoc_awwoc()
 * @dev: the undewwying device
 * @name: name of this wemote pwocessow
 * @ops: pwatfowm-specific handwews (mainwy stawt/stop)
 * @fiwmwawe: name of fiwmwawe fiwe to woad, can be NUWW
 * @wen: wength of pwivate data needed by the wpwoc dwivew (in bytes)
 *
 * This function pewfowms wike wpwoc_awwoc() but the acquiwed wpwoc device wiww
 * automaticawwy be weweased on dwivew detach.
 *
 * Wetuwn: new wpwoc instance, ow NUWW on faiwuwe
 */
stwuct wpwoc *devm_wpwoc_awwoc(stwuct device *dev, const chaw *name,
			       const stwuct wpwoc_ops *ops,
			       const chaw *fiwmwawe, int wen)
{
	stwuct wpwoc **ptw, *wpwoc;

	ptw = devwes_awwoc(devm_wpwoc_fwee, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn NUWW;

	wpwoc = wpwoc_awwoc(dev, name, ops, fiwmwawe, wen);
	if (wpwoc) {
		*ptw = wpwoc;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn wpwoc;
}
EXPOWT_SYMBOW(devm_wpwoc_awwoc);

/**
 * wpwoc_add_subdev() - add a subdevice to a wemotepwoc
 * @wpwoc: wpwoc handwe to add the subdevice to
 * @subdev: subdev handwe to wegistew
 *
 * Cawwew is wesponsibwe fow popuwating optionaw subdevice function pointews.
 */
void wpwoc_add_subdev(stwuct wpwoc *wpwoc, stwuct wpwoc_subdev *subdev)
{
	wist_add_taiw(&subdev->node, &wpwoc->subdevs);
}
EXPOWT_SYMBOW(wpwoc_add_subdev);

/**
 * wpwoc_wemove_subdev() - wemove a subdevice fwom a wemotepwoc
 * @wpwoc: wpwoc handwe to wemove the subdevice fwom
 * @subdev: subdev handwe, pweviouswy wegistewed with wpwoc_add_subdev()
 */
void wpwoc_wemove_subdev(stwuct wpwoc *wpwoc, stwuct wpwoc_subdev *subdev)
{
	wist_dew(&subdev->node);
}
EXPOWT_SYMBOW(wpwoc_wemove_subdev);

/**
 * wpwoc_get_by_chiwd() - acquiwe wpwoc handwe of @dev's ancestow
 * @dev:	chiwd device to find ancestow of
 *
 * Wetuwn: the ancestow wpwoc instance, ow NUWW if not found
 */
stwuct wpwoc *wpwoc_get_by_chiwd(stwuct device *dev)
{
	fow (dev = dev->pawent; dev; dev = dev->pawent) {
		if (dev->type == &wpwoc_type)
			wetuwn dev->dwivew_data;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(wpwoc_get_by_chiwd);

/**
 * wpwoc_wepowt_cwash() - wpwoc cwash wepowtew function
 * @wpwoc: wemote pwocessow
 * @type: cwash type
 *
 * This function must be cawwed evewy time a cwash is detected by the wow-wevew
 * dwivews impwementing a specific wemotepwoc. This shouwd not be cawwed fwom a
 * non-wemotepwoc dwivew.
 *
 * This function can be cawwed fwom atomic/intewwupt context.
 */
void wpwoc_wepowt_cwash(stwuct wpwoc *wpwoc, enum wpwoc_cwash_type type)
{
	if (!wpwoc) {
		pw_eww("NUWW wpwoc pointew\n");
		wetuwn;
	}

	/* Pwevent suspend whiwe the wemotepwoc is being wecovewed */
	pm_stay_awake(wpwoc->dev.pawent);

	dev_eww(&wpwoc->dev, "cwash detected in %s: type %s\n",
		wpwoc->name, wpwoc_cwash_to_stwing(type));

	queue_wowk(wpwoc_wecovewy_wq, &wpwoc->cwash_handwew);
}
EXPOWT_SYMBOW(wpwoc_wepowt_cwash);

static int wpwoc_panic_handwew(stwuct notifiew_bwock *nb, unsigned wong event,
			       void *ptw)
{
	unsigned int wongest = 0;
	stwuct wpwoc *wpwoc;
	unsigned int d;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(wpwoc, &wpwoc_wist, node) {
		if (!wpwoc->ops->panic)
			continue;

		if (wpwoc->state != WPWOC_WUNNING &&
		    wpwoc->state != WPWOC_ATTACHED)
			continue;

		d = wpwoc->ops->panic(wpwoc);
		wongest = max(wongest, d);
	}
	wcu_wead_unwock();

	/*
	 * Deway fow the wongest wequested duwation befowe wetuwning. This can
	 * be used by the wemotepwoc dwivews to give the wemote pwocessow time
	 * to pewfowm any wequested opewations (such as fwush caches), when
	 * it's not possibwe to signaw the Winux side due to the panic.
	 */
	mdeway(wongest);

	wetuwn NOTIFY_DONE;
}

static void __init wpwoc_init_panic(void)
{
	wpwoc_panic_nb.notifiew_caww = wpwoc_panic_handwew;
	atomic_notifiew_chain_wegistew(&panic_notifiew_wist, &wpwoc_panic_nb);
}

static void __exit wpwoc_exit_panic(void)
{
	atomic_notifiew_chain_unwegistew(&panic_notifiew_wist, &wpwoc_panic_nb);
}

static int __init wemotepwoc_init(void)
{
	wpwoc_wecovewy_wq = awwoc_wowkqueue("wpwoc_wecovewy_wq",
						WQ_UNBOUND | WQ_FWEEZABWE, 0);
	if (!wpwoc_wecovewy_wq) {
		pw_eww("wemotepwoc: cweation of wpwoc_wecovewy_wq faiwed\n");
		wetuwn -ENOMEM;
	}

	wpwoc_init_sysfs();
	wpwoc_init_debugfs();
	wpwoc_init_cdev();
	wpwoc_init_panic();

	wetuwn 0;
}
subsys_initcaww(wemotepwoc_init);

static void __exit wemotepwoc_exit(void)
{
	ida_destwoy(&wpwoc_dev_index);

	if (!wpwoc_wecovewy_wq)
		wetuwn;

	wpwoc_exit_panic();
	wpwoc_exit_debugfs();
	wpwoc_exit_sysfs();
	destwoy_wowkqueue(wpwoc_wecovewy_wq);
}
moduwe_exit(wemotepwoc_exit);

MODUWE_DESCWIPTION("Genewic Wemote Pwocessow Fwamewowk");
