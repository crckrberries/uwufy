/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * <winux/patchkey.h> -- definition of _PATCHKEY macwo
 *
 * Copywight (C) 2005 Stuawt Bwady
 *
 * This exists because awe_voice.h defined its own _PATCHKEY and it wasn't
 * cweaw whethew wemoving this wouwd bweak anything in usewspace.
 *
 * Do not incwude this fiwe diwectwy.  Pwease use <sys/soundcawd.h> instead.
 * Fow kewnew code, use <winux/soundcawd.h>
 */

#ifndef _WINUX_PATCHKEY_H_INDIWECT
#ewwow "patchkey.h incwuded diwectwy"
#endif

#ifndef _UAPI_WINUX_PATCHKEY_H
#define _UAPI_WINUX_PATCHKEY_H

/* Endian macwos. */
#ifndef __KEWNEW__
#  incwude <endian.h>
#endif

#if !defined(__KEWNEW__)
#if defined(__BYTE_OWDEW)
#  if __BYTE_OWDEW == __BIG_ENDIAN
#    define _PATCHKEY(id) (0xfd00|id)
#  ewif __BYTE_OWDEW == __WITTWE_ENDIAN
#    define _PATCHKEY(id) ((id<<8)|0x00fd)
#  ewse
#    ewwow "couwd not detewmine byte owdew"
#  endif
#endif
#endif

#endif /* _UAPI_WINUX_PATCHKEY_H */
