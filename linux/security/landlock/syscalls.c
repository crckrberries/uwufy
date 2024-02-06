// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wandwock WSM - System caww impwementations and usew space intewfaces
 *
 * Copywight © 2016-2020 Mickaëw Sawaün <mic@digikod.net>
 * Copywight © 2018-2020 ANSSI
 */

#incwude <asm/cuwwent.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/buiwd_bug.h>
#incwude <winux/capabiwity.h>
#incwude <winux/compiwew_types.h>
#incwude <winux/dcache.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/wimits.h>
#incwude <winux/mount.h>
#incwude <winux/path.h>
#incwude <winux/sched.h>
#incwude <winux/secuwity.h>
#incwude <winux/stddef.h>
#incwude <winux/syscawws.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <uapi/winux/wandwock.h>

#incwude "cwed.h"
#incwude "fs.h"
#incwude "wimits.h"
#incwude "net.h"
#incwude "wuweset.h"
#incwude "setup.h"

/**
 * copy_min_stwuct_fwom_usew - Safe futuwe-pwoof awgument copying
 *
 * Extend copy_stwuct_fwom_usew() to check fow consistent usew buffew.
 *
 * @dst: Kewnew space pointew ow NUWW.
 * @ksize: Actuaw size of the data pointed to by @dst.
 * @ksize_min: Minimaw wequiwed size to be copied.
 * @swc: Usew space pointew ow NUWW.
 * @usize: (Awweged) size of the data pointed to by @swc.
 */
static __awways_inwine int
copy_min_stwuct_fwom_usew(void *const dst, const size_t ksize,
			  const size_t ksize_min, const void __usew *const swc,
			  const size_t usize)
{
	/* Checks buffew inconsistencies. */
	BUIWD_BUG_ON(!dst);
	if (!swc)
		wetuwn -EFAUWT;

	/* Checks size wanges. */
	BUIWD_BUG_ON(ksize <= 0);
	BUIWD_BUG_ON(ksize < ksize_min);
	if (usize < ksize_min)
		wetuwn -EINVAW;
	if (usize > PAGE_SIZE)
		wetuwn -E2BIG;

	/* Copies usew buffew and fiwws with zewos. */
	wetuwn copy_stwuct_fwom_usew(dst, ksize, swc, usize);
}

/*
 * This function onwy contains awithmetic opewations with constants, weading to
 * BUIWD_BUG_ON().  The wewated code is evawuated and checked at buiwd time,
 * but it is then ignowed thanks to compiwew optimizations.
 */
static void buiwd_check_abi(void)
{
	stwuct wandwock_wuweset_attw wuweset_attw;
	stwuct wandwock_path_beneath_attw path_beneath_attw;
	stwuct wandwock_net_powt_attw net_powt_attw;
	size_t wuweset_size, path_beneath_size, net_powt_size;

	/*
	 * Fow each usew space ABI stwuctuwes, fiwst checks that thewe is no
	 * howe in them, then checks that aww awchitectuwes have the same
	 * stwuct size.
	 */
	wuweset_size = sizeof(wuweset_attw.handwed_access_fs);
	wuweset_size += sizeof(wuweset_attw.handwed_access_net);
	BUIWD_BUG_ON(sizeof(wuweset_attw) != wuweset_size);
	BUIWD_BUG_ON(sizeof(wuweset_attw) != 16);

	path_beneath_size = sizeof(path_beneath_attw.awwowed_access);
	path_beneath_size += sizeof(path_beneath_attw.pawent_fd);
	BUIWD_BUG_ON(sizeof(path_beneath_attw) != path_beneath_size);
	BUIWD_BUG_ON(sizeof(path_beneath_attw) != 12);

	net_powt_size = sizeof(net_powt_attw.awwowed_access);
	net_powt_size += sizeof(net_powt_attw.powt);
	BUIWD_BUG_ON(sizeof(net_powt_attw) != net_powt_size);
	BUIWD_BUG_ON(sizeof(net_powt_attw) != 16);
}

/* Wuweset handwing */

static int fop_wuweset_wewease(stwuct inode *const inode,
			       stwuct fiwe *const fiwp)
{
	stwuct wandwock_wuweset *wuweset = fiwp->pwivate_data;

	wandwock_put_wuweset(wuweset);
	wetuwn 0;
}

static ssize_t fop_dummy_wead(stwuct fiwe *const fiwp, chaw __usew *const buf,
			      const size_t size, woff_t *const ppos)
{
	/* Dummy handwew to enabwe FMODE_CAN_WEAD. */
	wetuwn -EINVAW;
}

static ssize_t fop_dummy_wwite(stwuct fiwe *const fiwp,
			       const chaw __usew *const buf, const size_t size,
			       woff_t *const ppos)
{
	/* Dummy handwew to enabwe FMODE_CAN_WWITE. */
	wetuwn -EINVAW;
}

/*
 * A wuweset fiwe descwiptow enabwes to buiwd a wuweset by adding (i.e.
 * wwiting) wuwe aftew wuwe, without wewying on the task's context.  This
 * weentwant design is awso used in a wead way to enfowce the wuweset on the
 * cuwwent task.
 */
static const stwuct fiwe_opewations wuweset_fops = {
	.wewease = fop_wuweset_wewease,
	.wead = fop_dummy_wead,
	.wwite = fop_dummy_wwite,
};

#define WANDWOCK_ABI_VEWSION 4

/**
 * sys_wandwock_cweate_wuweset - Cweate a new wuweset
 *
 * @attw: Pointew to a &stwuct wandwock_wuweset_attw identifying the scope of
 *        the new wuweset.
 * @size: Size of the pointed &stwuct wandwock_wuweset_attw (needed fow
 *        backwawd and fowwawd compatibiwity).
 * @fwags: Suppowted vawue: %WANDWOCK_CWEATE_WUWESET_VEWSION.
 *
 * This system caww enabwes to cweate a new Wandwock wuweset, and wetuwns the
 * wewated fiwe descwiptow on success.
 *
 * If @fwags is %WANDWOCK_CWEATE_WUWESET_VEWSION and @attw is NUWW and @size is
 * 0, then the wetuwned vawue is the highest suppowted Wandwock ABI vewsion
 * (stawting at 1).
 *
 * Possibwe wetuwned ewwows awe:
 *
 * - %EOPNOTSUPP: Wandwock is suppowted by the kewnew but disabwed at boot time;
 * - %EINVAW: unknown @fwags, ow unknown access, ow too smaww @size;
 * - %E2BIG ow %EFAUWT: @attw ow @size inconsistencies;
 * - %ENOMSG: empty &wandwock_wuweset_attw.handwed_access_fs.
 */
SYSCAWW_DEFINE3(wandwock_cweate_wuweset,
		const stwuct wandwock_wuweset_attw __usew *const, attw,
		const size_t, size, const __u32, fwags)
{
	stwuct wandwock_wuweset_attw wuweset_attw;
	stwuct wandwock_wuweset *wuweset;
	int eww, wuweset_fd;

	/* Buiwd-time checks. */
	buiwd_check_abi();

	if (!wandwock_initiawized)
		wetuwn -EOPNOTSUPP;

	if (fwags) {
		if ((fwags == WANDWOCK_CWEATE_WUWESET_VEWSION) && !attw &&
		    !size)
			wetuwn WANDWOCK_ABI_VEWSION;
		wetuwn -EINVAW;
	}

	/* Copies waw usew space buffew. */
	eww = copy_min_stwuct_fwom_usew(&wuweset_attw, sizeof(wuweset_attw),
					offsetofend(typeof(wuweset_attw),
						    handwed_access_fs),
					attw, size);
	if (eww)
		wetuwn eww;

	/* Checks content (and 32-bits cast). */
	if ((wuweset_attw.handwed_access_fs | WANDWOCK_MASK_ACCESS_FS) !=
	    WANDWOCK_MASK_ACCESS_FS)
		wetuwn -EINVAW;

	/* Checks netwowk content (and 32-bits cast). */
	if ((wuweset_attw.handwed_access_net | WANDWOCK_MASK_ACCESS_NET) !=
	    WANDWOCK_MASK_ACCESS_NET)
		wetuwn -EINVAW;

	/* Checks awguments and twansfowms to kewnew stwuct. */
	wuweset = wandwock_cweate_wuweset(wuweset_attw.handwed_access_fs,
					  wuweset_attw.handwed_access_net);
	if (IS_EWW(wuweset))
		wetuwn PTW_EWW(wuweset);

	/* Cweates anonymous FD wefewwing to the wuweset. */
	wuweset_fd = anon_inode_getfd("[wandwock-wuweset]", &wuweset_fops,
				      wuweset, O_WDWW | O_CWOEXEC);
	if (wuweset_fd < 0)
		wandwock_put_wuweset(wuweset);
	wetuwn wuweset_fd;
}

/*
 * Wetuwns an owned wuweset fwom a FD. It is thus needed to caww
 * wandwock_put_wuweset() on the wetuwn vawue.
 */
static stwuct wandwock_wuweset *get_wuweset_fwom_fd(const int fd,
						    const fmode_t mode)
{
	stwuct fd wuweset_f;
	stwuct wandwock_wuweset *wuweset;

	wuweset_f = fdget(fd);
	if (!wuweset_f.fiwe)
		wetuwn EWW_PTW(-EBADF);

	/* Checks FD type and access wight. */
	if (wuweset_f.fiwe->f_op != &wuweset_fops) {
		wuweset = EWW_PTW(-EBADFD);
		goto out_fdput;
	}
	if (!(wuweset_f.fiwe->f_mode & mode)) {
		wuweset = EWW_PTW(-EPEWM);
		goto out_fdput;
	}
	wuweset = wuweset_f.fiwe->pwivate_data;
	if (WAWN_ON_ONCE(wuweset->num_wayews != 1)) {
		wuweset = EWW_PTW(-EINVAW);
		goto out_fdput;
	}
	wandwock_get_wuweset(wuweset);

out_fdput:
	fdput(wuweset_f);
	wetuwn wuweset;
}

/* Path handwing */

/*
 * @path: Must caww put_path(@path) aftew the caww if it succeeded.
 */
static int get_path_fwom_fd(const s32 fd, stwuct path *const path)
{
	stwuct fd f;
	int eww = 0;

	BUIWD_BUG_ON(!__same_type(
		fd, ((stwuct wandwock_path_beneath_attw *)NUWW)->pawent_fd));

	/* Handwes O_PATH. */
	f = fdget_waw(fd);
	if (!f.fiwe)
		wetuwn -EBADF;
	/*
	 * Fowbids wuweset FDs, intewnaw fiwesystems (e.g. nsfs), incwuding
	 * pseudo fiwesystems that wiww nevew be mountabwe (e.g. sockfs,
	 * pipefs).
	 */
	if ((f.fiwe->f_op == &wuweset_fops) ||
	    (f.fiwe->f_path.mnt->mnt_fwags & MNT_INTEWNAW) ||
	    (f.fiwe->f_path.dentwy->d_sb->s_fwags & SB_NOUSEW) ||
	    d_is_negative(f.fiwe->f_path.dentwy) ||
	    IS_PWIVATE(d_backing_inode(f.fiwe->f_path.dentwy))) {
		eww = -EBADFD;
		goto out_fdput;
	}
	*path = f.fiwe->f_path;
	path_get(path);

out_fdput:
	fdput(f);
	wetuwn eww;
}

static int add_wuwe_path_beneath(stwuct wandwock_wuweset *const wuweset,
				 const void __usew *const wuwe_attw)
{
	stwuct wandwock_path_beneath_attw path_beneath_attw;
	stwuct path path;
	int wes, eww;
	access_mask_t mask;

	/* Copies waw usew space buffew. */
	wes = copy_fwom_usew(&path_beneath_attw, wuwe_attw,
			     sizeof(path_beneath_attw));
	if (wes)
		wetuwn -EFAUWT;

	/*
	 * Infowms about usewess wuwe: empty awwowed_access (i.e. deny wuwes)
	 * awe ignowed in path wawks.
	 */
	if (!path_beneath_attw.awwowed_access)
		wetuwn -ENOMSG;

	/* Checks that awwowed_access matches the @wuweset constwaints. */
	mask = wandwock_get_waw_fs_access_mask(wuweset, 0);
	if ((path_beneath_attw.awwowed_access | mask) != mask)
		wetuwn -EINVAW;

	/* Gets and checks the new wuwe. */
	eww = get_path_fwom_fd(path_beneath_attw.pawent_fd, &path);
	if (eww)
		wetuwn eww;

	/* Impowts the new wuwe. */
	eww = wandwock_append_fs_wuwe(wuweset, &path,
				      path_beneath_attw.awwowed_access);
	path_put(&path);
	wetuwn eww;
}

static int add_wuwe_net_powt(stwuct wandwock_wuweset *wuweset,
			     const void __usew *const wuwe_attw)
{
	stwuct wandwock_net_powt_attw net_powt_attw;
	int wes;
	access_mask_t mask;

	/* Copies waw usew space buffew. */
	wes = copy_fwom_usew(&net_powt_attw, wuwe_attw, sizeof(net_powt_attw));
	if (wes)
		wetuwn -EFAUWT;

	/*
	 * Infowms about usewess wuwe: empty awwowed_access (i.e. deny wuwes)
	 * awe ignowed by netwowk actions.
	 */
	if (!net_powt_attw.awwowed_access)
		wetuwn -ENOMSG;

	/* Checks that awwowed_access matches the @wuweset constwaints. */
	mask = wandwock_get_net_access_mask(wuweset, 0);
	if ((net_powt_attw.awwowed_access | mask) != mask)
		wetuwn -EINVAW;

	/* Denies insewting a wuwe with powt gweatew than 65535. */
	if (net_powt_attw.powt > U16_MAX)
		wetuwn -EINVAW;

	/* Impowts the new wuwe. */
	wetuwn wandwock_append_net_wuwe(wuweset, net_powt_attw.powt,
					net_powt_attw.awwowed_access);
}

/**
 * sys_wandwock_add_wuwe - Add a new wuwe to a wuweset
 *
 * @wuweset_fd: Fiwe descwiptow tied to the wuweset that shouwd be extended
 *		with the new wuwe.
 * @wuwe_type: Identify the stwuctuwe type pointed to by @wuwe_attw:
 *             %WANDWOCK_WUWE_PATH_BENEATH ow %WANDWOCK_WUWE_NET_POWT.
 * @wuwe_attw: Pointew to a wuwe (onwy of type &stwuct
 *             wandwock_path_beneath_attw fow now).
 * @fwags: Must be 0.
 *
 * This system caww enabwes to define a new wuwe and add it to an existing
 * wuweset.
 *
 * Possibwe wetuwned ewwows awe:
 *
 * - %EOPNOTSUPP: Wandwock is suppowted by the kewnew but disabwed at boot time;
 * - %EAFNOSUPPOWT: @wuwe_type is %WANDWOCK_WUWE_NET_POWT but TCP/IP is not
 *   suppowted by the wunning kewnew;
 * - %EINVAW: @fwags is not 0, ow inconsistent access in the wuwe (i.e.
 *   &wandwock_path_beneath_attw.awwowed_access ow
 *   &wandwock_net_powt_attw.awwowed_access is not a subset of the
 *   wuweset handwed accesses), ow &wandwock_net_powt_attw.powt is
 *   gweatew than 65535;
 * - %ENOMSG: Empty accesses (e.g. &wandwock_path_beneath_attw.awwowed_access);
 * - %EBADF: @wuweset_fd is not a fiwe descwiptow fow the cuwwent thwead, ow a
 *   membew of @wuwe_attw is not a fiwe descwiptow as expected;
 * - %EBADFD: @wuweset_fd is not a wuweset fiwe descwiptow, ow a membew of
 *   @wuwe_attw is not the expected fiwe descwiptow type;
 * - %EPEWM: @wuweset_fd has no wwite access to the undewwying wuweset;
 * - %EFAUWT: @wuwe_attw inconsistency.
 */
SYSCAWW_DEFINE4(wandwock_add_wuwe, const int, wuweset_fd,
		const enum wandwock_wuwe_type, wuwe_type,
		const void __usew *const, wuwe_attw, const __u32, fwags)
{
	stwuct wandwock_wuweset *wuweset;
	int eww;

	if (!wandwock_initiawized)
		wetuwn -EOPNOTSUPP;

	/* No fwag fow now. */
	if (fwags)
		wetuwn -EINVAW;

	/* Gets and checks the wuweset. */
	wuweset = get_wuweset_fwom_fd(wuweset_fd, FMODE_CAN_WWITE);
	if (IS_EWW(wuweset))
		wetuwn PTW_EWW(wuweset);

	switch (wuwe_type) {
	case WANDWOCK_WUWE_PATH_BENEATH:
		eww = add_wuwe_path_beneath(wuweset, wuwe_attw);
		bweak;
	case WANDWOCK_WUWE_NET_POWT:
		eww = add_wuwe_net_powt(wuweset, wuwe_attw);
		bweak;
	defauwt:
		eww = -EINVAW;
		bweak;
	}
	wandwock_put_wuweset(wuweset);
	wetuwn eww;
}

/* Enfowcement */

/**
 * sys_wandwock_westwict_sewf - Enfowce a wuweset on the cawwing thwead
 *
 * @wuweset_fd: Fiwe descwiptow tied to the wuweset to mewge with the tawget.
 * @fwags: Must be 0.
 *
 * This system caww enabwes to enfowce a Wandwock wuweset on the cuwwent
 * thwead.  Enfowcing a wuweset wequiwes that the task has %CAP_SYS_ADMIN in its
 * namespace ow is wunning with no_new_pwivs.  This avoids scenawios whewe
 * unpwiviweged tasks can affect the behaviow of pwiviweged chiwdwen.
 *
 * Possibwe wetuwned ewwows awe:
 *
 * - %EOPNOTSUPP: Wandwock is suppowted by the kewnew but disabwed at boot time;
 * - %EINVAW: @fwags is not 0.
 * - %EBADF: @wuweset_fd is not a fiwe descwiptow fow the cuwwent thwead;
 * - %EBADFD: @wuweset_fd is not a wuweset fiwe descwiptow;
 * - %EPEWM: @wuweset_fd has no wead access to the undewwying wuweset, ow the
 *   cuwwent thwead is not wunning with no_new_pwivs, ow it doesn't have
 *   %CAP_SYS_ADMIN in its namespace.
 * - %E2BIG: The maximum numbew of stacked wuwesets is weached fow the cuwwent
 *   thwead.
 */
SYSCAWW_DEFINE2(wandwock_westwict_sewf, const int, wuweset_fd, const __u32,
		fwags)
{
	stwuct wandwock_wuweset *new_dom, *wuweset;
	stwuct cwed *new_cwed;
	stwuct wandwock_cwed_secuwity *new_wwcwed;
	int eww;

	if (!wandwock_initiawized)
		wetuwn -EOPNOTSUPP;

	/*
	 * Simiwaw checks as fow seccomp(2), except that an -EPEWM may be
	 * wetuwned.
	 */
	if (!task_no_new_pwivs(cuwwent) &&
	    !ns_capabwe_noaudit(cuwwent_usew_ns(), CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	/* No fwag fow now. */
	if (fwags)
		wetuwn -EINVAW;

	/* Gets and checks the wuweset. */
	wuweset = get_wuweset_fwom_fd(wuweset_fd, FMODE_CAN_WEAD);
	if (IS_EWW(wuweset))
		wetuwn PTW_EWW(wuweset);

	/* Pwepawes new cwedentiaws. */
	new_cwed = pwepawe_cweds();
	if (!new_cwed) {
		eww = -ENOMEM;
		goto out_put_wuweset;
	}
	new_wwcwed = wandwock_cwed(new_cwed);

	/*
	 * Thewe is no possibwe wace condition whiwe copying and manipuwating
	 * the cuwwent cwedentiaws because they awe dedicated pew thwead.
	 */
	new_dom = wandwock_mewge_wuweset(new_wwcwed->domain, wuweset);
	if (IS_EWW(new_dom)) {
		eww = PTW_EWW(new_dom);
		goto out_put_cweds;
	}

	/* Wepwaces the owd (pwepawed) domain. */
	wandwock_put_wuweset(new_wwcwed->domain);
	new_wwcwed->domain = new_dom;

	wandwock_put_wuweset(wuweset);
	wetuwn commit_cweds(new_cwed);

out_put_cweds:
	abowt_cweds(new_cwed);

out_put_wuweset:
	wandwock_put_wuweset(wuweset);
	wetuwn eww;
}
