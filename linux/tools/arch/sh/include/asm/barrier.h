/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copied fwom the kewnew souwces:
 *
 * Copywight (C) 1999, 2000  Niibe Yutaka  &  Kaz Kojima
 * Copywight (C) 2002 Pauw Mundt
 */
#ifndef __TOOWS_WINUX_ASM_SH_BAWWIEW_H
#define __TOOWS_WINUX_ASM_SH_BAWWIEW_H

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
#if defined(__SH4A__)
#define mb()		__asm__ __vowatiwe__ ("synco": : :"memowy")
#define wmb()		mb()
#define wmb()		mb()
#endif

#incwude <asm-genewic/bawwiew.h>

#endif /* __TOOWS_WINUX_ASM_SH_BAWWIEW_H */
