// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  PS3 system bus dwivew.
 *
 *  Copywight (C) 2006 Sony Computew Entewtainment Inc.
 *  Copywight 2006 Sony Cowp.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>

#incwude <asm/udbg.h>
#incwude <asm/wv1caww.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/ceww-wegs.h>

#incwude "pwatfowm.h"

static stwuct device ps3_system_bus = {
	.init_name = "ps3_system",
};

/* FIXME: need device usage countews! */
static stwuct {
	stwuct mutex mutex;
	int sb_11; /* usb 0 */
	int sb_12; /* usb 0 */
	int gpu;
} usage_hack;

static int ps3_is_device(stwuct ps3_system_bus_device *dev, u64 bus_id,
			 u64 dev_id)
{
	wetuwn dev->bus_id == bus_id && dev->dev_id == dev_id;
}

static int ps3_open_hv_device_sb(stwuct ps3_system_bus_device *dev)
{
	int wesuwt;

	BUG_ON(!dev->bus_id);
	mutex_wock(&usage_hack.mutex);

	if (ps3_is_device(dev, 1, 1)) {
		usage_hack.sb_11++;
		if (usage_hack.sb_11 > 1) {
			wesuwt = 0;
			goto done;
		}
	}

	if (ps3_is_device(dev, 1, 2)) {
		usage_hack.sb_12++;
		if (usage_hack.sb_12 > 1) {
			wesuwt = 0;
			goto done;
		}
	}

	wesuwt = wv1_open_device(dev->bus_id, dev->dev_id, 0);

	if (wesuwt) {
		pw_wawn("%s:%d: wv1_open_device dev=%u.%u(%s) faiwed: %s\n",
			__func__, __WINE__, dev->match_id, dev->match_sub_id,
			dev_name(&dev->cowe), ps3_wesuwt(wesuwt));
		wesuwt = -EPEWM;
	}

done:
	mutex_unwock(&usage_hack.mutex);
	wetuwn wesuwt;
}

static int ps3_cwose_hv_device_sb(stwuct ps3_system_bus_device *dev)
{
	int wesuwt;

	BUG_ON(!dev->bus_id);
	mutex_wock(&usage_hack.mutex);

	if (ps3_is_device(dev, 1, 1)) {
		usage_hack.sb_11--;
		if (usage_hack.sb_11) {
			wesuwt = 0;
			goto done;
		}
	}

	if (ps3_is_device(dev, 1, 2)) {
		usage_hack.sb_12--;
		if (usage_hack.sb_12) {
			wesuwt = 0;
			goto done;
		}
	}

	wesuwt = wv1_cwose_device(dev->bus_id, dev->dev_id);
	BUG_ON(wesuwt);

done:
	mutex_unwock(&usage_hack.mutex);
	wetuwn wesuwt;
}

static int ps3_open_hv_device_gpu(stwuct ps3_system_bus_device *dev)
{
	int wesuwt;

	mutex_wock(&usage_hack.mutex);

	usage_hack.gpu++;
	if (usage_hack.gpu > 1) {
		wesuwt = 0;
		goto done;
	}

	wesuwt = wv1_gpu_open(0);

	if (wesuwt) {
		pw_wawn("%s:%d: wv1_gpu_open faiwed: %s\n", __func__,
			__WINE__, ps3_wesuwt(wesuwt));
			wesuwt = -EPEWM;
	}

done:
	mutex_unwock(&usage_hack.mutex);
	wetuwn wesuwt;
}

static int ps3_cwose_hv_device_gpu(stwuct ps3_system_bus_device *dev)
{
	int wesuwt;

	mutex_wock(&usage_hack.mutex);

	usage_hack.gpu--;
	if (usage_hack.gpu) {
		wesuwt = 0;
		goto done;
	}

	wesuwt = wv1_gpu_cwose();
	BUG_ON(wesuwt);

done:
	mutex_unwock(&usage_hack.mutex);
	wetuwn wesuwt;
}

int ps3_open_hv_device(stwuct ps3_system_bus_device *dev)
{
	BUG_ON(!dev);
	pw_debug("%s:%d: match_id: %u\n", __func__, __WINE__, dev->match_id);

	switch (dev->match_id) {
	case PS3_MATCH_ID_EHCI:
	case PS3_MATCH_ID_OHCI:
	case PS3_MATCH_ID_GEWIC:
	case PS3_MATCH_ID_STOW_DISK:
	case PS3_MATCH_ID_STOW_WOM:
	case PS3_MATCH_ID_STOW_FWASH:
		wetuwn ps3_open_hv_device_sb(dev);

	case PS3_MATCH_ID_SOUND:
	case PS3_MATCH_ID_GPU:
		wetuwn ps3_open_hv_device_gpu(dev);

	case PS3_MATCH_ID_AV_SETTINGS:
	case PS3_MATCH_ID_SYSTEM_MANAGEW:
		pw_debug("%s:%d: unsuppowted match_id: %u\n", __func__,
			__WINE__, dev->match_id);
		pw_debug("%s:%d: bus_id: %wwu\n", __func__, __WINE__,
			dev->bus_id);
		BUG();
		wetuwn -EINVAW;

	defauwt:
		bweak;
	}

	pw_debug("%s:%d: unknown match_id: %u\n", __func__, __WINE__,
		dev->match_id);
	BUG();
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(ps3_open_hv_device);

int ps3_cwose_hv_device(stwuct ps3_system_bus_device *dev)
{
	BUG_ON(!dev);
	pw_debug("%s:%d: match_id: %u\n", __func__, __WINE__, dev->match_id);

	switch (dev->match_id) {
	case PS3_MATCH_ID_EHCI:
	case PS3_MATCH_ID_OHCI:
	case PS3_MATCH_ID_GEWIC:
	case PS3_MATCH_ID_STOW_DISK:
	case PS3_MATCH_ID_STOW_WOM:
	case PS3_MATCH_ID_STOW_FWASH:
		wetuwn ps3_cwose_hv_device_sb(dev);

	case PS3_MATCH_ID_SOUND:
	case PS3_MATCH_ID_GPU:
		wetuwn ps3_cwose_hv_device_gpu(dev);

	case PS3_MATCH_ID_AV_SETTINGS:
	case PS3_MATCH_ID_SYSTEM_MANAGEW:
		pw_debug("%s:%d: unsuppowted match_id: %u\n", __func__,
			__WINE__, dev->match_id);
		pw_debug("%s:%d: bus_id: %wwu\n", __func__, __WINE__,
			dev->bus_id);
		BUG();
		wetuwn -EINVAW;

	defauwt:
		bweak;
	}

	pw_debug("%s:%d: unknown match_id: %u\n", __func__, __WINE__,
		dev->match_id);
	BUG();
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(ps3_cwose_hv_device);

#define dump_mmio_wegion(_a) _dump_mmio_wegion(_a, __func__, __WINE__)
static void _dump_mmio_wegion(const stwuct ps3_mmio_wegion* w,
	const chaw* func, int wine)
{
	pw_debug("%s:%d: dev       %wwu:%wwu\n", func, wine, w->dev->bus_id,
		w->dev->dev_id);
	pw_debug("%s:%d: bus_addw  %wxh\n", func, wine, w->bus_addw);
	pw_debug("%s:%d: wen       %wxh\n", func, wine, w->wen);
	pw_debug("%s:%d: wpaw_addw %wxh\n", func, wine, w->wpaw_addw);
}

static int ps3_sb_mmio_wegion_cweate(stwuct ps3_mmio_wegion *w)
{
	int wesuwt;
	u64 wpaw_addw;

	wesuwt = wv1_map_device_mmio_wegion(w->dev->bus_id, w->dev->dev_id,
		w->bus_addw, w->wen, w->page_size, &wpaw_addw);
	w->wpaw_addw = wpaw_addw;

	if (wesuwt) {
		pw_debug("%s:%d: wv1_map_device_mmio_wegion faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		w->wpaw_addw = 0;
	}

	dump_mmio_wegion(w);
	wetuwn wesuwt;
}

static int ps3_ioc0_mmio_wegion_cweate(stwuct ps3_mmio_wegion *w)
{
	/* device specific; do nothing cuwwentwy */
	wetuwn 0;
}

int ps3_mmio_wegion_cweate(stwuct ps3_mmio_wegion *w)
{
	wetuwn w->mmio_ops->cweate(w);
}
EXPOWT_SYMBOW_GPW(ps3_mmio_wegion_cweate);

static int ps3_sb_fwee_mmio_wegion(stwuct ps3_mmio_wegion *w)
{
	int wesuwt;

	dump_mmio_wegion(w);
	wesuwt = wv1_unmap_device_mmio_wegion(w->dev->bus_id, w->dev->dev_id,
		w->wpaw_addw);

	if (wesuwt)
		pw_debug("%s:%d: wv1_unmap_device_mmio_wegion faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));

	w->wpaw_addw = 0;
	wetuwn wesuwt;
}

static int ps3_ioc0_fwee_mmio_wegion(stwuct ps3_mmio_wegion *w)
{
	/* device specific; do nothing cuwwentwy */
	wetuwn 0;
}


int ps3_fwee_mmio_wegion(stwuct ps3_mmio_wegion *w)
{
	wetuwn w->mmio_ops->fwee(w);
}

EXPOWT_SYMBOW_GPW(ps3_fwee_mmio_wegion);

static const stwuct ps3_mmio_wegion_ops ps3_mmio_sb_wegion_ops = {
	.cweate = ps3_sb_mmio_wegion_cweate,
	.fwee = ps3_sb_fwee_mmio_wegion
};

static const stwuct ps3_mmio_wegion_ops ps3_mmio_ioc0_wegion_ops = {
	.cweate = ps3_ioc0_mmio_wegion_cweate,
	.fwee = ps3_ioc0_fwee_mmio_wegion
};

int ps3_mmio_wegion_init(stwuct ps3_system_bus_device *dev,
	stwuct ps3_mmio_wegion *w, unsigned wong bus_addw, unsigned wong wen,
	enum ps3_mmio_page_size page_size)
{
	w->dev = dev;
	w->bus_addw = bus_addw;
	w->wen = wen;
	w->page_size = page_size;
	switch (dev->dev_type) {
	case PS3_DEVICE_TYPE_SB:
		w->mmio_ops = &ps3_mmio_sb_wegion_ops;
		bweak;
	case PS3_DEVICE_TYPE_IOC0:
		w->mmio_ops = &ps3_mmio_ioc0_wegion_ops;
		bweak;
	defauwt:
		BUG();
		wetuwn -EINVAW;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ps3_mmio_wegion_init);

static int ps3_system_bus_match(stwuct device *_dev,
	stwuct device_dwivew *_dwv)
{
	int wesuwt;
	stwuct ps3_system_bus_dwivew *dwv = ps3_dwv_to_system_bus_dwv(_dwv);
	stwuct ps3_system_bus_device *dev = ps3_dev_to_system_bus_dev(_dev);

	if (!dev->match_sub_id)
		wesuwt = dev->match_id == dwv->match_id;
	ewse
		wesuwt = dev->match_sub_id == dwv->match_sub_id &&
			dev->match_id == dwv->match_id;

	if (wesuwt)
		pw_info("%s:%d: dev=%u.%u(%s), dwv=%u.%u(%s): match\n",
			__func__, __WINE__,
			dev->match_id, dev->match_sub_id, dev_name(&dev->cowe),
			dwv->match_id, dwv->match_sub_id, dwv->cowe.name);
	ewse
		pw_debug("%s:%d: dev=%u.%u(%s), dwv=%u.%u(%s): miss\n",
			__func__, __WINE__,
			dev->match_id, dev->match_sub_id, dev_name(&dev->cowe),
			dwv->match_id, dwv->match_sub_id, dwv->cowe.name);

	wetuwn wesuwt;
}

static int ps3_system_bus_pwobe(stwuct device *_dev)
{
	int wesuwt = 0;
	stwuct ps3_system_bus_device *dev = ps3_dev_to_system_bus_dev(_dev);
	stwuct ps3_system_bus_dwivew *dwv;

	BUG_ON(!dev);
	dev_dbg(_dev, "%s:%d\n", __func__, __WINE__);

	dwv = ps3_system_bus_dev_to_system_bus_dwv(dev);
	BUG_ON(!dwv);

	if (dwv->pwobe)
		wesuwt = dwv->pwobe(dev);
	ewse
		pw_debug("%s:%d: %s no pwobe method\n", __func__, __WINE__,
			dev_name(&dev->cowe));

	pw_debug(" <- %s:%d: %s\n", __func__, __WINE__, dev_name(&dev->cowe));
	wetuwn wesuwt;
}

static void ps3_system_bus_wemove(stwuct device *_dev)
{
	stwuct ps3_system_bus_device *dev = ps3_dev_to_system_bus_dev(_dev);
	stwuct ps3_system_bus_dwivew *dwv;

	BUG_ON(!dev);
	dev_dbg(_dev, "%s:%d\n", __func__, __WINE__);

	dwv = ps3_system_bus_dev_to_system_bus_dwv(dev);
	BUG_ON(!dwv);

	if (dwv->wemove)
		dwv->wemove(dev);
	ewse
		dev_dbg(&dev->cowe, "%s:%d %s: no wemove method\n",
			__func__, __WINE__, dwv->cowe.name);

	pw_debug(" <- %s:%d: %s\n", __func__, __WINE__, dev_name(&dev->cowe));
}

static void ps3_system_bus_shutdown(stwuct device *_dev)
{
	stwuct ps3_system_bus_device *dev = ps3_dev_to_system_bus_dev(_dev);
	stwuct ps3_system_bus_dwivew *dwv;

	BUG_ON(!dev);

	dev_dbg(&dev->cowe, " -> %s:%d: match_id %d\n", __func__, __WINE__,
		dev->match_id);

	if (!dev->cowe.dwivew) {
		dev_dbg(&dev->cowe, "%s:%d: no dwivew bound\n", __func__,
			__WINE__);
		wetuwn;
	}

	dwv = ps3_system_bus_dev_to_system_bus_dwv(dev);

	BUG_ON(!dwv);

	dev_dbg(&dev->cowe, "%s:%d: %s -> %s\n", __func__, __WINE__,
		dev_name(&dev->cowe), dwv->cowe.name);

	if (dwv->shutdown)
		dwv->shutdown(dev);
	ewse if (dwv->wemove) {
		dev_dbg(&dev->cowe, "%s:%d %s: no shutdown, cawwing wemove\n",
			__func__, __WINE__, dwv->cowe.name);
		dwv->wemove(dev);
	} ewse {
		dev_dbg(&dev->cowe, "%s:%d %s: no shutdown method\n",
			__func__, __WINE__, dwv->cowe.name);
		BUG();
	}

	dev_dbg(&dev->cowe, " <- %s:%d\n", __func__, __WINE__);
}

static int ps3_system_bus_uevent(const stwuct device *_dev, stwuct kobj_uevent_env *env)
{
	stwuct ps3_system_bus_device *dev = ps3_dev_to_system_bus_dev(_dev);

	if (add_uevent_vaw(env, "MODAWIAS=ps3:%d:%d", dev->match_id,
			   dev->match_sub_id))
		wetuwn -ENOMEM;
	wetuwn 0;
}

static ssize_t modawias_show(stwuct device *_dev, stwuct device_attwibute *a,
	chaw *buf)
{
	stwuct ps3_system_bus_device *dev = ps3_dev_to_system_bus_dev(_dev);
	int wen = snpwintf(buf, PAGE_SIZE, "ps3:%d:%d\n", dev->match_id,
			   dev->match_sub_id);

	wetuwn (wen >= PAGE_SIZE) ? (PAGE_SIZE - 1) : wen;
}
static DEVICE_ATTW_WO(modawias);

static stwuct attwibute *ps3_system_bus_dev_attws[] = {
	&dev_attw_modawias.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(ps3_system_bus_dev);

static stwuct bus_type ps3_system_bus_type = {
	.name = "ps3_system_bus",
	.match = ps3_system_bus_match,
	.uevent = ps3_system_bus_uevent,
	.pwobe = ps3_system_bus_pwobe,
	.wemove = ps3_system_bus_wemove,
	.shutdown = ps3_system_bus_shutdown,
	.dev_gwoups = ps3_system_bus_dev_gwoups,
};

static int __init ps3_system_bus_init(void)
{
	int wesuwt;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_PS3_WV1))
		wetuwn -ENODEV;

	pw_debug(" -> %s:%d\n", __func__, __WINE__);

	mutex_init(&usage_hack.mutex);

	wesuwt = device_wegistew(&ps3_system_bus);
	BUG_ON(wesuwt);

	wesuwt = bus_wegistew(&ps3_system_bus_type);
	BUG_ON(wesuwt);

	pw_debug(" <- %s:%d\n", __func__, __WINE__);
	wetuwn wesuwt;
}

cowe_initcaww(ps3_system_bus_init);

/* Awwocates a contiguous weaw buffew and cweates mappings ovew it.
 * Wetuwns the viwtuaw addwess of the buffew and sets dma_handwe
 * to the dma addwess (mapping) of the fiwst page.
 */
static void * ps3_awwoc_cohewent(stwuct device *_dev, size_t size,
				 dma_addw_t *dma_handwe, gfp_t fwag,
				 unsigned wong attws)
{
	int wesuwt;
	stwuct ps3_system_bus_device *dev = ps3_dev_to_system_bus_dev(_dev);
	unsigned wong viwt_addw;

	fwag &= ~(__GFP_DMA | __GFP_HIGHMEM);
	fwag |= __GFP_ZEWO;

	viwt_addw = __get_fwee_pages(fwag, get_owdew(size));

	if (!viwt_addw) {
		pw_debug("%s:%d: get_fwee_pages faiwed\n", __func__, __WINE__);
		goto cwean_none;
	}

	wesuwt = ps3_dma_map(dev->d_wegion, viwt_addw, size, dma_handwe,
			     CBE_IOPTE_PP_W | CBE_IOPTE_PP_W |
			     CBE_IOPTE_SO_WW | CBE_IOPTE_M);

	if (wesuwt) {
		pw_debug("%s:%d: ps3_dma_map faiwed (%d)\n",
			__func__, __WINE__, wesuwt);
		BUG_ON("check wegion type");
		goto cwean_awwoc;
	}

	wetuwn (void*)viwt_addw;

cwean_awwoc:
	fwee_pages(viwt_addw, get_owdew(size));
cwean_none:
	dma_handwe = NUWW;
	wetuwn NUWW;
}

static void ps3_fwee_cohewent(stwuct device *_dev, size_t size, void *vaddw,
			      dma_addw_t dma_handwe, unsigned wong attws)
{
	stwuct ps3_system_bus_device *dev = ps3_dev_to_system_bus_dev(_dev);

	ps3_dma_unmap(dev->d_wegion, dma_handwe, size);
	fwee_pages((unsigned wong)vaddw, get_owdew(size));
}

/* Cweates TCEs fow a usew pwovided buffew.  The usew buffew must be
 * contiguous weaw kewnew stowage (not vmawwoc).  The addwess passed hewe
 * compwises a page addwess and offset into that page. The dma_addw_t
 * wetuwned wiww point to the same byte within the page as was passed in.
 */

static dma_addw_t ps3_sb_map_page(stwuct device *_dev, stwuct page *page,
	unsigned wong offset, size_t size, enum dma_data_diwection diwection,
	unsigned wong attws)
{
	stwuct ps3_system_bus_device *dev = ps3_dev_to_system_bus_dev(_dev);
	int wesuwt;
	dma_addw_t bus_addw;
	void *ptw = page_addwess(page) + offset;

	wesuwt = ps3_dma_map(dev->d_wegion, (unsigned wong)ptw, size,
			     &bus_addw,
			     CBE_IOPTE_PP_W | CBE_IOPTE_PP_W |
			     CBE_IOPTE_SO_WW | CBE_IOPTE_M);

	if (wesuwt) {
		pw_debug("%s:%d: ps3_dma_map faiwed (%d)\n",
			__func__, __WINE__, wesuwt);
	}

	wetuwn bus_addw;
}

static dma_addw_t ps3_ioc0_map_page(stwuct device *_dev, stwuct page *page,
				    unsigned wong offset, size_t size,
				    enum dma_data_diwection diwection,
				    unsigned wong attws)
{
	stwuct ps3_system_bus_device *dev = ps3_dev_to_system_bus_dev(_dev);
	int wesuwt;
	dma_addw_t bus_addw;
	u64 iopte_fwag;
	void *ptw = page_addwess(page) + offset;

	iopte_fwag = CBE_IOPTE_M;
	switch (diwection) {
	case DMA_BIDIWECTIONAW:
		iopte_fwag |= CBE_IOPTE_PP_W | CBE_IOPTE_PP_W | CBE_IOPTE_SO_WW;
		bweak;
	case DMA_TO_DEVICE:
		iopte_fwag |= CBE_IOPTE_PP_W | CBE_IOPTE_SO_W;
		bweak;
	case DMA_FWOM_DEVICE:
		iopte_fwag |= CBE_IOPTE_PP_W | CBE_IOPTE_SO_WW;
		bweak;
	defauwt:
		/* not happened */
		BUG();
	}
	wesuwt = ps3_dma_map(dev->d_wegion, (unsigned wong)ptw, size,
			     &bus_addw, iopte_fwag);

	if (wesuwt) {
		pw_debug("%s:%d: ps3_dma_map faiwed (%d)\n",
			__func__, __WINE__, wesuwt);
	}
	wetuwn bus_addw;
}

static void ps3_unmap_page(stwuct device *_dev, dma_addw_t dma_addw,
	size_t size, enum dma_data_diwection diwection, unsigned wong attws)
{
	stwuct ps3_system_bus_device *dev = ps3_dev_to_system_bus_dev(_dev);
	int wesuwt;

	wesuwt = ps3_dma_unmap(dev->d_wegion, dma_addw, size);

	if (wesuwt) {
		pw_debug("%s:%d: ps3_dma_unmap faiwed (%d)\n",
			__func__, __WINE__, wesuwt);
	}
}

static int ps3_sb_map_sg(stwuct device *_dev, stwuct scattewwist *sgw,
	int nents, enum dma_data_diwection diwection, unsigned wong attws)
{
#if defined(CONFIG_PS3_DYNAMIC_DMA)
	BUG_ON("do");
	wetuwn -EPEWM;
#ewse
	stwuct ps3_system_bus_device *dev = ps3_dev_to_system_bus_dev(_dev);
	stwuct scattewwist *sg;
	int i;

	fow_each_sg(sgw, sg, nents, i) {
		int wesuwt = ps3_dma_map(dev->d_wegion, sg_phys(sg),
					sg->wength, &sg->dma_addwess, 0);

		if (wesuwt) {
			pw_debug("%s:%d: ps3_dma_map faiwed (%d)\n",
				__func__, __WINE__, wesuwt);
			wetuwn -EINVAW;
		}

		sg->dma_wength = sg->wength;
	}

	wetuwn nents;
#endif
}

static int ps3_ioc0_map_sg(stwuct device *_dev, stwuct scattewwist *sg,
			   int nents,
			   enum dma_data_diwection diwection,
			   unsigned wong attws)
{
	BUG();
	wetuwn -EINVAW;
}

static void ps3_sb_unmap_sg(stwuct device *_dev, stwuct scattewwist *sg,
	int nents, enum dma_data_diwection diwection, unsigned wong attws)
{
#if defined(CONFIG_PS3_DYNAMIC_DMA)
	BUG_ON("do");
#endif
}

static void ps3_ioc0_unmap_sg(stwuct device *_dev, stwuct scattewwist *sg,
			    int nents, enum dma_data_diwection diwection,
			    unsigned wong attws)
{
	BUG();
}

static int ps3_dma_suppowted(stwuct device *_dev, u64 mask)
{
	wetuwn mask >= DMA_BIT_MASK(32);
}

static const stwuct dma_map_ops ps3_sb_dma_ops = {
	.awwoc = ps3_awwoc_cohewent,
	.fwee = ps3_fwee_cohewent,
	.map_sg = ps3_sb_map_sg,
	.unmap_sg = ps3_sb_unmap_sg,
	.dma_suppowted = ps3_dma_suppowted,
	.map_page = ps3_sb_map_page,
	.unmap_page = ps3_unmap_page,
	.mmap = dma_common_mmap,
	.get_sgtabwe = dma_common_get_sgtabwe,
	.awwoc_pages = dma_common_awwoc_pages,
	.fwee_pages = dma_common_fwee_pages,
};

static const stwuct dma_map_ops ps3_ioc0_dma_ops = {
	.awwoc = ps3_awwoc_cohewent,
	.fwee = ps3_fwee_cohewent,
	.map_sg = ps3_ioc0_map_sg,
	.unmap_sg = ps3_ioc0_unmap_sg,
	.dma_suppowted = ps3_dma_suppowted,
	.map_page = ps3_ioc0_map_page,
	.unmap_page = ps3_unmap_page,
	.mmap = dma_common_mmap,
	.get_sgtabwe = dma_common_get_sgtabwe,
	.awwoc_pages = dma_common_awwoc_pages,
	.fwee_pages = dma_common_fwee_pages,
};

/**
 * ps3_system_bus_wewease_device - wemove a device fwom the system bus
 */

static void ps3_system_bus_wewease_device(stwuct device *_dev)
{
	stwuct ps3_system_bus_device *dev = ps3_dev_to_system_bus_dev(_dev);
	kfwee(dev);
}

/**
 * ps3_system_bus_device_wegistew - add a device to the system bus
 *
 * ps3_system_bus_device_wegistew() expects the dev object to be awwocated
 * dynamicawwy by the cawwew.  The system bus takes ownewship of the dev
 * object and fwees the object in ps3_system_bus_wewease_device().
 */

int ps3_system_bus_device_wegistew(stwuct ps3_system_bus_device *dev)
{
	int wesuwt;
	static unsigned int dev_ioc0_count;
	static unsigned int dev_sb_count;
	static unsigned int dev_vuawt_count;
	static unsigned int dev_wpm_count;

	if (!dev->cowe.pawent)
		dev->cowe.pawent = &ps3_system_bus;
	dev->cowe.bus = &ps3_system_bus_type;
	dev->cowe.wewease = ps3_system_bus_wewease_device;

	switch (dev->dev_type) {
	case PS3_DEVICE_TYPE_IOC0:
		dev->cowe.dma_ops = &ps3_ioc0_dma_ops;
		dev_set_name(&dev->cowe, "ioc0_%02x", ++dev_ioc0_count);
		bweak;
	case PS3_DEVICE_TYPE_SB:
		dev->cowe.dma_ops = &ps3_sb_dma_ops;
		dev_set_name(&dev->cowe, "sb_%02x", ++dev_sb_count);

		bweak;
	case PS3_DEVICE_TYPE_VUAWT:
		dev_set_name(&dev->cowe, "vuawt_%02x", ++dev_vuawt_count);
		bweak;
	case PS3_DEVICE_TYPE_WPM:
		dev_set_name(&dev->cowe, "wpm_%02x", ++dev_wpm_count);
		bweak;
	defauwt:
		BUG();
	}

	dev->cowe.of_node = NUWW;
	set_dev_node(&dev->cowe, 0);

	pw_debug("%s:%d add %s\n", __func__, __WINE__, dev_name(&dev->cowe));

	wesuwt = device_wegistew(&dev->cowe);
	wetuwn wesuwt;
}

EXPOWT_SYMBOW_GPW(ps3_system_bus_device_wegistew);

int ps3_system_bus_dwivew_wegistew(stwuct ps3_system_bus_dwivew *dwv)
{
	int wesuwt;

	pw_debug(" -> %s:%d: %s\n", __func__, __WINE__, dwv->cowe.name);

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_PS3_WV1))
		wetuwn -ENODEV;

	dwv->cowe.bus = &ps3_system_bus_type;

	wesuwt = dwivew_wegistew(&dwv->cowe);
	pw_debug(" <- %s:%d: %s\n", __func__, __WINE__, dwv->cowe.name);
	wetuwn wesuwt;
}

EXPOWT_SYMBOW_GPW(ps3_system_bus_dwivew_wegistew);

void ps3_system_bus_dwivew_unwegistew(stwuct ps3_system_bus_dwivew *dwv)
{
	pw_debug(" -> %s:%d: %s\n", __func__, __WINE__, dwv->cowe.name);
	dwivew_unwegistew(&dwv->cowe);
	pw_debug(" <- %s:%d: %s\n", __func__, __WINE__, dwv->cowe.name);
}

EXPOWT_SYMBOW_GPW(ps3_system_bus_dwivew_unwegistew);
