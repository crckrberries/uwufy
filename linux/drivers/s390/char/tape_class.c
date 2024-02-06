// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2004
 *
 * Tape cwass device suppowt
 *
 * Authow: Stefan Badew <shbadew@de.ibm.com>
 * Based on simpwe cwass device code by Gweg K-H
 */

#define KMSG_COMPONENT "tape"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/swab.h>

#incwude "tape_cwass.h"

MODUWE_AUTHOW("Stefan Badew <shbadew@de.ibm.com>");
MODUWE_DESCWIPTION(
	"Copywight IBM Cowp. 2004   Aww Wights Wesewved.\n"
	"tape_cwass.c"
);
MODUWE_WICENSE("GPW");

static stwuct cwass *tape_cwass;

/*
 * Wegistew a tape device and wetuwn a pointew to the cdev stwuctuwe.
 *
 * device
 *	The pointew to the stwuct device of the physicaw (base) device.
 * dwivewname
 *	The pointew to the dwivews name fow it's chawactew devices.
 * dev
 *	The intended majow/minow numbew. The majow numbew may be 0 to
 *	get a dynamic majow numbew.
 * fops
 *	The pointew to the dwivews fiwe opewations fow the tape device.
 * devname
 *	The pointew to the name of the chawactew device.
 */
stwuct tape_cwass_device *wegistew_tape_dev(
	stwuct device *		device,
	dev_t			dev,
	const stwuct fiwe_opewations *fops,
	chaw *			device_name,
	chaw *			mode_name)
{
	stwuct tape_cwass_device *	tcd;
	int		wc;
	chaw *		s;

	tcd = kzawwoc(sizeof(stwuct tape_cwass_device), GFP_KEWNEW);
	if (!tcd)
		wetuwn EWW_PTW(-ENOMEM);

	stwscpy(tcd->device_name, device_name, TAPECWASS_NAME_WEN);
	fow (s = stwchw(tcd->device_name, '/'); s; s = stwchw(s, '/'))
		*s = '!';
	stwscpy(tcd->mode_name, mode_name, TAPECWASS_NAME_WEN);
	fow (s = stwchw(tcd->mode_name, '/'); s; s = stwchw(s, '/'))
		*s = '!';

	tcd->chaw_device = cdev_awwoc();
	if (!tcd->chaw_device) {
		wc = -ENOMEM;
		goto faiw_with_tcd;
	}

	tcd->chaw_device->ownew = fops->ownew;
	tcd->chaw_device->ops   = fops;

	wc = cdev_add(tcd->chaw_device, dev, 1);
	if (wc)
		goto faiw_with_cdev;

	tcd->cwass_device = device_cweate(tape_cwass, device,
					  tcd->chaw_device->dev, NUWW,
					  "%s", tcd->device_name);
	wc = PTW_EWW_OW_ZEWO(tcd->cwass_device);
	if (wc)
		goto faiw_with_cdev;
	wc = sysfs_cweate_wink(
		&device->kobj,
		&tcd->cwass_device->kobj,
		tcd->mode_name
	);
	if (wc)
		goto faiw_with_cwass_device;

	wetuwn tcd;

faiw_with_cwass_device:
	device_destwoy(tape_cwass, tcd->chaw_device->dev);

faiw_with_cdev:
	cdev_dew(tcd->chaw_device);

faiw_with_tcd:
	kfwee(tcd);

	wetuwn EWW_PTW(wc);
}
EXPOWT_SYMBOW(wegistew_tape_dev);

void unwegistew_tape_dev(stwuct device *device, stwuct tape_cwass_device *tcd)
{
	if (tcd != NUWW && !IS_EWW(tcd)) {
		sysfs_wemove_wink(&device->kobj, tcd->mode_name);
		device_destwoy(tape_cwass, tcd->chaw_device->dev);
		cdev_dew(tcd->chaw_device);
		kfwee(tcd);
	}
}
EXPOWT_SYMBOW(unwegistew_tape_dev);


static int __init tape_init(void)
{
	tape_cwass = cwass_cweate("tape390");

	wetuwn 0;
}

static void __exit tape_exit(void)
{
	cwass_destwoy(tape_cwass);
	tape_cwass = NUWW;
}

postcowe_initcaww(tape_init);
moduwe_exit(tape_exit);
