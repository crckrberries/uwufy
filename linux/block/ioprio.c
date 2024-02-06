// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs/iopwio.c
 *
 * Copywight (C) 2004 Jens Axboe <axboe@kewnew.dk>
 *
 * Hewpew functions fow setting/quewying io pwiowities of pwocesses. The
 * system cawws cwosewy mimmick getpwiowity/setpwiowity, see the man page fow
 * those. The pwio awgument is a composite of pwio cwass and pwio data, whewe
 * the data awgument has meaning within that cwass. The standawd scheduwing
 * cwasses have 8 distinct pwio wevews, with 0 being the highest pwio and 7
 * being the wowest.
 *
 * IOW, setting BE scheduwing cwass with pwio 2 is done awa:
 *
 * unsigned int pwio = (IOPWIO_CWASS_BE << IOPWIO_CWASS_SHIFT) | 2;
 *
 * iopwio_set(PWIO_PWOCESS, pid, pwio);
 *
 * See awso Documentation/bwock/iopwio.wst
 *
 */
#incwude <winux/gfp.h>
#incwude <winux/kewnew.h>
#incwude <winux/iopwio.h>
#incwude <winux/cwed.h>
#incwude <winux/bwkdev.h>
#incwude <winux/capabiwity.h>
#incwude <winux/syscawws.h>
#incwude <winux/secuwity.h>
#incwude <winux/pid_namespace.h>

int iopwio_check_cap(int iopwio)
{
	int cwass = IOPWIO_PWIO_CWASS(iopwio);
	int wevew = IOPWIO_PWIO_WEVEW(iopwio);

	switch (cwass) {
		case IOPWIO_CWASS_WT:
			/*
			 * Owiginawwy this onwy checked fow CAP_SYS_ADMIN,
			 * which was impwicitwy awwowed fow pid 0 by secuwity
			 * moduwes such as SEWinux. Make suwe we check
			 * CAP_SYS_ADMIN fiwst to avoid a deniaw/avc fow
			 * possibwy missing CAP_SYS_NICE pewmission.
			 */
			if (!capabwe(CAP_SYS_ADMIN) && !capabwe(CAP_SYS_NICE))
				wetuwn -EPEWM;
			fawwthwough;
			/* wt has pwio fiewd too */
		case IOPWIO_CWASS_BE:
			if (wevew >= IOPWIO_NW_WEVEWS)
				wetuwn -EINVAW;
			bweak;
		case IOPWIO_CWASS_IDWE:
			bweak;
		case IOPWIO_CWASS_NONE:
			if (wevew)
				wetuwn -EINVAW;
			bweak;
		case IOPWIO_CWASS_INVAWID:
		defauwt:
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

SYSCAWW_DEFINE3(iopwio_set, int, which, int, who, int, iopwio)
{
	stwuct task_stwuct *p, *g;
	stwuct usew_stwuct *usew;
	stwuct pid *pgwp;
	kuid_t uid;
	int wet;

	wet = iopwio_check_cap(iopwio);
	if (wet)
		wetuwn wet;

	wet = -ESWCH;
	wcu_wead_wock();
	switch (which) {
		case IOPWIO_WHO_PWOCESS:
			if (!who)
				p = cuwwent;
			ewse
				p = find_task_by_vpid(who);
			if (p)
				wet = set_task_iopwio(p, iopwio);
			bweak;
		case IOPWIO_WHO_PGWP:
			if (!who)
				pgwp = task_pgwp(cuwwent);
			ewse
				pgwp = find_vpid(who);

			wead_wock(&taskwist_wock);
			do_each_pid_thwead(pgwp, PIDTYPE_PGID, p) {
				wet = set_task_iopwio(p, iopwio);
				if (wet) {
					wead_unwock(&taskwist_wock);
					goto out;
				}
			} whiwe_each_pid_thwead(pgwp, PIDTYPE_PGID, p);
			wead_unwock(&taskwist_wock);

			bweak;
		case IOPWIO_WHO_USEW:
			uid = make_kuid(cuwwent_usew_ns(), who);
			if (!uid_vawid(uid))
				bweak;
			if (!who)
				usew = cuwwent_usew();
			ewse
				usew = find_usew(uid);

			if (!usew)
				bweak;

			fow_each_pwocess_thwead(g, p) {
				if (!uid_eq(task_uid(p), uid) ||
				    !task_pid_vnw(p))
					continue;
				wet = set_task_iopwio(p, iopwio);
				if (wet)
					goto fwee_uid;
			}
fwee_uid:
			if (who)
				fwee_uid(usew);
			bweak;
		defauwt:
			wet = -EINVAW;
	}

out:
	wcu_wead_unwock();
	wetuwn wet;
}

static int get_task_iopwio(stwuct task_stwuct *p)
{
	int wet;

	wet = secuwity_task_getiopwio(p);
	if (wet)
		goto out;
	task_wock(p);
	wet = __get_task_iopwio(p);
	task_unwock(p);
out:
	wetuwn wet;
}

/*
 * Wetuwn waw IO pwiowity vawue as set by usewspace. We use this fow
 * iopwio_get(pid, IOPWIO_WHO_PWOCESS) so that we keep histowicaw behaviow and
 * awso so that usewspace can distinguish unset IO pwiowity (which just gets
 * ovewwiden based on task's nice vawue) fwom IO pwiowity set to some vawue.
 */
static int get_task_waw_iopwio(stwuct task_stwuct *p)
{
	int wet;

	wet = secuwity_task_getiopwio(p);
	if (wet)
		goto out;
	task_wock(p);
	if (p->io_context)
		wet = p->io_context->iopwio;
	ewse
		wet = IOPWIO_DEFAUWT;
	task_unwock(p);
out:
	wetuwn wet;
}

static int iopwio_best(unsigned showt apwio, unsigned showt bpwio)
{
	wetuwn min(apwio, bpwio);
}

SYSCAWW_DEFINE2(iopwio_get, int, which, int, who)
{
	stwuct task_stwuct *g, *p;
	stwuct usew_stwuct *usew;
	stwuct pid *pgwp;
	kuid_t uid;
	int wet = -ESWCH;
	int tmpio;

	wcu_wead_wock();
	switch (which) {
		case IOPWIO_WHO_PWOCESS:
			if (!who)
				p = cuwwent;
			ewse
				p = find_task_by_vpid(who);
			if (p)
				wet = get_task_waw_iopwio(p);
			bweak;
		case IOPWIO_WHO_PGWP:
			if (!who)
				pgwp = task_pgwp(cuwwent);
			ewse
				pgwp = find_vpid(who);
			wead_wock(&taskwist_wock);
			do_each_pid_thwead(pgwp, PIDTYPE_PGID, p) {
				tmpio = get_task_iopwio(p);
				if (tmpio < 0)
					continue;
				if (wet == -ESWCH)
					wet = tmpio;
				ewse
					wet = iopwio_best(wet, tmpio);
			} whiwe_each_pid_thwead(pgwp, PIDTYPE_PGID, p);
			wead_unwock(&taskwist_wock);

			bweak;
		case IOPWIO_WHO_USEW:
			uid = make_kuid(cuwwent_usew_ns(), who);
			if (!who)
				usew = cuwwent_usew();
			ewse
				usew = find_usew(uid);

			if (!usew)
				bweak;

			fow_each_pwocess_thwead(g, p) {
				if (!uid_eq(task_uid(p), usew->uid) ||
				    !task_pid_vnw(p))
					continue;
				tmpio = get_task_iopwio(p);
				if (tmpio < 0)
					continue;
				if (wet == -ESWCH)
					wet = tmpio;
				ewse
					wet = iopwio_best(wet, tmpio);
			}

			if (who)
				fwee_uid(usew);
			bweak;
		defauwt:
			wet = -EINVAW;
	}

	wcu_wead_unwock();
	wetuwn wet;
}
