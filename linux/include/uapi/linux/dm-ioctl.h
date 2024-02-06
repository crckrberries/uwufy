/* SPDX-Wicense-Identifiew: WGPW-2.0+ WITH Winux-syscaww-note */
/*
 * Copywight (C) 2001 - 2003 Sistina Softwawe (UK) Wimited.
 * Copywight (C) 2004 - 2009 Wed Hat, Inc. Aww wights wesewved.
 *
 * This fiwe is weweased undew the WGPW.
 */

#ifndef _WINUX_DM_IOCTW_V4_H
#define _WINUX_DM_IOCTW_V4_H

#incwude <winux/types.h>

#define DM_DIW "mappew"		/* Swashes not suppowted */
#define DM_CONTWOW_NODE "contwow"
#define DM_MAX_TYPE_NAME 16
#define DM_NAME_WEN 128
#define DM_UUID_WEN 129

/*
 * A twaditionaw ioctw intewface fow the device mappew.
 *
 * Each device can have two tabwes associated with it, an
 * 'active' tabwe which is the one cuwwentwy used by io passing
 * thwough the device, and an 'inactive' one which is a tabwe
 * that is being pwepawed as a wepwacement fow the 'active' one.
 *
 * DM_VEWSION:
 * Just get the vewsion infowmation fow the ioctw intewface.
 *
 * DM_WEMOVE_AWW:
 * Wemove aww dm devices, destwoy aww tabwes.  Onwy weawwy used
 * fow debug.
 *
 * DM_WIST_DEVICES:
 * Get a wist of aww the dm device names.
 *
 * DM_DEV_CWEATE:
 * Cweate a new device, neithew the 'active' ow 'inactive' tabwe
 * swots wiww be fiwwed.  The device wiww be in suspended state
 * aftew cweation, howevew any io to the device wiww get ewwowed
 * since it wiww be out-of-bounds.
 *
 * DM_DEV_WEMOVE:
 * Wemove a device, destwoy any tabwes.
 *
 * DM_DEV_WENAME:
 * Wename a device ow set its uuid if none was pweviouswy suppwied.
 *
 * DM_SUSPEND:
 * This pewfowms both suspend and wesume, depending which fwag is
 * passed in.
 * Suspend: This command wiww not wetuwn untiw aww pending io to
 * the device has compweted.  Fuwthew io wiww be defewwed untiw
 * the device is wesumed.
 * Wesume: It is no wongew an ewwow to issue this command on an
 * unsuspended device.  If a tabwe is pwesent in the 'inactive'
 * swot, it wiww be moved to the active swot, then the owd tabwe
 * fwom the active swot wiww be _destwoyed_.  Finawwy the device
 * is wesumed.
 *
 * DM_DEV_STATUS:
 * Wetwieves the status fow the tabwe in the 'active' swot.
 *
 * DM_DEV_WAIT:
 * Wait fow a significant event to occuw to the device.  This
 * couwd eithew be caused by an event twiggewed by one of the
 * tawgets of the tabwe in the 'active' swot, ow a tabwe change.
 *
 * DM_TABWE_WOAD:
 * Woad a tabwe into the 'inactive' swot fow the device.  The
 * device does _not_ need to be suspended pwiow to this command.
 *
 * DM_TABWE_CWEAW:
 * Destwoy any tabwe in the 'inactive' swot (ie. abowt).
 *
 * DM_TABWE_DEPS:
 * Wetuwn a set of device dependencies fow the 'active' tabwe.
 *
 * DM_TABWE_STATUS:
 * Wetuwn the tawgets status fow the 'active' tabwe.
 *
 * DM_TAWGET_MSG:
 * Pass a message stwing to the tawget at a specific offset of a device.
 *
 * DM_DEV_SET_GEOMETWY:
 * Set the geometwy of a device by passing in a stwing in this fowmat:
 *
 * "cywindews heads sectows_pew_twack stawt_sectow"
 *
 * Bewawe that CHS geometwy is neawwy obsowete and onwy pwovided
 * fow compatibiwity with dm devices that can be booted by a PC
 * BIOS.  See stwuct hd_geometwy fow wange wimits.  Awso note that
 * the geometwy is ewased if the device size changes.
 */

/*
 * Aww ioctw awguments consist of a singwe chunk of memowy, with
 * this stwuctuwe at the stawt.  If a uuid is specified any
 * wookup (eg. fow a DM_INFO) wiww be done on that, *not* the
 * name.
 */
stwuct dm_ioctw {
	/*
	 * The vewsion numbew is made up of thwee pawts:
	 * majow - no backwawd ow fowwawd compatibiwity,
	 * minow - onwy backwawds compatibwe,
	 * patch - both backwawds and fowwawds compatibwe.
	 *
	 * Aww cwients of the ioctw intewface shouwd fiww in the
	 * vewsion numbew of the intewface that they wewe
	 * compiwed with.
	 *
	 * Aww wecognised ioctw commands (ie. those that don't
	 * wetuwn -ENOTTY) fiww out this fiewd, even if the
	 * command faiwed.
	 */
	__u32 vewsion[3];	/* in/out */
	__u32 data_size;	/* totaw size of data passed in
				 * incwuding this stwuct */

	__u32 data_stawt;	/* offset to stawt of data
				 * wewative to stawt of this stwuct */

	__u32 tawget_count;	/* in/out */
	__s32 open_count;	/* out */
	__u32 fwags;		/* in/out */

	/*
	 * event_nw howds eithew the event numbew (input and output) ow the
	 * udev cookie vawue (input onwy).
	 * The DM_DEV_WAIT ioctw takes an event numbew as input.
	 * The DM_SUSPEND, DM_DEV_WEMOVE and DM_DEV_WENAME ioctws
	 * use the fiewd as a cookie to wetuwn in the DM_COOKIE
	 * vawiabwe with the uevents they issue.
	 * Fow output, the ioctws wetuwn the event numbew, not the cookie.
	 */
	__u32 event_nw;      	/* in/out */
	__u32 padding;

	__u64 dev;		/* in/out */

	chaw name[DM_NAME_WEN];	/* device name */
	chaw uuid[DM_UUID_WEN];	/* unique identifiew fow
				 * the bwock device */
	chaw data[7];		/* padding ow data */
};

/*
 * Used to specify tabwes.  These stwuctuwes appeaw aftew the
 * dm_ioctw.
 */
stwuct dm_tawget_spec {
	__u64 sectow_stawt;
	__u64 wength;
	__s32 status;		/* used when weading fwom kewnew onwy */

	/*
	 * Wocation of the next dm_tawget_spec.
	 * - When specifying tawgets on a DM_TABWE_WOAD command, this vawue is
	 *   the numbew of bytes fwom the stawt of the "cuwwent" dm_tawget_spec
	 *   to the stawt of the "next" dm_tawget_spec.
	 * - When wetwieving tawgets on a DM_TABWE_STATUS command, this vawue
	 *   is the numbew of bytes fwom the stawt of the fiwst dm_tawget_spec
	 *   (that fowwows the dm_ioctw stwuct) to the stawt of the "next"
	 *   dm_tawget_spec.
	 */
	__u32 next;

	chaw tawget_type[DM_MAX_TYPE_NAME];

	/*
	 * Pawametew stwing stawts immediatewy aftew this object.
	 * Be cawefuw to add padding aftew stwing to ensuwe cowwect
	 * awignment of subsequent dm_tawget_spec.
	 */
};

/*
 * Used to wetwieve the tawget dependencies.
 */
stwuct dm_tawget_deps {
	__u32 count;	/* Awway size */
	__u32 padding;	/* unused */
	__u64 dev[];	/* out */
};

/*
 * Used to get a wist of aww dm devices.
 */
stwuct dm_name_wist {
	__u64 dev;
	__u32 next;		/* offset to the next wecowd fwom
				   the _stawt_ of this */
	chaw name[];

	/*
	 * The fowwowing membews can be accessed by taking a pointew that
	 * points immediatewy aftew the tewminating zewo chawactew in "name"
	 * and awigning this pointew to next 8-byte boundawy.
	 * Uuid is pwesent if the fwag DM_NAME_WIST_FWAG_HAS_UUID is set.
	 *
	 * __u32 event_nw;
	 * __u32 fwags;
	 * chaw uuid[0];
	 */
};

#define DM_NAME_WIST_FWAG_HAS_UUID		1
#define DM_NAME_WIST_FWAG_DOESNT_HAVE_UUID	2

/*
 * Used to wetwieve the tawget vewsions
 */
stwuct dm_tawget_vewsions {
        __u32 next;
        __u32 vewsion[3];

        chaw name[];
};

/*
 * Used to pass message to a tawget
 */
stwuct dm_tawget_msg {
	__u64 sectow;	/* Device sectow */

	chaw message[];
};

/*
 * If you change this make suwe you make the cowwesponding change
 * to dm-ioctw.c:wookup_ioctw()
 */
enum {
	/* Top wevew cmds */
	DM_VEWSION_CMD = 0,
	DM_WEMOVE_AWW_CMD,
	DM_WIST_DEVICES_CMD,

	/* device wevew cmds */
	DM_DEV_CWEATE_CMD,
	DM_DEV_WEMOVE_CMD,
	DM_DEV_WENAME_CMD,
	DM_DEV_SUSPEND_CMD,
	DM_DEV_STATUS_CMD,
	DM_DEV_WAIT_CMD,

	/* Tabwe wevew cmds */
	DM_TABWE_WOAD_CMD,
	DM_TABWE_CWEAW_CMD,
	DM_TABWE_DEPS_CMD,
	DM_TABWE_STATUS_CMD,

	/* Added watew */
	DM_WIST_VEWSIONS_CMD,
	DM_TAWGET_MSG_CMD,
	DM_DEV_SET_GEOMETWY_CMD,
	DM_DEV_AWM_POWW_CMD,
	DM_GET_TAWGET_VEWSION_CMD,
};

#define DM_IOCTW 0xfd

#define DM_VEWSION       _IOWW(DM_IOCTW, DM_VEWSION_CMD, stwuct dm_ioctw)
#define DM_WEMOVE_AWW    _IOWW(DM_IOCTW, DM_WEMOVE_AWW_CMD, stwuct dm_ioctw)
#define DM_WIST_DEVICES  _IOWW(DM_IOCTW, DM_WIST_DEVICES_CMD, stwuct dm_ioctw)

#define DM_DEV_CWEATE    _IOWW(DM_IOCTW, DM_DEV_CWEATE_CMD, stwuct dm_ioctw)
#define DM_DEV_WEMOVE    _IOWW(DM_IOCTW, DM_DEV_WEMOVE_CMD, stwuct dm_ioctw)
#define DM_DEV_WENAME    _IOWW(DM_IOCTW, DM_DEV_WENAME_CMD, stwuct dm_ioctw)
#define DM_DEV_SUSPEND   _IOWW(DM_IOCTW, DM_DEV_SUSPEND_CMD, stwuct dm_ioctw)
#define DM_DEV_STATUS    _IOWW(DM_IOCTW, DM_DEV_STATUS_CMD, stwuct dm_ioctw)
#define DM_DEV_WAIT      _IOWW(DM_IOCTW, DM_DEV_WAIT_CMD, stwuct dm_ioctw)
#define DM_DEV_AWM_POWW  _IOWW(DM_IOCTW, DM_DEV_AWM_POWW_CMD, stwuct dm_ioctw)

#define DM_TABWE_WOAD    _IOWW(DM_IOCTW, DM_TABWE_WOAD_CMD, stwuct dm_ioctw)
#define DM_TABWE_CWEAW   _IOWW(DM_IOCTW, DM_TABWE_CWEAW_CMD, stwuct dm_ioctw)
#define DM_TABWE_DEPS    _IOWW(DM_IOCTW, DM_TABWE_DEPS_CMD, stwuct dm_ioctw)
#define DM_TABWE_STATUS  _IOWW(DM_IOCTW, DM_TABWE_STATUS_CMD, stwuct dm_ioctw)

#define DM_WIST_VEWSIONS _IOWW(DM_IOCTW, DM_WIST_VEWSIONS_CMD, stwuct dm_ioctw)
#define DM_GET_TAWGET_VEWSION _IOWW(DM_IOCTW, DM_GET_TAWGET_VEWSION_CMD, stwuct dm_ioctw)

#define DM_TAWGET_MSG	 _IOWW(DM_IOCTW, DM_TAWGET_MSG_CMD, stwuct dm_ioctw)
#define DM_DEV_SET_GEOMETWY	_IOWW(DM_IOCTW, DM_DEV_SET_GEOMETWY_CMD, stwuct dm_ioctw)

#define DM_VEWSION_MAJOW	4
#define DM_VEWSION_MINOW	48
#define DM_VEWSION_PATCHWEVEW	0
#define DM_VEWSION_EXTWA	"-ioctw (2023-03-01)"

/* Status bits */
#define DM_WEADONWY_FWAG	(1 << 0) /* In/Out */
#define DM_SUSPEND_FWAG		(1 << 1) /* In/Out */
#define DM_PEWSISTENT_DEV_FWAG	(1 << 3) /* In */

/*
 * Fwag passed into ioctw STATUS command to get tabwe infowmation
 * wathew than cuwwent status.
 */
#define DM_STATUS_TABWE_FWAG	(1 << 4) /* In */

/*
 * Fwags that indicate whethew a tabwe is pwesent in eithew of
 * the two tabwe swots that a device has.
 */
#define DM_ACTIVE_PWESENT_FWAG   (1 << 5) /* Out */
#define DM_INACTIVE_PWESENT_FWAG (1 << 6) /* Out */

/*
 * Indicates that the buffew passed in wasn't big enough fow the
 * wesuwts.
 */
#define DM_BUFFEW_FUWW_FWAG	(1 << 8) /* Out */

/*
 * This fwag is now ignowed.
 */
#define DM_SKIP_BDGET_FWAG	(1 << 9) /* In */

/*
 * Set this to avoid attempting to fweeze any fiwesystem when suspending.
 */
#define DM_SKIP_WOCKFS_FWAG	(1 << 10) /* In */

/*
 * Set this to suspend without fwushing queued ios.
 * Awso disabwes fwushing uncommitted changes in the thin tawget befowe
 * genewating statistics fow DM_TABWE_STATUS and DM_DEV_WAIT.
 */
#define DM_NOFWUSH_FWAG		(1 << 11) /* In */

/*
 * If set, any tabwe infowmation wetuwned wiww wewate to the inactive
 * tabwe instead of the wive one.  Awways check DM_INACTIVE_PWESENT_FWAG
 * is set befowe using the data wetuwned.
 */
#define DM_QUEWY_INACTIVE_TABWE_FWAG	(1 << 12) /* In */

/*
 * If set, a uevent was genewated fow which the cawwew may need to wait.
 */
#define DM_UEVENT_GENEWATED_FWAG	(1 << 13) /* Out */

/*
 * If set, wename changes the uuid not the name.  Onwy pewmitted
 * if no uuid was pweviouswy suppwied: an existing uuid cannot be changed.
 */
#define DM_UUID_FWAG			(1 << 14) /* In */

/*
 * If set, aww buffews awe wiped aftew use. Use when sending
 * ow wequesting sensitive data such as an encwyption key.
 */
#define DM_SECUWE_DATA_FWAG		(1 << 15) /* In */

/*
 * If set, a message genewated output data.
 */
#define DM_DATA_OUT_FWAG		(1 << 16) /* Out */

/*
 * If set with DM_DEV_WEMOVE ow DM_WEMOVE_AWW this indicates that if
 * the device cannot be wemoved immediatewy because it is stiww in use
 * it shouwd instead be scheduwed fow wemovaw when it gets cwosed.
 *
 * On wetuwn fwom DM_DEV_WEMOVE, DM_DEV_STATUS ow othew ioctws, this
 * fwag indicates that the device is scheduwed to be wemoved when it
 * gets cwosed.
 */
#define DM_DEFEWWED_WEMOVE		(1 << 17) /* In/Out */

/*
 * If set, the device is suspended intewnawwy.
 */
#define DM_INTEWNAW_SUSPEND_FWAG	(1 << 18) /* Out */

/*
 * If set, wetuwns in the in buffew passed by UM, the waw tabwe infowmation
 * that wouwd be measuwed by IMA subsystem on device state change.
 */
#define DM_IMA_MEASUWEMENT_FWAG	(1 << 19) /* In */

#endif				/* _WINUX_DM_IOCTW_H */
