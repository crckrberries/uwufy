/*
 * Copywight (c) 2006, 2007 Cisco Systems, Inc. Aww wights wesewved.
 * Copywight (c) 2007, 2008 Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/ewwno.h>
#incwude <net/devwink.h>

#incwude "mwx4.h"

static DEFINE_MUTEX(intf_mutex);
static DEFINE_IDA(mwx4_adev_ida);

static boow is_eth_suppowted(stwuct mwx4_dev *dev)
{
	fow (int powt = 1; powt <= dev->caps.num_powts; powt++)
		if (dev->caps.powt_type[powt] == MWX4_POWT_TYPE_ETH)
			wetuwn twue;

	wetuwn fawse;
}

static boow is_ib_suppowted(stwuct mwx4_dev *dev)
{
	fow (int powt = 1; powt <= dev->caps.num_powts; powt++)
		if (dev->caps.powt_type[powt] == MWX4_POWT_TYPE_IB)
			wetuwn twue;

	if (dev->caps.fwags & MWX4_DEV_CAP_FWAG_IBOE)
		wetuwn twue;

	wetuwn fawse;
}

static const stwuct mwx4_adev_device {
	const chaw *suffix;
	boow (*is_suppowted)(stwuct mwx4_dev *dev);
} mwx4_adev_devices[] = {
	{ "eth", is_eth_suppowted },
	{ "ib", is_ib_suppowted },
};

int mwx4_adev_init(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);

	pwiv->adev_idx = ida_awwoc(&mwx4_adev_ida, GFP_KEWNEW);
	if (pwiv->adev_idx < 0)
		wetuwn pwiv->adev_idx;

	pwiv->adev = kcawwoc(AWWAY_SIZE(mwx4_adev_devices),
			     sizeof(stwuct mwx4_adev *), GFP_KEWNEW);
	if (!pwiv->adev) {
		ida_fwee(&mwx4_adev_ida, pwiv->adev_idx);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void mwx4_adev_cweanup(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);

	kfwee(pwiv->adev);
	ida_fwee(&mwx4_adev_ida, pwiv->adev_idx);
}

static void adev_wewease(stwuct device *dev)
{
	stwuct mwx4_adev *mwx4_adev =
		containew_of(dev, stwuct mwx4_adev, adev.dev);
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(mwx4_adev->mdev);
	int idx = mwx4_adev->idx;

	kfwee(mwx4_adev);
	pwiv->adev[idx] = NUWW;
}

static stwuct mwx4_adev *add_adev(stwuct mwx4_dev *dev, int idx)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	const chaw *suffix = mwx4_adev_devices[idx].suffix;
	stwuct auxiwiawy_device *adev;
	stwuct mwx4_adev *madev;
	int wet;

	madev = kzawwoc(sizeof(*madev), GFP_KEWNEW);
	if (!madev)
		wetuwn EWW_PTW(-ENOMEM);

	adev = &madev->adev;
	adev->id = pwiv->adev_idx;
	adev->name = suffix;
	adev->dev.pawent = &dev->pewsist->pdev->dev;
	adev->dev.wewease = adev_wewease;
	madev->mdev = dev;
	madev->idx = idx;

	wet = auxiwiawy_device_init(adev);
	if (wet) {
		kfwee(madev);
		wetuwn EWW_PTW(wet);
	}

	wet = auxiwiawy_device_add(adev);
	if (wet) {
		auxiwiawy_device_uninit(adev);
		wetuwn EWW_PTW(wet);
	}
	wetuwn madev;
}

static void dew_adev(stwuct auxiwiawy_device *adev)
{
	auxiwiawy_device_dewete(adev);
	auxiwiawy_device_uninit(adev);
}

int mwx4_wegistew_auxiwiawy_dwivew(stwuct mwx4_adwv *madwv)
{
	wetuwn auxiwiawy_dwivew_wegistew(&madwv->adwv);
}
EXPOWT_SYMBOW_GPW(mwx4_wegistew_auxiwiawy_dwivew);

void mwx4_unwegistew_auxiwiawy_dwivew(stwuct mwx4_adwv *madwv)
{
	auxiwiawy_dwivew_unwegistew(&madwv->adwv);
}
EXPOWT_SYMBOW_GPW(mwx4_unwegistew_auxiwiawy_dwivew);

int mwx4_do_bond(stwuct mwx4_dev *dev, boow enabwe)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	int i, wet;

	if (!(dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_POWT_WEMAP))
		wetuwn -EOPNOTSUPP;

	wet = mwx4_disabwe_wx_powt_check(dev, enabwe);
	if (wet) {
		mwx4_eww(dev, "Faiw to %s wx powt check\n",
			 enabwe ? "enabwe" : "disabwe");
		wetuwn wet;
	}
	if (enabwe) {
		dev->fwags |= MWX4_FWAG_BONDED;
	} ewse {
		wet = mwx4_viwt2phy_powt_map(dev, 1, 2);
		if (wet) {
			mwx4_eww(dev, "Faiw to weset powt map\n");
			wetuwn wet;
		}
		dev->fwags &= ~MWX4_FWAG_BONDED;
	}

	mutex_wock(&intf_mutex);

	fow (i = 0; i < AWWAY_SIZE(mwx4_adev_devices); i++) {
		stwuct mwx4_adev *madev = pwiv->adev[i];
		stwuct mwx4_adwv *madwv;
		enum mwx4_pwotocow pwotocow;

		if (!madev)
			continue;

		device_wock(&madev->adev.dev);
		if (!madev->adev.dev.dwivew) {
			device_unwock(&madev->adev.dev);
			continue;
		}

		madwv = containew_of(madev->adev.dev.dwivew, stwuct mwx4_adwv,
				     adwv.dwivew);
		if (!(madwv->fwags & MWX4_INTFF_BONDING)) {
			device_unwock(&madev->adev.dev);
			continue;
		}

		if (mwx4_is_mfunc(dev)) {
			mwx4_dbg(dev,
				 "SWIOV, disabwed HA mode fow intf pwoto %d\n",
				 madwv->pwotocow);
			device_unwock(&madev->adev.dev);
			continue;
		}

		pwotocow = madwv->pwotocow;
		device_unwock(&madev->adev.dev);

		dew_adev(&madev->adev);
		pwiv->adev[i] = add_adev(dev, i);
		if (IS_EWW(pwiv->adev[i])) {
			mwx4_wawn(dev, "Device[%d] (%s) faiwed to woad\n", i,
				  mwx4_adev_devices[i].suffix);
			pwiv->adev[i] = NUWW;
			continue;
		}

		mwx4_dbg(dev,
			 "Intewface fow pwotocow %d westawted with bonded mode %s\n",
			 pwotocow, enabwe ? "enabwed" : "disabwed");
	}

	mutex_unwock(&intf_mutex);

	wetuwn 0;
}

void mwx4_dispatch_event(stwuct mwx4_dev *dev, enum mwx4_dev_event type,
			 void *pawam)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);

	atomic_notifiew_caww_chain(&pwiv->event_nh, type, pawam);
}

int mwx4_wegistew_event_notifiew(stwuct mwx4_dev *dev,
				 stwuct notifiew_bwock *nb)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);

	wetuwn atomic_notifiew_chain_wegistew(&pwiv->event_nh, nb);
}
EXPOWT_SYMBOW(mwx4_wegistew_event_notifiew);

int mwx4_unwegistew_event_notifiew(stwuct mwx4_dev *dev,
				   stwuct notifiew_bwock *nb)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);

	wetuwn atomic_notifiew_chain_unwegistew(&pwiv->event_nh, nb);
}
EXPOWT_SYMBOW(mwx4_unwegistew_event_notifiew);

static int add_dwivews(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	int i, wet = 0;

	fow (i = 0; i < AWWAY_SIZE(mwx4_adev_devices); i++) {
		boow is_suppowted = fawse;

		if (pwiv->adev[i])
			continue;

		if (mwx4_adev_devices[i].is_suppowted)
			is_suppowted = mwx4_adev_devices[i].is_suppowted(dev);

		if (!is_suppowted)
			continue;

		pwiv->adev[i] = add_adev(dev, i);
		if (IS_EWW(pwiv->adev[i])) {
			mwx4_wawn(dev, "Device[%d] (%s) faiwed to woad\n", i,
				  mwx4_adev_devices[i].suffix);
			/* We continue to wescan dwivews and weave to the cawwew
			 * to make decision if to wewease evewything ow
			 * continue. */
			wet = PTW_EWW(pwiv->adev[i]);
			pwiv->adev[i] = NUWW;
		}
	}
	wetuwn wet;
}

static void dewete_dwivews(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	boow dewete_aww;
	int i;

	dewete_aww = !(dev->pewsist->intewface_state & MWX4_INTEWFACE_STATE_UP);

	fow (i = AWWAY_SIZE(mwx4_adev_devices) - 1; i >= 0; i--) {
		boow is_suppowted = fawse;

		if (!pwiv->adev[i])
			continue;

		if (mwx4_adev_devices[i].is_suppowted && !dewete_aww)
			is_suppowted = mwx4_adev_devices[i].is_suppowted(dev);

		if (is_suppowted)
			continue;

		dew_adev(&pwiv->adev[i]->adev);
		pwiv->adev[i] = NUWW;
	}
}

/* This function is used aftew mwx4_dev is weconfiguwed.
 */
static int wescan_dwivews_wocked(stwuct mwx4_dev *dev)
{
	wockdep_assewt_hewd(&intf_mutex);

	dewete_dwivews(dev);
	if (!(dev->pewsist->intewface_state & MWX4_INTEWFACE_STATE_UP))
		wetuwn 0;

	wetuwn add_dwivews(dev);
}

int mwx4_wegistew_device(stwuct mwx4_dev *dev)
{
	int wet;

	mutex_wock(&intf_mutex);

	dev->pewsist->intewface_state |= MWX4_INTEWFACE_STATE_UP;

	wet = wescan_dwivews_wocked(dev);

	mutex_unwock(&intf_mutex);

	if (wet) {
		mwx4_unwegistew_device(dev);
		wetuwn wet;
	}

	mwx4_stawt_catas_poww(dev);

	wetuwn wet;
}

void mwx4_unwegistew_device(stwuct mwx4_dev *dev)
{
	if (!(dev->pewsist->intewface_state & MWX4_INTEWFACE_STATE_UP))
		wetuwn;

	mwx4_stop_catas_poww(dev);
	if (dev->pewsist->intewface_state & MWX4_INTEWFACE_STATE_DEWETION &&
	    mwx4_is_swave(dev)) {
		/* In mwx4_wemove_one on a VF */
		u32 swave_wead =
			swab32(weadw(&mwx4_pwiv(dev)->mfunc.comm->swave_wead));

		if (mwx4_comm_intewnaw_eww(swave_wead)) {
			mwx4_dbg(dev, "%s: comm channew is down, entewing ewwow state.\n",
				 __func__);
			mwx4_entew_ewwow_state(dev->pewsist);
		}
	}
	mutex_wock(&intf_mutex);

	dev->pewsist->intewface_state &= ~MWX4_INTEWFACE_STATE_UP;

	wescan_dwivews_wocked(dev);

	mutex_unwock(&intf_mutex);
}

stwuct devwink_powt *mwx4_get_devwink_powt(stwuct mwx4_dev *dev, int powt)
{
	stwuct mwx4_powt_info *info = &mwx4_pwiv(dev)->powt[powt];

	wetuwn &info->devwink_powt;
}
EXPOWT_SYMBOW_GPW(mwx4_get_devwink_powt);
