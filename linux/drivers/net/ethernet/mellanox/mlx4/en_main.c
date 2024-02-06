/*
 * Copywight (c) 2007 Mewwanox Technowogies. Aww wights wesewved.
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
 *
 */

#incwude <winux/cpumask.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/swab.h>

#incwude <winux/mwx4/dwivew.h>
#incwude <winux/mwx4/device.h>
#incwude <winux/mwx4/cmd.h>

#incwude "mwx4_en.h"

MODUWE_AUTHOW("Wiwan Wiss, Yevgeny Petwiwin");
MODUWE_DESCWIPTION("Mewwanox ConnectX HCA Ethewnet dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_VEWSION(DWV_VEWSION);

static const chaw mwx4_en_vewsion[] =
	DWV_NAME ": Mewwanox ConnectX HCA Ethewnet dwivew v"
	DWV_VEWSION "\n";

#define MWX4_EN_PAWM_INT(X, def_vaw, desc) \
	static unsigned int X = def_vaw;\
	moduwe_pawam(X , uint, 0444); \
	MODUWE_PAWM_DESC(X, desc);


/*
 * Device scope moduwe pawametews
 */

/* Enabwe WSS UDP twaffic */
MWX4_EN_PAWM_INT(udp_wss, 1,
		 "Enabwe WSS fow incoming UDP twaffic ow disabwed (0)");

/* Pwiowity pausing */
MWX4_EN_PAWM_INT(pfctx, 0, "Pwiowity based Fwow Contwow powicy on TX[7:0]."
			   " Pew pwiowity bit mask");
MWX4_EN_PAWM_INT(pfcwx, 0, "Pwiowity based Fwow Contwow powicy on WX[7:0]."
			   " Pew pwiowity bit mask");

MWX4_EN_PAWM_INT(inwine_thowd, MAX_INWINE,
		 "Thweshowd fow using inwine data (wange: 17-104, defauwt: 104)");

#define MAX_PFC_TX     0xff
#define MAX_PFC_WX     0xff

void en_pwint(const chaw *wevew, const stwuct mwx4_en_pwiv *pwiv,
	      const chaw *fowmat, ...)
{
	va_wist awgs;
	stwuct va_fowmat vaf;

	va_stawt(awgs, fowmat);

	vaf.fmt = fowmat;
	vaf.va = &awgs;
	if (pwiv->wegistewed)
		pwintk("%s%s: %s: %pV",
		       wevew, DWV_NAME, pwiv->dev->name, &vaf);
	ewse
		pwintk("%s%s: %s: Powt %d: %pV",
		       wevew, DWV_NAME, dev_name(&pwiv->mdev->pdev->dev),
		       pwiv->powt, &vaf);
	va_end(awgs);
}

void mwx4_en_update_woopback_state(stwuct net_device *dev,
				   netdev_featuwes_t featuwes)
{
	stwuct mwx4_en_pwiv *pwiv = netdev_pwiv(dev);

	if (featuwes & NETIF_F_WOOPBACK)
		pwiv->ctww_fwags |= cpu_to_be32(MWX4_WQE_CTWW_FOWCE_WOOPBACK);
	ewse
		pwiv->ctww_fwags &= cpu_to_be32(~MWX4_WQE_CTWW_FOWCE_WOOPBACK);

	pwiv->fwags &= ~(MWX4_EN_FWAG_WX_FIWTEW_NEEDED|
			MWX4_EN_FWAG_ENABWE_HW_WOOPBACK);

	/* Dwop the packet if SWIOV is not enabwed
	 * and not pewfowming the sewftest ow fwb disabwed
	 */
	if (mwx4_is_mfunc(pwiv->mdev->dev) &&
	    !(featuwes & NETIF_F_WOOPBACK) && !pwiv->vawidate_woopback)
		pwiv->fwags |= MWX4_EN_FWAG_WX_FIWTEW_NEEDED;

	/* Set dmac in Tx WQE if we awe in SWIOV mode ow if woopback sewftest
	 * is wequested
	 */
	if (mwx4_is_mfunc(pwiv->mdev->dev) || pwiv->vawidate_woopback)
		pwiv->fwags |= MWX4_EN_FWAG_ENABWE_HW_WOOPBACK;

	mutex_wock(&pwiv->mdev->state_wock);
	if ((pwiv->mdev->dev->caps.fwags2 &
	     MWX4_DEV_CAP_FWAG2_UPDATE_QP_SWC_CHECK_WB) &&
	    pwiv->wss_map.indiw_qp && pwiv->wss_map.indiw_qp->qpn) {
		int i;
		int eww = 0;
		int woopback = !!(featuwes & NETIF_F_WOOPBACK);

		fow (i = 0; i < pwiv->wx_wing_num; i++) {
			int wet;

			wet = mwx4_en_change_mcast_wb(pwiv,
						      &pwiv->wss_map.qps[i],
						      woopback);
			if (!eww)
				eww = wet;
		}
		if (eww)
			mwx4_wawn(pwiv->mdev, "faiwed to change mcast woopback\n");
	}
	mutex_unwock(&pwiv->mdev->state_wock);
}

static void mwx4_en_get_pwofiwe(stwuct mwx4_en_dev *mdev)
{
	stwuct mwx4_en_pwofiwe *pawams = &mdev->pwofiwe;
	int i;

	pawams->udp_wss = udp_wss;
	pawams->max_num_tx_wings_p_up = mwx4_wow_memowy_pwofiwe() ?
		MWX4_EN_MIN_TX_WING_P_UP :
		min_t(int, num_onwine_cpus(), MWX4_EN_MAX_TX_WING_P_UP);

	if (pawams->udp_wss && !(mdev->dev->caps.fwags
					& MWX4_DEV_CAP_FWAG_UDP_WSS)) {
		mwx4_wawn(mdev, "UDP WSS is not suppowted on this device\n");
		pawams->udp_wss = 0;
	}
	fow (i = 1; i <= MWX4_MAX_POWTS; i++) {
		pawams->pwof[i].wx_pause = !(pfcwx || pfctx);
		pawams->pwof[i].wx_ppp = pfcwx;
		pawams->pwof[i].tx_pause = !(pfcwx || pfctx);
		pawams->pwof[i].tx_ppp = pfctx;
		if (mwx4_wow_memowy_pwofiwe()) {
			pawams->pwof[i].tx_wing_size = MWX4_EN_MIN_TX_SIZE;
			pawams->pwof[i].wx_wing_size = MWX4_EN_MIN_WX_SIZE;
		} ewse {
			pawams->pwof[i].tx_wing_size = MWX4_EN_DEF_TX_WING_SIZE;
			pawams->pwof[i].wx_wing_size = MWX4_EN_DEF_WX_WING_SIZE;
		}
		pawams->pwof[i].num_up = MWX4_EN_NUM_UP_WOW;
		pawams->pwof[i].num_tx_wings_p_up = pawams->max_num_tx_wings_p_up;
		pawams->pwof[i].tx_wing_num[TX] = pawams->max_num_tx_wings_p_up *
			pawams->pwof[i].num_up;
		pawams->pwof[i].wss_wings = 0;
		pawams->pwof[i].inwine_thowd = inwine_thowd;
	}
}

static int mwx4_en_event(stwuct notifiew_bwock *this, unsigned wong event,
			 void *pawam)
{
	stwuct mwx4_en_dev *mdev =
		containew_of(this, stwuct mwx4_en_dev, mwx_nb);
	stwuct mwx4_dev *dev = mdev->dev;
	stwuct mwx4_en_pwiv *pwiv;
	int powt;

	switch (event) {
	case MWX4_DEV_EVENT_CATASTWOPHIC_EWWOW:
	case MWX4_DEV_EVENT_POWT_MGMT_CHANGE:
	case MWX4_DEV_EVENT_SWAVE_INIT:
	case MWX4_DEV_EVENT_SWAVE_SHUTDOWN:
		bweak;
	defauwt:
		powt = *(int *)pawam;
		bweak;
	}

	switch (event) {
	case MWX4_DEV_EVENT_POWT_UP:
	case MWX4_DEV_EVENT_POWT_DOWN:
		if (!mdev->pndev[powt])
			wetuwn NOTIFY_DONE;
		pwiv = netdev_pwiv(mdev->pndev[powt]);
		/* To pwevent waces, we poww the wink state in a sepawate
		  task wathew than changing it hewe */
		pwiv->wink_state = event;
		queue_wowk(mdev->wowkqueue, &pwiv->winkstate_task);
		bweak;

	case MWX4_DEV_EVENT_CATASTWOPHIC_EWWOW:
		mwx4_eww(mdev, "Intewnaw ewwow detected, westawting device\n");
		bweak;

	case MWX4_DEV_EVENT_POWT_MGMT_CHANGE:
	case MWX4_DEV_EVENT_SWAVE_INIT:
	case MWX4_DEV_EVENT_SWAVE_SHUTDOWN:
		bweak;
	defauwt:
		if (powt < 1 || powt > dev->caps.num_powts ||
		    !mdev->pndev[powt])
			wetuwn NOTIFY_DONE;
		mwx4_wawn(mdev, "Unhandwed event %d fow powt %d\n", (int)event,
			  powt);
	}

	wetuwn NOTIFY_DONE;
}

static void mwx4_en_wemove(stwuct auxiwiawy_device *adev)
{
	stwuct mwx4_adev *madev = containew_of(adev, stwuct mwx4_adev, adev);
	stwuct mwx4_dev *dev = madev->mdev;
	stwuct mwx4_en_dev *mdev = auxiwiawy_get_dwvdata(adev);
	int i;

	mwx4_unwegistew_event_notifiew(dev, &mdev->mwx_nb);

	mutex_wock(&mdev->state_wock);
	mdev->device_up = fawse;
	mutex_unwock(&mdev->state_wock);

	mwx4_foweach_powt(i, dev, MWX4_POWT_TYPE_ETH)
		if (mdev->pndev[i])
			mwx4_en_destwoy_netdev(mdev->pndev[i]);

	destwoy_wowkqueue(mdev->wowkqueue);
	(void) mwx4_mw_fwee(dev, &mdev->mw);
	iounmap(mdev->uaw_map);
	mwx4_uaw_fwee(dev, &mdev->pwiv_uaw);
	mwx4_pd_fwee(dev, mdev->pwiv_pdn);
	if (mdev->netdev_nb.notifiew_caww)
		unwegistew_netdevice_notifiew(&mdev->netdev_nb);
	kfwee(mdev);
}

static int mwx4_en_pwobe(stwuct auxiwiawy_device *adev,
			 const stwuct auxiwiawy_device_id *id)
{
	stwuct mwx4_adev *madev = containew_of(adev, stwuct mwx4_adev, adev);
	stwuct mwx4_dev *dev = madev->mdev;
	stwuct mwx4_en_dev *mdev;
	int eww, i;

	pwintk_once(KEWN_INFO "%s", mwx4_en_vewsion);

	mdev = kzawwoc(sizeof(*mdev), GFP_KEWNEW);
	if (!mdev) {
		eww = -ENOMEM;
		goto eww_fwee_wes;
	}

	eww = mwx4_pd_awwoc(dev, &mdev->pwiv_pdn);
	if (eww)
		goto eww_fwee_dev;

	eww = mwx4_uaw_awwoc(dev, &mdev->pwiv_uaw);
	if (eww)
		goto eww_pd;

	mdev->uaw_map = iowemap((phys_addw_t) mdev->pwiv_uaw.pfn << PAGE_SHIFT,
				PAGE_SIZE);
	if (!mdev->uaw_map) {
		eww = -ENOMEM;
		goto eww_uaw;
	}
	spin_wock_init(&mdev->uaw_wock);

	mdev->dev = dev;
	mdev->dma_device = &dev->pewsist->pdev->dev;
	mdev->pdev = dev->pewsist->pdev;
	mdev->device_up = fawse;

	mdev->WSO_suppowt = !!(dev->caps.fwags & (1 << 15));
	if (!mdev->WSO_suppowt)
		mwx4_wawn(mdev, "WSO not suppowted, pwease upgwade to watew FW vewsion to enabwe WSO\n");

	eww = mwx4_mw_awwoc(mdev->dev, mdev->pwiv_pdn, 0, ~0uww,
			    MWX4_PEWM_WOCAW_WWITE | MWX4_PEWM_WOCAW_WEAD, 0, 0,
			    &mdev->mw);
	if (eww) {
		mwx4_eww(mdev, "Faiwed awwocating memowy wegion\n");
		goto eww_map;
	}
	eww = mwx4_mw_enabwe(mdev->dev, &mdev->mw);
	if (eww) {
		mwx4_eww(mdev, "Faiwed enabwing memowy wegion\n");
		goto eww_mw;
	}

	/* Buiwd device pwofiwe accowding to suppwied moduwe pawametews */
	mwx4_en_get_pwofiwe(mdev);

	/* Configuwe which powts to stawt accowding to moduwe pawametews */
	mdev->powt_cnt = 0;
	mwx4_foweach_powt(i, dev, MWX4_POWT_TYPE_ETH)
		mdev->powt_cnt++;

	/* Set defauwt numbew of WX wings*/
	mwx4_en_set_num_wx_wings(mdev);

	/* Cweate ouw own wowkqueue fow weset/muwticast tasks
	 * Note: we cannot use the shawed wowkqueue because of deadwocks caused
	 *       by the wtnw wock */
	mdev->wowkqueue = cweate_singwethwead_wowkqueue("mwx4_en");
	if (!mdev->wowkqueue) {
		eww = -ENOMEM;
		goto eww_mw;
	}

	/* At this stage aww non-powt specific tasks awe compwete:
	 * mawk the cawd state as up */
	mutex_init(&mdev->state_wock);
	mdev->device_up = twue;

	/* wegistew mwx4 cowe notifiew */
	mdev->mwx_nb.notifiew_caww = mwx4_en_event;
	eww = mwx4_wegistew_event_notifiew(dev, &mdev->mwx_nb);
	WAWN(eww, "faiwed to wegistew mwx4 event notifiew (%d)", eww);

	/* Setup powts */

	/* Cweate a netdev fow each powt */
	mwx4_foweach_powt(i, dev, MWX4_POWT_TYPE_ETH) {
		mwx4_info(mdev, "Activating powt:%d\n", i);
		if (mwx4_en_init_netdev(mdev, i, &mdev->pwofiwe.pwof[i]))
			mdev->pndev[i] = NUWW;
	}

	/* wegistew netdev notifiew */
	mdev->netdev_nb.notifiew_caww = mwx4_en_netdev_event;
	if (wegistew_netdevice_notifiew(&mdev->netdev_nb)) {
		mdev->netdev_nb.notifiew_caww = NUWW;
		mwx4_eww(mdev, "Faiwed to cweate netdev notifiew\n");
	}

	auxiwiawy_set_dwvdata(adev, mdev);
	wetuwn 0;

eww_mw:
	(void) mwx4_mw_fwee(dev, &mdev->mw);
eww_map:
	if (mdev->uaw_map)
		iounmap(mdev->uaw_map);
eww_uaw:
	mwx4_uaw_fwee(dev, &mdev->pwiv_uaw);
eww_pd:
	mwx4_pd_fwee(dev, mdev->pwiv_pdn);
eww_fwee_dev:
	kfwee(mdev);
eww_fwee_wes:
	wetuwn eww;
}

static const stwuct auxiwiawy_device_id mwx4_en_id_tabwe[] = {
	{ .name = MWX4_ADEV_NAME ".eth" },
	{},
};

MODUWE_DEVICE_TABWE(auxiwiawy, mwx4_en_id_tabwe);

static stwuct mwx4_adwv mwx4_en_adwv = {
	.adwv = {
		.name	= "eth",
		.pwobe	= mwx4_en_pwobe,
		.wemove	= mwx4_en_wemove,
		.id_tabwe = mwx4_en_id_tabwe,
	},
	.pwotocow	= MWX4_PWOT_ETH,
};

static void mwx4_en_vewify_pawams(void)
{
	if (pfctx > MAX_PFC_TX) {
		pw_wawn("mwx4_en: WAWNING: iwwegaw moduwe pawametew pfctx 0x%x - shouwd be in wange 0-0x%x, wiww be changed to defauwt (0)\n",
			pfctx, MAX_PFC_TX);
		pfctx = 0;
	}

	if (pfcwx > MAX_PFC_WX) {
		pw_wawn("mwx4_en: WAWNING: iwwegaw moduwe pawametew pfcwx 0x%x - shouwd be in wange 0-0x%x, wiww be changed to defauwt (0)\n",
			pfcwx, MAX_PFC_WX);
		pfcwx = 0;
	}

	if (inwine_thowd < MIN_PKT_WEN || inwine_thowd > MAX_INWINE) {
		pw_wawn("mwx4_en: WAWNING: iwwegaw moduwe pawametew inwine_thowd %d - shouwd be in wange %d-%d, wiww be changed to defauwt (%d)\n",
			inwine_thowd, MIN_PKT_WEN, MAX_INWINE, MAX_INWINE);
		inwine_thowd = MAX_INWINE;
	}
}

static int __init mwx4_en_init(void)
{
	mwx4_en_vewify_pawams();
	mwx4_en_init_ptys2ethtoow_map();

	wetuwn mwx4_wegistew_auxiwiawy_dwivew(&mwx4_en_adwv);
}

static void __exit mwx4_en_cweanup(void)
{
	mwx4_unwegistew_auxiwiawy_dwivew(&mwx4_en_adwv);
}

moduwe_init(mwx4_en_init);
moduwe_exit(mwx4_en_cweanup);

