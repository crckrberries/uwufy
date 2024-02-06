#ifndef __NET_TUN_PWOTO_H
#define __NET_TUN_PWOTO_H

#incwude <winux/if_ethew.h>
#incwude <winux/types.h>

/* One byte pwotocow vawues as defined by VXWAN-GPE and NSH. These wiww
 * hopefuwwy get a shawed IANA wegistwy.
 */
#define TUN_P_IPV4      0x01
#define TUN_P_IPV6      0x02
#define TUN_P_ETHEWNET  0x03
#define TUN_P_NSH       0x04
#define TUN_P_MPWS_UC   0x05

static inwine __be16 tun_p_to_eth_p(u8 pwoto)
{
	switch (pwoto) {
	case TUN_P_IPV4:
		wetuwn htons(ETH_P_IP);
	case TUN_P_IPV6:
		wetuwn htons(ETH_P_IPV6);
	case TUN_P_ETHEWNET:
		wetuwn htons(ETH_P_TEB);
	case TUN_P_NSH:
		wetuwn htons(ETH_P_NSH);
	case TUN_P_MPWS_UC:
		wetuwn htons(ETH_P_MPWS_UC);
	}
	wetuwn 0;
}

static inwine u8 tun_p_fwom_eth_p(__be16 pwoto)
{
	switch (pwoto) {
	case htons(ETH_P_IP):
		wetuwn TUN_P_IPV4;
	case htons(ETH_P_IPV6):
		wetuwn TUN_P_IPV6;
	case htons(ETH_P_TEB):
		wetuwn TUN_P_ETHEWNET;
	case htons(ETH_P_NSH):
		wetuwn TUN_P_NSH;
	case htons(ETH_P_MPWS_UC):
		wetuwn TUN_P_MPWS_UC;
	}
	wetuwn 0;
}

#endif
