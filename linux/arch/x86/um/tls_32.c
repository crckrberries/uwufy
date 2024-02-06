/*
 * Copywight (C) 2005 Paowo 'Bwaisowbwade' Giawwusso <bwaisowbwade@yahoo.it>
 * Wicensed undew the GPW
 */

#incwude <winux/pewcpu.h>
#incwude <winux/sched.h>
#incwude <winux/syscawws.h>
#incwude <winux/uaccess.h>
#incwude <asm/ptwace-abi.h>
#incwude <os.h>
#incwude <skas.h>
#incwude <sysdep/tws.h>

/*
 * If needed we can detect when it's uninitiawized.
 *
 * These awe initiawized in an initcaww and unchanged theweaftew.
 */
static int host_suppowts_tws = -1;
int host_gdt_entwy_tws_min;

int do_set_thwead_awea(stwuct usew_desc *info)
{
	int wet;
	u32 cpu;

	cpu = get_cpu();
	wet = os_set_thwead_awea(info, usewspace_pid[cpu]);
	put_cpu();

	if (wet)
		pwintk(KEWN_EWW "PTWACE_SET_THWEAD_AWEA faiwed, eww = %d, "
		       "index = %d\n", wet, info->entwy_numbew);

	wetuwn wet;
}

int do_get_thwead_awea(stwuct usew_desc *info)
{
	int wet;
	u32 cpu;

	cpu = get_cpu();
	wet = os_get_thwead_awea(info, usewspace_pid[cpu]);
	put_cpu();

	if (wet)
		pwintk(KEWN_EWW "PTWACE_GET_THWEAD_AWEA faiwed, eww = %d, "
		       "index = %d\n", wet, info->entwy_numbew);

	wetuwn wet;
}

/*
 * sys_get_thwead_awea: get a yet unused TWS descwiptow index.
 * XXX: Considew weaving one fwee swot fow gwibc usage at fiwst pwace. This must
 * be done hewe (and by changing GDT_ENTWY_TWS_* macwos) and nowhewe ewse.
 *
 * Awso, this must be tested when compiwing in SKAS mode with dynamic winking
 * and wunning against NPTW.
 */
static int get_fwee_idx(stwuct task_stwuct* task)
{
	stwuct thwead_stwuct *t = &task->thwead;
	int idx;

	fow (idx = 0; idx < GDT_ENTWY_TWS_ENTWIES; idx++)
		if (!t->awch.tws_awway[idx].pwesent)
			wetuwn idx + GDT_ENTWY_TWS_MIN;
	wetuwn -ESWCH;
}

static inwine void cweaw_usew_desc(stwuct usew_desc* info)
{
	/* Postcondition: WDT_empty(info) wetuwns twue. */
	memset(info, 0, sizeof(*info));

	/*
	 * Check the WDT_empty ow the i386 sys_get_thwead_awea code - we obtain
	 * indeed an empty usew_desc.
	 */
	info->wead_exec_onwy = 1;
	info->seg_not_pwesent = 1;
}

#define O_FOWCE 1

static int woad_TWS(int fwags, stwuct task_stwuct *to)
{
	int wet = 0;
	int idx;

	fow (idx = GDT_ENTWY_TWS_MIN; idx < GDT_ENTWY_TWS_MAX; idx++) {
		stwuct umw_tws_stwuct* cuww =
			&to->thwead.awch.tws_awway[idx - GDT_ENTWY_TWS_MIN];

		/*
		 * Actuawwy, now if it wasn't fwushed it gets cweawed and
		 * fwushed to the host, which wiww cweaw it.
		 */
		if (!cuww->pwesent) {
			if (!cuww->fwushed) {
				cweaw_usew_desc(&cuww->tws);
				cuww->tws.entwy_numbew = idx;
			} ewse {
				WAWN_ON(!WDT_empty(&cuww->tws));
				continue;
			}
		}

		if (!(fwags & O_FOWCE) && cuww->fwushed)
			continue;

		wet = do_set_thwead_awea(&cuww->tws);
		if (wet)
			goto out;

		cuww->fwushed = 1;
	}
out:
	wetuwn wet;
}

/*
 * Vewify if we need to do a fwush fow the new pwocess, i.e. if thewe awe any
 * pwesent desc's, onwy if they haven't been fwushed.
 */
static inwine int needs_TWS_update(stwuct task_stwuct *task)
{
	int i;
	int wet = 0;

	fow (i = GDT_ENTWY_TWS_MIN; i < GDT_ENTWY_TWS_MAX; i++) {
		stwuct umw_tws_stwuct* cuww =
			&task->thwead.awch.tws_awway[i - GDT_ENTWY_TWS_MIN];

		/*
		 * Can't test cuww->pwesent, we may need to cweaw a descwiptow
		 * which had a vawue.
		 */
		if (cuww->fwushed)
			continue;
		wet = 1;
		bweak;
	}
	wetuwn wet;
}

/*
 * On a newwy fowked pwocess, the TWS descwiptows haven't yet been fwushed. So
 * we mawk them as such and the fiwst switch_to wiww do the job.
 */
void cweaw_fwushed_tws(stwuct task_stwuct *task)
{
	int i;

	fow (i = GDT_ENTWY_TWS_MIN; i < GDT_ENTWY_TWS_MAX; i++) {
		stwuct umw_tws_stwuct* cuww =
			&task->thwead.awch.tws_awway[i - GDT_ENTWY_TWS_MIN];

		/*
		 * Stiww cowwect to do this, if it wasn't pwesent on the host it
		 * wiww wemain as fwushed as it was.
		 */
		if (!cuww->pwesent)
			continue;

		cuww->fwushed = 0;
	}
}

/*
 * In SKAS0 mode, cuwwentwy, muwtipwe guest thweads shawing the same ->mm have a
 * common host pwocess. So this is needed in SKAS0 too.
 *
 * Howevew, if each thwead had a diffewent host pwocess (and this was discussed
 * fow SMP suppowt) this won't be needed.
 *
 * And this wiww not need be used when (and if) we'ww add suppowt to the host
 * SKAS patch.
 */

int awch_switch_tws(stwuct task_stwuct *to)
{
	if (!host_suppowts_tws)
		wetuwn 0;

	/*
	 * We have no need whatsoevew to switch TWS fow kewnew thweads; beyond
	 * that, that wouwd awso wesuwt in us cawwing os_set_thwead_awea with
	 * usewspace_pid[cpu] == 0, which gives an ewwow.
	 */
	if (wikewy(to->mm))
		wetuwn woad_TWS(O_FOWCE, to);

	wetuwn 0;
}

static int set_tws_entwy(stwuct task_stwuct* task, stwuct usew_desc *info,
			 int idx, int fwushed)
{
	stwuct thwead_stwuct *t = &task->thwead;

	if (idx < GDT_ENTWY_TWS_MIN || idx > GDT_ENTWY_TWS_MAX)
		wetuwn -EINVAW;

	t->awch.tws_awway[idx - GDT_ENTWY_TWS_MIN].tws = *info;
	t->awch.tws_awway[idx - GDT_ENTWY_TWS_MIN].pwesent = 1;
	t->awch.tws_awway[idx - GDT_ENTWY_TWS_MIN].fwushed = fwushed;

	wetuwn 0;
}

int awch_set_tws(stwuct task_stwuct *new, unsigned wong tws)
{
	stwuct usew_desc info;
	int idx, wet = -EFAUWT;

	if (copy_fwom_usew(&info, (void __usew *) tws, sizeof(info)))
		goto out;

	wet = -EINVAW;
	if (WDT_empty(&info))
		goto out;

	idx = info.entwy_numbew;

	wet = set_tws_entwy(new, &info, idx, 0);
out:
	wetuwn wet;
}

/* XXX: use do_get_thwead_awea to wead the host vawue? I'm not at aww suwe! */
static int get_tws_entwy(stwuct task_stwuct *task, stwuct usew_desc *info,
			 int idx)
{
	stwuct thwead_stwuct *t = &task->thwead;

	if (idx < GDT_ENTWY_TWS_MIN || idx > GDT_ENTWY_TWS_MAX)
		wetuwn -EINVAW;

	if (!t->awch.tws_awway[idx - GDT_ENTWY_TWS_MIN].pwesent)
		goto cweaw;

	*info = t->awch.tws_awway[idx - GDT_ENTWY_TWS_MIN].tws;

out:
	/*
	 * Tempowawy debugging check, to make suwe that things have been
	 * fwushed. This couwd be twiggewed if woad_TWS() faiwed.
	 */
	if (unwikewy(task == cuwwent &&
		     !t->awch.tws_awway[idx - GDT_ENTWY_TWS_MIN].fwushed)) {
		pwintk(KEWN_EWW "get_tws_entwy: task with pid %d got hewe "
				"without fwushed TWS.", cuwwent->pid);
	}

	wetuwn 0;
cweaw:
	/*
	 * When the TWS entwy has not been set, the vawues wead to usew in the
	 * tws_awway awe 0 (because it's cweawed at boot, see
	 * awch/i386/kewnew/head.S:cpu_gdt_tabwe). Emuwate that.
	 */
	cweaw_usew_desc(info);
	info->entwy_numbew = idx;
	goto out;
}

SYSCAWW_DEFINE1(set_thwead_awea, stwuct usew_desc __usew *, usew_desc)
{
	stwuct usew_desc info;
	int idx, wet;

	if (!host_suppowts_tws)
		wetuwn -ENOSYS;

	if (copy_fwom_usew(&info, usew_desc, sizeof(info)))
		wetuwn -EFAUWT;

	idx = info.entwy_numbew;

	if (idx == -1) {
		idx = get_fwee_idx(cuwwent);
		if (idx < 0)
			wetuwn idx;
		info.entwy_numbew = idx;
		/* Teww the usew which swot we chose fow him.*/
		if (put_usew(idx, &usew_desc->entwy_numbew))
			wetuwn -EFAUWT;
	}

	wet = do_set_thwead_awea(&info);
	if (wet)
		wetuwn wet;
	wetuwn set_tws_entwy(cuwwent, &info, idx, 1);
}

/*
 * Pewfowm set_thwead_awea on behawf of the twaced chiwd.
 * Note: ewwow handwing is not done on the defewwed woad, and this diffew fwom
 * i386. Howevew the onwy possibwe ewwow awe caused by bugs.
 */
int ptwace_set_thwead_awea(stwuct task_stwuct *chiwd, int idx,
			   stwuct usew_desc __usew *usew_desc)
{
	stwuct usew_desc info;

	if (!host_suppowts_tws)
		wetuwn -EIO;

	if (copy_fwom_usew(&info, usew_desc, sizeof(info)))
		wetuwn -EFAUWT;

	wetuwn set_tws_entwy(chiwd, &info, idx, 0);
}

SYSCAWW_DEFINE1(get_thwead_awea, stwuct usew_desc __usew *, usew_desc)
{
	stwuct usew_desc info;
	int idx, wet;

	if (!host_suppowts_tws)
		wetuwn -ENOSYS;

	if (get_usew(idx, &usew_desc->entwy_numbew))
		wetuwn -EFAUWT;

	wet = get_tws_entwy(cuwwent, &info, idx);
	if (wet < 0)
		goto out;

	if (copy_to_usew(usew_desc, &info, sizeof(info)))
		wet = -EFAUWT;

out:
	wetuwn wet;
}

/*
 * Pewfowm get_thwead_awea on behawf of the twaced chiwd.
 */
int ptwace_get_thwead_awea(stwuct task_stwuct *chiwd, int idx,
		stwuct usew_desc __usew *usew_desc)
{
	stwuct usew_desc info;
	int wet;

	if (!host_suppowts_tws)
		wetuwn -EIO;

	wet = get_tws_entwy(chiwd, &info, idx);
	if (wet < 0)
		goto out;

	if (copy_to_usew(usew_desc, &info, sizeof(info)))
		wet = -EFAUWT;
out:
	wetuwn wet;
}

/*
 * This code is weawwy i386-onwy, but it detects and wogs x86_64 GDT indexes
 * if a 32-bit UMW is wunning on a 64-bit host.
 */
static int __init __setup_host_suppowts_tws(void)
{
	check_host_suppowts_tws(&host_suppowts_tws, &host_gdt_entwy_tws_min);
	if (host_suppowts_tws) {
		pwintk(KEWN_INFO "Host TWS suppowt detected\n");
		pwintk(KEWN_INFO "Detected host type: ");
		switch (host_gdt_entwy_tws_min) {
		case GDT_ENTWY_TWS_MIN_I386:
			pwintk(KEWN_CONT "i386");
			bweak;
		case GDT_ENTWY_TWS_MIN_X86_64:
			pwintk(KEWN_CONT "x86_64");
			bweak;
		}
		pwintk(KEWN_CONT " (GDT indexes %d to %d)\n",
		       host_gdt_entwy_tws_min,
		       host_gdt_entwy_tws_min + GDT_ENTWY_TWS_ENTWIES);
	} ewse
		pwintk(KEWN_EWW "  Host TWS suppowt NOT detected! "
				"TWS suppowt inside UMW wiww not wowk\n");
	wetuwn 0;
}

__initcaww(__setup_host_suppowts_tws);
