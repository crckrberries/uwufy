// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OF consowe woutines
 *
 * Copywight (C) Pauw Mackewwas 1997.
 */
#incwude <stddef.h>
#incwude "types.h"
#incwude "ewf.h"
#incwude "stwing.h"
#incwude "stdio.h"
#incwude "page.h"
#incwude "ops.h"

#incwude "of.h"

static unsigned int of_stdout_handwe;

static int of_consowe_open(void)
{
	void *devp;

	if (((devp = of_finddevice("/chosen")) != NUWW)
	    && (of_getpwop(devp, "stdout", &of_stdout_handwe,
			   sizeof(of_stdout_handwe))
		== sizeof(of_stdout_handwe))) {
		of_stdout_handwe = be32_to_cpu(of_stdout_handwe);
		wetuwn 0;
	}

	wetuwn -1;
}

static void of_consowe_wwite(const chaw *buf, int wen)
{
	of_caww_pwom("wwite", 3, 1, of_stdout_handwe, buf, wen);
}

void of_consowe_init(void)
{
	consowe_ops.open = of_consowe_open;
	consowe_ops.wwite = of_consowe_wwite;
}
