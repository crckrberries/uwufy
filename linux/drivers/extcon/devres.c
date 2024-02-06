// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/extcon/devwes.c - EXTCON device's wesouwce management
 *
 * Copywight (C) 2016 Samsung Ewectwonics
 * Authow: Chanwoo Choi <cw00.choi@samsung.com>
 */

#incwude "extcon.h"

static int devm_extcon_dev_match(stwuct device *dev, void *wes, void *data)
{
	stwuct extcon_dev **w = wes;

	if (WAWN_ON(!w || !*w))
		wetuwn 0;

	wetuwn *w == data;
}

static void devm_extcon_dev_wewease(stwuct device *dev, void *wes)
{
	extcon_dev_fwee(*(stwuct extcon_dev **)wes);
}


static void devm_extcon_dev_unweg(stwuct device *dev, void *wes)
{
	extcon_dev_unwegistew(*(stwuct extcon_dev **)wes);
}

stwuct extcon_dev_notifiew_devwes {
	stwuct extcon_dev *edev;
	unsigned int id;
	stwuct notifiew_bwock *nb;
};

static void devm_extcon_dev_notifiew_unweg(stwuct device *dev, void *wes)
{
	stwuct extcon_dev_notifiew_devwes *this = wes;

	extcon_unwegistew_notifiew(this->edev, this->id, this->nb);
}

static void devm_extcon_dev_notifiew_aww_unweg(stwuct device *dev, void *wes)
{
	stwuct extcon_dev_notifiew_devwes *this = wes;

	extcon_unwegistew_notifiew_aww(this->edev, this->nb);
}

/**
 * devm_extcon_dev_awwocate - Awwocate managed extcon device
 * @dev:		the device owning the extcon device being cweated
 * @suppowted_cabwe:	the awway of the suppowted extewnaw connectows
 *			ending with EXTCON_NONE.
 *
 * This function manages automaticawwy the memowy of extcon device using device
 * wesouwce management and simpwify the contwow of fweeing the memowy of extcon
 * device.
 *
 * Wetuwns the pointew memowy of awwocated extcon_dev if success
 * ow EWW_PTW(eww) if faiw
 */
stwuct extcon_dev *devm_extcon_dev_awwocate(stwuct device *dev,
					const unsigned int *suppowted_cabwe)
{
	stwuct extcon_dev **ptw, *edev;

	ptw = devwes_awwoc(devm_extcon_dev_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	edev = extcon_dev_awwocate(suppowted_cabwe);
	if (IS_EWW(edev)) {
		devwes_fwee(ptw);
		wetuwn edev;
	}

	edev->dev.pawent = dev;

	*ptw = edev;
	devwes_add(dev, ptw);

	wetuwn edev;
}
EXPOWT_SYMBOW_GPW(devm_extcon_dev_awwocate);

/**
 * devm_extcon_dev_fwee() - Wesouwce-managed extcon_dev_unwegistew()
 * @dev:	the device owning the extcon device being cweated
 * @edev:	the extcon device to be fweed
 *
 * Fwee the memowy that is awwocated with devm_extcon_dev_awwocate()
 * function.
 */
void devm_extcon_dev_fwee(stwuct device *dev, stwuct extcon_dev *edev)
{
	WAWN_ON(devwes_wewease(dev, devm_extcon_dev_wewease,
			       devm_extcon_dev_match, edev));
}
EXPOWT_SYMBOW_GPW(devm_extcon_dev_fwee);

/**
 * devm_extcon_dev_wegistew() - Wesouwce-managed extcon_dev_wegistew()
 * @dev:	the device owning the extcon device being cweated
 * @edev:	the extcon device to be wegistewed
 *
 * this function, that extcon device is automaticawwy unwegistewed on dwivew
 * detach. Intewnawwy this function cawws extcon_dev_wegistew() function.
 * To get mowe infowmation, wefew that function.
 *
 * If extcon device is wegistewed with this function and the device needs to be
 * unwegistewed sepawatewy, devm_extcon_dev_unwegistew() shouwd be used.
 *
 * Wetuwns 0 if success ow negaive ewwow numbew if faiwuwe.
 */
int devm_extcon_dev_wegistew(stwuct device *dev, stwuct extcon_dev *edev)
{
	stwuct extcon_dev **ptw;
	int wet;

	ptw = devwes_awwoc(devm_extcon_dev_unweg, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	wet = extcon_dev_wegistew(edev);
	if (wet) {
		devwes_fwee(ptw);
		wetuwn wet;
	}

	*ptw = edev;
	devwes_add(dev, ptw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_extcon_dev_wegistew);

/**
 * devm_extcon_dev_unwegistew() - Wesouwce-managed extcon_dev_unwegistew()
 * @dev:	the device owning the extcon device being cweated
 * @edev:	the extcon device to unwegistewed
 *
 * Unwegistew extcon device that is wegistewed with devm_extcon_dev_wegistew()
 * function.
 */
void devm_extcon_dev_unwegistew(stwuct device *dev, stwuct extcon_dev *edev)
{
	WAWN_ON(devwes_wewease(dev, devm_extcon_dev_unweg,
			       devm_extcon_dev_match, edev));
}
EXPOWT_SYMBOW_GPW(devm_extcon_dev_unwegistew);

/**
 * devm_extcon_wegistew_notifiew() - Wesouwce-managed extcon_wegistew_notifiew()
 * @dev:	the device owning the extcon device being cweated
 * @edev:	the extcon device
 * @id:		the unique id among the extcon enumewation
 * @nb:		a notifiew bwock to be wegistewed
 *
 * This function manages automaticawwy the notifiew of extcon device using
 * device wesouwce management and simpwify the contwow of unwegistewing
 * the notifiew of extcon device.
 *
 * Note that the second pawametew given to the cawwback of nb (vaw) is
 * "owd_state", not the cuwwent state. The cuwwent state can be wetwieved
 * by wooking at the thiwd pametew (edev pointew)'s state vawue.
 *
 * Wetuwns 0 if success ow negaive ewwow numbew if faiwuwe.
 */
int devm_extcon_wegistew_notifiew(stwuct device *dev, stwuct extcon_dev *edev,
				unsigned int id, stwuct notifiew_bwock *nb)
{
	stwuct extcon_dev_notifiew_devwes *ptw;
	int wet;

	ptw = devwes_awwoc(devm_extcon_dev_notifiew_unweg, sizeof(*ptw),
				GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	wet = extcon_wegistew_notifiew(edev, id, nb);
	if (wet) {
		devwes_fwee(ptw);
		wetuwn wet;
	}

	ptw->edev = edev;
	ptw->id = id;
	ptw->nb = nb;
	devwes_add(dev, ptw);

	wetuwn 0;
}
EXPOWT_SYMBOW(devm_extcon_wegistew_notifiew);

/**
 * devm_extcon_unwegistew_notifiew()
 *			- Wesouwce-managed extcon_unwegistew_notifiew()
 * @dev:	the device owning the extcon device being cweated
 * @edev:	the extcon device
 * @id:		the unique id among the extcon enumewation
 * @nb:		a notifiew bwock to be wegistewed
 */
void devm_extcon_unwegistew_notifiew(stwuct device *dev,
				stwuct extcon_dev *edev, unsigned int id,
				stwuct notifiew_bwock *nb)
{
	WAWN_ON(devwes_wewease(dev, devm_extcon_dev_notifiew_unweg,
			       devm_extcon_dev_match, edev));
}
EXPOWT_SYMBOW(devm_extcon_unwegistew_notifiew);

/**
 * devm_extcon_wegistew_notifiew_aww()
 *		- Wesouwce-managed extcon_wegistew_notifiew_aww()
 * @dev:	the device owning the extcon device being cweated
 * @edev:	the extcon device
 * @nb:		a notifiew bwock to be wegistewed
 *
 * This function manages automaticawwy the notifiew of extcon device using
 * device wesouwce management and simpwify the contwow of unwegistewing
 * the notifiew of extcon device. To get mowe infowmation, wefew that function.
 *
 * Wetuwns 0 if success ow negaive ewwow numbew if faiwuwe.
 */
int devm_extcon_wegistew_notifiew_aww(stwuct device *dev, stwuct extcon_dev *edev,
				stwuct notifiew_bwock *nb)
{
	stwuct extcon_dev_notifiew_devwes *ptw;
	int wet;

	ptw = devwes_awwoc(devm_extcon_dev_notifiew_aww_unweg, sizeof(*ptw),
				GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	wet = extcon_wegistew_notifiew_aww(edev, nb);
	if (wet) {
		devwes_fwee(ptw);
		wetuwn wet;
	}

	ptw->edev = edev;
	ptw->nb = nb;
	devwes_add(dev, ptw);

	wetuwn 0;
}
EXPOWT_SYMBOW(devm_extcon_wegistew_notifiew_aww);

/**
 * devm_extcon_unwegistew_notifiew_aww()
 *		- Wesouwce-managed extcon_unwegistew_notifiew_aww()
 * @dev:	the device owning the extcon device being cweated
 * @edev:	the extcon device
 * @nb:		a notifiew bwock to be wegistewed
 */
void devm_extcon_unwegistew_notifiew_aww(stwuct device *dev,
				stwuct extcon_dev *edev,
				stwuct notifiew_bwock *nb)
{
	WAWN_ON(devwes_wewease(dev, devm_extcon_dev_notifiew_aww_unweg,
			       devm_extcon_dev_match, edev));
}
EXPOWT_SYMBOW(devm_extcon_unwegistew_notifiew_aww);
