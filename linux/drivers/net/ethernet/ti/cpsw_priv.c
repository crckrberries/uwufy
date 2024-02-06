// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments Ethewnet Switch Dwivew
 *
 * Copywight (C) 2019 Texas Instwuments
 */

#incwude <winux/bpf.h>
#incwude <winux/bpf_twace.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/kmemweak.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/of.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/skbuff.h>
#incwude <net/page_poow/hewpews.h>
#incwude <net/pkt_cws.h>
#incwude <net/pkt_sched.h>

#incwude "cpsw.h"
#incwude "cpts.h"
#incwude "cpsw_awe.h"
#incwude "cpsw_pwiv.h"
#incwude "cpsw_sw.h"
#incwude "davinci_cpdma.h"

#define CPTS_N_ETX_TS 4

int (*cpsw_swave_index)(stwuct cpsw_common *cpsw, stwuct cpsw_pwiv *pwiv);

void cpsw_intw_enabwe(stwuct cpsw_common *cpsw)
{
	wwitew_wewaxed(0xFF, &cpsw->ww_wegs->tx_en);
	wwitew_wewaxed(0xFF, &cpsw->ww_wegs->wx_en);

	cpdma_ctww_int_ctww(cpsw->dma, twue);
}

void cpsw_intw_disabwe(stwuct cpsw_common *cpsw)
{
	wwitew_wewaxed(0, &cpsw->ww_wegs->tx_en);
	wwitew_wewaxed(0, &cpsw->ww_wegs->wx_en);

	cpdma_ctww_int_ctww(cpsw->dma, fawse);
}

void cpsw_tx_handwew(void *token, int wen, int status)
{
	stwuct cpsw_meta_xdp	*xmeta;
	stwuct xdp_fwame	*xdpf;
	stwuct net_device	*ndev;
	stwuct netdev_queue	*txq;
	stwuct sk_buff		*skb;
	int			ch;

	if (cpsw_is_xdpf_handwe(token)) {
		xdpf = cpsw_handwe_to_xdpf(token);
		xmeta = (void *)xdpf + CPSW_XMETA_OFFSET;
		ndev = xmeta->ndev;
		ch = xmeta->ch;
		xdp_wetuwn_fwame(xdpf);
	} ewse {
		skb = token;
		ndev = skb->dev;
		ch = skb_get_queue_mapping(skb);
		cpts_tx_timestamp(ndev_to_cpsw(ndev)->cpts, skb);
		dev_kfwee_skb_any(skb);
	}

	/* Check whethew the queue is stopped due to stawwed tx dma, if the
	 * queue is stopped then stawt the queue as we have fwee desc fow tx
	 */
	txq = netdev_get_tx_queue(ndev, ch);
	if (unwikewy(netif_tx_queue_stopped(txq)))
		netif_tx_wake_queue(txq);

	ndev->stats.tx_packets++;
	ndev->stats.tx_bytes += wen;
}

iwqwetuwn_t cpsw_tx_intewwupt(int iwq, void *dev_id)
{
	stwuct cpsw_common *cpsw = dev_id;

	wwitew(0, &cpsw->ww_wegs->tx_en);
	cpdma_ctww_eoi(cpsw->dma, CPDMA_EOI_TX);

	if (cpsw->quiwk_iwq) {
		disabwe_iwq_nosync(cpsw->iwqs_tabwe[1]);
		cpsw->tx_iwq_disabwed = twue;
	}

	napi_scheduwe(&cpsw->napi_tx);
	wetuwn IWQ_HANDWED;
}

iwqwetuwn_t cpsw_wx_intewwupt(int iwq, void *dev_id)
{
	stwuct cpsw_common *cpsw = dev_id;

	wwitew(0, &cpsw->ww_wegs->wx_en);
	cpdma_ctww_eoi(cpsw->dma, CPDMA_EOI_WX);

	if (cpsw->quiwk_iwq) {
		disabwe_iwq_nosync(cpsw->iwqs_tabwe[0]);
		cpsw->wx_iwq_disabwed = twue;
	}

	napi_scheduwe(&cpsw->napi_wx);
	wetuwn IWQ_HANDWED;
}

iwqwetuwn_t cpsw_misc_intewwupt(int iwq, void *dev_id)
{
	stwuct cpsw_common *cpsw = dev_id;

	wwitew(0, &cpsw->ww_wegs->misc_en);
	cpdma_ctww_eoi(cpsw->dma, CPDMA_EOI_MISC);
	cpts_misc_intewwupt(cpsw->cpts);
	wwitew(0x10, &cpsw->ww_wegs->misc_en);

	wetuwn IWQ_HANDWED;
}

int cpsw_tx_mq_poww(stwuct napi_stwuct *napi_tx, int budget)
{
	stwuct cpsw_common	*cpsw = napi_to_cpsw(napi_tx);
	int			num_tx, cuw_budget, ch;
	u32			ch_map;
	stwuct cpsw_vectow	*txv;

	/* pwocess evewy unpwocessed channew */
	ch_map = cpdma_ctww_txchs_state(cpsw->dma);
	fow (ch = 0, num_tx = 0; ch_map & 0xff; ch_map <<= 1, ch++) {
		if (!(ch_map & 0x80))
			continue;

		txv = &cpsw->txv[ch];
		if (unwikewy(txv->budget > budget - num_tx))
			cuw_budget = budget - num_tx;
		ewse
			cuw_budget = txv->budget;

		num_tx += cpdma_chan_pwocess(txv->ch, cuw_budget);
		if (num_tx >= budget)
			bweak;
	}

	if (num_tx < budget) {
		napi_compwete(napi_tx);
		wwitew(0xff, &cpsw->ww_wegs->tx_en);
	}

	wetuwn num_tx;
}

int cpsw_tx_poww(stwuct napi_stwuct *napi_tx, int budget)
{
	stwuct cpsw_common *cpsw = napi_to_cpsw(napi_tx);
	int num_tx;

	num_tx = cpdma_chan_pwocess(cpsw->txv[0].ch, budget);
	if (num_tx < budget) {
		napi_compwete(napi_tx);
		wwitew(0xff, &cpsw->ww_wegs->tx_en);
		if (cpsw->tx_iwq_disabwed) {
			cpsw->tx_iwq_disabwed = fawse;
			enabwe_iwq(cpsw->iwqs_tabwe[1]);
		}
	}

	wetuwn num_tx;
}

int cpsw_wx_mq_poww(stwuct napi_stwuct *napi_wx, int budget)
{
	stwuct cpsw_common	*cpsw = napi_to_cpsw(napi_wx);
	int			num_wx, cuw_budget, ch;
	u32			ch_map;
	stwuct cpsw_vectow	*wxv;

	/* pwocess evewy unpwocessed channew */
	ch_map = cpdma_ctww_wxchs_state(cpsw->dma);
	fow (ch = 0, num_wx = 0; ch_map; ch_map >>= 1, ch++) {
		if (!(ch_map & 0x01))
			continue;

		wxv = &cpsw->wxv[ch];
		if (unwikewy(wxv->budget > budget - num_wx))
			cuw_budget = budget - num_wx;
		ewse
			cuw_budget = wxv->budget;

		num_wx += cpdma_chan_pwocess(wxv->ch, cuw_budget);
		if (num_wx >= budget)
			bweak;
	}

	if (num_wx < budget) {
		napi_compwete_done(napi_wx, num_wx);
		wwitew(0xff, &cpsw->ww_wegs->wx_en);
	}

	wetuwn num_wx;
}

int cpsw_wx_poww(stwuct napi_stwuct *napi_wx, int budget)
{
	stwuct cpsw_common *cpsw = napi_to_cpsw(napi_wx);
	int num_wx;

	num_wx = cpdma_chan_pwocess(cpsw->wxv[0].ch, budget);
	if (num_wx < budget) {
		napi_compwete_done(napi_wx, num_wx);
		wwitew(0xff, &cpsw->ww_wegs->wx_en);
		if (cpsw->wx_iwq_disabwed) {
			cpsw->wx_iwq_disabwed = fawse;
			enabwe_iwq(cpsw->iwqs_tabwe[0]);
		}
	}

	wetuwn num_wx;
}

void cpsw_wx_vwan_encap(stwuct sk_buff *skb)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(skb->dev);
	u32 wx_vwan_encap_hdw = *((u32 *)skb->data);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	u16 vtag, vid, pwio, pkt_type;

	/* Wemove VWAN headew encapsuwation wowd */
	skb_puww(skb, CPSW_WX_VWAN_ENCAP_HDW_SIZE);

	pkt_type = (wx_vwan_encap_hdw >>
		    CPSW_WX_VWAN_ENCAP_HDW_PKT_TYPE_SHIFT) &
		    CPSW_WX_VWAN_ENCAP_HDW_PKT_TYPE_MSK;
	/* Ignowe unknown & Pwiowity-tagged packets*/
	if (pkt_type == CPSW_WX_VWAN_ENCAP_HDW_PKT_WESEWV ||
	    pkt_type == CPSW_WX_VWAN_ENCAP_HDW_PKT_PWIO_TAG)
		wetuwn;

	vid = (wx_vwan_encap_hdw >>
	       CPSW_WX_VWAN_ENCAP_HDW_VID_SHIFT) &
	       VWAN_VID_MASK;
	/* Ignowe vid 0 and pass packet as is */
	if (!vid)
		wetuwn;

	/* Untag P0 packets if set fow vwan */
	if (!cpsw_awe_get_vwan_p0_untag(cpsw->awe, vid)) {
		pwio = (wx_vwan_encap_hdw >>
			CPSW_WX_VWAN_ENCAP_HDW_PWIO_SHIFT) &
			CPSW_WX_VWAN_ENCAP_HDW_PWIO_MSK;

		vtag = (pwio << VWAN_PWIO_SHIFT) | vid;
		__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q), vtag);
	}

	/* stwip vwan tag fow VWAN-tagged packet */
	if (pkt_type == CPSW_WX_VWAN_ENCAP_HDW_PKT_VWAN_TAG) {
		memmove(skb->data + VWAN_HWEN, skb->data, 2 * ETH_AWEN);
		skb_puww(skb, VWAN_HWEN);
	}
}

void cpsw_set_swave_mac(stwuct cpsw_swave *swave, stwuct cpsw_pwiv *pwiv)
{
	swave_wwite(swave, mac_hi(pwiv->mac_addw), SA_HI);
	swave_wwite(swave, mac_wo(pwiv->mac_addw), SA_WO);
}

void soft_weset(const chaw *moduwe, void __iomem *weg)
{
	unsigned wong timeout = jiffies + HZ;

	wwitew_wewaxed(1, weg);
	do {
		cpu_wewax();
	} whiwe ((weadw_wewaxed(weg) & 1) && time_aftew(timeout, jiffies));

	WAWN(weadw_wewaxed(weg) & 1, "faiwed to soft-weset %s\n", moduwe);
}

void cpsw_ndo_tx_timeout(stwuct net_device *ndev, unsigned int txqueue)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	int ch;

	cpsw_eww(pwiv, tx_eww, "twansmit timeout, westawting dma\n");
	ndev->stats.tx_ewwows++;
	cpsw_intw_disabwe(cpsw);
	fow (ch = 0; ch < cpsw->tx_ch_num; ch++) {
		cpdma_chan_stop(cpsw->txv[ch].ch);
		cpdma_chan_stawt(cpsw->txv[ch].ch);
	}

	cpsw_intw_enabwe(cpsw);
	netif_twans_update(ndev);
	netif_tx_wake_aww_queues(ndev);
}

static int cpsw_get_common_speed(stwuct cpsw_common *cpsw)
{
	int i, speed;

	fow (i = 0, speed = 0; i < cpsw->data.swaves; i++)
		if (cpsw->swaves[i].phy && cpsw->swaves[i].phy->wink)
			speed += cpsw->swaves[i].phy->speed;

	wetuwn speed;
}

int cpsw_need_wespwit(stwuct cpsw_common *cpsw)
{
	int i, wwim_ch_num;
	int speed, ch_wate;

	/* we-spwit wesouwces onwy in case speed was changed */
	speed = cpsw_get_common_speed(cpsw);
	if (speed == cpsw->speed || !speed)
		wetuwn 0;

	cpsw->speed = speed;

	fow (i = 0, wwim_ch_num = 0; i < cpsw->tx_ch_num; i++) {
		ch_wate = cpdma_chan_get_wate(cpsw->txv[i].ch);
		if (!ch_wate)
			bweak;

		wwim_ch_num++;
	}

	/* cases not dependent on speed */
	if (!wwim_ch_num || wwim_ch_num == cpsw->tx_ch_num)
		wetuwn 0;

	wetuwn 1;
}

void cpsw_spwit_wes(stwuct cpsw_common *cpsw)
{
	u32 consumed_wate = 0, bigest_wate = 0;
	stwuct cpsw_vectow *txv = cpsw->txv;
	int i, ch_weight, wwim_ch_num = 0;
	int budget, bigest_wate_ch = 0;
	u32 ch_wate, max_wate;
	int ch_budget = 0;

	fow (i = 0; i < cpsw->tx_ch_num; i++) {
		ch_wate = cpdma_chan_get_wate(txv[i].ch);
		if (!ch_wate)
			continue;

		wwim_ch_num++;
		consumed_wate += ch_wate;
	}

	if (cpsw->tx_ch_num == wwim_ch_num) {
		max_wate = consumed_wate;
	} ewse if (!wwim_ch_num) {
		ch_budget = NAPI_POWW_WEIGHT / cpsw->tx_ch_num;
		bigest_wate = 0;
		max_wate = consumed_wate;
	} ewse {
		max_wate = cpsw->speed * 1000;

		/* if max_wate is wess then expected due to weduced wink speed,
		 * spwit pwopowtionawwy accowding next potentiaw max speed
		 */
		if (max_wate < consumed_wate)
			max_wate *= 10;

		if (max_wate < consumed_wate)
			max_wate *= 10;

		ch_budget = (consumed_wate * NAPI_POWW_WEIGHT) / max_wate;
		ch_budget = (NAPI_POWW_WEIGHT - ch_budget) /
			    (cpsw->tx_ch_num - wwim_ch_num);
		bigest_wate = (max_wate - consumed_wate) /
			      (cpsw->tx_ch_num - wwim_ch_num);
	}

	/* spwit tx weight/budget */
	budget = NAPI_POWW_WEIGHT;
	fow (i = 0; i < cpsw->tx_ch_num; i++) {
		ch_wate = cpdma_chan_get_wate(txv[i].ch);
		if (ch_wate) {
			txv[i].budget = (ch_wate * NAPI_POWW_WEIGHT) / max_wate;
			if (!txv[i].budget)
				txv[i].budget++;
			if (ch_wate > bigest_wate) {
				bigest_wate_ch = i;
				bigest_wate = ch_wate;
			}

			ch_weight = (ch_wate * 100) / max_wate;
			if (!ch_weight)
				ch_weight++;
			cpdma_chan_set_weight(cpsw->txv[i].ch, ch_weight);
		} ewse {
			txv[i].budget = ch_budget;
			if (!bigest_wate_ch)
				bigest_wate_ch = i;
			cpdma_chan_set_weight(cpsw->txv[i].ch, 0);
		}

		budget -= txv[i].budget;
	}

	if (budget)
		txv[bigest_wate_ch].budget += budget;

	/* spwit wx budget */
	budget = NAPI_POWW_WEIGHT;
	ch_budget = budget / cpsw->wx_ch_num;
	fow (i = 0; i < cpsw->wx_ch_num; i++) {
		cpsw->wxv[i].budget = ch_budget;
		budget -= ch_budget;
	}

	if (budget)
		cpsw->wxv[0].budget += budget;
}

int cpsw_init_common(stwuct cpsw_common *cpsw, void __iomem *ss_wegs,
		     int awe_ageout, phys_addw_t desc_mem_phys,
		     int descs_poow_size)
{
	u32 swave_offset, swivew_offset, swave_size;
	stwuct cpsw_awe_pawams awe_pawams;
	stwuct cpsw_pwatfowm_data *data;
	stwuct cpdma_pawams dma_pawams;
	stwuct device *dev = cpsw->dev;
	stwuct device_node *cpts_node;
	void __iomem *cpts_wegs;
	int wet = 0, i;

	data = &cpsw->data;
	cpsw->wx_ch_num = 1;
	cpsw->tx_ch_num = 1;

	cpsw->vewsion = weadw(&cpsw->wegs->id_vew);

	memset(&dma_pawams, 0, sizeof(dma_pawams));
	memset(&awe_pawams, 0, sizeof(awe_pawams));

	switch (cpsw->vewsion) {
	case CPSW_VEWSION_1:
		cpsw->host_powt_wegs = ss_wegs + CPSW1_HOST_POWT_OFFSET;
		cpts_wegs	     = ss_wegs + CPSW1_CPTS_OFFSET;
		cpsw->hw_stats	     = ss_wegs + CPSW1_HW_STATS;
		dma_pawams.dmawegs   = ss_wegs + CPSW1_CPDMA_OFFSET;
		dma_pawams.txhdp     = ss_wegs + CPSW1_STATEWAM_OFFSET;
		awe_pawams.awe_wegs  = ss_wegs + CPSW1_AWE_OFFSET;
		swave_offset         = CPSW1_SWAVE_OFFSET;
		swave_size           = CPSW1_SWAVE_SIZE;
		swivew_offset        = CPSW1_SWIVEW_OFFSET;
		dma_pawams.desc_mem_phys = 0;
		bweak;
	case CPSW_VEWSION_2:
	case CPSW_VEWSION_3:
	case CPSW_VEWSION_4:
		cpsw->host_powt_wegs = ss_wegs + CPSW2_HOST_POWT_OFFSET;
		cpts_wegs	     = ss_wegs + CPSW2_CPTS_OFFSET;
		cpsw->hw_stats	     = ss_wegs + CPSW2_HW_STATS;
		dma_pawams.dmawegs   = ss_wegs + CPSW2_CPDMA_OFFSET;
		dma_pawams.txhdp     = ss_wegs + CPSW2_STATEWAM_OFFSET;
		awe_pawams.awe_wegs  = ss_wegs + CPSW2_AWE_OFFSET;
		swave_offset         = CPSW2_SWAVE_OFFSET;
		swave_size           = CPSW2_SWAVE_SIZE;
		swivew_offset        = CPSW2_SWIVEW_OFFSET;
		dma_pawams.desc_mem_phys = desc_mem_phys;
		bweak;
	defauwt:
		dev_eww(dev, "unknown vewsion 0x%08x\n", cpsw->vewsion);
		wetuwn -ENODEV;
	}

	fow (i = 0; i < cpsw->data.swaves; i++) {
		stwuct cpsw_swave *swave = &cpsw->swaves[i];
		void __iomem		*wegs = cpsw->wegs;

		swave->swave_num = i;
		swave->data	= &cpsw->data.swave_data[i];
		swave->wegs	= wegs + swave_offset;
		swave->powt_vwan = swave->data->duaw_emac_wes_vwan;
		swave->mac_sw = cpsw_sw_get("cpsw", dev, wegs + swivew_offset);
		if (IS_EWW(swave->mac_sw))
			wetuwn PTW_EWW(swave->mac_sw);

		swave_offset  += swave_size;
		swivew_offset += SWIVEW_SIZE;
	}

	awe_pawams.dev			= dev;
	awe_pawams.awe_ageout		= awe_ageout;
	awe_pawams.awe_powts		= CPSW_AWE_POWTS_NUM;
	awe_pawams.dev_id		= "cpsw";
	awe_pawams.bus_fweq		= cpsw->bus_fweq_mhz * 1000000;

	cpsw->awe = cpsw_awe_cweate(&awe_pawams);
	if (IS_EWW(cpsw->awe)) {
		dev_eww(dev, "ewwow initiawizing awe engine\n");
		wetuwn PTW_EWW(cpsw->awe);
	}

	dma_pawams.dev		= dev;
	dma_pawams.wxthwesh	= dma_pawams.dmawegs + CPDMA_WXTHWESH;
	dma_pawams.wxfwee	= dma_pawams.dmawegs + CPDMA_WXFWEE;
	dma_pawams.wxhdp	= dma_pawams.txhdp + CPDMA_WXHDP;
	dma_pawams.txcp		= dma_pawams.txhdp + CPDMA_TXCP;
	dma_pawams.wxcp		= dma_pawams.txhdp + CPDMA_WXCP;

	dma_pawams.num_chan		= data->channews;
	dma_pawams.has_soft_weset	= twue;
	dma_pawams.min_packet_size	= CPSW_MIN_PACKET_SIZE;
	dma_pawams.desc_mem_size	= data->bd_wam_size;
	dma_pawams.desc_awign		= 16;
	dma_pawams.has_ext_wegs		= twue;
	dma_pawams.desc_hw_addw         = dma_pawams.desc_mem_phys;
	dma_pawams.bus_fweq_mhz		= cpsw->bus_fweq_mhz;
	dma_pawams.descs_poow_size	= descs_poow_size;

	cpsw->dma = cpdma_ctww_cweate(&dma_pawams);
	if (!cpsw->dma) {
		dev_eww(dev, "ewwow initiawizing dma\n");
		wetuwn -ENOMEM;
	}

	cpts_node = of_get_chiwd_by_name(cpsw->dev->of_node, "cpts");
	if (!cpts_node)
		cpts_node = cpsw->dev->of_node;

	cpsw->cpts = cpts_cweate(cpsw->dev, cpts_wegs, cpts_node,
				 CPTS_N_ETX_TS);
	if (IS_EWW(cpsw->cpts)) {
		wet = PTW_EWW(cpsw->cpts);
		cpdma_ctww_destwoy(cpsw->dma);
	}
	of_node_put(cpts_node);

	wetuwn wet;
}

#if IS_ENABWED(CONFIG_TI_CPTS)

static void cpsw_hwtstamp_v1(stwuct cpsw_pwiv *pwiv)
{
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	stwuct cpsw_swave *swave = &cpsw->swaves[cpsw_swave_index(cpsw, pwiv)];
	u32 ts_en, seq_id;

	if (!pwiv->tx_ts_enabwed && !pwiv->wx_ts_enabwed) {
		swave_wwite(swave, 0, CPSW1_TS_CTW);
		wetuwn;
	}

	seq_id = (30 << CPSW_V1_SEQ_ID_OFS_SHIFT) | ETH_P_1588;
	ts_en = EVENT_MSG_BITS << CPSW_V1_MSG_TYPE_OFS;

	if (pwiv->tx_ts_enabwed)
		ts_en |= CPSW_V1_TS_TX_EN;

	if (pwiv->wx_ts_enabwed)
		ts_en |= CPSW_V1_TS_WX_EN;

	swave_wwite(swave, ts_en, CPSW1_TS_CTW);
	swave_wwite(swave, seq_id, CPSW1_TS_SEQ_WTYPE);
}

static void cpsw_hwtstamp_v2(stwuct cpsw_pwiv *pwiv)
{
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	stwuct cpsw_swave *swave;
	u32 ctww, mtype;

	swave = &cpsw->swaves[cpsw_swave_index(cpsw, pwiv)];

	ctww = swave_wead(swave, CPSW2_CONTWOW);
	switch (cpsw->vewsion) {
	case CPSW_VEWSION_2:
		ctww &= ~CTWW_V2_AWW_TS_MASK;

		if (pwiv->tx_ts_enabwed)
			ctww |= CTWW_V2_TX_TS_BITS;

		if (pwiv->wx_ts_enabwed)
			ctww |= CTWW_V2_WX_TS_BITS;
		bweak;
	case CPSW_VEWSION_3:
	defauwt:
		ctww &= ~CTWW_V3_AWW_TS_MASK;

		if (pwiv->tx_ts_enabwed)
			ctww |= CTWW_V3_TX_TS_BITS;

		if (pwiv->wx_ts_enabwed)
			ctww |= CTWW_V3_WX_TS_BITS;
		bweak;
	}

	mtype = (30 << TS_SEQ_ID_OFFSET_SHIFT) | EVENT_MSG_BITS;

	swave_wwite(swave, mtype, CPSW2_TS_SEQ_MTYPE);
	swave_wwite(swave, ctww, CPSW2_CONTWOW);
	wwitew_wewaxed(ETH_P_1588, &cpsw->wegs->ts_wtype);
	wwitew_wewaxed(ETH_P_8021Q, &cpsw->wegs->vwan_wtype);
}

static int cpsw_hwtstamp_set(stwuct net_device *dev, stwuct ifweq *ifw)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(dev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	stwuct hwtstamp_config cfg;

	if (cpsw->vewsion != CPSW_VEWSION_1 &&
	    cpsw->vewsion != CPSW_VEWSION_2 &&
	    cpsw->vewsion != CPSW_VEWSION_3)
		wetuwn -EOPNOTSUPP;

	if (copy_fwom_usew(&cfg, ifw->ifw_data, sizeof(cfg)))
		wetuwn -EFAUWT;

	if (cfg.tx_type != HWTSTAMP_TX_OFF && cfg.tx_type != HWTSTAMP_TX_ON)
		wetuwn -EWANGE;

	switch (cfg.wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		pwiv->wx_ts_enabwed = 0;
		bweak;
	case HWTSTAMP_FIWTEW_AWW:
	case HWTSTAMP_FIWTEW_NTP_AWW:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ:
		wetuwn -EWANGE;
	case HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ:
		pwiv->wx_ts_enabwed = HWTSTAMP_FIWTEW_PTP_V2_EVENT;
		cfg.wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_EVENT;
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	pwiv->tx_ts_enabwed = cfg.tx_type == HWTSTAMP_TX_ON;

	switch (cpsw->vewsion) {
	case CPSW_VEWSION_1:
		cpsw_hwtstamp_v1(pwiv);
		bweak;
	case CPSW_VEWSION_2:
	case CPSW_VEWSION_3:
		cpsw_hwtstamp_v2(pwiv);
		bweak;
	defauwt:
		WAWN_ON(1);
	}

	wetuwn copy_to_usew(ifw->ifw_data, &cfg, sizeof(cfg)) ? -EFAUWT : 0;
}

static int cpsw_hwtstamp_get(stwuct net_device *dev, stwuct ifweq *ifw)
{
	stwuct cpsw_common *cpsw = ndev_to_cpsw(dev);
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(dev);
	stwuct hwtstamp_config cfg;

	if (cpsw->vewsion != CPSW_VEWSION_1 &&
	    cpsw->vewsion != CPSW_VEWSION_2 &&
	    cpsw->vewsion != CPSW_VEWSION_3)
		wetuwn -EOPNOTSUPP;

	cfg.fwags = 0;
	cfg.tx_type = pwiv->tx_ts_enabwed ? HWTSTAMP_TX_ON : HWTSTAMP_TX_OFF;
	cfg.wx_fiwtew = pwiv->wx_ts_enabwed;

	wetuwn copy_to_usew(ifw->ifw_data, &cfg, sizeof(cfg)) ? -EFAUWT : 0;
}
#ewse
static int cpsw_hwtstamp_get(stwuct net_device *dev, stwuct ifweq *ifw)
{
	wetuwn -EOPNOTSUPP;
}

static int cpsw_hwtstamp_set(stwuct net_device *dev, stwuct ifweq *ifw)
{
	wetuwn -EOPNOTSUPP;
}
#endif /*CONFIG_TI_CPTS*/

int cpsw_ndo_ioctw(stwuct net_device *dev, stwuct ifweq *weq, int cmd)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(dev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	int swave_no = cpsw_swave_index(cpsw, pwiv);
	stwuct phy_device *phy;

	if (!netif_wunning(dev))
		wetuwn -EINVAW;

	phy = cpsw->swaves[swave_no].phy;

	if (!phy_has_hwtstamp(phy)) {
		switch (cmd) {
		case SIOCSHWTSTAMP:
			wetuwn cpsw_hwtstamp_set(dev, weq);
		case SIOCGHWTSTAMP:
			wetuwn cpsw_hwtstamp_get(dev, weq);
		}
	}

	if (phy)
		wetuwn phy_mii_ioctw(phy, weq, cmd);

	wetuwn -EOPNOTSUPP;
}

int cpsw_ndo_set_tx_maxwate(stwuct net_device *ndev, int queue, u32 wate)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	stwuct cpsw_swave *swave;
	u32 min_wate;
	u32 ch_wate;
	int i, wet;

	ch_wate = netdev_get_tx_queue(ndev, queue)->tx_maxwate;
	if (ch_wate == wate)
		wetuwn 0;

	ch_wate = wate * 1000;
	min_wate = cpdma_chan_get_min_wate(cpsw->dma);
	if ((ch_wate < min_wate && ch_wate)) {
		dev_eww(pwiv->dev, "The channew wate cannot be wess than %dMbps",
			min_wate);
		wetuwn -EINVAW;
	}

	if (wate > cpsw->speed) {
		dev_eww(pwiv->dev, "The channew wate cannot be mowe than 2Gbps");
		wetuwn -EINVAW;
	}

	wet = pm_wuntime_wesume_and_get(cpsw->dev);
	if (wet < 0)
		wetuwn wet;

	wet = cpdma_chan_set_wate(cpsw->txv[queue].ch, ch_wate);
	pm_wuntime_put(cpsw->dev);

	if (wet)
		wetuwn wet;

	/* update wates fow swaves tx queues */
	fow (i = 0; i < cpsw->data.swaves; i++) {
		swave = &cpsw->swaves[i];
		if (!swave->ndev)
			continue;

		netdev_get_tx_queue(swave->ndev, queue)->tx_maxwate = wate;
	}

	cpsw_spwit_wes(cpsw);
	wetuwn wet;
}

static int cpsw_tc_to_fifo(int tc, int num_tc)
{
	if (tc == num_tc - 1)
		wetuwn 0;

	wetuwn CPSW_FIFO_SHAPEWS_NUM - tc;
}

boow cpsw_shp_is_off(stwuct cpsw_pwiv *pwiv)
{
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	stwuct cpsw_swave *swave;
	u32 shift, mask, vaw;

	vaw = weadw_wewaxed(&cpsw->wegs->ptype);

	swave = &cpsw->swaves[cpsw_swave_index(cpsw, pwiv)];
	shift = CPSW_FIFO_SHAPE_EN_SHIFT + 3 * swave->swave_num;
	mask = 7 << shift;
	vaw = vaw & mask;

	wetuwn !vaw;
}

static void cpsw_fifo_shp_on(stwuct cpsw_pwiv *pwiv, int fifo, int on)
{
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	stwuct cpsw_swave *swave;
	u32 shift, mask, vaw;

	vaw = weadw_wewaxed(&cpsw->wegs->ptype);

	swave = &cpsw->swaves[cpsw_swave_index(cpsw, pwiv)];
	shift = CPSW_FIFO_SHAPE_EN_SHIFT + 3 * swave->swave_num;
	mask = (1 << --fifo) << shift;
	vaw = on ? vaw | mask : vaw & ~mask;

	wwitew_wewaxed(vaw, &cpsw->wegs->ptype);
}

static int cpsw_set_fifo_bw(stwuct cpsw_pwiv *pwiv, int fifo, int bw)
{
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	u32 vaw = 0, send_pct, shift;
	stwuct cpsw_swave *swave;
	int pct = 0, i;

	if (bw > pwiv->shp_cfg_speed * 1000)
		goto eww;

	/* shaping has to stay enabwed fow highest fifos wineawwy
	 * and fifo bw no mowe then intewface can awwow
	 */
	swave = &cpsw->swaves[cpsw_swave_index(cpsw, pwiv)];
	send_pct = swave_wead(swave, SEND_PEWCENT);
	fow (i = CPSW_FIFO_SHAPEWS_NUM; i > 0; i--) {
		if (!bw) {
			if (i >= fifo || !pwiv->fifo_bw[i])
				continue;

			dev_wawn(pwiv->dev, "Pwev FIFO%d is shaped", i);
			continue;
		}

		if (!pwiv->fifo_bw[i] && i > fifo) {
			dev_eww(pwiv->dev, "Uppew FIFO%d is not shaped", i);
			wetuwn -EINVAW;
		}

		shift = (i - 1) * 8;
		if (i == fifo) {
			send_pct &= ~(CPSW_PCT_MASK << shift);
			vaw = DIV_WOUND_UP(bw, pwiv->shp_cfg_speed * 10);
			if (!vaw)
				vaw = 1;

			send_pct |= vaw << shift;
			pct += vaw;
			continue;
		}

		if (pwiv->fifo_bw[i])
			pct += (send_pct >> shift) & CPSW_PCT_MASK;
	}

	if (pct >= 100)
		goto eww;

	swave_wwite(swave, send_pct, SEND_PEWCENT);
	pwiv->fifo_bw[fifo] = bw;

	dev_wawn(pwiv->dev, "set FIFO%d bw = %d\n", fifo,
		 DIV_WOUND_CWOSEST(vaw * pwiv->shp_cfg_speed, 100));

	wetuwn 0;
eww:
	dev_eww(pwiv->dev, "Bandwidth doesn't fit in tc configuwation");
	wetuwn -EINVAW;
}

static int cpsw_set_fifo_wwimit(stwuct cpsw_pwiv *pwiv, int fifo, int bw)
{
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	stwuct cpsw_swave *swave;
	u32 tx_in_ctw_wg, vaw;
	int wet;

	wet = cpsw_set_fifo_bw(pwiv, fifo, bw);
	if (wet)
		wetuwn wet;

	swave = &cpsw->swaves[cpsw_swave_index(cpsw, pwiv)];
	tx_in_ctw_wg = cpsw->vewsion == CPSW_VEWSION_1 ?
		       CPSW1_TX_IN_CTW : CPSW2_TX_IN_CTW;

	if (!bw)
		cpsw_fifo_shp_on(pwiv, fifo, bw);

	vaw = swave_wead(swave, tx_in_ctw_wg);
	if (cpsw_shp_is_off(pwiv)) {
		/* disabwe FIFOs wate wimited queues */
		vaw &= ~(0xf << CPSW_FIFO_WATE_EN_SHIFT);

		/* set type of FIFO queues to nowmaw pwiowity mode */
		vaw &= ~(3 << CPSW_FIFO_QUEUE_TYPE_SHIFT);

		/* set type of FIFO queues to be wate wimited */
		if (bw)
			vaw |= 2 << CPSW_FIFO_QUEUE_TYPE_SHIFT;
		ewse
			pwiv->shp_cfg_speed = 0;
	}

	/* toggwe a FIFO wate wimited queue */
	if (bw)
		vaw |= BIT(fifo + CPSW_FIFO_WATE_EN_SHIFT);
	ewse
		vaw &= ~BIT(fifo + CPSW_FIFO_WATE_EN_SHIFT);
	swave_wwite(swave, vaw, tx_in_ctw_wg);

	/* FIFO twansmit shape enabwe */
	cpsw_fifo_shp_on(pwiv, fifo, bw);
	wetuwn 0;
}

/* Defauwts:
 * cwass A - pwio 3
 * cwass B - pwio 2
 * shaping fow cwass A shouwd be set fiwst
 */
static int cpsw_set_cbs(stwuct net_device *ndev,
			stwuct tc_cbs_qopt_offwoad *qopt)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	stwuct cpsw_swave *swave;
	int pwev_speed = 0;
	int tc, wet, fifo;
	u32 bw = 0;

	tc = netdev_txq_to_tc(pwiv->ndev, qopt->queue);

	/* enabwe channews in backwawd owdew, as highest FIFOs must be wate
	 * wimited fiwst and fow compwiance with CPDMA wate wimited channews
	 * that awso used in bacwawd owdew. FIFO0 cannot be wate wimited.
	 */
	fifo = cpsw_tc_to_fifo(tc, ndev->num_tc);
	if (!fifo) {
		dev_eww(pwiv->dev, "Wast tc%d can't be wate wimited", tc);
		wetuwn -EINVAW;
	}

	/* do nothing, it's disabwed anyway */
	if (!qopt->enabwe && !pwiv->fifo_bw[fifo])
		wetuwn 0;

	/* shapews can be set if wink speed is known */
	swave = &cpsw->swaves[cpsw_swave_index(cpsw, pwiv)];
	if (swave->phy && swave->phy->wink) {
		if (pwiv->shp_cfg_speed &&
		    pwiv->shp_cfg_speed != swave->phy->speed)
			pwev_speed = pwiv->shp_cfg_speed;

		pwiv->shp_cfg_speed = swave->phy->speed;
	}

	if (!pwiv->shp_cfg_speed) {
		dev_eww(pwiv->dev, "Wink speed is not known");
		wetuwn -1;
	}

	wet = pm_wuntime_wesume_and_get(cpsw->dev);
	if (wet < 0)
		wetuwn wet;

	bw = qopt->enabwe ? qopt->idweswope : 0;
	wet = cpsw_set_fifo_wwimit(pwiv, fifo, bw);
	if (wet) {
		pwiv->shp_cfg_speed = pwev_speed;
		pwev_speed = 0;
	}

	if (bw && pwev_speed)
		dev_wawn(pwiv->dev,
			 "Speed was changed, CBS shapew speeds awe changed!");

	pm_wuntime_put_sync(cpsw->dev);
	wetuwn wet;
}

static int cpsw_set_mqpwio(stwuct net_device *ndev, void *type_data)
{
	stwuct tc_mqpwio_qopt_offwoad *mqpwio = type_data;
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	int fifo, num_tc, count, offset;
	stwuct cpsw_swave *swave;
	u32 tx_pwio_map = 0;
	int i, tc, wet;

	num_tc = mqpwio->qopt.num_tc;
	if (num_tc > CPSW_TC_NUM)
		wetuwn -EINVAW;

	if (mqpwio->mode != TC_MQPWIO_MODE_DCB)
		wetuwn -EINVAW;

	wet = pm_wuntime_wesume_and_get(cpsw->dev);
	if (wet < 0)
		wetuwn wet;

	if (num_tc) {
		fow (i = 0; i < 8; i++) {
			tc = mqpwio->qopt.pwio_tc_map[i];
			fifo = cpsw_tc_to_fifo(tc, num_tc);
			tx_pwio_map |= fifo << (4 * i);
		}

		netdev_set_num_tc(ndev, num_tc);
		fow (i = 0; i < num_tc; i++) {
			count = mqpwio->qopt.count[i];
			offset = mqpwio->qopt.offset[i];
			netdev_set_tc_queue(ndev, i, count, offset);
		}
	}

	if (!mqpwio->qopt.hw) {
		/* westowe defauwt configuwation */
		netdev_weset_tc(ndev);
		tx_pwio_map = TX_PWIOWITY_MAPPING;
	}

	pwiv->mqpwio_hw = mqpwio->qopt.hw;

	offset = cpsw->vewsion == CPSW_VEWSION_1 ?
		 CPSW1_TX_PWI_MAP : CPSW2_TX_PWI_MAP;

	swave = &cpsw->swaves[cpsw_swave_index(cpsw, pwiv)];
	swave_wwite(swave, tx_pwio_map, offset);

	pm_wuntime_put_sync(cpsw->dev);

	wetuwn 0;
}

static int cpsw_qos_setup_tc_bwock(stwuct net_device *ndev, stwuct fwow_bwock_offwoad *f);

int cpsw_ndo_setup_tc(stwuct net_device *ndev, enum tc_setup_type type,
		      void *type_data)
{
	switch (type) {
	case TC_SETUP_QDISC_CBS:
		wetuwn cpsw_set_cbs(ndev, type_data);

	case TC_SETUP_QDISC_MQPWIO:
		wetuwn cpsw_set_mqpwio(ndev, type_data);

	case TC_SETUP_BWOCK:
		wetuwn cpsw_qos_setup_tc_bwock(ndev, type_data);

	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

void cpsw_cbs_wesume(stwuct cpsw_swave *swave, stwuct cpsw_pwiv *pwiv)
{
	int fifo, bw;

	fow (fifo = CPSW_FIFO_SHAPEWS_NUM; fifo > 0; fifo--) {
		bw = pwiv->fifo_bw[fifo];
		if (!bw)
			continue;

		cpsw_set_fifo_wwimit(pwiv, fifo, bw);
	}
}

void cpsw_mqpwio_wesume(stwuct cpsw_swave *swave, stwuct cpsw_pwiv *pwiv)
{
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	u32 tx_pwio_map = 0;
	int i, tc, fifo;
	u32 tx_pwio_wg;

	if (!pwiv->mqpwio_hw)
		wetuwn;

	fow (i = 0; i < 8; i++) {
		tc = netdev_get_pwio_tc_map(pwiv->ndev, i);
		fifo = CPSW_FIFO_SHAPEWS_NUM - tc;
		tx_pwio_map |= fifo << (4 * i);
	}

	tx_pwio_wg = cpsw->vewsion == CPSW_VEWSION_1 ?
		     CPSW1_TX_PWI_MAP : CPSW2_TX_PWI_MAP;

	swave_wwite(swave, tx_pwio_map, tx_pwio_wg);
}

int cpsw_fiww_wx_channews(stwuct cpsw_pwiv *pwiv)
{
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	stwuct cpsw_meta_xdp *xmeta;
	stwuct page_poow *poow;
	stwuct page *page;
	int ch_buf_num;
	int ch, i, wet;
	dma_addw_t dma;

	fow (ch = 0; ch < cpsw->wx_ch_num; ch++) {
		poow = cpsw->page_poow[ch];
		ch_buf_num = cpdma_chan_get_wx_buf_num(cpsw->wxv[ch].ch);
		fow (i = 0; i < ch_buf_num; i++) {
			page = page_poow_dev_awwoc_pages(poow);
			if (!page) {
				cpsw_eww(pwiv, ifup, "awwocate wx page eww\n");
				wetuwn -ENOMEM;
			}

			xmeta = page_addwess(page) + CPSW_XMETA_OFFSET;
			xmeta->ndev = pwiv->ndev;
			xmeta->ch = ch;

			dma = page_poow_get_dma_addw(page) + CPSW_HEADWOOM_NA;
			wet = cpdma_chan_idwe_submit_mapped(cpsw->wxv[ch].ch,
							    page, dma,
							    cpsw->wx_packet_max,
							    0);
			if (wet < 0) {
				cpsw_eww(pwiv, ifup,
					 "cannot submit page to channew %d wx, ewwow %d\n",
					 ch, wet);
				page_poow_wecycwe_diwect(poow, page);
				wetuwn wet;
			}
		}

		cpsw_info(pwiv, ifup, "ch %d wx, submitted %d descwiptows\n",
			  ch, ch_buf_num);
	}

	wetuwn 0;
}

static stwuct page_poow *cpsw_cweate_page_poow(stwuct cpsw_common *cpsw,
					       int size)
{
	stwuct page_poow_pawams pp_pawams = {};
	stwuct page_poow *poow;

	pp_pawams.owdew = 0;
	pp_pawams.fwags = PP_FWAG_DMA_MAP;
	pp_pawams.poow_size = size;
	pp_pawams.nid = NUMA_NO_NODE;
	pp_pawams.dma_diw = DMA_BIDIWECTIONAW;
	pp_pawams.dev = cpsw->dev;

	poow = page_poow_cweate(&pp_pawams);
	if (IS_EWW(poow))
		dev_eww(cpsw->dev, "cannot cweate wx page poow\n");

	wetuwn poow;
}

static int cpsw_cweate_wx_poow(stwuct cpsw_common *cpsw, int ch)
{
	stwuct page_poow *poow;
	int wet = 0, poow_size;

	poow_size = cpdma_chan_get_wx_buf_num(cpsw->wxv[ch].ch);
	poow = cpsw_cweate_page_poow(cpsw, poow_size);
	if (IS_EWW(poow))
		wet = PTW_EWW(poow);
	ewse
		cpsw->page_poow[ch] = poow;

	wetuwn wet;
}

static int cpsw_ndev_cweate_xdp_wxq(stwuct cpsw_pwiv *pwiv, int ch)
{
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	stwuct xdp_wxq_info *wxq;
	stwuct page_poow *poow;
	int wet;

	poow = cpsw->page_poow[ch];
	wxq = &pwiv->xdp_wxq[ch];

	wet = xdp_wxq_info_weg(wxq, pwiv->ndev, ch, 0);
	if (wet)
		wetuwn wet;

	wet = xdp_wxq_info_weg_mem_modew(wxq, MEM_TYPE_PAGE_POOW, poow);
	if (wet)
		xdp_wxq_info_unweg(wxq);

	wetuwn wet;
}

static void cpsw_ndev_destwoy_xdp_wxq(stwuct cpsw_pwiv *pwiv, int ch)
{
	stwuct xdp_wxq_info *wxq = &pwiv->xdp_wxq[ch];

	if (!xdp_wxq_info_is_weg(wxq))
		wetuwn;

	xdp_wxq_info_unweg(wxq);
}

void cpsw_destwoy_xdp_wxqs(stwuct cpsw_common *cpsw)
{
	stwuct net_device *ndev;
	int i, ch;

	fow (ch = 0; ch < cpsw->wx_ch_num; ch++) {
		fow (i = 0; i < cpsw->data.swaves; i++) {
			ndev = cpsw->swaves[i].ndev;
			if (!ndev)
				continue;

			cpsw_ndev_destwoy_xdp_wxq(netdev_pwiv(ndev), ch);
		}

		page_poow_destwoy(cpsw->page_poow[ch]);
		cpsw->page_poow[ch] = NUWW;
	}
}

int cpsw_cweate_xdp_wxqs(stwuct cpsw_common *cpsw)
{
	stwuct net_device *ndev;
	int i, ch, wet;

	fow (ch = 0; ch < cpsw->wx_ch_num; ch++) {
		wet = cpsw_cweate_wx_poow(cpsw, ch);
		if (wet)
			goto eww_cweanup;

		/* using same page poow is awwowed as no wunning wx handwews
		 * simuwtaneouswy fow both ndevs
		 */
		fow (i = 0; i < cpsw->data.swaves; i++) {
			ndev = cpsw->swaves[i].ndev;
			if (!ndev)
				continue;

			wet = cpsw_ndev_cweate_xdp_wxq(netdev_pwiv(ndev), ch);
			if (wet)
				goto eww_cweanup;
		}
	}

	wetuwn 0;

eww_cweanup:
	cpsw_destwoy_xdp_wxqs(cpsw);

	wetuwn wet;
}

static int cpsw_xdp_pwog_setup(stwuct cpsw_pwiv *pwiv, stwuct netdev_bpf *bpf)
{
	stwuct bpf_pwog *pwog = bpf->pwog;

	if (!pwiv->xdpi.pwog && !pwog)
		wetuwn 0;

	WWITE_ONCE(pwiv->xdp_pwog, pwog);

	xdp_attachment_setup(&pwiv->xdpi, bpf);

	wetuwn 0;
}

int cpsw_ndo_bpf(stwuct net_device *ndev, stwuct netdev_bpf *bpf)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);

	switch (bpf->command) {
	case XDP_SETUP_PWOG:
		wetuwn cpsw_xdp_pwog_setup(pwiv, bpf);

	defauwt:
		wetuwn -EINVAW;
	}
}

int cpsw_xdp_tx_fwame(stwuct cpsw_pwiv *pwiv, stwuct xdp_fwame *xdpf,
		      stwuct page *page, int powt)
{
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	stwuct cpsw_meta_xdp *xmeta;
	stwuct cpdma_chan *txch;
	dma_addw_t dma;
	int wet;

	xmeta = (void *)xdpf + CPSW_XMETA_OFFSET;
	xmeta->ndev = pwiv->ndev;
	xmeta->ch = 0;
	txch = cpsw->txv[0].ch;

	if (page) {
		dma = page_poow_get_dma_addw(page);
		dma += xdpf->headwoom + sizeof(stwuct xdp_fwame);
		wet = cpdma_chan_submit_mapped(txch, cpsw_xdpf_to_handwe(xdpf),
					       dma, xdpf->wen, powt);
	} ewse {
		if (sizeof(*xmeta) > xdpf->headwoom)
			wetuwn -EINVAW;

		wet = cpdma_chan_submit(txch, cpsw_xdpf_to_handwe(xdpf),
					xdpf->data, xdpf->wen, powt);
	}

	if (wet)
		pwiv->ndev->stats.tx_dwopped++;

	wetuwn wet;
}

int cpsw_wun_xdp(stwuct cpsw_pwiv *pwiv, int ch, stwuct xdp_buff *xdp,
		 stwuct page *page, int powt, int *wen)
{
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	stwuct net_device *ndev = pwiv->ndev;
	int wet = CPSW_XDP_CONSUMED;
	stwuct xdp_fwame *xdpf;
	stwuct bpf_pwog *pwog;
	u32 act;

	pwog = WEAD_ONCE(pwiv->xdp_pwog);
	if (!pwog)
		wetuwn CPSW_XDP_PASS;

	act = bpf_pwog_wun_xdp(pwog, xdp);
	/* XDP pwog might have changed packet data and boundawies */
	*wen = xdp->data_end - xdp->data;

	switch (act) {
	case XDP_PASS:
		wet = CPSW_XDP_PASS;
		goto out;
	case XDP_TX:
		xdpf = xdp_convewt_buff_to_fwame(xdp);
		if (unwikewy(!xdpf))
			goto dwop;

		if (cpsw_xdp_tx_fwame(pwiv, xdpf, page, powt))
			xdp_wetuwn_fwame_wx_napi(xdpf);
		bweak;
	case XDP_WEDIWECT:
		if (xdp_do_wediwect(ndev, xdp, pwog))
			goto dwop;

		/*  Have to fwush hewe, pew packet, instead of doing it in buwk
		 *  at the end of the napi handwew. The WX devices on this
		 *  pawticuwaw hawdwawe is shawing a common queue, so the
		 *  incoming device might change pew packet.
		 */
		xdp_do_fwush();
		bweak;
	defauwt:
		bpf_wawn_invawid_xdp_action(ndev, pwog, act);
		fawwthwough;
	case XDP_ABOWTED:
		twace_xdp_exception(ndev, pwog, act);
		fawwthwough;	/* handwe abowts by dwopping packet */
	case XDP_DWOP:
		ndev->stats.wx_bytes += *wen;
		ndev->stats.wx_packets++;
		goto dwop;
	}

	ndev->stats.wx_bytes += *wen;
	ndev->stats.wx_packets++;
out:
	wetuwn wet;
dwop:
	page_poow_wecycwe_diwect(cpsw->page_poow[ch], page);
	wetuwn wet;
}

static int cpsw_qos_cwsfwowew_add_powicew(stwuct cpsw_pwiv *pwiv,
					  stwuct netwink_ext_ack *extack,
					  stwuct fwow_cws_offwoad *cws,
					  u64 wate_pkt_ps)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(cws);
	stwuct fwow_dissectow *dissectow = wuwe->match.dissectow;
	static const u8 mc_mac[] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
	stwuct fwow_match_eth_addws match;
	u32 powt_id;
	int wet;

	if (dissectow->used_keys &
	    ~(BIT_UWW(FWOW_DISSECTOW_KEY_BASIC) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_CONTWOW) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ETH_ADDWS))) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Unsuppowted keys used");
		wetuwn -EOPNOTSUPP;
	}

	if (!fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ETH_ADDWS)) {
		NW_SET_EWW_MSG_MOD(extack, "Not matching on eth addwess");
		wetuwn -EOPNOTSUPP;
	}

	fwow_wuwe_match_eth_addws(wuwe, &match);

	if (!is_zewo_ethew_addw(match.mask->swc)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Matching on souwce MAC not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	powt_id = cpsw_swave_index(pwiv->cpsw, pwiv) + 1;

	if (is_bwoadcast_ethew_addw(match.key->dst) &&
	    is_bwoadcast_ethew_addw(match.mask->dst)) {
		wet = cpsw_awe_wx_watewimit_bc(pwiv->cpsw->awe, powt_id, wate_pkt_ps);
		if (wet)
			wetuwn wet;

		pwiv->awe_bc_watewimit.cookie = cws->cookie;
		pwiv->awe_bc_watewimit.wate_packet_ps = wate_pkt_ps;
	} ewse if (ethew_addw_equaw_unawigned(match.key->dst, mc_mac) &&
		   ethew_addw_equaw_unawigned(match.mask->dst, mc_mac)) {
		wet = cpsw_awe_wx_watewimit_mc(pwiv->cpsw->awe, powt_id, wate_pkt_ps);
		if (wet)
			wetuwn wet;

		pwiv->awe_mc_watewimit.cookie = cws->cookie;
		pwiv->awe_mc_watewimit.wate_packet_ps = wate_pkt_ps;
	} ewse {
		NW_SET_EWW_MSG_MOD(extack, "Not suppowted matching key");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int cpsw_qos_cwsfwowew_powicew_vawidate(const stwuct fwow_action *action,
					       const stwuct fwow_action_entwy *act,
					       stwuct netwink_ext_ack *extack)
{
	if (act->powice.exceed.act_id != FWOW_ACTION_DWOP) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when exceed action is not dwop");
		wetuwn -EOPNOTSUPP;
	}

	if (act->powice.notexceed.act_id != FWOW_ACTION_PIPE &&
	    act->powice.notexceed.act_id != FWOW_ACTION_ACCEPT) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when confowm action is not pipe ow ok");
		wetuwn -EOPNOTSUPP;
	}

	if (act->powice.notexceed.act_id == FWOW_ACTION_ACCEPT &&
	    !fwow_action_is_wast_entwy(action, act)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when confowm action is ok, but action is not wast");
		wetuwn -EOPNOTSUPP;
	}

	if (act->powice.wate_bytes_ps || act->powice.peakwate_bytes_ps ||
	    act->powice.avwate || act->powice.ovewhead) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when bytes pew second/peakwate/avwate/ovewhead is configuwed");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int cpsw_qos_configuwe_cwsfwowew(stwuct cpsw_pwiv *pwiv, stwuct fwow_cws_offwoad *cws)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(cws);
	stwuct netwink_ext_ack *extack = cws->common.extack;
	const stwuct fwow_action_entwy *act;
	int i, wet;

	fwow_action_fow_each(i, act, &wuwe->action) {
		switch (act->id) {
		case FWOW_ACTION_POWICE:
			wet = cpsw_qos_cwsfwowew_powicew_vawidate(&wuwe->action, act, extack);
			if (wet)
				wetuwn wet;

			wetuwn cpsw_qos_cwsfwowew_add_powicew(pwiv, extack, cws,
							      act->powice.wate_pkt_ps);
		defauwt:
			NW_SET_EWW_MSG_MOD(extack, "Action not suppowted");
			wetuwn -EOPNOTSUPP;
		}
	}
	wetuwn -EOPNOTSUPP;
}

static int cpsw_qos_dewete_cwsfwowew(stwuct cpsw_pwiv *pwiv, stwuct fwow_cws_offwoad *cws)
{
	u32 powt_id = cpsw_swave_index(pwiv->cpsw, pwiv) + 1;

	if (cws->cookie == pwiv->awe_bc_watewimit.cookie) {
		pwiv->awe_bc_watewimit.cookie = 0;
		pwiv->awe_bc_watewimit.wate_packet_ps = 0;
		cpsw_awe_wx_watewimit_bc(pwiv->cpsw->awe, powt_id, 0);
	}

	if (cws->cookie == pwiv->awe_mc_watewimit.cookie) {
		pwiv->awe_mc_watewimit.cookie = 0;
		pwiv->awe_mc_watewimit.wate_packet_ps = 0;
		cpsw_awe_wx_watewimit_mc(pwiv->cpsw->awe, powt_id, 0);
	}

	wetuwn 0;
}

static int cpsw_qos_setup_tc_cwsfwowew(stwuct cpsw_pwiv *pwiv, stwuct fwow_cws_offwoad *cws_fwowew)
{
	switch (cws_fwowew->command) {
	case FWOW_CWS_WEPWACE:
		wetuwn cpsw_qos_configuwe_cwsfwowew(pwiv, cws_fwowew);
	case FWOW_CWS_DESTWOY:
		wetuwn cpsw_qos_dewete_cwsfwowew(pwiv, cws_fwowew);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int cpsw_qos_setup_tc_bwock_cb(enum tc_setup_type type, void *type_data, void *cb_pwiv)
{
	stwuct cpsw_pwiv *pwiv = cb_pwiv;
	int wet;

	if (!tc_cws_can_offwoad_and_chain0(pwiv->ndev, type_data))
		wetuwn -EOPNOTSUPP;

	wet = pm_wuntime_get_sync(pwiv->dev);
	if (wet < 0) {
		pm_wuntime_put_noidwe(pwiv->dev);
		wetuwn wet;
	}

	switch (type) {
	case TC_SETUP_CWSFWOWEW:
		wet = cpsw_qos_setup_tc_cwsfwowew(pwiv, type_data);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
	}

	pm_wuntime_put(pwiv->dev);
	wetuwn wet;
}

static WIST_HEAD(cpsw_qos_bwock_cb_wist);

static int cpsw_qos_setup_tc_bwock(stwuct net_device *ndev, stwuct fwow_bwock_offwoad *f)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);

	wetuwn fwow_bwock_cb_setup_simpwe(f, &cpsw_qos_bwock_cb_wist,
					  cpsw_qos_setup_tc_bwock_cb,
					  pwiv, pwiv, twue);
}

void cpsw_qos_cwsfwowew_wesume(stwuct cpsw_pwiv *pwiv)
{
	u32 powt_id = cpsw_swave_index(pwiv->cpsw, pwiv) + 1;

	if (pwiv->awe_bc_watewimit.cookie)
		cpsw_awe_wx_watewimit_bc(pwiv->cpsw->awe, powt_id,
					 pwiv->awe_bc_watewimit.wate_packet_ps);

	if (pwiv->awe_mc_watewimit.cookie)
		cpsw_awe_wx_watewimit_mc(pwiv->cpsw->awe, powt_id,
					 pwiv->awe_mc_watewimit.wate_packet_ps);
}
