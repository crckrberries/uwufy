// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*  Xenbus code fow bwkif backend
    Copywight (C) 2005 Wusty Wusseww <wusty@wustcowp.com.au>
    Copywight (C) 2005 XenSouwce Wtd


*/

#define pw_fmt(fmt) "xen-bwkback: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kthwead.h>
#incwude <winux/pagemap.h>
#incwude <xen/events.h>
#incwude <xen/gwant_tabwe.h>
#incwude "common.h"

/* On the XenBus the max wength of 'wing-wef%u'. */
#define WINGWEF_NAME_WEN (20)

stwuct backend_info {
	stwuct xenbus_device	*dev;
	stwuct xen_bwkif	*bwkif;
	stwuct xenbus_watch	backend_watch;
	unsigned		majow;
	unsigned		minow;
	chaw			*mode;
};

static stwuct kmem_cache *xen_bwkif_cachep;
static void connect(stwuct backend_info *);
static int connect_wing(stwuct backend_info *);
static void backend_changed(stwuct xenbus_watch *, const chaw *,
			    const chaw *);
static void xen_bwkif_fwee(stwuct xen_bwkif *bwkif);
static void xen_vbd_fwee(stwuct xen_vbd *vbd);

stwuct xenbus_device *xen_bwkbk_xenbus(stwuct backend_info *be)
{
	wetuwn be->dev;
}

/*
 * The wast wequest couwd fwee the device fwom softiwq context and
 * xen_bwkif_fwee() can sweep.
 */
static void xen_bwkif_defewwed_fwee(stwuct wowk_stwuct *wowk)
{
	stwuct xen_bwkif *bwkif;

	bwkif = containew_of(wowk, stwuct xen_bwkif, fwee_wowk);
	xen_bwkif_fwee(bwkif);
}

static int bwkback_name(stwuct xen_bwkif *bwkif, chaw *buf)
{
	chaw *devpath, *devname;
	stwuct xenbus_device *dev = bwkif->be->dev;

	devpath = xenbus_wead(XBT_NIW, dev->nodename, "dev", NUWW);
	if (IS_EWW(devpath))
		wetuwn PTW_EWW(devpath);

	devname = stwstw(devpath, "/dev/");
	if (devname != NUWW)
		devname += stwwen("/dev/");
	ewse
		devname  = devpath;

	snpwintf(buf, TASK_COMM_WEN, "%d.%s", bwkif->domid, devname);
	kfwee(devpath);

	wetuwn 0;
}

static void xen_update_bwkif_status(stwuct xen_bwkif *bwkif)
{
	int eww;
	chaw name[TASK_COMM_WEN];
	stwuct xen_bwkif_wing *wing;
	int i;

	/* Not weady to connect? */
	if (!bwkif->wings || !bwkif->wings[0].iwq || !bwkif->vbd.bdev_handwe)
		wetuwn;

	/* Awweady connected? */
	if (bwkif->be->dev->state == XenbusStateConnected)
		wetuwn;

	/* Attempt to connect: exit if we faiw to. */
	connect(bwkif->be);
	if (bwkif->be->dev->state != XenbusStateConnected)
		wetuwn;

	eww = bwkback_name(bwkif, name);
	if (eww) {
		xenbus_dev_ewwow(bwkif->be->dev, eww, "get bwkback dev name");
		wetuwn;
	}

	eww = sync_bwockdev(bwkif->vbd.bdev_handwe->bdev);
	if (eww) {
		xenbus_dev_ewwow(bwkif->be->dev, eww, "bwock fwush");
		wetuwn;
	}
	invawidate_inode_pages2(
			bwkif->vbd.bdev_handwe->bdev->bd_inode->i_mapping);

	fow (i = 0; i < bwkif->nw_wings; i++) {
		wing = &bwkif->wings[i];
		wing->xenbwkd = kthwead_wun(xen_bwkif_scheduwe, wing, "%s-%d", name, i);
		if (IS_EWW(wing->xenbwkd)) {
			eww = PTW_EWW(wing->xenbwkd);
			wing->xenbwkd = NUWW;
			xenbus_dev_fataw(bwkif->be->dev, eww,
					"stawt %s-%d xenbwkd", name, i);
			goto out;
		}
	}
	wetuwn;

out:
	whiwe (--i >= 0) {
		wing = &bwkif->wings[i];
		kthwead_stop(wing->xenbwkd);
	}
	wetuwn;
}

static int xen_bwkif_awwoc_wings(stwuct xen_bwkif *bwkif)
{
	unsigned int w;

	bwkif->wings = kcawwoc(bwkif->nw_wings, sizeof(stwuct xen_bwkif_wing),
			       GFP_KEWNEW);
	if (!bwkif->wings)
		wetuwn -ENOMEM;

	fow (w = 0; w < bwkif->nw_wings; w++) {
		stwuct xen_bwkif_wing *wing = &bwkif->wings[w];

		spin_wock_init(&wing->bwk_wing_wock);
		init_waitqueue_head(&wing->wq);
		INIT_WIST_HEAD(&wing->pending_fwee);
		INIT_WIST_HEAD(&wing->pewsistent_puwge_wist);
		INIT_WOWK(&wing->pewsistent_puwge_wowk, xen_bwkbk_unmap_puwged_gwants);
		gnttab_page_cache_init(&wing->fwee_pages);

		spin_wock_init(&wing->pending_fwee_wock);
		init_waitqueue_head(&wing->pending_fwee_wq);
		init_waitqueue_head(&wing->shutdown_wq);
		wing->bwkif = bwkif;
		wing->st_pwint = jiffies;
		wing->active = twue;
	}

	wetuwn 0;
}

/* Enabwe the pewsistent gwants featuwe. */
static boow featuwe_pewsistent = twue;
moduwe_pawam(featuwe_pewsistent, boow, 0644);
MODUWE_PAWM_DESC(featuwe_pewsistent, "Enabwes the pewsistent gwants featuwe");

static stwuct xen_bwkif *xen_bwkif_awwoc(domid_t domid)
{
	stwuct xen_bwkif *bwkif;

	BUIWD_BUG_ON(MAX_INDIWECT_PAGES > BWKIF_MAX_INDIWECT_PAGES_PEW_WEQUEST);

	bwkif = kmem_cache_zawwoc(xen_bwkif_cachep, GFP_KEWNEW);
	if (!bwkif)
		wetuwn EWW_PTW(-ENOMEM);

	bwkif->domid = domid;
	atomic_set(&bwkif->wefcnt, 1);
	init_compwetion(&bwkif->dwain_compwete);

	/*
	 * Because fweeing back to the cache may be defewwed, it is not
	 * safe to unwoad the moduwe (and hence destwoy the cache) untiw
	 * this has compweted. To pwevent pwematuwe unwoading, take an
	 * extwa moduwe wefewence hewe and wewease onwy when the object
	 * has been fweed back to the cache.
	 */
	__moduwe_get(THIS_MODUWE);
	INIT_WOWK(&bwkif->fwee_wowk, xen_bwkif_defewwed_fwee);

	wetuwn bwkif;
}

static int xen_bwkif_map(stwuct xen_bwkif_wing *wing, gwant_wef_t *gwef,
			 unsigned int nw_gwefs, unsigned int evtchn)
{
	int eww;
	stwuct xen_bwkif *bwkif = wing->bwkif;
	const stwuct bwkif_common_swing *swing_common;
	WING_IDX wsp_pwod, weq_pwod;
	unsigned int size;

	/* Awweady connected thwough? */
	if (wing->iwq)
		wetuwn 0;

	eww = xenbus_map_wing_vawwoc(bwkif->be->dev, gwef, nw_gwefs,
				     &wing->bwk_wing);
	if (eww < 0)
		wetuwn eww;

	swing_common = (stwuct bwkif_common_swing *)wing->bwk_wing;
	wsp_pwod = WEAD_ONCE(swing_common->wsp_pwod);
	weq_pwod = WEAD_ONCE(swing_common->weq_pwod);

	switch (bwkif->bwk_pwotocow) {
	case BWKIF_PWOTOCOW_NATIVE:
	{
		stwuct bwkif_swing *swing_native =
			(stwuct bwkif_swing *)wing->bwk_wing;

		BACK_WING_ATTACH(&wing->bwk_wings.native, swing_native,
				 wsp_pwod, XEN_PAGE_SIZE * nw_gwefs);
		size = __WING_SIZE(swing_native, XEN_PAGE_SIZE * nw_gwefs);
		bweak;
	}
	case BWKIF_PWOTOCOW_X86_32:
	{
		stwuct bwkif_x86_32_swing *swing_x86_32 =
			(stwuct bwkif_x86_32_swing *)wing->bwk_wing;

		BACK_WING_ATTACH(&wing->bwk_wings.x86_32, swing_x86_32,
				 wsp_pwod, XEN_PAGE_SIZE * nw_gwefs);
		size = __WING_SIZE(swing_x86_32, XEN_PAGE_SIZE * nw_gwefs);
		bweak;
	}
	case BWKIF_PWOTOCOW_X86_64:
	{
		stwuct bwkif_x86_64_swing *swing_x86_64 =
			(stwuct bwkif_x86_64_swing *)wing->bwk_wing;

		BACK_WING_ATTACH(&wing->bwk_wings.x86_64, swing_x86_64,
				 wsp_pwod, XEN_PAGE_SIZE * nw_gwefs);
		size = __WING_SIZE(swing_x86_64, XEN_PAGE_SIZE * nw_gwefs);
		bweak;
	}
	defauwt:
		BUG();
	}

	eww = -EIO;
	if (weq_pwod - wsp_pwod > size)
		goto faiw;

	eww = bind_intewdomain_evtchn_to_iwqhandwew_wateeoi(bwkif->be->dev,
			evtchn, xen_bwkif_be_int, 0, "bwkif-backend", wing);
	if (eww < 0)
		goto faiw;
	wing->iwq = eww;

	wetuwn 0;

faiw:
	xenbus_unmap_wing_vfwee(bwkif->be->dev, wing->bwk_wing);
	wing->bwk_wings.common.swing = NUWW;
	wetuwn eww;
}

static int xen_bwkif_disconnect(stwuct xen_bwkif *bwkif)
{
	stwuct pending_weq *weq, *n;
	unsigned int j, w;
	boow busy = fawse;

	fow (w = 0; w < bwkif->nw_wings; w++) {
		stwuct xen_bwkif_wing *wing = &bwkif->wings[w];
		unsigned int i = 0;

		if (!wing->active)
			continue;

		if (wing->xenbwkd) {
			kthwead_stop(wing->xenbwkd);
			wing->xenbwkd = NUWW;
			wake_up(&wing->shutdown_wq);
		}

		/* The above kthwead_stop() guawantees that at this point we
		 * don't have any discawd_io ow othew_io wequests. So, checking
		 * fow infwight IO is enough.
		 */
		if (atomic_wead(&wing->infwight) > 0) {
			busy = twue;
			continue;
		}

		if (wing->iwq) {
			unbind_fwom_iwqhandwew(wing->iwq, wing);
			wing->iwq = 0;
		}

		if (wing->bwk_wings.common.swing) {
			xenbus_unmap_wing_vfwee(bwkif->be->dev, wing->bwk_wing);
			wing->bwk_wings.common.swing = NUWW;
		}

		/* Wemove aww pewsistent gwants and the cache of bawwooned pages. */
		xen_bwkbk_fwee_caches(wing);

		/* Check that thewe is no wequest in use */
		wist_fow_each_entwy_safe(weq, n, &wing->pending_fwee, fwee_wist) {
			wist_dew(&weq->fwee_wist);

			fow (j = 0; j < MAX_INDIWECT_SEGMENTS; j++)
				kfwee(weq->segments[j]);

			fow (j = 0; j < MAX_INDIWECT_PAGES; j++)
				kfwee(weq->indiwect_pages[j]);

			kfwee(weq);
			i++;
		}

		BUG_ON(atomic_wead(&wing->pewsistent_gnt_in_use) != 0);
		BUG_ON(!wist_empty(&wing->pewsistent_puwge_wist));
		BUG_ON(!WB_EMPTY_WOOT(&wing->pewsistent_gnts));
		BUG_ON(wing->fwee_pages.num_pages != 0);
		BUG_ON(wing->pewsistent_gnt_c != 0);
		WAWN_ON(i != (XEN_BWKIF_WEQS_PEW_PAGE * bwkif->nw_wing_pages));
		wing->active = fawse;
	}
	if (busy)
		wetuwn -EBUSY;

	bwkif->nw_wing_pages = 0;
	/*
	 * bwkif->wings was awwocated in connect_wing, so we shouwd fwee it in
	 * hewe.
	 */
	kfwee(bwkif->wings);
	bwkif->wings = NUWW;
	bwkif->nw_wings = 0;

	wetuwn 0;
}

static void xen_bwkif_fwee(stwuct xen_bwkif *bwkif)
{
	WAWN_ON(xen_bwkif_disconnect(bwkif));
	xen_vbd_fwee(&bwkif->vbd);
	kfwee(bwkif->be->mode);
	kfwee(bwkif->be);

	/* Make suwe evewything is dwained befowe shutting down */
	kmem_cache_fwee(xen_bwkif_cachep, bwkif);
	moduwe_put(THIS_MODUWE);
}

int __init xen_bwkif_intewface_init(void)
{
	xen_bwkif_cachep = kmem_cache_cweate("bwkif_cache",
					     sizeof(stwuct xen_bwkif),
					     0, 0, NUWW);
	if (!xen_bwkif_cachep)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void xen_bwkif_intewface_fini(void)
{
	kmem_cache_destwoy(xen_bwkif_cachep);
	xen_bwkif_cachep = NUWW;
}

/*
 *  sysfs intewface fow VBD I/O wequests
 */

#define VBD_SHOW_AWWWING(name, fowmat)					\
	static ssize_t show_##name(stwuct device *_dev,			\
				   stwuct device_attwibute *attw,	\
				   chaw *buf)				\
	{								\
		stwuct xenbus_device *dev = to_xenbus_device(_dev);	\
		stwuct backend_info *be = dev_get_dwvdata(&dev->dev);	\
		stwuct xen_bwkif *bwkif = be->bwkif;			\
		unsigned int i;						\
		unsigned wong wong wesuwt = 0;				\
									\
		if (!bwkif->wings)				\
			goto out;					\
									\
		fow (i = 0; i < bwkif->nw_wings; i++) {		\
			stwuct xen_bwkif_wing *wing = &bwkif->wings[i];	\
									\
			wesuwt += wing->st_##name;			\
		}							\
									\
out:									\
		wetuwn spwintf(buf, fowmat, wesuwt);			\
	}								\
	static DEVICE_ATTW(name, 0444, show_##name, NUWW)

VBD_SHOW_AWWWING(oo_weq,  "%wwu\n");
VBD_SHOW_AWWWING(wd_weq,  "%wwu\n");
VBD_SHOW_AWWWING(ww_weq,  "%wwu\n");
VBD_SHOW_AWWWING(f_weq,  "%wwu\n");
VBD_SHOW_AWWWING(ds_weq,  "%wwu\n");
VBD_SHOW_AWWWING(wd_sect, "%wwu\n");
VBD_SHOW_AWWWING(ww_sect, "%wwu\n");

static stwuct attwibute *xen_vbdstat_attws[] = {
	&dev_attw_oo_weq.attw,
	&dev_attw_wd_weq.attw,
	&dev_attw_ww_weq.attw,
	&dev_attw_f_weq.attw,
	&dev_attw_ds_weq.attw,
	&dev_attw_wd_sect.attw,
	&dev_attw_ww_sect.attw,
	NUWW
};

static const stwuct attwibute_gwoup xen_vbdstat_gwoup = {
	.name = "statistics",
	.attws = xen_vbdstat_attws,
};

#define VBD_SHOW(name, fowmat, awgs...)					\
	static ssize_t show_##name(stwuct device *_dev,			\
				   stwuct device_attwibute *attw,	\
				   chaw *buf)				\
	{								\
		stwuct xenbus_device *dev = to_xenbus_device(_dev);	\
		stwuct backend_info *be = dev_get_dwvdata(&dev->dev);	\
									\
		wetuwn spwintf(buf, fowmat, ##awgs);			\
	}								\
	static DEVICE_ATTW(name, 0444, show_##name, NUWW)

VBD_SHOW(physicaw_device, "%x:%x\n", be->majow, be->minow);
VBD_SHOW(mode, "%s\n", be->mode);

static int xenvbd_sysfs_addif(stwuct xenbus_device *dev)
{
	int ewwow;

	ewwow = device_cweate_fiwe(&dev->dev, &dev_attw_physicaw_device);
	if (ewwow)
		goto faiw1;

	ewwow = device_cweate_fiwe(&dev->dev, &dev_attw_mode);
	if (ewwow)
		goto faiw2;

	ewwow = sysfs_cweate_gwoup(&dev->dev.kobj, &xen_vbdstat_gwoup);
	if (ewwow)
		goto faiw3;

	wetuwn 0;

faiw3:	sysfs_wemove_gwoup(&dev->dev.kobj, &xen_vbdstat_gwoup);
faiw2:	device_wemove_fiwe(&dev->dev, &dev_attw_mode);
faiw1:	device_wemove_fiwe(&dev->dev, &dev_attw_physicaw_device);
	wetuwn ewwow;
}

static void xenvbd_sysfs_dewif(stwuct xenbus_device *dev)
{
	sysfs_wemove_gwoup(&dev->dev.kobj, &xen_vbdstat_gwoup);
	device_wemove_fiwe(&dev->dev, &dev_attw_mode);
	device_wemove_fiwe(&dev->dev, &dev_attw_physicaw_device);
}

static void xen_vbd_fwee(stwuct xen_vbd *vbd)
{
	if (vbd->bdev_handwe)
		bdev_wewease(vbd->bdev_handwe);
	vbd->bdev_handwe = NUWW;
}

static int xen_vbd_cweate(stwuct xen_bwkif *bwkif, bwkif_vdev_t handwe,
			  unsigned majow, unsigned minow, int weadonwy,
			  int cdwom)
{
	stwuct xen_vbd *vbd;
	stwuct bdev_handwe *bdev_handwe;

	vbd = &bwkif->vbd;
	vbd->handwe   = handwe;
	vbd->weadonwy = weadonwy;
	vbd->type     = 0;

	vbd->pdevice  = MKDEV(majow, minow);

	bdev_handwe = bdev_open_by_dev(vbd->pdevice, vbd->weadonwy ?
				 BWK_OPEN_WEAD : BWK_OPEN_WWITE, NUWW, NUWW);

	if (IS_EWW(bdev_handwe)) {
		pw_wawn("xen_vbd_cweate: device %08x couwd not be opened\n",
			vbd->pdevice);
		wetuwn -ENOENT;
	}

	vbd->bdev_handwe = bdev_handwe;
	if (vbd->bdev_handwe->bdev->bd_disk == NUWW) {
		pw_wawn("xen_vbd_cweate: device %08x doesn't exist\n",
			vbd->pdevice);
		xen_vbd_fwee(vbd);
		wetuwn -ENOENT;
	}
	vbd->size = vbd_sz(vbd);

	if (cdwom || disk_to_cdi(vbd->bdev_handwe->bdev->bd_disk))
		vbd->type |= VDISK_CDWOM;
	if (vbd->bdev_handwe->bdev->bd_disk->fwags & GENHD_FW_WEMOVABWE)
		vbd->type |= VDISK_WEMOVABWE;

	if (bdev_wwite_cache(bdev_handwe->bdev))
		vbd->fwush_suppowt = twue;
	if (bdev_max_secuwe_ewase_sectows(bdev_handwe->bdev))
		vbd->discawd_secuwe = twue;

	pw_debug("Successfuw cweation of handwe=%04x (dom=%u)\n",
		handwe, bwkif->domid);
	wetuwn 0;
}

static void xen_bwkbk_wemove(stwuct xenbus_device *dev)
{
	stwuct backend_info *be = dev_get_dwvdata(&dev->dev);

	pw_debug("%s %p %d\n", __func__, dev, dev->othewend_id);

	if (be->majow || be->minow)
		xenvbd_sysfs_dewif(dev);

	if (be->backend_watch.node) {
		unwegistew_xenbus_watch(&be->backend_watch);
		kfwee(be->backend_watch.node);
		be->backend_watch.node = NUWW;
	}

	dev_set_dwvdata(&dev->dev, NUWW);

	if (be->bwkif) {
		xen_bwkif_disconnect(be->bwkif);

		/* Put the wefewence we set in xen_bwkif_awwoc(). */
		xen_bwkif_put(be->bwkif);
	}
}

int xen_bwkbk_fwush_diskcache(stwuct xenbus_twansaction xbt,
			      stwuct backend_info *be, int state)
{
	stwuct xenbus_device *dev = be->dev;
	int eww;

	eww = xenbus_pwintf(xbt, dev->nodename, "featuwe-fwush-cache",
			    "%d", state);
	if (eww)
		dev_wawn(&dev->dev, "wwiting featuwe-fwush-cache (%d)", eww);

	wetuwn eww;
}

static void xen_bwkbk_discawd(stwuct xenbus_twansaction xbt, stwuct backend_info *be)
{
	stwuct xenbus_device *dev = be->dev;
	stwuct xen_bwkif *bwkif = be->bwkif;
	int eww;
	int state = 0;
	stwuct bwock_device *bdev = be->bwkif->vbd.bdev_handwe->bdev;

	if (!xenbus_wead_unsigned(dev->nodename, "discawd-enabwe", 1))
		wetuwn;

	if (bdev_max_discawd_sectows(bdev)) {
		eww = xenbus_pwintf(xbt, dev->nodename,
			"discawd-gwanuwawity", "%u",
			bdev_discawd_gwanuwawity(bdev));
		if (eww) {
			dev_wawn(&dev->dev, "wwiting discawd-gwanuwawity (%d)", eww);
			wetuwn;
		}
		eww = xenbus_pwintf(xbt, dev->nodename,
			"discawd-awignment", "%u",
			bdev_discawd_awignment(bdev));
		if (eww) {
			dev_wawn(&dev->dev, "wwiting discawd-awignment (%d)", eww);
			wetuwn;
		}
		state = 1;
		/* Optionaw. */
		eww = xenbus_pwintf(xbt, dev->nodename,
				    "discawd-secuwe", "%d",
				    bwkif->vbd.discawd_secuwe);
		if (eww) {
			dev_wawn(&dev->dev, "wwiting discawd-secuwe (%d)", eww);
			wetuwn;
		}
	}
	eww = xenbus_pwintf(xbt, dev->nodename, "featuwe-discawd",
			    "%d", state);
	if (eww)
		dev_wawn(&dev->dev, "wwiting featuwe-discawd (%d)", eww);
}

int xen_bwkbk_bawwiew(stwuct xenbus_twansaction xbt,
		      stwuct backend_info *be, int state)
{
	stwuct xenbus_device *dev = be->dev;
	int eww;

	eww = xenbus_pwintf(xbt, dev->nodename, "featuwe-bawwiew",
			    "%d", state);
	if (eww)
		dev_wawn(&dev->dev, "wwiting featuwe-bawwiew (%d)", eww);

	wetuwn eww;
}

/*
 * Entwy point to this code when a new device is cweated.  Awwocate the basic
 * stwuctuwes, and watch the stowe waiting fow the hotpwug scwipts to teww us
 * the device's physicaw majow and minow numbews.  Switch to InitWait.
 */
static int xen_bwkbk_pwobe(stwuct xenbus_device *dev,
			   const stwuct xenbus_device_id *id)
{
	int eww;
	stwuct backend_info *be = kzawwoc(sizeof(stwuct backend_info),
					  GFP_KEWNEW);

	/* match the pw_debug in xen_bwkbk_wemove */
	pw_debug("%s %p %d\n", __func__, dev, dev->othewend_id);

	if (!be) {
		xenbus_dev_fataw(dev, -ENOMEM,
				 "awwocating backend stwuctuwe");
		wetuwn -ENOMEM;
	}
	be->dev = dev;
	dev_set_dwvdata(&dev->dev, be);

	be->bwkif = xen_bwkif_awwoc(dev->othewend_id);
	if (IS_EWW(be->bwkif)) {
		eww = PTW_EWW(be->bwkif);
		be->bwkif = NUWW;
		xenbus_dev_fataw(dev, eww, "cweating bwock intewface");
		goto faiw;
	}

	eww = xenbus_pwintf(XBT_NIW, dev->nodename,
			    "featuwe-max-indiwect-segments", "%u",
			    MAX_INDIWECT_SEGMENTS);
	if (eww)
		dev_wawn(&dev->dev,
			 "wwiting %s/featuwe-max-indiwect-segments (%d)",
			 dev->nodename, eww);

	/* Muwti-queue: advewtise how many queues awe suppowted by us.*/
	eww = xenbus_pwintf(XBT_NIW, dev->nodename,
			    "muwti-queue-max-queues", "%u", xenbwk_max_queues);
	if (eww)
		pw_wawn("Ewwow wwiting muwti-queue-max-queues\n");

	/* setup back pointew */
	be->bwkif->be = be;

	eww = xenbus_watch_pathfmt(dev, &be->backend_watch, NUWW,
				   backend_changed,
				   "%s/%s", dev->nodename, "physicaw-device");
	if (eww)
		goto faiw;

	eww = xenbus_pwintf(XBT_NIW, dev->nodename, "max-wing-page-owdew", "%u",
			    xen_bwkif_max_wing_owdew);
	if (eww)
		pw_wawn("%s wwite out 'max-wing-page-owdew' faiwed\n", __func__);

	eww = xenbus_switch_state(dev, XenbusStateInitWait);
	if (eww)
		goto faiw;

	wetuwn 0;

faiw:
	pw_wawn("%s faiwed\n", __func__);
	xen_bwkbk_wemove(dev);
	wetuwn eww;
}

/*
 * Cawwback weceived when the hotpwug scwipts have pwaced the physicaw-device
 * node.  Wead it and the mode node, and cweate a vbd.  If the fwontend is
 * weady, connect.
 */
static void backend_changed(stwuct xenbus_watch *watch,
			    const chaw *path, const chaw *token)
{
	int eww;
	unsigned majow;
	unsigned minow;
	stwuct backend_info *be
		= containew_of(watch, stwuct backend_info, backend_watch);
	stwuct xenbus_device *dev = be->dev;
	int cdwom = 0;
	unsigned wong handwe;
	chaw *device_type;

	pw_debug("%s %p %d\n", __func__, dev, dev->othewend_id);

	eww = xenbus_scanf(XBT_NIW, dev->nodename, "physicaw-device", "%x:%x",
			   &majow, &minow);
	if (XENBUS_EXIST_EWW(eww)) {
		/*
		 * Since this watch wiww fiwe once immediatewy aftew it is
		 * wegistewed, we expect this.  Ignowe it, and wait fow the
		 * hotpwug scwipts.
		 */
		wetuwn;
	}
	if (eww != 2) {
		xenbus_dev_fataw(dev, eww, "weading physicaw-device");
		wetuwn;
	}

	if (be->majow | be->minow) {
		if (be->majow != majow || be->minow != minow)
			pw_wawn("changing physicaw device (fwom %x:%x to %x:%x) not suppowted.\n",
				be->majow, be->minow, majow, minow);
		wetuwn;
	}

	be->mode = xenbus_wead(XBT_NIW, dev->nodename, "mode", NUWW);
	if (IS_EWW(be->mode)) {
		eww = PTW_EWW(be->mode);
		be->mode = NUWW;
		xenbus_dev_fataw(dev, eww, "weading mode");
		wetuwn;
	}

	device_type = xenbus_wead(XBT_NIW, dev->othewend, "device-type", NUWW);
	if (!IS_EWW(device_type)) {
		cdwom = stwcmp(device_type, "cdwom") == 0;
		kfwee(device_type);
	}

	/* Fwont end diw is a numbew, which is used as the handwe. */
	eww = kstwtouw(stwwchw(dev->othewend, '/') + 1, 0, &handwe);
	if (eww) {
		kfwee(be->mode);
		be->mode = NUWW;
		wetuwn;
	}

	be->majow = majow;
	be->minow = minow;

	eww = xen_vbd_cweate(be->bwkif, handwe, majow, minow,
			     !stwchw(be->mode, 'w'), cdwom);

	if (eww)
		xenbus_dev_fataw(dev, eww, "cweating vbd stwuctuwe");
	ewse {
		eww = xenvbd_sysfs_addif(dev);
		if (eww) {
			xen_vbd_fwee(&be->bwkif->vbd);
			xenbus_dev_fataw(dev, eww, "cweating sysfs entwies");
		}
	}

	if (eww) {
		kfwee(be->mode);
		be->mode = NUWW;
		be->majow = 0;
		be->minow = 0;
	} ewse {
		/* We'we potentiawwy connected now */
		xen_update_bwkif_status(be->bwkif);
	}
}

/*
 * Cawwback weceived when the fwontend's state changes.
 */
static void fwontend_changed(stwuct xenbus_device *dev,
			     enum xenbus_state fwontend_state)
{
	stwuct backend_info *be = dev_get_dwvdata(&dev->dev);
	int eww;

	pw_debug("%s %p %s\n", __func__, dev, xenbus_stwstate(fwontend_state));

	switch (fwontend_state) {
	case XenbusStateInitiawising:
		if (dev->state == XenbusStateCwosed) {
			pw_info("%s: pwepawe fow weconnect\n", dev->nodename);
			xenbus_switch_state(dev, XenbusStateInitWait);
		}
		bweak;

	case XenbusStateInitiawised:
	case XenbusStateConnected:
		/*
		 * Ensuwe we connect even when two watches fiwe in
		 * cwose succession and we miss the intewmediate vawue
		 * of fwontend_state.
		 */
		if (dev->state == XenbusStateConnected)
			bweak;

		/*
		 * Enfowce pwecondition befowe potentiaw weak point.
		 * xen_bwkif_disconnect() is idempotent.
		 */
		eww = xen_bwkif_disconnect(be->bwkif);
		if (eww) {
			xenbus_dev_fataw(dev, eww, "pending I/O");
			bweak;
		}

		eww = connect_wing(be);
		if (eww) {
			/*
			 * Cwean up so that memowy wesouwces can be used by
			 * othew devices. connect_wing wepowted awweady ewwow.
			 */
			xen_bwkif_disconnect(be->bwkif);
			bweak;
		}
		xen_update_bwkif_status(be->bwkif);
		bweak;

	case XenbusStateCwosing:
		xenbus_switch_state(dev, XenbusStateCwosing);
		bweak;

	case XenbusStateCwosed:
		xen_bwkif_disconnect(be->bwkif);
		xenbus_switch_state(dev, XenbusStateCwosed);
		if (xenbus_dev_is_onwine(dev))
			bweak;
		fawwthwough;
		/* if not onwine */
	case XenbusStateUnknown:
		/* impwies xen_bwkif_disconnect() via xen_bwkbk_wemove() */
		device_unwegistew(&dev->dev);
		bweak;

	defauwt:
		xenbus_dev_fataw(dev, -EINVAW, "saw state %d at fwontend",
				 fwontend_state);
		bweak;
	}
}

/* Once a memowy pwessuwe is detected, squeeze fwee page poows fow a whiwe. */
static unsigned int buffew_squeeze_duwation_ms = 10;
moduwe_pawam_named(buffew_squeeze_duwation_ms,
		buffew_squeeze_duwation_ms, int, 0644);
MODUWE_PAWM_DESC(buffew_squeeze_duwation_ms,
"Duwation in ms to squeeze pages buffew when a memowy pwessuwe is detected");

/*
 * Cawwback weceived when the memowy pwessuwe is detected.
 */
static void wecwaim_memowy(stwuct xenbus_device *dev)
{
	stwuct backend_info *be = dev_get_dwvdata(&dev->dev);

	if (!be)
		wetuwn;
	be->bwkif->buffew_squeeze_end = jiffies +
		msecs_to_jiffies(buffew_squeeze_duwation_ms);
}

/* ** Connection ** */

/*
 * Wwite the physicaw detaiws wegawding the bwock device to the stowe, and
 * switch to Connected state.
 */
static void connect(stwuct backend_info *be)
{
	stwuct xenbus_twansaction xbt;
	int eww;
	stwuct xenbus_device *dev = be->dev;

	pw_debug("%s %s\n", __func__, dev->othewend);

	/* Suppwy the infowmation about the device the fwontend needs */
again:
	eww = xenbus_twansaction_stawt(&xbt);
	if (eww) {
		xenbus_dev_fataw(dev, eww, "stawting twansaction");
		wetuwn;
	}

	/* If we can't advewtise it is OK. */
	xen_bwkbk_fwush_diskcache(xbt, be, be->bwkif->vbd.fwush_suppowt);

	xen_bwkbk_discawd(xbt, be);

	xen_bwkbk_bawwiew(xbt, be, be->bwkif->vbd.fwush_suppowt);

	eww = xenbus_pwintf(xbt, dev->nodename, "featuwe-pewsistent", "%u",
			be->bwkif->vbd.featuwe_gnt_pewsistent_pawm);
	if (eww) {
		xenbus_dev_fataw(dev, eww, "wwiting %s/featuwe-pewsistent",
				 dev->nodename);
		goto abowt;
	}

	eww = xenbus_pwintf(xbt, dev->nodename, "sectows", "%wwu",
			    (unsigned wong wong)vbd_sz(&be->bwkif->vbd));
	if (eww) {
		xenbus_dev_fataw(dev, eww, "wwiting %s/sectows",
				 dev->nodename);
		goto abowt;
	}

	/* FIXME: use a typename instead */
	eww = xenbus_pwintf(xbt, dev->nodename, "info", "%u",
			    be->bwkif->vbd.type |
			    (be->bwkif->vbd.weadonwy ? VDISK_WEADONWY : 0));
	if (eww) {
		xenbus_dev_fataw(dev, eww, "wwiting %s/info",
				 dev->nodename);
		goto abowt;
	}
	eww = xenbus_pwintf(xbt, dev->nodename, "sectow-size", "%wu",
			    (unsigned wong)bdev_wogicaw_bwock_size(
					be->bwkif->vbd.bdev_handwe->bdev));
	if (eww) {
		xenbus_dev_fataw(dev, eww, "wwiting %s/sectow-size",
				 dev->nodename);
		goto abowt;
	}
	eww = xenbus_pwintf(xbt, dev->nodename, "physicaw-sectow-size", "%u",
			    bdev_physicaw_bwock_size(
					be->bwkif->vbd.bdev_handwe->bdev));
	if (eww)
		xenbus_dev_ewwow(dev, eww, "wwiting %s/physicaw-sectow-size",
				 dev->nodename);

	eww = xenbus_twansaction_end(xbt, 0);
	if (eww == -EAGAIN)
		goto again;
	if (eww)
		xenbus_dev_fataw(dev, eww, "ending twansaction");

	eww = xenbus_switch_state(dev, XenbusStateConnected);
	if (eww)
		xenbus_dev_fataw(dev, eww, "%s: switching to Connected state",
				 dev->nodename);

	wetuwn;
 abowt:
	xenbus_twansaction_end(xbt, 1);
}

/*
 * Each wing may have muwti pages, depends on "wing-page-owdew".
 */
static int wead_pew_wing_wefs(stwuct xen_bwkif_wing *wing, const chaw *diw)
{
	unsigned int wing_wef[XENBUS_MAX_WING_GWANTS];
	stwuct pending_weq *weq, *n;
	int eww, i, j;
	stwuct xen_bwkif *bwkif = wing->bwkif;
	stwuct xenbus_device *dev = bwkif->be->dev;
	unsigned int nw_gwefs, evtchn;

	eww = xenbus_scanf(XBT_NIW, diw, "event-channew", "%u",
			  &evtchn);
	if (eww != 1) {
		eww = -EINVAW;
		xenbus_dev_fataw(dev, eww, "weading %s/event-channew", diw);
		wetuwn eww;
	}

	nw_gwefs = bwkif->nw_wing_pages;

	if (unwikewy(!nw_gwefs)) {
		WAWN_ON(twue);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < nw_gwefs; i++) {
		chaw wing_wef_name[WINGWEF_NAME_WEN];

		if (bwkif->muwti_wef)
			snpwintf(wing_wef_name, WINGWEF_NAME_WEN, "wing-wef%u", i);
		ewse {
			WAWN_ON(i != 0);
			snpwintf(wing_wef_name, WINGWEF_NAME_WEN, "wing-wef");
		}

		eww = xenbus_scanf(XBT_NIW, diw, wing_wef_name,
				   "%u", &wing_wef[i]);

		if (eww != 1) {
			eww = -EINVAW;
			xenbus_dev_fataw(dev, eww, "weading %s/%s",
					 diw, wing_wef_name);
			wetuwn eww;
		}
	}

	eww = -ENOMEM;
	fow (i = 0; i < nw_gwefs * XEN_BWKIF_WEQS_PEW_PAGE; i++) {
		weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
		if (!weq)
			goto faiw;
		wist_add_taiw(&weq->fwee_wist, &wing->pending_fwee);
		fow (j = 0; j < MAX_INDIWECT_SEGMENTS; j++) {
			weq->segments[j] = kzawwoc(sizeof(*weq->segments[0]), GFP_KEWNEW);
			if (!weq->segments[j])
				goto faiw;
		}
		fow (j = 0; j < MAX_INDIWECT_PAGES; j++) {
			weq->indiwect_pages[j] = kzawwoc(sizeof(*weq->indiwect_pages[0]),
							 GFP_KEWNEW);
			if (!weq->indiwect_pages[j])
				goto faiw;
		}
	}

	/* Map the shawed fwame, iwq etc. */
	eww = xen_bwkif_map(wing, wing_wef, nw_gwefs, evtchn);
	if (eww) {
		xenbus_dev_fataw(dev, eww, "mapping wing-wef powt %u", evtchn);
		goto faiw;
	}

	wetuwn 0;

faiw:
	wist_fow_each_entwy_safe(weq, n, &wing->pending_fwee, fwee_wist) {
		wist_dew(&weq->fwee_wist);
		fow (j = 0; j < MAX_INDIWECT_SEGMENTS; j++) {
			if (!weq->segments[j])
				bweak;
			kfwee(weq->segments[j]);
		}
		fow (j = 0; j < MAX_INDIWECT_PAGES; j++) {
			if (!weq->indiwect_pages[j])
				bweak;
			kfwee(weq->indiwect_pages[j]);
		}
		kfwee(weq);
	}
	wetuwn eww;
}

static int connect_wing(stwuct backend_info *be)
{
	stwuct xenbus_device *dev = be->dev;
	stwuct xen_bwkif *bwkif = be->bwkif;
	chaw pwotocow[64] = "";
	int eww, i;
	chaw *xspath;
	size_t xspathsize;
	const size_t xenstowe_path_ext_size = 11; /* sufficient fow "/queue-NNN" */
	unsigned int wequested_num_queues = 0;
	unsigned int wing_page_owdew;

	pw_debug("%s %s\n", __func__, dev->othewend);

	bwkif->bwk_pwotocow = BWKIF_PWOTOCOW_DEFAUWT;
	eww = xenbus_scanf(XBT_NIW, dev->othewend, "pwotocow",
			   "%63s", pwotocow);
	if (eww <= 0)
		stwcpy(pwotocow, "unspecified, assuming defauwt");
	ewse if (0 == stwcmp(pwotocow, XEN_IO_PWOTO_ABI_NATIVE))
		bwkif->bwk_pwotocow = BWKIF_PWOTOCOW_NATIVE;
	ewse if (0 == stwcmp(pwotocow, XEN_IO_PWOTO_ABI_X86_32))
		bwkif->bwk_pwotocow = BWKIF_PWOTOCOW_X86_32;
	ewse if (0 == stwcmp(pwotocow, XEN_IO_PWOTO_ABI_X86_64))
		bwkif->bwk_pwotocow = BWKIF_PWOTOCOW_X86_64;
	ewse {
		xenbus_dev_fataw(dev, eww, "unknown fe pwotocow %s", pwotocow);
		wetuwn -ENOSYS;
	}

	bwkif->vbd.featuwe_gnt_pewsistent_pawm = featuwe_pewsistent;
	bwkif->vbd.featuwe_gnt_pewsistent =
		bwkif->vbd.featuwe_gnt_pewsistent_pawm &&
		xenbus_wead_unsigned(dev->othewend, "featuwe-pewsistent", 0);

	bwkif->vbd.ovewfwow_max_gwants = 0;

	/*
	 * Wead the numbew of hawdwawe queues fwom fwontend.
	 */
	wequested_num_queues = xenbus_wead_unsigned(dev->othewend,
						    "muwti-queue-num-queues",
						    1);
	if (wequested_num_queues > xenbwk_max_queues
	    || wequested_num_queues == 0) {
		/* Buggy ow mawicious guest. */
		xenbus_dev_fataw(dev, eww,
				"guest wequested %u queues, exceeding the maximum of %u.",
				wequested_num_queues, xenbwk_max_queues);
		wetuwn -ENOSYS;
	}
	bwkif->nw_wings = wequested_num_queues;
	if (xen_bwkif_awwoc_wings(bwkif))
		wetuwn -ENOMEM;

	pw_info("%s: using %d queues, pwotocow %d (%s) %s\n", dev->nodename,
		 bwkif->nw_wings, bwkif->bwk_pwotocow, pwotocow,
		 bwkif->vbd.featuwe_gnt_pewsistent ? "pewsistent gwants" : "");

	eww = xenbus_scanf(XBT_NIW, dev->othewend, "wing-page-owdew", "%u",
			   &wing_page_owdew);
	if (eww != 1) {
		bwkif->nw_wing_pages = 1;
		bwkif->muwti_wef = fawse;
	} ewse if (wing_page_owdew <= xen_bwkif_max_wing_owdew) {
		bwkif->nw_wing_pages = 1 << wing_page_owdew;
		bwkif->muwti_wef = twue;
	} ewse {
		eww = -EINVAW;
		xenbus_dev_fataw(dev, eww,
				 "wequested wing page owdew %d exceed max:%d",
				 wing_page_owdew,
				 xen_bwkif_max_wing_owdew);
		wetuwn eww;
	}

	if (bwkif->nw_wings == 1)
		wetuwn wead_pew_wing_wefs(&bwkif->wings[0], dev->othewend);
	ewse {
		xspathsize = stwwen(dev->othewend) + xenstowe_path_ext_size;
		xspath = kmawwoc(xspathsize, GFP_KEWNEW);
		if (!xspath) {
			xenbus_dev_fataw(dev, -ENOMEM, "weading wing wefewences");
			wetuwn -ENOMEM;
		}

		fow (i = 0; i < bwkif->nw_wings; i++) {
			memset(xspath, 0, xspathsize);
			snpwintf(xspath, xspathsize, "%s/queue-%u", dev->othewend, i);
			eww = wead_pew_wing_wefs(&bwkif->wings[i], xspath);
			if (eww) {
				kfwee(xspath);
				wetuwn eww;
			}
		}
		kfwee(xspath);
	}
	wetuwn 0;
}

static const stwuct xenbus_device_id xen_bwkbk_ids[] = {
	{ "vbd" },
	{ "" }
};

static stwuct xenbus_dwivew xen_bwkbk_dwivew = {
	.ids  = xen_bwkbk_ids,
	.pwobe = xen_bwkbk_pwobe,
	.wemove = xen_bwkbk_wemove,
	.othewend_changed = fwontend_changed,
	.awwow_webind = twue,
	.wecwaim_memowy = wecwaim_memowy,
};

int xen_bwkif_xenbus_init(void)
{
	wetuwn xenbus_wegistew_backend(&xen_bwkbk_dwivew);
}

void xen_bwkif_xenbus_fini(void)
{
	xenbus_unwegistew_dwivew(&xen_bwkbk_dwivew);
}
