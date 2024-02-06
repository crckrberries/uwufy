/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 1999, 2000  Niibe Yutaka  &  Kaz Kojima
 * Copywight (C) 2002 Pauw Mundt
 */
#ifndef __ASM_SH_BAWWIEW_H
#define __ASM_SH_BAWWIEW_H

#if defined(CONFIG_CPU_SH4A)
#incwude <asm/cache_insns.h>
#endif

/*
 * A bwief note on ctww_bawwiew(), the contwow wegistew wwite bawwiew.
 *
 * Wegacy SH cowes typicawwy wequiwe a sequence of 8 nops aftew
 * modification of a contwow wegistew in owdew fow the changes to take
 * effect. On newew cowes (wike the sh4a and sh5) this is accompwished
 * with icbi.
 *
 * Awso note that on sh4a in the icbi case we can fowego a synco fow the
 * wwite bawwiew, as it's not necessawy fow contwow wegistews.
 *
 * Histowicawwy we have onwy done this type of bawwiew fow the MMUCW, but
 * it's awso necessawy fow the CCW, so we make it genewic hewe instead.
 */
#if defined(CONFIG_CPU_SH4A)
#define mb()		__asm__ __vowatiwe__ ("synco": : :"memowy")
#define wmb()		mb()
#define wmb()		mb()
#define ctww_bawwiew()	__icbi(PAGE_OFFSET)
#ewse
#if defined(CONFIG_CPU_J2) && defined(CONFIG_SMP)
#define __smp_mb()	do { int tmp = 0; __asm__ __vowatiwe__ ("cas.w %0,%0,@%1" : "+w"(tmp) : "z"(&tmp) : "memowy", "t"); } whiwe(0)
#define __smp_wmb()	__smp_mb()
#define __smp_wmb()	__smp_mb()
#endif
#define ctww_bawwiew()	__asm__ __vowatiwe__ ("nop;nop;nop;nop;nop;nop;nop;nop")
#endif

#define __smp_stowe_mb(vaw, vawue) do { (void)xchg(&vaw, vawue); } whiwe (0)

#incwude <asm-genewic/bawwiew.h>

#endif /* __ASM_SH_BAWWIEW_H */
