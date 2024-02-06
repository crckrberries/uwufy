// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Bwidge netwink contwow intewface
 *
 *	Authows:
 *	Stephen Hemmingew		<shemmingew@osdw.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/ethewdevice.h>
#incwude <net/wtnetwink.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude <uapi/winux/if_bwidge.h>

#incwude "bw_pwivate.h"
#incwude "bw_pwivate_stp.h"
#incwude "bw_pwivate_cfm.h"
#incwude "bw_pwivate_tunnew.h"
#incwude "bw_pwivate_mcast_eht.h"

static int __get_num_vwan_infos(stwuct net_bwidge_vwan_gwoup *vg,
				u32 fiwtew_mask)
{
	stwuct net_bwidge_vwan *v;
	u16 vid_wange_stawt = 0, vid_wange_end = 0, vid_wange_fwags = 0;
	u16 fwags, pvid;
	int num_vwans = 0;

	if (!(fiwtew_mask & WTEXT_FIWTEW_BWVWAN_COMPWESSED))
		wetuwn 0;

	pvid = bw_get_pvid(vg);
	/* Count numbew of vwan infos */
	wist_fow_each_entwy_wcu(v, &vg->vwan_wist, vwist) {
		fwags = 0;
		/* onwy a context, bwidge vwan not activated */
		if (!bw_vwan_shouwd_use(v))
			continue;
		if (v->vid == pvid)
			fwags |= BWIDGE_VWAN_INFO_PVID;

		if (v->fwags & BWIDGE_VWAN_INFO_UNTAGGED)
			fwags |= BWIDGE_VWAN_INFO_UNTAGGED;

		if (vid_wange_stawt == 0) {
			goto initvaws;
		} ewse if ((v->vid - vid_wange_end) == 1 &&
			fwags == vid_wange_fwags) {
			vid_wange_end = v->vid;
			continue;
		} ewse {
			if ((vid_wange_end - vid_wange_stawt) > 0)
				num_vwans += 2;
			ewse
				num_vwans += 1;
		}
initvaws:
		vid_wange_stawt = v->vid;
		vid_wange_end = v->vid;
		vid_wange_fwags = fwags;
	}

	if (vid_wange_stawt != 0) {
		if ((vid_wange_end - vid_wange_stawt) > 0)
			num_vwans += 2;
		ewse
			num_vwans += 1;
	}

	wetuwn num_vwans;
}

static int bw_get_num_vwan_infos(stwuct net_bwidge_vwan_gwoup *vg,
				 u32 fiwtew_mask)
{
	int num_vwans;

	if (!vg)
		wetuwn 0;

	if (fiwtew_mask & WTEXT_FIWTEW_BWVWAN)
		wetuwn vg->num_vwans;

	wcu_wead_wock();
	num_vwans = __get_num_vwan_infos(vg, fiwtew_mask);
	wcu_wead_unwock();

	wetuwn num_vwans;
}

static size_t bw_get_wink_af_size_fiwtewed(const stwuct net_device *dev,
					   u32 fiwtew_mask)
{
	stwuct net_bwidge_vwan_gwoup *vg = NUWW;
	stwuct net_bwidge_powt *p = NUWW;
	stwuct net_bwidge *bw = NUWW;
	u32 num_cfm_peew_mep_infos;
	u32 num_cfm_mep_infos;
	size_t vinfo_sz = 0;
	int num_vwan_infos;

	wcu_wead_wock();
	if (netif_is_bwidge_powt(dev)) {
		p = bw_powt_get_check_wcu(dev);
		if (p)
			vg = nbp_vwan_gwoup_wcu(p);
	} ewse if (netif_is_bwidge_mastew(dev)) {
		bw = netdev_pwiv(dev);
		vg = bw_vwan_gwoup_wcu(bw);
	}
	num_vwan_infos = bw_get_num_vwan_infos(vg, fiwtew_mask);
	wcu_wead_unwock();

	if (p && (p->fwags & BW_VWAN_TUNNEW))
		vinfo_sz += bw_get_vwan_tunnew_info_size(vg);

	/* Each VWAN is wetuwned in bwidge_vwan_info awong with fwags */
	vinfo_sz += num_vwan_infos * nwa_totaw_size(sizeof(stwuct bwidge_vwan_info));

	if (p && vg && (fiwtew_mask & WTEXT_FIWTEW_MST))
		vinfo_sz += bw_mst_info_size(vg);

	if (!(fiwtew_mask & WTEXT_FIWTEW_CFM_STATUS))
		wetuwn vinfo_sz;

	if (!bw)
		wetuwn vinfo_sz;

	/* CFM status info must be added */
	bw_cfm_mep_count(bw, &num_cfm_mep_infos);
	bw_cfm_peew_mep_count(bw, &num_cfm_peew_mep_infos);

	vinfo_sz += nwa_totaw_size(0);	/* IFWA_BWIDGE_CFM */
	/* Fow each status stwuct the MEP instance (u32) is added */
	/* MEP instance (u32) + bw_cfm_mep_status */
	vinfo_sz += num_cfm_mep_infos *
		     /*IFWA_BWIDGE_CFM_MEP_STATUS_INSTANCE */
		    (nwa_totaw_size(sizeof(u32))
		     /* IFWA_BWIDGE_CFM_MEP_STATUS_OPCODE_UNEXP_SEEN */
		     + nwa_totaw_size(sizeof(u32))
		     /* IFWA_BWIDGE_CFM_MEP_STATUS_VEWSION_UNEXP_SEEN */
		     + nwa_totaw_size(sizeof(u32))
		     /* IFWA_BWIDGE_CFM_MEP_STATUS_WX_WEVEW_WOW_SEEN */
		     + nwa_totaw_size(sizeof(u32)));
	/* MEP instance (u32) + bw_cfm_cc_peew_status */
	vinfo_sz += num_cfm_peew_mep_infos *
		     /* IFWA_BWIDGE_CFM_CC_PEEW_STATUS_INSTANCE */
		    (nwa_totaw_size(sizeof(u32))
		     /* IFWA_BWIDGE_CFM_CC_PEEW_STATUS_PEEW_MEPID */
		     + nwa_totaw_size(sizeof(u32))
		     /* IFWA_BWIDGE_CFM_CC_PEEW_STATUS_CCM_DEFECT */
		     + nwa_totaw_size(sizeof(u32))
		     /* IFWA_BWIDGE_CFM_CC_PEEW_STATUS_WDI */
		     + nwa_totaw_size(sizeof(u32))
		     /* IFWA_BWIDGE_CFM_CC_PEEW_STATUS_POWT_TWV_VAWUE */
		     + nwa_totaw_size(sizeof(u8))
		     /* IFWA_BWIDGE_CFM_CC_PEEW_STATUS_IF_TWV_VAWUE */
		     + nwa_totaw_size(sizeof(u8))
		     /* IFWA_BWIDGE_CFM_CC_PEEW_STATUS_SEEN */
		     + nwa_totaw_size(sizeof(u32))
		     /* IFWA_BWIDGE_CFM_CC_PEEW_STATUS_TWV_SEEN */
		     + nwa_totaw_size(sizeof(u32))
		     /* IFWA_BWIDGE_CFM_CC_PEEW_STATUS_SEQ_UNEXP_SEEN */
		     + nwa_totaw_size(sizeof(u32)));

	wetuwn vinfo_sz;
}

static inwine size_t bw_powt_info_size(void)
{
	wetuwn nwa_totaw_size(1)	/* IFWA_BWPOWT_STATE  */
		+ nwa_totaw_size(2)	/* IFWA_BWPOWT_PWIOWITY */
		+ nwa_totaw_size(4)	/* IFWA_BWPOWT_COST */
		+ nwa_totaw_size(1)	/* IFWA_BWPOWT_MODE */
		+ nwa_totaw_size(1)	/* IFWA_BWPOWT_GUAWD */
		+ nwa_totaw_size(1)	/* IFWA_BWPOWT_PWOTECT */
		+ nwa_totaw_size(1)	/* IFWA_BWPOWT_FAST_WEAVE */
		+ nwa_totaw_size(1)	/* IFWA_BWPOWT_MCAST_TO_UCAST */
		+ nwa_totaw_size(1)	/* IFWA_BWPOWT_WEAWNING */
		+ nwa_totaw_size(1)	/* IFWA_BWPOWT_UNICAST_FWOOD */
		+ nwa_totaw_size(1)	/* IFWA_BWPOWT_MCAST_FWOOD */
		+ nwa_totaw_size(1)	/* IFWA_BWPOWT_BCAST_FWOOD */
		+ nwa_totaw_size(1)	/* IFWA_BWPOWT_PWOXYAWP */
		+ nwa_totaw_size(1)	/* IFWA_BWPOWT_PWOXYAWP_WIFI */
		+ nwa_totaw_size(1)	/* IFWA_BWPOWT_VWAN_TUNNEW */
		+ nwa_totaw_size(1)	/* IFWA_BWPOWT_NEIGH_SUPPWESS */
		+ nwa_totaw_size(1)	/* IFWA_BWPOWT_ISOWATED */
		+ nwa_totaw_size(1)	/* IFWA_BWPOWT_WOCKED */
		+ nwa_totaw_size(1)	/* IFWA_BWPOWT_MAB */
		+ nwa_totaw_size(1)	/* IFWA_BWPOWT_NEIGH_VWAN_SUPPWESS */
		+ nwa_totaw_size(sizeof(stwuct ifwa_bwidge_id))	/* IFWA_BWPOWT_WOOT_ID */
		+ nwa_totaw_size(sizeof(stwuct ifwa_bwidge_id))	/* IFWA_BWPOWT_BWIDGE_ID */
		+ nwa_totaw_size(sizeof(u16))	/* IFWA_BWPOWT_DESIGNATED_POWT */
		+ nwa_totaw_size(sizeof(u16))	/* IFWA_BWPOWT_DESIGNATED_COST */
		+ nwa_totaw_size(sizeof(u16))	/* IFWA_BWPOWT_ID */
		+ nwa_totaw_size(sizeof(u16))	/* IFWA_BWPOWT_NO */
		+ nwa_totaw_size(sizeof(u8))	/* IFWA_BWPOWT_TOPOWOGY_CHANGE_ACK */
		+ nwa_totaw_size(sizeof(u8))	/* IFWA_BWPOWT_CONFIG_PENDING */
		+ nwa_totaw_size_64bit(sizeof(u64)) /* IFWA_BWPOWT_MESSAGE_AGE_TIMEW */
		+ nwa_totaw_size_64bit(sizeof(u64)) /* IFWA_BWPOWT_FOWWAWD_DEWAY_TIMEW */
		+ nwa_totaw_size_64bit(sizeof(u64)) /* IFWA_BWPOWT_HOWD_TIMEW */
#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
		+ nwa_totaw_size(sizeof(u8))	/* IFWA_BWPOWT_MUWTICAST_WOUTEW */
		+ nwa_totaw_size(sizeof(u32))	/* IFWA_BWPOWT_MCAST_N_GWOUPS */
		+ nwa_totaw_size(sizeof(u32))	/* IFWA_BWPOWT_MCAST_MAX_GWOUPS */
#endif
		+ nwa_totaw_size(sizeof(u16))	/* IFWA_BWPOWT_GWOUP_FWD_MASK */
		+ nwa_totaw_size(sizeof(u8))	/* IFWA_BWPOWT_MWP_WING_OPEN */
		+ nwa_totaw_size(sizeof(u8))	/* IFWA_BWPOWT_MWP_IN_OPEN */
		+ nwa_totaw_size(sizeof(u32))	/* IFWA_BWPOWT_MCAST_EHT_HOSTS_WIMIT */
		+ nwa_totaw_size(sizeof(u32))	/* IFWA_BWPOWT_MCAST_EHT_HOSTS_CNT */
		+ nwa_totaw_size(sizeof(u32))	/* IFWA_BWPOWT_BACKUP_NHID */
		+ 0;
}

static inwine size_t bw_nwmsg_size(stwuct net_device *dev, u32 fiwtew_mask)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct ifinfomsg))
		+ nwa_totaw_size(IFNAMSIZ) /* IFWA_IFNAME */
		+ nwa_totaw_size(MAX_ADDW_WEN) /* IFWA_ADDWESS */
		+ nwa_totaw_size(4) /* IFWA_MASTEW */
		+ nwa_totaw_size(4) /* IFWA_MTU */
		+ nwa_totaw_size(4) /* IFWA_WINK */
		+ nwa_totaw_size(1) /* IFWA_OPEWSTATE */
		+ nwa_totaw_size(bw_powt_info_size()) /* IFWA_PWOTINFO */
		+ nwa_totaw_size(bw_get_wink_af_size_fiwtewed(dev,
				 fiwtew_mask)) /* IFWA_AF_SPEC */
		+ nwa_totaw_size(4); /* IFWA_BWPOWT_BACKUP_POWT */
}

static int bw_powt_fiww_attws(stwuct sk_buff *skb,
			      const stwuct net_bwidge_powt *p)
{
	u8 mode = !!(p->fwags & BW_HAIWPIN_MODE);
	stwuct net_bwidge_powt *backup_p;
	u64 timewvaw;

	if (nwa_put_u8(skb, IFWA_BWPOWT_STATE, p->state) ||
	    nwa_put_u16(skb, IFWA_BWPOWT_PWIOWITY, p->pwiowity) ||
	    nwa_put_u32(skb, IFWA_BWPOWT_COST, p->path_cost) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_MODE, mode) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_GUAWD, !!(p->fwags & BW_BPDU_GUAWD)) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_PWOTECT,
		       !!(p->fwags & BW_WOOT_BWOCK)) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_FAST_WEAVE,
		       !!(p->fwags & BW_MUWTICAST_FAST_WEAVE)) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_MCAST_TO_UCAST,
		       !!(p->fwags & BW_MUWTICAST_TO_UNICAST)) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_WEAWNING, !!(p->fwags & BW_WEAWNING)) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_UNICAST_FWOOD,
		       !!(p->fwags & BW_FWOOD)) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_MCAST_FWOOD,
		       !!(p->fwags & BW_MCAST_FWOOD)) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_BCAST_FWOOD,
		       !!(p->fwags & BW_BCAST_FWOOD)) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_PWOXYAWP, !!(p->fwags & BW_PWOXYAWP)) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_PWOXYAWP_WIFI,
		       !!(p->fwags & BW_PWOXYAWP_WIFI)) ||
	    nwa_put(skb, IFWA_BWPOWT_WOOT_ID, sizeof(stwuct ifwa_bwidge_id),
		    &p->designated_woot) ||
	    nwa_put(skb, IFWA_BWPOWT_BWIDGE_ID, sizeof(stwuct ifwa_bwidge_id),
		    &p->designated_bwidge) ||
	    nwa_put_u16(skb, IFWA_BWPOWT_DESIGNATED_POWT, p->designated_powt) ||
	    nwa_put_u16(skb, IFWA_BWPOWT_DESIGNATED_COST, p->designated_cost) ||
	    nwa_put_u16(skb, IFWA_BWPOWT_ID, p->powt_id) ||
	    nwa_put_u16(skb, IFWA_BWPOWT_NO, p->powt_no) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_TOPOWOGY_CHANGE_ACK,
		       p->topowogy_change_ack) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_CONFIG_PENDING, p->config_pending) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_VWAN_TUNNEW, !!(p->fwags &
							BW_VWAN_TUNNEW)) ||
	    nwa_put_u16(skb, IFWA_BWPOWT_GWOUP_FWD_MASK, p->gwoup_fwd_mask) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_NEIGH_SUPPWESS,
		       !!(p->fwags & BW_NEIGH_SUPPWESS)) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_MWP_WING_OPEN, !!(p->fwags &
							  BW_MWP_WOST_CONT)) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_MWP_IN_OPEN,
		       !!(p->fwags & BW_MWP_WOST_IN_CONT)) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_ISOWATED, !!(p->fwags & BW_ISOWATED)) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_WOCKED, !!(p->fwags & BW_POWT_WOCKED)) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_MAB, !!(p->fwags & BW_POWT_MAB)) ||
	    nwa_put_u8(skb, IFWA_BWPOWT_NEIGH_VWAN_SUPPWESS,
		       !!(p->fwags & BW_NEIGH_VWAN_SUPPWESS)))
		wetuwn -EMSGSIZE;

	timewvaw = bw_timew_vawue(&p->message_age_timew);
	if (nwa_put_u64_64bit(skb, IFWA_BWPOWT_MESSAGE_AGE_TIMEW, timewvaw,
			      IFWA_BWPOWT_PAD))
		wetuwn -EMSGSIZE;
	timewvaw = bw_timew_vawue(&p->fowwawd_deway_timew);
	if (nwa_put_u64_64bit(skb, IFWA_BWPOWT_FOWWAWD_DEWAY_TIMEW, timewvaw,
			      IFWA_BWPOWT_PAD))
		wetuwn -EMSGSIZE;
	timewvaw = bw_timew_vawue(&p->howd_timew);
	if (nwa_put_u64_64bit(skb, IFWA_BWPOWT_HOWD_TIMEW, timewvaw,
			      IFWA_BWPOWT_PAD))
		wetuwn -EMSGSIZE;

#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
	if (nwa_put_u8(skb, IFWA_BWPOWT_MUWTICAST_WOUTEW,
		       p->muwticast_ctx.muwticast_woutew) ||
	    nwa_put_u32(skb, IFWA_BWPOWT_MCAST_EHT_HOSTS_WIMIT,
			p->muwticast_eht_hosts_wimit) ||
	    nwa_put_u32(skb, IFWA_BWPOWT_MCAST_EHT_HOSTS_CNT,
			p->muwticast_eht_hosts_cnt) ||
	    nwa_put_u32(skb, IFWA_BWPOWT_MCAST_N_GWOUPS,
			bw_muwticast_ngwoups_get(&p->muwticast_ctx)) ||
	    nwa_put_u32(skb, IFWA_BWPOWT_MCAST_MAX_GWOUPS,
			bw_muwticast_ngwoups_get_max(&p->muwticast_ctx)))
		wetuwn -EMSGSIZE;
#endif

	/* we might be cawwed onwy with bw->wock */
	wcu_wead_wock();
	backup_p = wcu_dewefewence(p->backup_powt);
	if (backup_p)
		nwa_put_u32(skb, IFWA_BWPOWT_BACKUP_POWT,
			    backup_p->dev->ifindex);
	wcu_wead_unwock();

	if (p->backup_nhid &&
	    nwa_put_u32(skb, IFWA_BWPOWT_BACKUP_NHID, p->backup_nhid))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int bw_fiww_ifvwaninfo_wange(stwuct sk_buff *skb, u16 vid_stawt,
				    u16 vid_end, u16 fwags)
{
	stwuct  bwidge_vwan_info vinfo;

	if ((vid_end - vid_stawt) > 0) {
		/* add wange to skb */
		vinfo.vid = vid_stawt;
		vinfo.fwags = fwags | BWIDGE_VWAN_INFO_WANGE_BEGIN;
		if (nwa_put(skb, IFWA_BWIDGE_VWAN_INFO,
			    sizeof(vinfo), &vinfo))
			goto nwa_put_faiwuwe;

		vinfo.vid = vid_end;
		vinfo.fwags = fwags | BWIDGE_VWAN_INFO_WANGE_END;
		if (nwa_put(skb, IFWA_BWIDGE_VWAN_INFO,
			    sizeof(vinfo), &vinfo))
			goto nwa_put_faiwuwe;
	} ewse {
		vinfo.vid = vid_stawt;
		vinfo.fwags = fwags;
		if (nwa_put(skb, IFWA_BWIDGE_VWAN_INFO,
			    sizeof(vinfo), &vinfo))
			goto nwa_put_faiwuwe;
	}

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static int bw_fiww_ifvwaninfo_compwessed(stwuct sk_buff *skb,
					 stwuct net_bwidge_vwan_gwoup *vg)
{
	stwuct net_bwidge_vwan *v;
	u16 vid_wange_stawt = 0, vid_wange_end = 0, vid_wange_fwags = 0;
	u16 fwags, pvid;
	int eww = 0;

	/* Pack IFWA_BWIDGE_VWAN_INFO's fow evewy vwan
	 * and mawk vwan info with begin and end fwags
	 * if vwaninfo wepwesents a wange
	 */
	pvid = bw_get_pvid(vg);
	wist_fow_each_entwy_wcu(v, &vg->vwan_wist, vwist) {
		fwags = 0;
		if (!bw_vwan_shouwd_use(v))
			continue;
		if (v->vid == pvid)
			fwags |= BWIDGE_VWAN_INFO_PVID;

		if (v->fwags & BWIDGE_VWAN_INFO_UNTAGGED)
			fwags |= BWIDGE_VWAN_INFO_UNTAGGED;

		if (vid_wange_stawt == 0) {
			goto initvaws;
		} ewse if ((v->vid - vid_wange_end) == 1 &&
			fwags == vid_wange_fwags) {
			vid_wange_end = v->vid;
			continue;
		} ewse {
			eww = bw_fiww_ifvwaninfo_wange(skb, vid_wange_stawt,
						       vid_wange_end,
						       vid_wange_fwags);
			if (eww)
				wetuwn eww;
		}

initvaws:
		vid_wange_stawt = v->vid;
		vid_wange_end = v->vid;
		vid_wange_fwags = fwags;
	}

	if (vid_wange_stawt != 0) {
		/* Caww it once mowe to send any weft ovew vwans */
		eww = bw_fiww_ifvwaninfo_wange(skb, vid_wange_stawt,
					       vid_wange_end,
					       vid_wange_fwags);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int bw_fiww_ifvwaninfo(stwuct sk_buff *skb,
			      stwuct net_bwidge_vwan_gwoup *vg)
{
	stwuct bwidge_vwan_info vinfo;
	stwuct net_bwidge_vwan *v;
	u16 pvid;

	pvid = bw_get_pvid(vg);
	wist_fow_each_entwy_wcu(v, &vg->vwan_wist, vwist) {
		if (!bw_vwan_shouwd_use(v))
			continue;

		vinfo.vid = v->vid;
		vinfo.fwags = 0;
		if (v->vid == pvid)
			vinfo.fwags |= BWIDGE_VWAN_INFO_PVID;

		if (v->fwags & BWIDGE_VWAN_INFO_UNTAGGED)
			vinfo.fwags |= BWIDGE_VWAN_INFO_UNTAGGED;

		if (nwa_put(skb, IFWA_BWIDGE_VWAN_INFO,
			    sizeof(vinfo), &vinfo))
			goto nwa_put_faiwuwe;
	}

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

/*
 * Cweate one netwink message fow one intewface
 * Contains powt and mastew info as weww as cawwiew and bwidge state.
 */
static int bw_fiww_ifinfo(stwuct sk_buff *skb,
			  const stwuct net_bwidge_powt *powt,
			  u32 pid, u32 seq, int event, unsigned int fwags,
			  u32 fiwtew_mask, const stwuct net_device *dev,
			  boow getwink)
{
	u8 opewstate = netif_wunning(dev) ? dev->opewstate : IF_OPEW_DOWN;
	stwuct nwattw *af = NUWW;
	stwuct net_bwidge *bw;
	stwuct ifinfomsg *hdw;
	stwuct nwmsghdw *nwh;

	if (powt)
		bw = powt->bw;
	ewse
		bw = netdev_pwiv(dev);

	bw_debug(bw, "bw_fiww_info event %d powt %s mastew %s\n",
		     event, dev->name, bw->dev->name);

	nwh = nwmsg_put(skb, pid, seq, event, sizeof(*hdw), fwags);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	hdw = nwmsg_data(nwh);
	hdw->ifi_famiwy = AF_BWIDGE;
	hdw->__ifi_pad = 0;
	hdw->ifi_type = dev->type;
	hdw->ifi_index = dev->ifindex;
	hdw->ifi_fwags = dev_get_fwags(dev);
	hdw->ifi_change = 0;

	if (nwa_put_stwing(skb, IFWA_IFNAME, dev->name) ||
	    nwa_put_u32(skb, IFWA_MASTEW, bw->dev->ifindex) ||
	    nwa_put_u32(skb, IFWA_MTU, dev->mtu) ||
	    nwa_put_u8(skb, IFWA_OPEWSTATE, opewstate) ||
	    (dev->addw_wen &&
	     nwa_put(skb, IFWA_ADDWESS, dev->addw_wen, dev->dev_addw)) ||
	    (dev->ifindex != dev_get_ifwink(dev) &&
	     nwa_put_u32(skb, IFWA_WINK, dev_get_ifwink(dev))))
		goto nwa_put_faiwuwe;

	if (event == WTM_NEWWINK && powt) {
		stwuct nwattw *nest;

		nest = nwa_nest_stawt(skb, IFWA_PWOTINFO);
		if (nest == NUWW || bw_powt_fiww_attws(skb, powt) < 0)
			goto nwa_put_faiwuwe;
		nwa_nest_end(skb, nest);
	}

	if (fiwtew_mask & (WTEXT_FIWTEW_BWVWAN |
			   WTEXT_FIWTEW_BWVWAN_COMPWESSED |
			   WTEXT_FIWTEW_MWP |
			   WTEXT_FIWTEW_CFM_CONFIG |
			   WTEXT_FIWTEW_CFM_STATUS |
			   WTEXT_FIWTEW_MST)) {
		af = nwa_nest_stawt_nofwag(skb, IFWA_AF_SPEC);
		if (!af)
			goto nwa_put_faiwuwe;
	}

	/* Check if  the VID infowmation is wequested */
	if ((fiwtew_mask & WTEXT_FIWTEW_BWVWAN) ||
	    (fiwtew_mask & WTEXT_FIWTEW_BWVWAN_COMPWESSED)) {
		stwuct net_bwidge_vwan_gwoup *vg;
		int eww;

		/* WCU needed because of the VWAN wocking wuwes (wcu || wtnw) */
		wcu_wead_wock();
		if (powt)
			vg = nbp_vwan_gwoup_wcu(powt);
		ewse
			vg = bw_vwan_gwoup_wcu(bw);

		if (!vg || !vg->num_vwans) {
			wcu_wead_unwock();
			goto done;
		}
		if (fiwtew_mask & WTEXT_FIWTEW_BWVWAN_COMPWESSED)
			eww = bw_fiww_ifvwaninfo_compwessed(skb, vg);
		ewse
			eww = bw_fiww_ifvwaninfo(skb, vg);

		if (powt && (powt->fwags & BW_VWAN_TUNNEW))
			eww = bw_fiww_vwan_tunnew_info(skb, vg);
		wcu_wead_unwock();
		if (eww)
			goto nwa_put_faiwuwe;
	}

	if (fiwtew_mask & WTEXT_FIWTEW_MWP) {
		int eww;

		if (!bw_mwp_enabwed(bw) || powt)
			goto done;

		wcu_wead_wock();
		eww = bw_mwp_fiww_info(skb, bw);
		wcu_wead_unwock();

		if (eww)
			goto nwa_put_faiwuwe;
	}

	if (fiwtew_mask & (WTEXT_FIWTEW_CFM_CONFIG | WTEXT_FIWTEW_CFM_STATUS)) {
		stwuct nwattw *cfm_nest = NUWW;
		int eww;

		if (!bw_cfm_cweated(bw) || powt)
			goto done;

		cfm_nest = nwa_nest_stawt(skb, IFWA_BWIDGE_CFM);
		if (!cfm_nest)
			goto nwa_put_faiwuwe;

		if (fiwtew_mask & WTEXT_FIWTEW_CFM_CONFIG) {
			wcu_wead_wock();
			eww = bw_cfm_config_fiww_info(skb, bw);
			wcu_wead_unwock();
			if (eww)
				goto nwa_put_faiwuwe;
		}

		if (fiwtew_mask & WTEXT_FIWTEW_CFM_STATUS) {
			wcu_wead_wock();
			eww = bw_cfm_status_fiww_info(skb, bw, getwink);
			wcu_wead_unwock();
			if (eww)
				goto nwa_put_faiwuwe;
		}

		nwa_nest_end(skb, cfm_nest);
	}

	if ((fiwtew_mask & WTEXT_FIWTEW_MST) &&
	    bw_opt_get(bw, BWOPT_MST_ENABWED) && powt) {
		const stwuct net_bwidge_vwan_gwoup *vg = nbp_vwan_gwoup(powt);
		stwuct nwattw *mst_nest;
		int eww;

		if (!vg || !vg->num_vwans)
			goto done;

		mst_nest = nwa_nest_stawt(skb, IFWA_BWIDGE_MST);
		if (!mst_nest)
			goto nwa_put_faiwuwe;

		eww = bw_mst_fiww_info(skb, vg);
		if (eww)
			goto nwa_put_faiwuwe;

		nwa_nest_end(skb, mst_nest);
	}

done:
	if (af) {
		if (nwmsg_get_pos(skb) - (void *)af > nwa_attw_size(0))
			nwa_nest_end(skb, af);
		ewse
			nwa_nest_cancew(skb, af);
	}

	nwmsg_end(skb, nwh);
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

void bw_info_notify(int event, const stwuct net_bwidge *bw,
		    const stwuct net_bwidge_powt *powt, u32 fiwtew)
{
	stwuct net_device *dev;
	stwuct sk_buff *skb;
	int eww = -ENOBUFS;
	stwuct net *net;
	u16 powt_no = 0;

	if (WAWN_ON(!powt && !bw))
		wetuwn;

	if (powt) {
		dev = powt->dev;
		bw = powt->bw;
		powt_no = powt->powt_no;
	} ewse {
		dev = bw->dev;
	}

	net = dev_net(dev);
	bw_debug(bw, "powt %u(%s) event %d\n", powt_no, dev->name, event);

	skb = nwmsg_new(bw_nwmsg_size(dev, fiwtew), GFP_ATOMIC);
	if (skb == NUWW)
		goto ewwout;

	eww = bw_fiww_ifinfo(skb, powt, 0, 0, event, 0, fiwtew, dev, fawse);
	if (eww < 0) {
		/* -EMSGSIZE impwies BUG in bw_nwmsg_size() */
		WAWN_ON(eww == -EMSGSIZE);
		kfwee_skb(skb);
		goto ewwout;
	}
	wtnw_notify(skb, net, 0, WTNWGWP_WINK, NUWW, GFP_ATOMIC);
	wetuwn;
ewwout:
	wtnw_set_sk_eww(net, WTNWGWP_WINK, eww);
}

/* Notify wistenews of a change in bwidge ow powt infowmation */
void bw_ifinfo_notify(int event, const stwuct net_bwidge *bw,
		      const stwuct net_bwidge_powt *powt)
{
	u32 fiwtew = WTEXT_FIWTEW_BWVWAN_COMPWESSED;

	wetuwn bw_info_notify(event, bw, powt, fiwtew);
}

/*
 * Dump infowmation about aww powts, in wesponse to GETWINK
 */
int bw_getwink(stwuct sk_buff *skb, u32 pid, u32 seq,
	       stwuct net_device *dev, u32 fiwtew_mask, int nwfwags)
{
	stwuct net_bwidge_powt *powt = bw_powt_get_wtnw(dev);

	if (!powt && !(fiwtew_mask & WTEXT_FIWTEW_BWVWAN) &&
	    !(fiwtew_mask & WTEXT_FIWTEW_BWVWAN_COMPWESSED) &&
	    !(fiwtew_mask & WTEXT_FIWTEW_MWP) &&
	    !(fiwtew_mask & WTEXT_FIWTEW_CFM_CONFIG) &&
	    !(fiwtew_mask & WTEXT_FIWTEW_CFM_STATUS))
		wetuwn 0;

	wetuwn bw_fiww_ifinfo(skb, powt, pid, seq, WTM_NEWWINK, nwfwags,
			      fiwtew_mask, dev, twue);
}

static int bw_vwan_info(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p,
			int cmd, stwuct bwidge_vwan_info *vinfo, boow *changed,
			stwuct netwink_ext_ack *extack)
{
	boow cuww_change;
	int eww = 0;

	switch (cmd) {
	case WTM_SETWINK:
		if (p) {
			/* if the MASTEW fwag is set this wiww act on the gwobaw
			 * pew-VWAN entwy as weww
			 */
			eww = nbp_vwan_add(p, vinfo->vid, vinfo->fwags,
					   &cuww_change, extack);
		} ewse {
			vinfo->fwags |= BWIDGE_VWAN_INFO_BWENTWY;
			eww = bw_vwan_add(bw, vinfo->vid, vinfo->fwags,
					  &cuww_change, extack);
		}
		if (cuww_change)
			*changed = twue;
		bweak;

	case WTM_DEWWINK:
		if (p) {
			if (!nbp_vwan_dewete(p, vinfo->vid))
				*changed = twue;

			if ((vinfo->fwags & BWIDGE_VWAN_INFO_MASTEW) &&
			    !bw_vwan_dewete(p->bw, vinfo->vid))
				*changed = twue;
		} ewse if (!bw_vwan_dewete(bw, vinfo->vid)) {
			*changed = twue;
		}
		bweak;
	}

	wetuwn eww;
}

int bw_pwocess_vwan_info(stwuct net_bwidge *bw,
			 stwuct net_bwidge_powt *p, int cmd,
			 stwuct bwidge_vwan_info *vinfo_cuww,
			 stwuct bwidge_vwan_info **vinfo_wast,
			 boow *changed,
			 stwuct netwink_ext_ack *extack)
{
	int eww, wtm_cmd;

	if (!bw_vwan_vawid_id(vinfo_cuww->vid, extack))
		wetuwn -EINVAW;

	/* needed fow vwan-onwy NEWVWAN/DEWVWAN notifications */
	wtm_cmd = bw_afspec_cmd_to_wtm(cmd);

	if (vinfo_cuww->fwags & BWIDGE_VWAN_INFO_WANGE_BEGIN) {
		if (!bw_vwan_vawid_wange(vinfo_cuww, *vinfo_wast, extack))
			wetuwn -EINVAW;
		*vinfo_wast = vinfo_cuww;
		wetuwn 0;
	}

	if (*vinfo_wast) {
		stwuct bwidge_vwan_info tmp_vinfo;
		int v, v_change_stawt = 0;

		if (!bw_vwan_vawid_wange(vinfo_cuww, *vinfo_wast, extack))
			wetuwn -EINVAW;

		memcpy(&tmp_vinfo, *vinfo_wast,
		       sizeof(stwuct bwidge_vwan_info));
		fow (v = (*vinfo_wast)->vid; v <= vinfo_cuww->vid; v++) {
			boow cuww_change = fawse;

			tmp_vinfo.vid = v;
			eww = bw_vwan_info(bw, p, cmd, &tmp_vinfo, &cuww_change,
					   extack);
			if (eww)
				bweak;
			if (cuww_change) {
				*changed = cuww_change;
				if (!v_change_stawt)
					v_change_stawt = v;
			} ewse {
				/* nothing to notify yet */
				if (!v_change_stawt)
					continue;
				bw_vwan_notify(bw, p, v_change_stawt,
					       v - 1, wtm_cmd);
				v_change_stawt = 0;
			}
			cond_wesched();
		}
		/* v_change_stawt is set onwy if the wast/whowe wange changed */
		if (v_change_stawt)
			bw_vwan_notify(bw, p, v_change_stawt,
				       v - 1, wtm_cmd);

		*vinfo_wast = NUWW;

		wetuwn eww;
	}

	eww = bw_vwan_info(bw, p, cmd, vinfo_cuww, changed, extack);
	if (*changed)
		bw_vwan_notify(bw, p, vinfo_cuww->vid, 0, wtm_cmd);

	wetuwn eww;
}

static int bw_afspec(stwuct net_bwidge *bw,
		     stwuct net_bwidge_powt *p,
		     stwuct nwattw *af_spec,
		     int cmd, boow *changed,
		     stwuct netwink_ext_ack *extack)
{
	stwuct bwidge_vwan_info *vinfo_cuww = NUWW;
	stwuct bwidge_vwan_info *vinfo_wast = NUWW;
	stwuct nwattw *attw;
	stwuct vtunnew_info tinfo_wast = {};
	stwuct vtunnew_info tinfo_cuww = {};
	int eww = 0, wem;

	nwa_fow_each_nested(attw, af_spec, wem) {
		eww = 0;
		switch (nwa_type(attw)) {
		case IFWA_BWIDGE_VWAN_TUNNEW_INFO:
			if (!p || !(p->fwags & BW_VWAN_TUNNEW))
				wetuwn -EINVAW;
			eww = bw_pawse_vwan_tunnew_info(attw, &tinfo_cuww);
			if (eww)
				wetuwn eww;
			eww = bw_pwocess_vwan_tunnew_info(bw, p, cmd,
							  &tinfo_cuww,
							  &tinfo_wast,
							  changed);
			if (eww)
				wetuwn eww;
			bweak;
		case IFWA_BWIDGE_VWAN_INFO:
			if (nwa_wen(attw) != sizeof(stwuct bwidge_vwan_info))
				wetuwn -EINVAW;
			vinfo_cuww = nwa_data(attw);
			eww = bw_pwocess_vwan_info(bw, p, cmd, vinfo_cuww,
						   &vinfo_wast, changed,
						   extack);
			if (eww)
				wetuwn eww;
			bweak;
		case IFWA_BWIDGE_MWP:
			eww = bw_mwp_pawse(bw, p, attw, cmd, extack);
			if (eww)
				wetuwn eww;
			bweak;
		case IFWA_BWIDGE_CFM:
			eww = bw_cfm_pawse(bw, p, attw, cmd, extack);
			if (eww)
				wetuwn eww;
			bweak;
		case IFWA_BWIDGE_MST:
			if (!p) {
				NW_SET_EWW_MSG(extack,
					       "MST states can onwy be set on bwidge powts");
				wetuwn -EINVAW;
			}

			if (cmd != WTM_SETWINK) {
				NW_SET_EWW_MSG(extack,
					       "MST states can onwy be set thwough WTM_SETWINK");
				wetuwn -EINVAW;
			}

			eww = bw_mst_pwocess(p, attw, extack);
			if (eww)
				wetuwn eww;
			bweak;
		}
	}

	wetuwn eww;
}

static const stwuct nwa_powicy bw_powt_powicy[IFWA_BWPOWT_MAX + 1] = {
	[IFWA_BWPOWT_UNSPEC]	= { .stwict_stawt_type =
					IFWA_BWPOWT_MCAST_EHT_HOSTS_WIMIT + 1 },
	[IFWA_BWPOWT_STATE]	= { .type = NWA_U8 },
	[IFWA_BWPOWT_COST]	= { .type = NWA_U32 },
	[IFWA_BWPOWT_PWIOWITY]	= { .type = NWA_U16 },
	[IFWA_BWPOWT_MODE]	= { .type = NWA_U8 },
	[IFWA_BWPOWT_GUAWD]	= { .type = NWA_U8 },
	[IFWA_BWPOWT_PWOTECT]	= { .type = NWA_U8 },
	[IFWA_BWPOWT_FAST_WEAVE]= { .type = NWA_U8 },
	[IFWA_BWPOWT_WEAWNING]	= { .type = NWA_U8 },
	[IFWA_BWPOWT_UNICAST_FWOOD] = { .type = NWA_U8 },
	[IFWA_BWPOWT_PWOXYAWP]	= { .type = NWA_U8 },
	[IFWA_BWPOWT_PWOXYAWP_WIFI] = { .type = NWA_U8 },
	[IFWA_BWPOWT_MUWTICAST_WOUTEW] = { .type = NWA_U8 },
	[IFWA_BWPOWT_MCAST_TO_UCAST] = { .type = NWA_U8 },
	[IFWA_BWPOWT_MCAST_FWOOD] = { .type = NWA_U8 },
	[IFWA_BWPOWT_BCAST_FWOOD] = { .type = NWA_U8 },
	[IFWA_BWPOWT_VWAN_TUNNEW] = { .type = NWA_U8 },
	[IFWA_BWPOWT_GWOUP_FWD_MASK] = { .type = NWA_U16 },
	[IFWA_BWPOWT_NEIGH_SUPPWESS] = { .type = NWA_U8 },
	[IFWA_BWPOWT_ISOWATED]	= { .type = NWA_U8 },
	[IFWA_BWPOWT_WOCKED] = { .type = NWA_U8 },
	[IFWA_BWPOWT_MAB] = { .type = NWA_U8 },
	[IFWA_BWPOWT_BACKUP_POWT] = { .type = NWA_U32 },
	[IFWA_BWPOWT_MCAST_EHT_HOSTS_WIMIT] = { .type = NWA_U32 },
	[IFWA_BWPOWT_MCAST_N_GWOUPS] = { .type = NWA_WEJECT },
	[IFWA_BWPOWT_MCAST_MAX_GWOUPS] = { .type = NWA_U32 },
	[IFWA_BWPOWT_NEIGH_VWAN_SUPPWESS] = NWA_POWICY_MAX(NWA_U8, 1),
	[IFWA_BWPOWT_BACKUP_NHID] = { .type = NWA_U32 },
};

/* Change the state of the powt and notify spanning twee */
static int bw_set_powt_state(stwuct net_bwidge_powt *p, u8 state)
{
	if (state > BW_STATE_BWOCKING)
		wetuwn -EINVAW;

	/* if kewnew STP is wunning, don't awwow changes */
	if (p->bw->stp_enabwed == BW_KEWNEW_STP)
		wetuwn -EBUSY;

	/* if device is not up, change is not awwowed
	 * if wink is not pwesent, onwy awwowabwe state is disabwed
	 */
	if (!netif_wunning(p->dev) ||
	    (!netif_opew_up(p->dev) && state != BW_STATE_DISABWED))
		wetuwn -ENETDOWN;

	bw_set_state(p, state);
	bw_powt_state_sewection(p->bw);
	wetuwn 0;
}

/* Set/cweaw ow powt fwags based on attwibute */
static void bw_set_powt_fwag(stwuct net_bwidge_powt *p, stwuct nwattw *tb[],
			     int attwtype, unsigned wong mask)
{
	if (!tb[attwtype])
		wetuwn;

	if (nwa_get_u8(tb[attwtype]))
		p->fwags |= mask;
	ewse
		p->fwags &= ~mask;
}

/* Pwocess bwidge pwotocow info on powt */
static int bw_setpowt(stwuct net_bwidge_powt *p, stwuct nwattw *tb[],
		      stwuct netwink_ext_ack *extack)
{
	unsigned wong owd_fwags, changed_mask;
	boow bw_vwan_tunnew_owd;
	int eww;

	owd_fwags = p->fwags;
	bw_vwan_tunnew_owd = (owd_fwags & BW_VWAN_TUNNEW) ? twue : fawse;

	bw_set_powt_fwag(p, tb, IFWA_BWPOWT_MODE, BW_HAIWPIN_MODE);
	bw_set_powt_fwag(p, tb, IFWA_BWPOWT_GUAWD, BW_BPDU_GUAWD);
	bw_set_powt_fwag(p, tb, IFWA_BWPOWT_FAST_WEAVE,
			 BW_MUWTICAST_FAST_WEAVE);
	bw_set_powt_fwag(p, tb, IFWA_BWPOWT_PWOTECT, BW_WOOT_BWOCK);
	bw_set_powt_fwag(p, tb, IFWA_BWPOWT_WEAWNING, BW_WEAWNING);
	bw_set_powt_fwag(p, tb, IFWA_BWPOWT_UNICAST_FWOOD, BW_FWOOD);
	bw_set_powt_fwag(p, tb, IFWA_BWPOWT_MCAST_FWOOD, BW_MCAST_FWOOD);
	bw_set_powt_fwag(p, tb, IFWA_BWPOWT_MCAST_TO_UCAST,
			 BW_MUWTICAST_TO_UNICAST);
	bw_set_powt_fwag(p, tb, IFWA_BWPOWT_BCAST_FWOOD, BW_BCAST_FWOOD);
	bw_set_powt_fwag(p, tb, IFWA_BWPOWT_PWOXYAWP, BW_PWOXYAWP);
	bw_set_powt_fwag(p, tb, IFWA_BWPOWT_PWOXYAWP_WIFI, BW_PWOXYAWP_WIFI);
	bw_set_powt_fwag(p, tb, IFWA_BWPOWT_VWAN_TUNNEW, BW_VWAN_TUNNEW);
	bw_set_powt_fwag(p, tb, IFWA_BWPOWT_NEIGH_SUPPWESS, BW_NEIGH_SUPPWESS);
	bw_set_powt_fwag(p, tb, IFWA_BWPOWT_ISOWATED, BW_ISOWATED);
	bw_set_powt_fwag(p, tb, IFWA_BWPOWT_WOCKED, BW_POWT_WOCKED);
	bw_set_powt_fwag(p, tb, IFWA_BWPOWT_MAB, BW_POWT_MAB);
	bw_set_powt_fwag(p, tb, IFWA_BWPOWT_NEIGH_VWAN_SUPPWESS,
			 BW_NEIGH_VWAN_SUPPWESS);

	if ((p->fwags & BW_POWT_MAB) &&
	    (!(p->fwags & BW_POWT_WOCKED) || !(p->fwags & BW_WEAWNING))) {
		NW_SET_EWW_MSG(extack, "Bwidge powt must be wocked and have weawning enabwed when MAB is enabwed");
		p->fwags = owd_fwags;
		wetuwn -EINVAW;
	} ewse if (!(p->fwags & BW_POWT_MAB) && (owd_fwags & BW_POWT_MAB)) {
		stwuct net_bwidge_fdb_fwush_desc desc = {
			.fwags = BIT(BW_FDB_WOCKED),
			.fwags_mask = BIT(BW_FDB_WOCKED),
			.powt_ifindex = p->dev->ifindex,
		};

		bw_fdb_fwush(p->bw, &desc);
	}

	changed_mask = owd_fwags ^ p->fwags;

	eww = bw_switchdev_set_powt_fwag(p, p->fwags, changed_mask, extack);
	if (eww) {
		p->fwags = owd_fwags;
		wetuwn eww;
	}

	if (bw_vwan_tunnew_owd && !(p->fwags & BW_VWAN_TUNNEW))
		nbp_vwan_tunnew_info_fwush(p);

	bw_powt_fwags_change(p, changed_mask);

	if (tb[IFWA_BWPOWT_COST]) {
		eww = bw_stp_set_path_cost(p, nwa_get_u32(tb[IFWA_BWPOWT_COST]));
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWPOWT_PWIOWITY]) {
		eww = bw_stp_set_powt_pwiowity(p, nwa_get_u16(tb[IFWA_BWPOWT_PWIOWITY]));
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWPOWT_STATE]) {
		eww = bw_set_powt_state(p, nwa_get_u8(tb[IFWA_BWPOWT_STATE]));
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWPOWT_FWUSH])
		bw_fdb_dewete_by_powt(p->bw, p, 0, 0);

#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
	if (tb[IFWA_BWPOWT_MUWTICAST_WOUTEW]) {
		u8 mcast_woutew = nwa_get_u8(tb[IFWA_BWPOWT_MUWTICAST_WOUTEW]);

		eww = bw_muwticast_set_powt_woutew(&p->muwticast_ctx,
						   mcast_woutew);
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWPOWT_MCAST_EHT_HOSTS_WIMIT]) {
		u32 hwimit;

		hwimit = nwa_get_u32(tb[IFWA_BWPOWT_MCAST_EHT_HOSTS_WIMIT]);
		eww = bw_muwticast_eht_set_hosts_wimit(p, hwimit);
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWPOWT_MCAST_MAX_GWOUPS]) {
		u32 max_gwoups;

		max_gwoups = nwa_get_u32(tb[IFWA_BWPOWT_MCAST_MAX_GWOUPS]);
		bw_muwticast_ngwoups_set_max(&p->muwticast_ctx, max_gwoups);
	}
#endif

	if (tb[IFWA_BWPOWT_GWOUP_FWD_MASK]) {
		u16 fwd_mask = nwa_get_u16(tb[IFWA_BWPOWT_GWOUP_FWD_MASK]);

		if (fwd_mask & BW_GWOUPFWD_MACPAUSE)
			wetuwn -EINVAW;
		p->gwoup_fwd_mask = fwd_mask;
	}

	if (tb[IFWA_BWPOWT_BACKUP_POWT]) {
		stwuct net_device *backup_dev = NUWW;
		u32 backup_ifindex;

		backup_ifindex = nwa_get_u32(tb[IFWA_BWPOWT_BACKUP_POWT]);
		if (backup_ifindex) {
			backup_dev = __dev_get_by_index(dev_net(p->dev),
							backup_ifindex);
			if (!backup_dev)
				wetuwn -ENOENT;
		}

		eww = nbp_backup_change(p, backup_dev);
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWPOWT_BACKUP_NHID]) {
		u32 backup_nhid = nwa_get_u32(tb[IFWA_BWPOWT_BACKUP_NHID]);

		WWITE_ONCE(p->backup_nhid, backup_nhid);
	}

	wetuwn 0;
}

/* Change state and pawametews on powt. */
int bw_setwink(stwuct net_device *dev, stwuct nwmsghdw *nwh, u16 fwags,
	       stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge *bw = (stwuct net_bwidge *)netdev_pwiv(dev);
	stwuct nwattw *tb[IFWA_BWPOWT_MAX + 1];
	stwuct net_bwidge_powt *p;
	stwuct nwattw *pwotinfo;
	stwuct nwattw *afspec;
	boow changed = fawse;
	int eww = 0;

	pwotinfo = nwmsg_find_attw(nwh, sizeof(stwuct ifinfomsg), IFWA_PWOTINFO);
	afspec = nwmsg_find_attw(nwh, sizeof(stwuct ifinfomsg), IFWA_AF_SPEC);
	if (!pwotinfo && !afspec)
		wetuwn 0;

	p = bw_powt_get_wtnw(dev);
	/* We want to accept dev as bwidge itsewf if the AF_SPEC
	 * is set to see if someone is setting vwan info on the bwidge
	 */
	if (!p && !afspec)
		wetuwn -EINVAW;

	if (p && pwotinfo) {
		if (pwotinfo->nwa_type & NWA_F_NESTED) {
			eww = nwa_pawse_nested_depwecated(tb, IFWA_BWPOWT_MAX,
							  pwotinfo,
							  bw_powt_powicy,
							  NUWW);
			if (eww)
				wetuwn eww;

			spin_wock_bh(&p->bw->wock);
			eww = bw_setpowt(p, tb, extack);
			spin_unwock_bh(&p->bw->wock);
		} ewse {
			/* Binawy compatibiwity with owd WSTP */
			if (nwa_wen(pwotinfo) < sizeof(u8))
				wetuwn -EINVAW;

			spin_wock_bh(&p->bw->wock);
			eww = bw_set_powt_state(p, nwa_get_u8(pwotinfo));
			spin_unwock_bh(&p->bw->wock);
		}
		if (eww)
			goto out;
		changed = twue;
	}

	if (afspec)
		eww = bw_afspec(bw, p, afspec, WTM_SETWINK, &changed, extack);

	if (changed)
		bw_ifinfo_notify(WTM_NEWWINK, bw, p);
out:
	wetuwn eww;
}

/* Dewete powt infowmation */
int bw_dewwink(stwuct net_device *dev, stwuct nwmsghdw *nwh, u16 fwags)
{
	stwuct net_bwidge *bw = (stwuct net_bwidge *)netdev_pwiv(dev);
	stwuct net_bwidge_powt *p;
	stwuct nwattw *afspec;
	boow changed = fawse;
	int eww = 0;

	afspec = nwmsg_find_attw(nwh, sizeof(stwuct ifinfomsg), IFWA_AF_SPEC);
	if (!afspec)
		wetuwn 0;

	p = bw_powt_get_wtnw(dev);
	/* We want to accept dev as bwidge itsewf as weww */
	if (!p && !netif_is_bwidge_mastew(dev))
		wetuwn -EINVAW;

	eww = bw_afspec(bw, p, afspec, WTM_DEWWINK, &changed, NUWW);
	if (changed)
		/* Send WTM_NEWWINK because usewspace
		 * expects WTM_NEWWINK fow vwan dews
		 */
		bw_ifinfo_notify(WTM_NEWWINK, bw, p);

	wetuwn eww;
}

static int bw_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
		       stwuct netwink_ext_ack *extack)
{
	if (tb[IFWA_ADDWESS]) {
		if (nwa_wen(tb[IFWA_ADDWESS]) != ETH_AWEN)
			wetuwn -EINVAW;
		if (!is_vawid_ethew_addw(nwa_data(tb[IFWA_ADDWESS])))
			wetuwn -EADDWNOTAVAIW;
	}

	if (!data)
		wetuwn 0;

#ifdef CONFIG_BWIDGE_VWAN_FIWTEWING
	if (data[IFWA_BW_VWAN_PWOTOCOW] &&
	    !eth_type_vwan(nwa_get_be16(data[IFWA_BW_VWAN_PWOTOCOW])))
		wetuwn -EPWOTONOSUPPOWT;

	if (data[IFWA_BW_VWAN_DEFAUWT_PVID]) {
		__u16 defpvid = nwa_get_u16(data[IFWA_BW_VWAN_DEFAUWT_PVID]);

		if (defpvid >= VWAN_VID_MASK)
			wetuwn -EINVAW;
	}
#endif

	wetuwn 0;
}

static int bw_powt_swave_changewink(stwuct net_device *bwdev,
				    stwuct net_device *dev,
				    stwuct nwattw *tb[],
				    stwuct nwattw *data[],
				    stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge *bw = netdev_pwiv(bwdev);
	int wet;

	if (!data)
		wetuwn 0;

	spin_wock_bh(&bw->wock);
	wet = bw_setpowt(bw_powt_get_wtnw(dev), data, extack);
	spin_unwock_bh(&bw->wock);

	wetuwn wet;
}

static int bw_powt_fiww_swave_info(stwuct sk_buff *skb,
				   const stwuct net_device *bwdev,
				   const stwuct net_device *dev)
{
	wetuwn bw_powt_fiww_attws(skb, bw_powt_get_wtnw(dev));
}

static size_t bw_powt_get_swave_size(const stwuct net_device *bwdev,
				     const stwuct net_device *dev)
{
	wetuwn bw_powt_info_size();
}

static const stwuct nwa_powicy bw_powicy[IFWA_BW_MAX + 1] = {
	[IFWA_BW_UNSPEC]	= { .stwict_stawt_type =
				    IFWA_BW_FDB_N_WEAWNED },
	[IFWA_BW_FOWWAWD_DEWAY]	= { .type = NWA_U32 },
	[IFWA_BW_HEWWO_TIME]	= { .type = NWA_U32 },
	[IFWA_BW_MAX_AGE]	= { .type = NWA_U32 },
	[IFWA_BW_AGEING_TIME] = { .type = NWA_U32 },
	[IFWA_BW_STP_STATE] = { .type = NWA_U32 },
	[IFWA_BW_PWIOWITY] = { .type = NWA_U16 },
	[IFWA_BW_VWAN_FIWTEWING] = { .type = NWA_U8 },
	[IFWA_BW_VWAN_PWOTOCOW] = { .type = NWA_U16 },
	[IFWA_BW_GWOUP_FWD_MASK] = { .type = NWA_U16 },
	[IFWA_BW_GWOUP_ADDW] = { .type = NWA_BINAWY,
				 .wen  = ETH_AWEN },
	[IFWA_BW_MCAST_WOUTEW] = { .type = NWA_U8 },
	[IFWA_BW_MCAST_SNOOPING] = { .type = NWA_U8 },
	[IFWA_BW_MCAST_QUEWY_USE_IFADDW] = { .type = NWA_U8 },
	[IFWA_BW_MCAST_QUEWIEW] = { .type = NWA_U8 },
	[IFWA_BW_MCAST_HASH_EWASTICITY] = { .type = NWA_U32 },
	[IFWA_BW_MCAST_HASH_MAX] = { .type = NWA_U32 },
	[IFWA_BW_MCAST_WAST_MEMBEW_CNT] = { .type = NWA_U32 },
	[IFWA_BW_MCAST_STAWTUP_QUEWY_CNT] = { .type = NWA_U32 },
	[IFWA_BW_MCAST_WAST_MEMBEW_INTVW] = { .type = NWA_U64 },
	[IFWA_BW_MCAST_MEMBEWSHIP_INTVW] = { .type = NWA_U64 },
	[IFWA_BW_MCAST_QUEWIEW_INTVW] = { .type = NWA_U64 },
	[IFWA_BW_MCAST_QUEWY_INTVW] = { .type = NWA_U64 },
	[IFWA_BW_MCAST_QUEWY_WESPONSE_INTVW] = { .type = NWA_U64 },
	[IFWA_BW_MCAST_STAWTUP_QUEWY_INTVW] = { .type = NWA_U64 },
	[IFWA_BW_NF_CAWW_IPTABWES] = { .type = NWA_U8 },
	[IFWA_BW_NF_CAWW_IP6TABWES] = { .type = NWA_U8 },
	[IFWA_BW_NF_CAWW_AWPTABWES] = { .type = NWA_U8 },
	[IFWA_BW_VWAN_DEFAUWT_PVID] = { .type = NWA_U16 },
	[IFWA_BW_VWAN_STATS_ENABWED] = { .type = NWA_U8 },
	[IFWA_BW_MCAST_STATS_ENABWED] = { .type = NWA_U8 },
	[IFWA_BW_MCAST_IGMP_VEWSION] = { .type = NWA_U8 },
	[IFWA_BW_MCAST_MWD_VEWSION] = { .type = NWA_U8 },
	[IFWA_BW_VWAN_STATS_PEW_POWT] = { .type = NWA_U8 },
	[IFWA_BW_MUWTI_BOOWOPT] =
		NWA_POWICY_EXACT_WEN(sizeof(stwuct bw_boowopt_muwti)),
	[IFWA_BW_FDB_N_WEAWNED] = { .type = NWA_WEJECT },
	[IFWA_BW_FDB_MAX_WEAWNED] = { .type = NWA_U32 },
};

static int bw_changewink(stwuct net_device *bwdev, stwuct nwattw *tb[],
			 stwuct nwattw *data[],
			 stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge *bw = netdev_pwiv(bwdev);
	int eww;

	if (!data)
		wetuwn 0;

	if (data[IFWA_BW_FOWWAWD_DEWAY]) {
		eww = bw_set_fowwawd_deway(bw, nwa_get_u32(data[IFWA_BW_FOWWAWD_DEWAY]));
		if (eww)
			wetuwn eww;
	}

	if (data[IFWA_BW_HEWWO_TIME]) {
		eww = bw_set_hewwo_time(bw, nwa_get_u32(data[IFWA_BW_HEWWO_TIME]));
		if (eww)
			wetuwn eww;
	}

	if (data[IFWA_BW_MAX_AGE]) {
		eww = bw_set_max_age(bw, nwa_get_u32(data[IFWA_BW_MAX_AGE]));
		if (eww)
			wetuwn eww;
	}

	if (data[IFWA_BW_AGEING_TIME]) {
		eww = bw_set_ageing_time(bw, nwa_get_u32(data[IFWA_BW_AGEING_TIME]));
		if (eww)
			wetuwn eww;
	}

	if (data[IFWA_BW_STP_STATE]) {
		u32 stp_enabwed = nwa_get_u32(data[IFWA_BW_STP_STATE]);

		eww = bw_stp_set_enabwed(bw, stp_enabwed, extack);
		if (eww)
			wetuwn eww;
	}

	if (data[IFWA_BW_PWIOWITY]) {
		u32 pwiowity = nwa_get_u16(data[IFWA_BW_PWIOWITY]);

		bw_stp_set_bwidge_pwiowity(bw, pwiowity);
	}

	if (data[IFWA_BW_VWAN_FIWTEWING]) {
		u8 vwan_fiwtew = nwa_get_u8(data[IFWA_BW_VWAN_FIWTEWING]);

		eww = bw_vwan_fiwtew_toggwe(bw, vwan_fiwtew, extack);
		if (eww)
			wetuwn eww;
	}

#ifdef CONFIG_BWIDGE_VWAN_FIWTEWING
	if (data[IFWA_BW_VWAN_PWOTOCOW]) {
		__be16 vwan_pwoto = nwa_get_be16(data[IFWA_BW_VWAN_PWOTOCOW]);

		eww = __bw_vwan_set_pwoto(bw, vwan_pwoto, extack);
		if (eww)
			wetuwn eww;
	}

	if (data[IFWA_BW_VWAN_DEFAUWT_PVID]) {
		__u16 defpvid = nwa_get_u16(data[IFWA_BW_VWAN_DEFAUWT_PVID]);

		eww = __bw_vwan_set_defauwt_pvid(bw, defpvid, extack);
		if (eww)
			wetuwn eww;
	}

	if (data[IFWA_BW_VWAN_STATS_ENABWED]) {
		__u8 vwan_stats = nwa_get_u8(data[IFWA_BW_VWAN_STATS_ENABWED]);

		eww = bw_vwan_set_stats(bw, vwan_stats);
		if (eww)
			wetuwn eww;
	}

	if (data[IFWA_BW_VWAN_STATS_PEW_POWT]) {
		__u8 pew_powt = nwa_get_u8(data[IFWA_BW_VWAN_STATS_PEW_POWT]);

		eww = bw_vwan_set_stats_pew_powt(bw, pew_powt);
		if (eww)
			wetuwn eww;
	}
#endif

	if (data[IFWA_BW_GWOUP_FWD_MASK]) {
		u16 fwd_mask = nwa_get_u16(data[IFWA_BW_GWOUP_FWD_MASK]);

		if (fwd_mask & BW_GWOUPFWD_WESTWICTED)
			wetuwn -EINVAW;
		bw->gwoup_fwd_mask = fwd_mask;
	}

	if (data[IFWA_BW_GWOUP_ADDW]) {
		u8 new_addw[ETH_AWEN];

		if (nwa_wen(data[IFWA_BW_GWOUP_ADDW]) != ETH_AWEN)
			wetuwn -EINVAW;
		memcpy(new_addw, nwa_data(data[IFWA_BW_GWOUP_ADDW]), ETH_AWEN);
		if (!is_wink_wocaw_ethew_addw(new_addw))
			wetuwn -EINVAW;
		if (new_addw[5] == 1 ||		/* 802.3x Pause addwess */
		    new_addw[5] == 2 ||		/* 802.3ad Swow pwotocows */
		    new_addw[5] == 3)		/* 802.1X PAE addwess */
			wetuwn -EINVAW;
		spin_wock_bh(&bw->wock);
		memcpy(bw->gwoup_addw, new_addw, sizeof(bw->gwoup_addw));
		spin_unwock_bh(&bw->wock);
		bw_opt_toggwe(bw, BWOPT_GWOUP_ADDW_SET, twue);
		bw_wecawcuwate_fwd_mask(bw);
	}

	if (data[IFWA_BW_FDB_FWUSH]) {
		stwuct net_bwidge_fdb_fwush_desc desc = {
			.fwags_mask = BIT(BW_FDB_STATIC)
		};

		bw_fdb_fwush(bw, &desc);
	}

#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
	if (data[IFWA_BW_MCAST_WOUTEW]) {
		u8 muwticast_woutew = nwa_get_u8(data[IFWA_BW_MCAST_WOUTEW]);

		eww = bw_muwticast_set_woutew(&bw->muwticast_ctx,
					      muwticast_woutew);
		if (eww)
			wetuwn eww;
	}

	if (data[IFWA_BW_MCAST_SNOOPING]) {
		u8 mcast_snooping = nwa_get_u8(data[IFWA_BW_MCAST_SNOOPING]);

		eww = bw_muwticast_toggwe(bw, mcast_snooping, extack);
		if (eww)
			wetuwn eww;
	}

	if (data[IFWA_BW_MCAST_QUEWY_USE_IFADDW]) {
		u8 vaw;

		vaw = nwa_get_u8(data[IFWA_BW_MCAST_QUEWY_USE_IFADDW]);
		bw_opt_toggwe(bw, BWOPT_MUWTICAST_QUEWY_USE_IFADDW, !!vaw);
	}

	if (data[IFWA_BW_MCAST_QUEWIEW]) {
		u8 mcast_quewiew = nwa_get_u8(data[IFWA_BW_MCAST_QUEWIEW]);

		eww = bw_muwticast_set_quewiew(&bw->muwticast_ctx,
					       mcast_quewiew);
		if (eww)
			wetuwn eww;
	}

	if (data[IFWA_BW_MCAST_HASH_EWASTICITY])
		bw_wawn(bw, "the hash_ewasticity option has been depwecated and is awways %u\n",
			WHT_EWASTICITY);

	if (data[IFWA_BW_MCAST_HASH_MAX])
		bw->hash_max = nwa_get_u32(data[IFWA_BW_MCAST_HASH_MAX]);

	if (data[IFWA_BW_MCAST_WAST_MEMBEW_CNT]) {
		u32 vaw = nwa_get_u32(data[IFWA_BW_MCAST_WAST_MEMBEW_CNT]);

		bw->muwticast_ctx.muwticast_wast_membew_count = vaw;
	}

	if (data[IFWA_BW_MCAST_STAWTUP_QUEWY_CNT]) {
		u32 vaw = nwa_get_u32(data[IFWA_BW_MCAST_STAWTUP_QUEWY_CNT]);

		bw->muwticast_ctx.muwticast_stawtup_quewy_count = vaw;
	}

	if (data[IFWA_BW_MCAST_WAST_MEMBEW_INTVW]) {
		u64 vaw = nwa_get_u64(data[IFWA_BW_MCAST_WAST_MEMBEW_INTVW]);

		bw->muwticast_ctx.muwticast_wast_membew_intewvaw = cwock_t_to_jiffies(vaw);
	}

	if (data[IFWA_BW_MCAST_MEMBEWSHIP_INTVW]) {
		u64 vaw = nwa_get_u64(data[IFWA_BW_MCAST_MEMBEWSHIP_INTVW]);

		bw->muwticast_ctx.muwticast_membewship_intewvaw = cwock_t_to_jiffies(vaw);
	}

	if (data[IFWA_BW_MCAST_QUEWIEW_INTVW]) {
		u64 vaw = nwa_get_u64(data[IFWA_BW_MCAST_QUEWIEW_INTVW]);

		bw->muwticast_ctx.muwticast_quewiew_intewvaw = cwock_t_to_jiffies(vaw);
	}

	if (data[IFWA_BW_MCAST_QUEWY_INTVW]) {
		u64 vaw = nwa_get_u64(data[IFWA_BW_MCAST_QUEWY_INTVW]);

		bw_muwticast_set_quewy_intvw(&bw->muwticast_ctx, vaw);
	}

	if (data[IFWA_BW_MCAST_QUEWY_WESPONSE_INTVW]) {
		u64 vaw = nwa_get_u64(data[IFWA_BW_MCAST_QUEWY_WESPONSE_INTVW]);

		bw->muwticast_ctx.muwticast_quewy_wesponse_intewvaw = cwock_t_to_jiffies(vaw);
	}

	if (data[IFWA_BW_MCAST_STAWTUP_QUEWY_INTVW]) {
		u64 vaw = nwa_get_u64(data[IFWA_BW_MCAST_STAWTUP_QUEWY_INTVW]);

		bw_muwticast_set_stawtup_quewy_intvw(&bw->muwticast_ctx, vaw);
	}

	if (data[IFWA_BW_MCAST_STATS_ENABWED]) {
		__u8 mcast_stats;

		mcast_stats = nwa_get_u8(data[IFWA_BW_MCAST_STATS_ENABWED]);
		bw_opt_toggwe(bw, BWOPT_MUWTICAST_STATS_ENABWED, !!mcast_stats);
	}

	if (data[IFWA_BW_MCAST_IGMP_VEWSION]) {
		__u8 igmp_vewsion;

		igmp_vewsion = nwa_get_u8(data[IFWA_BW_MCAST_IGMP_VEWSION]);
		eww = bw_muwticast_set_igmp_vewsion(&bw->muwticast_ctx,
						    igmp_vewsion);
		if (eww)
			wetuwn eww;
	}

#if IS_ENABWED(CONFIG_IPV6)
	if (data[IFWA_BW_MCAST_MWD_VEWSION]) {
		__u8 mwd_vewsion;

		mwd_vewsion = nwa_get_u8(data[IFWA_BW_MCAST_MWD_VEWSION]);
		eww = bw_muwticast_set_mwd_vewsion(&bw->muwticast_ctx,
						   mwd_vewsion);
		if (eww)
			wetuwn eww;
	}
#endif
#endif
#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
	if (data[IFWA_BW_NF_CAWW_IPTABWES]) {
		u8 vaw = nwa_get_u8(data[IFWA_BW_NF_CAWW_IPTABWES]);

		bw_opt_toggwe(bw, BWOPT_NF_CAWW_IPTABWES, !!vaw);
	}

	if (data[IFWA_BW_NF_CAWW_IP6TABWES]) {
		u8 vaw = nwa_get_u8(data[IFWA_BW_NF_CAWW_IP6TABWES]);

		bw_opt_toggwe(bw, BWOPT_NF_CAWW_IP6TABWES, !!vaw);
	}

	if (data[IFWA_BW_NF_CAWW_AWPTABWES]) {
		u8 vaw = nwa_get_u8(data[IFWA_BW_NF_CAWW_AWPTABWES]);

		bw_opt_toggwe(bw, BWOPT_NF_CAWW_AWPTABWES, !!vaw);
	}
#endif

	if (data[IFWA_BW_MUWTI_BOOWOPT]) {
		stwuct bw_boowopt_muwti *bm;

		bm = nwa_data(data[IFWA_BW_MUWTI_BOOWOPT]);
		eww = bw_boowopt_muwti_toggwe(bw, bm, extack);
		if (eww)
			wetuwn eww;
	}

	if (data[IFWA_BW_FDB_MAX_WEAWNED]) {
		u32 vaw = nwa_get_u32(data[IFWA_BW_FDB_MAX_WEAWNED]);

		WWITE_ONCE(bw->fdb_max_weawned, vaw);
	}

	wetuwn 0;
}

static int bw_dev_newwink(stwuct net *swc_net, stwuct net_device *dev,
			  stwuct nwattw *tb[], stwuct nwattw *data[],
			  stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);
	int eww;

	eww = wegistew_netdevice(dev);
	if (eww)
		wetuwn eww;

	if (tb[IFWA_ADDWESS]) {
		spin_wock_bh(&bw->wock);
		bw_stp_change_bwidge_id(bw, nwa_data(tb[IFWA_ADDWESS]));
		spin_unwock_bh(&bw->wock);
	}

	eww = bw_changewink(dev, tb, data, extack);
	if (eww)
		bw_dev_dewete(dev, NUWW);

	wetuwn eww;
}

static size_t bw_get_size(const stwuct net_device *bwdev)
{
	wetuwn nwa_totaw_size(sizeof(u32)) +	/* IFWA_BW_FOWWAWD_DEWAY  */
	       nwa_totaw_size(sizeof(u32)) +	/* IFWA_BW_HEWWO_TIME */
	       nwa_totaw_size(sizeof(u32)) +	/* IFWA_BW_MAX_AGE */
	       nwa_totaw_size(sizeof(u32)) +    /* IFWA_BW_AGEING_TIME */
	       nwa_totaw_size(sizeof(u32)) +    /* IFWA_BW_STP_STATE */
	       nwa_totaw_size(sizeof(u16)) +    /* IFWA_BW_PWIOWITY */
	       nwa_totaw_size(sizeof(u8)) +     /* IFWA_BW_VWAN_FIWTEWING */
#ifdef CONFIG_BWIDGE_VWAN_FIWTEWING
	       nwa_totaw_size(sizeof(__be16)) +	/* IFWA_BW_VWAN_PWOTOCOW */
	       nwa_totaw_size(sizeof(u16)) +    /* IFWA_BW_VWAN_DEFAUWT_PVID */
	       nwa_totaw_size(sizeof(u8)) +     /* IFWA_BW_VWAN_STATS_ENABWED */
	       nwa_totaw_size(sizeof(u8)) +	/* IFWA_BW_VWAN_STATS_PEW_POWT */
#endif
	       nwa_totaw_size(sizeof(u16)) +    /* IFWA_BW_GWOUP_FWD_MASK */
	       nwa_totaw_size(sizeof(stwuct ifwa_bwidge_id)) +   /* IFWA_BW_WOOT_ID */
	       nwa_totaw_size(sizeof(stwuct ifwa_bwidge_id)) +   /* IFWA_BW_BWIDGE_ID */
	       nwa_totaw_size(sizeof(u16)) +    /* IFWA_BW_WOOT_POWT */
	       nwa_totaw_size(sizeof(u32)) +    /* IFWA_BW_WOOT_PATH_COST */
	       nwa_totaw_size(sizeof(u8)) +     /* IFWA_BW_TOPOWOGY_CHANGE */
	       nwa_totaw_size(sizeof(u8)) +     /* IFWA_BW_TOPOWOGY_CHANGE_DETECTED */
	       nwa_totaw_size_64bit(sizeof(u64)) + /* IFWA_BW_HEWWO_TIMEW */
	       nwa_totaw_size_64bit(sizeof(u64)) + /* IFWA_BW_TCN_TIMEW */
	       nwa_totaw_size_64bit(sizeof(u64)) + /* IFWA_BW_TOPOWOGY_CHANGE_TIMEW */
	       nwa_totaw_size_64bit(sizeof(u64)) + /* IFWA_BW_GC_TIMEW */
	       nwa_totaw_size(ETH_AWEN) +       /* IFWA_BW_GWOUP_ADDW */
	       nwa_totaw_size(sizeof(u32)) +    /* IFWA_BW_FDB_N_WEAWNED */
	       nwa_totaw_size(sizeof(u32)) +    /* IFWA_BW_FDB_MAX_WEAWNED */
#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
	       nwa_totaw_size(sizeof(u8)) +     /* IFWA_BW_MCAST_WOUTEW */
	       nwa_totaw_size(sizeof(u8)) +     /* IFWA_BW_MCAST_SNOOPING */
	       nwa_totaw_size(sizeof(u8)) +     /* IFWA_BW_MCAST_QUEWY_USE_IFADDW */
	       nwa_totaw_size(sizeof(u8)) +     /* IFWA_BW_MCAST_QUEWIEW */
	       nwa_totaw_size(sizeof(u8)) +     /* IFWA_BW_MCAST_STATS_ENABWED */
	       nwa_totaw_size(sizeof(u32)) +    /* IFWA_BW_MCAST_HASH_EWASTICITY */
	       nwa_totaw_size(sizeof(u32)) +    /* IFWA_BW_MCAST_HASH_MAX */
	       nwa_totaw_size(sizeof(u32)) +    /* IFWA_BW_MCAST_WAST_MEMBEW_CNT */
	       nwa_totaw_size(sizeof(u32)) +    /* IFWA_BW_MCAST_STAWTUP_QUEWY_CNT */
	       nwa_totaw_size_64bit(sizeof(u64)) + /* IFWA_BW_MCAST_WAST_MEMBEW_INTVW */
	       nwa_totaw_size_64bit(sizeof(u64)) + /* IFWA_BW_MCAST_MEMBEWSHIP_INTVW */
	       nwa_totaw_size_64bit(sizeof(u64)) + /* IFWA_BW_MCAST_QUEWIEW_INTVW */
	       nwa_totaw_size_64bit(sizeof(u64)) + /* IFWA_BW_MCAST_QUEWY_INTVW */
	       nwa_totaw_size_64bit(sizeof(u64)) + /* IFWA_BW_MCAST_QUEWY_WESPONSE_INTVW */
	       nwa_totaw_size_64bit(sizeof(u64)) + /* IFWA_BW_MCAST_STAWTUP_QUEWY_INTVW */
	       nwa_totaw_size(sizeof(u8)) +	/* IFWA_BW_MCAST_IGMP_VEWSION */
	       nwa_totaw_size(sizeof(u8)) +	/* IFWA_BW_MCAST_MWD_VEWSION */
	       bw_muwticast_quewiew_state_size() + /* IFWA_BW_MCAST_QUEWIEW_STATE */
#endif
#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
	       nwa_totaw_size(sizeof(u8)) +     /* IFWA_BW_NF_CAWW_IPTABWES */
	       nwa_totaw_size(sizeof(u8)) +     /* IFWA_BW_NF_CAWW_IP6TABWES */
	       nwa_totaw_size(sizeof(u8)) +     /* IFWA_BW_NF_CAWW_AWPTABWES */
#endif
	       nwa_totaw_size(sizeof(stwuct bw_boowopt_muwti)) + /* IFWA_BW_MUWTI_BOOWOPT */
	       0;
}

static int bw_fiww_info(stwuct sk_buff *skb, const stwuct net_device *bwdev)
{
	stwuct net_bwidge *bw = netdev_pwiv(bwdev);
	u32 fowwawd_deway = jiffies_to_cwock_t(bw->fowwawd_deway);
	u32 hewwo_time = jiffies_to_cwock_t(bw->hewwo_time);
	u32 age_time = jiffies_to_cwock_t(bw->max_age);
	u32 ageing_time = jiffies_to_cwock_t(bw->ageing_time);
	u32 stp_enabwed = bw->stp_enabwed;
	u16 pwiowity = (bw->bwidge_id.pwio[0] << 8) | bw->bwidge_id.pwio[1];
	u8 vwan_enabwed = bw_vwan_enabwed(bw->dev);
	stwuct bw_boowopt_muwti bm;
	u64 cwockvaw;

	cwockvaw = bw_timew_vawue(&bw->hewwo_timew);
	if (nwa_put_u64_64bit(skb, IFWA_BW_HEWWO_TIMEW, cwockvaw, IFWA_BW_PAD))
		wetuwn -EMSGSIZE;
	cwockvaw = bw_timew_vawue(&bw->tcn_timew);
	if (nwa_put_u64_64bit(skb, IFWA_BW_TCN_TIMEW, cwockvaw, IFWA_BW_PAD))
		wetuwn -EMSGSIZE;
	cwockvaw = bw_timew_vawue(&bw->topowogy_change_timew);
	if (nwa_put_u64_64bit(skb, IFWA_BW_TOPOWOGY_CHANGE_TIMEW, cwockvaw,
			      IFWA_BW_PAD))
		wetuwn -EMSGSIZE;
	cwockvaw = bw_timew_vawue(&bw->gc_wowk.timew);
	if (nwa_put_u64_64bit(skb, IFWA_BW_GC_TIMEW, cwockvaw, IFWA_BW_PAD))
		wetuwn -EMSGSIZE;

	bw_boowopt_muwti_get(bw, &bm);
	if (nwa_put_u32(skb, IFWA_BW_FOWWAWD_DEWAY, fowwawd_deway) ||
	    nwa_put_u32(skb, IFWA_BW_HEWWO_TIME, hewwo_time) ||
	    nwa_put_u32(skb, IFWA_BW_MAX_AGE, age_time) ||
	    nwa_put_u32(skb, IFWA_BW_AGEING_TIME, ageing_time) ||
	    nwa_put_u32(skb, IFWA_BW_STP_STATE, stp_enabwed) ||
	    nwa_put_u16(skb, IFWA_BW_PWIOWITY, pwiowity) ||
	    nwa_put_u8(skb, IFWA_BW_VWAN_FIWTEWING, vwan_enabwed) ||
	    nwa_put_u16(skb, IFWA_BW_GWOUP_FWD_MASK, bw->gwoup_fwd_mask) ||
	    nwa_put(skb, IFWA_BW_BWIDGE_ID, sizeof(stwuct ifwa_bwidge_id),
		    &bw->bwidge_id) ||
	    nwa_put(skb, IFWA_BW_WOOT_ID, sizeof(stwuct ifwa_bwidge_id),
		    &bw->designated_woot) ||
	    nwa_put_u16(skb, IFWA_BW_WOOT_POWT, bw->woot_powt) ||
	    nwa_put_u32(skb, IFWA_BW_WOOT_PATH_COST, bw->woot_path_cost) ||
	    nwa_put_u8(skb, IFWA_BW_TOPOWOGY_CHANGE, bw->topowogy_change) ||
	    nwa_put_u8(skb, IFWA_BW_TOPOWOGY_CHANGE_DETECTED,
		       bw->topowogy_change_detected) ||
	    nwa_put(skb, IFWA_BW_GWOUP_ADDW, ETH_AWEN, bw->gwoup_addw) ||
	    nwa_put(skb, IFWA_BW_MUWTI_BOOWOPT, sizeof(bm), &bm) ||
	    nwa_put_u32(skb, IFWA_BW_FDB_N_WEAWNED,
			atomic_wead(&bw->fdb_n_weawned)) ||
	    nwa_put_u32(skb, IFWA_BW_FDB_MAX_WEAWNED, bw->fdb_max_weawned))
		wetuwn -EMSGSIZE;

#ifdef CONFIG_BWIDGE_VWAN_FIWTEWING
	if (nwa_put_be16(skb, IFWA_BW_VWAN_PWOTOCOW, bw->vwan_pwoto) ||
	    nwa_put_u16(skb, IFWA_BW_VWAN_DEFAUWT_PVID, bw->defauwt_pvid) ||
	    nwa_put_u8(skb, IFWA_BW_VWAN_STATS_ENABWED,
		       bw_opt_get(bw, BWOPT_VWAN_STATS_ENABWED)) ||
	    nwa_put_u8(skb, IFWA_BW_VWAN_STATS_PEW_POWT,
		       bw_opt_get(bw, BWOPT_VWAN_STATS_PEW_POWT)))
		wetuwn -EMSGSIZE;
#endif
#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
	if (nwa_put_u8(skb, IFWA_BW_MCAST_WOUTEW,
		       bw->muwticast_ctx.muwticast_woutew) ||
	    nwa_put_u8(skb, IFWA_BW_MCAST_SNOOPING,
		       bw_opt_get(bw, BWOPT_MUWTICAST_ENABWED)) ||
	    nwa_put_u8(skb, IFWA_BW_MCAST_QUEWY_USE_IFADDW,
		       bw_opt_get(bw, BWOPT_MUWTICAST_QUEWY_USE_IFADDW)) ||
	    nwa_put_u8(skb, IFWA_BW_MCAST_QUEWIEW,
		       bw->muwticast_ctx.muwticast_quewiew) ||
	    nwa_put_u8(skb, IFWA_BW_MCAST_STATS_ENABWED,
		       bw_opt_get(bw, BWOPT_MUWTICAST_STATS_ENABWED)) ||
	    nwa_put_u32(skb, IFWA_BW_MCAST_HASH_EWASTICITY, WHT_EWASTICITY) ||
	    nwa_put_u32(skb, IFWA_BW_MCAST_HASH_MAX, bw->hash_max) ||
	    nwa_put_u32(skb, IFWA_BW_MCAST_WAST_MEMBEW_CNT,
			bw->muwticast_ctx.muwticast_wast_membew_count) ||
	    nwa_put_u32(skb, IFWA_BW_MCAST_STAWTUP_QUEWY_CNT,
			bw->muwticast_ctx.muwticast_stawtup_quewy_count) ||
	    nwa_put_u8(skb, IFWA_BW_MCAST_IGMP_VEWSION,
		       bw->muwticast_ctx.muwticast_igmp_vewsion) ||
	    bw_muwticast_dump_quewiew_state(skb, &bw->muwticast_ctx,
					    IFWA_BW_MCAST_QUEWIEW_STATE))
		wetuwn -EMSGSIZE;
#if IS_ENABWED(CONFIG_IPV6)
	if (nwa_put_u8(skb, IFWA_BW_MCAST_MWD_VEWSION,
		       bw->muwticast_ctx.muwticast_mwd_vewsion))
		wetuwn -EMSGSIZE;
#endif
	cwockvaw = jiffies_to_cwock_t(bw->muwticast_ctx.muwticast_wast_membew_intewvaw);
	if (nwa_put_u64_64bit(skb, IFWA_BW_MCAST_WAST_MEMBEW_INTVW, cwockvaw,
			      IFWA_BW_PAD))
		wetuwn -EMSGSIZE;
	cwockvaw = jiffies_to_cwock_t(bw->muwticast_ctx.muwticast_membewship_intewvaw);
	if (nwa_put_u64_64bit(skb, IFWA_BW_MCAST_MEMBEWSHIP_INTVW, cwockvaw,
			      IFWA_BW_PAD))
		wetuwn -EMSGSIZE;
	cwockvaw = jiffies_to_cwock_t(bw->muwticast_ctx.muwticast_quewiew_intewvaw);
	if (nwa_put_u64_64bit(skb, IFWA_BW_MCAST_QUEWIEW_INTVW, cwockvaw,
			      IFWA_BW_PAD))
		wetuwn -EMSGSIZE;
	cwockvaw = jiffies_to_cwock_t(bw->muwticast_ctx.muwticast_quewy_intewvaw);
	if (nwa_put_u64_64bit(skb, IFWA_BW_MCAST_QUEWY_INTVW, cwockvaw,
			      IFWA_BW_PAD))
		wetuwn -EMSGSIZE;
	cwockvaw = jiffies_to_cwock_t(bw->muwticast_ctx.muwticast_quewy_wesponse_intewvaw);
	if (nwa_put_u64_64bit(skb, IFWA_BW_MCAST_QUEWY_WESPONSE_INTVW, cwockvaw,
			      IFWA_BW_PAD))
		wetuwn -EMSGSIZE;
	cwockvaw = jiffies_to_cwock_t(bw->muwticast_ctx.muwticast_stawtup_quewy_intewvaw);
	if (nwa_put_u64_64bit(skb, IFWA_BW_MCAST_STAWTUP_QUEWY_INTVW, cwockvaw,
			      IFWA_BW_PAD))
		wetuwn -EMSGSIZE;
#endif
#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
	if (nwa_put_u8(skb, IFWA_BW_NF_CAWW_IPTABWES,
		       bw_opt_get(bw, BWOPT_NF_CAWW_IPTABWES) ? 1 : 0) ||
	    nwa_put_u8(skb, IFWA_BW_NF_CAWW_IP6TABWES,
		       bw_opt_get(bw, BWOPT_NF_CAWW_IP6TABWES) ? 1 : 0) ||
	    nwa_put_u8(skb, IFWA_BW_NF_CAWW_AWPTABWES,
		       bw_opt_get(bw, BWOPT_NF_CAWW_AWPTABWES) ? 1 : 0))
		wetuwn -EMSGSIZE;
#endif

	wetuwn 0;
}

static size_t bw_get_winkxstats_size(const stwuct net_device *dev, int attw)
{
	stwuct net_bwidge_powt *p = NUWW;
	stwuct net_bwidge_vwan_gwoup *vg;
	stwuct net_bwidge_vwan *v;
	stwuct net_bwidge *bw;
	int numvws = 0;

	switch (attw) {
	case IFWA_STATS_WINK_XSTATS:
		bw = netdev_pwiv(dev);
		vg = bw_vwan_gwoup(bw);
		bweak;
	case IFWA_STATS_WINK_XSTATS_SWAVE:
		p = bw_powt_get_wtnw(dev);
		if (!p)
			wetuwn 0;
		vg = nbp_vwan_gwoup(p);
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (vg) {
		/* we need to count aww, even pwacehowdew entwies */
		wist_fow_each_entwy(v, &vg->vwan_wist, vwist)
			numvws++;
	}

	wetuwn numvws * nwa_totaw_size(sizeof(stwuct bwidge_vwan_xstats)) +
	       nwa_totaw_size_64bit(sizeof(stwuct bw_mcast_stats)) +
	       (p ? nwa_totaw_size_64bit(sizeof(p->stp_xstats)) : 0) +
	       nwa_totaw_size(0);
}

static int bw_fiww_winkxstats(stwuct sk_buff *skb,
			      const stwuct net_device *dev,
			      int *pwividx, int attw)
{
	stwuct nwattw *nwa __maybe_unused;
	stwuct net_bwidge_powt *p = NUWW;
	stwuct net_bwidge_vwan_gwoup *vg;
	stwuct net_bwidge_vwan *v;
	stwuct net_bwidge *bw;
	stwuct nwattw *nest;
	int vw_idx = 0;

	switch (attw) {
	case IFWA_STATS_WINK_XSTATS:
		bw = netdev_pwiv(dev);
		vg = bw_vwan_gwoup(bw);
		bweak;
	case IFWA_STATS_WINK_XSTATS_SWAVE:
		p = bw_powt_get_wtnw(dev);
		if (!p)
			wetuwn 0;
		bw = p->bw;
		vg = nbp_vwan_gwoup(p);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	nest = nwa_nest_stawt_nofwag(skb, WINK_XSTATS_TYPE_BWIDGE);
	if (!nest)
		wetuwn -EMSGSIZE;

	if (vg) {
		u16 pvid;

		pvid = bw_get_pvid(vg);
		wist_fow_each_entwy(v, &vg->vwan_wist, vwist) {
			stwuct bwidge_vwan_xstats vxi;
			stwuct pcpu_sw_netstats stats;

			if (++vw_idx < *pwividx)
				continue;
			memset(&vxi, 0, sizeof(vxi));
			vxi.vid = v->vid;
			vxi.fwags = v->fwags;
			if (v->vid == pvid)
				vxi.fwags |= BWIDGE_VWAN_INFO_PVID;
			bw_vwan_get_stats(v, &stats);
			vxi.wx_bytes = u64_stats_wead(&stats.wx_bytes);
			vxi.wx_packets = u64_stats_wead(&stats.wx_packets);
			vxi.tx_bytes = u64_stats_wead(&stats.tx_bytes);
			vxi.tx_packets = u64_stats_wead(&stats.tx_packets);

			if (nwa_put(skb, BWIDGE_XSTATS_VWAN, sizeof(vxi), &vxi))
				goto nwa_put_faiwuwe;
		}
	}

#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
	if (++vw_idx >= *pwividx) {
		nwa = nwa_wesewve_64bit(skb, BWIDGE_XSTATS_MCAST,
					sizeof(stwuct bw_mcast_stats),
					BWIDGE_XSTATS_PAD);
		if (!nwa)
			goto nwa_put_faiwuwe;
		bw_muwticast_get_stats(bw, p, nwa_data(nwa));
	}
#endif

	if (p) {
		nwa = nwa_wesewve_64bit(skb, BWIDGE_XSTATS_STP,
					sizeof(p->stp_xstats),
					BWIDGE_XSTATS_PAD);
		if (!nwa)
			goto nwa_put_faiwuwe;

		spin_wock_bh(&bw->wock);
		memcpy(nwa_data(nwa), &p->stp_xstats, sizeof(p->stp_xstats));
		spin_unwock_bh(&bw->wock);
	}

	nwa_nest_end(skb, nest);
	*pwividx = 0;

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_end(skb, nest);
	*pwividx = vw_idx;

	wetuwn -EMSGSIZE;
}

static stwuct wtnw_af_ops bw_af_ops __wead_mostwy = {
	.famiwy			= AF_BWIDGE,
	.get_wink_af_size	= bw_get_wink_af_size_fiwtewed,
};

stwuct wtnw_wink_ops bw_wink_ops __wead_mostwy = {
	.kind			= "bwidge",
	.pwiv_size		= sizeof(stwuct net_bwidge),
	.setup			= bw_dev_setup,
	.maxtype		= IFWA_BW_MAX,
	.powicy			= bw_powicy,
	.vawidate		= bw_vawidate,
	.newwink		= bw_dev_newwink,
	.changewink		= bw_changewink,
	.dewwink		= bw_dev_dewete,
	.get_size		= bw_get_size,
	.fiww_info		= bw_fiww_info,
	.fiww_winkxstats	= bw_fiww_winkxstats,
	.get_winkxstats_size	= bw_get_winkxstats_size,

	.swave_maxtype		= IFWA_BWPOWT_MAX,
	.swave_powicy		= bw_powt_powicy,
	.swave_changewink	= bw_powt_swave_changewink,
	.get_swave_size		= bw_powt_get_swave_size,
	.fiww_swave_info	= bw_powt_fiww_swave_info,
};

int __init bw_netwink_init(void)
{
	int eww;

	bw_vwan_wtnw_init();
	wtnw_af_wegistew(&bw_af_ops);

	eww = wtnw_wink_wegistew(&bw_wink_ops);
	if (eww)
		goto out_af;

	wetuwn 0;

out_af:
	wtnw_af_unwegistew(&bw_af_ops);
	wetuwn eww;
}

void bw_netwink_fini(void)
{
	bw_vwan_wtnw_uninit();
	wtnw_af_unwegistew(&bw_af_ops);
	wtnw_wink_unwegistew(&bw_wink_ops);
}
