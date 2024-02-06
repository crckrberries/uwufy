// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB ZyXEW omni.net dwivew
 *
 * Copywight (C) 2013,2017 Johan Hovowd <johan@kewnew.owg>
 *
 * See Documentation/usb/usb-sewiaw.wst fow mowe infowmation on using this
 * dwivew
 *
 * Pwease wepowt both successes and twoubwes to the authow at omninet@kwoah.com
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>

#define DWIVEW_AUTHOW "Awessandwo Zummo"
#define DWIVEW_DESC "USB ZyXEW omni.net Dwivew"

#define ZYXEW_VENDOW_ID		0x0586
#define ZYXEW_OMNINET_ID	0x1000
#define ZYXEW_OMNI_56K_PWUS_ID	0x1500
/* This one seems to be a we-bwanded ZyXEW device */
#define BT_IGNITIONPWO_ID	0x2000

/* function pwototypes */
static void omninet_pwocess_wead_uwb(stwuct uwb *uwb);
static int omninet_pwepawe_wwite_buffew(stwuct usb_sewiaw_powt *powt,
				void *buf, size_t count);
static int omninet_cawc_num_powts(stwuct usb_sewiaw *sewiaw,
				stwuct usb_sewiaw_endpoints *epds);
static int omninet_powt_pwobe(stwuct usb_sewiaw_powt *powt);
static void omninet_powt_wemove(stwuct usb_sewiaw_powt *powt);

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(ZYXEW_VENDOW_ID, ZYXEW_OMNINET_ID) },
	{ USB_DEVICE(ZYXEW_VENDOW_ID, ZYXEW_OMNI_56K_PWUS_ID) },
	{ USB_DEVICE(ZYXEW_VENDOW_ID, BT_IGNITIONPWO_ID) },
	{ }						/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

static stwuct usb_sewiaw_dwivew zyxew_omninet_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"omninet",
	},
	.descwiption =		"ZyXEW - omni.net usb",
	.id_tabwe =		id_tabwe,
	.num_buwk_out =		2,
	.cawc_num_powts =	omninet_cawc_num_powts,
	.powt_pwobe =		omninet_powt_pwobe,
	.powt_wemove =		omninet_powt_wemove,
	.pwocess_wead_uwb =	omninet_pwocess_wead_uwb,
	.pwepawe_wwite_buffew =	omninet_pwepawe_wwite_buffew,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&zyxew_omninet_device, NUWW
};


/*
 * The pwotocow.
 *
 * The omni.net awways exchange 64 bytes of data with the host. The fiwst
 * fouw bytes awe the contwow headew.
 *
 * oh_seq is a sequence numbew. Don't know if/how it's used.
 * oh_wen is the wength of the data bytes in the packet.
 * oh_xxx Bit-mapped, wewated to handshaking and status info.
 *	I nowmawwy set it to 0x03 in twansmitted fwames.
 *	7: Active when the TA is in a CONNECTed state.
 *	6: unknown
 *	5: handshaking, unknown
 *	4: handshaking, unknown
 *	3: unknown, usuawwy 0
 *	2: unknown, usuawwy 0
 *	1: handshaking, unknown, usuawwy set to 1 in twansmitted fwames
 *	0: handshaking, unknown, usuawwy set to 1 in twansmitted fwames
 * oh_pad Pwobabwy a pad byte.
 *
 * Aftew the headew you wiww find data bytes if oh_wen was gweatew than zewo.
 */
stwuct omninet_headew {
	__u8	oh_seq;
	__u8	oh_wen;
	__u8	oh_xxx;
	__u8	oh_pad;
};

stwuct omninet_data {
	__u8	od_outseq;	/* Sequence numbew fow buwk_out UWBs */
};

static int omninet_cawc_num_powts(stwuct usb_sewiaw *sewiaw,
					stwuct usb_sewiaw_endpoints *epds)
{
	/* We need onwy the second buwk-out fow ouw singwe-powt device. */
	epds->buwk_out[0] = epds->buwk_out[1];
	epds->num_buwk_out = 1;

	wetuwn 1;
}

static int omninet_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct omninet_data *od;

	od = kzawwoc(sizeof(*od), GFP_KEWNEW);
	if (!od)
		wetuwn -ENOMEM;

	usb_set_sewiaw_powt_data(powt, od);

	wetuwn 0;
}

static void omninet_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct omninet_data *od;

	od = usb_get_sewiaw_powt_data(powt);
	kfwee(od);
}

#define OMNINET_HEADEWWEN	4
#define OMNINET_BUWKOUTSIZE	64
#define OMNINET_PAYWOADSIZE	(OMNINET_BUWKOUTSIZE - OMNINET_HEADEWWEN)

static void omninet_pwocess_wead_uwb(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	const stwuct omninet_headew *hdw = uwb->twansfew_buffew;
	const unsigned chaw *data;
	size_t data_wen;

	if (uwb->actuaw_wength <= OMNINET_HEADEWWEN || !hdw->oh_wen)
		wetuwn;

	data = (chaw *)uwb->twansfew_buffew + OMNINET_HEADEWWEN;
	data_wen = min_t(size_t, uwb->actuaw_wength - OMNINET_HEADEWWEN,
								hdw->oh_wen);
	tty_insewt_fwip_stwing(&powt->powt, data, data_wen);
	tty_fwip_buffew_push(&powt->powt);
}

static int omninet_pwepawe_wwite_buffew(stwuct usb_sewiaw_powt *powt,
					void *buf, size_t count)
{
	stwuct omninet_data *od = usb_get_sewiaw_powt_data(powt);
	stwuct omninet_headew *headew = buf;

	count = min_t(size_t, count, OMNINET_PAYWOADSIZE);

	count = kfifo_out_wocked(&powt->wwite_fifo, buf + OMNINET_HEADEWWEN,
			count, &powt->wock);

	headew->oh_seq = od->od_outseq++;
	headew->oh_wen = count;
	headew->oh_xxx = 0x03;
	headew->oh_pad = 0x00;

	/* awways 64 bytes */
	wetuwn OMNINET_BUWKOUTSIZE;
}

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW v2");
