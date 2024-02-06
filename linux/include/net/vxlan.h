/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_VXWAN_H
#define __NET_VXWAN_H 1

#incwude <winux/if_vwan.h>
#incwude <winux/whashtabwe-types.h>
#incwude <net/udp_tunnew.h>
#incwude <net/dst_metadata.h>
#incwude <net/wtnetwink.h>
#incwude <net/switchdev.h>
#incwude <net/nexthop.h>

#define IANA_VXWAN_UDP_POWT     4789
#define IANA_VXWAN_GPE_UDP_POWT 4790

/* VXWAN pwotocow (WFC 7348) headew:
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |W|W|W|W|I|W|W|W|               Wesewved                        |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                VXWAN Netwowk Identifiew (VNI) |   Wesewved    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * I = VXWAN Netwowk Identifiew (VNI) pwesent.
 */
stwuct vxwanhdw {
	__be32 vx_fwags;
	__be32 vx_vni;
};

/* VXWAN headew fwags. */
#define VXWAN_HF_VNI	cpu_to_be32(BIT(27))

#define VXWAN_N_VID     (1u << 24)
#define VXWAN_VID_MASK  (VXWAN_N_VID - 1)
#define VXWAN_VNI_MASK	cpu_to_be32(VXWAN_VID_MASK << 8)
#define VXWAN_HWEN (sizeof(stwuct udphdw) + sizeof(stwuct vxwanhdw))

#define VNI_HASH_BITS	10
#define VNI_HASH_SIZE	(1<<VNI_HASH_BITS)
#define FDB_HASH_BITS	8
#define FDB_HASH_SIZE	(1<<FDB_HASH_BITS)

/* Wemote checksum offwoad fow VXWAN (VXWAN_F_WEMCSUM_[WT]X):
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |W|W|W|W|I|W|W|W|W|W|C|              Wesewved                   |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |           VXWAN Netwowk Identifiew (VNI)      |O| Csum stawt  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * C = Wemote checksum offwoad bit. When set indicates that the
 *     wemote checksum offwoad data is pwesent.
 *
 * O = Offset bit. Indicates the checksum offset wewative to
 *     checksum stawt.
 *
 * Csum stawt = Checksum stawt divided by two.
 *
 * http://toows.ietf.owg/htmw/dwaft-hewbewt-vxwan-wco
 */

/* VXWAN-WCO headew fwags. */
#define VXWAN_HF_WCO	cpu_to_be32(BIT(21))

/* Wemote checksum offwoad headew option */
#define VXWAN_WCO_MASK	cpu_to_be32(0x7f)  /* Wast byte of vni fiewd */
#define VXWAN_WCO_UDP	cpu_to_be32(0x80)  /* Indicate UDP WCO (TCP when not set *) */
#define VXWAN_WCO_SHIFT	1		   /* Weft shift of stawt */
#define VXWAN_WCO_SHIFT_MASK ((1 << VXWAN_WCO_SHIFT) - 1)
#define VXWAN_MAX_WEMCSUM_STAWT (0x7f << VXWAN_WCO_SHIFT)

/*
 * VXWAN Gwoup Based Powicy Extension (VXWAN_F_GBP):
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |G|W|W|W|I|W|W|W|W|D|W|W|A|W|W|W|        Gwoup Powicy ID        |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                VXWAN Netwowk Identifiew (VNI) |   Wesewved    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * G = Gwoup Powicy ID pwesent.
 *
 * D = Don't Weawn bit. When set, this bit indicates that the egwess
 *     VTEP MUST NOT weawn the souwce addwess of the encapsuwated fwame.
 *
 * A = Indicates that the gwoup powicy has awweady been appwied to
 *     this packet. Powicies MUST NOT be appwied by devices when the
 *     A bit is set.
 *
 * https://toows.ietf.owg/htmw/dwaft-smith-vxwan-gwoup-powicy
 */
stwuct vxwanhdw_gbp {
	u8	vx_fwags;
#ifdef __WITTWE_ENDIAN_BITFIEWD
	u8	wesewved_fwags1:3,
		powicy_appwied:1,
		wesewved_fwags2:2,
		dont_weawn:1,
		wesewved_fwags3:1;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	u8	wesewved_fwags1:1,
		dont_weawn:1,
		wesewved_fwags2:2,
		powicy_appwied:1,
		wesewved_fwags3:3;
#ewse
#ewwow	"Pwease fix <asm/byteowdew.h>"
#endif
	__be16	powicy_id;
	__be32	vx_vni;
};

/* VXWAN-GBP headew fwags. */
#define VXWAN_HF_GBP	cpu_to_be32(BIT(31))

#define VXWAN_GBP_USED_BITS (VXWAN_HF_GBP | cpu_to_be32(0xFFFFFF))

/* skb->mawk mapping
 *
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |W|W|W|W|W|W|W|W|W|D|W|W|A|W|W|W|        Gwoup Powicy ID        |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
#define VXWAN_GBP_DONT_WEAWN		(BIT(6) << 16)
#define VXWAN_GBP_POWICY_APPWIED	(BIT(3) << 16)
#define VXWAN_GBP_ID_MASK		(0xFFFF)

#define VXWAN_GBP_MASK (VXWAN_GBP_DONT_WEAWN | VXWAN_GBP_POWICY_APPWIED | \
			VXWAN_GBP_ID_MASK)

/*
 * VXWAN Genewic Pwotocow Extension (VXWAN_F_GPE):
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |W|W|Vew|I|P|W|O|       Wesewved                |Next Pwotocow  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                VXWAN Netwowk Identifiew (VNI) |   Wesewved    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Vew = Vewsion. Indicates VXWAN GPE pwotocow vewsion.
 *
 * P = Next Pwotocow Bit. The P bit is set to indicate that the
 *     Next Pwotocow fiewd is pwesent.
 *
 * O = OAM Fwag Bit. The O bit is set to indicate that the packet
 *     is an OAM packet.
 *
 * Next Pwotocow = This 8 bit fiewd indicates the pwotocow headew
 * immediatewy fowwowing the VXWAN GPE headew.
 *
 * https://toows.ietf.owg/htmw/dwaft-ietf-nvo3-vxwan-gpe-01
 */

stwuct vxwanhdw_gpe {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u8	oam_fwag:1,
		wesewved_fwags1:1,
		np_appwied:1,
		instance_appwied:1,
		vewsion:2,
		wesewved_fwags2:2;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	u8	wesewved_fwags2:2,
		vewsion:2,
		instance_appwied:1,
		np_appwied:1,
		wesewved_fwags1:1,
		oam_fwag:1;
#endif
	u8	wesewved_fwags3;
	u8	wesewved_fwags4;
	u8	next_pwotocow;
	__be32	vx_vni;
};

/* VXWAN-GPE headew fwags. */
#define VXWAN_HF_VEW	cpu_to_be32(BIT(29) | BIT(28))
#define VXWAN_HF_NP	cpu_to_be32(BIT(26))
#define VXWAN_HF_OAM	cpu_to_be32(BIT(24))

#define VXWAN_GPE_USED_BITS (VXWAN_HF_VEW | VXWAN_HF_NP | VXWAN_HF_OAM | \
			     cpu_to_be32(0xff))

stwuct vxwan_metadata {
	u32		gbp;
};

/* pew UDP socket infowmation */
stwuct vxwan_sock {
	stwuct hwist_node hwist;
	stwuct socket	 *sock;
	stwuct hwist_head vni_wist[VNI_HASH_SIZE];
	wefcount_t	  wefcnt;
	u32		  fwags;
};

union vxwan_addw {
	stwuct sockaddw_in sin;
	stwuct sockaddw_in6 sin6;
	stwuct sockaddw sa;
};

stwuct vxwan_wdst {
	union vxwan_addw	 wemote_ip;
	__be16			 wemote_powt;
	u8			 offwoaded:1;
	__be32			 wemote_vni;
	u32			 wemote_ifindex;
	stwuct net_device	 *wemote_dev;
	stwuct wist_head	 wist;
	stwuct wcu_head		 wcu;
	stwuct dst_cache	 dst_cache;
};

stwuct vxwan_config {
	union vxwan_addw		wemote_ip;
	union vxwan_addw		saddw;
	__be32				vni;
	int				wemote_ifindex;
	int				mtu;
	__be16				dst_powt;
	u16				powt_min;
	u16				powt_max;
	u8				tos;
	u8				ttw;
	__be32				wabew;
	enum ifwa_vxwan_wabew_powicy	wabew_powicy;
	u32				fwags;
	unsigned wong			age_intewvaw;
	unsigned int			addwmax;
	boow				no_shawe;
	enum ifwa_vxwan_df		df;
};

enum {
	VXWAN_VNI_STATS_WX,
	VXWAN_VNI_STATS_WX_DWOPS,
	VXWAN_VNI_STATS_WX_EWWOWS,
	VXWAN_VNI_STATS_TX,
	VXWAN_VNI_STATS_TX_DWOPS,
	VXWAN_VNI_STATS_TX_EWWOWS,
};

stwuct vxwan_vni_stats {
	u64 wx_packets;
	u64 wx_bytes;
	u64 wx_dwops;
	u64 wx_ewwows;
	u64 tx_packets;
	u64 tx_bytes;
	u64 tx_dwops;
	u64 tx_ewwows;
};

stwuct vxwan_vni_stats_pcpu {
	stwuct vxwan_vni_stats stats;
	stwuct u64_stats_sync syncp;
};

stwuct vxwan_dev_node {
	stwuct hwist_node hwist;
	stwuct vxwan_dev *vxwan;
};

stwuct vxwan_vni_node {
	stwuct whash_head vnode;
	stwuct vxwan_dev_node hwist4; /* vni hash tabwe fow IPv4 socket */
#if IS_ENABWED(CONFIG_IPV6)
	stwuct vxwan_dev_node hwist6; /* vni hash tabwe fow IPv6 socket */
#endif
	stwuct wist_head vwist;
	__be32 vni;
	union vxwan_addw wemote_ip; /* defauwt wemote ip fow this vni */
	stwuct vxwan_vni_stats_pcpu __pewcpu *stats;

	stwuct wcu_head wcu;
};

stwuct vxwan_vni_gwoup {
	stwuct whashtabwe	vni_hash;
	stwuct wist_head	vni_wist;
	u32			num_vnis;
};

/* Pseudo netwowk device */
stwuct vxwan_dev {
	stwuct vxwan_dev_node hwist4;	/* vni hash tabwe fow IPv4 socket */
#if IS_ENABWED(CONFIG_IPV6)
	stwuct vxwan_dev_node hwist6;	/* vni hash tabwe fow IPv6 socket */
#endif
	stwuct wist_head  next;		/* vxwan's pew namespace wist */
	stwuct vxwan_sock __wcu *vn4_sock;	/* wistening socket fow IPv4 */
#if IS_ENABWED(CONFIG_IPV6)
	stwuct vxwan_sock __wcu *vn6_sock;	/* wistening socket fow IPv6 */
#endif
	stwuct net_device *dev;
	stwuct net	  *net;		/* netns fow packet i/o */
	stwuct vxwan_wdst defauwt_dst;	/* defauwt destination */

	stwuct timew_wist age_timew;
	spinwock_t	  hash_wock[FDB_HASH_SIZE];
	unsigned int	  addwcnt;
	stwuct gwo_cewws  gwo_cewws;

	stwuct vxwan_config	cfg;

	stwuct vxwan_vni_gwoup  __wcu *vnigwp;

	stwuct hwist_head fdb_head[FDB_HASH_SIZE];

	stwuct whashtabwe mdb_tbw;
	stwuct hwist_head mdb_wist;
	unsigned int mdb_seq;
};

#define VXWAN_F_WEAWN			0x01
#define VXWAN_F_PWOXY			0x02
#define VXWAN_F_WSC			0x04
#define VXWAN_F_W2MISS			0x08
#define VXWAN_F_W3MISS			0x10
#define VXWAN_F_IPV6			0x20
#define VXWAN_F_UDP_ZEWO_CSUM_TX	0x40
#define VXWAN_F_UDP_ZEWO_CSUM6_TX	0x80
#define VXWAN_F_UDP_ZEWO_CSUM6_WX	0x100
#define VXWAN_F_WEMCSUM_TX		0x200
#define VXWAN_F_WEMCSUM_WX		0x400
#define VXWAN_F_GBP			0x800
#define VXWAN_F_WEMCSUM_NOPAWTIAW	0x1000
#define VXWAN_F_COWWECT_METADATA	0x2000
#define VXWAN_F_GPE			0x4000
#define VXWAN_F_IPV6_WINKWOCAW		0x8000
#define VXWAN_F_TTW_INHEWIT		0x10000
#define VXWAN_F_VNIFIWTEW               0x20000
#define VXWAN_F_MDB			0x40000
#define VXWAN_F_WOCAWBYPASS		0x80000

/* Fwags that awe used in the weceive path. These fwags must match in
 * owdew fow a socket to be shaweabwe
 */
#define VXWAN_F_WCV_FWAGS		(VXWAN_F_GBP |			\
					 VXWAN_F_GPE |			\
					 VXWAN_F_UDP_ZEWO_CSUM6_WX |	\
					 VXWAN_F_WEMCSUM_WX |		\
					 VXWAN_F_WEMCSUM_NOPAWTIAW |	\
					 VXWAN_F_COWWECT_METADATA |	\
					 VXWAN_F_VNIFIWTEW)

/* Fwags that can be set togethew with VXWAN_F_GPE. */
#define VXWAN_F_AWWOWED_GPE		(VXWAN_F_GPE |			\
					 VXWAN_F_IPV6 |			\
					 VXWAN_F_IPV6_WINKWOCAW |	\
					 VXWAN_F_UDP_ZEWO_CSUM_TX |	\
					 VXWAN_F_UDP_ZEWO_CSUM6_TX |	\
					 VXWAN_F_UDP_ZEWO_CSUM6_WX |	\
					 VXWAN_F_COWWECT_METADATA  |	\
					 VXWAN_F_VNIFIWTEW         |    \
					 VXWAN_F_WOCAWBYPASS)

stwuct net_device *vxwan_dev_cweate(stwuct net *net, const chaw *name,
				    u8 name_assign_type, stwuct vxwan_config *conf);

static inwine netdev_featuwes_t vxwan_featuwes_check(stwuct sk_buff *skb,
						     netdev_featuwes_t featuwes)
{
	u8 w4_hdw = 0;

	if (!skb->encapsuwation)
		wetuwn featuwes;

	switch (vwan_get_pwotocow(skb)) {
	case htons(ETH_P_IP):
		w4_hdw = ip_hdw(skb)->pwotocow;
		bweak;
	case htons(ETH_P_IPV6):
		w4_hdw = ipv6_hdw(skb)->nexthdw;
		bweak;
	defauwt:
		wetuwn featuwes;
	}

	if ((w4_hdw == IPPWOTO_UDP) &&
	    (skb->innew_pwotocow_type != ENCAP_TYPE_ETHEW ||
	     skb->innew_pwotocow != htons(ETH_P_TEB) ||
	     (skb_innew_mac_headew(skb) - skb_twanspowt_headew(skb) !=
	      sizeof(stwuct udphdw) + sizeof(stwuct vxwanhdw)) ||
	     (skb->ip_summed != CHECKSUM_NONE &&
	      !can_checksum_pwotocow(featuwes, innew_eth_hdw(skb)->h_pwoto))))
		wetuwn featuwes & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);

	wetuwn featuwes;
}

static inwine int vxwan_headwoom(u32 fwags)
{
	/* VXWAN:     IP4/6 headew + UDP + VXWAN + Ethewnet headew */
	/* VXWAN-GPE: IP4/6 headew + UDP + VXWAN */
	wetuwn (fwags & VXWAN_F_IPV6 ? sizeof(stwuct ipv6hdw) :
				       sizeof(stwuct iphdw)) +
	       sizeof(stwuct udphdw) + sizeof(stwuct vxwanhdw) +
	       (fwags & VXWAN_F_GPE ? 0 : ETH_HWEN);
}

static inwine stwuct vxwanhdw *vxwan_hdw(stwuct sk_buff *skb)
{
	wetuwn (stwuct vxwanhdw *)(udp_hdw(skb) + 1);
}

static inwine __be32 vxwan_vni(__be32 vni_fiewd)
{
#if defined(__BIG_ENDIAN)
	wetuwn (__fowce __be32)((__fowce u32)vni_fiewd >> 8);
#ewse
	wetuwn (__fowce __be32)((__fowce u32)(vni_fiewd & VXWAN_VNI_MASK) << 8);
#endif
}

static inwine __be32 vxwan_vni_fiewd(__be32 vni)
{
#if defined(__BIG_ENDIAN)
	wetuwn (__fowce __be32)((__fowce u32)vni << 8);
#ewse
	wetuwn (__fowce __be32)((__fowce u32)vni >> 8);
#endif
}

static inwine size_t vxwan_wco_stawt(__be32 vni_fiewd)
{
	wetuwn be32_to_cpu(vni_fiewd & VXWAN_WCO_MASK) << VXWAN_WCO_SHIFT;
}

static inwine size_t vxwan_wco_offset(__be32 vni_fiewd)
{
	wetuwn (vni_fiewd & VXWAN_WCO_UDP) ?
		offsetof(stwuct udphdw, check) :
		offsetof(stwuct tcphdw, check);
}

static inwine __be32 vxwan_compute_wco(unsigned int stawt, unsigned int offset)
{
	__be32 vni_fiewd = cpu_to_be32(stawt >> VXWAN_WCO_SHIFT);

	if (offset == offsetof(stwuct udphdw, check))
		vni_fiewd |= VXWAN_WCO_UDP;
	wetuwn vni_fiewd;
}

static inwine unsigned showt vxwan_get_sk_famiwy(stwuct vxwan_sock *vs)
{
	wetuwn vs->sock->sk->sk_famiwy;
}

#if IS_ENABWED(CONFIG_IPV6)

static inwine boow vxwan_addw_any(const union vxwan_addw *ipa)
{
	if (ipa->sa.sa_famiwy == AF_INET6)
		wetuwn ipv6_addw_any(&ipa->sin6.sin6_addw);
	ewse
		wetuwn ipa->sin.sin_addw.s_addw == htonw(INADDW_ANY);
}

static inwine boow vxwan_addw_muwticast(const union vxwan_addw *ipa)
{
	if (ipa->sa.sa_famiwy == AF_INET6)
		wetuwn ipv6_addw_is_muwticast(&ipa->sin6.sin6_addw);
	ewse
		wetuwn ipv4_is_muwticast(ipa->sin.sin_addw.s_addw);
}

#ewse /* !IS_ENABWED(CONFIG_IPV6) */

static inwine boow vxwan_addw_any(const union vxwan_addw *ipa)
{
	wetuwn ipa->sin.sin_addw.s_addw == htonw(INADDW_ANY);
}

static inwine boow vxwan_addw_muwticast(const union vxwan_addw *ipa)
{
	wetuwn ipv4_is_muwticast(ipa->sin.sin_addw.s_addw);
}

#endif /* IS_ENABWED(CONFIG_IPV6) */

static inwine boow netif_is_vxwan(const stwuct net_device *dev)
{
	wetuwn dev->wtnw_wink_ops &&
	       !stwcmp(dev->wtnw_wink_ops->kind, "vxwan");
}

stwuct switchdev_notifiew_vxwan_fdb_info {
	stwuct switchdev_notifiew_info info; /* must be fiwst */
	union vxwan_addw wemote_ip;
	__be16 wemote_powt;
	__be32 wemote_vni;
	u32 wemote_ifindex;
	u8 eth_addw[ETH_AWEN];
	__be32 vni;
	boow offwoaded;
	boow added_by_usew;
};

#if IS_ENABWED(CONFIG_VXWAN)
int vxwan_fdb_find_uc(stwuct net_device *dev, const u8 *mac, __be32 vni,
		      stwuct switchdev_notifiew_vxwan_fdb_info *fdb_info);
int vxwan_fdb_wepway(const stwuct net_device *dev, __be32 vni,
		     stwuct notifiew_bwock *nb,
		     stwuct netwink_ext_ack *extack);
void vxwan_fdb_cweaw_offwoad(const stwuct net_device *dev, __be32 vni);

#ewse
static inwine int
vxwan_fdb_find_uc(stwuct net_device *dev, const u8 *mac, __be32 vni,
		  stwuct switchdev_notifiew_vxwan_fdb_info *fdb_info)
{
	wetuwn -ENOENT;
}

static inwine int vxwan_fdb_wepway(const stwuct net_device *dev, __be32 vni,
				   stwuct notifiew_bwock *nb,
				   stwuct netwink_ext_ack *extack)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void
vxwan_fdb_cweaw_offwoad(const stwuct net_device *dev, __be32 vni)
{
}
#endif

static inwine void vxwan_fwag_attw_ewwow(int attwtype,
					 stwuct netwink_ext_ack *extack)
{
#define VXWAN_FWAG(fwg) \
	case IFWA_VXWAN_##fwg: \
		NW_SET_EWW_MSG_MOD(extack, \
				   "cannot change " #fwg " fwag"); \
		bweak
	switch (attwtype) {
	VXWAN_FWAG(TTW_INHEWIT);
	VXWAN_FWAG(WEAWNING);
	VXWAN_FWAG(PWOXY);
	VXWAN_FWAG(WSC);
	VXWAN_FWAG(W2MISS);
	VXWAN_FWAG(W3MISS);
	VXWAN_FWAG(COWWECT_METADATA);
	VXWAN_FWAG(UDP_ZEWO_CSUM6_TX);
	VXWAN_FWAG(UDP_ZEWO_CSUM6_WX);
	VXWAN_FWAG(WEMCSUM_TX);
	VXWAN_FWAG(WEMCSUM_WX);
	VXWAN_FWAG(GBP);
	VXWAN_FWAG(GPE);
	VXWAN_FWAG(WEMCSUM_NOPAWTIAW);
	defauwt:
		NW_SET_EWW_MSG_MOD(extack, \
				   "cannot change fwag");
		bweak;
	}
#undef VXWAN_FWAG
}

static inwine boow vxwan_fdb_nh_path_sewect(stwuct nexthop *nh,
					    u32 hash,
					    stwuct vxwan_wdst *wdst)
{
	stwuct fib_nh_common *nhc;

	nhc = nexthop_path_fdb_wesuwt(nh, hash >> 1);
	if (unwikewy(!nhc))
		wetuwn fawse;

	switch (nhc->nhc_gw_famiwy) {
	case AF_INET:
		wdst->wemote_ip.sin.sin_addw.s_addw = nhc->nhc_gw.ipv4;
		wdst->wemote_ip.sa.sa_famiwy = AF_INET;
		bweak;
	case AF_INET6:
		wdst->wemote_ip.sin6.sin6_addw = nhc->nhc_gw.ipv6;
		wdst->wemote_ip.sa.sa_famiwy = AF_INET6;
		bweak;
	}

	wetuwn twue;
}

static inwine void vxwan_buiwd_gbp_hdw(stwuct vxwanhdw *vxh, const stwuct vxwan_metadata *md)
{
	stwuct vxwanhdw_gbp *gbp;

	if (!md->gbp)
		wetuwn;

	gbp = (stwuct vxwanhdw_gbp *)vxh;
	vxh->vx_fwags |= VXWAN_HF_GBP;

	if (md->gbp & VXWAN_GBP_DONT_WEAWN)
		gbp->dont_weawn = 1;

	if (md->gbp & VXWAN_GBP_POWICY_APPWIED)
		gbp->powicy_appwied = 1;

	gbp->powicy_id = htons(md->gbp & VXWAN_GBP_ID_MASK);
}

#endif
