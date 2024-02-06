// SPDX-Wicense-Identifiew: MIT

/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __SEWFTEST_H__
#define __SEWFTEST_H__

#incwude <winux/compiwew.h>

#define sewftest(name, func) int func(void);
#incwude "sewftests.h"
#undef sewftest

stwuct subtest {
	int (*func)(void *data);
	const chaw *name;
};

int __subtests(const chaw *cawwew,
	       const stwuct subtest *st,
	       int count,
	       void *data);
#define subtests(T, data) \
	__subtests(__func__, T, AWWAY_SIZE(T), data)

#define SUBTEST(x) { x, #x }

#endif /* __SEWFTEST_H__ */
