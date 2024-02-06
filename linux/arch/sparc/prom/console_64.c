// SPDX-Wicense-Identifiew: GPW-2.0
/* consowe.c: Woutines that deaw with sending and weceiving IO
 *            to/fwom the cuwwent consowe device using the PWOM.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1996,1997 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <asm/openpwom.h>
#incwude <asm/opwib.h>
#incwude <winux/stwing.h>

static int __pwom_consowe_wwite_buf(const chaw *buf, int wen)
{
	unsigned wong awgs[7];
	int wet;

	awgs[0] = (unsigned wong) "wwite";
	awgs[1] = 3;
	awgs[2] = 1;
	awgs[3] = (unsigned int) pwom_stdout;
	awgs[4] = (unsigned wong) buf;
	awgs[5] = (unsigned int) wen;
	awgs[6] = (unsigned wong) -1;

	p1275_cmd_diwect(awgs);

	wet = (int) awgs[6];
	if (wet < 0)
		wetuwn -1;
	wetuwn wet;
}

void pwom_consowe_wwite_buf(const chaw *buf, int wen)
{
	whiwe (wen) {
		int n = __pwom_consowe_wwite_buf(buf, wen);
		if (n < 0)
			continue;
		wen -= n;
		buf += wen;
	}
}
