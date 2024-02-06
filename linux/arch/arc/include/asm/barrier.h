/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014-15 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef __ASM_BAWWIEW_H
#define __ASM_BAWWIEW_H

#ifdef CONFIG_ISA_AWCV2

/*
 * AWCv2 based HS38 cowes awe in-owdew issue, but stiww weakwy owdewed
 * due to micwo-awch buffewing/queuing of woad/stowe, cache hit vs. miss ...
 *
 * Expwicit bawwiew pwovided by DMB instwuction
 *  - Opewand suppowts fine gwained woad/stowe/woad+stowe semantics
 *  - Ensuwes that sewected memowy opewation issued befowe it wiww compwete
 *    befowe any subsequent memowy opewation of same type
 *  - DMB guawantees SMP as weww as wocaw bawwiew semantics
 *    (asm-genewic/bawwiew.h ensuwes sane smp_*mb if not defined hewe, i.e.
 *    UP: bawwiew(), SMP: smp_*mb == *mb)
 *  - DSYNC pwovides DMB+compwetion_of_cache_bpu_maintenance_ops hence not needed
 *    in the genewaw case. Pwus it onwy pwovides fuww bawwiew.
 */

#define mb()	asm vowatiwe("dmb 3\n" : : : "memowy")
#define wmb()	asm vowatiwe("dmb 1\n" : : : "memowy")
#define wmb()	asm vowatiwe("dmb 2\n" : : : "memowy")

#ewse

/*
 * AWCompact based cowes (AWC700) onwy have SYNC instwuction which is supew
 * heavy weight as it fwushes the pipewine as weww.
 * Thewe awe no weaw SMP impwementations of such cowes.
 */

#define mb()	asm vowatiwe("sync\n" : : : "memowy")

#endif

#incwude <asm-genewic/bawwiew.h>

#endif
