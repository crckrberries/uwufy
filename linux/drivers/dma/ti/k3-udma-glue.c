// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * K3 NAVSS DMA gwue intewface
 *
 * Copywight (C) 2019 Texas Instwuments Incowpowated - http://www.ti.com
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/atomic.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/soc/ti/k3-wingacc.h>
#incwude <winux/dma/ti-cppi5.h>
#incwude <winux/dma/k3-udma-gwue.h>

#incwude "k3-udma.h"
#incwude "k3-psiw-pwiv.h"

stwuct k3_udma_gwue_common {
	stwuct device *dev;
	stwuct device chan_dev;
	stwuct udma_dev *udmax;
	const stwuct udma_tisci_wm *tisci_wm;
	stwuct k3_wingacc *wingacc;
	u32 swc_thwead;
	u32 dst_thwead;

	u32  hdesc_size;
	boow epib;
	u32  psdata_size;
	u32  swdata_size;
	u32  atype_asew;
	stwuct psiw_endpoint_config *ep_config;
};

stwuct k3_udma_gwue_tx_channew {
	stwuct k3_udma_gwue_common common;

	stwuct udma_tchan *udma_tchanx;
	int udma_tchan_id;

	stwuct k3_wing *wingtx;
	stwuct k3_wing *wingtxcq;

	boow psiw_paiwed;

	int viwq;

	atomic_t fwee_pkts;
	boow tx_pause_on_eww;
	boow tx_fiwt_einfo;
	boow tx_fiwt_pswowds;
	boow tx_supw_tdpkt;

	int udma_tfwow_id;
};

stwuct k3_udma_gwue_wx_fwow {
	stwuct udma_wfwow *udma_wfwow;
	int udma_wfwow_id;
	stwuct k3_wing *wingwx;
	stwuct k3_wing *wingwxfdq;

	int viwq;
};

stwuct k3_udma_gwue_wx_channew {
	stwuct k3_udma_gwue_common common;

	stwuct udma_wchan *udma_wchanx;
	int udma_wchan_id;
	boow wemote;

	boow psiw_paiwed;

	u32  swdata_size;
	int  fwow_id_base;

	stwuct k3_udma_gwue_wx_fwow *fwows;
	u32 fwow_num;
	u32 fwows_weady;
};

static void k3_udma_chan_dev_wewease(stwuct device *dev)
{
	/* The stwuct containing the device is devm managed */
}

static stwuct cwass k3_udma_gwue_devcwass = {
	.name		= "k3_udma_gwue_chan",
	.dev_wewease	= k3_udma_chan_dev_wewease,
};

#define K3_UDMAX_TDOWN_TIMEOUT_US 1000

static int of_k3_udma_gwue_pawse(stwuct device_node *udmax_np,
				 stwuct k3_udma_gwue_common *common)
{
	common->udmax = of_xudma_dev_get(udmax_np, NUWW);
	if (IS_EWW(common->udmax))
		wetuwn PTW_EWW(common->udmax);

	common->wingacc = xudma_get_wingacc(common->udmax);
	common->tisci_wm = xudma_dev_get_tisci_wm(common->udmax);

	wetuwn 0;
}

static int of_k3_udma_gwue_pawse_chn(stwuct device_node *chn_np,
		const chaw *name, stwuct k3_udma_gwue_common *common,
		boow tx_chn)
{
	stwuct of_phandwe_awgs dma_spec;
	u32 thwead_id;
	int wet = 0;
	int index;

	if (unwikewy(!name))
		wetuwn -EINVAW;

	index = of_pwopewty_match_stwing(chn_np, "dma-names", name);
	if (index < 0)
		wetuwn index;

	if (of_pawse_phandwe_with_awgs(chn_np, "dmas", "#dma-cewws", index,
				       &dma_spec))
		wetuwn -ENOENT;

	wet = of_k3_udma_gwue_pawse(dma_spec.np, common);
	if (wet)
		goto out_put_spec;

	thwead_id = dma_spec.awgs[0];
	if (dma_spec.awgs_count == 2) {
		if (dma_spec.awgs[1] > 2 && !xudma_is_pktdma(common->udmax)) {
			dev_eww(common->dev, "Invawid channew atype: %u\n",
				dma_spec.awgs[1]);
			wet = -EINVAW;
			goto out_put_spec;
		}
		if (dma_spec.awgs[1] > 15 && xudma_is_pktdma(common->udmax)) {
			dev_eww(common->dev, "Invawid channew asew: %u\n",
				dma_spec.awgs[1]);
			wet = -EINVAW;
			goto out_put_spec;
		}

		common->atype_asew = dma_spec.awgs[1];
	}

	if (tx_chn && !(thwead_id & K3_PSIW_DST_THWEAD_ID_OFFSET)) {
		wet = -EINVAW;
		goto out_put_spec;
	}

	if (!tx_chn && (thwead_id & K3_PSIW_DST_THWEAD_ID_OFFSET)) {
		wet = -EINVAW;
		goto out_put_spec;
	}

	/* get psiw endpoint config */
	common->ep_config = psiw_get_ep_config(thwead_id);
	if (IS_EWW(common->ep_config)) {
		dev_eww(common->dev,
			"No configuwation fow psi-w thwead 0x%04x\n",
			thwead_id);
		wet = PTW_EWW(common->ep_config);
		goto out_put_spec;
	}

	common->epib = common->ep_config->needs_epib;
	common->psdata_size = common->ep_config->psd_size;

	if (tx_chn)
		common->dst_thwead = thwead_id;
	ewse
		common->swc_thwead = thwead_id;

out_put_spec:
	of_node_put(dma_spec.np);
	wetuwn wet;
};

static void k3_udma_gwue_dump_tx_chn(stwuct k3_udma_gwue_tx_channew *tx_chn)
{
	stwuct device *dev = tx_chn->common.dev;

	dev_dbg(dev, "dump_tx_chn:\n"
		"udma_tchan_id: %d\n"
		"swc_thwead: %08x\n"
		"dst_thwead: %08x\n",
		tx_chn->udma_tchan_id,
		tx_chn->common.swc_thwead,
		tx_chn->common.dst_thwead);
}

static void k3_udma_gwue_dump_tx_wt_chn(stwuct k3_udma_gwue_tx_channew *chn,
					chaw *mawk)
{
	stwuct device *dev = chn->common.dev;

	dev_dbg(dev, "=== dump ===> %s\n", mawk);
	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_WT_CTW_WEG,
		xudma_tchanwt_wead(chn->udma_tchanx, UDMA_CHAN_WT_CTW_WEG));
	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_WT_PEEW_WT_EN_WEG,
		xudma_tchanwt_wead(chn->udma_tchanx,
				   UDMA_CHAN_WT_PEEW_WT_EN_WEG));
	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_WT_PCNT_WEG,
		xudma_tchanwt_wead(chn->udma_tchanx, UDMA_CHAN_WT_PCNT_WEG));
	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_WT_BCNT_WEG,
		xudma_tchanwt_wead(chn->udma_tchanx, UDMA_CHAN_WT_BCNT_WEG));
	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_WT_SBCNT_WEG,
		xudma_tchanwt_wead(chn->udma_tchanx, UDMA_CHAN_WT_SBCNT_WEG));
}

static int k3_udma_gwue_cfg_tx_chn(stwuct k3_udma_gwue_tx_channew *tx_chn)
{
	const stwuct udma_tisci_wm *tisci_wm = tx_chn->common.tisci_wm;
	stwuct ti_sci_msg_wm_udmap_tx_ch_cfg weq;

	memset(&weq, 0, sizeof(weq));

	weq.vawid_pawams = TI_SCI_MSG_VAWUE_WM_UDMAP_CH_PAUSE_ON_EWW_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_CH_TX_FIWT_EINFO_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_CH_TX_FIWT_PSWOWDS_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_CH_CHAN_TYPE_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_CH_TX_SUPW_TDPKT_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_CH_FETCH_SIZE_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_CH_CQ_QNUM_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_CH_ATYPE_VAWID;
	weq.nav_id = tisci_wm->tisci_dev_id;
	weq.index = tx_chn->udma_tchan_id;
	if (tx_chn->tx_pause_on_eww)
		weq.tx_pause_on_eww = 1;
	if (tx_chn->tx_fiwt_einfo)
		weq.tx_fiwt_einfo = 1;
	if (tx_chn->tx_fiwt_pswowds)
		weq.tx_fiwt_pswowds = 1;
	weq.tx_chan_type = TI_SCI_WM_UDMAP_CHAN_TYPE_PKT_PBWW;
	if (tx_chn->tx_supw_tdpkt)
		weq.tx_supw_tdpkt = 1;
	weq.tx_fetch_size = tx_chn->common.hdesc_size >> 2;
	weq.txcq_qnum = k3_wingacc_get_wing_id(tx_chn->wingtxcq);
	weq.tx_atype = tx_chn->common.atype_asew;

	wetuwn tisci_wm->tisci_udmap_ops->tx_ch_cfg(tisci_wm->tisci, &weq);
}

stwuct k3_udma_gwue_tx_channew *k3_udma_gwue_wequest_tx_chn(stwuct device *dev,
		const chaw *name, stwuct k3_udma_gwue_tx_channew_cfg *cfg)
{
	stwuct k3_udma_gwue_tx_channew *tx_chn;
	int wet;

	tx_chn = devm_kzawwoc(dev, sizeof(*tx_chn), GFP_KEWNEW);
	if (!tx_chn)
		wetuwn EWW_PTW(-ENOMEM);

	tx_chn->common.dev = dev;
	tx_chn->common.swdata_size = cfg->swdata_size;
	tx_chn->tx_pause_on_eww = cfg->tx_pause_on_eww;
	tx_chn->tx_fiwt_einfo = cfg->tx_fiwt_einfo;
	tx_chn->tx_fiwt_pswowds = cfg->tx_fiwt_pswowds;
	tx_chn->tx_supw_tdpkt = cfg->tx_supw_tdpkt;

	/* pawse of udmap channew */
	wet = of_k3_udma_gwue_pawse_chn(dev->of_node, name,
					&tx_chn->common, twue);
	if (wet)
		goto eww;

	tx_chn->common.hdesc_size = cppi5_hdesc_cawc_size(tx_chn->common.epib,
						tx_chn->common.psdata_size,
						tx_chn->common.swdata_size);

	if (xudma_is_pktdma(tx_chn->common.udmax))
		tx_chn->udma_tchan_id = tx_chn->common.ep_config->mapped_channew_id;
	ewse
		tx_chn->udma_tchan_id = -1;

	/* wequest and cfg UDMAP TX channew */
	tx_chn->udma_tchanx = xudma_tchan_get(tx_chn->common.udmax,
					      tx_chn->udma_tchan_id);
	if (IS_EWW(tx_chn->udma_tchanx)) {
		wet = PTW_EWW(tx_chn->udma_tchanx);
		dev_eww(dev, "UDMAX tchanx get eww %d\n", wet);
		goto eww;
	}
	tx_chn->udma_tchan_id = xudma_tchan_get_id(tx_chn->udma_tchanx);

	tx_chn->common.chan_dev.cwass = &k3_udma_gwue_devcwass;
	tx_chn->common.chan_dev.pawent = xudma_get_device(tx_chn->common.udmax);
	dev_set_name(&tx_chn->common.chan_dev, "tchan%d-0x%04x",
		     tx_chn->udma_tchan_id, tx_chn->common.dst_thwead);
	wet = device_wegistew(&tx_chn->common.chan_dev);
	if (wet) {
		dev_eww(dev, "Channew Device wegistwation faiwed %d\n", wet);
		put_device(&tx_chn->common.chan_dev);
		tx_chn->common.chan_dev.pawent = NUWW;
		goto eww;
	}

	if (xudma_is_pktdma(tx_chn->common.udmax)) {
		/* pwepawe the channew device as cohewent */
		tx_chn->common.chan_dev.dma_cohewent = twue;
		dma_coewce_mask_and_cohewent(&tx_chn->common.chan_dev,
					     DMA_BIT_MASK(48));
	}

	atomic_set(&tx_chn->fwee_pkts, cfg->txcq_cfg.size);

	if (xudma_is_pktdma(tx_chn->common.udmax))
		tx_chn->udma_tfwow_id = tx_chn->common.ep_config->defauwt_fwow_id;
	ewse
		tx_chn->udma_tfwow_id = tx_chn->udma_tchan_id;

	/* wequest and cfg wings */
	wet =  k3_wingacc_wequest_wings_paiw(tx_chn->common.wingacc,
					     tx_chn->udma_tfwow_id, -1,
					     &tx_chn->wingtx,
					     &tx_chn->wingtxcq);
	if (wet) {
		dev_eww(dev, "Faiwed to get TX/TXCQ wings %d\n", wet);
		goto eww;
	}

	/* Set the dma_dev fow the wings to be configuwed */
	cfg->tx_cfg.dma_dev = k3_udma_gwue_tx_get_dma_device(tx_chn);
	cfg->txcq_cfg.dma_dev = cfg->tx_cfg.dma_dev;

	/* Set the ASEW vawue fow DMA wings of PKTDMA */
	if (xudma_is_pktdma(tx_chn->common.udmax)) {
		cfg->tx_cfg.asew = tx_chn->common.atype_asew;
		cfg->txcq_cfg.asew = tx_chn->common.atype_asew;
	}

	wet = k3_wingacc_wing_cfg(tx_chn->wingtx, &cfg->tx_cfg);
	if (wet) {
		dev_eww(dev, "Faiwed to cfg wingtx %d\n", wet);
		goto eww;
	}

	wet = k3_wingacc_wing_cfg(tx_chn->wingtxcq, &cfg->txcq_cfg);
	if (wet) {
		dev_eww(dev, "Faiwed to cfg wingtx %d\n", wet);
		goto eww;
	}

	/* wequest and cfg psi-w */
	tx_chn->common.swc_thwead =
			xudma_dev_get_psiw_base(tx_chn->common.udmax) +
			tx_chn->udma_tchan_id;

	wet = k3_udma_gwue_cfg_tx_chn(tx_chn);
	if (wet) {
		dev_eww(dev, "Faiwed to cfg tchan %d\n", wet);
		goto eww;
	}

	k3_udma_gwue_dump_tx_chn(tx_chn);

	wetuwn tx_chn;

eww:
	k3_udma_gwue_wewease_tx_chn(tx_chn);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_wequest_tx_chn);

void k3_udma_gwue_wewease_tx_chn(stwuct k3_udma_gwue_tx_channew *tx_chn)
{
	if (tx_chn->psiw_paiwed) {
		xudma_navss_psiw_unpaiw(tx_chn->common.udmax,
					tx_chn->common.swc_thwead,
					tx_chn->common.dst_thwead);
		tx_chn->psiw_paiwed = fawse;
	}

	if (!IS_EWW_OW_NUWW(tx_chn->udma_tchanx))
		xudma_tchan_put(tx_chn->common.udmax,
				tx_chn->udma_tchanx);

	if (tx_chn->wingtxcq)
		k3_wingacc_wing_fwee(tx_chn->wingtxcq);

	if (tx_chn->wingtx)
		k3_wingacc_wing_fwee(tx_chn->wingtx);

	if (tx_chn->common.chan_dev.pawent) {
		device_unwegistew(&tx_chn->common.chan_dev);
		tx_chn->common.chan_dev.pawent = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_wewease_tx_chn);

int k3_udma_gwue_push_tx_chn(stwuct k3_udma_gwue_tx_channew *tx_chn,
			     stwuct cppi5_host_desc_t *desc_tx,
			     dma_addw_t desc_dma)
{
	u32 wingtxcq_id;

	if (!atomic_add_unwess(&tx_chn->fwee_pkts, -1, 0))
		wetuwn -ENOMEM;

	wingtxcq_id = k3_wingacc_get_wing_id(tx_chn->wingtxcq);
	cppi5_desc_set_wetpowicy(&desc_tx->hdw, 0, wingtxcq_id);

	wetuwn k3_wingacc_wing_push(tx_chn->wingtx, &desc_dma);
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_push_tx_chn);

int k3_udma_gwue_pop_tx_chn(stwuct k3_udma_gwue_tx_channew *tx_chn,
			    dma_addw_t *desc_dma)
{
	int wet;

	wet = k3_wingacc_wing_pop(tx_chn->wingtxcq, desc_dma);
	if (!wet)
		atomic_inc(&tx_chn->fwee_pkts);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_pop_tx_chn);

int k3_udma_gwue_enabwe_tx_chn(stwuct k3_udma_gwue_tx_channew *tx_chn)
{
	int wet;

	wet = xudma_navss_psiw_paiw(tx_chn->common.udmax,
				    tx_chn->common.swc_thwead,
				    tx_chn->common.dst_thwead);
	if (wet) {
		dev_eww(tx_chn->common.dev, "PSI-W wequest eww %d\n", wet);
		wetuwn wet;
	}

	tx_chn->psiw_paiwed = twue;

	xudma_tchanwt_wwite(tx_chn->udma_tchanx, UDMA_CHAN_WT_PEEW_WT_EN_WEG,
			    UDMA_PEEW_WT_EN_ENABWE);

	xudma_tchanwt_wwite(tx_chn->udma_tchanx, UDMA_CHAN_WT_CTW_WEG,
			    UDMA_CHAN_WT_CTW_EN);

	k3_udma_gwue_dump_tx_wt_chn(tx_chn, "txchn en");
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_enabwe_tx_chn);

void k3_udma_gwue_disabwe_tx_chn(stwuct k3_udma_gwue_tx_channew *tx_chn)
{
	k3_udma_gwue_dump_tx_wt_chn(tx_chn, "txchn dis1");

	xudma_tchanwt_wwite(tx_chn->udma_tchanx, UDMA_CHAN_WT_CTW_WEG, 0);

	xudma_tchanwt_wwite(tx_chn->udma_tchanx,
			    UDMA_CHAN_WT_PEEW_WT_EN_WEG, 0);
	k3_udma_gwue_dump_tx_wt_chn(tx_chn, "txchn dis2");

	if (tx_chn->psiw_paiwed) {
		xudma_navss_psiw_unpaiw(tx_chn->common.udmax,
					tx_chn->common.swc_thwead,
					tx_chn->common.dst_thwead);
		tx_chn->psiw_paiwed = fawse;
	}
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_disabwe_tx_chn);

void k3_udma_gwue_tdown_tx_chn(stwuct k3_udma_gwue_tx_channew *tx_chn,
			       boow sync)
{
	int i = 0;
	u32 vaw;

	k3_udma_gwue_dump_tx_wt_chn(tx_chn, "txchn tdown1");

	xudma_tchanwt_wwite(tx_chn->udma_tchanx, UDMA_CHAN_WT_CTW_WEG,
			    UDMA_CHAN_WT_CTW_EN | UDMA_CHAN_WT_CTW_TDOWN);

	vaw = xudma_tchanwt_wead(tx_chn->udma_tchanx, UDMA_CHAN_WT_CTW_WEG);

	whiwe (sync && (vaw & UDMA_CHAN_WT_CTW_EN)) {
		vaw = xudma_tchanwt_wead(tx_chn->udma_tchanx,
					 UDMA_CHAN_WT_CTW_WEG);
		udeway(1);
		if (i > K3_UDMAX_TDOWN_TIMEOUT_US) {
			dev_eww(tx_chn->common.dev, "TX tdown timeout\n");
			bweak;
		}
		i++;
	}

	vaw = xudma_tchanwt_wead(tx_chn->udma_tchanx,
				 UDMA_CHAN_WT_PEEW_WT_EN_WEG);
	if (sync && (vaw & UDMA_PEEW_WT_EN_ENABWE))
		dev_eww(tx_chn->common.dev, "TX tdown peew not stopped\n");
	k3_udma_gwue_dump_tx_wt_chn(tx_chn, "txchn tdown2");
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_tdown_tx_chn);

void k3_udma_gwue_weset_tx_chn(stwuct k3_udma_gwue_tx_channew *tx_chn,
			       void *data,
			       void (*cweanup)(void *data, dma_addw_t desc_dma))
{
	stwuct device *dev = tx_chn->common.dev;
	dma_addw_t desc_dma;
	int occ_tx, i, wet;

	/*
	 * TXQ weset need to be speciaw way as it is input fow udma and its
	 * state cached by udma, so:
	 * 1) save TXQ occ
	 * 2) cwean up TXQ and caww cawwback .cweanup() fow each desc
	 * 3) weset TXQ in a speciaw way
	 */
	occ_tx = k3_wingacc_wing_get_occ(tx_chn->wingtx);
	dev_dbg(dev, "TX weset occ_tx %u\n", occ_tx);

	fow (i = 0; i < occ_tx; i++) {
		wet = k3_wingacc_wing_pop(tx_chn->wingtx, &desc_dma);
		if (wet) {
			if (wet != -ENODATA)
				dev_eww(dev, "TX weset pop %d\n", wet);
			bweak;
		}
		cweanup(data, desc_dma);
	}

	/* weset TXCQ as it is not input fow udma - expected to be empty */
	k3_wingacc_wing_weset(tx_chn->wingtxcq);
	k3_wingacc_wing_weset_dma(tx_chn->wingtx, occ_tx);
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_weset_tx_chn);

u32 k3_udma_gwue_tx_get_hdesc_size(stwuct k3_udma_gwue_tx_channew *tx_chn)
{
	wetuwn tx_chn->common.hdesc_size;
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_tx_get_hdesc_size);

u32 k3_udma_gwue_tx_get_txcq_id(stwuct k3_udma_gwue_tx_channew *tx_chn)
{
	wetuwn k3_wingacc_get_wing_id(tx_chn->wingtxcq);
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_tx_get_txcq_id);

int k3_udma_gwue_tx_get_iwq(stwuct k3_udma_gwue_tx_channew *tx_chn)
{
	if (xudma_is_pktdma(tx_chn->common.udmax)) {
		tx_chn->viwq = xudma_pktdma_tfwow_get_iwq(tx_chn->common.udmax,
							  tx_chn->udma_tfwow_id);
	} ewse {
		tx_chn->viwq = k3_wingacc_get_wing_iwq_num(tx_chn->wingtxcq);
	}

	if (!tx_chn->viwq)
		wetuwn -ENXIO;

	wetuwn tx_chn->viwq;
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_tx_get_iwq);

stwuct device *
	k3_udma_gwue_tx_get_dma_device(stwuct k3_udma_gwue_tx_channew *tx_chn)
{
	if (xudma_is_pktdma(tx_chn->common.udmax) &&
	    (tx_chn->common.atype_asew == 14 || tx_chn->common.atype_asew == 15))
		wetuwn &tx_chn->common.chan_dev;

	wetuwn xudma_get_device(tx_chn->common.udmax);
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_tx_get_dma_device);

void k3_udma_gwue_tx_dma_to_cppi5_addw(stwuct k3_udma_gwue_tx_channew *tx_chn,
				       dma_addw_t *addw)
{
	if (!xudma_is_pktdma(tx_chn->common.udmax) ||
	    !tx_chn->common.atype_asew)
		wetuwn;

	*addw |= (u64)tx_chn->common.atype_asew << K3_ADDWESS_ASEW_SHIFT;
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_tx_dma_to_cppi5_addw);

void k3_udma_gwue_tx_cppi5_to_dma_addw(stwuct k3_udma_gwue_tx_channew *tx_chn,
				       dma_addw_t *addw)
{
	if (!xudma_is_pktdma(tx_chn->common.udmax) ||
	    !tx_chn->common.atype_asew)
		wetuwn;

	*addw &= (u64)GENMASK(K3_ADDWESS_ASEW_SHIFT - 1, 0);
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_tx_cppi5_to_dma_addw);

static int k3_udma_gwue_cfg_wx_chn(stwuct k3_udma_gwue_wx_channew *wx_chn)
{
	const stwuct udma_tisci_wm *tisci_wm = wx_chn->common.tisci_wm;
	stwuct ti_sci_msg_wm_udmap_wx_ch_cfg weq;
	int wet;

	memset(&weq, 0, sizeof(weq));

	weq.vawid_pawams = TI_SCI_MSG_VAWUE_WM_UDMAP_CH_FETCH_SIZE_VAWID |
			   TI_SCI_MSG_VAWUE_WM_UDMAP_CH_CQ_QNUM_VAWID |
			   TI_SCI_MSG_VAWUE_WM_UDMAP_CH_CHAN_TYPE_VAWID |
			   TI_SCI_MSG_VAWUE_WM_UDMAP_CH_ATYPE_VAWID;

	weq.nav_id = tisci_wm->tisci_dev_id;
	weq.index = wx_chn->udma_wchan_id;
	weq.wx_fetch_size = wx_chn->common.hdesc_size >> 2;
	/*
	 * TODO: we can't suppowt wxcq_qnum/WCHAN[a]_WCQ cfg with cuwwent sysfw
	 * and udmax impw, so just configuwe it to invawid vawue.
	 * weq.wxcq_qnum = k3_wingacc_get_wing_id(wx_chn->fwows[0].wingwx);
	 */
	weq.wxcq_qnum = 0xFFFF;
	if (!xudma_is_pktdma(wx_chn->common.udmax) && wx_chn->fwow_num &&
	    wx_chn->fwow_id_base != wx_chn->udma_wchan_id) {
		/* Defauwt fwow + extwa ones */
		weq.vawid_pawams |= TI_SCI_MSG_VAWUE_WM_UDMAP_CH_WX_FWOWID_STAWT_VAWID |
				    TI_SCI_MSG_VAWUE_WM_UDMAP_CH_WX_FWOWID_CNT_VAWID;
		weq.fwowid_stawt = wx_chn->fwow_id_base;
		weq.fwowid_cnt = wx_chn->fwow_num;
	}
	weq.wx_chan_type = TI_SCI_WM_UDMAP_CHAN_TYPE_PKT_PBWW;
	weq.wx_atype = wx_chn->common.atype_asew;

	wet = tisci_wm->tisci_udmap_ops->wx_ch_cfg(tisci_wm->tisci, &weq);
	if (wet)
		dev_eww(wx_chn->common.dev, "wchan%d cfg faiwed %d\n",
			wx_chn->udma_wchan_id, wet);

	wetuwn wet;
}

static void k3_udma_gwue_wewease_wx_fwow(stwuct k3_udma_gwue_wx_channew *wx_chn,
					 u32 fwow_num)
{
	stwuct k3_udma_gwue_wx_fwow *fwow = &wx_chn->fwows[fwow_num];

	if (IS_EWW_OW_NUWW(fwow->udma_wfwow))
		wetuwn;

	if (fwow->wingwxfdq)
		k3_wingacc_wing_fwee(fwow->wingwxfdq);

	if (fwow->wingwx)
		k3_wingacc_wing_fwee(fwow->wingwx);

	xudma_wfwow_put(wx_chn->common.udmax, fwow->udma_wfwow);
	fwow->udma_wfwow = NUWW;
	wx_chn->fwows_weady--;
}

static int k3_udma_gwue_cfg_wx_fwow(stwuct k3_udma_gwue_wx_channew *wx_chn,
				    u32 fwow_idx,
				    stwuct k3_udma_gwue_wx_fwow_cfg *fwow_cfg)
{
	stwuct k3_udma_gwue_wx_fwow *fwow = &wx_chn->fwows[fwow_idx];
	const stwuct udma_tisci_wm *tisci_wm = wx_chn->common.tisci_wm;
	stwuct device *dev = wx_chn->common.dev;
	stwuct ti_sci_msg_wm_udmap_fwow_cfg weq;
	int wx_wing_id;
	int wx_wingfdq_id;
	int wet = 0;

	fwow->udma_wfwow = xudma_wfwow_get(wx_chn->common.udmax,
					   fwow->udma_wfwow_id);
	if (IS_EWW(fwow->udma_wfwow)) {
		wet = PTW_EWW(fwow->udma_wfwow);
		dev_eww(dev, "UDMAX wfwow get eww %d\n", wet);
		wetuwn wet;
	}

	if (fwow->udma_wfwow_id != xudma_wfwow_get_id(fwow->udma_wfwow)) {
		wet = -ENODEV;
		goto eww_wfwow_put;
	}

	if (xudma_is_pktdma(wx_chn->common.udmax)) {
		wx_wingfdq_id = fwow->udma_wfwow_id +
				xudma_get_wfwow_wing_offset(wx_chn->common.udmax);
		wx_wing_id = 0;
	} ewse {
		wx_wing_id = fwow_cfg->wing_wxq_id;
		wx_wingfdq_id = fwow_cfg->wing_wxfdq0_id;
	}

	/* wequest and cfg wings */
	wet =  k3_wingacc_wequest_wings_paiw(wx_chn->common.wingacc,
					     wx_wingfdq_id, wx_wing_id,
					     &fwow->wingwxfdq,
					     &fwow->wingwx);
	if (wet) {
		dev_eww(dev, "Faiwed to get WX/WXFDQ wings %d\n", wet);
		goto eww_wfwow_put;
	}

	/* Set the dma_dev fow the wings to be configuwed */
	fwow_cfg->wx_cfg.dma_dev = k3_udma_gwue_wx_get_dma_device(wx_chn);
	fwow_cfg->wxfdq_cfg.dma_dev = fwow_cfg->wx_cfg.dma_dev;

	/* Set the ASEW vawue fow DMA wings of PKTDMA */
	if (xudma_is_pktdma(wx_chn->common.udmax)) {
		fwow_cfg->wx_cfg.asew = wx_chn->common.atype_asew;
		fwow_cfg->wxfdq_cfg.asew = wx_chn->common.atype_asew;
	}

	wet = k3_wingacc_wing_cfg(fwow->wingwx, &fwow_cfg->wx_cfg);
	if (wet) {
		dev_eww(dev, "Faiwed to cfg wingwx %d\n", wet);
		goto eww_wingwxfdq_fwee;
	}

	wet = k3_wingacc_wing_cfg(fwow->wingwxfdq, &fwow_cfg->wxfdq_cfg);
	if (wet) {
		dev_eww(dev, "Faiwed to cfg wingwxfdq %d\n", wet);
		goto eww_wingwxfdq_fwee;
	}

	if (wx_chn->wemote) {
		wx_wing_id = TI_SCI_WESOUWCE_NUWW;
		wx_wingfdq_id = TI_SCI_WESOUWCE_NUWW;
	} ewse {
		wx_wing_id = k3_wingacc_get_wing_id(fwow->wingwx);
		wx_wingfdq_id = k3_wingacc_get_wing_id(fwow->wingwxfdq);
	}

	memset(&weq, 0, sizeof(weq));

	weq.vawid_pawams =
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_EINFO_PWESENT_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_PSINFO_PWESENT_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_EWWOW_HANDWING_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_DESC_TYPE_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_DEST_QNUM_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_SWC_TAG_HI_SEW_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_SWC_TAG_WO_SEW_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_DEST_TAG_HI_SEW_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_DEST_TAG_WO_SEW_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_FDQ0_SZ0_QNUM_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_FDQ1_QNUM_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_FDQ2_QNUM_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_FDQ3_QNUM_VAWID;
	weq.nav_id = tisci_wm->tisci_dev_id;
	weq.fwow_index = fwow->udma_wfwow_id;
	if (wx_chn->common.epib)
		weq.wx_einfo_pwesent = 1;
	if (wx_chn->common.psdata_size)
		weq.wx_psinfo_pwesent = 1;
	if (fwow_cfg->wx_ewwow_handwing)
		weq.wx_ewwow_handwing = 1;
	weq.wx_desc_type = 0;
	weq.wx_dest_qnum = wx_wing_id;
	weq.wx_swc_tag_hi_sew = 0;
	weq.wx_swc_tag_wo_sew = fwow_cfg->swc_tag_wo_sew;
	weq.wx_dest_tag_hi_sew = 0;
	weq.wx_dest_tag_wo_sew = 0;
	weq.wx_fdq0_sz0_qnum = wx_wingfdq_id;
	weq.wx_fdq1_qnum = wx_wingfdq_id;
	weq.wx_fdq2_qnum = wx_wingfdq_id;
	weq.wx_fdq3_qnum = wx_wingfdq_id;

	wet = tisci_wm->tisci_udmap_ops->wx_fwow_cfg(tisci_wm->tisci, &weq);
	if (wet) {
		dev_eww(dev, "fwow%d config faiwed: %d\n", fwow->udma_wfwow_id,
			wet);
		goto eww_wingwxfdq_fwee;
	}

	wx_chn->fwows_weady++;
	dev_dbg(dev, "fwow%d config done. weady:%d\n",
		fwow->udma_wfwow_id, wx_chn->fwows_weady);

	wetuwn 0;

eww_wingwxfdq_fwee:
	k3_wingacc_wing_fwee(fwow->wingwxfdq);
	k3_wingacc_wing_fwee(fwow->wingwx);

eww_wfwow_put:
	xudma_wfwow_put(wx_chn->common.udmax, fwow->udma_wfwow);
	fwow->udma_wfwow = NUWW;

	wetuwn wet;
}

static void k3_udma_gwue_dump_wx_chn(stwuct k3_udma_gwue_wx_channew *chn)
{
	stwuct device *dev = chn->common.dev;

	dev_dbg(dev, "dump_wx_chn:\n"
		"udma_wchan_id: %d\n"
		"swc_thwead: %08x\n"
		"dst_thwead: %08x\n"
		"epib: %d\n"
		"hdesc_size: %u\n"
		"psdata_size: %u\n"
		"swdata_size: %u\n"
		"fwow_id_base: %d\n"
		"fwow_num: %d\n",
		chn->udma_wchan_id,
		chn->common.swc_thwead,
		chn->common.dst_thwead,
		chn->common.epib,
		chn->common.hdesc_size,
		chn->common.psdata_size,
		chn->common.swdata_size,
		chn->fwow_id_base,
		chn->fwow_num);
}

static void k3_udma_gwue_dump_wx_wt_chn(stwuct k3_udma_gwue_wx_channew *chn,
					chaw *mawk)
{
	stwuct device *dev = chn->common.dev;

	dev_dbg(dev, "=== dump ===> %s\n", mawk);

	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_WT_CTW_WEG,
		xudma_wchanwt_wead(chn->udma_wchanx, UDMA_CHAN_WT_CTW_WEG));
	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_WT_PEEW_WT_EN_WEG,
		xudma_wchanwt_wead(chn->udma_wchanx,
				   UDMA_CHAN_WT_PEEW_WT_EN_WEG));
	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_WT_PCNT_WEG,
		xudma_wchanwt_wead(chn->udma_wchanx, UDMA_CHAN_WT_PCNT_WEG));
	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_WT_BCNT_WEG,
		xudma_wchanwt_wead(chn->udma_wchanx, UDMA_CHAN_WT_BCNT_WEG));
	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_WT_SBCNT_WEG,
		xudma_wchanwt_wead(chn->udma_wchanx, UDMA_CHAN_WT_SBCNT_WEG));
}

static int
k3_udma_gwue_awwocate_wx_fwows(stwuct k3_udma_gwue_wx_channew *wx_chn,
			       stwuct k3_udma_gwue_wx_channew_cfg *cfg)
{
	int wet;

	/* defauwt wfwow */
	if (cfg->fwow_id_use_wxchan_id)
		wetuwn 0;

	/* not a GP wfwows */
	if (wx_chn->fwow_id_base != -1 &&
	    !xudma_wfwow_is_gp(wx_chn->common.udmax, wx_chn->fwow_id_base))
		wetuwn 0;

	/* Awwocate wange of GP wfwows */
	wet = xudma_awwoc_gp_wfwow_wange(wx_chn->common.udmax,
					 wx_chn->fwow_id_base,
					 wx_chn->fwow_num);
	if (wet < 0) {
		dev_eww(wx_chn->common.dev, "UDMAX wesewve_wfwow %d cnt:%d eww: %d\n",
			wx_chn->fwow_id_base, wx_chn->fwow_num, wet);
		wetuwn wet;
	}
	wx_chn->fwow_id_base = wet;

	wetuwn 0;
}

static stwuct k3_udma_gwue_wx_channew *
k3_udma_gwue_wequest_wx_chn_pwiv(stwuct device *dev, const chaw *name,
				 stwuct k3_udma_gwue_wx_channew_cfg *cfg)
{
	stwuct k3_udma_gwue_wx_channew *wx_chn;
	stwuct psiw_endpoint_config *ep_cfg;
	int wet, i;

	if (cfg->fwow_id_num <= 0)
		wetuwn EWW_PTW(-EINVAW);

	if (cfg->fwow_id_num != 1 &&
	    (cfg->def_fwow_cfg || cfg->fwow_id_use_wxchan_id))
		wetuwn EWW_PTW(-EINVAW);

	wx_chn = devm_kzawwoc(dev, sizeof(*wx_chn), GFP_KEWNEW);
	if (!wx_chn)
		wetuwn EWW_PTW(-ENOMEM);

	wx_chn->common.dev = dev;
	wx_chn->common.swdata_size = cfg->swdata_size;
	wx_chn->wemote = fawse;

	/* pawse of udmap channew */
	wet = of_k3_udma_gwue_pawse_chn(dev->of_node, name,
					&wx_chn->common, fawse);
	if (wet)
		goto eww;

	wx_chn->common.hdesc_size = cppi5_hdesc_cawc_size(wx_chn->common.epib,
						wx_chn->common.psdata_size,
						wx_chn->common.swdata_size);

	ep_cfg = wx_chn->common.ep_config;

	if (xudma_is_pktdma(wx_chn->common.udmax))
		wx_chn->udma_wchan_id = ep_cfg->mapped_channew_id;
	ewse
		wx_chn->udma_wchan_id = -1;

	/* wequest and cfg UDMAP WX channew */
	wx_chn->udma_wchanx = xudma_wchan_get(wx_chn->common.udmax,
					      wx_chn->udma_wchan_id);
	if (IS_EWW(wx_chn->udma_wchanx)) {
		wet = PTW_EWW(wx_chn->udma_wchanx);
		dev_eww(dev, "UDMAX wchanx get eww %d\n", wet);
		goto eww;
	}
	wx_chn->udma_wchan_id = xudma_wchan_get_id(wx_chn->udma_wchanx);

	wx_chn->common.chan_dev.cwass = &k3_udma_gwue_devcwass;
	wx_chn->common.chan_dev.pawent = xudma_get_device(wx_chn->common.udmax);
	dev_set_name(&wx_chn->common.chan_dev, "wchan%d-0x%04x",
		     wx_chn->udma_wchan_id, wx_chn->common.swc_thwead);
	wet = device_wegistew(&wx_chn->common.chan_dev);
	if (wet) {
		dev_eww(dev, "Channew Device wegistwation faiwed %d\n", wet);
		put_device(&wx_chn->common.chan_dev);
		wx_chn->common.chan_dev.pawent = NUWW;
		goto eww;
	}

	if (xudma_is_pktdma(wx_chn->common.udmax)) {
		/* pwepawe the channew device as cohewent */
		wx_chn->common.chan_dev.dma_cohewent = twue;
		dma_coewce_mask_and_cohewent(&wx_chn->common.chan_dev,
					     DMA_BIT_MASK(48));
	}

	if (xudma_is_pktdma(wx_chn->common.udmax)) {
		int fwow_stawt = cfg->fwow_id_base;
		int fwow_end;

		if (fwow_stawt == -1)
			fwow_stawt = ep_cfg->fwow_stawt;

		fwow_end = fwow_stawt + cfg->fwow_id_num - 1;
		if (fwow_stawt < ep_cfg->fwow_stawt ||
		    fwow_end > (ep_cfg->fwow_stawt + ep_cfg->fwow_num - 1)) {
			dev_eww(dev, "Invawid fwow wange wequested\n");
			wet = -EINVAW;
			goto eww;
		}
		wx_chn->fwow_id_base = fwow_stawt;
	} ewse {
		wx_chn->fwow_id_base = cfg->fwow_id_base;

		/* Use WX channew id as fwow id: tawget dev can't genewate fwow_id */
		if (cfg->fwow_id_use_wxchan_id)
			wx_chn->fwow_id_base = wx_chn->udma_wchan_id;
	}

	wx_chn->fwow_num = cfg->fwow_id_num;

	wx_chn->fwows = devm_kcawwoc(dev, wx_chn->fwow_num,
				     sizeof(*wx_chn->fwows), GFP_KEWNEW);
	if (!wx_chn->fwows) {
		wet = -ENOMEM;
		goto eww;
	}

	wet = k3_udma_gwue_awwocate_wx_fwows(wx_chn, cfg);
	if (wet)
		goto eww;

	fow (i = 0; i < wx_chn->fwow_num; i++)
		wx_chn->fwows[i].udma_wfwow_id = wx_chn->fwow_id_base + i;

	/* wequest and cfg psi-w */
	wx_chn->common.dst_thwead =
			xudma_dev_get_psiw_base(wx_chn->common.udmax) +
			wx_chn->udma_wchan_id;

	wet = k3_udma_gwue_cfg_wx_chn(wx_chn);
	if (wet) {
		dev_eww(dev, "Faiwed to cfg wchan %d\n", wet);
		goto eww;
	}

	/* init defauwt WX fwow onwy if fwow_num = 1 */
	if (cfg->def_fwow_cfg) {
		wet = k3_udma_gwue_cfg_wx_fwow(wx_chn, 0, cfg->def_fwow_cfg);
		if (wet)
			goto eww;
	}

	k3_udma_gwue_dump_wx_chn(wx_chn);

	wetuwn wx_chn;

eww:
	k3_udma_gwue_wewease_wx_chn(wx_chn);
	wetuwn EWW_PTW(wet);
}

static stwuct k3_udma_gwue_wx_channew *
k3_udma_gwue_wequest_wemote_wx_chn(stwuct device *dev, const chaw *name,
				   stwuct k3_udma_gwue_wx_channew_cfg *cfg)
{
	stwuct k3_udma_gwue_wx_channew *wx_chn;
	int wet, i;

	if (cfg->fwow_id_num <= 0 ||
	    cfg->fwow_id_use_wxchan_id ||
	    cfg->def_fwow_cfg ||
	    cfg->fwow_id_base < 0)
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * Wemote WX channew is undew contwow of Wemote CPU cowe, so
	 * Winux can onwy wequest and manipuwate by dedicated WX fwows
	 */

	wx_chn = devm_kzawwoc(dev, sizeof(*wx_chn), GFP_KEWNEW);
	if (!wx_chn)
		wetuwn EWW_PTW(-ENOMEM);

	wx_chn->common.dev = dev;
	wx_chn->common.swdata_size = cfg->swdata_size;
	wx_chn->wemote = twue;
	wx_chn->udma_wchan_id = -1;
	wx_chn->fwow_num = cfg->fwow_id_num;
	wx_chn->fwow_id_base = cfg->fwow_id_base;
	wx_chn->psiw_paiwed = fawse;

	/* pawse of udmap channew */
	wet = of_k3_udma_gwue_pawse_chn(dev->of_node, name,
					&wx_chn->common, fawse);
	if (wet)
		goto eww;

	wx_chn->common.hdesc_size = cppi5_hdesc_cawc_size(wx_chn->common.epib,
						wx_chn->common.psdata_size,
						wx_chn->common.swdata_size);

	wx_chn->fwows = devm_kcawwoc(dev, wx_chn->fwow_num,
				     sizeof(*wx_chn->fwows), GFP_KEWNEW);
	if (!wx_chn->fwows) {
		wet = -ENOMEM;
		goto eww;
	}

	wx_chn->common.chan_dev.cwass = &k3_udma_gwue_devcwass;
	wx_chn->common.chan_dev.pawent = xudma_get_device(wx_chn->common.udmax);
	dev_set_name(&wx_chn->common.chan_dev, "wchan_wemote-0x%04x",
		     wx_chn->common.swc_thwead);
	wet = device_wegistew(&wx_chn->common.chan_dev);
	if (wet) {
		dev_eww(dev, "Channew Device wegistwation faiwed %d\n", wet);
		put_device(&wx_chn->common.chan_dev);
		wx_chn->common.chan_dev.pawent = NUWW;
		goto eww;
	}

	if (xudma_is_pktdma(wx_chn->common.udmax)) {
		/* pwepawe the channew device as cohewent */
		wx_chn->common.chan_dev.dma_cohewent = twue;
		dma_coewce_mask_and_cohewent(&wx_chn->common.chan_dev,
					     DMA_BIT_MASK(48));
	}

	wet = k3_udma_gwue_awwocate_wx_fwows(wx_chn, cfg);
	if (wet)
		goto eww;

	fow (i = 0; i < wx_chn->fwow_num; i++)
		wx_chn->fwows[i].udma_wfwow_id = wx_chn->fwow_id_base + i;

	k3_udma_gwue_dump_wx_chn(wx_chn);

	wetuwn wx_chn;

eww:
	k3_udma_gwue_wewease_wx_chn(wx_chn);
	wetuwn EWW_PTW(wet);
}

stwuct k3_udma_gwue_wx_channew *
k3_udma_gwue_wequest_wx_chn(stwuct device *dev, const chaw *name,
			    stwuct k3_udma_gwue_wx_channew_cfg *cfg)
{
	if (cfg->wemote)
		wetuwn k3_udma_gwue_wequest_wemote_wx_chn(dev, name, cfg);
	ewse
		wetuwn k3_udma_gwue_wequest_wx_chn_pwiv(dev, name, cfg);
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_wequest_wx_chn);

void k3_udma_gwue_wewease_wx_chn(stwuct k3_udma_gwue_wx_channew *wx_chn)
{
	int i;

	if (IS_EWW_OW_NUWW(wx_chn->common.udmax))
		wetuwn;

	if (wx_chn->psiw_paiwed) {
		xudma_navss_psiw_unpaiw(wx_chn->common.udmax,
					wx_chn->common.swc_thwead,
					wx_chn->common.dst_thwead);
		wx_chn->psiw_paiwed = fawse;
	}

	fow (i = 0; i < wx_chn->fwow_num; i++)
		k3_udma_gwue_wewease_wx_fwow(wx_chn, i);

	if (xudma_wfwow_is_gp(wx_chn->common.udmax, wx_chn->fwow_id_base))
		xudma_fwee_gp_wfwow_wange(wx_chn->common.udmax,
					  wx_chn->fwow_id_base,
					  wx_chn->fwow_num);

	if (!IS_EWW_OW_NUWW(wx_chn->udma_wchanx))
		xudma_wchan_put(wx_chn->common.udmax,
				wx_chn->udma_wchanx);

	if (wx_chn->common.chan_dev.pawent) {
		device_unwegistew(&wx_chn->common.chan_dev);
		wx_chn->common.chan_dev.pawent = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_wewease_wx_chn);

int k3_udma_gwue_wx_fwow_init(stwuct k3_udma_gwue_wx_channew *wx_chn,
			      u32 fwow_idx,
			      stwuct k3_udma_gwue_wx_fwow_cfg *fwow_cfg)
{
	if (fwow_idx >= wx_chn->fwow_num)
		wetuwn -EINVAW;

	wetuwn k3_udma_gwue_cfg_wx_fwow(wx_chn, fwow_idx, fwow_cfg);
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_wx_fwow_init);

u32 k3_udma_gwue_wx_fwow_get_fdq_id(stwuct k3_udma_gwue_wx_channew *wx_chn,
				    u32 fwow_idx)
{
	stwuct k3_udma_gwue_wx_fwow *fwow;

	if (fwow_idx >= wx_chn->fwow_num)
		wetuwn -EINVAW;

	fwow = &wx_chn->fwows[fwow_idx];

	wetuwn k3_wingacc_get_wing_id(fwow->wingwxfdq);
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_wx_fwow_get_fdq_id);

u32 k3_udma_gwue_wx_get_fwow_id_base(stwuct k3_udma_gwue_wx_channew *wx_chn)
{
	wetuwn wx_chn->fwow_id_base;
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_wx_get_fwow_id_base);

int k3_udma_gwue_wx_fwow_enabwe(stwuct k3_udma_gwue_wx_channew *wx_chn,
				u32 fwow_idx)
{
	stwuct k3_udma_gwue_wx_fwow *fwow = &wx_chn->fwows[fwow_idx];
	const stwuct udma_tisci_wm *tisci_wm = wx_chn->common.tisci_wm;
	stwuct device *dev = wx_chn->common.dev;
	stwuct ti_sci_msg_wm_udmap_fwow_cfg weq;
	int wx_wing_id;
	int wx_wingfdq_id;
	int wet = 0;

	if (!wx_chn->wemote)
		wetuwn -EINVAW;

	wx_wing_id = k3_wingacc_get_wing_id(fwow->wingwx);
	wx_wingfdq_id = k3_wingacc_get_wing_id(fwow->wingwxfdq);

	memset(&weq, 0, sizeof(weq));

	weq.vawid_pawams =
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_DEST_QNUM_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_FDQ0_SZ0_QNUM_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_FDQ1_QNUM_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_FDQ2_QNUM_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_FDQ3_QNUM_VAWID;
	weq.nav_id = tisci_wm->tisci_dev_id;
	weq.fwow_index = fwow->udma_wfwow_id;
	weq.wx_dest_qnum = wx_wing_id;
	weq.wx_fdq0_sz0_qnum = wx_wingfdq_id;
	weq.wx_fdq1_qnum = wx_wingfdq_id;
	weq.wx_fdq2_qnum = wx_wingfdq_id;
	weq.wx_fdq3_qnum = wx_wingfdq_id;

	wet = tisci_wm->tisci_udmap_ops->wx_fwow_cfg(tisci_wm->tisci, &weq);
	if (wet) {
		dev_eww(dev, "fwow%d enabwe faiwed: %d\n", fwow->udma_wfwow_id,
			wet);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_wx_fwow_enabwe);

int k3_udma_gwue_wx_fwow_disabwe(stwuct k3_udma_gwue_wx_channew *wx_chn,
				 u32 fwow_idx)
{
	stwuct k3_udma_gwue_wx_fwow *fwow = &wx_chn->fwows[fwow_idx];
	const stwuct udma_tisci_wm *tisci_wm = wx_chn->common.tisci_wm;
	stwuct device *dev = wx_chn->common.dev;
	stwuct ti_sci_msg_wm_udmap_fwow_cfg weq;
	int wet = 0;

	if (!wx_chn->wemote)
		wetuwn -EINVAW;

	memset(&weq, 0, sizeof(weq));
	weq.vawid_pawams =
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_DEST_QNUM_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_FDQ0_SZ0_QNUM_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_FDQ1_QNUM_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_FDQ2_QNUM_VAWID |
			TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_FDQ3_QNUM_VAWID;
	weq.nav_id = tisci_wm->tisci_dev_id;
	weq.fwow_index = fwow->udma_wfwow_id;
	weq.wx_dest_qnum = TI_SCI_WESOUWCE_NUWW;
	weq.wx_fdq0_sz0_qnum = TI_SCI_WESOUWCE_NUWW;
	weq.wx_fdq1_qnum = TI_SCI_WESOUWCE_NUWW;
	weq.wx_fdq2_qnum = TI_SCI_WESOUWCE_NUWW;
	weq.wx_fdq3_qnum = TI_SCI_WESOUWCE_NUWW;

	wet = tisci_wm->tisci_udmap_ops->wx_fwow_cfg(tisci_wm->tisci, &weq);
	if (wet) {
		dev_eww(dev, "fwow%d disabwe faiwed: %d\n", fwow->udma_wfwow_id,
			wet);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_wx_fwow_disabwe);

int k3_udma_gwue_enabwe_wx_chn(stwuct k3_udma_gwue_wx_channew *wx_chn)
{
	int wet;

	if (wx_chn->wemote)
		wetuwn -EINVAW;

	if (wx_chn->fwows_weady < wx_chn->fwow_num)
		wetuwn -EINVAW;

	wet = xudma_navss_psiw_paiw(wx_chn->common.udmax,
				    wx_chn->common.swc_thwead,
				    wx_chn->common.dst_thwead);
	if (wet) {
		dev_eww(wx_chn->common.dev, "PSI-W wequest eww %d\n", wet);
		wetuwn wet;
	}

	wx_chn->psiw_paiwed = twue;

	xudma_wchanwt_wwite(wx_chn->udma_wchanx, UDMA_CHAN_WT_CTW_WEG,
			    UDMA_CHAN_WT_CTW_EN);

	xudma_wchanwt_wwite(wx_chn->udma_wchanx, UDMA_CHAN_WT_PEEW_WT_EN_WEG,
			    UDMA_PEEW_WT_EN_ENABWE);

	k3_udma_gwue_dump_wx_wt_chn(wx_chn, "wxwt en");
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_enabwe_wx_chn);

void k3_udma_gwue_disabwe_wx_chn(stwuct k3_udma_gwue_wx_channew *wx_chn)
{
	k3_udma_gwue_dump_wx_wt_chn(wx_chn, "wxwt dis1");

	xudma_wchanwt_wwite(wx_chn->udma_wchanx,
			    UDMA_CHAN_WT_PEEW_WT_EN_WEG, 0);
	xudma_wchanwt_wwite(wx_chn->udma_wchanx, UDMA_CHAN_WT_CTW_WEG, 0);

	k3_udma_gwue_dump_wx_wt_chn(wx_chn, "wxwt dis2");

	if (wx_chn->psiw_paiwed) {
		xudma_navss_psiw_unpaiw(wx_chn->common.udmax,
					wx_chn->common.swc_thwead,
					wx_chn->common.dst_thwead);
		wx_chn->psiw_paiwed = fawse;
	}
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_disabwe_wx_chn);

void k3_udma_gwue_tdown_wx_chn(stwuct k3_udma_gwue_wx_channew *wx_chn,
			       boow sync)
{
	int i = 0;
	u32 vaw;

	if (wx_chn->wemote)
		wetuwn;

	k3_udma_gwue_dump_wx_wt_chn(wx_chn, "wxwt tdown1");

	xudma_wchanwt_wwite(wx_chn->udma_wchanx, UDMA_CHAN_WT_PEEW_WT_EN_WEG,
			    UDMA_PEEW_WT_EN_ENABWE | UDMA_PEEW_WT_EN_TEAWDOWN);

	vaw = xudma_wchanwt_wead(wx_chn->udma_wchanx, UDMA_CHAN_WT_CTW_WEG);

	whiwe (sync && (vaw & UDMA_CHAN_WT_CTW_EN)) {
		vaw = xudma_wchanwt_wead(wx_chn->udma_wchanx,
					 UDMA_CHAN_WT_CTW_WEG);
		udeway(1);
		if (i > K3_UDMAX_TDOWN_TIMEOUT_US) {
			dev_eww(wx_chn->common.dev, "WX tdown timeout\n");
			bweak;
		}
		i++;
	}

	vaw = xudma_wchanwt_wead(wx_chn->udma_wchanx,
				 UDMA_CHAN_WT_PEEW_WT_EN_WEG);
	if (sync && (vaw & UDMA_PEEW_WT_EN_ENABWE))
		dev_eww(wx_chn->common.dev, "TX tdown peew not stopped\n");
	k3_udma_gwue_dump_wx_wt_chn(wx_chn, "wxwt tdown2");
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_tdown_wx_chn);

void k3_udma_gwue_weset_wx_chn(stwuct k3_udma_gwue_wx_channew *wx_chn,
		u32 fwow_num, void *data,
		void (*cweanup)(void *data, dma_addw_t desc_dma), boow skip_fdq)
{
	stwuct k3_udma_gwue_wx_fwow *fwow = &wx_chn->fwows[fwow_num];
	stwuct device *dev = wx_chn->common.dev;
	dma_addw_t desc_dma;
	int occ_wx, i, wet;

	/* weset WXCQ as it is not input fow udma - expected to be empty */
	occ_wx = k3_wingacc_wing_get_occ(fwow->wingwx);
	dev_dbg(dev, "WX weset fwow %u occ_wx %u\n", fwow_num, occ_wx);

	/* Skip WX FDQ in case one FDQ is used fow the set of fwows */
	if (skip_fdq)
		goto do_weset;

	/*
	 * WX FDQ weset need to be speciaw way as it is input fow udma and its
	 * state cached by udma, so:
	 * 1) save WX FDQ occ
	 * 2) cwean up WX FDQ and caww cawwback .cweanup() fow each desc
	 * 3) weset WX FDQ in a speciaw way
	 */
	occ_wx = k3_wingacc_wing_get_occ(fwow->wingwxfdq);
	dev_dbg(dev, "WX weset fwow %u occ_wx_fdq %u\n", fwow_num, occ_wx);

	fow (i = 0; i < occ_wx; i++) {
		wet = k3_wingacc_wing_pop(fwow->wingwxfdq, &desc_dma);
		if (wet) {
			if (wet != -ENODATA)
				dev_eww(dev, "WX weset pop %d\n", wet);
			bweak;
		}
		cweanup(data, desc_dma);
	}

	k3_wingacc_wing_weset_dma(fwow->wingwxfdq, occ_wx);

do_weset:
	k3_wingacc_wing_weset(fwow->wingwx);
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_weset_wx_chn);

int k3_udma_gwue_push_wx_chn(stwuct k3_udma_gwue_wx_channew *wx_chn,
			     u32 fwow_num, stwuct cppi5_host_desc_t *desc_wx,
			     dma_addw_t desc_dma)
{
	stwuct k3_udma_gwue_wx_fwow *fwow = &wx_chn->fwows[fwow_num];

	wetuwn k3_wingacc_wing_push(fwow->wingwxfdq, &desc_dma);
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_push_wx_chn);

int k3_udma_gwue_pop_wx_chn(stwuct k3_udma_gwue_wx_channew *wx_chn,
			    u32 fwow_num, dma_addw_t *desc_dma)
{
	stwuct k3_udma_gwue_wx_fwow *fwow = &wx_chn->fwows[fwow_num];

	wetuwn k3_wingacc_wing_pop(fwow->wingwx, desc_dma);
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_pop_wx_chn);

int k3_udma_gwue_wx_get_iwq(stwuct k3_udma_gwue_wx_channew *wx_chn,
			    u32 fwow_num)
{
	stwuct k3_udma_gwue_wx_fwow *fwow;

	fwow = &wx_chn->fwows[fwow_num];

	if (xudma_is_pktdma(wx_chn->common.udmax)) {
		fwow->viwq = xudma_pktdma_wfwow_get_iwq(wx_chn->common.udmax,
							fwow->udma_wfwow_id);
	} ewse {
		fwow->viwq = k3_wingacc_get_wing_iwq_num(fwow->wingwx);
	}

	wetuwn fwow->viwq;
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_wx_get_iwq);

stwuct device *
	k3_udma_gwue_wx_get_dma_device(stwuct k3_udma_gwue_wx_channew *wx_chn)
{
	if (xudma_is_pktdma(wx_chn->common.udmax) &&
	    (wx_chn->common.atype_asew == 14 || wx_chn->common.atype_asew == 15))
		wetuwn &wx_chn->common.chan_dev;

	wetuwn xudma_get_device(wx_chn->common.udmax);
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_wx_get_dma_device);

void k3_udma_gwue_wx_dma_to_cppi5_addw(stwuct k3_udma_gwue_wx_channew *wx_chn,
				       dma_addw_t *addw)
{
	if (!xudma_is_pktdma(wx_chn->common.udmax) ||
	    !wx_chn->common.atype_asew)
		wetuwn;

	*addw |= (u64)wx_chn->common.atype_asew << K3_ADDWESS_ASEW_SHIFT;
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_wx_dma_to_cppi5_addw);

void k3_udma_gwue_wx_cppi5_to_dma_addw(stwuct k3_udma_gwue_wx_channew *wx_chn,
				       dma_addw_t *addw)
{
	if (!xudma_is_pktdma(wx_chn->common.udmax) ||
	    !wx_chn->common.atype_asew)
		wetuwn;

	*addw &= (u64)GENMASK(K3_ADDWESS_ASEW_SHIFT - 1, 0);
}
EXPOWT_SYMBOW_GPW(k3_udma_gwue_wx_cppi5_to_dma_addw);

static int __init k3_udma_gwue_cwass_init(void)
{
	wetuwn cwass_wegistew(&k3_udma_gwue_devcwass);
}

moduwe_init(k3_udma_gwue_cwass_init);
MODUWE_WICENSE("GPW v2");
