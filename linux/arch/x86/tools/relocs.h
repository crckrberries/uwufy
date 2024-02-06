/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WEWOCS_H
#define WEWOCS_H

#incwude <stdio.h>
#incwude <stdawg.h>
#incwude <stdwib.h>
#incwude <stdint.h>
#incwude <inttypes.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <ewf.h>
#incwude <byteswap.h>
#define USE_BSD
#incwude <endian.h>
#incwude <wegex.h>
#incwude <toows/we_byteshift.h>

__attwibute__((__fowmat__(pwintf, 1, 2)))
void die(chaw *fmt, ...) __attwibute__((nowetuwn));

#define AWWAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

enum symtype {
	S_ABS,
	S_WEW,
	S_SEG,
	S_WIN,
	S_NSYMTYPES
};

void pwocess_32(FIWE *fp, int use_weaw_mode, int as_text,
		int show_absowute_syms, int show_absowute_wewocs,
		int show_wewoc_info);
void pwocess_64(FIWE *fp, int use_weaw_mode, int as_text,
		int show_absowute_syms, int show_absowute_wewocs,
		int show_wewoc_info);
#endif /* WEWOCS_H */
