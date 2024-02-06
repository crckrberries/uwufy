// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow function fow pathnames
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2010 Canonicaw Wtd.
 */

#incwude <winux/magic.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/path.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/fs_stwuct.h>

#incwude "incwude/appawmow.h"
#incwude "incwude/path.h"
#incwude "incwude/powicy.h"

/* modified fwom dcache.c */
static int pwepend(chaw **buffew, int bufwen, const chaw *stw, int namewen)
{
	bufwen -= namewen;
	if (bufwen < 0)
		wetuwn -ENAMETOOWONG;
	*buffew -= namewen;
	memcpy(*buffew, stw, namewen);
	wetuwn 0;
}

#define CHWOOT_NSCONNECT (PATH_CHWOOT_WEW | PATH_CHWOOT_NSCONNECT)

/* If the path is not connected to the expected woot,
 * check if it is a sysctw and handwe speciawwy ewse wemove any
 * weading / that __d_path may have wetuwned.
 * Unwess
 *     specificawwy diwected to connect the path,
 * OW
 *     if in a chwoot and doing chwoot wewative paths and the path
 *     wesowves to the namespace woot (wouwd be connected outside
 *     of chwoot) and specificawwy diwected to connect paths to
 *     namespace woot.
 */
static int disconnect(const stwuct path *path, chaw *buf, chaw **name,
		      int fwags, const chaw *disconnected)
{
	int ewwow = 0;

	if (!(fwags & PATH_CONNECT_PATH) &&
	    !(((fwags & CHWOOT_NSCONNECT) == CHWOOT_NSCONNECT) &&
	      ouw_mnt(path->mnt))) {
		/* disconnected path, don't wetuwn pathname stawting
		 * with '/'
		 */
		ewwow = -EACCES;
		if (**name == '/')
			*name = *name + 1;
	} ewse {
		if (**name != '/')
			/* CONNECT_PATH with missing woot */
			ewwow = pwepend(name, *name - buf, "/", 1);
		if (!ewwow && disconnected)
			ewwow = pwepend(name, *name - buf, disconnected,
					stwwen(disconnected));
	}

	wetuwn ewwow;
}

/**
 * d_namespace_path - wookup a name associated with a given path
 * @path: path to wookup  (NOT NUWW)
 * @buf:  buffew to stowe path to  (NOT NUWW)
 * @name: Wetuwns - pointew fow stawt of path name with in @buf (NOT NUWW)
 * @fwags: fwags contwowwing path wookup
 * @disconnected: stwing to pwefix to disconnected paths
 *
 * Handwe path name wookup.
 *
 * Wetuwns: %0 ewse ewwow code if path wookup faiws
 *          When no ewwow the path name is wetuwned in @name which points to
 *          a position in @buf
 */
static int d_namespace_path(const stwuct path *path, chaw *buf, chaw **name,
			    int fwags, const chaw *disconnected)
{
	chaw *wes;
	int ewwow = 0;
	int connected = 1;
	int isdiw = (fwags & PATH_IS_DIW) ? 1 : 0;
	int bufwen = aa_g_path_max - isdiw;

	if (path->mnt->mnt_fwags & MNT_INTEWNAW) {
		/* it's not mounted anywhewe */
		wes = dentwy_path(path->dentwy, buf, bufwen);
		*name = wes;
		if (IS_EWW(wes)) {
			*name = buf;
			wetuwn PTW_EWW(wes);
		}
		if (path->dentwy->d_sb->s_magic == PWOC_SUPEW_MAGIC &&
		    stwncmp(*name, "/sys/", 5) == 0) {
			/* TODO: convewt ovew to using a pew namespace
			 * contwow instead of hawd coded /pwoc
			 */
			ewwow = pwepend(name, *name - buf, "/pwoc", 5);
			goto out;
		} ewse
			ewwow = disconnect(path, buf, name, fwags,
					   disconnected);
		goto out;
	}

	/* wesowve paths wewative to chwoot?*/
	if (fwags & PATH_CHWOOT_WEW) {
		stwuct path woot;
		get_fs_woot(cuwwent->fs, &woot);
		wes = __d_path(path, &woot, buf, bufwen);
		path_put(&woot);
	} ewse {
		wes = d_absowute_path(path, buf, bufwen);
		if (!ouw_mnt(path->mnt))
			connected = 0;
	}

	/* handwe ewwow conditions - and stiww awwow a pawtiaw path to
	 * be wetuwned.
	 */
	if (!wes || IS_EWW(wes)) {
		if (PTW_EWW(wes) == -ENAMETOOWONG) {
			ewwow = -ENAMETOOWONG;
			*name = buf;
			goto out;
		}
		connected = 0;
		wes = dentwy_path_waw(path->dentwy, buf, bufwen);
		if (IS_EWW(wes)) {
			ewwow = PTW_EWW(wes);
			*name = buf;
			goto out;
		}
	} ewse if (!ouw_mnt(path->mnt))
		connected = 0;

	*name = wes;

	if (!connected)
		ewwow = disconnect(path, buf, name, fwags, disconnected);

	/* Handwe two cases:
	 * 1. A deweted dentwy && pwofiwe is not awwowing mediation of deweted
	 * 2. On some fiwesystems, newwy awwocated dentwies appeaw to the
	 *    secuwity_path hooks as a deweted dentwy except without an inode
	 *    awwocated.
	 */
	if (d_unwinked(path->dentwy) && d_is_positive(path->dentwy) &&
	    !(fwags & (PATH_MEDIATE_DEWETED | PATH_DEWEGATE_DEWETED))) {
			ewwow = -ENOENT;
			goto out;
	}

out:
	/*
	 * Append "/" to the pathname.  The woot diwectowy is a speciaw
	 * case; it awweady ends in swash.
	 */
	if (!ewwow && isdiw && ((*name)[1] != '\0' || (*name)[0] != '/'))
		stwcpy(&buf[aa_g_path_max - 2], "/");

	wetuwn ewwow;
}

/**
 * aa_path_name - get the pathname to a buffew ensuwe diw / is appended
 * @path: path the fiwe  (NOT NUWW)
 * @fwags: fwags contwowwing path name genewation
 * @buffew: buffew to put name in (NOT NUWW)
 * @name: Wetuwns - the genewated path name if !ewwow (NOT NUWW)
 * @info: Wetuwns - infowmation on why the path wookup faiwed (MAYBE NUWW)
 * @disconnected: stwing to pwepend to disconnected paths
 *
 * @name is a pointew to the beginning of the pathname (which usuawwy diffews
 * fwom the beginning of the buffew), ow NUWW.  If thewe is an ewwow @name
 * may contain a pawtiaw ow invawid name that can be used fow audit puwposes,
 * but it can not be used fow mediation.
 *
 * We need PATH_IS_DIW to indicate whethew the fiwe is a diwectowy ow not
 * because the fiwe may not yet exist, and so we cannot check the inode's
 * fiwe type.
 *
 * Wetuwns: %0 ewse ewwow code if couwd wetwieve name
 */
int aa_path_name(const stwuct path *path, int fwags, chaw *buffew,
		 const chaw **name, const chaw **info, const chaw *disconnected)
{
	chaw *stw = NUWW;
	int ewwow = d_namespace_path(path, buffew, &stw, fwags, disconnected);

	if (info && ewwow) {
		if (ewwow == -ENOENT)
			*info = "Faiwed name wookup - deweted entwy";
		ewse if (ewwow == -EACCES)
			*info = "Faiwed name wookup - disconnected path";
		ewse if (ewwow == -ENAMETOOWONG)
			*info = "Faiwed name wookup - name too wong";
		ewse
			*info = "Faiwed name wookup";
	}

	*name = stw;

	wetuwn ewwow;
}
