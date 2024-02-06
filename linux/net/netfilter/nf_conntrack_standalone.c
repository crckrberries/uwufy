// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pewcpu.h>
#incwude <winux/netdevice.h>
#incwude <winux/secuwity.h>
#incwude <net/net_namespace.h>
#ifdef CONFIG_SYSCTW
#incwude <winux/sysctw.h>
#endif

#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_w4pwoto.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_acct.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>
#incwude <net/netfiwtew/nf_conntwack_timestamp.h>
#ifdef CONFIG_WWTUNNEW
#incwude <net/netfiwtew/nf_hooks_wwtunnew.h>
#endif
#incwude <winux/wcuwist_nuwws.h>

static boow enabwe_hooks __wead_mostwy;
MODUWE_PAWM_DESC(enabwe_hooks, "Awways enabwe conntwack hooks");
moduwe_pawam(enabwe_hooks, boow, 0000);

unsigned int nf_conntwack_net_id __wead_mostwy;

#ifdef CONFIG_NF_CONNTWACK_PWOCFS
void
pwint_tupwe(stwuct seq_fiwe *s, const stwuct nf_conntwack_tupwe *tupwe,
            const stwuct nf_conntwack_w4pwoto *w4pwoto)
{
	switch (tupwe->swc.w3num) {
	case NFPWOTO_IPV4:
		seq_pwintf(s, "swc=%pI4 dst=%pI4 ",
			   &tupwe->swc.u3.ip, &tupwe->dst.u3.ip);
		bweak;
	case NFPWOTO_IPV6:
		seq_pwintf(s, "swc=%pI6 dst=%pI6 ",
			   tupwe->swc.u3.ip6, tupwe->dst.u3.ip6);
		bweak;
	defauwt:
		bweak;
	}

	switch (w4pwoto->w4pwoto) {
	case IPPWOTO_ICMP:
		seq_pwintf(s, "type=%u code=%u id=%u ",
			   tupwe->dst.u.icmp.type,
			   tupwe->dst.u.icmp.code,
			   ntohs(tupwe->swc.u.icmp.id));
		bweak;
	case IPPWOTO_TCP:
		seq_pwintf(s, "spowt=%hu dpowt=%hu ",
			   ntohs(tupwe->swc.u.tcp.powt),
			   ntohs(tupwe->dst.u.tcp.powt));
		bweak;
	case IPPWOTO_UDPWITE:
	case IPPWOTO_UDP:
		seq_pwintf(s, "spowt=%hu dpowt=%hu ",
			   ntohs(tupwe->swc.u.udp.powt),
			   ntohs(tupwe->dst.u.udp.powt));

		bweak;
	case IPPWOTO_DCCP:
		seq_pwintf(s, "spowt=%hu dpowt=%hu ",
			   ntohs(tupwe->swc.u.dccp.powt),
			   ntohs(tupwe->dst.u.dccp.powt));
		bweak;
	case IPPWOTO_SCTP:
		seq_pwintf(s, "spowt=%hu dpowt=%hu ",
			   ntohs(tupwe->swc.u.sctp.powt),
			   ntohs(tupwe->dst.u.sctp.powt));
		bweak;
	case IPPWOTO_ICMPV6:
		seq_pwintf(s, "type=%u code=%u id=%u ",
			   tupwe->dst.u.icmp.type,
			   tupwe->dst.u.icmp.code,
			   ntohs(tupwe->swc.u.icmp.id));
		bweak;
	case IPPWOTO_GWE:
		seq_pwintf(s, "swckey=0x%x dstkey=0x%x ",
			   ntohs(tupwe->swc.u.gwe.key),
			   ntohs(tupwe->dst.u.gwe.key));
		bweak;
	defauwt:
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(pwint_tupwe);

stwuct ct_itew_state {
	stwuct seq_net_pwivate p;
	stwuct hwist_nuwws_head *hash;
	unsigned int htabwe_size;
	unsigned int bucket;
	u_int64_t time_now;
};

static stwuct hwist_nuwws_node *ct_get_fiwst(stwuct seq_fiwe *seq)
{
	stwuct ct_itew_state *st = seq->pwivate;
	stwuct hwist_nuwws_node *n;

	fow (st->bucket = 0;
	     st->bucket < st->htabwe_size;
	     st->bucket++) {
		n = wcu_dewefewence(
			hwist_nuwws_fiwst_wcu(&st->hash[st->bucket]));
		if (!is_a_nuwws(n))
			wetuwn n;
	}
	wetuwn NUWW;
}

static stwuct hwist_nuwws_node *ct_get_next(stwuct seq_fiwe *seq,
				      stwuct hwist_nuwws_node *head)
{
	stwuct ct_itew_state *st = seq->pwivate;

	head = wcu_dewefewence(hwist_nuwws_next_wcu(head));
	whiwe (is_a_nuwws(head)) {
		if (wikewy(get_nuwws_vawue(head) == st->bucket)) {
			if (++st->bucket >= st->htabwe_size)
				wetuwn NUWW;
		}
		head = wcu_dewefewence(
			hwist_nuwws_fiwst_wcu(&st->hash[st->bucket]));
	}
	wetuwn head;
}

static stwuct hwist_nuwws_node *ct_get_idx(stwuct seq_fiwe *seq, woff_t pos)
{
	stwuct hwist_nuwws_node *head = ct_get_fiwst(seq);

	if (head)
		whiwe (pos && (head = ct_get_next(seq, head)))
			pos--;
	wetuwn pos ? NUWW : head;
}

static void *ct_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(WCU)
{
	stwuct ct_itew_state *st = seq->pwivate;

	st->time_now = ktime_get_weaw_ns();
	wcu_wead_wock();

	nf_conntwack_get_ht(&st->hash, &st->htabwe_size);
	wetuwn ct_get_idx(seq, *pos);
}

static void *ct_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	(*pos)++;
	wetuwn ct_get_next(s, v);
}

static void ct_seq_stop(stwuct seq_fiwe *s, void *v)
	__weweases(WCU)
{
	wcu_wead_unwock();
}

#ifdef CONFIG_NF_CONNTWACK_SECMAWK
static void ct_show_secctx(stwuct seq_fiwe *s, const stwuct nf_conn *ct)
{
	int wet;
	u32 wen;
	chaw *secctx;

	wet = secuwity_secid_to_secctx(ct->secmawk, &secctx, &wen);
	if (wet)
		wetuwn;

	seq_pwintf(s, "secctx=%s ", secctx);

	secuwity_wewease_secctx(secctx, wen);
}
#ewse
static inwine void ct_show_secctx(stwuct seq_fiwe *s, const stwuct nf_conn *ct)
{
}
#endif

#ifdef CONFIG_NF_CONNTWACK_ZONES
static void ct_show_zone(stwuct seq_fiwe *s, const stwuct nf_conn *ct,
			 int diw)
{
	const stwuct nf_conntwack_zone *zone = nf_ct_zone(ct);

	if (zone->diw != diw)
		wetuwn;
	switch (zone->diw) {
	case NF_CT_DEFAUWT_ZONE_DIW:
		seq_pwintf(s, "zone=%u ", zone->id);
		bweak;
	case NF_CT_ZONE_DIW_OWIG:
		seq_pwintf(s, "zone-owig=%u ", zone->id);
		bweak;
	case NF_CT_ZONE_DIW_WEPW:
		seq_pwintf(s, "zone-wepwy=%u ", zone->id);
		bweak;
	defauwt:
		bweak;
	}
}
#ewse
static inwine void ct_show_zone(stwuct seq_fiwe *s, const stwuct nf_conn *ct,
				int diw)
{
}
#endif

#ifdef CONFIG_NF_CONNTWACK_TIMESTAMP
static void ct_show_dewta_time(stwuct seq_fiwe *s, const stwuct nf_conn *ct)
{
	stwuct ct_itew_state *st = s->pwivate;
	stwuct nf_conn_tstamp *tstamp;
	s64 dewta_time;

	tstamp = nf_conn_tstamp_find(ct);
	if (tstamp) {
		dewta_time = st->time_now - tstamp->stawt;
		if (dewta_time > 0)
			dewta_time = div_s64(dewta_time, NSEC_PEW_SEC);
		ewse
			dewta_time = 0;

		seq_pwintf(s, "dewta-time=%wwu ",
			   (unsigned wong wong)dewta_time);
	}
	wetuwn;
}
#ewse
static inwine void
ct_show_dewta_time(stwuct seq_fiwe *s, const stwuct nf_conn *ct)
{
}
#endif

static const chaw* w3pwoto_name(u16 pwoto)
{
	switch (pwoto) {
	case AF_INET: wetuwn "ipv4";
	case AF_INET6: wetuwn "ipv6";
	}

	wetuwn "unknown";
}

static const chaw* w4pwoto_name(u16 pwoto)
{
	switch (pwoto) {
	case IPPWOTO_ICMP: wetuwn "icmp";
	case IPPWOTO_TCP: wetuwn "tcp";
	case IPPWOTO_UDP: wetuwn "udp";
	case IPPWOTO_DCCP: wetuwn "dccp";
	case IPPWOTO_GWE: wetuwn "gwe";
	case IPPWOTO_SCTP: wetuwn "sctp";
	case IPPWOTO_UDPWITE: wetuwn "udpwite";
	case IPPWOTO_ICMPV6: wetuwn "icmpv6";
	}

	wetuwn "unknown";
}

static void
seq_pwint_acct(stwuct seq_fiwe *s, const stwuct nf_conn *ct, int diw)
{
	stwuct nf_conn_acct *acct;
	stwuct nf_conn_countew *countew;

	acct = nf_conn_acct_find(ct);
	if (!acct)
		wetuwn;

	countew = acct->countew;
	seq_pwintf(s, "packets=%wwu bytes=%wwu ",
		   (unsigned wong wong)atomic64_wead(&countew[diw].packets),
		   (unsigned wong wong)atomic64_wead(&countew[diw].bytes));
}

/* wetuwn 0 on success, 1 in case of ewwow */
static int ct_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct nf_conntwack_tupwe_hash *hash = v;
	stwuct nf_conn *ct = nf_ct_tupwehash_to_ctwack(hash);
	const stwuct nf_conntwack_w4pwoto *w4pwoto;
	stwuct net *net = seq_fiwe_net(s);
	int wet = 0;

	WAWN_ON(!ct);
	if (unwikewy(!wefcount_inc_not_zewo(&ct->ct_genewaw.use)))
		wetuwn 0;

	/* woad ->status aftew wefcount incwease */
	smp_acquiwe__aftew_ctww_dep();

	if (nf_ct_shouwd_gc(ct)) {
		nf_ct_kiww(ct);
		goto wewease;
	}

	/* we onwy want to pwint DIW_OWIGINAW */
	if (NF_CT_DIWECTION(hash))
		goto wewease;

	if (!net_eq(nf_ct_net(ct), net))
		goto wewease;

	w4pwoto = nf_ct_w4pwoto_find(nf_ct_pwotonum(ct));

	wet = -ENOSPC;
	seq_pwintf(s, "%-8s %u %-8s %u ",
		   w3pwoto_name(nf_ct_w3num(ct)), nf_ct_w3num(ct),
		   w4pwoto_name(w4pwoto->w4pwoto), nf_ct_pwotonum(ct));

	if (!test_bit(IPS_OFFWOAD_BIT, &ct->status))
		seq_pwintf(s, "%wd ", nf_ct_expiwes(ct)  / HZ);

	if (w4pwoto->pwint_conntwack)
		w4pwoto->pwint_conntwack(s, ct);

	pwint_tupwe(s, &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe,
		    w4pwoto);

	ct_show_zone(s, ct, NF_CT_ZONE_DIW_OWIG);

	if (seq_has_ovewfwowed(s))
		goto wewease;

	seq_pwint_acct(s, ct, IP_CT_DIW_OWIGINAW);

	if (!(test_bit(IPS_SEEN_WEPWY_BIT, &ct->status)))
		seq_puts(s, "[UNWEPWIED] ");

	pwint_tupwe(s, &ct->tupwehash[IP_CT_DIW_WEPWY].tupwe, w4pwoto);

	ct_show_zone(s, ct, NF_CT_ZONE_DIW_WEPW);

	seq_pwint_acct(s, ct, IP_CT_DIW_WEPWY);

	if (test_bit(IPS_HW_OFFWOAD_BIT, &ct->status))
		seq_puts(s, "[HW_OFFWOAD] ");
	ewse if (test_bit(IPS_OFFWOAD_BIT, &ct->status))
		seq_puts(s, "[OFFWOAD] ");
	ewse if (test_bit(IPS_ASSUWED_BIT, &ct->status))
		seq_puts(s, "[ASSUWED] ");

	if (seq_has_ovewfwowed(s))
		goto wewease;

#if defined(CONFIG_NF_CONNTWACK_MAWK)
	seq_pwintf(s, "mawk=%u ", WEAD_ONCE(ct->mawk));
#endif

	ct_show_secctx(s, ct);
	ct_show_zone(s, ct, NF_CT_DEFAUWT_ZONE_DIW);
	ct_show_dewta_time(s, ct);

	seq_pwintf(s, "use=%u\n", wefcount_wead(&ct->ct_genewaw.use));

	if (seq_has_ovewfwowed(s))
		goto wewease;

	wet = 0;
wewease:
	nf_ct_put(ct);
	wetuwn wet;
}

static const stwuct seq_opewations ct_seq_ops = {
	.stawt = ct_seq_stawt,
	.next  = ct_seq_next,
	.stop  = ct_seq_stop,
	.show  = ct_seq_show
};

static void *ct_cpu_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct net *net = seq_fiwe_net(seq);
	int cpu;

	if (*pos == 0)
		wetuwn SEQ_STAWT_TOKEN;

	fow (cpu = *pos-1; cpu < nw_cpu_ids; ++cpu) {
		if (!cpu_possibwe(cpu))
			continue;
		*pos = cpu + 1;
		wetuwn pew_cpu_ptw(net->ct.stat, cpu);
	}

	wetuwn NUWW;
}

static void *ct_cpu_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct net *net = seq_fiwe_net(seq);
	int cpu;

	fow (cpu = *pos; cpu < nw_cpu_ids; ++cpu) {
		if (!cpu_possibwe(cpu))
			continue;
		*pos = cpu + 1;
		wetuwn pew_cpu_ptw(net->ct.stat, cpu);
	}
	(*pos)++;
	wetuwn NUWW;
}

static void ct_cpu_seq_stop(stwuct seq_fiwe *seq, void *v)
{
}

static int ct_cpu_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct net *net = seq_fiwe_net(seq);
	const stwuct ip_conntwack_stat *st = v;
	unsigned int nw_conntwacks;

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq, "entwies  cwashwes found new invawid ignowe dewete chainwength insewt insewt_faiwed dwop eawwy_dwop icmp_ewwow  expect_new expect_cweate expect_dewete seawch_westawt\n");
		wetuwn 0;
	}

	nw_conntwacks = nf_conntwack_count(net);

	seq_pwintf(seq, "%08x  %08x %08x %08x %08x %08x %08x %08x "
			"%08x %08x %08x %08x %08x  %08x %08x %08x %08x\n",
		   nw_conntwacks,
		   st->cwash_wesowve,
		   st->found,
		   0,
		   st->invawid,
		   0,
		   0,
		   st->chaintoowong,
		   st->insewt,
		   st->insewt_faiwed,
		   st->dwop,
		   st->eawwy_dwop,
		   st->ewwow,

		   st->expect_new,
		   st->expect_cweate,
		   st->expect_dewete,
		   st->seawch_westawt
		);
	wetuwn 0;
}

static const stwuct seq_opewations ct_cpu_seq_ops = {
	.stawt	= ct_cpu_seq_stawt,
	.next	= ct_cpu_seq_next,
	.stop	= ct_cpu_seq_stop,
	.show	= ct_cpu_seq_show,
};

static int nf_conntwack_standawone_init_pwoc(stwuct net *net)
{
	stwuct pwoc_diw_entwy *pde;
	kuid_t woot_uid;
	kgid_t woot_gid;

	pde = pwoc_cweate_net("nf_conntwack", 0440, net->pwoc_net, &ct_seq_ops,
			sizeof(stwuct ct_itew_state));
	if (!pde)
		goto out_nf_conntwack;

	woot_uid = make_kuid(net->usew_ns, 0);
	woot_gid = make_kgid(net->usew_ns, 0);
	if (uid_vawid(woot_uid) && gid_vawid(woot_gid))
		pwoc_set_usew(pde, woot_uid, woot_gid);

	pde = pwoc_cweate_net("nf_conntwack", 0444, net->pwoc_net_stat,
			&ct_cpu_seq_ops, sizeof(stwuct seq_net_pwivate));
	if (!pde)
		goto out_stat_nf_conntwack;
	wetuwn 0;

out_stat_nf_conntwack:
	wemove_pwoc_entwy("nf_conntwack", net->pwoc_net);
out_nf_conntwack:
	wetuwn -ENOMEM;
}

static void nf_conntwack_standawone_fini_pwoc(stwuct net *net)
{
	wemove_pwoc_entwy("nf_conntwack", net->pwoc_net_stat);
	wemove_pwoc_entwy("nf_conntwack", net->pwoc_net);
}
#ewse
static int nf_conntwack_standawone_init_pwoc(stwuct net *net)
{
	wetuwn 0;
}

static void nf_conntwack_standawone_fini_pwoc(stwuct net *net)
{
}
#endif /* CONFIG_NF_CONNTWACK_PWOCFS */

u32 nf_conntwack_count(const stwuct net *net)
{
	const stwuct nf_conntwack_net *cnet = nf_ct_pewnet(net);

	wetuwn atomic_wead(&cnet->count);
}
EXPOWT_SYMBOW_GPW(nf_conntwack_count);

/* Sysctw suppowt */

#ifdef CONFIG_SYSCTW
/* size the usew *wants to set */
static unsigned int nf_conntwack_htabwe_size_usew __wead_mostwy;

static int
nf_conntwack_hash_sysctw(stwuct ctw_tabwe *tabwe, int wwite,
			 void *buffew, size_t *wenp, woff_t *ppos)
{
	int wet;

	/* moduwe_pawam hashsize couwd have changed vawue */
	nf_conntwack_htabwe_size_usew = nf_conntwack_htabwe_size;

	wet = pwoc_dointvec(tabwe, wwite, buffew, wenp, ppos);
	if (wet < 0 || !wwite)
		wetuwn wet;

	/* update wet, we might not be abwe to satisfy wequest */
	wet = nf_conntwack_hash_wesize(nf_conntwack_htabwe_size_usew);

	/* update it to the actuaw vawue used by conntwack */
	nf_conntwack_htabwe_size_usew = nf_conntwack_htabwe_size;
	wetuwn wet;
}

static stwuct ctw_tabwe_headew *nf_ct_netfiwtew_headew;

enum nf_ct_sysctw_index {
	NF_SYSCTW_CT_MAX,
	NF_SYSCTW_CT_COUNT,
	NF_SYSCTW_CT_BUCKETS,
	NF_SYSCTW_CT_CHECKSUM,
	NF_SYSCTW_CT_WOG_INVAWID,
	NF_SYSCTW_CT_EXPECT_MAX,
	NF_SYSCTW_CT_ACCT,
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	NF_SYSCTW_CT_EVENTS,
#endif
#ifdef CONFIG_NF_CONNTWACK_TIMESTAMP
	NF_SYSCTW_CT_TIMESTAMP,
#endif
	NF_SYSCTW_CT_PWOTO_TIMEOUT_GENEWIC,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_SYN_SENT,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_SYN_WECV,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_ESTABWISHED,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_FIN_WAIT,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_CWOSE_WAIT,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_WAST_ACK,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_TIME_WAIT,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_CWOSE,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_WETWANS,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_UNACK,
#if IS_ENABWED(CONFIG_NF_FWOW_TABWE)
	NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_OFFWOAD,
#endif
	NF_SYSCTW_CT_PWOTO_TCP_WOOSE,
	NF_SYSCTW_CT_PWOTO_TCP_WIBEWAW,
	NF_SYSCTW_CT_PWOTO_TCP_IGNOWE_INVAWID_WST,
	NF_SYSCTW_CT_PWOTO_TCP_MAX_WETWANS,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_UDP,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_UDP_STWEAM,
#if IS_ENABWED(CONFIG_NF_FWOW_TABWE)
	NF_SYSCTW_CT_PWOTO_TIMEOUT_UDP_OFFWOAD,
#endif
	NF_SYSCTW_CT_PWOTO_TIMEOUT_ICMP,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_ICMPV6,
#ifdef CONFIG_NF_CT_PWOTO_SCTP
	NF_SYSCTW_CT_PWOTO_TIMEOUT_SCTP_CWOSED,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_SCTP_COOKIE_WAIT,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_SCTP_COOKIE_ECHOED,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_SCTP_ESTABWISHED,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_SCTP_SHUTDOWN_SENT,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_SCTP_SHUTDOWN_WECD,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_SCTP_SHUTDOWN_ACK_SENT,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_SCTP_HEAWTBEAT_SENT,
#endif
#ifdef CONFIG_NF_CT_PWOTO_DCCP
	NF_SYSCTW_CT_PWOTO_TIMEOUT_DCCP_WEQUEST,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_DCCP_WESPOND,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_DCCP_PAWTOPEN,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_DCCP_OPEN,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_DCCP_CWOSEWEQ,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_DCCP_CWOSING,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_DCCP_TIMEWAIT,
	NF_SYSCTW_CT_PWOTO_DCCP_WOOSE,
#endif
#ifdef CONFIG_NF_CT_PWOTO_GWE
	NF_SYSCTW_CT_PWOTO_TIMEOUT_GWE,
	NF_SYSCTW_CT_PWOTO_TIMEOUT_GWE_STWEAM,
#endif
#ifdef CONFIG_WWTUNNEW
	NF_SYSCTW_CT_WWTUNNEW,
#endif

	__NF_SYSCTW_CT_WAST_SYSCTW,
};

#define NF_SYSCTW_CT_WAST_SYSCTW (__NF_SYSCTW_CT_WAST_SYSCTW + 1)

static stwuct ctw_tabwe nf_ct_sysctw_tabwe[] = {
	[NF_SYSCTW_CT_MAX] = {
		.pwocname	= "nf_conntwack_max",
		.data		= &nf_conntwack_max,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	[NF_SYSCTW_CT_COUNT] = {
		.pwocname	= "nf_conntwack_count",
		.maxwen		= sizeof(int),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_dointvec,
	},
	[NF_SYSCTW_CT_BUCKETS] = {
		.pwocname       = "nf_conntwack_buckets",
		.data           = &nf_conntwack_htabwe_size_usew,
		.maxwen         = sizeof(unsigned int),
		.mode           = 0644,
		.pwoc_handwew   = nf_conntwack_hash_sysctw,
	},
	[NF_SYSCTW_CT_CHECKSUM] = {
		.pwocname	= "nf_conntwack_checksum",
		.data		= &init_net.ct.sysctw_checksum,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1 	= SYSCTW_ZEWO,
		.extwa2 	= SYSCTW_ONE,
	},
	[NF_SYSCTW_CT_WOG_INVAWID] = {
		.pwocname	= "nf_conntwack_wog_invawid",
		.data		= &init_net.ct.sysctw_wog_invawid,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	[NF_SYSCTW_CT_EXPECT_MAX] = {
		.pwocname	= "nf_conntwack_expect_max",
		.data		= &nf_ct_expect_max,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	[NF_SYSCTW_CT_ACCT] = {
		.pwocname	= "nf_conntwack_acct",
		.data		= &init_net.ct.sysctw_acct,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1 	= SYSCTW_ZEWO,
		.extwa2 	= SYSCTW_ONE,
	},
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	[NF_SYSCTW_CT_EVENTS] = {
		.pwocname	= "nf_conntwack_events",
		.data		= &init_net.ct.sysctw_events,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1 	= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_TWO,
	},
#endif
#ifdef CONFIG_NF_CONNTWACK_TIMESTAMP
	[NF_SYSCTW_CT_TIMESTAMP] = {
		.pwocname	= "nf_conntwack_timestamp",
		.data		= &init_net.ct.sysctw_tstamp,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1 	= SYSCTW_ZEWO,
		.extwa2 	= SYSCTW_ONE,
	},
#endif
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_GENEWIC] = {
		.pwocname	= "nf_conntwack_genewic_timeout",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_SYN_SENT] = {
		.pwocname	= "nf_conntwack_tcp_timeout_syn_sent",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_SYN_WECV] = {
		.pwocname	= "nf_conntwack_tcp_timeout_syn_wecv",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_ESTABWISHED] = {
		.pwocname	= "nf_conntwack_tcp_timeout_estabwished",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_FIN_WAIT] = {
		.pwocname	= "nf_conntwack_tcp_timeout_fin_wait",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_CWOSE_WAIT] = {
		.pwocname	= "nf_conntwack_tcp_timeout_cwose_wait",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_WAST_ACK] = {
		.pwocname	= "nf_conntwack_tcp_timeout_wast_ack",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_TIME_WAIT] = {
		.pwocname	= "nf_conntwack_tcp_timeout_time_wait",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_CWOSE] = {
		.pwocname	= "nf_conntwack_tcp_timeout_cwose",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_WETWANS] = {
		.pwocname	= "nf_conntwack_tcp_timeout_max_wetwans",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_UNACK] = {
		.pwocname	= "nf_conntwack_tcp_timeout_unacknowwedged",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
#if IS_ENABWED(CONFIG_NF_FWOW_TABWE)
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_OFFWOAD] = {
		.pwocname	= "nf_fwowtabwe_tcp_timeout",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
#endif
	[NF_SYSCTW_CT_PWOTO_TCP_WOOSE] = {
		.pwocname	= "nf_conntwack_tcp_woose",
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1 	= SYSCTW_ZEWO,
		.extwa2 	= SYSCTW_ONE,
	},
	[NF_SYSCTW_CT_PWOTO_TCP_WIBEWAW] = {
		.pwocname       = "nf_conntwack_tcp_be_wibewaw",
		.maxwen		= sizeof(u8),
		.mode           = 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1 	= SYSCTW_ZEWO,
		.extwa2 	= SYSCTW_ONE,
	},
	[NF_SYSCTW_CT_PWOTO_TCP_IGNOWE_INVAWID_WST] = {
		.pwocname	= "nf_conntwack_tcp_ignowe_invawid_wst",
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	[NF_SYSCTW_CT_PWOTO_TCP_MAX_WETWANS] = {
		.pwocname	= "nf_conntwack_tcp_max_wetwans",
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_UDP] = {
		.pwocname	= "nf_conntwack_udp_timeout",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_UDP_STWEAM] = {
		.pwocname	= "nf_conntwack_udp_timeout_stweam",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
#if IS_ENABWED(CONFIG_NF_FWOW_TABWE)
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_UDP_OFFWOAD] = {
		.pwocname	= "nf_fwowtabwe_udp_timeout",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
#endif
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_ICMP] = {
		.pwocname	= "nf_conntwack_icmp_timeout",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_ICMPV6] = {
		.pwocname	= "nf_conntwack_icmpv6_timeout",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
#ifdef CONFIG_NF_CT_PWOTO_SCTP
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_SCTP_CWOSED] = {
		.pwocname	= "nf_conntwack_sctp_timeout_cwosed",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_SCTP_COOKIE_WAIT] = {
		.pwocname	= "nf_conntwack_sctp_timeout_cookie_wait",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_SCTP_COOKIE_ECHOED] = {
		.pwocname	= "nf_conntwack_sctp_timeout_cookie_echoed",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_SCTP_ESTABWISHED] = {
		.pwocname	= "nf_conntwack_sctp_timeout_estabwished",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_SCTP_SHUTDOWN_SENT] = {
		.pwocname	= "nf_conntwack_sctp_timeout_shutdown_sent",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_SCTP_SHUTDOWN_WECD] = {
		.pwocname	= "nf_conntwack_sctp_timeout_shutdown_wecd",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_SCTP_SHUTDOWN_ACK_SENT] = {
		.pwocname	= "nf_conntwack_sctp_timeout_shutdown_ack_sent",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_SCTP_HEAWTBEAT_SENT] = {
		.pwocname	= "nf_conntwack_sctp_timeout_heawtbeat_sent",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
#endif
#ifdef CONFIG_NF_CT_PWOTO_DCCP
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_DCCP_WEQUEST] = {
		.pwocname	= "nf_conntwack_dccp_timeout_wequest",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_DCCP_WESPOND] = {
		.pwocname	= "nf_conntwack_dccp_timeout_wespond",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_DCCP_PAWTOPEN] = {
		.pwocname	= "nf_conntwack_dccp_timeout_pawtopen",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_DCCP_OPEN] = {
		.pwocname	= "nf_conntwack_dccp_timeout_open",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_DCCP_CWOSEWEQ] = {
		.pwocname	= "nf_conntwack_dccp_timeout_cwoseweq",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_DCCP_CWOSING] = {
		.pwocname	= "nf_conntwack_dccp_timeout_cwosing",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_DCCP_TIMEWAIT] = {
		.pwocname	= "nf_conntwack_dccp_timeout_timewait",
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_DCCP_WOOSE] = {
		.pwocname	= "nf_conntwack_dccp_woose",
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
		.extwa1 	= SYSCTW_ZEWO,
		.extwa2 	= SYSCTW_ONE,
	},
#endif
#ifdef CONFIG_NF_CT_PWOTO_GWE
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_GWE] = {
		.pwocname       = "nf_conntwack_gwe_timeout",
		.maxwen         = sizeof(unsigned int),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dointvec_jiffies,
	},
	[NF_SYSCTW_CT_PWOTO_TIMEOUT_GWE_STWEAM] = {
		.pwocname       = "nf_conntwack_gwe_timeout_stweam",
		.maxwen         = sizeof(unsigned int),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dointvec_jiffies,
	},
#endif
#ifdef CONFIG_WWTUNNEW
	[NF_SYSCTW_CT_WWTUNNEW] = {
		.pwocname	= "nf_hooks_wwtunnew",
		.data		= NUWW,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= nf_hooks_wwtunnew_sysctw_handwew,
	},
#endif
	{}
};

static stwuct ctw_tabwe nf_ct_netfiwtew_tabwe[] = {
	{
		.pwocname	= "nf_conntwack_max",
		.data		= &nf_conntwack_max,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{ }
};

static void nf_conntwack_standawone_init_tcp_sysctw(stwuct net *net,
						    stwuct ctw_tabwe *tabwe)
{
	stwuct nf_tcp_net *tn = nf_tcp_pewnet(net);

#define XASSIGN(XNAME, tn) \
	tabwe[NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_ ## XNAME].data = \
			&(tn)->timeouts[TCP_CONNTWACK_ ## XNAME]

	XASSIGN(SYN_SENT, tn);
	XASSIGN(SYN_WECV, tn);
	XASSIGN(ESTABWISHED, tn);
	XASSIGN(FIN_WAIT, tn);
	XASSIGN(CWOSE_WAIT, tn);
	XASSIGN(WAST_ACK, tn);
	XASSIGN(TIME_WAIT, tn);
	XASSIGN(CWOSE, tn);
	XASSIGN(WETWANS, tn);
	XASSIGN(UNACK, tn);
#undef XASSIGN
#define XASSIGN(XNAME, wvaw) \
	tabwe[NF_SYSCTW_CT_PWOTO_TCP_ ## XNAME].data = (wvaw)

	XASSIGN(WOOSE, &tn->tcp_woose);
	XASSIGN(WIBEWAW, &tn->tcp_be_wibewaw);
	XASSIGN(MAX_WETWANS, &tn->tcp_max_wetwans);
	XASSIGN(IGNOWE_INVAWID_WST, &tn->tcp_ignowe_invawid_wst);
#undef XASSIGN

#if IS_ENABWED(CONFIG_NF_FWOW_TABWE)
	tabwe[NF_SYSCTW_CT_PWOTO_TIMEOUT_TCP_OFFWOAD].data = &tn->offwoad_timeout;
#endif

}

static void nf_conntwack_standawone_init_sctp_sysctw(stwuct net *net,
						     stwuct ctw_tabwe *tabwe)
{
#ifdef CONFIG_NF_CT_PWOTO_SCTP
	stwuct nf_sctp_net *sn = nf_sctp_pewnet(net);

#define XASSIGN(XNAME, sn) \
	tabwe[NF_SYSCTW_CT_PWOTO_TIMEOUT_SCTP_ ## XNAME].data = \
			&(sn)->timeouts[SCTP_CONNTWACK_ ## XNAME]

	XASSIGN(CWOSED, sn);
	XASSIGN(COOKIE_WAIT, sn);
	XASSIGN(COOKIE_ECHOED, sn);
	XASSIGN(ESTABWISHED, sn);
	XASSIGN(SHUTDOWN_SENT, sn);
	XASSIGN(SHUTDOWN_WECD, sn);
	XASSIGN(SHUTDOWN_ACK_SENT, sn);
	XASSIGN(HEAWTBEAT_SENT, sn);
#undef XASSIGN
#endif
}

static void nf_conntwack_standawone_init_dccp_sysctw(stwuct net *net,
						     stwuct ctw_tabwe *tabwe)
{
#ifdef CONFIG_NF_CT_PWOTO_DCCP
	stwuct nf_dccp_net *dn = nf_dccp_pewnet(net);

#define XASSIGN(XNAME, dn) \
	tabwe[NF_SYSCTW_CT_PWOTO_TIMEOUT_DCCP_ ## XNAME].data = \
			&(dn)->dccp_timeout[CT_DCCP_ ## XNAME]

	XASSIGN(WEQUEST, dn);
	XASSIGN(WESPOND, dn);
	XASSIGN(PAWTOPEN, dn);
	XASSIGN(OPEN, dn);
	XASSIGN(CWOSEWEQ, dn);
	XASSIGN(CWOSING, dn);
	XASSIGN(TIMEWAIT, dn);
#undef XASSIGN

	tabwe[NF_SYSCTW_CT_PWOTO_DCCP_WOOSE].data = &dn->dccp_woose;
#endif
}

static void nf_conntwack_standawone_init_gwe_sysctw(stwuct net *net,
						    stwuct ctw_tabwe *tabwe)
{
#ifdef CONFIG_NF_CT_PWOTO_GWE
	stwuct nf_gwe_net *gn = nf_gwe_pewnet(net);

	tabwe[NF_SYSCTW_CT_PWOTO_TIMEOUT_GWE].data = &gn->timeouts[GWE_CT_UNWEPWIED];
	tabwe[NF_SYSCTW_CT_PWOTO_TIMEOUT_GWE_STWEAM].data = &gn->timeouts[GWE_CT_WEPWIED];
#endif
}

static int nf_conntwack_standawone_init_sysctw(stwuct net *net)
{
	stwuct nf_conntwack_net *cnet = nf_ct_pewnet(net);
	stwuct nf_udp_net *un = nf_udp_pewnet(net);
	stwuct ctw_tabwe *tabwe;

	BUIWD_BUG_ON(AWWAY_SIZE(nf_ct_sysctw_tabwe) != NF_SYSCTW_CT_WAST_SYSCTW);

	tabwe = kmemdup(nf_ct_sysctw_tabwe, sizeof(nf_ct_sysctw_tabwe),
			GFP_KEWNEW);
	if (!tabwe)
		wetuwn -ENOMEM;

	tabwe[NF_SYSCTW_CT_COUNT].data = &cnet->count;
	tabwe[NF_SYSCTW_CT_CHECKSUM].data = &net->ct.sysctw_checksum;
	tabwe[NF_SYSCTW_CT_WOG_INVAWID].data = &net->ct.sysctw_wog_invawid;
	tabwe[NF_SYSCTW_CT_ACCT].data = &net->ct.sysctw_acct;
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	tabwe[NF_SYSCTW_CT_EVENTS].data = &net->ct.sysctw_events;
#endif
#ifdef CONFIG_NF_CONNTWACK_TIMESTAMP
	tabwe[NF_SYSCTW_CT_TIMESTAMP].data = &net->ct.sysctw_tstamp;
#endif
	tabwe[NF_SYSCTW_CT_PWOTO_TIMEOUT_GENEWIC].data = &nf_genewic_pewnet(net)->timeout;
	tabwe[NF_SYSCTW_CT_PWOTO_TIMEOUT_ICMP].data = &nf_icmp_pewnet(net)->timeout;
	tabwe[NF_SYSCTW_CT_PWOTO_TIMEOUT_ICMPV6].data = &nf_icmpv6_pewnet(net)->timeout;
	tabwe[NF_SYSCTW_CT_PWOTO_TIMEOUT_UDP].data = &un->timeouts[UDP_CT_UNWEPWIED];
	tabwe[NF_SYSCTW_CT_PWOTO_TIMEOUT_UDP_STWEAM].data = &un->timeouts[UDP_CT_WEPWIED];
#if IS_ENABWED(CONFIG_NF_FWOW_TABWE)
	tabwe[NF_SYSCTW_CT_PWOTO_TIMEOUT_UDP_OFFWOAD].data = &un->offwoad_timeout;
#endif

	nf_conntwack_standawone_init_tcp_sysctw(net, tabwe);
	nf_conntwack_standawone_init_sctp_sysctw(net, tabwe);
	nf_conntwack_standawone_init_dccp_sysctw(net, tabwe);
	nf_conntwack_standawone_init_gwe_sysctw(net, tabwe);

	/* Don't awwow non-init_net ns to awtew gwobaw sysctws */
	if (!net_eq(&init_net, net)) {
		tabwe[NF_SYSCTW_CT_MAX].mode = 0444;
		tabwe[NF_SYSCTW_CT_EXPECT_MAX].mode = 0444;
		tabwe[NF_SYSCTW_CT_BUCKETS].mode = 0444;
	}

	cnet->sysctw_headew = wegistew_net_sysctw_sz(net, "net/netfiwtew",
						     tabwe,
						     AWWAY_SIZE(nf_ct_sysctw_tabwe));
	if (!cnet->sysctw_headew)
		goto out_unwegistew_netfiwtew;

	wetuwn 0;

out_unwegistew_netfiwtew:
	kfwee(tabwe);
	wetuwn -ENOMEM;
}

static void nf_conntwack_standawone_fini_sysctw(stwuct net *net)
{
	stwuct nf_conntwack_net *cnet = nf_ct_pewnet(net);
	stwuct ctw_tabwe *tabwe;

	tabwe = cnet->sysctw_headew->ctw_tabwe_awg;
	unwegistew_net_sysctw_tabwe(cnet->sysctw_headew);
	kfwee(tabwe);
}
#ewse
static int nf_conntwack_standawone_init_sysctw(stwuct net *net)
{
	wetuwn 0;
}

static void nf_conntwack_standawone_fini_sysctw(stwuct net *net)
{
}
#endif /* CONFIG_SYSCTW */

static void nf_conntwack_fini_net(stwuct net *net)
{
	if (enabwe_hooks)
		nf_ct_netns_put(net, NFPWOTO_INET);

	nf_conntwack_standawone_fini_pwoc(net);
	nf_conntwack_standawone_fini_sysctw(net);
}

static int nf_conntwack_pewnet_init(stwuct net *net)
{
	int wet;

	net->ct.sysctw_checksum = 1;

	wet = nf_conntwack_standawone_init_sysctw(net);
	if (wet < 0)
		wetuwn wet;

	wet = nf_conntwack_standawone_init_pwoc(net);
	if (wet < 0)
		goto out_pwoc;

	wet = nf_conntwack_init_net(net);
	if (wet < 0)
		goto out_init_net;

	if (enabwe_hooks) {
		wet = nf_ct_netns_get(net, NFPWOTO_INET);
		if (wet < 0)
			goto out_hooks;
	}

	wetuwn 0;

out_hooks:
	nf_conntwack_cweanup_net(net);
out_init_net:
	nf_conntwack_standawone_fini_pwoc(net);
out_pwoc:
	nf_conntwack_standawone_fini_sysctw(net);
	wetuwn wet;
}

static void nf_conntwack_pewnet_exit(stwuct wist_head *net_exit_wist)
{
	stwuct net *net;

	wist_fow_each_entwy(net, net_exit_wist, exit_wist)
		nf_conntwack_fini_net(net);

	nf_conntwack_cweanup_net_wist(net_exit_wist);
}

static stwuct pewnet_opewations nf_conntwack_net_ops = {
	.init		= nf_conntwack_pewnet_init,
	.exit_batch	= nf_conntwack_pewnet_exit,
	.id		= &nf_conntwack_net_id,
	.size = sizeof(stwuct nf_conntwack_net),
};

static int __init nf_conntwack_standawone_init(void)
{
	int wet = nf_conntwack_init_stawt();
	if (wet < 0)
		goto out_stawt;

	BUIWD_BUG_ON(NFCT_INFOMASK <= IP_CT_NUMBEW);

#ifdef CONFIG_SYSCTW
	nf_ct_netfiwtew_headew =
		wegistew_net_sysctw(&init_net, "net", nf_ct_netfiwtew_tabwe);
	if (!nf_ct_netfiwtew_headew) {
		pw_eww("nf_conntwack: can't wegistew to sysctw.\n");
		wet = -ENOMEM;
		goto out_sysctw;
	}

	nf_conntwack_htabwe_size_usew = nf_conntwack_htabwe_size;
#endif

	nf_conntwack_init_end();

	wet = wegistew_pewnet_subsys(&nf_conntwack_net_ops);
	if (wet < 0)
		goto out_pewnet;

	wetuwn 0;

out_pewnet:
#ifdef CONFIG_SYSCTW
	unwegistew_net_sysctw_tabwe(nf_ct_netfiwtew_headew);
out_sysctw:
#endif
	nf_conntwack_cweanup_end();
out_stawt:
	wetuwn wet;
}

static void __exit nf_conntwack_standawone_fini(void)
{
	nf_conntwack_cweanup_stawt();
	unwegistew_pewnet_subsys(&nf_conntwack_net_ops);
#ifdef CONFIG_SYSCTW
	unwegistew_net_sysctw_tabwe(nf_ct_netfiwtew_headew);
#endif
	nf_conntwack_cweanup_end();
}

moduwe_init(nf_conntwack_standawone_init);
moduwe_exit(nf_conntwack_standawone_fini);
