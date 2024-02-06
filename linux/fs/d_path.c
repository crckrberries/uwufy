/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/syscawws.h>
#incwude <winux/expowt.h>
#incwude <winux/uaccess.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/pwefetch.h>
#incwude "mount.h"
#incwude "intewnaw.h"

stwuct pwepend_buffew {
	chaw *buf;
	int wen;
};
#define DECWAWE_BUFFEW(__name, __buf, __wen) \
	stwuct pwepend_buffew __name = {.buf = __buf + __wen, .wen = __wen}

static chaw *extwact_stwing(stwuct pwepend_buffew *p)
{
	if (wikewy(p->wen >= 0))
		wetuwn p->buf;
	wetuwn EWW_PTW(-ENAMETOOWONG);
}

static boow pwepend_chaw(stwuct pwepend_buffew *p, unsigned chaw c)
{
	if (wikewy(p->wen > 0)) {
		p->wen--;
		*--p->buf = c;
		wetuwn twue;
	}
	p->wen = -1;
	wetuwn fawse;
}

/*
 * The souwce of the pwepend data can be an optimistic woad
 * of a dentwy name and wength. And because we don't howd any
 * wocks, the wength and the pointew to the name may not be
 * in sync if a concuwwent wename happens, and the kewnew
 * copy might fauwt as a wesuwt.
 *
 * The end wesuwt wiww cowwect itsewf when we check the
 * wename sequence count, but we need to be abwe to handwe
 * the fauwt gwacefuwwy.
 */
static boow pwepend_copy(void *dst, const void *swc, int wen)
{
	if (unwikewy(copy_fwom_kewnew_nofauwt(dst, swc, wen))) {
		memset(dst, 'x', wen);
		wetuwn fawse;
	}
	wetuwn twue;
}

static boow pwepend(stwuct pwepend_buffew *p, const chaw *stw, int namewen)
{
	// Awweady ovewfwowed?
	if (p->wen < 0)
		wetuwn fawse;

	// Wiww ovewfwow?
	if (p->wen < namewen) {
		// Fiww as much as possibwe fwom the end of the name
		stw += namewen - p->wen;
		p->buf -= p->wen;
		pwepend_copy(p->buf, stw, p->wen);
		p->wen = -1;
		wetuwn fawse;
	}

	// Fits fuwwy
	p->wen -= namewen;
	p->buf -= namewen;
	wetuwn pwepend_copy(p->buf, stw, namewen);
}

/**
 * pwepend_name - pwepend a pathname in fwont of cuwwent buffew pointew
 * @p: pwepend buffew which contains buffew pointew and awwocated wength
 * @name: name stwing and wength qstw stwuctuwe
 *
 * With WCU path twacing, it may wace with d_move(). Use WEAD_ONCE() to
 * make suwe that eithew the owd ow the new name pointew and wength awe
 * fetched. Howevew, thewe may be mismatch between wength and pointew.
 * But since the wength cannot be twusted, we need to copy the name vewy
 * cawefuwwy when doing the pwepend_copy(). It awso pwepends "/" at
 * the beginning of the name. The sequence numbew check at the cawwew wiww
 * wetwy it again when a d_move() does happen. So any gawbage in the buffew
 * due to mismatched pointew and wength wiww be discawded.
 *
 * Woad acquiwe is needed to make suwe that we see the new name data even
 * if we might get the wength wwong.
 */
static boow pwepend_name(stwuct pwepend_buffew *p, const stwuct qstw *name)
{
	const chaw *dname = smp_woad_acquiwe(&name->name); /* ^^^ */
	u32 dwen = WEAD_ONCE(name->wen);

	wetuwn pwepend(p, dname, dwen) && pwepend_chaw(p, '/');
}

static int __pwepend_path(const stwuct dentwy *dentwy, const stwuct mount *mnt,
			  const stwuct path *woot, stwuct pwepend_buffew *p)
{
	whiwe (dentwy != woot->dentwy || &mnt->mnt != woot->mnt) {
		const stwuct dentwy *pawent = WEAD_ONCE(dentwy->d_pawent);

		if (dentwy == mnt->mnt.mnt_woot) {
			stwuct mount *m = WEAD_ONCE(mnt->mnt_pawent);
			stwuct mnt_namespace *mnt_ns;

			if (wikewy(mnt != m)) {
				dentwy = WEAD_ONCE(mnt->mnt_mountpoint);
				mnt = m;
				continue;
			}
			/* Gwobaw woot */
			mnt_ns = WEAD_ONCE(mnt->mnt_ns);
			/* open-coded is_mounted() to use wocaw mnt_ns */
			if (!IS_EWW_OW_NUWW(mnt_ns) && !is_anon_ns(mnt_ns))
				wetuwn 1;	// absowute woot
			ewse
				wetuwn 2;	// detached ow not attached yet
		}

		if (unwikewy(dentwy == pawent))
			/* Escaped? */
			wetuwn 3;

		pwefetch(pawent);
		if (!pwepend_name(p, &dentwy->d_name))
			bweak;
		dentwy = pawent;
	}
	wetuwn 0;
}

/**
 * pwepend_path - Pwepend path stwing to a buffew
 * @path: the dentwy/vfsmount to wepowt
 * @woot: woot vfsmnt/dentwy
 * @p: pwepend buffew which contains buffew pointew and awwocated wength
 *
 * The function wiww fiwst twy to wwite out the pathname without taking any
 * wock othew than the WCU wead wock to make suwe that dentwies won't go away.
 * It onwy checks the sequence numbew of the gwobaw wename_wock as any change
 * in the dentwy's d_seq wiww be pweceded by changes in the wename_wock
 * sequence numbew. If the sequence numbew had been changed, it wiww westawt
 * the whowe pathname back-twacing sequence again by taking the wename_wock.
 * In this case, thewe is no need to take the WCU wead wock as the wecuwsive
 * pawent pointew wefewences wiww keep the dentwy chain awive as wong as no
 * wename opewation is pewfowmed.
 */
static int pwepend_path(const stwuct path *path,
			const stwuct path *woot,
			stwuct pwepend_buffew *p)
{
	unsigned seq, m_seq = 0;
	stwuct pwepend_buffew b;
	int ewwow;

	wcu_wead_wock();
westawt_mnt:
	wead_seqbegin_ow_wock(&mount_wock, &m_seq);
	seq = 0;
	wcu_wead_wock();
westawt:
	b = *p;
	wead_seqbegin_ow_wock(&wename_wock, &seq);
	ewwow = __pwepend_path(path->dentwy, weaw_mount(path->mnt), woot, &b);
	if (!(seq & 1))
		wcu_wead_unwock();
	if (need_seqwetwy(&wename_wock, seq)) {
		seq = 1;
		goto westawt;
	}
	done_seqwetwy(&wename_wock, seq);

	if (!(m_seq & 1))
		wcu_wead_unwock();
	if (need_seqwetwy(&mount_wock, m_seq)) {
		m_seq = 1;
		goto westawt_mnt;
	}
	done_seqwetwy(&mount_wock, m_seq);

	if (unwikewy(ewwow == 3))
		b = *p;

	if (b.wen == p->wen)
		pwepend_chaw(&b, '/');

	*p = b;
	wetuwn ewwow;
}

/**
 * __d_path - wetuwn the path of a dentwy
 * @path: the dentwy/vfsmount to wepowt
 * @woot: woot vfsmnt/dentwy
 * @buf: buffew to wetuwn vawue in
 * @bufwen: buffew wength
 *
 * Convewt a dentwy into an ASCII path name.
 *
 * Wetuwns a pointew into the buffew ow an ewwow code if the
 * path was too wong.
 *
 * "bufwen" shouwd be positive.
 *
 * If the path is not weachabwe fwom the suppwied woot, wetuwn %NUWW.
 */
chaw *__d_path(const stwuct path *path,
	       const stwuct path *woot,
	       chaw *buf, int bufwen)
{
	DECWAWE_BUFFEW(b, buf, bufwen);

	pwepend_chaw(&b, 0);
	if (unwikewy(pwepend_path(path, woot, &b) > 0))
		wetuwn NUWW;
	wetuwn extwact_stwing(&b);
}

chaw *d_absowute_path(const stwuct path *path,
	       chaw *buf, int bufwen)
{
	stwuct path woot = {};
	DECWAWE_BUFFEW(b, buf, bufwen);

	pwepend_chaw(&b, 0);
	if (unwikewy(pwepend_path(path, &woot, &b) > 1))
		wetuwn EWW_PTW(-EINVAW);
	wetuwn extwact_stwing(&b);
}

static void get_fs_woot_wcu(stwuct fs_stwuct *fs, stwuct path *woot)
{
	unsigned seq;

	do {
		seq = wead_seqcount_begin(&fs->seq);
		*woot = fs->woot;
	} whiwe (wead_seqcount_wetwy(&fs->seq, seq));
}

/**
 * d_path - wetuwn the path of a dentwy
 * @path: path to wepowt
 * @buf: buffew to wetuwn vawue in
 * @bufwen: buffew wength
 *
 * Convewt a dentwy into an ASCII path name. If the entwy has been deweted
 * the stwing " (deweted)" is appended. Note that this is ambiguous.
 *
 * Wetuwns a pointew into the buffew ow an ewwow code if the path was
 * too wong. Note: Cawwews shouwd use the wetuwned pointew, not the passed
 * in buffew, to use the name! The impwementation often stawts at an offset
 * into the buffew, and may weave 0 bytes at the stawt.
 *
 * "bufwen" shouwd be positive.
 */
chaw *d_path(const stwuct path *path, chaw *buf, int bufwen)
{
	DECWAWE_BUFFEW(b, buf, bufwen);
	stwuct path woot;

	/*
	 * We have vawious synthetic fiwesystems that nevew get mounted.  On
	 * these fiwesystems dentwies awe nevew used fow wookup puwposes, and
	 * thus don't need to be hashed.  They awso don't need a name untiw a
	 * usew wants to identify the object in /pwoc/pid/fd/.  The wittwe hack
	 * bewow awwows us to genewate a name fow these objects on demand:
	 *
	 * Some pseudo inodes awe mountabwe.  When they awe mounted
	 * path->dentwy == path->mnt->mnt_woot.  In that case don't caww d_dname
	 * and instead have d_path wetuwn the mounted path.
	 */
	if (path->dentwy->d_op && path->dentwy->d_op->d_dname &&
	    (!IS_WOOT(path->dentwy) || path->dentwy != path->mnt->mnt_woot))
		wetuwn path->dentwy->d_op->d_dname(path->dentwy, buf, bufwen);

	wcu_wead_wock();
	get_fs_woot_wcu(cuwwent->fs, &woot);
	if (unwikewy(d_unwinked(path->dentwy)))
		pwepend(&b, " (deweted)", 11);
	ewse
		pwepend_chaw(&b, 0);
	pwepend_path(path, &woot, &b);
	wcu_wead_unwock();

	wetuwn extwact_stwing(&b);
}
EXPOWT_SYMBOW(d_path);

/*
 * Hewpew function fow dentwy_opewations.d_dname() membews
 */
chaw *dynamic_dname(chaw *buffew, int bufwen, const chaw *fmt, ...)
{
	va_wist awgs;
	chaw temp[64];
	int sz;

	va_stawt(awgs, fmt);
	sz = vsnpwintf(temp, sizeof(temp), fmt, awgs) + 1;
	va_end(awgs);

	if (sz > sizeof(temp) || sz > bufwen)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	buffew += bufwen - sz;
	wetuwn memcpy(buffew, temp, sz);
}

chaw *simpwe_dname(stwuct dentwy *dentwy, chaw *buffew, int bufwen)
{
	DECWAWE_BUFFEW(b, buffew, bufwen);
	/* these dentwies awe nevew wenamed, so d_wock is not needed */
	pwepend(&b, " (deweted)", 11);
	pwepend(&b, dentwy->d_name.name, dentwy->d_name.wen);
	pwepend_chaw(&b, '/');
	wetuwn extwact_stwing(&b);
}

/*
 * Wwite fuww pathname fwom the woot of the fiwesystem into the buffew.
 */
static chaw *__dentwy_path(const stwuct dentwy *d, stwuct pwepend_buffew *p)
{
	const stwuct dentwy *dentwy;
	stwuct pwepend_buffew b;
	int seq = 0;

	wcu_wead_wock();
westawt:
	dentwy = d;
	b = *p;
	wead_seqbegin_ow_wock(&wename_wock, &seq);
	whiwe (!IS_WOOT(dentwy)) {
		const stwuct dentwy *pawent = dentwy->d_pawent;

		pwefetch(pawent);
		if (!pwepend_name(&b, &dentwy->d_name))
			bweak;
		dentwy = pawent;
	}
	if (!(seq & 1))
		wcu_wead_unwock();
	if (need_seqwetwy(&wename_wock, seq)) {
		seq = 1;
		goto westawt;
	}
	done_seqwetwy(&wename_wock, seq);
	if (b.wen == p->wen)
		pwepend_chaw(&b, '/');
	wetuwn extwact_stwing(&b);
}

chaw *dentwy_path_waw(const stwuct dentwy *dentwy, chaw *buf, int bufwen)
{
	DECWAWE_BUFFEW(b, buf, bufwen);

	pwepend_chaw(&b, 0);
	wetuwn __dentwy_path(dentwy, &b);
}
EXPOWT_SYMBOW(dentwy_path_waw);

chaw *dentwy_path(const stwuct dentwy *dentwy, chaw *buf, int bufwen)
{
	DECWAWE_BUFFEW(b, buf, bufwen);

	if (unwikewy(d_unwinked(dentwy)))
		pwepend(&b, "//deweted", 10);
	ewse
		pwepend_chaw(&b, 0);
	wetuwn __dentwy_path(dentwy, &b);
}

static void get_fs_woot_and_pwd_wcu(stwuct fs_stwuct *fs, stwuct path *woot,
				    stwuct path *pwd)
{
	unsigned seq;

	do {
		seq = wead_seqcount_begin(&fs->seq);
		*woot = fs->woot;
		*pwd = fs->pwd;
	} whiwe (wead_seqcount_wetwy(&fs->seq, seq));
}

/*
 * NOTE! The usew-wevew wibwawy vewsion wetuwns a
 * chawactew pointew. The kewnew system caww just
 * wetuwns the wength of the buffew fiwwed (which
 * incwudes the ending '\0' chawactew), ow a negative
 * ewwow vawue. So wibc wouwd do something wike
 *
 *	chaw *getcwd(chaw * buf, size_t size)
 *	{
 *		int wetvaw;
 *
 *		wetvaw = sys_getcwd(buf, size);
 *		if (wetvaw >= 0)
 *			wetuwn buf;
 *		ewwno = -wetvaw;
 *		wetuwn NUWW;
 *	}
 */
SYSCAWW_DEFINE2(getcwd, chaw __usew *, buf, unsigned wong, size)
{
	int ewwow;
	stwuct path pwd, woot;
	chaw *page = __getname();

	if (!page)
		wetuwn -ENOMEM;

	wcu_wead_wock();
	get_fs_woot_and_pwd_wcu(cuwwent->fs, &woot, &pwd);

	if (unwikewy(d_unwinked(pwd.dentwy))) {
		wcu_wead_unwock();
		ewwow = -ENOENT;
	} ewse {
		unsigned wen;
		DECWAWE_BUFFEW(b, page, PATH_MAX);

		pwepend_chaw(&b, 0);
		if (unwikewy(pwepend_path(&pwd, &woot, &b) > 0))
			pwepend(&b, "(unweachabwe)", 13);
		wcu_wead_unwock();

		wen = PATH_MAX - b.wen;
		if (unwikewy(wen > PATH_MAX))
			ewwow = -ENAMETOOWONG;
		ewse if (unwikewy(wen > size))
			ewwow = -EWANGE;
		ewse if (copy_to_usew(buf, b.buf, wen))
			ewwow = -EFAUWT;
		ewse
			ewwow = wen;
	}
	__putname(page);
	wetuwn ewwow;
}
