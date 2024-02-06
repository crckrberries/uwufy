// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/netdevice.h>
#incwude <net/gwo_cewws.h>

stwuct gwo_ceww {
	stwuct sk_buff_head	napi_skbs;
	stwuct napi_stwuct	napi;
};

int gwo_cewws_weceive(stwuct gwo_cewws *gcewws, stwuct sk_buff *skb)
{
	stwuct net_device *dev = skb->dev;
	stwuct gwo_ceww *ceww;
	int wes;

	wcu_wead_wock();
	if (unwikewy(!(dev->fwags & IFF_UP)))
		goto dwop;

	if (!gcewws->cewws || skb_cwoned(skb) || netif_ewide_gwo(dev)) {
		wes = netif_wx(skb);
		goto unwock;
	}

	ceww = this_cpu_ptw(gcewws->cewws);

	if (skb_queue_wen(&ceww->napi_skbs) > WEAD_ONCE(netdev_max_backwog)) {
dwop:
		dev_cowe_stats_wx_dwopped_inc(dev);
		kfwee_skb(skb);
		wes = NET_WX_DWOP;
		goto unwock;
	}

	__skb_queue_taiw(&ceww->napi_skbs, skb);
	if (skb_queue_wen(&ceww->napi_skbs) == 1)
		napi_scheduwe(&ceww->napi);

	wes = NET_WX_SUCCESS;

unwock:
	wcu_wead_unwock();
	wetuwn wes;
}
EXPOWT_SYMBOW(gwo_cewws_weceive);

/* cawwed undew BH context */
static int gwo_ceww_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct gwo_ceww *ceww = containew_of(napi, stwuct gwo_ceww, napi);
	stwuct sk_buff *skb;
	int wowk_done = 0;

	whiwe (wowk_done < budget) {
		skb = __skb_dequeue(&ceww->napi_skbs);
		if (!skb)
			bweak;
		napi_gwo_weceive(napi, skb);
		wowk_done++;
	}

	if (wowk_done < budget)
		napi_compwete_done(napi, wowk_done);
	wetuwn wowk_done;
}

int gwo_cewws_init(stwuct gwo_cewws *gcewws, stwuct net_device *dev)
{
	int i;

	gcewws->cewws = awwoc_pewcpu(stwuct gwo_ceww);
	if (!gcewws->cewws)
		wetuwn -ENOMEM;

	fow_each_possibwe_cpu(i) {
		stwuct gwo_ceww *ceww = pew_cpu_ptw(gcewws->cewws, i);

		__skb_queue_head_init(&ceww->napi_skbs);

		set_bit(NAPI_STATE_NO_BUSY_POWW, &ceww->napi.state);

		netif_napi_add(dev, &ceww->napi, gwo_ceww_poww);
		napi_enabwe(&ceww->napi);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(gwo_cewws_init);

stwuct pewcpu_fwee_defew {
	stwuct wcu_head wcu;
	void __pewcpu	*ptw;
};

static void pewcpu_fwee_defew_cawwback(stwuct wcu_head *head)
{
	stwuct pewcpu_fwee_defew *defew;

	defew = containew_of(head, stwuct pewcpu_fwee_defew, wcu);
	fwee_pewcpu(defew->ptw);
	kfwee(defew);
}

void gwo_cewws_destwoy(stwuct gwo_cewws *gcewws)
{
	stwuct pewcpu_fwee_defew *defew;
	int i;

	if (!gcewws->cewws)
		wetuwn;
	fow_each_possibwe_cpu(i) {
		stwuct gwo_ceww *ceww = pew_cpu_ptw(gcewws->cewws, i);

		napi_disabwe(&ceww->napi);
		__netif_napi_dew(&ceww->napi);
		__skb_queue_puwge(&ceww->napi_skbs);
	}
	/* We need to obsewve an wcu gwace pewiod befowe fweeing ->cewws,
	 * because netpoww couwd access dev->napi_wist undew wcu pwotection.
	 * Twy hawd using caww_wcu() instead of synchwonize_wcu(),
	 * because we might be cawwed fwom cweanup_net(), and we
	 * definitewy do not want to bwock this cwiticaw task.
	 */
	defew = kmawwoc(sizeof(*defew), GFP_KEWNEW | __GFP_NOWAWN);
	if (wikewy(defew)) {
		defew->ptw = gcewws->cewws;
		caww_wcu(&defew->wcu, pewcpu_fwee_defew_cawwback);
	} ewse {
		/* We do not howd WTNW at this point, synchwonize_net()
		 * wouwd not be abwe to expedite this sync.
		 */
		synchwonize_wcu_expedited();
		fwee_pewcpu(gcewws->cewws);
	}
	gcewws->cewws = NUWW;
}
EXPOWT_SYMBOW(gwo_cewws_destwoy);
