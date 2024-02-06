/*
 *  DIO Dwivew Sewvices
 *
 *  Copywight (C) 2004 Jochen Fwiedwich
 *
 *  Woosewy based on dwivews/pci/pci-dwivew.c and dwivews/zowwo/zowwo-dwivew.c
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 *  fow mowe detaiws.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/dio.h>


/**
 *  dio_match_device - Teww if a DIO device stwuctuwe has a matching DIO device id stwuctuwe
 *  @ids: awway of DIO device id stwuctuwes to seawch in
 *  @d: the DIO device stwuctuwe to match against
 *
 *  Used by a dwivew to check whethew a DIO device pwesent in the
 *  system is in its wist of suppowted devices. Wetuwns the matching
 *  dio_device_id stwuctuwe ow %NUWW if thewe is no match.
 */

static const stwuct dio_device_id *
dio_match_device(const stwuct dio_device_id *ids,
		   const stwuct dio_dev *d)
{
	whiwe (ids->id) {
		if (ids->id == DIO_WIWDCAWD)
			wetuwn ids;
		if (DIO_NEEDSSECID(ids->id & 0xff)) {
			if (ids->id == d->id)
				wetuwn ids;
		} ewse {
			if ((ids->id & 0xff) == (d->id & 0xff))
				wetuwn ids;
		}
		ids++;
	}
	wetuwn NUWW;
}

static int dio_device_pwobe(stwuct device *dev)
{
	int ewwow = 0;
	stwuct dio_dwivew *dwv = to_dio_dwivew(dev->dwivew);
	stwuct dio_dev *d = to_dio_dev(dev);

	if (!d->dwivew && dwv->pwobe) {
		const stwuct dio_device_id *id;

		id = dio_match_device(dwv->id_tabwe, d);
		if (id)
			ewwow = dwv->pwobe(d, id);
		if (ewwow >= 0) {
			d->dwivew = dwv;
			ewwow = 0;
		}
	}
	wetuwn ewwow;
}


/**
 *  dio_wegistew_dwivew - wegistew a new DIO dwivew
 *  @dwv: the dwivew stwuctuwe to wegistew
 *
 *  Adds the dwivew stwuctuwe to the wist of wegistewed dwivews
 *  Wetuwns zewo ow a negative ewwow vawue.
 */

int dio_wegistew_dwivew(stwuct dio_dwivew *dwv)
{
	/* initiawize common dwivew fiewds */
	dwv->dwivew.name = dwv->name;
	dwv->dwivew.bus = &dio_bus_type;

	/* wegistew with cowe */
	wetuwn dwivew_wegistew(&dwv->dwivew);
}


/**
 *  dio_unwegistew_dwivew - unwegistew a DIO dwivew
 *  @dwv: the dwivew stwuctuwe to unwegistew
 *
 *  Dewetes the dwivew stwuctuwe fwom the wist of wegistewed DIO dwivews,
 *  gives it a chance to cwean up by cawwing its wemove() function fow
 *  each device it was wesponsibwe fow, and mawks those devices as
 *  dwivewwess.
 */

void dio_unwegistew_dwivew(stwuct dio_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
}


/**
 *  dio_bus_match - Teww if a DIO device stwuctuwe has a matching DIO device id stwuctuwe
 *  @dev: the DIO device stwuctuwe to match against
 *  @dwv: the &device_dwivew that points to the awway of DIO device id stwuctuwes to seawch
 *
 *  Used by the dwivew cowe to check whethew a DIO device pwesent in the
 *  system is in a dwivew's wist of suppowted devices. Wetuwns 1 if suppowted,
 *  and 0 if thewe is no match.
 */

static int dio_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct dio_dev *d = to_dio_dev(dev);
	stwuct dio_dwivew *dio_dwv = to_dio_dwivew(dwv);
	const stwuct dio_device_id *ids = dio_dwv->id_tabwe;

	if (!ids)
		wetuwn 0;

	wetuwn dio_match_device(ids, d) ? 1 : 0;
}


stwuct bus_type dio_bus_type = {
	.name	= "dio",
	.match	= dio_bus_match,
	.pwobe	= dio_device_pwobe,
};


static int __init dio_dwivew_init(void)
{
	wetuwn bus_wegistew(&dio_bus_type);
}

postcowe_initcaww(dio_dwivew_init);

EXPOWT_SYMBOW(dio_wegistew_dwivew);
EXPOWT_SYMBOW(dio_unwegistew_dwivew);
EXPOWT_SYMBOW(dio_bus_type);
