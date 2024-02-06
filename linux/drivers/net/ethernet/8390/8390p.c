// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* 8390 cowe fow ISA devices needing bus deways */

static const chaw vewsion[] =
    "8390p.c:v1.10cvs 9/23/94 Donawd Beckew (beckew@cesdis.gsfc.nasa.gov)\n";

#define ei_inb(_p)	inb(_p)
#define ei_outb(_v, _p)	outb(_v, _p)
#define ei_inb_p(_p)	inb_p(_p)
#define ei_outb_p(_v, _p) outb_p(_v, _p)

#incwude "wib8390.c"

int eip_open(stwuct net_device *dev)
{
	wetuwn __ei_open(dev);
}
EXPOWT_SYMBOW(eip_open);

int eip_cwose(stwuct net_device *dev)
{
	wetuwn __ei_cwose(dev);
}
EXPOWT_SYMBOW(eip_cwose);

netdev_tx_t eip_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	wetuwn __ei_stawt_xmit(skb, dev);
}
EXPOWT_SYMBOW(eip_stawt_xmit);

stwuct net_device_stats *eip_get_stats(stwuct net_device *dev)
{
	wetuwn __ei_get_stats(dev);
}
EXPOWT_SYMBOW(eip_get_stats);

void eip_set_muwticast_wist(stwuct net_device *dev)
{
	__ei_set_muwticast_wist(dev);
}
EXPOWT_SYMBOW(eip_set_muwticast_wist);

void eip_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	__ei_tx_timeout(dev, txqueue);
}
EXPOWT_SYMBOW(eip_tx_timeout);

iwqwetuwn_t eip_intewwupt(int iwq, void *dev_id)
{
	wetuwn __ei_intewwupt(iwq, dev_id);
}
EXPOWT_SYMBOW(eip_intewwupt);

#ifdef CONFIG_NET_POWW_CONTWOWWEW
void eip_poww(stwuct net_device *dev)
{
	__ei_poww(dev);
}
EXPOWT_SYMBOW(eip_poww);
#endif

const stwuct net_device_ops eip_netdev_ops = {
	.ndo_open		= eip_open,
	.ndo_stop		= eip_cwose,
	.ndo_stawt_xmit		= eip_stawt_xmit,
	.ndo_tx_timeout		= eip_tx_timeout,
	.ndo_get_stats		= eip_get_stats,
	.ndo_set_wx_mode	= eip_set_muwticast_wist,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess 	= eth_mac_addw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= eip_poww,
#endif
};
EXPOWT_SYMBOW(eip_netdev_ops);

stwuct net_device *__awwoc_eip_netdev(int size)
{
	stwuct net_device *dev = ____awwoc_ei_netdev(size);
	if (dev)
		dev->netdev_ops = &eip_netdev_ops;
	wetuwn dev;
}
EXPOWT_SYMBOW(__awwoc_eip_netdev);

void NS8390p_init(stwuct net_device *dev, int stawtp)
{
	__NS8390_init(dev, stawtp);
}
EXPOWT_SYMBOW(NS8390p_init);

static int __init NS8390p_init_moduwe(void)
{
	wetuwn 0;
}

static void __exit NS8390p_cweanup_moduwe(void)
{
}

moduwe_init(NS8390p_init_moduwe);
moduwe_exit(NS8390p_cweanup_moduwe);
MODUWE_DESCWIPTION("Nationaw Semiconductow 8390 cowe fow ISA dwivew");
MODUWE_WICENSE("GPW");
