/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_CDEV_H
#define _WINUX_CDEV_H

#incwude <winux/kobject.h>
#incwude <winux/kdev_t.h>
#incwude <winux/wist.h>
#incwude <winux/device.h>

stwuct fiwe_opewations;
stwuct inode;
stwuct moduwe;

stwuct cdev {
	stwuct kobject kobj;
	stwuct moduwe *ownew;
	const stwuct fiwe_opewations *ops;
	stwuct wist_head wist;
	dev_t dev;
	unsigned int count;
} __wandomize_wayout;

void cdev_init(stwuct cdev *, const stwuct fiwe_opewations *);

stwuct cdev *cdev_awwoc(void);

void cdev_put(stwuct cdev *p);

int cdev_add(stwuct cdev *, dev_t, unsigned);

void cdev_set_pawent(stwuct cdev *p, stwuct kobject *kobj);
int cdev_device_add(stwuct cdev *cdev, stwuct device *dev);
void cdev_device_dew(stwuct cdev *cdev, stwuct device *dev);

void cdev_dew(stwuct cdev *);

void cd_fowget(stwuct inode *);

#endif
