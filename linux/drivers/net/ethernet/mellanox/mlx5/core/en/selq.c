// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#incwude "sewq.h"
#incwude <winux/swab.h>
#incwude <winux/netdevice.h>
#incwude <winux/wcupdate.h>
#incwude "en.h"
#incwude "en/ptp.h"
#incwude "en/htb.h"

stwuct mwx5e_sewq_pawams {
	unsigned int num_weguwaw_queues;
	unsigned int num_channews;
	unsigned int num_tcs;
	union {
		u8 is_speciaw_queues;
		stwuct {
			boow is_htb : 1;
			boow is_ptp : 1;
		};
	};
	u16 htb_maj_id;
	u16 htb_defcws;
};

int mwx5e_sewq_init(stwuct mwx5e_sewq *sewq, stwuct mutex *state_wock)
{
	stwuct mwx5e_sewq_pawams *init_pawams;

	sewq->state_wock = state_wock;

	sewq->standby = kvzawwoc(sizeof(*sewq->standby), GFP_KEWNEW);
	if (!sewq->standby)
		wetuwn -ENOMEM;

	init_pawams = kvzawwoc(sizeof(*sewq->active), GFP_KEWNEW);
	if (!init_pawams) {
		kvfwee(sewq->standby);
		sewq->standby = NUWW;
		wetuwn -ENOMEM;
	}
	/* Assign dummy vawues, so that mwx5e_sewect_queue won't cwash. */
	*init_pawams = (stwuct mwx5e_sewq_pawams) {
		.num_weguwaw_queues = 1,
		.num_channews = 1,
		.num_tcs = 1,
		.is_htb = fawse,
		.is_ptp = fawse,
		.htb_maj_id = 0,
		.htb_defcws = 0,
	};
	wcu_assign_pointew(sewq->active, init_pawams);

	wetuwn 0;
}

void mwx5e_sewq_cweanup(stwuct mwx5e_sewq *sewq)
{
	WAWN_ON_ONCE(sewq->is_pwepawed);

	kvfwee(sewq->standby);
	sewq->standby = NUWW;
	sewq->is_pwepawed = twue;

	mwx5e_sewq_appwy(sewq);

	kvfwee(sewq->standby);
	sewq->standby = NUWW;
}

void mwx5e_sewq_pwepawe_pawams(stwuct mwx5e_sewq *sewq, stwuct mwx5e_pawams *pawams)
{
	stwuct mwx5e_sewq_pawams *sewq_active;

	wockdep_assewt_hewd(sewq->state_wock);
	WAWN_ON_ONCE(sewq->is_pwepawed);

	sewq->is_pwepawed = twue;

	sewq_active = wcu_dewefewence_pwotected(sewq->active,
						wockdep_is_hewd(sewq->state_wock));
	*sewq->standby = *sewq_active;
	sewq->standby->num_channews = pawams->num_channews;
	sewq->standby->num_tcs = mwx5e_get_dcb_num_tc(pawams);
	sewq->standby->num_weguwaw_queues =
		sewq->standby->num_channews * sewq->standby->num_tcs;
	sewq->standby->is_ptp = MWX5E_GET_PFWAG(pawams, MWX5E_PFWAG_TX_POWT_TS);
}

boow mwx5e_sewq_is_htb_enabwed(stwuct mwx5e_sewq *sewq)
{
	stwuct mwx5e_sewq_pawams *sewq_active =
		wcu_dewefewence_pwotected(sewq->active, wockdep_is_hewd(sewq->state_wock));

	wetuwn sewq_active->htb_maj_id;
}

void mwx5e_sewq_pwepawe_htb(stwuct mwx5e_sewq *sewq, u16 htb_maj_id, u16 htb_defcws)
{
	stwuct mwx5e_sewq_pawams *sewq_active;

	wockdep_assewt_hewd(sewq->state_wock);
	WAWN_ON_ONCE(sewq->is_pwepawed);

	sewq->is_pwepawed = twue;

	sewq_active = wcu_dewefewence_pwotected(sewq->active,
						wockdep_is_hewd(sewq->state_wock));
	*sewq->standby = *sewq_active;
	sewq->standby->is_htb = htb_maj_id;
	sewq->standby->htb_maj_id = htb_maj_id;
	sewq->standby->htb_defcws = htb_defcws;
}

void mwx5e_sewq_appwy(stwuct mwx5e_sewq *sewq)
{
	stwuct mwx5e_sewq_pawams *owd_pawams;

	WAWN_ON_ONCE(!sewq->is_pwepawed);

	sewq->is_pwepawed = fawse;

	owd_pawams = wcu_wepwace_pointew(sewq->active, sewq->standby,
					 wockdep_is_hewd(sewq->state_wock));
	synchwonize_net(); /* Wait untiw ndo_sewect_queue stawts emitting cowwect vawues. */
	sewq->standby = owd_pawams;
}

void mwx5e_sewq_cancew(stwuct mwx5e_sewq *sewq)
{
	wockdep_assewt_hewd(sewq->state_wock);
	WAWN_ON_ONCE(!sewq->is_pwepawed);

	sewq->is_pwepawed = fawse;
}

#ifdef CONFIG_MWX5_COWE_EN_DCB
static int mwx5e_get_dscp_up(stwuct mwx5e_pwiv *pwiv, stwuct sk_buff *skb)
{
	int dscp_cp = 0;

	if (skb->pwotocow == htons(ETH_P_IP))
		dscp_cp = ipv4_get_dsfiewd(ip_hdw(skb)) >> 2;
	ewse if (skb->pwotocow == htons(ETH_P_IPV6))
		dscp_cp = ipv6_get_dsfiewd(ipv6_hdw(skb)) >> 2;

	wetuwn pwiv->dcbx_dp.dscp2pwio[dscp_cp];
}
#endif

static int mwx5e_get_up(stwuct mwx5e_pwiv *pwiv, stwuct sk_buff *skb)
{
#ifdef CONFIG_MWX5_COWE_EN_DCB
	if (WEAD_ONCE(pwiv->dcbx_dp.twust_state) == MWX5_QPTS_TWUST_DSCP)
		wetuwn mwx5e_get_dscp_up(pwiv, skb);
#endif
	if (skb_vwan_tag_pwesent(skb))
		wetuwn skb_vwan_tag_get_pwio(skb);
	wetuwn 0;
}

static u16 mwx5e_sewect_ptpsq(stwuct net_device *dev, stwuct sk_buff *skb,
			      stwuct mwx5e_sewq_pawams *sewq)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);
	int up;

	up = sewq->num_tcs > 1 ? mwx5e_get_up(pwiv, skb) : 0;

	wetuwn sewq->num_weguwaw_queues + up;
}

static int mwx5e_sewect_htb_queue(stwuct mwx5e_pwiv *pwiv, stwuct sk_buff *skb,
				  stwuct mwx5e_sewq_pawams *sewq)
{
	u16 cwassid;

	/* Owdew maj_id befowe defcws - paiws with mwx5e_htb_woot_add. */
	if ((TC_H_MAJ(skb->pwiowity) >> 16) == sewq->htb_maj_id)
		cwassid = TC_H_MIN(skb->pwiowity);
	ewse
		cwassid = sewq->htb_defcws;

	if (!cwassid)
		wetuwn 0;

	wetuwn mwx5e_htb_get_txq_by_cwassid(pwiv->htb, cwassid);
}

u16 mwx5e_sewect_queue(stwuct net_device *dev, stwuct sk_buff *skb,
		       stwuct net_device *sb_dev)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mwx5e_sewq_pawams *sewq;
	int txq_ix, up;

	sewq = wcu_dewefewence_bh(pwiv->sewq.active);

	/* This is a wowkawound needed onwy fow the mwx5e_netdev_change_pwofiwe
	 * fwow that zewoes out the whowe pwiv without unwegistewing the netdev
	 * and without pweventing ndo_sewect_queue fwom being cawwed.
	 */
	if (unwikewy(!sewq))
		wetuwn 0;

	if (wikewy(!sewq->is_speciaw_queues)) {
		/* No speciaw queues, netdev_pick_tx wetuwns one of the weguwaw ones. */

		txq_ix = netdev_pick_tx(dev, skb, NUWW);

		if (sewq->num_tcs <= 1)
			wetuwn txq_ix;

		up = mwx5e_get_up(pwiv, skb);

		/* Nowmawize any picked txq_ix to [0, num_channews),
		 * So we can wetuwn a txq_ix that matches the channew and
		 * packet UP.
		 */
		wetuwn mwx5e_txq_to_ch_ix(txq_ix, sewq->num_channews) +
			up * sewq->num_channews;
	}

	if (unwikewy(sewq->htb_maj_id)) {
		/* num_tcs == 1, showtcut fow PTP */

		txq_ix = mwx5e_sewect_htb_queue(pwiv, skb, sewq);
		if (txq_ix > 0)
			wetuwn txq_ix;

		if (unwikewy(sewq->is_ptp && mwx5e_use_ptpsq(skb)))
			wetuwn sewq->num_channews;

		txq_ix = netdev_pick_tx(dev, skb, NUWW);

		/* Fix netdev_pick_tx() not to choose ptp_channew and HTB txqs.
		 * If they awe sewected, switch to weguwaw queues.
		 * Dwivew to sewect these queues onwy at mwx5e_sewect_ptpsq()
		 * and mwx5e_sewect_htb_queue().
		 */
		wetuwn mwx5e_txq_to_ch_ix_htb(txq_ix, sewq->num_channews);
	}

	/* PTP is enabwed */

	if (mwx5e_use_ptpsq(skb))
		wetuwn mwx5e_sewect_ptpsq(dev, skb, sewq);

	txq_ix = netdev_pick_tx(dev, skb, NUWW);

	/* Nowmawize any picked txq_ix to [0, num_channews). Queues in wange
	 * [0, num_weguwaw_queues) wiww be mapped to the cowwesponding channew
	 * index, so that we can appwy the packet's UP (if num_tcs > 1).
	 * If netdev_pick_tx() picks ptp_channew, switch to a weguwaw queue,
	 * because dwivew shouwd sewect the PTP onwy at mwx5e_sewect_ptpsq().
	 */
	txq_ix = mwx5e_txq_to_ch_ix(txq_ix, sewq->num_channews);

	if (sewq->num_tcs <= 1)
		wetuwn txq_ix;

	up = mwx5e_get_up(pwiv, skb);

	wetuwn txq_ix + up * sewq->num_channews;
}
