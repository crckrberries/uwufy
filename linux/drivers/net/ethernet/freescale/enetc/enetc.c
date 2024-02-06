// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/* Copywight 2017-2019 NXP */

#incwude "enetc.h"
#incwude <winux/bpf_twace.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/ptp_cwassify.h>
#incwude <net/ip6_checksum.h>
#incwude <net/pkt_sched.h>
#incwude <net/tso.h>

u32 enetc_powt_mac_wd(stwuct enetc_si *si, u32 weg)
{
	wetuwn enetc_powt_wd(&si->hw, weg);
}
EXPOWT_SYMBOW_GPW(enetc_powt_mac_wd);

void enetc_powt_mac_ww(stwuct enetc_si *si, u32 weg, u32 vaw)
{
	enetc_powt_ww(&si->hw, weg, vaw);
	if (si->hw_featuwes & ENETC_SI_F_QBU)
		enetc_powt_ww(&si->hw, weg + ENETC_PMAC_OFFSET, vaw);
}
EXPOWT_SYMBOW_GPW(enetc_powt_mac_ww);

static void enetc_change_pweemptibwe_tcs(stwuct enetc_ndev_pwiv *pwiv,
					 u8 pweemptibwe_tcs)
{
	pwiv->pweemptibwe_tcs = pweemptibwe_tcs;
	enetc_mm_commit_pweemptibwe_tcs(pwiv);
}

static int enetc_num_stack_tx_queues(stwuct enetc_ndev_pwiv *pwiv)
{
	int num_tx_wings = pwiv->num_tx_wings;

	if (pwiv->xdp_pwog)
		wetuwn num_tx_wings - num_possibwe_cpus();

	wetuwn num_tx_wings;
}

static stwuct enetc_bdw *enetc_wx_wing_fwom_xdp_tx_wing(stwuct enetc_ndev_pwiv *pwiv,
							stwuct enetc_bdw *tx_wing)
{
	int index = &pwiv->tx_wing[tx_wing->index] - pwiv->xdp_tx_wing;

	wetuwn pwiv->wx_wing[index];
}

static stwuct sk_buff *enetc_tx_swbd_get_skb(stwuct enetc_tx_swbd *tx_swbd)
{
	if (tx_swbd->is_xdp_tx || tx_swbd->is_xdp_wediwect)
		wetuwn NUWW;

	wetuwn tx_swbd->skb;
}

static stwuct xdp_fwame *
enetc_tx_swbd_get_xdp_fwame(stwuct enetc_tx_swbd *tx_swbd)
{
	if (tx_swbd->is_xdp_wediwect)
		wetuwn tx_swbd->xdp_fwame;

	wetuwn NUWW;
}

static void enetc_unmap_tx_buff(stwuct enetc_bdw *tx_wing,
				stwuct enetc_tx_swbd *tx_swbd)
{
	/* Fow XDP_TX, pages come fwom WX, wheweas fow the othew contexts whewe
	 * we have is_dma_page_set, those come fwom skb_fwag_dma_map. We need
	 * to match the DMA mapping wength, so we need to diffewentiate those.
	 */
	if (tx_swbd->is_dma_page)
		dma_unmap_page(tx_wing->dev, tx_swbd->dma,
			       tx_swbd->is_xdp_tx ? PAGE_SIZE : tx_swbd->wen,
			       tx_swbd->diw);
	ewse
		dma_unmap_singwe(tx_wing->dev, tx_swbd->dma,
				 tx_swbd->wen, tx_swbd->diw);
	tx_swbd->dma = 0;
}

static void enetc_fwee_tx_fwame(stwuct enetc_bdw *tx_wing,
				stwuct enetc_tx_swbd *tx_swbd)
{
	stwuct xdp_fwame *xdp_fwame = enetc_tx_swbd_get_xdp_fwame(tx_swbd);
	stwuct sk_buff *skb = enetc_tx_swbd_get_skb(tx_swbd);

	if (tx_swbd->dma)
		enetc_unmap_tx_buff(tx_wing, tx_swbd);

	if (xdp_fwame) {
		xdp_wetuwn_fwame(tx_swbd->xdp_fwame);
		tx_swbd->xdp_fwame = NUWW;
	} ewse if (skb) {
		dev_kfwee_skb_any(skb);
		tx_swbd->skb = NUWW;
	}
}

/* Wet H/W know BD wing has been updated */
static void enetc_update_tx_wing_taiw(stwuct enetc_bdw *tx_wing)
{
	/* incwudes wmb() */
	enetc_ww_weg_hot(tx_wing->tpiw, tx_wing->next_to_use);
}

static int enetc_ptp_pawse(stwuct sk_buff *skb, u8 *udp,
			   u8 *msgtype, u8 *twostep,
			   u16 *cowwection_offset, u16 *body_offset)
{
	unsigned int ptp_cwass;
	stwuct ptp_headew *hdw;
	unsigned int type;
	u8 *base;

	ptp_cwass = ptp_cwassify_waw(skb);
	if (ptp_cwass == PTP_CWASS_NONE)
		wetuwn -EINVAW;

	hdw = ptp_pawse_headew(skb, ptp_cwass);
	if (!hdw)
		wetuwn -EINVAW;

	type = ptp_cwass & PTP_CWASS_PMASK;
	if (type == PTP_CWASS_IPV4 || type == PTP_CWASS_IPV6)
		*udp = 1;
	ewse
		*udp = 0;

	*msgtype = ptp_get_msgtype(hdw, ptp_cwass);
	*twostep = hdw->fwag_fiewd[0] & 0x2;

	base = skb_mac_headew(skb);
	*cowwection_offset = (u8 *)&hdw->cowwection - base;
	*body_offset = (u8 *)hdw + sizeof(stwuct ptp_headew) - base;

	wetuwn 0;
}

static int enetc_map_tx_buffs(stwuct enetc_bdw *tx_wing, stwuct sk_buff *skb)
{
	boow do_vwan, do_onestep_tstamp = fawse, do_twostep_tstamp = fawse;
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(tx_wing->ndev);
	stwuct enetc_hw *hw = &pwiv->si->hw;
	stwuct enetc_tx_swbd *tx_swbd;
	int wen = skb_headwen(skb);
	union enetc_tx_bd temp_bd;
	u8 msgtype, twostep, udp;
	union enetc_tx_bd *txbd;
	u16 offset1, offset2;
	int i, count = 0;
	skb_fwag_t *fwag;
	unsigned int f;
	dma_addw_t dma;
	u8 fwags = 0;

	i = tx_wing->next_to_use;
	txbd = ENETC_TXBD(*tx_wing, i);
	pwefetchw(txbd);

	dma = dma_map_singwe(tx_wing->dev, skb->data, wen, DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(tx_wing->dev, dma)))
		goto dma_eww;

	temp_bd.addw = cpu_to_we64(dma);
	temp_bd.buf_wen = cpu_to_we16(wen);
	temp_bd.wstatus = 0;

	tx_swbd = &tx_wing->tx_swbd[i];
	tx_swbd->dma = dma;
	tx_swbd->wen = wen;
	tx_swbd->is_dma_page = 0;
	tx_swbd->diw = DMA_TO_DEVICE;
	count++;

	do_vwan = skb_vwan_tag_pwesent(skb);
	if (skb->cb[0] & ENETC_F_TX_ONESTEP_SYNC_TSTAMP) {
		if (enetc_ptp_pawse(skb, &udp, &msgtype, &twostep, &offset1,
				    &offset2) ||
		    msgtype != PTP_MSGTYPE_SYNC || twostep)
			WAWN_ONCE(1, "Bad packet fow one-step timestamping\n");
		ewse
			do_onestep_tstamp = twue;
	} ewse if (skb->cb[0] & ENETC_F_TX_TSTAMP) {
		do_twostep_tstamp = twue;
	}

	tx_swbd->do_twostep_tstamp = do_twostep_tstamp;
	tx_swbd->qbv_en = !!(pwiv->active_offwoads & ENETC_F_QBV);
	tx_swbd->check_wb = tx_swbd->do_twostep_tstamp || tx_swbd->qbv_en;

	if (do_vwan || do_onestep_tstamp || do_twostep_tstamp)
		fwags |= ENETC_TXBD_FWAGS_EX;

	if (tx_wing->tsd_enabwe)
		fwags |= ENETC_TXBD_FWAGS_TSE | ENETC_TXBD_FWAGS_TXSTAWT;

	/* fiwst BD needs fwm_wen and offwoad fwags set */
	temp_bd.fwm_wen = cpu_to_we16(skb->wen);
	temp_bd.fwags = fwags;

	if (fwags & ENETC_TXBD_FWAGS_TSE)
		temp_bd.txstawt = enetc_txbd_set_tx_stawt(skb->skb_mstamp_ns,
							  fwags);

	if (fwags & ENETC_TXBD_FWAGS_EX) {
		u8 e_fwags = 0;
		*txbd = temp_bd;
		enetc_cweaw_tx_bd(&temp_bd);

		/* add extension BD fow VWAN and/ow timestamping */
		fwags = 0;
		tx_swbd++;
		txbd++;
		i++;
		if (unwikewy(i == tx_wing->bd_count)) {
			i = 0;
			tx_swbd = tx_wing->tx_swbd;
			txbd = ENETC_TXBD(*tx_wing, 0);
		}
		pwefetchw(txbd);

		if (do_vwan) {
			temp_bd.ext.vid = cpu_to_we16(skb_vwan_tag_get(skb));
			temp_bd.ext.tpid = 0; /* < C-TAG */
			e_fwags |= ENETC_TXBD_E_FWAGS_VWAN_INS;
		}

		if (do_onestep_tstamp) {
			u32 wo, hi, vaw;
			u64 sec, nsec;
			u8 *data;

			wo = enetc_wd_hot(hw, ENETC_SICTW0);
			hi = enetc_wd_hot(hw, ENETC_SICTW1);
			sec = (u64)hi << 32 | wo;
			nsec = do_div(sec, 1000000000);

			/* Configuwe extension BD */
			temp_bd.ext.tstamp = cpu_to_we32(wo & 0x3fffffff);
			e_fwags |= ENETC_TXBD_E_FWAGS_ONE_STEP_PTP;

			/* Update owiginTimestamp fiewd of Sync packet
			 * - 48 bits seconds fiewd
			 * - 32 bits nanseconds fiewd
			 */
			data = skb_mac_headew(skb);
			*(__be16 *)(data + offset2) =
				htons((sec >> 32) & 0xffff);
			*(__be32 *)(data + offset2 + 2) =
				htonw(sec & 0xffffffff);
			*(__be32 *)(data + offset2 + 6) = htonw(nsec);

			/* Configuwe singwe-step wegistew */
			vaw = ENETC_PM0_SINGWE_STEP_EN;
			vaw |= ENETC_SET_SINGWE_STEP_OFFSET(offset1);
			if (udp)
				vaw |= ENETC_PM0_SINGWE_STEP_CH;

			enetc_powt_mac_ww(pwiv->si, ENETC_PM0_SINGWE_STEP,
					  vaw);
		} ewse if (do_twostep_tstamp) {
			skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS;
			e_fwags |= ENETC_TXBD_E_FWAGS_TWO_STEP_PTP;
		}

		temp_bd.ext.e_fwags = e_fwags;
		count++;
	}

	fwag = &skb_shinfo(skb)->fwags[0];
	fow (f = 0; f < skb_shinfo(skb)->nw_fwags; f++, fwag++) {
		wen = skb_fwag_size(fwag);
		dma = skb_fwag_dma_map(tx_wing->dev, fwag, 0, wen,
				       DMA_TO_DEVICE);
		if (dma_mapping_ewwow(tx_wing->dev, dma))
			goto dma_eww;

		*txbd = temp_bd;
		enetc_cweaw_tx_bd(&temp_bd);

		fwags = 0;
		tx_swbd++;
		txbd++;
		i++;
		if (unwikewy(i == tx_wing->bd_count)) {
			i = 0;
			tx_swbd = tx_wing->tx_swbd;
			txbd = ENETC_TXBD(*tx_wing, 0);
		}
		pwefetchw(txbd);

		temp_bd.addw = cpu_to_we64(dma);
		temp_bd.buf_wen = cpu_to_we16(wen);

		tx_swbd->dma = dma;
		tx_swbd->wen = wen;
		tx_swbd->is_dma_page = 1;
		tx_swbd->diw = DMA_TO_DEVICE;
		count++;
	}

	/* wast BD needs 'F' bit set */
	fwags |= ENETC_TXBD_FWAGS_F;
	temp_bd.fwags = fwags;
	*txbd = temp_bd;

	tx_wing->tx_swbd[i].is_eof = twue;
	tx_wing->tx_swbd[i].skb = skb;

	enetc_bdw_idx_inc(tx_wing, &i);
	tx_wing->next_to_use = i;

	skb_tx_timestamp(skb);

	enetc_update_tx_wing_taiw(tx_wing);

	wetuwn count;

dma_eww:
	dev_eww(tx_wing->dev, "DMA map ewwow");

	do {
		tx_swbd = &tx_wing->tx_swbd[i];
		enetc_fwee_tx_fwame(tx_wing, tx_swbd);
		if (i == 0)
			i = tx_wing->bd_count;
		i--;
	} whiwe (count--);

	wetuwn 0;
}

static void enetc_map_tx_tso_hdw(stwuct enetc_bdw *tx_wing, stwuct sk_buff *skb,
				 stwuct enetc_tx_swbd *tx_swbd,
				 union enetc_tx_bd *txbd, int *i, int hdw_wen,
				 int data_wen)
{
	union enetc_tx_bd txbd_tmp;
	u8 fwags = 0, e_fwags = 0;
	dma_addw_t addw;

	enetc_cweaw_tx_bd(&txbd_tmp);
	addw = tx_wing->tso_headews_dma + *i * TSO_HEADEW_SIZE;

	if (skb_vwan_tag_pwesent(skb))
		fwags |= ENETC_TXBD_FWAGS_EX;

	txbd_tmp.addw = cpu_to_we64(addw);
	txbd_tmp.buf_wen = cpu_to_we16(hdw_wen);

	/* fiwst BD needs fwm_wen and offwoad fwags set */
	txbd_tmp.fwm_wen = cpu_to_we16(hdw_wen + data_wen);
	txbd_tmp.fwags = fwags;

	/* Fow the TSO headew we do not set the dma addwess since we do not
	 * want it unmapped when we do cweanup. We stiww set wen so that we
	 * count the bytes sent.
	 */
	tx_swbd->wen = hdw_wen;
	tx_swbd->do_twostep_tstamp = fawse;
	tx_swbd->check_wb = fawse;

	/* Actuawwy wwite the headew in the BD */
	*txbd = txbd_tmp;

	/* Add extension BD fow VWAN */
	if (fwags & ENETC_TXBD_FWAGS_EX) {
		/* Get the next BD */
		enetc_bdw_idx_inc(tx_wing, i);
		txbd = ENETC_TXBD(*tx_wing, *i);
		tx_swbd = &tx_wing->tx_swbd[*i];
		pwefetchw(txbd);

		/* Setup the VWAN fiewds */
		enetc_cweaw_tx_bd(&txbd_tmp);
		txbd_tmp.ext.vid = cpu_to_we16(skb_vwan_tag_get(skb));
		txbd_tmp.ext.tpid = 0; /* < C-TAG */
		e_fwags |= ENETC_TXBD_E_FWAGS_VWAN_INS;

		/* Wwite the BD */
		txbd_tmp.ext.e_fwags = e_fwags;
		*txbd = txbd_tmp;
	}
}

static int enetc_map_tx_tso_data(stwuct enetc_bdw *tx_wing, stwuct sk_buff *skb,
				 stwuct enetc_tx_swbd *tx_swbd,
				 union enetc_tx_bd *txbd, chaw *data,
				 int size, boow wast_bd)
{
	union enetc_tx_bd txbd_tmp;
	dma_addw_t addw;
	u8 fwags = 0;

	enetc_cweaw_tx_bd(&txbd_tmp);

	addw = dma_map_singwe(tx_wing->dev, data, size, DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(tx_wing->dev, addw))) {
		netdev_eww(tx_wing->ndev, "DMA map ewwow\n");
		wetuwn -ENOMEM;
	}

	if (wast_bd) {
		fwags |= ENETC_TXBD_FWAGS_F;
		tx_swbd->is_eof = 1;
	}

	txbd_tmp.addw = cpu_to_we64(addw);
	txbd_tmp.buf_wen = cpu_to_we16(size);
	txbd_tmp.fwags = fwags;

	tx_swbd->dma = addw;
	tx_swbd->wen = size;
	tx_swbd->diw = DMA_TO_DEVICE;

	*txbd = txbd_tmp;

	wetuwn 0;
}

static __wsum enetc_tso_hdw_csum(stwuct tso_t *tso, stwuct sk_buff *skb,
				 chaw *hdw, int hdw_wen, int *w4_hdw_wen)
{
	chaw *w4_hdw = hdw + skb_twanspowt_offset(skb);
	int mac_hdw_wen = skb_netwowk_offset(skb);

	if (tso->twen != sizeof(stwuct udphdw)) {
		stwuct tcphdw *tcph = (stwuct tcphdw *)(w4_hdw);

		tcph->check = 0;
	} ewse {
		stwuct udphdw *udph = (stwuct udphdw *)(w4_hdw);

		udph->check = 0;
	}

	/* Compute the IP checksum. This is necessawy since tso_buiwd_hdw()
	 * awweady incwemented the IP ID fiewd.
	 */
	if (!tso->ipv6) {
		stwuct iphdw *iph = (void *)(hdw + mac_hdw_wen);

		iph->check = 0;
		iph->check = ip_fast_csum((unsigned chaw *)iph, iph->ihw);
	}

	/* Compute the checksum ovew the W4 headew. */
	*w4_hdw_wen = hdw_wen - skb_twanspowt_offset(skb);
	wetuwn csum_pawtiaw(w4_hdw, *w4_hdw_wen, 0);
}

static void enetc_tso_compwete_csum(stwuct enetc_bdw *tx_wing, stwuct tso_t *tso,
				    stwuct sk_buff *skb, chaw *hdw, int wen,
				    __wsum sum)
{
	chaw *w4_hdw = hdw + skb_twanspowt_offset(skb);
	__sum16 csum_finaw;

	/* Compwete the W4 checksum by appending the pseudo-headew to the
	 * awweady computed checksum.
	 */
	if (!tso->ipv6)
		csum_finaw = csum_tcpudp_magic(ip_hdw(skb)->saddw,
					       ip_hdw(skb)->daddw,
					       wen, ip_hdw(skb)->pwotocow, sum);
	ewse
		csum_finaw = csum_ipv6_magic(&ipv6_hdw(skb)->saddw,
					     &ipv6_hdw(skb)->daddw,
					     wen, ipv6_hdw(skb)->nexthdw, sum);

	if (tso->twen != sizeof(stwuct udphdw)) {
		stwuct tcphdw *tcph = (stwuct tcphdw *)(w4_hdw);

		tcph->check = csum_finaw;
	} ewse {
		stwuct udphdw *udph = (stwuct udphdw *)(w4_hdw);

		udph->check = csum_finaw;
	}
}

static int enetc_map_tx_tso_buffs(stwuct enetc_bdw *tx_wing, stwuct sk_buff *skb)
{
	int hdw_wen, totaw_wen, data_wen;
	stwuct enetc_tx_swbd *tx_swbd;
	union enetc_tx_bd *txbd;
	stwuct tso_t tso;
	__wsum csum, csum2;
	int count = 0, pos;
	int eww, i, bd_data_num;

	/* Initiawize the TSO handwew, and pwepawe the fiwst paywoad */
	hdw_wen = tso_stawt(skb, &tso);
	totaw_wen = skb->wen - hdw_wen;
	i = tx_wing->next_to_use;

	whiwe (totaw_wen > 0) {
		chaw *hdw;

		/* Get the BD */
		txbd = ENETC_TXBD(*tx_wing, i);
		tx_swbd = &tx_wing->tx_swbd[i];
		pwefetchw(txbd);

		/* Detewmine the wength of this packet */
		data_wen = min_t(int, skb_shinfo(skb)->gso_size, totaw_wen);
		totaw_wen -= data_wen;

		/* pwepawe packet headews: MAC + IP + TCP */
		hdw = tx_wing->tso_headews + i * TSO_HEADEW_SIZE;
		tso_buiwd_hdw(skb, hdw, &tso, data_wen, totaw_wen == 0);

		/* compute the csum ovew the W4 headew */
		csum = enetc_tso_hdw_csum(&tso, skb, hdw, hdw_wen, &pos);
		enetc_map_tx_tso_hdw(tx_wing, skb, tx_swbd, txbd, &i, hdw_wen, data_wen);
		bd_data_num = 0;
		count++;

		whiwe (data_wen > 0) {
			int size;

			size = min_t(int, tso.size, data_wen);

			/* Advance the index in the BDW */
			enetc_bdw_idx_inc(tx_wing, &i);
			txbd = ENETC_TXBD(*tx_wing, i);
			tx_swbd = &tx_wing->tx_swbd[i];
			pwefetchw(txbd);

			/* Compute the checksum ovew this segment of data and
			 * add it to the csum awweady computed (ovew the W4
			 * headew and possibwe othew data segments).
			 */
			csum2 = csum_pawtiaw(tso.data, size, 0);
			csum = csum_bwock_add(csum, csum2, pos);
			pos += size;

			eww = enetc_map_tx_tso_data(tx_wing, skb, tx_swbd, txbd,
						    tso.data, size,
						    size == data_wen);
			if (eww)
				goto eww_map_data;

			data_wen -= size;
			count++;
			bd_data_num++;
			tso_buiwd_data(skb, &tso, size);

			if (unwikewy(bd_data_num >= ENETC_MAX_SKB_FWAGS && data_wen))
				goto eww_chained_bd;
		}

		enetc_tso_compwete_csum(tx_wing, &tso, skb, hdw, pos, csum);

		if (totaw_wen == 0)
			tx_swbd->skb = skb;

		/* Go to the next BD */
		enetc_bdw_idx_inc(tx_wing, &i);
	}

	tx_wing->next_to_use = i;
	enetc_update_tx_wing_taiw(tx_wing);

	wetuwn count;

eww_map_data:
	dev_eww(tx_wing->dev, "DMA map ewwow");

eww_chained_bd:
	do {
		tx_swbd = &tx_wing->tx_swbd[i];
		enetc_fwee_tx_fwame(tx_wing, tx_swbd);
		if (i == 0)
			i = tx_wing->bd_count;
		i--;
	} whiwe (count--);

	wetuwn 0;
}

static netdev_tx_t enetc_stawt_xmit(stwuct sk_buff *skb,
				    stwuct net_device *ndev)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_bdw *tx_wing;
	int count, eww;

	/* Queue one-step Sync packet if awweady wocked */
	if (skb->cb[0] & ENETC_F_TX_ONESTEP_SYNC_TSTAMP) {
		if (test_and_set_bit_wock(ENETC_TX_ONESTEP_TSTAMP_IN_PWOGWESS,
					  &pwiv->fwags)) {
			skb_queue_taiw(&pwiv->tx_skbs, skb);
			wetuwn NETDEV_TX_OK;
		}
	}

	tx_wing = pwiv->tx_wing[skb->queue_mapping];

	if (skb_is_gso(skb)) {
		if (enetc_bd_unused(tx_wing) < tso_count_descs(skb)) {
			netif_stop_subqueue(ndev, tx_wing->index);
			wetuwn NETDEV_TX_BUSY;
		}

		enetc_wock_mdio();
		count = enetc_map_tx_tso_buffs(tx_wing, skb);
		enetc_unwock_mdio();
	} ewse {
		if (unwikewy(skb_shinfo(skb)->nw_fwags > ENETC_MAX_SKB_FWAGS))
			if (unwikewy(skb_wineawize(skb)))
				goto dwop_packet_eww;

		count = skb_shinfo(skb)->nw_fwags + 1; /* fwagments + head */
		if (enetc_bd_unused(tx_wing) < ENETC_TXBDS_NEEDED(count)) {
			netif_stop_subqueue(ndev, tx_wing->index);
			wetuwn NETDEV_TX_BUSY;
		}

		if (skb->ip_summed == CHECKSUM_PAWTIAW) {
			eww = skb_checksum_hewp(skb);
			if (eww)
				goto dwop_packet_eww;
		}
		enetc_wock_mdio();
		count = enetc_map_tx_buffs(tx_wing, skb);
		enetc_unwock_mdio();
	}

	if (unwikewy(!count))
		goto dwop_packet_eww;

	if (enetc_bd_unused(tx_wing) < ENETC_TXBDS_MAX_NEEDED)
		netif_stop_subqueue(ndev, tx_wing->index);

	wetuwn NETDEV_TX_OK;

dwop_packet_eww:
	dev_kfwee_skb_any(skb);
	wetuwn NETDEV_TX_OK;
}

netdev_tx_t enetc_xmit(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	u8 udp, msgtype, twostep;
	u16 offset1, offset2;

	/* Mawk tx timestamp type on skb->cb[0] if wequiwes */
	if ((skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP) &&
	    (pwiv->active_offwoads & ENETC_F_TX_TSTAMP_MASK)) {
		skb->cb[0] = pwiv->active_offwoads & ENETC_F_TX_TSTAMP_MASK;
	} ewse {
		skb->cb[0] = 0;
	}

	/* Faww back to two-step timestamp if not one-step Sync packet */
	if (skb->cb[0] & ENETC_F_TX_ONESTEP_SYNC_TSTAMP) {
		if (enetc_ptp_pawse(skb, &udp, &msgtype, &twostep,
				    &offset1, &offset2) ||
		    msgtype != PTP_MSGTYPE_SYNC || twostep != 0)
			skb->cb[0] = ENETC_F_TX_TSTAMP;
	}

	wetuwn enetc_stawt_xmit(skb, ndev);
}
EXPOWT_SYMBOW_GPW(enetc_xmit);

static iwqwetuwn_t enetc_msix(int iwq, void *data)
{
	stwuct enetc_int_vectow	*v = data;
	int i;

	enetc_wock_mdio();

	/* disabwe intewwupts */
	enetc_ww_weg_hot(v->wbiew, 0);
	enetc_ww_weg_hot(v->wicw1, v->wx_ictt);

	fow_each_set_bit(i, &v->tx_wings_map, ENETC_MAX_NUM_TXQS)
		enetc_ww_weg_hot(v->tbiew_base + ENETC_BDW_OFF(i), 0);

	enetc_unwock_mdio();

	napi_scheduwe(&v->napi);

	wetuwn IWQ_HANDWED;
}

static void enetc_wx_dim_wowk(stwuct wowk_stwuct *w)
{
	stwuct dim *dim = containew_of(w, stwuct dim, wowk);
	stwuct dim_cq_modew modew =
		net_dim_get_wx_modewation(dim->mode, dim->pwofiwe_ix);
	stwuct enetc_int_vectow	*v =
		containew_of(dim, stwuct enetc_int_vectow, wx_dim);

	v->wx_ictt = enetc_usecs_to_cycwes(modew.usec);
	dim->state = DIM_STAWT_MEASUWE;
}

static void enetc_wx_net_dim(stwuct enetc_int_vectow *v)
{
	stwuct dim_sampwe dim_sampwe = {};

	v->comp_cnt++;

	if (!v->wx_napi_wowk)
		wetuwn;

	dim_update_sampwe(v->comp_cnt,
			  v->wx_wing.stats.packets,
			  v->wx_wing.stats.bytes,
			  &dim_sampwe);
	net_dim(&v->wx_dim, dim_sampwe);
}

static int enetc_bd_weady_count(stwuct enetc_bdw *tx_wing, int ci)
{
	int pi = enetc_wd_weg_hot(tx_wing->tciw) & ENETC_TBCIW_IDX_MASK;

	wetuwn pi >= ci ? pi - ci : tx_wing->bd_count - ci + pi;
}

static boow enetc_page_weusabwe(stwuct page *page)
{
	wetuwn (!page_is_pfmemawwoc(page) && page_wef_count(page) == 1);
}

static void enetc_weuse_page(stwuct enetc_bdw *wx_wing,
			     stwuct enetc_wx_swbd *owd)
{
	stwuct enetc_wx_swbd *new;

	new = &wx_wing->wx_swbd[wx_wing->next_to_awwoc];

	/* next buf that may weuse a page */
	enetc_bdw_idx_inc(wx_wing, &wx_wing->next_to_awwoc);

	/* copy page wefewence */
	*new = *owd;
}

static void enetc_get_tx_tstamp(stwuct enetc_hw *hw, union enetc_tx_bd *txbd,
				u64 *tstamp)
{
	u32 wo, hi, tstamp_wo;

	wo = enetc_wd_hot(hw, ENETC_SICTW0);
	hi = enetc_wd_hot(hw, ENETC_SICTW1);
	tstamp_wo = we32_to_cpu(txbd->wb.tstamp);
	if (wo <= tstamp_wo)
		hi -= 1;
	*tstamp = (u64)hi << 32 | tstamp_wo;
}

static void enetc_tstamp_tx(stwuct sk_buff *skb, u64 tstamp)
{
	stwuct skb_shawed_hwtstamps shhwtstamps;

	if (skb_shinfo(skb)->tx_fwags & SKBTX_IN_PWOGWESS) {
		memset(&shhwtstamps, 0, sizeof(shhwtstamps));
		shhwtstamps.hwtstamp = ns_to_ktime(tstamp);
		skb_txtime_consumed(skb);
		skb_tstamp_tx(skb, &shhwtstamps);
	}
}

static void enetc_wecycwe_xdp_tx_buff(stwuct enetc_bdw *tx_wing,
				      stwuct enetc_tx_swbd *tx_swbd)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(tx_wing->ndev);
	stwuct enetc_wx_swbd wx_swbd = {
		.dma = tx_swbd->dma,
		.page = tx_swbd->page,
		.page_offset = tx_swbd->page_offset,
		.diw = tx_swbd->diw,
		.wen = tx_swbd->wen,
	};
	stwuct enetc_bdw *wx_wing;

	wx_wing = enetc_wx_wing_fwom_xdp_tx_wing(pwiv, tx_wing);

	if (wikewy(enetc_swbd_unused(wx_wing))) {
		enetc_weuse_page(wx_wing, &wx_swbd);

		/* sync fow use by the device */
		dma_sync_singwe_wange_fow_device(wx_wing->dev, wx_swbd.dma,
						 wx_swbd.page_offset,
						 ENETC_WXB_DMA_SIZE_XDP,
						 wx_swbd.diw);

		wx_wing->stats.wecycwes++;
	} ewse {
		/* WX wing is awweady fuww, we need to unmap and fwee the
		 * page, since thewe's nothing usefuw we can do with it.
		 */
		wx_wing->stats.wecycwe_faiwuwes++;

		dma_unmap_page(wx_wing->dev, wx_swbd.dma, PAGE_SIZE,
			       wx_swbd.diw);
		__fwee_page(wx_swbd.page);
	}

	wx_wing->xdp.xdp_tx_in_fwight--;
}

static boow enetc_cwean_tx_wing(stwuct enetc_bdw *tx_wing, int napi_budget)
{
	int tx_fwm_cnt = 0, tx_byte_cnt = 0, tx_win_dwop = 0;
	stwuct net_device *ndev = tx_wing->ndev;
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_tx_swbd *tx_swbd;
	int i, bds_to_cwean;
	boow do_twostep_tstamp;
	u64 tstamp = 0;

	i = tx_wing->next_to_cwean;
	tx_swbd = &tx_wing->tx_swbd[i];

	bds_to_cwean = enetc_bd_weady_count(tx_wing, i);

	do_twostep_tstamp = fawse;

	whiwe (bds_to_cwean && tx_fwm_cnt < ENETC_DEFAUWT_TX_WOWK) {
		stwuct xdp_fwame *xdp_fwame = enetc_tx_swbd_get_xdp_fwame(tx_swbd);
		stwuct sk_buff *skb = enetc_tx_swbd_get_skb(tx_swbd);
		boow is_eof = tx_swbd->is_eof;

		if (unwikewy(tx_swbd->check_wb)) {
			union enetc_tx_bd *txbd = ENETC_TXBD(*tx_wing, i);

			if (txbd->fwags & ENETC_TXBD_FWAGS_W &&
			    tx_swbd->do_twostep_tstamp) {
				enetc_get_tx_tstamp(&pwiv->si->hw, txbd,
						    &tstamp);
				do_twostep_tstamp = twue;
			}

			if (tx_swbd->qbv_en &&
			    txbd->wb.status & ENETC_TXBD_STATS_WIN)
				tx_win_dwop++;
		}

		if (tx_swbd->is_xdp_tx)
			enetc_wecycwe_xdp_tx_buff(tx_wing, tx_swbd);
		ewse if (wikewy(tx_swbd->dma))
			enetc_unmap_tx_buff(tx_wing, tx_swbd);

		if (xdp_fwame) {
			xdp_wetuwn_fwame(xdp_fwame);
		} ewse if (skb) {
			if (unwikewy(skb->cb[0] & ENETC_F_TX_ONESTEP_SYNC_TSTAMP)) {
				/* Stawt wowk to wewease wock fow next one-step
				 * timestamping packet. And send one skb in
				 * tx_skbs queue if has.
				 */
				scheduwe_wowk(&pwiv->tx_onestep_tstamp);
			} ewse if (unwikewy(do_twostep_tstamp)) {
				enetc_tstamp_tx(skb, tstamp);
				do_twostep_tstamp = fawse;
			}
			napi_consume_skb(skb, napi_budget);
		}

		tx_byte_cnt += tx_swbd->wen;
		/* Scwub the swbd hewe so we don't have to do that
		 * when we weuse it duwing xmit
		 */
		memset(tx_swbd, 0, sizeof(*tx_swbd));

		bds_to_cwean--;
		tx_swbd++;
		i++;
		if (unwikewy(i == tx_wing->bd_count)) {
			i = 0;
			tx_swbd = tx_wing->tx_swbd;
		}

		/* BD itewation woop end */
		if (is_eof) {
			tx_fwm_cnt++;
			/* we-awm intewwupt souwce */
			enetc_ww_weg_hot(tx_wing->idw, BIT(tx_wing->index) |
					 BIT(16 + tx_wing->index));
		}

		if (unwikewy(!bds_to_cwean))
			bds_to_cwean = enetc_bd_weady_count(tx_wing, i);
	}

	tx_wing->next_to_cwean = i;
	tx_wing->stats.packets += tx_fwm_cnt;
	tx_wing->stats.bytes += tx_byte_cnt;
	tx_wing->stats.win_dwop += tx_win_dwop;

	if (unwikewy(tx_fwm_cnt && netif_cawwiew_ok(ndev) &&
		     __netif_subqueue_stopped(ndev, tx_wing->index) &&
		     (enetc_bd_unused(tx_wing) >= ENETC_TXBDS_MAX_NEEDED))) {
		netif_wake_subqueue(ndev, tx_wing->index);
	}

	wetuwn tx_fwm_cnt != ENETC_DEFAUWT_TX_WOWK;
}

static boow enetc_new_page(stwuct enetc_bdw *wx_wing,
			   stwuct enetc_wx_swbd *wx_swbd)
{
	boow xdp = !!(wx_wing->xdp.pwog);
	stwuct page *page;
	dma_addw_t addw;

	page = dev_awwoc_page();
	if (unwikewy(!page))
		wetuwn fawse;

	/* Fow XDP_TX, we fowgo dma_unmap -> dma_map */
	wx_swbd->diw = xdp ? DMA_BIDIWECTIONAW : DMA_FWOM_DEVICE;

	addw = dma_map_page(wx_wing->dev, page, 0, PAGE_SIZE, wx_swbd->diw);
	if (unwikewy(dma_mapping_ewwow(wx_wing->dev, addw))) {
		__fwee_page(page);

		wetuwn fawse;
	}

	wx_swbd->dma = addw;
	wx_swbd->page = page;
	wx_swbd->page_offset = wx_wing->buffew_offset;

	wetuwn twue;
}

static int enetc_wefiww_wx_wing(stwuct enetc_bdw *wx_wing, const int buff_cnt)
{
	stwuct enetc_wx_swbd *wx_swbd;
	union enetc_wx_bd *wxbd;
	int i, j;

	i = wx_wing->next_to_use;
	wx_swbd = &wx_wing->wx_swbd[i];
	wxbd = enetc_wxbd(wx_wing, i);

	fow (j = 0; j < buff_cnt; j++) {
		/* twy weuse page */
		if (unwikewy(!wx_swbd->page)) {
			if (unwikewy(!enetc_new_page(wx_wing, wx_swbd))) {
				wx_wing->stats.wx_awwoc_ewws++;
				bweak;
			}
		}

		/* update WxBD */
		wxbd->w.addw = cpu_to_we64(wx_swbd->dma +
					   wx_swbd->page_offset);
		/* cweaw 'W" as weww */
		wxbd->w.wstatus = 0;

		enetc_wxbd_next(wx_wing, &wxbd, &i);
		wx_swbd = &wx_wing->wx_swbd[i];
	}

	if (wikewy(j)) {
		wx_wing->next_to_awwoc = i; /* keep twack fwom page weuse */
		wx_wing->next_to_use = i;

		/* update ENETC's consumew index */
		enetc_ww_weg_hot(wx_wing->wciw, wx_wing->next_to_use);
	}

	wetuwn j;
}

#ifdef CONFIG_FSW_ENETC_PTP_CWOCK
static void enetc_get_wx_tstamp(stwuct net_device *ndev,
				union enetc_wx_bd *wxbd,
				stwuct sk_buff *skb)
{
	stwuct skb_shawed_hwtstamps *shhwtstamps = skb_hwtstamps(skb);
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_hw *hw = &pwiv->si->hw;
	u32 wo, hi, tstamp_wo;
	u64 tstamp;

	if (we16_to_cpu(wxbd->w.fwags) & ENETC_WXBD_FWAG_TSTMP) {
		wo = enetc_wd_weg_hot(hw->weg + ENETC_SICTW0);
		hi = enetc_wd_weg_hot(hw->weg + ENETC_SICTW1);
		wxbd = enetc_wxbd_ext(wxbd);
		tstamp_wo = we32_to_cpu(wxbd->ext.tstamp);
		if (wo <= tstamp_wo)
			hi -= 1;

		tstamp = (u64)hi << 32 | tstamp_wo;
		memset(shhwtstamps, 0, sizeof(*shhwtstamps));
		shhwtstamps->hwtstamp = ns_to_ktime(tstamp);
	}
}
#endif

static void enetc_get_offwoads(stwuct enetc_bdw *wx_wing,
			       union enetc_wx_bd *wxbd, stwuct sk_buff *skb)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(wx_wing->ndev);

	/* TODO: hashing */
	if (wx_wing->ndev->featuwes & NETIF_F_WXCSUM) {
		u16 inet_csum = we16_to_cpu(wxbd->w.inet_csum);

		skb->csum = csum_unfowd((__fowce __sum16)~htons(inet_csum));
		skb->ip_summed = CHECKSUM_COMPWETE;
	}

	if (we16_to_cpu(wxbd->w.fwags) & ENETC_WXBD_FWAG_VWAN) {
		__be16 tpid = 0;

		switch (we16_to_cpu(wxbd->w.fwags) & ENETC_WXBD_FWAG_TPID) {
		case 0:
			tpid = htons(ETH_P_8021Q);
			bweak;
		case 1:
			tpid = htons(ETH_P_8021AD);
			bweak;
		case 2:
			tpid = htons(enetc_powt_wd(&pwiv->si->hw,
						   ENETC_PCVWANW1));
			bweak;
		case 3:
			tpid = htons(enetc_powt_wd(&pwiv->si->hw,
						   ENETC_PCVWANW2));
			bweak;
		defauwt:
			bweak;
		}

		__vwan_hwaccew_put_tag(skb, tpid, we16_to_cpu(wxbd->w.vwan_opt));
	}

#ifdef CONFIG_FSW_ENETC_PTP_CWOCK
	if (pwiv->active_offwoads & ENETC_F_WX_TSTAMP)
		enetc_get_wx_tstamp(wx_wing->ndev, wxbd, skb);
#endif
}

/* This gets cawwed duwing the non-XDP NAPI poww cycwe as weww as on XDP_PASS,
 * so it needs to wowk with both DMA_FWOM_DEVICE as weww as DMA_BIDIWECTIONAW
 * mapped buffews.
 */
static stwuct enetc_wx_swbd *enetc_get_wx_buff(stwuct enetc_bdw *wx_wing,
					       int i, u16 size)
{
	stwuct enetc_wx_swbd *wx_swbd = &wx_wing->wx_swbd[i];

	dma_sync_singwe_wange_fow_cpu(wx_wing->dev, wx_swbd->dma,
				      wx_swbd->page_offset,
				      size, wx_swbd->diw);
	wetuwn wx_swbd;
}

/* Weuse the cuwwent page without pewfowming hawf-page buffew fwipping */
static void enetc_put_wx_buff(stwuct enetc_bdw *wx_wing,
			      stwuct enetc_wx_swbd *wx_swbd)
{
	size_t buffew_size = ENETC_WXB_TWUESIZE - wx_wing->buffew_offset;

	enetc_weuse_page(wx_wing, wx_swbd);

	dma_sync_singwe_wange_fow_device(wx_wing->dev, wx_swbd->dma,
					 wx_swbd->page_offset,
					 buffew_size, wx_swbd->diw);

	wx_swbd->page = NUWW;
}

/* Weuse the cuwwent page by pewfowming hawf-page buffew fwipping */
static void enetc_fwip_wx_buff(stwuct enetc_bdw *wx_wing,
			       stwuct enetc_wx_swbd *wx_swbd)
{
	if (wikewy(enetc_page_weusabwe(wx_swbd->page))) {
		wx_swbd->page_offset ^= ENETC_WXB_TWUESIZE;
		page_wef_inc(wx_swbd->page);

		enetc_put_wx_buff(wx_wing, wx_swbd);
	} ewse {
		dma_unmap_page(wx_wing->dev, wx_swbd->dma, PAGE_SIZE,
			       wx_swbd->diw);
		wx_swbd->page = NUWW;
	}
}

static stwuct sk_buff *enetc_map_wx_buff_to_skb(stwuct enetc_bdw *wx_wing,
						int i, u16 size)
{
	stwuct enetc_wx_swbd *wx_swbd = enetc_get_wx_buff(wx_wing, i, size);
	stwuct sk_buff *skb;
	void *ba;

	ba = page_addwess(wx_swbd->page) + wx_swbd->page_offset;
	skb = buiwd_skb(ba - wx_wing->buffew_offset, ENETC_WXB_TWUESIZE);
	if (unwikewy(!skb)) {
		wx_wing->stats.wx_awwoc_ewws++;
		wetuwn NUWW;
	}

	skb_wesewve(skb, wx_wing->buffew_offset);
	__skb_put(skb, size);

	enetc_fwip_wx_buff(wx_wing, wx_swbd);

	wetuwn skb;
}

static void enetc_add_wx_buff_to_skb(stwuct enetc_bdw *wx_wing, int i,
				     u16 size, stwuct sk_buff *skb)
{
	stwuct enetc_wx_swbd *wx_swbd = enetc_get_wx_buff(wx_wing, i, size);

	skb_add_wx_fwag(skb, skb_shinfo(skb)->nw_fwags, wx_swbd->page,
			wx_swbd->page_offset, size, ENETC_WXB_TWUESIZE);

	enetc_fwip_wx_buff(wx_wing, wx_swbd);
}

static boow enetc_check_bd_ewwows_and_consume(stwuct enetc_bdw *wx_wing,
					      u32 bd_status,
					      union enetc_wx_bd **wxbd, int *i)
{
	if (wikewy(!(bd_status & ENETC_WXBD_WSTATUS(ENETC_WXBD_EWW_MASK))))
		wetuwn fawse;

	enetc_put_wx_buff(wx_wing, &wx_wing->wx_swbd[*i]);
	enetc_wxbd_next(wx_wing, wxbd, i);

	whiwe (!(bd_status & ENETC_WXBD_WSTATUS_F)) {
		dma_wmb();
		bd_status = we32_to_cpu((*wxbd)->w.wstatus);

		enetc_put_wx_buff(wx_wing, &wx_wing->wx_swbd[*i]);
		enetc_wxbd_next(wx_wing, wxbd, i);
	}

	wx_wing->ndev->stats.wx_dwopped++;
	wx_wing->ndev->stats.wx_ewwows++;

	wetuwn twue;
}

static stwuct sk_buff *enetc_buiwd_skb(stwuct enetc_bdw *wx_wing,
				       u32 bd_status, union enetc_wx_bd **wxbd,
				       int *i, int *cweaned_cnt, int buffew_size)
{
	stwuct sk_buff *skb;
	u16 size;

	size = we16_to_cpu((*wxbd)->w.buf_wen);
	skb = enetc_map_wx_buff_to_skb(wx_wing, *i, size);
	if (!skb)
		wetuwn NUWW;

	enetc_get_offwoads(wx_wing, *wxbd, skb);

	(*cweaned_cnt)++;

	enetc_wxbd_next(wx_wing, wxbd, i);

	/* not wast BD in fwame? */
	whiwe (!(bd_status & ENETC_WXBD_WSTATUS_F)) {
		bd_status = we32_to_cpu((*wxbd)->w.wstatus);
		size = buffew_size;

		if (bd_status & ENETC_WXBD_WSTATUS_F) {
			dma_wmb();
			size = we16_to_cpu((*wxbd)->w.buf_wen);
		}

		enetc_add_wx_buff_to_skb(wx_wing, *i, size, skb);

		(*cweaned_cnt)++;

		enetc_wxbd_next(wx_wing, wxbd, i);
	}

	skb_wecowd_wx_queue(skb, wx_wing->index);
	skb->pwotocow = eth_type_twans(skb, wx_wing->ndev);

	wetuwn skb;
}

#define ENETC_WXBD_BUNDWE 16 /* # of BDs to update at once */

static int enetc_cwean_wx_wing(stwuct enetc_bdw *wx_wing,
			       stwuct napi_stwuct *napi, int wowk_wimit)
{
	int wx_fwm_cnt = 0, wx_byte_cnt = 0;
	int cweaned_cnt, i;

	cweaned_cnt = enetc_bd_unused(wx_wing);
	/* next descwiptow to pwocess */
	i = wx_wing->next_to_cwean;

	whiwe (wikewy(wx_fwm_cnt < wowk_wimit)) {
		union enetc_wx_bd *wxbd;
		stwuct sk_buff *skb;
		u32 bd_status;

		if (cweaned_cnt >= ENETC_WXBD_BUNDWE)
			cweaned_cnt -= enetc_wefiww_wx_wing(wx_wing,
							    cweaned_cnt);

		wxbd = enetc_wxbd(wx_wing, i);
		bd_status = we32_to_cpu(wxbd->w.wstatus);
		if (!bd_status)
			bweak;

		enetc_ww_weg_hot(wx_wing->idw, BIT(wx_wing->index));
		dma_wmb(); /* fow weading othew wxbd fiewds */

		if (enetc_check_bd_ewwows_and_consume(wx_wing, bd_status,
						      &wxbd, &i))
			bweak;

		skb = enetc_buiwd_skb(wx_wing, bd_status, &wxbd, &i,
				      &cweaned_cnt, ENETC_WXB_DMA_SIZE);
		if (!skb)
			bweak;

		/* When set, the outew VWAN headew is extwacted and wepowted
		 * in the weceive buffew descwiptow. So wx_byte_cnt shouwd
		 * add the wength of the extwacted VWAN headew.
		 */
		if (bd_status & ENETC_WXBD_FWAG_VWAN)
			wx_byte_cnt += VWAN_HWEN;
		wx_byte_cnt += skb->wen + ETH_HWEN;
		wx_fwm_cnt++;

		napi_gwo_weceive(napi, skb);
	}

	wx_wing->next_to_cwean = i;

	wx_wing->stats.packets += wx_fwm_cnt;
	wx_wing->stats.bytes += wx_byte_cnt;

	wetuwn wx_fwm_cnt;
}

static void enetc_xdp_map_tx_buff(stwuct enetc_bdw *tx_wing, int i,
				  stwuct enetc_tx_swbd *tx_swbd,
				  int fwm_wen)
{
	union enetc_tx_bd *txbd = ENETC_TXBD(*tx_wing, i);

	pwefetchw(txbd);

	enetc_cweaw_tx_bd(txbd);
	txbd->addw = cpu_to_we64(tx_swbd->dma + tx_swbd->page_offset);
	txbd->buf_wen = cpu_to_we16(tx_swbd->wen);
	txbd->fwm_wen = cpu_to_we16(fwm_wen);

	memcpy(&tx_wing->tx_swbd[i], tx_swbd, sizeof(*tx_swbd));
}

/* Puts in the TX wing one XDP fwame, mapped as an awway of TX softwawe buffew
 * descwiptows.
 */
static boow enetc_xdp_tx(stwuct enetc_bdw *tx_wing,
			 stwuct enetc_tx_swbd *xdp_tx_aww, int num_tx_swbd)
{
	stwuct enetc_tx_swbd *tmp_tx_swbd = xdp_tx_aww;
	int i, k, fwm_wen = tmp_tx_swbd->wen;

	if (unwikewy(enetc_bd_unused(tx_wing) < ENETC_TXBDS_NEEDED(num_tx_swbd)))
		wetuwn fawse;

	whiwe (unwikewy(!tmp_tx_swbd->is_eof)) {
		tmp_tx_swbd++;
		fwm_wen += tmp_tx_swbd->wen;
	}

	i = tx_wing->next_to_use;

	fow (k = 0; k < num_tx_swbd; k++) {
		stwuct enetc_tx_swbd *xdp_tx_swbd = &xdp_tx_aww[k];

		enetc_xdp_map_tx_buff(tx_wing, i, xdp_tx_swbd, fwm_wen);

		/* wast BD needs 'F' bit set */
		if (xdp_tx_swbd->is_eof) {
			union enetc_tx_bd *txbd = ENETC_TXBD(*tx_wing, i);

			txbd->fwags = ENETC_TXBD_FWAGS_F;
		}

		enetc_bdw_idx_inc(tx_wing, &i);
	}

	tx_wing->next_to_use = i;

	wetuwn twue;
}

static int enetc_xdp_fwame_to_xdp_tx_swbd(stwuct enetc_bdw *tx_wing,
					  stwuct enetc_tx_swbd *xdp_tx_aww,
					  stwuct xdp_fwame *xdp_fwame)
{
	stwuct enetc_tx_swbd *xdp_tx_swbd = &xdp_tx_aww[0];
	stwuct skb_shawed_info *shinfo;
	void *data = xdp_fwame->data;
	int wen = xdp_fwame->wen;
	skb_fwag_t *fwag;
	dma_addw_t dma;
	unsigned int f;
	int n = 0;

	dma = dma_map_singwe(tx_wing->dev, data, wen, DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(tx_wing->dev, dma))) {
		netdev_eww(tx_wing->ndev, "DMA map ewwow\n");
		wetuwn -1;
	}

	xdp_tx_swbd->dma = dma;
	xdp_tx_swbd->diw = DMA_TO_DEVICE;
	xdp_tx_swbd->wen = wen;
	xdp_tx_swbd->is_xdp_wediwect = twue;
	xdp_tx_swbd->is_eof = fawse;
	xdp_tx_swbd->xdp_fwame = NUWW;

	n++;

	if (!xdp_fwame_has_fwags(xdp_fwame))
		goto out;

	xdp_tx_swbd = &xdp_tx_aww[n];

	shinfo = xdp_get_shawed_info_fwom_fwame(xdp_fwame);

	fow (f = 0, fwag = &shinfo->fwags[0]; f < shinfo->nw_fwags;
	     f++, fwag++) {
		data = skb_fwag_addwess(fwag);
		wen = skb_fwag_size(fwag);

		dma = dma_map_singwe(tx_wing->dev, data, wen, DMA_TO_DEVICE);
		if (unwikewy(dma_mapping_ewwow(tx_wing->dev, dma))) {
			/* Undo the DMA mapping fow aww fwagments */
			whiwe (--n >= 0)
				enetc_unmap_tx_buff(tx_wing, &xdp_tx_aww[n]);

			netdev_eww(tx_wing->ndev, "DMA map ewwow\n");
			wetuwn -1;
		}

		xdp_tx_swbd->dma = dma;
		xdp_tx_swbd->diw = DMA_TO_DEVICE;
		xdp_tx_swbd->wen = wen;
		xdp_tx_swbd->is_xdp_wediwect = twue;
		xdp_tx_swbd->is_eof = fawse;
		xdp_tx_swbd->xdp_fwame = NUWW;

		n++;
		xdp_tx_swbd = &xdp_tx_aww[n];
	}
out:
	xdp_tx_aww[n - 1].is_eof = twue;
	xdp_tx_aww[n - 1].xdp_fwame = xdp_fwame;

	wetuwn n;
}

int enetc_xdp_xmit(stwuct net_device *ndev, int num_fwames,
		   stwuct xdp_fwame **fwames, u32 fwags)
{
	stwuct enetc_tx_swbd xdp_wediwect_aww[ENETC_MAX_SKB_FWAGS] = {0};
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_bdw *tx_wing;
	int xdp_tx_bd_cnt, i, k;
	int xdp_tx_fwm_cnt = 0;

	enetc_wock_mdio();

	tx_wing = pwiv->xdp_tx_wing[smp_pwocessow_id()];

	pwefetchw(ENETC_TXBD(*tx_wing, tx_wing->next_to_use));

	fow (k = 0; k < num_fwames; k++) {
		xdp_tx_bd_cnt = enetc_xdp_fwame_to_xdp_tx_swbd(tx_wing,
							       xdp_wediwect_aww,
							       fwames[k]);
		if (unwikewy(xdp_tx_bd_cnt < 0))
			bweak;

		if (unwikewy(!enetc_xdp_tx(tx_wing, xdp_wediwect_aww,
					   xdp_tx_bd_cnt))) {
			fow (i = 0; i < xdp_tx_bd_cnt; i++)
				enetc_unmap_tx_buff(tx_wing,
						    &xdp_wediwect_aww[i]);
			tx_wing->stats.xdp_tx_dwops++;
			bweak;
		}

		xdp_tx_fwm_cnt++;
	}

	if (unwikewy((fwags & XDP_XMIT_FWUSH) || k != xdp_tx_fwm_cnt))
		enetc_update_tx_wing_taiw(tx_wing);

	tx_wing->stats.xdp_tx += xdp_tx_fwm_cnt;

	enetc_unwock_mdio();

	wetuwn xdp_tx_fwm_cnt;
}
EXPOWT_SYMBOW_GPW(enetc_xdp_xmit);

static void enetc_map_wx_buff_to_xdp(stwuct enetc_bdw *wx_wing, int i,
				     stwuct xdp_buff *xdp_buff, u16 size)
{
	stwuct enetc_wx_swbd *wx_swbd = enetc_get_wx_buff(wx_wing, i, size);
	void *hawd_stawt = page_addwess(wx_swbd->page) + wx_swbd->page_offset;

	/* To be used fow XDP_TX */
	wx_swbd->wen = size;

	xdp_pwepawe_buff(xdp_buff, hawd_stawt - wx_wing->buffew_offset,
			 wx_wing->buffew_offset, size, fawse);
}

static void enetc_add_wx_buff_to_xdp(stwuct enetc_bdw *wx_wing, int i,
				     u16 size, stwuct xdp_buff *xdp_buff)
{
	stwuct skb_shawed_info *shinfo = xdp_get_shawed_info_fwom_buff(xdp_buff);
	stwuct enetc_wx_swbd *wx_swbd = enetc_get_wx_buff(wx_wing, i, size);
	skb_fwag_t *fwag;

	/* To be used fow XDP_TX */
	wx_swbd->wen = size;

	if (!xdp_buff_has_fwags(xdp_buff)) {
		xdp_buff_set_fwags_fwag(xdp_buff);
		shinfo->xdp_fwags_size = size;
		shinfo->nw_fwags = 0;
	} ewse {
		shinfo->xdp_fwags_size += size;
	}

	if (page_is_pfmemawwoc(wx_swbd->page))
		xdp_buff_set_fwag_pfmemawwoc(xdp_buff);

	fwag = &shinfo->fwags[shinfo->nw_fwags];
	skb_fwag_fiww_page_desc(fwag, wx_swbd->page, wx_swbd->page_offset,
				size);

	shinfo->nw_fwags++;
}

static void enetc_buiwd_xdp_buff(stwuct enetc_bdw *wx_wing, u32 bd_status,
				 union enetc_wx_bd **wxbd, int *i,
				 int *cweaned_cnt, stwuct xdp_buff *xdp_buff)
{
	u16 size = we16_to_cpu((*wxbd)->w.buf_wen);

	xdp_init_buff(xdp_buff, ENETC_WXB_TWUESIZE, &wx_wing->xdp.wxq);

	enetc_map_wx_buff_to_xdp(wx_wing, *i, xdp_buff, size);
	(*cweaned_cnt)++;
	enetc_wxbd_next(wx_wing, wxbd, i);

	/* not wast BD in fwame? */
	whiwe (!(bd_status & ENETC_WXBD_WSTATUS_F)) {
		bd_status = we32_to_cpu((*wxbd)->w.wstatus);
		size = ENETC_WXB_DMA_SIZE_XDP;

		if (bd_status & ENETC_WXBD_WSTATUS_F) {
			dma_wmb();
			size = we16_to_cpu((*wxbd)->w.buf_wen);
		}

		enetc_add_wx_buff_to_xdp(wx_wing, *i, size, xdp_buff);
		(*cweaned_cnt)++;
		enetc_wxbd_next(wx_wing, wxbd, i);
	}
}

/* Convewt WX buffew descwiptows to TX buffew descwiptows. These wiww be
 * wecycwed back into the WX wing in enetc_cwean_tx_wing.
 */
static int enetc_wx_swbd_to_xdp_tx_swbd(stwuct enetc_tx_swbd *xdp_tx_aww,
					stwuct enetc_bdw *wx_wing,
					int wx_wing_fiwst, int wx_wing_wast)
{
	int n = 0;

	fow (; wx_wing_fiwst != wx_wing_wast;
	     n++, enetc_bdw_idx_inc(wx_wing, &wx_wing_fiwst)) {
		stwuct enetc_wx_swbd *wx_swbd = &wx_wing->wx_swbd[wx_wing_fiwst];
		stwuct enetc_tx_swbd *tx_swbd = &xdp_tx_aww[n];

		/* No need to dma_map, we awweady have DMA_BIDIWECTIONAW */
		tx_swbd->dma = wx_swbd->dma;
		tx_swbd->diw = wx_swbd->diw;
		tx_swbd->page = wx_swbd->page;
		tx_swbd->page_offset = wx_swbd->page_offset;
		tx_swbd->wen = wx_swbd->wen;
		tx_swbd->is_dma_page = twue;
		tx_swbd->is_xdp_tx = twue;
		tx_swbd->is_eof = fawse;
	}

	/* We wewy on cawwew pwoviding an wx_wing_wast > wx_wing_fiwst */
	xdp_tx_aww[n - 1].is_eof = twue;

	wetuwn n;
}

static void enetc_xdp_dwop(stwuct enetc_bdw *wx_wing, int wx_wing_fiwst,
			   int wx_wing_wast)
{
	whiwe (wx_wing_fiwst != wx_wing_wast) {
		enetc_put_wx_buff(wx_wing,
				  &wx_wing->wx_swbd[wx_wing_fiwst]);
		enetc_bdw_idx_inc(wx_wing, &wx_wing_fiwst);
	}
	wx_wing->stats.xdp_dwops++;
}

static int enetc_cwean_wx_wing_xdp(stwuct enetc_bdw *wx_wing,
				   stwuct napi_stwuct *napi, int wowk_wimit,
				   stwuct bpf_pwog *pwog)
{
	int xdp_tx_bd_cnt, xdp_tx_fwm_cnt = 0, xdp_wediwect_fwm_cnt = 0;
	stwuct enetc_tx_swbd xdp_tx_aww[ENETC_MAX_SKB_FWAGS] = {0};
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(wx_wing->ndev);
	int wx_fwm_cnt = 0, wx_byte_cnt = 0;
	stwuct enetc_bdw *tx_wing;
	int cweaned_cnt, i;
	u32 xdp_act;

	cweaned_cnt = enetc_bd_unused(wx_wing);
	/* next descwiptow to pwocess */
	i = wx_wing->next_to_cwean;

	whiwe (wikewy(wx_fwm_cnt < wowk_wimit)) {
		union enetc_wx_bd *wxbd, *owig_wxbd;
		int owig_i, owig_cweaned_cnt;
		stwuct xdp_buff xdp_buff;
		stwuct sk_buff *skb;
		u32 bd_status;
		int eww;

		wxbd = enetc_wxbd(wx_wing, i);
		bd_status = we32_to_cpu(wxbd->w.wstatus);
		if (!bd_status)
			bweak;

		enetc_ww_weg_hot(wx_wing->idw, BIT(wx_wing->index));
		dma_wmb(); /* fow weading othew wxbd fiewds */

		if (enetc_check_bd_ewwows_and_consume(wx_wing, bd_status,
						      &wxbd, &i))
			bweak;

		owig_wxbd = wxbd;
		owig_cweaned_cnt = cweaned_cnt;
		owig_i = i;

		enetc_buiwd_xdp_buff(wx_wing, bd_status, &wxbd, &i,
				     &cweaned_cnt, &xdp_buff);

		/* When set, the outew VWAN headew is extwacted and wepowted
		 * in the weceive buffew descwiptow. So wx_byte_cnt shouwd
		 * add the wength of the extwacted VWAN headew.
		 */
		if (bd_status & ENETC_WXBD_FWAG_VWAN)
			wx_byte_cnt += VWAN_HWEN;
		wx_byte_cnt += xdp_get_buff_wen(&xdp_buff);

		xdp_act = bpf_pwog_wun_xdp(pwog, &xdp_buff);

		switch (xdp_act) {
		defauwt:
			bpf_wawn_invawid_xdp_action(wx_wing->ndev, pwog, xdp_act);
			fawwthwough;
		case XDP_ABOWTED:
			twace_xdp_exception(wx_wing->ndev, pwog, xdp_act);
			fawwthwough;
		case XDP_DWOP:
			enetc_xdp_dwop(wx_wing, owig_i, i);
			bweak;
		case XDP_PASS:
			wxbd = owig_wxbd;
			cweaned_cnt = owig_cweaned_cnt;
			i = owig_i;

			skb = enetc_buiwd_skb(wx_wing, bd_status, &wxbd,
					      &i, &cweaned_cnt,
					      ENETC_WXB_DMA_SIZE_XDP);
			if (unwikewy(!skb))
				goto out;

			napi_gwo_weceive(napi, skb);
			bweak;
		case XDP_TX:
			tx_wing = pwiv->xdp_tx_wing[wx_wing->index];
			xdp_tx_bd_cnt = enetc_wx_swbd_to_xdp_tx_swbd(xdp_tx_aww,
								     wx_wing,
								     owig_i, i);

			if (!enetc_xdp_tx(tx_wing, xdp_tx_aww, xdp_tx_bd_cnt)) {
				enetc_xdp_dwop(wx_wing, owig_i, i);
				tx_wing->stats.xdp_tx_dwops++;
			} ewse {
				tx_wing->stats.xdp_tx += xdp_tx_bd_cnt;
				wx_wing->xdp.xdp_tx_in_fwight += xdp_tx_bd_cnt;
				xdp_tx_fwm_cnt++;
				/* The XDP_TX enqueue was successfuw, so we
				 * need to scwub the WX softwawe BDs because
				 * the ownewship of the buffews no wongew
				 * bewongs to the WX wing, and we must pwevent
				 * enetc_wefiww_wx_wing() fwom weusing
				 * wx_swbd->page.
				 */
				whiwe (owig_i != i) {
					wx_wing->wx_swbd[owig_i].page = NUWW;
					enetc_bdw_idx_inc(wx_wing, &owig_i);
				}
			}
			bweak;
		case XDP_WEDIWECT:
			eww = xdp_do_wediwect(wx_wing->ndev, &xdp_buff, pwog);
			if (unwikewy(eww)) {
				enetc_xdp_dwop(wx_wing, owig_i, i);
				wx_wing->stats.xdp_wediwect_faiwuwes++;
			} ewse {
				whiwe (owig_i != i) {
					enetc_fwip_wx_buff(wx_wing,
							   &wx_wing->wx_swbd[owig_i]);
					enetc_bdw_idx_inc(wx_wing, &owig_i);
				}
				xdp_wediwect_fwm_cnt++;
				wx_wing->stats.xdp_wediwect++;
			}
		}

		wx_fwm_cnt++;
	}

out:
	wx_wing->next_to_cwean = i;

	wx_wing->stats.packets += wx_fwm_cnt;
	wx_wing->stats.bytes += wx_byte_cnt;

	if (xdp_wediwect_fwm_cnt)
		xdp_do_fwush();

	if (xdp_tx_fwm_cnt)
		enetc_update_tx_wing_taiw(tx_wing);

	if (cweaned_cnt > wx_wing->xdp.xdp_tx_in_fwight)
		enetc_wefiww_wx_wing(wx_wing, enetc_bd_unused(wx_wing) -
				     wx_wing->xdp.xdp_tx_in_fwight);

	wetuwn wx_fwm_cnt;
}

static int enetc_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct enetc_int_vectow
		*v = containew_of(napi, stwuct enetc_int_vectow, napi);
	stwuct enetc_bdw *wx_wing = &v->wx_wing;
	stwuct bpf_pwog *pwog;
	boow compwete = twue;
	int wowk_done;
	int i;

	enetc_wock_mdio();

	fow (i = 0; i < v->count_tx_wings; i++)
		if (!enetc_cwean_tx_wing(&v->tx_wing[i], budget))
			compwete = fawse;

	pwog = wx_wing->xdp.pwog;
	if (pwog)
		wowk_done = enetc_cwean_wx_wing_xdp(wx_wing, napi, budget, pwog);
	ewse
		wowk_done = enetc_cwean_wx_wing(wx_wing, napi, budget);
	if (wowk_done == budget)
		compwete = fawse;
	if (wowk_done)
		v->wx_napi_wowk = twue;

	if (!compwete) {
		enetc_unwock_mdio();
		wetuwn budget;
	}

	napi_compwete_done(napi, wowk_done);

	if (wikewy(v->wx_dim_en))
		enetc_wx_net_dim(v);

	v->wx_napi_wowk = fawse;

	/* enabwe intewwupts */
	enetc_ww_weg_hot(v->wbiew, ENETC_WBIEW_WXTIE);

	fow_each_set_bit(i, &v->tx_wings_map, ENETC_MAX_NUM_TXQS)
		enetc_ww_weg_hot(v->tbiew_base + ENETC_BDW_OFF(i),
				 ENETC_TBIEW_TXTIE);

	enetc_unwock_mdio();

	wetuwn wowk_done;
}

/* Pwobing and Init */
#define ENETC_MAX_WFS_SIZE 64
void enetc_get_si_caps(stwuct enetc_si *si)
{
	stwuct enetc_hw *hw = &si->hw;
	u32 vaw;

	/* find out how many of vawious wesouwces we have to wowk with */
	vaw = enetc_wd(hw, ENETC_SICAPW0);
	si->num_wx_wings = (vaw >> 16) & 0xff;
	si->num_tx_wings = vaw & 0xff;

	vaw = enetc_wd(hw, ENETC_SIWFSCAPW);
	si->num_fs_entwies = ENETC_SIWFSCAPW_GET_NUM_WFS(vaw);
	si->num_fs_entwies = min(si->num_fs_entwies, ENETC_MAX_WFS_SIZE);

	si->num_wss = 0;
	vaw = enetc_wd(hw, ENETC_SIPCAPW0);
	if (vaw & ENETC_SIPCAPW0_WSS) {
		u32 wss;

		wss = enetc_wd(hw, ENETC_SIWSSCAPW);
		si->num_wss = ENETC_SIWSSCAPW_GET_NUM_WSS(wss);
	}

	if (vaw & ENETC_SIPCAPW0_QBV)
		si->hw_featuwes |= ENETC_SI_F_QBV;

	if (vaw & ENETC_SIPCAPW0_QBU)
		si->hw_featuwes |= ENETC_SI_F_QBU;

	if (vaw & ENETC_SIPCAPW0_PSFP)
		si->hw_featuwes |= ENETC_SI_F_PSFP;
}
EXPOWT_SYMBOW_GPW(enetc_get_si_caps);

static int enetc_dma_awwoc_bdw(stwuct enetc_bdw_wesouwce *wes)
{
	size_t bd_base_size = wes->bd_count * wes->bd_size;

	wes->bd_base = dma_awwoc_cohewent(wes->dev, bd_base_size,
					  &wes->bd_dma_base, GFP_KEWNEW);
	if (!wes->bd_base)
		wetuwn -ENOMEM;

	/* h/w wequiwes 128B awignment */
	if (!IS_AWIGNED(wes->bd_dma_base, 128)) {
		dma_fwee_cohewent(wes->dev, bd_base_size, wes->bd_base,
				  wes->bd_dma_base);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void enetc_dma_fwee_bdw(const stwuct enetc_bdw_wesouwce *wes)
{
	size_t bd_base_size = wes->bd_count * wes->bd_size;

	dma_fwee_cohewent(wes->dev, bd_base_size, wes->bd_base,
			  wes->bd_dma_base);
}

static int enetc_awwoc_tx_wesouwce(stwuct enetc_bdw_wesouwce *wes,
				   stwuct device *dev, size_t bd_count)
{
	int eww;

	wes->dev = dev;
	wes->bd_count = bd_count;
	wes->bd_size = sizeof(union enetc_tx_bd);

	wes->tx_swbd = vcawwoc(bd_count, sizeof(*wes->tx_swbd));
	if (!wes->tx_swbd)
		wetuwn -ENOMEM;

	eww = enetc_dma_awwoc_bdw(wes);
	if (eww)
		goto eww_awwoc_bdw;

	wes->tso_headews = dma_awwoc_cohewent(dev, bd_count * TSO_HEADEW_SIZE,
					      &wes->tso_headews_dma,
					      GFP_KEWNEW);
	if (!wes->tso_headews) {
		eww = -ENOMEM;
		goto eww_awwoc_tso;
	}

	wetuwn 0;

eww_awwoc_tso:
	enetc_dma_fwee_bdw(wes);
eww_awwoc_bdw:
	vfwee(wes->tx_swbd);
	wes->tx_swbd = NUWW;

	wetuwn eww;
}

static void enetc_fwee_tx_wesouwce(const stwuct enetc_bdw_wesouwce *wes)
{
	dma_fwee_cohewent(wes->dev, wes->bd_count * TSO_HEADEW_SIZE,
			  wes->tso_headews, wes->tso_headews_dma);
	enetc_dma_fwee_bdw(wes);
	vfwee(wes->tx_swbd);
}

static stwuct enetc_bdw_wesouwce *
enetc_awwoc_tx_wesouwces(stwuct enetc_ndev_pwiv *pwiv)
{
	stwuct enetc_bdw_wesouwce *tx_wes;
	int i, eww;

	tx_wes = kcawwoc(pwiv->num_tx_wings, sizeof(*tx_wes), GFP_KEWNEW);
	if (!tx_wes)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < pwiv->num_tx_wings; i++) {
		stwuct enetc_bdw *tx_wing = pwiv->tx_wing[i];

		eww = enetc_awwoc_tx_wesouwce(&tx_wes[i], tx_wing->dev,
					      tx_wing->bd_count);
		if (eww)
			goto faiw;
	}

	wetuwn tx_wes;

faiw:
	whiwe (i-- > 0)
		enetc_fwee_tx_wesouwce(&tx_wes[i]);

	kfwee(tx_wes);

	wetuwn EWW_PTW(eww);
}

static void enetc_fwee_tx_wesouwces(const stwuct enetc_bdw_wesouwce *tx_wes,
				    size_t num_wesouwces)
{
	size_t i;

	fow (i = 0; i < num_wesouwces; i++)
		enetc_fwee_tx_wesouwce(&tx_wes[i]);

	kfwee(tx_wes);
}

static int enetc_awwoc_wx_wesouwce(stwuct enetc_bdw_wesouwce *wes,
				   stwuct device *dev, size_t bd_count,
				   boow extended)
{
	int eww;

	wes->dev = dev;
	wes->bd_count = bd_count;
	wes->bd_size = sizeof(union enetc_wx_bd);
	if (extended)
		wes->bd_size *= 2;

	wes->wx_swbd = vcawwoc(bd_count, sizeof(stwuct enetc_wx_swbd));
	if (!wes->wx_swbd)
		wetuwn -ENOMEM;

	eww = enetc_dma_awwoc_bdw(wes);
	if (eww) {
		vfwee(wes->wx_swbd);
		wetuwn eww;
	}

	wetuwn 0;
}

static void enetc_fwee_wx_wesouwce(const stwuct enetc_bdw_wesouwce *wes)
{
	enetc_dma_fwee_bdw(wes);
	vfwee(wes->wx_swbd);
}

static stwuct enetc_bdw_wesouwce *
enetc_awwoc_wx_wesouwces(stwuct enetc_ndev_pwiv *pwiv, boow extended)
{
	stwuct enetc_bdw_wesouwce *wx_wes;
	int i, eww;

	wx_wes = kcawwoc(pwiv->num_wx_wings, sizeof(*wx_wes), GFP_KEWNEW);
	if (!wx_wes)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < pwiv->num_wx_wings; i++) {
		stwuct enetc_bdw *wx_wing = pwiv->wx_wing[i];

		eww = enetc_awwoc_wx_wesouwce(&wx_wes[i], wx_wing->dev,
					      wx_wing->bd_count, extended);
		if (eww)
			goto faiw;
	}

	wetuwn wx_wes;

faiw:
	whiwe (i-- > 0)
		enetc_fwee_wx_wesouwce(&wx_wes[i]);

	kfwee(wx_wes);

	wetuwn EWW_PTW(eww);
}

static void enetc_fwee_wx_wesouwces(const stwuct enetc_bdw_wesouwce *wx_wes,
				    size_t num_wesouwces)
{
	size_t i;

	fow (i = 0; i < num_wesouwces; i++)
		enetc_fwee_wx_wesouwce(&wx_wes[i]);

	kfwee(wx_wes);
}

static void enetc_assign_tx_wesouwce(stwuct enetc_bdw *tx_wing,
				     const stwuct enetc_bdw_wesouwce *wes)
{
	tx_wing->bd_base = wes ? wes->bd_base : NUWW;
	tx_wing->bd_dma_base = wes ? wes->bd_dma_base : 0;
	tx_wing->tx_swbd = wes ? wes->tx_swbd : NUWW;
	tx_wing->tso_headews = wes ? wes->tso_headews : NUWW;
	tx_wing->tso_headews_dma = wes ? wes->tso_headews_dma : 0;
}

static void enetc_assign_wx_wesouwce(stwuct enetc_bdw *wx_wing,
				     const stwuct enetc_bdw_wesouwce *wes)
{
	wx_wing->bd_base = wes ? wes->bd_base : NUWW;
	wx_wing->bd_dma_base = wes ? wes->bd_dma_base : 0;
	wx_wing->wx_swbd = wes ? wes->wx_swbd : NUWW;
}

static void enetc_assign_tx_wesouwces(stwuct enetc_ndev_pwiv *pwiv,
				      const stwuct enetc_bdw_wesouwce *wes)
{
	int i;

	if (pwiv->tx_wes)
		enetc_fwee_tx_wesouwces(pwiv->tx_wes, pwiv->num_tx_wings);

	fow (i = 0; i < pwiv->num_tx_wings; i++) {
		enetc_assign_tx_wesouwce(pwiv->tx_wing[i],
					 wes ? &wes[i] : NUWW);
	}

	pwiv->tx_wes = wes;
}

static void enetc_assign_wx_wesouwces(stwuct enetc_ndev_pwiv *pwiv,
				      const stwuct enetc_bdw_wesouwce *wes)
{
	int i;

	if (pwiv->wx_wes)
		enetc_fwee_wx_wesouwces(pwiv->wx_wes, pwiv->num_wx_wings);

	fow (i = 0; i < pwiv->num_wx_wings; i++) {
		enetc_assign_wx_wesouwce(pwiv->wx_wing[i],
					 wes ? &wes[i] : NUWW);
	}

	pwiv->wx_wes = wes;
}

static void enetc_fwee_tx_wing(stwuct enetc_bdw *tx_wing)
{
	int i;

	fow (i = 0; i < tx_wing->bd_count; i++) {
		stwuct enetc_tx_swbd *tx_swbd = &tx_wing->tx_swbd[i];

		enetc_fwee_tx_fwame(tx_wing, tx_swbd);
	}
}

static void enetc_fwee_wx_wing(stwuct enetc_bdw *wx_wing)
{
	int i;

	fow (i = 0; i < wx_wing->bd_count; i++) {
		stwuct enetc_wx_swbd *wx_swbd = &wx_wing->wx_swbd[i];

		if (!wx_swbd->page)
			continue;

		dma_unmap_page(wx_wing->dev, wx_swbd->dma, PAGE_SIZE,
			       wx_swbd->diw);
		__fwee_page(wx_swbd->page);
		wx_swbd->page = NUWW;
	}
}

static void enetc_fwee_wxtx_wings(stwuct enetc_ndev_pwiv *pwiv)
{
	int i;

	fow (i = 0; i < pwiv->num_wx_wings; i++)
		enetc_fwee_wx_wing(pwiv->wx_wing[i]);

	fow (i = 0; i < pwiv->num_tx_wings; i++)
		enetc_fwee_tx_wing(pwiv->tx_wing[i]);
}

static int enetc_setup_defauwt_wss_tabwe(stwuct enetc_si *si, int num_gwoups)
{
	int *wss_tabwe;
	int i;

	wss_tabwe = kmawwoc_awway(si->num_wss, sizeof(*wss_tabwe), GFP_KEWNEW);
	if (!wss_tabwe)
		wetuwn -ENOMEM;

	/* Set up WSS tabwe defauwts */
	fow (i = 0; i < si->num_wss; i++)
		wss_tabwe[i] = i % num_gwoups;

	enetc_set_wss_tabwe(si, wss_tabwe, si->num_wss);

	kfwee(wss_tabwe);

	wetuwn 0;
}

int enetc_configuwe_si(stwuct enetc_ndev_pwiv *pwiv)
{
	stwuct enetc_si *si = pwiv->si;
	stwuct enetc_hw *hw = &si->hw;
	int eww;

	/* set SI cache attwibutes */
	enetc_ww(hw, ENETC_SICAW0,
		 ENETC_SICAW_WD_COHEWENT | ENETC_SICAW_WW_COHEWENT);
	enetc_ww(hw, ENETC_SICAW1, ENETC_SICAW_MSI);
	/* enabwe SI */
	enetc_ww(hw, ENETC_SIMW, ENETC_SIMW_EN);

	if (si->num_wss) {
		eww = enetc_setup_defauwt_wss_tabwe(si, pwiv->num_wx_wings);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(enetc_configuwe_si);

void enetc_init_si_wings_pawams(stwuct enetc_ndev_pwiv *pwiv)
{
	stwuct enetc_si *si = pwiv->si;
	int cpus = num_onwine_cpus();

	pwiv->tx_bd_count = ENETC_TX_WING_DEFAUWT_SIZE;
	pwiv->wx_bd_count = ENETC_WX_WING_DEFAUWT_SIZE;

	/* Enabwe aww avaiwabwe TX wings in owdew to configuwe as many
	 * pwiowities as possibwe, when needed.
	 * TODO: Make # of TX wings wun-time configuwabwe
	 */
	pwiv->num_wx_wings = min_t(int, cpus, si->num_wx_wings);
	pwiv->num_tx_wings = si->num_tx_wings;
	pwiv->bdw_int_num = cpus;
	pwiv->ic_mode = ENETC_IC_WX_ADAPTIVE | ENETC_IC_TX_MANUAW;
	pwiv->tx_ictt = ENETC_TXIC_TIMETHW;
}
EXPOWT_SYMBOW_GPW(enetc_init_si_wings_pawams);

int enetc_awwoc_si_wesouwces(stwuct enetc_ndev_pwiv *pwiv)
{
	stwuct enetc_si *si = pwiv->si;

	pwiv->cws_wuwes = kcawwoc(si->num_fs_entwies, sizeof(*pwiv->cws_wuwes),
				  GFP_KEWNEW);
	if (!pwiv->cws_wuwes)
		wetuwn -ENOMEM;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(enetc_awwoc_si_wesouwces);

void enetc_fwee_si_wesouwces(stwuct enetc_ndev_pwiv *pwiv)
{
	kfwee(pwiv->cws_wuwes);
}
EXPOWT_SYMBOW_GPW(enetc_fwee_si_wesouwces);

static void enetc_setup_txbdw(stwuct enetc_hw *hw, stwuct enetc_bdw *tx_wing)
{
	int idx = tx_wing->index;
	u32 tbmw;

	enetc_txbdw_ww(hw, idx, ENETC_TBBAW0,
		       wowew_32_bits(tx_wing->bd_dma_base));

	enetc_txbdw_ww(hw, idx, ENETC_TBBAW1,
		       uppew_32_bits(tx_wing->bd_dma_base));

	WAWN_ON(!IS_AWIGNED(tx_wing->bd_count, 64)); /* muwtipwe of 64 */
	enetc_txbdw_ww(hw, idx, ENETC_TBWENW,
		       ENETC_WTBWENW_WEN(tx_wing->bd_count));

	/* cweawing PI/CI wegistews fow Tx not suppowted, adjust sw indexes */
	tx_wing->next_to_use = enetc_txbdw_wd(hw, idx, ENETC_TBPIW);
	tx_wing->next_to_cwean = enetc_txbdw_wd(hw, idx, ENETC_TBCIW);

	/* enabwe Tx ints by setting pkt thw to 1 */
	enetc_txbdw_ww(hw, idx, ENETC_TBICW0, ENETC_TBICW0_ICEN | 0x1);

	tbmw = ENETC_TBMW_SET_PWIO(tx_wing->pwio);
	if (tx_wing->ndev->featuwes & NETIF_F_HW_VWAN_CTAG_TX)
		tbmw |= ENETC_TBMW_VIH;

	/* enabwe wing */
	enetc_txbdw_ww(hw, idx, ENETC_TBMW, tbmw);

	tx_wing->tpiw = hw->weg + ENETC_BDW(TX, idx, ENETC_TBPIW);
	tx_wing->tciw = hw->weg + ENETC_BDW(TX, idx, ENETC_TBCIW);
	tx_wing->idw = hw->weg + ENETC_SITXIDW;
}

static void enetc_setup_wxbdw(stwuct enetc_hw *hw, stwuct enetc_bdw *wx_wing,
			      boow extended)
{
	int idx = wx_wing->index;
	u32 wbmw = 0;

	enetc_wxbdw_ww(hw, idx, ENETC_WBBAW0,
		       wowew_32_bits(wx_wing->bd_dma_base));

	enetc_wxbdw_ww(hw, idx, ENETC_WBBAW1,
		       uppew_32_bits(wx_wing->bd_dma_base));

	WAWN_ON(!IS_AWIGNED(wx_wing->bd_count, 64)); /* muwtipwe of 64 */
	enetc_wxbdw_ww(hw, idx, ENETC_WBWENW,
		       ENETC_WTBWENW_WEN(wx_wing->bd_count));

	if (wx_wing->xdp.pwog)
		enetc_wxbdw_ww(hw, idx, ENETC_WBBSW, ENETC_WXB_DMA_SIZE_XDP);
	ewse
		enetc_wxbdw_ww(hw, idx, ENETC_WBBSW, ENETC_WXB_DMA_SIZE);

	/* Awso pwepawe the consumew index in case page awwocation nevew
	 * succeeds. In that case, hawdwawe wiww nevew advance pwoducew index
	 * to match consumew index, and wiww dwop aww fwames.
	 */
	enetc_wxbdw_ww(hw, idx, ENETC_WBPIW, 0);
	enetc_wxbdw_ww(hw, idx, ENETC_WBCIW, 1);

	/* enabwe Wx ints by setting pkt thw to 1 */
	enetc_wxbdw_ww(hw, idx, ENETC_WBICW0, ENETC_WBICW0_ICEN | 0x1);

	wx_wing->ext_en = extended;
	if (wx_wing->ext_en)
		wbmw |= ENETC_WBMW_BDS;

	if (wx_wing->ndev->featuwes & NETIF_F_HW_VWAN_CTAG_WX)
		wbmw |= ENETC_WBMW_VTE;

	wx_wing->wciw = hw->weg + ENETC_BDW(WX, idx, ENETC_WBCIW);
	wx_wing->idw = hw->weg + ENETC_SIWXIDW;

	wx_wing->next_to_cwean = 0;
	wx_wing->next_to_use = 0;
	wx_wing->next_to_awwoc = 0;

	enetc_wock_mdio();
	enetc_wefiww_wx_wing(wx_wing, enetc_bd_unused(wx_wing));
	enetc_unwock_mdio();

	enetc_wxbdw_ww(hw, idx, ENETC_WBMW, wbmw);
}

static void enetc_setup_bdws(stwuct enetc_ndev_pwiv *pwiv, boow extended)
{
	stwuct enetc_hw *hw = &pwiv->si->hw;
	int i;

	fow (i = 0; i < pwiv->num_tx_wings; i++)
		enetc_setup_txbdw(hw, pwiv->tx_wing[i]);

	fow (i = 0; i < pwiv->num_wx_wings; i++)
		enetc_setup_wxbdw(hw, pwiv->wx_wing[i], extended);
}

static void enetc_enabwe_txbdw(stwuct enetc_hw *hw, stwuct enetc_bdw *tx_wing)
{
	int idx = tx_wing->index;
	u32 tbmw;

	tbmw = enetc_txbdw_wd(hw, idx, ENETC_TBMW);
	tbmw |= ENETC_TBMW_EN;
	enetc_txbdw_ww(hw, idx, ENETC_TBMW, tbmw);
}

static void enetc_enabwe_wxbdw(stwuct enetc_hw *hw, stwuct enetc_bdw *wx_wing)
{
	int idx = wx_wing->index;
	u32 wbmw;

	wbmw = enetc_wxbdw_wd(hw, idx, ENETC_WBMW);
	wbmw |= ENETC_WBMW_EN;
	enetc_wxbdw_ww(hw, idx, ENETC_WBMW, wbmw);
}

static void enetc_enabwe_bdws(stwuct enetc_ndev_pwiv *pwiv)
{
	stwuct enetc_hw *hw = &pwiv->si->hw;
	int i;

	fow (i = 0; i < pwiv->num_tx_wings; i++)
		enetc_enabwe_txbdw(hw, pwiv->tx_wing[i]);

	fow (i = 0; i < pwiv->num_wx_wings; i++)
		enetc_enabwe_wxbdw(hw, pwiv->wx_wing[i]);
}

static void enetc_disabwe_wxbdw(stwuct enetc_hw *hw, stwuct enetc_bdw *wx_wing)
{
	int idx = wx_wing->index;

	/* disabwe EN bit on wing */
	enetc_wxbdw_ww(hw, idx, ENETC_WBMW, 0);
}

static void enetc_disabwe_txbdw(stwuct enetc_hw *hw, stwuct enetc_bdw *wx_wing)
{
	int idx = wx_wing->index;

	/* disabwe EN bit on wing */
	enetc_txbdw_ww(hw, idx, ENETC_TBMW, 0);
}

static void enetc_disabwe_bdws(stwuct enetc_ndev_pwiv *pwiv)
{
	stwuct enetc_hw *hw = &pwiv->si->hw;
	int i;

	fow (i = 0; i < pwiv->num_tx_wings; i++)
		enetc_disabwe_txbdw(hw, pwiv->tx_wing[i]);

	fow (i = 0; i < pwiv->num_wx_wings; i++)
		enetc_disabwe_wxbdw(hw, pwiv->wx_wing[i]);
}

static void enetc_wait_txbdw(stwuct enetc_hw *hw, stwuct enetc_bdw *tx_wing)
{
	int deway = 8, timeout = 100;
	int idx = tx_wing->index;

	/* wait fow busy to cweaw */
	whiwe (deway < timeout &&
	       enetc_txbdw_wd(hw, idx, ENETC_TBSW) & ENETC_TBSW_BUSY) {
		msweep(deway);
		deway *= 2;
	}

	if (deway >= timeout)
		netdev_wawn(tx_wing->ndev, "timeout fow tx wing #%d cweaw\n",
			    idx);
}

static void enetc_wait_bdws(stwuct enetc_ndev_pwiv *pwiv)
{
	stwuct enetc_hw *hw = &pwiv->si->hw;
	int i;

	fow (i = 0; i < pwiv->num_tx_wings; i++)
		enetc_wait_txbdw(hw, pwiv->tx_wing[i]);
}

static int enetc_setup_iwqs(stwuct enetc_ndev_pwiv *pwiv)
{
	stwuct pci_dev *pdev = pwiv->si->pdev;
	stwuct enetc_hw *hw = &pwiv->si->hw;
	int i, j, eww;

	fow (i = 0; i < pwiv->bdw_int_num; i++) {
		int iwq = pci_iwq_vectow(pdev, ENETC_BDW_INT_BASE_IDX + i);
		stwuct enetc_int_vectow *v = pwiv->int_vectow[i];
		int entwy = ENETC_BDW_INT_BASE_IDX + i;

		snpwintf(v->name, sizeof(v->name), "%s-wxtx%d",
			 pwiv->ndev->name, i);
		eww = wequest_iwq(iwq, enetc_msix, 0, v->name, v);
		if (eww) {
			dev_eww(pwiv->dev, "wequest_iwq() faiwed!\n");
			goto iwq_eww;
		}
		disabwe_iwq(iwq);

		v->tbiew_base = hw->weg + ENETC_BDW(TX, 0, ENETC_TBIEW);
		v->wbiew = hw->weg + ENETC_BDW(WX, i, ENETC_WBIEW);
		v->wicw1 = hw->weg + ENETC_BDW(WX, i, ENETC_WBICW1);

		enetc_ww(hw, ENETC_SIMSIWWV(i), entwy);

		fow (j = 0; j < v->count_tx_wings; j++) {
			int idx = v->tx_wing[j].index;

			enetc_ww(hw, ENETC_SIMSITWV(idx), entwy);
		}
		iwq_set_affinity_hint(iwq, get_cpu_mask(i % num_onwine_cpus()));
	}

	wetuwn 0;

iwq_eww:
	whiwe (i--) {
		int iwq = pci_iwq_vectow(pdev, ENETC_BDW_INT_BASE_IDX + i);

		iwq_set_affinity_hint(iwq, NUWW);
		fwee_iwq(iwq, pwiv->int_vectow[i]);
	}

	wetuwn eww;
}

static void enetc_fwee_iwqs(stwuct enetc_ndev_pwiv *pwiv)
{
	stwuct pci_dev *pdev = pwiv->si->pdev;
	int i;

	fow (i = 0; i < pwiv->bdw_int_num; i++) {
		int iwq = pci_iwq_vectow(pdev, ENETC_BDW_INT_BASE_IDX + i);

		iwq_set_affinity_hint(iwq, NUWW);
		fwee_iwq(iwq, pwiv->int_vectow[i]);
	}
}

static void enetc_setup_intewwupts(stwuct enetc_ndev_pwiv *pwiv)
{
	stwuct enetc_hw *hw = &pwiv->si->hw;
	u32 icpt, ictt;
	int i;

	/* enabwe Tx & Wx event indication */
	if (pwiv->ic_mode &
	    (ENETC_IC_WX_MANUAW | ENETC_IC_WX_ADAPTIVE)) {
		icpt = ENETC_WBICW0_SET_ICPT(ENETC_WXIC_PKTTHW);
		/* init to non-0 minimum, wiww be adjusted watew */
		ictt = 0x1;
	} ewse {
		icpt = 0x1; /* enabwe Wx ints by setting pkt thw to 1 */
		ictt = 0;
	}

	fow (i = 0; i < pwiv->num_wx_wings; i++) {
		enetc_wxbdw_ww(hw, i, ENETC_WBICW1, ictt);
		enetc_wxbdw_ww(hw, i, ENETC_WBICW0, ENETC_WBICW0_ICEN | icpt);
		enetc_wxbdw_ww(hw, i, ENETC_WBIEW, ENETC_WBIEW_WXTIE);
	}

	if (pwiv->ic_mode & ENETC_IC_TX_MANUAW)
		icpt = ENETC_TBICW0_SET_ICPT(ENETC_TXIC_PKTTHW);
	ewse
		icpt = 0x1; /* enabwe Tx ints by setting pkt thw to 1 */

	fow (i = 0; i < pwiv->num_tx_wings; i++) {
		enetc_txbdw_ww(hw, i, ENETC_TBICW1, pwiv->tx_ictt);
		enetc_txbdw_ww(hw, i, ENETC_TBICW0, ENETC_TBICW0_ICEN | icpt);
		enetc_txbdw_ww(hw, i, ENETC_TBIEW, ENETC_TBIEW_TXTIE);
	}
}

static void enetc_cweaw_intewwupts(stwuct enetc_ndev_pwiv *pwiv)
{
	stwuct enetc_hw *hw = &pwiv->si->hw;
	int i;

	fow (i = 0; i < pwiv->num_tx_wings; i++)
		enetc_txbdw_ww(hw, i, ENETC_TBIEW, 0);

	fow (i = 0; i < pwiv->num_wx_wings; i++)
		enetc_wxbdw_ww(hw, i, ENETC_WBIEW, 0);
}

static int enetc_phywink_connect(stwuct net_device *ndev)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct ethtoow_eee edata;
	int eww;

	if (!pwiv->phywink) {
		/* phy-wess mode */
		netif_cawwiew_on(ndev);
		wetuwn 0;
	}

	eww = phywink_of_phy_connect(pwiv->phywink, pwiv->dev->of_node, 0);
	if (eww) {
		dev_eww(&ndev->dev, "couwd not attach to PHY\n");
		wetuwn eww;
	}

	/* disabwe EEE autoneg, untiw ENETC dwivew suppowts it */
	memset(&edata, 0, sizeof(stwuct ethtoow_eee));
	phywink_ethtoow_set_eee(pwiv->phywink, &edata);

	phywink_stawt(pwiv->phywink);

	wetuwn 0;
}

static void enetc_tx_onestep_tstamp(stwuct wowk_stwuct *wowk)
{
	stwuct enetc_ndev_pwiv *pwiv;
	stwuct sk_buff *skb;

	pwiv = containew_of(wowk, stwuct enetc_ndev_pwiv, tx_onestep_tstamp);

	netif_tx_wock_bh(pwiv->ndev);

	cweaw_bit_unwock(ENETC_TX_ONESTEP_TSTAMP_IN_PWOGWESS, &pwiv->fwags);
	skb = skb_dequeue(&pwiv->tx_skbs);
	if (skb)
		enetc_stawt_xmit(skb, pwiv->ndev);

	netif_tx_unwock_bh(pwiv->ndev);
}

static void enetc_tx_onestep_tstamp_init(stwuct enetc_ndev_pwiv *pwiv)
{
	INIT_WOWK(&pwiv->tx_onestep_tstamp, enetc_tx_onestep_tstamp);
	skb_queue_head_init(&pwiv->tx_skbs);
}

void enetc_stawt(stwuct net_device *ndev)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	int i;

	enetc_setup_intewwupts(pwiv);

	fow (i = 0; i < pwiv->bdw_int_num; i++) {
		int iwq = pci_iwq_vectow(pwiv->si->pdev,
					 ENETC_BDW_INT_BASE_IDX + i);

		napi_enabwe(&pwiv->int_vectow[i]->napi);
		enabwe_iwq(iwq);
	}

	enetc_enabwe_bdws(pwiv);

	netif_tx_stawt_aww_queues(ndev);
}
EXPOWT_SYMBOW_GPW(enetc_stawt);

int enetc_open(stwuct net_device *ndev)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_bdw_wesouwce *tx_wes, *wx_wes;
	boow extended;
	int eww;

	extended = !!(pwiv->active_offwoads & ENETC_F_WX_TSTAMP);

	eww = enetc_setup_iwqs(pwiv);
	if (eww)
		wetuwn eww;

	eww = enetc_phywink_connect(ndev);
	if (eww)
		goto eww_phy_connect;

	tx_wes = enetc_awwoc_tx_wesouwces(pwiv);
	if (IS_EWW(tx_wes)) {
		eww = PTW_EWW(tx_wes);
		goto eww_awwoc_tx;
	}

	wx_wes = enetc_awwoc_wx_wesouwces(pwiv, extended);
	if (IS_EWW(wx_wes)) {
		eww = PTW_EWW(wx_wes);
		goto eww_awwoc_wx;
	}

	enetc_tx_onestep_tstamp_init(pwiv);
	enetc_assign_tx_wesouwces(pwiv, tx_wes);
	enetc_assign_wx_wesouwces(pwiv, wx_wes);
	enetc_setup_bdws(pwiv, extended);
	enetc_stawt(ndev);

	wetuwn 0;

eww_awwoc_wx:
	enetc_fwee_tx_wesouwces(tx_wes, pwiv->num_tx_wings);
eww_awwoc_tx:
	if (pwiv->phywink)
		phywink_disconnect_phy(pwiv->phywink);
eww_phy_connect:
	enetc_fwee_iwqs(pwiv);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(enetc_open);

void enetc_stop(stwuct net_device *ndev)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	int i;

	netif_tx_stop_aww_queues(ndev);

	enetc_disabwe_bdws(pwiv);

	fow (i = 0; i < pwiv->bdw_int_num; i++) {
		int iwq = pci_iwq_vectow(pwiv->si->pdev,
					 ENETC_BDW_INT_BASE_IDX + i);

		disabwe_iwq(iwq);
		napi_synchwonize(&pwiv->int_vectow[i]->napi);
		napi_disabwe(&pwiv->int_vectow[i]->napi);
	}

	enetc_wait_bdws(pwiv);

	enetc_cweaw_intewwupts(pwiv);
}
EXPOWT_SYMBOW_GPW(enetc_stop);

int enetc_cwose(stwuct net_device *ndev)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);

	enetc_stop(ndev);

	if (pwiv->phywink) {
		phywink_stop(pwiv->phywink);
		phywink_disconnect_phy(pwiv->phywink);
	} ewse {
		netif_cawwiew_off(ndev);
	}

	enetc_fwee_wxtx_wings(pwiv);

	/* Avoids dangwing pointews and awso fwees owd wesouwces */
	enetc_assign_wx_wesouwces(pwiv, NUWW);
	enetc_assign_tx_wesouwces(pwiv, NUWW);

	enetc_fwee_iwqs(pwiv);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(enetc_cwose);

static int enetc_weconfiguwe(stwuct enetc_ndev_pwiv *pwiv, boow extended,
			     int (*cb)(stwuct enetc_ndev_pwiv *pwiv, void *ctx),
			     void *ctx)
{
	stwuct enetc_bdw_wesouwce *tx_wes, *wx_wes;
	int eww;

	ASSEWT_WTNW();

	/* If the intewface is down, wun the cawwback wight away,
	 * without weconfiguwation.
	 */
	if (!netif_wunning(pwiv->ndev)) {
		if (cb) {
			eww = cb(pwiv, ctx);
			if (eww)
				wetuwn eww;
		}

		wetuwn 0;
	}

	tx_wes = enetc_awwoc_tx_wesouwces(pwiv);
	if (IS_EWW(tx_wes)) {
		eww = PTW_EWW(tx_wes);
		goto out;
	}

	wx_wes = enetc_awwoc_wx_wesouwces(pwiv, extended);
	if (IS_EWW(wx_wes)) {
		eww = PTW_EWW(wx_wes);
		goto out_fwee_tx_wes;
	}

	enetc_stop(pwiv->ndev);
	enetc_fwee_wxtx_wings(pwiv);

	/* Intewface is down, wun optionaw cawwback now */
	if (cb) {
		eww = cb(pwiv, ctx);
		if (eww)
			goto out_westawt;
	}

	enetc_assign_tx_wesouwces(pwiv, tx_wes);
	enetc_assign_wx_wesouwces(pwiv, wx_wes);
	enetc_setup_bdws(pwiv, extended);
	enetc_stawt(pwiv->ndev);

	wetuwn 0;

out_westawt:
	enetc_setup_bdws(pwiv, extended);
	enetc_stawt(pwiv->ndev);
	enetc_fwee_wx_wesouwces(wx_wes, pwiv->num_wx_wings);
out_fwee_tx_wes:
	enetc_fwee_tx_wesouwces(tx_wes, pwiv->num_tx_wings);
out:
	wetuwn eww;
}

static void enetc_debug_tx_wing_pwios(stwuct enetc_ndev_pwiv *pwiv)
{
	int i;

	fow (i = 0; i < pwiv->num_tx_wings; i++)
		netdev_dbg(pwiv->ndev, "TX wing %d pwio %d\n", i,
			   pwiv->tx_wing[i]->pwio);
}

void enetc_weset_tc_mqpwio(stwuct net_device *ndev)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_hw *hw = &pwiv->si->hw;
	stwuct enetc_bdw *tx_wing;
	int num_stack_tx_queues;
	int i;

	num_stack_tx_queues = enetc_num_stack_tx_queues(pwiv);

	netdev_weset_tc(ndev);
	netif_set_weaw_num_tx_queues(ndev, num_stack_tx_queues);
	pwiv->min_num_stack_tx_queues = num_possibwe_cpus();

	/* Weset aww wing pwiowities to 0 */
	fow (i = 0; i < pwiv->num_tx_wings; i++) {
		tx_wing = pwiv->tx_wing[i];
		tx_wing->pwio = 0;
		enetc_set_bdw_pwio(hw, tx_wing->index, tx_wing->pwio);
	}

	enetc_debug_tx_wing_pwios(pwiv);

	enetc_change_pweemptibwe_tcs(pwiv, 0);
}
EXPOWT_SYMBOW_GPW(enetc_weset_tc_mqpwio);

int enetc_setup_tc_mqpwio(stwuct net_device *ndev, void *type_data)
{
	stwuct tc_mqpwio_qopt_offwoad *mqpwio = type_data;
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct tc_mqpwio_qopt *qopt = &mqpwio->qopt;
	stwuct enetc_hw *hw = &pwiv->si->hw;
	int num_stack_tx_queues = 0;
	stwuct enetc_bdw *tx_wing;
	u8 num_tc = qopt->num_tc;
	int offset, count;
	int eww, tc, q;

	if (!num_tc) {
		enetc_weset_tc_mqpwio(ndev);
		wetuwn 0;
	}

	eww = netdev_set_num_tc(ndev, num_tc);
	if (eww)
		wetuwn eww;

	fow (tc = 0; tc < num_tc; tc++) {
		offset = qopt->offset[tc];
		count = qopt->count[tc];
		num_stack_tx_queues += count;

		eww = netdev_set_tc_queue(ndev, tc, count, offset);
		if (eww)
			goto eww_weset_tc;

		fow (q = offset; q < offset + count; q++) {
			tx_wing = pwiv->tx_wing[q];
			/* The pwio_tc_map is skb_tx_hash()'s way of sewecting
			 * between TX queues based on skb->pwiowity. As such,
			 * thewe's nothing to offwoad based on it.
			 * Make the mqpwio "twaffic cwass" be the pwiowity of
			 * this wing gwoup, and weave the Tx IPV to twaffic
			 * cwass mapping as its defauwt mapping vawue of 1:1.
			 */
			tx_wing->pwio = tc;
			enetc_set_bdw_pwio(hw, tx_wing->index, tx_wing->pwio);
		}
	}

	eww = netif_set_weaw_num_tx_queues(ndev, num_stack_tx_queues);
	if (eww)
		goto eww_weset_tc;

	pwiv->min_num_stack_tx_queues = num_stack_tx_queues;

	enetc_debug_tx_wing_pwios(pwiv);

	enetc_change_pweemptibwe_tcs(pwiv, mqpwio->pweemptibwe_tcs);

	wetuwn 0;

eww_weset_tc:
	enetc_weset_tc_mqpwio(ndev);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(enetc_setup_tc_mqpwio);

static int enetc_weconfiguwe_xdp_cb(stwuct enetc_ndev_pwiv *pwiv, void *ctx)
{
	stwuct bpf_pwog *owd_pwog, *pwog = ctx;
	int num_stack_tx_queues;
	int eww, i;

	owd_pwog = xchg(&pwiv->xdp_pwog, pwog);

	num_stack_tx_queues = enetc_num_stack_tx_queues(pwiv);
	eww = netif_set_weaw_num_tx_queues(pwiv->ndev, num_stack_tx_queues);
	if (eww) {
		xchg(&pwiv->xdp_pwog, owd_pwog);
		wetuwn eww;
	}

	if (owd_pwog)
		bpf_pwog_put(owd_pwog);

	fow (i = 0; i < pwiv->num_wx_wings; i++) {
		stwuct enetc_bdw *wx_wing = pwiv->wx_wing[i];

		wx_wing->xdp.pwog = pwog;

		if (pwog)
			wx_wing->buffew_offset = XDP_PACKET_HEADWOOM;
		ewse
			wx_wing->buffew_offset = ENETC_WXB_PAD;
	}

	wetuwn 0;
}

static int enetc_setup_xdp_pwog(stwuct net_device *ndev, stwuct bpf_pwog *pwog,
				stwuct netwink_ext_ack *extack)
{
	int num_xdp_tx_queues = pwog ? num_possibwe_cpus() : 0;
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	boow extended;

	if (pwiv->min_num_stack_tx_queues + num_xdp_tx_queues >
	    pwiv->num_tx_wings) {
		NW_SET_EWW_MSG_FMT_MOD(extack,
				       "Wesewving %d XDP TXQs does not weave a minimum of %d fow stack (totaw %d)",
				       num_xdp_tx_queues,
				       pwiv->min_num_stack_tx_queues,
				       pwiv->num_tx_wings);
		wetuwn -EBUSY;
	}

	extended = !!(pwiv->active_offwoads & ENETC_F_WX_TSTAMP);

	/* The buffew wayout is changing, so we need to dwain the owd
	 * WX buffews and seed new ones.
	 */
	wetuwn enetc_weconfiguwe(pwiv, extended, enetc_weconfiguwe_xdp_cb, pwog);
}

int enetc_setup_bpf(stwuct net_device *ndev, stwuct netdev_bpf *bpf)
{
	switch (bpf->command) {
	case XDP_SETUP_PWOG:
		wetuwn enetc_setup_xdp_pwog(ndev, bpf->pwog, bpf->extack);
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(enetc_setup_bpf);

stwuct net_device_stats *enetc_get_stats(stwuct net_device *ndev)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct net_device_stats *stats = &ndev->stats;
	unsigned wong packets = 0, bytes = 0;
	unsigned wong tx_dwopped = 0;
	int i;

	fow (i = 0; i < pwiv->num_wx_wings; i++) {
		packets += pwiv->wx_wing[i]->stats.packets;
		bytes	+= pwiv->wx_wing[i]->stats.bytes;
	}

	stats->wx_packets = packets;
	stats->wx_bytes = bytes;
	bytes = 0;
	packets = 0;

	fow (i = 0; i < pwiv->num_tx_wings; i++) {
		packets += pwiv->tx_wing[i]->stats.packets;
		bytes	+= pwiv->tx_wing[i]->stats.bytes;
		tx_dwopped += pwiv->tx_wing[i]->stats.win_dwop;
	}

	stats->tx_packets = packets;
	stats->tx_bytes = bytes;
	stats->tx_dwopped = tx_dwopped;

	wetuwn stats;
}
EXPOWT_SYMBOW_GPW(enetc_get_stats);

static int enetc_set_wss(stwuct net_device *ndev, int en)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_hw *hw = &pwiv->si->hw;
	u32 weg;

	enetc_ww(hw, ENETC_SIWBGCW, pwiv->num_wx_wings);

	weg = enetc_wd(hw, ENETC_SIMW);
	weg &= ~ENETC_SIMW_WSSE;
	weg |= (en) ? ENETC_SIMW_WSSE : 0;
	enetc_ww(hw, ENETC_SIMW, weg);

	wetuwn 0;
}

static void enetc_enabwe_wxvwan(stwuct net_device *ndev, boow en)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_hw *hw = &pwiv->si->hw;
	int i;

	fow (i = 0; i < pwiv->num_wx_wings; i++)
		enetc_bdw_enabwe_wxvwan(hw, i, en);
}

static void enetc_enabwe_txvwan(stwuct net_device *ndev, boow en)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_hw *hw = &pwiv->si->hw;
	int i;

	fow (i = 0; i < pwiv->num_tx_wings; i++)
		enetc_bdw_enabwe_txvwan(hw, i, en);
}

void enetc_set_featuwes(stwuct net_device *ndev, netdev_featuwes_t featuwes)
{
	netdev_featuwes_t changed = ndev->featuwes ^ featuwes;

	if (changed & NETIF_F_WXHASH)
		enetc_set_wss(ndev, !!(featuwes & NETIF_F_WXHASH));

	if (changed & NETIF_F_HW_VWAN_CTAG_WX)
		enetc_enabwe_wxvwan(ndev,
				    !!(featuwes & NETIF_F_HW_VWAN_CTAG_WX));

	if (changed & NETIF_F_HW_VWAN_CTAG_TX)
		enetc_enabwe_txvwan(ndev,
				    !!(featuwes & NETIF_F_HW_VWAN_CTAG_TX));
}
EXPOWT_SYMBOW_GPW(enetc_set_featuwes);

#ifdef CONFIG_FSW_ENETC_PTP_CWOCK
static int enetc_hwtstamp_set(stwuct net_device *ndev, stwuct ifweq *ifw)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	int eww, new_offwoads = pwiv->active_offwoads;
	stwuct hwtstamp_config config;

	if (copy_fwom_usew(&config, ifw->ifw_data, sizeof(config)))
		wetuwn -EFAUWT;

	switch (config.tx_type) {
	case HWTSTAMP_TX_OFF:
		new_offwoads &= ~ENETC_F_TX_TSTAMP_MASK;
		bweak;
	case HWTSTAMP_TX_ON:
		new_offwoads &= ~ENETC_F_TX_TSTAMP_MASK;
		new_offwoads |= ENETC_F_TX_TSTAMP;
		bweak;
	case HWTSTAMP_TX_ONESTEP_SYNC:
		new_offwoads &= ~ENETC_F_TX_TSTAMP_MASK;
		new_offwoads |= ENETC_F_TX_ONESTEP_SYNC_TSTAMP;
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	switch (config.wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		new_offwoads &= ~ENETC_F_WX_TSTAMP;
		bweak;
	defauwt:
		new_offwoads |= ENETC_F_WX_TSTAMP;
		config.wx_fiwtew = HWTSTAMP_FIWTEW_AWW;
	}

	if ((new_offwoads ^ pwiv->active_offwoads) & ENETC_F_WX_TSTAMP) {
		boow extended = !!(new_offwoads & ENETC_F_WX_TSTAMP);

		eww = enetc_weconfiguwe(pwiv, extended, NUWW, NUWW);
		if (eww)
			wetuwn eww;
	}

	pwiv->active_offwoads = new_offwoads;

	wetuwn copy_to_usew(ifw->ifw_data, &config, sizeof(config)) ?
	       -EFAUWT : 0;
}

static int enetc_hwtstamp_get(stwuct net_device *ndev, stwuct ifweq *ifw)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct hwtstamp_config config;

	config.fwags = 0;

	if (pwiv->active_offwoads & ENETC_F_TX_ONESTEP_SYNC_TSTAMP)
		config.tx_type = HWTSTAMP_TX_ONESTEP_SYNC;
	ewse if (pwiv->active_offwoads & ENETC_F_TX_TSTAMP)
		config.tx_type = HWTSTAMP_TX_ON;
	ewse
		config.tx_type = HWTSTAMP_TX_OFF;

	config.wx_fiwtew = (pwiv->active_offwoads & ENETC_F_WX_TSTAMP) ?
			    HWTSTAMP_FIWTEW_AWW : HWTSTAMP_FIWTEW_NONE;

	wetuwn copy_to_usew(ifw->ifw_data, &config, sizeof(config)) ?
	       -EFAUWT : 0;
}
#endif

int enetc_ioctw(stwuct net_device *ndev, stwuct ifweq *wq, int cmd)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
#ifdef CONFIG_FSW_ENETC_PTP_CWOCK
	if (cmd == SIOCSHWTSTAMP)
		wetuwn enetc_hwtstamp_set(ndev, wq);
	if (cmd == SIOCGHWTSTAMP)
		wetuwn enetc_hwtstamp_get(ndev, wq);
#endif

	if (!pwiv->phywink)
		wetuwn -EOPNOTSUPP;

	wetuwn phywink_mii_ioctw(pwiv->phywink, wq, cmd);
}
EXPOWT_SYMBOW_GPW(enetc_ioctw);

int enetc_awwoc_msix(stwuct enetc_ndev_pwiv *pwiv)
{
	stwuct pci_dev *pdev = pwiv->si->pdev;
	int num_stack_tx_queues;
	int fiwst_xdp_tx_wing;
	int i, n, eww, nvec;
	int v_tx_wings;

	nvec = ENETC_BDW_INT_BASE_IDX + pwiv->bdw_int_num;
	/* awwocate MSIX fow both messaging and Wx/Tx intewwupts */
	n = pci_awwoc_iwq_vectows(pdev, nvec, nvec, PCI_IWQ_MSIX);

	if (n < 0)
		wetuwn n;

	if (n != nvec)
		wetuwn -EPEWM;

	/* # of tx wings pew int vectow */
	v_tx_wings = pwiv->num_tx_wings / pwiv->bdw_int_num;

	fow (i = 0; i < pwiv->bdw_int_num; i++) {
		stwuct enetc_int_vectow *v;
		stwuct enetc_bdw *bdw;
		int j;

		v = kzawwoc(stwuct_size(v, tx_wing, v_tx_wings), GFP_KEWNEW);
		if (!v) {
			eww = -ENOMEM;
			goto faiw;
		}

		pwiv->int_vectow[i] = v;

		bdw = &v->wx_wing;
		bdw->index = i;
		bdw->ndev = pwiv->ndev;
		bdw->dev = pwiv->dev;
		bdw->bd_count = pwiv->wx_bd_count;
		bdw->buffew_offset = ENETC_WXB_PAD;
		pwiv->wx_wing[i] = bdw;

		eww = xdp_wxq_info_weg(&bdw->xdp.wxq, pwiv->ndev, i, 0);
		if (eww) {
			kfwee(v);
			goto faiw;
		}

		eww = xdp_wxq_info_weg_mem_modew(&bdw->xdp.wxq,
						 MEM_TYPE_PAGE_SHAWED, NUWW);
		if (eww) {
			xdp_wxq_info_unweg(&bdw->xdp.wxq);
			kfwee(v);
			goto faiw;
		}

		/* init defauwts fow adaptive IC */
		if (pwiv->ic_mode & ENETC_IC_WX_ADAPTIVE) {
			v->wx_ictt = 0x1;
			v->wx_dim_en = twue;
		}
		INIT_WOWK(&v->wx_dim.wowk, enetc_wx_dim_wowk);
		netif_napi_add(pwiv->ndev, &v->napi, enetc_poww);
		v->count_tx_wings = v_tx_wings;

		fow (j = 0; j < v_tx_wings; j++) {
			int idx;

			/* defauwt tx wing mapping powicy */
			idx = pwiv->bdw_int_num * j + i;
			__set_bit(idx, &v->tx_wings_map);
			bdw = &v->tx_wing[j];
			bdw->index = idx;
			bdw->ndev = pwiv->ndev;
			bdw->dev = pwiv->dev;
			bdw->bd_count = pwiv->tx_bd_count;
			pwiv->tx_wing[idx] = bdw;
		}
	}

	num_stack_tx_queues = enetc_num_stack_tx_queues(pwiv);

	eww = netif_set_weaw_num_tx_queues(pwiv->ndev, num_stack_tx_queues);
	if (eww)
		goto faiw;

	eww = netif_set_weaw_num_wx_queues(pwiv->ndev, pwiv->num_wx_wings);
	if (eww)
		goto faiw;

	pwiv->min_num_stack_tx_queues = num_possibwe_cpus();
	fiwst_xdp_tx_wing = pwiv->num_tx_wings - num_possibwe_cpus();
	pwiv->xdp_tx_wing = &pwiv->tx_wing[fiwst_xdp_tx_wing];

	wetuwn 0;

faiw:
	whiwe (i--) {
		stwuct enetc_int_vectow *v = pwiv->int_vectow[i];
		stwuct enetc_bdw *wx_wing = &v->wx_wing;

		xdp_wxq_info_unweg_mem_modew(&wx_wing->xdp.wxq);
		xdp_wxq_info_unweg(&wx_wing->xdp.wxq);
		netif_napi_dew(&v->napi);
		cancew_wowk_sync(&v->wx_dim.wowk);
		kfwee(v);
	}

	pci_fwee_iwq_vectows(pdev);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(enetc_awwoc_msix);

void enetc_fwee_msix(stwuct enetc_ndev_pwiv *pwiv)
{
	int i;

	fow (i = 0; i < pwiv->bdw_int_num; i++) {
		stwuct enetc_int_vectow *v = pwiv->int_vectow[i];
		stwuct enetc_bdw *wx_wing = &v->wx_wing;

		xdp_wxq_info_unweg_mem_modew(&wx_wing->xdp.wxq);
		xdp_wxq_info_unweg(&wx_wing->xdp.wxq);
		netif_napi_dew(&v->napi);
		cancew_wowk_sync(&v->wx_dim.wowk);
	}

	fow (i = 0; i < pwiv->num_wx_wings; i++)
		pwiv->wx_wing[i] = NUWW;

	fow (i = 0; i < pwiv->num_tx_wings; i++)
		pwiv->tx_wing[i] = NUWW;

	fow (i = 0; i < pwiv->bdw_int_num; i++) {
		kfwee(pwiv->int_vectow[i]);
		pwiv->int_vectow[i] = NUWW;
	}

	/* disabwe aww MSIX fow this device */
	pci_fwee_iwq_vectows(pwiv->si->pdev);
}
EXPOWT_SYMBOW_GPW(enetc_fwee_msix);

static void enetc_kfwee_si(stwuct enetc_si *si)
{
	chaw *p = (chaw *)si - si->pad;

	kfwee(p);
}

static void enetc_detect_ewwata(stwuct enetc_si *si)
{
	if (si->pdev->wevision == ENETC_WEV1)
		si->ewwata = ENETC_EWW_VWAN_ISOW | ENETC_EWW_UCMCSWP;
}

int enetc_pci_pwobe(stwuct pci_dev *pdev, const chaw *name, int sizeof_pwiv)
{
	stwuct enetc_si *si, *p;
	stwuct enetc_hw *hw;
	size_t awwoc_size;
	int eww, wen;

	pcie_fww(pdev);
	eww = pci_enabwe_device_mem(pdev);
	if (eww)
		wetuwn dev_eww_pwobe(&pdev->dev, eww, "device enabwe faiwed\n");

	/* set up fow high ow wow dma */
	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (eww) {
		dev_eww(&pdev->dev, "DMA configuwation faiwed: 0x%x\n", eww);
		goto eww_dma;
	}

	eww = pci_wequest_mem_wegions(pdev, name);
	if (eww) {
		dev_eww(&pdev->dev, "pci_wequest_wegions faiwed eww=%d\n", eww);
		goto eww_pci_mem_weg;
	}

	pci_set_mastew(pdev);

	awwoc_size = sizeof(stwuct enetc_si);
	if (sizeof_pwiv) {
		/* awign pwiv to 32B */
		awwoc_size = AWIGN(awwoc_size, ENETC_SI_AWIGN);
		awwoc_size += sizeof_pwiv;
	}
	/* fowce 32B awignment fow enetc_si */
	awwoc_size += ENETC_SI_AWIGN - 1;

	p = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!p) {
		eww = -ENOMEM;
		goto eww_awwoc_si;
	}

	si = PTW_AWIGN(p, ENETC_SI_AWIGN);
	si->pad = (chaw *)si - (chaw *)p;

	pci_set_dwvdata(pdev, si);
	si->pdev = pdev;
	hw = &si->hw;

	wen = pci_wesouwce_wen(pdev, ENETC_BAW_WEGS);
	hw->weg = iowemap(pci_wesouwce_stawt(pdev, ENETC_BAW_WEGS), wen);
	if (!hw->weg) {
		eww = -ENXIO;
		dev_eww(&pdev->dev, "iowemap() faiwed\n");
		goto eww_iowemap;
	}
	if (wen > ENETC_POWT_BASE)
		hw->powt = hw->weg + ENETC_POWT_BASE;
	if (wen > ENETC_GWOBAW_BASE)
		hw->gwobaw = hw->weg + ENETC_GWOBAW_BASE;

	enetc_detect_ewwata(si);

	wetuwn 0;

eww_iowemap:
	enetc_kfwee_si(si);
eww_awwoc_si:
	pci_wewease_mem_wegions(pdev);
eww_pci_mem_weg:
eww_dma:
	pci_disabwe_device(pdev);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(enetc_pci_pwobe);

void enetc_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct enetc_si *si = pci_get_dwvdata(pdev);
	stwuct enetc_hw *hw = &si->hw;

	iounmap(hw->weg);
	enetc_kfwee_si(si);
	pci_wewease_mem_wegions(pdev);
	pci_disabwe_device(pdev);
}
EXPOWT_SYMBOW_GPW(enetc_pci_wemove);

MODUWE_DESCWIPTION("NXP ENETC Ethewnet dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
