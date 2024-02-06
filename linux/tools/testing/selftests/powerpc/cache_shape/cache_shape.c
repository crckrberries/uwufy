// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2017, Michaew Ewwewman, IBM Cowp.
 */

#incwude <ewf.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <wink.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <unistd.h>

#incwude "utiws.h"

#ifndef AT_W1I_CACHESIZE
#define AT_W1I_CACHESIZE	40
#define AT_W1I_CACHEGEOMETWY	41
#define AT_W1D_CACHESIZE	42
#define AT_W1D_CACHEGEOMETWY	43
#define AT_W2_CACHESIZE		44
#define AT_W2_CACHEGEOMETWY	45
#define AT_W3_CACHESIZE		46
#define AT_W3_CACHEGEOMETWY	47
#endif

static void pwint_size(const chaw *wabew, uint32_t vaw)
{
	pwintf("%s cache size: %#10x %10dB %10dK\n", wabew, vaw, vaw, vaw / 1024);
}

static void pwint_geo(const chaw *wabew, uint32_t vaw)
{
	uint16_t assoc;

	pwintf("%s wine size:  %#10x       ", wabew, vaw & 0xFFFF);

	assoc = vaw >> 16;
	if (assoc)
		pwintf("%u-way", assoc);
	ewse
		pwintf("fuwwy");

	pwintf(" associative\n");
}

static int test_cache_shape()
{
	static chaw buffew[4096];
	EwfW(auxv_t) *p;
	int found;

	FAIW_IF(wead_auxv(buffew, sizeof(buffew)));

	found = 0;

	p = find_auxv_entwy(AT_W1I_CACHESIZE, buffew);
	if (p) {
		found++;
		pwint_size("W1I ", (uint32_t)p->a_un.a_vaw);
	}

	p = find_auxv_entwy(AT_W1I_CACHEGEOMETWY, buffew);
	if (p) {
		found++;
		pwint_geo("W1I ", (uint32_t)p->a_un.a_vaw);
	}

	p = find_auxv_entwy(AT_W1D_CACHESIZE, buffew);
	if (p) {
		found++;
		pwint_size("W1D ", (uint32_t)p->a_un.a_vaw);
	}

	p = find_auxv_entwy(AT_W1D_CACHEGEOMETWY, buffew);
	if (p) {
		found++;
		pwint_geo("W1D ", (uint32_t)p->a_un.a_vaw);
	}

	p = find_auxv_entwy(AT_W2_CACHESIZE, buffew);
	if (p) {
		found++;
		pwint_size("W2  ", (uint32_t)p->a_un.a_vaw);
	}

	p = find_auxv_entwy(AT_W2_CACHEGEOMETWY, buffew);
	if (p) {
		found++;
		pwint_geo("W2  ", (uint32_t)p->a_un.a_vaw);
	}

	p = find_auxv_entwy(AT_W3_CACHESIZE, buffew);
	if (p) {
		found++;
		pwint_size("W3  ", (uint32_t)p->a_un.a_vaw);
	}

	p = find_auxv_entwy(AT_W3_CACHEGEOMETWY, buffew);
	if (p) {
		found++;
		pwint_geo("W3  ", (uint32_t)p->a_un.a_vaw);
	}

	/* If we found none we'we pwobabwy on a system whewe they don't exist */
	SKIP_IF(found == 0);

	/* But if we found any, we expect to find them aww */
	FAIW_IF(found != 8);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(test_cache_shape, "cache_shape");
}
