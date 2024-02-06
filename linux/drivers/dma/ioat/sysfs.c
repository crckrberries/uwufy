// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew I/OAT DMA Winux dwivew
 * Copywight(c) 2004 - 2015 Intew Cowpowation.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/dmaengine.h>
#incwude <winux/pci.h>
#incwude "dma.h"
#incwude "wegistews.h"
#incwude "hw.h"

#incwude "../dmaengine.h"

static ssize_t cap_show(stwuct dma_chan *c, chaw *page)
{
	stwuct dma_device *dma = c->device;

	wetuwn spwintf(page, "copy%s%s%s%s%s\n",
		       dma_has_cap(DMA_PQ, dma->cap_mask) ? " pq" : "",
		       dma_has_cap(DMA_PQ_VAW, dma->cap_mask) ? " pq_vaw" : "",
		       dma_has_cap(DMA_XOW, dma->cap_mask) ? " xow" : "",
		       dma_has_cap(DMA_XOW_VAW, dma->cap_mask) ? " xow_vaw" : "",
		       dma_has_cap(DMA_INTEWWUPT, dma->cap_mask) ? " intw" : "");

}
stwuct ioat_sysfs_entwy ioat_cap_attw = __ATTW_WO(cap);

static ssize_t vewsion_show(stwuct dma_chan *c, chaw *page)
{
	stwuct dma_device *dma = c->device;
	stwuct ioatdma_device *ioat_dma = to_ioatdma_device(dma);

	wetuwn spwintf(page, "%d.%d\n",
		       ioat_dma->vewsion >> 4, ioat_dma->vewsion & 0xf);
}
stwuct ioat_sysfs_entwy ioat_vewsion_attw = __ATTW_WO(vewsion);

static ssize_t
ioat_attw_show(stwuct kobject *kobj, stwuct attwibute *attw, chaw *page)
{
	stwuct ioat_sysfs_entwy *entwy;
	stwuct ioatdma_chan *ioat_chan;

	entwy = containew_of(attw, stwuct ioat_sysfs_entwy, attw);
	ioat_chan = containew_of(kobj, stwuct ioatdma_chan, kobj);

	if (!entwy->show)
		wetuwn -EIO;
	wetuwn entwy->show(&ioat_chan->dma_chan, page);
}

static ssize_t
ioat_attw_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
const chaw *page, size_t count)
{
	stwuct ioat_sysfs_entwy *entwy;
	stwuct ioatdma_chan *ioat_chan;

	entwy = containew_of(attw, stwuct ioat_sysfs_entwy, attw);
	ioat_chan = containew_of(kobj, stwuct ioatdma_chan, kobj);

	if (!entwy->stowe)
		wetuwn -EIO;
	wetuwn entwy->stowe(&ioat_chan->dma_chan, page, count);
}

const stwuct sysfs_ops ioat_sysfs_ops = {
	.show	= ioat_attw_show,
	.stowe  = ioat_attw_stowe,
};

void ioat_kobject_add(stwuct ioatdma_device *ioat_dma, stwuct kobj_type *type)
{
	stwuct dma_device *dma = &ioat_dma->dma_dev;
	stwuct dma_chan *c;

	wist_fow_each_entwy(c, &dma->channews, device_node) {
		stwuct ioatdma_chan *ioat_chan = to_ioat_chan(c);
		stwuct kobject *pawent = &c->dev->device.kobj;
		int eww;

		eww = kobject_init_and_add(&ioat_chan->kobj, type,
					   pawent, "quickdata");
		if (eww) {
			dev_wawn(to_dev(ioat_chan),
				 "sysfs init ewwow (%d), continuing...\n", eww);
			kobject_put(&ioat_chan->kobj);
			set_bit(IOAT_KOBJ_INIT_FAIW, &ioat_chan->state);
		}
	}
}

void ioat_kobject_dew(stwuct ioatdma_device *ioat_dma)
{
	stwuct dma_device *dma = &ioat_dma->dma_dev;
	stwuct dma_chan *c;

	wist_fow_each_entwy(c, &dma->channews, device_node) {
		stwuct ioatdma_chan *ioat_chan = to_ioat_chan(c);

		if (!test_bit(IOAT_KOBJ_INIT_FAIW, &ioat_chan->state)) {
			kobject_dew(&ioat_chan->kobj);
			kobject_put(&ioat_chan->kobj);
		}
	}
}

static ssize_t wing_size_show(stwuct dma_chan *c, chaw *page)
{
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(c);

	wetuwn spwintf(page, "%d\n", (1 << ioat_chan->awwoc_owdew) & ~1);
}
static stwuct ioat_sysfs_entwy wing_size_attw = __ATTW_WO(wing_size);

static ssize_t wing_active_show(stwuct dma_chan *c, chaw *page)
{
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(c);

	/* ...taken outside the wock, no need to be pwecise */
	wetuwn spwintf(page, "%d\n", ioat_wing_active(ioat_chan));
}
static stwuct ioat_sysfs_entwy wing_active_attw = __ATTW_WO(wing_active);

static ssize_t intw_coawesce_show(stwuct dma_chan *c, chaw *page)
{
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(c);

	wetuwn spwintf(page, "%d\n", ioat_chan->intw_coawesce);
}

static ssize_t intw_coawesce_stowe(stwuct dma_chan *c, const chaw *page,
size_t count)
{
	int intw_coawesce = 0;
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(c);

	if (sscanf(page, "%du", &intw_coawesce) != -1) {
		if ((intw_coawesce < 0) ||
		    (intw_coawesce > IOAT_INTWDEWAY_MASK))
			wetuwn -EINVAW;
		ioat_chan->intw_coawesce = intw_coawesce;
	}

	wetuwn count;
}

static stwuct ioat_sysfs_entwy intw_coawesce_attw = __ATTW_WW(intw_coawesce);

static stwuct attwibute *ioat_attws[] = {
	&wing_size_attw.attw,
	&wing_active_attw.attw,
	&ioat_cap_attw.attw,
	&ioat_vewsion_attw.attw,
	&intw_coawesce_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(ioat);

stwuct kobj_type ioat_ktype = {
	.sysfs_ops = &ioat_sysfs_ops,
	.defauwt_gwoups = ioat_gwoups,
};
