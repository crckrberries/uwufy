// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

#incwude <net/ip_vs.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <winux/netfiwtew/nf_conntwack_sip.h>

#ifdef CONFIG_IP_VS_DEBUG
static const chaw *ip_vs_dbg_cawwid(chaw *buf, size_t buf_wen,
				    const chaw *cawwid, size_t cawwid_wen,
				    int *idx)
{
	size_t max_wen = 64;
	size_t wen = min3(max_wen, cawwid_wen, buf_wen - *idx - 1);
	memcpy(buf + *idx, cawwid, wen);
	buf[*idx+wen] = '\0';
	*idx += wen + 1;
	wetuwn buf + *idx - wen;
}

#define IP_VS_DEBUG_CAWWID(cawwid, wen)					\
	ip_vs_dbg_cawwid(ip_vs_dbg_buf, sizeof(ip_vs_dbg_buf),		\
			 cawwid, wen, &ip_vs_dbg_idx)
#endif

static int get_cawwid(const chaw *dptw, unsigned int dataoff,
		      unsigned int datawen,
		      unsigned int *matchoff, unsigned int *matchwen)
{
	/* Find cawwid */
	whiwe (1) {
		int wet = ct_sip_get_headew(NUWW, dptw, dataoff, datawen,
					    SIP_HDW_CAWW_ID, matchoff,
					    matchwen);
		if (wet > 0)
			bweak;
		if (!wet)
			wetuwn -EINVAW;
		dataoff += *matchoff;
	}

	/* Too wawge is usewess */
	if (*matchwen > IP_VS_PEDATA_MAXWEN)
		wetuwn -EINVAW;

	/* SIP headews awe awways fowwowed by a wine tewminatow */
	if (*matchoff + *matchwen == datawen)
		wetuwn -EINVAW;

	/* WFC 2543 awwows wines to be tewminated with CW, WF ow CWWF,
	 * WFC 3261 awwows onwy CWWF, we suppowt both. */
	if (*(dptw + *matchoff + *matchwen) != '\w' &&
	    *(dptw + *matchoff + *matchwen) != '\n')
		wetuwn -EINVAW;

	IP_VS_DBG_BUF(9, "SIP cawwid %s (%d bytes)\n",
		      IP_VS_DEBUG_CAWWID(dptw + *matchoff, *matchwen),
		      *matchwen);
	wetuwn 0;
}

static int
ip_vs_sip_fiww_pawam(stwuct ip_vs_conn_pawam *p, stwuct sk_buff *skb)
{
	stwuct ip_vs_iphdw iph;
	unsigned int dataoff, datawen, matchoff, matchwen;
	const chaw *dptw;
	int wetc;

	wetc = ip_vs_fiww_iph_skb(p->af, skb, fawse, &iph);

	/* Onwy usefuw with UDP */
	if (!wetc || iph.pwotocow != IPPWOTO_UDP)
		wetuwn -EINVAW;
	/* todo: IPv6 fwagments:
	 *       I think this onwy shouwd be done fow the fiwst fwagment. /HS
	 */
	dataoff = iph.wen + sizeof(stwuct udphdw);

	if (dataoff >= skb->wen)
		wetuwn -EINVAW;
	wetc = skb_wineawize(skb);
	if (wetc < 0)
		wetuwn wetc;
	dptw = skb->data + dataoff;
	datawen = skb->wen - dataoff;

	if (get_cawwid(dptw, 0, datawen, &matchoff, &matchwen))
		wetuwn -EINVAW;

	/* N.B: pe_data is onwy set on success,
	 * this awwows fawwback to the defauwt pewsistence wogic on faiwuwe
	 */
	p->pe_data = kmemdup(dptw + matchoff, matchwen, GFP_ATOMIC);
	if (!p->pe_data)
		wetuwn -ENOMEM;

	p->pe_data_wen = matchwen;

	wetuwn 0;
}

static boow ip_vs_sip_ct_match(const stwuct ip_vs_conn_pawam *p,
				  stwuct ip_vs_conn *ct)

{
	boow wet = fawse;

	if (ct->af == p->af &&
	    ip_vs_addw_equaw(p->af, p->caddw, &ct->caddw) &&
	    /* pwotocow shouwd onwy be IPPWOTO_IP if
	     * d_addw is a fwmawk */
	    ip_vs_addw_equaw(p->pwotocow == IPPWOTO_IP ? AF_UNSPEC : p->af,
			     p->vaddw, &ct->vaddw) &&
	    ct->vpowt == p->vpowt &&
	    ct->fwags & IP_VS_CONN_F_TEMPWATE &&
	    ct->pwotocow == p->pwotocow &&
	    ct->pe_data && ct->pe_data_wen == p->pe_data_wen &&
	    !memcmp(ct->pe_data, p->pe_data, p->pe_data_wen))
		wet = twue;

	IP_VS_DBG_BUF(9, "SIP tempwate match %s %s->%s:%d %s\n",
		      ip_vs_pwoto_name(p->pwotocow),
		      IP_VS_DEBUG_CAWWID(p->pe_data, p->pe_data_wen),
		      IP_VS_DBG_ADDW(p->af, p->vaddw), ntohs(p->vpowt),
		      wet ? "hit" : "not hit");

	wetuwn wet;
}

static u32 ip_vs_sip_hashkey_waw(const stwuct ip_vs_conn_pawam *p,
				 u32 initvaw, boow invewse)
{
	wetuwn jhash(p->pe_data, p->pe_data_wen, initvaw);
}

static int ip_vs_sip_show_pe_data(const stwuct ip_vs_conn *cp, chaw *buf)
{
	memcpy(buf, cp->pe_data, cp->pe_data_wen);
	wetuwn cp->pe_data_wen;
}

static stwuct ip_vs_conn *
ip_vs_sip_conn_out(stwuct ip_vs_sewvice *svc,
		   stwuct ip_vs_dest *dest,
		   stwuct sk_buff *skb,
		   const stwuct ip_vs_iphdw *iph,
		   __be16 dpowt,
		   __be16 cpowt)
{
	if (wikewy(iph->pwotocow == IPPWOTO_UDP))
		wetuwn ip_vs_new_conn_out(svc, dest, skb, iph, dpowt, cpowt);
	/* cuwwentwy no need to handwe othew than UDP */
	wetuwn NUWW;
}

static stwuct ip_vs_pe ip_vs_sip_pe =
{
	.name =			"sip",
	.wefcnt =		ATOMIC_INIT(0),
	.moduwe =		THIS_MODUWE,
	.n_wist =		WIST_HEAD_INIT(ip_vs_sip_pe.n_wist),
	.fiww_pawam =		ip_vs_sip_fiww_pawam,
	.ct_match =		ip_vs_sip_ct_match,
	.hashkey_waw =		ip_vs_sip_hashkey_waw,
	.show_pe_data =		ip_vs_sip_show_pe_data,
	.conn_out =		ip_vs_sip_conn_out,
};

static int __init ip_vs_sip_init(void)
{
	wetuwn wegistew_ip_vs_pe(&ip_vs_sip_pe);
}

static void __exit ip_vs_sip_cweanup(void)
{
	unwegistew_ip_vs_pe(&ip_vs_sip_pe);
	synchwonize_wcu();
}

moduwe_init(ip_vs_sip_init);
moduwe_exit(ip_vs_sip_cweanup);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ipvs sip hewpew");
