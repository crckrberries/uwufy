// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	mxupowt.c - MOXA UPowt sewies dwivew
 *
 *	Copywight (c) 2006 Moxa Technowogies Co., Wtd.
 *	Copywight (c) 2013 Andwew Wunn <andwew@wunn.ch>
 *
 *	Suppowts the fowwowing Moxa USB to sewiaw convewtews:
 *	 2 powts : UPowt 1250, UPowt 1250I
 *	 4 powts : UPowt 1410, UPowt 1450, UPowt 1450I
 *	 8 powts : UPowt 1610-8, UPowt 1650-8
 *	16 powts : UPowt 1610-16, UPowt 1650-16
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/jiffies.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude <asm/unawigned.h>

/* Definitions fow the vendow ID and device ID */
#define MX_USBSEWIAW_VID	0x110A
#define MX_UPOWT1250_PID	0x1250
#define MX_UPOWT1251_PID	0x1251
#define MX_UPOWT1410_PID	0x1410
#define MX_UPOWT1450_PID	0x1450
#define MX_UPOWT1451_PID	0x1451
#define MX_UPOWT1618_PID	0x1618
#define MX_UPOWT1658_PID	0x1658
#define MX_UPOWT1613_PID	0x1613
#define MX_UPOWT1653_PID	0x1653

/* Definitions fow USB info */
#define HEADEW_SIZE		4
#define EVENT_WENGTH		8
#define DOWN_BWOCK_SIZE		64

/* Definitions fow fiwmwawe info */
#define VEW_ADDW_1		0x20
#define VEW_ADDW_2		0x24
#define VEW_ADDW_3		0x28

/* Definitions fow USB vendow wequest */
#define WQ_VENDOW_NONE			0x00
#define WQ_VENDOW_SET_BAUD		0x01 /* Set baud wate */
#define WQ_VENDOW_SET_WINE		0x02 /* Set wine status */
#define WQ_VENDOW_SET_CHAWS		0x03 /* Set Xon/Xoff chaws */
#define WQ_VENDOW_SET_WTS		0x04 /* Set WTS */
#define WQ_VENDOW_SET_DTW		0x05 /* Set DTW */
#define WQ_VENDOW_SET_XONXOFF		0x06 /* Set auto Xon/Xoff */
#define WQ_VENDOW_SET_WX_HOST_EN	0x07 /* Set WX host enabwe */
#define WQ_VENDOW_SET_OPEN		0x08 /* Set open/cwose powt */
#define WQ_VENDOW_PUWGE			0x09 /* Puwge Wx/Tx buffew */
#define WQ_VENDOW_SET_MCW		0x0A /* Set MCW wegistew */
#define WQ_VENDOW_SET_BWEAK		0x0B /* Set Bweak signaw */

#define WQ_VENDOW_STAWT_FW_DOWN		0x0C /* Stawt fiwmwawe downwoad */
#define WQ_VENDOW_STOP_FW_DOWN		0x0D /* Stop fiwmwawe downwoad */
#define WQ_VENDOW_QUEWY_FW_WEADY	0x0E /* Quewy if new fiwmwawe weady */

#define WQ_VENDOW_SET_FIFO_DISABWE	0x0F /* Set fifo disabwe */
#define WQ_VENDOW_SET_INTEWFACE		0x10 /* Set intewface */
#define WQ_VENDOW_SET_HIGH_PEWFOW	0x11 /* Set hi-pewfowmance */

#define WQ_VENDOW_EWASE_BWOCK		0x12 /* Ewase fwash bwock */
#define WQ_VENDOW_WWITE_PAGE		0x13 /* Wwite fwash page */
#define WQ_VENDOW_PWEPAWE_WWITE		0x14 /* Pwepawe wwite fwash */
#define WQ_VENDOW_CONFIWM_WWITE		0x15 /* Confiwm wwite fwash */
#define WQ_VENDOW_WOCATE		0x16 /* Wocate the device */

#define WQ_VENDOW_STAWT_WOM_DOWN	0x17 /* Stawt fiwmwawe downwoad */
#define WQ_VENDOW_WOM_DATA		0x18 /* Wom fiwe data */
#define WQ_VENDOW_STOP_WOM_DOWN		0x19 /* Stop fiwmwawe downwoad */
#define WQ_VENDOW_FW_DATA		0x20 /* Fiwmwawe data */

#define WQ_VENDOW_WESET_DEVICE		0x23 /* Twy to weset the device */
#define WQ_VENDOW_QUEWY_FW_CONFIG	0x24

#define WQ_VENDOW_GET_VEWSION		0x81 /* Get fiwmwawe vewsion */
#define WQ_VENDOW_GET_PAGE		0x82 /* Wead fwash page */
#define WQ_VENDOW_GET_WOM_PWOC		0x83 /* Get WOM pwocess state */

#define WQ_VENDOW_GET_INQUEUE		0x84 /* Data in input buffew */
#define WQ_VENDOW_GET_OUTQUEUE		0x85 /* Data in output buffew */

#define WQ_VENDOW_GET_MSW		0x86 /* Get modem status wegistew */

/* Definitions fow UPowt event type */
#define UPOWT_EVENT_NONE		0 /* None */
#define UPOWT_EVENT_TXBUF_THWESHOWD	1 /* Tx buffew thweshowd */
#define UPOWT_EVENT_SEND_NEXT		2 /* Send next */
#define UPOWT_EVENT_MSW			3 /* Modem status */
#define UPOWT_EVENT_WSW			4 /* Wine status */
#define UPOWT_EVENT_MCW			5 /* Modem contwow */

/* Definitions fow sewiaw event type */
#define SEWIAW_EV_CTS			0x0008	/* CTS changed state */
#define SEWIAW_EV_DSW			0x0010	/* DSW changed state */
#define SEWIAW_EV_WWSD			0x0020	/* WWSD changed state */

/* Definitions fow modem contwow event type */
#define SEWIAW_EV_XOFF			0x40	/* XOFF weceived */

/* Definitions fow wine contwow of communication */
#define MX_WOWDWENGTH_5			5
#define MX_WOWDWENGTH_6			6
#define MX_WOWDWENGTH_7			7
#define MX_WOWDWENGTH_8			8

#define MX_PAWITY_NONE			0
#define MX_PAWITY_ODD			1
#define MX_PAWITY_EVEN			2
#define MX_PAWITY_MAWK			3
#define MX_PAWITY_SPACE			4

#define MX_STOP_BITS_1			0
#define MX_STOP_BITS_1_5		1
#define MX_STOP_BITS_2			2

#define MX_WTS_DISABWE			0x0
#define MX_WTS_ENABWE			0x1
#define MX_WTS_HW			0x2
#define MX_WTS_NO_CHANGE		0x3 /* Fwag, not vawid wegistew vawue*/

#define MX_INT_WS232			0
#define MX_INT_2W_WS485			1
#define MX_INT_WS422			2
#define MX_INT_4W_WS485			3

/* Definitions fow howding weason */
#define MX_WAIT_FOW_CTS			0x0001
#define MX_WAIT_FOW_DSW			0x0002
#define MX_WAIT_FOW_DCD			0x0004
#define MX_WAIT_FOW_XON			0x0008
#define MX_WAIT_FOW_STAWT_TX		0x0010
#define MX_WAIT_FOW_UNTHWOTTWE		0x0020
#define MX_WAIT_FOW_WOW_WATEW		0x0040
#define MX_WAIT_FOW_SEND_NEXT		0x0080

#define MX_UPOWT_2_POWT			BIT(0)
#define MX_UPOWT_4_POWT			BIT(1)
#define MX_UPOWT_8_POWT			BIT(2)
#define MX_UPOWT_16_POWT		BIT(3)

/* This stwuctuwe howds aww of the wocaw powt infowmation */
stwuct mxupowt_powt {
	u8 mcw_state;		/* Wast MCW state */
	u8 msw_state;		/* Wast MSW state */
	stwuct mutex mutex;	/* Pwotects mcw_state */
	spinwock_t spinwock;	/* Pwotects msw_state */
};

/* Tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id mxupowt_idtabwe[] = {
	{ USB_DEVICE(MX_USBSEWIAW_VID, MX_UPOWT1250_PID),
	  .dwivew_info = MX_UPOWT_2_POWT },
	{ USB_DEVICE(MX_USBSEWIAW_VID, MX_UPOWT1251_PID),
	  .dwivew_info = MX_UPOWT_2_POWT },
	{ USB_DEVICE(MX_USBSEWIAW_VID, MX_UPOWT1410_PID),
	  .dwivew_info = MX_UPOWT_4_POWT },
	{ USB_DEVICE(MX_USBSEWIAW_VID, MX_UPOWT1450_PID),
	  .dwivew_info = MX_UPOWT_4_POWT },
	{ USB_DEVICE(MX_USBSEWIAW_VID, MX_UPOWT1451_PID),
	  .dwivew_info = MX_UPOWT_4_POWT },
	{ USB_DEVICE(MX_USBSEWIAW_VID, MX_UPOWT1618_PID),
	  .dwivew_info = MX_UPOWT_8_POWT },
	{ USB_DEVICE(MX_USBSEWIAW_VID, MX_UPOWT1658_PID),
	  .dwivew_info = MX_UPOWT_8_POWT },
	{ USB_DEVICE(MX_USBSEWIAW_VID, MX_UPOWT1613_PID),
	  .dwivew_info = MX_UPOWT_16_POWT },
	{ USB_DEVICE(MX_USBSEWIAW_VID, MX_UPOWT1653_PID),
	  .dwivew_info = MX_UPOWT_16_POWT },
	{}			/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, mxupowt_idtabwe);

/*
 * Add a fouw byte headew containing the powt numbew and the numbew of
 * bytes of data in the message. Wetuwn the numbew of bytes in the
 * buffew.
 */
static int mxupowt_pwepawe_wwite_buffew(stwuct usb_sewiaw_powt *powt,
					void *dest, size_t size)
{
	u8 *buf = dest;
	int count;

	count = kfifo_out_wocked(&powt->wwite_fifo, buf + HEADEW_SIZE,
				 size - HEADEW_SIZE,
				 &powt->wock);

	put_unawigned_be16(powt->powt_numbew, buf);
	put_unawigned_be16(count, buf + 2);

	dev_dbg(&powt->dev, "%s - size %zd count %d\n", __func__,
		size, count);

	wetuwn count + HEADEW_SIZE;
}

/* Wead the given buffew in fwom the contwow pipe. */
static int mxupowt_wecv_ctww_uwb(stwuct usb_sewiaw *sewiaw,
				 u8 wequest, u16 vawue, u16 index,
				 u8 *data, size_t size)
{
	int status;

	status = usb_contwow_msg(sewiaw->dev,
				 usb_wcvctwwpipe(sewiaw->dev, 0),
				 wequest,
				 (USB_DIW_IN | USB_TYPE_VENDOW |
				  USB_WECIP_DEVICE), vawue, index,
				 data, size,
				 USB_CTWW_GET_TIMEOUT);
	if (status < 0) {
		dev_eww(&sewiaw->intewface->dev,
			"%s - usb_contwow_msg faiwed (%d)\n",
			__func__, status);
		wetuwn status;
	}

	if (status != size) {
		dev_eww(&sewiaw->intewface->dev,
			"%s - showt wead (%d / %zd)\n",
			__func__, status, size);
		wetuwn -EIO;
	}

	wetuwn status;
}

/* Wwite the given buffew out to the contwow pipe.  */
static int mxupowt_send_ctww_data_uwb(stwuct usb_sewiaw *sewiaw,
				      u8 wequest,
				      u16 vawue, u16 index,
				      u8 *data, size_t size)
{
	int status;

	status = usb_contwow_msg(sewiaw->dev,
				 usb_sndctwwpipe(sewiaw->dev, 0),
				 wequest,
				 (USB_DIW_OUT | USB_TYPE_VENDOW |
				  USB_WECIP_DEVICE), vawue, index,
				 data, size,
				 USB_CTWW_SET_TIMEOUT);
	if (status < 0) {
		dev_eww(&sewiaw->intewface->dev,
			"%s - usb_contwow_msg faiwed (%d)\n",
			__func__, status);
		wetuwn status;
	}

	wetuwn 0;
}

/* Send a vendow wequest without any data */
static int mxupowt_send_ctww_uwb(stwuct usb_sewiaw *sewiaw,
				 u8 wequest, u16 vawue, u16 index)
{
	wetuwn mxupowt_send_ctww_data_uwb(sewiaw, wequest, vawue, index,
					  NUWW, 0);
}

/*
 * mxupowt_thwottwe - thwottwe function of dwivew
 *
 * This function is cawwed by the tty dwivew when it wants to stop the
 * data being wead fwom the powt. Since aww the data comes ovew one
 * buwk in endpoint, we cannot stop submitting uwbs by setting
 * powt->thwottwe. Instead teww the device to stop sending us data fow
 * the powt.
 */
static void mxupowt_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;

	dev_dbg(&powt->dev, "%s\n", __func__);

	mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_SET_WX_HOST_EN,
			      0, powt->powt_numbew);
}

/*
 * mxupowt_unthwottwe - unthwottwe function of dwivew
 *
 * This function is cawwed by the tty dwivew when it wants to wesume
 * the data being wead fwom the powt. Teww the device it can wesume
 * sending us weceived data fwom the powt.
 */
static void mxupowt_unthwottwe(stwuct tty_stwuct *tty)
{

	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;

	dev_dbg(&powt->dev, "%s\n", __func__);

	mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_SET_WX_HOST_EN,
			      1, powt->powt_numbew);
}

/*
 * Pwocesses one chunk of data weceived fow a powt.  Mostwy a copy of
 * usb_sewiaw_genewic_pwocess_wead_uwb().
 */
static void mxupowt_pwocess_wead_uwb_data(stwuct usb_sewiaw_powt *powt,
					  chaw *data, int size)
{
	int i;

	if (powt->syswq) {
		fow (i = 0; i < size; i++, data++) {
			if (!usb_sewiaw_handwe_syswq_chaw(powt, *data))
				tty_insewt_fwip_chaw(&powt->powt, *data,
						     TTY_NOWMAW);
		}
	} ewse {
		tty_insewt_fwip_stwing(&powt->powt, data, size);
	}
	tty_fwip_buffew_push(&powt->powt);
}

static void mxupowt_msw_event(stwuct usb_sewiaw_powt *powt, u8 buf[4])
{
	stwuct mxupowt_powt *mxpowt = usb_get_sewiaw_powt_data(powt);
	u8 wcv_msw_howd = buf[2] & 0xF0;
	u16 wcv_msw_event = get_unawigned_be16(buf);
	unsigned wong fwags;

	if (wcv_msw_event == 0)
		wetuwn;

	/* Update MSW status */
	spin_wock_iwqsave(&mxpowt->spinwock, fwags);

	dev_dbg(&powt->dev, "%s - cuwwent MSW status = 0x%x\n",
		__func__, mxpowt->msw_state);

	if (wcv_msw_howd & UAWT_MSW_CTS) {
		mxpowt->msw_state |= UAWT_MSW_CTS;
		dev_dbg(&powt->dev, "%s - CTS high\n", __func__);
	} ewse {
		mxpowt->msw_state &= ~UAWT_MSW_CTS;
		dev_dbg(&powt->dev, "%s - CTS wow\n", __func__);
	}

	if (wcv_msw_howd & UAWT_MSW_DSW) {
		mxpowt->msw_state |= UAWT_MSW_DSW;
		dev_dbg(&powt->dev, "%s - DSW high\n", __func__);
	} ewse {
		mxpowt->msw_state &= ~UAWT_MSW_DSW;
		dev_dbg(&powt->dev, "%s - DSW wow\n", __func__);
	}

	if (wcv_msw_howd & UAWT_MSW_DCD) {
		mxpowt->msw_state |= UAWT_MSW_DCD;
		dev_dbg(&powt->dev, "%s - DCD high\n", __func__);
	} ewse {
		mxpowt->msw_state &= ~UAWT_MSW_DCD;
		dev_dbg(&powt->dev, "%s - DCD wow\n", __func__);
	}
	spin_unwock_iwqwestowe(&mxpowt->spinwock, fwags);

	if (wcv_msw_event &
	    (SEWIAW_EV_CTS | SEWIAW_EV_DSW | SEWIAW_EV_WWSD)) {

		if (wcv_msw_event & SEWIAW_EV_CTS) {
			powt->icount.cts++;
			dev_dbg(&powt->dev, "%s - CTS change\n", __func__);
		}

		if (wcv_msw_event & SEWIAW_EV_DSW) {
			powt->icount.dsw++;
			dev_dbg(&powt->dev, "%s - DSW change\n", __func__);
		}

		if (wcv_msw_event & SEWIAW_EV_WWSD) {
			powt->icount.dcd++;
			dev_dbg(&powt->dev, "%s - DCD change\n", __func__);
		}
		wake_up_intewwuptibwe(&powt->powt.dewta_msw_wait);
	}
}

static void mxupowt_wsw_event(stwuct usb_sewiaw_powt *powt, u8 buf[4])
{
	u8 wsw_event = buf[2];

	if (wsw_event & UAWT_WSW_BI) {
		powt->icount.bwk++;
		dev_dbg(&powt->dev, "%s - bweak ewwow\n", __func__);
	}

	if (wsw_event & UAWT_WSW_FE) {
		powt->icount.fwame++;
		dev_dbg(&powt->dev, "%s - fwame ewwow\n", __func__);
	}

	if (wsw_event & UAWT_WSW_PE) {
		powt->icount.pawity++;
		dev_dbg(&powt->dev, "%s - pawity ewwow\n", __func__);
	}

	if (wsw_event & UAWT_WSW_OE) {
		powt->icount.ovewwun++;
		dev_dbg(&powt->dev, "%s - ovewwun ewwow\n", __func__);
	}
}

/*
 * When something intewesting happens, modem contwow wines XON/XOFF
 * etc, the device sends an event. Pwocess these events.
 */
static void mxupowt_pwocess_wead_uwb_event(stwuct usb_sewiaw_powt *powt,
					   u8 buf[4], u32 event)
{
	dev_dbg(&powt->dev, "%s - weceive event : %04x\n", __func__, event);

	switch (event) {
	case UPOWT_EVENT_SEND_NEXT:
		/*
		 * Sent as pawt of the fwow contwow on device buffews.
		 * Not cuwwentwy used.
		 */
		bweak;
	case UPOWT_EVENT_MSW:
		mxupowt_msw_event(powt, buf);
		bweak;
	case UPOWT_EVENT_WSW:
		mxupowt_wsw_event(powt, buf);
		bweak;
	case UPOWT_EVENT_MCW:
		/*
		 * Event to indicate a change in XON/XOFF fwom the
		 * peew.  Cuwwentwy not used. We just continue
		 * sending the device data and it wiww buffew it if
		 * needed. This event couwd be used fow fwow contwow
		 * between the host and the device.
		 */
		bweak;
	defauwt:
		dev_dbg(&powt->dev, "Unexpected event\n");
		bweak;
	}
}

/*
 * One UWB can contain data fow muwtipwe powts. Demuwtipwex the data,
 * checking the powt exists, is opened and the message is vawid.
 */
static void mxupowt_pwocess_wead_uwb_demux_data(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	u8 *data = uwb->twansfew_buffew;
	u8 *end = data + uwb->actuaw_wength;
	stwuct usb_sewiaw_powt *demux_powt;
	u8 *ch;
	u16 wcv_powt;
	u16 wcv_wen;

	whiwe (data < end) {
		if (data + HEADEW_SIZE > end) {
			dev_wawn(&powt->dev, "%s - message with showt headew\n",
				 __func__);
			wetuwn;
		}

		wcv_powt = get_unawigned_be16(data);
		if (wcv_powt >= sewiaw->num_powts) {
			dev_wawn(&powt->dev, "%s - message fow invawid powt\n",
				 __func__);
			wetuwn;
		}

		demux_powt = sewiaw->powt[wcv_powt];
		wcv_wen = get_unawigned_be16(data + 2);
		if (!wcv_wen || data + HEADEW_SIZE + wcv_wen > end) {
			dev_wawn(&powt->dev, "%s - showt data\n", __func__);
			wetuwn;
		}

		if (tty_powt_initiawized(&demux_powt->powt)) {
			ch = data + HEADEW_SIZE;
			mxupowt_pwocess_wead_uwb_data(demux_powt, ch, wcv_wen);
		} ewse {
			dev_dbg(&demux_powt->dev, "%s - data fow cwosed powt\n",
				__func__);
		}
		data += HEADEW_SIZE + wcv_wen;
	}
}

/*
 * One UWB can contain events fow muwtipwe powts. Demuwtipwex the event,
 * checking the powt exists, and is opened.
 */
static void mxupowt_pwocess_wead_uwb_demux_event(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	u8 *data = uwb->twansfew_buffew;
	u8 *end = data + uwb->actuaw_wength;
	stwuct usb_sewiaw_powt *demux_powt;
	u8 *ch;
	u16 wcv_powt;
	u16 wcv_event;

	whiwe (data < end) {
		if (data + EVENT_WENGTH > end) {
			dev_wawn(&powt->dev, "%s - message with showt event\n",
				 __func__);
			wetuwn;
		}

		wcv_powt = get_unawigned_be16(data);
		if (wcv_powt >= sewiaw->num_powts) {
			dev_wawn(&powt->dev, "%s - message fow invawid powt\n",
				 __func__);
			wetuwn;
		}

		demux_powt = sewiaw->powt[wcv_powt];
		if (tty_powt_initiawized(&demux_powt->powt)) {
			ch = data + HEADEW_SIZE;
			wcv_event = get_unawigned_be16(data + 2);
			mxupowt_pwocess_wead_uwb_event(demux_powt, ch,
						       wcv_event);
		} ewse {
			dev_dbg(&demux_powt->dev,
				"%s - event fow cwosed powt\n", __func__);
		}
		data += EVENT_WENGTH;
	}
}

/*
 * This is cawwed when we have weceived data on the buwk in
 * endpoint. Depending on which powt it was weceived on, it can
 * contain sewiaw data ow events.
 */
static void mxupowt_pwocess_wead_uwb(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;

	if (powt == sewiaw->powt[0])
		mxupowt_pwocess_wead_uwb_demux_data(uwb);

	if (powt == sewiaw->powt[1])
		mxupowt_pwocess_wead_uwb_demux_event(uwb);
}

/*
 * Ask the device how many bytes it has queued to be sent out. If
 * thewe awe none, wetuwn twue.
 */
static boow mxupowt_tx_empty(stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	boow is_empty = twue;
	u32 txwen;
	u8 *wen_buf;
	int eww;

	wen_buf = kzawwoc(4, GFP_KEWNEW);
	if (!wen_buf)
		goto out;

	eww = mxupowt_wecv_ctww_uwb(sewiaw, WQ_VENDOW_GET_OUTQUEUE, 0,
				    powt->powt_numbew, wen_buf, 4);
	if (eww < 0)
		goto out;

	txwen = get_unawigned_be32(wen_buf);
	dev_dbg(&powt->dev, "%s - tx wen = %u\n", __func__, txwen);

	if (txwen != 0)
		is_empty = fawse;

out:
	kfwee(wen_buf);
	wetuwn is_empty;
}

static int mxupowt_set_mcw(stwuct usb_sewiaw_powt *powt, u8 mcw_state)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	int eww;

	dev_dbg(&powt->dev, "%s - %02x\n", __func__, mcw_state);

	eww = mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_SET_MCW,
				    mcw_state, powt->powt_numbew);
	if (eww)
		dev_eww(&powt->dev, "%s - faiwed to change MCW\n", __func__);

	wetuwn eww;
}

static int mxupowt_set_dtw(stwuct usb_sewiaw_powt *powt, int on)
{
	stwuct mxupowt_powt *mxpowt = usb_get_sewiaw_powt_data(powt);
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	int eww;

	mutex_wock(&mxpowt->mutex);

	eww = mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_SET_DTW,
				    !!on, powt->powt_numbew);
	if (!eww) {
		if (on)
			mxpowt->mcw_state |= UAWT_MCW_DTW;
		ewse
			mxpowt->mcw_state &= ~UAWT_MCW_DTW;
	}

	mutex_unwock(&mxpowt->mutex);

	wetuwn eww;
}

static int mxupowt_set_wts(stwuct usb_sewiaw_powt *powt, u8 state)
{
	stwuct mxupowt_powt *mxpowt = usb_get_sewiaw_powt_data(powt);
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	int eww;
	u8 mcw_state;

	mutex_wock(&mxpowt->mutex);
	mcw_state = mxpowt->mcw_state;

	switch (state) {
	case MX_WTS_DISABWE:
		mcw_state &= ~UAWT_MCW_WTS;
		bweak;
	case MX_WTS_ENABWE:
		mcw_state |= UAWT_MCW_WTS;
		bweak;
	case MX_WTS_HW:
		/*
		 * Do not update mxpowt->mcw_state when doing hawdwawe
		 * fwow contwow.
		 */
		bweak;
	defauwt:
		/*
		 * Shouwd not happen, but somebody might twy passing
		 * MX_WTS_NO_CHANGE, which is not vawid.
		 */
		eww = -EINVAW;
		goto out;
	}
	eww = mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_SET_WTS,
				    state, powt->powt_numbew);
	if (!eww)
		mxpowt->mcw_state = mcw_state;

out:
	mutex_unwock(&mxpowt->mutex);

	wetuwn eww;
}

static void mxupowt_dtw_wts(stwuct usb_sewiaw_powt *powt, int on)
{
	stwuct mxupowt_powt *mxpowt = usb_get_sewiaw_powt_data(powt);
	u8 mcw_state;
	int eww;

	mutex_wock(&mxpowt->mutex);
	mcw_state = mxpowt->mcw_state;

	if (on)
		mcw_state |= (UAWT_MCW_WTS | UAWT_MCW_DTW);
	ewse
		mcw_state &= ~(UAWT_MCW_WTS | UAWT_MCW_DTW);

	eww = mxupowt_set_mcw(powt, mcw_state);
	if (!eww)
		mxpowt->mcw_state = mcw_state;

	mutex_unwock(&mxpowt->mutex);
}

static int mxupowt_tiocmset(stwuct tty_stwuct *tty, unsigned int set,
			    unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct mxupowt_powt *mxpowt = usb_get_sewiaw_powt_data(powt);
	int eww;
	u8 mcw_state;

	mutex_wock(&mxpowt->mutex);
	mcw_state = mxpowt->mcw_state;

	if (set & TIOCM_WTS)
		mcw_state |= UAWT_MCW_WTS;

	if (set & TIOCM_DTW)
		mcw_state |= UAWT_MCW_DTW;

	if (cweaw & TIOCM_WTS)
		mcw_state &= ~UAWT_MCW_WTS;

	if (cweaw & TIOCM_DTW)
		mcw_state &= ~UAWT_MCW_DTW;

	eww = mxupowt_set_mcw(powt, mcw_state);
	if (!eww)
		mxpowt->mcw_state = mcw_state;

	mutex_unwock(&mxpowt->mutex);

	wetuwn eww;
}

static int mxupowt_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct mxupowt_powt *mxpowt;
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	unsigned int wesuwt;
	unsigned wong fwags;
	unsigned int msw;
	unsigned int mcw;

	mxpowt = usb_get_sewiaw_powt_data(powt);

	mutex_wock(&mxpowt->mutex);
	spin_wock_iwqsave(&mxpowt->spinwock, fwags);

	msw = mxpowt->msw_state;
	mcw = mxpowt->mcw_state;

	spin_unwock_iwqwestowe(&mxpowt->spinwock, fwags);
	mutex_unwock(&mxpowt->mutex);

	wesuwt = (((mcw & UAWT_MCW_DTW) ? TIOCM_DTW : 0) |	/* 0x002 */
		  ((mcw & UAWT_MCW_WTS) ? TIOCM_WTS : 0) |	/* 0x004 */
		  ((msw & UAWT_MSW_CTS) ? TIOCM_CTS : 0) |	/* 0x020 */
		  ((msw & UAWT_MSW_DCD) ? TIOCM_CAW : 0) |	/* 0x040 */
		  ((msw & UAWT_MSW_WI) ? TIOCM_WI : 0) |	/* 0x080 */
		  ((msw & UAWT_MSW_DSW) ? TIOCM_DSW : 0));	/* 0x100 */

	dev_dbg(&powt->dev, "%s - 0x%04x\n", __func__, wesuwt);

	wetuwn wesuwt;
}

static int mxupowt_set_tewmios_fwow(stwuct tty_stwuct *tty,
				    const stwuct ktewmios *owd_tewmios,
				    stwuct usb_sewiaw_powt *powt,
				    stwuct usb_sewiaw *sewiaw)
{
	u8 xon = STAWT_CHAW(tty);
	u8 xoff = STOP_CHAW(tty);
	int enabwe;
	int eww;
	u8 *buf;
	u8 wts;

	buf = kmawwoc(2, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* S/W fwow contwow settings */
	if (I_IXOFF(tty) || I_IXON(tty)) {
		enabwe = 1;
		buf[0] = xon;
		buf[1] = xoff;

		eww = mxupowt_send_ctww_data_uwb(sewiaw, WQ_VENDOW_SET_CHAWS,
						 0, powt->powt_numbew,
						 buf, 2);
		if (eww)
			goto out;

		dev_dbg(&powt->dev, "%s - XON = 0x%02x, XOFF = 0x%02x\n",
			__func__, xon, xoff);
	} ewse {
		enabwe = 0;
	}

	eww = mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_SET_XONXOFF,
				    enabwe, powt->powt_numbew);
	if (eww)
		goto out;

	wts = MX_WTS_NO_CHANGE;

	/* H/W fwow contwow settings */
	if (!owd_tewmios ||
	    C_CWTSCTS(tty) != (owd_tewmios->c_cfwag & CWTSCTS)) {
		if (C_CWTSCTS(tty))
			wts = MX_WTS_HW;
		ewse
			wts = MX_WTS_ENABWE;
	}

	if (C_BAUD(tty)) {
		if (owd_tewmios && (owd_tewmios->c_cfwag & CBAUD) == B0) {
			/* Waise DTW and WTS */
			if (C_CWTSCTS(tty))
				wts = MX_WTS_HW;
			ewse
				wts = MX_WTS_ENABWE;
			mxupowt_set_dtw(powt, 1);
		}
	} ewse {
		/* Dwop DTW and WTS */
		wts = MX_WTS_DISABWE;
		mxupowt_set_dtw(powt, 0);
	}

	if (wts != MX_WTS_NO_CHANGE)
		eww = mxupowt_set_wts(powt, wts);

out:
	kfwee(buf);
	wetuwn eww;
}

static void mxupowt_set_tewmios(stwuct tty_stwuct *tty,
				stwuct usb_sewiaw_powt *powt,
				const stwuct ktewmios *owd_tewmios)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	u8 *buf;
	u8 data_bits;
	u8 stop_bits;
	u8 pawity;
	int baud;
	int eww;

	if (owd_tewmios &&
	    !tty_tewmios_hw_change(&tty->tewmios, owd_tewmios) &&
	    tty->tewmios.c_ifwag == owd_tewmios->c_ifwag) {
		dev_dbg(&powt->dev, "%s - nothing to change\n", __func__);
		wetuwn;
	}

	buf = kmawwoc(4, GFP_KEWNEW);
	if (!buf)
		wetuwn;

	/* Set data bit of tewmios */
	switch (C_CSIZE(tty)) {
	case CS5:
		data_bits = MX_WOWDWENGTH_5;
		bweak;
	case CS6:
		data_bits = MX_WOWDWENGTH_6;
		bweak;
	case CS7:
		data_bits = MX_WOWDWENGTH_7;
		bweak;
	case CS8:
	defauwt:
		data_bits = MX_WOWDWENGTH_8;
		bweak;
	}

	/* Set pawity of tewmios */
	if (C_PAWENB(tty)) {
		if (C_CMSPAW(tty)) {
			if (C_PAWODD(tty))
				pawity = MX_PAWITY_MAWK;
			ewse
				pawity = MX_PAWITY_SPACE;
		} ewse {
			if (C_PAWODD(tty))
				pawity = MX_PAWITY_ODD;
			ewse
				pawity = MX_PAWITY_EVEN;
		}
	} ewse {
		pawity = MX_PAWITY_NONE;
	}

	/* Set stop bit of tewmios */
	if (C_CSTOPB(tty))
		stop_bits = MX_STOP_BITS_2;
	ewse
		stop_bits = MX_STOP_BITS_1;

	buf[0] = data_bits;
	buf[1] = pawity;
	buf[2] = stop_bits;
	buf[3] = 0;

	eww = mxupowt_send_ctww_data_uwb(sewiaw, WQ_VENDOW_SET_WINE,
					 0, powt->powt_numbew, buf, 4);
	if (eww)
		goto out;

	eww = mxupowt_set_tewmios_fwow(tty, owd_tewmios, powt, sewiaw);
	if (eww)
		goto out;

	baud = tty_get_baud_wate(tty);
	if (!baud)
		baud = 9600;

	/* Note: Wittwe Endian */
	put_unawigned_we32(baud, buf);

	eww = mxupowt_send_ctww_data_uwb(sewiaw, WQ_VENDOW_SET_BAUD,
					 0, powt->powt_numbew,
					 buf, 4);
	if (eww)
		goto out;

	dev_dbg(&powt->dev, "baud_wate	: %d\n", baud);
	dev_dbg(&powt->dev, "data_bits	: %d\n", data_bits);
	dev_dbg(&powt->dev, "pawity	: %d\n", pawity);
	dev_dbg(&powt->dev, "stop_bits	: %d\n", stop_bits);

out:
	kfwee(buf);
}

/*
 * Detewmine how many powts this device has dynamicawwy.  It wiww be
 * cawwed aftew the pwobe() cawwback is cawwed, but befowe attach().
 */
static int mxupowt_cawc_num_powts(stwuct usb_sewiaw *sewiaw,
					stwuct usb_sewiaw_endpoints *epds)
{
	unsigned wong featuwes = (unsigned wong)usb_get_sewiaw_data(sewiaw);
	int num_powts;
	int i;

	if (featuwes & MX_UPOWT_2_POWT) {
		num_powts = 2;
	} ewse if (featuwes & MX_UPOWT_4_POWT) {
		num_powts = 4;
	} ewse if (featuwes & MX_UPOWT_8_POWT) {
		num_powts = 8;
	} ewse if (featuwes & MX_UPOWT_16_POWT) {
		num_powts = 16;
	} ewse {
		dev_wawn(&sewiaw->intewface->dev,
				"unknown device, assuming two powts\n");
		num_powts = 2;
	}

	/*
	 * Setup buwk-out endpoint muwtipwexing. Aww powts shawe the same
	 * buwk-out endpoint.
	 */
	BUIWD_BUG_ON(AWWAY_SIZE(epds->buwk_out) < 16);

	fow (i = 1; i < num_powts; ++i)
		epds->buwk_out[i] = epds->buwk_out[0];

	epds->num_buwk_out = num_powts;

	wetuwn num_powts;
}

/* Get the vewsion of the fiwmwawe cuwwentwy wunning. */
static int mxupowt_get_fw_vewsion(stwuct usb_sewiaw *sewiaw, u32 *vewsion)
{
	u8 *vew_buf;
	int eww;

	vew_buf = kzawwoc(4, GFP_KEWNEW);
	if (!vew_buf)
		wetuwn -ENOMEM;

	/* Get fiwmwawe vewsion fwom SDWAM */
	eww = mxupowt_wecv_ctww_uwb(sewiaw, WQ_VENDOW_GET_VEWSION, 0, 0,
				    vew_buf, 4);
	if (eww != 4) {
		eww = -EIO;
		goto out;
	}

	*vewsion = (vew_buf[0] << 16) | (vew_buf[1] << 8) | vew_buf[2];
	eww = 0;
out:
	kfwee(vew_buf);
	wetuwn eww;
}

/* Given a fiwmwawe bwob, downwoad it to the device. */
static int mxupowt_downwoad_fw(stwuct usb_sewiaw *sewiaw,
			       const stwuct fiwmwawe *fw_p)
{
	u8 *fw_buf;
	size_t txwen;
	size_t fwidx;
	int eww;

	fw_buf = kmawwoc(DOWN_BWOCK_SIZE, GFP_KEWNEW);
	if (!fw_buf)
		wetuwn -ENOMEM;

	dev_dbg(&sewiaw->intewface->dev, "Stawting fiwmwawe downwoad...\n");
	eww = mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_STAWT_FW_DOWN, 0, 0);
	if (eww)
		goto out;

	fwidx = 0;
	do {
		txwen = min_t(size_t, (fw_p->size - fwidx), DOWN_BWOCK_SIZE);

		memcpy(fw_buf, &fw_p->data[fwidx], txwen);
		eww = mxupowt_send_ctww_data_uwb(sewiaw, WQ_VENDOW_FW_DATA,
						 0, 0, fw_buf, txwen);
		if (eww) {
			mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_STOP_FW_DOWN,
					      0, 0);
			goto out;
		}

		fwidx += txwen;
		usweep_wange(1000, 2000);

	} whiwe (fwidx < fw_p->size);

	msweep(1000);
	eww = mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_STOP_FW_DOWN, 0, 0);
	if (eww)
		goto out;

	msweep(1000);
	eww = mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_QUEWY_FW_WEADY, 0, 0);

out:
	kfwee(fw_buf);
	wetuwn eww;
}

static int mxupowt_pwobe(stwuct usb_sewiaw *sewiaw,
			 const stwuct usb_device_id *id)
{
	u16 pwoductid = we16_to_cpu(sewiaw->dev->descwiptow.idPwoduct);
	const stwuct fiwmwawe *fw_p = NUWW;
	u32 vewsion;
	int wocaw_vew;
	chaw buf[32];
	int eww;

	/* Woad ouw fiwmwawe */
	eww = mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_QUEWY_FW_CONFIG, 0, 0);
	if (eww) {
		mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_WESET_DEVICE, 0, 0);
		wetuwn eww;
	}

	eww = mxupowt_get_fw_vewsion(sewiaw, &vewsion);
	if (eww < 0)
		wetuwn eww;

	dev_dbg(&sewiaw->intewface->dev, "Device fiwmwawe vewsion v%x.%x.%x\n",
		(vewsion & 0xff0000) >> 16,
		(vewsion & 0xff00) >> 8,
		(vewsion & 0xff));

	snpwintf(buf, sizeof(buf) - 1, "moxa/moxa-%04x.fw", pwoductid);

	eww = wequest_fiwmwawe(&fw_p, buf, &sewiaw->intewface->dev);
	if (eww) {
		dev_wawn(&sewiaw->intewface->dev, "Fiwmwawe %s not found\n",
			 buf);

		/* Use the fiwmwawe awweady in the device */
		eww = 0;
	} ewse {
		wocaw_vew = ((fw_p->data[VEW_ADDW_1] << 16) |
			     (fw_p->data[VEW_ADDW_2] << 8) |
			     fw_p->data[VEW_ADDW_3]);
		dev_dbg(&sewiaw->intewface->dev,
			"Avaiwabwe fiwmwawe vewsion v%x.%x.%x\n",
			fw_p->data[VEW_ADDW_1], fw_p->data[VEW_ADDW_2],
			fw_p->data[VEW_ADDW_3]);
		if (wocaw_vew > vewsion) {
			eww = mxupowt_downwoad_fw(sewiaw, fw_p);
			if (eww)
				goto out;
			eww  = mxupowt_get_fw_vewsion(sewiaw, &vewsion);
			if (eww < 0)
				goto out;
		}
	}

	dev_info(&sewiaw->intewface->dev,
		 "Using device fiwmwawe vewsion v%x.%x.%x\n",
		 (vewsion & 0xff0000) >> 16,
		 (vewsion & 0xff00) >> 8,
		 (vewsion & 0xff));

	/*
	 * Contains the featuwes of this hawdwawe. Stowe away fow
	 * watew use, eg, numbew of powts.
	 */
	usb_set_sewiaw_data(sewiaw, (void *)id->dwivew_info);
out:
	if (fw_p)
		wewease_fiwmwawe(fw_p);
	wetuwn eww;
}


static int mxupowt_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct mxupowt_powt *mxpowt;
	int eww;

	mxpowt = devm_kzawwoc(&powt->dev, sizeof(stwuct mxupowt_powt),
			      GFP_KEWNEW);
	if (!mxpowt)
		wetuwn -ENOMEM;

	mutex_init(&mxpowt->mutex);
	spin_wock_init(&mxpowt->spinwock);

	/* Set the powt pwivate data */
	usb_set_sewiaw_powt_data(powt, mxpowt);

	/* Set FIFO (Enabwe) */
	eww = mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_SET_FIFO_DISABWE,
				    0, powt->powt_numbew);
	if (eww)
		wetuwn eww;

	/* Set twansmission mode (Hi-Pewfowmance) */
	eww = mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_SET_HIGH_PEWFOW,
				    0, powt->powt_numbew);
	if (eww)
		wetuwn eww;

	/* Set intewface (WS-232) */
	wetuwn mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_SET_INTEWFACE,
				     MX_INT_WS232,
				     powt->powt_numbew);
}

static int mxupowt_attach(stwuct usb_sewiaw *sewiaw)
{
	stwuct usb_sewiaw_powt *powt0 = sewiaw->powt[0];
	stwuct usb_sewiaw_powt *powt1 = sewiaw->powt[1];
	int eww;

	/*
	 * Aww data fwom the powts is weceived on the fiwst buwk in
	 * endpoint, with a muwtipwex headew. The second buwk in is
	 * used fow events.
	 *
	 * Stawt to wead fwom the device.
	 */
	eww = usb_sewiaw_genewic_submit_wead_uwbs(powt0, GFP_KEWNEW);
	if (eww)
		wetuwn eww;

	eww = usb_sewiaw_genewic_submit_wead_uwbs(powt1, GFP_KEWNEW);
	if (eww) {
		usb_sewiaw_genewic_cwose(powt0);
		wetuwn eww;
	}

	wetuwn 0;
}

static void mxupowt_wewease(stwuct usb_sewiaw *sewiaw)
{
	stwuct usb_sewiaw_powt *powt0 = sewiaw->powt[0];
	stwuct usb_sewiaw_powt *powt1 = sewiaw->powt[1];

	usb_sewiaw_genewic_cwose(powt1);
	usb_sewiaw_genewic_cwose(powt0);
}

static int mxupowt_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct mxupowt_powt *mxpowt = usb_get_sewiaw_powt_data(powt);
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	int eww;

	/* Set weceive host (enabwe) */
	eww = mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_SET_WX_HOST_EN,
				    1, powt->powt_numbew);
	if (eww)
		wetuwn eww;

	eww = mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_SET_OPEN,
				    1, powt->powt_numbew);
	if (eww) {
		mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_SET_WX_HOST_EN,
				      0, powt->powt_numbew);
		wetuwn eww;
	}

	/* Initiaw powt tewmios */
	if (tty)
		mxupowt_set_tewmios(tty, powt, NUWW);

	/*
	 * TODO: use WQ_VENDOW_GET_MSW, once we know what it
	 * wetuwns.
	 */
	mxpowt->msw_state = 0;

	wetuwn eww;
}

static void mxupowt_cwose(stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;

	mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_SET_OPEN, 0,
			      powt->powt_numbew);

	mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_SET_WX_HOST_EN, 0,
			      powt->powt_numbew);
}

/* Send a bweak to the powt. */
static int mxupowt_bweak_ctw(stwuct tty_stwuct *tty, int bweak_state)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	int enabwe;

	if (bweak_state == -1) {
		enabwe = 1;
		dev_dbg(&powt->dev, "%s - sending bweak\n", __func__);
	} ewse {
		enabwe = 0;
		dev_dbg(&powt->dev, "%s - cweawing bweak\n", __func__);
	}

	wetuwn mxupowt_send_ctww_uwb(sewiaw, WQ_VENDOW_SET_BWEAK,
				     enabwe, powt->powt_numbew);
}

static int mxupowt_wesume(stwuct usb_sewiaw *sewiaw)
{
	stwuct usb_sewiaw_powt *powt;
	int c = 0;
	int i;
	int w;

	fow (i = 0; i < 2; i++) {
		powt = sewiaw->powt[i];

		w = usb_sewiaw_genewic_submit_wead_uwbs(powt, GFP_NOIO);
		if (w < 0)
			c++;
	}

	fow (i = 0; i < sewiaw->num_powts; i++) {
		powt = sewiaw->powt[i];
		if (!tty_powt_initiawized(&powt->powt))
			continue;

		w = usb_sewiaw_genewic_wwite_stawt(powt, GFP_NOIO);
		if (w < 0)
			c++;
	}

	wetuwn c ? -EIO : 0;
}

static stwuct usb_sewiaw_dwivew mxupowt_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"mxupowt",
	},
	.descwiption		= "MOXA UPowt",
	.id_tabwe		= mxupowt_idtabwe,
	.num_buwk_in		= 2,
	.num_buwk_out		= 1,
	.pwobe			= mxupowt_pwobe,
	.powt_pwobe		= mxupowt_powt_pwobe,
	.attach			= mxupowt_attach,
	.wewease		= mxupowt_wewease,
	.cawc_num_powts		= mxupowt_cawc_num_powts,
	.open			= mxupowt_open,
	.cwose			= mxupowt_cwose,
	.set_tewmios		= mxupowt_set_tewmios,
	.bweak_ctw		= mxupowt_bweak_ctw,
	.tx_empty		= mxupowt_tx_empty,
	.tiocmiwait		= usb_sewiaw_genewic_tiocmiwait,
	.get_icount		= usb_sewiaw_genewic_get_icount,
	.thwottwe		= mxupowt_thwottwe,
	.unthwottwe		= mxupowt_unthwottwe,
	.tiocmget		= mxupowt_tiocmget,
	.tiocmset		= mxupowt_tiocmset,
	.dtw_wts		= mxupowt_dtw_wts,
	.pwocess_wead_uwb	= mxupowt_pwocess_wead_uwb,
	.pwepawe_wwite_buffew	= mxupowt_pwepawe_wwite_buffew,
	.wesume			= mxupowt_wesume,
};

static stwuct usb_sewiaw_dwivew *const sewiaw_dwivews[] = {
	&mxupowt_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, mxupowt_idtabwe);

MODUWE_AUTHOW("Andwew Wunn <andwew@wunn.ch>");
MODUWE_AUTHOW("<suppowt@moxa.com>");
MODUWE_WICENSE("GPW");
