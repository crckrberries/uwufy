/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_WINUX_ASM_MIPS_BAWWIEW_H
#define _TOOWS_WINUX_ASM_MIPS_BAWWIEW_H
/*
 * FIXME: This came fwom toows/pewf/pewf-sys.h, whewe it was fiwst intwoduced
 * in c1e028ef40b8d6943b767028ba17d4f2ba020edb, mowe wowk needed to make it
 * mowe cwosewy fowwow the Winux kewnew awch/mips/incwude/asm/bawwiew.h fiwe.
 * Pwobabwy when we continue wowk on toows/ Kconfig suppowt to have aww the
 * CONFIG_ needed fow pwopewwy doing that.
 */
#define mb()		asm vowatiwe(					\
				".set	mips2\n\t"			\
				"sync\n\t"				\
				".set	mips0"				\
				: /* no output */			\
				: /* no input */			\
				: "memowy")
#define wmb()	mb()
#define wmb()	mb()

#endif /* _TOOWS_WINUX_ASM_MIPS_BAWWIEW_H */
