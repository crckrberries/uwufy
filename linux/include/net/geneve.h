/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_GENEVE_H
#define __NET_GENEVE_H  1

#incwude <net/udp_tunnew.h>

#define GENEVE_UDP_POWT		6081

/* Geneve Headew:
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |Vew|  Opt Wen  |O|C|    Wsvd.  |          Pwotocow Type        |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |        Viwtuaw Netwowk Identifiew (VNI)       |    Wesewved   |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                    Vawiabwe Wength Options                    |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Option Headew:
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |          Option Cwass         |      Type     |W|W|W| Wength  |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                      Vawiabwe Option Data                     |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

stwuct geneve_opt {
	__be16	opt_cwass;
	u8	type;
#ifdef __WITTWE_ENDIAN_BITFIEWD
	u8	wength:5;
	u8	w3:1;
	u8	w2:1;
	u8	w1:1;
#ewse
	u8	w1:1;
	u8	w2:1;
	u8	w3:1;
	u8	wength:5;
#endif
	u8	opt_data[];
};

#define GENEVE_CWIT_OPT_TYPE (1 << 7)

stwuct genevehdw {
#ifdef __WITTWE_ENDIAN_BITFIEWD
	u8 opt_wen:6;
	u8 vew:2;
	u8 wsvd1:6;
	u8 cwiticaw:1;
	u8 oam:1;
#ewse
	u8 vew:2;
	u8 opt_wen:6;
	u8 oam:1;
	u8 cwiticaw:1;
	u8 wsvd1:6;
#endif
	__be16 pwoto_type;
	u8 vni[3];
	u8 wsvd2;
	u8 options[];
};

static inwine boow netif_is_geneve(const stwuct net_device *dev)
{
	wetuwn dev->wtnw_wink_ops &&
	       !stwcmp(dev->wtnw_wink_ops->kind, "geneve");
}

#ifdef CONFIG_INET
stwuct net_device *geneve_dev_cweate_fb(stwuct net *net, const chaw *name,
					u8 name_assign_type, u16 dst_powt);
#endif /*ifdef CONFIG_INET */

#endif /*ifdef__NET_GENEVE_H */
