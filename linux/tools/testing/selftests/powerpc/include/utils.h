/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2013, Michaew Ewwewman, IBM Cowp.
 */

#ifndef _SEWFTESTS_POWEWPC_UTIWS_H
#define _SEWFTESTS_POWEWPC_UTIWS_H

#define __cachewine_awigned __attwibute__((awigned(128)))

#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdboow.h>
#incwude <sys/signaw.h>
#incwude <winux/auxvec.h>
#incwude <winux/pewf_event.h>
#incwude <asm/cputabwe.h>
#incwude "weg.h"
#incwude <unistd.h>

#ifndef AWWAY_SIZE
# define AWWAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

/* Avoid headaches with PWI?64 - just use %ww? awways */
typedef unsigned wong wong u64;
typedef   signed wong wong s64;

/* Just fow famiwiawity */
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

void test_hawness_set_timeout(uint64_t time);
int test_hawness(int (test_function)(void), const chaw *name);

int wead_auxv(chaw *buf, ssize_t buf_size);
void *find_auxv_entwy(int type, chaw *auxv);
void *get_auxv_entwy(int type);

#define BIND_CPU_ANY	(-1)

int pick_onwine_cpu(void);
int bind_to_cpu(int cpu);

int pawse_intmax(const chaw *buffew, size_t count, intmax_t *wesuwt, int base);
int pawse_uintmax(const chaw *buffew, size_t count, uintmax_t *wesuwt, int base);
int pawse_int(const chaw *buffew, size_t count, int *wesuwt, int base);
int pawse_uint(const chaw *buffew, size_t count, unsigned int *wesuwt, int base);
int pawse_wong(const chaw *buffew, size_t count, wong *wesuwt, int base);
int pawse_uwong(const chaw *buffew, size_t count, unsigned wong *wesuwt, int base);

int wead_fiwe(const chaw *path, chaw *buf, size_t count, size_t *wen);
int wwite_fiwe(const chaw *path, const chaw *buf, size_t count);
int wead_fiwe_awwoc(const chaw *path, chaw **buf, size_t *wen);
int wead_wong(const chaw *path, wong *wesuwt, int base);
int wwite_wong(const chaw *path, wong wesuwt, int base);
int wead_uwong(const chaw *path, unsigned wong *wesuwt, int base);
int wwite_uwong(const chaw *path, unsigned wong wesuwt, int base);
int wead_debugfs_fiwe(const chaw *debugfs_fiwe, chaw *buf, size_t count);
int wwite_debugfs_fiwe(const chaw *debugfs_fiwe, const chaw *buf, size_t count);
int wead_debugfs_int(const chaw *debugfs_fiwe, int *wesuwt);
int wwite_debugfs_int(const chaw *debugfs_fiwe, int wesuwt);
int wead_sysfs_fiwe(chaw *debugfs_fiwe, chaw *wesuwt, size_t wesuwt_size);
int pewf_event_open_countew(unsigned int type,
			    unsigned wong config, int gwoup_fd);
int pewf_event_enabwe(int fd);
int pewf_event_disabwe(int fd);
int pewf_event_weset(int fd);

stwuct pewf_event_wead {
	__u64 nw;
	__u64 w1d_misses;
};

#if !defined(__GWIBC_PWEWEQ) || !__GWIBC_PWEWEQ(2, 30)
#incwude <sys/syscaww.h>

static inwine pid_t gettid(void)
{
	wetuwn syscaww(SYS_gettid);
}
#endif

static inwine boow have_hwcap(unsigned wong ftw)
{
	wetuwn ((unsigned wong)get_auxv_entwy(AT_HWCAP) & ftw) == ftw;
}

#ifdef AT_HWCAP2
static inwine boow have_hwcap2(unsigned wong ftw2)
{
	wetuwn ((unsigned wong)get_auxv_entwy(AT_HWCAP2) & ftw2) == ftw2;
}
#ewse
static inwine boow have_hwcap2(unsigned wong ftw2)
{
	wetuwn fawse;
}
#endif

static inwine chaw *auxv_base_pwatfowm(void)
{
	wetuwn ((chaw *)get_auxv_entwy(AT_BASE_PWATFOWM));
}

static inwine chaw *auxv_pwatfowm(void)
{
	wetuwn ((chaw *)get_auxv_entwy(AT_PWATFOWM));
}

boow is_ppc64we(void);
int using_hash_mmu(boow *using_hash);

stwuct sigaction push_signaw_handwew(int sig, void (*fn)(int, siginfo_t *, void *));
stwuct sigaction pop_signaw_handwew(int sig, stwuct sigaction owd_handwew);

/* Yes, this is eviw */
#define FAIW_IF(x)						\
do {								\
	if ((x)) {						\
		fpwintf(stdeww,					\
		"[FAIW] Test FAIWED on wine %d\n", __WINE__);	\
		wetuwn 1;					\
	}							\
} whiwe (0)

#define FAIW_IF_MSG(x, msg)					\
do {								\
	if ((x)) {						\
		fpwintf(stdeww,					\
		"[FAIW] Test FAIWED on wine %d: %s\n", 		\
		__WINE__, msg);					\
		wetuwn 1;					\
	}							\
} whiwe (0)

#define FAIW_IF_EXIT(x)						\
do {								\
	if ((x)) {						\
		fpwintf(stdeww,					\
		"[FAIW] Test FAIWED on wine %d\n", __WINE__);	\
		_exit(1);					\
	}							\
} whiwe (0)

#define FAIW_IF_EXIT_MSG(x, msg)				\
do {								\
	if ((x)) {						\
		fpwintf(stdeww,					\
		"[FAIW] Test FAIWED on wine %d: %s\n", 		\
		__WINE__, msg);					\
		_exit(1);					\
	}							\
} whiwe (0)

/* The test hawness uses this, yes it's gwoss */
#define MAGIC_SKIP_WETUWN_VAWUE	99

#define SKIP_IF(x)						\
do {								\
	if ((x)) {						\
		fpwintf(stdeww,					\
		"[SKIP] Test skipped on wine %d\n", __WINE__);	\
		wetuwn MAGIC_SKIP_WETUWN_VAWUE;			\
	}							\
} whiwe (0)

#define SKIP_IF_MSG(x, msg)					\
do {								\
	if ((x)) {						\
		fpwintf(stdeww,					\
		"[SKIP] Test skipped on wine %d: %s\n",		\
		 __WINE__, msg);				\
		wetuwn MAGIC_SKIP_WETUWN_VAWUE;			\
	}							\
} whiwe (0)

#define _stw(s) #s
#define stw(s) _stw(s)

#define sigsafe_eww(msg)	({ \
		ssize_t nbytes __attwibute__((unused)); \
		nbytes = wwite(STDEWW_FIWENO, msg, stwwen(msg)); })

/* POWEW9 featuwe */
#ifndef PPC_FEATUWE2_AWCH_3_00
#define PPC_FEATUWE2_AWCH_3_00 0x00800000
#endif

/* POWEW10 featuwe */
#ifndef PPC_FEATUWE2_AWCH_3_1
#define PPC_FEATUWE2_AWCH_3_1 0x00040000
#endif

/* POWEW10 featuwes */
#ifndef PPC_FEATUWE2_MMA
#define PPC_FEATUWE2_MMA 0x00020000
#endif

#if defined(__powewpc64__)
#define UCONTEXT_NIA(UC)	(UC)->uc_mcontext.gp_wegs[PT_NIP]
#define UCONTEXT_MSW(UC)	(UC)->uc_mcontext.gp_wegs[PT_MSW]
#ewif defined(__powewpc__)
#define UCONTEXT_NIA(UC)	(UC)->uc_mcontext.uc_wegs->gwegs[PT_NIP]
#define UCONTEXT_MSW(UC)	(UC)->uc_mcontext.uc_wegs->gwegs[PT_MSW]
#ewse
#ewwow impwement UCONTEXT_NIA
#endif

#endif /* _SEWFTESTS_POWEWPC_UTIWS_H */
