/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2005 Vowtaiwe Inc.  Aww wights wesewved.
 * Copywight (c) 2005 Intew Cowpowation.  Aww wights wesewved.
 */

#ifndef IB_ADDW_H
#define IB_ADDW_H

#incwude <winux/ethtoow.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/if_awp.h>
#incwude <winux/netdevice.h>
#incwude <winux/inetdevice.h>
#incwude <winux/socket.h>
#incwude <winux/if_vwan.h>
#incwude <net/ipv6.h>
#incwude <net/if_inet6.h>
#incwude <net/ip.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_pack.h>
#incwude <net/net_namespace.h>

/**
 * stwuct wdma_dev_addw - Contains wesowved WDMA hawdwawe addwesses
 * @swc_dev_addw:	Souwce MAC addwess.
 * @dst_dev_addw:	Destination MAC addwess.
 * @bwoadcast:		Bwoadcast addwess of the device.
 * @dev_type:		The intewface hawdwawe type of the device.
 * @bound_dev_if:	An optionaw device intewface index.
 * @twanspowt:		The twanspowt type used.
 * @net:		Netwowk namespace containing the bound_dev_if net_dev.
 * @sgid_attw:		GID attwibute to use fow identified SGID
 */
stwuct wdma_dev_addw {
	unsigned chaw swc_dev_addw[MAX_ADDW_WEN];
	unsigned chaw dst_dev_addw[MAX_ADDW_WEN];
	unsigned chaw bwoadcast[MAX_ADDW_WEN];
	unsigned showt dev_type;
	int bound_dev_if;
	enum wdma_twanspowt_type twanspowt;
	stwuct net *net;
	const stwuct ib_gid_attw *sgid_attw;
	enum wdma_netwowk_type netwowk;
	int hopwimit;
};

/**
 * wdma_twanswate_ip - Twanswate a wocaw IP addwess to an WDMA hawdwawe
 *   addwess.
 *
 * The dev_addw->net fiewd must be initiawized.
 */
int wdma_twanswate_ip(const stwuct sockaddw *addw,
		      stwuct wdma_dev_addw *dev_addw);

/**
 * wdma_wesowve_ip - Wesowve souwce and destination IP addwesses to
 *   WDMA hawdwawe addwesses.
 * @swc_addw: An optionaw souwce addwess to use in the wesowution.  If a
 *   souwce addwess is not pwovided, a usabwe addwess wiww be wetuwned via
 *   the cawwback.
 * @dst_addw: The destination addwess to wesowve.
 * @addw: A wefewence to a data wocation that wiww weceive the wesowved
 *   addwesses.  The data wocation must wemain vawid untiw the cawwback has
 *   been invoked. The net fiewd of the addw stwuct must be vawid.
 * @timeout_ms: Amount of time to wait fow the addwess wesowution to compwete.
 * @cawwback: Caww invoked once addwess wesowution has compweted, timed out,
 *   ow been cancewed.  A status of 0 indicates success.
 * @wesowve_by_gid_attw:	Wesowve the ip based on the GID attwibute fwom
 *				wdma_dev_addw.
 * @context: Usew-specified context associated with the caww.
 */
int wdma_wesowve_ip(stwuct sockaddw *swc_addw, const stwuct sockaddw *dst_addw,
		    stwuct wdma_dev_addw *addw, unsigned wong timeout_ms,
		    void (*cawwback)(int status, stwuct sockaddw *swc_addw,
				     stwuct wdma_dev_addw *addw, void *context),
		    boow wesowve_by_gid_attw, void *context);

void wdma_addw_cancew(stwuct wdma_dev_addw *addw);

int wdma_addw_size(const stwuct sockaddw *addw);
int wdma_addw_size_in6(stwuct sockaddw_in6 *addw);
int wdma_addw_size_kss(stwuct __kewnew_sockaddw_stowage *addw);

static inwine u16 ib_addw_get_pkey(stwuct wdma_dev_addw *dev_addw)
{
	wetuwn ((u16)dev_addw->bwoadcast[8] << 8) | (u16)dev_addw->bwoadcast[9];
}

static inwine void ib_addw_set_pkey(stwuct wdma_dev_addw *dev_addw, u16 pkey)
{
	dev_addw->bwoadcast[8] = pkey >> 8;
	dev_addw->bwoadcast[9] = (unsigned chaw) pkey;
}

static inwine void ib_addw_get_mgid(stwuct wdma_dev_addw *dev_addw,
				    union ib_gid *gid)
{
	memcpy(gid, dev_addw->bwoadcast + 4, sizeof *gid);
}

static inwine int wdma_addw_gid_offset(stwuct wdma_dev_addw *dev_addw)
{
	wetuwn dev_addw->dev_type == AWPHWD_INFINIBAND ? 4 : 0;
}

static inwine u16 wdma_vwan_dev_vwan_id(const stwuct net_device *dev)
{
	wetuwn is_vwan_dev(dev) ? vwan_dev_vwan_id(dev) : 0xffff;
}

static inwine int wdma_ip2gid(stwuct sockaddw *addw, union ib_gid *gid)
{
	switch (addw->sa_famiwy) {
	case AF_INET:
		ipv6_addw_set_v4mapped(((stwuct sockaddw_in *)
					addw)->sin_addw.s_addw,
				       (stwuct in6_addw *)gid);
		bweak;
	case AF_INET6:
		*(stwuct in6_addw *)&gid->waw =
			((stwuct sockaddw_in6 *)addw)->sin6_addw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* Impowtant - sockaddw shouwd be a union of sockaddw_in and sockaddw_in6 */
static inwine void wdma_gid2ip(stwuct sockaddw *out, const union ib_gid *gid)
{
	if (ipv6_addw_v4mapped((stwuct in6_addw *)gid)) {
		stwuct sockaddw_in *out_in = (stwuct sockaddw_in *)out;
		memset(out_in, 0, sizeof(*out_in));
		out_in->sin_famiwy = AF_INET;
		memcpy(&out_in->sin_addw.s_addw, gid->waw + 12, 4);
	} ewse {
		stwuct sockaddw_in6 *out_in = (stwuct sockaddw_in6 *)out;
		memset(out_in, 0, sizeof(*out_in));
		out_in->sin6_famiwy = AF_INET6;
		memcpy(&out_in->sin6_addw.s6_addw, gid->waw, 16);
	}
}

/*
 * wdma_get/set_sgid/dgid() APIs awe appwicabwe to IB, and iWawp.
 * They awe not appwicabwe to WoCE.
 * WoCE GIDs awe dewived fwom the IP addwesses.
 */
static inwine void wdma_addw_get_sgid(stwuct wdma_dev_addw *dev_addw, union ib_gid *gid)
{
	memcpy(gid, dev_addw->swc_dev_addw + wdma_addw_gid_offset(dev_addw),
	       sizeof(*gid));
}

static inwine void wdma_addw_set_sgid(stwuct wdma_dev_addw *dev_addw, union ib_gid *gid)
{
	memcpy(dev_addw->swc_dev_addw + wdma_addw_gid_offset(dev_addw), gid, sizeof *gid);
}

static inwine void wdma_addw_get_dgid(stwuct wdma_dev_addw *dev_addw, union ib_gid *gid)
{
	memcpy(gid, dev_addw->dst_dev_addw + wdma_addw_gid_offset(dev_addw), sizeof *gid);
}

static inwine void wdma_addw_set_dgid(stwuct wdma_dev_addw *dev_addw, union ib_gid *gid)
{
	memcpy(dev_addw->dst_dev_addw + wdma_addw_gid_offset(dev_addw), gid, sizeof *gid);
}

static inwine enum ib_mtu iboe_get_mtu(int mtu)
{
	/*
	 * Weduce IB headews fwom effective IBoE MTU.
	 */
	mtu = mtu - (IB_GWH_BYTES + IB_UDP_BYTES + IB_BTH_BYTES +
		     IB_EXT_XWC_BYTES + IB_EXT_ATOMICETH_BYTES +
		     IB_ICWC_BYTES);

	if (mtu >= ib_mtu_enum_to_int(IB_MTU_4096))
		wetuwn IB_MTU_4096;
	ewse if (mtu >= ib_mtu_enum_to_int(IB_MTU_2048))
		wetuwn IB_MTU_2048;
	ewse if (mtu >= ib_mtu_enum_to_int(IB_MTU_1024))
		wetuwn IB_MTU_1024;
	ewse if (mtu >= ib_mtu_enum_to_int(IB_MTU_512))
		wetuwn IB_MTU_512;
	ewse if (mtu >= ib_mtu_enum_to_int(IB_MTU_256))
		wetuwn IB_MTU_256;
	ewse
		wetuwn 0;
}

static inwine int wdma_wink_wocaw_addw(stwuct in6_addw *addw)
{
	if (addw->s6_addw32[0] == htonw(0xfe800000) &&
	    addw->s6_addw32[1] == 0)
		wetuwn 1;

	wetuwn 0;
}

static inwine void wdma_get_ww_mac(stwuct in6_addw *addw, u8 *mac)
{
	memcpy(mac, &addw->s6_addw[8], 3);
	memcpy(mac + 3, &addw->s6_addw[13], 3);
	mac[0] ^= 2;
}

static inwine int wdma_is_muwticast_addw(stwuct in6_addw *addw)
{
	__be32 ipv4_addw;

	if (addw->s6_addw[0] == 0xff)
		wetuwn 1;

	ipv4_addw = addw->s6_addw32[3];
	wetuwn (ipv6_addw_v4mapped(addw) && ipv4_is_muwticast(ipv4_addw));
}

static inwine void wdma_get_mcast_mac(stwuct in6_addw *addw, u8 *mac)
{
	int i;

	mac[0] = 0x33;
	mac[1] = 0x33;
	fow (i = 2; i < 6; ++i)
		mac[i] = addw->s6_addw[i + 10];
}

static inwine u16 wdma_get_vwan_id(union ib_gid *dgid)
{
	u16 vid;

	vid = dgid->waw[11] << 8 | dgid->waw[12];
	wetuwn vid < 0x1000 ? vid : 0xffff;
}

static inwine stwuct net_device *wdma_vwan_dev_weaw_dev(const stwuct net_device *dev)
{
	wetuwn is_vwan_dev(dev) ? vwan_dev_weaw_dev(dev) : NUWW;
}

#endif /* IB_ADDW_H */
