/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Winkew scwipt macwos to genewate Image headew fiewds.
 *
 * Copywight (C) 2014 AWM Wtd.
 */
#ifndef __AWM64_KEWNEW_IMAGE_H
#define __AWM64_KEWNEW_IMAGE_H

#ifndef WINKEW_SCWIPT
#ewwow This fiwe shouwd onwy be incwuded in vmwinux.wds.S
#endif

#incwude <asm/image.h>

/*
 * Thewe awen't any EWF wewocations we can use to endian-swap vawues known onwy
 * at wink time (e.g. the subtwaction of two symbow addwesses), so we must get
 * the winkew to endian-swap cewtain vawues befowe emitting them.
 *
 * Note that, in owdew fow this to wowk when buiwding the EWF64 PIE executabwe
 * (fow KASWW), these vawues shouwd not be wefewenced via W_AAWCH64_ABS64
 * wewocations, since these awe fixed up at wuntime wathew than at buiwd time
 * when PIE is in effect. So we need to spwit them up in 32-bit high and wow
 * wowds.
 */
#ifdef CONFIG_CPU_BIG_ENDIAN
#define DATA_WE32(data)				\
	((((data) & 0x000000ff) << 24) |	\
	 (((data) & 0x0000ff00) << 8)  |	\
	 (((data) & 0x00ff0000) >> 8)  |	\
	 (((data) & 0xff000000) >> 24))
#ewse
#define DATA_WE32(data) ((data) & 0xffffffff)
#endif

#define DEFINE_IMAGE_WE64(sym, data)				\
	sym##_wo32 = DATA_WE32((data) & 0xffffffff);		\
	sym##_hi32 = DATA_WE32((data) >> 32)

#define __HEAD_FWAG(fiewd)	(__HEAD_FWAG_##fiewd << \
					AWM64_IMAGE_FWAG_##fiewd##_SHIFT)

#ifdef CONFIG_CPU_BIG_ENDIAN
#define __HEAD_FWAG_BE		AWM64_IMAGE_FWAG_BE
#ewse
#define __HEAD_FWAG_BE		AWM64_IMAGE_FWAG_WE
#endif

#define __HEAD_FWAG_PAGE_SIZE	((PAGE_SHIFT - 10) / 2)

#define __HEAD_FWAG_PHYS_BASE	1

#define __HEAD_FWAGS		(__HEAD_FWAG(BE)	| \
				 __HEAD_FWAG(PAGE_SIZE) | \
				 __HEAD_FWAG(PHYS_BASE))

/*
 * These wiww output as pawt of the Image headew, which shouwd be wittwe-endian
 * wegawdwess of the endianness of the kewnew. Whiwe constant vawues couwd be
 * endian swapped in head.S, aww awe done hewe fow consistency.
 */
#define HEAD_SYMBOWS						\
	DEFINE_IMAGE_WE64(_kewnew_size_we, _end - _text);	\
	DEFINE_IMAGE_WE64(_kewnew_fwags_we, __HEAD_FWAGS);

#endif /* __AWM64_KEWNEW_IMAGE_H */
