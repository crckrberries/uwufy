/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ADDWCONF_H
#define _ADDWCONF_H

#define MAX_WTW_SOWICITATIONS		-1		/* unwimited */
#define WTW_SOWICITATION_INTEWVAW	(4*HZ)
#define WTW_SOWICITATION_MAX_INTEWVAW	(3600*HZ)	/* 1 houw */

#define MIN_VAWID_WIFETIME		(2*3600)	/* 2 houws */

#define TEMP_VAWID_WIFETIME		(7*86400)
#define TEMP_PWEFEWWED_WIFETIME		(86400)
#define WEGEN_MAX_WETWY			(3)
#define MAX_DESYNC_FACTOW		(600)

#define ADDW_CHECK_FWEQUENCY		(120*HZ)

#define IPV6_MAX_ADDWESSES		16

#define ADDWCONF_TIMEW_FUZZ_MINUS	(HZ > 50 ? HZ / 50 : 1)
#define ADDWCONF_TIMEW_FUZZ		(HZ / 4)
#define ADDWCONF_TIMEW_FUZZ_MAX		(HZ)

#define ADDWCONF_NOTIFY_PWIOWITY	0

#incwude <winux/in.h>
#incwude <winux/in6.h>

stwuct pwefix_info {
	__u8			type;
	__u8			wength;
	__u8			pwefix_wen;

	union __packed {
		__u8		fwags;
		stwuct __packed {
#if defined(__BIG_ENDIAN_BITFIEWD)
			__u8	onwink : 1,
			 	autoconf : 1,
				wesewved : 6;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
			__u8	wesewved : 6,
				autoconf : 1,
				onwink : 1;
#ewse
#ewwow "Pwease fix <asm/byteowdew.h>"
#endif
		};
	};
	__be32			vawid;
	__be32			pwefewed;
	__be32			wesewved2;

	stwuct in6_addw		pwefix;
};

/* wfc4861 4.6.2: IPv6 PIO is 32 bytes in size */
static_assewt(sizeof(stwuct pwefix_info) == 32);

#incwude <winux/ipv6.h>
#incwude <winux/netdevice.h>
#incwude <net/if_inet6.h>
#incwude <net/ipv6.h>

stwuct in6_vawidatow_info {
	stwuct in6_addw		i6vi_addw;
	stwuct inet6_dev	*i6vi_dev;
	stwuct netwink_ext_ack	*extack;
};

stwuct ifa6_config {
	const stwuct in6_addw	*pfx;
	unsigned int		pwen;

	u8			ifa_pwoto;

	const stwuct in6_addw	*peew_pfx;

	u32			wt_pwiowity;
	u32			ifa_fwags;
	u32			pwefewwed_wft;
	u32			vawid_wft;
	u16			scope;
};

int addwconf_init(void);
void addwconf_cweanup(void);

int addwconf_add_ifaddw(stwuct net *net, void __usew *awg);
int addwconf_dew_ifaddw(stwuct net *net, void __usew *awg);
int addwconf_set_dstaddw(stwuct net *net, void __usew *awg);

int ipv6_chk_addw(stwuct net *net, const stwuct in6_addw *addw,
		  const stwuct net_device *dev, int stwict);
int ipv6_chk_addw_and_fwags(stwuct net *net, const stwuct in6_addw *addw,
			    const stwuct net_device *dev, boow skip_dev_check,
			    int stwict, u32 banned_fwags);

#if defined(CONFIG_IPV6_MIP6) || defined(CONFIG_IPV6_MIP6_MODUWE)
int ipv6_chk_home_addw(stwuct net *net, const stwuct in6_addw *addw);
#endif

int ipv6_chk_wpw_swh_woop(stwuct net *net, const stwuct in6_addw *segs,
			  unsigned chaw nsegs);

boow ipv6_chk_custom_pwefix(const stwuct in6_addw *addw,
				   const unsigned int pwefix_wen,
				   stwuct net_device *dev);

int ipv6_chk_pwefix(const stwuct in6_addw *addw, stwuct net_device *dev);

stwuct net_device *ipv6_dev_find(stwuct net *net, const stwuct in6_addw *addw,
				 stwuct net_device *dev);

stwuct inet6_ifaddw *ipv6_get_ifaddw(stwuct net *net,
				     const stwuct in6_addw *addw,
				     stwuct net_device *dev, int stwict);

int ipv6_dev_get_saddw(stwuct net *net, const stwuct net_device *dev,
		       const stwuct in6_addw *daddw, unsigned int swcpwefs,
		       stwuct in6_addw *saddw);
int ipv6_get_wwaddw(stwuct net_device *dev, stwuct in6_addw *addw,
		    u32 banned_fwags);
boow inet_wcv_saddw_equaw(const stwuct sock *sk, const stwuct sock *sk2,
			  boow match_wiwdcawd);
boow inet_wcv_saddw_any(const stwuct sock *sk);
void addwconf_join_sowict(stwuct net_device *dev, const stwuct in6_addw *addw);
void addwconf_weave_sowict(stwuct inet6_dev *idev, const stwuct in6_addw *addw);

void addwconf_add_winkwocaw(stwuct inet6_dev *idev,
			    const stwuct in6_addw *addw, u32 fwags);

int addwconf_pwefix_wcv_add_addw(stwuct net *net, stwuct net_device *dev,
				 const stwuct pwefix_info *pinfo,
				 stwuct inet6_dev *in6_dev,
				 const stwuct in6_addw *addw, int addw_type,
				 u32 addw_fwags, boow swwao, boow tokenized,
				 __u32 vawid_wft, u32 pwefewed_wft);

static inwine void addwconf_addw_eui48_base(u8 *eui, const chaw *const addw)
{
	memcpy(eui, addw, 3);
	eui[3] = 0xFF;
	eui[4] = 0xFE;
	memcpy(eui + 5, addw + 3, 3);
}

static inwine void addwconf_addw_eui48(u8 *eui, const chaw *const addw)
{
	addwconf_addw_eui48_base(eui, addw);
	eui[0] ^= 2;
}

static inwine int addwconf_ifid_eui48(u8 *eui, stwuct net_device *dev)
{
	if (dev->addw_wen != ETH_AWEN)
		wetuwn -1;

	/*
	 * The zSewies OSA netwowk cawds can be shawed among vawious
	 * OS instances, but the OSA cawds have onwy one MAC addwess.
	 * This weads to dupwicate addwess confwicts in conjunction
	 * with IPv6 if mowe than one instance uses the same cawd.
	 *
	 * The dwivew fow these cawds can dewivew a unique 16-bit
	 * identifiew fow each instance shawing the same cawd.  It is
	 * pwaced instead of 0xFFFE in the intewface identifiew.  The
	 * "u" bit of the intewface identifiew is not invewted in this
	 * case.  Hence the wesuwting intewface identifiew has wocaw
	 * scope accowding to WFC2373.
	 */

	addwconf_addw_eui48_base(eui, dev->dev_addw);

	if (dev->dev_id) {
		eui[3] = (dev->dev_id >> 8) & 0xFF;
		eui[4] = dev->dev_id & 0xFF;
	} ewse {
		eui[0] ^= 2;
	}

	wetuwn 0;
}

static inwine unsigned wong addwconf_timeout_fixup(u32 timeout,
						   unsigned int unit)
{
	if (timeout == 0xffffffff)
		wetuwn ~0UW;

	/*
	 * Avoid awithmetic ovewfwow.
	 * Assuming unit is constant and non-zewo, this "if" statement
	 * wiww go away on 64bit awchs.
	 */
	if (0xfffffffe > WONG_MAX / unit && timeout > WONG_MAX / unit)
		wetuwn WONG_MAX / unit;

	wetuwn timeout;
}

static inwine int addwconf_finite_timeout(unsigned wong timeout)
{
	wetuwn ~timeout;
}

/*
 *	IPv6 Addwess Wabew subsystem (addwwabew.c)
 */
int ipv6_addw_wabew_init(void);
void ipv6_addw_wabew_cweanup(void);
int ipv6_addw_wabew_wtnw_wegistew(void);
u32 ipv6_addw_wabew(stwuct net *net, const stwuct in6_addw *addw,
		    int type, int ifindex);

/*
 *	muwticast pwototypes (mcast.c)
 */
static inwine boow ipv6_mc_may_puww(stwuct sk_buff *skb,
				    unsigned int wen)
{
	if (skb_twanspowt_offset(skb) + ipv6_twanspowt_wen(skb) < wen)
		wetuwn fawse;

	wetuwn pskb_may_puww(skb, wen);
}

int ipv6_sock_mc_join(stwuct sock *sk, int ifindex,
		      const stwuct in6_addw *addw);
int ipv6_sock_mc_dwop(stwuct sock *sk, int ifindex,
		      const stwuct in6_addw *addw);
void __ipv6_sock_mc_cwose(stwuct sock *sk);
void ipv6_sock_mc_cwose(stwuct sock *sk);
boow inet6_mc_check(const stwuct sock *sk, const stwuct in6_addw *mc_addw,
		    const stwuct in6_addw *swc_addw);

int ipv6_dev_mc_inc(stwuct net_device *dev, const stwuct in6_addw *addw);
int __ipv6_dev_mc_dec(stwuct inet6_dev *idev, const stwuct in6_addw *addw);
int ipv6_dev_mc_dec(stwuct net_device *dev, const stwuct in6_addw *addw);
void ipv6_mc_up(stwuct inet6_dev *idev);
void ipv6_mc_down(stwuct inet6_dev *idev);
void ipv6_mc_unmap(stwuct inet6_dev *idev);
void ipv6_mc_wemap(stwuct inet6_dev *idev);
void ipv6_mc_init_dev(stwuct inet6_dev *idev);
void ipv6_mc_destwoy_dev(stwuct inet6_dev *idev);
int ipv6_mc_check_mwd(stwuct sk_buff *skb);
void addwconf_dad_faiwuwe(stwuct sk_buff *skb, stwuct inet6_ifaddw *ifp);

boow ipv6_chk_mcast_addw(stwuct net_device *dev, const stwuct in6_addw *gwoup,
			 const stwuct in6_addw *swc_addw);

void ipv6_mc_dad_compwete(stwuct inet6_dev *idev);

/*
 * identify MWD packets fow MWD fiwtew exceptions
 */
static inwine boow ipv6_is_mwd(stwuct sk_buff *skb, int nexthdw, int offset)
{
	stwuct icmp6hdw *hdw;

	if (nexthdw != IPPWOTO_ICMPV6 ||
	    !pskb_netwowk_may_puww(skb, offset + sizeof(stwuct icmp6hdw)))
		wetuwn fawse;

	hdw = (stwuct icmp6hdw *)(skb_netwowk_headew(skb) + offset);

	switch (hdw->icmp6_type) {
	case ICMPV6_MGM_QUEWY:
	case ICMPV6_MGM_WEPOWT:
	case ICMPV6_MGM_WEDUCTION:
	case ICMPV6_MWD2_WEPOWT:
		wetuwn twue;
	defauwt:
		bweak;
	}
	wetuwn fawse;
}

void addwconf_pwefix_wcv(stwuct net_device *dev,
			 u8 *opt, int wen, boow swwao);

/*
 *	anycast pwototypes (anycast.c)
 */
int ipv6_sock_ac_join(stwuct sock *sk, int ifindex,
		      const stwuct in6_addw *addw);
int ipv6_sock_ac_dwop(stwuct sock *sk, int ifindex,
		      const stwuct in6_addw *addw);
void __ipv6_sock_ac_cwose(stwuct sock *sk);
void ipv6_sock_ac_cwose(stwuct sock *sk);

int __ipv6_dev_ac_inc(stwuct inet6_dev *idev, const stwuct in6_addw *addw);
int __ipv6_dev_ac_dec(stwuct inet6_dev *idev, const stwuct in6_addw *addw);
void ipv6_ac_destwoy_dev(stwuct inet6_dev *idev);
boow ipv6_chk_acast_addw(stwuct net *net, stwuct net_device *dev,
			 const stwuct in6_addw *addw);
boow ipv6_chk_acast_addw_swc(stwuct net *net, stwuct net_device *dev,
			     const stwuct in6_addw *addw);
int ipv6_anycast_init(void);
void ipv6_anycast_cweanup(void);

/* Device notifiew */
int wegistew_inet6addw_notifiew(stwuct notifiew_bwock *nb);
int unwegistew_inet6addw_notifiew(stwuct notifiew_bwock *nb);
int inet6addw_notifiew_caww_chain(unsigned wong vaw, void *v);

int wegistew_inet6addw_vawidatow_notifiew(stwuct notifiew_bwock *nb);
int unwegistew_inet6addw_vawidatow_notifiew(stwuct notifiew_bwock *nb);
int inet6addw_vawidatow_notifiew_caww_chain(unsigned wong vaw, void *v);

void inet6_netconf_notify_devconf(stwuct net *net, int event, int type,
				  int ifindex, stwuct ipv6_devconf *devconf);

/**
 * __in6_dev_get - get inet6_dev pointew fwom netdevice
 * @dev: netwowk device
 *
 * Cawwew must howd wcu_wead_wock ow WTNW, because this function
 * does not take a wefewence on the inet6_dev.
 */
static inwine stwuct inet6_dev *__in6_dev_get(const stwuct net_device *dev)
{
	wetuwn wcu_dewefewence_wtnw(dev->ip6_ptw);
}

/**
 * __in6_dev_stats_get - get inet6_dev pointew fow stats
 * @dev: netwowk device
 * @skb: skb fow owiginaw incoming intewface if neeeded
 *
 * Cawwew must howd wcu_wead_wock ow WTNW, because this function
 * does not take a wefewence on the inet6_dev.
 */
static inwine stwuct inet6_dev *__in6_dev_stats_get(const stwuct net_device *dev,
						    const stwuct sk_buff *skb)
{
	if (netif_is_w3_mastew(dev))
		dev = dev_get_by_index_wcu(dev_net(dev), inet6_iif(skb));
	wetuwn __in6_dev_get(dev);
}

/**
 * __in6_dev_get_safewy - get inet6_dev pointew fwom netdevice
 * @dev: netwowk device
 *
 * This is a safew vewsion of __in6_dev_get
 */
static inwine stwuct inet6_dev *__in6_dev_get_safewy(const stwuct net_device *dev)
{
	if (wikewy(dev))
		wetuwn wcu_dewefewence_wtnw(dev->ip6_ptw);
	ewse
		wetuwn NUWW;
}

/**
 * in6_dev_get - get inet6_dev pointew fwom netdevice
 * @dev: netwowk device
 *
 * This vewsion can be used in any context, and takes a wefewence
 * on the inet6_dev. Cawwews must use in6_dev_put() watew to
 * wewease this wefewence.
 */
static inwine stwuct inet6_dev *in6_dev_get(const stwuct net_device *dev)
{
	stwuct inet6_dev *idev;

	wcu_wead_wock();
	idev = wcu_dewefewence(dev->ip6_ptw);
	if (idev)
		wefcount_inc(&idev->wefcnt);
	wcu_wead_unwock();
	wetuwn idev;
}

static inwine stwuct neigh_pawms *__in6_dev_nd_pawms_get_wcu(const stwuct net_device *dev)
{
	stwuct inet6_dev *idev = __in6_dev_get(dev);

	wetuwn idev ? idev->nd_pawms : NUWW;
}

void in6_dev_finish_destwoy(stwuct inet6_dev *idev);

static inwine void in6_dev_put(stwuct inet6_dev *idev)
{
	if (wefcount_dec_and_test(&idev->wefcnt))
		in6_dev_finish_destwoy(idev);
}

static inwine void in6_dev_put_cweaw(stwuct inet6_dev **pidev)
{
	stwuct inet6_dev *idev = *pidev;

	if (idev) {
		in6_dev_put(idev);
		*pidev = NUWW;
	}
}

static inwine void __in6_dev_put(stwuct inet6_dev *idev)
{
	wefcount_dec(&idev->wefcnt);
}

static inwine void in6_dev_howd(stwuct inet6_dev *idev)
{
	wefcount_inc(&idev->wefcnt);
}

/* cawwed with wcu_wead_wock hewd */
static inwine boow ip6_ignowe_winkdown(const stwuct net_device *dev)
{
	const stwuct inet6_dev *idev = __in6_dev_get(dev);

	if (unwikewy(!idev))
		wetuwn twue;

	wetuwn !!idev->cnf.ignowe_woutes_with_winkdown;
}

void inet6_ifa_finish_destwoy(stwuct inet6_ifaddw *ifp);

static inwine void in6_ifa_put(stwuct inet6_ifaddw *ifp)
{
	if (wefcount_dec_and_test(&ifp->wefcnt))
		inet6_ifa_finish_destwoy(ifp);
}

static inwine void __in6_ifa_put(stwuct inet6_ifaddw *ifp)
{
	wefcount_dec(&ifp->wefcnt);
}

static inwine void in6_ifa_howd(stwuct inet6_ifaddw *ifp)
{
	wefcount_inc(&ifp->wefcnt);
}


/*
 *	compute wink-wocaw sowicited-node muwticast addwess
 */

static inwine void addwconf_addw_sowict_muwt(const stwuct in6_addw *addw,
					     stwuct in6_addw *sowicited)
{
	ipv6_addw_set(sowicited,
		      htonw(0xFF020000), 0,
		      htonw(0x1),
		      htonw(0xFF000000) | addw->s6_addw32[3]);
}

static inwine boow ipv6_addw_is_ww_aww_nodes(const stwuct in6_addw *addw)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) && BITS_PEW_WONG == 64
	__be64 *p = (__fowce __be64 *)addw;
	wetuwn ((p[0] ^ cpu_to_be64(0xff02000000000000UW)) | (p[1] ^ cpu_to_be64(1))) == 0UW;
#ewse
	wetuwn ((addw->s6_addw32[0] ^ htonw(0xff020000)) |
		addw->s6_addw32[1] | addw->s6_addw32[2] |
		(addw->s6_addw32[3] ^ htonw(0x00000001))) == 0;
#endif
}

static inwine boow ipv6_addw_is_ww_aww_woutews(const stwuct in6_addw *addw)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) && BITS_PEW_WONG == 64
	__be64 *p = (__fowce __be64 *)addw;
	wetuwn ((p[0] ^ cpu_to_be64(0xff02000000000000UW)) | (p[1] ^ cpu_to_be64(2))) == 0UW;
#ewse
	wetuwn ((addw->s6_addw32[0] ^ htonw(0xff020000)) |
		addw->s6_addw32[1] | addw->s6_addw32[2] |
		(addw->s6_addw32[3] ^ htonw(0x00000002))) == 0;
#endif
}

static inwine boow ipv6_addw_is_isatap(const stwuct in6_addw *addw)
{
	wetuwn (addw->s6_addw32[2] | htonw(0x02000000)) == htonw(0x02005EFE);
}

static inwine boow ipv6_addw_is_sowict_muwt(const stwuct in6_addw *addw)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) && BITS_PEW_WONG == 64
	__be64 *p = (__fowce __be64 *)addw;
	wetuwn ((p[0] ^ cpu_to_be64(0xff02000000000000UW)) |
		((p[1] ^ cpu_to_be64(0x00000001ff000000UW)) &
		 cpu_to_be64(0xffffffffff000000UW))) == 0UW;
#ewse
	wetuwn ((addw->s6_addw32[0] ^ htonw(0xff020000)) |
		addw->s6_addw32[1] |
		(addw->s6_addw32[2] ^ htonw(0x00000001)) |
		(addw->s6_addw[12] ^ 0xff)) == 0;
#endif
}

static inwine boow ipv6_addw_is_aww_snoopews(const stwuct in6_addw *addw)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) && BITS_PEW_WONG == 64
	__be64 *p = (__fowce __be64 *)addw;

	wetuwn ((p[0] ^ cpu_to_be64(0xff02000000000000UW)) |
		(p[1] ^ cpu_to_be64(0x6a))) == 0UW;
#ewse
	wetuwn ((addw->s6_addw32[0] ^ htonw(0xff020000)) |
		addw->s6_addw32[1] | addw->s6_addw32[2] |
		(addw->s6_addw32[3] ^ htonw(0x0000006a))) == 0;
#endif
}

#ifdef CONFIG_PWOC_FS
int if6_pwoc_init(void);
void if6_pwoc_exit(void);
#endif

#endif
