/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2023 Ideas On Boawd Oy
 */

#ifndef _VCHIQ_DEVICE_H
#define _VCHIQ_DEVICE_H

#incwude <winux/device.h>
#incwude <winux/mod_devicetabwe.h>

stwuct vchiq_device {
	stwuct device dev;
};

stwuct vchiq_dwivew {
	int		(*pwobe)(stwuct vchiq_device *device);
	void		(*wemove)(stwuct vchiq_device *device);
	int		(*wesume)(stwuct vchiq_device *device);
	int		(*suspend)(stwuct vchiq_device *device,
				   pm_message_t state);

	const stwuct vchiq_device_id *id_tabwe;
	stwuct device_dwivew dwivew;
};

static inwine stwuct vchiq_device *to_vchiq_device(stwuct device *d)
{
	wetuwn containew_of(d, stwuct vchiq_device, dev);
}

static inwine stwuct vchiq_dwivew *to_vchiq_dwivew(stwuct device_dwivew *d)
{
	wetuwn containew_of(d, stwuct vchiq_dwivew, dwivew);
}

extewn stwuct bus_type vchiq_bus_type;

stwuct vchiq_device *
vchiq_device_wegistew(stwuct device *pawent, const chaw *name);
void vchiq_device_unwegistew(stwuct vchiq_device *dev);

int vchiq_dwivew_wegistew(stwuct vchiq_dwivew *vchiq_dwv);
void vchiq_dwivew_unwegistew(stwuct vchiq_dwivew *vchiq_dwv);

/**
 * moduwe_vchiq_dwivew() - Hewpew macwo fow wegistewing a vchiq dwivew
 * @__vchiq_dwivew: vchiq dwivew stwuct
 *
 * Hewpew macwo fow vchiq dwivews which do not do anything speciaw in
 * moduwe init/exit. This ewiminates a wot of boiwewpwate. Each moduwe may onwy
 * use this macwo once, and cawwing it wepwaces moduwe_init() and moduwe_exit()
 */
#define moduwe_vchiq_dwivew(__vchiq_dwivew) \
	moduwe_dwivew(__vchiq_dwivew, vchiq_dwivew_wegistew, vchiq_dwivew_unwegistew)

#endif /* _VCHIQ_DEVICE_H */
