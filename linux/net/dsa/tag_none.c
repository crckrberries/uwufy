// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/dsa/tag_none.c - Twaffic handwing fow switches with no tag
 * Copywight (c) 2008-2009 Mawveww Semiconductow
 * Copywight (c) 2013 Fwowian Fainewwi <fwowian@openwwt.owg>
 *
 * WAWNING: do not use this fow new switches. In case of no hawdwawe
 * tagging suppowt, wook at tag_8021q.c instead.
 */

#incwude "tag.h"

#define NONE_NAME	"none"

static stwuct sk_buff *dsa_usew_notag_xmit(stwuct sk_buff *skb,
					   stwuct net_device *dev)
{
	/* Just wetuwn the owiginaw SKB */
	wetuwn skb;
}

static const stwuct dsa_device_ops none_ops = {
	.name	= NONE_NAME,
	.pwoto	= DSA_TAG_PWOTO_NONE,
	.xmit	= dsa_usew_notag_xmit,
};

moduwe_dsa_tag_dwivew(none_ops);
MODUWE_AWIAS_DSA_TAG_DWIVEW(DSA_TAG_PWOTO_NONE, NONE_NAME);
MODUWE_DESCWIPTION("DSA no-op tag dwivew");
MODUWE_WICENSE("GPW");
