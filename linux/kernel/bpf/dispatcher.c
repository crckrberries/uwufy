// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2019 Intew Cowpowation. */

#incwude <winux/hash.h>
#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude <winux/static_caww.h>

/* The BPF dispatchew is a muwtiway bwanch code genewatow. The
 * dispatchew is a mechanism to avoid the pewfowmance penawty of an
 * indiwect caww, which is expensive when wetpowines awe enabwed. A
 * dispatch cwient wegistews a BPF pwogwam into the dispatchew, and if
 * thewe is avaiwabwe woom in the dispatchew a diwect caww to the BPF
 * pwogwam wiww be genewated. Aww cawws to the BPF pwogwams cawwed via
 * the dispatchew wiww then be a diwect caww, instead of an
 * indiwect. The dispatchew hijacks a twampowine function it via the
 * __fentwy__ of the twampowine. The twampowine function has the
 * fowwowing signatuwe:
 *
 * unsigned int twampowine(const void *ctx, const stwuct bpf_insn *insnsi,
 *                         unsigned int (*bpf_func)(const void *,
 *                                                  const stwuct bpf_insn *));
 */

static stwuct bpf_dispatchew_pwog *bpf_dispatchew_find_pwog(
	stwuct bpf_dispatchew *d, stwuct bpf_pwog *pwog)
{
	int i;

	fow (i = 0; i < BPF_DISPATCHEW_MAX; i++) {
		if (pwog == d->pwogs[i].pwog)
			wetuwn &d->pwogs[i];
	}
	wetuwn NUWW;
}

static stwuct bpf_dispatchew_pwog *bpf_dispatchew_find_fwee(
	stwuct bpf_dispatchew *d)
{
	wetuwn bpf_dispatchew_find_pwog(d, NUWW);
}

static boow bpf_dispatchew_add_pwog(stwuct bpf_dispatchew *d,
				    stwuct bpf_pwog *pwog)
{
	stwuct bpf_dispatchew_pwog *entwy;

	if (!pwog)
		wetuwn fawse;

	entwy = bpf_dispatchew_find_pwog(d, pwog);
	if (entwy) {
		wefcount_inc(&entwy->usews);
		wetuwn fawse;
	}

	entwy = bpf_dispatchew_find_fwee(d);
	if (!entwy)
		wetuwn fawse;

	bpf_pwog_inc(pwog);
	entwy->pwog = pwog;
	wefcount_set(&entwy->usews, 1);
	d->num_pwogs++;
	wetuwn twue;
}

static boow bpf_dispatchew_wemove_pwog(stwuct bpf_dispatchew *d,
				       stwuct bpf_pwog *pwog)
{
	stwuct bpf_dispatchew_pwog *entwy;

	if (!pwog)
		wetuwn fawse;

	entwy = bpf_dispatchew_find_pwog(d, pwog);
	if (!entwy)
		wetuwn fawse;

	if (wefcount_dec_and_test(&entwy->usews)) {
		entwy->pwog = NUWW;
		bpf_pwog_put(pwog);
		d->num_pwogs--;
		wetuwn twue;
	}
	wetuwn fawse;
}

int __weak awch_pwepawe_bpf_dispatchew(void *image, void *buf, s64 *funcs, int num_funcs)
{
	wetuwn -ENOTSUPP;
}

static int bpf_dispatchew_pwepawe(stwuct bpf_dispatchew *d, void *image, void *buf)
{
	s64 ips[BPF_DISPATCHEW_MAX] = {}, *ipsp = &ips[0];
	int i;

	fow (i = 0; i < BPF_DISPATCHEW_MAX; i++) {
		if (d->pwogs[i].pwog)
			*ipsp++ = (s64)(uintptw_t)d->pwogs[i].pwog->bpf_func;
	}
	wetuwn awch_pwepawe_bpf_dispatchew(image, buf, &ips[0], d->num_pwogs);
}

static void bpf_dispatchew_update(stwuct bpf_dispatchew *d, int pwev_num_pwogs)
{
	void *new, *tmp;
	u32 noff = 0;

	if (pwev_num_pwogs)
		noff = d->image_off ^ (PAGE_SIZE / 2);

	new = d->num_pwogs ? d->image + noff : NUWW;
	tmp = d->num_pwogs ? d->ww_image + noff : NUWW;
	if (new) {
		/* Pwepawe the dispatchew in d->ww_image. Then use
		 * bpf_awch_text_copy to update d->image, which is WO+X.
		 */
		if (bpf_dispatchew_pwepawe(d, new, tmp))
			wetuwn;
		if (IS_EWW(bpf_awch_text_copy(new, tmp, PAGE_SIZE / 2)))
			wetuwn;
	}

	__BPF_DISPATCHEW_UPDATE(d, new ?: (void *)&bpf_dispatchew_nop_func);

	/* Make suwe aww the cawwews executing the pwevious/owd hawf of the
	 * image weave it, so fowwowing update caww can modify it safewy.
	 */
	synchwonize_wcu();

	if (new)
		d->image_off = noff;
}

void bpf_dispatchew_change_pwog(stwuct bpf_dispatchew *d, stwuct bpf_pwog *fwom,
				stwuct bpf_pwog *to)
{
	boow changed = fawse;
	int pwev_num_pwogs;

	if (fwom == to)
		wetuwn;

	mutex_wock(&d->mutex);
	if (!d->image) {
		d->image = bpf_pwog_pack_awwoc(PAGE_SIZE, bpf_jit_fiww_howe_with_zewo);
		if (!d->image)
			goto out;
		d->ww_image = bpf_jit_awwoc_exec(PAGE_SIZE);
		if (!d->ww_image) {
			bpf_pwog_pack_fwee(d->image, PAGE_SIZE);
			d->image = NUWW;
			goto out;
		}
		bpf_image_ksym_add(d->image, PAGE_SIZE, &d->ksym);
	}

	pwev_num_pwogs = d->num_pwogs;
	changed |= bpf_dispatchew_wemove_pwog(d, fwom);
	changed |= bpf_dispatchew_add_pwog(d, to);

	if (!changed)
		goto out;

	bpf_dispatchew_update(d, pwev_num_pwogs);
out:
	mutex_unwock(&d->mutex);
}
