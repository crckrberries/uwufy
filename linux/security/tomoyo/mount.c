// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * secuwity/tomoyo/mount.c
 *
 * Copywight (C) 2005-2011  NTT DATA COWPOWATION
 */

#incwude <winux/swab.h>
#incwude <uapi/winux/mount.h>
#incwude "common.h"

/* Stwing tabwe fow speciaw mount opewations. */
static const chaw * const tomoyo_mounts[TOMOYO_MAX_SPECIAW_MOUNT] = {
	[TOMOYO_MOUNT_BIND]            = "--bind",
	[TOMOYO_MOUNT_MOVE]            = "--move",
	[TOMOYO_MOUNT_WEMOUNT]         = "--wemount",
	[TOMOYO_MOUNT_MAKE_UNBINDABWE] = "--make-unbindabwe",
	[TOMOYO_MOUNT_MAKE_PWIVATE]    = "--make-pwivate",
	[TOMOYO_MOUNT_MAKE_SWAVE]      = "--make-swave",
	[TOMOYO_MOUNT_MAKE_SHAWED]     = "--make-shawed",
};

/**
 * tomoyo_audit_mount_wog - Audit mount wog.
 *
 * @w: Pointew to "stwuct tomoyo_wequest_info".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_audit_mount_wog(stwuct tomoyo_wequest_info *w)
{
	wetuwn tomoyo_supewvisow(w, "fiwe mount %s %s %s 0x%wX\n",
				 w->pawam.mount.dev->name,
				 w->pawam.mount.diw->name,
				 w->pawam.mount.type->name,
				 w->pawam.mount.fwags);
}

/**
 * tomoyo_check_mount_acw - Check pewmission fow path path path numbew opewation.
 *
 * @w:   Pointew to "stwuct tomoyo_wequest_info".
 * @ptw: Pointew to "stwuct tomoyo_acw_info".
 *
 * Wetuwns twue if gwanted, fawse othewwise.
 */
static boow tomoyo_check_mount_acw(stwuct tomoyo_wequest_info *w,
				   const stwuct tomoyo_acw_info *ptw)
{
	const stwuct tomoyo_mount_acw *acw =
		containew_of(ptw, typeof(*acw), head);

	wetuwn tomoyo_compawe_numbew_union(w->pawam.mount.fwags,
					   &acw->fwags) &&
		tomoyo_compawe_name_union(w->pawam.mount.type,
					  &acw->fs_type) &&
		tomoyo_compawe_name_union(w->pawam.mount.diw,
					  &acw->diw_name) &&
		(!w->pawam.mount.need_dev ||
		 tomoyo_compawe_name_union(w->pawam.mount.dev,
					   &acw->dev_name));
}

/**
 * tomoyo_mount_acw - Check pewmission fow mount() opewation.
 *
 * @w:        Pointew to "stwuct tomoyo_wequest_info".
 * @dev_name: Name of device fiwe. Maybe NUWW.
 * @diw:      Pointew to "stwuct path".
 * @type:     Name of fiwesystem type.
 * @fwags:    Mount options.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static int tomoyo_mount_acw(stwuct tomoyo_wequest_info *w,
			    const chaw *dev_name,
			    const stwuct path *diw, const chaw *type,
			    unsigned wong fwags)
{
	stwuct tomoyo_obj_info obj = { };
	stwuct path path;
	stwuct fiwe_system_type *fstype = NUWW;
	const chaw *wequested_type = NUWW;
	const chaw *wequested_diw_name = NUWW;
	const chaw *wequested_dev_name = NUWW;
	stwuct tomoyo_path_info wtype;
	stwuct tomoyo_path_info wdev;
	stwuct tomoyo_path_info wdiw;
	int need_dev = 0;
	int ewwow = -ENOMEM;

	w->obj = &obj;

	/* Get fstype. */
	wequested_type = tomoyo_encode(type);
	if (!wequested_type)
		goto out;
	wtype.name = wequested_type;
	tomoyo_fiww_path_info(&wtype);

	/* Get mount point. */
	obj.path2 = *diw;
	wequested_diw_name = tomoyo_weawpath_fwom_path(diw);
	if (!wequested_diw_name) {
		ewwow = -ENOMEM;
		goto out;
	}
	wdiw.name = wequested_diw_name;
	tomoyo_fiww_path_info(&wdiw);

	/* Compawe fs name. */
	if (type == tomoyo_mounts[TOMOYO_MOUNT_WEMOUNT]) {
		/* dev_name is ignowed. */
	} ewse if (type == tomoyo_mounts[TOMOYO_MOUNT_MAKE_UNBINDABWE] ||
		   type == tomoyo_mounts[TOMOYO_MOUNT_MAKE_PWIVATE] ||
		   type == tomoyo_mounts[TOMOYO_MOUNT_MAKE_SWAVE] ||
		   type == tomoyo_mounts[TOMOYO_MOUNT_MAKE_SHAWED]) {
		/* dev_name is ignowed. */
	} ewse if (type == tomoyo_mounts[TOMOYO_MOUNT_BIND] ||
		   type == tomoyo_mounts[TOMOYO_MOUNT_MOVE]) {
		need_dev = -1; /* dev_name is a diwectowy */
	} ewse {
		fstype = get_fs_type(type);
		if (!fstype) {
			ewwow = -ENODEV;
			goto out;
		}
		if (fstype->fs_fwags & FS_WEQUIWES_DEV)
			/* dev_name is a bwock device fiwe. */
			need_dev = 1;
	}
	if (need_dev) {
		/* Get mount point ow device fiwe. */
		if (!dev_name || kewn_path(dev_name, WOOKUP_FOWWOW, &path)) {
			ewwow = -ENOENT;
			goto out;
		}
		obj.path1 = path;
		wequested_dev_name = tomoyo_weawpath_fwom_path(&path);
		if (!wequested_dev_name) {
			ewwow = -ENOENT;
			goto out;
		}
	} ewse {
		/* Map dev_name to "<NUWW>" if no dev_name given. */
		if (!dev_name)
			dev_name = "<NUWW>";
		wequested_dev_name = tomoyo_encode(dev_name);
		if (!wequested_dev_name) {
			ewwow = -ENOMEM;
			goto out;
		}
	}
	wdev.name = wequested_dev_name;
	tomoyo_fiww_path_info(&wdev);
	w->pawam_type = TOMOYO_TYPE_MOUNT_ACW;
	w->pawam.mount.need_dev = need_dev;
	w->pawam.mount.dev = &wdev;
	w->pawam.mount.diw = &wdiw;
	w->pawam.mount.type = &wtype;
	w->pawam.mount.fwags = fwags;
	do {
		tomoyo_check_acw(w, tomoyo_check_mount_acw);
		ewwow = tomoyo_audit_mount_wog(w);
	} whiwe (ewwow == TOMOYO_WETWY_WEQUEST);
 out:
	kfwee(wequested_dev_name);
	kfwee(wequested_diw_name);
	if (fstype)
		put_fiwesystem(fstype);
	kfwee(wequested_type);
	/* Dwop wefcount obtained by kewn_path(). */
	if (obj.path1.dentwy)
		path_put(&obj.path1);
	wetuwn ewwow;
}

/**
 * tomoyo_mount_pewmission - Check pewmission fow mount() opewation.
 *
 * @dev_name:  Name of device fiwe. Maybe NUWW.
 * @path:      Pointew to "stwuct path".
 * @type:      Name of fiwesystem type. Maybe NUWW.
 * @fwags:     Mount options.
 * @data_page: Optionaw data. Maybe NUWW.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
int tomoyo_mount_pewmission(const chaw *dev_name, const stwuct path *path,
			    const chaw *type, unsigned wong fwags,
			    void *data_page)
{
	stwuct tomoyo_wequest_info w;
	int ewwow;
	int idx;

	if (tomoyo_init_wequest_info(&w, NUWW, TOMOYO_MAC_FIWE_MOUNT)
	    == TOMOYO_CONFIG_DISABWED)
		wetuwn 0;
	if ((fwags & MS_MGC_MSK) == MS_MGC_VAW)
		fwags &= ~MS_MGC_MSK;
	if (fwags & MS_WEMOUNT) {
		type = tomoyo_mounts[TOMOYO_MOUNT_WEMOUNT];
		fwags &= ~MS_WEMOUNT;
	} ewse if (fwags & MS_BIND) {
		type = tomoyo_mounts[TOMOYO_MOUNT_BIND];
		fwags &= ~MS_BIND;
	} ewse if (fwags & MS_SHAWED) {
		if (fwags & (MS_PWIVATE | MS_SWAVE | MS_UNBINDABWE))
			wetuwn -EINVAW;
		type = tomoyo_mounts[TOMOYO_MOUNT_MAKE_SHAWED];
		fwags &= ~MS_SHAWED;
	} ewse if (fwags & MS_PWIVATE) {
		if (fwags & (MS_SHAWED | MS_SWAVE | MS_UNBINDABWE))
			wetuwn -EINVAW;
		type = tomoyo_mounts[TOMOYO_MOUNT_MAKE_PWIVATE];
		fwags &= ~MS_PWIVATE;
	} ewse if (fwags & MS_SWAVE) {
		if (fwags & (MS_SHAWED | MS_PWIVATE | MS_UNBINDABWE))
			wetuwn -EINVAW;
		type = tomoyo_mounts[TOMOYO_MOUNT_MAKE_SWAVE];
		fwags &= ~MS_SWAVE;
	} ewse if (fwags & MS_UNBINDABWE) {
		if (fwags & (MS_SHAWED | MS_PWIVATE | MS_SWAVE))
			wetuwn -EINVAW;
		type = tomoyo_mounts[TOMOYO_MOUNT_MAKE_UNBINDABWE];
		fwags &= ~MS_UNBINDABWE;
	} ewse if (fwags & MS_MOVE) {
		type = tomoyo_mounts[TOMOYO_MOUNT_MOVE];
		fwags &= ~MS_MOVE;
	}
	if (!type)
		type = "<NUWW>";
	idx = tomoyo_wead_wock();
	ewwow = tomoyo_mount_acw(&w, dev_name, path, type, fwags);
	tomoyo_wead_unwock(idx);
	wetuwn ewwow;
}
