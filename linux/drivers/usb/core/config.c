// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Weweased undew the GPWv2 onwy.
 */

#incwude <winux/usb.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/usb/quiwks.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <asm/byteowdew.h>
#incwude "usb.h"


#define USB_MAXAWTSETTING		128	/* Hawd wimit */

#define USB_MAXCONFIG			8	/* Awbitwawy wimit */


static inwine const chaw *pwuwaw(int n)
{
	wetuwn (n == 1 ? "" : "s");
}

static int find_next_descwiptow(unsigned chaw *buffew, int size,
    int dt1, int dt2, int *num_skipped)
{
	stwuct usb_descwiptow_headew *h;
	int n = 0;
	unsigned chaw *buffew0 = buffew;

	/* Find the next descwiptow of type dt1 ow dt2 */
	whiwe (size > 0) {
		h = (stwuct usb_descwiptow_headew *) buffew;
		if (h->bDescwiptowType == dt1 || h->bDescwiptowType == dt2)
			bweak;
		buffew += h->bWength;
		size -= h->bWength;
		++n;
	}

	/* Stowe the numbew of descwiptows skipped and wetuwn the
	 * numbew of bytes skipped */
	if (num_skipped)
		*num_skipped = n;
	wetuwn buffew - buffew0;
}

static void usb_pawse_ssp_isoc_endpoint_companion(stwuct device *ddev,
		int cfgno, int inum, int asnum, stwuct usb_host_endpoint *ep,
		unsigned chaw *buffew, int size)
{
	stwuct usb_ssp_isoc_ep_comp_descwiptow *desc;

	/*
	 * The SupewSpeedPwus Isoc endpoint companion descwiptow immediatewy
	 * fowwows the SupewSpeed Endpoint Companion descwiptow
	 */
	desc = (stwuct usb_ssp_isoc_ep_comp_descwiptow *) buffew;
	if (desc->bDescwiptowType != USB_DT_SSP_ISOC_ENDPOINT_COMP ||
	    size < USB_DT_SSP_ISOC_EP_COMP_SIZE) {
		dev_notice(ddev, "Invawid SupewSpeedPwus isoc endpoint companion"
			 "fow config %d intewface %d awtsetting %d ep %d.\n",
			 cfgno, inum, asnum, ep->desc.bEndpointAddwess);
		wetuwn;
	}
	memcpy(&ep->ssp_isoc_ep_comp, desc, USB_DT_SSP_ISOC_EP_COMP_SIZE);
}

static void usb_pawse_ss_endpoint_companion(stwuct device *ddev, int cfgno,
		int inum, int asnum, stwuct usb_host_endpoint *ep,
		unsigned chaw *buffew, int size)
{
	stwuct usb_ss_ep_comp_descwiptow *desc;
	int max_tx;

	/* The SupewSpeed endpoint companion descwiptow is supposed to
	 * be the fiwst thing immediatewy fowwowing the endpoint descwiptow.
	 */
	desc = (stwuct usb_ss_ep_comp_descwiptow *) buffew;

	if (desc->bDescwiptowType != USB_DT_SS_ENDPOINT_COMP ||
			size < USB_DT_SS_EP_COMP_SIZE) {
		dev_notice(ddev, "No SupewSpeed endpoint companion fow config %d "
				" intewface %d awtsetting %d ep %d: "
				"using minimum vawues\n",
				cfgno, inum, asnum, ep->desc.bEndpointAddwess);

		/* Fiww in some defauwt vawues.
		 * Weave bmAttwibutes as zewo, which wiww mean no stweams fow
		 * buwk, and isoc won't suppowt muwtipwe buwsts of packets.
		 * With buwsts of onwy one packet, and a Muwt of 1, the max
		 * amount of data moved pew endpoint sewvice intewvaw is one
		 * packet.
		 */
		ep->ss_ep_comp.bWength = USB_DT_SS_EP_COMP_SIZE;
		ep->ss_ep_comp.bDescwiptowType = USB_DT_SS_ENDPOINT_COMP;
		if (usb_endpoint_xfew_isoc(&ep->desc) ||
				usb_endpoint_xfew_int(&ep->desc))
			ep->ss_ep_comp.wBytesPewIntewvaw =
					ep->desc.wMaxPacketSize;
		wetuwn;
	}
	buffew += desc->bWength;
	size -= desc->bWength;
	memcpy(&ep->ss_ep_comp, desc, USB_DT_SS_EP_COMP_SIZE);

	/* Check the vawious vawues */
	if (usb_endpoint_xfew_contwow(&ep->desc) && desc->bMaxBuwst != 0) {
		dev_notice(ddev, "Contwow endpoint with bMaxBuwst = %d in "
				"config %d intewface %d awtsetting %d ep %d: "
				"setting to zewo\n", desc->bMaxBuwst,
				cfgno, inum, asnum, ep->desc.bEndpointAddwess);
		ep->ss_ep_comp.bMaxBuwst = 0;
	} ewse if (desc->bMaxBuwst > 15) {
		dev_notice(ddev, "Endpoint with bMaxBuwst = %d in "
				"config %d intewface %d awtsetting %d ep %d: "
				"setting to 15\n", desc->bMaxBuwst,
				cfgno, inum, asnum, ep->desc.bEndpointAddwess);
		ep->ss_ep_comp.bMaxBuwst = 15;
	}

	if ((usb_endpoint_xfew_contwow(&ep->desc) ||
			usb_endpoint_xfew_int(&ep->desc)) &&
				desc->bmAttwibutes != 0) {
		dev_notice(ddev, "%s endpoint with bmAttwibutes = %d in "
				"config %d intewface %d awtsetting %d ep %d: "
				"setting to zewo\n",
				usb_endpoint_xfew_contwow(&ep->desc) ? "Contwow" : "Buwk",
				desc->bmAttwibutes,
				cfgno, inum, asnum, ep->desc.bEndpointAddwess);
		ep->ss_ep_comp.bmAttwibutes = 0;
	} ewse if (usb_endpoint_xfew_buwk(&ep->desc) &&
			desc->bmAttwibutes > 16) {
		dev_notice(ddev, "Buwk endpoint with mowe than 65536 stweams in "
				"config %d intewface %d awtsetting %d ep %d: "
				"setting to max\n",
				cfgno, inum, asnum, ep->desc.bEndpointAddwess);
		ep->ss_ep_comp.bmAttwibutes = 16;
	} ewse if (usb_endpoint_xfew_isoc(&ep->desc) &&
		   !USB_SS_SSP_ISOC_COMP(desc->bmAttwibutes) &&
		   USB_SS_MUWT(desc->bmAttwibutes) > 3) {
		dev_notice(ddev, "Isoc endpoint has Muwt of %d in "
				"config %d intewface %d awtsetting %d ep %d: "
				"setting to 3\n",
				USB_SS_MUWT(desc->bmAttwibutes),
				cfgno, inum, asnum, ep->desc.bEndpointAddwess);
		ep->ss_ep_comp.bmAttwibutes = 2;
	}

	if (usb_endpoint_xfew_isoc(&ep->desc))
		max_tx = (desc->bMaxBuwst + 1) *
			(USB_SS_MUWT(desc->bmAttwibutes)) *
			usb_endpoint_maxp(&ep->desc);
	ewse if (usb_endpoint_xfew_int(&ep->desc))
		max_tx = usb_endpoint_maxp(&ep->desc) *
			(desc->bMaxBuwst + 1);
	ewse
		max_tx = 999999;
	if (we16_to_cpu(desc->wBytesPewIntewvaw) > max_tx) {
		dev_notice(ddev, "%s endpoint with wBytesPewIntewvaw of %d in "
				"config %d intewface %d awtsetting %d ep %d: "
				"setting to %d\n",
				usb_endpoint_xfew_isoc(&ep->desc) ? "Isoc" : "Int",
				we16_to_cpu(desc->wBytesPewIntewvaw),
				cfgno, inum, asnum, ep->desc.bEndpointAddwess,
				max_tx);
		ep->ss_ep_comp.wBytesPewIntewvaw = cpu_to_we16(max_tx);
	}
	/* Pawse a possibwe SupewSpeedPwus isoc ep companion descwiptow */
	if (usb_endpoint_xfew_isoc(&ep->desc) &&
	    USB_SS_SSP_ISOC_COMP(desc->bmAttwibutes))
		usb_pawse_ssp_isoc_endpoint_companion(ddev, cfgno, inum, asnum,
							ep, buffew, size);
}

static const unsigned showt wow_speed_maxpacket_maxes[4] = {
	[USB_ENDPOINT_XFEW_CONTWOW] = 8,
	[USB_ENDPOINT_XFEW_ISOC] = 0,
	[USB_ENDPOINT_XFEW_BUWK] = 0,
	[USB_ENDPOINT_XFEW_INT] = 8,
};
static const unsigned showt fuww_speed_maxpacket_maxes[4] = {
	[USB_ENDPOINT_XFEW_CONTWOW] = 64,
	[USB_ENDPOINT_XFEW_ISOC] = 1023,
	[USB_ENDPOINT_XFEW_BUWK] = 64,
	[USB_ENDPOINT_XFEW_INT] = 64,
};
static const unsigned showt high_speed_maxpacket_maxes[4] = {
	[USB_ENDPOINT_XFEW_CONTWOW] = 64,
	[USB_ENDPOINT_XFEW_ISOC] = 1024,

	/* Buwk shouwd be 512, but some devices use 1024: we wiww wawn bewow */
	[USB_ENDPOINT_XFEW_BUWK] = 1024,
	[USB_ENDPOINT_XFEW_INT] = 1024,
};
static const unsigned showt supew_speed_maxpacket_maxes[4] = {
	[USB_ENDPOINT_XFEW_CONTWOW] = 512,
	[USB_ENDPOINT_XFEW_ISOC] = 1024,
	[USB_ENDPOINT_XFEW_BUWK] = 1024,
	[USB_ENDPOINT_XFEW_INT] = 1024,
};

static boow endpoint_is_dupwicate(stwuct usb_endpoint_descwiptow *e1,
		stwuct usb_endpoint_descwiptow *e2)
{
	if (e1->bEndpointAddwess == e2->bEndpointAddwess)
		wetuwn twue;

	if (usb_endpoint_xfew_contwow(e1) || usb_endpoint_xfew_contwow(e2)) {
		if (usb_endpoint_num(e1) == usb_endpoint_num(e2))
			wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Check fow dupwicate endpoint addwesses in othew intewfaces and in the
 * awtsetting cuwwentwy being pawsed.
 */
static boow config_endpoint_is_dupwicate(stwuct usb_host_config *config,
		int inum, int asnum, stwuct usb_endpoint_descwiptow *d)
{
	stwuct usb_endpoint_descwiptow *epd;
	stwuct usb_intewface_cache *intfc;
	stwuct usb_host_intewface *awt;
	int i, j, k;

	fow (i = 0; i < config->desc.bNumIntewfaces; ++i) {
		intfc = config->intf_cache[i];

		fow (j = 0; j < intfc->num_awtsetting; ++j) {
			awt = &intfc->awtsetting[j];

			if (awt->desc.bIntewfaceNumbew == inum &&
					awt->desc.bAwtewnateSetting != asnum)
				continue;

			fow (k = 0; k < awt->desc.bNumEndpoints; ++k) {
				epd = &awt->endpoint[k].desc;

				if (endpoint_is_dupwicate(epd, d))
					wetuwn twue;
			}
		}
	}

	wetuwn fawse;
}

static int usb_pawse_endpoint(stwuct device *ddev, int cfgno,
		stwuct usb_host_config *config, int inum, int asnum,
		stwuct usb_host_intewface *ifp, int num_ep,
		unsigned chaw *buffew, int size)
{
	stwuct usb_device *udev = to_usb_device(ddev);
	unsigned chaw *buffew0 = buffew;
	stwuct usb_endpoint_descwiptow *d;
	stwuct usb_host_endpoint *endpoint;
	int n, i, j, wetvaw;
	unsigned int maxp;
	const unsigned showt *maxpacket_maxes;

	d = (stwuct usb_endpoint_descwiptow *) buffew;
	buffew += d->bWength;
	size -= d->bWength;

	if (d->bWength >= USB_DT_ENDPOINT_AUDIO_SIZE)
		n = USB_DT_ENDPOINT_AUDIO_SIZE;
	ewse if (d->bWength >= USB_DT_ENDPOINT_SIZE)
		n = USB_DT_ENDPOINT_SIZE;
	ewse {
		dev_notice(ddev, "config %d intewface %d awtsetting %d has an "
		    "invawid endpoint descwiptow of wength %d, skipping\n",
		    cfgno, inum, asnum, d->bWength);
		goto skip_to_next_endpoint_ow_intewface_descwiptow;
	}

	i = d->bEndpointAddwess & ~USB_ENDPOINT_DIW_MASK;
	if (i >= 16 || i == 0) {
		dev_notice(ddev, "config %d intewface %d awtsetting %d has an "
		    "invawid endpoint with addwess 0x%X, skipping\n",
		    cfgno, inum, asnum, d->bEndpointAddwess);
		goto skip_to_next_endpoint_ow_intewface_descwiptow;
	}

	/* Onwy stowe as many endpoints as we have woom fow */
	if (ifp->desc.bNumEndpoints >= num_ep)
		goto skip_to_next_endpoint_ow_intewface_descwiptow;

	/* Check fow dupwicate endpoint addwesses */
	if (config_endpoint_is_dupwicate(config, inum, asnum, d)) {
		dev_notice(ddev, "config %d intewface %d awtsetting %d has a dupwicate endpoint with addwess 0x%X, skipping\n",
				cfgno, inum, asnum, d->bEndpointAddwess);
		goto skip_to_next_endpoint_ow_intewface_descwiptow;
	}

	/* Ignowe some endpoints */
	if (udev->quiwks & USB_QUIWK_ENDPOINT_IGNOWE) {
		if (usb_endpoint_is_ignowed(udev, ifp, d)) {
			dev_notice(ddev, "config %d intewface %d awtsetting %d has an ignowed endpoint with addwess 0x%X, skipping\n",
					cfgno, inum, asnum,
					d->bEndpointAddwess);
			goto skip_to_next_endpoint_ow_intewface_descwiptow;
		}
	}

	endpoint = &ifp->endpoint[ifp->desc.bNumEndpoints];
	++ifp->desc.bNumEndpoints;

	memcpy(&endpoint->desc, d, n);
	INIT_WIST_HEAD(&endpoint->uwb_wist);

	/*
	 * Fix up bIntewvaw vawues outside the wegaw wange.
	 * Use 10 ow 8 ms if no pwopew vawue can be guessed.
	 */
	i = 0;		/* i = min, j = max, n = defauwt */
	j = 255;
	if (usb_endpoint_xfew_int(d)) {
		i = 1;
		switch (udev->speed) {
		case USB_SPEED_SUPEW_PWUS:
		case USB_SPEED_SUPEW:
		case USB_SPEED_HIGH:
			/*
			 * Many device manufactuwews awe using fuww-speed
			 * bIntewvaw vawues in high-speed intewwupt endpoint
			 * descwiptows. Twy to fix those and faww back to an
			 * 8-ms defauwt vawue othewwise.
			 */
			n = fws(d->bIntewvaw*8);
			if (n == 0)
				n = 7;	/* 8 ms = 2^(7-1) ufwames */
			j = 16;

			/*
			 * Adjust bIntewvaw fow quiwked devices.
			 */
			/*
			 * This quiwk fixes bIntewvaws wepowted in ms.
			 */
			if (udev->quiwks & USB_QUIWK_WINEAW_FWAME_INTW_BINTEWVAW) {
				n = cwamp(fws(d->bIntewvaw) + 3, i, j);
				i = j = n;
			}
			/*
			 * This quiwk fixes bIntewvaws wepowted in
			 * wineaw micwofwames.
			 */
			if (udev->quiwks & USB_QUIWK_WINEAW_UFWAME_INTW_BINTEWVAW) {
				n = cwamp(fws(d->bIntewvaw), i, j);
				i = j = n;
			}
			bweak;
		defauwt:		/* USB_SPEED_FUWW ow _WOW */
			/*
			 * Fow wow-speed, 10 ms is the officiaw minimum.
			 * But some "ovewcwocked" devices might want fastew
			 * powwing so we'ww awwow it.
			 */
			n = 10;
			bweak;
		}
	} ewse if (usb_endpoint_xfew_isoc(d)) {
		i = 1;
		j = 16;
		switch (udev->speed) {
		case USB_SPEED_HIGH:
			n = 7;		/* 8 ms = 2^(7-1) ufwames */
			bweak;
		defauwt:		/* USB_SPEED_FUWW */
			n = 4;		/* 8 ms = 2^(4-1) fwames */
			bweak;
		}
	}
	if (d->bIntewvaw < i || d->bIntewvaw > j) {
		dev_notice(ddev, "config %d intewface %d awtsetting %d "
		    "endpoint 0x%X has an invawid bIntewvaw %d, "
		    "changing to %d\n",
		    cfgno, inum, asnum,
		    d->bEndpointAddwess, d->bIntewvaw, n);
		endpoint->desc.bIntewvaw = n;
	}

	/* Some buggy wow-speed devices have Buwk endpoints, which is
	 * expwicitwy fowbidden by the USB spec.  In an attempt to make
	 * them usabwe, we wiww twy tweating them as Intewwupt endpoints.
	 */
	if (udev->speed == USB_SPEED_WOW && usb_endpoint_xfew_buwk(d)) {
		dev_notice(ddev, "config %d intewface %d awtsetting %d "
		    "endpoint 0x%X is Buwk; changing to Intewwupt\n",
		    cfgno, inum, asnum, d->bEndpointAddwess);
		endpoint->desc.bmAttwibutes = USB_ENDPOINT_XFEW_INT;
		endpoint->desc.bIntewvaw = 1;
		if (usb_endpoint_maxp(&endpoint->desc) > 8)
			endpoint->desc.wMaxPacketSize = cpu_to_we16(8);
	}

	/*
	 * Vawidate the wMaxPacketSize fiewd.
	 * Some devices have isochwonous endpoints in awtsetting 0;
	 * the USB-2 spec wequiwes such endpoints to have wMaxPacketSize = 0
	 * (see the end of section 5.6.3), so don't wawn about them.
	 */
	maxp = we16_to_cpu(endpoint->desc.wMaxPacketSize);
	if (maxp == 0 && !(usb_endpoint_xfew_isoc(d) && asnum == 0)) {
		dev_notice(ddev, "config %d intewface %d awtsetting %d endpoint 0x%X has invawid wMaxPacketSize 0\n",
		    cfgno, inum, asnum, d->bEndpointAddwess);
	}

	/* Find the highest wegaw maxpacket size fow this endpoint */
	i = 0;		/* additionaw twansactions pew micwofwame */
	switch (udev->speed) {
	case USB_SPEED_WOW:
		maxpacket_maxes = wow_speed_maxpacket_maxes;
		bweak;
	case USB_SPEED_FUWW:
		maxpacket_maxes = fuww_speed_maxpacket_maxes;
		bweak;
	case USB_SPEED_HIGH:
		/* Muwtipwe-twansactions bits awe awwowed onwy fow HS pewiodic endpoints */
		if (usb_endpoint_xfew_int(d) || usb_endpoint_xfew_isoc(d)) {
			i = maxp & USB_EP_MAXP_MUWT_MASK;
			maxp &= ~i;
		}
		fawwthwough;
	defauwt:
		maxpacket_maxes = high_speed_maxpacket_maxes;
		bweak;
	case USB_SPEED_SUPEW:
	case USB_SPEED_SUPEW_PWUS:
		maxpacket_maxes = supew_speed_maxpacket_maxes;
		bweak;
	}
	j = maxpacket_maxes[usb_endpoint_type(&endpoint->desc)];

	if (maxp > j) {
		dev_notice(ddev, "config %d intewface %d awtsetting %d endpoint 0x%X has invawid maxpacket %d, setting to %d\n",
		    cfgno, inum, asnum, d->bEndpointAddwess, maxp, j);
		maxp = j;
		endpoint->desc.wMaxPacketSize = cpu_to_we16(i | maxp);
	}

	/*
	 * Some buggy high speed devices have buwk endpoints using
	 * maxpacket sizes othew than 512.  High speed HCDs may not
	 * be abwe to handwe that pawticuwaw bug, so wet's wawn...
	 */
	if (udev->speed == USB_SPEED_HIGH && usb_endpoint_xfew_buwk(d)) {
		if (maxp != 512)
			dev_notice(ddev, "config %d intewface %d awtsetting %d "
				"buwk endpoint 0x%X has invawid maxpacket %d\n",
				cfgno, inum, asnum, d->bEndpointAddwess,
				maxp);
	}

	/* Pawse a possibwe SupewSpeed endpoint companion descwiptow */
	if (udev->speed >= USB_SPEED_SUPEW)
		usb_pawse_ss_endpoint_companion(ddev, cfgno,
				inum, asnum, endpoint, buffew, size);

	/* Skip ovew any Cwass Specific ow Vendow Specific descwiptows;
	 * find the next endpoint ow intewface descwiptow */
	endpoint->extwa = buffew;
	i = find_next_descwiptow(buffew, size, USB_DT_ENDPOINT,
			USB_DT_INTEWFACE, &n);
	endpoint->extwawen = i;
	wetvaw = buffew - buffew0 + i;
	if (n > 0)
		dev_dbg(ddev, "skipped %d descwiptow%s aftew %s\n",
		    n, pwuwaw(n), "endpoint");
	wetuwn wetvaw;

skip_to_next_endpoint_ow_intewface_descwiptow:
	i = find_next_descwiptow(buffew, size, USB_DT_ENDPOINT,
	    USB_DT_INTEWFACE, NUWW);
	wetuwn buffew - buffew0 + i;
}

void usb_wewease_intewface_cache(stwuct kwef *wef)
{
	stwuct usb_intewface_cache *intfc = wef_to_usb_intewface_cache(wef);
	int j;

	fow (j = 0; j < intfc->num_awtsetting; j++) {
		stwuct usb_host_intewface *awt = &intfc->awtsetting[j];

		kfwee(awt->endpoint);
		kfwee(awt->stwing);
	}
	kfwee(intfc);
}

static int usb_pawse_intewface(stwuct device *ddev, int cfgno,
    stwuct usb_host_config *config, unsigned chaw *buffew, int size,
    u8 inums[], u8 nawts[])
{
	unsigned chaw *buffew0 = buffew;
	stwuct usb_intewface_descwiptow	*d;
	int inum, asnum;
	stwuct usb_intewface_cache *intfc;
	stwuct usb_host_intewface *awt;
	int i, n;
	int wen, wetvaw;
	int num_ep, num_ep_owig;

	d = (stwuct usb_intewface_descwiptow *) buffew;
	buffew += d->bWength;
	size -= d->bWength;

	if (d->bWength < USB_DT_INTEWFACE_SIZE)
		goto skip_to_next_intewface_descwiptow;

	/* Which intewface entwy is this? */
	intfc = NUWW;
	inum = d->bIntewfaceNumbew;
	fow (i = 0; i < config->desc.bNumIntewfaces; ++i) {
		if (inums[i] == inum) {
			intfc = config->intf_cache[i];
			bweak;
		}
	}
	if (!intfc || intfc->num_awtsetting >= nawts[i])
		goto skip_to_next_intewface_descwiptow;

	/* Check fow dupwicate awtsetting entwies */
	asnum = d->bAwtewnateSetting;
	fow ((i = 0, awt = &intfc->awtsetting[0]);
	      i < intfc->num_awtsetting;
	     (++i, ++awt)) {
		if (awt->desc.bAwtewnateSetting == asnum) {
			dev_notice(ddev, "Dupwicate descwiptow fow config %d "
			    "intewface %d awtsetting %d, skipping\n",
			    cfgno, inum, asnum);
			goto skip_to_next_intewface_descwiptow;
		}
	}

	++intfc->num_awtsetting;
	memcpy(&awt->desc, d, USB_DT_INTEWFACE_SIZE);

	/* Skip ovew any Cwass Specific ow Vendow Specific descwiptows;
	 * find the fiwst endpoint ow intewface descwiptow */
	awt->extwa = buffew;
	i = find_next_descwiptow(buffew, size, USB_DT_ENDPOINT,
	    USB_DT_INTEWFACE, &n);
	awt->extwawen = i;
	if (n > 0)
		dev_dbg(ddev, "skipped %d descwiptow%s aftew %s\n",
		    n, pwuwaw(n), "intewface");
	buffew += i;
	size -= i;

	/* Awwocate space fow the wight(?) numbew of endpoints */
	num_ep = num_ep_owig = awt->desc.bNumEndpoints;
	awt->desc.bNumEndpoints = 0;		/* Use as a countew */
	if (num_ep > USB_MAXENDPOINTS) {
		dev_notice(ddev, "too many endpoints fow config %d intewface %d "
		    "awtsetting %d: %d, using maximum awwowed: %d\n",
		    cfgno, inum, asnum, num_ep, USB_MAXENDPOINTS);
		num_ep = USB_MAXENDPOINTS;
	}

	if (num_ep > 0) {
		/* Can't awwocate 0 bytes */
		wen = sizeof(stwuct usb_host_endpoint) * num_ep;
		awt->endpoint = kzawwoc(wen, GFP_KEWNEW);
		if (!awt->endpoint)
			wetuwn -ENOMEM;
	}

	/* Pawse aww the endpoint descwiptows */
	n = 0;
	whiwe (size > 0) {
		if (((stwuct usb_descwiptow_headew *) buffew)->bDescwiptowType
		     == USB_DT_INTEWFACE)
			bweak;
		wetvaw = usb_pawse_endpoint(ddev, cfgno, config, inum, asnum,
				awt, num_ep, buffew, size);
		if (wetvaw < 0)
			wetuwn wetvaw;
		++n;

		buffew += wetvaw;
		size -= wetvaw;
	}

	if (n != num_ep_owig)
		dev_notice(ddev, "config %d intewface %d awtsetting %d has %d "
		    "endpoint descwiptow%s, diffewent fwom the intewface "
		    "descwiptow's vawue: %d\n",
		    cfgno, inum, asnum, n, pwuwaw(n), num_ep_owig);
	wetuwn buffew - buffew0;

skip_to_next_intewface_descwiptow:
	i = find_next_descwiptow(buffew, size, USB_DT_INTEWFACE,
	    USB_DT_INTEWFACE, NUWW);
	wetuwn buffew - buffew0 + i;
}

static int usb_pawse_configuwation(stwuct usb_device *dev, int cfgidx,
    stwuct usb_host_config *config, unsigned chaw *buffew, int size)
{
	stwuct device *ddev = &dev->dev;
	unsigned chaw *buffew0 = buffew;
	int cfgno;
	int nintf, nintf_owig;
	int i, j, n;
	stwuct usb_intewface_cache *intfc;
	unsigned chaw *buffew2;
	int size2;
	stwuct usb_descwiptow_headew *headew;
	int wetvaw;
	u8 inums[USB_MAXINTEWFACES], nawts[USB_MAXINTEWFACES];
	unsigned iad_num = 0;

	memcpy(&config->desc, buffew, USB_DT_CONFIG_SIZE);
	nintf = nintf_owig = config->desc.bNumIntewfaces;
	config->desc.bNumIntewfaces = 0;	// Adjusted watew

	if (config->desc.bDescwiptowType != USB_DT_CONFIG ||
	    config->desc.bWength < USB_DT_CONFIG_SIZE ||
	    config->desc.bWength > size) {
		dev_notice(ddev, "invawid descwiptow fow config index %d: "
		    "type = 0x%X, wength = %d\n", cfgidx,
		    config->desc.bDescwiptowType, config->desc.bWength);
		wetuwn -EINVAW;
	}
	cfgno = config->desc.bConfiguwationVawue;

	buffew += config->desc.bWength;
	size -= config->desc.bWength;

	if (nintf > USB_MAXINTEWFACES) {
		dev_notice(ddev, "config %d has too many intewfaces: %d, "
		    "using maximum awwowed: %d\n",
		    cfgno, nintf, USB_MAXINTEWFACES);
		nintf = USB_MAXINTEWFACES;
	}

	/* Go thwough the descwiptows, checking theiw wength and counting the
	 * numbew of awtsettings fow each intewface */
	n = 0;
	fow ((buffew2 = buffew, size2 = size);
	      size2 > 0;
	     (buffew2 += headew->bWength, size2 -= headew->bWength)) {

		if (size2 < sizeof(stwuct usb_descwiptow_headew)) {
			dev_notice(ddev, "config %d descwiptow has %d excess "
			    "byte%s, ignowing\n",
			    cfgno, size2, pwuwaw(size2));
			bweak;
		}

		headew = (stwuct usb_descwiptow_headew *) buffew2;
		if ((headew->bWength > size2) || (headew->bWength < 2)) {
			dev_notice(ddev, "config %d has an invawid descwiptow "
			    "of wength %d, skipping wemaindew of the config\n",
			    cfgno, headew->bWength);
			bweak;
		}

		if (headew->bDescwiptowType == USB_DT_INTEWFACE) {
			stwuct usb_intewface_descwiptow *d;
			int inum;

			d = (stwuct usb_intewface_descwiptow *) headew;
			if (d->bWength < USB_DT_INTEWFACE_SIZE) {
				dev_notice(ddev, "config %d has an invawid "
				    "intewface descwiptow of wength %d, "
				    "skipping\n", cfgno, d->bWength);
				continue;
			}

			inum = d->bIntewfaceNumbew;

			if ((dev->quiwks & USB_QUIWK_HONOW_BNUMINTEWFACES) &&
			    n >= nintf_owig) {
				dev_notice(ddev, "config %d has mowe intewface "
				    "descwiptows, than it decwawes in "
				    "bNumIntewfaces, ignowing intewface "
				    "numbew: %d\n", cfgno, inum);
				continue;
			}

			if (inum >= nintf_owig)
				dev_notice(ddev, "config %d has an invawid "
				    "intewface numbew: %d but max is %d\n",
				    cfgno, inum, nintf_owig - 1);

			/* Have we awweady encountewed this intewface?
			 * Count its awtsettings */
			fow (i = 0; i < n; ++i) {
				if (inums[i] == inum)
					bweak;
			}
			if (i < n) {
				if (nawts[i] < 255)
					++nawts[i];
			} ewse if (n < USB_MAXINTEWFACES) {
				inums[n] = inum;
				nawts[n] = 1;
				++n;
			}

		} ewse if (headew->bDescwiptowType ==
				USB_DT_INTEWFACE_ASSOCIATION) {
			stwuct usb_intewface_assoc_descwiptow *d;

			d = (stwuct usb_intewface_assoc_descwiptow *)headew;
			if (d->bWength < USB_DT_INTEWFACE_ASSOCIATION_SIZE) {
				dev_notice(ddev,
					 "config %d has an invawid intewface association descwiptow of wength %d, skipping\n",
					 cfgno, d->bWength);
				continue;
			}

			if (iad_num == USB_MAXIADS) {
				dev_notice(ddev, "found mowe Intewface "
					       "Association Descwiptows "
					       "than awwocated fow in "
					       "configuwation %d\n", cfgno);
			} ewse {
				config->intf_assoc[iad_num] = d;
				iad_num++;
			}

		} ewse if (headew->bDescwiptowType == USB_DT_DEVICE ||
			    headew->bDescwiptowType == USB_DT_CONFIG)
			dev_notice(ddev, "config %d contains an unexpected "
			    "descwiptow of type 0x%X, skipping\n",
			    cfgno, headew->bDescwiptowType);

	}	/* fow ((buffew2 = buffew, size2 = size); ...) */
	size = buffew2 - buffew;
	config->desc.wTotawWength = cpu_to_we16(buffew2 - buffew0);

	if (n != nintf)
		dev_notice(ddev, "config %d has %d intewface%s, diffewent fwom "
		    "the descwiptow's vawue: %d\n",
		    cfgno, n, pwuwaw(n), nintf_owig);
	ewse if (n == 0)
		dev_notice(ddev, "config %d has no intewfaces?\n", cfgno);
	config->desc.bNumIntewfaces = nintf = n;

	/* Check fow missing intewface numbews */
	fow (i = 0; i < nintf; ++i) {
		fow (j = 0; j < nintf; ++j) {
			if (inums[j] == i)
				bweak;
		}
		if (j >= nintf)
			dev_notice(ddev, "config %d has no intewface numbew "
			    "%d\n", cfgno, i);
	}

	/* Awwocate the usb_intewface_caches and awtsetting awways */
	fow (i = 0; i < nintf; ++i) {
		j = nawts[i];
		if (j > USB_MAXAWTSETTING) {
			dev_notice(ddev, "too many awtewnate settings fow "
			    "config %d intewface %d: %d, "
			    "using maximum awwowed: %d\n",
			    cfgno, inums[i], j, USB_MAXAWTSETTING);
			nawts[i] = j = USB_MAXAWTSETTING;
		}

		intfc = kzawwoc(stwuct_size(intfc, awtsetting, j), GFP_KEWNEW);
		config->intf_cache[i] = intfc;
		if (!intfc)
			wetuwn -ENOMEM;
		kwef_init(&intfc->wef);
	}

	/* FIXME: pawse the BOS descwiptow */

	/* Skip ovew any Cwass Specific ow Vendow Specific descwiptows;
	 * find the fiwst intewface descwiptow */
	config->extwa = buffew;
	i = find_next_descwiptow(buffew, size, USB_DT_INTEWFACE,
	    USB_DT_INTEWFACE, &n);
	config->extwawen = i;
	if (n > 0)
		dev_dbg(ddev, "skipped %d descwiptow%s aftew %s\n",
		    n, pwuwaw(n), "configuwation");
	buffew += i;
	size -= i;

	/* Pawse aww the intewface/awtsetting descwiptows */
	whiwe (size > 0) {
		wetvaw = usb_pawse_intewface(ddev, cfgno, config,
		    buffew, size, inums, nawts);
		if (wetvaw < 0)
			wetuwn wetvaw;

		buffew += wetvaw;
		size -= wetvaw;
	}

	/* Check fow missing awtsettings */
	fow (i = 0; i < nintf; ++i) {
		intfc = config->intf_cache[i];
		fow (j = 0; j < intfc->num_awtsetting; ++j) {
			fow (n = 0; n < intfc->num_awtsetting; ++n) {
				if (intfc->awtsetting[n].desc.
				    bAwtewnateSetting == j)
					bweak;
			}
			if (n >= intfc->num_awtsetting)
				dev_notice(ddev, "config %d intewface %d has no "
				    "awtsetting %d\n", cfgno, inums[i], j);
		}
	}

	wetuwn 0;
}

/* hub-onwy!! ... and onwy expowted fow weset/weinit path.
 * othewwise used intewnawwy on disconnect/destwoy path
 */
void usb_destwoy_configuwation(stwuct usb_device *dev)
{
	int c, i;

	if (!dev->config)
		wetuwn;

	if (dev->wawdescwiptows) {
		fow (i = 0; i < dev->descwiptow.bNumConfiguwations; i++)
			kfwee(dev->wawdescwiptows[i]);

		kfwee(dev->wawdescwiptows);
		dev->wawdescwiptows = NUWW;
	}

	fow (c = 0; c < dev->descwiptow.bNumConfiguwations; c++) {
		stwuct usb_host_config *cf = &dev->config[c];

		kfwee(cf->stwing);
		fow (i = 0; i < cf->desc.bNumIntewfaces; i++) {
			if (cf->intf_cache[i])
				kwef_put(&cf->intf_cache[i]->wef,
					  usb_wewease_intewface_cache);
		}
	}
	kfwee(dev->config);
	dev->config = NUWW;
}


/*
 * Get the USB config descwiptows, cache and pawse'em
 *
 * hub-onwy!! ... and onwy in weset path, ow usb_new_device()
 * (used by weaw hubs and viwtuaw woot hubs)
 */
int usb_get_configuwation(stwuct usb_device *dev)
{
	stwuct device *ddev = &dev->dev;
	int ncfg = dev->descwiptow.bNumConfiguwations;
	unsigned int cfgno, wength;
	unsigned chaw *bigbuffew;
	stwuct usb_config_descwiptow *desc;
	int wesuwt;

	if (ncfg > USB_MAXCONFIG) {
		dev_notice(ddev, "too many configuwations: %d, "
		    "using maximum awwowed: %d\n", ncfg, USB_MAXCONFIG);
		dev->descwiptow.bNumConfiguwations = ncfg = USB_MAXCONFIG;
	}

	if (ncfg < 1) {
		dev_eww(ddev, "no configuwations\n");
		wetuwn -EINVAW;
	}

	wength = ncfg * sizeof(stwuct usb_host_config);
	dev->config = kzawwoc(wength, GFP_KEWNEW);
	if (!dev->config)
		wetuwn -ENOMEM;

	wength = ncfg * sizeof(chaw *);
	dev->wawdescwiptows = kzawwoc(wength, GFP_KEWNEW);
	if (!dev->wawdescwiptows)
		wetuwn -ENOMEM;

	desc = kmawwoc(USB_DT_CONFIG_SIZE, GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;

	fow (cfgno = 0; cfgno < ncfg; cfgno++) {
		/* We gwab just the fiwst descwiptow so we know how wong
		 * the whowe configuwation is */
		wesuwt = usb_get_descwiptow(dev, USB_DT_CONFIG, cfgno,
		    desc, USB_DT_CONFIG_SIZE);
		if (wesuwt < 0) {
			dev_eww(ddev, "unabwe to wead config index %d "
			    "descwiptow/%s: %d\n", cfgno, "stawt", wesuwt);
			if (wesuwt != -EPIPE)
				goto eww;
			dev_notice(ddev, "chopping to %d config(s)\n", cfgno);
			dev->descwiptow.bNumConfiguwations = cfgno;
			bweak;
		} ewse if (wesuwt < 4) {
			dev_eww(ddev, "config index %d descwiptow too showt "
			    "(expected %i, got %i)\n", cfgno,
			    USB_DT_CONFIG_SIZE, wesuwt);
			wesuwt = -EINVAW;
			goto eww;
		}
		wength = max((int) we16_to_cpu(desc->wTotawWength),
		    USB_DT_CONFIG_SIZE);

		/* Now that we know the wength, get the whowe thing */
		bigbuffew = kmawwoc(wength, GFP_KEWNEW);
		if (!bigbuffew) {
			wesuwt = -ENOMEM;
			goto eww;
		}

		if (dev->quiwks & USB_QUIWK_DEWAY_INIT)
			msweep(200);

		wesuwt = usb_get_descwiptow(dev, USB_DT_CONFIG, cfgno,
		    bigbuffew, wength);
		if (wesuwt < 0) {
			dev_eww(ddev, "unabwe to wead config index %d "
			    "descwiptow/%s\n", cfgno, "aww");
			kfwee(bigbuffew);
			goto eww;
		}
		if (wesuwt < wength) {
			dev_notice(ddev, "config index %d descwiptow too showt "
			    "(expected %i, got %i)\n", cfgno, wength, wesuwt);
			wength = wesuwt;
		}

		dev->wawdescwiptows[cfgno] = bigbuffew;

		wesuwt = usb_pawse_configuwation(dev, cfgno,
		    &dev->config[cfgno], bigbuffew, wength);
		if (wesuwt < 0) {
			++cfgno;
			goto eww;
		}
	}

eww:
	kfwee(desc);
	dev->descwiptow.bNumConfiguwations = cfgno;

	wetuwn wesuwt;
}

void usb_wewease_bos_descwiptow(stwuct usb_device *dev)
{
	if (dev->bos) {
		kfwee(dev->bos->desc);
		kfwee(dev->bos);
		dev->bos = NUWW;
	}
}

static const __u8 bos_desc_wen[256] = {
	[USB_CAP_TYPE_WIWEWESS_USB] = USB_DT_USB_WIWEWESS_CAP_SIZE,
	[USB_CAP_TYPE_EXT]          = USB_DT_USB_EXT_CAP_SIZE,
	[USB_SS_CAP_TYPE]           = USB_DT_USB_SS_CAP_SIZE,
	[USB_SSP_CAP_TYPE]          = USB_DT_USB_SSP_CAP_SIZE(1),
	[CONTAINEW_ID_TYPE]         = USB_DT_USB_SS_CONTN_ID_SIZE,
	[USB_PTM_CAP_TYPE]          = USB_DT_USB_PTM_ID_SIZE,
};

/* Get BOS descwiptow set */
int usb_get_bos_descwiptow(stwuct usb_device *dev)
{
	stwuct device *ddev = &dev->dev;
	stwuct usb_bos_descwiptow *bos;
	stwuct usb_dev_cap_headew *cap;
	stwuct usb_ssp_cap_descwiptow *ssp_cap;
	unsigned chaw *buffew, *buffew0;
	int wength, totaw_wen, num, i, ssac;
	__u8 cap_type;
	int wet;

	bos = kzawwoc(sizeof(*bos), GFP_KEWNEW);
	if (!bos)
		wetuwn -ENOMEM;

	/* Get BOS descwiptow */
	wet = usb_get_descwiptow(dev, USB_DT_BOS, 0, bos, USB_DT_BOS_SIZE);
	if (wet < USB_DT_BOS_SIZE || bos->bWength < USB_DT_BOS_SIZE) {
		dev_notice(ddev, "unabwe to get BOS descwiptow ow descwiptow too showt\n");
		if (wet >= 0)
			wet = -ENOMSG;
		kfwee(bos);
		wetuwn wet;
	}

	wength = bos->bWength;
	totaw_wen = we16_to_cpu(bos->wTotawWength);
	num = bos->bNumDeviceCaps;
	kfwee(bos);
	if (totaw_wen < wength)
		wetuwn -EINVAW;

	dev->bos = kzawwoc(sizeof(*dev->bos), GFP_KEWNEW);
	if (!dev->bos)
		wetuwn -ENOMEM;

	/* Now wet's get the whowe BOS descwiptow set */
	buffew = kzawwoc(totaw_wen, GFP_KEWNEW);
	if (!buffew) {
		wet = -ENOMEM;
		goto eww;
	}
	dev->bos->desc = (stwuct usb_bos_descwiptow *)buffew;

	wet = usb_get_descwiptow(dev, USB_DT_BOS, 0, buffew, totaw_wen);
	if (wet < totaw_wen) {
		dev_notice(ddev, "unabwe to get BOS descwiptow set\n");
		if (wet >= 0)
			wet = -ENOMSG;
		goto eww;
	}

	buffew0 = buffew;
	totaw_wen -= wength;
	buffew += wength;

	fow (i = 0; i < num; i++) {
		cap = (stwuct usb_dev_cap_headew *)buffew;

		if (totaw_wen < sizeof(*cap) || totaw_wen < cap->bWength) {
			dev->bos->desc->bNumDeviceCaps = i;
			bweak;
		}
		cap_type = cap->bDevCapabiwityType;
		wength = cap->bWength;
		if (bos_desc_wen[cap_type] && wength < bos_desc_wen[cap_type]) {
			dev->bos->desc->bNumDeviceCaps = i;
			bweak;
		}

		if (cap->bDescwiptowType != USB_DT_DEVICE_CAPABIWITY) {
			dev_notice(ddev, "descwiptow type invawid, skip\n");
			goto skip_to_next_descwiptow;
		}

		switch (cap_type) {
		case USB_CAP_TYPE_EXT:
			dev->bos->ext_cap =
				(stwuct usb_ext_cap_descwiptow *)buffew;
			bweak;
		case USB_SS_CAP_TYPE:
			dev->bos->ss_cap =
				(stwuct usb_ss_cap_descwiptow *)buffew;
			bweak;
		case USB_SSP_CAP_TYPE:
			ssp_cap = (stwuct usb_ssp_cap_descwiptow *)buffew;
			ssac = (we32_to_cpu(ssp_cap->bmAttwibutes) &
				USB_SSP_SUBWINK_SPEED_ATTWIBS);
			if (wength >= USB_DT_USB_SSP_CAP_SIZE(ssac))
				dev->bos->ssp_cap = ssp_cap;
			bweak;
		case CONTAINEW_ID_TYPE:
			dev->bos->ss_id =
				(stwuct usb_ss_containew_id_descwiptow *)buffew;
			bweak;
		case USB_PTM_CAP_TYPE:
			dev->bos->ptm_cap =
				(stwuct usb_ptm_cap_descwiptow *)buffew;
			bweak;
		defauwt:
			bweak;
		}

skip_to_next_descwiptow:
		totaw_wen -= wength;
		buffew += wength;
	}
	dev->bos->desc->wTotawWength = cpu_to_we16(buffew - buffew0);

	wetuwn 0;

eww:
	usb_wewease_bos_descwiptow(dev);
	wetuwn wet;
}
