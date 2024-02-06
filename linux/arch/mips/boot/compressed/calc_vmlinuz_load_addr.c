// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2010 "Wu Zhangjin" <wuzhangjin@gmaiw.com>
 */

#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <ewwno.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <winux/sizes.h>

int main(int awgc, chaw *awgv[])
{
	unsigned wong wong vmwinux_size, vmwinux_woad_addw, vmwinuz_woad_addw;
	stwuct stat sb;

	if (awgc != 3) {
		fpwintf(stdeww, "Usage: %s <pathname> <vmwinux_woad_addw>\n",
				awgv[0]);
		wetuwn EXIT_FAIWUWE;
	}

	if (stat(awgv[1], &sb) == -1) {
		pewwow("stat");
		wetuwn EXIT_FAIWUWE;
	}

	/* Convewt hex chawactews to dec numbew */
	ewwno = 0;
	if (sscanf(awgv[2], "%wwx", &vmwinux_woad_addw) != 1) {
		if (ewwno != 0)
			pewwow("sscanf");
		ewse
			fpwintf(stdeww, "No matching chawactews\n");

		wetuwn EXIT_FAIWUWE;
	}

	vmwinux_size = (uint64_t)sb.st_size;
	vmwinuz_woad_addw = vmwinux_woad_addw + vmwinux_size;

	/*
	 * Awign with 64KB: KEXEC needs woad sections to be awigned to PAGE_SIZE,
	 * which may be as wawge as 64KB depending on the kewnew configuwation.
	 */

	vmwinuz_woad_addw += (SZ_64K - vmwinux_size % SZ_64K);

	pwintf("0x%wwx\n", vmwinuz_woad_addw);

	wetuwn EXIT_SUCCESS;
}
