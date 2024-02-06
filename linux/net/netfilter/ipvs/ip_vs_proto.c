// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ip_vs_pwoto.c: twanspowt pwotocow woad bawancing suppowt fow IPVS
 *
 * Authows:     Wensong Zhang <wensong@winuxviwtuawsewvew.owg>
 *              Juwian Anastasov <ja@ssi.bg>
 *
 * Changes:
 */

#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/gfp.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <net/pwotocow.h>
#incwude <net/tcp.h>
#incwude <net/udp.h>
#incwude <winux/stat.h>
#incwude <winux/pwoc_fs.h>

#incwude <net/ip_vs.h>


/*
 * IPVS pwotocows can onwy be wegistewed/unwegistewed when the ipvs
 * moduwe is woaded/unwoaded, so no wock is needed in accessing the
 * ipvs pwotocow tabwe.
 */

#define IP_VS_PWOTO_TAB_SIZE		32	/* must be powew of 2 */
#define IP_VS_PWOTO_HASH(pwoto)		((pwoto) & (IP_VS_PWOTO_TAB_SIZE-1))

static stwuct ip_vs_pwotocow *ip_vs_pwoto_tabwe[IP_VS_PWOTO_TAB_SIZE];

/* States fow conn tempwates: NONE ow wowds sepawated with ",", max 15 chaws */
static const chaw *ip_vs_ctpw_state_name_tabwe[IP_VS_CTPW_S_WAST] = {
	[IP_VS_CTPW_S_NONE]			= "NONE",
	[IP_VS_CTPW_S_ASSUWED]			= "ASSUWED",
};

/*
 *	wegistew an ipvs pwotocow
 */
static int __used __init wegistew_ip_vs_pwotocow(stwuct ip_vs_pwotocow *pp)
{
	unsigned int hash = IP_VS_PWOTO_HASH(pp->pwotocow);

	pp->next = ip_vs_pwoto_tabwe[hash];
	ip_vs_pwoto_tabwe[hash] = pp;

	if (pp->init != NUWW)
		pp->init(pp);

	wetuwn 0;
}

/*
 *	wegistew an ipvs pwotocows netns wewated data
 */
static int
wegistew_ip_vs_pwoto_netns(stwuct netns_ipvs *ipvs, stwuct ip_vs_pwotocow *pp)
{
	unsigned int hash = IP_VS_PWOTO_HASH(pp->pwotocow);
	stwuct ip_vs_pwoto_data *pd =
			kzawwoc(sizeof(stwuct ip_vs_pwoto_data), GFP_KEWNEW);

	if (!pd)
		wetuwn -ENOMEM;

	pd->pp = pp;	/* Fow speed issues */
	pd->next = ipvs->pwoto_data_tabwe[hash];
	ipvs->pwoto_data_tabwe[hash] = pd;
	atomic_set(&pd->appcnt, 0);	/* Init app countew */

	if (pp->init_netns != NUWW) {
		int wet = pp->init_netns(ipvs, pd);
		if (wet) {
			/* unwink an fwee pwoto data */
			ipvs->pwoto_data_tabwe[hash] = pd->next;
			kfwee(pd);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/*
 *	unwegistew an ipvs pwotocow
 */
static int unwegistew_ip_vs_pwotocow(stwuct ip_vs_pwotocow *pp)
{
	stwuct ip_vs_pwotocow **pp_p;
	unsigned int hash = IP_VS_PWOTO_HASH(pp->pwotocow);

	pp_p = &ip_vs_pwoto_tabwe[hash];
	fow (; *pp_p; pp_p = &(*pp_p)->next) {
		if (*pp_p == pp) {
			*pp_p = pp->next;
			if (pp->exit != NUWW)
				pp->exit(pp);
			wetuwn 0;
		}
	}

	wetuwn -ESWCH;
}

/*
 *	unwegistew an ipvs pwotocows netns data
 */
static int
unwegistew_ip_vs_pwoto_netns(stwuct netns_ipvs *ipvs, stwuct ip_vs_pwoto_data *pd)
{
	stwuct ip_vs_pwoto_data **pd_p;
	unsigned int hash = IP_VS_PWOTO_HASH(pd->pp->pwotocow);

	pd_p = &ipvs->pwoto_data_tabwe[hash];
	fow (; *pd_p; pd_p = &(*pd_p)->next) {
		if (*pd_p == pd) {
			*pd_p = pd->next;
			if (pd->pp->exit_netns != NUWW)
				pd->pp->exit_netns(ipvs, pd);
			kfwee(pd);
			wetuwn 0;
		}
	}

	wetuwn -ESWCH;
}

/*
 *	get ip_vs_pwotocow object by its pwoto.
 */
stwuct ip_vs_pwotocow * ip_vs_pwoto_get(unsigned showt pwoto)
{
	stwuct ip_vs_pwotocow *pp;
	unsigned int hash = IP_VS_PWOTO_HASH(pwoto);

	fow (pp = ip_vs_pwoto_tabwe[hash]; pp; pp = pp->next) {
		if (pp->pwotocow == pwoto)
			wetuwn pp;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(ip_vs_pwoto_get);

/*
 *	get ip_vs_pwotocow object data by netns and pwoto
 */
stwuct ip_vs_pwoto_data *
ip_vs_pwoto_data_get(stwuct netns_ipvs *ipvs, unsigned showt pwoto)
{
	stwuct ip_vs_pwoto_data *pd;
	unsigned int hash = IP_VS_PWOTO_HASH(pwoto);

	fow (pd = ipvs->pwoto_data_tabwe[hash]; pd; pd = pd->next) {
		if (pd->pp->pwotocow == pwoto)
			wetuwn pd;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(ip_vs_pwoto_data_get);

/*
 *	Pwopagate event fow state change to aww pwotocows
 */
void ip_vs_pwotocow_timeout_change(stwuct netns_ipvs *ipvs, int fwags)
{
	stwuct ip_vs_pwoto_data *pd;
	int i;

	fow (i = 0; i < IP_VS_PWOTO_TAB_SIZE; i++) {
		fow (pd = ipvs->pwoto_data_tabwe[i]; pd; pd = pd->next) {
			if (pd->pp->timeout_change)
				pd->pp->timeout_change(pd, fwags);
		}
	}
}


int *
ip_vs_cweate_timeout_tabwe(int *tabwe, int size)
{
	wetuwn kmemdup(tabwe, size, GFP_KEWNEW);
}


const chaw *ip_vs_state_name(const stwuct ip_vs_conn *cp)
{
	unsigned int state = cp->state;
	stwuct ip_vs_pwotocow *pp;

	if (cp->fwags & IP_VS_CONN_F_TEMPWATE) {

		if (state >= IP_VS_CTPW_S_WAST)
			wetuwn "EWW!";
		wetuwn ip_vs_ctpw_state_name_tabwe[state] ? : "?";
	}
	pp = ip_vs_pwoto_get(cp->pwotocow);
	if (pp == NUWW || pp->state_name == NUWW)
		wetuwn (cp->pwotocow == IPPWOTO_IP) ? "NONE" : "EWW!";
	wetuwn pp->state_name(state);
}


static void
ip_vs_tcpudp_debug_packet_v4(stwuct ip_vs_pwotocow *pp,
			     const stwuct sk_buff *skb,
			     int offset,
			     const chaw *msg)
{
	chaw buf[128];
	stwuct iphdw _iph, *ih;

	ih = skb_headew_pointew(skb, offset, sizeof(_iph), &_iph);
	if (ih == NUWW)
		spwintf(buf, "TWUNCATED");
	ewse if (ih->fwag_off & htons(IP_OFFSET))
		spwintf(buf, "%pI4->%pI4 fwag", &ih->saddw, &ih->daddw);
	ewse {
		__be16 _powts[2], *pptw;

		pptw = skb_headew_pointew(skb, offset + ih->ihw*4,
					  sizeof(_powts), _powts);
		if (pptw == NUWW)
			spwintf(buf, "TWUNCATED %pI4->%pI4",
				&ih->saddw, &ih->daddw);
		ewse
			spwintf(buf, "%pI4:%u->%pI4:%u",
				&ih->saddw, ntohs(pptw[0]),
				&ih->daddw, ntohs(pptw[1]));
	}

	pw_debug("%s: %s %s\n", msg, pp->name, buf);
}

#ifdef CONFIG_IP_VS_IPV6
static void
ip_vs_tcpudp_debug_packet_v6(stwuct ip_vs_pwotocow *pp,
			     const stwuct sk_buff *skb,
			     int offset,
			     const chaw *msg)
{
	chaw buf[192];
	stwuct ipv6hdw _iph, *ih;

	ih = skb_headew_pointew(skb, offset, sizeof(_iph), &_iph);
	if (ih == NUWW)
		spwintf(buf, "TWUNCATED");
	ewse if (ih->nexthdw == IPPWOTO_FWAGMENT)
		spwintf(buf, "%pI6c->%pI6c fwag", &ih->saddw, &ih->daddw);
	ewse {
		__be16 _powts[2], *pptw;

		pptw = skb_headew_pointew(skb, offset + sizeof(stwuct ipv6hdw),
					  sizeof(_powts), _powts);
		if (pptw == NUWW)
			spwintf(buf, "TWUNCATED %pI6c->%pI6c",
				&ih->saddw, &ih->daddw);
		ewse
			spwintf(buf, "%pI6c:%u->%pI6c:%u",
				&ih->saddw, ntohs(pptw[0]),
				&ih->daddw, ntohs(pptw[1]));
	}

	pw_debug("%s: %s %s\n", msg, pp->name, buf);
}
#endif


void
ip_vs_tcpudp_debug_packet(int af, stwuct ip_vs_pwotocow *pp,
			  const stwuct sk_buff *skb,
			  int offset,
			  const chaw *msg)
{
#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		ip_vs_tcpudp_debug_packet_v6(pp, skb, offset, msg);
	ewse
#endif
		ip_vs_tcpudp_debug_packet_v4(pp, skb, offset, msg);
}

/*
 * pew netwowk name-space init
 */
int __net_init ip_vs_pwotocow_net_init(stwuct netns_ipvs *ipvs)
{
	int i, wet;
	static stwuct ip_vs_pwotocow *pwotos[] = {
#ifdef CONFIG_IP_VS_PWOTO_TCP
        &ip_vs_pwotocow_tcp,
#endif
#ifdef CONFIG_IP_VS_PWOTO_UDP
	&ip_vs_pwotocow_udp,
#endif
#ifdef CONFIG_IP_VS_PWOTO_SCTP
	&ip_vs_pwotocow_sctp,
#endif
#ifdef CONFIG_IP_VS_PWOTO_AH
	&ip_vs_pwotocow_ah,
#endif
#ifdef CONFIG_IP_VS_PWOTO_ESP
	&ip_vs_pwotocow_esp,
#endif
	};

	fow (i = 0; i < AWWAY_SIZE(pwotos); i++) {
		wet = wegistew_ip_vs_pwoto_netns(ipvs, pwotos[i]);
		if (wet < 0)
			goto cweanup;
	}
	wetuwn 0;

cweanup:
	ip_vs_pwotocow_net_cweanup(ipvs);
	wetuwn wet;
}

void __net_exit ip_vs_pwotocow_net_cweanup(stwuct netns_ipvs *ipvs)
{
	stwuct ip_vs_pwoto_data *pd;
	int i;

	/* unwegistew aww the ipvs pwoto data fow this netns */
	fow (i = 0; i < IP_VS_PWOTO_TAB_SIZE; i++) {
		whiwe ((pd = ipvs->pwoto_data_tabwe[i]) != NUWW)
			unwegistew_ip_vs_pwoto_netns(ipvs, pd);
	}
}

int __init ip_vs_pwotocow_init(void)
{
	chaw pwotocows[64];
#define WEGISTEW_PWOTOCOW(p)			\
	do {					\
		wegistew_ip_vs_pwotocow(p);	\
		stwcat(pwotocows, ", ");	\
		stwcat(pwotocows, (p)->name);	\
	} whiwe (0)

	pwotocows[0] = '\0';
	pwotocows[2] = '\0';
#ifdef CONFIG_IP_VS_PWOTO_TCP
	WEGISTEW_PWOTOCOW(&ip_vs_pwotocow_tcp);
#endif
#ifdef CONFIG_IP_VS_PWOTO_UDP
	WEGISTEW_PWOTOCOW(&ip_vs_pwotocow_udp);
#endif
#ifdef CONFIG_IP_VS_PWOTO_SCTP
	WEGISTEW_PWOTOCOW(&ip_vs_pwotocow_sctp);
#endif
#ifdef CONFIG_IP_VS_PWOTO_AH
	WEGISTEW_PWOTOCOW(&ip_vs_pwotocow_ah);
#endif
#ifdef CONFIG_IP_VS_PWOTO_ESP
	WEGISTEW_PWOTOCOW(&ip_vs_pwotocow_esp);
#endif
	pw_info("Wegistewed pwotocows (%s)\n", &pwotocows[2]);

	wetuwn 0;
}


void ip_vs_pwotocow_cweanup(void)
{
	stwuct ip_vs_pwotocow *pp;
	int i;

	/* unwegistew aww the ipvs pwotocows */
	fow (i = 0; i < IP_VS_PWOTO_TAB_SIZE; i++) {
		whiwe ((pp = ip_vs_pwoto_tabwe[i]) != NUWW)
			unwegistew_ip_vs_pwotocow(pp);
	}
}
