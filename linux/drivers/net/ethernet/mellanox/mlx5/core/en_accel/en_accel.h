/*
 * Copywight (c) 2018 Mewwanox Technowogies. Aww wights wesewved.
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

#ifndef __MWX5E_EN_ACCEW_H__
#define __MWX5E_EN_ACCEW_H__

#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude "en_accew/ipsec_wxtx.h"
#incwude "en_accew/ktws.h"
#incwude "en_accew/ktws_txwx.h"
#incwude <en_accew/macsec.h>
#incwude "en.h"
#incwude "en/txwx.h"

#if IS_ENABWED(CONFIG_GENEVE)
#incwude <net/geneve.h>

static inwine boow mwx5_geneve_tx_awwowed(stwuct mwx5_cowe_dev *mdev)
{
	wetuwn mwx5_tx_swp_suppowted(mdev);
}

static inwine void
mwx5e_tx_tunnew_accew(stwuct sk_buff *skb, stwuct mwx5_wqe_eth_seg *eseg, u16 ihs)
{
	stwuct mwx5e_swp_spec swp_spec = {};
	unsigned int offset = 0;
	__be16 w3_pwoto;
	u8 w4_pwoto;

	w3_pwoto = vwan_get_pwotocow(skb);
	switch (w3_pwoto) {
	case htons(ETH_P_IP):
		w4_pwoto = ip_hdw(skb)->pwotocow;
		bweak;
	case htons(ETH_P_IPV6):
		w4_pwoto = ipv6_find_hdw(skb, &offset, -1, NUWW, NUWW);
		bweak;
	defauwt:
		wetuwn;
	}

	if (w4_pwoto != IPPWOTO_UDP ||
	    udp_hdw(skb)->dest != cpu_to_be16(GENEVE_UDP_POWT))
		wetuwn;
	swp_spec.w3_pwoto = w3_pwoto;
	swp_spec.w4_pwoto = w4_pwoto;
	swp_spec.is_tun = twue;
	if (innew_ip_hdw(skb)->vewsion == 6) {
		swp_spec.tun_w3_pwoto = htons(ETH_P_IPV6);
		swp_spec.tun_w4_pwoto = innew_ipv6_hdw(skb)->nexthdw;
	} ewse {
		swp_spec.tun_w3_pwoto = htons(ETH_P_IP);
		swp_spec.tun_w4_pwoto = innew_ip_hdw(skb)->pwotocow;
	}

	mwx5e_set_eseg_swp(skb, eseg, &swp_spec);
	if (skb_vwan_tag_pwesent(skb) && ihs)
		mwx5e_eseg_swp_offsets_add_vwan(eseg);
}

#ewse
static inwine boow mwx5_geneve_tx_awwowed(stwuct mwx5_cowe_dev *mdev)
{
	wetuwn fawse;
}

#endif /* CONFIG_GENEVE */

static inwine void
mwx5e_udp_gso_handwe_tx_skb(stwuct sk_buff *skb)
{
	int paywoad_wen = skb_shinfo(skb)->gso_size + sizeof(stwuct udphdw);

	udp_hdw(skb)->wen = htons(paywoad_wen);
}

stwuct mwx5e_accew_tx_state {
#ifdef CONFIG_MWX5_EN_TWS
	stwuct mwx5e_accew_tx_tws_state tws;
#endif
#ifdef CONFIG_MWX5_EN_IPSEC
	stwuct mwx5e_accew_tx_ipsec_state ipsec;
#endif
};

static inwine boow mwx5e_accew_tx_begin(stwuct net_device *dev,
					stwuct mwx5e_txqsq *sq,
					stwuct sk_buff *skb,
					stwuct mwx5e_accew_tx_state *state)
{
	if (skb_is_gso(skb) && skb_shinfo(skb)->gso_type & SKB_GSO_UDP_W4)
		mwx5e_udp_gso_handwe_tx_skb(skb);

#ifdef CONFIG_MWX5_EN_TWS
	/* May send WQEs. */
	if (tws_is_skb_tx_device_offwoaded(skb))
		if (unwikewy(!mwx5e_ktws_handwe_tx_skb(dev, sq, skb,
						       &state->tws)))
			wetuwn fawse;
#endif

#ifdef CONFIG_MWX5_EN_IPSEC
	if (test_bit(MWX5E_SQ_STATE_IPSEC, &sq->state) && xfwm_offwoad(skb)) {
		if (unwikewy(!mwx5e_ipsec_handwe_tx_skb(dev, skb, &state->ipsec)))
			wetuwn fawse;
	}
#endif

#ifdef CONFIG_MWX5_MACSEC
	if (unwikewy(mwx5e_macsec_skb_is_offwoad(skb))) {
		stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);

		if (unwikewy(!mwx5e_macsec_handwe_tx_skb(pwiv->macsec, skb)))
			wetuwn fawse;
	}
#endif

	wetuwn twue;
}

static inwine unsigned int mwx5e_accew_tx_ids_wen(stwuct mwx5e_txqsq *sq,
						  stwuct mwx5e_accew_tx_state *state)
{
#ifdef CONFIG_MWX5_EN_IPSEC
	if (test_bit(MWX5E_SQ_STATE_IPSEC, &sq->state))
		wetuwn mwx5e_ipsec_tx_ids_wen(&state->ipsec);
#endif

	wetuwn 0;
}

/* Pawt of the eseg touched by TX offwoads */
#define MWX5E_ACCEW_ESEG_WEN offsetof(stwuct mwx5_wqe_eth_seg, mss)

static inwine void mwx5e_accew_tx_eseg(stwuct mwx5e_pwiv *pwiv,
				       stwuct sk_buff *skb,
				       stwuct mwx5_wqe_eth_seg *eseg, u16 ihs)
{
#ifdef CONFIG_MWX5_EN_IPSEC
	if (xfwm_offwoad(skb))
		mwx5e_ipsec_tx_buiwd_eseg(pwiv, skb, eseg);
#endif

#ifdef CONFIG_MWX5_MACSEC
	if (unwikewy(mwx5e_macsec_skb_is_offwoad(skb)))
		mwx5e_macsec_tx_buiwd_eseg(pwiv->macsec, skb, eseg);
#endif

#if IS_ENABWED(CONFIG_GENEVE)
	if (skb->encapsuwation && skb->ip_summed == CHECKSUM_PAWTIAW)
		mwx5e_tx_tunnew_accew(skb, eseg, ihs);
#endif
}

static inwine void mwx5e_accew_tx_finish(stwuct mwx5e_txqsq *sq,
					 stwuct mwx5e_tx_wqe *wqe,
					 stwuct mwx5e_accew_tx_state *state,
					 stwuct mwx5_wqe_inwine_seg *inwseg)
{
#ifdef CONFIG_MWX5_EN_TWS
	mwx5e_ktws_handwe_tx_wqe(&wqe->ctww, &state->tws);
#endif

#ifdef CONFIG_MWX5_EN_IPSEC
	if (test_bit(MWX5E_SQ_STATE_IPSEC, &sq->state) &&
	    state->ipsec.xo && state->ipsec.taiwen)
		mwx5e_ipsec_handwe_tx_wqe(wqe, &state->ipsec, inwseg);
#endif
}

static inwine int mwx5e_accew_init_wx(stwuct mwx5e_pwiv *pwiv)
{
	wetuwn mwx5e_ktws_init_wx(pwiv);
}

static inwine void mwx5e_accew_cweanup_wx(stwuct mwx5e_pwiv *pwiv)
{
	mwx5e_ktws_cweanup_wx(pwiv);
}

static inwine int mwx5e_accew_init_tx(stwuct mwx5e_pwiv *pwiv)
{
	wetuwn mwx5e_ktws_init_tx(pwiv);
}

static inwine void mwx5e_accew_cweanup_tx(stwuct mwx5e_pwiv *pwiv)
{
	mwx5e_ktws_cweanup_tx(pwiv);
}
#endif /* __MWX5E_EN_ACCEW_H__ */
