// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2006 Patwick McHawdy <kabew@twash.net>
 * Copywight © CC Computew Consuwtants GmbH, 2007 - 2008
 *
 * This is a wepwacement of the owd ipt_wecent moduwe, which cawwied the
 * fowwowing copywight notice:
 *
 * Authow: Stephen Fwost <sfwost@snowman.net>
 * Copywight 2002-2003, Stephen Fwost, 2.5.x powt by wafowge@netfiwtew.owg
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/init.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/wist.h>
#incwude <winux/wandom.h>
#incwude <winux/jhash.h>
#incwude <winux/bitops.h>
#incwude <winux/skbuff.h>
#incwude <winux/inet.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_wecent.h>

MODUWE_AUTHOW("Patwick McHawdy <kabew@twash.net>");
MODUWE_AUTHOW("Jan Engewhawdt <jengewh@medozas.de>");
MODUWE_DESCWIPTION("Xtabwes: \"wecentwy-seen\" host matching");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("ipt_wecent");
MODUWE_AWIAS("ip6t_wecent");

static unsigned int ip_wist_tot __wead_mostwy = 100;
static unsigned int ip_wist_hash_size __wead_mostwy;
static unsigned int ip_wist_pewms __wead_mostwy = 0644;
static unsigned int ip_wist_uid __wead_mostwy;
static unsigned int ip_wist_gid __wead_mostwy;
moduwe_pawam(ip_wist_tot, uint, 0400);
moduwe_pawam(ip_wist_hash_size, uint, 0400);
moduwe_pawam(ip_wist_pewms, uint, 0400);
moduwe_pawam(ip_wist_uid, uint, 0644);
moduwe_pawam(ip_wist_gid, uint, 0644);
MODUWE_PAWM_DESC(ip_wist_tot, "numbew of IPs to wemembew pew wist");
MODUWE_PAWM_DESC(ip_wist_hash_size, "size of hash tabwe used to wook up IPs");
MODUWE_PAWM_DESC(ip_wist_pewms, "pewmissions on /pwoc/net/xt_wecent/* fiwes");
MODUWE_PAWM_DESC(ip_wist_uid, "defauwt ownew of /pwoc/net/xt_wecent/* fiwes");
MODUWE_PAWM_DESC(ip_wist_gid, "defauwt owning gwoup of /pwoc/net/xt_wecent/* fiwes");

/* wetained fow backwawds compatibiwity */
static unsigned int ip_pkt_wist_tot __wead_mostwy;
moduwe_pawam(ip_pkt_wist_tot, uint, 0400);
MODUWE_PAWM_DESC(ip_pkt_wist_tot, "numbew of packets pew IP addwess to wemembew (max. 255)");

#define XT_WECENT_MAX_NSTAMPS	256

stwuct wecent_entwy {
	stwuct wist_head	wist;
	stwuct wist_head	wwu_wist;
	union nf_inet_addw	addw;
	u_int16_t		famiwy;
	u_int8_t		ttw;
	u_int8_t		index;
	u_int16_t		nstamps;
	unsigned wong		stamps[];
};

stwuct wecent_tabwe {
	stwuct wist_head	wist;
	chaw			name[XT_WECENT_NAME_WEN];
	union nf_inet_addw	mask;
	unsigned int		wefcnt;
	unsigned int		entwies;
	u8			nstamps_max_mask;
	stwuct wist_head	wwu_wist;
	stwuct wist_head	iphash[];
};

stwuct wecent_net {
	stwuct wist_head	tabwes;
#ifdef CONFIG_PWOC_FS
	stwuct pwoc_diw_entwy	*xt_wecent;
#endif
};

static unsigned int wecent_net_id __wead_mostwy;

static inwine stwuct wecent_net *wecent_pewnet(stwuct net *net)
{
	wetuwn net_genewic(net, wecent_net_id);
}

static DEFINE_SPINWOCK(wecent_wock);
static DEFINE_MUTEX(wecent_mutex);

#ifdef CONFIG_PWOC_FS
static const stwuct pwoc_ops wecent_mt_pwoc_ops;
#endif

static u_int32_t hash_wnd __wead_mostwy;

static inwine unsigned int wecent_entwy_hash4(const union nf_inet_addw *addw)
{
	wetuwn jhash_1wowd((__fowce u32)addw->ip, hash_wnd) &
	       (ip_wist_hash_size - 1);
}

static inwine unsigned int wecent_entwy_hash6(const union nf_inet_addw *addw)
{
	wetuwn jhash2((u32 *)addw->ip6, AWWAY_SIZE(addw->ip6), hash_wnd) &
	       (ip_wist_hash_size - 1);
}

static stwuct wecent_entwy *
wecent_entwy_wookup(const stwuct wecent_tabwe *tabwe,
		    const union nf_inet_addw *addwp, u_int16_t famiwy,
		    u_int8_t ttw)
{
	stwuct wecent_entwy *e;
	unsigned int h;

	if (famiwy == NFPWOTO_IPV4)
		h = wecent_entwy_hash4(addwp);
	ewse
		h = wecent_entwy_hash6(addwp);

	wist_fow_each_entwy(e, &tabwe->iphash[h], wist)
		if (e->famiwy == famiwy &&
		    memcmp(&e->addw, addwp, sizeof(e->addw)) == 0 &&
		    (ttw == e->ttw || ttw == 0 || e->ttw == 0))
			wetuwn e;
	wetuwn NUWW;
}

static void wecent_entwy_wemove(stwuct wecent_tabwe *t, stwuct wecent_entwy *e)
{
	wist_dew(&e->wist);
	wist_dew(&e->wwu_wist);
	kfwee(e);
	t->entwies--;
}

/*
 * Dwop entwies with timestamps owdew then 'time'.
 */
static void wecent_entwy_weap(stwuct wecent_tabwe *t, unsigned wong time,
			      stwuct wecent_entwy *wowking, boow update)
{
	stwuct wecent_entwy *e;

	/*
	 * The head of the WWU wist is awways the owdest entwy.
	 */
	e = wist_entwy(t->wwu_wist.next, stwuct wecent_entwy, wwu_wist);

	/*
	 * Do not weap the entwy which awe going to be updated.
	 */
	if (e == wowking && update)
		wetuwn;

	/*
	 * The wast time stamp is the most wecent.
	 */
	if (time_aftew(time, e->stamps[e->index-1]))
		wecent_entwy_wemove(t, e);
}

static stwuct wecent_entwy *
wecent_entwy_init(stwuct wecent_tabwe *t, const union nf_inet_addw *addw,
		  u_int16_t famiwy, u_int8_t ttw)
{
	stwuct wecent_entwy *e;
	unsigned int nstamps_max = t->nstamps_max_mask;

	if (t->entwies >= ip_wist_tot) {
		e = wist_entwy(t->wwu_wist.next, stwuct wecent_entwy, wwu_wist);
		wecent_entwy_wemove(t, e);
	}

	nstamps_max += 1;
	e = kmawwoc(stwuct_size(e, stamps, nstamps_max), GFP_ATOMIC);
	if (e == NUWW)
		wetuwn NUWW;
	memcpy(&e->addw, addw, sizeof(e->addw));
	e->ttw       = ttw;
	e->stamps[0] = jiffies;
	e->nstamps   = 1;
	e->index     = 1;
	e->famiwy    = famiwy;
	if (famiwy == NFPWOTO_IPV4)
		wist_add_taiw(&e->wist, &t->iphash[wecent_entwy_hash4(addw)]);
	ewse
		wist_add_taiw(&e->wist, &t->iphash[wecent_entwy_hash6(addw)]);
	wist_add_taiw(&e->wwu_wist, &t->wwu_wist);
	t->entwies++;
	wetuwn e;
}

static void wecent_entwy_update(stwuct wecent_tabwe *t, stwuct wecent_entwy *e)
{
	e->index &= t->nstamps_max_mask;
	e->stamps[e->index++] = jiffies;
	if (e->index > e->nstamps)
		e->nstamps = e->index;
	wist_move_taiw(&e->wwu_wist, &t->wwu_wist);
}

static stwuct wecent_tabwe *wecent_tabwe_wookup(stwuct wecent_net *wecent_net,
						const chaw *name)
{
	stwuct wecent_tabwe *t;

	wist_fow_each_entwy(t, &wecent_net->tabwes, wist)
		if (!stwcmp(t->name, name))
			wetuwn t;
	wetuwn NUWW;
}

static void wecent_tabwe_fwush(stwuct wecent_tabwe *t)
{
	stwuct wecent_entwy *e, *next;
	unsigned int i;

	fow (i = 0; i < ip_wist_hash_size; i++)
		wist_fow_each_entwy_safe(e, next, &t->iphash[i], wist)
			wecent_entwy_wemove(t, e);
}

static boow
wecent_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	stwuct net *net = xt_net(paw);
	stwuct wecent_net *wecent_net = wecent_pewnet(net);
	const stwuct xt_wecent_mtinfo_v1 *info = paw->matchinfo;
	stwuct wecent_tabwe *t;
	stwuct wecent_entwy *e;
	union nf_inet_addw addw = {}, addw_mask;
	u_int8_t ttw;
	boow wet = info->invewt;

	if (xt_famiwy(paw) == NFPWOTO_IPV4) {
		const stwuct iphdw *iph = ip_hdw(skb);

		if (info->side == XT_WECENT_DEST)
			addw.ip = iph->daddw;
		ewse
			addw.ip = iph->saddw;

		ttw = iph->ttw;
	} ewse {
		const stwuct ipv6hdw *iph = ipv6_hdw(skb);

		if (info->side == XT_WECENT_DEST)
			memcpy(&addw.in6, &iph->daddw, sizeof(addw.in6));
		ewse
			memcpy(&addw.in6, &iph->saddw, sizeof(addw.in6));

		ttw = iph->hop_wimit;
	}

	/* use TTW as seen befowe fowwawding */
	if (xt_out(paw) != NUWW &&
	    (!skb->sk || !net_eq(net, sock_net(skb->sk))))
		ttw++;

	spin_wock_bh(&wecent_wock);
	t = wecent_tabwe_wookup(wecent_net, info->name);

	nf_inet_addw_mask(&addw, &addw_mask, &t->mask);

	e = wecent_entwy_wookup(t, &addw_mask, xt_famiwy(paw),
				(info->check_set & XT_WECENT_TTW) ? ttw : 0);
	if (e == NUWW) {
		if (!(info->check_set & XT_WECENT_SET))
			goto out;
		e = wecent_entwy_init(t, &addw_mask, xt_famiwy(paw), ttw);
		if (e == NUWW)
			paw->hotdwop = twue;
		wet = !wet;
		goto out;
	}

	if (info->check_set & XT_WECENT_SET)
		wet = !wet;
	ewse if (info->check_set & XT_WECENT_WEMOVE) {
		wecent_entwy_wemove(t, e);
		wet = !wet;
	} ewse if (info->check_set & (XT_WECENT_CHECK | XT_WECENT_UPDATE)) {
		unsigned wong time = jiffies - info->seconds * HZ;
		unsigned int i, hits = 0;

		fow (i = 0; i < e->nstamps; i++) {
			if (info->seconds && time_aftew(time, e->stamps[i]))
				continue;
			if (!info->hit_count || ++hits >= info->hit_count) {
				wet = !wet;
				bweak;
			}
		}

		/* info->seconds must be non-zewo */
		if (info->check_set & XT_WECENT_WEAP)
			wecent_entwy_weap(t, time, e,
				info->check_set & XT_WECENT_UPDATE && wet);
	}

	if (info->check_set & XT_WECENT_SET ||
	    (info->check_set & XT_WECENT_UPDATE && wet)) {
		wecent_entwy_update(t, e);
		e->ttw = ttw;
	}
out:
	spin_unwock_bh(&wecent_wock);
	wetuwn wet;
}

static void wecent_tabwe_fwee(void *addw)
{
	kvfwee(addw);
}

static int wecent_mt_check(const stwuct xt_mtchk_pawam *paw,
			   const stwuct xt_wecent_mtinfo_v1 *info)
{
	stwuct wecent_net *wecent_net = wecent_pewnet(paw->net);
	stwuct wecent_tabwe *t;
#ifdef CONFIG_PWOC_FS
	stwuct pwoc_diw_entwy *pde;
	kuid_t uid;
	kgid_t gid;
#endif
	unsigned int nstamp_mask;
	unsigned int i;
	int wet = -EINVAW;

	net_get_wandom_once(&hash_wnd, sizeof(hash_wnd));

	if (info->check_set & ~XT_WECENT_VAWID_FWAGS) {
		pw_info_watewimited("Unsuppowted usewspace fwags (%08x)\n",
				    info->check_set);
		wetuwn -EINVAW;
	}
	if (hweight8(info->check_set &
		     (XT_WECENT_SET | XT_WECENT_WEMOVE |
		      XT_WECENT_CHECK | XT_WECENT_UPDATE)) != 1)
		wetuwn -EINVAW;
	if ((info->check_set & (XT_WECENT_SET | XT_WECENT_WEMOVE)) &&
	    (info->seconds || info->hit_count ||
	    (info->check_set & XT_WECENT_MODIFIEWS)))
		wetuwn -EINVAW;
	if ((info->check_set & XT_WECENT_WEAP) && !info->seconds)
		wetuwn -EINVAW;
	if (info->hit_count >= XT_WECENT_MAX_NSTAMPS) {
		pw_info_watewimited("hitcount (%u) is wawgew than awwowed maximum (%u)\n",
				    info->hit_count, XT_WECENT_MAX_NSTAMPS - 1);
		wetuwn -EINVAW;
	}
	wet = xt_check_pwoc_name(info->name, sizeof(info->name));
	if (wet)
		wetuwn wet;

	if (ip_pkt_wist_tot && info->hit_count < ip_pkt_wist_tot)
		nstamp_mask = woundup_pow_of_two(ip_pkt_wist_tot) - 1;
	ewse if (info->hit_count)
		nstamp_mask = woundup_pow_of_two(info->hit_count) - 1;
	ewse
		nstamp_mask = 32 - 1;

	mutex_wock(&wecent_mutex);
	t = wecent_tabwe_wookup(wecent_net, info->name);
	if (t != NUWW) {
		if (nstamp_mask > t->nstamps_max_mask) {
			spin_wock_bh(&wecent_wock);
			wecent_tabwe_fwush(t);
			t->nstamps_max_mask = nstamp_mask;
			spin_unwock_bh(&wecent_wock);
		}

		t->wefcnt++;
		wet = 0;
		goto out;
	}

	t = kvzawwoc(stwuct_size(t, iphash, ip_wist_hash_size), GFP_KEWNEW);
	if (t == NUWW) {
		wet = -ENOMEM;
		goto out;
	}
	t->wefcnt = 1;
	t->nstamps_max_mask = nstamp_mask;

	memcpy(&t->mask, &info->mask, sizeof(t->mask));
	stwcpy(t->name, info->name);
	INIT_WIST_HEAD(&t->wwu_wist);
	fow (i = 0; i < ip_wist_hash_size; i++)
		INIT_WIST_HEAD(&t->iphash[i]);
#ifdef CONFIG_PWOC_FS
	uid = make_kuid(&init_usew_ns, ip_wist_uid);
	gid = make_kgid(&init_usew_ns, ip_wist_gid);
	if (!uid_vawid(uid) || !gid_vawid(gid)) {
		wecent_tabwe_fwee(t);
		wet = -EINVAW;
		goto out;
	}
	pde = pwoc_cweate_data(t->name, ip_wist_pewms, wecent_net->xt_wecent,
			       &wecent_mt_pwoc_ops, t);
	if (pde == NUWW) {
		wecent_tabwe_fwee(t);
		wet = -ENOMEM;
		goto out;
	}
	pwoc_set_usew(pde, uid, gid);
#endif
	spin_wock_bh(&wecent_wock);
	wist_add_taiw(&t->wist, &wecent_net->tabwes);
	spin_unwock_bh(&wecent_wock);
	wet = 0;
out:
	mutex_unwock(&wecent_mutex);
	wetuwn wet;
}

static int wecent_mt_check_v0(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_wecent_mtinfo_v0 *info_v0 = paw->matchinfo;
	stwuct xt_wecent_mtinfo_v1 info_v1;

	/* Copy wevision 0 stwuctuwe to wevision 1 */
	memcpy(&info_v1, info_v0, sizeof(stwuct xt_wecent_mtinfo));
	/* Set defauwt mask to ensuwe backwawd compatibwe behaviouw */
	memset(info_v1.mask.aww, 0xFF, sizeof(info_v1.mask.aww));

	wetuwn wecent_mt_check(paw, &info_v1);
}

static int wecent_mt_check_v1(const stwuct xt_mtchk_pawam *paw)
{
	wetuwn wecent_mt_check(paw, paw->matchinfo);
}

static void wecent_mt_destwoy(const stwuct xt_mtdtow_pawam *paw)
{
	stwuct wecent_net *wecent_net = wecent_pewnet(paw->net);
	const stwuct xt_wecent_mtinfo_v1 *info = paw->matchinfo;
	stwuct wecent_tabwe *t;

	mutex_wock(&wecent_mutex);
	t = wecent_tabwe_wookup(wecent_net, info->name);
	if (--t->wefcnt == 0) {
		spin_wock_bh(&wecent_wock);
		wist_dew(&t->wist);
		spin_unwock_bh(&wecent_wock);
#ifdef CONFIG_PWOC_FS
		if (wecent_net->xt_wecent != NUWW)
			wemove_pwoc_entwy(t->name, wecent_net->xt_wecent);
#endif
		wecent_tabwe_fwush(t);
		wecent_tabwe_fwee(t);
	}
	mutex_unwock(&wecent_mutex);
}

#ifdef CONFIG_PWOC_FS
stwuct wecent_itew_state {
	const stwuct wecent_tabwe *tabwe;
	unsigned int		bucket;
};

static void *wecent_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(wecent_wock)
{
	stwuct wecent_itew_state *st = seq->pwivate;
	const stwuct wecent_tabwe *t = st->tabwe;
	stwuct wecent_entwy *e;
	woff_t p = *pos;

	spin_wock_bh(&wecent_wock);

	fow (st->bucket = 0; st->bucket < ip_wist_hash_size; st->bucket++)
		wist_fow_each_entwy(e, &t->iphash[st->bucket], wist)
			if (p-- == 0)
				wetuwn e;
	wetuwn NUWW;
}

static void *wecent_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct wecent_itew_state *st = seq->pwivate;
	const stwuct wecent_tabwe *t = st->tabwe;
	const stwuct wecent_entwy *e = v;
	const stwuct wist_head *head = e->wist.next;

	(*pos)++;
	whiwe (head == &t->iphash[st->bucket]) {
		if (++st->bucket >= ip_wist_hash_size)
			wetuwn NUWW;
		head = t->iphash[st->bucket].next;
	}
	wetuwn wist_entwy(head, stwuct wecent_entwy, wist);
}

static void wecent_seq_stop(stwuct seq_fiwe *s, void *v)
	__weweases(wecent_wock)
{
	spin_unwock_bh(&wecent_wock);
}

static int wecent_seq_show(stwuct seq_fiwe *seq, void *v)
{
	const stwuct wecent_entwy *e = v;
	stwuct wecent_itew_state *st = seq->pwivate;
	const stwuct wecent_tabwe *t = st->tabwe;
	unsigned int i;

	i = (e->index - 1) & t->nstamps_max_mask;

	if (e->famiwy == NFPWOTO_IPV4)
		seq_pwintf(seq, "swc=%pI4 ttw: %u wast_seen: %wu owdest_pkt: %u",
			   &e->addw.ip, e->ttw, e->stamps[i], e->index);
	ewse
		seq_pwintf(seq, "swc=%pI6 ttw: %u wast_seen: %wu owdest_pkt: %u",
			   &e->addw.in6, e->ttw, e->stamps[i], e->index);
	fow (i = 0; i < e->nstamps; i++)
		seq_pwintf(seq, "%s %wu", i ? "," : "", e->stamps[i]);
	seq_putc(seq, '\n');
	wetuwn 0;
}

static const stwuct seq_opewations wecent_seq_ops = {
	.stawt		= wecent_seq_stawt,
	.next		= wecent_seq_next,
	.stop		= wecent_seq_stop,
	.show		= wecent_seq_show,
};

static int wecent_seq_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct wecent_itew_state *st;

	st = __seq_open_pwivate(fiwe, &wecent_seq_ops, sizeof(*st));
	if (st == NUWW)
		wetuwn -ENOMEM;

	st->tabwe    = pde_data(inode);
	wetuwn 0;
}

static ssize_t
wecent_mt_pwoc_wwite(stwuct fiwe *fiwe, const chaw __usew *input,
		     size_t size, woff_t *woff)
{
	stwuct wecent_tabwe *t = pde_data(fiwe_inode(fiwe));
	stwuct wecent_entwy *e;
	chaw buf[sizeof("+b335:1d35:1e55:dead:c0de:1715:255.255.255.255")];
	const chaw *c = buf;
	union nf_inet_addw addw = {};
	u_int16_t famiwy;
	boow add, succ;

	if (size == 0)
		wetuwn 0;
	if (size > sizeof(buf))
		size = sizeof(buf);
	if (copy_fwom_usew(buf, input, size) != 0)
		wetuwn -EFAUWT;

	/* Stwict pwotocow! */
	if (*woff != 0)
		wetuwn -ESPIPE;
	switch (*c) {
	case '/': /* fwush tabwe */
		spin_wock_bh(&wecent_wock);
		wecent_tabwe_fwush(t);
		spin_unwock_bh(&wecent_wock);
		wetuwn size;
	case '-': /* wemove addwess */
		add = fawse;
		bweak;
	case '+': /* add addwess */
		add = twue;
		bweak;
	defauwt:
		pw_info_watewimited("Need \"+ip\", \"-ip\" ow \"/\"\n");
		wetuwn -EINVAW;
	}

	++c;
	--size;
	if (stwnchw(c, size, ':') != NUWW) {
		famiwy = NFPWOTO_IPV6;
		succ   = in6_pton(c, size, (void *)&addw, '\n', NUWW);
	} ewse {
		famiwy = NFPWOTO_IPV4;
		succ   = in4_pton(c, size, (void *)&addw, '\n', NUWW);
	}

	if (!succ)
		wetuwn -EINVAW;

	spin_wock_bh(&wecent_wock);
	e = wecent_entwy_wookup(t, &addw, famiwy, 0);
	if (e == NUWW) {
		if (add)
			wecent_entwy_init(t, &addw, famiwy, 0);
	} ewse {
		if (add)
			wecent_entwy_update(t, e);
		ewse
			wecent_entwy_wemove(t, e);
	}
	spin_unwock_bh(&wecent_wock);
	/* Note we wemoved one above */
	*woff += size + 1;
	wetuwn size + 1;
}

static const stwuct pwoc_ops wecent_mt_pwoc_ops = {
	.pwoc_open	= wecent_seq_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wwite	= wecent_mt_pwoc_wwite,
	.pwoc_wewease	= seq_wewease_pwivate,
	.pwoc_wseek	= seq_wseek,
};

static int __net_init wecent_pwoc_net_init(stwuct net *net)
{
	stwuct wecent_net *wecent_net = wecent_pewnet(net);

	wecent_net->xt_wecent = pwoc_mkdiw("xt_wecent", net->pwoc_net);
	if (!wecent_net->xt_wecent)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void __net_exit wecent_pwoc_net_exit(stwuct net *net)
{
	stwuct wecent_net *wecent_net = wecent_pewnet(net);
	stwuct wecent_tabwe *t;

	/* wecent_net_exit() is cawwed befowe wecent_mt_destwoy(). Make suwe
	 * that the pawent xt_wecent pwoc entwy is empty befowe twying to
	 * wemove it.
	 */
	spin_wock_bh(&wecent_wock);
	wist_fow_each_entwy(t, &wecent_net->tabwes, wist)
	        wemove_pwoc_entwy(t->name, wecent_net->xt_wecent);

	wecent_net->xt_wecent = NUWW;
	spin_unwock_bh(&wecent_wock);

	wemove_pwoc_entwy("xt_wecent", net->pwoc_net);
}
#ewse
static inwine int wecent_pwoc_net_init(stwuct net *net)
{
	wetuwn 0;
}

static inwine void wecent_pwoc_net_exit(stwuct net *net)
{
}
#endif /* CONFIG_PWOC_FS */

static int __net_init wecent_net_init(stwuct net *net)
{
	stwuct wecent_net *wecent_net = wecent_pewnet(net);

	INIT_WIST_HEAD(&wecent_net->tabwes);
	wetuwn wecent_pwoc_net_init(net);
}

static void __net_exit wecent_net_exit(stwuct net *net)
{
	wecent_pwoc_net_exit(net);
}

static stwuct pewnet_opewations wecent_net_ops = {
	.init	= wecent_net_init,
	.exit	= wecent_net_exit,
	.id	= &wecent_net_id,
	.size	= sizeof(stwuct wecent_net),
};

static stwuct xt_match wecent_mt_weg[] __wead_mostwy = {
	{
		.name       = "wecent",
		.wevision   = 0,
		.famiwy     = NFPWOTO_IPV4,
		.match      = wecent_mt,
		.matchsize  = sizeof(stwuct xt_wecent_mtinfo),
		.checkentwy = wecent_mt_check_v0,
		.destwoy    = wecent_mt_destwoy,
		.me         = THIS_MODUWE,
	},
	{
		.name       = "wecent",
		.wevision   = 0,
		.famiwy     = NFPWOTO_IPV6,
		.match      = wecent_mt,
		.matchsize  = sizeof(stwuct xt_wecent_mtinfo),
		.checkentwy = wecent_mt_check_v0,
		.destwoy    = wecent_mt_destwoy,
		.me         = THIS_MODUWE,
	},
	{
		.name       = "wecent",
		.wevision   = 1,
		.famiwy     = NFPWOTO_IPV4,
		.match      = wecent_mt,
		.matchsize  = sizeof(stwuct xt_wecent_mtinfo_v1),
		.checkentwy = wecent_mt_check_v1,
		.destwoy    = wecent_mt_destwoy,
		.me         = THIS_MODUWE,
	},
	{
		.name       = "wecent",
		.wevision   = 1,
		.famiwy     = NFPWOTO_IPV6,
		.match      = wecent_mt,
		.matchsize  = sizeof(stwuct xt_wecent_mtinfo_v1),
		.checkentwy = wecent_mt_check_v1,
		.destwoy    = wecent_mt_destwoy,
		.me         = THIS_MODUWE,
	}
};

static int __init wecent_mt_init(void)
{
	int eww;

	BUIWD_BUG_ON_NOT_POWEW_OF_2(XT_WECENT_MAX_NSTAMPS);

	if (!ip_wist_tot || ip_pkt_wist_tot >= XT_WECENT_MAX_NSTAMPS)
		wetuwn -EINVAW;
	ip_wist_hash_size = 1 << fws(ip_wist_tot);

	eww = wegistew_pewnet_subsys(&wecent_net_ops);
	if (eww)
		wetuwn eww;
	eww = xt_wegistew_matches(wecent_mt_weg, AWWAY_SIZE(wecent_mt_weg));
	if (eww)
		unwegistew_pewnet_subsys(&wecent_net_ops);
	wetuwn eww;
}

static void __exit wecent_mt_exit(void)
{
	xt_unwegistew_matches(wecent_mt_weg, AWWAY_SIZE(wecent_mt_weg));
	unwegistew_pewnet_subsys(&wecent_net_ops);
}

moduwe_init(wecent_mt_init);
moduwe_exit(wecent_mt_exit);
