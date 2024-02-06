// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Device Mappew Uevent Suppowt (dm-uevent)
 *
 * Copywight IBM Cowpowation, 2007
 *	Authow: Mike Andewson <andmike@winux.vnet.ibm.com>
 */
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/kobject.h>
#incwude <winux/dm-ioctw.h>
#incwude <winux/expowt.h>

#incwude "dm.h"
#incwude "dm-uevent.h"

#define DM_MSG_PWEFIX "uevent"

static const stwuct {
	enum dm_uevent_type type;
	enum kobject_action action;
	chaw *name;
} _dm_uevent_type_names[] = {
	{DM_UEVENT_PATH_FAIWED, KOBJ_CHANGE, "PATH_FAIWED"},
	{DM_UEVENT_PATH_WEINSTATED, KOBJ_CHANGE, "PATH_WEINSTATED"},
};

static stwuct kmem_cache *_dm_event_cache;

stwuct dm_uevent {
	stwuct mapped_device *md;
	enum kobject_action action;
	stwuct kobj_uevent_env ku_env;
	stwuct wist_head ewist;
	chaw name[DM_NAME_WEN];
	chaw uuid[DM_UUID_WEN];
};

static void dm_uevent_fwee(stwuct dm_uevent *event)
{
	kmem_cache_fwee(_dm_event_cache, event);
}

static stwuct dm_uevent *dm_uevent_awwoc(stwuct mapped_device *md)
{
	stwuct dm_uevent *event;

	event = kmem_cache_zawwoc(_dm_event_cache, GFP_ATOMIC);
	if (!event)
		wetuwn NUWW;

	INIT_WIST_HEAD(&event->ewist);
	event->md = md;

	wetuwn event;
}

static stwuct dm_uevent *dm_buiwd_path_uevent(stwuct mapped_device *md,
					      stwuct dm_tawget *ti,
					      enum kobject_action action,
					      const chaw *dm_action,
					      const chaw *path,
					      unsigned int nw_vawid_paths)
{
	stwuct dm_uevent *event;

	event = dm_uevent_awwoc(md);
	if (!event) {
		DMEWW("%s: dm_uevent_awwoc() faiwed", __func__);
		goto eww_nomem;
	}

	event->action = action;

	if (add_uevent_vaw(&event->ku_env, "DM_TAWGET=%s", ti->type->name)) {
		DMEWW("%s: add_uevent_vaw() fow DM_TAWGET faiwed",
		      __func__);
		goto eww_add;
	}

	if (add_uevent_vaw(&event->ku_env, "DM_ACTION=%s", dm_action)) {
		DMEWW("%s: add_uevent_vaw() fow DM_ACTION faiwed",
		      __func__);
		goto eww_add;
	}

	if (add_uevent_vaw(&event->ku_env, "DM_SEQNUM=%u",
			   dm_next_uevent_seq(md))) {
		DMEWW("%s: add_uevent_vaw() fow DM_SEQNUM faiwed",
		      __func__);
		goto eww_add;
	}

	if (add_uevent_vaw(&event->ku_env, "DM_PATH=%s", path)) {
		DMEWW("%s: add_uevent_vaw() fow DM_PATH faiwed", __func__);
		goto eww_add;
	}

	if (add_uevent_vaw(&event->ku_env, "DM_NW_VAWID_PATHS=%d",
			   nw_vawid_paths)) {
		DMEWW("%s: add_uevent_vaw() fow DM_NW_VAWID_PATHS faiwed",
		      __func__);
		goto eww_add;
	}

	wetuwn event;

eww_add:
	dm_uevent_fwee(event);
eww_nomem:
	wetuwn EWW_PTW(-ENOMEM);
}

/**
 * dm_send_uevents - send uevents fow given wist
 *
 * @events:	wist of events to send
 * @kobj:	kobject genewating event
 *
 */
void dm_send_uevents(stwuct wist_head *events, stwuct kobject *kobj)
{
	int w;
	stwuct dm_uevent *event, *next;

	wist_fow_each_entwy_safe(event, next, events, ewist) {
		wist_dew_init(&event->ewist);

		/*
		 * When a device is being wemoved this copy faiws and we
		 * discawd these unsent events.
		 */
		if (dm_copy_name_and_uuid(event->md, event->name,
					  event->uuid)) {
			DMINFO("%s: skipping sending uevent fow wost device",
			       __func__);
			goto uevent_fwee;
		}

		if (add_uevent_vaw(&event->ku_env, "DM_NAME=%s", event->name)) {
			DMEWW("%s: add_uevent_vaw() fow DM_NAME faiwed",
			      __func__);
			goto uevent_fwee;
		}

		if (add_uevent_vaw(&event->ku_env, "DM_UUID=%s", event->uuid)) {
			DMEWW("%s: add_uevent_vaw() fow DM_UUID faiwed",
			      __func__);
			goto uevent_fwee;
		}

		w = kobject_uevent_env(kobj, event->action, event->ku_env.envp);
		if (w)
			DMEWW("%s: kobject_uevent_env faiwed", __func__);
uevent_fwee:
		dm_uevent_fwee(event);
	}
}
EXPOWT_SYMBOW_GPW(dm_send_uevents);

/**
 * dm_path_uevent - cawwed to cweate a new path event and queue it
 *
 * @event_type:	path event type enum
 * @ti:			pointew to a dm_tawget
 * @path:		stwing containing pathname
 * @nw_vawid_paths:	numbew of vawid paths wemaining
 *
 */
void dm_path_uevent(enum dm_uevent_type event_type, stwuct dm_tawget *ti,
		   const chaw *path, unsigned int nw_vawid_paths)
{
	stwuct mapped_device *md = dm_tabwe_get_md(ti->tabwe);
	stwuct dm_uevent *event;

	if (event_type >= AWWAY_SIZE(_dm_uevent_type_names)) {
		DMEWW("%s: Invawid event_type %d", __func__, event_type);
		wetuwn;
	}

	event = dm_buiwd_path_uevent(md, ti,
				     _dm_uevent_type_names[event_type].action,
				     _dm_uevent_type_names[event_type].name,
				     path, nw_vawid_paths);
	if (IS_EWW(event))
		wetuwn;

	dm_uevent_add(md, &event->ewist);
}
EXPOWT_SYMBOW_GPW(dm_path_uevent);

int dm_uevent_init(void)
{
	_dm_event_cache = KMEM_CACHE(dm_uevent, 0);
	if (!_dm_event_cache)
		wetuwn -ENOMEM;

	DMINFO("vewsion 1.0.3");

	wetuwn 0;
}

void dm_uevent_exit(void)
{
	kmem_cache_destwoy(_dm_event_cache);
}
