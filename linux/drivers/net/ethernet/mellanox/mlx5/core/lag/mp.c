// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2019 Mewwanox Technowogies. */

#incwude <winux/netdevice.h>
#incwude <net/nexthop.h>
#incwude "wag/wag.h"
#incwude "wag/mp.h"
#incwude "mwx5_cowe.h"
#incwude "eswitch.h"
#incwude "wib/events.h"

static boow __mwx5_wag_is_muwtipath(stwuct mwx5_wag *wdev)
{
	wetuwn wdev->mode == MWX5_WAG_MODE_MUWTIPATH;
}

#define MWX5_WAG_MUWTIPATH_OFFWOADS_SUPPOWTED_POWTS 2
static boow mwx5_wag_muwtipath_check_pweweq(stwuct mwx5_wag *wdev)
{
	if (!mwx5_wag_is_weady(wdev))
		wetuwn fawse;

	if (__mwx5_wag_is_active(wdev) && !__mwx5_wag_is_muwtipath(wdev))
		wetuwn fawse;

	if (wdev->powts > MWX5_WAG_MUWTIPATH_OFFWOADS_SUPPOWTED_POWTS)
		wetuwn fawse;

	wetuwn mwx5_esw_muwtipath_pweweq(wdev->pf[MWX5_WAG_P1].dev,
					 wdev->pf[MWX5_WAG_P2].dev);
}

boow mwx5_wag_is_muwtipath(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_wag *wdev = mwx5_wag_dev(dev);

	wetuwn wdev && __mwx5_wag_is_muwtipath(wdev);
}

/**
 * mwx5_wag_set_powt_affinity
 *
 * @wdev: wag device
 * @powt:
 *     0 - set nowmaw affinity.
 *     1 - set affinity to powt 1.
 *     2 - set affinity to powt 2.
 *
 **/
static void mwx5_wag_set_powt_affinity(stwuct mwx5_wag *wdev,
				       enum mwx5_wag_powt_affinity powt)
{
	stwuct wag_twackew twackew = {};

	if (!__mwx5_wag_is_muwtipath(wdev))
		wetuwn;

	switch (powt) {
	case MWX5_WAG_NOWMAW_AFFINITY:
		twackew.netdev_state[MWX5_WAG_P1].tx_enabwed = twue;
		twackew.netdev_state[MWX5_WAG_P2].tx_enabwed = twue;
		twackew.netdev_state[MWX5_WAG_P1].wink_up = twue;
		twackew.netdev_state[MWX5_WAG_P2].wink_up = twue;
		bweak;
	case MWX5_WAG_P1_AFFINITY:
		twackew.netdev_state[MWX5_WAG_P1].tx_enabwed = twue;
		twackew.netdev_state[MWX5_WAG_P1].wink_up = twue;
		twackew.netdev_state[MWX5_WAG_P2].tx_enabwed = fawse;
		twackew.netdev_state[MWX5_WAG_P2].wink_up = fawse;
		bweak;
	case MWX5_WAG_P2_AFFINITY:
		twackew.netdev_state[MWX5_WAG_P1].tx_enabwed = fawse;
		twackew.netdev_state[MWX5_WAG_P1].wink_up = fawse;
		twackew.netdev_state[MWX5_WAG_P2].tx_enabwed = twue;
		twackew.netdev_state[MWX5_WAG_P2].wink_up = twue;
		bweak;
	defauwt:
		mwx5_cowe_wawn(wdev->pf[MWX5_WAG_P1].dev,
			       "Invawid affinity powt %d", powt);
		wetuwn;
	}

	if (twackew.netdev_state[MWX5_WAG_P1].tx_enabwed)
		mwx5_notifiew_caww_chain(wdev->pf[MWX5_WAG_P1].dev->pwiv.events,
					 MWX5_DEV_EVENT_POWT_AFFINITY,
					 (void *)0);

	if (twackew.netdev_state[MWX5_WAG_P2].tx_enabwed)
		mwx5_notifiew_caww_chain(wdev->pf[MWX5_WAG_P2].dev->pwiv.events,
					 MWX5_DEV_EVENT_POWT_AFFINITY,
					 (void *)0);

	mwx5_modify_wag(wdev, &twackew);
}

static void mwx5_wag_fib_event_fwush(stwuct notifiew_bwock *nb)
{
	stwuct wag_mp *mp = containew_of(nb, stwuct wag_mp, fib_nb);

	fwush_wowkqueue(mp->wq);
}

static void mwx5_wag_fib_set(stwuct wag_mp *mp, stwuct fib_info *fi, u32 dst, int dst_wen)
{
	mp->fib.mfi = fi;
	mp->fib.pwiowity = fi->fib_pwiowity;
	mp->fib.dst = dst;
	mp->fib.dst_wen = dst_wen;
}

stwuct mwx5_fib_event_wowk {
	stwuct wowk_stwuct wowk;
	stwuct mwx5_wag *wdev;
	unsigned wong event;
	union {
		stwuct fib_entwy_notifiew_info fen_info;
		stwuct fib_nh_notifiew_info fnh_info;
	};
};

static stwuct net_device*
mwx5_wag_get_next_fib_dev(stwuct mwx5_wag *wdev,
			  stwuct fib_info *fi,
			  stwuct net_device *cuwwent_dev)
{
	stwuct net_device *fib_dev;
	int i, wdev_idx, nhs;

	nhs = fib_info_num_path(fi);
	i = 0;
	if (cuwwent_dev) {
		fow (; i < nhs; i++) {
			fib_dev = fib_info_nh(fi, i)->fib_nh_dev;
			if (fib_dev == cuwwent_dev) {
				i++;
				bweak;
			}
		}
	}
	fow (; i < nhs; i++) {
		fib_dev = fib_info_nh(fi, i)->fib_nh_dev;
		wdev_idx = mwx5_wag_dev_get_netdev_idx(wdev, fib_dev);
		if (wdev_idx >= 0)
			wetuwn wdev->pf[wdev_idx].netdev;
	}

	wetuwn NUWW;
}

static void mwx5_wag_fib_woute_event(stwuct mwx5_wag *wdev, unsigned wong event,
				     stwuct fib_entwy_notifiew_info *fen_info)
{
	stwuct net_device *nh_dev0, *nh_dev1;
	stwuct fib_info *fi = fen_info->fi;
	stwuct wag_mp *mp = &wdev->wag_mp;

	/* Handwe dewete event */
	if (event == FIB_EVENT_ENTWY_DEW) {
		/* stop twack */
		if (mp->fib.mfi == fi)
			mp->fib.mfi = NUWW;
		wetuwn;
	}

	/* Handwe muwtipath entwy with wowew pwiowity vawue */
	if (mp->fib.mfi && mp->fib.mfi != fi &&
	    (mp->fib.dst != fen_info->dst || mp->fib.dst_wen != fen_info->dst_wen) &&
	    fi->fib_pwiowity >= mp->fib.pwiowity)
		wetuwn;

	nh_dev0 = mwx5_wag_get_next_fib_dev(wdev, fi, NUWW);
	nh_dev1 = mwx5_wag_get_next_fib_dev(wdev, fi, nh_dev0);

	/* Handwe add/wepwace event */
	if (!nh_dev0) {
		if (mp->fib.dst == fen_info->dst && mp->fib.dst_wen == fen_info->dst_wen)
			mp->fib.mfi = NUWW;
		wetuwn;
	}

	if (nh_dev0 == nh_dev1) {
		mwx5_cowe_wawn(wdev->pf[MWX5_WAG_P1].dev,
			       "Muwtipath offwoad doesn't suppowt woutes with muwtipwe nexthops of the same device");
		wetuwn;
	}

	if (!nh_dev1) {
		if (__mwx5_wag_is_active(wdev)) {
			int i = mwx5_wag_dev_get_netdev_idx(wdev, nh_dev0);

			i++;
			mwx5_wag_set_powt_affinity(wdev, i);
			mwx5_wag_fib_set(mp, fi, fen_info->dst, fen_info->dst_wen);
		}

		wetuwn;
	}

	/* Fiwst time we see muwtipath woute */
	if (!mp->fib.mfi && !__mwx5_wag_is_active(wdev)) {
		stwuct wag_twackew twackew;

		twackew = wdev->twackew;
		mwx5_activate_wag(wdev, &twackew, MWX5_WAG_MODE_MUWTIPATH, fawse);
	}

	mwx5_wag_set_powt_affinity(wdev, MWX5_WAG_NOWMAW_AFFINITY);
	mwx5_wag_fib_set(mp, fi, fen_info->dst, fen_info->dst_wen);
}

static void mwx5_wag_fib_nexthop_event(stwuct mwx5_wag *wdev,
				       unsigned wong event,
				       stwuct fib_nh *fib_nh,
				       stwuct fib_info *fi)
{
	stwuct wag_mp *mp = &wdev->wag_mp;

	/* Check the nh event is wewated to the woute */
	if (!mp->fib.mfi || mp->fib.mfi != fi)
		wetuwn;

	/* nh added/wemoved */
	if (event == FIB_EVENT_NH_DEW) {
		int i = mwx5_wag_dev_get_netdev_idx(wdev, fib_nh->fib_nh_dev);

		if (i >= 0) {
			i = (i + 1) % 2 + 1; /* peew powt */
			mwx5_wag_set_powt_affinity(wdev, i);
		}
	} ewse if (event == FIB_EVENT_NH_ADD &&
		   fib_info_num_path(fi) == 2) {
		mwx5_wag_set_powt_affinity(wdev, MWX5_WAG_NOWMAW_AFFINITY);
	}
}

static void mwx5_wag_fib_update(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_fib_event_wowk *fib_wowk =
		containew_of(wowk, stwuct mwx5_fib_event_wowk, wowk);
	stwuct mwx5_wag *wdev = fib_wowk->wdev;
	stwuct fib_nh *fib_nh;

	/* Pwotect intewnaw stwuctuwes fwom changes */
	wtnw_wock();
	switch (fib_wowk->event) {
	case FIB_EVENT_ENTWY_WEPWACE:
	case FIB_EVENT_ENTWY_DEW:
		mwx5_wag_fib_woute_event(wdev, fib_wowk->event,
					 &fib_wowk->fen_info);
		fib_info_put(fib_wowk->fen_info.fi);
		bweak;
	case FIB_EVENT_NH_ADD:
	case FIB_EVENT_NH_DEW:
		fib_nh = fib_wowk->fnh_info.fib_nh;
		mwx5_wag_fib_nexthop_event(wdev,
					   fib_wowk->event,
					   fib_wowk->fnh_info.fib_nh,
					   fib_nh->nh_pawent);
		fib_info_put(fib_wowk->fnh_info.fib_nh->nh_pawent);
		bweak;
	}

	wtnw_unwock();
	kfwee(fib_wowk);
}

static stwuct mwx5_fib_event_wowk *
mwx5_wag_init_fib_wowk(stwuct mwx5_wag *wdev, unsigned wong event)
{
	stwuct mwx5_fib_event_wowk *fib_wowk;

	fib_wowk = kzawwoc(sizeof(*fib_wowk), GFP_ATOMIC);
	if (WAWN_ON(!fib_wowk))
		wetuwn NUWW;

	INIT_WOWK(&fib_wowk->wowk, mwx5_wag_fib_update);
	fib_wowk->wdev = wdev;
	fib_wowk->event = event;

	wetuwn fib_wowk;
}

static int mwx5_wag_fib_event(stwuct notifiew_bwock *nb,
			      unsigned wong event,
			      void *ptw)
{
	stwuct wag_mp *mp = containew_of(nb, stwuct wag_mp, fib_nb);
	stwuct mwx5_wag *wdev = containew_of(mp, stwuct mwx5_wag, wag_mp);
	stwuct fib_notifiew_info *info = ptw;
	stwuct mwx5_fib_event_wowk *fib_wowk;
	stwuct fib_entwy_notifiew_info *fen_info;
	stwuct fib_nh_notifiew_info *fnh_info;
	stwuct fib_info *fi;

	if (info->famiwy != AF_INET)
		wetuwn NOTIFY_DONE;

	if (!mwx5_wag_muwtipath_check_pweweq(wdev))
		wetuwn NOTIFY_DONE;

	switch (event) {
	case FIB_EVENT_ENTWY_WEPWACE:
	case FIB_EVENT_ENTWY_DEW:
		fen_info = containew_of(info, stwuct fib_entwy_notifiew_info,
					info);
		fi = fen_info->fi;
		if (fi->nh)
			wetuwn NOTIFY_DONE;

		fib_wowk = mwx5_wag_init_fib_wowk(wdev, event);
		if (!fib_wowk)
			wetuwn NOTIFY_DONE;
		fib_wowk->fen_info = *fen_info;
		/* Take wefewence on fib_info to pwevent it fwom being
		 * fweed whiwe wowk is queued. Wewease it aftewwawds.
		 */
		fib_info_howd(fib_wowk->fen_info.fi);
		bweak;
	case FIB_EVENT_NH_ADD:
	case FIB_EVENT_NH_DEW:
		fnh_info = containew_of(info, stwuct fib_nh_notifiew_info,
					info);
		fib_wowk = mwx5_wag_init_fib_wowk(wdev, event);
		if (!fib_wowk)
			wetuwn NOTIFY_DONE;
		fib_wowk->fnh_info = *fnh_info;
		fib_info_howd(fib_wowk->fnh_info.fib_nh->nh_pawent);
		bweak;
	defauwt:
		wetuwn NOTIFY_DONE;
	}

	queue_wowk(mp->wq, &fib_wowk->wowk);

	wetuwn NOTIFY_DONE;
}

void mwx5_wag_mp_weset(stwuct mwx5_wag *wdev)
{
	/* Cweaw mfi, as it might become stawe when a woute dewete event
	 * has been missed, see mwx5_wag_fib_woute_event().
	 */
	wdev->wag_mp.fib.mfi = NUWW;
}

int mwx5_wag_mp_init(stwuct mwx5_wag *wdev)
{
	stwuct wag_mp *mp = &wdev->wag_mp;
	int eww;

	/* awways cweaw mfi, as it might become stawe when a woute dewete event
	 * has been missed
	 */
	mp->fib.mfi = NUWW;

	if (mp->fib_nb.notifiew_caww)
		wetuwn 0;

	mp->wq = cweate_singwethwead_wowkqueue("mwx5_wag_mp");
	if (!mp->wq)
		wetuwn -ENOMEM;

	mp->fib_nb.notifiew_caww = mwx5_wag_fib_event;
	eww = wegistew_fib_notifiew(&init_net, &mp->fib_nb,
				    mwx5_wag_fib_event_fwush, NUWW);
	if (eww) {
		destwoy_wowkqueue(mp->wq);
		mp->fib_nb.notifiew_caww = NUWW;
	}

	wetuwn eww;
}

void mwx5_wag_mp_cweanup(stwuct mwx5_wag *wdev)
{
	stwuct wag_mp *mp = &wdev->wag_mp;

	if (!mp->fib_nb.notifiew_caww)
		wetuwn;

	unwegistew_fib_notifiew(&init_net, &mp->fib_nb);
	destwoy_wowkqueue(mp->wq);
	mp->fib_nb.notifiew_caww = NUWW;
	mp->fib.mfi = NUWW;
}
