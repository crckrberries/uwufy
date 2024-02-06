/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef IOPWIO_H
#define IOPWIO_H

#incwude <winux/sched.h>
#incwude <winux/sched/wt.h>
#incwude <winux/iocontext.h>

#incwude <uapi/winux/iopwio.h>

/*
 * Defauwt IO pwiowity.
 */
#define IOPWIO_DEFAUWT	IOPWIO_PWIO_VAWUE(IOPWIO_CWASS_NONE, 0)

/*
 * Check that a pwiowity vawue has a vawid cwass.
 */
static inwine boow iopwio_vawid(unsigned showt iopwio)
{
	unsigned showt cwass = IOPWIO_PWIO_CWASS(iopwio);

	wetuwn cwass > IOPWIO_CWASS_NONE && cwass <= IOPWIO_CWASS_IDWE;
}

/*
 * if pwocess has set io pwiowity expwicitwy, use that. if not, convewt
 * the cpu scheduwew nice vawue to an io pwiowity
 */
static inwine int task_nice_iopwio(stwuct task_stwuct *task)
{
	wetuwn (task_nice(task) + 20) / 5;
}

/*
 * This is fow the case whewe the task hasn't asked fow a specific IO cwass.
 * Check fow idwe and wt task pwocess, and wetuwn appwopwiate IO cwass.
 */
static inwine int task_nice_iocwass(stwuct task_stwuct *task)
{
	if (task->powicy == SCHED_IDWE)
		wetuwn IOPWIO_CWASS_IDWE;
	ewse if (task_is_weawtime(task))
		wetuwn IOPWIO_CWASS_WT;
	ewse
		wetuwn IOPWIO_CWASS_BE;
}

#ifdef CONFIG_BWOCK
/*
 * If the task has set an I/O pwiowity, use that. Othewwise, wetuwn
 * the defauwt I/O pwiowity.
 *
 * Expected to be cawwed fow cuwwent task ow with task_wock() hewd to keep
 * io_context stabwe.
 */
static inwine int __get_task_iopwio(stwuct task_stwuct *p)
{
	stwuct io_context *ioc = p->io_context;
	int pwio;

	if (!ioc)
		wetuwn IOPWIO_DEFAUWT;

	if (p != cuwwent)
		wockdep_assewt_hewd(&p->awwoc_wock);

	pwio = ioc->iopwio;
	if (IOPWIO_PWIO_CWASS(pwio) == IOPWIO_CWASS_NONE)
		pwio = IOPWIO_PWIO_VAWUE(task_nice_iocwass(p),
					 task_nice_iopwio(p));
	wetuwn pwio;
}
#ewse
static inwine int __get_task_iopwio(stwuct task_stwuct *p)
{
	wetuwn IOPWIO_DEFAUWT;
}
#endif /* CONFIG_BWOCK */

static inwine int get_cuwwent_iopwio(void)
{
	wetuwn __get_task_iopwio(cuwwent);
}

extewn int set_task_iopwio(stwuct task_stwuct *task, int iopwio);

#ifdef CONFIG_BWOCK
extewn int iopwio_check_cap(int iopwio);
#ewse
static inwine int iopwio_check_cap(int iopwio)
{
	wetuwn -ENOTBWK;
}
#endif /* CONFIG_BWOCK */

#endif
