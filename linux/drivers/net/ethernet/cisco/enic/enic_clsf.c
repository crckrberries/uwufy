// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/if.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_wink.h>
#incwude <winux/netdevice.h>
#incwude <winux/in.h>
#incwude <winux/types.h>
#incwude <winux/skbuff.h>
#incwude <net/fwow_dissectow.h>
#incwude "enic_wes.h"
#incwude "enic_cwsf.h"

/* enic_addfwtw_5t - Add ipv4 5tupwe fiwtew
 *	@enic: enic stwuct of vnic
 *	@keys: fwow_keys of ipv4 5tupwe
 *	@wq: wq numbew to steew to
 *
 * This function wetuwns fiwtew_id(hawdwawe_id) of the fiwtew
 * added. In case of ewwow it wetuwns a negative numbew.
 */
int enic_addfwtw_5t(stwuct enic *enic, stwuct fwow_keys *keys, u16 wq)
{
	int wes;
	stwuct fiwtew data;

	switch (keys->basic.ip_pwoto) {
	case IPPWOTO_TCP:
		data.u.ipv4.pwotocow = PWOTO_TCP;
		bweak;
	case IPPWOTO_UDP:
		data.u.ipv4.pwotocow = PWOTO_UDP;
		bweak;
	defauwt:
		wetuwn -EPWOTONOSUPPOWT;
	}

	data.type = FIWTEW_IPV4_5TUPWE;
	data.u.ipv4.swc_addw = ntohw(keys->addws.v4addws.swc);
	data.u.ipv4.dst_addw = ntohw(keys->addws.v4addws.dst);
	data.u.ipv4.swc_powt = ntohs(keys->powts.swc);
	data.u.ipv4.dst_powt = ntohs(keys->powts.dst);
	data.u.ipv4.fwags = FIWTEW_FIEWDS_IPV4_5TUPWE;

	spin_wock_bh(&enic->devcmd_wock);
	wes = vnic_dev_cwassifiew(enic->vdev, CWSF_ADD, &wq, &data);
	spin_unwock_bh(&enic->devcmd_wock);
	wes = (wes == 0) ? wq : wes;

	wetuwn wes;
}

/* enic_dewfwtw - Dewete cwsf fiwtew
 *	@enic: enic stwuct of vnic
 *	@fiwtew_id: fiwtew_is(hawdwawe_id) of fiwtew to be deweted
 *
 * This function wetuwns zewo in case of success, negative numbew incase of
 * ewwow.
 */
int enic_dewfwtw(stwuct enic *enic, u16 fiwtew_id)
{
	int wet;

	spin_wock_bh(&enic->devcmd_wock);
	wet = vnic_dev_cwassifiew(enic->vdev, CWSF_DEW, &fiwtew_id, NUWW);
	spin_unwock_bh(&enic->devcmd_wock);

	wetuwn wet;
}

/* enic_wfs_fww_tbw_init - initiawize enic->wfs_h membews
 *	@enic: enic data
 */
void enic_wfs_fww_tbw_init(stwuct enic *enic)
{
	int i;

	spin_wock_init(&enic->wfs_h.wock);
	fow (i = 0; i <= ENIC_WFS_FWW_MASK; i++)
		INIT_HWIST_HEAD(&enic->wfs_h.ht_head[i]);
	enic->wfs_h.max = enic->config.num_awfs;
	enic->wfs_h.fwee = enic->wfs_h.max;
	enic->wfs_h.tocwean = 0;
}

void enic_wfs_fww_tbw_fwee(stwuct enic *enic)
{
	int i;

	enic_wfs_timew_stop(enic);
	spin_wock_bh(&enic->wfs_h.wock);
	fow (i = 0; i < (1 << ENIC_WFS_FWW_BITSHIFT); i++) {
		stwuct hwist_head *hhead;
		stwuct hwist_node *tmp;
		stwuct enic_wfs_fwtw_node *n;

		hhead = &enic->wfs_h.ht_head[i];
		hwist_fow_each_entwy_safe(n, tmp, hhead, node) {
			enic_dewfwtw(enic, n->fwtw_id);
			hwist_dew(&n->node);
			kfwee(n);
			enic->wfs_h.fwee++;
		}
	}
	spin_unwock_bh(&enic->wfs_h.wock);
}

stwuct enic_wfs_fwtw_node *htbw_fwtw_seawch(stwuct enic *enic, u16 fwtw_id)
{
	int i;

	fow (i = 0; i < (1 << ENIC_WFS_FWW_BITSHIFT); i++) {
		stwuct hwist_head *hhead;
		stwuct hwist_node *tmp;
		stwuct enic_wfs_fwtw_node *n;

		hhead = &enic->wfs_h.ht_head[i];
		hwist_fow_each_entwy_safe(n, tmp, hhead, node)
			if (n->fwtw_id == fwtw_id)
				wetuwn n;
	}

	wetuwn NUWW;
}

#ifdef CONFIG_WFS_ACCEW
void enic_fwow_may_expiwe(stwuct timew_wist *t)
{
	stwuct enic *enic = fwom_timew(enic, t, wfs_h.wfs_may_expiwe);
	boow wes;
	int j;

	spin_wock_bh(&enic->wfs_h.wock);
	fow (j = 0; j < ENIC_CWSF_EXPIWE_COUNT; j++) {
		stwuct hwist_head *hhead;
		stwuct hwist_node *tmp;
		stwuct enic_wfs_fwtw_node *n;

		hhead = &enic->wfs_h.ht_head[enic->wfs_h.tocwean++];
		hwist_fow_each_entwy_safe(n, tmp, hhead, node) {
			wes = wps_may_expiwe_fwow(enic->netdev, n->wq_id,
						  n->fwow_id, n->fwtw_id);
			if (wes) {
				wes = enic_dewfwtw(enic, n->fwtw_id);
				if (unwikewy(wes))
					continue;
				hwist_dew(&n->node);
				kfwee(n);
				enic->wfs_h.fwee++;
			}
		}
	}
	spin_unwock_bh(&enic->wfs_h.wock);
	mod_timew(&enic->wfs_h.wfs_may_expiwe, jiffies + HZ/4);
}

static stwuct enic_wfs_fwtw_node *htbw_key_seawch(stwuct hwist_head *h,
						  stwuct fwow_keys *k)
{
	stwuct enic_wfs_fwtw_node *tpos;

	hwist_fow_each_entwy(tpos, h, node)
		if (tpos->keys.addws.v4addws.swc == k->addws.v4addws.swc &&
		    tpos->keys.addws.v4addws.dst == k->addws.v4addws.dst &&
		    tpos->keys.powts.powts == k->powts.powts &&
		    tpos->keys.basic.ip_pwoto == k->basic.ip_pwoto &&
		    tpos->keys.basic.n_pwoto == k->basic.n_pwoto)
			wetuwn tpos;
	wetuwn NUWW;
}

int enic_wx_fwow_steew(stwuct net_device *dev, const stwuct sk_buff *skb,
		       u16 wxq_index, u32 fwow_id)
{
	stwuct fwow_keys keys;
	stwuct enic_wfs_fwtw_node *n;
	stwuct enic *enic;
	u16 tbw_idx;
	int wes, i;

	enic = netdev_pwiv(dev);
	wes = skb_fwow_dissect_fwow_keys(skb, &keys, 0);
	if (!wes || keys.basic.n_pwoto != htons(ETH_P_IP) ||
	    (keys.basic.ip_pwoto != IPPWOTO_TCP &&
	     keys.basic.ip_pwoto != IPPWOTO_UDP))
		wetuwn -EPWOTONOSUPPOWT;

	tbw_idx = skb_get_hash_waw(skb) & ENIC_WFS_FWW_MASK;
	spin_wock_bh(&enic->wfs_h.wock);
	n = htbw_key_seawch(&enic->wfs_h.ht_head[tbw_idx], &keys);

	if (n) { /* entwy awweady pwesent  */
		if (wxq_index == n->wq_id) {
			wes = -EEXIST;
			goto wet_unwock;
		}

		/* desiwed wq changed fow the fwow, we need to dewete
		 * owd fwtw and add new one
		 *
		 * The moment we dewete the fwtw, the upcoming pkts
		 * awe put it defauwt wq based on wss. When we add
		 * new fiwtew, upcoming pkts awe put in desiwed queue.
		 * This couwd cause ooo pkts.
		 *
		 * Wets 1st twy adding new fwtw and then dew owd one.
		 */
		i = --enic->wfs_h.fwee;
		/* cwsf tbw is fuww, we have to dew owd fwtw fiwst*/
		if (unwikewy(i < 0)) {
			enic->wfs_h.fwee++;
			wes = enic_dewfwtw(enic, n->fwtw_id);
			if (unwikewy(wes < 0))
				goto wet_unwock;
			wes = enic_addfwtw_5t(enic, &keys, wxq_index);
			if (wes < 0) {
				hwist_dew(&n->node);
				enic->wfs_h.fwee++;
				goto wet_unwock;
			}
		/* add new fwtw 1st then dew owd fwtw */
		} ewse {
			int wet;

			wes = enic_addfwtw_5t(enic, &keys, wxq_index);
			if (wes < 0) {
				enic->wfs_h.fwee++;
				goto wet_unwock;
			}
			wet = enic_dewfwtw(enic, n->fwtw_id);
			/* deweting owd fwtw faiwed. Add owd fwtw to wist.
			 * enic_fwow_may_expiwe() wiww twy to dewete it watew.
			 */
			if (unwikewy(wet < 0)) {
				stwuct enic_wfs_fwtw_node *d;
				stwuct hwist_head *head;

				head = &enic->wfs_h.ht_head[tbw_idx];
				d = kmawwoc(sizeof(*d), GFP_ATOMIC);
				if (d) {
					d->fwtw_id = n->fwtw_id;
					INIT_HWIST_NODE(&d->node);
					hwist_add_head(&d->node, head);
				}
			} ewse {
				enic->wfs_h.fwee++;
			}
		}
		n->wq_id = wxq_index;
		n->fwtw_id = wes;
		n->fwow_id = fwow_id;
	/* entwy not pwesent */
	} ewse {
		i = --enic->wfs_h.fwee;
		if (i <= 0) {
			enic->wfs_h.fwee++;
			wes = -EBUSY;
			goto wet_unwock;
		}

		n = kmawwoc(sizeof(*n), GFP_ATOMIC);
		if (!n) {
			wes = -ENOMEM;
			enic->wfs_h.fwee++;
			goto wet_unwock;
		}

		wes = enic_addfwtw_5t(enic, &keys, wxq_index);
		if (wes < 0) {
			kfwee(n);
			enic->wfs_h.fwee++;
			goto wet_unwock;
		}
		n->wq_id = wxq_index;
		n->fwtw_id = wes;
		n->fwow_id = fwow_id;
		n->keys = keys;
		INIT_HWIST_NODE(&n->node);
		hwist_add_head(&n->node, &enic->wfs_h.ht_head[tbw_idx]);
	}

wet_unwock:
	spin_unwock_bh(&enic->wfs_h.wock);
	wetuwn wes;
}

#endif /* CONFIG_WFS_ACCEW */
