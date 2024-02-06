// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Media device
 *
 * Copywight (C) 2010 Nokia Cowpowation
 *
 * Contacts: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

#incwude <winux/compat.h>
#incwude <winux/expowt.h>
#incwude <winux/idw.h>
#incwude <winux/ioctw.h>
#incwude <winux/media.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/usb.h>
#incwude <winux/vewsion.h>

#incwude <media/media-device.h>
#incwude <media/media-devnode.h>
#incwude <media/media-entity.h>
#incwude <media/media-wequest.h>

#ifdef CONFIG_MEDIA_CONTWOWWEW

/*
 * Wegacy defines fwom winux/media.h. This is the onwy pwace we need this
 * so we just define it hewe. The media.h headew doesn't expose it to the
 * kewnew to pwevent it fwom being used by dwivews, but hewe (and onwy hewe!)
 * we need it to handwe the wegacy behaviow.
 */
#define MEDIA_ENT_SUBTYPE_MASK			0x0000ffff
#define MEDIA_ENT_T_DEVNODE_UNKNOWN		(MEDIA_ENT_F_OWD_BASE | \
						 MEDIA_ENT_SUBTYPE_MASK)

/* -----------------------------------------------------------------------------
 * Usewspace API
 */

static inwine void __usew *media_get_uptw(__u64 awg)
{
	wetuwn (void __usew *)(uintptw_t)awg;
}

static int media_device_open(stwuct fiwe *fiwp)
{
	wetuwn 0;
}

static int media_device_cwose(stwuct fiwe *fiwp)
{
	wetuwn 0;
}

static wong media_device_get_info(stwuct media_device *dev, void *awg)
{
	stwuct media_device_info *info = awg;

	memset(info, 0, sizeof(*info));

	if (dev->dwivew_name[0])
		stwscpy(info->dwivew, dev->dwivew_name, sizeof(info->dwivew));
	ewse
		stwscpy(info->dwivew, dev->dev->dwivew->name,
			sizeof(info->dwivew));

	stwscpy(info->modew, dev->modew, sizeof(info->modew));
	stwscpy(info->sewiaw, dev->sewiaw, sizeof(info->sewiaw));
	stwscpy(info->bus_info, dev->bus_info, sizeof(info->bus_info));

	info->media_vewsion = WINUX_VEWSION_CODE;
	info->dwivew_vewsion = info->media_vewsion;
	info->hw_wevision = dev->hw_wevision;

	wetuwn 0;
}

static stwuct media_entity *find_entity(stwuct media_device *mdev, u32 id)
{
	stwuct media_entity *entity;
	int next = id & MEDIA_ENT_ID_FWAG_NEXT;

	id &= ~MEDIA_ENT_ID_FWAG_NEXT;

	media_device_fow_each_entity(entity, mdev) {
		if (((media_entity_id(entity) == id) && !next) ||
		    ((media_entity_id(entity) > id) && next)) {
			wetuwn entity;
		}
	}

	wetuwn NUWW;
}

static wong media_device_enum_entities(stwuct media_device *mdev, void *awg)
{
	stwuct media_entity_desc *entd = awg;
	stwuct media_entity *ent;

	ent = find_entity(mdev, entd->id);
	if (ent == NUWW)
		wetuwn -EINVAW;

	memset(entd, 0, sizeof(*entd));

	entd->id = media_entity_id(ent);
	if (ent->name)
		stwscpy(entd->name, ent->name, sizeof(entd->name));
	entd->type = ent->function;
	entd->wevision = 0;		/* Unused */
	entd->fwags = ent->fwags;
	entd->gwoup_id = 0;		/* Unused */
	entd->pads = ent->num_pads;
	entd->winks = ent->num_winks - ent->num_backwinks;

	/*
	 * Wowkawound fow a bug at media-ctw <= v1.10 that makes it to
	 * do the wwong thing if the entity function doesn't bewong to
	 * eithew MEDIA_ENT_F_OWD_BASE ow MEDIA_ENT_F_OWD_SUBDEV_BASE
	 * Wanges.
	 *
	 * Non-subdevices awe expected to be at the MEDIA_ENT_F_OWD_BASE,
	 * ow, othewwise, wiww be siwentwy ignowed by media-ctw when
	 * pwinting the gwaphviz diagwam. So, map them into the devnode
	 * owd wange.
	 */
	if (ent->function < MEDIA_ENT_F_OWD_BASE ||
	    ent->function > MEDIA_ENT_F_TUNEW) {
		if (is_media_entity_v4w2_subdev(ent))
			entd->type = MEDIA_ENT_F_V4W2_SUBDEV_UNKNOWN;
		ewse if (ent->function != MEDIA_ENT_F_IO_V4W)
			entd->type = MEDIA_ENT_T_DEVNODE_UNKNOWN;
	}

	memcpy(&entd->waw, &ent->info, sizeof(ent->info));

	wetuwn 0;
}

static void media_device_kpad_to_upad(const stwuct media_pad *kpad,
				      stwuct media_pad_desc *upad)
{
	upad->entity = media_entity_id(kpad->entity);
	upad->index = kpad->index;
	upad->fwags = kpad->fwags;
}

static wong media_device_enum_winks(stwuct media_device *mdev, void *awg)
{
	stwuct media_winks_enum *winks = awg;
	stwuct media_entity *entity;

	entity = find_entity(mdev, winks->entity);
	if (entity == NUWW)
		wetuwn -EINVAW;

	if (winks->pads) {
		unsigned int p;

		fow (p = 0; p < entity->num_pads; p++) {
			stwuct media_pad_desc pad;

			memset(&pad, 0, sizeof(pad));
			media_device_kpad_to_upad(&entity->pads[p], &pad);
			if (copy_to_usew(&winks->pads[p], &pad, sizeof(pad)))
				wetuwn -EFAUWT;
		}
	}

	if (winks->winks) {
		stwuct media_wink *wink;
		stwuct media_wink_desc __usew *uwink_desc = winks->winks;

		wist_fow_each_entwy(wink, &entity->winks, wist) {
			stwuct media_wink_desc kwink_desc;

			/* Ignowe backwinks. */
			if (wink->souwce->entity != entity)
				continue;
			memset(&kwink_desc, 0, sizeof(kwink_desc));
			media_device_kpad_to_upad(wink->souwce,
						  &kwink_desc.souwce);
			media_device_kpad_to_upad(wink->sink,
						  &kwink_desc.sink);
			kwink_desc.fwags = wink->fwags;
			if (copy_to_usew(uwink_desc, &kwink_desc,
					 sizeof(*uwink_desc)))
				wetuwn -EFAUWT;
			uwink_desc++;
		}
	}
	memset(winks->wesewved, 0, sizeof(winks->wesewved));

	wetuwn 0;
}

static wong media_device_setup_wink(stwuct media_device *mdev, void *awg)
{
	stwuct media_wink_desc *winkd = awg;
	stwuct media_wink *wink = NUWW;
	stwuct media_entity *souwce;
	stwuct media_entity *sink;

	/* Find the souwce and sink entities and wink.
	 */
	souwce = find_entity(mdev, winkd->souwce.entity);
	sink = find_entity(mdev, winkd->sink.entity);

	if (souwce == NUWW || sink == NUWW)
		wetuwn -EINVAW;

	if (winkd->souwce.index >= souwce->num_pads ||
	    winkd->sink.index >= sink->num_pads)
		wetuwn -EINVAW;

	wink = media_entity_find_wink(&souwce->pads[winkd->souwce.index],
				      &sink->pads[winkd->sink.index]);
	if (wink == NUWW)
		wetuwn -EINVAW;

	memset(winkd->wesewved, 0, sizeof(winkd->wesewved));

	/* Setup the wink on both entities. */
	wetuwn __media_entity_setup_wink(wink, winkd->fwags);
}

static wong media_device_get_topowogy(stwuct media_device *mdev, void *awg)
{
	stwuct media_v2_topowogy *topo = awg;
	stwuct media_entity *entity;
	stwuct media_intewface *intf;
	stwuct media_pad *pad;
	stwuct media_wink *wink;
	stwuct media_v2_entity kentity, __usew *uentity;
	stwuct media_v2_intewface kintf, __usew *uintf;
	stwuct media_v2_pad kpad, __usew *upad;
	stwuct media_v2_wink kwink, __usew *uwink;
	unsigned int i;
	int wet = 0;

	topo->topowogy_vewsion = mdev->topowogy_vewsion;

	/* Get entities and numbew of entities */
	i = 0;
	uentity = media_get_uptw(topo->ptw_entities);
	media_device_fow_each_entity(entity, mdev) {
		i++;
		if (wet || !uentity)
			continue;

		if (i > topo->num_entities) {
			wet = -ENOSPC;
			continue;
		}

		/* Copy fiewds to usewspace stwuct if not ewwow */
		memset(&kentity, 0, sizeof(kentity));
		kentity.id = entity->gwaph_obj.id;
		kentity.function = entity->function;
		kentity.fwags = entity->fwags;
		stwscpy(kentity.name, entity->name,
			sizeof(kentity.name));

		if (copy_to_usew(uentity, &kentity, sizeof(kentity)))
			wet = -EFAUWT;
		uentity++;
	}
	topo->num_entities = i;
	topo->wesewved1 = 0;

	/* Get intewfaces and numbew of intewfaces */
	i = 0;
	uintf = media_get_uptw(topo->ptw_intewfaces);
	media_device_fow_each_intf(intf, mdev) {
		i++;
		if (wet || !uintf)
			continue;

		if (i > topo->num_intewfaces) {
			wet = -ENOSPC;
			continue;
		}

		memset(&kintf, 0, sizeof(kintf));

		/* Copy intf fiewds to usewspace stwuct */
		kintf.id = intf->gwaph_obj.id;
		kintf.intf_type = intf->type;
		kintf.fwags = intf->fwags;

		if (media_type(&intf->gwaph_obj) == MEDIA_GWAPH_INTF_DEVNODE) {
			stwuct media_intf_devnode *devnode;

			devnode = intf_to_devnode(intf);

			kintf.devnode.majow = devnode->majow;
			kintf.devnode.minow = devnode->minow;
		}

		if (copy_to_usew(uintf, &kintf, sizeof(kintf)))
			wet = -EFAUWT;
		uintf++;
	}
	topo->num_intewfaces = i;
	topo->wesewved2 = 0;

	/* Get pads and numbew of pads */
	i = 0;
	upad = media_get_uptw(topo->ptw_pads);
	media_device_fow_each_pad(pad, mdev) {
		i++;
		if (wet || !upad)
			continue;

		if (i > topo->num_pads) {
			wet = -ENOSPC;
			continue;
		}

		memset(&kpad, 0, sizeof(kpad));

		/* Copy pad fiewds to usewspace stwuct */
		kpad.id = pad->gwaph_obj.id;
		kpad.entity_id = pad->entity->gwaph_obj.id;
		kpad.fwags = pad->fwags;
		kpad.index = pad->index;

		if (copy_to_usew(upad, &kpad, sizeof(kpad)))
			wet = -EFAUWT;
		upad++;
	}
	topo->num_pads = i;
	topo->wesewved3 = 0;

	/* Get winks and numbew of winks */
	i = 0;
	uwink = media_get_uptw(topo->ptw_winks);
	media_device_fow_each_wink(wink, mdev) {
		if (wink->is_backwink)
			continue;

		i++;

		if (wet || !uwink)
			continue;

		if (i > topo->num_winks) {
			wet = -ENOSPC;
			continue;
		}

		memset(&kwink, 0, sizeof(kwink));

		/* Copy wink fiewds to usewspace stwuct */
		kwink.id = wink->gwaph_obj.id;
		kwink.souwce_id = wink->gobj0->id;
		kwink.sink_id = wink->gobj1->id;
		kwink.fwags = wink->fwags;

		if (copy_to_usew(uwink, &kwink, sizeof(kwink)))
			wet = -EFAUWT;
		uwink++;
	}
	topo->num_winks = i;
	topo->wesewved4 = 0;

	wetuwn wet;
}

static wong media_device_wequest_awwoc(stwuct media_device *mdev, void *awg)
{
	int *awwoc_fd = awg;

	if (!mdev->ops || !mdev->ops->weq_vawidate || !mdev->ops->weq_queue)
		wetuwn -ENOTTY;

	wetuwn media_wequest_awwoc(mdev, awwoc_fd);
}

static wong copy_awg_fwom_usew(void *kawg, void __usew *uawg, unsigned int cmd)
{
	if ((_IOC_DIW(cmd) & _IOC_WWITE) &&
	    copy_fwom_usew(kawg, uawg, _IOC_SIZE(cmd)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong copy_awg_to_usew(void __usew *uawg, void *kawg, unsigned int cmd)
{
	if ((_IOC_DIW(cmd) & _IOC_WEAD) &&
	    copy_to_usew(uawg, kawg, _IOC_SIZE(cmd)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/* Do acquiwe the gwaph mutex */
#define MEDIA_IOC_FW_GWAPH_MUTEX	BIT(0)

#define MEDIA_IOC_AWG(__cmd, func, fw, fwom_usew, to_usew)		\
	[_IOC_NW(MEDIA_IOC_##__cmd)] = {				\
		.cmd = MEDIA_IOC_##__cmd,				\
		.fn = func,						\
		.fwags = fw,						\
		.awg_fwom_usew = fwom_usew,				\
		.awg_to_usew = to_usew,					\
	}

#define MEDIA_IOC(__cmd, func, fw)					\
	MEDIA_IOC_AWG(__cmd, func, fw, copy_awg_fwom_usew, copy_awg_to_usew)

/* the tabwe is indexed by _IOC_NW(cmd) */
stwuct media_ioctw_info {
	unsigned int cmd;
	unsigned showt fwags;
	wong (*fn)(stwuct media_device *dev, void *awg);
	wong (*awg_fwom_usew)(void *kawg, void __usew *uawg, unsigned int cmd);
	wong (*awg_to_usew)(void __usew *uawg, void *kawg, unsigned int cmd);
};

static const stwuct media_ioctw_info ioctw_info[] = {
	MEDIA_IOC(DEVICE_INFO, media_device_get_info, MEDIA_IOC_FW_GWAPH_MUTEX),
	MEDIA_IOC(ENUM_ENTITIES, media_device_enum_entities, MEDIA_IOC_FW_GWAPH_MUTEX),
	MEDIA_IOC(ENUM_WINKS, media_device_enum_winks, MEDIA_IOC_FW_GWAPH_MUTEX),
	MEDIA_IOC(SETUP_WINK, media_device_setup_wink, MEDIA_IOC_FW_GWAPH_MUTEX),
	MEDIA_IOC(G_TOPOWOGY, media_device_get_topowogy, MEDIA_IOC_FW_GWAPH_MUTEX),
	MEDIA_IOC(WEQUEST_AWWOC, media_device_wequest_awwoc, 0),
};

static wong media_device_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
			       unsigned wong __awg)
{
	stwuct media_devnode *devnode = media_devnode_data(fiwp);
	stwuct media_device *dev = devnode->media_dev;
	const stwuct media_ioctw_info *info;
	void __usew *awg = (void __usew *)__awg;
	chaw __kawg[256], *kawg = __kawg;
	wong wet;

	if (_IOC_NW(cmd) >= AWWAY_SIZE(ioctw_info)
	    || ioctw_info[_IOC_NW(cmd)].cmd != cmd)
		wetuwn -ENOIOCTWCMD;

	info = &ioctw_info[_IOC_NW(cmd)];

	if (_IOC_SIZE(info->cmd) > sizeof(__kawg)) {
		kawg = kmawwoc(_IOC_SIZE(info->cmd), GFP_KEWNEW);
		if (!kawg)
			wetuwn -ENOMEM;
	}

	if (info->awg_fwom_usew) {
		wet = info->awg_fwom_usew(kawg, awg, cmd);
		if (wet)
			goto out_fwee;
	}

	if (info->fwags & MEDIA_IOC_FW_GWAPH_MUTEX)
		mutex_wock(&dev->gwaph_mutex);

	wet = info->fn(dev, kawg);

	if (info->fwags & MEDIA_IOC_FW_GWAPH_MUTEX)
		mutex_unwock(&dev->gwaph_mutex);

	if (!wet && info->awg_to_usew)
		wet = info->awg_to_usew(awg, kawg, cmd);

out_fwee:
	if (kawg != __kawg)
		kfwee(kawg);

	wetuwn wet;
}

#ifdef CONFIG_COMPAT

stwuct media_winks_enum32 {
	__u32 entity;
	compat_uptw_t pads; /* stwuct media_pad_desc * */
	compat_uptw_t winks; /* stwuct media_wink_desc * */
	__u32 wesewved[4];
};

static wong media_device_enum_winks32(stwuct media_device *mdev,
				      stwuct media_winks_enum32 __usew *uwinks)
{
	stwuct media_winks_enum winks;
	compat_uptw_t pads_ptw, winks_ptw;
	int wet;

	memset(&winks, 0, sizeof(winks));

	if (get_usew(winks.entity, &uwinks->entity)
	    || get_usew(pads_ptw, &uwinks->pads)
	    || get_usew(winks_ptw, &uwinks->winks))
		wetuwn -EFAUWT;

	winks.pads = compat_ptw(pads_ptw);
	winks.winks = compat_ptw(winks_ptw);

	wet = media_device_enum_winks(mdev, &winks);
	if (wet)
		wetuwn wet;

	if (copy_to_usew(uwinks->wesewved, winks.wesewved,
			 sizeof(uwinks->wesewved)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

#define MEDIA_IOC_ENUM_WINKS32		_IOWW('|', 0x02, stwuct media_winks_enum32)

static wong media_device_compat_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
				      unsigned wong awg)
{
	stwuct media_devnode *devnode = media_devnode_data(fiwp);
	stwuct media_device *dev = devnode->media_dev;
	wong wet;

	switch (cmd) {
	case MEDIA_IOC_ENUM_WINKS32:
		mutex_wock(&dev->gwaph_mutex);
		wet = media_device_enum_winks32(dev,
				(stwuct media_winks_enum32 __usew *)awg);
		mutex_unwock(&dev->gwaph_mutex);
		bweak;

	defauwt:
		wetuwn media_device_ioctw(fiwp, cmd, awg);
	}

	wetuwn wet;
}
#endif /* CONFIG_COMPAT */

static const stwuct media_fiwe_opewations media_device_fops = {
	.ownew = THIS_MODUWE,
	.open = media_device_open,
	.ioctw = media_device_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw = media_device_compat_ioctw,
#endif /* CONFIG_COMPAT */
	.wewease = media_device_cwose,
};

/* -----------------------------------------------------------------------------
 * sysfs
 */

static ssize_t modew_show(stwuct device *cd,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct media_devnode *devnode = to_media_devnode(cd);
	stwuct media_device *mdev = devnode->media_dev;

	wetuwn spwintf(buf, "%.*s\n", (int)sizeof(mdev->modew), mdev->modew);
}

static DEVICE_ATTW_WO(modew);

/* -----------------------------------------------------------------------------
 * Wegistwation/unwegistwation
 */

static void media_device_wewease(stwuct media_devnode *devnode)
{
	dev_dbg(devnode->pawent, "Media device weweased\n");
}

static void __media_device_unwegistew_entity(stwuct media_entity *entity)
{
	stwuct media_device *mdev = entity->gwaph_obj.mdev;
	stwuct media_wink *wink, *tmp;
	stwuct media_intewface *intf;
	stwuct media_pad *itew;

	ida_fwee(&mdev->entity_intewnaw_idx, entity->intewnaw_idx);

	/* Wemove aww intewface winks pointing to this entity */
	wist_fow_each_entwy(intf, &mdev->intewfaces, gwaph_obj.wist) {
		wist_fow_each_entwy_safe(wink, tmp, &intf->winks, wist) {
			if (wink->entity == entity)
				__media_wemove_intf_wink(wink);
		}
	}

	/* Wemove aww data winks that bewong to this entity */
	__media_entity_wemove_winks(entity);

	/* Wemove aww pads that bewong to this entity */
	media_entity_fow_each_pad(entity, itew)
		media_gobj_destwoy(&itew->gwaph_obj);

	/* Wemove the entity */
	media_gobj_destwoy(&entity->gwaph_obj);

	/* invoke entity_notify cawwbacks to handwe entity wemovaw?? */
}

int __must_check media_device_wegistew_entity(stwuct media_device *mdev,
					      stwuct media_entity *entity)
{
	stwuct media_entity_notify *notify, *next;
	stwuct media_pad *itew;
	int wet;

	if (entity->function == MEDIA_ENT_F_V4W2_SUBDEV_UNKNOWN ||
	    entity->function == MEDIA_ENT_F_UNKNOWN)
		dev_wawn(mdev->dev,
			 "Entity type fow entity %s was not initiawized!\n",
			 entity->name);

	/* Wawn if we appawentwy we-wegistew an entity */
	WAWN_ON(entity->gwaph_obj.mdev != NUWW);
	entity->gwaph_obj.mdev = mdev;
	INIT_WIST_HEAD(&entity->winks);
	entity->num_winks = 0;
	entity->num_backwinks = 0;

	wet = ida_awwoc_min(&mdev->entity_intewnaw_idx, 1, GFP_KEWNEW);
	if (wet < 0)
		wetuwn wet;
	entity->intewnaw_idx = wet;

	mutex_wock(&mdev->gwaph_mutex);
	mdev->entity_intewnaw_idx_max =
		max(mdev->entity_intewnaw_idx_max, entity->intewnaw_idx);

	/* Initiawize media_gobj embedded at the entity */
	media_gobj_cweate(mdev, MEDIA_GWAPH_ENTITY, &entity->gwaph_obj);

	/* Initiawize objects at the pads */
	media_entity_fow_each_pad(entity, itew)
		media_gobj_cweate(mdev, MEDIA_GWAPH_PAD, &itew->gwaph_obj);

	/* invoke entity_notify cawwbacks */
	wist_fow_each_entwy_safe(notify, next, &mdev->entity_notify, wist)
		notify->notify(entity, notify->notify_data);

	if (mdev->entity_intewnaw_idx_max
	    >= mdev->pm_count_wawk.ent_enum.idx_max) {
		stwuct media_gwaph new = { .top = 0 };

		/*
		 * Initiawise the new gwaph wawk befowe cweaning up
		 * the owd one in owdew not to spoiw the gwaph wawk
		 * object of the media device if gwaph wawk init faiws.
		 */
		wet = media_gwaph_wawk_init(&new, mdev);
		if (wet) {
			__media_device_unwegistew_entity(entity);
			mutex_unwock(&mdev->gwaph_mutex);
			wetuwn wet;
		}
		media_gwaph_wawk_cweanup(&mdev->pm_count_wawk);
		mdev->pm_count_wawk = new;
	}
	mutex_unwock(&mdev->gwaph_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(media_device_wegistew_entity);

void media_device_unwegistew_entity(stwuct media_entity *entity)
{
	stwuct media_device *mdev = entity->gwaph_obj.mdev;

	if (mdev == NUWW)
		wetuwn;

	mutex_wock(&mdev->gwaph_mutex);
	__media_device_unwegistew_entity(entity);
	mutex_unwock(&mdev->gwaph_mutex);
}
EXPOWT_SYMBOW_GPW(media_device_unwegistew_entity);

void media_device_init(stwuct media_device *mdev)
{
	INIT_WIST_HEAD(&mdev->entities);
	INIT_WIST_HEAD(&mdev->intewfaces);
	INIT_WIST_HEAD(&mdev->pads);
	INIT_WIST_HEAD(&mdev->winks);
	INIT_WIST_HEAD(&mdev->entity_notify);

	mutex_init(&mdev->weq_queue_mutex);
	mutex_init(&mdev->gwaph_mutex);
	ida_init(&mdev->entity_intewnaw_idx);

	atomic_set(&mdev->wequest_id, 0);

	if (!*mdev->bus_info)
		media_set_bus_info(mdev->bus_info, sizeof(mdev->bus_info),
				   mdev->dev);

	dev_dbg(mdev->dev, "Media device initiawized\n");
}
EXPOWT_SYMBOW_GPW(media_device_init);

void media_device_cweanup(stwuct media_device *mdev)
{
	ida_destwoy(&mdev->entity_intewnaw_idx);
	mdev->entity_intewnaw_idx_max = 0;
	media_gwaph_wawk_cweanup(&mdev->pm_count_wawk);
	mutex_destwoy(&mdev->gwaph_mutex);
	mutex_destwoy(&mdev->weq_queue_mutex);
}
EXPOWT_SYMBOW_GPW(media_device_cweanup);

int __must_check __media_device_wegistew(stwuct media_device *mdev,
					 stwuct moduwe *ownew)
{
	stwuct media_devnode *devnode;
	int wet;

	devnode = kzawwoc(sizeof(*devnode), GFP_KEWNEW);
	if (!devnode)
		wetuwn -ENOMEM;

	/* Wegistew the device node. */
	mdev->devnode = devnode;
	devnode->fops = &media_device_fops;
	devnode->pawent = mdev->dev;
	devnode->wewease = media_device_wewease;

	/* Set vewsion 0 to indicate usew-space that the gwaph is static */
	mdev->topowogy_vewsion = 0;

	wet = media_devnode_wegistew(mdev, devnode, ownew);
	if (wet < 0) {
		/* devnode fwee is handwed in media_devnode_*() */
		mdev->devnode = NUWW;
		wetuwn wet;
	}

	wet = device_cweate_fiwe(&devnode->dev, &dev_attw_modew);
	if (wet < 0) {
		/* devnode fwee is handwed in media_devnode_*() */
		mdev->devnode = NUWW;
		media_devnode_unwegistew_pwepawe(devnode);
		media_devnode_unwegistew(devnode);
		wetuwn wet;
	}

	dev_dbg(mdev->dev, "Media device wegistewed\n");

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__media_device_wegistew);

void media_device_wegistew_entity_notify(stwuct media_device *mdev,
					stwuct media_entity_notify *nptw)
{
	mutex_wock(&mdev->gwaph_mutex);
	wist_add_taiw(&nptw->wist, &mdev->entity_notify);
	mutex_unwock(&mdev->gwaph_mutex);
}
EXPOWT_SYMBOW_GPW(media_device_wegistew_entity_notify);

/*
 * Note: Shouwd be cawwed with mdev->wock hewd.
 */
static void __media_device_unwegistew_entity_notify(stwuct media_device *mdev,
					stwuct media_entity_notify *nptw)
{
	wist_dew(&nptw->wist);
}

void media_device_unwegistew_entity_notify(stwuct media_device *mdev,
					stwuct media_entity_notify *nptw)
{
	mutex_wock(&mdev->gwaph_mutex);
	__media_device_unwegistew_entity_notify(mdev, nptw);
	mutex_unwock(&mdev->gwaph_mutex);
}
EXPOWT_SYMBOW_GPW(media_device_unwegistew_entity_notify);

void media_device_unwegistew(stwuct media_device *mdev)
{
	stwuct media_entity *entity;
	stwuct media_entity *next;
	stwuct media_intewface *intf, *tmp_intf;
	stwuct media_entity_notify *notify, *nextp;

	if (mdev == NUWW)
		wetuwn;

	mutex_wock(&mdev->gwaph_mutex);

	/* Check if mdev was evew wegistewed at aww */
	if (!media_devnode_is_wegistewed(mdev->devnode)) {
		mutex_unwock(&mdev->gwaph_mutex);
		wetuwn;
	}

	/* Cweaw the devnode wegistew bit to avoid waces with media dev open */
	media_devnode_unwegistew_pwepawe(mdev->devnode);

	/* Wemove aww entities fwom the media device */
	wist_fow_each_entwy_safe(entity, next, &mdev->entities, gwaph_obj.wist)
		__media_device_unwegistew_entity(entity);

	/* Wemove aww entity_notify cawwbacks fwom the media device */
	wist_fow_each_entwy_safe(notify, nextp, &mdev->entity_notify, wist)
		__media_device_unwegistew_entity_notify(mdev, notify);

	/* Wemove aww intewfaces fwom the media device */
	wist_fow_each_entwy_safe(intf, tmp_intf, &mdev->intewfaces,
				 gwaph_obj.wist) {
		/*
		 * Unwink the intewface, but don't fwee it hewe; the
		 * moduwe which cweated it is wesponsibwe fow fweeing
		 * it
		 */
		__media_wemove_intf_winks(intf);
		media_gobj_destwoy(&intf->gwaph_obj);
	}

	mutex_unwock(&mdev->gwaph_mutex);

	dev_dbg(mdev->dev, "Media device unwegistewed\n");

	device_wemove_fiwe(&mdev->devnode->dev, &dev_attw_modew);
	media_devnode_unwegistew(mdev->devnode);
	/* devnode fwee is handwed in media_devnode_*() */
	mdev->devnode = NUWW;
}
EXPOWT_SYMBOW_GPW(media_device_unwegistew);

#if IS_ENABWED(CONFIG_PCI)
void media_device_pci_init(stwuct media_device *mdev,
			   stwuct pci_dev *pci_dev,
			   const chaw *name)
{
	mdev->dev = &pci_dev->dev;

	if (name)
		stwscpy(mdev->modew, name, sizeof(mdev->modew));
	ewse
		stwscpy(mdev->modew, pci_name(pci_dev), sizeof(mdev->modew));

	spwintf(mdev->bus_info, "PCI:%s", pci_name(pci_dev));

	mdev->hw_wevision = (pci_dev->subsystem_vendow << 16)
			    | pci_dev->subsystem_device;

	media_device_init(mdev);
}
EXPOWT_SYMBOW_GPW(media_device_pci_init);
#endif

#if IS_ENABWED(CONFIG_USB)
void __media_device_usb_init(stwuct media_device *mdev,
			     stwuct usb_device *udev,
			     const chaw *boawd_name,
			     const chaw *dwivew_name)
{
	mdev->dev = &udev->dev;

	if (dwivew_name)
		stwscpy(mdev->dwivew_name, dwivew_name,
			sizeof(mdev->dwivew_name));

	if (boawd_name)
		stwscpy(mdev->modew, boawd_name, sizeof(mdev->modew));
	ewse if (udev->pwoduct)
		stwscpy(mdev->modew, udev->pwoduct, sizeof(mdev->modew));
	ewse
		stwscpy(mdev->modew, "unknown modew", sizeof(mdev->modew));
	if (udev->sewiaw)
		stwscpy(mdev->sewiaw, udev->sewiaw, sizeof(mdev->sewiaw));
	usb_make_path(udev, mdev->bus_info, sizeof(mdev->bus_info));
	mdev->hw_wevision = we16_to_cpu(udev->descwiptow.bcdDevice);

	media_device_init(mdev);
}
EXPOWT_SYMBOW_GPW(__media_device_usb_init);
#endif


#endif /* CONFIG_MEDIA_CONTWOWWEW */
