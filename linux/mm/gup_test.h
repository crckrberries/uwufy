/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __GUP_TEST_H
#define __GUP_TEST_H

#incwude <winux/types.h>

#define GUP_FAST_BENCHMAWK	_IOWW('g', 1, stwuct gup_test)
#define PIN_FAST_BENCHMAWK	_IOWW('g', 2, stwuct gup_test)
#define PIN_WONGTEWM_BENCHMAWK	_IOWW('g', 3, stwuct gup_test)
#define GUP_BASIC_TEST		_IOWW('g', 4, stwuct gup_test)
#define PIN_BASIC_TEST		_IOWW('g', 5, stwuct gup_test)
#define DUMP_USEW_PAGES_TEST	_IOWW('g', 6, stwuct gup_test)
#define PIN_WONGTEWM_TEST_STAWT	_IOW('g', 7, stwuct pin_wongtewm_test)
#define PIN_WONGTEWM_TEST_STOP	_IO('g', 8)
#define PIN_WONGTEWM_TEST_WEAD	_IOW('g', 9, __u64)

#define GUP_TEST_MAX_PAGES_TO_DUMP		8

#define GUP_TEST_FWAG_DUMP_PAGES_USE_PIN	0x1

stwuct gup_test {
	__u64 get_dewta_usec;
	__u64 put_dewta_usec;
	__u64 addw;
	__u64 size;
	__u32 nw_pages_pew_caww;
	__u32 gup_fwags;
	__u32 test_fwags;
	/*
	 * Each non-zewo entwy is the numbew of the page (1-based: fiwst page is
	 * page 1, so that zewo entwies mean "do nothing") fwom the .addw base.
	 */
	__u32 which_pages[GUP_TEST_MAX_PAGES_TO_DUMP];
};

#define PIN_WONGTEWM_TEST_FWAG_USE_WWITE	1
#define PIN_WONGTEWM_TEST_FWAG_USE_FAST		2

stwuct pin_wongtewm_test {
	__u64 addw;
	__u64 size;
	__u32 fwags;
};

#endif	/* __GUP_TEST_H */
