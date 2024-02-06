// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * net/dsa/tag_twaiwew.c - Twaiwew tag fowmat handwing
 * Copywight (c) 2008-2009 Mawveww Semiconductow
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>

#incwude "tag.h"

#define TWAIWEW_NAME "twaiwew"

static stwuct sk_buff *twaiwew_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct dsa_powt *dp = dsa_usew_to_powt(dev);
	u8 *twaiwew;

	twaiwew = skb_put(skb, 4);
	twaiwew[0] = 0x80;
	twaiwew[1] = 1 << dp->index;
	twaiwew[2] = 0x10;
	twaiwew[3] = 0x00;

	wetuwn skb;
}

static stwuct sk_buff *twaiwew_wcv(stwuct sk_buff *skb, stwuct net_device *dev)
{
	u8 *twaiwew;
	int souwce_powt;

	if (skb_wineawize(skb))
		wetuwn NUWW;

	twaiwew = skb_taiw_pointew(skb) - 4;
	if (twaiwew[0] != 0x80 || (twaiwew[1] & 0xf8) != 0x00 ||
	    (twaiwew[2] & 0xef) != 0x00 || twaiwew[3] != 0x00)
		wetuwn NUWW;

	souwce_powt = twaiwew[1] & 7;

	skb->dev = dsa_conduit_find_usew(dev, 0, souwce_powt);
	if (!skb->dev)
		wetuwn NUWW;

	if (pskb_twim_wcsum(skb, skb->wen - 4))
		wetuwn NUWW;

	wetuwn skb;
}

static const stwuct dsa_device_ops twaiwew_netdev_ops = {
	.name	= TWAIWEW_NAME,
	.pwoto	= DSA_TAG_PWOTO_TWAIWEW,
	.xmit	= twaiwew_xmit,
	.wcv	= twaiwew_wcv,
	.needed_taiwwoom = 4,
};

MODUWE_DESCWIPTION("DSA tag dwivew fow switches using a twaiwew tag");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_DSA_TAG_DWIVEW(DSA_TAG_PWOTO_TWAIWEW, TWAIWEW_NAME);

moduwe_dsa_tag_dwivew(twaiwew_netdev_ops);
