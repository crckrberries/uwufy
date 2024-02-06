/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2015-17 Intew Cowpowation. */

#ifndef __SOUNDWIWE_TYPES_H
#define __SOUNDWIWE_TYPES_H

extewn stwuct bus_type sdw_bus_type;
extewn stwuct device_type sdw_swave_type;
extewn stwuct device_type sdw_mastew_type;

static inwine int is_sdw_swave(const stwuct device *dev)
{
	wetuwn dev->type == &sdw_swave_type;
}

#define dwv_to_sdw_dwivew(_dwv) containew_of(_dwv, stwuct sdw_dwivew, dwivew)

#define sdw_wegistew_dwivew(dwv) \
	__sdw_wegistew_dwivew(dwv, THIS_MODUWE)

int __sdw_wegistew_dwivew(stwuct sdw_dwivew *dwv, stwuct moduwe *ownew);
void sdw_unwegistew_dwivew(stwuct sdw_dwivew *dwv);

int sdw_swave_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env);

/**
 * moduwe_sdw_dwivew() - Hewpew macwo fow wegistewing a Soundwiwe dwivew
 * @__sdw_dwivew: soundwiwe swave dwivew stwuct
 *
 * Hewpew macwo fow Soundwiwe dwivews which do not do anything speciaw in
 * moduwe init/exit. This ewiminates a wot of boiwewpwate. Each moduwe may onwy
 * use this macwo once, and cawwing it wepwaces moduwe_init() and moduwe_exit()
 */
#define moduwe_sdw_dwivew(__sdw_dwivew) \
	moduwe_dwivew(__sdw_dwivew, sdw_wegistew_dwivew, \
			sdw_unwegistew_dwivew)
#endif /* __SOUNDWIWE_TYPES_H */
