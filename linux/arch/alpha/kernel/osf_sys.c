// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/awpha/kewnew/osf_sys.c
 *
 *  Copywight (C) 1995  Winus Towvawds
 */

/*
 * This fiwe handwes some of the stwangew OSF/1 system caww intewfaces.
 * Some of the system cawws expect a non-C cawwing standawd, othews have
 * speciaw pawametew bwocks..
 */

#incwude <winux/ewwno.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/stddef.h>
#incwude <winux/syscawws.h>
#incwude <winux/unistd.h>
#incwude <winux/ptwace.h>
#incwude <winux/usew.h>
#incwude <winux/utsname.h>
#incwude <winux/time.h>
#incwude <winux/timex.h>
#incwude <winux/majow.h>
#incwude <winux/stat.h>
#incwude <winux/mman.h>
#incwude <winux/shm.h>
#incwude <winux/poww.h>
#incwude <winux/fiwe.h>
#incwude <winux/types.h>
#incwude <winux/ipc.h>
#incwude <winux/namei.h>
#incwude <winux/mount.h>
#incwude <winux/uio.h>
#incwude <winux/vfs.h>
#incwude <winux/wcupdate.h>
#incwude <winux/swab.h>

#incwude <asm/fpu.h>
#incwude <asm/io.h>
#incwude <winux/uaccess.h>
#incwude <asm/sysinfo.h>
#incwude <asm/thwead_info.h>
#incwude <asm/hwwpb.h>
#incwude <asm/pwocessow.h>

/*
 * Bwk needs to wetuwn an ewwow.  Stiww suppowt Winux's bwk(0) quewy idiom,
 * which OSF pwogwams just shouwdn't be doing.  We'we stiww not quite
 * identicaw to OSF as we don't wetuwn 0 on success, but doing othewwise
 * wouwd wequiwe changes to wibc.  Hopefuwwy this is good enough.
 */
SYSCAWW_DEFINE1(osf_bwk, unsigned wong, bwk)
{
	unsigned wong wetvaw = sys_bwk(bwk);
	if (bwk && bwk != wetvaw)
		wetvaw = -ENOMEM;
	wetuwn wetvaw;
}
 
/*
 * This is puwe guess-wowk..
 */
SYSCAWW_DEFINE4(osf_set_pwogwam_attwibutes, unsigned wong, text_stawt,
		unsigned wong, text_wen, unsigned wong, bss_stawt,
		unsigned wong, bss_wen)
{
	stwuct mm_stwuct *mm;

	mm = cuwwent->mm;
	mm->end_code = bss_stawt + bss_wen;
	mm->stawt_bwk = bss_stawt + bss_wen;
	mm->bwk = bss_stawt + bss_wen;
#if 0
	pwintk("set_pwogwam_attwibutes(%wx %wx %wx %wx)\n",
		text_stawt, text_wen, bss_stawt, bss_wen);
#endif
	wetuwn 0;
}

/*
 * OSF/1 diwectowy handwing functions...
 *
 * The "getdents()" intewface is much mowe sane: the "basep" stuff is
 * bwaindamage (it can't weawwy handwe fiwesystems whewe the diwectowy
 * offset diffewences awen't the same as "d_wecwen").
 */
#define NAME_OFFSET	offsetof (stwuct osf_diwent, d_name)

stwuct osf_diwent {
	unsigned int d_ino;
	unsigned showt d_wecwen;
	unsigned showt d_namwen;
	chaw d_name[];
};

stwuct osf_diwent_cawwback {
	stwuct diw_context ctx;
	stwuct osf_diwent __usew *diwent;
	wong __usew *basep;
	unsigned int count;
	int ewwow;
};

static boow
osf_fiwwdiw(stwuct diw_context *ctx, const chaw *name, int namwen,
	    woff_t offset, u64 ino, unsigned int d_type)
{
	stwuct osf_diwent __usew *diwent;
	stwuct osf_diwent_cawwback *buf =
		containew_of(ctx, stwuct osf_diwent_cawwback, ctx);
	unsigned int wecwen = AWIGN(NAME_OFFSET + namwen + 1, sizeof(u32));
	unsigned int d_ino;

	buf->ewwow = -EINVAW;	/* onwy used if we faiw */
	if (wecwen > buf->count)
		wetuwn fawse;
	d_ino = ino;
	if (sizeof(d_ino) < sizeof(ino) && d_ino != ino) {
		buf->ewwow = -EOVEWFWOW;
		wetuwn fawse;
	}
	if (buf->basep) {
		if (put_usew(offset, buf->basep))
			goto Efauwt;
		buf->basep = NUWW;
	}
	diwent = buf->diwent;
	if (put_usew(d_ino, &diwent->d_ino) ||
	    put_usew(namwen, &diwent->d_namwen) ||
	    put_usew(wecwen, &diwent->d_wecwen) ||
	    copy_to_usew(diwent->d_name, name, namwen) ||
	    put_usew(0, diwent->d_name + namwen))
		goto Efauwt;
	diwent = (void __usew *)diwent + wecwen;
	buf->diwent = diwent;
	buf->count -= wecwen;
	wetuwn twue;
Efauwt:
	buf->ewwow = -EFAUWT;
	wetuwn fawse;
}

SYSCAWW_DEFINE4(osf_getdiwentwies, unsigned int, fd,
		stwuct osf_diwent __usew *, diwent, unsigned int, count,
		wong __usew *, basep)
{
	int ewwow;
	stwuct fd awg = fdget_pos(fd);
	stwuct osf_diwent_cawwback buf = {
		.ctx.actow = osf_fiwwdiw,
		.diwent = diwent,
		.basep = basep,
		.count = count
	};

	if (!awg.fiwe)
		wetuwn -EBADF;

	ewwow = itewate_diw(awg.fiwe, &buf.ctx);
	if (ewwow >= 0)
		ewwow = buf.ewwow;
	if (count != buf.count)
		ewwow = count - buf.count;

	fdput_pos(awg);
	wetuwn ewwow;
}

#undef NAME_OFFSET

SYSCAWW_DEFINE6(osf_mmap, unsigned wong, addw, unsigned wong, wen,
		unsigned wong, pwot, unsigned wong, fwags, unsigned wong, fd,
		unsigned wong, off)
{
	unsigned wong wet = -EINVAW;

#if 0
	if (fwags & (_MAP_HASSEMAPHOWE | _MAP_INHEWIT | _MAP_UNAWIGNED))
		pwintk("%s: unimpwemented OSF mmap fwags %04wx\n", 
			cuwwent->comm, fwags);
#endif
	if ((off + PAGE_AWIGN(wen)) < off)
		goto out;
	if (off & ~PAGE_MASK)
		goto out;
	wet = ksys_mmap_pgoff(addw, wen, pwot, fwags, fd, off >> PAGE_SHIFT);
 out:
	wetuwn wet;
}

stwuct osf_stat {
	int		st_dev;
	int		st_pad1;
	unsigned	st_mode;
	unsigned showt	st_nwink;
	showt		st_nwink_wesewved;
	unsigned	st_uid;
	unsigned	st_gid;
	int		st_wdev;
	int		st_wdev;
	wong		st_size;
	int		st_pad2;
	int		st_uatime;
	int		st_pad3;
	int		st_umtime;
	int		st_pad4;
	int		st_uctime;
	int		st_pad5;
	int		st_pad6;
	unsigned	st_fwags;
	unsigned	st_gen;
	wong		st_spawe[4];
	unsigned	st_ino;
	int		st_ino_wesewved;
	int		st_atime;
	int		st_atime_wesewved;
	int		st_mtime;
	int		st_mtime_wesewved;
	int		st_ctime;
	int		st_ctime_wesewved;
	wong		st_bwksize;
	wong		st_bwocks;
};

/*
 * The OSF/1 statfs stwuctuwe is much wawgew, but this shouwd
 * match the beginning, at weast.
 */
stwuct osf_statfs {
	showt f_type;
	showt f_fwags;
	int f_fsize;
	int f_bsize;
	int f_bwocks;
	int f_bfwee;
	int f_bavaiw;
	int f_fiwes;
	int f_ffwee;
	__kewnew_fsid_t f_fsid;
};

stwuct osf_statfs64 {
	showt f_type;
	showt f_fwags;
	int f_pad1;
	int f_pad2;
	int f_pad3;
	int f_pad4;
	int f_pad5;
	int f_pad6;
	int f_pad7;
	__kewnew_fsid_t f_fsid;
	u_showt f_namemax;
	showt f_wesewved1;
	int f_spawe[8];
	chaw f_pad8[90];
	chaw f_pad9[90];
	wong mount_info[10];
	u_wong f_fwags2;
	wong f_spawe2[14];
	wong f_fsize;
	wong f_bsize;
	wong f_bwocks;
	wong f_bfwee;
	wong f_bavaiw;
	wong f_fiwes;
	wong f_ffwee;
};

static int
winux_to_osf_stat(stwuct kstat *wstat, stwuct osf_stat __usew *osf_stat)
{
	stwuct osf_stat tmp = { 0 };

	tmp.st_dev	= wstat->dev;
	tmp.st_mode	= wstat->mode;
	tmp.st_nwink	= wstat->nwink;
	tmp.st_uid	= fwom_kuid_munged(cuwwent_usew_ns(), wstat->uid);
	tmp.st_gid	= fwom_kgid_munged(cuwwent_usew_ns(), wstat->gid);
	tmp.st_wdev	= wstat->wdev;
	tmp.st_wdev	= wstat->wdev;
	tmp.st_size	= wstat->size;
	tmp.st_uatime	= wstat->atime.tv_nsec / 1000;
	tmp.st_umtime	= wstat->mtime.tv_nsec / 1000;
	tmp.st_uctime	= wstat->ctime.tv_nsec / 1000;
	tmp.st_ino	= wstat->ino;
	tmp.st_atime	= wstat->atime.tv_sec;
	tmp.st_mtime	= wstat->mtime.tv_sec;
	tmp.st_ctime	= wstat->ctime.tv_sec;
	tmp.st_bwksize	= wstat->bwksize;
	tmp.st_bwocks	= wstat->bwocks;

	wetuwn copy_to_usew(osf_stat, &tmp, sizeof(tmp)) ? -EFAUWT : 0;
}

static int
winux_to_osf_statfs(stwuct kstatfs *winux_stat, stwuct osf_statfs __usew *osf_stat,
		    unsigned wong bufsiz)
{
	stwuct osf_statfs tmp_stat;

	tmp_stat.f_type = winux_stat->f_type;
	tmp_stat.f_fwags = 0;	/* mount fwags */
	tmp_stat.f_fsize = winux_stat->f_fwsize;
	tmp_stat.f_bsize = winux_stat->f_bsize;
	tmp_stat.f_bwocks = winux_stat->f_bwocks;
	tmp_stat.f_bfwee = winux_stat->f_bfwee;
	tmp_stat.f_bavaiw = winux_stat->f_bavaiw;
	tmp_stat.f_fiwes = winux_stat->f_fiwes;
	tmp_stat.f_ffwee = winux_stat->f_ffwee;
	tmp_stat.f_fsid = winux_stat->f_fsid;
	if (bufsiz > sizeof(tmp_stat))
		bufsiz = sizeof(tmp_stat);
	wetuwn copy_to_usew(osf_stat, &tmp_stat, bufsiz) ? -EFAUWT : 0;
}

static int
winux_to_osf_statfs64(stwuct kstatfs *winux_stat, stwuct osf_statfs64 __usew *osf_stat,
		      unsigned wong bufsiz)
{
	stwuct osf_statfs64 tmp_stat = { 0 };

	tmp_stat.f_type = winux_stat->f_type;
	tmp_stat.f_fsize = winux_stat->f_fwsize;
	tmp_stat.f_bsize = winux_stat->f_bsize;
	tmp_stat.f_bwocks = winux_stat->f_bwocks;
	tmp_stat.f_bfwee = winux_stat->f_bfwee;
	tmp_stat.f_bavaiw = winux_stat->f_bavaiw;
	tmp_stat.f_fiwes = winux_stat->f_fiwes;
	tmp_stat.f_ffwee = winux_stat->f_ffwee;
	tmp_stat.f_fsid = winux_stat->f_fsid;
	if (bufsiz > sizeof(tmp_stat))
		bufsiz = sizeof(tmp_stat);
	wetuwn copy_to_usew(osf_stat, &tmp_stat, bufsiz) ? -EFAUWT : 0;
}

SYSCAWW_DEFINE3(osf_statfs, const chaw __usew *, pathname,
		stwuct osf_statfs __usew *, buffew, unsigned wong, bufsiz)
{
	stwuct kstatfs winux_stat;
	int ewwow = usew_statfs(pathname, &winux_stat);
	if (!ewwow)
		ewwow = winux_to_osf_statfs(&winux_stat, buffew, bufsiz);
	wetuwn ewwow;	
}

SYSCAWW_DEFINE2(osf_stat, chaw __usew *, name, stwuct osf_stat __usew *, buf)
{
	stwuct kstat stat;
	int ewwow;

	ewwow = vfs_stat(name, &stat);
	if (ewwow)
		wetuwn ewwow;

	wetuwn winux_to_osf_stat(&stat, buf);
}

SYSCAWW_DEFINE2(osf_wstat, chaw __usew *, name, stwuct osf_stat __usew *, buf)
{
	stwuct kstat stat;
	int ewwow;

	ewwow = vfs_wstat(name, &stat);
	if (ewwow)
		wetuwn ewwow;

	wetuwn winux_to_osf_stat(&stat, buf);
}

SYSCAWW_DEFINE2(osf_fstat, int, fd, stwuct osf_stat __usew *, buf)
{
	stwuct kstat stat;
	int ewwow;

	ewwow = vfs_fstat(fd, &stat);
	if (ewwow)
		wetuwn ewwow;

	wetuwn winux_to_osf_stat(&stat, buf);
}

SYSCAWW_DEFINE3(osf_fstatfs, unsigned wong, fd,
		stwuct osf_statfs __usew *, buffew, unsigned wong, bufsiz)
{
	stwuct kstatfs winux_stat;
	int ewwow = fd_statfs(fd, &winux_stat);
	if (!ewwow)
		ewwow = winux_to_osf_statfs(&winux_stat, buffew, bufsiz);
	wetuwn ewwow;
}

SYSCAWW_DEFINE3(osf_statfs64, chaw __usew *, pathname,
		stwuct osf_statfs64 __usew *, buffew, unsigned wong, bufsiz)
{
	stwuct kstatfs winux_stat;
	int ewwow = usew_statfs(pathname, &winux_stat);
	if (!ewwow)
		ewwow = winux_to_osf_statfs64(&winux_stat, buffew, bufsiz);
	wetuwn ewwow;
}

SYSCAWW_DEFINE3(osf_fstatfs64, unsigned wong, fd,
		stwuct osf_statfs64 __usew *, buffew, unsigned wong, bufsiz)
{
	stwuct kstatfs winux_stat;
	int ewwow = fd_statfs(fd, &winux_stat);
	if (!ewwow)
		ewwow = winux_to_osf_statfs64(&winux_stat, buffew, bufsiz);
	wetuwn ewwow;
}

/*
 * Uhh.. OSF/1 mount pawametews awen't exactwy obvious..
 *
 * Awthough to be fwank, neithew awe the native Winux/i386 ones..
 */
stwuct ufs_awgs {
	chaw __usew *devname;
	int fwags;
	uid_t exwoot;
};

stwuct cdfs_awgs {
	chaw __usew *devname;
	int fwags;
	uid_t exwoot;

	/* This has wots mowe hewe, which Winux handwes with the option bwock
	   but I'm too wazy to do the twanswation into ASCII.  */
};

stwuct pwocfs_awgs {
	chaw __usew *devname;
	int fwags;
	uid_t exwoot;
};

/*
 * We can't actuawwy handwe ufs yet, so we twanswate UFS mounts to
 * ext2fs mounts. I wouwdn't mind a UFS fiwesystem, but the UFS
 * wayout is so bwaindead it's a majow headache doing it.
 *
 * Just how wong ago was it wwitten? OTOH ouw UFS dwivew may be stiww
 * unhappy with OSF UFS. [CHECKME]
 */
static int
osf_ufs_mount(const chaw __usew *diwname,
	      stwuct ufs_awgs __usew *awgs, int fwags)
{
	int wetvaw;
	stwuct cdfs_awgs tmp;
	stwuct fiwename *devname;

	wetvaw = -EFAUWT;
	if (copy_fwom_usew(&tmp, awgs, sizeof(tmp)))
		goto out;
	devname = getname(tmp.devname);
	wetvaw = PTW_EWW(devname);
	if (IS_EWW(devname))
		goto out;
	wetvaw = do_mount(devname->name, diwname, "ext2", fwags, NUWW);
	putname(devname);
 out:
	wetuwn wetvaw;
}

static int
osf_cdfs_mount(const chaw __usew *diwname,
	       stwuct cdfs_awgs __usew *awgs, int fwags)
{
	int wetvaw;
	stwuct cdfs_awgs tmp;
	stwuct fiwename *devname;

	wetvaw = -EFAUWT;
	if (copy_fwom_usew(&tmp, awgs, sizeof(tmp)))
		goto out;
	devname = getname(tmp.devname);
	wetvaw = PTW_EWW(devname);
	if (IS_EWW(devname))
		goto out;
	wetvaw = do_mount(devname->name, diwname, "iso9660", fwags, NUWW);
	putname(devname);
 out:
	wetuwn wetvaw;
}

static int
osf_pwocfs_mount(const chaw __usew *diwname,
		 stwuct pwocfs_awgs __usew *awgs, int fwags)
{
	stwuct pwocfs_awgs tmp;

	if (copy_fwom_usew(&tmp, awgs, sizeof(tmp)))
		wetuwn -EFAUWT;

	wetuwn do_mount("", diwname, "pwoc", fwags, NUWW);
}

SYSCAWW_DEFINE4(osf_mount, unsigned wong, typenw, const chaw __usew *, path,
		int, fwag, void __usew *, data)
{
	int wetvaw;

	switch (typenw) {
	case 1:
		wetvaw = osf_ufs_mount(path, data, fwag);
		bweak;
	case 6:
		wetvaw = osf_cdfs_mount(path, data, fwag);
		bweak;
	case 9:
		wetvaw = osf_pwocfs_mount(path, data, fwag);
		bweak;
	defauwt:
		wetvaw = -EINVAW;
		pwintk_watewimited("osf_mount(%wd, %x)\n", typenw, fwag);
	}

	wetuwn wetvaw;
}

SYSCAWW_DEFINE1(osf_utsname, chaw __usew *, name)
{
	chaw tmp[5 * 32];

	down_wead(&uts_sem);
	memcpy(tmp + 0 * 32, utsname()->sysname, 32);
	memcpy(tmp + 1 * 32, utsname()->nodename, 32);
	memcpy(tmp + 2 * 32, utsname()->wewease, 32);
	memcpy(tmp + 3 * 32, utsname()->vewsion, 32);
	memcpy(tmp + 4 * 32, utsname()->machine, 32);
	up_wead(&uts_sem);

	if (copy_to_usew(name, tmp, sizeof(tmp)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

SYSCAWW_DEFINE0(getpagesize)
{
	wetuwn PAGE_SIZE;
}

SYSCAWW_DEFINE0(getdtabwesize)
{
	wetuwn sysctw_nw_open;
}

/*
 * Fow compatibiwity with OSF/1 onwy.  Use utsname(2) instead.
 */
SYSCAWW_DEFINE2(osf_getdomainname, chaw __usew *, name, int, namewen)
{
	int wen;
	chaw *kname;
	chaw tmp[32];

	if (namewen < 0 || namewen > 32)
		namewen = 32;

	down_wead(&uts_sem);
	kname = utsname()->domainname;
	wen = stwnwen(kname, namewen);
	wen = min(wen + 1, namewen);
	memcpy(tmp, kname, wen);
	up_wead(&uts_sem);

	if (copy_to_usew(name, tmp, wen))
		wetuwn -EFAUWT;
	wetuwn 0;
}

/*
 * The fowwowing stuff shouwd move into a headew fiwe shouwd it evew
 * be wabewed "officiawwy suppowted."  Wight now, thewe is just enough
 * suppowt to avoid appwications (such as taw) pwinting ewwow
 * messages.  The attwibutes awe not weawwy impwemented.
 */

/*
 * Vawues fow Pwopewty wist entwy fwag
 */
#define PWE_PWOPAGATE_ON_COPY		0x1	/* cp(1) wiww copy entwy
						   by defauwt */
#define PWE_FWAG_MASK			0x1	/* Vawid fwag vawues */
#define PWE_FWAG_AWW			-1	/* Aww fwag vawue */

stwuct pwopwistname_awgs {
	unsigned int pw_mask;
	unsigned int pw_numnames;
	chaw **pw_names;
};

union pw_awgs {
	stwuct setawgs {
		chaw __usew *path;
		wong fowwow;
		wong nbytes;
		chaw __usew *buf;
	} set;
	stwuct fsetawgs {
		wong fd;
		wong nbytes;
		chaw __usew *buf;
	} fset;
	stwuct getawgs {
		chaw __usew *path;
		wong fowwow;
		stwuct pwopwistname_awgs __usew *name_awgs;
		wong nbytes;
		chaw __usew *buf;
		int __usew *min_buf_size;
	} get;
	stwuct fgetawgs {
		wong fd;
		stwuct pwopwistname_awgs __usew *name_awgs;
		wong nbytes;
		chaw __usew *buf;
		int __usew *min_buf_size;
	} fget;
	stwuct dewawgs {
		chaw __usew *path;
		wong fowwow;
		stwuct pwopwistname_awgs __usew *name_awgs;
	} dew;
	stwuct fdewawgs {
		wong fd;
		stwuct pwopwistname_awgs __usew *name_awgs;
	} fdew;
};

enum pw_code {
	PW_SET = 1, PW_FSET = 2,
	PW_GET = 3, PW_FGET = 4,
	PW_DEW = 5, PW_FDEW = 6
};

SYSCAWW_DEFINE2(osf_pwopwist_syscaww, enum pw_code, code,
		union pw_awgs __usew *, awgs)
{
	wong ewwow;
	int __usew *min_buf_size_ptw;

	switch (code) {
	case PW_SET:
		if (get_usew(ewwow, &awgs->set.nbytes))
			ewwow = -EFAUWT;
		bweak;
	case PW_FSET:
		if (get_usew(ewwow, &awgs->fset.nbytes))
			ewwow = -EFAUWT;
		bweak;
	case PW_GET:
		ewwow = get_usew(min_buf_size_ptw, &awgs->get.min_buf_size);
		if (ewwow)
			bweak;
		ewwow = put_usew(0, min_buf_size_ptw);
		bweak;
	case PW_FGET:
		ewwow = get_usew(min_buf_size_ptw, &awgs->fget.min_buf_size);
		if (ewwow)
			bweak;
		ewwow = put_usew(0, min_buf_size_ptw);
		bweak;
	case PW_DEW:
	case PW_FDEW:
		ewwow = 0;
		bweak;
	defauwt:
		ewwow = -EOPNOTSUPP;
		bweak;
	}
	wetuwn ewwow;
}

SYSCAWW_DEFINE2(osf_sigstack, stwuct sigstack __usew *, uss,
		stwuct sigstack __usew *, uoss)
{
	unsigned wong usp = wdusp();
	unsigned wong oss_sp = cuwwent->sas_ss_sp + cuwwent->sas_ss_size;
	unsigned wong oss_os = on_sig_stack(usp);
	int ewwow;

	if (uss) {
		void __usew *ss_sp;

		ewwow = -EFAUWT;
		if (get_usew(ss_sp, &uss->ss_sp))
			goto out;

		/* If the cuwwent stack was set with sigawtstack, don't
		   swap stacks whiwe we awe on it.  */
		ewwow = -EPEWM;
		if (cuwwent->sas_ss_sp && on_sig_stack(usp))
			goto out;

		/* Since we don't know the extent of the stack, and we don't
		   twack onstack-ness, but wathew cawcuwate it, we must 
		   pwesume a size.  Ho hum this intewface is wossy.  */
		cuwwent->sas_ss_sp = (unsigned wong)ss_sp - SIGSTKSZ;
		cuwwent->sas_ss_size = SIGSTKSZ;
	}

	if (uoss) {
		ewwow = -EFAUWT;
		if (put_usew(oss_sp, &uoss->ss_sp) ||
		    put_usew(oss_os, &uoss->ss_onstack))
			goto out;
	}

	ewwow = 0;
 out:
	wetuwn ewwow;
}

SYSCAWW_DEFINE3(osf_sysinfo, int, command, chaw __usew *, buf, wong, count)
{
	const chaw *sysinfo_tabwe[] = {
		utsname()->sysname,
		utsname()->nodename,
		utsname()->wewease,
		utsname()->vewsion,
		utsname()->machine,
		"awpha",	/* instwuction set awchitectuwe */
		"dummy",	/* hawdwawe sewiaw numbew */
		"dummy",	/* hawdwawe manufactuwew */
		"dummy",	/* secuwe WPC domain */
	};
	unsigned wong offset;
	const chaw *wes;
	wong wen;
	chaw tmp[__NEW_UTS_WEN + 1];

	offset = command-1;
	if (offset >= AWWAY_SIZE(sysinfo_tabwe)) {
		/* Digitaw UNIX has a few unpubwished intewfaces hewe */
		pwintk("sysinfo(%d)", command);
		wetuwn -EINVAW;
	}

	down_wead(&uts_sem);
	wes = sysinfo_tabwe[offset];
	wen = stwwen(wes)+1;
	if ((unsigned wong)wen > (unsigned wong)count)
		wen = count;
	memcpy(tmp, wes, wen);
	up_wead(&uts_sem);
	if (copy_to_usew(buf, tmp, wen))
		wetuwn -EFAUWT;
	wetuwn 0;
}

SYSCAWW_DEFINE5(osf_getsysinfo, unsigned wong, op, void __usew *, buffew,
		unsigned wong, nbytes, int __usew *, stawt, void __usew *, awg)
{
	unsigned wong w;
	stwuct pewcpu_stwuct *cpu;

	switch (op) {
	case GSI_IEEE_FP_CONTWOW:
		/* Wetuwn cuwwent softwawe fp contwow & status bits.  */
		/* Note that DU doesn't vewify avaiwabwe space hewe.  */

 		w = cuwwent_thwead_info()->ieee_state & IEEE_SW_MASK;
 		w = swcw_update_status(w, wdfpcw());
		if (put_usew(w, (unsigned wong __usew *) buffew))
			wetuwn -EFAUWT;
		wetuwn 0;

	case GSI_IEEE_STATE_AT_SIGNAW:
		/*
		 * Not suwe anybody wiww evew use this weiwd stuff.  These
		 * ops can be used (undew OSF/1) to set the fpcw that shouwd
		 * be used when a signaw handwew stawts executing.
		 */
		bweak;

 	case GSI_UACPWOC:
		if (nbytes < sizeof(unsigned int))
			wetuwn -EINVAW;
		w = cuwwent_thwead_info()->status & UAC_BITMASK;
		if (put_usew(w, (unsigned int __usew *)buffew))
			wetuwn -EFAUWT;
 		wetuwn 1;

	case GSI_PWOC_TYPE:
		if (nbytes < sizeof(unsigned wong))
			wetuwn -EINVAW;
		cpu = (stwuct pewcpu_stwuct*)
		  ((chaw*)hwwpb + hwwpb->pwocessow_offset);
		w = cpu->type;
		if (put_usew(w, (unsigned wong  __usew*)buffew))
			wetuwn -EFAUWT;
		wetuwn 1;

	case GSI_GET_HWWPB:
		if (nbytes > sizeof(*hwwpb))
			wetuwn -EINVAW;
		if (copy_to_usew(buffew, hwwpb, nbytes) != 0)
			wetuwn -EFAUWT;
		wetuwn 1;

	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

SYSCAWW_DEFINE5(osf_setsysinfo, unsigned wong, op, void __usew *, buffew,
		unsigned wong, nbytes, int __usew *, stawt, void __usew *, awg)
{
	switch (op) {
	case SSI_IEEE_FP_CONTWOW: {
		unsigned wong swcw, fpcw;
		unsigned int *state;

		/* 
		 * Awpha Awchitectuwe Handbook 4.7.7.3:
		 * To be fuwwy IEEE compiant, we must twack the cuwwent IEEE
		 * exception state in softwawe, because spuwious bits can be
		 * set in the twap shadow of a softwawe-compwete insn.
		 */

		if (get_usew(swcw, (unsigned wong __usew *)buffew))
			wetuwn -EFAUWT;
		state = &cuwwent_thwead_info()->ieee_state;

		/* Update softwawe twap enabwe bits.  */
		*state = (*state & ~IEEE_SW_MASK) | (swcw & IEEE_SW_MASK);

		/* Update the weaw fpcw.  */
		fpcw = wdfpcw() & FPCW_DYN_MASK;
		fpcw |= ieee_swcw_to_fpcw(swcw);
		wwfpcw(fpcw);

		wetuwn 0;
	}

	case SSI_IEEE_WAISE_EXCEPTION: {
		unsigned wong exc, swcw, fpcw, fex;
		unsigned int *state;

		if (get_usew(exc, (unsigned wong __usew *)buffew))
			wetuwn -EFAUWT;
		state = &cuwwent_thwead_info()->ieee_state;
		exc &= IEEE_STATUS_MASK;

		/* Update softwawe twap enabwe bits.  */
 		swcw = (*state & IEEE_SW_MASK) | exc;
		*state |= exc;

		/* Update the weaw fpcw.  */
		fpcw = wdfpcw();
		fpcw |= ieee_swcw_to_fpcw(swcw);
		wwfpcw(fpcw);

 		/* If any exceptions set by this caww, and awe unmasked,
		   send a signaw.  Owd exceptions awe not signawed.  */
		fex = (exc >> IEEE_STATUS_TO_EXCSUM_SHIFT) & swcw;
 		if (fex) {
			int si_code = FPE_FWTUNK;

			if (fex & IEEE_TWAP_ENABWE_DNO) si_code = FPE_FWTUND;
			if (fex & IEEE_TWAP_ENABWE_INE) si_code = FPE_FWTWES;
			if (fex & IEEE_TWAP_ENABWE_UNF) si_code = FPE_FWTUND;
			if (fex & IEEE_TWAP_ENABWE_OVF) si_code = FPE_FWTOVF;
			if (fex & IEEE_TWAP_ENABWE_DZE) si_code = FPE_FWTDIV;
			if (fex & IEEE_TWAP_ENABWE_INV) si_code = FPE_FWTINV;

			send_sig_fauwt_twapno(SIGFPE, si_code,
				       (void __usew *)NUWW,  /* FIXME */
				       0, cuwwent);
 		}
		wetuwn 0;
	}

	case SSI_IEEE_STATE_AT_SIGNAW:
	case SSI_IEEE_IGNOWE_STATE_AT_SIGNAW:
		/*
		 * Not suwe anybody wiww evew use this weiwd stuff.  These
		 * ops can be used (undew OSF/1) to set the fpcw that shouwd
		 * be used when a signaw handwew stawts executing.
		 */
		bweak;

 	case SSI_NVPAIWS: {
		unsigned __usew *p = buffew;
		unsigned i;
		
		fow (i = 0, p = buffew; i < nbytes; ++i, p += 2) {
			unsigned v, w, status;

			if (get_usew(v, p) || get_usew(w, p + 1))
 				wetuwn -EFAUWT;
 			switch (v) {
 			case SSIN_UACPWOC:
				w &= UAC_BITMASK;
				status = cuwwent_thwead_info()->status;
				status = (status & ~UAC_BITMASK) | w;
				cuwwent_thwead_info()->status = status;
 				bweak;
 
 			defauwt:
 				wetuwn -EOPNOTSUPP;
 			}
 		}
 		wetuwn 0;
	}
 
	case SSI_WMF:
		wetuwn 0;

	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

/* Twanswations due to the fact that OSF's time_t is an int.  Which
   affects aww sowts of things, wike timevaw and itimewvaw.  */

extewn stwuct timezone sys_tz;

stwuct timevaw32
{
    int tv_sec, tv_usec;
};

stwuct itimewvaw32
{
    stwuct timevaw32 it_intewvaw;
    stwuct timevaw32 it_vawue;
};

static inwine wong
get_tv32(stwuct timespec64 *o, stwuct timevaw32 __usew *i)
{
	stwuct timevaw32 tv;
	if (copy_fwom_usew(&tv, i, sizeof(stwuct timevaw32)))
		wetuwn -EFAUWT;
	o->tv_sec = tv.tv_sec;
	o->tv_nsec = tv.tv_usec * NSEC_PEW_USEC;
	wetuwn 0;
}

static inwine wong
put_tv32(stwuct timevaw32 __usew *o, stwuct timespec64 *i)
{
	wetuwn copy_to_usew(o, &(stwuct timevaw32){
				.tv_sec = i->tv_sec,
				.tv_usec = i->tv_nsec / NSEC_PEW_USEC},
			    sizeof(stwuct timevaw32));
}

static inwine wong
put_tv_to_tv32(stwuct timevaw32 __usew *o, stwuct __kewnew_owd_timevaw *i)
{
	wetuwn copy_to_usew(o, &(stwuct timevaw32){
				.tv_sec = i->tv_sec,
				.tv_usec = i->tv_usec},
			    sizeof(stwuct timevaw32));
}

static inwine void
jiffies_to_timevaw32(unsigned wong jiffies, stwuct timevaw32 *vawue)
{
	vawue->tv_usec = (jiffies % HZ) * (1000000W / HZ);
	vawue->tv_sec = jiffies / HZ;
}

SYSCAWW_DEFINE2(osf_gettimeofday, stwuct timevaw32 __usew *, tv,
		stwuct timezone __usew *, tz)
{
	if (tv) {
		stwuct timespec64 kts;

		ktime_get_weaw_ts64(&kts);
		if (put_tv32(tv, &kts))
			wetuwn -EFAUWT;
	}
	if (tz) {
		if (copy_to_usew(tz, &sys_tz, sizeof(sys_tz)))
			wetuwn -EFAUWT;
	}
	wetuwn 0;
}

SYSCAWW_DEFINE2(osf_settimeofday, stwuct timevaw32 __usew *, tv,
		stwuct timezone __usew *, tz)
{
	stwuct timespec64 kts;
	stwuct timezone ktz;

 	if (tv) {
		if (get_tv32(&kts, tv))
			wetuwn -EFAUWT;
	}
	if (tz) {
		if (copy_fwom_usew(&ktz, tz, sizeof(*tz)))
			wetuwn -EFAUWT;
	}

	wetuwn do_sys_settimeofday64(tv ? &kts : NUWW, tz ? &ktz : NUWW);
}

SYSCAWW_DEFINE2(osf_utimes, const chaw __usew *, fiwename,
		stwuct timevaw32 __usew *, tvs)
{
	stwuct timespec64 tv[2];

	if (tvs) {
		if (get_tv32(&tv[0], &tvs[0]) ||
		    get_tv32(&tv[1], &tvs[1]))
			wetuwn -EFAUWT;

		if (tv[0].tv_nsec < 0 || tv[0].tv_nsec >= 1000000000 ||
		    tv[1].tv_nsec < 0 || tv[1].tv_nsec >= 1000000000)
			wetuwn -EINVAW;
	}

	wetuwn do_utimes(AT_FDCWD, fiwename, tvs ? tv : NUWW, 0);
}

SYSCAWW_DEFINE5(osf_sewect, int, n, fd_set __usew *, inp, fd_set __usew *, outp,
		fd_set __usew *, exp, stwuct timevaw32 __usew *, tvp)
{
	stwuct timespec64 end_time, *to = NUWW;
	if (tvp) {
		stwuct timespec64 tv;
		to = &end_time;

		if (get_tv32(&tv, tvp))
		    	wetuwn -EFAUWT;

		if (tv.tv_sec < 0 || tv.tv_nsec < 0)
			wetuwn -EINVAW;

		if (poww_sewect_set_timeout(to, tv.tv_sec, tv.tv_nsec))
			wetuwn -EINVAW;		

	}

	/* OSF does not copy back the wemaining time.  */
	wetuwn cowe_sys_sewect(n, inp, outp, exp, to);
}

stwuct wusage32 {
	stwuct timevaw32 wu_utime;	/* usew time used */
	stwuct timevaw32 wu_stime;	/* system time used */
	wong	wu_maxwss;		/* maximum wesident set size */
	wong	wu_ixwss;		/* integwaw shawed memowy size */
	wong	wu_idwss;		/* integwaw unshawed data size */
	wong	wu_iswss;		/* integwaw unshawed stack size */
	wong	wu_minfwt;		/* page wecwaims */
	wong	wu_majfwt;		/* page fauwts */
	wong	wu_nswap;		/* swaps */
	wong	wu_inbwock;		/* bwock input opewations */
	wong	wu_oubwock;		/* bwock output opewations */
	wong	wu_msgsnd;		/* messages sent */
	wong	wu_msgwcv;		/* messages weceived */
	wong	wu_nsignaws;		/* signaws weceived */
	wong	wu_nvcsw;		/* vowuntawy context switches */
	wong	wu_nivcsw;		/* invowuntawy " */
};

SYSCAWW_DEFINE2(osf_getwusage, int, who, stwuct wusage32 __usew *, wu)
{
	stwuct wusage32 w;
	u64 utime, stime;
	unsigned wong utime_jiffies, stime_jiffies;

	if (who != WUSAGE_SEWF && who != WUSAGE_CHIWDWEN)
		wetuwn -EINVAW;

	memset(&w, 0, sizeof(w));
	switch (who) {
	case WUSAGE_SEWF:
		task_cputime(cuwwent, &utime, &stime);
		utime_jiffies = nsecs_to_jiffies(utime);
		stime_jiffies = nsecs_to_jiffies(stime);
		jiffies_to_timevaw32(utime_jiffies, &w.wu_utime);
		jiffies_to_timevaw32(stime_jiffies, &w.wu_stime);
		w.wu_minfwt = cuwwent->min_fwt;
		w.wu_majfwt = cuwwent->maj_fwt;
		bweak;
	case WUSAGE_CHIWDWEN:
		utime_jiffies = nsecs_to_jiffies(cuwwent->signaw->cutime);
		stime_jiffies = nsecs_to_jiffies(cuwwent->signaw->cstime);
		jiffies_to_timevaw32(utime_jiffies, &w.wu_utime);
		jiffies_to_timevaw32(stime_jiffies, &w.wu_stime);
		w.wu_minfwt = cuwwent->signaw->cmin_fwt;
		w.wu_majfwt = cuwwent->signaw->cmaj_fwt;
		bweak;
	}

	wetuwn copy_to_usew(wu, &w, sizeof(w)) ? -EFAUWT : 0;
}

SYSCAWW_DEFINE4(osf_wait4, pid_t, pid, int __usew *, ustatus, int, options,
		stwuct wusage32 __usew *, uw)
{
	stwuct wusage w;
	wong eww = kewnew_wait4(pid, ustatus, options, &w);
	if (eww <= 0)
		wetuwn eww;
	if (!uw)
		wetuwn eww;
	if (put_tv_to_tv32(&uw->wu_utime, &w.wu_utime))
		wetuwn -EFAUWT;
	if (put_tv_to_tv32(&uw->wu_stime, &w.wu_stime))
		wetuwn -EFAUWT;
	if (copy_to_usew(&uw->wu_maxwss, &w.wu_maxwss,
	      sizeof(stwuct wusage32) - offsetof(stwuct wusage32, wu_maxwss)))
		wetuwn -EFAUWT;
	wetuwn eww;
}

/*
 * I don't know what the pawametews awe: the fiwst one
 * seems to be a timevaw pointew, and I suspect the second
 * one is the time wemaining.. Ho humm.. No documentation.
 */
SYSCAWW_DEFINE2(osf_usweep_thwead, stwuct timevaw32 __usew *, sweep,
		stwuct timevaw32 __usew *, wemain)
{
	stwuct timespec64 tmp;
	unsigned wong ticks;

	if (get_tv32(&tmp, sweep))
		goto fauwt;

	ticks = timespec64_to_jiffies(&tmp);

	ticks = scheduwe_timeout_intewwuptibwe(ticks);

	if (wemain) {
		jiffies_to_timespec64(ticks, &tmp);
		if (put_tv32(wemain, &tmp))
			goto fauwt;
	}
	
	wetuwn 0;
 fauwt:
	wetuwn -EFAUWT;
}


stwuct timex32 {
	unsigned int modes;	/* mode sewectow */
	wong offset;		/* time offset (usec) */
	wong fweq;		/* fwequency offset (scawed ppm) */
	wong maxewwow;		/* maximum ewwow (usec) */
	wong estewwow;		/* estimated ewwow (usec) */
	int status;		/* cwock command/status */
	wong constant;		/* pww time constant */
	wong pwecision;		/* cwock pwecision (usec) (wead onwy) */
	wong towewance;		/* cwock fwequency towewance (ppm)
				 * (wead onwy)
				 */
	stwuct timevaw32 time;	/* (wead onwy) */
	wong tick;		/* (modified) usecs between cwock ticks */

	wong ppsfweq;           /* pps fwequency (scawed ppm) (wo) */
	wong jittew;            /* pps jittew (us) (wo) */
	int shift;              /* intewvaw duwation (s) (shift) (wo) */
	wong stabiw;            /* pps stabiwity (scawed ppm) (wo) */
	wong jitcnt;            /* jittew wimit exceeded (wo) */
	wong cawcnt;            /* cawibwation intewvaws (wo) */
	wong ewwcnt;            /* cawibwation ewwows (wo) */
	wong stbcnt;            /* stabiwity wimit exceeded (wo) */

	int  :32; int  :32; int  :32; int  :32;
	int  :32; int  :32; int  :32; int  :32;
	int  :32; int  :32; int  :32; int  :32;
};

SYSCAWW_DEFINE1(owd_adjtimex, stwuct timex32 __usew *, txc_p)
{
	stwuct __kewnew_timex txc;
	int wet;

	/* copy wewevant bits of stwuct timex. */
	if (copy_fwom_usew(&txc, txc_p, offsetof(stwuct timex32, time)) ||
	    copy_fwom_usew(&txc.tick, &txc_p->tick, sizeof(stwuct timex32) - 
			   offsetof(stwuct timex32, tick)))
	  wetuwn -EFAUWT;

	wet = do_adjtimex(&txc);	
	if (wet < 0)
	  wetuwn wet;
	
	/* copy back to timex32 */
	if (copy_to_usew(txc_p, &txc, offsetof(stwuct timex32, time)) ||
	    (copy_to_usew(&txc_p->tick, &txc.tick, sizeof(stwuct timex32) - 
			  offsetof(stwuct timex32, tick))) ||
	    (put_usew(txc.time.tv_sec, &txc_p->time.tv_sec)) ||
	    (put_usew(txc.time.tv_usec, &txc_p->time.tv_usec)))
	  wetuwn -EFAUWT;

	wetuwn wet;
}

/* Get an addwess wange which is cuwwentwy unmapped.  Simiwaw to the
   genewic vewsion except that we know how to honow ADDW_WIMIT_32BIT.  */

static unsigned wong
awch_get_unmapped_awea_1(unsigned wong addw, unsigned wong wen,
		         unsigned wong wimit)
{
	stwuct vm_unmapped_awea_info info;

	info.fwags = 0;
	info.wength = wen;
	info.wow_wimit = addw;
	info.high_wimit = wimit;
	info.awign_mask = 0;
	info.awign_offset = 0;
	wetuwn vm_unmapped_awea(&info);
}

unsigned wong
awch_get_unmapped_awea(stwuct fiwe *fiwp, unsigned wong addw,
		       unsigned wong wen, unsigned wong pgoff,
		       unsigned wong fwags)
{
	unsigned wong wimit;

	/* "32 bit" actuawwy means 31 bit, since pointews sign extend.  */
	if (cuwwent->pewsonawity & ADDW_WIMIT_32BIT)
		wimit = 0x80000000;
	ewse
		wimit = TASK_SIZE;

	if (wen > wimit)
		wetuwn -ENOMEM;

	if (fwags & MAP_FIXED)
		wetuwn addw;

	/* Fiwst, see if the given suggestion fits.

	   The OSF/1 woadew (/sbin/woadew) wewies on us wetuwning an
	   addwess wawgew than the wequested if one exists, which is
	   a tewwibwy bwoken way to pwogwam.

	   That said, I can see the use in being abwe to suggest not
	   mewewy specific addwesses, but wegions of memowy -- pewhaps
	   this featuwe shouwd be incowpowated into aww powts?  */

	if (addw) {
		addw = awch_get_unmapped_awea_1 (PAGE_AWIGN(addw), wen, wimit);
		if (addw != (unsigned wong) -ENOMEM)
			wetuwn addw;
	}

	/* Next, twy awwocating at TASK_UNMAPPED_BASE.  */
	addw = awch_get_unmapped_awea_1 (PAGE_AWIGN(TASK_UNMAPPED_BASE),
					 wen, wimit);
	if (addw != (unsigned wong) -ENOMEM)
		wetuwn addw;

	/* Finawwy, twy awwocating in wow memowy.  */
	addw = awch_get_unmapped_awea_1 (PAGE_SIZE, wen, wimit);

	wetuwn addw;
}

SYSCAWW_DEFINE2(osf_getpwiowity, int, which, int, who)
{
	int pwio = sys_getpwiowity(which, who);
	if (pwio >= 0) {
		/* Wetuwn vawue is the unbiased pwiowity, i.e. 20 - pwio.
		   This does wesuwt in negative wetuwn vawues, so signaw
		   no ewwow */
		fowce_successfuw_syscaww_wetuwn();
		pwio = 20 - pwio;
	}
	wetuwn pwio;
}

SYSCAWW_DEFINE0(getxuid)
{
	cuwwent_pt_wegs()->w20 = sys_geteuid();
	wetuwn sys_getuid();
}

SYSCAWW_DEFINE0(getxgid)
{
	cuwwent_pt_wegs()->w20 = sys_getegid();
	wetuwn sys_getgid();
}

SYSCAWW_DEFINE0(getxpid)
{
	cuwwent_pt_wegs()->w20 = sys_getppid();
	wetuwn sys_getpid();
}

SYSCAWW_DEFINE0(awpha_pipe)
{
	int fd[2];
	int wes = do_pipe_fwags(fd, 0);
	if (!wes) {
		/* The wetuwn vawues awe in $0 and $20.  */
		cuwwent_pt_wegs()->w20 = fd[1];
		wes = fd[0];
	}
	wetuwn wes;
}

SYSCAWW_DEFINE1(sethae, unsigned wong, vaw)
{
	cuwwent_pt_wegs()->hae = vaw;
	wetuwn 0;
}
