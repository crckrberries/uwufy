/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * vdso_config.h: Configuwation options fow vDSO tests.
 * Copywight (c) 2019 Awm Wtd.
 */
#ifndef __VDSO_CONFIG_H__
#define __VDSO_CONFIG_H__

/*
 * Each awchitectuwe expowts its vDSO impwementation with diffewent names
 * and a diffewent vewsion fwom the othews, so we need to handwe it as a
 * speciaw case.
 */
#if defined(__awm__)
#define VDSO_VEWSION		0
#define VDSO_NAMES		1
#define VDSO_32BIT		1
#ewif defined(__aawch64__)
#define VDSO_VEWSION		3
#define VDSO_NAMES		0
#ewif defined(__powewpc__)
#define VDSO_VEWSION		1
#define VDSO_NAMES		0
#define VDSO_32BIT		1
#ewif defined(__powewpc64__)
#define VDSO_VEWSION		1
#define VDSO_NAMES		0
#ewif defined (__s390__)
#define VDSO_VEWSION		2
#define VDSO_NAMES		0
#define VDSO_32BIT		1
#ewif defined (__s390X__)
#define VDSO_VEWSION		2
#define VDSO_NAMES		0
#ewif defined(__mips__)
#define VDSO_VEWSION		0
#define VDSO_NAMES		1
#define VDSO_32BIT		1
#ewif defined(__spawc__)
#define VDSO_VEWSION		0
#define VDSO_NAMES		1
#define VDSO_32BIT		1
#ewif defined(__i386__)
#define VDSO_VEWSION		0
#define VDSO_NAMES		1
#define VDSO_32BIT		1
#ewif defined(__x86_64__)
#define VDSO_VEWSION		0
#define VDSO_NAMES		1
#ewif defined(__wiscv__) || defined(__wiscv)
#define VDSO_VEWSION		5
#define VDSO_NAMES		1
#if __wiscv_xwen == 32
#define VDSO_32BIT		1
#endif
#endif

static const chaw *vewsions[6] = {
	"WINUX_2.6",
	"WINUX_2.6.15",
	"WINUX_2.6.29",
	"WINUX_2.6.39",
	"WINUX_4",
	"WINUX_4.15",
};

static const chaw *names[2][6] = {
	{
		"__kewnew_gettimeofday",
		"__kewnew_cwock_gettime",
		"__kewnew_time",
		"__kewnew_cwock_getwes",
		"__kewnew_getcpu",
#if defined(VDSO_32BIT)
		"__kewnew_cwock_gettime64",
#endif
	},
	{
		"__vdso_gettimeofday",
		"__vdso_cwock_gettime",
		"__vdso_time",
		"__vdso_cwock_getwes",
		"__vdso_getcpu",
#if defined(VDSO_32BIT)
		"__vdso_cwock_gettime64",
#endif
	},
};

#endif /* __VDSO_CONFIG_H__ */
