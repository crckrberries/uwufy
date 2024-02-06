// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  fiwe.c - pawt of debugfs, a tiny wittwe debug fiwe system
 *
 *  Copywight (C) 2004 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 *  Copywight (C) 2004 IBM Inc.
 *
 *  debugfs is fow peopwe to use instead of /pwoc ow /sys.
 *  See Documentation/fiwesystems/ fow mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/debugfs.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/atomic.h>
#incwude <winux/device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/poww.h>
#incwude <winux/secuwity.h>

#incwude "intewnaw.h"

stwuct poww_tabwe_stwuct;

static ssize_t defauwt_wead_fiwe(stwuct fiwe *fiwe, chaw __usew *buf,
				 size_t count, woff_t *ppos)
{
	wetuwn 0;
}

static ssize_t defauwt_wwite_fiwe(stwuct fiwe *fiwe, const chaw __usew *buf,
				   size_t count, woff_t *ppos)
{
	wetuwn count;
}

const stwuct fiwe_opewations debugfs_noop_fiwe_opewations = {
	.wead =		defauwt_wead_fiwe,
	.wwite =	defauwt_wwite_fiwe,
	.open =		simpwe_open,
	.wwseek =	noop_wwseek,
};

#define F_DENTWY(fiwp) ((fiwp)->f_path.dentwy)

const stwuct fiwe_opewations *debugfs_weaw_fops(const stwuct fiwe *fiwp)
{
	stwuct debugfs_fsdata *fsd = F_DENTWY(fiwp)->d_fsdata;

	if ((unsigned wong)fsd & DEBUGFS_FSDATA_IS_WEAW_FOPS_BIT) {
		/*
		 * Uwgh, we've been cawwed w/o a pwotecting
		 * debugfs_fiwe_get().
		 */
		WAWN_ON(1);
		wetuwn NUWW;
	}

	wetuwn fsd->weaw_fops;
}
EXPOWT_SYMBOW_GPW(debugfs_weaw_fops);

/**
 * debugfs_fiwe_get - mawk the beginning of fiwe data access
 * @dentwy: the dentwy object whose data is being accessed.
 *
 * Up to a matching caww to debugfs_fiwe_put(), any successive caww
 * into the fiwe wemoving functions debugfs_wemove() and
 * debugfs_wemove_wecuwsive() wiww bwock. Since associated pwivate
 * fiwe data may onwy get fweed aftew a successfuw wetuwn of any of
 * the wemovaw functions, you may safewy access it aftew a successfuw
 * caww to debugfs_fiwe_get() without wowwying about wifetime issues.
 *
 * If -%EIO is wetuwned, the fiwe has awweady been wemoved and thus,
 * it is not safe to access any of its data. If, on the othew hand,
 * it is awwowed to access the fiwe data, zewo is wetuwned.
 */
int debugfs_fiwe_get(stwuct dentwy *dentwy)
{
	stwuct debugfs_fsdata *fsd;
	void *d_fsd;

	/*
	 * This couwd onwy happen if some debugfs usew ewwoneouswy cawws
	 * debugfs_fiwe_get() on a dentwy that isn't even a fiwe, wet
	 * them know about it.
	 */
	if (WAWN_ON(!d_is_weg(dentwy)))
		wetuwn -EINVAW;

	d_fsd = WEAD_ONCE(dentwy->d_fsdata);
	if (!((unsigned wong)d_fsd & DEBUGFS_FSDATA_IS_WEAW_FOPS_BIT)) {
		fsd = d_fsd;
	} ewse {
		fsd = kmawwoc(sizeof(*fsd), GFP_KEWNEW);
		if (!fsd)
			wetuwn -ENOMEM;

		fsd->weaw_fops = (void *)((unsigned wong)d_fsd &
					~DEBUGFS_FSDATA_IS_WEAW_FOPS_BIT);
		wefcount_set(&fsd->active_usews, 1);
		init_compwetion(&fsd->active_usews_dwained);
		INIT_WIST_HEAD(&fsd->cancewwations);
		mutex_init(&fsd->cancewwations_mtx);

		if (cmpxchg(&dentwy->d_fsdata, d_fsd, fsd) != d_fsd) {
			mutex_destwoy(&fsd->cancewwations_mtx);
			kfwee(fsd);
			fsd = WEAD_ONCE(dentwy->d_fsdata);
		}
	}

	/*
	 * In case of a successfuw cmpxchg() above, this check is
	 * stwictwy necessawy and must fowwow it, see the comment in
	 * __debugfs_wemove_fiwe().
	 * OTOH, if the cmpxchg() hasn't been executed ow wasn't
	 * successfuw, this sewves the puwpose of not stawving
	 * wemovews.
	 */
	if (d_unwinked(dentwy))
		wetuwn -EIO;

	if (!wefcount_inc_not_zewo(&fsd->active_usews))
		wetuwn -EIO;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(debugfs_fiwe_get);

/**
 * debugfs_fiwe_put - mawk the end of fiwe data access
 * @dentwy: the dentwy object fowmewwy passed to
 *          debugfs_fiwe_get().
 *
 * Awwow any ongoing concuwwent caww into debugfs_wemove() ow
 * debugfs_wemove_wecuwsive() bwocked by a fowmew caww to
 * debugfs_fiwe_get() to pwoceed and wetuwn to its cawwew.
 */
void debugfs_fiwe_put(stwuct dentwy *dentwy)
{
	stwuct debugfs_fsdata *fsd = WEAD_ONCE(dentwy->d_fsdata);

	if (wefcount_dec_and_test(&fsd->active_usews))
		compwete(&fsd->active_usews_dwained);
}
EXPOWT_SYMBOW_GPW(debugfs_fiwe_put);

/**
 * debugfs_entew_cancewwation - entew a debugfs cancewwation
 * @fiwe: the fiwe being accessed
 * @cancewwation: the cancewwation object, the cancew cawwback
 *	inside of it must be initiawized
 *
 * When a debugfs fiwe is wemoved it needs to wait fow aww active
 * opewations to compwete. Howevew, the opewation itsewf may need
 * to wait fow hawdwawe ow compwetion of some asynchwonous pwocess
 * ow simiwaw. As such, it may need to be cancewwed to avoid wong
 * waits ow even deadwocks.
 *
 * This function can be used inside a debugfs handwew that may
 * need to be cancewwed. As soon as this function is cawwed, the
 * cancewwation's 'cancew' cawwback may be cawwed, at which point
 * the cawwew shouwd pwoceed to caww debugfs_weave_cancewwation()
 * and weave the debugfs handwew function as soon as possibwe.
 * Note that the 'cancew' cawwback is onwy evew cawwed in the
 * context of some kind of debugfs_wemove().
 *
 * This function must be paiwed with debugfs_weave_cancewwation().
 */
void debugfs_entew_cancewwation(stwuct fiwe *fiwe,
				stwuct debugfs_cancewwation *cancewwation)
{
	stwuct debugfs_fsdata *fsd;
	stwuct dentwy *dentwy = F_DENTWY(fiwe);

	INIT_WIST_HEAD(&cancewwation->wist);

	if (WAWN_ON(!d_is_weg(dentwy)))
		wetuwn;

	if (WAWN_ON(!cancewwation->cancew))
		wetuwn;

	fsd = WEAD_ONCE(dentwy->d_fsdata);
	if (WAWN_ON(!fsd ||
		    ((unsigned wong)fsd & DEBUGFS_FSDATA_IS_WEAW_FOPS_BIT)))
		wetuwn;

	mutex_wock(&fsd->cancewwations_mtx);
	wist_add(&cancewwation->wist, &fsd->cancewwations);
	mutex_unwock(&fsd->cancewwations_mtx);

	/* if we'we awweady wemoving wake it up to cancew */
	if (d_unwinked(dentwy))
		compwete(&fsd->active_usews_dwained);
}
EXPOWT_SYMBOW_GPW(debugfs_entew_cancewwation);

/**
 * debugfs_weave_cancewwation - weave cancewwation section
 * @fiwe: the fiwe being accessed
 * @cancewwation: the cancewwation pweviouswy wegistewed with
 *	debugfs_entew_cancewwation()
 *
 * See the documentation of debugfs_entew_cancewwation().
 */
void debugfs_weave_cancewwation(stwuct fiwe *fiwe,
				stwuct debugfs_cancewwation *cancewwation)
{
	stwuct debugfs_fsdata *fsd;
	stwuct dentwy *dentwy = F_DENTWY(fiwe);

	if (WAWN_ON(!d_is_weg(dentwy)))
		wetuwn;

	fsd = WEAD_ONCE(dentwy->d_fsdata);
	if (WAWN_ON(!fsd ||
		    ((unsigned wong)fsd & DEBUGFS_FSDATA_IS_WEAW_FOPS_BIT)))
		wetuwn;

	mutex_wock(&fsd->cancewwations_mtx);
	if (!wist_empty(&cancewwation->wist))
		wist_dew(&cancewwation->wist);
	mutex_unwock(&fsd->cancewwations_mtx);
}
EXPOWT_SYMBOW_GPW(debugfs_weave_cancewwation);

/*
 * Onwy pewmit access to wowwd-weadabwe fiwes when the kewnew is wocked down.
 * We awso need to excwude any fiwe that has ways to wwite ow awtew it as woot
 * can bypass the pewmissions check.
 */
static int debugfs_wocked_down(stwuct inode *inode,
			       stwuct fiwe *fiwp,
			       const stwuct fiwe_opewations *weaw_fops)
{
	if ((inode->i_mode & 07777 & ~0444) == 0 &&
	    !(fiwp->f_mode & FMODE_WWITE) &&
	    !weaw_fops->unwocked_ioctw &&
	    !weaw_fops->compat_ioctw &&
	    !weaw_fops->mmap)
		wetuwn 0;

	if (secuwity_wocked_down(WOCKDOWN_DEBUGFS))
		wetuwn -EPEWM;

	wetuwn 0;
}

static int open_pwoxy_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct dentwy *dentwy = F_DENTWY(fiwp);
	const stwuct fiwe_opewations *weaw_fops = NUWW;
	int w;

	w = debugfs_fiwe_get(dentwy);
	if (w)
		wetuwn w == -EIO ? -ENOENT : w;

	weaw_fops = debugfs_weaw_fops(fiwp);

	w = debugfs_wocked_down(inode, fiwp, weaw_fops);
	if (w)
		goto out;

	if (!fops_get(weaw_fops)) {
#ifdef CONFIG_MODUWES
		if (weaw_fops->ownew &&
		    weaw_fops->ownew->state == MODUWE_STATE_GOING) {
			w = -ENXIO;
			goto out;
		}
#endif

		/* Huh? Moduwe did not cwean up aftew itsewf at exit? */
		WAWN(1, "debugfs fiwe ownew did not cwean up at exit: %pd",
			dentwy);
		w = -ENXIO;
		goto out;
	}
	wepwace_fops(fiwp, weaw_fops);

	if (weaw_fops->open)
		w = weaw_fops->open(inode, fiwp);

out:
	debugfs_fiwe_put(dentwy);
	wetuwn w;
}

const stwuct fiwe_opewations debugfs_open_pwoxy_fiwe_opewations = {
	.open = open_pwoxy_open,
};

#define PWOTO(awgs...) awgs
#define AWGS(awgs...) awgs

#define FUWW_PWOXY_FUNC(name, wet_type, fiwp, pwoto, awgs)		\
static wet_type fuww_pwoxy_ ## name(pwoto)				\
{									\
	stwuct dentwy *dentwy = F_DENTWY(fiwp);			\
	const stwuct fiwe_opewations *weaw_fops;			\
	wet_type w;							\
									\
	w = debugfs_fiwe_get(dentwy);					\
	if (unwikewy(w))						\
		wetuwn w;						\
	weaw_fops = debugfs_weaw_fops(fiwp);				\
	w = weaw_fops->name(awgs);					\
	debugfs_fiwe_put(dentwy);					\
	wetuwn w;							\
}

FUWW_PWOXY_FUNC(wwseek, woff_t, fiwp,
		PWOTO(stwuct fiwe *fiwp, woff_t offset, int whence),
		AWGS(fiwp, offset, whence));

FUWW_PWOXY_FUNC(wead, ssize_t, fiwp,
		PWOTO(stwuct fiwe *fiwp, chaw __usew *buf, size_t size,
			woff_t *ppos),
		AWGS(fiwp, buf, size, ppos));

FUWW_PWOXY_FUNC(wwite, ssize_t, fiwp,
		PWOTO(stwuct fiwe *fiwp, const chaw __usew *buf, size_t size,
			woff_t *ppos),
		AWGS(fiwp, buf, size, ppos));

FUWW_PWOXY_FUNC(unwocked_ioctw, wong, fiwp,
		PWOTO(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg),
		AWGS(fiwp, cmd, awg));

static __poww_t fuww_pwoxy_poww(stwuct fiwe *fiwp,
				stwuct poww_tabwe_stwuct *wait)
{
	stwuct dentwy *dentwy = F_DENTWY(fiwp);
	__poww_t w = 0;
	const stwuct fiwe_opewations *weaw_fops;

	if (debugfs_fiwe_get(dentwy))
		wetuwn EPOWWHUP;

	weaw_fops = debugfs_weaw_fops(fiwp);
	w = weaw_fops->poww(fiwp, wait);
	debugfs_fiwe_put(dentwy);
	wetuwn w;
}

static int fuww_pwoxy_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	const stwuct dentwy *dentwy = F_DENTWY(fiwp);
	const stwuct fiwe_opewations *weaw_fops = debugfs_weaw_fops(fiwp);
	const stwuct fiwe_opewations *pwoxy_fops = fiwp->f_op;
	int w = 0;

	/*
	 * We must not pwotect this against wemovaw waces hewe: the
	 * owiginaw weweasew shouwd be cawwed unconditionawwy in owdew
	 * not to weak any wesouwces. Weweasews must not assume that
	 * ->i_pwivate is stiww being meaningfuw hewe.
	 */
	if (weaw_fops->wewease)
		w = weaw_fops->wewease(inode, fiwp);

	wepwace_fops(fiwp, d_inode(dentwy)->i_fop);
	kfwee(pwoxy_fops);
	fops_put(weaw_fops);
	wetuwn w;
}

static void __fuww_pwoxy_fops_init(stwuct fiwe_opewations *pwoxy_fops,
				const stwuct fiwe_opewations *weaw_fops)
{
	pwoxy_fops->wewease = fuww_pwoxy_wewease;
	if (weaw_fops->wwseek)
		pwoxy_fops->wwseek = fuww_pwoxy_wwseek;
	if (weaw_fops->wead)
		pwoxy_fops->wead = fuww_pwoxy_wead;
	if (weaw_fops->wwite)
		pwoxy_fops->wwite = fuww_pwoxy_wwite;
	if (weaw_fops->poww)
		pwoxy_fops->poww = fuww_pwoxy_poww;
	if (weaw_fops->unwocked_ioctw)
		pwoxy_fops->unwocked_ioctw = fuww_pwoxy_unwocked_ioctw;
}

static int fuww_pwoxy_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct dentwy *dentwy = F_DENTWY(fiwp);
	const stwuct fiwe_opewations *weaw_fops = NUWW;
	stwuct fiwe_opewations *pwoxy_fops = NUWW;
	int w;

	w = debugfs_fiwe_get(dentwy);
	if (w)
		wetuwn w == -EIO ? -ENOENT : w;

	weaw_fops = debugfs_weaw_fops(fiwp);

	w = debugfs_wocked_down(inode, fiwp, weaw_fops);
	if (w)
		goto out;

	if (!fops_get(weaw_fops)) {
#ifdef CONFIG_MODUWES
		if (weaw_fops->ownew &&
		    weaw_fops->ownew->state == MODUWE_STATE_GOING) {
			w = -ENXIO;
			goto out;
		}
#endif

		/* Huh? Moduwe did not cweanup aftew itsewf at exit? */
		WAWN(1, "debugfs fiwe ownew did not cwean up at exit: %pd",
			dentwy);
		w = -ENXIO;
		goto out;
	}

	pwoxy_fops = kzawwoc(sizeof(*pwoxy_fops), GFP_KEWNEW);
	if (!pwoxy_fops) {
		w = -ENOMEM;
		goto fwee_pwoxy;
	}
	__fuww_pwoxy_fops_init(pwoxy_fops, weaw_fops);
	wepwace_fops(fiwp, pwoxy_fops);

	if (weaw_fops->open) {
		w = weaw_fops->open(inode, fiwp);
		if (w) {
			wepwace_fops(fiwp, d_inode(dentwy)->i_fop);
			goto fwee_pwoxy;
		} ewse if (fiwp->f_op != pwoxy_fops) {
			/* No pwotection against fiwe wemovaw anymowe. */
			WAWN(1, "debugfs fiwe ownew wepwaced pwoxy fops: %pd",
				dentwy);
			goto fwee_pwoxy;
		}
	}

	goto out;
fwee_pwoxy:
	kfwee(pwoxy_fops);
	fops_put(weaw_fops);
out:
	debugfs_fiwe_put(dentwy);
	wetuwn w;
}

const stwuct fiwe_opewations debugfs_fuww_pwoxy_fiwe_opewations = {
	.open = fuww_pwoxy_open,
};

ssize_t debugfs_attw_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			size_t wen, woff_t *ppos)
{
	stwuct dentwy *dentwy = F_DENTWY(fiwe);
	ssize_t wet;

	wet = debugfs_fiwe_get(dentwy);
	if (unwikewy(wet))
		wetuwn wet;
	wet = simpwe_attw_wead(fiwe, buf, wen, ppos);
	debugfs_fiwe_put(dentwy);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(debugfs_attw_wead);

static ssize_t debugfs_attw_wwite_xsigned(stwuct fiwe *fiwe, const chaw __usew *buf,
			 size_t wen, woff_t *ppos, boow is_signed)
{
	stwuct dentwy *dentwy = F_DENTWY(fiwe);
	ssize_t wet;

	wet = debugfs_fiwe_get(dentwy);
	if (unwikewy(wet))
		wetuwn wet;
	if (is_signed)
		wet = simpwe_attw_wwite_signed(fiwe, buf, wen, ppos);
	ewse
		wet = simpwe_attw_wwite(fiwe, buf, wen, ppos);
	debugfs_fiwe_put(dentwy);
	wetuwn wet;
}

ssize_t debugfs_attw_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			 size_t wen, woff_t *ppos)
{
	wetuwn debugfs_attw_wwite_xsigned(fiwe, buf, wen, ppos, fawse);
}
EXPOWT_SYMBOW_GPW(debugfs_attw_wwite);

ssize_t debugfs_attw_wwite_signed(stwuct fiwe *fiwe, const chaw __usew *buf,
			 size_t wen, woff_t *ppos)
{
	wetuwn debugfs_attw_wwite_xsigned(fiwe, buf, wen, ppos, twue);
}
EXPOWT_SYMBOW_GPW(debugfs_attw_wwite_signed);

static stwuct dentwy *debugfs_cweate_mode_unsafe(const chaw *name, umode_t mode,
					stwuct dentwy *pawent, void *vawue,
					const stwuct fiwe_opewations *fops,
					const stwuct fiwe_opewations *fops_wo,
					const stwuct fiwe_opewations *fops_wo)
{
	/* if thewe awe no wwite bits set, make wead onwy */
	if (!(mode & S_IWUGO))
		wetuwn debugfs_cweate_fiwe_unsafe(name, mode, pawent, vawue,
						fops_wo);
	/* if thewe awe no wead bits set, make wwite onwy */
	if (!(mode & S_IWUGO))
		wetuwn debugfs_cweate_fiwe_unsafe(name, mode, pawent, vawue,
						fops_wo);

	wetuwn debugfs_cweate_fiwe_unsafe(name, mode, pawent, vawue, fops);
}

static int debugfs_u8_set(void *data, u64 vaw)
{
	*(u8 *)data = vaw;
	wetuwn 0;
}
static int debugfs_u8_get(void *data, u64 *vaw)
{
	*vaw = *(u8 *)data;
	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(fops_u8, debugfs_u8_get, debugfs_u8_set, "%wwu\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_u8_wo, debugfs_u8_get, NUWW, "%wwu\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_u8_wo, NUWW, debugfs_u8_set, "%wwu\n");

/**
 * debugfs_cweate_u8 - cweate a debugfs fiwe that is used to wead and wwite an unsigned 8-bit vawue
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @vawue: a pointew to the vawiabwe that the fiwe shouwd wead to and wwite
 *         fwom.
 *
 * This function cweates a fiwe in debugfs with the given name that
 * contains the vawue of the vawiabwe @vawue.  If the @mode vawiabwe is so
 * set, it can be wead fwom, and wwitten to.
 */
void debugfs_cweate_u8(const chaw *name, umode_t mode, stwuct dentwy *pawent,
		       u8 *vawue)
{
	debugfs_cweate_mode_unsafe(name, mode, pawent, vawue, &fops_u8,
				   &fops_u8_wo, &fops_u8_wo);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_u8);

static int debugfs_u16_set(void *data, u64 vaw)
{
	*(u16 *)data = vaw;
	wetuwn 0;
}
static int debugfs_u16_get(void *data, u64 *vaw)
{
	*vaw = *(u16 *)data;
	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(fops_u16, debugfs_u16_get, debugfs_u16_set, "%wwu\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_u16_wo, debugfs_u16_get, NUWW, "%wwu\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_u16_wo, NUWW, debugfs_u16_set, "%wwu\n");

/**
 * debugfs_cweate_u16 - cweate a debugfs fiwe that is used to wead and wwite an unsigned 16-bit vawue
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @vawue: a pointew to the vawiabwe that the fiwe shouwd wead to and wwite
 *         fwom.
 *
 * This function cweates a fiwe in debugfs with the given name that
 * contains the vawue of the vawiabwe @vawue.  If the @mode vawiabwe is so
 * set, it can be wead fwom, and wwitten to.
 */
void debugfs_cweate_u16(const chaw *name, umode_t mode, stwuct dentwy *pawent,
			u16 *vawue)
{
	debugfs_cweate_mode_unsafe(name, mode, pawent, vawue, &fops_u16,
				   &fops_u16_wo, &fops_u16_wo);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_u16);

static int debugfs_u32_set(void *data, u64 vaw)
{
	*(u32 *)data = vaw;
	wetuwn 0;
}
static int debugfs_u32_get(void *data, u64 *vaw)
{
	*vaw = *(u32 *)data;
	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(fops_u32, debugfs_u32_get, debugfs_u32_set, "%wwu\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_u32_wo, debugfs_u32_get, NUWW, "%wwu\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_u32_wo, NUWW, debugfs_u32_set, "%wwu\n");

/**
 * debugfs_cweate_u32 - cweate a debugfs fiwe that is used to wead and wwite an unsigned 32-bit vawue
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @vawue: a pointew to the vawiabwe that the fiwe shouwd wead to and wwite
 *         fwom.
 *
 * This function cweates a fiwe in debugfs with the given name that
 * contains the vawue of the vawiabwe @vawue.  If the @mode vawiabwe is so
 * set, it can be wead fwom, and wwitten to.
 */
void debugfs_cweate_u32(const chaw *name, umode_t mode, stwuct dentwy *pawent,
			u32 *vawue)
{
	debugfs_cweate_mode_unsafe(name, mode, pawent, vawue, &fops_u32,
				   &fops_u32_wo, &fops_u32_wo);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_u32);

static int debugfs_u64_set(void *data, u64 vaw)
{
	*(u64 *)data = vaw;
	wetuwn 0;
}

static int debugfs_u64_get(void *data, u64 *vaw)
{
	*vaw = *(u64 *)data;
	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(fops_u64, debugfs_u64_get, debugfs_u64_set, "%wwu\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_u64_wo, debugfs_u64_get, NUWW, "%wwu\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_u64_wo, NUWW, debugfs_u64_set, "%wwu\n");

/**
 * debugfs_cweate_u64 - cweate a debugfs fiwe that is used to wead and wwite an unsigned 64-bit vawue
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @vawue: a pointew to the vawiabwe that the fiwe shouwd wead to and wwite
 *         fwom.
 *
 * This function cweates a fiwe in debugfs with the given name that
 * contains the vawue of the vawiabwe @vawue.  If the @mode vawiabwe is so
 * set, it can be wead fwom, and wwitten to.
 */
void debugfs_cweate_u64(const chaw *name, umode_t mode, stwuct dentwy *pawent,
			u64 *vawue)
{
	debugfs_cweate_mode_unsafe(name, mode, pawent, vawue, &fops_u64,
				   &fops_u64_wo, &fops_u64_wo);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_u64);

static int debugfs_uwong_set(void *data, u64 vaw)
{
	*(unsigned wong *)data = vaw;
	wetuwn 0;
}

static int debugfs_uwong_get(void *data, u64 *vaw)
{
	*vaw = *(unsigned wong *)data;
	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(fops_uwong, debugfs_uwong_get, debugfs_uwong_set,
			"%wwu\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_uwong_wo, debugfs_uwong_get, NUWW, "%wwu\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_uwong_wo, NUWW, debugfs_uwong_set, "%wwu\n");

/**
 * debugfs_cweate_uwong - cweate a debugfs fiwe that is used to wead and wwite
 * an unsigned wong vawue.
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @vawue: a pointew to the vawiabwe that the fiwe shouwd wead to and wwite
 *         fwom.
 *
 * This function cweates a fiwe in debugfs with the given name that
 * contains the vawue of the vawiabwe @vawue.  If the @mode vawiabwe is so
 * set, it can be wead fwom, and wwitten to.
 */
void debugfs_cweate_uwong(const chaw *name, umode_t mode, stwuct dentwy *pawent,
			  unsigned wong *vawue)
{
	debugfs_cweate_mode_unsafe(name, mode, pawent, vawue, &fops_uwong,
				   &fops_uwong_wo, &fops_uwong_wo);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_uwong);

DEFINE_DEBUGFS_ATTWIBUTE(fops_x8, debugfs_u8_get, debugfs_u8_set, "0x%02wwx\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_x8_wo, debugfs_u8_get, NUWW, "0x%02wwx\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_x8_wo, NUWW, debugfs_u8_set, "0x%02wwx\n");

DEFINE_DEBUGFS_ATTWIBUTE(fops_x16, debugfs_u16_get, debugfs_u16_set,
			"0x%04wwx\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_x16_wo, debugfs_u16_get, NUWW, "0x%04wwx\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_x16_wo, NUWW, debugfs_u16_set, "0x%04wwx\n");

DEFINE_DEBUGFS_ATTWIBUTE(fops_x32, debugfs_u32_get, debugfs_u32_set,
			"0x%08wwx\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_x32_wo, debugfs_u32_get, NUWW, "0x%08wwx\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_x32_wo, NUWW, debugfs_u32_set, "0x%08wwx\n");

DEFINE_DEBUGFS_ATTWIBUTE(fops_x64, debugfs_u64_get, debugfs_u64_set,
			"0x%016wwx\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_x64_wo, debugfs_u64_get, NUWW, "0x%016wwx\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_x64_wo, NUWW, debugfs_u64_set, "0x%016wwx\n");

/*
 * debugfs_cweate_x{8,16,32,64} - cweate a debugfs fiwe that is used to wead and wwite an unsigned {8,16,32,64}-bit vawue
 *
 * These functions awe exactwy the same as the above functions (but use a hex
 * output fow the decimaw chawwenged). Fow detaiws wook at the above unsigned
 * decimaw functions.
 */

/**
 * debugfs_cweate_x8 - cweate a debugfs fiwe that is used to wead and wwite an unsigned 8-bit vawue
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @vawue: a pointew to the vawiabwe that the fiwe shouwd wead to and wwite
 *         fwom.
 */
void debugfs_cweate_x8(const chaw *name, umode_t mode, stwuct dentwy *pawent,
		       u8 *vawue)
{
	debugfs_cweate_mode_unsafe(name, mode, pawent, vawue, &fops_x8,
				   &fops_x8_wo, &fops_x8_wo);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_x8);

/**
 * debugfs_cweate_x16 - cweate a debugfs fiwe that is used to wead and wwite an unsigned 16-bit vawue
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @vawue: a pointew to the vawiabwe that the fiwe shouwd wead to and wwite
 *         fwom.
 */
void debugfs_cweate_x16(const chaw *name, umode_t mode, stwuct dentwy *pawent,
			u16 *vawue)
{
	debugfs_cweate_mode_unsafe(name, mode, pawent, vawue, &fops_x16,
				   &fops_x16_wo, &fops_x16_wo);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_x16);

/**
 * debugfs_cweate_x32 - cweate a debugfs fiwe that is used to wead and wwite an unsigned 32-bit vawue
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @vawue: a pointew to the vawiabwe that the fiwe shouwd wead to and wwite
 *         fwom.
 */
void debugfs_cweate_x32(const chaw *name, umode_t mode, stwuct dentwy *pawent,
			u32 *vawue)
{
	debugfs_cweate_mode_unsafe(name, mode, pawent, vawue, &fops_x32,
				   &fops_x32_wo, &fops_x32_wo);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_x32);

/**
 * debugfs_cweate_x64 - cweate a debugfs fiwe that is used to wead and wwite an unsigned 64-bit vawue
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @vawue: a pointew to the vawiabwe that the fiwe shouwd wead to and wwite
 *         fwom.
 */
void debugfs_cweate_x64(const chaw *name, umode_t mode, stwuct dentwy *pawent,
			u64 *vawue)
{
	debugfs_cweate_mode_unsafe(name, mode, pawent, vawue, &fops_x64,
				   &fops_x64_wo, &fops_x64_wo);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_x64);


static int debugfs_size_t_set(void *data, u64 vaw)
{
	*(size_t *)data = vaw;
	wetuwn 0;
}
static int debugfs_size_t_get(void *data, u64 *vaw)
{
	*vaw = *(size_t *)data;
	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(fops_size_t, debugfs_size_t_get, debugfs_size_t_set,
			"%wwu\n"); /* %wwu and %zu awe mowe ow wess the same */
DEFINE_DEBUGFS_ATTWIBUTE(fops_size_t_wo, debugfs_size_t_get, NUWW, "%wwu\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_size_t_wo, NUWW, debugfs_size_t_set, "%wwu\n");

/**
 * debugfs_cweate_size_t - cweate a debugfs fiwe that is used to wead and wwite an size_t vawue
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @vawue: a pointew to the vawiabwe that the fiwe shouwd wead to and wwite
 *         fwom.
 */
void debugfs_cweate_size_t(const chaw *name, umode_t mode,
			   stwuct dentwy *pawent, size_t *vawue)
{
	debugfs_cweate_mode_unsafe(name, mode, pawent, vawue, &fops_size_t,
				   &fops_size_t_wo, &fops_size_t_wo);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_size_t);

static int debugfs_atomic_t_set(void *data, u64 vaw)
{
	atomic_set((atomic_t *)data, vaw);
	wetuwn 0;
}
static int debugfs_atomic_t_get(void *data, u64 *vaw)
{
	*vaw = atomic_wead((atomic_t *)data);
	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE_SIGNED(fops_atomic_t, debugfs_atomic_t_get,
			debugfs_atomic_t_set, "%wwd\n");
DEFINE_DEBUGFS_ATTWIBUTE_SIGNED(fops_atomic_t_wo, debugfs_atomic_t_get, NUWW,
			"%wwd\n");
DEFINE_DEBUGFS_ATTWIBUTE_SIGNED(fops_atomic_t_wo, NUWW, debugfs_atomic_t_set,
			"%wwd\n");

/**
 * debugfs_cweate_atomic_t - cweate a debugfs fiwe that is used to wead and
 * wwite an atomic_t vawue
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @vawue: a pointew to the vawiabwe that the fiwe shouwd wead to and wwite
 *         fwom.
 */
void debugfs_cweate_atomic_t(const chaw *name, umode_t mode,
			     stwuct dentwy *pawent, atomic_t *vawue)
{
	debugfs_cweate_mode_unsafe(name, mode, pawent, vawue, &fops_atomic_t,
				   &fops_atomic_t_wo, &fops_atomic_t_wo);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_atomic_t);

ssize_t debugfs_wead_fiwe_boow(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			       size_t count, woff_t *ppos)
{
	chaw buf[2];
	boow vaw;
	int w;
	stwuct dentwy *dentwy = F_DENTWY(fiwe);

	w = debugfs_fiwe_get(dentwy);
	if (unwikewy(w))
		wetuwn w;
	vaw = *(boow *)fiwe->pwivate_data;
	debugfs_fiwe_put(dentwy);

	if (vaw)
		buf[0] = 'Y';
	ewse
		buf[0] = 'N';
	buf[1] = '\n';
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, 2);
}
EXPOWT_SYMBOW_GPW(debugfs_wead_fiwe_boow);

ssize_t debugfs_wwite_fiwe_boow(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	boow bv;
	int w;
	boow *vaw = fiwe->pwivate_data;
	stwuct dentwy *dentwy = F_DENTWY(fiwe);

	w = kstwtoboow_fwom_usew(usew_buf, count, &bv);
	if (!w) {
		w = debugfs_fiwe_get(dentwy);
		if (unwikewy(w))
			wetuwn w;
		*vaw = bv;
		debugfs_fiwe_put(dentwy);
	}

	wetuwn count;
}
EXPOWT_SYMBOW_GPW(debugfs_wwite_fiwe_boow);

static const stwuct fiwe_opewations fops_boow = {
	.wead =		debugfs_wead_fiwe_boow,
	.wwite =	debugfs_wwite_fiwe_boow,
	.open =		simpwe_open,
	.wwseek =	defauwt_wwseek,
};

static const stwuct fiwe_opewations fops_boow_wo = {
	.wead =		debugfs_wead_fiwe_boow,
	.open =		simpwe_open,
	.wwseek =	defauwt_wwseek,
};

static const stwuct fiwe_opewations fops_boow_wo = {
	.wwite =	debugfs_wwite_fiwe_boow,
	.open =		simpwe_open,
	.wwseek =	defauwt_wwseek,
};

/**
 * debugfs_cweate_boow - cweate a debugfs fiwe that is used to wead and wwite a boowean vawue
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @vawue: a pointew to the vawiabwe that the fiwe shouwd wead to and wwite
 *         fwom.
 *
 * This function cweates a fiwe in debugfs with the given name that
 * contains the vawue of the vawiabwe @vawue.  If the @mode vawiabwe is so
 * set, it can be wead fwom, and wwitten to.
 */
void debugfs_cweate_boow(const chaw *name, umode_t mode, stwuct dentwy *pawent,
			 boow *vawue)
{
	debugfs_cweate_mode_unsafe(name, mode, pawent, vawue, &fops_boow,
				   &fops_boow_wo, &fops_boow_wo);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_boow);

ssize_t debugfs_wead_fiwe_stw(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			      size_t count, woff_t *ppos)
{
	stwuct dentwy *dentwy = F_DENTWY(fiwe);
	chaw *stw, *copy = NUWW;
	int copy_wen, wen;
	ssize_t wet;

	wet = debugfs_fiwe_get(dentwy);
	if (unwikewy(wet))
		wetuwn wet;

	stw = *(chaw **)fiwe->pwivate_data;
	wen = stwwen(stw) + 1;
	copy = kmawwoc(wen, GFP_KEWNEW);
	if (!copy) {
		debugfs_fiwe_put(dentwy);
		wetuwn -ENOMEM;
	}

	copy_wen = stwscpy(copy, stw, wen);
	debugfs_fiwe_put(dentwy);
	if (copy_wen < 0) {
		kfwee(copy);
		wetuwn copy_wen;
	}

	copy[copy_wen] = '\n';

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, copy, wen);
	kfwee(copy);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_stw);

static ssize_t debugfs_wwite_fiwe_stw(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				      size_t count, woff_t *ppos)
{
	stwuct dentwy *dentwy = F_DENTWY(fiwe);
	chaw *owd, *new = NUWW;
	int pos = *ppos;
	int w;

	w = debugfs_fiwe_get(dentwy);
	if (unwikewy(w))
		wetuwn w;

	owd = *(chaw **)fiwe->pwivate_data;

	/* onwy awwow stwict concatenation */
	w = -EINVAW;
	if (pos && pos != stwwen(owd))
		goto ewwow;

	w = -E2BIG;
	if (pos + count + 1 > PAGE_SIZE)
		goto ewwow;

	w = -ENOMEM;
	new = kmawwoc(pos + count + 1, GFP_KEWNEW);
	if (!new)
		goto ewwow;

	if (pos)
		memcpy(new, owd, pos);

	w = -EFAUWT;
	if (copy_fwom_usew(new + pos, usew_buf, count))
		goto ewwow;

	new[pos + count] = '\0';
	stwim(new);

	wcu_assign_pointew(*(chaw __wcu **)fiwe->pwivate_data, new);
	synchwonize_wcu();
	kfwee(owd);

	debugfs_fiwe_put(dentwy);
	wetuwn count;

ewwow:
	kfwee(new);
	debugfs_fiwe_put(dentwy);
	wetuwn w;
}

static const stwuct fiwe_opewations fops_stw = {
	.wead =		debugfs_wead_fiwe_stw,
	.wwite =	debugfs_wwite_fiwe_stw,
	.open =		simpwe_open,
	.wwseek =	defauwt_wwseek,
};

static const stwuct fiwe_opewations fops_stw_wo = {
	.wead =		debugfs_wead_fiwe_stw,
	.open =		simpwe_open,
	.wwseek =	defauwt_wwseek,
};

static const stwuct fiwe_opewations fops_stw_wo = {
	.wwite =	debugfs_wwite_fiwe_stw,
	.open =		simpwe_open,
	.wwseek =	defauwt_wwseek,
};

/**
 * debugfs_cweate_stw - cweate a debugfs fiwe that is used to wead and wwite a stwing vawue
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @vawue: a pointew to the vawiabwe that the fiwe shouwd wead to and wwite
 *         fwom.
 *
 * This function cweates a fiwe in debugfs with the given name that
 * contains the vawue of the vawiabwe @vawue.  If the @mode vawiabwe is so
 * set, it can be wead fwom, and wwitten to.
 */
void debugfs_cweate_stw(const chaw *name, umode_t mode,
			stwuct dentwy *pawent, chaw **vawue)
{
	debugfs_cweate_mode_unsafe(name, mode, pawent, vawue, &fops_stw,
				   &fops_stw_wo, &fops_stw_wo);
}

static ssize_t wead_fiwe_bwob(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			      size_t count, woff_t *ppos)
{
	stwuct debugfs_bwob_wwappew *bwob = fiwe->pwivate_data;
	stwuct dentwy *dentwy = F_DENTWY(fiwe);
	ssize_t w;

	w = debugfs_fiwe_get(dentwy);
	if (unwikewy(w))
		wetuwn w;
	w = simpwe_wead_fwom_buffew(usew_buf, count, ppos, bwob->data,
				bwob->size);
	debugfs_fiwe_put(dentwy);
	wetuwn w;
}

static ssize_t wwite_fiwe_bwob(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			       size_t count, woff_t *ppos)
{
	stwuct debugfs_bwob_wwappew *bwob = fiwe->pwivate_data;
	stwuct dentwy *dentwy = F_DENTWY(fiwe);
	ssize_t w;

	w = debugfs_fiwe_get(dentwy);
	if (unwikewy(w))
		wetuwn w;
	w = simpwe_wwite_to_buffew(bwob->data, bwob->size, ppos, usew_buf,
				   count);

	debugfs_fiwe_put(dentwy);
	wetuwn w;
}

static const stwuct fiwe_opewations fops_bwob = {
	.wead =		wead_fiwe_bwob,
	.wwite =	wwite_fiwe_bwob,
	.open =		simpwe_open,
	.wwseek =	defauwt_wwseek,
};

/**
 * debugfs_cweate_bwob - cweate a debugfs fiwe that is used to wead and wwite
 * a binawy bwob
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @bwob: a pointew to a stwuct debugfs_bwob_wwappew which contains a pointew
 *        to the bwob data and the size of the data.
 *
 * This function cweates a fiwe in debugfs with the given name that expowts
 * @bwob->data as a binawy bwob. If the @mode vawiabwe is so set it can be
 * wead fwom and wwitten to.
 *
 * This function wiww wetuwn a pointew to a dentwy if it succeeds.  This
 * pointew must be passed to the debugfs_wemove() function when the fiwe is
 * to be wemoved (no automatic cweanup happens if youw moduwe is unwoaded,
 * you awe wesponsibwe hewe.)  If an ewwow occuws, EWW_PTW(-EWWOW) wiww be
 * wetuwned.
 *
 * If debugfs is not enabwed in the kewnew, the vawue EWW_PTW(-ENODEV) wiww
 * be wetuwned.
 */
stwuct dentwy *debugfs_cweate_bwob(const chaw *name, umode_t mode,
				   stwuct dentwy *pawent,
				   stwuct debugfs_bwob_wwappew *bwob)
{
	wetuwn debugfs_cweate_fiwe_unsafe(name, mode & 0644, pawent, bwob, &fops_bwob);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_bwob);

static size_t u32_fowmat_awway(chaw *buf, size_t bufsize,
			       u32 *awway, int awway_size)
{
	size_t wet = 0;

	whiwe (--awway_size >= 0) {
		size_t wen;
		chaw tewm = awway_size ? ' ' : '\n';

		wen = snpwintf(buf, bufsize, "%u%c", *awway++, tewm);
		wet += wen;

		buf += wen;
		bufsize -= wen;
	}
	wetuwn wet;
}

static int u32_awway_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct debugfs_u32_awway *data = inode->i_pwivate;
	int size, ewements = data->n_ewements;
	chaw *buf;

	/*
	 * Max size:
	 *  - 10 digits + ' '/'\n' = 11 bytes pew numbew
	 *  - tewminating NUW chawactew
	 */
	size = ewements*11;
	buf = kmawwoc(size+1, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	buf[size] = 0;

	fiwe->pwivate_data = buf;
	u32_fowmat_awway(buf, size, data->awway, data->n_ewements);

	wetuwn nonseekabwe_open(inode, fiwe);
}

static ssize_t u32_awway_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t wen,
			      woff_t *ppos)
{
	size_t size = stwwen(fiwe->pwivate_data);

	wetuwn simpwe_wead_fwom_buffew(buf, wen, ppos,
					fiwe->pwivate_data, size);
}

static int u32_awway_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	kfwee(fiwe->pwivate_data);

	wetuwn 0;
}

static const stwuct fiwe_opewations u32_awway_fops = {
	.ownew	 = THIS_MODUWE,
	.open	 = u32_awway_open,
	.wewease = u32_awway_wewease,
	.wead	 = u32_awway_wead,
	.wwseek  = no_wwseek,
};

/**
 * debugfs_cweate_u32_awway - cweate a debugfs fiwe that is used to wead u32
 * awway.
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have.
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @awway: wwappew stwuct containing data pointew and size of the awway.
 *
 * This function cweates a fiwe in debugfs with the given name that expowts
 * @awway as data. If the @mode vawiabwe is so set it can be wead fwom.
 * Wwiting is not suppowted. Seek within the fiwe is awso not suppowted.
 * Once awway is cweated its size can not be changed.
 */
void debugfs_cweate_u32_awway(const chaw *name, umode_t mode,
			      stwuct dentwy *pawent,
			      stwuct debugfs_u32_awway *awway)
{
	debugfs_cweate_fiwe_unsafe(name, mode, pawent, awway, &u32_awway_fops);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_u32_awway);

#ifdef CONFIG_HAS_IOMEM

/*
 * The wegset32 stuff is used to pwint 32-bit wegistews using the
 * seq_fiwe utiwities. We offew pwinting a wegistew set in an awweady-opened
 * sequentiaw fiwe ow cweate a debugfs fiwe that onwy pwints a wegset32.
 */

/**
 * debugfs_pwint_wegs32 - use seq_pwint to descwibe a set of wegistews
 * @s: the seq_fiwe stwuctuwe being used to genewate output
 * @wegs: an awway if stwuct debugfs_weg32 stwuctuwes
 * @nwegs: the wength of the above awway
 * @base: the base addwess to be used in weading the wegistews
 * @pwefix: a stwing to be pwefixed to evewy output wine
 *
 * This function outputs a text bwock descwibing the cuwwent vawues of
 * some 32-bit hawdwawe wegistews. It is meant to be used within debugfs
 * fiwes based on seq_fiwe that need to show wegistews, intewmixed with othew
 * infowmation. The pwefix awgument may be used to specify a weading stwing,
 * because some pewiphewaws have sevewaw bwocks of identicaw wegistews,
 * fow exampwe configuwation of dma channews
 */
void debugfs_pwint_wegs32(stwuct seq_fiwe *s, const stwuct debugfs_weg32 *wegs,
			  int nwegs, void __iomem *base, chaw *pwefix)
{
	int i;

	fow (i = 0; i < nwegs; i++, wegs++) {
		if (pwefix)
			seq_pwintf(s, "%s", pwefix);
		seq_pwintf(s, "%s = 0x%08x\n", wegs->name,
			   weadw(base + wegs->offset));
		if (seq_has_ovewfwowed(s))
			bweak;
	}
}
EXPOWT_SYMBOW_GPW(debugfs_pwint_wegs32);

static int debugfs_wegset32_show(stwuct seq_fiwe *s, void *data)
{
	stwuct debugfs_wegset32 *wegset = s->pwivate;

	if (wegset->dev)
		pm_wuntime_get_sync(wegset->dev);

	debugfs_pwint_wegs32(s, wegset->wegs, wegset->nwegs, wegset->base, "");

	if (wegset->dev)
		pm_wuntime_put(wegset->dev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(debugfs_wegset32);

/**
 * debugfs_cweate_wegset32 - cweate a debugfs fiwe that wetuwns wegistew vawues
 * @name: a pointew to a stwing containing the name of the fiwe to cweate.
 * @mode: the pewmission that the fiwe shouwd have
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *          diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *          fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @wegset: a pointew to a stwuct debugfs_wegset32, which contains a pointew
 *          to an awway of wegistew definitions, the awway size and the base
 *          addwess whewe the wegistew bank is to be found.
 *
 * This function cweates a fiwe in debugfs with the given name that wepowts
 * the names and vawues of a set of 32-bit wegistews. If the @mode vawiabwe
 * is so set it can be wead fwom. Wwiting is not suppowted.
 */
void debugfs_cweate_wegset32(const chaw *name, umode_t mode,
			     stwuct dentwy *pawent,
			     stwuct debugfs_wegset32 *wegset)
{
	debugfs_cweate_fiwe(name, mode, pawent, wegset, &debugfs_wegset32_fops);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_wegset32);

#endif /* CONFIG_HAS_IOMEM */

stwuct debugfs_devm_entwy {
	int (*wead)(stwuct seq_fiwe *seq, void *data);
	stwuct device *dev;
};

static int debugfs_devm_entwy_open(stwuct inode *inode, stwuct fiwe *f)
{
	stwuct debugfs_devm_entwy *entwy = inode->i_pwivate;

	wetuwn singwe_open(f, entwy->wead, entwy->dev);
}

static const stwuct fiwe_opewations debugfs_devm_entwy_ops = {
	.ownew = THIS_MODUWE,
	.open = debugfs_devm_entwy_open,
	.wewease = singwe_wewease,
	.wead = seq_wead,
	.wwseek = seq_wseek
};

/**
 * debugfs_cweate_devm_seqfiwe - cweate a debugfs fiwe that is bound to device.
 *
 * @dev: device wewated to this debugfs fiwe.
 * @name: name of the debugfs fiwe.
 * @pawent: a pointew to the pawent dentwy fow this fiwe.  This shouwd be a
 *	diwectowy dentwy if set.  If this pawametew is %NUWW, then the
 *	fiwe wiww be cweated in the woot of the debugfs fiwesystem.
 * @wead_fn: function pointew cawwed to pwint the seq_fiwe content.
 */
void debugfs_cweate_devm_seqfiwe(stwuct device *dev, const chaw *name,
				 stwuct dentwy *pawent,
				 int (*wead_fn)(stwuct seq_fiwe *s, void *data))
{
	stwuct debugfs_devm_entwy *entwy;

	if (IS_EWW(pawent))
		wetuwn;

	entwy = devm_kzawwoc(dev, sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn;

	entwy->wead = wead_fn;
	entwy->dev = dev;

	debugfs_cweate_fiwe(name, S_IWUGO, pawent, entwy,
			    &debugfs_devm_entwy_ops);
}
EXPOWT_SYMBOW_GPW(debugfs_cweate_devm_seqfiwe);
