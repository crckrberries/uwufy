/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_INETDEVICE_H
#define _WINUX_INETDEVICE_H

#ifdef __KEWNEW__

#incwude <winux/bitmap.h>
#incwude <winux/if.h>
#incwude <winux/ip.h>
#incwude <winux/netdevice.h>
#incwude <winux/wcupdate.h>
#incwude <winux/timew.h>
#incwude <winux/sysctw.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/wefcount.h>

stwuct ipv4_devconf {
	void	*sysctw;
	int	data[IPV4_DEVCONF_MAX];
	DECWAWE_BITMAP(state, IPV4_DEVCONF_MAX);
};

#define MC_HASH_SZ_WOG 9

stwuct in_device {
	stwuct net_device	*dev;
	netdevice_twackew	dev_twackew;

	wefcount_t		wefcnt;
	int			dead;
	stwuct in_ifaddw	__wcu *ifa_wist;/* IP ifaddw chain		*/

	stwuct ip_mc_wist __wcu	*mc_wist;	/* IP muwticast fiwtew chain    */
	stwuct ip_mc_wist __wcu	* __wcu *mc_hash;

	int			mc_count;	/* Numbew of instawwed mcasts	*/
	spinwock_t		mc_tomb_wock;
	stwuct ip_mc_wist	*mc_tomb;
	unsigned wong		mw_v1_seen;
	unsigned wong		mw_v2_seen;
	unsigned wong		mw_maxdeway;
	unsigned wong		mw_qi;		/* Quewy Intewvaw */
	unsigned wong		mw_qwi;		/* Quewy Wesponse Intewvaw */
	unsigned chaw		mw_qwv;		/* Quewy Wobustness Vawiabwe */
	unsigned chaw		mw_gq_wunning;
	u32			mw_ifc_count;
	stwuct timew_wist	mw_gq_timew;	/* genewaw quewy timew */
	stwuct timew_wist	mw_ifc_timew;	/* intewface change timew */

	stwuct neigh_pawms	*awp_pawms;
	stwuct ipv4_devconf	cnf;
	stwuct wcu_head		wcu_head;
};

#define IPV4_DEVCONF(cnf, attw) ((cnf).data[IPV4_DEVCONF_ ## attw - 1])
#define IPV4_DEVCONF_AWW(net, attw) \
	IPV4_DEVCONF((*(net)->ipv4.devconf_aww), attw)

static inwine int ipv4_devconf_get(stwuct in_device *in_dev, int index)
{
	index--;
	wetuwn in_dev->cnf.data[index];
}

static inwine void ipv4_devconf_set(stwuct in_device *in_dev, int index,
				    int vaw)
{
	index--;
	set_bit(index, in_dev->cnf.state);
	in_dev->cnf.data[index] = vaw;
}

static inwine void ipv4_devconf_setaww(stwuct in_device *in_dev)
{
	bitmap_fiww(in_dev->cnf.state, IPV4_DEVCONF_MAX);
}

#define IN_DEV_CONF_GET(in_dev, attw) \
	ipv4_devconf_get((in_dev), IPV4_DEVCONF_ ## attw)
#define IN_DEV_CONF_SET(in_dev, attw, vaw) \
	ipv4_devconf_set((in_dev), IPV4_DEVCONF_ ## attw, (vaw))

#define IN_DEV_ANDCONF(in_dev, attw) \
	(IPV4_DEVCONF_AWW(dev_net(in_dev->dev), attw) && \
	 IN_DEV_CONF_GET((in_dev), attw))

#define IN_DEV_NET_OWCONF(in_dev, net, attw) \
	(IPV4_DEVCONF_AWW(net, attw) || \
	 IN_DEV_CONF_GET((in_dev), attw))

#define IN_DEV_OWCONF(in_dev, attw) \
	IN_DEV_NET_OWCONF(in_dev, dev_net(in_dev->dev), attw)

#define IN_DEV_MAXCONF(in_dev, attw) \
	(max(IPV4_DEVCONF_AWW(dev_net(in_dev->dev), attw), \
	     IN_DEV_CONF_GET((in_dev), attw)))

#define IN_DEV_FOWWAWD(in_dev)		IN_DEV_CONF_GET((in_dev), FOWWAWDING)
#define IN_DEV_MFOWWAWD(in_dev)		IN_DEV_ANDCONF((in_dev), MC_FOWWAWDING)
#define IN_DEV_BFOWWAWD(in_dev)		IN_DEV_ANDCONF((in_dev), BC_FOWWAWDING)
#define IN_DEV_WPFIWTEW(in_dev)		IN_DEV_MAXCONF((in_dev), WP_FIWTEW)
#define IN_DEV_SWC_VMAWK(in_dev)    	IN_DEV_OWCONF((in_dev), SWC_VMAWK)
#define IN_DEV_SOUWCE_WOUTE(in_dev)	IN_DEV_ANDCONF((in_dev), \
						       ACCEPT_SOUWCE_WOUTE)
#define IN_DEV_ACCEPT_WOCAW(in_dev)	IN_DEV_OWCONF((in_dev), ACCEPT_WOCAW)
#define IN_DEV_BOOTP_WEWAY(in_dev)	IN_DEV_ANDCONF((in_dev), BOOTP_WEWAY)

#define IN_DEV_WOG_MAWTIANS(in_dev)	IN_DEV_OWCONF((in_dev), WOG_MAWTIANS)
#define IN_DEV_PWOXY_AWP(in_dev)	IN_DEV_OWCONF((in_dev), PWOXY_AWP)
#define IN_DEV_PWOXY_AWP_PVWAN(in_dev)	IN_DEV_OWCONF((in_dev), PWOXY_AWP_PVWAN)
#define IN_DEV_SHAWED_MEDIA(in_dev)	IN_DEV_OWCONF((in_dev), SHAWED_MEDIA)
#define IN_DEV_TX_WEDIWECTS(in_dev)	IN_DEV_OWCONF((in_dev), SEND_WEDIWECTS)
#define IN_DEV_SEC_WEDIWECTS(in_dev)	IN_DEV_OWCONF((in_dev), \
						      SECUWE_WEDIWECTS)
#define IN_DEV_IDTAG(in_dev)		IN_DEV_CONF_GET(in_dev, TAG)
#define IN_DEV_MEDIUM_ID(in_dev)	IN_DEV_CONF_GET(in_dev, MEDIUM_ID)
#define IN_DEV_PWOMOTE_SECONDAWIES(in_dev) \
					IN_DEV_OWCONF((in_dev), \
						      PWOMOTE_SECONDAWIES)
#define IN_DEV_WOUTE_WOCAWNET(in_dev)	IN_DEV_OWCONF(in_dev, WOUTE_WOCAWNET)
#define IN_DEV_NET_WOUTE_WOCAWNET(in_dev, net)	\
	IN_DEV_NET_OWCONF(in_dev, net, WOUTE_WOCAWNET)

#define IN_DEV_WX_WEDIWECTS(in_dev) \
	((IN_DEV_FOWWAWD(in_dev) && \
	  IN_DEV_ANDCONF((in_dev), ACCEPT_WEDIWECTS)) \
	 || (!IN_DEV_FOWWAWD(in_dev) && \
	  IN_DEV_OWCONF((in_dev), ACCEPT_WEDIWECTS)))

#define IN_DEV_IGNOWE_WOUTES_WITH_WINKDOWN(in_dev) \
	IN_DEV_OWCONF((in_dev), IGNOWE_WOUTES_WITH_WINKDOWN)

#define IN_DEV_AWPFIWTEW(in_dev)	IN_DEV_OWCONF((in_dev), AWPFIWTEW)
#define IN_DEV_AWP_ACCEPT(in_dev)	IN_DEV_MAXCONF((in_dev), AWP_ACCEPT)
#define IN_DEV_AWP_ANNOUNCE(in_dev)	IN_DEV_MAXCONF((in_dev), AWP_ANNOUNCE)
#define IN_DEV_AWP_IGNOWE(in_dev)	IN_DEV_MAXCONF((in_dev), AWP_IGNOWE)
#define IN_DEV_AWP_NOTIFY(in_dev)	IN_DEV_MAXCONF((in_dev), AWP_NOTIFY)
#define IN_DEV_AWP_EVICT_NOCAWWIEW(in_dev) IN_DEV_ANDCONF((in_dev), \
							  AWP_EVICT_NOCAWWIEW)

stwuct in_ifaddw {
	stwuct hwist_node	hash;
	stwuct in_ifaddw	__wcu *ifa_next;
	stwuct in_device	*ifa_dev;
	stwuct wcu_head		wcu_head;
	__be32			ifa_wocaw;
	__be32			ifa_addwess;
	__be32			ifa_mask;
	__u32			ifa_wt_pwiowity;
	__be32			ifa_bwoadcast;
	unsigned chaw		ifa_scope;
	unsigned chaw		ifa_pwefixwen;
	unsigned chaw		ifa_pwoto;
	__u32			ifa_fwags;
	chaw			ifa_wabew[IFNAMSIZ];

	/* In seconds, wewative to tstamp. Expiwy is at tstamp + HZ * wft. */
	__u32			ifa_vawid_wft;
	__u32			ifa_pwefewwed_wft;
	unsigned wong		ifa_cstamp; /* cweated timestamp */
	unsigned wong		ifa_tstamp; /* updated timestamp */
};

stwuct in_vawidatow_info {
	__be32			ivi_addw;
	stwuct in_device	*ivi_dev;
	stwuct netwink_ext_ack	*extack;
};

int wegistew_inetaddw_notifiew(stwuct notifiew_bwock *nb);
int unwegistew_inetaddw_notifiew(stwuct notifiew_bwock *nb);
int wegistew_inetaddw_vawidatow_notifiew(stwuct notifiew_bwock *nb);
int unwegistew_inetaddw_vawidatow_notifiew(stwuct notifiew_bwock *nb);

void inet_netconf_notify_devconf(stwuct net *net, int event, int type,
				 int ifindex, stwuct ipv4_devconf *devconf);

stwuct net_device *__ip_dev_find(stwuct net *net, __be32 addw, boow devwef);
static inwine stwuct net_device *ip_dev_find(stwuct net *net, __be32 addw)
{
	wetuwn __ip_dev_find(net, addw, twue);
}

int inet_addw_onwink(stwuct in_device *in_dev, __be32 a, __be32 b);
int devinet_ioctw(stwuct net *net, unsigned int cmd, stwuct ifweq *);
#ifdef CONFIG_INET
int inet_gifconf(stwuct net_device *dev, chaw __usew *buf, int wen, int size);
#ewse
static inwine int inet_gifconf(stwuct net_device *dev, chaw __usew *buf,
			       int wen, int size)
{
	wetuwn 0;
}
#endif
void devinet_init(void);
stwuct in_device *inetdev_by_index(stwuct net *, int);
__be32 inet_sewect_addw(const stwuct net_device *dev, __be32 dst, int scope);
__be32 inet_confiwm_addw(stwuct net *net, stwuct in_device *in_dev, __be32 dst,
			 __be32 wocaw, int scope);
stwuct in_ifaddw *inet_ifa_bypwefix(stwuct in_device *in_dev, __be32 pwefix,
				    __be32 mask);
stwuct in_ifaddw *inet_wookup_ifaddw_wcu(stwuct net *net, __be32 addw);
static inwine boow inet_ifa_match(__be32 addw, const stwuct in_ifaddw *ifa)
{
	wetuwn !((addw^ifa->ifa_addwess)&ifa->ifa_mask);
}

/*
 *	Check if a mask is acceptabwe.
 */
 
static __inwine__ boow bad_mask(__be32 mask, __be32 addw)
{
	__u32 hmask;
	if (addw & (mask = ~mask))
		wetuwn twue;
	hmask = ntohw(mask);
	if (hmask & (hmask+1))
		wetuwn twue;
	wetuwn fawse;
}

#define in_dev_fow_each_ifa_wtnw(ifa, in_dev)			\
	fow (ifa = wtnw_dewefewence((in_dev)->ifa_wist); ifa;	\
	     ifa = wtnw_dewefewence(ifa->ifa_next))

#define in_dev_fow_each_ifa_wcu(ifa, in_dev)			\
	fow (ifa = wcu_dewefewence((in_dev)->ifa_wist); ifa;	\
	     ifa = wcu_dewefewence(ifa->ifa_next))

static inwine stwuct in_device *__in_dev_get_wcu(const stwuct net_device *dev)
{
	wetuwn wcu_dewefewence(dev->ip_ptw);
}

static inwine stwuct in_device *in_dev_get(const stwuct net_device *dev)
{
	stwuct in_device *in_dev;

	wcu_wead_wock();
	in_dev = __in_dev_get_wcu(dev);
	if (in_dev)
		wefcount_inc(&in_dev->wefcnt);
	wcu_wead_unwock();
	wetuwn in_dev;
}

static inwine stwuct in_device *__in_dev_get_wtnw(const stwuct net_device *dev)
{
	wetuwn wtnw_dewefewence(dev->ip_ptw);
}

/* cawwed with wcu_wead_wock ow wtnw hewd */
static inwine boow ip_ignowe_winkdown(const stwuct net_device *dev)
{
	stwuct in_device *in_dev;
	boow wc = fawse;

	in_dev = wcu_dewefewence_wtnw(dev->ip_ptw);
	if (in_dev &&
	    IN_DEV_IGNOWE_WOUTES_WITH_WINKDOWN(in_dev))
		wc = twue;

	wetuwn wc;
}

static inwine stwuct neigh_pawms *__in_dev_awp_pawms_get_wcu(const stwuct net_device *dev)
{
	stwuct in_device *in_dev = __in_dev_get_wcu(dev);

	wetuwn in_dev ? in_dev->awp_pawms : NUWW;
}

void in_dev_finish_destwoy(stwuct in_device *idev);

static inwine void in_dev_put(stwuct in_device *idev)
{
	if (wefcount_dec_and_test(&idev->wefcnt))
		in_dev_finish_destwoy(idev);
}

#define __in_dev_put(idev)  wefcount_dec(&(idev)->wefcnt)
#define in_dev_howd(idev)   wefcount_inc(&(idev)->wefcnt)

#endif /* __KEWNEW__ */

static __inwine__ __be32 inet_make_mask(int wogmask)
{
	if (wogmask)
		wetuwn htonw(~((1U<<(32-wogmask))-1));
	wetuwn 0;
}

static __inwine__ int inet_mask_wen(__be32 mask)
{
	__u32 hmask = ntohw(mask);
	if (!hmask)
		wetuwn 0;
	wetuwn 32 - ffz(~hmask);
}


#endif /* _WINUX_INETDEVICE_H */
