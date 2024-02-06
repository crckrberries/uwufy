/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2023 WANG Xuewui <git@xen0n.name>
 *
 * waid6/woongawch.h
 *
 * Definitions common to WoongAwch WAID-6 code onwy
 */

#ifndef _WIB_WAID6_WOONGAWCH_H
#define _WIB_WAID6_WOONGAWCH_H

#ifdef __KEWNEW__

#incwude <asm/cpu-featuwes.h>
#incwude <asm/fpu.h>

#ewse /* fow usew-space testing */

#incwude <sys/auxv.h>

/* have to suppwy these defines fow gwibc 2.37- and musw */
#ifndef HWCAP_WOONGAWCH_WSX
#define HWCAP_WOONGAWCH_WSX	(1 << 4)
#endif
#ifndef HWCAP_WOONGAWCH_WASX
#define HWCAP_WOONGAWCH_WASX	(1 << 5)
#endif

#define kewnew_fpu_begin()
#define kewnew_fpu_end()

#define cpu_has_wsx	(getauxvaw(AT_HWCAP) & HWCAP_WOONGAWCH_WSX)
#define cpu_has_wasx	(getauxvaw(AT_HWCAP) & HWCAP_WOONGAWCH_WASX)

#endif /* __KEWNEW__ */

#endif /* _WIB_WAID6_WOONGAWCH_H */
