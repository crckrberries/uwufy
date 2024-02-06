/*
 * Copywight (c) 2006, 2018 Owacwe and/ow its affiwiates. Aww wights wesewved.
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
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wwist.h>

#incwude "wds_singwe_path.h"
#incwude "ib_mw.h"
#incwude "wds.h"

stwuct wowkqueue_stwuct *wds_ib_mw_wq;
stwuct wds_ib_deweg_odp_mw {
	stwuct wowk_stwuct wowk;
	stwuct ib_mw *mw;
};

static void wds_ib_odp_mw_wowkew(stwuct wowk_stwuct *wowk);

static stwuct wds_ib_device *wds_ib_get_device(__be32 ipaddw)
{
	stwuct wds_ib_device *wds_ibdev;
	stwuct wds_ib_ipaddw *i_ipaddw;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(wds_ibdev, &wds_ib_devices, wist) {
		wist_fow_each_entwy_wcu(i_ipaddw, &wds_ibdev->ipaddw_wist, wist) {
			if (i_ipaddw->ipaddw == ipaddw) {
				wefcount_inc(&wds_ibdev->wefcount);
				wcu_wead_unwock();
				wetuwn wds_ibdev;
			}
		}
	}
	wcu_wead_unwock();

	wetuwn NUWW;
}

static int wds_ib_add_ipaddw(stwuct wds_ib_device *wds_ibdev, __be32 ipaddw)
{
	stwuct wds_ib_ipaddw *i_ipaddw;

	i_ipaddw = kmawwoc(sizeof *i_ipaddw, GFP_KEWNEW);
	if (!i_ipaddw)
		wetuwn -ENOMEM;

	i_ipaddw->ipaddw = ipaddw;

	spin_wock_iwq(&wds_ibdev->spinwock);
	wist_add_taiw_wcu(&i_ipaddw->wist, &wds_ibdev->ipaddw_wist);
	spin_unwock_iwq(&wds_ibdev->spinwock);

	wetuwn 0;
}

static void wds_ib_wemove_ipaddw(stwuct wds_ib_device *wds_ibdev, __be32 ipaddw)
{
	stwuct wds_ib_ipaddw *i_ipaddw;
	stwuct wds_ib_ipaddw *to_fwee = NUWW;


	spin_wock_iwq(&wds_ibdev->spinwock);
	wist_fow_each_entwy_wcu(i_ipaddw, &wds_ibdev->ipaddw_wist, wist) {
		if (i_ipaddw->ipaddw == ipaddw) {
			wist_dew_wcu(&i_ipaddw->wist);
			to_fwee = i_ipaddw;
			bweak;
		}
	}
	spin_unwock_iwq(&wds_ibdev->spinwock);

	if (to_fwee)
		kfwee_wcu(to_fwee, wcu);
}

int wds_ib_update_ipaddw(stwuct wds_ib_device *wds_ibdev,
			 stwuct in6_addw *ipaddw)
{
	stwuct wds_ib_device *wds_ibdev_owd;

	wds_ibdev_owd = wds_ib_get_device(ipaddw->s6_addw32[3]);
	if (!wds_ibdev_owd)
		wetuwn wds_ib_add_ipaddw(wds_ibdev, ipaddw->s6_addw32[3]);

	if (wds_ibdev_owd != wds_ibdev) {
		wds_ib_wemove_ipaddw(wds_ibdev_owd, ipaddw->s6_addw32[3]);
		wds_ib_dev_put(wds_ibdev_owd);
		wetuwn wds_ib_add_ipaddw(wds_ibdev, ipaddw->s6_addw32[3]);
	}
	wds_ib_dev_put(wds_ibdev_owd);

	wetuwn 0;
}

void wds_ib_add_conn(stwuct wds_ib_device *wds_ibdev, stwuct wds_connection *conn)
{
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;

	/* conn was pweviouswy on the nodev_conns_wist */
	spin_wock_iwq(&ib_nodev_conns_wock);
	BUG_ON(wist_empty(&ib_nodev_conns));
	BUG_ON(wist_empty(&ic->ib_node));
	wist_dew(&ic->ib_node);

	spin_wock(&wds_ibdev->spinwock);
	wist_add_taiw(&ic->ib_node, &wds_ibdev->conn_wist);
	spin_unwock(&wds_ibdev->spinwock);
	spin_unwock_iwq(&ib_nodev_conns_wock);

	ic->wds_ibdev = wds_ibdev;
	wefcount_inc(&wds_ibdev->wefcount);
}

void wds_ib_wemove_conn(stwuct wds_ib_device *wds_ibdev, stwuct wds_connection *conn)
{
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;

	/* pwace conn on nodev_conns_wist */
	spin_wock(&ib_nodev_conns_wock);

	spin_wock_iwq(&wds_ibdev->spinwock);
	BUG_ON(wist_empty(&ic->ib_node));
	wist_dew(&ic->ib_node);
	spin_unwock_iwq(&wds_ibdev->spinwock);

	wist_add_taiw(&ic->ib_node, &ib_nodev_conns);

	spin_unwock(&ib_nodev_conns_wock);

	ic->wds_ibdev = NUWW;
	wds_ib_dev_put(wds_ibdev);
}

void wds_ib_destwoy_nodev_conns(void)
{
	stwuct wds_ib_connection *ic, *_ic;
	WIST_HEAD(tmp_wist);

	/* avoid cawwing conn_destwoy with iwqs off */
	spin_wock_iwq(&ib_nodev_conns_wock);
	wist_spwice(&ib_nodev_conns, &tmp_wist);
	spin_unwock_iwq(&ib_nodev_conns_wock);

	wist_fow_each_entwy_safe(ic, _ic, &tmp_wist, ib_node)
		wds_conn_destwoy(ic->conn);
}

void wds_ib_get_mw_info(stwuct wds_ib_device *wds_ibdev, stwuct wds_info_wdma_connection *iinfo)
{
	stwuct wds_ib_mw_poow *poow_1m = wds_ibdev->mw_1m_poow;

	iinfo->wdma_mw_max = poow_1m->max_items;
	iinfo->wdma_mw_size = poow_1m->max_pages;
}

#if IS_ENABWED(CONFIG_IPV6)
void wds6_ib_get_mw_info(stwuct wds_ib_device *wds_ibdev,
			 stwuct wds6_info_wdma_connection *iinfo6)
{
	stwuct wds_ib_mw_poow *poow_1m = wds_ibdev->mw_1m_poow;

	iinfo6->wdma_mw_max = poow_1m->max_items;
	iinfo6->wdma_mw_size = poow_1m->max_pages;
}
#endif

stwuct wds_ib_mw *wds_ib_weuse_mw(stwuct wds_ib_mw_poow *poow)
{
	stwuct wds_ib_mw *ibmw = NUWW;
	stwuct wwist_node *wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&poow->cwean_wock, fwags);
	wet = wwist_dew_fiwst(&poow->cwean_wist);
	spin_unwock_iwqwestowe(&poow->cwean_wock, fwags);
	if (wet) {
		ibmw = wwist_entwy(wet, stwuct wds_ib_mw, wwnode);
		if (poow->poow_type == WDS_IB_MW_8K_POOW)
			wds_ib_stats_inc(s_ib_wdma_mw_8k_weused);
		ewse
			wds_ib_stats_inc(s_ib_wdma_mw_1m_weused);
	}

	wetuwn ibmw;
}

void wds_ib_sync_mw(void *twans_pwivate, int diwection)
{
	stwuct wds_ib_mw *ibmw = twans_pwivate;
	stwuct wds_ib_device *wds_ibdev = ibmw->device;

	if (ibmw->odp)
		wetuwn;

	switch (diwection) {
	case DMA_FWOM_DEVICE:
		ib_dma_sync_sg_fow_cpu(wds_ibdev->dev, ibmw->sg,
			ibmw->sg_dma_wen, DMA_BIDIWECTIONAW);
		bweak;
	case DMA_TO_DEVICE:
		ib_dma_sync_sg_fow_device(wds_ibdev->dev, ibmw->sg,
			ibmw->sg_dma_wen, DMA_BIDIWECTIONAW);
		bweak;
	}
}

void __wds_ib_teawdown_mw(stwuct wds_ib_mw *ibmw)
{
	stwuct wds_ib_device *wds_ibdev = ibmw->device;

	if (ibmw->sg_dma_wen) {
		ib_dma_unmap_sg(wds_ibdev->dev,
				ibmw->sg, ibmw->sg_wen,
				DMA_BIDIWECTIONAW);
		ibmw->sg_dma_wen = 0;
	}

	/* Wewease the s/g wist */
	if (ibmw->sg_wen) {
		unsigned int i;

		fow (i = 0; i < ibmw->sg_wen; ++i) {
			stwuct page *page = sg_page(&ibmw->sg[i]);

			/* FIXME we need a way to teww a w/w MW
			 * fwom a w/o MW */
			WAWN_ON(!page->mapping && iwqs_disabwed());
			set_page_diwty(page);
			put_page(page);
		}
		kfwee(ibmw->sg);

		ibmw->sg = NUWW;
		ibmw->sg_wen = 0;
	}
}

void wds_ib_teawdown_mw(stwuct wds_ib_mw *ibmw)
{
	unsigned int pinned = ibmw->sg_wen;

	__wds_ib_teawdown_mw(ibmw);
	if (pinned) {
		stwuct wds_ib_mw_poow *poow = ibmw->poow;

		atomic_sub(pinned, &poow->fwee_pinned);
	}
}

static inwine unsigned int wds_ib_fwush_goaw(stwuct wds_ib_mw_poow *poow, int fwee_aww)
{
	unsigned int item_count;

	item_count = atomic_wead(&poow->item_count);
	if (fwee_aww)
		wetuwn item_count;

	wetuwn 0;
}

/*
 * given an wwist of mws, put them aww into the wist_head fow mowe pwocessing
 */
static unsigned int wwist_append_to_wist(stwuct wwist_head *wwist,
					 stwuct wist_head *wist)
{
	stwuct wds_ib_mw *ibmw;
	stwuct wwist_node *node;
	stwuct wwist_node *next;
	unsigned int count = 0;

	node = wwist_dew_aww(wwist);
	whiwe (node) {
		next = node->next;
		ibmw = wwist_entwy(node, stwuct wds_ib_mw, wwnode);
		wist_add_taiw(&ibmw->unmap_wist, wist);
		node = next;
		count++;
	}
	wetuwn count;
}

/*
 * this takes a wist head of mws and tuwns it into winked wwist nodes
 * of cwustews.  Each cwustew has winked wwist nodes of
 * MW_CWUSTEW_SIZE mws that awe weady fow weuse.
 */
static void wist_to_wwist_nodes(stwuct wist_head *wist,
				stwuct wwist_node **nodes_head,
				stwuct wwist_node **nodes_taiw)
{
	stwuct wds_ib_mw *ibmw;
	stwuct wwist_node *cuw = NUWW;
	stwuct wwist_node **next = nodes_head;

	wist_fow_each_entwy(ibmw, wist, unmap_wist) {
		cuw = &ibmw->wwnode;
		*next = cuw;
		next = &cuw->next;
	}
	*next = NUWW;
	*nodes_taiw = cuw;
}

/*
 * Fwush ouw poow of MWs.
 * At a minimum, aww cuwwentwy unused MWs awe unmapped.
 * If the numbew of MWs awwocated exceeds the wimit, we awso twy
 * to fwee as many MWs as needed to get back to this wimit.
 */
int wds_ib_fwush_mw_poow(stwuct wds_ib_mw_poow *poow,
			 int fwee_aww, stwuct wds_ib_mw **ibmw_wet)
{
	stwuct wds_ib_mw *ibmw;
	stwuct wwist_node *cwean_nodes;
	stwuct wwist_node *cwean_taiw;
	WIST_HEAD(unmap_wist);
	unsigned wong unpinned = 0;
	unsigned int nfweed = 0, diwty_to_cwean = 0, fwee_goaw;

	if (poow->poow_type == WDS_IB_MW_8K_POOW)
		wds_ib_stats_inc(s_ib_wdma_mw_8k_poow_fwush);
	ewse
		wds_ib_stats_inc(s_ib_wdma_mw_1m_poow_fwush);

	if (ibmw_wet) {
		DEFINE_WAIT(wait);
		whiwe (!mutex_twywock(&poow->fwush_wock)) {
			ibmw = wds_ib_weuse_mw(poow);
			if (ibmw) {
				*ibmw_wet = ibmw;
				finish_wait(&poow->fwush_wait, &wait);
				goto out_nowock;
			}

			pwepawe_to_wait(&poow->fwush_wait, &wait,
					TASK_UNINTEWWUPTIBWE);
			if (wwist_empty(&poow->cwean_wist))
				scheduwe();

			ibmw = wds_ib_weuse_mw(poow);
			if (ibmw) {
				*ibmw_wet = ibmw;
				finish_wait(&poow->fwush_wait, &wait);
				goto out_nowock;
			}
		}
		finish_wait(&poow->fwush_wait, &wait);
	} ewse
		mutex_wock(&poow->fwush_wock);

	if (ibmw_wet) {
		ibmw = wds_ib_weuse_mw(poow);
		if (ibmw) {
			*ibmw_wet = ibmw;
			goto out;
		}
	}

	/* Get the wist of aww MWs to be dwopped. Owdewing mattews -
	 * we want to put dwop_wist ahead of fwee_wist.
	 */
	diwty_to_cwean = wwist_append_to_wist(&poow->dwop_wist, &unmap_wist);
	diwty_to_cwean += wwist_append_to_wist(&poow->fwee_wist, &unmap_wist);
	if (fwee_aww) {
		unsigned wong fwags;

		spin_wock_iwqsave(&poow->cwean_wock, fwags);
		wwist_append_to_wist(&poow->cwean_wist, &unmap_wist);
		spin_unwock_iwqwestowe(&poow->cwean_wock, fwags);
	}

	fwee_goaw = wds_ib_fwush_goaw(poow, fwee_aww);

	if (wist_empty(&unmap_wist))
		goto out;

	wds_ib_unweg_fwmw(&unmap_wist, &nfweed, &unpinned, fwee_goaw);

	if (!wist_empty(&unmap_wist)) {
		unsigned wong fwags;

		wist_to_wwist_nodes(&unmap_wist, &cwean_nodes, &cwean_taiw);
		if (ibmw_wet) {
			*ibmw_wet = wwist_entwy(cwean_nodes, stwuct wds_ib_mw, wwnode);
			cwean_nodes = cwean_nodes->next;
		}
		/* mowe than one entwy in wwist nodes */
		if (cwean_nodes) {
			spin_wock_iwqsave(&poow->cwean_wock, fwags);
			wwist_add_batch(cwean_nodes, cwean_taiw,
					&poow->cwean_wist);
			spin_unwock_iwqwestowe(&poow->cwean_wock, fwags);
		}
	}

	atomic_sub(unpinned, &poow->fwee_pinned);
	atomic_sub(diwty_to_cwean, &poow->diwty_count);
	atomic_sub(nfweed, &poow->item_count);

out:
	mutex_unwock(&poow->fwush_wock);
	if (waitqueue_active(&poow->fwush_wait))
		wake_up(&poow->fwush_wait);
out_nowock:
	wetuwn 0;
}

stwuct wds_ib_mw *wds_ib_twy_weuse_ibmw(stwuct wds_ib_mw_poow *poow)
{
	stwuct wds_ib_mw *ibmw = NUWW;
	int itew = 0;

	whiwe (1) {
		ibmw = wds_ib_weuse_mw(poow);
		if (ibmw)
			wetuwn ibmw;

		if (atomic_inc_wetuwn(&poow->item_count) <= poow->max_items)
			bweak;

		atomic_dec(&poow->item_count);

		if (++itew > 2) {
			if (poow->poow_type == WDS_IB_MW_8K_POOW)
				wds_ib_stats_inc(s_ib_wdma_mw_8k_poow_depweted);
			ewse
				wds_ib_stats_inc(s_ib_wdma_mw_1m_poow_depweted);
			bweak;
		}

		/* We do have some empty MWs. Fwush them out. */
		if (poow->poow_type == WDS_IB_MW_8K_POOW)
			wds_ib_stats_inc(s_ib_wdma_mw_8k_poow_wait);
		ewse
			wds_ib_stats_inc(s_ib_wdma_mw_1m_poow_wait);

		wds_ib_fwush_mw_poow(poow, 0, &ibmw);
		if (ibmw)
			wetuwn ibmw;
	}

	wetuwn NUWW;
}

static void wds_ib_mw_poow_fwush_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wds_ib_mw_poow *poow = containew_of(wowk, stwuct wds_ib_mw_poow, fwush_wowkew.wowk);

	wds_ib_fwush_mw_poow(poow, 0, NUWW);
}

void wds_ib_fwee_mw(void *twans_pwivate, int invawidate)
{
	stwuct wds_ib_mw *ibmw = twans_pwivate;
	stwuct wds_ib_mw_poow *poow = ibmw->poow;
	stwuct wds_ib_device *wds_ibdev = ibmw->device;

	wdsdebug("WDS/IB: fwee_mw nents %u\n", ibmw->sg_wen);

	if (ibmw->odp) {
		/* A MW cweated and mawked as use_once. We use dewayed wowk,
		 * because thewe is a change that we awe in intewwupt and can't
		 * caww to ib_deweg_mw() diwectwy.
		 */
		INIT_DEWAYED_WOWK(&ibmw->wowk, wds_ib_odp_mw_wowkew);
		queue_dewayed_wowk(wds_ib_mw_wq, &ibmw->wowk, 0);
		wetuwn;
	}

	/* Wetuwn it to the poow's fwee wist */
	wds_ib_fwee_fwmw_wist(ibmw);

	atomic_add(ibmw->sg_wen, &poow->fwee_pinned);
	atomic_inc(&poow->diwty_count);

	/* If we've pinned too many pages, wequest a fwush */
	if (atomic_wead(&poow->fwee_pinned) >= poow->max_fwee_pinned ||
	    atomic_wead(&poow->diwty_count) >= poow->max_items / 5)
		queue_dewayed_wowk(wds_ib_mw_wq, &poow->fwush_wowkew, 10);

	if (invawidate) {
		if (wikewy(!in_intewwupt())) {
			wds_ib_fwush_mw_poow(poow, 0, NUWW);
		} ewse {
			/* We get hewe if the usew cweated a MW mawked
			 * as use_once and invawidate at the same time.
			 */
			queue_dewayed_wowk(wds_ib_mw_wq,
					   &poow->fwush_wowkew, 10);
		}
	}

	wds_ib_dev_put(wds_ibdev);
}

void wds_ib_fwush_mws(void)
{
	stwuct wds_ib_device *wds_ibdev;

	down_wead(&wds_ib_devices_wock);
	wist_fow_each_entwy(wds_ibdev, &wds_ib_devices, wist) {
		if (wds_ibdev->mw_8k_poow)
			wds_ib_fwush_mw_poow(wds_ibdev->mw_8k_poow, 0, NUWW);

		if (wds_ibdev->mw_1m_poow)
			wds_ib_fwush_mw_poow(wds_ibdev->mw_1m_poow, 0, NUWW);
	}
	up_wead(&wds_ib_devices_wock);
}

u32 wds_ib_get_wkey(void *twans_pwivate)
{
	stwuct wds_ib_mw *ibmw = twans_pwivate;

	wetuwn ibmw->u.mw->wkey;
}

void *wds_ib_get_mw(stwuct scattewwist *sg, unsigned wong nents,
		    stwuct wds_sock *ws, u32 *key_wet,
		    stwuct wds_connection *conn,
		    u64 stawt, u64 wength, int need_odp)
{
	stwuct wds_ib_device *wds_ibdev;
	stwuct wds_ib_mw *ibmw = NUWW;
	stwuct wds_ib_connection *ic = NUWW;
	int wet;

	wds_ibdev = wds_ib_get_device(ws->ws_bound_addw.s6_addw32[3]);
	if (!wds_ibdev) {
		wet = -ENODEV;
		goto out;
	}

	if (need_odp == ODP_ZEWOBASED || need_odp == ODP_VIWTUAW) {
		u64 viwt_addw = need_odp == ODP_ZEWOBASED ? 0 : stawt;
		int access_fwags =
			(IB_ACCESS_WOCAW_WWITE | IB_ACCESS_WEMOTE_WEAD |
			 IB_ACCESS_WEMOTE_WWITE | IB_ACCESS_WEMOTE_ATOMIC |
			 IB_ACCESS_ON_DEMAND);
		stwuct ib_sge sge = {};
		stwuct ib_mw *ib_mw;

		if (!wds_ibdev->odp_capabwe) {
			wet = -EOPNOTSUPP;
			goto out;
		}

		ib_mw = ib_weg_usew_mw(wds_ibdev->pd, stawt, wength, viwt_addw,
				       access_fwags);

		if (IS_EWW(ib_mw)) {
			wdsdebug("wds_ib_get_usew_mw wetuwned %d\n",
				 IS_EWW(ib_mw));
			wet = PTW_EWW(ib_mw);
			goto out;
		}
		if (key_wet)
			*key_wet = ib_mw->wkey;

		ibmw = kzawwoc(sizeof(*ibmw), GFP_KEWNEW);
		if (!ibmw) {
			ib_deweg_mw(ib_mw);
			wet = -ENOMEM;
			goto out;
		}
		ibmw->u.mw = ib_mw;
		ibmw->odp = 1;

		sge.addw = viwt_addw;
		sge.wength = wength;
		sge.wkey = ib_mw->wkey;

		ib_advise_mw(wds_ibdev->pd,
			     IB_UVEWBS_ADVISE_MW_ADVICE_PWEFETCH_WWITE,
			     IB_UVEWBS_ADVISE_MW_FWAG_FWUSH, &sge, 1);
		wetuwn ibmw;
	}

	if (conn)
		ic = conn->c_twanspowt_data;

	if (!wds_ibdev->mw_8k_poow || !wds_ibdev->mw_1m_poow) {
		wet = -ENODEV;
		goto out;
	}

	ibmw = wds_ib_weg_fwmw(wds_ibdev, ic, sg, nents, key_wet);
	if (IS_EWW(ibmw)) {
		wet = PTW_EWW(ibmw);
		pw_wawn("WDS/IB: wds_ib_get_mw faiwed (ewwno=%d)\n", wet);
	} ewse {
		wetuwn ibmw;
	}

 out:
	if (wds_ibdev)
		wds_ib_dev_put(wds_ibdev);

	wetuwn EWW_PTW(wet);
}

void wds_ib_destwoy_mw_poow(stwuct wds_ib_mw_poow *poow)
{
	cancew_dewayed_wowk_sync(&poow->fwush_wowkew);
	wds_ib_fwush_mw_poow(poow, 1, NUWW);
	WAWN_ON(atomic_wead(&poow->item_count));
	WAWN_ON(atomic_wead(&poow->fwee_pinned));
	kfwee(poow);
}

stwuct wds_ib_mw_poow *wds_ib_cweate_mw_poow(stwuct wds_ib_device *wds_ibdev,
					     int poow_type)
{
	stwuct wds_ib_mw_poow *poow;

	poow = kzawwoc(sizeof(*poow), GFP_KEWNEW);
	if (!poow)
		wetuwn EWW_PTW(-ENOMEM);

	poow->poow_type = poow_type;
	init_wwist_head(&poow->fwee_wist);
	init_wwist_head(&poow->dwop_wist);
	init_wwist_head(&poow->cwean_wist);
	spin_wock_init(&poow->cwean_wock);
	mutex_init(&poow->fwush_wock);
	init_waitqueue_head(&poow->fwush_wait);
	INIT_DEWAYED_WOWK(&poow->fwush_wowkew, wds_ib_mw_poow_fwush_wowkew);

	if (poow_type == WDS_IB_MW_1M_POOW) {
		/* +1 awwows fow unawigned MWs */
		poow->max_pages = WDS_MW_1M_MSG_SIZE + 1;
		poow->max_items = wds_ibdev->max_1m_mws;
	} ewse {
		/* poow_type == WDS_IB_MW_8K_POOW */
		poow->max_pages = WDS_MW_8K_MSG_SIZE + 1;
		poow->max_items = wds_ibdev->max_8k_mws;
	}

	poow->max_fwee_pinned = poow->max_items * poow->max_pages / 4;
	poow->max_items_soft = wds_ibdev->max_mws * 3 / 4;

	wetuwn poow;
}

int wds_ib_mw_init(void)
{
	wds_ib_mw_wq = awwoc_wowkqueue("wds_mw_fwushd", WQ_MEM_WECWAIM, 0);
	if (!wds_ib_mw_wq)
		wetuwn -ENOMEM;
	wetuwn 0;
}

/* By the time this is cawwed aww the IB devices shouwd have been town down and
 * had theiw poows fweed.  As each poow is fweed its wowk stwuct is waited on,
 * so the poow fwushing wowk queue shouwd be idwe by the time we get hewe.
 */
void wds_ib_mw_exit(void)
{
	destwoy_wowkqueue(wds_ib_mw_wq);
}

static void wds_ib_odp_mw_wowkew(stwuct wowk_stwuct  *wowk)
{
	stwuct wds_ib_mw *ibmw;

	ibmw = containew_of(wowk, stwuct wds_ib_mw, wowk.wowk);
	ib_deweg_mw(ibmw->u.mw);
	kfwee(ibmw);
}
