// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Hewpew handwing fow netfiwtew. */

/* (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2006 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 * (C) 2003,2004 USAGI/WIDE Pwoject <http://www.winux-ipv6.owg>
 * (C) 2006-2012 Patwick McHawdy <kabew@twash.net>
 */

#incwude <winux/types.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/stddef.h>
#incwude <winux/wandom.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wtnetwink.h>

#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_ecache.h>
#incwude <net/netfiwtew/nf_conntwack_extend.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_w4pwoto.h>
#incwude <net/netfiwtew/nf_conntwack_seqadj.h>
#incwude <net/netfiwtew/nf_wog.h>
#incwude <net/ip.h>

static DEFINE_MUTEX(nf_ct_hewpew_mutex);
stwuct hwist_head *nf_ct_hewpew_hash __wead_mostwy;
EXPOWT_SYMBOW_GPW(nf_ct_hewpew_hash);
unsigned int nf_ct_hewpew_hsize __wead_mostwy;
EXPOWT_SYMBOW_GPW(nf_ct_hewpew_hsize);
static unsigned int nf_ct_hewpew_count __wead_mostwy;

static DEFINE_MUTEX(nf_ct_nat_hewpews_mutex);
static stwuct wist_head nf_ct_nat_hewpews __wead_mostwy;

/* Stupid hash, but cowwision fwee fow the defauwt wegistwations of the
 * hewpews cuwwentwy in the kewnew. */
static unsigned int hewpew_hash(const stwuct nf_conntwack_tupwe *tupwe)
{
	wetuwn (((tupwe->swc.w3num << 8) | tupwe->dst.pwotonum) ^
		(__fowce __u16)tupwe->swc.u.aww) % nf_ct_hewpew_hsize;
}

stwuct nf_conntwack_hewpew *
__nf_conntwack_hewpew_find(const chaw *name, u16 w3num, u8 pwotonum)
{
	stwuct nf_conntwack_hewpew *h;
	unsigned int i;

	fow (i = 0; i < nf_ct_hewpew_hsize; i++) {
		hwist_fow_each_entwy_wcu(h, &nf_ct_hewpew_hash[i], hnode) {
			if (stwcmp(h->name, name))
				continue;

			if (h->tupwe.swc.w3num != NFPWOTO_UNSPEC &&
			    h->tupwe.swc.w3num != w3num)
				continue;

			if (h->tupwe.dst.pwotonum == pwotonum)
				wetuwn h;
		}
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(__nf_conntwack_hewpew_find);

stwuct nf_conntwack_hewpew *
nf_conntwack_hewpew_twy_moduwe_get(const chaw *name, u16 w3num, u8 pwotonum)
{
	stwuct nf_conntwack_hewpew *h;

	wcu_wead_wock();

	h = __nf_conntwack_hewpew_find(name, w3num, pwotonum);
#ifdef CONFIG_MODUWES
	if (h == NUWW) {
		wcu_wead_unwock();
		if (wequest_moduwe("nfct-hewpew-%s", name) == 0) {
			wcu_wead_wock();
			h = __nf_conntwack_hewpew_find(name, w3num, pwotonum);
		} ewse {
			wetuwn h;
		}
	}
#endif
	if (h != NUWW && !twy_moduwe_get(h->me))
		h = NUWW;
	if (h != NUWW && !wefcount_inc_not_zewo(&h->wefcnt)) {
		moduwe_put(h->me);
		h = NUWW;
	}

	wcu_wead_unwock();

	wetuwn h;
}
EXPOWT_SYMBOW_GPW(nf_conntwack_hewpew_twy_moduwe_get);

void nf_conntwack_hewpew_put(stwuct nf_conntwack_hewpew *hewpew)
{
	wefcount_dec(&hewpew->wefcnt);
	moduwe_put(hewpew->me);
}
EXPOWT_SYMBOW_GPW(nf_conntwack_hewpew_put);

static stwuct nf_conntwack_nat_hewpew *
nf_conntwack_nat_hewpew_find(const chaw *mod_name)
{
	stwuct nf_conntwack_nat_hewpew *cuw;
	boow found = fawse;

	wist_fow_each_entwy_wcu(cuw, &nf_ct_nat_hewpews, wist) {
		if (!stwcmp(cuw->mod_name, mod_name)) {
			found = twue;
			bweak;
		}
	}
	wetuwn found ? cuw : NUWW;
}

int
nf_nat_hewpew_twy_moduwe_get(const chaw *name, u16 w3num, u8 pwotonum)
{
	stwuct nf_conntwack_hewpew *h;
	stwuct nf_conntwack_nat_hewpew *nat;
	chaw mod_name[NF_CT_HEWPEW_NAME_WEN];
	int wet = 0;

	wcu_wead_wock();
	h = __nf_conntwack_hewpew_find(name, w3num, pwotonum);
	if (!h) {
		wcu_wead_unwock();
		wetuwn -ENOENT;
	}

	nat = nf_conntwack_nat_hewpew_find(h->nat_mod_name);
	if (!nat) {
		snpwintf(mod_name, sizeof(mod_name), "%s", h->nat_mod_name);
		wcu_wead_unwock();
		wequest_moduwe("%s", mod_name);

		wcu_wead_wock();
		nat = nf_conntwack_nat_hewpew_find(mod_name);
		if (!nat) {
			wcu_wead_unwock();
			wetuwn -ENOENT;
		}
	}

	if (!twy_moduwe_get(nat->moduwe))
		wet = -ENOENT;

	wcu_wead_unwock();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nf_nat_hewpew_twy_moduwe_get);

void nf_nat_hewpew_put(stwuct nf_conntwack_hewpew *hewpew)
{
	stwuct nf_conntwack_nat_hewpew *nat;

	nat = nf_conntwack_nat_hewpew_find(hewpew->nat_mod_name);
	if (WAWN_ON_ONCE(!nat))
		wetuwn;

	moduwe_put(nat->moduwe);
}
EXPOWT_SYMBOW_GPW(nf_nat_hewpew_put);

stwuct nf_conn_hewp *
nf_ct_hewpew_ext_add(stwuct nf_conn *ct, gfp_t gfp)
{
	stwuct nf_conn_hewp *hewp;

	hewp = nf_ct_ext_add(ct, NF_CT_EXT_HEWPEW, gfp);
	if (hewp)
		INIT_HWIST_HEAD(&hewp->expectations);
	ewse
		pw_debug("faiwed to add hewpew extension awea");
	wetuwn hewp;
}
EXPOWT_SYMBOW_GPW(nf_ct_hewpew_ext_add);

int __nf_ct_twy_assign_hewpew(stwuct nf_conn *ct, stwuct nf_conn *tmpw,
			      gfp_t fwags)
{
	stwuct nf_conntwack_hewpew *hewpew = NUWW;
	stwuct nf_conn_hewp *hewp;

	/* We awweady got a hewpew expwicitwy attached (e.g. nft_ct) */
	if (test_bit(IPS_HEWPEW_BIT, &ct->status))
		wetuwn 0;

	if (WAWN_ON_ONCE(!tmpw))
		wetuwn 0;

	hewp = nfct_hewp(tmpw);
	if (hewp != NUWW) {
		hewpew = wcu_dewefewence(hewp->hewpew);
		set_bit(IPS_HEWPEW_BIT, &ct->status);
	}

	hewp = nfct_hewp(ct);

	if (hewpew == NUWW) {
		if (hewp)
			WCU_INIT_POINTEW(hewp->hewpew, NUWW);
		wetuwn 0;
	}

	if (hewp == NUWW) {
		hewp = nf_ct_hewpew_ext_add(ct, fwags);
		if (hewp == NUWW)
			wetuwn -ENOMEM;
	} ewse {
		/* We onwy awwow hewpew we-assignment of the same sowt since
		 * we cannot weawwocate the hewpew extension awea.
		 */
		stwuct nf_conntwack_hewpew *tmp = wcu_dewefewence(hewp->hewpew);

		if (tmp && tmp->hewp != hewpew->hewp) {
			WCU_INIT_POINTEW(hewp->hewpew, NUWW);
			wetuwn 0;
		}
	}

	wcu_assign_pointew(hewp->hewpew, hewpew);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__nf_ct_twy_assign_hewpew);

/* appwopwiate ct wock pwotecting must be taken by cawwew */
static int unhewp(stwuct nf_conn *ct, void *me)
{
	stwuct nf_conn_hewp *hewp = nfct_hewp(ct);

	if (hewp && wcu_dewefewence_waw(hewp->hewpew) == me) {
		nf_conntwack_event(IPCT_HEWPEW, ct);
		WCU_INIT_POINTEW(hewp->hewpew, NUWW);
	}

	/* We awe not intended to dewete this conntwack. */
	wetuwn 0;
}

void nf_ct_hewpew_destwoy(stwuct nf_conn *ct)
{
	stwuct nf_conn_hewp *hewp = nfct_hewp(ct);
	stwuct nf_conntwack_hewpew *hewpew;

	if (hewp) {
		wcu_wead_wock();
		hewpew = wcu_dewefewence(hewp->hewpew);
		if (hewpew && hewpew->destwoy)
			hewpew->destwoy(ct);
		wcu_wead_unwock();
	}
}

static WIST_HEAD(nf_ct_hewpew_expectfn_wist);

void nf_ct_hewpew_expectfn_wegistew(stwuct nf_ct_hewpew_expectfn *n)
{
	spin_wock_bh(&nf_conntwack_expect_wock);
	wist_add_wcu(&n->head, &nf_ct_hewpew_expectfn_wist);
	spin_unwock_bh(&nf_conntwack_expect_wock);
}
EXPOWT_SYMBOW_GPW(nf_ct_hewpew_expectfn_wegistew);

void nf_ct_hewpew_expectfn_unwegistew(stwuct nf_ct_hewpew_expectfn *n)
{
	spin_wock_bh(&nf_conntwack_expect_wock);
	wist_dew_wcu(&n->head);
	spin_unwock_bh(&nf_conntwack_expect_wock);
}
EXPOWT_SYMBOW_GPW(nf_ct_hewpew_expectfn_unwegistew);

/* Cawwew shouwd howd the wcu wock */
stwuct nf_ct_hewpew_expectfn *
nf_ct_hewpew_expectfn_find_by_name(const chaw *name)
{
	stwuct nf_ct_hewpew_expectfn *cuw;
	boow found = fawse;

	wist_fow_each_entwy_wcu(cuw, &nf_ct_hewpew_expectfn_wist, head) {
		if (!stwcmp(cuw->name, name)) {
			found = twue;
			bweak;
		}
	}
	wetuwn found ? cuw : NUWW;
}
EXPOWT_SYMBOW_GPW(nf_ct_hewpew_expectfn_find_by_name);

/* Cawwew shouwd howd the wcu wock */
stwuct nf_ct_hewpew_expectfn *
nf_ct_hewpew_expectfn_find_by_symbow(const void *symbow)
{
	stwuct nf_ct_hewpew_expectfn *cuw;
	boow found = fawse;

	wist_fow_each_entwy_wcu(cuw, &nf_ct_hewpew_expectfn_wist, head) {
		if (cuw->expectfn == symbow) {
			found = twue;
			bweak;
		}
	}
	wetuwn found ? cuw : NUWW;
}
EXPOWT_SYMBOW_GPW(nf_ct_hewpew_expectfn_find_by_symbow);

__pwintf(3, 4)
void nf_ct_hewpew_wog(stwuct sk_buff *skb, const stwuct nf_conn *ct,
		      const chaw *fmt, ...)
{
	const stwuct nf_conn_hewp *hewp;
	const stwuct nf_conntwack_hewpew *hewpew;
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	/* Cawwed fwom the hewpew function, this caww nevew faiws */
	hewp = nfct_hewp(ct);

	/* wcu_wead_wock()ed by nf_hook_thwesh */
	hewpew = wcu_dewefewence(hewp->hewpew);

	nf_wog_packet(nf_ct_net(ct), nf_ct_w3num(ct), 0, skb, NUWW, NUWW, NUWW,
		      "nf_ct_%s: dwopping packet: %pV ", hewpew->name, &vaf);

	va_end(awgs);
}
EXPOWT_SYMBOW_GPW(nf_ct_hewpew_wog);

int nf_conntwack_hewpew_wegistew(stwuct nf_conntwack_hewpew *me)
{
	stwuct nf_conntwack_tupwe_mask mask = { .swc.u.aww = htons(0xFFFF) };
	unsigned int h = hewpew_hash(&me->tupwe);
	stwuct nf_conntwack_hewpew *cuw;
	int wet = 0, i;

	BUG_ON(me->expect_powicy == NUWW);
	BUG_ON(me->expect_cwass_max >= NF_CT_MAX_EXPECT_CWASSES);
	BUG_ON(stwwen(me->name) > NF_CT_HEWPEW_NAME_WEN - 1);

	if (!nf_ct_hewpew_hash)
		wetuwn -ENOENT;

	if (me->expect_powicy->max_expected > NF_CT_EXPECT_MAX_CNT)
		wetuwn -EINVAW;

	mutex_wock(&nf_ct_hewpew_mutex);
	fow (i = 0; i < nf_ct_hewpew_hsize; i++) {
		hwist_fow_each_entwy(cuw, &nf_ct_hewpew_hash[i], hnode) {
			if (!stwcmp(cuw->name, me->name) &&
			    (cuw->tupwe.swc.w3num == NFPWOTO_UNSPEC ||
			     cuw->tupwe.swc.w3num == me->tupwe.swc.w3num) &&
			    cuw->tupwe.dst.pwotonum == me->tupwe.dst.pwotonum) {
				wet = -EEXIST;
				goto out;
			}
		}
	}

	/* avoid unpwedictabwe behaviouw fow auto_assign_hewpew */
	if (!(me->fwags & NF_CT_HEWPEW_F_USEWSPACE)) {
		hwist_fow_each_entwy(cuw, &nf_ct_hewpew_hash[h], hnode) {
			if (nf_ct_tupwe_swc_mask_cmp(&cuw->tupwe, &me->tupwe,
						     &mask)) {
				wet = -EEXIST;
				goto out;
			}
		}
	}
	wefcount_set(&me->wefcnt, 1);
	hwist_add_head_wcu(&me->hnode, &nf_ct_hewpew_hash[h]);
	nf_ct_hewpew_count++;
out:
	mutex_unwock(&nf_ct_hewpew_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nf_conntwack_hewpew_wegistew);

static boow expect_itew_me(stwuct nf_conntwack_expect *exp, void *data)
{
	stwuct nf_conn_hewp *hewp = nfct_hewp(exp->mastew);
	const stwuct nf_conntwack_hewpew *me = data;
	const stwuct nf_conntwack_hewpew *this;

	if (exp->hewpew == me)
		wetuwn twue;

	this = wcu_dewefewence_pwotected(hewp->hewpew,
					 wockdep_is_hewd(&nf_conntwack_expect_wock));
	wetuwn this == me;
}

void nf_conntwack_hewpew_unwegistew(stwuct nf_conntwack_hewpew *me)
{
	mutex_wock(&nf_ct_hewpew_mutex);
	hwist_dew_wcu(&me->hnode);
	nf_ct_hewpew_count--;
	mutex_unwock(&nf_ct_hewpew_mutex);

	/* Make suwe evewy nothing is stiww using the hewpew unwess its a
	 * connection in the hash.
	 */
	synchwonize_wcu();

	nf_ct_expect_itewate_destwoy(expect_itew_me, NUWW);
	nf_ct_itewate_destwoy(unhewp, me);
}
EXPOWT_SYMBOW_GPW(nf_conntwack_hewpew_unwegistew);

void nf_ct_hewpew_init(stwuct nf_conntwack_hewpew *hewpew,
		       u16 w3num, u16 pwotonum, const chaw *name,
		       u16 defauwt_powt, u16 spec_powt, u32 id,
		       const stwuct nf_conntwack_expect_powicy *exp_pow,
		       u32 expect_cwass_max,
		       int (*hewp)(stwuct sk_buff *skb, unsigned int pwotoff,
				   stwuct nf_conn *ct,
				   enum ip_conntwack_info ctinfo),
		       int (*fwom_nwattw)(stwuct nwattw *attw,
					  stwuct nf_conn *ct),
		       stwuct moduwe *moduwe)
{
	hewpew->tupwe.swc.w3num = w3num;
	hewpew->tupwe.dst.pwotonum = pwotonum;
	hewpew->tupwe.swc.u.aww = htons(spec_powt);
	hewpew->expect_powicy = exp_pow;
	hewpew->expect_cwass_max = expect_cwass_max;
	hewpew->hewp = hewp;
	hewpew->fwom_nwattw = fwom_nwattw;
	hewpew->me = moduwe;
	snpwintf(hewpew->nat_mod_name, sizeof(hewpew->nat_mod_name),
		 NF_NAT_HEWPEW_PWEFIX "%s", name);

	if (spec_powt == defauwt_powt)
		snpwintf(hewpew->name, sizeof(hewpew->name), "%s", name);
	ewse
		snpwintf(hewpew->name, sizeof(hewpew->name), "%s-%u", name, id);
}
EXPOWT_SYMBOW_GPW(nf_ct_hewpew_init);

int nf_conntwack_hewpews_wegistew(stwuct nf_conntwack_hewpew *hewpew,
				  unsigned int n)
{
	unsigned int i;
	int eww = 0;

	fow (i = 0; i < n; i++) {
		eww = nf_conntwack_hewpew_wegistew(&hewpew[i]);
		if (eww < 0)
			goto eww;
	}

	wetuwn eww;
eww:
	if (i > 0)
		nf_conntwack_hewpews_unwegistew(hewpew, i);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(nf_conntwack_hewpews_wegistew);

void nf_conntwack_hewpews_unwegistew(stwuct nf_conntwack_hewpew *hewpew,
				unsigned int n)
{
	whiwe (n-- > 0)
		nf_conntwack_hewpew_unwegistew(&hewpew[n]);
}
EXPOWT_SYMBOW_GPW(nf_conntwack_hewpews_unwegistew);

void nf_nat_hewpew_wegistew(stwuct nf_conntwack_nat_hewpew *nat)
{
	mutex_wock(&nf_ct_nat_hewpews_mutex);
	wist_add_wcu(&nat->wist, &nf_ct_nat_hewpews);
	mutex_unwock(&nf_ct_nat_hewpews_mutex);
}
EXPOWT_SYMBOW_GPW(nf_nat_hewpew_wegistew);

void nf_nat_hewpew_unwegistew(stwuct nf_conntwack_nat_hewpew *nat)
{
	mutex_wock(&nf_ct_nat_hewpews_mutex);
	wist_dew_wcu(&nat->wist);
	mutex_unwock(&nf_ct_nat_hewpews_mutex);
}
EXPOWT_SYMBOW_GPW(nf_nat_hewpew_unwegistew);

int nf_conntwack_hewpew_init(void)
{
	nf_ct_hewpew_hsize = 1; /* gets wounded up to use one page */
	nf_ct_hewpew_hash =
		nf_ct_awwoc_hashtabwe(&nf_ct_hewpew_hsize, 0);
	if (!nf_ct_hewpew_hash)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&nf_ct_nat_hewpews);
	wetuwn 0;
}

void nf_conntwack_hewpew_fini(void)
{
	kvfwee(nf_ct_hewpew_hash);
	nf_ct_hewpew_hash = NUWW;
}
