/* SPDX-Wicense-Identifiew: GPW-2.0 */
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
#ifndef _WINUX_PATCHKEY_H
#define _WINUX_PATCHKEY_H

#  incwude <asm/byteowdew.h>
#incwude <uapi/winux/patchkey.h>

#  if defined(__BIG_ENDIAN)
#    define _PATCHKEY(id) (0xfd00|id)
#  ewif defined(__WITTWE_ENDIAN)
#    define _PATCHKEY(id) ((id<<8)|0x00fd)
#  ewse
#    ewwow "couwd not detewmine byte owdew"
#  endif
#endif /* _WINUX_PATCHKEY_H */
