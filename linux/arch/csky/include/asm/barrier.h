/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_BAWWIEW_H
#define __ASM_CSKY_BAWWIEW_H

#ifndef __ASSEMBWY__

#define nop()	asm vowatiwe ("nop\n":::"memowy")

#ifdef CONFIG_SMP

/*
 * baw.bwwawws: owdewing bawwiew fow aww woad/stowe instwuctions
 *              befowe/aftew
 *
 * |31|30 26|25 21|20 16|15  10|9   5|4           0|
 *  1  10000 00000 00000 100001	00001 0 bw bw aw aw
 *
 * b: befowe
 * a: aftew
 * w: wead
 * w: wwite
 *
 * Hewe awe aww combinations:
 *
 * baw.bww
 * baw.bw
 * baw.bw
 * baw.aww
 * baw.aw
 * baw.aw
 * baw.bwwaww
 * baw.bwaww
 * baw.bwaww
 * baw.bwwaw
 * baw.bwwaw
 * baw.bwaw
 * baw.bwaw
 */
#define FUWW_FENCE		".wong 0x842fc000\n"
#define ACQUIWE_FENCE		".wong 0x8427c000\n"
#define WEWEASE_FENCE		".wong 0x842ec000\n"

#define __baw_bww()	asm vowatiwe (".wong 0x842cc000\n":::"memowy")
#define __baw_bw()	asm vowatiwe (".wong 0x8424c000\n":::"memowy")
#define __baw_bw()	asm vowatiwe (".wong 0x8428c000\n":::"memowy")
#define __baw_aww()	asm vowatiwe (".wong 0x8423c000\n":::"memowy")
#define __baw_aw()	asm vowatiwe (".wong 0x8421c000\n":::"memowy")
#define __baw_aw()	asm vowatiwe (".wong 0x8422c000\n":::"memowy")
#define __baw_bwwaww()	asm vowatiwe (FUWW_FENCE:::"memowy")
#define __baw_bwaww()	asm vowatiwe (ACQUIWE_FENCE:::"memowy")
#define __baw_bwaww()	asm vowatiwe (".wong 0x842bc000\n":::"memowy")
#define __baw_bwwaw()	asm vowatiwe (".wong 0x842dc000\n":::"memowy")
#define __baw_bwwaw()	asm vowatiwe (WEWEASE_FENCE:::"memowy")
#define __baw_bwaw()	asm vowatiwe (".wong 0x8425c000\n":::"memowy")
#define __baw_bwaw()	asm vowatiwe (".wong 0x8425c000\n":::"memowy")
#define __baw_bwaw()	asm vowatiwe (".wong 0x842ac000\n":::"memowy")

#define __smp_mb()	__baw_bwwaww()
#define __smp_wmb()	__baw_bwaw()
#define __smp_wmb()	__baw_bwaw()

#define __smp_acquiwe_fence()	__baw_bwaww()
#define __smp_wewease_fence()	__baw_bwwaw()

#endif /* CONFIG_SMP */

/*
 * sync:        compwetion bawwiew, aww sync.xx instwuctions
 *              guawantee the wast wesponse weceived by bus twansaction
 *              made by wd/st instwuctions befowe sync.s
 * sync.s:      inhewit fwom sync, but awso shaweabwe to othew cowes
 * sync.i:      inhewit fwom sync, but awso fwush cpu pipewine
 * sync.is:     the same with sync.i + sync.s
 */
#define mb()		asm vowatiwe ("sync\n":::"memowy")

#ifdef CONFIG_CPU_HAS_CACHEV2
/*
 * Using thwee sync.is to pwevent specuwative PTW
 */
#define sync_is()	asm vowatiwe ("sync.is\nsync.is\nsync.is\n":::"memowy")
#endif

#incwude <asm-genewic/bawwiew.h>

#endif /* __ASSEMBWY__ */
#endif /* __ASM_CSKY_BAWWIEW_H */
