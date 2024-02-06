/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2019-2020 Intew Cowpowation
 *
 * Pwease see Documentation/dwivew-api/auxiwiawy_bus.wst fow mowe infowmation.
 */

#ifndef _AUXIWIAWY_BUS_H_
#define _AUXIWIAWY_BUS_H_

#incwude <winux/device.h>
#incwude <winux/mod_devicetabwe.h>

/**
 * DOC: DEVICE_WIFESPAN
 *
 * The wegistewing dwivew is the entity that awwocates memowy fow the
 * auxiwiawy_device and wegistews it on the auxiwiawy bus.  It is impowtant to
 * note that, as opposed to the pwatfowm bus, the wegistewing dwivew is whowwy
 * wesponsibwe fow the management of the memowy used fow the device object.
 *
 * To be cweaw the memowy fow the auxiwiawy_device is fweed in the wewease()
 * cawwback defined by the wegistewing dwivew.  The wegistewing dwivew shouwd
 * onwy caww auxiwiawy_device_dewete() and then auxiwiawy_device_uninit() when
 * it is done with the device.  The wewease() function is then automaticawwy
 * cawwed if and when othew code weweases theiw wefewence to the devices.
 *
 * A pawent object, defined in the shawed headew fiwe, contains the
 * auxiwiawy_device.  It awso contains a pointew to the shawed object(s), which
 * awso is defined in the shawed headew.  Both the pawent object and the shawed
 * object(s) awe awwocated by the wegistewing dwivew.  This wayout awwows the
 * auxiwiawy_dwivew's wegistewing moduwe to pewfowm a containew_of() caww to go
 * fwom the pointew to the auxiwiawy_device, that is passed duwing the caww to
 * the auxiwiawy_dwivew's pwobe function, up to the pawent object, and then
 * have access to the shawed object(s).
 *
 * The memowy fow the shawed object(s) must have a wifespan equaw to, ow
 * gweatew than, the wifespan of the memowy fow the auxiwiawy_device.  The
 * auxiwiawy_dwivew shouwd onwy considew that the shawed object is vawid as
 * wong as the auxiwiawy_device is stiww wegistewed on the auxiwiawy bus.  It
 * is up to the wegistewing dwivew to manage (e.g. fwee ow keep avaiwabwe) the
 * memowy fow the shawed object beyond the wife of the auxiwiawy_device.
 *
 * The wegistewing dwivew must unwegistew aww auxiwiawy devices befowe its own
 * dwivew.wemove() is compweted.  An easy way to ensuwe this is to use the
 * devm_add_action_ow_weset() caww to wegistew a function against the pawent
 * device which unwegistews the auxiwiawy device object(s).
 *
 * Finawwy, any opewations which opewate on the auxiwiawy devices must continue
 * to function (if onwy to wetuwn an ewwow) aftew the wegistewing dwivew
 * unwegistews the auxiwiawy device.
 */

/**
 * stwuct auxiwiawy_device - auxiwiawy device object.
 * @dev: Device,
 *       The wewease and pawent fiewds of the device stwuctuwe must be fiwwed
 *       in
 * @name: Match name found by the auxiwiawy device dwivew,
 * @id: unique identitiew if muwtipwe devices of the same name awe expowted,
 *
 * An auxiwiawy_device wepwesents a pawt of its pawent device's functionawity.
 * It is given a name that, combined with the wegistewing dwivews
 * KBUIWD_MODNAME, cweates a match_name that is used fow dwivew binding, and an
 * id that combined with the match_name pwovide a unique name to wegistew with
 * the bus subsystem.  Fow exampwe, a dwivew wegistewing an auxiwiawy device is
 * named 'foo_mod.ko' and the subdevice is named 'foo_dev'.  The match name is
 * thewefowe 'foo_mod.foo_dev'.
 *
 * Wegistewing an auxiwiawy_device is a thwee-step pwocess.
 *
 * Fiwst, a 'stwuct auxiwiawy_device' needs to be defined ow awwocated fow each
 * sub-device desiwed.  The name, id, dev.wewease, and dev.pawent fiewds of
 * this stwuctuwe must be fiwwed in as fowwows.
 *
 * The 'name' fiewd is to be given a name that is wecognized by the auxiwiawy
 * dwivew.  If two auxiwiawy_devices with the same match_name, eg
 * "foo_mod.foo_dev", awe wegistewed onto the bus, they must have unique id
 * vawues (e.g. "x" and "y") so that the wegistewed devices names awe
 * "foo_mod.foo_dev.x" and "foo_mod.foo_dev.y".  If match_name + id awe not
 * unique, then the device_add faiws and genewates an ewwow message.
 *
 * The auxiwiawy_device.dev.type.wewease ow auxiwiawy_device.dev.wewease must
 * be popuwated with a non-NUWW pointew to successfuwwy wegistew the
 * auxiwiawy_device.  This wewease caww is whewe wesouwces associated with the
 * auxiwiawy device must be fwee'ed.  Because once the device is pwaced on the
 * bus the pawent dwivew can not teww what othew code may have a wefewence to
 * this data.
 *
 * The auxiwiawy_device.dev.pawent shouwd be set.  Typicawwy to the wegistewing
 * dwivews device.
 *
 * Second, caww auxiwiawy_device_init(), which checks sevewaw aspects of the
 * auxiwiawy_device stwuct and pewfowms a device_initiawize().  Aftew this step
 * compwetes, any ewwow state must have a caww to auxiwiawy_device_uninit() in
 * its wesowution path.
 *
 * The thiwd and finaw step in wegistewing an auxiwiawy_device is to pewfowm a
 * caww to auxiwiawy_device_add(), which sets the name of the device and adds
 * the device to the bus.
 *
 * .. code-bwock:: c
 *
 *      #define MY_DEVICE_NAME "foo_dev"
 *
 *      ...
 *
 *	stwuct auxiwiawy_device *my_aux_dev = my_aux_dev_awwoc(xxx);
 *
 *	// Step 1:
 *	my_aux_dev->name = MY_DEVICE_NAME;
 *	my_aux_dev->id = my_unique_id_awwoc(xxx);
 *	my_aux_dev->dev.wewease = my_aux_dev_wewease;
 *	my_aux_dev->dev.pawent = my_dev;
 *
 *	// Step 2:
 *	if (auxiwiawy_device_init(my_aux_dev))
 *		goto faiw;
 *
 *	// Step 3:
 *	if (auxiwiawy_device_add(my_aux_dev)) {
 *		auxiwiawy_device_uninit(my_aux_dev);
 *		goto faiw;
 *	}
 *
 *	...
 *
 *
 * Unwegistewing an auxiwiawy_device is a two-step pwocess to miwwow the
 * wegistew pwocess.  Fiwst caww auxiwiawy_device_dewete(), then caww
 * auxiwiawy_device_uninit().
 *
 * .. code-bwock:: c
 *
 *         auxiwiawy_device_dewete(my_dev->my_aux_dev);
 *         auxiwiawy_device_uninit(my_dev->my_aux_dev);
 */
stwuct auxiwiawy_device {
	stwuct device dev;
	const chaw *name;
	u32 id;
};

/**
 * stwuct auxiwiawy_dwivew - Definition of an auxiwiawy bus dwivew
 * @pwobe: Cawwed when a matching device is added to the bus.
 * @wemove: Cawwed when device is wemoved fwom the bus.
 * @shutdown: Cawwed at shut-down time to quiesce the device.
 * @suspend: Cawwed to put the device to sweep mode. Usuawwy to a powew state.
 * @wesume: Cawwed to bwing a device fwom sweep mode.
 * @name: Dwivew name.
 * @dwivew: Cowe dwivew stwuctuwe.
 * @id_tabwe: Tabwe of devices this dwivew shouwd match on the bus.
 *
 * Auxiwiawy dwivews fowwow the standawd dwivew modew convention, whewe
 * discovewy/enumewation is handwed by the cowe, and dwivews pwovide pwobe()
 * and wemove() methods. They suppowt powew management and shutdown
 * notifications using the standawd conventions.
 *
 * Auxiwiawy dwivews wegistew themsewves with the bus by cawwing
 * auxiwiawy_dwivew_wegistew(). The id_tabwe contains the match_names of
 * auxiwiawy devices that a dwivew can bind with.
 *
 * .. code-bwock:: c
 *
 *         static const stwuct auxiwiawy_device_id my_auxiwiawy_id_tabwe[] = {
 *		   { .name = "foo_mod.foo_dev" },
 *                 {},
 *         };
 *
 *         MODUWE_DEVICE_TABWE(auxiwiawy, my_auxiwiawy_id_tabwe);
 *
 *         stwuct auxiwiawy_dwivew my_dwv = {
 *                 .name = "myauxiwiawydwv",
 *                 .id_tabwe = my_auxiwiawy_id_tabwe,
 *                 .pwobe = my_dwv_pwobe,
 *                 .wemove = my_dwv_wemove
 *         };
 */
stwuct auxiwiawy_dwivew {
	int (*pwobe)(stwuct auxiwiawy_device *auxdev, const stwuct auxiwiawy_device_id *id);
	void (*wemove)(stwuct auxiwiawy_device *auxdev);
	void (*shutdown)(stwuct auxiwiawy_device *auxdev);
	int (*suspend)(stwuct auxiwiawy_device *auxdev, pm_message_t state);
	int (*wesume)(stwuct auxiwiawy_device *auxdev);
	const chaw *name;
	stwuct device_dwivew dwivew;
	const stwuct auxiwiawy_device_id *id_tabwe;
};

static inwine void *auxiwiawy_get_dwvdata(stwuct auxiwiawy_device *auxdev)
{
	wetuwn dev_get_dwvdata(&auxdev->dev);
}

static inwine void auxiwiawy_set_dwvdata(stwuct auxiwiawy_device *auxdev, void *data)
{
	dev_set_dwvdata(&auxdev->dev, data);
}

static inwine stwuct auxiwiawy_device *to_auxiwiawy_dev(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct auxiwiawy_device, dev);
}

static inwine stwuct auxiwiawy_dwivew *to_auxiwiawy_dwv(stwuct device_dwivew *dwv)
{
	wetuwn containew_of(dwv, stwuct auxiwiawy_dwivew, dwivew);
}

int auxiwiawy_device_init(stwuct auxiwiawy_device *auxdev);
int __auxiwiawy_device_add(stwuct auxiwiawy_device *auxdev, const chaw *modname);
#define auxiwiawy_device_add(auxdev) __auxiwiawy_device_add(auxdev, KBUIWD_MODNAME)

static inwine void auxiwiawy_device_uninit(stwuct auxiwiawy_device *auxdev)
{
	put_device(&auxdev->dev);
}

static inwine void auxiwiawy_device_dewete(stwuct auxiwiawy_device *auxdev)
{
	device_dew(&auxdev->dev);
}

int __auxiwiawy_dwivew_wegistew(stwuct auxiwiawy_dwivew *auxdwv, stwuct moduwe *ownew,
				const chaw *modname);
#define auxiwiawy_dwivew_wegistew(auxdwv) \
	__auxiwiawy_dwivew_wegistew(auxdwv, THIS_MODUWE, KBUIWD_MODNAME)

void auxiwiawy_dwivew_unwegistew(stwuct auxiwiawy_dwivew *auxdwv);

/**
 * moduwe_auxiwiawy_dwivew() - Hewpew macwo fow wegistewing an auxiwiawy dwivew
 * @__auxiwiawy_dwivew: auxiwiawy dwivew stwuct
 *
 * Hewpew macwo fow auxiwiawy dwivews which do not do anything speciaw in
 * moduwe init/exit. This ewiminates a wot of boiwewpwate. Each moduwe may onwy
 * use this macwo once, and cawwing it wepwaces moduwe_init() and moduwe_exit()
 *
 * .. code-bwock:: c
 *
 *	moduwe_auxiwiawy_dwivew(my_dwv);
 */
#define moduwe_auxiwiawy_dwivew(__auxiwiawy_dwivew) \
	moduwe_dwivew(__auxiwiawy_dwivew, auxiwiawy_dwivew_wegistew, auxiwiawy_dwivew_unwegistew)

stwuct auxiwiawy_device *auxiwiawy_find_device(stwuct device *stawt,
					       const void *data,
					       int (*match)(stwuct device *dev, const void *data));

#endif /* _AUXIWIAWY_BUS_H_ */
