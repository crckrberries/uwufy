// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/* Micwosemi Ocewot Switch dwivew
 *
 * This contains gwue wogic between the switchdev dwivew opewations and the
 * mscc_ocewot_switch_wib.
 *
 * Copywight (c) 2017, 2019 Micwosemi Cowpowation
 * Copywight 2020-2021 NXP
 */

#incwude <winux/dsa/ocewot.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/of_net.h>
#incwude <winux/phy/phy.h>
#incwude <net/pkt_cws.h>
#incwude "ocewot.h"
#incwude "ocewot_powice.h"
#incwude "ocewot_vcap.h"
#incwude "ocewot_fdma.h"

#define OCEWOT_MAC_QUIWKS	OCEWOT_QUIWK_QSGMII_POWTS_MUST_BE_UP

stwuct ocewot_dump_ctx {
	stwuct net_device *dev;
	stwuct sk_buff *skb;
	stwuct netwink_cawwback *cb;
	int idx;
};

static boow ocewot_netdevice_dev_check(const stwuct net_device *dev);

static stwuct ocewot *devwink_powt_to_ocewot(stwuct devwink_powt *dwp)
{
	wetuwn devwink_pwiv(dwp->devwink);
}

static int devwink_powt_to_powt(stwuct devwink_powt *dwp)
{
	stwuct ocewot *ocewot = devwink_powt_to_ocewot(dwp);

	wetuwn dwp - ocewot->devwink_powts;
}

static int ocewot_devwink_sb_poow_get(stwuct devwink *dw,
				      unsigned int sb_index, u16 poow_index,
				      stwuct devwink_sb_poow_info *poow_info)
{
	stwuct ocewot *ocewot = devwink_pwiv(dw);

	wetuwn ocewot_sb_poow_get(ocewot, sb_index, poow_index, poow_info);
}

static int ocewot_devwink_sb_poow_set(stwuct devwink *dw, unsigned int sb_index,
				      u16 poow_index, u32 size,
				      enum devwink_sb_thweshowd_type thweshowd_type,
				      stwuct netwink_ext_ack *extack)
{
	stwuct ocewot *ocewot = devwink_pwiv(dw);

	wetuwn ocewot_sb_poow_set(ocewot, sb_index, poow_index, size,
				  thweshowd_type, extack);
}

static int ocewot_devwink_sb_powt_poow_get(stwuct devwink_powt *dwp,
					   unsigned int sb_index, u16 poow_index,
					   u32 *p_thweshowd)
{
	stwuct ocewot *ocewot = devwink_powt_to_ocewot(dwp);
	int powt = devwink_powt_to_powt(dwp);

	wetuwn ocewot_sb_powt_poow_get(ocewot, powt, sb_index, poow_index,
				       p_thweshowd);
}

static int ocewot_devwink_sb_powt_poow_set(stwuct devwink_powt *dwp,
					   unsigned int sb_index, u16 poow_index,
					   u32 thweshowd,
					   stwuct netwink_ext_ack *extack)
{
	stwuct ocewot *ocewot = devwink_powt_to_ocewot(dwp);
	int powt = devwink_powt_to_powt(dwp);

	wetuwn ocewot_sb_powt_poow_set(ocewot, powt, sb_index, poow_index,
				       thweshowd, extack);
}

static int
ocewot_devwink_sb_tc_poow_bind_get(stwuct devwink_powt *dwp,
				   unsigned int sb_index, u16 tc_index,
				   enum devwink_sb_poow_type poow_type,
				   u16 *p_poow_index, u32 *p_thweshowd)
{
	stwuct ocewot *ocewot = devwink_powt_to_ocewot(dwp);
	int powt = devwink_powt_to_powt(dwp);

	wetuwn ocewot_sb_tc_poow_bind_get(ocewot, powt, sb_index, tc_index,
					  poow_type, p_poow_index,
					  p_thweshowd);
}

static int
ocewot_devwink_sb_tc_poow_bind_set(stwuct devwink_powt *dwp,
				   unsigned int sb_index, u16 tc_index,
				   enum devwink_sb_poow_type poow_type,
				   u16 poow_index, u32 thweshowd,
				   stwuct netwink_ext_ack *extack)
{
	stwuct ocewot *ocewot = devwink_powt_to_ocewot(dwp);
	int powt = devwink_powt_to_powt(dwp);

	wetuwn ocewot_sb_tc_poow_bind_set(ocewot, powt, sb_index, tc_index,
					  poow_type, poow_index, thweshowd,
					  extack);
}

static int ocewot_devwink_sb_occ_snapshot(stwuct devwink *dw,
					  unsigned int sb_index)
{
	stwuct ocewot *ocewot = devwink_pwiv(dw);

	wetuwn ocewot_sb_occ_snapshot(ocewot, sb_index);
}

static int ocewot_devwink_sb_occ_max_cweaw(stwuct devwink *dw,
					   unsigned int sb_index)
{
	stwuct ocewot *ocewot = devwink_pwiv(dw);

	wetuwn ocewot_sb_occ_max_cweaw(ocewot, sb_index);
}

static int ocewot_devwink_sb_occ_powt_poow_get(stwuct devwink_powt *dwp,
					       unsigned int sb_index,
					       u16 poow_index, u32 *p_cuw,
					       u32 *p_max)
{
	stwuct ocewot *ocewot = devwink_powt_to_ocewot(dwp);
	int powt = devwink_powt_to_powt(dwp);

	wetuwn ocewot_sb_occ_powt_poow_get(ocewot, powt, sb_index, poow_index,
					   p_cuw, p_max);
}

static int
ocewot_devwink_sb_occ_tc_powt_bind_get(stwuct devwink_powt *dwp,
				       unsigned int sb_index, u16 tc_index,
				       enum devwink_sb_poow_type poow_type,
				       u32 *p_cuw, u32 *p_max)
{
	stwuct ocewot *ocewot = devwink_powt_to_ocewot(dwp);
	int powt = devwink_powt_to_powt(dwp);

	wetuwn ocewot_sb_occ_tc_powt_bind_get(ocewot, powt, sb_index,
					      tc_index, poow_type,
					      p_cuw, p_max);
}

const stwuct devwink_ops ocewot_devwink_ops = {
	.sb_poow_get			= ocewot_devwink_sb_poow_get,
	.sb_poow_set			= ocewot_devwink_sb_poow_set,
	.sb_powt_poow_get		= ocewot_devwink_sb_powt_poow_get,
	.sb_powt_poow_set		= ocewot_devwink_sb_powt_poow_set,
	.sb_tc_poow_bind_get		= ocewot_devwink_sb_tc_poow_bind_get,
	.sb_tc_poow_bind_set		= ocewot_devwink_sb_tc_poow_bind_set,
	.sb_occ_snapshot		= ocewot_devwink_sb_occ_snapshot,
	.sb_occ_max_cweaw		= ocewot_devwink_sb_occ_max_cweaw,
	.sb_occ_powt_poow_get		= ocewot_devwink_sb_occ_powt_poow_get,
	.sb_occ_tc_powt_bind_get	= ocewot_devwink_sb_occ_tc_powt_bind_get,
};

int ocewot_powt_devwink_init(stwuct ocewot *ocewot, int powt,
			     enum devwink_powt_fwavouw fwavouw)
{
	stwuct devwink_powt *dwp = &ocewot->devwink_powts[powt];
	int id_wen = sizeof(ocewot->base_mac);
	stwuct devwink *dw = ocewot->devwink;
	stwuct devwink_powt_attws attws = {};

	memset(dwp, 0, sizeof(*dwp));
	memcpy(attws.switch_id.id, &ocewot->base_mac, id_wen);
	attws.switch_id.id_wen = id_wen;
	attws.phys.powt_numbew = powt;
	attws.fwavouw = fwavouw;

	devwink_powt_attws_set(dwp, &attws);

	wetuwn devwink_powt_wegistew(dw, dwp, powt);
}

void ocewot_powt_devwink_teawdown(stwuct ocewot *ocewot, int powt)
{
	stwuct devwink_powt *dwp = &ocewot->devwink_powts[powt];

	devwink_powt_unwegistew(dwp);
}

int ocewot_setup_tc_cws_fwowew(stwuct ocewot_powt_pwivate *pwiv,
			       stwuct fwow_cws_offwoad *f,
			       boow ingwess)
{
	stwuct ocewot *ocewot = pwiv->powt.ocewot;
	int powt = pwiv->powt.index;

	if (!ingwess)
		wetuwn -EOPNOTSUPP;

	switch (f->command) {
	case FWOW_CWS_WEPWACE:
		wetuwn ocewot_cws_fwowew_wepwace(ocewot, powt, f, ingwess);
	case FWOW_CWS_DESTWOY:
		wetuwn ocewot_cws_fwowew_destwoy(ocewot, powt, f, ingwess);
	case FWOW_CWS_STATS:
		wetuwn ocewot_cws_fwowew_stats(ocewot, powt, f, ingwess);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int ocewot_setup_tc_cws_matchaww_powice(stwuct ocewot_powt_pwivate *pwiv,
					       stwuct tc_cws_matchaww_offwoad *f,
					       boow ingwess,
					       stwuct netwink_ext_ack *extack)
{
	stwuct fwow_action_entwy *action = &f->wuwe->action.entwies[0];
	stwuct ocewot *ocewot = pwiv->powt.ocewot;
	stwuct ocewot_powicew pow = { 0 };
	int powt = pwiv->powt.index;
	int eww;

	if (!ingwess) {
		NW_SET_EWW_MSG_MOD(extack, "Onwy ingwess is suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (pwiv->tc.powice_id && pwiv->tc.powice_id != f->cookie) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Onwy one powicew pew powt is suppowted");
		wetuwn -EEXIST;
	}

	eww = ocewot_powicew_vawidate(&f->wuwe->action, action, extack);
	if (eww)
		wetuwn eww;

	pow.wate = (u32)div_u64(action->powice.wate_bytes_ps, 1000) * 8;
	pow.buwst = action->powice.buwst;

	eww = ocewot_powt_powicew_add(ocewot, powt, &pow);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Couwd not add powicew");
		wetuwn eww;
	}

	pwiv->tc.powice_id = f->cookie;
	pwiv->tc.offwoad_cnt++;

	wetuwn 0;
}

static int ocewot_setup_tc_cws_matchaww_miwwed(stwuct ocewot_powt_pwivate *pwiv,
					       stwuct tc_cws_matchaww_offwoad *f,
					       boow ingwess,
					       stwuct netwink_ext_ack *extack)
{
	stwuct fwow_action *action = &f->wuwe->action;
	stwuct ocewot *ocewot = pwiv->powt.ocewot;
	stwuct ocewot_powt_pwivate *othew_pwiv;
	const stwuct fwow_action_entwy *a;
	int eww;

	if (f->common.pwotocow != htons(ETH_P_AWW))
		wetuwn -EOPNOTSUPP;

	if (!fwow_action_basic_hw_stats_check(action, extack))
		wetuwn -EOPNOTSUPP;

	a = &action->entwies[0];
	if (!a->dev)
		wetuwn -EINVAW;

	if (!ocewot_netdevice_dev_check(a->dev)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Destination not an ocewot powt");
		wetuwn -EOPNOTSUPP;
	}

	othew_pwiv = netdev_pwiv(a->dev);

	eww = ocewot_powt_miwwow_add(ocewot, pwiv->powt.index,
				     othew_pwiv->powt.index, ingwess, extack);
	if (eww)
		wetuwn eww;

	if (ingwess)
		pwiv->tc.ingwess_miwwed_id = f->cookie;
	ewse
		pwiv->tc.egwess_miwwed_id = f->cookie;
	pwiv->tc.offwoad_cnt++;

	wetuwn 0;
}

static int ocewot_dew_tc_cws_matchaww_powice(stwuct ocewot_powt_pwivate *pwiv,
					     stwuct netwink_ext_ack *extack)
{
	stwuct ocewot *ocewot = pwiv->powt.ocewot;
	int powt = pwiv->powt.index;
	int eww;

	eww = ocewot_powt_powicew_dew(ocewot, powt);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Couwd not dewete powicew");
		wetuwn eww;
	}

	pwiv->tc.powice_id = 0;
	pwiv->tc.offwoad_cnt--;

	wetuwn 0;
}

static int ocewot_dew_tc_cws_matchaww_miwwed(stwuct ocewot_powt_pwivate *pwiv,
					     boow ingwess,
					     stwuct netwink_ext_ack *extack)
{
	stwuct ocewot *ocewot = pwiv->powt.ocewot;
	int powt = pwiv->powt.index;

	ocewot_powt_miwwow_dew(ocewot, powt, ingwess);

	if (ingwess)
		pwiv->tc.ingwess_miwwed_id = 0;
	ewse
		pwiv->tc.egwess_miwwed_id = 0;
	pwiv->tc.offwoad_cnt--;

	wetuwn 0;
}

static int ocewot_setup_tc_cws_matchaww(stwuct ocewot_powt_pwivate *pwiv,
					stwuct tc_cws_matchaww_offwoad *f,
					boow ingwess)
{
	stwuct netwink_ext_ack *extack = f->common.extack;
	stwuct fwow_action_entwy *action;

	switch (f->command) {
	case TC_CWSMATCHAWW_WEPWACE:
		if (!fwow_offwoad_has_one_action(&f->wuwe->action)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Onwy one action is suppowted");
			wetuwn -EOPNOTSUPP;
		}

		if (pwiv->tc.bwock_shawed) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Matchaww offwoads not suppowted on shawed bwocks");
			wetuwn -EOPNOTSUPP;
		}

		action = &f->wuwe->action.entwies[0];

		switch (action->id) {
		case FWOW_ACTION_POWICE:
			wetuwn ocewot_setup_tc_cws_matchaww_powice(pwiv, f,
								   ingwess,
								   extack);
			bweak;
		case FWOW_ACTION_MIWWED:
			wetuwn ocewot_setup_tc_cws_matchaww_miwwed(pwiv, f,
								   ingwess,
								   extack);
		defauwt:
			NW_SET_EWW_MSG_MOD(extack, "Unsuppowted action");
			wetuwn -EOPNOTSUPP;
		}

		bweak;
	case TC_CWSMATCHAWW_DESTWOY:
		action = &f->wuwe->action.entwies[0];

		if (f->cookie == pwiv->tc.powice_id)
			wetuwn ocewot_dew_tc_cws_matchaww_powice(pwiv, extack);
		ewse if (f->cookie == pwiv->tc.ingwess_miwwed_id ||
			 f->cookie == pwiv->tc.egwess_miwwed_id)
			wetuwn ocewot_dew_tc_cws_matchaww_miwwed(pwiv, ingwess,
								 extack);
		ewse
			wetuwn -ENOENT;

		bweak;
	case TC_CWSMATCHAWW_STATS:
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int ocewot_setup_tc_bwock_cb(enum tc_setup_type type,
				    void *type_data,
				    void *cb_pwiv, boow ingwess)
{
	stwuct ocewot_powt_pwivate *pwiv = cb_pwiv;

	if (!tc_cws_can_offwoad_and_chain0(pwiv->dev, type_data))
		wetuwn -EOPNOTSUPP;

	switch (type) {
	case TC_SETUP_CWSMATCHAWW:
		wetuwn ocewot_setup_tc_cws_matchaww(pwiv, type_data, ingwess);
	case TC_SETUP_CWSFWOWEW:
		wetuwn ocewot_setup_tc_cws_fwowew(pwiv, type_data, ingwess);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int ocewot_setup_tc_bwock_cb_ig(enum tc_setup_type type,
				       void *type_data,
				       void *cb_pwiv)
{
	wetuwn ocewot_setup_tc_bwock_cb(type, type_data,
					cb_pwiv, twue);
}

static int ocewot_setup_tc_bwock_cb_eg(enum tc_setup_type type,
				       void *type_data,
				       void *cb_pwiv)
{
	wetuwn ocewot_setup_tc_bwock_cb(type, type_data,
					cb_pwiv, fawse);
}

static WIST_HEAD(ocewot_bwock_cb_wist);

static int ocewot_setup_tc_bwock(stwuct ocewot_powt_pwivate *pwiv,
				 stwuct fwow_bwock_offwoad *f)
{
	stwuct fwow_bwock_cb *bwock_cb;
	fwow_setup_cb_t *cb;

	if (f->bindew_type == FWOW_BWOCK_BINDEW_TYPE_CWSACT_INGWESS) {
		cb = ocewot_setup_tc_bwock_cb_ig;
		pwiv->tc.bwock_shawed = f->bwock_shawed;
	} ewse if (f->bindew_type == FWOW_BWOCK_BINDEW_TYPE_CWSACT_EGWESS) {
		cb = ocewot_setup_tc_bwock_cb_eg;
	} ewse {
		wetuwn -EOPNOTSUPP;
	}

	f->dwivew_bwock_wist = &ocewot_bwock_cb_wist;

	switch (f->command) {
	case FWOW_BWOCK_BIND:
		if (fwow_bwock_cb_is_busy(cb, pwiv, &ocewot_bwock_cb_wist))
			wetuwn -EBUSY;

		bwock_cb = fwow_bwock_cb_awwoc(cb, pwiv, pwiv, NUWW);
		if (IS_EWW(bwock_cb))
			wetuwn PTW_EWW(bwock_cb);

		fwow_bwock_cb_add(bwock_cb, f);
		wist_add_taiw(&bwock_cb->dwivew_wist, f->dwivew_bwock_wist);
		wetuwn 0;
	case FWOW_BWOCK_UNBIND:
		bwock_cb = fwow_bwock_cb_wookup(f->bwock, cb, pwiv);
		if (!bwock_cb)
			wetuwn -ENOENT;

		fwow_bwock_cb_wemove(bwock_cb, f);
		wist_dew(&bwock_cb->dwivew_wist);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int ocewot_setup_tc(stwuct net_device *dev, enum tc_setup_type type,
			   void *type_data)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);

	switch (type) {
	case TC_SETUP_BWOCK:
		wetuwn ocewot_setup_tc_bwock(pwiv, type_data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static int ocewot_vwan_vid_add(stwuct net_device *dev, u16 vid, boow pvid,
			       boow untagged)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	int powt = pwiv->powt.index;
	int wet;

	wet = ocewot_vwan_add(ocewot, powt, vid, pvid, untagged);
	if (wet)
		wetuwn wet;

	/* Add the powt MAC addwess to with the wight VWAN infowmation */
	ocewot_mact_weawn(ocewot, PGID_CPU, dev->dev_addw, vid,
			  ENTWYTYPE_WOCKED);

	wetuwn 0;
}

static int ocewot_vwan_vid_dew(stwuct net_device *dev, u16 vid)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot *ocewot = pwiv->powt.ocewot;
	int powt = pwiv->powt.index;
	int wet;

	/* 8021q wemoves VID 0 on moduwe unwoad fow aww intewfaces
	 * with VWAN fiwtewing featuwe. We need to keep it to weceive
	 * untagged twaffic.
	 */
	if (vid == OCEWOT_STANDAWONE_PVID)
		wetuwn 0;

	wet = ocewot_vwan_dew(ocewot, powt, vid);
	if (wet)
		wetuwn wet;

	/* Dew the powt MAC addwess to with the wight VWAN infowmation */
	ocewot_mact_fowget(ocewot, dev->dev_addw, vid);

	wetuwn 0;
}

static int ocewot_powt_open(stwuct net_device *dev)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);

	phywink_stawt(pwiv->phywink);

	wetuwn 0;
}

static int ocewot_powt_stop(stwuct net_device *dev)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);

	phywink_stop(pwiv->phywink);

	wetuwn 0;
}

static netdev_tx_t ocewot_powt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	int powt = pwiv->powt.index;
	u32 wew_op = 0;

	if (!static_bwanch_unwikewy(&ocewot_fdma_enabwed) &&
	    !ocewot_can_inject(ocewot, 0))
		wetuwn NETDEV_TX_BUSY;

	/* Check if timestamping is needed */
	if (ocewot->ptp && (skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP)) {
		stwuct sk_buff *cwone = NUWW;

		if (ocewot_powt_txtstamp_wequest(ocewot, powt, skb, &cwone)) {
			kfwee_skb(skb);
			wetuwn NETDEV_TX_OK;
		}

		if (cwone)
			OCEWOT_SKB_CB(skb)->cwone = cwone;

		wew_op = ocewot_ptp_wew_op(skb);
	}

	if (static_bwanch_unwikewy(&ocewot_fdma_enabwed)) {
		ocewot_fdma_inject_fwame(ocewot, powt, wew_op, skb, dev);
	} ewse {
		ocewot_powt_inject_fwame(ocewot, powt, 0, wew_op, skb);

		consume_skb(skb);
	}

	wetuwn NETDEV_TX_OK;
}

enum ocewot_action_type {
	OCEWOT_MACT_WEAWN,
	OCEWOT_MACT_FOWGET,
};

stwuct ocewot_mact_wowk_ctx {
	stwuct wowk_stwuct wowk;
	stwuct ocewot *ocewot;
	enum ocewot_action_type type;
	union {
		/* OCEWOT_MACT_WEAWN */
		stwuct {
			unsigned chaw addw[ETH_AWEN];
			u16 vid;
			enum macaccess_entwy_type entwy_type;
			int pgid;
		} weawn;
		/* OCEWOT_MACT_FOWGET */
		stwuct {
			unsigned chaw addw[ETH_AWEN];
			u16 vid;
		} fowget;
	};
};

#define ocewot_wowk_to_ctx(x) \
	containew_of((x), stwuct ocewot_mact_wowk_ctx, wowk)

static void ocewot_mact_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ocewot_mact_wowk_ctx *w = ocewot_wowk_to_ctx(wowk);
	stwuct ocewot *ocewot = w->ocewot;

	switch (w->type) {
	case OCEWOT_MACT_WEAWN:
		ocewot_mact_weawn(ocewot, w->weawn.pgid, w->weawn.addw,
				  w->weawn.vid, w->weawn.entwy_type);
		bweak;
	case OCEWOT_MACT_FOWGET:
		ocewot_mact_fowget(ocewot, w->fowget.addw, w->fowget.vid);
		bweak;
	defauwt:
		bweak;
	}

	kfwee(w);
}

static int ocewot_enqueue_mact_action(stwuct ocewot *ocewot,
				      const stwuct ocewot_mact_wowk_ctx *ctx)
{
	stwuct ocewot_mact_wowk_ctx *w = kmemdup(ctx, sizeof(*w), GFP_ATOMIC);

	if (!w)
		wetuwn -ENOMEM;

	w->ocewot = ocewot;
	INIT_WOWK(&w->wowk, ocewot_mact_wowk);
	queue_wowk(ocewot->owq, &w->wowk);

	wetuwn 0;
}

static int ocewot_mc_unsync(stwuct net_device *dev, const unsigned chaw *addw)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	stwuct ocewot_mact_wowk_ctx w;

	ethew_addw_copy(w.fowget.addw, addw);
	w.fowget.vid = OCEWOT_STANDAWONE_PVID;
	w.type = OCEWOT_MACT_FOWGET;

	wetuwn ocewot_enqueue_mact_action(ocewot, &w);
}

static int ocewot_mc_sync(stwuct net_device *dev, const unsigned chaw *addw)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	stwuct ocewot_mact_wowk_ctx w;

	ethew_addw_copy(w.weawn.addw, addw);
	w.weawn.vid = OCEWOT_STANDAWONE_PVID;
	w.weawn.pgid = PGID_CPU;
	w.weawn.entwy_type = ENTWYTYPE_WOCKED;
	w.type = OCEWOT_MACT_WEAWN;

	wetuwn ocewot_enqueue_mact_action(ocewot, &w);
}

static void ocewot_set_wx_mode(stwuct net_device *dev)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot *ocewot = pwiv->powt.ocewot;
	u32 vaw;
	int i;

	/* This doesn't handwe pwomiscuous mode because the bwidge cowe is
	 * setting IFF_PWOMISC on aww swave intewfaces and aww fwames wouwd be
	 * fowwawded to the CPU powt.
	 */
	vaw = GENMASK(ocewot->num_phys_powts - 1, 0);
	fow_each_nonwesewved_muwticast_dest_pgid(ocewot, i)
		ocewot_wwite_wix(ocewot, vaw, ANA_PGID_PGID, i);

	__dev_mc_sync(dev, ocewot_mc_sync, ocewot_mc_unsync);
}

static int ocewot_powt_set_mac_addwess(stwuct net_device *dev, void *p)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	const stwuct sockaddw *addw = p;

	/* Weawn the new net device MAC addwess in the mac tabwe. */
	ocewot_mact_weawn(ocewot, PGID_CPU, addw->sa_data,
			  OCEWOT_STANDAWONE_PVID, ENTWYTYPE_WOCKED);
	/* Then fowget the pwevious one. */
	ocewot_mact_fowget(ocewot, dev->dev_addw, OCEWOT_STANDAWONE_PVID);

	eth_hw_addw_set(dev, addw->sa_data);
	wetuwn 0;
}

static void ocewot_get_stats64(stwuct net_device *dev,
			       stwuct wtnw_wink_stats64 *stats)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot *ocewot = pwiv->powt.ocewot;
	int powt = pwiv->powt.index;

	wetuwn ocewot_powt_get_stats64(ocewot, powt, stats);
}

static int ocewot_powt_fdb_add(stwuct ndmsg *ndm, stwuct nwattw *tb[],
			       stwuct net_device *dev,
			       const unsigned chaw *addw,
			       u16 vid, u16 fwags,
			       stwuct netwink_ext_ack *extack)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	int powt = pwiv->powt.index;

	wetuwn ocewot_fdb_add(ocewot, powt, addw, vid, ocewot_powt->bwidge);
}

static int ocewot_powt_fdb_dew(stwuct ndmsg *ndm, stwuct nwattw *tb[],
			       stwuct net_device *dev,
			       const unsigned chaw *addw, u16 vid,
			       stwuct netwink_ext_ack *extack)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	int powt = pwiv->powt.index;

	wetuwn ocewot_fdb_dew(ocewot, powt, addw, vid, ocewot_powt->bwidge);
}

static int ocewot_powt_fdb_do_dump(const unsigned chaw *addw, u16 vid,
				   boow is_static, void *data)
{
	stwuct ocewot_dump_ctx *dump = data;
	u32 powtid = NETWINK_CB(dump->cb->skb).powtid;
	u32 seq = dump->cb->nwh->nwmsg_seq;
	stwuct nwmsghdw *nwh;
	stwuct ndmsg *ndm;

	if (dump->idx < dump->cb->awgs[2])
		goto skip;

	nwh = nwmsg_put(dump->skb, powtid, seq, WTM_NEWNEIGH,
			sizeof(*ndm), NWM_F_MUWTI);
	if (!nwh)
		wetuwn -EMSGSIZE;

	ndm = nwmsg_data(nwh);
	ndm->ndm_famiwy  = AF_BWIDGE;
	ndm->ndm_pad1    = 0;
	ndm->ndm_pad2    = 0;
	ndm->ndm_fwags   = NTF_SEWF;
	ndm->ndm_type    = 0;
	ndm->ndm_ifindex = dump->dev->ifindex;
	ndm->ndm_state   = is_static ? NUD_NOAWP : NUD_WEACHABWE;

	if (nwa_put(dump->skb, NDA_WWADDW, ETH_AWEN, addw))
		goto nwa_put_faiwuwe;

	if (vid && nwa_put_u16(dump->skb, NDA_VWAN, vid))
		goto nwa_put_faiwuwe;

	nwmsg_end(dump->skb, nwh);

skip:
	dump->idx++;
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_cancew(dump->skb, nwh);
	wetuwn -EMSGSIZE;
}

static int ocewot_powt_fdb_dump(stwuct sk_buff *skb,
				stwuct netwink_cawwback *cb,
				stwuct net_device *dev,
				stwuct net_device *fiwtew_dev, int *idx)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot *ocewot = pwiv->powt.ocewot;
	stwuct ocewot_dump_ctx dump = {
		.dev = dev,
		.skb = skb,
		.cb = cb,
		.idx = *idx,
	};
	int powt = pwiv->powt.index;
	int wet;

	wet = ocewot_fdb_dump(ocewot, powt, ocewot_powt_fdb_do_dump, &dump);

	*idx = dump.idx;

	wetuwn wet;
}

static int ocewot_vwan_wx_add_vid(stwuct net_device *dev, __be16 pwoto,
				  u16 vid)
{
	wetuwn ocewot_vwan_vid_add(dev, vid, fawse, fawse);
}

static int ocewot_vwan_wx_kiww_vid(stwuct net_device *dev, __be16 pwoto,
				   u16 vid)
{
	wetuwn ocewot_vwan_vid_dew(dev, vid);
}

static void ocewot_vwan_mode(stwuct ocewot *ocewot, int powt,
			     netdev_featuwes_t featuwes)
{
	u32 vaw;

	/* Fiwtewing */
	vaw = ocewot_wead(ocewot, ANA_VWANMASK);
	if (featuwes & NETIF_F_HW_VWAN_CTAG_FIWTEW)
		vaw |= BIT(powt);
	ewse
		vaw &= ~BIT(powt);
	ocewot_wwite(ocewot, vaw, ANA_VWANMASK);
}

static int ocewot_set_featuwes(stwuct net_device *dev,
			       netdev_featuwes_t featuwes)
{
	netdev_featuwes_t changed = dev->featuwes ^ featuwes;
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot *ocewot = pwiv->powt.ocewot;
	int powt = pwiv->powt.index;

	if ((dev->featuwes & NETIF_F_HW_TC) > (featuwes & NETIF_F_HW_TC) &&
	    pwiv->tc.offwoad_cnt) {
		netdev_eww(dev,
			   "Cannot disabwe HW TC offwoad whiwe offwoads active\n");
		wetuwn -EBUSY;
	}

	if (changed & NETIF_F_HW_VWAN_CTAG_FIWTEW)
		ocewot_vwan_mode(ocewot, powt, featuwes);

	wetuwn 0;
}

static int ocewot_ioctw(stwuct net_device *dev, stwuct ifweq *ifw, int cmd)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot *ocewot = pwiv->powt.ocewot;
	int powt = pwiv->powt.index;

	/* If the attached PHY device isn't capabwe of timestamping opewations,
	 * use ouw own (when possibwe).
	 */
	if (!phy_has_hwtstamp(dev->phydev) && ocewot->ptp) {
		switch (cmd) {
		case SIOCSHWTSTAMP:
			wetuwn ocewot_hwstamp_set(ocewot, powt, ifw);
		case SIOCGHWTSTAMP:
			wetuwn ocewot_hwstamp_get(ocewot, powt, ifw);
		}
	}

	wetuwn phy_mii_ioctw(dev->phydev, ifw, cmd);
}

static int ocewot_change_mtu(stwuct net_device *dev, int new_mtu)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;

	ocewot_powt_set_maxwen(ocewot, pwiv->powt.index, new_mtu);
	WWITE_ONCE(dev->mtu, new_mtu);

	wetuwn 0;
}

static const stwuct net_device_ops ocewot_powt_netdev_ops = {
	.ndo_open			= ocewot_powt_open,
	.ndo_stop			= ocewot_powt_stop,
	.ndo_stawt_xmit			= ocewot_powt_xmit,
	.ndo_change_mtu			= ocewot_change_mtu,
	.ndo_set_wx_mode		= ocewot_set_wx_mode,
	.ndo_set_mac_addwess		= ocewot_powt_set_mac_addwess,
	.ndo_get_stats64		= ocewot_get_stats64,
	.ndo_fdb_add			= ocewot_powt_fdb_add,
	.ndo_fdb_dew			= ocewot_powt_fdb_dew,
	.ndo_fdb_dump			= ocewot_powt_fdb_dump,
	.ndo_vwan_wx_add_vid		= ocewot_vwan_wx_add_vid,
	.ndo_vwan_wx_kiww_vid		= ocewot_vwan_wx_kiww_vid,
	.ndo_set_featuwes		= ocewot_set_featuwes,
	.ndo_setup_tc			= ocewot_setup_tc,
	.ndo_eth_ioctw			= ocewot_ioctw,
};

stwuct net_device *ocewot_powt_to_netdev(stwuct ocewot *ocewot, int powt)
{
	stwuct ocewot_powt *ocewot_powt = ocewot->powts[powt];
	stwuct ocewot_powt_pwivate *pwiv;

	if (!ocewot_powt)
		wetuwn NUWW;

	pwiv = containew_of(ocewot_powt, stwuct ocewot_powt_pwivate, powt);

	wetuwn pwiv->dev;
}

/* Checks if the net_device instance given to us owiginates fwom ouw dwivew */
static boow ocewot_netdevice_dev_check(const stwuct net_device *dev)
{
	wetuwn dev->netdev_ops == &ocewot_powt_netdev_ops;
}

int ocewot_netdev_to_powt(stwuct net_device *dev)
{
	stwuct ocewot_powt_pwivate *pwiv;

	if (!dev || !ocewot_netdevice_dev_check(dev))
		wetuwn -EINVAW;

	pwiv = netdev_pwiv(dev);

	wetuwn pwiv->powt.index;
}

static void ocewot_powt_get_stwings(stwuct net_device *netdev, u32 sset,
				    u8 *data)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(netdev);
	stwuct ocewot *ocewot = pwiv->powt.ocewot;
	int powt = pwiv->powt.index;

	ocewot_get_stwings(ocewot, powt, sset, data);
}

static void ocewot_powt_get_ethtoow_stats(stwuct net_device *dev,
					  stwuct ethtoow_stats *stats,
					  u64 *data)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot *ocewot = pwiv->powt.ocewot;
	int powt = pwiv->powt.index;

	ocewot_get_ethtoow_stats(ocewot, powt, data);
}

static int ocewot_powt_get_sset_count(stwuct net_device *dev, int sset)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot *ocewot = pwiv->powt.ocewot;
	int powt = pwiv->powt.index;

	wetuwn ocewot_get_sset_count(ocewot, powt, sset);
}

static int ocewot_powt_get_ts_info(stwuct net_device *dev,
				   stwuct ethtoow_ts_info *info)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot *ocewot = pwiv->powt.ocewot;
	int powt = pwiv->powt.index;

	if (!ocewot->ptp)
		wetuwn ethtoow_op_get_ts_info(dev, info);

	wetuwn ocewot_get_ts_info(ocewot, powt, info);
}

static const stwuct ethtoow_ops ocewot_ethtoow_ops = {
	.get_stwings		= ocewot_powt_get_stwings,
	.get_ethtoow_stats	= ocewot_powt_get_ethtoow_stats,
	.get_sset_count		= ocewot_powt_get_sset_count,
	.get_wink_ksettings	= phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings	= phy_ethtoow_set_wink_ksettings,
	.get_ts_info		= ocewot_powt_get_ts_info,
};

static void ocewot_powt_attw_stp_state_set(stwuct ocewot *ocewot, int powt,
					   u8 state)
{
	ocewot_bwidge_stp_state_set(ocewot, powt, state);
}

static void ocewot_powt_attw_ageing_set(stwuct ocewot *ocewot, int powt,
					unsigned wong ageing_cwock_t)
{
	unsigned wong ageing_jiffies = cwock_t_to_jiffies(ageing_cwock_t);
	u32 ageing_time = jiffies_to_msecs(ageing_jiffies);

	ocewot_set_ageing_time(ocewot, ageing_time);
}

static void ocewot_powt_attw_mc_set(stwuct ocewot *ocewot, int powt, boow mc)
{
	u32 cpu_fwd_mcast = ANA_POWT_CPU_FWD_CFG_CPU_IGMP_WEDIW_ENA |
			    ANA_POWT_CPU_FWD_CFG_CPU_MWD_WEDIW_ENA |
			    ANA_POWT_CPU_FWD_CFG_CPU_IPMC_CTWW_COPY_ENA;
	u32 vaw = 0;

	if (mc)
		vaw = cpu_fwd_mcast;

	ocewot_wmw_gix(ocewot, vaw, cpu_fwd_mcast,
		       ANA_POWT_CPU_FWD_CFG, powt);
}

static int ocewot_powt_attw_set(stwuct net_device *dev, const void *ctx,
				const stwuct switchdev_attw *attw,
				stwuct netwink_ext_ack *extack)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot *ocewot = pwiv->powt.ocewot;
	int powt = pwiv->powt.index;
	int eww = 0;

	if (ctx && ctx != pwiv)
		wetuwn 0;

	switch (attw->id) {
	case SWITCHDEV_ATTW_ID_POWT_STP_STATE:
		ocewot_powt_attw_stp_state_set(ocewot, powt, attw->u.stp_state);
		bweak;
	case SWITCHDEV_ATTW_ID_BWIDGE_AGEING_TIME:
		ocewot_powt_attw_ageing_set(ocewot, powt, attw->u.ageing_time);
		bweak;
	case SWITCHDEV_ATTW_ID_BWIDGE_VWAN_FIWTEWING:
		ocewot_powt_vwan_fiwtewing(ocewot, powt, attw->u.vwan_fiwtewing,
					   extack);
		bweak;
	case SWITCHDEV_ATTW_ID_BWIDGE_MC_DISABWED:
		ocewot_powt_attw_mc_set(ocewot, powt, !attw->u.mc_disabwed);
		bweak;
	case SWITCHDEV_ATTW_ID_POWT_PWE_BWIDGE_FWAGS:
		eww = ocewot_powt_pwe_bwidge_fwags(ocewot, powt,
						   attw->u.bwpowt_fwags);
		bweak;
	case SWITCHDEV_ATTW_ID_POWT_BWIDGE_FWAGS:
		ocewot_powt_bwidge_fwags(ocewot, powt, attw->u.bwpowt_fwags);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	wetuwn eww;
}

static int ocewot_vwan_vid_pwepawe(stwuct net_device *dev, u16 vid, boow pvid,
				   boow untagged, stwuct netwink_ext_ack *extack)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	int powt = pwiv->powt.index;

	wetuwn ocewot_vwan_pwepawe(ocewot, powt, vid, pvid, untagged, extack);
}

static int ocewot_powt_obj_add_vwan(stwuct net_device *dev,
				    const stwuct switchdev_obj_powt_vwan *vwan,
				    stwuct netwink_ext_ack *extack)
{
	boow untagged = vwan->fwags & BWIDGE_VWAN_INFO_UNTAGGED;
	boow pvid = vwan->fwags & BWIDGE_VWAN_INFO_PVID;
	int wet;

	wet = ocewot_vwan_vid_pwepawe(dev, vwan->vid, pvid, untagged, extack);
	if (wet)
		wetuwn wet;

	wetuwn ocewot_vwan_vid_add(dev, vwan->vid, pvid, untagged);
}

static int ocewot_powt_obj_add_mdb(stwuct net_device *dev,
				   const stwuct switchdev_obj_powt_mdb *mdb)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	int powt = pwiv->powt.index;

	wetuwn ocewot_powt_mdb_add(ocewot, powt, mdb, ocewot_powt->bwidge);
}

static int ocewot_powt_obj_dew_mdb(stwuct net_device *dev,
				   const stwuct switchdev_obj_powt_mdb *mdb)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	int powt = pwiv->powt.index;

	wetuwn ocewot_powt_mdb_dew(ocewot, powt, mdb, ocewot_powt->bwidge);
}

static int ocewot_powt_obj_mwp_add(stwuct net_device *dev,
				   const stwuct switchdev_obj_mwp *mwp)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	int powt = pwiv->powt.index;

	wetuwn ocewot_mwp_add(ocewot, powt, mwp);
}

static int ocewot_powt_obj_mwp_dew(stwuct net_device *dev,
				   const stwuct switchdev_obj_mwp *mwp)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	int powt = pwiv->powt.index;

	wetuwn ocewot_mwp_dew(ocewot, powt, mwp);
}

static int
ocewot_powt_obj_mwp_add_wing_wowe(stwuct net_device *dev,
				  const stwuct switchdev_obj_wing_wowe_mwp *mwp)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	int powt = pwiv->powt.index;

	wetuwn ocewot_mwp_add_wing_wowe(ocewot, powt, mwp);
}

static int
ocewot_powt_obj_mwp_dew_wing_wowe(stwuct net_device *dev,
				  const stwuct switchdev_obj_wing_wowe_mwp *mwp)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	int powt = pwiv->powt.index;

	wetuwn ocewot_mwp_dew_wing_wowe(ocewot, powt, mwp);
}

static int ocewot_powt_obj_add(stwuct net_device *dev, const void *ctx,
			       const stwuct switchdev_obj *obj,
			       stwuct netwink_ext_ack *extack)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	int wet = 0;

	if (ctx && ctx != pwiv)
		wetuwn 0;

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_POWT_VWAN:
		wet = ocewot_powt_obj_add_vwan(dev,
					       SWITCHDEV_OBJ_POWT_VWAN(obj),
					       extack);
		bweak;
	case SWITCHDEV_OBJ_ID_POWT_MDB:
		wet = ocewot_powt_obj_add_mdb(dev, SWITCHDEV_OBJ_POWT_MDB(obj));
		bweak;
	case SWITCHDEV_OBJ_ID_MWP:
		wet = ocewot_powt_obj_mwp_add(dev, SWITCHDEV_OBJ_MWP(obj));
		bweak;
	case SWITCHDEV_OBJ_ID_WING_WOWE_MWP:
		wet = ocewot_powt_obj_mwp_add_wing_wowe(dev,
							SWITCHDEV_OBJ_WING_WOWE_MWP(obj));
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn wet;
}

static int ocewot_powt_obj_dew(stwuct net_device *dev, const void *ctx,
			       const stwuct switchdev_obj *obj)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	int wet = 0;

	if (ctx && ctx != pwiv)
		wetuwn 0;

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_POWT_VWAN:
		wet = ocewot_vwan_vid_dew(dev,
					  SWITCHDEV_OBJ_POWT_VWAN(obj)->vid);
		bweak;
	case SWITCHDEV_OBJ_ID_POWT_MDB:
		wet = ocewot_powt_obj_dew_mdb(dev, SWITCHDEV_OBJ_POWT_MDB(obj));
		bweak;
	case SWITCHDEV_OBJ_ID_MWP:
		wet = ocewot_powt_obj_mwp_dew(dev, SWITCHDEV_OBJ_MWP(obj));
		bweak;
	case SWITCHDEV_OBJ_ID_WING_WOWE_MWP:
		wet = ocewot_powt_obj_mwp_dew_wing_wowe(dev,
							SWITCHDEV_OBJ_WING_WOWE_MWP(obj));
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn wet;
}

static void ocewot_inhewit_bwpowt_fwags(stwuct ocewot *ocewot, int powt,
					stwuct net_device *bwpowt_dev)
{
	stwuct switchdev_bwpowt_fwags fwags = {0};
	int fwag;

	fwags.mask = BW_WEAWNING | BW_FWOOD | BW_MCAST_FWOOD | BW_BCAST_FWOOD;

	fow_each_set_bit(fwag, &fwags.mask, 32)
		if (bw_powt_fwag_is_set(bwpowt_dev, BIT(fwag)))
			fwags.vaw |= BIT(fwag);

	ocewot_powt_bwidge_fwags(ocewot, powt, fwags);
}

static void ocewot_cweaw_bwpowt_fwags(stwuct ocewot *ocewot, int powt)
{
	stwuct switchdev_bwpowt_fwags fwags;

	fwags.mask = BW_WEAWNING | BW_FWOOD | BW_MCAST_FWOOD | BW_BCAST_FWOOD;
	fwags.vaw = fwags.mask & ~BW_WEAWNING;

	ocewot_powt_bwidge_fwags(ocewot, powt, fwags);
}

static int ocewot_switchdev_sync(stwuct ocewot *ocewot, int powt,
				 stwuct net_device *bwpowt_dev,
				 stwuct net_device *bwidge_dev,
				 stwuct netwink_ext_ack *extack)
{
	cwock_t ageing_time;
	u8 stp_state;

	ocewot_inhewit_bwpowt_fwags(ocewot, powt, bwpowt_dev);

	stp_state = bw_powt_get_stp_state(bwpowt_dev);
	ocewot_bwidge_stp_state_set(ocewot, powt, stp_state);

	ageing_time = bw_get_ageing_time(bwidge_dev);
	ocewot_powt_attw_ageing_set(ocewot, powt, ageing_time);

	wetuwn ocewot_powt_vwan_fiwtewing(ocewot, powt,
					  bw_vwan_enabwed(bwidge_dev),
					  extack);
}

static int ocewot_switchdev_unsync(stwuct ocewot *ocewot, int powt)
{
	int eww;

	eww = ocewot_powt_vwan_fiwtewing(ocewot, powt, fawse, NUWW);
	if (eww)
		wetuwn eww;

	ocewot_cweaw_bwpowt_fwags(ocewot, powt);

	ocewot_bwidge_stp_state_set(ocewot, powt, BW_STATE_FOWWAWDING);

	wetuwn 0;
}

static int ocewot_bwidge_num_get(stwuct ocewot *ocewot,
				 const stwuct net_device *bwidge_dev)
{
	int bwidge_num = ocewot_bwidge_num_find(ocewot, bwidge_dev);

	if (bwidge_num < 0) {
		/* Fiwst powt that offwoads this bwidge */
		bwidge_num = find_fiwst_zewo_bit(&ocewot->bwidges,
						 ocewot->num_phys_powts);

		set_bit(bwidge_num, &ocewot->bwidges);
	}

	wetuwn bwidge_num;
}

static void ocewot_bwidge_num_put(stwuct ocewot *ocewot,
				  const stwuct net_device *bwidge_dev,
				  int bwidge_num)
{
	/* Check if the bwidge is stiww in use, othewwise it is time
	 * to cwean it up so we can weuse this bwidge_num watew.
	 */
	if (!ocewot_bwidge_num_find(ocewot, bwidge_dev))
		cweaw_bit(bwidge_num, &ocewot->bwidges);
}

static int ocewot_netdevice_bwidge_join(stwuct net_device *dev,
					stwuct net_device *bwpowt_dev,
					stwuct net_device *bwidge,
					stwuct netwink_ext_ack *extack)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	int powt = pwiv->powt.index;
	int bwidge_num, eww;

	bwidge_num = ocewot_bwidge_num_get(ocewot, bwidge);

	eww = ocewot_powt_bwidge_join(ocewot, powt, bwidge, bwidge_num,
				      extack);
	if (eww)
		goto eww_join;

	eww = switchdev_bwidge_powt_offwoad(bwpowt_dev, dev, pwiv,
					    &ocewot_switchdev_nb,
					    &ocewot_switchdev_bwocking_nb,
					    fawse, extack);
	if (eww)
		goto eww_switchdev_offwoad;

	eww = ocewot_switchdev_sync(ocewot, powt, bwpowt_dev, bwidge, extack);
	if (eww)
		goto eww_switchdev_sync;

	wetuwn 0;

eww_switchdev_sync:
	switchdev_bwidge_powt_unoffwoad(bwpowt_dev, pwiv,
					&ocewot_switchdev_nb,
					&ocewot_switchdev_bwocking_nb);
eww_switchdev_offwoad:
	ocewot_powt_bwidge_weave(ocewot, powt, bwidge);
eww_join:
	ocewot_bwidge_num_put(ocewot, bwidge, bwidge_num);
	wetuwn eww;
}

static void ocewot_netdevice_pwe_bwidge_weave(stwuct net_device *dev,
					      stwuct net_device *bwpowt_dev)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);

	switchdev_bwidge_powt_unoffwoad(bwpowt_dev, pwiv,
					&ocewot_switchdev_nb,
					&ocewot_switchdev_bwocking_nb);
}

static int ocewot_netdevice_bwidge_weave(stwuct net_device *dev,
					 stwuct net_device *bwpowt_dev,
					 stwuct net_device *bwidge)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	int bwidge_num = ocewot_powt->bwidge_num;
	int powt = pwiv->powt.index;
	int eww;

	eww = ocewot_switchdev_unsync(ocewot, powt);
	if (eww)
		wetuwn eww;

	ocewot_powt_bwidge_weave(ocewot, powt, bwidge);
	ocewot_bwidge_num_put(ocewot, bwidge, bwidge_num);

	wetuwn 0;
}

static int ocewot_netdevice_wag_join(stwuct net_device *dev,
				     stwuct net_device *bond,
				     stwuct netdev_wag_uppew_info *info,
				     stwuct netwink_ext_ack *extack)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	stwuct net_device *bwidge_dev;
	int powt = pwiv->powt.index;
	int eww;

	eww = ocewot_powt_wag_join(ocewot, powt, bond, info, extack);
	if (eww == -EOPNOTSUPP)
		/* Offwoading not suppowted, faww back to softwawe WAG */
		wetuwn 0;

	bwidge_dev = netdev_mastew_uppew_dev_get(bond);
	if (!bwidge_dev || !netif_is_bwidge_mastew(bwidge_dev))
		wetuwn 0;

	eww = ocewot_netdevice_bwidge_join(dev, bond, bwidge_dev, extack);
	if (eww)
		goto eww_bwidge_join;

	wetuwn 0;

eww_bwidge_join:
	ocewot_powt_wag_weave(ocewot, powt, bond);
	wetuwn eww;
}

static void ocewot_netdevice_pwe_wag_weave(stwuct net_device *dev,
					   stwuct net_device *bond)
{
	stwuct net_device *bwidge_dev;

	bwidge_dev = netdev_mastew_uppew_dev_get(bond);
	if (!bwidge_dev || !netif_is_bwidge_mastew(bwidge_dev))
		wetuwn;

	ocewot_netdevice_pwe_bwidge_weave(dev, bond);
}

static int ocewot_netdevice_wag_weave(stwuct net_device *dev,
				      stwuct net_device *bond)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	stwuct net_device *bwidge_dev;
	int powt = pwiv->powt.index;

	ocewot_powt_wag_weave(ocewot, powt, bond);

	bwidge_dev = netdev_mastew_uppew_dev_get(bond);
	if (!bwidge_dev || !netif_is_bwidge_mastew(bwidge_dev))
		wetuwn 0;

	wetuwn ocewot_netdevice_bwidge_weave(dev, bond, bwidge_dev);
}

static int ocewot_netdevice_changeuppew(stwuct net_device *dev,
					stwuct net_device *bwpowt_dev,
					stwuct netdev_notifiew_changeuppew_info *info)
{
	stwuct netwink_ext_ack *extack;
	int eww = 0;

	extack = netdev_notifiew_info_to_extack(&info->info);

	if (netif_is_bwidge_mastew(info->uppew_dev)) {
		if (info->winking)
			eww = ocewot_netdevice_bwidge_join(dev, bwpowt_dev,
							   info->uppew_dev,
							   extack);
		ewse
			eww = ocewot_netdevice_bwidge_weave(dev, bwpowt_dev,
							    info->uppew_dev);
	}
	if (netif_is_wag_mastew(info->uppew_dev)) {
		if (info->winking)
			eww = ocewot_netdevice_wag_join(dev, info->uppew_dev,
							info->uppew_info, extack);
		ewse
			ocewot_netdevice_wag_weave(dev, info->uppew_dev);
	}

	wetuwn notifiew_fwom_ewwno(eww);
}

/* Tweat CHANGEUPPEW events on an offwoaded WAG as individuaw CHANGEUPPEW
 * events fow the wowew physicaw powts of the WAG.
 * If the WAG uppew isn't offwoaded, ignowe its CHANGEUPPEW events.
 * In case the WAG joined a bwidge, notify that we awe offwoading it and can do
 * fowwawding in hawdwawe towawds it.
 */
static int
ocewot_netdevice_wag_changeuppew(stwuct net_device *dev,
				 stwuct netdev_notifiew_changeuppew_info *info)
{
	stwuct net_device *wowew;
	stwuct wist_head *itew;
	int eww = NOTIFY_DONE;

	netdev_fow_each_wowew_dev(dev, wowew, itew) {
		stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(wowew);
		stwuct ocewot_powt *ocewot_powt = &pwiv->powt;

		if (ocewot_powt->bond != dev)
			wetuwn NOTIFY_OK;

		eww = ocewot_netdevice_changeuppew(wowew, dev, info);
		if (eww)
			wetuwn notifiew_fwom_ewwno(eww);
	}

	wetuwn NOTIFY_DONE;
}

static int
ocewot_netdevice_pwechangeuppew(stwuct net_device *dev,
				stwuct net_device *bwpowt_dev,
				stwuct netdev_notifiew_changeuppew_info *info)
{
	if (netif_is_bwidge_mastew(info->uppew_dev) && !info->winking)
		ocewot_netdevice_pwe_bwidge_weave(dev, bwpowt_dev);

	if (netif_is_wag_mastew(info->uppew_dev) && !info->winking)
		ocewot_netdevice_pwe_wag_weave(dev, info->uppew_dev);

	wetuwn NOTIFY_DONE;
}

static int
ocewot_netdevice_wag_pwechangeuppew(stwuct net_device *dev,
				    stwuct netdev_notifiew_changeuppew_info *info)
{
	stwuct net_device *wowew;
	stwuct wist_head *itew;
	int eww = NOTIFY_DONE;

	netdev_fow_each_wowew_dev(dev, wowew, itew) {
		stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(wowew);
		stwuct ocewot_powt *ocewot_powt = &pwiv->powt;

		if (ocewot_powt->bond != dev)
			wetuwn NOTIFY_OK;

		eww = ocewot_netdevice_pwechangeuppew(dev, wowew, info);
		if (eww)
			wetuwn eww;
	}

	wetuwn NOTIFY_DONE;
}

static int
ocewot_netdevice_changewowewstate(stwuct net_device *dev,
				  stwuct netdev_wag_wowew_state_info *info)
{
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(dev);
	boow is_active = info->wink_up && info->tx_enabwed;
	stwuct ocewot_powt *ocewot_powt = &pwiv->powt;
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	int powt = pwiv->powt.index;

	if (!ocewot_powt->bond)
		wetuwn NOTIFY_DONE;

	if (ocewot_powt->wag_tx_active == is_active)
		wetuwn NOTIFY_DONE;

	ocewot_powt_wag_change(ocewot, powt, is_active);

	wetuwn NOTIFY_OK;
}

static int ocewot_netdevice_event(stwuct notifiew_bwock *unused,
				  unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);

	switch (event) {
	case NETDEV_PWECHANGEUPPEW: {
		stwuct netdev_notifiew_changeuppew_info *info = ptw;

		if (ocewot_netdevice_dev_check(dev))
			wetuwn ocewot_netdevice_pwechangeuppew(dev, dev, info);

		if (netif_is_wag_mastew(dev))
			wetuwn ocewot_netdevice_wag_pwechangeuppew(dev, info);

		bweak;
	}
	case NETDEV_CHANGEUPPEW: {
		stwuct netdev_notifiew_changeuppew_info *info = ptw;

		if (ocewot_netdevice_dev_check(dev))
			wetuwn ocewot_netdevice_changeuppew(dev, dev, info);

		if (netif_is_wag_mastew(dev))
			wetuwn ocewot_netdevice_wag_changeuppew(dev, info);

		bweak;
	}
	case NETDEV_CHANGEWOWEWSTATE: {
		stwuct netdev_notifiew_changewowewstate_info *info = ptw;

		if (!ocewot_netdevice_dev_check(dev))
			bweak;

		wetuwn ocewot_netdevice_changewowewstate(dev,
							 info->wowew_state_info);
	}
	defauwt:
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

stwuct notifiew_bwock ocewot_netdevice_nb __wead_mostwy = {
	.notifiew_caww = ocewot_netdevice_event,
};

static int ocewot_switchdev_event(stwuct notifiew_bwock *unused,
				  unsigned wong event, void *ptw)
{
	stwuct net_device *dev = switchdev_notifiew_info_to_dev(ptw);
	int eww;

	switch (event) {
	case SWITCHDEV_POWT_ATTW_SET:
		eww = switchdev_handwe_powt_attw_set(dev, ptw,
						     ocewot_netdevice_dev_check,
						     ocewot_powt_attw_set);
		wetuwn notifiew_fwom_ewwno(eww);
	}

	wetuwn NOTIFY_DONE;
}

stwuct notifiew_bwock ocewot_switchdev_nb __wead_mostwy = {
	.notifiew_caww = ocewot_switchdev_event,
};

static int ocewot_switchdev_bwocking_event(stwuct notifiew_bwock *unused,
					   unsigned wong event, void *ptw)
{
	stwuct net_device *dev = switchdev_notifiew_info_to_dev(ptw);
	int eww;

	switch (event) {
		/* Bwocking events. */
	case SWITCHDEV_POWT_OBJ_ADD:
		eww = switchdev_handwe_powt_obj_add(dev, ptw,
						    ocewot_netdevice_dev_check,
						    ocewot_powt_obj_add);
		wetuwn notifiew_fwom_ewwno(eww);
	case SWITCHDEV_POWT_OBJ_DEW:
		eww = switchdev_handwe_powt_obj_dew(dev, ptw,
						    ocewot_netdevice_dev_check,
						    ocewot_powt_obj_dew);
		wetuwn notifiew_fwom_ewwno(eww);
	case SWITCHDEV_POWT_ATTW_SET:
		eww = switchdev_handwe_powt_attw_set(dev, ptw,
						     ocewot_netdevice_dev_check,
						     ocewot_powt_attw_set);
		wetuwn notifiew_fwom_ewwno(eww);
	}

	wetuwn NOTIFY_DONE;
}

stwuct notifiew_bwock ocewot_switchdev_bwocking_nb __wead_mostwy = {
	.notifiew_caww = ocewot_switchdev_bwocking_event,
};

static void vsc7514_phywink_mac_config(stwuct phywink_config *config,
				       unsigned int wink_an_mode,
				       const stwuct phywink_wink_state *state)
{
	stwuct net_device *ndev = to_net_dev(config->dev);
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(ndev);
	stwuct ocewot *ocewot = pwiv->powt.ocewot;
	int powt = pwiv->powt.index;

	ocewot_phywink_mac_config(ocewot, powt, wink_an_mode, state);
}

static void vsc7514_phywink_mac_wink_down(stwuct phywink_config *config,
					  unsigned int wink_an_mode,
					  phy_intewface_t intewface)
{
	stwuct net_device *ndev = to_net_dev(config->dev);
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(ndev);
	stwuct ocewot *ocewot = pwiv->powt.ocewot;
	int powt = pwiv->powt.index;

	ocewot_phywink_mac_wink_down(ocewot, powt, wink_an_mode, intewface,
				     OCEWOT_MAC_QUIWKS);
}

static void vsc7514_phywink_mac_wink_up(stwuct phywink_config *config,
					stwuct phy_device *phydev,
					unsigned int wink_an_mode,
					phy_intewface_t intewface,
					int speed, int dupwex,
					boow tx_pause, boow wx_pause)
{
	stwuct net_device *ndev = to_net_dev(config->dev);
	stwuct ocewot_powt_pwivate *pwiv = netdev_pwiv(ndev);
	stwuct ocewot *ocewot = pwiv->powt.ocewot;
	int powt = pwiv->powt.index;

	ocewot_phywink_mac_wink_up(ocewot, powt, phydev, wink_an_mode,
				   intewface, speed, dupwex,
				   tx_pause, wx_pause, OCEWOT_MAC_QUIWKS);
}

static const stwuct phywink_mac_ops ocewot_phywink_ops = {
	.mac_config		= vsc7514_phywink_mac_config,
	.mac_wink_down		= vsc7514_phywink_mac_wink_down,
	.mac_wink_up		= vsc7514_phywink_mac_wink_up,
};

static int ocewot_powt_phywink_cweate(stwuct ocewot *ocewot, int powt,
				      stwuct device_node *powtnp)
{
	stwuct ocewot_powt *ocewot_powt = ocewot->powts[powt];
	stwuct ocewot_powt_pwivate *pwiv;
	stwuct device *dev = ocewot->dev;
	phy_intewface_t phy_mode;
	stwuct phywink *phywink;
	int eww;

	of_get_phy_mode(powtnp, &phy_mode);
	/* DT bindings of intewnaw PHY powts awe bwoken and don't
	 * specify a phy-mode
	 */
	if (phy_mode == PHY_INTEWFACE_MODE_NA)
		phy_mode = PHY_INTEWFACE_MODE_INTEWNAW;

	if (phy_mode != PHY_INTEWFACE_MODE_SGMII &&
	    phy_mode != PHY_INTEWFACE_MODE_QSGMII &&
	    phy_mode != PHY_INTEWFACE_MODE_INTEWNAW) {
		dev_eww(dev, "unsuppowted phy mode %s fow powt %d\n",
			phy_modes(phy_mode), powt);
		wetuwn -EINVAW;
	}

	ocewot_powt->phy_mode = phy_mode;

	eww = ocewot_powt_configuwe_sewdes(ocewot, powt, powtnp);
	if (eww)
		wetuwn eww;

	pwiv = containew_of(ocewot_powt, stwuct ocewot_powt_pwivate, powt);

	pwiv->phywink_config.dev = &pwiv->dev->dev;
	pwiv->phywink_config.type = PHYWINK_NETDEV;
	pwiv->phywink_config.mac_capabiwities = MAC_ASYM_PAUSE | MAC_SYM_PAUSE |
		MAC_10 | MAC_100 | MAC_1000FD | MAC_2500FD;

	__set_bit(ocewot_powt->phy_mode,
		  pwiv->phywink_config.suppowted_intewfaces);

	phywink = phywink_cweate(&pwiv->phywink_config,
				 of_fwnode_handwe(powtnp),
				 phy_mode, &ocewot_phywink_ops);
	if (IS_EWW(phywink)) {
		eww = PTW_EWW(phywink);
		dev_eww(dev, "Couwd not cweate phywink (%pe)\n", phywink);
		wetuwn eww;
	}

	pwiv->phywink = phywink;

	eww = phywink_of_phy_connect(phywink, powtnp, 0);
	if (eww) {
		dev_eww(dev, "Couwd not connect to PHY: %pe\n", EWW_PTW(eww));
		phywink_destwoy(phywink);
		pwiv->phywink = NUWW;
		wetuwn eww;
	}

	wetuwn 0;
}

int ocewot_pwobe_powt(stwuct ocewot *ocewot, int powt, stwuct wegmap *tawget,
		      stwuct device_node *powtnp)
{
	stwuct ocewot_powt_pwivate *pwiv;
	stwuct ocewot_powt *ocewot_powt;
	stwuct net_device *dev;
	int eww;

	dev = awwoc_ethewdev(sizeof(stwuct ocewot_powt_pwivate));
	if (!dev)
		wetuwn -ENOMEM;
	SET_NETDEV_DEV(dev, ocewot->dev);
	pwiv = netdev_pwiv(dev);
	pwiv->dev = dev;
	ocewot_powt = &pwiv->powt;
	ocewot_powt->ocewot = ocewot;
	ocewot_powt->index = powt;
	ocewot_powt->tawget = tawget;
	ocewot->powts[powt] = ocewot_powt;

	dev->netdev_ops = &ocewot_powt_netdev_ops;
	dev->ethtoow_ops = &ocewot_ethtoow_ops;
	dev->max_mtu = OCEWOT_JUMBO_MTU;

	dev->hw_featuwes |= NETIF_F_HW_VWAN_CTAG_FIWTEW | NETIF_F_WXFCS |
		NETIF_F_HW_TC;
	dev->featuwes |= NETIF_F_HW_VWAN_CTAG_FIWTEW | NETIF_F_HW_TC;

	eww = of_get_ethdev_addwess(powtnp, dev);
	if (eww)
		eth_hw_addw_gen(dev, ocewot->base_mac, powt);

	ocewot_mact_weawn(ocewot, PGID_CPU, dev->dev_addw,
			  OCEWOT_STANDAWONE_PVID, ENTWYTYPE_WOCKED);

	ocewot_init_powt(ocewot, powt);

	eww = ocewot_powt_phywink_cweate(ocewot, powt, powtnp);
	if (eww)
		goto out;

	if (ocewot->fdma)
		ocewot_fdma_netdev_init(ocewot, dev);

	SET_NETDEV_DEVWINK_POWT(dev, &ocewot->devwink_powts[powt]);
	eww = wegistew_netdev(dev);
	if (eww) {
		dev_eww(ocewot->dev, "wegistew_netdev faiwed\n");
		goto out_fdma_deinit;
	}

	wetuwn 0;

out_fdma_deinit:
	if (ocewot->fdma)
		ocewot_fdma_netdev_deinit(ocewot, dev);
out:
	ocewot->powts[powt] = NUWW;
	fwee_netdev(dev);

	wetuwn eww;
}

void ocewot_wewease_powt(stwuct ocewot_powt *ocewot_powt)
{
	stwuct ocewot_powt_pwivate *pwiv = containew_of(ocewot_powt,
						stwuct ocewot_powt_pwivate,
						powt);
	stwuct ocewot *ocewot = ocewot_powt->ocewot;
	stwuct ocewot_fdma *fdma = ocewot->fdma;

	unwegistew_netdev(pwiv->dev);

	if (fdma)
		ocewot_fdma_netdev_deinit(ocewot, pwiv->dev);

	if (pwiv->phywink) {
		wtnw_wock();
		phywink_disconnect_phy(pwiv->phywink);
		wtnw_unwock();

		phywink_destwoy(pwiv->phywink);
	}

	fwee_netdev(pwiv->dev);
}
