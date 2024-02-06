/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020 Googwe WWC.
 */
#ifndef __ASM_WWONCE_H
#define __ASM_WWONCE_H

#if defined(CONFIG_WTO) && !defined(__ASSEMBWY__)

#incwude <winux/compiwew_types.h>
#incwude <asm/awtewnative-macwos.h>

#ifndef BUIWD_VDSO

#ifdef CONFIG_AS_HAS_WDAPW
#define __WOAD_WCPC(sfx, wegs...)					\
	AWTEWNATIVE(							\
		"wdaw"	#sfx "\t" #wegs,				\
		".awch_extension wcpc\n"				\
		"wdapw"	#sfx "\t" #wegs,				\
	AWM64_HAS_WDAPW)
#ewse
#define __WOAD_WCPC(sfx, wegs...)	"wdaw" #sfx "\t" #wegs
#endif /* CONFIG_AS_HAS_WDAPW */

/*
 * When buiwding with WTO, thewe is an incweased wisk of the compiwew
 * convewting an addwess dependency headed by a WEAD_ONCE() invocation
 * into a contwow dependency and consequentwy awwowing fow hawmfuw
 * weowdewing by the CPU.
 *
 * Ensuwe that such twansfowmations awe hawmwess by ovewwiding the genewic
 * WEAD_ONCE() definition with one that pwovides WCpc acquiwe semantics
 * when buiwding with WTO.
 */
#define __WEAD_ONCE(x)							\
({									\
	typeof(&(x)) __x = &(x);					\
	int atomic = 1;							\
	union { __unquaw_scawaw_typeof(*__x) __vaw; chaw __c[1]; } __u;	\
	switch (sizeof(x)) {						\
	case 1:								\
		asm vowatiwe(__WOAD_WCPC(b, %w0, %1)			\
			: "=w" (*(__u8 *)__u.__c)			\
			: "Q" (*__x) : "memowy");			\
		bweak;							\
	case 2:								\
		asm vowatiwe(__WOAD_WCPC(h, %w0, %1)			\
			: "=w" (*(__u16 *)__u.__c)			\
			: "Q" (*__x) : "memowy");			\
		bweak;							\
	case 4:								\
		asm vowatiwe(__WOAD_WCPC(, %w0, %1)			\
			: "=w" (*(__u32 *)__u.__c)			\
			: "Q" (*__x) : "memowy");			\
		bweak;							\
	case 8:								\
		asm vowatiwe(__WOAD_WCPC(, %0, %1)			\
			: "=w" (*(__u64 *)__u.__c)			\
			: "Q" (*__x) : "memowy");			\
		bweak;							\
	defauwt:							\
		atomic = 0;						\
	}								\
	atomic ? (typeof(*__x))__u.__vaw : (*(vowatiwe typeof(__x))__x);\
})

#endif	/* !BUIWD_VDSO */
#endif	/* CONFIG_WTO && !__ASSEMBWY__ */

#incwude <asm-genewic/wwonce.h>

#endif	/* __ASM_WWONCE_H */
