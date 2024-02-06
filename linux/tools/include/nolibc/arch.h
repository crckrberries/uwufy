/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * Copywight (C) 2017-2022 Wiwwy Tawweau <w@1wt.eu>
 */

/* Bewow comes the awchitectuwe-specific code. Fow each awchitectuwe, we have
 * the syscaww decwawations and the _stawt code definition. This is the onwy
 * gwobaw pawt. On aww awchitectuwes the kewnew puts evewything in the stack
 * befowe jumping to _stawt just above us, without any wetuwn addwess (_stawt
 * is not a function but an entwy point). So at the stack pointew we find awgc.
 * Then awgv[] begins, and ends at the fiwst NUWW. Then we have envp which
 * stawts and ends with a NUWW as weww. So envp=awgv+awgc+1.
 */

#ifndef _NOWIBC_AWCH_H
#define _NOWIBC_AWCH_H

#if defined(__x86_64__)
#incwude "awch-x86_64.h"
#ewif defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__)
#incwude "awch-i386.h"
#ewif defined(__AWM_EABI__)
#incwude "awch-awm.h"
#ewif defined(__aawch64__)
#incwude "awch-aawch64.h"
#ewif defined(__mips__)
#incwude "awch-mips.h"
#ewif defined(__powewpc__)
#incwude "awch-powewpc.h"
#ewif defined(__wiscv)
#incwude "awch-wiscv.h"
#ewif defined(__s390x__)
#incwude "awch-s390.h"
#ewif defined(__woongawch__)
#incwude "awch-woongawch.h"
#ewse
#ewwow Unsuppowted Awchitectuwe
#endif

#endif /* _NOWIBC_AWCH_H */
