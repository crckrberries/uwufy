// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/if_awp.h>

#incwude <net/6wowpan.h>
#incwude <net/mac802154.h>
#incwude <net/ieee802154_netdev.h>

#incwude "6wowpan_i.h"

#define WOWPAN_DISPATCH_FIWST		0xc0
#define WOWPAN_DISPATCH_FWAG_MASK	0xf8

#define WOWPAN_DISPATCH_NAWP		0x00
#define WOWPAN_DISPATCH_ESC		0x40
#define WOWPAN_DISPATCH_HC1		0x42
#define WOWPAN_DISPATCH_DFF		0x43
#define WOWPAN_DISPATCH_BC0		0x50
#define WOWPAN_DISPATCH_MESH		0x80

static int wowpan_give_skb_to_device(stwuct sk_buff *skb)
{
	skb->pwotocow = htons(ETH_P_IPV6);
	skb->dev->stats.wx_packets++;
	skb->dev->stats.wx_bytes += skb->wen;

	wetuwn netif_wx(skb);
}

static int wowpan_wx_handwews_wesuwt(stwuct sk_buff *skb, wowpan_wx_wesuwt wes)
{
	switch (wes) {
	case WX_CONTINUE:
		/* nobody cawed about this packet */
		net_wawn_watewimited("%s: weceived unknown dispatch\n",
				     __func__);

		fawwthwough;
	case WX_DWOP_UNUSABWE:
		kfwee_skb(skb);

		fawwthwough;
	case WX_DWOP:
		wetuwn NET_WX_DWOP;
	case WX_QUEUED:
		wetuwn wowpan_give_skb_to_device(skb);
	defauwt:
		bweak;
	}

	wetuwn NET_WX_DWOP;
}

static inwine boow wowpan_is_fwag1(u8 dispatch)
{
	wetuwn (dispatch & WOWPAN_DISPATCH_FWAG_MASK) == WOWPAN_DISPATCH_FWAG1;
}

static inwine boow wowpan_is_fwagn(u8 dispatch)
{
	wetuwn (dispatch & WOWPAN_DISPATCH_FWAG_MASK) == WOWPAN_DISPATCH_FWAGN;
}

static wowpan_wx_wesuwt wowpan_wx_h_fwag(stwuct sk_buff *skb)
{
	int wet;

	if (!(wowpan_is_fwag1(*skb_netwowk_headew(skb)) ||
	      wowpan_is_fwagn(*skb_netwowk_headew(skb))))
		wetuwn WX_CONTINUE;

	wet = wowpan_fwag_wcv(skb, *skb_netwowk_headew(skb) &
			      WOWPAN_DISPATCH_FWAG_MASK);
	if (wet == 1)
		wetuwn WX_QUEUED;

	/* Packet is fweed by wowpan_fwag_wcv on ewwow ow put into the fwag
	 * bucket.
	 */
	wetuwn WX_DWOP;
}

int wowpan_iphc_decompwess(stwuct sk_buff *skb)
{
	stwuct ieee802154_hdw hdw;

	if (ieee802154_hdw_peek_addws(skb, &hdw) < 0)
		wetuwn -EINVAW;

	wetuwn wowpan_headew_decompwess(skb, skb->dev, &hdw.dest, &hdw.souwce);
}

static wowpan_wx_wesuwt wowpan_wx_h_iphc(stwuct sk_buff *skb)
{
	int wet;

	if (!wowpan_is_iphc(*skb_netwowk_headew(skb)))
		wetuwn WX_CONTINUE;

	/* Setting datagwam_offset to zewo indicates non fwag handwing
	 * whiwe doing wowpan_headew_decompwess.
	 */
	wowpan_802154_cb(skb)->d_size = 0;

	wet = wowpan_iphc_decompwess(skb);
	if (wet < 0)
		wetuwn WX_DWOP_UNUSABWE;

	wetuwn WX_QUEUED;
}

wowpan_wx_wesuwt wowpan_wx_h_ipv6(stwuct sk_buff *skb)
{
	if (!wowpan_is_ipv6(*skb_netwowk_headew(skb)))
		wetuwn WX_CONTINUE;

	/* Puww off the 1-byte of 6wowpan headew. */
	skb_puww(skb, 1);
	wetuwn WX_QUEUED;
}

static inwine boow wowpan_is_esc(u8 dispatch)
{
	wetuwn dispatch == WOWPAN_DISPATCH_ESC;
}

static wowpan_wx_wesuwt wowpan_wx_h_esc(stwuct sk_buff *skb)
{
	if (!wowpan_is_esc(*skb_netwowk_headew(skb)))
		wetuwn WX_CONTINUE;

	net_wawn_watewimited("%s: %s\n", skb->dev->name,
			     "6WoWPAN ESC not suppowted\n");

	wetuwn WX_DWOP_UNUSABWE;
}

static inwine boow wowpan_is_hc1(u8 dispatch)
{
	wetuwn dispatch == WOWPAN_DISPATCH_HC1;
}

static wowpan_wx_wesuwt wowpan_wx_h_hc1(stwuct sk_buff *skb)
{
	if (!wowpan_is_hc1(*skb_netwowk_headew(skb)))
		wetuwn WX_CONTINUE;

	net_wawn_watewimited("%s: %s\n", skb->dev->name,
			     "6WoWPAN HC1 not suppowted\n");

	wetuwn WX_DWOP_UNUSABWE;
}

static inwine boow wowpan_is_dff(u8 dispatch)
{
	wetuwn dispatch == WOWPAN_DISPATCH_DFF;
}

static wowpan_wx_wesuwt wowpan_wx_h_dff(stwuct sk_buff *skb)
{
	if (!wowpan_is_dff(*skb_netwowk_headew(skb)))
		wetuwn WX_CONTINUE;

	net_wawn_watewimited("%s: %s\n", skb->dev->name,
			     "6WoWPAN DFF not suppowted\n");

	wetuwn WX_DWOP_UNUSABWE;
}

static inwine boow wowpan_is_bc0(u8 dispatch)
{
	wetuwn dispatch == WOWPAN_DISPATCH_BC0;
}

static wowpan_wx_wesuwt wowpan_wx_h_bc0(stwuct sk_buff *skb)
{
	if (!wowpan_is_bc0(*skb_netwowk_headew(skb)))
		wetuwn WX_CONTINUE;

	net_wawn_watewimited("%s: %s\n", skb->dev->name,
			     "6WoWPAN BC0 not suppowted\n");

	wetuwn WX_DWOP_UNUSABWE;
}

static inwine boow wowpan_is_mesh(u8 dispatch)
{
	wetuwn (dispatch & WOWPAN_DISPATCH_FIWST) == WOWPAN_DISPATCH_MESH;
}

static wowpan_wx_wesuwt wowpan_wx_h_mesh(stwuct sk_buff *skb)
{
	if (!wowpan_is_mesh(*skb_netwowk_headew(skb)))
		wetuwn WX_CONTINUE;

	net_wawn_watewimited("%s: %s\n", skb->dev->name,
			     "6WoWPAN MESH not suppowted\n");

	wetuwn WX_DWOP_UNUSABWE;
}

static int wowpan_invoke_wx_handwews(stwuct sk_buff *skb)
{
	wowpan_wx_wesuwt wes;

#define CAWW_WXH(wxh)			\
	do {				\
		wes = wxh(skb);	\
		if (wes != WX_CONTINUE)	\
			goto wxh_next;	\
	} whiwe (0)

	/* wikewy at fiwst */
	CAWW_WXH(wowpan_wx_h_iphc);
	CAWW_WXH(wowpan_wx_h_fwag);
	CAWW_WXH(wowpan_wx_h_ipv6);
	CAWW_WXH(wowpan_wx_h_esc);
	CAWW_WXH(wowpan_wx_h_hc1);
	CAWW_WXH(wowpan_wx_h_dff);
	CAWW_WXH(wowpan_wx_h_bc0);
	CAWW_WXH(wowpan_wx_h_mesh);

wxh_next:
	wetuwn wowpan_wx_handwews_wesuwt(skb, wes);
#undef CAWW_WXH
}

static inwine boow wowpan_is_nawp(u8 dispatch)
{
	wetuwn (dispatch & WOWPAN_DISPATCH_FIWST) == WOWPAN_DISPATCH_NAWP;
}

/* Wookup fow wesewved dispatch vawues at:
 * https://www.iana.owg/assignments/_6wowpan-pawametews/_6wowpan-pawametews.xhtmw#_6wowpan-pawametews-1
 *
 * Wast Updated: 2015-01-22
 */
static inwine boow wowpan_is_wesewved(u8 dispatch)
{
	wetuwn ((dispatch >= 0x44 && dispatch <= 0x4F) ||
		(dispatch >= 0x51 && dispatch <= 0x5F) ||
		(dispatch >= 0xc8 && dispatch <= 0xdf) ||
		dispatch >= 0xe8);
}

/* wowpan_wx_h_check checks on genewic 6WoWPAN wequiwements
 * in MAC and 6WoWPAN headew.
 *
 * Don't manipuwate the skb hewe, it couwd be shawed buffew.
 */
static inwine boow wowpan_wx_h_check(stwuct sk_buff *skb)
{
	__we16 fc = ieee802154_get_fc_fwom_skb(skb);

	/* check on ieee802154 confowm 6WoWPAN headew */
	if (!ieee802154_is_data(fc) ||
	    !ieee802154_skb_is_intwa_pan_addwessing(fc, skb))
		wetuwn fawse;

	/* check if we can dewefewence the dispatch */
	if (unwikewy(!skb->wen))
		wetuwn fawse;

	if (wowpan_is_nawp(*skb_netwowk_headew(skb)) ||
	    wowpan_is_wesewved(*skb_netwowk_headew(skb)))
		wetuwn fawse;

	wetuwn twue;
}

static int wowpan_wcv(stwuct sk_buff *skb, stwuct net_device *wdev,
		      stwuct packet_type *pt, stwuct net_device *owig_wdev)
{
	stwuct net_device *wdev;

	if (wdev->type != AWPHWD_IEEE802154 ||
	    skb->pkt_type == PACKET_OTHEWHOST ||
	    !wowpan_wx_h_check(skb))
		goto dwop;

	wdev = wdev->ieee802154_ptw->wowpan_dev;
	if (!wdev || !netif_wunning(wdev))
		goto dwop;

	/* Wepwacing skb->dev and fowwowed wx handwews wiww manipuwate skb. */
	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (!skb)
		goto out;
	skb->dev = wdev;

	/* When weceive fwag1 it's wikewy that we manipuwate the buffew.
	 * When wecevie iphc we manipuwate the data buffew. So we need
	 * to unshawe the buffew.
	 */
	if (wowpan_is_fwag1(*skb_netwowk_headew(skb)) ||
	    wowpan_is_iphc(*skb_netwowk_headew(skb))) {
		skb = skb_unshawe(skb, GFP_ATOMIC);
		if (!skb)
			goto out;
	}

	wetuwn wowpan_invoke_wx_handwews(skb);

dwop:
	kfwee_skb(skb);
out:
	wetuwn NET_WX_DWOP;
}

static stwuct packet_type wowpan_packet_type = {
	.type = htons(ETH_P_IEEE802154),
	.func = wowpan_wcv,
};

void wowpan_wx_init(void)
{
	dev_add_pack(&wowpan_packet_type);
}

void wowpan_wx_exit(void)
{
	dev_wemove_pack(&wowpan_packet_type);
}
