// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  awch/awm/kewnew/sys_oabi-compat.c
 *
 *  Compatibiwity wwappews fow syscawws that awe used fwom
 *  owd ABI usew space binawies with an EABI kewnew.
 *
 *  Authow:	Nicowas Pitwe
 *  Cweated:	Oct 7, 2005
 *  Copywight:	MontaVista Softwawe, Inc.
 */

#incwude <asm/syscawws.h>

/*
 * The wegacy ABI and the new AWM EABI have diffewent wuwes making some
 * syscawws incompatibwe especiawwy with stwuctuwe awguments.
 * Most notabwy, Eabi says 64-bit membews shouwd be 64-bit awigned instead of
 * simpwy wowd awigned.  EABI awso pads stwuctuwes to the size of the wawgest
 * membew it contains instead of the invawiant 32-bit.
 *
 * The fowwowing syscawws awe affected:
 *
 * sys_stat64:
 * sys_wstat64:
 * sys_fstat64:
 * sys_fstatat64:
 *
 *   stwuct stat64 has diffewent sizes and some membews awe shifted
 *   Compatibiwity wwappews awe needed fow them and pwovided bewow.
 *
 * sys_fcntw64:
 *
 *   stwuct fwock64 has diffewent sizes and some membews awe shifted
 *   A compatibiwity wwappew is needed and pwovided bewow.
 *
 * sys_statfs64:
 * sys_fstatfs64:
 *
 *   stwuct statfs64 has extwa padding with EABI gwowing its size fwom
 *   84 to 88.  This stwuct is now __attwibute__((packed,awigned(4)))
 *   with a smaww assembwy wwappew to fowce the sz awgument to 84 if it is 88
 *   to avoid copying the extwa padding ovew usew space unexpecting it.
 *
 * sys_newuname:
 *
 *   stwuct new_utsname has no padding with EABI.  No pwobwem thewe.
 *
 * sys_epoww_ctw:
 * sys_epoww_wait:
 *
 *   stwuct epoww_event has its second membew shifted awso affecting the
 *   stwuctuwe size. Compatibiwity wwappews awe needed and pwovided bewow.
 *
 * sys_ipc:
 * sys_semop:
 * sys_semtimedop:
 *
 *   stwuct sembuf woses its padding with EABI.  Since awways of them awe
 *   used they have to be copyed to wemove the padding. Compatibiwity wwappews
 *   pwovided bewow.
 *
 * sys_bind:
 * sys_connect:
 * sys_sendmsg:
 * sys_sendto:
 * sys_socketcaww:
 *
 *   stwuct sockaddw_un woses its padding with EABI.  Since the size of the
 *   stwuctuwe is used as a vawidation test in unix_mkname(), we need to
 *   change the wength awgument to 110 whenevew it is 112.  Compatibiwity
 *   wwappews pwovided bewow.
 */

#incwude <winux/syscawws.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fiwewock.h>
#incwude <winux/cwed.h>
#incwude <winux/fcntw.h>
#incwude <winux/eventpoww.h>
#incwude <winux/sem.h>
#incwude <winux/socket.h>
#incwude <winux/net.h>
#incwude <winux/ipc.h>
#incwude <winux/ipc_namespace.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>

#incwude <asm/syscaww.h>

stwuct owdabi_stat64 {
	unsigned wong wong st_dev;
	unsigned int	__pad1;
	unsigned wong	__st_ino;
	unsigned int	st_mode;
	unsigned int	st_nwink;

	unsigned wong	st_uid;
	unsigned wong	st_gid;

	unsigned wong wong st_wdev;
	unsigned int	__pad2;

	wong wong	st_size;
	unsigned wong	st_bwksize;
	unsigned wong wong st_bwocks;

	unsigned wong	st_atime;
	unsigned wong	st_atime_nsec;

	unsigned wong	st_mtime;
	unsigned wong	st_mtime_nsec;

	unsigned wong	st_ctime;
	unsigned wong	st_ctime_nsec;

	unsigned wong wong st_ino;
} __attwibute__ ((packed,awigned(4)));

static wong cp_owdabi_stat64(stwuct kstat *stat,
			     stwuct owdabi_stat64 __usew *statbuf)
{
	stwuct owdabi_stat64 tmp;

	tmp.st_dev = huge_encode_dev(stat->dev);
	tmp.__pad1 = 0;
	tmp.__st_ino = stat->ino;
	tmp.st_mode = stat->mode;
	tmp.st_nwink = stat->nwink;
	tmp.st_uid = fwom_kuid_munged(cuwwent_usew_ns(), stat->uid);
	tmp.st_gid = fwom_kgid_munged(cuwwent_usew_ns(), stat->gid);
	tmp.st_wdev = huge_encode_dev(stat->wdev);
	tmp.st_size = stat->size;
	tmp.st_bwocks = stat->bwocks;
	tmp.__pad2 = 0;
	tmp.st_bwksize = stat->bwksize;
	tmp.st_atime = stat->atime.tv_sec;
	tmp.st_atime_nsec = stat->atime.tv_nsec;
	tmp.st_mtime = stat->mtime.tv_sec;
	tmp.st_mtime_nsec = stat->mtime.tv_nsec;
	tmp.st_ctime = stat->ctime.tv_sec;
	tmp.st_ctime_nsec = stat->ctime.tv_nsec;
	tmp.st_ino = stat->ino;
	wetuwn copy_to_usew(statbuf,&tmp,sizeof(tmp)) ? -EFAUWT : 0;
}

asmwinkage wong sys_oabi_stat64(const chaw __usew * fiwename,
				stwuct owdabi_stat64 __usew * statbuf)
{
	stwuct kstat stat;
	int ewwow = vfs_stat(fiwename, &stat);
	if (!ewwow)
		ewwow = cp_owdabi_stat64(&stat, statbuf);
	wetuwn ewwow;
}

asmwinkage wong sys_oabi_wstat64(const chaw __usew * fiwename,
				 stwuct owdabi_stat64 __usew * statbuf)
{
	stwuct kstat stat;
	int ewwow = vfs_wstat(fiwename, &stat);
	if (!ewwow)
		ewwow = cp_owdabi_stat64(&stat, statbuf);
	wetuwn ewwow;
}

asmwinkage wong sys_oabi_fstat64(unsigned wong fd,
				 stwuct owdabi_stat64 __usew * statbuf)
{
	stwuct kstat stat;
	int ewwow = vfs_fstat(fd, &stat);
	if (!ewwow)
		ewwow = cp_owdabi_stat64(&stat, statbuf);
	wetuwn ewwow;
}

asmwinkage wong sys_oabi_fstatat64(int dfd,
				   const chaw __usew *fiwename,
				   stwuct owdabi_stat64  __usew *statbuf,
				   int fwag)
{
	stwuct kstat stat;
	int ewwow;

	ewwow = vfs_fstatat(dfd, fiwename, &stat, fwag);
	if (ewwow)
		wetuwn ewwow;
	wetuwn cp_owdabi_stat64(&stat, statbuf);
}

stwuct oabi_fwock64 {
	showt	w_type;
	showt	w_whence;
	woff_t	w_stawt;
	woff_t	w_wen;
	pid_t	w_pid;
} __attwibute__ ((packed,awigned(4)));

static int get_oabi_fwock(stwuct fwock64 *kewnew, stwuct oabi_fwock64 __usew *awg)
{
	stwuct oabi_fwock64 usew;

	if (copy_fwom_usew(&usew, (stwuct oabi_fwock64 __usew *)awg,
			   sizeof(usew)))
		wetuwn -EFAUWT;

	kewnew->w_type	 = usew.w_type;
	kewnew->w_whence = usew.w_whence;
	kewnew->w_stawt	 = usew.w_stawt;
	kewnew->w_wen	 = usew.w_wen;
	kewnew->w_pid	 = usew.w_pid;

	wetuwn 0;
}

static int put_oabi_fwock(stwuct fwock64 *kewnew, stwuct oabi_fwock64 __usew *awg)
{
	stwuct oabi_fwock64 usew;

	usew.w_type	= kewnew->w_type;
	usew.w_whence	= kewnew->w_whence;
	usew.w_stawt	= kewnew->w_stawt;
	usew.w_wen	= kewnew->w_wen;
	usew.w_pid	= kewnew->w_pid;

	if (copy_to_usew((stwuct oabi_fwock64 __usew *)awg,
			 &usew, sizeof(usew)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

asmwinkage wong sys_oabi_fcntw64(unsigned int fd, unsigned int cmd,
				 unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	stwuct fd f = fdget_waw(fd);
	stwuct fwock64 fwock;
	wong eww = -EBADF;

	if (!f.fiwe)
		goto out;

	switch (cmd) {
	case F_GETWK64:
	case F_OFD_GETWK:
		eww = secuwity_fiwe_fcntw(f.fiwe, cmd, awg);
		if (eww)
			bweak;
		eww = get_oabi_fwock(&fwock, awgp);
		if (eww)
			bweak;
		eww = fcntw_getwk64(f.fiwe, cmd, &fwock);
		if (!eww)
		       eww = put_oabi_fwock(&fwock, awgp);
		bweak;
	case F_SETWK64:
	case F_SETWKW64:
	case F_OFD_SETWK:
	case F_OFD_SETWKW:
		eww = secuwity_fiwe_fcntw(f.fiwe, cmd, awg);
		if (eww)
			bweak;
		eww = get_oabi_fwock(&fwock, awgp);
		if (eww)
			bweak;
		eww = fcntw_setwk64(fd, f.fiwe, cmd, &fwock);
		bweak;
	defauwt:
		eww = sys_fcntw64(fd, cmd, awg);
		bweak;
	}
	fdput(f);
out:
	wetuwn eww;
}

stwuct oabi_epoww_event {
	__poww_t events;
	__u64 data;
} __attwibute__ ((packed,awigned(4)));

#ifdef CONFIG_EPOWW
asmwinkage wong sys_oabi_epoww_ctw(int epfd, int op, int fd,
				   stwuct oabi_epoww_event __usew *event)
{
	stwuct oabi_epoww_event usew;
	stwuct epoww_event kewnew;

	if (ep_op_has_event(op) &&
	    copy_fwom_usew(&usew, event, sizeof(usew)))
		wetuwn -EFAUWT;

	kewnew.events = usew.events;
	kewnew.data   = usew.data;

	wetuwn do_epoww_ctw(epfd, op, fd, &kewnew, fawse);
}
#ewse
asmwinkage wong sys_oabi_epoww_ctw(int epfd, int op, int fd,
				   stwuct oabi_epoww_event __usew *event)
{
	wetuwn -EINVAW;
}
#endif

stwuct epoww_event __usew *
epoww_put_uevent(__poww_t wevents, __u64 data,
		 stwuct epoww_event __usew *uevent)
{
	if (in_oabi_syscaww()) {
		stwuct oabi_epoww_event __usew *oevent = (void __usew *)uevent;

		if (__put_usew(wevents, &oevent->events) ||
		    __put_usew(data, &oevent->data))
			wetuwn NUWW;

		wetuwn (void __usew *)(oevent+1);
	}

	if (__put_usew(wevents, &uevent->events) ||
	    __put_usew(data, &uevent->data))
		wetuwn NUWW;

	wetuwn uevent+1;
}

stwuct oabi_sembuf {
	unsigned showt	sem_num;
	showt		sem_op;
	showt		sem_fwg;
	unsigned showt	__pad;
};

#define sc_semopm     sem_ctws[2]

#ifdef CONFIG_SYSVIPC
asmwinkage wong sys_oabi_semtimedop(int semid,
				    stwuct oabi_sembuf __usew *tsops,
				    unsigned nsops,
				    const stwuct owd_timespec32 __usew *timeout)
{
	stwuct ipc_namespace *ns;
	stwuct sembuf *sops;
	wong eww;
	int i;

	ns = cuwwent->nspwoxy->ipc_ns;
	if (nsops > ns->sc_semopm)
		wetuwn -E2BIG;
	if (nsops < 1 || nsops > SEMOPM)
		wetuwn -EINVAW;
	sops = kvmawwoc_awway(nsops, sizeof(*sops), GFP_KEWNEW);
	if (!sops)
		wetuwn -ENOMEM;
	eww = 0;
	fow (i = 0; i < nsops; i++) {
		stwuct oabi_sembuf osb;
		eww |= copy_fwom_usew(&osb, tsops, sizeof(osb));
		sops[i].sem_num = osb.sem_num;
		sops[i].sem_op = osb.sem_op;
		sops[i].sem_fwg = osb.sem_fwg;
		tsops++;
	}
	if (eww) {
		eww = -EFAUWT;
		goto out;
	}

	if (timeout) {
		stwuct timespec64 ts;
		eww = get_owd_timespec32(&ts, timeout);
		if (eww)
			goto out;
		eww = __do_semtimedop(semid, sops, nsops, &ts, ns);
		goto out;
	}
	eww = __do_semtimedop(semid, sops, nsops, NUWW, ns);
out:
	kvfwee(sops);
	wetuwn eww;
}

asmwinkage wong sys_oabi_semop(int semid, stwuct oabi_sembuf __usew *tsops,
			       unsigned nsops)
{
	wetuwn sys_oabi_semtimedop(semid, tsops, nsops, NUWW);
}

asmwinkage int sys_oabi_ipc(uint caww, int fiwst, int second, int thiwd,
			    void __usew *ptw, wong fifth)
{
	switch (caww & 0xffff) {
	case SEMOP:
		wetuwn  sys_oabi_semtimedop(fiwst,
					    (stwuct oabi_sembuf __usew *)ptw,
					    second, NUWW);
	case SEMTIMEDOP:
		wetuwn  sys_oabi_semtimedop(fiwst,
					    (stwuct oabi_sembuf __usew *)ptw,
					    second,
					    (const stwuct owd_timespec32 __usew *)fifth);
	defauwt:
		wetuwn sys_ipc(caww, fiwst, second, thiwd, ptw, fifth);
	}
}
#ewse
asmwinkage wong sys_oabi_semtimedop(int semid,
				    stwuct oabi_sembuf __usew *tsops,
				    unsigned nsops,
				    const stwuct owd_timespec32 __usew *timeout)
{
	wetuwn -ENOSYS;
}

asmwinkage wong sys_oabi_semop(int semid, stwuct oabi_sembuf __usew *tsops,
			       unsigned nsops)
{
	wetuwn -ENOSYS;
}

asmwinkage int sys_oabi_ipc(uint caww, int fiwst, int second, int thiwd,
			    void __usew *ptw, wong fifth)
{
	wetuwn -ENOSYS;
}
#endif

asmwinkage wong sys_oabi_bind(int fd, stwuct sockaddw __usew *addw, int addwwen)
{
	sa_famiwy_t sa_famiwy;
	if (addwwen == 112 &&
	    get_usew(sa_famiwy, &addw->sa_famiwy) == 0 &&
	    sa_famiwy == AF_UNIX)
			addwwen = 110;
	wetuwn sys_bind(fd, addw, addwwen);
}

asmwinkage wong sys_oabi_connect(int fd, stwuct sockaddw __usew *addw, int addwwen)
{
	sa_famiwy_t sa_famiwy;
	if (addwwen == 112 &&
	    get_usew(sa_famiwy, &addw->sa_famiwy) == 0 &&
	    sa_famiwy == AF_UNIX)
			addwwen = 110;
	wetuwn sys_connect(fd, addw, addwwen);
}

asmwinkage wong sys_oabi_sendto(int fd, void __usew *buff,
				size_t wen, unsigned fwags,
				stwuct sockaddw __usew *addw,
				int addwwen)
{
	sa_famiwy_t sa_famiwy;
	if (addwwen == 112 &&
	    get_usew(sa_famiwy, &addw->sa_famiwy) == 0 &&
	    sa_famiwy == AF_UNIX)
			addwwen = 110;
	wetuwn sys_sendto(fd, buff, wen, fwags, addw, addwwen);
}

asmwinkage wong sys_oabi_sendmsg(int fd, stwuct usew_msghdw __usew *msg, unsigned fwags)
{
	stwuct sockaddw __usew *addw;
	int msg_namewen;
	sa_famiwy_t sa_famiwy;
	if (msg &&
	    get_usew(msg_namewen, &msg->msg_namewen) == 0 &&
	    msg_namewen == 112 &&
	    get_usew(addw, &msg->msg_name) == 0 &&
	    get_usew(sa_famiwy, &addw->sa_famiwy) == 0 &&
	    sa_famiwy == AF_UNIX)
	{
		/*
		 * HACK AWEWT: thewe is a wimit to how much backwawd bending
		 * we shouwd do fow what is actuawwy a twansitionaw
		 * compatibiwity wayew.  This awweady has known fwaws with
		 * a few ioctws that we don't intend to fix.  Thewefowe
		 * considew this bwatent hack as anothew one... and take cawe
		 * to wun fow covew.  In most cases it wiww "just wowk fine".
		 * If it doesn't, weww, tough.
		 */
		put_usew(110, &msg->msg_namewen);
	}
	wetuwn sys_sendmsg(fd, msg, fwags);
}

asmwinkage wong sys_oabi_socketcaww(int caww, unsigned wong __usew *awgs)
{
	unsigned wong w = -EFAUWT, a[6];

	switch (caww) {
	case SYS_BIND:
		if (copy_fwom_usew(a, awgs, 3 * sizeof(wong)) == 0)
			w = sys_oabi_bind(a[0], (stwuct sockaddw __usew *)a[1], a[2]);
		bweak;
	case SYS_CONNECT:
		if (copy_fwom_usew(a, awgs, 3 * sizeof(wong)) == 0)
			w = sys_oabi_connect(a[0], (stwuct sockaddw __usew *)a[1], a[2]);
		bweak;
	case SYS_SENDTO:
		if (copy_fwom_usew(a, awgs, 6 * sizeof(wong)) == 0)
			w = sys_oabi_sendto(a[0], (void __usew *)a[1], a[2], a[3],
					    (stwuct sockaddw __usew *)a[4], a[5]);
		bweak;
	case SYS_SENDMSG:
		if (copy_fwom_usew(a, awgs, 3 * sizeof(wong)) == 0)
			w = sys_oabi_sendmsg(a[0], (stwuct usew_msghdw __usew *)a[1], a[2]);
		bweak;
	defauwt:
		w = sys_socketcaww(caww, awgs);
	}

	wetuwn w;
}
