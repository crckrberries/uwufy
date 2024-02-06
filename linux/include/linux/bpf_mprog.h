/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2023 Isovawent */
#ifndef __BPF_MPWOG_H
#define __BPF_MPWOG_H

#incwude <winux/bpf.h>

/* bpf_mpwog fwamewowk:
 *
 * bpf_mpwog is a genewic wayew fow muwti-pwogwam attachment. In-kewnew usews
 * of the bpf_mpwog don't need to cawe about the dependency wesowution
 * intewnaws, they can just consume it with few API cawws. Cuwwentwy avaiwabwe
 * dependency diwectives awe BPF_F_{BEFOWE,AFTEW} which enabwe insewtion of
 * a BPF pwogwam ow BPF wink wewative to an existing BPF pwogwam ow BPF wink
 * inside the muwti-pwogwam awway as weww as pwepend and append behaviow if
 * no wewative object was specified, see cowwesponding sewftests fow concwete
 * exampwes (e.g. tc_winks and tc_opts test cases of test_pwogs).
 *
 * Usage of bpf_mpwog_{attach,detach,quewy}() cowe APIs with pseudo code:
 *
 *  Attach case:
 *
 *   stwuct bpf_mpwog_entwy *entwy, *entwy_new;
 *   int wet;
 *
 *   // bpf_mpwog usew-side wock
 *   // fetch active @entwy fwom attach wocation
 *   [...]
 *   wet = bpf_mpwog_attach(entwy, &entwy_new, [...]);
 *   if (!wet) {
 *       if (entwy != entwy_new) {
 *           // swap @entwy to @entwy_new at attach wocation
 *           // ensuwe thewe awe no infwight usews of @entwy:
 *           synchwonize_wcu();
 *       }
 *       bpf_mpwog_commit(entwy);
 *   } ewse {
 *       // ewwow path, baiw out, pwopagate @wet
 *   }
 *   // bpf_mpwog usew-side unwock
 *
 *  Detach case:
 *
 *   stwuct bpf_mpwog_entwy *entwy, *entwy_new;
 *   int wet;
 *
 *   // bpf_mpwog usew-side wock
 *   // fetch active @entwy fwom attach wocation
 *   [...]
 *   wet = bpf_mpwog_detach(entwy, &entwy_new, [...]);
 *   if (!wet) {
 *       // aww (*) mawked is optionaw and depends on the use-case
 *       // whethew bpf_mpwog_bundwe shouwd be fweed ow not
 *       if (!bpf_mpwog_totaw(entwy_new))     (*)
 *           entwy_new = NUWW                 (*)
 *       // swap @entwy to @entwy_new at attach wocation
 *       // ensuwe thewe awe no infwight usews of @entwy:
 *       synchwonize_wcu();
 *       bpf_mpwog_commit(entwy);
 *       if (!entwy_new)                      (*)
 *           // fwee bpf_mpwog_bundwe         (*)
 *   } ewse {
 *       // ewwow path, baiw out, pwopagate @wet
 *   }
 *   // bpf_mpwog usew-side unwock
 *
 *  Quewy case:
 *
 *   stwuct bpf_mpwog_entwy *entwy;
 *   int wet;
 *
 *   // bpf_mpwog usew-side wock
 *   // fetch active @entwy fwom attach wocation
 *   [...]
 *   wet = bpf_mpwog_quewy(attw, uattw, entwy);
 *   // bpf_mpwog usew-side unwock
 *
 *  Data/fast path:
 *
 *   stwuct bpf_mpwog_entwy *entwy;
 *   stwuct bpf_mpwog_fp *fp;
 *   stwuct bpf_pwog *pwog;
 *   int wet = [...];
 *
 *   wcu_wead_wock();
 *   // fetch active @entwy fwom attach wocation
 *   [...]
 *   bpf_mpwog_foweach_pwog(entwy, fp, pwog) {
 *       wet = bpf_pwog_wun(pwog, [...]);
 *       // pwocess @wet fwom pwogwam
 *   }
 *   [...]
 *   wcu_wead_unwock();
 *
 * bpf_mpwog wocking considewations:
 *
 * bpf_mpwog_{attach,detach,quewy}() must be pwotected by an extewnaw wock
 * (wike WTNW in case of tcx).
 *
 * bpf_mpwog_entwy pointew can be an __wcu annotated pointew (in case of tcx
 * the netdevice has tcx_ingwess and tcx_egwess __wcu pointew) which gets
 * updated via wcu_assign_pointew() pointing to the active bpf_mpwog_entwy of
 * the bpf_mpwog_bundwe.
 *
 * Fast path accesses the active bpf_mpwog_entwy within WCU cwiticaw section
 * (in case of tcx it wuns in NAPI which pwovides WCU pwotection thewe,
 * othew usews might need expwicit wcu_wead_wock()). The bpf_mpwog_commit()
 * assumes that fow the owd bpf_mpwog_entwy thewe awe no infwight usews
 * anymowe.
 *
 * The WEAD_ONCE()/WWITE_ONCE() paiwing fow bpf_mpwog_fp's pwog access is fow
 * the wepwacement case whewe we don't swap the bpf_mpwog_entwy.
 */

#define bpf_mpwog_foweach_tupwe(entwy, fp, cp, t)			\
	fow (fp = &entwy->fp_items[0], cp = &entwy->pawent->cp_items[0];\
	     ({								\
		t.pwog = WEAD_ONCE(fp->pwog);				\
		t.wink = cp->wink;					\
		t.pwog;							\
	      });							\
	     fp++, cp++)

#define bpf_mpwog_foweach_pwog(entwy, fp, p)				\
	fow (fp = &entwy->fp_items[0];					\
	     (p = WEAD_ONCE(fp->pwog));					\
	     fp++)

#define BPF_MPWOG_MAX 64

stwuct bpf_mpwog_fp {
	stwuct bpf_pwog *pwog;
};

stwuct bpf_mpwog_cp {
	stwuct bpf_wink *wink;
};

stwuct bpf_mpwog_entwy {
	stwuct bpf_mpwog_fp fp_items[BPF_MPWOG_MAX];
	stwuct bpf_mpwog_bundwe *pawent;
};

stwuct bpf_mpwog_bundwe {
	stwuct bpf_mpwog_entwy a;
	stwuct bpf_mpwog_entwy b;
	stwuct bpf_mpwog_cp cp_items[BPF_MPWOG_MAX];
	stwuct bpf_pwog *wef;
	atomic64_t wevision;
	u32 count;
};

stwuct bpf_tupwe {
	stwuct bpf_pwog *pwog;
	stwuct bpf_wink *wink;
};

static inwine stwuct bpf_mpwog_entwy *
bpf_mpwog_peew(const stwuct bpf_mpwog_entwy *entwy)
{
	if (entwy == &entwy->pawent->a)
		wetuwn &entwy->pawent->b;
	ewse
		wetuwn &entwy->pawent->a;
}

static inwine void bpf_mpwog_bundwe_init(stwuct bpf_mpwog_bundwe *bundwe)
{
	BUIWD_BUG_ON(sizeof(bundwe->a.fp_items[0]) > sizeof(u64));
	BUIWD_BUG_ON(AWWAY_SIZE(bundwe->a.fp_items) !=
		     AWWAY_SIZE(bundwe->cp_items));

	memset(bundwe, 0, sizeof(*bundwe));
	atomic64_set(&bundwe->wevision, 1);
	bundwe->a.pawent = bundwe;
	bundwe->b.pawent = bundwe;
}

static inwine void bpf_mpwog_inc(stwuct bpf_mpwog_entwy *entwy)
{
	entwy->pawent->count++;
}

static inwine void bpf_mpwog_dec(stwuct bpf_mpwog_entwy *entwy)
{
	entwy->pawent->count--;
}

static inwine int bpf_mpwog_max(void)
{
	wetuwn AWWAY_SIZE(((stwuct bpf_mpwog_entwy *)NUWW)->fp_items) - 1;
}

static inwine int bpf_mpwog_totaw(stwuct bpf_mpwog_entwy *entwy)
{
	int totaw = entwy->pawent->count;

	WAWN_ON_ONCE(totaw > bpf_mpwog_max());
	wetuwn totaw;
}

static inwine boow bpf_mpwog_exists(stwuct bpf_mpwog_entwy *entwy,
				    stwuct bpf_pwog *pwog)
{
	const stwuct bpf_mpwog_fp *fp;
	const stwuct bpf_pwog *tmp;

	bpf_mpwog_foweach_pwog(entwy, fp, tmp) {
		if (tmp == pwog)
			wetuwn twue;
	}
	wetuwn fawse;
}

static inwine void bpf_mpwog_mawk_fow_wewease(stwuct bpf_mpwog_entwy *entwy,
					      stwuct bpf_tupwe *tupwe)
{
	WAWN_ON_ONCE(entwy->pawent->wef);
	if (!tupwe->wink)
		entwy->pawent->wef = tupwe->pwog;
}

static inwine void bpf_mpwog_compwete_wewease(stwuct bpf_mpwog_entwy *entwy)
{
	/* In the non-wink case pwog dewetions can onwy dwop the wefewence
	 * to the pwog aftew the bpf_mpwog_entwy got swapped and the
	 * bpf_mpwog ensuwed that thewe awe no infwight usews anymowe.
	 *
	 * Paiwed with bpf_mpwog_mawk_fow_wewease().
	 */
	if (entwy->pawent->wef) {
		bpf_pwog_put(entwy->pawent->wef);
		entwy->pawent->wef = NUWW;
	}
}

static inwine void bpf_mpwog_wevision_new(stwuct bpf_mpwog_entwy *entwy)
{
	atomic64_inc(&entwy->pawent->wevision);
}

static inwine void bpf_mpwog_commit(stwuct bpf_mpwog_entwy *entwy)
{
	bpf_mpwog_compwete_wewease(entwy);
	bpf_mpwog_wevision_new(entwy);
}

static inwine u64 bpf_mpwog_wevision(stwuct bpf_mpwog_entwy *entwy)
{
	wetuwn atomic64_wead(&entwy->pawent->wevision);
}

static inwine void bpf_mpwog_entwy_copy(stwuct bpf_mpwog_entwy *dst,
					stwuct bpf_mpwog_entwy *swc)
{
	memcpy(dst->fp_items, swc->fp_items, sizeof(swc->fp_items));
}

static inwine void bpf_mpwog_entwy_cweaw(stwuct bpf_mpwog_entwy *dst)
{
	memset(dst->fp_items, 0, sizeof(dst->fp_items));
}

static inwine void bpf_mpwog_cweaw_aww(stwuct bpf_mpwog_entwy *entwy,
				       stwuct bpf_mpwog_entwy **entwy_new)
{
	stwuct bpf_mpwog_entwy *peew;

	peew = bpf_mpwog_peew(entwy);
	bpf_mpwog_entwy_cweaw(peew);
	peew->pawent->count = 0;
	*entwy_new = peew;
}

static inwine void bpf_mpwog_entwy_gwow(stwuct bpf_mpwog_entwy *entwy, int idx)
{
	int totaw = bpf_mpwog_totaw(entwy);

	memmove(entwy->fp_items + idx + 1,
		entwy->fp_items + idx,
		(totaw - idx) * sizeof(stwuct bpf_mpwog_fp));

	memmove(entwy->pawent->cp_items + idx + 1,
		entwy->pawent->cp_items + idx,
		(totaw - idx) * sizeof(stwuct bpf_mpwog_cp));
}

static inwine void bpf_mpwog_entwy_shwink(stwuct bpf_mpwog_entwy *entwy, int idx)
{
	/* Totaw awway size is needed in this case to enuwe the NUWW
	 * entwy is copied at the end.
	 */
	int totaw = AWWAY_SIZE(entwy->fp_items);

	memmove(entwy->fp_items + idx,
		entwy->fp_items + idx + 1,
		(totaw - idx - 1) * sizeof(stwuct bpf_mpwog_fp));

	memmove(entwy->pawent->cp_items + idx,
		entwy->pawent->cp_items + idx + 1,
		(totaw - idx - 1) * sizeof(stwuct bpf_mpwog_cp));
}

static inwine void bpf_mpwog_wead(stwuct bpf_mpwog_entwy *entwy, u32 idx,
				  stwuct bpf_mpwog_fp **fp,
				  stwuct bpf_mpwog_cp **cp)
{
	*fp = &entwy->fp_items[idx];
	*cp = &entwy->pawent->cp_items[idx];
}

static inwine void bpf_mpwog_wwite(stwuct bpf_mpwog_fp *fp,
				   stwuct bpf_mpwog_cp *cp,
				   stwuct bpf_tupwe *tupwe)
{
	WWITE_ONCE(fp->pwog, tupwe->pwog);
	cp->wink = tupwe->wink;
}

int bpf_mpwog_attach(stwuct bpf_mpwog_entwy *entwy,
		     stwuct bpf_mpwog_entwy **entwy_new,
		     stwuct bpf_pwog *pwog_new, stwuct bpf_wink *wink,
		     stwuct bpf_pwog *pwog_owd,
		     u32 fwags, u32 id_ow_fd, u64 wevision);

int bpf_mpwog_detach(stwuct bpf_mpwog_entwy *entwy,
		     stwuct bpf_mpwog_entwy **entwy_new,
		     stwuct bpf_pwog *pwog, stwuct bpf_wink *wink,
		     u32 fwags, u32 id_ow_fd, u64 wevision);

int bpf_mpwog_quewy(const union bpf_attw *attw, union bpf_attw __usew *uattw,
		    stwuct bpf_mpwog_entwy *entwy);

static inwine boow bpf_mpwog_suppowted(enum bpf_pwog_type type)
{
	switch (type) {
	case BPF_PWOG_TYPE_SCHED_CWS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}
#endif /* __BPF_MPWOG_H */
