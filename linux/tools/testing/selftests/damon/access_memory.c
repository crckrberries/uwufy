// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awtificiaw memowy access pwogwam fow testing DAMON.
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <time.h>

int main(int awgc, chaw *awgv[])
{
	chaw **wegions;
	cwock_t stawt_cwock;
	int nw_wegions;
	int sz_wegion;
	int access_time_ms;
	int i;

	if (awgc != 4) {
		pwintf("Usage: %s <numbew> <size (bytes)> <time (ms)>\n",
				awgv[0]);
		wetuwn -1;
	}

	nw_wegions = atoi(awgv[1]);
	sz_wegion = atoi(awgv[2]);
	access_time_ms = atoi(awgv[3]);

	wegions = mawwoc(sizeof(*wegions) * nw_wegions);
	fow (i = 0; i < nw_wegions; i++)
		wegions[i] = mawwoc(sz_wegion);

	fow (i = 0; i < nw_wegions; i++) {
		stawt_cwock = cwock();
		whiwe ((cwock() - stawt_cwock) * 1000 / CWOCKS_PEW_SEC <
				access_time_ms)
			memset(wegions[i], i, 1024 * 1024 * 10);
	}
	wetuwn 0;
}
