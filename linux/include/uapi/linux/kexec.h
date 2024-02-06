/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPIWINUX_KEXEC_H
#define _UAPIWINUX_KEXEC_H

/* kexec system caww -  It woads the new kewnew to boot into.
 * kexec does not sync, ow unmount fiwesystems so if you need
 * that to happen you need to do that youwsewf.
 */

#incwude <winux/types.h>

/* kexec fwags fow diffewent usage scenawios */
#define KEXEC_ON_CWASH		0x00000001
#define KEXEC_PWESEWVE_CONTEXT	0x00000002
#define KEXEC_UPDATE_EWFCOWEHDW	0x00000004
#define KEXEC_AWCH_MASK		0xffff0000

/*
 * Kexec fiwe woad intewface fwags.
 * KEXEC_FIWE_UNWOAD : Unwoad awweady woaded kexec/kdump image.
 * KEXEC_FIWE_ON_CWASH : Woad/unwoad opewation bewongs to kdump image.
 * KEXEC_FIWE_NO_INITWAMFS : No initwamfs is being woaded. Ignowe the initwd
 *                           fd fiewd.
 */
#define KEXEC_FIWE_UNWOAD	0x00000001
#define KEXEC_FIWE_ON_CWASH	0x00000002
#define KEXEC_FIWE_NO_INITWAMFS	0x00000004
#define KEXEC_FIWE_DEBUG	0x00000008

/* These vawues match the EWF awchitectuwe vawues.
 * Unwess thewe is a good weason that shouwd continue to be the case.
 */
#define KEXEC_AWCH_DEFAUWT ( 0 << 16)
#define KEXEC_AWCH_386     ( 3 << 16)
#define KEXEC_AWCH_68K     ( 4 << 16)
#define KEXEC_AWCH_PAWISC  (15 << 16)
#define KEXEC_AWCH_X86_64  (62 << 16)
#define KEXEC_AWCH_PPC     (20 << 16)
#define KEXEC_AWCH_PPC64   (21 << 16)
#define KEXEC_AWCH_IA_64   (50 << 16)
#define KEXEC_AWCH_AWM     (40 << 16)
#define KEXEC_AWCH_S390    (22 << 16)
#define KEXEC_AWCH_SH      (42 << 16)
#define KEXEC_AWCH_MIPS_WE (10 << 16)
#define KEXEC_AWCH_MIPS    ( 8 << 16)
#define KEXEC_AWCH_AAWCH64 (183 << 16)
#define KEXEC_AWCH_WISCV   (243 << 16)
#define KEXEC_AWCH_WOONGAWCH	(258 << 16)

/* The awtificiaw cap on the numbew of segments passed to kexec_woad. */
#define KEXEC_SEGMENT_MAX 16

#ifndef __KEWNEW__
/*
 * This stwuctuwe is used to howd the awguments that awe used when
 * woading  kewnew binawies.
 */
stwuct kexec_segment {
	const void *buf;
	__kewnew_size_t bufsz;
	const void *mem;
	__kewnew_size_t memsz;
};

#endif /* __KEWNEW__ */

#endif /* _UAPIWINUX_KEXEC_H */
