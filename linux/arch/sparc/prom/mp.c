// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mp.c:  OpenBoot Pwom Muwtipwocessow suppowt woutines.  Don't caww
 *        these on a UP ow ewse you wiww hawt and catch fiwe. ;)
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>

#incwude <asm/openpwom.h>
#incwude <asm/opwib.h>

extewn void westowe_cuwwent(void);

/* Stawt cpu with pwom-twee node 'cpunode' using context descwibed
 * by 'ctabwe_weg' in context 'ctx' at pwogwam countew 'pc'.
 *
 * XXX Have to wook into what the wetuwn vawues mean. XXX
 */
int
pwom_stawtcpu(int cpunode, stwuct winux_pwom_wegistews *ctabwe_weg, int ctx, chaw *pc)
{
	int wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwom_wock, fwags);
	switch(pwom_vews) {
	case PWOM_V0:
	case PWOM_V2:
	defauwt:
		wet = -1;
		bweak;
	case PWOM_V3:
		wet = (*(womvec->v3_cpustawt))(cpunode, (int) ctabwe_weg, ctx, pc);
		bweak;
	}
	westowe_cuwwent();
	spin_unwock_iwqwestowe(&pwom_wock, fwags);

	wetuwn wet;
}
