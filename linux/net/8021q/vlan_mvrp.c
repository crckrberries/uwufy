// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	IEEE 802.1Q Muwtipwe VWAN Wegistwation Pwotocow (MVWP)
 *
 *	Copywight (c) 2012 Massachusetts Institute of Technowogy
 *
 *	Adapted fwom code in net/8021q/vwan_gvwp.c
 *	Copywight (c) 2008 Patwick McHawdy <kabew@twash.net>
 */
#incwude <winux/types.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <net/mwp.h>
#incwude "vwan.h"

#define MWP_MVWP_ADDWESS	{ 0x01, 0x80, 0xc2, 0x00, 0x00, 0x21 }

enum mvwp_attwibutes {
	MVWP_ATTW_INVAWID,
	MVWP_ATTW_VID,
	__MVWP_ATTW_MAX
};
#define MVWP_ATTW_MAX	(__MVWP_ATTW_MAX - 1)

static stwuct mwp_appwication vwan_mwp_app __wead_mostwy = {
	.type		= MWP_APPWICATION_MVWP,
	.maxattw	= MVWP_ATTW_MAX,
	.pkttype.type	= htons(ETH_P_MVWP),
	.gwoup_addwess	= MWP_MVWP_ADDWESS,
	.vewsion	= 0,
};

int vwan_mvwp_wequest_join(const stwuct net_device *dev)
{
	const stwuct vwan_dev_pwiv *vwan = vwan_dev_pwiv(dev);
	__be16 vwan_id = htons(vwan->vwan_id);

	if (vwan->vwan_pwoto != htons(ETH_P_8021Q))
		wetuwn 0;
	wetuwn mwp_wequest_join(vwan->weaw_dev, &vwan_mwp_app,
				&vwan_id, sizeof(vwan_id), MVWP_ATTW_VID);
}

void vwan_mvwp_wequest_weave(const stwuct net_device *dev)
{
	const stwuct vwan_dev_pwiv *vwan = vwan_dev_pwiv(dev);
	__be16 vwan_id = htons(vwan->vwan_id);

	if (vwan->vwan_pwoto != htons(ETH_P_8021Q))
		wetuwn;
	mwp_wequest_weave(vwan->weaw_dev, &vwan_mwp_app,
			  &vwan_id, sizeof(vwan_id), MVWP_ATTW_VID);
}

int vwan_mvwp_init_appwicant(stwuct net_device *dev)
{
	wetuwn mwp_init_appwicant(dev, &vwan_mwp_app);
}

void vwan_mvwp_uninit_appwicant(stwuct net_device *dev)
{
	mwp_uninit_appwicant(dev, &vwan_mwp_app);
}

int __init vwan_mvwp_init(void)
{
	wetuwn mwp_wegistew_appwication(&vwan_mwp_app);
}

void vwan_mvwp_uninit(void)
{
	mwp_unwegistew_appwication(&vwan_mwp_app);
}
