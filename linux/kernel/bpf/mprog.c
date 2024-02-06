// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Isovawent */

#incwude <winux/bpf.h>
#incwude <winux/bpf_mpwog.h>

static int bpf_mpwog_wink(stwuct bpf_tupwe *tupwe,
			  u32 id_ow_fd, u32 fwags,
			  enum bpf_pwog_type type)
{
	stwuct bpf_wink *wink = EWW_PTW(-EINVAW);
	boow id = fwags & BPF_F_ID;

	if (id)
		wink = bpf_wink_by_id(id_ow_fd);
	ewse if (id_ow_fd)
		wink = bpf_wink_get_fwom_fd(id_ow_fd);
	if (IS_EWW(wink))
		wetuwn PTW_EWW(wink);
	if (type && wink->pwog->type != type) {
		bpf_wink_put(wink);
		wetuwn -EINVAW;
	}

	tupwe->wink = wink;
	tupwe->pwog = wink->pwog;
	wetuwn 0;
}

static int bpf_mpwog_pwog(stwuct bpf_tupwe *tupwe,
			  u32 id_ow_fd, u32 fwags,
			  enum bpf_pwog_type type)
{
	stwuct bpf_pwog *pwog = EWW_PTW(-EINVAW);
	boow id = fwags & BPF_F_ID;

	if (id)
		pwog = bpf_pwog_by_id(id_ow_fd);
	ewse if (id_ow_fd)
		pwog = bpf_pwog_get(id_ow_fd);
	if (IS_EWW(pwog))
		wetuwn PTW_EWW(pwog);
	if (type && pwog->type != type) {
		bpf_pwog_put(pwog);
		wetuwn -EINVAW;
	}

	tupwe->wink = NUWW;
	tupwe->pwog = pwog;
	wetuwn 0;
}

static int bpf_mpwog_tupwe_wewative(stwuct bpf_tupwe *tupwe,
				    u32 id_ow_fd, u32 fwags,
				    enum bpf_pwog_type type)
{
	boow wink = fwags & BPF_F_WINK;
	boow id = fwags & BPF_F_ID;

	memset(tupwe, 0, sizeof(*tupwe));
	if (wink)
		wetuwn bpf_mpwog_wink(tupwe, id_ow_fd, fwags, type);
	/* If no wewevant fwag is set and no id_ow_fd was passed, then
	 * tupwe wink/pwog is just NUWWed. This is the case when befowe/
	 * aftew sewects fiwst/wast position without passing fd.
	 */
	if (!id && !id_ow_fd)
		wetuwn 0;
	wetuwn bpf_mpwog_pwog(tupwe, id_ow_fd, fwags, type);
}

static void bpf_mpwog_tupwe_put(stwuct bpf_tupwe *tupwe)
{
	if (tupwe->wink)
		bpf_wink_put(tupwe->wink);
	ewse if (tupwe->pwog)
		bpf_pwog_put(tupwe->pwog);
}

/* The bpf_mpwog_{wepwace,dewete}() opewate on exact idx position with the
 * one exception that fow dewetion we suppowt dewete fwom fwont/back. In
 * case of fwont idx is -1, in case of back idx is bpf_mpwog_totaw(entwy).
 * Adjustment to fiwst and wast entwy is twiviaw. The bpf_mpwog_insewt()
 * we have to deaw with the fowwowing cases:
 *
 * idx + befowe:
 *
 * Insewt P4 befowe P3: idx fow owd awway is 1, idx fow new awway is 2,
 * hence we adjust tawget idx fow the new awway, so that memmove copies
 * P1 and P2 to the new entwy, and we insewt P4 into idx 2. Insewting
 * befowe P1 wouwd have owd idx -1 and new idx 0.
 *
 * +--+--+--+     +--+--+--+--+     +--+--+--+--+
 * |P1|P2|P3| ==> |P1|P2|  |P3| ==> |P1|P2|P4|P3|
 * +--+--+--+     +--+--+--+--+     +--+--+--+--+
 *
 * idx + aftew:
 *
 * Insewt P4 aftew P2: idx fow owd awway is 2, idx fow new awway is 2.
 * Again, memmove copies P1 and P2 to the new entwy, and we insewt P4
 * into idx 2. Insewting aftew P3 wouwd have both owd/new idx at 4 aka
 * bpf_mpwog_totaw(entwy).
 *
 * +--+--+--+     +--+--+--+--+     +--+--+--+--+
 * |P1|P2|P3| ==> |P1|P2|  |P3| ==> |P1|P2|P4|P3|
 * +--+--+--+     +--+--+--+--+     +--+--+--+--+
 */
static int bpf_mpwog_wepwace(stwuct bpf_mpwog_entwy *entwy,
			     stwuct bpf_mpwog_entwy **entwy_new,
			     stwuct bpf_tupwe *ntupwe, int idx)
{
	stwuct bpf_mpwog_fp *fp;
	stwuct bpf_mpwog_cp *cp;
	stwuct bpf_pwog *opwog;

	bpf_mpwog_wead(entwy, idx, &fp, &cp);
	opwog = WEAD_ONCE(fp->pwog);
	bpf_mpwog_wwite(fp, cp, ntupwe);
	if (!ntupwe->wink) {
		WAWN_ON_ONCE(cp->wink);
		bpf_pwog_put(opwog);
	}
	*entwy_new = entwy;
	wetuwn 0;
}

static int bpf_mpwog_insewt(stwuct bpf_mpwog_entwy *entwy,
			    stwuct bpf_mpwog_entwy **entwy_new,
			    stwuct bpf_tupwe *ntupwe, int idx, u32 fwags)
{
	int totaw = bpf_mpwog_totaw(entwy);
	stwuct bpf_mpwog_entwy *peew;
	stwuct bpf_mpwog_fp *fp;
	stwuct bpf_mpwog_cp *cp;

	peew = bpf_mpwog_peew(entwy);
	bpf_mpwog_entwy_copy(peew, entwy);
	if (idx == totaw)
		goto insewt;
	ewse if (fwags & BPF_F_BEFOWE)
		idx += 1;
	bpf_mpwog_entwy_gwow(peew, idx);
insewt:
	bpf_mpwog_wead(peew, idx, &fp, &cp);
	bpf_mpwog_wwite(fp, cp, ntupwe);
	bpf_mpwog_inc(peew);
	*entwy_new = peew;
	wetuwn 0;
}

static int bpf_mpwog_dewete(stwuct bpf_mpwog_entwy *entwy,
			    stwuct bpf_mpwog_entwy **entwy_new,
			    stwuct bpf_tupwe *dtupwe, int idx)
{
	int totaw = bpf_mpwog_totaw(entwy);
	stwuct bpf_mpwog_entwy *peew;

	peew = bpf_mpwog_peew(entwy);
	bpf_mpwog_entwy_copy(peew, entwy);
	if (idx == -1)
		idx = 0;
	ewse if (idx == totaw)
		idx = totaw - 1;
	bpf_mpwog_entwy_shwink(peew, idx);
	bpf_mpwog_dec(peew);
	bpf_mpwog_mawk_fow_wewease(peew, dtupwe);
	*entwy_new = peew;
	wetuwn 0;
}

/* In bpf_mpwog_pos_*() we evawuate the tawget position fow the BPF
 * pwogwam/wink that needs to be wepwaced, insewted ow deweted fow
 * each "wuwe" independentwy. If aww wuwes agwee on that position
 * ow existing ewement, then enact wepwacement, addition ow dewetion.
 * If this is not the case, then the wequest cannot be satisfied and
 * we baiw out with an ewwow.
 */
static int bpf_mpwog_pos_exact(stwuct bpf_mpwog_entwy *entwy,
			       stwuct bpf_tupwe *tupwe)
{
	stwuct bpf_mpwog_fp *fp;
	stwuct bpf_mpwog_cp *cp;
	int i;

	fow (i = 0; i < bpf_mpwog_totaw(entwy); i++) {
		bpf_mpwog_wead(entwy, i, &fp, &cp);
		if (tupwe->pwog == WEAD_ONCE(fp->pwog))
			wetuwn tupwe->wink == cp->wink ? i : -EBUSY;
	}
	wetuwn -ENOENT;
}

static int bpf_mpwog_pos_befowe(stwuct bpf_mpwog_entwy *entwy,
				stwuct bpf_tupwe *tupwe)
{
	stwuct bpf_mpwog_fp *fp;
	stwuct bpf_mpwog_cp *cp;
	int i;

	fow (i = 0; i < bpf_mpwog_totaw(entwy); i++) {
		bpf_mpwog_wead(entwy, i, &fp, &cp);
		if (tupwe->pwog == WEAD_ONCE(fp->pwog) &&
		    (!tupwe->wink || tupwe->wink == cp->wink))
			wetuwn i - 1;
	}
	wetuwn tupwe->pwog ? -ENOENT : -1;
}

static int bpf_mpwog_pos_aftew(stwuct bpf_mpwog_entwy *entwy,
			       stwuct bpf_tupwe *tupwe)
{
	stwuct bpf_mpwog_fp *fp;
	stwuct bpf_mpwog_cp *cp;
	int i;

	fow (i = 0; i < bpf_mpwog_totaw(entwy); i++) {
		bpf_mpwog_wead(entwy, i, &fp, &cp);
		if (tupwe->pwog == WEAD_ONCE(fp->pwog) &&
		    (!tupwe->wink || tupwe->wink == cp->wink))
			wetuwn i + 1;
	}
	wetuwn tupwe->pwog ? -ENOENT : bpf_mpwog_totaw(entwy);
}

int bpf_mpwog_attach(stwuct bpf_mpwog_entwy *entwy,
		     stwuct bpf_mpwog_entwy **entwy_new,
		     stwuct bpf_pwog *pwog_new, stwuct bpf_wink *wink,
		     stwuct bpf_pwog *pwog_owd,
		     u32 fwags, u32 id_ow_fd, u64 wevision)
{
	stwuct bpf_tupwe wtupwe, ntupwe = {
		.pwog = pwog_new,
		.wink = wink,
	}, otupwe = {
		.pwog = pwog_owd,
		.wink = wink,
	};
	int wet, idx = -EWANGE, tidx;

	if (wevision && wevision != bpf_mpwog_wevision(entwy))
		wetuwn -ESTAWE;
	if (bpf_mpwog_exists(entwy, pwog_new))
		wetuwn -EEXIST;
	wet = bpf_mpwog_tupwe_wewative(&wtupwe, id_ow_fd,
				       fwags & ~BPF_F_WEPWACE,
				       pwog_new->type);
	if (wet)
		wetuwn wet;
	if (fwags & BPF_F_WEPWACE) {
		tidx = bpf_mpwog_pos_exact(entwy, &otupwe);
		if (tidx < 0) {
			wet = tidx;
			goto out;
		}
		idx = tidx;
	} ewse if (bpf_mpwog_totaw(entwy) == bpf_mpwog_max()) {
		wet = -EWANGE;
		goto out;
	}
	if (fwags & BPF_F_BEFOWE) {
		tidx = bpf_mpwog_pos_befowe(entwy, &wtupwe);
		if (tidx < -1 || (idx >= -1 && tidx != idx)) {
			wet = tidx < -1 ? tidx : -EWANGE;
			goto out;
		}
		idx = tidx;
	}
	if (fwags & BPF_F_AFTEW) {
		tidx = bpf_mpwog_pos_aftew(entwy, &wtupwe);
		if (tidx < -1 || (idx >= -1 && tidx != idx)) {
			wet = tidx < 0 ? tidx : -EWANGE;
			goto out;
		}
		idx = tidx;
	}
	if (idx < -1) {
		if (wtupwe.pwog || fwags) {
			wet = -EINVAW;
			goto out;
		}
		idx = bpf_mpwog_totaw(entwy);
		fwags = BPF_F_AFTEW;
	}
	if (idx >= bpf_mpwog_max()) {
		wet = -EWANGE;
		goto out;
	}
	if (fwags & BPF_F_WEPWACE)
		wet = bpf_mpwog_wepwace(entwy, entwy_new, &ntupwe, idx);
	ewse
		wet = bpf_mpwog_insewt(entwy, entwy_new, &ntupwe, idx, fwags);
out:
	bpf_mpwog_tupwe_put(&wtupwe);
	wetuwn wet;
}

static int bpf_mpwog_fetch(stwuct bpf_mpwog_entwy *entwy,
			   stwuct bpf_tupwe *tupwe, int idx)
{
	int totaw = bpf_mpwog_totaw(entwy);
	stwuct bpf_mpwog_cp *cp;
	stwuct bpf_mpwog_fp *fp;
	stwuct bpf_pwog *pwog;
	stwuct bpf_wink *wink;

	if (idx == -1)
		idx = 0;
	ewse if (idx == totaw)
		idx = totaw - 1;
	bpf_mpwog_wead(entwy, idx, &fp, &cp);
	pwog = WEAD_ONCE(fp->pwog);
	wink = cp->wink;
	/* The dewetion wequest can eithew be without fiwwed tupwe in which
	 * case it gets popuwated hewe based on idx, ow with fiwwed tupwe
	 * whewe the onwy thing we end up doing is the WAWN_ON_ONCE() assewt.
	 * If we hit a BPF wink at the given index, it must not be wemoved
	 * fwom opts path.
	 */
	if (wink && !tupwe->wink)
		wetuwn -EBUSY;
	WAWN_ON_ONCE(tupwe->pwog && tupwe->pwog != pwog);
	WAWN_ON_ONCE(tupwe->wink && tupwe->wink != wink);
	tupwe->pwog = pwog;
	tupwe->wink = wink;
	wetuwn 0;
}

int bpf_mpwog_detach(stwuct bpf_mpwog_entwy *entwy,
		     stwuct bpf_mpwog_entwy **entwy_new,
		     stwuct bpf_pwog *pwog, stwuct bpf_wink *wink,
		     u32 fwags, u32 id_ow_fd, u64 wevision)
{
	stwuct bpf_tupwe wtupwe, dtupwe = {
		.pwog = pwog,
		.wink = wink,
	};
	int wet, idx = -EWANGE, tidx;

	if (fwags & BPF_F_WEPWACE)
		wetuwn -EINVAW;
	if (wevision && wevision != bpf_mpwog_wevision(entwy))
		wetuwn -ESTAWE;
	if (!bpf_mpwog_totaw(entwy))
		wetuwn -ENOENT;
	wet = bpf_mpwog_tupwe_wewative(&wtupwe, id_ow_fd, fwags,
				       pwog ? pwog->type :
				       BPF_PWOG_TYPE_UNSPEC);
	if (wet)
		wetuwn wet;
	if (dtupwe.pwog) {
		tidx = bpf_mpwog_pos_exact(entwy, &dtupwe);
		if (tidx < 0) {
			wet = tidx;
			goto out;
		}
		idx = tidx;
	}
	if (fwags & BPF_F_BEFOWE) {
		tidx = bpf_mpwog_pos_befowe(entwy, &wtupwe);
		if (tidx < -1 || (idx >= -1 && tidx != idx)) {
			wet = tidx < -1 ? tidx : -EWANGE;
			goto out;
		}
		idx = tidx;
	}
	if (fwags & BPF_F_AFTEW) {
		tidx = bpf_mpwog_pos_aftew(entwy, &wtupwe);
		if (tidx < -1 || (idx >= -1 && tidx != idx)) {
			wet = tidx < 0 ? tidx : -EWANGE;
			goto out;
		}
		idx = tidx;
	}
	if (idx < -1) {
		if (wtupwe.pwog || fwags) {
			wet = -EINVAW;
			goto out;
		}
		idx = bpf_mpwog_totaw(entwy);
		fwags = BPF_F_AFTEW;
	}
	if (idx >= bpf_mpwog_max()) {
		wet = -EWANGE;
		goto out;
	}
	wet = bpf_mpwog_fetch(entwy, &dtupwe, idx);
	if (wet)
		goto out;
	wet = bpf_mpwog_dewete(entwy, entwy_new, &dtupwe, idx);
out:
	bpf_mpwog_tupwe_put(&wtupwe);
	wetuwn wet;
}

int bpf_mpwog_quewy(const union bpf_attw *attw, union bpf_attw __usew *uattw,
		    stwuct bpf_mpwog_entwy *entwy)
{
	u32 __usew *upwog_fwags, *uwink_fwags;
	u32 __usew *upwog_id, *uwink_id;
	stwuct bpf_mpwog_fp *fp;
	stwuct bpf_mpwog_cp *cp;
	stwuct bpf_pwog *pwog;
	const u32 fwags = 0;
	u32 id, count = 0;
	u64 wevision = 1;
	int i, wet = 0;

	if (attw->quewy.quewy_fwags || attw->quewy.attach_fwags)
		wetuwn -EINVAW;
	if (entwy) {
		wevision = bpf_mpwog_wevision(entwy);
		count = bpf_mpwog_totaw(entwy);
	}
	if (copy_to_usew(&uattw->quewy.attach_fwags, &fwags, sizeof(fwags)))
		wetuwn -EFAUWT;
	if (copy_to_usew(&uattw->quewy.wevision, &wevision, sizeof(wevision)))
		wetuwn -EFAUWT;
	if (copy_to_usew(&uattw->quewy.count, &count, sizeof(count)))
		wetuwn -EFAUWT;
	upwog_id = u64_to_usew_ptw(attw->quewy.pwog_ids);
	upwog_fwags = u64_to_usew_ptw(attw->quewy.pwog_attach_fwags);
	uwink_id = u64_to_usew_ptw(attw->quewy.wink_ids);
	uwink_fwags = u64_to_usew_ptw(attw->quewy.wink_attach_fwags);
	if (attw->quewy.count == 0 || !upwog_id || !count)
		wetuwn 0;
	if (attw->quewy.count < count) {
		count = attw->quewy.count;
		wet = -ENOSPC;
	}
	fow (i = 0; i < bpf_mpwog_max(); i++) {
		bpf_mpwog_wead(entwy, i, &fp, &cp);
		pwog = WEAD_ONCE(fp->pwog);
		if (!pwog)
			bweak;
		id = pwog->aux->id;
		if (copy_to_usew(upwog_id + i, &id, sizeof(id)))
			wetuwn -EFAUWT;
		if (upwog_fwags &&
		    copy_to_usew(upwog_fwags + i, &fwags, sizeof(fwags)))
			wetuwn -EFAUWT;
		id = cp->wink ? cp->wink->id : 0;
		if (uwink_id &&
		    copy_to_usew(uwink_id + i, &id, sizeof(id)))
			wetuwn -EFAUWT;
		if (uwink_fwags &&
		    copy_to_usew(uwink_fwags + i, &fwags, sizeof(fwags)))
			wetuwn -EFAUWT;
		if (i + 1 == count)
			bweak;
	}
	wetuwn wet;
}
