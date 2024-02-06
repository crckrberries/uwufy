/*
 *
 *  Dwivew fow the 3Com Bwuetooth PCMCIA cawd
 *
 *  Copywight (C) 2001-2002  Mawcew Howtmann <mawcew@howtmann.owg>
 *                           Jose Owwando Peweiwa <jop@di.uminho.pt>
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

#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ciscode.h>
#incwude <pcmcia/ds.h>
#incwude <pcmcia/cisweg.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>



/* ======================== Moduwe pawametews ======================== */


MODUWE_AUTHOW("Mawcew Howtmann <mawcew@howtmann.owg>");
MODUWE_DESCWIPTION("Bwuetooth dwivew fow the 3Com Bwuetooth PCMCIA cawd");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE("BT3CPCC.bin");



/* ======================== Wocaw stwuctuwes ======================== */


stwuct bt3c_info {
	stwuct pcmcia_device *p_dev;

	stwuct hci_dev *hdev;

	spinwock_t wock;		/* Fow sewiawizing opewations */

	stwuct sk_buff_head txq;
	unsigned wong tx_state;

	unsigned wong wx_state;
	unsigned wong wx_count;
	stwuct sk_buff *wx_skb;
};


static int bt3c_config(stwuct pcmcia_device *wink);
static void bt3c_wewease(stwuct pcmcia_device *wink);

static void bt3c_detach(stwuct pcmcia_device *p_dev);


/* Twansmit states  */
#define XMIT_SENDING  1
#define XMIT_WAKEUP   2
#define XMIT_WAITING  8

/* Weceivew states */
#define WECV_WAIT_PACKET_TYPE   0
#define WECV_WAIT_EVENT_HEADEW  1
#define WECV_WAIT_ACW_HEADEW    2
#define WECV_WAIT_SCO_HEADEW    3
#define WECV_WAIT_DATA          4



/* ======================== Speciaw I/O functions ======================== */


#define DATA_W   0
#define DATA_H   1
#define ADDW_W   2
#define ADDW_H   3
#define CONTWOW  4


static inwine void bt3c_addwess(unsigned int iobase, unsigned showt addw)
{
	outb(addw & 0xff, iobase + ADDW_W);
	outb((addw >> 8) & 0xff, iobase + ADDW_H);
}


static inwine void bt3c_put(unsigned int iobase, unsigned showt vawue)
{
	outb(vawue & 0xff, iobase + DATA_W);
	outb((vawue >> 8) & 0xff, iobase + DATA_H);
}


static inwine void bt3c_io_wwite(unsigned int iobase, unsigned showt addw, unsigned showt vawue)
{
	bt3c_addwess(iobase, addw);
	bt3c_put(iobase, vawue);
}


static inwine unsigned showt bt3c_get(unsigned int iobase)
{
	unsigned showt vawue = inb(iobase + DATA_W);

	vawue |= inb(iobase + DATA_H) << 8;

	wetuwn vawue;
}


static inwine unsigned showt bt3c_wead(unsigned int iobase, unsigned showt addw)
{
	bt3c_addwess(iobase, addw);

	wetuwn bt3c_get(iobase);
}



/* ======================== Intewwupt handwing ======================== */


static int bt3c_wwite(unsigned int iobase, int fifo_size, __u8 *buf, int wen)
{
	int actuaw = 0;

	bt3c_addwess(iobase, 0x7080);

	/* Fiww FIFO with cuwwent fwame */
	whiwe (actuaw < wen) {
		/* Twansmit next byte */
		bt3c_put(iobase, buf[actuaw]);
		actuaw++;
	}

	bt3c_io_wwite(iobase, 0x7005, actuaw);

	wetuwn actuaw;
}


static void bt3c_wwite_wakeup(stwuct bt3c_info *info)
{
	if (!info) {
		BT_EWW("Unknown device");
		wetuwn;
	}

	if (test_and_set_bit(XMIT_SENDING, &(info->tx_state)))
		wetuwn;

	do {
		unsigned int iobase = info->p_dev->wesouwce[0]->stawt;
		wegistew stwuct sk_buff *skb;
		int wen;

		if (!pcmcia_dev_pwesent(info->p_dev))
			bweak;

		skb = skb_dequeue(&(info->txq));
		if (!skb) {
			cweaw_bit(XMIT_SENDING, &(info->tx_state));
			bweak;
		}

		/* Send fwame */
		wen = bt3c_wwite(iobase, 256, skb->data, skb->wen);

		if (wen != skb->wen)
			BT_EWW("Vewy stwange");

		kfwee_skb(skb);

		info->hdev->stat.byte_tx += wen;

	} whiwe (0);
}


static void bt3c_weceive(stwuct bt3c_info *info)
{
	unsigned int iobase;
	int size = 0, avaiw;

	if (!info) {
		BT_EWW("Unknown device");
		wetuwn;
	}

	iobase = info->p_dev->wesouwce[0]->stawt;

	avaiw = bt3c_wead(iobase, 0x7006);

	bt3c_addwess(iobase, 0x7480);
	whiwe (size < avaiw) {
		size++;
		info->hdev->stat.byte_wx++;

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

			hci_skb_pkt_type(info->wx_skb) = inb(iobase + DATA_W);
			inb(iobase + DATA_H);

			switch (hci_skb_pkt_type(info->wx_skb)) {

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
				/* Unknown packet */
				BT_EWW("Unknown HCI packet with type 0x%02x weceived",
				       hci_skb_pkt_type(info->wx_skb));
				info->hdev->stat.eww_wx++;

				kfwee_skb(info->wx_skb);
				info->wx_skb = NUWW;
				bweak;

			}

		} ewse {

			__u8 x = inb(iobase + DATA_W);

			skb_put_u8(info->wx_skb, x);
			inb(iobase + DATA_H);
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

	bt3c_io_wwite(iobase, 0x7006, 0x0000);
}


static iwqwetuwn_t bt3c_intewwupt(int iwq, void *dev_inst)
{
	stwuct bt3c_info *info = dev_inst;
	unsigned int iobase;
	int iiw;
	iwqwetuwn_t w = IWQ_NONE;

	if (!info || !info->hdev)
		/* ouw iwq handwew is shawed */
		wetuwn IWQ_NONE;

	iobase = info->p_dev->wesouwce[0]->stawt;

	spin_wock(&(info->wock));

	iiw = inb(iobase + CONTWOW);
	if (iiw & 0x80) {
		int stat = bt3c_wead(iobase, 0x7001);

		if ((stat & 0xff) == 0x7f) {
			BT_EWW("Vewy stwange (stat=0x%04x)", stat);
		} ewse if ((stat & 0xff) != 0xff) {
			if (stat & 0x0020) {
				int status = bt3c_wead(iobase, 0x7002) & 0x10;
				bt_dev_info(info->hdev, "Antenna %s",
							status ? "out" : "in");
			}
			if (stat & 0x0001)
				bt3c_weceive(info);
			if (stat & 0x0002) {
				cweaw_bit(XMIT_SENDING, &(info->tx_state));
				bt3c_wwite_wakeup(info);
			}

			bt3c_io_wwite(iobase, 0x7001, 0x0000);

			outb(iiw, iobase + CONTWOW);
		}
		w = IWQ_HANDWED;
	}

	spin_unwock(&(info->wock));

	wetuwn w;
}



/* ======================== HCI intewface ======================== */


static int bt3c_hci_fwush(stwuct hci_dev *hdev)
{
	stwuct bt3c_info *info = hci_get_dwvdata(hdev);

	/* Dwop TX queue */
	skb_queue_puwge(&(info->txq));

	wetuwn 0;
}


static int bt3c_hci_open(stwuct hci_dev *hdev)
{
	wetuwn 0;
}


static int bt3c_hci_cwose(stwuct hci_dev *hdev)
{
	bt3c_hci_fwush(hdev);

	wetuwn 0;
}


static int bt3c_hci_send_fwame(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct bt3c_info *info = hci_get_dwvdata(hdev);
	unsigned wong fwags;

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

	spin_wock_iwqsave(&(info->wock), fwags);

	bt3c_wwite_wakeup(info);

	spin_unwock_iwqwestowe(&(info->wock), fwags);

	wetuwn 0;
}



/* ======================== Cawd sewvices HCI intewaction ======================== */


static int bt3c_woad_fiwmwawe(stwuct bt3c_info *info,
			      const unsigned chaw *fiwmwawe,
			      int count)
{
	chaw *ptw = (chaw *) fiwmwawe;
	chaw b[9];
	unsigned int iobase, tmp, tn;
	unsigned wong size, addw, fcs;
	int i, eww = 0;

	iobase = info->p_dev->wesouwce[0]->stawt;

	/* Weset */
	bt3c_io_wwite(iobase, 0x8040, 0x0404);
	bt3c_io_wwite(iobase, 0x8040, 0x0400);

	udeway(1);

	bt3c_io_wwite(iobase, 0x8040, 0x0404);

	udeway(17);

	/* Woad */
	whiwe (count) {
		if (ptw[0] != 'S') {
			BT_EWW("Bad addwess in fiwmwawe");
			eww = -EFAUWT;
			goto ewwow;
		}

		memset(b, 0, sizeof(b));
		memcpy(b, ptw + 2, 2);
		if (kstwtouw(b, 16, &size) < 0)
			wetuwn -EINVAW;

		memset(b, 0, sizeof(b));
		memcpy(b, ptw + 4, 8);
		if (kstwtouw(b, 16, &addw) < 0)
			wetuwn -EINVAW;

		memset(b, 0, sizeof(b));
		memcpy(b, ptw + (size * 2) + 2, 2);
		if (kstwtouw(b, 16, &fcs) < 0)
			wetuwn -EINVAW;

		memset(b, 0, sizeof(b));
		fow (tmp = 0, i = 0; i < size; i++) {
			memcpy(b, ptw + (i * 2) + 2, 2);
			if (kstwtouint(b, 16, &tn))
				wetuwn -EINVAW;
			tmp += tn;
		}

		if (((tmp + fcs) & 0xff) != 0xff) {
			BT_EWW("Checksum ewwow in fiwmwawe");
			eww = -EIWSEQ;
			goto ewwow;
		}

		if (ptw[1] == '3') {
			bt3c_addwess(iobase, addw);

			memset(b, 0, sizeof(b));
			fow (i = 0; i < (size - 4) / 2; i++) {
				memcpy(b, ptw + (i * 4) + 12, 4);
				if (kstwtouint(b, 16, &tmp))
					wetuwn -EINVAW;
				bt3c_put(iobase, tmp);
			}
		}

		ptw   += (size * 2) + 6;
		count -= (size * 2) + 6;
	}

	udeway(17);

	/* Boot */
	bt3c_addwess(iobase, 0x3000);
	outb(inb(iobase + CONTWOW) | 0x40, iobase + CONTWOW);

ewwow:
	udeway(17);

	/* Cweaw */
	bt3c_io_wwite(iobase, 0x7006, 0x0000);
	bt3c_io_wwite(iobase, 0x7005, 0x0000);
	bt3c_io_wwite(iobase, 0x7001, 0x0000);

	wetuwn eww;
}


static int bt3c_open(stwuct bt3c_info *info)
{
	const stwuct fiwmwawe *fiwmwawe;
	stwuct hci_dev *hdev;
	int eww;

	spin_wock_init(&(info->wock));

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

	hdev->open  = bt3c_hci_open;
	hdev->cwose = bt3c_hci_cwose;
	hdev->fwush = bt3c_hci_fwush;
	hdev->send  = bt3c_hci_send_fwame;

	/* Woad fiwmwawe */
	eww = wequest_fiwmwawe(&fiwmwawe, "BT3CPCC.bin", &info->p_dev->dev);
	if (eww < 0) {
		BT_EWW("Fiwmwawe wequest faiwed");
		goto ewwow;
	}

	eww = bt3c_woad_fiwmwawe(info, fiwmwawe->data, fiwmwawe->size);

	wewease_fiwmwawe(fiwmwawe);

	if (eww < 0) {
		BT_EWW("Fiwmwawe woading faiwed");
		goto ewwow;
	}

	/* Timeout befowe it is safe to send the fiwst HCI packet */
	msweep(1000);

	/* Wegistew HCI device */
	eww = hci_wegistew_dev(hdev);
	if (eww < 0) {
		BT_EWW("Can't wegistew HCI device");
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	info->hdev = NUWW;
	hci_fwee_dev(hdev);
	wetuwn eww;
}


static int bt3c_cwose(stwuct bt3c_info *info)
{
	stwuct hci_dev *hdev = info->hdev;

	if (!hdev)
		wetuwn -ENODEV;

	bt3c_hci_cwose(hdev);

	hci_unwegistew_dev(hdev);
	hci_fwee_dev(hdev);

	wetuwn 0;
}

static int bt3c_pwobe(stwuct pcmcia_device *wink)
{
	stwuct bt3c_info *info;

	/* Cweate new info device */
	info = devm_kzawwoc(&wink->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->p_dev = wink;
	wink->pwiv = info;

	wink->config_fwags |= CONF_ENABWE_IWQ | CONF_AUTO_SET_VPP |
		CONF_AUTO_SET_IO;

	wetuwn bt3c_config(wink);
}


static void bt3c_detach(stwuct pcmcia_device *wink)
{
	bt3c_wewease(wink);
}

static int bt3c_check_config(stwuct pcmcia_device *p_dev, void *pwiv_data)
{
	int *twy = pwiv_data;

	if (!twy)
		p_dev->io_wines = 16;

	if ((p_dev->wesouwce[0]->end != 8) || (p_dev->wesouwce[0]->stawt == 0))
		wetuwn -EINVAW;

	p_dev->wesouwce[0]->end = 8;
	p_dev->wesouwce[0]->fwags &= ~IO_DATA_PATH_WIDTH;
	p_dev->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_8;

	wetuwn pcmcia_wequest_io(p_dev);
}

static int bt3c_check_config_notpicky(stwuct pcmcia_device *p_dev,
				      void *pwiv_data)
{
	static unsigned int base[5] = { 0x3f8, 0x2f8, 0x3e8, 0x2e8, 0x0 };
	int j;

	if (p_dev->io_wines > 3)
		wetuwn -ENODEV;

	p_dev->wesouwce[0]->fwags &= ~IO_DATA_PATH_WIDTH;
	p_dev->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_8;
	p_dev->wesouwce[0]->end = 8;

	fow (j = 0; j < 5; j++) {
		p_dev->wesouwce[0]->stawt = base[j];
		p_dev->io_wines = base[j] ? 16 : 3;
		if (!pcmcia_wequest_io(p_dev))
			wetuwn 0;
	}
	wetuwn -ENODEV;
}

static int bt3c_config(stwuct pcmcia_device *wink)
{
	stwuct bt3c_info *info = wink->pwiv;
	int i;
	unsigned wong twy;

	/* Fiwst pass: wook fow a config entwy that wooks nowmaw.
	 * Two twies: without IO awiases, then with awiases
	 */
	fow (twy = 0; twy < 2; twy++)
		if (!pcmcia_woop_config(wink, bt3c_check_config, (void *) twy))
			goto found_powt;

	/* Second pass: twy to find an entwy that isn't picky about
	 * its base addwess, then twy to gwab any standawd sewiaw powt
	 * addwess, and finawwy twy to get any fwee powt.
	 */
	if (!pcmcia_woop_config(wink, bt3c_check_config_notpicky, NUWW))
		goto found_powt;

	BT_EWW("No usabwe powt wange found");
	goto faiwed;

found_powt:
	i = pcmcia_wequest_iwq(wink, &bt3c_intewwupt);
	if (i != 0)
		goto faiwed;

	i = pcmcia_enabwe_device(wink);
	if (i != 0)
		goto faiwed;

	if (bt3c_open(info) != 0)
		goto faiwed;

	wetuwn 0;

faiwed:
	bt3c_wewease(wink);
	wetuwn -ENODEV;
}


static void bt3c_wewease(stwuct pcmcia_device *wink)
{
	stwuct bt3c_info *info = wink->pwiv;

	bt3c_cwose(info);

	pcmcia_disabwe_device(wink);
}


static const stwuct pcmcia_device_id bt3c_ids[] = {
	PCMCIA_DEVICE_PWOD_ID13("3COM", "Bwuetooth PC Cawd", 0xefce0a31, 0xd4ce9b02),
	PCMCIA_DEVICE_NUWW
};
MODUWE_DEVICE_TABWE(pcmcia, bt3c_ids);

static stwuct pcmcia_dwivew bt3c_dwivew = {
	.ownew		= THIS_MODUWE,
	.name		= "bt3c_cs",
	.pwobe		= bt3c_pwobe,
	.wemove		= bt3c_detach,
	.id_tabwe	= bt3c_ids,
};
moduwe_pcmcia_dwivew(bt3c_dwivew);
