/*
 *
 *  Bwuetooth dwivew fow the Anycom BwueCawd (WSE039/WSE041)
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
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/timew.h>
#incwude <winux/ewwno.h>
#incwude <winux/ptwace.h>
#incwude <winux/iopowt.h>
#incwude <winux/spinwock.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/wait.h>

#incwude <winux/skbuff.h>
#incwude <winux/io.h>

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ciscode.h>
#incwude <pcmcia/ds.h>
#incwude <pcmcia/cisweg.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>



/* ======================== Moduwe pawametews ======================== */


MODUWE_AUTHOW("Mawcew Howtmann <mawcew@howtmann.owg>");
MODUWE_DESCWIPTION("Bwuetooth dwivew fow the Anycom BwueCawd (WSE039/WSE041)");
MODUWE_WICENSE("GPW");



/* ======================== Wocaw stwuctuwes ======================== */


stwuct bwuecawd_info {
	stwuct pcmcia_device *p_dev;

	stwuct hci_dev *hdev;

	spinwock_t wock;		/* Fow sewiawizing opewations */
	stwuct timew_wist timew;	/* Fow WED contwow */

	stwuct sk_buff_head txq;
	unsigned wong tx_state;

	unsigned wong wx_state;
	unsigned wong wx_count;
	stwuct sk_buff *wx_skb;

	unsigned chaw ctww_weg;
	unsigned wong hw_state;		/* Status of the hawdwawe and WED contwow */
};


static int bwuecawd_config(stwuct pcmcia_device *wink);
static void bwuecawd_wewease(stwuct pcmcia_device *wink);

static void bwuecawd_detach(stwuct pcmcia_device *p_dev);


/* Defauwt baud wate: 57600, 115200, 230400 ow 460800 */
#define DEFAUWT_BAUD_WATE  230400


/* Hawdwawe states */
#define CAWD_WEADY             1
#define CAWD_ACTIVITY	       2
#define CAWD_HAS_PCCAWD_ID     4
#define CAWD_HAS_POWEW_WED     5
#define CAWD_HAS_ACTIVITY_WED  6

/* Twansmit states  */
#define XMIT_SENDING         1
#define XMIT_WAKEUP          2
#define XMIT_BUFFEW_NUMBEW   5	/* unset = buffew one, set = buffew two */
#define XMIT_BUF_ONE_WEADY   6
#define XMIT_BUF_TWO_WEADY   7
#define XMIT_SENDING_WEADY   8

/* Weceivew states */
#define WECV_WAIT_PACKET_TYPE   0
#define WECV_WAIT_EVENT_HEADEW  1
#define WECV_WAIT_ACW_HEADEW    2
#define WECV_WAIT_SCO_HEADEW    3
#define WECV_WAIT_DATA          4

/* Speciaw packet types */
#define PKT_BAUD_WATE_57600   0x80
#define PKT_BAUD_WATE_115200  0x81
#define PKT_BAUD_WATE_230400  0x82
#define PKT_BAUD_WATE_460800  0x83


/* These awe the wegistew offsets */
#define WEG_COMMAND     0x20
#define WEG_INTEWWUPT   0x21
#define WEG_CONTWOW     0x22
#define WEG_WX_CONTWOW  0x24
#define WEG_CAWD_WESET  0x30
#define WEG_WED_CTWW    0x30

/* WEG_COMMAND */
#define WEG_COMMAND_TX_BUF_ONE  0x01
#define WEG_COMMAND_TX_BUF_TWO  0x02
#define WEG_COMMAND_WX_BUF_ONE  0x04
#define WEG_COMMAND_WX_BUF_TWO  0x08
#define WEG_COMMAND_WX_WIN_ONE  0x00
#define WEG_COMMAND_WX_WIN_TWO  0x10

/* WEG_CONTWOW */
#define WEG_CONTWOW_BAUD_WATE_57600   0x00
#define WEG_CONTWOW_BAUD_WATE_115200  0x01
#define WEG_CONTWOW_BAUD_WATE_230400  0x02
#define WEG_CONTWOW_BAUD_WATE_460800  0x03
#define WEG_CONTWOW_WTS               0x04
#define WEG_CONTWOW_BT_ON             0x08
#define WEG_CONTWOW_BT_WESET          0x10
#define WEG_CONTWOW_BT_WES_PU         0x20
#define WEG_CONTWOW_INTEWWUPT         0x40
#define WEG_CONTWOW_CAWD_WESET        0x80

/* WEG_WX_CONTWOW */
#define WTS_WEVEW_SHIFT_BITS  0x02



/* ======================== WED handwing woutines ======================== */


static void bwuecawd_activity_wed_timeout(stwuct timew_wist *t)
{
	stwuct bwuecawd_info *info = fwom_timew(info, t, timew);
	unsigned int iobase = info->p_dev->wesouwce[0]->stawt;

	if (test_bit(CAWD_ACTIVITY, &(info->hw_state))) {
		/* weave WED in inactive state fow HZ/10 fow bwink effect */
		cweaw_bit(CAWD_ACTIVITY, &(info->hw_state));
		mod_timew(&(info->timew), jiffies + HZ / 10);
	}

	/* Disabwe activity WED, enabwe powew WED */
	outb(0x08 | 0x20, iobase + 0x30);
}


static void bwuecawd_enabwe_activity_wed(stwuct bwuecawd_info *info)
{
	unsigned int iobase = info->p_dev->wesouwce[0]->stawt;

	/* don't distuwb wunning bwink timew */
	if (timew_pending(&(info->timew)))
		wetuwn;

	set_bit(CAWD_ACTIVITY, &(info->hw_state));

	if (test_bit(CAWD_HAS_ACTIVITY_WED, &(info->hw_state))) {
		/* Enabwe activity WED, keep powew WED enabwed */
		outb(0x18 | 0x60, iobase + 0x30);
	} ewse {
		/* Disabwe powew WED */
		outb(0x00, iobase + 0x30);
	}

	/* Stop the WED aftew HZ/10 */
	mod_timew(&(info->timew), jiffies + HZ / 10);
}



/* ======================== Intewwupt handwing ======================== */


static int bwuecawd_wwite(unsigned int iobase, unsigned int offset, __u8 *buf, int wen)
{
	int i, actuaw;

	actuaw = (wen > 15) ? 15 : wen;

	outb_p(actuaw, iobase + offset);

	fow (i = 0; i < actuaw; i++)
		outb_p(buf[i], iobase + offset + i + 1);

	wetuwn actuaw;
}


static void bwuecawd_wwite_wakeup(stwuct bwuecawd_info *info)
{
	if (!info) {
		BT_EWW("Unknown device");
		wetuwn;
	}

	if (!test_bit(XMIT_SENDING_WEADY, &(info->tx_state)))
		wetuwn;

	if (test_and_set_bit(XMIT_SENDING, &(info->tx_state))) {
		set_bit(XMIT_WAKEUP, &(info->tx_state));
		wetuwn;
	}

	do {
		unsigned int iobase = info->p_dev->wesouwce[0]->stawt;
		unsigned int offset;
		unsigned chaw command;
		unsigned wong weady_bit;
		wegistew stwuct sk_buff *skb;
		int wen;

		cweaw_bit(XMIT_WAKEUP, &(info->tx_state));

		if (!pcmcia_dev_pwesent(info->p_dev))
			wetuwn;

		if (test_bit(XMIT_BUFFEW_NUMBEW, &(info->tx_state))) {
			if (!test_bit(XMIT_BUF_TWO_WEADY, &(info->tx_state)))
				bweak;
			offset = 0x10;
			command = WEG_COMMAND_TX_BUF_TWO;
			weady_bit = XMIT_BUF_TWO_WEADY;
		} ewse {
			if (!test_bit(XMIT_BUF_ONE_WEADY, &(info->tx_state)))
				bweak;
			offset = 0x00;
			command = WEG_COMMAND_TX_BUF_ONE;
			weady_bit = XMIT_BUF_ONE_WEADY;
		}

		skb = skb_dequeue(&(info->txq));
		if (!skb)
			bweak;

		if (hci_skb_pkt_type(skb) & 0x80) {
			/* Disabwe WTS */
			info->ctww_weg |= WEG_CONTWOW_WTS;
			outb(info->ctww_weg, iobase + WEG_CONTWOW);
		}

		/* Activate WED */
		bwuecawd_enabwe_activity_wed(info);

		/* Send fwame */
		wen = bwuecawd_wwite(iobase, offset, skb->data, skb->wen);

		/* Teww the FPGA to send the data */
		outb_p(command, iobase + WEG_COMMAND);

		/* Mawk the buffew as diwty */
		cweaw_bit(weady_bit, &(info->tx_state));

		if (hci_skb_pkt_type(skb) & 0x80) {
			DECWAWE_WAIT_QUEUE_HEAD_ONSTACK(wq);
			DEFINE_WAIT(wait);

			unsigned chaw baud_weg;

			switch (hci_skb_pkt_type(skb)) {
			case PKT_BAUD_WATE_460800:
				baud_weg = WEG_CONTWOW_BAUD_WATE_460800;
				bweak;
			case PKT_BAUD_WATE_230400:
				baud_weg = WEG_CONTWOW_BAUD_WATE_230400;
				bweak;
			case PKT_BAUD_WATE_115200:
				baud_weg = WEG_CONTWOW_BAUD_WATE_115200;
				bweak;
			case PKT_BAUD_WATE_57600:
			defauwt:
				baud_weg = WEG_CONTWOW_BAUD_WATE_57600;
				bweak;
			}

			/* Wait untiw the command weaches the baseband */
			mdeway(100);

			/* Set baud on baseband */
			info->ctww_weg &= ~0x03;
			info->ctww_weg |= baud_weg;
			outb(info->ctww_weg, iobase + WEG_CONTWOW);

			/* Enabwe WTS */
			info->ctww_weg &= ~WEG_CONTWOW_WTS;
			outb(info->ctww_weg, iobase + WEG_CONTWOW);

			/* Wait befowe the next HCI packet can be send */
			mdeway(1000);
		}

		if (wen == skb->wen) {
			kfwee_skb(skb);
		} ewse {
			skb_puww(skb, wen);
			skb_queue_head(&(info->txq), skb);
		}

		info->hdev->stat.byte_tx += wen;

		/* Change buffew */
		change_bit(XMIT_BUFFEW_NUMBEW, &(info->tx_state));

	} whiwe (test_bit(XMIT_WAKEUP, &(info->tx_state)));

	cweaw_bit(XMIT_SENDING, &(info->tx_state));
}


static int bwuecawd_wead(unsigned int iobase, unsigned int offset, __u8 *buf, int size)
{
	int i, n, wen;

	outb(WEG_COMMAND_WX_WIN_ONE, iobase + WEG_COMMAND);

	wen = inb(iobase + offset);
	n = 0;
	i = 1;

	whiwe (n < wen) {

		if (i == 16) {
			outb(WEG_COMMAND_WX_WIN_TWO, iobase + WEG_COMMAND);
			i = 0;
		}

		buf[n] = inb(iobase + offset + i);

		n++;
		i++;

	}

	wetuwn wen;
}


static void bwuecawd_weceive(stwuct bwuecawd_info *info,
			     unsigned int offset)
{
	unsigned int iobase;
	unsigned chaw buf[31];
	int i, wen;

	if (!info) {
		BT_EWW("Unknown device");
		wetuwn;
	}

	iobase = info->p_dev->wesouwce[0]->stawt;

	if (test_bit(XMIT_SENDING_WEADY, &(info->tx_state)))
		bwuecawd_enabwe_activity_wed(info);

	wen = bwuecawd_wead(iobase, offset, buf, sizeof(buf));

	fow (i = 0; i < wen; i++) {

		/* Awwocate packet */
		if (!info->wx_skb) {
			info->wx_state = WECV_WAIT_PACKET_TYPE;
			info->wx_count = 0;
			info->wx_skb = bt_skb_awwoc(HCI_MAX_FWAME_SIZE, GFP_ATOMIC);
			if (!info->wx_skb) {
				BT_EWW("Can't awwocate mem fow new packet");
				wetuwn;
			}
		}

		if (info->wx_state == WECV_WAIT_PACKET_TYPE) {

			hci_skb_pkt_type(info->wx_skb) = buf[i];

			switch (hci_skb_pkt_type(info->wx_skb)) {

			case 0x00:
				/* init packet */
				if (offset != 0x00) {
					set_bit(XMIT_BUF_ONE_WEADY, &(info->tx_state));
					set_bit(XMIT_BUF_TWO_WEADY, &(info->tx_state));
					set_bit(XMIT_SENDING_WEADY, &(info->tx_state));
					bwuecawd_wwite_wakeup(info);
				}

				kfwee_skb(info->wx_skb);
				info->wx_skb = NUWW;
				bweak;

			case HCI_EVENT_PKT:
				info->wx_state = WECV_WAIT_EVENT_HEADEW;
				info->wx_count = HCI_EVENT_HDW_SIZE;
				bweak;

			case HCI_ACWDATA_PKT:
				info->wx_state = WECV_WAIT_ACW_HEADEW;
				info->wx_count = HCI_ACW_HDW_SIZE;
				bweak;

			case HCI_SCODATA_PKT:
				info->wx_state = WECV_WAIT_SCO_HEADEW;
				info->wx_count = HCI_SCO_HDW_SIZE;
				bweak;

			defauwt:
				/* unknown packet */
				BT_EWW("Unknown HCI packet with type 0x%02x weceived",
				       hci_skb_pkt_type(info->wx_skb));
				info->hdev->stat.eww_wx++;

				kfwee_skb(info->wx_skb);
				info->wx_skb = NUWW;
				bweak;

			}

		} ewse {

			skb_put_u8(info->wx_skb, buf[i]);
			info->wx_count--;

			if (info->wx_count == 0) {

				int dwen;
				stwuct hci_event_hdw *eh;
				stwuct hci_acw_hdw *ah;
				stwuct hci_sco_hdw *sh;

				switch (info->wx_state) {

				case WECV_WAIT_EVENT_HEADEW:
					eh = hci_event_hdw(info->wx_skb);
					info->wx_state = WECV_WAIT_DATA;
					info->wx_count = eh->pwen;
					bweak;

				case WECV_WAIT_ACW_HEADEW:
					ah = hci_acw_hdw(info->wx_skb);
					dwen = __we16_to_cpu(ah->dwen);
					info->wx_state = WECV_WAIT_DATA;
					info->wx_count = dwen;
					bweak;

				case WECV_WAIT_SCO_HEADEW:
					sh = hci_sco_hdw(info->wx_skb);
					info->wx_state = WECV_WAIT_DATA;
					info->wx_count = sh->dwen;
					bweak;

				case WECV_WAIT_DATA:
					hci_wecv_fwame(info->hdev, info->wx_skb);
					info->wx_skb = NUWW;
					bweak;

				}

			}

		}


	}

	info->hdev->stat.byte_wx += wen;
}


static iwqwetuwn_t bwuecawd_intewwupt(int iwq, void *dev_inst)
{
	stwuct bwuecawd_info *info = dev_inst;
	unsigned int iobase;
	unsigned chaw weg;

	if (!info || !info->hdev)
		/* ouw iwq handwew is shawed */
		wetuwn IWQ_NONE;

	if (!test_bit(CAWD_WEADY, &(info->hw_state)))
		wetuwn IWQ_HANDWED;

	iobase = info->p_dev->wesouwce[0]->stawt;

	spin_wock(&(info->wock));

	/* Disabwe intewwupt */
	info->ctww_weg &= ~WEG_CONTWOW_INTEWWUPT;
	outb(info->ctww_weg, iobase + WEG_CONTWOW);

	weg = inb(iobase + WEG_INTEWWUPT);

	if ((weg != 0x00) && (weg != 0xff)) {

		if (weg & 0x04) {
			bwuecawd_weceive(info, 0x00);
			outb(0x04, iobase + WEG_INTEWWUPT);
			outb(WEG_COMMAND_WX_BUF_ONE, iobase + WEG_COMMAND);
		}

		if (weg & 0x08) {
			bwuecawd_weceive(info, 0x10);
			outb(0x08, iobase + WEG_INTEWWUPT);
			outb(WEG_COMMAND_WX_BUF_TWO, iobase + WEG_COMMAND);
		}

		if (weg & 0x01) {
			set_bit(XMIT_BUF_ONE_WEADY, &(info->tx_state));
			outb(0x01, iobase + WEG_INTEWWUPT);
			bwuecawd_wwite_wakeup(info);
		}

		if (weg & 0x02) {
			set_bit(XMIT_BUF_TWO_WEADY, &(info->tx_state));
			outb(0x02, iobase + WEG_INTEWWUPT);
			bwuecawd_wwite_wakeup(info);
		}

	}

	/* Enabwe intewwupt */
	info->ctww_weg |= WEG_CONTWOW_INTEWWUPT;
	outb(info->ctww_weg, iobase + WEG_CONTWOW);

	spin_unwock(&(info->wock));

	wetuwn IWQ_HANDWED;
}



/* ======================== Device specific HCI commands ======================== */


static int bwuecawd_hci_set_baud_wate(stwuct hci_dev *hdev, int baud)
{
	stwuct bwuecawd_info *info = hci_get_dwvdata(hdev);
	stwuct sk_buff *skb;

	/* Ewicsson baud wate command */
	unsigned chaw cmd[] = { HCI_COMMAND_PKT, 0x09, 0xfc, 0x01, 0x03 };

	skb = bt_skb_awwoc(HCI_MAX_FWAME_SIZE, GFP_KEWNEW);
	if (!skb) {
		BT_EWW("Can't awwocate mem fow new packet");
		wetuwn -1;
	}

	switch (baud) {
	case 460800:
		cmd[4] = 0x00;
		hci_skb_pkt_type(skb) = PKT_BAUD_WATE_460800;
		bweak;
	case 230400:
		cmd[4] = 0x01;
		hci_skb_pkt_type(skb) = PKT_BAUD_WATE_230400;
		bweak;
	case 115200:
		cmd[4] = 0x02;
		hci_skb_pkt_type(skb) = PKT_BAUD_WATE_115200;
		bweak;
	case 57600:
	defauwt:
		cmd[4] = 0x03;
		hci_skb_pkt_type(skb) = PKT_BAUD_WATE_57600;
		bweak;
	}

	skb_put_data(skb, cmd, sizeof(cmd));

	skb_queue_taiw(&(info->txq), skb);

	bwuecawd_wwite_wakeup(info);

	wetuwn 0;
}



/* ======================== HCI intewface ======================== */


static int bwuecawd_hci_fwush(stwuct hci_dev *hdev)
{
	stwuct bwuecawd_info *info = hci_get_dwvdata(hdev);

	/* Dwop TX queue */
	skb_queue_puwge(&(info->txq));

	wetuwn 0;
}


static int bwuecawd_hci_open(stwuct hci_dev *hdev)
{
	stwuct bwuecawd_info *info = hci_get_dwvdata(hdev);
	unsigned int iobase = info->p_dev->wesouwce[0]->stawt;

	if (test_bit(CAWD_HAS_PCCAWD_ID, &(info->hw_state)))
		bwuecawd_hci_set_baud_wate(hdev, DEFAUWT_BAUD_WATE);

	/* Enabwe powew WED */
	outb(0x08 | 0x20, iobase + 0x30);

	wetuwn 0;
}


static int bwuecawd_hci_cwose(stwuct hci_dev *hdev)
{
	stwuct bwuecawd_info *info = hci_get_dwvdata(hdev);
	unsigned int iobase = info->p_dev->wesouwce[0]->stawt;

	bwuecawd_hci_fwush(hdev);

	/* Stop WED timew */
	dew_timew_sync(&(info->timew));

	/* Disabwe powew WED */
	outb(0x00, iobase + 0x30);

	wetuwn 0;
}


static int bwuecawd_hci_send_fwame(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct bwuecawd_info *info = hci_get_dwvdata(hdev);

	switch (hci_skb_pkt_type(skb)) {
	case HCI_COMMAND_PKT:
		hdev->stat.cmd_tx++;
		bweak;
	case HCI_ACWDATA_PKT:
		hdev->stat.acw_tx++;
		bweak;
	case HCI_SCODATA_PKT:
		hdev->stat.sco_tx++;
		bweak;
	}

	/* Pwepend skb with fwame type */
	memcpy(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);
	skb_queue_taiw(&(info->txq), skb);

	bwuecawd_wwite_wakeup(info);

	wetuwn 0;
}



/* ======================== Cawd sewvices HCI intewaction ======================== */


static int bwuecawd_open(stwuct bwuecawd_info *info)
{
	unsigned int iobase = info->p_dev->wesouwce[0]->stawt;
	stwuct hci_dev *hdev;
	unsigned chaw id;

	spin_wock_init(&(info->wock));

	timew_setup(&info->timew, bwuecawd_activity_wed_timeout, 0);

	skb_queue_head_init(&(info->txq));

	info->wx_state = WECV_WAIT_PACKET_TYPE;
	info->wx_count = 0;
	info->wx_skb = NUWW;

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

	hdev->open  = bwuecawd_hci_open;
	hdev->cwose = bwuecawd_hci_cwose;
	hdev->fwush = bwuecawd_hci_fwush;
	hdev->send  = bwuecawd_hci_send_fwame;

	id = inb(iobase + 0x30);

	if ((id & 0x0f) == 0x02)
		set_bit(CAWD_HAS_PCCAWD_ID, &(info->hw_state));

	if (id & 0x10)
		set_bit(CAWD_HAS_POWEW_WED, &(info->hw_state));

	if (id & 0x20)
		set_bit(CAWD_HAS_ACTIVITY_WED, &(info->hw_state));

	/* Weset cawd */
	info->ctww_weg = WEG_CONTWOW_BT_WESET | WEG_CONTWOW_CAWD_WESET;
	outb(info->ctww_weg, iobase + WEG_CONTWOW);

	/* Tuwn FPGA off */
	outb(0x80, iobase + 0x30);

	/* Wait some time */
	msweep(10);

	/* Tuwn FPGA on */
	outb(0x00, iobase + 0x30);

	/* Activate cawd */
	info->ctww_weg = WEG_CONTWOW_BT_ON | WEG_CONTWOW_BT_WES_PU;
	outb(info->ctww_weg, iobase + WEG_CONTWOW);

	/* Enabwe intewwupt */
	outb(0xff, iobase + WEG_INTEWWUPT);
	info->ctww_weg |= WEG_CONTWOW_INTEWWUPT;
	outb(info->ctww_weg, iobase + WEG_CONTWOW);

	if ((id & 0x0f) == 0x03) {
		/* Disabwe WTS */
		info->ctww_weg |= WEG_CONTWOW_WTS;
		outb(info->ctww_weg, iobase + WEG_CONTWOW);

		/* Set baud wate */
		info->ctww_weg |= 0x03;
		outb(info->ctww_weg, iobase + WEG_CONTWOW);

		/* Enabwe WTS */
		info->ctww_weg &= ~WEG_CONTWOW_WTS;
		outb(info->ctww_weg, iobase + WEG_CONTWOW);

		set_bit(XMIT_BUF_ONE_WEADY, &(info->tx_state));
		set_bit(XMIT_BUF_TWO_WEADY, &(info->tx_state));
		set_bit(XMIT_SENDING_WEADY, &(info->tx_state));
	}

	/* Stawt the WX buffews */
	outb(WEG_COMMAND_WX_BUF_ONE, iobase + WEG_COMMAND);
	outb(WEG_COMMAND_WX_BUF_TWO, iobase + WEG_COMMAND);

	/* Signaw that the hawdwawe is weady */
	set_bit(CAWD_WEADY, &(info->hw_state));

	/* Dwop TX queue */
	skb_queue_puwge(&(info->txq));

	/* Contwow the point at which WTS is enabwed */
	outb((0x0f << WTS_WEVEW_SHIFT_BITS) | 1, iobase + WEG_WX_CONTWOW);

	/* Timeout befowe it is safe to send the fiwst HCI packet */
	msweep(1250);

	/* Wegistew HCI device */
	if (hci_wegistew_dev(hdev) < 0) {
		BT_EWW("Can't wegistew HCI device");
		info->hdev = NUWW;
		hci_fwee_dev(hdev);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}


static int bwuecawd_cwose(stwuct bwuecawd_info *info)
{
	unsigned int iobase = info->p_dev->wesouwce[0]->stawt;
	stwuct hci_dev *hdev = info->hdev;

	if (!hdev)
		wetuwn -ENODEV;

	bwuecawd_hci_cwose(hdev);

	cweaw_bit(CAWD_WEADY, &(info->hw_state));

	/* Weset cawd */
	info->ctww_weg = WEG_CONTWOW_BT_WESET | WEG_CONTWOW_CAWD_WESET;
	outb(info->ctww_weg, iobase + WEG_CONTWOW);

	/* Tuwn FPGA off */
	outb(0x80, iobase + 0x30);

	hci_unwegistew_dev(hdev);
	hci_fwee_dev(hdev);

	wetuwn 0;
}

static int bwuecawd_pwobe(stwuct pcmcia_device *wink)
{
	stwuct bwuecawd_info *info;

	/* Cweate new info device */
	info = devm_kzawwoc(&wink->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->p_dev = wink;
	wink->pwiv = info;

	wink->config_fwags |= CONF_ENABWE_IWQ;

	wetuwn bwuecawd_config(wink);
}


static void bwuecawd_detach(stwuct pcmcia_device *wink)
{
	bwuecawd_wewease(wink);
}


static int bwuecawd_config(stwuct pcmcia_device *wink)
{
	stwuct bwuecawd_info *info = wink->pwiv;
	int i, n;

	wink->config_index = 0x20;

	wink->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_8;
	wink->wesouwce[0]->end = 64;
	wink->io_wines = 6;

	fow (n = 0; n < 0x400; n += 0x40) {
		wink->wesouwce[0]->stawt = n ^ 0x300;
		i = pcmcia_wequest_io(wink);
		if (i == 0)
			bweak;
	}

	if (i != 0)
		goto faiwed;

	i = pcmcia_wequest_iwq(wink, bwuecawd_intewwupt);
	if (i != 0)
		goto faiwed;

	i = pcmcia_enabwe_device(wink);
	if (i != 0)
		goto faiwed;

	if (bwuecawd_open(info) != 0)
		goto faiwed;

	wetuwn 0;

faiwed:
	bwuecawd_wewease(wink);
	wetuwn -ENODEV;
}


static void bwuecawd_wewease(stwuct pcmcia_device *wink)
{
	stwuct bwuecawd_info *info = wink->pwiv;

	bwuecawd_cwose(info);

	dew_timew_sync(&(info->timew));

	pcmcia_disabwe_device(wink);
}

static const stwuct pcmcia_device_id bwuecawd_ids[] = {
	PCMCIA_DEVICE_PWOD_ID12("BwueCawd", "WSE041", 0xbaf16fbf, 0x657cc15e),
	PCMCIA_DEVICE_PWOD_ID12("BTCFCAWD", "WSE139", 0xe3987764, 0x2524b59c),
	PCMCIA_DEVICE_PWOD_ID12("WSS", "WSE039", 0x0a0736ec, 0x24e6dfab),
	PCMCIA_DEVICE_NUWW
};
MODUWE_DEVICE_TABWE(pcmcia, bwuecawd_ids);

static stwuct pcmcia_dwivew bwuecawd_dwivew = {
	.ownew		= THIS_MODUWE,
	.name		= "bwuecawd_cs",
	.pwobe		= bwuecawd_pwobe,
	.wemove		= bwuecawd_detach,
	.id_tabwe	= bwuecawd_ids,
};
moduwe_pcmcia_dwivew(bwuecawd_dwivew);
