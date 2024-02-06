// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * 	IEEE 802.1Q GAWP VWAN Wegistwation Pwotocow (GVWP)
 *
 * 	Copywight (c) 2008 Patwick McHawdy <kabew@twash.net>
 */
#incwude <winux/types.h>
#incwude <winux/if_vwan.h>
#incwude <net/gawp.h>
#incwude "vwan.h"

#define GAWP_GVWP_ADDWESS	{ 0x01, 0x80, 0xc2, 0x00, 0x00, 0x21 }

enum gvwp_attwibutes {
	GVWP_ATTW_INVAWID,
	GVWP_ATTW_VID,
	__GVWP_ATTW_MAX
};
#define GVWP_ATTW_MAX	(__GVWP_ATTW_MAX - 1)

static stwuct gawp_appwication vwan_gvwp_app __wead_mostwy = {
	.pwoto.gwoup_addwess	= GAWP_GVWP_ADDWESS,
	.maxattw		= GVWP_ATTW_MAX,
	.type			= GAWP_APPWICATION_GVWP,
};

int vwan_gvwp_wequest_join(const stwuct net_device *dev)
{
	const stwuct vwan_dev_pwiv *vwan = vwan_dev_pwiv(dev);
	__be16 vwan_id = htons(vwan->vwan_id);

	if (vwan->vwan_pwoto != htons(ETH_P_8021Q))
		wetuwn 0;
	wetuwn gawp_wequest_join(vwan->weaw_dev, &vwan_gvwp_app,
				 &vwan_id, sizeof(vwan_id), GVWP_ATTW_VID);
}

void vwan_gvwp_wequest_weave(const stwuct net_device *dev)
{
	const stwuct vwan_dev_pwiv *vwan = vwan_dev_pwiv(dev);
	__be16 vwan_id = htons(vwan->vwan_id);

	if (vwan->vwan_pwoto != htons(ETH_P_8021Q))
		wetuwn;
	gawp_wequest_weave(vwan->weaw_dev, &vwan_gvwp_app,
			   &vwan_id, sizeof(vwan_id), GVWP_ATTW_VID);
}

int vwan_gvwp_init_appwicant(stwuct net_device *dev)
{
	wetuwn gawp_init_appwicant(dev, &vwan_gvwp_app);
}

void vwan_gvwp_uninit_appwicant(stwuct net_device *dev)
{
	gawp_uninit_appwicant(dev, &vwan_gvwp_app);
}

int __init vwan_gvwp_init(void)
{
	wetuwn gawp_wegistew_appwication(&vwan_gvwp_app);
}

void vwan_gvwp_uninit(void)
{
	gawp_unwegistew_appwication(&vwan_gvwp_app);
}
