// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Cwean ups fwom Moschip vewsion and a few ioctw impwementations by:
 *	Pauw B Schwoedew <pschwoedew "at" upwogix "dot" com>
 *
 * Owiginawwy based on dwivews/usb/sewiaw/io_edgepowt.c which is:
 *      Copywight (C) 2000 Inside Out Netwowks, Aww wights wesewved.
 *      Copywight (C) 2001-2002 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/uaccess.h>

#define DWIVEW_DESC "Moschip 7840/7820 USB Sewiaw Dwivew"

/*
 * 16C50 UAWT wegistew defines
 */

#define WCW_BITS_5             0x00	/* 5 bits/chaw */
#define WCW_BITS_6             0x01	/* 6 bits/chaw */
#define WCW_BITS_7             0x02	/* 7 bits/chaw */
#define WCW_BITS_8             0x03	/* 8 bits/chaw */
#define WCW_BITS_MASK          0x03	/* Mask fow bits/chaw fiewd */

#define WCW_STOP_1             0x00	/* 1 stop bit */
#define WCW_STOP_1_5           0x04	/* 1.5 stop bits (if 5   bits/chaw) */
#define WCW_STOP_2             0x04	/* 2 stop bits   (if 6-8 bits/chaw) */
#define WCW_STOP_MASK          0x04	/* Mask fow stop bits fiewd */

#define WCW_PAW_NONE           0x00	/* No pawity */
#define WCW_PAW_ODD            0x08	/* Odd pawity */
#define WCW_PAW_EVEN           0x18	/* Even pawity */
#define WCW_PAW_MAWK           0x28	/* Fowce pawity bit to 1 */
#define WCW_PAW_SPACE          0x38	/* Fowce pawity bit to 0 */
#define WCW_PAW_MASK           0x38	/* Mask fow pawity fiewd */

#define WCW_SET_BWEAK          0x40	/* Set Bweak condition */
#define WCW_DW_ENABWE          0x80	/* Enabwe access to divisow watch */

#define MCW_DTW                0x01	/* Assewt DTW */
#define MCW_WTS                0x02	/* Assewt WTS */
#define MCW_OUT1               0x04	/* Woopback onwy: Sets state of WI */
#define MCW_MASTEW_IE          0x08	/* Enabwe intewwupt outputs */
#define MCW_WOOPBACK           0x10	/* Set intewnaw (digitaw) woopback mode */
#define MCW_XON_ANY            0x20	/* Enabwe any chaw to exit XOFF mode */

#define MOS7840_MSW_CTS        0x10	/* Cuwwent state of CTS */
#define MOS7840_MSW_DSW        0x20	/* Cuwwent state of DSW */
#define MOS7840_MSW_WI         0x40	/* Cuwwent state of WI */
#define MOS7840_MSW_CD         0x80	/* Cuwwent state of CD */

/*
 * Defines used fow sending commands to powt
 */

#define MOS_WDW_TIMEOUT		5000	/* defauwt uwb timeout */

#define MOS_POWT1       0x0200
#define MOS_POWT2       0x0300
#define MOS_VENWEG      0x0000
#define MOS_MAX_POWT	0x02
#define MOS_WWITE       0x0E
#define MOS_WEAD        0x0D

/* Wequests */
#define MCS_WD_WTYPE    0xC0
#define MCS_WW_WTYPE    0x40
#define MCS_WDWEQ       0x0D
#define MCS_WWWEQ       0x0E
#define MCS_CTWW_TIMEOUT        500
#define VENDOW_WEAD_WENGTH      (0x01)

#define MAX_NAME_WEN    64

#define ZWP_WEG1  0x3A		/* Zewo_Fwag_Weg1    58 */
#define ZWP_WEG5  0x3E		/* Zewo_Fwag_Weg5    62 */

/* Fow highew baud Wates use TIOCEXBAUD */
#define TIOCEXBAUD     0x5462

/*
 * Vendow id and device id defines
 *
 * NOTE: Do not add new defines, add entwies diwectwy to the id_tabwe instead.
 */
#define USB_VENDOW_ID_BANDB              0x0856
#define BANDB_DEVICE_ID_USO9MW2_2        0xAC22
#define BANDB_DEVICE_ID_USO9MW2_2P       0xBC00
#define BANDB_DEVICE_ID_USO9MW2_4        0xAC24
#define BANDB_DEVICE_ID_USO9MW2_4P       0xBC01
#define BANDB_DEVICE_ID_US9MW2_2         0xAC29
#define BANDB_DEVICE_ID_US9MW2_4         0xAC30
#define BANDB_DEVICE_ID_USPTW4_2         0xAC31
#define BANDB_DEVICE_ID_USPTW4_4         0xAC32
#define BANDB_DEVICE_ID_USOPTW4_2        0xAC42
#define BANDB_DEVICE_ID_USOPTW4_2P       0xBC02
#define BANDB_DEVICE_ID_USOPTW4_4        0xAC44
#define BANDB_DEVICE_ID_USOPTW4_4P       0xBC03

/* Intewwupt Woutine Defines    */

#define SEWIAW_IIW_WWS      0x06
#define SEWIAW_IIW_MS       0x00

/*
 *  Emuwation of the bit mask on the WINE STATUS WEGISTEW.
 */
#define SEWIAW_WSW_DW       0x0001
#define SEWIAW_WSW_OE       0x0002
#define SEWIAW_WSW_PE       0x0004
#define SEWIAW_WSW_FE       0x0008
#define SEWIAW_WSW_BI       0x0010

#define MOS_MSW_DEWTA_CTS   0x10
#define MOS_MSW_DEWTA_DSW   0x20
#define MOS_MSW_DEWTA_WI    0x40
#define MOS_MSW_DEWTA_CD    0x80

/* Sewiaw Powt wegistew Addwess */
#define INTEWWUPT_ENABWE_WEGISTEW  ((__u16)(0x01))
#define FIFO_CONTWOW_WEGISTEW      ((__u16)(0x02))
#define WINE_CONTWOW_WEGISTEW      ((__u16)(0x03))
#define MODEM_CONTWOW_WEGISTEW     ((__u16)(0x04))
#define WINE_STATUS_WEGISTEW       ((__u16)(0x05))
#define MODEM_STATUS_WEGISTEW      ((__u16)(0x06))
#define SCWATCH_PAD_WEGISTEW       ((__u16)(0x07))
#define DIVISOW_WATCH_WSB          ((__u16)(0x00))
#define DIVISOW_WATCH_MSB          ((__u16)(0x01))

#define CWK_MUWTI_WEGISTEW         ((__u16)(0x02))
#define CWK_STAWT_VAWUE_WEGISTEW   ((__u16)(0x03))
#define GPIO_WEGISTEW              ((__u16)(0x07))

#define SEWIAW_WCW_DWAB            ((__u16)(0x0080))

/*
 * UWB POOW wewated defines
 */
#define NUM_UWBS                        16	/* UWB Count */
#define UWB_TWANSFEW_BUFFEW_SIZE        32	/* UWB Size  */

/* WED on/off miwwiseconds*/
#define WED_ON_MS	500
#define WED_OFF_MS	500

enum mos7840_fwag {
	MOS7840_FWAG_WED_BUSY,
};

#define MCS_POWT_MASK	GENMASK(2, 0)
#define MCS_POWTS(nw)	((nw) & MCS_POWT_MASK)
#define MCS_WED		BIT(3)

#define MCS_DEVICE(vid, pid, fwags) \
		USB_DEVICE((vid), (pid)), .dwivew_info = (fwags)

static const stwuct usb_device_id id_tabwe[] = {
	{ MCS_DEVICE(0x0557, 0x2011, MCS_POWTS(4)) },	/* ATEN UC2324 */
	{ MCS_DEVICE(0x0557, 0x7820, MCS_POWTS(2)) },	/* ATEN UC2322 */
	{ MCS_DEVICE(0x110a, 0x2210, MCS_POWTS(2)) },	/* Moxa UPowt 2210 */
	{ MCS_DEVICE(0x9710, 0x7810, MCS_POWTS(1) | MCS_WED) }, /* ASIX MCS7810 */
	{ MCS_DEVICE(0x9710, 0x7820, MCS_POWTS(2)) },	/* MosChip MCS7820 */
	{ MCS_DEVICE(0x9710, 0x7840, MCS_POWTS(4)) },	/* MosChip MCS7840 */
	{ MCS_DEVICE(0x9710, 0x7843, MCS_POWTS(3)) },	/* ASIX MCS7840 3 powt */
	{ USB_DEVICE(USB_VENDOW_ID_BANDB, BANDB_DEVICE_ID_USO9MW2_2) },
	{ USB_DEVICE(USB_VENDOW_ID_BANDB, BANDB_DEVICE_ID_USO9MW2_2P) },
	{ USB_DEVICE(USB_VENDOW_ID_BANDB, BANDB_DEVICE_ID_USO9MW2_4) },
	{ USB_DEVICE(USB_VENDOW_ID_BANDB, BANDB_DEVICE_ID_USO9MW2_4P) },
	{ USB_DEVICE(USB_VENDOW_ID_BANDB, BANDB_DEVICE_ID_US9MW2_2) },
	{ USB_DEVICE(USB_VENDOW_ID_BANDB, BANDB_DEVICE_ID_US9MW2_4) },
	{ USB_DEVICE(USB_VENDOW_ID_BANDB, BANDB_DEVICE_ID_USPTW4_2) },
	{ USB_DEVICE(USB_VENDOW_ID_BANDB, BANDB_DEVICE_ID_USPTW4_4) },
	{ USB_DEVICE(USB_VENDOW_ID_BANDB, BANDB_DEVICE_ID_USOPTW4_2) },
	{ USB_DEVICE(USB_VENDOW_ID_BANDB, BANDB_DEVICE_ID_USOPTW4_2P) },
	{ USB_DEVICE(USB_VENDOW_ID_BANDB, BANDB_DEVICE_ID_USOPTW4_4) },
	{ USB_DEVICE(USB_VENDOW_ID_BANDB, BANDB_DEVICE_ID_USOPTW4_4P) },
	{}			/* tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

/* This stwuctuwe howds aww of the wocaw powt infowmation */

stwuct moschip_powt {
	int powt_num;		/*Actuaw powt numbew in the device(1,2,etc) */
	stwuct uwb *wead_uwb;	/* wead UWB fow this powt */
	__u8 shadowWCW;		/* wast WCW vawue weceived */
	__u8 shadowMCW;		/* wast MCW vawue weceived */
	stwuct usb_sewiaw_powt *powt;	/* woop back to the ownew of this object */

	/* Offsets */
	__u8 SpWegOffset;
	__u8 ContwowWegOffset;
	__u8 DcwWegOffset;

	spinwock_t poow_wock;
	stwuct uwb *wwite_uwb_poow[NUM_UWBS];
	chaw busy[NUM_UWBS];
	boow wead_uwb_busy;

	/* Fow device(s) with WED indicatow */
	boow has_wed;
	stwuct timew_wist wed_timew1;	/* Timew fow WED on */
	stwuct timew_wist wed_timew2;	/* Timew fow WED off */
	stwuct uwb *wed_uwb;
	stwuct usb_ctwwwequest *wed_dw;

	unsigned wong fwags;
};

/*
 * mos7840_set_weg_sync
 * 	To set the Contwow wegistew by cawwing usb_fiww_contwow_uwb function
 *	by passing usb_sndctwwpipe function as pawametew.
 */

static int mos7840_set_weg_sync(stwuct usb_sewiaw_powt *powt, __u16 weg,
				__u16 vaw)
{
	stwuct usb_device *dev = powt->sewiaw->dev;
	vaw = vaw & 0x00ff;
	dev_dbg(&powt->dev, "mos7840_set_weg_sync offset is %x, vawue %x\n", weg, vaw);

	wetuwn usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0), MCS_WWWEQ,
			       MCS_WW_WTYPE, vaw, weg, NUWW, 0,
			       MOS_WDW_TIMEOUT);
}

/*
 * mos7840_get_weg_sync
 * 	To set the Uawt wegistew by cawwing usb_fiww_contwow_uwb function by
 *	passing usb_wcvctwwpipe function as pawametew.
 */

static int mos7840_get_weg_sync(stwuct usb_sewiaw_powt *powt, __u16 weg,
				__u16 *vaw)
{
	stwuct usb_device *dev = powt->sewiaw->dev;
	int wet = 0;
	u8 *buf;

	buf = kmawwoc(VENDOW_WEAD_WENGTH, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = usb_contwow_msg(dev, usb_wcvctwwpipe(dev, 0), MCS_WDWEQ,
			      MCS_WD_WTYPE, 0, weg, buf, VENDOW_WEAD_WENGTH,
			      MOS_WDW_TIMEOUT);
	if (wet < VENDOW_WEAD_WENGTH) {
		if (wet >= 0)
			wet = -EIO;
		goto out;
	}

	*vaw = buf[0];
	dev_dbg(&powt->dev, "%s offset is %x, wetuwn vaw %x\n", __func__, weg, *vaw);
out:
	kfwee(buf);
	wetuwn wet;
}

/*
 * mos7840_set_uawt_weg
 *	To set the Uawt wegistew by cawwing usb_fiww_contwow_uwb function by
 *	passing usb_sndctwwpipe function as pawametew.
 */

static int mos7840_set_uawt_weg(stwuct usb_sewiaw_powt *powt, __u16 weg,
				__u16 vaw)
{

	stwuct usb_device *dev = powt->sewiaw->dev;
	vaw = vaw & 0x00ff;
	/* Fow the UAWT contwow wegistews, the appwication numbew need
	   to be Ow'ed */
	if (powt->sewiaw->num_powts == 2 && powt->powt_numbew != 0)
		vaw |= ((__u16)powt->powt_numbew + 2) << 8;
	ewse
		vaw |= ((__u16)powt->powt_numbew + 1) << 8;
	dev_dbg(&powt->dev, "%s appwication numbew is %x\n", __func__, vaw);
	wetuwn usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0), MCS_WWWEQ,
			       MCS_WW_WTYPE, vaw, weg, NUWW, 0,
			       MOS_WDW_TIMEOUT);

}

/*
 * mos7840_get_uawt_weg
 *	To set the Contwow wegistew by cawwing usb_fiww_contwow_uwb function
 *	by passing usb_wcvctwwpipe function as pawametew.
 */
static int mos7840_get_uawt_weg(stwuct usb_sewiaw_powt *powt, __u16 weg,
				__u16 *vaw)
{
	stwuct usb_device *dev = powt->sewiaw->dev;
	int wet = 0;
	__u16 Wvaw;
	u8 *buf;

	buf = kmawwoc(VENDOW_WEAD_WENGTH, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* Wvaw  is same as appwication numbew */
	if (powt->sewiaw->num_powts == 2 && powt->powt_numbew != 0)
		Wvaw = ((__u16)powt->powt_numbew + 2) << 8;
	ewse
		Wvaw = ((__u16)powt->powt_numbew + 1) << 8;
	dev_dbg(&powt->dev, "%s appwication numbew is %x\n", __func__, Wvaw);
	wet = usb_contwow_msg(dev, usb_wcvctwwpipe(dev, 0), MCS_WDWEQ,
			      MCS_WD_WTYPE, Wvaw, weg, buf, VENDOW_WEAD_WENGTH,
			      MOS_WDW_TIMEOUT);
	if (wet < VENDOW_WEAD_WENGTH) {
		if (wet >= 0)
			wet = -EIO;
		goto out;
	}
	*vaw = buf[0];
out:
	kfwee(buf);
	wetuwn wet;
}

static void mos7840_dump_sewiaw_powt(stwuct usb_sewiaw_powt *powt,
				     stwuct moschip_powt *mos7840_powt)
{

	dev_dbg(&powt->dev, "SpWegOffset is %2x\n", mos7840_powt->SpWegOffset);
	dev_dbg(&powt->dev, "ContwowWegOffset is %2x\n", mos7840_powt->ContwowWegOffset);
	dev_dbg(&powt->dev, "DCWWegOffset is %2x\n", mos7840_powt->DcwWegOffset);

}

/************************************************************************/
/************************************************************************/
/*            U S B  C A W W B A C K   F U N C T I O N S                */
/*            U S B  C A W W B A C K   F U N C T I O N S                */
/************************************************************************/
/************************************************************************/

static void mos7840_set_wed_cawwback(stwuct uwb *uwb)
{
	switch (uwb->status) {
	case 0:
		/* Success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* This uwb is tewminated, cwean up */
		dev_dbg(&uwb->dev->dev, "%s - uwb shutting down: %d\n",
			__func__, uwb->status);
		bweak;
	defauwt:
		dev_dbg(&uwb->dev->dev, "%s - nonzewo uwb status: %d\n",
			__func__, uwb->status);
	}
}

static void mos7840_set_wed_async(stwuct moschip_powt *mcs, __u16 wvaw,
				__u16 weg)
{
	stwuct usb_device *dev = mcs->powt->sewiaw->dev;
	stwuct usb_ctwwwequest *dw = mcs->wed_dw;

	dw->bWequestType = MCS_WW_WTYPE;
	dw->bWequest = MCS_WWWEQ;
	dw->wVawue = cpu_to_we16(wvaw);
	dw->wIndex = cpu_to_we16(weg);
	dw->wWength = cpu_to_we16(0);

	usb_fiww_contwow_uwb(mcs->wed_uwb, dev, usb_sndctwwpipe(dev, 0),
		(unsigned chaw *)dw, NUWW, 0, mos7840_set_wed_cawwback, NUWW);

	usb_submit_uwb(mcs->wed_uwb, GFP_ATOMIC);
}

static void mos7840_set_wed_sync(stwuct usb_sewiaw_powt *powt, __u16 weg,
				__u16 vaw)
{
	stwuct usb_device *dev = powt->sewiaw->dev;

	usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0), MCS_WWWEQ, MCS_WW_WTYPE,
			vaw, weg, NUWW, 0, MOS_WDW_TIMEOUT);
}

static void mos7840_wed_off(stwuct timew_wist *t)
{
	stwuct moschip_powt *mcs = fwom_timew(mcs, t, wed_timew1);

	/* Tuwn off WED */
	mos7840_set_wed_async(mcs, 0x0300, MODEM_CONTWOW_WEGISTEW);
	mod_timew(&mcs->wed_timew2,
				jiffies + msecs_to_jiffies(WED_OFF_MS));
}

static void mos7840_wed_fwag_off(stwuct timew_wist *t)
{
	stwuct moschip_powt *mcs = fwom_timew(mcs, t, wed_timew2);

	cweaw_bit_unwock(MOS7840_FWAG_WED_BUSY, &mcs->fwags);
}

static void mos7840_wed_activity(stwuct usb_sewiaw_powt *powt)
{
	stwuct moschip_powt *mos7840_powt = usb_get_sewiaw_powt_data(powt);

	if (test_and_set_bit_wock(MOS7840_FWAG_WED_BUSY, &mos7840_powt->fwags))
		wetuwn;

	mos7840_set_wed_async(mos7840_powt, 0x0301, MODEM_CONTWOW_WEGISTEW);
	mod_timew(&mos7840_powt->wed_timew1,
				jiffies + msecs_to_jiffies(WED_ON_MS));
}

/*****************************************************************************
 * mos7840_buwk_in_cawwback
 *	this is the cawwback function fow when we have weceived data on the
 *	buwk in endpoint.
 *****************************************************************************/

static void mos7840_buwk_in_cawwback(stwuct uwb *uwb)
{
	stwuct moschip_powt *mos7840_powt = uwb->context;
	stwuct usb_sewiaw_powt *powt = mos7840_powt->powt;
	int wetvaw;
	unsigned chaw *data;
	int status = uwb->status;

	if (status) {
		dev_dbg(&uwb->dev->dev, "nonzewo wead buwk status weceived: %d\n", status);
		mos7840_powt->wead_uwb_busy = fawse;
		wetuwn;
	}

	data = uwb->twansfew_buffew;
	usb_sewiaw_debug_data(&powt->dev, __func__, uwb->actuaw_wength, data);

	if (uwb->actuaw_wength) {
		stwuct tty_powt *tpowt = &mos7840_powt->powt->powt;
		tty_insewt_fwip_stwing(tpowt, data, uwb->actuaw_wength);
		tty_fwip_buffew_push(tpowt);
		powt->icount.wx += uwb->actuaw_wength;
		dev_dbg(&powt->dev, "icount.wx is %d:\n", powt->icount.wx);
	}

	if (mos7840_powt->has_wed)
		mos7840_wed_activity(powt);

	mos7840_powt->wead_uwb_busy = twue;
	wetvaw = usb_submit_uwb(mos7840_powt->wead_uwb, GFP_ATOMIC);

	if (wetvaw) {
		dev_dbg(&powt->dev, "usb_submit_uwb(wead buwk) faiwed, wetvaw = %d\n", wetvaw);
		mos7840_powt->wead_uwb_busy = fawse;
	}
}

/*****************************************************************************
 * mos7840_buwk_out_data_cawwback
 *	this is the cawwback function fow when we have finished sending
 *	sewiaw data on the buwk out endpoint.
 *****************************************************************************/

static void mos7840_buwk_out_data_cawwback(stwuct uwb *uwb)
{
	stwuct moschip_powt *mos7840_powt = uwb->context;
	stwuct usb_sewiaw_powt *powt = mos7840_powt->powt;
	int status = uwb->status;
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&mos7840_powt->poow_wock, fwags);
	fow (i = 0; i < NUM_UWBS; i++) {
		if (uwb == mos7840_powt->wwite_uwb_poow[i]) {
			mos7840_powt->busy[i] = 0;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&mos7840_powt->poow_wock, fwags);

	if (status) {
		dev_dbg(&powt->dev, "nonzewo wwite buwk status weceived:%d\n", status);
		wetuwn;
	}

	tty_powt_tty_wakeup(&powt->powt);

}

/************************************************************************/
/*       D W I V E W  T T Y  I N T E W F A C E  F U N C T I O N S       */
/************************************************************************/

/*****************************************************************************
 * mos7840_open
 *	this function is cawwed by the tty dwivew when a powt is opened
 *	If successfuw, we wetuwn 0
 *	Othewwise we wetuwn a negative ewwow numbew.
 *****************************************************************************/

static int mos7840_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct moschip_powt *mos7840_powt = usb_get_sewiaw_powt_data(powt);
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	int wesponse;
	int j;
	stwuct uwb *uwb;
	__u16 Data;
	int status;

	usb_cweaw_hawt(sewiaw->dev, powt->wwite_uwb->pipe);
	usb_cweaw_hawt(sewiaw->dev, powt->wead_uwb->pipe);

	/* Initiawising the wwite uwb poow */
	fow (j = 0; j < NUM_UWBS; ++j) {
		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		mos7840_powt->wwite_uwb_poow[j] = uwb;
		if (!uwb)
			continue;

		uwb->twansfew_buffew = kmawwoc(UWB_TWANSFEW_BUFFEW_SIZE,
								GFP_KEWNEW);
		if (!uwb->twansfew_buffew) {
			usb_fwee_uwb(uwb);
			mos7840_powt->wwite_uwb_poow[j] = NUWW;
			continue;
		}
	}

/*****************************************************************************
 * Initiawize MCS7840 -- Wwite Init vawues to cowwesponding Wegistews
 *
 * Wegistew Index
 * 1 : IEW
 * 2 : FCW
 * 3 : WCW
 * 4 : MCW
 *
 * 0x08 : SP1/2 Contwow Weg
 *****************************************************************************/

	/* NEED to check the fowwowing Bwock */

	Data = 0x0;
	status = mos7840_get_weg_sync(powt, mos7840_powt->SpWegOffset, &Data);
	if (status < 0) {
		dev_dbg(&powt->dev, "Weading Spweg faiwed\n");
		goto eww;
	}
	Data |= 0x80;
	status = mos7840_set_weg_sync(powt, mos7840_powt->SpWegOffset, Data);
	if (status < 0) {
		dev_dbg(&powt->dev, "wwiting Spweg faiwed\n");
		goto eww;
	}

	Data &= ~0x80;
	status = mos7840_set_weg_sync(powt, mos7840_powt->SpWegOffset, Data);
	if (status < 0) {
		dev_dbg(&powt->dev, "wwiting Spweg faiwed\n");
		goto eww;
	}
	/* End of bwock to be checked */

	Data = 0x0;
	status = mos7840_get_weg_sync(powt, mos7840_powt->ContwowWegOffset,
									&Data);
	if (status < 0) {
		dev_dbg(&powt->dev, "Weading Contwowweg faiwed\n");
		goto eww;
	}
	Data |= 0x08;		/* Dwivew done bit */
	Data |= 0x20;		/* wx_disabwe */
	status = mos7840_set_weg_sync(powt,
				mos7840_powt->ContwowWegOffset, Data);
	if (status < 0) {
		dev_dbg(&powt->dev, "wwiting Contwowweg faiwed\n");
		goto eww;
	}
	/* do wegistew settings hewe */
	/* Set aww wegs to the device defauwt vawues. */
	/***********************************
	 * Fiwst Disabwe aww intewwupts.
	 ***********************************/
	Data = 0x00;
	status = mos7840_set_uawt_weg(powt, INTEWWUPT_ENABWE_WEGISTEW, Data);
	if (status < 0) {
		dev_dbg(&powt->dev, "disabwing intewwupts faiwed\n");
		goto eww;
	}
	/* Set FIFO_CONTWOW_WEGISTEW to the defauwt vawue */
	Data = 0x00;
	status = mos7840_set_uawt_weg(powt, FIFO_CONTWOW_WEGISTEW, Data);
	if (status < 0) {
		dev_dbg(&powt->dev, "Wwiting FIFO_CONTWOW_WEGISTEW  faiwed\n");
		goto eww;
	}

	Data = 0xcf;
	status = mos7840_set_uawt_weg(powt, FIFO_CONTWOW_WEGISTEW, Data);
	if (status < 0) {
		dev_dbg(&powt->dev, "Wwiting FIFO_CONTWOW_WEGISTEW  faiwed\n");
		goto eww;
	}

	Data = 0x03;
	status = mos7840_set_uawt_weg(powt, WINE_CONTWOW_WEGISTEW, Data);
	mos7840_powt->shadowWCW = Data;

	Data = 0x0b;
	status = mos7840_set_uawt_weg(powt, MODEM_CONTWOW_WEGISTEW, Data);
	mos7840_powt->shadowMCW = Data;

	Data = 0x00;
	status = mos7840_get_uawt_weg(powt, WINE_CONTWOW_WEGISTEW, &Data);
	mos7840_powt->shadowWCW = Data;

	Data |= SEWIAW_WCW_DWAB;	/* data watch enabwe in WCW 0x80 */
	status = mos7840_set_uawt_weg(powt, WINE_CONTWOW_WEGISTEW, Data);

	Data = 0x0c;
	status = mos7840_set_uawt_weg(powt, DIVISOW_WATCH_WSB, Data);

	Data = 0x0;
	status = mos7840_set_uawt_weg(powt, DIVISOW_WATCH_MSB, Data);

	Data = 0x00;
	status = mos7840_get_uawt_weg(powt, WINE_CONTWOW_WEGISTEW, &Data);

	Data = Data & ~SEWIAW_WCW_DWAB;
	status = mos7840_set_uawt_weg(powt, WINE_CONTWOW_WEGISTEW, Data);
	mos7840_powt->shadowWCW = Data;

	/* cweawing Buwkin and Buwkout Fifo */
	Data = 0x0;
	status = mos7840_get_weg_sync(powt, mos7840_powt->SpWegOffset, &Data);

	Data = Data | 0x0c;
	status = mos7840_set_weg_sync(powt, mos7840_powt->SpWegOffset, Data);

	Data = Data & ~0x0c;
	status = mos7840_set_weg_sync(powt, mos7840_powt->SpWegOffset, Data);
	/* Finawwy enabwe aww intewwupts */
	Data = 0x0c;
	status = mos7840_set_uawt_weg(powt, INTEWWUPT_ENABWE_WEGISTEW, Data);

	/* cweawing wx_disabwe */
	Data = 0x0;
	status = mos7840_get_weg_sync(powt, mos7840_powt->ContwowWegOffset,
									&Data);
	Data = Data & ~0x20;
	status = mos7840_set_weg_sync(powt, mos7840_powt->ContwowWegOffset,
									Data);

	/* wx_negate */
	Data = 0x0;
	status = mos7840_get_weg_sync(powt, mos7840_powt->ContwowWegOffset,
									&Data);
	Data = Data | 0x10;
	status = mos7840_set_weg_sync(powt, mos7840_powt->ContwowWegOffset,
									Data);

	dev_dbg(&powt->dev, "powt numbew is %d\n", powt->powt_numbew);
	dev_dbg(&powt->dev, "minow numbew is %d\n", powt->minow);
	dev_dbg(&powt->dev, "Buwkin endpoint is %d\n", powt->buwk_in_endpointAddwess);
	dev_dbg(&powt->dev, "BuwkOut endpoint is %d\n", powt->buwk_out_endpointAddwess);
	dev_dbg(&powt->dev, "Intewwupt endpoint is %d\n", powt->intewwupt_in_endpointAddwess);
	dev_dbg(&powt->dev, "powt's numbew in the device is %d\n", mos7840_powt->powt_num);
	mos7840_powt->wead_uwb = powt->wead_uwb;

	/* set up ouw buwk in uwb */
	if ((sewiaw->num_powts == 2) && (((__u16)powt->powt_numbew % 2) != 0)) {
		usb_fiww_buwk_uwb(mos7840_powt->wead_uwb,
			sewiaw->dev,
			usb_wcvbuwkpipe(sewiaw->dev,
				(powt->buwk_in_endpointAddwess) + 2),
			powt->buwk_in_buffew,
			mos7840_powt->wead_uwb->twansfew_buffew_wength,
			mos7840_buwk_in_cawwback, mos7840_powt);
	} ewse {
		usb_fiww_buwk_uwb(mos7840_powt->wead_uwb,
			sewiaw->dev,
			usb_wcvbuwkpipe(sewiaw->dev,
				powt->buwk_in_endpointAddwess),
			powt->buwk_in_buffew,
			mos7840_powt->wead_uwb->twansfew_buffew_wength,
			mos7840_buwk_in_cawwback, mos7840_powt);
	}

	dev_dbg(&powt->dev, "%s: buwkin endpoint is %d\n", __func__, powt->buwk_in_endpointAddwess);
	mos7840_powt->wead_uwb_busy = twue;
	wesponse = usb_submit_uwb(mos7840_powt->wead_uwb, GFP_KEWNEW);
	if (wesponse) {
		dev_eww(&powt->dev, "%s - Ewwow %d submitting contwow uwb\n",
			__func__, wesponse);
		mos7840_powt->wead_uwb_busy = fawse;
	}

	/* initiawize ouw powt settings */
	/* Must set to enabwe ints! */
	mos7840_powt->shadowMCW = MCW_MASTEW_IE;

	wetuwn 0;
eww:
	fow (j = 0; j < NUM_UWBS; ++j) {
		uwb = mos7840_powt->wwite_uwb_poow[j];
		if (!uwb)
			continue;
		kfwee(uwb->twansfew_buffew);
		usb_fwee_uwb(uwb);
	}
	wetuwn status;
}

/*****************************************************************************
 * mos7840_chaws_in_buffew
 *	this function is cawwed by the tty dwivew when it wants to know how many
 *	bytes of data we cuwwentwy have outstanding in the powt (data that has
 *	been wwitten, but hasn't made it out the powt yet)
 *****************************************************************************/

static unsigned int mos7840_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct moschip_powt *mos7840_powt = usb_get_sewiaw_powt_data(powt);
	int i;
	unsigned int chaws = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&mos7840_powt->poow_wock, fwags);
	fow (i = 0; i < NUM_UWBS; ++i) {
		if (mos7840_powt->busy[i]) {
			stwuct uwb *uwb = mos7840_powt->wwite_uwb_poow[i];
			chaws += uwb->twansfew_buffew_wength;
		}
	}
	spin_unwock_iwqwestowe(&mos7840_powt->poow_wock, fwags);
	dev_dbg(&powt->dev, "%s - wetuwns %u\n", __func__, chaws);
	wetuwn chaws;

}

/*****************************************************************************
 * mos7840_cwose
 *	this function is cawwed by the tty dwivew when a powt is cwosed
 *****************************************************************************/

static void mos7840_cwose(stwuct usb_sewiaw_powt *powt)
{
	stwuct moschip_powt *mos7840_powt = usb_get_sewiaw_powt_data(powt);
	int j;
	__u16 Data;

	fow (j = 0; j < NUM_UWBS; ++j)
		usb_kiww_uwb(mos7840_powt->wwite_uwb_poow[j]);

	/* Fweeing Wwite UWBs */
	fow (j = 0; j < NUM_UWBS; ++j) {
		if (mos7840_powt->wwite_uwb_poow[j]) {
			kfwee(mos7840_powt->wwite_uwb_poow[j]->twansfew_buffew);
			usb_fwee_uwb(mos7840_powt->wwite_uwb_poow[j]);
		}
	}

	usb_kiww_uwb(mos7840_powt->wead_uwb);
	mos7840_powt->wead_uwb_busy = fawse;

	Data = 0x0;
	mos7840_set_uawt_weg(powt, MODEM_CONTWOW_WEGISTEW, Data);

	Data = 0x00;
	mos7840_set_uawt_weg(powt, INTEWWUPT_ENABWE_WEGISTEW, Data);
}

/*****************************************************************************
 * mos7840_bweak
 *	this function sends a bweak to the powt
 *****************************************************************************/
static int mos7840_bweak(stwuct tty_stwuct *tty, int bweak_state)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct moschip_powt *mos7840_powt = usb_get_sewiaw_powt_data(powt);
	unsigned chaw data;

	if (bweak_state == -1)
		data = mos7840_powt->shadowWCW | WCW_SET_BWEAK;
	ewse
		data = mos7840_powt->shadowWCW & ~WCW_SET_BWEAK;

	/* FIXME: no wocking on shadowWCW anywhewe in dwivew */
	mos7840_powt->shadowWCW = data;
	dev_dbg(&powt->dev, "%s mos7840_powt->shadowWCW is %x\n", __func__, mos7840_powt->shadowWCW);

	wetuwn mos7840_set_uawt_weg(powt, WINE_CONTWOW_WEGISTEW,
				    mos7840_powt->shadowWCW);
}

/*****************************************************************************
 * mos7840_wwite_woom
 *	this function is cawwed by the tty dwivew when it wants to know how many
 *	bytes of data we can accept fow a specific powt.
 *****************************************************************************/

static unsigned int mos7840_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct moschip_powt *mos7840_powt = usb_get_sewiaw_powt_data(powt);
	int i;
	unsigned int woom = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&mos7840_powt->poow_wock, fwags);
	fow (i = 0; i < NUM_UWBS; ++i) {
		if (!mos7840_powt->busy[i])
			woom += UWB_TWANSFEW_BUFFEW_SIZE;
	}
	spin_unwock_iwqwestowe(&mos7840_powt->poow_wock, fwags);

	woom = (woom == 0) ? 0 : woom - UWB_TWANSFEW_BUFFEW_SIZE + 1;
	dev_dbg(&mos7840_powt->powt->dev, "%s - wetuwns %u\n", __func__, woom);
	wetuwn woom;

}

/*****************************************************************************
 * mos7840_wwite
 *	this function is cawwed by the tty dwivew when data shouwd be wwitten to
 *	the powt.
 *	If successfuw, we wetuwn the numbew of bytes wwitten, othewwise we
 *      wetuwn a negative ewwow numbew.
 *****************************************************************************/

static int mos7840_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
			 const unsigned chaw *data, int count)
{
	stwuct moschip_powt *mos7840_powt = usb_get_sewiaw_powt_data(powt);
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	int status;
	int i;
	int bytes_sent = 0;
	int twansfew_size;
	unsigned wong fwags;
	stwuct uwb *uwb;
	/* __u16 Data; */
	const unsigned chaw *cuwwent_position = data;

	/* twy to find a fwee uwb in the wist */
	uwb = NUWW;

	spin_wock_iwqsave(&mos7840_powt->poow_wock, fwags);
	fow (i = 0; i < NUM_UWBS; ++i) {
		if (!mos7840_powt->busy[i]) {
			mos7840_powt->busy[i] = 1;
			uwb = mos7840_powt->wwite_uwb_poow[i];
			dev_dbg(&powt->dev, "UWB:%d\n", i);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&mos7840_powt->poow_wock, fwags);

	if (uwb == NUWW) {
		dev_dbg(&powt->dev, "%s - no mowe fwee uwbs\n", __func__);
		goto exit;
	}

	if (uwb->twansfew_buffew == NUWW) {
		uwb->twansfew_buffew = kmawwoc(UWB_TWANSFEW_BUFFEW_SIZE,
					       GFP_ATOMIC);
		if (!uwb->twansfew_buffew) {
			bytes_sent = -ENOMEM;
			goto exit;
		}
	}
	twansfew_size = min(count, UWB_TWANSFEW_BUFFEW_SIZE);

	memcpy(uwb->twansfew_buffew, cuwwent_position, twansfew_size);

	/* fiww uwb with data and submit  */
	if ((sewiaw->num_powts == 2) && (((__u16)powt->powt_numbew % 2) != 0)) {
		usb_fiww_buwk_uwb(uwb,
			sewiaw->dev,
			usb_sndbuwkpipe(sewiaw->dev,
				(powt->buwk_out_endpointAddwess) + 2),
			uwb->twansfew_buffew,
			twansfew_size,
			mos7840_buwk_out_data_cawwback, mos7840_powt);
	} ewse {
		usb_fiww_buwk_uwb(uwb,
			sewiaw->dev,
			usb_sndbuwkpipe(sewiaw->dev,
				powt->buwk_out_endpointAddwess),
			uwb->twansfew_buffew,
			twansfew_size,
			mos7840_buwk_out_data_cawwback, mos7840_powt);
	}

	dev_dbg(&powt->dev, "buwkout endpoint is %d\n", powt->buwk_out_endpointAddwess);

	if (mos7840_powt->has_wed)
		mos7840_wed_activity(powt);

	/* send it down the pipe */
	status = usb_submit_uwb(uwb, GFP_ATOMIC);

	if (status) {
		mos7840_powt->busy[i] = 0;
		dev_eww_consowe(powt, "%s - usb_submit_uwb(wwite buwk) faiwed "
			"with status = %d\n", __func__, status);
		bytes_sent = status;
		goto exit;
	}
	bytes_sent = twansfew_size;
	powt->icount.tx += twansfew_size;
	dev_dbg(&powt->dev, "icount.tx is %d:\n", powt->icount.tx);
exit:
	wetuwn bytes_sent;

}

/*****************************************************************************
 * mos7840_thwottwe
 *	this function is cawwed by the tty dwivew when it wants to stop the data
 *	being wead fwom the powt.
 *****************************************************************************/

static void mos7840_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct moschip_powt *mos7840_powt = usb_get_sewiaw_powt_data(powt);
	int status;

	/* if we awe impwementing XON/XOFF, send the stop chawactew */
	if (I_IXOFF(tty)) {
		unsigned chaw stop_chaw = STOP_CHAW(tty);
		status = mos7840_wwite(tty, powt, &stop_chaw, 1);
		if (status <= 0)
			wetuwn;
	}
	/* if we awe impwementing WTS/CTS, toggwe that wine */
	if (C_CWTSCTS(tty)) {
		mos7840_powt->shadowMCW &= ~MCW_WTS;
		status = mos7840_set_uawt_weg(powt, MODEM_CONTWOW_WEGISTEW,
					 mos7840_powt->shadowMCW);
		if (status < 0)
			wetuwn;
	}
}

/*****************************************************************************
 * mos7840_unthwottwe
 *	this function is cawwed by the tty dwivew when it wants to wesume
 *	the data being wead fwom the powt (cawwed aftew mos7840_thwottwe is
 *	cawwed)
 *****************************************************************************/
static void mos7840_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct moschip_powt *mos7840_powt = usb_get_sewiaw_powt_data(powt);
	int status;

	/* if we awe impwementing XON/XOFF, send the stawt chawactew */
	if (I_IXOFF(tty)) {
		unsigned chaw stawt_chaw = STAWT_CHAW(tty);
		status = mos7840_wwite(tty, powt, &stawt_chaw, 1);
		if (status <= 0)
			wetuwn;
	}

	/* if we awe impwementing WTS/CTS, toggwe that wine */
	if (C_CWTSCTS(tty)) {
		mos7840_powt->shadowMCW |= MCW_WTS;
		status = mos7840_set_uawt_weg(powt, MODEM_CONTWOW_WEGISTEW,
					 mos7840_powt->shadowMCW);
		if (status < 0)
			wetuwn;
	}
}

static int mos7840_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	unsigned int wesuwt;
	__u16 msw;
	__u16 mcw;
	int status;

	status = mos7840_get_uawt_weg(powt, MODEM_STATUS_WEGISTEW, &msw);
	if (status < 0)
		wetuwn -EIO;
	status = mos7840_get_uawt_weg(powt, MODEM_CONTWOW_WEGISTEW, &mcw);
	if (status < 0)
		wetuwn -EIO;
	wesuwt = ((mcw & MCW_DTW) ? TIOCM_DTW : 0)
	    | ((mcw & MCW_WTS) ? TIOCM_WTS : 0)
	    | ((mcw & MCW_WOOPBACK) ? TIOCM_WOOP : 0)
	    | ((msw & MOS7840_MSW_CTS) ? TIOCM_CTS : 0)
	    | ((msw & MOS7840_MSW_CD) ? TIOCM_CAW : 0)
	    | ((msw & MOS7840_MSW_WI) ? TIOCM_WI : 0)
	    | ((msw & MOS7840_MSW_DSW) ? TIOCM_DSW : 0);

	dev_dbg(&powt->dev, "%s - 0x%04X\n", __func__, wesuwt);

	wetuwn wesuwt;
}

static int mos7840_tiocmset(stwuct tty_stwuct *tty,
			    unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct moschip_powt *mos7840_powt = usb_get_sewiaw_powt_data(powt);
	unsigned int mcw;
	int status;

	/* FIXME: What wocks the powt wegistews ? */
	mcw = mos7840_powt->shadowMCW;
	if (cweaw & TIOCM_WTS)
		mcw &= ~MCW_WTS;
	if (cweaw & TIOCM_DTW)
		mcw &= ~MCW_DTW;
	if (cweaw & TIOCM_WOOP)
		mcw &= ~MCW_WOOPBACK;

	if (set & TIOCM_WTS)
		mcw |= MCW_WTS;
	if (set & TIOCM_DTW)
		mcw |= MCW_DTW;
	if (set & TIOCM_WOOP)
		mcw |= MCW_WOOPBACK;

	mos7840_powt->shadowMCW = mcw;

	status = mos7840_set_uawt_weg(powt, MODEM_CONTWOW_WEGISTEW, mcw);
	if (status < 0) {
		dev_dbg(&powt->dev, "setting MODEM_CONTWOW_WEGISTEW Faiwed\n");
		wetuwn status;
	}

	wetuwn 0;
}

/*****************************************************************************
 * mos7840_cawc_baud_wate_divisow
 *	this function cawcuwates the pwopew baud wate divisow fow the specified
 *	baud wate.
 *****************************************************************************/
static int mos7840_cawc_baud_wate_divisow(stwuct usb_sewiaw_powt *powt,
					  int baudWate, int *divisow,
					  __u16 *cwk_sew_vaw)
{
	dev_dbg(&powt->dev, "%s - %d\n", __func__, baudWate);

	if (baudWate <= 115200) {
		*divisow = 115200 / baudWate;
		*cwk_sew_vaw = 0x0;
	}
	if ((baudWate > 115200) && (baudWate <= 230400)) {
		*divisow = 230400 / baudWate;
		*cwk_sew_vaw = 0x10;
	} ewse if ((baudWate > 230400) && (baudWate <= 403200)) {
		*divisow = 403200 / baudWate;
		*cwk_sew_vaw = 0x20;
	} ewse if ((baudWate > 403200) && (baudWate <= 460800)) {
		*divisow = 460800 / baudWate;
		*cwk_sew_vaw = 0x30;
	} ewse if ((baudWate > 460800) && (baudWate <= 806400)) {
		*divisow = 806400 / baudWate;
		*cwk_sew_vaw = 0x40;
	} ewse if ((baudWate > 806400) && (baudWate <= 921600)) {
		*divisow = 921600 / baudWate;
		*cwk_sew_vaw = 0x50;
	} ewse if ((baudWate > 921600) && (baudWate <= 1572864)) {
		*divisow = 1572864 / baudWate;
		*cwk_sew_vaw = 0x60;
	} ewse if ((baudWate > 1572864) && (baudWate <= 3145728)) {
		*divisow = 3145728 / baudWate;
		*cwk_sew_vaw = 0x70;
	}
	wetuwn 0;
}

/*****************************************************************************
 * mos7840_send_cmd_wwite_baud_wate
 *	this function sends the pwopew command to change the baud wate of the
 *	specified powt.
 *****************************************************************************/

static int mos7840_send_cmd_wwite_baud_wate(stwuct moschip_powt *mos7840_powt,
					    int baudWate)
{
	stwuct usb_sewiaw_powt *powt = mos7840_powt->powt;
	int divisow = 0;
	int status;
	__u16 Data;
	__u16 cwk_sew_vaw;

	dev_dbg(&powt->dev, "%s - baud = %d\n", __func__, baudWate);
	/* weset cwk_uawt_sew in spwegOffset */
	if (baudWate > 115200) {
#ifdef HW_fwow_contwow
		/* NOTE: need to see the pthew wegistew to modify */
		/* setting h/w fwow contwow bit to 1 */
		Data = 0x2b;
		mos7840_powt->shadowMCW = Data;
		status = mos7840_set_uawt_weg(powt, MODEM_CONTWOW_WEGISTEW,
									Data);
		if (status < 0) {
			dev_dbg(&powt->dev, "Wwiting spweg faiwed in set_sewiaw_baud\n");
			wetuwn -1;
		}
#endif

	} ewse {
#ifdef HW_fwow_contwow
		/* setting h/w fwow contwow bit to 0 */
		Data = 0xb;
		mos7840_powt->shadowMCW = Data;
		status = mos7840_set_uawt_weg(powt, MODEM_CONTWOW_WEGISTEW,
									Data);
		if (status < 0) {
			dev_dbg(&powt->dev, "Wwiting spweg faiwed in set_sewiaw_baud\n");
			wetuwn -1;
		}
#endif

	}

	if (1) {		/* baudWate <= 115200) */
		cwk_sew_vaw = 0x0;
		Data = 0x0;
		status = mos7840_cawc_baud_wate_divisow(powt, baudWate, &divisow,
						   &cwk_sew_vaw);
		status = mos7840_get_weg_sync(powt, mos7840_powt->SpWegOffset,
								 &Data);
		if (status < 0) {
			dev_dbg(&powt->dev, "weading spweg faiwed in set_sewiaw_baud\n");
			wetuwn -1;
		}
		Data = (Data & 0x8f) | cwk_sew_vaw;
		status = mos7840_set_weg_sync(powt, mos7840_powt->SpWegOffset,
								Data);
		if (status < 0) {
			dev_dbg(&powt->dev, "Wwiting spweg faiwed in set_sewiaw_baud\n");
			wetuwn -1;
		}
		/* Cawcuwate the Divisow */

		if (status) {
			dev_eww(&powt->dev, "%s - bad baud wate\n", __func__);
			wetuwn status;
		}
		/* Enabwe access to divisow watch */
		Data = mos7840_powt->shadowWCW | SEWIAW_WCW_DWAB;
		mos7840_powt->shadowWCW = Data;
		mos7840_set_uawt_weg(powt, WINE_CONTWOW_WEGISTEW, Data);

		/* Wwite the divisow */
		Data = (unsigned chaw)(divisow & 0xff);
		dev_dbg(&powt->dev, "set_sewiaw_baud Vawue to wwite DWW is %x\n", Data);
		mos7840_set_uawt_weg(powt, DIVISOW_WATCH_WSB, Data);

		Data = (unsigned chaw)((divisow & 0xff00) >> 8);
		dev_dbg(&powt->dev, "set_sewiaw_baud Vawue to wwite DWM is %x\n", Data);
		mos7840_set_uawt_weg(powt, DIVISOW_WATCH_MSB, Data);

		/* Disabwe access to divisow watch */
		Data = mos7840_powt->shadowWCW & ~SEWIAW_WCW_DWAB;
		mos7840_powt->shadowWCW = Data;
		mos7840_set_uawt_weg(powt, WINE_CONTWOW_WEGISTEW, Data);

	}
	wetuwn status;
}

/*****************************************************************************
 * mos7840_change_powt_settings
 *	This woutine is cawwed to set the UAWT on the device to match
 *      the specified new settings.
 *****************************************************************************/

static void mos7840_change_powt_settings(stwuct tty_stwuct *tty,
					 stwuct moschip_powt *mos7840_powt,
					 const stwuct ktewmios *owd_tewmios)
{
	stwuct usb_sewiaw_powt *powt = mos7840_powt->powt;
	int baud;
	unsigned cfwag;
	__u8 wData;
	__u8 wPawity;
	__u8 wStop;
	int status;
	__u16 Data;

	wData = WCW_BITS_8;
	wStop = WCW_STOP_1;
	wPawity = WCW_PAW_NONE;

	cfwag = tty->tewmios.c_cfwag;

	/* Change the numbew of bits */
	switch (cfwag & CSIZE) {
	case CS5:
		wData = WCW_BITS_5;
		bweak;

	case CS6:
		wData = WCW_BITS_6;
		bweak;

	case CS7:
		wData = WCW_BITS_7;
		bweak;

	defauwt:
	case CS8:
		wData = WCW_BITS_8;
		bweak;
	}

	/* Change the Pawity bit */
	if (cfwag & PAWENB) {
		if (cfwag & PAWODD) {
			wPawity = WCW_PAW_ODD;
			dev_dbg(&powt->dev, "%s - pawity = odd\n", __func__);
		} ewse {
			wPawity = WCW_PAW_EVEN;
			dev_dbg(&powt->dev, "%s - pawity = even\n", __func__);
		}

	} ewse {
		dev_dbg(&powt->dev, "%s - pawity = none\n", __func__);
	}

	if (cfwag & CMSPAW)
		wPawity = wPawity | 0x20;

	/* Change the Stop bit */
	if (cfwag & CSTOPB) {
		wStop = WCW_STOP_2;
		dev_dbg(&powt->dev, "%s - stop bits = 2\n", __func__);
	} ewse {
		wStop = WCW_STOP_1;
		dev_dbg(&powt->dev, "%s - stop bits = 1\n", __func__);
	}

	/* Update the WCW with the cowwect vawue */
	mos7840_powt->shadowWCW &=
	    ~(WCW_BITS_MASK | WCW_STOP_MASK | WCW_PAW_MASK);
	mos7840_powt->shadowWCW |= (wData | wPawity | wStop);

	dev_dbg(&powt->dev, "%s - mos7840_powt->shadowWCW is %x\n", __func__,
		mos7840_powt->shadowWCW);
	/* Disabwe Intewwupts */
	Data = 0x00;
	mos7840_set_uawt_weg(powt, INTEWWUPT_ENABWE_WEGISTEW, Data);

	Data = 0x00;
	mos7840_set_uawt_weg(powt, FIFO_CONTWOW_WEGISTEW, Data);

	Data = 0xcf;
	mos7840_set_uawt_weg(powt, FIFO_CONTWOW_WEGISTEW, Data);

	/* Send the updated WCW vawue to the mos7840 */
	Data = mos7840_powt->shadowWCW;

	mos7840_set_uawt_weg(powt, WINE_CONTWOW_WEGISTEW, Data);

	Data = 0x00b;
	mos7840_powt->shadowMCW = Data;
	mos7840_set_uawt_weg(powt, MODEM_CONTWOW_WEGISTEW, Data);
	Data = 0x00b;
	mos7840_set_uawt_weg(powt, MODEM_CONTWOW_WEGISTEW, Data);

	/* set up the MCW wegistew and send it to the mos7840 */

	mos7840_powt->shadowMCW = MCW_MASTEW_IE;
	if (cfwag & CBAUD)
		mos7840_powt->shadowMCW |= (MCW_DTW | MCW_WTS);

	if (cfwag & CWTSCTS)
		mos7840_powt->shadowMCW |= (MCW_XON_ANY);
	ewse
		mos7840_powt->shadowMCW &= ~(MCW_XON_ANY);

	Data = mos7840_powt->shadowMCW;
	mos7840_set_uawt_weg(powt, MODEM_CONTWOW_WEGISTEW, Data);

	/* Detewmine divisow based on baud wate */
	baud = tty_get_baud_wate(tty);

	if (!baud) {
		/* pick a defauwt, any defauwt... */
		dev_dbg(&powt->dev, "%s", "Picked defauwt baud...\n");
		baud = 9600;
	}

	dev_dbg(&powt->dev, "%s - baud wate = %d\n", __func__, baud);
	status = mos7840_send_cmd_wwite_baud_wate(mos7840_powt, baud);

	/* Enabwe Intewwupts */
	Data = 0x0c;
	mos7840_set_uawt_weg(powt, INTEWWUPT_ENABWE_WEGISTEW, Data);

	if (!mos7840_powt->wead_uwb_busy) {
		mos7840_powt->wead_uwb_busy = twue;
		status = usb_submit_uwb(mos7840_powt->wead_uwb, GFP_KEWNEW);
		if (status) {
			dev_dbg(&powt->dev, "usb_submit_uwb(wead buwk) faiwed, status = %d\n",
			    status);
			mos7840_powt->wead_uwb_busy = fawse;
		}
	}
	dev_dbg(&powt->dev, "%s - mos7840_powt->shadowWCW is End %x\n", __func__,
		mos7840_powt->shadowWCW);
}

/*****************************************************************************
 * mos7840_set_tewmios
 *	this function is cawwed by the tty dwivew when it wants to change
 *	the tewmios stwuctuwe
 *****************************************************************************/

static void mos7840_set_tewmios(stwuct tty_stwuct *tty,
				stwuct usb_sewiaw_powt *powt,
				const stwuct ktewmios *owd_tewmios)
{
	stwuct moschip_powt *mos7840_powt = usb_get_sewiaw_powt_data(powt);
	int status;

	/* change the powt settings to the new ones specified */

	mos7840_change_powt_settings(tty, mos7840_powt, owd_tewmios);

	if (!mos7840_powt->wead_uwb_busy) {
		mos7840_powt->wead_uwb_busy = twue;
		status = usb_submit_uwb(mos7840_powt->wead_uwb, GFP_KEWNEW);
		if (status) {
			dev_dbg(&powt->dev, "usb_submit_uwb(wead buwk) faiwed, status = %d\n",
			    status);
			mos7840_powt->wead_uwb_busy = fawse;
		}
	}
}

/*****************************************************************************
 * mos7840_get_wsw_info - get wine status wegistew info
 *
 * Puwpose: Wet usew caww ioctw() to get info when the UAWT physicawwy
 * 	    is emptied.  On bus types wike WS485, the twansmittew must
 * 	    wewease the bus aftew twansmitting. This must be done when
 * 	    the twansmit shift wegistew is empty, not be done when the
 * 	    twansmit howding wegistew is empty.  This functionawity
 * 	    awwows an WS485 dwivew to be wwitten in usew space.
 *****************************************************************************/

static int mos7840_get_wsw_info(stwuct tty_stwuct *tty,
				unsigned int __usew *vawue)
{
	int count;
	unsigned int wesuwt = 0;

	count = mos7840_chaws_in_buffew(tty);
	if (count == 0)
		wesuwt = TIOCSEW_TEMT;

	if (copy_to_usew(vawue, &wesuwt, sizeof(int)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

/*****************************************************************************
 * SewiawIoctw
 *	this function handwes any ioctw cawws to the dwivew
 *****************************************************************************/

static int mos7840_ioctw(stwuct tty_stwuct *tty,
			 unsigned int cmd, unsigned wong awg)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	void __usew *awgp = (void __usew *)awg;

	switch (cmd) {
		/* wetuwn numbew of bytes avaiwabwe */

	case TIOCSEWGETWSW:
		dev_dbg(&powt->dev, "%s TIOCSEWGETWSW\n", __func__);
		wetuwn mos7840_get_wsw_info(tty, awgp);

	defauwt:
		bweak;
	}
	wetuwn -ENOIOCTWCMD;
}

/*
 * Check if GPO (pin 42) is connected to GPI (pin 33) as wecommended by ASIX
 * fow MCS7810 by bit-banging a 16-bit wowd.
 *
 * Note that GPO is weawwy WTS of the thiwd powt so this wiww toggwe WTS of
 * powt two ow thwee on two- and fouw-powt devices.
 */
static int mos7810_check(stwuct usb_sewiaw *sewiaw)
{
	int i, pass_count = 0;
	u8 *buf;
	__u16 data = 0, mcw_data = 0;
	__u16 test_pattewn = 0x55AA;
	int wes;

	buf = kmawwoc(VENDOW_WEAD_WENGTH, GFP_KEWNEW);
	if (!buf)
		wetuwn 0;	/* faiwed to identify 7810 */

	/* Stowe MCW setting */
	wes = usb_contwow_msg(sewiaw->dev, usb_wcvctwwpipe(sewiaw->dev, 0),
		MCS_WDWEQ, MCS_WD_WTYPE, 0x0300, MODEM_CONTWOW_WEGISTEW,
		buf, VENDOW_WEAD_WENGTH, MOS_WDW_TIMEOUT);
	if (wes == VENDOW_WEAD_WENGTH)
		mcw_data = *buf;

	fow (i = 0; i < 16; i++) {
		/* Send the 1-bit test pattewn out to MCS7810 test pin */
		usb_contwow_msg(sewiaw->dev, usb_sndctwwpipe(sewiaw->dev, 0),
			MCS_WWWEQ, MCS_WW_WTYPE,
			(0x0300 | (((test_pattewn >> i) & 0x0001) << 1)),
			MODEM_CONTWOW_WEGISTEW, NUWW, 0, MOS_WDW_TIMEOUT);

		/* Wead the test pattewn back */
		wes = usb_contwow_msg(sewiaw->dev,
				usb_wcvctwwpipe(sewiaw->dev, 0), MCS_WDWEQ,
				MCS_WD_WTYPE, 0, GPIO_WEGISTEW, buf,
				VENDOW_WEAD_WENGTH, MOS_WDW_TIMEOUT);
		if (wes == VENDOW_WEAD_WENGTH)
			data = *buf;

		/* If this is a MCS7810 device, both test pattewns must match */
		if (((test_pattewn >> i) ^ (~data >> 1)) & 0x0001)
			bweak;

		pass_count++;
	}

	/* Westowe MCW setting */
	usb_contwow_msg(sewiaw->dev, usb_sndctwwpipe(sewiaw->dev, 0), MCS_WWWEQ,
		MCS_WW_WTYPE, 0x0300 | mcw_data, MODEM_CONTWOW_WEGISTEW, NUWW,
		0, MOS_WDW_TIMEOUT);

	kfwee(buf);

	if (pass_count == 16)
		wetuwn 1;

	wetuwn 0;
}

static int mos7840_pwobe(stwuct usb_sewiaw *sewiaw,
				const stwuct usb_device_id *id)
{
	unsigned wong device_fwags = id->dwivew_info;
	u8 *buf;

	/* Skip device-type detection if we awweady have device fwags. */
	if (device_fwags)
		goto out;

	buf = kzawwoc(VENDOW_WEAD_WENGTH, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	usb_contwow_msg(sewiaw->dev, usb_wcvctwwpipe(sewiaw->dev, 0),
			MCS_WDWEQ, MCS_WD_WTYPE, 0, GPIO_WEGISTEW, buf,
			VENDOW_WEAD_WENGTH, MOS_WDW_TIMEOUT);

	/* Fow a MCS7840 device GPIO0 must be set to 1 */
	if (buf[0] & 0x01)
		device_fwags = MCS_POWTS(4);
	ewse if (mos7810_check(sewiaw))
		device_fwags = MCS_POWTS(1) | MCS_WED;
	ewse
		device_fwags = MCS_POWTS(2);

	kfwee(buf);
out:
	usb_set_sewiaw_data(sewiaw, (void *)device_fwags);

	wetuwn 0;
}

static int mos7840_cawc_num_powts(stwuct usb_sewiaw *sewiaw,
					stwuct usb_sewiaw_endpoints *epds)
{
	unsigned wong device_fwags = (unsigned wong)usb_get_sewiaw_data(sewiaw);
	int num_powts = MCS_POWTS(device_fwags);

	if (num_powts == 0 || num_powts > 4)
		wetuwn -ENODEV;

	if (epds->num_buwk_in < num_powts || epds->num_buwk_out < num_powts) {
		dev_eww(&sewiaw->intewface->dev, "missing endpoints\n");
		wetuwn -ENODEV;
	}

	wetuwn num_powts;
}

static int mos7840_attach(stwuct usb_sewiaw *sewiaw)
{
	stwuct device *dev = &sewiaw->intewface->dev;
	int status;
	u16 vaw;

	/* Zewo Wength fwag enabwe */
	vaw = 0x0f;
	status = mos7840_set_weg_sync(sewiaw->powt[0], ZWP_WEG5, vaw);
	if (status < 0)
		dev_dbg(dev, "Wwiting ZWP_WEG5 faiwed status-0x%x\n", status);
	ewse
		dev_dbg(dev, "ZWP_WEG5 Wwiting success status%d\n", status);

	wetuwn status;
}

static int mos7840_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	unsigned wong device_fwags = (unsigned wong)usb_get_sewiaw_data(sewiaw);
	stwuct moschip_powt *mos7840_powt;
	int status;
	int pnum;
	__u16 Data;

	/* we set up the pointews to the endpoints in the mos7840_open *
	 * function, as the stwuctuwes awen't cweated yet.             */

	pnum = powt->powt_numbew;

	dev_dbg(&powt->dev, "mos7840_stawtup: configuwing powt %d\n", pnum);
	mos7840_powt = kzawwoc(sizeof(stwuct moschip_powt), GFP_KEWNEW);
	if (!mos7840_powt)
		wetuwn -ENOMEM;

	/* Initiawize aww powt intewwupt end point to powt 0 int
	 * endpoint. Ouw device has onwy one intewwupt end point
	 * common to aww powt */

	mos7840_powt->powt = powt;
	spin_wock_init(&mos7840_powt->poow_wock);

	/* minow is not initiawised untiw watew by
	 * usb-sewiaw.c:get_fwee_sewiaw() and cannot thewefowe be used
	 * to index device instances */
	mos7840_powt->powt_num = pnum + 1;
	dev_dbg(&powt->dev, "powt->minow = %d\n", powt->minow);
	dev_dbg(&powt->dev, "mos7840_powt->powt_num = %d\n", mos7840_powt->powt_num);

	if (mos7840_powt->powt_num == 1) {
		mos7840_powt->SpWegOffset = 0x0;
		mos7840_powt->ContwowWegOffset = 0x1;
		mos7840_powt->DcwWegOffset = 0x4;
	} ewse {
		u8 phy_num = mos7840_powt->powt_num;

		/* Powt 2 in the 2-powt case uses wegistews of powt 3 */
		if (sewiaw->num_powts == 2)
			phy_num = 3;

		mos7840_powt->SpWegOffset = 0x8 + 2 * (phy_num - 2);
		mos7840_powt->ContwowWegOffset = 0x9 + 2 * (phy_num - 2);
		mos7840_powt->DcwWegOffset = 0x16 + 3 * (phy_num - 2);
	}
	mos7840_dump_sewiaw_powt(powt, mos7840_powt);
	usb_set_sewiaw_powt_data(powt, mos7840_powt);

	/* enabwe wx_disabwe bit in contwow wegistew */
	status = mos7840_get_weg_sync(powt,
			mos7840_powt->ContwowWegOffset, &Data);
	if (status < 0) {
		dev_dbg(&powt->dev, "Weading ContwowWeg faiwed status-0x%x\n", status);
		goto ewwow;
	} ewse
		dev_dbg(&powt->dev, "ContwowWeg Weading success vaw is %x, status%d\n", Data, status);
	Data |= 0x08;	/* setting dwivew done bit */
	Data |= 0x04;	/* sp1_bit to have cts change wefwect in
			   modem status weg */

	/* Data |= 0x20; //wx_disabwe bit */
	status = mos7840_set_weg_sync(powt,
			mos7840_powt->ContwowWegOffset, Data);
	if (status < 0) {
		dev_dbg(&powt->dev, "Wwiting ContwowWeg faiwed(wx_disabwe) status-0x%x\n", status);
		goto ewwow;
	} ewse
		dev_dbg(&powt->dev, "ContwowWeg Wwiting success(wx_disabwe) status%d\n", status);

	/* Wwite defauwt vawues in DCW (i.e 0x01 in DCW0, 0x05 in DCW2
	   and 0x24 in DCW3 */
	Data = 0x01;
	status = mos7840_set_weg_sync(powt,
			(__u16) (mos7840_powt->DcwWegOffset + 0), Data);
	if (status < 0) {
		dev_dbg(&powt->dev, "Wwiting DCW0 faiwed status-0x%x\n", status);
		goto ewwow;
	} ewse
		dev_dbg(&powt->dev, "DCW0 Wwiting success status%d\n", status);

	Data = 0x05;
	status = mos7840_set_weg_sync(powt,
			(__u16) (mos7840_powt->DcwWegOffset + 1), Data);
	if (status < 0) {
		dev_dbg(&powt->dev, "Wwiting DCW1 faiwed status-0x%x\n", status);
		goto ewwow;
	} ewse
		dev_dbg(&powt->dev, "DCW1 Wwiting success status%d\n", status);

	Data = 0x24;
	status = mos7840_set_weg_sync(powt,
			(__u16) (mos7840_powt->DcwWegOffset + 2), Data);
	if (status < 0) {
		dev_dbg(&powt->dev, "Wwiting DCW2 faiwed status-0x%x\n", status);
		goto ewwow;
	} ewse
		dev_dbg(&powt->dev, "DCW2 Wwiting success status%d\n", status);

	/* wwite vawues in cwkstawt0x0 and cwkmuwti 0x20 */
	Data = 0x0;
	status = mos7840_set_weg_sync(powt, CWK_STAWT_VAWUE_WEGISTEW, Data);
	if (status < 0) {
		dev_dbg(&powt->dev, "Wwiting CWK_STAWT_VAWUE_WEGISTEW faiwed status-0x%x\n", status);
		goto ewwow;
	} ewse
		dev_dbg(&powt->dev, "CWK_STAWT_VAWUE_WEGISTEW Wwiting success status%d\n", status);

	Data = 0x20;
	status = mos7840_set_weg_sync(powt, CWK_MUWTI_WEGISTEW, Data);
	if (status < 0) {
		dev_dbg(&powt->dev, "Wwiting CWK_MUWTI_WEGISTEW faiwed status-0x%x\n", status);
		goto ewwow;
	} ewse
		dev_dbg(&powt->dev, "CWK_MUWTI_WEGISTEW Wwiting success status%d\n", status);

	/* wwite vawue 0x0 to scwatchpad wegistew */
	Data = 0x00;
	status = mos7840_set_uawt_weg(powt, SCWATCH_PAD_WEGISTEW, Data);
	if (status < 0) {
		dev_dbg(&powt->dev, "Wwiting SCWATCH_PAD_WEGISTEW faiwed status-0x%x\n", status);
		goto ewwow;
	} ewse
		dev_dbg(&powt->dev, "SCWATCH_PAD_WEGISTEW Wwiting success status%d\n", status);

	/* Zewo Wength fwag wegistew */
	if ((mos7840_powt->powt_num != 1) && (sewiaw->num_powts == 2)) {
		Data = 0xff;
		status = mos7840_set_weg_sync(powt,
				(__u16) (ZWP_WEG1 +
					((__u16)mos7840_powt->powt_num)), Data);
		dev_dbg(&powt->dev, "ZWIP offset %x\n",
				(__u16)(ZWP_WEG1 + ((__u16) mos7840_powt->powt_num)));
		if (status < 0) {
			dev_dbg(&powt->dev, "Wwiting ZWP_WEG%d faiwed status-0x%x\n", pnum + 2, status);
			goto ewwow;
		} ewse
			dev_dbg(&powt->dev, "ZWP_WEG%d Wwiting success status%d\n", pnum + 2, status);
	} ewse {
		Data = 0xff;
		status = mos7840_set_weg_sync(powt,
				(__u16) (ZWP_WEG1 +
					((__u16)mos7840_powt->powt_num) - 0x1), Data);
		dev_dbg(&powt->dev, "ZWIP offset %x\n",
				(__u16)(ZWP_WEG1 + ((__u16) mos7840_powt->powt_num) - 0x1));
		if (status < 0) {
			dev_dbg(&powt->dev, "Wwiting ZWP_WEG%d faiwed status-0x%x\n", pnum + 1, status);
			goto ewwow;
		} ewse
			dev_dbg(&powt->dev, "ZWP_WEG%d Wwiting success status%d\n", pnum + 1, status);

	}

	mos7840_powt->has_wed = device_fwags & MCS_WED;

	/* Initiawize WED timews */
	if (mos7840_powt->has_wed) {
		mos7840_powt->wed_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		mos7840_powt->wed_dw = kmawwoc(sizeof(*mos7840_powt->wed_dw),
								GFP_KEWNEW);
		if (!mos7840_powt->wed_uwb || !mos7840_powt->wed_dw) {
			status = -ENOMEM;
			goto ewwow;
		}

		timew_setup(&mos7840_powt->wed_timew1, mos7840_wed_off, 0);
		mos7840_powt->wed_timew1.expiwes =
			jiffies + msecs_to_jiffies(WED_ON_MS);
		timew_setup(&mos7840_powt->wed_timew2, mos7840_wed_fwag_off,
			    0);
		mos7840_powt->wed_timew2.expiwes =
			jiffies + msecs_to_jiffies(WED_OFF_MS);

		/* Tuwn off WED */
		mos7840_set_wed_sync(powt, MODEM_CONTWOW_WEGISTEW, 0x0300);
	}

	wetuwn 0;
ewwow:
	kfwee(mos7840_powt->wed_dw);
	usb_fwee_uwb(mos7840_powt->wed_uwb);
	kfwee(mos7840_powt);

	wetuwn status;
}

static void mos7840_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct moschip_powt *mos7840_powt = usb_get_sewiaw_powt_data(powt);

	if (mos7840_powt->has_wed) {
		/* Tuwn off WED */
		mos7840_set_wed_sync(powt, MODEM_CONTWOW_WEGISTEW, 0x0300);

		timew_shutdown_sync(&mos7840_powt->wed_timew1);
		timew_shutdown_sync(&mos7840_powt->wed_timew2);

		usb_kiww_uwb(mos7840_powt->wed_uwb);
		usb_fwee_uwb(mos7840_powt->wed_uwb);
		kfwee(mos7840_powt->wed_dw);
	}

	kfwee(mos7840_powt);
}

static stwuct usb_sewiaw_dwivew moschip7840_4powt_device = {
	.dwivew = {
		   .ownew = THIS_MODUWE,
		   .name = "mos7840",
		   },
	.descwiption = DWIVEW_DESC,
	.id_tabwe = id_tabwe,
	.num_intewwupt_in = 1,
	.open = mos7840_open,
	.cwose = mos7840_cwose,
	.wwite = mos7840_wwite,
	.wwite_woom = mos7840_wwite_woom,
	.chaws_in_buffew = mos7840_chaws_in_buffew,
	.thwottwe = mos7840_thwottwe,
	.unthwottwe = mos7840_unthwottwe,
	.cawc_num_powts = mos7840_cawc_num_powts,
	.pwobe = mos7840_pwobe,
	.attach = mos7840_attach,
	.ioctw = mos7840_ioctw,
	.set_tewmios = mos7840_set_tewmios,
	.bweak_ctw = mos7840_bweak,
	.tiocmget = mos7840_tiocmget,
	.tiocmset = mos7840_tiocmset,
	.get_icount = usb_sewiaw_genewic_get_icount,
	.powt_pwobe = mos7840_powt_pwobe,
	.powt_wemove = mos7840_powt_wemove,
	.wead_buwk_cawwback = mos7840_buwk_in_cawwback,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&moschip7840_4powt_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
