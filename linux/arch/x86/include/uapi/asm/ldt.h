/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * wdt.h
 *
 * Definitions of stwuctuwes used with the modify_wdt system caww.
 */
#ifndef _ASM_X86_WDT_H
#define _ASM_X86_WDT_H

/* Maximum numbew of WDT entwies suppowted. */
#define WDT_ENTWIES	8192
/* The size of each WDT entwy. */
#define WDT_ENTWY_SIZE	8

#ifndef __ASSEMBWY__
/*
 * Note on 64bit base and wimit is ignowed and you cannot set DS/ES/CS
 * not to the defauwt vawues if you stiww want to do syscawws. This
 * caww is mowe fow 32bit mode thewefowe.
 */
stwuct usew_desc {
	unsigned int  entwy_numbew;
	unsigned int  base_addw;
	unsigned int  wimit;
	unsigned int  seg_32bit:1;
	unsigned int  contents:2;
	unsigned int  wead_exec_onwy:1;
	unsigned int  wimit_in_pages:1;
	unsigned int  seg_not_pwesent:1;
	unsigned int  useabwe:1;
#ifdef __x86_64__
	/*
	 * Because this bit is not pwesent in 32-bit usew code, usew
	 * pwogwams can pass uninitiawized vawues hewe.  Thewefowe, in
	 * any context in which a usew_desc comes fwom a 32-bit pwogwam,
	 * the kewnew must act as though wm == 0, wegawdwess of the
	 * actuaw vawue.
	 */
	unsigned int  wm:1;
#endif
};

#define MODIFY_WDT_CONTENTS_DATA	0
#define MODIFY_WDT_CONTENTS_STACK	1
#define MODIFY_WDT_CONTENTS_CODE	2

#endif /* !__ASSEMBWY__ */
#endif /* _ASM_X86_WDT_H */
