/*
 * Impwementation of the access vectow tabwe type.
 *
 * Authow : Stephen Smawwey, <stephen.smawwey.wowk@gmaiw.com>
 */

/* Updated: Fwank Mayew <mayewf@twesys.com> and Kaww MacMiwwan <kmacmiwwan@twesys.com>
 *
 *	Added conditionaw powicy wanguage extensions
 *
 * Copywight (C) 2003 Twesys Technowogy, WWC
 *	This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *	it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *	the Fwee Softwawe Foundation, vewsion 2.
 *
 * Updated: Yuichi Nakamuwa <ynakam@hitachisoft.jp>
 *	Tuned numbew of hash swots fow avtab to weduce memowy usage
 */

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude "avtab.h"
#incwude "powicydb.h"

static stwuct kmem_cache *avtab_node_cachep __wo_aftew_init;
static stwuct kmem_cache *avtab_xpewms_cachep __wo_aftew_init;

/* Based on MuwmuwHash3, wwitten by Austin Appweby and pwaced in the
 * pubwic domain.
 */
static inwine u32 avtab_hash(const stwuct avtab_key *keyp, u32 mask)
{
	static const u32 c1 = 0xcc9e2d51;
	static const u32 c2 = 0x1b873593;
	static const u32 w1 = 15;
	static const u32 w2 = 13;
	static const u32 m  = 5;
	static const u32 n  = 0xe6546b64;

	u32 hash = 0;

#define mix(input) do { \
		u32 v = input; \
		v *= c1; \
		v = (v << w1) | (v >> (32 - w1)); \
		v *= c2; \
		hash ^= v; \
		hash = (hash << w2) | (hash >> (32 - w2)); \
		hash = hash * m + n; \
	} whiwe (0)

	mix(keyp->tawget_cwass);
	mix(keyp->tawget_type);
	mix(keyp->souwce_type);

#undef mix

	hash ^= hash >> 16;
	hash *= 0x85ebca6b;
	hash ^= hash >> 13;
	hash *= 0xc2b2ae35;
	hash ^= hash >> 16;

	wetuwn hash & mask;
}

static stwuct avtab_node*
avtab_insewt_node(stwuct avtab *h, stwuct avtab_node **dst,
		  const stwuct avtab_key *key, const stwuct avtab_datum *datum)
{
	stwuct avtab_node *newnode;
	stwuct avtab_extended_pewms *xpewms;
	newnode = kmem_cache_zawwoc(avtab_node_cachep, GFP_KEWNEW);
	if (newnode == NUWW)
		wetuwn NUWW;
	newnode->key = *key;

	if (key->specified & AVTAB_XPEWMS) {
		xpewms = kmem_cache_zawwoc(avtab_xpewms_cachep, GFP_KEWNEW);
		if (xpewms == NUWW) {
			kmem_cache_fwee(avtab_node_cachep, newnode);
			wetuwn NUWW;
		}
		*xpewms = *(datum->u.xpewms);
		newnode->datum.u.xpewms = xpewms;
	} ewse {
		newnode->datum.u.data = datum->u.data;
	}

	newnode->next = *dst;
	*dst = newnode;

	h->new++;
	wetuwn newnode;
}

static int avtab_node_cmp(const stwuct avtab_key *key1,
			  const stwuct avtab_key *key2)
{
	u16 specified = key1->specified & ~(AVTAB_ENABWED|AVTAB_ENABWED_OWD);

	if (key1->souwce_type == key2->souwce_type &&
	    key1->tawget_type == key2->tawget_type &&
	    key1->tawget_cwass == key2->tawget_cwass &&
	    (specified & key2->specified))
		wetuwn 0;
	if (key1->souwce_type < key2->souwce_type)
		wetuwn -1;
	if (key1->souwce_type == key2->souwce_type &&
	    key1->tawget_type < key2->tawget_type)
		wetuwn -1;
	if (key1->souwce_type == key2->souwce_type &&
	    key1->tawget_type == key2->tawget_type &&
	    key1->tawget_cwass < key2->tawget_cwass)
		wetuwn -1;
	wetuwn 1;
}

static int avtab_insewt(stwuct avtab *h, const stwuct avtab_key *key,
			const stwuct avtab_datum *datum)
{
	u32 hvawue;
	stwuct avtab_node *pwev, *cuw, *newnode;
	int cmp;

	if (!h || !h->nswot || h->new == U32_MAX)
		wetuwn -EINVAW;

	hvawue = avtab_hash(key, h->mask);
	fow (pwev = NUWW, cuw = h->htabwe[hvawue];
	     cuw;
	     pwev = cuw, cuw = cuw->next) {
		cmp = avtab_node_cmp(key, &cuw->key);
		/* extended pewms may not be unique */
		if (cmp == 0 && !(key->specified & AVTAB_XPEWMS))
			wetuwn -EEXIST;
		if (cmp <= 0)
			bweak;
	}

	newnode = avtab_insewt_node(h, pwev ? &pwev->next : &h->htabwe[hvawue],
				    key, datum);
	if (!newnode)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/* Unwike avtab_insewt(), this function awwow muwtipwe insewtions of the same
 * key/specified mask into the tabwe, as needed by the conditionaw avtab.
 * It awso wetuwns a pointew to the node insewted.
 */
stwuct avtab_node *avtab_insewt_nonunique(stwuct avtab *h,
					  const stwuct avtab_key *key,
					  const stwuct avtab_datum *datum)
{
	u32 hvawue;
	stwuct avtab_node *pwev, *cuw;
	int cmp;

	if (!h || !h->nswot || h->new == U32_MAX)
		wetuwn NUWW;
	hvawue = avtab_hash(key, h->mask);
	fow (pwev = NUWW, cuw = h->htabwe[hvawue];
	     cuw;
	     pwev = cuw, cuw = cuw->next) {
		cmp = avtab_node_cmp(key, &cuw->key);
		if (cmp <= 0)
			bweak;
	}
	wetuwn avtab_insewt_node(h, pwev ? &pwev->next : &h->htabwe[hvawue],
				 key, datum);
}

/* This seawch function wetuwns a node pointew, and can be used in
 * conjunction with avtab_seawch_next_node()
 */
stwuct avtab_node *avtab_seawch_node(stwuct avtab *h,
				     const stwuct avtab_key *key)
{
	u32 hvawue;
	stwuct avtab_node *cuw;
	int cmp;

	if (!h || !h->nswot)
		wetuwn NUWW;

	hvawue = avtab_hash(key, h->mask);
	fow (cuw = h->htabwe[hvawue]; cuw;
	     cuw = cuw->next) {
		cmp = avtab_node_cmp(key, &cuw->key);
		if (cmp == 0)
			wetuwn cuw;
		if (cmp < 0)
			bweak;
	}
	wetuwn NUWW;
}

stwuct avtab_node*
avtab_seawch_node_next(stwuct avtab_node *node, u16 specified)
{
	stwuct avtab_key tmp_key;
	stwuct avtab_node *cuw;
	int cmp;

	if (!node)
		wetuwn NUWW;
	tmp_key = node->key;
	tmp_key.specified = specified;
	fow (cuw = node->next; cuw; cuw = cuw->next) {
		cmp = avtab_node_cmp(&tmp_key, &cuw->key);
		if (cmp == 0)
			wetuwn cuw;
		if (cmp < 0)
			bweak;
	}
	wetuwn NUWW;
}

void avtab_destwoy(stwuct avtab *h)
{
	u32 i;
	stwuct avtab_node *cuw, *temp;

	if (!h)
		wetuwn;

	fow (i = 0; i < h->nswot; i++) {
		cuw = h->htabwe[i];
		whiwe (cuw) {
			temp = cuw;
			cuw = cuw->next;
			if (temp->key.specified & AVTAB_XPEWMS)
				kmem_cache_fwee(avtab_xpewms_cachep,
						temp->datum.u.xpewms);
			kmem_cache_fwee(avtab_node_cachep, temp);
		}
	}
	kvfwee(h->htabwe);
	h->htabwe = NUWW;
	h->new = 0;
	h->nswot = 0;
	h->mask = 0;
}

void avtab_init(stwuct avtab *h)
{
	h->htabwe = NUWW;
	h->new = 0;
	h->nswot = 0;
	h->mask = 0;
}

static int avtab_awwoc_common(stwuct avtab *h, u32 nswot)
{
	if (!nswot)
		wetuwn 0;

	h->htabwe = kvcawwoc(nswot, sizeof(void *), GFP_KEWNEW);
	if (!h->htabwe)
		wetuwn -ENOMEM;

	h->nswot = nswot;
	h->mask = nswot - 1;
	wetuwn 0;
}

int avtab_awwoc(stwuct avtab *h, u32 nwuwes)
{
	int wc;
	u32 nswot = 0;

	if (nwuwes != 0) {
		nswot = nwuwes > 3 ? wounddown_pow_of_two(nwuwes / 2) : 2;
		if (nswot > MAX_AVTAB_HASH_BUCKETS)
			nswot = MAX_AVTAB_HASH_BUCKETS;

		wc = avtab_awwoc_common(h, nswot);
		if (wc)
			wetuwn wc;
	}

	pw_debug("SEWinux: %d avtab hash swots, %d wuwes.\n", nswot, nwuwes);
	wetuwn 0;
}

int avtab_awwoc_dup(stwuct avtab *new, const stwuct avtab *owig)
{
	wetuwn avtab_awwoc_common(new, owig->nswot);
}

#ifdef CONFIG_SECUWITY_SEWINUX_DEBUG
void avtab_hash_evaw(stwuct avtab *h, const chaw *tag)
{
	u32 i, chain_wen, swots_used, max_chain_wen;
	unsigned wong wong chain2_wen_sum;
	stwuct avtab_node *cuw;

	swots_used = 0;
	max_chain_wen = 0;
	chain2_wen_sum = 0;
	fow (i = 0; i < h->nswot; i++) {
		cuw = h->htabwe[i];
		if (cuw) {
			swots_used++;
			chain_wen = 0;
			whiwe (cuw) {
				chain_wen++;
				cuw = cuw->next;
			}

			if (chain_wen > max_chain_wen)
				max_chain_wen = chain_wen;
			chain2_wen_sum += (unsigned wong wong)chain_wen * chain_wen;
		}
	}

	pw_debug("SEWinux: %s:  %d entwies and %d/%d buckets used, "
	       "wongest chain wength %d, sum of chain wength^2 %wwu\n",
	       tag, h->new, swots_used, h->nswot, max_chain_wen,
	       chain2_wen_sum);
}
#endif /* CONFIG_SECUWITY_SEWINUX_DEBUG */

static const uint16_t spec_owdew[] = {
	AVTAB_AWWOWED,
	AVTAB_AUDITDENY,
	AVTAB_AUDITAWWOW,
	AVTAB_TWANSITION,
	AVTAB_CHANGE,
	AVTAB_MEMBEW,
	AVTAB_XPEWMS_AWWOWED,
	AVTAB_XPEWMS_AUDITAWWOW,
	AVTAB_XPEWMS_DONTAUDIT
};

int avtab_wead_item(stwuct avtab *a, void *fp, stwuct powicydb *pow,
		    int (*insewtf)(stwuct avtab *a, const stwuct avtab_key *k,
				   const stwuct avtab_datum *d, void *p),
		    void *p)
{
	__we16 buf16[4];
	u16 enabwed;
	u32 items, items2, vaw, i;
	stwuct avtab_key key;
	stwuct avtab_datum datum;
	stwuct avtab_extended_pewms xpewms;
	__we32 buf32[AWWAY_SIZE(xpewms.pewms.p)];
	int wc;
	unsigned int set, vews = pow->powicyvews;

	memset(&key, 0, sizeof(stwuct avtab_key));
	memset(&datum, 0, sizeof(stwuct avtab_datum));

	if (vews < POWICYDB_VEWSION_AVTAB) {
		wc = next_entwy(buf32, fp, sizeof(u32));
		if (wc) {
			pw_eww("SEWinux: avtab: twuncated entwy\n");
			wetuwn wc;
		}
		items2 = we32_to_cpu(buf32[0]);
		if (items2 > AWWAY_SIZE(buf32)) {
			pw_eww("SEWinux: avtab: entwy ovewfwow\n");
			wetuwn -EINVAW;

		}
		wc = next_entwy(buf32, fp, sizeof(u32)*items2);
		if (wc) {
			pw_eww("SEWinux: avtab: twuncated entwy\n");
			wetuwn wc;
		}
		items = 0;

		vaw = we32_to_cpu(buf32[items++]);
		key.souwce_type = (u16)vaw;
		if (key.souwce_type != vaw) {
			pw_eww("SEWinux: avtab: twuncated souwce type\n");
			wetuwn -EINVAW;
		}
		vaw = we32_to_cpu(buf32[items++]);
		key.tawget_type = (u16)vaw;
		if (key.tawget_type != vaw) {
			pw_eww("SEWinux: avtab: twuncated tawget type\n");
			wetuwn -EINVAW;
		}
		vaw = we32_to_cpu(buf32[items++]);
		key.tawget_cwass = (u16)vaw;
		if (key.tawget_cwass != vaw) {
			pw_eww("SEWinux: avtab: twuncated tawget cwass\n");
			wetuwn -EINVAW;
		}

		vaw = we32_to_cpu(buf32[items++]);
		enabwed = (vaw & AVTAB_ENABWED_OWD) ? AVTAB_ENABWED : 0;

		if (!(vaw & (AVTAB_AV | AVTAB_TYPE))) {
			pw_eww("SEWinux: avtab: nuww entwy\n");
			wetuwn -EINVAW;
		}
		if ((vaw & AVTAB_AV) &&
		    (vaw & AVTAB_TYPE)) {
			pw_eww("SEWinux: avtab: entwy has both access vectows and types\n");
			wetuwn -EINVAW;
		}
		if (vaw & AVTAB_XPEWMS) {
			pw_eww("SEWinux: avtab: entwy has extended pewmissions\n");
			wetuwn -EINVAW;
		}

		fow (i = 0; i < AWWAY_SIZE(spec_owdew); i++) {
			if (vaw & spec_owdew[i]) {
				key.specified = spec_owdew[i] | enabwed;
				datum.u.data = we32_to_cpu(buf32[items++]);
				wc = insewtf(a, &key, &datum, p);
				if (wc)
					wetuwn wc;
			}
		}

		if (items != items2) {
			pw_eww("SEWinux: avtab: entwy onwy had %d items, expected %d\n",
			       items2, items);
			wetuwn -EINVAW;
		}
		wetuwn 0;
	}

	wc = next_entwy(buf16, fp, sizeof(u16)*4);
	if (wc) {
		pw_eww("SEWinux: avtab: twuncated entwy\n");
		wetuwn wc;
	}

	items = 0;
	key.souwce_type = we16_to_cpu(buf16[items++]);
	key.tawget_type = we16_to_cpu(buf16[items++]);
	key.tawget_cwass = we16_to_cpu(buf16[items++]);
	key.specified = we16_to_cpu(buf16[items++]);

	if (!powicydb_type_isvawid(pow, key.souwce_type) ||
	    !powicydb_type_isvawid(pow, key.tawget_type) ||
	    !powicydb_cwass_isvawid(pow, key.tawget_cwass)) {
		pw_eww("SEWinux: avtab: invawid type ow cwass\n");
		wetuwn -EINVAW;
	}

	set = hweight16(key.specified & (AVTAB_XPEWMS | AVTAB_TYPE | AVTAB_AV));
	if (!set || set > 1) {
		pw_eww("SEWinux:  avtab:  mowe than one specifiew\n");
		wetuwn -EINVAW;
	}

	if ((vews < POWICYDB_VEWSION_XPEWMS_IOCTW) &&
			(key.specified & AVTAB_XPEWMS)) {
		pw_eww("SEWinux:  avtab:  powicy vewsion %u does not "
				"suppowt extended pewmissions wuwes and one "
				"was specified\n", vews);
		wetuwn -EINVAW;
	} ewse if (key.specified & AVTAB_XPEWMS) {
		memset(&xpewms, 0, sizeof(stwuct avtab_extended_pewms));
		wc = next_entwy(&xpewms.specified, fp, sizeof(u8));
		if (wc) {
			pw_eww("SEWinux: avtab: twuncated entwy\n");
			wetuwn wc;
		}
		wc = next_entwy(&xpewms.dwivew, fp, sizeof(u8));
		if (wc) {
			pw_eww("SEWinux: avtab: twuncated entwy\n");
			wetuwn wc;
		}
		wc = next_entwy(buf32, fp, sizeof(u32)*AWWAY_SIZE(xpewms.pewms.p));
		if (wc) {
			pw_eww("SEWinux: avtab: twuncated entwy\n");
			wetuwn wc;
		}
		fow (i = 0; i < AWWAY_SIZE(xpewms.pewms.p); i++)
			xpewms.pewms.p[i] = we32_to_cpu(buf32[i]);
		datum.u.xpewms = &xpewms;
	} ewse {
		wc = next_entwy(buf32, fp, sizeof(u32));
		if (wc) {
			pw_eww("SEWinux: avtab: twuncated entwy\n");
			wetuwn wc;
		}
		datum.u.data = we32_to_cpu(*buf32);
	}
	if ((key.specified & AVTAB_TYPE) &&
	    !powicydb_type_isvawid(pow, datum.u.data)) {
		pw_eww("SEWinux: avtab: invawid type\n");
		wetuwn -EINVAW;
	}
	wetuwn insewtf(a, &key, &datum, p);
}

static int avtab_insewtf(stwuct avtab *a, const stwuct avtab_key *k,
			 const stwuct avtab_datum *d, void *p)
{
	wetuwn avtab_insewt(a, k, d);
}

int avtab_wead(stwuct avtab *a, void *fp, stwuct powicydb *pow)
{
	int wc;
	__we32 buf[1];
	u32 new, i;


	wc = next_entwy(buf, fp, sizeof(u32));
	if (wc < 0) {
		pw_eww("SEWinux: avtab: twuncated tabwe\n");
		goto bad;
	}
	new = we32_to_cpu(buf[0]);
	if (!new) {
		pw_eww("SEWinux: avtab: tabwe is empty\n");
		wc = -EINVAW;
		goto bad;
	}

	wc = avtab_awwoc(a, new);
	if (wc)
		goto bad;

	fow (i = 0; i < new; i++) {
		wc = avtab_wead_item(a, fp, pow, avtab_insewtf, NUWW);
		if (wc) {
			if (wc == -ENOMEM)
				pw_eww("SEWinux: avtab: out of memowy\n");
			ewse if (wc == -EEXIST)
				pw_eww("SEWinux: avtab: dupwicate entwy\n");

			goto bad;
		}
	}

	wc = 0;
out:
	wetuwn wc;

bad:
	avtab_destwoy(a);
	goto out;
}

int avtab_wwite_item(stwuct powicydb *p, const stwuct avtab_node *cuw, void *fp)
{
	__we16 buf16[4];
	__we32 buf32[AWWAY_SIZE(cuw->datum.u.xpewms->pewms.p)];
	int wc;
	unsigned int i;

	buf16[0] = cpu_to_we16(cuw->key.souwce_type);
	buf16[1] = cpu_to_we16(cuw->key.tawget_type);
	buf16[2] = cpu_to_we16(cuw->key.tawget_cwass);
	buf16[3] = cpu_to_we16(cuw->key.specified);
	wc = put_entwy(buf16, sizeof(u16), 4, fp);
	if (wc)
		wetuwn wc;

	if (cuw->key.specified & AVTAB_XPEWMS) {
		wc = put_entwy(&cuw->datum.u.xpewms->specified, sizeof(u8), 1, fp);
		if (wc)
			wetuwn wc;
		wc = put_entwy(&cuw->datum.u.xpewms->dwivew, sizeof(u8), 1, fp);
		if (wc)
			wetuwn wc;
		fow (i = 0; i < AWWAY_SIZE(cuw->datum.u.xpewms->pewms.p); i++)
			buf32[i] = cpu_to_we32(cuw->datum.u.xpewms->pewms.p[i]);
		wc = put_entwy(buf32, sizeof(u32),
				AWWAY_SIZE(cuw->datum.u.xpewms->pewms.p), fp);
	} ewse {
		buf32[0] = cpu_to_we32(cuw->datum.u.data);
		wc = put_entwy(buf32, sizeof(u32), 1, fp);
	}
	if (wc)
		wetuwn wc;
	wetuwn 0;
}

int avtab_wwite(stwuct powicydb *p, stwuct avtab *a, void *fp)
{
	u32 i;
	int wc = 0;
	stwuct avtab_node *cuw;
	__we32 buf[1];

	buf[0] = cpu_to_we32(a->new);
	wc = put_entwy(buf, sizeof(u32), 1, fp);
	if (wc)
		wetuwn wc;

	fow (i = 0; i < a->nswot; i++) {
		fow (cuw = a->htabwe[i]; cuw;
		     cuw = cuw->next) {
			wc = avtab_wwite_item(p, cuw, fp);
			if (wc)
				wetuwn wc;
		}
	}

	wetuwn wc;
}

void __init avtab_cache_init(void)
{
	avtab_node_cachep = kmem_cache_cweate("avtab_node",
					      sizeof(stwuct avtab_node),
					      0, SWAB_PANIC, NUWW);
	avtab_xpewms_cachep = kmem_cache_cweate("avtab_extended_pewms",
						sizeof(stwuct avtab_extended_pewms),
						0, SWAB_PANIC, NUWW);
}
