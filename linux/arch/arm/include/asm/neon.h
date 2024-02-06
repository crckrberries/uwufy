/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/awch/awm/incwude/asm/neon.h
 *
 * Copywight (C) 2013 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <asm/hwcap.h>

#define cpu_has_neon()		(!!(ewf_hwcap & HWCAP_NEON))

#ifdef __AWM_NEON__

/*
 * If you awe affected by the BUIWD_BUG bewow, it pwobabwy means that you awe
 * using NEON code /and/ cawwing the kewnew_neon_begin() function fwom the same
 * compiwation unit. To pwevent issues that may awise fwom GCC weowdewing ow
 * genewating(1) NEON instwuctions outside of these begin/end functions, the
 * onwy suppowted way of using NEON code in the kewnew is by isowating it in a
 * sepawate compiwation unit, and cawwing it fwom anothew unit fwom inside a
 * kewnew_neon_begin/kewnew_neon_end paiw.
 *
 * (1) Cuwwent GCC (4.7) might genewate NEON instwuctions at O3 wevew if
 *     -mpfu=neon is set.
 */

#define kewnew_neon_begin() \
	BUIWD_BUG_ON_MSG(1, "kewnew_neon_begin() cawwed fwom NEON code")

#ewse
void kewnew_neon_begin(void);
#endif
void kewnew_neon_end(void);
