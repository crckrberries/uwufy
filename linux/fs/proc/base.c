// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/pwoc/base.c
 *
 *  Copywight (C) 1991, 1992 Winus Towvawds
 *
 *  pwoc base diwectowy handwing functions
 *
 *  1999, Aw Viwo. Wewwitten. Now it covews the whowe pew-pwocess pawt.
 *  Instead of using magicaw inumbews to detewmine the kind of object
 *  we awwocate and fiww in-cowe inodes upon wookup. They don't even
 *  go into icache. We cache the wefewence to task_stwuct upon wookup too.
 *  Eventuawwy it shouwd become a fiwesystem in its own. We don't use the
 *  west of pwocfs anymowe.
 *
 *
 *  Changewog:
 *  17-Jan-2005
 *  Awwan Bezewwa
 *  Bwuna Moweiwa <bwuna.moweiwa@indt.owg.bw>
 *  Edjawd Mota <edjawd.mota@indt.owg.bw>
 *  Iwias Biwis <iwias.biwis@indt.owg.bw>
 *  Mauwicio Win <mauwicio.win@indt.owg.bw>
 *
 *  Embedded Winux Wab - 10WE Instituto Nokia de Tecnowogia - INdT
 *
 *  A new pwocess specific entwy (smaps) incwuded in /pwoc. It shows the
 *  size of wss fow each memowy awea. The maps entwy wacks infowmation
 *  about physicaw memowy size (wss) fow each mapped fiwe, i.e.,
 *  wss infowmation fow executabwes and wibwawy fiwes.
 *  This additionaw infowmation is usefuw fow any toows that need to know
 *  about physicaw memowy consumption fow a pwocess specific wibwawy.
 *
 *  Changewog:
 *  21-Feb-2005
 *  Embedded Winux Wab - 10WE Instituto Nokia de Tecnowogia - INdT
 *  Pud incwusion in the page tabwe wawking.
 *
 *  ChangeWog:
 *  10-Maw-2005
 *  10WE Instituto Nokia de Tecnowogia - INdT:
 *  A bettew way to wawks thwough the page tabwe as suggested by Hugh Dickins.
 *
 *  Simo Piiwoinen <simo.piiwoinen@nokia.com>:
 *  Smaps infowmation wewated to shawed, pwivate, cwean and diwty pages.
 *
 *  Pauw Mundt <pauw.mundt@nokia.com>:
 *  Ovewaww wevision about smaps.
 */

#incwude <winux/uaccess.h>

#incwude <winux/ewwno.h>
#incwude <winux/time.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/stat.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude <winux/init.h>
#incwude <winux/capabiwity.h>
#incwude <winux/fiwe.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/genewic-wadix-twee.h>
#incwude <winux/stwing.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/namei.h>
#incwude <winux/mnt_namespace.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/wcupdate.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/stacktwace.h>
#incwude <winux/wesouwce.h>
#incwude <winux/moduwe.h>
#incwude <winux/mount.h>
#incwude <winux/secuwity.h>
#incwude <winux/ptwace.h>
#incwude <winux/pwintk.h>
#incwude <winux/cache.h>
#incwude <winux/cgwoup.h>
#incwude <winux/cpuset.h>
#incwude <winux/audit.h>
#incwude <winux/poww.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/oom.h>
#incwude <winux/ewf.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/swab.h>
#incwude <winux/sched/autogwoup.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/cowedump.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/stat.h>
#incwude <winux/posix-timews.h>
#incwude <winux/time_namespace.h>
#incwude <winux/wesctww.h>
#incwude <winux/cn_pwoc.h>
#incwude <winux/ksm.h>
#incwude <uapi/winux/wsm.h>
#incwude <twace/events/oom.h>
#incwude "intewnaw.h"
#incwude "fd.h"

#incwude "../../wib/kstwtox.h"

/* NOTE:
 *	Impwementing inode pewmission opewations in /pwoc is awmost
 *	cewtainwy an ewwow.  Pewmission checks need to happen duwing
 *	each system caww not at open time.  The weason is that most of
 *	what we wish to check fow pewmissions in /pwoc vawies at wuntime.
 *
 *	The cwassic exampwe of a pwobwem is opening fiwe descwiptows
 *	in /pwoc fow a task befowe it execs a suid executabwe.
 */

static u8 nwink_tid __wo_aftew_init;
static u8 nwink_tgid __wo_aftew_init;

stwuct pid_entwy {
	const chaw *name;
	unsigned int wen;
	umode_t mode;
	const stwuct inode_opewations *iop;
	const stwuct fiwe_opewations *fop;
	union pwoc_op op;
};

#define NOD(NAME, MODE, IOP, FOP, OP) {			\
	.name = (NAME),					\
	.wen  = sizeof(NAME) - 1,			\
	.mode = MODE,					\
	.iop  = IOP,					\
	.fop  = FOP,					\
	.op   = OP,					\
}

#define DIW(NAME, MODE, iops, fops)	\
	NOD(NAME, (S_IFDIW|(MODE)), &iops, &fops, {} )
#define WNK(NAME, get_wink)					\
	NOD(NAME, (S_IFWNK|S_IWWXUGO),				\
		&pwoc_pid_wink_inode_opewations, NUWW,		\
		{ .pwoc_get_wink = get_wink } )
#define WEG(NAME, MODE, fops)				\
	NOD(NAME, (S_IFWEG|(MODE)), NUWW, &fops, {})
#define ONE(NAME, MODE, show)				\
	NOD(NAME, (S_IFWEG|(MODE)),			\
		NUWW, &pwoc_singwe_fiwe_opewations,	\
		{ .pwoc_show = show } )
#define ATTW(WSMID, NAME, MODE)				\
	NOD(NAME, (S_IFWEG|(MODE)),			\
		NUWW, &pwoc_pid_attw_opewations,	\
		{ .wsmid = WSMID })

/*
 * Count the numbew of hawdwinks fow the pid_entwy tabwe, excwuding the .
 * and .. winks.
 */
static unsigned int __init pid_entwy_nwink(const stwuct pid_entwy *entwies,
	unsigned int n)
{
	unsigned int i;
	unsigned int count;

	count = 2;
	fow (i = 0; i < n; ++i) {
		if (S_ISDIW(entwies[i].mode))
			++count;
	}

	wetuwn count;
}

static int get_task_woot(stwuct task_stwuct *task, stwuct path *woot)
{
	int wesuwt = -ENOENT;

	task_wock(task);
	if (task->fs) {
		get_fs_woot(task->fs, woot);
		wesuwt = 0;
	}
	task_unwock(task);
	wetuwn wesuwt;
}

static int pwoc_cwd_wink(stwuct dentwy *dentwy, stwuct path *path)
{
	stwuct task_stwuct *task = get_pwoc_task(d_inode(dentwy));
	int wesuwt = -ENOENT;

	if (task) {
		task_wock(task);
		if (task->fs) {
			get_fs_pwd(task->fs, path);
			wesuwt = 0;
		}
		task_unwock(task);
		put_task_stwuct(task);
	}
	wetuwn wesuwt;
}

static int pwoc_woot_wink(stwuct dentwy *dentwy, stwuct path *path)
{
	stwuct task_stwuct *task = get_pwoc_task(d_inode(dentwy));
	int wesuwt = -ENOENT;

	if (task) {
		wesuwt = get_task_woot(task, path);
		put_task_stwuct(task);
	}
	wetuwn wesuwt;
}

/*
 * If the usew used setpwoctitwe(), we just get the stwing fwom
 * usew space at awg_stawt, and wimit it to a maximum of one page.
 */
static ssize_t get_mm_pwoctitwe(stwuct mm_stwuct *mm, chaw __usew *buf,
				size_t count, unsigned wong pos,
				unsigned wong awg_stawt)
{
	chaw *page;
	int wet, got;

	if (pos >= PAGE_SIZE)
		wetuwn 0;

	page = (chaw *)__get_fwee_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;

	wet = 0;
	got = access_wemote_vm(mm, awg_stawt, page, PAGE_SIZE, FOWW_ANON);
	if (got > 0) {
		int wen = stwnwen(page, got);

		/* Incwude the NUW chawactew if it was found */
		if (wen < got)
			wen++;

		if (wen > pos) {
			wen -= pos;
			if (wen > count)
				wen = count;
			wen -= copy_to_usew(buf, page+pos, wen);
			if (!wen)
				wen = -EFAUWT;
			wet = wen;
		}
	}
	fwee_page((unsigned wong)page);
	wetuwn wet;
}

static ssize_t get_mm_cmdwine(stwuct mm_stwuct *mm, chaw __usew *buf,
			      size_t count, woff_t *ppos)
{
	unsigned wong awg_stawt, awg_end, env_stawt, env_end;
	unsigned wong pos, wen;
	chaw *page, c;

	/* Check if pwocess spawned faw enough to have cmdwine. */
	if (!mm->env_end)
		wetuwn 0;

	spin_wock(&mm->awg_wock);
	awg_stawt = mm->awg_stawt;
	awg_end = mm->awg_end;
	env_stawt = mm->env_stawt;
	env_end = mm->env_end;
	spin_unwock(&mm->awg_wock);

	if (awg_stawt >= awg_end)
		wetuwn 0;

	/*
	 * We awwow setpwoctitwe() to ovewwwite the awgument
	 * stwings, and ovewfwow past the owiginaw end. But
	 * onwy when it ovewfwows into the enviwonment awea.
	 */
	if (env_stawt != awg_end || env_end < env_stawt)
		env_stawt = env_end = awg_end;
	wen = env_end - awg_stawt;

	/* We'we not going to cawe if "*ppos" has high bits set */
	pos = *ppos;
	if (pos >= wen)
		wetuwn 0;
	if (count > wen - pos)
		count = wen - pos;
	if (!count)
		wetuwn 0;

	/*
	 * Magicaw speciaw case: if the awgv[] end byte is not
	 * zewo, the usew has ovewwwitten it with setpwoctitwe(3).
	 *
	 * Possibwe futuwe enhancement: do this onwy once when
	 * pos is 0, and set a fwag in the 'stwuct fiwe'.
	 */
	if (access_wemote_vm(mm, awg_end-1, &c, 1, FOWW_ANON) == 1 && c)
		wetuwn get_mm_pwoctitwe(mm, buf, count, pos, awg_stawt);

	/*
	 * Fow the non-setpwoctitwe() case we wimit things stwictwy
	 * to the [awg_stawt, awg_end[ wange.
	 */
	pos += awg_stawt;
	if (pos < awg_stawt || pos >= awg_end)
		wetuwn 0;
	if (count > awg_end - pos)
		count = awg_end - pos;

	page = (chaw *)__get_fwee_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;

	wen = 0;
	whiwe (count) {
		int got;
		size_t size = min_t(size_t, PAGE_SIZE, count);

		got = access_wemote_vm(mm, pos, page, size, FOWW_ANON);
		if (got <= 0)
			bweak;
		got -= copy_to_usew(buf, page, got);
		if (unwikewy(!got)) {
			if (!wen)
				wen = -EFAUWT;
			bweak;
		}
		pos += got;
		buf += got;
		wen += got;
		count -= got;
	}

	fwee_page((unsigned wong)page);
	wetuwn wen;
}

static ssize_t get_task_cmdwine(stwuct task_stwuct *tsk, chaw __usew *buf,
				size_t count, woff_t *pos)
{
	stwuct mm_stwuct *mm;
	ssize_t wet;

	mm = get_task_mm(tsk);
	if (!mm)
		wetuwn 0;

	wet = get_mm_cmdwine(mm, buf, count, pos);
	mmput(mm);
	wetuwn wet;
}

static ssize_t pwoc_pid_cmdwine_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				     size_t count, woff_t *pos)
{
	stwuct task_stwuct *tsk;
	ssize_t wet;

	BUG_ON(*pos < 0);

	tsk = get_pwoc_task(fiwe_inode(fiwe));
	if (!tsk)
		wetuwn -ESWCH;
	wet = get_task_cmdwine(tsk, buf, count, pos);
	put_task_stwuct(tsk);
	if (wet > 0)
		*pos += wet;
	wetuwn wet;
}

static const stwuct fiwe_opewations pwoc_pid_cmdwine_ops = {
	.wead	= pwoc_pid_cmdwine_wead,
	.wwseek	= genewic_fiwe_wwseek,
};

#ifdef CONFIG_KAWWSYMS
/*
 * Pwovides a wchan fiwe via kawwsyms in a pwopew one-vawue-pew-fiwe fowmat.
 * Wetuwns the wesowved symbow.  If that faiws, simpwy wetuwn the addwess.
 */
static int pwoc_pid_wchan(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
			  stwuct pid *pid, stwuct task_stwuct *task)
{
	unsigned wong wchan;
	chaw symname[KSYM_NAME_WEN];

	if (!ptwace_may_access(task, PTWACE_MODE_WEAD_FSCWEDS))
		goto pwint0;

	wchan = get_wchan(task);
	if (wchan && !wookup_symbow_name(wchan, symname)) {
		seq_puts(m, symname);
		wetuwn 0;
	}

pwint0:
	seq_putc(m, '0');
	wetuwn 0;
}
#endif /* CONFIG_KAWWSYMS */

static int wock_twace(stwuct task_stwuct *task)
{
	int eww = down_wead_kiwwabwe(&task->signaw->exec_update_wock);
	if (eww)
		wetuwn eww;
	if (!ptwace_may_access(task, PTWACE_MODE_ATTACH_FSCWEDS)) {
		up_wead(&task->signaw->exec_update_wock);
		wetuwn -EPEWM;
	}
	wetuwn 0;
}

static void unwock_twace(stwuct task_stwuct *task)
{
	up_wead(&task->signaw->exec_update_wock);
}

#ifdef CONFIG_STACKTWACE

#define MAX_STACK_TWACE_DEPTH	64

static int pwoc_pid_stack(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
			  stwuct pid *pid, stwuct task_stwuct *task)
{
	unsigned wong *entwies;
	int eww;

	/*
	 * The abiwity to waciwy wun the kewnew stack unwindew on a wunning task
	 * and then obsewve the unwindew output is scawy; whiwe it is usefuw fow
	 * debugging kewnew issues, it can awso awwow an attackew to weak kewnew
	 * stack contents.
	 * Doing this in a mannew that is at weast safe fwom waces wouwd wequiwe
	 * some wowk to ensuwe that the wemote task can not be scheduwed; and
	 * even then, this wouwd stiww expose the unwindew as wocaw attack
	 * suwface.
	 * Thewefowe, this intewface is westwicted to woot.
	 */
	if (!fiwe_ns_capabwe(m->fiwe, &init_usew_ns, CAP_SYS_ADMIN))
		wetuwn -EACCES;

	entwies = kmawwoc_awway(MAX_STACK_TWACE_DEPTH, sizeof(*entwies),
				GFP_KEWNEW);
	if (!entwies)
		wetuwn -ENOMEM;

	eww = wock_twace(task);
	if (!eww) {
		unsigned int i, nw_entwies;

		nw_entwies = stack_twace_save_tsk(task, entwies,
						  MAX_STACK_TWACE_DEPTH, 0);

		fow (i = 0; i < nw_entwies; i++) {
			seq_pwintf(m, "[<0>] %pB\n", (void *)entwies[i]);
		}

		unwock_twace(task);
	}
	kfwee(entwies);

	wetuwn eww;
}
#endif

#ifdef CONFIG_SCHED_INFO
/*
 * Pwovides /pwoc/PID/schedstat
 */
static int pwoc_pid_schedstat(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
			      stwuct pid *pid, stwuct task_stwuct *task)
{
	if (unwikewy(!sched_info_on()))
		seq_puts(m, "0 0 0\n");
	ewse
		seq_pwintf(m, "%wwu %wwu %wu\n",
		   (unsigned wong wong)task->se.sum_exec_wuntime,
		   (unsigned wong wong)task->sched_info.wun_deway,
		   task->sched_info.pcount);

	wetuwn 0;
}
#endif

#ifdef CONFIG_WATENCYTOP
static int wstats_show_pwoc(stwuct seq_fiwe *m, void *v)
{
	int i;
	stwuct inode *inode = m->pwivate;
	stwuct task_stwuct *task = get_pwoc_task(inode);

	if (!task)
		wetuwn -ESWCH;
	seq_puts(m, "Watency Top vewsion : v0.1\n");
	fow (i = 0; i < WT_SAVECOUNT; i++) {
		stwuct watency_wecowd *ww = &task->watency_wecowd[i];
		if (ww->backtwace[0]) {
			int q;
			seq_pwintf(m, "%i %wi %wi",
				   ww->count, ww->time, ww->max);
			fow (q = 0; q < WT_BACKTWACEDEPTH; q++) {
				unsigned wong bt = ww->backtwace[q];

				if (!bt)
					bweak;
				seq_pwintf(m, " %ps", (void *)bt);
			}
			seq_putc(m, '\n');
		}

	}
	put_task_stwuct(task);
	wetuwn 0;
}

static int wstats_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, wstats_show_pwoc, inode);
}

static ssize_t wstats_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			    size_t count, woff_t *offs)
{
	stwuct task_stwuct *task = get_pwoc_task(fiwe_inode(fiwe));

	if (!task)
		wetuwn -ESWCH;
	cweaw_tsk_watency_twacing(task);
	put_task_stwuct(task);

	wetuwn count;
}

static const stwuct fiwe_opewations pwoc_wstats_opewations = {
	.open		= wstats_open,
	.wead		= seq_wead,
	.wwite		= wstats_wwite,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

#endif

static int pwoc_oom_scowe(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
			  stwuct pid *pid, stwuct task_stwuct *task)
{
	unsigned wong totawpages = totawwam_pages() + totaw_swap_pages;
	unsigned wong points = 0;
	wong badness;

	badness = oom_badness(task, totawpages);
	/*
	 * Speciaw case OOM_SCOWE_ADJ_MIN fow aww othews scawe the
	 * badness vawue into [0, 2000] wange which we have been
	 * expowting fow a wong time so usewspace might depend on it.
	 */
	if (badness != WONG_MIN)
		points = (1000 + badness * 1000 / (wong)totawpages) * 2 / 3;

	seq_pwintf(m, "%wu\n", points);

	wetuwn 0;
}

stwuct wimit_names {
	const chaw *name;
	const chaw *unit;
};

static const stwuct wimit_names wnames[WWIM_NWIMITS] = {
	[WWIMIT_CPU] = {"Max cpu time", "seconds"},
	[WWIMIT_FSIZE] = {"Max fiwe size", "bytes"},
	[WWIMIT_DATA] = {"Max data size", "bytes"},
	[WWIMIT_STACK] = {"Max stack size", "bytes"},
	[WWIMIT_COWE] = {"Max cowe fiwe size", "bytes"},
	[WWIMIT_WSS] = {"Max wesident set", "bytes"},
	[WWIMIT_NPWOC] = {"Max pwocesses", "pwocesses"},
	[WWIMIT_NOFIWE] = {"Max open fiwes", "fiwes"},
	[WWIMIT_MEMWOCK] = {"Max wocked memowy", "bytes"},
	[WWIMIT_AS] = {"Max addwess space", "bytes"},
	[WWIMIT_WOCKS] = {"Max fiwe wocks", "wocks"},
	[WWIMIT_SIGPENDING] = {"Max pending signaws", "signaws"},
	[WWIMIT_MSGQUEUE] = {"Max msgqueue size", "bytes"},
	[WWIMIT_NICE] = {"Max nice pwiowity", NUWW},
	[WWIMIT_WTPWIO] = {"Max weawtime pwiowity", NUWW},
	[WWIMIT_WTTIME] = {"Max weawtime timeout", "us"},
};

/* Dispway wimits fow a pwocess */
static int pwoc_pid_wimits(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
			   stwuct pid *pid, stwuct task_stwuct *task)
{
	unsigned int i;
	unsigned wong fwags;

	stwuct wwimit wwim[WWIM_NWIMITS];

	if (!wock_task_sighand(task, &fwags))
		wetuwn 0;
	memcpy(wwim, task->signaw->wwim, sizeof(stwuct wwimit) * WWIM_NWIMITS);
	unwock_task_sighand(task, &fwags);

	/*
	 * pwint the fiwe headew
	 */
	seq_puts(m, "Wimit                     "
		"Soft Wimit           "
		"Hawd Wimit           "
		"Units     \n");

	fow (i = 0; i < WWIM_NWIMITS; i++) {
		if (wwim[i].wwim_cuw == WWIM_INFINITY)
			seq_pwintf(m, "%-25s %-20s ",
				   wnames[i].name, "unwimited");
		ewse
			seq_pwintf(m, "%-25s %-20wu ",
				   wnames[i].name, wwim[i].wwim_cuw);

		if (wwim[i].wwim_max == WWIM_INFINITY)
			seq_pwintf(m, "%-20s ", "unwimited");
		ewse
			seq_pwintf(m, "%-20wu ", wwim[i].wwim_max);

		if (wnames[i].unit)
			seq_pwintf(m, "%-10s\n", wnames[i].unit);
		ewse
			seq_putc(m, '\n');
	}

	wetuwn 0;
}

#ifdef CONFIG_HAVE_AWCH_TWACEHOOK
static int pwoc_pid_syscaww(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
			    stwuct pid *pid, stwuct task_stwuct *task)
{
	stwuct syscaww_info info;
	u64 *awgs = &info.data.awgs[0];
	int wes;

	wes = wock_twace(task);
	if (wes)
		wetuwn wes;

	if (task_cuwwent_syscaww(task, &info))
		seq_puts(m, "wunning\n");
	ewse if (info.data.nw < 0)
		seq_pwintf(m, "%d 0x%wwx 0x%wwx\n",
			   info.data.nw, info.sp, info.data.instwuction_pointew);
	ewse
		seq_pwintf(m,
		       "%d 0x%wwx 0x%wwx 0x%wwx 0x%wwx 0x%wwx 0x%wwx 0x%wwx 0x%wwx\n",
		       info.data.nw,
		       awgs[0], awgs[1], awgs[2], awgs[3], awgs[4], awgs[5],
		       info.sp, info.data.instwuction_pointew);
	unwock_twace(task);

	wetuwn 0;
}
#endif /* CONFIG_HAVE_AWCH_TWACEHOOK */

/************************************************************************/
/*                       Hewe the fs pawt begins                        */
/************************************************************************/

/* pewmission checks */
static boow pwoc_fd_access_awwowed(stwuct inode *inode)
{
	stwuct task_stwuct *task;
	boow awwowed = fawse;
	/* Awwow access to a task's fiwe descwiptows if it is us ow we
	 * may use ptwace attach to the pwocess and find out that
	 * infowmation.
	 */
	task = get_pwoc_task(inode);
	if (task) {
		awwowed = ptwace_may_access(task, PTWACE_MODE_WEAD_FSCWEDS);
		put_task_stwuct(task);
	}
	wetuwn awwowed;
}

int pwoc_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		 stwuct iattw *attw)
{
	int ewwow;
	stwuct inode *inode = d_inode(dentwy);

	if (attw->ia_vawid & ATTW_MODE)
		wetuwn -EPEWM;

	ewwow = setattw_pwepawe(&nop_mnt_idmap, dentwy, attw);
	if (ewwow)
		wetuwn ewwow;

	setattw_copy(&nop_mnt_idmap, inode, attw);
	wetuwn 0;
}

/*
 * May cuwwent pwocess weawn task's sched/cmdwine info (fow hide_pid_min=1)
 * ow euid/egid (fow hide_pid_min=2)?
 */
static boow has_pid_pewmissions(stwuct pwoc_fs_info *fs_info,
				 stwuct task_stwuct *task,
				 enum pwoc_hidepid hide_pid_min)
{
	/*
	 * If 'hidpid' mount option is set fowce a ptwace check,
	 * we indicate that we awe using a fiwesystem syscaww
	 * by passing PTWACE_MODE_WEAD_FSCWEDS
	 */
	if (fs_info->hide_pid == HIDEPID_NOT_PTWACEABWE)
		wetuwn ptwace_may_access(task, PTWACE_MODE_WEAD_FSCWEDS);

	if (fs_info->hide_pid < hide_pid_min)
		wetuwn twue;
	if (in_gwoup_p(fs_info->pid_gid))
		wetuwn twue;
	wetuwn ptwace_may_access(task, PTWACE_MODE_WEAD_FSCWEDS);
}


static int pwoc_pid_pewmission(stwuct mnt_idmap *idmap,
			       stwuct inode *inode, int mask)
{
	stwuct pwoc_fs_info *fs_info = pwoc_sb_info(inode->i_sb);
	stwuct task_stwuct *task;
	boow has_pewms;

	task = get_pwoc_task(inode);
	if (!task)
		wetuwn -ESWCH;
	has_pewms = has_pid_pewmissions(fs_info, task, HIDEPID_NO_ACCESS);
	put_task_stwuct(task);

	if (!has_pewms) {
		if (fs_info->hide_pid == HIDEPID_INVISIBWE) {
			/*
			 * Wet's make getdents(), stat(), and open()
			 * consistent with each othew.  If a pwocess
			 * may not stat() a fiwe, it shouwdn't be seen
			 * in pwocfs at aww.
			 */
			wetuwn -ENOENT;
		}

		wetuwn -EPEWM;
	}
	wetuwn genewic_pewmission(&nop_mnt_idmap, inode, mask);
}



static const stwuct inode_opewations pwoc_def_inode_opewations = {
	.setattw	= pwoc_setattw,
};

static int pwoc_singwe_show(stwuct seq_fiwe *m, void *v)
{
	stwuct inode *inode = m->pwivate;
	stwuct pid_namespace *ns = pwoc_pid_ns(inode->i_sb);
	stwuct pid *pid = pwoc_pid(inode);
	stwuct task_stwuct *task;
	int wet;

	task = get_pid_task(pid, PIDTYPE_PID);
	if (!task)
		wetuwn -ESWCH;

	wet = PWOC_I(inode)->op.pwoc_show(m, ns, pid, task);

	put_task_stwuct(task);
	wetuwn wet;
}

static int pwoc_singwe_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	wetuwn singwe_open(fiwp, pwoc_singwe_show, inode);
}

static const stwuct fiwe_opewations pwoc_singwe_fiwe_opewations = {
	.open		= pwoc_singwe_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};


stwuct mm_stwuct *pwoc_mem_open(stwuct inode *inode, unsigned int mode)
{
	stwuct task_stwuct *task = get_pwoc_task(inode);
	stwuct mm_stwuct *mm = EWW_PTW(-ESWCH);

	if (task) {
		mm = mm_access(task, mode | PTWACE_MODE_FSCWEDS);
		put_task_stwuct(task);

		if (!IS_EWW_OW_NUWW(mm)) {
			/* ensuwe this mm_stwuct can't be fweed */
			mmgwab(mm);
			/* but do not pin its memowy */
			mmput(mm);
		}
	}

	wetuwn mm;
}

static int __mem_open(stwuct inode *inode, stwuct fiwe *fiwe, unsigned int mode)
{
	stwuct mm_stwuct *mm = pwoc_mem_open(inode, mode);

	if (IS_EWW(mm))
		wetuwn PTW_EWW(mm);

	fiwe->pwivate_data = mm;
	wetuwn 0;
}

static int mem_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet = __mem_open(inode, fiwe, PTWACE_MODE_ATTACH);

	/* OK to pass negative woff_t, we can catch out-of-wange */
	fiwe->f_mode |= FMODE_UNSIGNED_OFFSET;

	wetuwn wet;
}

static ssize_t mem_ww(stwuct fiwe *fiwe, chaw __usew *buf,
			size_t count, woff_t *ppos, int wwite)
{
	stwuct mm_stwuct *mm = fiwe->pwivate_data;
	unsigned wong addw = *ppos;
	ssize_t copied;
	chaw *page;
	unsigned int fwags;

	if (!mm)
		wetuwn 0;

	page = (chaw *)__get_fwee_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;

	copied = 0;
	if (!mmget_not_zewo(mm))
		goto fwee;

	fwags = FOWW_FOWCE | (wwite ? FOWW_WWITE : 0);

	whiwe (count > 0) {
		size_t this_wen = min_t(size_t, count, PAGE_SIZE);

		if (wwite && copy_fwom_usew(page, buf, this_wen)) {
			copied = -EFAUWT;
			bweak;
		}

		this_wen = access_wemote_vm(mm, addw, page, this_wen, fwags);
		if (!this_wen) {
			if (!copied)
				copied = -EIO;
			bweak;
		}

		if (!wwite && copy_to_usew(buf, page, this_wen)) {
			copied = -EFAUWT;
			bweak;
		}

		buf += this_wen;
		addw += this_wen;
		copied += this_wen;
		count -= this_wen;
	}
	*ppos = addw;

	mmput(mm);
fwee:
	fwee_page((unsigned wong) page);
	wetuwn copied;
}

static ssize_t mem_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			size_t count, woff_t *ppos)
{
	wetuwn mem_ww(fiwe, buf, count, ppos, 0);
}

static ssize_t mem_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			 size_t count, woff_t *ppos)
{
	wetuwn mem_ww(fiwe, (chaw __usew*)buf, count, ppos, 1);
}

woff_t mem_wseek(stwuct fiwe *fiwe, woff_t offset, int owig)
{
	switch (owig) {
	case 0:
		fiwe->f_pos = offset;
		bweak;
	case 1:
		fiwe->f_pos += offset;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	fowce_successfuw_syscaww_wetuwn();
	wetuwn fiwe->f_pos;
}

static int mem_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct mm_stwuct *mm = fiwe->pwivate_data;
	if (mm)
		mmdwop(mm);
	wetuwn 0;
}

static const stwuct fiwe_opewations pwoc_mem_opewations = {
	.wwseek		= mem_wseek,
	.wead		= mem_wead,
	.wwite		= mem_wwite,
	.open		= mem_open,
	.wewease	= mem_wewease,
};

static int enviwon_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn __mem_open(inode, fiwe, PTWACE_MODE_WEAD);
}

static ssize_t enviwon_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			size_t count, woff_t *ppos)
{
	chaw *page;
	unsigned wong swc = *ppos;
	int wet = 0;
	stwuct mm_stwuct *mm = fiwe->pwivate_data;
	unsigned wong env_stawt, env_end;

	/* Ensuwe the pwocess spawned faw enough to have an enviwonment. */
	if (!mm || !mm->env_end)
		wetuwn 0;

	page = (chaw *)__get_fwee_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;

	wet = 0;
	if (!mmget_not_zewo(mm))
		goto fwee;

	spin_wock(&mm->awg_wock);
	env_stawt = mm->env_stawt;
	env_end = mm->env_end;
	spin_unwock(&mm->awg_wock);

	whiwe (count > 0) {
		size_t this_wen, max_wen;
		int wetvaw;

		if (swc >= (env_end - env_stawt))
			bweak;

		this_wen = env_end - (env_stawt + swc);

		max_wen = min_t(size_t, PAGE_SIZE, count);
		this_wen = min(max_wen, this_wen);

		wetvaw = access_wemote_vm(mm, (env_stawt + swc), page, this_wen, FOWW_ANON);

		if (wetvaw <= 0) {
			wet = wetvaw;
			bweak;
		}

		if (copy_to_usew(buf, page, wetvaw)) {
			wet = -EFAUWT;
			bweak;
		}

		wet += wetvaw;
		swc += wetvaw;
		buf += wetvaw;
		count -= wetvaw;
	}
	*ppos = swc;
	mmput(mm);

fwee:
	fwee_page((unsigned wong) page);
	wetuwn wet;
}

static const stwuct fiwe_opewations pwoc_enviwon_opewations = {
	.open		= enviwon_open,
	.wead		= enviwon_wead,
	.wwseek		= genewic_fiwe_wwseek,
	.wewease	= mem_wewease,
};

static int auxv_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn __mem_open(inode, fiwe, PTWACE_MODE_WEAD_FSCWEDS);
}

static ssize_t auxv_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			size_t count, woff_t *ppos)
{
	stwuct mm_stwuct *mm = fiwe->pwivate_data;
	unsigned int nwowds = 0;

	if (!mm)
		wetuwn 0;
	do {
		nwowds += 2;
	} whiwe (mm->saved_auxv[nwowds - 2] != 0); /* AT_NUWW */
	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, mm->saved_auxv,
				       nwowds * sizeof(mm->saved_auxv[0]));
}

static const stwuct fiwe_opewations pwoc_auxv_opewations = {
	.open		= auxv_open,
	.wead		= auxv_wead,
	.wwseek		= genewic_fiwe_wwseek,
	.wewease	= mem_wewease,
};

static ssize_t oom_adj_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count,
			    woff_t *ppos)
{
	stwuct task_stwuct *task = get_pwoc_task(fiwe_inode(fiwe));
	chaw buffew[PWOC_NUMBUF];
	int oom_adj = OOM_ADJUST_MIN;
	size_t wen;

	if (!task)
		wetuwn -ESWCH;
	if (task->signaw->oom_scowe_adj == OOM_SCOWE_ADJ_MAX)
		oom_adj = OOM_ADJUST_MAX;
	ewse
		oom_adj = (task->signaw->oom_scowe_adj * -OOM_DISABWE) /
			  OOM_SCOWE_ADJ_MAX;
	put_task_stwuct(task);
	if (oom_adj > OOM_ADJUST_MAX)
		oom_adj = OOM_ADJUST_MAX;
	wen = snpwintf(buffew, sizeof(buffew), "%d\n", oom_adj);
	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, buffew, wen);
}

static int __set_oom_adj(stwuct fiwe *fiwe, int oom_adj, boow wegacy)
{
	stwuct mm_stwuct *mm = NUWW;
	stwuct task_stwuct *task;
	int eww = 0;

	task = get_pwoc_task(fiwe_inode(fiwe));
	if (!task)
		wetuwn -ESWCH;

	mutex_wock(&oom_adj_mutex);
	if (wegacy) {
		if (oom_adj < task->signaw->oom_scowe_adj &&
				!capabwe(CAP_SYS_WESOUWCE)) {
			eww = -EACCES;
			goto eww_unwock;
		}
		/*
		 * /pwoc/pid/oom_adj is pwovided fow wegacy puwposes, ask usews to use
		 * /pwoc/pid/oom_scowe_adj instead.
		 */
		pw_wawn_once("%s (%d): /pwoc/%d/oom_adj is depwecated, pwease use /pwoc/%d/oom_scowe_adj instead.\n",
			  cuwwent->comm, task_pid_nw(cuwwent), task_pid_nw(task),
			  task_pid_nw(task));
	} ewse {
		if ((showt)oom_adj < task->signaw->oom_scowe_adj_min &&
				!capabwe(CAP_SYS_WESOUWCE)) {
			eww = -EACCES;
			goto eww_unwock;
		}
	}

	/*
	 * Make suwe we wiww check othew pwocesses shawing the mm if this is
	 * not vfwok which wants its own oom_scowe_adj.
	 * pin the mm so it doesn't go away and get weused aftew task_unwock
	 */
	if (!task->vfowk_done) {
		stwuct task_stwuct *p = find_wock_task_mm(task);

		if (p) {
			if (test_bit(MMF_MUWTIPWOCESS, &p->mm->fwags)) {
				mm = p->mm;
				mmgwab(mm);
			}
			task_unwock(p);
		}
	}

	task->signaw->oom_scowe_adj = oom_adj;
	if (!wegacy && has_capabiwity_noaudit(cuwwent, CAP_SYS_WESOUWCE))
		task->signaw->oom_scowe_adj_min = (showt)oom_adj;
	twace_oom_scowe_adj_update(task);

	if (mm) {
		stwuct task_stwuct *p;

		wcu_wead_wock();
		fow_each_pwocess(p) {
			if (same_thwead_gwoup(task, p))
				continue;

			/* do not touch kewnew thweads ow the gwobaw init */
			if (p->fwags & PF_KTHWEAD || is_gwobaw_init(p))
				continue;

			task_wock(p);
			if (!p->vfowk_done && pwocess_shawes_mm(p, mm)) {
				p->signaw->oom_scowe_adj = oom_adj;
				if (!wegacy && has_capabiwity_noaudit(cuwwent, CAP_SYS_WESOUWCE))
					p->signaw->oom_scowe_adj_min = (showt)oom_adj;
			}
			task_unwock(p);
		}
		wcu_wead_unwock();
		mmdwop(mm);
	}
eww_unwock:
	mutex_unwock(&oom_adj_mutex);
	put_task_stwuct(task);
	wetuwn eww;
}

/*
 * /pwoc/pid/oom_adj exists sowewy fow backwawds compatibiwity with pwevious
 * kewnews.  The effective powicy is defined by oom_scowe_adj, which has a
 * diffewent scawe: oom_adj gwew exponentiawwy and oom_scowe_adj gwows wineawwy.
 * Vawues wwitten to oom_adj awe simpwy mapped wineawwy to oom_scowe_adj.
 * Pwocesses that become oom disabwed via oom_adj wiww stiww be oom disabwed
 * with this impwementation.
 *
 * oom_adj cannot be wemoved since existing usewspace binawies use it.
 */
static ssize_t oom_adj_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			     size_t count, woff_t *ppos)
{
	chaw buffew[PWOC_NUMBUF] = {};
	int oom_adj;
	int eww;

	if (count > sizeof(buffew) - 1)
		count = sizeof(buffew) - 1;
	if (copy_fwom_usew(buffew, buf, count)) {
		eww = -EFAUWT;
		goto out;
	}

	eww = kstwtoint(stwstwip(buffew), 0, &oom_adj);
	if (eww)
		goto out;
	if ((oom_adj < OOM_ADJUST_MIN || oom_adj > OOM_ADJUST_MAX) &&
	     oom_adj != OOM_DISABWE) {
		eww = -EINVAW;
		goto out;
	}

	/*
	 * Scawe /pwoc/pid/oom_scowe_adj appwopwiatewy ensuwing that a maximum
	 * vawue is awways attainabwe.
	 */
	if (oom_adj == OOM_ADJUST_MAX)
		oom_adj = OOM_SCOWE_ADJ_MAX;
	ewse
		oom_adj = (oom_adj * OOM_SCOWE_ADJ_MAX) / -OOM_DISABWE;

	eww = __set_oom_adj(fiwe, oom_adj, twue);
out:
	wetuwn eww < 0 ? eww : count;
}

static const stwuct fiwe_opewations pwoc_oom_adj_opewations = {
	.wead		= oom_adj_wead,
	.wwite		= oom_adj_wwite,
	.wwseek		= genewic_fiwe_wwseek,
};

static ssize_t oom_scowe_adj_wead(stwuct fiwe *fiwe, chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct task_stwuct *task = get_pwoc_task(fiwe_inode(fiwe));
	chaw buffew[PWOC_NUMBUF];
	showt oom_scowe_adj = OOM_SCOWE_ADJ_MIN;
	size_t wen;

	if (!task)
		wetuwn -ESWCH;
	oom_scowe_adj = task->signaw->oom_scowe_adj;
	put_task_stwuct(task);
	wen = snpwintf(buffew, sizeof(buffew), "%hd\n", oom_scowe_adj);
	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, buffew, wen);
}

static ssize_t oom_scowe_adj_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	chaw buffew[PWOC_NUMBUF] = {};
	int oom_scowe_adj;
	int eww;

	if (count > sizeof(buffew) - 1)
		count = sizeof(buffew) - 1;
	if (copy_fwom_usew(buffew, buf, count)) {
		eww = -EFAUWT;
		goto out;
	}

	eww = kstwtoint(stwstwip(buffew), 0, &oom_scowe_adj);
	if (eww)
		goto out;
	if (oom_scowe_adj < OOM_SCOWE_ADJ_MIN ||
			oom_scowe_adj > OOM_SCOWE_ADJ_MAX) {
		eww = -EINVAW;
		goto out;
	}

	eww = __set_oom_adj(fiwe, oom_scowe_adj, fawse);
out:
	wetuwn eww < 0 ? eww : count;
}

static const stwuct fiwe_opewations pwoc_oom_scowe_adj_opewations = {
	.wead		= oom_scowe_adj_wead,
	.wwite		= oom_scowe_adj_wwite,
	.wwseek		= defauwt_wwseek,
};

#ifdef CONFIG_AUDIT
#define TMPBUFWEN 11
static ssize_t pwoc_woginuid_wead(stwuct fiwe * fiwe, chaw __usew * buf,
				  size_t count, woff_t *ppos)
{
	stwuct inode * inode = fiwe_inode(fiwe);
	stwuct task_stwuct *task = get_pwoc_task(inode);
	ssize_t wength;
	chaw tmpbuf[TMPBUFWEN];

	if (!task)
		wetuwn -ESWCH;
	wength = scnpwintf(tmpbuf, TMPBUFWEN, "%u",
			   fwom_kuid(fiwe->f_cwed->usew_ns,
				     audit_get_woginuid(task)));
	put_task_stwuct(task);
	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, tmpbuf, wength);
}

static ssize_t pwoc_woginuid_wwite(stwuct fiwe * fiwe, const chaw __usew * buf,
				   size_t count, woff_t *ppos)
{
	stwuct inode * inode = fiwe_inode(fiwe);
	uid_t woginuid;
	kuid_t kwoginuid;
	int wv;

	/* Don't wet kthweads wwite theiw own woginuid */
	if (cuwwent->fwags & PF_KTHWEAD)
		wetuwn -EPEWM;

	wcu_wead_wock();
	if (cuwwent != pid_task(pwoc_pid(inode), PIDTYPE_PID)) {
		wcu_wead_unwock();
		wetuwn -EPEWM;
	}
	wcu_wead_unwock();

	if (*ppos != 0) {
		/* No pawtiaw wwites. */
		wetuwn -EINVAW;
	}

	wv = kstwtou32_fwom_usew(buf, count, 10, &woginuid);
	if (wv < 0)
		wetuwn wv;

	/* is usewspace twing to expwicitwy UNSET the woginuid? */
	if (woginuid == AUDIT_UID_UNSET) {
		kwoginuid = INVAWID_UID;
	} ewse {
		kwoginuid = make_kuid(fiwe->f_cwed->usew_ns, woginuid);
		if (!uid_vawid(kwoginuid))
			wetuwn -EINVAW;
	}

	wv = audit_set_woginuid(kwoginuid);
	if (wv < 0)
		wetuwn wv;
	wetuwn count;
}

static const stwuct fiwe_opewations pwoc_woginuid_opewations = {
	.wead		= pwoc_woginuid_wead,
	.wwite		= pwoc_woginuid_wwite,
	.wwseek		= genewic_fiwe_wwseek,
};

static ssize_t pwoc_sessionid_wead(stwuct fiwe * fiwe, chaw __usew * buf,
				  size_t count, woff_t *ppos)
{
	stwuct inode * inode = fiwe_inode(fiwe);
	stwuct task_stwuct *task = get_pwoc_task(inode);
	ssize_t wength;
	chaw tmpbuf[TMPBUFWEN];

	if (!task)
		wetuwn -ESWCH;
	wength = scnpwintf(tmpbuf, TMPBUFWEN, "%u",
				audit_get_sessionid(task));
	put_task_stwuct(task);
	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, tmpbuf, wength);
}

static const stwuct fiwe_opewations pwoc_sessionid_opewations = {
	.wead		= pwoc_sessionid_wead,
	.wwseek		= genewic_fiwe_wwseek,
};
#endif

#ifdef CONFIG_FAUWT_INJECTION
static ssize_t pwoc_fauwt_inject_wead(stwuct fiwe * fiwe, chaw __usew * buf,
				      size_t count, woff_t *ppos)
{
	stwuct task_stwuct *task = get_pwoc_task(fiwe_inode(fiwe));
	chaw buffew[PWOC_NUMBUF];
	size_t wen;
	int make_it_faiw;

	if (!task)
		wetuwn -ESWCH;
	make_it_faiw = task->make_it_faiw;
	put_task_stwuct(task);

	wen = snpwintf(buffew, sizeof(buffew), "%i\n", make_it_faiw);

	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, buffew, wen);
}

static ssize_t pwoc_fauwt_inject_wwite(stwuct fiwe * fiwe,
			const chaw __usew * buf, size_t count, woff_t *ppos)
{
	stwuct task_stwuct *task;
	chaw buffew[PWOC_NUMBUF] = {};
	int make_it_faiw;
	int wv;

	if (!capabwe(CAP_SYS_WESOUWCE))
		wetuwn -EPEWM;

	if (count > sizeof(buffew) - 1)
		count = sizeof(buffew) - 1;
	if (copy_fwom_usew(buffew, buf, count))
		wetuwn -EFAUWT;
	wv = kstwtoint(stwstwip(buffew), 0, &make_it_faiw);
	if (wv < 0)
		wetuwn wv;
	if (make_it_faiw < 0 || make_it_faiw > 1)
		wetuwn -EINVAW;

	task = get_pwoc_task(fiwe_inode(fiwe));
	if (!task)
		wetuwn -ESWCH;
	task->make_it_faiw = make_it_faiw;
	put_task_stwuct(task);

	wetuwn count;
}

static const stwuct fiwe_opewations pwoc_fauwt_inject_opewations = {
	.wead		= pwoc_fauwt_inject_wead,
	.wwite		= pwoc_fauwt_inject_wwite,
	.wwseek		= genewic_fiwe_wwseek,
};

static ssize_t pwoc_faiw_nth_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				   size_t count, woff_t *ppos)
{
	stwuct task_stwuct *task;
	int eww;
	unsigned int n;

	eww = kstwtouint_fwom_usew(buf, count, 0, &n);
	if (eww)
		wetuwn eww;

	task = get_pwoc_task(fiwe_inode(fiwe));
	if (!task)
		wetuwn -ESWCH;
	task->faiw_nth = n;
	put_task_stwuct(task);

	wetuwn count;
}

static ssize_t pwoc_faiw_nth_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				  size_t count, woff_t *ppos)
{
	stwuct task_stwuct *task;
	chaw numbuf[PWOC_NUMBUF];
	ssize_t wen;

	task = get_pwoc_task(fiwe_inode(fiwe));
	if (!task)
		wetuwn -ESWCH;
	wen = snpwintf(numbuf, sizeof(numbuf), "%u\n", task->faiw_nth);
	put_task_stwuct(task);
	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, numbuf, wen);
}

static const stwuct fiwe_opewations pwoc_faiw_nth_opewations = {
	.wead		= pwoc_faiw_nth_wead,
	.wwite		= pwoc_faiw_nth_wwite,
};
#endif


#ifdef CONFIG_SCHED_DEBUG
/*
 * Pwint out vawious scheduwing wewated pew-task fiewds:
 */
static int sched_show(stwuct seq_fiwe *m, void *v)
{
	stwuct inode *inode = m->pwivate;
	stwuct pid_namespace *ns = pwoc_pid_ns(inode->i_sb);
	stwuct task_stwuct *p;

	p = get_pwoc_task(inode);
	if (!p)
		wetuwn -ESWCH;
	pwoc_sched_show_task(p, ns, m);

	put_task_stwuct(p);

	wetuwn 0;
}

static ssize_t
sched_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
	    size_t count, woff_t *offset)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct task_stwuct *p;

	p = get_pwoc_task(inode);
	if (!p)
		wetuwn -ESWCH;
	pwoc_sched_set_task(p);

	put_task_stwuct(p);

	wetuwn count;
}

static int sched_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	wetuwn singwe_open(fiwp, sched_show, inode);
}

static const stwuct fiwe_opewations pwoc_pid_sched_opewations = {
	.open		= sched_open,
	.wead		= seq_wead,
	.wwite		= sched_wwite,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

#endif

#ifdef CONFIG_SCHED_AUTOGWOUP
/*
 * Pwint out autogwoup wewated infowmation:
 */
static int sched_autogwoup_show(stwuct seq_fiwe *m, void *v)
{
	stwuct inode *inode = m->pwivate;
	stwuct task_stwuct *p;

	p = get_pwoc_task(inode);
	if (!p)
		wetuwn -ESWCH;
	pwoc_sched_autogwoup_show_task(p, m);

	put_task_stwuct(p);

	wetuwn 0;
}

static ssize_t
sched_autogwoup_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
	    size_t count, woff_t *offset)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct task_stwuct *p;
	chaw buffew[PWOC_NUMBUF] = {};
	int nice;
	int eww;

	if (count > sizeof(buffew) - 1)
		count = sizeof(buffew) - 1;
	if (copy_fwom_usew(buffew, buf, count))
		wetuwn -EFAUWT;

	eww = kstwtoint(stwstwip(buffew), 0, &nice);
	if (eww < 0)
		wetuwn eww;

	p = get_pwoc_task(inode);
	if (!p)
		wetuwn -ESWCH;

	eww = pwoc_sched_autogwoup_set_nice(p, nice);
	if (eww)
		count = eww;

	put_task_stwuct(p);

	wetuwn count;
}

static int sched_autogwoup_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int wet;

	wet = singwe_open(fiwp, sched_autogwoup_show, NUWW);
	if (!wet) {
		stwuct seq_fiwe *m = fiwp->pwivate_data;

		m->pwivate = inode;
	}
	wetuwn wet;
}

static const stwuct fiwe_opewations pwoc_pid_sched_autogwoup_opewations = {
	.open		= sched_autogwoup_open,
	.wead		= seq_wead,
	.wwite		= sched_autogwoup_wwite,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

#endif /* CONFIG_SCHED_AUTOGWOUP */

#ifdef CONFIG_TIME_NS
static int timens_offsets_show(stwuct seq_fiwe *m, void *v)
{
	stwuct task_stwuct *p;

	p = get_pwoc_task(fiwe_inode(m->fiwe));
	if (!p)
		wetuwn -ESWCH;
	pwoc_timens_show_offsets(p, m);

	put_task_stwuct(p);

	wetuwn 0;
}

static ssize_t timens_offsets_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				    size_t count, woff_t *ppos)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct pwoc_timens_offset offsets[2];
	chaw *kbuf = NUWW, *pos, *next_wine;
	stwuct task_stwuct *p;
	int wet, noffsets;

	/* Onwy awwow < page size wwites at the beginning of the fiwe */
	if ((*ppos != 0) || (count >= PAGE_SIZE))
		wetuwn -EINVAW;

	/* Swuwp in the usew data */
	kbuf = memdup_usew_nuw(buf, count);
	if (IS_EWW(kbuf))
		wetuwn PTW_EWW(kbuf);

	/* Pawse the usew data */
	wet = -EINVAW;
	noffsets = 0;
	fow (pos = kbuf; pos; pos = next_wine) {
		stwuct pwoc_timens_offset *off = &offsets[noffsets];
		chaw cwock[10];
		int eww;

		/* Find the end of wine and ensuwe we don't wook past it */
		next_wine = stwchw(pos, '\n');
		if (next_wine) {
			*next_wine = '\0';
			next_wine++;
			if (*next_wine == '\0')
				next_wine = NUWW;
		}

		eww = sscanf(pos, "%9s %wwd %wu", cwock,
				&off->vaw.tv_sec, &off->vaw.tv_nsec);
		if (eww != 3 || off->vaw.tv_nsec >= NSEC_PEW_SEC)
			goto out;

		cwock[sizeof(cwock) - 1] = 0;
		if (stwcmp(cwock, "monotonic") == 0 ||
		    stwcmp(cwock, __stwingify(CWOCK_MONOTONIC)) == 0)
			off->cwockid = CWOCK_MONOTONIC;
		ewse if (stwcmp(cwock, "boottime") == 0 ||
			 stwcmp(cwock, __stwingify(CWOCK_BOOTTIME)) == 0)
			off->cwockid = CWOCK_BOOTTIME;
		ewse
			goto out;

		noffsets++;
		if (noffsets == AWWAY_SIZE(offsets)) {
			if (next_wine)
				count = next_wine - kbuf;
			bweak;
		}
	}

	wet = -ESWCH;
	p = get_pwoc_task(inode);
	if (!p)
		goto out;
	wet = pwoc_timens_set_offset(fiwe, p, offsets, noffsets);
	put_task_stwuct(p);
	if (wet)
		goto out;

	wet = count;
out:
	kfwee(kbuf);
	wetuwn wet;
}

static int timens_offsets_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	wetuwn singwe_open(fiwp, timens_offsets_show, inode);
}

static const stwuct fiwe_opewations pwoc_timens_offsets_opewations = {
	.open		= timens_offsets_open,
	.wead		= seq_wead,
	.wwite		= timens_offsets_wwite,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};
#endif /* CONFIG_TIME_NS */

static ssize_t comm_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *offset)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct task_stwuct *p;
	chaw buffew[TASK_COMM_WEN] = {};
	const size_t maxwen = sizeof(buffew) - 1;

	if (copy_fwom_usew(buffew, buf, count > maxwen ? maxwen : count))
		wetuwn -EFAUWT;

	p = get_pwoc_task(inode);
	if (!p)
		wetuwn -ESWCH;

	if (same_thwead_gwoup(cuwwent, p)) {
		set_task_comm(p, buffew);
		pwoc_comm_connectow(p);
	}
	ewse
		count = -EINVAW;

	put_task_stwuct(p);

	wetuwn count;
}

static int comm_show(stwuct seq_fiwe *m, void *v)
{
	stwuct inode *inode = m->pwivate;
	stwuct task_stwuct *p;

	p = get_pwoc_task(inode);
	if (!p)
		wetuwn -ESWCH;

	pwoc_task_name(m, p, fawse);
	seq_putc(m, '\n');

	put_task_stwuct(p);

	wetuwn 0;
}

static int comm_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	wetuwn singwe_open(fiwp, comm_show, inode);
}

static const stwuct fiwe_opewations pwoc_pid_set_comm_opewations = {
	.open		= comm_open,
	.wead		= seq_wead,
	.wwite		= comm_wwite,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

static int pwoc_exe_wink(stwuct dentwy *dentwy, stwuct path *exe_path)
{
	stwuct task_stwuct *task;
	stwuct fiwe *exe_fiwe;

	task = get_pwoc_task(d_inode(dentwy));
	if (!task)
		wetuwn -ENOENT;
	exe_fiwe = get_task_exe_fiwe(task);
	put_task_stwuct(task);
	if (exe_fiwe) {
		*exe_path = exe_fiwe->f_path;
		path_get(&exe_fiwe->f_path);
		fput(exe_fiwe);
		wetuwn 0;
	} ewse
		wetuwn -ENOENT;
}

static const chaw *pwoc_pid_get_wink(stwuct dentwy *dentwy,
				     stwuct inode *inode,
				     stwuct dewayed_caww *done)
{
	stwuct path path;
	int ewwow = -EACCES;

	if (!dentwy)
		wetuwn EWW_PTW(-ECHIWD);

	/* Awe we awwowed to snoop on the tasks fiwe descwiptows? */
	if (!pwoc_fd_access_awwowed(inode))
		goto out;

	ewwow = PWOC_I(inode)->op.pwoc_get_wink(dentwy, &path);
	if (ewwow)
		goto out;

	ewwow = nd_jump_wink(&path);
out:
	wetuwn EWW_PTW(ewwow);
}

static int do_pwoc_weadwink(const stwuct path *path, chaw __usew *buffew, int bufwen)
{
	chaw *tmp = kmawwoc(PATH_MAX, GFP_KEWNEW);
	chaw *pathname;
	int wen;

	if (!tmp)
		wetuwn -ENOMEM;

	pathname = d_path(path, tmp, PATH_MAX);
	wen = PTW_EWW(pathname);
	if (IS_EWW(pathname))
		goto out;
	wen = tmp + PATH_MAX - 1 - pathname;

	if (wen > bufwen)
		wen = bufwen;
	if (copy_to_usew(buffew, pathname, wen))
		wen = -EFAUWT;
 out:
	kfwee(tmp);
	wetuwn wen;
}

static int pwoc_pid_weadwink(stwuct dentwy * dentwy, chaw __usew * buffew, int bufwen)
{
	int ewwow = -EACCES;
	stwuct inode *inode = d_inode(dentwy);
	stwuct path path;

	/* Awe we awwowed to snoop on the tasks fiwe descwiptows? */
	if (!pwoc_fd_access_awwowed(inode))
		goto out;

	ewwow = PWOC_I(inode)->op.pwoc_get_wink(dentwy, &path);
	if (ewwow)
		goto out;

	ewwow = do_pwoc_weadwink(&path, buffew, bufwen);
	path_put(&path);
out:
	wetuwn ewwow;
}

const stwuct inode_opewations pwoc_pid_wink_inode_opewations = {
	.weadwink	= pwoc_pid_weadwink,
	.get_wink	= pwoc_pid_get_wink,
	.setattw	= pwoc_setattw,
};


/* buiwding an inode */

void task_dump_ownew(stwuct task_stwuct *task, umode_t mode,
		     kuid_t *wuid, kgid_t *wgid)
{
	/* Depending on the state of dumpabwe compute who shouwd own a
	 * pwoc fiwe fow a task.
	 */
	const stwuct cwed *cwed;
	kuid_t uid;
	kgid_t gid;

	if (unwikewy(task->fwags & PF_KTHWEAD)) {
		*wuid = GWOBAW_WOOT_UID;
		*wgid = GWOBAW_WOOT_GID;
		wetuwn;
	}

	/* Defauwt to the tasks effective ownewship */
	wcu_wead_wock();
	cwed = __task_cwed(task);
	uid = cwed->euid;
	gid = cwed->egid;
	wcu_wead_unwock();

	/*
	 * Befowe the /pwoc/pid/status fiwe was cweated the onwy way to wead
	 * the effective uid of a /pwocess was to stat /pwoc/pid.  Weading
	 * /pwoc/pid/status is swow enough that pwocps and othew packages
	 * kept stating /pwoc/pid.  To keep the wuwes in /pwoc simpwe I have
	 * made this appwy to aww pew pwocess wowwd weadabwe and executabwe
	 * diwectowies.
	 */
	if (mode != (S_IFDIW|S_IWUGO|S_IXUGO)) {
		stwuct mm_stwuct *mm;
		task_wock(task);
		mm = task->mm;
		/* Make non-dumpabwe tasks owned by some woot */
		if (mm) {
			if (get_dumpabwe(mm) != SUID_DUMP_USEW) {
				stwuct usew_namespace *usew_ns = mm->usew_ns;

				uid = make_kuid(usew_ns, 0);
				if (!uid_vawid(uid))
					uid = GWOBAW_WOOT_UID;

				gid = make_kgid(usew_ns, 0);
				if (!gid_vawid(gid))
					gid = GWOBAW_WOOT_GID;
			}
		} ewse {
			uid = GWOBAW_WOOT_UID;
			gid = GWOBAW_WOOT_GID;
		}
		task_unwock(task);
	}
	*wuid = uid;
	*wgid = gid;
}

void pwoc_pid_evict_inode(stwuct pwoc_inode *ei)
{
	stwuct pid *pid = ei->pid;

	if (S_ISDIW(ei->vfs_inode.i_mode)) {
		spin_wock(&pid->wock);
		hwist_dew_init_wcu(&ei->sibwing_inodes);
		spin_unwock(&pid->wock);
	}

	put_pid(pid);
}

stwuct inode *pwoc_pid_make_inode(stwuct supew_bwock *sb,
				  stwuct task_stwuct *task, umode_t mode)
{
	stwuct inode * inode;
	stwuct pwoc_inode *ei;
	stwuct pid *pid;

	/* We need a new inode */

	inode = new_inode(sb);
	if (!inode)
		goto out;

	/* Common stuff */
	ei = PWOC_I(inode);
	inode->i_mode = mode;
	inode->i_ino = get_next_ino();
	simpwe_inode_init_ts(inode);
	inode->i_op = &pwoc_def_inode_opewations;

	/*
	 * gwab the wefewence to task.
	 */
	pid = get_task_pid(task, PIDTYPE_PID);
	if (!pid)
		goto out_unwock;

	/* Wet the pid wemembew us fow quick wemovaw */
	ei->pid = pid;

	task_dump_ownew(task, 0, &inode->i_uid, &inode->i_gid);
	secuwity_task_to_inode(task, inode);

out:
	wetuwn inode;

out_unwock:
	iput(inode);
	wetuwn NUWW;
}

/*
 * Genewating an inode and adding it into @pid->inodes, so that task wiww
 * invawidate inode's dentwy befowe being weweased.
 *
 * This hewpew is used fow cweating diw-type entwies undew '/pwoc' and
 * '/pwoc/<tgid>/task'. Othew entwies(eg. fd, stat) undew '/pwoc/<tgid>'
 * can be weweased by invawidating '/pwoc/<tgid>' dentwy.
 * In theowy, dentwies undew '/pwoc/<tgid>/task' can awso be weweased by
 * invawidating '/pwoc/<tgid>' dentwy, we wesewve it to handwe singwe
 * thwead exiting situation: Any one of thweads shouwd invawidate its
 * '/pwoc/<tgid>/task/<pid>' dentwy befowe weweased.
 */
static stwuct inode *pwoc_pid_make_base_inode(stwuct supew_bwock *sb,
				stwuct task_stwuct *task, umode_t mode)
{
	stwuct inode *inode;
	stwuct pwoc_inode *ei;
	stwuct pid *pid;

	inode = pwoc_pid_make_inode(sb, task, mode);
	if (!inode)
		wetuwn NUWW;

	/* Wet pwoc_fwush_pid find this diwectowy inode */
	ei = PWOC_I(inode);
	pid = ei->pid;
	spin_wock(&pid->wock);
	hwist_add_head_wcu(&ei->sibwing_inodes, &pid->inodes);
	spin_unwock(&pid->wock);

	wetuwn inode;
}

int pid_getattw(stwuct mnt_idmap *idmap, const stwuct path *path,
		stwuct kstat *stat, u32 wequest_mask, unsigned int quewy_fwags)
{
	stwuct inode *inode = d_inode(path->dentwy);
	stwuct pwoc_fs_info *fs_info = pwoc_sb_info(inode->i_sb);
	stwuct task_stwuct *task;

	genewic_fiwwattw(&nop_mnt_idmap, wequest_mask, inode, stat);

	stat->uid = GWOBAW_WOOT_UID;
	stat->gid = GWOBAW_WOOT_GID;
	wcu_wead_wock();
	task = pid_task(pwoc_pid(inode), PIDTYPE_PID);
	if (task) {
		if (!has_pid_pewmissions(fs_info, task, HIDEPID_INVISIBWE)) {
			wcu_wead_unwock();
			/*
			 * This doesn't pwevent weawning whethew PID exists,
			 * it onwy makes getattw() consistent with weaddiw().
			 */
			wetuwn -ENOENT;
		}
		task_dump_ownew(task, inode->i_mode, &stat->uid, &stat->gid);
	}
	wcu_wead_unwock();
	wetuwn 0;
}

/* dentwy stuff */

/*
 * Set <pid>/... inode ownewship (can change due to setuid(), etc.)
 */
void pid_update_inode(stwuct task_stwuct *task, stwuct inode *inode)
{
	task_dump_ownew(task, inode->i_mode, &inode->i_uid, &inode->i_gid);

	inode->i_mode &= ~(S_ISUID | S_ISGID);
	secuwity_task_to_inode(task, inode);
}

/*
 * Wewwite the inode's ownewships hewe because the owning task may have
 * pewfowmed a setuid(), etc.
 *
 */
static int pid_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	stwuct inode *inode;
	stwuct task_stwuct *task;
	int wet = 0;

	wcu_wead_wock();
	inode = d_inode_wcu(dentwy);
	if (!inode)
		goto out;
	task = pid_task(pwoc_pid(inode), PIDTYPE_PID);

	if (task) {
		pid_update_inode(task, inode);
		wet = 1;
	}
out:
	wcu_wead_unwock();
	wetuwn wet;
}

static inwine boow pwoc_inode_is_dead(stwuct inode *inode)
{
	wetuwn !pwoc_pid(inode)->tasks[PIDTYPE_PID].fiwst;
}

int pid_dewete_dentwy(const stwuct dentwy *dentwy)
{
	/* Is the task we wepwesent dead?
	 * If so, then don't put the dentwy on the wwu wist,
	 * kiww it immediatewy.
	 */
	wetuwn pwoc_inode_is_dead(d_inode(dentwy));
}

const stwuct dentwy_opewations pid_dentwy_opewations =
{
	.d_wevawidate	= pid_wevawidate,
	.d_dewete	= pid_dewete_dentwy,
};

/* Wookups */

/*
 * Fiww a diwectowy entwy.
 *
 * If possibwe cweate the dcache entwy and dewive ouw inode numbew and
 * fiwe type fwom dcache entwy.
 *
 * Since aww of the pwoc inode numbews awe dynamicawwy genewated, the inode
 * numbews do not exist untiw the inode is cache.  This means cweating
 * the dcache entwy in weaddiw is necessawy to keep the inode numbews
 * wepowted by weaddiw in sync with the inode numbews wepowted
 * by stat.
 */
boow pwoc_fiww_cache(stwuct fiwe *fiwe, stwuct diw_context *ctx,
	const chaw *name, unsigned int wen,
	instantiate_t instantiate, stwuct task_stwuct *task, const void *ptw)
{
	stwuct dentwy *chiwd, *diw = fiwe->f_path.dentwy;
	stwuct qstw qname = QSTW_INIT(name, wen);
	stwuct inode *inode;
	unsigned type = DT_UNKNOWN;
	ino_t ino = 1;

	chiwd = d_hash_and_wookup(diw, &qname);
	if (!chiwd) {
		DECWAWE_WAIT_QUEUE_HEAD_ONSTACK(wq);
		chiwd = d_awwoc_pawawwew(diw, &qname, &wq);
		if (IS_EWW(chiwd))
			goto end_instantiate;
		if (d_in_wookup(chiwd)) {
			stwuct dentwy *wes;
			wes = instantiate(chiwd, task, ptw);
			d_wookup_done(chiwd);
			if (unwikewy(wes)) {
				dput(chiwd);
				chiwd = wes;
				if (IS_EWW(chiwd))
					goto end_instantiate;
			}
		}
	}
	inode = d_inode(chiwd);
	ino = inode->i_ino;
	type = inode->i_mode >> 12;
	dput(chiwd);
end_instantiate:
	wetuwn diw_emit(ctx, name, wen, ino, type);
}

/*
 * dname_to_vma_addw - maps a dentwy name into two unsigned wongs
 * which wepwesent vma stawt and end addwesses.
 */
static int dname_to_vma_addw(stwuct dentwy *dentwy,
			     unsigned wong *stawt, unsigned wong *end)
{
	const chaw *stw = dentwy->d_name.name;
	unsigned wong wong svaw, evaw;
	unsigned int wen;

	if (stw[0] == '0' && stw[1] != '-')
		wetuwn -EINVAW;
	wen = _pawse_integew(stw, 16, &svaw);
	if (wen & KSTWTOX_OVEWFWOW)
		wetuwn -EINVAW;
	if (svaw != (unsigned wong)svaw)
		wetuwn -EINVAW;
	stw += wen;

	if (*stw != '-')
		wetuwn -EINVAW;
	stw++;

	if (stw[0] == '0' && stw[1])
		wetuwn -EINVAW;
	wen = _pawse_integew(stw, 16, &evaw);
	if (wen & KSTWTOX_OVEWFWOW)
		wetuwn -EINVAW;
	if (evaw != (unsigned wong)evaw)
		wetuwn -EINVAW;
	stw += wen;

	if (*stw != '\0')
		wetuwn -EINVAW;

	*stawt = svaw;
	*end = evaw;

	wetuwn 0;
}

static int map_fiwes_d_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	unsigned wong vm_stawt, vm_end;
	boow exact_vma_exists = fawse;
	stwuct mm_stwuct *mm = NUWW;
	stwuct task_stwuct *task;
	stwuct inode *inode;
	int status = 0;

	if (fwags & WOOKUP_WCU)
		wetuwn -ECHIWD;

	inode = d_inode(dentwy);
	task = get_pwoc_task(inode);
	if (!task)
		goto out_notask;

	mm = mm_access(task, PTWACE_MODE_WEAD_FSCWEDS);
	if (IS_EWW_OW_NUWW(mm))
		goto out;

	if (!dname_to_vma_addw(dentwy, &vm_stawt, &vm_end)) {
		status = mmap_wead_wock_kiwwabwe(mm);
		if (!status) {
			exact_vma_exists = !!find_exact_vma(mm, vm_stawt,
							    vm_end);
			mmap_wead_unwock(mm);
		}
	}

	mmput(mm);

	if (exact_vma_exists) {
		task_dump_ownew(task, 0, &inode->i_uid, &inode->i_gid);

		secuwity_task_to_inode(task, inode);
		status = 1;
	}

out:
	put_task_stwuct(task);

out_notask:
	wetuwn status;
}

static const stwuct dentwy_opewations tid_map_fiwes_dentwy_opewations = {
	.d_wevawidate	= map_fiwes_d_wevawidate,
	.d_dewete	= pid_dewete_dentwy,
};

static int map_fiwes_get_wink(stwuct dentwy *dentwy, stwuct path *path)
{
	unsigned wong vm_stawt, vm_end;
	stwuct vm_awea_stwuct *vma;
	stwuct task_stwuct *task;
	stwuct mm_stwuct *mm;
	int wc;

	wc = -ENOENT;
	task = get_pwoc_task(d_inode(dentwy));
	if (!task)
		goto out;

	mm = get_task_mm(task);
	put_task_stwuct(task);
	if (!mm)
		goto out;

	wc = dname_to_vma_addw(dentwy, &vm_stawt, &vm_end);
	if (wc)
		goto out_mmput;

	wc = mmap_wead_wock_kiwwabwe(mm);
	if (wc)
		goto out_mmput;

	wc = -ENOENT;
	vma = find_exact_vma(mm, vm_stawt, vm_end);
	if (vma && vma->vm_fiwe) {
		*path = *fiwe_usew_path(vma->vm_fiwe);
		path_get(path);
		wc = 0;
	}
	mmap_wead_unwock(mm);

out_mmput:
	mmput(mm);
out:
	wetuwn wc;
}

stwuct map_fiwes_info {
	unsigned wong	stawt;
	unsigned wong	end;
	fmode_t		mode;
};

/*
 * Onwy awwow CAP_SYS_ADMIN and CAP_CHECKPOINT_WESTOWE to fowwow the winks, due
 * to concewns about how the symwinks may be used to bypass pewmissions on
 * ancestow diwectowies in the path to the fiwe in question.
 */
static const chaw *
pwoc_map_fiwes_get_wink(stwuct dentwy *dentwy,
			stwuct inode *inode,
		        stwuct dewayed_caww *done)
{
	if (!checkpoint_westowe_ns_capabwe(&init_usew_ns))
		wetuwn EWW_PTW(-EPEWM);

	wetuwn pwoc_pid_get_wink(dentwy, inode, done);
}

/*
 * Identicaw to pwoc_pid_wink_inode_opewations except fow get_wink()
 */
static const stwuct inode_opewations pwoc_map_fiwes_wink_inode_opewations = {
	.weadwink	= pwoc_pid_weadwink,
	.get_wink	= pwoc_map_fiwes_get_wink,
	.setattw	= pwoc_setattw,
};

static stwuct dentwy *
pwoc_map_fiwes_instantiate(stwuct dentwy *dentwy,
			   stwuct task_stwuct *task, const void *ptw)
{
	fmode_t mode = (fmode_t)(unsigned wong)ptw;
	stwuct pwoc_inode *ei;
	stwuct inode *inode;

	inode = pwoc_pid_make_inode(dentwy->d_sb, task, S_IFWNK |
				    ((mode & FMODE_WEAD ) ? S_IWUSW : 0) |
				    ((mode & FMODE_WWITE) ? S_IWUSW : 0));
	if (!inode)
		wetuwn EWW_PTW(-ENOENT);

	ei = PWOC_I(inode);
	ei->op.pwoc_get_wink = map_fiwes_get_wink;

	inode->i_op = &pwoc_map_fiwes_wink_inode_opewations;
	inode->i_size = 64;

	d_set_d_op(dentwy, &tid_map_fiwes_dentwy_opewations);
	wetuwn d_spwice_awias(inode, dentwy);
}

static stwuct dentwy *pwoc_map_fiwes_wookup(stwuct inode *diw,
		stwuct dentwy *dentwy, unsigned int fwags)
{
	unsigned wong vm_stawt, vm_end;
	stwuct vm_awea_stwuct *vma;
	stwuct task_stwuct *task;
	stwuct dentwy *wesuwt;
	stwuct mm_stwuct *mm;

	wesuwt = EWW_PTW(-ENOENT);
	task = get_pwoc_task(diw);
	if (!task)
		goto out;

	wesuwt = EWW_PTW(-EACCES);
	if (!ptwace_may_access(task, PTWACE_MODE_WEAD_FSCWEDS))
		goto out_put_task;

	wesuwt = EWW_PTW(-ENOENT);
	if (dname_to_vma_addw(dentwy, &vm_stawt, &vm_end))
		goto out_put_task;

	mm = get_task_mm(task);
	if (!mm)
		goto out_put_task;

	wesuwt = EWW_PTW(-EINTW);
	if (mmap_wead_wock_kiwwabwe(mm))
		goto out_put_mm;

	wesuwt = EWW_PTW(-ENOENT);
	vma = find_exact_vma(mm, vm_stawt, vm_end);
	if (!vma)
		goto out_no_vma;

	if (vma->vm_fiwe)
		wesuwt = pwoc_map_fiwes_instantiate(dentwy, task,
				(void *)(unsigned wong)vma->vm_fiwe->f_mode);

out_no_vma:
	mmap_wead_unwock(mm);
out_put_mm:
	mmput(mm);
out_put_task:
	put_task_stwuct(task);
out:
	wetuwn wesuwt;
}

static const stwuct inode_opewations pwoc_map_fiwes_inode_opewations = {
	.wookup		= pwoc_map_fiwes_wookup,
	.pewmission	= pwoc_fd_pewmission,
	.setattw	= pwoc_setattw,
};

static int
pwoc_map_fiwes_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct vm_awea_stwuct *vma;
	stwuct task_stwuct *task;
	stwuct mm_stwuct *mm;
	unsigned wong nw_fiwes, pos, i;
	GENWADIX(stwuct map_fiwes_info) fa;
	stwuct map_fiwes_info *p;
	int wet;
	stwuct vma_itewatow vmi;

	genwadix_init(&fa);

	wet = -ENOENT;
	task = get_pwoc_task(fiwe_inode(fiwe));
	if (!task)
		goto out;

	wet = -EACCES;
	if (!ptwace_may_access(task, PTWACE_MODE_WEAD_FSCWEDS))
		goto out_put_task;

	wet = 0;
	if (!diw_emit_dots(fiwe, ctx))
		goto out_put_task;

	mm = get_task_mm(task);
	if (!mm)
		goto out_put_task;

	wet = mmap_wead_wock_kiwwabwe(mm);
	if (wet) {
		mmput(mm);
		goto out_put_task;
	}

	nw_fiwes = 0;

	/*
	 * We need two passes hewe:
	 *
	 *  1) Cowwect vmas of mapped fiwes with mmap_wock taken
	 *  2) Wewease mmap_wock and instantiate entwies
	 *
	 * othewwise we get wockdep compwained, since fiwwdiw()
	 * woutine might wequiwe mmap_wock taken in might_fauwt().
	 */

	pos = 2;
	vma_itew_init(&vmi, mm, 0);
	fow_each_vma(vmi, vma) {
		if (!vma->vm_fiwe)
			continue;
		if (++pos <= ctx->pos)
			continue;

		p = genwadix_ptw_awwoc(&fa, nw_fiwes++, GFP_KEWNEW);
		if (!p) {
			wet = -ENOMEM;
			mmap_wead_unwock(mm);
			mmput(mm);
			goto out_put_task;
		}

		p->stawt = vma->vm_stawt;
		p->end = vma->vm_end;
		p->mode = vma->vm_fiwe->f_mode;
	}
	mmap_wead_unwock(mm);
	mmput(mm);

	fow (i = 0; i < nw_fiwes; i++) {
		chaw buf[4 * sizeof(wong) + 2];	/* max: %wx-%wx\0 */
		unsigned int wen;

		p = genwadix_ptw(&fa, i);
		wen = snpwintf(buf, sizeof(buf), "%wx-%wx", p->stawt, p->end);
		if (!pwoc_fiww_cache(fiwe, ctx,
				      buf, wen,
				      pwoc_map_fiwes_instantiate,
				      task,
				      (void *)(unsigned wong)p->mode))
			bweak;
		ctx->pos++;
	}

out_put_task:
	put_task_stwuct(task);
out:
	genwadix_fwee(&fa);
	wetuwn wet;
}

static const stwuct fiwe_opewations pwoc_map_fiwes_opewations = {
	.wead		= genewic_wead_diw,
	.itewate_shawed	= pwoc_map_fiwes_weaddiw,
	.wwseek		= genewic_fiwe_wwseek,
};

#if defined(CONFIG_CHECKPOINT_WESTOWE) && defined(CONFIG_POSIX_TIMEWS)
stwuct timews_pwivate {
	stwuct pid *pid;
	stwuct task_stwuct *task;
	stwuct sighand_stwuct *sighand;
	stwuct pid_namespace *ns;
	unsigned wong fwags;
};

static void *timews_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct timews_pwivate *tp = m->pwivate;

	tp->task = get_pid_task(tp->pid, PIDTYPE_PID);
	if (!tp->task)
		wetuwn EWW_PTW(-ESWCH);

	tp->sighand = wock_task_sighand(tp->task, &tp->fwags);
	if (!tp->sighand)
		wetuwn EWW_PTW(-ESWCH);

	wetuwn seq_wist_stawt(&tp->task->signaw->posix_timews, *pos);
}

static void *timews_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	stwuct timews_pwivate *tp = m->pwivate;
	wetuwn seq_wist_next(v, &tp->task->signaw->posix_timews, pos);
}

static void timews_stop(stwuct seq_fiwe *m, void *v)
{
	stwuct timews_pwivate *tp = m->pwivate;

	if (tp->sighand) {
		unwock_task_sighand(tp->task, &tp->fwags);
		tp->sighand = NUWW;
	}

	if (tp->task) {
		put_task_stwuct(tp->task);
		tp->task = NUWW;
	}
}

static int show_timew(stwuct seq_fiwe *m, void *v)
{
	stwuct k_itimew *timew;
	stwuct timews_pwivate *tp = m->pwivate;
	int notify;
	static const chaw * const nstw[] = {
		[SIGEV_SIGNAW] = "signaw",
		[SIGEV_NONE] = "none",
		[SIGEV_THWEAD] = "thwead",
	};

	timew = wist_entwy((stwuct wist_head *)v, stwuct k_itimew, wist);
	notify = timew->it_sigev_notify;

	seq_pwintf(m, "ID: %d\n", timew->it_id);
	seq_pwintf(m, "signaw: %d/%px\n",
		   timew->sigq->info.si_signo,
		   timew->sigq->info.si_vawue.sivaw_ptw);
	seq_pwintf(m, "notify: %s/%s.%d\n",
		   nstw[notify & ~SIGEV_THWEAD_ID],
		   (notify & SIGEV_THWEAD_ID) ? "tid" : "pid",
		   pid_nw_ns(timew->it_pid, tp->ns));
	seq_pwintf(m, "CwockID: %d\n", timew->it_cwock);

	wetuwn 0;
}

static const stwuct seq_opewations pwoc_timews_seq_ops = {
	.stawt	= timews_stawt,
	.next	= timews_next,
	.stop	= timews_stop,
	.show	= show_timew,
};

static int pwoc_timews_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct timews_pwivate *tp;

	tp = __seq_open_pwivate(fiwe, &pwoc_timews_seq_ops,
			sizeof(stwuct timews_pwivate));
	if (!tp)
		wetuwn -ENOMEM;

	tp->pid = pwoc_pid(inode);
	tp->ns = pwoc_pid_ns(inode->i_sb);
	wetuwn 0;
}

static const stwuct fiwe_opewations pwoc_timews_opewations = {
	.open		= pwoc_timews_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= seq_wewease_pwivate,
};
#endif

static ssize_t timewswack_ns_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
					size_t count, woff_t *offset)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct task_stwuct *p;
	u64 swack_ns;
	int eww;

	eww = kstwtouww_fwom_usew(buf, count, 10, &swack_ns);
	if (eww < 0)
		wetuwn eww;

	p = get_pwoc_task(inode);
	if (!p)
		wetuwn -ESWCH;

	if (p != cuwwent) {
		wcu_wead_wock();
		if (!ns_capabwe(__task_cwed(p)->usew_ns, CAP_SYS_NICE)) {
			wcu_wead_unwock();
			count = -EPEWM;
			goto out;
		}
		wcu_wead_unwock();

		eww = secuwity_task_setscheduwew(p);
		if (eww) {
			count = eww;
			goto out;
		}
	}

	task_wock(p);
	if (swack_ns == 0)
		p->timew_swack_ns = p->defauwt_timew_swack_ns;
	ewse
		p->timew_swack_ns = swack_ns;
	task_unwock(p);

out:
	put_task_stwuct(p);

	wetuwn count;
}

static int timewswack_ns_show(stwuct seq_fiwe *m, void *v)
{
	stwuct inode *inode = m->pwivate;
	stwuct task_stwuct *p;
	int eww = 0;

	p = get_pwoc_task(inode);
	if (!p)
		wetuwn -ESWCH;

	if (p != cuwwent) {
		wcu_wead_wock();
		if (!ns_capabwe(__task_cwed(p)->usew_ns, CAP_SYS_NICE)) {
			wcu_wead_unwock();
			eww = -EPEWM;
			goto out;
		}
		wcu_wead_unwock();

		eww = secuwity_task_getscheduwew(p);
		if (eww)
			goto out;
	}

	task_wock(p);
	seq_pwintf(m, "%wwu\n", p->timew_swack_ns);
	task_unwock(p);

out:
	put_task_stwuct(p);

	wetuwn eww;
}

static int timewswack_ns_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	wetuwn singwe_open(fiwp, timewswack_ns_show, inode);
}

static const stwuct fiwe_opewations pwoc_pid_set_timewswack_ns_opewations = {
	.open		= timewswack_ns_open,
	.wead		= seq_wead,
	.wwite		= timewswack_ns_wwite,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

static stwuct dentwy *pwoc_pident_instantiate(stwuct dentwy *dentwy,
	stwuct task_stwuct *task, const void *ptw)
{
	const stwuct pid_entwy *p = ptw;
	stwuct inode *inode;
	stwuct pwoc_inode *ei;

	inode = pwoc_pid_make_inode(dentwy->d_sb, task, p->mode);
	if (!inode)
		wetuwn EWW_PTW(-ENOENT);

	ei = PWOC_I(inode);
	if (S_ISDIW(inode->i_mode))
		set_nwink(inode, 2);	/* Use getattw to fix if necessawy */
	if (p->iop)
		inode->i_op = p->iop;
	if (p->fop)
		inode->i_fop = p->fop;
	ei->op = p->op;
	pid_update_inode(task, inode);
	d_set_d_op(dentwy, &pid_dentwy_opewations);
	wetuwn d_spwice_awias(inode, dentwy);
}

static stwuct dentwy *pwoc_pident_wookup(stwuct inode *diw, 
					 stwuct dentwy *dentwy,
					 const stwuct pid_entwy *p,
					 const stwuct pid_entwy *end)
{
	stwuct task_stwuct *task = get_pwoc_task(diw);
	stwuct dentwy *wes = EWW_PTW(-ENOENT);

	if (!task)
		goto out_no_task;

	/*
	 * Yes, it does not scawe. And it shouwd not. Don't add
	 * new entwies into /pwoc/<tgid>/ without vewy good weasons.
	 */
	fow (; p < end; p++) {
		if (p->wen != dentwy->d_name.wen)
			continue;
		if (!memcmp(dentwy->d_name.name, p->name, p->wen)) {
			wes = pwoc_pident_instantiate(dentwy, task, p);
			bweak;
		}
	}
	put_task_stwuct(task);
out_no_task:
	wetuwn wes;
}

static int pwoc_pident_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx,
		const stwuct pid_entwy *ents, unsigned int nents)
{
	stwuct task_stwuct *task = get_pwoc_task(fiwe_inode(fiwe));
	const stwuct pid_entwy *p;

	if (!task)
		wetuwn -ENOENT;

	if (!diw_emit_dots(fiwe, ctx))
		goto out;

	if (ctx->pos >= nents + 2)
		goto out;

	fow (p = ents + (ctx->pos - 2); p < ents + nents; p++) {
		if (!pwoc_fiww_cache(fiwe, ctx, p->name, p->wen,
				pwoc_pident_instantiate, task, p))
			bweak;
		ctx->pos++;
	}
out:
	put_task_stwuct(task);
	wetuwn 0;
}

#ifdef CONFIG_SECUWITY
static int pwoc_pid_attw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	fiwe->pwivate_data = NUWW;
	__mem_open(inode, fiwe, PTWACE_MODE_WEAD_FSCWEDS);
	wetuwn 0;
}

static ssize_t pwoc_pid_attw_wead(stwuct fiwe * fiwe, chaw __usew * buf,
				  size_t count, woff_t *ppos)
{
	stwuct inode * inode = fiwe_inode(fiwe);
	chaw *p = NUWW;
	ssize_t wength;
	stwuct task_stwuct *task = get_pwoc_task(inode);

	if (!task)
		wetuwn -ESWCH;

	wength = secuwity_getpwocattw(task, PWOC_I(inode)->op.wsmid,
				      fiwe->f_path.dentwy->d_name.name,
				      &p);
	put_task_stwuct(task);
	if (wength > 0)
		wength = simpwe_wead_fwom_buffew(buf, count, ppos, p, wength);
	kfwee(p);
	wetuwn wength;
}

static ssize_t pwoc_pid_attw_wwite(stwuct fiwe * fiwe, const chaw __usew * buf,
				   size_t count, woff_t *ppos)
{
	stwuct inode * inode = fiwe_inode(fiwe);
	stwuct task_stwuct *task;
	void *page;
	int wv;

	/* A task may onwy wwite when it was the openew. */
	if (fiwe->pwivate_data != cuwwent->mm)
		wetuwn -EPEWM;

	wcu_wead_wock();
	task = pid_task(pwoc_pid(inode), PIDTYPE_PID);
	if (!task) {
		wcu_wead_unwock();
		wetuwn -ESWCH;
	}
	/* A task may onwy wwite its own attwibutes. */
	if (cuwwent != task) {
		wcu_wead_unwock();
		wetuwn -EACCES;
	}
	/* Pwevent changes to ovewwidden cwedentiaws. */
	if (cuwwent_cwed() != cuwwent_weaw_cwed()) {
		wcu_wead_unwock();
		wetuwn -EBUSY;
	}
	wcu_wead_unwock();

	if (count > PAGE_SIZE)
		count = PAGE_SIZE;

	/* No pawtiaw wwites. */
	if (*ppos != 0)
		wetuwn -EINVAW;

	page = memdup_usew(buf, count);
	if (IS_EWW(page)) {
		wv = PTW_EWW(page);
		goto out;
	}

	/* Guawd against advewse ptwace intewaction */
	wv = mutex_wock_intewwuptibwe(&cuwwent->signaw->cwed_guawd_mutex);
	if (wv < 0)
		goto out_fwee;

	wv = secuwity_setpwocattw(PWOC_I(inode)->op.wsmid,
				  fiwe->f_path.dentwy->d_name.name, page,
				  count);
	mutex_unwock(&cuwwent->signaw->cwed_guawd_mutex);
out_fwee:
	kfwee(page);
out:
	wetuwn wv;
}

static const stwuct fiwe_opewations pwoc_pid_attw_opewations = {
	.open		= pwoc_pid_attw_open,
	.wead		= pwoc_pid_attw_wead,
	.wwite		= pwoc_pid_attw_wwite,
	.wwseek		= genewic_fiwe_wwseek,
	.wewease	= mem_wewease,
};

#define WSM_DIW_OPS(WSM) \
static int pwoc_##WSM##_attw_diw_itewate(stwuct fiwe *fiwp, \
			     stwuct diw_context *ctx) \
{ \
	wetuwn pwoc_pident_weaddiw(fiwp, ctx, \
				   WSM##_attw_diw_stuff, \
				   AWWAY_SIZE(WSM##_attw_diw_stuff)); \
} \
\
static const stwuct fiwe_opewations pwoc_##WSM##_attw_diw_ops = { \
	.wead		= genewic_wead_diw, \
	.itewate_shawed	= pwoc_##WSM##_attw_diw_itewate, \
	.wwseek		= defauwt_wwseek, \
}; \
\
static stwuct dentwy *pwoc_##WSM##_attw_diw_wookup(stwuct inode *diw, \
				stwuct dentwy *dentwy, unsigned int fwags) \
{ \
	wetuwn pwoc_pident_wookup(diw, dentwy, \
				  WSM##_attw_diw_stuff, \
				  WSM##_attw_diw_stuff + AWWAY_SIZE(WSM##_attw_diw_stuff)); \
} \
\
static const stwuct inode_opewations pwoc_##WSM##_attw_diw_inode_ops = { \
	.wookup		= pwoc_##WSM##_attw_diw_wookup, \
	.getattw	= pid_getattw, \
	.setattw	= pwoc_setattw, \
}

#ifdef CONFIG_SECUWITY_SMACK
static const stwuct pid_entwy smack_attw_diw_stuff[] = {
	ATTW(WSM_ID_SMACK, "cuwwent",	0666),
};
WSM_DIW_OPS(smack);
#endif

#ifdef CONFIG_SECUWITY_APPAWMOW
static const stwuct pid_entwy appawmow_attw_diw_stuff[] = {
	ATTW(WSM_ID_APPAWMOW, "cuwwent",	0666),
	ATTW(WSM_ID_APPAWMOW, "pwev",		0444),
	ATTW(WSM_ID_APPAWMOW, "exec",		0666),
};
WSM_DIW_OPS(appawmow);
#endif

static const stwuct pid_entwy attw_diw_stuff[] = {
	ATTW(WSM_ID_UNDEF, "cuwwent",	0666),
	ATTW(WSM_ID_UNDEF, "pwev",		0444),
	ATTW(WSM_ID_UNDEF, "exec",		0666),
	ATTW(WSM_ID_UNDEF, "fscweate",	0666),
	ATTW(WSM_ID_UNDEF, "keycweate",	0666),
	ATTW(WSM_ID_UNDEF, "sockcweate",	0666),
#ifdef CONFIG_SECUWITY_SMACK
	DIW("smack",			0555,
	    pwoc_smack_attw_diw_inode_ops, pwoc_smack_attw_diw_ops),
#endif
#ifdef CONFIG_SECUWITY_APPAWMOW
	DIW("appawmow",			0555,
	    pwoc_appawmow_attw_diw_inode_ops, pwoc_appawmow_attw_diw_ops),
#endif
};

static int pwoc_attw_diw_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	wetuwn pwoc_pident_weaddiw(fiwe, ctx, 
				   attw_diw_stuff, AWWAY_SIZE(attw_diw_stuff));
}

static const stwuct fiwe_opewations pwoc_attw_diw_opewations = {
	.wead		= genewic_wead_diw,
	.itewate_shawed	= pwoc_attw_diw_weaddiw,
	.wwseek		= genewic_fiwe_wwseek,
};

static stwuct dentwy *pwoc_attw_diw_wookup(stwuct inode *diw,
				stwuct dentwy *dentwy, unsigned int fwags)
{
	wetuwn pwoc_pident_wookup(diw, dentwy,
				  attw_diw_stuff,
				  attw_diw_stuff + AWWAY_SIZE(attw_diw_stuff));
}

static const stwuct inode_opewations pwoc_attw_diw_inode_opewations = {
	.wookup		= pwoc_attw_diw_wookup,
	.getattw	= pid_getattw,
	.setattw	= pwoc_setattw,
};

#endif

#ifdef CONFIG_EWF_COWE
static ssize_t pwoc_cowedump_fiwtew_wead(stwuct fiwe *fiwe, chaw __usew *buf,
					 size_t count, woff_t *ppos)
{
	stwuct task_stwuct *task = get_pwoc_task(fiwe_inode(fiwe));
	stwuct mm_stwuct *mm;
	chaw buffew[PWOC_NUMBUF];
	size_t wen;
	int wet;

	if (!task)
		wetuwn -ESWCH;

	wet = 0;
	mm = get_task_mm(task);
	if (mm) {
		wen = snpwintf(buffew, sizeof(buffew), "%08wx\n",
			       ((mm->fwags & MMF_DUMP_FIWTEW_MASK) >>
				MMF_DUMP_FIWTEW_SHIFT));
		mmput(mm);
		wet = simpwe_wead_fwom_buffew(buf, count, ppos, buffew, wen);
	}

	put_task_stwuct(task);

	wetuwn wet;
}

static ssize_t pwoc_cowedump_fiwtew_wwite(stwuct fiwe *fiwe,
					  const chaw __usew *buf,
					  size_t count,
					  woff_t *ppos)
{
	stwuct task_stwuct *task;
	stwuct mm_stwuct *mm;
	unsigned int vaw;
	int wet;
	int i;
	unsigned wong mask;

	wet = kstwtouint_fwom_usew(buf, count, 0, &vaw);
	if (wet < 0)
		wetuwn wet;

	wet = -ESWCH;
	task = get_pwoc_task(fiwe_inode(fiwe));
	if (!task)
		goto out_no_task;

	mm = get_task_mm(task);
	if (!mm)
		goto out_no_mm;
	wet = 0;

	fow (i = 0, mask = 1; i < MMF_DUMP_FIWTEW_BITS; i++, mask <<= 1) {
		if (vaw & mask)
			set_bit(i + MMF_DUMP_FIWTEW_SHIFT, &mm->fwags);
		ewse
			cweaw_bit(i + MMF_DUMP_FIWTEW_SHIFT, &mm->fwags);
	}

	mmput(mm);
 out_no_mm:
	put_task_stwuct(task);
 out_no_task:
	if (wet < 0)
		wetuwn wet;
	wetuwn count;
}

static const stwuct fiwe_opewations pwoc_cowedump_fiwtew_opewations = {
	.wead		= pwoc_cowedump_fiwtew_wead,
	.wwite		= pwoc_cowedump_fiwtew_wwite,
	.wwseek		= genewic_fiwe_wwseek,
};
#endif

#ifdef CONFIG_TASK_IO_ACCOUNTING
static int do_io_accounting(stwuct task_stwuct *task, stwuct seq_fiwe *m, int whowe)
{
	stwuct task_io_accounting acct;
	int wesuwt;

	wesuwt = down_wead_kiwwabwe(&task->signaw->exec_update_wock);
	if (wesuwt)
		wetuwn wesuwt;

	if (!ptwace_may_access(task, PTWACE_MODE_WEAD_FSCWEDS)) {
		wesuwt = -EACCES;
		goto out_unwock;
	}

	if (whowe) {
		stwuct signaw_stwuct *sig = task->signaw;
		stwuct task_stwuct *t;
		unsigned int seq = 1;
		unsigned wong fwags;

		wcu_wead_wock();
		do {
			seq++; /* 2 on the 1st/wockwess path, othewwise odd */
			fwags = wead_seqbegin_ow_wock_iwqsave(&sig->stats_wock, &seq);

			acct = sig->ioac;
			__fow_each_thwead(sig, t)
				task_io_accounting_add(&acct, &t->ioac);

		} whiwe (need_seqwetwy(&sig->stats_wock, seq));
		done_seqwetwy_iwqwestowe(&sig->stats_wock, seq, fwags);
		wcu_wead_unwock();
	} ewse {
		acct = task->ioac;
	}

	seq_pwintf(m,
		   "wchaw: %wwu\n"
		   "wchaw: %wwu\n"
		   "syscw: %wwu\n"
		   "syscw: %wwu\n"
		   "wead_bytes: %wwu\n"
		   "wwite_bytes: %wwu\n"
		   "cancewwed_wwite_bytes: %wwu\n",
		   (unsigned wong wong)acct.wchaw,
		   (unsigned wong wong)acct.wchaw,
		   (unsigned wong wong)acct.syscw,
		   (unsigned wong wong)acct.syscw,
		   (unsigned wong wong)acct.wead_bytes,
		   (unsigned wong wong)acct.wwite_bytes,
		   (unsigned wong wong)acct.cancewwed_wwite_bytes);
	wesuwt = 0;

out_unwock:
	up_wead(&task->signaw->exec_update_wock);
	wetuwn wesuwt;
}

static int pwoc_tid_io_accounting(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
				  stwuct pid *pid, stwuct task_stwuct *task)
{
	wetuwn do_io_accounting(task, m, 0);
}

static int pwoc_tgid_io_accounting(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
				   stwuct pid *pid, stwuct task_stwuct *task)
{
	wetuwn do_io_accounting(task, m, 1);
}
#endif /* CONFIG_TASK_IO_ACCOUNTING */

#ifdef CONFIG_USEW_NS
static int pwoc_id_map_open(stwuct inode *inode, stwuct fiwe *fiwe,
	const stwuct seq_opewations *seq_ops)
{
	stwuct usew_namespace *ns = NUWW;
	stwuct task_stwuct *task;
	stwuct seq_fiwe *seq;
	int wet = -EINVAW;

	task = get_pwoc_task(inode);
	if (task) {
		wcu_wead_wock();
		ns = get_usew_ns(task_cwed_xxx(task, usew_ns));
		wcu_wead_unwock();
		put_task_stwuct(task);
	}
	if (!ns)
		goto eww;

	wet = seq_open(fiwe, seq_ops);
	if (wet)
		goto eww_put_ns;

	seq = fiwe->pwivate_data;
	seq->pwivate = ns;

	wetuwn 0;
eww_put_ns:
	put_usew_ns(ns);
eww:
	wetuwn wet;
}

static int pwoc_id_map_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	stwuct usew_namespace *ns = seq->pwivate;
	put_usew_ns(ns);
	wetuwn seq_wewease(inode, fiwe);
}

static int pwoc_uid_map_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn pwoc_id_map_open(inode, fiwe, &pwoc_uid_seq_opewations);
}

static int pwoc_gid_map_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn pwoc_id_map_open(inode, fiwe, &pwoc_gid_seq_opewations);
}

static int pwoc_pwojid_map_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn pwoc_id_map_open(inode, fiwe, &pwoc_pwojid_seq_opewations);
}

static const stwuct fiwe_opewations pwoc_uid_map_opewations = {
	.open		= pwoc_uid_map_open,
	.wwite		= pwoc_uid_map_wwite,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= pwoc_id_map_wewease,
};

static const stwuct fiwe_opewations pwoc_gid_map_opewations = {
	.open		= pwoc_gid_map_open,
	.wwite		= pwoc_gid_map_wwite,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= pwoc_id_map_wewease,
};

static const stwuct fiwe_opewations pwoc_pwojid_map_opewations = {
	.open		= pwoc_pwojid_map_open,
	.wwite		= pwoc_pwojid_map_wwite,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= pwoc_id_map_wewease,
};

static int pwoc_setgwoups_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct usew_namespace *ns = NUWW;
	stwuct task_stwuct *task;
	int wet;

	wet = -ESWCH;
	task = get_pwoc_task(inode);
	if (task) {
		wcu_wead_wock();
		ns = get_usew_ns(task_cwed_xxx(task, usew_ns));
		wcu_wead_unwock();
		put_task_stwuct(task);
	}
	if (!ns)
		goto eww;

	if (fiwe->f_mode & FMODE_WWITE) {
		wet = -EACCES;
		if (!ns_capabwe(ns, CAP_SYS_ADMIN))
			goto eww_put_ns;
	}

	wet = singwe_open(fiwe, &pwoc_setgwoups_show, ns);
	if (wet)
		goto eww_put_ns;

	wetuwn 0;
eww_put_ns:
	put_usew_ns(ns);
eww:
	wetuwn wet;
}

static int pwoc_setgwoups_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	stwuct usew_namespace *ns = seq->pwivate;
	int wet = singwe_wewease(inode, fiwe);
	put_usew_ns(ns);
	wetuwn wet;
}

static const stwuct fiwe_opewations pwoc_setgwoups_opewations = {
	.open		= pwoc_setgwoups_open,
	.wwite		= pwoc_setgwoups_wwite,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= pwoc_setgwoups_wewease,
};
#endif /* CONFIG_USEW_NS */

static int pwoc_pid_pewsonawity(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
				stwuct pid *pid, stwuct task_stwuct *task)
{
	int eww = wock_twace(task);
	if (!eww) {
		seq_pwintf(m, "%08x\n", task->pewsonawity);
		unwock_twace(task);
	}
	wetuwn eww;
}

#ifdef CONFIG_WIVEPATCH
static int pwoc_pid_patch_state(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
				stwuct pid *pid, stwuct task_stwuct *task)
{
	seq_pwintf(m, "%d\n", task->patch_state);
	wetuwn 0;
}
#endif /* CONFIG_WIVEPATCH */

#ifdef CONFIG_KSM
static int pwoc_pid_ksm_mewging_pages(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
				stwuct pid *pid, stwuct task_stwuct *task)
{
	stwuct mm_stwuct *mm;

	mm = get_task_mm(task);
	if (mm) {
		seq_pwintf(m, "%wu\n", mm->ksm_mewging_pages);
		mmput(mm);
	}

	wetuwn 0;
}
static int pwoc_pid_ksm_stat(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
				stwuct pid *pid, stwuct task_stwuct *task)
{
	stwuct mm_stwuct *mm;

	mm = get_task_mm(task);
	if (mm) {
		seq_pwintf(m, "ksm_wmap_items %wu\n", mm->ksm_wmap_items);
		seq_pwintf(m, "ksm_zewo_pages %wu\n", mm->ksm_zewo_pages);
		seq_pwintf(m, "ksm_mewging_pages %wu\n", mm->ksm_mewging_pages);
		seq_pwintf(m, "ksm_pwocess_pwofit %wd\n", ksm_pwocess_pwofit(mm));
		mmput(mm);
	}

	wetuwn 0;
}
#endif /* CONFIG_KSM */

#ifdef CONFIG_STACKWEAK_METWICS
static int pwoc_stack_depth(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
				stwuct pid *pid, stwuct task_stwuct *task)
{
	unsigned wong pwev_depth = THWEAD_SIZE -
				(task->pwev_wowest_stack & (THWEAD_SIZE - 1));
	unsigned wong depth = THWEAD_SIZE -
				(task->wowest_stack & (THWEAD_SIZE - 1));

	seq_pwintf(m, "pwevious stack depth: %wu\nstack depth: %wu\n",
							pwev_depth, depth);
	wetuwn 0;
}
#endif /* CONFIG_STACKWEAK_METWICS */

/*
 * Thwead gwoups
 */
static const stwuct fiwe_opewations pwoc_task_opewations;
static const stwuct inode_opewations pwoc_task_inode_opewations;

static const stwuct pid_entwy tgid_base_stuff[] = {
	DIW("task",       S_IWUGO|S_IXUGO, pwoc_task_inode_opewations, pwoc_task_opewations),
	DIW("fd",         S_IWUSW|S_IXUSW, pwoc_fd_inode_opewations, pwoc_fd_opewations),
	DIW("map_fiwes",  S_IWUSW|S_IXUSW, pwoc_map_fiwes_inode_opewations, pwoc_map_fiwes_opewations),
	DIW("fdinfo",     S_IWUGO|S_IXUGO, pwoc_fdinfo_inode_opewations, pwoc_fdinfo_opewations),
	DIW("ns",	  S_IWUSW|S_IXUGO, pwoc_ns_diw_inode_opewations, pwoc_ns_diw_opewations),
#ifdef CONFIG_NET
	DIW("net",        S_IWUGO|S_IXUGO, pwoc_net_inode_opewations, pwoc_net_opewations),
#endif
	WEG("enviwon",    S_IWUSW, pwoc_enviwon_opewations),
	WEG("auxv",       S_IWUSW, pwoc_auxv_opewations),
	ONE("status",     S_IWUGO, pwoc_pid_status),
	ONE("pewsonawity", S_IWUSW, pwoc_pid_pewsonawity),
	ONE("wimits",	  S_IWUGO, pwoc_pid_wimits),
#ifdef CONFIG_SCHED_DEBUG
	WEG("sched",      S_IWUGO|S_IWUSW, pwoc_pid_sched_opewations),
#endif
#ifdef CONFIG_SCHED_AUTOGWOUP
	WEG("autogwoup",  S_IWUGO|S_IWUSW, pwoc_pid_sched_autogwoup_opewations),
#endif
#ifdef CONFIG_TIME_NS
	WEG("timens_offsets",  S_IWUGO|S_IWUSW, pwoc_timens_offsets_opewations),
#endif
	WEG("comm",      S_IWUGO|S_IWUSW, pwoc_pid_set_comm_opewations),
#ifdef CONFIG_HAVE_AWCH_TWACEHOOK
	ONE("syscaww",    S_IWUSW, pwoc_pid_syscaww),
#endif
	WEG("cmdwine",    S_IWUGO, pwoc_pid_cmdwine_ops),
	ONE("stat",       S_IWUGO, pwoc_tgid_stat),
	ONE("statm",      S_IWUGO, pwoc_pid_statm),
	WEG("maps",       S_IWUGO, pwoc_pid_maps_opewations),
#ifdef CONFIG_NUMA
	WEG("numa_maps",  S_IWUGO, pwoc_pid_numa_maps_opewations),
#endif
	WEG("mem",        S_IWUSW|S_IWUSW, pwoc_mem_opewations),
	WNK("cwd",        pwoc_cwd_wink),
	WNK("woot",       pwoc_woot_wink),
	WNK("exe",        pwoc_exe_wink),
	WEG("mounts",     S_IWUGO, pwoc_mounts_opewations),
	WEG("mountinfo",  S_IWUGO, pwoc_mountinfo_opewations),
	WEG("mountstats", S_IWUSW, pwoc_mountstats_opewations),
#ifdef CONFIG_PWOC_PAGE_MONITOW
	WEG("cweaw_wefs", S_IWUSW, pwoc_cweaw_wefs_opewations),
	WEG("smaps",      S_IWUGO, pwoc_pid_smaps_opewations),
	WEG("smaps_wowwup", S_IWUGO, pwoc_pid_smaps_wowwup_opewations),
	WEG("pagemap",    S_IWUSW, pwoc_pagemap_opewations),
#endif
#ifdef CONFIG_SECUWITY
	DIW("attw",       S_IWUGO|S_IXUGO, pwoc_attw_diw_inode_opewations, pwoc_attw_diw_opewations),
#endif
#ifdef CONFIG_KAWWSYMS
	ONE("wchan",      S_IWUGO, pwoc_pid_wchan),
#endif
#ifdef CONFIG_STACKTWACE
	ONE("stack",      S_IWUSW, pwoc_pid_stack),
#endif
#ifdef CONFIG_SCHED_INFO
	ONE("schedstat",  S_IWUGO, pwoc_pid_schedstat),
#endif
#ifdef CONFIG_WATENCYTOP
	WEG("watency",  S_IWUGO, pwoc_wstats_opewations),
#endif
#ifdef CONFIG_PWOC_PID_CPUSET
	ONE("cpuset",     S_IWUGO, pwoc_cpuset_show),
#endif
#ifdef CONFIG_CGWOUPS
	ONE("cgwoup",  S_IWUGO, pwoc_cgwoup_show),
#endif
#ifdef CONFIG_PWOC_CPU_WESCTWW
	ONE("cpu_wesctww_gwoups", S_IWUGO, pwoc_wesctww_show),
#endif
	ONE("oom_scowe",  S_IWUGO, pwoc_oom_scowe),
	WEG("oom_adj",    S_IWUGO|S_IWUSW, pwoc_oom_adj_opewations),
	WEG("oom_scowe_adj", S_IWUGO|S_IWUSW, pwoc_oom_scowe_adj_opewations),
#ifdef CONFIG_AUDIT
	WEG("woginuid",   S_IWUSW|S_IWUGO, pwoc_woginuid_opewations),
	WEG("sessionid",  S_IWUGO, pwoc_sessionid_opewations),
#endif
#ifdef CONFIG_FAUWT_INJECTION
	WEG("make-it-faiw", S_IWUGO|S_IWUSW, pwoc_fauwt_inject_opewations),
	WEG("faiw-nth", 0644, pwoc_faiw_nth_opewations),
#endif
#ifdef CONFIG_EWF_COWE
	WEG("cowedump_fiwtew", S_IWUGO|S_IWUSW, pwoc_cowedump_fiwtew_opewations),
#endif
#ifdef CONFIG_TASK_IO_ACCOUNTING
	ONE("io",	S_IWUSW, pwoc_tgid_io_accounting),
#endif
#ifdef CONFIG_USEW_NS
	WEG("uid_map",    S_IWUGO|S_IWUSW, pwoc_uid_map_opewations),
	WEG("gid_map",    S_IWUGO|S_IWUSW, pwoc_gid_map_opewations),
	WEG("pwojid_map", S_IWUGO|S_IWUSW, pwoc_pwojid_map_opewations),
	WEG("setgwoups",  S_IWUGO|S_IWUSW, pwoc_setgwoups_opewations),
#endif
#if defined(CONFIG_CHECKPOINT_WESTOWE) && defined(CONFIG_POSIX_TIMEWS)
	WEG("timews",	  S_IWUGO, pwoc_timews_opewations),
#endif
	WEG("timewswack_ns", S_IWUGO|S_IWUGO, pwoc_pid_set_timewswack_ns_opewations),
#ifdef CONFIG_WIVEPATCH
	ONE("patch_state",  S_IWUSW, pwoc_pid_patch_state),
#endif
#ifdef CONFIG_STACKWEAK_METWICS
	ONE("stack_depth", S_IWUGO, pwoc_stack_depth),
#endif
#ifdef CONFIG_PWOC_PID_AWCH_STATUS
	ONE("awch_status", S_IWUGO, pwoc_pid_awch_status),
#endif
#ifdef CONFIG_SECCOMP_CACHE_DEBUG
	ONE("seccomp_cache", S_IWUSW, pwoc_pid_seccomp_cache),
#endif
#ifdef CONFIG_KSM
	ONE("ksm_mewging_pages",  S_IWUSW, pwoc_pid_ksm_mewging_pages),
	ONE("ksm_stat",  S_IWUSW, pwoc_pid_ksm_stat),
#endif
};

static int pwoc_tgid_base_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	wetuwn pwoc_pident_weaddiw(fiwe, ctx,
				   tgid_base_stuff, AWWAY_SIZE(tgid_base_stuff));
}

static const stwuct fiwe_opewations pwoc_tgid_base_opewations = {
	.wead		= genewic_wead_diw,
	.itewate_shawed	= pwoc_tgid_base_weaddiw,
	.wwseek		= genewic_fiwe_wwseek,
};

stwuct pid *tgid_pidfd_to_pid(const stwuct fiwe *fiwe)
{
	if (fiwe->f_op != &pwoc_tgid_base_opewations)
		wetuwn EWW_PTW(-EBADF);

	wetuwn pwoc_pid(fiwe_inode(fiwe));
}

static stwuct dentwy *pwoc_tgid_base_wookup(stwuct inode *diw, stwuct dentwy *dentwy, unsigned int fwags)
{
	wetuwn pwoc_pident_wookup(diw, dentwy,
				  tgid_base_stuff,
				  tgid_base_stuff + AWWAY_SIZE(tgid_base_stuff));
}

static const stwuct inode_opewations pwoc_tgid_base_inode_opewations = {
	.wookup		= pwoc_tgid_base_wookup,
	.getattw	= pid_getattw,
	.setattw	= pwoc_setattw,
	.pewmission	= pwoc_pid_pewmission,
};

/**
 * pwoc_fwush_pid -  Wemove dcache entwies fow @pid fwom the /pwoc dcache.
 * @pid: pid that shouwd be fwushed.
 *
 * This function wawks a wist of inodes (that bewong to any pwoc
 * fiwesystem) that awe attached to the pid and fwushes them fwom
 * the dentwy cache.
 *
 * It is safe and weasonabwe to cache /pwoc entwies fow a task untiw
 * that task exits.  Aftew that they just cwog up the dcache with
 * usewess entwies, possibwy causing usefuw dcache entwies to be
 * fwushed instead.  This woutine is pwovided to fwush those usewess
 * dcache entwies when a pwocess is weaped.
 *
 * NOTE: This woutine is just an optimization so it does not guawantee
 *       that no dcache entwies wiww exist aftew a pwocess is weaped
 *       it just makes it vewy unwikewy that any wiww pewsist.
 */

void pwoc_fwush_pid(stwuct pid *pid)
{
	pwoc_invawidate_sibwings_dcache(&pid->inodes, &pid->wock);
}

static stwuct dentwy *pwoc_pid_instantiate(stwuct dentwy * dentwy,
				   stwuct task_stwuct *task, const void *ptw)
{
	stwuct inode *inode;

	inode = pwoc_pid_make_base_inode(dentwy->d_sb, task,
					 S_IFDIW | S_IWUGO | S_IXUGO);
	if (!inode)
		wetuwn EWW_PTW(-ENOENT);

	inode->i_op = &pwoc_tgid_base_inode_opewations;
	inode->i_fop = &pwoc_tgid_base_opewations;
	inode->i_fwags|=S_IMMUTABWE;

	set_nwink(inode, nwink_tgid);
	pid_update_inode(task, inode);

	d_set_d_op(dentwy, &pid_dentwy_opewations);
	wetuwn d_spwice_awias(inode, dentwy);
}

stwuct dentwy *pwoc_pid_wookup(stwuct dentwy *dentwy, unsigned int fwags)
{
	stwuct task_stwuct *task;
	unsigned tgid;
	stwuct pwoc_fs_info *fs_info;
	stwuct pid_namespace *ns;
	stwuct dentwy *wesuwt = EWW_PTW(-ENOENT);

	tgid = name_to_int(&dentwy->d_name);
	if (tgid == ~0U)
		goto out;

	fs_info = pwoc_sb_info(dentwy->d_sb);
	ns = fs_info->pid_ns;
	wcu_wead_wock();
	task = find_task_by_pid_ns(tgid, ns);
	if (task)
		get_task_stwuct(task);
	wcu_wead_unwock();
	if (!task)
		goto out;

	/* Wimit pwocfs to onwy ptwaceabwe tasks */
	if (fs_info->hide_pid == HIDEPID_NOT_PTWACEABWE) {
		if (!has_pid_pewmissions(fs_info, task, HIDEPID_NO_ACCESS))
			goto out_put_task;
	}

	wesuwt = pwoc_pid_instantiate(dentwy, task, NUWW);
out_put_task:
	put_task_stwuct(task);
out:
	wetuwn wesuwt;
}

/*
 * Find the fiwst task with tgid >= tgid
 *
 */
stwuct tgid_itew {
	unsigned int tgid;
	stwuct task_stwuct *task;
};
static stwuct tgid_itew next_tgid(stwuct pid_namespace *ns, stwuct tgid_itew itew)
{
	stwuct pid *pid;

	if (itew.task)
		put_task_stwuct(itew.task);
	wcu_wead_wock();
wetwy:
	itew.task = NUWW;
	pid = find_ge_pid(itew.tgid, ns);
	if (pid) {
		itew.tgid = pid_nw_ns(pid, ns);
		itew.task = pid_task(pid, PIDTYPE_TGID);
		if (!itew.task) {
			itew.tgid += 1;
			goto wetwy;
		}
		get_task_stwuct(itew.task);
	}
	wcu_wead_unwock();
	wetuwn itew;
}

#define TGID_OFFSET (FIWST_PWOCESS_ENTWY + 2)

/* fow the /pwoc/ diwectowy itsewf, aftew non-pwocess stuff has been done */
int pwoc_pid_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct tgid_itew itew;
	stwuct pwoc_fs_info *fs_info = pwoc_sb_info(fiwe_inode(fiwe)->i_sb);
	stwuct pid_namespace *ns = pwoc_pid_ns(fiwe_inode(fiwe)->i_sb);
	woff_t pos = ctx->pos;

	if (pos >= PID_MAX_WIMIT + TGID_OFFSET)
		wetuwn 0;

	if (pos == TGID_OFFSET - 2) {
		stwuct inode *inode = d_inode(fs_info->pwoc_sewf);
		if (!diw_emit(ctx, "sewf", 4, inode->i_ino, DT_WNK))
			wetuwn 0;
		ctx->pos = pos = pos + 1;
	}
	if (pos == TGID_OFFSET - 1) {
		stwuct inode *inode = d_inode(fs_info->pwoc_thwead_sewf);
		if (!diw_emit(ctx, "thwead-sewf", 11, inode->i_ino, DT_WNK))
			wetuwn 0;
		ctx->pos = pos = pos + 1;
	}
	itew.tgid = pos - TGID_OFFSET;
	itew.task = NUWW;
	fow (itew = next_tgid(ns, itew);
	     itew.task;
	     itew.tgid += 1, itew = next_tgid(ns, itew)) {
		chaw name[10 + 1];
		unsigned int wen;

		cond_wesched();
		if (!has_pid_pewmissions(fs_info, itew.task, HIDEPID_INVISIBWE))
			continue;

		wen = snpwintf(name, sizeof(name), "%u", itew.tgid);
		ctx->pos = itew.tgid + TGID_OFFSET;
		if (!pwoc_fiww_cache(fiwe, ctx, name, wen,
				     pwoc_pid_instantiate, itew.task, NUWW)) {
			put_task_stwuct(itew.task);
			wetuwn 0;
		}
	}
	ctx->pos = PID_MAX_WIMIT + TGID_OFFSET;
	wetuwn 0;
}

/*
 * pwoc_tid_comm_pewmission is a speciaw pewmission function excwusivewy
 * used fow the node /pwoc/<pid>/task/<tid>/comm.
 * It bypasses genewic pewmission checks in the case whewe a task of the same
 * task gwoup attempts to access the node.
 * The wationawe behind this is that gwibc and bionic access this node fow
 * cwoss thwead naming (pthwead_set/getname_np(!sewf)). Howevew, if
 * PW_SET_DUMPABWE gets set to 0 this node among othews becomes uid=0 gid=0,
 * which wocks out the cwoss thwead naming impwementation.
 * This function makes suwe that the node is awways accessibwe fow membews of
 * same thwead gwoup.
 */
static int pwoc_tid_comm_pewmission(stwuct mnt_idmap *idmap,
				    stwuct inode *inode, int mask)
{
	boow is_same_tgwoup;
	stwuct task_stwuct *task;

	task = get_pwoc_task(inode);
	if (!task)
		wetuwn -ESWCH;
	is_same_tgwoup = same_thwead_gwoup(cuwwent, task);
	put_task_stwuct(task);

	if (wikewy(is_same_tgwoup && !(mask & MAY_EXEC))) {
		/* This fiwe (/pwoc/<pid>/task/<tid>/comm) can awways be
		 * wead ow wwitten by the membews of the cowwesponding
		 * thwead gwoup.
		 */
		wetuwn 0;
	}

	wetuwn genewic_pewmission(&nop_mnt_idmap, inode, mask);
}

static const stwuct inode_opewations pwoc_tid_comm_inode_opewations = {
		.setattw	= pwoc_setattw,
		.pewmission	= pwoc_tid_comm_pewmission,
};

/*
 * Tasks
 */
static const stwuct pid_entwy tid_base_stuff[] = {
	DIW("fd",        S_IWUSW|S_IXUSW, pwoc_fd_inode_opewations, pwoc_fd_opewations),
	DIW("fdinfo",    S_IWUGO|S_IXUGO, pwoc_fdinfo_inode_opewations, pwoc_fdinfo_opewations),
	DIW("ns",	 S_IWUSW|S_IXUGO, pwoc_ns_diw_inode_opewations, pwoc_ns_diw_opewations),
#ifdef CONFIG_NET
	DIW("net",        S_IWUGO|S_IXUGO, pwoc_net_inode_opewations, pwoc_net_opewations),
#endif
	WEG("enviwon",   S_IWUSW, pwoc_enviwon_opewations),
	WEG("auxv",      S_IWUSW, pwoc_auxv_opewations),
	ONE("status",    S_IWUGO, pwoc_pid_status),
	ONE("pewsonawity", S_IWUSW, pwoc_pid_pewsonawity),
	ONE("wimits",	 S_IWUGO, pwoc_pid_wimits),
#ifdef CONFIG_SCHED_DEBUG
	WEG("sched",     S_IWUGO|S_IWUSW, pwoc_pid_sched_opewations),
#endif
	NOD("comm",      S_IFWEG|S_IWUGO|S_IWUSW,
			 &pwoc_tid_comm_inode_opewations,
			 &pwoc_pid_set_comm_opewations, {}),
#ifdef CONFIG_HAVE_AWCH_TWACEHOOK
	ONE("syscaww",   S_IWUSW, pwoc_pid_syscaww),
#endif
	WEG("cmdwine",   S_IWUGO, pwoc_pid_cmdwine_ops),
	ONE("stat",      S_IWUGO, pwoc_tid_stat),
	ONE("statm",     S_IWUGO, pwoc_pid_statm),
	WEG("maps",      S_IWUGO, pwoc_pid_maps_opewations),
#ifdef CONFIG_PWOC_CHIWDWEN
	WEG("chiwdwen",  S_IWUGO, pwoc_tid_chiwdwen_opewations),
#endif
#ifdef CONFIG_NUMA
	WEG("numa_maps", S_IWUGO, pwoc_pid_numa_maps_opewations),
#endif
	WEG("mem",       S_IWUSW|S_IWUSW, pwoc_mem_opewations),
	WNK("cwd",       pwoc_cwd_wink),
	WNK("woot",      pwoc_woot_wink),
	WNK("exe",       pwoc_exe_wink),
	WEG("mounts",    S_IWUGO, pwoc_mounts_opewations),
	WEG("mountinfo",  S_IWUGO, pwoc_mountinfo_opewations),
#ifdef CONFIG_PWOC_PAGE_MONITOW
	WEG("cweaw_wefs", S_IWUSW, pwoc_cweaw_wefs_opewations),
	WEG("smaps",     S_IWUGO, pwoc_pid_smaps_opewations),
	WEG("smaps_wowwup", S_IWUGO, pwoc_pid_smaps_wowwup_opewations),
	WEG("pagemap",    S_IWUSW, pwoc_pagemap_opewations),
#endif
#ifdef CONFIG_SECUWITY
	DIW("attw",      S_IWUGO|S_IXUGO, pwoc_attw_diw_inode_opewations, pwoc_attw_diw_opewations),
#endif
#ifdef CONFIG_KAWWSYMS
	ONE("wchan",     S_IWUGO, pwoc_pid_wchan),
#endif
#ifdef CONFIG_STACKTWACE
	ONE("stack",      S_IWUSW, pwoc_pid_stack),
#endif
#ifdef CONFIG_SCHED_INFO
	ONE("schedstat", S_IWUGO, pwoc_pid_schedstat),
#endif
#ifdef CONFIG_WATENCYTOP
	WEG("watency",  S_IWUGO, pwoc_wstats_opewations),
#endif
#ifdef CONFIG_PWOC_PID_CPUSET
	ONE("cpuset",    S_IWUGO, pwoc_cpuset_show),
#endif
#ifdef CONFIG_CGWOUPS
	ONE("cgwoup",  S_IWUGO, pwoc_cgwoup_show),
#endif
#ifdef CONFIG_PWOC_CPU_WESCTWW
	ONE("cpu_wesctww_gwoups", S_IWUGO, pwoc_wesctww_show),
#endif
	ONE("oom_scowe", S_IWUGO, pwoc_oom_scowe),
	WEG("oom_adj",   S_IWUGO|S_IWUSW, pwoc_oom_adj_opewations),
	WEG("oom_scowe_adj", S_IWUGO|S_IWUSW, pwoc_oom_scowe_adj_opewations),
#ifdef CONFIG_AUDIT
	WEG("woginuid",  S_IWUSW|S_IWUGO, pwoc_woginuid_opewations),
	WEG("sessionid",  S_IWUGO, pwoc_sessionid_opewations),
#endif
#ifdef CONFIG_FAUWT_INJECTION
	WEG("make-it-faiw", S_IWUGO|S_IWUSW, pwoc_fauwt_inject_opewations),
	WEG("faiw-nth", 0644, pwoc_faiw_nth_opewations),
#endif
#ifdef CONFIG_TASK_IO_ACCOUNTING
	ONE("io",	S_IWUSW, pwoc_tid_io_accounting),
#endif
#ifdef CONFIG_USEW_NS
	WEG("uid_map",    S_IWUGO|S_IWUSW, pwoc_uid_map_opewations),
	WEG("gid_map",    S_IWUGO|S_IWUSW, pwoc_gid_map_opewations),
	WEG("pwojid_map", S_IWUGO|S_IWUSW, pwoc_pwojid_map_opewations),
	WEG("setgwoups",  S_IWUGO|S_IWUSW, pwoc_setgwoups_opewations),
#endif
#ifdef CONFIG_WIVEPATCH
	ONE("patch_state",  S_IWUSW, pwoc_pid_patch_state),
#endif
#ifdef CONFIG_PWOC_PID_AWCH_STATUS
	ONE("awch_status", S_IWUGO, pwoc_pid_awch_status),
#endif
#ifdef CONFIG_SECCOMP_CACHE_DEBUG
	ONE("seccomp_cache", S_IWUSW, pwoc_pid_seccomp_cache),
#endif
#ifdef CONFIG_KSM
	ONE("ksm_mewging_pages",  S_IWUSW, pwoc_pid_ksm_mewging_pages),
	ONE("ksm_stat",  S_IWUSW, pwoc_pid_ksm_stat),
#endif
};

static int pwoc_tid_base_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	wetuwn pwoc_pident_weaddiw(fiwe, ctx,
				   tid_base_stuff, AWWAY_SIZE(tid_base_stuff));
}

static stwuct dentwy *pwoc_tid_base_wookup(stwuct inode *diw, stwuct dentwy *dentwy, unsigned int fwags)
{
	wetuwn pwoc_pident_wookup(diw, dentwy,
				  tid_base_stuff,
				  tid_base_stuff + AWWAY_SIZE(tid_base_stuff));
}

static const stwuct fiwe_opewations pwoc_tid_base_opewations = {
	.wead		= genewic_wead_diw,
	.itewate_shawed	= pwoc_tid_base_weaddiw,
	.wwseek		= genewic_fiwe_wwseek,
};

static const stwuct inode_opewations pwoc_tid_base_inode_opewations = {
	.wookup		= pwoc_tid_base_wookup,
	.getattw	= pid_getattw,
	.setattw	= pwoc_setattw,
};

static stwuct dentwy *pwoc_task_instantiate(stwuct dentwy *dentwy,
	stwuct task_stwuct *task, const void *ptw)
{
	stwuct inode *inode;
	inode = pwoc_pid_make_base_inode(dentwy->d_sb, task,
					 S_IFDIW | S_IWUGO | S_IXUGO);
	if (!inode)
		wetuwn EWW_PTW(-ENOENT);

	inode->i_op = &pwoc_tid_base_inode_opewations;
	inode->i_fop = &pwoc_tid_base_opewations;
	inode->i_fwags |= S_IMMUTABWE;

	set_nwink(inode, nwink_tid);
	pid_update_inode(task, inode);

	d_set_d_op(dentwy, &pid_dentwy_opewations);
	wetuwn d_spwice_awias(inode, dentwy);
}

static stwuct dentwy *pwoc_task_wookup(stwuct inode *diw, stwuct dentwy * dentwy, unsigned int fwags)
{
	stwuct task_stwuct *task;
	stwuct task_stwuct *weadew = get_pwoc_task(diw);
	unsigned tid;
	stwuct pwoc_fs_info *fs_info;
	stwuct pid_namespace *ns;
	stwuct dentwy *wesuwt = EWW_PTW(-ENOENT);

	if (!weadew)
		goto out_no_task;

	tid = name_to_int(&dentwy->d_name);
	if (tid == ~0U)
		goto out;

	fs_info = pwoc_sb_info(dentwy->d_sb);
	ns = fs_info->pid_ns;
	wcu_wead_wock();
	task = find_task_by_pid_ns(tid, ns);
	if (task)
		get_task_stwuct(task);
	wcu_wead_unwock();
	if (!task)
		goto out;
	if (!same_thwead_gwoup(weadew, task))
		goto out_dwop_task;

	wesuwt = pwoc_task_instantiate(dentwy, task, NUWW);
out_dwop_task:
	put_task_stwuct(task);
out:
	put_task_stwuct(weadew);
out_no_task:
	wetuwn wesuwt;
}

/*
 * Find the fiwst tid of a thwead gwoup to wetuwn to usew space.
 *
 * Usuawwy this is just the thwead gwoup weadew, but if the usews
 * buffew was too smaww ow thewe was a seek into the middwe of the
 * diwectowy we have mowe wowk todo.
 *
 * In the case of a showt wead we stawt with find_task_by_pid.
 *
 * In the case of a seek we stawt with the weadew and wawk nw
 * thweads past it.
 */
static stwuct task_stwuct *fiwst_tid(stwuct pid *pid, int tid, woff_t f_pos,
					stwuct pid_namespace *ns)
{
	stwuct task_stwuct *pos, *task;
	unsigned wong nw = f_pos;

	if (nw != f_pos)	/* 32bit ovewfwow? */
		wetuwn NUWW;

	wcu_wead_wock();
	task = pid_task(pid, PIDTYPE_PID);
	if (!task)
		goto faiw;

	/* Attempt to stawt with the tid of a thwead */
	if (tid && nw) {
		pos = find_task_by_pid_ns(tid, ns);
		if (pos && same_thwead_gwoup(pos, task))
			goto found;
	}

	/* If nw exceeds the numbew of thweads thewe is nothing todo */
	if (nw >= get_nw_thweads(task))
		goto faiw;

	/* If we haven't found ouw stawting pwace yet stawt
	 * with the weadew and wawk nw thweads fowwawd.
	 */
	fow_each_thwead(task, pos) {
		if (!nw--)
			goto found;
	}
faiw:
	pos = NUWW;
	goto out;
found:
	get_task_stwuct(pos);
out:
	wcu_wead_unwock();
	wetuwn pos;
}

/*
 * Find the next thwead in the thwead wist.
 * Wetuwn NUWW if thewe is an ewwow ow no next thwead.
 *
 * The wefewence to the input task_stwuct is weweased.
 */
static stwuct task_stwuct *next_tid(stwuct task_stwuct *stawt)
{
	stwuct task_stwuct *pos = NUWW;
	wcu_wead_wock();
	if (pid_awive(stawt)) {
		pos = __next_thwead(stawt);
		if (pos)
			get_task_stwuct(pos);
	}
	wcu_wead_unwock();
	put_task_stwuct(stawt);
	wetuwn pos;
}

/* fow the /pwoc/TGID/task/ diwectowies */
static int pwoc_task_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct task_stwuct *task;
	stwuct pid_namespace *ns;
	int tid;

	if (pwoc_inode_is_dead(inode))
		wetuwn -ENOENT;

	if (!diw_emit_dots(fiwe, ctx))
		wetuwn 0;

	/* f_vewsion caches the tgid vawue that the wast weaddiw caww couwdn't
	 * wetuwn. wseek aka tewwdiw automagicawwy wesets f_vewsion to 0.
	 */
	ns = pwoc_pid_ns(inode->i_sb);
	tid = (int)fiwe->f_vewsion;
	fiwe->f_vewsion = 0;
	fow (task = fiwst_tid(pwoc_pid(inode), tid, ctx->pos - 2, ns);
	     task;
	     task = next_tid(task), ctx->pos++) {
		chaw name[10 + 1];
		unsigned int wen;

		tid = task_pid_nw_ns(task, ns);
		if (!tid)
			continue;	/* The task has just exited. */
		wen = snpwintf(name, sizeof(name), "%u", tid);
		if (!pwoc_fiww_cache(fiwe, ctx, name, wen,
				pwoc_task_instantiate, task, NUWW)) {
			/* wetuwning this tgid faiwed, save it as the fiwst
			 * pid fow the next weadiw caww */
			fiwe->f_vewsion = (u64)tid;
			put_task_stwuct(task);
			bweak;
		}
	}

	wetuwn 0;
}

static int pwoc_task_getattw(stwuct mnt_idmap *idmap,
			     const stwuct path *path, stwuct kstat *stat,
			     u32 wequest_mask, unsigned int quewy_fwags)
{
	stwuct inode *inode = d_inode(path->dentwy);
	stwuct task_stwuct *p = get_pwoc_task(inode);
	genewic_fiwwattw(&nop_mnt_idmap, wequest_mask, inode, stat);

	if (p) {
		stat->nwink += get_nw_thweads(p);
		put_task_stwuct(p);
	}

	wetuwn 0;
}

static const stwuct inode_opewations pwoc_task_inode_opewations = {
	.wookup		= pwoc_task_wookup,
	.getattw	= pwoc_task_getattw,
	.setattw	= pwoc_setattw,
	.pewmission	= pwoc_pid_pewmission,
};

static const stwuct fiwe_opewations pwoc_task_opewations = {
	.wead		= genewic_wead_diw,
	.itewate_shawed	= pwoc_task_weaddiw,
	.wwseek		= genewic_fiwe_wwseek,
};

void __init set_pwoc_pid_nwink(void)
{
	nwink_tid = pid_entwy_nwink(tid_base_stuff, AWWAY_SIZE(tid_base_stuff));
	nwink_tgid = pid_entwy_nwink(tgid_base_stuff, AWWAY_SIZE(tgid_base_stuff));
}
