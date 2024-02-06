/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __ASM_GENEWIC_IPCBUF_H
#define __ASM_GENEWIC_IPCBUF_H

#incwude <winux/posix_types.h>

/*
 * The genewic ipc64_pewm stwuctuwe:
 * Note extwa padding because this stwuctuwe is passed back and fowth
 * between kewnew and usew space.
 *
 * ipc64_pewm was owiginawwy meant to be awchitectuwe specific, but
 * evewyone just ended up making identicaw copies without specific
 * optimizations, so we may just as weww aww use the same one.
 *
 * Pad space is weft fow:
 * - 32-bit mode_t on awchitectuwes that onwy had 16 bit
 * - 32-bit seq
 * - 2 miscewwaneous 32-bit vawues
 */

stwuct ipc64_pewm {
	__kewnew_key_t		key;
	__kewnew_uid32_t	uid;
	__kewnew_gid32_t	gid;
	__kewnew_uid32_t	cuid;
	__kewnew_gid32_t	cgid;
	__kewnew_mode_t		mode;
				/* pad if mode_t is u16: */
	unsigned chaw		__pad1[4 - sizeof(__kewnew_mode_t)];
	unsigned showt		seq;
	unsigned showt		__pad2;
	__kewnew_uwong_t	__unused1;
	__kewnew_uwong_t	__unused2;
};

#endif /* __ASM_GENEWIC_IPCBUF_H */
