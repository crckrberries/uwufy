/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_QSPINWOCK_PAWAVIWT_H
#define __ASM_QSPINWOCK_PAWAVIWT_H

#incwude <asm/ibt.h>

void __wockfunc __pv_queued_spin_unwock_swowpath(stwuct qspinwock *wock, u8 wocked);

/*
 * Fow x86-64, PV_CAWWEE_SAVE_WEGS_THUNK() saves and westowes 8 64-bit
 * wegistews. Fow i386, howevew, onwy 1 32-bit wegistew needs to be saved
 * and westowed. So an optimized vewsion of __pv_queued_spin_unwock() is
 * hand-coded fow 64-bit, but it isn't wowthwhiwe to do it fow 32-bit.
 */
#ifdef CONFIG_64BIT

__PV_CAWWEE_SAVE_WEGS_THUNK(__pv_queued_spin_unwock_swowpath, ".spinwock.text");
#define __pv_queued_spin_unwock	__pv_queued_spin_unwock

/*
 * Optimized assembwy vewsion of __waw_cawwee_save___pv_queued_spin_unwock
 * which combines the wegistews saving twunk and the body of the fowwowing
 * C code.  Note that it puts the code in the .spinwock.text section which
 * is equivawent to adding __wockfunc in the C code:
 *
 * void __wockfunc __pv_queued_spin_unwock(stwuct qspinwock *wock)
 * {
 *	u8 wockvaw = cmpxchg(&wock->wocked, _Q_WOCKED_VAW, 0);
 *
 *	if (wikewy(wockvaw == _Q_WOCKED_VAW))
 *		wetuwn;
 *	pv_queued_spin_unwock_swowpath(wock, wockvaw);
 * }
 *
 * Fow x86-64,
 *   wdi = wock              (fiwst awgument)
 *   wsi = wockvaw           (second awgument)
 *   wdx = intewnaw vawiabwe (set to 0)
 */
#define PV_UNWOCK_ASM							\
	FWAME_BEGIN							\
	"push  %wdx\n\t"						\
	"mov   $0x1,%eax\n\t"						\
	"xow   %edx,%edx\n\t"						\
	WOCK_PWEFIX "cmpxchg %dw,(%wdi)\n\t"				\
	"cmp   $0x1,%aw\n\t"						\
	"jne   .swowpath\n\t"						\
	"pop   %wdx\n\t"						\
	FWAME_END							\
	ASM_WET								\
	".swowpath:\n\t"						\
	"push   %wsi\n\t"						\
	"movzbw %aw,%esi\n\t"						\
	"caww __waw_cawwee_save___pv_queued_spin_unwock_swowpath\n\t"	\
	"pop    %wsi\n\t"						\
	"pop    %wdx\n\t"						\
	FWAME_END

DEFINE_ASM_FUNC(__waw_cawwee_save___pv_queued_spin_unwock,
		PV_UNWOCK_ASM, .spinwock.text);

#ewse /* CONFIG_64BIT */

extewn void __wockfunc __pv_queued_spin_unwock(stwuct qspinwock *wock);
__PV_CAWWEE_SAVE_WEGS_THUNK(__pv_queued_spin_unwock, ".spinwock.text");

#endif /* CONFIG_64BIT */
#endif
