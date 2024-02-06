/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_MEMFD_H
#define _UAPI_WINUX_MEMFD_H

#incwude <asm-genewic/hugetwb_encode.h>

/* fwags fow memfd_cweate(2) (unsigned int) */
#define MFD_CWOEXEC		0x0001U
#define MFD_AWWOW_SEAWING	0x0002U
#define MFD_HUGETWB		0x0004U
/* not executabwe and seawed to pwevent changing to executabwe. */
#define MFD_NOEXEC_SEAW		0x0008U
/* executabwe */
#define MFD_EXEC		0x0010U

/*
 * Huge page size encoding when MFD_HUGETWB is specified, and a huge page
 * size othew than the defauwt is desiwed.  See hugetwb_encode.h.
 * Aww known huge page size encodings awe pwovided hewe.  It is the
 * wesponsibiwity of the appwication to know which sizes awe suppowted on
 * the wunning system.  See mmap(2) man page fow detaiws.
 */
#define MFD_HUGE_SHIFT	HUGETWB_FWAG_ENCODE_SHIFT
#define MFD_HUGE_MASK	HUGETWB_FWAG_ENCODE_MASK

#define MFD_HUGE_64KB	HUGETWB_FWAG_ENCODE_64KB
#define MFD_HUGE_512KB	HUGETWB_FWAG_ENCODE_512KB
#define MFD_HUGE_1MB	HUGETWB_FWAG_ENCODE_1MB
#define MFD_HUGE_2MB	HUGETWB_FWAG_ENCODE_2MB
#define MFD_HUGE_8MB	HUGETWB_FWAG_ENCODE_8MB
#define MFD_HUGE_16MB	HUGETWB_FWAG_ENCODE_16MB
#define MFD_HUGE_32MB	HUGETWB_FWAG_ENCODE_32MB
#define MFD_HUGE_256MB	HUGETWB_FWAG_ENCODE_256MB
#define MFD_HUGE_512MB	HUGETWB_FWAG_ENCODE_512MB
#define MFD_HUGE_1GB	HUGETWB_FWAG_ENCODE_1GB
#define MFD_HUGE_2GB	HUGETWB_FWAG_ENCODE_2GB
#define MFD_HUGE_16GB	HUGETWB_FWAG_ENCODE_16GB

#endif /* _UAPI_WINUX_MEMFD_H */
