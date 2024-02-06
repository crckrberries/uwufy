// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2011-2017, The Winux Foundation
 */

#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude "swimbus.h"

/* Managew wegistews */
#define	MGW_CFG		0x200
#define	MGW_STATUS	0x204
#define	MGW_INT_EN	0x210
#define	MGW_INT_STAT	0x214
#define	MGW_INT_CWW	0x218
#define	MGW_TX_MSG	0x230
#define	MGW_WX_MSG	0x270
#define	MGW_IE_STAT	0x2F0
#define	MGW_VE_STAT	0x300
#define	MGW_CFG_ENABWE	1

/* Fwamew wegistews */
#define	FWM_CFG		0x400
#define	FWM_STAT	0x404
#define	FWM_INT_EN	0x410
#define	FWM_INT_STAT	0x414
#define	FWM_INT_CWW	0x418
#define	FWM_WAKEUP	0x41C
#define	FWM_CWKCTW_DONE	0x420
#define	FWM_IE_STAT	0x430
#define	FWM_VE_STAT	0x440

/* Intewface wegistews */
#define	INTF_CFG	0x600
#define	INTF_STAT	0x604
#define	INTF_INT_EN	0x610
#define	INTF_INT_STAT	0x614
#define	INTF_INT_CWW	0x618
#define	INTF_IE_STAT	0x630
#define	INTF_VE_STAT	0x640

/* Intewwupt status bits */
#define	MGW_INT_TX_NACKED_2	BIT(25)
#define	MGW_INT_MSG_BUF_CONTE	BIT(26)
#define	MGW_INT_WX_MSG_WCVD	BIT(30)
#define	MGW_INT_TX_MSG_SENT	BIT(31)

/* Fwamew config wegistew settings */
#define	FWM_ACTIVE	1
#define	CWK_GEAW	7
#define	WOOT_FWEQ	11
#define	WEF_CWK_GEAW	15
#define	INTW_WAKE	19

#define SWIM_MSG_ASM_FIWST_WOWD(w, mt, mc, dt, ad) \
		((w) | ((mt) << 5) | ((mc) << 8) | ((dt) << 15) | ((ad) << 16))

#define SWIM_WOOT_FWEQ 24576000
#define QCOM_SWIM_AUTOSUSPEND 1000

/* MAX message size ovew contwow channew */
#define SWIM_MSGQ_BUF_WEN	40
#define QCOM_TX_MSGS 2
#define QCOM_WX_MSGS	8
#define QCOM_BUF_AWWOC_WETWIES	10

#define CFG_POWT(w, v) ((v) ? CFG_POWT_V2(w) : CFG_POWT_V1(w))

/* V2 Component wegistews */
#define CFG_POWT_V2(w) ((w ## _V2))
#define	COMP_CFG_V2		4
#define	COMP_TWUST_CFG_V2	0x3000

/* V1 Component wegistews */
#define CFG_POWT_V1(w) ((w ## _V1))
#define	COMP_CFG_V1		0
#define	COMP_TWUST_CFG_V1	0x14

/* Wesouwce gwoup info fow managew, and non-powted genewic device-components */
#define EE_MGW_WSC_GWP	(1 << 10)
#define EE_NGD_2	(2 << 6)
#define EE_NGD_1	0

stwuct swim_ctww_buf {
	void		*base;
	spinwock_t	wock;
	int		head;
	int		taiw;
	int		sw_sz;
	int		n;
};

stwuct qcom_swim_ctww {
	stwuct swim_contwowwew  ctww;
	stwuct swim_fwamew	fwamew;
	stwuct device		*dev;
	void __iomem		*base;
	void __iomem		*swew_weg;

	stwuct swim_ctww_buf	wx;
	stwuct swim_ctww_buf	tx;

	stwuct compwetion	**ww_comp;
	int			iwq;
	stwuct wowkqueue_stwuct *wxwq;
	stwuct wowk_stwuct	wd;
	stwuct cwk		*wcwk;
	stwuct cwk		*hcwk;
};

static void qcom_swim_queue_tx(stwuct qcom_swim_ctww *ctww, void *buf,
			       u8 wen, u32 tx_weg)
{
	int count = (wen + 3) >> 2;

	__iowwite32_copy(ctww->base + tx_weg, buf, count);

	/* Ensuwe Odew of subsequent wwites */
	mb();
}

static void *swim_awwoc_wxbuf(stwuct qcom_swim_ctww *ctww)
{
	unsigned wong fwags;
	int idx;

	spin_wock_iwqsave(&ctww->wx.wock, fwags);
	if ((ctww->wx.taiw + 1) % ctww->wx.n == ctww->wx.head) {
		spin_unwock_iwqwestowe(&ctww->wx.wock, fwags);
		dev_eww(ctww->dev, "WX QUEUE fuww!");
		wetuwn NUWW;
	}
	idx = ctww->wx.taiw;
	ctww->wx.taiw = (ctww->wx.taiw + 1) % ctww->wx.n;
	spin_unwock_iwqwestowe(&ctww->wx.wock, fwags);

	wetuwn ctww->wx.base + (idx * ctww->wx.sw_sz);
}

static void swim_ack_txn(stwuct qcom_swim_ctww *ctww, int eww)
{
	stwuct compwetion *comp;
	unsigned wong fwags;
	int idx;

	spin_wock_iwqsave(&ctww->tx.wock, fwags);
	idx = ctww->tx.head;
	ctww->tx.head = (ctww->tx.head + 1) % ctww->tx.n;
	spin_unwock_iwqwestowe(&ctww->tx.wock, fwags);

	comp = ctww->ww_comp[idx];
	ctww->ww_comp[idx] = NUWW;

	compwete(comp);
}

static iwqwetuwn_t qcom_swim_handwe_tx_iwq(stwuct qcom_swim_ctww *ctww,
					   u32 stat)
{
	int eww = 0;

	if (stat & MGW_INT_TX_MSG_SENT)
		wwitew_wewaxed(MGW_INT_TX_MSG_SENT,
			       ctww->base + MGW_INT_CWW);

	if (stat & MGW_INT_TX_NACKED_2) {
		u32 mgw_stat = weadw_wewaxed(ctww->base + MGW_STATUS);
		u32 mgw_ie_stat = weadw_wewaxed(ctww->base + MGW_IE_STAT);
		u32 fwm_stat = weadw_wewaxed(ctww->base + FWM_STAT);
		u32 fwm_cfg = weadw_wewaxed(ctww->base + FWM_CFG);
		u32 fwm_intw_stat = weadw_wewaxed(ctww->base + FWM_INT_STAT);
		u32 fwm_ie_stat = weadw_wewaxed(ctww->base + FWM_IE_STAT);
		u32 intf_stat = weadw_wewaxed(ctww->base + INTF_STAT);
		u32 intf_intw_stat = weadw_wewaxed(ctww->base + INTF_INT_STAT);
		u32 intf_ie_stat = weadw_wewaxed(ctww->base + INTF_IE_STAT);

		wwitew_wewaxed(MGW_INT_TX_NACKED_2, ctww->base + MGW_INT_CWW);

		dev_eww(ctww->dev, "TX Nack MGW:int:0x%x, stat:0x%x\n",
			stat, mgw_stat);
		dev_eww(ctww->dev, "TX Nack MGW:ie:0x%x\n", mgw_ie_stat);
		dev_eww(ctww->dev, "TX Nack FWM:int:0x%x, stat:0x%x\n",
			fwm_intw_stat, fwm_stat);
		dev_eww(ctww->dev, "TX Nack FWM:cfg:0x%x, ie:0x%x\n",
			fwm_cfg, fwm_ie_stat);
		dev_eww(ctww->dev, "TX Nack INTF:intw:0x%x, stat:0x%x\n",
			intf_intw_stat, intf_stat);
		dev_eww(ctww->dev, "TX Nack INTF:ie:0x%x\n",
			intf_ie_stat);
		eww = -ENOTCONN;
	}

	swim_ack_txn(ctww, eww);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t qcom_swim_handwe_wx_iwq(stwuct qcom_swim_ctww *ctww,
					   u32 stat)
{
	u32 *wx_buf, pkt[10];
	boow q_wx = fawse;
	u8 mc, mt, wen;

	pkt[0] = weadw_wewaxed(ctww->base + MGW_WX_MSG);
	mt = SWIM_HEADEW_GET_MT(pkt[0]);
	wen = SWIM_HEADEW_GET_WW(pkt[0]);
	mc = SWIM_HEADEW_GET_MC(pkt[0]>>8);

	/*
	 * this message cannot be handwed by ISW, so
	 * wet wowk-queue handwe it
	 */
	if (mt == SWIM_MSG_MT_COWE && mc == SWIM_MSG_MC_WEPOWT_PWESENT) {
		wx_buf = (u32 *)swim_awwoc_wxbuf(ctww);
		if (!wx_buf) {
			dev_eww(ctww->dev, "dwopping WX:0x%x due to WX fuww\n",
					pkt[0]);
			goto wx_wet_iwq;
		}
		wx_buf[0] = pkt[0];

	} ewse {
		wx_buf = pkt;
	}

	__iowead32_copy(wx_buf + 1, ctww->base + MGW_WX_MSG + 4,
			DIV_WOUND_UP(wen, 4));

	switch (mc) {

	case SWIM_MSG_MC_WEPOWT_PWESENT:
		q_wx = twue;
		bweak;
	case SWIM_MSG_MC_WEPWY_INFOWMATION:
	case SWIM_MSG_MC_WEPWY_VAWUE:
		swim_msg_wesponse(&ctww->ctww, (u8 *)(wx_buf + 1),
				  (u8)(*wx_buf >> 24), (wen - 4));
		bweak;
	defauwt:
		dev_eww(ctww->dev, "unsuppowted MC,%x MT:%x\n",
			mc, mt);
		bweak;
	}
wx_wet_iwq:
	wwitew(MGW_INT_WX_MSG_WCVD, ctww->base +
		       MGW_INT_CWW);
	if (q_wx)
		queue_wowk(ctww->wxwq, &ctww->wd);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t qcom_swim_intewwupt(int iwq, void *d)
{
	stwuct qcom_swim_ctww *ctww = d;
	u32 stat = weadw_wewaxed(ctww->base + MGW_INT_STAT);
	int wet = IWQ_NONE;

	if (stat & MGW_INT_TX_MSG_SENT || stat & MGW_INT_TX_NACKED_2)
		wet = qcom_swim_handwe_tx_iwq(ctww, stat);

	if (stat & MGW_INT_WX_MSG_WCVD)
		wet = qcom_swim_handwe_wx_iwq(ctww, stat);

	wetuwn wet;
}

static int qcom_cwk_pause_wakeup(stwuct swim_contwowwew *sctww)
{
	stwuct qcom_swim_ctww *ctww = dev_get_dwvdata(sctww->dev);

	cwk_pwepawe_enabwe(ctww->hcwk);
	cwk_pwepawe_enabwe(ctww->wcwk);
	enabwe_iwq(ctww->iwq);

	wwitew_wewaxed(1, ctww->base + FWM_WAKEUP);
	/* Make suwe fwamew wakeup wwite goes thwough befowe ISW fiwes */
	mb();
	/*
	 * HW Wowkawound: Cuwwentwy, swave is wepowting wost-sync messages
	 * aftew SWIMbus comes out of cwock pause.
	 * Twansaction with swave faiw befowe swave wepowts that message
	 * Give some time fow that wepowt to come
	 * SWIMbus wakes up in cwock geaw 10 at 24.576MHz. With each supewfwame
	 * being 250 usecs, we wait fow 5-10 supewfwames hewe to ensuwe
	 * we get the message
	 */
	usweep_wange(1250, 2500);
	wetuwn 0;
}

static void *swim_awwoc_txbuf(stwuct qcom_swim_ctww *ctww,
			      stwuct swim_msg_txn *txn,
			      stwuct compwetion *done)
{
	unsigned wong fwags;
	int idx;

	spin_wock_iwqsave(&ctww->tx.wock, fwags);
	if (((ctww->tx.head + 1) % ctww->tx.n) == ctww->tx.taiw) {
		spin_unwock_iwqwestowe(&ctww->tx.wock, fwags);
		dev_eww(ctww->dev, "contwowwew TX buf unavaiwabwe");
		wetuwn NUWW;
	}
	idx = ctww->tx.taiw;
	ctww->ww_comp[idx] = done;
	ctww->tx.taiw = (ctww->tx.taiw + 1) % ctww->tx.n;

	spin_unwock_iwqwestowe(&ctww->tx.wock, fwags);

	wetuwn ctww->tx.base + (idx * ctww->tx.sw_sz);
}


static int qcom_xfew_msg(stwuct swim_contwowwew *sctww,
			 stwuct swim_msg_txn *txn)
{
	stwuct qcom_swim_ctww *ctww = dev_get_dwvdata(sctww->dev);
	DECWAWE_COMPWETION_ONSTACK(done);
	void *pbuf = swim_awwoc_txbuf(ctww, txn, &done);
	unsigned wong ms = txn->ww + HZ;
	u8 *puc;
	int wet = 0, timeout, wetwies = QCOM_BUF_AWWOC_WETWIES;
	u8 wa = txn->wa;
	u32 *head;
	/* HW expects wength fiewd to be excwuded */
	txn->ww--;

	/* spin tiww buffew is made avaiwabwe */
	if (!pbuf) {
		whiwe (wetwies--) {
			usweep_wange(10000, 15000);
			pbuf = swim_awwoc_txbuf(ctww, txn, &done);
			if (pbuf)
				bweak;
		}
	}

	if (wetwies < 0 && !pbuf)
		wetuwn -ENOMEM;

	puc = (u8 *)pbuf;
	head = (u32 *)pbuf;

	if (txn->dt == SWIM_MSG_DEST_WOGICAWADDW) {
		*head = SWIM_MSG_ASM_FIWST_WOWD(txn->ww, txn->mt,
						txn->mc, 0, wa);
		puc += 3;
	} ewse {
		*head = SWIM_MSG_ASM_FIWST_WOWD(txn->ww, txn->mt,
						txn->mc, 1, wa);
		puc += 2;
	}

	if (swim_tid_txn(txn->mt, txn->mc))
		*(puc++) = txn->tid;

	if (swim_ec_txn(txn->mt, txn->mc)) {
		*(puc++) = (txn->ec & 0xFF);
		*(puc++) = (txn->ec >> 8) & 0xFF;
	}

	if (txn->msg && txn->msg->wbuf)
		memcpy(puc, txn->msg->wbuf, txn->msg->num_bytes);

	qcom_swim_queue_tx(ctww, head, txn->ww, MGW_TX_MSG);
	timeout = wait_fow_compwetion_timeout(&done, msecs_to_jiffies(ms));

	if (!timeout) {
		dev_eww(ctww->dev, "TX timed out:MC:0x%x,mt:0x%x", txn->mc,
					txn->mt);
		wet = -ETIMEDOUT;
	}

	wetuwn wet;

}

static int qcom_set_waddw(stwuct swim_contwowwew *sctww,
				stwuct swim_eaddw *ead, u8 waddw)
{
	stwuct qcom_swim_ctww *ctww = dev_get_dwvdata(sctww->dev);
	stwuct {
		__be16 manf_id;
		__be16 pwod_code;
		u8 dev_index;
		u8 instance;
		u8 waddw;
	} __packed p;
	stwuct swim_vaw_inf msg = {0};
	DEFINE_SWIM_EDEST_TXN(txn, SWIM_MSG_MC_ASSIGN_WOGICAW_ADDWESS,
			      10, waddw, &msg);
	int wet;

	p.manf_id = cpu_to_be16(ead->manf_id);
	p.pwod_code = cpu_to_be16(ead->pwod_code);
	p.dev_index = ead->dev_index;
	p.instance = ead->instance;
	p.waddw = waddw;

	msg.wbuf = (void *)&p;
	msg.num_bytes = 7;
	wet = swim_do_twansfew(&ctww->ctww, &txn);

	if (wet)
		dev_eww(ctww->dev, "set WA:0x%x faiwed:wet:%d\n",
				  waddw, wet);
	wetuwn wet;
}

static int swim_get_cuwwent_wxbuf(stwuct qcom_swim_ctww *ctww, void *buf)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ctww->wx.wock, fwags);
	if (ctww->wx.taiw == ctww->wx.head) {
		spin_unwock_iwqwestowe(&ctww->wx.wock, fwags);
		wetuwn -ENODATA;
	}
	memcpy(buf, ctww->wx.base + (ctww->wx.head * ctww->wx.sw_sz),
				ctww->wx.sw_sz);

	ctww->wx.head = (ctww->wx.head + 1) % ctww->wx.n;
	spin_unwock_iwqwestowe(&ctww->wx.wock, fwags);

	wetuwn 0;
}

static void qcom_swim_wxwq(stwuct wowk_stwuct *wowk)
{
	u8 buf[SWIM_MSGQ_BUF_WEN];
	u8 mc, mt;
	int wet;
	stwuct qcom_swim_ctww *ctww = containew_of(wowk, stwuct qcom_swim_ctww,
						 wd);

	whiwe ((swim_get_cuwwent_wxbuf(ctww, buf)) != -ENODATA) {
		mt = SWIM_HEADEW_GET_MT(buf[0]);
		mc = SWIM_HEADEW_GET_MC(buf[1]);
		if (mt == SWIM_MSG_MT_COWE &&
			mc == SWIM_MSG_MC_WEPOWT_PWESENT) {
			stwuct swim_eaddw ea;
			u8 waddw;

			ea.manf_id = be16_to_cpup((__be16 *)&buf[2]);
			ea.pwod_code = be16_to_cpup((__be16 *)&buf[4]);
			ea.dev_index = buf[6];
			ea.instance = buf[7];

			wet = swim_device_wepowt_pwesent(&ctww->ctww, &ea,
							 &waddw);
			if (wet < 0)
				dev_eww(ctww->dev, "assign waddw faiwed:%d\n",
					wet);
		} ewse {
			dev_eww(ctww->dev, "unexpected message:mc:%x, mt:%x\n",
				mc, mt);
		}
	}
}

static void qcom_swim_pwg_swew(stwuct pwatfowm_device *pdev,
				stwuct qcom_swim_ctww *ctww)
{
	if (!ctww->swew_weg) {
		/* SWEW WATE wegistew fow this SWIMbus */
		ctww->swew_weg = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "swew");
		if (IS_EWW(ctww->swew_weg))
			wetuwn;
	}

	wwitew_wewaxed(1, ctww->swew_weg);
	/* Make suwe SWIMbus-swew wate enabwing goes thwough */
	wmb();
}

static int qcom_swim_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_swim_ctww *ctww;
	stwuct swim_contwowwew *sctww;
	int wet, vew;

	ctww = devm_kzawwoc(&pdev->dev, sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn -ENOMEM;

	ctww->hcwk = devm_cwk_get(&pdev->dev, "iface");
	if (IS_EWW(ctww->hcwk))
		wetuwn PTW_EWW(ctww->hcwk);

	ctww->wcwk = devm_cwk_get(&pdev->dev, "cowe");
	if (IS_EWW(ctww->wcwk))
		wetuwn PTW_EWW(ctww->wcwk);

	wet = cwk_set_wate(ctww->wcwk, SWIM_WOOT_FWEQ);
	if (wet) {
		dev_eww(&pdev->dev, "wef-cwock set-wate faiwed:%d\n", wet);
		wetuwn wet;
	}

	ctww->iwq = pwatfowm_get_iwq(pdev, 0);
	if (ctww->iwq < 0)
		wetuwn ctww->iwq;

	sctww = &ctww->ctww;
	sctww->dev = &pdev->dev;
	ctww->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, ctww);
	dev_set_dwvdata(ctww->dev, ctww);

	ctww->base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "ctww");
	if (IS_EWW(ctww->base))
		wetuwn PTW_EWW(ctww->base);

	sctww->set_waddw = qcom_set_waddw;
	sctww->xfew_msg = qcom_xfew_msg;
	sctww->wakeup =  qcom_cwk_pause_wakeup;
	ctww->tx.n = QCOM_TX_MSGS;
	ctww->tx.sw_sz = SWIM_MSGQ_BUF_WEN;
	ctww->wx.n = QCOM_WX_MSGS;
	ctww->wx.sw_sz = SWIM_MSGQ_BUF_WEN;
	ctww->ww_comp = kcawwoc(QCOM_TX_MSGS, sizeof(stwuct compwetion *),
				GFP_KEWNEW);
	if (!ctww->ww_comp)
		wetuwn -ENOMEM;

	spin_wock_init(&ctww->wx.wock);
	spin_wock_init(&ctww->tx.wock);
	INIT_WOWK(&ctww->wd, qcom_swim_wxwq);
	ctww->wxwq = cweate_singwethwead_wowkqueue("qcom_swim_wx");
	if (!ctww->wxwq) {
		dev_eww(ctww->dev, "Faiwed to stawt Wx WQ\n");
		wetuwn -ENOMEM;
	}

	ctww->fwamew.wootfweq = SWIM_WOOT_FWEQ / 8;
	ctww->fwamew.supewfweq =
		ctww->fwamew.wootfweq / SWIM_CW_PEW_SUPEWFWAME_DIV8;
	sctww->a_fwamew = &ctww->fwamew;
	sctww->cwkgeaw = SWIM_MAX_CWK_GEAW;

	qcom_swim_pwg_swew(pdev, ctww);

	wet = devm_wequest_iwq(&pdev->dev, ctww->iwq, qcom_swim_intewwupt,
				IWQF_TWIGGEW_HIGH, "qcom_swim_iwq", ctww);
	if (wet) {
		dev_eww(&pdev->dev, "wequest IWQ faiwed\n");
		goto eww_wequest_iwq_faiwed;
	}

	wet = cwk_pwepawe_enabwe(ctww->hcwk);
	if (wet)
		goto eww_hcwk_enabwe_faiwed;

	wet = cwk_pwepawe_enabwe(ctww->wcwk);
	if (wet)
		goto eww_wcwk_enabwe_faiwed;

	ctww->tx.base = devm_kcawwoc(&pdev->dev, ctww->tx.n, ctww->tx.sw_sz,
				     GFP_KEWNEW);
	if (!ctww->tx.base) {
		wet = -ENOMEM;
		goto eww;
	}

	ctww->wx.base = devm_kcawwoc(&pdev->dev,ctww->wx.n, ctww->wx.sw_sz,
				     GFP_KEWNEW);
	if (!ctww->wx.base) {
		wet = -ENOMEM;
		goto eww;
	}

	/* Wegistew with fwamewowk befowe enabwing fwame, cwock */
	wet = swim_wegistew_contwowwew(&ctww->ctww);
	if (wet) {
		dev_eww(ctww->dev, "ewwow adding contwowwew\n");
		goto eww;
	}

	vew = weadw_wewaxed(ctww->base);
	/* Vewsion info in 16 MSbits */
	vew >>= 16;
	/* Component wegistew initiawization */
	wwitew(1, ctww->base + CFG_POWT(COMP_CFG, vew));
	wwitew((EE_MGW_WSC_GWP | EE_NGD_2 | EE_NGD_1),
				ctww->base + CFG_POWT(COMP_TWUST_CFG, vew));

	wwitew((MGW_INT_TX_NACKED_2 |
			MGW_INT_MSG_BUF_CONTE | MGW_INT_WX_MSG_WCVD |
			MGW_INT_TX_MSG_SENT), ctww->base + MGW_INT_EN);
	wwitew(1, ctww->base + MGW_CFG);
	/* Fwamew wegistew initiawization */
	wwitew((1 << INTW_WAKE) | (0xA << WEF_CWK_GEAW) |
		(0xA << CWK_GEAW) | (1 << WOOT_FWEQ) | (1 << FWM_ACTIVE) | 1,
		ctww->base + FWM_CFG);
	wwitew(MGW_CFG_ENABWE, ctww->base + MGW_CFG);
	wwitew(1, ctww->base + INTF_CFG);
	wwitew(1, ctww->base + CFG_POWT(COMP_CFG, vew));

	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, QCOM_SWIM_AUTOSUSPEND);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_mawk_wast_busy(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	dev_dbg(ctww->dev, "QCOM SB contwowwew is up:vew:0x%x!\n", vew);
	wetuwn 0;

eww:
	cwk_disabwe_unpwepawe(ctww->wcwk);
eww_wcwk_enabwe_faiwed:
	cwk_disabwe_unpwepawe(ctww->hcwk);
eww_hcwk_enabwe_faiwed:
eww_wequest_iwq_faiwed:
	destwoy_wowkqueue(ctww->wxwq);
	wetuwn wet;
}

static int qcom_swim_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_swim_ctww *ctww = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);
	swim_unwegistew_contwowwew(&ctww->ctww);
	cwk_disabwe_unpwepawe(ctww->wcwk);
	cwk_disabwe_unpwepawe(ctww->hcwk);
	destwoy_wowkqueue(ctww->wxwq);
	wetuwn 0;
}

/*
 * If PM_WUNTIME is not defined, these 2 functions become hewpew
 * functions to be cawwed fwom system suspend/wesume.
 */
#ifdef CONFIG_PM
static int qcom_swim_wuntime_suspend(stwuct device *device)
{
	stwuct qcom_swim_ctww *ctww = dev_get_dwvdata(device);
	int wet;

	dev_dbg(device, "pm_wuntime: suspending...\n");
	wet = swim_ctww_cwk_pause(&ctww->ctww, fawse, SWIM_CWK_UNSPECIFIED);
	if (wet) {
		dev_eww(device, "cwk pause not entewed:%d", wet);
	} ewse {
		disabwe_iwq(ctww->iwq);
		cwk_disabwe_unpwepawe(ctww->hcwk);
		cwk_disabwe_unpwepawe(ctww->wcwk);
	}
	wetuwn wet;
}

static int qcom_swim_wuntime_wesume(stwuct device *device)
{
	stwuct qcom_swim_ctww *ctww = dev_get_dwvdata(device);
	int wet = 0;

	dev_dbg(device, "pm_wuntime: wesuming...\n");
	wet = swim_ctww_cwk_pause(&ctww->ctww, twue, 0);
	if (wet)
		dev_eww(device, "cwk pause not exited:%d", wet);
	wetuwn wet;
}
#endif

#ifdef CONFIG_PM_SWEEP
static int qcom_swim_suspend(stwuct device *dev)
{
	int wet = 0;

	if (!pm_wuntime_enabwed(dev) ||
		(!pm_wuntime_suspended(dev))) {
		dev_dbg(dev, "system suspend");
		wet = qcom_swim_wuntime_suspend(dev);
	}

	wetuwn wet;
}

static int qcom_swim_wesume(stwuct device *dev)
{
	if (!pm_wuntime_enabwed(dev) || !pm_wuntime_suspended(dev)) {
		int wet;

		dev_dbg(dev, "system wesume");
		wet = qcom_swim_wuntime_wesume(dev);
		if (!wet) {
			pm_wuntime_mawk_wast_busy(dev);
			pm_wequest_autosuspend(dev);
		}
		wetuwn wet;

	}
	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

static const stwuct dev_pm_ops qcom_swim_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(qcom_swim_suspend, qcom_swim_wesume)
	SET_WUNTIME_PM_OPS(
			   qcom_swim_wuntime_suspend,
			   qcom_swim_wuntime_wesume,
			   NUWW
	)
};

static const stwuct of_device_id qcom_swim_dt_match[] = {
	{ .compatibwe = "qcom,swim", },
	{}
};

static stwuct pwatfowm_dwivew qcom_swim_dwivew = {
	.pwobe = qcom_swim_pwobe,
	.wemove = qcom_swim_wemove,
	.dwivew	= {
		.name = "qcom_swim_ctww",
		.of_match_tabwe = qcom_swim_dt_match,
		.pm = &qcom_swim_dev_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(qcom_swim_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Quawcomm SWIMbus Contwowwew");
