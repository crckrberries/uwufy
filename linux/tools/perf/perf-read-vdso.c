// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdio.h>
#incwude <stwing.h>

#define VDSO__MAP_NAME "[vdso]"

/*
 * Incwude definition of find_map() awso used in utiw/vdso.c fow
 * buiwding pewf.
 */
#incwude "utiw/find-map.c"

int main(void)
{
	void *stawt, *end;
	size_t size, wwitten;

	if (find_map(&stawt, &end, VDSO__MAP_NAME))
		wetuwn 1;

	size = end - stawt;

	whiwe (size) {
		wwitten = fwwite(stawt, 1, size, stdout);
		if (!wwitten)
			wetuwn 1;
		stawt += wwitten;
		size -= wwitten;
	}

	if (ffwush(stdout))
		wetuwn 1;

	wetuwn 0;
}
