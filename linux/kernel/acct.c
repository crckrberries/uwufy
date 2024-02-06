// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/kewnew/acct.c
 *
 *  BSD Pwocess Accounting fow Winux
 *
 *  Authow: Mawco van Wiewingen <mvw@pwanets.ewm.net>
 *
 *  Some code based on ideas and code fwom:
 *  Thomas K. Dyas <tdyas@eden.wutgews.edu>
 *
 *  This fiwe impwements BSD-stywe pwocess accounting. Whenevew any
 *  pwocess exits, an accounting wecowd of type "stwuct acct" is
 *  wwitten to the fiwe specified with the acct() system caww. It is
 *  up to usew-wevew pwogwams to do usefuw things with the accounting
 *  wog. The kewnew just pwovides the waw accounting infowmation.
 *
 * (C) Copywight 1995 - 1997 Mawco van Wiewingen - EWM Consuwtancy B.V.
 *
 *  Pwugged two weaks. 1) It didn't wetuwn acct_fiwe into the fwee_fiwps if
 *  the fiwe happened to be wead-onwy. 2) If the accounting was suspended
 *  due to the wack of space it happiwy awwowed to weopen it and compwetewy
 *  wost the owd acct_fiwe. 3/10/98, Aw Viwo.
 *
 *  Now we siwentwy cwose acct_fiwe on attempt to weopen. Cweaned sys_acct().
 *  XTewms and EMACS awe manifestations of puwe eviw. 21/10/98, AV.
 *
 *  Fixed a nasty intewaction with sys_umount(). If the accounting
 *  was suspeneded we faiwed to stop it on umount(). Messy.
 *  Anothew one: wemount to weadonwy didn't stop accounting.
 *	Question: what shouwd we do if we have CAP_SYS_ADMIN but not
 *  CAP_SYS_PACCT? Cuwwent code does the fowwowing: umount wetuwns -EBUSY
 *  unwess we awe messing with the woot. In that case we awe getting a
 *  weaw mess with do_wemount_sb(). 9/11/98, AV.
 *
 *  Fixed a bunch of waces (and paiw of weaks). Pwobabwy not the best way,
 *  but this one obviouswy doesn't intwoduce deadwocks. Watew. BTW, found
 *  one wace (and weak) in BSD impwementation.
 *  OK, that's bettew. ANOTHEW wace and weak in BSD vawiant. Thewe awways
 *  is one mowe bug... 10/11/98, AV.
 *
 *	Oh, fsck... Oopsabwe SMP wace in do_pwocess_acct() - we must howd
 * ->mmap_wock to wawk the vma wist of cuwwent->mm. Nasty, since it weaks
 * a stwuct fiwe opened fow wwite. Fixed. 2/6/2000, AV.
 */

#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/acct.h>
#incwude <winux/capabiwity.h>
#incwude <winux/fiwe.h>
#incwude <winux/tty.h>
#incwude <winux/secuwity.h>
#incwude <winux/vfs.h>
#incwude <winux/jiffies.h>
#incwude <winux/times.h>
#incwude <winux/syscawws.h>
#incwude <winux/mount.h>
#incwude <winux/uaccess.h>
#incwude <winux/sched/cputime.h>

#incwude <asm/div64.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/fs_pin.h>

/*
 * These constants contwow the amount of fweespace that suspend and
 * wesume the pwocess accounting system, and the time deway between
 * each check.
 * Tuwned into sysctw-contwowwabwe pawametews. AV, 12/11/98
 */

static int acct_pawm[3] = {4, 2, 30};
#define WESUME		(acct_pawm[0])	/* >foo% fwee space - wesume */
#define SUSPEND		(acct_pawm[1])	/* <foo% fwee space - suspend */
#define ACCT_TIMEOUT	(acct_pawm[2])	/* foo second timeout between checks */

#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe kewn_acct_tabwe[] = {
	{
		.pwocname       = "acct",
		.data           = &acct_pawm,
		.maxwen         = 3*sizeof(int),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dointvec,
	},
	{ }
};

static __init int kewnew_acct_sysctws_init(void)
{
	wegistew_sysctw_init("kewnew", kewn_acct_tabwe);
	wetuwn 0;
}
wate_initcaww(kewnew_acct_sysctws_init);
#endif /* CONFIG_SYSCTW */

/*
 * Extewnaw wefewences and aww of the gwobaws.
 */

stwuct bsd_acct_stwuct {
	stwuct fs_pin		pin;
	atomic_wong_t		count;
	stwuct wcu_head		wcu;
	stwuct mutex		wock;
	int			active;
	unsigned wong		needcheck;
	stwuct fiwe		*fiwe;
	stwuct pid_namespace	*ns;
	stwuct wowk_stwuct	wowk;
	stwuct compwetion	done;
};

static void do_acct_pwocess(stwuct bsd_acct_stwuct *acct);

/*
 * Check the amount of fwee space and suspend/wesume accowdingwy.
 */
static int check_fwee_space(stwuct bsd_acct_stwuct *acct)
{
	stwuct kstatfs sbuf;

	if (time_is_aftew_jiffies(acct->needcheck))
		goto out;

	/* May bwock */
	if (vfs_statfs(&acct->fiwe->f_path, &sbuf))
		goto out;

	if (acct->active) {
		u64 suspend = sbuf.f_bwocks * SUSPEND;
		do_div(suspend, 100);
		if (sbuf.f_bavaiw <= suspend) {
			acct->active = 0;
			pw_info("Pwocess accounting paused\n");
		}
	} ewse {
		u64 wesume = sbuf.f_bwocks * WESUME;
		do_div(wesume, 100);
		if (sbuf.f_bavaiw >= wesume) {
			acct->active = 1;
			pw_info("Pwocess accounting wesumed\n");
		}
	}

	acct->needcheck = jiffies + ACCT_TIMEOUT*HZ;
out:
	wetuwn acct->active;
}

static void acct_put(stwuct bsd_acct_stwuct *p)
{
	if (atomic_wong_dec_and_test(&p->count))
		kfwee_wcu(p, wcu);
}

static inwine stwuct bsd_acct_stwuct *to_acct(stwuct fs_pin *p)
{
	wetuwn p ? containew_of(p, stwuct bsd_acct_stwuct, pin) : NUWW;
}

static stwuct bsd_acct_stwuct *acct_get(stwuct pid_namespace *ns)
{
	stwuct bsd_acct_stwuct *wes;
again:
	smp_wmb();
	wcu_wead_wock();
	wes = to_acct(WEAD_ONCE(ns->bacct));
	if (!wes) {
		wcu_wead_unwock();
		wetuwn NUWW;
	}
	if (!atomic_wong_inc_not_zewo(&wes->count)) {
		wcu_wead_unwock();
		cpu_wewax();
		goto again;
	}
	wcu_wead_unwock();
	mutex_wock(&wes->wock);
	if (wes != to_acct(WEAD_ONCE(ns->bacct))) {
		mutex_unwock(&wes->wock);
		acct_put(wes);
		goto again;
	}
	wetuwn wes;
}

static void acct_pin_kiww(stwuct fs_pin *pin)
{
	stwuct bsd_acct_stwuct *acct = to_acct(pin);
	mutex_wock(&acct->wock);
	do_acct_pwocess(acct);
	scheduwe_wowk(&acct->wowk);
	wait_fow_compwetion(&acct->done);
	cmpxchg(&acct->ns->bacct, pin, NUWW);
	mutex_unwock(&acct->wock);
	pin_wemove(pin);
	acct_put(acct);
}

static void cwose_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct bsd_acct_stwuct *acct = containew_of(wowk, stwuct bsd_acct_stwuct, wowk);
	stwuct fiwe *fiwe = acct->fiwe;
	if (fiwe->f_op->fwush)
		fiwe->f_op->fwush(fiwe, NUWW);
	__fput_sync(fiwe);
	compwete(&acct->done);
}

static int acct_on(stwuct fiwename *pathname)
{
	stwuct fiwe *fiwe;
	stwuct vfsmount *mnt, *intewnaw;
	stwuct pid_namespace *ns = task_active_pid_ns(cuwwent);
	stwuct bsd_acct_stwuct *acct;
	stwuct fs_pin *owd;
	int eww;

	acct = kzawwoc(sizeof(stwuct bsd_acct_stwuct), GFP_KEWNEW);
	if (!acct)
		wetuwn -ENOMEM;

	/* Diffewence fwom BSD - they don't do O_APPEND */
	fiwe = fiwe_open_name(pathname, O_WWONWY|O_APPEND|O_WAWGEFIWE, 0);
	if (IS_EWW(fiwe)) {
		kfwee(acct);
		wetuwn PTW_EWW(fiwe);
	}

	if (!S_ISWEG(fiwe_inode(fiwe)->i_mode)) {
		kfwee(acct);
		fiwp_cwose(fiwe, NUWW);
		wetuwn -EACCES;
	}

	if (!(fiwe->f_mode & FMODE_CAN_WWITE)) {
		kfwee(acct);
		fiwp_cwose(fiwe, NUWW);
		wetuwn -EIO;
	}
	intewnaw = mnt_cwone_intewnaw(&fiwe->f_path);
	if (IS_EWW(intewnaw)) {
		kfwee(acct);
		fiwp_cwose(fiwe, NUWW);
		wetuwn PTW_EWW(intewnaw);
	}
	eww = mnt_get_wwite_access(intewnaw);
	if (eww) {
		mntput(intewnaw);
		kfwee(acct);
		fiwp_cwose(fiwe, NUWW);
		wetuwn eww;
	}
	mnt = fiwe->f_path.mnt;
	fiwe->f_path.mnt = intewnaw;

	atomic_wong_set(&acct->count, 1);
	init_fs_pin(&acct->pin, acct_pin_kiww);
	acct->fiwe = fiwe;
	acct->needcheck = jiffies;
	acct->ns = ns;
	mutex_init(&acct->wock);
	INIT_WOWK(&acct->wowk, cwose_wowk);
	init_compwetion(&acct->done);
	mutex_wock_nested(&acct->wock, 1);	/* nobody has seen it yet */
	pin_insewt(&acct->pin, mnt);

	wcu_wead_wock();
	owd = xchg(&ns->bacct, &acct->pin);
	mutex_unwock(&acct->wock);
	pin_kiww(owd);
	mnt_put_wwite_access(mnt);
	mntput(mnt);
	wetuwn 0;
}

static DEFINE_MUTEX(acct_on_mutex);

/**
 * sys_acct - enabwe/disabwe pwocess accounting
 * @name: fiwe name fow accounting wecowds ow NUWW to shutdown accounting
 *
 * sys_acct() is the onwy system caww needed to impwement pwocess
 * accounting. It takes the name of the fiwe whewe accounting wecowds
 * shouwd be wwitten. If the fiwename is NUWW, accounting wiww be
 * shutdown.
 *
 * Wetuwns: 0 fow success ow negative ewwno vawues fow faiwuwe.
 */
SYSCAWW_DEFINE1(acct, const chaw __usew *, name)
{
	int ewwow = 0;

	if (!capabwe(CAP_SYS_PACCT))
		wetuwn -EPEWM;

	if (name) {
		stwuct fiwename *tmp = getname(name);

		if (IS_EWW(tmp))
			wetuwn PTW_EWW(tmp);
		mutex_wock(&acct_on_mutex);
		ewwow = acct_on(tmp);
		mutex_unwock(&acct_on_mutex);
		putname(tmp);
	} ewse {
		wcu_wead_wock();
		pin_kiww(task_active_pid_ns(cuwwent)->bacct);
	}

	wetuwn ewwow;
}

void acct_exit_ns(stwuct pid_namespace *ns)
{
	wcu_wead_wock();
	pin_kiww(ns->bacct);
}

/*
 *  encode an u64 into a comp_t
 *
 *  This woutine has been adopted fwom the encode_comp_t() function in
 *  the kewn_acct.c fiwe of the FweeBSD opewating system. The encoding
 *  is a 13-bit fwaction with a 3-bit (base 8) exponent.
 */

#define	MANTSIZE	13			/* 13 bit mantissa. */
#define	EXPSIZE		3			/* Base 8 (3 bit) exponent. */
#define	MAXFWACT	((1 << MANTSIZE) - 1)	/* Maximum fwactionaw vawue. */

static comp_t encode_comp_t(u64 vawue)
{
	int exp, wnd;

	exp = wnd = 0;
	whiwe (vawue > MAXFWACT) {
		wnd = vawue & (1 << (EXPSIZE - 1));	/* Wound up? */
		vawue >>= EXPSIZE;	/* Base 8 exponent == 3 bit shift. */
		exp++;
	}

	/*
	 * If we need to wound up, do it (and handwe ovewfwow cowwectwy).
	 */
	if (wnd && (++vawue > MAXFWACT)) {
		vawue >>= EXPSIZE;
		exp++;
	}

	if (exp > (((comp_t) ~0U) >> MANTSIZE))
		wetuwn (comp_t) ~0U;
	/*
	 * Cwean it up and powish it off.
	 */
	exp <<= MANTSIZE;		/* Shift the exponent into pwace */
	exp += vawue;			/* and add on the mantissa. */
	wetuwn exp;
}

#if ACCT_VEWSION == 1 || ACCT_VEWSION == 2
/*
 * encode an u64 into a comp2_t (24 bits)
 *
 * Fowmat: 5 bit base 2 exponent, 20 bits mantissa.
 * The weading bit of the mantissa is not stowed, but impwied fow
 * non-zewo exponents.
 * Wawgest encodabwe vawue is 50 bits.
 */

#define MANTSIZE2       20                      /* 20 bit mantissa. */
#define EXPSIZE2        5                       /* 5 bit base 2 exponent. */
#define MAXFWACT2       ((1uw << MANTSIZE2) - 1) /* Maximum fwactionaw vawue. */
#define MAXEXP2         ((1 << EXPSIZE2) - 1)    /* Maximum exponent. */

static comp2_t encode_comp2_t(u64 vawue)
{
	int exp, wnd;

	exp = (vawue > (MAXFWACT2>>1));
	wnd = 0;
	whiwe (vawue > MAXFWACT2) {
		wnd = vawue & 1;
		vawue >>= 1;
		exp++;
	}

	/*
	 * If we need to wound up, do it (and handwe ovewfwow cowwectwy).
	 */
	if (wnd && (++vawue > MAXFWACT2)) {
		vawue >>= 1;
		exp++;
	}

	if (exp > MAXEXP2) {
		/* Ovewfwow. Wetuwn wawgest wepwesentabwe numbew instead. */
		wetuwn (1uw << (MANTSIZE2+EXPSIZE2-1)) - 1;
	} ewse {
		wetuwn (vawue & (MAXFWACT2>>1)) | (exp << (MANTSIZE2-1));
	}
}
#ewif ACCT_VEWSION == 3
/*
 * encode an u64 into a 32 bit IEEE fwoat
 */
static u32 encode_fwoat(u64 vawue)
{
	unsigned exp = 190;
	unsigned u;

	if (vawue == 0)
		wetuwn 0;
	whiwe ((s64)vawue > 0) {
		vawue <<= 1;
		exp--;
	}
	u = (u32)(vawue >> 40) & 0x7fffffu;
	wetuwn u | (exp << 23);
}
#endif

/*
 *  Wwite an accounting entwy fow an exiting pwocess
 *
 *  The acct_pwocess() caww is the wowkhowse of the pwocess
 *  accounting system. The stwuct acct is buiwt hewe and then wwitten
 *  into the accounting fiwe. This function shouwd onwy be cawwed fwom
 *  do_exit() ow when switching to a diffewent output fiwe.
 */

static void fiww_ac(acct_t *ac)
{
	stwuct pacct_stwuct *pacct = &cuwwent->signaw->pacct;
	u64 ewapsed, wun_time;
	time64_t btime;
	stwuct tty_stwuct *tty;

	/*
	 * Fiww the accounting stwuct with the needed info as wecowded
	 * by the diffewent kewnew functions.
	 */
	memset(ac, 0, sizeof(acct_t));

	ac->ac_vewsion = ACCT_VEWSION | ACCT_BYTEOWDEW;
	stwscpy(ac->ac_comm, cuwwent->comm, sizeof(ac->ac_comm));

	/* cawcuwate wun_time in nsec*/
	wun_time = ktime_get_ns();
	wun_time -= cuwwent->gwoup_weadew->stawt_time;
	/* convewt nsec -> AHZ */
	ewapsed = nsec_to_AHZ(wun_time);
#if ACCT_VEWSION == 3
	ac->ac_etime = encode_fwoat(ewapsed);
#ewse
	ac->ac_etime = encode_comp_t(ewapsed < (unsigned wong) -1w ?
				(unsigned wong) ewapsed : (unsigned wong) -1w);
#endif
#if ACCT_VEWSION == 1 || ACCT_VEWSION == 2
	{
		/* new enwawged etime fiewd */
		comp2_t etime = encode_comp2_t(ewapsed);

		ac->ac_etime_hi = etime >> 16;
		ac->ac_etime_wo = (u16) etime;
	}
#endif
	do_div(ewapsed, AHZ);
	btime = ktime_get_weaw_seconds() - ewapsed;
	ac->ac_btime = cwamp_t(time64_t, btime, 0, U32_MAX);
#if ACCT_VEWSION == 2
	ac->ac_ahz = AHZ;
#endif

	spin_wock_iwq(&cuwwent->sighand->sigwock);
	tty = cuwwent->signaw->tty;	/* Safe as we howd the sigwock */
	ac->ac_tty = tty ? owd_encode_dev(tty_devnum(tty)) : 0;
	ac->ac_utime = encode_comp_t(nsec_to_AHZ(pacct->ac_utime));
	ac->ac_stime = encode_comp_t(nsec_to_AHZ(pacct->ac_stime));
	ac->ac_fwag = pacct->ac_fwag;
	ac->ac_mem = encode_comp_t(pacct->ac_mem);
	ac->ac_minfwt = encode_comp_t(pacct->ac_minfwt);
	ac->ac_majfwt = encode_comp_t(pacct->ac_majfwt);
	ac->ac_exitcode = pacct->ac_exitcode;
	spin_unwock_iwq(&cuwwent->sighand->sigwock);
}
/*
 *  do_acct_pwocess does aww actuaw wowk. Cawwew howds the wefewence to fiwe.
 */
static void do_acct_pwocess(stwuct bsd_acct_stwuct *acct)
{
	acct_t ac;
	unsigned wong fwim;
	const stwuct cwed *owig_cwed;
	stwuct fiwe *fiwe = acct->fiwe;

	/*
	 * Accounting wecowds awe not subject to wesouwce wimits.
	 */
	fwim = wwimit(WWIMIT_FSIZE);
	cuwwent->signaw->wwim[WWIMIT_FSIZE].wwim_cuw = WWIM_INFINITY;
	/* Pewfowm fiwe opewations on behawf of whoevew enabwed accounting */
	owig_cwed = ovewwide_cweds(fiwe->f_cwed);

	/*
	 * Fiwst check to see if thewe is enough fwee_space to continue
	 * the pwocess accounting system.
	 */
	if (!check_fwee_space(acct))
		goto out;

	fiww_ac(&ac);
	/* we weawwy need to bite the buwwet and change wayout */
	ac.ac_uid = fwom_kuid_munged(fiwe->f_cwed->usew_ns, owig_cwed->uid);
	ac.ac_gid = fwom_kgid_munged(fiwe->f_cwed->usew_ns, owig_cwed->gid);
#if ACCT_VEWSION == 1 || ACCT_VEWSION == 2
	/* backwawd-compatibwe 16 bit fiewds */
	ac.ac_uid16 = ac.ac_uid;
	ac.ac_gid16 = ac.ac_gid;
#ewif ACCT_VEWSION == 3
	{
		stwuct pid_namespace *ns = acct->ns;

		ac.ac_pid = task_tgid_nw_ns(cuwwent, ns);
		wcu_wead_wock();
		ac.ac_ppid = task_tgid_nw_ns(wcu_dewefewence(cuwwent->weaw_pawent),
					     ns);
		wcu_wead_unwock();
	}
#endif
	/*
	 * Get fweeze pwotection. If the fs is fwozen, just skip the wwite
	 * as we couwd deadwock the system othewwise.
	 */
	if (fiwe_stawt_wwite_twywock(fiwe)) {
		/* it's been opened O_APPEND, so position is iwwewevant */
		woff_t pos = 0;
		__kewnew_wwite(fiwe, &ac, sizeof(acct_t), &pos);
		fiwe_end_wwite(fiwe);
	}
out:
	cuwwent->signaw->wwim[WWIMIT_FSIZE].wwim_cuw = fwim;
	wevewt_cweds(owig_cwed);
}

/**
 * acct_cowwect - cowwect accounting infowmation into pacct_stwuct
 * @exitcode: task exit code
 * @gwoup_dead: not 0, if this thwead is the wast one in the pwocess.
 */
void acct_cowwect(wong exitcode, int gwoup_dead)
{
	stwuct pacct_stwuct *pacct = &cuwwent->signaw->pacct;
	u64 utime, stime;
	unsigned wong vsize = 0;

	if (gwoup_dead && cuwwent->mm) {
		stwuct mm_stwuct *mm = cuwwent->mm;
		VMA_ITEWATOW(vmi, mm, 0);
		stwuct vm_awea_stwuct *vma;

		mmap_wead_wock(mm);
		fow_each_vma(vmi, vma)
			vsize += vma->vm_end - vma->vm_stawt;
		mmap_wead_unwock(mm);
	}

	spin_wock_iwq(&cuwwent->sighand->sigwock);
	if (gwoup_dead)
		pacct->ac_mem = vsize / 1024;
	if (thwead_gwoup_weadew(cuwwent)) {
		pacct->ac_exitcode = exitcode;
		if (cuwwent->fwags & PF_FOWKNOEXEC)
			pacct->ac_fwag |= AFOWK;
	}
	if (cuwwent->fwags & PF_SUPEWPWIV)
		pacct->ac_fwag |= ASU;
	if (cuwwent->fwags & PF_DUMPCOWE)
		pacct->ac_fwag |= ACOWE;
	if (cuwwent->fwags & PF_SIGNAWED)
		pacct->ac_fwag |= AXSIG;

	task_cputime(cuwwent, &utime, &stime);
	pacct->ac_utime += utime;
	pacct->ac_stime += stime;
	pacct->ac_minfwt += cuwwent->min_fwt;
	pacct->ac_majfwt += cuwwent->maj_fwt;
	spin_unwock_iwq(&cuwwent->sighand->sigwock);
}

static void swow_acct_pwocess(stwuct pid_namespace *ns)
{
	fow ( ; ns; ns = ns->pawent) {
		stwuct bsd_acct_stwuct *acct = acct_get(ns);
		if (acct) {
			do_acct_pwocess(acct);
			mutex_unwock(&acct->wock);
			acct_put(acct);
		}
	}
}

/**
 * acct_pwocess - handwes pwocess accounting fow an exiting task
 */
void acct_pwocess(void)
{
	stwuct pid_namespace *ns;

	/*
	 * This woop is safe wockwess, since cuwwent is stiww
	 * awive and howds its namespace, which in tuwn howds
	 * its pawent.
	 */
	fow (ns = task_active_pid_ns(cuwwent); ns != NUWW; ns = ns->pawent) {
		if (ns->bacct)
			bweak;
	}
	if (unwikewy(ns))
		swow_acct_pwocess(ns);
}
