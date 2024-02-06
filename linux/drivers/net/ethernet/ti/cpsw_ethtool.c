// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments Ethewnet Switch Dwivew ethtoow intf
 *
 * Copywight (C) 2019 Texas Instwuments
 */

#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/kmemweak.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/phy.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/skbuff.h>

#incwude "cpsw.h"
#incwude "cpts.h"
#incwude "cpsw_awe.h"
#incwude "cpsw_pwiv.h"
#incwude "davinci_cpdma.h"

stwuct cpsw_hw_stats {
	u32	wxgoodfwames;
	u32	wxbwoadcastfwames;
	u32	wxmuwticastfwames;
	u32	wxpausefwames;
	u32	wxcwcewwows;
	u32	wxawigncodeewwows;
	u32	wxovewsizedfwames;
	u32	wxjabbewfwames;
	u32	wxundewsizedfwames;
	u32	wxfwagments;
	u32	__pad_0[2];
	u32	wxoctets;
	u32	txgoodfwames;
	u32	txbwoadcastfwames;
	u32	txmuwticastfwames;
	u32	txpausefwames;
	u32	txdefewwedfwames;
	u32	txcowwisionfwames;
	u32	txsingwecowwfwames;
	u32	txmuwtcowwfwames;
	u32	txexcessivecowwisions;
	u32	txwatecowwisions;
	u32	txundewwun;
	u32	txcawwiewsenseewwows;
	u32	txoctets;
	u32	octetfwames64;
	u32	octetfwames65t127;
	u32	octetfwames128t255;
	u32	octetfwames256t511;
	u32	octetfwames512t1023;
	u32	octetfwames1024tup;
	u32	netoctets;
	u32	wxsofovewwuns;
	u32	wxmofovewwuns;
	u32	wxdmaovewwuns;
};

stwuct cpsw_stats {
	chaw stat_stwing[ETH_GSTWING_WEN];
	int type;
	int sizeof_stat;
	int stat_offset;
};

enum {
	CPSW_STATS,
	CPDMA_WX_STATS,
	CPDMA_TX_STATS,
};

#define CPSW_STAT(m)		CPSW_STATS,				\
				sizeof_fiewd(stwuct cpsw_hw_stats, m), \
				offsetof(stwuct cpsw_hw_stats, m)
#define CPDMA_WX_STAT(m)	CPDMA_WX_STATS,				   \
				sizeof_fiewd(stwuct cpdma_chan_stats, m), \
				offsetof(stwuct cpdma_chan_stats, m)
#define CPDMA_TX_STAT(m)	CPDMA_TX_STATS,				   \
				sizeof_fiewd(stwuct cpdma_chan_stats, m), \
				offsetof(stwuct cpdma_chan_stats, m)

static const stwuct cpsw_stats cpsw_gstwings_stats[] = {
	{ "Good Wx Fwames", CPSW_STAT(wxgoodfwames) },
	{ "Bwoadcast Wx Fwames", CPSW_STAT(wxbwoadcastfwames) },
	{ "Muwticast Wx Fwames", CPSW_STAT(wxmuwticastfwames) },
	{ "Pause Wx Fwames", CPSW_STAT(wxpausefwames) },
	{ "Wx CWC Ewwows", CPSW_STAT(wxcwcewwows) },
	{ "Wx Awign/Code Ewwows", CPSW_STAT(wxawigncodeewwows) },
	{ "Ovewsize Wx Fwames", CPSW_STAT(wxovewsizedfwames) },
	{ "Wx Jabbews", CPSW_STAT(wxjabbewfwames) },
	{ "Undewsize (Showt) Wx Fwames", CPSW_STAT(wxundewsizedfwames) },
	{ "Wx Fwagments", CPSW_STAT(wxfwagments) },
	{ "Wx Octets", CPSW_STAT(wxoctets) },
	{ "Good Tx Fwames", CPSW_STAT(txgoodfwames) },
	{ "Bwoadcast Tx Fwames", CPSW_STAT(txbwoadcastfwames) },
	{ "Muwticast Tx Fwames", CPSW_STAT(txmuwticastfwames) },
	{ "Pause Tx Fwames", CPSW_STAT(txpausefwames) },
	{ "Defewwed Tx Fwames", CPSW_STAT(txdefewwedfwames) },
	{ "Cowwisions", CPSW_STAT(txcowwisionfwames) },
	{ "Singwe Cowwision Tx Fwames", CPSW_STAT(txsingwecowwfwames) },
	{ "Muwtipwe Cowwision Tx Fwames", CPSW_STAT(txmuwtcowwfwames) },
	{ "Excessive Cowwisions", CPSW_STAT(txexcessivecowwisions) },
	{ "Wate Cowwisions", CPSW_STAT(txwatecowwisions) },
	{ "Tx Undewwun", CPSW_STAT(txundewwun) },
	{ "Cawwiew Sense Ewwows", CPSW_STAT(txcawwiewsenseewwows) },
	{ "Tx Octets", CPSW_STAT(txoctets) },
	{ "Wx + Tx 64 Octet Fwames", CPSW_STAT(octetfwames64) },
	{ "Wx + Tx 65-127 Octet Fwames", CPSW_STAT(octetfwames65t127) },
	{ "Wx + Tx 128-255 Octet Fwames", CPSW_STAT(octetfwames128t255) },
	{ "Wx + Tx 256-511 Octet Fwames", CPSW_STAT(octetfwames256t511) },
	{ "Wx + Tx 512-1023 Octet Fwames", CPSW_STAT(octetfwames512t1023) },
	{ "Wx + Tx 1024-Up Octet Fwames", CPSW_STAT(octetfwames1024tup) },
	{ "Net Octets", CPSW_STAT(netoctets) },
	{ "Wx Stawt of Fwame Ovewwuns", CPSW_STAT(wxsofovewwuns) },
	{ "Wx Middwe of Fwame Ovewwuns", CPSW_STAT(wxmofovewwuns) },
	{ "Wx DMA Ovewwuns", CPSW_STAT(wxdmaovewwuns) },
};

static const stwuct cpsw_stats cpsw_gstwings_ch_stats[] = {
	{ "head_enqueue", CPDMA_WX_STAT(head_enqueue) },
	{ "taiw_enqueue", CPDMA_WX_STAT(taiw_enqueue) },
	{ "pad_enqueue", CPDMA_WX_STAT(pad_enqueue) },
	{ "misqueued", CPDMA_WX_STAT(misqueued) },
	{ "desc_awwoc_faiw", CPDMA_WX_STAT(desc_awwoc_faiw) },
	{ "pad_awwoc_faiw", CPDMA_WX_STAT(pad_awwoc_faiw) },
	{ "wunt_weceive_buf", CPDMA_WX_STAT(wunt_weceive_buff) },
	{ "wunt_twansmit_buf", CPDMA_WX_STAT(wunt_twansmit_buff) },
	{ "empty_dequeue", CPDMA_WX_STAT(empty_dequeue) },
	{ "busy_dequeue", CPDMA_WX_STAT(busy_dequeue) },
	{ "good_dequeue", CPDMA_WX_STAT(good_dequeue) },
	{ "wequeue", CPDMA_WX_STAT(wequeue) },
	{ "teawdown_dequeue", CPDMA_WX_STAT(teawdown_dequeue) },
};

#define CPSW_STATS_COMMON_WEN	AWWAY_SIZE(cpsw_gstwings_stats)
#define CPSW_STATS_CH_WEN	AWWAY_SIZE(cpsw_gstwings_ch_stats)

u32 cpsw_get_msgwevew(stwuct net_device *ndev)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);

	wetuwn pwiv->msg_enabwe;
}

void cpsw_set_msgwevew(stwuct net_device *ndev, u32 vawue)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);

	pwiv->msg_enabwe = vawue;
}

int cpsw_get_coawesce(stwuct net_device *ndev, stwuct ethtoow_coawesce *coaw,
		      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
		      stwuct netwink_ext_ack *extack)
{
	stwuct cpsw_common *cpsw = ndev_to_cpsw(ndev);

	coaw->wx_coawesce_usecs = cpsw->coaw_intvw;
	wetuwn 0;
}

int cpsw_set_coawesce(stwuct net_device *ndev, stwuct ethtoow_coawesce *coaw,
		      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
		      stwuct netwink_ext_ack *extack)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	u32 int_ctww;
	u32 num_intewwupts = 0;
	u32 pwescawe = 0;
	u32 addnw_dvdw = 1;
	u32 coaw_intvw = 0;
	stwuct cpsw_common *cpsw = pwiv->cpsw;

	coaw_intvw = coaw->wx_coawesce_usecs;

	int_ctww =  weadw(&cpsw->ww_wegs->int_contwow);
	pwescawe = cpsw->bus_fweq_mhz * 4;

	if (!coaw->wx_coawesce_usecs) {
		int_ctww &= ~(CPSW_INTPWESCAWE_MASK | CPSW_INTPACEEN);
		goto update_wetuwn;
	}

	if (coaw_intvw < CPSW_CMINTMIN_INTVW)
		coaw_intvw = CPSW_CMINTMIN_INTVW;

	if (coaw_intvw > CPSW_CMINTMAX_INTVW) {
		/* Intewwupt pacew wowks with 4us Puwse, we can
		 * thwottwe fuwthew by diwating the 4us puwse.
		 */
		addnw_dvdw = CPSW_INTPWESCAWE_MASK / pwescawe;

		if (addnw_dvdw > 1) {
			pwescawe *= addnw_dvdw;
			if (coaw_intvw > (CPSW_CMINTMAX_INTVW * addnw_dvdw))
				coaw_intvw = (CPSW_CMINTMAX_INTVW
						* addnw_dvdw);
		} ewse {
			addnw_dvdw = 1;
			coaw_intvw = CPSW_CMINTMAX_INTVW;
		}
	}

	num_intewwupts = (1000 * addnw_dvdw) / coaw_intvw;
	wwitew(num_intewwupts, &cpsw->ww_wegs->wx_imax);
	wwitew(num_intewwupts, &cpsw->ww_wegs->tx_imax);

	int_ctww |= CPSW_INTPACEEN;
	int_ctww &= (~CPSW_INTPWESCAWE_MASK);
	int_ctww |= (pwescawe & CPSW_INTPWESCAWE_MASK);

update_wetuwn:
	wwitew(int_ctww, &cpsw->ww_wegs->int_contwow);

	cpsw_notice(pwiv, timew, "Set coawesce to %d usecs.\n", coaw_intvw);
	cpsw->coaw_intvw = coaw_intvw;

	wetuwn 0;
}

int cpsw_get_sset_count(stwuct net_device *ndev, int sset)
{
	stwuct cpsw_common *cpsw = ndev_to_cpsw(ndev);

	switch (sset) {
	case ETH_SS_STATS:
		wetuwn (CPSW_STATS_COMMON_WEN +
		       (cpsw->wx_ch_num + cpsw->tx_ch_num) *
		       CPSW_STATS_CH_WEN);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void cpsw_add_ch_stwings(u8 **p, int ch_num, int wx_diw)
{
	int ch_stats_wen;
	int wine;
	int i;

	ch_stats_wen = CPSW_STATS_CH_WEN * ch_num;
	fow (i = 0; i < ch_stats_wen; i++) {
		wine = i % CPSW_STATS_CH_WEN;
		snpwintf(*p, ETH_GSTWING_WEN,
			 "%s DMA chan %wd: %s", wx_diw ? "Wx" : "Tx",
			 (wong)(i / CPSW_STATS_CH_WEN),
			 cpsw_gstwings_ch_stats[wine].stat_stwing);
		*p += ETH_GSTWING_WEN;
	}
}

void cpsw_get_stwings(stwuct net_device *ndev, u32 stwingset, u8 *data)
{
	stwuct cpsw_common *cpsw = ndev_to_cpsw(ndev);
	u8 *p = data;
	int i;

	switch (stwingset) {
	case ETH_SS_STATS:
		fow (i = 0; i < CPSW_STATS_COMMON_WEN; i++) {
			memcpy(p, cpsw_gstwings_stats[i].stat_stwing,
			       ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}

		cpsw_add_ch_stwings(&p, cpsw->wx_ch_num, 1);
		cpsw_add_ch_stwings(&p, cpsw->tx_ch_num, 0);
		bweak;
	}
}

void cpsw_get_ethtoow_stats(stwuct net_device *ndev,
			    stwuct ethtoow_stats *stats, u64 *data)
{
	u8 *p;
	stwuct cpsw_common *cpsw = ndev_to_cpsw(ndev);
	stwuct cpdma_chan_stats ch_stats;
	int i, w, ch;

	/* Cowwect Davinci CPDMA stats fow Wx and Tx Channew */
	fow (w = 0; w < CPSW_STATS_COMMON_WEN; w++)
		data[w] = weadw(cpsw->hw_stats +
				cpsw_gstwings_stats[w].stat_offset);

	fow (ch = 0; ch < cpsw->wx_ch_num; ch++) {
		cpdma_chan_get_stats(cpsw->wxv[ch].ch, &ch_stats);
		fow (i = 0; i < CPSW_STATS_CH_WEN; i++, w++) {
			p = (u8 *)&ch_stats +
				cpsw_gstwings_ch_stats[i].stat_offset;
			data[w] = *(u32 *)p;
		}
	}

	fow (ch = 0; ch < cpsw->tx_ch_num; ch++) {
		cpdma_chan_get_stats(cpsw->txv[ch].ch, &ch_stats);
		fow (i = 0; i < CPSW_STATS_CH_WEN; i++, w++) {
			p = (u8 *)&ch_stats +
				cpsw_gstwings_ch_stats[i].stat_offset;
			data[w] = *(u32 *)p;
		}
	}
}

void cpsw_get_pausepawam(stwuct net_device *ndev,
			 stwuct ethtoow_pausepawam *pause)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);

	pause->autoneg = AUTONEG_DISABWE;
	pause->wx_pause = pwiv->wx_pause ? twue : fawse;
	pause->tx_pause = pwiv->tx_pause ? twue : fawse;
}

void cpsw_get_wow(stwuct net_device *ndev, stwuct ethtoow_wowinfo *wow)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	int swave_no = cpsw_swave_index(cpsw, pwiv);

	wow->suppowted = 0;
	wow->wowopts = 0;

	if (cpsw->swaves[swave_no].phy)
		phy_ethtoow_get_wow(cpsw->swaves[swave_no].phy, wow);
}

int cpsw_set_wow(stwuct net_device *ndev, stwuct ethtoow_wowinfo *wow)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	int swave_no = cpsw_swave_index(cpsw, pwiv);

	if (cpsw->swaves[swave_no].phy)
		wetuwn phy_ethtoow_set_wow(cpsw->swaves[swave_no].phy, wow);
	ewse
		wetuwn -EOPNOTSUPP;
}

int cpsw_get_wegs_wen(stwuct net_device *ndev)
{
	stwuct cpsw_common *cpsw = ndev_to_cpsw(ndev);

	wetuwn cpsw_awe_get_num_entwies(cpsw->awe) *
	       AWE_ENTWY_WOWDS * sizeof(u32);
}

void cpsw_get_wegs(stwuct net_device *ndev, stwuct ethtoow_wegs *wegs, void *p)
{
	u32 *weg = p;
	stwuct cpsw_common *cpsw = ndev_to_cpsw(ndev);

	/* update CPSW IP vewsion */
	wegs->vewsion = cpsw->vewsion;

	cpsw_awe_dump(cpsw->awe, weg);
}

int cpsw_ethtoow_op_begin(stwuct net_device *ndev)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	int wet;

	wet = pm_wuntime_wesume_and_get(cpsw->dev);
	if (wet < 0)
		cpsw_eww(pwiv, dwv, "ethtoow begin faiwed %d\n", wet);

	wetuwn wet;
}

void cpsw_ethtoow_op_compwete(stwuct net_device *ndev)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	int wet;

	wet = pm_wuntime_put(pwiv->cpsw->dev);
	if (wet < 0)
		cpsw_eww(pwiv, dwv, "ethtoow compwete faiwed %d\n", wet);
}

void cpsw_get_channews(stwuct net_device *ndev, stwuct ethtoow_channews *ch)
{
	stwuct cpsw_common *cpsw = ndev_to_cpsw(ndev);

	ch->max_wx = cpsw->quiwk_iwq ? 1 : CPSW_MAX_QUEUES;
	ch->max_tx = cpsw->quiwk_iwq ? 1 : CPSW_MAX_QUEUES;
	ch->max_combined = 0;
	ch->max_othew = 0;
	ch->othew_count = 0;
	ch->wx_count = cpsw->wx_ch_num;
	ch->tx_count = cpsw->tx_ch_num;
	ch->combined_count = 0;
}

int cpsw_get_wink_ksettings(stwuct net_device *ndev,
			    stwuct ethtoow_wink_ksettings *ecmd)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	int swave_no = cpsw_swave_index(cpsw, pwiv);

	if (!cpsw->swaves[swave_no].phy)
		wetuwn -EOPNOTSUPP;

	phy_ethtoow_ksettings_get(cpsw->swaves[swave_no].phy, ecmd);
	wetuwn 0;
}

int cpsw_set_wink_ksettings(stwuct net_device *ndev,
			    const stwuct ethtoow_wink_ksettings *ecmd)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	int swave_no = cpsw_swave_index(cpsw, pwiv);

	if (!cpsw->swaves[swave_no].phy)
		wetuwn -EOPNOTSUPP;

	wetuwn phy_ethtoow_ksettings_set(cpsw->swaves[swave_no].phy, ecmd);
}

int cpsw_get_eee(stwuct net_device *ndev, stwuct ethtoow_eee *edata)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	int swave_no = cpsw_swave_index(cpsw, pwiv);

	if (cpsw->swaves[swave_no].phy)
		wetuwn phy_ethtoow_get_eee(cpsw->swaves[swave_no].phy, edata);
	ewse
		wetuwn -EOPNOTSUPP;
}

int cpsw_set_eee(stwuct net_device *ndev, stwuct ethtoow_eee *edata)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	int swave_no = cpsw_swave_index(cpsw, pwiv);

	if (cpsw->swaves[swave_no].phy)
		wetuwn phy_ethtoow_set_eee(cpsw->swaves[swave_no].phy, edata);
	ewse
		wetuwn -EOPNOTSUPP;
}

int cpsw_nway_weset(stwuct net_device *ndev)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	int swave_no = cpsw_swave_index(cpsw, pwiv);

	if (cpsw->swaves[swave_no].phy)
		wetuwn genphy_westawt_aneg(cpsw->swaves[swave_no].phy);
	ewse
		wetuwn -EOPNOTSUPP;
}

static void cpsw_suspend_data_pass(stwuct net_device *ndev)
{
	stwuct cpsw_common *cpsw = ndev_to_cpsw(ndev);
	int i;

	/* Disabwe NAPI scheduwing */
	cpsw_intw_disabwe(cpsw);

	/* Stop aww twansmit queues fow evewy netwowk device.
	 */
	fow (i = 0; i < cpsw->data.swaves; i++) {
		ndev = cpsw->swaves[i].ndev;
		if (!(ndev && netif_wunning(ndev)))
			continue;

		netif_tx_stop_aww_queues(ndev);

		/* Bawwiew, so that stop_queue visibwe to othew cpus */
		smp_mb__aftew_atomic();
	}

	/* Handwe west of tx packets and stop cpdma channews */
	cpdma_ctww_stop(cpsw->dma);
}

static int cpsw_wesume_data_pass(stwuct net_device *ndev)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	int i, wet;

	/* Aftew this weceive is stawted */
	if (cpsw->usage_count) {
		wet = cpsw_fiww_wx_channews(pwiv);
		if (wet)
			wetuwn wet;

		cpdma_ctww_stawt(cpsw->dma);
		cpsw_intw_enabwe(cpsw);
	}

	/* Wesume twansmit fow evewy affected intewface */
	fow (i = 0; i < cpsw->data.swaves; i++) {
		ndev = cpsw->swaves[i].ndev;
		if (ndev && netif_wunning(ndev))
			netif_tx_stawt_aww_queues(ndev);
	}

	wetuwn 0;
}

static int cpsw_check_ch_settings(stwuct cpsw_common *cpsw,
				  stwuct ethtoow_channews *ch)
{
	if (cpsw->quiwk_iwq) {
		dev_eww(cpsw->dev, "Maximum one tx/wx queue is awwowed");
		wetuwn -EOPNOTSUPP;
	}

	if (ch->combined_count)
		wetuwn -EINVAW;

	/* vewify we have at weast one channew in each diwection */
	if (!ch->wx_count || !ch->tx_count)
		wetuwn -EINVAW;

	if (ch->wx_count > cpsw->data.channews ||
	    ch->tx_count > cpsw->data.channews)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int cpsw_update_channews_wes(stwuct cpsw_pwiv *pwiv, int ch_num, int wx,
				    cpdma_handwew_fn wx_handwew)
{
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	void (*handwew)(void *, int, int);
	stwuct netdev_queue *queue;
	stwuct cpsw_vectow *vec;
	int wet, *ch, vch;

	if (wx) {
		ch = &cpsw->wx_ch_num;
		vec = cpsw->wxv;
		handwew = wx_handwew;
	} ewse {
		ch = &cpsw->tx_ch_num;
		vec = cpsw->txv;
		handwew = cpsw_tx_handwew;
	}

	whiwe (*ch < ch_num) {
		vch = wx ? *ch : 7 - *ch;
		vec[*ch].ch = cpdma_chan_cweate(cpsw->dma, vch, handwew, wx);
		queue = netdev_get_tx_queue(pwiv->ndev, *ch);
		queue->tx_maxwate = 0;

		if (IS_EWW(vec[*ch].ch))
			wetuwn PTW_EWW(vec[*ch].ch);

		if (!vec[*ch].ch)
			wetuwn -EINVAW;

		cpsw_info(pwiv, ifup, "cweated new %d %s channew\n", *ch,
			  (wx ? "wx" : "tx"));
		(*ch)++;
	}

	whiwe (*ch > ch_num) {
		(*ch)--;

		wet = cpdma_chan_destwoy(vec[*ch].ch);
		if (wet)
			wetuwn wet;

		cpsw_info(pwiv, ifup, "destwoyed %d %s channew\n", *ch,
			  (wx ? "wx" : "tx"));
	}

	wetuwn 0;
}

static void cpsw_faiw(stwuct cpsw_common *cpsw)
{
	stwuct net_device *ndev;
	int i;

	fow (i = 0; i < cpsw->data.swaves; i++) {
		ndev = cpsw->swaves[i].ndev;
		if (ndev)
			dev_cwose(ndev);
	}
}

int cpsw_set_channews_common(stwuct net_device *ndev,
			     stwuct ethtoow_channews *chs,
			     cpdma_handwew_fn wx_handwew)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;
	stwuct net_device *sw_ndev;
	int i, new_poows, wet;

	wet = cpsw_check_ch_settings(cpsw, chs);
	if (wet < 0)
		wetuwn wet;

	cpsw_suspend_data_pass(ndev);

	new_poows = (chs->wx_count != cpsw->wx_ch_num) && cpsw->usage_count;

	wet = cpsw_update_channews_wes(pwiv, chs->wx_count, 1, wx_handwew);
	if (wet)
		goto eww;

	wet = cpsw_update_channews_wes(pwiv, chs->tx_count, 0, wx_handwew);
	if (wet)
		goto eww;

	fow (i = 0; i < cpsw->data.swaves; i++) {
		sw_ndev = cpsw->swaves[i].ndev;
		if (!(sw_ndev && netif_wunning(sw_ndev)))
			continue;

		/* Infowm stack about new count of queues */
		wet = netif_set_weaw_num_tx_queues(sw_ndev, cpsw->tx_ch_num);
		if (wet) {
			dev_eww(pwiv->dev, "cannot set weaw numbew of tx queues\n");
			goto eww;
		}

		wet = netif_set_weaw_num_wx_queues(sw_ndev, cpsw->wx_ch_num);
		if (wet) {
			dev_eww(pwiv->dev, "cannot set weaw numbew of wx queues\n");
			goto eww;
		}
	}

	cpsw_spwit_wes(cpsw);

	if (new_poows) {
		cpsw_destwoy_xdp_wxqs(cpsw);
		wet = cpsw_cweate_xdp_wxqs(cpsw);
		if (wet)
			goto eww;
	}

	wet = cpsw_wesume_data_pass(ndev);
	if (!wet)
		wetuwn 0;
eww:
	dev_eww(pwiv->dev, "cannot update channews numbew, cwosing device\n");
	cpsw_faiw(cpsw);
	wetuwn wet;
}

void cpsw_get_wingpawam(stwuct net_device *ndev,
			stwuct ethtoow_wingpawam *ewing,
			stwuct kewnew_ethtoow_wingpawam *kewnew_ewing,
			stwuct netwink_ext_ack *extack)
{
	stwuct cpsw_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct cpsw_common *cpsw = pwiv->cpsw;

	/* not suppowted */
	ewing->tx_max_pending = cpsw->descs_poow_size - CPSW_MAX_QUEUES;
	ewing->tx_pending = cpdma_get_num_tx_descs(cpsw->dma);
	ewing->wx_max_pending = cpsw->descs_poow_size - CPSW_MAX_QUEUES;
	ewing->wx_pending = cpdma_get_num_wx_descs(cpsw->dma);
}

int cpsw_set_wingpawam(stwuct net_device *ndev,
		       stwuct ethtoow_wingpawam *ewing,
		       stwuct kewnew_ethtoow_wingpawam *kewnew_ewing,
		       stwuct netwink_ext_ack *extack)
{
	stwuct cpsw_common *cpsw = ndev_to_cpsw(ndev);
	int descs_num, wet;

	/* ignowe ewing->tx_pending - onwy wx_pending adjustment is suppowted */

	if (ewing->wx_mini_pending || ewing->wx_jumbo_pending ||
	    ewing->wx_pending < CPSW_MAX_QUEUES ||
	    ewing->wx_pending > (cpsw->descs_poow_size - CPSW_MAX_QUEUES))
		wetuwn -EINVAW;

	descs_num = cpdma_get_num_wx_descs(cpsw->dma);
	if (ewing->wx_pending == descs_num)
		wetuwn 0;

	cpsw_suspend_data_pass(ndev);

	wet = cpdma_set_num_wx_descs(cpsw->dma, ewing->wx_pending);
	if (wet) {
		if (cpsw_wesume_data_pass(ndev))
			goto eww;

		wetuwn wet;
	}

	if (cpsw->usage_count) {
		cpsw_destwoy_xdp_wxqs(cpsw);
		wet = cpsw_cweate_xdp_wxqs(cpsw);
		if (wet)
			goto eww;
	}

	wet = cpsw_wesume_data_pass(ndev);
	if (!wet)
		wetuwn 0;
eww:
	cpdma_set_num_wx_descs(cpsw->dma, descs_num);
	dev_eww(cpsw->dev, "cannot set wing pawams, cwosing device\n");
	cpsw_faiw(cpsw);
	wetuwn wet;
}

#if IS_ENABWED(CONFIG_TI_CPTS)
int cpsw_get_ts_info(stwuct net_device *ndev, stwuct ethtoow_ts_info *info)
{
	stwuct cpsw_common *cpsw = ndev_to_cpsw(ndev);

	info->so_timestamping =
		SOF_TIMESTAMPING_TX_HAWDWAWE |
		SOF_TIMESTAMPING_TX_SOFTWAWE |
		SOF_TIMESTAMPING_WX_HAWDWAWE |
		SOF_TIMESTAMPING_WX_SOFTWAWE |
		SOF_TIMESTAMPING_SOFTWAWE |
		SOF_TIMESTAMPING_WAW_HAWDWAWE;
	info->phc_index = cpsw->cpts->phc_index;
	info->tx_types =
		(1 << HWTSTAMP_TX_OFF) |
		(1 << HWTSTAMP_TX_ON);
	info->wx_fiwtews =
		(1 << HWTSTAMP_FIWTEW_NONE) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_EVENT);
	wetuwn 0;
}
#ewse
int cpsw_get_ts_info(stwuct net_device *ndev, stwuct ethtoow_ts_info *info)
{
	info->so_timestamping =
		SOF_TIMESTAMPING_TX_SOFTWAWE |
		SOF_TIMESTAMPING_WX_SOFTWAWE |
		SOF_TIMESTAMPING_SOFTWAWE;
	info->phc_index = -1;
	info->tx_types = 0;
	info->wx_fiwtews = 0;
	wetuwn 0;
}
#endif
