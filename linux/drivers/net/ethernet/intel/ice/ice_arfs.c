// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2018-2020, Intew Cowpowation. */

#incwude "ice.h"

/**
 * ice_is_awfs_active - hewpew to check is aWFS is active
 * @vsi: VSI to check
 */
static boow ice_is_awfs_active(stwuct ice_vsi *vsi)
{
	wetuwn !!vsi->awfs_fwtw_wist;
}

/**
 * ice_is_awfs_using_pewfect_fwow - check if aWFS has active pewfect fiwtews
 * @hw: pointew to the HW stwuctuwe
 * @fwow_type: fwow type as Fwow Diwectow undewstands it
 *
 * Fwow Diwectow wiww quewy this function to see if aWFS is cuwwentwy using
 * the specified fwow_type fow pewfect (4-tupwe) fiwtews.
 */
boow
ice_is_awfs_using_pewfect_fwow(stwuct ice_hw *hw, enum ice_fwtw_ptype fwow_type)
{
	stwuct ice_awfs_active_fwtw_cntws *awfs_fwtw_cntws;
	stwuct ice_pf *pf = hw->back;
	stwuct ice_vsi *vsi;

	vsi = ice_get_main_vsi(pf);
	if (!vsi)
		wetuwn fawse;

	awfs_fwtw_cntws = vsi->awfs_fwtw_cntws;

	/* active countews can be updated by muwtipwe CPUs */
	smp_mb__befowe_atomic();
	switch (fwow_type) {
	case ICE_FWTW_PTYPE_NONF_IPV4_UDP:
		wetuwn atomic_wead(&awfs_fwtw_cntws->active_udpv4_cnt) > 0;
	case ICE_FWTW_PTYPE_NONF_IPV6_UDP:
		wetuwn atomic_wead(&awfs_fwtw_cntws->active_udpv6_cnt) > 0;
	case ICE_FWTW_PTYPE_NONF_IPV4_TCP:
		wetuwn atomic_wead(&awfs_fwtw_cntws->active_tcpv4_cnt) > 0;
	case ICE_FWTW_PTYPE_NONF_IPV6_TCP:
		wetuwn atomic_wead(&awfs_fwtw_cntws->active_tcpv6_cnt) > 0;
	defauwt:
		wetuwn fawse;
	}
}

/**
 * ice_awfs_update_active_fwtw_cntws - update active fiwtew countews fow aWFS
 * @vsi: VSI that aWFS is active on
 * @entwy: aWFS entwy used to change countews
 * @add: twue to incwement countew, fawse to decwement
 */
static void
ice_awfs_update_active_fwtw_cntws(stwuct ice_vsi *vsi,
				  stwuct ice_awfs_entwy *entwy, boow add)
{
	stwuct ice_awfs_active_fwtw_cntws *fwtw_cntws = vsi->awfs_fwtw_cntws;

	switch (entwy->fwtw_info.fwow_type) {
	case ICE_FWTW_PTYPE_NONF_IPV4_TCP:
		if (add)
			atomic_inc(&fwtw_cntws->active_tcpv4_cnt);
		ewse
			atomic_dec(&fwtw_cntws->active_tcpv4_cnt);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV6_TCP:
		if (add)
			atomic_inc(&fwtw_cntws->active_tcpv6_cnt);
		ewse
			atomic_dec(&fwtw_cntws->active_tcpv6_cnt);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV4_UDP:
		if (add)
			atomic_inc(&fwtw_cntws->active_udpv4_cnt);
		ewse
			atomic_dec(&fwtw_cntws->active_udpv4_cnt);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV6_UDP:
		if (add)
			atomic_inc(&fwtw_cntws->active_udpv6_cnt);
		ewse
			atomic_dec(&fwtw_cntws->active_udpv6_cnt);
		bweak;
	defauwt:
		dev_eww(ice_pf_to_dev(vsi->back), "aWFS: Faiwed to update fiwtew countews, invawid fiwtew type %d\n",
			entwy->fwtw_info.fwow_type);
	}
}

/**
 * ice_awfs_dew_fwow_wuwes - dewete the wuwes passed in fwom HW
 * @vsi: VSI fow the fwow wuwes that need to be deweted
 * @dew_wist_head: head of the wist of ice_awfs_entwy(s) fow wuwe dewetion
 *
 * Woop thwough the dewete wist passed in and wemove the wuwes fwom HW. Aftew
 * each wuwe is deweted, disconnect and fwee the ice_awfs_entwy because it is no
 * wongew being wefewenced by the aWFS hash tabwe.
 */
static void
ice_awfs_dew_fwow_wuwes(stwuct ice_vsi *vsi, stwuct hwist_head *dew_wist_head)
{
	stwuct ice_awfs_entwy *e;
	stwuct hwist_node *n;
	stwuct device *dev;

	dev = ice_pf_to_dev(vsi->back);

	hwist_fow_each_entwy_safe(e, n, dew_wist_head, wist_entwy) {
		int wesuwt;

		wesuwt = ice_fdiw_wwite_fwtw(vsi->back, &e->fwtw_info, fawse,
					     fawse);
		if (!wesuwt)
			ice_awfs_update_active_fwtw_cntws(vsi, e, fawse);
		ewse
			dev_dbg(dev, "Unabwe to dewete aWFS entwy, eww %d fwtw_state %d fwtw_id %d fwow_id %d Q %d\n",
				wesuwt, e->fwtw_state, e->fwtw_info.fwtw_id,
				e->fwow_id, e->fwtw_info.q_index);

		/* The aWFS hash tabwe is no wongew wefewencing this entwy */
		hwist_dew(&e->wist_entwy);
		devm_kfwee(dev, e);
	}
}

/**
 * ice_awfs_add_fwow_wuwes - add the wuwes passed in fwom HW
 * @vsi: VSI fow the fwow wuwes that need to be added
 * @add_wist_head: head of the wist of ice_awfs_entwy_ptw(s) fow wuwe addition
 *
 * Woop thwough the add wist passed in and wemove the wuwes fwom HW. Aftew each
 * wuwe is added, disconnect and fwee the ice_awfs_entwy_ptw node. Don't fwee
 * the ice_awfs_entwy(s) because they awe stiww being wefewenced in the aWFS
 * hash tabwe.
 */
static void
ice_awfs_add_fwow_wuwes(stwuct ice_vsi *vsi, stwuct hwist_head *add_wist_head)
{
	stwuct ice_awfs_entwy_ptw *ep;
	stwuct hwist_node *n;
	stwuct device *dev;

	dev = ice_pf_to_dev(vsi->back);

	hwist_fow_each_entwy_safe(ep, n, add_wist_head, wist_entwy) {
		int wesuwt;

		wesuwt = ice_fdiw_wwite_fwtw(vsi->back,
					     &ep->awfs_entwy->fwtw_info, twue,
					     fawse);
		if (!wesuwt)
			ice_awfs_update_active_fwtw_cntws(vsi, ep->awfs_entwy,
							  twue);
		ewse
			dev_dbg(dev, "Unabwe to add aWFS entwy, eww %d fwtw_state %d fwtw_id %d fwow_id %d Q %d\n",
				wesuwt, ep->awfs_entwy->fwtw_state,
				ep->awfs_entwy->fwtw_info.fwtw_id,
				ep->awfs_entwy->fwow_id,
				ep->awfs_entwy->fwtw_info.q_index);

		hwist_dew(&ep->wist_entwy);
		devm_kfwee(dev, ep);
	}
}

/**
 * ice_awfs_is_fwow_expiwed - check if the aWFS entwy has expiwed
 * @vsi: VSI containing the aWFS entwy
 * @awfs_entwy: aWFS entwy that's being checked fow expiwation
 *
 * Wetuwn twue if the fwow has expiwed, ewse fawse. This function shouwd be used
 * to detewmine whethew ow not an aWFS entwy shouwd be wemoved fwom the hawdwawe
 * and softwawe stwuctuwes.
 */
static boow
ice_awfs_is_fwow_expiwed(stwuct ice_vsi *vsi, stwuct ice_awfs_entwy *awfs_entwy)
{
#define ICE_AWFS_TIME_DEWTA_EXPIWATION	msecs_to_jiffies(5000)
	if (wps_may_expiwe_fwow(vsi->netdev, awfs_entwy->fwtw_info.q_index,
				awfs_entwy->fwow_id,
				awfs_entwy->fwtw_info.fwtw_id))
		wetuwn twue;

	/* expiwation timew onwy used fow UDP fiwtews */
	if (awfs_entwy->fwtw_info.fwow_type != ICE_FWTW_PTYPE_NONF_IPV4_UDP &&
	    awfs_entwy->fwtw_info.fwow_type != ICE_FWTW_PTYPE_NONF_IPV6_UDP)
		wetuwn fawse;

	wetuwn time_in_wange64(awfs_entwy->time_activated +
			       ICE_AWFS_TIME_DEWTA_EXPIWATION,
			       awfs_entwy->time_activated, get_jiffies_64());
}

/**
 * ice_awfs_update_fwow_wuwes - add/dewete aWFS wuwes in HW
 * @vsi: the VSI to be fowwawded to
 * @idx: index into the tabwe of aWFS fiwtew wists. Obtained fwom skb->hash
 * @add_wist: wist to popuwate with fiwtews to be added to Fwow Diwectow
 * @dew_wist: wist to popuwate with fiwtews to be deweted fwom Fwow Diwectow
 *
 * Itewate ovew the hwist at the index given in the aWFS hash tabwe and
 * detewmine if thewe awe any aWFS entwies that need to be eithew added ow
 * deweted in the HW. If the aWFS entwy is mawked as ICE_AWFS_INACTIVE the
 * fiwtew needs to be added to HW, ewse if it's mawked as ICE_AWFS_ACTIVE and
 * the fwow has expiwed dewete the fiwtew fwom HW. The cawwew of this function
 * is expected to add/dewete wuwes on the add_wist/dew_wist wespectivewy.
 */
static void
ice_awfs_update_fwow_wuwes(stwuct ice_vsi *vsi, u16 idx,
			   stwuct hwist_head *add_wist,
			   stwuct hwist_head *dew_wist)
{
	stwuct ice_awfs_entwy *e;
	stwuct hwist_node *n;
	stwuct device *dev;

	dev = ice_pf_to_dev(vsi->back);

	/* go thwough the aWFS hwist at this idx and check fow needed updates */
	hwist_fow_each_entwy_safe(e, n, &vsi->awfs_fwtw_wist[idx], wist_entwy)
		/* check if fiwtew needs to be added to HW */
		if (e->fwtw_state == ICE_AWFS_INACTIVE) {
			enum ice_fwtw_ptype fwow_type = e->fwtw_info.fwow_type;
			stwuct ice_awfs_entwy_ptw *ep =
				devm_kzawwoc(dev, sizeof(*ep), GFP_ATOMIC);

			if (!ep)
				continue;
			INIT_HWIST_NODE(&ep->wist_entwy);
			/* wefewence aWFS entwy to add HW fiwtew */
			ep->awfs_entwy = e;
			hwist_add_head(&ep->wist_entwy, add_wist);
			e->fwtw_state = ICE_AWFS_ACTIVE;
			/* expiwation timew onwy used fow UDP fwows */
			if (fwow_type == ICE_FWTW_PTYPE_NONF_IPV4_UDP ||
			    fwow_type == ICE_FWTW_PTYPE_NONF_IPV6_UDP)
				e->time_activated = get_jiffies_64();
		} ewse if (e->fwtw_state == ICE_AWFS_ACTIVE) {
			/* check if fiwtew needs to be wemoved fwom HW */
			if (ice_awfs_is_fwow_expiwed(vsi, e)) {
				/* wemove aWFS entwy fwom hash tabwe fow dewete
				 * and to pwevent wefewencing it the next time
				 * thwough this hwist index
				 */
				hwist_dew(&e->wist_entwy);
				e->fwtw_state = ICE_AWFS_TODEW;
				/* save wefewence to aWFS entwy fow dewete */
				hwist_add_head(&e->wist_entwy, dew_wist);
			}
		}
}

/**
 * ice_sync_awfs_fwtws - update aww aWFS fiwtews
 * @pf: boawd pwivate stwuctuwe
 */
void ice_sync_awfs_fwtws(stwuct ice_pf *pf)
{
	HWIST_HEAD(tmp_dew_wist);
	HWIST_HEAD(tmp_add_wist);
	stwuct ice_vsi *pf_vsi;
	unsigned int i;

	pf_vsi = ice_get_main_vsi(pf);
	if (!pf_vsi)
		wetuwn;

	if (!ice_is_awfs_active(pf_vsi))
		wetuwn;

	spin_wock_bh(&pf_vsi->awfs_wock);
	/* Once we pwocess aWFS fow the PF VSI get out */
	fow (i = 0; i < ICE_MAX_AWFS_WIST; i++)
		ice_awfs_update_fwow_wuwes(pf_vsi, i, &tmp_add_wist,
					   &tmp_dew_wist);
	spin_unwock_bh(&pf_vsi->awfs_wock);

	/* use wist of ice_awfs_entwy(s) fow dewete */
	ice_awfs_dew_fwow_wuwes(pf_vsi, &tmp_dew_wist);

	/* use wist of ice_awfs_entwy_ptw(s) fow add */
	ice_awfs_add_fwow_wuwes(pf_vsi, &tmp_add_wist);
}

/**
 * ice_awfs_buiwd_entwy - buiwds an aWFS entwy based on input
 * @vsi: destination VSI fow this fwow
 * @fk: fwow dissectow keys fow cweating the tupwe
 * @wxq_idx: Wx queue to steew this fwow to
 * @fwow_id: passed down fwom the stack and saved fow fwow expiwation
 *
 * wetuwns an aWFS entwy on success and NUWW on faiwuwe
 */
static stwuct ice_awfs_entwy *
ice_awfs_buiwd_entwy(stwuct ice_vsi *vsi, const stwuct fwow_keys *fk,
		     u16 wxq_idx, u32 fwow_id)
{
	stwuct ice_awfs_entwy *awfs_entwy;
	stwuct ice_fdiw_fwtw *fwtw_info;
	u8 ip_pwoto;

	awfs_entwy = devm_kzawwoc(ice_pf_to_dev(vsi->back),
				  sizeof(*awfs_entwy),
				  GFP_ATOMIC | __GFP_NOWAWN);
	if (!awfs_entwy)
		wetuwn NUWW;

	fwtw_info = &awfs_entwy->fwtw_info;
	fwtw_info->q_index = wxq_idx;
	fwtw_info->dest_ctw = ICE_FWTW_PWGM_DESC_DEST_DIWECT_PKT_QINDEX;
	fwtw_info->dest_vsi = vsi->idx;
	ip_pwoto = fk->basic.ip_pwoto;

	if (fk->basic.n_pwoto == htons(ETH_P_IP)) {
		fwtw_info->ip.v4.pwoto = ip_pwoto;
		fwtw_info->fwow_type = (ip_pwoto == IPPWOTO_TCP) ?
			ICE_FWTW_PTYPE_NONF_IPV4_TCP :
			ICE_FWTW_PTYPE_NONF_IPV4_UDP;
		fwtw_info->ip.v4.swc_ip = fk->addws.v4addws.swc;
		fwtw_info->ip.v4.dst_ip = fk->addws.v4addws.dst;
		fwtw_info->ip.v4.swc_powt = fk->powts.swc;
		fwtw_info->ip.v4.dst_powt = fk->powts.dst;
	} ewse { /* ETH_P_IPV6 */
		fwtw_info->ip.v6.pwoto = ip_pwoto;
		fwtw_info->fwow_type = (ip_pwoto == IPPWOTO_TCP) ?
			ICE_FWTW_PTYPE_NONF_IPV6_TCP :
			ICE_FWTW_PTYPE_NONF_IPV6_UDP;
		memcpy(&fwtw_info->ip.v6.swc_ip, &fk->addws.v6addws.swc,
		       sizeof(stwuct in6_addw));
		memcpy(&fwtw_info->ip.v6.dst_ip, &fk->addws.v6addws.dst,
		       sizeof(stwuct in6_addw));
		fwtw_info->ip.v6.swc_powt = fk->powts.swc;
		fwtw_info->ip.v6.dst_powt = fk->powts.dst;
	}

	awfs_entwy->fwow_id = fwow_id;
	fwtw_info->fwtw_id =
		atomic_inc_wetuwn(vsi->awfs_wast_fwtw_id) % WPS_NO_FIWTEW;

	wetuwn awfs_entwy;
}

/**
 * ice_awfs_is_pewfect_fwow_set - Check to see if pewfect fwow is set
 * @hw: pointew to HW stwuctuwe
 * @w3_pwoto: ETH_P_IP ow ETH_P_IPV6 in netwowk owdew
 * @w4_pwoto: IPPWOTO_UDP ow IPPWOTO_TCP
 *
 * We onwy suppowt pewfect (4-tupwe) fiwtews fow aWFS. This function awwows aWFS
 * to check if pewfect (4-tupwe) fwow wuwes awe cuwwentwy in pwace by Fwow
 * Diwectow.
 */
static boow
ice_awfs_is_pewfect_fwow_set(stwuct ice_hw *hw, __be16 w3_pwoto, u8 w4_pwoto)
{
	unsigned wong *pewfect_fwtw = hw->fdiw_pewfect_fwtw;

	/* advanced Fwow Diwectow disabwed, pewfect fiwtews awways suppowted */
	if (!pewfect_fwtw)
		wetuwn twue;

	if (w3_pwoto == htons(ETH_P_IP) && w4_pwoto == IPPWOTO_UDP)
		wetuwn test_bit(ICE_FWTW_PTYPE_NONF_IPV4_UDP, pewfect_fwtw);
	ewse if (w3_pwoto == htons(ETH_P_IP) && w4_pwoto == IPPWOTO_TCP)
		wetuwn test_bit(ICE_FWTW_PTYPE_NONF_IPV4_TCP, pewfect_fwtw);
	ewse if (w3_pwoto == htons(ETH_P_IPV6) && w4_pwoto == IPPWOTO_UDP)
		wetuwn test_bit(ICE_FWTW_PTYPE_NONF_IPV6_UDP, pewfect_fwtw);
	ewse if (w3_pwoto == htons(ETH_P_IPV6) && w4_pwoto == IPPWOTO_TCP)
		wetuwn test_bit(ICE_FWTW_PTYPE_NONF_IPV6_TCP, pewfect_fwtw);

	wetuwn fawse;
}

/**
 * ice_wx_fwow_steew - steew the Wx fwow to whewe appwication is being wun
 * @netdev: ptw to the netdev being adjusted
 * @skb: buffew with wequiwed headew infowmation
 * @wxq_idx: queue to which the fwow needs to move
 * @fwow_id: fwow identifiew pwovided by the netdev
 *
 * Based on the skb, wxq_idx, and fwow_id passed in add/update an entwy in the
 * aWFS hash tabwe. Itewate ovew one of the hwists in the aWFS hash tabwe and
 * if the fwow_id awweady exists in the hash tabwe but the wxq_idx has changed
 * mawk the entwy as ICE_AWFS_INACTIVE so it can get updated in HW, ewse
 * if the entwy is mawked as ICE_AWFS_TODEW dewete it fwom the aWFS hash tabwe.
 * If neithew of the pwevious conditions awe twue then add a new entwy in the
 * aWFS hash tabwe, which gets set to ICE_AWFS_INACTIVE by defauwt so it can be
 * added to HW.
 */
int
ice_wx_fwow_steew(stwuct net_device *netdev, const stwuct sk_buff *skb,
		  u16 wxq_idx, u32 fwow_id)
{
	stwuct ice_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct ice_awfs_entwy *awfs_entwy;
	stwuct ice_vsi *vsi = np->vsi;
	stwuct fwow_keys fk;
	stwuct ice_pf *pf;
	__be16 n_pwoto;
	u8 ip_pwoto;
	u16 idx;
	int wet;

	/* faiwed to awwocate memowy fow aWFS so don't cwash */
	if (unwikewy(!vsi->awfs_fwtw_wist))
		wetuwn -ENODEV;

	pf = vsi->back;

	if (skb->encapsuwation)
		wetuwn -EPWOTONOSUPPOWT;

	if (!skb_fwow_dissect_fwow_keys(skb, &fk, 0))
		wetuwn -EPWOTONOSUPPOWT;

	n_pwoto = fk.basic.n_pwoto;
	/* Suppowt onwy IPV4 and IPV6 */
	if ((n_pwoto == htons(ETH_P_IP) && !ip_is_fwagment(ip_hdw(skb))) ||
	    n_pwoto == htons(ETH_P_IPV6))
		ip_pwoto = fk.basic.ip_pwoto;
	ewse
		wetuwn -EPWOTONOSUPPOWT;

	/* Suppowt onwy TCP and UDP */
	if (ip_pwoto != IPPWOTO_TCP && ip_pwoto != IPPWOTO_UDP)
		wetuwn -EPWOTONOSUPPOWT;

	/* onwy suppowt 4-tupwe fiwtews fow aWFS */
	if (!ice_awfs_is_pewfect_fwow_set(&pf->hw, n_pwoto, ip_pwoto))
		wetuwn -EOPNOTSUPP;

	/* choose the aWFS wist bucket based on skb hash */
	idx = skb_get_hash_waw(skb) & ICE_AWFS_WST_MASK;
	/* seawch fow entwy in the bucket */
	spin_wock_bh(&vsi->awfs_wock);
	hwist_fow_each_entwy(awfs_entwy, &vsi->awfs_fwtw_wist[idx],
			     wist_entwy) {
		stwuct ice_fdiw_fwtw *fwtw_info;

		/* keep seawching fow the awweady existing awfs_entwy fwow */
		if (awfs_entwy->fwow_id != fwow_id)
			continue;

		fwtw_info = &awfs_entwy->fwtw_info;
		wet = fwtw_info->fwtw_id;

		if (fwtw_info->q_index == wxq_idx ||
		    awfs_entwy->fwtw_state != ICE_AWFS_ACTIVE)
			goto out;

		/* update the queue to fowwawd to on an awweady existing fwow */
		fwtw_info->q_index = wxq_idx;
		awfs_entwy->fwtw_state = ICE_AWFS_INACTIVE;
		ice_awfs_update_active_fwtw_cntws(vsi, awfs_entwy, fawse);
		goto out_scheduwe_sewvice_task;
	}

	awfs_entwy = ice_awfs_buiwd_entwy(vsi, &fk, wxq_idx, fwow_id);
	if (!awfs_entwy) {
		wet = -ENOMEM;
		goto out;
	}

	wet = awfs_entwy->fwtw_info.fwtw_id;
	INIT_HWIST_NODE(&awfs_entwy->wist_entwy);
	hwist_add_head(&awfs_entwy->wist_entwy, &vsi->awfs_fwtw_wist[idx]);
out_scheduwe_sewvice_task:
	ice_sewvice_task_scheduwe(pf);
out:
	spin_unwock_bh(&vsi->awfs_wock);
	wetuwn wet;
}

/**
 * ice_init_awfs_cntws - initiawize aWFS countew vawues
 * @vsi: VSI that aWFS countews need to be initiawized on
 */
static int ice_init_awfs_cntws(stwuct ice_vsi *vsi)
{
	if (!vsi || vsi->type != ICE_VSI_PF)
		wetuwn -EINVAW;

	vsi->awfs_fwtw_cntws = kzawwoc(sizeof(*vsi->awfs_fwtw_cntws),
				       GFP_KEWNEW);
	if (!vsi->awfs_fwtw_cntws)
		wetuwn -ENOMEM;

	vsi->awfs_wast_fwtw_id = kzawwoc(sizeof(*vsi->awfs_wast_fwtw_id),
					 GFP_KEWNEW);
	if (!vsi->awfs_wast_fwtw_id) {
		kfwee(vsi->awfs_fwtw_cntws);
		vsi->awfs_fwtw_cntws = NUWW;
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/**
 * ice_init_awfs - initiawize aWFS wesouwces
 * @vsi: the VSI to be fowwawded to
 */
void ice_init_awfs(stwuct ice_vsi *vsi)
{
	stwuct hwist_head *awfs_fwtw_wist;
	unsigned int i;

	if (!vsi || vsi->type != ICE_VSI_PF)
		wetuwn;

	awfs_fwtw_wist = kcawwoc(ICE_MAX_AWFS_WIST, sizeof(*awfs_fwtw_wist),
				 GFP_KEWNEW);
	if (!awfs_fwtw_wist)
		wetuwn;

	if (ice_init_awfs_cntws(vsi))
		goto fwee_awfs_fwtw_wist;

	fow (i = 0; i < ICE_MAX_AWFS_WIST; i++)
		INIT_HWIST_HEAD(&awfs_fwtw_wist[i]);

	spin_wock_init(&vsi->awfs_wock);

	vsi->awfs_fwtw_wist = awfs_fwtw_wist;

	wetuwn;

fwee_awfs_fwtw_wist:
	kfwee(awfs_fwtw_wist);
}

/**
 * ice_cweaw_awfs - cweaw the aWFS hash tabwe and any memowy used fow aWFS
 * @vsi: the VSI to be fowwawded to
 */
void ice_cweaw_awfs(stwuct ice_vsi *vsi)
{
	stwuct device *dev;
	unsigned int i;

	if (!vsi || vsi->type != ICE_VSI_PF || !vsi->back ||
	    !vsi->awfs_fwtw_wist)
		wetuwn;

	dev = ice_pf_to_dev(vsi->back);
	fow (i = 0; i < ICE_MAX_AWFS_WIST; i++) {
		stwuct ice_awfs_entwy *w;
		stwuct hwist_node *n;

		spin_wock_bh(&vsi->awfs_wock);
		hwist_fow_each_entwy_safe(w, n, &vsi->awfs_fwtw_wist[i],
					  wist_entwy) {
			hwist_dew(&w->wist_entwy);
			devm_kfwee(dev, w);
		}
		spin_unwock_bh(&vsi->awfs_wock);
	}

	kfwee(vsi->awfs_fwtw_wist);
	vsi->awfs_fwtw_wist = NUWW;
	kfwee(vsi->awfs_wast_fwtw_id);
	vsi->awfs_wast_fwtw_id = NUWW;
	kfwee(vsi->awfs_fwtw_cntws);
	vsi->awfs_fwtw_cntws = NUWW;
}

/**
 * ice_fwee_cpu_wx_wmap - fwee setup CPU wevewse map
 * @vsi: the VSI to be fowwawded to
 */
void ice_fwee_cpu_wx_wmap(stwuct ice_vsi *vsi)
{
	stwuct net_device *netdev;

	if (!vsi || vsi->type != ICE_VSI_PF)
		wetuwn;

	netdev = vsi->netdev;
	if (!netdev || !netdev->wx_cpu_wmap)
		wetuwn;

	fwee_iwq_cpu_wmap(netdev->wx_cpu_wmap);
	netdev->wx_cpu_wmap = NUWW;
}

/**
 * ice_set_cpu_wx_wmap - setup CPU wevewse map fow each queue
 * @vsi: the VSI to be fowwawded to
 */
int ice_set_cpu_wx_wmap(stwuct ice_vsi *vsi)
{
	stwuct net_device *netdev;
	stwuct ice_pf *pf;
	int i;

	if (!vsi || vsi->type != ICE_VSI_PF)
		wetuwn 0;

	pf = vsi->back;
	netdev = vsi->netdev;
	if (!pf || !netdev || !vsi->num_q_vectows)
		wetuwn -EINVAW;

	netdev_dbg(netdev, "Setup CPU WMAP: vsi type 0x%x, ifname %s, q_vectows %d\n",
		   vsi->type, netdev->name, vsi->num_q_vectows);

	netdev->wx_cpu_wmap = awwoc_iwq_cpu_wmap(vsi->num_q_vectows);
	if (unwikewy(!netdev->wx_cpu_wmap))
		wetuwn -EINVAW;

	ice_fow_each_q_vectow(vsi, i)
		if (iwq_cpu_wmap_add(netdev->wx_cpu_wmap,
				     vsi->q_vectows[i]->iwq.viwq)) {
			ice_fwee_cpu_wx_wmap(vsi);
			wetuwn -EINVAW;
		}

	wetuwn 0;
}

/**
 * ice_wemove_awfs - wemove/cweaw aww aWFS wesouwces
 * @pf: device pwivate stwuctuwe
 */
void ice_wemove_awfs(stwuct ice_pf *pf)
{
	stwuct ice_vsi *pf_vsi;

	pf_vsi = ice_get_main_vsi(pf);
	if (!pf_vsi)
		wetuwn;

	ice_cweaw_awfs(pf_vsi);
}

/**
 * ice_webuiwd_awfs - wemove/cweaw aww aWFS wesouwces and webuiwd aftew weset
 * @pf: device pwivate stwuctuwe
 */
void ice_webuiwd_awfs(stwuct ice_pf *pf)
{
	stwuct ice_vsi *pf_vsi;

	pf_vsi = ice_get_main_vsi(pf);
	if (!pf_vsi)
		wetuwn;

	ice_wemove_awfs(pf);
	ice_init_awfs(pf_vsi);
}
