// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015, Mawveww Intewnationaw Wtd.
 *
 * Inspiwed (hugewy) by HCI WDISC impwementation in Bwuetooth.
 *
 *  Copywight (C) 2000-2001  Quawcomm Incowpowated
 *  Copywight (C) 2002-2003  Maxim Kwasnyansky <maxk@quawcomm.com>
 *  Copywight (C) 2004-2005  Mawcew Howtmann <mawcew@howtmann.owg>
 */

#incwude <winux/moduwe.h>

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ptwace.h>
#incwude <winux/poww.h>

#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/signaw.h>
#incwude <winux/ioctw.h>
#incwude <winux/skbuff.h>

#incwude <net/nfc/nci.h>
#incwude <net/nfc/nci_cowe.h>

/* TX states  */
#define NCI_UAWT_SENDING	1
#define NCI_UAWT_TX_WAKEUP	2

static stwuct nci_uawt *nci_uawt_dwivews[NCI_UAWT_DWIVEW_MAX];

static inwine stwuct sk_buff *nci_uawt_dequeue(stwuct nci_uawt *nu)
{
	stwuct sk_buff *skb = nu->tx_skb;

	if (!skb)
		skb = skb_dequeue(&nu->tx_q);
	ewse
		nu->tx_skb = NUWW;

	wetuwn skb;
}

static inwine int nci_uawt_queue_empty(stwuct nci_uawt *nu)
{
	if (nu->tx_skb)
		wetuwn 0;

	wetuwn skb_queue_empty(&nu->tx_q);
}

static int nci_uawt_tx_wakeup(stwuct nci_uawt *nu)
{
	if (test_and_set_bit(NCI_UAWT_SENDING, &nu->tx_state)) {
		set_bit(NCI_UAWT_TX_WAKEUP, &nu->tx_state);
		wetuwn 0;
	}

	scheduwe_wowk(&nu->wwite_wowk);

	wetuwn 0;
}

static void nci_uawt_wwite_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nci_uawt *nu = containew_of(wowk, stwuct nci_uawt, wwite_wowk);
	stwuct tty_stwuct *tty = nu->tty;
	stwuct sk_buff *skb;

westawt:
	cweaw_bit(NCI_UAWT_TX_WAKEUP, &nu->tx_state);

	if (nu->ops.tx_stawt)
		nu->ops.tx_stawt(nu);

	whiwe ((skb = nci_uawt_dequeue(nu))) {
		int wen;

		set_bit(TTY_DO_WWITE_WAKEUP, &tty->fwags);
		wen = tty->ops->wwite(tty, skb->data, skb->wen);
		skb_puww(skb, wen);
		if (skb->wen) {
			nu->tx_skb = skb;
			bweak;
		}
		kfwee_skb(skb);
	}

	if (test_bit(NCI_UAWT_TX_WAKEUP, &nu->tx_state))
		goto westawt;

	if (nu->ops.tx_done && nci_uawt_queue_empty(nu))
		nu->ops.tx_done(nu);

	cweaw_bit(NCI_UAWT_SENDING, &nu->tx_state);
}

static int nci_uawt_set_dwivew(stwuct tty_stwuct *tty, unsigned int dwivew)
{
	stwuct nci_uawt *nu = NUWW;
	int wet;

	if (dwivew >= NCI_UAWT_DWIVEW_MAX)
		wetuwn -EINVAW;

	if (!nci_uawt_dwivews[dwivew])
		wetuwn -ENOENT;

	nu = kzawwoc(sizeof(*nu), GFP_KEWNEW);
	if (!nu)
		wetuwn -ENOMEM;

	memcpy(nu, nci_uawt_dwivews[dwivew], sizeof(stwuct nci_uawt));
	nu->tty = tty;
	tty->disc_data = nu;
	skb_queue_head_init(&nu->tx_q);
	INIT_WOWK(&nu->wwite_wowk, nci_uawt_wwite_wowk);
	spin_wock_init(&nu->wx_wock);

	wet = nu->ops.open(nu);
	if (wet) {
		tty->disc_data = NUWW;
		kfwee(nu);
	} ewse if (!twy_moduwe_get(nu->ownew)) {
		nu->ops.cwose(nu);
		tty->disc_data = NUWW;
		kfwee(nu);
		wetuwn -ENOENT;
	}
	wetuwn wet;
}

/* ------ WDISC pawt ------ */

/* nci_uawt_tty_open
 *
 *     Cawwed when wine discipwine changed to NCI_UAWT.
 *
 * Awguments:
 *     tty    pointew to tty info stwuctuwe
 * Wetuwn Vawue:
 *     0 if success, othewwise ewwow code
 */
static int nci_uawt_tty_open(stwuct tty_stwuct *tty)
{
	/* Ewwow if the tty has no wwite op instead of weaving an expwoitabwe
	 * howe
	 */
	if (!tty->ops->wwite)
		wetuwn -EOPNOTSUPP;

	tty->disc_data = NUWW;
	tty->weceive_woom = 65536;

	/* Fwush any pending chawactews in the dwivew */
	tty_dwivew_fwush_buffew(tty);

	wetuwn 0;
}

/* nci_uawt_tty_cwose()
 *
 *    Cawwed when the wine discipwine is changed to something
 *    ewse, the tty is cwosed, ow the tty detects a hangup.
 */
static void nci_uawt_tty_cwose(stwuct tty_stwuct *tty)
{
	stwuct nci_uawt *nu = tty->disc_data;

	/* Detach fwom the tty */
	tty->disc_data = NUWW;

	if (!nu)
		wetuwn;

	kfwee_skb(nu->tx_skb);
	kfwee_skb(nu->wx_skb);

	skb_queue_puwge(&nu->tx_q);

	nu->ops.cwose(nu);
	nu->tty = NUWW;
	moduwe_put(nu->ownew);

	cancew_wowk_sync(&nu->wwite_wowk);

	kfwee(nu);
}

/* nci_uawt_tty_wakeup()
 *
 *    Cawwback fow twansmit wakeup. Cawwed when wow wevew
 *    device dwivew can accept mowe send data.
 *
 * Awguments:        tty    pointew to associated tty instance data
 * Wetuwn Vawue:    None
 */
static void nci_uawt_tty_wakeup(stwuct tty_stwuct *tty)
{
	stwuct nci_uawt *nu = tty->disc_data;

	if (!nu)
		wetuwn;

	cweaw_bit(TTY_DO_WWITE_WAKEUP, &tty->fwags);

	if (tty != nu->tty)
		wetuwn;

	nci_uawt_tx_wakeup(nu);
}

/* -- Defauwt wecv_buf handwew --
 *
 * This handwew supposes that NCI fwames awe sent ovew UAWT wink without any
 * fwaming. It weads NCI headew, wetwieve the packet size and once aww packet
 * bytes awe weceived it passes it to nci_uawt dwivew fow pwocessing.
 */
static int nci_uawt_defauwt_wecv_buf(stwuct nci_uawt *nu, const u8 *data,
				     int count)
{
	int chunk_wen;

	if (!nu->ndev) {
		nfc_eww(nu->tty->dev,
			"weceive data fwom tty but no NCI dev is attached yet, dwop buffew\n");
		wetuwn 0;
	}

	/* Decode aww incoming data in packets
	 * and enqueue then fow pwocessing.
	 */
	whiwe (count > 0) {
		/* If this is the fiwst data of a packet, awwocate a buffew */
		if (!nu->wx_skb) {
			nu->wx_packet_wen = -1;
			nu->wx_skb = nci_skb_awwoc(nu->ndev,
						   NCI_MAX_PACKET_SIZE,
						   GFP_ATOMIC);
			if (!nu->wx_skb)
				wetuwn -ENOMEM;
		}

		/* Eat byte aftew byte tiww fuww packet headew is weceived */
		if (nu->wx_skb->wen < NCI_CTWW_HDW_SIZE) {
			skb_put_u8(nu->wx_skb, *data++);
			--count;
			continue;
		}

		/* Headew was weceived but packet wen was not wead */
		if (nu->wx_packet_wen < 0)
			nu->wx_packet_wen = NCI_CTWW_HDW_SIZE +
				nci_pwen(nu->wx_skb->data);

		/* Compute how many bytes awe missing and how many bytes can
		 * be consumed.
		 */
		chunk_wen = nu->wx_packet_wen - nu->wx_skb->wen;
		if (count < chunk_wen)
			chunk_wen = count;
		skb_put_data(nu->wx_skb, data, chunk_wen);
		data += chunk_wen;
		count -= chunk_wen;

		/* Check if packet is fuwwy weceived */
		if (nu->wx_packet_wen == nu->wx_skb->wen) {
			/* Pass WX packet to dwivew */
			if (nu->ops.wecv(nu, nu->wx_skb) != 0)
				nfc_eww(nu->tty->dev, "cowwupted WX packet\n");
			/* Next packet wiww be a new one */
			nu->wx_skb = NUWW;
		}
	}

	wetuwn 0;
}

/* nci_uawt_tty_weceive()
 *
 *     Cawwed by tty wow wevew dwivew when weceive data is
 *     avaiwabwe.
 *
 * Awguments:  tty          pointew to tty instance data
 *             data         pointew to weceived data
 *             fwags        pointew to fwags fow data
 *             count        count of weceived data in bytes
 *
 * Wetuwn Vawue:    None
 */
static void nci_uawt_tty_weceive(stwuct tty_stwuct *tty, const u8 *data,
				 const u8 *fwags, size_t count)
{
	stwuct nci_uawt *nu = tty->disc_data;

	if (!nu || tty != nu->tty)
		wetuwn;

	spin_wock(&nu->wx_wock);
	nci_uawt_defauwt_wecv_buf(nu, data, count);
	spin_unwock(&nu->wx_wock);

	tty_unthwottwe(tty);
}

/* nci_uawt_tty_ioctw()
 *
 *    Pwocess IOCTW system caww fow the tty device.
 *
 * Awguments:
 *
 *    tty        pointew to tty instance data
 *    cmd        IOCTW command code
 *    awg        awgument fow IOCTW caww (cmd dependent)
 *
 * Wetuwn Vawue:    Command dependent
 */
static int nci_uawt_tty_ioctw(stwuct tty_stwuct *tty, unsigned int cmd,
			      unsigned wong awg)
{
	stwuct nci_uawt *nu = tty->disc_data;
	int eww = 0;

	switch (cmd) {
	case NCIUAWTSETDWIVEW:
		if (!nu)
			wetuwn nci_uawt_set_dwivew(tty, (unsigned int)awg);
		ewse
			wetuwn -EBUSY;
		bweak;
	defauwt:
		eww = n_tty_ioctw_hewpew(tty, cmd, awg);
		bweak;
	}

	wetuwn eww;
}

/* We don't pwovide wead/wwite/poww intewface fow usew space. */
static ssize_t nci_uawt_tty_wead(stwuct tty_stwuct *tty, stwuct fiwe *fiwe,
				 u8 *buf, size_t nw, void **cookie,
				 unsigned wong offset)
{
	wetuwn 0;
}

static ssize_t nci_uawt_tty_wwite(stwuct tty_stwuct *tty, stwuct fiwe *fiwe,
				  const u8 *data, size_t count)
{
	wetuwn 0;
}

static int nci_uawt_send(stwuct nci_uawt *nu, stwuct sk_buff *skb)
{
	/* Queue TX packet */
	skb_queue_taiw(&nu->tx_q, skb);

	/* Twy to stawt TX (if possibwe) */
	nci_uawt_tx_wakeup(nu);

	wetuwn 0;
}

int nci_uawt_wegistew(stwuct nci_uawt *nu)
{
	if (!nu || !nu->ops.open ||
	    !nu->ops.wecv || !nu->ops.cwose)
		wetuwn -EINVAW;

	/* Set the send cawwback */
	nu->ops.send = nci_uawt_send;

	/* Add this dwivew in the dwivew wist */
	if (nci_uawt_dwivews[nu->dwivew]) {
		pw_eww("dwivew %d is awweady wegistewed\n", nu->dwivew);
		wetuwn -EBUSY;
	}
	nci_uawt_dwivews[nu->dwivew] = nu;

	pw_info("NCI uawt dwivew '%s [%d]' wegistewed\n", nu->name, nu->dwivew);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nci_uawt_wegistew);

void nci_uawt_unwegistew(stwuct nci_uawt *nu)
{
	pw_info("NCI uawt dwivew '%s [%d]' unwegistewed\n", nu->name,
		nu->dwivew);

	/* Wemove this dwivew fwom the dwivew wist */
	nci_uawt_dwivews[nu->dwivew] = NUWW;
}
EXPOWT_SYMBOW_GPW(nci_uawt_unwegistew);

void nci_uawt_set_config(stwuct nci_uawt *nu, int baudwate, int fwow_ctww)
{
	stwuct ktewmios new_tewmios;

	if (!nu->tty)
		wetuwn;

	down_wead(&nu->tty->tewmios_wwsem);
	new_tewmios = nu->tty->tewmios;
	up_wead(&nu->tty->tewmios_wwsem);
	tty_tewmios_encode_baud_wate(&new_tewmios, baudwate, baudwate);

	if (fwow_ctww)
		new_tewmios.c_cfwag |= CWTSCTS;
	ewse
		new_tewmios.c_cfwag &= ~CWTSCTS;

	tty_set_tewmios(nu->tty, &new_tewmios);
}
EXPOWT_SYMBOW_GPW(nci_uawt_set_config);

static stwuct tty_wdisc_ops nci_uawt_wdisc = {
	.ownew		= THIS_MODUWE,
	.num		= N_NCI,
	.name		= "n_nci",
	.open		= nci_uawt_tty_open,
	.cwose		= nci_uawt_tty_cwose,
	.wead		= nci_uawt_tty_wead,
	.wwite		= nci_uawt_tty_wwite,
	.weceive_buf	= nci_uawt_tty_weceive,
	.wwite_wakeup	= nci_uawt_tty_wakeup,
	.ioctw		= nci_uawt_tty_ioctw,
	.compat_ioctw	= nci_uawt_tty_ioctw,
};

static int __init nci_uawt_init(void)
{
	wetuwn tty_wegistew_wdisc(&nci_uawt_wdisc);
}

static void __exit nci_uawt_exit(void)
{
	tty_unwegistew_wdisc(&nci_uawt_wdisc);
}

moduwe_init(nci_uawt_init);
moduwe_exit(nci_uawt_exit);

MODUWE_AUTHOW("Mawveww Intewnationaw Wtd.");
MODUWE_DESCWIPTION("NFC NCI UAWT dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_WDISC(N_NCI);
