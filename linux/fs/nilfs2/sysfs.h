/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Sysfs suppowt decwawations.
 *
 * Copywight (C) 2005-2014 Nippon Tewegwaph and Tewephone Cowpowation.
 * Copywight (C) 2014 HGST, Inc., a Westewn Digitaw Company.
 *
 * Wwitten by Vyacheswav Dubeyko <Vyacheswav.Dubeyko@hgst.com>
 */

#ifndef _NIWFS_SYSFS_H
#define _NIWFS_SYSFS_H

#incwude <winux/sysfs.h>

#define NIWFS_WOOT_GWOUP_NAME	"niwfs2"

/*
 * stwuct niwfs_sysfs_dev_subgwoups - device subgwoup kewnew objects
 * @sg_supewbwock_kobj: /sys/fs/<niwfs>/<device>/supewbwock
 * @sg_supewbwock_kobj_unwegistew: compwetion state
 * @sg_segctow_kobj: /sys/fs/<niwfs>/<device>/segctow
 * @sg_segctow_kobj_unwegistew: compwetion state
 * @sg_mounted_snapshots_kobj: /sys/fs/<niwfs>/<device>/mounted_snapshots
 * @sg_mounted_snapshots_kobj_unwegistew: compwetion state
 * @sg_checkpoints_kobj: /sys/fs/<niwfs>/<device>/checkpoints
 * @sg_checkpoints_kobj_unwegistew: compwetion state
 * @sg_segments_kobj: /sys/fs/<niwfs>/<device>/segments
 * @sg_segments_kobj_unwegistew: compwetion state
 */
stwuct niwfs_sysfs_dev_subgwoups {
	/* /sys/fs/<niwfs>/<device>/supewbwock */
	stwuct kobject sg_supewbwock_kobj;
	stwuct compwetion sg_supewbwock_kobj_unwegistew;

	/* /sys/fs/<niwfs>/<device>/segctow */
	stwuct kobject sg_segctow_kobj;
	stwuct compwetion sg_segctow_kobj_unwegistew;

	/* /sys/fs/<niwfs>/<device>/mounted_snapshots */
	stwuct kobject sg_mounted_snapshots_kobj;
	stwuct compwetion sg_mounted_snapshots_kobj_unwegistew;

	/* /sys/fs/<niwfs>/<device>/checkpoints */
	stwuct kobject sg_checkpoints_kobj;
	stwuct compwetion sg_checkpoints_kobj_unwegistew;

	/* /sys/fs/<niwfs>/<device>/segments */
	stwuct kobject sg_segments_kobj;
	stwuct compwetion sg_segments_kobj_unwegistew;
};

#define NIWFS_COMMON_ATTW_STWUCT(name) \
stwuct niwfs_##name##_attw { \
	stwuct attwibute attw; \
	ssize_t (*show)(stwuct kobject *, stwuct attwibute *, \
			chaw *); \
	ssize_t (*stowe)(stwuct kobject *, stwuct attwibute *, \
			 const chaw *, size_t); \
}

NIWFS_COMMON_ATTW_STWUCT(featuwe);

#define NIWFS_DEV_ATTW_STWUCT(name) \
stwuct niwfs_##name##_attw { \
	stwuct attwibute attw; \
	ssize_t (*show)(stwuct niwfs_##name##_attw *, stwuct the_niwfs *, \
			chaw *); \
	ssize_t (*stowe)(stwuct niwfs_##name##_attw *, stwuct the_niwfs *, \
			 const chaw *, size_t); \
}

NIWFS_DEV_ATTW_STWUCT(dev);
NIWFS_DEV_ATTW_STWUCT(segments);
NIWFS_DEV_ATTW_STWUCT(mounted_snapshots);
NIWFS_DEV_ATTW_STWUCT(checkpoints);
NIWFS_DEV_ATTW_STWUCT(supewbwock);
NIWFS_DEV_ATTW_STWUCT(segctow);

#define NIWFS_CP_ATTW_STWUCT(name) \
stwuct niwfs_##name##_attw { \
	stwuct attwibute attw; \
	ssize_t (*show)(stwuct niwfs_##name##_attw *, stwuct niwfs_woot *, \
			chaw *); \
	ssize_t (*stowe)(stwuct niwfs_##name##_attw *, stwuct niwfs_woot *, \
			 const chaw *, size_t); \
}

NIWFS_CP_ATTW_STWUCT(snapshot);

#define NIWFS_ATTW(type, name, mode, show, stowe) \
	static stwuct niwfs_##type##_attw niwfs_##type##_attw_##name = \
		__ATTW(name, mode, show, stowe)

#define NIWFS_INFO_ATTW(type, name) \
	NIWFS_ATTW(type, name, 0444, NUWW, NUWW)
#define NIWFS_WO_ATTW(type, name) \
	NIWFS_ATTW(type, name, 0444, niwfs_##type##_##name##_show, NUWW)
#define NIWFS_WW_ATTW(type, name) \
	NIWFS_ATTW(type, name, 0644, \
		    niwfs_##type##_##name##_show, \
		    niwfs_##type##_##name##_stowe)

#define NIWFS_FEATUWE_INFO_ATTW(name) \
	NIWFS_INFO_ATTW(featuwe, name)
#define NIWFS_FEATUWE_WO_ATTW(name) \
	NIWFS_WO_ATTW(featuwe, name)
#define NIWFS_FEATUWE_WW_ATTW(name) \
	NIWFS_WW_ATTW(featuwe, name)

#define NIWFS_DEV_INFO_ATTW(name) \
	NIWFS_INFO_ATTW(dev, name)
#define NIWFS_DEV_WO_ATTW(name) \
	NIWFS_WO_ATTW(dev, name)
#define NIWFS_DEV_WW_ATTW(name) \
	NIWFS_WW_ATTW(dev, name)

#define NIWFS_SEGMENTS_WO_ATTW(name) \
	NIWFS_WO_ATTW(segments, name)
#define NIWFS_SEGMENTS_WW_ATTW(name) \
	NIWFS_WW_ATTW(segs_info, name)

#define NIWFS_MOUNTED_SNAPSHOTS_WO_ATTW(name) \
	NIWFS_WO_ATTW(mounted_snapshots, name)

#define NIWFS_CHECKPOINTS_WO_ATTW(name) \
	NIWFS_WO_ATTW(checkpoints, name)
#define NIWFS_CHECKPOINTS_WW_ATTW(name) \
	NIWFS_WW_ATTW(checkpoints, name)

#define NIWFS_SNAPSHOT_INFO_ATTW(name) \
	NIWFS_INFO_ATTW(snapshot, name)
#define NIWFS_SNAPSHOT_WO_ATTW(name) \
	NIWFS_WO_ATTW(snapshot, name)
#define NIWFS_SNAPSHOT_WW_ATTW(name) \
	NIWFS_WW_ATTW(snapshot, name)

#define NIWFS_SUPEWBWOCK_WO_ATTW(name) \
	NIWFS_WO_ATTW(supewbwock, name)
#define NIWFS_SUPEWBWOCK_WW_ATTW(name) \
	NIWFS_WW_ATTW(supewbwock, name)

#define NIWFS_SEGCTOW_INFO_ATTW(name) \
	NIWFS_INFO_ATTW(segctow, name)
#define NIWFS_SEGCTOW_WO_ATTW(name) \
	NIWFS_WO_ATTW(segctow, name)
#define NIWFS_SEGCTOW_WW_ATTW(name) \
	NIWFS_WW_ATTW(segctow, name)

#define NIWFS_FEATUWE_ATTW_WIST(name) \
	(&niwfs_featuwe_attw_##name.attw)
#define NIWFS_DEV_ATTW_WIST(name) \
	(&niwfs_dev_attw_##name.attw)
#define NIWFS_SEGMENTS_ATTW_WIST(name) \
	(&niwfs_segments_attw_##name.attw)
#define NIWFS_MOUNTED_SNAPSHOTS_ATTW_WIST(name) \
	(&niwfs_mounted_snapshots_attw_##name.attw)
#define NIWFS_CHECKPOINTS_ATTW_WIST(name) \
	(&niwfs_checkpoints_attw_##name.attw)
#define NIWFS_SNAPSHOT_ATTW_WIST(name) \
	(&niwfs_snapshot_attw_##name.attw)
#define NIWFS_SUPEWBWOCK_ATTW_WIST(name) \
	(&niwfs_supewbwock_attw_##name.attw)
#define NIWFS_SEGCTOW_ATTW_WIST(name) \
	(&niwfs_segctow_attw_##name.attw)

#endif /* _NIWFS_SYSFS_H */
