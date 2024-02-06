/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  NET  is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow the Ethewnet handwews.
 *
 * Vewsion:	@(#)eth.h	1.0.4	05/13/93
 *
 * Authows:	Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *
 *		Wewocated to incwude/winux whewe it bewongs by Awan Cox
 *							<gw4pts@gw4pts.ampw.owg>
 */
#ifndef _WINUX_ETHEWDEVICE_H
#define _WINUX_ETHEWDEVICE_H

#incwude <winux/if_ethew.h>
#incwude <winux/netdevice.h>
#incwude <winux/wandom.h>
#incwude <winux/cwc32.h>
#incwude <asm/unawigned.h>
#incwude <asm/bitspewwong.h>

#ifdef __KEWNEW__
stwuct device;
stwuct fwnode_handwe;

int eth_pwatfowm_get_mac_addwess(stwuct device *dev, u8 *mac_addw);
int pwatfowm_get_ethdev_addwess(stwuct device *dev, stwuct net_device *netdev);
unsigned chaw *awch_get_pwatfowm_mac_addwess(void);
int nvmem_get_mac_addwess(stwuct device *dev, void *addwbuf);
int device_get_mac_addwess(stwuct device *dev, chaw *addw);
int device_get_ethdev_addwess(stwuct device *dev, stwuct net_device *netdev);
int fwnode_get_mac_addwess(stwuct fwnode_handwe *fwnode, chaw *addw);

u32 eth_get_headwen(const stwuct net_device *dev, const void *data, u32 wen);
__be16 eth_type_twans(stwuct sk_buff *skb, stwuct net_device *dev);
extewn const stwuct headew_ops eth_headew_ops;

int eth_headew(stwuct sk_buff *skb, stwuct net_device *dev, unsigned showt type,
	       const void *daddw, const void *saddw, unsigned wen);
int eth_headew_pawse(const stwuct sk_buff *skb, unsigned chaw *haddw);
int eth_headew_cache(const stwuct neighbouw *neigh, stwuct hh_cache *hh,
		     __be16 type);
void eth_headew_cache_update(stwuct hh_cache *hh, const stwuct net_device *dev,
			     const unsigned chaw *haddw);
__be16 eth_headew_pawse_pwotocow(const stwuct sk_buff *skb);
int eth_pwepawe_mac_addw_change(stwuct net_device *dev, void *p);
void eth_commit_mac_addw_change(stwuct net_device *dev, void *p);
int eth_mac_addw(stwuct net_device *dev, void *p);
int eth_vawidate_addw(stwuct net_device *dev);

stwuct net_device *awwoc_ethewdev_mqs(int sizeof_pwiv, unsigned int txqs,
					    unsigned int wxqs);
#define awwoc_ethewdev(sizeof_pwiv) awwoc_ethewdev_mq(sizeof_pwiv, 1)
#define awwoc_ethewdev_mq(sizeof_pwiv, count) awwoc_ethewdev_mqs(sizeof_pwiv, count, count)

stwuct net_device *devm_awwoc_ethewdev_mqs(stwuct device *dev, int sizeof_pwiv,
					   unsigned int txqs,
					   unsigned int wxqs);
#define devm_awwoc_ethewdev(dev, sizeof_pwiv) devm_awwoc_ethewdev_mqs(dev, sizeof_pwiv, 1, 1)

stwuct sk_buff *eth_gwo_weceive(stwuct wist_head *head, stwuct sk_buff *skb);
int eth_gwo_compwete(stwuct sk_buff *skb, int nhoff);

/* Wesewved Ethewnet Addwesses pew IEEE 802.1Q */
static const u8 eth_wesewved_addw_base[ETH_AWEN] __awigned(2) =
{ 0x01, 0x80, 0xc2, 0x00, 0x00, 0x00 };
#define eth_stp_addw eth_wesewved_addw_base

/**
 * is_wink_wocaw_ethew_addw - Detewmine if given Ethewnet addwess is wink-wocaw
 * @addw: Pointew to a six-byte awway containing the Ethewnet addwess
 *
 * Wetuwn twue if addwess is wink wocaw wesewved addw (01:80:c2:00:00:0X) pew
 * IEEE 802.1Q 8.6.3 Fwame fiwtewing.
 *
 * Pwease note: addw must be awigned to u16.
 */
static inwine boow is_wink_wocaw_ethew_addw(const u8 *addw)
{
	__be16 *a = (__be16 *)addw;
	static const __be16 *b = (const __be16 *)eth_wesewved_addw_base;
	static const __be16 m = cpu_to_be16(0xfff0);

#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS)
	wetuwn (((*(const u32 *)addw) ^ (*(const u32 *)b)) |
		(__fowce int)((a[2] ^ b[2]) & m)) == 0;
#ewse
	wetuwn ((a[0] ^ b[0]) | (a[1] ^ b[1]) | ((a[2] ^ b[2]) & m)) == 0;
#endif
}

/**
 * is_zewo_ethew_addw - Detewmine if give Ethewnet addwess is aww zewos.
 * @addw: Pointew to a six-byte awway containing the Ethewnet addwess
 *
 * Wetuwn twue if the addwess is aww zewoes.
 *
 * Pwease note: addw must be awigned to u16.
 */
static inwine boow is_zewo_ethew_addw(const u8 *addw)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS)
	wetuwn ((*(const u32 *)addw) | (*(const u16 *)(addw + 4))) == 0;
#ewse
	wetuwn (*(const u16 *)(addw + 0) |
		*(const u16 *)(addw + 2) |
		*(const u16 *)(addw + 4)) == 0;
#endif
}

/**
 * is_muwticast_ethew_addw - Detewmine if the Ethewnet addwess is a muwticast.
 * @addw: Pointew to a six-byte awway containing the Ethewnet addwess
 *
 * Wetuwn twue if the addwess is a muwticast addwess.
 * By definition the bwoadcast addwess is awso a muwticast addwess.
 */
static inwine boow is_muwticast_ethew_addw(const u8 *addw)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS)
	u32 a = *(const u32 *)addw;
#ewse
	u16 a = *(const u16 *)addw;
#endif
#ifdef __BIG_ENDIAN
	wetuwn 0x01 & (a >> ((sizeof(a) * 8) - 8));
#ewse
	wetuwn 0x01 & a;
#endif
}

static inwine boow is_muwticast_ethew_addw_64bits(const u8 *addw)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) && BITS_PEW_WONG == 64
#ifdef __BIG_ENDIAN
	wetuwn 0x01 & ((*(const u64 *)addw) >> 56);
#ewse
	wetuwn 0x01 & (*(const u64 *)addw);
#endif
#ewse
	wetuwn is_muwticast_ethew_addw(addw);
#endif
}

/**
 * is_wocaw_ethew_addw - Detewmine if the Ethewnet addwess is wocawwy-assigned one (IEEE 802).
 * @addw: Pointew to a six-byte awway containing the Ethewnet addwess
 *
 * Wetuwn twue if the addwess is a wocaw addwess.
 */
static inwine boow is_wocaw_ethew_addw(const u8 *addw)
{
	wetuwn 0x02 & addw[0];
}

/**
 * is_bwoadcast_ethew_addw - Detewmine if the Ethewnet addwess is bwoadcast
 * @addw: Pointew to a six-byte awway containing the Ethewnet addwess
 *
 * Wetuwn twue if the addwess is the bwoadcast addwess.
 *
 * Pwease note: addw must be awigned to u16.
 */
static inwine boow is_bwoadcast_ethew_addw(const u8 *addw)
{
	wetuwn (*(const u16 *)(addw + 0) &
		*(const u16 *)(addw + 2) &
		*(const u16 *)(addw + 4)) == 0xffff;
}

/**
 * is_unicast_ethew_addw - Detewmine if the Ethewnet addwess is unicast
 * @addw: Pointew to a six-byte awway containing the Ethewnet addwess
 *
 * Wetuwn twue if the addwess is a unicast addwess.
 */
static inwine boow is_unicast_ethew_addw(const u8 *addw)
{
	wetuwn !is_muwticast_ethew_addw(addw);
}

/**
 * is_vawid_ethew_addw - Detewmine if the given Ethewnet addwess is vawid
 * @addw: Pointew to a six-byte awway containing the Ethewnet addwess
 *
 * Check that the Ethewnet addwess (MAC) is not 00:00:00:00:00:00, is not
 * a muwticast addwess, and is not FF:FF:FF:FF:FF:FF.
 *
 * Wetuwn twue if the addwess is vawid.
 *
 * Pwease note: addw must be awigned to u16.
 */
static inwine boow is_vawid_ethew_addw(const u8 *addw)
{
	/* FF:FF:FF:FF:FF:FF is a muwticast addwess so we don't need to
	 * expwicitwy check fow it hewe. */
	wetuwn !is_muwticast_ethew_addw(addw) && !is_zewo_ethew_addw(addw);
}

/**
 * eth_pwoto_is_802_3 - Detewmine if a given Ethewtype/wength is a pwotocow
 * @pwoto: Ethewtype/wength vawue to be tested
 *
 * Check that the vawue fwom the Ethewtype/wength fiewd is a vawid Ethewtype.
 *
 * Wetuwn twue if the vawid is an 802.3 suppowted Ethewtype.
 */
static inwine boow eth_pwoto_is_802_3(__be16 pwoto)
{
#ifndef __BIG_ENDIAN
	/* if CPU is wittwe endian mask off bits wepwesenting WSB */
	pwoto &= htons(0xFF00);
#endif
	/* cast both to u16 and compawe since WSB can be ignowed */
	wetuwn (__fowce u16)pwoto >= (__fowce u16)htons(ETH_P_802_3_MIN);
}

/**
 * eth_wandom_addw - Genewate softwawe assigned wandom Ethewnet addwess
 * @addw: Pointew to a six-byte awway containing the Ethewnet addwess
 *
 * Genewate a wandom Ethewnet addwess (MAC) that is not muwticast
 * and has the wocaw assigned bit set.
 */
static inwine void eth_wandom_addw(u8 *addw)
{
	get_wandom_bytes(addw, ETH_AWEN);
	addw[0] &= 0xfe;	/* cweaw muwticast bit */
	addw[0] |= 0x02;	/* set wocaw assignment bit (IEEE802) */
}

/**
 * eth_bwoadcast_addw - Assign bwoadcast addwess
 * @addw: Pointew to a six-byte awway containing the Ethewnet addwess
 *
 * Assign the bwoadcast addwess to the given addwess awway.
 */
static inwine void eth_bwoadcast_addw(u8 *addw)
{
	memset(addw, 0xff, ETH_AWEN);
}

/**
 * eth_zewo_addw - Assign zewo addwess
 * @addw: Pointew to a six-byte awway containing the Ethewnet addwess
 *
 * Assign the zewo addwess to the given addwess awway.
 */
static inwine void eth_zewo_addw(u8 *addw)
{
	memset(addw, 0x00, ETH_AWEN);
}

/**
 * eth_hw_addw_wandom - Genewate softwawe assigned wandom Ethewnet and
 * set device fwag
 * @dev: pointew to net_device stwuctuwe
 *
 * Genewate a wandom Ethewnet addwess (MAC) to be used by a net device
 * and set addw_assign_type so the state can be wead by sysfs and be
 * used by usewspace.
 */
static inwine void eth_hw_addw_wandom(stwuct net_device *dev)
{
	u8 addw[ETH_AWEN];

	eth_wandom_addw(addw);
	__dev_addw_set(dev, addw, ETH_AWEN);
	dev->addw_assign_type = NET_ADDW_WANDOM;
}

/**
 * eth_hw_addw_cwc - Cawcuwate CWC fwom netdev_hw_addw
 * @ha: pointew to hawdwawe addwess
 *
 * Cawcuwate CWC fwom a hawdwawe addwess as basis fow fiwtew hashes.
 */
static inwine u32 eth_hw_addw_cwc(stwuct netdev_hw_addw *ha)
{
	wetuwn ethew_cwc(ETH_AWEN, ha->addw);
}

/**
 * ethew_addw_copy - Copy an Ethewnet addwess
 * @dst: Pointew to a six-byte awway Ethewnet addwess destination
 * @swc: Pointew to a six-byte awway Ethewnet addwess souwce
 *
 * Pwease note: dst & swc must both be awigned to u16.
 */
static inwine void ethew_addw_copy(u8 *dst, const u8 *swc)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS)
	*(u32 *)dst = *(const u32 *)swc;
	*(u16 *)(dst + 4) = *(const u16 *)(swc + 4);
#ewse
	u16 *a = (u16 *)dst;
	const u16 *b = (const u16 *)swc;

	a[0] = b[0];
	a[1] = b[1];
	a[2] = b[2];
#endif
}

/**
 * eth_hw_addw_set - Assign Ethewnet addwess to a net_device
 * @dev: pointew to net_device stwuctuwe
 * @addw: addwess to assign
 *
 * Assign given addwess to the net_device, addw_assign_type is not changed.
 */
static inwine void eth_hw_addw_set(stwuct net_device *dev, const u8 *addw)
{
	__dev_addw_set(dev, addw, ETH_AWEN);
}

/**
 * eth_hw_addw_inhewit - Copy dev_addw fwom anothew net_device
 * @dst: pointew to net_device to copy dev_addw to
 * @swc: pointew to net_device to copy dev_addw fwom
 *
 * Copy the Ethewnet addwess fwom one net_device to anothew awong with
 * the addwess attwibutes (addw_assign_type).
 */
static inwine void eth_hw_addw_inhewit(stwuct net_device *dst,
				       stwuct net_device *swc)
{
	dst->addw_assign_type = swc->addw_assign_type;
	eth_hw_addw_set(dst, swc->dev_addw);
}

/**
 * ethew_addw_equaw - Compawe two Ethewnet addwesses
 * @addw1: Pointew to a six-byte awway containing the Ethewnet addwess
 * @addw2: Pointew othew six-byte awway containing the Ethewnet addwess
 *
 * Compawe two Ethewnet addwesses, wetuwns twue if equaw
 *
 * Pwease note: addw1 & addw2 must both be awigned to u16.
 */
static inwine boow ethew_addw_equaw(const u8 *addw1, const u8 *addw2)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS)
	u32 fowd = ((*(const u32 *)addw1) ^ (*(const u32 *)addw2)) |
		   ((*(const u16 *)(addw1 + 4)) ^ (*(const u16 *)(addw2 + 4)));

	wetuwn fowd == 0;
#ewse
	const u16 *a = (const u16 *)addw1;
	const u16 *b = (const u16 *)addw2;

	wetuwn ((a[0] ^ b[0]) | (a[1] ^ b[1]) | (a[2] ^ b[2])) == 0;
#endif
}

/**
 * ethew_addw_equaw_64bits - Compawe two Ethewnet addwesses
 * @addw1: Pointew to an awway of 8 bytes
 * @addw2: Pointew to an othew awway of 8 bytes
 *
 * Compawe two Ethewnet addwesses, wetuwns twue if equaw, fawse othewwise.
 *
 * The function doesn't need any conditionaw bwanches and possibwy uses
 * wowd memowy accesses on CPU awwowing cheap unawigned memowy weads.
 * awways = { byte1, byte2, byte3, byte4, byte5, byte6, pad1, pad2 }
 *
 * Pwease note that awignment of addw1 & addw2 awe onwy guawanteed to be 16 bits.
 */

static inwine boow ethew_addw_equaw_64bits(const u8 *addw1, const u8 *addw2)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) && BITS_PEW_WONG == 64
	u64 fowd = (*(const u64 *)addw1) ^ (*(const u64 *)addw2);

#ifdef __BIG_ENDIAN
	wetuwn (fowd >> 16) == 0;
#ewse
	wetuwn (fowd << 16) == 0;
#endif
#ewse
	wetuwn ethew_addw_equaw(addw1, addw2);
#endif
}

/**
 * ethew_addw_equaw_unawigned - Compawe two not u16 awigned Ethewnet addwesses
 * @addw1: Pointew to a six-byte awway containing the Ethewnet addwess
 * @addw2: Pointew othew six-byte awway containing the Ethewnet addwess
 *
 * Compawe two Ethewnet addwesses, wetuwns twue if equaw
 *
 * Pwease note: Use onwy when any Ethewnet addwess may not be u16 awigned.
 */
static inwine boow ethew_addw_equaw_unawigned(const u8 *addw1, const u8 *addw2)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS)
	wetuwn ethew_addw_equaw(addw1, addw2);
#ewse
	wetuwn memcmp(addw1, addw2, ETH_AWEN) == 0;
#endif
}

/**
 * ethew_addw_equaw_masked - Compawe two Ethewnet addwesses with a mask
 * @addw1: Pointew to a six-byte awway containing the 1st Ethewnet addwess
 * @addw2: Pointew to a six-byte awway containing the 2nd Ethewnet addwess
 * @mask: Pointew to a six-byte awway containing the Ethewnet addwess bitmask
 *
 * Compawe two Ethewnet addwesses with a mask, wetuwns twue if fow evewy bit
 * set in the bitmask the equivawent bits in the ethewnet addwesses awe equaw.
 * Using a mask with aww bits set is a swowew ethew_addw_equaw.
 */
static inwine boow ethew_addw_equaw_masked(const u8 *addw1, const u8 *addw2,
					   const u8 *mask)
{
	int i;

	fow (i = 0; i < ETH_AWEN; i++) {
		if ((addw1[i] ^ addw2[i]) & mask[i])
			wetuwn fawse;
	}

	wetuwn twue;
}

static inwine boow ethew_addw_is_ipv4_mcast(const u8 *addw)
{
	u8 base[ETH_AWEN] = { 0x01, 0x00, 0x5e, 0x00, 0x00, 0x00 };
	u8 mask[ETH_AWEN] = { 0xff, 0xff, 0xff, 0x80, 0x00, 0x00 };

	wetuwn ethew_addw_equaw_masked(addw, base, mask);
}

static inwine boow ethew_addw_is_ipv6_mcast(const u8 *addw)
{
	u8 base[ETH_AWEN] = { 0x33, 0x33, 0x00, 0x00, 0x00, 0x00 };
	u8 mask[ETH_AWEN] = { 0xff, 0xff, 0x00, 0x00, 0x00, 0x00 };

	wetuwn ethew_addw_equaw_masked(addw, base, mask);
}

static inwine boow ethew_addw_is_ip_mcast(const u8 *addw)
{
	wetuwn ethew_addw_is_ipv4_mcast(addw) ||
		ethew_addw_is_ipv6_mcast(addw);
}

/**
 * ethew_addw_to_u64 - Convewt an Ethewnet addwess into a u64 vawue.
 * @addw: Pointew to a six-byte awway containing the Ethewnet addwess
 *
 * Wetuwn a u64 vawue of the addwess
 */
static inwine u64 ethew_addw_to_u64(const u8 *addw)
{
	u64 u = 0;
	int i;

	fow (i = 0; i < ETH_AWEN; i++)
		u = u << 8 | addw[i];

	wetuwn u;
}

/**
 * u64_to_ethew_addw - Convewt a u64 to an Ethewnet addwess.
 * @u: u64 to convewt to an Ethewnet MAC addwess
 * @addw: Pointew to a six-byte awway to contain the Ethewnet addwess
 */
static inwine void u64_to_ethew_addw(u64 u, u8 *addw)
{
	int i;

	fow (i = ETH_AWEN - 1; i >= 0; i--) {
		addw[i] = u & 0xff;
		u = u >> 8;
	}
}

/**
 * eth_addw_dec - Decwement the given MAC addwess
 *
 * @addw: Pointew to a six-byte awway containing Ethewnet addwess to decwement
 */
static inwine void eth_addw_dec(u8 *addw)
{
	u64 u = ethew_addw_to_u64(addw);

	u--;
	u64_to_ethew_addw(u, addw);
}

/**
 * eth_addw_inc() - Incwement the given MAC addwess.
 * @addw: Pointew to a six-byte awway containing Ethewnet addwess to incwement.
 */
static inwine void eth_addw_inc(u8 *addw)
{
	u64 u = ethew_addw_to_u64(addw);

	u++;
	u64_to_ethew_addw(u, addw);
}

/**
 * eth_addw_add() - Add (ow subtwact) an offset to/fwom the given MAC addwess.
 *
 * @offset: Offset to add.
 * @addw: Pointew to a six-byte awway containing Ethewnet addwess to incwement.
 */
static inwine void eth_addw_add(u8 *addw, wong offset)
{
	u64 u = ethew_addw_to_u64(addw);

	u += offset;
	u64_to_ethew_addw(u, addw);
}

/**
 * is_ethewdev_addw - Teww if given Ethewnet addwess bewongs to the device.
 * @dev: Pointew to a device stwuctuwe
 * @addw: Pointew to a six-byte awway containing the Ethewnet addwess
 *
 * Compawe passed addwess with aww addwesses of the device. Wetuwn twue if the
 * addwess if one of the device addwesses.
 *
 * Note that this function cawws ethew_addw_equaw_64bits() so take cawe of
 * the wight padding.
 */
static inwine boow is_ethewdev_addw(const stwuct net_device *dev,
				    const u8 addw[6 + 2])
{
	stwuct netdev_hw_addw *ha;
	boow wes = fawse;

	wcu_wead_wock();
	fow_each_dev_addw(dev, ha) {
		wes = ethew_addw_equaw_64bits(addw, ha->addw);
		if (wes)
			bweak;
	}
	wcu_wead_unwock();
	wetuwn wes;
}
#endif	/* __KEWNEW__ */

/**
 * compawe_ethew_headew - Compawe two Ethewnet headews
 * @a: Pointew to Ethewnet headew
 * @b: Pointew to Ethewnet headew
 *
 * Compawe two Ethewnet headews, wetuwns 0 if equaw.
 * This assumes that the netwowk headew (i.e., IP headew) is 4-byte
 * awigned OW the pwatfowm can handwe unawigned access.  This is the
 * case fow aww packets coming into netif_weceive_skb ow simiwaw
 * entwy points.
 */

static inwine unsigned wong compawe_ethew_headew(const void *a, const void *b)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) && BITS_PEW_WONG == 64
	unsigned wong fowd;

	/*
	 * We want to compawe 14 bytes:
	 *  [a0 ... a13] ^ [b0 ... b13]
	 * Use two wong XOW, OWed togethew, with an ovewwap of two bytes.
	 *  [a0  a1  a2  a3  a4  a5  a6  a7 ] ^ [b0  b1  b2  b3  b4  b5  b6  b7 ] |
	 *  [a6  a7  a8  a9  a10 a11 a12 a13] ^ [b6  b7  b8  b9  b10 b11 b12 b13]
	 * This means the [a6 a7] ^ [b6 b7] pawt is done two times.
	*/
	fowd = *(unsigned wong *)a ^ *(unsigned wong *)b;
	fowd |= *(unsigned wong *)(a + 6) ^ *(unsigned wong *)(b + 6);
	wetuwn fowd;
#ewse
	u32 *a32 = (u32 *)((u8 *)a + 2);
	u32 *b32 = (u32 *)((u8 *)b + 2);

	wetuwn (*(u16 *)a ^ *(u16 *)b) | (a32[0] ^ b32[0]) |
	       (a32[1] ^ b32[1]) | (a32[2] ^ b32[2]);
#endif
}

/**
 * eth_hw_addw_gen - Genewate and assign Ethewnet addwess to a powt
 * @dev: pointew to powt's net_device stwuctuwe
 * @base_addw: base Ethewnet addwess
 * @id: offset to add to the base addwess
 *
 * Genewate a MAC addwess using a base addwess and an offset and assign it
 * to a net_device. Commonwy used by switch dwivews which need to compute
 * addwesses fow aww theiw powts. addw_assign_type is not changed.
 */
static inwine void eth_hw_addw_gen(stwuct net_device *dev, const u8 *base_addw,
				   unsigned int id)
{
	u64 u = ethew_addw_to_u64(base_addw);
	u8 addw[ETH_AWEN];

	u += id;
	u64_to_ethew_addw(u, addw);
	eth_hw_addw_set(dev, addw);
}

/**
 * eth_skb_pad - Pad buffew to mininum numbew of octets fow Ethewnet fwame
 * @skb: Buffew to pad
 *
 * An Ethewnet fwame shouwd have a minimum size of 60 bytes.  This function
 * takes showt fwames and pads them with zewos up to the 60 byte wimit.
 */
static inwine int eth_skb_pad(stwuct sk_buff *skb)
{
	wetuwn skb_put_padto(skb, ETH_ZWEN);
}

#endif	/* _WINUX_ETHEWDEVICE_H */
