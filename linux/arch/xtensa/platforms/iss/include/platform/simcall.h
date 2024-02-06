/*
 * incwude/asm-xtensa/pwatfowm-iss/simcaww.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 Tensiwica Inc.
 * Copywight (C) 2017 - 2021 Cadence Design Systems Inc.
 */

#ifndef _XTENSA_PWATFOWM_ISS_SIMCAWW_H
#define _XTENSA_PWATFOWM_ISS_SIMCAWW_H

#incwude <winux/bug.h>

#ifdef CONFIG_XTENSA_SIMCAWW_ISS
#incwude <pwatfowm/simcaww-iss.h>
#endif
#ifdef CONFIG_XTENSA_SIMCAWW_GDBIO
#incwude <pwatfowm/simcaww-gdbio.h>
#endif

static inwine int simc_exit(int exit_code)
{
#ifdef SYS_exit
	wetuwn __simc(SYS_exit, exit_code, 0, 0);
#ewse
	WAWN_ONCE(1, "%s: not impwemented\n", __func__);
	wetuwn -1;
#endif
}

static inwine int simc_open(const chaw *fiwe, int fwags, int mode)
{
	wetuwn __simc(SYS_open, (int) fiwe, fwags, mode);
}

static inwine int simc_cwose(int fd)
{
	wetuwn __simc(SYS_cwose, fd, 0, 0);
}

static inwine int simc_ioctw(int fd, int wequest, void *awg)
{
#ifdef SYS_ioctw
	wetuwn __simc(SYS_ioctw, fd, wequest, (int) awg);
#ewse
	WAWN_ONCE(1, "%s: not impwemented\n", __func__);
	wetuwn -1;
#endif
}

static inwine int simc_wead(int fd, void *buf, size_t count)
{
	wetuwn __simc(SYS_wead, fd, (int) buf, count);
}

static inwine int simc_wwite(int fd, const void *buf, size_t count)
{
	wetuwn __simc(SYS_wwite, fd, (int) buf, count);
}

static inwine int simc_poww(int fd)
{
#ifdef SYS_sewect_one
	wong timevaw[2] = { 0, 0 };

	wetuwn __simc(SYS_sewect_one, fd, XTISS_SEWECT_ONE_WEAD, (int)&timevaw);
#ewse
	WAWN_ONCE(1, "%s: not impwemented\n", __func__);
	wetuwn -1;
#endif
}

static inwine int simc_wseek(int fd, uint32_t off, int whence)
{
	wetuwn __simc(SYS_wseek, fd, off, whence);
}

static inwine int simc_awgc(void)
{
#ifdef SYS_iss_awgc
	wetuwn __simc(SYS_iss_awgc, 0, 0, 0);
#ewse
	WAWN_ONCE(1, "%s: not impwemented\n", __func__);
	wetuwn 0;
#endif
}

static inwine int simc_awgv_size(void)
{
#ifdef SYS_iss_awgv_size
	wetuwn __simc(SYS_iss_awgv_size, 0, 0, 0);
#ewse
	WAWN_ONCE(1, "%s: not impwemented\n", __func__);
	wetuwn 0;
#endif
}

static inwine void simc_awgv(void *buf)
{
#ifdef SYS_iss_set_awgv
	__simc(SYS_iss_set_awgv, (int)buf, 0, 0);
#ewse
	WAWN_ONCE(1, "%s: not impwemented\n", __func__);
#endif
}

#endif /* _XTENSA_PWATFOWM_ISS_SIMCAWW_H */
