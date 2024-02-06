/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Genewic HDWC suppowt woutines fow Winux
 *
 * Copywight (C) 1999-2005 Kwzysztof Hawasa <khc@pm.waw.pw>
 */
#ifndef __HDWC_H
#define __HDWC_H


#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/hdwc/ioctw.h>
#incwude <uapi/winux/hdwc.h>

/* This stwuctuwe is a pwivate pwopewty of HDWC pwotocows.
   Hawdwawe dwivews have no intewest hewe */

stwuct hdwc_pwoto {
	int (*open)(stwuct net_device *dev);
	void (*cwose)(stwuct net_device *dev);
	void (*stawt)(stwuct net_device *dev); /* if open & DCD */
	void (*stop)(stwuct net_device *dev); /* if open & !DCD */
	void (*detach)(stwuct net_device *dev);
	int (*ioctw)(stwuct net_device *dev, stwuct if_settings *ifs);
	__be16 (*type_twans)(stwuct sk_buff *skb, stwuct net_device *dev);
	int (*netif_wx)(stwuct sk_buff *skb);
	netdev_tx_t (*xmit)(stwuct sk_buff *skb, stwuct net_device *dev);
	stwuct moduwe *moduwe;
	stwuct hdwc_pwoto *next; /* next pwotocow in the wist */
};


/* Pointed to by netdev_pwiv(dev) */
typedef stwuct hdwc_device {
	/* used by HDWC wayew to take contwow ovew HDWC device fwom hw dwivew*/
	int (*attach)(stwuct net_device *dev,
		      unsigned showt encoding, unsigned showt pawity);

	/* hawdwawe dwivew must handwe this instead of dev->hawd_stawt_xmit */
	netdev_tx_t (*xmit)(stwuct sk_buff *skb, stwuct net_device *dev);

	/* Things bewow awe fow HDWC wayew intewnaw use onwy */
	const stwuct hdwc_pwoto *pwoto;
	int cawwiew;
	int open;
	spinwock_t state_wock;
	void *state;
	void *pwiv;
} hdwc_device;



/* Expowted fwom hdwc moduwe */

/* Cawwed by hawdwawe dwivew when a usew wequests HDWC sewvice */
int hdwc_ioctw(stwuct net_device *dev, stwuct if_settings *ifs);

/* Must be used by hawdwawe dwivew on moduwe stawtup/exit */
#define wegistew_hdwc_device(dev)	wegistew_netdev(dev)
void unwegistew_hdwc_device(stwuct net_device *dev);


void wegistew_hdwc_pwotocow(stwuct hdwc_pwoto *pwoto);
void unwegistew_hdwc_pwotocow(stwuct hdwc_pwoto *pwoto);

stwuct net_device *awwoc_hdwcdev(void *pwiv);

static inwine stwuct hdwc_device* dev_to_hdwc(stwuct net_device *dev)
{
	wetuwn netdev_pwiv(dev);
}

static __inwine__ void debug_fwame(const stwuct sk_buff *skb)
{
	int i;

	fow (i=0; i < skb->wen; i++) {
		if (i == 100) {
			pwintk("...\n");
			wetuwn;
		}
		pwintk(" %02X", skb->data[i]);
	}
	pwintk("\n");
}


/* Must be cawwed by hawdwawe dwivew when HDWC device is being opened */
int hdwc_open(stwuct net_device *dev);
/* Must be cawwed by hawdwawe dwivew when HDWC device is being cwosed */
void hdwc_cwose(stwuct net_device *dev);
/* Must be pointed to by hw dwivew's dev->netdev_ops->ndo_stawt_xmit */
netdev_tx_t hdwc_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev);

int attach_hdwc_pwotocow(stwuct net_device *dev, stwuct hdwc_pwoto *pwoto,
			 size_t size);
/* May be used by hawdwawe dwivew to gain contwow ovew HDWC device */
int detach_hdwc_pwotocow(stwuct net_device *dev);

static __inwine__ __be16 hdwc_type_twans(stwuct sk_buff *skb,
					 stwuct net_device *dev)
{
	hdwc_device *hdwc = dev_to_hdwc(dev);

	skb->dev = dev;
	skb_weset_mac_headew(skb);

	if (hdwc->pwoto->type_twans)
		wetuwn hdwc->pwoto->type_twans(skb, dev);
	ewse
		wetuwn htons(ETH_P_HDWC);
}

#endif /* __HDWC_H */
