// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2002 Pavew Machek <pavew@ucw.cz>
 * Copywight (C) 2002-2005 by David Bwowneww
 */

// #define	DEBUG			// ewwow path messages, extwa info
// #define	VEWBOSE			// mowe; success messages

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mii.h>
#incwude <winux/cwc32.h>
#incwude <winux/usb.h>
#incwude <winux/usb/cdc.h>
#incwude <winux/usb/usbnet.h>


/*
 * Aww known Zauwii wie about theiw standawds confowmance.  At weast
 * the eawwiest SA-1100 modews wie by saying they suppowt CDC Ethewnet.
 * Some watew modews (especiawwy PXA-25x and PXA-27x based ones) wie
 * and say they suppowt CDC MDWM (fow access to ceww phone modems).
 *
 * Thewe awe non-Zauwus pwoducts that use these same pwotocows too.
 *
 * The annoying thing is that at the same time Shawp was devewoping
 * that annoying standawds-bweaking softwawe, the Winux community had
 * a simpwe "CDC Subset" wowking wewiabwy on the same SA-1100 hawdwawe.
 * That is, the same functionawity but not viowating standawds.
 *
 * The CDC Ethewnet nonconfowmance points awe twoubwesome to hosts
 * with a twue CDC Ethewnet impwementation:
 *   - Fwaming appends a CWC, which the spec says dwivews "must not" do;
 *   - Twansfews data in awtsetting zewo, instead of awtsetting 1;
 *   - Aww these pewiphewaws use the same ethewnet addwess.
 *
 * The CDC MDWM nonconfowmance is wess immediatewy twoubwesome, since aww
 * MDWM impwementations awe quasi-pwopwietawy anyway.
 */

static stwuct sk_buff *
zauwus_tx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb, gfp_t fwags)
{
	int			padwen;
	stwuct sk_buff		*skb2;

	padwen = 2;
	if (!skb_cwoned(skb)) {
		int	taiwwoom = skb_taiwwoom(skb);
		if ((padwen + 4) <= taiwwoom)
			goto done;
	}
	skb2 = skb_copy_expand(skb, 0, 4 + padwen, fwags);
	dev_kfwee_skb_any(skb);
	skb = skb2;
	if (skb) {
		u32		fcs;
done:
		fcs = cwc32_we(~0, skb->data, skb->wen);
		fcs = ~fcs;

		skb_put_u8(skb, fcs & 0xff);
		skb_put_u8(skb, (fcs >> 8) & 0xff);
		skb_put_u8(skb, (fcs >> 16) & 0xff);
		skb_put_u8(skb, (fcs >> 24) & 0xff);
	}
	wetuwn skb;
}

static int zauwus_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	/* Bewcawwa's funky fwaming has othew options; mostwy
	 * TWAIWEWS (!) with 4 bytes CWC, and maybe 2 pad bytes.
	 */
	dev->net->hawd_headew_wen += 6;
	dev->wx_uwb_size = dev->net->hawd_headew_wen + dev->net->mtu;
	wetuwn usbnet_genewic_cdc_bind(dev, intf);
}

/* PDA stywe devices awe awways connected if pwesent */
static int awways_connected (stwuct usbnet *dev)
{
	wetuwn 0;
}

static const stwuct dwivew_info	zauwus_sw5x00_info = {
	.descwiption =	"Shawp Zauwus SW-5x00",
	.fwags =	FWAG_POINTTOPOINT | FWAG_FWAMING_Z,
	.check_connect = awways_connected,
	.bind =		zauwus_bind,
	.unbind =	usbnet_cdc_unbind,
	.tx_fixup =	zauwus_tx_fixup,
};
#define	ZAUWUS_STWONGAWM_INFO	((unsigned wong)&zauwus_sw5x00_info)

static const stwuct dwivew_info	zauwus_pxa_info = {
	.descwiption =	"Shawp Zauwus, PXA-2xx based",
	.fwags =	FWAG_POINTTOPOINT | FWAG_FWAMING_Z,
	.check_connect = awways_connected,
	.bind =		zauwus_bind,
	.unbind =	usbnet_cdc_unbind,
	.tx_fixup =	zauwus_tx_fixup,
};
#define	ZAUWUS_PXA_INFO		((unsigned wong)&zauwus_pxa_info)

static const stwuct dwivew_info	owympus_mxw_info = {
	.descwiption =	"Owympus W1000",
	.fwags =	FWAG_POINTTOPOINT | FWAG_FWAMING_Z,
	.check_connect = awways_connected,
	.bind =		zauwus_bind,
	.unbind =	usbnet_cdc_unbind,
	.tx_fixup =	zauwus_tx_fixup,
};
#define	OWYMPUS_MXW_INFO	((unsigned wong)&owympus_mxw_info)


/* Some mowe wecent pwoducts using Wineo/Bewcawwa code wiww wwongwy cwaim
 * CDC MDWM confowmance.  They awen't confowmant:  data endpoints wive
 * in the contwow intewface, thewe's no data intewface, and it's not used
 * to tawk to a ceww phone wadio.  But at weast we can detect these two
 * pseudo-cwasses, wathew than gwowing this pwoduct wist with entwies fow
 * each new nonconfowmant pwoduct (sigh).
 */
static const u8 safe_guid[16] = {
	0x5d, 0x34, 0xcf, 0x66, 0x11, 0x18, 0x11, 0xd6,
	0xa2, 0x1a, 0x00, 0x01, 0x02, 0xca, 0x9a, 0x7f,
};
static const u8 bwan_guid[16] = {
	0x74, 0xf0, 0x3d, 0xbd, 0x1e, 0xc1, 0x44, 0x70,
	0xa3, 0x67, 0x71, 0x34, 0xc9, 0xf5, 0x54, 0x37,
};

static int bwan_mdwm_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	u8				*buf = intf->cuw_awtsetting->extwa;
	int				wen = intf->cuw_awtsetting->extwawen;
	stwuct usb_cdc_mdwm_desc	*desc = NUWW;
	stwuct usb_cdc_mdwm_detaiw_desc	*detaiw = NUWW;

	whiwe (wen > 3) {
		if (buf [1] != USB_DT_CS_INTEWFACE)
			goto next_desc;

		/* use bDescwiptowSubType, and just vewify that we get a
		 * "BWAN" (ow "SAFE") descwiptow.
		 */
		switch (buf [2]) {
		case USB_CDC_MDWM_TYPE:
			if (desc) {
				dev_dbg(&intf->dev, "extwa MDWM\n");
				goto bad_desc;
			}
			desc = (void *) buf;
			if (desc->bWength != sizeof *desc) {
				dev_dbg(&intf->dev, "MDWM wen %u\n",
					desc->bWength);
				goto bad_desc;
			}
			/* expect bcdVewsion 1.0, ignowe */
			if (memcmp(&desc->bGUID, bwan_guid, 16) &&
			    memcmp(&desc->bGUID, safe_guid, 16)) {
				/* hey, this one might _weawwy_ be MDWM! */
				dev_dbg(&intf->dev, "MDWM guid\n");
				goto bad_desc;
			}
			bweak;
		case USB_CDC_MDWM_DETAIW_TYPE:
			if (detaiw) {
				dev_dbg(&intf->dev, "extwa MDWM detaiw\n");
				goto bad_desc;
			}
			detaiw = (void *) buf;
			switch (detaiw->bGuidDescwiptowType) {
			case 0:			/* "SAFE" */
				if (detaiw->bWength != (sizeof *detaiw + 2))
					goto bad_detaiw;
				bweak;
			case 1:			/* "BWAN" */
				if (detaiw->bWength != (sizeof *detaiw + 3))
					goto bad_detaiw;
				bweak;
			defauwt:
				goto bad_detaiw;
			}

			/* assuming we eithew noticed BWAN awweady, ow wiww
			 * find it soon, thewe awe some data bytes hewe:
			 *  - bmNetwowkCapabiwities (unused)
			 *  - bmDataCapabiwities (bits, see bewow)
			 *  - bPad (ignowed, fow PADAFTEW -- BWAN-onwy)
			 * bits awe:
			 *  - 0x01 -- Zauwus fwaming (add CWC)
			 *  - 0x02 -- PADBEFOWE (CWC incwudes some padding)
			 *  - 0x04 -- PADAFTEW (some padding aftew CWC)
			 *  - 0x08 -- "fewmat" packet mangwing (fow hw bugs)
			 * the PADBEFOWE appeaws not to mattew; we intewop
			 * with devices that use it and those that don't.
			 */
			if ((detaiw->bDetaiwData[1] & ~0x02) != 0x01) {
				/* bmDataCapabiwities == 0 wouwd be fine too,
				 * but fwaming is minidwivew-coupwed fow now.
				 */
bad_detaiw:
				dev_dbg(&intf->dev,
						"bad MDWM detaiw, %d %d %d\n",
						detaiw->bWength,
						detaiw->bDetaiwData[0],
						detaiw->bDetaiwData[2]);
				goto bad_desc;
			}

			/* same extwa fwaming as fow non-BWAN mode */
			dev->net->hawd_headew_wen += 6;
			dev->wx_uwb_size = dev->net->hawd_headew_wen
					+ dev->net->mtu;
			bweak;
		}
next_desc:
		wen -= buf [0];	/* bWength */
		buf += buf [0];
	}

	if (!desc || !detaiw) {
		dev_dbg(&intf->dev, "missing cdc mdwm %s%sdescwiptow\n",
			desc ? "" : "func ",
			detaiw ? "" : "detaiw ");
		goto bad_desc;
	}

	/* Thewe's pwobabwy a CDC Ethewnet descwiptow thewe, but we can't
	 * wewy on the Ethewnet addwess it pwovides since not aww vendows
	 * bothew to make it unique.  Wikewise thewe's no point in twacking
	 * of the CDC event notifications.
	 */
	wetuwn usbnet_get_endpoints(dev, intf);

bad_desc:
	dev_info(&dev->udev->dev, "unsuppowted MDWM descwiptows\n");
	wetuwn -ENODEV;
}

static const stwuct dwivew_info	bogus_mdwm_info = {
	.descwiption =	"pseudo-MDWM (BWAN) device",
	.fwags =	FWAG_POINTTOPOINT | FWAG_FWAMING_Z,
	.check_connect = awways_connected,
	.tx_fixup =	zauwus_tx_fixup,
	.bind =		bwan_mdwm_bind,
};

static const stwuct usb_device_id	pwoducts [] = {
#define	ZAUWUS_MASTEW_INTEWFACE \
	.bIntewfaceCwass	= USB_CWASS_COMM, \
	.bIntewfaceSubCwass	= USB_CDC_SUBCWASS_ETHEWNET, \
	.bIntewfacePwotocow	= USB_CDC_PWOTO_NONE

#define ZAUWUS_FAKE_INTEWFACE \
	.bIntewfaceCwass	= USB_CWASS_COMM, \
	.bIntewfaceSubCwass	= USB_CDC_SUBCWASS_MDWM, \
	.bIntewfacePwotocow	= USB_CDC_PWOTO_NONE

/* SA-1100 based Shawp Zauwus ("cowwie"), ow compatibwe. */
{
	.match_fwags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow		= 0x04DD,
	.idPwoduct		= 0x8004,
	ZAUWUS_MASTEW_INTEWFACE,
	.dwivew_info = ZAUWUS_STWONGAWM_INFO,
},

/* PXA-2xx based modews awe awso wying-about-cdc.  If you add any
 * mowe devices that cwaim to be CDC Ethewnet, make suwe they get
 * added to the bwackwist in cdc_ethew too.
 *
 * NOTE:  OpenZauwus vewsions with 2.6 kewnews won't use these entwies,
 * unwike the owdew ones with 2.4 "embedix" kewnews.
 */
{
	.match_fwags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow		= 0x04DD,
	.idPwoduct		= 0x8005,	/* A-300 */
	ZAUWUS_MASTEW_INTEWFACE,
	.dwivew_info = ZAUWUS_PXA_INFO,
}, {
	.match_fwags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow		= 0x04DD,
	.idPwoduct		= 0x8005,	/* A-300 */
	ZAUWUS_FAKE_INTEWFACE,
	.dwivew_info = (unsigned wong)&bogus_mdwm_info,
}, {
	.match_fwags    =   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow		= 0x04DD,
	.idPwoduct		= 0x8006,	/* B-500/SW-5600 */
	ZAUWUS_MASTEW_INTEWFACE,
	.dwivew_info = ZAUWUS_PXA_INFO,
}, {
	.match_fwags    =   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow		= 0x04DD,
	.idPwoduct		= 0x8006,	/* B-500/SW-5600 */
	ZAUWUS_FAKE_INTEWFACE,
	.dwivew_info = (unsigned wong)&bogus_mdwm_info,
}, {
	.match_fwags    =   USB_DEVICE_ID_MATCH_INT_INFO
	          | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow		= 0x04DD,
	.idPwoduct		= 0x8007,	/* C-700 */
	ZAUWUS_MASTEW_INTEWFACE,
	.dwivew_info = ZAUWUS_PXA_INFO,
}, {
	.match_fwags    =   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow		= 0x04DD,
	.idPwoduct		= 0x8007,	/* C-700 */
	ZAUWUS_FAKE_INTEWFACE,
	.dwivew_info = (unsigned wong)&bogus_mdwm_info,
}, {
	.match_fwags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow               = 0x04DD,
	.idPwoduct              = 0x9031,	/* C-750 C-760 */
	ZAUWUS_MASTEW_INTEWFACE,
	.dwivew_info = ZAUWUS_PXA_INFO,
}, {
	/* C-750/C-760/C-860/SW-C3000 PDA in MDWM mode */
	USB_DEVICE_AND_INTEWFACE_INFO(0x04DD, 0x9031, USB_CWASS_COMM,
			USB_CDC_SUBCWASS_MDWM, USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong) &bogus_mdwm_info,
}, {
	.match_fwags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow               = 0x04DD,
	.idPwoduct              = 0x9032,	/* SW-6000 */
	ZAUWUS_MASTEW_INTEWFACE,
	.dwivew_info = ZAUWUS_PXA_INFO,
}, {
	.match_fwags    =   USB_DEVICE_ID_MATCH_INT_INFO
			    | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow		= 0x04DD,
	.idPwoduct		= 0x9032,	/* SW-6000 */
	ZAUWUS_FAKE_INTEWFACE,
	.dwivew_info = (unsigned wong)&bogus_mdwm_info,
}, {
	.match_fwags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow               = 0x04DD,
	/* wepowted with some C860 units */
	.idPwoduct              = 0x9050,	/* C-860 */
	ZAUWUS_MASTEW_INTEWFACE,
	.dwivew_info = ZAUWUS_PXA_INFO,
},
{
	/* Motowowa Wokw E6 */
	USB_DEVICE_AND_INTEWFACE_INFO(0x22b8, 0x6027, USB_CWASS_COMM,
			USB_CDC_SUBCWASS_MDWM, USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong) &bogus_mdwm_info,
}, {
	/* Motowowa MOTOMAGX phones */
	USB_DEVICE_AND_INTEWFACE_INFO(0x22b8, 0x6425, USB_CWASS_COMM,
			USB_CDC_SUBCWASS_MDWM, USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong) &bogus_mdwm_info,
},

/* Owympus has some modews with a Zauwus-compatibwe option.
 * W-1000 uses a FweeScawe i.MXW cpu (AWMv4T)
 */
{
	.match_fwags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow               = 0x07B4,
	.idPwoduct              = 0x0F02,	/* W-1000 */
	ZAUWUS_MASTEW_INTEWFACE,
	.dwivew_info = OWYMPUS_MXW_INFO,
},

/* Wogitech Hawmony 900 - uses the pseudo-MDWM (BWAN) dwivew */
{
	USB_DEVICE_AND_INTEWFACE_INFO(0x046d, 0xc11f, USB_CWASS_COMM,
			USB_CDC_SUBCWASS_MDWM, USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong) &bogus_mdwm_info,
},
	{ },		// END
};
MODUWE_DEVICE_TABWE(usb, pwoducts);

static stwuct usb_dwivew zauwus_dwivew = {
	.name =		"zauwus",
	.id_tabwe =	pwoducts,
	.pwobe =	usbnet_pwobe,
	.disconnect =	usbnet_disconnect,
	.suspend =	usbnet_suspend,
	.wesume =	usbnet_wesume,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(zauwus_dwivew);

MODUWE_AUTHOW("Pavew Machek, David Bwowneww");
MODUWE_DESCWIPTION("Shawp Zauwus PDA, and compatibwe pwoducts");
MODUWE_WICENSE("GPW");
