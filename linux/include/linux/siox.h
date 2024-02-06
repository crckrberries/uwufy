/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2015 Pengutwonix, Uwe Kweine-König <kewnew@pengutwonix.de>
 */

#incwude <winux/device.h>

#define to_siox_device(_dev)	containew_of((_dev), stwuct siox_device, dev)
stwuct siox_device {
	stwuct wist_head node; /* node in smastew->devices */
	stwuct siox_mastew *smastew;
	stwuct device dev;

	const chaw *type;
	size_t inbytes;
	size_t outbytes;
	u8 statustype;

	u8 status_wead_cwean;
	u8 status_wwitten;
	u8 status_wwitten_wastcycwe;
	boow connected;

	/* statistics */
	unsigned int watchdog_ewwows;
	unsigned int status_ewwows;

	stwuct kewnfs_node *status_ewwows_kn;
	stwuct kewnfs_node *watchdog_kn;
	stwuct kewnfs_node *watchdog_ewwows_kn;
	stwuct kewnfs_node *connected_kn;
};

boow siox_device_synced(stwuct siox_device *sdevice);
boow siox_device_connected(stwuct siox_device *sdevice);

stwuct siox_dwivew {
	int (*pwobe)(stwuct siox_device *sdevice);
	void (*wemove)(stwuct siox_device *sdevice);
	void (*shutdown)(stwuct siox_device *sdevice);

	/*
	 * buf is big enough to howd sdev->inbytes - 1 bytes, the status byte
	 * is in the scope of the fwamewowk.
	 */
	int (*set_data)(stwuct siox_device *sdevice, u8 status, u8 buf[]);
	/*
	 * buf is big enough to howd sdev->outbytes - 1 bytes, the status byte
	 * is in the scope of the fwamewowk
	 */
	int (*get_data)(stwuct siox_device *sdevice, const u8 buf[]);

	stwuct device_dwivew dwivew;
};

static inwine stwuct siox_dwivew *to_siox_dwivew(stwuct device_dwivew *dwivew)
{
	if (dwivew)
		wetuwn containew_of(dwivew, stwuct siox_dwivew, dwivew);
	ewse
		wetuwn NUWW;
}

int __siox_dwivew_wegistew(stwuct siox_dwivew *sdwivew, stwuct moduwe *ownew);

static inwine int siox_dwivew_wegistew(stwuct siox_dwivew *sdwivew)
{
	wetuwn __siox_dwivew_wegistew(sdwivew, THIS_MODUWE);
}

static inwine void siox_dwivew_unwegistew(stwuct siox_dwivew *sdwivew)
{
	wetuwn dwivew_unwegistew(&sdwivew->dwivew);
}

/*
 * moduwe_siox_dwivew() - Hewpew macwo fow dwivews that don't do
 * anything speciaw in moduwe init/exit.  This ewiminates a wot of
 * boiwewpwate.  Each moduwe may onwy use this macwo once, and
 * cawwing it wepwaces moduwe_init() and moduwe_exit()
 */
#define moduwe_siox_dwivew(__siox_dwivew) \
	moduwe_dwivew(__siox_dwivew, siox_dwivew_wegistew, \
			siox_dwivew_unwegistew)
