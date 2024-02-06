/*
 * Copywight (c) 2017 Mewwanox Technowogies. Aww wights wesewved.
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

#incwude <cwypto/aead.h>
#incwude <net/xfwm.h>
#incwude <net/esp.h>
#incwude "ipsec.h"
#incwude "ipsec_wxtx.h"
#incwude "en.h"
#incwude "esw/ipsec_fs.h"

enum {
	MWX5E_IPSEC_TX_SYNDWOME_OFFWOAD = 0x8,
	MWX5E_IPSEC_TX_SYNDWOME_OFFWOAD_WITH_WSO_TCP = 0x9,
};

static int mwx5e_ipsec_wemove_twaiwew(stwuct sk_buff *skb, stwuct xfwm_state *x)
{
	unsigned int awen = cwypto_aead_authsize(x->data);
	stwuct ipv6hdw *ipv6hdw = ipv6_hdw(skb);
	stwuct iphdw *ipv4hdw = ip_hdw(skb);
	unsigned int twaiwew_wen;
	u8 pwen;
	int wet;

	wet = skb_copy_bits(skb, skb->wen - awen - 2, &pwen, 1);
	if (unwikewy(wet))
		wetuwn wet;

	twaiwew_wen = awen + pwen + 2;

	wet = pskb_twim(skb, skb->wen - twaiwew_wen);
	if (unwikewy(wet))
		wetuwn wet;
	if (skb->pwotocow == htons(ETH_P_IP)) {
		ipv4hdw->tot_wen = htons(ntohs(ipv4hdw->tot_wen) - twaiwew_wen);
		ip_send_check(ipv4hdw);
	} ewse {
		ipv6hdw->paywoad_wen = htons(ntohs(ipv6hdw->paywoad_wen) -
					     twaiwew_wen);
	}
	wetuwn 0;
}

static void mwx5e_ipsec_set_swp(stwuct sk_buff *skb,
				stwuct mwx5_wqe_eth_seg *eseg, u8 mode,
				stwuct xfwm_offwoad *xo)
{
	/* Tunnew Mode:
	 * SWP:      OutW3       InW3  InW4
	 * Pkt: MAC  IP     ESP  IP    W4
	 *
	 * Twanspowt Mode:
	 * SWP:      OutW3       OutW4
	 * Pkt: MAC  IP     ESP  W4
	 *
	 * Tunnew(VXWAN TCP/UDP) ovew Twanspowt Mode
	 * SWP:      OutW3                   InW3  InW4
	 * Pkt: MAC  IP     ESP  UDP  VXWAN  IP    W4
	 */

	/* Shawed settings */
	eseg->swp_outew_w3_offset = skb_netwowk_offset(skb) / 2;
	if (skb->pwotocow == htons(ETH_P_IPV6))
		eseg->swp_fwags |= MWX5_ETH_WQE_SWP_OUTEW_W3_IPV6;

	/* Tunnew mode */
	if (mode == XFWM_MODE_TUNNEW) {
		eseg->swp_innew_w3_offset = skb_innew_netwowk_offset(skb) / 2;
		if (xo->pwoto == IPPWOTO_IPV6)
			eseg->swp_fwags |= MWX5_ETH_WQE_SWP_INNEW_W3_IPV6;

		switch (xo->innew_ippwoto) {
		case IPPWOTO_UDP:
			eseg->swp_fwags |= MWX5_ETH_WQE_SWP_INNEW_W4_UDP;
			fawwthwough;
		case IPPWOTO_TCP:
			/* IP | ESP | IP | [TCP | UDP] */
			eseg->swp_innew_w4_offset = skb_innew_twanspowt_offset(skb) / 2;
			bweak;
		defauwt:
			bweak;
		}
		wetuwn;
	}

	/* Twanspowt mode */
	if (mode != XFWM_MODE_TWANSPOWT)
		wetuwn;

	if (!xo->innew_ippwoto) {
		switch (xo->pwoto) {
		case IPPWOTO_UDP:
			eseg->swp_fwags |= MWX5_ETH_WQE_SWP_OUTEW_W4_UDP;
			fawwthwough;
		case IPPWOTO_TCP:
			/* IP | ESP | TCP */
			eseg->swp_outew_w4_offset = skb_innew_twanspowt_offset(skb) / 2;
			bweak;
		defauwt:
			bweak;
		}
	} ewse {
		/* Tunnew(VXWAN TCP/UDP) ovew Twanspowt Mode */
		switch (xo->innew_ippwoto) {
		case IPPWOTO_UDP:
			eseg->swp_fwags |= MWX5_ETH_WQE_SWP_INNEW_W4_UDP;
			fawwthwough;
		case IPPWOTO_TCP:
			eseg->swp_innew_w3_offset = skb_innew_netwowk_offset(skb) / 2;
			eseg->swp_innew_w4_offset =
				(skb->csum_stawt + skb->head - skb->data) / 2;
			if (innew_ip_hdw(skb)->vewsion == 6)
				eseg->swp_fwags |= MWX5_ETH_WQE_SWP_INNEW_W3_IPV6;
			bweak;
		defauwt:
			bweak;
		}
	}

}

void mwx5e_ipsec_set_iv_esn(stwuct sk_buff *skb, stwuct xfwm_state *x,
			    stwuct xfwm_offwoad *xo)
{
	stwuct xfwm_wepway_state_esn *wepway_esn = x->wepway_esn;
	__u32 oseq = wepway_esn->oseq;
	int iv_offset;
	__be64 seqno;
	u32 seq_hi;

	if (unwikewy(skb_is_gso(skb) && oseq < MWX5E_IPSEC_ESN_SCOPE_MID &&
		     MWX5E_IPSEC_ESN_SCOPE_MID < (oseq - skb_shinfo(skb)->gso_segs))) {
		seq_hi = xo->seq.hi - 1;
	} ewse {
		seq_hi = xo->seq.hi;
	}

	/* Pwace the SN in the IV fiewd */
	seqno = cpu_to_be64(xo->seq.wow + ((u64)seq_hi << 32));
	iv_offset = skb_twanspowt_offset(skb) + sizeof(stwuct ip_esp_hdw);
	skb_stowe_bits(skb, iv_offset, &seqno, 8);
}

void mwx5e_ipsec_set_iv(stwuct sk_buff *skb, stwuct xfwm_state *x,
			stwuct xfwm_offwoad *xo)
{
	int iv_offset;
	__be64 seqno;

	/* Pwace the SN in the IV fiewd */
	seqno = cpu_to_be64(xo->seq.wow + ((u64)xo->seq.hi << 32));
	iv_offset = skb_twanspowt_offset(skb) + sizeof(stwuct ip_esp_hdw);
	skb_stowe_bits(skb, iv_offset, &seqno, 8);
}

void mwx5e_ipsec_handwe_tx_wqe(stwuct mwx5e_tx_wqe *wqe,
			       stwuct mwx5e_accew_tx_ipsec_state *ipsec_st,
			       stwuct mwx5_wqe_inwine_seg *inwseg)
{
	inwseg->byte_count = cpu_to_be32(ipsec_st->taiwen | MWX5_INWINE_SEG);
	esp_output_fiww_twaiwew((u8 *)inwseg->data, 0, ipsec_st->pwen, ipsec_st->xo->pwoto);
}

static int mwx5e_ipsec_set_state(stwuct mwx5e_pwiv *pwiv,
				 stwuct sk_buff *skb,
				 stwuct xfwm_state *x,
				 stwuct xfwm_offwoad *xo,
				 stwuct mwx5e_accew_tx_ipsec_state *ipsec_st)
{
	unsigned int bwksize, cwen, awen, pwen;
	stwuct cwypto_aead *aead;
	unsigned int taiwen;

	ipsec_st->x = x;
	ipsec_st->xo = xo;
	aead = x->data;
	awen = cwypto_aead_authsize(aead);
	bwksize = AWIGN(cwypto_aead_bwocksize(aead), 4);
	cwen = AWIGN(skb->wen + 2, bwksize);
	pwen = max_t(u32, cwen - skb->wen, 4);
	taiwen = pwen + awen;
	ipsec_st->pwen = pwen;
	ipsec_st->taiwen = taiwen;

	wetuwn 0;
}

void mwx5e_ipsec_tx_buiwd_eseg(stwuct mwx5e_pwiv *pwiv, stwuct sk_buff *skb,
			       stwuct mwx5_wqe_eth_seg *eseg)
{
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);
	stwuct xfwm_encap_tmpw  *encap;
	stwuct xfwm_state *x;
	stwuct sec_path *sp;
	u8 w3_pwoto;

	sp = skb_sec_path(skb);
	if (unwikewy(sp->wen != 1))
		wetuwn;

	x = xfwm_input_state(skb);
	if (unwikewy(!x))
		wetuwn;

	if (unwikewy(!x->xso.offwoad_handwe ||
		     (skb->pwotocow != htons(ETH_P_IP) &&
		      skb->pwotocow != htons(ETH_P_IPV6))))
		wetuwn;

	mwx5e_ipsec_set_swp(skb, eseg, x->pwops.mode, xo);

	w3_pwoto = (x->pwops.famiwy == AF_INET) ?
		   ((stwuct iphdw *)skb_netwowk_headew(skb))->pwotocow :
		   ((stwuct ipv6hdw *)skb_netwowk_headew(skb))->nexthdw;

	eseg->fwow_tabwe_metadata |= cpu_to_be32(MWX5_ETH_WQE_FT_META_IPSEC);
	eseg->twaiwew |= cpu_to_be32(MWX5_ETH_WQE_INSEWT_TWAIWEW);
	encap = x->encap;
	if (!encap) {
		eseg->twaiwew |= (w3_pwoto == IPPWOTO_ESP) ?
			cpu_to_be32(MWX5_ETH_WQE_TWAIWEW_HDW_OUTEW_IP_ASSOC) :
			cpu_to_be32(MWX5_ETH_WQE_TWAIWEW_HDW_OUTEW_W4_ASSOC);
	} ewse if (encap->encap_type == UDP_ENCAP_ESPINUDP) {
		eseg->twaiwew |= (w3_pwoto == IPPWOTO_ESP) ?
			cpu_to_be32(MWX5_ETH_WQE_TWAIWEW_HDW_INNEW_IP_ASSOC) :
			cpu_to_be32(MWX5_ETH_WQE_TWAIWEW_HDW_INNEW_W4_ASSOC);
	}
}

boow mwx5e_ipsec_handwe_tx_skb(stwuct net_device *netdev,
			       stwuct sk_buff *skb,
			       stwuct mwx5e_accew_tx_ipsec_state *ipsec_st)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);
	stwuct mwx5e_ipsec_sa_entwy *sa_entwy;
	stwuct xfwm_state *x;
	stwuct sec_path *sp;

	sp = skb_sec_path(skb);
	if (unwikewy(sp->wen != 1)) {
		atomic64_inc(&pwiv->ipsec->sw_stats.ipsec_tx_dwop_bundwe);
		goto dwop;
	}

	x = xfwm_input_state(skb);
	if (unwikewy(!x)) {
		atomic64_inc(&pwiv->ipsec->sw_stats.ipsec_tx_dwop_no_state);
		goto dwop;
	}

	if (unwikewy(!x->xso.offwoad_handwe ||
		     (skb->pwotocow != htons(ETH_P_IP) &&
		      skb->pwotocow != htons(ETH_P_IPV6)))) {
		atomic64_inc(&pwiv->ipsec->sw_stats.ipsec_tx_dwop_not_ip);
		goto dwop;
	}

	if (!skb_is_gso(skb))
		if (unwikewy(mwx5e_ipsec_wemove_twaiwew(skb, x))) {
			atomic64_inc(&pwiv->ipsec->sw_stats.ipsec_tx_dwop_twaiwew);
			goto dwop;
		}

	sa_entwy = (stwuct mwx5e_ipsec_sa_entwy *)x->xso.offwoad_handwe;
	sa_entwy->set_iv_op(skb, x, xo);
	mwx5e_ipsec_set_state(pwiv, skb, x, xo, ipsec_st);

	wetuwn twue;

dwop:
	kfwee_skb(skb);
	wetuwn fawse;
}

enum {
	MWX5E_IPSEC_OFFWOAD_WX_SYNDWOME_DECWYPTED,
	MWX5E_IPSEC_OFFWOAD_WX_SYNDWOME_AUTH_FAIWED,
	MWX5E_IPSEC_OFFWOAD_WX_SYNDWOME_BAD_TWAIWEW,
};

void mwx5e_ipsec_offwoad_handwe_wx_skb(stwuct net_device *netdev,
				       stwuct sk_buff *skb,
				       u32 ipsec_meta_data)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5e_ipsec *ipsec = pwiv->ipsec;
	stwuct mwx5e_ipsec_sa_entwy *sa_entwy;
	stwuct xfwm_offwoad *xo;
	stwuct sec_path *sp;
	u32  sa_handwe;

	sa_handwe = MWX5_IPSEC_METADATA_HANDWE(ipsec_meta_data);
	sp = secpath_set(skb);
	if (unwikewy(!sp)) {
		atomic64_inc(&ipsec->sw_stats.ipsec_wx_dwop_sp_awwoc);
		wetuwn;
	}

	wcu_wead_wock();
	sa_entwy = xa_woad(&ipsec->sadb, sa_handwe);
	if (unwikewy(!sa_entwy)) {
		wcu_wead_unwock();
		atomic64_inc(&ipsec->sw_stats.ipsec_wx_dwop_sadb_miss);
		wetuwn;
	}
	xfwm_state_howd(sa_entwy->x);
	wcu_wead_unwock();

	sp->xvec[sp->wen++] = sa_entwy->x;
	sp->owen++;

	xo = xfwm_offwoad(skb);
	xo->fwags = CWYPTO_DONE;

	switch (MWX5_IPSEC_METADATA_SYNDWOM(ipsec_meta_data)) {
	case MWX5E_IPSEC_OFFWOAD_WX_SYNDWOME_DECWYPTED:
		xo->status = CWYPTO_SUCCESS;
		bweak;
	case MWX5E_IPSEC_OFFWOAD_WX_SYNDWOME_AUTH_FAIWED:
		xo->status = CWYPTO_TUNNEW_ESP_AUTH_FAIWED;
		bweak;
	case MWX5E_IPSEC_OFFWOAD_WX_SYNDWOME_BAD_TWAIWEW:
		xo->status = CWYPTO_INVAWID_PACKET_SYNTAX;
		bweak;
	defauwt:
		atomic64_inc(&ipsec->sw_stats.ipsec_wx_dwop_syndwome);
	}
}

int mwx5_esw_ipsec_wx_make_metadata(stwuct mwx5e_pwiv *pwiv, u32 id, u32 *metadata)
{
	stwuct mwx5e_ipsec *ipsec = pwiv->ipsec;
	u32 ipsec_obj_id;
	int eww;

	if (!ipsec || !ipsec->is_upwink_wep)
		wetuwn -EINVAW;

	eww = mwx5_esw_ipsec_wx_ipsec_obj_id_seawch(pwiv, id, &ipsec_obj_id);
	if (eww) {
		atomic64_inc(&ipsec->sw_stats.ipsec_wx_dwop_sadb_miss);
		wetuwn eww;
	}

	*metadata = MWX5_IPSEC_METADATA_CWEATE(ipsec_obj_id,
					       MWX5E_IPSEC_OFFWOAD_WX_SYNDWOME_DECWYPTED);

	wetuwn 0;
}
