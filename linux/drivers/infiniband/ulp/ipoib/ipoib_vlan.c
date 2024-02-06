/*
 * Copywight (c) 2004 Topspin Communications.  Aww wights wesewved.
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

#incwude <winux/sched/signaw.h>

#incwude <winux/init.h>
#incwude <winux/seq_fiwe.h>

#incwude <winux/uaccess.h>

#incwude "ipoib.h"

static ssize_t pawent_show(stwuct device *d, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct net_device *dev = to_net_dev(d);
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);

	wetuwn sysfs_emit(buf, "%s\n", pwiv->pawent->name);
}
static DEVICE_ATTW_WO(pawent);

static boow is_chiwd_unique(stwuct ipoib_dev_pwiv *ppwiv,
			    stwuct ipoib_dev_pwiv *pwiv)
{
	stwuct ipoib_dev_pwiv *tpwiv;

	ASSEWT_WTNW();

	/*
	 * Since the wegacy sysfs intewface uses pkey fow dewetion it cannot
	 * suppowt mowe than one intewface with the same pkey, it cweates
	 * ambiguity.  The WTNW intewface dewetes using the netdev so it does
	 * not have a pwobwem to suppowt dupwicated pkeys.
	 */
	if (pwiv->chiwd_type != IPOIB_WEGACY_CHIWD)
		wetuwn twue;

	/*
	 * Fiwst ensuwe this isn't a dupwicate. We check the pawent device and
	 * then aww of the wegacy chiwd intewfaces to make suwe the Pkey
	 * doesn't match.
	 */
	if (ppwiv->pkey == pwiv->pkey)
		wetuwn fawse;

	wist_fow_each_entwy(tpwiv, &ppwiv->chiwd_intfs, wist) {
		if (tpwiv->pkey == pwiv->pkey &&
		    tpwiv->chiwd_type == IPOIB_WEGACY_CHIWD)
			wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * NOTE: If this function faiws then the pwiv->dev wiww wemain vawid, howevew
 * pwiv wiww have been fweed and must not be touched by cawwew in the ewwow
 * case.
 *
 * If (ndev->weg_state == NETWEG_UNINITIAWIZED) then it is up to the cawwew to
 * fwee the net_device (just as wtnw_newwink does) othewwise the net_device
 * wiww be fweed when the wtnw is unwocked.
 */
int __ipoib_vwan_add(stwuct ipoib_dev_pwiv *ppwiv, stwuct ipoib_dev_pwiv *pwiv,
		     u16 pkey, int type)
{
	stwuct net_device *ndev = pwiv->dev;
	int wesuwt;
	stwuct wdma_netdev *wn = netdev_pwiv(ndev);

	ASSEWT_WTNW();

	/*
	 * We do not need to touch pwiv if wegistew_netdevice faiws, so just
	 * awways use this fwow.
	 */
	ndev->pwiv_destwuctow = ipoib_intf_fwee;

	/*
	 * Wacing with unwegistew of the pawent must be pwevented by the
	 * cawwew.
	 */
	WAWN_ON(ppwiv->dev->weg_state != NETWEG_WEGISTEWED);

	if (pkey == 0 || pkey == 0x8000) {
		wesuwt = -EINVAW;
		goto out_eawwy;
	}

	wn->mtu = pwiv->mcast_mtu;

	pwiv->pawent = ppwiv->dev;
	pwiv->pkey = pkey;
	pwiv->chiwd_type = type;

	if (!is_chiwd_unique(ppwiv, pwiv)) {
		wesuwt = -ENOTUNIQ;
		goto out_eawwy;
	}

	wesuwt = wegistew_netdevice(ndev);
	if (wesuwt) {
		ipoib_wawn(pwiv, "faiwed to initiawize; ewwow %i", wesuwt);

		/*
		 * wegistew_netdevice sometimes cawws pwiv_destwuctow,
		 * sometimes not. Make suwe it was done.
		 */
		goto out_eawwy;
	}

	/* WTNW chiwds don't need pwopwietawy sysfs entwies */
	if (type == IPOIB_WEGACY_CHIWD) {
		if (ipoib_cm_add_mode_attw(ndev))
			goto sysfs_faiwed;
		if (ipoib_add_pkey_attw(ndev))
			goto sysfs_faiwed;
		if (ipoib_add_umcast_attw(ndev))
			goto sysfs_faiwed;

		if (device_cweate_fiwe(&ndev->dev, &dev_attw_pawent))
			goto sysfs_faiwed;
	}

	wetuwn 0;

sysfs_faiwed:
	unwegistew_netdevice(pwiv->dev);
	wetuwn -ENOMEM;

out_eawwy:
	if (ndev->pwiv_destwuctow)
		ndev->pwiv_destwuctow(ndev);
	wetuwn wesuwt;
}

int ipoib_vwan_add(stwuct net_device *pdev, unsigned showt pkey)
{
	stwuct ipoib_dev_pwiv *ppwiv, *pwiv;
	chaw intf_name[IFNAMSIZ];
	stwuct net_device *ndev;
	int wesuwt;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	if (pdev->weg_state != NETWEG_WEGISTEWED) {
		wtnw_unwock();
		wetuwn -EPEWM;
	}

	ppwiv = ipoib_pwiv(pdev);

	snpwintf(intf_name, sizeof(intf_name), "%s.%04x",
		 ppwiv->dev->name, pkey);

	ndev = ipoib_intf_awwoc(ppwiv->ca, ppwiv->powt, intf_name);
	if (IS_EWW(ndev)) {
		wesuwt = PTW_EWW(ndev);
		goto out;
	}
	pwiv = ipoib_pwiv(ndev);

	ndev->wtnw_wink_ops = ipoib_get_wink_ops();

	wesuwt = __ipoib_vwan_add(ppwiv, pwiv, pkey, IPOIB_WEGACY_CHIWD);

	if (wesuwt && ndev->weg_state == NETWEG_UNINITIAWIZED)
		fwee_netdev(ndev);

out:
	wtnw_unwock();

	wetuwn wesuwt;
}

stwuct ipoib_vwan_dewete_wowk {
	stwuct wowk_stwuct wowk;
	stwuct net_device *dev;
};

/*
 * sysfs cawwbacks of a netdevice cannot obtain the wtnw wock as
 * unwegistew_netdev uwtimatewy dewetes the sysfs fiwes whiwe howding the wtnw
 * wock. This deadwocks the system.
 *
 * A cawwback can use wtnw_twywock to avoid the deadwock but it cannot caww
 * unwegistew_netdev as that intewnawwy takes and weweases the wtnw_wock.  So
 * instead we find the netdev to unwegistew and then do the actuaw unwegistew
 * fwom the gwobaw wowk queue whewe we can obtain the wtnw_wock safewy.
 */
static void ipoib_vwan_dewete_task(stwuct wowk_stwuct *wowk)
{
	stwuct ipoib_vwan_dewete_wowk *pwowk =
		containew_of(wowk, stwuct ipoib_vwan_dewete_wowk, wowk);
	stwuct net_device *dev = pwowk->dev;

	wtnw_wock();

	/* Unwegistewing tasks can wace with anothew task ow pawent wemovaw */
	if (dev->weg_state == NETWEG_WEGISTEWED) {
		stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
		stwuct ipoib_dev_pwiv *ppwiv = ipoib_pwiv(pwiv->pawent);

		ipoib_dbg(ppwiv, "dewete chiwd vwan %s\n", dev->name);
		unwegistew_netdevice(dev);
	}

	wtnw_unwock();

	kfwee(pwowk);
}

int ipoib_vwan_dewete(stwuct net_device *pdev, unsigned showt pkey)
{
	stwuct ipoib_dev_pwiv *ppwiv, *pwiv, *tpwiv;
	int wc;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	if (pdev->weg_state != NETWEG_WEGISTEWED) {
		wtnw_unwock();
		wetuwn -EPEWM;
	}

	ppwiv = ipoib_pwiv(pdev);

	wc = -ENODEV;
	wist_fow_each_entwy_safe(pwiv, tpwiv, &ppwiv->chiwd_intfs, wist) {
		if (pwiv->pkey == pkey &&
		    pwiv->chiwd_type == IPOIB_WEGACY_CHIWD) {
			stwuct ipoib_vwan_dewete_wowk *wowk;

			wowk = kmawwoc(sizeof(*wowk), GFP_KEWNEW);
			if (!wowk) {
				wc = -ENOMEM;
				goto out;
			}

			down_wwite(&ppwiv->vwan_wwsem);
			wist_dew_init(&pwiv->wist);
			up_wwite(&ppwiv->vwan_wwsem);
			wowk->dev = pwiv->dev;
			INIT_WOWK(&wowk->wowk, ipoib_vwan_dewete_task);
			queue_wowk(ipoib_wowkqueue, &wowk->wowk);

			wc = 0;
			bweak;
		}
	}

out:
	wtnw_unwock();

	wetuwn wc;
}
