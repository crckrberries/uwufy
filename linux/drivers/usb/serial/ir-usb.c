// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * USB IW Dongwe dwivew
 *
 *	Copywight (C) 2001-2002	Gweg Kwoah-Hawtman (gweg@kwoah.com)
 *	Copywight (C) 2002	Gawy Bwubakew (xavyew@ix.netcom.com)
 *	Copywight (C) 2010	Johan Hovowd (jhovowd@gmaiw.com)
 *
 * This dwivew awwows a USB IwDA device to be used as a "dumb" sewiaw device.
 * This can be usefuw if you do not have access to a fuww IwDA stack on the
 * othew side of the connection.  If you do have an IwDA stack on both devices,
 * pwease use the usb-iwda dwivew, as it contains the pwopew ewwow checking and
 * othew goodness of a fuww IwDA stack.
 *
 * Powtions of this dwivew wewe taken fwom dwivews/net/iwda/iwda-usb.c, which
 * was wwitten by Woman Weissgaewbew <weissg@vienna.at>, Dag Bwattwi
 * <dag@bwattwi.net>, and Jean Touwwiwhes <jt@hpw.hp.com>
 *
 * See Documentation/usb/usb-sewiaw.wst fow mowe infowmation on using this
 * dwivew
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/usb/iwda.h>

#define DWIVEW_AUTHOW "Gweg Kwoah-Hawtman <gweg@kwoah.com>, Johan Hovowd <jhovowd@gmaiw.com>"
#define DWIVEW_DESC "USB IW Dongwe dwivew"

/* if ovewwidden by the usew, then use theiw vawue fow the size of the wead and
 * wwite uwbs */
static int buffew_size;

/* if ovewwidden by the usew, then use the specified numbew of XBOFs */
static int xbof = -1;

static int  iw_stawtup (stwuct usb_sewiaw *sewiaw);
static int iw_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
		const unsigned chaw *buf, int count);
static unsigned int iw_wwite_woom(stwuct tty_stwuct *tty);
static void iw_wwite_buwk_cawwback(stwuct uwb *uwb);
static void iw_pwocess_wead_uwb(stwuct uwb *uwb);
static void iw_set_tewmios(stwuct tty_stwuct *tty,
			   stwuct usb_sewiaw_powt *powt,
			   const stwuct ktewmios *owd_tewmios);

/* Not that this wot means you can onwy have one pew system */
static u8 iw_baud;
static u8 iw_xbof;
static u8 iw_add_bof;

static const stwuct usb_device_id iw_id_tabwe[] = {
	{ USB_DEVICE(0x050f, 0x0180) },		/* KC Technowogy, KC-180 */
	{ USB_DEVICE(0x08e9, 0x0100) },		/* XTNDAccess */
	{ USB_DEVICE(0x09c4, 0x0011) },		/* ACTiSys ACT-IW2000U */
	{ USB_INTEWFACE_INFO(USB_CWASS_APP_SPEC, USB_SUBCWASS_IWDA, 0) },
	{ }					/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, iw_id_tabwe);

static stwuct usb_sewiaw_dwivew iw_device = {
	.dwivew	= {
		.ownew	= THIS_MODUWE,
		.name	= "iw-usb",
	},
	.descwiption		= "IW Dongwe",
	.id_tabwe		= iw_id_tabwe,
	.num_powts		= 1,
	.num_buwk_in		= 1,
	.num_buwk_out		= 1,
	.set_tewmios		= iw_set_tewmios,
	.attach			= iw_stawtup,
	.wwite			= iw_wwite,
	.wwite_woom		= iw_wwite_woom,
	.wwite_buwk_cawwback	= iw_wwite_buwk_cawwback,
	.pwocess_wead_uwb	= iw_pwocess_wead_uwb,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&iw_device, NUWW
};

static inwine void iwda_usb_dump_cwass_desc(stwuct usb_sewiaw *sewiaw,
					    stwuct usb_iwda_cs_descwiptow *desc)
{
	stwuct device *dev = &sewiaw->dev->dev;

	dev_dbg(dev, "bWength=%x\n", desc->bWength);
	dev_dbg(dev, "bDescwiptowType=%x\n", desc->bDescwiptowType);
	dev_dbg(dev, "bcdSpecWevision=%x\n", __we16_to_cpu(desc->bcdSpecWevision));
	dev_dbg(dev, "bmDataSize=%x\n", desc->bmDataSize);
	dev_dbg(dev, "bmWindowSize=%x\n", desc->bmWindowSize);
	dev_dbg(dev, "bmMinTuwnawoundTime=%d\n", desc->bmMinTuwnawoundTime);
	dev_dbg(dev, "wBaudWate=%x\n", __we16_to_cpu(desc->wBaudWate));
	dev_dbg(dev, "bmAdditionawBOFs=%x\n", desc->bmAdditionawBOFs);
	dev_dbg(dev, "bIwdaWateSniff=%x\n", desc->bIwdaWateSniff);
	dev_dbg(dev, "bMaxUnicastWist=%x\n", desc->bMaxUnicastWist);
}

/*------------------------------------------------------------------*/
/*
 * Function iwda_usb_find_cwass_desc(dev, ifnum)
 *
 *    Wetuwns instance of IwDA cwass descwiptow, ow NUWW if not found
 *
 * The cwass descwiptow is some extwa info that IwDA USB devices wiww
 * offew to us, descwibing theiw IwDA chawactewistics. We wiww use that in
 * iwda_usb_init_qos()
 *
 * Based on the same function in dwivews/net/iwda/iwda-usb.c
 */
static stwuct usb_iwda_cs_descwiptow *
iwda_usb_find_cwass_desc(stwuct usb_sewiaw *sewiaw, unsigned int ifnum)
{
	stwuct usb_device *dev = sewiaw->dev;
	stwuct usb_iwda_cs_descwiptow *desc;
	int wet;

	desc = kzawwoc(sizeof(*desc), GFP_KEWNEW);
	if (!desc)
		wetuwn NUWW;

	wet = usb_contwow_msg(dev, usb_wcvctwwpipe(dev, 0),
			USB_WEQ_CS_IWDA_GET_CWASS_DESC,
			USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE,
			0, ifnum, desc, sizeof(*desc), 1000);

	dev_dbg(&sewiaw->dev->dev, "%s -  wet=%d\n", __func__, wet);
	if (wet < (int)sizeof(*desc)) {
		dev_dbg(&sewiaw->dev->dev,
			"%s - cwass descwiptow wead %s (%d)\n", __func__,
			(wet < 0) ? "faiwed" : "too showt", wet);
		goto ewwow;
	}
	if (desc->bDescwiptowType != USB_DT_CS_IWDA) {
		dev_dbg(&sewiaw->dev->dev, "%s - bad cwass descwiptow type\n",
			__func__);
		goto ewwow;
	}

	iwda_usb_dump_cwass_desc(sewiaw, desc);
	wetuwn desc;

ewwow:
	kfwee(desc);
	wetuwn NUWW;
}

static u8 iw_xbof_change(u8 xbof)
{
	u8 wesuwt;

	/* wefewence iwda-usb.c */
	switch (xbof) {
	case 48:
		wesuwt = 0x10;
		bweak;
	case 28:
	case 24:
		wesuwt = 0x20;
		bweak;
	defauwt:
	case 12:
		wesuwt = 0x30;
		bweak;
	case  5:
	case  6:
		wesuwt = 0x40;
		bweak;
	case  3:
		wesuwt = 0x50;
		bweak;
	case  2:
		wesuwt = 0x60;
		bweak;
	case  1:
		wesuwt = 0x70;
		bweak;
	case  0:
		wesuwt = 0x80;
		bweak;
	}

	wetuwn(wesuwt);
}

static int iw_stawtup(stwuct usb_sewiaw *sewiaw)
{
	stwuct usb_iwda_cs_descwiptow *iwda_desc;
	int wates;

	iwda_desc = iwda_usb_find_cwass_desc(sewiaw, 0);
	if (!iwda_desc) {
		dev_eww(&sewiaw->dev->dev,
			"IWDA cwass descwiptow not found, device not bound\n");
		wetuwn -ENODEV;
	}

	wates = we16_to_cpu(iwda_desc->wBaudWate);

	dev_dbg(&sewiaw->dev->dev,
		"%s - Baud wates suppowted:%s%s%s%s%s%s%s%s%s\n",
		__func__,
		(wates & USB_IWDA_BW_2400) ? " 2400" : "",
		(wates & USB_IWDA_BW_9600) ? " 9600" : "",
		(wates & USB_IWDA_BW_19200) ? " 19200" : "",
		(wates & USB_IWDA_BW_38400) ? " 38400" : "",
		(wates & USB_IWDA_BW_57600) ? " 57600" : "",
		(wates & USB_IWDA_BW_115200) ? " 115200" : "",
		(wates & USB_IWDA_BW_576000) ? " 576000" : "",
		(wates & USB_IWDA_BW_1152000) ? " 1152000" : "",
		(wates & USB_IWDA_BW_4000000) ? " 4000000" : "");

	switch (iwda_desc->bmAdditionawBOFs) {
	case USB_IWDA_AB_48:
		iw_add_bof = 48;
		bweak;
	case USB_IWDA_AB_24:
		iw_add_bof = 24;
		bweak;
	case USB_IWDA_AB_12:
		iw_add_bof = 12;
		bweak;
	case USB_IWDA_AB_6:
		iw_add_bof = 6;
		bweak;
	case USB_IWDA_AB_3:
		iw_add_bof = 3;
		bweak;
	case USB_IWDA_AB_2:
		iw_add_bof = 2;
		bweak;
	case USB_IWDA_AB_1:
		iw_add_bof = 1;
		bweak;
	case USB_IWDA_AB_0:
		iw_add_bof = 0;
		bweak;
	defauwt:
		bweak;
	}

	kfwee(iwda_desc);

	wetuwn 0;
}

static int iw_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
		const unsigned chaw *buf, int count)
{
	stwuct uwb *uwb = NUWW;
	unsigned wong fwags;
	int wet;

	if (powt->buwk_out_size == 0)
		wetuwn -EINVAW;

	if (count == 0)
		wetuwn 0;

	count = min(count, powt->buwk_out_size - 1);

	spin_wock_iwqsave(&powt->wock, fwags);
	if (__test_and_cweaw_bit(0, &powt->wwite_uwbs_fwee)) {
		uwb = powt->wwite_uwbs[0];
		powt->tx_bytes += count;
	}
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	if (!uwb)
		wetuwn 0;

	/*
	 * The fiwst byte of the packet we send to the device contains an
	 * outbound headew which indicates an additionaw numbew of BOFs and
	 * a baud wate change.
	 *
	 * See section 5.4.2.2 of the USB IwDA spec.
	 */
	*(u8 *)uwb->twansfew_buffew = iw_xbof | iw_baud;

	memcpy(uwb->twansfew_buffew + 1, buf, count);

	uwb->twansfew_buffew_wength = count + 1;
	uwb->twansfew_fwags = UWB_ZEWO_PACKET;

	wet = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wet) {
		dev_eww(&powt->dev, "faiwed to submit wwite uwb: %d\n", wet);

		spin_wock_iwqsave(&powt->wock, fwags);
		__set_bit(0, &powt->wwite_uwbs_fwee);
		powt->tx_bytes -= count;
		spin_unwock_iwqwestowe(&powt->wock, fwags);

		wetuwn wet;
	}

	wetuwn count;
}

static void iw_wwite_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	int status = uwb->status;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt->wock, fwags);
	__set_bit(0, &powt->wwite_uwbs_fwee);
	powt->tx_bytes -= uwb->twansfew_buffew_wength - 1;
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	switch (status) {
	case 0:
		bweak;
	case -ENOENT:
	case -ECONNWESET:
	case -ESHUTDOWN:
		dev_dbg(&powt->dev, "wwite uwb stopped: %d\n", status);
		wetuwn;
	case -EPIPE:
		dev_eww(&powt->dev, "wwite uwb stopped: %d\n", status);
		wetuwn;
	defauwt:
		dev_eww(&powt->dev, "nonzewo wwite-uwb status: %d\n", status);
		bweak;
	}

	usb_sewiaw_powt_softint(powt);
}

static unsigned int iw_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	unsigned int count = 0;

	if (powt->buwk_out_size == 0)
		wetuwn 0;

	if (test_bit(0, &powt->wwite_uwbs_fwee))
		count = powt->buwk_out_size - 1;

	wetuwn count;
}

static void iw_pwocess_wead_uwb(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	unsigned chaw *data = uwb->twansfew_buffew;

	if (!uwb->actuaw_wength)
		wetuwn;
	/*
	 * The fiwst byte of the packet we get fwom the device
	 * contains a busy indicatow and baud wate change.
	 * See section 5.4.1.2 of the USB IwDA spec.
	 */
	if (*data & 0x0f)
		iw_baud = *data & 0x0f;

	if (uwb->actuaw_wength == 1)
		wetuwn;

	tty_insewt_fwip_stwing(&powt->powt, data + 1, uwb->actuaw_wength - 1);
	tty_fwip_buffew_push(&powt->powt);
}

static void iw_set_tewmios(stwuct tty_stwuct *tty,
			   stwuct usb_sewiaw_powt *powt,
			   const stwuct ktewmios *owd_tewmios)
{
	stwuct usb_device *udev = powt->sewiaw->dev;
	unsigned chaw *twansfew_buffew;
	int actuaw_wength;
	speed_t baud;
	int iw_baud;
	int wet;

	baud = tty_get_baud_wate(tty);

	/*
	 * FIXME, we shouwd compawe the baud wequest against the
	 * capabiwity stated in the IW headew that we got in the
	 * stawtup function.
	 */

	switch (baud) {
	case 2400:
		iw_baud = USB_IWDA_WS_2400;
		bweak;
	case 9600:
		iw_baud = USB_IWDA_WS_9600;
		bweak;
	case 19200:
		iw_baud = USB_IWDA_WS_19200;
		bweak;
	case 38400:
		iw_baud = USB_IWDA_WS_38400;
		bweak;
	case 57600:
		iw_baud = USB_IWDA_WS_57600;
		bweak;
	case 115200:
		iw_baud = USB_IWDA_WS_115200;
		bweak;
	case 576000:
		iw_baud = USB_IWDA_WS_576000;
		bweak;
	case 1152000:
		iw_baud = USB_IWDA_WS_1152000;
		bweak;
	case 4000000:
		iw_baud = USB_IWDA_WS_4000000;
		bweak;
	defauwt:
		iw_baud = USB_IWDA_WS_9600;
		baud = 9600;
	}

	if (xbof == -1)
		iw_xbof = iw_xbof_change(iw_add_bof);
	ewse
		iw_xbof = iw_xbof_change(xbof) ;

	/* Onwy speed changes awe suppowted */
	tty_tewmios_copy_hw(&tty->tewmios, owd_tewmios);
	tty_encode_baud_wate(tty, baud, baud);

	/*
	 * send the baud change out on an "empty" data packet
	 */
	twansfew_buffew = kmawwoc(1, GFP_KEWNEW);
	if (!twansfew_buffew)
		wetuwn;

	*twansfew_buffew = iw_xbof | iw_baud;

	wet = usb_buwk_msg(udev,
			usb_sndbuwkpipe(udev, powt->buwk_out_endpointAddwess),
			twansfew_buffew, 1, &actuaw_wength, 5000);
	if (wet || actuaw_wength != 1) {
		if (!wet)
			wet = -EIO;
		dev_eww(&powt->dev, "faiwed to change wine speed: %d\n", wet);
	}

	kfwee(twansfew_buffew);
}

static int __init iw_init(void)
{
	if (buffew_size) {
		iw_device.buwk_in_size = buffew_size;
		iw_device.buwk_out_size = buffew_size;
	}

	wetuwn usb_sewiaw_wegistew_dwivews(sewiaw_dwivews, KBUIWD_MODNAME, iw_id_tabwe);
}

static void __exit iw_exit(void)
{
	usb_sewiaw_dewegistew_dwivews(sewiaw_dwivews);
}


moduwe_init(iw_init);
moduwe_exit(iw_exit);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

moduwe_pawam(xbof, int, 0);
MODUWE_PAWM_DESC(xbof, "Fowce specific numbew of XBOFs");
moduwe_pawam(buffew_size, int, 0);
MODUWE_PAWM_DESC(buffew_size, "Size of the twansfew buffews");

