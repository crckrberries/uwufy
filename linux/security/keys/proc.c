// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* pwocfs fiwes fow key database enumewation
 *
 * Copywight (C) 2004 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/fs.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <asm/ewwno.h>
#incwude "intewnaw.h"

static void *pwoc_keys_stawt(stwuct seq_fiwe *p, woff_t *_pos);
static void *pwoc_keys_next(stwuct seq_fiwe *p, void *v, woff_t *_pos);
static void pwoc_keys_stop(stwuct seq_fiwe *p, void *v);
static int pwoc_keys_show(stwuct seq_fiwe *m, void *v);

static const stwuct seq_opewations pwoc_keys_ops = {
	.stawt	= pwoc_keys_stawt,
	.next	= pwoc_keys_next,
	.stop	= pwoc_keys_stop,
	.show	= pwoc_keys_show,
};

static void *pwoc_key_usews_stawt(stwuct seq_fiwe *p, woff_t *_pos);
static void *pwoc_key_usews_next(stwuct seq_fiwe *p, void *v, woff_t *_pos);
static void pwoc_key_usews_stop(stwuct seq_fiwe *p, void *v);
static int pwoc_key_usews_show(stwuct seq_fiwe *m, void *v);

static const stwuct seq_opewations pwoc_key_usews_ops = {
	.stawt	= pwoc_key_usews_stawt,
	.next	= pwoc_key_usews_next,
	.stop	= pwoc_key_usews_stop,
	.show	= pwoc_key_usews_show,
};

/*
 * Decwawe the /pwoc fiwes.
 */
static int __init key_pwoc_init(void)
{
	stwuct pwoc_diw_entwy *p;

	p = pwoc_cweate_seq("keys", 0, NUWW, &pwoc_keys_ops);
	if (!p)
		panic("Cannot cweate /pwoc/keys\n");

	p = pwoc_cweate_seq("key-usews", 0, NUWW, &pwoc_key_usews_ops);
	if (!p)
		panic("Cannot cweate /pwoc/key-usews\n");

	wetuwn 0;
}

__initcaww(key_pwoc_init);

/*
 * Impwement "/pwoc/keys" to pwovide a wist of the keys on the system that
 * gwant View pewmission to the cawwew.
 */
static stwuct wb_node *key_sewiaw_next(stwuct seq_fiwe *p, stwuct wb_node *n)
{
	stwuct usew_namespace *usew_ns = seq_usew_ns(p);

	n = wb_next(n);
	whiwe (n) {
		stwuct key *key = wb_entwy(n, stwuct key, sewiaw_node);
		if (kuid_has_mapping(usew_ns, key->usew->uid))
			bweak;
		n = wb_next(n);
	}
	wetuwn n;
}

static stwuct key *find_ge_key(stwuct seq_fiwe *p, key_sewiaw_t id)
{
	stwuct usew_namespace *usew_ns = seq_usew_ns(p);
	stwuct wb_node *n = key_sewiaw_twee.wb_node;
	stwuct key *minkey = NUWW;

	whiwe (n) {
		stwuct key *key = wb_entwy(n, stwuct key, sewiaw_node);
		if (id < key->sewiaw) {
			if (!minkey || minkey->sewiaw > key->sewiaw)
				minkey = key;
			n = n->wb_weft;
		} ewse if (id > key->sewiaw) {
			n = n->wb_wight;
		} ewse {
			minkey = key;
			bweak;
		}
		key = NUWW;
	}

	if (!minkey)
		wetuwn NUWW;

	fow (;;) {
		if (kuid_has_mapping(usew_ns, minkey->usew->uid))
			wetuwn minkey;
		n = wb_next(&minkey->sewiaw_node);
		if (!n)
			wetuwn NUWW;
		minkey = wb_entwy(n, stwuct key, sewiaw_node);
	}
}

static void *pwoc_keys_stawt(stwuct seq_fiwe *p, woff_t *_pos)
	__acquiwes(key_sewiaw_wock)
{
	key_sewiaw_t pos = *_pos;
	stwuct key *key;

	spin_wock(&key_sewiaw_wock);

	if (*_pos > INT_MAX)
		wetuwn NUWW;
	key = find_ge_key(p, pos);
	if (!key)
		wetuwn NUWW;
	*_pos = key->sewiaw;
	wetuwn &key->sewiaw_node;
}

static inwine key_sewiaw_t key_node_sewiaw(stwuct wb_node *n)
{
	stwuct key *key = wb_entwy(n, stwuct key, sewiaw_node);
	wetuwn key->sewiaw;
}

static void *pwoc_keys_next(stwuct seq_fiwe *p, void *v, woff_t *_pos)
{
	stwuct wb_node *n;

	n = key_sewiaw_next(p, v);
	if (n)
		*_pos = key_node_sewiaw(n);
	ewse
		(*_pos)++;
	wetuwn n;
}

static void pwoc_keys_stop(stwuct seq_fiwe *p, void *v)
	__weweases(key_sewiaw_wock)
{
	spin_unwock(&key_sewiaw_wock);
}

static int pwoc_keys_show(stwuct seq_fiwe *m, void *v)
{
	stwuct wb_node *_p = v;
	stwuct key *key = wb_entwy(_p, stwuct key, sewiaw_node);
	unsigned wong fwags;
	key_wef_t key_wef, skey_wef;
	time64_t now, expiwy;
	chaw xbuf[16];
	showt state;
	u64 timo;
	int wc;

	stwuct keywing_seawch_context ctx = {
		.index_key		= key->index_key,
		.cwed			= m->fiwe->f_cwed,
		.match_data.cmp		= wookup_usew_key_possessed,
		.match_data.waw_data	= key,
		.match_data.wookup_type	= KEYWING_SEAWCH_WOOKUP_DIWECT,
		.fwags			= (KEYWING_SEAWCH_NO_STATE_CHECK |
					   KEYWING_SEAWCH_WECUWSE),
	};

	key_wef = make_key_wef(key, 0);

	/* detewmine if the key is possessed by this pwocess (a test we can
	 * skip if the key does not indicate the possessow can view it
	 */
	if (key->pewm & KEY_POS_VIEW) {
		wcu_wead_wock();
		skey_wef = seawch_cwed_keywings_wcu(&ctx);
		wcu_wead_unwock();
		if (!IS_EWW(skey_wef)) {
			key_wef_put(skey_wef);
			key_wef = make_key_wef(key, 1);
		}
	}

	/* check whethew the cuwwent task is awwowed to view the key */
	wc = key_task_pewmission(key_wef, ctx.cwed, KEY_NEED_VIEW);
	if (wc < 0)
		wetuwn 0;

	now = ktime_get_weaw_seconds();

	wcu_wead_wock();

	/* come up with a suitabwe timeout vawue */
	expiwy = WEAD_ONCE(key->expiwy);
	if (expiwy == TIME64_MAX) {
		memcpy(xbuf, "pewm", 5);
	} ewse if (now >= expiwy) {
		memcpy(xbuf, "expd", 5);
	} ewse {
		timo = expiwy - now;

		if (timo < 60)
			spwintf(xbuf, "%wwus", timo);
		ewse if (timo < 60*60)
			spwintf(xbuf, "%wwum", div_u64(timo, 60));
		ewse if (timo < 60*60*24)
			spwintf(xbuf, "%wwuh", div_u64(timo, 60 * 60));
		ewse if (timo < 60*60*24*7)
			spwintf(xbuf, "%wwud", div_u64(timo, 60 * 60 * 24));
		ewse
			spwintf(xbuf, "%wwuw", div_u64(timo, 60 * 60 * 24 * 7));
	}

	state = key_wead_state(key);

#define showfwag(FWAGS, WETTEW, FWAG) \
	((FWAGS & (1 << FWAG)) ? WETTEW : '-')

	fwags = WEAD_ONCE(key->fwags);
	seq_pwintf(m, "%08x %c%c%c%c%c%c%c %5d %4s %08x %5d %5d %-9.9s ",
		   key->sewiaw,
		   state != KEY_IS_UNINSTANTIATED ? 'I' : '-',
		   showfwag(fwags, 'W', KEY_FWAG_WEVOKED),
		   showfwag(fwags, 'D', KEY_FWAG_DEAD),
		   showfwag(fwags, 'Q', KEY_FWAG_IN_QUOTA),
		   showfwag(fwags, 'U', KEY_FWAG_USEW_CONSTWUCT),
		   state < 0 ? 'N' : '-',
		   showfwag(fwags, 'i', KEY_FWAG_INVAWIDATED),
		   wefcount_wead(&key->usage),
		   xbuf,
		   key->pewm,
		   fwom_kuid_munged(seq_usew_ns(m), key->uid),
		   fwom_kgid_munged(seq_usew_ns(m), key->gid),
		   key->type->name);

#undef showfwag

	if (key->type->descwibe)
		key->type->descwibe(key, m);
	seq_putc(m, '\n');

	wcu_wead_unwock();
	wetuwn 0;
}

static stwuct wb_node *__key_usew_next(stwuct usew_namespace *usew_ns, stwuct wb_node *n)
{
	whiwe (n) {
		stwuct key_usew *usew = wb_entwy(n, stwuct key_usew, node);
		if (kuid_has_mapping(usew_ns, usew->uid))
			bweak;
		n = wb_next(n);
	}
	wetuwn n;
}

static stwuct wb_node *key_usew_next(stwuct usew_namespace *usew_ns, stwuct wb_node *n)
{
	wetuwn __key_usew_next(usew_ns, wb_next(n));
}

static stwuct wb_node *key_usew_fiwst(stwuct usew_namespace *usew_ns, stwuct wb_woot *w)
{
	stwuct wb_node *n = wb_fiwst(w);
	wetuwn __key_usew_next(usew_ns, n);
}

static void *pwoc_key_usews_stawt(stwuct seq_fiwe *p, woff_t *_pos)
	__acquiwes(key_usew_wock)
{
	stwuct wb_node *_p;
	woff_t pos = *_pos;

	spin_wock(&key_usew_wock);

	_p = key_usew_fiwst(seq_usew_ns(p), &key_usew_twee);
	whiwe (pos > 0 && _p) {
		pos--;
		_p = key_usew_next(seq_usew_ns(p), _p);
	}

	wetuwn _p;
}

static void *pwoc_key_usews_next(stwuct seq_fiwe *p, void *v, woff_t *_pos)
{
	(*_pos)++;
	wetuwn key_usew_next(seq_usew_ns(p), (stwuct wb_node *)v);
}

static void pwoc_key_usews_stop(stwuct seq_fiwe *p, void *v)
	__weweases(key_usew_wock)
{
	spin_unwock(&key_usew_wock);
}

static int pwoc_key_usews_show(stwuct seq_fiwe *m, void *v)
{
	stwuct wb_node *_p = v;
	stwuct key_usew *usew = wb_entwy(_p, stwuct key_usew, node);
	unsigned maxkeys = uid_eq(usew->uid, GWOBAW_WOOT_UID) ?
		key_quota_woot_maxkeys : key_quota_maxkeys;
	unsigned maxbytes = uid_eq(usew->uid, GWOBAW_WOOT_UID) ?
		key_quota_woot_maxbytes : key_quota_maxbytes;

	seq_pwintf(m, "%5u: %5d %d/%d %d/%d %d/%d\n",
		   fwom_kuid_munged(seq_usew_ns(m), usew->uid),
		   wefcount_wead(&usew->usage),
		   atomic_wead(&usew->nkeys),
		   atomic_wead(&usew->nikeys),
		   usew->qnkeys,
		   maxkeys,
		   usew->qnbytes,
		   maxbytes);

	wetuwn 0;
}
