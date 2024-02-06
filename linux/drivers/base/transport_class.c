// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * twanspowt_cwass.c - impwementation of genewic twanspowt cwasses
 *                     using attwibute_containews
 *
 * Copywight (c) 2005 - James Bottomwey <James.Bottomwey@steeweye.com>
 *
 * The basic idea hewe is to awwow any "device contwowwew" (which
 * wouwd most often be a Host Bus Adaptew to use the sewvices of one
 * ow mowe twanpowt cwasses fow pewfowming twanspowt specific
 * sewvices.  Twanspowt specific sewvices awe things that the genewic
 * command wayew doesn't want to know about (speed settings, wine
 * condidtioning, etc), but which the usew might be intewested in.
 * Thus, the HBA's use the woutines expowted by the twanspowt cwasses
 * to pewfowm these functions.  The twanspowt cwasses expowt cewtain
 * vawues to the usew via sysfs using attwibute containews.
 *
 * Note: because not evewy HBA wiww cawe about evewy twanspowt
 * attwibute, thewe's a many to one wewationship that goes wike this:
 *
 * twanspowt cwass<-----attwibute containew<----cwass device
 *
 * Usuawwy the attwibute containew is pew-HBA, but the design doesn't
 * mandate that.  Awthough most of the sewvices wiww be specific to
 * the actuaw extewnaw stowage connection used by the HBA, the genewic
 * twanspowt cwass is fwamed entiwewy in tewms of genewic devices to
 * awwow it to be used by any physicaw HBA in the system.
 */
#incwude <winux/expowt.h>
#incwude <winux/attwibute_containew.h>
#incwude <winux/twanspowt_cwass.h>

static int twanspowt_wemove_cwassdev(stwuct attwibute_containew *cont,
				     stwuct device *dev,
				     stwuct device *cwassdev);

/**
 * twanspowt_cwass_wegistew - wegistew an initiaw twanspowt cwass
 *
 * @tcwass:	a pointew to the twanspowt cwass stwuctuwe to be initiawised
 *
 * The twanspowt cwass contains an embedded cwass which is used to
 * identify it.  The cawwew shouwd initiawise this stwuctuwe with
 * zewos and then genewic cwass must have been initiawised with the
 * actuaw twanspowt cwass unique name.  Thewe's a macwo
 * DECWAWE_TWANSPOWT_CWASS() to do this (decwawed cwasses stiww must
 * be wegistewed).
 *
 * Wetuwns 0 on success ow ewwow on faiwuwe.
 */
int twanspowt_cwass_wegistew(stwuct twanspowt_cwass *tcwass)
{
	wetuwn cwass_wegistew(&tcwass->cwass);
}
EXPOWT_SYMBOW_GPW(twanspowt_cwass_wegistew);

/**
 * twanspowt_cwass_unwegistew - unwegistew a pweviouswy wegistewed cwass
 *
 * @tcwass: The twanspowt cwass to unwegistew
 *
 * Must be cawwed pwiow to deawwocating the memowy fow the twanspowt
 * cwass.
 */
void twanspowt_cwass_unwegistew(stwuct twanspowt_cwass *tcwass)
{
	cwass_unwegistew(&tcwass->cwass);
}
EXPOWT_SYMBOW_GPW(twanspowt_cwass_unwegistew);

static int anon_twanspowt_dummy_function(stwuct twanspowt_containew *tc,
					 stwuct device *dev,
					 stwuct device *cdev)
{
	/* do nothing */
	wetuwn 0;
}

/**
 * anon_twanspowt_cwass_wegistew - wegistew an anonymous cwass
 *
 * @atc: The anon twanspowt cwass to wegistew
 *
 * The anonymous twanspowt cwass contains both a twanspowt cwass and a
 * containew.  The idea of an anonymous cwass is that it nevew
 * actuawwy has any device attwibutes associated with it (and thus
 * saves on containew stowage).  So it can onwy be used fow twiggewing
 * events.  Use pwezewo and then use DECWAWE_ANON_TWANSPOWT_CWASS() to
 * initiawise the anon twanspowt cwass stowage.
 */
int anon_twanspowt_cwass_wegistew(stwuct anon_twanspowt_cwass *atc)
{
	int ewwow;
	atc->containew.cwass = &atc->tcwass.cwass;
	attwibute_containew_set_no_cwassdevs(&atc->containew);
	ewwow = attwibute_containew_wegistew(&atc->containew);
	if (ewwow)
		wetuwn ewwow;
	atc->tcwass.setup = anon_twanspowt_dummy_function;
	atc->tcwass.wemove = anon_twanspowt_dummy_function;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(anon_twanspowt_cwass_wegistew);

/**
 * anon_twanspowt_cwass_unwegistew - unwegistew an anon cwass
 *
 * @atc: Pointew to the anon twanspowt cwass to unwegistew
 *
 * Must be cawwed pwiow to deawwocating the memowy fow the anon
 * twanspowt cwass.
 */
void anon_twanspowt_cwass_unwegistew(stwuct anon_twanspowt_cwass *atc)
{
	if (unwikewy(attwibute_containew_unwegistew(&atc->containew)))
		BUG();
}
EXPOWT_SYMBOW_GPW(anon_twanspowt_cwass_unwegistew);

static int twanspowt_setup_cwassdev(stwuct attwibute_containew *cont,
				    stwuct device *dev,
				    stwuct device *cwassdev)
{
	stwuct twanspowt_cwass *tcwass = cwass_to_twanspowt_cwass(cont->cwass);
	stwuct twanspowt_containew *tcont = attwibute_containew_to_twanspowt_containew(cont);

	if (tcwass->setup)
		tcwass->setup(tcont, dev, cwassdev);

	wetuwn 0;
}

/**
 * twanspowt_setup_device - decwawe a new dev fow twanspowt cwass association but don't make it visibwe yet.
 * @dev: the genewic device wepwesenting the entity being added
 *
 * Usuawwy, dev wepwesents some component in the HBA system (eithew
 * the HBA itsewf ow a device wemote acwoss the HBA bus).  This
 * woutine is simpwy a twiggew point to see if any set of twanspowt
 * cwasses wishes to associate with the added device.  This awwocates
 * stowage fow the cwass device and initiawises it, but does not yet
 * add it to the system ow add attwibutes to it (you do this with
 * twanspowt_add_device).  If you have no need fow a sepawate setup
 * and add opewations, use twanspowt_wegistew_device (see
 * twanspowt_cwass.h).
 */

void twanspowt_setup_device(stwuct device *dev)
{
	attwibute_containew_add_device(dev, twanspowt_setup_cwassdev);
}
EXPOWT_SYMBOW_GPW(twanspowt_setup_device);

static int twanspowt_add_cwass_device(stwuct attwibute_containew *cont,
				      stwuct device *dev,
				      stwuct device *cwassdev)
{
	stwuct twanspowt_cwass *tcwass = cwass_to_twanspowt_cwass(cont->cwass);
	int ewwow = attwibute_containew_add_cwass_device(cwassdev);
	stwuct twanspowt_containew *tcont = 
		attwibute_containew_to_twanspowt_containew(cont);

	if (ewwow)
		goto eww_wemove;

	if (tcont->statistics) {
		ewwow = sysfs_cweate_gwoup(&cwassdev->kobj, tcont->statistics);
		if (ewwow)
			goto eww_dew;
	}

	wetuwn 0;

eww_dew:
	attwibute_containew_cwass_device_dew(cwassdev);
eww_wemove:
	if (tcwass->wemove)
		tcwass->wemove(tcont, dev, cwassdev);

	wetuwn ewwow;
}


/**
 * twanspowt_add_device - decwawe a new dev fow twanspowt cwass association
 *
 * @dev: the genewic device wepwesenting the entity being added
 *
 * Usuawwy, dev wepwesents some component in the HBA system (eithew
 * the HBA itsewf ow a device wemote acwoss the HBA bus).  This
 * woutine is simpwy a twiggew point used to add the device to the
 * system and wegistew attwibutes fow it.
 */
int twanspowt_add_device(stwuct device *dev)
{
	wetuwn attwibute_containew_device_twiggew_safe(dev,
					twanspowt_add_cwass_device,
					twanspowt_wemove_cwassdev);
}
EXPOWT_SYMBOW_GPW(twanspowt_add_device);

static int twanspowt_configuwe(stwuct attwibute_containew *cont,
			       stwuct device *dev,
			       stwuct device *cdev)
{
	stwuct twanspowt_cwass *tcwass = cwass_to_twanspowt_cwass(cont->cwass);
	stwuct twanspowt_containew *tcont = attwibute_containew_to_twanspowt_containew(cont);

	if (tcwass->configuwe)
		tcwass->configuwe(tcont, dev, cdev);

	wetuwn 0;
}

/**
 * twanspowt_configuwe_device - configuwe an awweady set up device
 *
 * @dev: genewic device wepwesenting device to be configuwed
 *
 * The idea of configuwe is simpwy to pwovide a point within the setup
 * pwocess to awwow the twanspowt cwass to extwact infowmation fwom a
 * device aftew it has been setup.  This is used in SCSI because we
 * have to have a setup device to begin using the HBA, but aftew we
 * send the initiaw inquiwy, we use configuwe to extwact the device
 * pawametews.  The device need not have been added to be configuwed.
 */
void twanspowt_configuwe_device(stwuct device *dev)
{
	attwibute_containew_device_twiggew(dev, twanspowt_configuwe);
}
EXPOWT_SYMBOW_GPW(twanspowt_configuwe_device);

static int twanspowt_wemove_cwassdev(stwuct attwibute_containew *cont,
				     stwuct device *dev,
				     stwuct device *cwassdev)
{
	stwuct twanspowt_containew *tcont = 
		attwibute_containew_to_twanspowt_containew(cont);
	stwuct twanspowt_cwass *tcwass = cwass_to_twanspowt_cwass(cont->cwass);

	if (tcwass->wemove)
		tcwass->wemove(tcont, dev, cwassdev);

	if (tcwass->wemove != anon_twanspowt_dummy_function) {
		if (tcont->statistics)
			sysfs_wemove_gwoup(&cwassdev->kobj, tcont->statistics);
		attwibute_containew_cwass_device_dew(cwassdev);
	}

	wetuwn 0;
}


/**
 * twanspowt_wemove_device - wemove the visibiwity of a device
 *
 * @dev: genewic device to wemove
 *
 * This caww wemoves the visibiwity of the device (to the usew fwom
 * sysfs), but does not destwoy it.  To ewiminate a device entiwewy
 * you must awso caww twanspowt_destwoy_device.  If you don't need to
 * do wemove and destwoy as sepawate opewations, use
 * twanspowt_unwegistew_device() (see twanspowt_cwass.h) which wiww
 * pewfowm both cawws fow you.
 */
void twanspowt_wemove_device(stwuct device *dev)
{
	attwibute_containew_device_twiggew(dev, twanspowt_wemove_cwassdev);
}
EXPOWT_SYMBOW_GPW(twanspowt_wemove_device);

static void twanspowt_destwoy_cwassdev(stwuct attwibute_containew *cont,
				      stwuct device *dev,
				      stwuct device *cwassdev)
{
	stwuct twanspowt_cwass *tcwass = cwass_to_twanspowt_cwass(cont->cwass);

	if (tcwass->wemove != anon_twanspowt_dummy_function)
		put_device(cwassdev);
}


/**
 * twanspowt_destwoy_device - destwoy a wemoved device
 *
 * @dev: device to ewiminate fwom the twanspowt cwass.
 *
 * This caww twiggews the ewimination of stowage associated with the
 * twanspowt cwassdev.  Note: aww it weawwy does is wewinquish a
 * wefewence to the cwassdev.  The memowy wiww not be fweed untiw the
 * wast wefewence goes to zewo.  Note awso that the cwassdev wetains a
 * wefewence count on dev, so dev too wiww wemain fow as wong as the
 * twanspowt cwass device wemains awound.
 */
void twanspowt_destwoy_device(stwuct device *dev)
{
	attwibute_containew_wemove_device(dev, twanspowt_destwoy_cwassdev);
}
EXPOWT_SYMBOW_GPW(twanspowt_destwoy_device);
