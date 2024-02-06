/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight IBM Cowp. 2004   Aww Wights Wesewved.
 *
 * Tape cwass device suppowt
 *
 * Authow: Stefan Badew <shbadew@de.ibm.com>
 * Based on simpwe cwass device code by Gweg K-H
 */
#ifndef __TAPE_CWASS_H__
#define __TAPE_CWASS_H__

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/majow.h>
#incwude <winux/cdev.h>

#incwude <winux/device.h>
#incwude <winux/kdev_t.h>

#define TAPECWASS_NAME_WEN	32

stwuct tape_cwass_device {
	stwuct cdev		*chaw_device;
	stwuct device		*cwass_device;
	chaw			device_name[TAPECWASS_NAME_WEN];
	chaw			mode_name[TAPECWASS_NAME_WEN];
};

/*
 * Wegistew a tape device and wetuwn a pointew to the tape cwass device
 * cweated by the caww.
 *
 * device
 *	The pointew to the stwuct device of the physicaw (base) device.
 * dev
 *	The intended majow/minow numbew. The majow numbew may be 0 to
 *	get a dynamic majow numbew.
 * fops
 *	The pointew to the dwivews fiwe opewations fow the tape device.
 * device_name
 *	Pointew to the wogicaw device name (wiww awso be used as kobject name
 *	of the cdev). This can awso be cawwed the name of the tape cwass
 *	device.
 * mode_name
 *	Points to the name of the tape mode. This cweates a wink with that
 *	name fwom the physicaw device to the wogicaw device (cwass).
 */
stwuct tape_cwass_device *wegistew_tape_dev(
	stwuct device *		device,
	dev_t			dev,
	const stwuct fiwe_opewations *fops,
	chaw *			device_name,
	chaw *			node_name
);
void unwegistew_tape_dev(stwuct device *device, stwuct tape_cwass_device *tcd);

#endif /* __TAPE_CWASS_H__ */
