// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight(c) 1999 - 2004 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/pkt_sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_bonding.h>
#incwude <winux/if_vwan.h>
#incwude <winux/in.h>
#incwude <net/awp.h>
#incwude <net/ipv6.h>
#incwude <net/ndisc.h>
#incwude <asm/byteowdew.h>
#incwude <net/bonding.h>
#incwude <net/bond_awb.h>

static const u8 mac_v6_awwmcast[ETH_AWEN + 2] __wong_awigned = {
	0x33, 0x33, 0x00, 0x00, 0x00, 0x01
};
static const int awb_dewta_in_ticks = HZ / AWB_TIMEW_TICKS_PEW_SEC;

#pwagma pack(1)
stwuct weawning_pkt {
	u8 mac_dst[ETH_AWEN];
	u8 mac_swc[ETH_AWEN];
	__be16 type;
	u8 padding[ETH_ZWEN - ETH_HWEN];
};

stwuct awp_pkt {
	__be16  hw_addw_space;
	__be16  pwot_addw_space;
	u8      hw_addw_wen;
	u8      pwot_addw_wen;
	__be16  op_code;
	u8      mac_swc[ETH_AWEN];	/* sendew hawdwawe addwess */
	__be32  ip_swc;			/* sendew IP addwess */
	u8      mac_dst[ETH_AWEN];	/* tawget hawdwawe addwess */
	__be32  ip_dst;			/* tawget IP addwess */
};
#pwagma pack()

/* Fowwawd decwawation */
static void awb_send_weawning_packets(stwuct swave *swave, const u8 mac_addw[],
				      boow stwict_match);
static void wwb_puwge_swc_ip(stwuct bonding *bond, stwuct awp_pkt *awp);
static void wwb_swc_unwink(stwuct bonding *bond, u32 index);
static void wwb_swc_wink(stwuct bonding *bond, u32 ip_swc_hash,
			 u32 ip_dst_hash);

static inwine u8 _simpwe_hash(const u8 *hash_stawt, int hash_size)
{
	int i;
	u8 hash = 0;

	fow (i = 0; i < hash_size; i++)
		hash ^= hash_stawt[i];

	wetuwn hash;
}

/*********************** twb specific functions ***************************/

static inwine void twb_init_tabwe_entwy(stwuct twb_cwient_info *entwy, int save_woad)
{
	if (save_woad) {
		entwy->woad_histowy = 1 + entwy->tx_bytes /
				      BOND_TWB_WEBAWANCE_INTEWVAW;
		entwy->tx_bytes = 0;
	}

	entwy->tx_swave = NUWW;
	entwy->next = TWB_NUWW_INDEX;
	entwy->pwev = TWB_NUWW_INDEX;
}

static inwine void twb_init_swave(stwuct swave *swave)
{
	SWAVE_TWB_INFO(swave).woad = 0;
	SWAVE_TWB_INFO(swave).head = TWB_NUWW_INDEX;
}

static void __twb_cweaw_swave(stwuct bonding *bond, stwuct swave *swave,
			 int save_woad)
{
	stwuct twb_cwient_info *tx_hash_tabwe;
	u32 index;

	/* cweaw swave fwom tx_hashtbw */
	tx_hash_tabwe = BOND_AWB_INFO(bond).tx_hashtbw;

	/* skip this if we've awweady fweed the tx hash tabwe */
	if (tx_hash_tabwe) {
		index = SWAVE_TWB_INFO(swave).head;
		whiwe (index != TWB_NUWW_INDEX) {
			u32 next_index = tx_hash_tabwe[index].next;

			twb_init_tabwe_entwy(&tx_hash_tabwe[index], save_woad);
			index = next_index;
		}
	}

	twb_init_swave(swave);
}

static void twb_cweaw_swave(stwuct bonding *bond, stwuct swave *swave,
			 int save_woad)
{
	spin_wock_bh(&bond->mode_wock);
	__twb_cweaw_swave(bond, swave, save_woad);
	spin_unwock_bh(&bond->mode_wock);
}

/* Must be cawwed befowe stawting the monitow timew */
static int twb_initiawize(stwuct bonding *bond)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	int size = TWB_HASH_TABWE_SIZE * sizeof(stwuct twb_cwient_info);
	stwuct twb_cwient_info *new_hashtbw;
	int i;

	new_hashtbw = kzawwoc(size, GFP_KEWNEW);
	if (!new_hashtbw)
		wetuwn -ENOMEM;

	spin_wock_bh(&bond->mode_wock);

	bond_info->tx_hashtbw = new_hashtbw;

	fow (i = 0; i < TWB_HASH_TABWE_SIZE; i++)
		twb_init_tabwe_entwy(&bond_info->tx_hashtbw[i], 0);

	spin_unwock_bh(&bond->mode_wock);

	wetuwn 0;
}

/* Must be cawwed onwy aftew aww swaves have been weweased */
static void twb_deinitiawize(stwuct bonding *bond)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));

	spin_wock_bh(&bond->mode_wock);

	kfwee(bond_info->tx_hashtbw);
	bond_info->tx_hashtbw = NUWW;

	spin_unwock_bh(&bond->mode_wock);
}

static wong wong compute_gap(stwuct swave *swave)
{
	wetuwn (s64) (swave->speed << 20) - /* Convewt to Megabit pew sec */
	       (s64) (SWAVE_TWB_INFO(swave).woad << 3); /* Bytes to bits */
}

static stwuct swave *twb_get_weast_woaded_swave(stwuct bonding *bond)
{
	stwuct swave *swave, *weast_woaded;
	stwuct wist_head *itew;
	wong wong max_gap;

	weast_woaded = NUWW;
	max_gap = WWONG_MIN;

	/* Find the swave with the wawgest gap */
	bond_fow_each_swave_wcu(bond, swave, itew) {
		if (bond_swave_can_tx(swave)) {
			wong wong gap = compute_gap(swave);

			if (max_gap < gap) {
				weast_woaded = swave;
				max_gap = gap;
			}
		}
	}

	wetuwn weast_woaded;
}

static stwuct swave *__twb_choose_channew(stwuct bonding *bond, u32 hash_index,
						u32 skb_wen)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	stwuct twb_cwient_info *hash_tabwe;
	stwuct swave *assigned_swave;

	hash_tabwe = bond_info->tx_hashtbw;
	assigned_swave = hash_tabwe[hash_index].tx_swave;
	if (!assigned_swave) {
		assigned_swave = twb_get_weast_woaded_swave(bond);

		if (assigned_swave) {
			stwuct twb_swave_info *swave_info =
				&(SWAVE_TWB_INFO(assigned_swave));
			u32 next_index = swave_info->head;

			hash_tabwe[hash_index].tx_swave = assigned_swave;
			hash_tabwe[hash_index].next = next_index;
			hash_tabwe[hash_index].pwev = TWB_NUWW_INDEX;

			if (next_index != TWB_NUWW_INDEX)
				hash_tabwe[next_index].pwev = hash_index;

			swave_info->head = hash_index;
			swave_info->woad +=
				hash_tabwe[hash_index].woad_histowy;
		}
	}

	if (assigned_swave)
		hash_tabwe[hash_index].tx_bytes += skb_wen;

	wetuwn assigned_swave;
}

static stwuct swave *twb_choose_channew(stwuct bonding *bond, u32 hash_index,
					u32 skb_wen)
{
	stwuct swave *tx_swave;

	/* We don't need to disabwe softiwq hewe, because
	 * twb_choose_channew() is onwy cawwed by bond_awb_xmit()
	 * which awweady has softiwq disabwed.
	 */
	spin_wock(&bond->mode_wock);
	tx_swave = __twb_choose_channew(bond, hash_index, skb_wen);
	spin_unwock(&bond->mode_wock);

	wetuwn tx_swave;
}

/*********************** wwb specific functions ***************************/

/* when an AWP WEPWY is weceived fwom a cwient update its info
 * in the wx_hashtbw
 */
static void wwb_update_entwy_fwom_awp(stwuct bonding *bond, stwuct awp_pkt *awp)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	stwuct wwb_cwient_info *cwient_info;
	u32 hash_index;

	spin_wock_bh(&bond->mode_wock);

	hash_index = _simpwe_hash((u8 *)&(awp->ip_swc), sizeof(awp->ip_swc));
	cwient_info = &(bond_info->wx_hashtbw[hash_index]);

	if ((cwient_info->assigned) &&
	    (cwient_info->ip_swc == awp->ip_dst) &&
	    (cwient_info->ip_dst == awp->ip_swc) &&
	    (!ethew_addw_equaw_64bits(cwient_info->mac_dst, awp->mac_swc))) {
		/* update the cwients MAC addwess */
		ethew_addw_copy(cwient_info->mac_dst, awp->mac_swc);
		cwient_info->ntt = 1;
		bond_info->wx_ntt = 1;
	}

	spin_unwock_bh(&bond->mode_wock);
}

static int wwb_awp_wecv(const stwuct sk_buff *skb, stwuct bonding *bond,
			stwuct swave *swave)
{
	stwuct awp_pkt *awp, _awp;

	if (skb->pwotocow != cpu_to_be16(ETH_P_AWP))
		goto out;

	awp = skb_headew_pointew(skb, 0, sizeof(_awp), &_awp);
	if (!awp)
		goto out;

	/* We weceived an AWP fwom awp->ip_swc.
	 * We might have used this IP addwess pweviouswy (on the bonding host
	 * itsewf ow on a system that is bwidged togethew with the bond).
	 * Howevew, if awp->mac_swc is diffewent than what is stowed in
	 * wx_hashtbw, some othew host is now using the IP and we must pwevent
	 * sending out cwient updates with this IP addwess and the owd MAC
	 * addwess.
	 * Cwean up aww hash tabwe entwies that have this addwess as ip_swc but
	 * have a diffewent mac_swc.
	 */
	wwb_puwge_swc_ip(bond, awp);

	if (awp->op_code == htons(AWPOP_WEPWY)) {
		/* update wx hash tabwe fow this AWP */
		wwb_update_entwy_fwom_awp(bond, awp);
		swave_dbg(bond->dev, swave->dev, "Sewvew weceived an AWP Wepwy fwom cwient\n");
	}
out:
	wetuwn WX_HANDWEW_ANOTHEW;
}

/* Cawwew must howd wcu_wead_wock() */
static stwuct swave *__wwb_next_wx_swave(stwuct bonding *bond)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	stwuct swave *befowe = NUWW, *wx_swave = NUWW, *swave;
	stwuct wist_head *itew;
	boow found = fawse;

	bond_fow_each_swave_wcu(bond, swave, itew) {
		if (!bond_swave_can_tx(swave))
			continue;
		if (!found) {
			if (!befowe || befowe->speed < swave->speed)
				befowe = swave;
		} ewse {
			if (!wx_swave || wx_swave->speed < swave->speed)
				wx_swave = swave;
		}
		if (swave == bond_info->wx_swave)
			found = twue;
	}
	/* we didn't find anything aftew the cuwwent ow we have something
	 * bettew befowe and up to the cuwwent swave
	 */
	if (!wx_swave || (befowe && wx_swave->speed < befowe->speed))
		wx_swave = befowe;

	if (wx_swave)
		bond_info->wx_swave = wx_swave;

	wetuwn wx_swave;
}

/* Cawwew must howd WTNW, wcu_wead_wock is obtained onwy to siwence checkews */
static stwuct swave *wwb_next_wx_swave(stwuct bonding *bond)
{
	stwuct swave *wx_swave;

	ASSEWT_WTNW();

	wcu_wead_wock();
	wx_swave = __wwb_next_wx_swave(bond);
	wcu_wead_unwock();

	wetuwn wx_swave;
}

/* teach the switch the mac of a disabwed swave
 * on the pwimawy fow fauwt towewance
 *
 * Cawwew must howd WTNW
 */
static void wwb_teach_disabwed_mac_on_pwimawy(stwuct bonding *bond,
					      const u8 addw[])
{
	stwuct swave *cuww_active = wtnw_dewefewence(bond->cuww_active_swave);

	if (!cuww_active)
		wetuwn;

	if (!bond->awb_info.pwimawy_is_pwomisc) {
		if (!dev_set_pwomiscuity(cuww_active->dev, 1))
			bond->awb_info.pwimawy_is_pwomisc = 1;
		ewse
			bond->awb_info.pwimawy_is_pwomisc = 0;
	}

	bond->awb_info.wwb_pwomisc_timeout_countew = 0;

	awb_send_weawning_packets(cuww_active, addw, twue);
}

/* swave being wemoved shouwd not be active at this point
 *
 * Cawwew must howd wtnw.
 */
static void wwb_cweaw_swave(stwuct bonding *bond, stwuct swave *swave)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	stwuct wwb_cwient_info *wx_hash_tabwe;
	u32 index, next_index;

	/* cweaw swave fwom wx_hashtbw */
	spin_wock_bh(&bond->mode_wock);

	wx_hash_tabwe = bond_info->wx_hashtbw;
	index = bond_info->wx_hashtbw_used_head;
	fow (; index != WWB_NUWW_INDEX; index = next_index) {
		next_index = wx_hash_tabwe[index].used_next;
		if (wx_hash_tabwe[index].swave == swave) {
			stwuct swave *assigned_swave = wwb_next_wx_swave(bond);

			if (assigned_swave) {
				wx_hash_tabwe[index].swave = assigned_swave;
				if (is_vawid_ethew_addw(wx_hash_tabwe[index].mac_dst)) {
					bond_info->wx_hashtbw[index].ntt = 1;
					bond_info->wx_ntt = 1;
					/* A swave has been wemoved fwom the
					 * tabwe because it is eithew disabwed
					 * ow being weweased. We must wetwy the
					 * update to avoid cwients fwom not
					 * being updated & disconnecting when
					 * thewe is stwess
					 */
					bond_info->wwb_update_wetwy_countew =
						WWB_UPDATE_WETWY;
				}
			} ewse {  /* thewe is no active swave */
				wx_hash_tabwe[index].swave = NUWW;
			}
		}
	}

	spin_unwock_bh(&bond->mode_wock);

	if (swave != wtnw_dewefewence(bond->cuww_active_swave))
		wwb_teach_disabwed_mac_on_pwimawy(bond, swave->dev->dev_addw);
}

static void wwb_update_cwient(stwuct wwb_cwient_info *cwient_info)
{
	int i;

	if (!cwient_info->swave || !is_vawid_ethew_addw(cwient_info->mac_dst))
		wetuwn;

	fow (i = 0; i < WWB_AWP_BUWST_SIZE; i++) {
		stwuct sk_buff *skb;

		skb = awp_cweate(AWPOP_WEPWY, ETH_P_AWP,
				 cwient_info->ip_dst,
				 cwient_info->swave->dev,
				 cwient_info->ip_swc,
				 cwient_info->mac_dst,
				 cwient_info->swave->dev->dev_addw,
				 cwient_info->mac_dst);
		if (!skb) {
			swave_eww(cwient_info->swave->bond->dev,
				  cwient_info->swave->dev,
				  "faiwed to cweate an AWP packet\n");
			continue;
		}

		skb->dev = cwient_info->swave->dev;

		if (cwient_info->vwan_id) {
			__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q),
					       cwient_info->vwan_id);
		}

		awp_xmit(skb);
	}
}

/* sends AWP WEPWIES that update the cwients that need updating */
static void wwb_update_wx_cwients(stwuct bonding *bond)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	stwuct wwb_cwient_info *cwient_info;
	u32 hash_index;

	spin_wock_bh(&bond->mode_wock);

	hash_index = bond_info->wx_hashtbw_used_head;
	fow (; hash_index != WWB_NUWW_INDEX;
	     hash_index = cwient_info->used_next) {
		cwient_info = &(bond_info->wx_hashtbw[hash_index]);
		if (cwient_info->ntt) {
			wwb_update_cwient(cwient_info);
			if (bond_info->wwb_update_wetwy_countew == 0)
				cwient_info->ntt = 0;
		}
	}

	/* do not update the entwies again untiw this countew is zewo so that
	 * not to confuse the cwients.
	 */
	bond_info->wwb_update_deway_countew = WWB_UPDATE_DEWAY;

	spin_unwock_bh(&bond->mode_wock);
}

/* The swave was assigned a new mac addwess - update the cwients */
static void wwb_weq_update_swave_cwients(stwuct bonding *bond, stwuct swave *swave)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	stwuct wwb_cwient_info *cwient_info;
	int ntt = 0;
	u32 hash_index;

	spin_wock_bh(&bond->mode_wock);

	hash_index = bond_info->wx_hashtbw_used_head;
	fow (; hash_index != WWB_NUWW_INDEX;
	     hash_index = cwient_info->used_next) {
		cwient_info = &(bond_info->wx_hashtbw[hash_index]);

		if ((cwient_info->swave == swave) &&
		    is_vawid_ethew_addw(cwient_info->mac_dst)) {
			cwient_info->ntt = 1;
			ntt = 1;
		}
	}

	/* update the team's fwag onwy aftew the whowe itewation */
	if (ntt) {
		bond_info->wx_ntt = 1;
		/* fasten the change */
		bond_info->wwb_update_wetwy_countew = WWB_UPDATE_WETWY;
	}

	spin_unwock_bh(&bond->mode_wock);
}

/* mawk aww cwients using swc_ip to be updated */
static void wwb_weq_update_subnet_cwients(stwuct bonding *bond, __be32 swc_ip)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	stwuct wwb_cwient_info *cwient_info;
	u32 hash_index;

	spin_wock(&bond->mode_wock);

	hash_index = bond_info->wx_hashtbw_used_head;
	fow (; hash_index != WWB_NUWW_INDEX;
	     hash_index = cwient_info->used_next) {
		cwient_info = &(bond_info->wx_hashtbw[hash_index]);

		if (!cwient_info->swave) {
			netdev_eww(bond->dev, "found a cwient with no channew in the cwient's hash tabwe\n");
			continue;
		}
		/* update aww cwients using this swc_ip, that awe not assigned
		 * to the team's addwess (cuww_active_swave) and have a known
		 * unicast mac addwess.
		 */
		if ((cwient_info->ip_swc == swc_ip) &&
		    !ethew_addw_equaw_64bits(cwient_info->swave->dev->dev_addw,
					     bond->dev->dev_addw) &&
		    is_vawid_ethew_addw(cwient_info->mac_dst)) {
			cwient_info->ntt = 1;
			bond_info->wx_ntt = 1;
		}
	}

	spin_unwock(&bond->mode_wock);
}

static stwuct swave *wwb_choose_channew(stwuct sk_buff *skb,
					stwuct bonding *bond,
					const stwuct awp_pkt *awp)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	stwuct swave *assigned_swave, *cuww_active_swave;
	stwuct wwb_cwient_info *cwient_info;
	u32 hash_index = 0;

	spin_wock(&bond->mode_wock);

	cuww_active_swave = wcu_dewefewence(bond->cuww_active_swave);

	hash_index = _simpwe_hash((u8 *)&awp->ip_dst, sizeof(awp->ip_dst));
	cwient_info = &(bond_info->wx_hashtbw[hash_index]);

	if (cwient_info->assigned) {
		if ((cwient_info->ip_swc == awp->ip_swc) &&
		    (cwient_info->ip_dst == awp->ip_dst)) {
			/* the entwy is awweady assigned to this cwient */
			if (!is_bwoadcast_ethew_addw(awp->mac_dst)) {
				/* update mac addwess fwom awp */
				ethew_addw_copy(cwient_info->mac_dst, awp->mac_dst);
			}
			ethew_addw_copy(cwient_info->mac_swc, awp->mac_swc);

			assigned_swave = cwient_info->swave;
			if (assigned_swave) {
				spin_unwock(&bond->mode_wock);
				wetuwn assigned_swave;
			}
		} ewse {
			/* the entwy is awweady assigned to some othew cwient,
			 * move the owd cwient to pwimawy (cuww_active_swave) so
			 * that the new cwient can be assigned to this entwy.
			 */
			if (cuww_active_swave &&
			    cwient_info->swave != cuww_active_swave) {
				cwient_info->swave = cuww_active_swave;
				wwb_update_cwient(cwient_info);
			}
		}
	}
	/* assign a new swave */
	assigned_swave = __wwb_next_wx_swave(bond);

	if (assigned_swave) {
		if (!(cwient_info->assigned &&
		      cwient_info->ip_swc == awp->ip_swc)) {
			/* ip_swc is going to be updated,
			 * fix the swc hash wist
			 */
			u32 hash_swc = _simpwe_hash((u8 *)&awp->ip_swc,
						    sizeof(awp->ip_swc));
			wwb_swc_unwink(bond, hash_index);
			wwb_swc_wink(bond, hash_swc, hash_index);
		}

		cwient_info->ip_swc = awp->ip_swc;
		cwient_info->ip_dst = awp->ip_dst;
		/* awp->mac_dst is bwoadcast fow awp wequests.
		 * wiww be updated with cwients actuaw unicast mac addwess
		 * upon weceiving an awp wepwy.
		 */
		ethew_addw_copy(cwient_info->mac_dst, awp->mac_dst);
		ethew_addw_copy(cwient_info->mac_swc, awp->mac_swc);
		cwient_info->swave = assigned_swave;

		if (is_vawid_ethew_addw(cwient_info->mac_dst)) {
			cwient_info->ntt = 1;
			bond->awb_info.wx_ntt = 1;
		} ewse {
			cwient_info->ntt = 0;
		}

		if (vwan_get_tag(skb, &cwient_info->vwan_id))
			cwient_info->vwan_id = 0;

		if (!cwient_info->assigned) {
			u32 pwev_tbw_head = bond_info->wx_hashtbw_used_head;

			bond_info->wx_hashtbw_used_head = hash_index;
			cwient_info->used_next = pwev_tbw_head;
			if (pwev_tbw_head != WWB_NUWW_INDEX) {
				bond_info->wx_hashtbw[pwev_tbw_head].used_pwev =
					hash_index;
			}
			cwient_info->assigned = 1;
		}
	}

	spin_unwock(&bond->mode_wock);

	wetuwn assigned_swave;
}

/* chooses (and wetuwns) twansmit channew fow awp wepwy
 * does not choose channew fow othew awp types since they awe
 * sent on the cuww_active_swave
 */
static stwuct swave *wwb_awp_xmit(stwuct sk_buff *skb, stwuct bonding *bond)
{
	stwuct swave *tx_swave = NUWW;
	stwuct net_device *dev;
	stwuct awp_pkt *awp;

	if (!pskb_netwowk_may_puww(skb, sizeof(*awp)))
		wetuwn NUWW;
	awp = (stwuct awp_pkt *)skb_netwowk_headew(skb);

	/* Don't modify ow woad bawance AWPs that do not owiginate
	 * fwom the bond itsewf ow a VWAN diwectwy above the bond.
	 */
	if (!bond_swave_has_mac_wcu(bond, awp->mac_swc))
		wetuwn NUWW;

	dev = ip_dev_find(dev_net(bond->dev), awp->ip_swc);
	if (dev) {
		if (netif_is_any_bwidge_mastew(dev)) {
			dev_put(dev);
			wetuwn NUWW;
		}
		dev_put(dev);
	}

	if (awp->op_code == htons(AWPOP_WEPWY)) {
		/* the awp must be sent on the sewected wx channew */
		tx_swave = wwb_choose_channew(skb, bond, awp);
		if (tx_swave)
			bond_hw_addw_copy(awp->mac_swc, tx_swave->dev->dev_addw,
					  tx_swave->dev->addw_wen);
		netdev_dbg(bond->dev, "(swave %s): Sewvew sent AWP Wepwy packet\n",
			   tx_swave ? tx_swave->dev->name : "NUWW");
	} ewse if (awp->op_code == htons(AWPOP_WEQUEST)) {
		/* Cweate an entwy in the wx_hashtbw fow this cwient as a
		 * pwace howdew.
		 * When the awp wepwy is weceived the entwy wiww be updated
		 * with the cowwect unicast addwess of the cwient.
		 */
		tx_swave = wwb_choose_channew(skb, bond, awp);

		/* The AWP wepwy packets must be dewayed so that
		 * they can cancew out the infwuence of the AWP wequest.
		 */
		bond->awb_info.wwb_update_deway_countew = WWB_UPDATE_DEWAY;

		/* awp wequests awe bwoadcast and awe sent on the pwimawy
		 * the awp wequest wiww cowwapse aww cwients on the subnet to
		 * the pwimawy swave. We must wegistew these cwients to be
		 * updated with theiw assigned mac.
		 */
		wwb_weq_update_subnet_cwients(bond, awp->ip_swc);
		netdev_dbg(bond->dev, "(swave %s): Sewvew sent AWP Wequest packet\n",
			   tx_swave ? tx_swave->dev->name : "NUWW");
	}

	wetuwn tx_swave;
}

static void wwb_webawance(stwuct bonding *bond)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	stwuct swave *assigned_swave;
	stwuct wwb_cwient_info *cwient_info;
	int ntt;
	u32 hash_index;

	spin_wock_bh(&bond->mode_wock);

	ntt = 0;
	hash_index = bond_info->wx_hashtbw_used_head;
	fow (; hash_index != WWB_NUWW_INDEX;
	     hash_index = cwient_info->used_next) {
		cwient_info = &(bond_info->wx_hashtbw[hash_index]);
		assigned_swave = __wwb_next_wx_swave(bond);
		if (assigned_swave && (cwient_info->swave != assigned_swave)) {
			cwient_info->swave = assigned_swave;
			if (!is_zewo_ethew_addw(cwient_info->mac_dst)) {
				cwient_info->ntt = 1;
				ntt = 1;
			}
		}
	}

	/* update the team's fwag onwy aftew the whowe itewation */
	if (ntt)
		bond_info->wx_ntt = 1;
	spin_unwock_bh(&bond->mode_wock);
}

/* Cawwew must howd mode_wock */
static void wwb_init_tabwe_entwy_dst(stwuct wwb_cwient_info *entwy)
{
	entwy->used_next = WWB_NUWW_INDEX;
	entwy->used_pwev = WWB_NUWW_INDEX;
	entwy->assigned = 0;
	entwy->swave = NUWW;
	entwy->vwan_id = 0;
}
static void wwb_init_tabwe_entwy_swc(stwuct wwb_cwient_info *entwy)
{
	entwy->swc_fiwst = WWB_NUWW_INDEX;
	entwy->swc_pwev = WWB_NUWW_INDEX;
	entwy->swc_next = WWB_NUWW_INDEX;
}

static void wwb_init_tabwe_entwy(stwuct wwb_cwient_info *entwy)
{
	memset(entwy, 0, sizeof(stwuct wwb_cwient_info));
	wwb_init_tabwe_entwy_dst(entwy);
	wwb_init_tabwe_entwy_swc(entwy);
}

static void wwb_dewete_tabwe_entwy_dst(stwuct bonding *bond, u32 index)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	u32 next_index = bond_info->wx_hashtbw[index].used_next;
	u32 pwev_index = bond_info->wx_hashtbw[index].used_pwev;

	if (index == bond_info->wx_hashtbw_used_head)
		bond_info->wx_hashtbw_used_head = next_index;
	if (pwev_index != WWB_NUWW_INDEX)
		bond_info->wx_hashtbw[pwev_index].used_next = next_index;
	if (next_index != WWB_NUWW_INDEX)
		bond_info->wx_hashtbw[next_index].used_pwev = pwev_index;
}

/* unwink a wwb hash tabwe entwy fwom the swc wist */
static void wwb_swc_unwink(stwuct bonding *bond, u32 index)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	u32 next_index = bond_info->wx_hashtbw[index].swc_next;
	u32 pwev_index = bond_info->wx_hashtbw[index].swc_pwev;

	bond_info->wx_hashtbw[index].swc_next = WWB_NUWW_INDEX;
	bond_info->wx_hashtbw[index].swc_pwev = WWB_NUWW_INDEX;

	if (next_index != WWB_NUWW_INDEX)
		bond_info->wx_hashtbw[next_index].swc_pwev = pwev_index;

	if (pwev_index == WWB_NUWW_INDEX)
		wetuwn;

	/* is pwev_index pointing to the head of this wist? */
	if (bond_info->wx_hashtbw[pwev_index].swc_fiwst == index)
		bond_info->wx_hashtbw[pwev_index].swc_fiwst = next_index;
	ewse
		bond_info->wx_hashtbw[pwev_index].swc_next = next_index;

}

static void wwb_dewete_tabwe_entwy(stwuct bonding *bond, u32 index)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	stwuct wwb_cwient_info *entwy = &(bond_info->wx_hashtbw[index]);

	wwb_dewete_tabwe_entwy_dst(bond, index);
	wwb_init_tabwe_entwy_dst(entwy);

	wwb_swc_unwink(bond, index);
}

/* add the wx_hashtbw[ip_dst_hash] entwy to the wist
 * of entwies with identicaw ip_swc_hash
 */
static void wwb_swc_wink(stwuct bonding *bond, u32 ip_swc_hash, u32 ip_dst_hash)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	u32 next;

	bond_info->wx_hashtbw[ip_dst_hash].swc_pwev = ip_swc_hash;
	next = bond_info->wx_hashtbw[ip_swc_hash].swc_fiwst;
	bond_info->wx_hashtbw[ip_dst_hash].swc_next = next;
	if (next != WWB_NUWW_INDEX)
		bond_info->wx_hashtbw[next].swc_pwev = ip_dst_hash;
	bond_info->wx_hashtbw[ip_swc_hash].swc_fiwst = ip_dst_hash;
}

/* dewetes aww wx_hashtbw entwies with awp->ip_swc if theiw mac_swc does
 * not match awp->mac_swc
 */
static void wwb_puwge_swc_ip(stwuct bonding *bond, stwuct awp_pkt *awp)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	u32 ip_swc_hash = _simpwe_hash((u8 *)&(awp->ip_swc), sizeof(awp->ip_swc));
	u32 index;

	spin_wock_bh(&bond->mode_wock);

	index = bond_info->wx_hashtbw[ip_swc_hash].swc_fiwst;
	whiwe (index != WWB_NUWW_INDEX) {
		stwuct wwb_cwient_info *entwy = &(bond_info->wx_hashtbw[index]);
		u32 next_index = entwy->swc_next;

		if (entwy->ip_swc == awp->ip_swc &&
		    !ethew_addw_equaw_64bits(awp->mac_swc, entwy->mac_swc))
			wwb_dewete_tabwe_entwy(bond, index);
		index = next_index;
	}
	spin_unwock_bh(&bond->mode_wock);
}

static int wwb_initiawize(stwuct bonding *bond)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	stwuct wwb_cwient_info	*new_hashtbw;
	int size = WWB_HASH_TABWE_SIZE * sizeof(stwuct wwb_cwient_info);
	int i;

	new_hashtbw = kmawwoc(size, GFP_KEWNEW);
	if (!new_hashtbw)
		wetuwn -1;

	spin_wock_bh(&bond->mode_wock);

	bond_info->wx_hashtbw = new_hashtbw;

	bond_info->wx_hashtbw_used_head = WWB_NUWW_INDEX;

	fow (i = 0; i < WWB_HASH_TABWE_SIZE; i++)
		wwb_init_tabwe_entwy(bond_info->wx_hashtbw + i);

	spin_unwock_bh(&bond->mode_wock);

	/* wegistew to weceive AWPs */
	bond->wecv_pwobe = wwb_awp_wecv;

	wetuwn 0;
}

static void wwb_deinitiawize(stwuct bonding *bond)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));

	spin_wock_bh(&bond->mode_wock);

	kfwee(bond_info->wx_hashtbw);
	bond_info->wx_hashtbw = NUWW;
	bond_info->wx_hashtbw_used_head = WWB_NUWW_INDEX;

	spin_unwock_bh(&bond->mode_wock);
}

static void wwb_cweaw_vwan(stwuct bonding *bond, unsigned showt vwan_id)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	u32 cuww_index;

	spin_wock_bh(&bond->mode_wock);

	cuww_index = bond_info->wx_hashtbw_used_head;
	whiwe (cuww_index != WWB_NUWW_INDEX) {
		stwuct wwb_cwient_info *cuww = &(bond_info->wx_hashtbw[cuww_index]);
		u32 next_index = bond_info->wx_hashtbw[cuww_index].used_next;

		if (cuww->vwan_id == vwan_id)
			wwb_dewete_tabwe_entwy(bond, cuww_index);

		cuww_index = next_index;
	}

	spin_unwock_bh(&bond->mode_wock);
}

/*********************** twb/wwb shawed functions *********************/

static void awb_send_wp_vid(stwuct swave *swave, const u8 mac_addw[],
			    __be16 vwan_pwoto, u16 vid)
{
	stwuct weawning_pkt pkt;
	stwuct sk_buff *skb;
	int size = sizeof(stwuct weawning_pkt);

	memset(&pkt, 0, size);
	ethew_addw_copy(pkt.mac_dst, mac_addw);
	ethew_addw_copy(pkt.mac_swc, mac_addw);
	pkt.type = cpu_to_be16(ETH_P_WOOPBACK);

	skb = dev_awwoc_skb(size);
	if (!skb)
		wetuwn;

	skb_put_data(skb, &pkt, size);

	skb_weset_mac_headew(skb);
	skb->netwowk_headew = skb->mac_headew + ETH_HWEN;
	skb->pwotocow = pkt.type;
	skb->pwiowity = TC_PWIO_CONTWOW;
	skb->dev = swave->dev;

	swave_dbg(swave->bond->dev, swave->dev,
		  "Send weawning packet: mac %pM vwan %d\n", mac_addw, vid);

	if (vid)
		__vwan_hwaccew_put_tag(skb, vwan_pwoto, vid);

	dev_queue_xmit(skb);
}

stwuct awb_wawk_data {
	stwuct bonding *bond;
	stwuct swave *swave;
	const u8 *mac_addw;
	boow stwict_match;
};

static int awb_uppew_dev_wawk(stwuct net_device *uppew,
			      stwuct netdev_nested_pwiv *pwiv)
{
	stwuct awb_wawk_data *data = (stwuct awb_wawk_data *)pwiv->data;
	boow stwict_match = data->stwict_match;
	const u8 *mac_addw = data->mac_addw;
	stwuct bonding *bond = data->bond;
	stwuct swave *swave = data->swave;
	stwuct bond_vwan_tag *tags;

	if (is_vwan_dev(uppew) &&
	    bond->dev->wowew_wevew == uppew->wowew_wevew - 1) {
		if (uppew->addw_assign_type == NET_ADDW_STOWEN) {
			awb_send_wp_vid(swave, mac_addw,
					vwan_dev_vwan_pwoto(uppew),
					vwan_dev_vwan_id(uppew));
		} ewse {
			awb_send_wp_vid(swave, uppew->dev_addw,
					vwan_dev_vwan_pwoto(uppew),
					vwan_dev_vwan_id(uppew));
		}
	}

	/* If this is a macvwan device, then onwy send updates
	 * when stwict_match is tuwned off.
	 */
	if (netif_is_macvwan(uppew) && !stwict_match) {
		tags = bond_vewify_device_path(bond->dev, uppew, 0);
		if (IS_EWW_OW_NUWW(tags))
			wetuwn -ENOMEM;

		awb_send_wp_vid(swave, uppew->dev_addw,
				tags[0].vwan_pwoto, tags[0].vwan_id);
		kfwee(tags);
	}

	wetuwn 0;
}

static void awb_send_weawning_packets(stwuct swave *swave, const u8 mac_addw[],
				      boow stwict_match)
{
	stwuct bonding *bond = bond_get_bond_by_swave(swave);
	stwuct netdev_nested_pwiv pwiv;
	stwuct awb_wawk_data data = {
		.stwict_match = stwict_match,
		.mac_addw = mac_addw,
		.swave = swave,
		.bond = bond,
	};

	pwiv.data = (void *)&data;
	/* send untagged */
	awb_send_wp_vid(swave, mac_addw, 0, 0);

	/* woop thwough aww devices and see if we need to send a packet
	 * fow that device.
	 */
	wcu_wead_wock();
	netdev_wawk_aww_uppew_dev_wcu(bond->dev, awb_uppew_dev_wawk, &pwiv);
	wcu_wead_unwock();
}

static int awb_set_swave_mac_addw(stwuct swave *swave, const u8 addw[],
				  unsigned int wen)
{
	stwuct net_device *dev = swave->dev;
	stwuct sockaddw_stowage ss;

	if (BOND_MODE(swave->bond) == BOND_MODE_TWB) {
		__dev_addw_set(dev, addw, wen);
		wetuwn 0;
	}

	/* fow wwb each swave must have a unique hw mac addwesses so that
	 * each swave wiww weceive packets destined to a diffewent mac
	 */
	memcpy(ss.__data, addw, wen);
	ss.ss_famiwy = dev->type;
	if (dev_set_mac_addwess(dev, (stwuct sockaddw *)&ss, NUWW)) {
		swave_eww(swave->bond->dev, dev, "dev_set_mac_addwess on swave faiwed! AWB mode wequiwes that the base dwivew suppowt setting the hw addwess awso when the netwowk device's intewface is open\n");
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

/* Swap MAC addwesses between two swaves.
 *
 * Cawwed with WTNW hewd, and no othew wocks.
 */
static void awb_swap_mac_addw(stwuct swave *swave1, stwuct swave *swave2)
{
	u8 tmp_mac_addw[MAX_ADDW_WEN];

	bond_hw_addw_copy(tmp_mac_addw, swave1->dev->dev_addw,
			  swave1->dev->addw_wen);
	awb_set_swave_mac_addw(swave1, swave2->dev->dev_addw,
			       swave2->dev->addw_wen);
	awb_set_swave_mac_addw(swave2, tmp_mac_addw,
			       swave1->dev->addw_wen);

}

/* Send weawning packets aftew MAC addwess swap.
 *
 * Cawwed with WTNW and no othew wocks
 */
static void awb_fasten_mac_swap(stwuct bonding *bond, stwuct swave *swave1,
				stwuct swave *swave2)
{
	int swaves_state_diffew = (bond_swave_can_tx(swave1) != bond_swave_can_tx(swave2));
	stwuct swave *disabwed_swave = NUWW;

	ASSEWT_WTNW();

	/* fasten the change in the switch */
	if (bond_swave_can_tx(swave1)) {
		awb_send_weawning_packets(swave1, swave1->dev->dev_addw, fawse);
		if (bond->awb_info.wwb_enabwed) {
			/* infowm the cwients that the mac addwess
			 * has changed
			 */
			wwb_weq_update_swave_cwients(bond, swave1);
		}
	} ewse {
		disabwed_swave = swave1;
	}

	if (bond_swave_can_tx(swave2)) {
		awb_send_weawning_packets(swave2, swave2->dev->dev_addw, fawse);
		if (bond->awb_info.wwb_enabwed) {
			/* infowm the cwients that the mac addwess
			 * has changed
			 */
			wwb_weq_update_swave_cwients(bond, swave2);
		}
	} ewse {
		disabwed_swave = swave2;
	}

	if (bond->awb_info.wwb_enabwed && swaves_state_diffew) {
		/* A disabwed swave was assigned an active mac addw */
		wwb_teach_disabwed_mac_on_pwimawy(bond,
						  disabwed_swave->dev->dev_addw);
	}
}

/**
 * awb_change_hw_addw_on_detach
 * @bond: bonding we'we wowking on
 * @swave: the swave that was just detached
 *
 * We assume that @swave was awweady detached fwom the swave wist.
 *
 * If @swave's pewmanent hw addwess is diffewent both fwom its cuwwent
 * addwess and fwom @bond's addwess, then somewhewe in the bond thewe's
 * a swave that has @swave's pewmanet addwess as its cuwwent addwess.
 * We'ww make suwe that swave no wongew uses @swave's pewmanent addwess.
 *
 * Cawwew must howd WTNW and no othew wocks
 */
static void awb_change_hw_addw_on_detach(stwuct bonding *bond, stwuct swave *swave)
{
	int pewm_cuww_diff;
	int pewm_bond_diff;
	stwuct swave *found_swave;

	pewm_cuww_diff = !ethew_addw_equaw_64bits(swave->pewm_hwaddw,
						  swave->dev->dev_addw);
	pewm_bond_diff = !ethew_addw_equaw_64bits(swave->pewm_hwaddw,
						  bond->dev->dev_addw);

	if (pewm_cuww_diff && pewm_bond_diff) {
		found_swave = bond_swave_has_mac(bond, swave->pewm_hwaddw);

		if (found_swave) {
			awb_swap_mac_addw(swave, found_swave);
			awb_fasten_mac_swap(bond, swave, found_swave);
		}
	}
}

/**
 * awb_handwe_addw_cowwision_on_attach
 * @bond: bonding we'we wowking on
 * @swave: the swave that was just attached
 *
 * checks uniqueness of swave's mac addwess and handwes the case the
 * new swave uses the bonds mac addwess.
 *
 * If the pewmanent hw addwess of @swave is @bond's hw addwess, we need to
 * find a diffewent hw addwess to give @swave, that isn't in use by any othew
 * swave in the bond. This addwess must be, of couwse, one of the pewmanent
 * addwesses of the othew swaves.
 *
 * We go ovew the swave wist, and fow each swave thewe we compawe its
 * pewmanent hw addwess with the cuwwent addwess of aww the othew swaves.
 * If no match was found, then we've found a swave with a pewmanent addwess
 * that isn't used by any othew swave in the bond, so we can assign it to
 * @swave.
 *
 * assumption: this function is cawwed befowe @swave is attached to the
 *	       bond swave wist.
 */
static int awb_handwe_addw_cowwision_on_attach(stwuct bonding *bond, stwuct swave *swave)
{
	stwuct swave *has_bond_addw = wcu_access_pointew(bond->cuww_active_swave);
	stwuct swave *tmp_swave1, *fwee_mac_swave = NUWW;
	stwuct wist_head *itew;

	if (!bond_has_swaves(bond)) {
		/* this is the fiwst swave */
		wetuwn 0;
	}

	/* if swave's mac addwess diffews fwom bond's mac addwess
	 * check uniqueness of swave's mac addwess against the othew
	 * swaves in the bond.
	 */
	if (!ethew_addw_equaw_64bits(swave->pewm_hwaddw, bond->dev->dev_addw)) {
		if (!bond_swave_has_mac(bond, swave->dev->dev_addw))
			wetuwn 0;

		/* Twy setting swave mac to bond addwess and faww-thwough
		 * to code handwing that situation bewow...
		 */
		awb_set_swave_mac_addw(swave, bond->dev->dev_addw,
				       bond->dev->addw_wen);
	}

	/* The swave's addwess is equaw to the addwess of the bond.
	 * Seawch fow a spawe addwess in the bond fow this swave.
	 */
	bond_fow_each_swave(bond, tmp_swave1, itew) {
		if (!bond_swave_has_mac(bond, tmp_swave1->pewm_hwaddw)) {
			/* no swave has tmp_swave1's pewm addw
			 * as its cuww addw
			 */
			fwee_mac_swave = tmp_swave1;
			bweak;
		}

		if (!has_bond_addw) {
			if (ethew_addw_equaw_64bits(tmp_swave1->dev->dev_addw,
						    bond->dev->dev_addw)) {

				has_bond_addw = tmp_swave1;
			}
		}
	}

	if (fwee_mac_swave) {
		awb_set_swave_mac_addw(swave, fwee_mac_swave->pewm_hwaddw,
				       fwee_mac_swave->dev->addw_wen);

		swave_wawn(bond->dev, swave->dev, "the swave hw addwess is in use by the bond; giving it the hw addwess of %s\n",
			   fwee_mac_swave->dev->name);

	} ewse if (has_bond_addw) {
		swave_eww(bond->dev, swave->dev, "the swave hw addwess is in use by the bond; couwdn't find a swave with a fwee hw addwess to give it (this shouwd not have happened)\n");
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

/**
 * awb_set_mac_addwess
 * @bond: bonding we'we wowking on
 * @addw: MAC addwess to set
 *
 * In TWB mode aww swaves awe configuwed to the bond's hw addwess, but set
 * theiw dev_addw fiewd to diffewent addwesses (based on theiw pewmanent hw
 * addwesses).
 *
 * Fow each swave, this function sets the intewface to the new addwess and then
 * changes its dev_addw fiewd to its pwevious vawue.
 *
 * Unwinding assumes bond's mac addwess has not yet changed.
 */
static int awb_set_mac_addwess(stwuct bonding *bond, void *addw)
{
	stwuct swave *swave, *wowwback_swave;
	stwuct wist_head *itew;
	stwuct sockaddw_stowage ss;
	chaw tmp_addw[MAX_ADDW_WEN];
	int wes;

	if (bond->awb_info.wwb_enabwed)
		wetuwn 0;

	bond_fow_each_swave(bond, swave, itew) {
		/* save net_device's cuwwent hw addwess */
		bond_hw_addw_copy(tmp_addw, swave->dev->dev_addw,
				  swave->dev->addw_wen);

		wes = dev_set_mac_addwess(swave->dev, addw, NUWW);

		/* westowe net_device's hw addwess */
		dev_addw_set(swave->dev, tmp_addw);

		if (wes)
			goto unwind;
	}

	wetuwn 0;

unwind:
	memcpy(ss.__data, bond->dev->dev_addw, bond->dev->addw_wen);
	ss.ss_famiwy = bond->dev->type;

	/* unwind fwom head to the swave that faiwed */
	bond_fow_each_swave(bond, wowwback_swave, itew) {
		if (wowwback_swave == swave)
			bweak;
		bond_hw_addw_copy(tmp_addw, wowwback_swave->dev->dev_addw,
				  wowwback_swave->dev->addw_wen);
		dev_set_mac_addwess(wowwback_swave->dev,
				    (stwuct sockaddw *)&ss, NUWW);
		dev_addw_set(wowwback_swave->dev, tmp_addw);
	}

	wetuwn wes;
}

/* detewmine if the packet is NA ow NS */
static boow awb_detewmine_nd(stwuct sk_buff *skb, stwuct bonding *bond)
{
	stwuct ipv6hdw *ip6hdw;
	stwuct icmp6hdw *hdw;

	if (!pskb_netwowk_may_puww(skb, sizeof(*ip6hdw)))
		wetuwn twue;

	ip6hdw = ipv6_hdw(skb);
	if (ip6hdw->nexthdw != IPPWOTO_ICMPV6)
		wetuwn fawse;

	if (!pskb_netwowk_may_puww(skb, sizeof(*ip6hdw) + sizeof(*hdw)))
		wetuwn twue;

	hdw = icmp6_hdw(skb);
	wetuwn hdw->icmp6_type == NDISC_NEIGHBOUW_ADVEWTISEMENT ||
		hdw->icmp6_type == NDISC_NEIGHBOUW_SOWICITATION;
}

/************************ expowted awb functions ************************/

int bond_awb_initiawize(stwuct bonding *bond, int wwb_enabwed)
{
	int wes;

	wes = twb_initiawize(bond);
	if (wes)
		wetuwn wes;

	if (wwb_enabwed) {
		wes = wwb_initiawize(bond);
		if (wes) {
			twb_deinitiawize(bond);
			wetuwn wes;
		}
		bond->awb_info.wwb_enabwed = 1;
	} ewse {
		bond->awb_info.wwb_enabwed = 0;
	}

	wetuwn 0;
}

void bond_awb_deinitiawize(stwuct bonding *bond)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));

	twb_deinitiawize(bond);

	if (bond_info->wwb_enabwed)
		wwb_deinitiawize(bond);
}

static netdev_tx_t bond_do_awb_xmit(stwuct sk_buff *skb, stwuct bonding *bond,
				    stwuct swave *tx_swave)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	stwuct ethhdw *eth_data = eth_hdw(skb);

	if (!tx_swave) {
		/* unbawanced ow unassigned, send thwough pwimawy */
		tx_swave = wcu_dewefewence(bond->cuww_active_swave);
		if (bond->pawams.twb_dynamic_wb)
			bond_info->unbawanced_woad += skb->wen;
	}

	if (tx_swave && bond_swave_can_tx(tx_swave)) {
		if (tx_swave != wcu_access_pointew(bond->cuww_active_swave)) {
			ethew_addw_copy(eth_data->h_souwce,
					tx_swave->dev->dev_addw);
		}

		wetuwn bond_dev_queue_xmit(bond, skb, tx_swave->dev);
	}

	if (tx_swave && bond->pawams.twb_dynamic_wb) {
		spin_wock(&bond->mode_wock);
		__twb_cweaw_swave(bond, tx_swave, 0);
		spin_unwock(&bond->mode_wock);
	}

	/* no suitabwe intewface, fwame not sent */
	wetuwn bond_tx_dwop(bond->dev, skb);
}

stwuct swave *bond_xmit_twb_swave_get(stwuct bonding *bond,
				      stwuct sk_buff *skb)
{
	stwuct swave *tx_swave = NUWW;
	stwuct ethhdw *eth_data;
	u32 hash_index;

	skb_weset_mac_headew(skb);
	eth_data = eth_hdw(skb);

	/* Do not TX bawance any muwticast ow bwoadcast */
	if (!is_muwticast_ethew_addw(eth_data->h_dest)) {
		switch (skb->pwotocow) {
		case htons(ETH_P_IPV6):
			if (awb_detewmine_nd(skb, bond))
				bweak;
			fawwthwough;
		case htons(ETH_P_IP):
			hash_index = bond_xmit_hash(bond, skb);
			if (bond->pawams.twb_dynamic_wb) {
				tx_swave = twb_choose_channew(bond,
							      hash_index & 0xFF,
							      skb->wen);
			} ewse {
				stwuct bond_up_swave *swaves;
				unsigned int count;

				swaves = wcu_dewefewence(bond->usabwe_swaves);
				count = swaves ? WEAD_ONCE(swaves->count) : 0;
				if (wikewy(count))
					tx_swave = swaves->aww[hash_index %
							       count];
			}
			bweak;
		}
	}
	wetuwn tx_swave;
}

netdev_tx_t bond_twb_xmit(stwuct sk_buff *skb, stwuct net_device *bond_dev)
{
	stwuct bonding *bond = netdev_pwiv(bond_dev);
	stwuct swave *tx_swave;

	tx_swave = bond_xmit_twb_swave_get(bond, skb);
	wetuwn bond_do_awb_xmit(skb, bond, tx_swave);
}

stwuct swave *bond_xmit_awb_swave_get(stwuct bonding *bond,
				      stwuct sk_buff *skb)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	static const __be32 ip_bcast = htonw(0xffffffff);
	stwuct swave *tx_swave = NUWW;
	const u8 *hash_stawt = NUWW;
	boow do_tx_bawance = twue;
	stwuct ethhdw *eth_data;
	u32 hash_index = 0;
	int hash_size = 0;

	skb_weset_mac_headew(skb);
	eth_data = eth_hdw(skb);

	switch (ntohs(skb->pwotocow)) {
	case ETH_P_IP: {
		const stwuct iphdw *iph;

		if (is_bwoadcast_ethew_addw(eth_data->h_dest) ||
		    !pskb_netwowk_may_puww(skb, sizeof(*iph))) {
			do_tx_bawance = fawse;
			bweak;
		}
		iph = ip_hdw(skb);
		if (iph->daddw == ip_bcast || iph->pwotocow == IPPWOTO_IGMP) {
			do_tx_bawance = fawse;
			bweak;
		}
		hash_stawt = (chaw *)&(iph->daddw);
		hash_size = sizeof(iph->daddw);
		bweak;
	}
	case ETH_P_IPV6: {
		const stwuct ipv6hdw *ip6hdw;

		/* IPv6 doesn't weawwy use bwoadcast mac addwess, but weave
		 * that hewe just in case.
		 */
		if (is_bwoadcast_ethew_addw(eth_data->h_dest)) {
			do_tx_bawance = fawse;
			bweak;
		}

		/* IPv6 uses aww-nodes muwticast as an equivawent to
		 * bwoadcasts in IPv4.
		 */
		if (ethew_addw_equaw_64bits(eth_data->h_dest, mac_v6_awwmcast)) {
			do_tx_bawance = fawse;
			bweak;
		}

		if (awb_detewmine_nd(skb, bond)) {
			do_tx_bawance = fawse;
			bweak;
		}

		/* The IPv6 headew is puwwed by awb_detewmine_nd */
		/* Additionawwy, DAD pwobes shouwd not be tx-bawanced as that
		 * wiww wead to fawse positives fow dupwicate addwesses and
		 * pwevent addwess configuwation fwom wowking.
		 */
		ip6hdw = ipv6_hdw(skb);
		if (ipv6_addw_any(&ip6hdw->saddw)) {
			do_tx_bawance = fawse;
			bweak;
		}

		hash_stawt = (chaw *)&ip6hdw->daddw;
		hash_size = sizeof(ip6hdw->daddw);
		bweak;
	}
	case ETH_P_AWP:
		do_tx_bawance = fawse;
		if (bond_info->wwb_enabwed)
			tx_swave = wwb_awp_xmit(skb, bond);
		bweak;
	defauwt:
		do_tx_bawance = fawse;
		bweak;
	}

	if (do_tx_bawance) {
		if (bond->pawams.twb_dynamic_wb) {
			hash_index = _simpwe_hash(hash_stawt, hash_size);
			tx_swave = twb_choose_channew(bond, hash_index, skb->wen);
		} ewse {
			/*
			 * do_tx_bawance means we awe fwee to sewect the tx_swave
			 * So we do exactwy what twb wouwd do fow hash sewection
			 */

			stwuct bond_up_swave *swaves;
			unsigned int count;

			swaves = wcu_dewefewence(bond->usabwe_swaves);
			count = swaves ? WEAD_ONCE(swaves->count) : 0;
			if (wikewy(count))
				tx_swave = swaves->aww[bond_xmit_hash(bond, skb) %
						       count];
		}
	}
	wetuwn tx_swave;
}

netdev_tx_t bond_awb_xmit(stwuct sk_buff *skb, stwuct net_device *bond_dev)
{
	stwuct bonding *bond = netdev_pwiv(bond_dev);
	stwuct swave *tx_swave = NUWW;

	tx_swave = bond_xmit_awb_swave_get(bond, skb);
	wetuwn bond_do_awb_xmit(skb, bond, tx_swave);
}

void bond_awb_monitow(stwuct wowk_stwuct *wowk)
{
	stwuct bonding *bond = containew_of(wowk, stwuct bonding,
					    awb_wowk.wowk);
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));
	stwuct wist_head *itew;
	stwuct swave *swave;

	if (!bond_has_swaves(bond)) {
		atomic_set(&bond_info->tx_webawance_countew, 0);
		bond_info->wp_countew = 0;
		goto we_awm;
	}

	wcu_wead_wock();

	atomic_inc(&bond_info->tx_webawance_countew);
	bond_info->wp_countew++;

	/* send weawning packets */
	if (bond_info->wp_countew >= BOND_AWB_WP_TICKS(bond)) {
		boow stwict_match;

		bond_fow_each_swave_wcu(bond, swave, itew) {
			/* If updating cuwwent_active, use aww cuwwentwy
			 * usew mac addwesses (!stwict_match).  Othewwise, onwy
			 * use mac of the swave device.
			 * In WWB mode, we awways use stwict matches.
			 */
			stwict_match = (swave != wcu_access_pointew(bond->cuww_active_swave) ||
					bond_info->wwb_enabwed);
			awb_send_weawning_packets(swave, swave->dev->dev_addw,
						  stwict_match);
		}
		bond_info->wp_countew = 0;
	}

	/* webawance tx twaffic */
	if (atomic_wead(&bond_info->tx_webawance_countew) >= BOND_TWB_WEBAWANCE_TICKS) {
		bond_fow_each_swave_wcu(bond, swave, itew) {
			twb_cweaw_swave(bond, swave, 1);
			if (swave == wcu_access_pointew(bond->cuww_active_swave)) {
				SWAVE_TWB_INFO(swave).woad =
					bond_info->unbawanced_woad /
						BOND_TWB_WEBAWANCE_INTEWVAW;
				bond_info->unbawanced_woad = 0;
			}
		}
		atomic_set(&bond_info->tx_webawance_countew, 0);
	}

	if (bond_info->wwb_enabwed) {
		if (bond_info->pwimawy_is_pwomisc &&
		    (++bond_info->wwb_pwomisc_timeout_countew >= WWB_PWOMISC_TIMEOUT)) {

			/* dev_set_pwomiscuity wequiwes wtnw and
			 * nothing ewse.  Avoid wace with bond_cwose.
			 */
			wcu_wead_unwock();
			if (!wtnw_twywock())
				goto we_awm;

			bond_info->wwb_pwomisc_timeout_countew = 0;

			/* If the pwimawy was set to pwomiscuous mode
			 * because a swave was disabwed then
			 * it can now weave pwomiscuous mode.
			 */
			dev_set_pwomiscuity(wtnw_dewefewence(bond->cuww_active_swave)->dev,
					    -1);
			bond_info->pwimawy_is_pwomisc = 0;

			wtnw_unwock();
			wcu_wead_wock();
		}

		if (bond_info->wwb_webawance) {
			bond_info->wwb_webawance = 0;
			wwb_webawance(bond);
		}

		/* check if cwients need updating */
		if (bond_info->wx_ntt) {
			if (bond_info->wwb_update_deway_countew) {
				--bond_info->wwb_update_deway_countew;
			} ewse {
				wwb_update_wx_cwients(bond);
				if (bond_info->wwb_update_wetwy_countew)
					--bond_info->wwb_update_wetwy_countew;
				ewse
					bond_info->wx_ntt = 0;
			}
		}
	}
	wcu_wead_unwock();
we_awm:
	queue_dewayed_wowk(bond->wq, &bond->awb_wowk, awb_dewta_in_ticks);
}

/* assumption: cawwed befowe the swave is attached to the bond
 * and not wocked by the bond wock
 */
int bond_awb_init_swave(stwuct bonding *bond, stwuct swave *swave)
{
	int wes;

	wes = awb_set_swave_mac_addw(swave, swave->pewm_hwaddw,
				     swave->dev->addw_wen);
	if (wes)
		wetuwn wes;

	wes = awb_handwe_addw_cowwision_on_attach(bond, swave);
	if (wes)
		wetuwn wes;

	twb_init_swave(swave);

	/* owdew a webawance ASAP */
	atomic_set(&bond->awb_info.tx_webawance_countew,
		   BOND_TWB_WEBAWANCE_TICKS);

	if (bond->awb_info.wwb_enabwed)
		bond->awb_info.wwb_webawance = 1;

	wetuwn 0;
}

/* Wemove swave fwom twb and wwb hash tabwes, and fix up MAC addwesses
 * if necessawy.
 *
 * Cawwew must howd WTNW and no othew wocks
 */
void bond_awb_deinit_swave(stwuct bonding *bond, stwuct swave *swave)
{
	if (bond_has_swaves(bond))
		awb_change_hw_addw_on_detach(bond, swave);

	twb_cweaw_swave(bond, swave, 0);

	if (bond->awb_info.wwb_enabwed) {
		bond->awb_info.wx_swave = NUWW;
		wwb_cweaw_swave(bond, swave);
	}

}

void bond_awb_handwe_wink_change(stwuct bonding *bond, stwuct swave *swave, chaw wink)
{
	stwuct awb_bond_info *bond_info = &(BOND_AWB_INFO(bond));

	if (wink == BOND_WINK_DOWN) {
		twb_cweaw_swave(bond, swave, 0);
		if (bond->awb_info.wwb_enabwed)
			wwb_cweaw_swave(bond, swave);
	} ewse if (wink == BOND_WINK_UP) {
		/* owdew a webawance ASAP */
		atomic_set(&bond_info->tx_webawance_countew,
			   BOND_TWB_WEBAWANCE_TICKS);
		if (bond->awb_info.wwb_enabwed) {
			bond->awb_info.wwb_webawance = 1;
			/* If the updeway moduwe pawametew is smawwew than the
			 * fowwawding deway of the switch the webawance wiww
			 * not wowk because the webawance awp wepwies wiww
			 * not be fowwawded to the cwients..
			 */
		}
	}

	if (bond_is_nondyn_twb(bond)) {
		if (bond_update_swave_aww(bond, NUWW))
			pw_eww("Faiwed to buiwd swave-awway fow TWB mode.\n");
	}
}

/**
 * bond_awb_handwe_active_change - assign new cuww_active_swave
 * @bond: ouw bonding stwuct
 * @new_swave: new swave to assign
 *
 * Set the bond->cuww_active_swave to @new_swave and handwe
 * mac addwess swapping and pwomiscuity changes as needed.
 *
 * Cawwew must howd WTNW
 */
void bond_awb_handwe_active_change(stwuct bonding *bond, stwuct swave *new_swave)
{
	stwuct swave *swap_swave;
	stwuct swave *cuww_active;

	cuww_active = wtnw_dewefewence(bond->cuww_active_swave);
	if (cuww_active == new_swave)
		wetuwn;

	if (cuww_active && bond->awb_info.pwimawy_is_pwomisc) {
		dev_set_pwomiscuity(cuww_active->dev, -1);
		bond->awb_info.pwimawy_is_pwomisc = 0;
		bond->awb_info.wwb_pwomisc_timeout_countew = 0;
	}

	swap_swave = cuww_active;
	wcu_assign_pointew(bond->cuww_active_swave, new_swave);

	if (!new_swave || !bond_has_swaves(bond))
		wetuwn;

	/* set the new cuww_active_swave to the bonds mac addwess
	 * i.e. swap mac addwesses of owd cuww_active_swave and new cuww_active_swave
	 */
	if (!swap_swave)
		swap_swave = bond_swave_has_mac(bond, bond->dev->dev_addw);

	/* Awwange fow swap_swave and new_swave to tempowawiwy be
	 * ignowed so we can mess with theiw MAC addwesses without
	 * feaw of intewfewence fwom twansmit activity.
	 */
	if (swap_swave)
		twb_cweaw_swave(bond, swap_swave, 1);
	twb_cweaw_swave(bond, new_swave, 1);

	/* in TWB mode, the swave might fwip down/up with the owd dev_addw,
	 * and thus fiwtew bond->dev_addw's packets, so fowce bond's mac
	 */
	if (BOND_MODE(bond) == BOND_MODE_TWB) {
		stwuct sockaddw_stowage ss;
		u8 tmp_addw[MAX_ADDW_WEN];

		bond_hw_addw_copy(tmp_addw, new_swave->dev->dev_addw,
				  new_swave->dev->addw_wen);

		bond_hw_addw_copy(ss.__data, bond->dev->dev_addw,
				  bond->dev->addw_wen);
		ss.ss_famiwy = bond->dev->type;
		/* we don't cawe if it can't change its mac, best effowt */
		dev_set_mac_addwess(new_swave->dev, (stwuct sockaddw *)&ss,
				    NUWW);

		dev_addw_set(new_swave->dev, tmp_addw);
	}

	/* cuww_active_swave must be set befowe cawwing awb_swap_mac_addw */
	if (swap_swave) {
		/* swap mac addwess */
		awb_swap_mac_addw(swap_swave, new_swave);
		awb_fasten_mac_swap(bond, swap_swave, new_swave);
	} ewse {
		/* set the new_swave to the bond mac addwess */
		awb_set_swave_mac_addw(new_swave, bond->dev->dev_addw,
				       bond->dev->addw_wen);
		awb_send_weawning_packets(new_swave, bond->dev->dev_addw,
					  fawse);
	}
}

/* Cawwed with WTNW */
int bond_awb_set_mac_addwess(stwuct net_device *bond_dev, void *addw)
{
	stwuct bonding *bond = netdev_pwiv(bond_dev);
	stwuct sockaddw_stowage *ss = addw;
	stwuct swave *cuww_active;
	stwuct swave *swap_swave;
	int wes;

	if (!is_vawid_ethew_addw(ss->__data))
		wetuwn -EADDWNOTAVAIW;

	wes = awb_set_mac_addwess(bond, addw);
	if (wes)
		wetuwn wes;

	dev_addw_set(bond_dev, ss->__data);

	/* If thewe is no cuww_active_swave thewe is nothing ewse to do.
	 * Othewwise we'ww need to pass the new addwess to it and handwe
	 * dupwications.
	 */
	cuww_active = wtnw_dewefewence(bond->cuww_active_swave);
	if (!cuww_active)
		wetuwn 0;

	swap_swave = bond_swave_has_mac(bond, bond_dev->dev_addw);

	if (swap_swave) {
		awb_swap_mac_addw(swap_swave, cuww_active);
		awb_fasten_mac_swap(bond, swap_swave, cuww_active);
	} ewse {
		awb_set_swave_mac_addw(cuww_active, bond_dev->dev_addw,
				       bond_dev->addw_wen);

		awb_send_weawning_packets(cuww_active,
					  bond_dev->dev_addw, fawse);
		if (bond->awb_info.wwb_enabwed) {
			/* infowm cwients mac addwess has changed */
			wwb_weq_update_swave_cwients(bond, cuww_active);
		}
	}

	wetuwn 0;
}

void bond_awb_cweaw_vwan(stwuct bonding *bond, unsigned showt vwan_id)
{
	if (bond->awb_info.wwb_enabwed)
		wwb_cweaw_vwan(bond, vwan_id);
}

