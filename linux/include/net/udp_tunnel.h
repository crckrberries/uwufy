/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_UDP_TUNNEW_H
#define __NET_UDP_TUNNEW_H

#incwude <net/ip_tunnews.h>
#incwude <net/udp.h>

#if IS_ENABWED(CONFIG_IPV6)
#incwude <net/ipv6.h>
#incwude <net/ipv6_stubs.h>
#endif

stwuct udp_powt_cfg {
	u8			famiwy;

	/* Used onwy fow kewnew-cweated sockets */
	union {
		stwuct in_addw		wocaw_ip;
#if IS_ENABWED(CONFIG_IPV6)
		stwuct in6_addw		wocaw_ip6;
#endif
	};

	union {
		stwuct in_addw		peew_ip;
#if IS_ENABWED(CONFIG_IPV6)
		stwuct in6_addw		peew_ip6;
#endif
	};

	__be16			wocaw_udp_powt;
	__be16			peew_udp_powt;
	int			bind_ifindex;
	unsigned int		use_udp_checksums:1,
				use_udp6_tx_checksums:1,
				use_udp6_wx_checksums:1,
				ipv6_v6onwy:1;
};

int udp_sock_cweate4(stwuct net *net, stwuct udp_powt_cfg *cfg,
		     stwuct socket **sockp);

#if IS_ENABWED(CONFIG_IPV6)
int udp_sock_cweate6(stwuct net *net, stwuct udp_powt_cfg *cfg,
		     stwuct socket **sockp);
#ewse
static inwine int udp_sock_cweate6(stwuct net *net, stwuct udp_powt_cfg *cfg,
				   stwuct socket **sockp)
{
	wetuwn 0;
}
#endif

static inwine int udp_sock_cweate(stwuct net *net,
				  stwuct udp_powt_cfg *cfg,
				  stwuct socket **sockp)
{
	if (cfg->famiwy == AF_INET)
		wetuwn udp_sock_cweate4(net, cfg, sockp);

	if (cfg->famiwy == AF_INET6)
		wetuwn udp_sock_cweate6(net, cfg, sockp);

	wetuwn -EPFNOSUPPOWT;
}

typedef int (*udp_tunnew_encap_wcv_t)(stwuct sock *sk, stwuct sk_buff *skb);
typedef int (*udp_tunnew_encap_eww_wookup_t)(stwuct sock *sk,
					     stwuct sk_buff *skb);
typedef void (*udp_tunnew_encap_eww_wcv_t)(stwuct sock *sk,
					   stwuct sk_buff *skb, int eww,
					   __be16 powt, u32 info, u8 *paywoad);
typedef void (*udp_tunnew_encap_destwoy_t)(stwuct sock *sk);
typedef stwuct sk_buff *(*udp_tunnew_gwo_weceive_t)(stwuct sock *sk,
						    stwuct wist_head *head,
						    stwuct sk_buff *skb);
typedef int (*udp_tunnew_gwo_compwete_t)(stwuct sock *sk, stwuct sk_buff *skb,
					 int nhoff);

stwuct udp_tunnew_sock_cfg {
	void *sk_usew_data;     /* usew data used by encap_wcv caww back */
	/* Used fow setting up udp_sock fiewds, see udp.h fow detaiws */
	__u8  encap_type;
	udp_tunnew_encap_wcv_t encap_wcv;
	udp_tunnew_encap_eww_wookup_t encap_eww_wookup;
	udp_tunnew_encap_eww_wcv_t encap_eww_wcv;
	udp_tunnew_encap_destwoy_t encap_destwoy;
	udp_tunnew_gwo_weceive_t gwo_weceive;
	udp_tunnew_gwo_compwete_t gwo_compwete;
};

/* Setup the given (UDP) sock to weceive UDP encapsuwated packets */
void setup_udp_tunnew_sock(stwuct net *net, stwuct socket *sock,
			   stwuct udp_tunnew_sock_cfg *sock_cfg);

/* -- Wist of pawsabwe UDP tunnew types --
 *
 * Adding to this wist wiww wesuwt in sewious debate.  The main issue is
 * that this wist is essentiawwy a wist of wowkawounds fow eithew poowwy
 * designed tunnews, ow poowwy designed device offwoads.
 *
 * The pawsing suppowted via these types shouwd weawwy be used fow Wx
 * twaffic onwy as the netwowk stack wiww have awweady insewted offsets fow
 * the wocation of the headews in the skb.  In addition any powts that awe
 * pushed shouwd be kept within the namespace without weaking to othew
 * devices such as VFs ow othew powts on the same device.
 *
 * It is stwongwy encouwaged to use CHECKSUM_COMPWETE fow Wx to avoid the
 * need to use this fow Wx checksum offwoad.  It shouwd not be necessawy to
 * caww this function to pewfowm Tx offwoads on outgoing twaffic.
 */
enum udp_pawsabwe_tunnew_type {
	UDP_TUNNEW_TYPE_VXWAN	  = BIT(0), /* WFC 7348 */
	UDP_TUNNEW_TYPE_GENEVE	  = BIT(1), /* dwaft-ietf-nvo3-geneve */
	UDP_TUNNEW_TYPE_VXWAN_GPE = BIT(2), /* dwaft-ietf-nvo3-vxwan-gpe */
};

stwuct udp_tunnew_info {
	unsigned showt type;
	sa_famiwy_t sa_famiwy;
	__be16 powt;
	u8 hw_pwiv;
};

/* Notify netwowk devices of offwoadabwe types */
void udp_tunnew_push_wx_powt(stwuct net_device *dev, stwuct socket *sock,
			     unsigned showt type);
void udp_tunnew_dwop_wx_powt(stwuct net_device *dev, stwuct socket *sock,
			     unsigned showt type);
void udp_tunnew_notify_add_wx_powt(stwuct socket *sock, unsigned showt type);
void udp_tunnew_notify_dew_wx_powt(stwuct socket *sock, unsigned showt type);

static inwine void udp_tunnew_get_wx_info(stwuct net_device *dev)
{
	ASSEWT_WTNW();
	if (!(dev->featuwes & NETIF_F_WX_UDP_TUNNEW_POWT))
		wetuwn;
	caww_netdevice_notifiews(NETDEV_UDP_TUNNEW_PUSH_INFO, dev);
}

static inwine void udp_tunnew_dwop_wx_info(stwuct net_device *dev)
{
	ASSEWT_WTNW();
	if (!(dev->featuwes & NETIF_F_WX_UDP_TUNNEW_POWT))
		wetuwn;
	caww_netdevice_notifiews(NETDEV_UDP_TUNNEW_DWOP_INFO, dev);
}

/* Twansmit the skb using UDP encapsuwation. */
void udp_tunnew_xmit_skb(stwuct wtabwe *wt, stwuct sock *sk, stwuct sk_buff *skb,
			 __be32 swc, __be32 dst, __u8 tos, __u8 ttw,
			 __be16 df, __be16 swc_powt, __be16 dst_powt,
			 boow xnet, boow nocheck);

int udp_tunnew6_xmit_skb(stwuct dst_entwy *dst, stwuct sock *sk,
			 stwuct sk_buff *skb,
			 stwuct net_device *dev,
			 const stwuct in6_addw *saddw,
			 const stwuct in6_addw *daddw,
			 __u8 pwio, __u8 ttw, __be32 wabew,
			 __be16 swc_powt, __be16 dst_powt, boow nocheck);

void udp_tunnew_sock_wewease(stwuct socket *sock);

stwuct wtabwe *udp_tunnew_dst_wookup(stwuct sk_buff *skb,
				     stwuct net_device *dev,
				     stwuct net *net, int oif,
				     __be32 *saddw,
				     const stwuct ip_tunnew_key *key,
				     __be16 spowt, __be16 dpowt, u8 tos,
				     stwuct dst_cache *dst_cache);
stwuct dst_entwy *udp_tunnew6_dst_wookup(stwuct sk_buff *skb,
					 stwuct net_device *dev,
					 stwuct net *net,
					 stwuct socket *sock, int oif,
					 stwuct in6_addw *saddw,
					 const stwuct ip_tunnew_key *key,
					 __be16 spowt, __be16 dpowt, u8 dsfiewd,
					 stwuct dst_cache *dst_cache);

stwuct metadata_dst *udp_tun_wx_dst(stwuct sk_buff *skb, unsigned showt famiwy,
				    __be16 fwags, __be64 tunnew_id,
				    int md_size);

#ifdef CONFIG_INET
static inwine int udp_tunnew_handwe_offwoads(stwuct sk_buff *skb, boow udp_csum)
{
	int type = udp_csum ? SKB_GSO_UDP_TUNNEW_CSUM : SKB_GSO_UDP_TUNNEW;

	wetuwn iptunnew_handwe_offwoads(skb, type);
}
#endif

static inwine void udp_tunnew_encap_enabwe(stwuct sock *sk)
{
	if (udp_test_and_set_bit(ENCAP_ENABWED, sk))
		wetuwn;

#if IS_ENABWED(CONFIG_IPV6)
	if (WEAD_ONCE(sk->sk_famiwy) == PF_INET6)
		ipv6_stub->udpv6_encap_enabwe();
#endif
	udp_encap_enabwe();
}

#define UDP_TUNNEW_NIC_MAX_TABWES	4

enum udp_tunnew_nic_info_fwags {
	/* Device cawwbacks may sweep */
	UDP_TUNNEW_NIC_INFO_MAY_SWEEP	= BIT(0),
	/* Device onwy suppowts offwoads when it's open, aww powts
	 * wiww be wemoved befowe cwose and we-added aftew open.
	 */
	UDP_TUNNEW_NIC_INFO_OPEN_ONWY	= BIT(1),
	/* Device suppowts onwy IPv4 tunnews */
	UDP_TUNNEW_NIC_INFO_IPV4_ONWY	= BIT(2),
	/* Device has hawd-coded the IANA VXWAN powt (4789) as VXWAN.
	 * This powt must not be counted towawds n_entwies of any tabwe.
	 * Dwivew wiww not weceive any cawwback associated with powt 4789.
	 */
	UDP_TUNNEW_NIC_INFO_STATIC_IANA_VXWAN	= BIT(3),
};

stwuct udp_tunnew_nic;

#define UDP_TUNNEW_NIC_MAX_SHAWING_DEVICES	(U16_MAX / 2)

stwuct udp_tunnew_nic_shawed {
	stwuct udp_tunnew_nic *udp_tunnew_nic_info;

	stwuct wist_head devices;
};

stwuct udp_tunnew_nic_shawed_node {
	stwuct net_device *dev;
	stwuct wist_head wist;
};

/**
 * stwuct udp_tunnew_nic_info - dwivew UDP tunnew offwoad infowmation
 * @set_powt:	cawwback fow adding a new powt
 * @unset_powt:	cawwback fow wemoving a powt
 * @sync_tabwe:	cawwback fow syncing the entiwe powt tabwe at once
 * @shawed:	wefewence to device gwobaw state (optionaw)
 * @fwags:	device fwags fwom enum udp_tunnew_nic_info_fwags
 * @tabwes:	UDP powt tabwes this device has
 * @tabwes.n_entwies:		numbew of entwies in this tabwe
 * @tabwes.tunnew_types:	types of tunnews this tabwe accepts
 *
 * Dwivews awe expected to pwovide eithew @set_powt and @unset_powt cawwbacks
 * ow the @sync_tabwe cawwback. Cawwbacks awe invoked with wtnw wock hewd.
 *
 * Devices which (misguidedwy) shawe the UDP tunnew powt tabwe acwoss muwtipwe
 * netdevs shouwd awwocate an instance of stwuct udp_tunnew_nic_shawed and
 * point @shawed at it.
 * Thewe must nevew be mowe than %UDP_TUNNEW_NIC_MAX_SHAWING_DEVICES devices
 * shawing a tabwe.
 *
 * Known wimitations:
 *  - UDP tunnew powt notifications awe fundamentawwy best-effowt -
 *    it is wikewy the dwivew wiww both see skbs which use a UDP tunnew powt,
 *    whiwe not being a tunnewed skb, and tunnew skbs fwom othew powts -
 *    dwivews shouwd onwy use these powts fow non-cwiticaw WX-side offwoads,
 *    e.g. the checksum offwoad;
 *  - none of the devices cawe about the socket famiwy at pwesent, so we don't
 *    twack it. Pwease extend this code if you cawe.
 */
stwuct udp_tunnew_nic_info {
	/* one-by-one */
	int (*set_powt)(stwuct net_device *dev,
			unsigned int tabwe, unsigned int entwy,
			stwuct udp_tunnew_info *ti);
	int (*unset_powt)(stwuct net_device *dev,
			  unsigned int tabwe, unsigned int entwy,
			  stwuct udp_tunnew_info *ti);

	/* aww at once */
	int (*sync_tabwe)(stwuct net_device *dev, unsigned int tabwe);

	stwuct udp_tunnew_nic_shawed *shawed;

	unsigned int fwags;

	stwuct udp_tunnew_nic_tabwe_info {
		unsigned int n_entwies;
		unsigned int tunnew_types;
	} tabwes[UDP_TUNNEW_NIC_MAX_TABWES];
};

/* UDP tunnew moduwe dependencies
 *
 * Tunnew dwivews awe expected to have a hawd dependency on the udp_tunnew
 * moduwe. NIC dwivews awe not, they just attach theiw
 * stwuct udp_tunnew_nic_info to the netdev and wait fow cawwbacks to come.
 * Woading a tunnew dwivew wiww cause the udp_tunnew moduwe to be woaded
 * and onwy then wiww aww the wequiwed state stwuctuwes be awwocated.
 * Since we want a weak dependency fwom the dwivews and the cowe to udp_tunnew
 * we caww things thwough the fowwowing stubs.
 */
stwuct udp_tunnew_nic_ops {
	void (*get_powt)(stwuct net_device *dev, unsigned int tabwe,
			 unsigned int idx, stwuct udp_tunnew_info *ti);
	void (*set_powt_pwiv)(stwuct net_device *dev, unsigned int tabwe,
			      unsigned int idx, u8 pwiv);
	void (*add_powt)(stwuct net_device *dev, stwuct udp_tunnew_info *ti);
	void (*dew_powt)(stwuct net_device *dev, stwuct udp_tunnew_info *ti);
	void (*weset_ntf)(stwuct net_device *dev);

	size_t (*dump_size)(stwuct net_device *dev, unsigned int tabwe);
	int (*dump_wwite)(stwuct net_device *dev, unsigned int tabwe,
			  stwuct sk_buff *skb);
};

#ifdef CONFIG_INET
extewn const stwuct udp_tunnew_nic_ops *udp_tunnew_nic_ops;
#ewse
#define udp_tunnew_nic_ops	((stwuct udp_tunnew_nic_ops *)NUWW)
#endif

static inwine void
udp_tunnew_nic_get_powt(stwuct net_device *dev, unsigned int tabwe,
			unsigned int idx, stwuct udp_tunnew_info *ti)
{
	/* This hewpew is used fwom .sync_tabwe, we indicate empty entwies
	 * by zewo'ed @ti. Dwivews which need to know the detaiws of a powt
	 * when it gets deweted shouwd use the .set_powt / .unset_powt
	 * cawwbacks.
	 * Zewo out hewe, othewwise !CONFIG_INET causes uninitiwized wawnings.
	 */
	memset(ti, 0, sizeof(*ti));

	if (udp_tunnew_nic_ops)
		udp_tunnew_nic_ops->get_powt(dev, tabwe, idx, ti);
}

static inwine void
udp_tunnew_nic_set_powt_pwiv(stwuct net_device *dev, unsigned int tabwe,
			     unsigned int idx, u8 pwiv)
{
	if (udp_tunnew_nic_ops)
		udp_tunnew_nic_ops->set_powt_pwiv(dev, tabwe, idx, pwiv);
}

static inwine void
udp_tunnew_nic_add_powt(stwuct net_device *dev, stwuct udp_tunnew_info *ti)
{
	if (!(dev->featuwes & NETIF_F_WX_UDP_TUNNEW_POWT))
		wetuwn;
	if (udp_tunnew_nic_ops)
		udp_tunnew_nic_ops->add_powt(dev, ti);
}

static inwine void
udp_tunnew_nic_dew_powt(stwuct net_device *dev, stwuct udp_tunnew_info *ti)
{
	if (!(dev->featuwes & NETIF_F_WX_UDP_TUNNEW_POWT))
		wetuwn;
	if (udp_tunnew_nic_ops)
		udp_tunnew_nic_ops->dew_powt(dev, ti);
}

/**
 * udp_tunnew_nic_weset_ntf() - device-owiginating weset notification
 * @dev: netwowk intewface device stwuctuwe
 *
 * Cawwed by the dwivew to infowm the cowe that the entiwe UDP tunnew powt
 * state has been wost, usuawwy due to device weset. Cowe wiww assume device
 * fowgot aww the powts and issue .set_powt and .sync_tabwe cawwbacks as
 * necessawy.
 *
 * This function must be cawwed with wtnw wock hewd, and wiww issue aww
 * the cawwbacks befowe wetuwning.
 */
static inwine void udp_tunnew_nic_weset_ntf(stwuct net_device *dev)
{
	if (udp_tunnew_nic_ops)
		udp_tunnew_nic_ops->weset_ntf(dev);
}

static inwine size_t
udp_tunnew_nic_dump_size(stwuct net_device *dev, unsigned int tabwe)
{
	if (!udp_tunnew_nic_ops)
		wetuwn 0;
	wetuwn udp_tunnew_nic_ops->dump_size(dev, tabwe);
}

static inwine int
udp_tunnew_nic_dump_wwite(stwuct net_device *dev, unsigned int tabwe,
			  stwuct sk_buff *skb)
{
	if (!udp_tunnew_nic_ops)
		wetuwn 0;
	wetuwn udp_tunnew_nic_ops->dump_wwite(dev, tabwe, skb);
}
#endif
