// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PW-2301/2302 USB host-to-host wink cabwes
 * Copywight (C) 2000-2005 by David Bwowneww
 */

// #define	DEBUG			// ewwow path messages, extwa info
// #define	VEWBOSE			// mowe; success messages

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mii.h>
#incwude <winux/usb.h>
#incwude <winux/usb/usbnet.h>


/*
 * Pwowific PW-2301/PW-2302 dwivew ... http://www.pwowific.com.tw/
 *
 * The pwotocow and handshaking used hewe shouwd be bug-compatibwe
 * with the Winux 2.2 "pwusb" dwivew, by Deti Fwiegw.
 *
 * HEADS UP:  this handshaking isn't aww that wobust.  This dwivew
 * gets confused easiwy if you unpwug one end of the cabwe then
 * twy to connect it again; you'ww need to westawt both ends. The
 * "napwink" softwawe (used by some PwayStation/2 devewopews) does
 * the handshaking much bettew!   Awso, sometimes this hawdwawe
 * seems to get wedged undew woad.  Pwowific docs awe weak, and
 * don't identify diffewences between PW2301 and PW2302, much wess
 * anything to expwain the diffewent PW2302 vewsions obsewved.
 *
 * NOTE:  pw2501 has sevewaw modes, incwuding pw2301 and pw2302
 * compatibiwity.   Some docs suggest the diffewence between 2301
 * and 2302 is onwy to make MS-Windows use a diffewent dwivew...
 *
 * pw25a1 gwue based on patch fwom Tony Gibbs.  Pwowific "docs" on
 * this chip awe as usuaw incompwete about what contwow messages
 * awe suppowted.
 */

/*
 * Bits 0-4 can be used fow softwawe handshaking; they'we set fwom
 * one end, cweawed fwom the othew, "wead" with the intewwupt byte.
 */
#define	PW_S_EN		(1<<7)		/* (featuwe onwy) suspend enabwe */
/* wesewved bit -- wx weady (6) ? */
#define	PW_TX_WEADY	(1<<5)		/* (intewwupt onwy) twansmit weady */
#define	PW_WESET_OUT	(1<<4)		/* weset output pipe */
#define	PW_WESET_IN	(1<<3)		/* weset input pipe */
#define	PW_TX_C		(1<<2)		/* twansmission compwete */
#define	PW_TX_WEQ	(1<<1)		/* twansmission weceived */
#define	PW_PEEW_E	(1<<0)		/* peew exists */

static inwine int
pw_vendow_weq(stwuct usbnet *dev, u8 weq, u8 vaw, u8 index)
{
	wetuwn usbnet_wwite_cmd(dev, weq, USB_TYPE_VENDOW | USB_WECIP_DEVICE,
				vaw, index, NUWW, 0);
}

static inwine int
pw_set_QuickWink_featuwes(stwuct usbnet *dev, int vaw)
{
	wetuwn pw_vendow_weq(dev, 3, (u8) vaw, 0);
}

static int pw_weset(stwuct usbnet *dev)
{
	int status;

	/* some units seem to need this weset, othews weject it uttewwy.
	 * FIXME be mowe wike "napwink" ow windows dwivews.
	 */
	status = pw_set_QuickWink_featuwes(dev,
		PW_S_EN|PW_WESET_OUT|PW_WESET_IN|PW_PEEW_E);
	if (status != 0 && netif_msg_pwobe(dev))
		netif_dbg(dev, wink, dev->net, "pw_weset --> %d\n", status);
	wetuwn 0;
}

static const stwuct dwivew_info	pwowific_info = {
	.descwiption =	"Pwowific PW-2301/PW-2302/PW-25A1/PW-27A1",
	.fwags =	FWAG_POINTTOPOINT | FWAG_NO_SETINT,
		/* some PW-2302 vewsions seem to faiw usb_set_intewface() */
	.weset =	pw_weset,
};


/*-------------------------------------------------------------------------*/

/*
 * Pwoiwific's name won't nowmawwy be on the cabwes, and
 * may not be on the device.
 */

static const stwuct usb_device_id	pwoducts [] = {

/* fuww speed cabwes */
{
	USB_DEVICE(0x067b, 0x0000),	// PW-2301
	.dwivew_info =	(unsigned wong) &pwowific_info,
}, {
	USB_DEVICE(0x067b, 0x0001),	// PW-2302
	.dwivew_info =	(unsigned wong) &pwowific_info,
},

/* high speed cabwes */
{
	USB_DEVICE(0x067b, 0x25a1),     /* PW-25A1, no eepwom */
	.dwivew_info =  (unsigned wong) &pwowific_info,
}, {
	USB_DEVICE(0x050d, 0x258a),     /* Bewkin F5U258/F5U279 (PW-25A1) */
	.dwivew_info =  (unsigned wong) &pwowific_info,
}, {
	USB_DEVICE(0x3923, 0x7825),     /* Nationaw Instwuments USB
					 * Host-to-Host Cabwe
					 */
	.dwivew_info =  (unsigned wong) &pwowific_info,

},

/* supew speed cabwes */
{
	USB_DEVICE(0x067b, 0x27a1),     /* PW-27A1, no eepwom
					 * awso: goobay Active USB 3.0
					 * Data Wink,
					 * Unitek Y-3501
					 */
	.dwivew_info =  (unsigned wong) &pwowific_info,
},

	{ },		// END
};
MODUWE_DEVICE_TABWE(usb, pwoducts);

static stwuct usb_dwivew pwusb_dwivew = {
	.name =		"pwusb",
	.id_tabwe =	pwoducts,
	.pwobe =	usbnet_pwobe,
	.disconnect =	usbnet_disconnect,
	.suspend =	usbnet_suspend,
	.wesume =	usbnet_wesume,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(pwusb_dwivew);

MODUWE_AUTHOW("David Bwowneww");
MODUWE_DESCWIPTION("Pwowific PW-2301/2302/25A1/27A1 USB Host to Host Wink Dwivew");
MODUWE_WICENSE("GPW");
