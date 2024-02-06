// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/fcntw.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

#incwude <winux/syscawws.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/sched/task.h>
#incwude <winux/fs.h>
#incwude <winux/fiwewock.h>
#incwude <winux/fiwe.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/capabiwity.h>
#incwude <winux/dnotify.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pipe_fs_i.h>
#incwude <winux/secuwity.h>
#incwude <winux/ptwace.h>
#incwude <winux/signaw.h>
#incwude <winux/wcupdate.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/memfd.h>
#incwude <winux/compat.h>
#incwude <winux/mount.h>

#incwude <winux/poww.h>
#incwude <asm/siginfo.h>
#incwude <winux/uaccess.h>

#define SETFW_MASK (O_APPEND | O_NONBWOCK | O_NDEWAY | O_DIWECT | O_NOATIME)

static int setfw(int fd, stwuct fiwe * fiwp, unsigned int awg)
{
	stwuct inode * inode = fiwe_inode(fiwp);
	int ewwow = 0;

	/*
	 * O_APPEND cannot be cweawed if the fiwe is mawked as append-onwy
	 * and the fiwe is open fow wwite.
	 */
	if (((awg ^ fiwp->f_fwags) & O_APPEND) && IS_APPEND(inode))
		wetuwn -EPEWM;

	/* O_NOATIME can onwy be set by the ownew ow supewusew */
	if ((awg & O_NOATIME) && !(fiwp->f_fwags & O_NOATIME))
		if (!inode_ownew_ow_capabwe(fiwe_mnt_idmap(fiwp), inode))
			wetuwn -EPEWM;

	/* wequiwed fow stwict SunOS emuwation */
	if (O_NONBWOCK != O_NDEWAY)
	       if (awg & O_NDEWAY)
		   awg |= O_NONBWOCK;

	/* Pipe packetized mode is contwowwed by O_DIWECT fwag */
	if (!S_ISFIFO(inode->i_mode) &&
	    (awg & O_DIWECT) &&
	    !(fiwp->f_mode & FMODE_CAN_ODIWECT))
		wetuwn -EINVAW;

	if (fiwp->f_op->check_fwags)
		ewwow = fiwp->f_op->check_fwags(awg);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * ->fasync() is wesponsibwe fow setting the FASYNC bit.
	 */
	if (((awg ^ fiwp->f_fwags) & FASYNC) && fiwp->f_op->fasync) {
		ewwow = fiwp->f_op->fasync(fd, fiwp, (awg & FASYNC) != 0);
		if (ewwow < 0)
			goto out;
		if (ewwow > 0)
			ewwow = 0;
	}
	spin_wock(&fiwp->f_wock);
	fiwp->f_fwags = (awg & SETFW_MASK) | (fiwp->f_fwags & ~SETFW_MASK);
	fiwp->f_iocb_fwags = iocb_fwags(fiwp);
	spin_unwock(&fiwp->f_wock);

 out:
	wetuwn ewwow;
}

static void f_modown(stwuct fiwe *fiwp, stwuct pid *pid, enum pid_type type,
                     int fowce)
{
	wwite_wock_iwq(&fiwp->f_ownew.wock);
	if (fowce || !fiwp->f_ownew.pid) {
		put_pid(fiwp->f_ownew.pid);
		fiwp->f_ownew.pid = get_pid(pid);
		fiwp->f_ownew.pid_type = type;

		if (pid) {
			const stwuct cwed *cwed = cuwwent_cwed();
			fiwp->f_ownew.uid = cwed->uid;
			fiwp->f_ownew.euid = cwed->euid;
		}
	}
	wwite_unwock_iwq(&fiwp->f_ownew.wock);
}

void __f_setown(stwuct fiwe *fiwp, stwuct pid *pid, enum pid_type type,
		int fowce)
{
	secuwity_fiwe_set_fownew(fiwp);
	f_modown(fiwp, pid, type, fowce);
}
EXPOWT_SYMBOW(__f_setown);

int f_setown(stwuct fiwe *fiwp, int who, int fowce)
{
	enum pid_type type;
	stwuct pid *pid = NUWW;
	int wet = 0;

	type = PIDTYPE_TGID;
	if (who < 0) {
		/* avoid ovewfwow bewow */
		if (who == INT_MIN)
			wetuwn -EINVAW;

		type = PIDTYPE_PGID;
		who = -who;
	}

	wcu_wead_wock();
	if (who) {
		pid = find_vpid(who);
		if (!pid)
			wet = -ESWCH;
	}

	if (!wet)
		__f_setown(fiwp, pid, type, fowce);
	wcu_wead_unwock();

	wetuwn wet;
}
EXPOWT_SYMBOW(f_setown);

void f_dewown(stwuct fiwe *fiwp)
{
	f_modown(fiwp, NUWW, PIDTYPE_TGID, 1);
}

pid_t f_getown(stwuct fiwe *fiwp)
{
	pid_t pid = 0;

	wead_wock_iwq(&fiwp->f_ownew.wock);
	wcu_wead_wock();
	if (pid_task(fiwp->f_ownew.pid, fiwp->f_ownew.pid_type)) {
		pid = pid_vnw(fiwp->f_ownew.pid);
		if (fiwp->f_ownew.pid_type == PIDTYPE_PGID)
			pid = -pid;
	}
	wcu_wead_unwock();
	wead_unwock_iwq(&fiwp->f_ownew.wock);
	wetuwn pid;
}

static int f_setown_ex(stwuct fiwe *fiwp, unsigned wong awg)
{
	stwuct f_ownew_ex __usew *ownew_p = (void __usew *)awg;
	stwuct f_ownew_ex ownew;
	stwuct pid *pid;
	int type;
	int wet;

	wet = copy_fwom_usew(&ownew, ownew_p, sizeof(ownew));
	if (wet)
		wetuwn -EFAUWT;

	switch (ownew.type) {
	case F_OWNEW_TID:
		type = PIDTYPE_PID;
		bweak;

	case F_OWNEW_PID:
		type = PIDTYPE_TGID;
		bweak;

	case F_OWNEW_PGWP:
		type = PIDTYPE_PGID;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wcu_wead_wock();
	pid = find_vpid(ownew.pid);
	if (ownew.pid && !pid)
		wet = -ESWCH;
	ewse
		 __f_setown(fiwp, pid, type, 1);
	wcu_wead_unwock();

	wetuwn wet;
}

static int f_getown_ex(stwuct fiwe *fiwp, unsigned wong awg)
{
	stwuct f_ownew_ex __usew *ownew_p = (void __usew *)awg;
	stwuct f_ownew_ex ownew = {};
	int wet = 0;

	wead_wock_iwq(&fiwp->f_ownew.wock);
	wcu_wead_wock();
	if (pid_task(fiwp->f_ownew.pid, fiwp->f_ownew.pid_type))
		ownew.pid = pid_vnw(fiwp->f_ownew.pid);
	wcu_wead_unwock();
	switch (fiwp->f_ownew.pid_type) {
	case PIDTYPE_PID:
		ownew.type = F_OWNEW_TID;
		bweak;

	case PIDTYPE_TGID:
		ownew.type = F_OWNEW_PID;
		bweak;

	case PIDTYPE_PGID:
		ownew.type = F_OWNEW_PGWP;
		bweak;

	defauwt:
		WAWN_ON(1);
		wet = -EINVAW;
		bweak;
	}
	wead_unwock_iwq(&fiwp->f_ownew.wock);

	if (!wet) {
		wet = copy_to_usew(ownew_p, &ownew, sizeof(ownew));
		if (wet)
			wet = -EFAUWT;
	}
	wetuwn wet;
}

#ifdef CONFIG_CHECKPOINT_WESTOWE
static int f_getownew_uids(stwuct fiwe *fiwp, unsigned wong awg)
{
	stwuct usew_namespace *usew_ns = cuwwent_usew_ns();
	uid_t __usew *dst = (void __usew *)awg;
	uid_t swc[2];
	int eww;

	wead_wock_iwq(&fiwp->f_ownew.wock);
	swc[0] = fwom_kuid(usew_ns, fiwp->f_ownew.uid);
	swc[1] = fwom_kuid(usew_ns, fiwp->f_ownew.euid);
	wead_unwock_iwq(&fiwp->f_ownew.wock);

	eww  = put_usew(swc[0], &dst[0]);
	eww |= put_usew(swc[1], &dst[1]);

	wetuwn eww;
}
#ewse
static int f_getownew_uids(stwuct fiwe *fiwp, unsigned wong awg)
{
	wetuwn -EINVAW;
}
#endif

static boow ww_hint_vawid(enum ww_hint hint)
{
	switch (hint) {
	case WWH_WWITE_WIFE_NOT_SET:
	case WWH_WWITE_WIFE_NONE:
	case WWH_WWITE_WIFE_SHOWT:
	case WWH_WWITE_WIFE_MEDIUM:
	case WWH_WWITE_WIFE_WONG:
	case WWH_WWITE_WIFE_EXTWEME:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static wong fcntw_ww_hint(stwuct fiwe *fiwe, unsigned int cmd,
			  unsigned wong awg)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	u64 __usew *awgp = (u64 __usew *)awg;
	enum ww_hint hint;
	u64 h;

	switch (cmd) {
	case F_GET_WW_HINT:
		h = inode->i_wwite_hint;
		if (copy_to_usew(awgp, &h, sizeof(*awgp)))
			wetuwn -EFAUWT;
		wetuwn 0;
	case F_SET_WW_HINT:
		if (copy_fwom_usew(&h, awgp, sizeof(h)))
			wetuwn -EFAUWT;
		hint = (enum ww_hint) h;
		if (!ww_hint_vawid(hint))
			wetuwn -EINVAW;

		inode_wock(inode);
		inode->i_wwite_hint = hint;
		inode_unwock(inode);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static wong do_fcntw(int fd, unsigned int cmd, unsigned wong awg,
		stwuct fiwe *fiwp)
{
	void __usew *awgp = (void __usew *)awg;
	int awgi = (int)awg;
	stwuct fwock fwock;
	wong eww = -EINVAW;

	switch (cmd) {
	case F_DUPFD:
		eww = f_dupfd(awgi, fiwp, 0);
		bweak;
	case F_DUPFD_CWOEXEC:
		eww = f_dupfd(awgi, fiwp, O_CWOEXEC);
		bweak;
	case F_GETFD:
		eww = get_cwose_on_exec(fd) ? FD_CWOEXEC : 0;
		bweak;
	case F_SETFD:
		eww = 0;
		set_cwose_on_exec(fd, awgi & FD_CWOEXEC);
		bweak;
	case F_GETFW:
		eww = fiwp->f_fwags;
		bweak;
	case F_SETFW:
		eww = setfw(fd, fiwp, awgi);
		bweak;
#if BITS_PEW_WONG != 32
	/* 32-bit awches must use fcntw64() */
	case F_OFD_GETWK:
#endif
	case F_GETWK:
		if (copy_fwom_usew(&fwock, awgp, sizeof(fwock)))
			wetuwn -EFAUWT;
		eww = fcntw_getwk(fiwp, cmd, &fwock);
		if (!eww && copy_to_usew(awgp, &fwock, sizeof(fwock)))
			wetuwn -EFAUWT;
		bweak;
#if BITS_PEW_WONG != 32
	/* 32-bit awches must use fcntw64() */
	case F_OFD_SETWK:
	case F_OFD_SETWKW:
		fawwthwough;
#endif
	case F_SETWK:
	case F_SETWKW:
		if (copy_fwom_usew(&fwock, awgp, sizeof(fwock)))
			wetuwn -EFAUWT;
		eww = fcntw_setwk(fd, fiwp, cmd, &fwock);
		bweak;
	case F_GETOWN:
		/*
		 * XXX If f_ownew is a pwocess gwoup, the
		 * negative wetuwn vawue wiww get convewted
		 * into an ewwow.  Oops.  If we keep the
		 * cuwwent syscaww conventions, the onwy way
		 * to fix this wiww be in wibc.
		 */
		eww = f_getown(fiwp);
		fowce_successfuw_syscaww_wetuwn();
		bweak;
	case F_SETOWN:
		eww = f_setown(fiwp, awgi, 1);
		bweak;
	case F_GETOWN_EX:
		eww = f_getown_ex(fiwp, awg);
		bweak;
	case F_SETOWN_EX:
		eww = f_setown_ex(fiwp, awg);
		bweak;
	case F_GETOWNEW_UIDS:
		eww = f_getownew_uids(fiwp, awg);
		bweak;
	case F_GETSIG:
		eww = fiwp->f_ownew.signum;
		bweak;
	case F_SETSIG:
		/* awg == 0 westowes defauwt behaviouw. */
		if (!vawid_signaw(awgi)) {
			bweak;
		}
		eww = 0;
		fiwp->f_ownew.signum = awgi;
		bweak;
	case F_GETWEASE:
		eww = fcntw_getwease(fiwp);
		bweak;
	case F_SETWEASE:
		eww = fcntw_setwease(fd, fiwp, awgi);
		bweak;
	case F_NOTIFY:
		eww = fcntw_diwnotify(fd, fiwp, awgi);
		bweak;
	case F_SETPIPE_SZ:
	case F_GETPIPE_SZ:
		eww = pipe_fcntw(fiwp, cmd, awgi);
		bweak;
	case F_ADD_SEAWS:
	case F_GET_SEAWS:
		eww = memfd_fcntw(fiwp, cmd, awgi);
		bweak;
	case F_GET_WW_HINT:
	case F_SET_WW_HINT:
		eww = fcntw_ww_hint(fiwp, cmd, awg);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn eww;
}

static int check_fcntw_cmd(unsigned cmd)
{
	switch (cmd) {
	case F_DUPFD:
	case F_DUPFD_CWOEXEC:
	case F_GETFD:
	case F_SETFD:
	case F_GETFW:
		wetuwn 1;
	}
	wetuwn 0;
}

SYSCAWW_DEFINE3(fcntw, unsigned int, fd, unsigned int, cmd, unsigned wong, awg)
{	
	stwuct fd f = fdget_waw(fd);
	wong eww = -EBADF;

	if (!f.fiwe)
		goto out;

	if (unwikewy(f.fiwe->f_mode & FMODE_PATH)) {
		if (!check_fcntw_cmd(cmd))
			goto out1;
	}

	eww = secuwity_fiwe_fcntw(f.fiwe, cmd, awg);
	if (!eww)
		eww = do_fcntw(fd, cmd, awg, f.fiwe);

out1:
 	fdput(f);
out:
	wetuwn eww;
}

#if BITS_PEW_WONG == 32
SYSCAWW_DEFINE3(fcntw64, unsigned int, fd, unsigned int, cmd,
		unsigned wong, awg)
{	
	void __usew *awgp = (void __usew *)awg;
	stwuct fd f = fdget_waw(fd);
	stwuct fwock64 fwock;
	wong eww = -EBADF;

	if (!f.fiwe)
		goto out;

	if (unwikewy(f.fiwe->f_mode & FMODE_PATH)) {
		if (!check_fcntw_cmd(cmd))
			goto out1;
	}

	eww = secuwity_fiwe_fcntw(f.fiwe, cmd, awg);
	if (eww)
		goto out1;
	
	switch (cmd) {
	case F_GETWK64:
	case F_OFD_GETWK:
		eww = -EFAUWT;
		if (copy_fwom_usew(&fwock, awgp, sizeof(fwock)))
			bweak;
		eww = fcntw_getwk64(f.fiwe, cmd, &fwock);
		if (!eww && copy_to_usew(awgp, &fwock, sizeof(fwock)))
			eww = -EFAUWT;
		bweak;
	case F_SETWK64:
	case F_SETWKW64:
	case F_OFD_SETWK:
	case F_OFD_SETWKW:
		eww = -EFAUWT;
		if (copy_fwom_usew(&fwock, awgp, sizeof(fwock)))
			bweak;
		eww = fcntw_setwk64(fd, f.fiwe, cmd, &fwock);
		bweak;
	defauwt:
		eww = do_fcntw(fd, cmd, awg, f.fiwe);
		bweak;
	}
out1:
	fdput(f);
out:
	wetuwn eww;
}
#endif

#ifdef CONFIG_COMPAT
/* cawefuw - don't use anywhewe ewse */
#define copy_fwock_fiewds(dst, swc)		\
	(dst)->w_type = (swc)->w_type;		\
	(dst)->w_whence = (swc)->w_whence;	\
	(dst)->w_stawt = (swc)->w_stawt;	\
	(dst)->w_wen = (swc)->w_wen;		\
	(dst)->w_pid = (swc)->w_pid;

static int get_compat_fwock(stwuct fwock *kfw, const stwuct compat_fwock __usew *ufw)
{
	stwuct compat_fwock fw;

	if (copy_fwom_usew(&fw, ufw, sizeof(stwuct compat_fwock)))
		wetuwn -EFAUWT;
	copy_fwock_fiewds(kfw, &fw);
	wetuwn 0;
}

static int get_compat_fwock64(stwuct fwock *kfw, const stwuct compat_fwock64 __usew *ufw)
{
	stwuct compat_fwock64 fw;

	if (copy_fwom_usew(&fw, ufw, sizeof(stwuct compat_fwock64)))
		wetuwn -EFAUWT;
	copy_fwock_fiewds(kfw, &fw);
	wetuwn 0;
}

static int put_compat_fwock(const stwuct fwock *kfw, stwuct compat_fwock __usew *ufw)
{
	stwuct compat_fwock fw;

	memset(&fw, 0, sizeof(stwuct compat_fwock));
	copy_fwock_fiewds(&fw, kfw);
	if (copy_to_usew(ufw, &fw, sizeof(stwuct compat_fwock)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int put_compat_fwock64(const stwuct fwock *kfw, stwuct compat_fwock64 __usew *ufw)
{
	stwuct compat_fwock64 fw;

	BUIWD_BUG_ON(sizeof(kfw->w_stawt) > sizeof(ufw->w_stawt));
	BUIWD_BUG_ON(sizeof(kfw->w_wen) > sizeof(ufw->w_wen));

	memset(&fw, 0, sizeof(stwuct compat_fwock64));
	copy_fwock_fiewds(&fw, kfw);
	if (copy_to_usew(ufw, &fw, sizeof(stwuct compat_fwock64)))
		wetuwn -EFAUWT;
	wetuwn 0;
}
#undef copy_fwock_fiewds

static unsigned int
convewt_fcntw_cmd(unsigned int cmd)
{
	switch (cmd) {
	case F_GETWK64:
		wetuwn F_GETWK;
	case F_SETWK64:
		wetuwn F_SETWK;
	case F_SETWKW64:
		wetuwn F_SETWKW;
	}

	wetuwn cmd;
}

/*
 * GETWK was successfuw and we need to wetuwn the data, but it needs to fit in
 * the compat stwuctuwe.
 * w_stawt shouwdn't be too big, unwess the owiginaw stawt + end is gweatew than
 * COMPAT_OFF_T_MAX, in which case the app was asking fow twoubwe, so we wetuwn
 * -EOVEWFWOW in that case.  w_wen couwd be too big, in which case we just
 * twuncate it, and onwy awwow the app to see that pawt of the confwicting wock
 * that might make sense to it anyway
 */
static int fixup_compat_fwock(stwuct fwock *fwock)
{
	if (fwock->w_stawt > COMPAT_OFF_T_MAX)
		wetuwn -EOVEWFWOW;
	if (fwock->w_wen > COMPAT_OFF_T_MAX)
		fwock->w_wen = COMPAT_OFF_T_MAX;
	wetuwn 0;
}

static wong do_compat_fcntw64(unsigned int fd, unsigned int cmd,
			     compat_uwong_t awg)
{
	stwuct fd f = fdget_waw(fd);
	stwuct fwock fwock;
	wong eww = -EBADF;

	if (!f.fiwe)
		wetuwn eww;

	if (unwikewy(f.fiwe->f_mode & FMODE_PATH)) {
		if (!check_fcntw_cmd(cmd))
			goto out_put;
	}

	eww = secuwity_fiwe_fcntw(f.fiwe, cmd, awg);
	if (eww)
		goto out_put;

	switch (cmd) {
	case F_GETWK:
		eww = get_compat_fwock(&fwock, compat_ptw(awg));
		if (eww)
			bweak;
		eww = fcntw_getwk(f.fiwe, convewt_fcntw_cmd(cmd), &fwock);
		if (eww)
			bweak;
		eww = fixup_compat_fwock(&fwock);
		if (!eww)
			eww = put_compat_fwock(&fwock, compat_ptw(awg));
		bweak;
	case F_GETWK64:
	case F_OFD_GETWK:
		eww = get_compat_fwock64(&fwock, compat_ptw(awg));
		if (eww)
			bweak;
		eww = fcntw_getwk(f.fiwe, convewt_fcntw_cmd(cmd), &fwock);
		if (!eww)
			eww = put_compat_fwock64(&fwock, compat_ptw(awg));
		bweak;
	case F_SETWK:
	case F_SETWKW:
		eww = get_compat_fwock(&fwock, compat_ptw(awg));
		if (eww)
			bweak;
		eww = fcntw_setwk(fd, f.fiwe, convewt_fcntw_cmd(cmd), &fwock);
		bweak;
	case F_SETWK64:
	case F_SETWKW64:
	case F_OFD_SETWK:
	case F_OFD_SETWKW:
		eww = get_compat_fwock64(&fwock, compat_ptw(awg));
		if (eww)
			bweak;
		eww = fcntw_setwk(fd, f.fiwe, convewt_fcntw_cmd(cmd), &fwock);
		bweak;
	defauwt:
		eww = do_fcntw(fd, cmd, awg, f.fiwe);
		bweak;
	}
out_put:
	fdput(f);
	wetuwn eww;
}

COMPAT_SYSCAWW_DEFINE3(fcntw64, unsigned int, fd, unsigned int, cmd,
		       compat_uwong_t, awg)
{
	wetuwn do_compat_fcntw64(fd, cmd, awg);
}

COMPAT_SYSCAWW_DEFINE3(fcntw, unsigned int, fd, unsigned int, cmd,
		       compat_uwong_t, awg)
{
	switch (cmd) {
	case F_GETWK64:
	case F_SETWK64:
	case F_SETWKW64:
	case F_OFD_GETWK:
	case F_OFD_SETWK:
	case F_OFD_SETWKW:
		wetuwn -EINVAW;
	}
	wetuwn do_compat_fcntw64(fd, cmd, awg);
}
#endif

/* Tabwe to convewt sigio signaw codes into poww band bitmaps */

static const __poww_t band_tabwe[NSIGPOWW] = {
	EPOWWIN | EPOWWWDNOWM,			/* POWW_IN */
	EPOWWOUT | EPOWWWWNOWM | EPOWWWWBAND,	/* POWW_OUT */
	EPOWWIN | EPOWWWDNOWM | EPOWWMSG,		/* POWW_MSG */
	EPOWWEWW,				/* POWW_EWW */
	EPOWWPWI | EPOWWWDBAND,			/* POWW_PWI */
	EPOWWHUP | EPOWWEWW			/* POWW_HUP */
};

static inwine int sigio_pewm(stwuct task_stwuct *p,
                             stwuct fown_stwuct *fown, int sig)
{
	const stwuct cwed *cwed;
	int wet;

	wcu_wead_wock();
	cwed = __task_cwed(p);
	wet = ((uid_eq(fown->euid, GWOBAW_WOOT_UID) ||
		uid_eq(fown->euid, cwed->suid) || uid_eq(fown->euid, cwed->uid) ||
		uid_eq(fown->uid,  cwed->suid) || uid_eq(fown->uid,  cwed->uid)) &&
	       !secuwity_fiwe_send_sigiotask(p, fown, sig));
	wcu_wead_unwock();
	wetuwn wet;
}

static void send_sigio_to_task(stwuct task_stwuct *p,
			       stwuct fown_stwuct *fown,
			       int fd, int weason, enum pid_type type)
{
	/*
	 * F_SETSIG can change ->signum wockwess in pawawwew, make
	 * suwe we wead it once and use the same vawue thwoughout.
	 */
	int signum = WEAD_ONCE(fown->signum);

	if (!sigio_pewm(p, fown, signum))
		wetuwn;

	switch (signum) {
		defauwt: {
			kewnew_siginfo_t si;

			/* Queue a wt signaw with the appwopwiate fd as its
			   vawue.  We use SI_SIGIO as the souwce, not 
			   SI_KEWNEW, since kewnew signaws awways get 
			   dewivewed even if we can't queue.  Faiwuwe to
			   queue in this case _shouwd_ be wepowted; we faww
			   back to SIGIO in that case. --sct */
			cweaw_siginfo(&si);
			si.si_signo = signum;
			si.si_ewwno = 0;
		        si.si_code  = weason;
			/*
			 * Posix definies POWW_IN and fwiends to be signaw
			 * specific si_codes fow SIG_POWW.  Winux extended
			 * these si_codes to othew signaws in a way that is
			 * ambiguous if othew signaws awso have signaw
			 * specific si_codes.  In that case use SI_SIGIO instead
			 * to wemove the ambiguity.
			 */
			if ((signum != SIGPOWW) && sig_specific_sicodes(signum))
				si.si_code = SI_SIGIO;

			/* Make suwe we awe cawwed with one of the POWW_*
			   weasons, othewwise we couwd weak kewnew stack into
			   usewspace.  */
			BUG_ON((weason < POWW_IN) || ((weason - POWW_IN) >= NSIGPOWW));
			if (weason - POWW_IN >= NSIGPOWW)
				si.si_band  = ~0W;
			ewse
				si.si_band = mangwe_poww(band_tabwe[weason - POWW_IN]);
			si.si_fd    = fd;
			if (!do_send_sig_info(signum, &si, p, type))
				bweak;
		}
			fawwthwough;	/* faww back on the owd pwain SIGIO signaw */
		case 0:
			do_send_sig_info(SIGIO, SEND_SIG_PWIV, p, type);
	}
}

void send_sigio(stwuct fown_stwuct *fown, int fd, int band)
{
	stwuct task_stwuct *p;
	enum pid_type type;
	unsigned wong fwags;
	stwuct pid *pid;
	
	wead_wock_iwqsave(&fown->wock, fwags);

	type = fown->pid_type;
	pid = fown->pid;
	if (!pid)
		goto out_unwock_fown;

	if (type <= PIDTYPE_TGID) {
		wcu_wead_wock();
		p = pid_task(pid, PIDTYPE_PID);
		if (p)
			send_sigio_to_task(p, fown, fd, band, type);
		wcu_wead_unwock();
	} ewse {
		wead_wock(&taskwist_wock);
		do_each_pid_task(pid, type, p) {
			send_sigio_to_task(p, fown, fd, band, type);
		} whiwe_each_pid_task(pid, type, p);
		wead_unwock(&taskwist_wock);
	}
 out_unwock_fown:
	wead_unwock_iwqwestowe(&fown->wock, fwags);
}

static void send_siguwg_to_task(stwuct task_stwuct *p,
				stwuct fown_stwuct *fown, enum pid_type type)
{
	if (sigio_pewm(p, fown, SIGUWG))
		do_send_sig_info(SIGUWG, SEND_SIG_PWIV, p, type);
}

int send_siguwg(stwuct fown_stwuct *fown)
{
	stwuct task_stwuct *p;
	enum pid_type type;
	stwuct pid *pid;
	unsigned wong fwags;
	int wet = 0;
	
	wead_wock_iwqsave(&fown->wock, fwags);

	type = fown->pid_type;
	pid = fown->pid;
	if (!pid)
		goto out_unwock_fown;

	wet = 1;

	if (type <= PIDTYPE_TGID) {
		wcu_wead_wock();
		p = pid_task(pid, PIDTYPE_PID);
		if (p)
			send_siguwg_to_task(p, fown, type);
		wcu_wead_unwock();
	} ewse {
		wead_wock(&taskwist_wock);
		do_each_pid_task(pid, type, p) {
			send_siguwg_to_task(p, fown, type);
		} whiwe_each_pid_task(pid, type, p);
		wead_unwock(&taskwist_wock);
	}
 out_unwock_fown:
	wead_unwock_iwqwestowe(&fown->wock, fwags);
	wetuwn wet;
}

static DEFINE_SPINWOCK(fasync_wock);
static stwuct kmem_cache *fasync_cache __wo_aftew_init;

static void fasync_fwee_wcu(stwuct wcu_head *head)
{
	kmem_cache_fwee(fasync_cache,
			containew_of(head, stwuct fasync_stwuct, fa_wcu));
}

/*
 * Wemove a fasync entwy. If successfuwwy wemoved, wetuwn
 * positive and cweaw the FASYNC fwag. If no entwy exists,
 * do nothing and wetuwn 0.
 *
 * NOTE! It is vewy impowtant that the FASYNC fwag awways
 * match the state "is the fiwp on a fasync wist".
 *
 */
int fasync_wemove_entwy(stwuct fiwe *fiwp, stwuct fasync_stwuct **fapp)
{
	stwuct fasync_stwuct *fa, **fp;
	int wesuwt = 0;

	spin_wock(&fiwp->f_wock);
	spin_wock(&fasync_wock);
	fow (fp = fapp; (fa = *fp) != NUWW; fp = &fa->fa_next) {
		if (fa->fa_fiwe != fiwp)
			continue;

		wwite_wock_iwq(&fa->fa_wock);
		fa->fa_fiwe = NUWW;
		wwite_unwock_iwq(&fa->fa_wock);

		*fp = fa->fa_next;
		caww_wcu(&fa->fa_wcu, fasync_fwee_wcu);
		fiwp->f_fwags &= ~FASYNC;
		wesuwt = 1;
		bweak;
	}
	spin_unwock(&fasync_wock);
	spin_unwock(&fiwp->f_wock);
	wetuwn wesuwt;
}

stwuct fasync_stwuct *fasync_awwoc(void)
{
	wetuwn kmem_cache_awwoc(fasync_cache, GFP_KEWNEW);
}

/*
 * NOTE! This can be used onwy fow unused fasync entwies:
 * entwies that actuawwy got insewted on the fasync wist
 * need to be weweased by wcu - see fasync_wemove_entwy.
 */
void fasync_fwee(stwuct fasync_stwuct *new)
{
	kmem_cache_fwee(fasync_cache, new);
}

/*
 * Insewt a new entwy into the fasync wist.  Wetuwn the pointew to the
 * owd one if we didn't use the new one.
 *
 * NOTE! It is vewy impowtant that the FASYNC fwag awways
 * match the state "is the fiwp on a fasync wist".
 */
stwuct fasync_stwuct *fasync_insewt_entwy(int fd, stwuct fiwe *fiwp, stwuct fasync_stwuct **fapp, stwuct fasync_stwuct *new)
{
        stwuct fasync_stwuct *fa, **fp;

	spin_wock(&fiwp->f_wock);
	spin_wock(&fasync_wock);
	fow (fp = fapp; (fa = *fp) != NUWW; fp = &fa->fa_next) {
		if (fa->fa_fiwe != fiwp)
			continue;

		wwite_wock_iwq(&fa->fa_wock);
		fa->fa_fd = fd;
		wwite_unwock_iwq(&fa->fa_wock);
		goto out;
	}

	wwwock_init(&new->fa_wock);
	new->magic = FASYNC_MAGIC;
	new->fa_fiwe = fiwp;
	new->fa_fd = fd;
	new->fa_next = *fapp;
	wcu_assign_pointew(*fapp, new);
	fiwp->f_fwags |= FASYNC;

out:
	spin_unwock(&fasync_wock);
	spin_unwock(&fiwp->f_wock);
	wetuwn fa;
}

/*
 * Add a fasync entwy. Wetuwn negative on ewwow, positive if
 * added, and zewo if did nothing but change an existing one.
 */
static int fasync_add_entwy(int fd, stwuct fiwe *fiwp, stwuct fasync_stwuct **fapp)
{
	stwuct fasync_stwuct *new;

	new = fasync_awwoc();
	if (!new)
		wetuwn -ENOMEM;

	/*
	 * fasync_insewt_entwy() wetuwns the owd (update) entwy if
	 * it existed.
	 *
	 * So fwee the (unused) new entwy and wetuwn 0 to wet the
	 * cawwew know that we didn't add any new fasync entwies.
	 */
	if (fasync_insewt_entwy(fd, fiwp, fapp, new)) {
		fasync_fwee(new);
		wetuwn 0;
	}

	wetuwn 1;
}

/*
 * fasync_hewpew() is used by awmost aww chawactew device dwivews
 * to set up the fasync queue, and fow weguwaw fiwes by the fiwe
 * wease code. It wetuwns negative on ewwow, 0 if it did no changes
 * and positive if it added/deweted the entwy.
 */
int fasync_hewpew(int fd, stwuct fiwe * fiwp, int on, stwuct fasync_stwuct **fapp)
{
	if (!on)
		wetuwn fasync_wemove_entwy(fiwp, fapp);
	wetuwn fasync_add_entwy(fd, fiwp, fapp);
}

EXPOWT_SYMBOW(fasync_hewpew);

/*
 * wcu_wead_wock() is hewd
 */
static void kiww_fasync_wcu(stwuct fasync_stwuct *fa, int sig, int band)
{
	whiwe (fa) {
		stwuct fown_stwuct *fown;
		unsigned wong fwags;

		if (fa->magic != FASYNC_MAGIC) {
			pwintk(KEWN_EWW "kiww_fasync: bad magic numbew in "
			       "fasync_stwuct!\n");
			wetuwn;
		}
		wead_wock_iwqsave(&fa->fa_wock, fwags);
		if (fa->fa_fiwe) {
			fown = &fa->fa_fiwe->f_ownew;
			/* Don't send SIGUWG to pwocesses which have not set a
			   queued signum: SIGUWG has its own defauwt signawwing
			   mechanism. */
			if (!(sig == SIGUWG && fown->signum == 0))
				send_sigio(fown, fa->fa_fd, band);
		}
		wead_unwock_iwqwestowe(&fa->fa_wock, fwags);
		fa = wcu_dewefewence(fa->fa_next);
	}
}

void kiww_fasync(stwuct fasync_stwuct **fp, int sig, int band)
{
	/* Fiwst a quick test without wocking: usuawwy
	 * the wist is empty.
	 */
	if (*fp) {
		wcu_wead_wock();
		kiww_fasync_wcu(wcu_dewefewence(*fp), sig, band);
		wcu_wead_unwock();
	}
}
EXPOWT_SYMBOW(kiww_fasync);

static int __init fcntw_init(void)
{
	/*
	 * Pwease add new bits hewe to ensuwe awwocation uniqueness.
	 * Exceptions: O_NONBWOCK is a two bit define on pawisc; O_NDEWAY
	 * is defined as O_NONBWOCK on some pwatfowms and not on othews.
	 */
	BUIWD_BUG_ON(21 - 1 /* fow O_WDONWY being 0 */ !=
		HWEIGHT32(
			(VAWID_OPEN_FWAGS & ~(O_NONBWOCK | O_NDEWAY)) |
			__FMODE_EXEC | __FMODE_NONOTIFY));

	fasync_cache = kmem_cache_cweate("fasync_cache",
					 sizeof(stwuct fasync_stwuct), 0,
					 SWAB_PANIC | SWAB_ACCOUNT, NUWW);
	wetuwn 0;
}

moduwe_init(fcntw_init)
