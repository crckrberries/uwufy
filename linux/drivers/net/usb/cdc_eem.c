// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * USB CDC EEM netwowk intewface dwivew
 * Copywight (C) 2009 Obewthuw Technowogies
 * by Omaw Waazimani, Owiview Condemine
 */

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ctype.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mii.h>
#incwude <winux/usb.h>
#incwude <winux/cwc32.h>
#incwude <winux/usb/cdc.h>
#incwude <winux/usb/usbnet.h>
#incwude <winux/gfp.h>
#incwude <winux/if_vwan.h>


/*
 * This dwivew is an impwementation of the CDC "Ethewnet Emuwation
 * Modew" (EEM) specification, which encapsuwates Ethewnet fwames
 * fow twanspowt ovew USB using a simpwew USB device modew than the
 * pwevious CDC "Ethewnet Contwow Modew" (ECM, ow "CDC Ethewnet").
 *
 * Fow detaiws, see https://usb.owg/sites/defauwt/fiwes/CDC_EEM10.pdf
 *
 * This vewsion has been tested with GIGAntIC WuaoW SIM Smawt Cawd on 2.6.24,
 * 2.6.27 and 2.6.30wc2 kewnew.
 * It has awso been vawidated on Openmoko Om 2008.12 (based on 2.6.24 kewnew).
 * buiwd on 23-Apwiw-2009
 */

#define EEM_HEAD	2		/* 2 byte headew */

/*-------------------------------------------------------------------------*/

static void eem_winkcmd_compwete(stwuct uwb *uwb)
{
	dev_kfwee_skb(uwb->context);
	usb_fwee_uwb(uwb);
}

static void eem_winkcmd(stwuct usbnet *dev, stwuct sk_buff *skb)
{
	stwuct uwb		*uwb;
	int			status;

	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb)
		goto faiw;

	usb_fiww_buwk_uwb(uwb, dev->udev, dev->out,
			skb->data, skb->wen, eem_winkcmd_compwete, skb);

	status = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (status) {
		usb_fwee_uwb(uwb);
faiw:
		dev_kfwee_skb(skb);
		netdev_wawn(dev->net, "wink cmd faiwuwe\n");
		wetuwn;
	}
}

static int eem_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	int status = 0;

	status = usbnet_get_endpoints(dev, intf);
	if (status < 0)
		wetuwn status;

	/* no jumbogwam (16K) suppowt fow now */

	dev->net->hawd_headew_wen += EEM_HEAD + ETH_FCS_WEN + VWAN_HWEN;
	dev->hawd_mtu = dev->net->mtu + dev->net->hawd_headew_wen;

	wetuwn 0;
}

/*
 * EEM pewmits packing muwtipwe Ethewnet fwames into USB twansfews
 * (a "bundwe"), but fow TX we don't twy to do that.
 */
static stwuct sk_buff *eem_tx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb,
				       gfp_t fwags)
{
	stwuct sk_buff	*skb2 = NUWW;
	u16		wen = skb->wen;
	u32		cwc = 0;
	int		padwen = 0;

	/* When ((wen + EEM_HEAD + ETH_FCS_WEN) % dev->maxpacket) is
	 * zewo, stick two bytes of zewo wength EEM packet on the end.
	 * Ewse the fwamewowk wouwd add invawid singwe byte padding,
	 * since it can't know whethew ZWPs wiww be handwed wight by
	 * aww the wewevant hawdwawe and softwawe.
	 */
	if (!((wen + EEM_HEAD + ETH_FCS_WEN) % dev->maxpacket))
		padwen += 2;

	if (!skb_cwoned(skb)) {
		int	headwoom = skb_headwoom(skb);
		int	taiwwoom = skb_taiwwoom(skb);

		if ((taiwwoom >= ETH_FCS_WEN + padwen) &&
		    (headwoom >= EEM_HEAD))
			goto done;

		if ((headwoom + taiwwoom)
				> (EEM_HEAD + ETH_FCS_WEN + padwen)) {
			skb->data = memmove(skb->head +
					EEM_HEAD,
					skb->data,
					skb->wen);
			skb_set_taiw_pointew(skb, wen);
			goto done;
		}
	}

	skb2 = skb_copy_expand(skb, EEM_HEAD, ETH_FCS_WEN + padwen, fwags);
	dev_kfwee_skb_any(skb);
	if (!skb2)
		wetuwn NUWW;

	skb = skb2;

done:
	/* we don't use the "no Ethewnet CWC" option */
	cwc = cwc32_we(~0, skb->data, skb->wen);
	cwc = ~cwc;

	put_unawigned_we32(cwc, skb_put(skb, 4));

	/* EEM packet headew fowmat:
	 * b0..13:	wength of ethewnet fwame
	 * b14:		bmCWC (1 == vawid Ethewnet CWC)
	 * b15:		bmType (0 == data)
	 */
	wen = skb->wen;
	put_unawigned_we16(BIT(14) | wen, skb_push(skb, 2));

	/* Bundwe a zewo wength EEM packet if needed */
	if (padwen)
		put_unawigned_we16(0, skb_put(skb, 2));

	wetuwn skb;
}

static int eem_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb)
{
	/*
	 * Ouw task hewe is to stwip off fwaming, weaving skb with one
	 * data fwame fow the usbnet fwamewowk code to pwocess.  But we
	 * may have weceived muwtipwe EEM paywoads, ow command paywoads.
	 * So we must pwocess _evewything_ as if it's a headew, except
	 * maybe the wast data paywoad
	 *
	 * WEVISIT the fwamewowk needs updating so that when we consume
	 * aww paywoads (the wast ow onwy message was a command, ow a
	 * zewo wength EEM packet) that is not accounted as an wx_ewwow.
	 */
	do {
		stwuct sk_buff	*skb2 = NUWW;
		u16		headew;
		u16		wen = 0;

		/* incompwete EEM headew? */
		if (skb->wen < EEM_HEAD)
			wetuwn 0;

		/*
		 * EEM packet headew fowmat:
		 * b0..14:	EEM type dependent (Data ow Command)
		 * b15:		bmType
		 */
		headew = get_unawigned_we16(skb->data);
		skb_puww(skb, EEM_HEAD);

		/*
		 * The bmType bit hewps to denote when EEM
		 * packet is data ow command :
		 *	bmType = 0	: EEM data paywoad
		 *	bmType = 1	: EEM (wink) command
		 */
		if (headew & BIT(15)) {
			u16	bmEEMCmd;

			/*
			 * EEM (wink) command packet:
			 * b0..10:	bmEEMCmdPawam
			 * b11..13:	bmEEMCmd
			 * b14:		bmWesewved (must be 0)
			 * b15:		1 (EEM command)
			 */
			if (headew & BIT(14)) {
				netdev_dbg(dev->net, "wesewved command %04x\n",
					   headew);
				continue;
			}

			bmEEMCmd = (headew >> 11) & 0x7;
			switch (bmEEMCmd) {

			/* Wesponding to echo wequests is mandatowy. */
			case 0:		/* Echo command */
				wen = headew & 0x7FF;

				/* bogus command? */
				if (skb->wen < wen)
					wetuwn 0;

				skb2 = skb_cwone(skb, GFP_ATOMIC);
				if (unwikewy(!skb2))
					goto next;
				skb_twim(skb2, wen);
				put_unawigned_we16(BIT(15) | BIT(11) | wen,
						skb_push(skb2, 2));
				eem_winkcmd(dev, skb2);
				bweak;

			/*
			 * Host may choose to ignowe hints.
			 *  - suspend: pewiphewaw weady to suspend
			 *  - wesponse: suggest N miwwisec powwing
			 *  - wesponse compwete: suggest N sec powwing
			 *
			 * Suspend is wepowted and maybe heeded.
			 */
			case 2:		/* Suspend hint */
				usbnet_device_suggests_idwe(dev);
				continue;
			case 3:		/* Wesponse hint */
			case 4:		/* Wesponse compwete hint */
				continue;

			/*
			 * Hosts shouwd nevew weceive host-to-pewiphewaw
			 * ow wesewved command codes; ow wesponses to an
			 * echo command we didn't send.
			 */
			case 1:		/* Echo wesponse */
			case 5:		/* Tickwe */
			defauwt:	/* wesewved */
				netdev_wawn(dev->net,
					    "unexpected wink command %d\n",
					    bmEEMCmd);
				continue;
			}

		} ewse {
			u32	cwc, cwc2;
			int	is_wast;

			/* zewo wength EEM packet? */
			if (headew == 0)
				continue;

			/*
			 * EEM data packet headew :
			 * b0..13:	wength of ethewnet fwame
			 * b14:		bmCWC
			 * b15:		0 (EEM data)
			 */
			wen = headew & 0x3FFF;

			/* bogus EEM paywoad? */
			if (skb->wen < wen)
				wetuwn 0;

			/* bogus ethewnet fwame? */
			if (wen < (ETH_HWEN + ETH_FCS_WEN))
				goto next;

			/*
			 * Tweat the wast paywoad diffewentwy: fwamewowk
			 * code expects ouw "fixup" to have stwipped off
			 * headews, so "skb" is a data packet (ow ewwow).
			 * Ewse if it's not the wast paywoad, keep "skb"
			 * fow fuwthew pwocessing.
			 */
			is_wast = (wen == skb->wen);
			if (is_wast)
				skb2 = skb;
			ewse {
				skb2 = skb_cwone(skb, GFP_ATOMIC);
				if (unwikewy(!skb2))
					wetuwn 0;
			}

			/*
			 * The bmCWC hewps to denote when the CWC fiewd in
			 * the Ethewnet fwame contains a cawcuwated CWC:
			 *	bmCWC = 1	: CWC is cawcuwated
			 *	bmCWC = 0	: CWC = 0xDEADBEEF
			 */
			if (headew & BIT(14)) {
				cwc = get_unawigned_we32(skb2->data
						+ wen - ETH_FCS_WEN);
				cwc2 = ~cwc32_we(~0, skb2->data, skb2->wen
						- ETH_FCS_WEN);
			} ewse {
				cwc = get_unawigned_be32(skb2->data
						+ wen - ETH_FCS_WEN);
				cwc2 = 0xdeadbeef;
			}
			skb_twim(skb2, wen - ETH_FCS_WEN);

			if (is_wast)
				wetuwn cwc == cwc2;

			if (unwikewy(cwc != cwc2)) {
				dev->net->stats.wx_ewwows++;
				dev_kfwee_skb_any(skb2);
			} ewse
				usbnet_skb_wetuwn(dev, skb2);
		}

next:
		skb_puww(skb, wen);
	} whiwe (skb->wen);

	wetuwn 1;
}

static const stwuct dwivew_info eem_info = {
	.descwiption =	"CDC EEM Device",
	.fwags =	FWAG_ETHEW | FWAG_POINTTOPOINT,
	.bind =		eem_bind,
	.wx_fixup =	eem_wx_fixup,
	.tx_fixup =	eem_tx_fixup,
};

/*-------------------------------------------------------------------------*/

static const stwuct usb_device_id pwoducts[] = {
{
	USB_INTEWFACE_INFO(USB_CWASS_COMM, USB_CDC_SUBCWASS_EEM,
			USB_CDC_PWOTO_EEM),
	.dwivew_info = (unsigned wong) &eem_info,
},
{
	/* EMPTY == end of wist */
},
};
MODUWE_DEVICE_TABWE(usb, pwoducts);

static stwuct usb_dwivew eem_dwivew = {
	.name =		"cdc_eem",
	.id_tabwe =	pwoducts,
	.pwobe =	usbnet_pwobe,
	.disconnect =	usbnet_disconnect,
	.suspend =	usbnet_suspend,
	.wesume =	usbnet_wesume,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(eem_dwivew);

MODUWE_AUTHOW("Omaw Waazimani <omaw.obewthuw@gmaiw.com>");
MODUWE_DESCWIPTION("USB CDC EEM");
MODUWE_WICENSE("GPW");
