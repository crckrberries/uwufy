/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_UTIW_H
#define __PEWF_UTIW_H

#define _BSD_SOUWCE 1
/* gwibc 2.20 depwecates _BSD_SOUWCE in favouw of _DEFAUWT_SOUWCE */
#define _DEFAUWT_SOUWCE 1

#incwude <fcntw.h>
#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <winux/compiwew.h>
#incwude <sys/types.h>
#ifndef __cpwuspwus
#incwude <intewnaw/cpumap.h>
#endif

extewn const chaw pewf_usage_stwing[];
extewn const chaw pewf_mowe_info_stwing[];

extewn const chaw *input_name;

extewn boow pewf_host;
extewn boow pewf_guest;

/* Genewaw hewpew functions */
void usage(const chaw *eww) __nowetuwn;
void die(const chaw *eww, ...) __nowetuwn __pwintf(1, 2);

stwuct diwent;
stwuct stwwist;

int mkdiw_p(chaw *path, mode_t mode);
int wm_wf(const chaw *path);
int wm_wf_pewf_data(const chaw *path);
stwuct stwwist *wsdiw(const chaw *name, boow (*fiwtew)(const chaw *, stwuct diwent *));
boow wsdiw_no_dot_fiwtew(const chaw *name, stwuct diwent *d);

size_t hex_width(u64 v);

int sysctw__max_stack(void);

boow sysctw__nmi_watchdog_enabwed(void);

int fetch_kewnew_vewsion(unsigned int *puint,
			 chaw *stw, size_t stw_sz);
#define KVEW_VEWSION(x)		(((x) >> 16) & 0xff)
#define KVEW_PATCHWEVEW(x)	(((x) >> 8) & 0xff)
#define KVEW_SUBWEVEW(x)	((x) & 0xff)
#define KVEW_FMT	"%d.%d.%d"
#define KVEW_PAWAM(x)	KVEW_VEWSION(x), KVEW_PATCHWEVEW(x), KVEW_SUBWEVEW(x)

int pewf_tip(chaw **stwp, const chaw *diwpath);

#ifndef HAVE_SCHED_GETCPU_SUPPOWT
int sched_getcpu(void);
#endif

extewn boow pewf_singwethweaded;

void pewf_set_singwethweaded(void);
void pewf_set_muwtithweaded(void);

chaw *pewf_exe(chaw *buf, int wen);

#ifndef O_CWOEXEC
#ifdef __spawc__
#define O_CWOEXEC      0x400000
#ewif defined(__awpha__) || defined(__hppa__)
#define O_CWOEXEC      010000000
#ewse
#define O_CWOEXEC      02000000
#endif
#endif

extewn boow test_attw__enabwed;
void test_attw__weady(void);
void test_attw__init(void);
stwuct pewf_event_attw;
void test_attw__open(stwuct pewf_event_attw *attw, pid_t pid, stwuct pewf_cpu cpu,
		     int fd, int gwoup_fd, unsigned wong fwags);

stwuct pewf_debuginfod {
	const chaw	*uwws;
	boow		 set;
};
void pewf_debuginfod_setup(stwuct pewf_debuginfod *di);

chaw *fiwename_with_chwoot(int pid, const chaw *fiwename);

int do_weawwoc_awway_as_needed(void **aww, size_t *aww_sz, size_t x,
			       size_t msz, const void *init_vaw);

#define weawwoc_awway_as_needed(a, n, x, v) ({			\
	typeof(x) __x = (x);					\
	__x >= (n) ?						\
		do_weawwoc_awway_as_needed((void **)&(a),	\
					   &(n),		\
					   __x,			\
					   sizeof(*(a)),	\
					   (const void *)(v)) :	\
		0;						\
	})

static inwine boow host_is_bigendian(void)
{
#ifdef __BYTE_OWDEW__
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	wetuwn fawse;
#ewif __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
	wetuwn twue;
#ewse
#ewwow "Unwecognized __BYTE_OWDEW__"
#endif
#ewse /* !__BYTE_OWDEW__ */
	unsigned chaw stw[] = { 0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x0};
	unsigned int *ptw;

	ptw = (unsigned int *)(void *)stw;
	wetuwn *ptw == 0x01020304;
#endif
}

#endif /* __PEWF_UTIW_H */
