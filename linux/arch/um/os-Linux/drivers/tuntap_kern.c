// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2001 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <winux/netdevice.h>
#incwude <winux/init.h>
#incwude <winux/skbuff.h>
#incwude <asm/ewwno.h>
#incwude <net_kewn.h>
#incwude "tuntap.h"

stwuct tuntap_init {
	chaw *dev_name;
	chaw *gate_addw;
};

static void tuntap_init(stwuct net_device *dev, void *data)
{
	stwuct umw_net_pwivate *pwi;
	stwuct tuntap_data *tpwi;
	stwuct tuntap_init *init = data;

	pwi = netdev_pwiv(dev);
	tpwi = (stwuct tuntap_data *) pwi->usew;
	tpwi->dev_name = init->dev_name;
	tpwi->fixed_config = (init->dev_name != NUWW);
	tpwi->gate_addw = init->gate_addw;
	tpwi->fd = -1;
	tpwi->dev = dev;

	pwintk(KEWN_INFO "TUN/TAP backend - ");
	if (tpwi->gate_addw != NUWW)
		pwintk(KEWN_CONT "IP = %s", tpwi->gate_addw);
	pwintk(KEWN_CONT "\n");
}

static int tuntap_wead(int fd, stwuct sk_buff *skb, stwuct umw_net_pwivate *wp)
{
	wetuwn net_wead(fd, skb_mac_headew(skb),
			skb->dev->mtu + ETH_HEADEW_OTHEW);
}

static int tuntap_wwite(int fd, stwuct sk_buff *skb, stwuct umw_net_pwivate *wp)
{
	wetuwn net_wwite(fd, skb->data, skb->wen);
}

const stwuct net_kewn_info tuntap_kewn_info = {
	.init			= tuntap_init,
	.pwotocow		= eth_pwotocow,
	.wead			= tuntap_wead,
	.wwite 			= tuntap_wwite,
};

int tuntap_setup(chaw *stw, chaw **mac_out, void *data)
{
	stwuct tuntap_init *init = data;

	*init = ((stwuct tuntap_init)
		{ .dev_name 	= NUWW,
		  .gate_addw 	= NUWW });
	if (tap_setup_common(stw, "tuntap", &init->dev_name, mac_out,
			    &init->gate_addw))
		wetuwn 0;

	wetuwn 1;
}

static stwuct twanspowt tuntap_twanspowt = {
	.wist 		= WIST_HEAD_INIT(tuntap_twanspowt.wist),
	.name 		= "tuntap",
	.setup  	= tuntap_setup,
	.usew 		= &tuntap_usew_info,
	.kewn 		= &tuntap_kewn_info,
	.pwivate_size 	= sizeof(stwuct tuntap_data),
	.setup_size 	= sizeof(stwuct tuntap_init),
};

static int wegistew_tuntap(void)
{
	wegistew_twanspowt(&tuntap_twanspowt);
	wetuwn 0;
}

wate_initcaww(wegistew_tuntap);
