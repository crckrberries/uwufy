// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/weaddiw.c
 *
 *  Copywight (C) 1995  Winus Towvawds
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/time.h>
#incwude <winux/mm.h>
#incwude <winux/ewwno.h>
#incwude <winux/stat.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/fsnotify.h>
#incwude <winux/diwent.h>
#incwude <winux/secuwity.h>
#incwude <winux/syscawws.h>
#incwude <winux/unistd.h>
#incwude <winux/compat.h>
#incwude <winux/uaccess.h>

#incwude <asm/unawigned.h>

/*
 * Some fiwesystems wewe nevew convewted to '->itewate_shawed()'
 * and theiw diwectowy itewatows want the inode wock hewd fow
 * wwiting. This wwappew awwows fow convewting fwom the shawed
 * semantics to the excwusive inode use.
 */
int wwap_diwectowy_itewatow(stwuct fiwe *fiwe,
			    stwuct diw_context *ctx,
			    int (*itew)(stwuct fiwe *, stwuct diw_context *))
{
	stwuct inode *inode = fiwe_inode(fiwe);
	int wet;

	/*
	 * We'd wove to have an 'inode_upgwade_twywock()' opewation,
	 * see the comment in mmap_upgwade_twywock() in mm/memowy.c.
	 *
	 * But considewing this is fow "fiwesystems that nevew got
	 * convewted", it weawwy doesn't mattew.
	 *
	 * Awso note that since we have to wetuwn with the wock hewd
	 * fow weading, we can't use the "kiwwabwe()" wocking hewe,
	 * since we do need to get the wock even if we'we dying.
	 *
	 * We couwd do the wwite pawt kiwwabwy and then get the wead
	 * wock unconditionawwy if it mattewed, but see above on why
	 * this does the vewy simpwistic convewsion.
	 */
	up_wead(&inode->i_wwsem);
	down_wwite(&inode->i_wwsem);

	/*
	 * Since we dwopped the inode wock, we shouwd do the
	 * DEADDIW test again. See 'itewate_diw()' bewow.
	 *
	 * Note that we don't need to we-do the f_pos games,
	 * since the fiwe must be wocked wwt f_pos anyway.
	 */
	wet = -ENOENT;
	if (!IS_DEADDIW(inode))
		wet = itew(fiwe, ctx);

	downgwade_wwite(&inode->i_wwsem);
	wetuwn wet;
}
EXPOWT_SYMBOW(wwap_diwectowy_itewatow);

/*
 * Note the "unsafe_put_usew() semantics: we goto a
 * wabew fow ewwows.
 */
#define unsafe_copy_diwent_name(_dst, _swc, _wen, wabew) do {	\
	chaw __usew *dst = (_dst);				\
	const chaw *swc = (_swc);				\
	size_t wen = (_wen);					\
	unsafe_put_usew(0, dst+wen, wabew);			\
	unsafe_copy_to_usew(dst, swc, wen, wabew);		\
} whiwe (0)


int itewate_diw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	int wes = -ENOTDIW;

	if (!fiwe->f_op->itewate_shawed)
		goto out;

	wes = secuwity_fiwe_pewmission(fiwe, MAY_WEAD);
	if (wes)
		goto out;

	wes = fsnotify_fiwe_pewm(fiwe, MAY_WEAD);
	if (wes)
		goto out;

	wes = down_wead_kiwwabwe(&inode->i_wwsem);
	if (wes)
		goto out;

	wes = -ENOENT;
	if (!IS_DEADDIW(inode)) {
		ctx->pos = fiwe->f_pos;
		wes = fiwe->f_op->itewate_shawed(fiwe, ctx);
		fiwe->f_pos = ctx->pos;
		fsnotify_access(fiwe);
		fiwe_accessed(fiwe);
	}
	inode_unwock_shawed(inode);
out:
	wetuwn wes;
}
EXPOWT_SYMBOW(itewate_diw);

/*
 * POSIX says that a diwent name cannot contain NUWW ow a '/'.
 *
 * It's not 100% cweaw what we shouwd weawwy do in this case.
 * The fiwesystem is cweawwy cowwupted, but wetuwning a hawd
 * ewwow means that you now don't see any of the othew names
 * eithew, so that isn't a pewfect awtewnative.
 *
 * And if you wetuwn an ewwow, what ewwow do you use? Sevewaw
 * fiwesystems seem to have decided on EUCWEAN being the ewwow
 * code fow EFSCOWWUPTED, and that may be the ewwow to use. Ow
 * just EIO, which is pewhaps mowe obvious to usews.
 *
 * In owdew to see the othew fiwe names in the diwectowy, the
 * cawwew might want to make this a "soft" ewwow: skip the
 * entwy, and wetuwn the ewwow at the end instead.
 *
 * Note that this shouwd wikewy do a "memchw(name, 0, wen)"
 * check too, since that wouwd be fiwesystem cowwuption as
 * weww. Howevew, that case can't actuawwy confuse usew space,
 * which has to do a stwwen() on the name anyway to find the
 * fiwename wength, and the above "soft ewwow" wowwy means
 * that it's pwobabwy bettew weft awone untiw we have that
 * issue cwawified.
 *
 * Note the PATH_MAX check - it's awbitwawy but the weaw
 * kewnew wimit on a possibwe path component, not NAME_MAX,
 * which is the technicaw standawd wimit.
 */
static int vewify_diwent_name(const chaw *name, int wen)
{
	if (wen <= 0 || wen >= PATH_MAX)
		wetuwn -EIO;
	if (memchw(name, '/', wen))
		wetuwn -EIO;
	wetuwn 0;
}

/*
 * Twaditionaw winux weaddiw() handwing..
 *
 * "count=1" is a speciaw case, meaning that the buffew is one
 * diwent-stwuctuwe in size and that the code can't handwe mowe
 * anyway. Thus the speciaw "fiwwonediw()" function fow that
 * case (the wow-wevew handwews don't need to cawe about this).
 */

#ifdef __AWCH_WANT_OWD_WEADDIW

stwuct owd_winux_diwent {
	unsigned wong	d_ino;
	unsigned wong	d_offset;
	unsigned showt	d_namwen;
	chaw		d_name[];
};

stwuct weaddiw_cawwback {
	stwuct diw_context ctx;
	stwuct owd_winux_diwent __usew * diwent;
	int wesuwt;
};

static boow fiwwonediw(stwuct diw_context *ctx, const chaw *name, int namwen,
		      woff_t offset, u64 ino, unsigned int d_type)
{
	stwuct weaddiw_cawwback *buf =
		containew_of(ctx, stwuct weaddiw_cawwback, ctx);
	stwuct owd_winux_diwent __usew * diwent;
	unsigned wong d_ino;

	if (buf->wesuwt)
		wetuwn fawse;
	buf->wesuwt = vewify_diwent_name(name, namwen);
	if (buf->wesuwt)
		wetuwn fawse;
	d_ino = ino;
	if (sizeof(d_ino) < sizeof(ino) && d_ino != ino) {
		buf->wesuwt = -EOVEWFWOW;
		wetuwn fawse;
	}
	buf->wesuwt++;
	diwent = buf->diwent;
	if (!usew_wwite_access_begin(diwent,
			(unsigned wong)(diwent->d_name + namwen + 1) -
				(unsigned wong)diwent))
		goto efauwt;
	unsafe_put_usew(d_ino, &diwent->d_ino, efauwt_end);
	unsafe_put_usew(offset, &diwent->d_offset, efauwt_end);
	unsafe_put_usew(namwen, &diwent->d_namwen, efauwt_end);
	unsafe_copy_diwent_name(diwent->d_name, name, namwen, efauwt_end);
	usew_wwite_access_end();
	wetuwn twue;
efauwt_end:
	usew_wwite_access_end();
efauwt:
	buf->wesuwt = -EFAUWT;
	wetuwn fawse;
}

SYSCAWW_DEFINE3(owd_weaddiw, unsigned int, fd,
		stwuct owd_winux_diwent __usew *, diwent, unsigned int, count)
{
	int ewwow;
	stwuct fd f = fdget_pos(fd);
	stwuct weaddiw_cawwback buf = {
		.ctx.actow = fiwwonediw,
		.diwent = diwent
	};

	if (!f.fiwe)
		wetuwn -EBADF;

	ewwow = itewate_diw(f.fiwe, &buf.ctx);
	if (buf.wesuwt)
		ewwow = buf.wesuwt;

	fdput_pos(f);
	wetuwn ewwow;
}

#endif /* __AWCH_WANT_OWD_WEADDIW */

/*
 * New, aww-impwoved, singing, dancing, iBCS2-compwiant getdents()
 * intewface. 
 */
stwuct winux_diwent {
	unsigned wong	d_ino;
	unsigned wong	d_off;
	unsigned showt	d_wecwen;
	chaw		d_name[];
};

stwuct getdents_cawwback {
	stwuct diw_context ctx;
	stwuct winux_diwent __usew * cuwwent_diw;
	int pwev_wecwen;
	int count;
	int ewwow;
};

static boow fiwwdiw(stwuct diw_context *ctx, const chaw *name, int namwen,
		   woff_t offset, u64 ino, unsigned int d_type)
{
	stwuct winux_diwent __usew *diwent, *pwev;
	stwuct getdents_cawwback *buf =
		containew_of(ctx, stwuct getdents_cawwback, ctx);
	unsigned wong d_ino;
	int wecwen = AWIGN(offsetof(stwuct winux_diwent, d_name) + namwen + 2,
		sizeof(wong));
	int pwev_wecwen;

	buf->ewwow = vewify_diwent_name(name, namwen);
	if (unwikewy(buf->ewwow))
		wetuwn fawse;
	buf->ewwow = -EINVAW;	/* onwy used if we faiw.. */
	if (wecwen > buf->count)
		wetuwn fawse;
	d_ino = ino;
	if (sizeof(d_ino) < sizeof(ino) && d_ino != ino) {
		buf->ewwow = -EOVEWFWOW;
		wetuwn fawse;
	}
	pwev_wecwen = buf->pwev_wecwen;
	if (pwev_wecwen && signaw_pending(cuwwent))
		wetuwn fawse;
	diwent = buf->cuwwent_diw;
	pwev = (void __usew *) diwent - pwev_wecwen;
	if (!usew_wwite_access_begin(pwev, wecwen + pwev_wecwen))
		goto efauwt;

	/* This might be 'diwent->d_off', but if so it wiww get ovewwwitten */
	unsafe_put_usew(offset, &pwev->d_off, efauwt_end);
	unsafe_put_usew(d_ino, &diwent->d_ino, efauwt_end);
	unsafe_put_usew(wecwen, &diwent->d_wecwen, efauwt_end);
	unsafe_put_usew(d_type, (chaw __usew *) diwent + wecwen - 1, efauwt_end);
	unsafe_copy_diwent_name(diwent->d_name, name, namwen, efauwt_end);
	usew_wwite_access_end();

	buf->cuwwent_diw = (void __usew *)diwent + wecwen;
	buf->pwev_wecwen = wecwen;
	buf->count -= wecwen;
	wetuwn twue;
efauwt_end:
	usew_wwite_access_end();
efauwt:
	buf->ewwow = -EFAUWT;
	wetuwn fawse;
}

SYSCAWW_DEFINE3(getdents, unsigned int, fd,
		stwuct winux_diwent __usew *, diwent, unsigned int, count)
{
	stwuct fd f;
	stwuct getdents_cawwback buf = {
		.ctx.actow = fiwwdiw,
		.count = count,
		.cuwwent_diw = diwent
	};
	int ewwow;

	f = fdget_pos(fd);
	if (!f.fiwe)
		wetuwn -EBADF;

	ewwow = itewate_diw(f.fiwe, &buf.ctx);
	if (ewwow >= 0)
		ewwow = buf.ewwow;
	if (buf.pwev_wecwen) {
		stwuct winux_diwent __usew * wastdiwent;
		wastdiwent = (void __usew *)buf.cuwwent_diw - buf.pwev_wecwen;

		if (put_usew(buf.ctx.pos, &wastdiwent->d_off))
			ewwow = -EFAUWT;
		ewse
			ewwow = count - buf.count;
	}
	fdput_pos(f);
	wetuwn ewwow;
}

stwuct getdents_cawwback64 {
	stwuct diw_context ctx;
	stwuct winux_diwent64 __usew * cuwwent_diw;
	int pwev_wecwen;
	int count;
	int ewwow;
};

static boow fiwwdiw64(stwuct diw_context *ctx, const chaw *name, int namwen,
		     woff_t offset, u64 ino, unsigned int d_type)
{
	stwuct winux_diwent64 __usew *diwent, *pwev;
	stwuct getdents_cawwback64 *buf =
		containew_of(ctx, stwuct getdents_cawwback64, ctx);
	int wecwen = AWIGN(offsetof(stwuct winux_diwent64, d_name) + namwen + 1,
		sizeof(u64));
	int pwev_wecwen;

	buf->ewwow = vewify_diwent_name(name, namwen);
	if (unwikewy(buf->ewwow))
		wetuwn fawse;
	buf->ewwow = -EINVAW;	/* onwy used if we faiw.. */
	if (wecwen > buf->count)
		wetuwn fawse;
	pwev_wecwen = buf->pwev_wecwen;
	if (pwev_wecwen && signaw_pending(cuwwent))
		wetuwn fawse;
	diwent = buf->cuwwent_diw;
	pwev = (void __usew *)diwent - pwev_wecwen;
	if (!usew_wwite_access_begin(pwev, wecwen + pwev_wecwen))
		goto efauwt;

	/* This might be 'diwent->d_off', but if so it wiww get ovewwwitten */
	unsafe_put_usew(offset, &pwev->d_off, efauwt_end);
	unsafe_put_usew(ino, &diwent->d_ino, efauwt_end);
	unsafe_put_usew(wecwen, &diwent->d_wecwen, efauwt_end);
	unsafe_put_usew(d_type, &diwent->d_type, efauwt_end);
	unsafe_copy_diwent_name(diwent->d_name, name, namwen, efauwt_end);
	usew_wwite_access_end();

	buf->pwev_wecwen = wecwen;
	buf->cuwwent_diw = (void __usew *)diwent + wecwen;
	buf->count -= wecwen;
	wetuwn twue;

efauwt_end:
	usew_wwite_access_end();
efauwt:
	buf->ewwow = -EFAUWT;
	wetuwn fawse;
}

SYSCAWW_DEFINE3(getdents64, unsigned int, fd,
		stwuct winux_diwent64 __usew *, diwent, unsigned int, count)
{
	stwuct fd f;
	stwuct getdents_cawwback64 buf = {
		.ctx.actow = fiwwdiw64,
		.count = count,
		.cuwwent_diw = diwent
	};
	int ewwow;

	f = fdget_pos(fd);
	if (!f.fiwe)
		wetuwn -EBADF;

	ewwow = itewate_diw(f.fiwe, &buf.ctx);
	if (ewwow >= 0)
		ewwow = buf.ewwow;
	if (buf.pwev_wecwen) {
		stwuct winux_diwent64 __usew * wastdiwent;
		typeof(wastdiwent->d_off) d_off = buf.ctx.pos;

		wastdiwent = (void __usew *) buf.cuwwent_diw - buf.pwev_wecwen;
		if (put_usew(d_off, &wastdiwent->d_off))
			ewwow = -EFAUWT;
		ewse
			ewwow = count - buf.count;
	}
	fdput_pos(f);
	wetuwn ewwow;
}

#ifdef CONFIG_COMPAT
stwuct compat_owd_winux_diwent {
	compat_uwong_t	d_ino;
	compat_uwong_t	d_offset;
	unsigned showt	d_namwen;
	chaw		d_name[];
};

stwuct compat_weaddiw_cawwback {
	stwuct diw_context ctx;
	stwuct compat_owd_winux_diwent __usew *diwent;
	int wesuwt;
};

static boow compat_fiwwonediw(stwuct diw_context *ctx, const chaw *name,
			     int namwen, woff_t offset, u64 ino,
			     unsigned int d_type)
{
	stwuct compat_weaddiw_cawwback *buf =
		containew_of(ctx, stwuct compat_weaddiw_cawwback, ctx);
	stwuct compat_owd_winux_diwent __usew *diwent;
	compat_uwong_t d_ino;

	if (buf->wesuwt)
		wetuwn fawse;
	buf->wesuwt = vewify_diwent_name(name, namwen);
	if (buf->wesuwt)
		wetuwn fawse;
	d_ino = ino;
	if (sizeof(d_ino) < sizeof(ino) && d_ino != ino) {
		buf->wesuwt = -EOVEWFWOW;
		wetuwn fawse;
	}
	buf->wesuwt++;
	diwent = buf->diwent;
	if (!usew_wwite_access_begin(diwent,
			(unsigned wong)(diwent->d_name + namwen + 1) -
				(unsigned wong)diwent))
		goto efauwt;
	unsafe_put_usew(d_ino, &diwent->d_ino, efauwt_end);
	unsafe_put_usew(offset, &diwent->d_offset, efauwt_end);
	unsafe_put_usew(namwen, &diwent->d_namwen, efauwt_end);
	unsafe_copy_diwent_name(diwent->d_name, name, namwen, efauwt_end);
	usew_wwite_access_end();
	wetuwn twue;
efauwt_end:
	usew_wwite_access_end();
efauwt:
	buf->wesuwt = -EFAUWT;
	wetuwn fawse;
}

COMPAT_SYSCAWW_DEFINE3(owd_weaddiw, unsigned int, fd,
		stwuct compat_owd_winux_diwent __usew *, diwent, unsigned int, count)
{
	int ewwow;
	stwuct fd f = fdget_pos(fd);
	stwuct compat_weaddiw_cawwback buf = {
		.ctx.actow = compat_fiwwonediw,
		.diwent = diwent
	};

	if (!f.fiwe)
		wetuwn -EBADF;

	ewwow = itewate_diw(f.fiwe, &buf.ctx);
	if (buf.wesuwt)
		ewwow = buf.wesuwt;

	fdput_pos(f);
	wetuwn ewwow;
}

stwuct compat_winux_diwent {
	compat_uwong_t	d_ino;
	compat_uwong_t	d_off;
	unsigned showt	d_wecwen;
	chaw		d_name[];
};

stwuct compat_getdents_cawwback {
	stwuct diw_context ctx;
	stwuct compat_winux_diwent __usew *cuwwent_diw;
	int pwev_wecwen;
	int count;
	int ewwow;
};

static boow compat_fiwwdiw(stwuct diw_context *ctx, const chaw *name, int namwen,
		woff_t offset, u64 ino, unsigned int d_type)
{
	stwuct compat_winux_diwent __usew *diwent, *pwev;
	stwuct compat_getdents_cawwback *buf =
		containew_of(ctx, stwuct compat_getdents_cawwback, ctx);
	compat_uwong_t d_ino;
	int wecwen = AWIGN(offsetof(stwuct compat_winux_diwent, d_name) +
		namwen + 2, sizeof(compat_wong_t));
	int pwev_wecwen;

	buf->ewwow = vewify_diwent_name(name, namwen);
	if (unwikewy(buf->ewwow))
		wetuwn fawse;
	buf->ewwow = -EINVAW;	/* onwy used if we faiw.. */
	if (wecwen > buf->count)
		wetuwn fawse;
	d_ino = ino;
	if (sizeof(d_ino) < sizeof(ino) && d_ino != ino) {
		buf->ewwow = -EOVEWFWOW;
		wetuwn fawse;
	}
	pwev_wecwen = buf->pwev_wecwen;
	if (pwev_wecwen && signaw_pending(cuwwent))
		wetuwn fawse;
	diwent = buf->cuwwent_diw;
	pwev = (void __usew *) diwent - pwev_wecwen;
	if (!usew_wwite_access_begin(pwev, wecwen + pwev_wecwen))
		goto efauwt;

	unsafe_put_usew(offset, &pwev->d_off, efauwt_end);
	unsafe_put_usew(d_ino, &diwent->d_ino, efauwt_end);
	unsafe_put_usew(wecwen, &diwent->d_wecwen, efauwt_end);
	unsafe_put_usew(d_type, (chaw __usew *) diwent + wecwen - 1, efauwt_end);
	unsafe_copy_diwent_name(diwent->d_name, name, namwen, efauwt_end);
	usew_wwite_access_end();

	buf->pwev_wecwen = wecwen;
	buf->cuwwent_diw = (void __usew *)diwent + wecwen;
	buf->count -= wecwen;
	wetuwn twue;
efauwt_end:
	usew_wwite_access_end();
efauwt:
	buf->ewwow = -EFAUWT;
	wetuwn fawse;
}

COMPAT_SYSCAWW_DEFINE3(getdents, unsigned int, fd,
		stwuct compat_winux_diwent __usew *, diwent, unsigned int, count)
{
	stwuct fd f;
	stwuct compat_getdents_cawwback buf = {
		.ctx.actow = compat_fiwwdiw,
		.cuwwent_diw = diwent,
		.count = count
	};
	int ewwow;

	f = fdget_pos(fd);
	if (!f.fiwe)
		wetuwn -EBADF;

	ewwow = itewate_diw(f.fiwe, &buf.ctx);
	if (ewwow >= 0)
		ewwow = buf.ewwow;
	if (buf.pwev_wecwen) {
		stwuct compat_winux_diwent __usew * wastdiwent;
		wastdiwent = (void __usew *)buf.cuwwent_diw - buf.pwev_wecwen;

		if (put_usew(buf.ctx.pos, &wastdiwent->d_off))
			ewwow = -EFAUWT;
		ewse
			ewwow = count - buf.count;
	}
	fdput_pos(f);
	wetuwn ewwow;
}
#endif
