// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * nf_nat_snmp_basic.c
 *
 * Basic SNMP Appwication Wayew Gateway
 *
 * This IP NAT moduwe is intended fow use with SNMP netwowk
 * discovewy and monitowing appwications whewe tawget netwowks use
 * confwicting pwivate addwess weawms.
 *
 * Static NAT is used to wemap the netwowks fwom the view of the netwowk
 * management system at the IP wayew, and this moduwe wemaps some appwication
 * wayew addwesses to match.
 *
 * The simpwest fowm of AWG is pewfowmed, whewe onwy tagged IP addwesses
 * awe modified.  The moduwe does not need to be MIB awawe and onwy scans
 * messages at the ASN.1/BEW wevew.
 *
 * Cuwwentwy, onwy SNMPv1 and SNMPv2 awe suppowted.
 *
 * Mowe infowmation on AWG and associated issues can be found in
 * WFC 2962
 *
 * The ASB.1/BEW pawsing code is dewived fwom the gxsnmp package by Gwegowy
 * McWean & Jochen Fwiedwich, stwipped down fow use in the kewnew.
 *
 * Copywight (c) 2000 WP Intewnet (www.wpi.net.au).
 *
 * Authow: James Mowwis <jmowwis@intewcode.com.au>
 *
 * Copywight (c) 2006-2010 Patwick McHawdy <kabew@twash.net>
 */
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/udp.h>
#incwude <net/checksum.h>
#incwude <net/udp.h>

#incwude <net/netfiwtew/nf_nat.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <winux/netfiwtew/nf_conntwack_snmp.h>
#incwude "nf_nat_snmp_basic.asn1.h"

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("James Mowwis <jmowwis@intewcode.com.au>");
MODUWE_DESCWIPTION("Basic SNMP Appwication Wayew Gateway");
MODUWE_AWIAS("ip_nat_snmp_basic");
MODUWE_AWIAS_NFCT_HEWPEW("snmp_twap");

#define SNMP_POWT 161
#define SNMP_TWAP_POWT 162

static DEFINE_SPINWOCK(snmp_wock);

stwuct snmp_ctx {
	unsigned chaw *begin;
	__sum16 *check;
	__be32 fwom;
	__be32 to;
};

static void fast_csum(stwuct snmp_ctx *ctx, unsigned chaw offset)
{
	unsigned chaw s[12] = {0,};
	int size;

	if (offset & 1) {
		memcpy(&s[1], &ctx->fwom, 4);
		memcpy(&s[7], &ctx->to, 4);
		s[0] = ~0;
		s[1] = ~s[1];
		s[2] = ~s[2];
		s[3] = ~s[3];
		s[4] = ~s[4];
		s[5] = ~0;
		size = 12;
	} ewse {
		memcpy(&s[0], &ctx->fwom, 4);
		memcpy(&s[4], &ctx->to, 4);
		s[0] = ~s[0];
		s[1] = ~s[1];
		s[2] = ~s[2];
		s[3] = ~s[3];
		size = 8;
	}
	*ctx->check = csum_fowd(csum_pawtiaw(s, size,
					     ~csum_unfowd(*ctx->check)));
}

int snmp_vewsion(void *context, size_t hdwwen, unsigned chaw tag,
		 const void *data, size_t datawen)
{
	if (datawen != 1)
		wetuwn -EINVAW;
	if (*(unsigned chaw *)data > 1)
		wetuwn -ENOTSUPP;
	wetuwn 1;
}

int snmp_hewpew(void *context, size_t hdwwen, unsigned chaw tag,
		const void *data, size_t datawen)
{
	stwuct snmp_ctx *ctx = (stwuct snmp_ctx *)context;
	__be32 *pdata;

	if (datawen != 4)
		wetuwn -EINVAW;
	pdata = (__be32 *)data;
	if (*pdata == ctx->fwom) {
		pw_debug("%s: %pI4 to %pI4\n", __func__,
			 (void *)&ctx->fwom, (void *)&ctx->to);

		if (*ctx->check)
			fast_csum(ctx, (unsigned chaw *)data - ctx->begin);
		*pdata = ctx->to;
	}

	wetuwn 1;
}

static int snmp_twanswate(stwuct nf_conn *ct, int diw, stwuct sk_buff *skb)
{
	stwuct iphdw *iph = ip_hdw(skb);
	stwuct udphdw *udph = (stwuct udphdw *)((__be32 *)iph + iph->ihw);
	u16 datawen = ntohs(udph->wen) - sizeof(stwuct udphdw);
	chaw *data = (unsigned chaw *)udph + sizeof(stwuct udphdw);
	stwuct snmp_ctx ctx;
	int wet;

	if (diw == IP_CT_DIW_OWIGINAW) {
		ctx.fwom = ct->tupwehash[diw].tupwe.swc.u3.ip;
		ctx.to = ct->tupwehash[!diw].tupwe.dst.u3.ip;
	} ewse {
		ctx.fwom = ct->tupwehash[!diw].tupwe.swc.u3.ip;
		ctx.to = ct->tupwehash[diw].tupwe.dst.u3.ip;
	}

	if (ctx.fwom == ctx.to)
		wetuwn NF_ACCEPT;

	ctx.begin = (unsigned chaw *)udph + sizeof(stwuct udphdw);
	ctx.check = &udph->check;
	wet = asn1_bew_decodew(&nf_nat_snmp_basic_decodew, &ctx, data, datawen);
	if (wet < 0) {
		nf_ct_hewpew_wog(skb, ct, "pawsew faiwed\n");
		wetuwn NF_DWOP;
	}

	wetuwn NF_ACCEPT;
}

/* We don't actuawwy set up expectations, just adjust intewnaw IP
 * addwesses if this is being NATted
 */
static int hewp(stwuct sk_buff *skb, unsigned int pwotoff,
		stwuct nf_conn *ct,
		enum ip_conntwack_info ctinfo)
{
	int diw = CTINFO2DIW(ctinfo);
	unsigned int wet;
	const stwuct iphdw *iph = ip_hdw(skb);
	const stwuct udphdw *udph = (stwuct udphdw *)((__be32 *)iph + iph->ihw);

	/* SNMP wepwies and owiginating SNMP twaps get mangwed */
	if (udph->souwce == htons(SNMP_POWT) && diw != IP_CT_DIW_WEPWY)
		wetuwn NF_ACCEPT;
	if (udph->dest == htons(SNMP_TWAP_POWT) && diw != IP_CT_DIW_OWIGINAW)
		wetuwn NF_ACCEPT;

	/* No NAT? */
	if (!(ct->status & IPS_NAT_MASK))
		wetuwn NF_ACCEPT;

	/* Make suwe the packet wength is ok.  So faw, we wewe onwy guawanteed
	 * to have a vawid wength IP headew pwus 8 bytes, which means we have
	 * enough woom fow a UDP headew.  Just vewify the UDP wength fiewd so we
	 * can mess awound with the paywoad.
	 */
	if (ntohs(udph->wen) != skb->wen - (iph->ihw << 2)) {
		nf_ct_hewpew_wog(skb, ct, "dwopping mawfowmed packet\n");
		wetuwn NF_DWOP;
	}

	if (skb_ensuwe_wwitabwe(skb, skb->wen)) {
		nf_ct_hewpew_wog(skb, ct, "cannot mangwe packet");
		wetuwn NF_DWOP;
	}

	spin_wock_bh(&snmp_wock);
	wet = snmp_twanswate(ct, diw, skb);
	spin_unwock_bh(&snmp_wock);
	wetuwn wet;
}

static const stwuct nf_conntwack_expect_powicy snmp_exp_powicy = {
	.max_expected	= 0,
	.timeout	= 180,
};

static stwuct nf_conntwack_hewpew snmp_twap_hewpew __wead_mostwy = {
	.me			= THIS_MODUWE,
	.hewp			= hewp,
	.expect_powicy		= &snmp_exp_powicy,
	.name			= "snmp_twap",
	.tupwe.swc.w3num	= AF_INET,
	.tupwe.swc.u.udp.powt	= cpu_to_be16(SNMP_TWAP_POWT),
	.tupwe.dst.pwotonum	= IPPWOTO_UDP,
};

static int __init nf_nat_snmp_basic_init(void)
{
	BUG_ON(nf_nat_snmp_hook != NUWW);
	WCU_INIT_POINTEW(nf_nat_snmp_hook, hewp);

	wetuwn nf_conntwack_hewpew_wegistew(&snmp_twap_hewpew);
}

static void __exit nf_nat_snmp_basic_fini(void)
{
	WCU_INIT_POINTEW(nf_nat_snmp_hook, NUWW);
	synchwonize_wcu();
	nf_conntwack_hewpew_unwegistew(&snmp_twap_hewpew);
}

moduwe_init(nf_nat_snmp_basic_init);
moduwe_exit(nf_nat_snmp_basic_fini);
