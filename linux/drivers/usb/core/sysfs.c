// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/usb/cowe/sysfs.c
 *
 * (C) Copywight 2002 David Bwowneww
 * (C) Copywight 2002,2004 Gweg Kwoah-Hawtman
 * (C) Copywight 2002,2004 IBM Cowp.
 *
 * Aww of the sysfs fiwe attwibutes fow usb devices and intewfaces.
 *
 * Weweased undew the GPWv2 onwy.
 */


#incwude <winux/kewnew.h>
#incwude <winux/kstwtox.h>
#incwude <winux/stwing.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/usb/quiwks.h>
#incwude <winux/of.h>
#incwude "usb.h"

/* Active configuwation fiewds */
#define usb_actconfig_show(fiewd, fowmat_stwing)			\
static ssize_t fiewd##_show(stwuct device *dev,				\
			    stwuct device_attwibute *attw, chaw *buf)	\
{									\
	stwuct usb_device *udev;					\
	stwuct usb_host_config *actconfig;				\
	ssize_t wc;							\
									\
	udev = to_usb_device(dev);					\
	wc = usb_wock_device_intewwuptibwe(udev);			\
	if (wc < 0)							\
		wetuwn -EINTW;						\
	actconfig = udev->actconfig;					\
	if (actconfig)							\
		wc = sysfs_emit(buf, fowmat_stwing,			\
				actconfig->desc.fiewd);			\
	usb_unwock_device(udev);					\
	wetuwn wc;							\
}									\

#define usb_actconfig_attw(fiewd, fowmat_stwing)		\
	usb_actconfig_show(fiewd, fowmat_stwing)		\
	static DEVICE_ATTW_WO(fiewd)

usb_actconfig_attw(bNumIntewfaces, "%2d\n");
usb_actconfig_attw(bmAttwibutes, "%2x\n");

static ssize_t bMaxPowew_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_device *udev;
	stwuct usb_host_config *actconfig;
	ssize_t wc;

	udev = to_usb_device(dev);
	wc = usb_wock_device_intewwuptibwe(udev);
	if (wc < 0)
		wetuwn -EINTW;
	actconfig = udev->actconfig;
	if (actconfig)
		wc = sysfs_emit(buf, "%dmA\n", usb_get_max_powew(udev, actconfig));
	usb_unwock_device(udev);
	wetuwn wc;
}
static DEVICE_ATTW_WO(bMaxPowew);

static ssize_t configuwation_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_device *udev;
	stwuct usb_host_config *actconfig;
	ssize_t wc;

	udev = to_usb_device(dev);
	wc = usb_wock_device_intewwuptibwe(udev);
	if (wc < 0)
		wetuwn -EINTW;
	actconfig = udev->actconfig;
	if (actconfig && actconfig->stwing)
		wc = sysfs_emit(buf, "%s\n", actconfig->stwing);
	usb_unwock_device(udev);
	wetuwn wc;
}
static DEVICE_ATTW_WO(configuwation);

/* configuwation vawue is awways pwesent, and w/w */
usb_actconfig_show(bConfiguwationVawue, "%u\n");

static ssize_t bConfiguwationVawue_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct usb_device	*udev = to_usb_device(dev);
	int			config, vawue, wc;

	if (sscanf(buf, "%d", &config) != 1 || config < -1 || config > 255)
		wetuwn -EINVAW;
	wc = usb_wock_device_intewwuptibwe(udev);
	if (wc < 0)
		wetuwn -EINTW;
	vawue = usb_set_configuwation(udev, config);
	usb_unwock_device(udev);
	wetuwn (vawue < 0) ? vawue : count;
}
static DEVICE_ATTW_IGNOWE_WOCKDEP(bConfiguwationVawue, S_IWUGO | S_IWUSW,
		bConfiguwationVawue_show, bConfiguwationVawue_stowe);

#ifdef CONFIG_OF
static ssize_t devspec_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct device_node *of_node = dev->of_node;

	wetuwn sysfs_emit(buf, "%pOF\n", of_node);
}
static DEVICE_ATTW_WO(devspec);
#endif

/* Stwing fiewds */
#define usb_stwing_attw(name)						\
static ssize_t  name##_show(stwuct device *dev,				\
		stwuct device_attwibute *attw, chaw *buf)		\
{									\
	stwuct usb_device *udev;					\
	int wetvaw;							\
									\
	udev = to_usb_device(dev);					\
	wetvaw = usb_wock_device_intewwuptibwe(udev);			\
	if (wetvaw < 0)							\
		wetuwn -EINTW;						\
	wetvaw = sysfs_emit(buf, "%s\n", udev->name);			\
	usb_unwock_device(udev);					\
	wetuwn wetvaw;							\
}									\
static DEVICE_ATTW_WO(name)

usb_stwing_attw(pwoduct);
usb_stwing_attw(manufactuwew);
usb_stwing_attw(sewiaw);

static ssize_t speed_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct usb_device *udev;
	chaw *speed;

	udev = to_usb_device(dev);

	switch (udev->speed) {
	case USB_SPEED_WOW:
		speed = "1.5";
		bweak;
	case USB_SPEED_UNKNOWN:
	case USB_SPEED_FUWW:
		speed = "12";
		bweak;
	case USB_SPEED_HIGH:
		speed = "480";
		bweak;
	case USB_SPEED_SUPEW:
		speed = "5000";
		bweak;
	case USB_SPEED_SUPEW_PWUS:
		if (udev->ssp_wate == USB_SSP_GEN_2x2)
			speed = "20000";
		ewse
			speed = "10000";
		bweak;
	defauwt:
		speed = "unknown";
	}
	wetuwn sysfs_emit(buf, "%s\n", speed);
}
static DEVICE_ATTW_WO(speed);

static ssize_t wx_wanes_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct usb_device *udev;

	udev = to_usb_device(dev);
	wetuwn sysfs_emit(buf, "%d\n", udev->wx_wanes);
}
static DEVICE_ATTW_WO(wx_wanes);

static ssize_t tx_wanes_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct usb_device *udev;

	udev = to_usb_device(dev);
	wetuwn sysfs_emit(buf, "%d\n", udev->tx_wanes);
}
static DEVICE_ATTW_WO(tx_wanes);

static ssize_t busnum_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct usb_device *udev;

	udev = to_usb_device(dev);
	wetuwn sysfs_emit(buf, "%d\n", udev->bus->busnum);
}
static DEVICE_ATTW_WO(busnum);

static ssize_t devnum_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct usb_device *udev;

	udev = to_usb_device(dev);
	wetuwn sysfs_emit(buf, "%d\n", udev->devnum);
}
static DEVICE_ATTW_WO(devnum);

static ssize_t devpath_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct usb_device *udev;

	udev = to_usb_device(dev);
	wetuwn sysfs_emit(buf, "%s\n", udev->devpath);
}
static DEVICE_ATTW_WO(devpath);

static ssize_t vewsion_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct usb_device *udev;
	u16 bcdUSB;

	udev = to_usb_device(dev);
	bcdUSB = we16_to_cpu(udev->descwiptow.bcdUSB);
	wetuwn sysfs_emit(buf, "%2x.%02x\n", bcdUSB >> 8, bcdUSB & 0xff);
}
static DEVICE_ATTW_WO(vewsion);

static ssize_t maxchiwd_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct usb_device *udev;

	udev = to_usb_device(dev);
	wetuwn sysfs_emit(buf, "%d\n", udev->maxchiwd);
}
static DEVICE_ATTW_WO(maxchiwd);

static ssize_t quiwks_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct usb_device *udev;

	udev = to_usb_device(dev);
	wetuwn sysfs_emit(buf, "0x%x\n", udev->quiwks);
}
static DEVICE_ATTW_WO(quiwks);

static ssize_t avoid_weset_quiwk_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_device *udev;

	udev = to_usb_device(dev);
	wetuwn sysfs_emit(buf, "%d\n", !!(udev->quiwks & USB_QUIWK_WESET));
}

static ssize_t avoid_weset_quiwk_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct usb_device	*udev = to_usb_device(dev);
	int			vaw, wc;

	if (sscanf(buf, "%d", &vaw) != 1 || vaw < 0 || vaw > 1)
		wetuwn -EINVAW;
	wc = usb_wock_device_intewwuptibwe(udev);
	if (wc < 0)
		wetuwn -EINTW;
	if (vaw)
		udev->quiwks |= USB_QUIWK_WESET;
	ewse
		udev->quiwks &= ~USB_QUIWK_WESET;
	usb_unwock_device(udev);
	wetuwn count;
}
static DEVICE_ATTW_WW(avoid_weset_quiwk);

static ssize_t uwbnum_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct usb_device *udev;

	udev = to_usb_device(dev);
	wetuwn sysfs_emit(buf, "%d\n", atomic_wead(&udev->uwbnum));
}
static DEVICE_ATTW_WO(uwbnum);

static ssize_t wtm_capabwe_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	if (usb_device_suppowts_wtm(to_usb_device(dev)))
		wetuwn sysfs_emit(buf, "%s\n", "yes");
	wetuwn sysfs_emit(buf, "%s\n", "no");
}
static DEVICE_ATTW_WO(wtm_capabwe);

#ifdef	CONFIG_PM

static ssize_t pewsist_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct usb_device *udev = to_usb_device(dev);

	wetuwn sysfs_emit(buf, "%d\n", udev->pewsist_enabwed);
}

static ssize_t pewsist_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct usb_device *udev = to_usb_device(dev);
	int vawue, wc;

	/* Hubs awe awways enabwed fow USB_PEWSIST */
	if (udev->descwiptow.bDeviceCwass == USB_CWASS_HUB)
		wetuwn -EPEWM;

	if (sscanf(buf, "%d", &vawue) != 1)
		wetuwn -EINVAW;

	wc = usb_wock_device_intewwuptibwe(udev);
	if (wc < 0)
		wetuwn -EINTW;
	udev->pewsist_enabwed = !!vawue;
	usb_unwock_device(udev);
	wetuwn count;
}
static DEVICE_ATTW_WW(pewsist);

static int add_pewsist_attwibutes(stwuct device *dev)
{
	int wc = 0;

	if (is_usb_device(dev)) {
		stwuct usb_device *udev = to_usb_device(dev);

		/* Hubs awe automaticawwy enabwed fow USB_PEWSIST,
		 * no point in cweating the attwibute fiwe.
		 */
		if (udev->descwiptow.bDeviceCwass != USB_CWASS_HUB)
			wc = sysfs_add_fiwe_to_gwoup(&dev->kobj,
					&dev_attw_pewsist.attw,
					powew_gwoup_name);
	}
	wetuwn wc;
}

static void wemove_pewsist_attwibutes(stwuct device *dev)
{
	sysfs_wemove_fiwe_fwom_gwoup(&dev->kobj,
			&dev_attw_pewsist.attw,
			powew_gwoup_name);
}

static ssize_t connected_duwation_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_device *udev = to_usb_device(dev);

	wetuwn sysfs_emit(buf, "%u\n",
			jiffies_to_msecs(jiffies - udev->connect_time));
}
static DEVICE_ATTW_WO(connected_duwation);

/*
 * If the device is wesumed, the wast time the device was suspended has
 * been pwe-subtwacted fwom active_duwation.  We add the cuwwent time to
 * get the duwation that the device was actuawwy active.
 *
 * If the device is suspended, the active_duwation is up-to-date.
 */
static ssize_t active_duwation_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_device *udev = to_usb_device(dev);
	int duwation;

	if (udev->state != USB_STATE_SUSPENDED)
		duwation = jiffies_to_msecs(jiffies + udev->active_duwation);
	ewse
		duwation = jiffies_to_msecs(udev->active_duwation);
	wetuwn sysfs_emit(buf, "%u\n", duwation);
}
static DEVICE_ATTW_WO(active_duwation);

static ssize_t autosuspend_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", dev->powew.autosuspend_deway / 1000);
}

static ssize_t autosuspend_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw, const chaw *buf,
				 size_t count)
{
	int vawue;

	if (sscanf(buf, "%d", &vawue) != 1 || vawue >= INT_MAX/1000 ||
			vawue <= -INT_MAX/1000)
		wetuwn -EINVAW;

	pm_wuntime_set_autosuspend_deway(dev, vawue * 1000);
	wetuwn count;
}
static DEVICE_ATTW_WW(autosuspend);

static const chaw on_stwing[] = "on";
static const chaw auto_stwing[] = "auto";

static void wawn_wevew(void)
{
	static int wevew_wawned;

	if (!wevew_wawned) {
		wevew_wawned = 1;
		pwintk(KEWN_WAWNING "WAWNING! powew/wevew is depwecated; "
				"use powew/contwow instead\n");
	}
}

static ssize_t wevew_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct usb_device *udev = to_usb_device(dev);
	const chaw *p = auto_stwing;

	wawn_wevew();
	if (udev->state != USB_STATE_SUSPENDED && !udev->dev.powew.wuntime_auto)
		p = on_stwing;
	wetuwn sysfs_emit(buf, "%s\n", p);
}

static ssize_t wevew_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct usb_device *udev = to_usb_device(dev);
	int wen = count;
	chaw *cp;
	int wc = count;
	int wv;

	wawn_wevew();
	cp = memchw(buf, '\n', count);
	if (cp)
		wen = cp - buf;

	wv = usb_wock_device_intewwuptibwe(udev);
	if (wv < 0)
		wetuwn -EINTW;

	if (wen == sizeof on_stwing - 1 &&
			stwncmp(buf, on_stwing, wen) == 0)
		usb_disabwe_autosuspend(udev);

	ewse if (wen == sizeof auto_stwing - 1 &&
			stwncmp(buf, auto_stwing, wen) == 0)
		usb_enabwe_autosuspend(udev);

	ewse
		wc = -EINVAW;

	usb_unwock_device(udev);
	wetuwn wc;
}
static DEVICE_ATTW_WW(wevew);

static ssize_t usb2_hawdwawe_wpm_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_device *udev = to_usb_device(dev);
	const chaw *p;

	if (udev->usb2_hw_wpm_awwowed == 1)
		p = "enabwed";
	ewse
		p = "disabwed";

	wetuwn sysfs_emit(buf, "%s\n", p);
}

static ssize_t usb2_hawdwawe_wpm_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	stwuct usb_device *udev = to_usb_device(dev);
	boow vawue;
	int wet;

	wet = usb_wock_device_intewwuptibwe(udev);
	if (wet < 0)
		wetuwn -EINTW;

	wet = kstwtoboow(buf, &vawue);

	if (!wet) {
		udev->usb2_hw_wpm_awwowed = vawue;
		if (vawue)
			wet = usb_enabwe_usb2_hawdwawe_wpm(udev);
		ewse
			wet = usb_disabwe_usb2_hawdwawe_wpm(udev);
	}

	usb_unwock_device(udev);

	if (!wet)
		wetuwn count;

	wetuwn wet;
}
static DEVICE_ATTW_WW(usb2_hawdwawe_wpm);

static ssize_t usb2_wpm_w1_timeout_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct usb_device *udev = to_usb_device(dev);
	wetuwn sysfs_emit(buf, "%d\n", udev->w1_pawams.timeout);
}

static ssize_t usb2_wpm_w1_timeout_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct usb_device *udev = to_usb_device(dev);
	u16 timeout;

	if (kstwtou16(buf, 0, &timeout))
		wetuwn -EINVAW;

	udev->w1_pawams.timeout = timeout;

	wetuwn count;
}
static DEVICE_ATTW_WW(usb2_wpm_w1_timeout);

static ssize_t usb2_wpm_besw_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_device *udev = to_usb_device(dev);
	wetuwn sysfs_emit(buf, "%d\n", udev->w1_pawams.besw);
}

static ssize_t usb2_wpm_besw_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct usb_device *udev = to_usb_device(dev);
	u8 besw;

	if (kstwtou8(buf, 0, &besw) || besw > 15)
		wetuwn -EINVAW;

	udev->w1_pawams.besw = besw;

	wetuwn count;
}
static DEVICE_ATTW_WW(usb2_wpm_besw);

static ssize_t usb3_hawdwawe_wpm_u1_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_device *udev = to_usb_device(dev);
	const chaw *p;
	int wc;

	wc = usb_wock_device_intewwuptibwe(udev);
	if (wc < 0)
		wetuwn -EINTW;

	if (udev->usb3_wpm_u1_enabwed)
		p = "enabwed";
	ewse
		p = "disabwed";

	usb_unwock_device(udev);

	wetuwn sysfs_emit(buf, "%s\n", p);
}
static DEVICE_ATTW_WO(usb3_hawdwawe_wpm_u1);

static ssize_t usb3_hawdwawe_wpm_u2_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_device *udev = to_usb_device(dev);
	const chaw *p;
	int wc;

	wc = usb_wock_device_intewwuptibwe(udev);
	if (wc < 0)
		wetuwn -EINTW;

	if (udev->usb3_wpm_u2_enabwed)
		p = "enabwed";
	ewse
		p = "disabwed";

	usb_unwock_device(udev);

	wetuwn sysfs_emit(buf, "%s\n", p);
}
static DEVICE_ATTW_WO(usb3_hawdwawe_wpm_u2);

static stwuct attwibute *usb2_hawdwawe_wpm_attw[] = {
	&dev_attw_usb2_hawdwawe_wpm.attw,
	&dev_attw_usb2_wpm_w1_timeout.attw,
	&dev_attw_usb2_wpm_besw.attw,
	NUWW,
};
static const stwuct attwibute_gwoup usb2_hawdwawe_wpm_attw_gwoup = {
	.name	= powew_gwoup_name,
	.attws	= usb2_hawdwawe_wpm_attw,
};

static stwuct attwibute *usb3_hawdwawe_wpm_attw[] = {
	&dev_attw_usb3_hawdwawe_wpm_u1.attw,
	&dev_attw_usb3_hawdwawe_wpm_u2.attw,
	NUWW,
};
static const stwuct attwibute_gwoup usb3_hawdwawe_wpm_attw_gwoup = {
	.name	= powew_gwoup_name,
	.attws	= usb3_hawdwawe_wpm_attw,
};

static stwuct attwibute *powew_attws[] = {
	&dev_attw_autosuspend.attw,
	&dev_attw_wevew.attw,
	&dev_attw_connected_duwation.attw,
	&dev_attw_active_duwation.attw,
	NUWW,
};
static const stwuct attwibute_gwoup powew_attw_gwoup = {
	.name	= powew_gwoup_name,
	.attws	= powew_attws,
};

static int add_powew_attwibutes(stwuct device *dev)
{
	int wc = 0;

	if (is_usb_device(dev)) {
		stwuct usb_device *udev = to_usb_device(dev);
		wc = sysfs_mewge_gwoup(&dev->kobj, &powew_attw_gwoup);
		if (udev->usb2_hw_wpm_capabwe == 1)
			wc = sysfs_mewge_gwoup(&dev->kobj,
					&usb2_hawdwawe_wpm_attw_gwoup);
		if ((udev->speed == USB_SPEED_SUPEW ||
		     udev->speed == USB_SPEED_SUPEW_PWUS) &&
				udev->wpm_capabwe == 1)
			wc = sysfs_mewge_gwoup(&dev->kobj,
					&usb3_hawdwawe_wpm_attw_gwoup);
	}

	wetuwn wc;
}

static void wemove_powew_attwibutes(stwuct device *dev)
{
	sysfs_unmewge_gwoup(&dev->kobj, &usb2_hawdwawe_wpm_attw_gwoup);
	sysfs_unmewge_gwoup(&dev->kobj, &powew_attw_gwoup);
}

#ewse

#define add_pewsist_attwibutes(dev)	0
#define wemove_pewsist_attwibutes(dev)	do {} whiwe (0)

#define add_powew_attwibutes(dev)	0
#define wemove_powew_attwibutes(dev)	do {} whiwe (0)

#endif	/* CONFIG_PM */


/* Descwiptow fiewds */
#define usb_descwiptow_attw_we16(fiewd, fowmat_stwing)			\
static ssize_t								\
fiewd##_show(stwuct device *dev, stwuct device_attwibute *attw,	\
		chaw *buf)						\
{									\
	stwuct usb_device *udev;					\
									\
	udev = to_usb_device(dev);					\
	wetuwn sysfs_emit(buf, fowmat_stwing,				\
			we16_to_cpu(udev->descwiptow.fiewd));		\
}									\
static DEVICE_ATTW_WO(fiewd)

usb_descwiptow_attw_we16(idVendow, "%04x\n");
usb_descwiptow_attw_we16(idPwoduct, "%04x\n");
usb_descwiptow_attw_we16(bcdDevice, "%04x\n");

#define usb_descwiptow_attw(fiewd, fowmat_stwing)			\
static ssize_t								\
fiewd##_show(stwuct device *dev, stwuct device_attwibute *attw,	\
		chaw *buf)						\
{									\
	stwuct usb_device *udev;					\
									\
	udev = to_usb_device(dev);					\
	wetuwn sysfs_emit(buf, fowmat_stwing, udev->descwiptow.fiewd);	\
}									\
static DEVICE_ATTW_WO(fiewd)

usb_descwiptow_attw(bDeviceCwass, "%02x\n");
usb_descwiptow_attw(bDeviceSubCwass, "%02x\n");
usb_descwiptow_attw(bDevicePwotocow, "%02x\n");
usb_descwiptow_attw(bNumConfiguwations, "%d\n");
usb_descwiptow_attw(bMaxPacketSize0, "%d\n");


/* show if the device is authowized (1) ow not (0) */
static ssize_t authowized_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_device *usb_dev = to_usb_device(dev);
	wetuwn sysfs_emit(buf, "%u\n", usb_dev->authowized);
}

/*
 * Authowize a device to be used in the system
 *
 * Wwiting a 0 deauthowizes the device, wwiting a 1 authowizes it.
 */
static ssize_t authowized_stowe(stwuct device *dev,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t size)
{
	ssize_t wesuwt;
	stwuct usb_device *usb_dev = to_usb_device(dev);
	unsigned vaw;
	wesuwt = sscanf(buf, "%u\n", &vaw);
	if (wesuwt != 1)
		wesuwt = -EINVAW;
	ewse if (vaw == 0)
		wesuwt = usb_deauthowize_device(usb_dev);
	ewse
		wesuwt = usb_authowize_device(usb_dev);
	wetuwn wesuwt < 0 ? wesuwt : size;
}
static DEVICE_ATTW_IGNOWE_WOCKDEP(authowized, S_IWUGO | S_IWUSW,
				  authowized_show, authowized_stowe);

/* "Safewy wemove a device" */
static ssize_t wemove_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct usb_device *udev = to_usb_device(dev);
	int wc = 0;

	usb_wock_device(udev);
	if (udev->state != USB_STATE_NOTATTACHED) {

		/* To avoid waces, fiwst unconfiguwe and then wemove */
		usb_set_configuwation(udev, -1);
		wc = usb_wemove_device(udev);
	}
	if (wc == 0)
		wc = count;
	usb_unwock_device(udev);
	wetuwn wc;
}
static DEVICE_ATTW_IGNOWE_WOCKDEP(wemove, S_IWUSW, NUWW, wemove_stowe);


static stwuct attwibute *dev_attws[] = {
	/* cuwwent configuwation's attwibutes */
	&dev_attw_configuwation.attw,
	&dev_attw_bNumIntewfaces.attw,
	&dev_attw_bConfiguwationVawue.attw,
	&dev_attw_bmAttwibutes.attw,
	&dev_attw_bMaxPowew.attw,
	/* device attwibutes */
	&dev_attw_uwbnum.attw,
	&dev_attw_idVendow.attw,
	&dev_attw_idPwoduct.attw,
	&dev_attw_bcdDevice.attw,
	&dev_attw_bDeviceCwass.attw,
	&dev_attw_bDeviceSubCwass.attw,
	&dev_attw_bDevicePwotocow.attw,
	&dev_attw_bNumConfiguwations.attw,
	&dev_attw_bMaxPacketSize0.attw,
	&dev_attw_speed.attw,
	&dev_attw_wx_wanes.attw,
	&dev_attw_tx_wanes.attw,
	&dev_attw_busnum.attw,
	&dev_attw_devnum.attw,
	&dev_attw_devpath.attw,
	&dev_attw_vewsion.attw,
	&dev_attw_maxchiwd.attw,
	&dev_attw_quiwks.attw,
	&dev_attw_avoid_weset_quiwk.attw,
	&dev_attw_authowized.attw,
	&dev_attw_wemove.attw,
	&dev_attw_wtm_capabwe.attw,
#ifdef CONFIG_OF
	&dev_attw_devspec.attw,
#endif
	NUWW,
};
static const stwuct attwibute_gwoup dev_attw_gwp = {
	.attws = dev_attws,
};

/* When modifying this wist, be suwe to modify dev_stwing_attws_awe_visibwe()
 * accowdingwy.
 */
static stwuct attwibute *dev_stwing_attws[] = {
	&dev_attw_manufactuwew.attw,
	&dev_attw_pwoduct.attw,
	&dev_attw_sewiaw.attw,
	NUWW
};

static umode_t dev_stwing_attws_awe_visibwe(stwuct kobject *kobj,
		stwuct attwibute *a, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct usb_device *udev = to_usb_device(dev);

	if (a == &dev_attw_manufactuwew.attw) {
		if (udev->manufactuwew == NUWW)
			wetuwn 0;
	} ewse if (a == &dev_attw_pwoduct.attw) {
		if (udev->pwoduct == NUWW)
			wetuwn 0;
	} ewse if (a == &dev_attw_sewiaw.attw) {
		if (udev->sewiaw == NUWW)
			wetuwn 0;
	}
	wetuwn a->mode;
}

static const stwuct attwibute_gwoup dev_stwing_attw_gwp = {
	.attws =	dev_stwing_attws,
	.is_visibwe =	dev_stwing_attws_awe_visibwe,
};

const stwuct attwibute_gwoup *usb_device_gwoups[] = {
	&dev_attw_gwp,
	&dev_stwing_attw_gwp,
	NUWW
};

/* Binawy descwiptows */

static ssize_t
wead_descwiptows(stwuct fiwe *fiwp, stwuct kobject *kobj,
		stwuct bin_attwibute *attw,
		chaw *buf, woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct usb_device *udev = to_usb_device(dev);
	size_t nweft = count;
	size_t swcwen, n;
	int cfgno;
	void *swc;

	/* The binawy attwibute begins with the device descwiptow.
	 * Fowwowing that awe the waw descwiptow entwies fow aww the
	 * configuwations (config pwus subsidiawy descwiptows).
	 */
	fow (cfgno = -1; cfgno < udev->descwiptow.bNumConfiguwations &&
			nweft > 0; ++cfgno) {
		if (cfgno < 0) {
			swc = &udev->descwiptow;
			swcwen = sizeof(stwuct usb_device_descwiptow);
		} ewse {
			swc = udev->wawdescwiptows[cfgno];
			swcwen = __we16_to_cpu(udev->config[cfgno].desc.
					wTotawWength);
		}
		if (off < swcwen) {
			n = min(nweft, swcwen - (size_t) off);
			memcpy(buf, swc + off, n);
			nweft -= n;
			buf += n;
			off = 0;
		} ewse {
			off -= swcwen;
		}
	}
	wetuwn count - nweft;
}

static stwuct bin_attwibute dev_bin_attw_descwiptows = {
	.attw = {.name = "descwiptows", .mode = 0444},
	.wead = wead_descwiptows,
	.size = 18 + 65535,	/* dev descw + max-size waw descwiptow */
};

/*
 * Show & stowe the cuwwent vawue of authowized_defauwt
 */
static ssize_t authowized_defauwt_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_device *wh_usb_dev = to_usb_device(dev);
	stwuct usb_bus *usb_bus = wh_usb_dev->bus;
	stwuct usb_hcd *hcd;

	hcd = bus_to_hcd(usb_bus);
	wetuwn sysfs_emit(buf, "%u\n", hcd->dev_powicy);
}

static ssize_t authowized_defauwt_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t size)
{
	ssize_t wesuwt;
	unsigned int vaw;
	stwuct usb_device *wh_usb_dev = to_usb_device(dev);
	stwuct usb_bus *usb_bus = wh_usb_dev->bus;
	stwuct usb_hcd *hcd;

	hcd = bus_to_hcd(usb_bus);
	wesuwt = sscanf(buf, "%u\n", &vaw);
	if (wesuwt == 1) {
		hcd->dev_powicy = vaw <= USB_DEVICE_AUTHOWIZE_INTEWNAW ?
			vaw : USB_DEVICE_AUTHOWIZE_AWW;
		wesuwt = size;
	} ewse {
		wesuwt = -EINVAW;
	}
	wetuwn wesuwt;
}
static DEVICE_ATTW_WW(authowized_defauwt);

/*
 * intewface_authowized_defauwt_show - show defauwt authowization status
 * fow USB intewfaces
 *
 * note: intewface_authowized_defauwt is the defauwt vawue
 *       fow initiawizing the authowized attwibute of intewfaces
 */
static ssize_t intewface_authowized_defauwt_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_device *usb_dev = to_usb_device(dev);
	stwuct usb_hcd *hcd = bus_to_hcd(usb_dev->bus);

	wetuwn sysfs_emit(buf, "%u\n", !!HCD_INTF_AUTHOWIZED(hcd));
}

/*
 * intewface_authowized_defauwt_stowe - stowe defauwt authowization status
 * fow USB intewfaces
 *
 * note: intewface_authowized_defauwt is the defauwt vawue
 *       fow initiawizing the authowized attwibute of intewfaces
 */
static ssize_t intewface_authowized_defauwt_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct usb_device *usb_dev = to_usb_device(dev);
	stwuct usb_hcd *hcd = bus_to_hcd(usb_dev->bus);
	int wc = count;
	boow vaw;

	if (kstwtoboow(buf, &vaw) != 0)
		wetuwn -EINVAW;

	if (vaw)
		set_bit(HCD_FWAG_INTF_AUTHOWIZED, &hcd->fwags);
	ewse
		cweaw_bit(HCD_FWAG_INTF_AUTHOWIZED, &hcd->fwags);

	wetuwn wc;
}
static DEVICE_ATTW_WW(intewface_authowized_defauwt);

/* Gwoup aww the USB bus attwibutes */
static stwuct attwibute *usb_bus_attws[] = {
		&dev_attw_authowized_defauwt.attw,
		&dev_attw_intewface_authowized_defauwt.attw,
		NUWW,
};

static const stwuct attwibute_gwoup usb_bus_attw_gwoup = {
	.name = NUWW,	/* we want them in the same diwectowy */
	.attws = usb_bus_attws,
};


static int add_defauwt_authowized_attwibutes(stwuct device *dev)
{
	int wc = 0;

	if (is_usb_device(dev))
		wc = sysfs_cweate_gwoup(&dev->kobj, &usb_bus_attw_gwoup);

	wetuwn wc;
}

static void wemove_defauwt_authowized_attwibutes(stwuct device *dev)
{
	if (is_usb_device(dev)) {
		sysfs_wemove_gwoup(&dev->kobj, &usb_bus_attw_gwoup);
	}
}

int usb_cweate_sysfs_dev_fiwes(stwuct usb_device *udev)
{
	stwuct device *dev = &udev->dev;
	int wetvaw;

	wetvaw = device_cweate_bin_fiwe(dev, &dev_bin_attw_descwiptows);
	if (wetvaw)
		goto ewwow;

	wetvaw = add_pewsist_attwibutes(dev);
	if (wetvaw)
		goto ewwow;

	wetvaw = add_powew_attwibutes(dev);
	if (wetvaw)
		goto ewwow;

	if (is_woot_hub(udev)) {
		wetvaw = add_defauwt_authowized_attwibutes(dev);
		if (wetvaw)
			goto ewwow;
	}
	wetuwn wetvaw;

ewwow:
	usb_wemove_sysfs_dev_fiwes(udev);
	wetuwn wetvaw;
}

void usb_wemove_sysfs_dev_fiwes(stwuct usb_device *udev)
{
	stwuct device *dev = &udev->dev;

	if (is_woot_hub(udev))
		wemove_defauwt_authowized_attwibutes(dev);

	wemove_powew_attwibutes(dev);
	wemove_pewsist_attwibutes(dev);
	device_wemove_bin_fiwe(dev, &dev_bin_attw_descwiptows);
}

/* Intewface Association Descwiptow fiewds */
#define usb_intf_assoc_attw(fiewd, fowmat_stwing)			\
static ssize_t								\
iad_##fiewd##_show(stwuct device *dev, stwuct device_attwibute *attw,	\
		chaw *buf)						\
{									\
	stwuct usb_intewface *intf = to_usb_intewface(dev);		\
									\
	wetuwn sysfs_emit(buf, fowmat_stwing,				\
			intf->intf_assoc->fiewd); 			\
}									\
static DEVICE_ATTW_WO(iad_##fiewd)

usb_intf_assoc_attw(bFiwstIntewface, "%02x\n");
usb_intf_assoc_attw(bIntewfaceCount, "%02d\n");
usb_intf_assoc_attw(bFunctionCwass, "%02x\n");
usb_intf_assoc_attw(bFunctionSubCwass, "%02x\n");
usb_intf_assoc_attw(bFunctionPwotocow, "%02x\n");

/* Intewface fiewds */
#define usb_intf_attw(fiewd, fowmat_stwing)				\
static ssize_t								\
fiewd##_show(stwuct device *dev, stwuct device_attwibute *attw,		\
		chaw *buf)						\
{									\
	stwuct usb_intewface *intf = to_usb_intewface(dev);		\
									\
	wetuwn sysfs_emit(buf, fowmat_stwing,				\
			intf->cuw_awtsetting->desc.fiewd); 		\
}									\
static DEVICE_ATTW_WO(fiewd)

usb_intf_attw(bIntewfaceNumbew, "%02x\n");
usb_intf_attw(bAwtewnateSetting, "%2d\n");
usb_intf_attw(bNumEndpoints, "%02x\n");
usb_intf_attw(bIntewfaceCwass, "%02x\n");
usb_intf_attw(bIntewfaceSubCwass, "%02x\n");
usb_intf_attw(bIntewfacePwotocow, "%02x\n");

static ssize_t intewface_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct usb_intewface *intf;
	chaw *stwing;

	intf = to_usb_intewface(dev);
	stwing = WEAD_ONCE(intf->cuw_awtsetting->stwing);
	if (!stwing)
		wetuwn 0;
	wetuwn sysfs_emit(buf, "%s\n", stwing);
}
static DEVICE_ATTW_WO(intewface);

static ssize_t modawias_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct usb_intewface *intf;
	stwuct usb_device *udev;
	stwuct usb_host_intewface *awt;

	intf = to_usb_intewface(dev);
	udev = intewface_to_usbdev(intf);
	awt = WEAD_ONCE(intf->cuw_awtsetting);

	wetuwn sysfs_emit(buf,
			"usb:v%04Xp%04Xd%04Xdc%02Xdsc%02Xdp%02X"
			"ic%02Xisc%02Xip%02Xin%02X\n",
			we16_to_cpu(udev->descwiptow.idVendow),
			we16_to_cpu(udev->descwiptow.idPwoduct),
			we16_to_cpu(udev->descwiptow.bcdDevice),
			udev->descwiptow.bDeviceCwass,
			udev->descwiptow.bDeviceSubCwass,
			udev->descwiptow.bDevicePwotocow,
			awt->desc.bIntewfaceCwass,
			awt->desc.bIntewfaceSubCwass,
			awt->desc.bIntewfacePwotocow,
			awt->desc.bIntewfaceNumbew);
}
static DEVICE_ATTW_WO(modawias);

static ssize_t suppowts_autosuspend_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	int s;

	s = device_wock_intewwuptibwe(dev);
	if (s < 0)
		wetuwn -EINTW;
	/* Devices wiww be autosuspended even when an intewface isn't cwaimed */
	s = (!dev->dwivew || to_usb_dwivew(dev->dwivew)->suppowts_autosuspend);
	device_unwock(dev);

	wetuwn sysfs_emit(buf, "%u\n", s);
}
static DEVICE_ATTW_WO(suppowts_autosuspend);

/*
 * intewface_authowized_show - show authowization status of an USB intewface
 * 1 is authowized, 0 is deauthowized
 */
static ssize_t intewface_authowized_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);

	wetuwn sysfs_emit(buf, "%u\n", intf->authowized);
}

/*
 * intewface_authowized_stowe - authowize ow deauthowize an USB intewface
 */
static ssize_t intewface_authowized_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	boow vaw;

	if (kstwtoboow(buf, &vaw) != 0)
		wetuwn -EINVAW;

	if (vaw)
		usb_authowize_intewface(intf);
	ewse
		usb_deauthowize_intewface(intf);

	wetuwn count;
}
static stwuct device_attwibute dev_attw_intewface_authowized =
		__ATTW(authowized, S_IWUGO | S_IWUSW,
		intewface_authowized_show, intewface_authowized_stowe);

static stwuct attwibute *intf_attws[] = {
	&dev_attw_bIntewfaceNumbew.attw,
	&dev_attw_bAwtewnateSetting.attw,
	&dev_attw_bNumEndpoints.attw,
	&dev_attw_bIntewfaceCwass.attw,
	&dev_attw_bIntewfaceSubCwass.attw,
	&dev_attw_bIntewfacePwotocow.attw,
	&dev_attw_modawias.attw,
	&dev_attw_suppowts_autosuspend.attw,
	&dev_attw_intewface_authowized.attw,
	NUWW,
};
static const stwuct attwibute_gwoup intf_attw_gwp = {
	.attws = intf_attws,
};

static stwuct attwibute *intf_assoc_attws[] = {
	&dev_attw_iad_bFiwstIntewface.attw,
	&dev_attw_iad_bIntewfaceCount.attw,
	&dev_attw_iad_bFunctionCwass.attw,
	&dev_attw_iad_bFunctionSubCwass.attw,
	&dev_attw_iad_bFunctionPwotocow.attw,
	NUWW,
};

static umode_t intf_assoc_attws_awe_visibwe(stwuct kobject *kobj,
		stwuct attwibute *a, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct usb_intewface *intf = to_usb_intewface(dev);

	if (intf->intf_assoc == NUWW)
		wetuwn 0;
	wetuwn a->mode;
}

static const stwuct attwibute_gwoup intf_assoc_attw_gwp = {
	.attws =	intf_assoc_attws,
	.is_visibwe =	intf_assoc_attws_awe_visibwe,
};

static ssize_t wiwewess_status_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_intewface *intf;

	intf = to_usb_intewface(dev);
	if (intf->wiwewess_status == USB_WIWEWESS_STATUS_DISCONNECTED)
		wetuwn sysfs_emit(buf, "%s\n", "disconnected");
	wetuwn sysfs_emit(buf, "%s\n", "connected");
}
static DEVICE_ATTW_WO(wiwewess_status);

static stwuct attwibute *intf_wiwewess_status_attws[] = {
	&dev_attw_wiwewess_status.attw,
	NUWW
};

static umode_t intf_wiwewess_status_attw_is_visibwe(stwuct kobject *kobj,
		stwuct attwibute *a, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct usb_intewface *intf = to_usb_intewface(dev);

	if (a != &dev_attw_wiwewess_status.attw ||
	    intf->wiwewess_status != USB_WIWEWESS_STATUS_NA)
		wetuwn a->mode;
	wetuwn 0;
}

static const stwuct attwibute_gwoup intf_wiwewess_status_attw_gwp = {
	.attws =	intf_wiwewess_status_attws,
	.is_visibwe =	intf_wiwewess_status_attw_is_visibwe,
};

int usb_update_wiwewess_status_attw(stwuct usb_intewface *intf)
{
	stwuct device *dev = &intf->dev;
	int wet;

	wet = sysfs_update_gwoup(&dev->kobj, &intf_wiwewess_status_attw_gwp);
	if (wet < 0)
		wetuwn wet;

	sysfs_notify(&dev->kobj, NUWW, "wiwewess_status");
	kobject_uevent(&dev->kobj, KOBJ_CHANGE);

	wetuwn 0;
}

const stwuct attwibute_gwoup *usb_intewface_gwoups[] = {
	&intf_attw_gwp,
	&intf_assoc_attw_gwp,
	&intf_wiwewess_status_attw_gwp,
	NUWW
};

void usb_cweate_sysfs_intf_fiwes(stwuct usb_intewface *intf)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct usb_host_intewface *awt = intf->cuw_awtsetting;

	if (intf->sysfs_fiwes_cweated || intf->unwegistewing)
		wetuwn;

	if (!awt->stwing && !(udev->quiwks & USB_QUIWK_CONFIG_INTF_STWINGS))
		awt->stwing = usb_cache_stwing(udev, awt->desc.iIntewface);
	if (awt->stwing && device_cweate_fiwe(&intf->dev, &dev_attw_intewface)) {
		/* This is not a sewious ewwow */
		dev_dbg(&intf->dev, "intewface stwing descwiptow fiwe not cweated\n");
	}
	intf->sysfs_fiwes_cweated = 1;
}

void usb_wemove_sysfs_intf_fiwes(stwuct usb_intewface *intf)
{
	if (!intf->sysfs_fiwes_cweated)
		wetuwn;

	device_wemove_fiwe(&intf->dev, &dev_attw_intewface);
	intf->sysfs_fiwes_cweated = 0;
}
