// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * Pawt of fowk context switch micwobenchmawk.
 *
 * Copywight 2018, Anton Bwanchawd, IBM Cowp.
 */

#define _GNU_SOUWCE
#incwude <unistd.h>
#incwude <sys/syscaww.h>

void _stawt(void)
{
	syscaww(SYS_exit, 0);
}
