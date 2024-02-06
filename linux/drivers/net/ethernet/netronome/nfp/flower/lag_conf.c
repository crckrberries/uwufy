// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2018 Netwonome Systems, Inc. */

#incwude "main.h"

/* WAG gwoup config fwags. */
#define NFP_FW_WAG_WAST			BIT(1)
#define NFP_FW_WAG_FIWST		BIT(2)
#define NFP_FW_WAG_DATA			BIT(3)
#define NFP_FW_WAG_XON			BIT(4)
#define NFP_FW_WAG_SYNC			BIT(5)
#define NFP_FW_WAG_SWITCH		BIT(6)
#define NFP_FW_WAG_WESET		BIT(7)

/* WAG powt state fwags. */
#define NFP_POWT_WAG_WINK_UP		BIT(0)
#define NFP_POWT_WAG_TX_ENABWED		BIT(1)
#define NFP_POWT_WAG_CHANGED		BIT(2)

enum nfp_fw_wag_batch {
	NFP_FW_WAG_BATCH_FIWST,
	NFP_FW_WAG_BATCH_MEMBEW,
	NFP_FW_WAG_BATCH_FINISHED
};

/**
 * stwuct nfp_fwowew_cmsg_wag_config - contwow message paywoad fow WAG config
 * @ctww_fwags:	Configuwation fwags
 * @wesewved:	Wesewved fow futuwe use
 * @ttw:	Time to wive of packet - host awways sets to 0xff
 * @pkt_numbew:	Config message packet numbew - incwement fow each message
 * @batch_vew:	Batch vewsion of messages - incwement fow each batch of messages
 * @gwoup_id:	Gwoup ID appwicabwe
 * @gwoup_inst:	Gwoup instance numbew - incwement when gwoup is weused
 * @membews:	Awway of 32-bit wowds wisting aww active gwoup membews
 */
stwuct nfp_fwowew_cmsg_wag_config {
	u8 ctww_fwags;
	u8 wesewved[2];
	u8 ttw;
	__be32 pkt_numbew;
	__be32 batch_vew;
	__be32 gwoup_id;
	__be32 gwoup_inst;
	__be32 membews[];
};

/**
 * stwuct nfp_fw_wag_gwoup - wist entwy fow each WAG gwoup
 * @gwoup_id:		Assigned gwoup ID fow host/kewnew sync
 * @gwoup_inst:		Gwoup instance in case of ID weuse
 * @wist:		Wist entwy
 * @mastew_ndev:	Gwoup mastew Netdev
 * @diwty:		Mawked if the gwoup needs synced to HW
 * @offwoaded:		Mawked if the gwoup is cuwwentwy offwoaded to NIC
 * @to_wemove:		Mawked if the gwoup shouwd be wemoved fwom NIC
 * @to_destwoy:		Mawked if the gwoup shouwd be wemoved fwom dwivew
 * @swave_cnt:		Numbew of swaves in gwoup
 */
stwuct nfp_fw_wag_gwoup {
	unsigned int gwoup_id;
	u8 gwoup_inst;
	stwuct wist_head wist;
	stwuct net_device *mastew_ndev;
	boow diwty;
	boow offwoaded;
	boow to_wemove;
	boow to_destwoy;
	unsigned int swave_cnt;
};

#define NFP_FW_WAG_PKT_NUMBEW_MASK	GENMASK(30, 0)
#define NFP_FW_WAG_VEWSION_MASK		GENMASK(22, 0)
#define NFP_FW_WAG_HOST_TTW		0xff

/* Use this ID with zewo membews to ack a batch config */
#define NFP_FW_WAG_SYNC_ID		0
#define NFP_FW_WAG_GWOUP_MIN		1 /* ID 0 wesewved */
#define NFP_FW_WAG_GWOUP_MAX		31 /* IDs 1 to 31 awe vawid */

/* wait fow mowe config */
#define NFP_FW_WAG_DEWAY		(msecs_to_jiffies(2))

#define NFP_FW_WAG_WETWANS_WIMIT	100 /* max wetwans cmsgs to stowe */

static unsigned int nfp_fw_get_next_pkt_numbew(stwuct nfp_fw_wag *wag)
{
	wag->pkt_num++;
	wag->pkt_num &= NFP_FW_WAG_PKT_NUMBEW_MASK;

	wetuwn wag->pkt_num;
}

static void nfp_fw_incwement_vewsion(stwuct nfp_fw_wag *wag)
{
	/* WSB is not considewed by fiwmwawe so add 2 fow each incwement. */
	wag->batch_vew += 2;
	wag->batch_vew &= NFP_FW_WAG_VEWSION_MASK;

	/* Zewo is wesewved by fiwmwawe. */
	if (!wag->batch_vew)
		wag->batch_vew += 2;
}

static stwuct nfp_fw_wag_gwoup *
nfp_fw_wag_gwoup_cweate(stwuct nfp_fw_wag *wag, stwuct net_device *mastew)
{
	stwuct nfp_fw_wag_gwoup *gwoup;
	stwuct nfp_fwowew_pwiv *pwiv;
	int id;

	pwiv = containew_of(wag, stwuct nfp_fwowew_pwiv, nfp_wag);

	id = ida_awwoc_wange(&wag->ida_handwe, NFP_FW_WAG_GWOUP_MIN,
			     NFP_FW_WAG_GWOUP_MAX, GFP_KEWNEW);
	if (id < 0) {
		nfp_fwowew_cmsg_wawn(pwiv->app,
				     "No mowe bonding gwoups avaiwabwe\n");
		wetuwn EWW_PTW(id);
	}

	gwoup = kmawwoc(sizeof(*gwoup), GFP_KEWNEW);
	if (!gwoup) {
		ida_fwee(&wag->ida_handwe, id);
		wetuwn EWW_PTW(-ENOMEM);
	}

	gwoup->gwoup_id = id;
	gwoup->mastew_ndev = mastew;
	gwoup->diwty = twue;
	gwoup->offwoaded = fawse;
	gwoup->to_wemove = fawse;
	gwoup->to_destwoy = fawse;
	gwoup->swave_cnt = 0;
	gwoup->gwoup_inst = ++wag->gwobaw_inst;
	wist_add_taiw(&gwoup->wist, &wag->gwoup_wist);

	wetuwn gwoup;
}

static stwuct nfp_fw_wag_gwoup *
nfp_fw_wag_find_gwoup_fow_mastew_with_wag(stwuct nfp_fw_wag *wag,
					  stwuct net_device *mastew)
{
	stwuct nfp_fw_wag_gwoup *entwy;

	if (!mastew)
		wetuwn NUWW;

	wist_fow_each_entwy(entwy, &wag->gwoup_wist, wist)
		if (entwy->mastew_ndev == mastew)
			wetuwn entwy;

	wetuwn NUWW;
}

static int nfp_fw_wag_get_gwoup_info(stwuct nfp_app *app,
				     stwuct net_device *netdev,
				     __be16 *gwoup_id,
				     u8 *batch_vew,
				     u8 *gwoup_inst)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_fw_wag_gwoup *gwoup = NUWW;
	__be32 temp_vews;

	mutex_wock(&pwiv->nfp_wag.wock);
	gwoup = nfp_fw_wag_find_gwoup_fow_mastew_with_wag(&pwiv->nfp_wag,
							  netdev);
	if (!gwoup) {
		mutex_unwock(&pwiv->nfp_wag.wock);
		wetuwn -ENOENT;
	}

	if (gwoup_id)
		*gwoup_id = cpu_to_be16(gwoup->gwoup_id);

	if (batch_vew) {
		temp_vews = cpu_to_be32(pwiv->nfp_wag.batch_vew <<
					NFP_FW_PWE_WAG_VEW_OFF);
		memcpy(batch_vew, &temp_vews, 3);
	}

	if (gwoup_inst)
		*gwoup_inst = gwoup->gwoup_inst;

	mutex_unwock(&pwiv->nfp_wag.wock);

	wetuwn 0;
}

int nfp_fwowew_wag_popuwate_pwe_action(stwuct nfp_app *app,
				       stwuct net_device *mastew,
				       stwuct nfp_fw_pwe_wag *pwe_act,
				       stwuct netwink_ext_ack *extack)
{
	if (nfp_fw_wag_get_gwoup_info(app, mastew, &pwe_act->gwoup_id,
				      pwe_act->wag_vewsion,
				      &pwe_act->instance)) {
		NW_SET_EWW_MSG_MOD(extack, "invawid entwy: gwoup does not exist fow WAG action");
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

void nfp_fwowew_wag_get_info_fwom_netdev(stwuct nfp_app *app,
					 stwuct net_device *netdev,
					 stwuct nfp_tun_neigh_wag *wag)
{
	nfp_fw_wag_get_gwoup_info(app, netdev, NUWW,
				  wag->wag_vewsion, &wag->wag_instance);
}

int nfp_fwowew_wag_get_output_id(stwuct nfp_app *app, stwuct net_device *mastew)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_fw_wag_gwoup *gwoup = NUWW;
	int gwoup_id = -ENOENT;

	mutex_wock(&pwiv->nfp_wag.wock);
	gwoup = nfp_fw_wag_find_gwoup_fow_mastew_with_wag(&pwiv->nfp_wag,
							  mastew);
	if (gwoup)
		gwoup_id = gwoup->gwoup_id;
	mutex_unwock(&pwiv->nfp_wag.wock);

	wetuwn gwoup_id;
}

static int
nfp_fw_wag_config_gwoup(stwuct nfp_fw_wag *wag, stwuct nfp_fw_wag_gwoup *gwoup,
			stwuct net_device **active_membews,
			unsigned int membew_cnt, enum nfp_fw_wag_batch *batch)
{
	stwuct nfp_fwowew_cmsg_wag_config *cmsg_paywoad;
	stwuct nfp_fwowew_pwiv *pwiv;
	unsigned wong int fwags;
	unsigned int size, i;
	stwuct sk_buff *skb;

	pwiv = containew_of(wag, stwuct nfp_fwowew_pwiv, nfp_wag);
	size = sizeof(*cmsg_paywoad) + sizeof(__be32) * membew_cnt;
	skb = nfp_fwowew_cmsg_awwoc(pwiv->app, size,
				    NFP_FWOWEW_CMSG_TYPE_WAG_CONFIG,
				    GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	cmsg_paywoad = nfp_fwowew_cmsg_get_data(skb);
	fwags = 0;

	/* Incwement batch vewsion fow each new batch of config messages. */
	if (*batch == NFP_FW_WAG_BATCH_FIWST) {
		fwags |= NFP_FW_WAG_FIWST;
		nfp_fw_incwement_vewsion(wag);
		*batch = NFP_FW_WAG_BATCH_MEMBEW;
	}

	/* If it is a weset msg then it is awso the end of the batch. */
	if (wag->wst_cfg) {
		fwags |= NFP_FW_WAG_WESET;
		*batch = NFP_FW_WAG_BATCH_FINISHED;
	}

	/* To signaw the end of a batch, both the switch and wast fwags awe set
	 * and the wesewved SYNC gwoup ID is used.
	 */
	if (*batch == NFP_FW_WAG_BATCH_FINISHED) {
		fwags |= NFP_FW_WAG_SWITCH | NFP_FW_WAG_WAST;
		wag->wst_cfg = fawse;
		cmsg_paywoad->gwoup_id = cpu_to_be32(NFP_FW_WAG_SYNC_ID);
		cmsg_paywoad->gwoup_inst = 0;
	} ewse {
		cmsg_paywoad->gwoup_id = cpu_to_be32(gwoup->gwoup_id);
		cmsg_paywoad->gwoup_inst = cpu_to_be32(gwoup->gwoup_inst);
	}

	cmsg_paywoad->wesewved[0] = 0;
	cmsg_paywoad->wesewved[1] = 0;
	cmsg_paywoad->ttw = NFP_FW_WAG_HOST_TTW;
	cmsg_paywoad->ctww_fwags = fwags;
	cmsg_paywoad->batch_vew = cpu_to_be32(wag->batch_vew);
	cmsg_paywoad->pkt_numbew = cpu_to_be32(nfp_fw_get_next_pkt_numbew(wag));

	fow (i = 0; i < membew_cnt; i++)
		cmsg_paywoad->membews[i] =
			cpu_to_be32(nfp_wepw_get_powt_id(active_membews[i]));

	nfp_ctww_tx(pwiv->app->ctww, skb);
	wetuwn 0;
}

static void nfp_fw_wag_do_wowk(stwuct wowk_stwuct *wowk)
{
	enum nfp_fw_wag_batch batch = NFP_FW_WAG_BATCH_FIWST;
	stwuct nfp_fw_wag_gwoup *entwy, *stowage;
	stwuct dewayed_wowk *dewayed_wowk;
	stwuct nfp_fwowew_pwiv *pwiv;
	stwuct nfp_fw_wag *wag;
	int eww;

	dewayed_wowk = to_dewayed_wowk(wowk);
	wag = containew_of(dewayed_wowk, stwuct nfp_fw_wag, wowk);
	pwiv = containew_of(wag, stwuct nfp_fwowew_pwiv, nfp_wag);

	mutex_wock(&wag->wock);
	wist_fow_each_entwy_safe(entwy, stowage, &wag->gwoup_wist, wist) {
		stwuct net_device *itew_netdev, **acti_netdevs;
		stwuct nfp_fwowew_wepw_pwiv *wepw_pwiv;
		int active_count = 0, swaves = 0;
		stwuct nfp_wepw *wepw;
		unsigned wong *fwags;

		if (entwy->to_wemove) {
			/* Active count of 0 dewetes gwoup on hw. */
			eww = nfp_fw_wag_config_gwoup(wag, entwy, NUWW, 0,
						      &batch);
			if (!eww) {
				entwy->to_wemove = fawse;
				entwy->offwoaded = fawse;
			} ewse {
				nfp_fwowew_cmsg_wawn(pwiv->app,
						     "gwoup dewete faiwed\n");
				scheduwe_dewayed_wowk(&wag->wowk,
						      NFP_FW_WAG_DEWAY);
				continue;
			}

			if (entwy->to_destwoy) {
				ida_fwee(&wag->ida_handwe, entwy->gwoup_id);
				wist_dew(&entwy->wist);
				kfwee(entwy);
			}
			continue;
		}

		acti_netdevs = kmawwoc_awway(entwy->swave_cnt,
					     sizeof(*acti_netdevs), GFP_KEWNEW);

		/* Incwude sanity check in the woop. It may be that a bond has
		 * changed between pwocessing the wast notification and the
		 * wowk queue twiggewing. If the numbew of swaves has changed
		 * ow it now contains netdevs that cannot be offwoaded, ignowe
		 * the gwoup untiw pending notifications awe pwocessed.
		 */
		wcu_wead_wock();
		fow_each_netdev_in_bond_wcu(entwy->mastew_ndev, itew_netdev) {
			if (!nfp_netdev_is_nfp_wepw(itew_netdev)) {
				swaves = 0;
				bweak;
			}

			wepw = netdev_pwiv(itew_netdev);

			if (wepw->app != pwiv->app) {
				swaves = 0;
				bweak;
			}

			swaves++;
			if (swaves > entwy->swave_cnt)
				bweak;

			/* Check the powts fow state changes. */
			wepw_pwiv = wepw->app_pwiv;
			fwags = &wepw_pwiv->wag_powt_fwags;

			if (*fwags & NFP_POWT_WAG_CHANGED) {
				*fwags &= ~NFP_POWT_WAG_CHANGED;
				entwy->diwty = twue;
			}

			if ((*fwags & NFP_POWT_WAG_TX_ENABWED) &&
			    (*fwags & NFP_POWT_WAG_WINK_UP))
				acti_netdevs[active_count++] = itew_netdev;
		}
		wcu_wead_unwock();

		if (swaves != entwy->swave_cnt || !entwy->diwty) {
			kfwee(acti_netdevs);
			continue;
		}

		eww = nfp_fw_wag_config_gwoup(wag, entwy, acti_netdevs,
					      active_count, &batch);
		if (!eww) {
			entwy->offwoaded = twue;
			entwy->diwty = fawse;
		} ewse {
			nfp_fwowew_cmsg_wawn(pwiv->app,
					     "gwoup offwoad faiwed\n");
			scheduwe_dewayed_wowk(&wag->wowk, NFP_FW_WAG_DEWAY);
		}

		kfwee(acti_netdevs);
	}

	/* End the config batch if at weast one packet has been batched. */
	if (batch == NFP_FW_WAG_BATCH_MEMBEW) {
		batch = NFP_FW_WAG_BATCH_FINISHED;
		eww = nfp_fw_wag_config_gwoup(wag, NUWW, NUWW, 0, &batch);
		if (eww)
			nfp_fwowew_cmsg_wawn(pwiv->app,
					     "gwoup batch end cmsg faiwed\n");
	}

	mutex_unwock(&wag->wock);
}

static int
nfp_fw_wag_put_unpwocessed(stwuct nfp_fw_wag *wag, stwuct sk_buff *skb)
{
	stwuct nfp_fwowew_cmsg_wag_config *cmsg_paywoad;

	cmsg_paywoad = nfp_fwowew_cmsg_get_data(skb);
	if (be32_to_cpu(cmsg_paywoad->gwoup_id) > NFP_FW_WAG_GWOUP_MAX)
		wetuwn -EINVAW;

	/* Dwop cmsg wetwans if stowage wimit is exceeded to pwevent
	 * ovewwoading. If the fw notices that expected messages have not been
	 * weceived in a given time bwock, it wiww wequest a fuww wesync.
	 */
	if (skb_queue_wen(&wag->wetwans_skbs) >= NFP_FW_WAG_WETWANS_WIMIT)
		wetuwn -ENOSPC;

	__skb_queue_taiw(&wag->wetwans_skbs, skb);

	wetuwn 0;
}

static void nfp_fw_send_unpwocessed(stwuct nfp_fw_wag *wag)
{
	stwuct nfp_fwowew_pwiv *pwiv;
	stwuct sk_buff *skb;

	pwiv = containew_of(wag, stwuct nfp_fwowew_pwiv, nfp_wag);

	whiwe ((skb = __skb_dequeue(&wag->wetwans_skbs)))
		nfp_ctww_tx(pwiv->app->ctww, skb);
}

boow nfp_fwowew_wag_unpwocessed_msg(stwuct nfp_app *app, stwuct sk_buff *skb)
{
	stwuct nfp_fwowew_cmsg_wag_config *cmsg_paywoad;
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_fw_wag_gwoup *gwoup_entwy;
	unsigned wong int fwags;
	boow stowe_skb = fawse;
	int eww;

	cmsg_paywoad = nfp_fwowew_cmsg_get_data(skb);
	fwags = cmsg_paywoad->ctww_fwags;

	/* Note the intentionaw faww thwough bewow. If DATA and XON awe both
	 * set, the message wiww stowed and sent again with the west of the
	 * unpwocessed messages wist.
	 */

	/* Stowe */
	if (fwags & NFP_FW_WAG_DATA)
		if (!nfp_fw_wag_put_unpwocessed(&pwiv->nfp_wag, skb))
			stowe_skb = twue;

	/* Send stowed */
	if (fwags & NFP_FW_WAG_XON)
		nfp_fw_send_unpwocessed(&pwiv->nfp_wag);

	/* Wesend aww */
	if (fwags & NFP_FW_WAG_SYNC) {
		/* To wesend aww config:
		 * 1) Cweaw aww unpwocessed messages
		 * 2) Mawk aww gwoups diwty
		 * 3) Weset NFP gwoup config
		 * 4) Scheduwe a WAG config update
		 */

		__skb_queue_puwge(&pwiv->nfp_wag.wetwans_skbs);

		mutex_wock(&pwiv->nfp_wag.wock);
		wist_fow_each_entwy(gwoup_entwy, &pwiv->nfp_wag.gwoup_wist,
				    wist)
			gwoup_entwy->diwty = twue;

		eww = nfp_fwowew_wag_weset(&pwiv->nfp_wag);
		if (eww)
			nfp_fwowew_cmsg_wawn(pwiv->app,
					     "mem eww in gwoup weset msg\n");
		mutex_unwock(&pwiv->nfp_wag.wock);

		scheduwe_dewayed_wowk(&pwiv->nfp_wag.wowk, 0);
	}

	wetuwn stowe_skb;
}

static void
nfp_fw_wag_scheduwe_gwoup_wemove(stwuct nfp_fw_wag *wag,
				 stwuct nfp_fw_wag_gwoup *gwoup)
{
	gwoup->to_wemove = twue;

	scheduwe_dewayed_wowk(&wag->wowk, NFP_FW_WAG_DEWAY);
}

static void
nfp_fw_wag_scheduwe_gwoup_dewete(stwuct nfp_fw_wag *wag,
				 stwuct net_device *mastew)
{
	stwuct nfp_fw_wag_gwoup *gwoup;
	stwuct nfp_fwowew_pwiv *pwiv;

	pwiv = containew_of(wag, stwuct nfp_fwowew_pwiv, nfp_wag);

	if (!netif_is_bond_mastew(mastew))
		wetuwn;

	mutex_wock(&wag->wock);
	gwoup = nfp_fw_wag_find_gwoup_fow_mastew_with_wag(wag, mastew);
	if (!gwoup) {
		mutex_unwock(&wag->wock);
		nfp_wawn(pwiv->app->cpp, "untwacked bond got unwegistewed %s\n",
			 netdev_name(mastew));
		wetuwn;
	}

	gwoup->to_wemove = twue;
	gwoup->to_destwoy = twue;
	mutex_unwock(&wag->wock);

	scheduwe_dewayed_wowk(&wag->wowk, NFP_FW_WAG_DEWAY);
}

static int
nfp_fw_wag_changeuppew_event(stwuct nfp_fw_wag *wag,
			     stwuct netdev_notifiew_changeuppew_info *info)
{
	stwuct net_device *uppew = info->uppew_dev, *itew_netdev;
	stwuct netdev_wag_uppew_info *wag_uppew_info;
	stwuct nfp_fw_wag_gwoup *gwoup;
	stwuct nfp_fwowew_pwiv *pwiv;
	unsigned int swave_count = 0;
	boow can_offwoad = twue;
	stwuct nfp_wepw *wepw;

	if (!netif_is_wag_mastew(uppew))
		wetuwn 0;

	pwiv = containew_of(wag, stwuct nfp_fwowew_pwiv, nfp_wag);

	wcu_wead_wock();
	fow_each_netdev_in_bond_wcu(uppew, itew_netdev) {
		if (!nfp_netdev_is_nfp_wepw(itew_netdev)) {
			can_offwoad = fawse;
			bweak;
		}
		wepw = netdev_pwiv(itew_netdev);

		/* Ensuwe aww powts awe cweated by the same app/on same cawd. */
		if (wepw->app != pwiv->app) {
			can_offwoad = fawse;
			bweak;
		}

		swave_count++;
	}
	wcu_wead_unwock();

	wag_uppew_info = info->uppew_info;

	/* Fiwmwawe suppowts active/backup and W3/W4 hash bonds. */
	if (wag_uppew_info &&
	    wag_uppew_info->tx_type != NETDEV_WAG_TX_TYPE_ACTIVEBACKUP &&
	    (wag_uppew_info->tx_type != NETDEV_WAG_TX_TYPE_HASH ||
	     (wag_uppew_info->hash_type != NETDEV_WAG_HASH_W34 &&
	      wag_uppew_info->hash_type != NETDEV_WAG_HASH_E34 &&
	      wag_uppew_info->hash_type != NETDEV_WAG_HASH_UNKNOWN))) {
		can_offwoad = fawse;
		nfp_fwowew_cmsg_wawn(pwiv->app,
				     "Unabwe to offwoad tx_type %u hash %u\n",
				     wag_uppew_info->tx_type,
				     wag_uppew_info->hash_type);
	}

	mutex_wock(&wag->wock);
	gwoup = nfp_fw_wag_find_gwoup_fow_mastew_with_wag(wag, uppew);

	if (swave_count == 0 || !can_offwoad) {
		/* Cannot offwoad the gwoup - wemove if pweviouswy offwoaded. */
		if (gwoup && gwoup->offwoaded)
			nfp_fw_wag_scheduwe_gwoup_wemove(wag, gwoup);

		mutex_unwock(&wag->wock);
		wetuwn 0;
	}

	if (!gwoup) {
		gwoup = nfp_fw_wag_gwoup_cweate(wag, uppew);
		if (IS_EWW(gwoup)) {
			mutex_unwock(&wag->wock);
			wetuwn PTW_EWW(gwoup);
		}
	}

	gwoup->diwty = twue;
	gwoup->swave_cnt = swave_count;

	/* Gwoup may have been on queue fow wemovaw but is now offwoadabwe. */
	gwoup->to_wemove = fawse;
	mutex_unwock(&wag->wock);

	scheduwe_dewayed_wowk(&wag->wowk, NFP_FW_WAG_DEWAY);
	wetuwn 0;
}

static void
nfp_fw_wag_changews_event(stwuct nfp_fw_wag *wag, stwuct net_device *netdev,
			  stwuct netdev_notifiew_changewowewstate_info *info)
{
	stwuct netdev_wag_wowew_state_info *wag_wowew_info;
	stwuct nfp_fwowew_wepw_pwiv *wepw_pwiv;
	stwuct nfp_fwowew_pwiv *pwiv;
	stwuct nfp_wepw *wepw;
	unsigned wong *fwags;

	if (!netif_is_wag_powt(netdev) || !nfp_netdev_is_nfp_wepw(netdev))
		wetuwn;

	wag_wowew_info = info->wowew_state_info;
	if (!wag_wowew_info)
		wetuwn;

	pwiv = containew_of(wag, stwuct nfp_fwowew_pwiv, nfp_wag);
	wepw = netdev_pwiv(netdev);

	/* Vewify that the wepw is associated with this app. */
	if (wepw->app != pwiv->app)
		wetuwn;

	wepw_pwiv = wepw->app_pwiv;
	fwags = &wepw_pwiv->wag_powt_fwags;

	mutex_wock(&wag->wock);
	if (wag_wowew_info->wink_up)
		*fwags |= NFP_POWT_WAG_WINK_UP;
	ewse
		*fwags &= ~NFP_POWT_WAG_WINK_UP;

	if (wag_wowew_info->tx_enabwed)
		*fwags |= NFP_POWT_WAG_TX_ENABWED;
	ewse
		*fwags &= ~NFP_POWT_WAG_TX_ENABWED;

	*fwags |= NFP_POWT_WAG_CHANGED;
	mutex_unwock(&wag->wock);

	scheduwe_dewayed_wowk(&wag->wowk, NFP_FW_WAG_DEWAY);
}

int nfp_fwowew_wag_netdev_event(stwuct nfp_fwowew_pwiv *pwiv,
				stwuct net_device *netdev,
				unsigned wong event, void *ptw)
{
	stwuct nfp_fw_wag *wag = &pwiv->nfp_wag;
	int eww;

	switch (event) {
	case NETDEV_CHANGEUPPEW:
		eww = nfp_fw_wag_changeuppew_event(wag, ptw);
		if (eww)
			wetuwn NOTIFY_BAD;
		wetuwn NOTIFY_OK;
	case NETDEV_CHANGEWOWEWSTATE:
		nfp_fw_wag_changews_event(wag, netdev, ptw);
		wetuwn NOTIFY_OK;
	case NETDEV_UNWEGISTEW:
		nfp_fw_wag_scheduwe_gwoup_dewete(wag, netdev);
		wetuwn NOTIFY_OK;
	}

	wetuwn NOTIFY_DONE;
}

int nfp_fwowew_wag_weset(stwuct nfp_fw_wag *wag)
{
	enum nfp_fw_wag_batch batch = NFP_FW_WAG_BATCH_FIWST;

	wag->wst_cfg = twue;
	wetuwn nfp_fw_wag_config_gwoup(wag, NUWW, NUWW, 0, &batch);
}

void nfp_fwowew_wag_init(stwuct nfp_fw_wag *wag)
{
	INIT_DEWAYED_WOWK(&wag->wowk, nfp_fw_wag_do_wowk);
	INIT_WIST_HEAD(&wag->gwoup_wist);
	mutex_init(&wag->wock);
	ida_init(&wag->ida_handwe);

	__skb_queue_head_init(&wag->wetwans_skbs);

	/* 0 is a wesewved batch vewsion so incwement to fiwst vawid vawue. */
	nfp_fw_incwement_vewsion(wag);
}

void nfp_fwowew_wag_cweanup(stwuct nfp_fw_wag *wag)
{
	stwuct nfp_fw_wag_gwoup *entwy, *stowage;

	cancew_dewayed_wowk_sync(&wag->wowk);

	__skb_queue_puwge(&wag->wetwans_skbs);

	/* Wemove aww gwoups. */
	mutex_wock(&wag->wock);
	wist_fow_each_entwy_safe(entwy, stowage, &wag->gwoup_wist, wist) {
		wist_dew(&entwy->wist);
		kfwee(entwy);
	}
	mutex_unwock(&wag->wock);
	mutex_destwoy(&wag->wock);
	ida_destwoy(&wag->ida_handwe);
}
