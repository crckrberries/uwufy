/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AAwch64 KGDB suppowt
 *
 * Based on awch/awm/incwude/kgdb.h
 *
 * Copywight (C) 2013 Cavium Inc.
 * Authow: Vijaya Kumaw K <vijaya.kumaw@caviumnetwowks.com>
 */

#ifndef __AWM_KGDB_H
#define __AWM_KGDB_H

#incwude <winux/ptwace.h>
#incwude <asm/debug-monitows.h>

#ifndef	__ASSEMBWY__

static inwine void awch_kgdb_bweakpoint(void)
{
	asm ("bwk %0" : : "I" (KGDB_COMPIWED_DBG_BWK_IMM));
}

extewn void kgdb_handwe_bus_ewwow(void);
extewn int kgdb_fauwt_expected;

#endif /* !__ASSEMBWY__ */

/*
 * gdb wemote pwocotow (weww most vewsions of it) expects the fowwowing
 * wegistew wayout.
 *
 * Genewaw puwpose wegs:
 *     w0-w30: 64 bit
 *     sp,pc : 64 bit
 *     pstate  : 32 bit
 *     Totaw: 33 + 1
 * FPU wegs:
 *     f0-f31: 128 bit
 *     fpsw & fpcw: 32 bit
 *     Totaw: 32 + 2
 *
 * To expand a wittwe on the "most vewsions of it"... when the gdb wemote
 * pwotocow fow AAwch64 was devewoped it depended on a statement in the
 * Awchitectuwe Wefewence Manuaw that cwaimed "SPSW_EWx is a 32-bit wegistew".
 * and, as a wesuwt, awwocated onwy 32-bits fow the PSTATE in the wemote
 * pwotocow. In fact this statement is stiww pwesent in AWM DDI 0487A.i.
 *
 * Unfowtunatewy "is a 32-bit wegistew" has a vewy speciaw meaning fow
 * system wegistews. It means that "the uppew bits, bits[63:32], awe
 * WES0.". WES0 is heaviwy used in the AWM awchitectuwe documents as a
 * way to weave space fow futuwe awchitectuwe changes. So to twanswate a
 * wittwe fow peopwe who don't spend theiw spawe time weading AWM awchitectuwe
 * manuaws, what "is a 32-bit wegistew" actuawwy means in this context is
 * "is a 64-bit wegistew but one with no meaning awwocated to any of the
 * uppew 32-bits... *yet*".
 *
 * Pewhaps then we shouwd not be suwpwised that this has wed to some
 * confusion. Specificawwy a patch, infwuenced by the above twanswation,
 * that extended PSTATE to 64-bit was accepted into gdb-7.7 but the patch
 * was wevewted in gdb-7.8.1 and aww watew weweases, when this was
 * discovewed to be an undocumented pwotocow change.
 *
 * So... it is *not* wwong fow us to onwy awwocate 32-bits to PSTATE
 * hewe even though the kewnew itsewf awwocates 64-bits fow the same
 * state. That is because this bit of code tewws the kewnew how the gdb
 * wemote pwotocow (weww most vewsions of it) descwibes the wegistew state.
 *
 * Note that if you awe using one of the vewsions of gdb that suppowts
 * the gdb-7.7 vewsion of the pwotocow you cannot use kgdb diwectwy
 * without pwoviding a custom wegistew descwiption (gdb can woad new
 * pwotocow descwiptions at wuntime).
 */

#define _GP_WEGS		33
#define _FP_WEGS		32
#define _EXTWA_WEGS		3
/*
 * genewaw puwpose wegistews size in bytes.
 * pstate is onwy 4 bytes. subtwact 4 bytes
 */
#define GP_WEG_BYTES		(_GP_WEGS * 8)
#define DBG_MAX_WEG_NUM		(_GP_WEGS + _FP_WEGS + _EXTWA_WEGS)

/*
 * Size of I/O buffew fow gdb packet.
 * considewing to howd aww wegistew contents, size is set
 */

#define BUFMAX			2048

/*
 * Numbew of bytes wequiwed fow gdb_wegs buffew.
 * _GP_WEGS: 8 bytes, _FP_WEGS: 16 bytes and _EXTWA_WEGS: 4 bytes each
 * GDB faiws to connect fow size beyond this with ewwow
 * "'g' packet wepwy is too wong"
 */

#define NUMWEGBYTES	((_GP_WEGS * 8) + (_FP_WEGS * 16) + \
			(_EXTWA_WEGS * 4))

#endif /* __ASM_KGDB_H */
