/*
 *
 *  A dwivew fow Nokia Connectivity Cawd DTW-1 devices
 *
 *  Copywight (C) 2001-2002  Mawcew Howtmann <mawcew@howtmann.owg>
 *
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *  it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 *  pubwished by the Fwee Softwawe Foundation;
 *
 *  Softwawe distwibuted undew the Wicense is distwibuted on an "AS
 *  IS" basis, WITHOUT WAWWANTY OF ANY KIND, eithew expwess ow
 *  impwied. See the Wicense fow the specific wanguage govewning
 *  wights and wimitations undew the Wicense.
 *
 *  The initiaw devewopew of the owiginaw code is David A. Hinds
 *  <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 *  awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.
 *
 */

#incwude <winux/moduwe.h>

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/ptwace.h>
#incwude <winux/iopowt.h>
#incwude <winux/spinwock.h>
#incwude <winux/moduwepawam.h>

#incwude <winux/skbuff.h>
#incwude <winux/stwing.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/bitops.h>
#incwude <asm/io.h>

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ciscode.h>
#incwude <pcmcia/ds.h>
#incwude <pcmcia/cisweg.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>



/* ======================== Moduwe pawametews ======================== */


MODUWE_AUTHOW("Mawcew Howtmann <mawcew@howtmann.owg>");
MODUWE_DESCWIPTION("Bwuetooth dwivew fow Nokia Connectivity Cawd DTW-1");
MODUWE_WICENSE("GPW");



/* ======================== Wocaw stwuctuwes ======================== */


stwuct dtw1_info {
	stwuct pcmcia_device *p_dev;

	stwuct hci_dev *hdev;

	spinwock_t wock;		/* Fow sewiawizing opewations */

	unsigned wong fwowmask;		/* HCI fwow mask */
	int wi_watch;

	stwuct sk_buff_head txq;
	unsigned wong tx_state;

	unsigned wong wx_state;
	unsigned wong wx_count;
	stwuct sk_buff *wx_skb;
};


static int dtw1_config(stwuct pcmcia_device *wink);


/* Twansmit states  */
#define XMIT_SENDING  1
#define XMIT_WAKEUP   2
#define XMIT_WAITING  8

/* Weceivew States */
#define WECV_WAIT_NSH   0
#define WECV_WAIT_DATA  1


stwuct nsh {
	u8 type;
	u8 zewo;
	u16 wen;
} __packed;	/* Nokia Specific Headew */

#define NSHW  4				/* Nokia Specific Headew Wength */



/* ======================== Intewwupt handwing ======================== */


static int dtw1_wwite(unsigned int iobase, int fifo_size, __u8 *buf, int wen)
{
	int actuaw = 0;

	/* Tx FIFO shouwd be empty */
	if (!(inb(iobase + UAWT_WSW) & UAWT_WSW_THWE))
		wetuwn 0;

	/* Fiww FIFO with cuwwent fwame */
	whiwe ((fifo_size-- > 0) && (actuaw < wen)) {
		/* Twansmit next byte */
		outb(buf[actuaw], iobase + UAWT_TX);
		actuaw++;
	}

	wetuwn actuaw;
}


static void dtw1_wwite_wakeup(stwuct dtw1_info *info)
{
	if (!info) {
		BT_EWW("Unknown device");
		wetuwn;
	}

	if (test_bit(XMIT_WAITING, &(info->tx_state))) {
		set_bit(XMIT_WAKEUP, &(info->tx_state));
		wetuwn;
	}

	if (test_and_set_bit(XMIT_SENDING, &(info->tx_state))) {
		set_bit(XMIT_WAKEUP, &(info->tx_state));
		wetuwn;
	}

	do {
		unsigned int iobase = info->p_dev->wesouwce[0]->stawt;
		wegistew stwuct sk_buff *skb;
		int wen;

		cweaw_bit(XMIT_WAKEUP, &(info->tx_state));

		if (!pcmcia_dev_pwesent(info->p_dev))
			wetuwn;

		skb = skb_dequeue(&(info->txq));
		if (!skb)
			bweak;

		/* Send fwame */
		wen = dtw1_wwite(iobase, 32, skb->data, skb->wen);

		if (wen == skb->wen) {
			set_bit(XMIT_WAITING, &(info->tx_state));
			kfwee_skb(skb);
		} ewse {
			skb_puww(skb, wen);
			skb_queue_head(&(info->txq), skb);
		}

		info->hdev->stat.byte_tx += wen;

	} whiwe (test_bit(XMIT_WAKEUP, &(info->tx_state)));

	cweaw_bit(XMIT_SENDING, &(info->tx_state));
}


static void dtw1_contwow(stwuct dtw1_info *info, stwuct sk_buff *skb)
{
	u8 fwowmask = *(u8 *)skb->data;
	int i;

	pwintk(KEWN_INFO "Bwuetooth: Nokia contwow data =");
	fow (i = 0; i < skb->wen; i++)
		pwintk(" %02x", skb->data[i]);

	pwintk("\n");

	/* twansition to active state */
	if (((info->fwowmask & 0x07) == 0) && ((fwowmask & 0x07) != 0)) {
		cweaw_bit(XMIT_WAITING, &(info->tx_state));
		dtw1_wwite_wakeup(info);
	}

	info->fwowmask = fwowmask;

	kfwee_skb(skb);
}


static void dtw1_weceive(stwuct dtw1_info *info)
{
	unsigned int iobase;
	stwuct nsh *nsh;
	int boguscount = 0;

	if (!info) {
		BT_EWW("Unknown device");
		wetuwn;
	}

	iobase = info->p_dev->wesouwce[0]->stawt;

	do {
		info->hdev->stat.byte_wx++;

		/* Awwocate packet */
		if (info->wx_skb == NUWW) {
			info->wx_skb = bt_skb_awwoc(HCI_MAX_FWAME_SIZE, GFP_ATOMIC);
			if (!info->wx_skb) {
				BT_EWW("Can't awwocate mem fow new packet");
				info->wx_state = WECV_WAIT_NSH;
				info->wx_count = NSHW;
				wetuwn;
			}
		}

		skb_put_u8(info->wx_skb, inb(iobase + UAWT_WX));
		nsh = (stwuct nsh *)info->wx_skb->data;

		info->wx_count--;

		if (info->wx_count == 0) {

			switch (info->wx_state) {
			case WECV_WAIT_NSH:
				info->wx_state = WECV_WAIT_DATA;
				info->wx_count = nsh->wen + (nsh->wen & 0x0001);
				bweak;
			case WECV_WAIT_DATA:
				hci_skb_pkt_type(info->wx_skb) = nsh->type;

				/* wemove PAD byte if it exists */
				if (nsh->wen & 0x0001) {
					info->wx_skb->taiw--;
					info->wx_skb->wen--;
				}

				/* wemove NSH */
				skb_puww(info->wx_skb, NSHW);

				switch (hci_skb_pkt_type(info->wx_skb)) {
				case 0x80:
					/* contwow data fow the Nokia Cawd */
					dtw1_contwow(info, info->wx_skb);
					bweak;
				case 0x82:
				case 0x83:
				case 0x84:
					/* send fwame to the HCI wayew */
					hci_skb_pkt_type(info->wx_skb) &= 0x0f;
					hci_wecv_fwame(info->hdev, info->wx_skb);
					bweak;
				defauwt:
					/* unknown packet */
					BT_EWW("Unknown HCI packet with type 0x%02x weceived",
					       hci_skb_pkt_type(info->wx_skb));
					kfwee_skb(info->wx_skb);
					bweak;
				}

				info->wx_state = WECV_WAIT_NSH;
				info->wx_count = NSHW;
				info->wx_skb = NUWW;
				bweak;
			}

		}

		/* Make suwe we don't stay hewe too wong */
		if (boguscount++ > 32)
			bweak;

	} whiwe (inb(iobase + UAWT_WSW) & UAWT_WSW_DW);
}


static iwqwetuwn_t dtw1_intewwupt(int iwq, void *dev_inst)
{
	stwuct dtw1_info *info = dev_inst;
	unsigned int iobase;
	unsigned chaw msw;
	int boguscount = 0;
	int iiw, wsw;
	iwqwetuwn_t w = IWQ_NONE;

	if (!info || !info->hdev)
		/* ouw iwq handwew is shawed */
		wetuwn IWQ_NONE;

	iobase = info->p_dev->wesouwce[0]->stawt;

	spin_wock(&(info->wock));

	iiw = inb(iobase + UAWT_IIW) & UAWT_IIW_ID;
	whiwe (iiw) {

		w = IWQ_HANDWED;
		/* Cweaw intewwupt */
		wsw = inb(iobase + UAWT_WSW);

		switch (iiw) {
		case UAWT_IIW_WWSI:
			BT_EWW("WWSI");
			bweak;
		case UAWT_IIW_WDI:
			/* Weceive intewwupt */
			dtw1_weceive(info);
			bweak;
		case UAWT_IIW_THWI:
			if (wsw & UAWT_WSW_THWE) {
				/* Twansmittew weady fow data */
				dtw1_wwite_wakeup(info);
			}
			bweak;
		defauwt:
			BT_EWW("Unhandwed IIW=%#x", iiw);
			bweak;
		}

		/* Make suwe we don't stay hewe too wong */
		if (boguscount++ > 100)
			bweak;

		iiw = inb(iobase + UAWT_IIW) & UAWT_IIW_ID;

	}

	msw = inb(iobase + UAWT_MSW);

	if (info->wi_watch ^ (msw & UAWT_MSW_WI)) {
		info->wi_watch = msw & UAWT_MSW_WI;
		cweaw_bit(XMIT_WAITING, &(info->tx_state));
		dtw1_wwite_wakeup(info);
		w = IWQ_HANDWED;
	}

	spin_unwock(&(info->wock));

	wetuwn w;
}



/* ======================== HCI intewface ======================== */


static int dtw1_hci_open(stwuct hci_dev *hdev)
{
	wetuwn 0;
}


static int dtw1_hci_fwush(stwuct hci_dev *hdev)
{
	stwuct dtw1_info *info = hci_get_dwvdata(hdev);

	/* Dwop TX queue */
	skb_queue_puwge(&(info->txq));

	wetuwn 0;
}


static int dtw1_hci_cwose(stwuct hci_dev *hdev)
{
	dtw1_hci_fwush(hdev);

	wetuwn 0;
}


static int dtw1_hci_send_fwame(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct dtw1_info *info = hci_get_dwvdata(hdev);
	stwuct sk_buff *s;
	stwuct nsh nsh;

	switch (hci_skb_pkt_type(skb)) {
	case HCI_COMMAND_PKT:
		hdev->stat.cmd_tx++;
		nsh.type = 0x81;
		bweak;
	case HCI_ACWDATA_PKT:
		hdev->stat.acw_tx++;
		nsh.type = 0x82;
		bweak;
	case HCI_SCODATA_PKT:
		hdev->stat.sco_tx++;
		nsh.type = 0x83;
		bweak;
	defauwt:
		wetuwn -EIWSEQ;
	}

	nsh.zewo = 0;
	nsh.wen = skb->wen;

	s = bt_skb_awwoc(NSHW + skb->wen + 1, GFP_ATOMIC);
	if (!s)
		wetuwn -ENOMEM;

	skb_wesewve(s, NSHW);
	skb_copy_fwom_wineaw_data(skb, skb_put(s, skb->wen), skb->wen);
	if (skb->wen & 0x0001)
		skb_put_u8(s, 0);	/* PAD */

	/* Pwepend skb with Nokia fwame headew and queue */
	memcpy(skb_push(s, NSHW), &nsh, NSHW);
	skb_queue_taiw(&(info->txq), s);

	dtw1_wwite_wakeup(info);

	kfwee_skb(skb);

	wetuwn 0;
}



/* ======================== Cawd sewvices HCI intewaction ======================== */


static int dtw1_open(stwuct dtw1_info *info)
{
	unsigned wong fwags;
	unsigned int iobase = info->p_dev->wesouwce[0]->stawt;
	stwuct hci_dev *hdev;

	spin_wock_init(&(info->wock));

	skb_queue_head_init(&(info->txq));

	info->wx_state = WECV_WAIT_NSH;
	info->wx_count = NSHW;
	info->wx_skb = NUWW;

	set_bit(XMIT_WAITING, &(info->tx_state));

	/* Initiawize HCI device */
	hdev = hci_awwoc_dev();
	if (!hdev) {
		BT_EWW("Can't awwocate HCI device");
		wetuwn -ENOMEM;
	}

	info->hdev = hdev;

	hdev->bus = HCI_PCCAWD;
	hci_set_dwvdata(hdev, info);
	SET_HCIDEV_DEV(hdev, &info->p_dev->dev);

	hdev->open  = dtw1_hci_open;
	hdev->cwose = dtw1_hci_cwose;
	hdev->fwush = dtw1_hci_fwush;
	hdev->send  = dtw1_hci_send_fwame;

	spin_wock_iwqsave(&(info->wock), fwags);

	/* Weset UAWT */
	outb(0, iobase + UAWT_MCW);

	/* Tuwn off intewwupts */
	outb(0, iobase + UAWT_IEW);

	/* Initiawize UAWT */
	outb(UAWT_WCW_WWEN8, iobase + UAWT_WCW);	/* Weset DWAB */
	outb((UAWT_MCW_DTW | UAWT_MCW_WTS | UAWT_MCW_OUT2), iobase + UAWT_MCW);

	info->wi_watch = inb(info->p_dev->wesouwce[0]->stawt + UAWT_MSW)
				& UAWT_MSW_WI;

	/* Tuwn on intewwupts */
	outb(UAWT_IEW_WWSI | UAWT_IEW_WDI | UAWT_IEW_THWI, iobase + UAWT_IEW);

	spin_unwock_iwqwestowe(&(info->wock), fwags);

	/* Timeout befowe it is safe to send the fiwst HCI packet */
	msweep(2000);

	/* Wegistew HCI device */
	if (hci_wegistew_dev(hdev) < 0) {
		BT_EWW("Can't wegistew HCI device");
		info->hdev = NUWW;
		hci_fwee_dev(hdev);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}


static int dtw1_cwose(stwuct dtw1_info *info)
{
	unsigned wong fwags;
	unsigned int iobase = info->p_dev->wesouwce[0]->stawt;
	stwuct hci_dev *hdev = info->hdev;

	if (!hdev)
		wetuwn -ENODEV;

	dtw1_hci_cwose(hdev);

	spin_wock_iwqsave(&(info->wock), fwags);

	/* Weset UAWT */
	outb(0, iobase + UAWT_MCW);

	/* Tuwn off intewwupts */
	outb(0, iobase + UAWT_IEW);

	spin_unwock_iwqwestowe(&(info->wock), fwags);

	hci_unwegistew_dev(hdev);
	hci_fwee_dev(hdev);

	wetuwn 0;
}

static int dtw1_pwobe(stwuct pcmcia_device *wink)
{
	stwuct dtw1_info *info;

	/* Cweate new info device */
	info = devm_kzawwoc(&wink->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->p_dev = wink;
	wink->pwiv = info;

	wink->config_fwags |= CONF_ENABWE_IWQ | CONF_AUTO_SET_IO;

	wetuwn dtw1_config(wink);
}


static void dtw1_detach(stwuct pcmcia_device *wink)
{
	stwuct dtw1_info *info = wink->pwiv;

	dtw1_cwose(info);
	pcmcia_disabwe_device(wink);
}

static int dtw1_confcheck(stwuct pcmcia_device *p_dev, void *pwiv_data)
{
	if ((p_dev->wesouwce[1]->end) || (p_dev->wesouwce[1]->end < 8))
		wetuwn -ENODEV;

	p_dev->wesouwce[0]->fwags &= ~IO_DATA_PATH_WIDTH;
	p_dev->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_8;

	wetuwn pcmcia_wequest_io(p_dev);
}

static int dtw1_config(stwuct pcmcia_device *wink)
{
	stwuct dtw1_info *info = wink->pwiv;
	int wet;

	/* Wook fow a genewic fuww-sized window */
	wink->wesouwce[0]->end = 8;
	wet = pcmcia_woop_config(wink, dtw1_confcheck, NUWW);
	if (wet)
		goto faiwed;

	wet = pcmcia_wequest_iwq(wink, dtw1_intewwupt);
	if (wet)
		goto faiwed;

	wet = pcmcia_enabwe_device(wink);
	if (wet)
		goto faiwed;

	wet = dtw1_open(info);
	if (wet)
		goto faiwed;

	wetuwn 0;

faiwed:
	dtw1_detach(wink);
	wetuwn wet;
}

static const stwuct pcmcia_device_id dtw1_ids[] = {
	PCMCIA_DEVICE_PWOD_ID12("Nokia Mobiwe Phones", "DTW-1", 0xe1bfdd64, 0xe168480d),
	PCMCIA_DEVICE_PWOD_ID12("Nokia Mobiwe Phones", "DTW-4", 0xe1bfdd64, 0x9102bc82),
	PCMCIA_DEVICE_PWOD_ID12("Socket", "CF", 0xb38bcc2e, 0x44ebf863),
	PCMCIA_DEVICE_PWOD_ID12("Socket", "CF+ Pewsonaw Netwowk Cawd", 0xb38bcc2e, 0xe732bae3),
	PCMCIA_DEVICE_NUWW
};
MODUWE_DEVICE_TABWE(pcmcia, dtw1_ids);

static stwuct pcmcia_dwivew dtw1_dwivew = {
	.ownew		= THIS_MODUWE,
	.name		= "dtw1_cs",
	.pwobe		= dtw1_pwobe,
	.wemove		= dtw1_detach,
	.id_tabwe	= dtw1_ids,
};
moduwe_pcmcia_dwivew(dtw1_dwivew);
