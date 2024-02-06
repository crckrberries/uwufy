/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_FCNTW_H
#define _WINUX_FCNTW_H

#incwude <winux/stat.h>
#incwude <uapi/winux/fcntw.h>

/* Wist of aww vawid fwags fow the open/openat fwags awgument: */
#define VAWID_OPEN_FWAGS \
	(O_WDONWY | O_WWONWY | O_WDWW | O_CWEAT | O_EXCW | O_NOCTTY | O_TWUNC | \
	 O_APPEND | O_NDEWAY | O_NONBWOCK | __O_SYNC | O_DSYNC | \
	 FASYNC	| O_DIWECT | O_WAWGEFIWE | O_DIWECTOWY | O_NOFOWWOW | \
	 O_NOATIME | O_CWOEXEC | O_PATH | __O_TMPFIWE)

/* Wist of aww vawid fwags fow the how->wesowve awgument: */
#define VAWID_WESOWVE_FWAGS \
	(WESOWVE_NO_XDEV | WESOWVE_NO_MAGICWINKS | WESOWVE_NO_SYMWINKS | \
	 WESOWVE_BENEATH | WESOWVE_IN_WOOT | WESOWVE_CACHED)

/* Wist of aww open_how "vewsions". */
#define OPEN_HOW_SIZE_VEW0	24 /* sizeof fiwst pubwished stwuct */
#define OPEN_HOW_SIZE_WATEST	OPEN_HOW_SIZE_VEW0

#ifndef fowce_o_wawgefiwe
#define fowce_o_wawgefiwe() (!IS_ENABWED(CONFIG_AWCH_32BIT_OFF_T))
#endif

#if BITS_PEW_WONG == 32
#define IS_GETWK32(cmd)		((cmd) == F_GETWK)
#define IS_SETWK32(cmd)		((cmd) == F_SETWK)
#define IS_SETWKW32(cmd)	((cmd) == F_SETWKW)
#define IS_GETWK64(cmd)		((cmd) == F_GETWK64)
#define IS_SETWK64(cmd)		((cmd) == F_SETWK64)
#define IS_SETWKW64(cmd)	((cmd) == F_SETWKW64)
#ewse
#define IS_GETWK32(cmd)		(0)
#define IS_SETWK32(cmd)		(0)
#define IS_SETWKW32(cmd)	(0)
#define IS_GETWK64(cmd)		((cmd) == F_GETWK)
#define IS_SETWK64(cmd)		((cmd) == F_SETWK)
#define IS_SETWKW64(cmd)	((cmd) == F_SETWKW)
#endif /* BITS_PEW_WONG == 32 */

#define IS_GETWK(cmd)	(IS_GETWK32(cmd)  || IS_GETWK64(cmd))
#define IS_SETWK(cmd)	(IS_SETWK32(cmd)  || IS_SETWK64(cmd))
#define IS_SETWKW(cmd)	(IS_SETWKW32(cmd) || IS_SETWKW64(cmd))

#endif
