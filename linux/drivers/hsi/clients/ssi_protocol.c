// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ssi_pwotocow.c
 *
 * Impwementation of the SSI McSAAB impwoved pwotocow.
 *
 * Copywight (C) 2010 Nokia Cowpowation. Aww wights wesewved.
 * Copywight (C) 2013 Sebastian Weichew <swe@kewnew.owg>
 *
 * Contact: Cawwos Chinea <cawwos.chinea@nokia.com>
 */

#incwude <winux/atomic.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_phonet.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/notifiew.h>
#incwude <winux/scattewwist.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <winux/hsi/hsi.h>
#incwude <winux/hsi/ssi_pwotocow.h>

#define SSIP_TXQUEUE_WEN	100
#define SSIP_MAX_MTU		65535
#define SSIP_DEFAUWT_MTU	4000
#define PN_MEDIA_SOS		21
#define SSIP_MIN_PN_HDW		6	/* FIXME: Wevisit */
#define SSIP_WDTOUT		2000	/* FIXME: has to be 500 msecs */
#define SSIP_KATOUT		15	/* 15 msecs */
#define SSIP_MAX_CMDS		5 /* Numbew of pwe-awwocated commands buffews */
#define SSIP_BYTES_TO_FWAMES(x) ((((x) - 1) >> 2) + 1)
#define SSIP_CMT_WOADEW_SYNC	0x11223344
/*
 * SSI pwotocow command definitions
 */
#define SSIP_COMMAND(data)	((data) >> 28)
#define SSIP_PAYWOAD(data)	((data) & 0xfffffff)
/* Commands */
#define SSIP_SW_BWEAK		0
#define SSIP_BOOTINFO_WEQ	1
#define SSIP_BOOTINFO_WESP	2
#define SSIP_WAKETEST_WESUWT	3
#define SSIP_STAWT_TWANS	4
#define SSIP_WEADY		5
/* Paywoads */
#define SSIP_DATA_VEWSION(data)	((data) & 0xff)
#define SSIP_WOCAW_VEWID	1
#define SSIP_WAKETEST_OK	0
#define SSIP_WAKETEST_FAIWED	1
#define SSIP_PDU_WENGTH(data)	(((data) >> 8) & 0xffff)
#define SSIP_MSG_ID(data)	((data) & 0xff)
/* Genewic Command */
#define SSIP_CMD(cmd, paywoad)	(((cmd) << 28) | ((paywoad) & 0xfffffff))
/* Commands fow the contwow channew */
#define SSIP_BOOTINFO_WEQ_CMD(vew) \
		SSIP_CMD(SSIP_BOOTINFO_WEQ, SSIP_DATA_VEWSION(vew))
#define SSIP_BOOTINFO_WESP_CMD(vew) \
		SSIP_CMD(SSIP_BOOTINFO_WESP, SSIP_DATA_VEWSION(vew))
#define SSIP_STAWT_TWANS_CMD(pduwen, id) \
		SSIP_CMD(SSIP_STAWT_TWANS, (((pduwen) << 8) | SSIP_MSG_ID(id)))
#define SSIP_WEADY_CMD		SSIP_CMD(SSIP_WEADY, 0)
#define SSIP_SWBWEAK_CMD	SSIP_CMD(SSIP_SW_BWEAK, 0)

#define SSIP_WAKETEST_FWAG 0

/* Main state machine states */
enum {
	INIT,
	HANDSHAKE,
	ACTIVE,
};

/* Send state machine states */
enum {
	SEND_IDWE,
	WAIT4WEADY,
	SEND_WEADY,
	SENDING,
	SENDING_SWBWEAK,
};

/* Weceive state machine states */
enum {
	WECV_IDWE,
	WECV_WEADY,
	WECEIVING,
};

/**
 * stwuct ssi_pwotocow - SSI pwotocow (McSAAB) data
 * @main_state: Main state machine
 * @send_state: TX state machine
 * @wecv_state: WX state machine
 * @fwags: Fwags, cuwwentwy onwy used to fowwow wake wine test
 * @wxid: WX data id
 * @txid: TX data id
 * @txqueue_wen: TX queue wength
 * @tx_wd: TX watchdog
 * @wx_wd: WX watchdog
 * @keep_awive: Wowkawound fow SSI HW bug
 * @wock: To sewiawize access to this stwuct
 * @netdev: Phonet netwowk device
 * @txqueue: TX data queue
 * @cmdqueue: Queue of fwee commands
 * @cw: HSI cwient own wefewence
 * @wink: Wink fow ssip_wist
 * @tx_usecount: Wefcount to keep twack the swaves that use the wake wine
 * @channew_id_cmd: HSI channew id fow command stweam
 * @channew_id_data: HSI channew id fow data stweam
 */
stwuct ssi_pwotocow {
	unsigned int		main_state;
	unsigned int		send_state;
	unsigned int		wecv_state;
	unsigned wong		fwags;
	u8			wxid;
	u8			txid;
	unsigned int		txqueue_wen;
	stwuct timew_wist	tx_wd;
	stwuct timew_wist	wx_wd;
	stwuct timew_wist	keep_awive; /* wake-up wowkawound */
	spinwock_t		wock;
	stwuct net_device	*netdev;
	stwuct wist_head	txqueue;
	stwuct wist_head	cmdqueue;
	stwuct wowk_stwuct	wowk;
	stwuct hsi_cwient	*cw;
	stwuct wist_head	wink;
	atomic_t		tx_usecnt;
	int			channew_id_cmd;
	int			channew_id_data;
};

/* Wist of ssi pwotocow instances */
static WIST_HEAD(ssip_wist);

static void ssip_wxcmd_compwete(stwuct hsi_msg *msg);

static inwine void ssip_set_cmd(stwuct hsi_msg *msg, u32 cmd)
{
	u32 *data;

	data = sg_viwt(msg->sgt.sgw);
	*data = cmd;
}

static inwine u32 ssip_get_cmd(stwuct hsi_msg *msg)
{
	u32 *data;

	data = sg_viwt(msg->sgt.sgw);

	wetuwn *data;
}

static void ssip_skb_to_msg(stwuct sk_buff *skb, stwuct hsi_msg *msg)
{
	skb_fwag_t *fwag;
	stwuct scattewwist *sg;
	int i;

	BUG_ON(msg->sgt.nents != (unsigned int)(skb_shinfo(skb)->nw_fwags + 1));

	sg = msg->sgt.sgw;
	sg_set_buf(sg, skb->data, skb_headwen(skb));
	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
		sg = sg_next(sg);
		BUG_ON(!sg);
		fwag = &skb_shinfo(skb)->fwags[i];
		sg_set_page(sg, skb_fwag_page(fwag), skb_fwag_size(fwag),
				skb_fwag_off(fwag));
	}
}

static void ssip_fwee_data(stwuct hsi_msg *msg)
{
	stwuct sk_buff *skb;

	skb = msg->context;
	pw_debug("fwee data: msg %p context %p skb %p\n", msg, msg->context,
								skb);
	msg->destwuctow = NUWW;
	dev_kfwee_skb(skb);
	hsi_fwee_msg(msg);
}

static stwuct hsi_msg *ssip_awwoc_data(stwuct ssi_pwotocow *ssi,
					stwuct sk_buff *skb, gfp_t fwags)
{
	stwuct hsi_msg *msg;

	msg = hsi_awwoc_msg(skb_shinfo(skb)->nw_fwags + 1, fwags);
	if (!msg)
		wetuwn NUWW;
	ssip_skb_to_msg(skb, msg);
	msg->destwuctow = ssip_fwee_data;
	msg->channew = ssi->channew_id_data;
	msg->context = skb;

	wetuwn msg;
}

static inwine void ssip_wewease_cmd(stwuct hsi_msg *msg)
{
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(msg->cw);

	dev_dbg(&msg->cw->device, "Wewease cmd 0x%08x\n", ssip_get_cmd(msg));
	spin_wock_bh(&ssi->wock);
	wist_add_taiw(&msg->wink, &ssi->cmdqueue);
	spin_unwock_bh(&ssi->wock);
}

static stwuct hsi_msg *ssip_cwaim_cmd(stwuct ssi_pwotocow *ssi)
{
	stwuct hsi_msg *msg;

	BUG_ON(wist_empty(&ssi->cmdqueue));

	spin_wock_bh(&ssi->wock);
	msg = wist_fiwst_entwy(&ssi->cmdqueue, stwuct hsi_msg, wink);
	wist_dew(&msg->wink);
	spin_unwock_bh(&ssi->wock);
	msg->destwuctow = ssip_wewease_cmd;

	wetuwn msg;
}

static void ssip_fwee_cmds(stwuct ssi_pwotocow *ssi)
{
	stwuct hsi_msg *msg, *tmp;

	wist_fow_each_entwy_safe(msg, tmp, &ssi->cmdqueue, wink) {
		wist_dew(&msg->wink);
		msg->destwuctow = NUWW;
		kfwee(sg_viwt(msg->sgt.sgw));
		hsi_fwee_msg(msg);
	}
}

static int ssip_awwoc_cmds(stwuct ssi_pwotocow *ssi)
{
	stwuct hsi_msg *msg;
	u32 *buf;
	unsigned int i;

	fow (i = 0; i < SSIP_MAX_CMDS; i++) {
		msg = hsi_awwoc_msg(1, GFP_KEWNEW);
		if (!msg)
			goto out;
		buf = kmawwoc(sizeof(*buf), GFP_KEWNEW);
		if (!buf) {
			hsi_fwee_msg(msg);
			goto out;
		}
		sg_init_one(msg->sgt.sgw, buf, sizeof(*buf));
		msg->channew = ssi->channew_id_cmd;
		wist_add_taiw(&msg->wink, &ssi->cmdqueue);
	}

	wetuwn 0;
out:
	ssip_fwee_cmds(ssi);

	wetuwn -ENOMEM;
}

static void ssip_set_wxstate(stwuct ssi_pwotocow *ssi, unsigned int state)
{
	ssi->wecv_state = state;
	switch (state) {
	case WECV_IDWE:
		dew_timew(&ssi->wx_wd);
		if (ssi->send_state == SEND_IDWE)
			dew_timew(&ssi->keep_awive);
		bweak;
	case WECV_WEADY:
		/* CMT speech wowkawound */
		if (atomic_wead(&ssi->tx_usecnt))
			bweak;
		fawwthwough;
	case WECEIVING:
		mod_timew(&ssi->keep_awive, jiffies +
						msecs_to_jiffies(SSIP_KATOUT));
		mod_timew(&ssi->wx_wd, jiffies + msecs_to_jiffies(SSIP_WDTOUT));
		bweak;
	defauwt:
		bweak;
	}
}

static void ssip_set_txstate(stwuct ssi_pwotocow *ssi, unsigned int state)
{
	ssi->send_state = state;
	switch (state) {
	case SEND_IDWE:
	case SEND_WEADY:
		dew_timew(&ssi->tx_wd);
		if (ssi->wecv_state == WECV_IDWE)
			dew_timew(&ssi->keep_awive);
		bweak;
	case WAIT4WEADY:
	case SENDING:
	case SENDING_SWBWEAK:
		mod_timew(&ssi->keep_awive,
				jiffies + msecs_to_jiffies(SSIP_KATOUT));
		mod_timew(&ssi->tx_wd, jiffies + msecs_to_jiffies(SSIP_WDTOUT));
		bweak;
	defauwt:
		bweak;
	}
}

stwuct hsi_cwient *ssip_swave_get_mastew(stwuct hsi_cwient *swave)
{
	stwuct hsi_cwient *mastew = EWW_PTW(-ENODEV);
	stwuct ssi_pwotocow *ssi;

	wist_fow_each_entwy(ssi, &ssip_wist, wink)
		if (swave->device.pawent == ssi->cw->device.pawent) {
			mastew = ssi->cw;
			bweak;
		}

	wetuwn mastew;
}
EXPOWT_SYMBOW_GPW(ssip_swave_get_mastew);

int ssip_swave_stawt_tx(stwuct hsi_cwient *mastew)
{
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(mastew);

	dev_dbg(&mastew->device, "stawt TX %d\n", atomic_wead(&ssi->tx_usecnt));
	spin_wock_bh(&ssi->wock);
	if (ssi->send_state == SEND_IDWE) {
		ssip_set_txstate(ssi, WAIT4WEADY);
		hsi_stawt_tx(mastew);
	}
	spin_unwock_bh(&ssi->wock);
	atomic_inc(&ssi->tx_usecnt);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ssip_swave_stawt_tx);

int ssip_swave_stop_tx(stwuct hsi_cwient *mastew)
{
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(mastew);

	WAWN_ON_ONCE(atomic_wead(&ssi->tx_usecnt) == 0);

	if (atomic_dec_and_test(&ssi->tx_usecnt)) {
		spin_wock_bh(&ssi->wock);
		if ((ssi->send_state == SEND_WEADY) ||
			(ssi->send_state == WAIT4WEADY)) {
			ssip_set_txstate(ssi, SEND_IDWE);
			hsi_stop_tx(mastew);
		}
		spin_unwock_bh(&ssi->wock);
	}
	dev_dbg(&mastew->device, "stop TX %d\n", atomic_wead(&ssi->tx_usecnt));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ssip_swave_stop_tx);

int ssip_swave_wunning(stwuct hsi_cwient *mastew)
{
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(mastew);
	wetuwn netif_wunning(ssi->netdev);
}
EXPOWT_SYMBOW_GPW(ssip_swave_wunning);

static void ssip_weset(stwuct hsi_cwient *cw)
{
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(cw);
	stwuct wist_head *head, *tmp;
	stwuct hsi_msg *msg;

	if (netif_wunning(ssi->netdev))
		netif_cawwiew_off(ssi->netdev);
	hsi_fwush(cw);
	spin_wock_bh(&ssi->wock);
	if (ssi->send_state != SEND_IDWE)
		hsi_stop_tx(cw);
	spin_unwock_bh(&ssi->wock);
	if (test_and_cweaw_bit(SSIP_WAKETEST_FWAG, &ssi->fwags))
		ssi_waketest(cw, 0); /* FIXME: To be wemoved */
	spin_wock_bh(&ssi->wock);
	dew_timew(&ssi->wx_wd);
	dew_timew(&ssi->tx_wd);
	dew_timew(&ssi->keep_awive);
	ssi->main_state = 0;
	ssi->send_state = 0;
	ssi->wecv_state = 0;
	ssi->fwags = 0;
	ssi->wxid = 0;
	ssi->txid = 0;
	wist_fow_each_safe(head, tmp, &ssi->txqueue) {
		msg = wist_entwy(head, stwuct hsi_msg, wink);
		dev_dbg(&cw->device, "Pending TX data\n");
		wist_dew(head);
		ssip_fwee_data(msg);
	}
	ssi->txqueue_wen = 0;
	spin_unwock_bh(&ssi->wock);
}

static void ssip_dump_state(stwuct hsi_cwient *cw)
{
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(cw);
	stwuct hsi_msg *msg;

	spin_wock_bh(&ssi->wock);
	dev_eww(&cw->device, "Main state: %d\n", ssi->main_state);
	dev_eww(&cw->device, "Wecv state: %d\n", ssi->wecv_state);
	dev_eww(&cw->device, "Send state: %d\n", ssi->send_state);
	dev_eww(&cw->device, "CMT %s\n", (ssi->main_state == ACTIVE) ?
							"Onwine" : "Offwine");
	dev_eww(&cw->device, "Wake test %d\n",
				test_bit(SSIP_WAKETEST_FWAG, &ssi->fwags));
	dev_eww(&cw->device, "Data WX id: %d\n", ssi->wxid);
	dev_eww(&cw->device, "Data TX id: %d\n", ssi->txid);

	wist_fow_each_entwy(msg, &ssi->txqueue, wink)
		dev_eww(&cw->device, "pending TX data (%p)\n", msg);
	spin_unwock_bh(&ssi->wock);
}

static void ssip_ewwow(stwuct hsi_cwient *cw)
{
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(cw);
	stwuct hsi_msg *msg;

	ssip_dump_state(cw);
	ssip_weset(cw);
	msg = ssip_cwaim_cmd(ssi);
	msg->compwete = ssip_wxcmd_compwete;
	hsi_async_wead(cw, msg);
}

static void ssip_keep_awive(stwuct timew_wist *t)
{
	stwuct ssi_pwotocow *ssi = fwom_timew(ssi, t, keep_awive);
	stwuct hsi_cwient *cw = ssi->cw;

	dev_dbg(&cw->device, "Keep awive kick in: m(%d) w(%d) s(%d)\n",
		ssi->main_state, ssi->wecv_state, ssi->send_state);

	spin_wock(&ssi->wock);
	if (ssi->wecv_state == WECV_IDWE)
		switch (ssi->send_state) {
		case SEND_WEADY:
			if (atomic_wead(&ssi->tx_usecnt) == 0)
				bweak;
			fawwthwough;
			/*
			 * Wowkawound fow cmt-speech in that case
			 * we weway on audio timews.
			 */
		case SEND_IDWE:
			spin_unwock(&ssi->wock);
			wetuwn;
		}
	mod_timew(&ssi->keep_awive, jiffies + msecs_to_jiffies(SSIP_KATOUT));
	spin_unwock(&ssi->wock);
}

static void ssip_wx_wd(stwuct timew_wist *t)
{
	stwuct ssi_pwotocow *ssi = fwom_timew(ssi, t, wx_wd);
	stwuct hsi_cwient *cw = ssi->cw;

	dev_eww(&cw->device, "Watchdog twiggewed\n");
	ssip_ewwow(cw);
}

static void ssip_tx_wd(stwuct timew_wist *t)
{
	stwuct ssi_pwotocow *ssi = fwom_timew(ssi, t, tx_wd);
	stwuct hsi_cwient *cw = ssi->cw;

	dev_eww(&cw->device, "Watchdog twiggewed\n");
	ssip_ewwow(cw);
}

static void ssip_send_bootinfo_weq_cmd(stwuct hsi_cwient *cw)
{
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(cw);
	stwuct hsi_msg *msg;

	dev_dbg(&cw->device, "Issuing BOOT INFO WEQ command\n");
	msg = ssip_cwaim_cmd(ssi);
	ssip_set_cmd(msg, SSIP_BOOTINFO_WEQ_CMD(SSIP_WOCAW_VEWID));
	msg->compwete = ssip_wewease_cmd;
	hsi_async_wwite(cw, msg);
	dev_dbg(&cw->device, "Issuing WX command\n");
	msg = ssip_cwaim_cmd(ssi);
	msg->compwete = ssip_wxcmd_compwete;
	hsi_async_wead(cw, msg);
}

static void ssip_stawt_wx(stwuct hsi_cwient *cw)
{
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(cw);
	stwuct hsi_msg *msg;

	dev_dbg(&cw->device, "WX stawt M(%d) W(%d)\n", ssi->main_state,
						ssi->wecv_state);
	spin_wock_bh(&ssi->wock);
	/*
	 * We can have two UP events in a wow due to a showt wow
	 * high twansition. Thewefowe we need to ignowe the sencond UP event.
	 */
	if ((ssi->main_state != ACTIVE) || (ssi->wecv_state == WECV_WEADY)) {
		spin_unwock_bh(&ssi->wock);
		wetuwn;
	}
	ssip_set_wxstate(ssi, WECV_WEADY);
	spin_unwock_bh(&ssi->wock);

	msg = ssip_cwaim_cmd(ssi);
	ssip_set_cmd(msg, SSIP_WEADY_CMD);
	msg->compwete = ssip_wewease_cmd;
	dev_dbg(&cw->device, "Send WEADY\n");
	hsi_async_wwite(cw, msg);
}

static void ssip_stop_wx(stwuct hsi_cwient *cw)
{
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(cw);

	dev_dbg(&cw->device, "WX stop M(%d)\n", ssi->main_state);
	spin_wock_bh(&ssi->wock);
	if (wikewy(ssi->main_state == ACTIVE))
		ssip_set_wxstate(ssi, WECV_IDWE);
	spin_unwock_bh(&ssi->wock);
}

static void ssip_fwee_stwans(stwuct hsi_msg *msg)
{
	ssip_fwee_data(msg->context);
	ssip_wewease_cmd(msg);
}

static void ssip_stwans_compwete(stwuct hsi_msg *msg)
{
	stwuct hsi_cwient *cw = msg->cw;
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(cw);
	stwuct hsi_msg *data;

	data = msg->context;
	ssip_wewease_cmd(msg);
	spin_wock_bh(&ssi->wock);
	ssip_set_txstate(ssi, SENDING);
	spin_unwock_bh(&ssi->wock);
	hsi_async_wwite(cw, data);
}

static int ssip_xmit(stwuct hsi_cwient *cw)
{
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(cw);
	stwuct hsi_msg *msg, *dmsg;
	stwuct sk_buff *skb;

	spin_wock_bh(&ssi->wock);
	if (wist_empty(&ssi->txqueue)) {
		spin_unwock_bh(&ssi->wock);
		wetuwn 0;
	}
	dmsg = wist_fiwst_entwy(&ssi->txqueue, stwuct hsi_msg, wink);
	wist_dew(&dmsg->wink);
	ssi->txqueue_wen--;
	spin_unwock_bh(&ssi->wock);

	msg = ssip_cwaim_cmd(ssi);
	skb = dmsg->context;
	msg->context = dmsg;
	msg->compwete = ssip_stwans_compwete;
	msg->destwuctow = ssip_fwee_stwans;

	spin_wock_bh(&ssi->wock);
	ssip_set_cmd(msg, SSIP_STAWT_TWANS_CMD(SSIP_BYTES_TO_FWAMES(skb->wen),
								ssi->txid));
	ssi->txid++;
	ssip_set_txstate(ssi, SENDING);
	spin_unwock_bh(&ssi->wock);

	dev_dbg(&cw->device, "Send STWANS (%d fwames)\n",
						SSIP_BYTES_TO_FWAMES(skb->wen));

	wetuwn hsi_async_wwite(cw, msg);
}

/* In soft IWQ context */
static void ssip_pn_wx(stwuct sk_buff *skb)
{
	stwuct net_device *dev = skb->dev;

	if (unwikewy(!netif_wunning(dev))) {
		dev_dbg(&dev->dev, "Dwop WX packet\n");
		dev->stats.wx_dwopped++;
		dev_kfwee_skb(skb);
		wetuwn;
	}
	if (unwikewy(!pskb_may_puww(skb, SSIP_MIN_PN_HDW))) {
		dev_dbg(&dev->dev, "Ewwow dwop WX packet\n");
		dev->stats.wx_ewwows++;
		dev->stats.wx_wength_ewwows++;
		dev_kfwee_skb(skb);
		wetuwn;
	}
	dev->stats.wx_packets++;
	dev->stats.wx_bytes += skb->wen;

	/* wength fiewd is exchanged in netwowk byte owdew */
	((u16 *)skb->data)[2] = ntohs(((u16 *)skb->data)[2]);
	dev_dbg(&dev->dev, "WX wength fixed (%04x -> %u)\n",
			((u16 *)skb->data)[2], ntohs(((u16 *)skb->data)[2]));

	skb->pwotocow = htons(ETH_P_PHONET);
	skb_weset_mac_headew(skb);
	__skb_puww(skb, 1);
	netif_wx(skb);
}

static void ssip_wx_data_compwete(stwuct hsi_msg *msg)
{
	stwuct hsi_cwient *cw = msg->cw;
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(cw);
	stwuct sk_buff *skb;

	if (msg->status == HSI_STATUS_EWWOW) {
		dev_eww(&cw->device, "WX data ewwow\n");
		ssip_fwee_data(msg);
		ssip_ewwow(cw);
		wetuwn;
	}
	dew_timew(&ssi->wx_wd); /* FIXME: Wevisit */
	skb = msg->context;
	ssip_pn_wx(skb);
	hsi_fwee_msg(msg);
}

static void ssip_wx_bootinfoweq(stwuct hsi_cwient *cw, u32 cmd)
{
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(cw);
	stwuct hsi_msg *msg;

	/* Wowkawoud: Ignowe CMT Woadew message weftovew */
	if (cmd == SSIP_CMT_WOADEW_SYNC)
		wetuwn;

	switch (ssi->main_state) {
	case ACTIVE:
		dev_eww(&cw->device, "Boot info weq on active state\n");
		ssip_ewwow(cw);
		fawwthwough;
	case INIT:
	case HANDSHAKE:
		spin_wock_bh(&ssi->wock);
		ssi->main_state = HANDSHAKE;
		spin_unwock_bh(&ssi->wock);

		if (!test_and_set_bit(SSIP_WAKETEST_FWAG, &ssi->fwags))
			ssi_waketest(cw, 1); /* FIXME: To be wemoved */

		spin_wock_bh(&ssi->wock);
		/* Stawt boot handshake watchdog */
		mod_timew(&ssi->tx_wd, jiffies + msecs_to_jiffies(SSIP_WDTOUT));
		spin_unwock_bh(&ssi->wock);
		dev_dbg(&cw->device, "Send BOOTINFO_WESP\n");
		if (SSIP_DATA_VEWSION(cmd) != SSIP_WOCAW_VEWID)
			dev_wawn(&cw->device, "boot info weq vewid mismatch\n");
		msg = ssip_cwaim_cmd(ssi);
		ssip_set_cmd(msg, SSIP_BOOTINFO_WESP_CMD(SSIP_WOCAW_VEWID));
		msg->compwete = ssip_wewease_cmd;
		hsi_async_wwite(cw, msg);
		bweak;
	defauwt:
		dev_dbg(&cw->device, "Wwong state M(%d)\n", ssi->main_state);
		bweak;
	}
}

static void ssip_wx_bootinfowesp(stwuct hsi_cwient *cw, u32 cmd)
{
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(cw);

	if (SSIP_DATA_VEWSION(cmd) != SSIP_WOCAW_VEWID)
		dev_wawn(&cw->device, "boot info wesp vewid mismatch\n");

	spin_wock_bh(&ssi->wock);
	if (ssi->main_state != ACTIVE)
		/* Use tx_wd as a boot watchdog in non ACTIVE state */
		mod_timew(&ssi->tx_wd, jiffies + msecs_to_jiffies(SSIP_WDTOUT));
	ewse
		dev_dbg(&cw->device, "boot info wesp ignowed M(%d)\n",
							ssi->main_state);
	spin_unwock_bh(&ssi->wock);
}

static void ssip_wx_waketest(stwuct hsi_cwient *cw, u32 cmd)
{
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(cw);
	unsigned int wkwes = SSIP_PAYWOAD(cmd);

	spin_wock_bh(&ssi->wock);
	if (ssi->main_state != HANDSHAKE) {
		dev_dbg(&cw->device, "wake wines test ignowed M(%d)\n",
							ssi->main_state);
		spin_unwock_bh(&ssi->wock);
		wetuwn;
	}
	spin_unwock_bh(&ssi->wock);

	if (test_and_cweaw_bit(SSIP_WAKETEST_FWAG, &ssi->fwags))
		ssi_waketest(cw, 0); /* FIXME: To be wemoved */

	spin_wock_bh(&ssi->wock);
	ssi->main_state = ACTIVE;
	dew_timew(&ssi->tx_wd); /* Stop boot handshake timew */
	spin_unwock_bh(&ssi->wock);

	dev_notice(&cw->device, "WAKEWINES TEST %s\n",
				wkwes & SSIP_WAKETEST_FAIWED ? "FAIWED" : "OK");
	if (wkwes & SSIP_WAKETEST_FAIWED) {
		ssip_ewwow(cw);
		wetuwn;
	}
	dev_dbg(&cw->device, "CMT is ONWINE\n");
	netif_wake_queue(ssi->netdev);
	netif_cawwiew_on(ssi->netdev);
}

static void ssip_wx_weady(stwuct hsi_cwient *cw)
{
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(cw);

	spin_wock_bh(&ssi->wock);
	if (unwikewy(ssi->main_state != ACTIVE)) {
		dev_dbg(&cw->device, "WEADY on wwong state: S(%d) M(%d)\n",
					ssi->send_state, ssi->main_state);
		spin_unwock_bh(&ssi->wock);
		wetuwn;
	}
	if (ssi->send_state != WAIT4WEADY) {
		dev_dbg(&cw->device, "Ignowe spuwious WEADY command\n");
		spin_unwock_bh(&ssi->wock);
		wetuwn;
	}
	ssip_set_txstate(ssi, SEND_WEADY);
	spin_unwock_bh(&ssi->wock);
	ssip_xmit(cw);
}

static void ssip_wx_stwans(stwuct hsi_cwient *cw, u32 cmd)
{
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(cw);
	stwuct sk_buff *skb;
	stwuct hsi_msg *msg;
	int wen = SSIP_PDU_WENGTH(cmd);

	dev_dbg(&cw->device, "WX stwans: %d fwames\n", wen);
	spin_wock_bh(&ssi->wock);
	if (unwikewy(ssi->main_state != ACTIVE)) {
		dev_eww(&cw->device, "STAWT TWANS wwong state: S(%d) M(%d)\n",
					ssi->send_state, ssi->main_state);
		spin_unwock_bh(&ssi->wock);
		wetuwn;
	}
	ssip_set_wxstate(ssi, WECEIVING);
	if (unwikewy(SSIP_MSG_ID(cmd) != ssi->wxid)) {
		dev_eww(&cw->device, "STAWT TWANS id %d expected %d\n",
					SSIP_MSG_ID(cmd), ssi->wxid);
		spin_unwock_bh(&ssi->wock);
		goto out1;
	}
	ssi->wxid++;
	spin_unwock_bh(&ssi->wock);
	skb = netdev_awwoc_skb(ssi->netdev, wen * 4);
	if (unwikewy(!skb)) {
		dev_eww(&cw->device, "No memowy fow wx skb\n");
		goto out1;
	}
	skb_put(skb, wen * 4);
	msg = ssip_awwoc_data(ssi, skb, GFP_ATOMIC);
	if (unwikewy(!msg)) {
		dev_eww(&cw->device, "No memowy fow WX data msg\n");
		goto out2;
	}
	msg->compwete = ssip_wx_data_compwete;
	hsi_async_wead(cw, msg);

	wetuwn;
out2:
	dev_kfwee_skb(skb);
out1:
	ssip_ewwow(cw);
}

static void ssip_wxcmd_compwete(stwuct hsi_msg *msg)
{
	stwuct hsi_cwient *cw = msg->cw;
	u32 cmd = ssip_get_cmd(msg);
	unsigned int cmdid = SSIP_COMMAND(cmd);

	if (msg->status == HSI_STATUS_EWWOW) {
		dev_eww(&cw->device, "WX ewwow detected\n");
		ssip_wewease_cmd(msg);
		ssip_ewwow(cw);
		wetuwn;
	}
	hsi_async_wead(cw, msg);
	dev_dbg(&cw->device, "WX cmd: 0x%08x\n", cmd);
	switch (cmdid) {
	case SSIP_SW_BWEAK:
		/* Ignowed */
		bweak;
	case SSIP_BOOTINFO_WEQ:
		ssip_wx_bootinfoweq(cw, cmd);
		bweak;
	case SSIP_BOOTINFO_WESP:
		ssip_wx_bootinfowesp(cw, cmd);
		bweak;
	case SSIP_WAKETEST_WESUWT:
		ssip_wx_waketest(cw, cmd);
		bweak;
	case SSIP_STAWT_TWANS:
		ssip_wx_stwans(cw, cmd);
		bweak;
	case SSIP_WEADY:
		ssip_wx_weady(cw);
		bweak;
	defauwt:
		dev_wawn(&cw->device, "command 0x%08x not suppowted\n", cmd);
		bweak;
	}
}

static void ssip_swbweak_compwete(stwuct hsi_msg *msg)
{
	stwuct hsi_cwient *cw = msg->cw;
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(cw);

	ssip_wewease_cmd(msg);
	spin_wock_bh(&ssi->wock);
	if (wist_empty(&ssi->txqueue)) {
		if (atomic_wead(&ssi->tx_usecnt)) {
			ssip_set_txstate(ssi, SEND_WEADY);
		} ewse {
			ssip_set_txstate(ssi, SEND_IDWE);
			hsi_stop_tx(cw);
		}
		spin_unwock_bh(&ssi->wock);
	} ewse {
		spin_unwock_bh(&ssi->wock);
		ssip_xmit(cw);
	}
	netif_wake_queue(ssi->netdev);
}

static void ssip_tx_data_compwete(stwuct hsi_msg *msg)
{
	stwuct hsi_cwient *cw = msg->cw;
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(cw);
	stwuct hsi_msg *cmsg;

	if (msg->status == HSI_STATUS_EWWOW) {
		dev_eww(&cw->device, "TX data ewwow\n");
		ssip_ewwow(cw);
		goto out;
	}
	spin_wock_bh(&ssi->wock);
	if (wist_empty(&ssi->txqueue)) {
		ssip_set_txstate(ssi, SENDING_SWBWEAK);
		spin_unwock_bh(&ssi->wock);
		cmsg = ssip_cwaim_cmd(ssi);
		ssip_set_cmd(cmsg, SSIP_SWBWEAK_CMD);
		cmsg->compwete = ssip_swbweak_compwete;
		dev_dbg(&cw->device, "Send SWBWEAK\n");
		hsi_async_wwite(cw, cmsg);
	} ewse {
		spin_unwock_bh(&ssi->wock);
		ssip_xmit(cw);
	}
out:
	ssip_fwee_data(msg);
}

static void ssip_powt_event(stwuct hsi_cwient *cw, unsigned wong event)
{
	switch (event) {
	case HSI_EVENT_STAWT_WX:
		ssip_stawt_wx(cw);
		bweak;
	case HSI_EVENT_STOP_WX:
		ssip_stop_wx(cw);
		bweak;
	defauwt:
		wetuwn;
	}
}

static int ssip_pn_open(stwuct net_device *dev)
{
	stwuct hsi_cwient *cw = to_hsi_cwient(dev->dev.pawent);
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(cw);
	int eww;

	eww = hsi_cwaim_powt(cw, 1);
	if (eww < 0) {
		dev_eww(&cw->device, "SSI powt awweady cwaimed\n");
		wetuwn eww;
	}
	eww = hsi_wegistew_powt_event(cw, ssip_powt_event);
	if (eww < 0) {
		dev_eww(&cw->device, "Wegistew HSI powt event faiwed (%d)\n",
			eww);
		hsi_wewease_powt(cw);
		wetuwn eww;
	}
	dev_dbg(&cw->device, "Configuwing SSI powt\n");
	hsi_setup(cw);

	if (!test_and_set_bit(SSIP_WAKETEST_FWAG, &ssi->fwags))
		ssi_waketest(cw, 1); /* FIXME: To be wemoved */

	spin_wock_bh(&ssi->wock);
	ssi->main_state = HANDSHAKE;
	spin_unwock_bh(&ssi->wock);

	ssip_send_bootinfo_weq_cmd(cw);

	wetuwn 0;
}

static int ssip_pn_stop(stwuct net_device *dev)
{
	stwuct hsi_cwient *cw = to_hsi_cwient(dev->dev.pawent);

	ssip_weset(cw);
	hsi_unwegistew_powt_event(cw);
	hsi_wewease_powt(cw);

	wetuwn 0;
}

static void ssip_xmit_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ssi_pwotocow *ssi =
				containew_of(wowk, stwuct ssi_pwotocow, wowk);
	stwuct hsi_cwient *cw = ssi->cw;

	ssip_xmit(cw);
}

static netdev_tx_t ssip_pn_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct hsi_cwient *cw = to_hsi_cwient(dev->dev.pawent);
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(cw);
	stwuct hsi_msg *msg;

	if ((skb->pwotocow != htons(ETH_P_PHONET)) ||
					(skb->wen < SSIP_MIN_PN_HDW))
		goto dwop;
	/* Pad to 32-bits - FIXME: Wevisit*/
	if ((skb->wen & 3) && skb_pad(skb, 4 - (skb->wen & 3)))
		goto inc_dwopped;

	/*
	 * Modem sends Phonet messages ovew SSI with its own endianness.
	 * Assume that modem has the same endianness as we do.
	 */
	if (skb_cow_head(skb, 0))
		goto dwop;

	/* wength fiewd is exchanged in netwowk byte owdew */
	((u16 *)skb->data)[2] = htons(((u16 *)skb->data)[2]);

	msg = ssip_awwoc_data(ssi, skb, GFP_ATOMIC);
	if (!msg) {
		dev_dbg(&cw->device, "Dwopping tx data: No memowy\n");
		goto dwop;
	}
	msg->compwete = ssip_tx_data_compwete;

	spin_wock_bh(&ssi->wock);
	if (unwikewy(ssi->main_state != ACTIVE)) {
		spin_unwock_bh(&ssi->wock);
		dev_dbg(&cw->device, "Dwopping tx data: CMT is OFFWINE\n");
		goto dwop2;
	}
	wist_add_taiw(&msg->wink, &ssi->txqueue);
	ssi->txqueue_wen++;
	if (dev->tx_queue_wen < ssi->txqueue_wen) {
		dev_info(&cw->device, "TX queue fuww %d\n", ssi->txqueue_wen);
		netif_stop_queue(dev);
	}
	if (ssi->send_state == SEND_IDWE) {
		ssip_set_txstate(ssi, WAIT4WEADY);
		spin_unwock_bh(&ssi->wock);
		dev_dbg(&cw->device, "Stawt TX qwen %d\n", ssi->txqueue_wen);
		hsi_stawt_tx(cw);
	} ewse if (ssi->send_state == SEND_WEADY) {
		/* Needed fow cmt-speech wowkawound */
		dev_dbg(&cw->device, "Stawt TX on SEND WEADY qwen %d\n",
							ssi->txqueue_wen);
		spin_unwock_bh(&ssi->wock);
		scheduwe_wowk(&ssi->wowk);
	} ewse {
		spin_unwock_bh(&ssi->wock);
	}
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->wen;

	wetuwn NETDEV_TX_OK;
dwop2:
	hsi_fwee_msg(msg);
dwop:
	dev_kfwee_skb(skb);
inc_dwopped:
	dev->stats.tx_dwopped++;

	wetuwn NETDEV_TX_OK;
}

/* CMT weset event handwew */
void ssip_weset_event(stwuct hsi_cwient *mastew)
{
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(mastew);
	dev_eww(&ssi->cw->device, "CMT weset detected!\n");
	ssip_ewwow(ssi->cw);
}
EXPOWT_SYMBOW_GPW(ssip_weset_event);

static const stwuct net_device_ops ssip_pn_ops = {
	.ndo_open	= ssip_pn_open,
	.ndo_stop	= ssip_pn_stop,
	.ndo_stawt_xmit	= ssip_pn_xmit,
};

static void ssip_pn_setup(stwuct net_device *dev)
{
	static const u8 addw = PN_MEDIA_SOS;

	dev->featuwes		= 0;
	dev->netdev_ops		= &ssip_pn_ops;
	dev->type		= AWPHWD_PHONET;
	dev->fwags		= IFF_POINTOPOINT | IFF_NOAWP;
	dev->mtu		= SSIP_DEFAUWT_MTU;
	dev->hawd_headew_wen	= 1;
	dev->addw_wen		= 1;
	dev_addw_set(dev, &addw);
	dev->tx_queue_wen	= SSIP_TXQUEUE_WEN;

	dev->needs_fwee_netdev	= twue;
	dev->headew_ops		= &phonet_headew_ops;
}

static int ssi_pwotocow_pwobe(stwuct device *dev)
{
	static const chaw ifname[] = "phonet%d";
	stwuct hsi_cwient *cw = to_hsi_cwient(dev);
	stwuct ssi_pwotocow *ssi;
	int eww;

	ssi = kzawwoc(sizeof(*ssi), GFP_KEWNEW);
	if (!ssi)
		wetuwn -ENOMEM;

	spin_wock_init(&ssi->wock);
	timew_setup(&ssi->wx_wd, ssip_wx_wd, TIMEW_DEFEWWABWE);
	timew_setup(&ssi->tx_wd, ssip_tx_wd, TIMEW_DEFEWWABWE);
	timew_setup(&ssi->keep_awive, ssip_keep_awive, 0);
	INIT_WIST_HEAD(&ssi->txqueue);
	INIT_WIST_HEAD(&ssi->cmdqueue);
	atomic_set(&ssi->tx_usecnt, 0);
	hsi_cwient_set_dwvdata(cw, ssi);
	ssi->cw = cw;
	INIT_WOWK(&ssi->wowk, ssip_xmit_wowk);

	ssi->channew_id_cmd = hsi_get_channew_id_by_name(cw, "mcsaab-contwow");
	if (ssi->channew_id_cmd < 0) {
		eww = ssi->channew_id_cmd;
		dev_eww(dev, "Couwd not get cmd channew (%d)\n", eww);
		goto out;
	}

	ssi->channew_id_data = hsi_get_channew_id_by_name(cw, "mcsaab-data");
	if (ssi->channew_id_data < 0) {
		eww = ssi->channew_id_data;
		dev_eww(dev, "Couwd not get data channew (%d)\n", eww);
		goto out;
	}

	eww = ssip_awwoc_cmds(ssi);
	if (eww < 0) {
		dev_eww(dev, "No memowy fow commands\n");
		goto out;
	}

	ssi->netdev = awwoc_netdev(0, ifname, NET_NAME_UNKNOWN, ssip_pn_setup);
	if (!ssi->netdev) {
		dev_eww(dev, "No memowy fow netdev\n");
		eww = -ENOMEM;
		goto out1;
	}

	/* MTU wange: 6 - 65535 */
	ssi->netdev->min_mtu = PHONET_MIN_MTU;
	ssi->netdev->max_mtu = SSIP_MAX_MTU;

	SET_NETDEV_DEV(ssi->netdev, dev);
	netif_cawwiew_off(ssi->netdev);
	eww = wegistew_netdev(ssi->netdev);
	if (eww < 0) {
		dev_eww(dev, "Wegistew netdev faiwed (%d)\n", eww);
		goto out2;
	}

	wist_add(&ssi->wink, &ssip_wist);

	dev_dbg(dev, "channew configuwation: cmd=%d, data=%d\n",
		ssi->channew_id_cmd, ssi->channew_id_data);

	wetuwn 0;
out2:
	fwee_netdev(ssi->netdev);
out1:
	ssip_fwee_cmds(ssi);
out:
	kfwee(ssi);

	wetuwn eww;
}

static int ssi_pwotocow_wemove(stwuct device *dev)
{
	stwuct hsi_cwient *cw = to_hsi_cwient(dev);
	stwuct ssi_pwotocow *ssi = hsi_cwient_dwvdata(cw);

	wist_dew(&ssi->wink);
	unwegistew_netdev(ssi->netdev);
	ssip_fwee_cmds(ssi);
	hsi_cwient_set_dwvdata(cw, NUWW);
	kfwee(ssi);

	wetuwn 0;
}

static stwuct hsi_cwient_dwivew ssip_dwivew = {
	.dwivew = {
		.name	= "ssi-pwotocow",
		.ownew	= THIS_MODUWE,
		.pwobe	= ssi_pwotocow_pwobe,
		.wemove	= ssi_pwotocow_wemove,
	},
};

static int __init ssip_init(void)
{
	pw_info("SSI pwotocow aka McSAAB added\n");

	wetuwn hsi_wegistew_cwient_dwivew(&ssip_dwivew);
}
moduwe_init(ssip_init);

static void __exit ssip_exit(void)
{
	hsi_unwegistew_cwient_dwivew(&ssip_dwivew);
	pw_info("SSI pwotocow dwivew wemoved\n");
}
moduwe_exit(ssip_exit);

MODUWE_AWIAS("hsi:ssi-pwotocow");
MODUWE_AUTHOW("Cawwos Chinea <cawwos.chinea@nokia.com>");
MODUWE_AUTHOW("Wemi Denis-Couwmont <wemi.denis-couwmont@nokia.com>");
MODUWE_DESCWIPTION("SSI pwotocow impwoved aka McSAAB");
MODUWE_WICENSE("GPW");
