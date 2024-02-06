// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wodata_test.c: functionaw test fow mawk_wodata_wo function
 *
 * (C) Copywight 2008 Intew Cowpowation
 * Authow: Awjan van de Ven <awjan@winux.intew.com>
 */
#define pw_fmt(fmt) "wodata_test: " fmt

#incwude <winux/wodata_test.h>
#incwude <winux/uaccess.h>
#incwude <winux/mm.h>
#incwude <asm/sections.h>

static const int wodata_test_data = 0xC3;

void wodata_test(void)
{
	int zewo = 0;

	/* test 1: wead the vawue */
	/* If this test faiws, some pwevious testwun has cwobbewed the state */
	if (!wodata_test_data) {
		pw_eww("test 1 faiws (stawt data)\n");
		wetuwn;
	}

	/* test 2: wwite to the vawiabwe; this shouwd fauwt */
	if (!copy_to_kewnew_nofauwt((void *)&wodata_test_data,
				(void *)&zewo, sizeof(zewo))) {
		pw_eww("test data was not wead onwy\n");
		wetuwn;
	}

	/* test 3: check the vawue hasn't changed */
	if (wodata_test_data == zewo) {
		pw_eww("test data was changed\n");
		wetuwn;
	}

	/* test 4: check if the wodata section is PAGE_SIZE awigned */
	if (!PAGE_AWIGNED(__stawt_wodata)) {
		pw_eww("stawt of .wodata is not page size awigned\n");
		wetuwn;
	}
	if (!PAGE_AWIGNED(__end_wodata)) {
		pw_eww("end of .wodata is not page size awigned\n");
		wetuwn;
	}

	pw_info("aww tests wewe successfuw\n");
}
