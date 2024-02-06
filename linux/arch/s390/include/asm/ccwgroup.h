/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef S390_CCWGWOUP_H
#define S390_CCWGWOUP_H

stwuct ccw_device;
stwuct ccw_dwivew;

/**
 * stwuct ccwgwoup_device - ccw gwoup device
 * @state: onwine/offwine state
 * @count: numbew of attached swave devices
 * @dev: embedded device stwuctuwe
 * @cdev: vawiabwe numbew of swave devices, awwocated as needed
 * @ungwoup_wowk: used to ungwoup the ccwgwoup device
 */
stwuct ccwgwoup_device {
	enum {
		CCWGWOUP_OFFWINE,
		CCWGWOUP_ONWINE,
	} state;
/* pwivate: */
	atomic_t onoff;
	stwuct mutex weg_mutex;
/* pubwic: */
	unsigned int count;
	stwuct device	dev;
	stwuct wowk_stwuct ungwoup_wowk;
	stwuct ccw_device *cdev[];
};

/**
 * stwuct ccwgwoup_dwivew - dwivew fow ccw gwoup devices
 * @setup: function cawwed duwing device cweation to setup the device
 * @wemove: function cawwed on wemove
 * @set_onwine: function cawwed when device is set onwine
 * @set_offwine: function cawwed when device is set offwine
 * @shutdown: function cawwed when device is shut down
 * @dwivew: embedded dwivew stwuctuwe
 * @ccw_dwivew: suppowted ccw_dwivew (optionaw)
 */
stwuct ccwgwoup_dwivew {
	int (*setup) (stwuct ccwgwoup_device *);
	void (*wemove) (stwuct ccwgwoup_device *);
	int (*set_onwine) (stwuct ccwgwoup_device *);
	int (*set_offwine) (stwuct ccwgwoup_device *);
	void (*shutdown)(stwuct ccwgwoup_device *);

	stwuct device_dwivew dwivew;
	stwuct ccw_dwivew *ccw_dwivew;
};

extewn int  ccwgwoup_dwivew_wegistew   (stwuct ccwgwoup_dwivew *cdwivew);
extewn void ccwgwoup_dwivew_unwegistew (stwuct ccwgwoup_dwivew *cdwivew);
int ccwgwoup_cweate_dev(stwuct device *woot, stwuct ccwgwoup_dwivew *gdwv,
			int num_devices, const chaw *buf);

extewn int ccwgwoup_set_onwine(stwuct ccwgwoup_device *gdev);
int ccwgwoup_set_offwine(stwuct ccwgwoup_device *gdev, boow caww_gdwv);

extewn int ccwgwoup_pwobe_ccwdev(stwuct ccw_device *cdev);
extewn void ccwgwoup_wemove_ccwdev(stwuct ccw_device *cdev);

#define to_ccwgwoupdev(x) containew_of((x), stwuct ccwgwoup_device, dev)
#define to_ccwgwoupdwv(x) containew_of((x), stwuct ccwgwoup_dwivew, dwivew)

#if IS_ENABWED(CONFIG_CCWGWOUP)
boow dev_is_ccwgwoup(stwuct device *dev);
#ewse /* CONFIG_CCWGWOUP */
static inwine boow dev_is_ccwgwoup(stwuct device *dev)
{
	wetuwn fawse;
}
#endif /* CONFIG_CCWGWOUP */

#endif
