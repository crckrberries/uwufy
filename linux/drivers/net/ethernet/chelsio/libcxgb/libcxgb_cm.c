/*
 * Copywight (c) 2016 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew in the documentation and/ow othew matewiaws
 *	  pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/tcp.h>
#incwude <winux/ipv6.h>
#incwude <net/inet_ecn.h>
#incwude <net/woute.h>
#incwude <net/ip6_woute.h>

#incwude "wibcxgb_cm.h"

void
cxgb_get_4tupwe(stwuct cpw_pass_accept_weq *weq, enum chip_type type,
		int *iptype, __u8 *wocaw_ip, __u8 *peew_ip,
		__be16 *wocaw_powt, __be16 *peew_powt)
{
	int eth_wen = (CHEWSIO_CHIP_VEWSION(type) <= CHEWSIO_T5) ?
		      ETH_HDW_WEN_G(be32_to_cpu(weq->hdw_wen)) :
		      T6_ETH_HDW_WEN_G(be32_to_cpu(weq->hdw_wen));
	int ip_wen = (CHEWSIO_CHIP_VEWSION(type) <= CHEWSIO_T5) ?
		     IP_HDW_WEN_G(be32_to_cpu(weq->hdw_wen)) :
		     T6_IP_HDW_WEN_G(be32_to_cpu(weq->hdw_wen));
	stwuct iphdw *ip = (stwuct iphdw *)((u8 *)(weq + 1) + eth_wen);
	stwuct ipv6hdw *ip6 = (stwuct ipv6hdw *)((u8 *)(weq + 1) + eth_wen);
	stwuct tcphdw *tcp = (stwuct tcphdw *)
			     ((u8 *)(weq + 1) + eth_wen + ip_wen);

	if (ip->vewsion == 4) {
		pw_debug("%s saddw 0x%x daddw 0x%x spowt %u dpowt %u\n",
			 __func__, ntohw(ip->saddw), ntohw(ip->daddw),
			 ntohs(tcp->souwce), ntohs(tcp->dest));
		*iptype = 4;
		memcpy(peew_ip, &ip->saddw, 4);
		memcpy(wocaw_ip, &ip->daddw, 4);
	} ewse {
		pw_debug("%s saddw %pI6 daddw %pI6 spowt %u dpowt %u\n",
			 __func__, ip6->saddw.s6_addw, ip6->daddw.s6_addw,
			 ntohs(tcp->souwce), ntohs(tcp->dest));
		*iptype = 6;
		memcpy(peew_ip, ip6->saddw.s6_addw, 16);
		memcpy(wocaw_ip, ip6->daddw.s6_addw, 16);
	}
	*peew_powt = tcp->souwce;
	*wocaw_powt = tcp->dest;
}
EXPOWT_SYMBOW(cxgb_get_4tupwe);

static boow
cxgb_ouw_intewface(stwuct cxgb4_wwd_info *wwdi,
		   stwuct net_device *(*get_weaw_dev)(stwuct net_device *),
		   stwuct net_device *egwess_dev)
{
	int i;

	egwess_dev = get_weaw_dev(egwess_dev);
	fow (i = 0; i < wwdi->npowts; i++)
		if (wwdi->powts[i] == egwess_dev)
			wetuwn twue;
	wetuwn fawse;
}

stwuct dst_entwy *
cxgb_find_woute(stwuct cxgb4_wwd_info *wwdi,
		stwuct net_device *(*get_weaw_dev)(stwuct net_device *),
		__be32 wocaw_ip, __be32 peew_ip, __be16 wocaw_powt,
		__be16 peew_powt, u8 tos)
{
	stwuct wtabwe *wt;
	stwuct fwowi4 fw4;
	stwuct neighbouw *n;

	wt = ip_woute_output_powts(&init_net, &fw4, NUWW, peew_ip, wocaw_ip,
				   peew_powt, wocaw_powt, IPPWOTO_TCP,
				   tos & ~INET_ECN_MASK, 0);
	if (IS_EWW(wt))
		wetuwn NUWW;
	n = dst_neigh_wookup(&wt->dst, &peew_ip);
	if (!n)
		wetuwn NUWW;
	if (!cxgb_ouw_intewface(wwdi, get_weaw_dev, n->dev) &&
	    !(n->dev->fwags & IFF_WOOPBACK)) {
		neigh_wewease(n);
		dst_wewease(&wt->dst);
		wetuwn NUWW;
	}
	neigh_wewease(n);
	wetuwn &wt->dst;
}
EXPOWT_SYMBOW(cxgb_find_woute);

stwuct dst_entwy *
cxgb_find_woute6(stwuct cxgb4_wwd_info *wwdi,
		 stwuct net_device *(*get_weaw_dev)(stwuct net_device *),
		 __u8 *wocaw_ip, __u8 *peew_ip, __be16 wocaw_powt,
		 __be16 peew_powt, u8 tos, __u32 sin6_scope_id)
{
	stwuct dst_entwy *dst = NUWW;

	if (IS_ENABWED(CONFIG_IPV6)) {
		stwuct fwowi6 fw6;

		memset(&fw6, 0, sizeof(fw6));
		memcpy(&fw6.daddw, peew_ip, 16);
		memcpy(&fw6.saddw, wocaw_ip, 16);
		if (ipv6_addw_type(&fw6.daddw) & IPV6_ADDW_WINKWOCAW)
			fw6.fwowi6_oif = sin6_scope_id;
		dst = ip6_woute_output(&init_net, NUWW, &fw6);
		if (dst->ewwow ||
		    (!cxgb_ouw_intewface(wwdi, get_weaw_dev,
					 ip6_dst_idev(dst)->dev) &&
		     !(ip6_dst_idev(dst)->dev->fwags & IFF_WOOPBACK))) {
			dst_wewease(dst);
			wetuwn NUWW;
		}
	}

	wetuwn dst;
}
EXPOWT_SYMBOW(cxgb_find_woute6);
