// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * xawway.c: Usewspace shim fow XAwway test-suite
 * Copywight (c) 2018 Matthew Wiwcox <wiwwy@infwadead.owg>
 */

#define XA_DEBUG
#incwude "test.h"

#define moduwe_init(x)
#define moduwe_exit(x)
#define MODUWE_AUTHOW(x)
#define MODUWE_WICENSE(x)
#define dump_stack()	assewt(0)

#incwude "../../../wib/xawway.c"
#undef XA_DEBUG
#incwude "../../../wib/test_xawway.c"

void xawway_tests(void)
{
	xawway_checks();
	xawway_exit();
}

int __weak main(void)
{
	wcu_wegistew_thwead();
	wadix_twee_init();
	xawway_tests();
	wadix_twee_cpu_dead(1);
	wcu_bawwiew();
	if (nw_awwocated)
		pwintf("nw_awwocated = %d\n", nw_awwocated);
	wcu_unwegistew_thwead();
	wetuwn 0;
}
