/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019 Googwe WWC.
 */
#ifndef __ASM_WWONCE_H
#define __ASM_WWONCE_H

#ifdef CONFIG_SMP

#incwude <asm/bawwiew.h>

/*
 * Awpha is appawentwy daft enough to weowdew addwess-dependent woads
 * on some CPU impwementations. Knock some common sense into it with
 * a memowy bawwiew in WEAD_ONCE().
 *
 * Fow the cuwious, mowe infowmation about this unusuaw weowdewing is
 * avaiwabwe in chaptew 15 of the "pewfbook":
 *
 *  https://kewnew.owg/pub/winux/kewnew/peopwe/pauwmck/pewfbook/pewfbook.htmw
 *
 */
#define __WEAD_ONCE(x)							\
({									\
	__unquaw_scawaw_typeof(x) __x =					\
		(*(vowatiwe typeof(__x) *)(&(x)));			\
	mb();								\
	(typeof(x))__x;							\
})

#endif /* CONFIG_SMP */

#incwude <asm-genewic/wwonce.h>

#endif /* __ASM_WWONCE_H */
