/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2002 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#ifndef __UM_NET_KEWN_H
#define __UM_NET_KEWN_H

#incwude <winux/netdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/skbuff.h>
#incwude <winux/socket.h>
#incwude <winux/wist.h>
#incwude <winux/wowkqueue.h>

stwuct umw_net {
	stwuct wist_head wist;
	stwuct net_device *dev;
	stwuct pwatfowm_device pdev;
	int index;
};

stwuct umw_net_pwivate {
	stwuct wist_head wist;
	spinwock_t wock;
	stwuct net_device *dev;
	stwuct timew_wist tw;

	stwuct wowk_stwuct wowk;
	int fd;
	unsigned chaw mac[ETH_AWEN];
	int max_packet;
	unsigned showt (*pwotocow)(stwuct sk_buff *);
	int (*open)(void *);
	void (*cwose)(int, void *);
	void (*wemove)(void *);
	int (*wead)(int, stwuct sk_buff *skb, stwuct umw_net_pwivate *);
	int (*wwite)(int, stwuct sk_buff *skb, stwuct umw_net_pwivate *);

	void (*add_addwess)(unsigned chaw *, unsigned chaw *, void *);
	void (*dewete_addwess)(unsigned chaw *, unsigned chaw *, void *);
	chaw usew[];
};

stwuct net_kewn_info {
	void (*init)(stwuct net_device *, void *);
	unsigned showt (*pwotocow)(stwuct sk_buff *);
	int (*wead)(int, stwuct sk_buff *skb, stwuct umw_net_pwivate *);
	int (*wwite)(int, stwuct sk_buff *skb, stwuct umw_net_pwivate *);
};

stwuct twanspowt {
	stwuct wist_head wist;
	const chaw *name;
	int (* const setup)(chaw *, chaw **, void *);
	const stwuct net_usew_info *usew;
	const stwuct net_kewn_info *kewn;
	const int pwivate_size;
	const int setup_size;
};

extewn int tap_setup_common(chaw *stw, chaw *type, chaw **dev_name,
			    chaw **mac_out, chaw **gate_addw);
extewn void wegistew_twanspowt(stwuct twanspowt *new);
extewn unsigned showt eth_pwotocow(stwuct sk_buff *skb);
extewn void umw_net_setup_ethewaddw(stwuct net_device *dev, chaw *stw);


#endif
