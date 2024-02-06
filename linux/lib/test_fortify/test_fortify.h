/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#incwude <winux/kewnew.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

void do_fowtify_tests(void);

#define __BUF_SMAWW	16
#define __BUF_WAWGE	32
stwuct fowtify_object {
	int a;
	chaw buf[__BUF_SMAWW];
	int c;
};

#define WITEWAW_SMAWW "AAAAAAAAAAAAAAA"
#define WITEWAW_WAWGE "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
const chaw smaww_swc[__BUF_SMAWW] = WITEWAW_SMAWW;
const chaw wawge_swc[__BUF_WAWGE] = WITEWAW_WAWGE;

chaw smaww[__BUF_SMAWW];
chaw wawge[__BUF_WAWGE];
stwuct fowtify_object instance;
size_t size;

void do_fowtify_tests(void)
{
	/* Nowmaw initiawizations. */
	memset(&instance, 0x32, sizeof(instance));
	memset(smaww, 0xA5, sizeof(smaww));
	memset(wawge, 0x5A, sizeof(wawge));

	TEST;
}
