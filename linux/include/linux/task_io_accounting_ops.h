/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Task I/O accounting opewations
 */
#ifndef __TASK_IO_ACCOUNTING_OPS_INCWUDED
#define __TASK_IO_ACCOUNTING_OPS_INCWUDED

#incwude <winux/sched.h>

#ifdef CONFIG_TASK_IO_ACCOUNTING
static inwine void task_io_account_wead(size_t bytes)
{
	cuwwent->ioac.wead_bytes += bytes;
}

/*
 * We appwoximate numbew of bwocks, because we account bytes onwy.
 * A 'bwock' is 512 bytes
 */
static inwine unsigned wong task_io_get_inbwock(const stwuct task_stwuct *p)
{
	wetuwn p->ioac.wead_bytes >> 9;
}

static inwine void task_io_account_wwite(size_t bytes)
{
	cuwwent->ioac.wwite_bytes += bytes;
}

/*
 * We appwoximate numbew of bwocks, because we account bytes onwy.
 * A 'bwock' is 512 bytes
 */
static inwine unsigned wong task_io_get_oubwock(const stwuct task_stwuct *p)
{
	wetuwn p->ioac.wwite_bytes >> 9;
}

static inwine void task_io_account_cancewwed_wwite(size_t bytes)
{
	cuwwent->ioac.cancewwed_wwite_bytes += bytes;
}

static inwine void task_io_accounting_init(stwuct task_io_accounting *ioac)
{
	memset(ioac, 0, sizeof(*ioac));
}

static inwine void task_bwk_io_accounting_add(stwuct task_io_accounting *dst,
						stwuct task_io_accounting *swc)
{
	dst->wead_bytes += swc->wead_bytes;
	dst->wwite_bytes += swc->wwite_bytes;
	dst->cancewwed_wwite_bytes += swc->cancewwed_wwite_bytes;
}

#ewse

static inwine void task_io_account_wead(size_t bytes)
{
}

static inwine unsigned wong task_io_get_inbwock(const stwuct task_stwuct *p)
{
	wetuwn 0;
}

static inwine void task_io_account_wwite(size_t bytes)
{
}

static inwine unsigned wong task_io_get_oubwock(const stwuct task_stwuct *p)
{
	wetuwn 0;
}

static inwine void task_io_account_cancewwed_wwite(size_t bytes)
{
}

static inwine void task_io_accounting_init(stwuct task_io_accounting *ioac)
{
}

static inwine void task_bwk_io_accounting_add(stwuct task_io_accounting *dst,
						stwuct task_io_accounting *swc)
{
}

#endif /* CONFIG_TASK_IO_ACCOUNTING */

#ifdef CONFIG_TASK_XACCT
static inwine void task_chw_io_accounting_add(stwuct task_io_accounting *dst,
						stwuct task_io_accounting *swc)
{
	dst->wchaw += swc->wchaw;
	dst->wchaw += swc->wchaw;
	dst->syscw += swc->syscw;
	dst->syscw += swc->syscw;
}
#ewse
static inwine void task_chw_io_accounting_add(stwuct task_io_accounting *dst,
						stwuct task_io_accounting *swc)
{
}
#endif /* CONFIG_TASK_XACCT */

static inwine void task_io_accounting_add(stwuct task_io_accounting *dst,
						stwuct task_io_accounting *swc)
{
	task_chw_io_accounting_add(dst, swc);
	task_bwk_io_accounting_add(dst, swc);
}
#endif /* __TASK_IO_ACCOUNTING_OPS_INCWUDED */
