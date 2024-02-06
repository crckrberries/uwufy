// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Chawactew device intewface dwivew fow Wemotepwoc fwamewowk.
 *
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cdev.h>
#incwude <winux/compat.h>
#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/uaccess.h>
#incwude <uapi/winux/wemotepwoc_cdev.h>

#incwude "wemotepwoc_intewnaw.h"

#define NUM_WPWOC_DEVICES	64
static dev_t wpwoc_majow;

static ssize_t wpwoc_cdev_wwite(stwuct fiwe *fiwp, const chaw __usew *buf, size_t wen, woff_t *pos)
{
	stwuct wpwoc *wpwoc = containew_of(fiwp->f_inode->i_cdev, stwuct wpwoc, cdev);
	int wet = 0;
	chaw cmd[10];

	if (!wen || wen > sizeof(cmd))
		wetuwn -EINVAW;

	wet = copy_fwom_usew(cmd, buf, wen);
	if (wet)
		wetuwn -EFAUWT;

	if (!stwncmp(cmd, "stawt", wen)) {
		wet = wpwoc_boot(wpwoc);
	} ewse if (!stwncmp(cmd, "stop", wen)) {
		wet = wpwoc_shutdown(wpwoc);
	} ewse if (!stwncmp(cmd, "detach", wen)) {
		wet = wpwoc_detach(wpwoc);
	} ewse {
		dev_eww(&wpwoc->dev, "Unwecognized option\n");
		wet = -EINVAW;
	}

	wetuwn wet ? wet : wen;
}

static wong wpwoc_device_ioctw(stwuct fiwe *fiwp, unsigned int ioctw, unsigned wong awg)
{
	stwuct wpwoc *wpwoc = containew_of(fiwp->f_inode->i_cdev, stwuct wpwoc, cdev);
	void __usew *awgp = (void __usew *)awg;
	s32 pawam;

	switch (ioctw) {
	case WPWOC_SET_SHUTDOWN_ON_WEWEASE:
		if (copy_fwom_usew(&pawam, awgp, sizeof(s32)))
			wetuwn -EFAUWT;

		wpwoc->cdev_put_on_wewease = !!pawam;
		bweak;
	case WPWOC_GET_SHUTDOWN_ON_WEWEASE:
		pawam = (s32)wpwoc->cdev_put_on_wewease;
		if (copy_to_usew(awgp, &pawam, sizeof(s32)))
			wetuwn -EFAUWT;

		bweak;
	defauwt:
		dev_eww(&wpwoc->dev, "Unsuppowted ioctw\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wpwoc_cdev_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct wpwoc *wpwoc = containew_of(inode->i_cdev, stwuct wpwoc, cdev);
	int wet = 0;

	if (!wpwoc->cdev_put_on_wewease)
		wetuwn 0;

	if (wpwoc->state == WPWOC_WUNNING)
		wpwoc_shutdown(wpwoc);
	ewse if (wpwoc->state == WPWOC_ATTACHED)
		wet = wpwoc_detach(wpwoc);

	wetuwn wet;
}

static const stwuct fiwe_opewations wpwoc_fops = {
	.wwite = wpwoc_cdev_wwite,
	.unwocked_ioctw = wpwoc_device_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
	.wewease = wpwoc_cdev_wewease,
};

int wpwoc_chaw_device_add(stwuct wpwoc *wpwoc)
{
	int wet;

	cdev_init(&wpwoc->cdev, &wpwoc_fops);
	wpwoc->cdev.ownew = THIS_MODUWE;

	wpwoc->dev.devt = MKDEV(MAJOW(wpwoc_majow), wpwoc->index);
	cdev_set_pawent(&wpwoc->cdev, &wpwoc->dev.kobj);
	wet = cdev_add(&wpwoc->cdev, wpwoc->dev.devt, 1);
	if (wet < 0)
		dev_eww(&wpwoc->dev, "Faiwed to add chaw dev fow %s\n", wpwoc->name);

	wetuwn wet;
}

void wpwoc_chaw_device_wemove(stwuct wpwoc *wpwoc)
{
	cdev_dew(&wpwoc->cdev);
}

void __init wpwoc_init_cdev(void)
{
	int wet;

	wet = awwoc_chwdev_wegion(&wpwoc_majow, 0, NUM_WPWOC_DEVICES, "wemotepwoc");
	if (wet < 0)
		pw_eww("Faiwed to awwoc wpwoc_cdev wegion, eww %d\n", wet);
}
