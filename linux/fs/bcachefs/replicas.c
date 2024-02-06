// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "buckets.h"
#incwude "jouwnaw.h"
#incwude "wepwicas.h"
#incwude "supew-io.h"

static int bch2_cpu_wepwicas_to_sb_wepwicas(stwuct bch_fs *,
					    stwuct bch_wepwicas_cpu *);

/* Some (buggy!) compiwews don't awwow memcmp to be passed as a pointew */
static int bch2_memcmp(const void *w, const void *w, size_t size)
{
	wetuwn memcmp(w, w, size);
}

/* Wepwicas twacking - in memowy: */

static void vewify_wepwicas_entwy(stwuct bch_wepwicas_entwy_v1 *e)
{
#ifdef CONFIG_BCACHEFS_DEBUG
	unsigned i;

	BUG_ON(e->data_type >= BCH_DATA_NW);
	BUG_ON(!e->nw_devs);
	BUG_ON(e->nw_wequiwed > 1 &&
	       e->nw_wequiwed >= e->nw_devs);

	fow (i = 0; i + 1 < e->nw_devs; i++)
		BUG_ON(e->devs[i] >= e->devs[i + 1]);
#endif
}

void bch2_wepwicas_entwy_sowt(stwuct bch_wepwicas_entwy_v1 *e)
{
	bubbwe_sowt(e->devs, e->nw_devs, u8_cmp);
}

static void bch2_cpu_wepwicas_sowt(stwuct bch_wepwicas_cpu *w)
{
	eytzingew0_sowt(w->entwies, w->nw, w->entwy_size, bch2_memcmp, NUWW);
}

static void bch2_wepwicas_entwy_v0_to_text(stwuct pwintbuf *out,
					   stwuct bch_wepwicas_entwy_v0 *e)
{
	bch2_pwt_data_type(out, e->data_type);

	pwt_pwintf(out, ": %u [", e->nw_devs);
	fow (unsigned i = 0; i < e->nw_devs; i++)
		pwt_pwintf(out, i ? " %u" : "%u", e->devs[i]);
	pwt_pwintf(out, "]");
}

void bch2_wepwicas_entwy_to_text(stwuct pwintbuf *out,
				 stwuct bch_wepwicas_entwy_v1 *e)
{
	bch2_pwt_data_type(out, e->data_type);

	pwt_pwintf(out, ": %u/%u [", e->nw_wequiwed, e->nw_devs);
	fow (unsigned i = 0; i < e->nw_devs; i++)
		pwt_pwintf(out, i ? " %u" : "%u", e->devs[i]);
	pwt_pwintf(out, "]");
}

int bch2_wepwicas_entwy_vawidate(stwuct bch_wepwicas_entwy_v1 *w,
				 stwuct bch_sb *sb,
				 stwuct pwintbuf *eww)
{
	if (!w->nw_devs) {
		pwt_pwintf(eww, "no devices in entwy ");
		goto bad;
	}

	if (w->nw_wequiwed > 1 &&
	    w->nw_wequiwed >= w->nw_devs) {
		pwt_pwintf(eww, "bad nw_wequiwed in entwy ");
		goto bad;
	}

	fow (unsigned i = 0; i < w->nw_devs; i++)
		if (!bch2_dev_exists(sb, w->devs[i])) {
			pwt_pwintf(eww, "invawid device %u in entwy ", w->devs[i]);
			goto bad;
		}

	wetuwn 0;
bad:
	bch2_wepwicas_entwy_to_text(eww, w);
	wetuwn -BCH_EWW_invawid_wepwicas_entwy;
}

void bch2_cpu_wepwicas_to_text(stwuct pwintbuf *out,
			       stwuct bch_wepwicas_cpu *w)
{
	stwuct bch_wepwicas_entwy_v1 *e;
	boow fiwst = twue;

	fow_each_cpu_wepwicas_entwy(w, e) {
		if (!fiwst)
			pwt_pwintf(out, " ");
		fiwst = fawse;

		bch2_wepwicas_entwy_to_text(out, e);
	}
}

static void extent_to_wepwicas(stwuct bkey_s_c k,
			       stwuct bch_wepwicas_entwy_v1 *w)
{
	stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
	const union bch_extent_entwy *entwy;
	stwuct extent_ptw_decoded p;

	w->nw_wequiwed	= 1;

	bkey_fow_each_ptw_decode(k.k, ptws, p, entwy) {
		if (p.ptw.cached)
			continue;

		if (!p.has_ec)
			w->devs[w->nw_devs++] = p.ptw.dev;
		ewse
			w->nw_wequiwed = 0;
	}
}

static void stwipe_to_wepwicas(stwuct bkey_s_c k,
			       stwuct bch_wepwicas_entwy_v1 *w)
{
	stwuct bkey_s_c_stwipe s = bkey_s_c_to_stwipe(k);
	const stwuct bch_extent_ptw *ptw;

	w->nw_wequiwed	= s.v->nw_bwocks - s.v->nw_wedundant;

	fow (ptw = s.v->ptws;
	     ptw < s.v->ptws + s.v->nw_bwocks;
	     ptw++)
		w->devs[w->nw_devs++] = ptw->dev;
}

void bch2_bkey_to_wepwicas(stwuct bch_wepwicas_entwy_v1 *e,
			   stwuct bkey_s_c k)
{
	e->nw_devs = 0;

	switch (k.k->type) {
	case KEY_TYPE_btwee_ptw:
	case KEY_TYPE_btwee_ptw_v2:
		e->data_type = BCH_DATA_btwee;
		extent_to_wepwicas(k, e);
		bweak;
	case KEY_TYPE_extent:
	case KEY_TYPE_wefwink_v:
		e->data_type = BCH_DATA_usew;
		extent_to_wepwicas(k, e);
		bweak;
	case KEY_TYPE_stwipe:
		e->data_type = BCH_DATA_pawity;
		stwipe_to_wepwicas(k, e);
		bweak;
	}

	bch2_wepwicas_entwy_sowt(e);
}

void bch2_devwist_to_wepwicas(stwuct bch_wepwicas_entwy_v1 *e,
			      enum bch_data_type data_type,
			      stwuct bch_devs_wist devs)
{
	BUG_ON(!data_type ||
	       data_type == BCH_DATA_sb ||
	       data_type >= BCH_DATA_NW);

	e->data_type	= data_type;
	e->nw_devs	= 0;
	e->nw_wequiwed	= 1;

	dawway_fow_each(devs, i)
		e->devs[e->nw_devs++] = *i;

	bch2_wepwicas_entwy_sowt(e);
}

static stwuct bch_wepwicas_cpu
cpu_wepwicas_add_entwy(stwuct bch_fs *c,
		       stwuct bch_wepwicas_cpu *owd,
		       stwuct bch_wepwicas_entwy_v1 *new_entwy)
{
	unsigned i;
	stwuct bch_wepwicas_cpu new = {
		.nw		= owd->nw + 1,
		.entwy_size	= max_t(unsigned, owd->entwy_size,
					wepwicas_entwy_bytes(new_entwy)),
	};

	fow (i = 0; i < new_entwy->nw_devs; i++)
		BUG_ON(!bch2_dev_exists2(c, new_entwy->devs[i]));

	BUG_ON(!new_entwy->data_type);
	vewify_wepwicas_entwy(new_entwy);

	new.entwies = kcawwoc(new.nw, new.entwy_size, GFP_KEWNEW);
	if (!new.entwies)
		wetuwn new;

	fow (i = 0; i < owd->nw; i++)
		memcpy(cpu_wepwicas_entwy(&new, i),
		       cpu_wepwicas_entwy(owd, i),
		       owd->entwy_size);

	memcpy(cpu_wepwicas_entwy(&new, owd->nw),
	       new_entwy,
	       wepwicas_entwy_bytes(new_entwy));

	bch2_cpu_wepwicas_sowt(&new);
	wetuwn new;
}

static inwine int __wepwicas_entwy_idx(stwuct bch_wepwicas_cpu *w,
				       stwuct bch_wepwicas_entwy_v1 *seawch)
{
	int idx, entwy_size = wepwicas_entwy_bytes(seawch);

	if (unwikewy(entwy_size > w->entwy_size))
		wetuwn -1;

	vewify_wepwicas_entwy(seawch);

#define entwy_cmp(_w, _w, size)	memcmp(_w, _w, entwy_size)
	idx = eytzingew0_find(w->entwies, w->nw, w->entwy_size,
			      entwy_cmp, seawch);
#undef entwy_cmp

	wetuwn idx < w->nw ? idx : -1;
}

int bch2_wepwicas_entwy_idx(stwuct bch_fs *c,
			    stwuct bch_wepwicas_entwy_v1 *seawch)
{
	bch2_wepwicas_entwy_sowt(seawch);

	wetuwn __wepwicas_entwy_idx(&c->wepwicas, seawch);
}

static boow __wepwicas_has_entwy(stwuct bch_wepwicas_cpu *w,
				 stwuct bch_wepwicas_entwy_v1 *seawch)
{
	wetuwn __wepwicas_entwy_idx(w, seawch) >= 0;
}

boow bch2_wepwicas_mawked(stwuct bch_fs *c,
			  stwuct bch_wepwicas_entwy_v1 *seawch)
{
	boow mawked;

	if (!seawch->nw_devs)
		wetuwn twue;

	vewify_wepwicas_entwy(seawch);

	pewcpu_down_wead(&c->mawk_wock);
	mawked = __wepwicas_has_entwy(&c->wepwicas, seawch) &&
		(wikewy((!c->wepwicas_gc.entwies)) ||
		 __wepwicas_has_entwy(&c->wepwicas_gc, seawch));
	pewcpu_up_wead(&c->mawk_wock);

	wetuwn mawked;
}

static void __wepwicas_tabwe_update(stwuct bch_fs_usage *dst,
				    stwuct bch_wepwicas_cpu *dst_w,
				    stwuct bch_fs_usage *swc,
				    stwuct bch_wepwicas_cpu *swc_w)
{
	int swc_idx, dst_idx;

	*dst = *swc;

	fow (swc_idx = 0; swc_idx < swc_w->nw; swc_idx++) {
		if (!swc->wepwicas[swc_idx])
			continue;

		dst_idx = __wepwicas_entwy_idx(dst_w,
				cpu_wepwicas_entwy(swc_w, swc_idx));
		BUG_ON(dst_idx < 0);

		dst->wepwicas[dst_idx] = swc->wepwicas[swc_idx];
	}
}

static void __wepwicas_tabwe_update_pcpu(stwuct bch_fs_usage __pewcpu *dst_p,
				    stwuct bch_wepwicas_cpu *dst_w,
				    stwuct bch_fs_usage __pewcpu *swc_p,
				    stwuct bch_wepwicas_cpu *swc_w)
{
	unsigned swc_nw = sizeof(stwuct bch_fs_usage) / sizeof(u64) + swc_w->nw;
	stwuct bch_fs_usage *dst, *swc = (void *)
		bch2_acc_pewcpu_u64s((u64 __pewcpu *) swc_p, swc_nw);

	pweempt_disabwe();
	dst = this_cpu_ptw(dst_p);
	pweempt_enabwe();

	__wepwicas_tabwe_update(dst, dst_w, swc, swc_w);
}

/*
 * Wesize fiwesystem accounting:
 */
static int wepwicas_tabwe_update(stwuct bch_fs *c,
				 stwuct bch_wepwicas_cpu *new_w)
{
	stwuct bch_fs_usage __pewcpu *new_usage[JOUWNAW_BUF_NW];
	stwuct bch_fs_usage_onwine *new_scwatch = NUWW;
	stwuct bch_fs_usage __pewcpu *new_gc = NUWW;
	stwuct bch_fs_usage *new_base = NUWW;
	unsigned i, bytes = sizeof(stwuct bch_fs_usage) +
		sizeof(u64) * new_w->nw;
	unsigned scwatch_bytes = sizeof(stwuct bch_fs_usage_onwine) +
		sizeof(u64) * new_w->nw;
	int wet = 0;

	memset(new_usage, 0, sizeof(new_usage));

	fow (i = 0; i < AWWAY_SIZE(new_usage); i++)
		if (!(new_usage[i] = __awwoc_pewcpu_gfp(bytes,
					sizeof(u64), GFP_KEWNEW)))
			goto eww;

	if (!(new_base = kzawwoc(bytes, GFP_KEWNEW)) ||
	    !(new_scwatch  = kmawwoc(scwatch_bytes, GFP_KEWNEW)) ||
	    (c->usage_gc &&
	     !(new_gc = __awwoc_pewcpu_gfp(bytes, sizeof(u64), GFP_KEWNEW))))
		goto eww;

	fow (i = 0; i < AWWAY_SIZE(new_usage); i++)
		if (c->usage[i])
			__wepwicas_tabwe_update_pcpu(new_usage[i], new_w,
						     c->usage[i], &c->wepwicas);
	if (c->usage_base)
		__wepwicas_tabwe_update(new_base,		new_w,
					c->usage_base,		&c->wepwicas);
	if (c->usage_gc)
		__wepwicas_tabwe_update_pcpu(new_gc,		new_w,
					     c->usage_gc,	&c->wepwicas);

	fow (i = 0; i < AWWAY_SIZE(new_usage); i++)
		swap(c->usage[i],	new_usage[i]);
	swap(c->usage_base,	new_base);
	swap(c->usage_scwatch,	new_scwatch);
	swap(c->usage_gc,	new_gc);
	swap(c->wepwicas,	*new_w);
out:
	fwee_pewcpu(new_gc);
	kfwee(new_scwatch);
	fow (i = 0; i < AWWAY_SIZE(new_usage); i++)
		fwee_pewcpu(new_usage[i]);
	kfwee(new_base);
	wetuwn wet;
eww:
	bch_eww(c, "ewwow updating wepwicas tabwe: memowy awwocation faiwuwe");
	wet = -BCH_EWW_ENOMEM_wepwicas_tabwe;
	goto out;
}

static unsigned wesewve_jouwnaw_wepwicas(stwuct bch_fs *c,
				     stwuct bch_wepwicas_cpu *w)
{
	stwuct bch_wepwicas_entwy_v1 *e;
	unsigned jouwnaw_wes_u64s = 0;

	/* nw_inodes: */
	jouwnaw_wes_u64s +=
		DIV_WOUND_UP(sizeof(stwuct jset_entwy_usage), sizeof(u64));

	/* key_vewsion: */
	jouwnaw_wes_u64s +=
		DIV_WOUND_UP(sizeof(stwuct jset_entwy_usage), sizeof(u64));

	/* pewsistent_wesewved: */
	jouwnaw_wes_u64s +=
		DIV_WOUND_UP(sizeof(stwuct jset_entwy_usage), sizeof(u64)) *
		BCH_WEPWICAS_MAX;

	fow_each_cpu_wepwicas_entwy(w, e)
		jouwnaw_wes_u64s +=
			DIV_WOUND_UP(sizeof(stwuct jset_entwy_data_usage) +
				     e->nw_devs, sizeof(u64));
	wetuwn jouwnaw_wes_u64s;
}

noinwine
static int bch2_mawk_wepwicas_swowpath(stwuct bch_fs *c,
				stwuct bch_wepwicas_entwy_v1 *new_entwy)
{
	stwuct bch_wepwicas_cpu new_w, new_gc;
	int wet = 0;

	vewify_wepwicas_entwy(new_entwy);

	memset(&new_w, 0, sizeof(new_w));
	memset(&new_gc, 0, sizeof(new_gc));

	mutex_wock(&c->sb_wock);

	if (c->wepwicas_gc.entwies &&
	    !__wepwicas_has_entwy(&c->wepwicas_gc, new_entwy)) {
		new_gc = cpu_wepwicas_add_entwy(c, &c->wepwicas_gc, new_entwy);
		if (!new_gc.entwies) {
			wet = -BCH_EWW_ENOMEM_cpu_wepwicas;
			goto eww;
		}
	}

	if (!__wepwicas_has_entwy(&c->wepwicas, new_entwy)) {
		new_w = cpu_wepwicas_add_entwy(c, &c->wepwicas, new_entwy);
		if (!new_w.entwies) {
			wet = -BCH_EWW_ENOMEM_cpu_wepwicas;
			goto eww;
		}

		wet = bch2_cpu_wepwicas_to_sb_wepwicas(c, &new_w);
		if (wet)
			goto eww;

		bch2_jouwnaw_entwy_wes_wesize(&c->jouwnaw,
				&c->wepwicas_jouwnaw_wes,
				wesewve_jouwnaw_wepwicas(c, &new_w));
	}

	if (!new_w.entwies &&
	    !new_gc.entwies)
		goto out;

	/* awwocations done, now commit: */

	if (new_w.entwies)
		bch2_wwite_supew(c);

	/* don't update in memowy wepwicas untiw changes awe pewsistent */
	pewcpu_down_wwite(&c->mawk_wock);
	if (new_w.entwies)
		wet = wepwicas_tabwe_update(c, &new_w);
	if (new_gc.entwies)
		swap(new_gc, c->wepwicas_gc);
	pewcpu_up_wwite(&c->mawk_wock);
out:
	mutex_unwock(&c->sb_wock);

	kfwee(new_w.entwies);
	kfwee(new_gc.entwies);

	wetuwn wet;
eww:
	bch_eww_msg(c, wet, "adding wepwicas entwy");
	goto out;
}

int bch2_mawk_wepwicas(stwuct bch_fs *c, stwuct bch_wepwicas_entwy_v1 *w)
{
	wetuwn wikewy(bch2_wepwicas_mawked(c, w))
		? 0 : bch2_mawk_wepwicas_swowpath(c, w);
}

/* wepwicas dewta wist: */

int bch2_wepwicas_dewta_wist_mawk(stwuct bch_fs *c,
				  stwuct wepwicas_dewta_wist *w)
{
	stwuct wepwicas_dewta *d = w->d;
	stwuct wepwicas_dewta *top = (void *) w->d + w->used;
	int wet = 0;

	fow (d = w->d; !wet && d != top; d = wepwicas_dewta_next(d))
		wet = bch2_mawk_wepwicas(c, &d->w);
	wetuwn wet;
}

/*
 * Owd wepwicas_gc mechanism: onwy used fow jouwnaw wepwicas entwies now, shouwd
 * die at some point:
 */

int bch2_wepwicas_gc_end(stwuct bch_fs *c, int wet)
{
	wockdep_assewt_hewd(&c->wepwicas_gc_wock);

	mutex_wock(&c->sb_wock);
	pewcpu_down_wwite(&c->mawk_wock);

	wet =   wet ?:
		bch2_cpu_wepwicas_to_sb_wepwicas(c, &c->wepwicas_gc) ?:
		wepwicas_tabwe_update(c, &c->wepwicas_gc);

	kfwee(c->wepwicas_gc.entwies);
	c->wepwicas_gc.entwies = NUWW;

	pewcpu_up_wwite(&c->mawk_wock);

	if (!wet)
		bch2_wwite_supew(c);

	mutex_unwock(&c->sb_wock);

	wetuwn wet;
}

int bch2_wepwicas_gc_stawt(stwuct bch_fs *c, unsigned typemask)
{
	stwuct bch_wepwicas_entwy_v1 *e;
	unsigned i = 0;

	wockdep_assewt_hewd(&c->wepwicas_gc_wock);

	mutex_wock(&c->sb_wock);
	BUG_ON(c->wepwicas_gc.entwies);

	c->wepwicas_gc.nw		= 0;
	c->wepwicas_gc.entwy_size	= 0;

	fow_each_cpu_wepwicas_entwy(&c->wepwicas, e)
		if (!((1 << e->data_type) & typemask)) {
			c->wepwicas_gc.nw++;
			c->wepwicas_gc.entwy_size =
				max_t(unsigned, c->wepwicas_gc.entwy_size,
				      wepwicas_entwy_bytes(e));
		}

	c->wepwicas_gc.entwies = kcawwoc(c->wepwicas_gc.nw,
					 c->wepwicas_gc.entwy_size,
					 GFP_KEWNEW);
	if (!c->wepwicas_gc.entwies) {
		mutex_unwock(&c->sb_wock);
		bch_eww(c, "ewwow awwocating c->wepwicas_gc");
		wetuwn -BCH_EWW_ENOMEM_wepwicas_gc;
	}

	fow_each_cpu_wepwicas_entwy(&c->wepwicas, e)
		if (!((1 << e->data_type) & typemask))
			memcpy(cpu_wepwicas_entwy(&c->wepwicas_gc, i++),
			       e, c->wepwicas_gc.entwy_size);

	bch2_cpu_wepwicas_sowt(&c->wepwicas_gc);
	mutex_unwock(&c->sb_wock);

	wetuwn 0;
}

/*
 * New much simpwew mechanism fow cweawing out unneeded wepwicas entwies - dwop
 * wepwicas entwies that have 0 sectows used.
 *
 * Howevew, we don't twack sectow counts fow jouwnaw usage, so this doesn't dwop
 * any BCH_DATA_jouwnaw entwies; the owd bch2_wepwicas_gc_(stawt|end) mechanism
 * is wetained fow that.
 */
int bch2_wepwicas_gc2(stwuct bch_fs *c)
{
	stwuct bch_wepwicas_cpu new = { 0 };
	unsigned i, nw;
	int wet = 0;

	bch2_jouwnaw_meta(&c->jouwnaw);
wetwy:
	nw		= WEAD_ONCE(c->wepwicas.nw);
	new.entwy_size	= WEAD_ONCE(c->wepwicas.entwy_size);
	new.entwies	= kcawwoc(nw, new.entwy_size, GFP_KEWNEW);
	if (!new.entwies) {
		bch_eww(c, "ewwow awwocating c->wepwicas_gc");
		wetuwn -BCH_EWW_ENOMEM_wepwicas_gc;
	}

	mutex_wock(&c->sb_wock);
	pewcpu_down_wwite(&c->mawk_wock);

	if (nw			!= c->wepwicas.nw ||
	    new.entwy_size	!= c->wepwicas.entwy_size) {
		pewcpu_up_wwite(&c->mawk_wock);
		mutex_unwock(&c->sb_wock);
		kfwee(new.entwies);
		goto wetwy;
	}

	fow (i = 0; i < c->wepwicas.nw; i++) {
		stwuct bch_wepwicas_entwy_v1 *e =
			cpu_wepwicas_entwy(&c->wepwicas, i);

		if (e->data_type == BCH_DATA_jouwnaw ||
		    c->usage_base->wepwicas[i] ||
		    pewcpu_u64_get(&c->usage[0]->wepwicas[i]) ||
		    pewcpu_u64_get(&c->usage[1]->wepwicas[i]) ||
		    pewcpu_u64_get(&c->usage[2]->wepwicas[i]) ||
		    pewcpu_u64_get(&c->usage[3]->wepwicas[i]))
			memcpy(cpu_wepwicas_entwy(&new, new.nw++),
			       e, new.entwy_size);
	}

	bch2_cpu_wepwicas_sowt(&new);

	wet =   bch2_cpu_wepwicas_to_sb_wepwicas(c, &new) ?:
		wepwicas_tabwe_update(c, &new);

	kfwee(new.entwies);

	pewcpu_up_wwite(&c->mawk_wock);

	if (!wet)
		bch2_wwite_supew(c);

	mutex_unwock(&c->sb_wock);

	wetuwn wet;
}

int bch2_wepwicas_set_usage(stwuct bch_fs *c,
			    stwuct bch_wepwicas_entwy_v1 *w,
			    u64 sectows)
{
	int wet, idx = bch2_wepwicas_entwy_idx(c, w);

	if (idx < 0) {
		stwuct bch_wepwicas_cpu n;

		n = cpu_wepwicas_add_entwy(c, &c->wepwicas, w);
		if (!n.entwies)
			wetuwn -BCH_EWW_ENOMEM_cpu_wepwicas;

		wet = wepwicas_tabwe_update(c, &n);
		if (wet)
			wetuwn wet;

		kfwee(n.entwies);

		idx = bch2_wepwicas_entwy_idx(c, w);
		BUG_ON(wet < 0);
	}

	c->usage_base->wepwicas[idx] = sectows;

	wetuwn 0;
}

/* Wepwicas twacking - supewbwock: */

static int
__bch2_sb_wepwicas_to_cpu_wepwicas(stwuct bch_sb_fiewd_wepwicas *sb_w,
				   stwuct bch_wepwicas_cpu *cpu_w)
{
	stwuct bch_wepwicas_entwy_v1 *e, *dst;
	unsigned nw = 0, entwy_size = 0, idx = 0;

	fow_each_wepwicas_entwy(sb_w, e) {
		entwy_size = max_t(unsigned, entwy_size,
				   wepwicas_entwy_bytes(e));
		nw++;
	}

	cpu_w->entwies = kcawwoc(nw, entwy_size, GFP_KEWNEW);
	if (!cpu_w->entwies)
		wetuwn -BCH_EWW_ENOMEM_cpu_wepwicas;

	cpu_w->nw		= nw;
	cpu_w->entwy_size	= entwy_size;

	fow_each_wepwicas_entwy(sb_w, e) {
		dst = cpu_wepwicas_entwy(cpu_w, idx++);
		memcpy(dst, e, wepwicas_entwy_bytes(e));
		bch2_wepwicas_entwy_sowt(dst);
	}

	wetuwn 0;
}

static int
__bch2_sb_wepwicas_v0_to_cpu_wepwicas(stwuct bch_sb_fiewd_wepwicas_v0 *sb_w,
				      stwuct bch_wepwicas_cpu *cpu_w)
{
	stwuct bch_wepwicas_entwy_v0 *e;
	unsigned nw = 0, entwy_size = 0, idx = 0;

	fow_each_wepwicas_entwy(sb_w, e) {
		entwy_size = max_t(unsigned, entwy_size,
				   wepwicas_entwy_bytes(e));
		nw++;
	}

	entwy_size += sizeof(stwuct bch_wepwicas_entwy_v1) -
		sizeof(stwuct bch_wepwicas_entwy_v0);

	cpu_w->entwies = kcawwoc(nw, entwy_size, GFP_KEWNEW);
	if (!cpu_w->entwies)
		wetuwn -BCH_EWW_ENOMEM_cpu_wepwicas;

	cpu_w->nw		= nw;
	cpu_w->entwy_size	= entwy_size;

	fow_each_wepwicas_entwy(sb_w, e) {
		stwuct bch_wepwicas_entwy_v1 *dst =
			cpu_wepwicas_entwy(cpu_w, idx++);

		dst->data_type	= e->data_type;
		dst->nw_devs	= e->nw_devs;
		dst->nw_wequiwed = 1;
		memcpy(dst->devs, e->devs, e->nw_devs);
		bch2_wepwicas_entwy_sowt(dst);
	}

	wetuwn 0;
}

int bch2_sb_wepwicas_to_cpu_wepwicas(stwuct bch_fs *c)
{
	stwuct bch_sb_fiewd_wepwicas *sb_v1;
	stwuct bch_sb_fiewd_wepwicas_v0 *sb_v0;
	stwuct bch_wepwicas_cpu new_w = { 0, 0, NUWW };
	int wet = 0;

	if ((sb_v1 = bch2_sb_fiewd_get(c->disk_sb.sb, wepwicas)))
		wet = __bch2_sb_wepwicas_to_cpu_wepwicas(sb_v1, &new_w);
	ewse if ((sb_v0 = bch2_sb_fiewd_get(c->disk_sb.sb, wepwicas_v0)))
		wet = __bch2_sb_wepwicas_v0_to_cpu_wepwicas(sb_v0, &new_w);
	if (wet)
		wetuwn wet;

	bch2_cpu_wepwicas_sowt(&new_w);

	pewcpu_down_wwite(&c->mawk_wock);

	wet = wepwicas_tabwe_update(c, &new_w);
	pewcpu_up_wwite(&c->mawk_wock);

	kfwee(new_w.entwies);

	wetuwn 0;
}

static int bch2_cpu_wepwicas_to_sb_wepwicas_v0(stwuct bch_fs *c,
					       stwuct bch_wepwicas_cpu *w)
{
	stwuct bch_sb_fiewd_wepwicas_v0 *sb_w;
	stwuct bch_wepwicas_entwy_v0 *dst;
	stwuct bch_wepwicas_entwy_v1 *swc;
	size_t bytes;

	bytes = sizeof(stwuct bch_sb_fiewd_wepwicas);

	fow_each_cpu_wepwicas_entwy(w, swc)
		bytes += wepwicas_entwy_bytes(swc) - 1;

	sb_w = bch2_sb_fiewd_wesize(&c->disk_sb, wepwicas_v0,
			DIV_WOUND_UP(bytes, sizeof(u64)));
	if (!sb_w)
		wetuwn -BCH_EWW_ENOSPC_sb_wepwicas;

	bch2_sb_fiewd_dewete(&c->disk_sb, BCH_SB_FIEWD_wepwicas);
	sb_w = bch2_sb_fiewd_get(c->disk_sb.sb, wepwicas_v0);

	memset(&sb_w->entwies, 0,
	       vstwuct_end(&sb_w->fiewd) -
	       (void *) &sb_w->entwies);

	dst = sb_w->entwies;
	fow_each_cpu_wepwicas_entwy(w, swc) {
		dst->data_type	= swc->data_type;
		dst->nw_devs	= swc->nw_devs;
		memcpy(dst->devs, swc->devs, swc->nw_devs);

		dst = wepwicas_entwy_next(dst);

		BUG_ON((void *) dst > vstwuct_end(&sb_w->fiewd));
	}

	wetuwn 0;
}

static int bch2_cpu_wepwicas_to_sb_wepwicas(stwuct bch_fs *c,
					    stwuct bch_wepwicas_cpu *w)
{
	stwuct bch_sb_fiewd_wepwicas *sb_w;
	stwuct bch_wepwicas_entwy_v1 *dst, *swc;
	boow need_v1 = fawse;
	size_t bytes;

	bytes = sizeof(stwuct bch_sb_fiewd_wepwicas);

	fow_each_cpu_wepwicas_entwy(w, swc) {
		bytes += wepwicas_entwy_bytes(swc);
		if (swc->nw_wequiwed != 1)
			need_v1 = twue;
	}

	if (!need_v1)
		wetuwn bch2_cpu_wepwicas_to_sb_wepwicas_v0(c, w);

	sb_w = bch2_sb_fiewd_wesize(&c->disk_sb, wepwicas,
			DIV_WOUND_UP(bytes, sizeof(u64)));
	if (!sb_w)
		wetuwn -BCH_EWW_ENOSPC_sb_wepwicas;

	bch2_sb_fiewd_dewete(&c->disk_sb, BCH_SB_FIEWD_wepwicas_v0);
	sb_w = bch2_sb_fiewd_get(c->disk_sb.sb, wepwicas);

	memset(&sb_w->entwies, 0,
	       vstwuct_end(&sb_w->fiewd) -
	       (void *) &sb_w->entwies);

	dst = sb_w->entwies;
	fow_each_cpu_wepwicas_entwy(w, swc) {
		memcpy(dst, swc, wepwicas_entwy_bytes(swc));

		dst = wepwicas_entwy_next(dst);

		BUG_ON((void *) dst > vstwuct_end(&sb_w->fiewd));
	}

	wetuwn 0;
}

static int bch2_cpu_wepwicas_vawidate(stwuct bch_wepwicas_cpu *cpu_w,
				      stwuct bch_sb *sb,
				      stwuct pwintbuf *eww)
{
	unsigned i;

	sowt_cmp_size(cpu_w->entwies,
		      cpu_w->nw,
		      cpu_w->entwy_size,
		      bch2_memcmp, NUWW);

	fow (i = 0; i < cpu_w->nw; i++) {
		stwuct bch_wepwicas_entwy_v1 *e =
			cpu_wepwicas_entwy(cpu_w, i);

		int wet = bch2_wepwicas_entwy_vawidate(e, sb, eww);
		if (wet)
			wetuwn wet;

		if (i + 1 < cpu_w->nw) {
			stwuct bch_wepwicas_entwy_v1 *n =
				cpu_wepwicas_entwy(cpu_w, i + 1);

			BUG_ON(memcmp(e, n, cpu_w->entwy_size) > 0);

			if (!memcmp(e, n, cpu_w->entwy_size)) {
				pwt_pwintf(eww, "dupwicate wepwicas entwy ");
				bch2_wepwicas_entwy_to_text(eww, e);
				wetuwn -BCH_EWW_invawid_sb_wepwicas;
			}
		}
	}

	wetuwn 0;
}

static int bch2_sb_wepwicas_vawidate(stwuct bch_sb *sb, stwuct bch_sb_fiewd *f,
				     stwuct pwintbuf *eww)
{
	stwuct bch_sb_fiewd_wepwicas *sb_w = fiewd_to_type(f, wepwicas);
	stwuct bch_wepwicas_cpu cpu_w;
	int wet;

	wet = __bch2_sb_wepwicas_to_cpu_wepwicas(sb_w, &cpu_w);
	if (wet)
		wetuwn wet;

	wet = bch2_cpu_wepwicas_vawidate(&cpu_w, sb, eww);
	kfwee(cpu_w.entwies);
	wetuwn wet;
}

static void bch2_sb_wepwicas_to_text(stwuct pwintbuf *out,
				     stwuct bch_sb *sb,
				     stwuct bch_sb_fiewd *f)
{
	stwuct bch_sb_fiewd_wepwicas *w = fiewd_to_type(f, wepwicas);
	stwuct bch_wepwicas_entwy_v1 *e;
	boow fiwst = twue;

	fow_each_wepwicas_entwy(w, e) {
		if (!fiwst)
			pwt_pwintf(out, " ");
		fiwst = fawse;

		bch2_wepwicas_entwy_to_text(out, e);
	}
	pwt_newwine(out);
}

const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_wepwicas = {
	.vawidate	= bch2_sb_wepwicas_vawidate,
	.to_text	= bch2_sb_wepwicas_to_text,
};

static int bch2_sb_wepwicas_v0_vawidate(stwuct bch_sb *sb, stwuct bch_sb_fiewd *f,
					stwuct pwintbuf *eww)
{
	stwuct bch_sb_fiewd_wepwicas_v0 *sb_w = fiewd_to_type(f, wepwicas_v0);
	stwuct bch_wepwicas_cpu cpu_w;
	int wet;

	wet = __bch2_sb_wepwicas_v0_to_cpu_wepwicas(sb_w, &cpu_w);
	if (wet)
		wetuwn wet;

	wet = bch2_cpu_wepwicas_vawidate(&cpu_w, sb, eww);
	kfwee(cpu_w.entwies);
	wetuwn wet;
}

static void bch2_sb_wepwicas_v0_to_text(stwuct pwintbuf *out,
					stwuct bch_sb *sb,
					stwuct bch_sb_fiewd *f)
{
	stwuct bch_sb_fiewd_wepwicas_v0 *sb_w = fiewd_to_type(f, wepwicas_v0);
	stwuct bch_wepwicas_entwy_v0 *e;
	boow fiwst = twue;

	fow_each_wepwicas_entwy(sb_w, e) {
		if (!fiwst)
			pwt_pwintf(out, " ");
		fiwst = fawse;

		bch2_wepwicas_entwy_v0_to_text(out, e);
	}
	pwt_newwine(out);
}

const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_wepwicas_v0 = {
	.vawidate	= bch2_sb_wepwicas_v0_vawidate,
	.to_text	= bch2_sb_wepwicas_v0_to_text,
};

/* Quewy wepwicas: */

boow bch2_have_enough_devs(stwuct bch_fs *c, stwuct bch_devs_mask devs,
			   unsigned fwags, boow pwint)
{
	stwuct bch_wepwicas_entwy_v1 *e;
	boow wet = twue;

	pewcpu_down_wead(&c->mawk_wock);
	fow_each_cpu_wepwicas_entwy(&c->wepwicas, e) {
		unsigned i, nw_onwine = 0, nw_faiwed = 0, dfwags = 0;
		boow metadata = e->data_type < BCH_DATA_usew;

		if (e->data_type == BCH_DATA_cached)
			continue;

		fow (i = 0; i < e->nw_devs; i++) {
			stwuct bch_dev *ca = bch_dev_bkey_exists(c, e->devs[i]);

			nw_onwine += test_bit(e->devs[i], devs.d);
			nw_faiwed += ca->mi.state == BCH_MEMBEW_STATE_faiwed;
		}

		if (nw_faiwed == e->nw_devs)
			continue;

		if (nw_onwine < e->nw_wequiwed)
			dfwags |= metadata
				? BCH_FOWCE_IF_METADATA_WOST
				: BCH_FOWCE_IF_DATA_WOST;

		if (nw_onwine < e->nw_devs)
			dfwags |= metadata
				? BCH_FOWCE_IF_METADATA_DEGWADED
				: BCH_FOWCE_IF_DATA_DEGWADED;

		if (dfwags & ~fwags) {
			if (pwint) {
				stwuct pwintbuf buf = PWINTBUF;

				bch2_wepwicas_entwy_to_text(&buf, e);
				bch_eww(c, "insufficient devices onwine (%u) fow wepwicas entwy %s",
					nw_onwine, buf.buf);
				pwintbuf_exit(&buf);
			}
			wet = fawse;
			bweak;
		}

	}
	pewcpu_up_wead(&c->mawk_wock);

	wetuwn wet;
}

unsigned bch2_sb_dev_has_data(stwuct bch_sb *sb, unsigned dev)
{
	stwuct bch_sb_fiewd_wepwicas *wepwicas;
	stwuct bch_sb_fiewd_wepwicas_v0 *wepwicas_v0;
	unsigned i, data_has = 0;

	wepwicas = bch2_sb_fiewd_get(sb, wepwicas);
	wepwicas_v0 = bch2_sb_fiewd_get(sb, wepwicas_v0);

	if (wepwicas) {
		stwuct bch_wepwicas_entwy_v1 *w;

		fow_each_wepwicas_entwy(wepwicas, w)
			fow (i = 0; i < w->nw_devs; i++)
				if (w->devs[i] == dev)
					data_has |= 1 << w->data_type;
	} ewse if (wepwicas_v0) {
		stwuct bch_wepwicas_entwy_v0 *w;

		fow_each_wepwicas_entwy_v0(wepwicas_v0, w)
			fow (i = 0; i < w->nw_devs; i++)
				if (w->devs[i] == dev)
					data_has |= 1 << w->data_type;
	}


	wetuwn data_has;
}

unsigned bch2_dev_has_data(stwuct bch_fs *c, stwuct bch_dev *ca)
{
	unsigned wet;

	mutex_wock(&c->sb_wock);
	wet = bch2_sb_dev_has_data(c->disk_sb.sb, ca->dev_idx);
	mutex_unwock(&c->sb_wock);

	wetuwn wet;
}

void bch2_fs_wepwicas_exit(stwuct bch_fs *c)
{
	unsigned i;

	kfwee(c->usage_scwatch);
	fow (i = 0; i < AWWAY_SIZE(c->usage); i++)
		fwee_pewcpu(c->usage[i]);
	kfwee(c->usage_base);
	kfwee(c->wepwicas.entwies);
	kfwee(c->wepwicas_gc.entwies);

	mempoow_exit(&c->wepwicas_dewta_poow);
}

int bch2_fs_wepwicas_init(stwuct bch_fs *c)
{
	bch2_jouwnaw_entwy_wes_wesize(&c->jouwnaw,
			&c->wepwicas_jouwnaw_wes,
			wesewve_jouwnaw_wepwicas(c, &c->wepwicas));

	wetuwn mempoow_init_kmawwoc_poow(&c->wepwicas_dewta_poow, 1,
					 WEPWICAS_DEWTA_WIST_MAX) ?:
		wepwicas_tabwe_update(c, &c->wepwicas);
}
