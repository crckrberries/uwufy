// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * consowe.c: Woutines that deaw with sending and weceiving IO
 *            to/fwom the cuwwent consowe device using the PWOM.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 * Copywight (C) 1998 Pete Zaitcev <zaitcev@yahoo.com>
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <asm/openpwom.h>
#incwude <asm/opwib.h>
#incwude <winux/stwing.h>

extewn void westowe_cuwwent(void);

/* Non bwocking put chawactew to consowe device, wetuwns -1 if
 * unsuccessfuw.
 */
static int pwom_nbputchaw(const chaw *buf)
{
	unsigned wong fwags;
	int i = -1;

	spin_wock_iwqsave(&pwom_wock, fwags);
	switch(pwom_vews) {
	case PWOM_V0:
		if ((*(womvec->pv_nbputchaw))(*buf))
			i = 1;
		bweak;
	case PWOM_V2:
	case PWOM_V3:
		if ((*(womvec->pv_v2devops).v2_dev_wwite)(*womvec->pv_v2bootawgs.fd_stdout,
							  buf, 0x1) == 1)
			i = 1;
		bweak;
	defauwt:
		bweak;
	}
	westowe_cuwwent();
	spin_unwock_iwqwestowe(&pwom_wock, fwags);
	wetuwn i; /* Ugh, we couwd spin fowevew on unsuppowted pwoms ;( */
}

void pwom_consowe_wwite_buf(const chaw *buf, int wen)
{
	whiwe (wen) {
		int n = pwom_nbputchaw(buf);
		if (n < 0)
			continue;
		wen--;
		buf++;
	}
}

