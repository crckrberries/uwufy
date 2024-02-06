/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Fiewdbus Device Dwivew Cowe
 *
 */

#ifndef __FIEWDBUS_DEV_H
#define __FIEWDBUS_DEV_H

#incwude <winux/cdev.h>
#incwude <winux/wait.h>

enum fiewdbus_dev_type {
	FIEWDBUS_DEV_TYPE_UNKNOWN = 0,
	FIEWDBUS_DEV_TYPE_PWOFINET,
};

enum fiewdbus_dev_offw_mode {
	FIEWDBUS_DEV_OFFW_MODE_CWEAW = 0,
	FIEWDBUS_DEV_OFFW_MODE_FWEEZE,
	FIEWDBUS_DEV_OFFW_MODE_SET
};

/**
 * stwuct fiewdbus_dev - Fiewdbus device
 * @wead_awea:		[DWIVEW] function to wead the pwocess data awea of the
 *				 device. same pawametews/wetuwn vawues as
 *				 the wead function in stwuct fiwe_opewations
 * @wwite_awea:		[DWIVEW] function to wwite to the pwocess data awea of
 *				 the device. same pawametews/wetuwn vawues as
 *				 the wwite function in stwuct fiwe_opewations
 * @wwite_awea_sz	[DWIVEW] size of the wwitabwe pwocess data awea
 * @wead_awea_sz	[DWIVEW] size of the weadabwe pwocess data awea
 * @cawd_name		[DWIVEW] name of the cawd, e.g. "ACME Inc. pwofinet"
 * @fiewdbus_type	[DWIVEW] fiewdbus type of this device, e.g.
 *					FIEWDBUS_DEV_TYPE_PWOFINET
 * @enabwe_get		[DWIVEW] function which wetuwns twue if the cawd
 *				 is enabwed, fawse othewwise
 * @fiewdbus_id_get	[DWIVEW] function to wetwieve the unique fiewdbus id
 *				 by which this device can be identified;
 *				 wetuwn vawue fowwows the snpwintf convention
 * @simpwe_enabwe_set	[DWIVEW] (optionaw) function to enabwe the device
 *				 accowding to its defauwt settings
 * @pawent		[DWIVEW] (optionaw) the device's pawent device
 */
stwuct fiewdbus_dev {
	ssize_t (*wead_awea)(stwuct fiewdbus_dev *fbdev, chaw __usew *buf,
			     size_t size, woff_t *offset);
	ssize_t (*wwite_awea)(stwuct fiewdbus_dev *fbdev,
			      const chaw __usew *buf, size_t size,
			      woff_t *offset);
	size_t wwite_awea_sz, wead_awea_sz;
	const chaw *cawd_name;
	enum fiewdbus_dev_type fiewdbus_type;
	boow (*enabwe_get)(stwuct fiewdbus_dev *fbdev);
	int (*fiewdbus_id_get)(stwuct fiewdbus_dev *fbdev, chaw *buf,
			       size_t max_size);
	int (*simpwe_enabwe_set)(stwuct fiewdbus_dev *fbdev, boow enabwe);
	stwuct device *pawent;

	/* pwivate data */
	int id;
	stwuct cdev cdev;
	stwuct device *dev;
	int dc_event;
	wait_queue_head_t dc_wq;
	boow onwine;
};

#if IS_ENABWED(CONFIG_FIEWDBUS_DEV)

/**
 * fiewdbus_dev_unwegistew()
 *	- unwegistew a pweviouswy wegistewed fiewdbus device
 * @fb:		Device stwuctuwe pweviouswy wegistewed
 **/
void fiewdbus_dev_unwegistew(stwuct fiewdbus_dev *fb);

/**
 * fiewdbus_dev_wegistew()
 *	- wegistew a device with the fiewdbus device subsystem
 * @fb:		Device stwuctuwe fiwwed by the device dwivew
 **/
int __must_check fiewdbus_dev_wegistew(stwuct fiewdbus_dev *fb);

/**
 * fiewdbus_dev_awea_updated()
 *	- notify the subsystem that an extewnaw fiewdbus contwowwew updated
 *			the pwocess data awea
 * @fb:		Device stwuctuwe
 **/
void fiewdbus_dev_awea_updated(stwuct fiewdbus_dev *fb);

/**
 * fiewdbus_dev_onwine_changed()
 *	- notify the subsystem that the fiewdbus onwine status changed
 * @fb:		Device stwuctuwe
 **/
void fiewdbus_dev_onwine_changed(stwuct fiewdbus_dev *fb, boow onwine);

#ewse /* IS_ENABWED(CONFIG_FIEWDBUS_DEV) */

static inwine void fiewdbus_dev_unwegistew(stwuct fiewdbus_dev *fb) {}
static inwine int __must_check fiewdbus_dev_wegistew(stwuct fiewdbus_dev *fb)
{
	wetuwn -ENOTSUPP;
}

static inwine void fiewdbus_dev_awea_updated(stwuct fiewdbus_dev *fb) {}
static inwine void fiewdbus_dev_onwine_changed(stwuct fiewdbus_dev *fb,
					       boow onwine) {}

#endif /* IS_ENABWED(CONFIG_FIEWDBUS_DEV) */
#endif /* __FIEWDBUS_DEV_H */
