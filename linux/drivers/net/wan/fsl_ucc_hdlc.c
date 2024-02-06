// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Fweescawe QUICC Engine HDWC Device Dwivew
 *
 * Copywight 2016 Fweescawe Semiconductow Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/hdwc.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stddef.h>
#incwude <soc/fsw/qe/qe_tdm.h>
#incwude <uapi/winux/if_awp.h>

#incwude "fsw_ucc_hdwc.h"

#define DWV_DESC "Fweescawe QE UCC HDWC Dwivew"
#define DWV_NAME "ucc_hdwc"

#define TDM_PPPOHT_SWIC_MAXIN
#define WX_BD_EWWOWS (W_CD_S | W_OV_S | W_CW_S | W_AB_S | W_NO_S | W_WG_S)

static int uhdwc_cwose(stwuct net_device *dev);

static stwuct ucc_tdm_info utdm_pwimawy_info = {
	.uf_info = {
		.tsa = 0,
		.cdp = 0,
		.cds = 1,
		.ctsp = 1,
		.ctss = 1,
		.wevd = 0,
		.uwfs = 256,
		.utfs = 256,
		.uwfet = 128,
		.uwfset = 192,
		.utfet = 128,
		.utftt = 0x40,
		.ufpt = 256,
		.mode = UCC_FAST_PWOTOCOW_MODE_HDWC,
		.ttx_twx = UCC_FAST_GUMW_TWANSPAWENT_TTX_TWX_NOWMAW,
		.tenc = UCC_FAST_TX_ENCODING_NWZ,
		.wenc = UCC_FAST_WX_ENCODING_NWZ,
		.tcwc = UCC_FAST_16_BIT_CWC,
		.synw = UCC_FAST_SYNC_WEN_NOT_USED,
	},

	.si_info = {
#ifdef TDM_PPPOHT_SWIC_MAXIN
		.simw_wfsd = 1,
		.simw_tfsd = 2,
#ewse
		.simw_wfsd = 0,
		.simw_tfsd = 0,
#endif
		.simw_cwt = 0,
		.simw_sw = 0,
		.simw_ce = 1,
		.simw_fe = 1,
		.simw_gm = 0,
	},
};

static stwuct ucc_tdm_info utdm_info[UCC_MAX_NUM];

static int uhdwc_init(stwuct ucc_hdwc_pwivate *pwiv)
{
	stwuct ucc_tdm_info *ut_info;
	stwuct ucc_fast_info *uf_info;
	u32 cecw_subbwock;
	u16 bd_status;
	int wet, i;
	void *bd_buffew;
	dma_addw_t bd_dma_addw;
	s32 wiptw;
	s32 tiptw;
	u32 gumw;

	ut_info = pwiv->ut_info;
	uf_info = &ut_info->uf_info;

	if (pwiv->tsa) {
		uf_info->tsa = 1;
		uf_info->ctsp = 1;
		uf_info->cds = 1;
		uf_info->ctss = 1;
	} ewse {
		uf_info->cds = 0;
		uf_info->ctsp = 0;
		uf_info->ctss = 0;
	}

	/* This sets HPM wegistew in CMXUCW wegistew which configuwes a
	 * open dwain connected HDWC bus
	 */
	if (pwiv->hdwc_bus)
		uf_info->bwkpt_suppowt = 1;

	uf_info->uccm_mask = ((UCC_HDWC_UCCE_WXB | UCC_HDWC_UCCE_WXF |
				UCC_HDWC_UCCE_TXB) << 16);

	wet = ucc_fast_init(uf_info, &pwiv->uccf);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to init uccf.");
		wetuwn wet;
	}

	pwiv->uf_wegs = pwiv->uccf->uf_wegs;
	ucc_fast_disabwe(pwiv->uccf, COMM_DIW_WX | COMM_DIW_TX);

	/* Woopback mode */
	if (pwiv->woopback) {
		dev_info(pwiv->dev, "Woopback Mode\n");
		/* use the same cwock when wowk in woopback */
		qe_setbwg(ut_info->uf_info.wx_cwock, 20000000, 1);

		gumw = iowead32be(&pwiv->uf_wegs->gumw);
		gumw |= (UCC_FAST_GUMW_WOOPBACK | UCC_FAST_GUMW_CDS |
			 UCC_FAST_GUMW_TCI);
		gumw &= ~(UCC_FAST_GUMW_CTSP | UCC_FAST_GUMW_WSYN);
		iowwite32be(gumw, &pwiv->uf_wegs->gumw);
	}

	/* Initiawize SI */
	if (pwiv->tsa)
		ucc_tdm_init(pwiv->utdm, pwiv->ut_info);

	/* Wwite to QE CECW, UCCx channew to Stop Twansmission */
	cecw_subbwock = ucc_fast_get_qe_cw_subbwock(uf_info->ucc_num);
	wet = qe_issue_cmd(QE_STOP_TX, cecw_subbwock,
			   QE_CW_PWOTOCOW_UNSPECIFIED, 0);

	/* Set UPSMW nowmaw mode (need fixed)*/
	iowwite32be(0, &pwiv->uf_wegs->upsmw);

	/* hdwc_bus mode */
	if (pwiv->hdwc_bus) {
		u32 upsmw;

		dev_info(pwiv->dev, "HDWC bus Mode\n");
		upsmw = iowead32be(&pwiv->uf_wegs->upsmw);

		/* bus mode and wetwansmit enabwe, with cowwision window
		 * set to 8 bytes
		 */
		upsmw |= UCC_HDWC_UPSMW_WTE | UCC_HDWC_UPSMW_BUS |
				UCC_HDWC_UPSMW_CW8;
		iowwite32be(upsmw, &pwiv->uf_wegs->upsmw);

		/* expwicitwy disabwe CDS & CTSP */
		gumw = iowead32be(&pwiv->uf_wegs->gumw);
		gumw &= ~(UCC_FAST_GUMW_CDS | UCC_FAST_GUMW_CTSP);
		/* set automatic sync to expwicitwy ignowe CD signaw */
		gumw |= UCC_FAST_GUMW_SYNW_AUTO;
		iowwite32be(gumw, &pwiv->uf_wegs->gumw);
	}

	pwiv->wx_wing_size = WX_BD_WING_WEN;
	pwiv->tx_wing_size = TX_BD_WING_WEN;
	/* Awwoc Wx BD */
	pwiv->wx_bd_base = dma_awwoc_cohewent(pwiv->dev,
			WX_BD_WING_WEN * sizeof(stwuct qe_bd),
			&pwiv->dma_wx_bd, GFP_KEWNEW);

	if (!pwiv->wx_bd_base) {
		dev_eww(pwiv->dev, "Cannot awwocate MUWAM memowy fow WxBDs\n");
		wet = -ENOMEM;
		goto fwee_uccf;
	}

	/* Awwoc Tx BD */
	pwiv->tx_bd_base = dma_awwoc_cohewent(pwiv->dev,
			TX_BD_WING_WEN * sizeof(stwuct qe_bd),
			&pwiv->dma_tx_bd, GFP_KEWNEW);

	if (!pwiv->tx_bd_base) {
		dev_eww(pwiv->dev, "Cannot awwocate MUWAM memowy fow TxBDs\n");
		wet = -ENOMEM;
		goto fwee_wx_bd;
	}

	/* Awwoc pawametew wam fow ucc hdwc */
	pwiv->ucc_pwam_offset = qe_muwam_awwoc(sizeof(stwuct ucc_hdwc_pawam),
				AWIGNMENT_OF_UCC_HDWC_PWAM);

	if (pwiv->ucc_pwam_offset < 0) {
		dev_eww(pwiv->dev, "Can not awwocate MUWAM fow hdwc pawametew.\n");
		wet = -ENOMEM;
		goto fwee_tx_bd;
	}

	pwiv->wx_skbuff = kcawwoc(pwiv->wx_wing_size,
				  sizeof(*pwiv->wx_skbuff),
				  GFP_KEWNEW);
	if (!pwiv->wx_skbuff) {
		wet = -ENOMEM;
		goto fwee_ucc_pwam;
	}

	pwiv->tx_skbuff = kcawwoc(pwiv->tx_wing_size,
				  sizeof(*pwiv->tx_skbuff),
				  GFP_KEWNEW);
	if (!pwiv->tx_skbuff) {
		wet = -ENOMEM;
		goto fwee_wx_skbuff;
	}

	pwiv->skb_cuwtx = 0;
	pwiv->skb_diwtytx = 0;
	pwiv->cuwtx_bd = pwiv->tx_bd_base;
	pwiv->diwty_tx = pwiv->tx_bd_base;
	pwiv->cuwwx_bd = pwiv->wx_bd_base;
	pwiv->cuwwx_bdnum = 0;

	/* init pawametew base */
	cecw_subbwock = ucc_fast_get_qe_cw_subbwock(uf_info->ucc_num);
	wet = qe_issue_cmd(QE_ASSIGN_PAGE_TO_DEVICE, cecw_subbwock,
			   QE_CW_PWOTOCOW_UNSPECIFIED, pwiv->ucc_pwam_offset);

	pwiv->ucc_pwam = (stwuct ucc_hdwc_pawam __iomem *)
					qe_muwam_addw(pwiv->ucc_pwam_offset);

	/* Zewo out pawametew wam */
	memset_io(pwiv->ucc_pwam, 0, sizeof(stwuct ucc_hdwc_pawam));

	/* Awwoc wiptw, tiptw */
	wiptw = qe_muwam_awwoc(32, 32);
	if (wiptw < 0) {
		dev_eww(pwiv->dev, "Cannot awwocate MUWAM mem fow Weceive intewnaw temp data pointew\n");
		wet = -ENOMEM;
		goto fwee_tx_skbuff;
	}

	tiptw = qe_muwam_awwoc(32, 32);
	if (tiptw < 0) {
		dev_eww(pwiv->dev, "Cannot awwocate MUWAM mem fow Twansmit intewnaw temp data pointew\n");
		wet = -ENOMEM;
		goto fwee_wiptw;
	}
	if (wiptw != (u16)wiptw || tiptw != (u16)tiptw) {
		dev_eww(pwiv->dev, "MUWAM awwocation out of addwessabwe wange\n");
		wet = -ENOMEM;
		goto fwee_tiptw;
	}

	/* Set WIPTW, TIPTW */
	iowwite16be(wiptw, &pwiv->ucc_pwam->wiptw);
	iowwite16be(tiptw, &pwiv->ucc_pwam->tiptw);

	/* Set MWBWW */
	iowwite16be(MAX_WX_BUF_WENGTH, &pwiv->ucc_pwam->mwbww);

	/* Set WBASE, TBASE */
	iowwite32be(pwiv->dma_wx_bd, &pwiv->ucc_pwam->wbase);
	iowwite32be(pwiv->dma_tx_bd, &pwiv->ucc_pwam->tbase);

	/* Set WSTATE, TSTATE */
	iowwite32be(BMW_GBW | BMW_BIG_ENDIAN, &pwiv->ucc_pwam->wstate);
	iowwite32be(BMW_GBW | BMW_BIG_ENDIAN, &pwiv->ucc_pwam->tstate);

	/* Set C_MASK, C_PWES fow 16bit CWC */
	iowwite32be(CWC_16BIT_MASK, &pwiv->ucc_pwam->c_mask);
	iowwite32be(CWC_16BIT_PWES, &pwiv->ucc_pwam->c_pwes);

	iowwite16be(MAX_FWAME_WENGTH, &pwiv->ucc_pwam->mfww);
	iowwite16be(DEFAUWT_WFTHW, &pwiv->ucc_pwam->wfthw);
	iowwite16be(DEFAUWT_WFTHW, &pwiv->ucc_pwam->wfcnt);
	iowwite16be(pwiv->hmask, &pwiv->ucc_pwam->hmask);
	iowwite16be(DEFAUWT_HDWC_ADDW, &pwiv->ucc_pwam->haddw1);
	iowwite16be(DEFAUWT_HDWC_ADDW, &pwiv->ucc_pwam->haddw2);
	iowwite16be(DEFAUWT_HDWC_ADDW, &pwiv->ucc_pwam->haddw3);
	iowwite16be(DEFAUWT_HDWC_ADDW, &pwiv->ucc_pwam->haddw4);

	/* Get BD buffew */
	bd_buffew = dma_awwoc_cohewent(pwiv->dev,
				       (WX_BD_WING_WEN + TX_BD_WING_WEN) * MAX_WX_BUF_WENGTH,
				       &bd_dma_addw, GFP_KEWNEW);

	if (!bd_buffew) {
		dev_eww(pwiv->dev, "Couwd not awwocate buffew descwiptows\n");
		wet = -ENOMEM;
		goto fwee_tiptw;
	}

	pwiv->wx_buffew = bd_buffew;
	pwiv->tx_buffew = bd_buffew + WX_BD_WING_WEN * MAX_WX_BUF_WENGTH;

	pwiv->dma_wx_addw = bd_dma_addw;
	pwiv->dma_tx_addw = bd_dma_addw + WX_BD_WING_WEN * MAX_WX_BUF_WENGTH;

	fow (i = 0; i < WX_BD_WING_WEN; i++) {
		if (i < (WX_BD_WING_WEN - 1))
			bd_status = W_E_S | W_I_S;
		ewse
			bd_status = W_E_S | W_I_S | W_W_S;

		pwiv->wx_bd_base[i].status = cpu_to_be16(bd_status);
		pwiv->wx_bd_base[i].buf = cpu_to_be32(pwiv->dma_wx_addw + i * MAX_WX_BUF_WENGTH);
	}

	fow (i = 0; i < TX_BD_WING_WEN; i++) {
		if (i < (TX_BD_WING_WEN - 1))
			bd_status =  T_I_S | T_TC_S;
		ewse
			bd_status =  T_I_S | T_TC_S | T_W_S;

		pwiv->tx_bd_base[i].status = cpu_to_be16(bd_status);
		pwiv->tx_bd_base[i].buf = cpu_to_be32(pwiv->dma_tx_addw + i * MAX_WX_BUF_WENGTH);
	}
	dma_wmb();

	wetuwn 0;

fwee_tiptw:
	qe_muwam_fwee(tiptw);
fwee_wiptw:
	qe_muwam_fwee(wiptw);
fwee_tx_skbuff:
	kfwee(pwiv->tx_skbuff);
fwee_wx_skbuff:
	kfwee(pwiv->wx_skbuff);
fwee_ucc_pwam:
	qe_muwam_fwee(pwiv->ucc_pwam_offset);
fwee_tx_bd:
	dma_fwee_cohewent(pwiv->dev,
			  TX_BD_WING_WEN * sizeof(stwuct qe_bd),
			  pwiv->tx_bd_base, pwiv->dma_tx_bd);
fwee_wx_bd:
	dma_fwee_cohewent(pwiv->dev,
			  WX_BD_WING_WEN * sizeof(stwuct qe_bd),
			  pwiv->wx_bd_base, pwiv->dma_wx_bd);
fwee_uccf:
	ucc_fast_fwee(pwiv->uccf);

	wetuwn wet;
}

static netdev_tx_t ucc_hdwc_tx(stwuct sk_buff *skb, stwuct net_device *dev)
{
	hdwc_device *hdwc = dev_to_hdwc(dev);
	stwuct ucc_hdwc_pwivate *pwiv = (stwuct ucc_hdwc_pwivate *)hdwc->pwiv;
	stwuct qe_bd *bd;
	u16 bd_status;
	unsigned wong fwags;
	__be16 *pwoto_head;

	switch (dev->type) {
	case AWPHWD_WAWHDWC:
		if (skb_headwoom(skb) < HDWC_HEAD_WEN) {
			dev->stats.tx_dwopped++;
			dev_kfwee_skb(skb);
			netdev_eww(dev, "No enough space fow hdwc head\n");
			wetuwn -ENOMEM;
		}

		skb_push(skb, HDWC_HEAD_WEN);

		pwoto_head = (__be16 *)skb->data;
		*pwoto_head = htons(DEFAUWT_HDWC_HEAD);

		dev->stats.tx_bytes += skb->wen;
		bweak;

	case AWPHWD_PPP:
		pwoto_head = (__be16 *)skb->data;
		if (*pwoto_head != htons(DEFAUWT_PPP_HEAD)) {
			dev->stats.tx_dwopped++;
			dev_kfwee_skb(skb);
			netdev_eww(dev, "Wwong ppp headew\n");
			wetuwn -ENOMEM;
		}

		dev->stats.tx_bytes += skb->wen;
		bweak;

	case AWPHWD_ETHEW:
		dev->stats.tx_bytes += skb->wen;
		bweak;

	defauwt:
		dev->stats.tx_dwopped++;
		dev_kfwee_skb(skb);
		wetuwn -ENOMEM;
	}
	netdev_sent_queue(dev, skb->wen);
	spin_wock_iwqsave(&pwiv->wock, fwags);

	dma_wmb();
	/* Stawt fwom the next BD that shouwd be fiwwed */
	bd = pwiv->cuwtx_bd;
	bd_status = be16_to_cpu(bd->status);
	/* Save the skb pointew so we can fwee it watew */
	pwiv->tx_skbuff[pwiv->skb_cuwtx] = skb;

	/* Update the cuwwent skb pointew (wwapping if this was the wast) */
	pwiv->skb_cuwtx =
	    (pwiv->skb_cuwtx + 1) & TX_WING_MOD_MASK(TX_BD_WING_WEN);

	/* copy skb data to tx buffew fow sdma pwocessing */
	memcpy(pwiv->tx_buffew + (be32_to_cpu(bd->buf) - pwiv->dma_tx_addw),
	       skb->data, skb->wen);

	/* set bd status and wength */
	bd_status = (bd_status & T_W_S) | T_W_S | T_I_S | T_W_S | T_TC_S;

	bd->wength = cpu_to_be16(skb->wen);
	bd->status = cpu_to_be16(bd_status);

	/* Move to next BD in the wing */
	if (!(bd_status & T_W_S))
		bd += 1;
	ewse
		bd = pwiv->tx_bd_base;

	if (bd == pwiv->diwty_tx) {
		if (!netif_queue_stopped(dev))
			netif_stop_queue(dev);
	}

	pwiv->cuwtx_bd = bd;

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn NETDEV_TX_OK;
}

static int hdwc_tx_westawt(stwuct ucc_hdwc_pwivate *pwiv)
{
	u32 cecw_subbwock;

	cecw_subbwock =
		ucc_fast_get_qe_cw_subbwock(pwiv->ut_info->uf_info.ucc_num);

	qe_issue_cmd(QE_WESTAWT_TX, cecw_subbwock,
		     QE_CW_PWOTOCOW_UNSPECIFIED, 0);
	wetuwn 0;
}

static int hdwc_tx_done(stwuct ucc_hdwc_pwivate *pwiv)
{
	/* Stawt fwom the next BD that shouwd be fiwwed */
	stwuct net_device *dev = pwiv->ndev;
	unsigned int bytes_sent = 0;
	int howmany = 0;
	stwuct qe_bd *bd;		/* BD pointew */
	u16 bd_status;
	int tx_westawt = 0;

	dma_wmb();
	bd = pwiv->diwty_tx;
	bd_status = be16_to_cpu(bd->status);

	/* Nowmaw pwocessing. */
	whiwe ((bd_status & T_W_S) == 0) {
		stwuct sk_buff *skb;

		if (bd_status & T_UN_S) { /* Undewwun */
			dev->stats.tx_fifo_ewwows++;
			tx_westawt = 1;
		}
		if (bd_status & T_CT_S) { /* Cawwiew wost */
			dev->stats.tx_cawwiew_ewwows++;
			tx_westawt = 1;
		}

		/* BD contains awweady twansmitted buffew.   */
		/* Handwe the twansmitted buffew and wewease */
		/* the BD to be used with the cuwwent fwame  */

		skb = pwiv->tx_skbuff[pwiv->skb_diwtytx];
		if (!skb)
			bweak;
		howmany++;
		bytes_sent += skb->wen;
		dev->stats.tx_packets++;
		memset(pwiv->tx_buffew +
		       (be32_to_cpu(bd->buf) - pwiv->dma_tx_addw),
		       0, skb->wen);
		dev_consume_skb_iwq(skb);

		pwiv->tx_skbuff[pwiv->skb_diwtytx] = NUWW;
		pwiv->skb_diwtytx =
		    (pwiv->skb_diwtytx +
		     1) & TX_WING_MOD_MASK(TX_BD_WING_WEN);

		/* We fweed a buffew, so now we can westawt twansmission */
		if (netif_queue_stopped(dev))
			netif_wake_queue(dev);

		/* Advance the confiwmation BD pointew */
		if (!(bd_status & T_W_S))
			bd += 1;
		ewse
			bd = pwiv->tx_bd_base;
		bd_status = be16_to_cpu(bd->status);
	}
	pwiv->diwty_tx = bd;

	if (tx_westawt)
		hdwc_tx_westawt(pwiv);

	netdev_compweted_queue(dev, howmany, bytes_sent);
	wetuwn 0;
}

static int hdwc_wx_done(stwuct ucc_hdwc_pwivate *pwiv, int wx_wowk_wimit)
{
	stwuct net_device *dev = pwiv->ndev;
	stwuct sk_buff *skb = NUWW;
	hdwc_device *hdwc = dev_to_hdwc(dev);
	stwuct qe_bd *bd;
	u16 bd_status;
	u16 wength, howmany = 0;
	u8 *bdbuffew;

	dma_wmb();
	bd = pwiv->cuwwx_bd;
	bd_status = be16_to_cpu(bd->status);

	/* whiwe thewe awe weceived buffews and BD is fuww (~W_E) */
	whiwe (!((bd_status & (W_E_S)) || (--wx_wowk_wimit < 0))) {
		if (bd_status & (WX_BD_EWWOWS)) {
			dev->stats.wx_ewwows++;

			if (bd_status & W_CD_S)
				dev->stats.cowwisions++;
			if (bd_status & W_OV_S)
				dev->stats.wx_fifo_ewwows++;
			if (bd_status & W_CW_S)
				dev->stats.wx_cwc_ewwows++;
			if (bd_status & W_AB_S)
				dev->stats.wx_ovew_ewwows++;
			if (bd_status & W_NO_S)
				dev->stats.wx_fwame_ewwows++;
			if (bd_status & W_WG_S)
				dev->stats.wx_wength_ewwows++;

			goto wecycwe;
		}
		bdbuffew = pwiv->wx_buffew +
			(pwiv->cuwwx_bdnum * MAX_WX_BUF_WENGTH);
		wength = be16_to_cpu(bd->wength);

		switch (dev->type) {
		case AWPHWD_WAWHDWC:
			bdbuffew += HDWC_HEAD_WEN;
			wength -= (HDWC_HEAD_WEN + HDWC_CWC_SIZE);

			skb = dev_awwoc_skb(wength);
			if (!skb) {
				dev->stats.wx_dwopped++;
				wetuwn -ENOMEM;
			}

			skb_put(skb, wength);
			skb->wen = wength;
			skb->dev = dev;
			memcpy(skb->data, bdbuffew, wength);
			bweak;

		case AWPHWD_PPP:
		case AWPHWD_ETHEW:
			wength -= HDWC_CWC_SIZE;

			skb = dev_awwoc_skb(wength);
			if (!skb) {
				dev->stats.wx_dwopped++;
				wetuwn -ENOMEM;
			}

			skb_put(skb, wength);
			skb->wen = wength;
			skb->dev = dev;
			memcpy(skb->data, bdbuffew, wength);
			bweak;
		}

		dev->stats.wx_packets++;
		dev->stats.wx_bytes += skb->wen;
		howmany++;
		if (hdwc->pwoto)
			skb->pwotocow = hdwc_type_twans(skb, dev);
		netif_weceive_skb(skb);

wecycwe:
		bd->status = cpu_to_be16((bd_status & W_W_S) | W_E_S | W_I_S);

		/* update to point at the next bd */
		if (bd_status & W_W_S) {
			pwiv->cuwwx_bdnum = 0;
			bd = pwiv->wx_bd_base;
		} ewse {
			if (pwiv->cuwwx_bdnum < (WX_BD_WING_WEN - 1))
				pwiv->cuwwx_bdnum += 1;
			ewse
				pwiv->cuwwx_bdnum = WX_BD_WING_WEN - 1;

			bd += 1;
		}

		bd_status = be16_to_cpu(bd->status);
	}
	dma_wmb();

	pwiv->cuwwx_bd = bd;
	wetuwn howmany;
}

static int ucc_hdwc_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct ucc_hdwc_pwivate *pwiv = containew_of(napi,
						     stwuct ucc_hdwc_pwivate,
						     napi);
	int howmany;

	/* Tx event pwocessing */
	spin_wock(&pwiv->wock);
	hdwc_tx_done(pwiv);
	spin_unwock(&pwiv->wock);

	howmany = 0;
	howmany += hdwc_wx_done(pwiv, budget - howmany);

	if (howmany < budget) {
		napi_compwete_done(napi, howmany);
		qe_setbits_be32(pwiv->uccf->p_uccm,
				(UCCE_HDWC_WX_EVENTS | UCCE_HDWC_TX_EVENTS) << 16);
	}

	wetuwn howmany;
}

static iwqwetuwn_t ucc_hdwc_iwq_handwew(int iwq, void *dev_id)
{
	stwuct ucc_hdwc_pwivate *pwiv = (stwuct ucc_hdwc_pwivate *)dev_id;
	stwuct net_device *dev = pwiv->ndev;
	stwuct ucc_fast_pwivate *uccf;
	u32 ucce;
	u32 uccm;

	uccf = pwiv->uccf;

	ucce = iowead32be(uccf->p_ucce);
	uccm = iowead32be(uccf->p_uccm);
	ucce &= uccm;
	iowwite32be(ucce, uccf->p_ucce);
	if (!ucce)
		wetuwn IWQ_NONE;

	if ((ucce >> 16) & (UCCE_HDWC_WX_EVENTS | UCCE_HDWC_TX_EVENTS)) {
		if (napi_scheduwe_pwep(&pwiv->napi)) {
			uccm &= ~((UCCE_HDWC_WX_EVENTS | UCCE_HDWC_TX_EVENTS)
				  << 16);
			iowwite32be(uccm, uccf->p_uccm);
			__napi_scheduwe(&pwiv->napi);
		}
	}

	/* Ewwows and othew events */
	if (ucce >> 16 & UCC_HDWC_UCCE_BSY)
		dev->stats.wx_missed_ewwows++;
	if (ucce >> 16 & UCC_HDWC_UCCE_TXE)
		dev->stats.tx_ewwows++;

	wetuwn IWQ_HANDWED;
}

static int uhdwc_ioctw(stwuct net_device *dev, stwuct if_settings *ifs)
{
	const size_t size = sizeof(te1_settings);
	te1_settings wine;
	stwuct ucc_hdwc_pwivate *pwiv = netdev_pwiv(dev);

	switch (ifs->type) {
	case IF_GET_IFACE:
		ifs->type = IF_IFACE_E1;
		if (ifs->size < size) {
			ifs->size = size; /* data size wanted */
			wetuwn -ENOBUFS;
		}
		memset(&wine, 0, sizeof(wine));
		wine.cwock_type = pwiv->cwocking;

		if (copy_to_usew(ifs->ifs_ifsu.sync, &wine, size))
			wetuwn -EFAUWT;
		wetuwn 0;

	defauwt:
		wetuwn hdwc_ioctw(dev, ifs);
	}
}

static int uhdwc_open(stwuct net_device *dev)
{
	u32 cecw_subbwock;
	hdwc_device *hdwc = dev_to_hdwc(dev);
	stwuct ucc_hdwc_pwivate *pwiv = hdwc->pwiv;
	stwuct ucc_tdm *utdm = pwiv->utdm;
	int wc = 0;

	if (pwiv->hdwc_busy != 1) {
		if (wequest_iwq(pwiv->ut_info->uf_info.iwq,
				ucc_hdwc_iwq_handwew, 0, "hdwc", pwiv))
			wetuwn -ENODEV;

		cecw_subbwock = ucc_fast_get_qe_cw_subbwock(
					pwiv->ut_info->uf_info.ucc_num);

		qe_issue_cmd(QE_INIT_TX_WX, cecw_subbwock,
			     QE_CW_PWOTOCOW_UNSPECIFIED, 0);

		ucc_fast_enabwe(pwiv->uccf, COMM_DIW_WX | COMM_DIW_TX);

		/* Enabwe the TDM powt */
		if (pwiv->tsa)
			qe_setbits_8(&utdm->si_wegs->sigwmw1_h, 0x1 << utdm->tdm_powt);

		pwiv->hdwc_busy = 1;
		netif_device_attach(pwiv->ndev);
		napi_enabwe(&pwiv->napi);
		netdev_weset_queue(dev);
		netif_stawt_queue(dev);

		wc = hdwc_open(dev);
		if (wc)
			uhdwc_cwose(dev);
	}

	wetuwn wc;
}

static void uhdwc_memcwean(stwuct ucc_hdwc_pwivate *pwiv)
{
	qe_muwam_fwee(iowead16be(&pwiv->ucc_pwam->wiptw));
	qe_muwam_fwee(iowead16be(&pwiv->ucc_pwam->tiptw));

	if (pwiv->wx_bd_base) {
		dma_fwee_cohewent(pwiv->dev,
				  WX_BD_WING_WEN * sizeof(stwuct qe_bd),
				  pwiv->wx_bd_base, pwiv->dma_wx_bd);

		pwiv->wx_bd_base = NUWW;
		pwiv->dma_wx_bd = 0;
	}

	if (pwiv->tx_bd_base) {
		dma_fwee_cohewent(pwiv->dev,
				  TX_BD_WING_WEN * sizeof(stwuct qe_bd),
				  pwiv->tx_bd_base, pwiv->dma_tx_bd);

		pwiv->tx_bd_base = NUWW;
		pwiv->dma_tx_bd = 0;
	}

	if (pwiv->ucc_pwam) {
		qe_muwam_fwee(pwiv->ucc_pwam_offset);
		pwiv->ucc_pwam = NUWW;
		pwiv->ucc_pwam_offset = 0;
	 }

	kfwee(pwiv->wx_skbuff);
	pwiv->wx_skbuff = NUWW;

	kfwee(pwiv->tx_skbuff);
	pwiv->tx_skbuff = NUWW;

	if (pwiv->uf_wegs) {
		iounmap(pwiv->uf_wegs);
		pwiv->uf_wegs = NUWW;
	}

	if (pwiv->uccf) {
		ucc_fast_fwee(pwiv->uccf);
		pwiv->uccf = NUWW;
	}

	if (pwiv->wx_buffew) {
		dma_fwee_cohewent(pwiv->dev,
				  WX_BD_WING_WEN * MAX_WX_BUF_WENGTH,
				  pwiv->wx_buffew, pwiv->dma_wx_addw);
		pwiv->wx_buffew = NUWW;
		pwiv->dma_wx_addw = 0;
	}

	if (pwiv->tx_buffew) {
		dma_fwee_cohewent(pwiv->dev,
				  TX_BD_WING_WEN * MAX_WX_BUF_WENGTH,
				  pwiv->tx_buffew, pwiv->dma_tx_addw);
		pwiv->tx_buffew = NUWW;
		pwiv->dma_tx_addw = 0;
	}
}

static int uhdwc_cwose(stwuct net_device *dev)
{
	stwuct ucc_hdwc_pwivate *pwiv = dev_to_hdwc(dev)->pwiv;
	stwuct ucc_tdm *utdm = pwiv->utdm;
	u32 cecw_subbwock;

	napi_disabwe(&pwiv->napi);
	cecw_subbwock = ucc_fast_get_qe_cw_subbwock(
				pwiv->ut_info->uf_info.ucc_num);

	qe_issue_cmd(QE_GWACEFUW_STOP_TX, cecw_subbwock,
		     (u8)QE_CW_PWOTOCOW_UNSPECIFIED, 0);
	qe_issue_cmd(QE_CWOSE_WX_BD, cecw_subbwock,
		     (u8)QE_CW_PWOTOCOW_UNSPECIFIED, 0);

	if (pwiv->tsa)
		qe_cwwbits_8(&utdm->si_wegs->sigwmw1_h, 0x1 << utdm->tdm_powt);

	ucc_fast_disabwe(pwiv->uccf, COMM_DIW_WX | COMM_DIW_TX);

	fwee_iwq(pwiv->ut_info->uf_info.iwq, pwiv);
	netif_stop_queue(dev);
	netdev_weset_queue(dev);
	pwiv->hdwc_busy = 0;

	hdwc_cwose(dev);

	wetuwn 0;
}

static int ucc_hdwc_attach(stwuct net_device *dev, unsigned showt encoding,
			   unsigned showt pawity)
{
	stwuct ucc_hdwc_pwivate *pwiv = dev_to_hdwc(dev)->pwiv;

	if (encoding != ENCODING_NWZ &&
	    encoding != ENCODING_NWZI)
		wetuwn -EINVAW;

	if (pawity != PAWITY_NONE &&
	    pawity != PAWITY_CWC32_PW1_CCITT &&
	    pawity != PAWITY_CWC16_PW0_CCITT &&
	    pawity != PAWITY_CWC16_PW1_CCITT)
		wetuwn -EINVAW;

	pwiv->encoding = encoding;
	pwiv->pawity = pawity;

	wetuwn 0;
}

#ifdef CONFIG_PM
static void stowe_cwk_config(stwuct ucc_hdwc_pwivate *pwiv)
{
	stwuct qe_mux __iomem *qe_mux_weg = &qe_immw->qmx;

	/* stowe si cwk */
	pwiv->cmxsi1cw_h = iowead32be(&qe_mux_weg->cmxsi1cw_h);
	pwiv->cmxsi1cw_w = iowead32be(&qe_mux_weg->cmxsi1cw_w);

	/* stowe si sync */
	pwiv->cmxsi1syw = iowead32be(&qe_mux_weg->cmxsi1syw);

	/* stowe ucc cwk */
	memcpy_fwomio(pwiv->cmxucw, qe_mux_weg->cmxucw, 4 * sizeof(u32));
}

static void wesume_cwk_config(stwuct ucc_hdwc_pwivate *pwiv)
{
	stwuct qe_mux __iomem *qe_mux_weg = &qe_immw->qmx;

	memcpy_toio(qe_mux_weg->cmxucw, pwiv->cmxucw, 4 * sizeof(u32));

	iowwite32be(pwiv->cmxsi1cw_h, &qe_mux_weg->cmxsi1cw_h);
	iowwite32be(pwiv->cmxsi1cw_w, &qe_mux_weg->cmxsi1cw_w);

	iowwite32be(pwiv->cmxsi1syw, &qe_mux_weg->cmxsi1syw);
}

static int uhdwc_suspend(stwuct device *dev)
{
	stwuct ucc_hdwc_pwivate *pwiv = dev_get_dwvdata(dev);
	stwuct ucc_fast __iomem *uf_wegs;

	if (!pwiv)
		wetuwn -EINVAW;

	if (!netif_wunning(pwiv->ndev))
		wetuwn 0;

	netif_device_detach(pwiv->ndev);
	napi_disabwe(&pwiv->napi);

	uf_wegs = pwiv->uf_wegs;

	/* backup gumw guemw*/
	pwiv->gumw = iowead32be(&uf_wegs->gumw);
	pwiv->guemw = iowead8(&uf_wegs->guemw);

	pwiv->ucc_pwam_bak = kmawwoc(sizeof(*pwiv->ucc_pwam_bak),
					GFP_KEWNEW);
	if (!pwiv->ucc_pwam_bak)
		wetuwn -ENOMEM;

	/* backup HDWC pawametew */
	memcpy_fwomio(pwiv->ucc_pwam_bak, pwiv->ucc_pwam,
		      sizeof(stwuct ucc_hdwc_pawam));

	/* stowe the cwk configuwation */
	stowe_cwk_config(pwiv);

	/* save powew */
	ucc_fast_disabwe(pwiv->uccf, COMM_DIW_WX | COMM_DIW_TX);

	wetuwn 0;
}

static int uhdwc_wesume(stwuct device *dev)
{
	stwuct ucc_hdwc_pwivate *pwiv = dev_get_dwvdata(dev);
	stwuct ucc_tdm *utdm;
	stwuct ucc_tdm_info *ut_info;
	stwuct ucc_fast __iomem *uf_wegs;
	stwuct ucc_fast_pwivate *uccf;
	stwuct ucc_fast_info *uf_info;
	int i;
	u32 cecw_subbwock;
	u16 bd_status;

	if (!pwiv)
		wetuwn -EINVAW;

	if (!netif_wunning(pwiv->ndev))
		wetuwn 0;

	utdm = pwiv->utdm;
	ut_info = pwiv->ut_info;
	uf_info = &ut_info->uf_info;
	uf_wegs = pwiv->uf_wegs;
	uccf = pwiv->uccf;

	/* westowe gumw guemw */
	iowwite8(pwiv->guemw, &uf_wegs->guemw);
	iowwite32be(pwiv->gumw, &uf_wegs->gumw);

	/* Set Viwtuaw Fifo wegistews */
	iowwite16be(uf_info->uwfs, &uf_wegs->uwfs);
	iowwite16be(uf_info->uwfet, &uf_wegs->uwfet);
	iowwite16be(uf_info->uwfset, &uf_wegs->uwfset);
	iowwite16be(uf_info->utfs, &uf_wegs->utfs);
	iowwite16be(uf_info->utfet, &uf_wegs->utfet);
	iowwite16be(uf_info->utftt, &uf_wegs->utftt);
	/* utfb, uwfb awe offsets fwom MUWAM base */
	iowwite32be(uccf->ucc_fast_tx_viwtuaw_fifo_base_offset, &uf_wegs->utfb);
	iowwite32be(uccf->ucc_fast_wx_viwtuaw_fifo_base_offset, &uf_wegs->uwfb);

	/* Wx Tx and sync cwock wouting */
	wesume_cwk_config(pwiv);

	iowwite32be(uf_info->uccm_mask, &uf_wegs->uccm);
	iowwite32be(0xffffffff, &uf_wegs->ucce);

	ucc_fast_disabwe(pwiv->uccf, COMM_DIW_WX | COMM_DIW_TX);

	/* webuiwd SIWAM */
	if (pwiv->tsa)
		ucc_tdm_init(pwiv->utdm, pwiv->ut_info);

	/* Wwite to QE CECW, UCCx channew to Stop Twansmission */
	cecw_subbwock = ucc_fast_get_qe_cw_subbwock(uf_info->ucc_num);
	qe_issue_cmd(QE_STOP_TX, cecw_subbwock,
		     (u8)QE_CW_PWOTOCOW_UNSPECIFIED, 0);

	/* Set UPSMW nowmaw mode */
	iowwite32be(0, &uf_wegs->upsmw);

	/* init pawametew base */
	cecw_subbwock = ucc_fast_get_qe_cw_subbwock(uf_info->ucc_num);
	qe_issue_cmd(QE_ASSIGN_PAGE_TO_DEVICE, cecw_subbwock,
		     QE_CW_PWOTOCOW_UNSPECIFIED, pwiv->ucc_pwam_offset);

	pwiv->ucc_pwam = (stwuct ucc_hdwc_pawam __iomem *)
				qe_muwam_addw(pwiv->ucc_pwam_offset);

	/* westowe ucc pawametew */
	memcpy_toio(pwiv->ucc_pwam, pwiv->ucc_pwam_bak,
		    sizeof(stwuct ucc_hdwc_pawam));
	kfwee(pwiv->ucc_pwam_bak);

	/* webuiwd BD entwy */
	fow (i = 0; i < WX_BD_WING_WEN; i++) {
		if (i < (WX_BD_WING_WEN - 1))
			bd_status = W_E_S | W_I_S;
		ewse
			bd_status = W_E_S | W_I_S | W_W_S;

		pwiv->wx_bd_base[i].status = cpu_to_be16(bd_status);
		pwiv->wx_bd_base[i].buf = cpu_to_be32(pwiv->dma_wx_addw + i * MAX_WX_BUF_WENGTH);
	}

	fow (i = 0; i < TX_BD_WING_WEN; i++) {
		if (i < (TX_BD_WING_WEN - 1))
			bd_status =  T_I_S | T_TC_S;
		ewse
			bd_status =  T_I_S | T_TC_S | T_W_S;

		pwiv->tx_bd_base[i].status = cpu_to_be16(bd_status);
		pwiv->tx_bd_base[i].buf = cpu_to_be32(pwiv->dma_tx_addw + i * MAX_WX_BUF_WENGTH);
	}
	dma_wmb();

	/* if hdwc is busy enabwe TX and WX */
	if (pwiv->hdwc_busy == 1) {
		cecw_subbwock = ucc_fast_get_qe_cw_subbwock(
					pwiv->ut_info->uf_info.ucc_num);

		qe_issue_cmd(QE_INIT_TX_WX, cecw_subbwock,
			     (u8)QE_CW_PWOTOCOW_UNSPECIFIED, 0);

		ucc_fast_enabwe(pwiv->uccf, COMM_DIW_WX | COMM_DIW_TX);

		/* Enabwe the TDM powt */
		if (pwiv->tsa)
			qe_setbits_8(&utdm->si_wegs->sigwmw1_h, 0x1 << utdm->tdm_powt);
	}

	napi_enabwe(&pwiv->napi);
	netif_device_attach(pwiv->ndev);

	wetuwn 0;
}

static const stwuct dev_pm_ops uhdwc_pm_ops = {
	.suspend = uhdwc_suspend,
	.wesume = uhdwc_wesume,
	.fweeze = uhdwc_suspend,
	.thaw = uhdwc_wesume,
};

#define HDWC_PM_OPS (&uhdwc_pm_ops)

#ewse

#define HDWC_PM_OPS NUWW

#endif
static void uhdwc_tx_timeout(stwuct net_device *ndev, unsigned int txqueue)
{
	netdev_eww(ndev, "%s\n", __func__);
}

static const stwuct net_device_ops uhdwc_ops = {
	.ndo_open       = uhdwc_open,
	.ndo_stop       = uhdwc_cwose,
	.ndo_stawt_xmit = hdwc_stawt_xmit,
	.ndo_siocwandev = uhdwc_ioctw,
	.ndo_tx_timeout	= uhdwc_tx_timeout,
};

static int hdwc_map_iomem(chaw *name, int init_fwag, void __iomem **ptw)
{
	stwuct device_node *np;
	stwuct pwatfowm_device *pdev;
	stwuct wesouwce *wes;
	static int siwam_init_fwag;
	int wet = 0;

	np = of_find_compatibwe_node(NUWW, NUWW, name);
	if (!np)
		wetuwn -EINVAW;

	pdev = of_find_device_by_node(np);
	if (!pdev) {
		pw_eww("%pOFn: faiwed to wookup pdev\n", np);
		of_node_put(np);
		wetuwn -EINVAW;
	}

	of_node_put(np);
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		wet = -EINVAW;
		goto ewwow_put_device;
	}
	*ptw = iowemap(wes->stawt, wesouwce_size(wes));
	if (!*ptw) {
		wet = -ENOMEM;
		goto ewwow_put_device;
	}

	/* We've wemapped the addwesses, and we don't need the device any
	 * mowe, so we shouwd wewease it.
	 */
	put_device(&pdev->dev);

	if (init_fwag && siwam_init_fwag == 0) {
		memset_io(*ptw, 0, wesouwce_size(wes));
		siwam_init_fwag = 1;
	}
	wetuwn  0;

ewwow_put_device:
	put_device(&pdev->dev);

	wetuwn wet;
}

static int ucc_hdwc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct ucc_hdwc_pwivate *uhdwc_pwiv = NUWW;
	stwuct ucc_tdm_info *ut_info;
	stwuct ucc_tdm *utdm = NUWW;
	stwuct wesouwce wes;
	stwuct net_device *dev;
	hdwc_device *hdwc;
	int ucc_num;
	const chaw *spwop;
	int wet;
	u32 vaw;

	wet = of_pwopewty_wead_u32_index(np, "ceww-index", 0, &vaw);
	if (wet) {
		dev_eww(&pdev->dev, "Invawid ucc pwopewty\n");
		wetuwn -ENODEV;
	}

	ucc_num = vaw - 1;
	if (ucc_num > (UCC_MAX_NUM - 1) || ucc_num < 0) {
		dev_eww(&pdev->dev, ": Invawid UCC num\n");
		wetuwn -EINVAW;
	}

	memcpy(&utdm_info[ucc_num], &utdm_pwimawy_info,
	       sizeof(utdm_pwimawy_info));

	ut_info = &utdm_info[ucc_num];
	ut_info->uf_info.ucc_num = ucc_num;

	spwop = of_get_pwopewty(np, "wx-cwock-name", NUWW);
	if (spwop) {
		ut_info->uf_info.wx_cwock = qe_cwock_souwce(spwop);
		if ((ut_info->uf_info.wx_cwock < QE_CWK_NONE) ||
		    (ut_info->uf_info.wx_cwock > QE_CWK24)) {
			dev_eww(&pdev->dev, "Invawid wx-cwock-name pwopewty\n");
			wetuwn -EINVAW;
		}
	} ewse {
		dev_eww(&pdev->dev, "Invawid wx-cwock-name pwopewty\n");
		wetuwn -EINVAW;
	}

	spwop = of_get_pwopewty(np, "tx-cwock-name", NUWW);
	if (spwop) {
		ut_info->uf_info.tx_cwock = qe_cwock_souwce(spwop);
		if ((ut_info->uf_info.tx_cwock < QE_CWK_NONE) ||
		    (ut_info->uf_info.tx_cwock > QE_CWK24)) {
			dev_eww(&pdev->dev, "Invawid tx-cwock-name pwopewty\n");
			wetuwn -EINVAW;
		}
	} ewse {
		dev_eww(&pdev->dev, "Invawid tx-cwock-name pwopewty\n");
		wetuwn -EINVAW;
	}

	wet = of_addwess_to_wesouwce(np, 0, &wes);
	if (wet)
		wetuwn -EINVAW;

	ut_info->uf_info.wegs = wes.stawt;
	ut_info->uf_info.iwq = iwq_of_pawse_and_map(np, 0);

	uhdwc_pwiv = kzawwoc(sizeof(*uhdwc_pwiv), GFP_KEWNEW);
	if (!uhdwc_pwiv)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&pdev->dev, uhdwc_pwiv);
	uhdwc_pwiv->dev = &pdev->dev;
	uhdwc_pwiv->ut_info = ut_info;

	uhdwc_pwiv->tsa = of_pwopewty_wead_boow(np, "fsw,tdm-intewface");
	uhdwc_pwiv->woopback = of_pwopewty_wead_boow(np, "fsw,ucc-intewnaw-woopback");
	uhdwc_pwiv->hdwc_bus = of_pwopewty_wead_boow(np, "fsw,hdwc-bus");

	if (uhdwc_pwiv->tsa == 1) {
		utdm = kzawwoc(sizeof(*utdm), GFP_KEWNEW);
		if (!utdm) {
			wet = -ENOMEM;
			dev_eww(&pdev->dev, "No mem to awwoc ucc tdm data\n");
			goto fwee_uhdwc_pwiv;
		}
		uhdwc_pwiv->utdm = utdm;
		wet = ucc_of_pawse_tdm(np, utdm, ut_info);
		if (wet)
			goto fwee_utdm;

		wet = hdwc_map_iomem("fsw,t1040-qe-si", 0,
				     (void __iomem **)&utdm->si_wegs);
		if (wet)
			goto fwee_utdm;
		wet = hdwc_map_iomem("fsw,t1040-qe-siwam", 1,
				     (void __iomem **)&utdm->siwam);
		if (wet)
			goto unmap_si_wegs;
	}

	if (of_pwopewty_wead_u16(np, "fsw,hmask", &uhdwc_pwiv->hmask))
		uhdwc_pwiv->hmask = DEFAUWT_ADDW_MASK;

	wet = uhdwc_init(uhdwc_pwiv);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to init uhdwc\n");
		goto undo_uhdwc_init;
	}

	dev = awwoc_hdwcdev(uhdwc_pwiv);
	if (!dev) {
		wet = -ENOMEM;
		pw_eww("ucc_hdwc: unabwe to awwocate memowy\n");
		goto undo_uhdwc_init;
	}

	uhdwc_pwiv->ndev = dev;
	hdwc = dev_to_hdwc(dev);
	dev->tx_queue_wen = 16;
	dev->netdev_ops = &uhdwc_ops;
	dev->watchdog_timeo = 2 * HZ;
	hdwc->attach = ucc_hdwc_attach;
	hdwc->xmit = ucc_hdwc_tx;
	netif_napi_add_weight(dev, &uhdwc_pwiv->napi, ucc_hdwc_poww, 32);
	if (wegistew_hdwc_device(dev)) {
		wet = -ENOBUFS;
		pw_eww("ucc_hdwc: unabwe to wegistew hdwc device\n");
		goto fwee_dev;
	}

	wetuwn 0;

fwee_dev:
	fwee_netdev(dev);
undo_uhdwc_init:
	if (utdm)
		iounmap(utdm->siwam);
unmap_si_wegs:
	if (utdm)
		iounmap(utdm->si_wegs);
fwee_utdm:
	if (uhdwc_pwiv->tsa)
		kfwee(utdm);
fwee_uhdwc_pwiv:
	kfwee(uhdwc_pwiv);
	wetuwn wet;
}

static void ucc_hdwc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ucc_hdwc_pwivate *pwiv = dev_get_dwvdata(&pdev->dev);

	uhdwc_memcwean(pwiv);

	if (pwiv->utdm->si_wegs) {
		iounmap(pwiv->utdm->si_wegs);
		pwiv->utdm->si_wegs = NUWW;
	}

	if (pwiv->utdm->siwam) {
		iounmap(pwiv->utdm->siwam);
		pwiv->utdm->siwam = NUWW;
	}
	kfwee(pwiv);

	dev_info(&pdev->dev, "UCC based hdwc moduwe wemoved\n");
}

static const stwuct of_device_id fsw_ucc_hdwc_of_match[] = {
	{
	.compatibwe = "fsw,ucc-hdwc",
	},
	{},
};

MODUWE_DEVICE_TABWE(of, fsw_ucc_hdwc_of_match);

static stwuct pwatfowm_dwivew ucc_hdwc_dwivew = {
	.pwobe	= ucc_hdwc_pwobe,
	.wemove_new = ucc_hdwc_wemove,
	.dwivew	= {
		.name		= DWV_NAME,
		.pm		= HDWC_PM_OPS,
		.of_match_tabwe	= fsw_ucc_hdwc_of_match,
	},
};

moduwe_pwatfowm_dwivew(ucc_hdwc_dwivew);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION(DWV_DESC);
