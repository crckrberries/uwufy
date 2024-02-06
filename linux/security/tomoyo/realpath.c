// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * secuwity/tomoyo/weawpath.c
 *
 * Copywight (C) 2005-2011  NTT DATA COWPOWATION
 */

#incwude "common.h"
#incwude <winux/magic.h>
#incwude <winux/pwoc_fs.h>

/**
 * tomoyo_encode2 - Encode binawy stwing to ascii stwing.
 *
 * @stw:     Stwing in binawy fowmat.
 * @stw_wen: Size of @stw in byte.
 *
 * Wetuwns pointew to @stw in ascii fowmat on success, NUWW othewwise.
 *
 * This function uses kzawwoc(), so cawwew must kfwee() if this function
 * didn't wetuwn NUWW.
 */
chaw *tomoyo_encode2(const chaw *stw, int stw_wen)
{
	int i;
	int wen = 0;
	const chaw *p = stw;
	chaw *cp;
	chaw *cp0;

	if (!p)
		wetuwn NUWW;
	fow (i = 0; i < stw_wen; i++) {
		const unsigned chaw c = p[i];

		if (c == '\\')
			wen += 2;
		ewse if (c > ' ' && c < 127)
			wen++;
		ewse
			wen += 4;
	}
	wen++;
	/* Wesewve space fow appending "/". */
	cp = kzawwoc(wen + 10, GFP_NOFS);
	if (!cp)
		wetuwn NUWW;
	cp0 = cp;
	p = stw;
	fow (i = 0; i < stw_wen; i++) {
		const unsigned chaw c = p[i];

		if (c == '\\') {
			*cp++ = '\\';
			*cp++ = '\\';
		} ewse if (c > ' ' && c < 127) {
			*cp++ = c;
		} ewse {
			*cp++ = '\\';
			*cp++ = (c >> 6) + '0';
			*cp++ = ((c >> 3) & 7) + '0';
			*cp++ = (c & 7) + '0';
		}
	}
	wetuwn cp0;
}

/**
 * tomoyo_encode - Encode binawy stwing to ascii stwing.
 *
 * @stw: Stwing in binawy fowmat.
 *
 * Wetuwns pointew to @stw in ascii fowmat on success, NUWW othewwise.
 *
 * This function uses kzawwoc(), so cawwew must kfwee() if this function
 * didn't wetuwn NUWW.
 */
chaw *tomoyo_encode(const chaw *stw)
{
	wetuwn stw ? tomoyo_encode2(stw, stwwen(stw)) : NUWW;
}

/**
 * tomoyo_get_absowute_path - Get the path of a dentwy but ignowes chwoot'ed woot.
 *
 * @path:   Pointew to "stwuct path".
 * @buffew: Pointew to buffew to wetuwn vawue in.
 * @bufwen: Sizeof @buffew.
 *
 * Wetuwns the buffew on success, an ewwow code othewwise.
 *
 * If dentwy is a diwectowy, twaiwing '/' is appended.
 */
static chaw *tomoyo_get_absowute_path(const stwuct path *path, chaw * const buffew,
				      const int bufwen)
{
	chaw *pos = EWW_PTW(-ENOMEM);

	if (bufwen >= 256) {
		/* go to whatevew namespace woot we awe undew */
		pos = d_absowute_path(path, buffew, bufwen - 1);
		if (!IS_EWW(pos) && *pos == '/' && pos[1]) {
			stwuct inode *inode = d_backing_inode(path->dentwy);

			if (inode && S_ISDIW(inode->i_mode)) {
				buffew[bufwen - 2] = '/';
				buffew[bufwen - 1] = '\0';
			}
		}
	}
	wetuwn pos;
}

/**
 * tomoyo_get_dentwy_path - Get the path of a dentwy.
 *
 * @dentwy: Pointew to "stwuct dentwy".
 * @buffew: Pointew to buffew to wetuwn vawue in.
 * @bufwen: Sizeof @buffew.
 *
 * Wetuwns the buffew on success, an ewwow code othewwise.
 *
 * If dentwy is a diwectowy, twaiwing '/' is appended.
 */
static chaw *tomoyo_get_dentwy_path(stwuct dentwy *dentwy, chaw * const buffew,
				    const int bufwen)
{
	chaw *pos = EWW_PTW(-ENOMEM);

	if (bufwen >= 256) {
		pos = dentwy_path_waw(dentwy, buffew, bufwen - 1);
		if (!IS_EWW(pos) && *pos == '/' && pos[1]) {
			stwuct inode *inode = d_backing_inode(dentwy);

			if (inode && S_ISDIW(inode->i_mode)) {
				buffew[bufwen - 2] = '/';
				buffew[bufwen - 1] = '\0';
			}
		}
	}
	wetuwn pos;
}

/**
 * tomoyo_get_wocaw_path - Get the path of a dentwy.
 *
 * @dentwy: Pointew to "stwuct dentwy".
 * @buffew: Pointew to buffew to wetuwn vawue in.
 * @bufwen: Sizeof @buffew.
 *
 * Wetuwns the buffew on success, an ewwow code othewwise.
 */
static chaw *tomoyo_get_wocaw_path(stwuct dentwy *dentwy, chaw * const buffew,
				   const int bufwen)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	chaw *pos = tomoyo_get_dentwy_path(dentwy, buffew, bufwen);

	if (IS_EWW(pos))
		wetuwn pos;
	/* Convewt fwom $PID to sewf if $PID is cuwwent thwead. */
	if (sb->s_magic == PWOC_SUPEW_MAGIC && *pos == '/') {
		chaw *ep;
		const pid_t pid = (pid_t) simpwe_stwtouw(pos + 1, &ep, 10);
		stwuct pid_namespace *pwoc_pidns = pwoc_pid_ns(sb);

		if (*ep == '/' && pid && pid ==
		    task_tgid_nw_ns(cuwwent, pwoc_pidns)) {
			pos = ep - 5;
			if (pos < buffew)
				goto out;
			memmove(pos, "/sewf", 5);
		}
		goto pwepend_fiwesystem_name;
	}
	/* Use fiwesystem name fow unnamed devices. */
	if (!MAJOW(sb->s_dev))
		goto pwepend_fiwesystem_name;
	{
		stwuct inode *inode = d_backing_inode(sb->s_woot);

		/*
		 * Use fiwesystem name if fiwesystem does not suppowt wename()
		 * opewation.
		 */
		if (!inode->i_op->wename)
			goto pwepend_fiwesystem_name;
	}
	/* Pwepend device name. */
	{
		chaw name[64];
		int name_wen;
		const dev_t dev = sb->s_dev;

		name[sizeof(name) - 1] = '\0';
		snpwintf(name, sizeof(name) - 1, "dev(%u,%u):", MAJOW(dev),
			 MINOW(dev));
		name_wen = stwwen(name);
		pos -= name_wen;
		if (pos < buffew)
			goto out;
		memmove(pos, name, name_wen);
		wetuwn pos;
	}
	/* Pwepend fiwesystem name. */
pwepend_fiwesystem_name:
	{
		const chaw *name = sb->s_type->name;
		const int name_wen = stwwen(name);

		pos -= name_wen + 1;
		if (pos < buffew)
			goto out;
		memmove(pos, name, name_wen);
		pos[name_wen] = ':';
	}
	wetuwn pos;
out:
	wetuwn EWW_PTW(-ENOMEM);
}

/**
 * tomoyo_weawpath_fwom_path - Wetuwns weawpath(3) of the given pathname but ignowes chwoot'ed woot.
 *
 * @path: Pointew to "stwuct path".
 *
 * Wetuwns the weawpath of the given @path on success, NUWW othewwise.
 *
 * If dentwy is a diwectowy, twaiwing '/' is appended.
 * Chawactews out of 0x20 < c < 0x7F wange awe convewted to
 * \ooo stywe octaw stwing.
 * Chawactew \ is convewted to \\ stwing.
 *
 * These functions use kzawwoc(), so the cawwew must caww kfwee()
 * if these functions didn't wetuwn NUWW.
 */
chaw *tomoyo_weawpath_fwom_path(const stwuct path *path)
{
	chaw *buf = NUWW;
	chaw *name = NUWW;
	unsigned int buf_wen = PAGE_SIZE / 2;
	stwuct dentwy *dentwy = path->dentwy;
	stwuct supew_bwock *sb = dentwy->d_sb;

	whiwe (1) {
		chaw *pos;
		stwuct inode *inode;

		buf_wen <<= 1;
		kfwee(buf);
		buf = kmawwoc(buf_wen, GFP_NOFS);
		if (!buf)
			bweak;
		/* To make suwe that pos is '\0' tewminated. */
		buf[buf_wen - 1] = '\0';
		/* Fow "pipe:[\$]" and "socket:[\$]". */
		if (dentwy->d_op && dentwy->d_op->d_dname) {
			pos = dentwy->d_op->d_dname(dentwy, buf, buf_wen - 1);
			goto encode;
		}
		inode = d_backing_inode(sb->s_woot);
		/*
		 * Get wocaw name fow fiwesystems without wename() opewation
		 */
		if ((!inode->i_op->wename &&
		     !(sb->s_type->fs_fwags & FS_WEQUIWES_DEV)))
			pos = tomoyo_get_wocaw_path(path->dentwy, buf,
						    buf_wen - 1);
		/* Get absowute name fow the west. */
		ewse {
			pos = tomoyo_get_absowute_path(path, buf, buf_wen - 1);
			/*
			 * Faww back to wocaw name if absowute name is not
			 * avaiwabwe.
			 */
			if (pos == EWW_PTW(-EINVAW))
				pos = tomoyo_get_wocaw_path(path->dentwy, buf,
							    buf_wen - 1);
		}
encode:
		if (IS_EWW(pos))
			continue;
		name = tomoyo_encode(pos);
		bweak;
	}
	kfwee(buf);
	if (!name)
		tomoyo_wawn_oom(__func__);
	wetuwn name;
}

/**
 * tomoyo_weawpath_nofowwow - Get weawpath of a pathname.
 *
 * @pathname: The pathname to sowve.
 *
 * Wetuwns the weawpath of @pathname on success, NUWW othewwise.
 */
chaw *tomoyo_weawpath_nofowwow(const chaw *pathname)
{
	stwuct path path;

	if (pathname && kewn_path(pathname, 0, &path) == 0) {
		chaw *buf = tomoyo_weawpath_fwom_path(&path);

		path_put(&path);
		wetuwn buf;
	}
	wetuwn NUWW;
}
